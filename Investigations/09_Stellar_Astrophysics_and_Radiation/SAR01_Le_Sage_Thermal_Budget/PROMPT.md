# SAR01: Le Sage Thermal Budget — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** §K KILL-DEEPEN RE-RUN (old verdict/runlog/results/cpp DELETED 2026-07-12 per §K.4) · **§K-DEEPENED 2026-07-13**.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §H (Adjudicator) + §K.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on canon flags.
> **This is a KILL-DEEPEN re-run.** The prior artifacts are gone by design so this run is unanchored (§K.4). Re-execute **direct, no auto-agents** (§K.4). The Adjudicator has already ruled once on the SAR01 kill — its trichotomy (buffer / throughpole / terminus) is the spine below.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Does the elastic redirection of convergence flux have ANY thermalisation leakage η, and what recharges the redirected flux's isotropy?** (NOT "how much is absorbed" — absorption was a transcription error; see below.)
2. **Why does it matter?** — Le Sage died because its corpuscles must be *absorbed* (a terminus), which melts everything. SDT's occlusion is *redirection* (a throughpole) — but only if the leakage η is below the geothermal budget. This is the gate between SDT-gravity-is-viable and SDT-has-a-heating-problem.
3. **How will we find out?** — Three routes (§④): A the leakage ceiling η from the 47 TW geothermal budget; B the Maxwell recharge/refill mechanism (what restores isotropy); C the buffer-vs-terminus accounting (§H trichotomy).
4. **What would prove us wrong?** — §⑧: η > 4.4×10⁻¹⁸ exceeds the 47 TW geothermal budget → SDT heating problem. A redirection that is secretly a terminus (no efflux) → Le Sage's death applies to SDT too.
5. **How will we know we're done?** — Dual verdict + the η ceiling on record + the recharge mechanism named (or flagged OPEN as the Law-II release-rate root).

## FARMER CORRECTION (Harvey 2026-07-03) — the premise fix that this re-run enforces

> The premise "matter **absorbs** convergence flux" is a **transcription error** against the founding
> occlusion principle. Influx is a **throughpole** (in/out, never terminates); occlusion is
> **redirection/blocking**, not capture; the work is pressure-asymmetry work, not energy deposition.
> The branch's real question is: **does the elastic redirection have any thermalisation leakage η?**

## §H TRICHOTOMY (the Adjudicator's ruling — the spine of this re-run)

Every flux path must be sorted into exactly one:
- **THROUGHPOLE** — movement passes through (in one side, out the other); nothing stored or destroyed. *Occlusion gravity is this.* PASS. **No heat.**
- **BUFFER** — movement banked *reversibly* and returned (excitation, angular momentum, bond PE). Ledger balanced. Native — violates no conservation. **A buffer is NOT a heat sink.**
- **TERMINUS** — movement destroyed / removed with no efflux. **FORBIDDEN** ("movement has no sink"). *Le Sage's net push requires one; that is why it dies.*

**The single question η measures:** what fraction of the redirected flux leaks from THROUGHPOLE/BUFFER into TERMINUS-like thermalisation (disordered heat with no efflux)? Absorption into a *store* (buffer) is native; absorption into *heat* (terminus) is forbidden. η is the forbidden fraction.

## DATA REQUIREMENTS

| Data | Value | Source |
|------|-------|--------|
| Solar luminosity | 3.828×10²⁶ W | IAU 2015 |
| CMB flux F_CMB | 3.131×10⁻⁶ W/m² | law_II |
| Earth thermal budget | 173 PW solar + **47 TW geothermal** | measured (the ceiling) |
| Prior earned ceiling | **η < 4.4×10⁻¹⁸** | 2026-07-03 run (deleted; re-derive clean) |

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| occlusion = redirection (throughpole) | founding principle / FARMER | **the corrected premise** | ✔ |
| f (transfer/pressure ratio) | `laws.hpp` (EMC01) | **pressure ratio, NOT energy efficiency** | ✔ |
| 47 TW geothermal | measured | the leakage ceiling | ✔ |
| Maxwell elastic-refill / recharge | Law-II release-rate law (STACK §3b) | **the named OPEN** (isotropy restoration) | ⚠ open |
| buffer/throughpole/terminus | HUNTER §H.LEASH | the accounting spine | ✔ |
| P_heat = f·P_conv·V_disp·N | prior draft | **KILLED** (an absorption formula; f is a pressure ratio, not efficiency) | ✖ dead |

## ④ Strategy — three routes

**Route A — The leakage ceiling η (re-derive clean).** Redirected throughput intercepted by Earth vs 47 TW: η_max = 47 TW / (occluded throughput). Re-derive the ceiling (prior: η < 4.4×10⁻¹⁸) **without** reading the deleted result. *Metric:* ceiling reproduced from geothermal budget alone. **Guard:** f is a *pressure ratio*, not an energy efficiency — do not multiply it in as a heat term (that was the killed formula).
**Route B — The recharge mechanism (the Maxwell objection).** What restores the isotropy of the redirected flux? This is the same root as the Law-II release-rate law (relay energy-coupling microphysics). *Metric:* name a native recharge mechanism, or flag it OPEN with its root ID. This is the honest open — do not fabricate a refill.
**Route C — Buffer/terminus accounting.** Trace the redirected flux ledger *in, through, and out* (§H Phase 1). Show it closes as throughpole+buffer with η→terminus bounded. *Kill condition (§H):* if any step requires a terminus (destruction with no efflux) to produce a net push, Le Sage's death applies — SDT gravity would need that same forbidden sink. Show it does NOT (occlusion is a pressure *shadow*, not a captured flux).

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | η ceiling < 4.4×10⁻¹⁸ from 47 TW budget | root-1 if leakage exceeds → SDT heating problem |
| T2 | occlusion push needs NO terminus (throughpole+buffer only) | root-1 (Le Sage death applies) |
| T3 | f used as pressure ratio, never as heat efficiency | root-3 (the killed absorption formula returns) |
| T4 | recharge mechanism named or flagged OPEN (not faked) | root-2 (Law-II release-rate root) |
| T5 | no rival-axiom gate (e.g. "must re-radiate isotropically") smuggled | root-4 (§G contraband) |

## ⑨.E Four-root sort
root-1 claim false (leakage real / terminus required → SDT heating problem) · root-2 dependency (Law-II recharge microphysics) · root-3 prompt (absorption formula, f-as-efficiency) · root-4 contraband (isotropic-re-radiation demand as a rival axiom). §H.LEASH: **name the mechanism of harm** before striking or confirming — buffers are not termini.

## Brainstorm — overlooked factors
- **The buffer/terminus distinction is the whole game.** "Movement has sinks" (buffers exist) and "movement has no sink" (no termini) are BOTH true; the SAR01 kill conflated them. η measures only the terminus fraction.
- **f is a pressure ratio, not an efficiency** — the single most important guard. The killed P_heat = f·P_conv·V_disp·N multiplied a pressure ratio as if it were a heat-coupling efficiency. Do not resurrect it.
- **Recharge = Law-II release rate.** The Maxwell "what refills the isotropy" objection is not unique to SAR01 — it's the relay energy-coupling microphysics that several branches owe. Pay it once at the root (STACK).
- **Sungrazer test (two-regime memory):** occlusion saturation g→2 near contact (+6.8% sungrazer) is a *separate* observable of the same redirection — a possible independent check the thermal budget doesn't touch.

## ⑤ Success / ⑥ Outputs
Class A: η ceiling re-derived clean, occlusion shown terminus-free (throughpole+buffer), recharge named. **Honest floor:** η < 4.4×10⁻¹⁸ on record + recharge flagged OPEN (Law-II root). Outputs: `RUN_LOG.md`, `sar01_lesage_budget.cpp` (re-created clean), `SAR01_VERDICT.md`, `results.txt`, `KILL_READJUDICATION_REGISTER.md` entry.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — SAR01 (§K KILL-DEEPEN re-run)
- Prompt completion target: [A|B|C]
- Physics class hoped: [NATIVE|OPEN]
- CALIBRATED budget: 0
- Routes: A η-ceiling · B recharge(Law-II) · C buffer/terminus ledger
- Re-run UNANCHORED: do NOT read the deleted verdict/results before committing the ceiling
- No auto-agents (§K.4) — direct execution
- Forbidden: absorption formula; f-as-efficiency; fabricated recharge; isotropic-re-radiation as a required axiom
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| leakage > 4.4×10⁻¹⁸ | trace which step thermalises (root-1) | SDT heating problem — report it | hide the exceedance |
| push needs a terminus | Le Sage death applies (root-1) | KILL the push mechanism | pretend a buffer is the sink |
| recharge unknown | flag OPEN, cite Law-II root | ship OPEN honest | fabricate a refill |
| a gate demands isotropic re-radiation | check §G contraband | kill the gate (root-4) | enforce the rival axiom |

**Disallowed:** the killed absorption formula · f-as-heat-efficiency · reading the deleted results pre-commit · fabricated recharge · rival-axiom kill gate.

---

## KILL-READJUDICATION outcome space (§K.5 — record in `KILL_READJUDICATION_REGISTER.md`)
KILL-CONFIRMED (leakage real / terminus required — SDT heating problem, scope named) · ROOT-RELOCATED (recharge microphysics was the gap — returns OPEN with Law-II root flagged) · KILL-OVERTURNED (gate demanded isotropic re-radiation = contraband; occlusion is terminus-free, branch clean).

---

*SAR01 · §K KILL-DEEPEN re-run 2026-07-13 · prior artifacts deleted by design; absorption→redirection premise fixed; buffer/throughpole/terminus is the spine; f is a pressure ratio not an efficiency; recharge = Law-II release-rate root.*
