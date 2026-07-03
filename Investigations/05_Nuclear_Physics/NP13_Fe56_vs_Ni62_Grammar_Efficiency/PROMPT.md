# NP13: Fe-56 vs Ni-62 Grammar Efficiency — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP13] NP13: Fe-56 vs Ni-62 Grammar Efficiency — Data/Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| B/A for Fe-56 | 8.790 MeV/n | AME2020 |
| B/A for Ni-62 | 8.795 MeV/n | AME2020 |
| Fe-56 grammar | 5α + 6d + 6t (26p, 30n) | ATOMICUS |
| Ni-62 grammar | 5α + 6d + 9t (28p, 34n) | ATOMICUS |
| Fe-56 cosmic abundance | Most abundant metal | Solar abundances |
| Ni-62 abundance | ~3.6% of nickel | NNDC |
| Triton fraction: Fe-56 | 6t / (6d + 6t) = 50% | Grammar |
| Triton fraction: Ni-62 | 9t / (6d + 9t) = 60% | Grammar |

## INVESTIGATION PROMPT

**Target**: Explain why Fe-56 is more cosmically abundant than Ni-62 despite Ni-62 having higher B/A.

### SDT Prediction
Fe-56's grammar is MORE symmetric (equal d and t count) → geometrically optimal. Ni-62 has a triton excess → less symmetric scaffold.

### Methodology
1. Compute the "grammar efficiency" metric for both: symmetry = |n_d − n_t| / (n_d + n_t)
2. Fe-56: |6−6|/12 = 0 (perfect symmetry)
3. Ni-62: |6−9|/15 = 0.2 (asymmetric)
4. Extend to ALL stable nuclei: compute B/A vs grammar symmetry
5. Is the most abundant isotope at each Z always the most symmetric?
6. Do magic numbers (Z=2,8,20,28,50,82) correspond to grammar symmetry maxima?

### Success Criteria
- [ ] Fe-56's abundance explained by grammar symmetry
- [ ] Correlation between grammar symmetry and natural abundance established
- [ ] Pattern extended to all elements Z=1–83
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP13
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 3.6%, 50%, 60%
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

*NP13 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
