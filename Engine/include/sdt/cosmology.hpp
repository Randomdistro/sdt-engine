#pragma once

/**
 * @file cosmology.hpp
 * @brief SDT Cosmology Module — Pressure Regimes, Release Cascade, CnuB
 *
 * Implements the SDT cosmological framework:
 *   - Pre-Clearing pressure regime characterisation
 *   - Release Cascade: the Clearing as local mechanical arrival
 *   - Pressure-gradient redshift (replaces metric expansion)
 *   - BAO scale as lattice equilibrium length
 *   - Stellar pressure domains (generalised Oort cloud centreline)
 *   - Hubble tension dissolution via non-uniform pressure gradient
 *
 * Core principle: there is no metric expansion. Redshift arises from
 * photons (lattice deformations) traversing the pressure gradient from
 * the Clearing (3000 K) to the present (2.73 K). Neutrinos, being open
 * windings that don't participate in the relay, are NOT subject to this
 * gradient — making them the true geometric distance ruler.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date March 2026
 */

#include <sdt/laws.hpp>
#include <cmath>
#include <numbers>

namespace sdt::cosmology {

using namespace sdt::laws;
using namespace sdt::laws::measured;

// =====================================================================
//  PRE-CLEARING PRESSURE REGIME
//
//  Before the Clearing (z = 1100, T = 3000 K), the lattice was coupled
//  and non-transmissive. Pressure was ~1.47e12 x present value.
//  Stable topological configurations were different ("dinosaur particles").
// =====================================================================

namespace pre_clearing {
    /// Energy density at recombination [J/m^3]
    inline constexpr double u_held = law_I::u_held;  // 6.13e-2 J/m^3

    /// Pressure at recombination [Pa]
    inline constexpr double P_held = u_held / 3.0;   // 2.04e-2 Pa

    /// Pressure ratio: recombination / present
    inline constexpr double pressure_ratio = u_held / law_I::u_CMB;  // ~1.47e12

    /// Relay content per spation at recombination [J]
    inline constexpr double epsilon_held = u_held * l_P3;  // ~2.59e-106 J

    /// Convergence burden at recombination [J]
    inline constexpr double Phi_rec = law_I::N * epsilon_held;

    /// Convergence pressure at recomb epoch [Pa]
    inline constexpr double P_conv_rec = Phi_rec / l_P3;  // ~3.61e60 Pa

    /// Power per spation at recombination [W]
    /// This is ORDER UNITY in SI watts — a deep structural result
    inline constexpr double W_per_spation = Phi_rec / t_P;  // ~0.283 W

    /// BAO sound speed in coupled lattice [m/s]
    inline constexpr double c_s = c / std::numbers::sqrt3;  // c/sqrt(3) ~ 1.73e8

    /// Coupled epoch duration required for BAO scale [s]
    /// 147 Mpc = c_s * t_coupled -> t_coupled ~ 830 Myr
    inline constexpr double Mpc = 3.085'677'581e22;
    inline constexpr double BAO_scale = 147.0 * Mpc;        // [m]
    inline constexpr double t_coupled = BAO_scale / c_s;     // [s] ~ 2.62e16

    /// BAO scale in Planck lengths
    inline constexpr double BAO_in_lP = BAO_scale / l_P;    // ~2.81e59
}

// =====================================================================
//  SDT STRAIN RATE (replaces Hubble parameter)
//
//  H_0 is not an expansion rate. It is the present-epoch strain rate
//  of the pressure gradient: sigma_0 = H_0/c [m^-1]
//  This is the rate of wavelength stretching per unit distance.
// =====================================================================

namespace strain {
    /// Hubble parameter [s^-1] — measured value, SDT reinterpretation
    inline constexpr double H0_CMB   = 67.4e3 / pre_clearing::Mpc;    // Planck
    inline constexpr double H0_local = 73.04e3 / pre_clearing::Mpc;   // SH0ES

    /// SDT strain rate [m^-1]
    inline constexpr double sigma_CMB   = H0_CMB / c;    // ~7.29e-27
    inline constexpr double sigma_local = H0_local / c;  // ~7.90e-27

    /// Strain rate tension (SDT: expected, not anomalous)
    /// Local pressure gradient is steeper near massive structures
    inline constexpr double tension_pct = (sigma_local - sigma_CMB) / sigma_CMB * 100.0;
    // ~8.4%
}

// =====================================================================
//  SDT AGE AND DISTANCE
//
//  R_CMB = ln(1 + z_rec) / sigma_0 ~ 9.53e26 m
//  Without expansion, comoving distance = physical distance
//  Age ~ 48 Gyr (standard comoving distance / c)
// =====================================================================

namespace age {
    /// Light-travel time to Clearing [s]
    inline constexpr double t_light_travel = law_I::R_CMB / c;
    // ~3.18e18 s ~ 100.7 Gyr

    /// SDT age via standard comoving distance reinterpreted [Gyr]
    /// In SDT without expansion, comoving distance IS the physical distance
    /// Standard comoving distance to CMB ~ 46.3 Gly ~ 48 Gyr light-travel
    inline constexpr double age_SDT_Gyr = 48.0;

    /// Age in seconds
    inline constexpr double age_SDT_s = age_SDT_Gyr * 1e9 * 365.25 * 24.0 * 3600.0;
}

// =====================================================================
//  STELLAR PRESSURE DOMAINS
//
//  Every star has a dominion radius: r_domain = sqrt(L / (4 pi F_CMB))
//  Beyond this, CMB convergence exceeds stellar convergence.
//  For the Sun: r_domain ~ 20,857 AU (Oort cloud centreline)
// =====================================================================

/// Pressure domain radius for arbitrary luminosity [m]
[[nodiscard]] inline auto pressure_domain(double luminosity_W) noexcept -> double {
    double F_CMB = c * law_I::u_CMB / 4.0;
    return std::sqrt(luminosity_W / (4.0 * std::numbers::pi * F_CMB));
}

/// Solar pressure domain [m] — verified ~20,857 AU
inline constexpr double r_domain_Sun = law_II::r_domain_Sun;  // 3.12e15 m

/// Solar domain in AU
inline constexpr double r_domain_Sun_AU = r_domain_Sun / AU;  // ~20,857

// =====================================================================
//  BAO AS LATTICE EQUILIBRIUM LENGTH
//
//  The BAO scale (147 Mpc) is not merely a fossil wavelength.
//  It is the fundamental equilibrium length of the lattice under its
//  own compression — the distance at which any major discharge
//  event's outward impulse is absorbed by the lattice elasticity.
//
//  The luminosity that would create a 147 Mpc equilibrium domain:
//  L = 4 pi F_CMB * BAO^2 ~ 2.1e18 L_Sun
//  (total luminosity of a supergalaxy cluster)
// =====================================================================

namespace bao {
    inline constexpr double scale = pre_clearing::BAO_scale;

    /// Central luminosity for BAO equilibrium [W]
    inline constexpr double L_central = 4.0 * std::numbers::pi
        * (c * law_I::u_CMB / 4.0) * scale * scale;
    // ~8.1e44 W ~ 2.1e18 L_Sun

    /// Scale-invariance: both solar domain and BAO follow
    /// r_eq = sqrt(L / (4 pi F_CMB))
    /// Same equation, different scales
}

// =====================================================================
//  VISUAL HISTORY OF THE SKY
//
//  T(z) = T_CMB * (1 + z)
//  At z ~ 1100: T = 3000 K, Wien peak ~ 966 nm (near-IR, orange-red)
//  At z ~ 107:  T = 293 K, space at room temperature
//  At z ~ 100:  T = 275 K, just above freezing
//  At z ~ 10:   T = 30 K, cold far-IR
//  At z = 0:    T = 2.73 K, microwave
//
//  UV-tail photons from the Clearing traversed the full visible
//  spectrum on their way to becoming microwaves:
//  UV -> violet -> blue -> green -> yellow -> orange -> red -> IR -> uW
// =====================================================================

/// Temperature at given redshift [K]
[[nodiscard]] constexpr auto T_at_z(double z) noexcept -> double {
    return T_CMB * (1.0 + z);
}

/// Wien peak wavelength [m] at given temperature [K]
[[nodiscard]] constexpr auto wien_peak(double T_K) noexcept -> double {
    return 2.898e-3 / T_K;
}

/// Redshift at which space reaches a given temperature
[[nodiscard]] constexpr auto z_at_T(double T_K) noexcept -> double {
    return T_K / T_CMB - 1.0;
}

// Notable epochs
inline constexpr double z_room_temp = z_at_T(293.15);   // ~106.5
inline constexpr double z_freezing  = z_at_T(273.15);   // ~99.2
inline constexpr double z_boiling   = z_at_T(373.15);   // ~135.9

} // namespace sdt::cosmology
