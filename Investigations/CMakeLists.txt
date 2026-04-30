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

# ═══ CQ13 Emission Prediction Engine ═══
set(CQ13_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ13_Emission_Prediction)

add_executable(sdt-cq13-engine ${CQ13_DIR}/cq13_emission_engine.cpp)
target_link_libraries(sdt-cq13-engine PRIVATE sdt-engine)
target_include_directories(sdt-cq13-engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CQ12_Emissions)

if(MSVC)
    target_compile_options(sdt-cq13-engine PRIVATE /W3)
endif()

