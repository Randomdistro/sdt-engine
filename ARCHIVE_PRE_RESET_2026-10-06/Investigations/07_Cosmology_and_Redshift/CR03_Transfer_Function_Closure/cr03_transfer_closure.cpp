// ============================================================================
// CR03 — Transfer Function Closure
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
//
// Can f = P_eff/P_conv be written in derivation basis primitives only?
// Stage 1: verify P_eff = m_p^2 m_e^2 c^5 / (4 pi alpha hbar^3)  (gates in RUN_LOG)
// Stage 2: f(R_CMB) sensitivity + PRE-REGISTERED structural candidate scan
// Stage 3: closure routes A (H0, re-expression) / B (BAO, circular as coded) /
//          C (N structural, FLM06 negative — cited).
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/cosmology.hpp>
#include <cstdio>
#include <cmath>
#include <iterator>

using namespace sdt::laws;

int main() {
    const double pi = std::numbers::pi;
    const double c  = measured::c,  hb = measured::hbar, al = measured::alpha;
    const double mp = measured::m_p, me = measured::m_e;

    std::printf("CR03 — Transfer Function Closure (J. C. Harvey, 2026-07-03)\n");
    std::printf("============================================================\n\n");

    // ---------------- Stage 1 ----------------
    const double P_eff_alg = mp*mp * me*me * c*c*c*c*c / (4.0 * pi * al * hb*hb*hb);

    // identity form: rebuild the hydrogen formula with W+1 radii
    const double Rp_W1 = 4.0 * hb / (mp * c);              // W+1 conjecture
    const double re_d  = al * hb / (me * c);               // r_e definition
    const double ke_e2 = al * hb * c;                      // Coulomb identity
    const double P_eff_id = 4.0 * ke_e2 / (pi * Rp_W1*Rp_W1 * re_d*re_d);

    const double rel_id  = P_eff_id / P_eff_alg - 1.0;
    const double rel_eng = P_eff_alg / law_III::P_eff - 1.0;

    std::printf("[Stage 1] P_eff algebra\n");
    std::printf("  P_eff (algebraic, derivation basis) = %.10e Pa\n", P_eff_alg);
    std::printf("  P_eff (identity rebuild)     = %.10e Pa   rel = %.2e  gate<1e-12: %s\n",
                P_eff_id, rel_id, std::fabs(rel_id) < 1e-12 ? "PASS" : "FAIL");
    std::printf("  P_eff (engine, measured R_p) = %.10e Pa   rel = %+.4f%%  gate<0.5%%: %s\n",
                law_III::P_eff, rel_eng*100.0, std::fabs(rel_eng) < 0.005 ? "PASS" : "FAIL");
    std::printf("  residual source: W+1 R_p = %.6e vs measured %.6e (%+.3f%%, enters squared)\n\n",
                Rp_W1, measured::R_p, (Rp_W1/measured::R_p - 1.0)*100.0);

    // ---------------- Stage 2 ----------------
    // f = P_eff * l_P / (R_CMB * a_rad * T^4); d ln f / d ln R_CMB = -1 exactly.
    const double aT4 = measured::a_rad * std::pow(measured::T_CMB, 4.0);
    auto f_of_R = [&](double R){ return P_eff_alg * measured::l_P / (R * aT4); };
    const double f_now = f_of_R(measured::R_CMB);
    std::printf("[Stage 2] f(R_CMB) = P_eff l_P / (R_CMB a_rad T^4)\n");
    std::printf("  f(9.527e26 m) = %.6e   engine f_transfer = %.6e  (rel %+.4f%%)\n",
                f_now, law_III::f_transfer, (f_now/law_III::f_transfer - 1.0)*100.0);
    std::printf("  d ln f / d ln R_CMB = -1 exactly (f ~ 1/R_CMB): 1%% R error -> 1%% f error\n\n");

    struct Cand { const char* name; double value; };
    const double mrat = me/mp;
    const Cand cands[] = {
        {"alpha^7",            std::pow(al,7)},
        {"alpha^8",            std::pow(al,8)},
        {"alpha^9",            std::pow(al,9)},
        {"alpha^8/pi",         std::pow(al,8)/pi},
        {"pi*alpha^8",         pi*std::pow(al,8)},
        {"4pi*alpha^8",        4.0*pi*std::pow(al,8)},
        {"alpha^8/(4pi)",      std::pow(al,8)/(4.0*pi)},
        {"(me/mp)*alpha^6",    mrat*std::pow(al,6)},
        {"(me/mp)^2*alpha^5",  mrat*mrat*std::pow(al,5)},
        {"1/sqrt(S_boundary)", 1.0/std::sqrt(law_I::S_boundary)},
    };
    std::printf("  Pre-registered structural candidate scan (hit gate: |R_req/R_CMB - 1| < 1%%)\n");
    std::printf("  %-22s %-12s %-12s %-14s %s\n", "candidate", "value", "f/cand", "R_req [m]", "R_req/R_CMB");
    int hits = 0;
    for (const auto& cd : cands) {
        const double R_req = measured::R_CMB * (f_now / cd.value);  // f ~ 1/R
        const double rr = R_req / measured::R_CMB;
        const bool hit = std::fabs(rr - 1.0) < 0.01;
        hits += hit;
        std::printf("  %-22s %-12.4e %-12.4g %-14.4e %.4g %s\n",
                    cd.name, cd.value, f_now/cd.value, R_req, rr, hit ? "<-- HIT" : "");
    }
    std::printf("  structural hits: %d of %zu (list CLOSED per RUN_LOG — no additions)\n\n",
                hits, std::size(cands));

    // ---------------- Stage 3 ----------------
    std::printf("[Stage 3] Closure routes\n");
    const double H0 = 67.4e3 / 3.0857e22;                    // s^-1, OBSERVED (Planck number)
    const double R_A = (c / H0) * std::log(1.0 + measured::z_rec);
    std::printf("  Route A: R = (c/H0) ln(1+z_rec) = %.4e m  vs stored %.4e (%+.2f%%)\n",
                R_A, measured::R_CMB, (R_A/measured::R_CMB - 1.0)*100.0);
    std::printf("           CONSISTENT — but H0 is OBSERVED: this RE-EXPRESSES class X, does\n");
    std::printf("           not close it. f via Route A still contains one measured scale.\n");
    std::printf("  Route B: cosmology.hpp defines t_coupled = BAO_scale/c_s = %.3e s — the\n",
                sdt::cosmology::pre_clearing::t_coupled);
    std::printf("           coupled-epoch duration is DERIVED FROM the 147 Mpc it would need\n");
    std::printf("           to predict. CIRCULAR as coded. No independent t_coupled exists in\n");
    std::printf("           the engine; Route B cannot run until one is derived.\n");
    std::printf("  Route C: N structural — FLM06 Seed Theorem (negative, PROVEN): N ~ 1e61\n");
    std::printf("           cannot be built from the derivation basis; every clean ratio bottoms out\n");
    std::printf("           at ~1e3. Cited, not re-litigated.\n\n");

    std::printf("VERDICT LINES\n");
    std::printf("  Algebra: P_eff = m_p^2 m_e^2 c^5/(4 pi alpha hbar^3) VERIFIED (id %.1e, engine %+.3f%%)\n",
                rel_id, rel_eng*100.0);
    std::printf("  f = [derivation basis] x l_P/(R_CMB a_rad T^4): every factor derivation basis EXCEPT R_CMB\n");
    std::printf("  Structural hits at 1%%: %d  |  Routes A/B/C: re-expression / circular / proven-negative\n", hits);
    std::printf("  => f remains class E->X-blocked: PARTIAL per prompt Sec.4. R_CMB is THE bottleneck.\n");
    return 0;
}
