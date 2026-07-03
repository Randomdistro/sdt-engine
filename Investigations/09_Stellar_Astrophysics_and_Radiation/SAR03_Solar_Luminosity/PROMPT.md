# SAR03: Solar Luminosity from Convergence Recycling — Data/Prompt

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
| Data | Value | Source |
|------|-------|--------|
| Solar luminosity | 3.828×10²⁶ W | IAU 2015 |
| Solar radius | 6.957×10⁸ m | IAU 2015 |
| Solar surface temperature | 5778 K | IAU |
| Solar core temperature | ~1.57×10⁷ K | Standard solar model |
| CMB flux at solar surface | F_CMB | law_II |
| Solar convergence gradient | From k_Sun = 686.3 | bridge |
| Solar pressure domain | 3.12×10¹⁵ m ≈ 20,800 AU | law_II |

## INVESTIGATION PROMPT

**Target**: Derive L_Sun from the convergence recycling process.

### SDT Interpretation
The Sun is a CONVERGENCE RECYCLER (Law II). It intercepts convergence flux from 4π steradians, concentrates it through nuclear rearrangement, and re-radiates it as thermal photons. The Sun does NOT create energy — it recycles convergence.

### Methodology
1. Total convergence intercepted: P_intercepted = P_conv × f × π R_Sun² (one face)
2. Convergence throughput: the Sun converts convergence pressure into thermal radiation at rate L
3. Equilibrium: L_Sun = 4π R_Sun² σ T_eff⁴ → this IS the luminosity
4. The question is: does the SDT convergence throughput model predict T_eff = 5778 K?
5. Core temperature: T_core should relate to P_conv × f × (R_Sun/r_core)² × (occlusion fraction at core)

### Derivation Chain

> **⚠️ FARMER correction (2026-07-03, J.C.Harvey directive):** chain line 2 below is a
> TRANSCRIPTION ERROR against the founding occlusion principle — it multiplies the **full**
> convergent throughput over the whole surface by z, but the principle says the influx arrives
> everywhere and **only the occluded (blocked-by-matter) fraction does work**; the rest passes
> through. The 2026-07-03 run measured the error at ×2.5×10⁴³. The correct intent: L is built
> from the Sun's **occluded-throughput ledger** — its baryon census × per-baryon engagement (cf.
> GOM12's occlusion budget Σf = 4.19×10⁻⁹) — converted at the Law-II release rate. The missing
> closure is the **Law-II release-rate law** (cascade root: RELAY ENERGY-COUPLING MICROPHYSICS,
> STACK §3b) — that is what must be derived before this chain can run; do not re-run the full-
> throughput form. (Implied occluded-conversion fraction the law must produce:
> L/(4πR²·P_conv·c) ≈ 8.5×10⁻⁵⁰ — recorded as the target of the closure, not fished at.)

L_Sun emerges from:
1. The solar k-hierarchy: k_Sun = 686.3 → z_Sun = 2.124×10⁻⁶
2. ~~The convergence recycling rate: L = z × (4π R_Sun²) × P_conv × c~~ **[KILLED as transcribed — see correction above; replace with the occluded-fraction ledger once Law-II rate law exists]**
3. Check: does this give 3.828×10²⁶ W?

### Success Criteria
- [ ] L_Sun reproduced within 20% from convergence recycling
- [ ] T_eff derived from convergence equilibrium
- [ ] The pressure domain radius matches Oort cloud centreline
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — SAR03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_I luminosity, SAR02 mode counting
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

*SAR03 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
