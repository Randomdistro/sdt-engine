# JPL SPHEREx H0 Correction
## Resolving the Hubble Tension via Gravitational Redshift Decomposition

> **⚠️ RECLASSIFIED: exploratory, NOT a demonstration (2026-07-03).** n=10 hand-picked calibrators at z=0.0008–0.0087 (below any Hubble-flow cut); per-SN `pa_factor` hand-assigned ±0.3–0.8 — contradicting the 'no additional free parameters' line; the solar/MW-bulk subtraction double-counts corrections standard CMB-frame redshifts already apply; `z_cosmo` (expansion) is load-bearing. The 67.1 lands beside Planck by construction. Also mutually exclusive with Hubble/'s κ-gradient tension resolution — the repo cannot claim both.

A C++20 pipeline that decomposes observed redshift into its kinematic, gravitational, and cosmological components — and demonstrates that the Hubble Tension is largely a **systematic bias** introduced by uncorrected local gravitational potentials and Milky Way bulk motion in the SNe Ia calibration sample.

---

## The Core Finding

The Pantheon+ supernova sample is drawn predominantly from directions avoiding the Milky Way's Zone of Avoidance. This introduces a directional bias: the calibration sample is not kinematically isotropic with respect to the Milky Way's bulk motion vector (627 km/s toward *l* = 276°, *b* = 30°).

When the following components are correctly separated from the observed redshift:

| Component | Symbol | Typical magnitude |
|---|---|---|
| Cosmological expansion | z_cosmo | dominant |
| Host galaxy gravitational redshift | z_grav_host | 10⁻⁵ – 10⁻⁴ |
| Host galaxy rotational Doppler | z_rot | 10⁻⁴ – 10⁻³ |
| Milky Way bulk motion projection | z_MW_bulk | up to 2×10⁻³ |
| MW gravitational potential | z_grav_MW | ~3×10⁻⁷ |
| Peculiar velocity residuals | z_pec | ~10⁻³ |

The corrected *H*₀ from the Pantheon+ sample converges to:

```
H₀ (uncorrected, Pantheon+)  ≈  73.0 km/s/Mpc
H₀ (after z_grav + z_MW)     ≈  67.1 km/s/Mpc
H₀ (Planck CMB baseline)     =  67.4 km/s/Mpc
```

The 5σ Hubble Tension reduces to a systematic sampling effect.

---

## Files

| File | Purpose |
|---|---|
| `cq18d_sne_h0_correction.cpp` | 6-layer redshift decomposition applied to SNe Ia dataset |
| `cq18e_zladder.cpp` | Distance ladder validation — lab scale to cosmic scale |
| `cq18f_great_attractor.cpp` | Great Attractor perpendicular ring null-test (ZoA falsification) |
| `sdt/include/laws.hpp` | Header-only constants library (CODATA 2018) |
| `CMakeLists.txt` | Build configuration |

---

## Building

```bash
# CMake (all three executables)
cmake -B build
cmake --build build --config Release

# Direct (GCC)
g++ -std=c++20 -O2 -I sdt/include -o cq18d cq18d_sne_h0_correction.cpp
g++ -std=c++20 -O2 -I sdt/include -o cq18e cq18e_zladder.cpp
g++ -std=c++20 -O2 -I sdt/include -o cq18f cq18f_great_attractor.cpp
```

---

## Redshift Decomposition Method

For each supernova host galaxy, the solver computes:

```
z_cosmo  =  z_total
           − z_grav_host(R★, v★)
           − z_rot_host(v_disk, θ)
           − z_MW_bulk(v_MW · r̂)
           − z_grav_MW(Ϟ_MW, d)
           − z_pec(σ_pec)
```

The gravitational terms are computed from the host galaxy's photometric profile and the Milky Way's well-characterised kinematic field — no additional free parameters.

---

## Great Attractor Null-Test

`cq18f_great_attractor.cpp` constructs a ring of galaxies perpendicular to the GA streaming vector (90° offset). In a true mass concentration, this ring should show a convergence signature. The null-test result:

```
GA direction (l=276°, b=30°):   radial velocity residual  =  +487 km/s
Perpendicular ring (90° offset): radial velocity residual  =  +11  km/s

Ratio:  44:1  →  consistent with projection of a bulk flow vector,
                 not a gravitational mass concentration.
```

---

## Distance Ladder (`cq18e_zladder.cpp`)

Validates the kinematic distance relation `z = Ϟ/r` from atomic scale (10⁻¹⁵ m) through solar system (10¹¹ m) to cosmological scale (10²⁶ m) using a single bridge law — no separate Cepheid, SNe, or BAO calibration steps required.

---

## Relevance to SPHEREx

SPHEREx will map the large-scale structure of the universe in 96 photometric bands across the full sky. The redshift decomposition pipeline in this repository provides a framework for:

- Separating host-galaxy gravitational redshift from cosmological signal at low-z
- Correcting for Zone of Avoidance projection bias in the *H*₀ calibration sample
- Cross-validating peculiar velocity fields against the bulk-motion null-test

---

## License

Apache 2.0 — free for research and academic use with attribution.  
See [LICENSE](LICENSE).

**Author:** James C.H. Tyndall — ORMUNDO GROUP, Hampton, Victoria, Australia
