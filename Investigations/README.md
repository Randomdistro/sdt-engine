# SDT Investigations

Formal research programme derived from SDT's theoretical framework and experimental catalogue.
Each investigation folder contains a **PROMPT.md** (methodology, gates, pivot tables — built from
`PERFECT_PROMPT_TEMPLATE.md`), optional **DATA_REQUIREMENTS.md**, and on run: **RUN_LOG.md** +
tool + **`*_VERDICT.md`**.

**Prompt standards (2026-06-27):**
- Author / extend prompts using `Investigations/PERFECT_PROMPT_TEMPLATE.md` (§⓪–§⑩).
- Execute using `Investigations/PROMPT_EXECUTION_PROTOCOL.md` — pre-commit thresholds, adjust on failure.
- **Batch upgrade:** `python Investigations/tools/prompt_upgrade.py` — applied to **125/128** prompts (§⑩ + header + dual verdict + RUN_LOG).
- **Full exemplar rewrites** (audit-driven, excruciating detail): `OP01`, `QM06`, `CH01`, `CM02`, `PM03`, `GD06`, `PPT04`, `TD01`.
- Re-run upgrade after editing prompts: `python Investigations/tools/prompt_upgrade.py --dry-run` to preview.

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
| CQ06_Eclipse_Saturation_Model | Missing galactic.hpp — needs implementation | GD05 reference |
| CQ07_Neutrino_Magnetic_Moment | Formalise μ_ν ≡ 0 prediction | neutrino.hpp:9 |
| CQ15_Spation_Depth_Engine | z(r)=ϟ/r reproduces redshift, Shapiro, bending, cosmological z | laws.hpp:bridge |
| CQ26_Universal_Drafting_Crossover | Is B=Φ(ξ), ξ=g_self/g_floor, one scale-invariant curve across atomic/stellar/galactic/nuclear? 40 examples × 3 types × 4 classes × 4 scales | galactic.hpp:77, APS02, GOM12, GD05-M4 |
| CQ37_Elementary_Charge_Quantisation | Can e = 1.602e-19 C be derived from {ℓ_P, c, ℏ, k_B, T_CMB, d}? | PPT02 dependency |

---

## Dependency Map

```
PPT01 (R/a quantisation)
  ├── PPT02 (α from topology — needs W=1 equilibrium)
  │   └── EMC02 (e from topology — depends on PPT02 solution)
  ├── PPT03 (m_p/m_e — needs W=3 vs W=1 ratio)
  └── NP15 (magnetic moments — needs circulation modes)

NP09 (deuteron binding)
  └── NP10 (alpha binding — needs bond energy from NP09)
       └── NP08 (triple alpha — needs packing energy)

GD01 (eclipse saturation model)
  └── GD05 (galaxy rotation curves — needs the model)

CR09+CR09 (Hubble + dark energy)
  └── CR08+CR08 (redshift model + BAO — shared cosmology)

EMC01 (transfer function)
  └── SAR01 (Le Sage thermal — needs f universality)
```
