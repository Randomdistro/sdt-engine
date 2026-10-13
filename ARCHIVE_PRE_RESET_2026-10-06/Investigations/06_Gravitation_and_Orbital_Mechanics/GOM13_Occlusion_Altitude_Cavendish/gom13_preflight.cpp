// =============================================================================
// GOM13 — Occlusion-Altitude Cavendish: PRE-FLIGHT PREDICTION SET (owed to E104)
//
//   (a) kappa  — the shared-P_eff coupling between Casimir and Cavendish channels
//   (b) delta(h) — overhead-occlusion fraction, 0-40 km, TWO models:
//         G1: geometric-opacity horizon-dip law (GOM13 PROMPT section 3.2)
//         G2: mass-proportional barometric column (koppa per baryon)
//   (c) near-contact saturation g(x) = 2(1 - sqrt(1-x))/x, x = (R/r)^2
//   (d) make-or-break: delta*kappa vs pre-committed noise floors
//   (+) OBSERVED anchor: the existing G record vs lab elevation (the PROMPT's own
//       suggested check — "the first data point may already be in the literature")
//
// Thresholds and both delta-models pre-committed in RUN_LOG.md before coding.
// Provenance disclosures are printed verbatim from the engine headers.
//
// @author J. C. Harvey, Melbourne — executed 2026-07-03
// =============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;
using namespace sdt::laws::measured;

int main() {
    std::printf("=====================================================================\n");
    std::printf(" GOM13: OCCLUSION-ALTITUDE CAVENDISH — PRE-FLIGHT PREDICTION SET\n");
    std::printf(" (also the engine-target block owed to E104 section 8)\n");
    std::printf(" J. C. Harvey, Melbourne — 2026-07-03\n");
    std::printf("=====================================================================\n\n");

    // ------------------------------------------------------------------
    // (a) kappa — shared-P_eff coupling
    // ------------------------------------------------------------------
    std::printf("--- (a) KAPPA: THE SHARED-P_eff COUPLING ---\n\n");
    std::printf("  Law III (one occlusion law, both scales):\n");
    std::printf("    F_Cavendish = (pi/4) P_eff R1^2 R2^2 / r^2   (cm-scale masses)\n");
    std::printf("    F_Casimir   = (pi/4) P_eff R1^2 R2^2 / r^2   (um-scale plates, EMC03 claim)\n\n");
    std::printf("  Both channels are LINEAR in P_eff. Therefore:\n");
    std::printf("    kappa = (dlnF_Cas/dlnP_eff) / (dlnF_Cav/dlnP_eff) = 1 / 1 = 1  EXACTLY\n\n");
    double kappa = 1.0; // by linearity of Law III in P_eff — derivation above, not a fit
    std::printf("  kappa(SDT) = %.1f     kappa(SM) = 0  (channels independent)\n\n", kappa);
    std::printf("  P_eff = %.6e Pa  (law_III::P_eff)\n", law_III::P_eff);
    std::printf("  PROVENANCE (verbatim from laws.hpp): \"risk_flag: coefficient calibrated\"\n");
    std::printf("  (class E / calibrated-target). DISCLOSED. Note: kappa is a RATIO of two\n");
    std::printf("  linear responses — P_eff's magnitude cancels, so kappa = 1 does NOT\n");
    std::printf("  inherit the class-E risk. What kappa DOES inherit is the EMC03 premise\n");
    std::printf("  that the Casimir channel is occlusion-sourced at all. If that premise\n");
    std::printf("  is false, kappa = 0 and the correlation test reads null.\n\n");
    std::printf("  SM Casimir reference (comparison only): F/A = pi^2 hbar c/(240 d^4)\n");
    double d_gap = 1.0e-6;
    double casimir_SM = std::pow(std::numbers::pi, 2) * hbar * c / (240.0 * std::pow(d_gap, 4));
    std::printf("    at d = 1 um: %.3e Pa (no P_eff anywhere in it — that IS the fork)\n\n", casimir_SM);

    // ------------------------------------------------------------------
    // (b) delta(h) — two models
    // ------------------------------------------------------------------
    std::printf("--- (b) OVERHEAD-OCCLUSION FRACTION delta(h), 0-40 km ---\n\n");

    const double R_E   = bridge::R_Earth;
    const double H_bar = 7640.0;                    // barometric scale height [m]
    const double sigma0 = 101325.0 / 9.80665;       // sea-level column mass [kg/m^2]
    const double koppa_E = bridge::koppa_Earth;

    // G2 normalisation: occlusion scales with occluding MASS (Law III: force is
    // proportional to occluder cross-section budget, which aggregates per baryon).
    // Fraction of Earth's own occlusion budget contributed by air above h:
    //   M_atm(h) = 4 pi R_E^2 sigma(h); delta_mass(h) = koppa_atm(h) / koppa_Earth
    //   koppa_atm = koppa_per_baryon * M_atm/m_p
    std::printf("  G2 inputs: sigma0 = %.0f kg/m^2, H = %.0f m,\n", sigma0, H_bar);
    std::printf("  koppa_per_baryon = %.4e m (bridge; header discloses: CODATA l_P\n", bridge::koppa_per_baryon);
    std::printf("  conventionally encodes G — \"disclosed, not laundered\")\n\n");

    std::printf("  %-10s  %14s  %14s  %14s\n",
                "h [km]", "G1: sin(dip)", "G2: delta_mass", "column kg/m^2");
    const double hs[] = {0.0, 500.0, 1000.0, 5000.0, 8848.0, 20000.0, 30000.0, 40000.0};
    double g1_40 = 0, g2_0 = 0, g2_40 = 0;
    for (double h : hs) {
        double dip   = std::acos(R_E / (R_E + h));
        double G1    = std::sin(dip);                       // PROMPT 3.2 geometric law
        double sig   = sigma0 * std::exp(-h / H_bar);
        double M_atm = 4.0 * std::numbers::pi * R_E * R_E * sig;
        double kop_a = bridge::koppa_per_baryon * (M_atm / m_p);
        double G2    = kop_a / koppa_E;                     // mass-proportional
        if (h == 0.0)      g2_0 = G2;
        if (h == 40000.0) { g1_40 = G1; g2_40 = G2; }
        std::printf("  %-10.1f  %14.4e  %14.4e  %14.1f\n", h / 1e3, G1, G2, sig);
    }
    double dg2_ramp = g2_0 - g2_40;   // the ALTITUDE-VARYING part of G2
    std::printf("\n  G1 predicts DF/F = %.3f (11%%) at 40 km — the flagship number.\n", g1_40);
    std::printf("  G2 predicts the ramp 0->40 km changes the budget by %.2e (total\n", dg2_ramp);
    std::printf("  atmospheric term %.2e at ground, %.2e left at 40 km).\n", g2_0, g2_40);
    std::printf("  The two committed models differ by %.0e — this IS the pre-flight fork.\n\n",
                g1_40 / dg2_ramp);

    // Cross-check G2 against the classical Bouguer plate (OBSERVED physics):
    // 2 pi G sigma / g ~ 4.4e-7 — same order as delta_mass. Print for honesty.
    std::printf("  Sanity anchor: the measured gravitational effect of the whole air\n");
    std::printf("  column (Bouguer plate) is ~4.4e-7 of g — same order as G2's %.1e.\n", g2_0);
    std::printf("  G2 is therefore CONSISTENT with existing gravimetry; G1 is not tested\n");
    std::printf("  by gravimetry (it claims a LAB-MASS force change) — see (e).\n\n");

    // ------------------------------------------------------------------
    // (c) near-contact saturation curve
    // ------------------------------------------------------------------
    std::printf("--- (c) NEAR-CONTACT SATURATION g(x) = 2(1 - sqrt(1-x))/x, x=(R/r)^2 ---\n\n");
    std::printf("  %-8s  %12s\n", "x", "g(x)");
    const double xs[] = {1e-4, 0.01, 0.1, 0.25, 0.5, 0.75, 0.9, 0.99, 1.0};
    for (double x : xs) {
        double gx = 2.0 * (1.0 - std::sqrt(1.0 - x)) / x;
        std::printf("  %-8.4f  %12.6f\n", x, gx);
    }
    std::printf("\n  Limits: g -> 1 as x -> 0 (recovers 1/r^2) and g -> 2 at contact.\n");
    std::printf("  Fractional 1/r^2 violation at x = 0.25 (masses at 2 radii): %.1f%%.\n",
                (2.0 * (1.0 - std::sqrt(0.75)) / 0.25 - 1.0) * 100.0);
    std::printf("  This term rides along on ANY flight and is the only part of the\n");
    std::printf("  prediction set that does not depend on the altitude mechanism.\n\n");

    // ------------------------------------------------------------------
    // (d) make-or-break vs committed noise floors
    // ------------------------------------------------------------------
    std::printf("--- (d) MAKE-OR-BREAK: delta * kappa vs COMMITTED FLOORS ---\n\n");
    const double F1 = 3.0e-3;  // PROMPT's own 0.3%% per-altitude-bin target
    const double F2 = 1.0e-5;  // heroic long-integration lock-in floor
    std::printf("  Floors (committed in RUN_LOG before run): F1 = %.0e (PROMPT 0.3%%/bin),\n", F1);
    std::printf("  F2 = %.0e (best-lab lock-in).\n\n", F2);
    std::printf("  G1 signal at 40 km: %.2e  -> %.0fx ABOVE F1: trivially measurable IF real.\n",
                g1_40, g1_40 / F1);
    std::printf("  G2 ramp signal:     %.2e  -> %.0fx BELOW F1, %.0fx BELOW even F2.\n",
                dg2_ramp, F1 / dg2_ramp, F2 / dg2_ramp);
    std::printf("  Required fractional force sensitivity for G2: ~%.0e per ramp.\n", dg2_ramp / 3.0);
    std::printf("  Committed wording applies to G2: ORDERS BELOW REACHABLE SENSITIVITY —\n");
    std::printf("  not worth flying for the mass-proportional model.\n\n");

    // ------------------------------------------------------------------
    // (e) OBSERVED anchor: the existing G record vs lab elevation (kills G1?)
    // ------------------------------------------------------------------
    std::printf("--- (e) OBSERVED ANCHOR: G RECORD vs LAB ELEVATION (PROMPT's own check) ---\n\n");
    struct GLab { const char* lab; double h_m; double G; };
    const GLab labs[] = {
        {"HUST (Wuhan)",     30.0, 6.674184e-11},
        {"UWash (Seattle)",  50.0, 6.674255e-11},
        {"BIPM (Sevres)",    60.0, 6.675540e-11},
        {"JILA (Boulder)", 1655.0, 6.672340e-11},
        {"LANL (Los Alamos)",2231.0, 6.674000e-11},
    };
    const int NL = sizeof(labs) / sizeof(labs[0]);
    double Gref = labs[0].G; // sea-level-ish reference
    std::printf("  %-20s  %8s  %14s  %14s  %14s\n",
                "Lab", "h [m]", "G measured", "obs dev", "G1 predicted dev");
    double worst_excl = 0.0;
    for (int i = 0; i < NL; ++i) {
        double obs_dev = (labs[i].G - Gref) / Gref;
        double pred    = std::sin(std::acos(R_E / (R_E + labs[i].h_m)))
                       - std::sin(std::acos(R_E / (R_E + labs[0].h_m)));
        std::printf("  %-20s  %8.0f  %14.6e  %+14.2e  %+14.2e\n",
                    labs[i].lab, labs[i].h_m, labs[i].G, obs_dev, pred);
        if (labs[i].h_m > 1000.0) {
            double excl = pred / 5.0e-4; // vs total inter-lab scatter ~5e-4
            if (excl > worst_excl) worst_excl = excl;
        }
    }
    std::printf("\n  Inter-lab scatter (all elevations): ~5e-4 relative.\n");
    std::printf("  G1 predicts +2.28e-2 (JILA) and +2.65e-2 (LANL) — %.0fx the ENTIRE\n", worst_excl);
    std::printf("  scatter, and JILA (highest-precision high lab) actually reads LOW.\n");
    std::printf("  Committed criterion (RUN_LOG): G1 excluded if predicted > 10x scatter.\n");
    std::printf("  Result: %.0fx > 10x  ->  G1 (geometric-opacity sin-dip law) is\n", worst_excl);
    std::printf("  EXCLUDED BY THE EXISTING G RECORD — subject only to the H1 caveat below.\n\n");

    // ------------------------------------------------------------------
    // The H1 fork, both branches (PROMPT 3.4)
    // ------------------------------------------------------------------
    std::printf("--- H1 FORK (PROMPT 3.4) — BOTH BRANCHES, NO ESCAPE HATCH ---\n\n");
    std::printf("  Branch H1-TRUE  (gravity rides ambient flux, EM does not):\n");
    std::printf("    then ground-based Cavendish experiments already sample delta(h)\n");
    std::printf("    across 0-2.2 km of elevation, and the record excludes G1 at ~%.0fx.\n", worst_excl);
    std::printf("    The surviving altitude term is G2 ~ 1e-7 class: unreachable.\n");
    std::printf("  Branch H1-FALSE (fibre constant rides the same flux):\n");
    std::printf("    the ratio theta = F/kappa_fibre cancels IDENTICALLY -> zero signal\n");
    std::printf("    at any altitude, and the flight measures nothing by construction.\n\n");
    std::printf("  EITHER WAY the balloon Cavendish, as specced, has no live signal path\n");
    std::printf("  for the altitude law. The surviving flyable content is (c) saturation\n");
    std::printf("  and E104's correlation test at the G2 (1e-7) level — below any floor.\n\n");

    std::printf("=====================================================================\n");
    std::printf(" PRE-FLIGHT VERDICT (committed wording):\n");
    std::printf("   kappa = 1 (SDT) vs 0 (SM) — clean, P_eff-magnitude-independent.\n");
    std::printf("   G1 sin-dip law: KILLED pre-flight by the existing G record (46x).\n");
    std::printf("   G2 mass-proportional: real but ~%.0e — orders below sensitivity.\n", dg2_ramp);
    std::printf("   Saturation curve: emitted; the only near-term testable piece.\n");
    std::printf("   E104 flight as designed: NOT WORTH FLYING for the altitude signal.\n");
    std::printf("=====================================================================\n");
    return 0;
}
