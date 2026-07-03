# FD06 — The Boundary Layer and No-Slip from Spation Traction

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Fluid mechanics *imposes* no-slip (`u=0` at a wall) as an empirical boundary condition with no first-principles reason; does SDT spation traction (PPT06) *derive* no-slip as a stable fixed point, with residual slip length `λ_s → 0` (continuum) or `λ_s ∼ ℓ_P` (molecularly negligible)?
2. **Why does it matter?** — No-slip is the unexplained foundation under every wall-bounded flow; if traction produces it as an output, then skin friction is just the traction shear `τ_w = μ(∂u/∂y)|_w` and the Blasius layer `δ ∼ √(νx/U)` is the diffusion-vs-advection balance — wiring FD06 to FD03 (transition), FD09 (drag crisis), FD10 (separation/shedding).
3. **How will we find out?** — Five gated phases (§④): start the lattice in *pure slip* (`u=U` everywhere) and show the traction rule alone relaxes the wall layer to zero — no `u=0` hand-set anywhere; the `√(νx/U)` scaling (P2) is the core gate.
4. **What would prove us wrong?** — §⑧, five falsifiers with real failure modes: finite slip `λ_s ≫ ℓ_P` in the continuum limit; `δ` slope ≠ ½; `C_f`/`δ` prefactor off by >2×; profiles failing to collapse; or no finite transition `Re_x`.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

**Domain**: Fluid Dynamics (SDT lattice mechanics) · **Status**: SPEC · **Author**: J. C. Harvey, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/kg fundamentals; no fields/wavefunctions/quarks/ΛCDM; certification labels on every result; translation test on every borrowed term; honesty over success).*

---

## 1. Executive Summary

In every textbook the **no-slip condition** (`u = 0` at a wall) is *imposed* as an empirical boundary condition — fluid mechanics has no first-principles reason a flow should stick to a solid surface. In Spatial Displacement Theory the wall is matter: a dense spation wake whose surface demands a phase velocity the lattice can only partly relay, so it *grips* (PPT06 traction) the immediately adjacent lattice. **The question:** does that traction, applied as a relay boundary on the FD01 Navier–Stokes lattice, *derive* no-slip rather than assume it, and does the resulting velocity-deficit region grow as the Blasius boundary layer `δ(x) ∼ √(νx/U)`? If so, the wall-shear (skin friction) is just the traction shear stress `τ_w = μ(∂u/∂y)|_wall`, and laminar→turbulent transition is the point where advection outruns relay-traction smoothing (links FD03). A clean recovery of `δ/x = 5.0/√Re_x` and `C_f = 0.664/√Re_x` with no-slip as an *output* earns Class C; a traction rule that fails to lock the wall velocity, or yields the wrong `δ` scaling, is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** A solid surface in SDT is not a "wall boundary condition" — it is a region of vortex-knot matter whose spations are already saturated relaying their own internal convergence throughput. Where this surface contacts free lattice, its rotational wake demands of the neighbouring spations a tangential phase velocity the lattice cannot fully relay (the `≤c` cap, PPT06). The unrelayed mismatch is **traction**: the surface drags the adjacent spations to its own tangential velocity (zero, for a stationary plate), exactly as a rough roller grips the sheet touching it. That grip propagates *outward* by the same nearest-neighbour relay diffusion that carries viscosity in FD01/FD02; meanwhile the bulk flow advects the gripped region downstream. The competition between sideways relay-diffusion of the grip and downstream advection sets a penetration depth — the boundary layer.

**Key variables and dimensions.**
- `U` — free-stream velocity outside the layer [m·s⁻¹]
- `u(x,y)` — streamwise velocity, `u → 0` at the wall (`y=0`), `u → U` far away [m·s⁻¹]
- `δ(x)` — boundary-layer thickness, `u = 0.99U` locus [m]
- `δ*` — displacement thickness; `θ` — momentum thickness [m]
- `x` — distance advected along the plate from the leading edge [m]
- `ν` — kinematic viscosity (relay-diffusion coefficient, from FD02) [m²·s⁻¹]; `μ = ρν` [Pa·s]
- `τ_w(x)` — wall shear stress (traction shear) [Pa]; `C_f = τ_w / (½ρU²)` — local skin-friction coefficient [–]
- `Re_x = Ux/ν` — local Reynolds number (advection ÷ relay-diffusion of the grip) [–]
- `T = 3(W+1)` — traction ratio (engine `law_VI::traction::traction_ratio_proton = 12`) [–]

**Connection to SDT.** The grip is `law_VI::traction`: a velocity mismatch `ω_demand` the lattice relays only up to `c`, producing a shear coupling between wall spations and the first free layer. Relay-diffusion of that coupling outward is the FD01 `ν∇²u` term; advection is the FD01 `(v·∇)v` term. The boundary layer is therefore the *same* coarse-grained relay bookkeeping as FD01, restricted to a half-space with a traction wall — no new physics, one new boundary mechanism. No-slip is not an axiom but the steady-state of maximal traction grip; skin friction is the rate that grip extracts momentum from the flow.

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Traction at a matter surface (PPT06, `law_VI::traction`).** A vortex-knot surface demands an angular/phase velocity `ω_demand` of its contacting spations; the lattice relays at `≤ c`, so the mismatch `T = ω_demand/ω_max = 3(W+1)` (engine `traction_ratio_proton = 12`) is unrelayed and appears as a *tangential drag* on the first free spation layer. For a macroscopic stationary wall this drag has one fixed point: the adjacent lattice velocity relaxes to the wall's velocity (zero). **This fixed point is the no-slip condition — derived, not imposed.** The `ℓ=1/2/≥3` wake channels (radial/rotational/orbital-entrainment) set which moments of the velocity field the wall couples to; the tangential (`ℓ=2` rotational) channel is the skin-friction coupling.

2. **Relay momentum diffusion (FD01, Law III).** The gripped tangential deficit at the wall is shared with contacting neighbours one tick per `t_P`; its continuum operator is `ν∇²u` with `ν = (geometry coefficient)·ℓ_P·c` *handed in from FD02* (not refitted here). This spreads the deficit *normal* to the wall (into `y`).

3. **Displacement transport (FD01 advection).** The bulk flow carries each gripped layer downstream at `≈U`; in time `t` it travels `x ≈ Ut`, during which the grip has diffused a normal distance `δ ∼ √(νt) = √(νx/U)`. This is the **Blasius balance** stated in pure relay terms: *normal relay-diffusion of traction vs streamwise advection.*

4. **Movement budget (Law V).** `v_circ² + v_trans² = c²` caps every layer velocity at `c`; near the wall the deficit is carried by the same budget, and the low-Mach (`U/c → 0`) limit keeps the layer incompressible (FD01 Phase 3) so the standard Blasius (constant-`ρ`) form applies.

5. **Convergence pressure as the closure (Law I, `law_I::P_conv`).** For the zero-pressure-gradient flat plate the streamwise `∇P = 0`; the layer is set by traction + diffusion + advection alone. Non-zero `∇P` (favourable/adverse) is the separation/drag-crisis hook handed downstream to FD09/FD10.

**Governing relations to derive (no new fitted parameters).**

- *No-slip as a fixed point.* Show that the traction update rule on the wall-adjacent layer has a unique stable fixed point `u(y=0) = u_wall = 0`, reached on a relay timescale `≪` advective timescale, so the wall layer is effectively pinned. The grip strength must be sufficient (set by `T = 3(W+1)`) that *partial* slip vanishes in the continuum limit — quantify any residual slip length `λ_s` and show `λ_s → 0` (or `λ_s ∼ ℓ_P`, i.e. molecularly negligible).
- *Blasius thickness.* From the diffusion-vs-advection balance, derive `δ(x) = C_δ √(νx/U)`, equivalently `δ/x = C_δ /√Re_x`; the convergence target is `C_δ ≈ 5.0` (99% thickness).
- *Skin friction.* `τ_w(x) = μ (∂u/∂y)|_{y=0}` from the derived profile; the convergence target is the local `C_f = 0.664/√Re_x` and the integrated drag `C_D = 1.328/√Re_L`.
- *Integral thicknesses.* `δ*/δ` and `θ/δ` from the derived profile (Blasius: `δ* ≈ 1.721√(νx/U)`, `θ ≈ 0.664√(νx/U)`, `H = δ*/θ ≈ 2.59`).

The deliverable of §3 is a chain in which the wall traction *produces* no-slip, the relay-diffusion/advection balance *produces* the `√(νx/U)` law, and the traction shear *produces* the skin friction — each Blasius number arising from one lattice mechanism, none inserted by hand.

---

## 4. Investigation Strategy

Five phases, each gated. Run them in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass).

### Phase 1 — Traction wall on the FD01 lattice (no-slip as output)
- **Goal.** Add a stationary matter wall to the FD01 relay lattice (half-space `y ≥ 0`, wall at `y=0`) and implement the PPT06 traction coupling on the wall-adjacent spation layer. Demonstrate that the *only* extra rule is the traction grip — no `u=0` is hand-set.
- **Method.** Encode the traction update from `law_VI::traction` (`ω_demand`, `traction_ratio_proton = 12`) as a tangential momentum exchange between wall and first free layer. Initialise the lattice with uniform `u = U` (slip everywhere) and relax. Tag every constant DERIVED / MEASURED-INPUT / CALIBRATED(n) in a parameter ledger (R2). Cite PPT06 (traction), FD01 (NS lattice), FD02 (`ν`) as upstream.
- **Success metric.** The wall-adjacent velocity relaxes to `u ≈ 0` from a pure-slip start, with residual slip length `λ_s` measured and shown `≲ ℓ_P` (i.e. continuum no-slip). **Checkpoint C1:** no-slip emerges as a traction fixed point, not an imposed BC; relaxation timescale ≪ advective timescale.

### Phase 2 — Boundary-layer growth `δ(x) ∼ √(νx/U)` (the Blasius scaling gate)
- **Goal.** Show the gripped deficit penetrates normal to the wall as the flow advects, with thickness growing as `√(νx/U)`.
- **Method.** Drive a steady free stream `U` over the plate; let traction grip + relay-diffusion act while advection carries layers downstream. Measure the `0.99U` locus `δ(x)` at several stations. Fit `δ = C_δ √(νx/U)` (log-log `δ` vs `x` should have slope ½). Maintain a ledger mapping the fitted `C_δ` to the diffusion-vs-advection balance, not to a tuned constant.
- **Success metric.** Slope of `log δ` vs `log x` is `0.50 ± 0.03`; prefactor `C_δ` recovers `≈ 5.0` (99% thickness) within the falsifier band (<2×). **Checkpoint C2 (the core gate):** `δ` scaling and prefactor match Blasius from traction + relay-diffusion alone.

### Phase 3 — Skin friction `C_f = 0.664/√Re_x` (traction shear)
- **Goal.** Derive the wall shear stress as the traction shear and recover the skin-friction law.
- **Method.** Compute `τ_w(x) = μ(∂u/∂y)|_{wall}` from the lattice velocity profile (`μ = ρν`, FD02 value). Form `C_f = τ_w/(½ρU²)` and plot vs `Re_x`. Integrate to the plate drag `C_D` over length `L`.
- **Success metric.** `C_f` follows `0.664/√Re_x` (prefactor within <2×; slope `−½` in `log` `C_f` vs `log Re_x`); integrated `C_D ≈ 1.328/√Re_L`. **Checkpoint C3:** skin friction is the traction shear, not a fitted drag law.

### Phase 4 — Profile self-similarity & integral thicknesses
- **Goal.** Confirm the velocity profile collapses to a single self-similar shape `u/U = f(y/δ)` and recover the displacement/momentum thicknesses.
- **Method.** Rescale profiles at several `x` by `η = y/δ(x)`; check collapse to one curve (the SDT analogue of the Blasius `f'(η)`). Compute `δ* = ∫(1−u/U)dy`, `θ = ∫(u/U)(1−u/U)dy`, shape factor `H = δ*/θ`.
- **Success metric.** Profiles collapse (RMS spread of rescaled curves <5%); `δ*/θ = H` recovers `≈ 2.59` and `δ*/δ`, `θ/δ` within the Blasius band. **Checkpoint C4:** the layer is self-similar with the correct integral ratios.

### Phase 5 — Transition threshold & two-stream verification
- **Goal.** Locate the laminar→turbulent transition as the point where advective transport outruns relay-traction smoothing, and verify the whole chain against a measured/DNS benchmark.
- **Method.** Increase `Re_x` until the steady layer destabilises in the lattice; record the critical `Re_x` and hand the mechanism (and any threshold number) to FD03. Run an independent macroscopic check: predict `δ` and `C_f` for a stated air or water flow at a measured `(U, x, ν, T)` and compare to the Blasius value / a published flat-plate measurement (R3 two-stream: analytic Blasius vs lattice). If a single fluid scale must be set, tag CALIBRATED(1) and document it.
- **Success metric.** Critical `Re_x` is finite and reported (order-of-magnitude check vs the canonical `≈ 5×10⁵`, not a tuned match); benchmark `δ` and `C_f` match within stated tolerance with calibration count `≤ 1`. **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Boundary layer derived natively | No-slip emerges as traction fixed point (`λ_s ≲ ℓ_P`) AND `δ/x = 5.0/√Re_x` (prefactor DERIVED) AND `C_f = 0.664/√Re_x` AND self-similar profile with `H ≈ 2.59`, all CALIBRATED(0), benchmark match <5%. |
| **C (QUALIFIED — convergence)** | Reproduced, one scale set | No-slip from traction, `δ` slope ½ and prefactor within <2× Blasius, `C_f` prefactor within <2×, with one fluid scale fitted (`ν` from FD02 or one calibration) tagged CALIBRATED(1) and documented. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | No-slip + `√(νx/U)` scaling reproduced numerically but a prefactor (e.g. `C_δ` or transition threshold) is PENDING FD02/FD03; dimensionally closed, not yet matching the Blasius constant. |
| **F (FAIL)** | Mechanism falsified | Traction does NOT lock the wall velocity (finite slip `λ_s ≫ ℓ_P` in continuum limit), OR `δ` scaling ≠ `√(νx/U)` (slope not ½), OR `C_f`/`δ` prefactor off by >2× with no reconciling mechanism. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd06_boundary_layer_traction.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-1 traction wall on the FD01 lattice (no-slip relaxation); Phase-2 `δ(x)` growth fit; Phase-3 `C_f` vs `Re_x`; Phase-4 profile-collapse & integral thicknesses; Phase-5 transition sweep + Blasius two-stream check; prints its own verdict. **No new constants redefined.** |
| `fd06_results.txt` | Plain text | Run output: slip-length relaxation (Phase 1), `δ` vs `x` log-log fit (Phase 2), `C_f` vs `Re_x` table (Phase 3), rescaled-profile spread and `H` (Phase 4), critical `Re_x` and benchmark comparison (Phase 5). |
| `FD06_DERIVATION.md` | Markdown | Full derivation: traction → no-slip fixed point; diffusion-vs-advection → `δ ∼ √(νx/U)`; traction shear → `C_f`; integral thicknesses; parameter ledger. |
| `FD06_VERDICT.md` | Markdown | A–F classification with the deciding metric; provenance × correspondence audit; what is DERIVED vs CALIBRATED(n) vs PENDING; downstream handoffs to FD09/FD10/FD03. |

---

## 7. Dependencies & References

**Upstream (required):**
- **PPT06 (Spation traction from the trefoil)** — `law_VI::traction` (`ω_demand`, `traction_ratio_proton = 3(W+1) = 12`, wake channels `ℓ=1/2/≥3`); the mechanical origin of the wall grip and thus of no-slip.
- **FD01 (Navier–Stokes from spation relay)** — the relay lattice and the `(v·∇)v` advection + `ν∇²v` diffusion terms this investigation restricts to a half-space.
- **FD02 (viscosity from the lattice)** — supplies the `ν = (coefficient)·ℓ_P·c` value used in the `δ` and `C_f` predictions; FD06 cannot reach Class A without FD02's independent `ν`.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_VI::traction` (grip), `law_III::solid_angle_occluded` / `law_I::P_conv` (pressure closure), `law_V` (`v_circ²+v_trans²=c²`, low-Mach), `bridge::koppa`.

**Downstream (unblocked by this):**
- **FD09 (drag crisis)** — the drag crisis is boundary-layer transition (laminar→turbulent reattachment); receives the Phase-5 transition mechanism and adverse-`∇P` separation hook.
- **FD10 (vortex shedding)** — shedding from a separated boundary layer; receives the separation criterion.
- **FD03 (laminar→turbulent transition)** — receives the critical-`Re_x` threshold (advection outrunning relay-traction smoothing).

**Related:** FD07 (lift/circulation) — bound circulation is the integrated wall traction; B16 (transport exponents, `ν ∝ √T`, exponent 0.5) feeding FD02's `ν`.

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — No-slip from traction (Phase 1) | Wall traction pins the adjacent layer | Wall velocity relaxes to `u≈0` from a pure-slip start; residual slip `λ_s ≲ ℓ_P` | Finite slip `λ_s ≫ ℓ_P` in the continuum limit ⟹ traction does not yield no-slip ⟹ Class F |
| F2 — Blasius thickness (Phase 2) | `δ ∼ √(νx/U)` from diffusion vs advection | `log δ` vs `log x` slope `0.50±0.03`, prefactor `C_δ ≈ 5.0` (<2×) | Slope ≠ ½ or prefactor off >2× ⟹ wrong penetration mechanism ⟹ Class F |
| F3 — Skin friction (Phase 3) | `τ_w` is the traction shear | `C_f = 0.664/√Re_x` (slope `−½`, prefactor <2×); `C_D ≈ 1.328/√Re_L` | `C_f` prefactor off >2× or wrong slope ⟹ traction ≠ wall shear |
| F4 — Self-similarity (Phase 4) | Profile collapses to one shape | Rescaled `u/U` vs `y/δ` collapse <5% RMS; `H ≈ 2.59` | No collapse, or `H` off-band ⟹ layer not self-similar / profile mis-derived |
| F5 — Transition & benchmark (Phase 5) | Transition = advection > relay smoothing | Finite critical `Re_x` (order `~5×10⁵`); benchmark `δ`,`C_f` <5% with CALIBRATED ≤1 | No transition, or benchmark off with >1 calibration ⟹ chain falsified |

---

## 9. Implementation Notes

- **Numerical stability.** The lattice is an explicit relay update; respect the CFL bound (`c·t_P/ℓ_P = 1` at the relay scale; coarse sub-steps keep `|u|Δt/Δx < 1`) and the diffusion cap `νΔt/Δy² ≤ 1/2` (sub-cycle or use an implicit normal-diffusion step near the wall, where gradients are steep). Use double precision; stretch the `y`-grid toward the wall to resolve the steep traction layer. Keep test grids modest (2-D, `N ≤ 256` streamwise) — this is a *demonstration of mechanism*, not a production CFD solver.
- **Testing strategy.** Three independent two-stream checks (R3): (i) slip-length relaxation from a pure-slip initial condition (Phase 1); (ii) `δ` vs `x` power-law fit against Blasius `5.0/√Re_x` (Phase 2); (iii) analytic Blasius profile vs lattice profile and `C_f` (Phases 3–4). Predict each number and commit it to the run log *before* comparing (R1). Anti-numerology (R5): no free integer or π inserted to force `C_δ`, `0.664`, or `H` — each must come from the traction/diffusion balance or be flagged CALIBRATED.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd06_boundary_layer_traction.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd06_boundary_layer_traction.cpp -o fd06` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes (use `law_VI::traction` directly).
- **Visualisation hints.** Dump the 2-D `u(x,y)` field to CSV for a heatmap; overlay the predicted `δ(x) = 5.0√(νx/U)` envelope on the `0.99U` locus; plot `C_f` vs `Re_x` log-log against `0.664/√Re_x`; show the rescaled-profile collapse (`u/U` vs `y/δ`) as the self-similarity proof; mark the Phase-5 critical `Re_x` on the `δ(x)` plot.
- **Author attribution:** J. C. Harvey, Melbourne. The standard-FD result (Blasius `δ/x = 5.0/√Re_x`, `C_f = 0.664/√Re_x`, no-slip, the integral thicknesses) is the CONVERGENCE target to *reproduce*, never an input to *borrow* — the no-slip condition in particular must arrive as a traction *output*, not be coded as a wall BC.

## 10. Questions This Opens *(generative — log new ones in `FD06_VERDICT.md`)*

1. **Is the residual slip length `λ_s` exactly `∼ ℓ_P`, or does the traction ratio `T = 3(W+1) = 12` set a larger, measurable slip** for specific surfaces? A finite predicted `λ_s` would connect to measured nanoscale slip lengths on superhydrophobic / atomically smooth surfaces — an SDT-distinct, testable number.
2. **Does the Blasius constant `C_δ ≈ 5.0` emerge fully from the traction/diffusion balance, or does a residual factor stay PENDING?** If it is fully geometric, FD06 is Class A; if one scale must be set from FD02's `ν`, it is honest Class C — the prompt must not paint over the distinction.
3. **Is the `ℓ=2` rotational traction channel that sets skin friction the same channel FD07 uses for bound circulation/lift?** If wall traction and bound circulation are one mechanism at different boundary conditions, FD06 and FD07 share a single coefficient — a strong internal-consistency test.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FD06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the traction/diffusion chain (at most CALIBRATED(1) one fluid scale in P5, documented)
- Engine namespaces actually used: law_VI::traction (ω_demand, traction_ratio_proton=12, wake channels ℓ=1/2/≥3), law_III (solid_angle_occluded), law_I (P_conv closure), law_V (low-Mach); ν referenced from FD02
- Phase thresholds (committed before run):
    P1 no-slip relaxes from pure-slip start, `λ_s ≲ ℓ_P` (kill if `λ_s ≫ ℓ_P`) · P2 `log δ`–`log x` slope 0.50 ± 0.03, `C_δ ≈ 5.0` within 2×
    P3 `C_f = 0.664/√Re_x` prefactor within 2×, slope −½ · P4 profile collapse <5% RMS, `H ≈ 2.59` · P5 finite `Re_x` (order ~5×10⁵), benchmark <5%, CALIBRATED ≤1
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces; **hand-set `u=0` at the wall instead of deriving it from traction**
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P1 finite slip `λ_s ≫ ℓ_P` in continuum limit | strengthen the traction grip via `T=3(W+1)`; recheck the fixed point | **KILL** (traction ≠ no-slip) | code `u=0` as a wall BC |
| P2 `δ` slope ≠ ½ | recheck the normal-diffusion-vs-advection balance | **KILL** (wrong penetration mechanism) | force the ½ slope |
| P3 `C_f` prefactor off >2× | recheck `τ_w = μ(∂u/∂y)` from the derived profile | **OPEN** the prefactor, cap at C | refit the drag law |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FD02 `ν`, FD03 transition) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in the Phase-1 native chain · coding no-slip as a wall BC rather than deriving it.

---

*FD06 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
