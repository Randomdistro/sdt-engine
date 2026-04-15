cmake_minimum_required(VERSION 3.20)
project(crumpiler VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Single binary, zero dependencies
add_executable(crumpiler
    main.cpp
)

target_include_directories(crumpiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Compiler-specific flags
if(MSVC)
    target_compile_options(crumpiler PRIVATE /W4 /permissive-)
else()
    target_compile_options(crumpiler PRIVATE -Wall -Wextra -Wpedantic)
endif()
