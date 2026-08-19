#pragma once

#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <numbers>

namespace sdt::occlusion {

using dynamics::Vec3;

inline constexpr std::size_t channel_count = 7;
inline constexpr double central_weight = 1.0 / 9.0;
inline constexpr double outer_weight = 4.0 / 27.0;
inline constexpr std::size_t radial_quadrature_count = 6;
inline constexpr std::size_t azimuth_quadrature_count = 16;

inline constexpr std::array<double, radial_quadrature_count> radial_nodes{
    -0.9324695142031521, -0.6612093864662645, -0.2386191860831969,
     0.2386191860831969,  0.6612093864662645,  0.9324695142031521
};
inline constexpr std::array<double, radial_quadrature_count> radial_weights{
    0.1713244923791704, 0.3607615730481386, 0.4679139345726910,
    0.4679139345726910, 0.3607615730481386, 0.1713244923791704
};

struct PairFrame {
    Vec3 normal{};
    Vec3 first{};
    Vec3 second{};
};

struct DiscNode {
    Vec3 position{};
    double area_weight_m2{};
};

[[nodiscard]] inline auto unit(Vec3 value) noexcept -> Vec3 {
    const double magnitude = dynamics::norm(value);
    return magnitude > 0.0 ? value / magnitude : Vec3{};
}

/// GOM43-E pair-facing frame. The least-aligned Cartesian reference prevents
/// a near-zero cross product and keeps the construction deterministic.
[[nodiscard]] inline auto pair_frame(Vec3 target_to_source) noexcept
    -> PairFrame {
    const Vec3 normal = unit(target_to_source);
    const std::array<Vec3, 3> axes{{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}
    }};
    std::size_t selected = 0;
    double alignment = std::abs(dynamics::dot(normal, axes[0]));
    for (std::size_t index = 1; index < axes.size(); ++index) {
        const double candidate =
            std::abs(dynamics::dot(normal, axes[index]));
        if (candidate < alignment) {
            selected = index;
            alignment = candidate;
        }
    }
    const Vec3 first = unit(dynamics::cross(normal, axes[selected]));
    return {normal, first, unit(dynamics::cross(normal, first))};
}

[[nodiscard]] constexpr auto channel_weight(std::size_t channel) noexcept
    -> double {
    return channel == 0 ? central_weight : outer_weight;
}

[[nodiscard]] inline auto channel_offset(
    std::size_t channel,
    double body_radius_m,
    const PairFrame& frame
) noexcept -> Vec3 {
    if (channel == 0) return {};
    const double phase =
        2.0 * std::numbers::pi * static_cast<double>(channel - 1) / 6.0;
    return (
        frame.first * std::cos(phase)
        + frame.second * std::sin(phase)
    ) * (2.0 * body_radius_m / 3.0);
}

template <class Visitor>
inline void for_each_disc_node(
    Vec3 centre,
    Vec3 first,
    Vec3 second,
    double radius_m,
    Visitor&& visitor
) {
    const double azimuth_weight =
        2.0 * std::numbers::pi
        / static_cast<double>(azimuth_quadrature_count);
    for (std::size_t radial = 0;
         radial < radial_quadrature_count;
         ++radial) {
        const double unit_radius = 0.5 * (radial_nodes[radial] + 1.0);
        const double radial_weight = 0.5 * radial_weights[radial];
        for (std::size_t azimuth = 0;
             azimuth < azimuth_quadrature_count;
             ++azimuth) {
            const double phase =
                2.0 * std::numbers::pi
                * (static_cast<double>(azimuth) + 0.5)
                / static_cast<double>(azimuth_quadrature_count);
            const Vec3 position = centre + (
                first * std::cos(phase) + second * std::sin(phase)
            ) * (radius_m * unit_radius);
            const double area_weight =
                radius_m * radius_m * unit_radius
                * radial_weight * azimuth_weight;
            visitor(DiscNode{position, area_weight});
        }
    }
}

/// Apparent solid angle of a finite face-on disc, evaluated by the fixed
/// GOM43-E area quadrature. `face_normal` points from the disc toward the
/// observer.
[[nodiscard]] inline auto disc_solid_angle(
    Vec3 observer,
    Vec3 centre,
    Vec3 face_normal,
    Vec3 first,
    Vec3 second,
    double radius_m
) noexcept -> double {
    double result = 0.0;
    for_each_disc_node(
        centre,
        first,
        second,
        radius_m,
        [&](const DiscNode& node) {
            const Vec3 to_observer = observer - node.position;
            const double distance_squared =
                dynamics::dot(to_observer, to_observer);
            if (!(distance_squared > 0.0)) return;
            const double cosine = std::max(
                0.0,
                dynamics::dot(face_normal, to_observer)
                    / std::sqrt(distance_squared)
            );
            result += cosine * node.area_weight_m2 / distance_squared;
        }
    );
    return result;
}

[[nodiscard]] inline auto axial_disc_solid_angle(
    double distance_m,
    double radius_m
) noexcept -> double {
    return 2.0 * std::numbers::pi * (
        1.0 - distance_m
            / std::sqrt(distance_m * distance_m + radius_m * radius_m)
    );
}

/// T10 movement-budget response. The supplied acceleration is split relative
/// to translation, with the parallel and perpendicular inertial factors
/// applied before integration.
[[nodiscard]] inline auto law_v_response(
    Vec3 acceleration,
    Vec3 velocity
) noexcept -> Vec3 {
    const double speed = dynamics::norm(velocity);
    if (!(speed > 0.0)) return acceleration;
    if (!(speed < laws::measured::c)) return {};
    const Vec3 direction = velocity / speed;
    const Vec3 parallel =
        direction * dynamics::dot(acceleration, direction);
    const Vec3 perpendicular = acceleration - parallel;
    const double gamma = laws::law_V::gamma(speed);
    return parallel / (gamma * gamma * gamma) + perpendicular / gamma;
}

} // namespace sdt::occlusion
