# FD02 — Viscosity and the Quantum of Circulation from Lattice Mechanics

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is fluid viscosity genuinely lattice momentum-diffusion `ν = ⅓ λ_mfp v_relay` (with the `⅓` traced to 3-D angular averaging, not borrowed), and does the lattice impose a real dissipation *floor* (`η/s ≳ ħ/(4π k_B)`) whose `1/(4π)` is derivable rather than fitted?
2. **Why does it matter?** — FD02 supplies the `ν` coefficient FD01 leaves PENDING and the circulation quantum `κ` FD07 needs; if the `⅓` and the floor coefficient are native, viscosity stops being a fitted material property and becomes relay geometry. **Honest caveat:** `κ = h/m` is essentially structural (Law VI winding *defines* one quantum of action per spation), so Phase 4 is a consistency check, not an independent prediction — graded accordingly.
3. **How will we find out?** — Five gated phases (§④): derive `ν` and its `⅓` (P1) and the `√T` exponent (P3) before reading any tabulated viscosity; the floor coefficient (P5) is DERIVED-or-CALIBRATED(1), never silently inserted.
4. **What would prove us wrong?** — §⑧, five falsifiers with real failure modes: air/water `ν` off by >2 orders or wrong air>water ordering; fitted `T`-exponent outside `0.5 ± 0.05` (not Sutherland-explained); `κ` reproducible only by inserting a free integer; no floor emerging; FD01 handshake off >10%.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

**Domain**: Fluid Dynamics (SDT lattice mechanics) · **Status**: SPEC · **Author**: J. C. Harvey, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (derivation basis inputs only; no G/M/kg fundamentals; no fields/wavefunctions/quarks/ΛCDM; certification labels on every result; translation test on every borrowed term; predict-before-look; honesty over success).*

---

## 1. Executive Summary

Viscosity is treated as a fitted material property in classical fluid mechanics, and the superfluid circulation quantum `κ = h/m` is handed down from quantum mechanics. In Spatial Displacement Theory both must instead be *mechanism*, since the only ontology is a granular relay lattice of spations passing convergence throughput at speed `c`. **The thesis is threefold.** (a) Kinematic viscosity is lattice momentum diffusion, `ν = ⅓ λ_mfp v_relay` (lattice kinetic theory), recovering B16's `ν ∝ √T` law (exponent 0.5), with dynamic viscosity `μ = ρν`. (b) Circulation around any closed lattice loop is quantised in units of the one-spation winding, `κ = h/m`, which is the SDT *origin* of the superfluid circulation quantum — superfluidity being phase-locked `W=1` tori (E59). (c) There is a relay floor on dissipation: a kinematic-viscosity quantum `~ħ/m` and a KSS-style bound `η/s ≳ ħ/(4π k_B)` emerge because the lattice cannot relay-diffuse momentum slower than one quantum per spation. A clean reproduction of all three earns Class C; any failure of `κ = h/m`, the 0.5 exponent, or the floor is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** A real fluid resists shear because molecules carry momentum across a velocity gradient as they random-walk between collisions. SDT keeps the picture but changes the carriers: the spation lattice is the medium, and momentum is convergence throughput relayed cell-to-cell at `c`. Shear stress is the net throughput carried across a shear plane per relay step; the mean free path `λ_mfp` is the coarse-grained distance a momentum quantum travels before its direction is randomised by knot scattering, and `v_relay` is the effective relay speed of that momentum (bounded by `c`). Viscosity is therefore not a substance property bolted on by hand — it is the diffusion coefficient of the same nearest-neighbour relay that carries every SDT force. Circulation is the line integral of that coarse-grained flow around a loop; because each spation can wind the flow by at most one quantum of action, the loop integral is quantised, and a vortex that phase-locks its winding cannot shed it — that is superfluidity.

**Key variables and dimensions.**
- `ν` — kinematic viscosity [m²·s⁻¹] (a length × speed: `λ_mfp · v_relay`)
- `μ = ρν` — dynamic viscosity [Pa·s = kg·m⁻¹·s⁻¹]
- `ρ` — displacement-load density [kg·m⁻³] (Law IV `V_disp`, *not* an imported fundamental)
- `λ_mfp` — momentum mean free path [m]; `v_relay` — relay/transport speed [m·s⁻¹], `≤ c`
- `T` — temperature [K]; B16 transport law gives `ν ∝ T^{0.5}`
- `Γ`, `κ` — circulation `Γ = ∮ v·dl` [m²·s⁻¹]; quantum `κ = h/m` [m²·s⁻¹]
- `η/s` — shear-viscosity-to-entropy-density ratio [dimensionless in `ħ/k_B` units]; floor `≳ ħ/(4π k_B)`
- `ℓ_P`, `t_P`, `c = ℓ_P/t_P` — relay lattice scale, tick, signal speed
- `W` — winding number (Law VI); superfluid pairs are phase-locked `W=1` tori

**Connection to SDT.** Momentum diffusion is the same lattice Laplacian relay that FD01 maps to the `ν∇²v` term — FD02 *supplies the coefficient* FD01 leaves PENDING. The `√T` scaling ties to B16's measured transport exponents. The circulation quantum is Law VI winding made macroscopic: one spation = one quantum of winding, `κ = h/m`. The `η/s` floor is the dissipation analogue of the movement budget (Law V) — the lattice has a minimum relay step, so it cannot transport momentum arbitrarily slowly.

---

## 3. Theoretical Framework

**First principles (SDT axioms only — no new fitted parameters).**

1. **Granular Pulse Invariant (FLM02).** Each spation relays one throughput pulse per `ℓ_P` per `t_P` to each contacting neighbour, fixing `c = ℓ_P/t_P`. Across a shear plane the *net* transverse throughput per step is the momentum flux; the proportionality constant of that flux to the velocity gradient is the dynamic viscosity. This is the lattice statement of kinetic theory, with spations in place of molecules.

2. **Lattice kinetic theory of viscosity.** From elementary momentum-transport across a plane, `μ = ⅓ ρ λ_mfp v_relay`, hence the kinematic form
   `ν = μ/ρ = ⅓ λ_mfp v_relay`.
   `λ_mfp` is the scattering length of momentum against vortex-knot matter (set by knot density / `V_disp`, not fitted), and `v_relay` is the thermalised transport speed. Both are *length* and *speed* drawn from lattice geometry, so `ν` is `length × speed`, dimensionally `[m²·s⁻¹]`, with no kilograms-as-fundamental entering.

3. **Temperature law (B16 handshake).** If `v_relay` is the thermal relay speed `v_relay ∝ √(k_B T / m)` (equipartition of throughput, `m` a measured-input mass scale) and `λ_mfp` is set by geometry weakly dependent on `T`, then `ν ∝ √T` — the B16 transport exponent **0.5**. This is a *prediction to reproduce*, not a fit: the exponent is fixed before any data are read (R1).

4. **Circulation quantisation (Law VI).** Circulation `Γ = ∮ v·dl` around a loop enclosing a vortex knot counts the winding it encloses. One spation contributes one quantum of action `ℏ` to the loop; for a knot of displacement-mass `m` the irreducible circulation is
   `κ = h/m  =  2πℏ/m`.
   This is Law VI winding (`law_VI::topology`) expressed as a macroscopic line integral; the `W=1` torus is the minimal phase-locked circulation, and phase-locked `W=1` pairs (E59) cannot decay their circulation — *that* is superfluidity, with no quantum wavefunction invoked.

5. **Relay floor on dissipation (Law V analogue).** The lattice cannot relay-diffuse momentum slower than one quantum of action per spation per tick. Expressed per unit entropy density `s`, this is a lower bound
   `η/s ≳ ħ/(4π k_B)`,
   and the kinematic-viscosity floor is `ν_min ~ ħ/m`. The `1/(4π)` is to be *derived from lattice geometry* (solid-angle / relay-step counting), not inserted; if it can only be set by hand it is flagged CALIBRATED(1).

**Governing relations to derive.**
- `ν = ⅓ λ_mfp v_relay` and `μ = ρν`, with `λ_mfp`, `v_relay` expressed in lattice primitives.
- `ν(T) ∝ T^{0.5}` (B16 exponent), the slope checked against a tabulated `ν(T)` curve.
- `κ = h/m`, evaluated for ⁴He using MEASURED-INPUT `m_He`.
- `η/s ≳ ħ/(4π k_B)` and `ν_min ~ ħ/m`, the coefficient derived or flagged.

The §3 deliverable is one chain in which viscosity, the circulation quantum, and the dissipation floor are *three faces of the same relay mechanism* — momentum handoff capped and quantised by the spation step. Any face that needs an imported QM axiom is a contamination flag, not a pass.

---

## 4. Investigation Strategy

Five phases, each gated. Run in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass). Predict every number and log it *before* comparison (R1).

### Phase 1 — Lattice kinetic theory of viscosity
- **Goal.** Derive `ν = ⅓ λ_mfp v_relay` and `μ = ρν` from the per-spation momentum-transport-across-a-plane argument, in SDT primitives only.
- **Method.** Set up the momentum flux through a shear plane from the GPI relay (FLM02): count net transverse throughput per tick as a function of the velocity gradient. Identify `λ_mfp` (knot-scattering length, from `V_disp`/knot density) and `v_relay` (thermal relay speed). Maintain a parameter ledger (R2) tagging each constant DERIVED / MEASURED-INPUT / CALIBRATED(n).
- **Success metric.** Closed expression `ν = ⅓ λ_mfp v_relay` with the `⅓` traced to lattice geometry (the angular-average factor, cf. `P_cf = P_conv/3`), zero free parameters beyond a single density/scale that is MEASURED-INPUT. **Checkpoint C1.**

### Phase 2 — Order-of-magnitude convergence on real fluids
- **Goal.** Recover air and water kinematic viscosity to order of magnitude from `λ_mfp · v_relay`.
- **Method.** Insert measured `λ_mfp` and thermal speed for air (STP) and water; compute `ν` and compare to tabulated values (air `ν ≈ 1.5×10⁻⁵ m²·s⁻¹`, water `ν ≈ 1.0×10⁻⁶ m²·s⁻¹` at ~20 °C). These tabulated values are the CONVERGENCE TARGET, never an input. Predict before looking.
- **Success metric.** Both `ν` within one order of magnitude (factor ≲ 10) of measured; relative ordering air > water reproduced. **Checkpoint C2.**

### Phase 3 — Temperature exponent (B16 handshake)
- **Goal.** Reproduce the `ν ∝ √T` law, exponent **0.5**.
- **Method.** With `v_relay ∝ √(k_B T/m)` and geometry-set `λ_mfp`, compute `ν(T)` over a `T` sweep; log-log fit the slope. Cross-check the emitted exponent against B16's transport-exponent value (0.5). Two-stream verify (R3): analytic `½`-power vs numerical fit.
- **Success metric.** Fitted exponent `0.5 ± 0.05`; agreement with B16 to <1%. **Checkpoint C3.** (Note real gases show ~0.7 from Sutherland correction — record the deviation as a known coarse-graining limit, not a fail of the lattice exponent.)

### Phase 4 — Circulation quantum (the superfluid gate)
- **Goal.** Derive `κ = h/m` from Law VI winding and evaluate for ⁴He.
- **Method.** Take the loop integral `Γ = ∮ v·dl` around a single `W=1` torus; show one-spation winding ⟹ `κ = h/m`. Evaluate with MEASURED-INPUT `m_He` (mass of the ⁴He atom): predict `κ = h/m_He` and compare to the measured superfluid circulation quantum `≈ 9.97×10⁻⁸ m²·s⁻¹`. Tie the non-decay of phase-locked pairs to E59.
- **Success metric.** Computed `κ` matches measured to <1% (it is `h/m` essentially by construction — the test is that the SDT winding argument *forces* `h/m` with no free integer, R5 anti-numerology). **Checkpoint C4 (core gate).**

### Phase 5 — Dissipation floor (η/s and ν_min)
- **Goal.** Derive the relay floor: `ν_min ~ ħ/m` and `η/s ≳ ħ/(4π k_B)`.
- **Method.** Argue the minimum momentum-diffusion step is one action quantum per spation; convert to `η/s` via entropy density. Attempt to derive the `1/(4π)` from solid-angle/relay-step counting (cf. `4π` in `exclusion_radius`); if it can only be set by matching the known KSS value, flag CALIBRATED(1). Compare `ν_min ~ ħ/m` to the smallest measured kinematic viscosities (superfluid ⁴He, quark-gluon-plasma `η/s ≈ ħ/(4π k_B)` regime — used as a CONVERGENCE benchmark only, not importing QGP physics).
- **Success metric.** Floor reproduced to within a factor of `4π`; coefficient either DERIVED (Class A path) or honestly CALIBRATED(1) (Class C path). **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | All three faces derived natively | `ν = ⅓ λ_mfp v_relay` with `⅓` DERIVED; air/water `ν` within factor 3; exponent `0.5 ± 0.02`; `κ = h/m` forced (no free integer); `η/s` floor with `1/(4π)` DERIVED — all at CALIBRATED(0). |
| **C (QUALIFIED — convergence)** | Reproduced, one scale set | `ν` within factor 10 (Phase 2); exponent `0.5 ± 0.05` matching B16 <1%; `κ = h/m_He` <1%; floor reproduced within factor `4π` with the coefficient CALIBRATED(1) and documented. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | `ν` form and `κ = h/m` reproduced, but `λ_mfp`/`v_relay` closure or the `η/s` coefficient is PENDING (ROOT-SIM / E59); dimensionally closed, not yet a full handshake with FD01. |
| **F (FAIL)** | Mechanism falsified | `κ ≠ h/m` (winding does not force the quantum), OR fitted temperature exponent `≠ 0.5` (outside `±0.05`, not explained by Sutherland correction), OR no dissipation floor emerges from the relay step. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd02_viscosity_circulation.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase 1–2 `ν = ⅓ λ_mfp v_relay` evaluation for air/water; Phase 3 `ν(T)` log-log exponent fit vs B16; Phase 4 `κ = h/m_He` vs measured; Phase 5 `η/s` floor; prints its own A–F verdict. **No new constants redefined.** |
| `fd02_results.txt` | Plain text | Run output: air/water `ν` predicted-vs-measured table, `ν(T)` exponent fit, `κ` for ⁴He, `η/s` and `ν_min` floor values with comparison. |
| `FD02_DERIVATION.md` | Markdown | Full chain: lattice kinetic theory → `ν`/`μ`; B16 `√T` derivation; Law VI winding → `κ = h/m`; relay-step → `η/s` floor; parameter ledger. |
| `FD02_VERDICT.md` | Markdown | A–F classification with the deciding metric; provenance × correspondence audit; DERIVED vs CALIBRATED(n) vs PENDING; handoff of `ν` coefficient to FD01 and `κ` to FD07. |

---

## 7. Dependencies & References

**Upstream (required):**
- **B16 (transport exponents)** — the `ν ∝ √T` law, exponent 0.5; Phase 3 must reproduce it to <1%.
- **PPT01 (Vortex Equilibrium Quantisation)** / **PPT09 (Winding Number Stability)** — vortex modes and `W=1` stability that ground the circulation quantum and superfluid phase-lock.
- **E59 (Superconductivity / superfluidity)** — phase-locked `W=1` vortex pairs; the non-decay of circulation that makes a superfluid.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_I::P_conv`, `law_III` (occlusion), `law_IV` (`V_disp` → ρ, knot density → `λ_mfp`), `law_V` (movement budget, floor analogue), `law_VI::topology` (winding → `κ`), `law_VI::traction`, `law_VI::confinement`.

**Downstream (unblocked by this):**
- **FD01 (Navier–Stokes)** — receives the `ν` coefficient it leaves PENDING; FD01 cannot reach Class A without FD02's independent value.
- **FD03 (Reynolds number)** — uses `ν` to form `Re = vL/ν`.
- **FD04 (Kolmogorov microscale)** — uses `ν` for the dissipation-scale `η = (ν³/ε)^{1/4}`.
- **FD06 (boundary layer)** — viscous traction at walls.
- **FD07 (circulation / lift)** — uses the circulation quantum `κ` and `Γ` machinery.

**Related:** Law VI traction/confinement (`law_VI::traction::ω_demand`) for the knot-scattering length; FLM02 (GPI) for the momentum-flux relay.

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Order of magnitude (Phase 2) | `ν = ⅓ λ_mfp v_relay` recovers real fluids | air `ν ≈ 1.5×10⁻⁵`, water `ν ≈ 1.0×10⁻⁶ m²·s⁻¹` within factor ≲ 10 | Off by >2 orders, or wrong air/water ordering ⟹ relay diffusion ≠ viscosity ⟹ Class F |
| F2 — Temperature exponent (Phase 3) | lattice kinetic theory gives `ν ∝ √T` | fitted exponent `0.5 ± 0.05`, matches B16 <1% | Exponent outside `±0.05` (and not Sutherland-explained) ⟹ thermal relay speed mis-modelled |
| F3 — Circulation quantum (Phase 4) | one-spation winding forces `κ = h/m` | `κ = h/m_He ≈ 9.97×10⁻⁸ m²·s⁻¹`, <1% | `κ ≠ h/m`, or quantum only reproduced by inserting a free integer ⟹ Law VI does not yield superfluid circulation ⟹ Class F |
| F4 — Dissipation floor (Phase 5) | relay step ⟹ `η/s ≳ ħ/(4π k_B)`, `ν_min ~ ħ/m` | floor present, within factor `4π` of KSS bound | No floor emerges, or smallest measured `ν` lies below the predicted `ν_min` ⟹ no relay minimum |
| F5 — FD01 handshake | FD02 `ν` = FD01 coarse-grain `ν` | agreement <1% | Disagreement >10% with no reconciling mechanism ⟹ the two derivations of `ν` are inconsistent ⟹ Class F |

---

## 9. Implementation Notes

- **Numerical stability.** Most of FD02 is closed-form evaluation, not time-stepping, so the main risk is unit slips, not CFL. Carry SI throughout, use double precision, and assert dimensional consistency (`[ν] = m²·s⁻¹`, `[κ] = m²·s⁻¹`, `[μ] = Pa·s`) with `static_assert`-style range checks at runtime. For the `ν(T)` log-log fit, use a clean linear least-squares on `log ν` vs `log T` and report both slope and `R²`.
- **Testing strategy.** Three independent two-stream checks (R3): (i) `ν = ⅓ λ_mfp v_relay` evaluated two ways — directly and via `μ/ρ` — must agree; (ii) the temperature exponent from the analytic `½`-power vs the numerical fit slope; (iii) `κ = h/m_He` computed from `h/m` vs from `2πℏ/m`. Predict every number and commit it to the run log *before* comparison (R1). Anti-numerology (R5): the `⅓`, the `0.5`, and the `1/(4π)` must each trace to lattice geometry or be flagged CALIBRATED — never inserted to force a match.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd02_viscosity_circulation.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd02_viscosity_circulation.cpp -o fd02` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes. `m_He`, tabulated `ν(T)`, and `λ_mfp`/thermal-speed inputs are MEASURED-INPUT and belong in `DATA_REQUIREMENTS.md`, not hard-coded as if derived.
- **Visualisation hints.** Plot the `ν(T)` log-log line with the fitted slope annotated against the 0.5 reference; a bar chart of predicted-vs-measured `ν` for air and water; and a number-line of kinematic viscosities from air down to superfluid ⁴He with the `ν_min ~ ħ/m` floor marked. A small schematic of momentum flux across a shear plane (GPI relay) makes the `λ_mfp v_relay` mechanism legible.
- **Author attribution:** J. C. Harvey, Melbourne. The standard-FD results (kinetic-theory viscosity, `κ = h/m`, the KSS `η/s` bound) are the CONVERGENCE targets to *reproduce*, never inputs to *borrow*.

## 10. Questions This Opens *(generative — log new ones in `FD02_VERDICT.md`)*

1. **Is `κ = h/m` a derivation or a definition?** Law VI assigns one action quantum per spation winding, which makes `κ = h/m` near-tautological. The real open question: does the *value* of the action quantum `ℏ` itself fall out of lattice geometry (FLM06 seed theorem), or is it an irreducible anchor? If the latter, Phase 4 is CONVERGENCE, not NATIVE — say so.
2. **Can the `1/(4π)` in the `η/s` floor be derived from solid-angle/relay-step counting** (the same `4π` that appears in `exclusion_radius`), or only matched to the measured KSS bound? If only matched, the floor is CALIBRATED(1) and the *physical* claim (a real lattice dissipation minimum) stays OPEN.
3. **Does the real `√T` law deviate the way the Sutherland correction (~0.7 exponent) predicts**, and is that deviation an SDT coarse-graining limit or an independent knot-scattering temperature dependence in `λ_mfp`?
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FD02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: declare it — `κ=h/m` is structural (note 1); the `η/s` `1/(4π)` is the budgeted CALIBRATED(1) candidate
- Engine namespaces actually used: law_IV (V_disp→ρ, knot density→λ_mfp), law_V (budget/floor analogue), law_VI::topology (winding→κ), law_VI::traction (knot-scattering)
- Phase thresholds (committed before run):
    P1 `⅓` traced to angular average · P2 air & water `ν` within factor 10, ordering air>water
    P3 fitted exponent 0.5 ± 0.05 (vs B16 <1%) · P4 `κ=h/m_He` <1% (consistency, not prediction) · P5 floor within factor 4π
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces; sell `κ=h/m` as an independent prediction
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P2 `ν` off >2 orders or wrong air/water order | recheck `λ_mfp`/`v_relay` from knot density | **KILL** (relay diffusion ≠ viscosity) | tune `λ_mfp` to the answer |
| P3 exponent outside 0.5 ± 0.05 | check for Sutherland correction; report deviation | **OPEN** the thermal-relay model | force a 0.5 fit |
| P5 `1/(4π)` only matchable, not derivable | flag floor **CALIBRATED(1)**, cap at C | **OPEN** the floor mechanism | claim A with an inserted `1/(4π)` |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (E59, ROOT-SIM) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in the Phase-1 native chain · grading `κ=h/m` as NATIVE when it is structural.

---

*FD02 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

## B16 full-curve closure freeze (2026-08-14)

The three literal exponent echoes in B16 are not targets for the forward
solver. The closure route is:

```text
FLM15 lock/occlusion cross-section sigma_lock(T)
  -> lambda_lock(T)=1/[n(T) sigma_lock(T)]
  -> v_relay(T) from the movement budget
  -> D(T)=(1/3) lambda_lock v_relay
  -> mu(T)=rho(T) D(T)
  -> k_thermal(T)=rho(T) c_v D(T)
  -> full measured curves
```

The primary sweep is a dilute monatomic gas at fixed measured pressure over at
least eight temperatures spanning a factor of two. The same cross-section and
relay speed are used for all three properties; no property-specific exponent
or scale is fitted. Raw pressure, temperature, composition, number density and
transport measurements carry source and uncertainty fields.

Frozen gates:

1. The FLM15 isotropic factor and lock cross-section pass before FD02 runs.
2. Every predicted value is emitted before its measured counterpart is read.
3. The analytic and numerical collision integrals agree to relative error
   `<1e-4`; doubling angular and radial quadrature changes each curve by `<1%`.
4. At fixed pressure, thermal conductivity and dynamic viscosity are separate
   observables, while diffusivity retains the density factor; the instrument
   must not copy one fitted slope into three rows.
5. Each normalized full curve advances only if its uncertainty-weighted RMS
   fractional residual is `<=10%` and no monotonic trend has the wrong sign.
   A missing amplitude closure or failed curve remains `PENDING`.
6. Deleting all measured transport columns leaves `sigma_lock(T)`,
   `lambda_lock(T)` and every predicted curve unchanged.

No body-source alias, Sutherland fit, tabulated collision integral, or
post-comparison exponent may enter the prediction path.
