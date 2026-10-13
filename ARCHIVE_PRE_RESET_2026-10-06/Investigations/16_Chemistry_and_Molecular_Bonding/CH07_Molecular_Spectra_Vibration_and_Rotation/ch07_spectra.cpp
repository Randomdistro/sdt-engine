// ============================================================================
//  CH07 — Molecular Spectra: Vibration & Rotation (wake mechanics only)
//  Author: J. C. Harvey, Melbourne · 2026-07-05
//  P1: does the NP17 shared-seat well carry a restoring stiffness? (registered
//      prediction in RUN_LOG: NO — scale-free 1/R has no interior minimum)
//  P2: mass-only isotopologue predictions (zero new inputs; k = charge geometry)
//  P3: rotation — DECLARED IDENTITY (imported winding quantiser, flagged)
//  Gates committed in RUN_LOG.md before this file. Exit honest.
// ============================================================================
#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;

static int fails = 0;

int main() {
    const double ahc  = coulomb_identity::k_e_e2;  // [J·m]
    const double hbar = measured::hbar;
    const double c    = measured::c;
    const double amu  = 1.66053906660e-27;         // [kg] unit bridge
    const double pi   = 3.14159265358979323846;

    std::printf("================================================================\n");
    std::printf("  CH07 — Molecular Spectra: Vibration & Rotation\n");
    std::printf("  Author: J. C. Harvey, Melbourne · 2026-07-05\n");
    std::printf("================================================================\n\n");

    std::printf("hbar ENTRY AUDIT (flagged up front, per RUN_LOG faith ledger):\n");
    std::printf("  (1) rotational ladder step  = wake-winding quantiser, ASSERTED (PPT06/APS04)\n");
    std::printf("  (2) line-position bridge E=hbar*omega, ASSERTED (emission bridge)\n");
    std::printf("  -> anything using them is capped IDENTITY/CONVERGENCE, never NATIVE.\n\n");

    // ------------------------------------------------------------------
    // P1 — native stiffness from the NP17 shared-seat well.
    // E(R,x) = (ahc/R) * g(x),  g(x) = 1 + 1/(2x) - 4/sqrt(1/4 + x^2)
    // (p-p repulsion + e-e repulsion - 4 p-e attractions, seats at radius xR
    //  on the perpendicular bisector). Scale-free by construction.
    // ------------------------------------------------------------------
    std::printf("P1  NATIVE STIFFNESS (NP17 shared-seat well, pure machinery)\n");
    double gbest = 1e9, xbest = 0;
    for (double x = 0.02; x <= 2.0; x += 1e-5) {
        double g = 1.0 + 1.0 / (2.0 * x) - 4.0 / std::sqrt(0.25 + x * x);
        if (g < gbest) { gbest = g; xbest = x; }
    }
    std::printf("    seat minimisation: g* = %.5f at x* = %.4f (H2+: exact -3 at midpoint —\n", gbest, xbest);
    std::printf("    same machinery as NP17's deuteron factor)\n");
    std::printf("    well form: E(R) = g* ahc / R  (scale-free)\n");
    double Re_H2 = 0.7414e-10;
    double d2E = 2.0 * gbest * ahc / (Re_H2 * Re_H2 * Re_H2); // d2/dR2 of g*ahc/R
    std::printf("    d2E/dR2 at measured Re(H2): %+.3e N/m  -> %s\n", d2E,
                d2E > 0 ? "restoring" : "NON-restoring (no interior minimum)");
    if (d2E > 0.0) {
        std::printf("    (unexpected against registered prediction — would proceed to 10%% gate)\n");
    } else {
        std::printf("    REGISTERED PREDICTION CONFIRMED: a pure 1/R shared-seat well carries NO\n");
        std::printf("    stiffness at any R. The vibrational k requires the short-range wall —\n");
        std::printf("    the CONTACT-SATURATION closure (same closure NP17 owes for the alpha).\n");
        std::printf("    -> P1 native chain: OPEN (honest FAIL of the prompt's P1 gate).\n");
    }
    fails += (d2E > 0 ? 0 : 1); // prompt P1 gate not met -> honest fail counted
    std::printf("\n");

    // ------------------------------------------------------------------
    // P2 — back-solved k (DECLARED circular for parent nu, caps at C) +
    //      mass-only isotopologue predictions (zero new inputs).
    // ------------------------------------------------------------------
    std::printf("P2  MASS-ONLY ISOTOPOLOGUE PREDICTIONS (k = charge geometry, unchanged)\n");
    const double mH = 1.00782503, mD = 2.01410178, mCl = 34.96885268;
    const double mC12 = 12.0, mC13 = 13.00335484, mO16 = 15.99491462;
    auto mu = [](double a, double b) { return a * b / (a + b); };
    struct Iso { const char* parent; const char* child; double muP, muC, weP, weC_meas; };
    Iso iso[3] = {
        {"HCl", "DCl",   mu(mH, mCl),  mu(mD, mCl),  2990.946, 2145.163},
        {"H2",  "D2",    mu(mH, mH),   mu(mD, mD),   4401.21,  3115.50},
        {"CO",  "13CO",  mu(mC12,mO16),mu(mC13,mO16),2169.813, 2121.42},
    };
    for (auto& s : iso) {
        double k = (s.muP * amu) * std::pow(2.0 * pi * c * (s.weP * 100.0), 2.0); // back-solved, declared
        double pred = s.weP * std::sqrt(s.muP / s.muC);
        double err = (pred - s.weC_meas) / s.weC_meas * 100.0;
        bool ok = std::fabs(err) < 0.5;
        if (!ok) ++fails;
        std::printf("    %-4s k=%7.1f N/m (back-solved, circular for parent nu) -> %-5s pred %9.2f cm-1  meas %9.2f  err %+7.3f%% %s\n",
                    s.parent, k, s.child, pred, s.weC_meas, err, ok ? "[PASS]" : "[FAIL]");
    }
    std::printf("    sqrt(k/mu) ORDERING check (back-solved k, reported only): k(H2) < k(HCl) < k(CO)\n\n");

    // ------------------------------------------------------------------
    // P3 — rotation: B = hbar/(4 pi c I), measured R. DECLARED IDENTITY.
    // ------------------------------------------------------------------
    std::printf("P3  ROTATION (DECLARED IDENTITY — measured R is spectroscopic in origin,\n");
    std::printf("    and the ladder step is the ASSERTED winding quantiser)\n");
    struct Rot { const char* name; double mu_u, R_A, B_meas; };
    Rot rot[2] = { {"CO", mu(mC12, mO16), 1.1283, 1.93128}, {"HCl", mu(mH, mCl), 1.2746, 10.5934} };
    for (auto& r : rot) {
        double I = r.mu_u * amu * std::pow(r.R_A * 1e-10, 2.0);
        double B = hbar / (4.0 * pi * c * I) / 100.0; // cm-1
        std::printf("    %-3s: B = %8.4f cm-1 (meas %8.4f, %+0.2f%%) — IDENTITY, earns nothing\n",
                    r.name, B, r.B_meas, (B - r.B_meas) / r.B_meas * 100.0);
    }
    std::printf("    even-2B spacing: consequence of the imported ladder — NOT demonstrated natively.\n\n");

    // ------------------------------------------------------------------
    // P4 — novel mass-only rotational prediction: B(DCl) from B(HCl).
    // ------------------------------------------------------------------
    std::printf("P4  NOVEL (mass-only, zero new inputs): B(DCl) = B(HCl) x mu_HCl/mu_DCl\n");
    double Bpred = 10.5934 * (mu(mH, mCl) / mu(mD, mCl));
    double Berr = (Bpred - 5.4488) / 5.4488 * 100.0;
    bool ok4 = std::fabs(Berr) < 1.0;
    if (!ok4) ++fails;
    std::printf("    B(DCl) pred %7.4f cm-1  meas 5.4488  err %+6.3f%% %s\n\n", Bpred, Berr, ok4 ? "[PASS]" : "[FAIL]");

    std::printf("P3-UNIFICATION (one winding quantiser for all channels): OPEN — owner\n");
    std::printf("    PPT06/APS04, live door FLM14 rotation DOF. Declared, not attempted.\n\n");

    std::printf("================================================================\n");
    std::printf("  CH07 SUMMARY\n");
    std::printf("  P1 native k : OPEN — scale-free shared-seat well has no stiffness;\n");
    std::printf("                missing closure = contact-saturation wall (ROOT-CONTACT)\n");
    std::printf("  P2 isotopes : mass-only predictions, all gates as printed\n");
    std::printf("  P3 rotation : IDENTITY (declared) · P3-unification: OPEN\n");
    std::printf("  committed-gate failures (incl. honest P1): %d\n", fails);
    std::printf("  Exit: %d\n", fails == 0 ? 0 : 1);
    std::printf("================================================================\n");
    return fails == 0 ? 0 : 1;
}
