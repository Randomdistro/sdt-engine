cmake_minimum_required(VERSION 3.16)
project(CQ18_Redshift_Decomposition CXX)
set(CMAKE_CXX_STANDARD 20)

# CQ18a — Solar system calibration
add_executable(cq18a cq18a_solar_zdecomp.cpp)
target_compile_options(cq18a PRIVATE -O2)

# CQ18b — Multi-planet survey
add_executable(cq18b cq18b_multiplanet_zdecomp.cpp)
target_compile_options(cq18b PRIVATE -O2)

# CQ18c — AGN z_grav systematic
add_executable(cq18c cq18c_agn_zdecomp.cpp)
target_compile_options(cq18c PRIVATE -O2)

# CQ18d — SNe Ia H0 tension
add_executable(cq18d cq18d_sne_h0_correction.cpp)
target_compile_options(cq18d PRIVATE -O2)

# CQ18e — Cosmological redshift gradient ladder (z=0.001 to z=7.6)
add_executable(cq18e cq18e_zladder.cpp)
target_compile_options(cq18e PRIVATE -O2)
