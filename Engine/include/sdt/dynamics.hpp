#pragma once

#include <sdt/laws.hpp>

#include <cmath>
#include <cstddef>
#include <numbers>
#include <vector>

namespace sdt::dynamics {

struct Vec3 {
    double x{};
    double y{};
    double z{};
};

[[nodiscard]] constexpr auto operator+(Vec3 a, Vec3 b) noexcept -> Vec3 {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

[[nodiscard]] constexpr auto operator-(Vec3 a, Vec3 b) noexcept -> Vec3 {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

[[nodiscard]] constexpr auto operator*(Vec3 value, double scale) noexcept -> Vec3 {
    return {value.x * scale, value.y * scale, value.z * scale};
}

[[nodiscard]] constexpr auto operator*(double scale, Vec3 value) noexcept -> Vec3 {
    return value * scale;
}

[[nodiscard]] constexpr auto operator/(Vec3 value, double scale) noexcept -> Vec3 {
    return {value.x / scale, value.y / scale, value.z / scale};
}

constexpr auto operator+=(Vec3& a, Vec3 b) noexcept -> Vec3& {
    a = a + b;
    return a;
}

constexpr auto operator-=(Vec3& a, Vec3 b) noexcept -> Vec3& {
    a = a - b;
    return a;
}

[[nodiscard]] constexpr auto dot(Vec3 a, Vec3 b) noexcept -> double {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

[[nodiscard]] constexpr auto cross(Vec3 a, Vec3 b) noexcept -> Vec3 {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

[[nodiscard]] inline auto norm(Vec3 value) noexcept -> double {
    return std::sqrt(dot(value, value));
}

struct Body {
    Vec3 position{};
    Vec3 velocity{};
    double koppa_m{};
    double collision_radius_m{};
};

enum class StepStatus {
    advanced,
    collision,
    invalid_state
};

struct Invariants {
    double koppa_weight{};
    Vec3 barycentre{};
    Vec3 momentum{};
    Vec3 angular_momentum{};
    double energy{};
};

/// T3/T6 bridge kernel: a_i = c² sum_j(koppa_j r_ji / |r_ji|³).
///
/// Source strength is a length. No G, source mass M, GM alias or force
/// softening enters. A 2D system uses the same function with z=0.
[[nodiscard]] inline auto accelerations(
    const std::vector<Body>& bodies,
    std::vector<Vec3>& result
) noexcept -> StepStatus {
    using sdt::laws::measured::c;

    result.assign(bodies.size(), {});
    for (const auto& body : bodies) {
        if (
            !std::isfinite(body.koppa_m)
            || !std::isfinite(body.collision_radius_m)
            || body.koppa_m <= 0.0
            || body.collision_radius_m < 0.0
        ) {
            return StepStatus::invalid_state;
        }
    }

    const double c2 = c * c;
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        for (std::size_t j = i + 1; j < bodies.size(); ++j) {
            const Vec3 delta = bodies[j].position - bodies[i].position;
            const double distance_squared = dot(delta, delta);
            const double contact =
                bodies[i].collision_radius_m + bodies[j].collision_radius_m;
            if (
                !std::isfinite(distance_squared)
                || distance_squared <= contact * contact
                || distance_squared == 0.0
            ) {
                return StepStatus::collision;
            }

            const double inverse_distance_cubed =
                1.0 / (distance_squared * std::sqrt(distance_squared));
            const Vec3 direction_kernel = delta * inverse_distance_cubed;
            result[i] += direction_kernel * (c2 * bodies[j].koppa_m);
            result[j] -= direction_kernel * (c2 * bodies[i].koppa_m);
        }
    }
    return StepStatus::advanced;
}

/// Velocity-Verlet step. The update is committed only if the predicted state
/// remains outside every supplied collision boundary.
[[nodiscard]] inline auto step(
    std::vector<Body>& bodies,
    double dt_s
) noexcept -> StepStatus {
    if (!std::isfinite(dt_s) || dt_s <= 0.0) {
        return StepStatus::invalid_state;
    }

    std::vector<Vec3> acceleration;
    const auto initial_status = accelerations(bodies, acceleration);
    if (initial_status != StepStatus::advanced) return initial_status;

    auto next = bodies;
    for (std::size_t i = 0; i < next.size(); ++i) {
        next[i].position +=
            bodies[i].velocity * dt_s
            + acceleration[i] * (0.5 * dt_s * dt_s);
    }

    std::vector<Vec3> next_acceleration;
    const auto predicted_status = accelerations(next, next_acceleration);
    if (predicted_status != StepStatus::advanced) return predicted_status;

    for (std::size_t i = 0; i < next.size(); ++i) {
        next[i].velocity +=
            (acceleration[i] + next_acceleration[i]) * (0.5 * dt_s);
    }

    bodies.swap(next);
    return StepStatus::advanced;
}

[[nodiscard]] inline auto invariants(
    const std::vector<Body>& bodies
) noexcept -> Invariants {
    using sdt::laws::measured::c;

    Invariants value{};
    for (const auto& body : bodies) {
        value.koppa_weight += body.koppa_m;
        value.barycentre += body.position * body.koppa_m;
        value.momentum += body.velocity * body.koppa_m;
        value.angular_momentum +=
            cross(body.position, body.velocity) * body.koppa_m;
        value.energy +=
            0.5 * body.koppa_m * dot(body.velocity, body.velocity);
    }
    if (value.koppa_weight > 0.0) {
        value.barycentre = value.barycentre / value.koppa_weight;
    }

    const double c2 = c * c;
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        for (std::size_t j = i + 1; j < bodies.size(); ++j) {
            const double distance =
                norm(bodies[j].position - bodies[i].position);
            if (distance > 0.0) {
                value.energy -=
                    c2 * bodies[i].koppa_m * bodies[j].koppa_m / distance;
            }
        }
    }
    return value;
}

[[nodiscard]] constexpr auto koppa_from_baryons(
    double baryon_count
) noexcept -> double {
    return baryon_count * sdt::laws::bridge::koppa_per_baryon;
}

[[nodiscard]] inline auto circular_pair(
    double koppa_1_m,
    double koppa_2_m,
    double separation_m
) -> std::vector<Body> {
    using sdt::laws::measured::c;

    const double total_koppa = koppa_1_m + koppa_2_m;
    const double omega =
        c * std::sqrt(total_koppa / (separation_m * separation_m * separation_m));
    const double radius_1 = separation_m * koppa_2_m / total_koppa;
    const double radius_2 = separation_m * koppa_1_m / total_koppa;

    return {
        {{-radius_1, 0.0, 0.0}, {0.0, -omega * radius_1, 0.0}, koppa_1_m, 0.0},
        {{ radius_2, 0.0, 0.0}, {0.0,  omega * radius_2, 0.0}, koppa_2_m, 0.0}
    };
}

[[nodiscard]] inline auto equilateral_three(
    double koppa_1_m,
    double koppa_2_m,
    double koppa_3_m,
    double side_m
) -> std::vector<Body> {
    using sdt::laws::measured::c;

    const double height = std::sqrt(3.0) * side_m / 2.0;
    const double total_koppa = koppa_1_m + koppa_2_m + koppa_3_m;
    const double omega =
        c * std::sqrt(
            total_koppa / (side_m * side_m * side_m)
        );

    std::vector<Body> bodies{
        {{-0.5 * side_m, -height / 3.0, 0.0}, {}, koppa_1_m, 0.0},
        {{ 0.5 * side_m, -height / 3.0, 0.0}, {}, koppa_2_m, 0.0},
        {{0.0, 2.0 * height / 3.0, 0.0}, {}, koppa_3_m, 0.0}
    };
    Vec3 barycentre{};
    for (const auto& body : bodies) {
        barycentre += body.position * body.koppa_m;
    }
    barycentre = barycentre / total_koppa;
    for (auto& body : bodies) {
        body.position -= barycentre;
        body.velocity = {
            -omega * body.position.y,
             omega * body.position.x,
             0.0
        };
    }
    return bodies;
}

[[nodiscard]] inline auto equilateral_three(
    double koppa_m,
    double side_m
) -> std::vector<Body> {
    return equilateral_three(koppa_m, koppa_m, koppa_m, side_m);
}

} // namespace sdt::dynamics
