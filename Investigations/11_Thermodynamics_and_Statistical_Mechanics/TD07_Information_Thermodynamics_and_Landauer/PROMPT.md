# TD07 — Information Thermodynamics and Landauer

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Does the Landauer bound `k_BT ln2` per erased bit follow *literally* from
   TD01's `S=k_B ln W` (erasing forces `W:2→1`, dumping `k_B ln2` of configurational entropy as heat
   because relay conserves throughput), and does the same throughput-conservation **close Maxwell's
   demon** — the demon's relay register must be reset, paying back exactly what it extracts — so SDT has
   no Second-Law loophole? (Honest note: the `k_BT ln2` step is near-definitional given TD01+TD02; the
   load-bearing, falsifiable content is the demon closure.)
2. **Why does it matter?** — This is where "information is physical" becomes a relay statement and where
   TD01's arrow-of-time / H4 demon note is discharged. If a relay demon could extract net work, the
   whole throughput-conservation ontology fails.
3. **How will we find out?** — Gated phases in §④; the bit-erasure ledger and the demon+reset accounting
   on the TD01 toy lattice.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers and real failure modes.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## Question

Landauer's principle says erasing one bit dissipates at least `k_BT ln2` of heat, and Maxwell's demon
must obey it. The gap: derive the Landauer bound and close the demon **on the relay lattice** — show
that information is physical because a bit *is* a relay configuration, and erasing it dumps organised
throughput as disordered heat.

## SDT mechanism & hypotheses

A bit is a distinguishable two-state relay configuration — a small set of microstates `W=2`. Erasing
it forces both logical states into one (`W:2→1`), which by [[TD01]]'s `S=k_B ln W` *destroys*
`k_B ln2` of configurational entropy; that throughput cannot vanish (relay conserves throughput) so it
is expelled as disordered heat into the bath at `T`, costing `k_BT ln2`. The demon is not a loophole:
sorting requires measuring (writing a relay record) and resetting that record is itself an erasure.

- **H1 (Landauer = forced microstate merge):** irreversible logic merges relay microstates; the
  minimum heat is `k_BT ln2` per bit erased — derived from TD01 counting + TD02's `k_BT`.
- **H2 (demon pays relay):** the demon's memory is a physical relay register; to sort indefinitely it
  must reset, paying `k_BT ln2` per cleared record — exactly offsetting the work it extracts. No net
  Second-Law violation (closes [[TD01]] H4).
- **H3 (reversible computation is free):** a logically reversible relay operation maps microstates
  one-to-one (`W` unchanged), so `ΔS=0` and it can in principle cost no heat — recovering Bennett.

## Strategy

1. **Bit erasure ledger.** *Goal:* `k_BT ln2` per bit. *Method:* on the TD01 toy lattice prepare a
   `W=2` register, force `W→1`, measure heat dumped to a relay bath. *Success:* dissipated heat
   `= k_BT ln2 ± 1%`; reversible (one-to-one) ops dump `≈0`.
2. **Maxwell's demon.** *Goal:* close the loophole. *Method:* simulate a demon sorting a relay gas
   into hot/cold halves while logging to a finite register; account for the reset cost. *Success:*
   `W_extracted − W_erase_cost ≤ 0`; the apparent gain vanishes exactly when the register reset is paid.
2b. **Szilard engine.** *Goal:* one-molecule cross-check. *Method:* run the Szilard cycle on the
   lattice. *Success:* `k_BT ln2` extracted per cycle equals the measurement+erase cost.
3. **Reversibility boundary.** *Goal:* map cost vs logical reversibility. *Method:* sweep a family of
   gates from fully irreversible to reversible. *Success:* heat cost `∝ ΔS = k_B Δ(ln W)`; zero at the
   reversible end (Bennett recovered).
4. **Audit.** *Goal:* confirm derivation basis. *Method:* delete-test `k_B`. *Success:* every bound is
   `k_BT ×` pure number (`ln2`, etc.); no ensemble imported.

## Success criteria

- **PASS (Class A):** `k_BT ln2`/bit derived from TD01 counting, demon closed, reversible-compute free
  — only `k_B` dependency-traced, zero fitted parameters.
- **QUALIFIED (Class C):** Landauer + demon native; reversible-limit cost within numerical noise.
  *(Expected.)*
- **PENDING (Class D):** erasure cost right but demon closure stays qualitative.
- **FAIL (Class F):** a relay demon extracts net work — a real Second-Law loophole exists.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | erase = microstate merge | heat `=k_BT ln2`/bit ±1% | information not physical on lattice |
| T2 | demon pays reset | net extracted work ≤ 0 | a real perpetual-motion loophole exists |
| T3 | reversible logic free | `ΔS=0` ops dump `≈0` heat | reversibility gives no thermodynamic relief |

## Dependencies

**Upstream:** [[TD01]] (`S=k_B ln W`, arrow-of-time, H4 demon note), [[TD02]] (`k_BT` scale).
**Downstream:** computation-energetics / reversible-logic studies, quantum-info correspondence (the
"no wavefunction" route to information). **Related:** [[TD06]] (radiation bath that carries away the
erased heat), [[project_foundational_ontology_influx_monopole]] (throughput conservation forbids the
demon's free lunch — the same eliminative move).
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — TD07
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (every bound is k_BT × a pure number — ln2, etc.)
- Engine namespaces actually used: measured::k_B, TD01 (S=k_B ln W counting), TD02 (k_BT scale)
- Phase thresholds (committed before run):
    P1 erase heat = k_BT ln2 ±1%; reversible ops dump ≈0 · P2 demon net (extract − reset) ≤ 0
    P2b Szilard k_BT ln2/cycle = measure+erase cost · P3 cost ∝ k_B Δ(ln W), →0 at reversible end
- Forbidden retroactive changes: import a quantum-info ensemble as mechanism; widen tolerances;
    plug ln2; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 erase heat off `k_BT ln2` by `> 1%` | check the `W:2→1` merge bookkeeping against TD01 counting | **OPEN** the Landauer ledger | plug `ln2` |
| P2 demon nets `> 0` work after reset | account for the *register reset* cost explicitly (the loophole) | **F** — a real perpetual-motion loophole exists; report it, do not bury | hide the register-reset cost |
| P3 reversible-end cost not `→ 0` | check the gate is genuinely one-to-one (`W` unchanged) | **OPEN** the Bennett limit | call a lossy gate reversible |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (TD01/TD02 toy lattice not ready) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (register size, gate family, cycle count); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Importing a quantum-information ensemble or wavefunction as the erasure mechanism · burying a demon
  that nets positive work · post-hoc tolerance widening · plugging `ln2` · `atomic::`/GM/G in the chain.

---

## Questions This Opens *(generative — log new ones in `TD07_VERDICT.md`)*

1. **Is throughput-conservation the *same* eliminative move as "no monopole / no free lunch"?** The demon
   fails because relay throughput cannot be created — is that literally the influx-throughpole principle
   ([[project_foundational_ontology_influx_monopole]]) applied to information?
2. **Does a relay bit have a minimum *physical* size (`~ℓ_P`) and so a minimum erase time/power?** If a
   bit is a relay configuration, is there a native ultimate limit beyond `k_BT ln2` set by the tick?
3. **Does reversible relay computation tie to the lossless light-propagation regime (FLM09)?** A
   one-to-one bond-switch wave dumps no heat — is reversible logic the information face of transparent
   relay propagation?

---

*TD07 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
