// =====================================================================
//  GD12 : displacement pressure by volume — shell depth, macro-shells, competition, emission depth
//  ---------------------------------------------------------------------
//  f(k) = V / (4 pi k^2 l_P^3),  V = N V_p,  k = r / l_P   (displaced volume per shell volume = pitches shifted)
//  f_total(x) = f_amb + sum_i f_i(x) ;  for distributed baryons sum_i f_i = (V_p / l_P) Theta_tilde(x)
//  NO TWEAKING: nothing is set, changed or implied after a result. See PROMPT.md.
//
//  Inputs: GD08 mw_arms_data.js, GD09 mw_baryons.js. Build: cl /std:c++20 /EHsc /O2 /openmp /I Engine/include gd12_pressure_by_volume.cpp
//  Run from this folder. Writes: gd12_ridge_metrics.csv mw_pressure.js
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
#include <array>
#include <sdt/laws.hpp>

namespace {

using namespace sdt::laws;
constexpr double PI = std::numbers::pi, DEG = PI / 180.0;
const double PC_M = measured::AU * 648000.0 / PI, KPC_M = 1000.0 * PC_M;
const double LP = measured::l_P, V_P = law_IV::V_disp_p;
const double N_SUN = bridge::N_baryons(bridge::koppa_Sun);
constexpr double EPS = 0.03;                                       // Plummer softening [kpc]
constexpr int NP_TOTAL = 1000000;
constexpr double ARM_CONTRAST = 1.32, R0 = 8.15;
const double A_F = (V_P / LP) / (4 * PI * KPC_M * KPC_M);          // raw kernel sum (kpc^-2 units) -> pitches

std::string slurp(const std::string& fn) { std::ifstream f(fn, std::ios::binary); std::stringstream ss; ss << f.rdbuf(); return ss.str(); }
struct Node { double x, y, sin, sz; int tier; int arm; double R; };
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
            ++p; a.nodes.push_back({v[0], v[1], v[2], v[3], (int)std::lround(v[4]), (int)arms.size(), std::hypot(v[0], v[1])});
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
    r.c = std::strtod(js.c_str() + p, &end); p = end - js.c_str() + 1;
    r.hi = std::strtod(js.c_str() + p, &end);
    return r;
}
struct Rng {
    std::mt19937_64 g; explicit Rng(uint64_t s) : g(s) {}
    double u() { return ((g() >> 11) + 0.5) * (1.0 / 9007199254740992.0); }
    double expo(double mean) { return -mean * std::log(u()); }
};
struct Cloud { std::vector<double> x, y, z, w; };
void push(Cloud& C, double x, double y, double z, double w) { C.x.push_back(x); C.y.push_back(y); C.z.push_back(z); C.w.push_back(w); }
void append(Cloud& A, const Cloud& B) {
    A.x.insert(A.x.end(), B.x.begin(), B.x.end()); A.y.insert(A.y.end(), B.y.begin(), B.y.end());
    A.z.insert(A.z.end(), B.z.begin(), B.z.end()); A.w.insert(A.w.end(), B.w.begin(), B.w.end());
}
constexpr double HX = 0.70, HY = 0.44, HZ = 0.18, BANG = 27.0 * DEG;
Cloud make_bulge(uint64_t seed, int Np, double N) {
    Rng r(seed); Cloud C; const double sa = std::sin(BANG), ca = std::cos(BANG);
    for (int i = 0; i < Np; ++i) {
        double s; do { s = r.expo(1) + r.expo(1) + r.expo(1); } while (s > 10.0);
        double cz = 2 * r.u() - 1, ph = 2 * PI * r.u(), sz = std::sqrt(1 - cz * cz);
        double X = HX * s * sz * std::cos(ph), Y = HY * s * sz * std::sin(ph), Zc = HZ * s * cz;
        push(C, X * sa + Y * ca, X * ca - Y * sa, Zc, N / Np);
    }
    return C;
}
Cloud make_disc(uint64_t seed, int Np, double N, double Rd, double zd, double Rmin, double Rmax) {
    Rng r(seed); Cloud C;
    for (int i = 0; i < Np; ++i) {
        double R; do { R = r.expo(Rd) + r.expo(Rd); } while (R < Rmin || R > Rmax);
        double ph = 2 * PI * r.u(), z = (r.u() < 0.5 ? -1 : 1) * r.expo(zd);
        push(C, R * std::cos(ph), R * std::sin(ph), z, N / Np);
    }
    return C;
}
// analytic densities [baryons per kpc^3], by component: 0 bulge, 1 thick, 2 thin, 3 gas (K = 1)
struct Dens { double Nb, Nk, Nt, Ng; };
double erl_frac(double Rd, double a, double b) { return (1 + a / Rd) * std::exp(-a / Rd) - (1 + b / Rd) * std::exp(-b / Rd); }
double n_comp(const Dens& D, double x, double y, double z, int c) {
    static const double Ptr = std::exp(-10.0) * (1 + 10 + 50);
    static const double Ft = erl_frac(2.6, 0, 20), Fk = erl_frac(2.0, 0, 20), Fg = erl_frac(5.2, 2, 19);
    const double R = std::hypot(x, y), az = std::fabs(z);
    switch (c) {
    case 0: { const double sa = std::sin(BANG), ca = std::cos(BANG), X = x * sa + y * ca, Y = x * ca - y * sa;
        const double s = std::sqrt(X * X / (HX * HX) + Y * Y / (HY * HY) + z * z / (HZ * HZ));
        return D.Nb / (8 * PI * HX * HY * HZ * (1 - Ptr)) * std::exp(-s); }
    case 1: return D.Nk * std::exp(-R / 2.0 - az / 0.90) / (Fk * 4 * PI * 2.0 * 2.0 * 0.90);
    case 2: return D.Nt * std::exp(-R / 2.6 - az / 0.30) / (Ft * 4 * PI * 2.6 * 2.6 * 0.30);
    default: return (R >= 2 && R <= 19) ? D.Ng * std::exp(-R / 5.2 - az / 0.10) / (Fg * 4 * PI * 5.2 * 5.2 * 0.10) : 0.0;
    }
}
double n_total(const Dens& D, double x, double y, double z) { return n_comp(D, x, y, z, 0) + n_comp(D, x, y, z, 1) + n_comp(D, x, y, z, 2) + n_comp(D, x, y, z, 3); }

struct Pt { double x, y, z; };
struct FG { std::vector<double> th, gx, gy, gz; };               // raw sums: sum w/(d^2+e^2) and its gradient
FG evalFG(const Cloud& C, const std::vector<Pt>& pts) {
    const size_t n = C.x.size(), m = pts.size(); const double e2 = EPS * EPS;
    FG f; f.th.assign(m, 0); f.gx.assign(m, 0); f.gy.assign(m, 0); f.gz.assign(m, 0);
#pragma omp parallel for schedule(static)
    for (long i = 0; i < (long)m; ++i) {
        double th = 0, gx = 0, gy = 0, gz = 0; const double px = pts[i].x, py = pts[i].y, pz = pts[i].z;
        for (size_t k = 0; k < n; ++k) {
            double dx = px - C.x[k], dy = py - C.y[k], dz = pz - C.z[k], d2 = dx * dx + dy * dy + dz * dz + e2, inv = 1.0 / d2, w = C.w[k];
            th += w * inv; double t = -2.0 * w * inv * inv; gx += t * dx; gy += t * dy; gz += t * dz;
        }
        f.th[i] = th; f.gx[i] = gx; f.gy[i] = gy; f.gz[i] = gz;
    }
    return f;
}
// Plummer-softened 1/d^2 sum under-counts by n eps pi/2 per unit (1/4pi): raw_true = raw_sum + 2 pi^2 n eps (and its gradient).
double soft_corr(double raw, double n_kpc3) { return raw + 2 * PI * PI * n_kpc3 * EPS; }
void soft_corr_comp(const Dens& D, int c, const std::vector<Pt>& pts, FG& f) {
    const double h = 0.02;
    for (size_t i = 0; i < pts.size(); ++i) {
        double x = pts[i].x, y = pts[i].y, z = pts[i].z, n = n_comp(D, x, y, z, c);
        f.th[i] = soft_corr(f.th[i], n);
        f.gx[i] += 2 * PI * PI * EPS * (n_comp(D, x + h, y, z, c) - n_comp(D, x - h, y, z, c)) / (2 * h);
        f.gy[i] += 2 * PI * PI * EPS * (n_comp(D, x, y + h, z, c) - n_comp(D, x, y - h, z, c)) / (2 * h);
        f.gz[i] += 2 * PI * PI * EPS * (n_comp(D, x, y, z + h, c) - n_comp(D, x, y, z - h, c)) / (2 * h);
    }
}
void addFG(FG& a, const FG& b) { for (size_t i = 0; i < a.th.size(); ++i) { a.th[i] += b.th[i]; a.gx[i] += b.gx[i]; a.gy[i] += b.gy[i]; a.gz[i] += b.gz[i]; } }

double theta_rays_raw(const Dens& D, double x, double y, double z, int ND, double step, double Lmax) {       // (1/4pi) sum -> mean column [baryons/kpc^2]
    double tot = 0;
#pragma omp parallel for reduction(+ : tot) schedule(static)
    for (int i = 0; i < ND; ++i) {
        double cz = 1 - 2 * (i + 0.5) / ND, sz = std::sqrt(1 - cz * cz), ph = PI * (1 + std::sqrt(5.0)) * (i + 0.5);
        double dx = sz * std::cos(ph), dy = sz * std::sin(ph), dz = cz, col = 0;
        for (double l = 0.5 * step; l < Lmax; l += step) col += n_total(D, x + l * dx, y + l * dy, z + l * dz) * step;
        tot += col;
    }
    return 4 * PI * tot / ND;                                    // raw = 4 pi x mean column
}

// ---- Amendment 3: deterministic f and gradient from fixed-direction ray quadrature on the analytic densities ----
struct ArmGrid {
    int n = 0; double half = 20.0, h = 0.05; std::vector<float> best; double ft = 1, fg = 1;
    double at(double x, double y) const {
        double gx = (x + half) / h, gy = (y + half) / h; int i = (int)std::floor(gx), j = (int)std::floor(gy);
        if (i < 0 || j < 0 || i >= n - 1 || j >= n - 1) return 0.0;
        double tx = gx - i, ty = gy - j;
        return (1 - ty) * ((1 - tx) * best[(size_t)j * n + i] + tx * best[(size_t)j * n + i + 1]) + ty * ((1 - tx) * best[(size_t)(j + 1) * n + i] + tx * best[(size_t)(j + 1) * n + i + 1]);
    }
};
ArmGrid build_arm_grid(const std::vector<Arm>& arms, const Dens& D, double K) {
    ArmGrid G; G.n = (int)std::lround(2 * G.half / G.h) + 1; G.best.assign((size_t)G.n * G.n, 0.f);
    std::vector<const Node*> nodes; for (auto& a : arms) for (auto& nd : a.nodes) if (nd.tier <= 1) nodes.push_back(&nd);
#pragma omp parallel for schedule(static)
    for (long j = 0; j < G.n; ++j) for (int i = 0; i < G.n; ++i) {
        double x = -G.half + G.h * i, y = -G.half + G.h * j, best = 0;
        for (auto* nd : nodes) { double dx = x - nd->x, dy = y - nd->y, d2 = dx * dx + dy * dy; if (d2 < 9 * nd->sin * nd->sin) best = std::fmax(best, std::exp(-d2 / (2 * nd->sin * nd->sin))); }
        G.best[(size_t)j * G.n + i] = (float)best;
    }
    static const double Ft = erl_frac(2.6, 0, 20), Fg = erl_frac(5.2, 2, 19);
    double It0 = 0, It = 0, Ig0 = 0, Ig = 0;
    for (int j = 0; j < G.n; ++j) for (int i = 0; i < G.n; ++i) {
        double x = -G.half + G.h * i, y = -G.half + G.h * j, R = std::hypot(x, y), b = G.best[(size_t)j * G.n + i];
        if (R <= 20.0) { double St = D.Nt * std::exp(-R / 2.6) / (Ft * 2 * PI * 2.6 * 2.6); It0 += St; It += St * (1 + (K - 1) * b); }
        if (R >= 2.0 && R <= 19.0) { double Sg = D.Ng * std::exp(-R / 5.2) / (Fg * 2 * PI * 5.2 * 5.2); Ig0 += Sg; Ig += Sg * (1 + (K - 1) * b); }
    }
    G.ft = It0 / It; G.fg = Ig0 / Ig; return G;
}
struct Dirs { std::vector<double> x, y, z; };
Dirs make_dirs(int ND) {
    Dirs d; for (int i = 0; i < ND; ++i) { double cz = 1 - 2 * (i + 0.5) / ND, sz = std::sqrt(1 - cz * cz), ph = PI * (1 + std::sqrt(5.0)) * (i + 0.5); d.x.push_back(sz * std::cos(ph)); d.y.push_back(sz * std::sin(ph)); d.z.push_back(cz); }
    return d;
}
double n_arm_total(const Dens& D, const ArmGrid& G, double K, double x, double y, double z) {
    double m = 1 + (K - 1) * G.at(x, y);
    return n_comp(D, x, y, z, 0) + n_comp(D, x, y, z, 1) + n_comp(D, x, y, z, 2) * m * G.ft + n_comp(D, x, y, z, 3) * m * G.fg;
}
double f_ray(const Dens& D, const ArmGrid& G, double K, const Dirs& DR, double x, double y, double z) {   // pitches
    const size_t ND = DR.x.size(); double tot = 0;
    for (size_t i = 0; i < ND; ++i) {
        double dx = DR.x[i], dy = DR.y[i], dz = DR.z[i], col = 0, l;
        for (l = 0.0125; l < 1.0; l += 0.025) col += n_arm_total(D, G, K, x + l * dx, y + l * dy, z + l * dz) * 0.025;
        for (l = 1.025; l < 4.0; l += 0.05) col += n_arm_total(D, G, K, x + l * dx, y + l * dy, z + l * dz) * 0.05;
        for (l = 4.075; l < 40.0; l += 0.15) col += n_arm_total(D, G, K, x + l * dx, y + l * dy, z + l * dz) * 0.15;
        tot += col;
    }
    return A_F * 4 * PI * tot / ND;
}

int g_fail = 0;
void check(const char* id, const char* what, bool ok, double v) {
    std::printf("  [%s] %s : %s  (%.3e)\n", ok ? "PASS" : "FAIL", id, what, v);
    if (!ok) ++g_fail;
}
// f(k) for body volume V
double f_of_k(double V, double k) { return V / (4 * PI * k * k * LP * LP * LP); }
struct Macro { double k0, m, fc, ff, mean, rel, grad_per_m; };
Macro macro_shell(double V, double r, int n = 100) {
    Macro s; s.k0 = r / LP; s.m = s.k0 / n; s.fc = f_of_k(V, s.k0);
    s.rel = 2.0 * n / s.k0 + (double)n * n / (s.k0 * s.k0);          // f_c/f_f - 1, analytic
    s.ff = s.fc / (1.0 + s.rel);
    s.mean = 0.5 * (s.fc + s.ff);                                    // difference below double resolution; exact mean = f at the macro-shell centre to O(rel^2)
    s.grad_per_m = -s.fc * s.rel / (1.0 + s.rel) / (n * LP);
    return s;
}

} // namespace

int main() {
    std::printf("=================================================================\n");
    std::printf(" GD12 DISPLACEMENT PRESSURE BY VOLUME   (NO TWEAKING; nothing matched)\n");
    std::printf("=================================================================\n");
    const double N_sh = law_I::N, R_CMB = law_I::R_CMB, S_bd = law_I::S_boundary;
    const double n_gamma = bridge::release_acoustics::photon_count(measured::T_CMB);
    const double n_b0 = bridge::release_acoustics::eta_bbn_deuterium * n_gamma;
    const double F_AMB = n_b0 * V_P * N_sh;
    std::printf("l_P = %.6e m ; V_p = %.4e m^3 ; N = %.4e ; N_Sun = %.4e\n", LP, V_P, N_sh, N_SUN);
    std::printf("ambient (uniform): n_b0 = eta n_gamma = %.4e x %.4e = %.4e m^-3 (eta is a BBN input shared with other chains) ; f_amb = n_b0 V_p N = %.4e pitches\n\n",
                bridge::release_acoustics::eta_bbn_deuterium, n_gamma, n_b0, F_AMB);

    // ---------------- A. shell depth and macro-shells ----------------
    std::printf("== A. SHELL DEPTH AND 100-SHELL MACRO-SHELLS (one body each) ==\n");
    const double V_sun = N_SUN * V_P, N_earth = bridge::N_baryons(bridge::koppa_Earth), V_earth = N_earth * V_P;
    std::printf("body volumes: Sun %.4e m^3 (N %.4e) ; Earth %.4e m^3 (N %.4e, from koppa_Earth)\n", V_sun, N_SUN, V_earth, N_earth);
    struct Case { const char* body; double V; const char* lab; double r; };
    const double N_gal_guess = 7.815e67 + 4.995e63; // used only for table rows in kpc: replaced by the exact count after inputs are read
    (void)N_gal_guess;
    std::printf("%-8s %-10s %-11s %-11s %-12s %-12s %-10s %-12s\n", "body", "r", "k = r/l_P", "macro count", "f close", "f far", "rel step", "grad[/m]");
    const Case rows[] = {{"Earth", V_earth, "1 m", 1.0}, {"Earth", V_earth, "R_Earth", bridge::R_Earth}, {"Sun", V_sun, "R_Sun", measured::R_Sun},
                         {"Sun", V_sun, "1 AU", measured::AU}, {"Sun", V_sun, "1 pc", PC_M}};
    for (auto& c : rows) { Macro s = macro_shell(c.V, c.r);
        std::printf("%-8s %-10s %-11.3e %-11.3e %-12.4e %-12.4e %-10.2e %-12.3e\n", c.body, c.lab, s.k0, s.m, s.fc, s.ff, s.rel, s.grad_per_m); }

    // ---------------- validation ----------------
    std::printf("\n== INSTRUMENT VALIDATION ==\n");
    {   double md = 0, mv = 0;
        for (double k0 : {1e3, 1e4, 1e5}) { Macro s = macro_shell(V_sun, k0 * LP);
            md = std::fmax(md, std::fabs(s.rel - (std::pow(1 + 100.0 / k0, 2) - 1)) / s.rel); }
        for (double r : {1.0, 6.4e6, 1.5e11, 3.1e16, 2.5e20}) { double k0 = r / LP;
            mv = std::fmax(mv, std::fabs(f_of_k(V_sun, k0) * 4 * PI * k0 * k0 * LP * LP * LP / V_sun - 1)); }
        check("V1", "macro-shell relative step 200/k0 + 1e4/k0^2 equals (1 + 100/k0)^2 - 1 at k0 = 1e3, 1e4, 1e5 (1e-12)", md < 1e-12, md);
        check("V2", "volume conservation: f(k) x shell volume = V at every depth (1e-12)", mv < 1e-12, mv); }
    {   // V3 Apollonius: two bodies on a line
        double D = measured::AU, ratio = std::sqrt(V_earth / V_sun), x_closed = D * ratio / (1 + ratio);          // from the smaller body
        double lo = 1e3, hi = D - 1e3; for (int it = 0; it < 200; ++it) { double mid = 0.5 * (lo + hi); double fa = f_of_k(V_earth, mid / LP), fb = f_of_k(V_sun, (D - mid) / LP); if (fa > fb) lo = mid; else hi = mid; }
        check("V3", "meeting point of two bodies: numerical root equals the closed form (1e-9)", std::fabs(0.5 * (lo + hi) / x_closed - 1) < 1e-9, 0.5 * (lo + hi) / x_closed - 1); }
    {   // V4 mean column on a uniform ball (softening corrected), V5 gradient kernel
        Rng r(31); Cloud ball; const int N = 1000000; const double Nb = 1e60;
        for (int i = 0; i < N; ++i) { double rr = std::cbrt(r.u()), cz = 2 * r.u() - 1, ph = 2 * PI * r.u(), s = std::sqrt(1 - cz * cz); push(ball, rr * s * std::cos(ph), rr * s * std::sin(ph), rr * cz, Nb / N); }
        std::vector<Pt> q = {{0, 0, 0}, {0.6, 0, 0}}; FG h = evalFG(ball, q);
        double n_k = Nb / (4.0 / 3.0 * PI), d = 0.6, cc = std::sqrt(1 - d * d);
        auto raw_true = [&](double dd) { double c2 = 1 - dd * dd; return 4 * PI * n_k * (0.5 + c2 / (2 * dd) * std::asinh(dd / std::sqrt(c2))); };
        double raw0 = soft_corr(h.th[0], n_k), raw1 = soft_corr(h.th[1], n_k), an0 = 4 * PI * n_k * 1.0, an1 = raw_true(d); (void)cc;
        check("V4a", "mean column at the ball centre, softening corrected (0.5%)", std::fabs(raw0 / an0 - 1) < 5e-3, raw0 / an0 - 1);
        check("V4b", "mean column at d = 0.6 a, closed form, softening corrected (0.5%)", std::fabs(raw1 / an1 - 1) < 5e-3, raw1 / an1 - 1);
        double hh = 1e-4, gan = (raw_true(d + hh) - raw_true(d - hh)) / (2 * hh);
        std::vector<Pt> dirs; { Rng rd(77); for (int i = 0; i < 400; ++i) { double cz = 2 * rd.u() - 1, ph = 2 * PI * rd.u(), sz = std::sqrt(1 - cz * cz); dirs.push_back({d * sz * std::cos(ph), d * sz * std::sin(ph), d * cz}); } }
        FG hg = evalFG(ball, dirs); double mean_r = 0;
        for (size_t i = 0; i < dirs.size(); ++i) mean_r += (hg.gx[i] * dirs[i].x + hg.gy[i] * dirs[i].y + hg.gz[i] * dirs[i].z) / d;
        mean_r /= dirs.size();
        check("V5", "radial gradient, 400-direction mean at d = 0.6 a, against the derivative of the closed form (2%)", std::fabs(mean_r / gan - 1) < 2e-2, mean_r / gan - 1);
    }
    std::printf("  validation failures so far: %d\n\n", g_fail);
    if (g_fail) { std::printf("validation failed — fields not used.\n"); return 1; }

    // ---------------- B. Earth in the Sun's gradient ----------------
    std::printf("== B. EARTH IN THE SUN'S GRADIENT (printed as computed; nothing compared) ==\n");
    {
        const double D = measured::AU, Re = bridge::R_Earth;
        double f_sun_at_earth = f_of_k(V_sun, D / LP), f_earth_surf = f_of_k(V_earth, Re / LP), f_earth_at_AU = f_of_k(V_earth, D / LP);
        double g_sun = 2 * f_sun_at_earth / D, g_earth = 2 * f_earth_surf / Re;
        double ratio = std::sqrt(V_earth / V_sun), x_m = D * ratio / (1 + ratio);
        std::printf("f_Sun at the Earth (1 AU)        = %.4e pitches ; gradient 2f/r = %.4e per m (points toward the Sun)\n", f_sun_at_earth, g_sun);
        std::printf("f_Earth at the Earth's surface   = %.4e pitches ; gradient 2f/r = %.4e per m (points toward the Earth's centre)\n", f_earth_surf, g_earth);
        std::printf("f_Earth / f_Sun at the Earth's surface = %.3e ; |grad f_Sun| / |grad f_Earth| there = %.3e\n", f_earth_surf / f_sun_at_earth, g_sun / g_earth);
        std::printf("meeting surface (f_Earth = f_Sun) on the Sun-Earth line: %.4e m from the Earth (%.2f R_Earth) ; shell depth %.3e ; pressure there = f_Earth + f_Sun = %.4e pitches\n",
                    x_m, x_m / Re, x_m / LP, f_of_k(V_earth, x_m / LP) + f_of_k(V_sun, (D - x_m) / LP));
        std::printf("total at the Earth's surface = f_amb + f_Earth + f_Sun = %.4e pitches (ambient share %.2e)\n", F_AMB + f_earth_surf + f_sun_at_earth, F_AMB / (F_AMB + f_earth_surf + f_sun_at_earth));
        (void)f_earth_at_AU;
    }

    // ---------------- inputs ----------------
    auto arms = read_arms("../GD08_Milky_Way_Arm_Topology/mw_arms_data.js");
    std::string bjs = slurp("../GD09_Milky_Way_Baryon_Inventory/mw_baryons.js");
    if (arms.empty() || bjs.empty()) { std::printf("input files missing\n"); return 1; }
    Dens D{read_count(bjs, "bulge_stellar").c + read_count(bjs, "gas_bulge").c, read_count(bjs, "disc_thick").c, read_count(bjs, "disc_thin").c, read_count(bjs, "gas_disc_He").c};
    const double N_sgr = read_count(bjs, "smbh").c, N_all = D.Nb + D.Nk + D.Nt + D.Ng;
    std::printf("\ninputs: %zu arms ; N bulge %.3e thick %.3e thin %.3e gas %.3e ; sum %.4e ; Sgr A* %.3e (mass-equivalent)\n", arms.size(), D.Nb, D.Nk, D.Nt, D.Ng, N_all, N_sgr);
    int nn = 0; for (auto& a : arms) nn += (int)a.nodes.size();

    // galaxy rows of table A (exact counts)
    {
        const double N_gal = N_all + N_sgr, V_gal = N_gal * V_P, r1 = std::sqrt(V_gal / (4 * PI * LP));
        std::printf("\nGalaxy (spherical-equivalent, V = %.4e m^3):\n%-10s %-11s %-11s %-12s %-12s %-10s %-12s\n", V_gal, "r", "k = r/l_P", "macro count", "f close", "f far", "rel step", "grad[/m]");
        for (auto rr : std::vector<std::pair<const char*, double>>{{"1 pc", PC_M}, {"1 kpc", KPC_M}, {"8.15 kpc", 8.15 * KPC_M}, {"15 kpc", 15 * KPC_M}, {"r_1", r1}, {"R_CMB", R_CMB}}) {
            Macro s = macro_shell(V_gal, rr.second); std::printf("%-10s %-11.3e %-11.3e %-12.4e %-12.4e %-10.2e %-12.3e\n", rr.first, s.k0, s.m, s.fc, s.ff, s.rel, s.grad_per_m); }
        std::printf("r_1 = %.3e m = %.1f kpc (shell shift one pitch, f = 1) ; macro-shells from the Galactic centre to the Sun: %.3e ; to the Clearing: %.3e (S = 4 pi N^2 = %.3e)\n",
                    r1, r1 / KPC_M, 8.15 * KPC_M / LP / 100, R_CMB / LP / 100, S_bd);
        std::printf("literal enumeration of macro-shells is not possible; the closed form f(k) is exact for any grouping of shells, so the macro-shell values above are exact.\n");
    }

    auto build = [&](uint64_t seed, Cloud& bulge, Cloud& thick, Cloud& thin, Cloud& gas) {
        int nb = std::max(20000, (int)std::lround(NP_TOTAL * D.Nb / N_all)), nt = std::max(20000, (int)std::lround(NP_TOTAL * D.Nt / N_all));
        int nk = std::max(15000, (int)std::lround(NP_TOTAL * D.Nk / N_all)), ng = std::max(15000, (int)std::lround(NP_TOTAL * D.Ng / N_all));
        bulge = make_bulge(seed + 1, nb, D.Nb); thick = make_disc(seed + 2, nk, D.Nk, 2.0, 0.90, 0.0, 20.0);
        thin = make_disc(seed + 3, nt, D.Nt, 2.6, 0.30, 0.0, 20.0); gas = make_disc(seed + 4, ng, D.Ng, 5.2, 0.10, 2.0, 19.0);
    };
    auto modulate = [&](Cloud C, double K) {
        if (K == 1.0) return C;
        std::vector<const Node*> nodes; for (auto& a : arms) for (auto& nd : a.nodes) if (nd.tier <= 1) nodes.push_back(&nd);
        std::vector<double> m(C.x.size()); double sa = 0, sm = 0;
#pragma omp parallel for schedule(static)
        for (long i = 0; i < (long)C.x.size(); ++i) {
            double best = 0;
            for (auto* nd : nodes) { double dx = C.x[i] - nd->x, dy = C.y[i] - nd->y, d2 = dx * dx + dy * dy; if (d2 < 9 * nd->sin * nd->sin) best = std::fmax(best, std::exp(-d2 / (2 * nd->sin * nd->sin))); }
            m[i] = 1 + (K - 1) * best;
        }
        for (size_t i = 0; i < m.size(); ++i) { sa += C.w[i]; sm += C.w[i] * m[i]; }
        for (size_t i = 0; i < m.size(); ++i) C.w[i] *= m[i] * sa / sm;
        return C;
    };

    // ---------------- evaluation points ----------------
    std::vector<Pt> pts; const int GN = 65; const double GS = 0.5, GM = 16.0;
    const int off_grid = 0; for (int j = 0; j < GN; ++j) for (int i = 0; i < GN; ++i) pts.push_back({-GM + GS * i, -GM + GS * j, 0});
    const int off_ridge = (int)pts.size(); for (auto& a : arms) for (auto& nd : a.nodes) pts.push_back({nd.x, nd.y, 0});
    const int off_sun = (int)pts.size(); pts.push_back({0, R0, 0});
    const int off_org = (int)pts.size(); pts.push_back({0, 0, 0});
    const int NAZ = 48, NRING = 33; const int off_ring = (int)pts.size();
    for (int rr = 0; rr < NRING; ++rr) for (int j = 0; j < NAZ; ++j) { double R = 1.0 + 0.5 * rr, ph = 2 * PI * (j + 0.5) / NAZ; pts.push_back({R * std::sin(ph), R * std::cos(ph), 0}); }
    const int off_sl = (int)pts.size(); const int NL = 36; const double dlist[5] = {2, 4, 6, 8, 10};
    for (int il = 0; il < NL; ++il) for (int id = 0; id < 5; ++id) { double l = 10.0 * il * DEG; pts.push_back({dlist[id] * std::sin(l), R0 - dlist[id] * std::cos(l), 0}); }
    std::printf("\nevaluation points: %zu\n", pts.size());

    // components, K = 1.32 (static disc as seen) and K = 1 (no arm contrast) for the arm term
    struct Comps { FG sgr, bul, thk, thn, gas; };
    auto compute = [&](uint64_t seed, double K, const std::vector<Pt>& P) {
        Cloud b, k, t, g; build(seed, b, k, t, g); Cloud tK = modulate(t, K), gK = modulate(g, K);
        Cloud s; push(s, 0, 0, 0, N_sgr);
        Comps c; c.sgr = evalFG(s, P); c.bul = evalFG(b, P); c.thk = evalFG(k, P); c.thn = evalFG(tK, P); c.gas = evalFG(gK, P);
        soft_corr_comp(D, 0, P, c.bul); soft_corr_comp(D, 1, P, c.thk); soft_corr_comp(D, 2, P, c.thn); soft_corr_comp(D, 3, P, c.gas);
        return c;
    };
    Comps C2 = compute(1000, ARM_CONTRAST, pts), C1 = compute(1000, 1.0, pts);
    const size_t NPT = pts.size();
    auto fcomp = [&](const Comps& c, int q, size_t i) { const FG& f = q == 0 ? c.sgr : q == 1 ? c.bul : q == 2 ? c.thk : q == 3 ? c.thn : c.gas; return A_F * f.th[i]; };
    auto floc = [&](const Comps& c, size_t i) { double s = 0; for (int q = 0; q < 5; ++q) s += fcomp(c, q, i); return s; };
    auto gvec = [&](const Comps& c, size_t i) { std::array<double, 3> g{0, 0, 0}; for (int q = 0; q < 5; ++q) { const FG& f = q == 0 ? c.sgr : q == 1 ? c.bul : q == 2 ? c.thk : q == 3 ? c.thn : c.gas; g[0] += A_F * f.gx[i]; g[1] += A_F * f.gy[i]; g[2] += A_F * f.gz[i]; } return g; };

    // noise from a second realisation (ridge + Sun + origin + rings), total local f and in-plane |grad f|
    double nz_f = 0, nz_g = 0;
    {   std::vector<Pt> sub(pts.begin() + off_ridge, pts.begin() + off_sl); Comps B = compute(5000, ARM_CONTRAST, sub);
        double s1 = 0, s2 = 0, g1 = 0, g2 = 0;
        for (size_t i = 0; i < sub.size(); ++i) { double fa = floc(C2, off_ridge + i), fb = floc(B, i); s1 += (fa - fb) * (fa - fb); s2 += fa * fa;
            auto ga = gvec(C2, off_ridge + i), gb = gvec(B, i); double ma = std::hypot(ga[0], ga[1]), mb = std::hypot(gb[0], gb[1]); g1 += (ma - mb) * (ma - mb); g2 += ma * ma; }
        nz_f = std::sqrt(s1 / s2) / std::sqrt(2.0); nz_g = std::sqrt(g1 / g2) / std::sqrt(2.0); }
    std::printf("Monte-Carlo noise (two seeds): f_local %.2f%% ; in-plane |grad f| %.2f%%\n", 100 * nz_f, 100 * nz_g);
    {   // V6 ray-quadrature cross-check of the column (K = 1)
        double rs = theta_rays_raw(D, 0, R0, 0, 3000, 0.05, 40.0), rg = theta_rays_raw(D, 0, 0, 0, 3000, 0.02, 40.0);
        double ps = 0, pg = 0; for (int q = 1; q < 5; ++q) { ps += (q == 1 ? C1.bul : q == 2 ? C1.thk : q == 3 ? C1.thn : C1.gas).th[off_sun]; pg += (q == 1 ? C1.bul : q == 2 ? C1.thk : q == 3 ? C1.thn : C1.gas).th[off_org]; }
        check("V6a", "column at the Sun: particle sum vs ray quadrature (3%)", std::fabs(ps / rs - 1) < 3e-2, ps / rs - 1);
        check("V6b", "column at the centre: particle sum vs ray quadrature (3%)", std::fabs(pg / rg - 1) < 3e-2, pg / rg - 1);
    }
    if (g_fail) { std::printf("validation failed — results not used.\n"); return 1; }

    // ---------------- C. fields ----------------
    std::printf("\n== C. PRESSURE BY VOLUME ON THE STATIC DISC (K = %.2f) ==\n", ARM_CONTRAST);
    auto describe = [&](const char* nm, size_t i) {
        double fl = floc(C2, i), ft = F_AMB + fl; auto g = gvec(C2, i);
        std::printf("%-7s f_local = %.4e (Sgr %.2e bulge %.2e thick %.2e thin %.2e gas %.2e) ; f_total = %.4e ; ambient share %.2e ; |grad f| = %.3e per kpc\n", nm, fl,
                    fcomp(C2, 0, i), fcomp(C2, 1, i), fcomp(C2, 2, i), fcomp(C2, 3, i), fcomp(C2, 4, i), ft, F_AMB / ft, std::hypot(g[0], g[1]));
    };
    describe("Sun", off_sun); describe("centre", off_org);
    std::printf("f_total centre/Sun = %.3f ; f_local centre/Sun = %.3f ; Sun f_local/f_amb = %.3f ; centre f_local/f_amb = %.3f\n",
                (F_AMB + floc(C2, off_org)) / (F_AMB + floc(C2, off_sun)), floc(C2, off_org) / floc(C2, off_sun), floc(C2, off_sun) / F_AMB, floc(C2, off_org) / F_AMB);
    std::printf("arm overdensity at the Sun: f_local %+.3f%%\n", 100 * (floc(C2, off_sun) / floc(C1, off_sun) - 1));
    // ring means
    std::vector<double> ringL(NRING), ringBR(NRING), ringDR(NRING);
    for (int rr = 0; rr < NRING; ++rr) { double a = 0, b = 0, d = 0; for (int j = 0; j < NAZ; ++j) { size_t i = off_ring + rr * NAZ + j; a += floc(C2, i); b += fcomp(C2, 0, i) + fcomp(C2, 1, i); d += fcomp(C2, 2, i) + fcomp(C2, 3, i) + fcomp(C2, 4, i); } ringL[rr] = a / NAZ; ringBR[rr] = b / NAZ; ringDR[rr] = d / NAZ; }
    std::printf("\nring means (pitches): R kpc | f_local | f_local/f_amb | bulge regime | disc regime\n");
    for (int rr = 0; rr < NRING; rr += 2) std::printf("  %5.1f | %.4e | %.3f | %.4e | %.4e\n", 1.0 + 0.5 * rr, ringL[rr], ringL[rr] / F_AMB, ringBR[rr], ringDR[rr]);
    double R_amb = -1; for (int rr = 1; rr < NRING; ++rr) if (ringL[rr - 1] >= F_AMB && ringL[rr] < F_AMB) { R_amb = 1.0 + 0.5 * (rr - 1) + 0.5 * (ringL[rr - 1] - F_AMB) / (ringL[rr - 1] - ringL[rr]); break; }
    double R_bd = -1; for (int rr = 1; rr < NRING; ++rr) if (ringBR[rr - 1] >= ringDR[rr - 1] && ringBR[rr] < ringDR[rr]) { R_bd = 1.0 + 0.5 * (rr - 1) + 0.5 * (ringBR[rr - 1] - ringDR[rr - 1]) / ((ringBR[rr - 1] - ringDR[rr - 1]) - (ringBR[rr] - ringDR[rr])); break; }
    std::printf("T4/T2 ring-mean crossings: f_local = f_amb at R = %s ; bulge regime = disc regime at R = %s\n",
                R_amb > 0 ? (std::to_string(R_amb).substr(0, 5) + " kpc").c_str() : "none in 1-17 kpc", R_bd > 0 ? (std::to_string(R_bd).substr(0, 5) + " kpc").c_str() : "none in 1-17 kpc");

    // T2: Sgr A* against the rest along the plane, analytic (no softening)
    {
        double f_rest0 = A_F * theta_rays_raw(D, 0, 0, 0, 3000, 0.02, 40.0);                    // bulge + discs at the centre, K = 1, analytic
        double r_S = std::sqrt(N_sgr * V_P / (4 * PI * LP * f_rest0));
        std::printf("T2 Sgr A* against the surrounding matter at the centre: f_rest(0) = %.4e pitches (analytic) ; f_Sgr = f_rest at r = %.3e m = %.2f pc (shell depth %.3e)\n",
                    f_rest0, r_S, r_S / PC_M, r_S / LP);
    }

    // ---------------- deterministic gradient (Amendment 3) ----------------
    ArmGrid AG = build_arm_grid(arms, D, ARM_CONTRAST); const Dirs DR = make_dirs(3000);
    std::vector<int> grid_sub, ridge_sub;
    for (int j = 0; j < GN; j += 2) for (int i = 0; i < GN; i += 2) { double R = std::hypot(pts[off_grid + j * GN + i].x, pts[off_grid + j * GN + i].y); if (R > 0.7 && R < 15.0) grid_sub.push_back(off_grid + j * GN + i); }
    { int kk = 0; for (auto& a : arms) for (auto& nd : a.nodes) { if (nd.tier <= 1 && kk % 3 == 0) ridge_sub.push_back(off_ridge + kk); ++kk; } }
    std::vector<int> gidx = grid_sub; gidx.insert(gidx.end(), ridge_sub.begin(), ridge_sub.end()); gidx.push_back(off_sun);
    std::vector<int> slot(NPT, -1); for (size_t q = 0; q < gidx.size(); ++q) slot[gidx[q]] = (int)q;
    std::vector<std::array<double, 3>> gr(gidx.size()); std::vector<double> fr(gidx.size());
    {   const double hh = 0.05;
#pragma omp parallel for schedule(dynamic)
        for (long q = 0; q < (long)gidx.size(); ++q) {
            const Pt& P = pts[gidx[q]];
            fr[q] = f_ray(D, AG, ARM_CONTRAST, DR, P.x, P.y, P.z);
            double gx = (f_ray(D, AG, ARM_CONTRAST, DR, P.x + hh, P.y, P.z) - f_ray(D, AG, ARM_CONTRAST, DR, P.x - hh, P.y, P.z)) / (2 * hh);
            double gy = (f_ray(D, AG, ARM_CONTRAST, DR, P.x, P.y + hh, P.z) - f_ray(D, AG, ARM_CONTRAST, DR, P.x, P.y - hh, P.z)) / (2 * hh);
            gr[q] = {gx, gy, 0.0};
        }
    }
    {   double s = 0; for (int i : ridge_sub) s += fr[slot[i]] / floc(C2, i) - 1; s /= ridge_sub.size();
        check("V8", "ridge nodes: mean f(ray, arms included) / f(particle sum) - 1 (3%)", std::fabs(s) < 3e-2, s);
        double r7 = 0, r9 = 0; const int na = 48;
        for (int j = 0; j < na; ++j) { double ph = 2 * PI * (j + 0.5) / na; r7 += f_ray(D, AG, ARM_CONTRAST, DR, 7.0 * std::sin(ph), 7.0 * std::cos(ph), 0); r9 += f_ray(D, AG, ARM_CONTRAST, DR, 9.0 * std::sin(ph), 9.0 * std::cos(ph), 0); }
        r7 /= na; r9 /= na; double dray = (r9 - r7) / 2.0, dpar = (ringL[16] - ringL[12]) / 2.0;
        check("V9", "ring-mean radial derivative 7-9 kpc: ray instrument vs particle-sum ring means (5%)", std::fabs(dray / dpar - 1) < 5e-2, dray / dpar - 1);
        std::printf("      (ring means at 7 and 9 kpc: ray %.4e %.4e ; particle %.4e %.4e)\n", r7, r9, ringL[12], ringL[16]); }
    if (g_fail) { std::printf("validation failed — gradient results not used.\n"); return 1; }
    { int q = slot[off_sun]; std::printf("Sun: f(ray) = %.4e ; in-plane grad f = (%.1f, %.1f) per kpc, |grad f| = %.1f ; direction to the Galactic centre is -y\n", fr[q], gr[q][0], gr[q][1], std::hypot(gr[q][0], gr[q][1])); }

    // T1: gradient points toward the nearest mass
    {
        Cloud all; { Cloud b, k, t, g; build(1000, b, k, t, g); Cloud tK = modulate(t, ARM_CONTRAST), gK = modulate(g, ARM_CONTRAST); all = b; append(all, k); append(all, tK); append(all, gK); push(all, 0, 0, 0, N_sgr); }
        std::vector<int> okA(grid_sub.size()), okB(grid_sub.size());
#pragma omp parallel for schedule(static)
        for (long q = 0; q < (long)grid_sub.size(); ++q) {
            int i = grid_sub[q]; double px = pts[i].x, py = pts[i].y, pz = pts[i].z, sx = 0, sy = 0, sw = 0;
            for (size_t k = 0; k < all.x.size(); ++k) { double dx = all.x[k] - px, dy = all.y[k] - py, dz = all.z[k] - pz; if (dx * dx + dy * dy + dz * dz < 1.0) { sx += all.w[k] * dx; sy += all.w[k] * dy; sw += all.w[k]; } }
            auto& g = gr[slot[i]]; double cx = sw > 0 ? sx / sw : 0, cy = sw > 0 ? sy / sw : 0;
            okA[q] = (g[0] * cx + g[1] * cy) > 0; okB[q] = (g[0] * (-px) + g[1] * (-py)) > 0;
        }
        int a = 0, b = 0; for (size_t q = 0; q < grid_sub.size(); ++q) { a += okA[q]; b += okB[q]; }
        double fa = (double)a / grid_sub.size(), fb = (double)b / grid_sub.size();
        auto cls = [](double f) { return f >= 0.99 ? "holds" : (f < 0.90 ? "fails" : "marginal"); };
        std::printf("\nT1 'pressure is always higher in the direction of the nearest mass' over %zu plane points (1 kpc grid), 0.7 < R < 15 kpc (deterministic gradient):\n", grid_sub.size());
        std::printf("   T1a gradient toward the baryon-weighted centroid within 1 kpc: %.4f  -> %s\n", fa, cls(fa));
        std::printf("   T1b gradient toward the Galactic centre: %.4f  -> %s\n", fb, cls(fb));
    }

    // arms (T3)
    std::printf("\n== T3 SHEATHS: direction of the pressure gradient against the ridge (measured + near-extended nodes, every third node, deterministic gradient) ==\n");
    FILE* fr_csv = std::fopen("gd12_ridge_metrics.csv", "w");
    std::fprintf(fr_csv, "arm,node,tier,x,y,R,f_total,f_local,f_bulge_regime,f_disc_regime,gradmag_per_kpc,cos_grad_t,cos_r_t,cos_grad_to_GC,contrast_ring,arm_excess_share\n");
    auto ring_at = [&](const std::vector<double>& v, double R) { double f = (R - 1.0) / 0.5; int k = (int)std::floor(f); if (k < 0) k = 0; if (k > NRING - 2) k = NRING - 2; double t = std::min(1.0, std::max(0.0, f - k)); return v[k] * (1 - t) + v[k + 1] * t; };
    std::printf("%-9s %-7s %-12s %-10s %-9s %-11s %-11s %-10s %-10s\n", "arm", "nodes", "<|g.t|/|g|>", "<|r.t|>", "|diff|", "to GC>0", "f/ring-1", "arm share", "bulge-dom");
    int k = 0; double sumg = 0, sumr = 0; int cntg = 0;
    for (auto& a : arms) {
        double sg = 0, sr = 0, sc = 0, sgc = 0, sas = 0; int nu = 0, nb = 0, nall = 0;
        for (size_t i = 0; i < a.nodes.size(); ++i, ++k) {
            const Node& nd = a.nodes[i]; size_t pi = off_ridge + k;
            size_t i0 = i ? i - 1 : i, i1 = i + 1 < a.nodes.size() ? i + 1 : i; double tx = a.nodes[i1].x - a.nodes[i0].x, ty = a.nodes[i1].y - a.nodes[i0].y, tl = std::hypot(tx, ty); tx /= tl; ty /= tl;
            double fl = floc(C2, pi), fb = fcomp(C2, 0, pi) + fcomp(C2, 1, pi), fd = fcomp(C2, 2, pi) + fcomp(C2, 3, pi) + fcomp(C2, 4, pi), con = fl / ring_at(ringL, nd.R) - 1, as = 1 - floc(C1, pi) / fl;
            double cr = std::fabs((nd.x * tx + nd.y * ty) / nd.R);
            if (slot[pi] >= 0) {
                auto& g = gr[slot[pi]]; double gm = std::hypot(g[0], g[1]); double cg = gm > 0 ? std::fabs(g[0] * tx + g[1] * ty) / gm : 0, toGC = gm > 0 ? (g[0] * (-nd.x) + g[1] * (-nd.y)) / (gm * nd.R) : 0;
                std::fprintf(fr_csv, "%s,%zu,%d,%.4f,%.4f,%.4f,%.4e,%.4e,%.4e,%.4e,%.4e,%.4f,%.4f,%.4f,%.5f,%.5f\n", a.name.c_str(), i, nd.tier, nd.x, nd.y, nd.R, F_AMB + fl, fl, fb, fd, gm, cg, cr, toGC, con, as);
                if (nd.tier <= 1) { sg += cg; sr += cr; sc += con; sgc += (toGC > 0); sas += as; nb += (fb > fd); ++nu; sumg += cg; sumr += cr; ++cntg; }
            } else {
                std::fprintf(fr_csv, "%s,%zu,%d,%.4f,%.4f,%.4f,%.4e,%.4e,%.4e,%.4e,,,%.4f,,%.5f,%.5f\n", a.name.c_str(), i, nd.tier, nd.x, nd.y, nd.R, F_AMB + fl, fl, fb, fd, cr, con, as);
            }
            ++nall;
        }
        if (nu) std::printf("%-9s %-7d %-12.3f %-10.3f %-9.3f %-11.3f %+-11.3e %-10.4f %-9.0f%%\n", a.name.c_str(), nu, sg / nu, sr / nu, std::fabs(sg / nu - sr / nu), sgc / nu, sc / nu, sas / nu, 100.0 * nb / nu);
    }
    std::fclose(fr_csv);
    {   double mg = sumg / cntg, mr = sumr / cntg; const char* cls = (mg >= 0.5) ? "supported" : (std::fabs(mg - mr) <= 0.05 ? "not supported" : "marginal");
        std::printf("all arms: <|grad f . t|/|grad f|> = %.3f against geometric <|r.t|> = %.3f (|diff| %.3f)  ->  %s\n", mg, mr, std::fabs(mg - mr), cls); }

    // ---------------- D. emission at depth ----------------
    std::printf("\n== D. EMISSION AT DEPTH: pressure by volume at the emitter against the observer (closure to spectral position open) ==\n");
    const double FS = F_AMB + floc(C2, off_sun);
    std::printf("observer (Sun) f_total = %.4e pitches\n", FS);
    std::printf("  l      d kpc   f_total(emitter)   Delta f (pitches)   ratio to Sun\n");
    for (int il : {0, 9, 18, 27}) for (int id = 0; id < 5; id += 2) { size_t i = off_sl + il * 5 + id; double ft = F_AMB + floc(C2, i);
        std::printf("  %-6d %-7.0f %-18.4e %-19.4e %-10.4f\n", 10 * il, dlist[id], ft, ft - FS, ft / FS); }
    { double lo = 1e30, hi = -1e30; for (int i = 0; i < NL * 5; ++i) { double ft = F_AMB + floc(C2, off_sl + i); lo = std::fmin(lo, ft / FS); hi = std::fmax(hi, ft / FS); }
      std::printf("ratio f_total(emitter)/f_total(Sun) over 180 emitters 2-10 kpc from the Sun: %.4f to %.4f ; with the ambient term removed the ratios would span %.3f to %.3f\n", lo, hi,
                  [&]() { double l2 = 1e30; for (int i = 0; i < NL * 5; ++i) l2 = std::fmin(l2, floc(C2, off_sl + i) / floc(C2, off_sun)); return l2; }(),
                  [&]() { double h2 = -1e30; for (int i = 0; i < NL * 5; ++i) h2 = std::fmax(h2, floc(C2, off_sl + i) / floc(C2, off_sun)); return h2; }()); }

    // viewer data
    {
        FILE* fj = std::fopen("mw_pressure.js", "w");
        std::fprintf(fj, "// Generated by gd12_pressure_by_volume.cpp. Static disc; pressure by volume in pitches. x,y in kpc, Galactic plane.\n");
        std::fprintf(fj, "window.MW_PRESSURE={n:%d,half:%.1f,fAmb:%.6g,cats:[\"Sgr A*\",\"bulge\",\"thick disc\",\"thin disc\",\"gas\"],cases:[\n", GN, GM, F_AMB);
        std::fprintf(fj, "{name:\"Pressure by volume f_total (displaced volume per shell volume)\",unit:\"pitches\",kind:\"log\",v:[");
        for (int j = 0; j < GN; ++j) for (int i = 0; i < GN; ++i) std::fprintf(fj, "%s%.5g", (i == 0 && j == 0) ? "" : ",", F_AMB + floc(C2, off_grid + j * GN + i));
        std::fprintf(fj, "]},\n{name:\"Dominant source of displaced volume (meeting surfaces are where two sources are equal)\",unit:\"\",kind:\"cat\",v:[");
        for (int j = 0; j < GN; ++j) for (int i = 0; i < GN; ++i) { size_t p = off_grid + j * GN + i; int best = 0; double bf = -1; for (int q = 0; q < 5; ++q) { double f = fcomp(C2, q, p); if (f > bf) { bf = f; best = q; } } std::fprintf(fj, "%s%d", (i == 0 && j == 0) ? "" : ",", best); }
        std::fprintf(fj, "]}\n]};\n"); std::fclose(fj);
    }
    std::printf("\nwrote gd12_ridge_metrics.csv mw_pressure.js\n");
    return 0;
}
