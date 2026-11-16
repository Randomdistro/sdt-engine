#pragma once

#include <sdt/dynamics.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <limits>
#include <numbers>
#include <string>
#include <vector>

namespace sdt_solver::multibody {

using sdt::dynamics::Vec3;
using sdt::dynamics::cross;
using sdt::dynamics::dot;
using sdt::dynamics::norm;

struct Quaternion {
    double w{1.0};
    double x{};
    double y{};
    double z{};
};

[[nodiscard]] constexpr auto operator*(Quaternion a, Quaternion b) noexcept
    -> Quaternion {
    return {
        a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w
    };
}

[[nodiscard]] constexpr auto conjugate(Quaternion q) noexcept -> Quaternion {
    return {q.w, -q.x, -q.y, -q.z};
}

[[nodiscard]] constexpr auto norm_squared(Quaternion q) noexcept -> double {
    return q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z;
}

[[nodiscard]] inline auto normalized(Quaternion q) noexcept -> Quaternion {
    const double magnitude = std::sqrt(norm_squared(q));
    if (!std::isfinite(magnitude) || magnitude <= 0.0) return {};
    return {
        q.w / magnitude,
        q.x / magnitude,
        q.y / magnitude,
        q.z / magnitude
    };
}

[[nodiscard]] inline auto rotate(Quaternion q, Vec3 value) noexcept -> Vec3 {
    q = normalized(q);
    const Quaternion p{0.0, value.x, value.y, value.z};
    const Quaternion result = q * p * conjugate(q);
    return {result.x, result.y, result.z};
}

[[nodiscard]] inline auto axis_angle(Vec3 axis, double angle) noexcept
    -> Quaternion {
    const double axis_norm = norm(axis);
    if (!(axis_norm > 0.0) || !std::isfinite(axis_norm)) return {};
    axis = axis / axis_norm;
    const double half = 0.5 * angle;
    const double sine = std::sin(half);
    return {
        std::cos(half),
        axis.x * sine,
        axis.y * sine,
        axis.z * sine
    };
}

[[nodiscard]] inline auto integrate(
    Quaternion orientation,
    Vec3 angular_velocity_world,
    double dt_s
) noexcept -> Quaternion {
    const double speed = norm(angular_velocity_world);
    if (speed == 0.0) return normalized(orientation);
    return normalized(
        axis_angle(angular_velocity_world / speed, speed * dt_s) * orientation
    );
}

[[nodiscard]] inline auto project_twist(
    Quaternion orientation,
    Vec3 axis_world
) noexcept -> Quaternion {
    axis_world = axis_world / norm(axis_world);
    const Vec3 vector{orientation.x, orientation.y, orientation.z};
    const double projection = dot(vector, axis_world);
    Quaternion twist{
        orientation.w,
        axis_world.x * projection,
        axis_world.y * projection,
        axis_world.z * projection
    };
    if (norm_squared(twist) < 1.0e-30) {
        twist = axis_angle(axis_world, std::numbers::pi);
    }
    twist = normalized(twist);
    return twist.w < 0.0
        ? Quaternion{-twist.w, -twist.x, -twist.y, -twist.z}
        : twist;
}

[[nodiscard]] inline auto rotation_vector(
    Quaternion from,
    Quaternion to
) noexcept -> Vec3 {
    Quaternion delta = normalized(to * conjugate(normalized(from)));
    if (delta.w < 0.0) {
        delta = {-delta.w, -delta.x, -delta.y, -delta.z};
    }
    const Vec3 vector{delta.x, delta.y, delta.z};
    const double sine = norm(vector);
    if (sine < 1.0e-18) return vector * 2.0;
    const double angle = 2.0 * std::atan2(sine, delta.w);
    return vector * (angle / sine);
}

struct Mat3 {
    std::array<double, 9> value{};

    [[nodiscard]] constexpr auto operator()(int row, int column) const noexcept
        -> double {
        return value[static_cast<std::size_t>(3 * row + column)];
    }

    constexpr auto operator()(int row, int column) noexcept -> double& {
        return value[static_cast<std::size_t>(3 * row + column)];
    }
};

[[nodiscard]] constexpr auto identity(double scale = 1.0) noexcept -> Mat3 {
    Mat3 result{};
    result(0, 0) = scale;
    result(1, 1) = scale;
    result(2, 2) = scale;
    return result;
}

[[nodiscard]] constexpr auto operator+(Mat3 a, Mat3 b) noexcept -> Mat3 {
    for (std::size_t i = 0; i < a.value.size(); ++i) {
        a.value[i] += b.value[i];
    }
    return a;
}

[[nodiscard]] constexpr auto operator-(Mat3 a, Mat3 b) noexcept -> Mat3 {
    for (std::size_t i = 0; i < a.value.size(); ++i) {
        a.value[i] -= b.value[i];
    }
    return a;
}

[[nodiscard]] constexpr auto operator*(Mat3 matrix, Vec3 vector) noexcept
    -> Vec3 {
    return {
        matrix(0, 0) * vector.x + matrix(0, 1) * vector.y
            + matrix(0, 2) * vector.z,
        matrix(1, 0) * vector.x + matrix(1, 1) * vector.y
            + matrix(1, 2) * vector.z,
        matrix(2, 0) * vector.x + matrix(2, 1) * vector.y
            + matrix(2, 2) * vector.z
    };
}

[[nodiscard]] constexpr auto operator*(Mat3 a, Mat3 b) noexcept -> Mat3 {
    Mat3 result{};
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            for (int k = 0; k < 3; ++k) {
                result(row, column) += a(row, k) * b(k, column);
            }
        }
    }
    return result;
}

[[nodiscard]] constexpr auto transpose(Mat3 matrix) noexcept -> Mat3 {
    Mat3 result{};
    for (int row = 0; row < 3; ++row) {
        for (int column = 0; column < 3; ++column) {
            result(row, column) = matrix(column, row);
        }
    }
    return result;
}

[[nodiscard]] constexpr auto skew(Vec3 value) noexcept -> Mat3 {
    Mat3 result{};
    result(0, 1) = -value.z;
    result(0, 2) = value.y;
    result(1, 0) = value.z;
    result(1, 2) = -value.x;
    result(2, 0) = -value.y;
    result(2, 1) = value.x;
    return result;
}

[[nodiscard]] inline auto rotation_matrix(Quaternion q) noexcept -> Mat3 {
    q = normalized(q);
    Mat3 result{};
    const double xx = q.x * q.x;
    const double yy = q.y * q.y;
    const double zz = q.z * q.z;
    const double xy = q.x * q.y;
    const double xz = q.x * q.z;
    const double yz = q.y * q.z;
    const double wx = q.w * q.x;
    const double wy = q.w * q.y;
    const double wz = q.w * q.z;
    result(0, 0) = 1.0 - 2.0 * (yy + zz);
    result(0, 1) = 2.0 * (xy - wz);
    result(0, 2) = 2.0 * (xz + wy);
    result(1, 0) = 2.0 * (xy + wz);
    result(1, 1) = 1.0 - 2.0 * (xx + zz);
    result(1, 2) = 2.0 * (yz - wx);
    result(2, 0) = 2.0 * (xz - wy);
    result(2, 1) = 2.0 * (yz + wx);
    result(2, 2) = 1.0 - 2.0 * (xx + yy);
    return result;
}

[[nodiscard]] inline auto solve(Mat3 matrix, Vec3 rhs, Vec3& result) noexcept
    -> bool {
    double augmented[3][4]{
        {matrix(0, 0), matrix(0, 1), matrix(0, 2), rhs.x},
        {matrix(1, 0), matrix(1, 1), matrix(1, 2), rhs.y},
        {matrix(2, 0), matrix(2, 1), matrix(2, 2), rhs.z}
    };
    for (int column = 0; column < 3; ++column) {
        int pivot = column;
        for (int row = column + 1; row < 3; ++row) {
            if (std::abs(augmented[row][column])
                > std::abs(augmented[pivot][column])) {
                pivot = row;
            }
        }
        if (std::abs(augmented[pivot][column]) < 1.0e-18) return false;
        if (pivot != column) {
            for (int k = column; k < 4; ++k) {
                std::swap(augmented[pivot][k], augmented[column][k]);
            }
        }
        const double divisor = augmented[column][column];
        for (int k = column; k < 4; ++k) {
            augmented[column][k] /= divisor;
        }
        for (int row = 0; row < 3; ++row) {
            if (row == column) continue;
            const double factor = augmented[row][column];
            for (int k = column; k < 4; ++k) {
                augmented[row][k] -= factor * augmented[column][k];
            }
        }
    }
    result = {augmented[0][3], augmented[1][3], augmented[2][3]};
    return std::isfinite(result.x) && std::isfinite(result.y)
        && std::isfinite(result.z);
}

struct RigidLink {
    std::string id;
    Vec3 position_m{};
    Quaternion orientation{};
    Vec3 velocity_m_s{};
    Vec3 angular_velocity_rad_s{};
    double inertial_mass_kg{};
    Vec3 inertia_diagonal_kg_m2{};
    double length_m{};
    double koppa_m{};
};

struct RevoluteJoint {
    std::string id;
    int parent{-1};
    std::size_t child{};
    Vec3 parent_anchor_m{};
    Vec3 child_anchor_m{};
    Vec3 axis_world{0.0, 0.0, 1.0};
};

struct Tolerances {
    double position_m{1.0e-10};
    double velocity_m_s{1.0e-10};
    double quaternion_norm{1.0e-12};
    int max_constraint_iterations{64};
};

struct Residuals {
    double position_m{};
    double velocity_m_s{};
    double quaternion_norm{};
    int position_iterations{};
    int velocity_iterations{};
};

enum class StepStatus {
    advanced,
    invalid_state,
    constraint_failure
};

[[nodiscard]] inline auto inverse_inertia_world(const RigidLink& link) noexcept
    -> Mat3 {
    Mat3 diagonal{};
    diagonal(0, 0) = 1.0 / link.inertia_diagonal_kg_m2.x;
    diagonal(1, 1) = 1.0 / link.inertia_diagonal_kg_m2.y;
    diagonal(2, 2) = 1.0 / link.inertia_diagonal_kg_m2.z;
    const Mat3 rotation = rotation_matrix(link.orientation);
    return rotation * diagonal * transpose(rotation);
}

[[nodiscard]] inline auto inertia_world(const RigidLink& link) noexcept -> Mat3 {
    Mat3 diagonal{};
    diagonal(0, 0) = link.inertia_diagonal_kg_m2.x;
    diagonal(1, 1) = link.inertia_diagonal_kg_m2.y;
    diagonal(2, 2) = link.inertia_diagonal_kg_m2.z;
    const Mat3 rotation = rotation_matrix(link.orientation);
    return rotation * diagonal * transpose(rotation);
}

[[nodiscard]] inline auto finite(const RigidLink& link) noexcept -> bool {
    const auto finite_vec = [](Vec3 value) {
        return std::isfinite(value.x) && std::isfinite(value.y)
            && std::isfinite(value.z);
    };
    return !link.id.empty()
        && finite_vec(link.position_m)
        && finite_vec(link.velocity_m_s)
        && finite_vec(link.angular_velocity_rad_s)
        && finite_vec(link.inertia_diagonal_kg_m2)
        && std::isfinite(norm_squared(link.orientation))
        && std::isfinite(link.inertial_mass_kg)
        && std::isfinite(link.length_m)
        && std::isfinite(link.koppa_m)
        && link.inertial_mass_kg > 0.0
        && link.inertia_diagonal_kg_m2.x > 0.0
        && link.inertia_diagonal_kg_m2.y > 0.0
        && link.inertia_diagonal_kg_m2.z > 0.0
        && link.length_m > 0.0
        && link.koppa_m >= 0.0
        && norm_squared(link.orientation) > 0.0;
}

[[nodiscard]] inline auto anchor_position(
    const std::vector<RigidLink>& links,
    const RevoluteJoint& joint,
    bool parent
) noexcept -> Vec3 {
    if (parent && joint.parent < 0) return joint.parent_anchor_m;
    const std::size_t index = parent
        ? static_cast<std::size_t>(joint.parent)
        : joint.child;
    const Vec3 local = parent
        ? joint.parent_anchor_m
        : joint.child_anchor_m;
    return links[index].position_m + rotate(links[index].orientation, local);
}

[[nodiscard]] inline auto anchor_velocity(
    const std::vector<RigidLink>& links,
    const RevoluteJoint& joint,
    bool parent
) noexcept -> Vec3 {
    if (parent && joint.parent < 0) return {};
    const std::size_t index = parent
        ? static_cast<std::size_t>(joint.parent)
        : joint.child;
    const Vec3 local = parent
        ? joint.parent_anchor_m
        : joint.child_anchor_m;
    const Vec3 radius = rotate(links[index].orientation, local);
    return links[index].velocity_m_s
        + cross(links[index].angular_velocity_rad_s, radius);
}

[[nodiscard]] inline auto effective_anchor_mass(
    const RigidLink& link,
    Vec3 radius_world
) noexcept -> Mat3 {
    const Mat3 radius_cross = skew(radius_world);
    return identity(1.0 / link.inertial_mass_kg)
        - radius_cross * inverse_inertia_world(link) * radius_cross;
}

inline void apply_position_impulse(
    RigidLink& link,
    Vec3 radius_world,
    Vec3 impulse
) noexcept {
    link.position_m += impulse / link.inertial_mass_kg;
    const Vec3 angle =
        inverse_inertia_world(link) * cross(radius_world, impulse);
    const double angle_norm = norm(angle);
    if (angle_norm > 0.0) {
        link.orientation = normalized(
            axis_angle(angle / angle_norm, angle_norm) * link.orientation
        );
    }
}

inline void apply_velocity_impulse(
    RigidLink& link,
    Vec3 radius_world,
    Vec3 impulse
) noexcept {
    link.velocity_m_s += impulse / link.inertial_mass_kg;
    link.angular_velocity_rad_s +=
        inverse_inertia_world(link) * cross(radius_world, impulse);
}

inline void project_joint_axes(
    std::vector<RigidLink>& links,
    const std::vector<RevoluteJoint>& joints
) noexcept {
    for (const auto& joint : joints) {
        links[joint.child].orientation =
            project_twist(links[joint.child].orientation, joint.axis_world);
        links[joint.child].angular_velocity_rad_s =
            joint.axis_world
            * dot(links[joint.child].angular_velocity_rad_s, joint.axis_world);
    }
}

[[nodiscard]] inline auto project_positions(
    std::vector<RigidLink>& links,
    const std::vector<RevoluteJoint>& joints,
    const Tolerances& tolerances,
    Residuals& residuals
) noexcept -> bool {
    for (int iteration = 0;
         iteration < tolerances.max_constraint_iterations;
         ++iteration) {
        project_joint_axes(links, joints);
        double maximum = 0.0;
        for (const auto& joint : joints) {
            RigidLink& child = links[joint.child];
            RigidLink* parent = joint.parent < 0
                ? nullptr
                : &links[static_cast<std::size_t>(joint.parent)];
            const Vec3 child_radius =
                rotate(child.orientation, joint.child_anchor_m);
            const Vec3 parent_radius = parent == nullptr
                ? Vec3{}
                : rotate(parent->orientation, joint.parent_anchor_m);
            const Vec3 error =
                anchor_position(links, joint, false)
                - anchor_position(links, joint, true);
            maximum = std::max(maximum, norm(error));
            Mat3 effective = effective_anchor_mass(child, child_radius);
            if (parent != nullptr) {
                effective = effective
                    + effective_anchor_mass(*parent, parent_radius);
            }
            Vec3 lambda{};
            if (!solve(effective, error, lambda)) return false;
            apply_position_impulse(child, child_radius, lambda * -1.0);
            if (parent != nullptr) {
                apply_position_impulse(*parent, parent_radius, lambda);
            }
        }
        residuals.position_iterations = iteration + 1;
        residuals.position_m = maximum;
        if (maximum <= tolerances.position_m) {
            project_joint_axes(links, joints);
            double projected_maximum = 0.0;
            for (const auto& joint : joints) {
                projected_maximum = std::max(
                    projected_maximum,
                    norm(
                        anchor_position(links, joint, false)
                        - anchor_position(links, joint, true)
                    )
                );
            }
            residuals.position_m = projected_maximum;
            if (projected_maximum <= tolerances.position_m) return true;
        }
    }
    return false;
}

[[nodiscard]] inline auto project_velocities(
    std::vector<RigidLink>& links,
    const std::vector<RevoluteJoint>& joints,
    const Tolerances& tolerances,
    Residuals& residuals
) noexcept -> bool {
    for (int iteration = 0;
         iteration < tolerances.max_constraint_iterations;
         ++iteration) {
        project_joint_axes(links, joints);
        double maximum = 0.0;
        for (const auto& joint : joints) {
            RigidLink& child = links[joint.child];
            RigidLink* parent = joint.parent < 0
                ? nullptr
                : &links[static_cast<std::size_t>(joint.parent)];
            const Vec3 child_radius =
                rotate(child.orientation, joint.child_anchor_m);
            const Vec3 parent_radius = parent == nullptr
                ? Vec3{}
                : rotate(parent->orientation, joint.parent_anchor_m);
            const Vec3 error =
                anchor_velocity(links, joint, false)
                - anchor_velocity(links, joint, true);
            maximum = std::max(maximum, norm(error));
            Mat3 effective = effective_anchor_mass(child, child_radius);
            if (parent != nullptr) {
                effective = effective
                    + effective_anchor_mass(*parent, parent_radius);
            }
            Vec3 lambda{};
            if (!solve(effective, error, lambda)) return false;
            apply_velocity_impulse(child, child_radius, lambda * -1.0);
            if (parent != nullptr) {
                apply_velocity_impulse(*parent, parent_radius, lambda);
            }
        }
        residuals.velocity_iterations = iteration + 1;
        residuals.velocity_m_s = maximum;
        if (maximum <= tolerances.velocity_m_s) {
            project_joint_axes(links, joints);
            double projected_maximum = 0.0;
            for (const auto& joint : joints) {
                projected_maximum = std::max(
                    projected_maximum,
                    norm(
                        anchor_velocity(links, joint, false)
                        - anchor_velocity(links, joint, true)
                    )
                );
            }
            residuals.velocity_m_s = projected_maximum;
            if (projected_maximum <= tolerances.velocity_m_s) return true;
        }
    }
    return false;
}

[[nodiscard]] inline auto validate_chain(
    const std::vector<RigidLink>& links,
    const std::vector<RevoluteJoint>& joints,
    std::string& error
) -> bool {
    if (links.empty() || joints.size() != links.size()) {
        error = "an open chain requires one revolute joint per link";
        return false;
    }
    std::vector<int> parent_count(links.size(), 0);
    for (std::size_t i = 0; i < links.size(); ++i) {
        if (!finite(links[i])) {
            error = "link state is non-finite or non-positive";
            return false;
        }
    }
    for (const auto& joint : joints) {
        if (joint.child >= links.size()
            || joint.parent >= static_cast<int>(links.size())
            || joint.parent == static_cast<int>(joint.child)) {
            error = "joint references an invalid link";
            return false;
        }
        const double axis_norm = norm(joint.axis_world);
        if (!std::isfinite(axis_norm) || std::abs(axis_norm - 1.0) > 1.0e-12) {
            error = "joint axis must be unit length";
            return false;
        }
        if (++parent_count[joint.child] != 1) {
            error = "each link must have exactly one parent joint";
            return false;
        }
    }
    int world_roots = 0;
    for (const auto& joint : joints) {
        if (joint.parent < 0) {
            ++world_roots;
        } else if (static_cast<std::size_t>(joint.parent) >= joint.child) {
            error = "links and joints must be in root-to-tip order";
            return false;
        }
    }
    if (world_roots != 1) {
        error = "an open chain requires exactly one world root";
        return false;
    }
    return true;
}

[[nodiscard]] inline auto step(
    std::vector<RigidLink>& links,
    const std::vector<RevoluteJoint>& joints,
    Vec3 uniform_acceleration_m_s2,
    double dt_s,
    const Tolerances& tolerances,
    Residuals& residuals
) noexcept -> StepStatus {
    if (!std::isfinite(dt_s) || dt_s <= 0.0) {
        return StepStatus::invalid_state;
    }
    if (links.size() == 1 && joints.size() == 1 && joints[0].parent < 0) {
        auto next = links;
        RigidLink& link = next[0];
        const RevoluteJoint& joint = joints[0];
        if (!finite(link)) return StepStatus::invalid_state;
        const Vec3 axis = joint.axis_world;
        link.orientation = project_twist(link.orientation, axis);
        const auto angular_acceleration = [&](
            const RigidLink& state
        ) noexcept {
            const Vec3 anchor_radius =
                rotate(state.orientation, joint.child_anchor_m);
            const Vec3 centre_from_pivot = anchor_radius * -1.0;
            const double parallel = dot(axis, centre_from_pivot);
            const double perpendicular_squared =
                dot(centre_from_pivot, centre_from_pivot)
                - parallel * parallel;
            const double pivot_inertia =
                dot(axis, inertia_world(state) * axis)
                + state.inertial_mass_kg * perpendicular_squared;
            const Vec3 force =
                uniform_acceleration_m_s2 * state.inertial_mass_kg;
            return dot(axis, cross(centre_from_pivot, force)) / pivot_inertia;
        };
        double angular_speed = dot(link.angular_velocity_rad_s, axis);
        angular_speed += 0.5 * angular_acceleration(link) * dt_s;
        link.orientation = project_twist(
            integrate(link.orientation, axis * angular_speed, dt_s),
            axis
        );
        const Vec3 anchor_radius =
            rotate(link.orientation, joint.child_anchor_m);
        link.position_m = joint.parent_anchor_m - anchor_radius;
        angular_speed += 0.5 * angular_acceleration(link) * dt_s;
        link.angular_velocity_rad_s = axis * angular_speed;
        link.velocity_m_s = cross(
            link.angular_velocity_rad_s,
            link.position_m - joint.parent_anchor_m
        );
        residuals = {};
        residuals.position_iterations = 1;
        residuals.velocity_iterations = 1;
        residuals.position_m = norm(
            link.position_m + anchor_radius - joint.parent_anchor_m
        );
        residuals.velocity_m_s = norm(
            link.velocity_m_s
            + cross(link.angular_velocity_rad_s, anchor_radius)
        );
        residuals.quaternion_norm =
            std::abs(std::sqrt(norm_squared(link.orientation)) - 1.0);
        if (residuals.position_m > tolerances.position_m
            || residuals.velocity_m_s > tolerances.velocity_m_s
            || residuals.quaternion_norm > tolerances.quaternion_norm) {
            return StepStatus::constraint_failure;
        }
        links.swap(next);
        return StepStatus::advanced;
    }
    auto next = links;
    for (auto& link : next) {
        if (!finite(link)) return StepStatus::invalid_state;
        link.velocity_m_s += uniform_acceleration_m_s2 * (0.5 * dt_s);
        link.position_m += link.velocity_m_s * dt_s;
        link.orientation =
            integrate(link.orientation, link.angular_velocity_rad_s, dt_s);
    }
    const auto predicted = next;
    Residuals current{};
    if (!project_positions(next, joints, tolerances, current)) {
        residuals = current;
        return StepStatus::constraint_failure;
    }
    for (std::size_t i = 0; i < next.size(); ++i) {
        next[i].velocity_m_s +=
            (next[i].position_m - predicted[i].position_m) / dt_s;
        next[i].angular_velocity_rad_s += rotation_vector(
            predicted[i].orientation,
            next[i].orientation
        ) / dt_s;
        next[i].velocity_m_s +=
            uniform_acceleration_m_s2 * (0.5 * dt_s);
    }
    if (!project_velocities(next, joints, tolerances, current)) {
        residuals = current;
        return StepStatus::constraint_failure;
    }
    for (const auto& link : next) {
        current.quaternion_norm = std::max(
            current.quaternion_norm,
            std::abs(std::sqrt(norm_squared(link.orientation)) - 1.0)
        );
    }
    if (current.quaternion_norm > tolerances.quaternion_norm) {
        residuals = current;
        return StepStatus::constraint_failure;
    }
    links.swap(next);
    residuals = current;
    return StepStatus::advanced;
}

[[nodiscard]] inline auto mechanical_energy(
    const std::vector<RigidLink>& links,
    Vec3 uniform_acceleration_m_s2
) noexcept -> double {
    double energy = 0.0;
    for (const auto& link : links) {
        energy += 0.5 * link.inertial_mass_kg
            * dot(link.velocity_m_s, link.velocity_m_s);
        energy += 0.5 * dot(
            link.angular_velocity_rad_s,
            inertia_world(link) * link.angular_velocity_rad_s
        );
        energy -= link.inertial_mass_kg
            * dot(uniform_acceleration_m_s2, link.position_m);
    }
    return energy;
}

} // namespace sdt_solver::multibody
