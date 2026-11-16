// =====================================================================
//  GD11 : static-disc displacement cascade and macro throughput
//  ---------------------------------------------------------------------
//  Static disc, positions and baryon counts only. No velocity, rotation or redshift enters.
//  S1  u(x) = (V_p/4pi) Int n_b (x-x') / |x-x'|^3 d^3x'        displacement field, div u = n_b V_p
//  S2  shell cascade: delta_k = V_enc/(4 pi r_k^2), flux conserved shell to shell
//  S3  Theta_tilde(x) = (1/4pi) Int n_b / |x-x'|^2 d^3x'        mean baryon column, Theta = sigma_occ * Theta_tilde
//  Pre-registration: PROMPT.md (same folder).
//
//  Inputs read from generated data: GD08 mw_arms_data.js, GD09 mw_baryons.js
//  Build: cl /std:c++20 /EHsc /O2 /openmp /I Engine/include gd11_static_disc_cascade.cpp
//  Run from this folder. Writes: gd11_ridge_metrics.csv  mw_throughput.js
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
const double PC_M = measured::AU * 648000.0 / PI, KPC_M = 1000.0 * PC_M;     // exact parsec definition
const double LP = measured::l_P;
const double V_P = law_IV::V_disp_p;                                          // proton exclusion volume [m^3]
const double KOPPA_B = bridge::koppa_per_baryon;                              // comparison route only
const double N_SUN = bridge::N_baryons(bridge::koppa_Sun);                    // baryons per solar mass, no kilograms
constexpr double EPS = 0.03;                                                  // Plummer softening [kpc]
constexpr int NP_TOTAL = 1000000;
constexpr double ARM_CONTRAST = 1.32, R0 = 8.15;

// ---------------- data readers (GD08 / GD09 generated files) ----------------
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

// ---------------- deterministic sampling ----------------
struct Rng {
    std::mt19937_64 g; explicit Rng(uint64_t s) : g(s) {}
    double u() { return ((g() >> 11) + 0.5) * (1.0 / 9007199254740992.0); }
    double expo(double mean) { return -mean * std::log(u()); }
};
struct Cloud { std::vector<double> x, y, z, w; };                 // w = baryons carried by the particle
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

// ---------------- analytic densities [baryons per kpc^3] (second route) ----------------
struct Dens { double Nb, Nk, Nt, Ng; };
double erl_frac(double Rd, double a, double b) { return (1 + a / Rd) * std::exp(-a / Rd) - (1 + b / Rd) * std::exp(-b / Rd); }
double n_total(const Dens& D, double x, double y, double z) {
    static const double Ptr = std::exp(-10.0) * (1 + 10 + 50);
    const double sa = std::sin(BANG), ca = std::cos(BANG), X = x * sa + y * ca, Y = x * ca - y * sa;
    const double s = std::sqrt(X * X / (HX * HX) + Y * Y / (HY * HY) + z * z / (HZ * HZ));
    double n = D.Nb / (8 * PI * HX * HY * HZ * (1 - Ptr)) * std::exp(-s);
    const double R = std::hypot(x, y), az = std::fabs(z);
    static const double Ft = erl_frac(2.6, 0, 20), Fk = erl_frac(2.0, 0, 20), Fg = erl_frac(5.2, 2, 19);
    n += D.Nt * std::exp(-R / 2.6 - az / 0.30) / (Ft * 4 * PI * 2.6 * 2.6 * 0.30);
    n += D.Nk * std::exp(-R / 2.0 - az / 0.90) / (Fk * 4 * PI * 2.0 * 2.0 * 0.90);
    if (R >= 2 && R <= 19) n += D.Ng * std::exp(-R / 5.2 - az / 0.10) / (Fg * 4 * PI * 5.2 * 5.2 * 0.10);
    return n;
}

// ---------------- field evaluation ----------------
struct Pt { double x, y, z; };
struct F { std::vector<double> th, ux, uy, uz, zb; };            // raw kernel sums
F evalF(const Cloud& C, const std::vector<Pt>& pts) {
    const size_t n = C.x.size(), m = pts.size(); const double e2 = EPS * EPS;
    F f; f.th.assign(m, 0); f.ux.assign(m, 0); f.uy.assign(m, 0); f.uz.assign(m, 0); f.zb.assign(m, 0);
#pragma omp parallel for schedule(static)
    for (long i = 0; i < (long)m; ++i) {
        double th = 0, ux = 0, uy = 0, uz = 0, zb = 0; const double px = pts[i].x, py = pts[i].y, pz = pts[i].z;
        for (size_t k = 0; k < n; ++k) {
            double dx = px - C.x[k], dy = py - C.y[k], dz = pz - C.z[k], d2 = dx * dx + dy * dy + dz * dz + e2;
            double inv = 1.0 / d2, rs = std::sqrt(inv), w = C.w[k];
            th += w * inv; zb += w * rs; double t = w * inv * rs; ux += t * dx; uy += t * dy; uz += t * dz;
        }
        f.th[i] = th; f.ux[i] = ux; f.uy[i] = uy; f.uz[i] = uz; f.zb[i] = zb;
    }
    return f;
}
void add(F& a, const F& b) { for (size_t i = 0; i < a.th.size(); ++i) { a.th[i] += b.th[i]; a.ux[i] += b.ux[i]; a.uy[i] += b.uy[i]; a.uz[i] += b.uz[i]; a.zb[i] += b.zb[i]; } }
// unit conversions (kpc sums -> SI)
double theta_tilde_m2(double th) { return th / (4 * PI * KPC_M * KPC_M); }              // mean baryon column [m^-2]
double u_m(double s) { return V_P * s / (4 * PI * KPC_M * KPC_M); }                      // displacement [m]
double sigma_eq(double th) { return theta_tilde_m2(th) * PC_M * PC_M / N_SUN; }          // Msun per pc^2 (via the engine's N_Sun)
double Z_bridge(double zb) { return KOPPA_B * zb / KPC_M; }

// The Plummer-softened 1/d^2 sum under-counts by n eps pi/2 per unit (1/4pi) (analytic, smooth density):
// raw_true = raw_sum + 2 pi^2 n eps  [raw units: baryons per kpc^2; n in baryons per kpc^3].
double soft_corr(double raw, double n_kpc3) { return raw + 2 * PI * PI * n_kpc3 * EPS; }

// mean column from analytic density by ray quadrature (Fibonacci directions)
double theta_tilde_rays(const Dens& D, double x, double y, double z, int ND, double step, double Lmax) {
    double tot = 0;
#pragma omp parallel for reduction(+ : tot) schedule(static)
    for (int i = 0; i < ND; ++i) {
        double cz = 1 - 2 * (i + 0.5) / ND, sz = std::sqrt(1 - cz * cz), ph = PI * (1 + std::sqrt(5.0)) * (i + 0.5);
        double dx = sz * std::cos(ph), dy = sz * std::sin(ph), dz = cz, col = 0;
        for (double l = 0.5 * step; l < Lmax; l += step) col += n_total(D, x + l * dx, y + l * dy, z + l * dz) * step;
        tot += col;
    }
    return tot / ND / (KPC_M * KPC_M);                           // [m^-2]
}

int g_fail = 0;
void check(const char* id, const char* what, bool ok, double v) {
    std::printf("  [%s] %s : %s  (%.3e)\n", ok ? "PASS" : "FAIL", id, what, v);
    if (!ok) ++g_fail;
}
std::string sci(double x) { char b[32]; std::snprintf(b, sizeof b, "%.3e", x); return b; }

} // namespace

int main() {
    std::printf("=================================================================\n");
    std::printf(" GD11 STATIC-DISC DISPLACEMENT CASCADE AND MACRO THROUGHPUT\n");
    std::printf(" positions + baryon counts only ; no velocity, rotation or redshift input\n");
    std::printf("=================================================================\n");
    const double N_sh = law_I::N, S_bd = law_I::S_boundary, R_CMB = law_I::R_CMB;
    const double R_excl = law_IV::R_excl_p, R_pl = law_III::R_p_lock, R_int = law_III::R_charge;
    const double sig_excl = PI * R_excl * R_excl, sig_p = PI * R_pl * R_pl, sig_int = PI * R_int * R_int;
    std::printf("l_P = %.6e m ; N = %.4e shells ; S = 4piN^2 = %.4e ; R_CMB = %.4e m\n", LP, N_sh, S_bd, R_CMB);
    std::printf("V_p = %.4e m^3 ; n_p = V_p/l_P^3 = %.4e spations per baryon ; R_excl = %.4e m\n", V_P, V_P / (LP * LP * LP), R_excl);
    std::printf("sigma_excl = %.3e m^2 ; sigma_p = %.3e m^2 ; sigma_int = %.3e m^2 ; N_Sun = %.4e baryons ; P_rad = %.4e Pa\n\n",
                sig_excl, sig_p, sig_int, N_SUN, law_I::P_rad);

    // ---------------- instrument validation ----------------
    std::printf("== INSTRUMENT VALIDATION ==\n");
    check("V1", "mass_from_V_disp(V_p) = m_p", std::fabs(law_IV::mass_from_V_disp(V_P) / measured::m_p - 1) < 1e-12,
          law_IV::mass_from_V_disp(V_P) / measured::m_p - 1);
    {   // V2 shell theorem for u, V3 flux conservation, V4 mean column on a uniform ball
        Rng r(21); Cloud shell, ball; const int N = 200000; const double Nb = 1e60;
        for (int i = 0; i < N; ++i) {
            double cz = 2 * r.u() - 1, ph = 2 * PI * r.u(), s = std::sqrt(1 - cz * cz); push(shell, s * std::cos(ph), s * std::sin(ph), cz, Nb / N);
            double rr = std::cbrt(r.u()); double cz2 = 2 * r.u() - 1, ph2 = 2 * PI * r.u(), s2 = std::sqrt(1 - cz2 * cz2);
            push(ball, rr * s2 * std::cos(ph2), rr * s2 * std::sin(ph2), rr * cz2, Nb / N);
        }
        std::vector<Pt> p = {{2, 0, 0}, {0.9, 0, 0}, {0, 0.3, 0}};
        F f = evalF(shell, p);
        double an = V_P * Nb / (4 * PI * (2 * KPC_M) * (2 * KPC_M)), got = u_m(f.ux[0]);
        check("V2a", "outside a uniform shell |u| = V N/(4 pi r^2) (0.5%)", std::fabs(got / an - 1) < 5e-3, got / an - 1);
        double inside = std::fmax(std::fabs(u_m(f.ux[2])), std::fabs(u_m(f.uy[2])));
        double surf = V_P * Nb / (4 * PI * KPC_M * KPC_M);
        check("V2b", "inside a uniform shell |u| <= 1% of the surface value", inside / surf < 1e-2, inside / surf);
        // V3 flux through spheres around the ball
        for (double Rs : {2.0, 5.0}) {
            const int ND = 3000; std::vector<Pt> sp(ND);
            for (int i = 0; i < ND; ++i) { double cz = 1 - 2 * (i + 0.5) / ND, sz = std::sqrt(1 - cz * cz), ph = PI * (1 + std::sqrt(5.0)) * (i + 0.5); sp[i] = {Rs * sz * std::cos(ph), Rs * sz * std::sin(ph), Rs * cz}; }
            F g = evalF(ball, sp); double mean = 0;
            for (int i = 0; i < ND; ++i) { double nx = sp[i].x / Rs, ny = sp[i].y / Rs, nz = sp[i].z / Rs; mean += u_m(g.ux[i] * nx + g.uy[i] * ny + g.uz[i] * nz); }
            mean /= ND; double flux = mean * 4 * PI * (Rs * KPC_M) * (Rs * KPC_M), want = V_P * Nb;
            char nm[64]; std::snprintf(nm, sizeof nm, "flux through r = %.0f kpc equals V N (1%%)", Rs);
            check(Rs == 2.0 ? "V3a" : "V3b", nm, std::fabs(flux / want - 1) < 1e-2, flux / want - 1);
        }
        // V4 mean column on a uniform ball (radius 1 kpc): centre and d = 0.6 a
        std::vector<Pt> q = {{0, 0, 0}, {0.6, 0, 0}}; F h = evalF(ball, q);
        double n_m = Nb / (4.0 / 3.0 * PI * KPC_M * KPC_M * KPC_M), a_m = KPC_M, n_k = Nb / (4.0 / 3.0 * PI);   // n_k per kpc^3 (a = 1 kpc)
        double c0 = n_m * a_m, d = 0.6, cc = std::sqrt(1 - d * d), c1 = n_m * a_m * (0.5 + cc * cc / (2 * d) * std::asinh(d / cc));
        double raw0 = soft_corr(h.th[0], n_k), raw1 = soft_corr(h.th[1], n_k);
        check("V4a", "mean column at the ball centre = n a, softening corrected (0.5%)", std::fabs(theta_tilde_m2(raw0) / c0 - 1) < 5e-3, theta_tilde_m2(raw0) / c0 - 1);
        check("V4b", "mean column at d = 0.6 a, closed form, softening corrected (0.5%)", std::fabs(theta_tilde_m2(raw1) / c1 - 1) < 5e-3, theta_tilde_m2(raw1) / c1 - 1);
        std::printf("      (uncorrected softened sum: %+.2f%% and %+.2f%%; analytic bias -(pi/2) eps/a = %+.2f%%)\n",
                    100 * (theta_tilde_m2(h.th[0]) / c0 - 1), 100 * (theta_tilde_m2(h.th[1]) / c1 - 1), -100 * 0.5 * PI * EPS);
    }
    std::printf("  validation failures so far: %d\n\n", g_fail);
    if (g_fail) { std::printf("validation failed — fields not used.\n"); return 1; }

    // ---------------- inputs ----------------
    auto arms = read_arms("../GD08_Milky_Way_Arm_Topology/mw_arms_data.js");
    std::string bjs = slurp("../GD09_Milky_Way_Baryon_Inventory/mw_baryons.js");
    if (arms.empty() || bjs.empty()) { std::printf("input files missing\n"); return 1; }
    Dens D{read_count(bjs, "bulge_stellar").c + read_count(bjs, "gas_bulge").c, read_count(bjs, "disc_thick").c, read_count(bjs, "disc_thin").c, read_count(bjs, "gas_disc_He").c};
    const double N_sgr = read_count(bjs, "smbh").c, N_all = D.Nb + D.Nk + D.Nt + D.Ng;
    std::printf("inputs: %zu arms ; N bulge %.3e thick %.3e thin %.3e gas %.3e ; sum %.4e ; Sgr A* %.3e (mass-equivalent)\n", arms.size(), D.Nb, D.Nk, D.Nt, D.Ng, N_all, N_sgr);
    int nn = 0; for (auto& a : arms) nn += (int)a.nodes.size();

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
    Cloud bulge, thick, thin, gas; build(1000, bulge, thick, thin, gas);

    // ---------------- S2 : the cascade ----------------
    std::printf("\n== S2 DISPLACEMENT CASCADE (spherical-equivalent shells about the Galactic centre) ==\n");
    struct RN { double r, cum; };
    std::vector<RN> rad; { Cloud all = bulge; append(all, thick); append(all, thin); append(all, gas);
        for (size_t i = 0; i < all.x.size(); ++i) rad.push_back({std::sqrt(all.x[i] * all.x[i] + all.y[i] * all.y[i] + all.z[i] * all.z[i]), all.w[i]});
        std::sort(rad.begin(), rad.end(), [](const RN& a, const RN& b) { return a.r < b.r; }); double c = 0; for (auto& e : rad) { c += e.cum; e.cum = c; } }
    auto N_enc = [&](double r_kpc) {
        size_t lo = 0, hi = rad.size(); while (lo < hi) { size_t mid = (lo + hi) / 2; if (rad[mid].r <= r_kpc) lo = mid + 1; else hi = mid; }
        return N_sgr + (lo ? rad[lo - 1].cum : 0.0);
    };
    std::printf("%-14s %-11s %-11s %-12s %-11s %-12s %-10s\n", "r", "N_enc", "V_enc[m^3]", "n_d[spations]", "shift[m]", "shift[pitch]", "shift/r");
    const double rlist_pc[] = {0.01, 0.1, 1, 10, 100, 1000, 2000, 4000, 8150, 15000, 30000, 86000, 300000, 1e6};
    double prev_flux = -1; bool rec_ok = true; double prev_r = 0, prev_d = 0;
    for (double rp : rlist_pc) {
        double r_m = rp * PC_M, N_e = N_enc(rp / 1000.0), V = N_e * V_P, d = V / (4 * PI * r_m * r_m);
        char lab[24]; if (rp >= 1000) std::snprintf(lab, sizeof lab, "%g kpc", rp / 1000.0); else std::snprintf(lab, sizeof lab, "%g pc", rp);
        std::printf("%-14s %-11.3e %-11.3e %-12.3e %-11.3e %-12.3e %-10.2e\n", lab, N_e, V, V / (LP * LP * LP), d, d / LP, d / r_m);
        if (rp >= 30000) { if (prev_r > 0 && std::fabs(d * r_m * r_m / (prev_d * prev_r * prev_r) - 1) > 1e-12) rec_ok = false; prev_r = r_m; prev_d = d; }
        (void)prev_flux;
    }
    {   // recursion identity far outside the matter: delta_{k+1} r_{k+1}^2 = delta_k r_k^2, doubling radii
        double V = (N_enc(100.0)) * V_P, r = 100.0 * KPC_M, d = V / (4 * PI * r * r), maxdev = 0;
        for (int k = 0; k < 40; ++k) { double r2 = 2 * r, d2 = d * (r * r) / (r2 * r2); maxdev = std::fmax(maxdev, std::fabs(d2 * r2 * r2 / (V / (4 * PI)) - 1)); r = r2; d = d2; }
        check("V5", "recursion delta_{k+1} r_{k+1}^2 = delta_k r_k^2 over 40 doublings", maxdev < 1e-12 && rec_ok, maxdev);
    }
    {
        double V_sgr = N_sgr * V_P, V_gal = (N_enc(1e4)) * V_P, V_sun = N_SUN * V_P;
        auto r1 = [&](double V) { return std::sqrt(V / (4 * PI * LP)); };
        std::printf("\ndisplacement horizon r_1 (shift = one pitch): proton %.3e m ; Sun %.3e m = %.2f pc ; Sgr A* alone %.3e m = %.2f kpc ; whole Galaxy %.3e m = %.1f kpc\n",
                    r1(V_P), r1(V_sun), r1(V_sun) / PC_M, r1(V_sgr), r1(V_sgr) / KPC_M, r1(V_gal), r1(V_gal) / KPC_M);
        double n_d = V_gal / (LP * LP * LP);
        std::printf("Galaxy: V_enc = %.4e m^3 (a cube of %.2f km) ; n_d = %.4e spations ; shift at R_CMB = n_d/S = %.3e pitch ; fraction of boundary cells = %.3e\n",
                    V_gal, std::cbrt(V_gal) / 1000.0, n_d, n_d / S_bd, n_d / S_bd);
        std::printf("visible disc extent 15 kpc (drawing limit) ; r_1/15 kpc = %.2f ; r_1/R_CMB = %.3e ; shells between r_1 and the Clearing ~ %.3e of N = %.3e\n",
                    r1(V_gal) / (15 * KPC_M), r1(V_gal) / R_CMB, (R_CMB - r1(V_gal)) / LP, N_sh);
        std::printf("matter volume fraction phi_V = n_b V_p: local (%.1e baryons/m^3 at 0.1 Msun/pc^3) = %.2e\n", 0.1 * N_SUN / (PC_M * PC_M * PC_M), 0.1 * N_SUN / (PC_M * PC_M * PC_M) * V_P);
    }

    // ---------------- evaluation points ----------------
    std::vector<Pt> pts; const int GN = 65; const double GS = 0.5, GM = 16.0;
    const int off_grid = 0; for (int j = 0; j < GN; ++j) for (int i = 0; i < GN; ++i) pts.push_back({-GM + GS * i, -GM + GS * j, 0});
    const int off_ridge = (int)pts.size(); for (auto& a : arms) for (auto& nd : a.nodes) pts.push_back({nd.x, nd.y, 0});
    const int off_sun = (int)pts.size(); pts.push_back({0, R0, 0});
    const int off_org = (int)pts.size(); pts.push_back({0, 0, 0});
    const int NAZ = 48, NRING = 33; const int off_ring = (int)pts.size();
    for (int rr = 0; rr < NRING; ++rr) for (int j = 0; j < NAZ; ++j) { double R = 1.0 + 0.5 * rr, ph = 2 * PI * (j + 0.5) / NAZ; pts.push_back({R * std::sin(ph), R * std::cos(ph), 0}); }
    std::printf("\nevaluation points: %zu\n", pts.size());

    Cloud thinK = modulate(thin, ARM_CONTRAST), gasK = modulate(gas, ARM_CONTRAST);
    F Fb = evalF(bulge, pts), Fk = evalF(thick, pts), Ft1 = evalF(thin, pts), Fg1 = evalF(gas, pts), Ft2 = evalF(thinK, pts), Fg2 = evalF(gasK, pts);
    F T1 = Fb; add(T1, Fk); add(T1, Ft1); add(T1, Fg1);                // K = 1
    F T2 = Fb; add(T2, Fk); add(T2, Ft2); add(T2, Fg2);                // K = 1.32 (the observed contrast)
    F Dsc = Fk; add(Dsc, Ft2); add(Dsc, Fg2);                          // disc regime (K = 1.32)
    std::vector<double> nloc(pts.size());                              // analytic local density (K = 1), softening correction
    for (size_t i = 0; i < pts.size(); ++i) { nloc[i] = n_total(D, pts[i].x, pts[i].y, pts[i].z); T1.th[i] = soft_corr(T1.th[i], nloc[i]); T2.th[i] = soft_corr(T2.th[i], nloc[i]); }

    // two-seed noise on the ridge + Sun + origin + rings (K = 1.32)
    double noise_th = 0, noise_u = 0;
    {
        Cloud b2, k2, t2, g2; build(5000, b2, k2, t2, g2); Cloud t2K = modulate(t2, ARM_CONTRAST), g2K = modulate(g2, ARM_CONTRAST);
        std::vector<Pt> sub(pts.begin() + off_ridge, pts.end()); F fb = evalF(b2, sub), fk = evalF(k2, sub), ft = evalF(t2K, sub), fg = evalF(g2K, sub);
        add(fb, fk); add(fb, ft); add(fb, fg);
        for (size_t i = 0; i < sub.size(); ++i) fb.th[i] = soft_corr(fb.th[i], nloc[off_ridge + i]);
        double s1 = 0, s2 = 0, u1 = 0, u2 = 0; size_t n = sub.size();
        for (size_t i = 0; i < n; ++i) {
            double a = T2.th[off_ridge + i], b = fb.th[i]; s1 += (a - b) * (a - b); s2 += a * a;
            double ua = std::sqrt(T2.ux[off_ridge + i] * T2.ux[off_ridge + i] + T2.uy[off_ridge + i] * T2.uy[off_ridge + i] + T2.uz[off_ridge + i] * T2.uz[off_ridge + i]);
            double ub = std::sqrt(fb.ux[i] * fb.ux[i] + fb.uy[i] * fb.uy[i] + fb.uz[i] * fb.uz[i]); u1 += (ua - ub) * (ua - ub); u2 += ua * ua;
        }
        noise_th = std::sqrt(s1 / s2) / std::sqrt(2.0); noise_u = std::sqrt(u1 / u2) / std::sqrt(2.0);
    }
    std::printf("Monte-Carlo noise (two seeds, ridge + Sun + origin + rings): Theta_tilde %.2f%% ; |u| %.2f%%\n", 100 * noise_th, 100 * noise_u);

    // second route: ray quadrature on analytic densities (K = 1) at the Sun and the origin
    {
        double rs = theta_tilde_rays(D, 0, R0, 0, 3000, 0.05, 40.0), rg = theta_tilde_rays(D, 0, 0, 0, 3000, 0.02, 40.0);
        double ps = theta_tilde_m2(T1.th[off_sun]), pg = theta_tilde_m2(T1.th[off_org]);
        check("V6a", "Theta_tilde at the Sun: particle sum vs ray quadrature (3%)", std::fabs(ps / rs - 1) < 3e-2, ps / rs - 1);
        check("V6b", "Theta_tilde at the centre: particle sum vs ray quadrature (3%)", std::fabs(pg / rg - 1) < 3e-2, pg / rg - 1);
    }
    if (g_fail) { std::printf("validation failed — results not used.\n"); return 1; }

    // ---------------- S3/S5/S7 : the fields at the Sun and the centre ----------------
    auto ucomp = [&](const F& f, int i) { return std::sqrt(f.ux[i] * f.ux[i] + f.uy[i] * f.uy[i] + f.uz[i] * f.uz[i]); };
    std::printf("\n== FIELDS (K = %.2f) ==\n", ARM_CONTRAST);
    auto report = [&](const char* nm, int i) {
        double tt = theta_tilde_m2(T2.th[i]);
        std::printf("%-8s mean column Theta_tilde = %.3e m^-2 (%.1f Msun/pc^2 equivalent) ; |u| = %.3e m = %.1f pitches ; Theta: excl %.2e  p %.2e  int %.2e ; bridge Z = %.3e\n",
                    nm, tt, sigma_eq(T2.th[i]), u_m(ucomp(T2, i)), u_m(ucomp(T2, i)) / LP, sig_excl * tt, sig_p * tt, sig_int * tt, Z_bridge(T2.zb[i]));
    };
    report("Sun", off_sun); report("centre", off_org);
    std::printf("ratio centre/Sun: Theta_tilde %.2f ; |u| %.2f ; bridge Z %.2f  (sigma-free patterns)\n",
                T2.th[off_org] / T2.th[off_sun], ucomp(T2, off_org) / ucomp(T2, off_sun), T2.zb[off_org] / T2.zb[off_sun]);
    std::printf("arm overdensity contribution at the Sun: Theta_tilde %+.3f%% ; |u| %+.3f%%\n", 100 * (T2.th[off_sun] / T1.th[off_sun] - 1), 100 * (ucomp(T2, off_sun) / ucomp(T1, off_sun) - 1));
    {   // tau_max for the dilute first-order form: longest in-plane columns from the Sun and the centre, analytic density x contrast bound
        double best = 0;
        for (int a = 0; a < 360; ++a) {
            double dx = std::sin(a * DEG), dy = std::cos(a * DEG);
            for (int src = 0; src < 2; ++src) { double col = 0, x0 = 0, y0 = src ? 0 : R0;
                for (double l = 0.01; l < 40.0; l += 0.02) col += n_total(D, x0 + l * dx, y0 + l * dy, 0.0) * 0.02;
                best = std::fmax(best, col / (KPC_M * KPC_M)); }
        }
        best *= ARM_CONTRAST;
        std::printf("longest in-plane column (Sun or centre, analytic, contrast bound) = %.3e m^-2 ; tau_max: excl %.2e  p %.2e  int %.2e -> first-order form %s\n",
                    best, sig_excl * best, sig_p * best, sig_int * best, sig_int * best <= 0.1 ? "valid (tau_max <= 0.1)" : "NOT valid");
    }
    std::printf("\nS5 pressure at the Sun, delta P / P_ref = -(1-s) Theta ; per bound with s -> 0: excl %.2e  p %.2e  int %.2e ; macro delta P = P_rad x that = %.2e Pa (int)\n",
                -sig_excl * theta_tilde_m2(T2.th[off_sun]), -sig_p * theta_tilde_m2(T2.th[off_sun]), -sig_int * theta_tilde_m2(T2.th[off_sun]),
                -law_I::P_rad * sig_int * theta_tilde_m2(T2.th[off_sun]));
    std::printf("S4 matter volume fraction at the Sun's neighbourhood phi_V ~ %.2e ; slow-passage term phi_V (1/s - 1) exceeds the blocking term sigma Theta_tilde only if s < %.2e (int bound)\n",
                0.1 * N_SUN / (PC_M * PC_M * PC_M) * V_P, (0.1 * N_SUN / (PC_M * PC_M * PC_M) * V_P) / (sig_int * theta_tilde_m2(T2.th[off_sun])));

    // ---------------- S6 : sheaths ----------------
    std::printf("\n== S6 SHEATHS (measured + near-extended ridge nodes, K = %.2f) ==\n", ARM_CONTRAST);
    // ring means for contrast
    std::vector<double> ringTh(NRING), ringU(NRING);
    for (int rr = 0; rr < NRING; ++rr) { double s = 0, u = 0; for (int j = 0; j < NAZ; ++j) { int i = off_ring + rr * NAZ + j; s += T2.th[i]; u += ucomp(T2, i); } ringTh[rr] = s / NAZ; ringU[rr] = u / NAZ; }
    auto ring_at = [&](const std::vector<double>& v, double R) { double f = (R - 1.0) / 0.5; int k = (int)std::floor(f); if (k < 0) k = 0; if (k > NRING - 2) k = NRING - 2; double t = std::min(1.0, std::max(0.0, f - k)); return v[k] * (1 - t) + v[k + 1] * t; };
    FILE* fr = std::fopen("gd11_ridge_metrics.csv", "w");
    std::fprintf(fr, "arm,node,tier,x,y,R,Theta_tilde_Msun_pc2,u_pitch,cos_u_t,cos_r_t,u_bulge_pitch,u_disc_pitch,cos_bulge_disc,contrast_Theta,contrast_u,Z_bridge\n");
    std::printf("%-9s %-7s %-9s %-9s %-10s %-10s %-10s %-10s %-10s %-9s\n", "arm", "nodes", "<|u.t|>", "<|r.t|>", "|diff|", "dTheta_ring", "d|u|_ring", "<cos b,d>", "bulge-dom", "R(ub=ud)");
    int k = 0; std::vector<double> M1u, M1r;
    for (auto& a : arms) {
        double su = 0, sr = 0, sd = 0, sct = 0, scu = 0, scs = 0; int nu = 0, nbd = 0; double Rx = -1;
        std::vector<std::pair<double, double>> ratio;
        for (size_t i = 0; i < a.nodes.size(); ++i, ++k) {
            const Node& nd = a.nodes[i]; int pi = off_ridge + k;
            size_t i0 = i ? i - 1 : i, i1 = i + 1 < a.nodes.size() ? i + 1 : i; double tx = a.nodes[i1].x - a.nodes[i0].x, ty = a.nodes[i1].y - a.nodes[i0].y, tl = std::hypot(tx, ty); tx /= tl; ty /= tl;
            double ux = T2.ux[pi], uy = T2.uy[pi], ul = std::hypot(ux, uy); double cu = ul > 0 ? std::fabs(ux * tx + uy * ty) / ul : 0, cr = std::fabs((nd.x * tx + nd.y * ty) / nd.R);
            double ubx = Fb.ux[pi], uby = Fb.uy[pi], ubz = Fb.uz[pi], udx = Dsc.ux[pi], udy = Dsc.uy[pi], udz = Dsc.uz[pi];
            double ub = std::sqrt(ubx * ubx + uby * uby + ubz * ubz), ud = std::sqrt(udx * udx + udy * udy + udz * udz), cbd = (ubx * udx + uby * udy + ubz * udz) / (ub * ud);
            double cth = T2.th[pi] / ring_at(ringTh, nd.R) - 1, cuu = ucomp(T2, pi) / ring_at(ringU, nd.R) - 1;
            std::fprintf(fr, "%s,%zu,%d,%.4f,%.4f,%.4f,%.3f,%.3f,%.4f,%.4f,%.3f,%.3f,%.4f,%.5f,%.5f,%.4e\n", a.name.c_str(), i, nd.tier, nd.x, nd.y, nd.R, sigma_eq(T2.th[pi]), u_m(ucomp(T2, pi)) / LP, cu, cr,
                         u_m(ub) / LP, u_m(ud) / LP, cbd, cth, cuu, Z_bridge(T2.zb[pi]));
            if (nd.tier <= 1) { nbd += (ub > ud); su += cu; sr += cr; sd += std::fabs(cu - cr); sct += cth; scu += cuu; scs += cbd; ++nu; ratio.push_back({nd.R, ub / ud}); M1u.push_back(cu); M1r.push_back(cr); }
        }
        std::sort(ratio.begin(), ratio.end());
        for (size_t i = 1; i < ratio.size(); ++i) if (ratio[i - 1].second >= 1.0 && ratio[i].second < 1.0) { Rx = ratio[i].first; break; }
        if (nu) std::printf("%-9s %-7d %-9.3f %-9.3f %-10.3f %+-10.2e %+-10.2e %-10.3f %-9.0f%% %s\n", a.name.c_str(), nu, su / nu, sr / nu, sd / nu, sct / nu, scu / nu, scs / nu, 100.0 * nbd / nu,
                            Rx > 0 ? (std::to_string(Rx).substr(0, 5) + " kpc").c_str() : "no crossing");
    }
    std::fclose(fr);
    double mu = 0, mr = 0; for (size_t i = 0; i < M1u.size(); ++i) { mu += M1u[i]; mr += M1r[i]; } mu /= M1u.size(); mr /= M1r.size();
    std::printf("all arms: <|u.t|> = %.3f ; <|r.t|> (geometric projection of a radial field) = %.3f ; difference %.3f\n", mu, mr, std::fabs(mu - mr));
    {   // M2 : flux carried along sheath cross-sections at R = 5, 8, 12 kpc
        std::printf("\nM2 displaced-volume flux carried along the sheath cross-sections (area pi sigma_in sigma_z) against the outward flux V_enc(R):\n");
        for (double R : {5.0, 8.0, 12.0}) {
            double sum = 0; int cross = 0; double Venc = N_enc(R) * V_P;
            int kk = 0; for (auto& a : arms) { for (size_t i = 0; i + 1 < a.nodes.size(); ++i) {
                const Node &p = a.nodes[i], &q = a.nodes[i + 1];
                if (p.tier <= 1 && q.tier <= 1 && (p.R - R) * (q.R - R) <= 0) {
                    const Node& nd = std::fabs(p.R - R) < std::fabs(q.R - R) ? p : q; int idx = std::fabs(p.R - R) < std::fabs(q.R - R) ? kk + (int)i : kk + (int)i + 1;
                    int pi = off_ridge + idx; double tx = q.x - p.x, ty = q.y - p.y, tl = std::hypot(tx, ty); tx /= tl; ty /= tl;
                    double ut = std::fabs(u_m(T2.ux[pi] * tx + T2.uy[pi] * ty)); sum += ut * PI * nd.sin * nd.sz * KPC_M * KPC_M; ++cross; } }
                kk += (int)a.nodes.size(); }
            std::printf("  R = %4.1f kpc : %d ridge crossings ; along-sheath flux %.3e m^3 ; V_enc %.3e m^3 ; fraction %.3e\n", R, cross, sum, Venc, sum / Venc);
        }
    }
    {   // classification
        std::printf("\nclassification (pre-registered): 'arms are channels for displacement along their length'\n");
        double M2 = 0; { double Venc = N_enc(8.0) * V_P, sum = 0; int kk = 0;
            for (auto& a : arms) { for (size_t i = 0; i + 1 < a.nodes.size(); ++i) { const Node &p = a.nodes[i], &q = a.nodes[i + 1];
                if (p.tier <= 1 && q.tier <= 1 && (p.R - 8.0) * (q.R - 8.0) <= 0) { int idx = kk + (int)i; int pi = off_ridge + idx; double tx = q.x - p.x, ty = q.y - p.y, tl = std::hypot(tx, ty); tx /= tl; ty /= tl;
                    sum += std::fabs(u_m(T2.ux[pi] * tx + T2.uy[pi] * ty)) * PI * p.sin * p.sz * KPC_M * KPC_M; } } kk += (int)a.nodes.size(); }
            M2 = sum / Venc; }
        const char* cls = (mu >= 0.5 && M2 >= 0.10) ? "supported" : ((std::fabs(mu - mr) <= 0.05 || M2 < 0.01) ? "not supported" : "marginal");
        std::printf("  M1 = %.3f against geometric %.3f (|diff| %.3f) ; M2(R = 8 kpc) = %.2e  ->  %s\n", mu, mr, std::fabs(mu - mr), M2, cls);
    }

    // ---------------- S7 : emission at depth, patterns ----------------
    std::printf("\n== S7 EMISSION AT DEPTH: patterns of the blocked-sky field (z_d = h1 Theta, h1 PENDING) ==\n");
    std::printf("Theta_tilde relative to the Sun along rings (sigma-free; multiply by sigma_occ for Theta):\n  R kpc : ");
    for (double R : {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 15.0}) std::printf("%5.1f ", R); std::printf("\n  ratio : ");
    for (double R : {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 15.0}) std::printf("%5.2f ", ring_at(ringTh, R) / ring_at(ringTh, R0)); std::printf("\n  bridge Z ratio (same rings): ");
    { std::vector<double> ringZ(NRING); for (int rr = 0; rr < NRING; ++rr) { double s = 0; for (int j = 0; j < NAZ; ++j) s += T2.zb[off_ring + rr * NAZ + j]; ringZ[rr] = s / NAZ; }
      for (double R : {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 15.0}) std::printf("%5.2f ", ring_at(ringZ, R) / ring_at(ringZ, R0)); std::printf("\n"); }
    std::printf("difference between the two kernels (1/r^2 against 1/r) over these rings is the open h(Theta) of GD06; both route values printed, neither chosen.\n");

    // viewer data
    {
        FILE* fj = std::fopen("mw_throughput.js", "w");
        std::fprintf(fj, "// Generated by gd11_static_disc_cascade.cpp. Static disc, no velocity input. x,y in kpc, Galactic plane.\n");
        std::fprintf(fj, "window.MW_THROUGHPUT={n:%d,half:%.1f,cases:[\n", GN, GM);
        auto emit = [&](const char* name, const char* unit, bool last, auto fn) {
            std::fprintf(fj, "{name:\"%s\",unit:\"%s\",v:[", name, unit);
            for (int j = 0; j < GN; ++j) for (int i = 0; i < GN; ++i) std::fprintf(fj, "%s%.4g", (i == 0 && j == 0) ? "" : ",", fn(off_grid + j * GN + i));
            std::fprintf(fj, "]}%s\n", last ? "" : ",");
        };
        emit("Mean baryon column seen from each point (blocked-sky field)", "Msun/pc2", false, [&](int i) { return sigma_eq(T2.th[i]); });
        emit("Displacement count |u| (spation pitches shifted)", "pitches", true, [&](int i) { return u_m(ucomp(T2, i)) / LP; });
        std::fprintf(fj, "]};\n"); std::fclose(fj);
    }
    std::printf("\nwrote gd11_ridge_metrics.csv mw_throughput.js\n");
    return 0;
}
