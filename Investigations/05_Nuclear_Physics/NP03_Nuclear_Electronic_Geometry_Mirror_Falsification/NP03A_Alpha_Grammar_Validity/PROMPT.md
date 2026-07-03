# NP03A — Alpha-Grammar Validity *(Claim 1: arithmetic only — proves NO geometry)*

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP03A] NP03A — Alpha-Grammar Validity *(Claim 1: arithmetic only — proves NO geometry)*: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

**Purpose.** Certify, electron-free, that every isotope maps cleanly to `1α + n_d·d + n_t·t`. This is the clean foundation; it must never be used to justify geometry (that is NP03E).

**Inputs.** Full isotope table `(Z, A)` (stable + unstable). **No electron data.**
**Outputs.** Per isotope: `(n_d, n_t)`, validity, and the four decay-transition vectors.

**Formulations (frozen, `nuclear.hpp`):**
```
n_t = A − 2Z ,  n_d = 3Z − A − 2 ;  inverse  Z = 2 + n_d + n_t ,  A = 4 + 2n_d + 3n_t
decay vectors in (n_d,n_t):  α:(−2,0)  β⁻:(+3,−2)  EC:(−3,+2)  n:(+1,−1)
```

**Fixed metrics.** (i) fraction of isotopes with `n_d,n_t ≥ 0` satisfying the inverse exactly; (ii) decay-vector closure (every transition lands on a valid lattice point); (iii) the 7 `nuclear.hpp` aggregate `static_assert`s pass.

**Null / negative control.** Random `(n_d,n_t)` assignment must **fail** the inverse map (`Z=2+n_d+n_t, A=4+2n_d+3n_t`) for ≥ almost all isotopes — proving the map carries information.

**Failure criteria.** Any stable isotope failing the inverse; any decay vector breaking charge/baryon conservation; aggregate asserts fail.

**Status.** Largely DONE — `nuclear.hpp` static_asserts + `NP01` already certify this. NP03A re-runs it as the electron-blind foundation and emits the decay-vector table for NP03E's count/closure metric.

**Reuses.** `nuclear.hpp`, `NP01`. **Provenance:** class **C**.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP03A
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

*NP03A · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
