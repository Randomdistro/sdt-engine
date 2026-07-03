// ============================================================================
// SAR01 — Le Sage Thermal Budget
// Author: J. C. Harvey, Melbourne. Date: 2026-07-03.
//
// Question: if gravity = convergence occlusion, does the occluded flux cook
// the occluding body? Classical Le Sage theories die here (Poincaré/Maxwell).
// Three ledgers, thresholds pre-committed in RUN_LOG.md:
//   A. Classical absorption floor:  P >= F_grav * c        (gate: 10x geothermal)
//   B. Prompt's coupled interception: pi R_E^2 * f * P_conv * c   (same gate)
//   C. SDT relay ledger: line-by-line, engine citations only.
// No G, no M-in-kg input: Earth mass via the koppa bridge (bridge::N_baryons),
// solar field via bridge::g_at_radius (v^2 R / r^2).
// ============================================================================

#include <sdt/laws.hpp>
#include <cstdio>
#include <cmath>

using namespace sdt::laws;

int main() {
    std::printf("SAR01 — Le Sage Thermal Budget (J. C. Harvey, 2026-07-03)\n");
    std::printf("==========================================================\n\n");

    // ---- Declared measured anchors (OBSERVED) --------------------------------
    const double geothermal_W = 4.7e13;          // 47 TW, Davies & Davies 2010
    const double R_Earth      = 6.371e6;         // m
    const double r_AU         = measured::AU;    // 1.495978707e11 m
    const double v_surf_Sun   = bridge::v_surface_Sun;   // 436762 m/s (GOM04)
    const double v_surf_Earth = 7909.0;          // m/s, surface orbital velocity
    const double R_Sun        = measured::R_Sun;

    std::printf("[0] Engine inputs (sdt::laws — single source of truth)\n");
    std::printf("    P_conv      = %.4e Pa   (law_I::P_conv)\n", law_I::P_conv);
    std::printf("    P_eff       = %.4e Pa   (law_III::P_eff)\n", law_III::P_eff);
    std::printf("    f_transfer  = %.4e      (law_III::f_transfer)\n", law_III::f_transfer);
    std::printf("    Phi         = %.4e J    (law_I::Phi)\n", law_I::Phi);
    std::printf("    F_CMB       = %.4e W/m^2 (law_II::F_CMB)\n\n", law_II::F_CMB);

    // ---- Earth mass via koppa bridge (NO G, NO M input) ----------------------
    const double koppa_E   = bridge::koppa(v_surf_Earth, R_Earth);       // v^2 R / c^2
    const double N_baryons = bridge::N_baryons(koppa_E);
    const double m_Earth   = N_baryons * measured::m_p;
    std::printf("[1] Earth mass via koppa bridge (native, no G)\n");
    std::printf("    koppa_Earth = %.4f m  (v^2 R / c^2)\n", koppa_E);
    std::printf("    N_baryons   = %.4e   (koppa / koppa_per_baryon)\n", N_baryons);
    std::printf("    m_Earth     = %.4e kg  (x m_p)  [ref value 5.972e24 — %.2f%% off]\n\n",
                m_Earth, (m_Earth/5.972e24 - 1.0)*100.0);

    // ---- Sun->Earth gravitational force (native) -----------------------------
    const double g_1AU  = bridge::g_interior(v_surf_Sun, R_Sun, r_AU, 1.0); // v^2 R / r^2 (frac=1 outside)
    const double F_grav = m_Earth * g_1AU;
    std::printf("[2] Sun->Earth force (native: g = v_surf^2 R_Sun / r^2)\n");
    std::printf("    g(1 AU)     = %.4e m/s^2\n", g_1AU);
    std::printf("    F_grav      = %.4e N\n\n", F_grav);

    // ============================ LEDGER A ====================================
    // Classical Le Sage: force by ABSORPTION of a lightspeed momentum flux.
    // Minimum absorbed power (perfectly one-sided absorption): P = F * c.
    // Real Le Sage is worse: net force is a shadow ASYMMETRY delta << 1 of the
    // isotropic flux, so P_total = F*c/delta. F*c is the strict floor.
    const double P_A     = F_grav * measured::c;
    const double ratio_A = P_A / geothermal_W;
    std::printf("[A] LEDGER A — classical absorption floor\n");
    std::printf("    P_A = F_grav * c = %.4e W\n", P_A);
    std::printf("    ratio to geothermal (47 TW): %.3e\n", ratio_A);
    std::printf("    gate (10x): %s\n", ratio_A > 10.0 ? "EXCEEDED -> absorption KILLED" : "within");
    // Same ledger for the Sun on its galactic orbit:
    const double v_gal = 2.2e5;                 // m/s, solar galactic orbital speed (OBSERVED)
    const double m_Sun_native = bridge::N_baryons(bridge::koppa_Sun) * measured::m_p;
    const double a_gal = v_gal * v_gal / 2.57e20;   // v^2/r, r = 8.3 kpc (OBSERVED)
    const double P_A_Sun = m_Sun_native * a_gal * measured::c;
    std::printf("    (Sun, galactic-orbit force ledger: m_Sun[koppa] = %.3e kg,\n", m_Sun_native);
    std::printf("     P = %.3e W = %.1f x L_Sun -> absorption also killed at stellar scale)\n\n",
                P_A_Sun, P_A_Sun / law_II::L_Sun);

    // ============================ LEDGER B ====================================
    // The PROMPT's own formula: P_heat = (pi R_E^2) * P_conv * c * f.
    const double P_B     = std::numbers::pi * R_Earth * R_Earth
                         * law_I::P_conv * measured::c * law_III::f_transfer;
    const double ratio_B = P_B / geothermal_W;
    std::printf("[B] LEDGER B — prompt's coupled-interception formula\n");
    std::printf("    P_B = pi R_E^2 * f * P_conv * c = %.4e W\n", P_B);
    std::printf("    ratio to geothermal: %.3e\n", ratio_B);
    std::printf("    gate (10x): %s\n", ratio_B > 10.0 ? "EXCEEDED -> formula rejected as a HEAT term" : "within");
    std::printf("    (This exceeds the total luminosity of the observable universe;\n");
    std::printf("     the f-coupling CANNOT be an absorptive coupling over the geometric disc.)\n\n");

    // ============================ LEDGER C ====================================
    // The SDT relay ledger — where the energy actually goes, line by line.
    std::printf("[C] LEDGER C — SDT relay ledger (engine citations)\n");
    std::printf("    C1. Law I (T1 Shell Cancellation): Phi = N*epsilon is preserved at EVERY\n");
    std::printf("        point of the lattice. Throughput is relayed, never terminated\n");
    std::printf("        (throughpole: influx in/out). => absorbed power term is 0 BY LAW I.\n");
    std::printf("    C2. Law III occlusion is a boundary condition on relay DIRECTION, not an\n");
    std::printf("        energy sink: F = (pi/4) P_eff R1^2 R2^2 / r^2 is a static pressure\n");
    std::printf("        asymmetry. A static pressure does no work on a static body: W = F.v.\n");
    std::printf("        Earth in free fall: v (radial) ~ 0 => W ~ 0. Hydrostatic analogy:\n");
    std::printf("        a submerged body under 10^7 Pa does not heat up.\n");
    std::printf("    C3. Law IV: the reorganisation cost of holding V_disp open IS the mass\n");
    std::printf("        (m = Phi V_disp / (l_P^3 c^2)) — a one-time standing cost, not a\n");
    std::printf("        continuous dissipation. V_disp(Earth) = %.3e m^3.\n",
                law_IV::V_disp_from_mass(m_Earth));
    std::printf("    C4. Honest debt: C1-C3 make the heating zero AXIOMATICALLY (conservative\n");
    std::printf("        relay). Maxwell's objection to elastic Le Sage — that lossless\n");
    std::printf("        redirection re-fills the shadow and cancels the force — is answered\n");
    std::printf("        in SDT only by the claim of COHERENT streamline deflection around\n");
    std::printf("        V_disp (FLM12), which is asserted, not derived. Sub-verdict: OPEN.\n\n");

    // ---- Falsifiable bound ----------------------------------------------------
    const double eta_max = geothermal_W / P_A;
    std::printf("[D] Falsifiable bound (no gate — reported as measured ceiling)\n");
    std::printf("    If ANY fraction eta of the force-carrying flux thermalises, Earth's\n");
    std::printf("    heat budget demands eta < 47 TW / (F*c) = %.3e\n", eta_max);
    std::printf("    Compare f_transfer = %.3e : the thermalised fraction of even the\n", law_III::f_transfer);
    std::printf("    COUPLED flux must be < %.1f%% — occlusion must be lossless to ~1 part\n",
                100.0 * eta_max / law_III::f_transfer);
    std::printf("    in 10^17 of the raw flux. SDT survives iff redirection is exactly\n");
    std::printf("    conservative (Law I); any derived dissipation channel kills it.\n\n");

    // ---- Verdict summary -------------------------------------------------------
    std::printf("VERDICT LINES\n");
    std::printf("  Ledger A (absorption Le Sage): %s (overshoot %.1e x)\n",
                ratio_A > 10 ? "KILLED" : "PASS", ratio_A);
    std::printf("  Ledger B (prompt heat formula): %s (overshoot %.1e x)\n",
                ratio_B > 10 ? "REJECTED as heat term" : "PASS", ratio_B);
    std::printf("  Ledger C (relay evasion): ZERO-HEATING BY AXIOM (Law I) — class OPEN,\n");
    std::printf("    owed: derivation that coherent redirection preserves the shadow force.\n");
    std::printf("  Empirical ceiling: eta < %.2e (thermalisation efficiency of occluded flux)\n", eta_max);
    return 0;
}
