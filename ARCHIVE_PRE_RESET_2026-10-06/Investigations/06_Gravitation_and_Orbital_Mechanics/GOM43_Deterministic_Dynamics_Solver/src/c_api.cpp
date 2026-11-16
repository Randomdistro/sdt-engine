#include <sdt_solver/celestial.hpp>
#include <sdt_solver/json.hpp>
#include <sdt_solver/occlusion_nbody.hpp>
#include <sdt_solver/solver.hpp>

#include <charconv>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <string>

namespace {

[[nodiscard]] auto copy_result(const std::string& value) -> char* {
    auto* buffer = static_cast<char*>(std::malloc(value.size() + 1));
    if (buffer == nullptr) return nullptr;
    std::memcpy(buffer, value.c_str(), value.size() + 1);
    return buffer;
}

[[nodiscard]] auto parse_u64(const char* text, std::uint64_t& value) -> bool {
    if (text == nullptr || *text == '\0') return false;
    const char* end = text + std::strlen(text);
    const auto conversion = std::from_chars(text, end, value);
    return conversion.ec == std::errc{} && conversion.ptr == end;
}

[[nodiscard]] auto is_nbody_case(const char* text) -> bool {
    if (text == nullptr) return false;
    try {
        const auto value = sdt_solver::json::parse(text);
        return value.is_object()
            && value.object().contains("contract_version")
            && value.object().at("contract_version").is_string()
            && value.object().at("contract_version").string()
                == sdt_solver::occlusion_nbody::contract_version;
    } catch (const std::exception&) {
        return false;
    }
}

} // namespace

extern "C" {

auto run_case(const char* case_json) -> char* {
    if (case_json == nullptr) {
        return copy_result(sdt_solver::run_case_json(""));
    }
    return copy_result(sdt_solver::run_case_json(case_json));
}

auto session_create(const char* case_json) -> char* {
    if (is_nbody_case(case_json)) {
        return copy_result(
            sdt_solver::occlusion_nbody::create_session_json(case_json)
        );
    }
    return copy_result(sdt_solver::celestial::create_session_json(
        case_json == nullptr ? "" : case_json
    ));
}

auto session_advance(
    const char* handle_decimal,
    const char* steps_decimal
) -> char* {
    std::uint64_t handle = 0;
    std::uint64_t steps = 0;
    if (!parse_u64(handle_decimal, handle)
        || !parse_u64(steps_decimal, steps)) {
        return copy_result(
            R"({"message":"invalid decimal handle or step count","status":"invalid_session"})"
        );
    }
    return copy_result(sdt_solver::occlusion_nbody::owns_handle(handle)
        ? sdt_solver::occlusion_nbody::advance_session_json(handle, steps)
        : sdt_solver::celestial::advance_session_json(handle, steps));
}

auto session_checkpoint(const char* handle_decimal) -> char* {
    std::uint64_t handle = 0;
    if (!parse_u64(handle_decimal, handle)) {
        return copy_result(
            R"({"message":"invalid decimal handle","status":"invalid_session"})"
        );
    }
    return copy_result(sdt_solver::occlusion_nbody::owns_handle(handle)
        ? sdt_solver::occlusion_nbody::checkpoint_session_json(handle)
        : sdt_solver::celestial::checkpoint_session_json(handle));
}

auto session_resume(
    const char* case_json,
    const char* checkpoint_json
) -> char* {
    if (is_nbody_case(case_json)) {
        return copy_result(sdt_solver::occlusion_nbody::resume_session_json(
            case_json == nullptr ? "" : case_json,
            checkpoint_json == nullptr ? "" : checkpoint_json
        ));
    }
    return copy_result(sdt_solver::celestial::resume_session_json(
        case_json == nullptr ? "" : case_json,
        checkpoint_json == nullptr ? "" : checkpoint_json
    ));
}

auto session_destroy(const char* handle_decimal) -> char* {
    std::uint64_t handle = 0;
    if (!parse_u64(handle_decimal, handle)) {
        return copy_result(
            R"({"message":"invalid decimal handle","status":"invalid_session"})"
        );
    }
    return copy_result(sdt_solver::occlusion_nbody::owns_handle(handle)
        ? sdt_solver::occlusion_nbody::destroy_session_json(handle)
        : sdt_solver::celestial::destroy_session_json(handle));
}

auto self_test() -> char* {
    return copy_result(sdt_solver::self_test_json());
}

auto solver_manifest() -> char* {
    return copy_result(sdt_solver::manifest_json());
}

void solver_free(char* buffer) {
    std::free(buffer);
}

}
