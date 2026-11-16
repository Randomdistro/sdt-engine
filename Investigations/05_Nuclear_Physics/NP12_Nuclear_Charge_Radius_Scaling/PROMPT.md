# NP12 — Nuclear boundary radius scaling (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The 2026-06-27 specification is kept below the line, superseded. "Charge radius" in the old title is the IAEA's label; here it is the **boundary radius**.

## 1. What is established (reset run 2026-10-10, `NP12_RESET_ASSESSMENT_2026-10-10.md`; 908 IAEA radii)
| model | RMS rel. dev. | R² | status |
|---|---|---|---|
| Z·R_p (old premise) | 890.8% | −3282 | **EXCLUDED (G1)**: a 1-D sum cannot fill a volume |
| 1.2 A^(1/3) (old rival) | 25.6% | −1.46 | partly a convention mismatch (edge radius against RMS radius, factor √(3/5)) |
| **R_p (A/η)^(1/3), η = π/√18 (canon, NP30 §6)** | **4.96%** | 0.961 | re-verified; the number was known from the engine comment, so it is **not blind** |

**Isotope chains** (60 elements with ≥ 5 isotopes): radii **grow by 2.36% on average over ΔN ≈ 15**, against 5.10% from A^(1/3). The old "constant along chains" prediction is **excluded (G1)**.

## 2. What the errors teach
- **The canon law has the right volume scaling but the wrong chain slope.** It predicts the A^(1/3) rate (5.1%); measured is about half that.
- **NP30 §6 and the triton-contraction rule supply the native mechanism:** added neutrons arrive as tritons that draw the boundary in (−11 mfm/triton heavy; endpoint r₀ → 0.9300 fm derived; slope "reproduced at −9.5…−11" from the r₀(f_t) approach).
- **The chain slope is therefore the discriminating observable,** and it was not used to build the volume law.

## 3. Next round (round 2; register before computing)
- **H2:** R(Z, N) = R_p (A/η_eff(f_t))^(1/3). Here η_eff rises toward close-pack as the triton fraction f_t = n_t/(n_d + n_t + 1) rises. The functional form of η_eff(f_t) is to be written **from NP30 §6's r₀(f_t) approach before any chain is loaded**, with the deuteron-offset term (NP30 "owed") declared as the one open element.
- **Observable:** per-chain fractional growth over ΔN for the 60 chains (not the volume RMS, which is already known).
- **Gate (cascade):** median per-chain slope error ≤ 3% (B3). Report the slope ratio predicted/measured, with A^(1/3) at 2.16× as the null.
- **Companion:** NP12f round 2 (live-sequencer point radii, running 2026-10-12) reports whether the built construction carries size at all. If it does, the same chain slope test is applied to the built nuclei.

## 4. Prohibitions
- No fitted η.
- No re-scoring of the exposed 4.96%.
- The word "charge" is not used for the boundary.
- Grammar counts (f_t) are shared-input with (Z, N) (NP24). The test is the **slope prediction**, not membership.

---

## Superseded specification (2026-06-27, kept as written)

# NP12: Nuclear Charge Radius Scaling — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [NP12] NP12: Nuclear Charge Radius Scaling — Investigation Prompt: **Measurable gap (written 2026-10-05 in the audit correction pass, from this prompt's own content; the 2026-06-27 template left it unfilled):** Which scaling of the nuclear boundary radius, linear in Z or the volume-additive A^(1/3) close-pack form, fits the measured radii, and with what residual and no free coefficient beyond a declared diagnostic?
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT / KILLED / OPEN).

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
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
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
| A rival lands on the same number | adjudicate by **origin** (gateway procedural §3.8): SDT-origin route ⇒ **CONVERGENCE**; a *named* contaminating input ⇒ **SHARED-INPUT**; state discrimination separately | — | downgrade a convergent result because a rival formula agrees; claim discrimination the numbers do not show *(row corrected 2026-10-03 — the stamped alignment row was excluded 2026-07-26)* |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*NP12 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The premise is that nuclear radii scale linearly with Z by adding proton radii in one dimension (Z·R_p), which is 890.8% off and dimensionally wrong for a volume-filling object.

**Correction:** State the premise as volume-additive (close-pack A^(1/3) form, already recovered) and gate that form against the measured radii.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
