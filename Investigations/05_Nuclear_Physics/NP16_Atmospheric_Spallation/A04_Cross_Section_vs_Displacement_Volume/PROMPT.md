# NP16-A04 — Reaction cross-section and the nucleus' size (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The 2026-06-27 specification is kept below the line, superseded.

## 1. What is established (reset run 2026-10-10, `NP16A04_RESET_ASSESSMENT_2026-10-10.md`)
- **The zero-parameter law-IV displacement volume is EXCLUDED (G1) as the cross-section scale, short by about 10⁹ at every A** (6–238).
  - R_disp(proton) = 4.19e-5 R_p: the law-IV displacement radius is ten thousandths of the boundary.
  - The A^(1/3) **shape** is shared (constant ratio 1.75e-9). Only the scale fails.
- The old grammar-scaling alternative used **three fitted radii** (r_α, r_d, r_t), which makes it CALIBRATED(3). It also needs a measured dataset (EXFOR/PDG reaction cross-sections) that is not in the repo: **PENDING_DATA**.

## 2. What the error teaches
- Cross-sections are set by the **boundary** (R_p and the nucleus' contact extent), not by the law-IV displacement volume.
- This sits directly on Harvey's 2026-10-11/12 proposal: occlusion strength and emission shift share one cause, the displacement, read at the depth where the interaction happens. A projectile at nuclear contact is beyond **hydrogen's** c-boundary (z_H ≈ 1.7 at 2R_p; PPT18) and shallow in each proton's own (z_p ≈ 0.13).
- A reaction cross-section is therefore the natural observable for the displacement-modulated occlusion law **once that law is derived**.

## 3. Next round (register before computing)
1. **Data:** fetch measured p + nucleus reaction cross-sections (σ_R across A, at a fixed energy band) with provenance into `Datasets/nuclear/`.
2. **Baseline (zero-parameter, labelled convergent):** σ = π(R_p + R(A))², with R(A) = R_p (A/η)^(1/3) (NP12 canon law). This shares its form with the standard geometric cross-section and cannot discriminate. It is reported as the zero-fit scale check.
3. **Native test (after the displacement-occlusion law is registered):** the energy dependence of σ_R. The projectile's movement budget changes its contact depth; the law must predict how σ_R varies with energy, with no fitted radius.
4. **The old three-radius fit** is reported only as CALIBRATED(3).

## 4. Prohibitions
- No fitted radii labelled as derived.
- No law-IV volume as an interaction size.

---

## Superseded specification (2026-06-27, kept as written)

# A04: Cross-Section vs Displacement Volume Scaling — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [A04] A04: Cross-Section vs Displacement Volume Scaling — Investigation Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT / KILLED / OPEN).

---

## 1. Objective

Test whether the spallation reaction cross-section σ_reaction scales
with the SDT displacement volume V_disp (or equivalently, with the
displacement radius R_disp) rather than with the conventional nuclear
charge radius R_ch or the empirical A^(2/3) scaling.

If σ ∝ R_disp², SDT provides a parameter-free prediction for spallation
cross-sections from mass alone. If the scaling is different, identify
what SDT quantity provides the best predictor.

---

## 2. The Test

### Conventional scaling (null hypothesis):
$$\\sigma_{\\text{reaction}} = \\pi r_0^2 (A_p^{1/3} + A_t^{1/3})^2$$

This uses one fitted parameter: r₀ ≈ 1.2–1.3 fm. It works well but
is NOT derived from any theory — it's a fit.

### SDT scaling (test hypothesis):
$$\\sigma_{\\text{SDT}} = \\pi (R_{\\text{disp},p} + R_{\\text{disp},t})^2$$

Where R_disp is computed from the SDT displacement volume:
$$V_{\\text{disp}} = \\frac{3m \\ell_P^3 c^2}{\\Phi}$$
$$R_{\\text{disp}} = \\left(\\frac{3V_{\\text{disp}}}{4\\pi}\\right)^{1/3}$$

This uses ZERO fitted parameters — everything is derived from SDT
constants and the measured mass.

### Grammar scaling (alternative SDT hypothesis):
$$\\sigma_{\\text{gram}} = \\pi R_{\\text{gram}}^2$$

Where R_gram is a function of the grammar block count:
$$R_{\\text{gram}} = r_\\alpha \\cdot n_\\alpha^{1/3} + r_d \\cdot n_d^{1/3} + r_t \\cdot n_t^{1/3}$$

This tests whether the nuclear size scales with GRAMMAR structure
rather than with total nucleon count.

---

## 3. Methodology

### Phase A: Assemble the dataset

For ≥30 nuclides spanning A = 6 (Li-6) to A = 238 (U-238):

1. Look up σ_reaction(p, 100 MeV) from EXFOR
   - Use the reaction cross-section (= total − elastic)
   - If not available at exactly 100 MeV, interpolate from nearby energies
   - Record uncertainty

2. Look up R_ch from Angeli & Marinova 2013

3. Compute V_disp and R_disp from SDT formulas:
   - V_disp = 3 × m_nucleus × ℓ_P³ × c² / Φ
   - Use atomic mass from AME2020 (in kg)
   - R_disp = (3V_disp / 4π)^(1/3)

4. Compute grammar (α, d, t) for each target

5. Tabulate: A, Z, N, R_ch, R_disp, V_disp, n_α, n_d, n_t, σ_reaction

### Phase B: Scaling law fits

For each scaling hypothesis, perform a log-log fit:

1. **Conventional**: log(σ) vs log(A^(1/3) + 1)
   - Expected slope: 2 (geometric scaling)
   - Fit: σ = C₁ × (A^(1/3) + 1)^α₁
   - Report: C₁, α₁, R², χ²_red

2. **SDT displacement**: log(σ) vs log(R_disp,p + R_disp,t)
   - Expected slope: 2 (geometric scaling)
   - Fit: σ = C₂ × (R_disp,p + R_disp,t)^α₂
   - Report: C₂, α₂, R², χ²_red
   - **Critical test**: Is C₂ = π? If so, the SDT prediction is exact.

3. **Measured radius**: log(σ) vs log(R_ch,p + R_ch,t)
   - Fit: σ = C₃ × (R_ch,p + R_ch,t)^α₃
   - Report: C₃, α₃, R², χ²_red

4. **Grammar blocks**: log(σ) vs log(n_α + n_d + n_t)
   - Fit: σ = C₄ × (n_blocks)^α₄
   - Report: C₄, α₄, R², χ²_red

### Phase C: Identify the best model

Compare all 4 models by:
- R² (higher is better)
- χ²_red (closer to 1 is better)
- Number of fitted parameters (fewer is better)
- Whether the fitted parameters match SDT predictions (C = π?)
- Residual pattern (systematic deviations at magic numbers?)

### Phase D: Residual analysis

For the best-fit model:

1. Plot residuals (σ_measured − σ_predicted) vs A
2. Look for systematic deviations:
   - At magic numbers (A near 40, 56, 90, 208)?
   - At large neutron excess (N − Z \u003e 20)?
   - At nuclear deformation (β₂ \u003e 0.2)?
3. If systematic deviations exist, determine whether adding a grammar
   correction term (e.g., shell occupancy fraction) removes them

### Phase E: Energy dependence

Repeat Phases A–C at:
- 200 MeV
- 1 GeV
- 3 GeV (if data available)

Does the best scaling model change with energy? SDT predicts it should
not (the displacement volume is energy-independent), but the effective
interaction radius may increase at higher energies due to wake
extension.

---

## 4. Required Outputs

1. **Master data table**: 30+ rows with A, Z, N, R_ch, R_disp, V_disp,
   grammar, σ_reaction at 100 MeV

2. **Log-log plots** (described textually): Four plots showing
   σ vs the four candidate scaling variables

3. **Fit summary table**:
   | Model | Fitted C | Fitted α | R² | χ²_red | Parameters |
   |-------|---------|---------|-----|--------|------------|
   | Conventional | ? | ? | ? | ? | 1 (r₀) |
   | SDT disp | ? | ? | ? | ? | 0 |
   | Measured R | ? | ? | ? | ? | 0 |
   | Grammar | ? | ? | ? | ? | 0 |

4. **Verdict**: Which model best describes the data? Is SDT displacement
   volume a BETTER predictor than conventional A^(2/3)?

5. **Parameter-free prediction accuracy**: For the SDT model with C = π
   fixed (no fitting at all), what is the mean absolute percentage error?

---

## 5. Success Criteria

- [ ] ≥30 nuclides included in the analysis
- [ ] All 4 scaling models tested with formal goodness-of-fit metrics
- [ ] SDT displacement model tested with ZERO fitted parameters
- [ ] Residual analysis identifies any systematic grammar-related deviations
- [ ] Energy dependence checked at ≥2 energies
- [ ] Clear verdict on which model provides the most accurate and
      most parsimonious description
- [ ] If SDT wins: the r₀ parameter is explained (derived from SDT
      constants). If SDT loses: the failure mode is identified.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — A04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
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
| A rival lands on the same number | adjudicate by **origin** (gateway procedural §3.8): SDT-origin route ⇒ **CONVERGENCE**; a *named* contaminating input ⇒ **SHARED-INPUT**; state discrimination separately | — | downgrade a convergent result because a rival formula agrees; claim discrimination the numbers do not show *(row corrected 2026-10-03 — the stamped alignment row was excluded 2026-07-26)* |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*A04 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
