# FD06 — Data Requirements

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

External data is used **only** as the convergence target / falsifier in Phases 2–5. None of it enters the derivation as a tunable input. The mechanism is SDT-native (PPT06 traction + FD01 relay); measured fluid properties are legitimate *measured-in-measured-units* inputs (whitelist §0). The Blasius numbers themselves are analytic and require no dataset — they are reproduced, never borrowed.

## A. Analytic reference values (no dataset — exact targets)

These are computed from the Blasius flat-plate similarity solution and serve as the primary convergence targets. List them in the run log *before* comparing (R1).

| Quantity | Target value | Use |
|---|---|---|
| 99% thickness | `δ/x = 5.0/√Re_x` (`C_δ ≈ 5.0`) | Phase 2 (F2) |
| Displacement thickness | `δ* = 1.721√(νx/U)` | Phase 4 |
| Momentum thickness | `θ = 0.664√(νx/U)` | Phase 4 |
| Shape factor | `H = δ*/θ ≈ 2.59` | Phase 4 (F4) |
| Local skin friction | `C_f = 0.664/√Re_x` | Phase 3 (F3) |
| Plate drag (length L) | `C_D = 1.328/√Re_L` | Phase 3 |
| Wall-gradient constant | `f''(0) ≈ 0.332` | Phase 3 profile check |

## B. Measured fluid properties (whitelist inputs, measured units)

Needed for the Phase-5 dimensional benchmark (turning a dimensionless prediction into a metre/Pascal). At most ONE of these may be used as the single permitted scale; if so, tag CALIBRATED(1).

| Quantity | Source | Notes |
|---|---|---|
| Kinematic viscosity `ν` of air / water at stated `T` | **Preferred: handed from FD02** (lattice-derived `ν = coeff·ℓ_P·c`). Fallback: NIST / CODATA tabulated `ν(T)` | Air `ν ≈ 1.5×10⁻⁵ m²/s` @ 20 °C; water `ν ≈ 1.0×10⁻⁶ m²/s` @ 20 °C |
| Density `ρ` at stated `T` | NIST tabulated; or Law IV `V_disp`-load | For `μ = ρν` and `C_f = τ_w/(½ρU²)` |
| Reference `(U, x, L)` | Chosen flow condition (stated in run log) | Any sub-transition `Re_x` (e.g. `Re_x ~ 10⁴–10⁵`) |

## C. Validation benchmark (optional — strengthens C5)

A published laminar flat-plate boundary-layer measurement or DNS for an independent cross-check of `δ(x)` and `C_f(Re_x)`:

| Dataset | Provides | Acquisition |
|---|---|---|
| Classical flat-plate experiments (e.g. tabulated in Schlichting, *Boundary-Layer Theory*) | `δ(x)`, `C_f(Re_x)`, transition `Re_x` | Textbook tables; transcribe the few points needed |
| Public laminar flat-plate DNS / CFD verification cases (e.g. NASA Turbulence Modeling Resource flat-plate) | High-`Re` `C_f(Re_x)`, profiles | Web; cite source + access date in `fd06_results.txt` |
| Canonical transition Reynolds number | `Re_x,crit ≈ 3×10⁵ – 5×10⁵` | Order-of-magnitude check only (Phase 5); NOT a tuned match |

## Provenance discipline

- Every external number gets a certification label (OBSERVED / MEASURED-INPUT) and a citation with access date in `fd06_results.txt`.
- The Blasius constants (`5.0`, `0.664`, `1.328`, `2.59`) are **convergence targets**, classified OBSERVED-as-target — the derivation must *produce* them; finding them coded as inputs to the lattice rule is a contamination failure.
- Calibration budget: **≤ 1** fitted scale total (the fluid `ν`/`ρ` pairing), tagged CALIBRATED(1) and documented; a derived FD02 `ν` keeps the budget at CALIBRATED(0) and is the path to Class A.
