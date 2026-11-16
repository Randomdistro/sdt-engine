#include <sdt_solver/celestial.hpp>
#include <sdt_solver/json.hpp>
#include <sdt_solver/multibody.hpp>
#include <sdt_solver/occlusion_nbody.hpp>
#include <sdt_solver/solver.hpp>

#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <numbers>
#include <string>
#include <vector>

namespace sdt_solver {
namespace {

using json::Array;
using json::Object;
using json::Value;
using multibody::Quaternion;
using multibody::RevoluteJoint;
using multibody::RigidLink;
using sdt::dynamics::Body;
using sdt::dynamics::Invariants;
using sdt::dynamics::StepStatus;
using sdt::dynamics::Vec3;

struct Check {
    std::string id;
    std::string name;
    double value{};
    std::string relation{"<="};
    double limit{};
    bool passed{};
    std::string classification;
};

void add_le(
    std::vector<Check>& checks,
    const std::string& id,
    const std::string& name,
    double value,
    double limit,
    const std::string& classification
) {
    checks.push_back({
        id, name, value, "<=", limit, value <= limit, classification
    });
}

void add_ge(
    std::vector<Check>& checks,
    const std::string& id,
    const std::string& name,
    double value,
    double limit,
    const std::string& classification
) {
    checks.push_back({
        id, name, value, ">=", limit, value >= limit, classification
    });
}

[[nodiscard]] auto relative_change(double value, double reference) -> double {
    return reference == 0.0
        ? std::abs(value)
        : std::abs(value / reference - 1.0);
}

[[nodiscard]] auto state_error(
    const std::vector<Body>& state,
    const std::vector<Body>& reference,
    double position_scale,
    double velocity_scale
) -> double {
    double position_sum = 0.0;
    double velocity_sum = 0.0;
    for (std::size_t i = 0; i < state.size(); ++i) {
        const Vec3 dp = state[i].position - reference[i].position;
        const Vec3 dv = state[i].velocity - reference[i].velocity;
        position_sum += sdt::dynamics::dot(dp, dp);
        velocity_sum += sdt::dynamics::dot(dv, dv);
    }
    return std::hypot(
        std::sqrt(position_sum / state.size()) / position_scale,
        std::sqrt(velocity_sum / state.size()) / velocity_scale
    );
}

[[nodiscard]] auto integrate(
    std::vector<Body> state,
    double dt,
    std::uint64_t steps,
    bool rk4 = false
) -> std::vector<Body> {
    for (std::uint64_t step = 0; step < steps; ++step) {
        const auto status = rk4
            ? sdt::dynamics::step_rk4(state, dt)
            : sdt::dynamics::step(state, dt);
        if (status != StepStatus::advanced) return {};
    }
    return state;
}

struct Drift {
    double separation{};
    double energy{};
    double barycentre{};
    double momentum{};
    double angular_momentum{};
    double minimum_separation{std::numeric_limits<double>::infinity()};
    double maximum_separation{};
    bool advanced{true};
};

[[nodiscard]] auto run_drift(
    std::vector<Body>& bodies,
    double dt,
    std::uint64_t steps,
    double reference_separation = 0.0
) -> Drift {
    const Invariants initial = sdt::dynamics::invariants(bodies);
    double momentum_scale = 0.0;
    double angular_scale = 0.0;
    for (const auto& body : bodies) {
        momentum_scale += body.koppa_m * sdt::dynamics::norm(body.velocity);
        angular_scale += body.koppa_m * sdt::dynamics::norm(
            sdt::dynamics::cross(body.position, body.velocity)
        );
    }
    momentum_scale = std::max(momentum_scale, 1.0e-300);
    angular_scale = std::max(angular_scale, 1.0e-300);

    Drift drift{};
    for (std::uint64_t step = 0; step < steps; ++step) {
        if (sdt::dynamics::step(bodies, dt) != StepStatus::advanced) {
            drift.advanced = false;
            break;
        }
        const Invariants current = sdt::dynamics::invariants(bodies);
        drift.energy = std::max(
            drift.energy,
            relative_change(current.energy, initial.energy)
        );
        drift.barycentre = std::max(
            drift.barycentre,
            sdt::dynamics::norm(current.barycentre - initial.barycentre)
                / std::max(reference_separation, 1.0)
        );
        drift.momentum = std::max(
            drift.momentum,
            sdt::dynamics::norm(current.momentum - initial.momentum)
                / momentum_scale
        );
        drift.angular_momentum = std::max(
            drift.angular_momentum,
            sdt::dynamics::norm(
                current.angular_momentum - initial.angular_momentum
            ) / angular_scale
        );
        if (bodies.size() >= 2) {
            const double separation =
                sdt::dynamics::norm(bodies[1].position - bodies[0].position);
            drift.minimum_separation =
                std::min(drift.minimum_separation, separation);
            drift.maximum_separation =
                std::max(drift.maximum_separation, separation);
            if (reference_separation > 0.0) {
                drift.separation = std::max(
                    drift.separation,
                    relative_change(separation, reference_separation)
                );
            }
        }
    }
    return drift;
}

[[nodiscard]] auto eccentric_pair(
    double koppa_1,
    double koppa_2,
    double semimajor_axis,
    double eccentricity
) -> std::vector<Body> {
    const double total = koppa_1 + koppa_2;
    const double separation = semimajor_axis * (1.0 - eccentricity);
    const double relative_speed = sdt::laws::measured::c * std::sqrt(
        total * (1.0 + eccentricity)
        / (semimajor_axis * (1.0 - eccentricity))
    );
    const double radius_1 = separation * koppa_2 / total;
    const double radius_2 = separation * koppa_1 / total;
    return {
        {
            {-radius_1, 0.0, 0.0},
            {0.0, -relative_speed * koppa_2 / total, 0.0},
            koppa_1,
            0.0
        },
        {
            {radius_2, 0.0, 0.0},
            {0.0, relative_speed * koppa_1 / total, 0.0},
            koppa_2,
            0.0
        }
    };
}

[[nodiscard]] auto rotate_x(Vec3 value, double angle) -> Vec3 {
    const double cosine = std::cos(angle);
    const double sine = std::sin(angle);
    return {
        value.x,
        cosine * value.y - sine * value.z,
        sine * value.y + cosine * value.z
    };
}

[[nodiscard]] auto lagrange_function(double x, double mu) -> double {
    const double d1 = x + mu;
    const double d2 = x - (1.0 - mu);
    return x
        - (1.0 - mu) * d1 / std::pow(std::abs(d1), 3)
        - mu * d2 / std::pow(std::abs(d2), 3);
}

[[nodiscard]] auto lagrange_derivative(double x, double mu) -> double {
    const double d1 = x + mu;
    const double d2 = x - (1.0 - mu);
    return 1.0
        + 2.0 * (1.0 - mu) / std::pow(std::abs(d1), 3)
        + 2.0 * mu / std::pow(std::abs(d2), 3);
}

[[nodiscard]] auto lagrange_root(double guess, double mu) -> double {
    double x = guess;
    for (int iteration = 0; iteration < 100; ++iteration) {
        const double change = lagrange_function(x, mu)
            / lagrange_derivative(x, mu);
        x -= change;
        if (std::abs(change) < 1.0e-15) break;
    }
    return x;
}

[[nodiscard]] auto quaternion_z(double angle) -> Quaternion {
    return multibody::axis_angle({0.0, 0.0, 1.0}, angle);
}

[[nodiscard]] auto make_chain(
    const std::vector<double>& lengths,
    const std::vector<double>& angles
) -> std::pair<std::vector<RigidLink>, std::vector<RevoluteJoint>> {
    std::vector<RigidLink> links;
    std::vector<RevoluteJoint> joints;
    Vec3 pivot{};
    for (std::size_t i = 0; i < lengths.size(); ++i) {
        const double length = lengths[i];
        const Quaternion orientation = quaternion_z(angles[i]);
        const Vec3 half_down =
            multibody::rotate(orientation, {0.0, -0.5 * length, 0.0});
        const Vec3 centre = pivot + half_down;
        const double mass = 1.0;
        const double transverse = mass * length * length / 12.0;
        links.push_back({
            "link-" + std::to_string(i + 1),
            centre,
            orientation,
            {},
            {},
            mass,
            {
                std::max(transverse, 1.0e-6),
                std::max(transverse, 1.0e-6),
                transverse
            },
            length,
            0.0
        });
        joints.push_back({
            "joint-" + std::to_string(i + 1),
            i == 0 ? -1 : static_cast<int>(i - 1),
            i,
            i == 0 ? Vec3{} : Vec3{0.0, -0.5 * lengths[i - 1], 0.0},
            {0.0, 0.5 * length, 0.0},
            {0.0, 0.0, 1.0}
        });
        pivot = centre + half_down;
    }
    return {std::move(links), std::move(joints)};
}

[[nodiscard]] auto make_bob_pendulum(double length, double angle)
    -> std::pair<std::vector<RigidLink>, std::vector<RevoluteJoint>> {
    const Quaternion orientation = quaternion_z(angle);
    const Vec3 centre =
        multibody::rotate(orientation, {0.0, -length, 0.0});
    const double small_inertia = 1.0e-4;
    std::vector<RigidLink> links{{
        "bob",
        centre,
        orientation,
        {},
        {},
        1.0,
        {small_inertia, small_inertia, small_inertia},
        length,
        0.0
    }};
    std::vector<RevoluteJoint> joints{{
        "pivot",
        -1,
        0,
        {},
        {0.0, length, 0.0},
        {0.0, 0.0, 1.0}
    }};
    return {std::move(links), std::move(joints)};
}

struct RigidRun {
    bool advanced{true};
    double max_position{};
    double max_velocity{};
    double max_quaternion{};
    double max_energy{};
    std::vector<double> downward_crossings;
    double final_angle{};
};

[[nodiscard]] auto link_angle(const RigidLink& link) -> double {
    const Vec3 down =
        multibody::rotate(link.orientation, {0.0, -1.0, 0.0});
    return std::atan2(down.x, -down.y);
}

[[nodiscard]] auto run_rigid(
    std::vector<RigidLink> links,
    const std::vector<RevoluteJoint>& joints,
    Vec3 acceleration,
    double dt,
    std::uint64_t steps,
    const multibody::Tolerances& tolerances
) -> RigidRun {
    RigidRun result;
    const double initial_energy =
        multibody::mechanical_energy(links, acceleration);
    double previous_angle = link_angle(links[0]);
    for (std::uint64_t step = 1; step <= steps; ++step) {
        multibody::Residuals residuals{};
        if (multibody::step(
                links,
                joints,
                acceleration,
                dt,
                tolerances,
                residuals
            ) != multibody::StepStatus::advanced) {
            result.advanced = false;
            break;
        }
        result.max_position =
            std::max(result.max_position, residuals.position_m);
        result.max_velocity =
            std::max(result.max_velocity, residuals.velocity_m_s);
        result.max_quaternion =
            std::max(result.max_quaternion, residuals.quaternion_norm);
        result.max_energy = std::max(
            result.max_energy,
            relative_change(
                multibody::mechanical_energy(links, acceleration),
                initial_energy
            )
        );
        const double angle = link_angle(links[0]);
        if (previous_angle > 0.0 && angle <= 0.0) {
            const double fraction = previous_angle / (previous_angle - angle);
            result.downward_crossings.push_back(
                (static_cast<double>(step - 1) + fraction) * dt
            );
        }
        previous_angle = angle;
    }
    result.final_angle = link_angle(links[0]);
    return result;
}

[[nodiscard]] auto elliptic_k(double parameter) -> double {
    double a = 1.0;
    double b = std::sqrt(1.0 - parameter);
    for (int iteration = 0; iteration < 32; ++iteration) {
        const double next_a = 0.5 * (a + b);
        const double next_b = std::sqrt(a * b);
        a = next_a;
        b = next_b;
        if (std::abs(a - b) < 1.0e-16 * a) break;
    }
    return std::numbers::pi / (2.0 * a);
}

[[nodiscard]] auto status_of(const std::string& result_json) -> std::string {
    const Value parsed = json::parse(result_json);
    return parsed.object().at("status").string();
}

void contract_checks(std::vector<Check>& checks) {
    const std::string case_json = R"({
      "contract_version":"1.0.0",
      "case_id":"determinism-smoke",
      "problem_class":"point_nbody",
      "frame":{"type":"inertial_cartesian","units":"SI"},
      "forces":[{"type":"koppa_pairwise"}],
      "bodies":[
        {"id":"a","position_m":[-1,0,0],"velocity_m_s":[0,-1,0],"koppa_m":1e-18,"collision_radius_m":0},
        {"id":"b","position_m":[1,0,0],"velocity_m_s":[0,1,0],"koppa_m":1e-18,"collision_radius_m":0}
      ],
      "integrator":"velocity_verlet",
      "timestep_s":0.001,
      "duration_s":0.01,
      "record_every_steps":1,
      "tolerances":{"position_m":1e-10,"velocity_m_s":1e-10,"quaternion_norm":1e-12,"max_constraint_iterations":64},
      "gates":[]
    })";
    const std::string rigid_json = R"({
      "contract_version":"1.0.0",
      "case_id":"rigid-validation-smoke",
      "problem_class":"articulated_rigid",
      "frame":{"type":"inertial_cartesian","units":"SI"},
      "forces":[{"type":"uniform_acceleration","acceleration_m_s2":[0,-9.80665,0],"provenance":{"classification":"MEASURED-INPUT","description":"validation fixture"}}],
      "links":[{"id":"rod","position_m":[0,-0.5,0],"quaternion_wxyz":[1,0,0,0],"velocity_m_s":[0,0,0],"angular_velocity_rad_s":[0,0,0],"inertial_mass_kg":1,"inertia_diagonal_kg_m2":[0.083333333333,0.000001,0.083333333333],"length_m":1}],
      "joints":[{"id":"pivot","parent":null,"child":"rod","parent_anchor_m":[0,0,0],"child_anchor_m":[0,0.5,0],"axis_world":[0,0,1]}],
      "integrator":"rattle",
      "timestep_s":0.001,
      "duration_s":0.01,
      "record_every_steps":1,
      "tolerances":{"position_m":1e-10,"velocity_m_s":1e-10,"quaternion_norm":1e-12,"max_constraint_iterations":64},
      "gates":[]
    })";
    const auto changed = [](std::string source,
                            const std::string& from,
                            const std::string& to) {
        const auto position = source.find(from);
        if (position == std::string::npos) return std::string{};
        source.replace(position, from.size(), to);
        return source;
    };
    const std::vector<std::string> invalid_cases{
        "{",
        R"({"contract_version":"2.0.0"})",
        R"({"contract_version":"1.0.0","case_id":"x","problem_class":"bad"})",
        changed(case_json, R"("id":"b")", R"("id":"a")"),
        changed(case_json, R"("timestep_s":0.001)", R"("timestep_s":-0.001)"),
        changed(case_json, R"("duration_s":0.01)", R"("duration_s":0.0105)"),
        changed(
            case_json,
            R"("record_every_steps":1)",
            R"("record_every_steps":11)"
        ),
        changed(rigid_json, R"("axis_world":[0,0,1])", R"("axis_world":[0,0,2])"),
        changed(rigid_json, R"("parent":null)", R"("parent":"rod")")
    };
    double rejected = 0.0;
    for (const auto& invalid : invalid_cases) {
        if (status_of(run_case_json(invalid)) == "invalid_case") rejected += 1.0;
    }
    add_ge(
        checks,
        "K0",
        "malformed cases classified",
        rejected,
        static_cast<double>(invalid_cases.size()),
        "CONTRACT"
    );

    const std::string first = run_case_json(case_json);
    const std::string second = run_case_json(case_json);
    add_ge(
        checks,
        "K1",
        "byte-identical replay",
        first == second ? 1.0 : 0.0,
        1.0,
        "CONTRACT"
    );
    const Value manifest = json::parse(manifest_json());
    const std::string hash = manifest.object().at("laws_sha256").string();
    const bool valid_hash = hash.size() == 64
        && std::all_of(hash.begin(), hash.end(), [](char ch) {
            return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f');
        })
        && hash != std::string(64, '0');
    add_ge(
        checks,
        "K2",
        "configured laws SHA-256",
        valid_hash ? 1.0 : 0.0,
        1.0,
        "CONTRACT"
    );
    char* abi_result = run_case(case_json.c_str());
    char* abi_manifest = solver_manifest();
    const bool abi_ok = abi_result != nullptr && abi_manifest != nullptr
        && status_of(abi_result) == "completed"
        && json::parse(abi_manifest).is_object();
    solver_free(abi_result);
    solver_free(abi_manifest);
    add_ge(
        checks,
        "K3",
        "C ABI buffers",
        abi_ok ? 1.0 : 0.0,
        1.0,
        "CONTRACT"
    );
}

void nbody_checks(std::vector<Check>& checks) {
    using sdt::laws::measured::c;
    std::vector<Body> pair{
        {{0.0, 0.0, 0.0}, {}, 2.0e-3, 0.0},
        {{1.0e9, 0.0, 0.0}, {}, 3.0e-3, 0.0}
    };
    std::vector<Vec3> acceleration;
    const auto status = sdt::dynamics::accelerations(pair, acceleration);
    const Vec3 weighted =
        acceleration[0] * pair[0].koppa_m
        + acceleration[1] * pair[1].koppa_m;
    const double symmetry = status == StepStatus::advanced
        ? sdt::dynamics::norm(weighted)
            / (pair[0].koppa_m * sdt::dynamics::norm(acceleration[0]))
        : 1.0;
    pair[1].position.x = 2.0e9;
    std::vector<Vec3> acceleration_2r;
    static_cast<void>(sdt::dynamics::accelerations(pair, acceleration_2r));
    const double inverse_square = std::abs(
        sdt::dynamics::norm(acceleration[0])
            / sdt::dynamics::norm(acceleration_2r[0])
        - 4.0
    );
    add_le(checks, "N0a", "pair symmetry", symmetry, 1.0e-14, "VALIDATED");
    add_le(
        checks,
        "N0b",
        "inverse-square scaling",
        inverse_square,
        1.0e-14,
        "VALIDATED"
    );

    constexpr double separation = 1.0e9;
    constexpr double k1 = 1.0e-3;
    constexpr double k2 = 2.0e-3;
    const double period = 2.0 * std::numbers::pi * std::sqrt(
        separation * separation * separation / (c * c * (k1 + k2))
    );
    auto circular = sdt::dynamics::circular_pair(k1, k2, separation);
    const Drift circular_drift =
        run_drift(circular, period / 2000.0, 200'000, separation);
    add_le(
        checks,
        "N1a",
        "circular separation drift",
        circular_drift.advanced ? circular_drift.separation : 1.0,
        5.0e-5,
        "VALIDATED"
    );
    add_le(
        checks,
        "N1b",
        "circular energy drift",
        circular_drift.advanced ? circular_drift.energy : 1.0,
        5.0e-6,
        "VALIDATED"
    );

    constexpr double semimajor = 1.2e9;
    constexpr double eccentricity = 0.5;
    const double eccentric_period = 2.0 * std::numbers::pi * std::sqrt(
        semimajor * semimajor * semimajor / (c * c * (k1 + k2))
    );
    auto eccentric = eccentric_pair(k1, k2, semimajor, eccentricity);
    const Drift eccentric_drift = run_drift(
        eccentric,
        eccentric_period / 8000.0,
        400'000
    );
    const double periapsis_error = relative_change(
        eccentric_drift.minimum_separation,
        semimajor * (1.0 - eccentricity)
    );
    const double apoapsis_error = relative_change(
        eccentric_drift.maximum_separation,
        semimajor * (1.0 + eccentricity)
    );
    add_le(
        checks,
        "N2a",
        "eccentric energy drift",
        eccentric_drift.advanced ? eccentric_drift.energy : 1.0,
        2.0e-5,
        "VALIDATED"
    );
    add_le(
        checks,
        "N2b",
        "eccentric angular drift",
        eccentric_drift.advanced ? eccentric_drift.angular_momentum : 1.0,
        2.0e-5,
        "VALIDATED"
    );
    add_le(
        checks,
        "N2c",
        "eccentric apsis error",
        std::max(periapsis_error, apoapsis_error),
        2.0e-4,
        "VALIDATED"
    );

    const auto circular_initial =
        sdt::dynamics::circular_pair(k1, k2, separation);
    const auto coarse = integrate(circular_initial, period / 500.0, 500);
    const auto fine = integrate(circular_initial, period / 1000.0, 1000);
    const double velocity_scale = sdt::dynamics::norm(
        circular_initial[0].velocity
    );
    const double coarse_error =
        state_error(coarse, circular_initial, separation, velocity_scale);
    const double fine_error =
        state_error(fine, circular_initial, separation, velocity_scale);
    add_ge(
        checks,
        "N3a",
        "Verlet convergence ratio",
        coarse_error / fine_error,
        3.5,
        "VALIDATED"
    );
    const auto verlet_cross =
        integrate(circular_initial, period / 2000.0, 2000);
    const auto rk4_cross =
        integrate(circular_initial, period / 2000.0, 2000, true);
    add_le(
        checks,
        "N3b",
        "Verlet RK4 cross-check",
        state_error(verlet_cross, rk4_cross, separation, velocity_scale),
        2.0e-4,
        "VALIDATED"
    );

    constexpr double triangle_side = 1.5e9;
    constexpr double tk1 = 2.5e-3;
    constexpr double tk2 = 2.5e-6;
    constexpr double tk3 = 2.5e-9;
    const double triangle_period = 2.0 * std::numbers::pi
        / (c * std::sqrt(
            (tk1 + tk2 + tk3)
            / (triangle_side * triangle_side * triangle_side)
        ));
    auto triangle =
        sdt::dynamics::equilateral_three(tk1, tk2, tk3, triangle_side);
    const Drift triangle_drift = run_drift(
        triangle,
        triangle_period / 4000.0,
        80'000,
        triangle_side
    );
    add_le(
        checks,
        "N4a",
        "triangle side drift",
        triangle_drift.advanced ? triangle_drift.separation : 1.0,
        1.0e-4,
        "VALIDATED"
    );
    add_le(
        checks,
        "N4b",
        "triangle barycentre drift",
        triangle_drift.advanced ? triangle_drift.barycentre : 1.0,
        1.0e-10,
        "VALIDATED"
    );

    constexpr double length_scale = 1.0e9;
    constexpr double figure_koppa = 1.0e-3;
    const double time_scale = std::sqrt(
        length_scale * length_scale * length_scale
        / (c * c * figure_koppa)
    );
    const double figure_velocity_scale = length_scale / time_scale;
    const double figure_period = 6.32591398 * time_scale;
    std::vector<Body> figure{
        {
            {-0.97000436 * length_scale, 0.24308753 * length_scale, 0.0},
            {
                0.466203685 * figure_velocity_scale,
                0.432365730 * figure_velocity_scale,
                0.0
            },
            figure_koppa,
            0.0
        },
        {
            {0.97000436 * length_scale, -0.24308753 * length_scale, 0.0},
            {
                0.466203685 * figure_velocity_scale,
                0.432365730 * figure_velocity_scale,
                0.0
            },
            figure_koppa,
            0.0
        },
        {
            {},
            {
                -0.932407370 * figure_velocity_scale,
                -0.864731460 * figure_velocity_scale,
                0.0
            },
            figure_koppa,
            0.0
        }
    };
    const auto figure_initial = figure;
    const Drift figure_drift = run_drift(
        figure,
        figure_period / 50000.0,
        50'000,
        length_scale
    );
    const double figure_error = state_error(
        figure,
        figure_initial,
        length_scale,
        figure_velocity_scale
    );
    add_le(
        checks,
        "N5",
        "figure-eight closure",
        figure_drift.advanced ? figure_error : 1.0,
        std::hypot(2.0e-5, 2.0e-5),
        "VALIDATED"
    );

    auto rotated_initial = figure_initial;
    for (auto& body : rotated_initial) {
        body.position = rotate_x(body.position, 0.713);
        body.velocity = rotate_x(body.velocity, 0.713);
    }
    const auto rotated = integrate(
        rotated_initial,
        figure_period / 50000.0,
        50'000
    );
    auto rotated_reference = figure;
    for (auto& body : rotated_reference) {
        body.position = rotate_x(body.position, 0.713);
        body.velocity = rotate_x(body.velocity, 0.713);
    }
    add_le(
        checks,
        "N6",
        "three-dimensional rotation invariance",
        state_error(
            rotated,
            rotated_reference,
            length_scale,
            figure_velocity_scale
        ),
        std::sqrt(2.0) * 1.0e-11,
        "VALIDATED"
    );

    constexpr double mu = 3.003e-6;
    const double hill = std::cbrt(mu / 3.0);
    const std::array<double, 3> roots{
        lagrange_root(1.0 - mu - hill, mu),
        lagrange_root(1.0 - mu + hill, mu),
        lagrange_root(-1.0 - mu + 7.0 * mu / 12.0, mu)
    };
    double root_residual = 0.0;
    for (const double root : roots) {
        root_residual =
            std::max(root_residual, std::abs(lagrange_function(root, mu)));
    }
    const Vec3 primary{-mu, 0.0, 0.0};
    const Vec3 secondary{1.0 - mu, 0.0, 0.0};
    const Vec3 l4{0.5 - mu, std::numbers::sqrt3 / 2.0, 0.0};
    const double geometry_error = std::max({
        std::abs(sdt::dynamics::norm(l4 - primary) - 1.0),
        std::abs(sdt::dynamics::norm(l4 - secondary) - 1.0),
        std::abs(std::atan2(l4.y, l4.x + mu) - std::numbers::pi / 3.0)
    });
    add_le(
        checks,
        "N7a",
        "Lagrange root residual",
        root_residual,
        1.0e-12,
        "VALIDATED"
    );
    add_le(
        checks,
        "N7b",
        "L4 L5 geometry",
        geometry_error,
        1.0e-10,
        "VALIDATED"
    );

    const double max_momentum = std::max({
        circular_drift.momentum,
        eccentric_drift.momentum,
        triangle_drift.momentum,
        figure_drift.momentum
    });
    const double max_angular = std::max({
        circular_drift.angular_momentum,
        eccentric_drift.angular_momentum,
        triangle_drift.angular_momentum,
        figure_drift.angular_momentum
    });
    add_le(
        checks,
        "N8a",
        "maximum momentum drift",
        max_momentum,
        1.0e-11,
        "VALIDATED"
    );
    add_le(
        checks,
        "N8b",
        "maximum angular drift",
        max_angular,
        1.0e-10,
        "VALIDATED"
    );

    std::vector<Body> collision{
        {{-1.0e6, 0.0, 0.0}, {1.0e4, 0.0, 0.0}, 1.0e-6, 1.0e5},
        {{ 1.0e6, 0.0, 0.0}, {-1.0e4, 0.0, 0.0}, 1.0e-6, 1.0e5}
    };
    StepStatus collision_status = StepStatus::advanced;
    for (int step = 0;
         step < 1000 && collision_status == StepStatus::advanced;
         ++step) {
        collision_status = sdt::dynamics::step(collision, 1.0);
    }
    const double margin =
        sdt::dynamics::norm(collision[1].position - collision[0].position)
        - collision[0].collision_radius_m
        - collision[1].collision_radius_m;
    add_ge(
        checks,
        "N9",
        "pre-overlap contact stop",
        collision_status == StepStatus::collision && margin > 0.0 ? margin : -1.0,
        0.0,
        "VALIDATED"
    );
}

void rigid_checks(std::vector<Check>& checks) {
    const multibody::Tolerances tolerances{
        1.0e-10,
        1.0e-10,
        1.0e-12,
        96
    };
    const Vec3 gravity{0.0, -9.80665, 0.0};

    auto [zero_links, zero_joints] =
        make_chain({0.7, 0.6, 0.5}, {0.4, -0.3, 0.2});
    const RigidRun zero = run_rigid(
        zero_links,
        zero_joints,
        {},
        0.001,
        10'000,
        tolerances
    );
    add_le(
        checks,
        "R0a",
        "zero-force position residual",
        zero.advanced ? zero.max_position : 1.0,
        1.0e-9,
        "CONDITIONAL"
    );
    add_le(
        checks,
        "R0b",
        "zero-force velocity residual",
        zero.advanced ? zero.max_velocity : 1.0,
        1.0e-9,
        "CONDITIONAL"
    );
    add_le(
        checks,
        "R0c",
        "zero-force quaternion residual",
        zero.advanced ? zero.max_quaternion : 1.0,
        1.0e-12,
        "CONDITIONAL"
    );

    auto [small_links, small_joints] = make_bob_pendulum(1.0, 0.05);
    const RigidRun small = run_rigid(
        small_links,
        small_joints,
        gravity,
        0.0005,
        14'000,
        tolerances
    );
    const double small_period = small.downward_crossings.size() >= 2
        ? small.downward_crossings[1] - small.downward_crossings[0]
        : 0.0;
    const double expected_small =
        2.0 * std::numbers::pi * std::sqrt(1.0 / 9.80665);
    add_le(
        checks,
        "R1",
        "small-angle period error",
        small.advanced && small_period > 0.0
            ? relative_change(small_period, expected_small)
            : 1.0,
        2.0e-3,
        "CONDITIONAL"
    );

    auto [finite_links, finite_joints] = make_bob_pendulum(1.0, 1.0);
    const RigidRun finite = run_rigid(
        finite_links,
        finite_joints,
        gravity,
        0.0005,
        16'000,
        tolerances
    );
    const double finite_period = finite.downward_crossings.size() >= 2
        ? finite.downward_crossings[1] - finite.downward_crossings[0]
        : 0.0;
    const double expected_finite = 4.0 * std::sqrt(1.0 / 9.80665)
        * elliptic_k(std::pow(std::sin(0.5), 2));
    add_le(
        checks,
        "R2a",
        "finite-amplitude period error",
        finite.advanced && finite_period > 0.0
            ? relative_change(finite_period, expected_finite)
            : 1.0,
        3.0e-3,
        "CONDITIONAL"
    );
    add_le(
        checks,
        "R2b",
        "finite-amplitude energy drift",
        finite.advanced ? finite.max_energy : 1.0,
        2.0e-3,
        "CONDITIONAL"
    );

    auto [double_links, double_joints] =
        make_chain({0.8, 0.7}, {0.7, -0.45});
    const RigidRun double_run = run_rigid(
        double_links,
        double_joints,
        gravity,
        0.0005,
        40'000,
        tolerances
    );
    add_le(
        checks,
        "R3a",
        "double-pendulum position residual",
        double_run.advanced ? double_run.max_position : 1.0,
        2.0e-8,
        "CONDITIONAL"
    );
    add_le(
        checks,
        "R3b",
        "double-pendulum velocity residual",
        double_run.advanced ? double_run.max_velocity : 1.0,
        2.0e-8,
        "CONDITIONAL"
    );
    add_le(
        checks,
        "R3c",
        "double-pendulum quaternion residual",
        double_run.advanced ? double_run.max_quaternion : 1.0,
        1.0e-12,
        "CONDITIONAL"
    );

    auto [sectioned_links, sectioned_joints] = make_chain(
        {0.4, 0.4, 0.4, 0.4, 0.4},
        {0.6, 0.3, 0.0, -0.3, -0.6}
    );
    const multibody::Tolerances sectioned_tolerances{
        1.0e-8,
        1.0e-8,
        1.0e-12,
        192
    };
    const RigidRun sectioned = run_rigid(
        sectioned_links,
        sectioned_joints,
        gravity,
        0.0005,
        20'000,
        sectioned_tolerances
    );
    add_le(
        checks,
        "R4a",
        "sectioned-chain position residual",
        sectioned.advanced ? sectioned.max_position : 1.0,
        2.0e-8,
        "CONDITIONAL"
    );
    add_le(
        checks,
        "R4b",
        "sectioned-chain velocity residual",
        sectioned.advanced ? sectioned.max_velocity : 1.0,
        2.0e-8,
        "CONDITIONAL"
    );

    const auto convergence_angle = [&](double dt) {
        auto [links, joints] = make_bob_pendulum(1.0, 0.05);
        const auto run = run_rigid(
            links,
            joints,
            gravity,
            dt,
            static_cast<std::uint64_t>(std::llround(1.0 / dt)),
            tolerances
        );
        return run.advanced ? run.final_angle
            : std::numeric_limits<double>::quiet_NaN();
    };
    const double coarse_angle = convergence_angle(0.002);
    const double fine_angle = convergence_angle(0.001);
    const double reference_angle = convergence_angle(0.00025);
    const double convergence_ratio =
        std::abs(coarse_angle - reference_angle)
        / std::abs(fine_angle - reference_angle);
    add_ge(
        checks,
        "R5",
        "pendulum timestep convergence",
        convergence_ratio,
        1.8,
        "CONDITIONAL"
    );

    auto [bad_links, bad_joints] = make_chain({1.0}, {0.2});
    bad_links[0].inertia_diagonal_kg_m2.z = 0.0;
    std::string validation_error;
    const bool rejected =
        !multibody::validate_chain(bad_links, bad_joints, validation_error)
        && !validation_error.empty();
    add_ge(
        checks,
        "R6",
        "malformed chain rejection",
        rejected ? 1.0 : 0.0,
        1.0,
        "CONDITIONAL"
    );
}

} // namespace

auto self_test_json() -> std::string {
    std::vector<Check> checks;
    contract_checks(checks);
    nbody_checks(checks);
    rigid_checks(checks);

    bool all_passed = true;
    bool nbody_passed = true;
    bool rigid_passed = true;
    Array gates;
    for (const Check& check : checks) {
        all_passed = all_passed && check.passed;
        if (!check.id.empty() && check.id[0] == 'N') {
            nbody_passed = nbody_passed && check.passed;
        }
        if (!check.id.empty() && check.id[0] == 'R') {
            rigid_passed = rigid_passed && check.passed;
        }
        gates.emplace_back(Object{
            {"classification", check.classification},
            {"id", check.id},
            {"limit", check.limit},
            {"name", check.name},
            {"passed", check.passed},
            {"relation", check.relation},
            {"value", check.value}
        });
    }
    const Value celestial_result = json::parse(celestial::self_test_json());
    const bool celestial_passed =
        celestial_result.object().at("status").string() == "passed";
    all_passed = all_passed && celestial_passed;
    const Value occlusion_nbody_result =
        json::parse(occlusion_nbody::self_test_json());
    const bool occlusion_nbody_passed =
        occlusion_nbody_result.object().at("status").string() == "passed";
    all_passed = all_passed && occlusion_nbody_passed;
    return json::canonical(Object{
        {"contract_version", contract_version},
        {"gates", std::move(gates)},
        {"manifest", json::parse(manifest_json())},
        {
            "physics_status",
            Object{
                {
                    "articulated_rigid",
                    rigid_passed ? "CONDITIONAL" : "NOT-QUALIFIED"
                },
                {
                    "point_nbody",
                    nbody_passed ? "VALIDATED" : "NOT-QUALIFIED"
                },
                {
                    "celestial_three_body",
                    celestial_passed ? "COMPUTED" : "NOT-QUALIFIED"
                },
                {
                    "sdt_occlusion_nbody",
                    occlusion_nbody_passed ? "COMPUTED" : "NOT-QUALIFIED"
                }
            }
        },
        {"celestial", celestial_result},
        {"occlusion_nbody", occlusion_nbody_result},
        {"status", all_passed ? "passed" : "failed"}
    });
}

} // namespace sdt_solver
