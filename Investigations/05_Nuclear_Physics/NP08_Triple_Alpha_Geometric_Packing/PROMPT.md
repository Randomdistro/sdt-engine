# NP08: Triple-Alpha Rate from Geometric Packing — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP08] NP08: Triple-Alpha Rate from Geometric Packing — Data/Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## DATA REQUIREMENTS

| Data | Value | Source |
|------|-------|--------|
| C-12 ground state mass | 12.000000 u (definition) | AME2020 |
| He-4 mass | 4.002603 u | AME2020 |
| 3 × He-4 mass | 12.007809 u | Computed |
| Mass excess = 3×m_α − m_C12 | 7.275 MeV | Q-value |
| Hoyle state energy | 7.654 MeV above C-12 g.s. | Measured |
| Hoyle state width | 8.5 eV | Measured |
| C-12 grammar | 1 alpha + 4 deuterons | ATOMICUS/006_C12.md |
| Alpha geometry | Tetrahedral (2p+2n) | SDT |

## INVESTIGATION PROMPT

**Target**: Derive the Hoyle state energy (7.654 MeV) from the geometric packing energy of 4 deuterons closing around an alpha core.

### SDT Interpretation

C-12 is NOT three alphas. It is 1 alpha core + 4 deuterons (α + 4d). The "triple-alpha" process is actually:
1. α + α → Be-8* (unstable — immediately decays unless...)
2. α + Be-8* → C-12* (Hoyle state) → C-12 + γ

SDT re-reads this as:
1. Two alpha cores approach → their ℓ≥3 wakes overlap → forms Be-8 (2α, no deuterons)
2. Be-8 grammar: 2α + 0d is UNSTABLE in SDT (no scaffold bonds — two standalone alphas)
3. A third alpha approaches → the combined 12 nucleons rearrange into α + 4d (C-12 grammar)
4. The 7.654 MeV Hoyle state = the geometric threshold for tetrahedral closure of the 4 deuterons around the central alpha

### Calculation

1. Compute the tetrahedral closure energy: 4 deuterons at the vertices of a tetrahedron surrounding a central alpha → the packing energy when the deuterons lock into their scaffold positions
2. Energy = sum of all d-α occlusion bonds + d-d occlusion bonds − Coulomb repulsion between the 4 deuterons' protons
   — NOTE (2026-07-03): NP09's scalar-occlusion route FAILED (−97.3%) and FLM12-D1 ruled the linear volume-price out at 34×; revise the premise before execution.
3. Compare to 7.654 MeV

### Success Criteria
- [ ] Hoyle state energy derived within 20% of 7.654 MeV
- [ ] The instability of Be-8 explained by grammar (2α + 0d = unbonded)
- [ ] The C-12 grammar (α + 4d) confirmed as the stable endpoint
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP08
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 20%
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

*NP08 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
