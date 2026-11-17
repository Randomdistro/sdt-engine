#pragma once
// SDT: native Om/depth -> quantized closed circulation -> Bohr correspondence.
// Classification: CONDITIONAL GEOMETRIC DERIVATION, NOT INDEPENDENT alpha,
// hbar, microscopic circulation-quantum or source-Om determination.
// No G, GM, Coulomb potential, CODATA Bohr radius or alpha is imported here.
// Caller declares a source c-boundary length, specific action, relay speed,
// and (for spectral energy) reduced mass / action quantum explicitly.
#include <cmath>

namespace sdt::geometry::om_atomic {

// Notation: om (ѻ) = positive source c-boundary LENGTH [m];
// Om(r) (Ѻ_r) = c/v(r) dimensionless; z = om/r.
// Om is not a physical spation radius and must not be confused with r_s.
[[nodiscard]] constexpr double depth(double om_m, double r_m) noexcept {
    return om_m / r_m;
}
[[nodiscard]] inline double velocity_ratio(double om_m, double r_m) noexcept {
    return std::sqrt(r_m / om_m);
}
[[nodiscard]] inline double bound_speed(double om_m, double r_m, double c_ms) noexcept {
    return c_ms * std::sqrt(depth(om_m, r_m));
}
[[nodiscard]] constexpr double source_length_from_speed(
    double v_ms, double r_m, double c_ms
) noexcept {
    return (v_ms * v_ms * r_m) / (c_ms * c_ms);
}
[[nodiscard]] constexpr double relative_closure(double z) noexcept {
    return 1.0 - z;
}
[[nodiscard]] constexpr double closure_length(
    double uncompressed_pitch_m, double z
) noexcept {
    return uncompressed_pitch_m * relative_closure(z);
}
// GOM22: far-frame relay profile, two closure factors.
// This is a PROPAGATION relation, not an orbital-velocity substitution.
[[nodiscard]] constexpr double far_relay_speed(double c_inf_ms, double z) noexcept {
    return c_inf_ms * relative_closure(z) * relative_closure(z);
}
// Single-valued circulation of mode n:
//  2 pi r_n v_n = n h / mu (assumption, not a derived vortex eigenvalue).
// Taking the bound-speed law v = c sqrt(om/r), the closed radius follows.
[[nodiscard]] constexpr double rung_radius(
    double om_m, double specific_action_m2s, double c_ms, int n
) noexcept {
    return (static_cast<double>(n) * n * specific_action_m2s * specific_action_m2s)
           / (c_ms * c_ms * om_m);
}
[[nodiscard]] constexpr double rung_depth(
    double om_m, double specific_action_m2s, double c_ms, int n
) noexcept {
    return om_m / rung_radius(om_m, specific_action_m2s, c_ms, n);
}
// Independent input omega = mu*c*om/hbar is NOT the fine structure constant
// until a comparison with atomic observations establishes correspondence.
[[nodiscard]] constexpr double beta_from_source(
    double om_m, double specific_action_m2s, double c_ms
) noexcept {
    return c_ms * om_m / specific_action_m2s;
}
// Conditional conservative inverse-square interaction, energy zero at infinity.
// Energy is *equivalent* to Bohr Coulomb-orbit energy under matching coupling.
[[nodiscard]] constexpr double bound_energy_joule(
    double mu_kg, double c_ms, double z
) noexcept {
    return -0.5 * mu_kg * c_ms * c_ms * z;
}
[[nodiscard]] constexpr double transition_energy_joule(
    double mu_kg, double c_ms, double z_low_n, double z_high_n
) noexcept {
    return 0.5 * mu_kg * c_ms * c_ms * (z_low_n - z_high_n);
}
[[nodiscard]] constexpr double transition_wavenumber_m_inv(
    double om_m, double specific_action_m2s, double c_ms, double mu_kg,
    double h_js, int n_low, int n_high
) noexcept {
    return transition_energy_joule(
        mu_kg, c_ms,
        rung_depth(om_m, specific_action_m2s, c_ms, n_low),
        rung_depth(om_m, specific_action_m2s, c_ms, n_high)
    ) / (h_js * c_ms);
}
}  // namespace sdt::geometry::om_atomic
