# GD01: Eclipse Saturation Model Implementation — Codebase Question

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## THE QUESTION
GD05 (galaxy rotation curves) references galactic.hpp for the eclipse saturation model, but this file DOES NOT EXIST in the codebase. The Engine only has: laws.hpp, cosmology.hpp, neutrino.hpp, magnetosphere.hpp, state28d.hpp.

The eclipse saturation model is referenced but NEVER implemented. This is a critical gap — the galaxy rotation curve prediction (SDT's answer to dark matter) has no computational implementation.

## INVESTIGATION PROMPT

### Target
Design and derive the eclipse saturation model mathematically, then implement it.

### What Needs to Be Derived
1. **Convergence occlusion by an extended disk**: For an observer at radius r in the galactic plane, what fraction of the 4π sky is occluded by the disk?
   - Ω_disk(r) = f(Σ(r'), h, z₀, r) integrated over the disk
   
2. **Saturation criterion**: At what radius does Ω_disk → 2π (half the sky)?
   - r_sat = function of disk mass, scale length, and thickness
   
3. **Rotation velocity from occlusion**:
   - v(r)² = (c²/k²) × Ω_disk(r) / (4π) × R_gal / r
   - Below saturation: v ∝ √(M(< r)/r) — Keplerian rise
   - At saturation: v → constant — flat curve

4. **The normalization**: What determines v_flat?
   - v_flat² = (c²/k²) × (1/2) × R_gal / r_sat
   - v_flat should depend only on total baryonic mass → BTFR

### Implementation in C++
A new galactic.hpp should provide:
- `eclipse_fraction(r, disk_profile)` — solid angle computation
- `rotation_velocity(r, disk_profile)` — from eclipse model
- `v_flat(total_mass, scale_length)` — flat velocity prediction
- `btfr_prediction(log_mass)` — Baryonic Tully-Fisher prediction

### Success Criteria
- [ ] Mathematical model fully derived 
- [ ] Implemented in galactic.hpp following existing engine patterns
- [ ] Tested against 10 SPARC galaxies
- [ ] BTFR slope = 4 reproduced
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GD01
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: galactic.hpp, GD01 eclipse saturation
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

*GD01 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
