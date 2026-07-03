# NP07: Primordial Lithium Resolution — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP07] NP07: Primordial Lithium Resolution — Data/Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## DATA REQUIREMENTS

| Data | Value | Source |
|------|-------|--------|
| BBN predicted Li-7/H ratio | (4.68 ± 0.67) × 10⁻¹⁰ | Cyburt et al. 2016 |
| Observed Li-7/H ratio (Spite plateau) | (1.58 ± 0.31) × 10⁻¹⁰ | Sbordone et al. 2010 |
| Discrepancy factor | ~3× (BBN overproduces Li-7) | The "lithium problem" |
| Li-7 grammar | α + d + t (3 blocks, 1 triton) | ATOMICUS/003_Li7.md |
| Li-6 grammar | α + d (2 blocks, 0 tritons) | ATOMICUS/003_Li6.md |
| Be-7 half-life (EC) | 53.22 d | NNDC |
| Be-7 grammar | α + d (EC isotope) | ATOMICUS |
| Be-7 → Li-7 by EC | Grammar correction: Δn_tri = +2, Δn_deu = −3 | SDT EC rules |

## INVESTIGATION PROMPT

**Target**: Determine whether SDT's grammar rules alter the predicted primordial Li-7 abundance.

### The Problem

Standard BBN predicts 3× more Li-7 than observed. The primordial Li-7 comes from Be-7 EC decay (Be-7 + e⁻ → Li-7 + ν). If SDT modifies the Be-7 EC rate or the Be-7 production rate, this changes the predicted Li-7 abundance.

### SDT-Specific Considerations

1. **Be-7 EC rate**: SDT predicts EC rates depend on charge state (INVESTIGATION_11_Anionisation). In the early universe, Be-7 is FULLY ionised — NO bound electrons. SDT: fully ionised Be-7 CANNOT undergo EC (no electron in the scaffold). This suppresses Li-7 production during the brief window before Be-7 captures an electron from the cooling plasma.

2. **Modified Be-7 survival**: If Be-7 EC is delayed (waiting for recombination to provide electrons), more Be-7 is destroyed by p + Be-7 → B-8 or other reactions before it can decay to Li-7.

3. **Grammar transition timing**: The Be-7 → Li-7 EC requires an electron. In SDT, the electron must reach the nuclear surface. At high T (early universe), electron kinetic energy means high v_trans → low v_circ (movement budget). An electron with low circulation may not couple to the Be-7 scaffold efficiently → further suppression.

### Calculation

1. Compute the temperature at which Be-7 first captures a bound electron (recombination of Be-7)
2. During the interval t_BBN to t_recombine(Be-7), compute how much Be-7 is destroyed by competing reactions
3. Compare the surviving Be-7 → Li-7 flux to the observed abundance
4. Does the SDT-modified EC timing resolve the 3× discrepancy?

### Success Criteria
- [ ] The ionisation-suppressed EC delay is quantified
- [ ] The resulting Li-7/H ratio is computed
- [ ] If the ratio drops from 4.68 to ~1.6 × 10⁻¹⁰: the lithium problem is resolved
- [ ] The resolution uses SDT grammar rules (EC requires bound electron)
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP07
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

*NP07 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
