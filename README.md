# SDT Engine — Kinematic Observatory Pipeline
## Parameter-Free Orbital & Redshift Solvers (No G, No M)

> **One observable. One constant. One closure condition.**  
> `zk² = 1`  — where `z = v²/c²` and `k = c/v`

---

## What This Is

A **C++20 computational engine** that characterises orbital systems, exoplanetary architectures, and cosmological redshift using **zero free parameters** — no gravitational constant G, no stellar mass M, no dark matter.

Every quantity is derived strictly from:

| Input | Symbol | Source |
|-------|--------|--------|
| Orbital period | T | Transit photometry / timing |
| Orbital radius | r | Parallax / geometry |
| Speed of light | c | SI exact |

The bridge law `Ϟ = v²r/c²` encodes the entire gravitational field of any body as a single kinematic constant in metres. From this one number, the full orbital architecture follows without further assumptions.

---

## The Bridge Law

For any orbit at radius `r` with velocity `v`:

```
Ϟ  =  v² · r / c²          [units: metres]
```

This is the **geometric c-boundary** (koppa) of the central body. It:
- Equals `GM/c²` as a derived consequence — G is never an input
- Is **the same** for every planet in the system (self-calibration test)
- Encodes local surface gravity: `g = c²Ϟ/r²`
- Predicts orbital velocity at any radius: `v(r) = c √(Ϟ/r)`

The closure condition `zk² = 1` (where `z = Ϟ/r`, `k = c/v`) is verified for every orbit as a consistency check.

---

## Solver Modules

### CQ18a — Solar System Calibration
**File:** `Investigations/CQ18_Redshift_Decomposition/cq18a_solar_zdecomp.cpp`

Derives `Ϟ_Sun` from each planet's orbital period and semi-major axis. All 8 planets converge to the same `Ϟ_Sun = 1477.0 m` to < 0.001%. No G, no M_Sun.

```
Ϟ_Sun = v_Earth² × AU / c² = 1477.046 m
```

### CQ18b — Multi-Planet System Solver (Exoplanets)
**File:** `Investigations/CQ18_Redshift_Decomposition/cq18b_multiplanet_zdecomp.cpp`

Applied to **TRAPPIST-1** and **Kepler-90**: derives the host star's Ϟ from transit timing alone, then predicts all planetary orbital radii. Self-calibration: every planet must return the same Ϟ_host.

**TRAPPIST-1 result:** `Ϟ_host = 1.53 m` (0.00104% of Ϟ_Sun, consistent with stellar mass ratio)  
**All 7 TRAPPIST planets** close to `zk² = 1` within 0.05%

### CQ18c — AGN / High-z Redshift Decomposition
**File:** `Investigations/CQ18_Redshift_Decomposition/cq18c_agn_zdecomp.cpp`

Decomposes quasar redshift into kinematic + gravitational + cosmological components without FRW metric assumptions.

### CQ18d — SNe Ia H₀ Correction
**File:** `Investigations/CQ18_Redshift_Decomposition/cq18d_sne_h0_correction.cpp`

Applies a **6-layer redshift decomposition** to the Pantheon+ SNe Ia dataset:

```
z_total = z_cosmo + z_grav_host + z_rot_host + z_MW_bulk + z_grav_MW + z_peculiar
```

When host galaxy gravitational redshift and Milky Way bulk motion (627 km/s toward the Great Attractor) are correctly subtracted from the SNe Ia calibration sample:

| Correction | H₀ |
|---|---|
| Uncorrected (Pantheon+) | ~73 km/s/Mpc |
| After z_grav + z_MW subtraction | ~67 km/s/Mpc |
| Planck CMB baseline | 67.4 km/s/Mpc |

**The Hubble Tension dissolves as a Zone of Avoidance sampling bias.**

### CQ18e — Redshift Distance Ladder
**File:** `Investigations/CQ18_Redshift_Decomposition/cq18e_zladder.cpp`

Validates the kinematic distance ladder from lab scale (10⁻¹⁵ m) to cosmic scale (10²⁶ m) using a single `z = 1/k²` bridge law. No separate Cepheid, SNe, or BAO calibrations needed.

### CQ18f — Great Attractor Falsification
**File:** `Investigations/CQ18_Redshift_Decomposition/cq18f_great_attractor.cpp`

Demonstrates that the Great Attractor streaming signal is a **lenticular projection phantom** of the Zone of Avoidance bulk-motion vector — not a gravitational mass concentration. The perpendicular ring null-test shows zero convergence signature at 90° from the GA vector.

---

## Building

### Requirements
- C++20 compiler (GCC 12+, MSVC 2022, Clang 15+)
- CMake 3.20+

### Compile individual solvers (GCC / MSYS2)
```bash
cd Investigations/CQ18_Redshift_Decomposition

# Solar system calibration
g++ -std=c++20 -O2 -I../../Engine/include -o cq18a.exe cq18a_solar_zdecomp.cpp
./cq18a.exe

# Multi-planet exoplanet solver (TRAPPIST-1, Kepler-90)
g++ -std=c++20 -O2 -I../../Engine/include -o cq18b.exe cq18b_multiplanet_zdecomp.cpp
./cq18b.exe

# H0 tension / SNe Ia decomposition
g++ -std=c++20 -O2 -I../../Engine/include -o cq18d.exe cq18d_sne_h0_correction.cpp
./cq18d.exe

# Great Attractor falsification
g++ -std=c++20 -O2 -I../../Engine/include -o cq18f.exe cq18f_great_attractor.cpp
./cq18f.exe
```

### Compile via CMake (all solvers)
```bash
cmake -B build
cmake --build build --config Release
```

---

## Key Validation Results

| System | Ϟ derived | Method | Error |
|--------|-----------|--------|-------|
| Sun (from Earth orbit) | 1477.046 m | T, AU, c only | — |
| Sun (from Mercury) | 1477.051 m | T, r, c only | 0.003% |
| Sun (from Neptune) | 1477.039 m | T, r, c only | 0.005% |
| TRAPPIST-1 (7 planets) | 1.530 m | Transit timing | 0.05% avg |
| Earth surface gravity | 9.8069 m/s² | Moon timing + R_Earth | 0.003% |
| H₀ (corrected) | 67.1 km/s/Mpc | SNe Ia + z_grav subtraction | 0.4% vs Planck |

---

## Prohibitions (by design)

This codebase **never imports**:

- `G` (gravitational constant) — derived consequence: `G = c² Ϟ / M`, where M comes from baryon count
- Stellar mass M as a prior — mass is derived from Ϟ, not assumed
- Dark matter or dark energy
- FRW metric expansion or curvature parameters
- Radial velocity priors for orbital mass estimation

All constants used are from **CODATA 2018** measurement: `c`, `ℏ`, `ℓ_P`, `m_p`, `α`.

---

## Repository Layout (relevant to this release)

```
sdt-engine/
├── Engine/include/sdt/
│   └── laws.hpp                 Single source of truth (all SDT constants)
│
├── Investigations/CQ18_Redshift_Decomposition/
│   ├── cq18a_solar_zdecomp.cpp  Solar system Ϟ calibration
│   ├── cq18b_multiplanet_zdecomp.cpp  Exoplanet orbital solver
│   ├── cq18c_agn_zdecomp.cpp    AGN / high-z decomposition
│   ├── cq18d_sne_h0_correction.cpp    SNe Ia H₀ correction
│   ├── cq18e_zladder.cpp        Distance ladder (lab → cosmic)
│   ├── cq18f_great_attractor.cpp  GA falsification
│   └── star_data.hpp            Stellar catalogue data
│
└── Theory/
    └── 00_Ruleset.md            Formal axioms and derivation rules
```

---

## Author

**James Christopher Tyndall**  
Director, ORMUNDO GROUP  
Hampton, Victoria, Australia  
May 2026

---

## License

All rights reserved — ORMUNDO GROUP 2026.  
Contact author for research collaboration or licensing enquiries.
