#include <sdt_solver/celestial.hpp>
#include <sdt_solver/json.hpp>
#include <sdt_solver/occlusion_nbody.hpp>
#include <sdt_solver/solver.hpp>

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

namespace {

[[nodiscard]] auto read_file(const char* path) -> std::string {
    std::ifstream input(path, std::ios::binary);
    if (!input) throw std::runtime_error("could not open case file");
    return {
        std::istreambuf_iterator<char>(input),
        std::istreambuf_iterator<char>()
    };
}

[[nodiscard]] auto result_succeeded(const std::string& text) -> bool {
    const auto value = sdt_solver::json::parse(text);
    const auto& status = value.object().at("status").string();
    return status == "completed" || status == "passed";
}

[[nodiscard]] auto session_handle(const std::string& text) -> std::uint64_t {
    const auto value = sdt_solver::json::parse(text);
    const auto& root = value.object();
    if (root.at("status").string() != "created"
        && root.at("status").string() != "resumed") {
        throw std::runtime_error(root.at("message").string());
    }
    return std::stoull(root.at("handle").string());
}

[[nodiscard]] auto is_nbody_case(const std::string& text) -> bool {
    const auto value = sdt_solver::json::parse(text);
    return value.object().at("contract_version").string()
        == sdt_solver::occlusion_nbody::contract_version;
}

} // namespace

int main(int argc, char** argv) {
    try {
        std::string output;
        if (argc == 2 && std::string(argv[1]) == "--self-test") {
            output = sdt_solver::self_test_json();
        } else if (
            argc == 2
            && std::string(argv[1]) == "--celestial-self-test"
        ) {
            output = sdt_solver::celestial::self_test_json();
        } else if (argc == 2 && std::string(argv[1]) == "--manifest") {
            output = sdt_solver::manifest_json();
        } else if (argc == 4 && std::string(argv[1]) == "--chunk") {
            const std::string case_text = read_file(argv[2]);
            const bool nbody = is_nbody_case(case_text);
            const std::uint64_t handle = session_handle(nbody
                ? sdt_solver::occlusion_nbody::create_session_json(case_text)
                : sdt_solver::celestial::create_session_json(case_text));
            output = nbody
                ? sdt_solver::occlusion_nbody::advance_session_json(
                    handle,
                    std::stoull(argv[3])
                )
                : sdt_solver::celestial::advance_session_json(
                    handle,
                    std::stoull(argv[3])
                );
            static_cast<void>(nbody
                ? sdt_solver::occlusion_nbody::destroy_session_json(handle)
                : sdt_solver::celestial::destroy_session_json(handle));
        } else if (argc == 5 && std::string(argv[1]) == "--resume") {
            const std::string case_text = read_file(argv[2]);
            const std::string checkpoint_text = read_file(argv[3]);
            const bool nbody = is_nbody_case(case_text);
            const std::uint64_t handle = session_handle(nbody
                ? sdt_solver::occlusion_nbody::resume_session_json(
                    case_text,
                    checkpoint_text
                )
                : sdt_solver::celestial::resume_session_json(
                    case_text,
                    checkpoint_text
                ));
            output = nbody
                ? sdt_solver::occlusion_nbody::advance_session_json(
                    handle,
                    std::stoull(argv[4])
                )
                : sdt_solver::celestial::advance_session_json(
                    handle,
                    std::stoull(argv[4])
                );
            static_cast<void>(nbody
                ? sdt_solver::occlusion_nbody::destroy_session_json(handle)
                : sdt_solver::celestial::destroy_session_json(handle));
        } else if (argc == 2) {
            output = sdt_solver::run_case_json(read_file(argv[1]));
        } else {
            std::cerr
                << "usage: sdt-dynamics-solver "
                << "--self-test | --celestial-self-test | --manifest | "
                << "CASE.sdtcase.json | --chunk CASE STEPS | "
                << "--resume CASE CHECKPOINT STEPS\n";
            return 2;
        }
        std::cout << output << '\n';
        if (std::string(argv[1]) == "--manifest") return 0;
        return result_succeeded(output) ? 0 : 1;
    } catch (const std::exception& error) {
        std::cerr << "solver error: " << error.what() << '\n';
        return 2;
    }
}
