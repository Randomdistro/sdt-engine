// ============================================================================
// NP07 — Primordial Lithium Resolution — grammar + mechanism-map tool
//
// P0: grammar selection rule (NATIVE, exact integers; cross-checks NP18)
// P1: Be-7 first-electron binding scale from whitelist {alpha, m_e, c}
// P2: required pre-EC destruction fraction (RIVAL-COMPARISON bookkeeping)
// P3: closure decision — committed OPEN unless native history + measured
//     destruction cross-sections are in-chain (they are not in this repo)
//
// Anchors: Spite plateau Li-7/H = (1.58 +/- 0.31)e-10  [OBSERVED, Sbordone 2010]
//          BBN prediction (4.68 +/- 0.67)e-10          [RIVAL comparison column ONLY]
//
// Author: J. C. Harvey, Melbourne. Executed 2026-07-03.
// ============================================================================

#include <sdt/laws.hpp>
#include <sdt/nuclear.hpp>
#include <cstdio>
#include <cmath>

int main() {
    using namespace sdt::laws;
    using sdt::nuclear::alpha_grammar;
    using sdt::nuclear::h3_grammar;

    std::printf("NP07 — Primordial Lithium — grammar + mechanism map\n");
    std::printf("==========================================================================\n\n");

    // ------------------------------------------------------------------ P0
    std::printf("[P0] grammar selection rule (NATIVE, exact integers)\n");
    const auto be7a = alpha_grammar(4, 7);
    const auto be7h = h3_grammar(4, 7);
    const auto li7 = alpha_grammar(3, 7);
    const auto li6 = alpha_grammar(3, 6);
    // EC vector in (n_d, n_t): (-3, +2)
    const int ec_nd = be7a.n_d - 3, ec_nt = be7a.n_t + 2;
    const bool p0 =
        (be7a.n_d == 3 && be7a.n_t == -1 && !be7a.valid) &&
        (be7h.n_d == 2 && be7h.n_t == 0 && be7h.valid) &&
        (li7.n_d == 0 && li7.n_t == 1 && li7.valid) &&
        (li6.n_d == 1 && li6.n_t == 0 && li6.valid) &&
        (ec_nd == li7.n_d && ec_nt == li7.n_t);
    std::printf("     Be-7 alpha-grammar (n_d,n_t) = (%d,%d) valid=%s  <- UNDERFLOW (n_t<0)\n",
                be7a.n_d, be7a.n_t, be7a.valid ? "yes" : "NO");
    std::printf("     Be-7 H3-grammar    (n_d,n_t) = (%d,%d) valid=%s  <- He-3 core, EC isotope\n",
                be7h.n_d, be7h.n_t, be7h.valid ? "yes" : "no");
    std::printf("     Li-7 (0,1) on-lattice: (%d,%d) valid=%s\n", li7.n_d, li7.n_t,
                li7.valid ? "yes" : "no");
    std::printf("     Li-6 (1,0) on-lattice: (%d,%d) valid=%s\n", li6.n_d, li6.n_t,
                li6.valid ? "yes" : "no");
    std::printf("     EC vector (-3,+2): Be-7 -> (%d,%d) == Li-7  %s\n", ec_nd, ec_nt,
                (ec_nd == 0 && ec_nt == 1) ? "EXACT" : "MISMATCH");
    std::printf("     Grammar reading: Be-7 is not alpha-constructible; it exists only in the\n");
    std::printf("     alternate He-3-core grammar and is EC-FORCED toward Li-7 (NP18 Phase 0).\n");
    std::printf("     Li-6 route: alpha+d. Li-7 routes: alpha+t direct, or Be-7 EC.\n");
    std::printf("     P0 gate: %s\n\n", p0 ? "PASS" : "FAIL");

    // ------------------------------------------------------------------ P1
    // ENGINE MACHINERY ONLY: seat velocity from laws.hpp atomic::bohr_velocity
    // (the k-ladder kinematics already in the engine), stripping cost = the
    // kinetic reorganisation 1/2 m_e v^2. No outside formalism imported.
    std::printf("[P1] Be-7 first-electron seat scale (engine atomic:: kinematics only)\n");
    const double v_seat_H = atomic::bohr_velocity(1, 1);   // innermost seat, Z=1
    const double v_seat_Be = atomic::bohr_velocity(4, 1);  // innermost seat, Z=4
    const double E_H = 0.5 * measured::m_e * v_seat_H * v_seat_H / measured::eV_to_J;
    const double E_Be3 = 0.5 * measured::m_e * v_seat_Be * v_seat_Be / measured::eV_to_J;
    const double ref = 217.7;
    const double err = std::fabs(E_Be3 - ref) / ref * 100.0;
    const bool p1 = (err < 0.5);
    std::printf("     v_seat(Z=1) = %.6e m/s -> strip cost 1/2 m_e v^2 = %.4f eV\n", v_seat_H, E_H);
    std::printf("     v_seat(Z=4) = %.6e m/s -> strip cost 1/2 m_e v^2 = %.2f eV  "
                "(ref 217.7, err %.3f%%)\n", v_seat_Be, E_Be3, err);
    std::printf("     SDT-EC rule: EC needs a seated electron at the scaffold. A fully-stripped\n");
    std::printf("     Be-7 cannot EC; the EC clock starts only when the plasma is cool enough\n");
    std::printf("     for Be-7 to hold this ~218 eV seat (~16x the hydrogen seat cost).\n");
    std::printf("     Chain: laws.hpp atomic::bohr_velocity (engine k-ladder) + kinematics. No\n");
    std::printf("     outside formalism in the chain.\n");
    std::printf("     P1 gate: %s\n\n", p1 ? "PASS" : "FAIL");

    // ------------------------------------------------------------------ P2
    std::printf("[P2] required pre-EC destruction fraction (RIVAL-COMPARISON bookkeeping)\n");
    const double obs = 1.58e-10, dobs = 0.31e-10;   // OBSERVED (Spite plateau)
    const double bbn = 4.68e-10, dbbn = 0.67e-10;   // RIVAL comparison column ONLY
    const double f = 1.0 - obs / bbn;
    const double df = std::sqrt(std::pow(dobs / bbn, 2.0)
                              + std::pow(obs * dbbn / (bbn * bbn), 2.0));
    std::printf("     Observed Li-7/H (Spite)  = (1.58 +/- 0.31)e-10   [OBSERVED anchor]\n");
    std::printf("     BBN predicted            = (4.68 +/- 0.67)e-10   [RIVAL column only]\n");
    std::printf("     IF the rival production number were taken at face value, ANY pre-EC\n");
    std::printf("     destruction mechanism must remove f = %.1f%% +/- %.1f%% of mass-7.\n",
                f * 100.0, df * 100.0);
    std::printf("     SIGN ANALYSIS (committed): delayed EC alone conserves mass-7 (Be-7 EC\n");
    std::printf("     -> Li-7 whenever it happens) and CANNOT reduce Li-7. Reduction requires\n");
    std::printf("     destruction DURING the ionised window: p + Be-7 -> B-8, B-8 -> Be-8 -> 2\n");
    std::printf("     alpha (mass-7 leaves the ledger). The SDT EC-blocking rule LENGTHENS that\n");
    std::printf("     window — the mechanism has the right SIGN.\n\n");

    // ------------------------------------------------------------------ P3
    std::printf("[P3] closure decision (committed pre-run)\n");
    std::printf("     Needed for a quantitative SDT resolution, and NOT available in-chain:\n");
    std::printf("       (i)  a native SDT primordial thermal/density history T(t), n_p(t)\n");
    std::printf("            — SDT rejects the expansion framework; its own cyclic cosmology\n");
    std::printf("            is uncommitted. No native history exists to integrate over.\n");
    std::printf("       (ii) measured sigma(p + Be-7 -> B-8) capture data (NACRE / EXFOR) —\n");
    std::printf("            legitimate OBSERVED input, but not present in this repository.\n");
    std::printf("     Neither is available -> the committed verdict applies: OPEN.\n");
    std::printf("     NO number is claimed for the final Li-7/H. The deliverable is the\n");
    std::printf("     mechanism map above + the named data needs.\n\n");

    std::printf("==========================================================================\n");
    std::printf("NP07 SUMMARY\n");
    std::printf("  P0 grammar selection rule   : %s  [NATIVE]\n", p0 ? "PASS" : "FAIL");
    std::printf("  P1 EC-electron binding scale: %s  [COMPUTED, scale-setting]\n",
                p1 ? "PASS" : "FAIL");
    std::printf("  P2 destruction requirement  : f = %.1f%% +/- %.1f%%  [RIVAL-COMPARISON]\n",
                f * 100.0, df * 100.0);
    std::printf("  P3 quantitative resolution  : OPEN — no native history, no sigma data\n");
    std::printf("  OVERALL: mechanism map earned; resolution honestly OPEN.\n");
    return (p0 && p1) ? 0 : 1;
}
