#pragma once

#include <sdt/laws.hpp>

#include <algorithm>
#include <cmath>
#include <numbers>

namespace sdt::materials {

struct BulkState {
    double radius_m{};
    double volume_m3{};
    double baryon_count{};
    double baryon_density_m3{};
    double koppa_total_m{};
    double koppa_density_m2{};
};

[[nodiscard]] constexpr auto sphere_volume(double radius_m) noexcept -> double {
    return 4.0 * std::numbers::pi * radius_m * radius_m * radius_m / 3.0;
}

[[nodiscard]] inline auto sphere_radius(double volume_m3) noexcept -> double {
    return std::cbrt(3.0 * volume_m3 / (4.0 * std::numbers::pi));
}

/// Material state from total baryon count and geometric radius.
///
/// T3/T6 aggregation: each baryon contributes the same koppa length. Volume
/// changes source density and near-boundary response, not the integrated
/// far-field monopole.
[[nodiscard]] constexpr auto state_from_baryons(
    double baryon_count,
    double radius_m
) noexcept -> BulkState {
    const double volume = sphere_volume(radius_m);
    const double koppa =
        baryon_count * sdt::laws::bridge::koppa_per_baryon;
    return {
        radius_m,
        volume,
        baryon_count,
        baryon_count / volume,
        koppa,
        koppa / volume
    };
}

/// Approximate material state from measured bulk resistance density [kg/m³].
/// The conversion rho*V/m_p neglects electron mass and binding defect.
[[nodiscard]] constexpr auto state_from_bulk_density(
    double resistance_density_kg_m3,
    double radius_m
) noexcept -> BulkState {
    const double volume = sphere_volume(radius_m);
    const double baryons =
        resistance_density_kg_m3 * volume / sdt::laws::measured::m_p;
    return state_from_baryons(baryons, radius_m);
}

/// Approximate radius/state for a specified total inertial resistance [kg].
[[nodiscard]] inline auto state_from_total_resistance(
    double resistance_kg,
    double resistance_density_kg_m3
) noexcept -> BulkState {
    const double volume = resistance_kg / resistance_density_kg_m3;
    const double radius = sphere_radius(volume);
    return state_from_baryons(
        resistance_kg / sdt::laws::measured::m_p,
        radius
    );
}

[[nodiscard]] constexpr auto far_acceleration(
    const BulkState& state,
    double distance_m
) noexcept -> double {
    const double c = sdt::laws::measured::c;
    return c * c * state.koppa_total_m / (distance_m * distance_m);
}

[[nodiscard]] constexpr auto surface_acceleration(
    const BulkState& state
) noexcept -> double {
    return far_acceleration(state, state.radius_m);
}

struct HelicalWakeSample {
    double phase_rad{};
    double axial_acceleration_ms2{};
    double azimuthal_acceleration_ms2{};
    double magnitude_ms2{};
};

/// Normalized Law-VI rotational wake kernel.
///
/// The r^-3 exponent is canonical. The unit surface normalization is a
/// visualization/control convention; it is not an absolute magnetic-amplitude
/// prediction.
[[nodiscard]] inline auto normalised_helical_wake(
    const BulkState& source,
    double observation_radius_m,
    double azimuth_rad,
    double axial_position_m,
    double time_s,
    double pitch_m,
    double angular_rate_rad_s,
    int winding,
    double alignment_fraction
) noexcept -> HelicalWakeSample {
    if (
        observation_radius_m <= 0.0
        || pitch_m <= 0.0
        || winding == 0
    ) {
        return {};
    }

    const double alignment =
        std::clamp(alignment_fraction, -1.0, 1.0);
    const double phase =
        static_cast<double>(winding) * azimuth_rad
        + 2.0 * std::numbers::pi * axial_position_m / pitch_m
        - angular_rate_rad_s * time_s;
    const double c = sdt::laws::measured::c;
    const double magnitude =
        c * c * source.koppa_total_m * source.radius_m
        / (
            observation_radius_m
            * observation_radius_m
            * observation_radius_m
        ) * std::abs(alignment);

    return {
        phase,
        magnitude * std::cos(phase) * (alignment < 0.0 ? -1.0 : 1.0),
        magnitude * std::sin(phase) * (alignment < 0.0 ? -1.0 : 1.0),
        magnitude
    };
}

/// Conventional-equivalent magnetic flux through a circular current loop:
/// Phi_B = pi k_e q omega R / c^2.
///
/// This derives the reported field unit from moving charge; magnetic field is
/// not introduced as a primitive.
[[nodiscard]] constexpr auto magnetic_flux_loop(
    double circulating_charge_C,
    double angular_rate_rad_s,
    double loop_radius_m
) noexcept -> double {
    const double c = sdt::laws::measured::c;
    return std::numbers::pi
        * sdt::laws::measured::k_e
        * circulating_charge_C
        * angular_rate_rad_s
        * loop_radius_m
        / (c * c);
}

/// Declared comparison control: `loop_units_per_atom` electron-equivalent
/// circulations per atom at one common angular rate. This is not a prediction
/// of a material's electronic alignment.
[[nodiscard]] constexpr auto atom_loop_flux_control(
    const BulkState& state,
    double baryons_per_atom,
    double loop_units_per_atom,
    double alignment_fraction,
    double angular_rate_rad_s
) noexcept -> double {
    if (baryons_per_atom <= 0.0) return 0.0;
    const double alignment =
        std::clamp(alignment_fraction, -1.0, 1.0);
    const double atom_count = state.baryon_count / baryons_per_atom;
    const double circulating_charge =
        atom_count
        * loop_units_per_atom
        * alignment
        * sdt::laws::measured::e_charge;
    return magnetic_flux_loop(
        circulating_charge,
        angular_rate_rad_s,
        state.radius_m
    );
}

} // namespace sdt::materials
