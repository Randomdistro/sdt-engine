# FD02 — Data Requirements

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

All entries below are **MEASURED-INPUT** (measured observables in measured units) or **CONVERGENCE TARGET** (a standard-FD result to *reproduce*, never to *borrow* as a derivation input). Whitelist primitives `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` are already in `Engine/include/sdt/laws.hpp::measured` and are **not** re-listed here. Anything not on this list or in the engine whitelist must not enter the derivation.

---

## A. Constants (from the engine, no external fetch)

| Symbol | Quantity | Source | Role |
|---|---|---|---|
| `ℏ`, `h = 2πℏ` | reduced / Planck constant | `laws.hpp::measured` | Circulation quantum `κ = h/m`; floor `ħ/m`, `ħ/(4π k_B)` |
| `k_B` | Boltzmann constant | `laws.hpp::measured` | Thermal relay speed `√(k_B T/m)`; `η/s` floor |
| `c`, `ℓ_P`, `t_P` | signal speed, Planck length/time | `laws.hpp::measured` | Relay bound `v_relay ≤ c`; lattice scale |

---

## B. Measured inputs (external — required for evaluation)

| Symbol | Quantity | Value (target) | Units | Source | Used in |
|---|---|---|---|---|---|
| `m_He` | mass of ⁴He atom | 6.6446573×10⁻²⁷ | kg | CODATA / AME2020 | Phase 4: `κ = h/m_He` |
| `λ_mfp,air` | mean free path, air at STP | ≈ 6.8×10⁻⁸ | m | standard kinetic-theory tables | Phase 1–2: `ν = ⅓ λ_mfp v_relay` |
| `v̄_air` | mean molecular speed, air ~20 °C | ≈ 4.6×10² | m·s⁻¹ | kinetic theory (√(8k_BT/πm)) | Phase 2 |
| `ρ_air`, `ρ_water` | densities at ~20 °C | 1.20 / 998 | kg·m⁻³ | standard reference | Phase 1: `μ = ρν` cross-check |
| `λ_mfp,water`, `v_water` scales | momentum scattering length & speed in water | order-of-magnitude | m, m·s⁻¹ | liquid-state references | Phase 2 (order-of-magnitude only) |

---

## C. Convergence targets (reproduce, do NOT use as derivation inputs)

| Symbol | Quantity | Value | Units | Source | Phase |
|---|---|---|---|---|---|
| `ν_air` | kinematic viscosity of air, ~20 °C | ≈ 1.5×10⁻⁵ | m²·s⁻¹ | NIST / engineering tables | 2 (factor ≲ 10) |
| `ν_water` | kinematic viscosity of water, ~20 °C | ≈ 1.0×10⁻⁶ | m²·s⁻¹ | NIST / IAPWS | 2 (factor ≲ 10) |
| `ν(T)` curve | air kinematic viscosity vs T | tabulated 200–400 K | m²·s⁻¹ vs K | NIST / engineering tables | 3 (slope fit) |
| B16 exponent | transport-law temperature exponent | 0.5 | dimensionless | B16 benchmark (in-repo) | 3 (<1% match) |
| `κ_He` | superfluid ⁴He circulation quantum | ≈ 9.97×10⁻⁸ | m²·s⁻¹ | Vinen / measured `h/m_He` | 4 (<1%) |
| `(η/s)_KSS` | Kovtun–Son–Starinets bound | `ħ/(4π k_B)` ≈ 6.1×10⁻¹³ | K·s (in `ħ/k_B` units) | KSS bound; QGP `≈ ħ/(4π k_B)` regime | 5 (within factor 4π) |

---

## D. Datasets to obtain

1. **Air kinematic viscosity vs temperature** — a tabulated `ν(T)` over at least 200–400 K (≥ 8 points) for the Phase-3 log-log exponent fit. Source: NIST Chemistry WebBook or a standard thermophysical-properties table. Store as CSV `ν_air_vs_T.csv` (columns: `T_K, nu_m2_s`).
2. **⁴He superfluid circulation quantum** — single measured value with uncertainty for the Phase-4 comparison (and the atomic mass `m_He` from AME2020/CODATA).
3. **KSS / QGP `η/s` benchmark** — the analytic bound `ħ/(4π k_B)` plus a representative measured low-`η/s` system value, used as a one-sided convergence check only (no QGP physics imported).

If a dataset is unavailable at run time, the corresponding phase reports **PENDING** (Class D) for that metric rather than fabricating a value (R1 honesty; mark gaps OPEN).

---

## E. Provenance notes

- `m_He`, `ρ`, `λ_mfp`, `v̄` are MEASURED-INPUT tools — legitimate because the **mechanism** (`ν = ⅓ λ_mfp v_relay`, `κ = h/m`) is SDT-native; only the numerical scales are measured.
- `ν_air`, `ν_water`, the `ν(T)` slope, `κ_He`, and the KSS bound are CONVERGENCE TARGETS: the investigation passes by *reproducing* them, and must never feed them back in as derivation inputs (that would be circular — flagged in the parameter ledger, R2).
- No `G`, `M(kg)`, `GM`, magnetons, or QM wavefunctions appear anywhere in the input set, per §0.
