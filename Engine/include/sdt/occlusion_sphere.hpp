#pragma once
// sdt/occlusion_sphere.hpp -- the seven-circle occlusion geometry stated on Helix geometry (contract 4.0.0).
//
// Contract 3.0.0 (sdt/occlusion.hpp) builds a pair-facing frame from the least-aligned global axis and places channel centres and
// disc-quadrature nodes with components. Here every one of those is a PLACE reached by a step: from a centre, along the direction
// at a right angle to the pair axis with a given bearing, by a given distance. The bearing is measured from "toward the pole"
// (Helix's convention), so the ring of six outer channels and the 16 azimuth nodes start from the axis' own meridian instead of a
// global axis; for an unshielded pair the integrand is symmetric about the axis and the two agree to rounding.
//
// Nothing here forms a component. See SPHERICAL_CONTRACT_4_0_0.md section 5 for the correspondence of each operation.
//
// Author: James Christopher Tyndall, Melbourne.

#include <sdt/laws.hpp>
#include <sdt/sphere_frame.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <numbers>
#include <optional>

namespace sdt::occlusion_sphere {

using sphere::Direction;
using sphere::Locus;
using sphere::Vector;

// Quadrature of contract 3.0.0 (the same values as sdt/occlusion.hpp; the equivalence test asserts it).
inline constexpr std::size_t channel_count = 7;
inline constexpr double central_weight = 1.0 / 9.0;
inline constexpr double outer_weight = 4.0 / 27.0;
inline constexpr std::size_t radial_quadrature_count = 6;
inline constexpr std::size_t azimuth_quadrature_count = 16;
inline constexpr std::array<double, radial_quadrature_count> radial_nodes{
    -0.9324695142031521, -0.6612093864662645, -0.2386191860831969,
     0.2386191860831969,  0.6612093864662645,  0.9324695142031521};
inline constexpr std::array<double, radial_quadrature_count> radial_weights{
    0.1713244923791704, 0.3607615730481386, 0.4679139345726910,
    0.4679139345726910, 0.3607615730481386, 0.1713244923791704};

[[nodiscard]] constexpr double channel_weight(std::size_t channel) noexcept {
    return channel == 0 ? central_weight : outer_weight;
}

// The place `distance` from `centre`, at a right angle to `axis`, along the heading `phase` (a bearing off the axis' own pole).
[[nodiscard]] inline Locus ring_place(const Locus& centre, const Direction& axis, double distance, double phase) {
    if (!(distance > 0.0)) return centre;
    return sphere::step_locus(centre, sphere::offset_direction(axis, sphere::kHalfPi, phase), distance);
}

// Channel 0 sits at the body's centre; channels 1..6 on a ring of radius 2R/3, 60 degrees apart.
[[nodiscard]] inline double channel_phase(std::size_t channel) noexcept {
    return 2.0 * std::numbers::pi * static_cast<double>(channel - 1) / 6.0;
}
[[nodiscard]] inline double channel_ring_radius(std::size_t channel, double body_radius_m) noexcept {
    return channel == 0 ? 0.0 : 2.0 * body_radius_m / 3.0;
}
[[nodiscard]] inline Locus channel_centre(const Locus& body, std::size_t channel, double body_radius_m, const Direction& axis) {
    if (channel == 0) return body;
    return ring_place(body, axis, channel_ring_radius(channel, body_radius_m), channel_phase(channel));
}

struct DiscNode {
    Locus place;
    double area_weight_m2;
};

template <class Visitor>
inline void for_each_disc_node(const Locus& centre, const Direction& axis, double radius_m, Visitor&& visitor) {
    const double azimuth_weight = 2.0 * std::numbers::pi / static_cast<double>(azimuth_quadrature_count);
    for (std::size_t radial = 0; radial < radial_quadrature_count; ++radial) {
        const double unit_radius = 0.5 * (radial_nodes[radial] + 1.0);
        const double radial_weight = 0.5 * radial_weights[radial];
        for (std::size_t azimuth = 0; azimuth < azimuth_quadrature_count; ++azimuth) {
            const double phase = 2.0 * std::numbers::pi * (static_cast<double>(azimuth) + 0.5) / static_cast<double>(azimuth_quadrature_count);
            const Locus place = ring_place(centre, axis, radius_m * unit_radius, phase);
            const double area_weight = radius_m * radius_m * unit_radius * radial_weight * azimuth_weight;
            visitor(DiscNode{place, area_weight});
        }
    }
}

// The cosine of the angle between two directions (a cosine of an angle between directions, never against a fixed axis).
[[nodiscard]] inline double cosine_between(const Direction& a, const Direction& b) noexcept {
    return std::cos(sphere::separation(a, b));
}

// Does the ray from `observer` to `node` pass through one of `blocker`'s seven channel discs (each of radius R/3), judged at the foot
// of the perpendicular from the blocker's centre on the ray? 3.0.0: fraction = dot(centre - observer, ray)/|ray|^2 must lie in (0, 1);
// the foot is observer + ray fraction; a channel blocks if |foot - channel centre| <= R/3.
// Here: the triangle (observer, node, blocker centre). L: observer -> node; d: observer -> blocker centre; psi: angle between them.
// The foot lies d cos(psi) along the ray and d sin(psi) across it. The channel ring (radius rho, phase phi_k, in the plane at a right
// angle to the observer -> blocker axis, phases measured from that axis' own pole) is seen from the foot at the squared distance
//     (d sin psi)^2 + rho^2 - 2 d sin psi cos psi rho cos(phi_k - chi),    chi = bearing of the ray direction off the axis.
// `ray` (observer -> node) and `centre` (observer -> blocker centre) are the two relative loci of the triangle; a caller that tests many
// blockers against one ray, or many rays against one blocker, forms them once.
[[nodiscard]] inline bool ray_blocked(const sphere::Relative& ray, const sphere::Relative& centre, double blocker_radius_m) {
    const double psi = sphere::separation(ray.direction, centre.direction);
    const double run = centre.distance * std::cos(psi);
    const double fraction = run / ray.distance;
    if (!(fraction > 0.0 && fraction < 1.0)) return false;
    const double miss = centre.distance * std::sin(psi);
    const double chi = sphere::bearing(centre.direction, ray.direction);
    const double channel_radius = blocker_radius_m / 3.0;
    const double limit = channel_radius * channel_radius;
    for (std::size_t channel = 0; channel < channel_count; ++channel) {
        const double rho = channel_ring_radius(channel, blocker_radius_m);
        const double cross = channel == 0 ? 0.0 : 2.0 * miss * std::cos(psi) * rho * std::cos(channel_phase(channel) - chi);
        const double squared = miss * miss + rho * rho - cross;
        if (squared <= limit) return true;
    }
    return false;
}

[[nodiscard]] inline bool ray_blocked(const Locus& observer, const Locus& node, const Locus& blocker_centre, double blocker_radius_m) {
    const auto ray = sphere::relative_locus(observer, node);
    if (!ray) return true;
    const auto centre = sphere::relative_locus(observer, blocker_centre);
    if (!centre) return false;
    return ray_blocked(*ray, *centre, blocker_radius_m);
}

// T10 movement-budget response on loci: the acceleration split about the velocity into a part along it (divided by gamma^3) and a
// part across it (divided by gamma), recombined by a vector sum.
[[nodiscard]] inline Vector law_v_response(const Vector& acceleration, const Vector& velocity) {
    if (!acceleration) return std::nullopt;
    if (!velocity) return acceleration;
    const double speed = velocity->radius();
    if (!(speed < laws::measured::c)) return std::nullopt;
    const double gamma = laws::law_V::gamma(speed);
    const Direction along = sphere::unit(*velocity);
    const Direction heading = sphere::unit(*acceleration);
    const double psi = sphere::separation(along, heading);
    const double magnitude = acceleration->radius();
    const double parallel = magnitude * std::cos(psi);
    const double perpendicular = magnitude * std::sin(psi);
    Vector result;
    if (parallel != 0.0) {
        const double amount = std::abs(parallel) / (gamma * gamma * gamma);
        result = sphere::add_scaled(result, parallel > 0.0 ? along : sphere::antipode(along), amount);
    }
    if (perpendicular > 0.0) {
        const Direction across = sphere::offset_direction(along, sphere::kHalfPi, sphere::bearing(along, heading));
        result = sphere::add_scaled(result, across, perpendicular / gamma);
    }
    return result;
}

}  // namespace sdt::occlusion_sphere
