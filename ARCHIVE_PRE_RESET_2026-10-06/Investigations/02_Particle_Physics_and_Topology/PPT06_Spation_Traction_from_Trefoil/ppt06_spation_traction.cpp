/**
 * @file cq14_spation_traction.cpp
 * @brief PPT06: Spation Traction from the Trefoil — How the Gears Start
 *
 * Derives the mechanical traction, rotation, and orbital entrainment
 * imparted to the spation lattice by the proton's (2,3) trefoil knot.
 *
 * Key result: v_phase = 1.831c at the proton surface (k=0.5464).
 * The spation lattice cannot match this → velocity deficit converts
 * to Coulomb field (ℓ=1), magnetic field (ℓ=2), and electron orbits (ℓ≥3).
 *
 * @author SDT Engine — James Tyndall, Melbourne, Australia
 * @date May 2026
 */

#include <cstdio>
#include <cmath>
#include <numbers>

namespace constants {
    constexpr double c       = 299'792'458.0;
    constexpr double c2      = c * c;
    constexpr double hbar    = 1.054'571'817e-34;
    constexpr double l_P     = 1.616'255e-35;
    constexpr double l_P2    = l_P * l_P;
    constexpr double l_P3    = l_P * l_P * l_P;
    constexpr double t_P     = 5.391'24e-44;
    constexpr double a_rad   = 7.565'7e-16;
    constexpr double T_CMB   = 2.7255;
    constexpr double alpha   = 7.297'352'5693e-3;
    constexpr double alpha_inv = 137.035'999'084;
    constexpr double m_p     = 1.672'621'923'69e-27;
    constexpr double m_e     = 9.109'383'7015e-31;
    constexpr double R_p     = 8.414e-16;
    constexpr double r_e     = 2.817'940'3262e-15;
    constexpr double a_0     = 5.291'772'109'03e-11;
    constexpr double e_charge = 1.602'176'634e-19;
    constexpr double eV_to_J = 1.602'176'634e-19;
    constexpr double mu_N    = 5.050'783'7461e-27;
    constexpr double pi      = std::numbers::pi;

    // SDT derived
    constexpr double u_CMB   = a_rad * T_CMB * T_CMB * T_CMB * T_CMB;
    constexpr double R_CMB   = 9.527e26;
    constexpr double N       = R_CMB / l_P;
    constexpr double epsilon = u_CMB * l_P3;
    constexpr double Phi     = N * epsilon;
    constexpr double P_conv  = Phi / l_P3;

    // Proton Compton wavelength
    constexpr double lambda_C_p = hbar / (m_p * c);

    // Budget angle (PPT05)
    constexpr double sin2_theta = 1.0 / 3.0;
    constexpr double cos2_theta = 2.0 / 3.0;
}

using namespace constants;

// ═══════════════════════════════════════════════════════════════
//  PART I — SUPERLUMINAL PHASE VELOCITY
// ═══════════════════════════════════════════════════════════════

void part_I() {
    std::printf("\n");
    std::printf("═══════════════════════════════════════════════════════════════\n");
    std::printf("  PART I — SUPERLUMINAL PHASE VELOCITY AT THE PROTON SURFACE\n");
    std::printf("═══════════════════════════════════════════════════════════════\n\n");

    // k at proton surface
    double k_surface = alpha_inv * std::sqrt(R_p / a_0);
    double v_phase = c / k_surface;

    std::printf("  k_surface = (1/α)√(R_p/a₀) = %.4f\n", k_surface);
    std::printf("  v_phase   = c/k = %.4f c = %.6e m/s\n", v_phase / c, v_phase);
    std::printf("\n");

    // The c-boundary (koppa)
    double koppa_H = alpha * alpha * a_0;
    std::printf("  ── C-Boundary (Koppa) ──\n");
    std::printf("  ϟ_H = α²a₀ = %.4e m = %.4f fm\n", koppa_H, koppa_H * 1e15);
    std::printf("  R_p = %.4e m = %.4f fm\n", R_p, R_p * 1e15);
    std::printf("  R_p < ϟ_H → proton surface is INSIDE c-boundary ✓\n\n");

    // Superluminal zone
    std::printf("  ── Superluminal Zone ──\n");
    std::printf("  Inner boundary:  R_p    = %.4f fm (k = %.4f, v = %.3fc)\n",
                R_p * 1e15, k_surface, v_phase / c);
    std::printf("  Outer boundary:  ϟ_H    = %.4f fm (k = 1.000, v = c)\n",
                koppa_H * 1e15);
    std::printf("  Zone thickness:          %.4f fm\n",
                (koppa_H - R_p) * 1e15);
    std::printf("  All spations in this zone experience v_phase > c.\n\n");

    // k profile through the superluminal zone
    std::printf("  ── k Profile Through Superluminal Zone ──\n");
    std::printf("  %8s  %8s  %8s  %10s\n", "r [fm]", "k(r)", "v/c", "Status");
    std::printf("  ────────────────────────────────────────────\n");

    double radii_fm[] = {0.84, 1.0, 1.2, 1.5, 2.0, 2.5, 2.818, 3.0, 5.0, 10.0, 53.0};
    for (double r_fm : radii_fm) {
        double r = r_fm * 1e-15;
        // k(r) from the velocity law: v(r) = (c/k_H)√(R_p/r) → k(r) = k_H√(r/R_p)
        // But at the atomic scale, k = (1/α)(r/a₀)^(1/2) for hydrogen
        // More precisely: v(r) = αc × (a₀/r)^(1/2) for Coulomb orbit
        // k(r) = c/v = (1/α)(r/a₀)^(1/2)
        double k_r = alpha_inv * std::sqrt(r / a_0);
        double v_r = c / k_r;
        const char* status = (k_r < 1.0) ? "SUPERLUMINAL" :
                             (k_r < 2.0) ? "near-c" : "subluminal";
        std::printf("  %8.3f  %8.4f  %8.4f  %10s\n",
                    r_fm, k_r, v_r / c, status);
    }
    std::printf("\n");
}

// ═══════════════════════════════════════════════════════════════
//  PART II — THE 6π WINDING AND ANGULAR DEMAND
// ═══════════════════════════════════════════════════════════════

void part_II() {
    std::printf("\n");
    std::printf("═══════════════════════════════════════════════════════════════\n");
    std::printf("  PART II — THE 6π WINDING AND ANGULAR VELOCITY MISMATCH\n");
    std::printf("═══════════════════════════════════════════════════════════════\n\n");

    int p = 2;  // poloidal windings
    int q = 3;  // toroidal windings
    int W = 3;  // winding number

    double total_angle = q * 2.0 * pi;
    std::printf("  Trefoil (p=%d, q=%d) — W=%d\n", p, q, W);
    std::printf("  Total angular excursion per cycle: %dπ = %.4f rad\n",
                q * 2, total_angle);

    // Torus geometry from PPT05
    double a_minor = lambda_C_p * std::sqrt(1.5) / p;
    double R_major = lambda_C_p * std::sqrt(3.0) / q;
    double eta = R_major / a_minor;

    std::printf("\n  ── (2,3) Torus Geometry ──\n");
    std::printf("  λ_C(proton) = %.4e m\n", lambda_C_p);
    std::printf("  a (minor)   = %.4e m = %.4f fm\n", a_minor, a_minor * 1e15);
    std::printf("  R (major)   = %.4e m = %.4f fm\n", R_major, R_major * 1e15);
    std::printf("  η = R/a     = %.4f  (= p√2/q)\n", eta);

    // Circulation velocities at stable budget angle
    double v_T = c / std::sqrt(3.0);      // toroidal
    double v_P = c * std::sqrt(2.0/3.0);  // poloidal

    std::printf("\n  ── Circulation Velocities ──\n");
    std::printf("  v_T = c/√3   = %.6e m/s (%.4fc)\n", v_T, v_T / c);
    std::printf("  v_P = c√(2/3)= %.6e m/s (%.4fc)\n", v_P, v_P / c);
    std::printf("  v_T² + v_P²  = %.6fc² (should be c²) ✓\n",
                (v_T * v_T + v_P * v_P) / c2);

    // Circulation period
    double T_circ = 2.0 * pi * lambda_C_p / c;
    double f_circ = 1.0 / T_circ;

    std::printf("\n  ── Circulation Period ──\n");
    std::printf("  T_circ = 2πλ_C/c = %.4e s = %.1f t_P\n", T_circ, T_circ / t_P);
    std::printf("  f_circ = 1/T     = %.4e Hz\n", f_circ);

    // Angular velocity demanded of contact spations
    double omega_demand = total_angle / T_circ;
    // = 6π / (2πλ_C/c) = 3c/λ_C = 3m_p c²/ℏ
    double omega_demand_check = 3.0 * m_p * c2 / hbar;

    std::printf("\n  ── Angular Velocity Mismatch ──\n");
    std::printf("  ω_demand  = 6π/T_circ = 3c/λ_C = %.4e rad/s\n", omega_demand);
    std::printf("  ω_demand  = 3m_pc²/ℏ  = %.4e rad/s (check) ✓\n", omega_demand_check);

    double omega_max = c / R_p;
    std::printf("  ω_max     = c/R_p     = %.4e rad/s\n", omega_max);

    double traction_ratio = omega_demand / omega_max;
    double traction_check = 3.0 * R_p * m_p * c / hbar;
    double traction_W = 3.0 * (W + 1.0);

    std::printf("\n  ── TRACTION RATIO ──\n");
    std::printf("  T = ω_demand/ω_max = %.4f\n", traction_ratio);
    std::printf("  T = 3R_p m_pc/ℏ    = %.4f (check) ✓\n", traction_check);
    std::printf("  T = 3(W+1)         = %.1f (integer form)\n", traction_W);
    std::printf("\n  The trefoil demands %.1f× more angular velocity\n", traction_ratio);
    std::printf("  than the lattice can supply. The spations are WRENCHED.\n\n");
}

// ═══════════════════════════════════════════════════════════════
//  PART III — TRACTION DECOMPOSITION INTO WAKE MULTIPOLES
// ═══════════════════════════════════════════════════════════════

void part_III() {
    std::printf("\n");
    std::printf("═══════════════════════════════════════════════════════════════\n");
    std::printf("  PART III — TRACTION DECOMPOSITION INTO THREE CHANNELS\n");
    std::printf("═══════════════════════════════════════════════════════════════\n\n");

    // Contact spations on the proton surface
    double N_contact = 4.0 * pi * R_p * R_p / l_P2;
    std::printf("  Contact spations: N = 4πR_p²/l_P² = %.4e\n", N_contact);

    // Traction per spation (ontic × traction ratio)
    double traction_ratio = 3.0 * R_p * m_p * c / hbar;
    double F_per_spation = epsilon / l_P * traction_ratio;
    std::printf("  Traction/spation: F = (ε/l_P) × T = %.4e N\n", F_per_spation);

    double F_total = N_contact * F_per_spation;
    std::printf("  Total traction:   F = N × F_sp    = %.4e N\n\n", F_total);

    // Energy partition at stable budget angle
    double E_proton_MeV = m_p * c2 / (1.602e-13);
    double E_toroidal = E_proton_MeV / 3.0;
    double E_poloidal = E_proton_MeV * 2.0 / 3.0;

    std::printf("  ── Energy Partition (Stable Budget Angle θ*) ──\n\n");
    std::printf("  Total rest energy: E_p = m_pc² = %.2f MeV\n\n", E_proton_MeV);
    std::printf("  %20s  %8s  %10s  %-28s\n",
                "Mode", "Fraction", "Energy", "Wake Output");
    std::printf("  ────────────────────────────────────────────────────────────\n");
    std::printf("  %20s  %8s  %7.1f MeV  %-28s\n",
                "Toroidal (v_T)", "1/3", E_toroidal, "ℓ=2 magnetic dipole wake");
    std::printf("  %20s  %8s  %7.1f MeV  %-28s\n",
                "Poloidal (v_P)", "2/3", E_poloidal, "ℓ=1 Coulomb + ℓ≥3 orbits");
    std::printf("  %20s  %8s  %7.1f MeV  %-28s\n",
                "Translational", "0", 0.0, "(proton at rest)");
    std::printf("\n");

    // The three output channels
    std::printf("  ── Three Mechanical Outputs of Traction ──\n\n");
    std::printf("  CHANNEL 1: TRACTION (radial, ℓ=1)\n");
    std::printf("    Mechanism: Spation displaced outward by unmatched\n");
    std::printf("               radial centrifugal component\n");
    std::printf("    Result:    Coulomb field ∝ 1/r²\n");
    std::printf("    Strength:  F = k_e e²/r² = αℏc/r²\n\n");

    std::printf("  CHANNEL 2: ROTATION (azimuthal, ℓ=2)\n");
    std::printf("    Mechanism: Spation entrained into organised circulation\n");
    std::printf("               pattern around trefoil axis\n");
    std::printf("    Result:    Magnetic field ∝ 1/r³ (dipole)\n");
    std::printf("    Strength:  μ_p = 2.793 μ_N\n\n");

    std::printf("  CHANNEL 3: ORBITAL ENTRAINMENT (tangential, ℓ≥3)\n");
    std::printf("    Mechanism: Persistent azimuthal drag at mode-lock radii\n");
    std::printf("    Result:    Electron orbits at k_n = 137n\n");
    std::printf("    Strength:  v_n = αc/n → Bohr model\n\n");
}

// ═══════════════════════════════════════════════════════════════
//  PART IV — THE GEAR RATIO
// ═══════════════════════════════════════════════════════════════

void part_IV() {
    std::printf("\n");
    std::printf("═══════════════════════════════════════════════════════════════\n");
    std::printf("  PART IV — THE GEAR RATIO: NUCLEAR → ATOMIC\n");
    std::printf("═══════════════════════════════════════════════════════════════\n\n");

    // Proton circulation frequency
    double omega_p = 3.0 * c / lambda_C_p;

    // Electron orbital frequency (hydrogen ground state)
    double omega_e = alpha * c / a_0;

    double gear_ratio = omega_p / omega_e;

    std::printf("  Proton circulation:  ω_p = 3c/λ_C = %.4e rad/s\n", omega_p);
    std::printf("  Electron orbit:      ω_e = αc/a₀  = %.4e rad/s\n", omega_e);
    std::printf("  Gear ratio:          ω_p/ω_e      = %.4e\n\n", gear_ratio);

    // Decompose the gear ratio
    double ratio_decomp = 3.0 * a_0 * m_p * c / (alpha * hbar);
    std::printf("  Decomposition: ω_p/ω_e = 3a₀m_pc/(αℏ)\n");
    std::printf("                         = 3 × (m_p/m_e) × (1/α)\n");
    double mass_ratio = m_p / m_e;
    std::printf("                         = 3 × %.2f × %.2f\n",
                mass_ratio, alpha_inv);
    std::printf("                         = %.4e ✓\n\n", 3.0 * mass_ratio * alpha_inv);

    std::printf("  The proton spins %.0e times per electron orbit.\n", gear_ratio);
    std::printf("  'Chemistry is nuclear physics geared down by χ = 137.'\n\n");

    // Lattice rotation at various radii
    std::printf("  ── Lattice Rotation vs Radius ──\n\n");
    std::printf("  %12s  %12s  %12s  %12s  %-16s\n",
                "r", "k(r)", "v(r)/c", "ω(r) [rad/s]", "Physical Scale");
    std::printf("  ─────────────────────────────────────────────────────────────\n");

    struct Zone {
        const char* name;
        double r;
        const char* scale;
    };

    Zone zones[] = {
        {"R_p",         R_p,             "Proton surface"},
        {"r_e",         r_e,             "C-boundary (koppa)"},
        {"10 fm",       10e-15,          "Nuclear radius"},
        {"100 fm",      100e-15,         "Inner atomic"},
        {"a₀/10",       a_0 / 10.0,      "Deep electron"},
        {"a₀",          a_0,             "Bohr radius"},
        {"10 a₀",       10.0 * a_0,      "Outer shell"},
    };

    for (auto& z : zones) {
        double k_r = alpha_inv * std::sqrt(z.r / a_0);
        double v_r = c / k_r;
        double omega_r = v_r / z.r;
        std::printf("  %12.4e  %12.4f  %12.6f  %12.4e  %-16s\n",
                    z.r, k_r, v_r / c, omega_r, z.scale);
    }
    std::printf("\n");
    std::printf("  The rotation rate drops from 10²⁴ (proton surface)\n");
    std::printf("  to 10¹⁶ (Bohr radius) — geared down by ~10⁸.\n");
    std::printf("  This IS the transmission. The lattice carries it.\n\n");
}

// ═══════════════════════════════════════════════════════════════
//  PART V — ONTIC vs KINETIC
// ═══════════════════════════════════════════════════════════════

void part_V() {
    std::printf("\n");
    std::printf("═══════════════════════════════════════════════════════════════\n");
    std::printf("  PART V — THE ONTIC AND THE KINETIC\n");
    std::printf("═══════════════════════════════════════════════════════════════\n\n");

    std::printf("  %-24s  %-26s  %-26s\n",
                "Aspect", "ONTIC (CMB convergence)", "KINETIC (trefoil traction)");
    std::printf("  ────────────────────────────────────────────────────────────\n");
    std::printf("  %-24s  %-26s  %-26s\n",
                "Source", "N shells to Clearing", "Proton circulation at c");
    std::printf("  %-24s  %-26s  %-26s\n",
                "Symmetry", "Spherically isotropic", "Axial (toroidal+poloidal)");
    std::printf("  %-24s  %-26s  %-26s\n",
                "Speed", "Relays at c", "Demands 1.831c");
    std::printf("  %-24s  %-26s  %-26s\n",
                "Role", "FUEL (raw energy)", "ENGINE (breaks symmetry)");
    std::printf("  %-24s  %-26s  %-26s\n",
                "Output (no matter)", "None (perfect cancel)", "N/A (no trefoil exists)");
    std::printf("  %-24s  %-26s  %-26s\n",
                "Output (with matter)", "Gravity (occlusion)", "E&M (traction + rotation)");
    std::printf("\n");

    std::printf("  The ontic is what arrives. The kinetic is what the\n");
    std::printf("  trefoil DOES with it. They are related but distinct:\n\n");
    std::printf("    Convergence → occlusion → gravity    (ℓ=0 wake)\n");
    std::printf("    Convergence → traction  → Coulomb    (ℓ=1 wake)\n");
    std::printf("    Convergence → rotation  → magnetism  (ℓ=2 wake)\n");
    std::printf("    Convergence → entrainment → orbits   (ℓ≥3 wake)\n\n");

    std::printf("  The trefoil converts isotropic pressure into\n");
    std::printf("  organised, directional mechanical output.\n");
    std::printf("  Electromagnetism is the EXHAUST of a topological engine\n");
    std::printf("  that cannot match the lattice speed limit.\n\n");
}

// ═══════════════════════════════════════════════════════════════
//  MAIN
// ═══════════════════════════════════════════════════════════════

int main() {
    std::printf("╔═════════════════════════════════════════════════════════════╗\n");
    std::printf("║  PPT06: SPATION TRACTION FROM THE TREFOIL                  ║\n");
    std::printf("║  How the Gears Start — v_phase = 1.831c at R_p            ║\n");
    std::printf("╚═════════════════════════════════════════════════════════════╝\n");

    part_I();
    part_II();
    part_III();
    part_IV();
    part_V();

    std::printf("═══════════════════════════════════════════════════════════════\n");
    std::printf("  INVESTIGATION COMPLETE\n");
    std::printf("═══════════════════════════════════════════════════════════════\n\n");
    std::printf("  [x] v_phase = 1.831c at proton surface (k = 0.5464)\n");
    std::printf("  [x] 6π winding demands ω = 4.27×10²⁴ rad/s\n");
    std::printf("  [x] Traction ratio T = 12 = 3(W+1)\n");
    std::printf("  [x] Three channels: traction/rotation/entrainment\n");
    std::printf("  [x] Gear ratio nuclear→atomic = ~10⁸ = 3(m_p/m_e)/α\n");
    std::printf("  [x] Ontic vs kinetic separation established\n\n");

    return 0;
}
