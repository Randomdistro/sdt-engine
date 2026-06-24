# FD04: The Kolmogorov −5/3 Cascade as the Displacement Cascade — Data Requirements

*All datasets below are CONVERGENCE TARGETS — measured spectra that SDT must reproduce, never inputs to borrow. The `−5/3` slope and the Kolmogorov microscale are what FD04 derives natively and then checks against these. Measured fluid properties (`ν`, `ε`, `L`, `Re`) are legitimate measured inputs in their measured units; the cascade MECHANISM must be SDT-native.*

## Primary turbulence-spectrum datasets (the −5/3 falsifier)
| Source | Content | Why it matters |
|--------|---------|----------------|
| Grant, Stewart & Moilliet (1962), *J. Fluid Mech.* — Discovery Passage tidal channel | One-dimensional velocity spectra over ~3 decades of `k`; the classic field confirmation of `−5/3` at very high `Re` | Cleanest extended inertial range; canonical slope check |
| Saddoughi & Veeravalli (1994), *J. Fluid Mech.* — NASA Ames 80×120 ft wind tunnel boundary layer | High-`Re` boundary-layer streamwise/transverse spectra; local isotropy at small scales | Wind-tunnel/atmospheric crossover; tests isotropy assumption |
| Comte-Bellot & Corrsin (1971), *J. Fluid Mech.* — grid turbulence | Decaying grid-turbulence energy spectra `E(k)` at successive downstream stations | Canonical *grid-turbulence* spectrum; widely used DNS/LES benchmark |
| Kaimal et al. (1972), *Q. J. R. Meteorol. Soc.* — Kansas atmospheric surface-layer | Atmospheric boundary-layer spectra `S(f)` for `u, v, w, T` vs frequency | Atmospheric `−5/3` over real geophysical scales |
| Champagne (1978) / Sreenivasan (1995) compilations | Cross-experiment compilation of the Kolmogorov constant `C_K` | Source for the measured `C_K ≈ 1.5 ± 0.1` target |

## Per-dataset required quantities
| Quantity | Symbol | Source |
|----------|--------|--------|
| 1-D (or 3-D) energy spectrum | `E(k)` or `E₁₁(k₁)`, `S(f)` | Spectrum table/figure of each dataset |
| Wavenumber / frequency grid | `k`, `f` | Same; convert `f → k` via Taylor frozen-turbulence `k = 2πf/U` |
| Mean advection speed (for Taylor hypothesis) | `U` | Reported flow conditions |
| Dissipation rate | `ε` | Reported, or inferred from integral-scale forcing — NOT fitted to the spectrum |
| Kinematic viscosity at stated T | `ν` | Fluid tables (water/air) at the dataset temperature — measured input |
| Integral scale | `L` | Reported or from spectrum low-`k` knee |
| Taylor / Reynolds number | `Re_λ`, `Re` | Reported |
| Reported Kolmogorov microscale | `η` | Reported, for Phase-3 cross-check |

## SDT-derived quantities to compare against the data
| Quantity | Formula | Source |
|----------|---------|--------|
| Eddy velocity law | `u_ℓ = (ε ℓ)^{1/3}` | FD04 §3 (constant-flux displacement cascade) |
| Inertial-range spectrum | `E(k) = C_K ε^{2/3} k^{−5/3}` | FD04 §3 Step B (dimensional closure on `{ε,k}`) |
| Dissipation microscale | `η = (ν³/ε)^{1/4}`, `u_η = (νε)^{1/4}`, `t_η = (ν/ε)^{1/2}` | FD04 §3 Step C |
| Inertial-range width | `L/η ∝ Re^{3/4}` | FD04 §3 / Phase 3 |
| Kinematic viscosity | `ν = (geom)·ℓ_P·c`, `ν ∝ √T` | FD02 (referenced), B16 (engine) |
| Spation floor | `η ≥ ℓ_P` in the deep limit `ν → ν_lattice ∼ ℓ_P·c` | FD04 Phase 3 |

## Notes on use
- Convert frequency spectra to wavenumber via Taylor's frozen-turbulence hypothesis (`k = 2πf/U`); record `U` so the conversion is auditable.
- Fit the slope over the **inertial band only** — exclude the energy-injection knee (`k ∼ 1/L`) and the dissipation roll-off (`k ∼ 1/η`).
- `ε` must come from each experiment's reported forcing/dissipation, never from fitting the spectrum to `−5/3` (that would be circular — R5 anti-numerology).
- The Kolmogorov constant `C_K ≈ 1.5` is the target for the *prefactor*; FD04 derives the *exponent* first and treats `C_K` as COMPUTED/PENDING until derived from a lattice shell count.
