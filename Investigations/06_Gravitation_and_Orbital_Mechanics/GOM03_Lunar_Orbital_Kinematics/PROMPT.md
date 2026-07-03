# GOM03: Lunar Orbital Kinematics from Pendulum Acceleration

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. Concept

A precision pendulum measures raw acceleration `a(t)` at a known latitude on
Earth's surface. The Moon's occlusion field (SDT Law III) modulates this
acceleration with a well-defined geometric signature. By inverting the
acceleration time-series, we recover the lunar orbital parameters
**without any mass-based gravitational model**.

This is a purely kinematic pipeline:
- **Input**: `a(t)` — pendulum period perturbation time-series
- **Output**: Lunar distance `d(t)`, orbital inclination, eccentricity, period

No G. No M. zk² = 1.

## 2. SDT Foundation

### 2.1 Tidal Acceleration from Occlusion Gradient

The Moon creates a convergence deficit (occlusion) in the spation lattice.
At the observer's position, the differential tidal acceleration is:

```
a_tidal(t) = (Ϟ_Moon / d(t)²) × (2 R_Earth cos θ_z(t)) / d(t)
           = 2 Ϟ_Moon R_Earth cos θ_z(t) / d(t)³
```

where:
- `Ϟ_Moon = v_Moon² R_Moon / c²` — lunar c-boundary (SDT bridge law)
- `d(t)` — Earth–Moon distance at time t
- `θ_z(t)` — lunar zenith angle at the observer
- `R_Earth` — Earth's radius

This has the same `1/d³` dependence as the Newtonian tidal force because
both describe the same geometric gradient — SDT derives it from convergence
pressure, not from mass attraction.

### 2.2 Pendulum Period Modulation

A pendulum with baseline period `T₀ = 2π√(L/g₀)` responds to the
tidal perturbation:

```
δT/T₀ = -δg / (2g₀) = -a_tidal / (2g₀)
```

The perturbation has components:
- **M2** (principal lunar semidiurnal): period ≈ 12.42 hours
- **O1** (principal lunar diurnal): period ≈ 25.82 hours
- **N2** (larger lunar elliptic): period ≈ 12.66 hours

### 2.3 Kinematic Inversion

Given `a_tidal(t)` extracted from the pendulum:

1. **Fourier decompose** → extract M2, O1, N2 amplitudes and phases
2. **M2 amplitude** → `Ϟ_Moon / d_mean³` → given Ϟ_Moon from SDT bridge, solve for `d_mean`
3. **M2/N2 ratio** → orbital eccentricity `e`
4. **O1/M2 ratio** → orbital inclination relative to observer latitude
5. **M2 phase drift** → sidereal month (orbital period)
6. **Amplitude modulation** → perigee/apogee → confirm `e`

## 3. SDT Consistency

### Law III (Occlusion Force)
Tidal acceleration = gradient of occlusion across Earth's diameter.
The force is `F = (π/4) P_eff R₁² R₂² / r²`, and the tidal component
is the radial derivative evaluated over Earth's extent.

### Law V (Movement Budget)
The Moon's orbital velocity `v_orb` satisfies `v_circ² + v_orb² = c²`.
At `v_orb ≈ 1.022 km/s`, the correction is negligible (~10⁻¹¹) but
formally present.

### Bridge Law
`Ϟ_Moon = v_Moon² R_Moon / c² = 5.46 × 10⁻⁵ m` — the entire lunar
gravitational field encoded in one number.

## 4. Validation

### 4.1 Against Lunar Laser Ranging (E26)
The APOLLO facility (Apache Point, NM) provides sub-cm lunar distance
measurements. The kinematic pipeline should recover `d(t)` to within
the LLR uncertainty envelope.

### 4.2 Self-Consistency Checks
- Recovered orbital period should match sidereal month: 27.321661 days
- Recovered eccentricity should match: 0.0549
- Recovered semimajor axis should match: 384,400 km ± 0.1%

## 5. Implementation

### Tool: `cq23_lunar_pendulum.cpp`

Standalone C++20 tool that:
1. Synthesises a year of pendulum acceleration data from known lunar ephemeris
2. Adds realistic noise (accelerometer precision ~ 10⁻⁹ m/s²)
3. Performs the kinematic inversion pipeline
4. Recovers orbital parameters
5. Compares to known values

### Success Criteria
- [ ] Recovered `d_mean` within 0.1% of 384,400 km
- [ ] Recovered eccentricity within 5% of 0.0549
- [ ] Recovered period within 0.01% of 27.321661 days
- [ ] No G or M used anywhere in the pipeline
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: bridge::koppa_*, depth_closure::, no G/M
- Phase thresholds (committed before run): 0.1%, 0.1%, 5%, 0.01%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*GOM03 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
