cmake_minimum_required(VERSION 3.20)
project(SDT_Horizons_Kinematics_Demo VERSION 1.0 LANGUAGES CXX)

set(
    SDT_EXPORTED_LAWS
    "${CMAKE_CURRENT_SOURCE_DIR}/sdt/include/laws.hpp"
    CACHE FILEPATH
    "Complete laws.hpp exported with this standalone package"
)
if(NOT EXISTS "${SDT_EXPORTED_LAWS}")
    message(
        FATAL_ERROR
        "Exported laws.hpp not found. Set -DSDT_EXPORTED_LAWS=<file>."
    )
endif()
get_filename_component(SDT_EXPORTED_INCLUDE "${SDT_EXPORTED_LAWS}" DIRECTORY)
file(SHA256 "${SDT_EXPORTED_LAWS}" SDT_EXPORTED_LAWS_SHA256)

set(SDT_REPOSITORY_LAWS "${CMAKE_CURRENT_SOURCE_DIR}/../../Engine/include/sdt/laws.hpp")
if(EXISTS "${SDT_REPOSITORY_LAWS}")
    file(SHA256 "${SDT_REPOSITORY_LAWS}" SDT_REPOSITORY_LAWS_SHA256)
    if(NOT SDT_EXPORTED_LAWS_SHA256 STREQUAL SDT_REPOSITORY_LAWS_SHA256)
        message(FATAL_ERROR "Exported laws.hpp is stale relative to the repository canonical header.")
    endif()
endif()
message(STATUS "SDT laws.hpp export SHA-256: ${SDT_EXPORTED_LAWS_SHA256}")

add_executable(jpl_horizons_demo jpl_horizons_demo.cpp)
target_compile_features(jpl_horizons_demo PRIVATE cxx_std_20)
target_include_directories(
    jpl_horizons_demo
    PRIVATE
        "${SDT_EXPORTED_INCLUDE}"
)

if(MSVC)
    target_compile_options(jpl_horizons_demo PRIVATE /W4 /permissive-)
else()
    target_compile_options(
        jpl_horizons_demo
        PRIVATE
            -Wall
            -Wextra
            -Wpedantic
    )
endif()

include(CTest)
if(BUILD_TESTING)
    add_test(
        NAME horizons_synthetic_known_answer
        COMMAND jpl_horizons_demo --self-test
    )
    add_test(
        NAME horizons_de441_fixture
        COMMAND
            jpl_horizons_demo
            --input "${CMAKE_CURRENT_SOURCE_DIR}/examples/jpl_horizons_earth_heliocentric_2002_157_160.csv"
            --output-csv "${CMAKE_CURRENT_BINARY_DIR}/horizons_fixture_results.csv"
            --output-json "${CMAKE_CURRENT_BINARY_DIR}/horizons_fixture_summary.json"
            --fixture-gates
    )
endif()

install(TARGETS jpl_horizons_demo RUNTIME DESTINATION bin)
install(
    FILES README.md DEMONSTRATION_PROTOCOL.md RUN_LOG.md LICENSE
    DESTINATION share/jpl_horizons_demo
)
install(
    DIRECTORY examples/
    DESTINATION share/jpl_horizons_demo/examples
)
install(
    FILES sdt/include/laws.hpp
    DESTINATION share/jpl_horizons_demo/sdt/include
)
