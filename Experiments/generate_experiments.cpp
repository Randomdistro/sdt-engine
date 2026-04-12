// ================================================================
// generate_experiments.cpp — Generate 100 SDT experiments
//
// Produces markdown files for experiments E21–E100 plus the
// three named experiments (Orbit Drop, Casimir Vibration,
// Cavendish Bell), and updates the README index.
//
// Each experiment: background, SDT prediction, standard prediction,
// observable, apparatus, feasibility, impact.
//
// Author: SDT Engine — James Christopher Tyndall
// ================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

struct Experiment {
    int number;
    std::string title;
    std::string filename;
    std::string sdt_prediction;
    std::string standard_prediction;
    std::string background;
    std::string observable;
    std::string apparatus;
    std::string feasibility;
    std::string difficulty;
    std::string impact_positive;
    std::string impact_negative;
    std::string category;
    std::string status;
};

std::vector<Experiment> build_experiments() {
    std::vector<Experiment> exps;

    // ─── ORBITAL MECHANICS & GRAVITY ───

    exps.push_back({21,
        "Orbital Velocity Drop Test — Frame Dragging via Solar Accretion",
        "E21_Orbit_Drop_Test",
        "Objects dropped from zero orbital velocity will curve their descent toward the Sun due to the solar convergence field's rotational gradient. The drops will strike the Sun further around (in the direction of Earth's orbit) than GR calculates. Even a minor shift of >10 km at the solar surface will demonstrate this. All bodies on the ecliptic are on the Sun's accretion disk in stable orbits — they do not fall straight.",
        "GR predicts frame dragging from the Sun's rotation is negligibly small (~milliarcseconds). A dropped object should fall radially inward with only Coriolis corrections from the initial orbital frame. No measurable lateral displacement beyond standard orbital mechanics.",
        "A spacecraft trails Earth in its orbit, then fires retrograde thrusters to reduce its heliocentric velocity to zero. Multiple test masses of different weights and compositions are released simultaneously. High-precision tracking monitors each mass as it falls sunward. SDT says the convergence field has a rotational component — the solar pressure gradient produces an accretion-like flow that curves all descents. This is why planets orbit in the ecliptic plane in the same direction. The \"frame dragging\" is not spacetime geometry but convergence flow geometry.",
        "Track each test mass via radar or laser ranging as it falls toward the Sun. Measure the lateral displacement (in the direction of Earth's orbital motion) from the GR-predicted radial trajectory. SDT predicts a systematic displacement >10 km at solar approach, scaling with the fall distance. Different masses should show IDENTICAL lateral displacement (mass-independent, because the convergence field is geometric).",
        "Spacecraft with retrograde thruster capability (Delta-V ~30 km/s to null orbital velocity at 1 AU). Multiple test masses (0.1 kg to 100 kg, different materials). Radar transponders or laser retroreflectors on each mass. Deep Space Network tracking. Mission duration ~60 days (free-fall from 1 AU to perihelion).",
        "**HIGH** — requires dedicated spacecraft mission. However, the physics is clean: zero orbital velocity from a known position, then passive tracking. No ambiguous measurements. The simplicity of the test is its strength.",
        "HIGH",
        "Demonstrates that the solar gravitational field has a rotational component not predicted by GR's negligible solar frame-dragging. Proves the accretion-disk model of planetary orbits. Extraordinary result.",
        "If no lateral displacement: the convergence field is radially symmetric at 1 AU, and the ecliptic orbital pattern requires a different explanation within SDT.",
        "Orbital Mechanics",
        "Proposed (space mission)"});

    exps.push_back({22,
        "Casimir Vacuum Sound Transmission",
        "E22_Casimir_Vacuum_Sound",
        "Sound will transmit through a hard vacuum via Casimir plate harmonics. Two closely-spaced Casimir plates in vacuum, one driven by a piezo actuator, will transmit vibrations to the second plate through the spation lattice pressure field. The vacuum is not empty — it is a pressurised medium, and pressure waves propagate.",
        "Standard physics predicts absolute zero sound transmission in a vacuum. Sound requires a material medium. The Casimir effect is explained by quantum vacuum fluctuations, which do not carry coherent mechanical vibrations.",
        "The Casimir effect demonstrates that the vacuum between closely-spaced plates is not empty — there is a measurable force between the plates. SDT interprets this force as convergent boundary pressure occlusion: the plates occlude spation relay content from each other, producing a net inward pressure. If the medium carrying this pressure is a real mechanical entity (the spation lattice), then coherent vibrations impressed on it should propagate. A vibrating Casimir plate should push the pressure field, which should push the neighbouring plate.",
        "Drive one Casimir plate with a piezoelectric actuator at frequencies from 1 kHz to 10 MHz. Detect vibrations on the second plate using a laser interferometer or a second piezo sensor. The plates are separated by 0.1–10 μm in a vacuum better than 10⁻⁹ mbar. Any detected signal at the drive frequency, above thermal noise, constitutes sound transmission through vacuum.",
        "Two gold-coated silicon plates (10 mm × 10 mm, optical-flat). Piezoelectric actuator (PZT-5H, resonant frequencies 1 kHz–10 MHz). Laser interferometer (sub-pm sensitivity, e.g. Zygo). Ultra-high vacuum chamber (10⁻⁹ mbar). Vibration isolation table. Faraday cage (to exclude electromagnetic crosstalk). Temperature control (4 K preferred, to reduce thermal noise).",
        "**MODERATE** — all components exist as standard lab equipment. The main challenges are: (1) excluding electromagnetic crosstalk between drive and sensor, (2) achieving sufficient sensitivity above thermal noise, (3) proving the signal propagates through the gap rather than through the mounting structure. Control experiment: separate the plates to >1 mm (Casimir force negligible) and verify signal disappearance.",
        "MODERATE",
        "Sound transmission through vacuum at Casimir-scale gaps would prove the vacuum is a mechanical medium capable of carrying pressure waves. This directly demonstrates the spation lattice. Revolutionary.",
        "If no signal: the Casimir pressure field does not carry coherent vibrations at accessible frequencies. The spation lattice may have a bandwidth or impedance that prevents mechanical coupling at these scales.",
        "Vacuum / Medium",
        "Proposed (laboratory)"});

    exps.push_back({23,
        "Cavendish Bell — Gravitational Shielding by Dense Shell",
        "E23_Cavendish_Bell",
        "A sphere dropped from the centre of a very large, very dense, hollow spherical shell (40 m radius, multi-layered with tungsten/osmium/lead) will experience REDUCED gravitational acceleration — less than 9.81 m/s². The dense shell occludes convergent boundary pressure from above, reducing the net downward force on the inner mass.",
        "GR and Newtonian gravity predict that a uniform spherical shell exerts ZERO gravitational force on any mass inside it (Newton's shell theorem). The dropped sphere should accelerate at exactly 9.81 m/s² regardless of the shell's mass or density. The shell's gravity cancels perfectly by symmetry.",
        "Newton's shell theorem states that a uniform spherical shell produces zero gravitational field inside itself. This is a direct consequence of the inverse-square law and spherical symmetry. SDT disagrees: the mechanism of gravity is convergent boundary pressure (CMB occlusion). A dense shell occludes a fraction of the incoming convergent pressure from all sky directions. While the shell's own occlusion is symmetric (producing zero NET shell-gravity), the shell ALSO blocks external convergent pressure that would otherwise reach the interior. The result is a slight reduction in the apparent gravitational acceleration inside the shell. This is not \"gravitational shielding\" in the Le Sage sense — it is a measurable reduction in the convergent pressure budget available to the interior.",
        "Construct a 40 m radius hollow sphere of alternating dense layers (tungsten, lead, osmium — total shell mass ~10⁶ tonnes). Drop a test mass from the exact centre down a vertical vacuum shaft. Measure the acceleration with sub-μg precision using laser interferometry. Compare to 9.81 m/s². SDT predicts a measurable deficit proportional to the shell's total occlusion fraction: Δg/g ≈ Ω_shell/4π, where Ω_shell is the solid angle subtended by the shell's cross-section.",
        "40 m radius spherical shell structure (civil engineering project). Dense metal layers: tungsten carbide tiles, lead sheets, osmium powder in containment. Vertical vacuum shaft (0.5 m diameter, 80 m long, through the centre). Laser drop-tower interferometer (sensitivity < 10⁻⁸ g). Seismic isolation. Environmental monitoring (temperature, tidal, atmospheric pressure corrections). Multiple drop runs for statistics.",
        "**EXTREME** — this is a megastructure. A 40 m radius tungsten/lead shell is a massive civil engineering project (~$100M+). However, the physics measurement itself is clean: drop a ball, measure g. The measurement technology (atom interferometry, laser ranging) already achieves the required precision. A smaller-scale prototype (5 m radius, single-layer lead) could test for the effect first, with reduced sensitivity.",
        "EXTREME",
        "If g < 9.81 m/s² inside the shell: Newton's shell theorem is violated. Gravity is not a pure geometric property of spacetime but involves a medium that can be partially occluded. This would be one of the most significant experimental results in physics history.",
        "If g = 9.81 m/s² to measurement precision: the occlusion fraction of the shell is below detection threshold. SDT may require the shell to be much denser or much larger, or the effect may be too small for terrestrial measurement.",
        "Gravity / Occlusion",
        "Proposed (megastructure)"});

    // ─── PLANETARY / SOLAR ───

    exps.push_back({24, "Mercury Perihelion Precession from k-Hierarchy",
        "E24_Mercury_Precession",
        "Mercury's perihelion precession of 43\"/century arises from the Sun's k²-gradient, not spacetime curvature.",
        "GR explains 43\"/century from spacetime curvature near a massive body.",
        "Mercury orbits deep in the Sun's convergence gradient. The k-factor changes measurably across Mercury's eccentric orbit. This gradient produces an orbital precession identical in magnitude to GR's prediction, because both are derived from the same velocity-field profile — but SDT attributes it to the pressure gradient rather than curved spacetime.",
        "Compare SDT k-gradient precession calculation to the measured value. This is a paper calculation, not a new measurement.",
        "Computational. Use laws.hpp bridge::v_orbital with solar k = 686.3 and Mercury's orbital parameters.",
        "**TRIVIAL** — pure calculation using existing data.", "TRIVIAL",
        "Shows SDT reproduces the 43\"/century value from pressure gradients.",
        "If the calculation gives a different value: the k-gradient model needs refinement.",
        "Orbital Mechanics", "Calculable now"});

    exps.push_back({25, "Pioneer Anomaly from Pressure Domain Boundary",
        "E25_Pioneer_Anomaly",
        "The Pioneer anomalous deceleration (~8.7 × 10⁻¹⁰ m/s²) arises from the spacecraft crossing pressure domain boundaries in the outer solar system.",
        "Thermal recoil from asymmetric spacecraft emission (resolved in 2012).",
        "The Pioneer anomaly was measured as a sunward acceleration of ~8.7 × 10⁻¹⁰ m/s². SDT's pressure domain model predicts that objects crossing convergence boundaries between the Sun and the CMB floor experience additional drag-like effects. Since the anomaly has been attributed to thermal recoil, this experiment would need to use a purpose-built, thermally symmetric spacecraft.",
        "Launch a thermally symmetric probe into the outer solar system with sub-nm/s² accelerometry. Measure residual acceleration after all thermal effects are accounted for.",
        "Thermally symmetric spacecraft. High-precision accelerometer (LISA Pathfinder heritage). Solar sail or ion drive for trajectory control.",
        "**HIGH** — requires dedicated deep-space mission.", "HIGH",
        "Residual anomalous acceleration would revive the Pioneer problem under SDT.",
        "If no residual: pressure domain boundaries do not produce measurable drag at spacecraft scales.",
        "Orbital Mechanics", "Proposed (space mission)"});

    exps.push_back({26, "Lunar Laser Ranging — k-Gradient Test",
        "E26_Lunar_Laser_Ranging",
        "Lunar orbit shows residual effects from Earth's k²-gradient that differ from GR geodesic precession at sub-mm level.",
        "GR predicts geodesic precession of the lunar orbit at 19.2 mas/year.",
        "The Moon orbits within Earth's convergence gradient. SDT's k-gradient produces orbital dynamics that should match GR to high precision but may show systematic residuals at the sub-mm level in the ranging data.",
        "Analyse existing Apache Point Observatory Lunar Laser Ranging data for systematic residuals vs GR-predicted orbit. Look for Earth-Moon distance anomalies correlated with solar pressure direction.",
        "Existing data from APOLLO facility (Apache Point, NM). Computational analysis.",
        "**LOW** — data already exists.", "LOW",
        "Sub-mm residuals correlated with solar direction would indicate pressure-field effects.",
        "If no residuals: Earth's k-gradient matches GR at sub-mm precision.",
        "Orbital Mechanics", "Archival analysis"});

    exps.push_back({27, "Solar Oblateness from Convergence Gradient",
        "E27_Solar_Oblateness",
        "The Sun's oblateness (J₂ = 2.2 × 10⁻⁷) arises from the convergence field's equatorial enhancement, not just rotation.",
        "Standard: solar J₂ from rotational flattening alone.",
        "SDT predicts the convergence field is enhanced at the Sun's equator due to the ecliptic plane geometry. This enhancement contributes to the measured oblateness beyond what rotation alone produces.",
        "Compare measured J₂ from helioseismology to rotational predictions. Excess oblateness could indicate convergence contribution.",
        "Helioseismology data (SDO, SOHO). Computational modeling.",
        "**LOW** — archival/computational.", "LOW",
        "Excess oblateness beyond rotation confirms convergence geometry.",
        "If J₂ matches rotation: no convergence enhancement detectable.",
        "Solar Physics", "Archival analysis"});

    // ─── NUCLEAR PHYSICS ───

    exps.push_back({28, "Triple-Alpha Rate from Geometric Packing",
        "E28_Triple_Alpha_Rate",
        "The Hoyle state in C-12 is NOT a three-alpha resonance but a single alpha + 4 deuteron geometric closure. The reaction rate should be calculable from the packing geometry alone.",
        "Standard: the Hoyle state is a 3α resonance at 7.654 MeV above C-12 ground state, crucial for stellar nucleosynthesis.",
        "SDT's nuclear grammar decomposes C-12 as α + 4d (one alpha core plus 4 deuterons), not as three alphas. The so-called \"triple alpha process\" is actually sequential deuteron addition. The 7.654 MeV Hoyle state is the threshold for geometric closure of the tetrahedral deuteron shell.",
        "Calculate the Hoyle state energy from the geometric packing energy of 4 deuterons around an alpha core. Compare to measured 7.654 MeV.",
        "Computational. Nuclear binding data from NUBASE2020.",
        "**TRIVIAL** — pure calculation.", "TRIVIAL",
        "If the geometric calculation reproduces 7.654 MeV: validates the α+4d model over the 3α model.",
        "If the energy differs: the packing geometry needs refinement.",
        "Nuclear Physics", "Calculable now"});

    exps.push_back({29, "Deuteron Binding from Occlusion Geometry",
        "E29_Deuteron_Binding",
        "The deuteron binding energy (2.224 MeV) is derivable from the occlusion geometry of one proton and one neutron at the measured separation of 2.14 fm.",
        "Standard: deuteron binding from nuclear potential models (Yukawa, AV18, etc.).",
        "The deuteron is the simplest nuclear system: one proton + one neutron. SDT's occlusion force F = (π/4) P_eff R₁² R₂² / r² should predict the binding energy from the measured charge radii and separation.",
        "Calculate occlusion binding energy from R_p = 0.841 fm, R_n ≈ equivalent, separation = 2.14 fm. Compare to measured 2.224 MeV.",
        "Computational. Use law_III::F_occlusion from laws.hpp.",
        "**TRIVIAL** — pure calculation.", "TRIVIAL",
        "Reproducing 2.224 MeV from occlusion geometry would ground the nuclear force in convergent pressure.",
        "If the energy differs significantly: occlusion geometry alone may not capture the full nuclear interaction.",
        "Nuclear Physics", "Calculable now"});

    exps.push_back({30, "Alpha Binding from Tetrahedral Occlusion",
        "E30_Alpha_Binding",
        "The alpha particle binding energy (28.296 MeV) should emerge from the tetrahedral packing geometry of 2p+2n.",
        "Standard: alpha binding from shell model or cluster model calculations.",
        "The alpha particle is 2 protons + 2 neutrons in a tetrahedral arrangement. The total binding (28.296 MeV, or 7.074 MeV/nucleon highest of any A≤4 nucleus) should be calculable from the occlusion geometry of four nucleons at their measured positions.",
        "Tetrahedral occlusion calculation using nuclear radii and the convergent pressure law.",
        "Computational.",
        "**TRIVIAL** — calculation.", "TRIVIAL",
        "Reproduces the peak light-nucleus stability from geometry alone.",
        "If the energy disagrees: tetrahedral assumption may need adjustment.",
        "Nuclear Physics", "Calculable now"});

    // Generate more experiments programmatically
    struct ExpTemplate {
        std::string title, sdt_pred, std_pred, bg, obs, app, feas, diff, imp_pos, imp_neg, cat, status;
    };

    std::vector<ExpTemplate> templates = {
        // E31-E40: Nuclear and atomic
        {"Neutron Lifetime from Lattice Topology",
         "The beam/bottle neutron lifetime discrepancy (~8 s) arises from different boundary conditions on the spation lattice.", "Standard: a dark decay channel or systematic error.", "The neutron lifetime measured in beam experiments (~888 s) differs from bottle experiments (~879 s).", "Compare both measurements with SDT boundary-condition corrections.", "Existing data.", "LOW — data reanalysis.", "LOW", "Resolves the lifetime puzzle.", "If no resolution: boundary conditions are not the source.", "Nuclear Physics", "Archival analysis"},
        {"Proton Radius Puzzle — W+1 Prediction",
         "R_p = 4ℏ/(m_p c) = 0.84124 fm, matching the muonic hydrogen measurement.", "Standard: electronic hydrogen gives ~0.877 fm, muonic gives ~0.841 fm.", "The proton radius puzzle: different measurements give different values.", "Already resolved — use muonic value as canonical.", "None — calculation.", "TRIVIAL — already validated.", "TRIVIAL", "SDT predicts the correct value with 0.02% precision.", "Already confirmed.", "Atomic Physics", "Validated"},
        {"Nuclear Charge Radius Scaling → Z × R_p",
         "Nuclear charge radii scale as R = Z × R_p for all elements.", "Standard: R = r₀ × A^(1/3), where r₀ ≈ 1.2 fm.", "SDT predicts charge radii scale linearly with Z, not with A^(1/3).", "Plot R_measured vs Z×R_p and vs r₀×A^(1/3) for all measured nuclei. Determine which fits better.", "NIST nuclear charge radius database.", "LOW — archival compilation.", "LOW", "If Z-scaling fits better: invalidates the A^(1/3) model.", "If A^(1/3) fits better: SDT's linear scaling is approximate.", "Nuclear Physics", "Archival analysis"},
        {"Quadrupole Moment of Li-7 from α+t Geometry",
         "Li-7's large quadrupole moment (-4.01 fm²) arises from the asymmetric alpha+triton arrangement.", "Standard: shell model explains it from p₃/₂ shell deformation.", "Li-7 = α + t (alpha + triton). The triton cap creates a prolate shape.", "Calculate quadrupole moment from the geometric α+t separation.", "Computational.", "TRIVIAL — calculation.", "TRIVIAL", "Geometric calculation reproducing Q = -4.01 fm² validates α+t model.", "If Q differs: geometric model needs refinement.", "Nuclear Physics", "Calculable now"},
        {"Fe-56 vs Ni-62: True Binding Energy Peak",
         "Ni-62 has the highest measured B/A (8.795 MeV/n), but Fe-56 is more abundant because its construction grammar is geometrically optimal.", "Standard: Fe-56 is more abundant due to stellar nucleosynthesis details.", "Fe-56 (8.790) and Ni-62 (8.795) are nearly identical in B/A. SDT explains the difference via triton fraction: Ni-62 has 23.1% tritons vs Fe-56's 16.7%.", "Computational comparison of grammar efficiency.", "Nuclear data.", "TRIVIAL — calculation.", "TRIVIAL", "Shows grammar efficiency predicts abundance ratio.", "If grammar efficiency doesn't correlate: mechanism is more complex.", "Nuclear Physics", "Calculable now"},
        {"Oxygen-16 Pure Deuteron Scaffold Verification",
         "O-16 = α + 6d (pure deuteron scaffold, 0% tritons). This predicts maximum stability per nucleon for its shell.", "Standard: O-16 is doubly magic (8p, 8n) in shell model.", "O-16 decomposes as alpha + 6 deuterons with zero tritons. Pure deuteron scaffolds should have maximum geometric symmetry.", "Compare O-16's binding per nucleon to neighboring isotopes. Verify pure-deuteron isotopes have enhanced stability.", "Nuclear binding energy data.", "TRIVIAL — archival.", "TRIVIAL", "Confirms pure deuteron scaffolds are the most stable constructions at each Z.", "If not: stability is not purely geometric.", "Nuclear Physics", "Archival analysis"},
        {"Double EC in Xe-124 from He-3 Core Grammar",
         "Xe-124 undergoes double EC because it has an He-3 core that requires TWO sequential captures to repair.", "Standard: double EC is a second-order weak process.", "Xe-124 (t½ = 1.8 × 10²² y) undergoes the rarest measured decay. SDT predicts this is two sequential He-3 core repairs.", "Verify grammar of Xe-124 under He-3 core: check n_deu ≥ 4 (need 2 donor+absorber pairs).", "Computational.", "TRIVIAL — grammar check.", "TRIVIAL", "Grammar predicts double EC viability.", "If grammar fails: may be a different mechanism.", "Nuclear Physics", "Calculable now"},
        {"EC Rate vs Charge State for Heavy Elements",
         "EC rate drops to zero at full ionisation for ALL elements, not just Be-7.", "Standard: EC requires bound electrons; rate varies with electron density at nucleus.", "SDT's He-3 core mechanism predicts charge-state dependence is universal. Cr-51, Mn-54, Fe-55 should all show rate cessation at full ionisation.", "Measure EC rates of Cr-51, Mn-54, Fe-55 at various charge states in EBIT or storage ring.", "GSI/FAIR storage ring, NIST EBIT.", "HIGH — frontier capability.", "HIGH", "Universal charge-state EC cessation validates the He-3 core mechanism.", "If some elements show EC at full ionisation: mechanism is more complex.", "Nuclear Physics", "Proposed (GSI/FAIR)"},
        {"Proton-Neutron Mass Difference from Topology",
         "m_n - m_p = 1.293 MeV arises from the extra neutron internal energy (one additional trefoil circulation).", "Standard: m_n - m_p from quark mass difference (m_d - m_u + EM corrections).", "The neutron is 1.293 MeV heavier than the proton. SDT attributes this to a topological difference in the trefoil knot circulation.", "Calculate the energy cost of the additional circulation mode.", "Computational.", "TRIVIAL — calculation.", "TRIVIAL", "Reproducing 1.293 MeV from topology would be extraordinary.", "If the number doesn't come out: topology alone doesn't set the mass difference.", "Nuclear Physics", "Calculable now"},
        {"Nuclear Magnetic Moments from Vortex Geometry",
         "Nuclear magnetic moments (μ_p = 2.793 μN, μ_n = -1.913 μN) arise from the trefoil vortex geometry.", "Standard: magnetic moments from quark constituent models.", "SDT's trefoil model (W=3 proton, W=1 electron) should predict magnetic moments from the vortex current distribution.", "Calculate μ_p and μ_n from the trefoil and torus current distributions.", "Computational.", "MODERATE — requires vortex current integration.", "MODERATE", "Reproducing both moments from geometry would validate the vortex model.", "If the moments don't match: vortex model needs refinement.", "Nuclear Physics", "Calculable now"},

        // E41-E50: Cosmological
        {"CMB Temperature from Spation Lattice Properties",
         "T_CMB = 2.7255 K is derivable from spation lattice properties, not a free parameter.", "Standard: T_CMB is a relic of the hot Big Bang, a free parameter.", "SDT's lattice model should fix T_CMB from the closure condition and lattice spacing.", "Derive T_CMB from first principles using zk²=1 and the relay density.", "Computational.", "MODERATE — derivation.", "MODERATE", "Deriving T_CMB would eliminate another free parameter.", "If T_CMB comes out wrong: lattice parameters need adjustment.", "Cosmology", "Calculable now"},
        {"Hubble Constant from Pressure Gradient",
         "H₀ = v/d is a pressure gradient measure, not an expansion rate. SDT predicts H₀(near) > H₀(far).", "Standard: H₀ is the expansion rate of the universe, should be constant at all distances.", "The Hubble tension (73 vs 67 km/s/Mpc) is a real physical difference, not systematic error.", "Calculate H₀ from the SDT pressure gradient at different distances.", "Existing SN Ia data (Pantheon+ catalog).", "LOW — data reanalysis.", "LOW", "Resolves the Hubble tension as a geometric effect.", "If the gradient doesn't match: pressure model needs refinement.", "Cosmology", "Archival analysis"},
        {"SN Ia Mass Step from Occlusion Gradient",
         "The ~0.04 mag mass step in SN Ia standardisation arises from host-galaxy convergence field differences.", "Standard: dust, metallicity, or progenitor differences.", "High-mass galaxies have higher local convergence (denser environments). This produces a systematic brightness offset in hosted supernovae.", "Correlate mass-step residuals with galaxy density measures.", "Pantheon+ catalog, host galaxy data.", "LOW — archival.", "LOW", "SDT explanation of the mass step would be a major cosmological result.", "If correlations don't hold: mass step has other origins.", "Cosmology", "Archival analysis"},
        {"CMB Dipole from Observer Motion in Pressure Field",
         "The CMB dipole (370 km/s) reflects our motion through the pressure field, not relative to a \"rest frame\" of expansion.", "Standard: CMB dipole from Earth's peculiar velocity relative to the CMB rest frame.", "SDT and standard physics agree on the kinematic interpretation but differ on ontology: SDT says we're moving through a real medium.", "Measure higher-order CMB motion effects (e.g., aberration quadrupole) that distinguish medium-motion from frame-motion.", "Planck CMB data.", "LOW — archival.", "LOW", "Higher-order effects could distinguish medium from frame.", "If indistinguishable: both interpretations are observationally equivalent at current precision.", "Cosmology", "Archival analysis"},
        {"BAO as Lattice Standing Waves",
         "Baryon acoustic oscillations are standing waves in the spation lattice pressure field, not sound waves in primordial plasma.", "Standard: BAO from acoustic oscillations in the baryon-photon plasma before recombination.", "SDT predicts BAO features from the lattice resonance structure rather than primordial sound.", "Compare SDT lattice resonance predictions to DESI BAO measurements.", "DESI survey data.", "MODERATE — calculation + data comparison.", "MODERATE", "Novel BAO explanation from lattice structure.", "If standard BAO model fits better: lattice resonances don't dominate.", "Cosmology", "Archival analysis"},
        {"Galaxy Rotation Curves from Eclipse Saturation",
         "Flat rotation curves arise from eclipse saturation — beyond a critical radius, all convergence lines are already occluded.", "Standard: dark matter halos.", "SDT's galactic.hpp predicts flat rotation curves from geometric saturation of the convergence field by the visible disk.", "Compare SDT rotation curve predictions to measured curves for 50+ galaxies.", "SPARC database of rotation curves.", "LOW — calculation + data comparison.", "LOW", "Explaining rotation curves without dark matter would be transformative.", "If SDT curves don't match: eclipse saturation model needs refinement.", "Cosmology", "Archival analysis"},
        {"Gravitational Lensing from Convergence Gradient",
         "Light bending near massive objects arises from the convergence-field gradient (refractive index of the spation lattice), not spacetime curvature.", "Standard: GR predicts light bending from spacetime curvature.", "SDT treats the spation lattice as a medium with a spatially varying refractive index. The convergence gradient near a massive body changes the lattice density, which changes the local speed of light.", "Calculate lensing angle from the k-gradient profile of a galaxy cluster. Compare to observed strong lensing.", "HST strong lensing data.", "MODERATE — calculation + data comparison.", "MODERATE", "Reproducing lensing without spacetime curvature validates the medium model.", "If angles don't match: medium model needs calibration.", "Cosmology", "Archival analysis"},
        {"Gravitational Wave Speed = c from Lattice Rigidity",
         "Gravitational waves propagate at c because they are transverse lattice distortions. GW170817 confirmed GW speed = c to 10⁻¹⁵.", "Standard: GR predicts GW speed = c from the massless spin-2 graviton.", "SDT and GR agree: GW speed = c. SDT explains this as the transverse wave speed of the spation lattice, which is the same as the electromagnetic wave speed because both propagate through the same medium.", "Already confirmed by GW170817/GRB 170817A timing.", "LIGO/Virgo/KAGRA data.", "TRIVIAL — already measured.", "TRIVIAL", "Already validated. SDT correctly predicted c.", "N/A — confirmed.", "Cosmology", "Validated"},
        {"Dark Energy as Residual Pressure Gradient",
         "The accelerating expansion is a misinterpretation of the pressure gradient at cosmological distances. SDT predicts a distance-dependent effective H₀ that mimics acceleration.", "Standard: dark energy (Λ) drives accelerating expansion.", "SDT predicts no acceleration. The apparent acceleration is a measurement artifact from interpreting pressure-gradient redshift as Doppler.", "Fit SDT pressure-gradient model to the Pantheon+ SN Ia Hubble diagram. Compare χ² with and without Λ.", "Pantheon+ catalog.", "LOW — calculation.", "LOW", "Fitting SN Ia data without dark energy would eliminate the cosmological constant problem.", "If ΛCDM fits significantly better: pressure gradient alone doesn't explain the data.", "Cosmology", "Archival analysis"},
        {"Cosmic Neutrino Background Temperature",
         "SDT predicts T_ν ≠ 1.95 K because neutrinos decouple at a different point in the lattice pressure history.", "Standard: T_ν = (4/11)^(1/3) × T_CMB ≈ 1.95 K from entropy conservation.", "Neutrinos decoupled earlier than photons. SDT's lattice model may predict a different decoupling temperature.", "Measure T_CνB when PTOLEMY or successor detector becomes available.", "PTOLEMY tritium detector.", "HIGH — frontier detector.", "HIGH", "Incorrect T_ν would distinguish lattice from expansion cosmology.", "If T_ν = 1.95 K: consistent with standard decoupling.", "Cosmology", "Awaiting detector"},

        // E51-E60: Electromagnetic and field
        {"Fine Structure Constant from Lattice Geometry",
         "α = 1/137.036 is derivable from the ratio of vortex poloidal to toroidal velocities for the W=1 (electron) topology.", "Standard: α is a fundamental constant with no known derivation.", "If α can be derived from lattice topology, it is no longer a free parameter.", "Calculate α from the W=1 torus mode partition.", "Computational.", "HIGH — requires solving the lattice eigenmode problem.", "HIGH", "Deriving α from topology would be one of the greatest achievements in physics.", "If α comes out wrong: torus partition doesn't set α.", "Electromagnetic", "Open problem"},
        {"Proton-Electron Mass Ratio from Winding Numbers",
         "m_p/m_e = 1836.15 should emerge from the W=3 vs W=1 vortex energy ratio.", "Standard: m_p/m_e from quark masses, which are themselves unexplained.", "SDT predicts the mass ratio from the topology: a trefoil (W=3) has more circulation energy than a torus (W=1).", "Calculate the energy ratio between W=3 and W=1 lattice vortices.", "Computational.", "HIGH — requires lattice vortex calculation.", "HIGH", "Deriving m_p/m_e from W=3/W=1 would be historic.", "If the ratio doesn't match: vortex energy scaling is more complex.", "Electromagnetic", "Open problem"},
        {"Anomalous Magnetic Moment (g-2) from Lattice Corrections",
         "The electron g-2 anomaly (α/2π + ...) arises from lattice perturbation corrections to the vortex circulation.", "Standard: QED calculates g-2 from higher-order Feynman diagrams.", "SDT should reproduce the g-2 correction series from lattice perturbation theory applied to the torus vortex.", "Calculate first-order lattice correction to the electron magnetic moment.", "Computational.", "HIGH — requires lattice perturbation theory.", "HIGH", "Reproducing α/2π from lattice corrections would validate the medium model.", "If the correction differs: lattice perturbation theory needs development.", "Electromagnetic", "Open problem"},
        {"Lamb Shift from Lattice Fluctuations",
         "The Lamb shift in hydrogen arises from spation lattice fluctuations (\"vacuum fluctuations\" in QED are lattice thermal noise).", "Standard: Lamb shift from vacuum polarisation and electron self-energy in QED.", "SDT replaces virtual particle loops with real lattice fluctuations.", "Calculate the Lamb shift from the spation lattice fluctuation spectrum.", "Computational.", "HIGH — requires lattice fluctuation model.", "HIGH", "Reproducing Lamb shift from real lattice fluctuations would reinterpret QED.", "If shift differs: lattice fluctuation model needs refinement.", "Electromagnetic", "Open problem"},
        {"Photoelectric Effect from Pressure-Field Coupling",
         "Photon absorption at a metal surface is a pressure-field resonance event, not a particle collision.", "Standard: photon as particle ejects electron when E > work function.", "SDT treats photons as propagating lattice distortions. Absorption occurs when the distortion frequency matches a surface electron's circulation frequency.", "Measure photoelectric emission timing with sub-attosecond precision. SDT predicts instant emission (no tunnelling delay).", "Attosecond laser laboratory.", "MODERATE — attosecond tech exists.", "MODERATE", "Sub-attosecond timing would confirm field-resonance absorption.", "If timing matches standard model: both interpretations are equivalent.", "Electromagnetic", "Proposed (laboratory)"},
        {"Compton Scattering from Lattice Momentum Transfer",
         "Compton scattering is lattice momentum transfer, with the same cross-section as QED but different ontology.", "Standard: photon-electron scattering with momentum transfer.", "SDT predicts identical cross-sections because the lattice momentum transfer follows the same conservation laws.", "Compare SDT cross-section calculation to measured Compton data.", "Existing measurements.", "TRIVIAL — calculation.", "TRIVIAL", "Agreement confirms lattice ontology is observationally equivalent.", "N/A — should agree by construction.", "Electromagnetic", "Validated"},
        {"Cherenkov Radiation as Lattice Shock Wave",
         "Cherenkov radiation occurs when a particle exceeds the local lattice phase velocity — identical to a sonic boom in air.", "Standard: particle exceeds phase velocity of light in medium n > 1.", "Both SDT and standard physics agree: Cherenkov radiation is a medium effect. SDT simply notes that the vacuum itself is a medium with n = 1.", "Already validated by all Cherenkov detectors.", "Existing data.", "TRIVIAL — already measured.", "TRIVIAL", "Confirms the medium interpretation.", "N/A — confirmed.", "Electromagnetic", "Validated"},
        {"Magnetic Monopole Non-Existence from Topology",
         "Magnetic monopoles do not exist because magnetic fields are vortex wakes, which are always dipolar. A monopole would require a half-vortex, which is topologically impossible.", "Standard: Dirac monopoles are allowed; searches have found none.", "SDT predicts monopoles are topologically forbidden. No experiment can find one.", "Continue monopole searches. SDT predicts continued null results.", "MoEDAL (CERN), IceCube.", "TRIVIAL — prediction of null result.", "TRIVIAL", "Continued null results are consistent with SDT.", "If a monopole is found: SDT's topological argument is wrong.", "Electromagnetic", "Ongoing null result"},
        {"Superconductivity from Lattice Phase Locking",
         "Superconductivity is lattice phase-locking: below Tc, electron pairs lock into the spation lattice's phase structure, producing zero-resistance flow.", "Standard: BCS theory — Cooper pairing via phonon exchange.", "SDT reinterprets Cooper pairs as lattice-phase-locked vortex pairs. The mechanism is the same at low energy; differences appear at high-Tc.", "Measure vortex lattice structure in type-II superconductors at extreme resolution. Compare to SDT lattice predictions.", "Scanning tunnelling microscopy on NbSe₂ or YBCO.", "MODERATE — STM measurements.", "MODERATE", "If vortex lattice matches SDT predictions: validates phase-locking model.", "If no additional structure: BCS and SDT are indistinguishable.", "Electromagnetic", "Proposed (laboratory)"},
        {"Casimir Force Scaling at Sub-nm Gaps",
         "Casimir force at sub-nm gaps should show deviations from the 1/d⁴ power law due to spation lattice granularity.", "Standard: Casimir force scales as 1/d⁴ at all separable distances.", "SDT predicts the Casimir force ultimately resolves into individual spation relay contributions at sub-nm gaps. The force law should show discretisation effects.", "Measure Casimir force at 0.1-10 nm plate separations with atomic force microscopy.", "AFM with calibrated cantilever, gold surfaces.", "MODERATE — AFM exists but sub-nm Casimir is at the measurement frontier.", "MODERATE", "Force discretisation would directly image spation lattice structure.", "If smooth 1/d⁴: lattice granularity is below AFM resolution.", "Vacuum / Medium", "Proposed (laboratory)"},

        // E61-E70: Thermodynamics and radiation
        {"Blackbody Spectrum from Lattice Mode Counting",
         "Planck's blackbody spectrum emerges from counting spation lattice modes, not quantised oscillators.", "Standard: Planck's quantisation hypothesis → blackbody spectrum.", "SDT derives the same spectrum because the lattice has the same mode structure as Planck's oscillators. The derivation is different but the result is identical.", "Verify the derivation reproduces Planck's law exactly.", "Computational.", "TRIVIAL — derivation.", "TRIVIAL", "Same result, different ontology. Shows lattice modes = Planck quantisation.", "N/A — must agree.", "Radiation", "Calculable now"},
        {"Stefan-Boltzmann Law from Convergence Throughput",
         "The Stefan-Boltzmann constant σ = 2π⁵k_B⁴/(15h³c²) is derivable from lattice throughput geometry.", "Standard: σ follows from Planck's law integration.", "SDT integrates the same spectral law over the same geometry. The constant is identical.", "Verify derivation.", "Computational.", "TRIVIAL — derivation.", "TRIVIAL", "Same result confirms lattice model is consistent.", "N/A — must agree.", "Radiation", "Calculable now"},
        {"Wien's Displacement from Lattice Peak Mode",
         "Wien's law λ_max T = 2.898 × 10⁻³ m·K from the peak mode of the lattice spectrum.", "Standard: from Planck distribution maximisation.", "Same derivation, same result.", "Computational verification.", "Computational.", "TRIVIAL.", "TRIVIAL", "Confirms consistency.", "N/A.", "Radiation", "Calculable now"},
        {"Solar Luminosity from Convergence Recycling",
         "The Sun's luminosity (3.828 × 10²⁶ W) is convergence recycling: the Sun processes convergent pressure into radiation.", "Standard: nuclear fusion powers the Sun.", "SDT does not deny fusion occurs — it says fusion occurs BECAUSE of convergence. The pressure budget determines the luminosity.", "Calculate solar luminosity from the convergence budget at R_Sun.", "Computational.", "MODERATE — derivation.", "MODERATE", "If L_Sun emerges from convergence: stars are convergence processors.", "If L_Sun doesn't match: convergence budget alone doesn't set luminosity.", "Stellar Physics", "Calculable now"},
        {"Stellar Main Sequence from k-Gradient Equilibrium",
         "The HR diagram main sequence is a k-gradient equilibrium sequence. Each spectral type corresponds to a specific k-value.", "Standard: main sequence from mass-luminosity relation and nuclear burning.", "SDT maps the main sequence to the k-hierarchy: hot blue stars have low k (strong convergence), cool red stars have high k (weak convergence).", "Map measured stellar k-values (from orbital velocities) to HR diagram positions.", "GAIA stellar survey data.", "LOW — archival.", "LOW", "k-hierarchy mapping of the main sequence validates the pressure model.", "If no correlation: k-values don't map cleanly to spectral type.", "Stellar Physics", "Archival analysis"},
        {"White Dwarf Chandrasekhar Limit from Occlusion Saturation",
         "The Chandrasekhar limit (1.44 M_Sun) arises from occlusion saturation — beyond this mass, the occlusion fraction exceeds the lattice's carrying capacity.", "Standard: electron degeneracy pressure can no longer support the star.", "SDT replaces electron degeneracy with occlusion saturation.", "Calculate the occlusion-saturation mass limit. Compare to 1.44 M_Sun.", "Computational.", "MODERATE — derivation.", "MODERATE", "Reproducing the Chandrasekhar limit from occlusion would be significant.", "If the limit differs: occlusion saturation model needs calibration.", "Stellar Physics", "Calculable now"},
        {"Neutron Star Maximum Mass from Lattice Compression Limit",
         "The TOV limit (~2.2 M_Sun) emerges from the spation lattice compression limit — beyond this, the lattice cannot support further matter.", "Standard: TOV limit from GR + nuclear equation of state.", "SDT predicts a maximum mass from lattice compression rather than spacetime geometry.", "Calculate the lattice compression limit and corresponding maximum mass.", "Computational.", "HIGH — requires lattice equation of state.", "HIGH", "Reproducing the TOV limit from lattice physics would unify nuclear and gravitational physics.", "If the limit differs: lattice equation of state needs work.", "Stellar Physics", "Calculable now"},
        {"Black Hole Singularity Replacement: Maximum Compression State",
         "There is no singularity. The 'black hole' interior is a maximum-compression lattice state where matter exists at the planck density.", "Standard: singularity at r = 0 inside event horizon.", "SDT replaces singularities with maximum-compression states. The lattice cannot be compressed below the Planck volume per spation.", "Observe gravitational wave ringdown for deviations from GR's Kerr metric.", "LIGO/Virgo ringdown analysis.", "HIGH — requires precision ringdown measurement.", "HIGH", "Ringdown echoes would indicate structure at the would-be horizon.", "If perfect Kerr: no observable deviation from classical black holes.", "Stellar Physics", "Archival analysis"},
        {"Hawking Temperature from Lattice Surface Modes",
         "Black hole temperature (Hawking radiation) arises from lattice surface modes at the c-boundary, not quantum tunnelling.", "Standard: Hawking radiation from quantum tunnelling through the event horizon.", "SDT predicts the same temperature formula (T = ℏc³/8πkGM) because the surface mode spectrum matches the quantum calculation.", "Same prediction — different mechanism, same result.", "Currently undetectable.", "IMPOSSIBLE — Hawking radiation unmeasurable for stellar-mass objects.", "IMPOSSIBLE", "Unobservable with current technology.", "N/A.", "Stellar Physics", "Unmeasurable"},
        {"Gravitational Redshift from k-Gradient",
         "Gravitational redshift z = GM/(rc²) is a k-gradient effect: photons climbing out of a convergence well lose energy to the lattice.", "Standard: GR gravitational time dilation.", "Both predict the same redshift. SDT attributes it to medium interaction rather than time dilation.", "Already measured (Pound-Rebka, GPS). Same prediction.", "Existing data.", "TRIVIAL — already measured.", "TRIVIAL", "Confirmed. Same prediction, different ontology.", "N/A — confirmed.", "Gravity / Occlusion", "Validated"},

        // E71-E80: Laboratory and practical
        {"Gravitational Casimir Effect: Mass-Dependent Plate Force",
         "Casimir plates made of different materials should show slightly different force due to their different nuclear occlusion fractions.", "Standard: Casimir force depends only on plate geometry and dielectric properties.", "SDT predicts the gravitational (convergent pressure) component of the Casimir force depends on mass.", "Measure Casimir force between tungsten plates vs aluminium plates at identical gaps.", "AFM Casimir apparatus with interchangeable plates.", "MODERATE — requires precision material control.", "MODERATE", "Mass-dependent Casimir force would prove the gravitational component.", "If no material dependence: Casimir force is purely electromagnetic.", "Vacuum / Medium", "Proposed (laboratory)"},
        {"Speed of Light Variation in Dense Media from Lattice Compression",
         "The refractive index of dense media arises from lattice compression by nuclear occlusion.", "Standard: refractive index from electromagnetic polarisation of the medium.", "SDT predicts the same n(ω) but from a different mechanism — lattice compression changes the local relay speed.", "Measure c in extremely dense nuclear matter (neutron-rich nuclei). SDT predicts n from density.", "Heavy-ion collision experiments.", "HIGH — frontier nuclear physics.", "HIGH", "If n correlates with lattice density: validates the medium model.", "If n follows standard polarisation: lattice compression isn't the mechanism.", "Electromagnetic", "Proposed (FAIR/RHIC)"},
        {"Local Speed of Light Measurement Near Dense Object",
         "The local speed of light near a very dense object (neutron star, white dwarf) should be measurably different from c.", "Standard: c is constant; what changes is the coordinate speed (time dilation).", "SDT predicts the lattice relay speed changes near dense objects because the lattice is compressed.", "Measure timing of pulsar emission through different density environments.", "Pulsar timing data.", "LOW — archival.", "LOW", "Timing anomalies near dense objects would support variable relay speed.", "If timing is clean: lattice compression doesn't measurably affect c.", "Electromagnetic", "Archival analysis"},
        {"Unruh Effect as Lattice Asymmetry",
         "The Unruh effect (accelerating observer sees thermal radiation) is lattice asymmetry: acceleration creates a differential relay rate.", "Standard: Unruh effect from Rindler horizon and Bogoliubov transformation.", "SDT and standard physics predict the same temperature (T = ℏa/2πck_B). Different mechanism, same result.", "Currently unmeasurable — requires a ~ 10²⁰ m/s².", "None available.", "IMPOSSIBLE with current technology.", "IMPOSSIBLE", "Unobservable.", "N/A.", "Radiation", "Unmeasurable"},
        {"Precision Equivalence Principle Test at Sub-μg Level",
         "SDT predicts exact equivalence of inertial and gravitational mass because both measure V_disp.", "Standard: equivalence principle is a postulate of GR, tested to 10⁻¹⁵.", "Both predict exact equivalence. SDT explains WHY: both are throughput reorganisation cost.", "Continue MICROSCOPE-type experiments to higher precision.", "MICROSCOPE satellite follow-on.", "HIGH — space mission.", "HIGH", "Continued agreement validates both theories. Any deviation would overthrow both.", "If violation found: both GR and SDT need modification.", "Gravity / Occlusion", "Ongoing"},
        {"Torsion Balance Gravitational Constant Measurement",
         "G is not fundamental — it is derived from G = c²R/(k²r) evaluated at laboratory scale. Different lab environments may give slightly different G.", "Standard: G is a universal fundamental constant (6.674 × 10⁻¹¹).", "The ~0.05% discrepancy between different G measurements may reflect real environmental variation.", "Measure G in underground laboratories vs mountaintop vs satellite. Look for systematic environment dependence.", "Multiple torsion balance facilities.", "MODERATE — coordinated measurement campaign.", "MODERATE", "If G varies with environment: proves G is derived, not fundamental.", "If G is constant: environmental effects are below measurement precision.", "Gravity / Occlusion", "Proposed (laboratory)"},
        {"Sagnac Effect as Lattice Phase Rotation",
         "The Sagnac effect is lattice phase rotation: rotating platforms produce differential relay path lengths.", "Standard: Sagnac effect from rotating reference frame (consistent with SR).", "Both predict the same phase shift. SDT attributes it to the lattice, SR to frame rotation.", "Already measured in ring laser gyroscopes. Same prediction.", "Existing data.", "TRIVIAL — already measured.", "TRIVIAL", "Confirmed. Same result.", "N/A — confirmed.", "Electromagnetic", "Validated"},
        {"Gravitational Time Dilation from Lattice Compression",
         "Clocks run slower in gravitational fields because the lattice is compressed: relay cycles are shorter → fewer ticks per external second.", "Standard: GR gravitational time dilation from spacetime curvature.", "Both predict identical time dilation. SDT explains mechanism: compressed lattice → shorter relay cycles → slower clock.", "Already measured (Hafele-Keating, GPS, Pound-Rebka). Same prediction.", "Existing data.", "TRIVIAL — already measured.", "TRIVIAL", "Confirmed. Same result, different explanation.", "N/A — confirmed.", "Gravity / Occlusion", "Validated"},
        {"Pair Production Threshold from Lattice Energy Budget",
         "Pair production at 2 × 511 keV = 1.022 MeV is lattice conversion: sufficient relay energy converts to two counter-rotating vortices.", "Standard: pair production from energy-mass equivalence in EM field of a nucleus.", "Both predict the same threshold. SDT attributes it to lattice vortex creation.", "Already measured. Same prediction.", "Existing data.", "TRIVIAL — already measured.", "TRIVIAL", "Confirmed. Same threshold.", "N/A — confirmed.", "Electromagnetic", "Validated"},
        {"Positron Annihilation as Vortex Collision",
         "Annihilation produces 2 × 511 keV photons because counter-rotating vortices cancel, releasing circulation energy to the lattice.", "Standard: matter-antimatter annihilation.", "Same prediction — 2 × 511 keV. Different mechanism.", "Already measured.", "Existing data.", "TRIVIAL.", "TRIVIAL", "Confirmed.", "N/A.", "Electromagnetic", "Validated"},
        {"Electron Diffraction from Lattice Scattering",
         "Electron diffraction is lattice scattering: the electron vortex interacts with crystal lattice structure via pressure field coupling.", "Standard: wave-particle duality — electron has de Broglie wavelength.", "SDT predicts the same diffraction pattern because the scattering geometry is identical. The electron is a vortex with wavelength λ = h/p, which is the lattice resonance wavelength.", "Already measured. Same pattern.", "Existing data.", "TRIVIAL — already measured.", "TRIVIAL", "Confirmed. Lattice scattering produces identical diffraction.", "N/A.", "Electromagnetic", "Validated"},

        // E81-E90: Specific tests
        {"Time of Flight Neutrino Mass Test",
         "Neutrinos travel at c (they are lattice distortions, not massive particles). Any measured speed deficit is lattice dispersion, not rest mass.", "Standard: neutrinos have small mass (< 0.8 eV) and travel slightly below c.", "SDT predicts neutrinos are massless lattice modes. Speed deficits arise from dispersion.", "Measure neutrino speed from next galactic supernova with sub-ns timing.", "IceCube + SN optical detection.", "HIGH — requires nearby supernova.", "HIGH", "If ν speed = c exactly: supports massless lattice mode.", "If v < c: neutrinos have mass, requiring SDT modification.", "Nuclear Physics", "Awaiting nearby SN"},
        {"Spation Lattice Resonance in Quantum Oscillator",
         "A mechanical oscillator at millikelvin temperatures should show quantised noise from the spation lattice thermal spectrum.", "Standard: quantum ground state motion dominated by zero-point energy.", "SDT predicts the same zero-point energy because the lattice thermal spectrum matches quantum vacuum fluctuations.", "Measure mechanical oscillator noise spectrum at 10 mK.", "LIGO-style optomechanical oscillator.", "MODERATE — exists.", "MODERATE", "Same spectrum confirms lattice = quantum vacuum.", "N/A — should agree.", "Vacuum / Medium", "Proposed (laboratory)"},
        {"Aharonov-Bohm as Lattice Phase Shift",
         "The AB effect is a lattice phase shift caused by a vector potential modifying lattice relay phases.", "Standard: AB effect from EM vector potential coupling to electron wavefunction.", "Both predict identical phase shifts. SDT attributes it to lattice relay modification.", "Already measured. Same prediction.", "Existing data.", "TRIVIAL.", "TRIVIAL", "Confirmed.", "N/A.", "Electromagnetic", "Validated"},
        {"Josephson Junction Frequency from Lattice Phase Coupling",
         "The Josephson frequency f = 2eV/h arises from lattice phase coupling across the superconducting gap.", "Standard: Josephson effect from macroscopic quantum coherence.", "Same frequency. Different ontology.", "Already measured. Defines the volt.", "Existing data.", "TRIVIAL.", "TRIVIAL", "Confirmed.", "N/A.", "Electromagnetic", "Validated"},
        {"Quantum Hall Effect from Lattice Topology",
         "Quantised Hall conductance (e²/h per Landau level) emerges from topological constraints in the 2D lattice.", "Standard: Landau quantisation + topological invariant.", "Same quantisation. SDT attributes it to lattice topology.", "Already measured. Defines resistance.", "Existing data.", "TRIVIAL.", "TRIVIAL", "Confirmed.", "N/A.", "Electromagnetic", "Validated"},
        {"Vacuum Birefringence from Lattice Anisotropy",
         "Strong magnetic fields produce vacuum birefringence because the field creates anisotropy in the lattice relay rates.", "Standard: QED vacuum birefringence from virtual pair loops.", "Same prediction — birefringence should be detectable at ~10¹⁵ T (magnetar fields).", "Measure polarisation of X-rays from magnetar SGR 1806-20.", "X-ray polarimeter (IXPE satellite).", "HIGH — frontier measurement.", "HIGH", "Detection confirms the medium has structure. Same prediction either way.", "If not detected: field strength insufficient or below sensitivity.", "Electromagnetic", "Proposed (satellite)"},
        {"Schwinger Pair Production from Lattice Breakdown",
         "Schwinger pair production (E > 1.3 × 10¹⁸ V/m) is lattice dielectric breakdown — the field exceeds the lattice's relay capacity.", "Standard: pair creation from strong-field QED.", "Same threshold. SDT attributes it to lattice breakdown.", "Measure pair production threshold at extreme field intensities (ELI facility).", "ELI-NP (Romania) petawatt lasers.", "HIGH — frontier facility.", "HIGH", "Same threshold confirms lattice-QED equivalence at this scale.", "If threshold differs: lattice has different breakdown point.", "Electromagnetic", "Proposed (ELI-NP)"},
        {"Bremsstrahlung from Lattice Deceleration Radiation",
         "Bremsstrahlung is lattice deceleration radiation: when a vortex decelerates, it releases circulation energy to the lattice as EM radiation.", "Standard: classical EM radiation from accelerated charges.", "Same spectrum. Same power law.", "Already measured extensively.", "Existing data.", "TRIVIAL.", "TRIVIAL", "Confirmed.", "N/A.", "Electromagnetic", "Validated"},
        {"Cosmic Ray Ultra-High Energy Cutoff (GZK) from Lattice Limit",
         "The GZK cutoff (~5 × 10¹⁹ eV) is the lattice energy density limit — above this, the vortex exceeds the lattice relay capacity.", "Standard: GZK cutoff from pion photoproduction on CMB.", "Same cutoff energy — different mechanisms.", "Already measured by Auger Observatory.", "Pierre Auger Observatory data.", "TRIVIAL — already measured.", "TRIVIAL", "Same cutoff. Consistent.", "N/A.", "Cosmology", "Validated"},
        {"Muon Anomalous Magnetic Moment (g-2) from Lattice Corrections",
         "The muon g-2 anomaly (~4.2σ from theory) arises from lattice corrections that differ at the muon mass scale.", "Standard: hadronic vacuum polarisation uncertainty.", "SDT predicts the lattice correction differs for muons because the W=1 vortex has a different mass/size ratio.", "Compare SDT lattice g-2 prediction to Fermilab measurement.", "Fermilab g-2 data.", "HIGH — requires lattice perturbation theory for muons.", "HIGH", "If SDT resolves the g-2 tension: validates lattice corrections.", "If SDT prediction matches standard: no new physics from lattice.", "Electromagnetic", "Calculable now"},

        // E91-E100: Engineering applications and practical tests
        {"Convergence-Assisted Propulsion: Solar Sail Enhancement",
         "A sail designed to reflect convergent pressure (not just photon pressure) should experience enhanced thrust.", "Standard: solar sail thrust = radiation pressure only.", "SDT predicts the convergence field contributes additional pressure beyond photon momentum. A properly designed sail might harvest this.", "Deploy a solar sail with convergence-optimised surface (dense, reflective) and compare thrust to photon-pressure predictions.", "Solar sail spacecraft (JAXA/NASA heritage).", "HIGH — space mission.", "HIGH", "Excess thrust beyond photon pressure would demonstrate convergence harvesting.", "If thrust matches photon pressure: convergence contribution is undetectable at sail scale.", "Engineering", "Proposed (space mission)"},
        {"Lattice Waveguide: Vacuum Waveguide Effect",
         "A hollow tube in vacuum should guide electromagnetic waves differently from free-space propagation due to lattice boundary effects.", "Standard: waveguide theory from boundary conditions on EM fields.", "SDT predicts the same waveguide modes because boundary conditions are identical. But predicts subtle corrections from lattice granularity at extreme frequencies.", "Measure waveguide cutoff frequencies at extreme precision in vacuum.", "Microwave/mm-wave waveguide in vacuum.", "MODERATE.", "MODERATE", "Any deviation from EM theory at extreme frequencies indicates lattice granularity.", "If no deviation: lattice is smooth at measured frequencies.", "Electromagnetic", "Proposed (laboratory)"},
        {"Convergence Lens: Focusing Convergent Pressure with Dense Matter",
         "A very dense sphere should focus convergent pressure, creating a measurable gravity enhancement on its far side.", "Standard: no such effect — gravity is not focusable.", "SDT predicts that a dense body partially occludes convergence from one direction, creating a pressure shadow. A second body in this shadow experiences enhanced net force toward the dense body — but also reduced force from behind.", "Measure gravitational acceleration on the far side of a dense sphere (Pb or W, 1 m radius) with sub-μg accelerometer.", "1 m radius lead sphere, MEMS accelerometer.", "HIGH — requires extreme sensitivity.", "HIGH", "Measurable pressure shadow behind a dense sphere proves gravity is occludable.", "If no shadow: occlusion at this scale is undetectable.", "Gravity / Occlusion", "Proposed (laboratory)"},
        {"Lattice Communication: Information Transfer Through Vacuum",
         "Coherent information can be transferred through vacuum at frequencies above the EM spectrum via lattice mode coupling.", "Standard: impossible — no medium for transmission above EM.", "SDT predicts the lattice supports modes beyond EM. Whether these can carry information is an open question.", "Attempt to modulate and detect non-EM lattice modes using Casimir-coupled piezoelectric transducers.", "Casimir transducer pairs in UHV.", "EXTREME — frontier physics.", "EXTREME", "If successful: opens entirely new communication physics.", "Most likely: no signal above noise at accessible frequencies.", "Engineering", "Proposed (laboratory)"},
        {"Artificial Gravity from Convergence Focusing",
         "Convergence focusing can create localised gravitational fields without rotation.", "Standard: no way to create artificial gravity except rotation or acceleration.", "SDT suggests that dense matter arrangements could focus convergence to create localised gravity wells.", "Computational feasibility study first. Required mass would likely be planetary-scale.", "Computational.", "EXTREME — likely requires planetary-scale mass.", "EXTREME", "If feasible: artificial gravity without rotation.", "Most likely: unfeasible at accessible mass scales.", "Engineering", "Computational feasibility"},
        {"Earth Core Seismic Speed from Lattice Compression",
         "Seismic wave speeds in Earth's core should correlate with the convergence-field compression gradient.", "Standard: seismic speeds from material properties (density, bulk/shear moduli).", "SDT predicts seismic velocities partially reflect lattice compression, which increases toward Earth's centre.", "Compare seismic travel times to SDT lattice compression model.", "Global seismograph network data.", "LOW — archival.", "LOW", "If correlation exists: supports lattice compression gradient.", "If no correlation: seismic speeds are purely material properties.", "Gravity / Occlusion", "Archival analysis"},
        {"Precision Cavendish with Variable Chamber Pressure",
         "The Cavendish experiment should show a measurable difference at different chamber gas pressures because the gas contributes to local convergence.", "Standard: G is independent of chamber atmosphere.", "SDT predicts extremely small pressure-dependent corrections to the measured G value.", "Measure G in vacuum vs 1 atm vs 100 atm.", "High-pressure torsion balance chamber.", "MODERATE — precision Cavendish exists.", "MODERATE", "If G varies with pressure: proves convergence mechanism.", "If G is constant: atmospheric convergence is undetectable.", "Gravity / Occlusion", "Proposed (laboratory)"},
        {"Ocean Tidal Analysis: SDT Pressure vs Newton Potential",
         "Tidal forces arise from convergence gradient differentials, not gravitational potential gradients. SDT predicts subtle higher-order tidal harmonics.", "Standard: tidal forces from gravitational potential gradient.", "SDT's convergence model should reproduce Newton's tidal formula at leading order but predict additional small corrections.", "Analyse high-precision ocean tide gauge data for SDT-predicted higher harmonics.", "Global tide gauge network (UHSLC).", "LOW — archival.", "LOW", "Detection of SDT-predicted harmonics in tidal data.", "If standard harmonics suffice: convergence corrections are undetectable.", "Gravity / Occlusion", "Archival analysis"},
        {"Lattice Dispersion Relation: Frequency-Dependent c",
         "At extremely high frequencies (approaching Planck frequency), c should show dispersion due to lattice granularity.", "Standard: c is frequency-independent in vacuum (Lorentz invariance).", "SDT predicts the lattice relay mechanism introduces dispersion at ~Planck frequencies. Measurable proxies: gamma-ray burst arrival times at different energies.", "Measure arrival time differences of high- vs low-energy photons from GRBs.", "Fermi-LAT, CTA.", "LOW — data exists.", "LOW", "Frequency-dependent c would prove lattice granularity and set the lattice spacing.", "If no dispersion: Lorentz invariance holds to measured precision.", "Electromagnetic", "Archival analysis"},
        {"Complete Convergence Budget of the Solar System",
         "The total convergence budget of the solar system (Sun + planets) should balance against the CMB influx, with stars as recyclers.", "Standard: no such conservation law exists.", "SDT's Law II (Release Cascade) predicts that every star processes convergent pressure. The solar luminosity should equal the convergence throughput.", "Calculate the total solar convergence budget from the k-hierarchy and compare to L_Sun.", "Computational.", "MODERATE — derivation.", "MODERATE", "If the budget balances: validates Law II (Release Cascade).", "If it doesn't balance: convergence accounting needs work.", "Cosmology", "Calculable now"},
    };

    int num = 31;
    for (auto& t : templates) {
        Experiment e;
        e.number = num++;
        e.title = t.title;
        std::ostringstream fn;
        fn << "E" << std::setfill('0') << std::setw(2) << e.number << "_";
        // Make filename from title
        std::string clean;
        for (char c : t.title) {
            if (std::isalnum(c)) clean += c;
            else if (c == ' ' || c == '-') clean += '_';
        }
        // Truncate to 50 chars
        if (clean.length() > 50) clean = clean.substr(0, 50);
        fn << clean;
        e.filename = fn.str();
        e.sdt_prediction = t.sdt_pred;
        e.standard_prediction = t.std_pred;
        e.background = t.bg;
        e.observable = t.obs;
        e.apparatus = t.app;
        e.feasibility = t.feas;
        e.difficulty = t.diff;
        e.impact_positive = t.imp_pos;
        e.impact_negative = t.imp_neg;
        e.category = t.cat;
        e.status = t.status;
        exps.push_back(e);
    }

    return exps;
}

void write_experiment(const std::string& dir, const Experiment& e) {
    std::ostringstream fn;
    fn << dir << "/" << e.filename << ".md";
    std::ofstream out(fn.str());

    out << "# " << e.filename.substr(0, 3) << ": " << e.title << "\n\n";
    out << "> **Category**: " << e.category << "\n";
    out << "> **Difficulty**: " << e.difficulty << "\n";
    out << "> **Status**: " << e.status << "\n\n";
    out << "---\n\n";
    out << "## 1. Background\n\n" << e.background << "\n\n";
    out << "## 2. SDT Prediction\n\n" << e.sdt_prediction << "\n\n";
    out << "## 3. Standard Prediction\n\n" << e.standard_prediction << "\n\n";
    out << "## 4. Observable\n\n" << e.observable << "\n\n";
    out << "## 5. Apparatus\n\n" << e.apparatus << "\n\n";
    out << "## 6. Feasibility\n\n" << e.feasibility << "\n\n";
    out << "## 7. Impact\n\n";
    out << "- **If confirmed**: " << e.impact_positive << "\n";
    out << "- **If not confirmed**: " << e.impact_negative << "\n";

    out.close();
    std::cout << "  WROTE: " << fn.str() << "\n";
}

int main() {
    std::string dir = "Experiments";
    auto exps = build_experiments();

    std::cout << "# Generating " << exps.size() << " experiments\n\n";

    for (auto& e : exps) {
        write_experiment(dir, e);
    }

    // Update README
    std::ofstream readme(dir + "/README.md");
    readme << "# SDT Experimental Programme\n\n";
    readme << "100 experiments derived from Spatial Displacement Theory predictions.\n";
    readme << "Each experiment specifies the SDT prediction, the standard model prediction,\n";
    readme << "the observable difference, feasibility, and impact.\n\n";
    readme << "**Author**: James Christopher Tyndall, Melbourne, Australia\n\n";
    readme << "---\n\n";

    // Group by category
    std::vector<std::string> cats = {
        "Orbital Mechanics", "Vacuum / Medium", "Gravity / Occlusion",
        "Nuclear Physics", "Atomic Physics", "Cosmology",
        "Electromagnetic", "Solar Physics", "Stellar Physics",
        "Radiation", "Engineering"
    };

    // Existing E01-E20
    readme << "## Index (E01–E20: Original Programme)\n\n";
    readme << "| # | Experiment | Status |\n";
    readme << "|---|-----------|--------|\n";
    readme << "| E01 | PTOLEMY CνB Detection | Awaiting detector |\n";
    readme << "| E02 | Neutrino Magnetic Moment | GEMMA-III running |\n";
    readme << "| E03 | Multi-Messenger Distance Discrepancy | Feasible now |\n";
    readme << "| E04 | Supernova Neutrino Timing | Awaiting nearby SN |\n";
    readme << "| E05 | Oort Cloud Centreline | Archival data |\n";
    readme << "| E06 | Saturn Ring Interferometry | Future orbiter |\n";
    readme << "| E07 | Primordial Lithium Resolution | Archival data |\n";
    readme << "| E08 | Hubble Tension 3-Way Test | Future |\n";
    readme << "| E09 | Le Sage Thermal Budget | Calculable now |\n";
    readme << "| E10 | Casimir as Convergence Occlusion | Already measured |\n";
    readme << "| E11 | Pressure-Gradient Redshift | Derivable now |\n";
    readme << "| E12 | Dark Stars / Supercritical Displacement | Future detection |\n";
    readme << "| E13 | Charge-State EC Rate Scan | Proposed (GSI/FAIR) |\n";
    readme << "| E14 | Ionisation-Controlled EC Medicine | Proposed (GSI/FAIR) |\n";
    readme << "| E15 | Magnetic Field Be-7 EC | Proposed (NHMFL) |\n";
    readme << "| E16 | Se-68 Cascade Timer | Proposed (GSI/FAIR) |\n";
    readme << "| E17 | Ba-133 Anion EC Rate | Proposed |\n";
    readme << "| E18 | Co-56 Gamma Rearrangement | Data reanalysis |\n";
    readme << "| E19 | Spectral He-3/He-4 Core | Proposed (ISOLDE) |\n";
    readme << "| E20 | Neutron Budget Verification | Archival analysis |\n\n";

    readme << "## Index (E21–E100: Extended Programme)\n\n";
    readme << "| # | Experiment | Category | Difficulty | Status |\n";
    readme << "|---|-----------|----------|-----------|--------|\n";

    for (auto& e : exps) {
        readme << "| E" << std::setfill('0') << std::setw(2) << e.number
               << " | " << e.title
               << " | " << e.category
               << " | " << e.difficulty
               << " | " << e.status << " |\n";
    }

    readme << "\n---\n\n";

    // Difficulty summary
    readme << "## Difficulty Summary\n\n";
    readme << "| Difficulty | Count |\n";
    readme << "|-----------|-------|\n";

    int trivial=0, low=0, mod=0, high=0, extreme=0, impossible=0;
    for (auto& e : exps) {
        if (e.difficulty == "TRIVIAL") trivial++;
        else if (e.difficulty == "LOW") low++;
        else if (e.difficulty == "MODERATE") mod++;
        else if (e.difficulty == "HIGH") high++;
        else if (e.difficulty == "EXTREME") extreme++;
        else if (e.difficulty == "IMPOSSIBLE") impossible++;
    }
    // Add existing 20
    readme << "| Validated/Trivial | " << trivial + 5 << " |\n";
    readme << "| Low (archival/calculation) | " << low + 6 << " |\n";
    readme << "| Moderate (existing facilities) | " << mod + 5 << " |\n";
    readme << "| High (frontier) | " << high + 4 << " |\n";
    readme << "| Extreme (megastructure/new physics) | " << extreme << " |\n";
    readme << "| Unmeasurable (current tech) | " << impossible << " |\n\n";

    readme << "---\n\n";
    readme << "*All predictions use empirically measured values only. No interpretive frameworks imported.*\n";

    readme.close();
    std::cout << "\nREADME updated with " << (20 + exps.size()) << " total experiments.\n";

    return 0;
}
