// PPT06 R2 (2026-10-06) — audit of the traction headline results: reproduction, dependence map, geometry dependence of T,
// W=1 control, arithmetic identities. Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <numbers>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
static const double PI = std::numbers::pi;

static double vph(double alpha, double a0, double Rp) { return std::sqrt(alpha * alpha * a0 / Rp); }                       // engine-literal form
static double vph_m(double alpha, double me, double Rp) { return std::sqrt(alpha * M::hbar / (me * M::c * Rp)); }       // a0 = hbar/(m_e c alpha)

int main() {
    std::printf("PPT06 R2 — traction audit (pre-registered 2026-10-06)\n=====================================================\n\n");
    int fails = 0;
    const double c = M::c, hb = M::hbar, mp = M::m_p, me = M::m_e, al = M::alpha, a0 = M::a_0, Rp = M::R_p, re = M::r_e;
    const double lam = hb / (mp * c), mu = mp / me, Rlock = law_III::R_p_lock, Rp22 = 8.4075e-16;
    const int W = law_VI::winding::W_proton;

    // ---- V1
    const double k = bridge::k_proton_surface;
    double e1 = std::fabs(k - std::sqrt(Rp / re)) / k;
    bool v1 = e1 < 1e-12 && std::fabs(k - 0.5464) < 5e-5 && std::fabs(Rlock / Rp - 1) < 3e-4;
    std::printf("[V1] k_proton_surface = %.6f ; sqrt(R_p/r_e) rel. diff %.2e ; R_p_lock = %.5e m vs measured %.5e m (%+.4f%%) -> %s\n", k, e1, Rlock, Rp, (Rlock / Rp - 1) * 100, v1 ? "PASS" : "FAIL");
    if (!v1) ++fails;
    // ---- V2
    double w2 = 0;
    for (double f : {0.5, 1.0, 2.0}) { double R = Rp * f; w2 = std::max(w2, std::fabs((law_VI::traction::omega_demand / law_VI::traction::omega_max(R)) / (3 * R / lam) - 1)); }
    double gear = (3.0 * c / lam) / (al * c / a0);
    double e2b = std::fabs(gear / (3 * mu / (al * al)) - 1);
    bool v2 = w2 < 1e-12 && e2b < 1e-9;
    std::printf("[V2] omega_demand/omega_max = 3R/lam_p: worst rel. diff %.2e ; omega_p/omega_e = 3 mu/alpha^2: rel. diff %.2e -> %s\n\n", w2, e2b, v2 ? "PASS" : "FAIL");
    if (!v2) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // ---- T1
    std::printf("[T1] reproduction from engine symbols (record prints: 1.831c, 4.27e24, 3.563e23, 12, 1.03e8)\n");
    std::printf("     %-22s %-12s %-10s %-12s %-12s %-9s\n", "R_p used", "R_p [m]", "v_ph/c", "w_demand", "w_max", "T");
    struct RP { const char* nm; double R; } rps[] = {{"measured (engine)", Rp}, {"lock 4*lam_p", Rlock}, {"CODATA 2022", Rp22}};
    double vlo = 1e9, vhi = 0;
    for (auto& r : rps) { double v = std::sqrt(re / r.R), T = law_VI::traction::omega_demand / (c / r.R); vlo = std::min(vlo, v); vhi = std::max(vhi, v);
        std::printf("     %-22s %.5e  %.5f    %.4e   %.4e   %.4f\n", r.nm, r.R, v, law_VI::traction::omega_demand, c / r.R, T); }
    std::printf("     engine: v_phase_proton_surface/c = %.5f ; traction_ratio_proton (literal 3(W+1)) = %.1f ; gear_ratio_nuclear_atomic = %.4e\n", law_VI::traction::v_phase_proton_surface / c, law_VI::traction::traction_ratio_proton, law_VI::traction::gear_ratio_nuclear_atomic);
    bool rep = std::fabs(law_VI::traction::v_phase_proton_surface / c - 1.831) < 1.5e-3 && std::fabs(law_VI::traction::omega_demand / 4.27e24 - 1) < 2e-3 && std::fabs(c / Rp / 3.563e23 - 1) < 2e-3 && std::fabs(law_VI::traction::omega_demand / (c / Rp) - 12) < 0.01 && std::fabs(law_VI::traction::gear_ratio_nuclear_atomic / 1.03e8 - 1) < 5e-3;
    std::printf("     record values reproduced to printed precision: %s\n\n", rep ? "yes" : "NO");

    // ---- T2
    std::printf("[T2] dependence of v_phase/c = sqrt(r_e/R_p) (finite differences, +/-1e-4)\n");
    auto dln = [&](auto f, double x0) { double h = 1e-4; return (std::log(f(x0 * (1 + h))) - std::log(f(x0 * (1 - h)))) / (std::log(1 + h) - std::log(1 - h)); };
    double eA = dln([&](double x) { return vph(x, a0, Rp); }, al), eB = dln([&](double x) { return vph(al, x, Rp); }, a0), eR = dln([&](double x) { return vph(al, a0, x); }, Rp);
    std::printf("     engine form (alpha, a_0, R_p independent): d ln v/d ln alpha = %+.4f ; a_0 = %+.4f ; R_p = %+.4f\n", eA, eB, eR);
    double mA = dln([&](double x) { return vph_m(x, me, Rp); }, al), mE = dln([&](double x) { return vph_m(al, x, Rp); }, me), mR = dln([&](double x) { return vph_m(al, me, x); }, Rp);
    std::printf("     a_0 = hbar/(m_e c alpha): d ln v/d ln alpha = %+.4f ; m_e = %+.4f ; R_p = %+.4f ; m_p = 0 (R_p held)\n", mA, mE, mR);
    bool atomic_dep = std::fabs(eA) > 1e-6 || std::fabs(eB) > 1e-6 || std::fabs(mA) > 1e-6 || std::fabs(mE) > 1e-6;
    std::printf("     'independent of atomic-scale input' rejected (|exponent| > 1e-6 for alpha, a_0 or m_e): %s\n", atomic_dep ? "YES (rejected)" : "no");
    double v2lock = al * mu / (W + 1), v2meas = re / Rp;
    std::printf("     R_p = 4 lam_p: v^2/c^2 = alpha mu/(W+1) = %.6f (alpha = %.6e, mu = %.4f) ; r_e/R_p (measured) = %.6f\n", v2lock, al, mu, v2meas);
    double target = 10.0 / 3.0;
    struct { const char* nm; double R, s; } sg[] = {{"CODATA 2018 0.8414(19) fm", 8.414e-16, 1.9e-18}, {"CODATA 2022 8.4075(64)e-16 m", Rp22, 6.4e-19}};
    bool excl = true;
    for (auto& s : sg) { double v2 = re / s.R, sv2 = v2 * s.s / s.R, z = (v2 - target) / sv2; if (std::fabs(z) <= 3) excl = false;
        std::printf("     %-30s v^2/c^2 = %.5f +/- %.5f ; 10/3 = %.5f ; deviation %+.1f sigma\n", s.nm, v2, sv2, target, z); }
    std::printf("     lock form (no R_p uncertainty; alpha, mu exact in-engine): %.6f vs 10/3: %+.3f%%\n", v2lock, (v2lock / target - 1) * 100);
    std::printf("     sqrt(10/3) excluded as the exact form (> 3 sigma both R_p values): %s\n\n", excl ? "YES" : "no");

    // ---- T3
    std::printf("[T3] T = q (v_T/c)(R_b/R_t), R_b = measured R_p\n");
    auto Tval = [&](int q, double vT, double Rt, double Rb) { return q * (vT / c) * (Rb / Rt); };
    struct G { const char* nm; double vT, Rt; } gs[8]; int ng = 0;
    gs[ng++] = {"PPT05 recipe (v_T=c/sqrt3, R_t=lam/sqrt3)", c / std::sqrt(3.0), lam / std::sqrt(3.0)};
    const int pp = 2, qq = 3;
    struct NN { const char* nm; int nT, nP; } rules[] = {{"PPT01 rule A (1,1)", 1, 1}, {"PPT01 rule B (2,3)", 2, 3}, {"PPT01 rule C (3,2)", 3, 2}};
    for (auto& r : rules) { double x = std::sqrt(double(qq) * r.nT / (double(pp) * r.nP)), rr = (double(qq) / pp) / x, vT = c / std::sqrt(1 + rr * rr), Rt = r.nT * lam / (vT / c);
        // R_t = n_T hbar/(m_p v_T) = n_T lam c / v_T
        gs[ng++] = {r.nm, vT, Rt}; }
    double Tmin = 1e9, Tmax = 0;
    std::printf("     %-44s v_T/c     R_t [fm]   R_t/lam   T\n", "geometry");
    for (int i = 0; i < ng; ++i) { double T = Tval(3, gs[i].vT, gs[i].Rt, Rp); Tmin = std::min(Tmin, T); Tmax = std::max(Tmax, T);
        std::printf("     %-44s %.4f    %.5f    %.4f    %.4f\n", gs[i].nm, gs[i].vT / c, gs[i].Rt * 1e15, gs[i].Rt / lam, T); }
    bool geo = (Tmax / Tmin - 1) > 0.01;
    std::printf("     T spans %.4f .. %.4f (ratio %.3f) ; 'T = 12 is a property of winding and boundary alone' rejected (spread > 1%%): %s\n", Tmin, Tmax, Tmax / Tmin, geo ? "YES (rejected)" : "no");
    // control: PPT05 recipe at q = 1, R_t = sqrt3 lam, v_T = c/sqrt3, R_b = (W+1) lam = 2 lam
    double Tc = Tval(1, c / std::sqrt(3.0), std::sqrt(3.0) * lam, 2.0 * lam);
    std::printf("     control W = 1 (PPT05 recipe at q = 1, R_b = 2 lam): T_c = %.6f ; integer form 3(W+1) at W = 1 = 6 ; ratio %.4f -> control %s\n", Tc, Tc / 6, std::fabs(Tc / 6 - 1) > 1e-6 ? "FAILS" : "passes");
    std::printf("     the factor '3' in 3R_p/lam_p: q = %d ; q^2/3 = %.4f ; coincide at q = 3 only (q = 1: %.4f vs %.4f)\n\n", qq, qq * qq / 3.0, 1.0, 1.0 / 3.0);

    // ---- T4
    double Tm = law_VI::traction::omega_demand / (c / Rp), vphc = std::sqrt(re / Rp), qprime = Tm / vphc;
    std::printf("[T4] two demands at R_p: v_phase/c = %.4f ; omega_demand R_p/c = %.4f ; deficit omega-form (omega_demand - omega_max) R_p/c = %.4f\n", vphc, Tm, Tm - 1);
    std::printf("     record 'T = (v_phase/c) x q': q' = T/(v_phase/c) = %.4f (record prints 6.55; q = 3 gives %.4f) ; holds if within 1%% at q = 3: %s\n\n", qprime, vphc * 3, std::fabs(Tm / (vphc * 3) - 1) < 0.01 ? "yes" : "NO");

    // ---- T5
    double printed = 3 * mu / al, correct = 3 * mu / (al * al);
    std::printf("[T5] gear ratio: omega_p/omega_e = %.5e ; printed '3 (m_p/m_e)(1/alpha)' = %.5e ; 3 mu/alpha^2 = %.5e ; printed/actual = %.5f (= alpha = %.5f)\n", gear, printed, correct, printed / gear, al);
    std::printf("     printed decomposition correct (within 1%%): %s\n\n", std::fabs(printed / gear - 1) < 0.01 ? "yes" : "NO");

    // ---- T6
    double E = mp * c * c / 1.602176634e-13, vT2 = std::pow(law_VI::topology::v_toroidal(2, 3) / c, 2);
    std::printf("[T6] energy partition of m_p c^2 = %.3f MeV: PPT06 table toroidal 1/3 = %.3f MeV, poloidal 2/3 = %.3f MeV ; laws.hpp law_VI::topology::v_toroidal(2,3): v_T^2/c^2 = %.4f -> %.3f MeV, v_P^2 -> %.3f MeV ; consistent (1e-6): %s\n\n",
                E, E / 3, 2 * E / 3, vT2, E * vT2, E * (1 - vT2), std::fabs(vT2 - 1.0 / 3) < 1e-6 ? "yes" : "NO");

    // ---- T7 (report only)
    double Nc = 4 * PI * Rp * Rp / (M::l_P * M::l_P), Ftot = Nc * (law_I::epsilon / M::l_P) * Tm, Fcoul = al * hb * c / (Rp * Rp);
    double Focc = (PI / 4) * law_III::P_eff * std::pow(Rp, 4) / std::pow(2 * Rp, 2);
    std::printf("[T7] report-only: N_contact = %.4e ; F_total = N (eps/l_P) T = %.4e N ; F_total x N = %.4e N ; alpha hbar c/R_p^2 = %.4e N ; law_III F (two R_p spheres, r = 2R_p) = %.4e N\n", Nc, Ftot, Ftot * law_I::N, Fcoul, Focc);
    std::printf("     ratios: F_total/Coulomb-form = %.3e ; F_total x N / Coulomb-form = %.3e ; F_total x N / law_III = %.3e (no accumulation rule stated; no criterion)\n\n", Ftot / Fcoul, Ftot * law_I::N / Fcoul, Ftot * law_I::N / Focc);

    // ---- T8
    std::printf("[T8] v_phase/c over R_p in {measured, lock, CODATA 2022}: %.5f .. %.5f ; spread %.1f ppm\n", vlo, vhi, (vhi / vlo - 1) * 1e6);
    std::printf("     the 1.83c seat in NP15/NP20/NP27 shares R_p (FLM07); NP15 mu_n and NP20 Q_beta are not recomputed here.\n");
    return 0;
}
