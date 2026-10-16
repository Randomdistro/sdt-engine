// =====================================================================
//  GD10 : Milky Way displacement field — bulge shells, arm sheaths,
//  equalisation along sheaths, emission depth.
//  ---------------------------------------------------------------------
//  Z(x) = koppa_b * sum_i w_i / |x - x_i|   (Depth-closure z = koppa/r, superposed)
//  v_c^2/c^2 = -R dZ/dR ;  (1+z_pair) = (1+Z_emit)/(1+Z_obs)
//  H1: P = P_conv (1+Z)^4.   H2: Z_eq - lam^2 Z_eq'' = Z_dil along each sheath ridge.
//  Pre-registration: PROMPT.md (same folder). No fitted parameter; lambda is scanned.
//
//  Inputs read from generated data: ../GD08_.../mw_arms_data.js, ../GD09_.../mw_baryons.js
//  Build: cl /std:c++20 /EHsc /O2 /openmp /I Engine/include gd10_displacement_field.cpp
//  Run from this folder. Writes: gd10_ridge_profiles.csv gd10_sightlines.csv mw_displacement.js
//
//  Author: SDT Canonical Engine — J. C. Harvey, Melbourne
// =====================================================================

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cmath>
#include <numbers>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <sdt/laws.hpp>

namespace {

using namespace sdt::laws;
constexpr double PI = std::numbers::pi, DEG = PI / 180.0;
const double KPC_M = 1000.0 * measured::AU * 648000.0 / PI;       // exact parsec definition
const double C_MS  = measured::c;                                  // m/s
const double KOPPA_B = bridge::koppa_per_baryon;                   // m per baryon

constexpr double R0 = 8.15, THETA0 = 236.0, THETA0_ERR = 7.0;      // Reid 2019 (kpc, km/s)
constexpr double EPS = 0.03;                                       // Plummer softening [kpc]
constexpr int NP_TOTAL = 240000;
constexpr double ARM_CONTRAST = 1.32;                              // Drimmel & Spergel 2001 (K band)
constexpr double LAMBDAS[] = {0.5, 1, 2, 4, 8, 16};
constexpr int NLAM = 6;

// ---------------- data readers (GD08 / GD09 generated files) ----------------
std::string slurp(const std::string& fn) {
    std::ifstream f(fn, std::ios::binary); std::stringstream ss; ss << f.rdbuf(); return ss.str();
}
struct Node { double x, y, sin, sz; int tier; int arm; double R; };
struct Arm { std::string name; std::vector<Node> nodes; };

std::vector<Arm> read_arms(const std::string& fn) {
    std::string s = slurp(fn); std::vector<Arm> arms; size_t pos = 0;
    while ((pos = s.find("{name:\"", pos)) != std::string::npos) {
        pos += 7; size_t e = s.find('"', pos); Arm a; a.name = s.substr(pos, e - pos);
        size_t p = s.find("pts:[", e) + 5;
        while (s[p] != ']') {
            if (s[p] == ',') { ++p; continue; }
            ++p;                                                   // '['
            char* end; double v[5];
            for (int i = 0; i < 5; ++i) { v[i] = std::strtod(s.c_str() + p, &end); p = end - s.c_str(); if (s[p] == ',') ++p; }
            ++p;                                                   // ']'
            a.nodes.push_back({v[0], v[1], v[2], v[3], (int)std::lround(v[4]), (int)arms.size(), std::hypot(v[0], v[1])});
        }
        arms.push_back(a); pos = p;
    }
    return arms;
}
struct Row { double lo, c, hi; };
Row read_count(const std::string& js, const std::string& id) {
    size_t p = js.find("{id:\"" + id + "\"");
    if (p == std::string::npos) { std::printf("missing row %s\n", id.c_str()); std::exit(2); }
    p = js.find("n:[", p) + 3; char* end; Row r;
    r.lo = std::strtod(js.c_str() + p, &end); p = end - js.c_str() + 1;
    r.c  = std::strtod(js.c_str() + p, &end); p = end - js.c_str() + 1;
    r.hi = std::strtod(js.c_str() + p, &end);
    return r;
}

// ---------------- deterministic sampling ----------------
struct Rng {
    std::mt19937_64 g; explicit Rng(uint64_t s) : g(s) {}
    double u() { return ((g() >> 11) + 0.5) * (1.0 / 9007199254740992.0); }
    double expo(double mean) { return -mean * std::log(u()); }
};
struct Cloud { std::vector<double> x, y, z, a; };               // a = koppa_b * w / kpc_m  [kpc]
void push(Cloud& C, double x, double y, double z, double a) { C.x.push_back(x); C.y.push_back(y); C.z.push_back(z); C.a.push_back(a); }

// b/p bulge, exponential in s = |(x/hx, y/hy, z/hz)|, major axis 27 deg (BH&G 2016). Also returns s.
Cloud make_bulge(uint64_t seed, int Np, double N, std::vector<double>* svals) {
    Rng r(seed); Cloud C; const double hx = 0.70, hy = 0.44, hz = 0.18, ang = 27.0 * DEG;
    const double a_i = KOPPA_B * (N / Np) / KPC_M, sa = std::sin(ang), ca = std::cos(ang);
    for (int i = 0; i < Np; ++i) {
        double s;
        do { s = r.expo(1) + r.expo(1) + r.expo(1); } while (s > 10.0);
        double cz = 2 * r.u() - 1, ph = 2 * PI * r.u(), sz = std::sqrt(1 - cz * cz);
        double X = hx * s * sz * std::cos(ph), Y = hy * s * sz * std::sin(ph), Zc = hz * s * cz;
        push(C, X * sa + Y * ca, X * ca - Y * sa, Zc, a_i);
        if (svals) svals->push_back(s);
    }
    return C;
}
// exponential disc: surface density ~ exp(-R/Rd), vertical Laplace(zd), R truncated to [Rmin,Rmax].
Cloud make_disc(uint64_t seed, int Np, double N, double Rd, double zd, double Rmin, double Rmax) {
    Rng r(seed); Cloud C; const double a_i = KOPPA_B * (N / Np) / KPC_M;
    for (int i = 0; i < Np; ++i) {
        double R;
        do { R = r.expo(Rd) + r.expo(Rd); } while (R < Rmin || R > Rmax);
        double ph = 2 * PI * r.u(), z = (r.u() < 0.5 ? -1 : 1) * r.expo(zd);
        push(C, R * std::cos(ph), R * std::sin(ph), z, a_i);
    }
    return C;
}
void append(Cloud& A, const Cloud& B) {
    A.x.insert(A.x.end(), B.x.begin(), B.x.end()); A.y.insert(A.y.end(), B.y.begin(), B.y.end());
    A.z.insert(A.z.end(), B.z.begin(), B.z.end()); A.a.insert(A.a.end(), B.a.begin(), B.a.end());
}

// ---------------- field evaluation ----------------
struct Pt { double x, y, z; };
std::vector<double> evalZ(const Cloud& C, const std::vector<Pt>& pts) {
    std::vector<double> out(pts.size()); const double e2 = EPS * EPS; const size_t n = C.x.size();
#pragma omp parallel for schedule(static)
    for (long i = 0; i < (long)pts.size(); ++i) {
        double s = 0; const double px = pts[i].x, py = pts[i].y, pz = pts[i].z;
        for (size_t k = 0; k < n; ++k) {
            double dx = px - C.x[k], dy = py - C.y[k], dz = pz - C.z[k];
            s += C.a[k] / std::sqrt(dx * dx + dy * dy + dz * dz + e2);
        }
        out[i] = s;
    }
    return out;
}
// v_c^2/c^2 = -R dZ/dR = R * sum a_i ((x-x_i).rhat)/(d^2+eps^2)^{3/2}, at points on a circle.
double rotation_bridge(const Cloud& C, double R, int naz) {
    double tot = 0; const double e2 = EPS * EPS; const size_t n = C.x.size();
#pragma omp parallel for reduction(+ : tot) schedule(static)
    for (int j = 0; j < naz; ++j) {
        double ph = 2 * PI * (j + 0.5) / naz, rx = std::sin(ph), ry = std::cos(ph), px = R * rx, py = R * ry, s = 0;
        for (size_t k = 0; k < n; ++k) {
            double dx = px - C.x[k], dy = py - C.y[k], dz = -C.z[k], d2 = dx * dx + dy * dy + dz * dz + e2;
            s += C.a[k] * (dx * rx + dy * ry) / (d2 * std::sqrt(d2));
        }
        tot += R * s;
    }
    return tot / naz;
}

// ---------------- equalisation along a sheath ridge (H2) ----------------
// (Z_i - lam^2/c_i [(Z_{i+1}-Z_i)/h_i - (Z_i-Z_{i-1})/h_{i-1}] = Zd_i), finite-volume, reflecting ends.
std::vector<double> equalise(const std::vector<double>& Zd, const std::vector<double>& h, double lam) {
    const int n = (int)Zd.size(); if (n < 2 || lam <= 0) return Zd;
    std::vector<double> cw(n), lo(n, 0), di(n), up(n, 0), rhs = Zd, Z(n);
    for (int i = 0; i < n; ++i) cw[i] = 0.5 * ((i > 0 ? h[i - 1] : 0) + (i < n - 1 ? h[i] : 0));
    const double L2 = lam * lam;
    for (int i = 0; i < n; ++i) {
        double dl = i > 0 ? 1.0 / h[i - 1] : 0, dr = i < n - 1 ? 1.0 / h[i] : 0;
        di[i] = 1 + L2 / cw[i] * (dl + dr); lo[i] = -L2 / cw[i] * dl; up[i] = -L2 / cw[i] * dr;
    }
    for (int i = 1; i < n; ++i) { double m = lo[i] / di[i - 1]; di[i] -= m * up[i - 1]; rhs[i] -= m * rhs[i - 1]; }
    Z[n - 1] = rhs[n - 1] / di[n - 1];
    for (int i = n - 2; i >= 0; --i) Z[i] = (rhs[i] - up[i] * Z[i + 1]) / di[i];
    return Z;
}
double weighted_mean(const std::vector<double>& Z, const std::vector<double>& h) {
    double s = 0, w = 0; const int n = (int)Z.size();
    for (int i = 0; i < n; ++i) { double c = 0.5 * ((i > 0 ? h[i - 1] : 0) + (i < n - 1 ? h[i] : 0)); s += c * Z[i]; w += c; }
    return s / w;
}
double integral(const std::vector<double>& Z, const std::vector<double>& h) {
    double s = 0; const int n = (int)Z.size();
    for (int i = 0; i < n; ++i) s += 0.5 * ((i > 0 ? h[i - 1] : 0) + (i < n - 1 ? h[i] : 0)) * Z[i];
    return s;
}

int g_fail = 0;
void check(const char* id, const char* what, bool ok, double v) {
    std::printf("  [%s] %s : %s  (%.3e)\n", ok ? "PASS" : "FAIL", id, what, v);
    if (!ok) ++g_fail;
}
double cz(double Z) { return C_MS * Z; }                           // m/s

} // namespace

int main() {
    std::printf("=================================================================\n");
    std::printf(" GD10 MILKY WAY DISPLACEMENT FIELD  (dilute Z = koppa_b sum/r ; H1, H2 labelled)\n");
    std::printf("=================================================================\n");
    std::printf("koppa_b = %.4e m ; kpc = %.6e m ; c = %.0f m/s\n\n", KOPPA_B, KPC_M, C_MS);

    // ---------------- instrument validation ----------------
    std::printf("== INSTRUMENT VALIDATION ==\n");
    {   // V1 point baryon
        Cloud c; push(c, 0, 0, 0, KOPPA_B * 1e67 / KPC_M);
        std::vector<Pt> p = {{3, 0, 0}}; auto z = evalZ(c, p);
        double an = KOPPA_B * 1e67 / KPC_M / 3.0;
        check("V1", "point baryon Z = koppa_b N / r", std::fabs(z[0] / an - 1) < 1e-3, z[0] / an - 1);
        // V5 rotation bridge on the point mass: v^2/c^2 = koppa_b N / r
        double vb = rotation_bridge(c, 3.0, 8);
        check("V5", "rotation bridge on a point mass", std::fabs(vb / an - 1) < 1e-3, vb / an - 1);
    }
    {   // V2 shell theorem (uniform hollow shell, radius 1 kpc)
        Rng r(11); Cloud c; const int N = 200000; const double N_b = 1e67;
        for (int i = 0; i < N; ++i) {
            double cz_ = 2 * r.u() - 1, ph = 2 * PI * r.u(), s = std::sqrt(1 - cz_ * cz_);
            push(c, s * std::cos(ph), s * std::sin(ph), cz_, KOPPA_B * (N_b / N) / KPC_M);
        }
        std::vector<Pt> p = {{2, 0, 0}, {0.5, 0, 0}, {0, 0.3, 0}}; auto z = evalZ(c, p);
        double a_tot = KOPPA_B * N_b / KPC_M;
        check("V2a", "outside a shell Z = koppa_b N / r (0.5%)", std::fabs(z[0] / (a_tot / 2) - 1) < 5e-3, z[0] / (a_tot / 2) - 1);
        check("V2b", "inside a shell Z constant = koppa_b N / R (1%)", std::fabs(z[1] / a_tot - 1) < 1e-2 && std::fabs(z[2] / a_tot - 1) < 1e-2,
              std::fmax(std::fabs(z[1] / a_tot - 1), std::fabs(z[2] / a_tot - 1)));
    }
    {   // V3 uniform thin disc on axis
        Rng r(12); Cloud c; const int N = 200000; const double N_b = 1e67, a = 2.0;
        for (int i = 0; i < N; ++i) { double R = a * std::sqrt(r.u()), ph = 2 * PI * r.u(); push(c, R * std::cos(ph), R * std::sin(ph), 0, KOPPA_B * (N_b / N) / KPC_M); }
        std::vector<Pt> p = {{0, 0, 1.0}}; auto z = evalZ(c, p);
        double a_tot = KOPPA_B * N_b / KPC_M, an = 2 * a_tot / (a * a) * (std::sqrt(1 + a * a) - 1.0);
        check("V3", "uniform disc on axis", std::fabs(z[0] / an - 1) < 1e-2, z[0] / an - 1);
    }
    {   // V4 equalisation operator
        const int n = 400; std::vector<double> Zd(n), h(n - 1); Rng r(13);
        for (int i = 0; i < n; ++i) Zd[i] = 1e-6 * (1.0 + 0.5 * std::sin(i * 0.05)) + 1e-8 * r.u();
        for (int i = 0; i < n - 1; ++i) h[i] = 0.02 + 0.01 * std::sin(i * 0.1);
        auto z0 = equalise(Zd, h, 0.0), zi = equalise(Zd, h, 1e3), zm = equalise(Zd, h, 2.0);
        double mean = weighted_mean(Zd, h), d0 = 0, di = 0;
        for (int i = 0; i < n; ++i) { d0 = std::fmax(d0, std::fabs(z0[i] - Zd[i])); di = std::fmax(di, std::fabs(zi[i] - mean)); }
        double cons = std::fabs(integral(zm, h) - integral(Zd, h)) / std::fabs(integral(Zd, h));
        check("V4a", "lambda->0 is the identity", d0 < 1e-15, d0);
        check("V4b", "lambda >> sheath length approaches the mean (rel 1e-3)", di / mean < 1e-3, di / mean);
        check("V4c", "integral of Z ds conserved (1e-9)", cons < 1e-9, cons);
    }
    {   // V6 closure composition
        double Za = 3.1e-7, Zb = 2.2e-7, one = (1 + Za) * (1 + Zb) - 1, two = Za + Zb + Za * Zb;
        check("V6", "multiplicative composition identity", std::fabs(one - two) < 1e-12, one - two);
    }
    std::printf("  validation failures: %d\n\n", g_fail);
    if (g_fail) { std::printf("validation failed — field not used.\n"); return 1; }

    // ---------------- inputs ----------------
    auto arms = read_arms("../GD08_Milky_Way_Arm_Topology/mw_arms_data.js");
    std::string bjs = slurp("../GD09_Milky_Way_Baryon_Inventory/mw_baryons.js");
    if (arms.empty() || bjs.empty()) { std::printf("input files missing\n"); return 1; }
    const double N_bulge = read_count(bjs, "bulge_stellar").c + read_count(bjs, "gas_bulge").c;
    const double N_thin = read_count(bjs, "disc_thin").c, N_thick = read_count(bjs, "disc_thick").c;
    const double N_gas = read_count(bjs, "gas_disc_He").c;
    Row sc = read_count(bjs, "stars_cold"); const double frac_sc = (sc.hi - sc.lo) / (2 * sc.c);
    const double N_all = N_bulge + N_thin + N_thick + N_gas;
    std::printf("inputs: %zu arms ; N bulge %.3e thin %.3e thick %.3e gas %.3e ; sum %.3e\n", arms.size(), N_bulge, N_thin, N_thick, N_gas, N_all);
    int nn = 0; for (auto& a : arms) nn += (int)a.nodes.size();
    std::printf("ridge nodes: %d (all tiers)\n\n", nn);

    auto build = [&](uint64_t seed, std::vector<double>* sv, Cloud& bulge, Cloud& thick, Cloud& thin, Cloud& gas) {
        int nb = std::max(20000, (int)std::lround(NP_TOTAL * N_bulge / N_all)), nt = std::max(20000, (int)std::lround(NP_TOTAL * N_thin / N_all));
        int nk = std::max(15000, (int)std::lround(NP_TOTAL * N_thick / N_all)), ng = std::max(15000, (int)std::lround(NP_TOTAL * N_gas / N_all));
        bulge = make_bulge(seed + 1, nb, N_bulge, sv);
        thick = make_disc(seed + 2, nk, N_thick, 2.0, 0.90, 0.0, 20.0);
        thin  = make_disc(seed + 3, nt, N_thin, 2.6, 0.30, 0.0, 20.0);
        gas   = make_disc(seed + 4, ng, N_gas, 5.2, 0.10, 2.0, 19.0);
    };
    // arm overdensity: weights ~ 1 + (K-1) max_a exp(-d^2/2 sigma^2) on tiers 0,1; counts conserved.
    auto modulate = [&](Cloud C, double K) {
        if (K == 1.0) return C;
        std::vector<const Node*> nodes;
        for (auto& a : arms) for (auto& nd : a.nodes) if (nd.tier <= 1) nodes.push_back(&nd);
        std::vector<double> m(C.x.size()); double sa = 0, sm = 0;
#pragma omp parallel for schedule(static)
        for (long i = 0; i < (long)C.x.size(); ++i) {
            double best = 0;
            for (auto* nd : nodes) {
                double dx = C.x[i] - nd->x, dy = C.y[i] - nd->y, d2 = dx * dx + dy * dy;
                if (d2 < 9 * nd->sin * nd->sin) best = std::fmax(best, std::exp(-d2 / (2 * nd->sin * nd->sin)));
            }
            m[i] = 1 + (K - 1) * best;
        }
        for (size_t i = 0; i < m.size(); ++i) { sa += C.a[i]; sm += C.a[i] * m[i]; }
        for (size_t i = 0; i < m.size(); ++i) C.a[i] *= m[i] * sa / sm;
        return C;
    };

    std::vector<double> sv; Cloud bulge, thick, thin, gas;
    build(1000, &sv, bulge, thick, thin, gas);

    // ---------------- bulge: recursive displacement shells ----------------
    std::printf("== BULGE RECURSIVE SHELLS (exponential profile, h = 0.70/0.44/0.18 kpc) ==\n");
    {
        const double sb[] = {0.5, 1, 2, 3, 4, 6, 10}; const int NS = 7; const double hq = std::cbrt(0.70 * 0.44 * 0.18);
        std::vector<double> Nk(NS, 0);
        for (double s : sv) { for (int k = 0; k < NS; ++k) if (s <= sb[k]) { Nk[k] += N_bulge / sv.size(); break; } }
        std::printf("%-6s %-8s %-11s %-11s %-12s %-12s %-12s %-10s\n", "shell", "r_edge", "N_k", "koppa_k[m]", "cZ_add[m/s]", "cZ_mult[m/s]", "compounding", "dP/P");
        for (int j = 0; j < NS; ++j) {
            double r_m = sb[j] * hq * KPC_M, Zadd = 0, lsum = 0;
            for (int k = 0; k <= j; ++k) { double zk = KOPPA_B * Nk[k] / r_m; Zadd += zk; lsum += std::log1p(zk); }
            double Zmul = std::expm1(lsum), Nc = 0; for (int k = 0; k <= j; ++k) Nc += Nk[k];
            std::printf("%-6d %-8.3f %-11.3e %-11.3e %-12.3f %-12.3f %-12.3e %-10.3e\n", j + 1, sb[j] * hq, Nk[j], KOPPA_B * Nk[j], cz(Zadd), cz(Zmul),
                        (Zmul - Zadd) / Zadd, 4 * Zmul);
            (void)Nc;
        }
        std::printf("(r_edge = s x (hx hy hz)^(1/3) kpc ; exterior field of each shell koppa_k/r ; compounding = (Z_mult - Z_add)/Z_add)\n\n");
    }

    // ---------------- evaluation points ----------------
    std::vector<Pt> pts; const int GN = 129; const double GS = 0.25, GM = 16.0;
    const int off_grid = 0; for (int j = 0; j < GN; ++j) for (int i = 0; i < GN; ++i) pts.push_back({-GM + GS * i, -GM + GS * j, 0});
    const int off_ridge = (int)pts.size(); for (auto& a : arms) for (auto& nd : a.nodes) pts.push_back({nd.x, nd.y, 0});
    const int off_sun = (int)pts.size(); pts.push_back({0, R0, 0});
    const int NAZ = 48; const double ring_R[3] = {R0 - 0.5, R0, R0 + 0.5};
    const int off_ring = (int)pts.size();
    for (int rr = 0; rr < 3; ++rr) for (int j = 0; j < NAZ; ++j) { double ph = 2 * PI * (j + 0.5) / NAZ; pts.push_back({ring_R[rr] * std::sin(ph), ring_R[rr] * std::cos(ph), 0}); }
    const int off_sl = (int)pts.size(); const int NL = 36; const double dlist[5] = {2, 4, 6, 8, 10};
    for (int il = 0; il < NL; ++il) for (int id = 0; id < 5; ++id) { double l = 10.0 * il * DEG; pts.push_back({dlist[id] * std::sin(l), R0 - dlist[id] * std::cos(l), 0}); }
    std::printf("evaluation points: %zu\n", pts.size());

    Cloud fixedC = bulge; append(fixedC, thick);
    auto Zfix = evalZ(fixedC, pts);
    auto field_for = [&](double K) {
        Cloud v = thin; append(v, gas); v = modulate(v, K); return evalZ(v, pts);
    };
    auto Zv1 = field_for(1.0), Zv2 = field_for(ARM_CONTRAST);
    std::vector<double> Z1(pts.size()), Z2(pts.size());
    for (size_t i = 0; i < pts.size(); ++i) { Z1[i] = Zfix[i] + Zv1[i]; Z2[i] = Zfix[i] + Zv2[i]; }

    // seed-B realisation for the noise estimate (ridge + Sun + rings, contrast case)
    std::vector<Pt> sub(pts.begin() + off_ridge, pts.begin() + off_sl);
    double noise_rel = 0, noise_ms = 0;
    {
        Cloud b2, k2, t2, g2; build(5000, nullptr, b2, k2, t2, g2);
        Cloud A = b2; append(A, k2); Cloud V = t2; append(V, g2); V = modulate(V, ARM_CONTRAST); append(A, V);
        auto ZB = evalZ(A, sub); double s2 = 0, s1 = 0; int n = (int)sub.size();
        for (int i = 0; i < n; ++i) { double d = ZB[i] - Z2[off_ridge + i]; s2 += d * d; s1 += Z2[off_ridge + i] * Z2[off_ridge + i]; }
        noise_rel = std::sqrt(s2 / s1) / std::sqrt(2.0); noise_ms = cz(std::sqrt(s2 / n) / std::sqrt(2.0));
    }
    std::printf("Monte-Carlo noise (two seeds, ridge+Sun+rings): %.3f%% of Z ; %.2f m/s rms\n\n", 100 * noise_rel, noise_ms);

    // ---------------- C1 / C2 : rotation bridge ----------------
    const double sig_comb = std::sqrt(frac_sc * frac_sc + std::pow(2 * THETA0_ERR / THETA0, 2));
    const double vref2 = std::pow(THETA0 * 1000.0 / C_MS, 2);
    Cloud A1 = fixedC; { Cloud v = thin; append(v, gas); append(A1, v); }
    Cloud A2 = fixedC; { Cloud v = thin; append(v, gas); v = modulate(v, ARM_CONTRAST); append(A2, v); }
    double vc1 = rotation_bridge(A1, R0, 96), vc2 = rotation_bridge(A2, R0, 96);
    std::printf("== C1 baryon-only rotation bridge at R0 = %.2f kpc ==\n", R0);
    std::printf("reference (Theta0/c)^2 = %.4e  (Theta0 = %.0f +- %.0f km/s)\n", vref2, THETA0, THETA0_ERR);
    std::printf("dilute K=1      : v_c^2/c^2 = %.4e  v_c = %.1f km/s  ratio = %.3f\n", vc1, std::sqrt(vc1) * C_MS / 1000, vc1 / vref2);
    std::printf("dilute K=%.2f  : v_c^2/c^2 = %.4e  v_c = %.1f km/s  ratio = %.3f\n", ARM_CONTRAST, vc2, std::sqrt(vc2) * C_MS / 1000, vc2 / vref2);
    std::printf("criterion |ratio-1| <= %.3f (sigma_comb) : %s\n", sig_comb, std::fabs(vc2 / vref2 - 1) <= sig_comb ? "consistent" : "inconsistent");
    std::printf("excluded components (stellar halo, hot corona) are not in the sum above\n\n");

    // ---------------- sheath equalisation ----------------
    // node bookkeeping
    std::vector<int> armStart(arms.size()); { int k = 0; for (size_t a = 0; a < arms.size(); ++a) { armStart[a] = k; k += (int)arms[a].nodes.size(); } }
    auto solve_dZ = [&](const std::vector<double>& Zfield, int maxTier, double lam) {   // returns dZ per node (0 for non-members)
        std::vector<double> dZ(nn, 0.0);
        for (size_t a = 0; a < arms.size(); ++a) {
            std::vector<int> idx; for (size_t k = 0; k < arms[a].nodes.size(); ++k) if (arms[a].nodes[k].tier <= maxTier) idx.push_back((int)k);
            if (idx.size() < 2) continue;
            std::vector<double> Zd, h;
            for (size_t m = 0; m < idx.size(); ++m) {
                Zd.push_back(Zfield[off_ridge + armStart[a] + idx[m]]);
                if (m) { auto& p = arms[a].nodes[idx[m - 1]]; auto& q = arms[a].nodes[idx[m]]; h.push_back(std::hypot(q.x - p.x, q.y - p.y)); }
            }
            std::vector<double> Ze = lam > 1e5 ? std::vector<double>(Zd.size(), weighted_mean(Zd, h)) : equalise(Zd, h, lam);
            for (size_t m = 0; m < idx.size(); ++m) dZ[armStart[a] + idx[m]] = Ze[m] - Zd[m];
        }
        return dZ;
    };
    // nearest member node for each evaluation point (per tier set)
    auto nearest = [&](int maxTier) {
        std::vector<int> ni(pts.size(), -1); std::vector<double> nd2(pts.size(), 1e9);
#pragma omp parallel for schedule(static)
        for (long i = 0; i < (long)pts.size(); ++i) {
            double best = 1e9; int bi = -1, k = 0;
            for (auto& a : arms) for (auto& nd : a.nodes) {
                if (nd.tier <= maxTier) { double dx = pts[i].x - nd.x, dy = pts[i].y - nd.y, d2 = dx * dx + dy * dy; if (d2 < best) { best = d2; bi = k; } }
                ++k;
            }
            ni[i] = bi; nd2[i] = best;
        }
        return std::make_pair(ni, nd2);
    };
    std::vector<const Node*> flat; for (auto& a : arms) for (auto& nd : a.nodes) flat.push_back(&nd);
    auto applyEq = [&](const std::vector<double>& Zbase, const std::vector<double>& dZ, const std::pair<std::vector<int>, std::vector<double>>& nr) {
        std::vector<double> Ze = Zbase;
        for (size_t i = 0; i < pts.size(); ++i) {
            int k = nr.first[i]; if (k < 0) continue; double s = flat[k]->sin, g = std::exp(-nr.second[i] / (2 * s * s));
            Ze[i] += g * dZ[k];
        }
        return Ze;
    };
    auto nrA = nearest(1), nrB = nearest(2);

    // Sun in a sheath?
    { double dsun = std::sqrt(nrA.second[off_sun]); int k = nrA.first[off_sun];
      std::printf("Sun: nearest ridge node (tiers 0-1) is %s at %.3f kpc (sigma_in %.3f) ; taper g = %.3f\n\n", arms[flat[k]->arm].name.c_str(), dsun, flat[k]->sin,
                  std::exp(-nrA.second[off_sun] / (2 * flat[k]->sin * flat[k]->sin))); }

    // equalised fields for the scan (contrast case Z2) and the lambda -> infinity limit, tier sets A and B
    const int NCASE = NLAM + 1;                                  // lambda scan + infinity
    auto lam_of = [&](int c) { return c < NLAM ? LAMBDAS[c] : 1e6; };
    std::vector<std::vector<double>> ZeA(NCASE), ZeB(NCASE), dZA(NCASE), dZB(NCASE);
    for (int c = 0; c < NCASE; ++c) {
        dZA[c] = solve_dZ(Z2, 1, lam_of(c)); ZeA[c] = applyEq(Z2, dZA[c], nrA);
        dZB[c] = solve_dZ(Z2, 2, lam_of(c)); ZeB[c] = applyEq(Z2, dZB[c], nrB);
    }

    // C2 : rotation bridge through ring means with the equalised depth (finite difference, h = 0.5 kpc)
    auto ringmean = [&](const std::vector<double>& Z, int rr) { double s = 0; for (int j = 0; j < NAZ; ++j) s += Z[off_ring + rr * NAZ + j]; return s / NAZ; };
    auto vc_fd = [&](const std::vector<double>& Z) { return -R0 * (ringmean(Z, 2) - ringmean(Z, 0)) / (ring_R[2] - ring_R[0]); };
    double vfd1 = vc_fd(Z1), vfd2 = vc_fd(Z2);
    std::printf("== C2 mechanism: v_c^2/c^2 at R0 by ring finite difference (h = 0.5 kpc) ==\n");
    std::printf("check: FD vs analytic force, K=1: %.4e vs %.4e (%+.2f%%)\n", vfd1, vc1, 100 * (vfd1 / vc1 - 1));
    std::printf("%-22s %-14s %-10s %-10s %-14s\n", "case", "v_c^2/c^2", "v_c km/s", "ratio", "vs criterion");
    auto line = [&](const char* nm, double v) {
        std::printf("%-22s %-14.4e %-10.1f %-10.3f %s\n", nm, v, std::sqrt(std::fmax(v, 0)) * C_MS / 1000, v / vref2, std::fabs(v / vref2 - 1) <= sig_comb ? "consistent" : "inconsistent");
    };
    line("dilute K=1 (FD)", vfd1); line("dilute K=1.32 (FD)", vfd2);
    for (int c = 0; c < NCASE; ++c) { char nm[48]; if (c < NLAM) std::snprintf(nm, sizeof nm, "equalised A lam=%.1f", LAMBDAS[c]); else std::snprintf(nm, sizeof nm, "equalised A lam=inf"); line(nm, vc_fd(ZeA[c])); }
    std::printf("\n");

    // C3 emission-depth gradient at R0
    std::printf("== C3 emission-depth gradient at R0 ==\n");
    std::printf("c dZ/dR (dilute, analytic) = %.2f m/s per kpc = %.4f km/s per kpc  (Loeb 2022 theoretical estimate magnitude 0.024 km/s per kpc)\n\n",
                -C_MS * vc1 / R0, C_MS * vc1 / R0 / 1000);

    // ---------------- emission at depth ----------------
    const double ZS1 = Z1[off_sun], ZS2 = Z2[off_sun];
    std::printf("== EMISSION AT DEPTH ==\n");
    std::printf("Sun depth: cZ = %.1f m/s (K=1) ; %.1f m/s (K=%.2f) ; dP/P = 4Z = %.3e\n", cz(ZS1), cz(ZS2), ARM_CONTRAST, 4 * ZS2);
    {   // depth at characteristic places
        auto ring_m = [&](double R) { double s = 0; for (int j = 0; j < 24; ++j) { double ph = 2 * PI * (j + 0.5) / 24; s += 0; (void)ph; } return s; };
        (void)ring_m;
    }
    {   // depth at the Galactic centre and along the bulge major axis from the grid centre
        int ic = GN / 2; double zc = Z2[ic + GN * ic];
        std::printf("grid centre (Galactic centre): cZ = %.1f m/s (K=%.2f)\n", cz(zc), ARM_CONTRAST);
    }
    // arm statistics: depth contrast sheath vs interarm at the same radius is read from the profile file
    FILE* fr = std::fopen("gd10_ridge_profiles.csv", "w");
    std::fprintf(fr, "arm,node,tier,x,y,R,cZ_K1,cZ_K%.2f", ARM_CONTRAST);
    for (int c = 0; c < NCASE; ++c) { if (c < NLAM) std::fprintf(fr, ",cZ_eqA_lam%.1f", LAMBDAS[c]); else std::fprintf(fr, ",cZ_eqA_lamInf"); }
    for (int c = 0; c < NCASE; ++c) { if (c < NLAM) std::fprintf(fr, ",cZ_eqB_lam%.1f", LAMBDAS[c]); else std::fprintf(fr, ",cZ_eqB_lamInf"); }
    std::fprintf(fr, "\n");
    int k = 0;
    for (auto& a : arms) for (size_t i = 0; i < a.nodes.size(); ++i, ++k) {
        auto& nd = a.nodes[i]; std::fprintf(fr, "%s,%zu,%d,%.4f,%.4f,%.4f,%.3f,%.3f", a.name.c_str(), i, nd.tier, nd.x, nd.y, nd.R, cz(Z1[off_ridge + k]), cz(Z2[off_ridge + k]));
        for (int c = 0; c < NCASE; ++c) std::fprintf(fr, ",%.3f", cz(Z2[off_ridge + k] + dZA[c][k]));
        for (int c = 0; c < NCASE; ++c) std::fprintf(fr, ",%.3f", cz(Z2[off_ridge + k] + dZB[c][k]));
        std::fprintf(fr, "\n");
    }
    std::fclose(fr);

    // effect of equalisation on emission from arm nodes (tier 0/1 members), per lambda
    std::printf("\nEqualisation effect on emitters in the sheaths (tiers 0-1, contrast case): shift of cZ in m/s\n");
    std::printf("%-10s %-10s %-10s %-10s %-10s\n", "lambda", "max|dcZ|", "rms dcZ", "max up", "max down");
    for (int c = 0; c < NCASE; ++c) {
        double mx = 0, ss = 0, up = 0, dn = 0; int n = 0;
        for (int kk = 0; kk < nn; ++kk) if (flat[kk]->tier <= 1) { double d = cz(dZA[c][kk]); mx = std::fmax(mx, std::fabs(d)); ss += d * d; up = std::fmax(up, d); dn = std::fmin(dn, d); ++n; }
        if (c < NLAM) std::printf("%-10.1f", LAMBDAS[c]); else std::printf("%-10s", "inf");
        std::printf(" %-10.2f %-10.2f %-10.2f %-10.2f\n", mx, std::sqrt(ss / n), up, dn);
    }
    std::printf("(Monte-Carlo noise floor %.2f m/s ; effects below 3x this are not reported as signal)\n", noise_ms);

    // arm contrast effect alone
    {
        double mx = 0, ss = 0; int n = 0;
        for (int kk = 0; kk < nn; ++kk) if (flat[kk]->tier <= 1) { double d = cz(Z2[off_ridge + kk] - Z1[off_ridge + kk]); mx = std::fmax(mx, std::fabs(d)); ss += d * d; ++n; }
        std::printf("arm baryon overdensity K=%.2f alone: sheath cZ shift max %.2f m/s, rms %.2f m/s\n", ARM_CONTRAST, mx, std::sqrt(ss / n));
    }

    // sightlines
    FILE* fs = std::fopen("gd10_sightlines.csv", "w");
    std::fprintf(fs, "l_deg,d_kpc,x,y,cz_pair_K1,cz_pair_K%.2f", ARM_CONTRAST);
    for (int c = 0; c < NCASE; ++c) { if (c < NLAM) std::fprintf(fs, ",eqA_lam%.1f", LAMBDAS[c]); else std::fprintf(fs, ",eqA_lamInf"); }
    std::fprintf(fs, "\n");
    auto pair = [&](double Ze, double Zo) { return C_MS * ((1 + Ze) / (1 + Zo) - 1); };
    double max_eff = 0;
    for (int il = 0; il < NL; ++il) for (int id = 0; id < 5; ++id) {
        int i = off_sl + il * 5 + id;
        std::fprintf(fs, "%d,%.0f,%.3f,%.3f,%.2f,%.2f", 10 * il, dlist[id], pts[i].x, pts[i].y, pair(Z1[i], ZS1), pair(Z2[i], ZS2));
        for (int c = 0; c < NCASE; ++c) {
            double v = pair(ZeA[c][i], ZeA[c][off_sun]); std::fprintf(fs, ",%.2f", v);
            max_eff = std::fmax(max_eff, std::fabs(v - pair(Z2[i], ZS2)));
        }
        std::fprintf(fs, "\n");
    }
    std::fclose(fs);
    std::printf("sightline emitters: largest change of the pair shift from equalisation = %.2f m/s\n", max_eff);

    // pair-shift range across the sample (dilute contrast case)
    {
        double lo = 1e9, hi = -1e9;
        for (int i = 0; i < NL * 5; ++i) { double v = pair(Z2[off_sl + i], ZS2); lo = std::fmin(lo, v); hi = std::fmax(hi, v); }
        std::printf("pair shift of emitters 2-10 kpc from the Sun (contrast case): %.1f to %.1f m/s (Gaia RV zero-point scatter ~300 m/s)\n", lo, hi);
    }

    // viewer data: coarse maps (every 2nd grid point) of cZ for four cases
    {
        FILE* fj = std::fopen("mw_displacement.js", "w");
        const int step = 2, M = (GN - 1) / step + 1;
        std::fprintf(fj, "// Generated by gd10_displacement_field.cpp. cZ in m/s at the Galactic plane; x,y in kpc.\n");
        std::fprintf(fj, "window.MW_DEPTH={n:%d,half:%.1f,sun:[0,%.2f],cases:[\n", M, GM, R0);
        auto emit = [&](const char* name, const std::vector<double>& Z, bool last) {
            std::fprintf(fj, "{name:\"%s\",v:[", name);
            for (int j = 0; j < GN; j += step) for (int i = 0; i < GN; i += step) std::fprintf(fj, "%s%.1f", (i == 0 && j == 0) ? "" : ",", cz(Z[off_grid + j * GN + i]));
            std::fprintf(fj, "]}%s\n", last ? "" : ",");
        };
        emit("dilute, no arm contrast", Z1, false);
        emit("dilute, arm contrast 1.32", Z2, false);
        emit("equalised along sheaths, lambda 2 kpc", ZeA[2], false);
        emit("equalised along sheaths, lambda 8 kpc", ZeA[4], true);
        std::fprintf(fj, "]};\n"); std::fclose(fj);
    }
    std::printf("\nwrote gd10_ridge_profiles.csv gd10_sightlines.csv mw_displacement.js\n");
    return 0;
}
