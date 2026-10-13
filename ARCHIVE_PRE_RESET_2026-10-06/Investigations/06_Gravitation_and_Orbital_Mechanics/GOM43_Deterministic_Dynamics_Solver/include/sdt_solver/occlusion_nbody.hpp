#pragma once

#include <cstdint>
#include <string>

namespace sdt_solver::occlusion_nbody {

inline constexpr auto contract_version = "3.0.0";
inline constexpr auto build_id = "gom43-multibody-seven-circle-3.0.0";
inline constexpr std::uint64_t handle_base = 0x4000000000000000ULL;

[[nodiscard]] auto owns_handle(std::uint64_t handle) noexcept -> bool;
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

} // namespace sdt_solver::occlusion_nbody
