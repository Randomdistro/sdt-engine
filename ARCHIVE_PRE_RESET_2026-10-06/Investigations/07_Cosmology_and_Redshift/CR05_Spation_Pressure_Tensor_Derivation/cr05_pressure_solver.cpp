/**
 * @file cq40_pressure_solver.cpp
 * @brief CR05 Phase 3 & 5: Spation Pressure Tensor Solver
 *
 * Computes:
 *   1. Pressure evolution P(z) = P_conv × (1+z)^4
 *   2. Energy density evolution ρ(z)
 *   3. Hubble parameter H(z) from Friedmann equation
 *   4. Comoving distance r_c(z) via integration
 *   5. Comparison with observed values
 *   6. Transfer function f closure verification
 *
 * Candidate models tested:
 *   A) Pressure balance: H² ∝ P/ρ
 *   B) Topology-driven: H² ∝ (1+z)³ × f(z)
 *   C) Resonance-driven: H² ∝ BAO coupling
 *   D) Bootstrap-FLRW: H² = H₀²[Ω_m(1+z)³ + Ω_r(1+z)⁴]
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne
 * @date June 2026
 */

#include <cmath>
#include <cstdio>
#include <vector>
#include <numbers>

// ═══════════════════════════════════════════════════════════════════════════
//  CONSTANTS FROM LAW I (SINGLE SOURCE OF TRUTH)
// ═══════════════════════════════════════════════════════════════════════════

namespace sdt {
    // Fundamental invariants
    inline constexpr double c           = 299'792'458.0;          // [m/s]
    inline constexpr double hbar        = 1.054'571'817e-34;      // [J·s]
    inline constexpr double l_P         = 1.616'255e-35;          // [m]
    inline constexpr double k_B         = 1.380'649e-23;          // [J/K]
    inline constexpr double T_CMB       = 2.7255;                 // [K]
    inline constexpr double a_rad       = 7.565'7e-16;            // [J/m³/K⁴]
    inline constexpr double z_rec       = 1100.0;                 // [-]
    inline constexpr double R_CMB       = 9.527e26;               // [m] (observed)

    // Derived constants (Law I)
    inline constexpr double l_P3        = l_P * l_P * l_P;
    inline constexpr double u_CMB       = a_rad * T_CMB * T_CMB * T_CMB * T_CMB;  // [J/m³]
    inline constexpr double P_rad       = u_CMB / 3.0;             // [Pa]
    inline constexpr double N_shells    = R_CMB / l_P;             // [dimensionless]
    inline constexpr double epsilon     = u_CMB * l_P3;            // [J]
    inline constexpr double Phi         = N_shells * epsilon;      // [J]
    inline constexpr double P_conv      = Phi / l_P3;              // [Pa]

    // Baryon and radiation parameters (from observations + Theory/02)
    inline constexpr double m_p         = 1.672'621'923'69e-27;   // [kg]
    inline constexpr double n_b_z0      = 0.1;                    // [m⁻³] (Ω_b h² ≈ 0.022)
    inline constexpr double rho_b_z0    = m_p * n_b_z0;           // [kg/m³]

    // Hubble parameter (observed by Planck)
    inline constexpr double H0_planck_SI = 2.198e-18;            // [s⁻¹]  67.4 km/s/Mpc
    inline constexpr double H0_planck_kmsMpc = 67.4;             // [km/s/Mpc]
    inline constexpr double Mpc_to_m    = 3.086e22;              // [m/Mpc]

    // Density parameter fractions (Planck 2018)
    inline constexpr double Omega_m     = 0.315;                 // [dimensionless]
    inline constexpr double Omega_r     = 9.24e-5;               // [dimensionless]
    inline constexpr double Omega_Lambda = 0.685;                // [dimensionless]
}

// ═══════════════════════════════════════════════════════════════════════════
//  PRESSURE EVOLUTION (from CR05 Phase 1-2)
// ═══════════════════════════════════════════════════════════════════════════

/**
 * @brief Pressure at redshift z
 * P(z) = P_conv × (1+z)^4
 */
double pressure_at_z(double z, double P_conv) {
    return P_conv * std::pow(1.0 + z, 4.0);
}

/**
 * @brief Energy density at redshift z (from volume conservation)
 * ρ(z) = ρ₀ × (1+z)³ [purely topological evolution]
 */
double rho_at_z(double z, double rho_0) {
    return rho_0 * std::pow(1.0 + z, 3.0);
}

/**
 * @brief Baryon number density at redshift z
 * n_b(z) = n_b(0) × (1+z)³
 */
double n_b_at_z(double z) {
    return sdt::n_b_z0 * std::pow(1.0 + z, 3.0);
}

// ═══════════════════════════════════════════════════════════════════════════
//  HUBBLE PARAMETER MODELS
// ═══════════════════════════════════════════════════════════════════════════

/**
 * @brief Model A: Pressure-balance (FAILS)
 * H² ∝ (P/ρ) → diverges for cosmological scales
 */
double hubble_modelA(double z) {
    double P_z = pressure_at_z(z, sdt::P_conv);
    double rho_z = rho_at_z(z, sdt::rho_b_z0);
    return std::sqrt(P_z / rho_z) / sdt::c;  // [in c-units, divided by c for proper H]
}

/**
 * @brief Model B: Topology-driven (FAILS)
 * H² ∝ linking_number_density × pressure
 * H²(z) = H₀² × (1+z)³ × (P_conv / P_scale)
 */
double hubble_modelB(double z, double H0) {
    return H0 * std::pow(1.0 + z, 1.5);  // H ∝ (1+z)^1.5
}

/**
 * @brief Model C: Resonance-driven (FAILS)
 * H² ∝ BAO wavenumber × pressure
 * H²(z) = H₀² × (1+z)⁴
 */
double hubble_modelC(double z, double H0) {
    return H0 * std::pow(1.0 + z, 2.0);  // H ∝ (1+z)^2
}

/**
 * @brief Model D (PREFERRED): Bootstrap-FLRW
 * H²(z) = H₀² [Ω_m(0)(1+z)³ + Ω_r(0)(1+z)⁴]
 *
 * This is the standard Friedmann equation interpreted via SDT topology:
 *   Ω_m ↔ linking number density (matter-like)
 *   Ω_r ↔ pressure field evolution (radiation-like)
 */
double hubble_modelD(double z, double H0_in_SI) {
    // H0_in_SI is in [s⁻¹]
    double sqrt_term = std::sqrt(
        sdt::Omega_m * std::pow(1.0 + z, 3.0) +
        sdt::Omega_r * std::pow(1.0 + z, 4.0)
    );
    return H0_in_SI * sqrt_term;
}

/**
 * @brief Extract H₀ from observed R_CMB using bootstrap approach
 *
 * Given: R_CMB_obs from measurements (e.g., CMB power spectrum)
 * Compute: comoving distance r_c(z_rec) using H(z)
 * Solve: H₀ such that r_c(z_rec, H₀) ≈ R_CMB_obs
 */
double solve_H0_from_R_CMB(double R_CMB_obs) {
    const double z_rec = 1100.0;
    const int N_steps = 10000;

    // Bracket search for H₀
    double H0_low = 2.0e-18;    // [s⁻¹]  ~60 km/s/Mpc
    double H0_high = 2.5e-18;   // [s⁻¹]  ~75 km/s/Mpc

    for (int iter = 0; iter < 20; ++iter) {
        double H0_mid = (H0_low + H0_high) / 2.0;

        // Integrate comoving distance
        double r_c = 0.0;
        double dz = z_rec / N_steps;

        for (int i = 0; i < N_steps; ++i) {
            double z_here = (i + 0.5) * dz;
            double H_z = hubble_modelD(z_here, H0_mid);
            r_c += (sdt::c / H_z) * dz;  // dr_c = (c/H) dz
        }

        if (r_c < R_CMB_obs) {
            H0_low = H0_mid;
        } else {
            H0_high = H0_mid;
        }
    }

    return (H0_low + H0_high) / 2.0;
}

// ═══════════════════════════════════════════════════════════════════════════
//  COMOVING DISTANCE INTEGRATION
// ═══════════════════════════════════════════════════════════════════════════

/**
 * @brief Comoving distance to redshift z
 * r_c(z) = (c / H₀) × ∫₀^z dz' / E(z')
 * where E(z) = H(z) / H₀
 */
double comoving_distance(double z, double H0_SI) {
    const int N_steps = 10000;
    double r_c = 0.0;
    double dz = z / N_steps;

    for (int i = 0; i < N_steps; ++i) {
        double z_here = (i + 0.5) * dz;
        double H_z = hubble_modelD(z_here, H0_SI);
        r_c += (sdt::c / H_z) * dz;
    }

    return r_c;
}

// ═══════════════════════════════════════════════════════════════════════════
//  TOPOLOGICAL LINKING NUMBER EVOLUTION
// ═══════════════════════════════════════════════════════════════════════════

/**
 * @brief Linking number density evolution
 * τ(z) = τ₀ × (1+z)³
 */
double linking_density_at_z(double z, double tau_0) {
    return tau_0 * std::pow(1.0 + z, 3.0);
}

/**
 * @brief Total linking number in observable volume
 * Lk(z) ∝ τ(z) × V(z) ∝ (1+z)³ × a⁻³ = const...
 * (Actually, total linking count is conserved, but density evolves as above)
 */
double linking_number_at_z(double z, double Lk_0) {
    // In a static comoving frame, total Lk is conserved
    // But linking *density* drops as (1+z)³
    // For this analysis, we track density evolution
    return linking_density_at_z(z, Lk_0);
}

// ═══════════════════════════════════════════════════════════════════════════
//  TRANSFER FUNCTION VERIFICATION
// ═══════════════════════════════════════════════════════════════════════════

/**
 * @brief Transfer function f = P_eff / P_conv
 *
 * From Law III:
 *   P_eff ≈ 5.225e31 Pa (calibrated from hydrogen)
 *   P_conv ≈ 2.459e48 Pa (from Law I)
 *
 * f = P_eff / P_conv ≈ 2.125e-17
 *
 * Status before CR05: CLASS E (CALIBRATED — depends on hydrogen calibration)
 * Status after CR05: CLASS C (CONVERGENCE — if H₀ derived purely from topology)
 */
double transfer_function_f() {
    // From Engine/include/sdt/laws.hpp
    const double P_eff = 5.225e31;  // [Pa]
    return P_eff / sdt::P_conv;
}

/**
 * @brief Audit the transfer-function dependency chain.
 */
void verify_transfer_function_closure() {
    printf("\n=== Transfer Function Closure Verification ===\n\n");

    double f = transfer_function_f();

    printf("f = P_eff / P_conv = %.6e\n", f);
    printf("P_eff = 5.225e31 Pa (from hydrogen calibration)\n");
    printf("P_conv = 2.459e48 Pa (from Law I: Φ/ℓ_P³)\n\n");

    printf("Dependencies of f:\n");
    printf("  P_eff ← hydrogen charge radius R_p, Coulomb constant k_e\n");
    printf("  P_conv ← R_CMB, P_rad (radiation pressure), shell count N\n");
    printf("  R_CMB ← observed boundary scale\n\n");

    printf("Closure Status:\n");
    printf("  R_CMB remains observed and P_eff remains hydrogen-calibrated.\n");
    printf("  Therefore f remains CLASS E.\n\n");
    printf("VERDICT: CR05 does not close the transfer function.\n\n");
}

// ═══════════════════════════════════════════════════════════════════════════
//  MAIN SOLVER
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    printf("╔════════════════════════════════════════════════════════════════════╗\n");
    printf("║         CR05 SPATION PRESSURE TENSOR SOLVER                        ║\n");
    printf("║    Audit of H₀-from-pressure and transfer-closure candidates      ║\n");
    printf("╚════════════════════════════════════════════════════════════════════╝\n\n");

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 1: CONSTANTS AND SETUP
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 1: LAW I CONVERGENCE CONSTANTS\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("Fundamental invariants:\n");
    printf("  c             = %.3e m/s\n", sdt::c);
    printf("  ℓ_P           = %.3e m\n", sdt::l_P);
    printf("  T_CMB         = %.3f K\n", sdt::T_CMB);
    printf("  R_CMB (obs)   = %.3e m\n", sdt::R_CMB);
    printf("  z_rec         = %.1f\n\n", sdt::z_rec);

    printf("Derived from Law I:\n");
    printf("  u_CMB         = %.3e J/m³\n", sdt::u_CMB);
    printf("  N_shells      = %.3e  [Planck shells to Clearing]\n", sdt::N_shells);
    printf("  ε             = %.3e J  [energy per shell]\n", sdt::epsilon);
    printf("  Φ             = %.3e J  [total convergence burden]\n", sdt::Phi);
    printf("  P_conv        = %.3e Pa  [convergence pressure]\n", sdt::P_conv);
    printf("  P_rad         = %.3e Pa  [radiation pressure at z=0]\n\n", sdt::P_rad);

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 2: PRESSURE EVOLUTION
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 2: PRESSURE EVOLUTION P(z) = P_conv × (1+z)⁴\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("Redshift z  |  P(z) [Pa]      |  ρ(z)/ρ₀    |  w(z)     | Class\n");
    printf("─────────────────────────────────────────────────────────────────\n");

    double z_samples[] = {0, 1, 10, 100, 1000, 1100};
    for (double z : z_samples) {
        double P_z = pressure_at_z(z, sdt::P_conv);
        double rho_ratio = std::pow(1.0 + z, 3.0);
        double w = P_z / (sdt::rho_b_z0 * rho_ratio * sdt::c * sdt::c);
        printf("%7.0f    | %.3e | %7.3e | %.3e | CANDIDATE\n", z, P_z, rho_ratio, w);
    }
    printf("\n");

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 3: HUBBLE PARAMETER CANDIDATES
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 3: HUBBLE PARAMETER MODELS (CANDIDATES A-D)\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("Model A (Pressure-Balance): H² ∝ P/ρ\n");
    printf("  Prediction: H₀ ≈ %.3e s⁻¹  [FAILS — diverges]\n\n", hubble_modelA(0));

    printf("Model B (Topology-Driven): H ∝ (1+z)^1.5\n");
    printf("  Prediction: requires normalization [FAILS]\n\n");

    printf("Model C (Resonance-Driven): H ∝ (1+z)^2\n");
    printf("  Prediction: requires normalization [FAILS]\n\n");

    printf("Model D (Bootstrap-FLRW): H² = H₀²[Ω_m(1+z)³ + Ω_r(1+z)⁴]\n");
    printf("  Ω_m = %.4f (imported normalization)\n", sdt::Omega_m);
    printf("  Ω_r = %.4e (imported normalization)\n", sdt::Omega_r);
    printf("  Status: comparison-only; not an SDT derivation\n\n");

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 4: HUBBLE PARAMETER EVOLUTION
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 4: HUBBLE EVOLUTION H(z) — MODEL D\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    double H0_obs_SI = sdt::H0_planck_kmsMpc / sdt::c * 1000.0 / sdt::Mpc_to_m;
    // Conversion: H₀ [km/s/Mpc] → [s⁻¹]
    H0_obs_SI = sdt::H0_planck_SI;  // Use canonical value

    printf("Observed H₀ (Planck 2018):\n");
    printf("  H₀ = %.1f ± 0.5 km/s/Mpc\n", sdt::H0_planck_kmsMpc);
    printf("  H₀ = %.3e s⁻¹\n\n", H0_obs_SI);

    printf("H(z) Evolution (Model D — Friedmann):\n");
    printf("Redshift z  |  H(z) [s⁻¹]     |  H(z)/H₀    | Regime\n");
    printf("─────────────────────────────────────────────────────────\n");

    double z_eval[] = {0, 0.1, 1, 10, 100, 1000, 1100};
    for (double z : z_eval) {
        double H_z = hubble_modelD(z, H0_obs_SI);
        double ratio = H_z / H0_obs_SI;
        const char* regime;
        if (z < 1) regime = "Present/Late";
        else if (z < 100) regime = "Matter-dom";
        else regime = "Radiation-dom";

        printf("%7.0f    | %.3e | %9.3e | %s\n", z, H_z, ratio, regime);
    }
    printf("\n");

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 5: COMOVING DISTANCE CALCULATION
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 5: COMOVING DISTANCE INTEGRAL\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("r_c(z) = (c/H₀) × ∫₀^z dz' / E(z')\n");
    printf("where E(z) = H(z) / H₀\n\n");

    double r_c_rec = comoving_distance(sdt::z_rec, H0_obs_SI);
    printf("Comoving distance to recombination (z = %.0f):\n", sdt::z_rec);
    printf("  r_c(z_rec) = %.3e m\n", r_c_rec);
    printf("  r_c(z_rec) = %.3e m  (for comparison)\n", sdt::R_CMB);
    printf("  Ratio: r_c / R_CMB = %.3f\n\n", r_c_rec / sdt::R_CMB);

    printf("Interpretation:\n");
    printf("  Observed R_CMB ≈ 9.53e26 m (from CMB power spectrum)\n");
    printf("  Computed r_c  ≈ %.3e m (from Friedmann with Model D)\n", r_c_rec);
    printf("  Agreement: %+.1f%%  [should be <5%% for validation]\n\n",
           100.0 * (r_c_rec / sdt::R_CMB - 1.0));

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 6: LINKING NUMBER EVOLUTION (TOPOLOGICAL FREEZE-OUT)
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 6: TOPOLOGICAL LINKING NUMBER EVOLUTION\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("τ(z) = τ₀ × (1+z)³  [linking number density]\n\n");
    printf("Redshift z  |  τ(z)/τ₀     |  Interpretation\n");
    printf("──────────────────────────────────────────────────\n");

    for (double z : z_eval) {
        double tau_ratio = linking_density_at_z(z, 1.0);
        const char* note;
        if (z < 10) note = "Decoupled (neutral lattice)";
        else if (z < 1100) note = "Coupling strengthening";
        else if (z == 1100) note = "Recombination freeze (TRANSITION)";
        else note = "Coupled (ionized plasma)";

        printf("%7.0f    | %.3e  | %s\n", z, tau_ratio, note);
    }
    printf("\n");

    printf("Freeze-out candidate (not independently derived):\n");
    printf("  Before z_rec: τ(z) = τ₀(1+z)³  [independent e⁻, p⁺]\n");
    printf("  At z_rec:     Electrons bind to protons (Law II ionization)\n");
    printf("  After z_rec:  τ drops by factor of 4 (W_e mode absorbed)\n");
    printf("  Consequence:  Lattice decouples; H(z) transitions\n\n");

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 7: H(z) TRANSITION AT RECOMBINATION
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 7: H(z) PHASE TRANSITION AT RECOMBINATION\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("Early times (z ≫ 1, radiation-dominated):\n");
    printf("  H²(z) ≈ H₀² Ω_r (1+z)⁴\n");
    printf("  H(z) ≈ H₀ √[Ω_r] (1+z)²  ∝ a⁻²\n");
    printf("  Effective: w_eff ≈ 1/3 (stiff)\n\n");

    printf("Late times (z ≪ 1, matter-dominated):\n");
    printf("  H²(z) ≈ H₀² Ω_m (1+z)³\n");
    printf("  H(z) ≈ H₀ √[Ω_m] (1+z)^{3/2}  ∝ a^{-3/2}\n");
    printf("  Effective: w_eff ≈ 0 (soft)\n\n");

    double H_early = hubble_modelD(2000, H0_obs_SI);
    double H_late = hubble_modelD(10, H0_obs_SI);
    double H_rec = hubble_modelD(sdt::z_rec, H0_obs_SI);

    printf("Transition Point (z_rec = %.0f):\n", sdt::z_rec);
    printf("  H(early, z=2000) / H₀ = %.3e  [high z, pressure-dominated]\n", H_early / H0_obs_SI);
    printf("  H(rec,   z=1100) / H₀ = %.3e  [at transition]\n", H_rec / H0_obs_SI);
    printf("  H(late,  z=10)   / H₀ = %.3e  [low z, density-dominated]\n", H_late / H0_obs_SI);
    printf("\n");

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 8: TRANSFER FUNCTION CLOSURE
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 8: TRANSFER FUNCTION CLOSURE (CR03 + CR05)\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    verify_transfer_function_closure();

    // ═══════════════════════════════════════════════════════════════════════
    //  SECTION 9: FINAL VERDICT
    // ═══════════════════════════════════════════════════════════════════════

    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("SECTION 9: CR05 VERDICT\n");
    printf("═══════════════════════════════════════════════════════════════════\n\n");

    printf("TASK: Derive H₀ from spation pressure tensor (Law I)\n\n");

    printf("RESULTS:\n");
    printf("  Pressure exponent and fourfold freeze-out: OPEN candidates\n");
    printf("  Candidates A, B, C: FAIL or require normalization\n");
    printf("  Model D: imports Friedmann structure, H₀ and Ω normalisations\n");
    printf("  Native Model-A H₀: %.3e km/s/Mpc (vs Planck: 67.4)\n",
           hubble_modelA(0) * sdt::Mpc_to_m / 1000.0);
    printf("    Comoving distance to z_rec: %.3e m\n", r_c_rec);
    printf("    (Observed: %.3e m, difference: %+.1f%%)\n\n", sdt::R_CMB,
           100.0 * (r_c_rec / sdt::R_CMB - 1.0));

    printf("  Transfer function: CLASS E (observed/calibrated dependencies remain)\n\n");
    printf("CLASSIFICATION: H₀/TRANSFER CLOSURE EXCLUDED; MECHANISMS OPEN\n\n");

    printf("════════════════════════════════════════════════════════════════════\n");
    printf("CR05 DIRECT AUDIT COMPLETE — NO TRANSFER-FUNCTION CLOSURE\n");
    printf("════════════════════════════════════════════════════════════════════\n\n");

    return 0;
}

/*
COMPILATION (Windows):
  cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:cq40_pressure_solver.exe cq40_pressure_solver.cpp

COMPILATION (Linux/Mac):
  g++ -std=c++20 -IEngine/include cq40_pressure_solver.cpp -o cq40_pressure_solver -lm

RUN:
  ./cq40_pressure_solver > cq40_results.txt 2>&1
*/
