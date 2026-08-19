#include <laws.hpp>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace {

constexpr double seconds_per_day = 86'400.0;
constexpr double metres_per_kilometre = 1'000.0;
constexpr double c = sdt::laws::measured::c;

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

[[nodiscard]] constexpr auto operator*(Vec3 a, double scalar) noexcept -> Vec3 {
    return {a.x * scalar, a.y * scalar, a.z * scalar};
}

[[nodiscard]] constexpr auto operator/(Vec3 a, double scalar) noexcept -> Vec3 {
    return {a.x / scalar, a.y / scalar, a.z / scalar};
}

[[nodiscard]] constexpr auto dot(Vec3 a, Vec3 b) noexcept -> double {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

[[nodiscard]] auto norm(Vec3 value) noexcept -> double {
    return std::sqrt(dot(value, value));
}

struct State {
    double jd_tdb{};
    std::string calendar;
    Vec3 position_m;
    Vec3 velocity_mps;
};

struct HorizonsTable {
    std::string source_path;
    std::string target;
    std::string centre;
    std::string ephemeris;
    std::string units;
    std::string reference_frame;
    std::vector<State> states;
};

struct Estimate {
    double median_koppa_m{};
    double relative_mad{};
    std::vector<double> positive_koppa_m;
};

struct Residual {
    Vec3 position_m;
    Vec3 velocity_mps;
    double position_residual_km{};
    double velocity_residual_kms{};
};

struct Gate {
    std::string id;
    bool pass{};
    std::string detail;
};

[[nodiscard]] auto trim(std::string value) -> std::string {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return {};
    }
    const auto last = value.find_last_not_of(" \t\r\n");
    return value.substr(first, last - first + 1);
}

[[nodiscard]] auto after_colon(const std::string& line) -> std::string {
    const auto position = line.find(':');
    return position == std::string::npos ? std::string{} : trim(line.substr(position + 1));
}

[[nodiscard]] auto before_source_tag(std::string value) -> std::string {
    const auto tag = value.find("{source:");
    if (tag != std::string::npos) {
        value.resize(tag);
    }
    return trim(value);
}

[[nodiscard]] auto source_tag(const std::string& value) -> std::string {
    const auto begin = value.find("{source:");
    if (begin == std::string::npos) {
        return {};
    }
    const auto content = begin + std::string_view{"{source:"}.size();
    const auto end = value.find('}', content);
    return trim(value.substr(content, end == std::string::npos ? end : end - content));
}

[[nodiscard]] auto split_csv(const std::string& line) -> std::vector<std::string> {
    std::vector<std::string> fields;
    std::string field;
    bool quoted = false;
    for (std::size_t index = 0; index < line.size(); ++index) {
        const char ch = line[index];
        if (ch == '"') {
            if (quoted && index + 1 < line.size() && line[index + 1] == '"') {
                field.push_back('"');
                ++index;
            } else {
                quoted = !quoted;
            }
        } else if (ch == ',' && !quoted) {
            fields.push_back(trim(field));
            field.clear();
        } else {
            field.push_back(ch);
        }
    }
    fields.push_back(trim(field));
    return fields;
}

[[nodiscard]] auto parse_number(const std::string& text, std::string_view label) -> double {
    std::size_t consumed = 0;
    const double value = std::stod(text, &consumed);
    if (consumed != text.size() || !std::isfinite(value)) {
        throw std::runtime_error("invalid " + std::string(label) + ": " + text);
    }
    return value;
}

[[nodiscard]] auto parse_horizons(const std::string& path) -> HorizonsTable {
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("cannot open Horizons input: " + path);
    }

    HorizonsTable table;
    table.source_path = path;
    bool in_states = false;
    bool saw_start = false;
    bool saw_end = false;
    std::string line;
    std::size_t line_number = 0;

    while (std::getline(input, line)) {
        ++line_number;
        line = trim(line);
        if (line.rfind("Target body name:", 0) == 0) {
            const auto value = after_colon(line);
            table.target = before_source_tag(value);
            if (table.ephemeris.empty()) {
                table.ephemeris = source_tag(value);
            }
        } else if (line.rfind("Center body name:", 0) == 0) {
            const auto value = after_colon(line);
            table.centre = before_source_tag(value);
            if (table.ephemeris.empty()) {
                table.ephemeris = source_tag(value);
            }
        } else if (line.rfind("Output units", 0) == 0) {
            table.units = after_colon(line);
        } else if (line.rfind("Reference frame", 0) == 0) {
            table.reference_frame = after_colon(line);
        } else if (line == "$$SOE") {
            in_states = true;
            saw_start = true;
        } else if (line == "$$EOE") {
            in_states = false;
            saw_end = true;
        } else if (in_states && !line.empty()) {
            const auto fields = split_csv(line);
            if (fields.size() < 8) {
                throw std::runtime_error(
                    "Horizons row has fewer than eight columns at line "
                    + std::to_string(line_number)
                );
            }
            State state;
            state.jd_tdb = parse_number(fields[0], "JDTDB");
            state.calendar = fields[1];
            state.position_m = {
                parse_number(fields[2], "X") * metres_per_kilometre,
                parse_number(fields[3], "Y") * metres_per_kilometre,
                parse_number(fields[4], "Z") * metres_per_kilometre
            };
            state.velocity_mps = {
                parse_number(fields[5], "VX") * metres_per_kilometre,
                parse_number(fields[6], "VY") * metres_per_kilometre,
                parse_number(fields[7], "VZ") * metres_per_kilometre
            };
            table.states.push_back(std::move(state));
        }
    }

    if (!saw_start || !saw_end) {
        throw std::runtime_error("Horizons input is missing $$SOE or $$EOE markers");
    }
    if (table.units != "KM-S") {
        throw std::runtime_error("unsupported Horizons units: expected KM-S, got " + table.units);
    }
    if (table.states.size() < 3) {
        throw std::runtime_error("at least three Horizons states are required");
    }
    for (std::size_t index = 1; index < table.states.size(); ++index) {
        if (!(table.states[index].jd_tdb > table.states[index - 1].jd_tdb)) {
            throw std::runtime_error("Horizons epochs must be strictly increasing");
        }
    }
    return table;
}

[[nodiscard]] auto median(std::vector<double> values) -> double {
    if (values.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    const auto middle = values.begin() + static_cast<std::ptrdiff_t>(values.size() / 2);
    std::nth_element(values.begin(), middle, values.end());
    const double upper = *middle;
    if (values.size() % 2 != 0) {
        return upper;
    }
    const auto lower = std::max_element(values.begin(), middle);
    return (*lower + upper) / 2.0;
}

[[nodiscard]] auto estimate_koppa(const std::vector<State>& states) -> Estimate {
    Estimate estimate;
    estimate.positive_koppa_m.reserve(states.size() - 2);
    for (std::size_t index = 1; index + 1 < states.size(); ++index) {
        const double dt = (states[index + 1].jd_tdb - states[index - 1].jd_tdb)
                        * seconds_per_day;
        if (!(dt > 0.0)) {
            continue;
        }
        const Vec3 acceleration =
            (states[index + 1].velocity_mps - states[index - 1].velocity_mps) / dt;
        const Vec3 position = states[index].position_m;
        const double radius = norm(position);
        if (!(radius > 0.0)) {
            continue;
        }
        const double koppa = -dot(acceleration, position) * radius / (c * c);
        if (std::isfinite(koppa) && koppa > 0.0) {
            estimate.positive_koppa_m.push_back(koppa);
        }
    }
    estimate.median_koppa_m = median(estimate.positive_koppa_m);
    std::vector<double> deviations;
    deviations.reserve(estimate.positive_koppa_m.size());
    for (const double value : estimate.positive_koppa_m) {
        deviations.push_back(std::abs(value - estimate.median_koppa_m));
    }
    const double mad = median(std::move(deviations));
    estimate.relative_mad = mad / estimate.median_koppa_m;
    return estimate;
}

[[nodiscard]] auto acceleration(Vec3 position, double koppa_m) -> Vec3 {
    const double radius = norm(position);
    if (!(radius > 0.0) || !std::isfinite(radius)) {
        throw std::runtime_error("propagator reached a zero or non-finite radius");
    }
    return position * (-c * c * koppa_m / (radius * radius * radius));
}

void verlet_step(Vec3& position, Vec3& velocity, double koppa_m, double dt) {
    const Vec3 initial_acceleration = acceleration(position, koppa_m);
    const Vec3 next_position =
        position + velocity * dt + initial_acceleration * (0.5 * dt * dt);
    const Vec3 next_acceleration = acceleration(next_position, koppa_m);
    velocity = velocity + (initial_acceleration + next_acceleration) * (0.5 * dt);
    position = next_position;
}

[[nodiscard]] auto propagate(
    const std::vector<State>& reference,
    double koppa_m,
    double maximum_step_seconds
) -> std::vector<Residual> {
    if (!(maximum_step_seconds > 0.0)) {
        throw std::runtime_error("maximum propagation step must be positive");
    }
    std::vector<Residual> results;
    results.reserve(reference.size());

    Vec3 position = reference.front().position_m;
    Vec3 velocity = reference.front().velocity_mps;
    results.push_back({position, velocity, 0.0, 0.0});

    for (std::size_t index = 1; index < reference.size(); ++index) {
        const double interval =
            (reference[index].jd_tdb - reference[index - 1].jd_tdb) * seconds_per_day;
        const auto substeps = static_cast<std::size_t>(
            std::max(1.0, std::ceil(std::abs(interval) / maximum_step_seconds))
        );
        const double step = interval / static_cast<double>(substeps);
        for (std::size_t count = 0; count < substeps; ++count) {
            verlet_step(position, velocity, koppa_m, step);
        }
        results.push_back({
            position,
            velocity,
            norm(position - reference[index].position_m) / metres_per_kilometre,
            norm(velocity - reference[index].velocity_mps) / metres_per_kilometre
        });
    }
    return results;
}

[[nodiscard]] auto cadence_seconds(const std::vector<State>& states) -> double {
    std::vector<double> intervals;
    intervals.reserve(states.size() - 1);
    for (std::size_t index = 1; index < states.size(); ++index) {
        intervals.push_back(
            (states[index].jd_tdb - states[index - 1].jd_tdb) * seconds_per_day
        );
    }
    return median(std::move(intervals));
}

[[nodiscard]] auto json_escape(const std::string& value) -> std::string {
    std::ostringstream escaped;
    for (const unsigned char ch : value) {
        switch (ch) {
            case '\\': escaped << "\\\\"; break;
            case '"': escaped << "\\\""; break;
            case '\n': escaped << "\\n"; break;
            case '\r': escaped << "\\r"; break;
            case '\t': escaped << "\\t"; break;
            default:
                if (ch < 0x20) {
                    escaped << "\\u"
                            << std::hex << std::setw(4) << std::setfill('0')
                            << static_cast<int>(ch)
                            << std::dec << std::setfill(' ');
                } else {
                    escaped << static_cast<char>(ch);
                }
        }
    }
    return escaped.str();
}

[[nodiscard]] auto write_csv(
    const std::string& path,
    const HorizonsTable& table,
    const std::vector<Residual>& residuals,
    double koppa_m
) -> std::size_t {
    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error("cannot open output CSV: " + path);
    }
    output << "jd_tdb,calendar,x_reference_km,y_reference_km,z_reference_km,"
              "vx_reference_kms,vy_reference_kms,vz_reference_kms,"
              "x_demo_km,y_demo_km,z_demo_km,vx_demo_kms,vy_demo_kms,vz_demo_kms,"
              "position_residual_km,velocity_residual_kms,koppa_m\n";
    output << std::setprecision(16);
    for (std::size_t index = 0; index < table.states.size(); ++index) {
        const auto& state = table.states[index];
        const auto& result = residuals[index];
        output
            << state.jd_tdb << ",\"" << state.calendar << "\","
            << state.position_m.x / metres_per_kilometre << ','
            << state.position_m.y / metres_per_kilometre << ','
            << state.position_m.z / metres_per_kilometre << ','
            << state.velocity_mps.x / metres_per_kilometre << ','
            << state.velocity_mps.y / metres_per_kilometre << ','
            << state.velocity_mps.z / metres_per_kilometre << ','
            << result.position_m.x / metres_per_kilometre << ','
            << result.position_m.y / metres_per_kilometre << ','
            << result.position_m.z / metres_per_kilometre << ','
            << result.velocity_mps.x / metres_per_kilometre << ','
            << result.velocity_mps.y / metres_per_kilometre << ','
            << result.velocity_mps.z / metres_per_kilometre << ','
            << result.position_residual_km << ','
            << result.velocity_residual_kms << ','
            << koppa_m << '\n';
    }
    if (!output) {
        throw std::runtime_error("failed while writing output CSV: " + path);
    }
    return table.states.size();
}

void write_json(
    std::ostream& output,
    const HorizonsTable& table,
    const Estimate& estimate,
    double cadence,
    double maximum_step,
    double maximum_position_residual,
    double maximum_velocity_residual,
    const std::vector<Gate>& gates
) {
    output << std::setprecision(16);
    output << "{\n"
           << "  \"schema_version\": \"1.0\",\n"
           << "  \"demonstration\": \"Horizons koppa two-body consistency\",\n"
           << "  \"scientific_result\": false,\n"
           << "  \"source_file\": \"" << json_escape(table.source_path) << "\",\n"
           << "  \"target\": \"" << json_escape(table.target) << "\",\n"
           << "  \"centre\": \"" << json_escape(table.centre) << "\",\n"
           << "  \"source_ephemeris\": \"" << json_escape(table.ephemeris) << "\",\n"
           << "  \"units\": \"" << json_escape(table.units) << "\",\n"
           << "  \"reference_frame\": \"" << json_escape(table.reference_frame) << "\",\n"
           << "  \"row_count\": " << table.states.size() << ",\n"
           << "  \"cadence_seconds\": " << cadence << ",\n"
           << "  \"estimator\": \"median positive radial acceleration from centred velocity difference\",\n"
           << "  \"integrator\": \"velocity-Verlet two-body\",\n"
           << "  \"maximum_step_seconds\": " << maximum_step << ",\n"
           << "  \"koppa_m\": " << estimate.median_koppa_m << ",\n"
           << "  \"koppa_relative_mad\": " << estimate.relative_mad << ",\n"
           << "  \"maximum_position_residual_km\": " << maximum_position_residual << ",\n"
           << "  \"maximum_velocity_residual_kms\": " << maximum_velocity_residual << ",\n"
           << "  \"gates\": [\n";
    for (std::size_t index = 0; index < gates.size(); ++index) {
        output << "    {\"id\":\"" << json_escape(gates[index].id)
               << "\",\"status\":\"" << (gates[index].pass ? "PASS" : "FAIL")
               << "\",\"detail\":\"" << json_escape(gates[index].detail) << "\"}"
               << (index + 1 == gates.size() ? "\n" : ",\n");
    }
    output << "  ]\n}\n";
}

[[nodiscard]] auto contains(const std::string& text, std::string_view token) -> bool {
    return text.find(token) != std::string::npos;
}

[[nodiscard]] auto all_pass(const std::vector<Gate>& gates) -> bool {
    return std::all_of(gates.begin(), gates.end(), [](const Gate& gate) {
        return gate.pass;
    });
}

[[nodiscard]] auto self_test() -> bool {
    constexpr double registered_koppa = 2.0;
    constexpr double radius = 1.0e8;
    const double speed =
        sdt::laws::bridge::circular_speed_from_koppa(registered_koppa, radius);
    const double period = 2.0 * std::numbers::pi * radius / speed;
    const double period_koppa =
        sdt::laws::bridge::koppa_from_circular_period(radius, period);
    const double bridge_relative_error =
        std::abs(period_koppa - registered_koppa) / registered_koppa;
    const double expected_acceleration = speed * speed / radius;
    const double acceleration_relative_error = std::abs(
        sdt::laws::bridge::radial_acceleration_from_koppa(
            registered_koppa,
            radius
        ) - expected_acceleration
    ) / expected_acceleration;
    constexpr std::size_t sample_count = 30'001;

    std::vector<State> synthetic;
    synthetic.reserve(sample_count);
    for (std::size_t index = 0; index < sample_count; ++index) {
        const double fraction =
            static_cast<double>(index) / static_cast<double>(sample_count - 1);
        const double angle = 2.0 * std::numbers::pi * fraction;
        synthetic.push_back({
            period * fraction / seconds_per_day,
            "synthetic",
            {radius * std::cos(angle), radius * std::sin(angle), 0.0},
            {-speed * std::sin(angle), speed * std::cos(angle), 0.0}
        });
    }

    const auto estimate = estimate_koppa(synthetic);
    const double koppa_relative_error =
        std::abs(estimate.median_koppa_m - registered_koppa) / registered_koppa;

    Vec3 position = synthetic.front().position_m;
    Vec3 velocity = synthetic.front().velocity_mps;
    constexpr std::size_t propagation_steps = 20'000;
    const double step = period / static_cast<double>(propagation_steps);
    for (std::size_t index = 0; index < propagation_steps; ++index) {
        verlet_step(position, velocity, registered_koppa, step);
    }
    const double closure_relative = norm(position - synthetic.front().position_m) / radius;

    const bool estimate_pass = koppa_relative_error <= 1.0e-8;
    const bool closure_pass = step <= 60.0 && closure_relative <= 2.0e-6;
    const bool bridge_pass =
        bridge_relative_error <= 1.0e-12
        && acceleration_relative_error <= 1.0e-12;
    std::cout << "O1 canonical T17 bridge: " << (bridge_pass ? "PASS" : "FAIL")
              << " period_rel_error=" << std::setprecision(10)
              << bridge_relative_error
              << " acceleration_rel_error=" << acceleration_relative_error << '\n';
    std::cout << "O1 synthetic koppa: " << (estimate_pass ? "PASS" : "FAIL")
              << " rel_error=" << std::setprecision(10) << koppa_relative_error << '\n';
    std::cout << "O1 synthetic closure: " << (closure_pass ? "PASS" : "FAIL")
              << " rel_position=" << closure_relative
              << " step_s=" << step << '\n';
    return bridge_pass && estimate_pass && closure_pass;
}

struct Options {
    std::string input_path;
    std::string output_csv{"jpl_horizons_demo_results.csv"};
    std::string output_json{"jpl_horizons_demo_summary.json"};
    double maximum_step_seconds{60.0};
    bool fixture_gates{};
    bool self_test{};
};

void usage(const char* executable) {
    std::cerr
        << "Usage:\n"
        << "  " << executable << " --self-test\n"
        << "  " << executable
        << " --input HORIZONS.csv [--output-csv FILE] [--output-json FILE]\n"
        << "      [--max-step-s 60] [--fixture-gates]\n";
}

[[nodiscard]] auto parse_options(int argc, char** argv) -> Options {
    Options options;
    for (int index = 1; index < argc; ++index) {
        const std::string argument = argv[index];
        auto require_value = [&](std::string_view option) -> std::string {
            if (++index >= argc) {
                throw std::runtime_error("missing value for " + std::string(option));
            }
            return argv[index];
        };
        if (argument == "--self-test") {
            options.self_test = true;
        } else if (argument == "--input") {
            options.input_path = require_value(argument);
        } else if (argument == "--output-csv") {
            options.output_csv = require_value(argument);
        } else if (argument == "--output-json") {
            options.output_json = require_value(argument);
        } else if (argument == "--max-step-s") {
            options.maximum_step_seconds =
                parse_number(require_value(argument), "maximum step");
        } else if (argument == "--fixture-gates") {
            options.fixture_gates = true;
        } else if (argument == "--help" || argument == "-h") {
            usage(argv[0]);
            std::exit(0);
        } else {
            throw std::runtime_error("unknown argument: " + argument);
        }
    }
    return options;
}

} // namespace

int main(int argc, char** argv) {
    try {
        const Options options = parse_options(argc, argv);
        if (options.self_test) {
            return self_test() ? 0 : 1;
        }
        if (options.input_path.empty()) {
            usage(argv[0]);
            return 2;
        }

        const HorizonsTable table = parse_horizons(options.input_path);
        const Estimate estimate = estimate_koppa(table.states);
        if (estimate.positive_koppa_m.empty()
            || !std::isfinite(estimate.median_koppa_m)
            || !(estimate.median_koppa_m > 0.0)) {
            throw std::runtime_error("no positive finite koppa estimates were produced");
        }

        const auto residuals = propagate(
            table.states,
            estimate.median_koppa_m,
            options.maximum_step_seconds
        );
        double maximum_position_residual = 0.0;
        double maximum_velocity_residual = 0.0;
        for (const auto& residual : residuals) {
            maximum_position_residual =
                std::max(maximum_position_residual, residual.position_residual_km);
            maximum_velocity_residual =
                std::max(maximum_velocity_residual, residual.velocity_residual_kms);
        }
        const double cadence = cadence_seconds(table.states);

        std::vector<Gate> gates;
        gates.push_back({
            "O0-parser",
            table.states.size() >= 3 && cadence > 0.0 && table.units == "KM-S",
            "rows=" + std::to_string(table.states.size())
                + ", cadence_s=" + std::to_string(cadence)
        });
        if (options.fixture_gates) {
            gates.push_back({
                "O0-fixture-metadata",
                table.states.size() >= 300
                    && contains(table.target, "Earth")
                    && contains(table.centre, "Sun")
                    && contains(table.ephemeris, "DE441"),
                "target=" + table.target + ", centre=" + table.centre
                    + ", source=" + table.ephemeris
            });
            gates.push_back({
                "O2-estimator-stability",
                estimate.relative_mad <= 0.002,
                "relative_mad=" + std::to_string(estimate.relative_mad)
            });
            gates.push_back({
                "O3-DE441-comparison",
                maximum_position_residual <= 20'000.0
                    && maximum_velocity_residual <= 0.05,
                "max_position_km=" + std::to_string(maximum_position_residual)
                    + ", max_velocity_kms=" + std::to_string(maximum_velocity_residual)
            });
        }

        const std::size_t written_rows =
            write_csv(options.output_csv, table, residuals, estimate.median_koppa_m);
        gates.push_back({
            "O4-row-completeness",
            written_rows == table.states.size() && residuals.size() == table.states.size(),
            "input=" + std::to_string(table.states.size())
                + ", output=" + std::to_string(written_rows)
        });

        std::ofstream json(options.output_json);
        gates.push_back({
            "O5-provenance",
            static_cast<bool>(json),
            json ? "summary=" + options.output_json : "cannot open summary output"
        });
        if (json) {
            write_json(
                json,
                table,
                estimate,
                cadence,
                options.maximum_step_seconds,
                maximum_position_residual,
                maximum_velocity_residual,
                gates
            );
            json.flush();
            if (!json) {
                gates.back().pass = false;
                gates.back().detail = "failed while writing summary output";
            }
        }

        std::cout << "Horizons kinematics demonstration\n"
                  << "  target: " << table.target << '\n'
                  << "  centre: " << table.centre << '\n'
                  << "  ephemeris: " << table.ephemeris << '\n'
                  << "  rows: " << table.states.size() << '\n'
                  << "  koppa: " << std::setprecision(12)
                  << estimate.median_koppa_m << " m\n"
                  << "  relative MAD: " << estimate.relative_mad << '\n'
                  << "  max position residual: " << maximum_position_residual << " km\n"
                  << "  max velocity residual: " << maximum_velocity_residual << " km/s\n";
        for (const auto& gate : gates) {
            std::cout << "  " << gate.id << ": "
                      << (gate.pass ? "PASS" : "FAIL")
                      << " — " << gate.detail << '\n';
        }
        std::cout
            << "Scope: consistency demonstration only; not a DE/SPICE replacement.\n";
        return all_pass(gates) ? 0 : 1;
    } catch (const std::exception& error) {
        std::cerr << "ERROR: " << error.what() << '\n';
        return 2;
    }
}

