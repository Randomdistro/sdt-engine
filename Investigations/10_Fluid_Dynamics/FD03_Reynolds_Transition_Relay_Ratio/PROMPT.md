# FD03 — The Reynolds Transition as a Lattice Relay Ratio

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Why is `Re` dimensionless and *why* does transition occur near a particular value: does the lattice fix the threshold `Re_crit` from **geometry** (the dominant-mode coherence length and the `2D` neighbour count), or is `Re_crit ≈ 2300` only reproducible by back-solving the coherence length from the measured number?
2. **Why does it matter?** — `Re` is the most consequential dimensionless group in fluids and standard texts give it no first-principles account; if SDT derives it as one medium's two competing rates, dimensionlessness becomes a *consequence* and transition becomes a *prediction*. Downstream: FD04 (the supra-threshold cascade), FD06 (flat-plate `Re_x`), FD10 (shedding onset).
3. **How will we find out?** — Four gated phases (§④). The dimensionlessness proof (P1) and the coherence-threshold *derivation* (P2) commit `Re_crit` to the run log **before** any data are read; the multi-geometry test (P3) is the real discriminator because geometry alone must move the threshold.
4. **What would prove us wrong?** — §⑧, five falsifiers with real failure modes — **the central one (F2) is honest about the trap:** the threshold must come from the coherence-length *computed from lattice geometry*, NOT back-solved from 2300; if `ℓ_c` can only be obtained by inverting the measured `Re_crit`, F2 is a CALIBRATED pass at best (cap at C), and a geometry that yields the *same* `Re_crit` for pipe/plate/Couette (F4) is a clean kill.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

**Domain**: Fluid Dynamics (SDT lattice mechanics) · **Status**: SPEC · **Author**: J. C. Harvey, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/GM fundamentals; no fields/wavefunctions/quarks/ΛCDM/magnetons; certification labels on every result; translation test on every borrowed term; honesty over success; anti-numerology).*

---

## 1. Executive Summary

The Reynolds number `Re = UL/ν` is the most consequential dimensionless group in fluid mechanics, yet textbooks present it as a phenomenological ratio with no first-principles account of *why* it is dimensionless or *why* transition occurs near a particular value. In SDT the lattice is the only ontology, so `Re` cannot be an imported abstraction — it must be the ratio of two **rates of the same medium**: advective displacement-transport (`U/L`) versus relay momentum-smoothing (`ν/L²`). **The question:** does `Re = (advective transport rate)/(relay smoothing rate)` explain transition as the crossing of an order-unity threshold set by lattice geometry, and does that threshold land in the measured transition band (pipe `Re_crit ≈ 2300`, flat-plate `Re_x ≈ 5×10⁵`)? Laminar flow persists while the lattice relay-smooths a perturbation within its coherence length; turbulence onsets when displacement transport outruns smoothing for the dominant mode. A native derivation that lands the threshold within an order of magnitude and ties it to geometry earns Class C; a ratio that misses by >1 order, or predicts no transition, is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** A perturbation injected into a flowing region is two things at once: it is *carried downstream* by the bulk flow (advection), and it is *spread and damped* by nearest-neighbour relay handoff (the lattice smoothing that FD02 identifies as viscosity). These are two competing rates of the same granular medium. While the relay can smooth a disturbance back below threshold before advection carries it a coherence length, the flow stays laminar — the lattice "keeps up". When the flow is fast or wide enough that a disturbance is advected beyond the reach of relay smoothing before it decays, the disturbance survives, cascades, and the flow goes turbulent. `Re` is the bookkeeping ratio of these two rates; being a ratio of like-dimensioned rates of one medium, it is *necessarily* dimensionless — that is the SDT explanation of its dimensionlessness.

**Key variables and dimensions.**
- `U` — characteristic flow speed [m·s⁻¹]
- `L` — characteristic length (pipe diameter, plate distance, gap) [m]
- `ν` — kinematic viscosity = relay-smoothing diffusivity [m²·s⁻¹] (handed in by FD02)
- `Re = UL/ν` — Reynolds number [dimensionless]
- `τ_adv = L/U` — advective transport time [s]
- `τ_relay = L²/ν` — relay-smoothing time over scale `L` [s]
- `Re = τ_relay/τ_adv` — ratio of the two times (equivalently rate ratio)
- `ℓ_c` — lattice/flow coherence length over which relay smoothing acts coherently [m]
- `Re_crit` — critical Reynolds number where the ratio crosses the geometric threshold [dimensionless]
- `ℓ_P`, `t_P`, `c = ℓ_P/t_P` — relay scale, tick, signal speed

**Connection to SDT.** Advective transport `U/L` is displacement transport — knots/cells carrying their velocity field downstream (FD01 advection term). Relay smoothing `ν/L²` is the lattice Laplacian diffusion of momentum (FD01/FD02 `ν∇²v`). The dimensionless `Re` is the ratio of these two *native* lattice rates; transition is a competition outcome, not an externally imposed instability criterion. The order-unity threshold is set by lattice/flow geometry (the coherence length `ℓ_c` and the dominant mode's wavelength), which is why different geometries give different `Re_crit`.

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Relay smoothing is a finite-rate diffusion (FD01 / FD02).** A velocity perturbation in a cell is shared with its `2D` contacting neighbours per tick; the continuum operator is `ν∇²v`. Over a scale `L`, the characteristic smoothing time is `τ_relay = L²/ν`. `ν = (geometry coefficient)·ℓ_P·c` is *referenced* from FD02, never refitted here. This is the only damping mechanism available to the lattice.

2. **Advective displacement transport (FD01 inertial term).** The bulk flow carries a perturbation at speed `U`; over scale `L` the transport time is `τ_adv = L/U`. This is the Granular-Pulse displacement transport coarse-grained (FLM02), capped by the movement budget `v_circ² + v² = c²` (Law V) so `U/c < 1` always.

3. **Re as a rate ratio (the dimensionless identity).** Divide the two times: `Re = τ_relay/τ_adv = (L²/ν)/(L/U) = UL/ν`. Both `τ_relay` and `τ_adv` are times of the *same* medium, so their ratio is dimensionless by construction — `Re` inherits its dimensionlessness from being one medium's two competing rates, not from an accidental cancellation of unrelated units. **This is the §1 "why dimensionless" answer and must be shown explicitly.**

4. **Coherence threshold (the transition condition).** Laminar flow holds while relay smoothing damps the dominant disturbance mode within one coherence length `ℓ_c` before advection transports it out: `τ_relay(ℓ_c) ≲ τ_adv(ℓ_c)`. Transition onsets when, for the *dominant* (least-damped) mode, the advective rate first exceeds the smoothing rate. This crossing defines `Re_crit = G`, where `G` is an order-unity-to-order-10³ geometric factor set by the mode geometry — *not* a fitted number; it must be computed from the dominant mode's aspect (e.g. wavenumber spectrum and the `2D` neighbour count), or flagged PENDING.

5. **Occlusion pressure provides the restoring/driving terms (Law I, Law III).** The pressure gradient driving the flow and the occlusion-pressure response to a displaced parcel both come from `P_conv` gradients (`law_I::P_conv`, `law_III::solid_angle_occluded`); no attractive term is invoked. Mass/inertia is displacement-load (Law IV `V_disp`), not kilograms-as-fundamental.

**Governing relations to derive (no new fitted parameters).**

- *Rate ratio.* `Re = τ_relay/τ_adv = UL/ν` from the two lattice times above — explicit, with dimensions shown.
- *Transition criterion.* `Re_crit = G(geometry)`, where `G` follows from the dominant-mode coherence condition `τ_relay(ℓ_c) = τ_adv(ℓ_c)`. Show how a confined geometry (pipe) yields `G ~ O(10³)` while an open geometry (flat plate) yields a larger `Re_x` because `L` (boundary-layer thickness) grows with distance.
- *Geometry dependence.* The *same* coherence condition must yield **different** `Re_crit` for pipe, flat-plate, and Taylor–Couette — geometry enters only through `ℓ_c` and the mode spectrum, never through a refit of `ν`.
- *Closure.* `ν` is taken from FD02; `G` is computed from lattice/mode geometry or flagged PENDING. No free integer or π is inserted to force `2300` (R5).

The deliverable of §3 is: (a) `Re` shown to be a like-rate ratio of one medium (dimensionlessness explained), and (b) a transition criterion in which geometry alone moves `Re_crit`, landing the pipe value in the measured band.

---

## 4. Investigation Strategy

Four phases, each gated. Run in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass).

### Phase 1 — The two lattice rates and the dimensionless identity
- **Goal.** Write `τ_adv = L/U` and `τ_relay = L²/ν` from SDT primitives (advective displacement transport and relay diffusion), and show `Re = τ_relay/τ_adv = UL/ν` is a ratio of two times of the *same* medium.
- **Method.** Build both rates from FD01's coarse-grained terms (advection vs `ν∇²v`), with `ν` referenced from FD02. Maintain a parameter ledger (R2) tagging every quantity DERIVED / MEASURED-INPUT / PENDING. State the dimensionlessness argument as a one-line dimensional proof.
- **Success metric.** `Re = UL/ν` reproduced exactly with both rates traced to lattice mechanisms; dimensionlessness shown as like-rate cancellation. **Checkpoint C1:** identity closed, zero free parameters beyond the FD02-pending `ν` and the geometric `G`.

### Phase 2 — The coherence threshold (transition criterion) — *the anti-tautology gate*
- **Goal.** Derive the transition condition `τ_relay(ℓ_c) = τ_adv(ℓ_c)` for the dominant mode and express `Re_crit = G(geometry)` **where `ℓ_c/L` is computed forward from lattice/mode geometry, never inverted from the measured 2300.**
- **The trap to avoid (stated plainly).** The relation `Re_crit ≈ (L/ℓ_c)²` lets anyone "predict" 2300 by *setting* `L/ℓ_c = √2300 ≈ 48`. That is a back-solve, not a derivation, and it can never fail F2. **The load-bearing step is computing `ℓ_c` independently:** the dominant-mode coherence length must come from the `2D` contacting-neighbour count and the least-damped wavenumber of a confined channel (a number known *before* the data are unsealed). If `ℓ_c` is obtained only by inverting `Re_crit`, the result is **CALIBRATED(1)** and the grade caps at C — the prompt forbids reporting it as DERIVED.
- **Method.** Identify the least-damped disturbance mode for a confined channel from the relay-diffusion operator; set the advective rate equal to the relay-smoothing rate at the forward-computed `ℓ_c`. Express `G` in terms of the mode wavenumber and the `2D` neighbour count, with each factor ledgered DERIVED or CALIBRATED. Commit the predicted pipe `Re_crit` to the run log *before* comparing to data (R1).
- **Success metric.** **A-path:** `ℓ_c/L` computed forward from geometry yields pipe `Re_crit` in the 2000–4000 band with CALIBRATED(0). **C-path:** the *mechanism* is right but `ℓ_c` had to be set from one scale — tag CALIBRATED(1), cap at C, and say so. **Checkpoint C2 (core gate):** a finite, geometry-set `Re_crit` from a forward-computed `ℓ_c`, not "no transition" and not a back-solved 2300.

### Phase 3 — Geometry dependence (multi-geometry test)
- **Goal.** Show the *same* criterion yields *different* `Re_crit` across geometries — the strongest evidence the mechanism is real rather than tuned.
- **Method.** Apply Phase-2's coherence condition to (i) pipe (diameter `L`), (ii) flat-plate boundary layer (`L` = local BL thickness, growing as `√(νx/U)` so transition is naturally reported as `Re_x`), and (iii) Taylor–Couette (gap `L`, comparison to critical Taylor number). Hold `ν` fixed (FD02 value); let only `ℓ_c` and the mode spectrum change.
- **Success metric.** Flat-plate `Re_x` lands near `5×10⁵` and Taylor–Couette onset maps to the measured critical Taylor number, both within one order, using the *same* `ν` and *only* geometric changes. **Checkpoint C3:** geometry alone reproduces the ordering and rough magnitudes of all three transitions.

### Phase 4 — Numerical two-stream verification
- **Goal.** Confirm, on a small lattice, that a perturbation decays below `Re_crit` and survives/grows above it, with the crossover at the derived `G`.
- **Method.** On a 1-D/2-D Phase-1-style relay lattice (FD01), inject a single Fourier disturbance into a uniform flow; measure whether `‖perturbation‖` decays (`e^{−ν k² t}` smoothing wins) or persists (advection wins) as `Re` is swept across the predicted `Re_crit`. Two-stream check (R3): analytic ratio crossing vs lattice crossover. Keep lattices small (`N ≤ 256`) — this demonstrates mechanism, not production CFD.
- **Success metric.** Lattice crossover `Re` matches the analytic `Re_crit = G` to <1% in the ratio (the *number* `G` may carry PENDING geometry uncertainty); decay below, growth above, confirmed. **Checkpoint C4.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Transition derived natively | `Re = τ_relay/τ_adv` proven dimensionless AND `Re_crit = G` with `ℓ_c/L` and `G` **computed forward** from lattice/mode geometry (CALIBRATED(0), *not* back-solved from 2300) AND pipe value in 2000–4000 band AND flat-plate + Taylor–Couette reproduced within order using the *same* `ν` and *only* geometric changes. |
| **C (QUALIFIED — convergence)** | Threshold reproduced, one scale set | Rate-ratio identity exact, multi-geometry ordering reproduced, pipe `Re_crit` within one order of `2300`, with exactly CALIBRATED(1) — the coherence scale `ℓ_c` set from one number (e.g. inverted from the pipe value) and the *same* `ℓ_c`-rule then *predicting* the plate/Couette thresholds. The back-solve is disclosed, not hidden. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | Rate-ratio identity and transition *mechanism* established, but `G` is PENDING the dominant-mode/`ℓ_c` calculation (or FD02 `ν`); dimensionally closed, magnitude not yet pinned. |
| **F (FAIL)** | Mechanism falsified | `Re_crit` off by >1 order of magnitude with no reconciling geometry, OR the criterion predicts no transition, OR predicts transition independent of geometry (same `Re_crit` for pipe/plate/Couette), OR the ratio is not genuinely dimensionless from like rates. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd03_reynolds_relay_ratio.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-1 rate-ratio identity; Phase-2/3 `Re_crit = G` evaluation across pipe/plate/Couette geometries; Phase-4 lattice perturbation-decay-vs-growth sweep across `Re_crit`; prints its own verdict. **No new constants redefined.** |
| `fd03_results.txt` | Plain text | Run output: the two rates and `Re` identity; predicted `Re_crit` per geometry vs measured (committed *before* comparison, R1); lattice crossover-`Re` vs analytic `G` (two-stream); parameter ledger. |
| `FD03_DERIVATION.md` | Markdown | Full derivation: two lattice rates → `Re = UL/ν` dimensionlessness proof → coherence threshold → `Re_crit = G(geometry)` for each geometry; parameter ledger. |
| `FD03_VERDICT.md` | Markdown | A–F classification with the deciding metric; provenance × correspondence audit; DERIVED vs CALIBRATED(n) vs PENDING; downstream handoffs to FD04/FD06/FD10. |

---

## 7. Dependencies & References

**Upstream (required):**
- **FD01 (Navier–Stokes from Spation Relay)** — supplies the advection term (`U/L` rate) and the relay-diffusion term (`ν∇²v`); FD03 cannot start without FD01's coarse-grained PDE and lattice rules.
- **FD02 (Viscosity from the Lattice)** — supplies the kinematic viscosity `ν = (coefficient)·ℓ_P·c`; FD03 references this value and must not refit it.
- **FLM02 (Granular Pulse Mechanics)** — advective displacement transport at the cell level.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_I::P_conv` (driving pressure), `law_III::solid_angle_occluded` (occlusion response), `law_IV` (`V_disp` → inertia/ρ), `law_V` (`v_circ²+v²=c²`, `U/c<1` cap), `law_VI::traction`/`law_VI::confinement` (mode/coherence geometry).

**Downstream (unblocked by this):**
- **FD04 (turbulent cascade above transition)** — receives the supra-`Re_crit` regime where disturbances survive and cascade.
- **FD10 (vortex shedding)** — receives the geometry-set instability onset (shedding `Re` thresholds).

**Related:** **FD06 (boundary-layer transition)** — shares the flat-plate `Re_x` coherence calculation; B16 transport exponents (`ν ∝ √T`, exponent 0.5) feed `ν`'s temperature dependence; FD05 (compressible/sound) for the `U/c` budget cap context.

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Dimensionlessness (Phase 1) | `Re` is a ratio of two like rates of one medium | `Re = τ_relay/τ_adv = UL/ν`, dimensions cancel exactly | Ratio not formed from like rates / not dimensionless ⟹ `Re` not a relay-rate ratio ⟹ Class F |
| F2 — Pipe threshold (Phase 2, anti-tautology) | `Re_crit = G` from an `ℓ_c` **computed forward** from the `2D` neighbour count + dominant wavenumber | forward-computed pipe `Re_crit` in 2000–4000 | If `ℓ_c` is back-solved from 2300 (`L/ℓ_c = √2300`), F2 **cannot fail** and is a CALIBRATED pass only (cap C); if the forward `ℓ_c` gives `Re_crit` off >1 order with no reconciling geometry ⟹ Class F |
| F3 — Transition exists (Phase 2) | A finite crossing exists | Finite `Re_crit`, decay below / growth above | Criterion gives no crossing (no transition) ⟹ mechanism falsified |
| F4 — Geometry dependence (Phase 3) | Same `ν`, different geometry → different `Re_crit` | Pipe ≈2300, plate `Re_x`≈5×10⁵, Couette ≈ critical Taylor number, all within order | Same `Re_crit` for all geometries (geometry-independent) ⟹ Class F |
| F5 — Crossover (Phase 4) | Lattice crossover = analytic `G` | Lattice perturbation crossover-`Re` matches analytic `Re_crit` <1% in the ratio | >1 order disagreement between lattice crossover and analytic `G` ⟹ relay-ratio not the transition mechanism |

---

## 9. Implementation Notes

- **Numerical stability.** The Phase-4 lattice is an explicit relay update (FD01 style); respect the CFL bound (`|v|Δt/Δx < 1`) and the diffusion cap (`ν Δt/Δx² ≤ 1/2`), sub-cycling or going implicit on the smoothing step if needed. Double precision; keep lattices small (1-D/2-D, `N ≤ 256`) — this is a mechanism demonstration, not a production transition solver.
- **Testing strategy.** Two-stream (R3): (i) analytic `Re = τ_relay/τ_adv` vs the lattice-measured rate ratio; (ii) analytic `Re_crit = G` vs the lattice perturbation crossover. Predict and commit every `Re_crit` to the run log *before* comparing to the data in `DATA_REQUIREMENTS.md` (R1). Anti-numerology (R5): the threshold `G` must come from the dominant-mode/`2D`-neighbour geometry, never a hand-inserted integer or π chosen to hit `2300` — if it cannot be derived, flag it PENDING and cap the verdict at D.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd03_reynolds_relay_ratio.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd03_reynolds_relay_ratio.cpp -o fd03` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** Plot the two rates `τ_relay` and `τ_adv` vs `Re` and mark their crossing (`Re_crit`); a log-log bar chart of predicted vs measured `Re_crit` across the three geometries; the lattice perturbation-norm time series for `Re` just below and just above threshold (decay vs growth) on one axis.
- **Author attribution:** J. C. Harvey, Melbourne. The standard-FD result (`Re_crit ≈ 2300`, `Re_x ≈ 5×10⁵`, the critical Taylor number) is the CONVERGENCE target to *reproduce*, never an input to *borrow*.

## 10. Questions This Opens *(generative — log new ones in `FD03_VERDICT.md`)*

1. **Is `Re_crit` genuinely a property of `√(L/ℓ_c)`-type lattice geometry**, or is the transition value irreducibly a property of the *spectrum* of unstable modes (so that no single `ℓ_c` exists)? If the latter, the SDT win is the dimensionlessness proof, and the threshold value stays OPEN.
2. **Does the same forward-`ℓ_c` rule that fixes the pipe value also predict the *subcritical* nature of pipe transition** (finite-amplitude threshold, hysteresis), which linear theory misses? That would be an SDT-distinct prediction beyond reproducing 2300.
3. **Why does the flat-plate `Re_x ≈ 5×10⁵` exceed the pipe value by ~200×** purely through `L` = growing boundary-layer thickness — is that ratio itself derivable from the FD06 `δ(x) ∝ √(νx/U)` law, closing FD03↔FD06?
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FD03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 if `ℓ_c` is forward-computed (A-path); exactly 1 if `ℓ_c` is set from the pipe value (C-path) — declare which
- Engine namespaces actually used: law_I (P_conv driving pressure), law_III (solid_angle_occluded), law_IV (V_disp→ρ), law_V (U/c<1 cap), law_VI::traction/confinement (mode geometry); ν referenced from FD02
- Phase thresholds (committed before run):
    P1 `Re=UL/ν` dimensionless exactly · P2 forward-`ℓ_c` pipe `Re_crit` in 2000–4000 (kill >1 order; CALIBRATED if back-solved)
    P3 same `ν`, plate `Re_x`~5×10⁵ and Couette within 1 order · P4 lattice crossover = analytic `G` <1% in ratio
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces; **back-solve `ℓ_c` from 2300 then grade A**
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Forward `ℓ_c` cannot be computed without the data | down-grade to **C**, set `ℓ_c` from one scale, disclose | **OPEN** the dominant-mode `ℓ_c` calculation | back-solve `L/ℓ_c=√2300` and grade A |
| P2 forward `Re_crit` off >1 order | recheck the `2D` neighbour count and dominant wavenumber | **KILL** the geometric-threshold claim | widen the "order of magnitude" band post-hoc |
| P3 same `Re_crit` for pipe/plate/Couette | re-examine `ℓ_c(geometry)` per case | **KILL** (geometry-independent = not the mechanism) | refit `ν` per geometry |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FD02 `ν`) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in the Phase-1 native chain · grading A on a back-solved `ℓ_c`.

---

*FD03 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
