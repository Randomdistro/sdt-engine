add_executable(sdt-benchmarks
    B01_B25/benchmarks_b01_b25.cpp
)

target_link_libraries(sdt-benchmarks PRIVATE sdt-engine)

# Enable all warnings
if(MSVC)
    target_compile_options(sdt-benchmarks PRIVATE /W4)
else()
    target_compile_options(sdt-benchmarks PRIVATE -Wall -Wextra -Wpedantic)
endif()
