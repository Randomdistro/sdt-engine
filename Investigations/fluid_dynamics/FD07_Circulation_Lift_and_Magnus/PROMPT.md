# FD07 — Circulation, Lift, and the Magnus Force from Differential Occlusion

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only: {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} plus measured observables in their measured units; no G/M/GM as fundamentals; no wavefunctions, fields-as-primitives, quarks/gluons, virtual particles, dark matter/energy, ΛCDM, or magnetons; certification labels DERIVED / COMPUTED / CALIBRATED(n) / OBSERVED / PENDING on every result; the audit spine A–F; the translation test on every borrowed term; honesty over success; never repaint or fabricate — log OPEN.)*

---

## 1. Executive Summary

Lift is the most consequential force in aerodynamics, yet the textbook derivation rests on an *imposed* bound circulation `Γ` and the Kutta condition asserted by fiat. In Spatial Displacement Theory the only ontology is a granular relay lattice of spations passing convergence throughput at one tick (`c = ℓ_P/t_P`); a body in flow is a vortex-knot obstacle that occludes that throughput. **The thesis:** a lifting or spinning body sets up an *asymmetric* spation wake — faster relay / lower occlusion on one side, slower / higher on the other (the CQ14 ℓ=2 rotational traction channel). The bound circulation `Γ` is the net differential traction around the body; the Kutta–Joukowski lift `L = ρ U Γ` is the **momentum-flux (occlusion) imbalance** between the two sides, resolved transverse to the flow. The Magnus force on a spinning cylinder is the same differential relay-drag. The Kutta condition is recovered as a wake **relay-continuity** requirement: the lattice cannot relay an infinite velocity around a sharp trailing edge. **The question:** does the occlusion asymmetry reproduce `L = ρ U Γ`, the thin-airfoil slope `dC_L/dα = 2π`, the correct Magnus sign and magnitude, and the Kutta condition — with no borrowed circulation? Correct sign + slope = Class C; wrong sign, slope ≠ 2π, or no Kutta condition = a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** Picture the lattice streaming past a body. On a cambered airfoil at angle of attack `α`, or on a cylinder spinning with surface speed `U_s`, the local relay is *biased*: where the surface motion (or camber-induced acceleration) adds to the oncoming flow, the lattice cells relay faster and the occlusion (static convergence push) is lower; on the opposite face the relay is slower and the occlusion higher. This is the continuum image of the CQ14 ℓ=2 traction channel — the lattice's organised, two-lobed *circulation* response to a spinning vortex (as distinct from the ℓ=1 radial channel that gives ordinary radial occlusion). The net swirl threaded around the body is the bound circulation `Γ`; the pressure (occlusion) deficit on the fast side, integrated over the body and projected transverse to `U`, is the lift. There is no attraction and no "suction": the body simply re-partitions a conserved relay budget so that one face carries less isotropic push than the other.

**Key variables and dimensions.**
- `U` — free-stream (oncoming) flow speed [m·s⁻¹]
- `α` — angle of attack [rad]
- `Γ = ∮ v·dl` — bound circulation around the body [m²·s⁻¹]
- `L` — lift per unit span (2-D) [N·m⁻¹]; or total lift [N]
- `ρ` — fluid mass (displacement-load) density [kg·m⁻³], from Law IV `V_disp`, not an imported fundamental
- `c_L = L / (½ρU²·chord)` — lift coefficient [–]; `dC_L/dα` lift-curve slope [rad⁻¹]
- `Ω`, `U_s = Ω a` — angular and surface speed of a spinning cylinder/ball of radius `a` [s⁻¹], [m·s⁻¹]
- `S = U_s/U` — spin ratio (Magnus parameter) [–]
- `ΔP(θ)` — fore/aft occlusion (static-pressure) asymmetry around the body [Pa]
- `κ = h/m` — FD02 circulation quantum [m²·s⁻¹] (for the quantized-vortex limit)
- `P_conv ≈ 2.46×10⁴⁸ Pa` — ambient isotropic convergence pressure (Law I)
- `c = ℓ_P/t_P` — relay signal speed; the absolute Law-V ceiling

**Connection to SDT.** The static pressure on each face is the *local isotropic* fraction of `P_conv` (Law I, Law III occlusion); the circulation `Γ` is the *anisotropic ℓ=2* fraction committed to swirl (CQ14 traction). Lift is the transverse component of the momentum-flux imbalance these two faces relay — `law_III` occlusion (`F = (π/4) P_eff R₁² R₂² / r²`) carries momentum, and an *asymmetric* occlusion field carries net transverse momentum. The Kutta condition is the lattice's refusal to relay a singular velocity at a sharp edge (a relay-continuity bound). The whole result is one statement: *a body that biases the lattice's relay asymmetrically threads a bound circulation, and the resulting occlusion imbalance is lift.*

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Occlusion force is a momentum flux (Law III).** `F = (π/4) P_eff R₁² R₂² / r²` (engine `law_III`) is occluded convergence pressure — a *push*, never an attraction. A body in flow occludes the lattice; if that occlusion is **fore/aft symmetric** there is drag but no transverse force. Lift therefore *requires* a left/right (suction-side/pressure-side) asymmetry in the occlusion field. The transverse resultant of the asymmetric occlusion is the lift.

2. **The ℓ=2 rotational traction channel (CQ14, Law VI).** `law_VI::traction` separates the lattice's response to a vortex into a radial `ℓ=1` channel (ordinary occlusion) and an organised two-lobed `ℓ=2` *circulation* channel — the lattice's swirl response to spin. Bound circulation `Γ` is the continuum coarse-graining of this `ℓ=2` traction wrapped around the body; it is *induced*, not imposed.

3. **Movement budget (Law V).** `v_circ² + v_trans² = c²` (engine `law_V`) caps the swirl: the bound circulation cannot make any lattice cell exceed `c`. This forbids singular velocities — the seed of the Kutta condition — and sets the relativistic corner of the lift law.

4. **Displacement-load = mass (Law IV).** `ρ` is reorganisation cost per volume (`ρ ∝ V_disp`), never kilograms-as-fundamental; it weights both the momentum flux `ρU` and the bound swirl.

5. **Circulation quantum (FD02).** In the quantized-vortex limit, bound circulation is set by `κ = h/m` (FD02); the smooth aerodynamic `Γ` is the many-quantum continuum of this `κ`.

**Governing relations to derive (no new fitted parameters).**

- *Lift as occlusion asymmetry (the core derivation).* Take the steady occlusion field around a 2-D body and split it into a symmetric part (drag) and an antisymmetric part driven by the `ℓ=2` traction (lift). The asymmetric static-pressure field `ΔP(θ)` integrated around the surface, projected onto the lift direction, must collapse to
  `L = ρ U Γ` (Kutta–Joukowski, per unit span),
  with `Γ` the net `ℓ=2` traction circulation. Every factor must trace to one SDT mechanism (occlusion → `ρU`; traction → `Γ`); maintain a strict ledger. **The sign is forced:** lift points *toward the low-occlusion (fast-relay) face*.
- *Thin-airfoil slope.* For a thin flat plate at small `α`, the relay asymmetry induced by the angle of attack threads `Γ = π U c α` (chord `c`), giving `c_L = 2π α` and hence the convergence target
  `dC_L/dα = 2π` per radian.
  Show the `2π` emerges from the ℓ=2 channel geometry, not inserted by hand (anti-numerology R5).
- *Kutta condition as relay continuity.* Show that an unpinned rear stagnation point would demand a singular relay velocity at the sharp trailing edge, violating the Law-V ceiling `v ≤ c`; the lattice resolves this by pinning the rear stagnation at the trailing edge — the Kutta condition is the relay-continuity bound, not a separate axiom. `Γ` is then *uniquely fixed* by this continuity (the value FD06 supplies via the boundary layer).
- *Magnus force.* For a spinning cylinder (radius `a`, surface speed `U_s = Ω a`), the spin biases the relay directly: bound `Γ = 2π a U_s` (continuum of the surface drag), giving `L = ρ U Γ = 2π ρ a U U_s` per unit span. Predict the **sign** (lift toward the side where surface motion adds to the flow) and order of magnitude versus measured Magnus data.
- *Quantized limit (optional).* Connect bound `Γ` to `κ = h/m` (FD02): `Γ = N κ` for `N` bound vortex quanta; the classical airfoil is `N ≫ 1`.

The deliverable of §3 is a chain in which lift is the transverse resultant of an `ℓ=2`-driven occlusion asymmetry, `Γ` is induced (not imposed), the Kutta condition is relay continuity (Law V), the thin-airfoil slope is `2π` from channel geometry, and the Magnus sign/magnitude follow from the same differential relay-drag. Any wrong sign, a slope ≠ `2π`, or a missing Kutta condition is a falsifier.

---

## 4. Investigation Strategy

Four phases, each gated. Run them in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass).

### Phase 1 — Occlusion asymmetry → Kutta–Joukowski `L = ρ U Γ`
- **Goal.** Derive `L = ρ U Γ` analytically as the transverse resultant of an antisymmetric occlusion field, with `Γ` identified as the net CQ14 `ℓ=2` traction circulation — no imposed circulation.
- **Method.** Write the steady occlusion (static-pressure) field around a 2-D body as `P(θ) = P_sym(θ) + ΔP(θ)`, with `P_sym` the fore/aft drag part and `ΔP` the `ℓ=2` antisymmetric part (`law_VI::traction`). Integrate the surface occlusion force (`law_III` momentum flux) and project transverse to `U`; show it collapses to `ρ U Γ`. Tag every term DERIVED / MEASURED-INPUT / CALIBRATED(n) in a parameter ledger (R2). Flag any G/M/GM intrusion as an automatic R0 violation. Cite FD01 (root), CQ14 (traction), FD02 (κ) upstream.
- **Success metric.** `L = ρ U Γ` recovered exactly, with lift toward the low-occlusion face (correct sign), zero fitted parameters. **Checkpoint C1:** Kutta–Joukowski derived from occlusion asymmetry alone, sign correct, no G/M.

### Phase 2 — Thin-airfoil slope `dC_L/dα = 2π` from the ℓ=2 channel (core gate)
- **Goal.** Show the bound circulation induced by angle of attack `α` is `Γ = π U c α`, yielding `c_L = 2π α` and the slope `dC_L/dα = 2π` per radian — with the `2π` traced to the `ℓ=2` channel geometry, not inserted.
- **Method.** For a thin flat plate at small `α`, derive the relay-asymmetry threading `Γ` from the CQ14 two-lobed traction response to the imposed flow deflection; normalise to `c_L`. Confirm the `2π` is geometric (lattice / channel), not a fitted coefficient (R5). Compare to the measured slope of real (thick, viscous) sections (`≈ 0.9–0.95 × 2π`) and attribute the deficit to FD06 boundary-layer thickness, not to the SDT mechanism.
- **Success metric.** `dC_L/dα = 2π rad⁻¹` (ideal) reproduced analytically and numerically; the `2π` shown geometric. **Checkpoint C2 (core gate):** slope is `2π` ± numerical tolerance with no fitted coefficient. A slope materially ≠ `2π` from the SDT mechanism (not boundary-layer correction) is an immediate Class F.

### Phase 3 — Kutta condition as relay continuity (Law V), and Magnus
- **Goal.** Recover the Kutta condition as a Law-V relay-continuity bound, and reproduce the Magnus force sign and order of magnitude from the same differential relay-drag.
- **Method.** (a) **Kutta:** show an unpinned rear stagnation point demands `v → ∞` at the sharp trailing edge, violating `v ≤ c` (Law V `v_circ²+v_trans²=c²`); the lattice pins the rear stagnation at the edge, uniquely fixing `Γ` (the FD06 boundary-layer handshake). (b) **Magnus:** for a spinning cylinder, derive `Γ = 2π a U_s`, hence `L = 2π ρ a U U_s`; predict the sign (lift toward the side where surface motion adds to the flow) and evaluate the magnitude against a measured Magnus data point (one fluid `ρ`, stated `U`, `Ω`, `a`) — tag CALIBRATED(0) if no coefficient is fitted.
- **Success metric.** Kutta condition emerges from the `v ≤ c` ceiling (no separate axiom); Magnus sign correct and magnitude within the stated tolerance of measured data. **Checkpoint C3.**

### Phase 4 — Quantized limit & downstream handshake
- **Goal.** Connect bound `Γ` to the FD02 circulation quantum `κ = h/m` (`Γ = Nκ`, `N ≫ 1` classical), and hand the shed-circulation result to FD10.
- **Method.** Express the airfoil `Γ` as `N` bound quanta `κ` and show the classical lift is the `N ≫ 1` continuum. Numerically: a 2-D panel/point-vortex model that (i) imposes Kutta at the trailing edge, (ii) returns `Γ` and `c_L`, (iii) recovers `dC_L/dα → 2π` as thickness → 0. Predict each number and commit to the run log *before* comparing (R1). Two-stream check (R3): analytic `L = ρUΓ` vs numerical panel integration of the surface pressure.
- **Success metric.** `Γ = Nκ` limit shown; numerical `c_L(α)` slope → `2π`; analytic vs numerical lift agree to <1%; shed-circulation field exported for FD10. **Checkpoint C4.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Lift derived natively | Phase-1 `L = ρUΓ` from occlusion asymmetry (sign correct) AND Phase-2 `dC_L/dα = 2π` with the `2π` shown geometric AND Phase-3 Kutta from `v ≤ c` AND Magnus sign+magnitude correct AND `κ=h/m` limit shown, all CALIBRATED(0), no G/M anywhere. |
| **C (QUALIFIED — convergence)** | Lift reproduced, one scale set | `L = ρUΓ` + correct sign + `2π` slope + Kutta-as-continuity + Magnus sign correct, with at most CALIBRATED(1) (one fluid/spin scale fitted and documented); quantized limit shown qualitatively. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | `L = ρUΓ` and the sign correct, but the `2π` slope or the Kutta/FD06 handshake is PENDING; dimensionally closed, not yet bijective to the `ℓ=2` channel at coefficient level. |
| **F (FAIL)** | Mechanism falsified | Occlusion asymmetry gives the WRONG lift sign, OR the SDT mechanism yields a thin-airfoil slope materially ≠ `2π` (not a boundary-layer correction), OR no Kutta condition emerges (relay continuity does not pin the rear stagnation), OR Magnus force has the wrong sign. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd07_circulation_lift_magnus.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-1 occlusion-asymmetry → `L=ρUΓ` sign check; Phase-2 thin-airfoil `c_L(α)` slope (target `2π`); Phase-3 Kutta-continuity demonstration + Magnus sign/magnitude evaluation; Phase-4 panel/point-vortex two-stream check and `Γ=Nκ` limit; prints its own verdict. **No new constants redefined.** |
| `fd07_results.txt` | Plain text | Run output: `L=ρUΓ` analytic-vs-numerical lift table; `c_L` vs `α` slope fit (predicted-vs-2π); Kutta-continuity result; Magnus `L` predicted-vs-measured with sign; `Γ/κ = N` quantum count. |
| `FD07_DERIVATION.md` | Markdown | Full derivation: occlusion-asymmetry → Kutta–Joukowski; the `ℓ=2` traction → `Γ` mapping; the geometric origin of `2π`; Kutta-as-relay-continuity (Law V); Magnus from differential relay-drag; `κ=h/m` continuum; parameter ledger. |
| `FD07_VERDICT.md` | Markdown | A–F classification with the deciding metric; provenance × correspondence audit; what is DERIVED vs CALIBRATED(n) vs PENDING; downstream handoff to FD10. |

---

## 7. Dependencies & References

**Upstream (required):**
- **CQ14 (spation traction from the trefoil)** — `law_VI::traction`; the `ℓ=2` rotational wake channel that *is* bound circulation, and the `ℓ=1` radial channel for ordinary occlusion. FD07's `Γ` is the continuum coarse-graining of CQ14.
- **FD01 (Navier–Stokes from Spation Relay)** — the root continuum equations; FD07 starts from the FD01 steady flow field. FD07 cannot reach Class A if FD01 is not at least Class C.
- **FD02 (circulation quantum)** — supplies `κ = h/m` for the quantized-vortex limit `Γ = Nκ`.
- **FD06 (boundary layer / no-slip)** — supplies the boundary-layer mechanism that uniquely fixes `Γ` via the Kutta condition (rear-stagnation pinning).
- **Law V (movement budget)** — `v_circ² + v_trans² = c²` (engine `law_V`); forbids singular trailing-edge velocity → the Kutta condition; sets the relativistic corner.
- **Law III (occlusion force)** — `F = (π/4) P_eff R₁²R₂²/r²` (engine `law_III`); the momentum-flux push whose left/right asymmetry is lift.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_III` (occlusion / momentum flux), `law_V` (budget, ceiling), `law_VI::traction` (CQ14 ℓ=2 channel), `law_IV` (`V_disp` → ρ), `bridge` (koppa, k, z if needed for scaling).

**Downstream (unblocked by this):**
- **FD10 (shed circulation / starting vortex)** — consumes the bound-circulation field and the Kelvin/Kutta result derived here.

**Related:** **FD08 (Bernoulli)** — supplies the streamline pressure field that the occlusion-asymmetry integration draws on; **FD06** — the no-slip boundary layer that physically sets the Kutta pinning.

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Lift sign (Phase 1) | Occlusion asymmetry gives lift toward the low-occlusion (fast-relay) face | `L = ρUΓ`, lift toward the fast side, analytically and numerically | Wrong transverse sign ⟹ occlusion asymmetry mis-mapped ⟹ Class F |
| F2 — Slope = 2π (Phase 2, core) | Thin-airfoil slope is `2π` from the ℓ=2 channel | `dC_L/dα = 2π rad⁻¹`, the `2π` geometric, not fitted | SDT mechanism (not boundary layer) gives slope materially ≠ `2π` ⟹ Class F |
| F3 — Kutta as continuity (Phase 3) | `v ≤ c` (Law V) forbids singular trailing-edge velocity, pinning rear stagnation | Kutta condition emerges, uniquely fixing `Γ`; no separate axiom | No Kutta condition emerges from relay continuity ⟹ circulation not lattice-fixed ⟹ Class F |
| F4 — Magnus sign/magnitude (Phase 3) | Spin biases relay; lift toward the side where surface motion adds to flow | `L = 2πρaUU_s`, correct sign, magnitude within tolerance of measured Magnus data | Wrong Magnus sign, or order-of-magnitude miss with no SDT route ⟹ Class F |
| F5 — Quantum limit (Phase 4) | Bound `Γ` is `N` quanta of `κ=h/m` | `Γ = Nκ`, `N ≫ 1`, classical lift as the continuum | `Γ` cannot be expressed as integer-`N` `κ` multiples ⟹ FD02 handshake PENDING (D, not F) |

---

## 9. Implementation Notes

- **Numerical method.** Phase 4 is a 2-D thin-airfoil / point-vortex (or simple panel) model: place bound vorticity, impose the Kutta condition at the trailing edge, integrate the surface occlusion (pressure) field for `L`, and verify `L = ρUΓ` (two-stream: analytic vs numerical) to <1%. Sweep `α` and fit `dC_L/dα`, confirming → `2π` as thickness → 0. For Magnus, a single spinning-cylinder evaluation (`Γ = 2π a U_s`) suffices for the sign + order-of-magnitude check. Use double precision; keep panel counts modest (`N ≤ 512`). This is a *demonstration of the mechanism*, not a production CFD/aero solver.
- **No borrowed units.** Express circulation in SDT-native yardsticks where possible (CQ14 `ℓ=2` traction, `κ = h/m` quanta); evaluate against measured fluid `ρ` and spin data in their measured units only as the *convergence check*, never as the derivation's input. Never express lift via imported aero coefficients as if they were SDT primitives.
- **Testing strategy.** Three independent two-stream checks (R3): (i) analytic `L=ρUΓ` vs numerical surface-pressure integration; (ii) `c_L(α)` slope vs `2π`; (iii) Magnus sign vs the surface-motion direction. Predict each number and commit it to the run log *before* comparing (R1). Anti-numerology (R5): the `2π` must trace to lattice / ℓ=2 channel geometry — no free integer or π inserted to force the slope.
- **Sign guard.** The deciding falsifier is the lift sign. Assert in code that lift points toward the low-occlusion (fast-relay) face and that Magnus lift points toward the side where surface motion adds to the flow; a sign flip is an immediate Class F, not a tuning knob.
- **No-G guard.** No `GM/R²` or `G`-anything may enter any code path; lift is `ρU Γ`, a pure occlusion/momentum-flux quantity. Any G/M intrusion is an automatic R0 violation.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd07_circulation_lift_magnus.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd07_circulation_lift_magnus.cpp -o fd07` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** Plot the occlusion asymmetry `ΔP(θ)` around the body (two-lobed = ℓ=2); `c_L` vs `α` with the `2π` tangent at the origin; the Magnus lift vs spin ratio `S = U_s/U`; and the bound-vortex / Kutta-pinned streamline pattern.
- **Author attribution:** James Christopher Tyndall, Melbourne. The standard-FD results (Kutta–Joukowski `L=ρUΓ`, the `2π` slope, the Magnus force, the Kutta condition) are the CONVERGENCE targets to *reproduce*, never inputs to *borrow*.
