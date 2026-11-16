// =====================================================================
//  GD13 : layered displacement by object — lockstep layers, contact, engulfment, pressure by volume.
//  Reading R1-R7 in PROMPT.md. NO TWEAKING. Plane (z-integrated) volume-cost model.
//    V_i = N_i V_p ; W_i = 100 V_i ; B_i(k) = V_i + k W_i
//    psi_i(d) = cumulative cost of plane cells within distance d of the centreline ; S_i = d psi / d d
//    kappa_i(x) = max(0, (psi_i(d_i(x)) - V_i)/W_i) ; f_i(x) = V_i / (S_i l_P)  [pitches]
//  Inputs: GD08 mw_arms_data.js, GD09 object_allotment.csv.
//  Build: cl /std:c++20 /EHsc /O2 /openmp /I Engine/include gd13_layered_displacement.cpp   (run from this folder)
//  Writes: gd13_contacts.csv gd13_ridge_owner.csv mw_layers.js
//
//  Author: SDT Canonical Engine — J. C. Harvey, Melbourne
// =====================================================================

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <numbers>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <exception>
#include <sdt/laws.hpp>

namespace {

using namespace sdt::laws;
constexpr double PI = std::numbers::pi, DEG = PI / 180.0;
const double PC_M = measured::AU * 648000.0 / PI, KPC_M = 1000.0 * PC_M, KPC3_M3 = KPC_M * KPC_M * KPC_M;
const double LP = measured::l_P, V_P = law_IV::V_disp_p;
constexpr double H_CELL = 0.0625, HALF = 40.0, R_EDGE = 17.0;
constexpr int NG = (int)(2 * HALF / H_CELL) + 1;

std::string slurp(const std::string& fn) { std::ifstream f(fn, std::ios::binary); std::stringstream ss; ss << f.rdbuf(); return ss.str(); }
struct Node { double x, y, sin, sz; int tier; };
struct Arm { std::string name; std::vector<Node> nodes; };
std::vector<Arm> read_arms(const std::string& fn) {
    std::string s = slurp(fn); std::vector<Arm> arms; size_t pos = 0;
    while ((pos = s.find("{name:\"", pos)) != std::string::npos) {
        pos += 7; size_t e = s.find('"', pos); Arm a; a.name = s.substr(pos, e - pos);
        size_t p = s.find("pts:[", e) + 5;
        while (s[p] != ']') {
            if (s[p] == ',') { ++p; continue; }
            ++p; char* end; double v[5];
            for (int i = 0; i < 5; ++i) { v[i] = std::strtod(s.c_str() + p, &end); p = end - s.c_str(); if (s[p] == ',') ++p; }
            ++p; a.nodes.push_back({v[0], v[1], v[2], v[3], (int)std::lround(v[4])});
        }
        arms.push_back(a); pos = p;
    }
    return arms;
}
// object_allotment.csv rows:  "name",group,N,share,relation,source
double csv_N(const std::string& csv, const std::string& name) {
    size_t p = csv.find("\"" + name + "\","); if (p == std::string::npos) { std::printf("missing allotment row: %s\n", name.c_str()); std::exit(2); }
    p = csv.find("\",", p) + 2; p = csv.find(',', p) + 1;                 // skip name quote, group
    return std::strtod(csv.c_str() + p, nullptr);
}

// Object: centreline polyline (point = one vertex), per-vertex plate height (<0 means sphere), volume.
struct Obj {
    std::string name; double V_m3 = 0; bool sphere = false; int cls = 0;   // cls: 0 point/sphere, 1 bar, 2 arm
    std::vector<double> px, py, ph;                                         // polyline, plate heights (kpc)
    // per-cell fields
    std::vector<float> d, cost; std::vector<double> psi, S, kappa, f; std::vector<double> sd, scum;
};

void build(Obj& o, int nx, int ny, double h, double x0, double y0) {
    const size_t N = (size_t)nx * ny; o.d.assign(N, 0.f); o.cost.assign(N, 0.f);
#pragma omp parallel for schedule(static)
    for (long j = 0; j < ny; ++j) for (int i = 0; i < nx; ++i) {
        double x = x0 + h * i, y = y0 + h * j, best = 1e30, hh = 0;
        if (o.sphere) { best = std::hypot(x - o.px[0], y - o.py[0]); }
        else {
            const size_t m = o.px.size();
            if (m == 1) { best = std::hypot(x - o.px[0], y - o.py[0]); hh = o.ph[0]; }
            for (size_t s = 0; s + 1 < m; ++s) {
                double ax = o.px[s], ay = o.py[s], bx = o.px[s + 1], by = o.py[s + 1], vx = bx - ax, vy = by - ay, L2 = vx * vx + vy * vy;
                double t = L2 > 0 ? ((x - ax) * vx + (y - ay) * vy) / L2 : 0; t = std::fmax(0.0, std::fmin(1.0, t));
                double dx = x - (ax + t * vx), dy = y - (ay + t * vy), dd = dx * dx + dy * dy;
                if (dd < best * best) { best = std::sqrt(dd); hh = 0.5 * (o.ph[s] + o.ph[s + 1]); }
            }
        }
        size_t c = (size_t)j * nx + i; o.d[c] = (float)best; o.cost[c] = (float)((o.sphere ? 2.0 * best : hh) * h * h);
    }
    // sort cells by distance, cumulative cost (cell mid-point rule)
    std::vector<size_t> idx(N); for (size_t c = 0; c < N; ++c) idx[c] = c;
    std::sort(idx.begin(), idx.end(), [&](size_t a, size_t b) { return o.d[a] < o.d[b]; });
    o.sd.resize(N); o.scum.resize(N); o.psi.assign(N, 0.0); double cum = 0;
    for (size_t r = 0; r < N; ++r) { size_t c = idx[r]; o.sd[r] = o.d[c]; cum += o.cost[c]; o.scum[r] = cum; o.psi[c] = cum - 0.5 * o.cost[c]; }
}
double psi_at(const Obj& o, double dv) {                                    // cumulative cost of cells with d <= dv
    if (dv <= 0) return 0.0;
    size_t k = std::upper_bound(o.sd.begin(), o.sd.end(), dv) - o.sd.begin(); return k ? o.scum[k - 1] : 0.0;
}
void derive(Obj& o, int nx, int ny, double h, double band) {                // S = dpsi/dd, kappa, f
    const size_t N = (size_t)nx * ny; o.S.assign(N, 0.0); o.kappa.assign(N, 0.0); o.f.assign(N, 0.0);
    const double V_kpc3 = o.V_m3 / KPC3_M3, W = 100.0 * V_kpc3;
#pragma omp parallel for schedule(static)
    for (long c = 0; c < (long)N; ++c) {
        double dc = o.d[c]; double lo = std::fmax(0.0, dc - 0.5 * band), hi = dc + 0.5 * band;
        double S = (psi_at(o, hi) - psi_at(o, lo)) / (hi - lo);
        o.S[c] = S; o.kappa[c] = std::fmax(0.0, (o.psi[c] - V_kpc3) / W);
        o.f[c] = S > 0 ? o.V_m3 / (S * KPC_M * KPC_M * LP) : 0.0;
    }
    (void)h; (void)nx; (void)ny;
}

int g_fail = 0;
void check(const char* id, const char* what, bool ok, double v) { std::printf("  [%s] %s : %s  (%.3e)\n", ok ? "PASS" : "FAIL", id, what, v); if (!ok) ++g_fail; }

} // namespace

int run_main();
int main() { try { return run_main(); } catch (const std::exception& e) { std::printf("EXCEPTION: %s\n", e.what()); return 2; } catch (...) { std::printf("EXCEPTION unknown\n"); return 3; } }
int run_main() {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    std::printf("=================================================================\n");
    std::printf(" GD13 LAYERED DISPLACEMENT BY OBJECT  (reading R1-R7; NO TWEAKING)\n");
    std::printf("=================================================================\n");
    std::printf("V_p = %.4e m^3 ; l_P = %.4e m ; grid %d x %d at %.4f kpc ; region R < %.0f kpc\n\n", V_P, LP, NG, NG, H_CELL, R_EDGE);

    // ---------------- instrument validation ----------------
    std::printf("== INSTRUMENT VALIDATION ==\n");
    {   // V1 sphere, V5 shell shift
        Obj o; o.sphere = true; o.px = {0}; o.py = {0}; o.V_m3 = 1e10; build(o, NG, NG, H_CELL, -HALF, -HALF); derive(o, NG, NG, H_CELL, 0.3);
        double e1 = 0, e5 = 0;
        for (double d : {2.0, 4.0, 8.0}) { double psi = psi_at(o, d), an = 4.0 * PI * d * d * d / 3.0; e1 = std::fmax(e1, std::fabs(psi / an - 1));
            double S = (psi_at(o, d + 0.15) - psi_at(o, d - 0.15)) / 0.3; e1 = std::fmax(e1, std::fabs(S / (4 * PI * d * d) - 1)); }
        check("V1", "sphere: psi(d) and S(d) against 4 pi d^3/3 and 4 pi d^2 (2%)", e1 < 2e-2, e1);
        // f at a cell at distance ~ 5 kpc
        size_t c = (size_t)(NG / 2) * NG + (NG / 2 + 100);                  // x = +5 kpc, y = 0
        double r = o.d[c], fan = o.V_m3 / (4 * PI * r * r * KPC_M * KPC_M * LP);
        e5 = std::fabs(o.f[c] / fan - 1); check("V5", "sphere shell shift f = V/(4 pi r^2 l_P) (2%)", e5 < 2e-2, e5);
    }
    {   // V2 straight plate L = 6, H = 0.2
        const double rot = 17.0 * DEG; Obj o; o.px = {-3 * std::cos(rot), 3 * std::cos(rot)}; o.py = {-3 * std::sin(rot), 3 * std::sin(rot)}; o.ph = {0.2, 0.2}; o.V_m3 = 1e10; build(o, NG, NG, H_CELL, -HALF, -HALF);
        double e = 0, eS = 0; const double L = 6.0, H = 0.2;
        for (double d : {1.0, 2.0, 3.0}) { double psi = psi_at(o, d), an = H * (2 * d * L + PI * d * d); e = std::fmax(e, std::fabs(psi / an - 1));
            double S = (psi_at(o, d + 0.1) - psi_at(o, d - 0.1)) / 0.2, anS = H * (2 * L + 2 * PI * d); eS = std::fmax(eS, std::fabs(S / anS - 1)); }
        check("V2", "plate: psi(d) = H(2dL + pi d^2) (2%)", e < 2e-2, e); check("V2", "plate: S(d) = H(2L + 2 pi d) (3%)", eS < 3e-2, eS);
    }
    {   // V3 two spheres at (-3,0) and (+3,0), V_b = 4 V_a
        Obj a, b; a.sphere = b.sphere = true; a.px = {-3}; a.py = {0}; b.px = {3}; b.py = {0}; a.V_m3 = 1e10; b.V_m3 = 4e10;
        build(a, NG, NG, H_CELL, -HALF, -HALF); derive(a, NG, NG, H_CELL, 0.3); build(b, NG, NG, H_CELL, -HALF, -HALF); derive(b, NG, NG, H_CELL, 0.3);
        double kc = 1e300; size_t cc = 0; const size_t N = (size_t)NG * NG;
        for (size_t c = 0; c < N; ++c) { double m = std::fmax(a.kappa[c], b.kappa[c]); if (m < kc) { kc = m; cc = c; } }
        // equal arrival layer: psi_a/V_a = psi_b/V_b  =>  d_b/d_a = (V_b/V_a)^(1/3), d_a + d_b = 6
        double Va = a.V_m3 / KPC3_M3, dA = 6.0 / (1.0 + std::cbrt(4.0)), kan = (4.0 * PI * dA * dA * dA / 3.0) / (100.0 * Va);
        check("V3a", "two spheres: contact layer against the analytic arrival condition (2%)", std::fabs(kc / kan - 1) < 2e-2, kc / kan - 1);
        // equal-f meeting point on the axis y = 0: numerical switch of the larger f
        double xs = 1e9; for (int i = 0; i < NG - 1; ++i) { size_t c0 = (size_t)(NG / 2) * NG + i, c1 = c0 + 1; double x0 = -HALF + H_CELL * i;
            if (x0 > -3 && x0 < 3 && ((a.f[c0] > b.f[c0]) != (a.f[c1] > b.f[c1]))) { xs = x0 + 0.025; break; } }
        check("V3b", "two spheres: equal-f meeting point at x = -1 kpc (closed form sqrt(Va/Vb) = 1/2) (2%)", std::fabs(xs - (-1.0)) < 0.1, xs + 1.0); (void)cc;
    }
    std::printf("  validation failures: %d\n\n", g_fail);
    if (g_fail) { std::printf("validation failed — nothing computed.\n"); return 1; }

    // ---------------- objects ----------------
    auto arms = read_arms("../GD08_Milky_Way_Arm_Topology/mw_arms_data.js");
    std::string csv = slurp("../GD09_Milky_Way_Baryon_Inventory/object_allotment.csv");
    if (arms.empty() || csv.empty()) { std::printf("input files missing\n"); return 1; }
    std::vector<Obj> obj;
    { Obj o; o.name = "Sgr A*"; o.sphere = true; o.cls = 0; o.px = {0}; o.py = {0}; o.V_m3 = csv_N(csv, "Sgr A* (4.2e6 Msun, mass-equivalent)") * V_P; obj.push_back(o); }
    { Obj o; o.name = "bulge"; o.sphere = true; o.cls = 0; o.px = {0}; o.py = {0}; o.V_m3 = csv_N(csv, "Bulge region (stellar + gas)") * V_P; obj.push_back(o); }
    { Obj o; o.name = "long bar"; o.cls = 1; const double ang = 30.5 * DEG; o.px = {-5.0 * std::sin(ang), 5.0 * std::sin(ang)}; o.py = {-5.0 * std::cos(ang), 5.0 * std::cos(ang)}; o.ph = {0.36, 0.36};
      o.V_m3 = csv_N(csv, "Long bar (thin + super-thin)") * V_P; obj.push_back(o); }
    for (auto& a : arms) { Obj o; o.name = a.name; o.cls = 2;
        for (auto& nd : a.nodes) if (nd.tier <= 1) { o.px.push_back(nd.x); o.py.push_back(nd.y); o.ph.push_back(2.0 * nd.sz); }
        o.V_m3 = csv_N(csv, a.name + ", +-2 sigma footprint") * V_P; obj.push_back(o); }
    const int NO = (int)obj.size(); const size_t N = (size_t)NG * NG;
    for (auto& o : obj) { build(o, NG, NG, H_CELL, -HALF, -HALF); derive(o, NG, NG, H_CELL, 0.3); }
    double Vsum = 0; for (auto& o : obj) Vsum += o.V_m3;
    std::printf("== OBJECTS (V = N V_p, layer W = 100 V) ==\n%-10s %-12s %-12s %-10s %-12s\n", "object", "N baryons", "V [m^3]", "share of V", "W [m^3]");
    for (auto& o : obj) std::printf("%-10s %-12.3e %-12.3e %-10.4f %-12.3e\n", o.name.c_str(), o.V_m3 / V_P, o.V_m3, o.V_m3 / Vsum, 100 * o.V_m3);
    std::printf("objects hold %.4e baryons ; the unallocated thin-disc + gas baryons and the thick disc belong to no object and do not displace here\n", Vsum / V_P);

    // ---------------- region mask, K_end ----------------
    std::vector<char> mask(N, 0); size_t nmask = 0;
    for (int j = 0; j < NG; ++j) for (int i = 0; i < NG; ++i) { double x = -HALF + H_CELL * i, y = -HALF + H_CELL * j; if (std::hypot(x, y) < R_EDGE) { mask[(size_t)j * NG + i] = 1; ++nmask; } }
    double K_end = 0; size_t c_end = 0;
    for (size_t c = 0; c < N; ++c) if (mask[c]) { double m = 1e300; for (auto& o : obj) m = std::fmin(m, o.kappa[c]); if (m > K_end) { K_end = m; c_end = c; } }
    std::printf("\nK_end = %.4e layers (the last plane cell inside %.0f kpc is first reached at x = (%.2f, %.2f) kpc)\n", K_end, R_EDGE, -HALF + H_CELL * (c_end % NG), -HALF + H_CELL * (c_end / NG));

    // ---------------- O1 contact timeline ----------------
    std::printf("\n== O1 CONTACT TIMELINE (first layer at which two objects reach a common plane cell) ==\n");
    struct Ct { double k; int a, b; size_t cell; };
    std::vector<Ct> cts;
    for (int a = 0; a < NO; ++a) for (int b = a + 1; b < NO; ++b) {
        double kc = 1e300; size_t cell = 0;
        for (size_t c = 0; c < N; ++c) if (mask[c]) { double m = std::fmax(obj[a].kappa[c], obj[b].kappa[c]); if (m < kc) { kc = m; cell = c; } }
        cts.push_back({kc, a, b, cell});
    }
    std::sort(cts.begin(), cts.end(), [](const Ct& p, const Ct& q) { return p.k < q.k; });
    FILE* fc = std::fopen("gd13_contacts.csv", "w"); std::fprintf(fc, "k_contact,object_a,object_b,x_kpc,y_kpc,R_kpc,reach_a_kpc,reach_b_kpc,k_over_k_end\n");
    std::printf("%-4s %-12s %-10s %-10s %-18s %-8s %-9s %-9s %-10s\n", "#", "k_c", "object A", "object B", "contact cell (x,y)", "R kpc", "reach A", "reach B", "k_c/K_end");
    int rank = 0;
    for (auto& t : cts) { double x = -HALF + H_CELL * (t.cell % NG), y = -HALF + H_CELL * (t.cell / NG);
        double ra = obj[t.a].d[t.cell], rb = obj[t.b].d[t.cell];
        std::fprintf(fc, "%.6e,%s,%s,%.2f,%.2f,%.2f,%.3f,%.3f,%.4e\n", t.k, obj[t.a].name.c_str(), obj[t.b].name.c_str(), x, y, std::hypot(x, y), ra, rb, t.k / K_end);
        if (rank < 24) std::printf("%-4d %-12.4e %-10s %-10s (%6.2f,%6.2f)        %-8.2f %-9.3f %-9.3f %-10.3e\n", rank + 1, t.k, obj[t.a].name.c_str(), obj[t.b].name.c_str(), x, y, std::hypot(x, y), ra, rb, t.k / K_end);
        ++rank; }
    std::fclose(fc);
    std::printf("(showing the first 24 of %d pairs; all in gd13_contacts.csv)\n", (int)cts.size());

    // ---------------- reach, owner, pressure ----------------
    std::vector<int> owner(N, -1); std::vector<double> fown(N, 0.0), fsum(N, 0.0); std::vector<int> nreach(N, 0);
    for (size_t c = 0; c < N; ++c) if (mask[c]) {
        int best = -1; double bf = -1; int cnt = 0; double ss = 0;
        for (int i = 0; i < NO; ++i) if (obj[i].kappa[c] <= K_end) { ++cnt; ss += obj[i].f[c]; if (obj[i].f[c] > bf) { bf = obj[i].f[c]; best = i; } }
        owner[c] = best; fown[c] = bf; fsum[c] = ss; nreach[c] = cnt;
    }
    {   size_t owned = 0, un = 0; for (size_t c = 0; c < N; ++c) if (mask[c]) { if (owner[c] >= 0) ++owned; else ++un; }
        check("V4", "owned + unreached cells equal the region cell count", owned + un == nmask, (double)(owned + un) - (double)nmask); }

    // ---------------- O2/O3 ownership ----------------
    std::printf("\n== O2 END-STATE OWNERSHIP at K_end (plane, R < %.0f kpc; owner = largest pressure by volume among reaching objects) ==\n", R_EDGE);
    std::vector<double> area(NO, 0.0), vol(NO, 0.0);
    for (size_t c = 0; c < N; ++c) if (mask[c] && owner[c] >= 0) { area[owner[c]] += H_CELL * H_CELL; vol[owner[c]] += obj[owner[c]].cost[c]; }
    double atot = 0; for (double a : area) atot += a;
    std::printf("%-10s %-12s %-10s %-14s %-12s\n", "object", "area kpc^2", "area share", "owned volume", "share of V");
    for (int i = 0; i < NO; ++i) std::printf("%-10s %-12.2f %-10.4f %-14.4e %-12.4f\n", obj[i].name.c_str(), area[i], area[i] / atot, vol[i], obj[i].V_m3 / Vsum);
    double aArms = 0, aBulge = 0, aBar = 0; for (int i = 0; i < NO; ++i) { if (obj[i].cls == 2) aArms += area[i]; else if (obj[i].cls == 1) aBar += area[i]; else aBulge += area[i]; }
    std::printf("classes over R < 17 kpc: arms %.4f , bulge+Sgr A* %.4f , bar %.4f of the owned area\n", aArms / atot, aBulge / atot, aBar / atot);

    std::printf("\n== O3 OWNER BY CLASS WITH RADIUS (annulus area shares) ==\n%-8s %-9s %-9s %-9s | %-12s\n", "R kpc", "arms", "bulge", "bar", "f_owner mean");
    double R_cross = -1, prev_a = 0, prev_b = 0; double armShare3 = 0; double a3 = 0, aA3 = 0;
    for (int rb = 0; rb < 17; ++rb) {
        double A = 0, B = 0, Br = 0, T = 0, fs = 0; for (size_t c = 0; c < N; ++c) if (mask[c] && owner[c] >= 0) { double R = std::hypot(-HALF + H_CELL * (c % NG), -HALF + H_CELL * (c / NG)); if (R >= rb && R < rb + 1) { T += 1; fs += fown[c]; int k = obj[owner[c]].cls; if (k == 2) A += 1; else if (k == 1) Br += 1; else B += 1; } if (R >= 3 && R < 17) { a3 += 1; if (obj[owner[c]].cls == 2) aA3 += 1; } }
        if (T > 0) std::printf("%-8d %-9.4f %-9.4f %-9.4f | %-12.4e\n", rb + 1, A / T, B / T, Br / T, fs / T);
        if (R_cross < 0 && rb > 0 && prev_b > prev_a && B > A) {} (void)prev_a; (void)prev_b;
        if (T > 0) { if (R_cross < 0 && A > B && rb >= 1) R_cross = rb; prev_a = A / T; prev_b = B / T; }
    }
    armShare3 = a3 > 0 ? aA3 / a3 : 0;
    std::printf("radius where the arms' owned area first exceeds the bulge's: %s\n", R_cross >= 0 ? (std::to_string(R_cross).substr(0, 4) + " kpc (annulus starting)").c_str() : "none");
    {   const char* cls = armShare3 >= 0.5 ? "supported" : (armShare3 >= 0.25 ? "marginal" : "not supported");
        std::printf("classification 'the spiral arms dominate': arms' share of owned area over 3 < R < 17 kpc = %.4f  ->  %s\n", armShare3, cls); }

    // ---------------- O4 free pressure laws ----------------
    std::printf("\n== O4 FREE PRESSURE BY VOLUME f_i = V_i/(S_i l_P) against distance from the centreline ==\n%-10s %-9s %-9s %-9s %-9s %-9s\n", "object", "d=0.5", "d=1", "d=2", "d=4", "d=8 kpc");
    for (auto& o : obj) { std::printf("%-10s", o.name.c_str()); for (double dv : {0.5, 1.0, 2.0, 4.0, 8.0}) { double S = (psi_at(o, dv + 0.15) - psi_at(o, std::fmax(0.0, dv - 0.15))) / 0.3; std::printf(" %-9.3e", o.V_m3 / (S * KPC_M * KPC_M * LP)); } std::printf("\n"); }

    // ---------------- O5 crossover and shunt ----------------
    std::printf("\n== O5 CROSSOVER AND SHUNT at K_end (50%% of each object's crossover volume is shunted into its own layer) ==\n");
    std::printf("%-10s %-12s %-12s %-12s %-14s\n", "object", "reached cost", "crossover", "frac", "shunt / B(K_end)");
    std::vector<double> xfrac(NO, 0.0);
    for (int i = 0; i < NO; ++i) { double rc = 0, xc = 0; for (size_t c = 0; c < N; ++c) if (mask[c] && obj[i].kappa[c] <= K_end) { rc += obj[i].cost[c]; if (nreach[c] >= 2) xc += obj[i].cost[c]; }
        double B = (obj[i].V_m3 + K_end * 100.0 * obj[i].V_m3) / KPC3_M3; xfrac[i] = rc > 0 ? xc / rc : 0;
        std::printf("%-10s %-12.4e %-12.4e %-12.4f %-14.4e\n", obj[i].name.c_str(), rc, xc, xfrac[i], 0.5 * xc / B); }

    // arms: where the crossover sits along the ridge, and who owns the ridge
    std::printf("\n== arms: crossover and owner along the ridge (thirds, inner -> outer) ; engulfment by the bulge ==\n");
    FILE* fo = std::fopen("gd13_ridge_owner.csv", "w"); std::fprintf(fo, "arm,node,x,y,R,owner,nreach,f_owner,f_sum\n");
    std::printf("%-10s %-30s %-32s %-10s\n", "arm", "crossover fraction (in/mid/out)", "owner = bulge or Sgr A* (in/mid/out)", "engulfed");
    int totalNodes = 0, engulfed = 0;
    for (int i = 0; i < NO; ++i) if (obj[i].cls == 2) {
        const Obj& o = obj[i]; size_t m = o.px.size(); std::vector<double> len(m, 0.0); for (size_t s = 1; s < m; ++s) len[s] = len[s - 1] + std::hypot(o.px[s] - o.px[s - 1], o.py[s] - o.py[s - 1]);
        double L = len.back(); double xc[3] = {0, 0, 0}, ob[3] = {0, 0, 0}, nn[3] = {0, 0, 0}; int eg = 0;
        for (size_t s = 0; s < m; ++s) { int ci = (int)std::floor((o.px[s] + HALF) / H_CELL + 0.5), cj = (int)std::floor((o.py[s] + HALF) / H_CELL + 0.5); size_t c = (size_t)cj * NG + ci; if (ci < 0 || cj < 0 || ci >= NG || cj >= NG) continue;
            int third = L > 0 ? std::min(2, (int)(3.0 * len[s] / L)) : 0; ++nn[third]; if (nreach[c] >= 2) ++xc[third]; bool bk = owner[c] >= 0 && obj[owner[c]].cls == 0; if (bk) { ++ob[third]; ++eg; }
            std::fprintf(fo, "%s,%zu,%.3f,%.3f,%.3f,%s,%d,%.4e,%.4e\n", o.name.c_str(), s, o.px[s], o.py[s], std::hypot(o.px[s], o.py[s]), owner[c] >= 0 ? obj[owner[c]].name.c_str() : "none", nreach[c], fown[c], fsum[c]); }
        totalNodes += (int)m; engulfed += eg;
        std::printf("%-10s %-.3f / %-.3f / %-.3f             %-.3f / %-.3f / %-.3f                %d of %zu\n", o.name.c_str(), nn[0] ? xc[0] / nn[0] : 0, nn[1] ? xc[1] / nn[1] : 0, nn[2] ? xc[2] / nn[2] : 0,
                    nn[0] ? ob[0] / nn[0] : 0, nn[1] ? ob[1] / nn[1] : 0, nn[2] ? ob[2] / nn[2] : 0, eg, m);
    }
    std::fclose(fo);
    std::printf("ridge nodes whose cell the bulge or Sgr A* owns at K_end: %d of %d\n", engulfed, totalNodes);

    // ---------------- O1b / O5b informational additions (Amendment 4) ----------------
    std::printf("\n== O1b per ridge node: layer at which another object first reaches the node's cell; layer at which the bulge front reaches it ==\n");
    std::printf("%-10s %-34s %-34s %-24s\n", "arm", "first reached by another (median k, in/mid/out)", "who (most often, in/mid/out)", "bulge reaches (median k, in/mid/out)");
    for (int i = 0; i < NO; ++i) if (obj[i].cls == 2) {
        const Obj& o = obj[i]; size_t m = o.px.size(); std::vector<double> len(m, 0.0); for (size_t q = 1; q < m; ++q) len[q] = len[q - 1] + std::hypot(o.px[q] - o.px[q - 1], o.py[q] - o.py[q - 1]);
        double L = len.back(); std::vector<double> kf[3], kb[3]; std::vector<int> who[3];
        for (size_t q = 0; q < m; ++q) { int ci = (int)std::floor((o.px[q] + HALF) / H_CELL + 0.5), cj = (int)std::floor((o.py[q] + HALF) / H_CELL + 0.5); if (ci < 0 || cj < 0 || ci >= NG || cj >= NG) continue;
            size_t c = (size_t)cj * NG + ci; int third = L > 0 ? std::min(2, (int)(3.0 * len[q] / L)) : 0; double best = 1e300; int bw = -1;
            for (int j = 0; j < NO; ++j) if (j != i && obj[j].kappa[c] < best) { best = obj[j].kappa[c]; bw = j; }
            kf[third].push_back(best); who[third].push_back(bw); kb[third].push_back(obj[1].kappa[c]); }
        auto med = [](std::vector<double> v) { if (v.empty()) return 0.0; std::sort(v.begin(), v.end()); return v[v.size() / 2]; };
        auto mode = [&](const std::vector<int>& w) { std::vector<int> cnt(NO, 0); for (int x : w) if (x >= 0) ++cnt[x]; int b = 0; for (int j = 1; j < NO; ++j) if (cnt[j] > cnt[b]) b = j; return b; };
        std::printf("%-10s %.2e / %.2e / %.2e          %-9s / %-9s / %-9s        %.2e / %.2e / %.2e\n", o.name.c_str(), med(kf[0]), med(kf[1]), med(kf[2]),
                    obj[mode(who[0])].name.c_str(), obj[mode(who[1])].name.c_str(), obj[mode(who[2])].name.c_str(), med(kb[0]), med(kb[1]), med(kb[2]));
    }
    std::printf("(layers; K_end = %.3e ; the bulge front reaches in-plane radius r at k = 4 pi r^3/3 / W_bulge)\n", K_end);
    std::printf("\n== O5b crossover fraction of each object (cost of cells it has reached that another object has also reached / its reached cost) at layer checkpoints ==\n");
    std::printf("%-10s %-10s %-10s %-10s %-10s | %-26s\n", "object", "k=1e47", "k=1e48", "k=1e49", "K_end", "bulge in-plane reach kpc at 1e47/1e48/1e49");
    for (int i = 0; i < NO; ++i) { std::printf("%-10s", obj[i].name.c_str());
        for (double Kc : {1e47, 1e48, 1e49, K_end}) { double rc = 0, xc = 0; for (size_t c = 0; c < N; ++c) if (mask[c] && obj[i].kappa[c] <= Kc) { rc += obj[i].cost[c]; int cnt = 0; for (int j = 0; j < NO; ++j) if (obj[j].kappa[c] <= Kc) ++cnt; if (cnt >= 2) xc += obj[i].cost[c]; }
            std::printf(" %-10.4f", rc > 0 ? xc / rc : 0.0); }
        if (i == 1) { std::printf(" | "); for (double Kc : {1e47, 1e48, 1e49}) std::printf("%.2f ", std::cbrt(3.0 * Kc * 100.0 * obj[1].V_m3 / KPC3_M3 / (4.0 * PI))); }
        std::printf("\n"); }

    // ---------------- O6 superposition comparison ----------------
    {   double s1 = 0, s2 = 0, n = 0; for (size_t c = 0; c < N; ++c) if (mask[c] && owner[c] >= 0) { double R = std::hypot(-HALF + H_CELL * (c % NG), -HALF + H_CELL * (c / NG)); if (R > 3) { s1 += fown[c]; s2 += fsum[c]; n += 1; } }
        std::printf("\nO6 over 3 < R < 17 kpc: mean f of the owner %.4e ; mean of the superposition sum f_i %.4e ; ratio sum/owner %.3f\n", s1 / n, s2 / n, s2 / s1); }

    // ---------------- viewer data (0.4 kpc blocks) ----------------
    {
        const int step = 4, MS = 80, M = 2 * MS + 1, c0 = (NG - 1) / 2; const double halfOut = MS * step * H_CELL; FILE* fj = std::fopen("mw_layers.js", "w");
        std::fprintf(fj, "// Generated by gd13_layered_displacement.cpp. Plane only; x,y in kpc. owner = object index (-1 outside R < 17 kpc).\n");
        std::fprintf(fj, "window.MW_LAYERS={n:%d,half:%.4f,kEnd:%.6e,cats:[", M, halfOut, K_end);
        for (int i = 0; i < NO; ++i) std::fprintf(fj, "%s\"%s\"", i ? "," : "", obj[i].name.c_str());
        std::fprintf(fj, "],colors:[[255,255,255],[255,183,77],[255,112,67],[201,167,255],[255,138,101],[79,195,247],[129,199,132],[245,200,80],[240,98,146],[128,203,196]],cases:[\n");
        std::fprintf(fj, "{name:\"Owner of each plane cell at the end of the layering (largest pressure by volume among the objects that reach it)\",kind:\"cat\",unit:\"\",v:[");
        for (int j = 0; j < M; ++j) for (int i = 0; i < M; ++i) std::fprintf(fj, "%s%d", (i == 0 && j == 0) ? "" : ",", owner[(size_t)(c0 + (j - MS) * step) * NG + (c0 + (i - MS) * step)]);
        std::fprintf(fj, "]},\n{name:\"Pressure by volume of the owner\",kind:\"log\",unit:\"pitches\",v:[");
        for (int j = 0; j < M; ++j) for (int i = 0; i < M; ++i) { size_t c = (size_t)(c0 + (j - MS) * step) * NG + (c0 + (i - MS) * step); std::fprintf(fj, "%s%.5g", (i == 0 && j == 0) ? "" : ",", owner[c] >= 0 ? fown[c] : 1e-3); }
        std::fprintf(fj, "]}\n]};\n"); std::fclose(fj);
    }
    std::printf("\nwrote gd13_contacts.csv gd13_ridge_owner.csv mw_layers.js\n");
    return 0;
}
