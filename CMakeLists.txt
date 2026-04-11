cmake_minimum_required(VERSION 3.20)
project(sdt-engine
    VERSION 5.0
    DESCRIPTION "Spatial Displacement Theory — Canonical Engine"
    LANGUAGES CXX
)

# C++20, no exceptions needed but keep them for diagnostics
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only engine library
add_library(sdt-engine INTERFACE)
target_include_directories(sdt-engine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine/include
)

# Benchmarks
add_subdirectory(Benchmarks)
