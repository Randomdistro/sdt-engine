# CQ12 Emission Engine investigations
set(CQ12_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ12_Emissions)

# Stage A: Pressure-well diagnostic inversion
add_executable(sdt-cq12-pressure-map ${CQ12_DIR}/cq12_pressure_well_map.cpp)
target_link_libraries(sdt-cq12-pressure-map PRIVATE sdt-engine)

# Stage B+: Geometry discovery
add_executable(sdt-cq12-geometry ${CQ12_DIR}/cq12_geometry_discovery.cpp)
target_link_libraries(sdt-cq12-geometry PRIVATE sdt-engine)

# Stage B++: Blind recovery
add_executable(sdt-cq12-blind ${CQ12_DIR}/cq12_blind_recovery.cpp)
target_link_libraries(sdt-cq12-blind PRIVATE sdt-engine)

# Stage B+++: Terrain clustering
add_executable(sdt-cq12-cluster ${CQ12_DIR}/cq12_terrain_cluster.cpp)
target_link_libraries(sdt-cq12-cluster PRIVATE sdt-engine)

# Stage C-fwd: Forward derivation
add_executable(sdt-cq12-forward ${CQ12_DIR}/cq12_forward_derivation.cpp)
target_link_libraries(sdt-cq12-forward PRIVATE sdt-engine)

# Stage C: Structure derivation
add_executable(sdt-cq12-structure ${CQ12_DIR}/cq12_structure_derivation.cpp)
target_link_libraries(sdt-cq12-structure PRIVATE sdt-engine)

# Stage D: Forward emission prediction
add_executable(sdt-cq12-emissions ${CQ12_DIR}/cq12_emissions.cpp)
target_link_libraries(sdt-cq12-emissions PRIVATE sdt-engine)

# Stage E: Multi-electron void geometry
add_executable(sdt-cq12-void-geometry ${CQ12_DIR}/cq12_void_geometry.cpp)
target_link_libraries(sdt-cq12-void-geometry PRIVATE sdt-engine)

# Warning settings
if(MSVC)
    set(CQ12_TARGETS sdt-cq12-pressure-map sdt-cq12-geometry sdt-cq12-blind
        sdt-cq12-cluster sdt-cq12-forward sdt-cq12-structure sdt-cq12-emissions
        sdt-cq12-void-geometry)
    foreach(tgt ${CQ12_TARGETS})
        target_compile_options(${tgt} PRIVATE /W3)
    endforeach()
endif()

# ═══ CQ01 Transfer Function Derivation ═══
set(CQ01_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ01_Transfer_Function_Derivation)

add_executable(sdt-cq01-transfer ${CQ01_DIR}/cq01_transfer_function.cpp)
target_link_libraries(sdt-cq01-transfer PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq01-transfer PRIVATE /W3)
endif()

# ═══ CQ02 Vortex Equilibrium Quantisation ═══
set(CQ02_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ02_Vortex_Equilibrium_Quantisation)

add_executable(sdt-cq02-vortex ${CQ02_DIR}/cq02_vortex_equilibrium.cpp)
target_link_libraries(sdt-cq02-vortex PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq02-vortex PRIVATE /W3)
endif()

# ═══ CQ03 Fine Structure from Topology ═══
set(CQ03_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ03_Fine_Structure_from_Topology)

add_executable(sdt-cq03-fine-structure ${CQ03_DIR}/cq03_fine_structure.cpp)
target_link_libraries(sdt-cq03-fine-structure PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq03-fine-structure PRIVATE /W3)
endif()

# ═══ CQ08 Granular Pulse Mechanics ═══
set(CQ08_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ08_Granular_Pulse_Mechanics)

add_executable(sdt-cq08-pulse-mechanics ${CQ08_DIR}/cq08_granular_pulse_mechanics.cpp)
target_link_libraries(sdt-cq08-pulse-mechanics PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq08-pulse-mechanics PRIVATE /W3)
endif()

# ═══ CQ09 Spation Rotation Investigation ═══
set(CQ09_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ09_Spation_Rotation)

add_executable(sdt-cq09-spation-rotation ${CQ09_DIR}/cq09_spation_rotation_map.cpp)
target_link_libraries(sdt-cq09-spation-rotation PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq09-spation-rotation PRIVATE /W3)
endif()

# ═══ CQ10 Lattice Pulse Propagation ═══
set(CQ10_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ10_Lattice_Pulse_Propagation)

add_executable(sdt-cq10-lattice-pulse ${CQ10_DIR}/cq10_lattice_pulse.cpp)
target_link_libraries(sdt-cq10-lattice-pulse PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq10-lattice-pulse PRIVATE /W3)
endif()

add_executable(sdt-cq10b-torus-mass ${CQ10_DIR}/cq10b_torus_derives_mass.cpp)
target_link_libraries(sdt-cq10b-torus-mass PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq10b-torus-mass PRIVATE /W3)
endif()

# ═══ CQ11 Trefoil Confinement ═══
set(CQ11_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ11_Trefoil_Confinement)

add_executable(sdt-cq11-trefoil-confinement ${CQ11_DIR}/cq11_trefoil_confinement.cpp)
target_link_libraries(sdt-cq11-trefoil-confinement PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq11-trefoil-confinement PRIVATE /W3)
endif()

# ═══ CQ13 Emission Prediction Engine ═══
set(CQ13_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ13_Emission_Prediction)

add_executable(sdt-cq13-engine ${CQ13_DIR}/cq13_emission_engine.cpp)
target_link_libraries(sdt-cq13-engine PRIVATE sdt-engine)
target_include_directories(sdt-cq13-engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CQ12_Emissions)

if(MSVC)
    target_compile_options(sdt-cq13-engine PRIVATE /W3)
endif()

# ═══ CQ15 Spation Depth Engine ═══
set(CQ15_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ15_Spation_Depth_Engine)

add_executable(sdt-cq15-depth-engine ${CQ15_DIR}/cq15_spation_depth_engine.cpp)
target_link_libraries(sdt-cq15-depth-engine PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq15-depth-engine PRIVATE /W3)
endif()

# ═══ CQ16 k-Hierarchy Advantage ═══
set(CQ16_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ16_k_Hierarchy_Advantage)

add_executable(sdt-cq16-k-hierarchy ${CQ16_DIR}/cq16_k_hierarchy.cpp)
target_link_libraries(sdt-cq16-k-hierarchy PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq16-k-hierarchy PRIVATE /W3)
endif()
