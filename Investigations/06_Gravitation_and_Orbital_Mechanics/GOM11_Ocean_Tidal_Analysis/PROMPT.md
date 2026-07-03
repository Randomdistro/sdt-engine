# GOM11: Ocean Tidal Analysis — SDT Pressure vs Newton Potential — Data/Prompt

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
| Data | Source |
|------|--------|
| Global tidal harmonic coefficients (M2, S2, N2, K1, O1) | FES2014 / GOT4.10 |
| Earth-Moon orbital parameters | JPL Horizons |
| Earth-Sun orbital parameters | JPL Horizons |
| Measured tidal amplitudes at ≥20 stations | NOAA/IOC tide gauges |
| Love numbers (h₂, k₂, l₂) | IERS |

## INVESTIGATION PROMPT

**Target**: Compute tidal forcing from SDT convergence gradient and compare to Newtonian tidal potential.

### SDT Tidal Model
Tides arise from the GRADIENT of convergence pressure across Earth's diameter:
- The Moon creates a convergence deficit (occlusion) that is stronger on the near side than the far side
- This differential pressure → tidal bulge
- SDT predicts: F_tidal = d/dr [F_occlusion] × (R_Earth)

$$F_{\text{tidal}} \propto \frac{R_1^2 R_2^2}{r^3} \times R_{\text{Earth}}$$

This has the SAME r⁻³ dependence as the Newtonian tidal force (since Newtonian tidal ∝ GM/r³). The SDT tidal amplitude should match the measured M2 amplitude.

### Methodology
1. Compute the SDT tidal force differential across Earth's body for the Moon
2. Compare M2 amplitude prediction to measured ~0.63 m mean
3. Compute same for the Sun (S2 component)
4. Check the M2/S2 ratio — should be ~2.17 (Moon/Sun tidal ratio)

### Success Criteria
- [ ] M2 tidal amplitude predicted within 10%
- [ ] M2/S2 ratio matches measured value
- [ ] SDT tidal force reduces algebraically to the Newtonian tidal expression
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM11
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: bridge::koppa_*, depth_closure::, no G/M
- Phase thresholds (committed before run): 10%
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

*GOM11 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
