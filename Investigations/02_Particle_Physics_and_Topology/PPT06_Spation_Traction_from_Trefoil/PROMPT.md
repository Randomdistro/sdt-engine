# PPT06: Spation Traction from the Trefoil — How the Gears Start

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [PPT06] PPT06: Spation Traction from the Trefoil — How the Gears Start: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## The Question

The proton is a W=3 trefoil circulating at c. The phase velocity imposed on contact spations at R_p is v_phase = c/k_surface = c/0.5464 = 1.831c — superluminal. The lattice cannot relay faster than c. What happens to the velocity deficit?

## Key Results

1. **Traction ratio** T = ω_demand/ω_max = 3(W+1) = 12 — the trefoil demands 12× the lattice's angular capacity
2. **Three output channels**: traction (ℓ=1 Coulomb), rotation (ℓ=2 magnetic), entrainment (ℓ≥3 orbits)
3. **Gear ratio** nuclear → atomic = ω_p/ω_e ≈ 10⁸ — the lattice carries the rotation from fm to pm scale
4. **Ontic vs kinetic**: CMB convergence is the fuel; trefoil circulation is the engine

## Inputs

- `laws.hpp:450-453`: k_proton_surface = 0.5464
- `CQ11_Trefoil_Confinement`: stable budget angle sin²θ* = 1/3
- `Theory/01_Closure_Derivations.md`: wake tensor ℓ-expansion

### Success Criteria
- [x] v_phase = 1.831c at proton surface derived
- [x] 6π total winding angular demand computed
- [x] Traction ratio T = 12 = 3(W+1) verified
- [x] Three channels identified and connected to wake multipoles
- [x] Gear ratio nuclear→atomic = ~10⁸ computed
- [x] Ontic/kinetic distinction formalised

### Completed: May 2026
See `INVESTIGATION.md` for the full derivation and `cq14_spation_traction.cpp` for computational verification.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_VI winding, bridge::k_*, PPT01 equilibrium
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

*PPT06 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
