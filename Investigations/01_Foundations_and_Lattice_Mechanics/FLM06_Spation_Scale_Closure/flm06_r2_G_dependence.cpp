// FLM06 R2 (2026-10-05) — which SDT outputs carry G (through the stored l_P) and which do not.
// Pre-registered in R2_REOPEN_2026-10-05.md §4 before this file existed. Author: J. C. Harvey, Melbourne.
// G appears only as the scaled quantity of the test (CODATA 2018 comparison value); never in an SDT formula.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
#include <functional>
#include <vector>
using namespace sdt::laws;
namespace M = sdt::laws::measured;

int main() {
    std::printf("FLM06 R2 — G-dependence ledger (pre-registered 2026-10-05)\n===========================================================\n\n");
    const double hb = M::hbar, c = M::c, mp = M::m_p, me = M::m_e, Rp = M::R_p;
    const double G0 = 6.67430e-11;                 // COMPARISON ONLY (CODATA 2018)
    const double GMsun = 1.32712440018e20;         // IAU nominal solar mass parameter (measured product; VERIFY)
    int fails = 0;

    // V1
    const double lP_calc = std::sqrt(hb * G0 / (c * c * c));
    bool v1 = std::fabs(lP_calc - M::l_P) / M::l_P < 1e-5;
    std::printf("[V1] sqrt(hbar G/c^3) = %.6e m vs stored l_P = %.6e m (rel %.2e) -> %s\n", lP_calc, M::l_P, (lP_calc - M::l_P) / M::l_P, v1 ? "PASS" : "FAIL");
    if (!v1) ++fails;
    // V2
    const double kS = bridge::koppa_Sun, kGM = GMsun / (c * c);
    bool v2 = std::fabs(kS - kGM) / kGM < 5e-4;
    std::printf("[V2] bridge::koppa_Sun = %.4f m vs GM_sun/c^2 = %.4f m (rel %+.2e) -> %s\n", kS, kGM, (kS - kGM) / kGM, v2 ? "PASS" : "FAIL");
    if (!v2) ++fails;
    // V3
    double worst = 0;
    for (double m : {me, mp, 1.78266192e-27 /*1 GeV/c^2*/, 1e-12 /*1 ng in kg*/}) {
        double kop = G0 * m / (c * c), lam = hb / (m * c), l = std::sqrt(kop * lam);
        worst = std::max(worst, std::fabs(l / lP_calc - 1.0));
    }
    bool v3 = worst < 1e-12;
    std::printf("[V3] sqrt(koppa(m) lambda(m)) / l_P(G) for m = m_e, m_p, 1 GeV, 1 ng: worst |ratio - 1| = %.2e -> %s  (construction: koppa lambda = G hbar/c^3)\n\n", worst, v3 ? "PASS" : "FAIL");
    if (!v3) ++fails;
    std::printf("VALIDATIONS: %s\n\n", fails == 0 ? "met" : "NOT MET -> G0");
    if (fails) return 1;

    // T1
    const double RS = M::R_Sun, AU = M::AU;
    struct Out { const char* nm; std::function<double(double)> f; double expect; };
    auto lP = [&](double s) { return std::sqrt(hb * G0 * s / (c * c * c)); };
    auto kb_eng = [&](double s) { return lP(s) * lP(s) / (Rp / 4.0); };
    std::vector<Out> outs = {
        {"l_P                                   ", [&](double s) { return lP(s); }, 0.5},
        {"koppa/baryon, SI route G m_p/c^2      ", [&](double s) { return G0 * s * mp / (c * c); }, 1.0},
        {"koppa/baryon, engine route l_P^2/(Rp/4)", kb_eng, 1.0},
        {"koppa_Sun = v^2 R/c^2 (orbital data)  ", [&](double) { return kS; }, 0.0},
        {"z_Sun = koppa_Sun/R_Sun               ", [&](double) { return kS / RS; }, 0.0},
        {"v_orbital at 1 AU = c sqrt(koppa/r)   ", [&](double) { return c * std::sqrt(kS / AU); }, 0.0},
        {"solar-limb deflection 4 koppa/b       ", [&](double) { return 4 * kS / RS; }, 0.0},
        {"N_b,Sun = koppa_Sun / koppa_b (engine)", [&](double s) { return kS / kb_eng(s); }, -1.0},
        {"M_Sun [kg] = GM/G                     ", [&](double s) { return GMsun / (G0 * s); }, -1.0},
        {"F_C/F_G (p-p) = k_e e^2/(m_p c^2 koppa_b)", [&](double s) { return coulomb_identity::k_e_e2 / (mp * c * c * kb_eng(s)); }, -1.0},
    };
    std::printf("[T1] d ln X / d ln G  (G scaled by 1 +- 1%%; every directly measured length, speed, action and mass held fixed)\n");
    std::printf("     output                                   exponent   expected\n");
    const double lo = 0.99, hi = 1.01;
    bool per_baryon_all_pm1 = true, kin_all_zero = true;
    for (auto& o : outs) {
        double e = (std::log(o.f(hi)) - std::log(o.f(lo))) / (std::log(hi) - std::log(lo));
        std::printf("     %s %+8.4f   %+5.1f\n", o.nm, e, o.expect);
        bool is_per_b = (o.expect != 0.0 && o.expect != 0.5);
        if (is_per_b && std::fabs(std::fabs(e) - 1.0) > 1e-3) per_baryon_all_pm1 = false;
        if (o.expect == 0.0 && std::fabs(e) > 1e-9) kin_all_zero = false;
    }
    std::printf("\n     every per-baryon route at exponent +-1: %s ; every body-level kinematic output at exponent 0: %s\n", per_baryon_all_pm1 ? "yes" : "NO", kin_all_zero ? "yes" : "NO");
    std::printf("     rejection criterion (a registered per-baryon route with exponent 0 exists): %s\n", per_baryon_all_pm1 ? "not met" : "MET");
    std::printf("     requirement for an independent source: a baryon count of one large body, not obtained through G, to better than G's relative uncertainty 2.2e-5\n\n");
    std::printf("SUMMARY: validations met; per-baryon routes all carry G (exponent +-1): %s; body-level kinematics G-independent: %s\n", per_baryon_all_pm1 ? "yes" : "no", kin_all_zero ? "yes" : "no");
    return 0;
}
