cmake_minimum_required(VERSION 3.24)
project(sdt_dynamics_solver VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

get_filename_component(SDT_REPOSITORY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../.." ABSOLUTE)
set(SDT_ENGINE_INCLUDE "${SDT_REPOSITORY_ROOT}/Engine/include")
set(SDT_COMPILER_INCLUDE "${SDT_REPOSITORY_ROOT}/Compiler/include")
set(SDT_LAWS_HEADER "${SDT_ENGINE_INCLUDE}/sdt/laws.hpp")

if(NOT EXISTS "${SDT_LAWS_HEADER}")
    message(FATAL_ERROR "Canonical laws header not found: ${SDT_LAWS_HEADER}")
endif()

file(SHA256 "${SDT_LAWS_HEADER}" SDT_LAWS_SHA256)
set(
    SDT_SOLVER_COMPILER
    "${CMAKE_CXX_COMPILER_ID}-${CMAKE_CXX_COMPILER_VERSION}"
)

add_library(
    sdt-dynamics-core
    STATIC
    src/solver.cpp
    src/celestial.cpp
    src/occlusion_nbody.cpp
    src/self_tests.cpp
    src/c_api.cpp
)
target_include_directories(
    sdt-dynamics-core
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${SDT_ENGINE_INCLUDE}"
        "${SDT_COMPILER_INCLUDE}"
)
target_compile_definitions(
    sdt-dynamics-core
    PRIVATE
        SDT_LAWS_SHA256="${SDT_LAWS_SHA256}"
        SDT_SOLVER_COMPILER="${SDT_SOLVER_COMPILER}"
)

if(MSVC)
    target_compile_options(
        sdt-dynamics-core
        PRIVATE /W4 /permissive- /fp:strict /utf-8 /openmp
    )
else()
    target_compile_options(
        sdt-dynamics-core
        PRIVATE -Wall -Wextra -Wpedantic -ffp-contract=off
    )
endif()

if(EMSCRIPTEN)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.1.45)
        message(
            FATAL_ERROR
            "Emscripten 3.1.45 or newer is required; found "
            "${CMAKE_CXX_COMPILER_VERSION}"
        )
    endif()
    add_executable(sdt-dynamics-wasm src/wasm_entry.cpp)
    target_link_libraries(sdt-dynamics-wasm PRIVATE sdt-dynamics-core)
    set_target_properties(
        sdt-dynamics-wasm
        PROPERTIES
            OUTPUT_NAME "sdt-dynamics-core"
            SUFFIX ".js"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/app/wasm"
    )
    target_link_options(
        sdt-dynamics-wasm
        PRIVATE
            "SHELL:-s MODULARIZE=1"
            "SHELL:-s EXPORT_NAME=createSdtDynamicsModule"
            "SHELL:-s ENVIRONMENT=worker"
            "SHELL:-s FILESYSTEM=0"
            "SHELL:-s ALLOW_MEMORY_GROWTH=1"
            "SHELL:-s ASSERTIONS=1"
            "SHELL:-s EXPORTED_FUNCTIONS=['_run_case','_session_create','_session_advance','_session_checkpoint','_session_resume','_session_destroy','_self_test','_solver_manifest','_solver_free','_malloc','_free']"
            "SHELL:-s EXPORTED_RUNTIME_METHODS=['HEAPU8']"
            "SHELL:--no-entry"
    )
else()
    add_executable(sdt-dynamics-solver src/cli.cpp)
    target_link_libraries(sdt-dynamics-solver PRIVATE sdt-dynamics-core)
    add_executable(sdt-dynamics-c-api-smoke tests/c_api_smoke.cpp)
    target_link_libraries(sdt-dynamics-c-api-smoke PRIVATE sdt-dynamics-core)

    enable_testing()
    add_test(
        NAME sdt-dynamics-self-test
        COMMAND sdt-dynamics-solver --self-test
    )
    add_test(
        NAME sdt-dynamics-manifest
        COMMAND sdt-dynamics-solver --manifest
    )
    add_test(
        NAME sdt-dynamics-c-api-smoke
        COMMAND sdt-dynamics-c-api-smoke
    )
endif()

