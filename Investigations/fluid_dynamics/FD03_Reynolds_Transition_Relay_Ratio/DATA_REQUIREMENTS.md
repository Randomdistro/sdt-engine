# FD03 — The Reynolds Transition as a Lattice Relay Ratio — Data Requirements

All values below enter as **MEASURED-INPUT in measured units** (legitimate, like spectral lines): they are the
*convergence targets* for the transition-threshold prediction, never fitted free parameters. The transition
*mechanism* (the relay-rate ratio) remains SDT-native. Every predicted `Re_crit` must be committed to the run
log **before** comparison (R1). Tag every use DERIVED / MEASURED-INPUT / CALIBRATED(n) (R2). Target CALIBRATED ≤ 1.

## 1. Pipe-Flow Transition Reynolds Number (primary target, Phase 2)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Critical pipe `Re_crit ≈ 2300` (onset of transition) | Reynolds, O. (1883), *Phil. Trans. R. Soc.* 174:935 | Primary convergence target for Phase-2 `Re_crit = G` |
| Transition band `Re ≈ 2000–4000` (lower critical to fully turbulent) | White, *Viscous Fluid Flow* 3rd ed.; Schlichting & Gersten, *Boundary-Layer Theory* | Band the prediction must land inside for Class A |
| Modern delayed-transition pipe results (`Re` up to ~10⁴ with controlled inlets) | Avila et al. (2011) *Science* 333:192; Eckhardt et al. (2007) *Annu. Rev. Fluid Mech.* 39:447 | Context: transition is a finite-amplitude threshold, not a single linear-instability point (sanity, not a refit target) |

## 2. Flat-Plate (Boundary-Layer) Transition (geometry test, Phase 3)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Flat-plate transition `Re_x ≈ 5×10⁵` (smooth plate, low free-stream turbulence) | Schlichting & Gersten, *Boundary-Layer Theory* 8th ed. | Geometry-dependence test: same `ν`, open geometry, larger threshold |
| Transition `Re_x` range `3×10⁵–3×10⁶` (depending on free-stream turbulence/roughness) | White, *Viscous Fluid Flow*; standard aerodynamics references | Band for the flat-plate prediction; shows geometry/disturbance sensitivity |

## 3. Taylor–Couette Onset (geometry test, Phase 3)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Critical Taylor number `Ta_crit ≈ 1708` (narrow-gap, inner-cylinder rotation) | Taylor, G.I. (1923) *Phil. Trans. R. Soc. A* 223:289; Chandrasekhar, *Hydrodynamic and Hydromagnetic Stability* | Third geometry: maps to a critical onset the same coherence criterion must reproduce |
| Critical `Re` for Taylor-vortex onset (gap-based) | Drazin & Reid, *Hydrodynamic Stability* | Cross-check of the Couette onset in `Re` units |

## 4. Engine-Internal Constants (NOT external — listed for traceability)

| Quantity | Source | Note |
|----------|--------|------|
| ℓ_P, t_P, c = ℓ_P/t_P | `sdt::laws::measured` / `law_I` | Relay scale, tick, signal speed — whitelist inputs |
| P_conv ≈ 2.46×10⁴⁸ Pa | `law_I::P_conv` | Driving / occlusion pressure (no attraction) |
| Movement-budget cap v_circ²+v²=c² | `law_V` | `U/c < 1` bound on advective transport |
| Kinematic viscosity ν = (coefficient)·ℓ_P·c | **FD02** (upstream) | The relay-smoothing diffusivity; referenced, never refit in FD03 |
| Dominant-mode / coherence geometry `ℓ_c`, `2D` neighbour count | `law_VI::traction`, `law_VI::confinement` / FD01 | Source of the geometric factor `G` in `Re_crit = G` |

## Notes
- No proprietary or restricted datasets are required; all items are published transition measurements or standard
  stability-theory reference values.
- The measured `Re_crit ≈ 2300`, `Re_x ≈ 5×10⁵`, and `Ta_crit ≈ 1708` are used **only** as targets to reproduce,
  never as inputs to the derivation (R5: never import a result as a borrowed target, and never insert an integer
  or π to force `2300`).
- The geometric threshold `G` must be derived from the dominant-mode coherence calculation; if it cannot be
  derived without fitting, flag it PENDING and cap the verdict at Class D.
- If the threshold calculation forces more than one fitted scale, the result is capped at Class C and the extra
  calibration must be documented explicitly in `FD03_VERDICT.md`.
