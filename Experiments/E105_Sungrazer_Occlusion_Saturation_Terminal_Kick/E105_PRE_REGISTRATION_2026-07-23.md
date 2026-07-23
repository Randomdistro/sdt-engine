# E105 — PRE-REGISTRATION (Method A, the strict front)
### Locked prediction, filed BEFORE touching the data. Priority-dated 2026-07-23.
*J. C. Harvey, Melbourne. Verified independently this date; passes the strict blade (Divergence + Pre-registration + Feasibility).*

## The blade check (all three hold)

**1. Divergence.** SDT modifies the infall acceleration by the occlusion-saturation factor
`g(r) = g_Newton(r)·G(x)`, `x = (R☉/r)²`, whereas Newton and GR have **G ≡ 1 exactly**. Different
measurable value for the same observable (terminal speed of a radial plunge).

**2. Pre-registration (unfitted — the number is DERIVED, zero free parameters).**
`G(x)` is not posited. The occlusion force tracks the solid angle the Sun actually subtends; the
inverse-square law is its point-source approximation. `G(x)` is the exact ratio of the two:
```
Ω_cap  = 2π(1 − √(1 − x))     true subtended solid angle of a sphere (sinθ = R/r)
Ω_disk = π x                  point-source (small-angle) approximation
G(x)   = Ω_cap / Ω_disk = 2(1 − √(1 − x)) / x
```
`G → 1` far out (cap = disk, recovers Newton), `G → 2` at contact (hemisphere vs disk). No knob.

**Locked predictions (integrating `g_N·G` along a radial plunge from infinity):**
| quantity | value (this derivation) | spec |
|---|---|---|
| terminal-speed excess at grazing (q → R☉) | **+6.69%** | +6.8% |
| Sun escape-class 617.6 km/s → | **658.9 km/s** | 659.9 |
| fraction of the extra kick delivered inside 1.5 R☉ | **79%** | ~80% |
| residual **shape** v_excess(r) | **follows G((R/r)²)** — flat beyond ~2 R☉, sharp rise inside | — |

**3. Feasibility.** Archival: SOHO/LASCO C2/C3 astrometry + Parker Solar Probe encounters. The
Kreutz sungrazer family provides hundreds of near-radial plunges to q ~ 1–2 R☉.

## The pre-committed test (thresholds fixed NOW, before the data)

Stack the terminal-velocity residual Δv(r)/v_Kepler(r) for sungrazers vs heliocentric distance r,
binned by perihelion q. **The discriminator is the SHAPE, not one number** — stochastic outgassing
cannot mimic a fixed universal G(x).

- **PASS (SDT):** the stacked residual follows **G((R☉/r)²)** — consistent with flat beyond 2 R☉,
  rising to +6–7% at grazing, with **≥70% of the excess inside 1.5 R☉** — and the residual is
  **universal** (same shape across comets, not comet-specific).
- **FAIL (Newton/GR):** residual consistent with **zero** (G ≡ 1) within errors after non-gravitational
  (outgassing/fragmentation) modelling; any excess is stochastic and comet-specific, not the fixed G(x).
- **Systematic to model out (the real work):** non-gravitational outgassing acceleration. The defence
  is **universality + shape** — outgassing is per-comet and stochastic; G(x) is one fixed curve for all.

## Provenance / honesty
- `G(x)` derivation: native occlusion geometry (Law III occlusion force ∝ subtended solid angle;
  the 1/r² law is the point-source limit). Independently re-derived and numerically confirmed 2026-07-23.
- No parameter was fitted to any comet. The +6.69% and 79% are pure integrals of the parameter-free G(x).
- Data not yet touched. This file is the priority-dated lock; the analysis pipeline runs against it.

## Next step (the actual shot)
Pull SOHO/LASCO Kreutz astrometry + Parker encounter kinematics into `Datasets/`, build the reproducible
Δv(r)/v_K residual-stacking pipeline, and test against the locked thresholds above. Method A verdict
line to follow on completion.

> **Blade status: PASS** — divergent (G(x) vs G≡1), pre-registered (parameter-free derivation, locked
> above), feasible (archival). E105 is the campaign spearhead.
