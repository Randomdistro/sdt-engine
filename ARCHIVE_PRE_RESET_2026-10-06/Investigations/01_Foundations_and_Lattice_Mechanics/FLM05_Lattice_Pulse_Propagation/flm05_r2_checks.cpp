// FLM05 R2 (2026-10-06) — Rotorpause construction, the 1/k^2 redshift form, three proton trefoil sizes, torus-derived mass.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;

static double bisect(double m1, double m2, double d) {          // zero of m1/r^2 - m2/(d-r)^2 on (0,d)
    double lo = 1e-9 * d, hi = d * (1 - 1e-9);
    for (int i = 0; i < 200; ++i) { double mid = 0.5 * (lo + hi), f = m1 / (mid * mid) - m2 / ((d - mid) * (d - mid)); if (f > 0) lo = mid; else hi = mid; }
    return 0.5 * (lo + hi);
}
static void gl(int n, std::vector<double>& x, std::vector<double>& w) {
    x.resize(n); w.resize(n);
    for (int i = 0; i < n; ++i) { double z = std::cos(PI * (i + 0.75) / (n + 0.5)), pp = 0;
        for (int it = 0; it < 100; ++it) { double p1 = 1, p2 = 0; for (int j = 0; j < n; ++j) { double p3 = p2; p2 = p1; p1 = ((2.0*j + 1) * z * p2 - j * p3) / (j + 1); } pp = n * (z * p1 - p2) / (z*z - 1); double dz = p1 / pp; z -= dz; if (std::fabs(dz) < 1e-15) break; }
        x[i] = z; w[i] = 2.0 / ((1 - z*z) * pp * pp); }
}
static double torus_numeric(double R, double r) {
    std::vector<double> x, w; gl(48, x, w); double s = 0;
    for (int i = 0; i < 48; ++i) for (int j = 0; j < 48; ++j) {
        double rho = 0.5 * r * (x[i] + 1), phi = PI * (x[j] + 1);
        s += (0.5 * r * w[i]) * (PI * w[j]) * 2 * PI * (R + rho * std::cos(phi)) * rho;
    }
    return s;
}

int main() {
    std::printf("FLM05 R2 — checks (pre-registered 2026-10-06)\n=============================================\n\n");
    int fails = 0;
    const double hb = M::hbar, c = M::c, mp = M::m_p, me = M::m_e, Rp = M::R_p, re = M::r_e, a0 = M::a_0, al = M::alpha, lP = M::l_P;

    // V1
    double em = 81.30057, f_cf = std::sqrt(em) / (1 + std::sqrt(em)), f_num = bisect(em, 1.0, 1.0);
    double rr_cf = 1.0 / (1.0 + std::sqrt(me / mp)), rr_num = bisect(mp, me, 1.0);
    bool v1 = std::fabs(f_num - f_cf) < 1e-12 && std::fabs(f_cf - 0.90017) < 1e-5 && std::fabs(rr_num - rr_cf) < 1e-12;
    std::printf("[V1] neutral point: Earth-Moon fraction numeric %.9f closed form %.9f (known 0.90017); p-e numeric %.12f closed form %.12f -> %s\n", f_num, f_cf, rr_num, rr_cf, v1 ? "PASS" : "FAIL");
    if (!v1) ++fails;
    // V2
    double Vn = torus_numeric(1.0, 0.8164965809), Vc = 2 * PI * PI * 1.0 * 0.8164965809 * 0.8164965809;
    bool v2 = std::fabs(Vn - Vc) / Vc < 1e-9;
    std::printf("[V2] torus volume numeric %.12f closed form %.12f (rel %.1e) -> %s\n\n", Vn, Vc, (Vn - Vc) / Vc, v2 ? "PASS" : "FAIL");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // T1
    std::printf("[T1] Rotorpause (CONSTRUCTION; input m_p/m_e = %.4f): r_rp/a0 = %.6f (numeric %.6f); flail angle sqrt(m_e/m_p) = %.4f deg\n\n", mp / me, rr_cf, rr_num, std::sqrt(me / mp) * 180 / PI);

    // T2
    double k = bridge::k_proton_surface, z1 = 1.0 / (k * k), z2 = re / Rp, rel = std::fabs(z1 - z2) / z2;
    double kb = bridge::koppa_per_baryon, zb = kb / Rp;
    double lam_p = hb / (mp * c), hier_ep = al * (lam_p / lP) * (lam_p / lP) / (me / mp), r_ratio = re / kb;
    std::printf("[T2] k(R_p) = %.6f ; 1/k^2 = %.6f ; r_e/R_p = %.6f ; rel diff %.2e -> stray-form criterion (>1e-3) %s\n", k, z1, z2, rel, rel > 1e-3 ? "MET (forms differ)" : "not met (forms agree)");
    std::printf("     k^2 r_e = %.6e m (= R_p to the engine's rounding: the k-ladder gives koppa_H = R_p/k^2 = r_e = %.6e m)\n", k * k * re, re);
    std::printf("     baryon koppa = %.6e m ; z_b = koppa_b/R_p = %.4e (not 3.35)\n", kb, zb);
    std::printf("     r_e/koppa_b = %.6e ; Coulomb/gravity (e-p) = alpha (lam_p/l_P)^2/(m_e/m_p) = %.6e ; rel diff %.2e\n\n", r_ratio, hier_ep, std::fabs(r_ratio - hier_ep) / hier_ep);

    // T3
    const double asp = std::sqrt(2.0 / 3.0), vT = std::sqrt(0.4), vP = std::sqrt(0.6);
    struct Sz { const char* nm; double R, a; const char* note; } S[3] = {
        {"FLM05  (T1 = R_p, T2 = T1 sqrt(2/3))", Rp, Rp * asp, ""},
        {"PPT01  (2,3) rule A, action closure", hb / (mp * vT * c), hb / (mp * vP * c), ""},
        {"canon  law_VI::confinement::trefoil_major_radius", law_VI::confinement::trefoil_major_radius, law_VI::confinement::trefoil_major_radius * asp, "minor radius assumed = rule-A aspect (canon gives only R)"}};
    std::printf("[T3] proton trefoil sizes in use\n     %-44s | R_major [m]   a [m]        | R/R_FLM05 | V_torus [m^3] | m(Law IV) [kg] | m/m_p      | V_torus/V_disp,p\n", "source");
    for (auto& s : S) {
        double V = 2 * PI * PI * s.R * s.a * s.a, m = law_I::Phi * V / (3.0 * M::l_P * M::l_P * M::l_P * c * c);
        std::printf("     %-44s | %.4e  %.4e | %.4f    | %.4e   | %.4e   | %.3e | %.3e %s\n", s.nm, s.R, s.a, s.R / Rp, V, m, m / mp, V / law_IV::V_disp_p, s.note);
    }
    std::printf("\nSUMMARY: validations met; stray form agrees with r_e/R_p to %.1e; torus-derived mass differs from m_p by factors ", rel);
    for (auto& s : S) { double V = 2 * PI * PI * s.R * s.a * s.a, m = law_I::Phi * V / (3.0 * M::l_P * M::l_P * M::l_P * c * c); std::printf("%.2e ", m / mp); }
    std::printf("\n");
    return 0;
}
