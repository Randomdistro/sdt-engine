cmake_minimum_required(VERSION 3.24)
project(sdt_celestial_and_multibody_solver VERSION 3.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
file(SHA256 "${CMAKE_CURRENT_SOURCE_DIR}/include/sdt/laws.hpp" SDT_LAWS_SHA256)
set(SDT_SOLVER_COMPILER "${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}")
add_library(sdt-celestial-core STATIC
  src/solver.cpp src/celestial.cpp src/occlusion_nbody.cpp
  src/self_tests.cpp src/c_api.cpp)
target_include_directories(sdt-celestial-core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(sdt-celestial-core PRIVATE
  SDT_LAWS_SHA256="${SDT_LAWS_SHA256}"
  SDT_SOLVER_COMPILER="${SDT_SOLVER_COMPILER}")
if(MSVC)
  target_compile_options(sdt-celestial-core PRIVATE /W4 /permissive- /fp:strict /utf-8 /openmp)
else()
  target_compile_options(sdt-celestial-core PRIVATE -Wall -Wextra -Wpedantic -ffp-contract=off)
endif()
if(EMSCRIPTEN)
  add_executable(sdt-celestial-wasm src/wasm_entry.cpp)
  target_link_libraries(sdt-celestial-wasm PRIVATE sdt-celestial-core)
  set_target_properties(sdt-celestial-wasm PROPERTIES
    OUTPUT_NAME "sdt-dynamics-core" SUFFIX ".js"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/web/wasm")
  target_link_options(sdt-celestial-wasm PRIVATE
    "SHELL:-s MODULARIZE=1"
    "SHELL:-s EXPORT_NAME=createSdtDynamicsModule"
    "SHELL:-s ENVIRONMENT=worker"
    "SHELL:-s FILESYSTEM=0"
    "SHELL:-s ALLOW_MEMORY_GROWTH=1"
    "SHELL:-s ASSERTIONS=1"
    "SHELL:-s EXPORTED_FUNCTIONS=['_run_case','_session_create','_session_advance','_session_checkpoint','_session_resume','_session_destroy','_self_test','_solver_manifest','_solver_free','_malloc','_free']"
    "SHELL:-s EXPORTED_RUNTIME_METHODS=['HEAPU8']"
    "SHELL:--no-entry")
else()
  add_executable(sdt-celestial-solver src/cli.cpp)
  target_link_libraries(sdt-celestial-solver PRIVATE sdt-celestial-core)
  add_executable(sdt-celestial-c-api-smoke tests/c_api_smoke.cpp)
  target_link_libraries(sdt-celestial-c-api-smoke PRIVATE sdt-celestial-core)
  enable_testing()
  add_test(NAME solver-self-test COMMAND sdt-celestial-solver --self-test)
  add_test(NAME celestial-self-test COMMAND sdt-celestial-solver --celestial-self-test)
  add_test(NAME c-api-smoke COMMAND sdt-celestial-c-api-smoke)
endif()
