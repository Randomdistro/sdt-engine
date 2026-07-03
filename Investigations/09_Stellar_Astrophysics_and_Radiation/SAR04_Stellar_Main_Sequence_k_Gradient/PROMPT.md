# SAR04: Stellar Main Sequence from k-Gradient — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## DATA REQUIREMENTS

| Data | Source | Content |
|------|--------|---------|
| GAIA DR3 HR diagram | ESA GAIA | L, T_eff, R for ~10⁶ stars |
| Stellar orbital velocities | Binary surveys / spectroscopic | Surface/orbital v for k computation |
| Main sequence L-M relation | Eker et al. 2018 | L ∝ M^3.5 |
| Stellar radii compilation | Torres et al. 2010 | R vs M for MS stars |
| Solar k value | k_Sun = 686.3 | laws.hpp bridge |
| Solar R, L, T_eff | IAU 2015 nominal | Calibration point |

## INVESTIGATION PROMPT

**Target**: Map the main sequence to a k-gradient equilibrium sequence.

### SDT Prediction

Each star has a k-value: k = c / v_surface (where v_surface is the escape/orbital velocity at the stellar surface). Hot blue stars have low k (strong convergence — compact, massive), cool red stars have high k (weak convergence — diffuse, low-mass).

The main sequence should be a CONTINUOUS k-sequence. Compute k for each spectral class:
- O star (v_esc ~ 1000 km/s): k ≈ 300
- B star: k ≈ 400  
- Sun (G2V): k = 686.3
- M dwarf (v_esc ~ 200 km/s): k ≈ 1500

### Methodology

1. For each star with measured M, R, L: compute k = c / √(2GM/R)
2. Plot k vs L, k vs T_eff, k vs M
3. Is the main sequence a monotonic function of k?
4. Does the mass-luminosity relation L ∝ M^3.5 emerge from the k-gradient?
5. Does the pressure domain radius (r_domain = √(L / 4π F_CMB)) correlate with the star's Roche lobe in binary systems?

### Success Criteria
- [ ] k computed for ≥50 main sequence stars spanning O–M
- [ ] MS is a monotonic k-sequence 
- [ ] L vs k relationship identified (power law? exponential?)
- [ ] Solar k = 686.3 sits correctly on the sequence
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — SAR04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_I luminosity, SAR02 mode counting
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

*SAR04 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
