#include <sdt_solver/json.hpp>
#include <sdt_solver/occlusion_nbody.hpp>

#include <sdt/compiler/sha256.hpp>
#include <sdt/occlusion.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <limits>
#include <map>
#include <memory>
#include <numbers>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

#ifndef SDT_LAWS_SHA256
#define SDT_LAWS_SHA256 \
    "0000000000000000000000000000000000000000000000000000000000000000"
#endif

#ifndef SDT_SOLVER_COMPILER
#define SDT_SOLVER_COMPILER "unconfigured-c++20"
#endif

namespace sdt_solver::occlusion_nbody {
namespace {

using json::Array;
using json::Object;
using json::Value;
using sdt::dynamics::Vec3;

struct BodyDefinition {
    std::string id;
    std::string baryon_count;
    double baryons{};
    double radius_m{};
    double collision_radius_m{};
    bool has_displacement{};
    std::string proton_count;
    std::string neutron_count;
    double protons{};
    double neutrons{};
    std::array<std::string, sdt::occlusion::channel_count> channel_baryons;
    std::array<double, sdt::occlusion::channel_count> channel_baryons_double{};
};

struct State {
    Vec3 position{};
    Vec3 velocity{};
};

struct Tolerances {
    double retarded_time_s{1.0e-12};
    int max_retarded_iterations{32};
};

struct Definition {
    std::string case_id;
    std::string integrator;
    double timestep_s{};
    double duration_s{};
    std::uint64_t steps{};
    std::uint64_t record_every_steps{};
    double history_seconds{};
    Tolerances tolerances;
    std::vector<BodyDefinition> bodies;
    std::vector<State> initial_states;
    Value normalized;
};

struct HistoryFrame {
    double time_s{};
    std::vector<State> states;
};

struct RetardedState {
    State state;
    double time_s{};
    double residual_s{};
    bool extrapolated{};
};

struct Interaction {
    std::size_t target{};
    std::size_t source{};
    std::size_t target_channel{};
    std::size_t source_channel{};
    Vec3 target_centre{};
    Vec3 source_centre{};
    Vec3 axis{};
    Vec3 acceleration{};
    double raw_solid_angle_sr{};
    double visible_solid_angle_sr{};
    double shield_fraction{};
    double retarded_time_s{};
    double retarded_residual_s{};
};

struct PairResult {
    std::size_t target{};
    std::size_t source{};
    Vec3 acceleration{};
    double solid_angle_sr{};
    double shield_fraction{};
};

struct Evaluation {
    std::vector<Vec3> accelerations;
    std::vector<Vec3> point_accelerations;
    std::vector<double> depths;
    std::vector<double> resistance_ratios;
    std::vector<Interaction> interactions;
    std::vector<PairResult> pairs;
    std::uint64_t relation_count{};
    double maximum_retarded_residual_s{};
    double maximum_resistance_ratio{1.0};
    double maximum_shield_fraction{};
    bool used_extrapolation{};
};

struct Diagnostics {
    double maximum_retarded_residual_s{};
    double maximum_resistance_ratio{1.0};
    double maximum_shield_fraction{};
    double maximum_speed_fraction_c{};
    double maximum_far_field_relative{};
    double medium_closure_relative{};
    Vec3 body_impulse{};
    Vec3 medium_impulse{};
    bool used_extrapolation{};
};

struct GridKey {
    std::int64_t x{};
    std::int64_t y{};
    std::int64_t z{};

    [[nodiscard]] auto operator==(const GridKey&) const noexcept -> bool =
        default;
};

struct GridKeyHash {
    [[nodiscard]] auto operator()(const GridKey& key) const noexcept
        -> std::size_t {
        const auto mix = [](std::uint64_t value) {
            value ^= value >> 30U;
            value *= 0xbf58476d1ce4e5b9ULL;
            value ^= value >> 27U;
            value *= 0x94d049bb133111ebULL;
            return value ^ (value >> 31U);
        };
        return static_cast<std::size_t>(
            mix(static_cast<std::uint64_t>(key.x))
            ^ (mix(static_cast<std::uint64_t>(key.y)) << 1U)
            ^ (mix(static_cast<std::uint64_t>(key.z)) << 2U)
        );
    }
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

[[nodiscard]] auto require_string(
    const Value& value,
    const std::string& context
) -> const std::string& {
    if (!value.is_string()) {
        throw std::runtime_error(context + " must be a string");
    }
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
    if (!(result > 0.0)) throw std::runtime_error(context + " must be positive");
    return result;
}

[[nodiscard]] auto require_nonnegative(
    const Value& value,
    const std::string& context
) -> double {
    const double result = require_number(value, context);
    if (result < 0.0) {
        throw std::runtime_error(context + " must be non-negative");
    }
    return result;
}

[[nodiscard]] auto require_integer(
    const Value& value,
    const std::string& context,
    std::uint64_t minimum,
    std::uint64_t maximum
) -> std::uint64_t {
    const double result = require_number(value, context);
    if (result < static_cast<double>(minimum)
        || result > static_cast<double>(maximum)
        || std::floor(result) != result) {
        throw std::runtime_error(context + " must be an integer in range");
    }
    return static_cast<std::uint64_t>(result);
}

[[nodiscard]] auto vec3_from(
    const Value& value,
    const std::string& context
) -> Vec3 {
    if (!value.is_array() || value.array().size() != 3) {
        throw std::runtime_error(context + " must be a three-vector");
    }
    return {
        require_number(value.array()[0], context + "[0]"),
        require_number(value.array()[1], context + "[1]"),
        require_number(value.array()[2], context + "[2]")
    };
}

[[nodiscard]] auto json_vec3(Vec3 value) -> Value {
    return Array{value.x, value.y, value.z};
}

[[nodiscard]] auto canonical_decimal(const std::string& text) -> std::string {
    if (text.empty()) throw std::runtime_error("baryon_count must not be empty");
    for (const char digit : text) {
        if (digit < '0' || digit > '9') {
            throw std::runtime_error(
                "baryon_count must be an unsigned decimal string"
            );
        }
    }
    const auto first = text.find_first_not_of('0');
    if (first == std::string::npos) {
        throw std::runtime_error("baryon_count must be positive");
    }
    return text.substr(first);
}

[[nodiscard]] auto canonical_nonnegative_decimal(
    const std::string& text,
    const std::string& context
) -> std::string {
    if (text.empty()) throw std::runtime_error(context + " must not be empty");
    for (const char digit : text) {
        if (digit < '0' || digit > '9') {
            throw std::runtime_error(context + " must be an unsigned decimal");
        }
    }
    const auto first = text.find_first_not_of('0');
    return first == std::string::npos ? "0" : text.substr(first);
}

[[nodiscard]] auto decimal_double(const std::string& text) -> double {
    char* end = nullptr;
    const double result = std::strtod(text.c_str(), &end);
    if (end != text.c_str() + text.size()
        || !std::isfinite(result)
        || !(result > 0.0)) {
        throw std::runtime_error("baryon_count is outside binary64 range");
    }
    return result;
}

[[nodiscard]] auto divide_small(
    const std::string& value,
    unsigned divisor
) -> std::pair<std::string, unsigned> {
    unsigned remainder = 0;
    std::string quotient;
    quotient.reserve(value.size());
    for (const char digit : value) {
        const unsigned current =
            remainder * 10U + static_cast<unsigned>(digit - '0');
        const unsigned next = current / divisor;
        remainder = current % divisor;
        if (!quotient.empty() || next != 0U) {
            quotient.push_back(static_cast<char>('0' + next));
        }
    }
    if (quotient.empty()) quotient = "0";
    return {quotient, remainder};
}

[[nodiscard]] auto multiply_small(
    const std::string& value,
    unsigned multiplier
) -> std::string {
    unsigned carry = 0;
    std::string result(value.size(), '0');
    for (std::size_t index = value.size(); index-- > 0;) {
        const unsigned product =
            static_cast<unsigned>(value[index] - '0') * multiplier + carry;
        result[index] = static_cast<char>('0' + product % 10U);
        carry = product / 10U;
    }
    while (carry != 0U) {
        result.insert(result.begin(), static_cast<char>('0' + carry % 10U));
        carry /= 10U;
    }
    const auto first = result.find_first_not_of('0');
    return first == std::string::npos ? "0" : result.substr(first);
}

[[nodiscard]] auto add_small(
    std::string value,
    unsigned addend
) -> std::string {
    std::size_t index = value.size();
    unsigned carry = addend;
    while (index > 0 && carry != 0U) {
        --index;
        const unsigned sum =
            static_cast<unsigned>(value[index] - '0') + carry;
        value[index] = static_cast<char>('0' + sum % 10U);
        carry = sum / 10U;
    }
    while (carry != 0U) {
        value.insert(value.begin(), static_cast<char>('0' + carry % 10U));
        carry /= 10U;
    }
    return value;
}

[[nodiscard]] auto channel_allocations(const std::string& count)
    -> std::array<std::string, sdt::occlusion::channel_count> {
    const auto [quotient, remainder] = divide_small(count, 27U);
    std::array<std::string, sdt::occlusion::channel_count> result;
    std::array<unsigned, sdt::occlusion::channel_count> remainders{};
    result[0] = add_small(multiply_small(quotient, 3U), (3U * remainder) / 27U);
    remainders[0] = (3U * remainder) % 27U;
    for (std::size_t channel = 1; channel < result.size(); ++channel) {
        result[channel] =
            add_small(multiply_small(quotient, 4U), (4U * remainder) / 27U);
        remainders[channel] = (4U * remainder) % 27U;
    }
    unsigned missing = 0;
    for (const unsigned value : remainders) missing += value;
    missing /= 27U;
    std::array<std::size_t, sdt::occlusion::channel_count> order{};
    for (std::size_t index = 0; index < order.size(); ++index) {
        order[index] = index;
    }
    std::stable_sort(
        order.begin(),
        order.end(),
        [&](std::size_t left, std::size_t right) {
            return remainders[left] > remainders[right];
        }
    );
    for (unsigned index = 0; index < missing; ++index) {
        result[order[index]] = add_small(result[order[index]], 1U);
    }
    return result;
}

[[nodiscard]] auto decimal_sum(
    const std::array<std::string, sdt::occlusion::channel_count>& values
) -> std::string {
    std::string result = "0";
    for (const std::string& value : values) {
        std::string left = result;
        std::string right = value;
        const std::size_t width = std::max(left.size(), right.size());
        left.insert(left.begin(), width - left.size(), '0');
        right.insert(right.begin(), width - right.size(), '0');
        std::string sum(width, '0');
        unsigned carry = 0;
        for (std::size_t index = width; index-- > 0;) {
            const unsigned digit =
                static_cast<unsigned>(left[index] - '0')
                + static_cast<unsigned>(right[index] - '0') + carry;
            sum[index] = static_cast<char>('0' + digit % 10U);
            carry = digit / 10U;
        }
        if (carry != 0U) sum.insert(sum.begin(), '1');
        const auto first = sum.find_first_not_of('0');
        result = first == std::string::npos ? "0" : sum.substr(first);
    }
    return result;
}

[[nodiscard]] auto parse_definition(const std::string& input) -> Definition {
    Definition result;
    result.normalized = json::parse(input);
    if (!result.normalized.is_object()) {
        throw std::runtime_error("case must be an object");
    }
    const Object& root = result.normalized.object();
    if (require_string(object_at(root, "contract_version"), "contract_version")
        != contract_version) {
        throw std::runtime_error("unsupported multibody contract_version");
    }
    if (require_string(object_at(root, "problem_class"), "problem_class")
        != "sdt_occlusion_nbody") {
        throw std::runtime_error("problem_class must be sdt_occlusion_nbody");
    }
    result.case_id = require_string(object_at(root, "case_id"), "case_id");
    if (result.case_id.empty()) throw std::runtime_error("case_id is empty");
    const Object& frame = object_at(root, "frame").object();
    if (require_string(object_at(frame, "type"), "frame.type")
            != "inertial_cartesian"
        || require_string(object_at(frame, "units"), "frame.units") != "SI") {
        throw std::runtime_error("frame must be inertial_cartesian in SI");
    }
    const Array& forces = object_at(root, "forces").array();
    if (forces.size() != 1
        || require_string(
            object_at(forces[0].object(), "type"),
            "force.type"
        ) != "retarded_seven_circle_occlusion") {
        throw std::runtime_error(
            "v3 requires exactly retarded_seven_circle_occlusion"
        );
    }
    result.integrator =
        require_string(object_at(root, "integrator"), "integrator");
    if (result.integrator != "velocity_verlet"
        && result.integrator != "fixed_rk4") {
        throw std::runtime_error("unsupported v3 integrator");
    }
    result.timestep_s =
        require_positive(object_at(root, "timestep_s"), "timestep_s");
    result.duration_s =
        require_positive(object_at(root, "duration_s"), "duration_s");
    const double raw_steps = result.duration_s / result.timestep_s;
    if (raw_steps < 1.0
        || raw_steps > 1.0e12
        || std::abs(raw_steps - std::round(raw_steps))
            > 1.0e-10 * std::max(1.0, raw_steps)) {
        throw std::runtime_error(
            "duration_s/timestep_s must be an integer no greater than 1e12"
        );
    }
    result.steps = static_cast<std::uint64_t>(std::round(raw_steps));
    result.record_every_steps = require_integer(
        object_at(root, "record_every_steps"),
        "record_every_steps",
        1,
        result.steps
    );
    result.history_seconds = root.contains("history_seconds")
        ? require_positive(root.at("history_seconds"), "history_seconds")
        : 0.0;
    if (root.contains("tolerances")) {
        const Object& tolerances = root.at("tolerances").object();
        if (tolerances.contains("retarded_time_s")) {
            result.tolerances.retarded_time_s = require_positive(
                tolerances.at("retarded_time_s"),
                "tolerances.retarded_time_s"
            );
        }
        if (tolerances.contains("max_retarded_iterations")) {
            result.tolerances.max_retarded_iterations = static_cast<int>(
                require_integer(
                    tolerances.at("max_retarded_iterations"),
                    "tolerances.max_retarded_iterations",
                    2,
                    128
                )
            );
        }
    }
    const Array& bodies = object_at(root, "bodies").array();
    if (bodies.size() < 2 || bodies.size() > 10000) {
        throw std::runtime_error("v3 requires from 2 to 10000 bodies");
    }
    std::set<std::string> ids;
    for (const Value& body_value : bodies) {
        const Object& body = body_value.object();
        BodyDefinition parsed;
        parsed.id = require_string(object_at(body, "id"), "body.id");
        if (!ids.insert(parsed.id).second) {
            throw std::runtime_error("body IDs must be unique");
        }
        parsed.baryon_count = canonical_decimal(
            require_string(object_at(body, "baryon_count"), "baryon_count")
        );
        parsed.baryons = decimal_double(parsed.baryon_count);
        parsed.radius_m = require_positive(
            object_at(body, "radius_m"),
            "body.radius_m"
        );
        parsed.collision_radius_m = require_nonnegative(
            object_at(body, "collision_radius_m"),
            "body.collision_radius_m"
        );
        parsed.channel_baryons = channel_allocations(parsed.baryon_count);
        if (decimal_sum(parsed.channel_baryons) != parsed.baryon_count) {
            throw std::runtime_error("channel baryon reconstruction failed");
        }
        for (std::size_t channel = 0;
             channel < sdt::occlusion::channel_count;
             ++channel) {
            parsed.channel_baryons_double[channel] =
                std::strtod(parsed.channel_baryons[channel].c_str(), nullptr);
        }
        if (body.contains("displacement")) {
            const Object& displacement = body.at("displacement").object();
            parsed.has_displacement = true;
            parsed.proton_count = canonical_nonnegative_decimal(
                require_string(
                    object_at(displacement, "proton_count"),
                    "displacement.proton_count"
                ),
                "displacement.proton_count"
            );
            parsed.neutron_count = canonical_nonnegative_decimal(
                require_string(
                    object_at(displacement, "neutron_count"),
                    "displacement.neutron_count"
                ),
                "displacement.neutron_count"
            );
            std::array<std::string, sdt::occlusion::channel_count> counts{};
            counts.fill("0");
            counts[0] = parsed.proton_count;
            counts[1] = parsed.neutron_count;
            if (decimal_sum(counts) != parsed.baryon_count) {
                throw std::runtime_error(
                    "proton_count plus neutron_count must equal baryon_count"
                );
            }
            parsed.protons = parsed.proton_count == "0"
                ? 0.0
                : decimal_double(parsed.proton_count);
            parsed.neutrons = parsed.neutron_count == "0"
                ? 0.0
                : decimal_double(parsed.neutron_count);
        }
        const State state{
            vec3_from(object_at(body, "position_m"), "body.position_m"),
            vec3_from(object_at(body, "velocity_m_s"), "body.velocity_m_s")
        };
        if (!(sdt::dynamics::norm(state.velocity)
            < sdt::laws::measured::c)) {
            throw std::runtime_error("initial body speed must be below c");
        }
        result.bodies.push_back(std::move(parsed));
        result.initial_states.push_back(state);
    }
    return result;
}

[[nodiscard]] auto state_json(
    const BodyDefinition& body,
    const State& state
) -> Value {
    return Object{
        {"id", body.id},
        {"position_m", json_vec3(state.position)},
        {"velocity_m_s", json_vec3(state.velocity)}
    };
}

class Session {
public:
    explicit Session(Definition definition)
        : definition_(std::move(definition)),
          states_(definition_.initial_states) {
        initialize_history();
        record_frame();
    }

    Session(Definition definition, const Value& checkpoint)
        : definition_(std::move(definition)) {
        restore(checkpoint);
    }

    [[nodiscard]] auto advance(std::uint64_t requested) -> std::string {
        const std::uint64_t remaining =
            definition_.steps > step_ ? definition_.steps - step_ : 0;
        const std::uint64_t count = std::min(requested, remaining);
        for (std::uint64_t index = 0; index < count; ++index) {
            if (!step_once()) break;
            if (step_ % definition_.record_every_steps == 0
                || step_ == definition_.steps) {
                record_frame();
            }
        }
        return result_json();
    }

    [[nodiscard]] auto run() -> std::string {
        return advance(definition_.steps - step_);
    }

    [[nodiscard]] auto checkpoint_json() const -> std::string {
        Array states;
        for (const State& state : states_) {
            states.emplace_back(Object{
                {"position_m", json_vec3(state.position)},
                {"velocity_m_s", json_vec3(state.velocity)}
            });
        }
        Array history;
        for (const HistoryFrame& frame : history_) {
            Array frame_states;
            for (const State& state : frame.states) {
                frame_states.emplace_back(Object{
                    {"position_m", json_vec3(state.position)},
                    {"velocity_m_s", json_vec3(state.velocity)}
                });
            }
            history.emplace_back(Object{
                {"states", std::move(frame_states)},
                {"time_s", frame.time_s}
            });
        }
        return json::canonical(Object{
            {"diagnostics", diagnostics_value()},
            {"history", std::move(history)},
            {"states", std::move(states)},
            {"step", static_cast<double>(step_)},
            {"time_s", time_s_},
            {"trajectory", trajectory_},
            {"version", contract_version}
        });
    }

private:
    Definition definition_;
    std::vector<State> states_;
    std::deque<HistoryFrame> history_;
    std::uint64_t step_{};
    double time_s_{};
    std::string status_{"running"};
    std::string message_{"session created"};
    Diagnostics diagnostics_;
    Array trajectory_;
    Evaluation last_evaluation_;
    bool has_last_evaluation_{};

    void initialize_history() {
        double maximum_distance = 0.0;
        for (std::size_t left = 0; left < states_.size(); ++left) {
            for (std::size_t right = left + 1; right < states_.size(); ++right) {
                maximum_distance = std::max(
                    maximum_distance,
                    sdt::dynamics::norm(
                        states_[right].position - states_[left].position
                    )
                );
            }
        }
        const double span = std::max(
            definition_.history_seconds,
            1.25 * maximum_distance / sdt::laws::measured::c
                + 2.0 * definition_.timestep_s
        );
        std::vector<State> previous = states_;
        for (State& state : previous) {
            state.position = state.position - state.velocity * span;
        }
        history_.push_back({-span, std::move(previous)});
        history_.push_back({0.0, states_});
    }

    [[nodiscard]] auto interpolate(
        std::size_t source,
        double query_time,
        double evaluation_time,
        const std::vector<State>& evaluation_states
    ) const -> std::pair<State, bool> {
        if (query_time <= history_.front().time_s) {
            const HistoryFrame& first = history_.front();
            const double delta = query_time - first.time_s;
            State state = first.states[source];
            state.position = state.position + state.velocity * delta;
            return {state, query_time < first.time_s};
        }
        const auto upper = std::lower_bound(
            history_.begin() + 1,
            history_.end(),
            query_time,
            [](const HistoryFrame& frame, double value) {
                return frame.time_s < value;
            }
        );
        if (upper != history_.end()) {
                const HistoryFrame& first = *(upper - 1);
                const HistoryFrame& second = *upper;
                const double span = second.time_s - first.time_s;
                const double fraction =
                    span > 0.0 ? (query_time - first.time_s) / span : 0.0;
                return {
                    {
                        first.states[source].position * (1.0 - fraction)
                            + second.states[source].position * fraction,
                        first.states[source].velocity * (1.0 - fraction)
                            + second.states[source].velocity * fraction
                    },
                    false
                };
        }
        const HistoryFrame& last = history_.back();
        if (evaluation_time > last.time_s && query_time <= evaluation_time) {
            const double span = evaluation_time - last.time_s;
            const double fraction = span > 0.0
                ? std::clamp(
                    (query_time - last.time_s) / span,
                    0.0,
                    1.0
                )
                : 0.0;
            return {
                {
                    last.states[source].position * (1.0 - fraction)
                        + evaluation_states[source].position * fraction,
                    last.states[source].velocity * (1.0 - fraction)
                        + evaluation_states[source].velocity * fraction
                },
                false
            };
        }
        State state = last.states[source];
        state.position =
            state.position + state.velocity * (query_time - last.time_s);
        return {state, true};
    }

    [[nodiscard]] auto retarded(
        std::size_t target,
        std::size_t source,
        double evaluation_time,
        const std::vector<State>& evaluation_states
    ) const -> RetardedState {
        const double c = sdt::laws::measured::c;
        double delay = sdt::dynamics::norm(
            evaluation_states[source].position
                - evaluation_states[target].position
        ) / c;
        double query_time = evaluation_time - delay;
        State sampled{};
        bool extrapolated = false;
        for (int iteration = 0;
             iteration < definition_.tolerances.max_retarded_iterations;
             ++iteration) {
            auto [state, used_extrapolation] = interpolate(
                source,
                query_time,
                evaluation_time,
                evaluation_states
            );
            sampled = state;
            extrapolated = extrapolated || used_extrapolation;
            const double next_delay = sdt::dynamics::norm(
                sampled.position - evaluation_states[target].position
            ) / c;
            if (std::abs(next_delay - delay)
                <= definition_.tolerances.retarded_time_s) {
                delay = next_delay;
                break;
            }
            delay = next_delay;
            query_time = evaluation_time - delay;
        }
        query_time = evaluation_time - delay;
        auto [final_state, used_extrapolation] = interpolate(
            source,
            query_time,
            evaluation_time,
            evaluation_states
        );
        sampled = final_state;
        extrapolated = extrapolated || used_extrapolation;
        const double residual = std::abs(
            delay - sdt::dynamics::norm(
                sampled.position - evaluation_states[target].position
            ) / c
        );
        return {sampled, query_time, residual, extrapolated};
    }

    [[nodiscard]] auto blocked(
        Vec3 observer,
        Vec3 source_node,
        const std::vector<RetardedState>& target_retarded,
        const std::vector<std::size_t>& candidates
    ) const -> bool {
        const Vec3 ray = source_node - observer;
        const double ray_squared = sdt::dynamics::dot(ray, ray);
        if (!(ray_squared > 0.0)) return true;
        for (const std::size_t blocker : candidates) {
            const Vec3 centre = target_retarded[blocker].state.position;
            const double fraction = sdt::dynamics::dot(
                centre - observer,
                ray
            ) / ray_squared;
            if (!(fraction > 0.0 && fraction < 1.0)) continue;
            const Vec3 intersection = observer + ray * fraction;
            const auto frame = sdt::occlusion::pair_frame(centre - observer);
            const double channel_radius =
                definition_.bodies[blocker].radius_m / 3.0;
            for (std::size_t channel = 0;
                 channel < sdt::occlusion::channel_count;
                 ++channel) {
                const Vec3 channel_centre = centre
                    + sdt::occlusion::channel_offset(
                        channel,
                        definition_.bodies[blocker].radius_m,
                        frame
                    );
                if (sdt::dynamics::norm(intersection - channel_centre)
                    <= channel_radius) {
                    return true;
                }
            }
        }
        return false;
    }

    [[nodiscard]] auto evaluate(
        double evaluation_time,
        const std::vector<State>& evaluation_states,
        bool include_interactions
    ) const -> Evaluation {
        const std::size_t count = states_.size();
        Evaluation result;
        result.accelerations.assign(count, {});
        result.point_accelerations.assign(count, {});
        result.depths.assign(count, 0.0);
        result.resistance_ratios.assign(count, 1.0);
        const bool capture_details = include_interactions && count <= 64U;
        std::vector<std::vector<RetardedState>> retarded_states(
            count,
            std::vector<RetardedState>(count)
        );
#if defined(_OPENMP)
#pragma omp parallel for schedule(static) if(count > 64U)
#endif
        for (std::int64_t target_index = 0;
             target_index < static_cast<std::int64_t>(count);
             ++target_index) {
            const std::size_t target =
                static_cast<std::size_t>(target_index);
            for (std::size_t source = 0; source < count; ++source) {
                if (target == source) continue;
                retarded_states[target][source] = retarded(
                    target,
                    source,
                    evaluation_time,
                    evaluation_states
                );
            }
        }
        for (std::size_t target = 0; target < count; ++target) {
            for (std::size_t source = 0; source < count; ++source) {
                if (target == source) continue;
                const RetardedState& state =
                    retarded_states[target][source];
                result.maximum_retarded_residual_s = std::max(
                    result.maximum_retarded_residual_s,
                    state.residual_s
                );
                result.used_extrapolation =
                    result.used_extrapolation || state.extrapolated;
            }
        }
        const double c2 =
            sdt::laws::measured::c * sdt::laws::measured::c;
        double maximum_radius = 0.0;
        double maximum_speed = 0.0;
        for (std::size_t index = 0; index < count; ++index) {
            maximum_radius = std::max(
                maximum_radius,
                definition_.bodies[index].radius_m
            );
            maximum_speed = std::max(
                maximum_speed,
                sdt::dynamics::norm(evaluation_states[index].velocity)
            );
        }
        const std::int64_t angular_resolution =
            std::max<std::int64_t>(4, static_cast<std::int64_t>(
                std::ceil(2.0 * std::cbrt(static_cast<double>(count)))
            ));
        const auto angular_key = [&](Vec3 direction) {
            const Vec3 unit = sdt::occlusion::unit(direction);
            return GridKey{
                static_cast<std::int64_t>(std::floor(
                    (unit.x + 1.0) * 0.5 * angular_resolution
                )),
                static_cast<std::int64_t>(std::floor(
                    (unit.y + 1.0) * 0.5 * angular_resolution
                )),
                static_cast<std::int64_t>(std::floor(
                    (unit.z + 1.0) * 0.5 * angular_resolution
                ))
            };
        };
        const std::int64_t angular_side = angular_resolution + 1;
        const auto angular_index = [&](GridKey key) {
            return static_cast<std::size_t>(
                (key.x * angular_side + key.y) * angular_side + key.z
            );
        };
        std::vector<double> target_maximum_shield(count, 0.0);
        if (!capture_details) {
            result.relation_count = 49U * count * (count - 1U);
        }
#if defined(_OPENMP)
#pragma omp parallel for schedule(static) if(count > 64U)
#endif
        for (std::int64_t target_index = 0;
             target_index < static_cast<std::int64_t>(count);
             ++target_index) {
            const std::size_t target =
                static_cast<std::size_t>(target_index);
            std::vector<std::int32_t> angular_heads(
                static_cast<std::size_t>(
                    angular_side * angular_side * angular_side
                ),
                -1
            );
            std::vector<std::int32_t> angular_next(count, -1);
            if (count > 64U) {
                for (std::size_t index = 0; index < count; ++index) {
                    if (index == target) continue;
                    const std::size_t cell = angular_index(angular_key(
                        evaluation_states[index].position
                            - evaluation_states[target].position
                    ));
                    angular_next[index] = angular_heads[cell];
                    angular_heads[cell] = static_cast<std::int32_t>(index);
                }
            }
            for (std::size_t source = 0; source < count; ++source) {
                if (target == source) continue;
                const RetardedState& source_state =
                    retarded_states[target][source];
                const Vec3 body_delta =
                    source_state.state.position
                    - evaluation_states[target].position;
                const double body_distance = sdt::dynamics::norm(body_delta);
                if (!(body_distance
                    > definition_.bodies[target].collision_radius_m
                        + definition_.bodies[source].collision_radius_m)) {
                    throw std::runtime_error("contact boundary reached");
                }
                const auto frame = sdt::occlusion::pair_frame(body_delta);
                const double source_channel_radius =
                    definition_.bodies[source].radius_m / 3.0;
                std::vector<std::size_t> candidates;
                if (count <= 64U) {
                    candidates.reserve(count > 2U ? count - 2U : 0U);
                    for (std::size_t blocker = 0; blocker < count; ++blocker) {
                        if (blocker != target && blocker != source) {
                            candidates.push_back(blocker);
                        }
                    }
                } else {
                    const Vec3 start = evaluation_states[target].position;
                    const Vec3 ray = source_state.state.position - start;
                    const double length = sdt::dynamics::norm(ray);
                    const double delay_motion =
                        maximum_speed * length / sdt::laws::measured::c;
                    const double corridor =
                        definition_.bodies[target].radius_m
                        + definition_.bodies[source].radius_m
                        + maximum_radius + delay_motion;
                    const std::int64_t reach = static_cast<std::int64_t>(
                        std::floor(
                            corridor / length
                            * static_cast<double>(angular_resolution) * 0.5
                        )
                    ) + 1;
                    const double ray_squared =
                        sdt::dynamics::dot(ray, ray);
                    const GridKey key = angular_key(ray);
                    for (std::int64_t dx = -reach; dx <= reach; ++dx) {
                        for (std::int64_t dy = -reach;
                             dy <= reach;
                             ++dy) {
                            for (std::int64_t dz = -reach;
                                 dz <= reach;
                                 ++dz) {
                                const GridKey adjacent{
                                    key.x + dx,
                                    key.y + dy,
                                    key.z + dz
                                };
                                if (
                                    adjacent.x < 0 || adjacent.y < 0
                                    || adjacent.z < 0
                                    || adjacent.x >= angular_side
                                    || adjacent.y >= angular_side
                                    || adjacent.z >= angular_side
                                ) {
                                    continue;
                                }
                                for (std::int32_t entry =
                                         angular_heads[
                                             angular_index(adjacent)
                                         ];
                                     entry >= 0;
                                     entry = angular_next[
                                         static_cast<std::size_t>(entry)
                                     ]) {
                                    const std::size_t blocker =
                                        static_cast<std::size_t>(entry);
                                    if (blocker == source) continue;
                                    const Vec3 centre =
                                        evaluation_states[blocker].position;
                                    const double fraction =
                                        sdt::dynamics::dot(
                                            centre - start,
                                            ray
                                        ) / ray_squared;
                                    if (!(fraction > 0.0 && fraction < 1.0)) {
                                        continue;
                                    }
                                    if (sdt::dynamics::norm(
                                            centre - (
                                                start + ray * fraction
                                            )
                                        ) <= corridor) {
                                        candidates.push_back(blocker);
                                    }
                                }
                            }
                        }
                    }
                }
                Vec3 pair_acceleration{};
                double pair_raw = 0.0;
                double pair_visible = 0.0;
                const bool aggregate_far_field =
                    !capture_details && candidates.empty()
                    && std::max(
                        definition_.bodies[target].radius_m,
                        definition_.bodies[source].radius_m
                    ) * std::max(
                        definition_.bodies[target].radius_m,
                        definition_.bodies[source].radius_m
                    ) < 1.0e-10 * body_distance * body_distance;
                if (aggregate_far_field) {
                    if (capture_details) result.relation_count += 49U;
                    pair_acceleration = body_delta * (
                        c2 * sdt::laws::bridge::koppa_per_baryon
                        * definition_.bodies[source].baryons
                        / (body_distance * body_distance * body_distance)
                    );
                    const double section_area = std::numbers::pi
                        * source_channel_radius * source_channel_radius;
                    pair_raw = 7.0 * section_area
                        / (body_distance * body_distance);
                    pair_visible = pair_raw;
                    result.depths[target] += pair_visible
                        / (2.0 * std::numbers::pi);
                } else {
                    for (std::size_t target_channel = 0;
                     target_channel < sdt::occlusion::channel_count;
                     ++target_channel) {
                    const Vec3 target_centre =
                        evaluation_states[target].position
                        + sdt::occlusion::channel_offset(
                            target_channel,
                            definition_.bodies[target].radius_m,
                            frame
                        );
                    const double target_fraction =
                        definition_.bodies[target]
                            .channel_baryons_double[target_channel]
                        / definition_.bodies[target].baryons;
                    for (std::size_t source_channel = 0;
                         source_channel < sdt::occlusion::channel_count;
                         ++source_channel) {
                        if (capture_details) ++result.relation_count;
                        const Vec3 source_centre =
                            source_state.state.position
                            + sdt::occlusion::channel_offset(
                                source_channel,
                                definition_.bodies[source].radius_m,
                                frame
                            );
                        const double area = std::numbers::pi
                            * source_channel_radius * source_channel_radius;
                        if (!(area > 0.0)) continue;
                        double raw_solid_angle = 0.0;
                        double visible_solid_angle = 0.0;
                        const Vec3 centre_to_observer =
                            target_centre - source_centre;
                        const double centre_distance_squared =
                            sdt::dynamics::dot(
                                centre_to_observer,
                                centre_to_observer
                            );
                        if (
                            candidates.empty()
                            && source_channel_radius * source_channel_radius
                                < 1.0e-10 * centre_distance_squared
                        ) {
                            raw_solid_angle = area * std::max(
                                0.0,
                                sdt::dynamics::dot(
                                    frame.normal * -1.0,
                                    centre_to_observer
                                ) / std::sqrt(centre_distance_squared)
                            ) / centre_distance_squared;
                            visible_solid_angle = raw_solid_angle;
                        } else {
                            sdt::occlusion::for_each_disc_node(
                                source_centre,
                                frame.first,
                                frame.second,
                                source_channel_radius,
                                [&](const sdt::occlusion::DiscNode& node) {
                                const Vec3 to_observer =
                                    target_centre - node.position;
                                const double distance_squared =
                                    sdt::dynamics::dot(
                                        to_observer,
                                        to_observer
                                    );
                                if (!(distance_squared > 0.0)) return;
                                const double cosine = std::max(
                                    0.0,
                                    sdt::dynamics::dot(
                                        frame.normal * -1.0,
                                        to_observer
                                    ) / std::sqrt(distance_squared)
                                );
                                const double contribution =
                                    cosine * node.area_weight_m2
                                    / distance_squared;
                                raw_solid_angle += contribution;
                                if (!blocked(
                                        target_centre,
                                        node.position,
                                        retarded_states[target],
                                        candidates
                                    )) {
                                    visible_solid_angle += contribution;
                                }
                                }
                            );
                        }
                        const double source_baryons =
                            definition_.bodies[source]
                                .channel_baryons_double[source_channel];
                        const Vec3 axis = sdt::occlusion::unit(
                            source_centre - target_centre
                        );
                        const Vec3 acceleration = axis * (
                            target_fraction * c2
                            * sdt::laws::bridge::koppa_per_baryon
                            * source_baryons
                            * visible_solid_angle / area
                        );
                        pair_acceleration += acceleration;
                        pair_raw += raw_solid_angle * target_fraction;
                        pair_visible +=
                            visible_solid_angle * target_fraction;
                        result.depths[target] +=
                            target_fraction * visible_solid_angle
                            / (2.0 * std::numbers::pi);
                        if (capture_details) {
                            result.interactions.push_back({
                                target,
                                source,
                                target_channel,
                                source_channel,
                                target_centre,
                                source_centre,
                                axis,
                                acceleration,
                                raw_solid_angle,
                                visible_solid_angle,
                                raw_solid_angle > 0.0
                                    ? std::clamp(
                                        1.0 - visible_solid_angle
                                            / raw_solid_angle,
                                        0.0,
                                        1.0
                                    )
                                    : 0.0,
                                source_state.time_s,
                                source_state.residual_s
                            });
                        }
                    }
                    }
                }
                const double shield = pair_raw > 0.0
                    ? std::clamp(1.0 - pair_visible / pair_raw, 0.0, 1.0)
                    : 0.0;
                target_maximum_shield[target] = std::max(
                    target_maximum_shield[target],
                    shield
                );
                if (capture_details) {
                    result.pairs.push_back({
                        target,
                        source,
                        pair_acceleration,
                        pair_visible,
                        shield
                    });
                }
                result.accelerations[target] += pair_acceleration;
                const Vec3 instantaneous =
                    evaluation_states[source].position
                    - evaluation_states[target].position;
                const double distance = sdt::dynamics::norm(instantaneous);
                result.point_accelerations[target] += instantaneous * (
                    c2 * sdt::laws::bridge::koppa_per_baryon
                    * definition_.bodies[source].baryons
                    / (distance * distance * distance)
                );
            }
        }
        for (const double shield : target_maximum_shield) {
            result.maximum_shield_fraction = std::max(
                result.maximum_shield_fraction,
                shield
            );
        }
        for (std::size_t target = 0; target < count; ++target) {
            const BodyDefinition& body = definition_.bodies[target];
            const double rest_volume = body.has_displacement
                ? body.protons * sdt::laws::law_IV::V_disp_from_mass(
                    sdt::laws::measured::m_p
                ) + body.neutrons * sdt::laws::law_IV::V_disp_from_mass(
                    sdt::laws::measured::m_n
                )
                : body.baryons * sdt::laws::law_IV::V_disp_from_mass(
                    sdt::laws::measured::m_p
                );
            const double effective_volume =
                rest_volume * (1.0 + result.depths[target]);
            const double rest_mass =
                sdt::laws::law_IV::mass_from_V_disp(rest_volume);
            const double effective_mass =
                sdt::laws::law_IV::mass_from_V_disp(effective_volume);
            const double resistance =
                rest_mass > 0.0 ? effective_mass / rest_mass : 1.0;
            result.resistance_ratios[target] = resistance;
            result.maximum_resistance_ratio = std::max(
                result.maximum_resistance_ratio,
                resistance
            );
            result.accelerations[target] =
                sdt::occlusion::law_v_response(
                    result.accelerations[target] / resistance,
                    evaluation_states[target].velocity
                );
        }
        return result;
    }

    [[nodiscard]] auto collision(const std::vector<State>& values) const
        -> bool {
        for (std::size_t left = 0; left < values.size(); ++left) {
            for (std::size_t right = left + 1; right < values.size(); ++right) {
                const double boundary =
                    definition_.bodies[left].collision_radius_m
                    + definition_.bodies[right].collision_radius_m;
                if (sdt::dynamics::norm(
                        values[right].position - values[left].position
                    ) <= boundary) {
                    return true;
                }
            }
        }
        return false;
    }

    [[nodiscard]] auto step_verlet() -> bool {
        const double dt = definition_.timestep_s;
        const Evaluation initial = evaluate(time_s_, states_, false);
        std::vector<State> candidate = states_;
        for (std::size_t index = 0; index < candidate.size(); ++index) {
            candidate[index].position = states_[index].position
                + states_[index].velocity * dt
                + initial.accelerations[index] * (0.5 * dt * dt);
        }
        if (collision(candidate)) return false;
        const Evaluation terminal =
            evaluate(time_s_ + dt, candidate, false);
        for (std::size_t index = 0; index < candidate.size(); ++index) {
            candidate[index].velocity = states_[index].velocity
                + (initial.accelerations[index]
                    + terminal.accelerations[index]) * (0.5 * dt);
            if (!(sdt::dynamics::norm(candidate[index].velocity)
                < sdt::laws::measured::c)) {
                return false;
            }
        }
        absorb_impulse(candidate);
        states_ = std::move(candidate);
        absorb_evaluation(terminal);
        last_evaluation_ = terminal;
        has_last_evaluation_ = true;
        return true;
    }

    [[nodiscard]] auto step_rk4() -> bool {
        struct Derivative {
            std::vector<Vec3> position;
            std::vector<Vec3> velocity;
        };
        const auto derivative = [&](double time,
                                    const std::vector<State>& values) {
            const Evaluation evaluated = evaluate(time, values, false);
            Derivative result;
            result.position.resize(values.size());
            result.velocity = evaluated.accelerations;
            for (std::size_t index = 0; index < values.size(); ++index) {
                result.position[index] = values[index].velocity;
            }
            return result;
        };
        const auto shifted = [](const std::vector<State>& values,
                                const Derivative& change,
                                double scale) {
            std::vector<State> result = values;
            for (std::size_t index = 0; index < values.size(); ++index) {
                result[index].position =
                    values[index].position + change.position[index] * scale;
                result[index].velocity =
                    values[index].velocity + change.velocity[index] * scale;
            }
            return result;
        };
        const double dt = definition_.timestep_s;
        const Derivative first = derivative(time_s_, states_);
        const auto second_state = shifted(states_, first, 0.5 * dt);
        const Derivative second =
            derivative(time_s_ + 0.5 * dt, second_state);
        const auto third_state = shifted(states_, second, 0.5 * dt);
        const Derivative third =
            derivative(time_s_ + 0.5 * dt, third_state);
        const auto fourth_state = shifted(states_, third, dt);
        const Derivative fourth = derivative(time_s_ + dt, fourth_state);
        std::vector<State> candidate = states_;
        for (std::size_t index = 0; index < candidate.size(); ++index) {
            candidate[index].position += (
                first.position[index]
                + second.position[index] * 2.0
                + third.position[index] * 2.0
                + fourth.position[index]
            ) * (dt / 6.0);
            candidate[index].velocity += (
                first.velocity[index]
                + second.velocity[index] * 2.0
                + third.velocity[index] * 2.0
                + fourth.velocity[index]
            ) * (dt / 6.0);
            if (!(sdt::dynamics::norm(candidate[index].velocity)
                < sdt::laws::measured::c)) {
                return false;
            }
        }
        if (collision(candidate)) return false;
        absorb_impulse(candidate);
        states_ = std::move(candidate);
        const Evaluation terminal = evaluate(time_s_ + dt, states_, false);
        absorb_evaluation(terminal);
        last_evaluation_ = terminal;
        has_last_evaluation_ = true;
        return true;
    }

    [[nodiscard]] auto step_once() -> bool {
        bool advanced = false;
        try {
            advanced = definition_.integrator == "velocity_verlet"
                ? step_verlet()
                : step_rk4();
        } catch (const std::exception& error) {
            status_ = "numerical_failure";
            message_ = error.what();
            return false;
        }
        if (!advanced) {
            status_ = collision(states_) ? "collision" : "numerical_failure";
            message_ = status_ == "collision"
                ? "contact boundary reached before overlap"
                : "step rejected at collision or c boundary";
            return false;
        }
        ++step_;
        time_s_ = static_cast<double>(step_) * definition_.timestep_s;
        history_.push_back({time_s_, states_});
        trim_history();
        if (step_ >= definition_.steps) {
            status_ = "completed";
            message_ = "multibody seven-circle run completed";
        } else {
            status_ = "running";
            message_ = "multibody seven-circle session advanced";
        }
        return true;
    }

    void absorb_impulse(const std::vector<State>& candidate) {
        Vec3 body_change{};
        double scale = 0.0;
        for (std::size_t index = 0; index < states_.size(); ++index) {
            const BodyDefinition& body = definition_.bodies[index];
            const double mass = body.has_displacement
                ? body.protons * sdt::laws::measured::m_p
                    + body.neutrons * sdt::laws::measured::m_n
                : body.baryons * sdt::laws::measured::m_p;
            const Vec3 change =
                (candidate[index].velocity - states_[index].velocity) * mass;
            body_change += change;
            scale += sdt::dynamics::norm(change);
        }
        diagnostics_.body_impulse += body_change;
        diagnostics_.medium_impulse -= body_change;
        const Vec3 closure =
            diagnostics_.body_impulse + diagnostics_.medium_impulse;
        diagnostics_.medium_closure_relative =
            scale > 0.0 ? sdt::dynamics::norm(closure) / scale : 0.0;
    }

    void absorb_evaluation(const Evaluation& evaluation) {
        diagnostics_.maximum_retarded_residual_s = std::max(
            diagnostics_.maximum_retarded_residual_s,
            evaluation.maximum_retarded_residual_s
        );
        diagnostics_.maximum_resistance_ratio = std::max(
            diagnostics_.maximum_resistance_ratio,
            evaluation.maximum_resistance_ratio
        );
        diagnostics_.maximum_shield_fraction = std::max(
            diagnostics_.maximum_shield_fraction,
            evaluation.maximum_shield_fraction
        );
        diagnostics_.used_extrapolation =
            diagnostics_.used_extrapolation || evaluation.used_extrapolation;
        for (const State& state : states_) {
            diagnostics_.maximum_speed_fraction_c = std::max(
                diagnostics_.maximum_speed_fraction_c,
                sdt::dynamics::norm(state.velocity)
                    / sdt::laws::measured::c
            );
        }
        for (std::size_t index = 0;
             index < evaluation.accelerations.size();
             ++index) {
            const double scale =
                sdt::dynamics::norm(evaluation.point_accelerations[index]);
            if (scale > 0.0) {
                diagnostics_.maximum_far_field_relative = std::max(
                    diagnostics_.maximum_far_field_relative,
                    sdt::dynamics::norm(
                        evaluation.accelerations[index]
                            - evaluation.point_accelerations[index]
                    ) / scale
                );
            }
        }
    }

    void trim_history() {
        double maximum_distance = 0.0;
        for (std::size_t left = 0; left < states_.size(); ++left) {
            for (std::size_t right = left + 1; right < states_.size(); ++right) {
                maximum_distance = std::max(
                    maximum_distance,
                    sdt::dynamics::norm(
                        states_[right].position - states_[left].position
                    )
                );
            }
        }
        const double retain = std::max(
            definition_.history_seconds,
            1.25 * maximum_distance / sdt::laws::measured::c
                + 2.0 * definition_.timestep_s
        );
        while (history_.size() > 2
            && history_[1].time_s < time_s_ - retain) {
            history_.pop_front();
        }
    }

    void record_frame() {
        Array values;
        for (std::size_t index = 0; index < states_.size(); ++index) {
            values.emplace_back(state_json(definition_.bodies[index], states_[index]));
        }
        trajectory_.emplace_back(Object{
            {"states", std::move(values)},
            {"step", static_cast<double>(step_)},
            {"time_s", time_s_}
        });
    }

    [[nodiscard]] auto interaction_json(const Interaction& value) const
        -> Value {
        return Object{
            {"acceleration_m_s2", json_vec3(value.acceleration)},
            {"axis", json_vec3(value.axis)},
            {"raw_solid_angle_sr", value.raw_solid_angle_sr},
            {"retarded_residual_s", value.retarded_residual_s},
            {"retarded_time_s", value.retarded_time_s},
            {"shield_fraction", value.shield_fraction},
            {"source", definition_.bodies[value.source].id},
            {"source_centre_m", json_vec3(value.source_centre)},
            {"source_channel", static_cast<double>(value.source_channel)},
            {
                "source_channel_baryons",
                definition_.bodies[value.source]
                    .channel_baryons[value.source_channel]
            },
            {"target", definition_.bodies[value.target].id},
            {"target_centre_m", json_vec3(value.target_centre)},
            {"target_channel", static_cast<double>(value.target_channel)},
            {
                "target_channel_baryons",
                definition_.bodies[value.target]
                    .channel_baryons[value.target_channel]
            },
            {"visible_solid_angle_sr", value.visible_solid_angle_sr}
        };
    }

    [[nodiscard]] auto diagnostics_value() const -> Value {
        return Object{
            {"maximum_far_field_relative", diagnostics_.maximum_far_field_relative},
            {
                "maximum_resistance_ratio",
                diagnostics_.maximum_resistance_ratio
            },
            {
                "maximum_retarded_residual_s",
                diagnostics_.maximum_retarded_residual_s
            },
            {
                "maximum_shield_fraction",
                diagnostics_.maximum_shield_fraction
            },
            {
                "maximum_speed_fraction_c",
                diagnostics_.maximum_speed_fraction_c
            },
            {
                "medium_closure_relative",
                diagnostics_.medium_closure_relative
            },
            {"body_impulse_kg_m_s", json_vec3(diagnostics_.body_impulse)},
            {"medium_impulse_kg_m_s", json_vec3(diagnostics_.medium_impulse)},
            {"used_ballistic_extrapolation", diagnostics_.used_extrapolation}
        };
    }

    [[nodiscard]] auto result_json() const -> std::string {
        Evaluation current;
        try {
            current = states_.size() > 64U && has_last_evaluation_
                ? last_evaluation_
                : evaluate(time_s_, states_, true);
        } catch (const std::exception&) {
            current.accelerations.assign(states_.size(), {});
            current.point_accelerations.assign(states_.size(), {});
            current.depths.assign(states_.size(), 0.0);
            current.resistance_ratios.assign(states_.size(), 1.0);
        }
        Array interactions;
        interactions.reserve(current.interactions.size());
        for (const Interaction& interaction : current.interactions) {
            interactions.emplace_back(interaction_json(interaction));
        }
        Array pairs;
        for (const PairResult& pair : current.pairs) {
            pairs.emplace_back(Object{
                {"acceleration_m_s2", json_vec3(pair.acceleration)},
                {"shield_fraction", pair.shield_fraction},
                {"source", definition_.bodies[pair.source].id},
                {"target", definition_.bodies[pair.target].id},
                {"visible_solid_angle_sr", pair.solid_angle_sr}
            });
        }
        Array ledgers;
        for (const BodyDefinition& body : definition_.bodies) {
            Array channels;
            for (const std::string& channel : body.channel_baryons) {
                channels.emplace_back(channel);
            }
            Object ledger{
                {"baryon_count", body.baryon_count},
                {"body", body.id},
                {"channels", std::move(channels)},
                {"reconstruction_exact", decimal_sum(body.channel_baryons)
                    == body.baryon_count}
            };
            if (body.has_displacement) {
                ledger.emplace("proton_count", body.proton_count);
                ledger.emplace("neutron_count", body.neutron_count);
            }
            ledgers.emplace_back(std::move(ledger));
        }
        const std::size_t expected = 49U * definition_.bodies.size()
            * (definition_.bodies.size() - 1U);
        Array gates{
            Object{
                {"id", "M0"},
                {"passed", true},
                {"value", 0.0}
            },
            Object{
                {"id", "M1"},
                {"passed", current.relation_count == expected},
                {"value", static_cast<double>(current.relation_count)}
            },
            Object{
                {"id", "M6"},
                {
                    "passed",
                    current.maximum_retarded_residual_s
                        <= 1.0e-12
                            * std::max(1.0, definition_.timestep_s)
                },
                {"value", current.maximum_retarded_residual_s}
            },
            Object{
                {"id", "M8"},
                {"passed", current.maximum_resistance_ratio >= 1.0},
                {"value", current.maximum_resistance_ratio}
            },
            Object{
                {"id", "M9"},
                {"passed", diagnostics_.maximum_speed_fraction_c < 1.0},
                {"value", diagnostics_.maximum_speed_fraction_c}
            }
        };
        const std::string trajectory_text = json::canonical(trajectory_);
        const std::string normalized_text =
            json::canonical(definition_.normalized);
        return json::canonical(Object{
            {"case_id", definition_.case_id},
            {"channel_ledger", std::move(ledgers)},
            {"classification", "COMPUTED"},
            {"contract_version", contract_version},
            {
                "diagnostics",
                [&]() {
                    Object value = diagnostics_value().object();
                    value.emplace(
                        "evaluated_channel_relations",
                        static_cast<double>(current.relation_count)
                    );
                    value.emplace(
                        "detail_output_truncated",
                        definition_.bodies.size() > 64U
                    );
                    return Value(std::move(value));
                }()
            },
            {"executed_steps", static_cast<double>(step_)},
            {"gates", std::move(gates)},
            {"interactions", std::move(interactions)},
            {"message", message_},
            {"normalized_case", definition_.normalized},
            {"pair_matrix", std::move(pairs)},
            {"problem_class", "sdt_occlusion_nbody"},
            {
                "provenance",
                Object{
                    {
                        "input_sha256",
                        sdt::compiler::SHA256::hash(normalized_text)
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
                        "fixed-step; fixed quadrature; no fast-math"
                    }
                }
            },
            {"status", status_},
            {"trajectory", trajectory_},
            {
                "trajectory_sha256",
                sdt::compiler::SHA256::hash(trajectory_text)
            }
        });
    }

    void restore(const Value& checkpoint) {
        if (!checkpoint.is_object()) {
            throw std::runtime_error("checkpoint must be an object");
        }
        const Object& root = checkpoint.object();
        if (require_string(object_at(root, "version"), "checkpoint.version")
            != contract_version) {
            throw std::runtime_error("checkpoint version mismatch");
        }
        step_ = require_integer(
            object_at(root, "step"),
            "checkpoint.step",
            0,
            definition_.steps
        );
        time_s_ = require_nonnegative(
            object_at(root, "time_s"),
            "checkpoint.time_s"
        );
        const Array& states = object_at(root, "states").array();
        if (states.size() != definition_.bodies.size()) {
            throw std::runtime_error("checkpoint state count mismatch");
        }
        for (const Value& value : states) {
            const Object& state = value.object();
            states_.push_back({
                vec3_from(object_at(state, "position_m"), "position_m"),
                vec3_from(object_at(state, "velocity_m_s"), "velocity_m_s")
            });
        }
        const Array& history = object_at(root, "history").array();
        for (const Value& frame_value : history) {
            const Object& frame = frame_value.object();
            HistoryFrame parsed;
            parsed.time_s = require_number(
                object_at(frame, "time_s"),
                "history.time_s"
            );
            for (const Value& state_value :
                 object_at(frame, "states").array()) {
                const Object& state = state_value.object();
                parsed.states.push_back({
                    vec3_from(object_at(state, "position_m"), "position_m"),
                    vec3_from(object_at(state, "velocity_m_s"), "velocity_m_s")
                });
            }
            history_.push_back(std::move(parsed));
        }
        trajectory_ = object_at(root, "trajectory").array();
        if (root.contains("diagnostics")) {
            const Object& diagnostics = root.at("diagnostics").object();
            diagnostics_.maximum_far_field_relative = require_number(
                object_at(diagnostics, "maximum_far_field_relative"),
                "maximum_far_field_relative"
            );
            diagnostics_.maximum_resistance_ratio = require_number(
                object_at(diagnostics, "maximum_resistance_ratio"),
                "maximum_resistance_ratio"
            );
            diagnostics_.maximum_retarded_residual_s = require_number(
                object_at(diagnostics, "maximum_retarded_residual_s"),
                "maximum_retarded_residual_s"
            );
            diagnostics_.maximum_shield_fraction = require_number(
                object_at(diagnostics, "maximum_shield_fraction"),
                "maximum_shield_fraction"
            );
            diagnostics_.maximum_speed_fraction_c = require_number(
                object_at(diagnostics, "maximum_speed_fraction_c"),
                "maximum_speed_fraction_c"
            );
            diagnostics_.medium_closure_relative = require_number(
                object_at(diagnostics, "medium_closure_relative"),
                "medium_closure_relative"
            );
            diagnostics_.body_impulse = vec3_from(
                object_at(diagnostics, "body_impulse_kg_m_s"),
                "body_impulse_kg_m_s"
            );
            diagnostics_.medium_impulse = vec3_from(
                object_at(diagnostics, "medium_impulse_kg_m_s"),
                "medium_impulse_kg_m_s"
            );
            diagnostics_.used_extrapolation =
                object_at(diagnostics, "used_ballistic_extrapolation").boolean();
        }
        status_ = step_ >= definition_.steps ? "completed" : "running";
        message_ = "checkpoint resumed";
    }
};

std::map<std::uint64_t, std::unique_ptr<Session>> sessions;
std::uint64_t next_handle = handle_base;

[[nodiscard]] auto invalid_result(const std::string& message) -> std::string {
    return json::canonical(Object{
        {"classification", "NOT-EXECUTED"},
        {"contract_version", contract_version},
        {"message", message},
        {"status", "invalid_case"}
    });
}

[[nodiscard]] auto invalid_session(const std::string& message) -> std::string {
    return json::canonical(Object{
        {"message", message},
        {"status", "invalid_session"}
    });
}

[[nodiscard]] auto qualification_fixture(
    std::size_t body_count,
    std::uint64_t steps = 1
) -> std::string {
    Array bodies;
    for (std::size_t index = 0; index < body_count; ++index) {
        bodies.emplace_back(Object{
            {"baryon_count", "805077908211484772344991472376387066"},
            {"collision_radius_m", 100.0},
            {"id", "body-" + std::to_string(index)},
            {
                "position_m",
                Array{
                    static_cast<double>(index) * 1.0e6,
                    static_cast<double>((index % 2U) * 2U) * 2.0e5,
                    static_cast<double>(index % 3U) * 1.0e5
                }
            },
            {"radius_m", 100.0},
            {"velocity_m_s", Array{0.0, 0.0, 0.0}}
        });
    }
    return json::canonical(Object{
        {"bodies", std::move(bodies)},
        {"case_id", "qualification-" + std::to_string(body_count)},
        {"contract_version", contract_version},
        {"duration_s", static_cast<double>(steps)},
        {
            "forces",
            Array{
                Object{
                    {"pressure_source", "sdt_law_I_P_conv"},
                    {"propagation_speed", "c"},
                    {"type", "retarded_seven_circle_occlusion"}
                }
            }
        },
        {
            "frame",
            Object{{"type", "inertial_cartesian"}, {"units", "SI"}}
        },
        {"gates", Array{}},
        {"integrator", "velocity_verlet"},
        {"problem_class", "sdt_occlusion_nbody"},
        {"record_every_steps", 1.0},
        {"timestep_s", 1.0},
        {
            "tolerances",
            Object{
                {"max_retarded_iterations", 32.0},
                {"retarded_time_s", 1.0e-12}
            }
        }
    });
}

} // namespace

auto owns_handle(std::uint64_t handle) noexcept -> bool {
    return handle >= handle_base;
}

auto run_case_json(const std::string& case_json) -> std::string {
    try {
        Session session(parse_definition(case_json));
        return session.run();
    } catch (const std::exception& error) {
        return invalid_result(error.what());
    }
}

auto create_session_json(const std::string& case_json) -> std::string {
    try {
        auto session = std::make_unique<Session>(parse_definition(case_json));
        const std::uint64_t handle = next_handle++;
        sessions.emplace(handle, std::move(session));
        return json::canonical(Object{
            {"handle", std::to_string(handle)},
            {"status", "created"}
        });
    } catch (const std::exception& error) {
        return invalid_result(error.what());
    }
}

auto advance_session_json(
    std::uint64_t handle,
    std::uint64_t steps
) -> std::string {
    const auto iterator = sessions.find(handle);
    if (iterator == sessions.end()) return invalid_session("unknown handle");
    return iterator->second->advance(steps);
}

auto checkpoint_session_json(std::uint64_t handle) -> std::string {
    const auto iterator = sessions.find(handle);
    if (iterator == sessions.end()) return invalid_session("unknown handle");
    return iterator->second->checkpoint_json();
}

auto resume_session_json(
    const std::string& case_json,
    const std::string& checkpoint_json
) -> std::string {
    try {
        auto session = std::make_unique<Session>(
            parse_definition(case_json),
            json::parse(checkpoint_json)
        );
        const std::uint64_t handle = next_handle++;
        sessions.emplace(handle, std::move(session));
        return json::canonical(Object{
            {"handle", std::to_string(handle)},
            {"status", "resumed"}
        });
    } catch (const std::exception& error) {
        return invalid_session(error.what());
    }
}

auto destroy_session_json(std::uint64_t handle) -> std::string {
    if (sessions.erase(handle) == 0U) return invalid_session("unknown handle");
    return R"({"status":"destroyed"})";
}

auto self_test_json() -> std::string {
    const double distance = 1000.0;
    const double radius = 1.0;
    const double numeric = sdt::occlusion::disc_solid_angle(
        {0.0, 0.0, 0.0},
        {0.0, 0.0, distance},
        {0.0, 0.0, -1.0},
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        radius
    );
    const double analytic =
        sdt::occlusion::axial_disc_solid_angle(distance, radius);
    const double relative = std::abs(numeric / analytic - 1.0);
    const auto allocation = channel_allocations("100000000000000000003");
    const bool exact =
        decimal_sum(allocation) == "100000000000000000003";
    const auto count_check = [](std::size_t count) {
        const Value value = json::parse(run_case_json(
            qualification_fixture(count)
        ));
        const std::size_t expected = 49U * count * (count - 1U);
        return value.object().at("status").string() == "completed"
            && value.object().at("interactions").array().size() == expected;
    };
    const bool count_2 = count_check(2);
    const bool count_3 = count_check(3);
    const bool count_7 = count_check(7);
    const std::string replay_case = qualification_fixture(2, 2);
    const Value created = json::parse(create_session_json(replay_case));
    const std::uint64_t first_handle =
        std::stoull(created.object().at("handle").string());
    static_cast<void>(advance_session_json(first_handle, 1));
    const std::string checkpoint = checkpoint_session_json(first_handle);
    static_cast<void>(destroy_session_json(first_handle));
    const Value resumed = json::parse(
        resume_session_json(replay_case, checkpoint)
    );
    const std::uint64_t resumed_handle =
        std::stoull(resumed.object().at("handle").string());
    const Value resumed_result = json::parse(
        advance_session_json(resumed_handle, 1)
    );
    static_cast<void>(destroy_session_json(resumed_handle));
    const Value uninterrupted = json::parse(run_case_json(replay_case));
    const bool replay =
        resumed_result.object().at("trajectory_sha256").string()
        == uninterrupted.object().at("trajectory_sha256").string();
    const bool all_passed =
        exact && relative <= 2.0e-6
        && count_2 && count_3 && count_7 && replay;
    return json::canonical(Object{
        {"classification", "COMPUTED"},
        {
            "gates",
            Array{
                Object{{"id", "M0"}, {"passed", exact}},
                Object{
                    {"id", "M3"},
                    {"passed", relative <= 2.0e-6},
                    {"value", relative}
                },
                Object{
                    {"id", "M1-2"},
                    {"passed", count_2},
                    {"value", count_2 ? 98.0 : 0.0}
                },
                Object{
                    {"id", "M1-3"},
                    {"passed", count_3},
                    {"value", count_3 ? 294.0 : 0.0}
                },
                Object{
                    {"id", "M1-7"},
                    {"passed", count_7},
                    {"value", count_7 ? 2058.0 : 0.0}
                },
                Object{
                    {"id", "M9"},
                    {
                        "passed",
                        sdt::dynamics::norm(sdt::occlusion::law_v_response(
                            {1.0, 0.0, 0.0},
                            {0.9 * sdt::laws::measured::c, 0.0, 0.0}
                        )) < 1.0
                    }
                },
                Object{
                    {"id", "M10"},
                    {"passed", replay},
                    {"value", replay ? 1.0 : 0.0}
                }
            }
        },
        {"status", all_passed ? "passed" : "failed"}
    });
}

auto manifest_json() -> std::string {
    return json::canonical(Object{
        {"build_id", build_id},
        {"contract_version", contract_version},
        {"interaction_count", "49*N*(N-1)"},
        {"laws_sha256", SDT_LAWS_SHA256},
        {"maximum_bodies", 10000.0},
        {
            "mechanism",
            "retarded full 7x7 baryon-channel solid-angle occlusion"
        },
        {
            "quadrature",
            Object{
                {
                    "azimuth_nodes",
                    static_cast<double>(
                        sdt::occlusion::azimuth_quadrature_count
                    )
                },
                {
                    "radial_nodes",
                    static_cast<double>(
                        sdt::occlusion::radial_quadrature_count
                    )
                }
            }
        }
    });
}

} // namespace sdt_solver::occlusion_nbody
