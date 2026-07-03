# NP12: Nuclear Charge Radius Scaling — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP12] NP12: Nuclear Charge Radius Scaling — Investigation Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. The Question

SDT predicts nuclear charge radii scale linearly with Z (proton count), not with A^(1/3) (mass number cube root). This is a direct consequence of the occlusion model: each proton contributes R_p to the charge radius. The standard model predicts R = r₀ × A^(1/3) (liquid drop).

Which fits the data better? This is a DECISIVE test — the two models diverge sharply for neutron-rich nuclei.

## 2. Methodology

### Phase A: Compile the dataset

Download R_ch values from Angeli & Marinova (2013) for ALL measured stable isotopes (~250+). For each, compute:
- R_SDT = Z × 0.8414 fm
- R_std = 1.2 × A^(1/3) fm
- Δ_SDT = |R_meas − R_SDT|
- Δ_std = |R_meas − R_std|

### Phase B: Global comparison

1. Compute RMS deviation for each model across all isotopes
2. Compute R² for each model
3. Plot R_meas vs R_SDT and R_meas vs R_std on the same axes
4. Identify which model has smaller systematic deviations

### Phase C: Isotope chain test (critical discriminator)

For isotope chains (same Z, varying A):
- SDT predicts R_ch = CONSTANT (all isotopes of the same element have the same charge radius, because Z doesn't change)
- Standard predicts R_ch ∝ A^(1/3) (radius increases with neutron number)
- MEASURED: R_ch varies slightly along isotope chains — by how much?

Test with: Ca isotopes (Z=20: A=40,42,43,44,46,48), Sn isotopes (Z=50: A=112–124), Pb isotopes (Z=82: A=204–208).

If the isotope chain variation is < 2%, SDT's Z-scaling is essentially correct (neutrons don't contribute to charge radius). If > 5%, the A^(1/3) model captures this variation better.

### Phase D: Magic number test

At magic proton numbers (Z=2,8,20,28,50,82), both models predict specific R_ch values. Compare:
- Are magic-Z nuclei anomalously small or large?
- Does either model capture magic-number kinks?

### Phase E: Is R_ch really Z × R_p?

Test the exact proportionality: plot R_ch / Z vs Z for all elements.
- If SDT is correct: R_ch / Z = constant = R_p = 0.8414 fm
- If not: R_ch / Z should drift systematically

## 3. Required Outputs

1. **RMS comparison table**: SDT vs Standard, overall and by Z-range
2. **Isotope chain analysis**: R_ch variation within Ca, Sn, Pb chains
3. **R_ch/Z plot**: Constancy test across the periodic table
4. **Verdict**: Which model fits better overall? Is there a mass-range where SDT wins and another where Standard wins?

## 4. Success Criteria

- [ ] ≥250 isotopes included in comparison
- [ ] Both models tested with formal goodness-of-fit metrics
- [ ] Isotope chain test performed for ≥3 elements
- [ ] Clear verdict stated with supporting statistics
- [ ] If SDT loses: quantify where and why it deviates
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP12
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 2%, 5%
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

*NP12 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
