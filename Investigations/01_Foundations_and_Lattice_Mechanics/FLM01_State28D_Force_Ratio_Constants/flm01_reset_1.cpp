// FLM01 blank-slate pass (2026-10-13). Registration: FLM01_RESET_ASSESSMENT_2026-10-13.md sections 0-2 (written before this file existed).
// Candidate derivations of the two un-derived State28D scales (1e10 Pa/m and 1e-20 J); no fitting.
// Author: J. C. Harvey, Melbourne.
#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>
using namespace sdt::laws;
namespace M = sdt::laws::measured;
int main() {
    std::printf("FLM01 blank-slate pass (registered in FLM01_RESET_ASSESSMENT_2026-10-13.md)\n=======================================================================\n\n");
    const double eps = law_I::epsilon, Phi = law_I::Phi, Pc = law_I::P_conv, lP = M::l_P == 0 ? 0 : M::l_P; (void)lP;
    std::printf("epsilon = a_rad T0^4 l_P^3 = %.4e J ; N = R_CMB/l_P = %.4e ; Phi = N eps = %.4e J ; P_conv = Phi/l_P^3 = %.4e Pa ; law_III::P_eff = %.4e Pa ; R_p_lock = %.4e m ; r_e = %.4e m ; l_P = %.4e m\n\n", eps, law_I::N, Phi, Pc, law_III::P_eff, law_III::R_p_lock, M::r_e, M::l_P);
    // prompt Phase 1 literal
    const double ae = 1e-15, ap = 1e-18, T5lit = Phi * eps / ((ae - ap) * ae * ae * ae);
    std::printf("Prompt Phase 1 as written: P_atom = Phi eps / a_e^3 = %.4e [J^2/m^3], T5 = Phi eps / ((a_e - a_p) a_e^3) = %.4e [J^2/m^4] ; the target is [Pa/m] = [J/m^4]: units differ by a factor of an energy -> dimensionally invalid (D3)\n", Phi * eps / (ae * ae * ae), T5lit);
    const double Phi5 = 0.25 * M::m_e * M::c * M::c;
    std::printf("Prompt Phase 2: Phi_5 = m_e c^2 / 4 = %.4e J (code scale 1e-20 J: ratio %.3e, log10 %.2f)\n\n", Phi5, Phi5 / 1e-20, std::log10(Phi5 / 1e-20));
    struct C { const char* nm; double v; double target; };
    const double L[3] = {law_III::R_p_lock, M::r_e, M::l_P}; const char* Ln[3] = {"R_p_lock", "r_e", "l_P"};
    const double Pn[2] = {law_III::P_eff, Pc}; const char* Pnn[2] = {"P_eff", "P_conv"};
    std::printf("Pressure-gradient candidates [Pa/m] against 1e10 Pa/m:\n"); int within = 0, n = 0; double lo = 1e300, hi = 0;
    for (int i = 0; i < 2; ++i) for (int j = 0; j < 3; ++j) { double v = Pn[i] / L[j]; double r = v / 1e10; ++n; lo = std::fmin(lo, v); hi = std::fmax(hi, v); bool w = std::fabs(r - 1) <= 0.2; within += w; std::printf("  %s / %s = %.4e Pa/m : ratio %.3e (log10 %.2f) %s\n", Pnn[i], Ln[j], v, r, std::log10(r), w ? "WITHIN 20%" : ""); }
    std::printf("Energy candidates [J] against 1e-20 J:\n");
    C en[4] = {{"m_e c^2 / 4", Phi5, 1e-20}, {"law_III::P_eff law_III::R_p_lock^3", law_III::P_eff * law_III::R_p_lock * law_III::R_p_lock * law_III::R_p_lock, 1e-20}, {"epsilon", eps, 1e-20}, {"Phi", Phi, 1e-20}};
    for (auto& c : en) { double r = c.v / c.target; ++n; lo = std::fmin(lo, c.v); hi = std::fmax(hi, c.v); bool w = std::fabs(r - 1) <= 0.2; within += w; std::printf("  %-18s = %.4e J : ratio %.3e (log10 %.2f) %s\n", c.nm, c.v, r, std::log10(r), w ? "WITHIN 20%" : ""); }
    std::printf("\ncandidates within 20%% of their code scale: %d of 10\n", within);
    std::printf("Look-elsewhere: a log-uniform candidate over 30 decades has a chance of 2*log10(1.2/0.8..)=%.3f of landing within 20%% of a given scale per candidate; for 10 candidates the expected number inside is about %.2f\n", std::log10(1.2 / 0.8) / 30.0, 10.0 * std::log10(1.2 / 0.8) / 30.0);
    std::printf("Outcome by the corrected rule: %s\n", within == 0 ? "no dimensionally valid candidate within 20% of either scale -> both scales CALIBRATED/OPEN (as the engine header records)" : "a candidate lies within 20%: report with its route and the look-elsewhere count above; not a derivation without a stated route");
    return 0;
}
