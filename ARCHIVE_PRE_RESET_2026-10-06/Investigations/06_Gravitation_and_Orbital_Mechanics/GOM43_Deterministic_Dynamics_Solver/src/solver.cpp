#include <sdt_solver/celestial.hpp>
#include <sdt_solver/json.hpp>
#include <sdt_solver/multibody.hpp>
#include <sdt_solver/occlusion_nbody.hpp>
#include <sdt_solver/solver.hpp>

#include <sdt/compiler/sha256.hpp>
#include <sdt/dynamics.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#ifndef SDT_LAWS_SHA256
#define SDT_LAWS_SHA256 \
    "0000000000000000000000000000000000000000000000000000000000000000"
#endif

#ifndef SDT_SOLVER_COMPILER
#define SDT_SOLVER_COMPILER "unconfigured-c++20"
#endif

namespace sdt_solver {
namespace {

using json::Array;
using json::Object;
using json::Value;
using multibody::Quaternion;
using sdt::dynamics::Body;
using sdt::dynamics::Invariants;
using sdt::dynamics::StepStatus;
using sdt::dynamics::Vec3;

struct Gate {
    std::string id;
    std::string metric;
    std::string relation;
    double limit{};
};

struct Case {
    std::string case_id;
    std::string problem_class;
    std::string integrator;
    double timestep_s{};
    double duration_s{};
    std::uint64_t steps{};
    std::uint64_t record_every_steps{};
    multibody::Tolerances tolerances{};
    Vec3 uniform_acceleration_m_s2{};
    bool has_koppa_force{};
    std::vector<std::string> body_ids;
    std::vector<Body> bodies;
    std::vector<multibody::RigidLink> links;
    std::vector<multibody::RevoluteJoint> joints;
    std::vector<Gate> gates;
    Value normalized;
};

struct Diagnostics {
    double relative_energy_drift{};
    double momentum_drift{};
    double angular_momentum_drift{};
    double max_position_constraint_m{};
    double max_velocity_constraint_m_s{};
    double max_quaternion_norm_error{};
};

struct Event {
    std::uint64_t step{};
    double time_s{};
    std::string type;
    std::string detail;
};

struct RunResult {
    std::string status{"completed"};
    std::string classification{"NOT-EXECUTED"};
    std::string message;
    std::uint64_t executed_steps{};
    Diagnostics diagnostics{};
    std::vector<Event> events;
    Array trajectory;
};

[[nodiscard]] auto object_at(
    const Object& object,
    const std::string& key
) -> const Value& {
    const auto iterator = object.find(key);
    if (iterator == object.end()) {
        throw std::runtime_error("missing required member '" + key + "'");
    }
    return iterator->second;
}

void require_object(const Value& value, const std::string& context) {
    if (!value.is_object()) throw std::runtime_error(context + " must be an object");
}

void require_array(const Value& value, const std::string& context) {
    if (!value.is_array()) throw std::runtime_error(context + " must be an array");
}

[[nodiscard]] auto require_string(
    const Value& value,
    const std::string& context
) -> const std::string& {
    if (!value.is_string()) throw std::runtime_error(context + " must be a string");
    return value.string();
}

[[nodiscard]] auto require_number(
    const Value& value,
    const std::string& context
) -> double {
    if (!value.is_number() || !std::isfinite(value.number())) {
        throw std::runtime_error(context + " must be a finite number");
    }
    return value.number();
}

[[nodiscard]] auto require_positive(
    const Value& value,
    const std::string& context
) -> double {
    const double result = require_number(value, context);
    if (result <= 0.0) throw std::runtime_error(context + " must be positive");
    return result;
}

[[nodiscard]] auto require_nonnegative(
    const Value& value,
    const std::string& context
) -> double {
    const double result = require_number(value, context);
    if (result < 0.0) throw std::runtime_error(context + " must be non-negative");
    return result;
}

[[nodiscard]] auto require_integer(
    const Value& value,
    const std::string& context,
    std::uint64_t minimum,
    std::uint64_t maximum
) -> std::uint64_t {
    const double number = require_number(value, context);
    if (number < static_cast<double>(minimum)
        || number > static_cast<double>(maximum)
        || std::floor(number) != number) {
        throw std::runtime_error(context + " must be an integer in range");
    }
    return static_cast<std::uint64_t>(number);
}

void require_keys(
    const Object& object,
    std::initializer_list<const char*> allowed,
    const std::string& context
) {
    std::set<std::string> names;
    for (const char* name : allowed) names.emplace(name);
    for (const auto& [name, value] : object) {
        static_cast<void>(value);
        if (!names.contains(name)) {
            throw std::runtime_error(
                context + " has unknown member '" + name + "'"
            );
        }
    }
}

[[nodiscard]] auto vec3_from(
    const Value& value,
    const std::string& context
) -> Vec3 {
    require_array(value, context);
    if (value.array().size() != 3) {
        throw std::runtime_error(context + " must have three components");
    }
    return {
        require_number(value.array()[0], context + "[0]"),
        require_number(value.array()[1], context + "[1]"),
        require_number(value.array()[2], context + "[2]")
    };
}

[[nodiscard]] auto quaternion_from(
    const Value& value,
    const std::string& context
) -> Quaternion {
    require_array(value, context);
    if (value.array().size() != 4) {
        throw std::runtime_error(context + " must have four components");
    }
    Quaternion result{
        require_number(value.array()[0], context + "[0]"),
        require_number(value.array()[1], context + "[1]"),
        require_number(value.array()[2], context + "[2]"),
        require_number(value.array()[3], context + "[3]")
    };
    const double magnitude = std::sqrt(multibody::norm_squared(result));
    if (!std::isfinite(magnitude) || std::abs(magnitude - 1.0) > 1.0e-10) {
        throw std::runtime_error(context + " must be unit length");
    }
    return multibody::normalized(result);
}

[[nodiscard]] auto json_vec3(Vec3 value) -> Value {
    return Array{value.x, value.y, value.z};
}

[[nodiscard]] auto json_quaternion(Quaternion value) -> Value {
    return Array{value.w, value.x, value.y, value.z};
}

[[nodiscard]] auto parse_case(const std::string& input) -> Case {
    Case result;
    result.normalized = json::parse(input);
    require_object(result.normalized, "case");
    const Object& root = result.normalized.object();
    require_keys(
        root,
        {
            "contract_version", "case_id", "problem_class", "frame", "forces",
            "bodies", "links", "joints", "integrator", "timestep_s",
            "duration_s", "record_every_steps", "tolerances", "gates"
        },
        "case"
    );

    if (require_string(object_at(root, "contract_version"), "contract_version")
        != contract_version) {
        throw std::runtime_error("unsupported contract_version");
    }
    result.case_id = require_string(object_at(root, "case_id"), "case_id");
    if (result.case_id.empty() || result.case_id.size() > 96) {
        throw std::runtime_error("case_id length is outside contract");
    }
    for (const char ch : result.case_id) {
        const bool permitted =
            (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
            || (ch >= '0' && ch <= '9') || ch == '.' || ch == '_'
            || ch == '-';
        if (!permitted) throw std::runtime_error("case_id has invalid character");
    }

    result.problem_class =
        require_string(object_at(root, "problem_class"), "problem_class");
    if (result.problem_class != "point_nbody"
        && result.problem_class != "articulated_rigid") {
        throw std::runtime_error("unsupported problem_class");
    }

    require_object(object_at(root, "frame"), "frame");
    const Object& frame = object_at(root, "frame").object();
    require_keys(frame, {"type", "units"}, "frame");
    if (require_string(object_at(frame, "type"), "frame.type")
            != "inertial_cartesian"
        || require_string(object_at(frame, "units"), "frame.units") != "SI") {
        throw std::runtime_error("only inertial_cartesian SI frames are supported");
    }

    result.integrator =
        require_string(object_at(root, "integrator"), "integrator");
    result.timestep_s =
        require_positive(object_at(root, "timestep_s"), "timestep_s");
    result.duration_s =
        require_positive(object_at(root, "duration_s"), "duration_s");
    const double step_count = result.duration_s / result.timestep_s;
    const double rounded_steps = std::round(step_count);
    if (rounded_steps < 1.0 || rounded_steps > 10'000'000.0
        || std::abs(step_count - rounded_steps)
            > 1.0e-10 * std::max(1.0, step_count)) {
        throw std::runtime_error(
            "duration_s/timestep_s must be an integer no greater than 10000000"
        );
    }
    result.steps = static_cast<std::uint64_t>(rounded_steps);
    result.record_every_steps = require_integer(
        object_at(root, "record_every_steps"),
        "record_every_steps",
        1,
        result.steps
    );

    require_object(object_at(root, "tolerances"), "tolerances");
    const Object& tolerances = object_at(root, "tolerances").object();
    require_keys(
        tolerances,
        {
            "position_m", "velocity_m_s", "quaternion_norm",
            "max_constraint_iterations"
        },
        "tolerances"
    );
    result.tolerances.position_m =
        require_positive(object_at(tolerances, "position_m"), "position_m");
    result.tolerances.velocity_m_s =
        require_positive(object_at(tolerances, "velocity_m_s"), "velocity_m_s");
    result.tolerances.quaternion_norm = require_positive(
        object_at(tolerances, "quaternion_norm"),
        "quaternion_norm"
    );
    result.tolerances.max_constraint_iterations = static_cast<int>(
        require_integer(
            object_at(tolerances, "max_constraint_iterations"),
            "max_constraint_iterations",
            1,
            256
        )
    );

    require_array(object_at(root, "forces"), "forces");
    if (object_at(root, "forces").array().empty()) {
        throw std::runtime_error("forces must not be empty");
    }
    bool has_uniform = false;
    for (const Value& force_value : object_at(root, "forces").array()) {
        require_object(force_value, "force");
        const Object& force = force_value.object();
        const std::string type =
            require_string(object_at(force, "type"), "force.type");
        if (type == "koppa_pairwise") {
            require_keys(force, {"type"}, "koppa_pairwise force");
            if (result.has_koppa_force) {
                throw std::runtime_error("duplicate koppa_pairwise force");
            }
            result.has_koppa_force = true;
        } else if (type == "uniform_acceleration") {
            require_keys(
                force,
                {"type", "acceleration_m_s2", "provenance"},
                "uniform_acceleration force"
            );
            if (has_uniform) {
                throw std::runtime_error("duplicate uniform_acceleration force");
            }
            has_uniform = true;
            result.uniform_acceleration_m_s2 = vec3_from(
                object_at(force, "acceleration_m_s2"),
                "force.acceleration_m_s2"
            );
            require_object(object_at(force, "provenance"), "force.provenance");
            const Object& provenance = object_at(force, "provenance").object();
            require_keys(
                provenance,
                {
                    "classification", "description", "v_surface_m_s", "radius_m"
                },
                "force.provenance"
            );
            const std::string classification = require_string(
                object_at(provenance, "classification"),
                "force.provenance.classification"
            );
            if (classification != "MEASURED-INPUT"
                && classification != "DERIVED"
                && classification != "COMPUTED"
                && classification != "CONDITIONAL") {
                throw std::runtime_error(
                    "force provenance classification is unsupported"
                );
            }
            if (require_string(
                    object_at(provenance, "description"),
                    "force.provenance.description"
                ).empty()) {
                throw std::runtime_error("force provenance description is empty");
            }
            const bool has_v = provenance.contains("v_surface_m_s");
            const bool has_r = provenance.contains("radius_m");
            if (has_v != has_r) {
                throw std::runtime_error(
                    "v_surface_m_s and radius_m must be supplied together"
                );
            }
            if (has_v) {
                static_cast<void>(require_positive(
                    provenance.at("v_surface_m_s"),
                    "v_surface_m_s"
                ));
                static_cast<void>(require_positive(
                    provenance.at("radius_m"),
                    "radius_m"
                ));
            }
        } else {
            throw std::runtime_error("unsupported force provider");
        }
    }

    if (result.problem_class == "point_nbody") {
        if (result.integrator != "velocity_verlet"
            && result.integrator != "fixed_rk4") {
            throw std::runtime_error("point_nbody requires a point integrator");
        }
        if (!result.has_koppa_force || has_uniform) {
            throw std::runtime_error(
                "point_nbody v1 requires exactly koppa_pairwise force"
            );
        }
        if (root.contains("links") || root.contains("joints")) {
            throw std::runtime_error("point_nbody cannot contain links or joints");
        }
        require_array(object_at(root, "bodies"), "bodies");
        std::set<std::string> ids;
        for (const Value& body_value : object_at(root, "bodies").array()) {
            require_object(body_value, "body");
            const Object& body = body_value.object();
            require_keys(
                body,
                {
                    "id", "position_m", "velocity_m_s", "koppa_m",
                    "collision_radius_m"
                },
                "body"
            );
            const std::string id = require_string(object_at(body, "id"), "body.id");
            if (id.empty() || !ids.emplace(id).second) {
                throw std::runtime_error("body IDs must be non-empty and unique");
            }
            result.body_ids.push_back(id);
            result.bodies.push_back({
                vec3_from(object_at(body, "position_m"), "body.position_m"),
                vec3_from(object_at(body, "velocity_m_s"), "body.velocity_m_s"),
                require_positive(object_at(body, "koppa_m"), "body.koppa_m"),
                require_nonnegative(
                    object_at(body, "collision_radius_m"),
                    "body.collision_radius_m"
                )
            });
        }
        if (result.bodies.empty()) {
            throw std::runtime_error("bodies must not be empty");
        }
    } else {
        if (result.integrator != "rattle") {
            throw std::runtime_error("articulated_rigid requires rattle");
        }
        if (result.has_koppa_force || !has_uniform) {
            throw std::runtime_error(
                "articulated_rigid v1 requires one uniform_acceleration force"
            );
        }
        if (root.contains("bodies")) {
            throw std::runtime_error("articulated_rigid cannot contain bodies");
        }
        require_array(object_at(root, "links"), "links");
        std::map<std::string, std::size_t> indices;
        for (const Value& link_value : object_at(root, "links").array()) {
            require_object(link_value, "link");
            const Object& link = link_value.object();
            require_keys(
                link,
                {
                    "id", "position_m", "quaternion_wxyz", "velocity_m_s",
                    "angular_velocity_rad_s", "inertial_mass_kg",
                    "inertia_diagonal_kg_m2", "length_m", "koppa_m"
                },
                "link"
            );
            const std::string id = require_string(object_at(link, "id"), "link.id");
            if (id.empty() || indices.contains(id)) {
                throw std::runtime_error("link IDs must be non-empty and unique");
            }
            indices[id] = result.links.size();
            const Vec3 inertia = vec3_from(
                object_at(link, "inertia_diagonal_kg_m2"),
                "link.inertia_diagonal_kg_m2"
            );
            if (inertia.x <= 0.0 || inertia.y <= 0.0 || inertia.z <= 0.0) {
                throw std::runtime_error("link inertia components must be positive");
            }
            result.links.push_back({
                id,
                vec3_from(object_at(link, "position_m"), "link.position_m"),
                quaternion_from(
                    object_at(link, "quaternion_wxyz"),
                    "link.quaternion_wxyz"
                ),
                vec3_from(object_at(link, "velocity_m_s"), "link.velocity_m_s"),
                vec3_from(
                    object_at(link, "angular_velocity_rad_s"),
                    "link.angular_velocity_rad_s"
                ),
                require_positive(
                    object_at(link, "inertial_mass_kg"),
                    "link.inertial_mass_kg"
                ),
                inertia,
                require_positive(object_at(link, "length_m"), "link.length_m"),
                link.contains("koppa_m")
                    ? require_positive(link.at("koppa_m"), "link.koppa_m")
                    : 0.0
            });
        }

        require_array(object_at(root, "joints"), "joints");
        std::set<std::string> joint_ids;
        for (const Value& joint_value : object_at(root, "joints").array()) {
            require_object(joint_value, "joint");
            const Object& joint = joint_value.object();
            require_keys(
                joint,
                {
                    "id", "parent", "child", "parent_anchor_m",
                    "child_anchor_m", "axis_world"
                },
                "joint"
            );
            const std::string id =
                require_string(object_at(joint, "id"), "joint.id");
            if (id.empty() || !joint_ids.emplace(id).second) {
                throw std::runtime_error("joint IDs must be non-empty and unique");
            }
            const Value& parent_value = object_at(joint, "parent");
            int parent = -1;
            if (!parent_value.is_null()) {
                const std::string parent_id =
                    require_string(parent_value, "joint.parent");
                const auto iterator = indices.find(parent_id);
                if (iterator == indices.end()) {
                    throw std::runtime_error("joint parent ID is unknown");
                }
                parent = static_cast<int>(iterator->second);
            }
            const std::string child_id =
                require_string(object_at(joint, "child"), "joint.child");
            const auto child_iterator = indices.find(child_id);
            if (child_iterator == indices.end()) {
                throw std::runtime_error("joint child ID is unknown");
            }
            result.joints.push_back({
                id,
                parent,
                child_iterator->second,
                vec3_from(
                    object_at(joint, "parent_anchor_m"),
                    "joint.parent_anchor_m"
                ),
                vec3_from(
                    object_at(joint, "child_anchor_m"),
                    "joint.child_anchor_m"
                ),
                vec3_from(object_at(joint, "axis_world"), "joint.axis_world")
            });
        }
        std::string chain_error;
        if (!multibody::validate_chain(result.links, result.joints, chain_error)) {
            throw std::runtime_error(chain_error);
        }
        double position_residual = 0.0;
        double velocity_residual = 0.0;
        for (const auto& joint : result.joints) {
            position_residual = std::max(
                position_residual,
                sdt::dynamics::norm(
                    multibody::anchor_position(result.links, joint, false)
                    - multibody::anchor_position(result.links, joint, true)
                )
            );
            velocity_residual = std::max(
                velocity_residual,
                sdt::dynamics::norm(
                    multibody::anchor_velocity(result.links, joint, false)
                    - multibody::anchor_velocity(result.links, joint, true)
                )
            );
        }
        if (position_residual > result.tolerances.position_m) {
            throw std::runtime_error(
                "initial articulated state is outside constraint tolerance"
            );
        }
        if (velocity_residual > result.tolerances.velocity_m_s) {
            throw std::runtime_error(
                "initial articulated velocity is outside constraint tolerance"
            );
        }
    }

    require_array(object_at(root, "gates"), "gates");
    std::set<std::string> gate_ids;
    for (const Value& gate_value : object_at(root, "gates").array()) {
        require_object(gate_value, "gate");
        const Object& gate = gate_value.object();
        require_keys(gate, {"id", "metric", "relation", "limit"}, "gate");
        Gate parsed{
            require_string(object_at(gate, "id"), "gate.id"),
            require_string(object_at(gate, "metric"), "gate.metric"),
            require_string(object_at(gate, "relation"), "gate.relation"),
            require_number(object_at(gate, "limit"), "gate.limit")
        };
        if (parsed.id.empty() || !gate_ids.emplace(parsed.id).second) {
            throw std::runtime_error("gate IDs must be non-empty and unique");
        }
        if (parsed.relation != "<=" && parsed.relation != ">=") {
            throw std::runtime_error("gate relation must be <= or >=");
        }
        static const std::set<std::string> metrics{
            "relative_energy_drift",
            "momentum_drift",
            "angular_momentum_drift",
            "max_position_constraint_m",
            "max_velocity_constraint_m_s",
            "max_quaternion_norm_error"
        };
        if (!metrics.contains(parsed.metric)) {
            throw std::runtime_error("gate metric is unsupported");
        }
        result.gates.push_back(std::move(parsed));
    }
    return result;
}

[[nodiscard]] auto relative_change(double value, double reference) noexcept
    -> double {
    return reference == 0.0
        ? std::abs(value)
        : std::abs(value / reference - 1.0);
}

[[nodiscard]] auto point_frame(
    std::uint64_t step,
    double time_s,
    const std::vector<std::string>& ids,
    const std::vector<Body>& bodies
) -> Value {
    Array states;
    states.reserve(bodies.size());
    for (std::size_t i = 0; i < bodies.size(); ++i) {
        states.emplace_back(Object{
            {"id", ids[i]},
            {"position_m", json_vec3(bodies[i].position)},
            {"velocity_m_s", json_vec3(bodies[i].velocity)}
        });
    }
    return Object{
        {"states", std::move(states)},
        {"step", static_cast<double>(step)},
        {"time_s", time_s}
    };
}

[[nodiscard]] auto rigid_frame(
    std::uint64_t step,
    double time_s,
    const std::vector<multibody::RigidLink>& links
) -> Value {
    Array states;
    states.reserve(links.size());
    for (const auto& link : links) {
        states.emplace_back(Object{
            {"angular_velocity_rad_s", json_vec3(link.angular_velocity_rad_s)},
            {"id", link.id},
            {"position_m", json_vec3(link.position_m)},
            {"quaternion_wxyz", json_quaternion(link.orientation)},
            {"velocity_m_s", json_vec3(link.velocity_m_s)}
        });
    }
    return Object{
        {"states", std::move(states)},
        {"step", static_cast<double>(step)},
        {"time_s", time_s}
    };
}

[[nodiscard]] auto run_point_case(const Case& definition) -> RunResult {
    RunResult result;
    result.classification = "VALIDATED";
    auto bodies = definition.bodies;
    const Invariants initial = sdt::dynamics::invariants(bodies);
    double momentum_scale = 0.0;
    double angular_scale = 0.0;
    for (const auto& body : bodies) {
        momentum_scale += body.koppa_m * sdt::dynamics::norm(body.velocity);
        angular_scale += body.koppa_m * sdt::dynamics::norm(
            sdt::dynamics::cross(body.position, body.velocity)
        );
    }
    momentum_scale = std::max(momentum_scale, 1.0);
    angular_scale = std::max(angular_scale, 1.0);
    result.trajectory.push_back(
        point_frame(0, 0.0, definition.body_ids, bodies)
    );
    for (std::uint64_t step = 1; step <= definition.steps; ++step) {
        const StepStatus status = definition.integrator == "velocity_verlet"
            ? sdt::dynamics::step(bodies, definition.timestep_s)
            : sdt::dynamics::step_rk4(bodies, definition.timestep_s);
        if (status != StepStatus::advanced) {
            result.status = status == StepStatus::collision
                ? "collision"
                : "numerical_failure";
            result.message = status == StepStatus::collision
                ? "contact boundary reached before overlap"
                : "point-body state became invalid";
            result.events.push_back({
                step - 1,
                static_cast<double>(step - 1) * definition.timestep_s,
                result.status,
                result.message
            });
            break;
        }
        result.executed_steps = step;
        const Invariants current = sdt::dynamics::invariants(bodies);
        result.diagnostics.relative_energy_drift = std::max(
            result.diagnostics.relative_energy_drift,
            relative_change(current.energy, initial.energy)
        );
        result.diagnostics.momentum_drift = std::max(
            result.diagnostics.momentum_drift,
            sdt::dynamics::norm(current.momentum - initial.momentum)
                / momentum_scale
        );
        result.diagnostics.angular_momentum_drift = std::max(
            result.diagnostics.angular_momentum_drift,
            sdt::dynamics::norm(
                current.angular_momentum - initial.angular_momentum
            ) / angular_scale
        );
        if (step % definition.record_every_steps == 0
            || step == definition.steps) {
            result.trajectory.push_back(point_frame(
                step,
                static_cast<double>(step) * definition.timestep_s,
                definition.body_ids,
                bodies
            ));
        }
    }
    if (result.status == "completed") {
        result.message = "fixed-step point-body run completed";
    }
    return result;
}

[[nodiscard]] auto run_rigid_case(const Case& definition) -> RunResult {
    RunResult result;
    result.classification = "CONDITIONAL";
    auto links = definition.links;
    const double initial_energy = multibody::mechanical_energy(
        links,
        definition.uniform_acceleration_m_s2
    );
    result.trajectory.push_back(rigid_frame(0, 0.0, links));
    for (std::uint64_t step = 1; step <= definition.steps; ++step) {
        multibody::Residuals residuals{};
        const auto status = multibody::step(
            links,
            definition.joints,
            definition.uniform_acceleration_m_s2,
            definition.timestep_s,
            definition.tolerances,
            residuals
        );
        result.diagnostics.max_position_constraint_m = std::max(
            result.diagnostics.max_position_constraint_m,
            residuals.position_m
        );
        result.diagnostics.max_velocity_constraint_m_s = std::max(
            result.diagnostics.max_velocity_constraint_m_s,
            residuals.velocity_m_s
        );
        result.diagnostics.max_quaternion_norm_error = std::max(
            result.diagnostics.max_quaternion_norm_error,
            residuals.quaternion_norm
        );
        if (status != multibody::StepStatus::advanced) {
            result.status = status == multibody::StepStatus::constraint_failure
                ? "constraint_failure"
                : "numerical_failure";
            result.message = status == multibody::StepStatus::constraint_failure
                ? "constraint projection exceeded its registered iteration budget"
                : "rigid-body state became invalid";
            result.events.push_back({
                step - 1,
                static_cast<double>(step - 1) * definition.timestep_s,
                result.status,
                result.message
            });
            break;
        }
        result.executed_steps = step;
        result.diagnostics.relative_energy_drift = std::max(
            result.diagnostics.relative_energy_drift,
            relative_change(
                multibody::mechanical_energy(
                    links,
                    definition.uniform_acceleration_m_s2
                ),
                initial_energy
            )
        );
        if (step % definition.record_every_steps == 0
            || step == definition.steps) {
            result.trajectory.push_back(rigid_frame(
                step,
                static_cast<double>(step) * definition.timestep_s,
                links
            ));
        }
    }
    if (result.status == "completed") {
        result.message =
            "fixed-step constrained rigid-body run completed under declared "
            "local acceleration";
    }
    return result;
}

[[nodiscard]] auto diagnostic_value(
    const Diagnostics& diagnostics,
    const std::string& metric
) -> double {
    if (metric == "relative_energy_drift") {
        return diagnostics.relative_energy_drift;
    }
    if (metric == "momentum_drift") return diagnostics.momentum_drift;
    if (metric == "angular_momentum_drift") {
        return diagnostics.angular_momentum_drift;
    }
    if (metric == "max_position_constraint_m") {
        return diagnostics.max_position_constraint_m;
    }
    if (metric == "max_velocity_constraint_m_s") {
        return diagnostics.max_velocity_constraint_m_s;
    }
    return diagnostics.max_quaternion_norm_error;
}

[[nodiscard]] auto diagnostics_json(const Diagnostics& diagnostics) -> Value {
    return Object{
        {"angular_momentum_drift", diagnostics.angular_momentum_drift},
        {"max_position_constraint_m", diagnostics.max_position_constraint_m},
        {"max_quaternion_norm_error", diagnostics.max_quaternion_norm_error},
        {
            "max_velocity_constraint_m_s",
            diagnostics.max_velocity_constraint_m_s
        },
        {"momentum_drift", diagnostics.momentum_drift},
        {"relative_energy_drift", diagnostics.relative_energy_drift}
    };
}

[[nodiscard]] auto invalid_result(
    const std::string& message,
    const std::string& case_id = "",
    const std::string& problem_class = "unknown"
) -> std::string {
    const Value empty_case = Object{};
    const std::string normalized = json::canonical(empty_case);
    const std::string empty_trajectory = "[]";
    return json::canonical(Object{
        {"case_id", case_id},
        {"classification", "NOT-EXECUTED"},
        {"contract_version", contract_version},
        {"diagnostics", diagnostics_json({})},
        {"events", Array{}},
        {"executed_steps", 0.0},
        {"gates", Array{}},
        {"message", message},
        {"normalized_case", empty_case},
        {"problem_class", problem_class},
        {
            "provenance",
            Object{
                {
                    "input_sha256",
                    sdt::compiler::SHA256::hash(normalized)
                },
                {"laws_sha256", SDT_LAWS_SHA256}
            }
        },
        {
            "solver",
            Object{
                {"build_id", build_id},
                {"compiler", SDT_SOLVER_COMPILER},
                {
                    "floating_point_policy",
                    "fixed-step; no fast-math; no contraction guarantee"
                }
            }
        },
        {"status", "invalid_case"},
        {"trajectory", Array{}},
        {
            "trajectory_sha256",
            sdt::compiler::SHA256::hash(empty_trajectory)
        }
    });
}

} // namespace

auto run_case_json(const std::string& case_json) -> std::string {
    try {
        const Value candidate = json::parse(case_json);
        if (candidate.is_object()
            && candidate.object().contains("contract_version")
            && candidate.object().at("contract_version").is_string()
            && (
                candidate.object().at("contract_version").string()
                    == celestial::contract_version
                || candidate.object().at("contract_version").string()
                    == celestial::displacement_contract_version
            )) {
            return celestial::run_case_json(case_json);
        }
        if (candidate.is_object()
            && candidate.object().contains("contract_version")
            && candidate.object().at("contract_version").is_string()
            && candidate.object().at("contract_version").string()
                == occlusion_nbody::contract_version) {
            return occlusion_nbody::run_case_json(case_json);
        }
        const Case definition = parse_case(case_json);
        RunResult run = definition.problem_class == "point_nbody"
            ? run_point_case(definition)
            : run_rigid_case(definition);
        Array gates;
        for (const Gate& gate : definition.gates) {
            const double value =
                diagnostic_value(run.diagnostics, gate.metric);
            const bool passed = gate.relation == "<="
                ? value <= gate.limit
                : value >= gate.limit;
            gates.emplace_back(Object{
                {"id", gate.id},
                {"limit", gate.limit},
                {"metric", gate.metric},
                {"passed", passed},
                {"relation", gate.relation},
                {"value", value}
            });
        }
        Array events;
        for (const Event& event : run.events) {
            events.emplace_back(Object{
                {"detail", event.detail},
                {"step", static_cast<double>(event.step)},
                {"time_s", event.time_s},
                {"type", event.type}
            });
        }
        const std::string normalized_case =
            json::canonical(definition.normalized);
        const std::string trajectory = json::canonical(run.trajectory);
        return json::canonical(Object{
            {"case_id", definition.case_id},
            {"classification", run.classification},
            {"contract_version", contract_version},
            {"diagnostics", diagnostics_json(run.diagnostics)},
            {"events", std::move(events)},
            {"executed_steps", static_cast<double>(run.executed_steps)},
            {"gates", std::move(gates)},
            {"message", run.message},
            {"normalized_case", definition.normalized},
            {"problem_class", definition.problem_class},
            {
                "provenance",
                Object{
                    {
                        "input_sha256",
                        sdt::compiler::SHA256::hash(normalized_case)
                    },
                    {"laws_sha256", SDT_LAWS_SHA256}
                }
            },
            {
                "solver",
                Object{
                    {"build_id", build_id},
                    {"compiler", SDT_SOLVER_COMPILER},
                    {
                        "floating_point_policy",
                        "fixed-step; no fast-math; no contraction guarantee"
                    }
                }
            },
            {"status", run.status},
            {"trajectory", std::move(run.trajectory)},
            {
                "trajectory_sha256",
                sdt::compiler::SHA256::hash(trajectory)
            }
        });
    } catch (const std::exception& error) {
        return invalid_result(error.what());
    }
}

auto manifest_json() -> std::string {
    return json::canonical(Object{
        {"build_id", build_id},
        {
            "c_abi",
            Array{
                "run_case", "session_create", "session_advance",
                "session_checkpoint", "session_resume", "session_destroy",
                "self_test", "solver_manifest", "solver_free"
            }
        },
        {"compiler", SDT_SOLVER_COMPILER},
        {"contract_version", contract_version},
        {"celestial_contract", celestial::contract_version},
        {"celestial_manifest", json::parse(celestial::manifest_json())},
        {"occlusion_nbody_contract", occlusion_nbody::contract_version},
        {
            "occlusion_nbody_manifest",
            json::parse(occlusion_nbody::manifest_json())
        },
        {
            "floating_point_policy",
            "fixed-step; no fast-math; no contraction guarantee"
        },
        {"laws_sha256", SDT_LAWS_SHA256},
        {
            "physics",
            Object{
                {
                    "articulated_rigid",
                    "CONDITIONAL: open-chain coplanar revolute links under "
                    "declared local uniform acceleration"
                },
                {
                    "not_implemented",
                    Array{
                        "adaptive stepping",
                        "closed loops",
                        "contact response",
                        "flexible beams",
                        "friction",
                        "general spatial hinge networks",
                        "flexible shadow media outside the registered "
                        "seven-cone celestial route"
                    }
                },
                {
                    "point_nbody",
                    "VALIDATED: sdt::dynamics koppa pairwise kernel"
                },
                {
                    "celestial_three_body",
                    "COMPUTED: retarded seven-cone pressure route with "
                    "Law-IV baryon resistance"
                },
                {
                    "sdt_occlusion_nbody",
                    "COMPUTED: arbitrary-N full 7x7 retarded solid-angle "
                    "occlusion with Law-IV and Law-V response"
                }
            }
        },
        {
            "wasm",
#if defined(__EMSCRIPTEN__)
            true
#else
            false
#endif
        }
    });
}

} // namespace sdt_solver
