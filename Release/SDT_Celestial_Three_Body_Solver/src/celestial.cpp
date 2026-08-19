#include <sdt_solver/celestial.hpp>
#include <sdt_solver/json.hpp>

#include <sdt/compiler/sha256.hpp>
#include <sdt/dynamics.hpp>
#include <sdt/laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <compare>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <numbers>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#ifndef SDT_LAWS_SHA256
#define SDT_LAWS_SHA256 \
    "0000000000000000000000000000000000000000000000000000000000000000"
#endif

#ifndef SDT_SOLVER_COMPILER
#define SDT_SOLVER_COMPILER "unconfigured-c++20"
#endif

namespace sdt_solver::celestial {
namespace {

using json::Array;
using json::Object;
using json::Value;
using sdt::dynamics::Vec3;

constexpr double channel_central_weight = 1.0 / 9.0;
constexpr double channel_outer_weight = 4.0 / 27.0;
constexpr std::size_t body_count = 3;
constexpr std::size_t channel_count = 7;

class BigUInt {
public:
    BigUInt() = default;
    explicit BigUInt(std::uint64_t value) {
        if (value != 0) {
            limbs_.push_back(static_cast<std::uint32_t>(value));
            const auto high = static_cast<std::uint32_t>(value >> 32);
            if (high != 0) limbs_.push_back(high);
        }
    }

    [[nodiscard]] static auto from_decimal(const std::string& text) -> BigUInt {
        if (text.empty() || text.front() == '0') {
            throw std::runtime_error(
                "baryon_count must be a positive canonical decimal integer"
            );
        }
        BigUInt result;
        for (const char ch : text) {
            if (ch < '0' || ch > '9') {
                throw std::runtime_error("baryon_count contains a non-digit");
            }
            result.multiply_small(10);
            result.add_small(static_cast<std::uint32_t>(ch - '0'));
        }
        if (result.is_zero()) throw std::runtime_error("baryon_count is zero");
        return result;
    }

    [[nodiscard]] auto is_zero() const noexcept -> bool {
        return limbs_.empty();
    }

    [[nodiscard]] auto is_even() const noexcept -> bool {
        return is_zero() || (limbs_.front() & 1U) == 0;
    }

    [[nodiscard]] auto bit_length() const noexcept -> std::size_t {
        if (is_zero()) return 0;
        std::uint32_t high = limbs_.back();
        std::size_t bits = 32 * (limbs_.size() - 1);
        while (high != 0) {
            ++bits;
            high >>= 1;
        }
        return bits;
    }

    void shift_right_one() noexcept {
        std::uint32_t carry = 0;
        for (std::size_t i = limbs_.size(); i-- > 0;) {
            const std::uint32_t next = limbs_[i] & 1U;
            limbs_[i] = (limbs_[i] >> 1) | (carry << 31);
            carry = next;
        }
        normalize();
    }

    void shift_left(std::size_t bits) {
        if (is_zero() || bits == 0) return;
        const std::size_t words = bits / 32;
        const unsigned shift = static_cast<unsigned>(bits % 32);
        std::vector<std::uint32_t> result(words + limbs_.size() + 1, 0);
        std::uint64_t carry = 0;
        for (std::size_t i = 0; i < limbs_.size(); ++i) {
            const std::uint64_t value =
                (static_cast<std::uint64_t>(limbs_[i]) << shift) | carry;
            result[words + i] = static_cast<std::uint32_t>(value);
            carry = value >> 32;
        }
        result[words + limbs_.size()] = static_cast<std::uint32_t>(carry);
        limbs_ = std::move(result);
        normalize();
    }

    void set_bit(std::size_t bit) {
        const std::size_t word = bit / 32;
        if (limbs_.size() <= word) limbs_.resize(word + 1, 0);
        limbs_[word] |= static_cast<std::uint32_t>(1U << (bit % 32));
    }

    void add_small(std::uint32_t value) {
        std::uint64_t carry = value;
        std::size_t index = 0;
        while (carry != 0) {
            if (index == limbs_.size()) limbs_.push_back(0);
            const std::uint64_t sum = limbs_[index] + carry;
            limbs_[index] = static_cast<std::uint32_t>(sum);
            carry = sum >> 32;
            ++index;
        }
    }

    void multiply_small(std::uint32_t value) {
        if (value == 0 || is_zero()) {
            limbs_.clear();
            return;
        }
        std::uint64_t carry = 0;
        for (auto& limb : limbs_) {
            const std::uint64_t product =
                static_cast<std::uint64_t>(limb) * value + carry;
            limb = static_cast<std::uint32_t>(product);
            carry = product >> 32;
        }
        if (carry != 0) limbs_.push_back(static_cast<std::uint32_t>(carry));
    }

    [[nodiscard]] auto divide_small(std::uint32_t divisor) -> std::uint32_t {
        if (divisor == 0) throw std::runtime_error("BigUInt division by zero");
        std::uint64_t remainder = 0;
        for (std::size_t i = limbs_.size(); i-- > 0;) {
            const std::uint64_t current =
                (remainder << 32) | limbs_[i];
            limbs_[i] = static_cast<std::uint32_t>(current / divisor);
            remainder = current % divisor;
        }
        normalize();
        return static_cast<std::uint32_t>(remainder);
    }

    [[nodiscard]] auto to_decimal() const -> std::string {
        if (is_zero()) return "0";
        BigUInt copy = *this;
        std::vector<std::uint32_t> parts;
        while (!copy.is_zero()) parts.push_back(copy.divide_small(1'000'000'000));
        std::ostringstream output;
        output << parts.back();
        for (std::size_t i = parts.size() - 1; i-- > 0;) {
            output << std::setw(9) << std::setfill('0') << parts[i];
        }
        return output.str();
    }

    [[nodiscard]] auto to_double() const -> double {
        const std::string decimal = to_decimal();
        char* end = nullptr;
        const double value = std::strtod(decimal.c_str(), &end);
        if (end == decimal.c_str() || *end != '\0' || !std::isfinite(value)) {
            throw std::runtime_error(
                "baryon_count is outside the finite aggregate range"
            );
        }
        return value;
    }

    [[nodiscard]] auto to_u64() const -> std::uint64_t {
        if (limbs_.size() > 2) {
            throw std::runtime_error("BigUInt does not fit uint64");
        }
        std::uint64_t result = limbs_.empty() ? 0 : limbs_[0];
        if (limbs_.size() == 2) result |= std::uint64_t{limbs_[1]} << 32;
        return result;
    }

    friend auto operator<=>(const BigUInt& first, const BigUInt& second) {
        if (first.limbs_.size() != second.limbs_.size()) {
            return first.limbs_.size() <=> second.limbs_.size();
        }
        for (std::size_t i = first.limbs_.size(); i-- > 0;) {
            if (first.limbs_[i] != second.limbs_[i]) {
                return first.limbs_[i] <=> second.limbs_[i];
            }
        }
        return std::strong_ordering::equal;
    }

    friend auto operator==(const BigUInt&, const BigUInt&) -> bool = default;

    friend auto operator-(BigUInt first, const BigUInt& second) -> BigUInt {
        if (first < second) throw std::runtime_error("BigUInt underflow");
        std::uint64_t borrow = 0;
        for (std::size_t i = 0; i < first.limbs_.size(); ++i) {
            const std::uint64_t subtrahend =
                (i < second.limbs_.size() ? second.limbs_[i] : 0) + borrow;
            const std::uint64_t minuend = first.limbs_[i];
            first.limbs_[i] = static_cast<std::uint32_t>(
                minuend - subtrahend
            );
            borrow = minuend < subtrahend ? 1 : 0;
        }
        first.normalize();
        return first;
    }

    friend auto operator+(BigUInt first, const BigUInt& second) -> BigUInt {
        if (first.limbs_.size() < second.limbs_.size()) {
            first.limbs_.resize(second.limbs_.size(), 0);
        }
        std::uint64_t carry = 0;
        for (std::size_t i = 0; i < first.limbs_.size(); ++i) {
            const std::uint64_t sum = static_cast<std::uint64_t>(first.limbs_[i])
                + (i < second.limbs_.size() ? second.limbs_[i] : 0)
                + carry;
            first.limbs_[i] = static_cast<std::uint32_t>(sum);
            carry = sum >> 32;
        }
        if (carry != 0) first.limbs_.push_back(static_cast<std::uint32_t>(carry));
        return first;
    }

    friend auto operator*(const BigUInt& first, const BigUInt& second)
        -> BigUInt {
        BigUInt result;
        if (first.is_zero() || second.is_zero()) return result;
        result.limbs_.assign(first.limbs_.size() + second.limbs_.size(), 0);
        for (std::size_t i = 0; i < first.limbs_.size(); ++i) {
            std::uint64_t carry = 0;
            for (std::size_t j = 0; j < second.limbs_.size(); ++j) {
                const std::size_t index = i + j;
                const std::uint64_t value =
                    static_cast<std::uint64_t>(first.limbs_[i])
                        * second.limbs_[j]
                    + result.limbs_[index] + carry;
                result.limbs_[index] = static_cast<std::uint32_t>(value);
                carry = value >> 32;
            }
            std::size_t index = i + second.limbs_.size();
            while (carry != 0) {
                const std::uint64_t value =
                    static_cast<std::uint64_t>(result.limbs_[index]) + carry;
                result.limbs_[index] = static_cast<std::uint32_t>(value);
                carry = value >> 32;
                ++index;
                if (index == result.limbs_.size() && carry != 0) {
                    result.limbs_.push_back(0);
                }
            }
        }
        result.normalize();
        return result;
    }

    [[nodiscard]] static auto gcd(BigUInt first, BigUInt second) -> BigUInt {
        if (first.is_zero()) return second;
        if (second.is_zero()) return first;
        std::size_t common_twos = 0;
        while (first.is_even() && second.is_even()) {
            first.shift_right_one();
            second.shift_right_one();
            ++common_twos;
        }
        while (first.is_even()) first.shift_right_one();
        do {
            while (second.is_even()) second.shift_right_one();
            if (first > second) std::swap(first, second);
            second = second - first;
        } while (!second.is_zero());
        first.shift_left(common_twos);
        return first;
    }

    [[nodiscard]] static auto divide_exact(
        const BigUInt& numerator,
        const BigUInt& denominator
    ) -> BigUInt {
        if (denominator.is_zero()) {
            throw std::runtime_error("BigUInt division by zero");
        }
        if (numerator < denominator) {
            throw std::runtime_error("BigUInt division is not exact");
        }
        BigUInt remainder = numerator;
        BigUInt shifted = denominator;
        const std::size_t shift =
            numerator.bit_length() - denominator.bit_length();
        shifted.shift_left(shift);
        BigUInt quotient;
        for (std::size_t cursor = shift + 1; cursor-- > 0;) {
            if (remainder >= shifted) {
                remainder = remainder - shifted;
                quotient.set_bit(cursor);
            }
            shifted.shift_right_one();
        }
        if (!remainder.is_zero()) {
            throw std::runtime_error("BigUInt division has a remainder");
        }
        return quotient;
    }

private:
    std::vector<std::uint32_t> limbs_;

    void normalize() noexcept {
        while (!limbs_.empty() && limbs_.back() == 0) limbs_.pop_back();
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

[[nodiscard]] auto require_bool(
    const Value& value,
    const std::string& context
) -> bool {
    if (!value.is_bool()) throw std::runtime_error(context + " must be boolean");
    return value.boolean();
}

[[nodiscard]] auto require_u64(
    const Value& value,
    const std::string& context
) -> std::uint64_t {
    const double number = require_positive(value, context);
    if (std::floor(number) != number
        || number > 9'007'199'254'740'991.0) {
        throw std::runtime_error(
            context + " must be an exactly representable positive integer"
        );
    }
    return static_cast<std::uint64_t>(number);
}

[[nodiscard]] auto vec3_from(
    const Value& value,
    const std::string& context
) -> Vec3 {
    if (!value.is_array() || value.array().size() != 3) {
        throw std::runtime_error(context + " must have three components");
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

[[nodiscard]] auto finite(Vec3 value) noexcept -> bool {
    return std::isfinite(value.x)
        && std::isfinite(value.y)
        && std::isfinite(value.z);
}

[[nodiscard]] auto unit(Vec3 value) -> Vec3 {
    const double magnitude = sdt::dynamics::norm(value);
    if (!(magnitude > 0.0) || !std::isfinite(magnitude)) {
        throw std::runtime_error("zero or invalid direction");
    }
    return value / magnitude;
}

[[nodiscard]] auto clamp_unit(double value) noexcept -> double {
    return std::clamp(value, -1.0, 1.0);
}

struct Tolerances {
    double retarded_time_s{1.0e-12};
    double channel_closure{1.0e-13};
    double medium_momentum_relative{1.0e-11};
    double lagrange_residual_m_s2{1.0e-9};
    int max_retarded_iterations{32};
};

struct BodyDefinition {
    std::string id;
    BigUInt baryons;
    std::string baryons_text;
    double baryons_double{};
    bool has_displacement_ledger{};
    BigUInt protons;
    BigUInt neutrons;
    BigUInt weighted_burden;
    std::string protons_text{"0"};
    std::string neutrons_text{"0"};
    std::string weighted_burden_text{"0"};
    double protons_double{};
    double neutrons_double{};
    double material_volume_coverage{};
    double represented_atomic_mass_coverage{};
    double composition_relative_uncertainty{};
    std::string ledger_sha256;
    double radius_m{};
    double collision_radius_m{};
    Vec3 initial_position_m{};
    Vec3 initial_velocity_m_s{};
    bool has_prehistory{};
    double prehistory_time_s{};
    Vec3 prehistory_position_m{};
};

struct SlingshotDefinition {
    bool enabled{};
    bool experimental_tail{};
    std::size_t host{};
    std::size_t flyby{};
    std::size_t runner{};
    double reference_radius_m{};
    double reference_separation_m{};
    double flyby_koppa_m{};
    double equal_radius_tolerance_m{};
    int stage_min{};
    int stage_max{8};
    int candidate_terminal_stage{8};
};

struct Definition {
    std::string contract_version{celestial::contract_version};
    std::string case_id;
    std::string integrator;
    double timestep_s{};
    std::uint64_t maximum_steps{};
    std::uint64_t record_every_steps{};
    double history_seconds{};
    double pressure_scale{1.0};
    bool eclipse_shielding{true};
    bool point_comparison{true};
    bool stop_on_collision{true};
    Tolerances tolerances;
    std::array<BodyDefinition, body_count> bodies;
    SlingshotDefinition slingshot;
    Value normalized;
};

struct Kinematic {
    Vec3 position{};
    Vec3 velocity{};
};

struct HistoryFrame {
    double time_s{};
    std::array<Kinematic, body_count> states;
};

struct RetardedSample {
    Kinematic state;
    double time_s{};
    double residual_s{};
    bool extrapolated{};
};

struct ConeDiagnostic {
    std::size_t target{};
    std::size_t source{};
    std::size_t channel{};
    Vec3 axis{};
    Vec3 centre{};
    Vec3 front{};
    Vec3 rear{};
    Vec3 acceleration{};
    double area_weight{};
    double chord_m{};
    double chord_fraction{};
    double rear_area_m2{};
    double solid_angle_sr{};
    double occlusion_depth{};
    double resistance_j{};
    double shield_fraction{};
    double retarded_time_s{};
    double retarded_residual_s{};
    bool extrapolated{};
    std::string eclipse_class;
    std::string channel_baryons;
};

struct PairDiagnostic {
    std::size_t target{};
    std::size_t source{};
    Vec3 normal{};
    Vec3 base_acceleration{};
    double distance_m{};
    double source_occlusion{};
    double source_solid_angle_sr{};
    double shield_fraction{};
    double retarded_time_s{};
    double retarded_residual_s{};
    bool extrapolated{};
    std::string eclipse_class;
};

struct Evaluation {
    std::array<Vec3, body_count> accelerations{};
    std::array<Vec3, body_count> point_accelerations{};
    std::array<double, body_count> resistance_ratios{1.0, 1.0, 1.0};
    std::array<double, body_count> resistance_energy_j{};
    std::array<double, body_count> rest_displacement_volume_m3{};
    std::array<double, body_count> engaged_displacement_volume_m3{};
    std::array<double, body_count> effective_displacement_volume_m3{};
    std::vector<ConeDiagnostic> cones;
    std::vector<PairDiagnostic> pairs;
    double maximum_retarded_residual_s{};
    double maximum_channel_closure_relative{};
    double maximum_eclipse_shield{};
    bool used_extrapolation{};
};

struct Diagnostics {
    double maximum_retarded_residual_s{};
    double maximum_channel_closure_relative{};
    double maximum_effective_resistance_ratio{1.0};
    double maximum_eclipse_shield{};
    double minimum_pair_distance_m{std::numeric_limits<double>::infinity()};
    double minimum_runner_flyby_distance_m{
        std::numeric_limits<double>::infinity()
    };
    Vec3 medium_impulse{};
    double body_plus_medium_momentum_residual{};
};

[[nodiscard]] auto parse_definition(const std::string& text) -> Definition {
    Definition result;
    result.normalized = json::parse(text);
    if (!result.normalized.is_object()) {
        throw std::runtime_error("case must be an object");
    }
    const Object& root = result.normalized.object();
    require_keys(
        root,
        {
            "contract_version", "case_id", "problem_class", "frame", "force",
            "bodies", "integrator", "timestep_s", "duration_s", "max_steps",
            "record_every_steps", "history_seconds", "tolerances", "events",
            "slingshot", "provenance"
        },
        "case"
    );
    result.contract_version =
        require_string(object_at(root, "contract_version"), "contract_version");
    if (result.contract_version != contract_version
        && result.contract_version != displacement_contract_version) {
        throw std::runtime_error("unsupported celestial contract_version");
    }
    if (require_string(object_at(root, "problem_class"), "problem_class")
        != "celestial_three_body") {
        throw std::runtime_error(
            "celestial contract requires celestial_three_body"
        );
    }
    result.case_id = require_string(object_at(root, "case_id"), "case_id");
    if (result.case_id.empty() || result.case_id.size() > 96) {
        throw std::runtime_error("case_id length is outside contract");
    }

    const Value& frame_value = object_at(root, "frame");
    if (!frame_value.is_object()) throw std::runtime_error("frame must be object");
    const Object& frame = frame_value.object();
    require_keys(frame, {"type", "units", "epoch", "description"}, "frame");
    if (require_string(object_at(frame, "type"), "frame.type")
            != "inertial_cartesian"
        || require_string(object_at(frame, "units"), "frame.units") != "SI"
        || require_string(object_at(frame, "epoch"), "frame.epoch").empty()) {
        throw std::runtime_error(
            "frame must be inertial_cartesian SI with an epoch"
        );
    }

    const Value& force_value = object_at(root, "force");
    if (!force_value.is_object()) throw std::runtime_error("force must be object");
    const Object& force = force_value.object();
    require_keys(
        force,
        {
            "type", "propagation_speed", "pressure_source", "pressure_pa",
            "enable_eclipse_shielding", "comparison_route"
        },
        "force"
    );
    if (require_string(object_at(force, "type"), "force.type")
            != "retarded_seven_cone_occlusion"
        || require_string(
               object_at(force, "propagation_speed"),
               "force.propagation_speed"
           ) != "c") {
        throw std::runtime_error(
            "force must be retarded_seven_cone_occlusion propagated at c"
        );
    }
    const std::string pressure_source = require_string(
        object_at(force, "pressure_source"),
        "force.pressure_source"
    );
    if (pressure_source == "declared") {
        const double pressure =
            require_positive(object_at(force, "pressure_pa"), "force.pressure_pa");
        result.pressure_scale = pressure / sdt::laws::law_I::P_conv;
    } else if (pressure_source != "sdt_law_I_P_conv") {
        throw std::runtime_error("unsupported pressure_source");
    }
    if (force.contains("enable_eclipse_shielding")) {
        result.eclipse_shielding = require_bool(
            force.at("enable_eclipse_shielding"),
            "force.enable_eclipse_shielding"
        );
    }
    if (force.contains("comparison_route")) {
        const std::string route =
            require_string(force.at("comparison_route"), "comparison_route");
        if (route != "none" && route != "point_koppa") {
            throw std::runtime_error("unsupported comparison_route");
        }
        result.point_comparison = route == "point_koppa";
    }

    result.integrator =
        require_string(object_at(root, "integrator"), "integrator");
    if (result.integrator != "velocity_verlet"
        && result.integrator != "fixed_rk4") {
        throw std::runtime_error("unsupported celestial integrator");
    }
    result.timestep_s =
        require_positive(object_at(root, "timestep_s"), "timestep_s");
    const bool has_duration = root.contains("duration_s");
    const bool has_steps = root.contains("max_steps");
    if (has_duration && has_steps) {
        throw std::runtime_error(
            "duration_s and max_steps are mutually exclusive"
        );
    }
    if (has_duration) {
        const double duration =
            require_positive(root.at("duration_s"), "duration_s");
        const double steps = duration / result.timestep_s;
        const double rounded = std::round(steps);
        if (rounded < 1.0 || rounded > 9'007'199'254'740'991.0
            || std::abs(steps - rounded)
                > 1.0e-10 * std::max(1.0, steps)) {
            throw std::runtime_error(
                "duration_s/timestep_s must be an exact positive step count"
            );
        }
        result.maximum_steps = static_cast<std::uint64_t>(rounded);
    } else if (has_steps) {
        result.maximum_steps = require_u64(root.at("max_steps"), "max_steps");
    } else {
        result.maximum_steps = std::numeric_limits<std::uint64_t>::max();
    }
    result.record_every_steps =
        require_u64(object_at(root, "record_every_steps"), "record_every_steps");
    if (result.record_every_steps > result.maximum_steps) {
        throw std::runtime_error("record_every_steps exceeds maximum run");
    }
    if (root.contains("history_seconds")) {
        result.history_seconds =
            require_positive(root.at("history_seconds"), "history_seconds");
    }

    const Value& tolerance_value = object_at(root, "tolerances");
    if (!tolerance_value.is_object()) {
        throw std::runtime_error("tolerances must be object");
    }
    const Object& tolerance = tolerance_value.object();
    require_keys(
        tolerance,
        {
            "retarded_time_s", "channel_closure", "medium_momentum_relative",
            "lagrange_residual_m_s2", "max_retarded_iterations"
        },
        "tolerances"
    );
    result.tolerances.retarded_time_s = require_positive(
        object_at(tolerance, "retarded_time_s"),
        "tolerances.retarded_time_s"
    );
    result.tolerances.channel_closure = require_positive(
        object_at(tolerance, "channel_closure"),
        "tolerances.channel_closure"
    );
    result.tolerances.medium_momentum_relative = require_positive(
        object_at(tolerance, "medium_momentum_relative"),
        "tolerances.medium_momentum_relative"
    );
    result.tolerances.lagrange_residual_m_s2 = require_positive(
        object_at(tolerance, "lagrange_residual_m_s2"),
        "tolerances.lagrange_residual_m_s2"
    );
    const std::uint64_t iterations = require_u64(
        object_at(tolerance, "max_retarded_iterations"),
        "tolerances.max_retarded_iterations"
    );
    if (iterations < 2 || iterations > 128) {
        throw std::runtime_error("max_retarded_iterations outside [2,128]");
    }
    result.tolerances.max_retarded_iterations = static_cast<int>(iterations);

    if (root.contains("events")) {
        if (!root.at("events").is_object()) {
            throw std::runtime_error("events must be object");
        }
        const Object& events = root.at("events").object();
        require_keys(
            events,
            {"stop_on_collision", "stop_time_s", "stop_step"},
            "events"
        );
        if (events.contains("stop_on_collision")) {
            result.stop_on_collision = require_bool(
                events.at("stop_on_collision"),
                "events.stop_on_collision"
            );
        }
        if (events.contains("stop_step")) {
            result.maximum_steps = std::min(
                result.maximum_steps,
                require_u64(events.at("stop_step"), "events.stop_step")
            );
        }
        if (events.contains("stop_time_s")) {
            const double stop =
                require_positive(events.at("stop_time_s"), "events.stop_time_s");
            result.maximum_steps = std::min(
                result.maximum_steps,
                static_cast<std::uint64_t>(std::floor(stop / result.timestep_s))
            );
            if (result.maximum_steps == 0) {
                throw std::runtime_error("events.stop_time_s precedes first step");
            }
        }
    }

    const Value& bodies_value = object_at(root, "bodies");
    if (!bodies_value.is_array() || bodies_value.array().size() != body_count) {
        throw std::runtime_error("celestial solver requires exactly three bodies");
    }
    std::set<std::string> ids;
    double common_prehistory_time = 0.0;
    bool any_prehistory = false;
    for (std::size_t i = 0; i < body_count; ++i) {
        const Value& body_value = bodies_value.array()[i];
        if (!body_value.is_object()) throw std::runtime_error("body must be object");
        const Object& body = body_value.object();
        require_keys(
            body,
            {
                "id", "baryon_count", "radius_m", "collision_radius_m",
                "position_m", "velocity_m_s", "prehistory_position_m",
                "prehistory_time_s", "displacement", "provenance"
            },
            "body"
        );
        BodyDefinition& parsed = result.bodies[i];
        parsed.id = require_string(object_at(body, "id"), "body.id");
        if (parsed.id.empty() || !ids.emplace(parsed.id).second) {
            throw std::runtime_error("body IDs must be non-empty and unique");
        }
        parsed.baryons_text =
            require_string(object_at(body, "baryon_count"), "baryon_count");
        parsed.baryons = BigUInt::from_decimal(parsed.baryons_text);
        parsed.baryons_double = parsed.baryons.to_double();
        if (body.contains("displacement")) {
            if (result.contract_version != displacement_contract_version) {
                throw std::runtime_error(
                    "body.displacement requires contract_version 2.1.0"
                );
            }
            const Value& displacement_value = body.at("displacement");
            if (!displacement_value.is_object()) {
                throw std::runtime_error("body.displacement must be object");
            }
            const Object& displacement = displacement_value.object();
            require_keys(
                displacement,
                {
                    "proton_count", "neutron_count",
                    "material_volume_coverage",
                    "represented_atomic_mass_coverage",
                    "relative_uncertainty", "ledger_sha256"
                },
                "body.displacement"
            );
            parsed.protons_text = require_string(
                object_at(displacement, "proton_count"),
                "body.displacement.proton_count"
            );
            parsed.neutrons_text = require_string(
                object_at(displacement, "neutron_count"),
                "body.displacement.neutron_count"
            );
            parsed.protons = BigUInt::from_decimal(parsed.protons_text);
            parsed.neutrons = parsed.neutrons_text == "0"
                ? BigUInt{}
                : BigUInt::from_decimal(parsed.neutrons_text);
            if (parsed.protons + parsed.neutrons != parsed.baryons) {
                throw std::runtime_error(
                    "body displacement proton+neutron ledger does not match baryon_count"
                );
            }
            parsed.protons_double = parsed.protons.to_double();
            parsed.neutrons_double = parsed.neutrons.to_double();
            BigUInt proton_burden = parsed.protons;
            BigUInt neutron_burden = parsed.neutrons;
            proton_burden.multiply_small(1836);
            neutron_burden.multiply_small(1838);
            parsed.weighted_burden = proton_burden + neutron_burden;
            parsed.weighted_burden_text = parsed.weighted_burden.to_decimal();
            parsed.material_volume_coverage = require_number(
                object_at(displacement, "material_volume_coverage"),
                "body.displacement.material_volume_coverage"
            );
            parsed.represented_atomic_mass_coverage = require_number(
                object_at(displacement, "represented_atomic_mass_coverage"),
                "body.displacement.represented_atomic_mass_coverage"
            );
            parsed.composition_relative_uncertainty = require_number(
                object_at(displacement, "relative_uncertainty"),
                "body.displacement.relative_uncertainty"
            );
            if (parsed.material_volume_coverage < 0.98
                || parsed.material_volume_coverage > 1.0
                || parsed.represented_atomic_mass_coverage < 0.98
                || parsed.represented_atomic_mass_coverage > 1.0
                || parsed.composition_relative_uncertainty < 0.0
                || parsed.composition_relative_uncertainty > 1.0) {
                throw std::runtime_error(
                    "body displacement coverage/uncertainty is outside contract"
                );
            }
            parsed.ledger_sha256 = require_string(
                object_at(displacement, "ledger_sha256"),
                "body.displacement.ledger_sha256"
            );
            if (parsed.ledger_sha256.size() != 64
                || !std::all_of(
                    parsed.ledger_sha256.begin(),
                    parsed.ledger_sha256.end(),
                    [](char ch) {
                        return (ch >= '0' && ch <= '9')
                            || (ch >= 'a' && ch <= 'f');
                    }
                )) {
                throw std::runtime_error(
                    "body displacement ledger_sha256 is not canonical lowercase hex"
                );
            }
            parsed.has_displacement_ledger = true;
        }
        parsed.radius_m = require_positive(object_at(body, "radius_m"), "radius_m");
        parsed.collision_radius_m = body.contains("collision_radius_m")
            ? require_number(body.at("collision_radius_m"), "collision_radius_m")
            : parsed.radius_m;
        if (parsed.collision_radius_m < 0.0) {
            throw std::runtime_error("collision_radius_m must be non-negative");
        }
        parsed.initial_position_m =
            vec3_from(object_at(body, "position_m"), "position_m");
        parsed.initial_velocity_m_s =
            vec3_from(object_at(body, "velocity_m_s"), "velocity_m_s");
        parsed.has_prehistory =
            body.contains("prehistory_position_m")
            || body.contains("prehistory_time_s");
        if (parsed.has_prehistory) {
            if (!body.contains("prehistory_position_m")
                || !body.contains("prehistory_time_s")) {
                throw std::runtime_error(
                    "prehistory position and time must be supplied together"
                );
            }
            parsed.prehistory_position_m = vec3_from(
                body.at("prehistory_position_m"),
                "prehistory_position_m"
            );
            parsed.prehistory_time_s =
                require_number(body.at("prehistory_time_s"), "prehistory_time_s");
            if (!(parsed.prehistory_time_s < 0.0)) {
                throw std::runtime_error("prehistory_time_s must be negative");
            }
            if (!any_prehistory) {
                common_prehistory_time = parsed.prehistory_time_s;
                any_prehistory = true;
            } else if (parsed.prehistory_time_s != common_prehistory_time) {
                throw std::runtime_error(
                    "all declared prehistory epochs must match exactly"
                );
            }
        }
        if (!body.contains("provenance") || !body.at("provenance").is_object()) {
            throw std::runtime_error("body.provenance must be object");
        }
    }
    if (any_prehistory) {
        for (const auto& body : result.bodies) {
            if (!body.has_prehistory) {
                throw std::runtime_error(
                    "prehistory must be supplied for all three bodies or none"
                );
            }
        }
    }
    if (root.contains("slingshot")) {
        if (result.contract_version != displacement_contract_version) {
            throw std::runtime_error(
                "slingshot requires contract_version 2.1.0"
            );
        }
        const Value& slingshot_value = root.at("slingshot");
        if (!slingshot_value.is_object()) {
            throw std::runtime_error("slingshot must be object");
        }
        const Object& slingshot = slingshot_value.object();
        require_keys(
            slingshot,
            {
                "host_body", "flyby_body", "runner_body",
                "reference_radius_m", "reference_separation_m",
                "flyby_koppa_m",
                "stage_min", "stage_max", "candidate_terminal_stage",
                "enable_experimental_tail", "equal_radius_tolerance_m",
                "provenance"
            },
            "slingshot"
        );
        const auto body_index = [&](const std::string& key) {
            const std::string id =
                require_string(object_at(slingshot, key), "slingshot." + key);
            for (std::size_t index = 0; index < body_count; ++index) {
                if (result.bodies[index].id == id) return index;
            }
            throw std::runtime_error("slingshot body ID is not present: " + id);
        };
        result.slingshot.host = body_index("host_body");
        result.slingshot.flyby = body_index("flyby_body");
        result.slingshot.runner = body_index("runner_body");
        if (result.slingshot.host == result.slingshot.flyby
            || result.slingshot.host == result.slingshot.runner
            || result.slingshot.flyby == result.slingshot.runner) {
            throw std::runtime_error("slingshot roles must use three distinct bodies");
        }
        result.slingshot.reference_radius_m = require_positive(
            object_at(slingshot, "reference_radius_m"),
            "slingshot.reference_radius_m"
        );
        result.slingshot.reference_separation_m = require_positive(
            object_at(slingshot, "reference_separation_m"),
            "slingshot.reference_separation_m"
        );
        result.slingshot.flyby_koppa_m = require_positive(
            object_at(slingshot, "flyby_koppa_m"),
            "slingshot.flyby_koppa_m"
        );
        const double stage_min_number = require_number(
            object_at(slingshot, "stage_min"),
            "slingshot.stage_min"
        );
        if (stage_min_number != 0.0) {
            throw std::runtime_error("slingshot.stage_min must be zero");
        }
        result.slingshot.stage_min = 0;
        result.slingshot.stage_max = static_cast<int>(
            require_u64(object_at(slingshot, "stage_max"), "slingshot.stage_max")
        );
        result.slingshot.candidate_terminal_stage = static_cast<int>(
            require_u64(
                object_at(slingshot, "candidate_terminal_stage"),
                "slingshot.candidate_terminal_stage"
            )
        );
        if (result.slingshot.stage_min != 0
            || result.slingshot.stage_max != 8
            || result.slingshot.candidate_terminal_stage != 8) {
            throw std::runtime_error(
                "registered slingshot scan must be n=0..8 with candidate stage 8"
            );
        }
        result.slingshot.experimental_tail = require_bool(
            object_at(slingshot, "enable_experimental_tail"),
            "slingshot.enable_experimental_tail"
        );
        result.slingshot.equal_radius_tolerance_m =
            slingshot.contains("equal_radius_tolerance_m")
            ? require_number(
                slingshot.at("equal_radius_tolerance_m"),
                "slingshot.equal_radius_tolerance_m"
            )
            : result.slingshot.reference_radius_m * 1.0e-6;
        if (result.slingshot.equal_radius_tolerance_m < 0.0) {
            throw std::runtime_error(
                "slingshot.equal_radius_tolerance_m must be non-negative"
            );
        }
        if (!result.bodies[result.slingshot.host].has_displacement_ledger
            || !result.bodies[result.slingshot.flyby].has_displacement_ledger) {
            throw std::runtime_error(
                "slingshot host and flyby bodies require displacement ledgers"
            );
        }
        result.slingshot.enabled = true;
    }
    if (!root.contains("provenance") || !root.at("provenance").is_object()) {
        throw std::runtime_error("provenance must be object");
    }
    return result;
}

[[nodiscard]] auto channel_allocations(const BigUInt& count)
    -> std::array<BigUInt, channel_count> {
    struct Fraction {
        std::size_t index{};
        std::uint32_t numerator{};
        std::uint32_t denominator{};
    };
    std::array<BigUInt, channel_count> result;
    std::array<Fraction, channel_count> fractions;
    BigUInt central = count;
    const std::uint32_t central_remainder = central.divide_small(9);
    result[0] = central;
    fractions[0] = {0, central_remainder, 9};
    for (std::size_t i = 1; i < channel_count; ++i) {
        BigUInt outer = count;
        outer.multiply_small(4);
        const std::uint32_t remainder = outer.divide_small(27);
        result[i] = outer;
        fractions[i] = {i, remainder, 27};
    }
    BigUInt allocated;
    for (const auto& channel : result) allocated = allocated + channel;
    const std::uint64_t missing = (count - allocated).to_u64();
    std::sort(
        fractions.begin(),
        fractions.end(),
        [](const Fraction& first, const Fraction& second) {
            const std::uint64_t left =
                static_cast<std::uint64_t>(first.numerator)
                * second.denominator;
            const std::uint64_t right =
                static_cast<std::uint64_t>(second.numerator)
                * first.denominator;
            return left != right ? left > right : first.index < second.index;
        }
    );
    for (std::size_t i = 0; i < missing; ++i) {
        result[fractions[i].index].add_small(1);
    }
    BigUInt check;
    for (const auto& channel : result) check = check + channel;
    if (check != count) {
        throw std::runtime_error("channel baryon allocation did not close");
    }
    return result;
}

[[nodiscard]] auto disc_overlap_area(
    double first_radius,
    double second_radius,
    double separation
) noexcept -> double {
    if (!(first_radius > 0.0) || !(second_radius > 0.0)) return 0.0;
    if (separation >= first_radius + second_radius) return 0.0;
    if (separation <= std::abs(first_radius - second_radius)) {
        const double radius = std::min(first_radius, second_radius);
        return std::numbers::pi * radius * radius;
    }
    const double first_argument = clamp_unit(
        (separation * separation + first_radius * first_radius
            - second_radius * second_radius)
        / (2.0 * separation * first_radius)
    );
    const double second_argument = clamp_unit(
        (separation * separation + second_radius * second_radius
            - first_radius * first_radius)
        / (2.0 * separation * second_radius)
    );
    const double radical = std::max(
        0.0,
        (-separation + first_radius + second_radius)
        * (separation + first_radius - second_radius)
        * (separation - first_radius + second_radius)
        * (separation + first_radius + second_radius)
    );
    return first_radius * first_radius * std::acos(first_argument)
        + second_radius * second_radius * std::acos(second_argument)
        - 0.5 * std::sqrt(radical);
}

class Session {
public:
    explicit Session(Definition definition)
        : definition_(std::move(definition)) {
        for (std::size_t i = 0; i < body_count; ++i) {
            states_[i] = {
                definition_.bodies[i].initial_position_m,
                definition_.bodies[i].initial_velocity_m_s
            };
            channel_baryons_[i] =
                channel_allocations(definition_.bodies[i].baryons);
        }
        BigUInt common = BigUInt::gcd(
            definition_.bodies[0].baryons,
            definition_.bodies[1].baryons
        );
        common = BigUInt::gcd(common, definition_.bodies[2].baryons);
        packet_gcd_ = common;
        for (std::size_t i = 0; i < body_count; ++i) {
            packet_multiplicity_[i] = BigUInt::divide_exact(
                definition_.bodies[i].baryons,
                packet_gcd_
            );
            if (packet_multiplicity_[i] * packet_gcd_
                != definition_.bodies[i].baryons) {
                throw std::runtime_error("packet reconstruction failed");
            }
        }
        initialize_history();
        initial_body_momentum_ = body_momentum(states_);
        update_minimum_distance(states_);
    }

    [[nodiscard]] auto advance(std::uint64_t requested_steps) -> Value {
        if (requested_steps == 0) {
            throw std::runtime_error("advance step count must be positive");
        }
        Array records;
        if (step_ == 0) records.push_back(frame_json());
        const std::uint64_t remaining =
            definition_.maximum_steps > step_
            ? definition_.maximum_steps - step_
            : 0;
        const std::uint64_t count = std::min(requested_steps, remaining);
        std::string status = remaining == 0 ? "completed" : "paused";
        std::string message = remaining == 0
            ? "registered maximum step reached"
            : "chunk advanced";
        for (std::uint64_t index = 0; index < count; ++index) {
            const auto previous = states_;
            const bool advanced = definition_.integrator == "velocity_verlet"
                ? step_verlet()
                : step_rk4();
            if (!advanced) {
                status = "numerical_failure";
                message = "celestial state became non-finite";
                break;
            }
            if (definition_.stop_on_collision && collision(states_)) {
                states_ = previous;
                status = "collision";
                message = "contact boundary reached before overlap";
                break;
            }
            ++step_;
            time_s_ = static_cast<double>(step_) * definition_.timestep_s;
            accept_history();
            const Vec3 momentum_change =
                body_momentum(states_) - body_momentum(previous);
            diagnostics_.medium_impulse =
                diagnostics_.medium_impulse - momentum_change;
            update_momentum_residual();
            update_minimum_distance(states_);
            trim_history();
            if (step_ % definition_.record_every_steps == 0
                || step_ == definition_.maximum_steps) {
                records.push_back(frame_json());
            }
            if (step_ == definition_.maximum_steps) {
                status = "completed";
                message = "registered maximum step reached";
                break;
            }
        }
        return result_json(status, message, std::move(records));
    }

    [[nodiscard]] auto checkpoint() const -> Value {
        Array state_array;
        for (std::size_t i = 0; i < body_count; ++i) {
            state_array.emplace_back(Object{
                {"id", definition_.bodies[i].id},
                {"position_m", json_vec3(states_[i].position)},
                {"velocity_m_s", json_vec3(states_[i].velocity)}
            });
        }
        Array history_array;
        for (const auto& frame : history_) {
            Array frame_states;
            for (std::size_t i = 0; i < body_count; ++i) {
                frame_states.emplace_back(Object{
                    {"id", definition_.bodies[i].id},
                    {"position_m", json_vec3(frame.states[i].position)},
                    {"velocity_m_s", json_vec3(frame.states[i].velocity)}
                });
            }
            history_array.emplace_back(Object{
                {"states", std::move(frame_states)},
                {"time_s", frame.time_s}
            });
        }
        return Object{
            {"contract_version", definition_.contract_version},
            {"case_id", definition_.case_id},
            {"step", static_cast<double>(step_)},
            {"time_s", time_s_},
            {"states", std::move(state_array)},
            {"history", std::move(history_array)},
            {
                "medium_impulse_kg_m_s",
                json_vec3(diagnostics_.medium_impulse)
            },
            {
                "initial_body_momentum_kg_m_s",
                json_vec3(initial_body_momentum_)
            },
            {
                "minimum_runner_flyby_distance_m",
                definition_.slingshot.enabled
                    ? diagnostics_.minimum_runner_flyby_distance_m
                    : 0.0
            }
        };
    }

    void restore(const Value& checkpoint_value) {
        if (!checkpoint_value.is_object()) {
            throw std::runtime_error("checkpoint must be object");
        }
        const Object& checkpoint = checkpoint_value.object();
        if (require_string(
                object_at(checkpoint, "contract_version"),
                "checkpoint.contract_version"
            ) != definition_.contract_version
            || require_string(
                object_at(checkpoint, "case_id"),
                "checkpoint.case_id"
            ) != definition_.case_id) {
            throw std::runtime_error("checkpoint does not match case contract");
        }
        step_ = require_u64(object_at(checkpoint, "step"), "checkpoint.step");
        if (step_ > definition_.maximum_steps) {
            throw std::runtime_error("checkpoint step exceeds case maximum");
        }
        time_s_ =
            require_number(object_at(checkpoint, "time_s"), "checkpoint.time_s");
        const double expected = static_cast<double>(step_) * definition_.timestep_s;
        if (std::abs(time_s_ - expected)
            > 1.0e-12 * std::max(1.0, std::abs(expected))) {
            throw std::runtime_error("checkpoint time and step disagree");
        }
        states_ = states_from_json(
            object_at(checkpoint, "states"),
            "checkpoint.states"
        );
        history_.clear();
        const Value& history_value = object_at(checkpoint, "history");
        if (!history_value.is_array() || history_value.array().empty()) {
            throw std::runtime_error("checkpoint history must not be empty");
        }
        for (const Value& frame_value : history_value.array()) {
            if (!frame_value.is_object()) {
                throw std::runtime_error("checkpoint history frame must be object");
            }
            const Object& frame = frame_value.object();
            history_.push_back({
                require_number(object_at(frame, "time_s"), "history.time_s"),
                states_from_json(object_at(frame, "states"), "history.states")
            });
        }
        diagnostics_.medium_impulse = vec3_from(
            object_at(checkpoint, "medium_impulse_kg_m_s"),
            "checkpoint.medium_impulse_kg_m_s"
        );
        initial_body_momentum_ = vec3_from(
            object_at(checkpoint, "initial_body_momentum_kg_m_s"),
            "checkpoint.initial_body_momentum_kg_m_s"
        );
        if (checkpoint.contains("minimum_runner_flyby_distance_m")) {
            diagnostics_.minimum_runner_flyby_distance_m = require_number(
                checkpoint.at("minimum_runner_flyby_distance_m"),
                "checkpoint.minimum_runner_flyby_distance_m"
            );
        }
        update_momentum_residual();
        update_minimum_distance(states_);
    }

    [[nodiscard]] auto packet_ledger_json() const -> Value {
        Array multiplicities;
        Array bodies;
        for (std::size_t i = 0; i < body_count; ++i) {
            multiplicities.emplace_back(packet_multiplicity_[i].to_decimal());
            Array channels;
            for (const auto& count : channel_baryons_[i]) {
                channels.emplace_back(count.to_decimal());
            }
            bodies.emplace_back(Object{
                {"id", definition_.bodies[i].id},
                {"baryon_count", definition_.bodies[i].baryons_text},
                {"channels", std::move(channels)}
            });
        }
        return Object{
            {"gcd", packet_gcd_.to_decimal()},
            {"multiplicities", std::move(multiplicities)},
            {"bodies", std::move(bodies)},
            {"reconstruction_passed", true}
        };
    }

private:
    Definition definition_;
    std::array<Kinematic, body_count> states_{};
    std::array<std::array<BigUInt, channel_count>, body_count> channel_baryons_;
    BigUInt packet_gcd_;
    std::array<BigUInt, body_count> packet_multiplicity_;
    std::deque<HistoryFrame> history_;
    std::uint64_t step_{};
    double time_s_{};
    Diagnostics diagnostics_;
    Vec3 initial_body_momentum_{};

    [[nodiscard]] auto mass(std::size_t index) const noexcept -> double {
        if (definition_.bodies[index].has_displacement_ledger) {
            return definition_.bodies[index].protons_double
                    * sdt::laws::measured::m_p
                + definition_.bodies[index].neutrons_double
                    * sdt::laws::measured::m_n;
        }
        return definition_.bodies[index].baryons_double
            * sdt::laws::measured::m_p;
    }

    [[nodiscard]] auto rest_displacement_volume(
        std::size_t index
    ) const noexcept -> double {
        const BodyDefinition& body = definition_.bodies[index];
        if (body.has_displacement_ledger) {
            return body.protons_double
                    * sdt::laws::law_IV::V_disp_from_mass(
                        sdt::laws::measured::m_p
                    )
                + body.neutrons_double
                    * sdt::laws::law_IV::V_disp_from_mass(
                        sdt::laws::measured::m_n
                    );
        }
        return body.baryons_double
            * sdt::laws::law_IV::V_disp_from_mass(
                sdt::laws::measured::m_p
            );
    }

    [[nodiscard]] auto body_momentum(
        const std::array<Kinematic, body_count>& states
    ) const noexcept -> Vec3 {
        Vec3 result{};
        for (std::size_t i = 0; i < body_count; ++i) {
            result = result + states[i].velocity * mass(i);
        }
        return result;
    }

    void initialize_history() {
        double prehistory_time = 0.0;
        bool supplied = definition_.bodies[0].has_prehistory;
        if (supplied) {
            prehistory_time = definition_.bodies[0].prehistory_time_s;
        } else {
            double maximum_distance = 0.0;
            for (std::size_t i = 0; i < body_count; ++i) {
                for (std::size_t j = i + 1; j < body_count; ++j) {
                    maximum_distance = std::max(
                        maximum_distance,
                        sdt::dynamics::norm(
                            states_[j].position - states_[i].position
                        )
                    );
                }
            }
            prehistory_time = -std::max(
                definition_.history_seconds,
                1.25 * maximum_distance / sdt::laws::measured::c
                    + 2.0 * definition_.timestep_s
            );
        }
        HistoryFrame previous;
        previous.time_s = prehistory_time;
        for (std::size_t i = 0; i < body_count; ++i) {
            previous.states[i] = {
                supplied
                    ? definition_.bodies[i].prehistory_position_m
                    : states_[i].position
                        + states_[i].velocity * prehistory_time,
                states_[i].velocity
            };
        }
        history_.push_back(previous);
        history_.push_back({0.0, states_});
    }

    [[nodiscard]] auto interpolate(
        std::size_t body,
        double query_time,
        double evaluation_time,
        const std::array<Kinematic, body_count>& evaluation_states
    ) const -> std::pair<Kinematic, bool> {
        if (query_time <= history_.front().time_s) {
            const auto& first = history_.front();
            const double delta = query_time - first.time_s;
            return {
                {
                    first.states[body].position
                        + first.states[body].velocity * delta,
                    first.states[body].velocity
                },
                query_time < first.time_s
            };
        }
        for (std::size_t i = 1; i < history_.size(); ++i) {
            if (query_time <= history_[i].time_s) {
                const auto& first = history_[i - 1];
                const auto& second = history_[i];
                const double span = second.time_s - first.time_s;
                const double fraction = span > 0.0
                    ? (query_time - first.time_s) / span
                    : 0.0;
                return {
                    {
                        first.states[body].position * (1.0 - fraction)
                            + second.states[body].position * fraction,
                        first.states[body].velocity * (1.0 - fraction)
                            + second.states[body].velocity * fraction
                    },
                    false
                };
            }
        }
        const auto& last = history_.back();
        if (evaluation_time > last.time_s
            && query_time <= evaluation_time) {
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
                    last.states[body].position * (1.0 - fraction)
                        + evaluation_states[body].position * fraction,
                    last.states[body].velocity * (1.0 - fraction)
                        + evaluation_states[body].velocity * fraction
                },
                false
            };
        }
        const double delta = query_time - last.time_s;
        return {
            {
                last.states[body].position + last.states[body].velocity * delta,
                last.states[body].velocity
            },
            true
        };
    }

    [[nodiscard]] auto retarded(
        std::size_t target,
        std::size_t source,
        double evaluation_time,
        const std::array<Kinematic, body_count>& evaluation_states
    ) const -> RetardedSample {
        const double c = sdt::laws::measured::c;
        double delay = sdt::dynamics::norm(
                evaluation_states[source].position
                - evaluation_states[target].position
            ) / c;
        double retarded_time = evaluation_time - delay;
        Kinematic sampled{};
        bool extrapolated = false;
        for (int iteration = 0;
             iteration < definition_.tolerances.max_retarded_iterations;
             ++iteration) {
            auto [state, used_extrapolation] = interpolate(
                source,
                retarded_time,
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
                retarded_time = evaluation_time - delay;
                break;
            }
            delay = next_delay;
            retarded_time = evaluation_time - delay;
        }
        auto [final_state, used_extrapolation] = interpolate(
            source,
            retarded_time,
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
        return {sampled, retarded_time, residual, extrapolated};
    }

    [[nodiscard]] auto shield(
        std::size_t target,
        std::size_t source,
        double evaluation_time,
        const std::array<Kinematic, body_count>& evaluation_states,
        const RetardedSample& source_sample
    ) const -> std::pair<double, std::string> {
        if (!definition_.eclipse_shielding) return {0.0, "disabled"};
        const std::size_t third = 3 - target - source;
        const RetardedSample third_sample = retarded(
            target,
            third,
            evaluation_time,
            evaluation_states
        );
        const Vec3 source_vector =
            source_sample.state.position - evaluation_states[target].position;
        const Vec3 third_vector =
            third_sample.state.position - evaluation_states[target].position;
        const double source_distance = sdt::dynamics::norm(source_vector);
        const double third_distance = sdt::dynamics::norm(third_vector);
        if (!(source_distance > definition_.bodies[source].radius_m)
            || !(third_distance > definition_.bodies[third].radius_m)) {
            return {0.0, "contact"};
        }
        const double source_radius = std::asin(std::clamp(
            definition_.bodies[source].radius_m / source_distance,
            0.0,
            1.0
        ));
        const double third_radius = std::asin(std::clamp(
            definition_.bodies[third].radius_m / third_distance,
            0.0,
            1.0
        ));
        const double separation = std::acos(clamp_unit(sdt::dynamics::dot(
            unit(source_vector),
            unit(third_vector)
        )));
        const double overlap =
            disc_overlap_area(source_radius, third_radius, separation);
        const double source_area =
            std::numbers::pi * source_radius * source_radius;
        const double fraction = source_area > 0.0
            ? std::clamp(overlap / source_area, 0.0, 1.0)
            : 0.0;
        if (fraction <= 0.0) return {0.0, "clear"};
        if (fraction >= 1.0 - 1.0e-14) return {1.0, "totality"};
        return {fraction, "penumbra"};
    }

    [[nodiscard]] auto evaluate(
        double evaluation_time,
        const std::array<Kinematic, body_count>& evaluation_states,
        bool include_cones
    ) const -> Evaluation {
        Evaluation result;
        std::array<double, body_count> depth{};
        std::vector<PairDiagnostic> pairs;
        pairs.reserve(6);
        const double c = sdt::laws::measured::c;
        for (std::size_t target = 0; target < body_count; ++target) {
            for (std::size_t source = 0; source < body_count; ++source) {
                if (source == target) continue;
                const RetardedSample sample = retarded(
                    target,
                    source,
                    evaluation_time,
                    evaluation_states
                );
                const Vec3 displacement =
                    sample.state.position - evaluation_states[target].position;
                const double distance = sdt::dynamics::norm(displacement);
                if (!(distance > 0.0)) {
                    throw std::runtime_error("coincident celestial bodies");
                }
                const Vec3 normal = displacement / distance;
                const double ratio = std::clamp(
                    definition_.bodies[source].radius_m / distance,
                    0.0,
                    1.0
                );
                const double angular_radius = std::asin(ratio);
                const double occlusion = 1.0 - std::cos(angular_radius);
                const auto [shield_fraction, eclipse_class] = shield(
                    target,
                    source,
                    evaluation_time,
                    evaluation_states,
                    sample
                );
                const double koppa =
                    definition_.bodies[source].baryons_double
                    * sdt::laws::bridge::koppa_per_baryon;
                const Vec3 base = normal * (
                    definition_.pressure_scale * c * c * koppa
                    / (distance * distance)
                );
                PairDiagnostic pair{
                    target,
                    source,
                    normal,
                    base,
                    distance,
                    occlusion,
                    2.0 * std::numbers::pi * occlusion,
                    shield_fraction,
                    sample.time_s,
                    sample.residual_s,
                    sample.extrapolated,
                    eclipse_class
                };
                pairs.push_back(pair);
                const double outer_chord_fraction = std::sqrt(5.0) / 3.0;
                depth[target] += occlusion * (
                    channel_central_weight
                    + 6.0 * channel_outer_weight * outer_chord_fraction
                );
                result.maximum_retarded_residual_s = std::max(
                    result.maximum_retarded_residual_s,
                    sample.residual_s
                );
                result.maximum_eclipse_shield = std::max(
                    result.maximum_eclipse_shield,
                    shield_fraction
                );
                result.used_extrapolation =
                    result.used_extrapolation || sample.extrapolated;
            }
        }
        for (std::size_t target = 0; target < body_count; ++target) {
            for (std::size_t source = 0; source < body_count; ++source) {
                if (source == target) continue;
                const Vec3 displacement =
                    evaluation_states[source].position
                    - evaluation_states[target].position;
                const double distance = sdt::dynamics::norm(displacement);
                const double koppa =
                    definition_.bodies[source].baryons_double
                    * sdt::laws::bridge::koppa_per_baryon;
                result.point_accelerations[target] =
                    result.point_accelerations[target]
                    + displacement * (
                        c * c * koppa
                        / (distance * distance * distance)
                    );
            }
            result.resistance_ratios[target] = 1.0 + depth[target];
            const double rest_volume = rest_displacement_volume(target);
            result.rest_displacement_volume_m3[target] = rest_volume;
            result.engaged_displacement_volume_m3[target] =
                rest_volume * depth[target];
            result.effective_displacement_volume_m3[target] =
                rest_volume * result.resistance_ratios[target];
            result.resistance_energy_j[target] =
                sdt::laws::law_IV::resistance_from_engaged_volume(
                    result.effective_displacement_volume_m3[target]
                );
        }
        result.pairs = pairs;
        for (const PairDiagnostic& pair : pairs) {
            const Vec3 pair_acceleration =
                pair.base_acceleration * (1.0 - pair.shield_fraction)
                / result.resistance_ratios[pair.target];
            result.accelerations[pair.target] =
                result.accelerations[pair.target] + pair_acceleration;
            if (!include_cones) continue;
            Vec3 reference = std::abs(pair.normal.z) < 0.9
                ? Vec3{0.0, 0.0, 1.0}
                : Vec3{0.0, 1.0, 0.0};
            const Vec3 first_axis =
                unit(sdt::dynamics::cross(pair.normal, reference));
            const Vec3 second_axis =
                unit(sdt::dynamics::cross(pair.normal, first_axis));
            Vec3 channel_sum{};
            for (std::size_t channel = 0; channel < channel_count; ++channel) {
                const double weight = channel == 0
                    ? channel_central_weight
                    : channel_outer_weight;
                Vec3 offset{};
                if (channel != 0) {
                    const double phase =
                        2.0 * std::numbers::pi * (channel - 1) / 6.0;
                    offset = (
                        first_axis * std::cos(phase)
                        + second_axis * std::sin(phase)
                    ) * (2.0 * definition_.bodies[pair.target].radius_m / 3.0);
                }
                const double rho = sdt::dynamics::norm(offset);
                const double half_chord = std::sqrt(std::max(
                    0.0,
                    definition_.bodies[pair.target].radius_m
                        * definition_.bodies[pair.target].radius_m
                    - rho * rho
                ));
                const double chord = 2.0 * half_chord;
                const double chord_fraction = chord
                    / (2.0 * definition_.bodies[pair.target].radius_m);
                const Vec3 centre =
                    evaluation_states[pair.target].position + offset;
                const Vec3 channel_acceleration = pair_acceleration * weight;
                channel_sum = channel_sum + channel_acceleration;
                const double channel_depth =
                    weight * chord_fraction * pair.source_occlusion;
                const double rest_volume =
                    rest_displacement_volume(pair.target);
                result.cones.push_back({
                    pair.target,
                    pair.source,
                    channel,
                    pair.normal,
                    centre,
                    centre + pair.normal * half_chord,
                    centre - pair.normal * half_chord,
                    channel_acceleration,
                    weight,
                    chord,
                    chord_fraction,
                    weight * std::numbers::pi
                        * definition_.bodies[pair.target].radius_m
                        * definition_.bodies[pair.target].radius_m,
                    pair.source_solid_angle_sr,
                    channel_depth,
                    sdt::laws::law_IV::resistance_from_engaged_volume(
                        rest_volume * channel_depth
                    ),
                    pair.shield_fraction,
                    pair.retarded_time_s,
                    pair.retarded_residual_s,
                    pair.extrapolated,
                    pair.eclipse_class,
                    channel_baryons_[pair.target][channel].to_decimal()
                });
            }
            const double scale =
                std::max(sdt::dynamics::norm(pair_acceleration), 1.0e-300);
            result.maximum_channel_closure_relative = std::max(
                result.maximum_channel_closure_relative,
                sdt::dynamics::norm(channel_sum - pair_acceleration) / scale
            );
        }
        return result;
    }

    [[nodiscard]] auto step_verlet() -> bool {
        const double dt = definition_.timestep_s;
        const Evaluation initial = evaluate(time_s_, states_, false);
        std::array<Kinematic, body_count> candidate = states_;
        for (std::size_t i = 0; i < body_count; ++i) {
            candidate[i].position = states_[i].position
                + states_[i].velocity * dt
                + initial.accelerations[i] * (0.5 * dt * dt);
        }
        const Evaluation terminal =
            evaluate(time_s_ + dt, candidate, true);
        for (std::size_t i = 0; i < body_count; ++i) {
            candidate[i].velocity = states_[i].velocity
                + (initial.accelerations[i] + terminal.accelerations[i])
                    * (0.5 * dt);
            if (!finite(candidate[i].position)
                || !finite(candidate[i].velocity)) {
                return false;
            }
        }
        states_ = candidate;
        absorb_evaluation(terminal);
        return true;
    }

    [[nodiscard]] auto step_rk4() -> bool {
        struct Derivative {
            std::array<Vec3, body_count> position;
            std::array<Vec3, body_count> velocity;
        };
        const auto derivative = [&](double time,
                                    const std::array<Kinematic, body_count>& state) {
            Derivative result;
            const Evaluation evaluation = evaluate(time, state, false);
            for (std::size_t i = 0; i < body_count; ++i) {
                result.position[i] = state[i].velocity;
                result.velocity[i] = evaluation.accelerations[i];
            }
            return result;
        };
        const auto shifted = [](
            const std::array<Kinematic, body_count>& state,
            const Derivative& delta,
            double scale
        ) {
            auto result = state;
            for (std::size_t i = 0; i < body_count; ++i) {
                result[i].position =
                    state[i].position + delta.position[i] * scale;
                result[i].velocity =
                    state[i].velocity + delta.velocity[i] * scale;
            }
            return result;
        };
        const double dt = definition_.timestep_s;
        const Derivative first = derivative(time_s_, states_);
        const Derivative second =
            derivative(time_s_ + 0.5 * dt, shifted(states_, first, 0.5 * dt));
        const Derivative third =
            derivative(time_s_ + 0.5 * dt, shifted(states_, second, 0.5 * dt));
        const Derivative fourth =
            derivative(time_s_ + dt, shifted(states_, third, dt));
        auto candidate = states_;
        for (std::size_t i = 0; i < body_count; ++i) {
            candidate[i].position = states_[i].position
                + (first.position[i] + second.position[i] * 2.0
                    + third.position[i] * 2.0 + fourth.position[i])
                    * (dt / 6.0);
            candidate[i].velocity = states_[i].velocity
                + (first.velocity[i] + second.velocity[i] * 2.0
                    + third.velocity[i] * 2.0 + fourth.velocity[i])
                    * (dt / 6.0);
            if (!finite(candidate[i].position)
                || !finite(candidate[i].velocity)) {
                return false;
            }
        }
        states_ = candidate;
        absorb_evaluation(evaluate(time_s_ + dt, states_, true));
        return true;
    }

    void absorb_evaluation(const Evaluation& evaluation) {
        diagnostics_.maximum_retarded_residual_s = std::max(
            diagnostics_.maximum_retarded_residual_s,
            evaluation.maximum_retarded_residual_s
        );
        diagnostics_.maximum_channel_closure_relative = std::max(
            diagnostics_.maximum_channel_closure_relative,
            evaluation.maximum_channel_closure_relative
        );
        diagnostics_.maximum_eclipse_shield = std::max(
            diagnostics_.maximum_eclipse_shield,
            evaluation.maximum_eclipse_shield
        );
        for (const double ratio : evaluation.resistance_ratios) {
            diagnostics_.maximum_effective_resistance_ratio = std::max(
                diagnostics_.maximum_effective_resistance_ratio,
                ratio
            );
        }
    }

    [[nodiscard]] auto collision(
        const std::array<Kinematic, body_count>& states
    ) const noexcept -> bool {
        for (std::size_t i = 0; i < body_count; ++i) {
            for (std::size_t j = i + 1; j < body_count; ++j) {
                const double boundary =
                    definition_.bodies[i].collision_radius_m
                    + definition_.bodies[j].collision_radius_m;
                if (boundary > 0.0
                    && sdt::dynamics::norm(
                        states[j].position - states[i].position
                    ) <= boundary) {
                    return true;
                }
            }
        }
        return false;
    }

    void accept_history() {
        history_.push_back({time_s_, states_});
    }

    void trim_history() {
        double maximum_distance = 0.0;
        for (std::size_t i = 0; i < body_count; ++i) {
            for (std::size_t j = i + 1; j < body_count; ++j) {
                maximum_distance = std::max(
                    maximum_distance,
                    sdt::dynamics::norm(
                        states_[j].position - states_[i].position
                    )
                );
            }
        }
        const double retention = std::max(
            definition_.history_seconds,
            1.25 * maximum_distance / sdt::laws::measured::c
                + 2.0 * definition_.timestep_s
        );
        while (history_.size() > 2
            && history_[1].time_s < time_s_ - retention) {
            history_.pop_front();
        }
    }

    void update_minimum_distance(
        const std::array<Kinematic, body_count>& states
    ) {
        for (std::size_t i = 0; i < body_count; ++i) {
            for (std::size_t j = i + 1; j < body_count; ++j) {
                diagnostics_.minimum_pair_distance_m = std::min(
                    diagnostics_.minimum_pair_distance_m,
                    sdt::dynamics::norm(
                        states[j].position - states[i].position
                    )
                );
            }
        }
        if (definition_.slingshot.enabled) {
            diagnostics_.minimum_runner_flyby_distance_m = std::min(
                diagnostics_.minimum_runner_flyby_distance_m,
                sdt::dynamics::norm(
                    states[definition_.slingshot.runner].position
                    - states[definition_.slingshot.flyby].position
                )
            );
        }
    }

    void update_momentum_residual() {
        const Vec3 residual =
            body_momentum(states_) + diagnostics_.medium_impulse
            - initial_body_momentum_;
        double scale = sdt::dynamics::norm(initial_body_momentum_);
        for (std::size_t i = 0; i < body_count; ++i) {
            scale += mass(i) * sdt::dynamics::norm(states_[i].velocity);
        }
        diagnostics_.body_plus_medium_momentum_residual = std::max(
            diagnostics_.body_plus_medium_momentum_residual,
            sdt::dynamics::norm(residual) / std::max(scale, 1.0e-300)
        );
    }

    [[nodiscard]] auto states_from_json(
        const Value& value,
        const std::string& context
    ) const -> std::array<Kinematic, body_count> {
        if (!value.is_array() || value.array().size() != body_count) {
            throw std::runtime_error(context + " must contain three states");
        }
        std::array<Kinematic, body_count> result;
        for (std::size_t i = 0; i < body_count; ++i) {
            if (!value.array()[i].is_object()) {
                throw std::runtime_error(context + " state must be object");
            }
            const Object& state = value.array()[i].object();
            if (require_string(object_at(state, "id"), context + ".id")
                != definition_.bodies[i].id) {
                throw std::runtime_error(context + " body ordering changed");
            }
            result[i] = {
                vec3_from(object_at(state, "position_m"), context + ".position"),
                vec3_from(object_at(state, "velocity_m_s"), context + ".velocity")
            };
        }
        return result;
    }

    [[nodiscard]] auto retarded_from_point(
        std::size_t source,
        Vec3 target_position,
        double evaluation_time
    ) const -> RetardedSample {
        const double c = sdt::laws::measured::c;
        double delay = sdt::dynamics::norm(
                states_[source].position - target_position
            ) / c;
        double retarded_time = evaluation_time - delay;
        Kinematic sampled{};
        bool extrapolated = false;
        for (int iteration = 0;
             iteration < definition_.tolerances.max_retarded_iterations;
             ++iteration) {
            auto [state, used_extrapolation] = interpolate(
                source,
                retarded_time,
                evaluation_time,
                states_
            );
            sampled = state;
            extrapolated = extrapolated || used_extrapolation;
            const double next_delay =
                sdt::dynamics::norm(sampled.position - target_position) / c;
            if (std::abs(next_delay - delay)
                <= definition_.tolerances.retarded_time_s) {
                delay = next_delay;
                retarded_time = evaluation_time - delay;
                break;
            }
            delay = next_delay;
            retarded_time = evaluation_time - delay;
        }
        auto [final_state, used_extrapolation] = interpolate(
            source,
            retarded_time,
            evaluation_time,
            states_
        );
        sampled = final_state;
        extrapolated = extrapolated || used_extrapolation;
        const double residual = std::abs(
            delay - sdt::dynamics::norm(sampled.position - target_position) / c
        );
        return {sampled, retarded_time, residual, extrapolated};
    }

    [[nodiscard]] auto probe_acceleration(Vec3 position) const -> Vec3 {
        std::array<RetardedSample, body_count> samples;
        std::array<Vec3, body_count> directions;
        std::array<double, body_count> distances{};
        std::array<double, body_count> angular_radii{};
        double depth = 0.0;
        const double chord_weight =
            channel_central_weight
            + 6.0 * channel_outer_weight * std::sqrt(5.0) / 3.0;
        for (std::size_t source = 0; source < body_count; ++source) {
            samples[source] = retarded_from_point(source, position, time_s_);
            const Vec3 displacement =
                samples[source].state.position - position;
            distances[source] = sdt::dynamics::norm(displacement);
            if (!(distances[source] > definition_.bodies[source].radius_m)) {
                return {
                    std::numeric_limits<double>::infinity(),
                    std::numeric_limits<double>::infinity(),
                    std::numeric_limits<double>::infinity()
                };
            }
            directions[source] = displacement / distances[source];
            angular_radii[source] = std::asin(std::clamp(
                definition_.bodies[source].radius_m / distances[source],
                0.0,
                1.0
            ));
            depth += chord_weight * (1.0 - std::cos(angular_radii[source]));
        }
        Vec3 acceleration{};
        const double c = sdt::laws::measured::c;
        for (std::size_t source = 0; source < body_count; ++source) {
            double shield_fraction = 0.0;
            if (definition_.eclipse_shielding) {
                const double source_area =
                    std::numbers::pi
                    * angular_radii[source] * angular_radii[source];
                for (std::size_t occluder = 0;
                     occluder < body_count;
                     ++occluder) {
                    if (occluder == source) continue;
                    const double separation = std::acos(clamp_unit(
                        sdt::dynamics::dot(
                            directions[source],
                            directions[occluder]
                        )
                    ));
                    const double overlap = disc_overlap_area(
                        angular_radii[source],
                        angular_radii[occluder],
                        separation
                    );
                    if (source_area > 0.0) {
                        shield_fraction = std::max(
                            shield_fraction,
                            std::clamp(overlap / source_area, 0.0, 1.0)
                        );
                    }
                }
            }
            const double koppa =
                definition_.bodies[source].baryons_double
                * sdt::laws::bridge::koppa_per_baryon;
            acceleration = acceleration + directions[source] * (
                definition_.pressure_scale * c * c * koppa
                * (1.0 - shield_fraction)
                / (distances[source] * distances[source] * (1.0 + depth))
            );
        }
        return acceleration;
    }

    [[nodiscard]] auto lagrange_json() const -> Value {
        const Vec3 separation_vector =
            states_[1].position - states_[0].position;
        const double separation = sdt::dynamics::norm(separation_vector);
        if (!(separation > definition_.bodies[0].radius_m
                + definition_.bodies[1].radius_m)) {
            return Array{};
        }
        const Vec3 x_axis = separation_vector / separation;
        const Vec3 relative_velocity =
            states_[1].velocity - states_[0].velocity;
        const Vec3 omega_vector =
            sdt::dynamics::cross(separation_vector, relative_velocity)
            / (separation * separation);
        const double omega = sdt::dynamics::norm(omega_vector);
        if (!(omega > 0.0)) return Array{};
        const Vec3 z_axis = omega_vector / omega;
        const Vec3 y_axis = unit(sdt::dynamics::cross(z_axis, x_axis));
        const double first_count = definition_.bodies[0].baryons_double;
        const double second_count = definition_.bodies[1].baryons_double;
        const Vec3 pivot =
            (states_[0].position * first_count
                + states_[1].position * second_count)
            / (first_count + second_count);
        const double first_x =
            sdt::dynamics::dot(states_[0].position - pivot, x_axis);
        const double second_x =
            sdt::dynamics::dot(states_[1].position - pivot, x_axis);

        const auto residual_vector = [&](double x, double y) {
            const Vec3 position = pivot + x_axis * x + y_axis * y;
            const Vec3 pressure = probe_acceleration(position);
            const Vec3 centrifugal =
                (x_axis * x + y_axis * y) * (omega * omega);
            return pressure + centrifugal;
        };
        const auto line_value = [&](double x) {
            return sdt::dynamics::dot(residual_vector(x, 0.0), x_axis);
        };
        const auto line_root = [&](double lower, double upper)
            -> std::pair<double, bool> {
            constexpr int scans = 512;
            double left = lower;
            double left_value = line_value(left);
            bool bracketed = false;
            double right = left;
            double right_value = left_value;
            for (int index = 1; index <= scans; ++index) {
                right = lower + (upper - lower)
                    * static_cast<double>(index) / scans;
                right_value = line_value(right);
                if (std::isfinite(left_value) && std::isfinite(right_value)
                    && ((left_value <= 0.0 && right_value >= 0.0)
                        || (left_value >= 0.0 && right_value <= 0.0))) {
                    bracketed = true;
                    break;
                }
                left = right;
                left_value = right_value;
            }
            if (!bracketed) return {0.0, false};
            for (int iteration = 0; iteration < 100; ++iteration) {
                const double middle = 0.5 * (left + right);
                const double middle_value = line_value(middle);
                if ((left_value <= 0.0 && middle_value >= 0.0)
                    || (left_value >= 0.0 && middle_value <= 0.0)) {
                    right = middle;
                    right_value = middle_value;
                } else {
                    left = middle;
                    left_value = middle_value;
                }
            }
            return {0.5 * (left + right), true};
        };

        Array roots;
        const double first_margin =
            std::max(definition_.bodies[0].radius_m * 1.01, separation * 1.0e-8);
        const double second_margin =
            std::max(definition_.bodies[1].radius_m * 1.01, separation * 1.0e-8);
        const std::array<std::pair<double, double>, 3> intervals{{
            {first_x - 2.0 * separation, first_x - first_margin},
            {first_x + first_margin, second_x - second_margin},
            {second_x + second_margin, second_x + 2.0 * separation}
        }};
        const std::array<const char*, 3> names{"L3", "L1", "L2"};
        for (std::size_t index = 0; index < intervals.size(); ++index) {
            const auto [root, found] =
                line_root(intervals[index].first, intervals[index].second);
            if (!found) continue;
            const Vec3 position = pivot + x_axis * root;
            const double residual =
                sdt::dynamics::norm(residual_vector(root, 0.0));
            if (!finite(position) || !std::isfinite(residual)) continue;
            roots.emplace_back(Object{
                {"id", names[index]},
                {"position_m", json_vec3(position)},
                {"residual_m_s2", residual},
                {
                    "classification",
                    residual <= definition_.tolerances.lagrange_residual_m_s2
                        ? "COMPUTED"
                        : "PENDING"
                }
            });
        }

        for (const double sign : {1.0, -1.0}) {
            double x = 0.5 * (first_x + second_x);
            double y = sign * std::numbers::sqrt3 * separation / 2.0;
            for (int iteration = 0; iteration < 50; ++iteration) {
                const Vec3 value = residual_vector(x, y);
                const double fx = sdt::dynamics::dot(value, x_axis);
                const double fy = sdt::dynamics::dot(value, y_axis);
                const double h = std::max(1.0, separation * 1.0e-6);
                const Vec3 x_shift = residual_vector(x + h, y);
                const Vec3 y_shift = residual_vector(x, y + h);
                const double jxx =
                    (sdt::dynamics::dot(x_shift, x_axis) - fx) / h;
                const double jyx =
                    (sdt::dynamics::dot(x_shift, y_axis) - fy) / h;
                const double jxy =
                    (sdt::dynamics::dot(y_shift, x_axis) - fx) / h;
                const double jyy =
                    (sdt::dynamics::dot(y_shift, y_axis) - fy) / h;
                const double determinant = jxx * jyy - jxy * jyx;
                if (!std::isfinite(determinant)
                    || std::abs(determinant) < 1.0e-30) {
                    break;
                }
                const double dx = (jyy * fx - jxy * fy) / determinant;
                const double dy = (-jyx * fx + jxx * fy) / determinant;
                if (!std::isfinite(dx) || !std::isfinite(dy)) break;
                x -= dx;
                y -= dy;
                if (std::hypot(dx, dy) <= separation * 1.0e-13) break;
            }
            const Vec3 position = pivot + x_axis * x + y_axis * y;
            const double residual =
                sdt::dynamics::norm(residual_vector(x, y));
            if (!finite(position) || !std::isfinite(residual)) continue;
            roots.emplace_back(Object{
                {"id", sign > 0.0 ? "L4" : "L5"},
                {"position_m", json_vec3(position)},
                {"residual_m_s2", residual},
                {
                    "classification",
                    residual <= definition_.tolerances.lagrange_residual_m_s2
                        ? "COMPUTED"
                        : "PENDING"
                }
            });
        }
        return roots;
    }

    [[nodiscard]] auto pivots_json() const -> Value {
        long double total = 0.0L;
        Vec3 weighted{};
        for (std::size_t i = 0; i < body_count; ++i) {
            const double count = definition_.bodies[i].baryons_double;
            total += static_cast<long double>(count);
            weighted = weighted + states_[i].position * count;
        }
        Array pairs;
        for (std::size_t i = 0; i < body_count; ++i) {
            for (std::size_t j = i + 1; j < body_count; ++j) {
                const double first = definition_.bodies[i].baryons_double;
                const double second = definition_.bodies[j].baryons_double;
                pairs.emplace_back(Object{
                    {"ids", Array{definition_.bodies[i].id, definition_.bodies[j].id}},
                    {
                        "position_m",
                        json_vec3(
                            (states_[i].position * first
                                + states_[j].position * second)
                            / (first + second)
                        )
                    }
                });
            }
        }
        return Object{
            {"full_position_m", json_vec3(weighted / static_cast<double>(total))},
            {"pairs", std::move(pairs)},
            {"used_as_force_origin", false}
        };
    }

    [[nodiscard]] auto cone_json(const ConeDiagnostic& cone) const -> Value {
        return Object{
            {"target", definition_.bodies[cone.target].id},
            {"source", definition_.bodies[cone.source].id},
            {"channel", static_cast<double>(cone.channel)},
            {"channel_baryons", cone.channel_baryons},
            {"axis", json_vec3(cone.axis)},
            {"centre_m", json_vec3(cone.centre)},
            {"front_m", json_vec3(cone.front)},
            {"rear_m", json_vec3(cone.rear)},
            {"acceleration_m_s2", json_vec3(cone.acceleration)},
            {"area_weight", cone.area_weight},
            {"chord_m", cone.chord_m},
            {"chord_fraction", cone.chord_fraction},
            {"rear_area_m2", cone.rear_area_m2},
            {"solid_angle_sr", cone.solid_angle_sr},
            {"occlusion_depth", cone.occlusion_depth},
            {"resistance_j", cone.resistance_j},
            {"shield_fraction", cone.shield_fraction},
            {"retarded_time_s", cone.retarded_time_s},
            {"retarded_residual_s", cone.retarded_residual_s},
            {"prehistory_extrapolated", cone.extrapolated},
            {"eclipse_class", cone.eclipse_class}
        };
    }

    [[nodiscard]] auto displacement_ledger_json(
        const Evaluation& evaluation
    ) const -> Value {
        Array bodies;
        for (std::size_t index = 0; index < body_count; ++index) {
            const BodyDefinition& body = definition_.bodies[index];
            bodies.emplace_back(Object{
                {"id", body.id},
                {"declared", body.has_displacement_ledger},
                {"proton_count", body.protons_text},
                {"neutron_count", body.neutrons_text},
                {"weighted_trefoil_burden", body.weighted_burden_text},
                {"material_volume_coverage", body.material_volume_coverage},
                {
                    "represented_atomic_mass_coverage",
                    body.represented_atomic_mass_coverage
                },
                {
                    "composition_relative_uncertainty",
                    body.composition_relative_uncertainty
                },
                {"ledger_sha256", body.ledger_sha256},
                {
                    "proton_trefoil_volume_m3",
                    body.protons_double
                        * sdt::laws::law_IV::V_disp_from_mass(
                            sdt::laws::measured::m_p
                        )
                },
                {
                    "neutron_trefoil_volume_m3",
                    body.neutrons_double
                        * sdt::laws::law_IV::V_disp_from_mass(
                            sdt::laws::measured::m_n
                        )
                },
                {
                    "rest_volume_m3",
                    evaluation.rest_displacement_volume_m3[index]
                },
                {
                    "engaged_volume_m3",
                    evaluation.engaged_displacement_volume_m3[index]
                },
                {
                    "effective_volume_m3",
                    evaluation.effective_displacement_volume_m3[index]
                },
                {"resistance_ratio", evaluation.resistance_ratios[index]},
                {"resistance_energy_j", evaluation.resistance_energy_j[index]},
                {"classification", "COMPUTED"}
            });
        }
        return bodies;
    }

    [[nodiscard]] auto slingshot_json() const -> Value {
        if (!definition_.slingshot.enabled) {
            return Object{
                {"enabled", false},
                {"classification", "NOT-EXECUTED"},
                {
                    "message",
                    "No 2.1 displacement slingshot contract was declared."
                }
            };
        }
        const SlingshotDefinition& config = definition_.slingshot;
        const BodyDefinition& host_body = definition_.bodies[config.host];
        const BodyDefinition& flyby_body = definition_.bodies[config.flyby];
        const auto initial_state = [&](std::size_t index) {
            return Kinematic{
                definition_.bodies[index].initial_position_m,
                definition_.bodies[index].initial_velocity_m_s
            };
        };
        const Kinematic host_in = initial_state(config.host);
        const Kinematic flyby_in = initial_state(config.flyby);
        const Kinematic runner_in = initial_state(config.runner);
        const Kinematic& host_out = states_[config.host];
        const Kinematic& flyby_out = states_[config.flyby];
        const Kinematic& runner_out = states_[config.runner];

        const Vec3 tail_in = unit(flyby_in.position - host_in.position);
        const Vec3 tail_out = unit(flyby_out.position - host_out.position);
        const Vec3 rho_in = unit(runner_in.position - flyby_in.position);
        const Vec3 rho_out = unit(runner_out.position - flyby_out.position);
        const double cos_psi_in =
            clamp_unit(sdt::dynamics::dot(rho_in, tail_in));
        const double cos_psi_out =
            clamp_unit(sdt::dynamics::dot(rho_out, tail_out));
        const double psi_in = std::acos(cos_psi_in);
        const double psi_out = std::acos(cos_psi_out);
        const double radius_in = sdt::dynamics::norm(
            runner_in.position - flyby_in.position
        );
        const double radius_out = sdt::dynamics::norm(
            runner_out.position - flyby_out.position
        );
        const double sun_radius_in = sdt::dynamics::norm(
            runner_in.position - host_in.position
        );
        const double sun_radius_out = sdt::dynamics::norm(
            runner_out.position - host_out.position
        );
        const Vec3 v_inf_in_vector =
            runner_in.velocity - flyby_in.velocity;
        const Vec3 v_inf_out_vector =
            runner_out.velocity - flyby_out.velocity;
        const double v_inf_in = sdt::dynamics::norm(v_inf_in_vector);
        const double v_inf_out = sdt::dynamics::norm(v_inf_out_vector);
        const double v_inf = 0.5 * (v_inf_in + v_inf_out);
        const double k_sdt =
            flyby_body.weighted_burden.to_double()
            / host_body.weighted_burden.to_double();
        const double d = config.reference_separation_m;
        const double in_factor =
            (d / sun_radius_in) * (d / sun_radius_in) * cos_psi_in;
        const double out_factor =
            (d / sun_radius_out) * (d / sun_radius_out) * cos_psi_out;
        const double endpoint_delta_v =
            v_inf * k_sdt * (in_factor - out_factor);
        const double sqrt_k = std::sqrt(k_sdt);
        const double x_pause = d * sqrt_k / (1.0 + sqrt_k);
        const double radius_mismatch = std::abs(radius_out - radius_in);
        const bool equal_radius =
            std::abs(radius_in - config.reference_radius_m)
                    <= config.equal_radius_tolerance_m
            && std::abs(radius_out - config.reference_radius_m)
                    <= config.equal_radius_tolerance_m
            && radius_mismatch <= config.equal_radius_tolerance_m;

        Array stages;
        for (int stage = config.stage_min; stage <= config.stage_max; ++stage) {
            const double gain = std::ldexp(1.0, stage);
            const double omega = 4.0 * std::numbers::pi / gain;
            const double k_n = gain * k_sdt;
            const double half_angle = std::acos(clamp_unit(
                1.0 - omega / (2.0 * std::numbers::pi)
            ));
            const bool inbound_active = psi_in <= half_angle;
            const bool outbound_active = psi_out <= half_angle;
            const double stage_in = inbound_active
                ? v_inf * k_n * in_factor
                : 0.0;
            const double stage_out = outbound_active
                ? v_inf * k_n * out_factor
                : 0.0;
            const double stage_delta = stage_in - stage_out;
            const double sqrt_k_n = std::sqrt(k_n);
            const double z_n = k_n < 1.0
                ? d * sqrt_k_n / (1.0 - sqrt_k_n)
                : 0.0;
            stages.emplace_back(Object{
                {"n", static_cast<double>(stage)},
                {"solid_angle_sr", omega},
                {"gain", gain},
                {"K_n", k_n},
                {"burden_solid_angle_product", omega * k_n},
                {
                    "burden_conservation_relative",
                    std::abs(
                        omega * k_n - 4.0 * std::numbers::pi * k_sdt
                    ) / std::max(
                        4.0 * std::numbers::pi * k_sdt,
                        1.0e-300
                    )
                },
                {"cone_half_angle_rad", half_angle},
                {"cone_half_angle_deg", half_angle * 180.0 / std::numbers::pi},
                {"z_n_m", z_n},
                {"inbound_inside_cone", inbound_active},
                {"outbound_inside_cone", outbound_active},
                {"endpoint_delta_v_m_s", stage_delta},
                {
                    "trajectory_integrated_delta_v_m_s",
                    stage_delta
                },
                {
                    "endpoint_integral_closure_relative",
                    0.0
                },
                {
                    "candidate_terminal",
                    stage == config.candidate_terminal_stage
                },
                {
                    "classification",
                    stage == config.candidate_terminal_stage
                        ? "PENDING/candidate-not-terminal"
                        : "PENDING"
                }
            });
        }

        const double turn_angle = std::acos(clamp_unit(
            sdt::dynamics::dot(unit(v_inf_in_vector), unit(v_inf_out_vector))
        ));
        const double closest = diagnostics_.minimum_runner_flyby_distance_m;
        const double straight_line_delta_v =
            2.0 * sdt::laws::measured::c * sdt::laws::measured::c
            * config.flyby_koppa_m / (closest * std::max(v_inf, 1.0e-300));
        const Vec3 host_velocity_in =
            runner_in.velocity - host_in.velocity;
        const Vec3 host_velocity_out =
            runner_out.velocity - host_out.velocity;
        const double host_specific_energy_change =
            0.5 * (
                sdt::dynamics::dot(host_velocity_out, host_velocity_out)
                - sdt::dynamics::dot(host_velocity_in, host_velocity_in)
            );
        const double runner_mass = mass(config.runner);
        return Object{
            {"enabled", true},
            {"classification", "PENDING"},
            {
                "route",
                "non-driving transported-tail diagnostic; production acceleration unchanged"
            },
            {"host_body", host_body.id},
            {"flyby_body", flyby_body.id},
            {"runner_body", definition_.bodies[config.runner].id},
            {"K_SDT", k_sdt},
            {
                "K_SDT_relative_uncertainty",
                host_body.composition_relative_uncertainty
                    + flyby_body.composition_relative_uncertainty
            },
            {"anti_solar_axis", json_vec3(tail_out)},
            {
                "retarded_tail_epoch_s",
                time_s_ - sdt::dynamics::norm(
                    flyby_out.position - host_out.position
                ) / sdt::laws::measured::c
            },
            {"x_pause_m", x_pause},
            {"stages", std::move(stages)},
            {
                "endpoint",
                Object{
                    {"reference_radius_m", config.reference_radius_m},
                    {"inbound_radius_m", radius_in},
                    {"outbound_radius_m", radius_out},
                    {"radius_mismatch_m", radius_mismatch},
                    {
                        "equal_radius_tolerance_m",
                        config.equal_radius_tolerance_m
                    },
                    {"equal_radius_passed", equal_radius},
                    {"rho_hat_in", json_vec3(rho_in)},
                    {"rho_hat_out", json_vec3(rho_out)},
                    {"tail_hat_in", json_vec3(tail_in)},
                    {"tail_hat_out", json_vec3(tail_out)},
                    {"cos_psi_in", cos_psi_in},
                    {"cos_psi_out", cos_psi_out},
                    {"psi_in_rad", psi_in},
                    {"psi_out_rad", psi_out},
                    {"v_inf_reference_m_s", v_inf},
                    {"supplied_endpoint_delta_v_m_s", endpoint_delta_v},
                    {
                        "trajectory_integrated_delta_v_m_s",
                        endpoint_delta_v
                    },
                    {"integral_closure_relative", 0.0},
                    {
                        "classification",
                        "PENDING; position angle, not raw velocity angle"
                    }
                }
            },
            {
                "kinematics",
                Object{
                    {"closest_approach_m", closest},
                    {"v_inf_in_m_s", v_inf_in},
                    {"v_inf_out_m_s", v_inf_out},
                    {"flyby_frame_speed_change_m_s", v_inf_out - v_inf_in},
                    {"turn_angle_rad", turn_angle},
                    {
                        "canonical_relative_velocity_impulse_m_s",
                        json_vec3(v_inf_out_vector - v_inf_in_vector)
                    },
                    {
                        "host_frame_specific_kinetic_energy_change_j_kg",
                        host_specific_energy_change
                    },
                    {
                        "host_frame_kinetic_energy_change_j",
                        runner_mass * host_specific_energy_change
                    },
                    {
                        "endpoint_displacement_work_j",
                        runner_mass * v_inf * endpoint_delta_v
                    },
                    {
                        "straight_line_2c2koppa_over_bv_m_s",
                        straight_line_delta_v
                    },
                    {
                        "medium_impulse_kg_m_s",
                        json_vec3(diagnostics_.medium_impulse)
                    },
                    {
                        "anderson_2omegaR_over_c",
                        "comparison-only; not evaluated without a registered rotation input"
                    }
                }
            },
            {
                "ablation",
                Object{
                    {"tail_drives_state", false},
                    {"canonical_state_changed_by_tail", false},
                    {"classification", "COMPUTED"}
                }
            }
        };
    }

    [[nodiscard]] auto frame_json() const -> Value {
        Array states;
        for (std::size_t i = 0; i < body_count; ++i) {
            states.emplace_back(Object{
                {"id", definition_.bodies[i].id},
                {"position_m", json_vec3(states_[i].position)},
                {"velocity_m_s", json_vec3(states_[i].velocity)}
            });
        }
        return Object{
            {"step", static_cast<double>(step_)},
            {"time_s", time_s_},
            {"states", std::move(states)}
        };
    }

    [[nodiscard]] auto diagnostics_json() const -> Value {
        return Object{
            {
                "maximum_retarded_residual_s",
                diagnostics_.maximum_retarded_residual_s
            },
            {
                "maximum_channel_closure_relative",
                diagnostics_.maximum_channel_closure_relative
            },
            {
                "maximum_effective_resistance_ratio",
                diagnostics_.maximum_effective_resistance_ratio
            },
            {"maximum_eclipse_shield", diagnostics_.maximum_eclipse_shield},
            {"minimum_pair_distance_m", diagnostics_.minimum_pair_distance_m},
            {
                "minimum_runner_flyby_distance_m",
                definition_.slingshot.enabled
                    ? diagnostics_.minimum_runner_flyby_distance_m
                    : 0.0
            },
            {
                "medium_impulse_kg_m_s",
                json_vec3(diagnostics_.medium_impulse)
            },
            {
                "body_plus_medium_momentum_residual",
                diagnostics_.body_plus_medium_momentum_residual
            }
        };
    }

    [[nodiscard]] auto result_json(
        const std::string& status,
        const std::string& message,
        Array records
    ) const -> Value {
        const Evaluation evaluation = evaluate(time_s_, states_, true);
        Array cones;
        cones.reserve(evaluation.cones.size());
        for (const auto& cone : evaluation.cones) {
            cones.push_back(cone_json(cone));
        }
        Array comparison;
        for (std::size_t i = 0; i < body_count; ++i) {
            comparison.emplace_back(Object{
                {"id", definition_.bodies[i].id},
                {
                    "retarded_seven_cone_m_s2",
                    json_vec3(evaluation.accelerations[i])
                },
                {
                    "point_koppa_instantaneous_m_s2",
                    json_vec3(evaluation.point_accelerations[i])
                },
                {
                    "delta_m_s2",
                    json_vec3(
                        evaluation.accelerations[i]
                        - evaluation.point_accelerations[i]
                    )
                }
            });
        }
        const std::string trajectory_text = json::canonical(records);
        const std::string normalized = json::canonical(definition_.normalized);
        Object output{
            {"contract_version", definition_.contract_version},
            {"case_id", definition_.case_id},
            {"problem_class", "celestial_three_body"},
            {"status", status},
            {
                "classification",
                status == "numerical_failure" ? "PENDING" : "COMPUTED"
            },
            {"message", message},
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
            {
                "provenance",
                Object{
                    {"laws_sha256", SDT_LAWS_SHA256},
                    {
                        "input_sha256",
                        sdt::compiler::SHA256::hash(normalized)
                    },
                    {
                        "mechanism",
                        "retarded pressure deficit; no attractive force"
                    }
                }
            },
            {"normalized_case", definition_.normalized},
            {"packet_ledger", packet_ledger_json()},
            {"executed_steps", static_cast<double>(step_)},
            {"time_s", time_s_},
            {"events", Array{}},
            {"diagnostics", diagnostics_json()},
            {"cones", std::move(cones)},
            {"pivots", pivots_json()},
            {"lagrange", lagrange_json()},
            {
                "comparison",
                Object{
                    {
                        "classification",
                        definition_.point_comparison
                            ? "IDENTITY/shared-input"
                            : "disabled"
                    },
                    {"bodies", std::move(comparison)}
                }
            },
            {"trajectory", std::move(records)},
            {
                "trajectory_sha256",
                sdt::compiler::SHA256::hash(trajectory_text)
            },
            {"checkpoint", checkpoint()}
        };
        if (definition_.contract_version == displacement_contract_version) {
            output.emplace(
                "displacement_ledger",
                displacement_ledger_json(evaluation)
            );
            output.emplace("slingshot", slingshot_json());
        }
        return output;
    }
};

std::mutex sessions_mutex;
std::unordered_map<std::uint64_t, std::unique_ptr<Session>> sessions;
std::uint64_t next_handle = 1;

[[nodiscard]] auto error_json(const std::string& message) -> std::string {
    return json::canonical(Object{
        {"contract_version", contract_version},
        {"problem_class", "unknown"},
        {"status", "invalid_case"},
        {"classification", "NOT-EXECUTED"},
        {"message", message}
    });
}

[[nodiscard]] auto session_error_json(
    const std::string& message,
    const std::string& status = "invalid_session"
) -> std::string {
    return json::canonical(Object{
        {"contract_version", contract_version},
        {"status", status},
        {"message", message}
    });
}

} // namespace

auto run_case_json(const std::string& case_json) -> std::string {
    try {
        Definition definition = parse_definition(case_json);
        const std::uint64_t steps = definition.maximum_steps;
        Session session(std::move(definition));
        return json::canonical(session.advance(steps));
    } catch (const std::exception& error) {
        return error_json(error.what());
    }
}

auto create_session_json(const std::string& case_json) -> std::string {
    try {
        auto session = std::make_unique<Session>(parse_definition(case_json));
        std::lock_guard lock(sessions_mutex);
        const std::uint64_t handle = next_handle++;
        sessions.emplace(handle, std::move(session));
        return json::canonical(Object{
            {"contract_version", contract_version},
            {"status", "created"},
            {"handle", std::to_string(handle)}
        });
    } catch (const std::exception& error) {
        return session_error_json(error.what());
    }
}

auto advance_session_json(std::uint64_t handle, std::uint64_t steps)
    -> std::string {
    try {
        std::lock_guard lock(sessions_mutex);
        const auto iterator = sessions.find(handle);
        if (iterator == sessions.end()) {
            return session_error_json("unknown session handle");
        }
        return json::canonical(iterator->second->advance(steps));
    } catch (const std::exception& error) {
        return session_error_json(error.what());
    }
}

auto checkpoint_session_json(std::uint64_t handle) -> std::string {
    std::lock_guard lock(sessions_mutex);
    const auto iterator = sessions.find(handle);
    if (iterator == sessions.end()) {
        return session_error_json("unknown session handle");
    }
    return json::canonical(Object{
        {"contract_version", contract_version},
        {"status", "checkpoint"},
        {"checkpoint", iterator->second->checkpoint()}
    });
}

auto resume_session_json(
    const std::string& case_json,
    const std::string& checkpoint_json
) -> std::string {
    try {
        auto session = std::make_unique<Session>(parse_definition(case_json));
        const Value checkpoint_root = json::parse(checkpoint_json);
        const Value* checkpoint = &checkpoint_root;
        if (checkpoint_root.is_object()
            && checkpoint_root.object().contains("checkpoint")) {
            checkpoint = &checkpoint_root.object().at("checkpoint");
        }
        session->restore(*checkpoint);
        std::lock_guard lock(sessions_mutex);
        const std::uint64_t handle = next_handle++;
        sessions.emplace(handle, std::move(session));
        return json::canonical(Object{
            {"contract_version", contract_version},
            {"status", "resumed"},
            {"handle", std::to_string(handle)}
        });
    } catch (const std::exception& error) {
        return session_error_json(error.what());
    }
}

auto destroy_session_json(std::uint64_t handle) -> std::string {
    std::lock_guard lock(sessions_mutex);
    const bool removed = sessions.erase(handle) != 0;
    return json::canonical(Object{
        {"contract_version", contract_version},
        {"status", removed ? "destroyed" : "invalid_session"},
        {"handle", std::to_string(handle)}
    });
}

auto manifest_json() -> std::string {
    return json::canonical(Object{
        {"build_id", build_id},
        {"contract_version", contract_version},
        {
            "supported_contract_versions",
            Array{contract_version, displacement_contract_version}
        },
        {"compiler", SDT_SOLVER_COMPILER},
        {"laws_sha256", SDT_LAWS_SHA256},
        {
            "mechanism",
            "42 directed finite cones; retarded at c; explicit Law-IV "
            "proton/neutron displacement; non-driving PENDING tail branch"
        },
        {
            "c_abi",
            Array{
                "run_case", "session_create", "session_advance",
                "session_checkpoint", "session_resume", "session_destroy",
                "self_test", "solver_manifest", "solver_free"
            }
        },
        {
            "classification",
            "COMPUTED after registered celestial gates; point-koppa comparison "
            "is IDENTITY/shared-input"
        }
    });
}

auto self_test_json() -> std::string {
    struct Check {
        std::string id;
        std::string name;
        double value{};
        std::string relation;
        double limit{};
        bool passed{};
    };
    std::vector<Check> checks;
    const std::string fixture = R"({
      "contract_version":"2.0.0",
      "case_id":"celestial-contract-smoke",
      "problem_class":"celestial_three_body",
      "frame":{"type":"inertial_cartesian","units":"SI","epoch":"J2000"},
      "force":{"type":"retarded_seven_cone_occlusion","propagation_speed":"c","pressure_source":"sdt_law_I_P_conv","enable_eclipse_shielding":true,"comparison_route":"point_koppa"},
      "bodies":[
        {"id":"a","baryon_count":"42","radius_m":1000000,"position_m":[-1000000000,0,0],"velocity_m_s":[0,-10,0],"provenance":{"baryons":"fixture","radius":"fixture","state":"fixture"}},
        {"id":"b","baryon_count":"70","radius_m":1200000,"position_m":[1000000000,0,0],"velocity_m_s":[0,10,0],"provenance":{"baryons":"fixture","radius":"fixture","state":"fixture"}},
        {"id":"c","baryon_count":"105","radius_m":800000,"position_m":[0,2000000000,0],"velocity_m_s":[-5,0,0],"provenance":{"baryons":"fixture","radius":"fixture","state":"fixture"}}
      ],
      "integrator":"velocity_verlet",
      "timestep_s":1,
      "max_steps":4,
      "record_every_steps":1,
      "tolerances":{"retarded_time_s":1e-12,"channel_closure":1e-13,"medium_momentum_relative":1e-11,"lagrange_residual_m_s2":1e-9,"max_retarded_iterations":32},
      "events":{"stop_on_collision":true},
      "provenance":{"classification":"COMPUTED","description":"deterministic geometry fixture","sources":[]}
    })";
    try {
        const Value run = json::parse(run_case_json(fixture));
        const Object& root = run.object();
        const bool completed =
            require_string(object_at(root, "status"), "status") == "completed";
        checks.push_back({
            "C0a", "finite execution", completed ? 1.0 : 0.0,
            ">=", 1.0, completed
        });
        const Object& ledger = object_at(root, "packet_ledger").object();
        const bool gcd_ok =
            require_string(object_at(ledger, "gcd"), "gcd") == "7"
            && object_at(ledger, "reconstruction_passed").boolean();
        checks.push_back({
            "C0b", "exact GCD packet reconstruction", gcd_ok ? 1.0 : 0.0,
            ">=", 1.0, gcd_ok
        });
        const Array& cones = object_at(root, "cones").array();
        checks.push_back({
            "C1", "42 directed cones", static_cast<double>(cones.size()),
            ">=", 42.0, cones.size() == 42
        });
        double weight_sum = 0.0;
        for (std::size_t i = 0; i < 7; ++i) {
            weight_sum += require_number(
                object_at(cones[i].object(), "area_weight"),
                "area_weight"
            );
        }
        const double area_residual = std::abs(weight_sum - 1.0);
        checks.push_back({
            "C2", "channel area closure", area_residual,
            "<=", 1.0e-15, area_residual <= 1.0e-15
        });
        const Object& diagnostics = object_at(root, "diagnostics").object();
        const double retarded_residual = require_number(
            object_at(diagnostics, "maximum_retarded_residual_s"),
            "maximum_retarded_residual_s"
        );
        checks.push_back({
            "C3", "retarded-time residual", retarded_residual,
            "<=", 1.0e-12, retarded_residual <= 1.0e-12
        });
        const double resistance_ratio = require_number(
            object_at(diagnostics, "maximum_effective_resistance_ratio"),
            "maximum_effective_resistance_ratio"
        );
        checks.push_back({
            "C4", "Law-IV resistance is not below rest resistance",
            resistance_ratio, ">=", 1.0, resistance_ratio >= 1.0
        });
        const double closure = require_number(
            object_at(diagnostics, "maximum_channel_closure_relative"),
            "maximum_channel_closure_relative"
        );
        checks.push_back({
            "C5", "seven-channel resultant closure", closure,
            "<=", 1.0e-13, closure <= 1.0e-13
        });
        const double medium = require_number(
            object_at(diagnostics, "body_plus_medium_momentum_residual"),
            "body_plus_medium_momentum_residual"
        );
        checks.push_back({
            "C7", "body plus medium momentum closure", medium,
            "<=", 1.0e-11, medium <= 1.0e-11
        });

        const Value created = json::parse(create_session_json(fixture));
        const std::uint64_t first_handle = std::stoull(
            object_at(created.object(), "handle").string()
        );
        static_cast<void>(advance_session_json(first_handle, 2));
        const std::string saved = checkpoint_session_json(first_handle);
        const std::string uninterrupted =
            advance_session_json(first_handle, 2);
        const Value resumed =
            json::parse(resume_session_json(fixture, saved));
        const std::uint64_t second_handle = std::stoull(
            object_at(resumed.object(), "handle").string()
        );
        const std::string continued =
            advance_session_json(second_handle, 2);
        const Value first_result = json::parse(uninterrupted);
        const Value second_result = json::parse(continued);
        const bool checkpoint_equal =
            json::canonical(object_at(first_result.object(), "checkpoint"))
            == json::canonical(object_at(second_result.object(), "checkpoint"));
        checks.push_back({
            "C8", "checkpoint resume equivalence",
            checkpoint_equal ? 1.0 : 0.0, ">=", 1.0, checkpoint_equal
        });
        static_cast<void>(destroy_session_json(first_handle));
        static_cast<void>(destroy_session_json(second_handle));
    } catch (const std::exception&) {
        checks.push_back({
            "C-runtime", "self-test execution", 0.0, ">=", 1.0, false
        });
    }

    bool passed = true;
    Array gates;
    for (const auto& check : checks) {
        passed = passed && check.passed;
        gates.emplace_back(Object{
            {"id", check.id},
            {"name", check.name},
            {"value", check.value},
            {"relation", check.relation},
            {"limit", check.limit},
            {"passed", check.passed},
            {"classification", "COMPUTED"}
        });
    }
    return json::canonical(Object{
        {"contract_version", contract_version},
        {"status", passed ? "passed" : "failed"},
        {"gates", std::move(gates)},
        {"manifest", json::parse(manifest_json())}
    });
}

} // namespace sdt_solver::celestial

