# FD01 — Navier–Stokes from Spation Relay (the Fluid-Dynamics root)

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/kg fundamentals; no fields/wavefunctions/quarks/ΛCDM; certification labels on every result; translation test on every borrowed term; honesty over success).*

---

## 1. Executive Summary

The incompressible Navier–Stokes (NS) equation is the empirical bedrock of classical fluid mechanics, yet in Spatial Displacement Theory the only ontology is a granular relay lattice of spations passing convergence throughput between contacting neighbours at one tick (`c = ℓ_P/t_P`). If SDT is complete, NS cannot be an imported axiom — it must *fall out* of coarse-graining per-spation contact relay. **The question:** does the continuum limit of spation relay mechanics reproduce, term-for-term, `∂v/∂t + (v·∇)v = −∇P/ρ + ν∇²v` with `∇·v = 0`, and the Euler and Stokes limits as special cases? This matters because NS is the *root* of every downstream FD investigation (viscosity FD02, sound FD05, turbulence, boundary layers); if the root is borrowed rather than derived, the whole branch is contaminated. The expected outcome is a native coarse-graining in which each NS term maps to one lattice mechanism, with no extra or missing terms, the viscosity coefficient handed to FD02, and incompressibility emerging as spation-number conservation in the low-Mach limit. A clean reproduction earns Class C (convergence); a coarse-grain that produces a term NS lacks, or drops one NS has, is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** Picture the spation lattice as an enormous lattice of touching ball bearings, each holding a fixed quantum of convergence throughput and passing it to whichever neighbour it contacts, one handoff per tick. A "fluid parcel" is not a substance riding on the lattice — it is a *coarse-grained velocity field* of the lattice cells themselves (or of vortex-knot matter advected through them). When a region is pushed, that push is relayed cell-to-cell at speed `c`; momentum spreads by the same nearest-neighbour relay that carries every force in SDT (Law III occlusion). Macroscopic flow is therefore the smoothed, block-averaged bookkeeping of discrete relay handoffs — exactly the move from molecular dynamics to NS, but with spations in place of molecules and convergence throughput in place of kinetic momentum.

**Key variables and dimensions.**
- `v(x,t)` — coarse-grained flow velocity field [m·s⁻¹]
- `P(x,t)` — convergence pressure field, native `P_conv` and its gradients [Pa = kg·m⁻¹·s⁻²]
- `ρ` — mass (displacement-load) density [kg·m⁻³], from Law IV `V_disp`, *not* an imported fundamental
- `ν` — kinematic viscosity [m²·s⁻¹]; `μ = ρν` dynamic viscosity [Pa·s]
- `ℓ_P`, `t_P`, `c = ℓ_P/t_P` — relay lattice scale, tick, signal speed
- `Ma = |v|/c_s` — Mach number; incompressible limit is `Ma → 0`
- `Re = |v|L/ν` — Reynolds number, the ratio of advection to relay diffusion

**Connection to SDT.** Pressure gradient `−∇P/ρ` is the *native* convergence-pressure gradient (Law I `P_conv`, the CMB push); it requires no "attraction". Advection `(v·∇)v` is displacement transport — knots/cells carrying their own velocity field along. Relay diffusion `ν∇²v` is the lattice smoothing of velocity perturbations by nearest-neighbour handoff, capped at `c`. Incompressibility `∇·v = 0` is spation-number conservation when flow is slow against the relay tick. The whole equation is one statement: *coarse-grained convergence-throughput bookkeeping in a granular relay medium.*

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Granular Pulse Invariant (CQ08).** Every spation receives and passes one relay pulse per `ℓ_P` per `t_P` from each contacting direction; the rate is invariant under velocity and acceleration. This fixes the only signal speed: `c = ℓ_P/t_P`. Constant velocity is free (symmetric pulse input); acceleration costs (pulse asymmetry `δ = a·t_P/c`). This *is* Newton I–III at the cell level and supplies the inertial term `∂v/∂t + (v·∇)v`.

2. **Occlusion / convergence pressure (Law I, Law III).** Isotropic spation pressure `P_conv ≈ 2.46×10⁴⁸ Pa` (`= Φ/ℓ_P³`, engine `law_I::P_conv`) is the ambient field; *gradients* in the effective relay throughput, `∇P`, are the only thing that can net-accelerate a parcel — the force is `−∇P/ρ` per unit mass. No attractive term exists; pressure differences are occlusion differences (`law_III::solid_angle_occluded`).

3. **Displacement-load = mass (Law IV).** Density `ρ` is reorganisation cost per volume, `ρ ∝ V_disp`-load, never kilograms-as-fundamental. This is the inertial mass that the momentum equation divides by.

4. **Movement budget (Law V).** `v_circ² + v_trans² = c²` (engine `law_V`) caps every velocity at `c` and ties translational flow to internal circulation — the low-Mach expansion parameter is `v_trans/c`, and `∇·v = 0` is its leading-order consequence.

5. **Relay momentum diffusion.** A velocity perturbation in cell *i* is shared with its `2D` contacting neighbours over one tick; the discrete relay operator is the lattice Laplacian, whose continuum limit is `∇²`. The diffusion coefficient is `ν = (fraction) · ℓ_P² / t_P = (fraction)·ℓ_P·c`, a *length × speed* — its numerical value is fixed by FD02, not fitted here. SDT transport scaling (B16) predicts a `ν ∝ √T` temperature law (exponent 0.5) that FD02 must reproduce.

**Governing relations to derive (no new fitted parameters).**

- *Coarse-graining operator.* Block-average the per-cell velocity over a box of side `L ≫ ℓ_P`: `v(x,t) = ⟨u_i⟩_box`. Show the discrete relay-update rule (handoff + asymmetry) becomes, to leading order in `ℓ_P/L` and `v/c`, a PDE.
- *Continuity.* Spation-number / displacement-load conservation → `∂ρ/∂t + ∇·(ρv) = 0`; in the low-Mach limit `ρ ≈ const` ⟹ `∇·v = 0`.
- *Momentum.* The relay-update expansion must yield, with no surplus terms:
  `∂v/∂t + (v·∇)v = −(1/ρ)∇P + ν∇²v`.
- *Closure.* `ν` is `(geometry-fixed coefficient)·ℓ_P·c`; the coefficient is computed in FD02 and merely *referenced* here. The pressure `P` is `P_conv`-derived (Law I), not an equation of state inserted by hand.

The deliverable of §3 is a chain in which **every** NS term has exactly one lattice mechanism and **every** lattice mechanism lands on exactly one NS term — a bijection. Any leftover is a falsifier.

---

## 4. Investigation Strategy

Five phases, each gated. Run them in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass).

### Phase 1 — Discrete relay model (the L1 update rule)
- **Goal.** Write down, in SDT primitives only, the per-spation contact-relay update: each cell holds a velocity (coarse momentum) and a held throughput; per tick it exchanges with its `2D` contacting neighbours and registers the GPI acceleration asymmetry `δ`. No PDE yet — only the discrete rule on a lattice of spacing `ℓ_P`, tick `t_P`.
- **Method.** Formalise the update operator `u_i(t+t_P) = R[{u_j(t)}, ∇P_i, δ_i]`. Tag every constant DERIVED / MEASURED-INPUT / CALIBRATED(n) in a parameter ledger (R2). Cite CQ08 (GPI), CQ10 (pulse propagation), ROOT-SIM (per-spation contact mechanics) as upstream.
- **Success metric.** The discrete rule conserves cell count and total throughput exactly (machine precision in a small-N numerical check), and reduces to free streaming when `∇P = 0` and `δ = 0`. **Checkpoint C1:** rule is closed and conservative, with zero free parameters beyond the FD02-pending `ν` coefficient.

### Phase 2 — Continuum coarse-graining (the term-by-term bijection)
- **Goal.** Take the Phase-1 rule to the continuum via a Chapman–Enskog-style / Taylor expansion in `ℓ_P/L` and `v/c`, and read off the emergent PDE.
- **Method.** Expand `R` to second order in the small parameters; collect terms by tensor order. Map: streaming → `∂v/∂t + (v·∇)v`; pressure asymmetry → `−∇P/ρ`; neighbour-sharing Laplacian → `ν∇²v`; count conservation → continuity. Maintain a strict ledger of which expansion term produced which PDE term.
- **Success metric.** The leading-order PDE is *exactly* incompressible NS — no surplus term (e.g. no spurious `∇(∇·v)`, no odd-order dispersion at this order), no missing term. **Checkpoint C2 (the core gate):** bijection holds. If a term survives that NS lacks, log it as a candidate falsifier and proceed to characterise it (it may be a genuine SDT-distinct prediction or a kill).

### Phase 3 — Incompressibility from spation-number conservation
- **Goal.** Derive `∇·v = 0` rather than assume it.
- **Method.** From continuity `∂ρ/∂t + ∇·(ρv) = 0` plus Law V (`v_trans/c → 0`), show density fluctuations are `O(Ma²)` and vanish in the low-Mach limit, leaving `∇·v = 0`. Identify the next-order compressible correction (handed to FD05).
- **Success metric.** `‖∇·v‖` scales as `Ma²` in a numerical sweep of the Phase-1 lattice; extrapolates to 0. **Checkpoint C3:** incompressibility is a derived limit, with the `Ma²` correction quantified.

### Phase 4 — Limit recovery (Euler and Stokes)
- **Goal.** Recover the two textbook reductions from the *same* derivation, no re-derivation.
- **Method.** Set the relay-smoothing coefficient `ν → 0` (perfect handoff, no diffusion) ⟹ Euler `∂v/∂t + (v·∇)v = −∇P/ρ`. Set advection `(v·∇)v → 0` (creeping flow, `Re ≪ 1`) ⟹ Stokes `∂v/∂t = −∇P/ρ + ν∇²v`. Confirm both as limits of the Phase-2 PDE, not separate models.
- **Success metric.** Both limits drop out analytically with the correct term set; a numerical Stokes-flow test (e.g. relaxation of a perturbation) matches the analytic Stokes solution to <1% (R3 two-stream: analytic vs lattice). **Checkpoint C4.**

### Phase 5 — Coefficient handshake & two-stream verification
- **Goal.** Confirm the viscosity coefficient emitted by the coarse-graining is *identical* to FD02's independently-computed lattice value, and that the whole chain reproduces a measured benchmark.
- **Method.** Compute `ν = (coefficient)·ℓ_P·c` symbolically here; compare to FD02. Calibrate the dimensionless coefficient against ONE measured fluid (e.g. water or air `ν` at a stated `T`) — tag CALIBRATED(1) explicitly if a single scale must be set, and document it. Run an independent macroscopic check: Poiseuille or Taylor–Green decay rate predicted from the derived `ν` vs measured/DNS value.
- **Success metric.** FD01 and FD02 `ν` coefficients agree to <1%; benchmark match within stated tolerance with calibration count ≤ 1. **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | NS derived natively | Phase-2 bijection exact AND `ν` coefficient DERIVED from lattice geometry (CALIBRATED(0)) AND Euler+Stokes limits recovered AND benchmark match <1%. |
| **C (QUALIFIED — convergence)** | NS reproduced, one scale set | Bijection exact, Euler+Stokes recovered, `ν` matches FD02 <1%, benchmark match within tolerance with CALIBRATED(1) (one fluid scale fitted, documented). |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | PDE form reproduced numerically but a coefficient (e.g. the diffusion fraction) is PENDING FD02/ROOT-SIM; dimensionally closed, not yet bijective at coefficient level. |
| **F (FAIL)** | Mechanism falsified | Coarse-graining produces a term NS lacks at leading order (and it is not a defensible SDT-distinct prediction), OR drops a term NS has, OR the emitted `ν` disagrees with FD02 by >10% with no reconciling mechanism. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd01_navier_stokes_relay.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-1 discrete relay lattice; Phase-3 `Ma²` incompressibility sweep; Phase-4 Stokes-relaxation two-stream check; prints its own verdict. **No new constants redefined.** |
| `fd01_results.txt` | Plain text | Run output: conservation check (Phase 1), `‖∇·v‖` vs `Ma` table (Phase 3), analytic-vs-lattice Stokes error (Phase 4), `ν` coefficient and FD02 comparison (Phase 5). |
| `FD01_DERIVATION.md` | Markdown | The full term-by-term coarse-graining: discrete rule → continuum PDE, the bijection table, incompressibility and limit derivations, parameter ledger. |
| `FD01_VERDICT.md` | Markdown | A–F classification with the metric that decided it; provenance × correspondence audit; what is DERIVED vs CALIBRATED(n) vs PENDING; downstream handoffs. |

---

## 7. Dependencies & References

**Upstream (required):**
- **ROOT-SIM** — per-spation contact mechanics, the L0/L1 root (never yet computed); Phase 1 builds the relay rule that ROOT-SIM must ultimately ground.
- **CQ08 (Granular Pulse Mechanics)** — GPI, `F = ma`, Newton I–III at the cell level; source of the inertial term and the acceleration asymmetry `δ`.
- **CQ10 (Lattice Pulse Propagation)** — pulse propagation in the lattice; supplies the relay-update kinematics.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_I::P_conv` (pressure field), `law_III::solid_angle_occluded` (occlusion → `∇P`), `law_IV` (`V_disp` → ρ), `law_V` (`v_circ²+v_trans²=c²`, low-Mach parameter), `bridge::koppa`.

**Downstream (unblocked by this):**
- **FD02 (viscosity)** — receives/cross-checks the `ν` coefficient; FD01 cannot reach Class A without FD02's independent value.
- **FD05 (compressible / sound)** — receives the `Ma²` correction dropped in Phase 3.
- **ALL other FD0x** — every later fluid investigation rests on this root.

**Related:** B16 (transport exponents, `ν ∝ √T`, exponent 0.5); Law VI topology/traction (`law_VI::topology`, `law_VI::traction::ω_demand`, `law_VI::confinement`) for vortex-knot advection in later phases.

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Bijection (Phase 2) | NS terms ↔ lattice mechanisms are one-to-one | Coarse-grain yields exactly `∂v/∂t+(v·∇)v=−∇P/ρ+ν∇²v`, no surplus/missing term | A surplus leading-order term that is not a defensible SDT-distinct prediction, or a missing term ⟹ NS not the continuum of relay ⟹ Class F |
| F2 — Incompressibility (Phase 3) | `∇·v=0` is a low-Mach limit | `‖∇·v‖ ∝ Ma²`, → 0 as `Ma→0` | `‖∇·v‖` finite at `Ma→0`, or wrong power ⟹ continuity mis-derived |
| F3 — Euler limit (Phase 4) | `ν→0` gives Euler | Exact inviscid form recovered, term set intact | Extra/missing term in inviscid limit ⟹ advection term mis-mapped |
| F4 — Stokes limit (Phase 4) | advection→0 gives Stokes | Lattice relaxation matches analytic Stokes <1% (two-stream) | >1% disagreement ⟹ relay-diffusion ≠ `ν∇²` |
| F5 — Coefficient handshake (Phase 5) | FD01 `ν` = FD02 `ν` | Agreement <1% | Disagreement >10% with no reconciling mechanism ⟹ Class F (relay diffusion not the viscosity mechanism) |

---

## 9. Implementation Notes

- **Numerical stability.** The Phase-1 lattice is an explicit relay update; respect a CFL-type bound (`c·t_P/ℓ_P = 1` exactly at the relay scale, so coarse-grained sub-steps must keep `|v|Δt/Δx < 1`). Use double precision; for the Stokes relaxation, an implicit or sub-cycled diffusion step avoids the `ν Δt/Δx² ≤ 1/2` stability cap. Keep test lattices small (e.g. 1-D and 2-D, `N ≤ 256`) — this is a *demonstration of mechanism*, not a production CFD solver.
- **Testing strategy.** Three independent two-stream checks (R3): (i) conservation of cell count and throughput to machine precision; (ii) `∇·v` vs `Ma` power-law fit; (iii) analytic Stokes solution vs lattice relaxation. Predict each number and commit it to the run log *before* comparing (R1). Anti-numerology (R5): no free integer or π inserted to force the coefficient — it must come from lattice geometry or be flagged CALIBRATED.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd01_navier_stokes_relay.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd01_navier_stokes_relay.cpp -o fd01` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** Dump the 2-D velocity field and `∇·v` to CSV for a quick quiver/heatmap; plot the Taylor–Green vortex decay envelope (predicted vs measured) and the `‖∇·v‖`-vs-`Ma` log-log fit. A side-by-side of the same initial condition under Euler (`ν=0`) and NS (`ν>0`) makes the limit recovery visually obvious.
- **Author attribution:** James Christopher Tyndall, Melbourne. The standard-FD result (NS, Euler, Stokes) is the CONVERGENCE target to *reproduce*, never an input to *borrow*.
