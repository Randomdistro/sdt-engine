#pragma once

#include <cstdint>
#include <string>

namespace sdt_solver::celestial {

inline constexpr auto contract_version = "2.0.0";
inline constexpr auto displacement_contract_version = "2.1.0";
inline constexpr auto build_id = "gom43-celestial-2.1.0";

[[nodiscard]] auto run_case_json(const std::string& case_json) -> std::string;
[[nodiscard]] auto create_session_json(const std::string& case_json) -> std::string;
[[nodiscard]] auto advance_session_json(
    std::uint64_t handle,
    std::uint64_t steps
) -> std::string;
[[nodiscard]] auto checkpoint_session_json(std::uint64_t handle) -> std::string;
[[nodiscard]] auto resume_session_json(
    const std::string& case_json,
    const std::string& checkpoint_json
) -> std::string;
[[nodiscard]] auto destroy_session_json(std::uint64_t handle) -> std::string;
[[nodiscard]] auto self_test_json() -> std::string;
[[nodiscard]] auto manifest_json() -> std::string;

} // namespace sdt_solver::celestial

