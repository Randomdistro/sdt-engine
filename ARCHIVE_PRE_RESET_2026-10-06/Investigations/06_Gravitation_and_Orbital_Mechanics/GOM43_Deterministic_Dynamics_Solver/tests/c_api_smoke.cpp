#include <sdt_solver/json.hpp>
#include <sdt_solver/solver.hpp>

#include <string>

int main() {
    constexpr auto case_json = R"({
      "contract_version":"1.0.0",
      "case_id":"c-abi-smoke",
      "problem_class":"point_nbody",
      "frame":{"type":"inertial_cartesian","units":"SI"},
      "forces":[{"type":"koppa_pairwise"}],
      "bodies":[
        {"id":"a","position_m":[-1,0,0],"velocity_m_s":[0,-1,0],"koppa_m":1e-18,"collision_radius_m":0},
        {"id":"b","position_m":[1,0,0],"velocity_m_s":[0,1,0],"koppa_m":1e-18,"collision_radius_m":0}
      ],
      "integrator":"velocity_verlet",
      "timestep_s":0.001,
      "duration_s":0.01,
      "record_every_steps":1,
      "tolerances":{"position_m":1e-10,"velocity_m_s":1e-10,"quaternion_norm":1e-12,"max_constraint_iterations":64},
      "gates":[]
    })";
    constexpr auto occlusion_json = R"({
      "contract_version":"3.0.0",
      "case_id":"c-abi-occlusion-smoke",
      "problem_class":"sdt_occlusion_nbody",
      "frame":{"type":"inertial_cartesian","units":"SI"},
      "forces":[{"type":"retarded_seven_circle_occlusion","pressure_source":"sdt_law_I_P_conv","propagation_speed":"c"}],
      "bodies":[
        {"id":"a","baryon_count":"805077908211484772344991472376387066","radius_m":0.01,"collision_radius_m":0.01,"position_m":[-1,0,0],"velocity_m_s":[0,-0.1,0]},
        {"id":"b","baryon_count":"805077908211484772344991472376387066","radius_m":0.01,"collision_radius_m":0.01,"position_m":[1,0,0],"velocity_m_s":[0,0.1,0]}
      ],
      "integrator":"velocity_verlet",
      "timestep_s":0.001,
      "duration_s":0.01,
      "record_every_steps":1,
      "tolerances":{"retarded_time_s":1e-12,"max_retarded_iterations":32},
      "gates":[{"id":"M0"},{"id":"M1"}]
    })";

    char* case_result = run_case(case_json);
    char* created_result = session_create(occlusion_json);
    char* test_result = self_test();
    char* manifest_result = solver_manifest();
    if (case_result == nullptr || created_result == nullptr
        || test_result == nullptr
        || manifest_result == nullptr) {
        solver_free(case_result);
        solver_free(created_result);
        solver_free(test_result);
        solver_free(manifest_result);
        return 1;
    }

    bool passed = false;
    try {
        const auto case_value = sdt_solver::json::parse(case_result);
        const auto created_value = sdt_solver::json::parse(created_result);
        const auto test_value = sdt_solver::json::parse(test_result);
        const auto manifest_value = sdt_solver::json::parse(manifest_result);
        const std::string handle =
            created_value.object().at("handle").string();
        char* advanced_result = session_advance(handle.c_str(), "1");
        char* checkpoint_result = session_checkpoint(handle.c_str());
        char* destroyed_result = session_destroy(handle.c_str());
        const auto advanced_value = sdt_solver::json::parse(advanced_result);
        const auto checkpoint_value = sdt_solver::json::parse(checkpoint_result);
        const auto destroyed_value = sdt_solver::json::parse(destroyed_result);
        passed =
            case_value.object().at("status").string() == "completed"
            && created_value.object().at("status").string() == "created"
            && advanced_value.object().at("status").string() == "running"
            && advanced_value.object().at("interactions").array().size() == 98
            && checkpoint_value.object().at("version").string() == "3.0.0"
            && destroyed_value.object().at("status").string() == "destroyed"
            && test_value.object().at("status").string() == "passed"
            && manifest_value.object().at("contract_version").string()
                == sdt_solver::contract_version;
        solver_free(advanced_result);
        solver_free(checkpoint_result);
        solver_free(destroyed_result);
    } catch (...) {
        passed = false;
    }

    solver_free(case_result);
    solver_free(created_result);
    solver_free(test_result);
    solver_free(manifest_result);
    return passed ? 0 : 1;
}

