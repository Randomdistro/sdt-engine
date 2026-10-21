#pragma once
// SDT: explicit pitch/diameter/radius geometry (20 October 2026).
// GEOMETRY ONLY. Identifying CODATA Planck length with a physical spation
// diameter is a hypothesis, not a measurement of a spation.
//
// Pitch is centre-to-centre neighbour separation in the specified contact
// model. A half-pitch surface radius does NOT by itself change the relay
// step, shell count, Law-I normalization or baryon-koppa coefficient.
// Such changes require a separately derived physical transfer operator.
#include <numbers>

namespace sdt::geometry::spation {

[[nodiscard]] constexpr double radius_from_diameter(double diameter_m) noexcept {
    return diameter_m / 2.0;
}
[[nodiscard]] constexpr double diameter_from_radius(double radius_m) noexcept {
    return 2.0 * radius_m;
}
[[nodiscard]] constexpr double projected_area_from_radius(double radius_m) noexcept {
    return std::numbers::pi * radius_m * radius_m;
}
[[nodiscard]] constexpr double surface_area_from_radius(double radius_m) noexcept {
    return 4.0 * std::numbers::pi * radius_m * radius_m;
}
[[nodiscard]] constexpr double sphere_volume_from_radius(double radius_m) noexcept {
    return (4.0 * std::numbers::pi / 3.0) * radius_m * radius_m * radius_m;
}
[[nodiscard]] constexpr double pitch_cube_volume(double pitch_m) noexcept {
    return pitch_m * pitch_m * pitch_m;
}
[[nodiscard]] constexpr double pitch_square_area(double pitch_m) noexcept {
    return pitch_m * pitch_m;
}
[[nodiscard]] constexpr double sphere_volume_from_diameter(double diameter_m) noexcept {
    return sphere_volume_from_radius(radius_from_diameter(diameter_m));
}
[[nodiscard]] constexpr double geometric_area_ratio_to_pitch_square() noexcept {
    return std::numbers::pi / 4.0;
}
[[nodiscard]] constexpr double geometric_volume_ratio_to_pitch_cube() noexcept {
    return std::numbers::pi / 6.0;
}

// Explicit hypothesis wrapper: the legacy l_P reference is a *diameter*
// only under the proposed spation geometry. No substitution into Law I/IV
// or bridge::koppa_per_baryon is authorized by this geometric identity.
struct DiameterHypothesis {
    double diameter_m;
    [[nodiscard]] constexpr double radius_m() const noexcept {
        return radius_from_diameter(diameter_m);
    }
    [[nodiscard]] constexpr double contact_pitch_m() const noexcept {
        return diameter_m;
    }
    [[nodiscard]] constexpr double physical_volume_m3() const noexcept {
        return sphere_volume_from_diameter(diameter_m);
    }
    [[nodiscard]] constexpr double projected_area_m2() const noexcept {
        return projected_area_from_radius(radius_m());
    }
};
}  // namespace sdt::geometry::spation
