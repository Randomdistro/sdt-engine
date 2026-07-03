// ═══════════════════════════════════════════════════════════════════════
// NP06 (CQ-50) — Gear-Frequency Binding Functional: E_bind = hbar*d_omega?
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
// All contact graphs, derivation rules, predictions and gates pre-committed
// in RUN_LOG.md BEFORE this file. Sealed anchors from
// NP05_Gate_G1_Price_of_Displacement/sealed/answers.json (AME2020),
// echoed below with provenance; committed predictions precede comparison.
// R5 guard in force: hbar*Omega_rim = mc^2 is a FORBIDDEN IDENTITY route.
// ═══════════════════════════════════════════════════════════════════════

#include <sdt/laws.hpp>
#include <cmath>
#include <cstdio>

int main() {
    using namespace sdt::laws;
    using namespace sdt::laws::measured;

    const double mpc2 = m_p * c * c / MeV_to_J;          // MeV
    const double Omega0 = m_p * c * c / hbar;            // rad/s (free rim frequency)

    std::printf("NP06 (CQ-50) — Gear-Frequency Binding Functional (J. C. Harvey, 2026-07-03)\n");
    std::printf("Hypothesis: E_bind = hbar * d_omega from a no-slip mesh-coupling pull.\n");
    std::printf("==========================================================================\n\n");

    // ---------- R5 trap, shown once ----------
    std::printf("[R5] hbar*Omega_rim = %.4f MeV = m_p c^2 EXACTLY -> any 'Delta omega' that\n",
                hbar * Omega0 / MeV_to_J);
    std::printf("     reduces to Delta(mc^2)/hbar restates E=mc^2 and 'predicts' binding by\n");
    std::printf("     definition. FORBIDDEN-IDENTITY. Not used anywhere below.\n\n");

    // ---------- D2: the kappa_geom derivation attempt ----------
    std::printf("[D2] kappa_geom from the committed no-slip contact geometry (ring contact s=2R):\n");
    std::printf("     available dimensionless inventory (committed in RUN_LOG before running):\n");
    std::printf("       overlap depth / R        = 0        (tangent contact)\n");
    std::printf("       contact-arc fraction     = 0        (point contact)\n");
    std::printf("       axis-angle cosines       = O(1), bounded by 1\n");
    std::printf("       winding / rim-speed ratio= 1        (identical rotors)\n");
    std::printf("     A rigid no-slip constraint LOCKS PHASE but stores no energy; a normal-mode\n");
    std::printf("     SPLIT requires a stiffness U(dphi). No inventory item supplies an energy\n");
    std::printf("     scale: every derivable kappa is 0 or O(1).\n");
    std::printf("     REQUIRED couplings (reverse ledger, REQUIRED-NOT-DERIVED, see below):\n");

    // Sealed anchors (NP05 sealed/answers.json, AME2020) — echoed with provenance
    const double B_d = 2.224573, B_t = 8.481821, B_h = 7.718058, B_a = 28.295674;
    const double B_Li6 = 31.994564, B_Be9 = 58.165000;
    const double Q[8] = {23.846528, 19.813853, 20.577616, 17.589280,
                          4.032675,  3.268912,  1.474317,  1.573652};
    const char* Qn[8] = {"R1 dd->a   ", "R2 tp->a   ", "R3 hn->a   ", "R4 dt->an  ",
                         "R5 dd->tp  ", "R6 dd->hn  ", "R7 ad->Li6 ", "R8 2an->Be9"};
    const double H2_eV = 4.52;   // OBSERVED anchor stated in the PROMPT

    const double kap_d = B_d / mpc2;                 // per-bond, 1 bond
    const double kap_t = (B_t / 3.0) / mpc2;
    const double kap_a = (B_a / 6.0) / mpc2;
    const double kap_H2 = (H2_eV * 1e-6) / mpc2;
    std::printf("       kappa_req(d)  = %.3e   kappa_req(t/bond) = %.3e\n", kap_d, kap_t);
    std::printf("       kappa_req(a/bond) = %.3e   kappa_req(H2) = %.3e\n", kap_a, kap_H2);
    std::printf("     -> spread d..a = x%.2f at IDENTICAL committed contact geometry;\n", kap_a / kap_d);
    std::printf("        spread H2..d = x%.1e with NO kinematic quantity to carry it.\n", kap_d / kap_H2);
    std::printf("     VERDICT D2: kappa_geom is NOT derivable at CALIBRATED(0) from the no-slip\n");
    std::printf("     mesh. Gate G-omega is DEAD AT THE DERIVATION STAGE (committed rule).\n\n");

    // ---------- D3: the H2 anchor ----------
    std::printf("[D3] H2 anchor (committed prediction BEFORE comparison):\n");
    std::printf("     protons at 1.4 a0 = %.3e fm; rim radius R_p = %.3f fm -> s/2R_p = %.0f\n",
                1.4 * a_0 * 1e15, R_p * 1e15, (1.4 * a_0) / (2.0 * R_p));
    std::printf("     rims DO NOT TOUCH -> contact-mesh prediction: epsilon(H2) = 0\n");
    std::printf("     measured: %.2f eV  -> structural FAIL (0 vs 4.52 eV; +/-15%% gate)\n", H2_eV);
    std::printf("     borrowed-kappa check (kappa_d, CALIBRATED(1)): epsilon = %.3f MeV vs 4.52 eV\n",
                B_d);
    std::printf("     -> off by x%.1e. The anchor fails BOTH ways: a contact mesh gives zero,\n",
                B_d * 1e6 / H2_eV);
    std::printf("     a contact-blind mesh gives 10^6 too much. The coupling must be carried by\n");
    std::printf("     a RANGED interaction (a 1/r wake) — which is not a frequency pull.\n\n");

    // ---------- D4: nuclear gate, failure-shape demo (CALIBRATED(1) declared) ----------
    std::printf("[D4] Nuclear set — failure-shape demo with epsilon locked to the deuteron\n");
    std::printf("     (CALIBRATED(1); per RUN_LOG this CANNOT pass G-omega even if it landed):\n");
    const double eps = B_d;   // per-bond energy calibrated on d (1 bond)
    struct Row { const char* n; int bonds; double meas; };
    const Row rows[] = {{"d   ", 1, B_d}, {"t   ", 3, B_t}, {"h   ", 3, B_h},
                        {"a   ", 6, B_a}, {"Li6 ", 9, B_Li6}, {"Be9 ", 14, B_Be9}};
    const int NB = 6;
    double bondsBE[6];
    for (int i = 0; i < NB; ++i) {
        const double pred = rows[i].bonds * eps;
        bondsBE[i] = pred;
        const double e = (pred - rows[i].meas) / rows[i].meas * 100.0;
        std::printf("     %s bonds=%2d  pred = %7.3f  sealed = %7.3f  (%+7.1f%%)  %s\n",
                    rows[i].n, rows[i].bonds, pred, rows[i].meas, e,
                    (std::fabs(e) <= 15.0 ? "within 15%" : "FAIL(15%)"));
    }
    // Q-values from the bond ledger: Q = BE(products) - BE(reactants)
    const double pd = bondsBE[0], pt = bondsBE[1], ph = bondsBE[2], pa = bondsBE[3];
    const double pLi6 = bondsBE[4], pBe9 = bondsBE[5];
    const double Qpred[8] = { pa - 2*pd, pa - pt, pa - ph, (pa + 0) - (pd + pt),
                              (pt + 0) - 2*pd, (ph + 0) - 2*pd, pLi6 - (pa + pd),
                              pBe9 - 2*pa };
    int qfail = 0;
    for (int i = 0; i < 8; ++i) {
        const double e = (Qpred[i] - Q[i]) / Q[i] * 100.0;
        if (std::fabs(e) > 15.0) ++qfail;
        std::printf("     %s pred Q = %7.3f  sealed = %7.3f  (%+7.1f%%)  %s\n",
                    Qn[i], Qpred[i], Q[i], e, (std::fabs(e) <= 15.0 ? "within 15%" : "FAIL(15%)"));
    }
    std::printf("     -> %d of 8 Q-values FAIL at +/-15%% even WITH the CALIBRATED(1) crutch.\n", qfail);
    std::printf("     Diagnostic (a): alpha under-binds at %+.1f%% — the even mesh does NOT\n",
                (pa - B_a) / B_a * 100.0);
    std::printf("     naturally over-bind alpha; the volume-form's alpha anomaly persists.\n");
    std::printf("     Diagnostic (b): Li6/Be9 over-bind per contact (+202%%/+183%% on R7/R8) —\n");
    std::printf("     loose clusters need contacts SOFTER than the core, again geometry-blind.\n\n");

    // ---------- Verdict ----------
    std::printf("==========================================================================\n");
    std::printf("VERDICT (numeric):\n");
    std::printf("  D2 kappa_geom      : NOT DERIVABLE at CALIBRATED(0) — no energy scale in the\n");
    std::printf("                       kinematic no-slip mesh -> G-omega DEAD at derivation\n");
    std::printf("  D3 H2 anchor       : contact mesh predicts 0 vs 4.52 eV (structural FAIL);\n");
    std::printf("                       borrowed kappa off by ~10^6\n");
    std::printf("  D4 nuclear shape   : with CALIBRATED(1) crutch: %d/8 Q FAIL, alpha %+.1f%%,\n",
                qfail, (pa - B_a) / B_a * 100.0);
    std::printf("                       per-bond kappa spread x%.2f at identical contact geometry\n",
                kap_a / kap_d);
    std::printf("  KILL               : E_bind = hbar*d_omega (kinematic mesh pull) is KILLED.\n");
    std::printf("  SUCCESSOR (named in RUN_LOG before the run, already partly paid): NP17\n");
    std::printf("  shared-electron Coulomb well — supplies the missing interaction scale\n");
    std::printf("  (alpha hbar c) and range (1/r); deuteron already lands at -1.06%%.\n");
    std::printf("  STRUCTURAL RESULT (PROMPT section 5): TWO clean kills — binding is neither a\n");
    std::printf("  static volume price (NP05/CQ-32) nor a kinematic frequency pull (NP06). It\n");
    std::printf("  requires a mediated ranged interaction: the shared-electron well + the\n");
    std::printf("  coordination-dependent lock term (NP10's constraint curve).\n");
    return 0;
}
