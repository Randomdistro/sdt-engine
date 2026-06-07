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

# ═══ CQ04 State28D Force Ratio Constants (superseded by CQ01+CQ16) ═══
set(CQ04_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ04_State28D_Force_Ratio_Constants)

add_executable(sdt-cq04-force-ratios ${CQ04_DIR}/cq04_force_ratio_constants.cpp)
target_link_libraries(sdt-cq04-force-ratios PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq04-force-ratios PRIVATE /W3)
endif()

# ═══ CQ05 Proton-Electron Mass Ratio (early derivation) ═══
set(CQ05_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ05_Proton_Electron_Mass_Ratio)

add_executable(sdt-cq05-mass-ratio ${CQ05_DIR}/cq05_mass_ratio.cpp)
target_link_libraries(sdt-cq05-mass-ratio PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq05-mass-ratio PRIVATE /W3)
endif()

# ═══ CQ06 Eclipse Saturation Model ═══
set(CQ06_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ06_Eclipse_Saturation_Model)

add_executable(sdt-cq06-eclipse ${CQ06_DIR}/cq06_eclipse_saturation.cpp)
target_link_libraries(sdt-cq06-eclipse PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq06-eclipse PRIVATE /W3)
endif()

# ═══ CQ19 Milky Way Occlusion Map ═══
set(CQ19_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ19_Milky_Way_Occlusion_Map)

add_executable(sdt-cq19     ${CQ19_DIR}/cq19_mw_occlusion_map.cpp)
add_executable(sdt-cq19b    ${CQ19_DIR}/cq19b_galactic_nucleus_shells.cpp)
add_executable(sdt-cq19c    ${CQ19_DIR}/cq19c_binding_proof.cpp)
add_executable(sdt-cq19d    ${CQ19_DIR}/cq19d_baryon_count.cpp)
add_executable(sdt-cq19e    ${CQ19_DIR}/cq19e_spiral_arms.cpp)

foreach(t sdt-cq19 sdt-cq19b sdt-cq19c sdt-cq19d sdt-cq19e)
    target_link_libraries(${t} PRIVATE sdt-engine)
    if(MSVC)
        target_compile_options(${t} PRIVATE /W3)
    else()
        target_compile_options(${t} PRIVATE -O2)
    endif()
endforeach()

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

# ═══ CQ17 Proton-Electron Mass Ratio ═══
set(CQ17_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ17_Proton_Electron_Mass_Ratio)

add_executable(sdt-cq17-mass-ratio ${CQ17_DIR}/cq17_mass_ratio_solver.cpp)
target_link_libraries(sdt-cq17-mass-ratio PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq17-mass-ratio PRIVATE /W3)
endif()

add_executable(sdt-cq17-28d ${CQ17_DIR}/cq17_28d_formal.cpp)
target_link_libraries(sdt-cq17-28d PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq17-28d PRIVATE /W3)
endif()

# ---- CQ18: Gravitational Redshift Decomposition ----
set(CQ18_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ18_Redshift_Decomposition)

add_executable(sdt-cq18a ${CQ18_DIR}/cq18a_solar_zdecomp.cpp)
add_executable(sdt-cq18b ${CQ18_DIR}/cq18b_multiplanet_zdecomp.cpp)
add_executable(sdt-cq18c ${CQ18_DIR}/cq18c_agn_zdecomp.cpp)
add_executable(sdt-cq18d ${CQ18_DIR}/cq18d_sne_h0_correction.cpp)
add_executable(sdt-cq18e ${CQ18_DIR}/cq18e_zladder.cpp)
add_executable(sdt-cq18f ${CQ18_DIR}/cq18f_great_attractor.cpp)
add_executable(sdt-cq18g ${CQ18_DIR}/cq18g_perp_ring.cpp)
add_executable(sdt-cq18g-live ${CQ18_DIR}/cq18g_live.cpp)
add_executable(sdt-cq18g-cf4  ${CQ18_DIR}/cq18g_cf4.cpp)
add_executable(sdt-cq18h      ${CQ18_DIR}/cq18h_cone_shell.cpp)

foreach(t sdt-cq18a sdt-cq18b sdt-cq18c sdt-cq18d sdt-cq18e sdt-cq18f sdt-cq18g sdt-cq18g-live sdt-cq18g-cf4 sdt-cq18h)
    if(MSVC)
        target_compile_options(${t} PRIVATE /W3)
    else()
        target_compile_options(${t} PRIVATE -O2)
    endif()
endforeach()

# ═══ E46 Galaxy Rotation Curves (Eclipse Saturation) ═══
set(E46_DIR ${CMAKE_CURRENT_SOURCE_DIR}/E46_Galaxy_Rotation_Curves)
add_executable(sdt-e46 ${E46_DIR}/e46_sparc_rotation_curves.cpp)
target_link_libraries(sdt-e46 PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-e46 PRIVATE /W3)
else()
    target_compile_options(sdt-e46 PRIVATE -O2)
endif()

# ═══ CQ23 3D Volumetric Integration ═══
set(CQ23_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ23_3D_Volumetric_Integration)
add_executable(sdt-cq23 ${CQ23_DIR}/cq23_3d_volumetric_integration.cpp)
target_link_libraries(sdt-cq23 PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq23 PRIVATE /W3)
else()
    target_compile_options(sdt-cq23 PRIVATE -O2)
endif()

# ═══ CQ20 Galactic Spation Topology ═══
set(CQ20_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ20_Galactic_Spation_Topology)

add_executable(sdt-cq20 ${CQ20_DIR}/cq20_spation_topology.cpp)
add_executable(sdt-cq20b ${CQ20_DIR}/cq20b_torus_spation_count.cpp)
add_executable(sdt-cq20c ${CQ20_DIR}/cq20c_torus_differential.cpp)
add_executable(sdt-cq20d ${CQ20_DIR}/cq20d_galactic_occlusion.cpp)
add_executable(sdt-cq20e ${CQ20_DIR}/cq20e_bulge_from_sagA.cpp)
add_executable(sdt-cq20f ${CQ20_DIR}/cq20f_trefoil_convection.cpp)
target_link_libraries(sdt-cq20 PRIVATE sdt-engine)
target_link_libraries(sdt-cq20b PRIVATE sdt-engine)
target_link_libraries(sdt-cq20c PRIVATE sdt-engine)
target_link_libraries(sdt-cq20d PRIVATE sdt-engine)
target_link_libraries(sdt-cq20e PRIVATE sdt-engine)
target_link_libraries(sdt-cq20f PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq20 PRIVATE /W3)
    target_compile_options(sdt-cq20b PRIVATE /W3)
    target_compile_options(sdt-cq20c PRIVATE /W3)
    target_compile_options(sdt-cq20d PRIVATE /W3)
    target_compile_options(sdt-cq20e PRIVATE /W3)
    target_compile_options(sdt-cq20f PRIVATE /W3)
else()
    target_compile_options(sdt-cq20 PRIVATE -O2)
    target_compile_options(sdt-cq20b PRIVATE -O2)
    target_compile_options(sdt-cq20c PRIVATE -O2)
    target_compile_options(sdt-cq20d PRIVATE -O2)
    target_compile_options(sdt-cq20e PRIVATE -O2)
    target_compile_options(sdt-cq20f PRIVATE -O2)
endif()

# ═══ CQ20g Convergence Occlusion (bidirectional gradient differential) ═══
add_executable(sdt-cq20g ${CQ20_DIR}/cq20g_convergence_occlusion.cpp)
target_link_libraries(sdt-cq20g PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-cq20g PRIVATE /W3)
else()
    target_compile_options(sdt-cq20g PRIVATE -O2)
endif()

# ═══ CQ21 Proton-Spation Interface: CMB-Derived Ontic Rate ═══
add_executable(sdt-cq21 ${CQ20_DIR}/cq21_proton_spation_cmb.cpp)
target_link_libraries(sdt-cq21 PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-cq21 PRIVATE /W3)
else()
    target_compile_options(sdt-cq21 PRIVATE -O2)
endif()

# ═══ CQ22 Galactic Skymap: Lattice Warping & Great Attractor ═══
add_executable(sdt-cq22 ${CQ20_DIR}/cq22_galactic_skymap.cpp)
target_link_libraries(sdt-cq22 PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-cq22 PRIVATE /W3)
else()
    target_compile_options(sdt-cq22 PRIVATE -O2)
endif()

# === SDT Galactic Calculator - Universal rotation curve engine ===
set(GALCALC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GalacticCalculator)
add_executable(sdt-galaxy-calc ${GALCALC_DIR}/sdt_galaxy_calc.cpp)
target_link_libraries(sdt-galaxy-calc PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-galaxy-calc PRIVATE /W3)
else()
    target_compile_options(sdt-galaxy-calc PRIVATE -O2)
endif()

# ═══ CQ25 Atomicus Nuclear Grammar ═══════════════════════════════════════════
# Exact integer coordinate transform (Z,A) → (n_d,n_t) on the nuclear chart.
# 287-nuclide natural basis, compile-time verified by static_assert ×7.
# Three-stage investigation: grammar table → fission snap → ASCII nuclide map.
set(CQ25_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ25_Atomicus_Nuclear_Grammar)
add_executable(sdt-cq25 ${CQ25_DIR}/cq25_atomicus_grammar.cpp)
target_link_libraries(sdt-cq25 PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-cq25 PRIVATE /W4)
else()
    target_compile_options(sdt-cq25 PRIVATE -O2 -Wall)
endif()

# ═══ CQ27 Stellar Fusion and Nuclear Growth ══════════════════════════════════
# Evaluates deu/tri fusion, solid-angle occlusion integrals, trefoil rotational
# spin gearing, temperature-dependent EC, and electronic shell mirror maps.
set(CQ27_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CQ27_Stellar_Fusion_and_Nuclear_Growth)
add_executable(sdt-cq27 ${CQ27_DIR}/cq27_stellar_fusion_growth.cpp)
target_link_libraries(sdt-cq27 PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-cq27 PRIVATE /W4)
else()
    target_compile_options(sdt-cq27 PRIVATE -O2 -Wall)
endif()

