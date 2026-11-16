# FD09 — Drag as an Occlusion Cross-Section — Data Requirements

All values below enter as **MEASURED-INPUT in measured units** (legitimate, like spectral lines): they are
comparison targets for the convergence check, never fitted free parameters and never inputs to the derivation.
The *mechanism* remains SDT-native (Law III occlusion). Tag every use DERIVED / MEASURED-INPUT / CALIBRATED(n)
(R2). Target CALIBRATED ≤ 1. Predict every number and commit it to the run log *before* loading these data (R1).

## 1. The Sphere Drag-Coefficient Curve (primary target)

The single load-bearing dataset: the standard smooth-sphere `C_D` vs `Re` curve spanning **Re ∈ 10⁻¹ … 10⁶**,
including the drag-crisis region.

| Data Point | Source | Purpose |
|-----------|--------|---------|
| `C_D(Re)` for a smooth sphere, `Re ∈ 10⁻¹–10⁶` (digitised curve) | Schlichting, *Boundary-Layer Theory*; NASA Glenn / standard FD texts | Primary convergence target for the full FD09 `C_D(Re)` model |
| Stokes regime `C_D = 24/Re`, `Re ≲ 1` (analytic) | Stokes law (closed form) | Phase-2 `6π` prefactor check |
| Sub-critical plateau `C_D ≈ 0.44–0.5`, `Re ≈ 10³–2×10⁵` | Schlichting / sphere-drag tables | Phase-3 form-drag order-of-magnitude check |
| Drag-crisis location `Re_crit ≈ 3×10⁵` (smooth sphere) | Schlichting / Achenbach (1972) sphere-drag measurements | Phase-4 crisis-location prediction target |
| Post-crisis minimum `C_D ≈ 0.07–0.1` | Achenbach (1972); standard FD texts | Phase-4 post-crisis `C_D` magnitude target |
| Intermediate-Re empirical correlations (e.g. Schiller–Naumann `C_D=24/Re(1+0.15Re^0.687)`, Clift–Gauvin) | Standard particle-drag references | Smooth blend check between Stokes and form regimes |

Provide as a digitised `Re, C_D` table (CSV) with the source and digitisation method noted. A handful of
well-spaced points per decade across all 7 decades, with extra density through the crisis (`Re ≈ 10⁵–10⁶`).

## 2. Reference Fluid Properties (for Re, Stokes, terminal velocity)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Kinematic/dynamic viscosity ν, μ of water at 20 °C (ν=1.004×10⁻⁶ m²/s) | NIST / IAPWS-IF97 | `Re` and Stokes-regime drag; terminal-velocity cases |
| Kinematic/dynamic viscosity ν, μ of air at 20 °C (ν=1.516×10⁻⁵ m²/s) | NIST / Sutherland | Second-fluid `Re`; droplet/sphere terminal velocity in air |
| Density ρ of water and air at 20 °C, 1 atm | NIST | Dynamic pressure `q=½ρv²`; `Re`; weight balance |
| Density of test-sphere materials (e.g. steel 7850, glass 2500 kg/m³) | Standard material tables | Terminal-velocity weight (mass = ρ_body·V) |

## 3. Terminal-Velocity Benchmarks (end-to-end check, Phase 5)

| Data Point | Source | Purpose |
|-----------|--------|---------|
| Measured terminal velocity of a falling sphere (steel/glass in water, e.g. falling-ball viscometer) | Standard fluids / viscometry references | Phase-5 `v_t` comparison, Stokes regime |
| Terminal velocity of a water droplet / sphere in air (e.g. raindrop terminal-velocity tables) | Gunn & Kinzer (1949); meteorology references | Phase-5 `v_t` comparison, form regime |

## 4. Engine-Internal Constants (NOT external — listed for traceability)

| Quantity | Source | Note |
|----------|--------|------|
| `law_III::solid_angle_occluded` (`πR²/r²`) | `Engine/include/sdt/laws.hpp` | The native shadow cross-section — drag mechanism |
| `law_III::F_occlusion` (`F=(π/4)P_eff R₁²R₂²/r²`) | `Engine/include/sdt/laws.hpp` | Universal occlusion force law (structural template) |
| `law_I::P_conv ≈ 2.46×10⁴⁸ Pa` | `law_I::P_conv` | Ambient convergence pressure (front/wake imbalance baseline) |
| `g = v_surf²/R_body`, `koppa = v²R/c²` | `law_V` / `bridge::koppa` | Terminal-velocity weight without G or M |
| `ν` (viscosity) | **FD02** (upstream) | Enters `Re` and the Stokes-regime drag |
| boundary-layer transition / wake angle | **FD06** (upstream) | Sets `C_D` plateau and the drag crisis |

## Notes
- No proprietary or restricted datasets are required; all items are standard reference values, closed-form
  analytic results, or published sphere-drag measurements.
- The `C_D(Re)` curve (incl. the crisis) and the terminal velocities are *targets to reproduce*, never inputs
  to the derivation (R5: never import a result as a borrowed target).
- If the Phase-5 balance forces more than one fitted scale (beyond a single wake-angle/efficiency constant), the
  result is capped at Class C and the extra calibration must be documented explicitly in `FD09_VERDICT.md`.
