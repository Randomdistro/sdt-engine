/**
 * @file earth_magnetosphere.hpp
 * @brief Earth's Magnetosphere & Solar Wind Interaction — SDT State28D Description
 *
 * Uses the 28D state manifold to describe:
 *   1. Earth as a toroidal exclusion topology (iron core = trefoil ensemble)
 *   2. Solar wind as a wake-conditioned proton/electron flux
 *   3. Magnetosphere as the Earth's ℓ=2 quadrupole wake boundary
 *   4. Bow shock, magnetopause, and reconnection as wake-wake collisions
 *
 * SDT interpretation: The magnetosphere is NOT a "field" around Earth.
 * It is the ℓ=2 quadrupole component of Earth's wake — the organized
 * circulation imprint of Earth's core vortex on the surrounding medium.
 * Solar wind is the Sun's ℓ=1 dipole wake (radial pressure deficit)
 * plus ℓ=2 quadrupole (organized Parker spiral flow).
 *
 * The interaction is wake overlap: two ℓ-expansions interfering.
 *
 * All constants from sdt_laws.hpp. Zero external dependencies.
 *
 * @author SDT Canonical Engine — James Tyndall
 * @date March 2026
 */

#pragma once

#include "state28d.hpp"
#include "laws.hpp"
#include <cmath>
#include <numbers>

namespace sdt::magnetosphere {

using namespace sdt::laws;
using namespace sdt::laws::measured;

// ═══════════════════════════════════════════════════════════════════════
//  EARTH — 28D STATE DESCRIPTION
// ═══════════════════════════════════════════════════════════════════════

namespace earth {
    // Physical constants
    inline constexpr double R_earth        = 6.371e6;        // [m] Mean radius
    inline constexpr double M_earth        = 5.972e24;       // [kg] Mass
    inline constexpr double omega_earth    = 7.292e-5;       // [rad/s] Rotation rate
    inline constexpr double B_surface      = 3.12e-5;        // [T] Mean surface dipole field
    inline constexpr double mu_earth       = 8.0e22;         // [A·m²] Magnetic dipole moment
    inline constexpr double R_core         = 3.486e6;        // [m] Outer core radius
    inline constexpr double R_inner_core   = 1.216e6;        // [m] Inner core radius

    // SDT derived
    inline constexpr double GM_earth       = 3.986e14;       // [m³/s²]
    inline constexpr double k_earth        = c / 7909.0;     // k from surface orbital v ≈ 7909 m/s
    inline constexpr double koppa_earth    = R_earth / (k_earth * k_earth);
    // ϟ_earth ≈ 44 mm — the c-boundary radius of Earth

    /**
     * @brief Construct Earth as a State28D object
     *
     * Earth's core is a toroidal convection system:
     * - T_1 = outer core radius (the "ring" of the toroidal flow)
     * - T_2 = inner core radius (the "tube" around which flow wraps)
     * - The ℓ=2 wake = magnetic dipole field
     * - Chirality Φ_3 = +1 (right-hand rule, geographic south = magnetic north)
     */
    inline State28D create_state() {
        State28D e;

        // Level 1: Existence
        e.xi_0 = 1.0;  // Exists

        // Level 2: Position (heliocentric)
        e.xi_10 = AU;                    // Distance from Sun [m]
        e.xi_11 = 29783.0;              // Orbital velocity [m/s]

        // Level 3: Plane
        e.xi_p0 = 1.0;                  // Inside its own boundary
        e.xi_p1 = std::numbers::pi * R_earth * R_earth;  // Cross-sectional area [m²]
        e.xi_p2 = 23.44 * std::numbers::pi / 180.0;      // Axial tilt [rad]

        // Level 4: Sphere
        e.xi_s0 = (4.0/3.0) * std::numbers::pi * R_earth * R_earth * R_earth;  // Volume [m³]
        e.xi_s1 = 0.0;                  // No bulk radial expansion
        e.xi_s2 = omega_earth;          // Rotation rate [rad/s]
        e.xi_s3 = 1.0;                  // Axis magnitude (unit)

        // Level 5: Torus — Earth's core as toroidal convection cell
        // The liquid outer core is a toroidal flow system driven by
        // convergent pressure heating from below
        e.T_1 = R_core;                 // Central ring = outer core radius [m]
        e.T_2 = R_core - R_inner_core;  // Tube diameter = shell thickness [m]
        e.T_3 = 4.0 * std::numbers::pi * R_core * R_core;  // Toroidal surface area [m²]
        // T_4: Polarised volume × pressure = magnetic dipole moment (in mechanical units)
        // μ_earth [A·m²] maps to wake circulation strength
        e.T_4 = mu_earth;               // [A·m² ≡ J/T ≡ mechanical wake moment]
        // T_5: Pressure gradient from core to surface
        e.T_5 = 330e9 / R_earth;        // ~330 GPa core pressure / R_earth [Pa/m]

        // Level 6: Dynamism
        e.Phi_0 = 4.0 * std::numbers::pi;  // Omnidirectional (full sphere)
        e.Phi_1 = 0.0;                  // No bulk acceleration (stable orbit)
        e.Phi_2 = 1.0 / 86400.0;        // Rotation frequency [Hz] (1 revolution/day)
        e.Phi_3 = +1.0;                 // Chirality: prograde rotation
        e.Phi_4 = 0.01;                 // Low trajectory variance (stable orbit)
        e.Phi_5 = 0.0;                  // No imminent phase transition

        // Level 7: Energy
        e.eps_0 = -GM_earth * M_earth / (2.0 * AU);   // Gravitational binding to Sun [J]
        e.eps_1 = 0.5 * M_earth * 29783.0 * 29783.0;  // Orbital kinetic energy [J]
        e.eps_2 = 0.5 * 0.3307 * M_earth * R_earth * R_earth * omega_earth * omega_earth;  // Rotational [J]
        // ε₃: Field energy = magnetic field energy stored in magnetosphere
        // U_B = (2/3) μ₀ μ_earth² / R_earth³
        e.eps_3 = (2.0/3.0) * 4.0e-7 * std::numbers::pi * mu_earth * mu_earth
                / (R_earth * R_earth * R_earth);       // ~6.4e18 J
        e.eps_b = GM_earth * M_earth / R_earth;        // Gravitational self-binding [J]
        e.eps_4 = 1.74e17;              // Total intercepted solar flux [W]
        e.eps_5 = 0.0;                  // No mechanical transmission currently

        return e;
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  SOLAR WIND — 28D STATE DESCRIPTION
// ═══════════════════════════════════════════════════════════════════════

namespace solar_wind {
    // Physical constants at 1 AU
    inline constexpr double n_sw        = 5.0e6;         // [m⁻³] Number density (5/cm³)
    inline constexpr double v_sw        = 400e3;         // [m/s] Bulk velocity (400 km/s slow wind)
    inline constexpr double T_sw        = 1.0e5;         // [K] Proton temperature
    inline constexpr double B_imf       = 5.0e-9;        // [T] Interplanetary magnetic field at 1 AU
    inline constexpr double rho_sw      = n_sw * m_p;    // [kg/m³] Mass density

    // SDT interpretation: solar wind = Sun's ℓ=1 wake (radial pressure deficit
    // created by solar luminosity) carrying entrained proton/electron topologies
    // at velocity v_sw. The Parker spiral is the ℓ=2 component of the Sun's wake
    // twisted by solar rotation.

    // Dynamic pressure: P_dyn = ½ ρ v²
    inline constexpr double P_dyn = 0.5 * rho_sw * v_sw * v_sw;
    // ≈ 1.3 nPa

    /**
     * @brief Construct a solar wind parcel as State28D at 1 AU
     *
     * A solar wind "parcel" is a correlated volume of medium
     * carrying the Sun's wake signature.
     */
    inline State28D create_parcel() {
        State28D sw;

        // Level 1
        sw.xi_0 = 1.0;

        // Level 2: Radial outflow
        sw.xi_10 = AU;                   // At 1 AU
        sw.xi_11 = v_sw;                 // 400 km/s radially outward

        // Level 3: Cross-section of a flux tube
        // Flux tube area at 1 AU: A = AU² × Ω where Ω ~ steradian
        sw.xi_p0 = 1.0;
        sw.xi_p1 = 1.0e18;              // ~10¹⁸ m² cross-section per flux tube
        // Parker spiral angle at 1 AU: arctan(ωR/v_sw) ≈ 45°
        sw.xi_p2 = std::numbers::pi / 4.0;  // Parker spiral angle [rad]

        // Level 4: Parcel volume
        sw.xi_s0 = 1.0e24;              // ~10²⁴ m³ typical parcel
        sw.xi_s1 = v_sw;                // Expanding radially
        sw.xi_s2 = 0.0;                 // No rigid-body rotation (differential flow)
        sw.xi_s3 = 1.0;                 // Radial axis

        // Level 5: No toroidal topology (solar wind is NOT matter — it's medium flow)
        // But it CARRIES topology: protons (W=3) and electrons (W=1) entrained
        sw.T_1 = 0.0;                   // No central ring (not a bound structure)
        sw.T_2 = 0.0;
        sw.T_3 = 0.0;
        // T_4: The organized flow component = ℓ=2 wake carried from Sun
        sw.T_4 = B_imf * AU * AU;       // Magnetic flux content [T·m²]
        sw.T_5 = P_dyn / AU;            // Pressure gradient [Pa/m]

        // Level 6
        sw.Phi_0 = 2.0 * std::numbers::pi;  // Half-sphere (outward only)
        sw.Phi_1 = 0.0;                 // Roughly constant velocity at 1 AU
        sw.Phi_2 = 0.0;                 // No oscillation in steady state
        sw.Phi_3 = +1.0;               // IMF polarity (current sheet dependent)
        sw.Phi_4 = 0.5;                 // Moderate variability
        sw.Phi_5 = 0.0;

        // Level 7
        sw.eps_0 = 0.0;                 // No potential (free-streaming)
        sw.eps_1 = 0.5 * rho_sw * v_sw * v_sw;  // Kinetic energy density [J/m³]
        sw.eps_2 = 0.0;                 // No rotation energy
        sw.eps_3 = B_imf * B_imf / (2.0 * 4.0e-7 * std::numbers::pi);  // Magnetic energy density [J/m³]
        sw.eps_b = 0.0;                 // Not bound
        sw.eps_4 = rho_sw * v_sw * v_sw * v_sw / 2.0;  // Kinetic flux [W/m²]
        sw.eps_5 = 0.0;

        return sw;
    }

    /**
     * @brief Solar wind dynamic pressure at distance r from Sun
     * Falls as 1/r² (constant mass flux, constant velocity)
     */
    [[nodiscard]] inline auto P_dynamic(double r) noexcept -> double {
        return P_dyn * (AU * AU) / (r * r);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  MAGNETOSPHERE — THE INTERACTION BOUNDARY
//
//  SDT: The magnetosphere is where Earth's ℓ=2 wake pressure
//  equals the solar wind's ℓ=1 wake pressure.
//  This is a WAKE-WAKE COLLISION, not a "field" phenomenon.
// ═══════════════════════════════════════════════════════════════════════

namespace interaction {

    /**
     * @brief Magnetopause standoff distance
     *
     * SDT derivation:
     *   Earth's ℓ=2 wake pressure at distance r:
     *     P_mag(r) = B_eq²/(2μ₀) × (R_E/r)⁶   (dipole falls as r⁻³, pressure as r⁻⁶)
     *
     *   Solar wind dynamic pressure:
     *     P_sw = ½ ρ v²
     *
     *   Balance: P_mag(R_mp) = P_sw
     *     → R_mp = R_E × (B_eq² / (2μ₀ P_sw))^(1/6)
     *
     *   This is the SAME formula as standard MHD, but the interpretation
     *   differs: it's wake pressure balance, not "field pressure".
     *
     * @param P_sw_dynamic Solar wind dynamic pressure [Pa]
     * @return Magnetopause standoff distance [m]
     */
    [[nodiscard]] inline auto magnetopause_standoff(double P_sw_dynamic) noexcept -> double {
        constexpr double mu_0 = 4.0e-7 * std::numbers::pi;
        constexpr double B_eq = earth::B_surface;  // Equatorial field
        double P_mag_surface = B_eq * B_eq / (2.0 * mu_0);
        return earth::R_earth * std::pow(P_mag_surface / P_sw_dynamic, 1.0 / 6.0);
    }

    /**
     * @brief Bow shock standoff distance
     *
     * SDT: The bow shock is where the solar wind's translational
     * velocity exceeds the local wake propagation speed (Alfvén speed).
     * Rankine-Hugoniot jump conditions apply because the medium's
     * relay properties create the same discontinuity structure.
     *
     * R_bs ≈ 1.3 × R_mp (empirical Mach number ratio for M_A ≈ 8)
     */
    [[nodiscard]] inline auto bow_shock_standoff(double R_mp) noexcept -> double {
        return 1.3 * R_mp;
    }

    /**
     * @brief Alfvén Mach number of solar wind
     *
     * SDT: The Alfvén speed is the rate at which ℓ=2 wake perturbations
     * propagate through the medium. It is NOT a "magnetic wave" — it is
     * wake transmission via the same relay mechanism that carries light,
     * but modulated by the local organized flow (ℓ=2 content).
     *
     * v_A = B / √(μ₀ ρ)
     */
    [[nodiscard]] inline auto alfven_mach(double v_bulk, double B, double rho) noexcept -> double {
        constexpr double mu_0 = 4.0e-7 * std::numbers::pi;
        double v_A = B / std::sqrt(mu_0 * rho);
        return v_bulk / v_A;
    }

    /**
     * @brief Magnetic reconnection rate (SDT: wake-wake topology exchange)
     *
     * SDT interpretation: "Reconnection" is topological reconfiguration
     * of two overlapping ℓ=2 wakes. When the IMF's Bz is antiparallel
     * to Earth's dipole, the two wakes are anti-aligned. The boundary
     * between them becomes unstable: the organized flow patterns merge
     * and redistribute.
     *
     * Rate ≈ 0.1 × v_A × B (Sweet-Parker-Petschek, same math,
     * different ontology: no field lines, just wake overlap interference)
     *
     * @param B Local magnetic field strength [T]
     * @param rho Local mass density [kg/m³]
     * @return Reconnection electric field [V/m]
     */
    [[nodiscard]] inline auto reconnection_rate(double B, double rho) noexcept -> double {
        constexpr double mu_0 = 4.0e-7 * std::numbers::pi;
        double v_A = B / std::sqrt(mu_0 * rho);
        constexpr double reconnection_efficiency = 0.1;  // Petschek fast reconnection
        return reconnection_efficiency * v_A * B;
    }

    /**
     * @brief Energy transfer from solar wind to magnetosphere [W]
     *
     * SDT: The solar wind's wake (ℓ=1 + ℓ=2) impinges on Earth's wake (ℓ=2).
     * Energy transfers through wake overlap at the magnetopause.
     *
     * The Akasofu ε parameter is an empirical measure of this:
     *   ε = (4π/μ₀) × v_sw × B² × l₀² × sin⁴(θ/2)
     * where θ is the clock angle and l₀ ≈ 7 R_E.
     *
     * SDT derives this as: the overlap integral of the two wakes,
     * projected onto the anti-aligned component (sin⁴(θ/2) factor).
     */
    [[nodiscard]] inline auto akasofu_epsilon(
        double v_sw, double B_total, double theta_clock
    ) noexcept -> double {
        constexpr double mu_0 = 4.0e-7 * std::numbers::pi;
        constexpr double l_0 = 7.0 * earth::R_earth;  // Effective coupling length
        double sin_half = std::sin(theta_clock / 2.0);
        double sin4 = sin_half * sin_half * sin_half * sin_half;
        return (4.0 * std::numbers::pi / mu_0) * v_sw * B_total * B_total
             * l_0 * l_0 * sin4;
    }

    /**
     * @brief Complete magnetosphere description as State28D
     *
     * The magnetosphere itself is a State28D object — a persistent
     * wake structure maintained by Earth's core circulation.
     */
    inline State28D create_magnetosphere() {
        State28D mag;
        constexpr double mu_0 = 4.0e-7 * std::numbers::pi;

        // Magnetopause standoff for typical conditions
        double R_mp = magnetopause_standoff(solar_wind::P_dyn);
        double R_bs = bow_shock_standoff(R_mp);

        // Level 1
        mag.xi_0 = 1.0;  // The magnetosphere exists as a wake structure

        // Level 2: Centered on Earth, co-moving
        mag.xi_10 = 0.0;  // Earth-centered frame
        mag.xi_11 = 0.0;  // Co-moving with Earth

        // Level 3: Cross-section (asymmetric: compressed sunward, stretched tailward)
        mag.xi_p0 = 1.0;
        mag.xi_p1 = std::numbers::pi * R_mp * R_mp;  // Dayside cross-section [m²]
        mag.xi_p2 = 0.0;  // No in-plane rotation (locked to solar wind direction)

        // Level 4: Volume (magnetotail extends ~1000 R_E downstream)
        double R_tail = 1000.0 * earth::R_earth;
        mag.xi_s0 = (2.0/3.0) * std::numbers::pi * R_mp * R_mp * R_tail;  // Approx volume [m³]
        mag.xi_s1 = 0.0;  // Quasi-static structure
        mag.xi_s2 = earth::omega_earth;  // Co-rotates with Earth (inner magnetosphere)
        mag.xi_s3 = 1.0;  // Along Earth's magnetic axis

        // Level 5: Toroidal structure
        // The magnetosphere's topology IS the dipole — a toroidal flow
        // pattern inherited from the core dynamo
        mag.T_1 = R_mp;                 // Major radius = magnetopause standoff [m]
        mag.T_2 = earth::R_earth;       // Tube scale = Earth radius [m]
        mag.T_3 = 4.0 * std::numbers::pi * R_mp * R_mp;  // Effective surface [m²]
        mag.T_4 = earth::mu_earth;       // Magnetic moment [A·m²]
        // T_5: Pressure gradient across magnetopause
        mag.T_5 = solar_wind::P_dyn / R_mp;  // [Pa/m]

        // Level 6: Dynamics — magnetosphere breathes with solar wind variations
        mag.Phi_0 = 4.0 * std::numbers::pi;  // Full sphere (but asymmetric)
        mag.Phi_1 = 0.0;                // No net acceleration
        mag.Phi_2 = 1.0 / (6.0 * 3600.0);  // ~6 hour substorm cycle [Hz]
        mag.Phi_3 = +1.0;               // Dipole chirality
        mag.Phi_4 = 1.0;                // HIGH variance — magnetosphere is dynamic
        mag.Phi_5 = 0.0;                // No structural phase transition

        // Level 7: Energy budget
        // Potential: magnetic energy stored in the magnetosphere
        double B_avg = earth::B_surface * std::pow(earth::R_earth / R_mp, 3);
        mag.eps_0 = B_avg * B_avg / (2.0 * mu_0) * mag.xi_s0;  // Magnetic potential energy [J]
        mag.eps_1 = 0.0;                // No bulk kinetic (quasi-static)
        mag.eps_2 = 0.0;                // Rotation energy is Earth's, not magnetosphere's
        // ε₃: Field energy density at magnetopause
        mag.eps_3 = B_avg * B_avg / (2.0 * mu_0);  // [J/m³]
        mag.eps_b = mag.eps_0;           // Binding = total stored magnetic energy
        // ε₄: Energy flux from solar wind into magnetosphere
        // Typical Akasofu ε for southward IMF (θ = π)
        mag.eps_4 = akasofu_epsilon(solar_wind::v_sw, solar_wind::B_imf, std::numbers::pi);
        mag.eps_5 = 0.0;

        return mag;
    }

    /**
     * @brief Print magnetosphere diagnostics
     */
    inline void print_diagnostics() {
        constexpr double mu_0 = 4.0e-7 * std::numbers::pi;
        double R_mp = magnetopause_standoff(solar_wind::P_dyn);
        double R_bs = bow_shock_standoff(R_mp);
        double M_A = alfven_mach(solar_wind::v_sw, solar_wind::B_imf, solar_wind::rho_sw);
        double eps = akasofu_epsilon(solar_wind::v_sw, solar_wind::B_imf, std::numbers::pi);

        std::printf("╔══════════════════════════════════════════════════════════╗\n");
        std::printf("║  EARTH MAGNETOSPHERE — SDT Wake-Wake Interaction Model  ║\n");
        std::printf("╚══════════════════════════════════════════════════════════╝\n\n");

        std::printf("── Earth (ℓ=2 quadrupole wake source) ──\n");
        std::printf("  Core toroid:   R = %.3e m, shell = %.3e m\n", earth::R_core, earth::R_core - earth::R_inner_core);
        std::printf("  Dipole moment: μ = %.3e A·m²\n", earth::mu_earth);
        std::printf("  Surface B:     %.3e T\n", earth::B_surface);
        std::printf("  ϟ (c-boundary): %.4f m (%.1f mm)\n", earth::koppa_earth, earth::koppa_earth * 1e3);
        std::printf("  ω:             %.5e rad/s\n\n", earth::omega_earth);

        std::printf("── Solar Wind (ℓ=1 dipole wake, Sun) ──\n");
        std::printf("  n at 1 AU:     %.1e m⁻³\n", solar_wind::n_sw);
        std::printf("  v at 1 AU:     %.0f km/s\n", solar_wind::v_sw / 1e3);
        std::printf("  P_dynamic:     %.3e Pa (%.2f nPa)\n", solar_wind::P_dyn, solar_wind::P_dyn * 1e9);
        std::printf("  B_IMF at 1 AU: %.1e T (%.1f nT)\n", solar_wind::B_imf, solar_wind::B_imf * 1e9);
        std::printf("  Parker angle:  45° (at 1 AU)\n\n");

        std::printf("── Interaction (wake-wake pressure balance) ──\n");
        std::printf("  Magnetopause:  R_mp = %.2f R_E = %.3e m\n", R_mp / earth::R_earth, R_mp);
        std::printf("  Bow shock:     R_bs = %.2f R_E = %.3e m\n", R_bs / earth::R_earth, R_bs);
        std::printf("  Alfvén Mach:   M_A = %.1f\n", M_A);
        std::printf("  ε (Akasofu):   %.3e W (Bz south)\n\n", eps);

        // Comparison with measured values
        std::printf("── Verification ──\n");
        double R_mp_RE = R_mp / earth::R_earth;
        double R_mp_exp = 10.0;  // Typical observed magnetopause ~ 10 R_E
        std::printf("  R_mp: SDT = %.2f R_E, observed ≈ %.1f R_E (%.1f%%)\n",
                    R_mp_RE, R_mp_exp, std::abs(R_mp_RE - R_mp_exp) / R_mp_exp * 100);

        double R_bs_RE = R_bs / earth::R_earth;
        double R_bs_exp = 13.0;  // Typical observed bow shock ~ 13 R_E
        std::printf("  R_bs: SDT = %.2f R_E, observed ≈ %.1f R_E (%.1f%%)\n",
                    R_bs_RE, R_bs_exp, std::abs(R_bs_RE - R_bs_exp) / R_bs_exp * 100);

        double eps_exp = 1e12;  // Typical Akasofu ε ~ 10¹² W for Bz south
        std::printf("  ε:    SDT = %.2e W, observed ≈ %.0e W\n\n", eps, eps_exp);

        std::printf("── SDT Ontological Map ──\n");
        std::printf("  ┌──────────────────────┬────────────────────────────────┐\n");
        std::printf("  │ Standard Physics      │ SDT Interpretation             │\n");
        std::printf("  ├──────────────────────┼────────────────────────────────┤\n");
        std::printf("  │ Magnetic field B      │ ℓ=2 quadrupole wake component  │\n");
        std::printf("  │ Field lines           │ Wake flow streamlines          │\n");
        std::printf("  │ Magnetopause          │ Wake-wake pressure balance     │\n");
        std::printf("  │ Bow shock             │ Wake exceeds relay speed       │\n");
        std::printf("  │ Reconnection          │ Wake topology reconfiguration  │\n");
        std::printf("  │ Ring current          │ Entrained topology circulation │\n");
        std::printf("  │ Radiation belts       │ Topology storage in wake lobe  │\n");
        std::printf("  │ Auroral precipitation │ Wake channel collapse → light  │\n");
        std::printf("  │ Geomagnetic storm     │ Wake compression event         │\n");
        std::printf("  │ Parker spiral         │ Sun's ℓ=2 wake + rotation      │\n");
        std::printf("  └──────────────────────┴────────────────────────────────┘\n");
    }
}

} // namespace sdt::magnetosphere
