# E24: Mercury Precession from k-Hierarchy — Data Requirements

## Measured Orbital Parameters
| Quantity | Value | Source |
|----------|-------|--------|
| Mercury semi-major axis a | 5.7909 × 10¹⁰ m | JPL Horizons |
| Mercury eccentricity e | 0.2056 | JPL |
| Mercury orbital period T | 87.969 d | JPL |
| Mercury perihelion distance | 4.600 × 10¹⁰ m | Computed |
| Mercury aphelion distance | 6.982 × 10¹⁰ m | Computed |
| Measured anomalous precession | 42.98 ± 0.04 "/century | Will (2014) |

## SDT Parameters
| Quantity | Value | Source |
|----------|-------|--------|
| k_Sun | 686.3 | bridge namespace in laws.hpp |
| R_Sun | 6.957 × 10⁸ m | laws.hpp |
| ϟ_Sun (c-boundary) | R_Sun / k² ≈ 1477 m | laws.hpp |
| v_orbital(r) | (c/k)√(R/r) | bridge::v_orbital |
| GM_equiv | c²R/k² | bridge::GM_equivalent |

## Required Derivation Steps
1. Express orbital velocity as function of r using SDT k-gradient
2. Compute radial gradient of v(r) → effective potential
3. Derive precession rate from mismatch between radial and angular periods
4. The precession arises because v(r) ≠ pure 1/r² at small r — the k-gradient introduces a correction term
5. Compare to GR prediction: δφ = 6πGM/(c²a(1−e²))
