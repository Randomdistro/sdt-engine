# CQ-34 — Angular Degree of Freedom from Trefoil Wake

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [PPT08] CQ-34 — Angular Degree of Freedom from Trefoil Wake: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

**Author:** James Christopher Tyndall, Melbourne, Australia  
**Date:** June 2026  
**Status:** SPEC  
**Dependency:** PPT01, PPT06, Law VI; blocks all L3 fine structure  
**Priority:** FOUNDATIONAL — this is the deepest structural gap in SDT after ROOT-SIM

---

## §0 Anti-creep protocol

- **declared dependencies:** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables
- **Prohibited:** spherical harmonics Y_ℓ^m as imported functions, |ψ(0)|², orbital angular momentum quantum numbers as external definitions, magnetic quantum numbers
- **The goal is native:** derive the angular degree of freedom from SDT topology, not import it from QM

---

## 1. The problem

SDT currently recovers only **radial / principal-n** structure:
- Node ladder: `r_n = n² a₀`
- Angular momentum: `L_n = nℏ`
- Energy: `E_n = -Ry/n²`

The rotation field `v(r) = cα√(a₀/r)` is a function of **r only** (FLM03). There is **no native reason** `l = 0` (s) differs from `l = 1` (p). The s-vs-p distinction is borrowed spherical-harmonic language — a structural borrow flagged as M1 in the contamination audit.

**Without a native angular DOF, SDT cannot compute:**
- Fine structure beyond Sommerfeld (which is imported)
- The Lamb shift (currently fitted: k_Lamb = 12.7227)
- Hyperfine structure (mechanism borrowed from QED)
- Selection rules for spectral transitions
- The sign 2S₁/₂ > 2P₁/₂

This was identified by the Lamb-dyad refutation workflow (2026-06-08) and flagged as `ANGULAR-DOF [OPEN · foundational]` in the INVESTIGATION_STACK.

## 2. The hypothesis

**The proton is not spherically symmetric.** It is a trefoil (W=3) — a three-lobed structure with a definite three-fold rotational symmetry axis. Its wake field inherits this asymmetry.

**Key insight:** In standard physics, the angular structure of atoms comes from the electron's wavefunction (Y_ℓ^m). In SDT, there are no wavefunctions. But the electron orbits inside a *non-spherical* wake field created by the proton's trefoil topology. The angular DOF should emerge from the **proton's topology**, not from the **electron's motion**.

This inverts the standard picture: angular structure is a property of the *nuclear wake geometry*, not of the *orbital eigenstates*.

## 3. The mechanism (candidate)

### 3.1 Trefoil wake structure

The trefoil knot (2,3 torus knot) has:
- Three-fold rotational symmetry about the z-axis
- A preferred plane (the equatorial plane of the torus)
- Phase velocity v_phase = 1.831c at R_p (from PPT06)
- Three output channels from the traction ratio T = 12 = 3(W+1)

The wake field at distance r from the proton should decompose as:
```
Φ_wake(r, θ, φ) = Φ₀(r) + Φ₂(r)P₂(cos θ) + Φ₃(r)cos(3φ) + ...
```

where:
- Φ₀(r) is the monopole (mass/gravity) — ℓ=0
- Φ₂(r) is the quadrupole (magnetic moment) — ℓ=2
- Φ₃(r) is the trefoil harmonic — ℓ=3 (unique to W=3)

### 3.2 Electron orbit in the wake

An electron orbiting at `r_n = n²a₀` sits in this asymmetric wake. Its orbit can be:
- **Equatorial** (in the trefoil plane) — maximum interaction with the ℓ=2 quadrupole → "s-like" (no angular node)
- **Polar** (perpendicular to the trefoil plane) — reduced quadrupole interaction → "p-like" (angular node)
- **Inclined** — intermediate

The energy difference between equatorial and polar orbits would be the fine structure splitting.

### 3.3 Why s > p (the Lamb shift sign)

In the equatorial orbit ("s-like"), the electron passes through all three lobes of the trefoil wake per revolution. The wake interaction is stronger because the electron samples the full azimuthal structure.

In the polar orbit ("p-like"), the electron passes over the top of the trefoil and sees a more averaged, smoother field. The interaction is weaker.

**Prediction:** The equatorial orbit has slightly *higher* energy than the polar orbit, because it interacts more strongly with the trefoil structure. This gives E(s) > E(p) — the correct sign for the Lamb shift.

## 4. Investigation stages

### Stage 1: Trefoil wake geometry (PAPER)
- Compute the wake field of a (2,3) torus knot at distance r >> R_p
- Express the multipole expansion in SDT variables (not imported harmonics — derive the angular functions from the trefoil geometry directly)
- Identify which angular modes are present and which are forbidden by the trefoil symmetry

### Stage 2: Energy splitting (CALCULATION)
- For an electron at r = a₀ (hydrogen ground state), compute the energy difference between equatorial and polar orbits in the trefoil wake
- Compare to the measured fine structure α²Ry and the Lamb shift 1057.845 MHz
- If the scale is wrong by orders of magnitude → negative result, document

### Stage 3: Angular quantisation (THEORY)
- Show that the trefoil wake permits only discrete angular states (from the three-fold symmetry)
- Count the states: how many "orbitals" does the trefoil geometry permit at each n?
- Compare to the standard 2l+1 degeneracy pattern

### Stage 4: Predictions (FALSIFIABLE)
- If the angular DOF comes from trefoil geometry, then:
  - **P1:** Deuterium (proton + neutron) should have a *different* fine structure than hydrogen (the neutron modifies the trefoil wake) — measurable
  - **P2:** Muonic hydrogen should show the same angular splitting pattern as electronic hydrogen (same proton topology, different orbit radius) — consistent with data
  - **P3:** Positronium (no proton) should have *no* fine structure from this mechanism — the angular DOF vanishes — falsifiable against the measured positronium spectrum

## 5. Acceptance criteria

**PASS:** A native angular DOF emerges from the trefoil wake geometry, with the correct number of states and the correct sign for the s-p splitting. The Lamb shift value is derived to within 10% without fitting k_Lamb.

**PARTIAL:** The mechanism produces an angular splitting but the magnitude is wrong. Document the scaling.

**FAIL:** The trefoil wake is too symmetric at atomic distances, or produces the wrong sign, or the angular states don't match the observed spectrum.

**CRITICAL FAILURE MODE:** If the equatorial-vs-polar energy difference has the *wrong sign* (E(p) > E(s)), the mechanism is refuted.

## 6. Connection to the stack

- **Solves:** ANGULAR-DOF (L2, foundational)
- **Unblocks:** Lamb shift native derivation, fine structure, hyperfine mechanism
- **Feeds:** APS01/APS02 emissions, E53/E91 g-2, all L3
- **Independent of:** ROOT-SIM (this is topology, not lattice simulation)

---

## 7. Provenance target

```
// provenance_status:     SDT-derived
// correspondence_status: known-match (fine structure) / novel-prediction (P1-P3)
// input_dependency:      primitive-derivation basis + W=3 topology
// class:                 C (target) / D (for novel predictions)
// risk_flag:             trefoil multipole expansion may need numerical simulation
```
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT08
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_VI winding, bridge::k_*, PPT01 equilibrium
- Phase thresholds (committed before run): 10%
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

*PPT08 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
