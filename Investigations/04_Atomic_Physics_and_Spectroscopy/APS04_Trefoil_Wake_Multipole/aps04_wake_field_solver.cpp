/**
 * @file cq38_wake_field_solver.cpp
 * @brief Trefoil Wake Field Computation and Multipole Decomposition
 *
 * Computes the velocity/pressure field induced by a (2,3) torus knot (proton trefoil)
 * at large radius r >> R_p, decomposes into multipole components native to three-fold
 * symmetry, and predicts the Lamb shift energy splitting.
 *
 * **Method:**
 * 1. Parametrize the (2,3) torus knot in 3D space
 * 2. Compute the velocity field on a lattice using a Biot-Savart-type circulation source
 * 3. Sample the field at multiple radii; extract equatorial vs polar components
 * 4. Fit to power laws Φ_ℓ(r) ~ A_ℓ r^{-α_ℓ}
 * 5. Extract Lamb shift energy splitting
 *
 * **No imported spherical harmonics.** Decomposition respects C₃ symmetry only.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date June 2026
 */

#include <cmath>
#include <numbers>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>

// ─────────────────────────────────────────────────────────────────────────
//  CONSTANTS
// ─────────────────────────────────────────────────────────────────────────

namespace constants {
    constexpr double c              = 299'792'458.0;           // [m/s]
    constexpr double hbar           = 1.054'571'817e-34;       // [J·s]
    constexpr double l_P            = 1.616'255e-35;           // [m]
    constexpr double alpha          = 7.297'352'5693e-3;       // [-]
    constexpr double m_p            = 1.672'621'923'69e-27;    // [kg]
    constexpr double m_e            = 9.109'383'7015e-31;      // [kg]
    constexpr double a_0            = 5.291'772'109'03e-11;    // [m]
    constexpr double R_p            = 8.414e-16;               // [m]
    constexpr double r_e            = 2.817'940'3262e-15;      // [m]
    constexpr double lambda_C_p     = hbar / (m_p * c);        // ≈ 1.321e-15 m
    constexpr double k_surface      = 1.0 / alpha * std::sqrt(R_p / a_0);  // ≈ 0.5464
    constexpr double v_phase_R_p    = c / k_surface;           // ≈ 1.831c

    constexpr double pi             = std::numbers::pi;
    constexpr double h              = 6.626'070'15e-34;        // [J·s]
    constexpr double k_e            = 8.987'551'7923e9;        // [N·m²/C²]
    constexpr double e_charge       = 1.602'176'634e-19;       // [C]
    constexpr double h_bar_meV_ns   = 6.582119569e-1;          // ℏ in meV·ns
}

using namespace constants;

// ─────────────────────────────────────────────────────────────────────────
//  TREFOIL PARAMETERIZATION: (2,3) Torus Knot
// ─────────────────────────────────────────────────────────────────────────

/**
 * Parametrize a (p,q) = (2,3) torus knot in normalized coordinates.
 * @param t Parameter ∈ [0, 2π], full cycle covers 3 toroidal turns (q=3)
 * @return 3D position [x, y, z] in units of R_p
 */
struct Point3D {
    double x, y, z;
    Point3D() = default;
    Point3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    Point3D operator+(const Point3D& p) const {
        return Point3D(x + p.x, y + p.y, z + p.z);
    }
    Point3D operator*(double s) const {
        return Point3D(x * s, y * s, z * s);
    }
    double dot(const Point3D& p) const {
        return x * p.x + y * p.y + z * p.z;
    }
    double norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

/**
 * (2,3) torus knot parametrization.
 * Major radius (around z-axis): R_major ≈ 1.0 (in knot-relative units)
 * Minor radius (cross-section): r_minor ≈ 0.3
 * The knot winds p=2 times poloidally, q=3 times toroidally.
 */
Point3D trefoil_knot(double t, double R_major = 1.0, double r_minor = 0.3) {
    const int p = 2;  // Poloidal winding
    const int q = 3;  // Toroidal winding

    // Poloidal angle (around the minor circle)
    double u = p * t;
    // Toroidal angle (around the major axis)
    double v = q * t;

    // Circle in the meridian plane, offset by R_major
    double x_circ = R_major + r_minor * std::cos(u);
    double z_circ = r_minor * std::sin(u);

    // Rotate around the z-axis
    double x = x_circ * std::cos(v);
    double y = x_circ * std::sin(v);
    double z = z_circ;

    return Point3D(x, y, z);
}

// ─────────────────────────────────────────────────────────────────────────
//  VELOCITY FIELD COMPUTATION
// ─────────────────────────────────────────────────────────────────────────

/**
 * Velocity at a point r due to circulation around the trefoil.
 * Uses a simplified Biot-Savart-type model:
 * Each element of the trefoil filament acts as a circulation source.
 * The velocity field is the superposition of contributions from the knot curve.
 *
 * For a vortex filament with circulation Γ at position r_source, the velocity
 * at position r is:
 *   v(r) = (Γ / 4π) ∮ (dl × (r - r_source)) / |r - r_source|³
 *
 * Here we use a simplified model: the velocity field of a trefoil wake
 * decays radially as v(r) ∝ 1/r (monopole-like for the axial component).
 * The azimuthal component has multipole structure.
 */
struct VelocityField {
    double v_r;        // Radial component
    double v_theta;    // Poloidal (meridian) component
    double v_phi;      // Toroidal (azimuthal) component
};

/**
 * Compute the circulating velocity field of the trefoil.
 * Approximation: the proton circulates at phase velocity v_phase ≈ 1.831c
 * with 6π winding per cycle. The effective "circulation" is Γ ~ R_p × v_phase.
 *
 * @param obs_point Observation point [x, y, z] in meters
 * @param knot_samples Number of samples along the knot
 * @return VelocityField at obs_point
 */
VelocityField compute_trefoil_velocity(Point3D obs_point, int knot_samples = 128) {
    VelocityField v_accum{0.0, 0.0, 0.0};

    // Circulation strength (related to phase velocity mismatch)
    double Gamma = 2.0 * pi * R_p * v_phase_R_p;  // Circulation = 2πRv

    // Sample the trefoil knot
    for (int i = 0; i < knot_samples; ++i) {
        double t = 2.0 * pi * i / knot_samples;
        Point3D knot_pt = trefoil_knot(t, 1.0, 0.3);  // Normalized
        knot_pt = knot_pt * R_p;  // Scale to physical units (meters)

        // Vector from knot segment to observation point
        Point3D dr = obs_point + (knot_pt * (-1.0));
        double r_dist = dr.norm();

        if (r_dist < 1e-20) continue;  // Skip singularity

        // Biot-Savart contribution (simplified)
        // The full Biot-Savart is complex for a 3D curve; here we approximate
        // by summing the dipole-like field from each segment.

        // Tangent direction (discretized)
        double dt = 2.0 * pi / knot_samples;
        Point3D knot_pt_next = trefoil_knot(t + dt, 1.0, 0.3) * R_p;
        Point3D tangent = (knot_pt_next + (knot_pt * (-1.0))) * (1.0 / dt);

        // Biot-Savart kernel: (tangent × dr) / r³
        Point3D cross_prod{
            tangent.y * dr.z - tangent.z * dr.y,
            tangent.z * dr.x - tangent.x * dr.z,
            tangent.x * dr.y - tangent.y * dr.x
        };

        double factor = (Gamma / (4.0 * pi)) * (1.0 / (r_dist * r_dist * r_dist));

        v_accum.v_r     += factor * cross_prod.x;  // Radial
        v_accum.v_theta += factor * cross_prod.y;  // Meridian
        v_accum.v_phi   += factor * cross_prod.z;  // Azimuthal
    }

    return v_accum;
}

// ─────────────────────────────────────────────────────────────────────────
//  MULTIPOLE ANALYSIS
// ─────────────────────────────────────────────────────────────────────────

/**
 * Wake potential components at a radius r, decomposed into multipole modes.
 * We extract:
 *   Φ₀(r) — monopole (ℓ=0): integrated potential
 *   Φ₂(r) — quadrupole (ℓ=2): P₂(cos θ) modulation
 *   Φ₃(r) — trefoil (ℓ=3): cos(3φ) modulation
 */
struct MultipoleComponents {
    double Phi_0;   // Monopole
    double Phi_2;   // Quadrupole
    double Phi_3;   // Trefoil harmonic
    double Phi_2_fit_exp;  // Fitted exponent for Φ₂(r)
    double Phi_3_fit_exp;  // Fitted exponent for Φ₃(r)
};

/**
 * Extract multipole components from velocity field samples at radius r.
 * Sample at θ ∈ {0, π/2, π} and average over φ.
 */
MultipoleComponents extract_multipoles(double r, int theta_samples = 3, int phi_samples = 12) {
    MultipoleComponents mp{0.0, 0.0, 0.0, 0.0, 0.0};

    // Sample at equatorial (θ = π/2) and polar (θ = 0, π) positions
    std::vector<double> phi_eq(phi_samples), phi_pol(phi_samples);

    for (int j = 0; j < phi_samples; ++j) {
        double phi = 2.0 * pi * j / phi_samples;

        // Equatorial position
        Point3D eq_pt{r * std::cos(phi), r * std::sin(phi), 0.0};
        VelocityField v_eq = compute_trefoil_velocity(eq_pt);
        double speed_eq = std::sqrt(v_eq.v_r * v_eq.v_r + v_eq.v_theta * v_eq.v_theta + v_eq.v_phi * v_eq.v_phi);
        phi_eq[j] = speed_eq;

        // Polar position (north pole)
        Point3D pol_pt{0.0, 0.0, r};
        VelocityField v_pol = compute_trefoil_velocity(pol_pt);
        double speed_pol = std::sqrt(v_pol.v_r * v_pol.v_r + v_pol.v_theta * v_pol.v_theta + v_pol.v_phi * v_pol.v_phi);
        phi_pol[j] = speed_pol;
    }

    // Monopole: average over all positions
    double avg_eq = std::accumulate(phi_eq.begin(), phi_eq.end(), 0.0) / phi_samples;
    double avg_pol = std::accumulate(phi_pol.begin(), phi_pol.end(), 0.0) / phi_samples;
    mp.Phi_0 = (avg_eq + avg_pol) / 2.0;

    // Quadrupole: difference between equatorial and polar
    // P₂(cos π/2) = −1/2, P₂(cos 0) = 1
    // Φ₂(r) P₂(cos θ) contributes: −(3/2) Φ₂(r) at equator, 0 at pole
    mp.Phi_2 = (avg_eq - avg_pol) * 2.0 / 3.0;  // Proportional to difference

    // Trefoil (ℓ=3): cos(3φ) modulation in equatorial plane
    std::vector<double> phi_eq_3fold(phi_samples);
    for (int j = 0; j < phi_samples; ++j) {
        double phi = 2.0 * pi * j / phi_samples;
        phi_eq_3fold[j] = phi_eq[j] * std::cos(3.0 * phi);
    }
    mp.Phi_3 = std::sqrt(std::accumulate(phi_eq_3fold.begin(), phi_eq_3fold.end(), 0.0,
                                          [](double a, double b) { return a + b * b; }) / phi_samples);

    return mp;
}

// ─────────────────────────────────────────────────────────────────────────
//  POWER-LAW FITTING
// ─────────────────────────────────────────────────────────────────────────

/**
 * Fit data points (r, Φ) to a power law Φ(r) = A r^{-n}.
 * Returns the fitted exponent n (should be 1, 3, 4 for Φ₀, Φ₂, Φ₃).
 */
struct PowerLawFit {
    double amplitude;  // A in Φ(r) = A r^{-n}
    double exponent;   // n in Φ(r) = A r^{-n}
    double rms_error;  // RMS fit error
};

PowerLawFit fit_power_law(const std::vector<double>& r_values, const std::vector<double>& Phi_values) {
    if (r_values.size() < 2) return {0.0, 0.0, 1e99};

    // Log-log fit: log Φ = log A − n log r
    // Linear regression in log space
    double sum_log_r = 0.0, sum_log_Phi = 0.0;
    double sum_log_r_sq = 0.0, sum_log_r_log_Phi = 0.0;
    int count = 0;

    for (size_t i = 0; i < r_values.size(); ++i) {
        if (Phi_values[i] <= 0.0) continue;  // Skip non-positive
        double log_r = std::log(r_values[i]);
        double log_Phi = std::log(Phi_values[i]);
        sum_log_r += log_r;
        sum_log_Phi += log_Phi;
        sum_log_r_sq += log_r * log_r;
        sum_log_r_log_Phi += log_r * log_Phi;
        count++;
    }

    if (count < 2) return {0.0, 0.0, 1e99};

    double avg_log_r = sum_log_r / count;
    double avg_log_Phi = sum_log_Phi / count;

    double numerator = sum_log_r_log_Phi - count * avg_log_r * avg_log_Phi;
    double denominator = sum_log_r_sq - count * avg_log_r * avg_log_r;

    double exponent = -numerator / denominator;  // Negative slope
    double amplitude = std::exp(avg_log_Phi + exponent * avg_log_r);  // Back to linear space

    // Compute RMS error
    double sum_sq_error = 0.0;
    for (size_t i = 0; i < r_values.size(); ++i) {
        if (Phi_values[i] <= 0.0) continue;
        double Phi_fit = amplitude / std::pow(r_values[i], exponent);
        double error = (Phi_values[i] - Phi_fit) / Phi_values[i];
        sum_sq_error += error * error;
    }
    double rms_error = std::sqrt(sum_sq_error / count) * 100.0;  // As percentage

    return {amplitude, exponent, rms_error};
}

// ─────────────────────────────────────────────────────────────────────────
//  LAMB SHIFT PREDICTION
// ─────────────────────────────────────────────────────────────────────────

/**
 * Predict the Lamb shift energy splitting.
 * ΔE = E(equatorial) − E(polar)
 *     ≈ [−3/2 Φ₂(a₀) P₂(−1/2)] − [−3/2 Φ₂(a₀) P₂(+1)]
 *     = Φ₂(a₀) [−3/2(−1/2) + 3/2(1)]
 *     = Φ₂(a₀) × 9/4
 * Plus correction from trefoil harmonic Φ₃.
 */
double predict_lamb_shift_MHz(double Phi_2_at_a0, double Phi_3_at_a0) {
    // Energy scale factor: α² × Rydberg energy
    double E_ry_eV = 13.605693122994;  // Rydberg energy in eV
    double alpha_sq = alpha * alpha;

    // Multipole contributions to energy splitting
    // The quadrupole coupling (ℓ=2) dominates
    double Delta_E_eV = alpha_sq * E_ry_eV * (Phi_2_at_a0 / r_e) * (9.0 / 4.0);

    // Trefoil correction (smaller, ℓ=3)
    double Delta_E_trefoil = alpha * alpha_sq * E_ry_eV * (Phi_3_at_a0 / r_e) * 0.5;
    Delta_E_eV += Delta_E_trefoil;

    // Convert to frequency
    double Delta_E_J = Delta_E_eV * e_charge;  // eV to Joules
    double Delta_nu_Hz = Delta_E_J / h;
    double Delta_nu_MHz = Delta_nu_Hz / 1e6;

    return Delta_nu_MHz;
}

// ─────────────────────────────────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────────────────────────────────

int main() {
    std::printf("═══════════════════════════════════════════════════════════════════════════════\n");
    std::printf("  APS04: Trefoil Wake Multipole Expansion and Lamb Shift Prediction\n");
    std::printf("═══════════════════════════════════════════════════════════════════════════════\n\n");

    // Phase 1: Trefoil Wake Geometry
    std::printf("PHASE 1: Trefoil Wake Geometry Computation\n");
    std::printf("──────────────────────────────────────────\n");
    std::printf("Proton radius R_p = %.6e m\n", R_p);
    std::printf("Bohr radius a_0 = %.6e m\n", a_0);
    std::printf("Proton phase velocity = %.4f c\n", v_phase_R_p / c);
    std::printf("Traction ratio = %.1f × c/c\n\n", v_phase_R_p / c);

    // Sample the wake field at multiple radii
    std::vector<double> r_sample, Phi_0_vals, Phi_2_vals, Phi_3_vals;

    // Radial range: 1 fm to 1000 fm
    for (double log_r_fm = 0.0; log_r_fm <= 3.0; log_r_fm += 0.25) {
        double r_fm = std::pow(10.0, log_r_fm);
        double r_m = r_fm * 1e-15;
        r_sample.push_back(r_m);
    }

    std::printf("Sampling wake field at %zu radii...\n", r_sample.size());

    for (double r : r_sample) {
        MultipoleComponents mp = extract_multipoles(r, 3, 12);
        Phi_0_vals.push_back(mp.Phi_0);
        Phi_2_vals.push_back(mp.Phi_2);
        Phi_3_vals.push_back(mp.Phi_3);
    }

    // Phase 2: Multipole Power-Law Fitting
    std::printf("\nPHASE 2: Multipole Power-Law Fitting\n");
    std::printf("────────────────────────────────────\n");

    PowerLawFit fit_0 = fit_power_law(r_sample, Phi_0_vals);
    PowerLawFit fit_2 = fit_power_law(r_sample, Phi_2_vals);
    PowerLawFit fit_3 = fit_power_law(r_sample, Phi_3_vals);

    std::printf("Φ₀(r) ∝ r^{−%.2f}  (expect −1.0 for Coulomb)  [RMS: %.1f%%]\n",
                fit_0.exponent, fit_0.rms_error);
    std::printf("Φ₂(r) ∝ r^{−%.2f}  (expect −3.0 for magnetic) [RMS: %.1f%%]\n",
                fit_2.exponent, fit_2.rms_error);
    std::printf("Φ₃(r) ∝ r^{−%.2f}  (expect −4.0 for trefoil) [RMS: %.1f%%]\n\n",
                fit_3.exponent, fit_3.rms_error);

    // Phase 3: Energy Splitting at a₀
    std::printf("PHASE 3: Orbital Energy Splitting at r = a_0\n");
    std::printf("────────────────────────────────────────────\n");

    MultipoleComponents mp_a0 = extract_multipoles(a_0, 3, 12);

    std::printf("Φ₀(a_0) = %.6e  [normalized]\n", mp_a0.Phi_0);
    std::printf("Φ₂(a_0) = %.6e  [quadrupole]\n", mp_a0.Phi_2);
    std::printf("Φ₃(a_0) = %.6e  [trefoil]\n\n", mp_a0.Phi_3);

    // Phase 4: Lamb Shift Prediction
    std::printf("PHASE 4: Lamb Shift Prediction\n");
    std::printf("───────────────────────────────\n");

    double Delta_E_Lamb_pred_MHz = predict_lamb_shift_MHz(mp_a0.Phi_2, mp_a0.Phi_3);
    double Delta_E_Lamb_obs_MHz = 1057.845;  // Measured (NIST)
    double error_pct = (Delta_E_Lamb_pred_MHz - Delta_E_Lamb_obs_MHz) / Delta_E_Lamb_obs_MHz * 100.0;

    std::printf("Measured Lamb shift (2S₁/₂ − 2P₁/₂): %.3f MHz\n", Delta_E_Lamb_obs_MHz);
    std::printf("Predicted Lamb shift (from trefoil): %.3f MHz\n", Delta_E_Lamb_pred_MHz);
    std::printf("Error: %.1f%%\n\n", error_pct);

    // Verdict
    std::printf("═══════════════════════════════════════════════════════════════════════════════\n");
    std::printf("VERDICT\n");
    std::printf("═══════════════════════════════════════════════════════════════════════════════\n");

    bool pass_multipole = (fit_0.rms_error < 5.0) && (fit_2.rms_error < 5.0) && (fit_3.rms_error < 10.0);
    bool pass_power_laws = (std::abs(fit_0.exponent - (-1.0)) < 0.2) &&
                           (std::abs(fit_2.exponent - (-3.0)) < 0.5) &&
                           (std::abs(fit_3.exponent - (-4.0)) < 0.5);
    bool pass_lamb = (std::abs(error_pct) < 5.0);

    std::printf("✓ Multipole decomposition: %s\n", pass_multipole ? "PASS" : "PARTIAL/FAIL");
    std::printf("✓ Power-law exponents:     %s\n", pass_power_laws ? "PASS" : "PARTIAL/FAIL");
    std::printf("✓ Lamb shift prediction:   %s (±%.1f%%)\n",
                pass_lamb ? "PASS" : "PARTIAL/FAIL", std::abs(error_pct));

    if (pass_multipole && pass_power_laws && pass_lamb) {
        std::printf("\nCQ38 VERDICT: PASS — Trefoil wake mechanism derived natively.\n");
        std::printf("Angular DOF unblocked. Fine structure closure candidate for Class C.\n");
        return 0;
    } else if (pass_multipole && pass_lamb) {
        std::printf("\nCQ38 VERDICT: QUALIFIED — Magnitude and mechanism correct; power laws partial.\n");
        std::printf("Suggests numerical simulation refinement needed for higher accuracy.\n");
        return 1;
    } else {
        std::printf("\nCQ38 VERDICT: PARTIAL/FAIL — See detailed diagnostics above.\n");
        std::printf("Trefoil wake decomposition may require full lattice simulation.\n");
        return 2;
    }
}
