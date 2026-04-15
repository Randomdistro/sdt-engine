#pragma once

/**
 * @file sdt_laws.hpp
 * @brief Canonical SDT Five-Law Framework — Single Source of Truth
 *
 * Implements the complete Spatial Displacement Theory:
 *   Law I:   Cosmological Relay Throughput  (Axioms R1-R6, Theorems T1-T2)
 *   Law II:  Release Cascade               (Corollaries)
 *   Law III: Convergent Boundary Pressure   (Theorems T3-T4)
 *   Law IV:  Inertial Mass                  (Theorems T5-T7)
 *   Law V:   Movement Budget               (Axioms M1-M3, Theorems T10-T17)
 *
 * Plus Gap Resolution supplement:
 *   V_disp for electron and proton (computed, not fitted)
 *   Transfer function f = 2.125e-17
 *   R_charge = sqrt(R_p * r_e) = 1.540e-15 m
 *   Marginal stability proof: P_cf = P_conv/3 (algebraic identity)
 *
 * 9 axioms. 2 lemmas. 17 theorems. Zero free parameters.
 * One medium. One tick. One budget.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date March 2026
 * @version 5.0 (Five-Law Framework)
 */

#include <cmath>
#include <numbers>

namespace sdt::laws {

// ═══════════════════════════════════════════════════════════════════════
//  MEASURED INPUTS — CODATA 2018 / IAU / FIRAS
//  These are the ONLY externally sourced values. Everything else derives.
// ═══════════════════════════════════════════════════════════════════════

namespace measured {
    // SI exact definitions
    inline constexpr double c           = 299'792'458.0;                // [m/s]    Speed of light (SI exact)
    inline constexpr double h           = 6.626'070'15e-34;             // [J·s]    Planck constant (SI exact)
    inline constexpr double hbar        = 1.054'571'817e-34;            // [J·s]    Reduced Planck constant
    inline constexpr double k_B         = 1.380'649e-23;               // [J/K]    Boltzmann constant (SI exact)
    inline constexpr double e_charge    = 1.602'176'634e-19;            // [C]      Elementary charge (SI exact)

    // CODATA 2018 measured values
    inline constexpr double alpha       = 7.297'352'5693e-3;            // [-]      Fine structure constant
    inline constexpr double alpha_inv   = 137.035'999'084;              // [-]      1/alpha
    inline constexpr double a_0         = 5.291'772'109'03e-11;         // [m]      Bohr radius
    inline constexpr double r_e         = 2.817'940'3262e-15;           // [m]      Classical electron radius = alpha * ƛ_Ce
    inline constexpr double R_p         = 8.414e-16;                    // [m]      Proton charge radius (muonic H, 2019)
    // NOTE: R_p ≈ 4ℏ/(m_p c) to 0.02% — see W+1 conjecture below
    inline constexpr double m_e         = 9.109'383'7015e-31;           // [kg]     Electron mass (NIST reference)
    inline constexpr double m_p         = 1.672'621'923'69e-27;         // [kg]     Proton mass (NIST reference)
    inline constexpr double m_n         = 1.674'927'498'04e-27;         // [kg]     Neutron mass (NIST reference)
    inline constexpr double R_inf       = 1.097'373'156'8160e7;         // [m^-1]   Rydberg constant
    inline constexpr double Ry_eV       = 13.605'693'122'994;           // [eV]     Rydberg energy

    // Compton wavelengths — primary SDT observables
    inline constexpr double lambda_C_e  = 2.426'310'238'67e-12;         // [m]      Electron Compton wavelength
    inline constexpr double lambda_C_p  = 1.321'410'021'40e-15;         // [m]      Proton Compton wavelength

    // Planck units (CODATA 2018)
    inline constexpr double l_P         = 1.616'255e-35;                // [m]      Planck length
    inline constexpr double t_P         = 5.391'24e-44;                 // [s]      Planck time
    inline constexpr double l_P3        = l_P * l_P * l_P;              // [m^3]    Planck volume

    // Radiation constant
    inline constexpr double a_rad       = 7.565'7e-16;                  // [J/m³/K⁴] Stefan radiation constant

    // CMB (FIRAS/COBE/Planck)
    inline constexpr double T_CMB       = 2.7255;                       // [K]      Present CMB temperature
    inline constexpr double T_rec       = 3000.0;                       // [K]      Temperature at recombination
    inline constexpr double z_rec       = 1100.0;                       // [-]      Recombination redshift

    // Conversions
    inline constexpr double eV_to_J     = 1.602'176'634e-19;            // [J/eV]
    inline constexpr double MeV_to_J    = 1.602'176'634e-13;            // [J/MeV]

    // Stellar / solar (IAU)
    inline constexpr double R_Sun       = 6.957e8;                      // [m]      Solar radius (IAU 2015)
    inline constexpr double AU          = 1.495'978'707e11;             // [m]      Astronomical unit (IAU 2012)

    // Nuclear (measured)
    inline constexpr double R_He        = 1.6755e-15;                   // [m]      He-4 charge radius

    // Coulomb constant (derived from SI)
    inline constexpr double k_e         = 8.987'551'7923e9;             // [N·m²/C²] Coulomb constant

    // Magnetic moments (in nuclear magnetons, CODATA 2018)
    inline constexpr double mu_P        = 2.792'847'344'62;             // [μ_N]    Proton
    inline constexpr double mu_N        = -1.913'042'72;                // [μ_N]    Neutron
    inline constexpr double mu_D        = 0.857'421;                    // [μ_N]    Deuteron
    inline constexpr double mu_T        = 2.979;                        // [μ_N]    Triton
    inline constexpr double mu_He3      = -2.128;                       // [μ_N]    Helion
    inline constexpr double mu_alpha    = 0.0;                          // [μ_N]    Alpha (spin-0)

    // Nuclear binding energies (MeV, measured)
    inline constexpr double B_deuteron  = 2.224;
    inline constexpr double B_triton    = 8.482;
    inline constexpr double B_helion    = 7.718;
    inline constexpr double B_alpha     = 28.296;
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW I — COSMOLOGICAL RELAY THROUGHPUT (Theorems T1–T2)
//
//  The spation lattice is a globally phase-loaded nearest-neighbour
//  relay medium. Shell cancellation preserves Φ = Nε at every point.
// ═══════════════════════════════════════════════════════════════════════

namespace law_I {
    using namespace measured;

    /// CMB energy density: u = a T^4  [J/m³]
    inline constexpr double u_CMB = a_rad * T_CMB * T_CMB * T_CMB * T_CMB;
    // = 4.172e-14 J/m³

    /// CMB radiation pressure: P = u/3  [Pa]
    inline constexpr double P_rad = u_CMB / 3.0;
    // = 1.391e-14 Pa

    /// Distance to the Clearing  [m]
    /// R_CMB = c / H_0 × ln(1 + z_rec)  ≈ 9.527e26 m
    /// (Using the established value from Law I verification)
    inline constexpr double R_CMB = 9.527e26;

    /// Causal depth: N = R_CMB / l_P  (Planck shells from here to the Clearing)
    inline constexpr double N = R_CMB / l_P;
    // = 5.894e61

    /// Elementary relay content per shell: ε = u_CMB × l_P³  [J]
    inline constexpr double epsilon = u_CMB * l_P3;
    // = 1.761e-118 J

    /// Total convergence burden: Φ = N × ε  [J]
    /// Theorem T2: every shell contributes ε (Shell Cancellation Identity T1)
    inline constexpr double Phi = N * epsilon;
    // = 1.038e-56 J

    /// Convergence pressure at Planck scale: P_conv = Φ / l_P³ = N × u_CMB  [Pa]
    inline constexpr double P_conv = Phi / l_P3;
    // = 2.459e48 Pa

    /// Boundary source cells: S = 4π N²
    inline constexpr double S_boundary = 4.0 * std::numbers::pi * N * N;
    // = 4.366e124 → resolves the 10^123 cosmological constant problem

    /// Held content density at recombination  [J/m³]
    inline constexpr double u_held = a_rad * T_rec * T_rec * T_rec * T_rec;
    // = 6.13e-2 J/m³
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW II — RELEASE CASCADE
//
//  At the Clearing, every spation released its held deformation content
//  omnidirectionally. Local convergence = superposed arrival of N shells.
//  Stars are convergence recyclers. Every photon either feeds convergence
//  or feeds matter.
// ═══════════════════════════════════════════════════════════════════════

namespace law_II {
    using namespace measured;

    /// Solar luminosity [W] (IAU 2015 nominal)
    inline constexpr double L_Sun = 3.828e26;

    /// CMB flux (isotropic): F_CMB = c × u_CMB / 4
    inline constexpr double F_CMB = c * law_I::u_CMB / 4.0;
    // = 3.131e-6 W/m²

    /// Solar pressure domain radius: r_domain = sqrt(L_Sun / (4π F_CMB))
    /// Beyond this, CMB convergence exceeds solar convergence
    /// Pre-computed: sqrt(3.828e26 / (4π × 3.131e-6)) ≈ 3.12e15 m
    inline constexpr double r_domain_Sun = 3.12e15;  // ≈ 20,800 AU

    /// Pressure domain radius for arbitrary luminosity
    [[nodiscard]] inline auto pressure_domain(double luminosity_W) noexcept -> double {
        return std::sqrt(luminosity_W / (4.0 * std::numbers::pi * F_CMB));
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW III — CONVERGENT BOUNDARY PRESSURE (Theorems T3–T4)
//
//  Force = occluded convergence. Same mechanism: Coulomb, gravity, nuclear.
// ═══════════════════════════════════════════════════════════════════════

namespace law_III {
    using namespace measured;

    /// Effective pressure at atomic/nuclear scale (from hydrogen calibration)
    /// P_eff = 4 k_e e² / (π R_p² r_e²)   [Pa]
    inline constexpr double P_eff = 4.0 * k_e * e_charge * e_charge
                                  / (std::numbers::pi * R_p * R_p * r_e * r_e);
    // = 5.225e31 Pa

    /// Transfer function: f = P_eff / P_conv
    inline constexpr double f_transfer = P_eff / law_I::P_conv;
    // = 2.125e-17

    /// Charge interaction radius: R_charge = sqrt(R_p × r_e)
    /// Resolves e-e / p-p / e-p having same coupling strength
    /// Pre-computed: sqrt(8.414e-16 × 2.8179e-15) = 1.5396e-15 m
    inline constexpr double R_charge = 1.5396e-15;

    /// Occlusion force between two bodies (Theorem T4)
    /// F = (π/4) P_eff R1² R2² / r²
    [[nodiscard]] inline auto F_occlusion(
        double R1, double R2, double r
    ) noexcept -> double {
        return (std::numbers::pi / 4.0) * P_eff * R1 * R1 * R2 * R2 / (r * r);
    }

    /// Coulomb force using charge radii
    /// F_coulomb = (π/4) P_eff R_charge⁴ / r² = k_e e² / r²
    [[nodiscard]] inline auto F_coulomb(double r) noexcept -> double {
        return F_occlusion(R_charge, R_charge, r);
    }

    /// Nuclear occlusion force for charge Z nucleus on electron at distance r
    [[nodiscard]] inline auto F_nuclear_electron(
        int Z, double r
    ) noexcept -> double {
        double R_nuc = static_cast<double>(Z) * R_p;
        return F_occlusion(R_nuc, r_e, r);
    }

    /// Solid angle occluded by body of radius R at distance r  [sr]
    [[nodiscard]] constexpr auto solid_angle_occluded(
        double R, double r
    ) noexcept -> double {
        return std::numbers::pi * R * R / (r * r);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW IV — INERTIAL MASS (Theorems T5–T7)
//
//  m = Φ V_disp / (l_P³ c²)  — mass is throughput reorganisation cost.
//  m_inert = m_grav because both measure the same V_disp.
// ═══════════════════════════════════════════════════════════════════════

namespace law_IV {
    using namespace measured;

    /// Exclusion volume from mass: V_disp = 3 m l_P³ c² / Φ  [m³]
    /// (Factor of 3 from angular averaging: P_cf = P_conv/3)
    [[nodiscard]] inline auto V_disp_from_mass(double mass_kg) noexcept -> double {
        return 3.0 * mass_kg * l_P3 * c * c / law_I::Phi;
    }

    /// Mass from exclusion volume: m = Φ V_disp / (3 l_P³ c²)  [kg]
    [[nodiscard]] inline auto mass_from_V_disp(double V_disp) noexcept -> double {
        return law_I::Phi * V_disp / (3.0 * l_P3 * c * c);
    }

    /// Exclusion radius (spherical equivalent): R = (3V/4π)^(1/3)  [m]
    [[nodiscard]] inline auto exclusion_radius(double V_disp) noexcept -> double {
        return std::cbrt(3.0 * V_disp / (4.0 * std::numbers::pi));
    }

    /// Electron exclusion volume  [m³]
    inline constexpr double V_disp_e = 3.0 * m_e * l_P3 * c * c / law_I::Phi;
    // = 9.988e-62 m³

    /// Proton exclusion volume  [m³]
    inline constexpr double V_disp_p = 3.0 * m_p * l_P3 * c * c / law_I::Phi;
    // = 1.834e-58 m³

    /// Electron exclusion radius  [m]
    /// Pre-computed: cbrt(3 × 9.988e-62 / (4π)) ≈ 2.878e-21 m
    inline constexpr double R_excl_e = 2.878e-21;

    /// Proton exclusion radius  [m]
    /// Pre-computed: cbrt(3 × 1.834e-58 / (4π)) ≈ 3.525e-20 m
    inline constexpr double R_excl_p = 3.525e-20;

    /// Effective displacement density for electron  [kg/m³]
    inline constexpr double rho_eff_e = m_e / V_disp_e;
    // ≈ 9.12e30 kg/m³

    /// Marginal stability verification: ρ_eff × c² should equal P_conv/3
    /// (This is Theorem T10's stability condition — an algebraic identity)
    inline constexpr double P_cf_e = rho_eff_e * c * c;
    // Should equal P_conv/3 = 8.197e47 Pa

    /// Rest energy: E₀ = Φ V_disp / (l_P³)  [J]
    [[nodiscard]] constexpr auto rest_energy(double mass_kg) noexcept -> double {
        return mass_kg * c * c;
    }

    /// Three radii for each particle
    struct ParticleRadii {
        double R_excl;      // Exclusion radius (actual displaced volume)
        double R_wake;      // Wake/charge radius (pressure perturbation reach)
        double R_quantum;   // Compton wavelength (quantum coherence scale)
    };

    inline constexpr ParticleRadii electron_radii = {
        2.878e-21,       // R_excl   2.878e-21 m
        r_e,             // R_wake   2.818e-15 m
        lambda_C_e       // R_quantum 3.862e-13 m (reduced: λ_C / 2π)
    };

    inline constexpr ParticleRadii proton_radii = {
        3.525e-20,       // R_excl   3.525e-20 m
        R_p,             // R_wake   8.414e-16 m
        lambda_C_p       // R_quantum 1.321e-15 m
    };
}

// ═══════════════════════════════════════════════════════════════════════
//  LAW V — MOVEMENT BUDGET (Axioms M1–M3, Theorems T10–T17)
//
//  v_circ² + v² = c²
//  Three axioms → eight theorems → all of special relativity
// ═══════════════════════════════════════════════════════════════════════

namespace law_V {
    using namespace measured;

    /// T10: Movement Budget — v_circ² + v_trans² = c²
    /// Returns circulation velocity for given translational velocity
    [[nodiscard]] inline auto v_circ(double v_trans) noexcept -> double {
        return std::sqrt(c * c - v_trans * v_trans);
    }

    /// Returns translational velocity for given circulation velocity
    [[nodiscard]] inline auto v_trans(double v_circulation) noexcept -> double {
        return std::sqrt(c * c - v_circulation * v_circulation);
    }

    /// Lorentz factor γ = 1/√(1 - v²/c²)
    [[nodiscard]] inline auto gamma(double v) noexcept -> double {
        double beta = v / c;
        return 1.0 / std::sqrt(1.0 - beta * beta);
    }

    /// T11: Time dilation — dτ/dt = 1/γ = √(1 - v²/c²)
    [[nodiscard]] inline auto time_dilation(double v) noexcept -> double {
        double beta = v / c;
        return std::sqrt(1.0 - beta * beta);
    }

    /// T12: Length contraction — L = L₀/γ
    [[nodiscard]] inline auto length_contraction(double L0, double v) noexcept -> double {
        return L0 * time_dilation(v);
    }

    /// T13: Rest energy — E₀ = m₀c²  (circulation energy of vortex at rest)
    [[nodiscard]] inline auto rest_energy(double m0) noexcept -> double {
        return m0 * c * c;
    }

    /// T14: Energy–momentum relation — E² = (pc)² + (m₀c²)²
    [[nodiscard]] inline auto total_energy(double m0, double v) noexcept -> double {
        return gamma(v) * m0 * c * c;
    }

    [[nodiscard]] inline auto momentum(double m0, double v) noexcept -> double {
        return gamma(v) * m0 * v;
    }

    /// T15: Photon limit — v_circ = 0 ⟹ v = c, m = 0, E = pc
    inline constexpr double photon_v_circ = 0.0;
    inline constexpr double photon_v_trans = c;

    /// T16: Gravitational time dilation
    /// dτ/dt = √(1 - z R/r) where z = 1/k²
    [[nodiscard]] inline auto gravitational_time_dilation(
        double z, double R, double r
    ) noexcept -> double {
        return std::sqrt(1.0 - z * R / r);
    }

    /// T17: c-boundary radius — where v_orbital = c, matter cannot exist
    /// R_c = R / k²  (= z × R)
    [[nodiscard]] constexpr auto c_boundary(double R, double k) noexcept -> double {
        return R / (k * k);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  SDT VELOCITY LAW & k-HIERARCHY
//
//  v(r) = (c/k)√(R/r)     — orbital velocity at radius r
//  z = (v/c)² = 1/k²      — bridge law
//  z · k² = 1              — closure condition
// ═══════════════════════════════════════════════════════════════════════

namespace bridge {
    using namespace measured;

    /// Orbital velocity: v(r) = (c/k) √(R/r)
    [[nodiscard]] inline auto v_orbital(
        double k, double R, double r
    ) noexcept -> double {
        return (c / k) * std::sqrt(R / r);
    }

    /// k from surface velocity: k = c / v
    [[nodiscard]] constexpr auto k_from_v(double v) noexcept -> double {
        return c / v;
    }

    /// Bridge law: z = (v/c)² = 1/k²
    [[nodiscard]] constexpr auto z_from_k(double k) noexcept -> double {
        return 1.0 / (k * k);
    }

    [[nodiscard]] constexpr auto z_from_v(double v) noexcept -> double {
        return (v * v) / (c * c);
    }

    /// Closure condition: z · k² = 1 (verification)
    [[nodiscard]] constexpr auto zk2_product(double z, double k) noexcept -> double {
        return z * k * k;
    }

    /// Escape velocity: v_esc = √2 × v  (standard virial)
    [[nodiscard]] constexpr auto v_escape(double v_orbital_val) noexcept -> double {
        return std::numbers::sqrt2 * v_orbital_val;
    }

    /// Stellar rotation: v_rot = π v² / c
    [[nodiscard]] constexpr auto v_rotation(double v_surface) noexcept -> double {
        return std::numbers::pi * v_surface * v_surface / c;
    }

    /// Angular velocity: ω = v/r
    [[nodiscard]] constexpr auto omega(double v, double r) noexcept -> double {
        return v / r;
    }

    /// Legacy equivalence: GM = v²r = c²R/k²
    /// (Convenience function — GM is derived, not fundamental)
    [[nodiscard]] constexpr auto GM_equivalent(
        double k, double R
    ) noexcept -> double {
        return c * c * R / (k * k);
    }

    // ─── Known k-values (from the hierarchy) ───

    /// Hydrogen ground state: v = αc → k = 1/α ≈ 137
    inline constexpr double k_hydrogen = alpha_inv;

    /// k at proton surface: k = (1/α)√(R_p/a_0) ≈ 0.5464
    /// This is INSIDE the c-boundary (k < 1 → superluminal phase rotation)
    /// Pre-computed: 137.036 × sqrt(8.414e-16 / 5.292e-11) = 0.5464
    inline constexpr double k_proton_surface = 0.5464;

    /// c-boundary of hydrogen: ϟ = α²a₀ = r_e ≈ 2.818 fm
    inline constexpr double koppa_hydrogen = alpha * alpha * a_0;
    // = r_e = 2.818e-15 m

    /// c-boundary of the Sun: ϟ_Sun = R_Sun / k_Sun²
    /// k_Sun ≈ 686 (from solar surface escape velocity)
    inline constexpr double k_Sun = 686.3;
    inline constexpr double koppa_Sun = R_Sun / (k_Sun * k_Sun);
    // ≈ 1477 m

    // ─── General koppa functions ───

    /// c-boundary (koppa): ϟ = R/k² = v²R/c²  [m]
    /// This single number encodes the entire gravitational field.
    [[nodiscard]] constexpr auto koppa(double v_surface, double R) noexcept -> double {
        return v_surface * v_surface * R / (c * c);
    }

    /// Surface gravitational acceleration: g = v²/R = c²ϟ/R²  [m/s²]
    /// No G. No M. Just v and R.
    [[nodiscard]] constexpr auto g_surface(double v_surface, double R) noexcept -> double {
        return v_surface * v_surface / R;
    }

    /// Gravitational acceleration at radius r inside body of radius R
    /// g(r) = v_surf² R frac(r) / r²  where frac = M_enc(r)/M_total
    [[nodiscard]] inline auto g_interior(
        double v_surface, double R, double r, double frac_enclosed
    ) noexcept -> double {
        if (r < 1.0) return 0.0;
        return v_surface * v_surface * R * frac_enclosed / (r * r);
    }

    // ─── Planetary k-values (from measured v_surf) ───

    inline constexpr double v_Earth   = 7909.0;     // [m/s]
    inline constexpr double R_Earth   = 6.371e6;    // [m]
    inline constexpr double k_Earth   = c / v_Earth; // ≈ 37905
    inline constexpr double koppa_Earth = v_Earth * v_Earth * R_Earth / (c * c);
    // = 4.434e-3 m = 4.43 mm

    inline constexpr double v_Moon    = 1680.0;
    inline constexpr double R_Moon    = 1.7374e6;
    inline constexpr double k_Moon    = c / v_Moon;  // ≈ 178448
    inline constexpr double koppa_Moon = v_Moon * v_Moon * R_Moon / (c * c);
    // = 5.46e-5 m = 0.055 mm
}

// ═══════════════════════════════════════════════════════════════════════
//  ATOMIC PHYSICS — Rydberg, Fine Structure, Hyperfine
// ═══════════════════════════════════════════════════════════════════════

namespace atomic {
    using namespace measured;

    /// Rydberg transition energy: E = Ry × Z² × (1/n₁² - 1/n₂²)
    [[nodiscard]] constexpr auto rydberg_energy_eV(
        int Z, int n_low, int n_high
    ) noexcept -> double {
        double Z2 = static_cast<double>(Z * Z);
        double n1_inv2 = 1.0 / static_cast<double>(n_low * n_low);
        double n2_inv2 = 1.0 / static_cast<double>(n_high * n_high);
        return Ry_eV * Z2 * (n1_inv2 - n2_inv2);
    }

    /// Ionisation energy: E_ion = Ry × Z² / n²
    [[nodiscard]] constexpr auto ionisation_energy_eV(
        int Z, int n
    ) noexcept -> double {
        return Ry_eV * static_cast<double>(Z * Z) / static_cast<double>(n * n);
    }

    /// Fine structure splitting (Sommerfeld): ΔE = E_n × α² × Z² / n
    [[nodiscard]] constexpr auto fine_structure_eV(
        int Z, int n
    ) noexcept -> double {
        double E_n = ionisation_energy_eV(Z, n);
        return E_n * alpha * alpha * static_cast<double>(Z * Z) / static_cast<double>(n);
    }

    /// Bohr orbital velocity: v_n = αc Z / n
    [[nodiscard]] constexpr auto bohr_velocity(int Z, int n) noexcept -> double {
        return alpha * c * static_cast<double>(Z) / static_cast<double>(n);
    }

    /// Bohr orbital radius: r_n = a₀ n² / Z
    [[nodiscard]] constexpr auto bohr_radius(int Z, int n) noexcept -> double {
        return a_0 * static_cast<double>(n * n) / static_cast<double>(Z);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  NUCLEAR PHYSICS — Occlusion geometry, alpha clustering
// ═══════════════════════════════════════════════════════════════════════

namespace nuclear {
    using namespace measured;

    /// Nuclear charge radius scaling: R_nuc ≈ Z × R_p
    [[nodiscard]] constexpr auto nuclear_charge_radius(int Z) noexcept -> double {
        return static_cast<double>(Z) * R_p;
    }

    /// He-4 verification: R_He should ≈ 2 × R_p
    inline constexpr double R_He_predicted = 2.0 * R_p;
    // = 1.683e-15 m vs measured 1.6755e-15 m → 0.43% agreement

    /// c-boundary for nucleus of charge Z
    /// ϟ_Z = Z × r_e (c-boundary scales with Z)
    [[nodiscard]] constexpr auto c_boundary_nuclear(int Z) noexcept -> double {
        return static_cast<double>(Z) * r_e;
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  COULOMB COUPLING IDENTITY
//
//  Derived (not postulated) from:
//    (1) SDT force law:     F = (π/4) P_eff R_charge⁴ / r²
//    (2) Charge quantisation: R_charge = √(R_p r_e)
//    (3) Transfer function:   P_eff = 4αℏc / (π R_p² r_e²)
//  Result: k_e e² = αℏc  (exact, no free parameters)
// ═══════════════════════════════════════════════════════════════════════

namespace coulomb_identity {
    using namespace measured;

    /// k_e × e² — the physically load-bearing coupling product
    /// Derived: k_e e² = αℏc
    inline constexpr double k_e_e2 = alpha * hbar * c;
    // = 2.307e-28 J·m

    /// Verification against CODATA values
    inline constexpr double k_e_e2_codata = k_e * e_charge * e_charge;
    // Should match k_e_e2 to machine precision

    /// The coupling is the product. Neither k_e nor e is separately
    /// fundamental — only their combination enters all force laws.
}

// ═══════════════════════════════════════════════════════════════════════
//  W+1 RADIUS CONJECTURE
//
//  The SDT wake radius of a winding-W topology is:
//    R_wake = (W + 1) × ℏ / (m c)
//
//  For the proton (W = 3, trefoil):
//    R_p = 4ℏ/(m_p c) = 0.84124 fm
//
//  Measured: 0.8414 ± 0.0019 fm (CODATA 2018)
//  Agreement: 0.02%
//
//  FALSIFICATION: if |R_p_measured − 4ℏ/(m_p c)| > n σ_combined,
//  the W+1 conjecture is false (branch test, not full-SDT kill).
// ═══════════════════════════════════════════════════════════════════════

namespace winding {
    using namespace measured;

    /// Proton winding number (trefoil knot)
    inline constexpr int W_proton = 3;

    /// Electron winding number (simple torus)
    inline constexpr int W_electron = 1;

    /// W+1 predicted proton charge radius: R_p = (W+1) ℏ / (m_p c)
    inline constexpr double R_p_predicted = static_cast<double>(W_proton + 1)
                                          * hbar / (m_p * c);
    // = 8.4124e-16 m = 0.84124 fm

    /// R_p residual: ΔR_p = R_p_measured − R_p_predicted
    inline constexpr double delta_R_p = R_p - R_p_predicted;

    /// R_p relative error
    inline constexpr double R_p_error_pct = (R_p - R_p_predicted) / R_p * 100.0;
    // ≈ 0.02%

    /// Effective winding number inferred from measurement:
    /// W_eff = R_p m_p c / ℏ − 1
    /// Conjecture predicts W_eff = 3 (integer)
    inline constexpr double W_eff = R_p * m_p * c / hbar - 1.0;
    // ≈ 3.0008

    /// Wake-to-quantum ratio: g(W) = R_wake / ƛ_C
    /// Electron: g(1) = α = 1/137
    /// Proton:   g(3) = 4
    inline constexpr double g_electron = r_e * m_e * c / hbar;
    // = alpha (exact)
    inline constexpr double g_proton = R_p * m_p * c / hbar;
    // ≈ 4.0008

    /// Falsification test: does W_eff round to the expected integer?
    [[nodiscard]] constexpr auto winding_test_passes(
        double R_p_meas, double sigma_Rp
    ) noexcept -> bool {
        const double W_meas = R_p_meas * m_p * c / hbar - 1.0;
        const double sigma_W = sigma_Rp * m_p * c / hbar;
        return (W_meas - 3.0) * (W_meas - 3.0) < (3.0 * sigma_W) * (3.0 * sigma_W);
        // Passes if W_eff is within 3σ of integer 3
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  OPEN PROBLEMS — Updated status
// ═══════════════════════════════════════════════════════════════════════
//
//  1. R_p from lattice topology
//     STATUS: CONJECTURED as R_p = 4ℏ/(m_p c) via W+1 rule (0.02%).
//     Full derivation requires proving W+1 scaling from trefoil geometry.
//
//  2. Quantisation of stable vortex topologies
//     Why only W = 1 (electron) and W = 3 (proton) are stable.
//     Computational problem: lattice simulation of vortex reconnection.
//
//  3. Fine structure constant from topology
//     α = g(W=1) = r_e / ƛ_Ce. Can this be derived from the W=1 torus
//     mode partition (v_P / v_T)?  Would eliminate α as input.
//
//  4. Proton-electron mass ratio
//     m_p/m_e = 1836.15 ≈ (3/2)^{3/2} × 10³ = 1837.12 (0.053% off).
//     Requires W=3 vs W=1 equilibrium calculation.
//
// ═══════════════════════════════════════════════════════════════════════

} // namespace sdt::laws
