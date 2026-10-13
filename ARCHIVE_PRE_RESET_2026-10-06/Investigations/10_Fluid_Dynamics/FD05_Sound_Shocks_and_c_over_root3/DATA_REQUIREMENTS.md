# FD05 — Data Requirements

**Investigation**: FD05 — Sound, Shocks, and the c/√3 Ceiling
**Author**: James Christopher Tyndall, Melbourne

All external data here are **MEASURED-INPUT** (the medium's compressibility and shock observables, in their measured units). The SDT mechanism is native; these numbers are the **convergence targets** the relay-wave model must reproduce, never coefficients to be borrowed (R5). Predict-before-look (R1): commit the derived value to the run log before unsealing the measured one.

## 1. Equation-of-state inputs (set the sound speed)

| Quantity | Symbol | Value (representative) | Units | Use | Source |
|---|---|---|---|---|---|
| Heat-capacity ratio, dry air | `γ` | 1.4006 | – | air `c_s = √(γR_gT)` (Phase 1) | CODATA / NIST gas tables |
| Specific gas constant, dry air | `R_g` | 287.05 | J kg⁻¹ K⁻¹ | air `c_s` | NIST / ISA |
| Reference temperature | `T` | 293.15 (and 273.15) | K | air `c_s`, T-dependence | ISA standard atmosphere |
| Bulk modulus, water (20 °C) | `K` | 2.18×10⁹ | Pa | water `c_s = √(K/ρ)` (Phase 1) | NIST / engineering tables |
| Density, water (20 °C) | `ρ` | 998.2 | kg m⁻³ | water `c_s` | NIST |
| Radiation EoS ratio | `w = P/u` | 1/3 (exact) | – | c/√3 ceiling (Phase 2) | from `law_I::P_rad = u/3` — **DERIVED, not external** |

## 2. Sound-speed convergence targets (what the model must hit)

| Medium | `c_s` measured | Units | Tolerance | Notes |
|---|---|---|---|---|
| Dry air, 20 °C, 1 atm | 343.2 | m s⁻¹ | ±1% | primary Phase 1 target |
| Dry air, 0 °C | 331.3 | m s⁻¹ | ±1% | T-dependence check |
| Water, 20 °C | 1481 | m s⁻¹ | ±5% | liquid cross-check |
| Radiation fluid (relativistic limit) | `c/√3 = 1.7321×10⁸` | m s⁻¹ | 4 sig figs | Phase 2 ceiling; matches CR04 BAO `c_s` |

## 3. Shock / Mach observables

| Quantity | Value (representative) | Units | Use | Source |
|---|---|---|---|---|
| Mean free path, air at STP | λ ≈ 68 | nm | shock thickness `δ ∼ 3–5 λ` (Phase 4) | kinetic theory / NIST |
| Measured shock-front width, air | ∼ 200 (few × λ) | nm | order-of-magnitude check (Phase 4) | weak-shock interferometry literature |
| Mach-angle data | `sinθ = 1/M`, `M = 1.2 … 10` | – | Mach-cone relation (Phase 4) | standard compressible-flow tables |
| E57 Cherenkov angle (water, β→1) | `cosθ_C = 1/(nβ)`, ~41° max | deg | unification cross-check (Phase 5) | **internal — Investigations/E57 (VERIFIED)** |

## 4. Internal (SDT) inputs — not external

- `c`, `ℓ_P`, `u_CMB`, `P_rad = u_CMB/3.0`, `P_conv` — from `Engine/include/sdt/laws.hpp` (`sdt::laws::law_I`). dependency-traced primitives + derived; **not** datasets.
- `c_s = c/√3` coupled-lattice / BAO sound speed — from **CR04** (internal result, re-derived here).
- Cherenkov shock criterion — from **E57** (internal, VERIFIED).

## 5. Acquisition notes

- Gas/liquid EoS values are textbook-stable; hard-code with citation in the MEASURED-INPUT block of `fd05_sound_shocks.cpp`. No live dataset fetch required.
- Mean-free-path and shock-width figures are order-of-magnitude checks only; a single representative value per medium suffices for the D/C-level shock-thickness test.
- If a fuller `c_s(T)` sweep is wanted, NIST gas tables (or the ISA model) supply air sound speed vs altitude/temperature for an extended Phase 3 overlay — optional, not required to land the verdict.
