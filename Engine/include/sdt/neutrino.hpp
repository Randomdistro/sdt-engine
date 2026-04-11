#pragma once

/**
 * @file neutrino.hpp
 * @brief SDT Neutrino Module — Open-Winding Topology & Mass Gap
 *
 * The neutrino is the minimum-occupation perturbation in the spation lattice:
 *   - Winding number W -> 0+ (open winding, never closes)
 *   - No toroidal flow -> no charge (l=1) -> no magnetic moment (l=2)
 *   - Propagates WITH the relay, not AGAINST it -> near-zero interaction
 *   - Mass gap: the minimum V_disp that can propagate as a distinct entity
 *
 * Flavour oscillation = helical pitch precession between three stable
 * pitch angles of the open winding. The open winding CAN precess precisely
 * BECAUSE it is not topologically locked (unlike W=1 electron or W=3 proton).
 *
 * Wake radius at W=0: R_wake = hbar/(m_nu c) ~ 10 um — macroscopic but
 * non-occluding. The wake-to-body ratio (R_wake/R_excl ~ 10^18) is the
 * largest of any known particle, explaining the negligible cross-section.
 *
 * @author SDT Canonical Engine — James Tyndall, Melbourne, Australia
 * @date March 2026
 */

#include <sdt/laws.hpp>
#include <cmath>

namespace sdt::neutrino {

using namespace sdt::laws::measured;

// =====================================================================
//  MEASURED NEUTRINO PARAMETERS
// =====================================================================

namespace measured {
    // Mass eigenstates — normal ordering best estimates
    inline constexpr double m_nu1_eV  = 0.02;
    inline constexpr double m_nu2_eV  = 0.029;
    inline constexpr double m_nu3_eV  = 0.06;

    inline constexpr double m_nu1_kg  = m_nu1_eV * eV_to_J / (c * c);
    inline constexpr double m_nu2_kg  = m_nu2_eV * eV_to_J / (c * c);
    inline constexpr double m_nu3_kg  = m_nu3_eV * eV_to_J / (c * c);

    // Mass-squared splittings
    inline constexpr double Dm21_sq   = 7.53e-5;    // [eV^2] solar
    inline constexpr double Dm32_sq   = 2.453e-3;   // [eV^2] atmospheric

    // Mixing angles (PDG 2023)
    inline constexpr double sin2_theta12 = 0.307;
    inline constexpr double sin2_theta23 = 0.546;
    inline constexpr double sin2_theta13 = 0.02220;

    // CnuB temperature (standard model)
    inline constexpr double T_CnuB_std = 1.9454;    // [K]

    // Cosmic neutrino number density (standard model)
    inline constexpr double n_nu_std  = 336.0e6;    // [/m^3]
}

// =====================================================================
//  WINDING TOPOLOGY — W = 0 (OPEN WINDING)
// =====================================================================

inline constexpr int W_neutrino = 0;

/// Wake radius for open winding: R_wake = hbar/(mc)
[[nodiscard]] inline auto wake_radius(double mass_kg) noexcept -> double {
    return hbar / (mass_kg * c);
}

// Pre-computed wake radii [m]
inline constexpr double R_wake_nu1 = hbar / (measured::m_nu1_kg * c);  // 9.87 um
inline constexpr double R_wake_nu2 = hbar / (measured::m_nu2_kg * c);  // 6.80 um
inline constexpr double R_wake_nu3 = hbar / (measured::m_nu3_kg * c);  // 3.29 um

// =====================================================================
//  DISPLACEMENT VOLUMES — from Law IV
// =====================================================================

inline constexpr double V_disp_nu1 = 3.0 * measured::m_nu1_kg * l_P3 * c * c
                                   / sdt::laws::law_I::Phi;  // 3.91e-69 m^3

inline constexpr double V_disp_nu2 = 3.0 * measured::m_nu2_kg * l_P3 * c * c
                                   / sdt::laws::law_I::Phi;  // 5.66e-69 m^3

inline constexpr double V_disp_nu3 = 3.0 * measured::m_nu3_kg * l_P3 * c * c
                                   / sdt::laws::law_I::Phi;  // 1.17e-68 m^3

// Exclusion radii (spherical equivalent) [m]
inline constexpr double R_excl_nu1 = 9.770e-24;  // 6.04e11 l_P
inline constexpr double R_excl_nu2 = 1.106e-23;  // 6.84e11 l_P
inline constexpr double R_excl_nu3 = 1.409e-23;  // 8.72e11 l_P

// =====================================================================
//  MASS GAP — THE MINIMUM PERSISTENT DISPLACEMENT
//
//  m_nu1 ~ 0.02 eV is the SDT mass gap: the smallest V_disp that
//  propagates indefinitely. Below this, perturbations thermalise.
//  N_min = V_gap / l_P^3 ~ 9.25e35 spations
// =====================================================================

namespace mass_gap {
    inline constexpr double m_gap_eV  = measured::m_nu1_eV;
    inline constexpr double m_gap_kg  = measured::m_nu1_kg;
    inline constexpr double V_gap     = V_disp_nu1;
    inline constexpr double E_gap_J   = m_gap_kg * c * c;
    inline constexpr double N_min     = V_gap / l_P3;  // ~9.25e35
}

// =====================================================================
//  MOVEMENT BUDGET
// =====================================================================

[[nodiscard]] inline auto v_circ(double v_trans) noexcept -> double {
    return std::sqrt(c * c - v_trans * v_trans);
}

[[nodiscard]] inline auto v_from_energy(double E_eV, double m_eV) noexcept -> double {
    double gamma = (E_eV > m_eV) ? E_eV / m_eV : 1.0 + E_eV / m_eV;
    return c * std::sqrt(1.0 - 1.0 / (gamma * gamma));
}

[[nodiscard]] inline auto gamma_from_energy(double E_eV, double m_eV) noexcept -> double {
    return (E_eV > m_eV) ? E_eV / m_eV : 1.0 + E_eV / m_eV;
}

// =====================================================================
//  OSCILLATION — PITCH PRECESSION MODEL
//
//  Three mass eigenstates = three stable pitch angles of the open
//  winding. The winding precesses because it is NOT topologically locked.
//  L_osc = 2.48 * E[MeV] / Dm^2[eV^2]  [m]
//  Pitch ratio: Dm32/Dm21 ~ 32.6 -> nu3 is ~6x more tilted
// =====================================================================

namespace oscillation {
    [[nodiscard]] inline auto L_osc(double E_MeV, double Dm2_eV2) noexcept -> double {
        return 2.48 * E_MeV / Dm2_eV2;
    }

    [[nodiscard]] inline auto L_21(double E_MeV) noexcept -> double {
        return L_osc(E_MeV, measured::Dm21_sq);
    }

    [[nodiscard]] inline auto L_32(double E_MeV) noexcept -> double {
        return L_osc(E_MeV, measured::Dm32_sq);
    }

    inline constexpr double pitch_ratio = measured::Dm32_sq / measured::Dm21_sq;
}

// =====================================================================
//  CnuB — COSMIC NEUTRINO BACKGROUND (SDT PREDICTIONS)
//
//  SDT: neutrinos are open windings — they do NOT participate in the
//  lattice relay. They are NOT subject to pressure-gradient redshift.
//  Neutrino-measured distances != photon-measured distances.
//  The discrepancy = lattice pressure-gradient contribution to z.
//
//  Key prediction: H0(neutrino) < H0(CMB) < H0(local)
// =====================================================================

namespace cnub {
    inline constexpr double T_std = measured::T_CnuB_std;
    inline constexpr double n_std = measured::n_nu_std;
    inline constexpr double n_baryon = 0.251;  // [/m^3]
    inline constexpr double nu_per_baryon = n_std / n_baryon;  // ~1.34e9
}

// =====================================================================
//  SOLAR NEUTRINO RATES
// =====================================================================

namespace solar {
    inline constexpr double E_per_chain_MeV = 26.7;
    inline constexpr double nu_per_chain    = 2.0;
    inline constexpr double L_Sun = sdt::laws::law_II::L_Sun;
    inline constexpr double nu_rate = L_Sun / (E_per_chain_MeV * 1e6 * eV_to_J) * nu_per_chain;
    // ~1.79e38 nu/s

    inline constexpr double flux_1AU = nu_rate / (4.0 * 3.14159265358979323846 * AU * AU);
    // ~6.36e14 nu/(m^2.s) = 6.36e10 nu/(cm^2.s) -- matches SNO/Super-K
}

// =====================================================================
//  WAKE STRUCTURE COMPARISON
//
//  Particle        W    R_excl         R_wake         R_wake/R_excl
//  Neutrino nu1    0    9.77e-24 m     9.87e-06 m     1.01e+18
//  Electron        1    2.88e-21 m     2.82e-15 m     9.79e+05
//  Proton          3    3.52e-20 m     8.41e-16 m     2.39e+04
//
//  The neutrino's wake/body ratio is 10^12 x the electron's.
//  Its influence is maximally diluted — this IS the weak interaction,
//  explained geometrically, not via coupling constants.
// =====================================================================

} // namespace sdt::neutrino
