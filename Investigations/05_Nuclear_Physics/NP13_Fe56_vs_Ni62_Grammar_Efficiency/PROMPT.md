# NP13: Fe-56 vs Ni-62 Grammar Efficiency — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP13] NP13: Fe-56 vs Ni-62 Grammar Efficiency — Data/Prompt: **Measurable gap (written 2026-10-05 in the audit correction pass, from this prompt's own content; the 2026-06-27 template left it unfilled):** Is Fe-56 or Ni-62 the more efficiently packed nucleus under the constitutional alpha-core + deuteron + triton grammar (measured B/A 8.790 and 8.794 MeV), and does packing efficiency explain the maximum of B/A?
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT / KILLED / OPEN).

## DATA REQUIREMENTS
| Data | Value | Source |
|------|-------|--------|
| B/A for Fe-56 | ~~8.790~~ 8.7904 MeV/n (8790.356 keV) | AME2020 |
| B/A for Ni-62 | ~~8.795~~ 8.7946 MeV/n (8794.556 keV) | AME2020 |
| Fe-56 grammar | ~~5α + 6d + 6t (26p, 30n)~~ α + 20d + 4t (26p, 30n) | ATOMICUS grammar: n_t = A − 2Z = 4, n_d = 3Z − A − 2 = 20 |
| Ni-62 grammar | ~~5α + 6d + 9t (28p, 34n)~~ α + 20d + 6t (28p, 34n) | ATOMICUS grammar: n_t = 6, n_d = 20 |
| Fe-56 cosmic abundance | Most abundant metal | Solar abundances |
| Ni-62 abundance | ~3.6% of nickel | NNDC |
| Triton fraction: Fe-56 | ~~6t / (6d + 6t) = 50%~~ 4t / (20d + 4t) = 16.7% | Grammar |
| Triton fraction: Ni-62 | ~~9t / (6d + 9t) = 60%~~ 6t / (20d + 6t) = 23.1% | Grammar |

> **Data correction 2026-10-11 (Harvey's instruction; input defect, not a claim result).** The grammar rows, the triton fractions and the B/A values in the table above were inconsistent with the constitutional grammar (one α core plus n_d deuterons plus n_t tritons): the old multiplicities summed to Z = 22 and 25, not 26 and 28. Corrected from n_t = A − 2Z and n_d = 3Z − A − 2 and from AME2020; the old values are struck through, not deleted. The two worked lines in the Methodology (items 2 and 3) are recomputed from the corrected counts. The claim itself (the SDT prediction on line "Fe-56's grammar is MORE symmetric…") is unchanged and is tested on the corrected inputs. The Pre-Run thresholds "50%, 60%" refer to the old triton fractions and are superseded by the audit correction below (gate on B/A only).

## INVESTIGATION PROMPT

**Target**: Explain why Fe-56 is more cosmically abundant than Ni-62 despite Ni-62 having higher B/A.

### SDT Prediction
Fe-56's grammar is MORE symmetric (equal d and t count) → geometrically optimal. Ni-62 has a triton excess → less symmetric scaffold.

### Methodology
1. Compute the "grammar efficiency" metric for both: symmetry = |n_d − n_t| / (n_d + n_t)
2. Fe-56: ~~|6−6|/12 = 0 (perfect symmetry)~~ |20−4|/24 = 0.667 (corrected counts)
3. Ni-62: ~~|6−9|/15 = 0.2 (asymmetric)~~ |20−6|/26 = 0.538 (corrected counts)
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
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
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
| A rival lands on the same number | adjudicate by **origin** (gateway procedural §3.8): SDT-origin route ⇒ **CONVERGENCE**; a *named* contaminating input ⇒ **SHARED-INPUT**; state discrimination separately | — | downgrade a convergent result because a rival formula agrees; claim discrimination the numbers do not show *(row corrected 2026-10-03 — the stamped alignment row was excluded 2026-07-26)* |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*NP13 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

## Audit correction 2026-10-05 (gating)

**Finding:** The thresholds include 50% and 60%, and the sign-off is "FAIL on stated thesis; PASS on grammar audit (quoted, modifier omitted)", scoring documentation as a PASS.

**Correction:** Gate B/A at ≤ 3.6% only and drop the audit item from the tally.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
