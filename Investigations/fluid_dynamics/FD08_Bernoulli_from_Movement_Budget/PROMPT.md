# FD08 — Bernoulli from the Movement Budget (convergence-pressure conservation along a streamline)

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/GM as fundamentals; no fields/wavefunctions/quarks/virtual-particles/ΛCDM/magnetons; certification labels on every result; translation test on every borrowed term; honesty over success; never repaint or fabricate — log OPEN.)*

---

## 1. Executive Summary

Bernoulli's principle — faster flow carries lower static pressure — is the most-cited invariant in classical fluid mechanics, yet in Spatial Displacement Theory the only ontology is a granular relay lattice of spations passing convergence throughput between neighbours at one tick (`c = ℓ_P/t_P`). **The thesis:** along a streamline the lattice carries a *fixed local convergence-pressure budget*; Bernoulli's law is a **budget partition**, not an independent axiom. The dynamic head `½ρv²` (organised displacement-transport energy) and the static pressure `P` draw on the *same* conserved convergence-pressure budget, so `½ρv² + P + ρgz = const` is convergence-pressure conservation along a streamline. **The question:** does integrating the FD01 SDT momentum balance along a streamline reproduce, term-for-term, the incompressible Bernoulli invariant, the Venturi pressure drop, the Pitot/stagnation relation `P₀ = P + ½ρv²`, and — crucially — does the cap connect to Law V's `v_circ² + v² = c²` so that incompressible Bernoulli is the *low-speed corner* of the same budget whose hard ceiling is `c²`? A clean reproduction with the correct pressure–velocity trade *sign* earns Class C (convergence); failure to produce the `½ρv² + P` invariant, or the wrong sign, is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** Picture a streamtube as a queue of spation cells, each holding the *same* total convergence-throughput budget. That budget can be spent two ways: as isotropic *static* push (`P`, the ambient occlusion pressure pressing in all directions) or as *organised* transport (`½ρv²`, the directed displacement-flux of the parcel). A cell cannot create budget; it can only re-partition it. Speed it up through a constriction and the directed share rises, so the isotropic share must fall — the static pressure drops. There is no "suction" and no attraction: the parcel is simply re-allocating a conserved ledger as it relays cell-to-cell at speed `c`. Bring the flow to rest against an obstacle (a Pitot mouth) and the *entire* budget reverts to static push: the stagnation pressure `P₀` is the whole ledger, the static `P` is what is left after the moving fraction `½ρv²` has been spent on transport.

**Key variables and dimensions.**
- `v(s)` — flow speed along streamline coordinate `s` [m·s⁻¹]
- `P(s)` — static convergence pressure field, native `P_conv` and its along-streamline value [Pa = kg·m⁻¹·s⁻²]
- `ρ` — mass (displacement-load) density [kg·m⁻³], from Law IV `V_disp`, *not* an imported fundamental
- `½ρv²` — dynamic head / directed transport budget [Pa]
- `ρgz` — gravitational head [Pa]; `g = v_surf²/R` is **SDT gravity** (Law-bridge), `g` in [m·s⁻²], `z` height [m] — **narrated via `g=v²/R`, never via G or M**
- `P₀` — stagnation (total) pressure [Pa]; `P₀ = P + ½ρv²` (+ `ρgz` if elevation varies)
- `B(s) = ½ρv² + P + ρgz` — the Bernoulli constant / convergence-pressure budget [Pa], constant along an inviscid streamline
- `c_s` — local sound speed [m·s⁻¹] (relay-stiffness speed, handed from FD05); `M = v/c_s` Mach number
- `γ` — adiabatic index of the working fluid (measured input for the compressible correction)
- `c = ℓ_P/t_P` — relay signal speed; the absolute Law-V ceiling

**Connection to SDT.** Static pressure `P` is the *isotropic* convergence push (Law I `P_conv`, the CMB-relay influx); the directed head `½ρv²` is the *anisotropic* fraction of the same throughput committed to transport (Law V partition). Conservation of the sum along a streamline is exactly the FD01 momentum balance with no dissipation, integrated along `s`. The gravitational head `ρgz` is the along-streamline work done against the SDT gravity field `g = v_surf²/R` (Law-bridge `koppa`, `g_surface`) — purely a `v²/R` quantity, no Newtonian `G` anywhere. The whole invariant is one statement: *the convergence-pressure ledger of a streamtube is conserved; speed is bought with static pressure and vice versa.*

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Movement budget (Law V).** `v_circ² + v_trans² = c²` (engine `law_V`) is the master ledger: every cell's velocity capacity is conserved and capped at `c`. Translational transport (`v_trans`) is bought from internal circulation (`v_circ`); the two cannot exceed `c²`. Bernoulli is this same partition expressed at the *continuum* level — directed head versus isotropic static push — with the fluid-mechanical ceiling `c_s` (and ultimately `c`) inherited from Law V.

2. **Convergence pressure (Law I, Law III).** Isotropic spation pressure `P_conv ≈ 2.46×10⁴⁸ Pa` (`law_I::P_conv`) is the ambient static field. Static `P` along a streamline is the *local* isotropic occlusion value (`law_III` occlusion); spending budget on directed transport reduces the isotropic remainder — there is no attractive term, only re-partition of a fixed throughput.

3. **Displacement-load = mass (Law IV).** Density `ρ` is reorganisation cost per volume (`ρ ∝ V_disp`-load), never kilograms-as-fundamental. It is the inertia that weights both `½ρv²` and `ρgz`.

4. **SDT gravity for the head term (Law-bridge).** The elevation head `ρgz` uses `g = v_surf²/R` (engine `bridge`, `g_surface`, `koppa = v²R/c²`). The investigation must derive/narrate the `ρgz` term from `g=v²/R` and *forbid* any `g = GM/R²` substitution; a depth-`z` (`z = ϟ/r`) framing of the head is the preferred SDT yardstick.

5. **FD01 streamline momentum balance.** Inviscid Euler limit of FD01, `ρ(∂v/∂t + (v·∇)v) = −∇P + ρg`, is the starting equation. Steady (`∂/∂t = 0`), inviscid (`ν → 0`, the FD01 Phase-4 Euler limit), projected onto the streamline direction `ŝ`.

**Governing relations to derive (no new fitted parameters).**

- *Streamline integration.* Take the steady inviscid FD01 momentum equation, dot with `ŝ`, and use `(v·∇)v·ŝ = v dv/ds` and `∇P·ŝ = dP/ds`, `g·ŝ = −g dz/ds`. Integrate along `s`:
  `d(½ρv²)/ds + dP/ds + ρg dz/ds = 0` ⟹ `½ρv² + P + ρgz = B = const`.
  Every term must trace to one SDT mechanism (budget partition); maintain a strict ledger.
- *Budget-partition identity.* Show `B` is the conserved convergence-pressure budget of the streamtube — i.e. that `½ρv²` and `P` are two draws on one ledger (Law V at continuum scale), so the *sign* of the pressure–velocity trade is forced: `dP/dv = −ρv < 0`.
- *Stagnation.* Set `v → 0` (parcel brought to rest, full ledger reverts to static): `P₀ = P + ½ρv²` (constant elevation). This is the Pitot reading; derive it as "the whole budget is now isotropic".
- *Venturi.* Continuity (`ρ A v = const`, FD01 incompressible) + Bernoulli ⟹ pressure drop across a constriction; predict `ΔP = ½ρ(v₂² − v₁²)` with `v₂ = v₁ A₁/A₂`.
- *Law-V continuity at the ceiling.* Show incompressible Bernoulli is the leading order of the budget expansion in `v/c_s` and `v/c`; compressible/relativistic corrections appear as the flow approaches `c_s` then `c`. The compressible stagnation relation must emerge as the next order:
  `P₀/P = (1 + (γ−1)/2 · M²)^{γ/(γ−1)}`, reducing to `P₀ = P + ½ρv²` as `M → 0`.

The deliverable of §3 is a chain in which the conserved budget `B` is a Law-V partition, each Bernoulli term maps to exactly one lattice mechanism, the pressure–velocity trade has the forced negative sign, and the incompressible form sits as the `M→0` corner of a single ceiling-capped budget. Any surplus term, missing term, or wrong sign is a falsifier.

---

## 4. Investigation Strategy

Five phases, each gated. Run them in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass).

### Phase 1 — Streamline integration of the FD01 Euler balance
- **Goal.** Derive `½ρv² + P + ρgz = const` analytically from the steady, inviscid FD01 momentum equation projected on a streamline — no assumed energy theorem, only the momentum balance integrated along `s`.
- **Method.** Start from FD01's Euler limit (Phase-4 of FD01). Dot with `ŝ`; substitute `(v·∇)v·ŝ = v dv/ds`; integrate. Tag every term DERIVED / MEASURED-INPUT / CALIBRATED(n) in a parameter ledger (R2). Explicitly narrate `ρgz` from `g = v_surf²/R` (Law-bridge), and *flag any G/M intrusion as an automatic R0 violation*. Cite FD01 (root) and Law V upstream.
- **Success metric.** The integral closes to `½ρv² + P + ρgz = B` with no surplus term and a constant `B` along the streamline; the `ρgz` term is written purely in `g=v²/R` form. **Checkpoint C1:** invariant derived from momentum balance alone, zero fitted parameters, no G/M anywhere.

### Phase 2 — Budget-partition identity & the forced sign (the core gate)
- **Goal.** Show `B` is the conserved convergence-pressure budget, i.e. that `½ρv²` (directed) and `P` (isotropic) are two draws on the *same* ledger — the continuum image of Law V's `v_circ² + v² = c²`.
- **Method.** Map static pressure `P` to the isotropic share of `P_conv` and `½ρv²` to the committed directed share; show their sum is the conserved per-streamtube throughput. Derive `dP/dv = −ρv` and confirm the trade is strictly negative (faster ⟹ lower static `P`). Tabulate the budget bijection (Law-V term ↔ Bernoulli term).
- **Success metric.** `B = const` reproduced as a partition of one ledger; `dP/dv < 0` analytically *and* numerically on a model streamtube. **Checkpoint C2 (core gate):** budget identity holds and the pressure–velocity sign is correct. A positive `dP/dv` (faster ⟹ higher static P) is an immediate Class F.

### Phase 3 — Venturi and stagnation/Pitot reproduction
- **Goal.** Reproduce the two canonical applications from the *same* invariant, no re-derivation.
- **Method.** (a) **Venturi:** combine incompressible continuity (`A₁v₁ = A₂v₂`, FD01) with Phase-1 Bernoulli; predict `ΔP = ½ρ(v₂² − v₁²)` for a stated area ratio and inlet condition. (b) **Stagnation:** set `v→0` in the budget; predict `P₀ = P + ½ρv²`. Use ONE measured fluid (e.g. air or water at a stated `ρ`, `T`) only to *evaluate* the prediction, not to tune the law — tag CALIBRATED(0) if no coefficient is fitted, CALIBRATED(1) only if one scale is set and document it.
- **Success metric.** Predicted Venturi `ΔP` and Pitot `P₀` match textbook/standard formulas exactly (analytic) and a numerical streamtube evaluation to <1%. **Checkpoint C3.**

### Phase 4 — Law-V continuity at the c-ceiling (compressible correction)
- **Goal.** Show incompressible Bernoulli is the low-speed corner of the *same* budget whose hard ceiling is `c²`, and recover the compressible stagnation correction as the next order.
- **Method.** Expand the budget in `M = v/c_s` (relay-stiffness `c_s` handed from FD05) and `v/c` (Law V). Show the `O(M²)` term reproduces `P₀/P = (1 + (γ−1)/2 · M²)^{γ/(γ−1)}` to leading order, with `½ρv² + P` as the `M→0` limit. Identify where the absolute Law-V ceiling `c` (not just `c_s`) caps the budget — the relativistic corner.
- **Success metric.** Compressible correction reproduced to the stated order; incompressible Bernoulli recovered as `M→0`; the budget remains bounded as `v→c` (Law V). **Checkpoint C4.**

### Phase 5 — Two-stream verification & downstream handshake
- **Goal.** Confirm the invariant numerically on a model streamtube and hand the pressure field to FD07 (lift) and the stagnation result to FD09 (drag).
- **Method.** Build a 1-D steady streamtube with varying area `A(s)`; integrate continuity + Bernoulli; verify `B(s) = const` to machine precision (R3 two-stream: analytic invariant vs numerical integration). Cross-check the Venturi/Pitot numbers against an independent reference value (textbook worked example or standard correlation). Predict each number and commit it to the run log *before* comparing (R1).
- **Success metric.** `B(s)` constant along the tube to machine precision; Venturi/Pitot within stated tolerance; pressure field exported for FD07/FD09. **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Bernoulli derived natively | Phase-1 invariant from momentum balance with no surplus/missing term AND Phase-2 budget identity with `dP/dv<0` AND Venturi+Pitot exact AND compressible correction recovered to leading order AND `ρgz` purely `g=v²/R` (no G/M), all CALIBRATED(0). |
| **C (QUALIFIED — convergence)** | Bernoulli reproduced, one scale set | Invariant + budget identity + correct sign + Venturi/Pitot match within tolerance, with at most CALIBRATED(1) (one fluid scale fitted and documented); compressible corner shown qualitatively. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | Invariant reproduced and sign correct, but the compressible correction or the `c_s` handshake (FD05) is PENDING; dimensionally closed, not yet bijective to Law V at coefficient level. |
| **F (FAIL)** | Mechanism falsified | Budget conservation does NOT yield the `½ρv²+P` invariant (surplus/missing term at leading order), OR predicts the wrong sign of the pressure–velocity trade (`dP/dv>0`), OR the `ρgz` head can only be obtained via G/M (R0 violation with no SDT route). |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd08_bernoulli_budget.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-2 `dP/dv` sign check; Phase-3 Venturi + Pitot evaluation; Phase-4 compressible-correction reduction; Phase-5 1-D streamtube `B(s)=const` two-stream check; prints its own verdict. **No new constants redefined.** |
| `fd08_results.txt` | Plain text | Run output: `B(s)` constancy table (Phase 5), `dP/dv` sign result (Phase 2), Venturi `ΔP` and Pitot `P₀` predicted-vs-reference (Phase 3), compressible `P₀/P` vs `M` table (Phase 4). |
| `FD08_DERIVATION.md` | Markdown | The full streamline integration: FD01 Euler balance → Bernoulli invariant; the Law-V budget-partition bijection table; Venturi/stagnation/compressible derivations; the `g=v²/R` narration of `ρgz`; parameter ledger. |
| `FD08_VERDICT.md` | Markdown | A–F classification with the deciding metric; provenance × correspondence audit; what is DERIVED vs CALIBRATED(n) vs PENDING; downstream handoffs to FD07/FD09. |

---

## 7. Dependencies & References

**Upstream (required):**
- **Law V (movement budget)** — `v_circ² + v² = c²` (engine `law_V`); the master ledger that Bernoulli is the continuum partition of, and the source of the `c`-ceiling.
- **FD01 (Navier–Stokes from Spation Relay)** — the root; FD08 starts from FD01's steady inviscid Euler limit and incompressible continuity. FD08 cannot reach Class A if FD01 is not at least Class C.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_V` (budget, ceiling), `law_I::P_conv` (static pressure field), `law_III` (occlusion → `∇P`), `law_IV` (`V_disp` → ρ), `bridge` (`g_surface = v²/R`, `koppa = v²R/c²`, depth `z = ϟ/r` for the head term).

**Downstream (unblocked by this):**
- **FD07 (lift)** — consumes the streamline pressure field derived here.
- **FD09 (stagnation / drag)** — consumes the stagnation/Pitot result `P₀ = P + ½ρv²`.

**Related:** **FD05 (compressible / sound)** — hands the relay-stiffness sound speed `c_s` used in the Mach expansion (Phase 4); CQ08 (GPI / inertial term inherited via FD01).

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Invariant (Phase 1) | Momentum balance integrates to `½ρv²+P+ρgz` | Exactly this invariant, `B=const`, no surplus/missing term | A surplus or missing leading-order term ⟹ Bernoulli not the streamline integral of the SDT balance ⟹ Class F |
| F2 — Trade sign (Phase 2) | Budget partition forces `dP/dv = −ρv < 0` | Faster flow ⟹ lower static `P`, analytically and numerically | `dP/dv > 0` (faster ⟹ higher static P) ⟹ partition mis-mapped ⟹ Class F |
| F3 — Venturi (Phase 3) | Continuity + Bernoulli give the constriction drop | `ΔP = ½ρ(v₂²−v₁²)` matches reference <1% | Wrong magnitude or sign of `ΔP` ⟹ continuity/budget coupling wrong |
| F4 — Stagnation (Phase 3) | Full budget reverts to static at rest | `P₀ = P + ½ρv²` reproduced exactly | `P₀ ≠ P + ½ρv²` ⟹ stagnation not "whole-budget isotropic" |
| F5 — c-ceiling continuity (Phase 4) | Incompressible Bernoulli is the `M→0` corner of the Law-V budget | `P₀/P = (1+(γ−1)/2·M²)^{γ/(γ−1)}` → `P+½ρv²` as `M→0`; budget bounded as `v→c` | Incompressible form not recovered as `M→0`, or budget unbounded at `v→c` ⟹ Law-V continuity broken |

---

## 9. Implementation Notes

- **Numerical method.** Phase 5 is a 1-D steady streamtube: prescribe area `A(s)`, solve continuity `ρAv = const` for `v(s)`, then `P(s) = B − ½ρv² − ρgz`, and verify `B(s)` returns constant to machine precision. Use double precision. This is a *demonstration of the invariant*, not a CFD solver — keep `s`-grids small (`N ≤ 1024`). For the compressible check (Phase 4), evaluate `P₀/P` over an `M` sweep `0 → 0.9` and confirm the `M→0` limit numerically.
- **No borrowed units.** Express the budget in SDT-native yardsticks where possible (`P_conv` fraction, depth `z = ϟ/r`); evaluate against measured fluid `ρ`, `γ`, `c_s` in their measured units only as the *convergence check*, never as the derivation's input.
- **Testing strategy.** Three independent two-stream checks (R3): (i) `B(s)` constancy to machine precision; (ii) `dP/dv` sign across a constriction; (iii) Venturi/Pitot predicted-vs-reference. Predict each number and commit it to the run log *before* comparing (R1). Anti-numerology (R5): no free integer or π inserted to force a match — every coefficient traces to lattice geometry / Law V or is flagged CALIBRATED.
- **Gravity head guard.** The `ρgz` term MUST be computed from `g = v_surf²/R` (Law-bridge). Any `GM/R²` substitution is an automatic R0 violation — assert it cannot enter the code path; document the `g=v²/R` value used.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd08_bernoulli_budget.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd08_bernoulli_budget.cpp -o fd08` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** Plot `v(s)`, `P(s)`, and `B(s)` along the streamtube (B flat = pass); the `P`-vs-`v` curve showing the negative trade; and the `P₀/P`-vs-`M` compressible curve with the incompressible `1 + ½γM²` tangent at the origin.
- **Author attribution:** James Christopher Tyndall, Melbourne. The standard-FD results (Bernoulli, Venturi, Pitot, compressible stagnation) are the CONVERGENCE targets to *reproduce*, never inputs to *borrow*.
