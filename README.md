# SDT Engine — Spatial Displacement Theory

**A mechanistic model of physical reality built from 9 axioms, producing 17 theorems with zero free parameters.**

*One medium. One tick. One budget.*

---

## Abstract

Spatial Displacement Theory (SDT) proposes that all physical phenomena emerge from a single postulate: space is a nearest-neighbour phase-relay medium — the **spation lattice** — in which all force, mass, and radiation arise from convergent pressure, occlusion geometry, and displacement topology, without recourse to gravitational constants, quantum mechanical wavefunctions, or Standard Model primitives.

From this postulate:

- **Gravity** is convergent boundary occlusion: F = (π/4) P_eff R₁²R₂² / r²
- **Mass** is throughput reorganisation cost: m = ΦV_disp / (3ℓ_P³c²)
- **Special relativity** is a movement budget: v_circ² + v² = c²
- **The Coulomb coupling** is derived: k_e·e² = αℏc (not postulated)
- **The proton charge radius** is predicted: R_p = 4ℏ/(m_p c) — matching muonic hydrogen to 0.02%
- **Nuclear structure** is purely geometric: one alpha core + deuteron/triton shells

The framework has been validated across 287 naturally occurring isotopes, 126 ionisation states, 12 spectral transitions, the binding energy curve, and the Golden Boundary (Z=79) nuclear stability threshold.

---

## Repository Structure

```
sdt-engine/
│
├── Engine/                      C++20 header-only library
│   └── include/sdt/
│       └── laws.hpp             THE single source of truth
│                                (9 axioms, 17 theorems, all constants)
│
├── Theory/                      Formal framework (read 00→04)
│   ├── 00_Ruleset.md
│   ├── 01_Closure_Derivations.md
│   ├── 02_Inputs_and_Derivations.md
│   ├── 03_Open_Problems.md
│   └── 04_Notation.md
│
├── Laws/                        The Five Laws (formal papers)
│   ├── Law_I_Cosmological_Relay_Throughput
│   ├── Law_II_Release_Cascade
│   ├── Law_III_Convergent_Boundary_Pressure
│   ├── Law_IV_Inertial_Mass
│   ├── Law_V_Movement_Budget
│   └── Law_VI_Vortex_Topology_Quantisation
│
├── ATOMICUS/                    Complete atomic/nuclear database
│   ├── elements/                118 element characterisations
│   ├── isotopes/                287 naturally occurring isotopes
│   ├── ec_investigations/       17 electron capture investigations
│   ├── rules/                   Nuclear construction grammar
│   ├── reports/                 Structural analysis outputs
│   ├── tools/                   C++20 generators & validators
│   └── reference/               Quick-reference cards
│
├── Hubble/                      Cosmological analysis suite
│   ├── INVESTIGATION_Hubble_Tension.md
│   ├── data/                    SN Ia datasets, zk² tables
│   └── tools/                   18 C++20 analysis tools
│
├── Experiments/                 8 proposed experimental tests
│   └── E13–E20 (falsifiable predictions)
│
└── Benchmarks/                  Validation suite (B01–B25)
```

---

## The Five Laws

| Law | Name | Core Statement |
|-----|------|----------------|
| **I** | Cosmological Relay Throughput | The spation lattice is a globally phase-loaded relay medium. Φ = Nε. |
| **II** | Release Cascade | At the Clearing, every spation released its held content. Stars recycle convergence. |
| **III** | Convergent Boundary Pressure | Force = occluded convergence. F = (π/4) P_eff R₁²R₂² / r². Same mechanism for Coulomb, gravity, nuclear. |
| **IV** | Inertial Mass | Mass = throughput reorganisation cost. m = ΦV_disp / (3ℓ_P³c²). Inertial = gravitational because both measure V_disp. |
| **V** | Movement Budget | v_circ² + v² = c². Three axioms → all of special relativity. |

---

## Key Results

| Prediction | Value | Match |
|-----------|-------|-------|
| Proton charge radius (W+1 conjecture) | 4ℏ/(m_p c) = 0.84124 fm | **0.02%** vs muonic H |
| Coulomb coupling identity | k_e·e² = αℏc | **6×10⁻⁸ %** (exact) |
| He-4 charge radius | Z × R_p = 1.683 fm | **0.44%** vs measured |
| Z² ionisation scaling | Ry × Z² for 13 H-like ions | **All < 0.5%** |
| Rydberg spectral lines | 12 transitions (Lyman, Balmer, Paschen) | **All < 1%** |
| Nuclear grammar | α + d + t for 287 isotopes | **287/287 valid** |
| Binding energy peak | Fe-56 at 8.790 MeV/nucleon | **Confirmed** |
| Golden Boundary | Au-197: first D < T (38 vs 39) | **Confirmed** |
| zk² = 1 closure | 126 ionisation levels | **126/126** |

---

## Nuclear Construction Grammar

Every nucleus (Z ≥ 2) decomposes into exactly:

$$\text{1 alpha core} + n_d \text{ deuterons} + n_t \text{ tritons}$$

$$n_t = A - 2Z, \quad n_d = 3Z - A - 2$$

The electron capture mechanism is driven by nuclei with an **He-3 core** (incomplete alpha) rather than an He-4 core. The alternate grammar — validated across all 56 EC isotopes — is:

$$n_t = A - 2Z + 1, \quad n_d = 3Z - A - 3$$

---

## Building

```bash
# Build validation suite
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release

# Run structural analysis (standalone)
cl /std:c++20 /EHsc /O2 /Fe:analysis.exe ATOMICUS/tools/structural_analysis.cpp
./analysis.exe
# → Writes ATOMICUS/STRUCTURAL_ANALYSIS_REPORT.md
```

---

## Prohibitions

This framework does **not** import:

- G or M as fundamental constants (derived from the k-hierarchy)
- Quantum mechanical wavefunctions or probability amplitudes
- Dark matter or dark energy
- Wave-particle duality
- Fields as ontological primitives

All values are from **empirical measurement** (CODATA 2018, NIST, NUBASE2020). The distinction is between importing interpretive frameworks (prohibited) and using measured data in its measured units (required).

---

## Author

**James Christopher Tyndall**
Melbourne, Australia
April 2026

---

## License

All rights reserved. Contact author for permissions.
