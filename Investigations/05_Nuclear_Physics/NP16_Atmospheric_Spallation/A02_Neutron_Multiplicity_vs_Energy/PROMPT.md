# A02: Neutron Multiplicity vs Energy Scaling — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [A02] A02: Neutron Multiplicity vs Energy Scaling — Investigation Prompt: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. Objective

Determine whether SDT grammar parameters (triton count, open neutron
count, triton fraction, shell closure proximity) can predict the neutron
multiplicity in (p,xn) spallation reactions as a function of incident
proton energy, WITHOUT using fitted parameters from conventional
nuclear physics (level density parameter, optical model potentials, etc.).

---

## 2. Scope

For a systematically chosen set of 20 targets spanning Z=13–83
(see DATA_REQUIREMENTS.md for the full list), collect all available
(p,xn) excitation function data from EXFOR and test whether the
following SDT quantities predict:

1. The THRESHOLD ENERGY for each (p,xn) channel
2. The PEAK CROSS-SECTION of each channel
3. The MAXIMUM MULTIPLICITY at any given energy
4. The AVERAGE MULTIPLICITY <ν> at standardised energies (200 MeV,
   800 MeV, 1.4 GeV)

---

## 3. Methodology

### Phase A: Data collection and tabulation

For each of the 20 targets:

1. Download all (p,xn) excitation functions from EXFOR (x = 1 to max)
2. For each channel, extract: E_thr, E_peak, σ_peak, FWHM
3. Tabulate the target grammar parameters: n_d, n_t, n_tri, n_deu,
   triton fraction, n_o, |N − N_magic|, β₂, R_nuc, S_n, S_2n

### Phase B: Threshold energy correlations

For each channel opening (x = 1,2,3,4,...):

1. Plot E_thr(p,xn) vs the cumulative SDT ejection cost:
   - SDT hypothesis: E_thr(x) = Σᵢ₌₁ˣ E_bond(nᵢ)
   - Where E_bond(n_o) = ℓ≥3 coupling only (lower)
   - And E_bond(n_c) = ℓ≥3 coupling + scaffold bridge (higher)
   - First approximation: E_bond ≈ S_n from AME2020

2. Correlate E_thr with grammar parameters:
   - Does E_thr scale with triton fraction? (more tritons → lower per-
     neutron cost for the first few ejections, because n_o are cheap?)
   - Does E_thr jump at shell closures? (magic N → all neutrons are
     tightly bound → high threshold?)
   - Does E_thr correlate with n_deu? (more deuterons → more rigid
     scaffold → higher threshold?)

3. Compute correlation coefficients (Pearson r, Spearman ρ) for each
   candidate predictor

### Phase C: Peak cross-section correlations

For the dominant channel at E = 40 MeV:

1. Plot σ_peak vs target grammar parameters
2. Hypothesis: σ_peak ∝ n_o (more open neutrons → larger probability
   of ejection → larger cross-section)
3. Alternative: σ_peak ∝ R_nuc² (purely geometric — larger nucleus →
   larger cross-section)
4. Test: is grammar (n_o) a better predictor than geometry (R²)?
   Compute both correlations and report which is tighter.

### Phase D: Maximum multiplicity at fixed energy

At E_p = 200 MeV (standard comparison point):

1. For each target, determine x_max (the highest channel with
   measurable cross-section, σ > 0.1 mb)
2. Plot x_max vs:
   - A (mass number) — conventional scaling
   - N (neutron number) — neutron availability
   - n_o (open neutron count) — SDT grammar prediction
   - n_t (total triton count) — SDT grammar prediction
   - N − N_magic (distance from magic) — shell effect

3. Fit each: x_max = a × (predictor) + b
4. Report R² for each fit
5. Identify which predictor explains the most variance

### Phase E: The SDT scaling law

From Phases B–D, propose a unified formula:

$$\\langle\\nu\\rangle(E, Z, A) = f(n_o, n_t, S_n, E)$$

Requirements:
- Must use ONLY grammar-derived quantities (not level density, not
  optical model)
- Must reduce to zero below threshold
- Must saturate at high energy (can't eject more neutrons than exist)
- Must show shell closure effects (reduced ν near magic N)

Compare the formula's predictions against ALL 20 targets at ALL
measured energies. Report:
- Mean absolute deviation
- Maximum deviation
- Whether any systematic trend in the residuals suggests a missing
  parameter

---

## 4. Required Outputs

1. **Data table**: 20 rows (one per target), with columns for Z, A, N,
   n_d, n_t, n_tri, n_deu, triton fraction, n_o, |N−N_magic|, β₂,
   R_nuc, S_n, S_2n, E_thr(p,1n), E_thr(p,2n), σ_peak(p,1n),
   σ_peak(p,2n), x_max(200 MeV), <ν>(200 MeV)

2. **Correlation matrix**: A matrix showing Pearson r between every pair
   of grammar parameters and every measured observable

3. **Best predictor identification**: Which grammar parameter(s)
   provide the best prediction of multiplicity? Rank them.

4. **Proposed scaling law**: Closed-form expression with justification

5. **Residual analysis**: Plot of (predicted − measured) vs A, Z, N
   to check for systematic biases

6. **Shell closure analysis**: Separate plot showing how ν deviates
   from the scaling law at magic numbers (N=20, 28, 50, 82, 126)

---

## 5. Success Criteria

- [ ] Data collected for ≥18/20 targets (some may lack EXFOR coverage)
- [ ] At least one grammar parameter achieves R² > 0.7 with x_max
- [ ] Threshold energies are reproduced within 30% for ≥15 targets
- [ ] Shell closure effects are visible in the data and captured by
      the scaling law
- [ ] The scaling law uses only grammar + measured constants (c, ℏ)
- [ ] Residual analysis shows no systematic trend with A or Z
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — A02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: NP01 grammar, law_III nuclear occlusion, ATOMICUS rules
- Phase thresholds (committed before run): 30%
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

*A02 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
