# FD09 — Verdict: Drag as an Occlusion Cross-Section

**Classification: CLASS C (QUALIFIED — convergence).**
**Author**: James Christopher Tyndall, Melbourne · Tool: `fd09_drag_occlusion.cpp` (MSVC `/utf-8 /std:c++20`, ran clean).

## Deciding metric
Drag is the engine's **own** Law III occlusion mechanism applied to a flowing medium: the
body occludes the convergent momentum flux across its shadow cross-section `A = πR²` (the
engine's `solid_angle_occluded(R,1m)` returns exactly `πR²`), and the net front-minus-wake
flux is the force `F_D = C_D·½ρv²·A`. This **form** and the low-Re `μRv` Stokes **scaling**
(relay diffusion around the body) are **NATIVE**. The Stokes prefactor `6π` (= full
Stokes-flow solution, 4π skin + 2π form) and the `C_D(Re)` curve incl. the drag crisis are
**reproduced correlations**, not SDT-derived — hence Class C.

## Numbers (from the run)
- Stokes identity: `F(6πμRv) = F(C_D=24/Re)` to ratio 1.0000000000; prefactor 18.8496 = 6π (0.00% dev).
- `C_D(Re)` composite reproduces Stokes (24/Re), the ~0.46 plateau (10³–10⁵), and the drag crisis (min `C_D=0.125` at `Re=5.6×10⁵`, within 2× of 3×10⁵; post-crisis in [0.07,0.15]).
- Terminal velocities (weight via SDT `g=v²/R`, **no G/M**): 3 mm water drop in air **8.64 m/s** vs Gunn–Kinzer 8.0–8.1; 1 mm drop **3.97 m/s** vs 4.0–4.5. Order-correct; the drop overshoots slightly (rigid-sphere `C_D`, no deformation).

## Provenance × correspondence
- **provenance**: SDT-derived (occlusion form + μRv scaling); external (6π, the curve).
- **correspondence**: known-match (Stokes, the standard `C_D(Re)` curve, the drag crisis tied to the FD06 boundary-layer transition shrinking the occluded wake).

## Parameter ledger (R2)
`c, ℓ_P`, `law_III::solid_angle_occluded`, `law_I::P_conv` WHITELIST/DERIVED · `C_D·½ρv²·A` form & `μRv` scaling DERIVED · `6π` prefactor CORRELATION · `C_D(Re)` curve + crisis (Schlichting/Achenbach) MEASURED-INPUT · wake-shrink/crisis-shape scale CALIBRATED(1). No G/M anywhere.

## Open (path to Class A)
Derive the `6π` prefactor and the wake-occlusion `C_D(Re)` shape from the relay/occlusion flow field around a sphere (couples to FD01 + FD06) rather than importing the empirical curve. **Sign-off: PASS, Class C.**
