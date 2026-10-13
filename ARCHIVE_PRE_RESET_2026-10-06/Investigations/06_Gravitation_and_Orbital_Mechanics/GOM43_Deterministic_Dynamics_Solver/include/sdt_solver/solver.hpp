#pragma once

#include <string>

namespace sdt_solver {

inline constexpr auto contract_version = "1.0.0";
inline constexpr auto build_id = "gom43-solver-1.0.0";

[[nodiscard]] auto run_case_json(const std::string& case_json) -> std::string;
[[nodiscard]] auto self_test_json() -> std::string;
[[nodiscard]] auto manifest_json() -> std::string;

} // namespace sdt_solver

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#define SDT_SOLVER_EXPORT EMSCRIPTEN_KEEPALIVE
#elif defined(_WIN32)
#define SDT_SOLVER_EXPORT __declspec(dllexport)
#else
#define SDT_SOLVER_EXPORT __attribute__((visibility("default")))
#endif

extern "C" {

SDT_SOLVER_EXPORT auto run_case(const char* case_json) -> char*;
SDT_SOLVER_EXPORT auto session_create(const char* case_json) -> char*;
SDT_SOLVER_EXPORT auto session_advance(
    const char* handle_decimal,
    const char* steps_decimal
) -> char*;
SDT_SOLVER_EXPORT auto session_checkpoint(const char* handle_decimal) -> char*;
SDT_SOLVER_EXPORT auto session_resume(
    const char* case_json,
    const char* checkpoint_json
) -> char*;
SDT_SOLVER_EXPORT auto session_destroy(const char* handle_decimal) -> char*;
SDT_SOLVER_EXPORT auto self_test() -> char*;
SDT_SOLVER_EXPORT auto solver_manifest() -> char*;
SDT_SOLVER_EXPORT void solver_free(char* buffer);

}

