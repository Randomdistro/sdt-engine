# NP03C — Trefoil Nucleon Topology *(embodiment; positions FROZEN from NP03B)*

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP03C] NP03C — Trefoil Nucleon Topology *(embodiment; positions FROZEN from NP03B)*: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

**Purpose.** Replace balls/sticks with the real nucleon topology — each nucleon a 6π (2,3) trefoil / toroidal structure — **at the positions NP03B already solved**. Rendering is *not* evidence; this stage builds the substrate NP03D tests for threading.

**Inputs.** NP03B positions (**frozen** — may not be moved).
**Outputs.** Per nucleon: an oriented (2,3) trefoil tube at its NP03B site; tube radius at `R_p ≈ 0.84 fm` scale.

**Formulations.**
```
trefoil (2,3):  x=(R+r cos3t)cos2t,  y=(R+r cos3t)sin2t,  z=r sin3t  (6π winding, W=3)
orientation:    knot axis = radial direction of the NP03B block site
tube scale:     R_p = 4ℏ/(m_p c) = 0.84124 fm   (laws.hpp::winding, frozen)
```

**Hard rule.** Topology is **imposed on** solved positions — it may not perturb them by even one step. A position-drift check (NP03C site == NP03B site, exactly) is mandatory.

**Fixed metrics.** (i) knot closure (curve returns to start), correct (2,3) crossing number = 3; (ii) radial orientation per site; (iii) **zero position drift** vs NP03B; (iv) `R_p` tube scale matches `laws.hpp`.

**Failure criteria.** Any nucleon position differs from NP03B; degenerate/self-intersecting tube where a trefoil should not; tube scale silently retuned.

**Reuses.** `laws.hpp::winding` (R_p), `PPT05`/`PPT06` (trefoil mechanics). **Provenance:** class **B** (internal embodiment).
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP03C
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
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

*NP03C · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
