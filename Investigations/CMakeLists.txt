# ─────────────────────────────────────────────────────────────────────────────
# Investigations build.  Folders are now grouped by physics domain (NN_Domain/).
# Each *_DIR variable below points at the domain-qualified path so the build
# resolves after the 2026-06-20 domain reorganisation.  See INDEX.html / README.md.
# ─────────────────────────────────────────────────────────────────────────────

# APS01 Emission Engine investigations
set(CQ12_DIR ${CMAKE_CURRENT_SOURCE_DIR}/04_Atomic_Physics_and_Spectroscopy/CQ12_Emissions)

# Stage A: Pressure-well diagnostic inversion
add_executable(sdt-aps01-pressure-map ${CQ12_DIR}/cq12_pressure_well_map.cpp)
target_link_libraries(sdt-aps01-pressure-map PRIVATE sdt-engine)

# Stage B+: Geometry discovery
add_executable(sdt-aps01-geometry ${CQ12_DIR}/cq12_geometry_discovery.cpp)
target_link_libraries(sdt-aps01-geometry PRIVATE sdt-engine)

# Stage B++: Blind recovery
add_executable(sdt-aps01-blind ${CQ12_DIR}/cq12_blind_recovery.cpp)
target_link_libraries(sdt-aps01-blind PRIVATE sdt-engine)

# Stage B+++: Terrain clustering
add_executable(sdt-aps01-cluster ${CQ12_DIR}/cq12_terrain_cluster.cpp)
target_link_libraries(sdt-aps01-cluster PRIVATE sdt-engine)

# Stage C-fwd: Forward derivation
add_executable(sdt-aps01-forward ${CQ12_DIR}/cq12_forward_derivation.cpp)
target_link_libraries(sdt-aps01-forward PRIVATE sdt-engine)

# Stage C: Structure derivation
add_executable(sdt-aps01-structure ${CQ12_DIR}/cq12_structure_derivation.cpp)
target_link_libraries(sdt-aps01-structure PRIVATE sdt-engine)

# Stage D: Forward emission prediction
add_executable(sdt-aps01-emissions ${CQ12_DIR}/cq12_emissions.cpp)
target_link_libraries(sdt-aps01-emissions PRIVATE sdt-engine)

# Stage E: Multi-electron void geometry
add_executable(sdt-aps01-void-geometry ${CQ12_DIR}/cq12_void_geometry.cpp)
target_link_libraries(sdt-aps01-void-geometry PRIVATE sdt-engine)

# Warning settings
if(MSVC)
    set(CQ12_TARGETS sdt-aps01-pressure-map sdt-aps01-geometry sdt-aps01-blind
        sdt-aps01-cluster sdt-aps01-forward sdt-aps01-structure sdt-aps01-emissions
        sdt-aps01-void-geometry)
    foreach(tgt ${CQ12_TARGETS})
        target_compile_options(${tgt} PRIVATE /W3)
    endforeach()
endif()

# ═══ EMC01 Transfer Function Derivation ═══
set(CQ01_DIR ${CMAKE_CURRENT_SOURCE_DIR}/03_Electromagnetism_and_Charge/CQ01_Transfer_Function_Derivation)

add_executable(sdt-emc01-transfer ${CQ01_DIR}/cq01_transfer_function.cpp)
target_link_libraries(sdt-emc01-transfer PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-emc01-transfer PRIVATE /W3)
endif()

# ═══ PPT01 Vortex Equilibrium Quantisation ═══
set(CQ02_DIR ${CMAKE_CURRENT_SOURCE_DIR}/02_Particle_Physics_and_Topology/CQ02_Vortex_Equilibrium_Quantisation)

add_executable(sdt-ppt01-vortex ${CQ02_DIR}/cq02_vortex_equilibrium.cpp)
target_link_libraries(sdt-ppt01-vortex PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-ppt01-vortex PRIVATE /W3)
endif()

# ═══ PPT02 Fine Structure from Topology ═══
set(CQ03_DIR ${CMAKE_CURRENT_SOURCE_DIR}/02_Particle_Physics_and_Topology/CQ03_Fine_Structure_from_Topology)

add_executable(sdt-ppt02-fine-structure ${CQ03_DIR}/cq03_fine_structure.cpp)
target_link_libraries(sdt-ppt02-fine-structure PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-ppt02-fine-structure PRIVATE /W3)
endif()

# ═══ FLM01 State28D Force Ratio Constants (superseded by EMC01+GOM02) ═══
set(CQ04_DIR ${CMAKE_CURRENT_SOURCE_DIR}/01_Foundations_and_Lattice_Mechanics/CQ04_State28D_Force_Ratio_Constants)

add_executable(sdt-flm01-force-ratios ${CQ04_DIR}/cq04_force_ratio_constants.cpp)
target_link_libraries(sdt-flm01-force-ratios PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-flm01-force-ratios PRIVATE /W3)
endif()

# ═══ PPT03 Proton-Electron Mass Ratio (early derivation) ═══
set(CQ05_DIR ${CMAKE_CURRENT_SOURCE_DIR}/02_Particle_Physics_and_Topology/CQ05_Proton_Electron_Mass_Ratio)

add_executable(sdt-ppt03-mass-ratio ${CQ05_DIR}/cq05_mass_ratio.cpp)
target_link_libraries(sdt-ppt03-mass-ratio PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-ppt03-mass-ratio PRIVATE /W3)
endif()

# ═══ GD01 Eclipse Saturation Model ═══
set(CQ06_DIR ${CMAKE_CURRENT_SOURCE_DIR}/08_Galactic_Dynamics/CQ06_Eclipse_Saturation_Model)

add_executable(sdt-gd01-eclipse ${CQ06_DIR}/cq06_eclipse_saturation.cpp)
target_link_libraries(sdt-gd01-eclipse PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-gd01-eclipse PRIVATE /W3)
endif()

# ═══ GD02 Milky Way Occlusion Map ═══
set(CQ19_DIR ${CMAKE_CURRENT_SOURCE_DIR}/08_Galactic_Dynamics/CQ19_Milky_Way_Occlusion_Map)

add_executable(sdt-gd02     ${CQ19_DIR}/cq19_mw_occlusion_map.cpp)
add_executable(sdt-cq19b    ${CQ19_DIR}/cq19b_galactic_nucleus_shells.cpp)
add_executable(sdt-cq19c    ${CQ19_DIR}/cq19c_binding_proof.cpp)
add_executable(sdt-cq19d    ${CQ19_DIR}/cq19d_baryon_count.cpp)
add_executable(sdt-cq19e    ${CQ19_DIR}/cq19e_spiral_arms.cpp)

foreach(t sdt-gd02 sdt-cq19b sdt-cq19c sdt-cq19d sdt-cq19e)
    target_link_libraries(${t} PRIVATE sdt-engine)
    if(MSVC)
        target_compile_options(${t} PRIVATE /W3)
    else()
        target_compile_options(${t} PRIVATE -O2)
    endif()
endforeach()

# ═══ FLM02 Granular Pulse Mechanics ═══
set(CQ08_DIR ${CMAKE_CURRENT_SOURCE_DIR}/01_Foundations_and_Lattice_Mechanics/CQ08_Granular_Pulse_Mechanics)

add_executable(sdt-flm02-pulse-mechanics ${CQ08_DIR}/cq08_granular_pulse_mechanics.cpp)
target_link_libraries(sdt-flm02-pulse-mechanics PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-flm02-pulse-mechanics PRIVATE /W3)
endif()

# ═══ FLM03 Spation Rotation Investigation ═══
set(CQ09_DIR ${CMAKE_CURRENT_SOURCE_DIR}/01_Foundations_and_Lattice_Mechanics/CQ09_Spation_Rotation)

add_executable(sdt-flm03-spation-rotation ${CQ09_DIR}/cq09_spation_rotation_map.cpp)
target_link_libraries(sdt-flm03-spation-rotation PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-flm03-spation-rotation PRIVATE /W3)
endif()

# ═══ FLM05 Lattice Pulse Propagation ═══
set(CQ10_DIR ${CMAKE_CURRENT_SOURCE_DIR}/01_Foundations_and_Lattice_Mechanics/CQ10_Lattice_Pulse_Propagation)

add_executable(sdt-flm05-lattice-pulse ${CQ10_DIR}/cq10_lattice_pulse.cpp)
target_link_libraries(sdt-flm05-lattice-pulse PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-flm05-lattice-pulse PRIVATE /W3)
endif()

add_executable(sdt-cq10b-torus-mass ${CQ10_DIR}/cq10b_torus_derives_mass.cpp)
target_link_libraries(sdt-cq10b-torus-mass PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-cq10b-torus-mass PRIVATE /W3)
endif()

# ═══ PPT05 Trefoil Confinement ═══
set(CQ11_DIR ${CMAKE_CURRENT_SOURCE_DIR}/02_Particle_Physics_and_Topology/CQ11_Trefoil_Confinement)

add_executable(sdt-ppt05-trefoil-confinement ${CQ11_DIR}/cq11_trefoil_confinement.cpp)
target_link_libraries(sdt-ppt05-trefoil-confinement PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-ppt05-trefoil-confinement PRIVATE /W3)
endif()

# ═══ APS02 Emission Prediction Engine ═══
set(CQ13_DIR ${CMAKE_CURRENT_SOURCE_DIR}/04_Atomic_Physics_and_Spectroscopy/CQ13_Emission_Prediction)

add_executable(sdt-aps02-engine ${CQ13_DIR}/cq13_emission_engine.cpp)
target_link_libraries(sdt-aps02-engine PRIVATE sdt-engine)
target_include_directories(sdt-aps02-engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/04_Atomic_Physics_and_Spectroscopy/CQ12_Emissions)

if(MSVC)
    target_compile_options(sdt-aps02-engine PRIVATE /W3)
endif()

# ═══ GOM01 Spation Depth Engine ═══
set(CQ15_DIR ${CMAKE_CURRENT_SOURCE_DIR}/06_Gravitation_and_Orbital_Mechanics/CQ15_Spation_Depth_Engine)

add_executable(sdt-gom01-depth-engine ${CQ15_DIR}/cq15_spation_depth_engine.cpp)
target_link_libraries(sdt-gom01-depth-engine PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-gom01-depth-engine PRIVATE /W3)
endif()

# ═══ GOM02 k-Hierarchy Advantage ═══
set(CQ16_DIR ${CMAKE_CURRENT_SOURCE_DIR}/06_Gravitation_and_Orbital_Mechanics/CQ16_k_Hierarchy_Advantage)

add_executable(sdt-gom02-k-hierarchy ${CQ16_DIR}/cq16_k_hierarchy.cpp)
target_link_libraries(sdt-gom02-k-hierarchy PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-gom02-k-hierarchy PRIVATE /W3)
endif()

# ═══ PPT07 Proton-Electron Mass Ratio ═══
set(CQ17_DIR ${CMAKE_CURRENT_SOURCE_DIR}/02_Particle_Physics_and_Topology/CQ17_Proton_Electron_Mass_Ratio)

add_executable(sdt-ppt07-mass-ratio ${CQ17_DIR}/cq17_mass_ratio_solver.cpp)
target_link_libraries(sdt-ppt07-mass-ratio PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-ppt07-mass-ratio PRIVATE /W3)
endif()

add_executable(sdt-ppt07-28d ${CQ17_DIR}/cq17_28d_formal.cpp)
target_link_libraries(sdt-ppt07-28d PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-ppt07-28d PRIVATE /W3)
endif()

# ---- CR01: Gravitational Redshift Decomposition ----
set(CQ18_DIR ${CMAKE_CURRENT_SOURCE_DIR}/07_Cosmology_and_Redshift/CQ18_Redshift_Decomposition)

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

# ═══ GD05 Galaxy Rotation Curves (Eclipse Saturation) ═══
set(E46_DIR ${CMAKE_CURRENT_SOURCE_DIR}/08_Galactic_Dynamics/E46_Galaxy_Rotation_Curves)
add_executable(sdt-e46 ${E46_DIR}/gd05_sparc_rotation_curves.cpp)
target_link_libraries(sdt-e46 PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-e46 PRIVATE /W3)
else()
    target_compile_options(sdt-e46 PRIVATE -O2)
endif()

# ═══ GOM03 3D Volumetric Integration ═══
set(CQ23_DIR ${CMAKE_CURRENT_SOURCE_DIR}/08_Galactic_Dynamics/CQ23_3D_Volumetric_Integration)
add_executable(sdt-gom03 ${CQ23_DIR}/cq23_3d_volumetric_integration.cpp)
target_link_libraries(sdt-gom03 PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-gom03 PRIVATE /W3)
else()
    target_compile_options(sdt-gom03 PRIVATE -O2)
endif()

# ═══ GD03 Galactic Spation Topology ═══
set(CQ20_DIR ${CMAKE_CURRENT_SOURCE_DIR}/08_Galactic_Dynamics/CQ20_Galactic_Spation_Topology)

add_executable(sdt-gd03 ${CQ20_DIR}/cq20_spation_topology.cpp)
add_executable(sdt-cq20b ${CQ20_DIR}/cq20b_torus_spation_count.cpp)
add_executable(sdt-cq20c ${CQ20_DIR}/cq20c_torus_differential.cpp)
add_executable(sdt-cq20d ${CQ20_DIR}/cq20d_galactic_occlusion.cpp)
add_executable(sdt-cq20e ${CQ20_DIR}/cq20e_bulge_from_sagA.cpp)
add_executable(sdt-cq20f ${CQ20_DIR}/cq20f_trefoil_convection.cpp)
target_link_libraries(sdt-gd03 PRIVATE sdt-engine)
target_link_libraries(sdt-cq20b PRIVATE sdt-engine)
target_link_libraries(sdt-cq20c PRIVATE sdt-engine)
target_link_libraries(sdt-cq20d PRIVATE sdt-engine)
target_link_libraries(sdt-cq20e PRIVATE sdt-engine)
target_link_libraries(sdt-cq20f PRIVATE sdt-engine)

if(MSVC)
    target_compile_options(sdt-gd03 PRIVATE /W3)
    target_compile_options(sdt-cq20b PRIVATE /W3)
    target_compile_options(sdt-cq20c PRIVATE /W3)
    target_compile_options(sdt-cq20d PRIVATE /W3)
    target_compile_options(sdt-cq20e PRIVATE /W3)
    target_compile_options(sdt-cq20f PRIVATE /W3)
else()
    target_compile_options(sdt-gd03 PRIVATE -O2)
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
set(GALCALC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/08_Galactic_Dynamics/GalacticCalculator)
add_executable(sdt-galaxy-calc ${GALCALC_DIR}/sdt_galaxy_calc.cpp)
target_link_libraries(sdt-galaxy-calc PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-galaxy-calc PRIVATE /W3)
else()
    target_compile_options(sdt-galaxy-calc PRIVATE -O2)
endif()

# ═══ NP01 Atomicus Nuclear Grammar ═══════════════════════════════════════════
# Exact integer coordinate transform (Z,A) → (n_d,n_t) on the nuclear chart.
# 287-nuclide natural basis, compile-time verified by static_assert ×7.
# Three-stage investigation: grammar table → fission snap → ASCII nuclide map.
set(CQ25_DIR ${CMAKE_CURRENT_SOURCE_DIR}/05_Nuclear_Physics/CQ25_Atomicus_Nuclear_Grammar)
add_executable(sdt-np01 ${CQ25_DIR}/cq25_atomicus_grammar.cpp)
target_link_libraries(sdt-np01 PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-np01 PRIVATE /W4)
else()
    target_compile_options(sdt-np01 PRIVATE -O2 -Wall)
endif()

# ═══ NP02 Stellar Fusion and Nuclear Growth ══════════════════════════════════
# Evaluates deu/tri fusion, solid-angle occlusion integrals, trefoil rotational
# spin gearing, temperature-dependent EC, and electronic shell mirror maps.
set(CQ27_DIR ${CMAKE_CURRENT_SOURCE_DIR}/05_Nuclear_Physics/CQ27_Stellar_Fusion_and_Nuclear_Growth)
add_executable(sdt-np02 ${CQ27_DIR}/cq27_stellar_fusion_growth.cpp)
target_link_libraries(sdt-np02 PRIVATE sdt-engine)
if(MSVC)
    target_compile_options(sdt-np02 PRIVATE /W4)
else()
    target_compile_options(sdt-np02 PRIVATE -O2 -Wall)
endif()
