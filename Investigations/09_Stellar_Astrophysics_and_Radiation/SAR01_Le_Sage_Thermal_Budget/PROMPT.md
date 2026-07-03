# SAR01: Le Sage Thermal Budget — Data/Prompt

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
| Solar convergence absorbed | L_conv = ∫ F_conv · dA over solar surface | SDT derivation |
| CMB flux F_CMB | 3.131×10⁻⁶ W/m² | law_II |
| Solar surface area | 6.08×10¹⁸ m² | From R_Sun |
| Total intercepted CMB | F_CMB × πR²_Sun ≈ 4.77×10⁷ W | Computed |
| Earth thermal budget | 173 PW solar + 47 TW geothermal | Measured |
| Convergence heating prediction | Depends on occlusion fraction | To compute |

## INVESTIGATION PROMPT

**Target**: Compute the thermal budget of an eclipsing body in the convergence field. Does convergence absorption produce detectable heating?

### The Le Sage Problem

> **⚠️ FARMER correction (2026-07-03, J.C.Harvey directive):** the premise line below —
> "matter **absorbs** convergence flux" — is a TRANSCRIPTION ERROR against the founding
> occlusion principle. The influx is a **throughpole** (in/out, never terminates); occlusion is
> **redirection/blocking**, not capture; the work is pressure-asymmetry work, not energy
> deposition. The branch's real question is therefore NOT "how much is absorbed" but: **does the
> elastic redirection have ANY thermalisation leakage?** The 2026-07-03 run earned the ceiling:
> η < 4.4×10⁻¹⁸ (any larger leakage exceeds the 47 TW geothermal budget) — that ceiling is the
> branch's falsifiable number. The named remaining open is Maxwell's elastic-refill objection:
> what restores the isotropy of the redirected flux (the recharge mechanism) — same root as the
> Law-II release-rate law (STACK §3b, RELAY ENERGY-COUPLING MICROPHYSICS).

If gravity = convergence occlusion, then matter ~~absorbs~~ **redirects (occludes)** convergence flux. Classical Le Sage theories fail because their corpuscles must be absorbed (momentum transfer by capture) and the absorption would melt everything. SDT's structural difference:

1. The transfer function f = 2.125×10⁻¹⁷ means only a TINY fraction of convergence is coupled
2. The convergence flux is redirected through the throughpole (relay-conserving), not absorbed as heat — the honest open is the leakage fraction η of that redirection
3. ~~The heating rate is: P_heat = f × P_conv × V_disp × (number of nucleons)~~ **[KILLED as transcribed — an absorption formula; the run rejected it as a heat term (f is a pressure ratio, not an energy efficiency). The earned form: P_heat = η × (occluded throughput), with measured ceiling η < 4.4×10⁻¹⁸]**

### Calculation
1. Compute total convergence power intercepted by Earth: (π R_E²) × P_conv × c × f
2. Compare to geothermal heat flow (47 TW)
3. If convergence heating << geothermal: Le Sage heating is undetectable (SDT passes)
4. If convergence heating >> geothermal: SDT has a heating problem

### Success Criteria
- [ ] Convergence heating rate computed for Earth
- [ ] Ratio to geothermal heat quantified
- [ ] Either: heating is negligible → no Le Sage problem; OR: mechanism for recycling identified
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — SAR01
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

*SAR01 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
