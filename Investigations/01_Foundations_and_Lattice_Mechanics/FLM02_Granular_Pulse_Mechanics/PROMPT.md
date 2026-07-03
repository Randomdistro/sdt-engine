# FLM02 — Granular Pulse Mechanics: The Dynamic Throughput Law

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [FLM02] FLM02 — Granular Pulse Mechanics: The Dynamic Throughput Law: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## Classification: Codebase Question / Theoretical Derivation
## Source: Conversation 701fe685, April 2026
## Depends on: Law I (Φ, ε, N), Law III (force), Law IV (V_disp), Law V (budget)

---

## Question

Laws III, IV, and V each describe a DIFFERENT aspect of dynamics:
- Law III: Force = occluded convergence (mechanism)
- Law IV: Mass = V_disp reorganisation cost (definition)
- Law V: v_circ² + v² = c² (budget)

**What is the MECHANISM that connects them?**

How does the granular pulse structure of the relay produce F = ma?
Why is constant velocity free? Why does acceleration cost energy?
What is inertia, mechanistically?

## Answer (Axioms → Theorems → Proofs)

### Axiom GPI: The Granular Pulse Invariant

> Every spation receives one relay pulse per Planck length per Planck time,
> from each direction, independently. This rate is invariant under all
> conditions — velocity, acceleration, gravitational state.

Formally:
```
Pulse rate per direction = 1/(l_P × t_P) = 1.148 × 10⁷⁸ Hz/m
```

This is the FUNDAMENTAL INVARIANT. c, ℏ, and all Planck units are consequences.

### Axiom CS: Constancy Stabilisation

> Once a velocity change ceases, the omnidirectional input re-symmetrises
> around the knot at the new velocity. The new velocity becomes the
> stable resting state.

### Axiom FL: Flux Locality

> All matter sits at the centre of its own flux. Inertia is relative
> to the local throughput environment. Mass is local — determined by
> V_disp (topology) and the local throughput density.

---

## Theorems

### Theorem GPI-1: c is a consequence

```
c = l_P / t_P [exact]
```

The relay propagation speed equals one Planck length per Planck time because
each spation passes the pulse to its neighbour in one tick.

### Theorem GPI-2: Omnidirectional symmetry at constant velocity

At constant velocity v, the particle's frame sees symmetric pulse input.
No pulse asymmetry → no net reorganisation → no force → no cost.

This IS Newton's First Law, derived from GPI.

### Theorem GPI-3: Pulse asymmetry during acceleration

During acceleration a, the particle is pushed through a throughput gradient.
In the direction of acceleration:
```
Effective pulse rate = (1 + δ)/(l_P × t_P)
```
where:
```
δ = a × t_P / c = a × l_P / c²
```

### Theorem GPI-4: F = ma from pulse asymmetry

The net throughput asymmetry δ creates a reorganisation load on V_disp:
```
F = [Φ V_disp / (3 l_P³ c²)] × a = m × a
```

Proof: See FLM02 proof file.

### Theorem GPI-5: Kinetic energy is circulation deficit

```
E_kinetic = E_circ(rest) - E_circ(v) = ½m(c² - (c² - v²)) = ½mv²
```

Relativistically: E_kinetic = (γ - 1)mc²

### Theorem GPI-6: Time dilation from budget partition

```
v_circ = c/γ → T_clock = γ T_rest
```

The clock slows because the circulation velocity drops as translation increases.

### Theorem GPI-7: Doppler from frame-dependent observation

```
f_observed = f_rest × √((1 ± β)/(1 ∓ β))
```

Derived from the invariant pulse rate combined with closure velocity and
time dilation.

### Theorem GPI-8: Constancy stabilisation is Newton's Third Law

When acceleration stops, the asymmetry δ → 0. The flux re-symmetrises.
The reaction: every action (δ) on the knot produces an equal reorganisation
cost on the source of the force (the thing doing the pushing), because
the pushed knot's V_disp reorganisation propagates back through the relay.

---

## Success Criteria

1. F = ma derived algebraically from GPI + V_disp
2. All 5 existing laws shown to be consequences of GPI
3. Numerical verification against 8+ experimental measurements
4. Formal law section added to laws.hpp
5. C++ implementation with constexpr verification functions

---

## Data Requirements

All constants from laws.hpp — no external data needed.
This is a purely theoretical derivation from existing axioms.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FLM02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: FLM08 `lattice_structure.hpp`, FLM02/FLM05 relay mechanics
- Phase thresholds (committed before run): [commit per phase in RUN_LOG]
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

*FLM02 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
