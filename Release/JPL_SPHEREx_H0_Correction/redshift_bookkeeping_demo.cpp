#include <laws.hpp>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace {

constexpr double c_kms = sdt::laws::measured::c / 1'000.0;
constexpr std::size_t component_count = 4;
constexpr std::array<std::string_view, component_count> component_names{
    "host_grav", "host_rotation", "observer_motion", "other"
};

struct Record {
    std::string id;
    double distance_mpc{};
    double z_input{};
    std::array<double, component_count> correction{};
    std::array<bool, component_count> already_applied{};
};

struct Result {
    std::array<double, component_count> correction_due{};
    std::array<double, component_count> delta_h0_if_not_subtracted{};
    double total_correction_due{};
    double z_residual{};
    bool in_linear_scope{};
    double h0_input_linear{std::numeric_limits<double>::quiet_NaN()};
    double h0_residual_linear{std::numeric_limits<double>::quiet_NaN()};
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
    if (quoted) {
        throw std::runtime_error("unterminated CSV quote");
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

[[nodiscard]] auto parse_flag(const std::string& text, std::string_view label) -> bool {
    if (text == "0") {
        return false;
    }
    if (text == "1") {
        return true;
    }
    throw std::runtime_error(
        std::string(label) + " must be binary 0 or 1, got: " + text
    );
}

[[nodiscard]] auto expected_header() -> std::vector<std::string> {
    return {
        "id",
        "distance_mpc",
        "z_input",
        "z_host_grav",
        "z_host_rotation",
        "z_observer_motion",
        "z_other",
        "host_grav_already_applied",
        "host_rotation_already_applied",
        "observer_motion_already_applied",
        "other_already_applied"
    };
}

[[nodiscard]] auto parse_catalogue(const std::string& path) -> std::vector<Record> {
    std::ifstream input(path);
    if (!input) {
        throw std::runtime_error("cannot open input CSV: " + path);
    }

    std::vector<Record> records;
    std::set<std::string> identifiers;
    std::string line;
    std::size_t line_number = 0;
    bool header_seen = false;

    while (std::getline(input, line)) {
        ++line_number;
        line = trim(line);
        if (line.empty() || line.front() == '#') {
            continue;
        }
        const auto fields = split_csv(line);
        if (!header_seen) {
            if (fields != expected_header()) {
                throw std::runtime_error(
                    "input header does not match schema version 1.0"
                );
            }
            header_seen = true;
            continue;
        }
        if (fields.size() != expected_header().size()) {
            throw std::runtime_error(
                "expected 11 columns at line " + std::to_string(line_number)
            );
        }

        Record record;
        record.id = fields[0];
        if (record.id.empty()) {
            throw std::runtime_error("empty identifier at line " + std::to_string(line_number));
        }
        if (!identifiers.insert(record.id).second) {
            throw std::runtime_error("duplicate identifier: " + record.id);
        }
        record.distance_mpc = parse_number(fields[1], "distance_mpc");
        record.z_input = parse_number(fields[2], "z_input");
        if (!(record.distance_mpc > 0.0)) {
            throw std::runtime_error("distance_mpc must be positive for " + record.id);
        }
        for (std::size_t index = 0; index < component_count; ++index) {
            record.correction[index] = parse_number(
                fields[3 + index],
                std::string{"z_"} + std::string{component_names[index]}
            );
            record.already_applied[index] = parse_flag(
                fields[7 + index],
                std::string{component_names[index]} + "_already_applied"
            );
        }
        records.push_back(std::move(record));
    }

    if (!header_seen) {
        throw std::runtime_error("input CSV has no schema header");
    }
    if (records.empty()) {
        throw std::runtime_error("input CSV has no data rows");
    }
    return records;
}

[[nodiscard]] auto analyse(const Record& record) -> Result {
    Result result;
    for (std::size_t index = 0; index < component_count; ++index) {
        result.correction_due[index] =
            record.already_applied[index] ? 0.0 : record.correction[index];
        result.total_correction_due += result.correction_due[index];
        result.delta_h0_if_not_subtracted[index] =
            c_kms * result.correction_due[index] / record.distance_mpc;
    }
    result.z_residual = record.z_input - result.total_correction_due;
    result.in_linear_scope = result.z_residual > 0.0 && result.z_residual <= 0.1;
    if (result.in_linear_scope) {
        result.h0_input_linear = c_kms * record.z_input / record.distance_mpc;
        result.h0_residual_linear = c_kms * result.z_residual / record.distance_mpc;
    }
    return result;
}

[[nodiscard]] auto analyse_all(const std::vector<Record>& records) -> std::vector<Result> {
    std::vector<Result> results;
    results.reserve(records.size());
    for (const auto& record : records) {
        results.push_back(analyse(record));
    }
    return results;
}

[[nodiscard]] auto csv_string(const std::string& value) -> std::string {
    std::string escaped{"\""};
    for (const char ch : value) {
        if (ch == '"') {
            escaped += "\"\"";
        } else {
            escaped += ch;
        }
    }
    escaped += '"';
    return escaped;
}

void write_optional(std::ostream& output, double value, bool available) {
    if (available) {
        output << value;
    }
}

[[nodiscard]] auto write_results_csv(
    const std::string& path,
    const std::vector<Record>& records,
    const std::vector<Result>& results
) -> std::size_t {
    std::ofstream output(path);
    if (!output) {
        throw std::runtime_error("cannot open output CSV: " + path);
    }
    output
        << "id,distance_mpc,z_input,z_total_subtracted,z_residual,in_linear_scope,"
           "h0_input_linear_kms_mpc,h0_residual_linear_kms_mpc,"
           "z_host_grav_due,z_host_rotation_due,z_observer_motion_due,z_other_due,"
           "delta_h0_if_host_grav_not_subtracted,"
           "delta_h0_if_host_rotation_not_subtracted,"
           "delta_h0_if_observer_motion_not_subtracted,"
           "delta_h0_if_other_not_subtracted\n";
    output << std::setprecision(16);
    for (std::size_t row = 0; row < records.size(); ++row) {
        const auto& record = records[row];
        const auto& result = results[row];
        output
            << csv_string(record.id) << ','
            << record.distance_mpc << ','
            << record.z_input << ','
            << result.total_correction_due << ','
            << result.z_residual << ','
            << (result.in_linear_scope ? 1 : 0) << ',';
        write_optional(output, result.h0_input_linear, result.in_linear_scope);
        output << ',';
        write_optional(output, result.h0_residual_linear, result.in_linear_scope);
        for (const double value : result.correction_due) {
            output << ',' << value;
        }
        for (const double value : result.delta_h0_if_not_subtracted) {
            output << ',' << value;
        }
        output << '\n';
    }
    if (!output) {
        throw std::runtime_error("failed while writing output CSV: " + path);
    }
    return records.size();
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

void write_summary_json(
    std::ostream& output,
    const std::string& source_path,
    const std::vector<Record>& records,
    const std::vector<Result>& results,
    const std::vector<Gate>& gates
) {
    std::size_t linear_scope_count = 0;
    std::size_t out_of_scope_count = 0;
    for (const auto& result : results) {
        if (result.in_linear_scope) {
            ++linear_scope_count;
        } else {
            ++out_of_scope_count;
        }
    }
    output << "{\n"
           << "  \"schema_version\": \"1.0\",\n"
           << "  \"demonstration\": \"explicit redshift-correction bookkeeping\",\n"
           << "  \"scientific_result\": false,\n"
           << "  \"source_file\": \"" << json_escape(source_path) << "\",\n"
           << "  \"row_count\": " << records.size() << ",\n"
           << "  \"linear_scope_count\": " << linear_scope_count << ",\n"
           << "  \"out_of_scope_count\": " << out_of_scope_count << ",\n"
           << "  \"external_target_h0\": null,\n"
           << "  \"gates\": [\n";
    for (std::size_t index = 0; index < gates.size(); ++index) {
        output << "    {\"id\":\"" << json_escape(gates[index].id)
               << "\",\"status\":\"" << (gates[index].pass ? "PASS" : "FAIL")
               << "\",\"detail\":\"" << json_escape(gates[index].detail) << "\"}"
               << (index + 1 == gates.size() ? "\n" : ",\n");
    }
    output << "  ]\n}\n";
}

[[nodiscard]] auto all_pass(const std::vector<Gate>& gates) -> bool {
    return std::all_of(gates.begin(), gates.end(), [](const Gate& gate) {
        return gate.pass;
    });
}

[[nodiscard]] auto synthetic_records() -> std::vector<Record> {
    constexpr double registered_h0 = 70.0;
    const auto residual_z = [](double distance) {
        return registered_h0 * distance / c_kms;
    };

    std::vector<Record> records{
        {
            "synthetic-all-due",
            10.0,
            residual_z(10.0) + 5.0e-7 + 2.0e-4 - 8.0e-4 + 1.0e-5,
            {5.0e-7, 2.0e-4, -8.0e-4, 1.0e-5},
            {false, false, false, false}
        },
        {
            "synthetic-host-other-applied",
            20.0,
            residual_z(20.0) - 1.5e-4 + 9.0e-4,
            {6.0e-7, -1.5e-4, 9.0e-4, -2.0e-5},
            {true, false, false, true}
        },
        {
            "synthetic-rotation-observer-applied",
            40.0,
            residual_z(40.0) + 4.0e-7 + 3.0e-5,
            {4.0e-7, 1.0e-4, -5.0e-4, 3.0e-5},
            {false, true, true, false}
        },
        {
            "synthetic-other-applied",
            100.0,
            residual_z(100.0) + 8.0e-7 - 2.0e-4 + 4.0e-4,
            {8.0e-7, -2.0e-4, 4.0e-4, 5.0e-5},
            {false, false, false, true}
        },
        {
            "synthetic-high-z-scope-guard",
            1'000.0,
            0.201,
            {1.0e-3, 0.0, 0.0, 0.0},
            {false, true, true, true}
        }
    };
    return records;
}

struct FixtureChecks {
    double maximum_recovery_error{};
    bool every_component_has_applied_example{true};
    bool applied_components_subtract_zero{true};
    bool sign_preservation{true};
    std::size_t in_scope_count{};
    std::size_t out_of_scope_count{};
};

[[nodiscard]] auto check_fixture(
    const std::vector<Record>& records,
    const std::vector<Result>& results
) -> FixtureChecks {
    FixtureChecks checks;
    std::array<bool, component_count> saw_applied{};
    bool saw_positive_sensitivity = false;
    bool saw_negative_sensitivity = false;
    for (std::size_t row = 0; row < records.size(); ++row) {
        const auto& record = records[row];
        const auto& result = results[row];
        if (result.in_linear_scope) {
            ++checks.in_scope_count;
            checks.maximum_recovery_error = std::max(
                checks.maximum_recovery_error,
                std::abs(result.h0_residual_linear - 70.0)
            );
        } else {
            ++checks.out_of_scope_count;
        }
        for (std::size_t component = 0; component < component_count; ++component) {
            if (record.already_applied[component]) {
                saw_applied[component] = true;
                checks.applied_components_subtract_zero =
                    checks.applied_components_subtract_zero
                    && result.correction_due[component] == 0.0;
            }
            const double due = result.correction_due[component];
            const double sensitivity = result.delta_h0_if_not_subtracted[component];
            if (due > 0.0) {
                saw_positive_sensitivity = true;
                checks.sign_preservation =
                    checks.sign_preservation && sensitivity > 0.0;
            } else if (due < 0.0) {
                saw_negative_sensitivity = true;
                checks.sign_preservation =
                    checks.sign_preservation && sensitivity < 0.0;
            }
        }
    }
    checks.every_component_has_applied_example =
        std::all_of(saw_applied.begin(), saw_applied.end(), [](bool value) {
            return value;
        });
    checks.sign_preservation =
        checks.sign_preservation && saw_positive_sensitivity && saw_negative_sensitivity;
    return checks;
}

[[nodiscard]] auto self_test() -> bool {
    bool parser_rejection = false;
    try {
        static_cast<void>(parse_flag("2", "test_flag"));
    } catch (const std::exception&) {
        parser_rejection = true;
    }

    const auto records = synthetic_records();
    const auto results = analyse_all(records);
    const auto checks = check_fixture(records, results);
    const bool recovery =
        checks.in_scope_count == 4
        && checks.maximum_recovery_error <= 1.0e-10;
    const bool applied =
        checks.every_component_has_applied_example
        && checks.applied_components_subtract_zero;
    const bool scope = checks.out_of_scope_count == 1;

    std::cout << "R0 parser rejection: " << (parser_rejection ? "PASS" : "FAIL") << '\n'
              << "R1 synthetic recovery: " << (recovery ? "PASS" : "FAIL")
              << " max_error=" << std::setprecision(12)
              << checks.maximum_recovery_error << '\n'
              << "R2 applied flags: " << (applied ? "PASS" : "FAIL") << '\n'
              << "R3 sign preservation: "
              << (checks.sign_preservation ? "PASS" : "FAIL") << '\n'
              << "R5 scope guard: " << (scope ? "PASS" : "FAIL") << '\n';
    return parser_rejection && recovery && applied && checks.sign_preservation && scope;
}

struct Options {
    std::string input_path;
    std::string output_csv{"redshift_bookkeeping_results.csv"};
    std::string output_json{"redshift_bookkeeping_summary.json"};
    bool fixture_gates{};
    bool self_test{};
};

void usage(const char* executable) {
    std::cerr
        << "Usage:\n"
        << "  " << executable << " --self-test\n"
        << "  " << executable
        << " --input CATALOGUE.csv [--output-csv FILE] [--output-json FILE]"
           " [--fixture-gates]\n";
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

        const auto records = parse_catalogue(options.input_path);
        const auto results = analyse_all(records);
        std::vector<Gate> gates{
            {
                "R0-parser",
                !records.empty(),
                "validated_rows=" + std::to_string(records.size())
            }
        };

        if (options.fixture_gates) {
            const auto checks = check_fixture(records, results);
            gates.push_back({
                "R1-synthetic-known-answer",
                checks.in_scope_count == 4
                    && checks.maximum_recovery_error <= 1.0e-6,
                "eligible_rows=" + std::to_string(checks.in_scope_count)
                    + ", maximum_H0_error="
                    + std::to_string(checks.maximum_recovery_error)
            });
            gates.push_back({
                "R2-no-double-subtraction",
                checks.every_component_has_applied_example
                    && checks.applied_components_subtract_zero,
                "each component has an already-applied fixture and subtracts zero"
            });
            gates.push_back({
                "R3-sign-preservation",
                checks.sign_preservation,
                "positive and negative correction sensitivities retain sign"
            });
            gates.push_back({
                "R5-scope-guard",
                checks.out_of_scope_count == 1,
                "out_of_scope_rows=" + std::to_string(checks.out_of_scope_count)
            });
        }

        const std::size_t written =
            write_results_csv(options.output_csv, records, results);
        gates.push_back({
            "R4-row-completeness",
            written == records.size() && results.size() == records.size(),
            "input=" + std::to_string(records.size())
                + ", output=" + std::to_string(written)
        });

        std::ofstream json(options.output_json);
        gates.push_back({
            "R6-provenance",
            static_cast<bool>(json),
            json ? "summary=" + options.output_json : "cannot open summary output"
        });
        if (json) {
            write_summary_json(json, options.input_path, records, results, gates);
            json.flush();
            if (!json) {
                gates.back().pass = false;
                gates.back().detail = "failed while writing summary output";
            }
        }

        std::size_t in_scope = 0;
        for (const auto& result : results) {
            if (result.in_linear_scope) {
                ++in_scope;
            }
        }
        std::cout << "Redshift-correction bookkeeping demonstration\n"
                  << "  rows: " << records.size() << '\n'
                  << "  low-z linear diagnostic rows: " << in_scope << '\n'
                  << "  out-of-scope rows: " << records.size() - in_scope << '\n';
        for (const auto& gate : gates) {
            std::cout << "  " << gate.id << ": "
                      << (gate.pass ? "PASS" : "FAIL")
                      << " — " << gate.detail << '\n';
        }
        std::cout
            << "Scope: bookkeeping demonstration only; no Hubble-tension result.\n";
        return all_pass(gates) ? 0 : 1;
    } catch (const std::exception& error) {
        std::cerr << "ERROR: " << error.what() << '\n';
        return 2;
    }
}

