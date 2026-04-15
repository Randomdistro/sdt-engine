# SDT Investigations

Formal research programme derived from SDT's theoretical framework and experimental catalogue.
Each investigation folder contains a PROMPT.md (detailed methodology and success criteria) and,
where applicable, a DATA_REQUIREMENTS.md (all constants, databases, and sources needed).

All investigations operate WITHIN SDT as the governing framework. SDT is the ruleset;
the investigation derives predictions and compares them to measurements.

---

## Atmospheric Spallation (consolidated)

| Folder | Subject |
|--------|---------|
| Atmospheric_Spallation/ | All spallation-related work: Q01–Q06 (theoretical), A01–A06 (archival) |

---

## Experiment Investigations (from Experiments/ catalogue)

### Nuclear Physics
| Folder | Experiment | Type |
|--------|-----------|------|
| E28_Triple_Alpha_Geometric_Packing | Hoyle state from α+4d packing geometry | Calculation |
| E29_Deuteron_Binding_from_Occlusion | B_d = 2.224 MeV from occlusion force | Calculation |
| E30_Alpha_Binding_from_Tetrahedral_Occlusion | B_α = 28.296 MeV from tetrahedral geometry | Calculation |
| E31_Neutron_Lifetime | τ_n ≈ 880 s from topological rearrangement rate | Derivation |
| E33_Nuclear_Charge_Radius_Scaling | R_ch = Z×R_p vs r₀×A^(1/3) — archival test | Archival |
| E35_Fe56_vs_Ni62_Grammar_Efficiency | Abundance from grammar symmetry | Archival |
| E39_Proton_Neutron_Mass_Difference | Δm = 1.293 MeV from topology | Derivation |
| E40_Nuclear_Magnetic_Moments_from_Vortex | μ for p, n, d, t, He-3 from W=3 trefoil | Derivation |

### Cosmology
| Folder | Experiment | Type |
|--------|-----------|------|
| E07_Primordial_Lithium_Resolution | Li-7 problem via ionisation-suppressed EC | Calculation |
| E11_E45_Pressure_Gradient_Redshift_and_BAO | Distance-redshift + BAO scale from lattice | Archival |
| E42_E49_Hubble_Tension_and_Dark_Energy | Pantheon+ fit without Λ | Archival |
| E46_Galaxy_Rotation_Curves | SPARC rotation curves from eclipse saturation | Archival |
| E47_Gravitational_Lensing | Lensing as convergence-gradient refraction | Archival |

### Orbital Mechanics / Gravity
| Folder | Experiment | Type |
|--------|-----------|------|
| E24_Mercury_Precession_from_k_Hierarchy | 42.98"/century from k²-gradient | Calculation |
| E97_Earth_Core_Seismic_Speed | Seismic v vs convergence gradient | Archival |
| E99_Ocean_Tidal_Analysis | Tidal forcing from convergence differential | Archival |
| E101_Solar_System_Convergence_Budget | Complete k-hierarchy for solar system | Calculation |

### Radiation / Stellar
| Folder | Experiment | Type |
|--------|-----------|------|
| E09_Le_Sage_Thermal_Budget | Convergence heating rate vs geothermal | Calculation |
| E61_E63_Blackbody_Radiation_from_Lattice | Planck, Stefan-Boltzmann, Wien from modes | Derivation |
| E64_Solar_Luminosity | L_Sun from convergence recycling | Calculation |
| E65_Stellar_Main_Sequence_k_Gradient | HR diagram as k-sequence | Archival |

---

## Codebase Questions (from engine code review)

| Folder | Question | Source |
|--------|----------|--------|
| CQ01_Transfer_Function_Derivation | Is f = 2.125e-17 universal or scale-dependent? | laws.hpp:200 |
| CQ02_Vortex_Equilibrium_Quantisation | Which R/a values give stable tori? | Theory/03_Open_Problems |
| CQ03_Fine_Structure_from_Topology | Can α be derived from W=1 geometry? | Theory/03_Open_Problems |
| CQ04_State28D_Force_Ratio_Constants | Derive the 10³⁰ and 10⁻⁹ magic numbers | state28d.hpp:168 |
| CQ05_Proton_Electron_Mass_Ratio | m_p/m_e from W=3 vs W=1 equilibrium | Theory/03_Open_Problems |
| CQ06_Eclipse_Saturation_Model | Missing galactic.hpp — needs implementation | E46 reference |
| CQ07_Neutrino_Magnetic_Moment | Formalise μ_ν ≡ 0 prediction | neutrino.hpp:9 |

---

## Dependency Map

```
CQ02 (R/a quantisation)
  ├── CQ03 (α from topology — needs W=1 equilibrium)
  ├── CQ05 (m_p/m_e — needs W=3 vs W=1 ratio)
  └── E40 (magnetic moments — needs circulation modes)

E29 (deuteron binding)
  └── E30 (alpha binding — needs bond energy from E29)
       └── E28 (triple alpha — needs packing energy)

CQ06 (eclipse saturation model)
  └── E46 (galaxy rotation curves — needs the model)

E42+E49 (Hubble + dark energy)
  └── E11+E45 (redshift model + BAO — shared cosmology)

CQ01 (transfer function)
  └── E09 (Le Sage thermal — needs f universality)
```
