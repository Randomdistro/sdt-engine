# CH05 — Reaction Energetics & Activation from Wake Reconfiguration

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether reaction enthalpy ΔH can be derived as the difference in total wake-cost between reactant and product electropause configurations, and the activation barrier Eₐ as the highest wake-cost point (a wake *saddle*) along the reconfiguration path, with catalysis simply a lower-wake route — NO transition-state wavefunctions, NO orbital correlation diagrams.
2. **Why does it matter?** — The transition state becomes a geometric saddle of the wake field, not a quantum resonance. It consumes CH01 bond well-depths and CH04 geometries, feeds the downstream chemical-kinetics investigations, and ties to TD05 free-energy accounting. If it holds, reaction barriers stop being quantum resonances and become locatable points in a classical wake field.
3. **How will we find out?** — Gated phases in §④: ΔH bond-energy bookkeeping, then Eₐ as a 1-D wake-cost saddle, then catalysis as improved cancellation along the path, then a novel Eₐ/BEP-slope call — the native mechanism is built before any orbital correlation diagram or `atomic::`/rival is invoked.
4. **What would prove us wrong?** — §⑧ numeric triggers: ΔH signs or magnitudes wrong across the reaction set, or barriers that cannot be located without an orbital correlation diagram (a quantum TS).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

ΔH bookkeeping from summed CH01 well-depths is a near-IDENTITY — it IS the standard bond-energy
sum re-narrated as electropause-merge accounting. So **ΔH alone earns at most CONVERGENCE.** The
LOAD-BEARING, gradeable content is (a) locating Eₐ as a genuine wake *saddle* that emerges from the
path geometry — not read off a measured Eₐ — and (b) the catalysis "same ΔH, lower Eₐ" signature
falling out natively.

> **Reproducing ΔH by summing tabulated bond energies is the textbook identity — it does not by
> itself earn NATIVE; the barrier-as-saddle and catalysis predictions are where the model is
> tested. Reading the barrier height off the measured Eₐ caps the grade at C.**

One wake-cost scale may be **CALIBRATED(1)** — declare it explicitly. The Eₐ ORDERING / BEP slope
must be **predicted**, not fit per reaction.

## Question

A chemical reaction breaks some shared electropauses and forms others, rerouting the wake field
along the way. **Can reaction enthalpy ΔH be derived as the difference in total wake-cost between
reactant and product electropause configurations, and the activation barrier Eₐ as the highest
wake-cost point along the reconfiguration path (a wake *saddle*), with catalysis being simply a
lower-wake route — no transition-state wavefunctions, no orbital correlation diagrams?** The
transition state is the geometric saddle of the wake field, not a quantum resonance.

## SDT mechanism & hypotheses

Each shared electropause (CH01) carries a well depth (bond energy) and each active wake carries a
cost. A reaction is a continuous deformation from the reactant wake configuration to the product
one. ΔH is the net change in summed well depths (the familiar "bonds broken − bonds formed"), now
read as electropause-merge bookkeeping. Along the deformation path the wakes must transiently
*overlap and mis-cancel* before re-pairing; the peak of that mis-cancellation cost is the barrier,
and its location is the transition state. A catalyst supplies an alternative electropause partner
that keeps wakes better cancelled throughout, lowering the saddle.

- **H1 (ΔH = Σ well-depth change):** ΔH = (Σ reactant electropause depths) − (Σ product depths);
  recover signs and magnitudes for a set of gas-phase reactions from CH01 bond energies.
- **H2 (Eₐ = wake saddle):** the barrier height tracks the maximum transient un-cancelled wake
  along the minimum-cost path; predicts Eₐ ordering across a homologous series.
- **H3 (catalysis = lower-wake path):** an added partner that keeps wakes cancelled lowers the
  saddle without changing ΔH; reproduces the catalyst's "same ΔH, lower Eₐ" signature.

## Strategy

**Phase 1 — ΔH bookkeeping.** *Goal:* enthalpies from bond-energy sums. *Method:* CH01 well depths
in/out. *Success:* ΔH sign correct for ≥12 reactions, magnitude within ~15% (combustion,
hydrogenation, HX formation).

**Phase 2 — Barrier as saddle.** *Goal:* Eₐ trend. *Method:* 1-D wake-cost profile along a bond
coordinate; locate the maximum. *Success:* correct Eₐ ordering across a homologous series; a
Hammond-postulate-style late/early TS correlation emerges natively.

**Phase 3 — Catalysis.** *Goal:* lower barrier, same ΔH. *Method:* add a partner wake that
improves cancellation along the path. *Success:* Eₐ drops, ΔH unchanged, for one model reaction.

**Phase 4 — Falsifier.** *Goal:* a novel call. *Method:* predict an un-fit Eₐ or a BEP-line slope
(ΔEₐ vs ΔH) and check against measured kinetics.

## Success criteria

- **PASS (A):** ΔH set + Eₐ ordering + catalysis signature + a correct novel Eₐ/BEP slope, no
  TS wavefunction.
- **QUALIFIED (C):** ΔH from bond sums + qualitative barrier-as-saddle; one wake-cost scale
  CALIBRATED(1). *(Expected landing.)*
- **PENDING (D):** ΔH bookkeeping works; barrier only schematic.
- **FAIL (F):** barriers cannot be located without an orbital correlation diagram.

## Falsification tests

| Test | Predicted outcome | If FAIL (explicit trigger) |
|------|-------------------|---------|
| ΔH = Σ well-depth change | signs + ~15% magnitudes across reactions | ΔH sign wrong for >2 of 12 reactions, or >15% magnitude after pivot ⇒ enthalpy isn't electropause bookkeeping |
| Eₐ = wake saddle | correct barrier ordering + Hammond shift | barrier ordering wrong / no saddle emerges from path geometry ⇒ barrier needs a quantum TS |
| Catalysis = lower-wake path | Eₐ down, ΔH fixed | catalyst changes ΔH or fails to lower Eₐ ⇒ catalysis has another basis |
| **Firewall:** ΔH identity vs load-bearing barrier | ΔH = bond-sum is CONVERGENCE only; the gradeable claim is the natively-located saddle + catalysis signature | ΔH reproduced but no saddle emerges, or Eₐ height read off measured Eₐ ⇒ only the textbook identity was re-narrated; grade caps at C, not NATIVE |

## Dependencies

**Upstream:** CH01 (electropause well depths), CH04 (the geometries that deform). **Downstream:**
chemical kinetics / rate investigations. **Related:** TD05 (thermodynamic free-energy / entropy
accounting), EMC03 (mis-cancellation surplus is the barrier).
---

## Questions This Opens *(generative — log new ones in `CH05_VERDICT.md`)*

1. Is the **Hammond postulate** (early vs late TS) a GEOMETRIC consequence of *where* the wake
   saddle sits along the reconfiguration path — early saddle for exothermic, late for endothermic?
2. Does the **BEP slope** (ΔEₐ vs ΔH) come out as a fixed fraction — a native constant of the
   wake-cost geometry rather than a fitted per-family parameter?
3. Is **catalytic lowering** quantifiable as exactly the cancellation improvement the added partner
   provides along the path (ties EMC03 mis-cancellation surplus)?
4. Does the wake-saddle picture predict the **kinetic isotope effect** without tunnelling
   wavefunctions — purely from the mass-loading of the reconfiguration coordinate?
5. Does it recover the **Arrhenius / Eyring prefactor** from the wake-reconfiguration attempt
   frequency (ties CH07 molecular vibration)?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 ΔH sign correct for >=12 reactions, magnitude within 15% · P2 correct Eₐ ORDERING across a homologous series + Hammond early/late TS correlation native · P3 catalysis: Eₐ drops, ΔH unchanged for one model reaction · P4 novel Eₐ or BEP-line slope within committed tol
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| Saddle won't appear from path geometry | re-parametrise the reconfiguration coordinate; check mis-cancellation cost (EMC03) | **OPEN** barrier-as-saddle | read Eₐ off measurement, call it predicted |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · claiming NATIVE on ΔH bond-sum alone (it is the identity) · reading the barrier height off the measured Eₐ · per-reaction refitting of the wake-cost scale.

---

*CH05 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
