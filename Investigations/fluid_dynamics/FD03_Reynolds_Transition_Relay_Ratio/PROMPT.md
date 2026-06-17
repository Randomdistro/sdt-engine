# FD03 — The Reynolds Transition as a Lattice Relay Ratio

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

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

2. **Advective displacement transport (FD01 inertial term).** The bulk flow carries a perturbation at speed `U`; over scale `L` the transport time is `τ_adv = L/U`. This is the Granular-Pulse displacement transport coarse-grained (CQ08), capped by the movement budget `v_circ² + v² = c²` (Law V) so `U/c < 1` always.

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

### Phase 2 — The coherence threshold (transition criterion)
- **Goal.** Derive the transition condition `τ_relay(ℓ_c) = τ_adv(ℓ_c)` for the dominant mode and express `Re_crit = G(geometry)`.
- **Method.** Identify the least-damped (dominant) disturbance mode for a confined channel; set the advective rate equal to the relay-smoothing rate at the coherence length `ℓ_c`. Express `G` in terms of the mode wavenumber and the `2D` neighbour count. Predict the pipe `Re_crit` *before* comparing to data (R1) and commit it to the run log.
- **Success metric.** Predicted pipe `Re_crit` within one order of magnitude of `≈2300` (target: within the 2000–4000 band if `G` is genuinely geometric). **Checkpoint C2 (core gate):** the criterion yields a finite, geometry-set `Re_crit`, not "no transition" and not a fitted `2300`.

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
| **A (PASS — derived)** | Transition derived natively | `Re = τ_relay/τ_adv` proven dimensionless AND `Re_crit = G` with `G` DERIVED from lattice/mode geometry (CALIBRATED(0)) AND pipe value in 2000–4000 band AND flat-plate + Taylor–Couette reproduced within order using the same `ν`. |
| **C (QUALIFIED — convergence)** | Threshold reproduced, one scale set | Rate-ratio identity exact, multi-geometry ordering reproduced, pipe `Re_crit` within one order of `2300`, with at most CALIBRATED(1) (one geometric/coherence scale fitted, documented). |
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
- **CQ08 (Granular Pulse Mechanics)** — advective displacement transport at the cell level.
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
| F2 — Pipe threshold (Phase 2) | `Re_crit = G(geometry)` lands in measured band | Predicted pipe `Re_crit` within one order of `2300` (target 2000–4000) | Off by >1 order with no reconciling geometry ⟹ Class F |
| F3 — Transition exists (Phase 2) | A finite crossing exists | Finite `Re_crit`, decay below / growth above | Criterion gives no crossing (no transition) ⟹ mechanism falsified |
| F4 — Geometry dependence (Phase 3) | Same `ν`, different geometry → different `Re_crit` | Pipe ≈2300, plate `Re_x`≈5×10⁵, Couette ≈ critical Taylor number, all within order | Same `Re_crit` for all geometries (geometry-independent) ⟹ Class F |
| F5 — Crossover (Phase 4) | Lattice crossover = analytic `G` | Lattice perturbation crossover-`Re` matches analytic `Re_crit` <1% in the ratio | >1 order disagreement between lattice crossover and analytic `G` ⟹ relay-ratio not the transition mechanism |

---

## 9. Implementation Notes

- **Numerical stability.** The Phase-4 lattice is an explicit relay update (FD01 style); respect the CFL bound (`|v|Δt/Δx < 1`) and the diffusion cap (`ν Δt/Δx² ≤ 1/2`), sub-cycling or going implicit on the smoothing step if needed. Double precision; keep lattices small (1-D/2-D, `N ≤ 256`) — this is a mechanism demonstration, not a production transition solver.
- **Testing strategy.** Two-stream (R3): (i) analytic `Re = τ_relay/τ_adv` vs the lattice-measured rate ratio; (ii) analytic `Re_crit = G` vs the lattice perturbation crossover. Predict and commit every `Re_crit` to the run log *before* comparing to the data in `DATA_REQUIREMENTS.md` (R1). Anti-numerology (R5): the threshold `G` must come from the dominant-mode/`2D`-neighbour geometry, never a hand-inserted integer or π chosen to hit `2300` — if it cannot be derived, flag it PENDING and cap the verdict at D.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd03_reynolds_relay_ratio.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd03_reynolds_relay_ratio.cpp -o fd03` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** Plot the two rates `τ_relay` and `τ_adv` vs `Re` and mark their crossing (`Re_crit`); a log-log bar chart of predicted vs measured `Re_crit` across the three geometries; the lattice perturbation-norm time series for `Re` just below and just above threshold (decay vs growth) on one axis.
- **Author attribution:** James Christopher Tyndall, Melbourne. The standard-FD result (`Re_crit ≈ 2300`, `Re_x ≈ 5×10⁵`, the critical Taylor number) is the CONVERGENCE target to *reproduce*, never an input to *borrow*.
