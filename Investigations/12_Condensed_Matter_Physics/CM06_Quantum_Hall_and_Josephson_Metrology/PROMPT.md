# CM06 — Quantum Hall and Josephson Metrology

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Are the two most precise constants in metrology — `R_K = h/e²`
   (von Klitzing, defines the ohm, E86) and `K_J = 2e/h` (Josephson, defines the volt, E85) — derivable
   as **native lattice-topology integer counts** (the Hall plateau = an integer count `ν` of
   occlusion-channel edge states, the Josephson "2" = the two locked vortices of CM01), with **no
   gauge-field machinery imported**? Concretely: does the per-channel throughput come out *exactly*
   `e²/h`, and is the "2e" forced to be two W=1 vortices rather than assumed?
2. **Why does it matter?** — CM06 is the **metrology-closure node**: it ties CM02's native ohm and
   CM01's `Φ₀ = h/2e` count to the SI's own ohm (E86) and volt (E85). If both fall out as integer
   counts, SDT inherits the SI definitions natively; if either needs gauge/topological-band theory,
   the metrology closure is borrowed. The "2e = two vortices" claim is the *same* "2" CM01 must earn.
3. **How will we find out?** — Four gated phases (§④): edge-channel confinement (P1) and the
   per-channel `e²/h` count (P2) run from EMC03 handedness + occlusion *before* the Josephson 2e is
   quoted; importing a gauge field or a topological-band Chern number as the mechanism caps it at C.
4. **What would prove us wrong?** — §⑧: three falsifiers with numeric triggers and real failure
   modes — the plateau value (T1) and the "2"-is-two-vortices test (T2) can both come out wrong.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with no repainting of a fired test.

## Question

The two most precise constants in metrology come from condensed matter: the **von Klitzing
resistance** `R_K = h/e²` (quantum Hall, defines the ohm — E86) and the **Josephson constant**
`K_J = 2e/h` (defines the volt — E85). Both are *exactly* topological — integers times `h/e`.
**Can `R_K = h/e²` and `K_J = 2e/h` be reproduced from SDT lattice topology and relay-phase coupling
— the Hall plateau as an integer count of occlusion-channel edge states, the Josephson "2e" as the
*two locked vortices* of [[CM01]], with no gauge-field machinery?** If the metrological constants
fall out as native integer counts, SDT inherits the SI's own definitions.

## SDT mechanism & hypotheses

Quantum Hall: in a strong swirl field the drifting vortices are confined to **edge relay channels**;
conduction is an integer count `ν` of those channels, each carrying `e²/h` of throughput → exact
plateaus, immune to disorder (topological = a count cannot vary continuously). Josephson: two
phase-locked condensates (CM01) coupled across a weak link relay a current set by their phase
difference; the voltage–frequency ratio is `2e/h` because the carrier is the **locked pair**.

- **H1 (Hall plateau = channel count):** `σ_xy = ν e²/h`, `ν` an integer edge-channel count; `R_K =
  h/e²` is the one-channel native resistance (closes against CM02's native ohm).
- **H2 (Josephson 2e = the pair):** `K_J = 2e/h`; the "2" is two locked vortices (CM01 H3), so
  `V = (h/2e) f` is a native phase-count relation, not a gauge result.
- **H3 (metrological exactness):** both are integer/topological, so robust to lattice disorder —
  plateaus are flat to the relay-quantisation floor.

## Strategy

**Phase 1 — Edge channels.** *Goal:* confined edge relay states in a swirl field. *Method:* EMC03
handedness + occlusion confinement of drifting vortices to boundaries. *Success:* discrete edge
channels exist; count `ν` integer.

**Phase 2 — Hall plateau.** *Goal:* `σ_xy = ν e²/h`. *Method:* throughput per channel = `e²/h`.
*Success:* `R_K = h/e²` to <0.1%; plateaus flat vs disorder.

**Phase 3 — Josephson.** *Goal:* `K_J = 2e/h`. *Method:* phase-difference current across a weak link
between two CM01 condensates. *Success:* `V = (h/2e) f`; the "2" demonstrably two vortices.

**Phase 4 — Metrology closure.** *Goal:* ohm (E86) + volt (E85) native. *Method:* cross-check
`R_K`, `K_J` vs SI. *Success:* both within the relay-quantisation floor; consistent with CM02 ohm.

## Success criteria

- ✅ **PASS (A):** `R_K = h/e²` and `K_J = 2e/h` both native integer counts, zero fits.
- ✅ **QUALIFIED (C):** both forms derived; one O(1) channel/geometry factor CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** edge-channel picture shown; only one of R_K / K_J quantitatively closed.
- ❌ **FAIL (F):** plateaus or 2e cannot be obtained without importing gauge/topological-band theory.

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction (numeric) | What KILLS it |
|---|------|--------------------------|---------------|
| T1 | Hall plateau = integer channel count | `σ_xy = ν·e²/h` with integer ν; one-channel `R_K = h/e² = 25812.807 Ω` to <0.1%; plateaus at integer ν only | if the per-channel throughput is not `e²/h` (off >0.1%), or plateaus land at non-integer ν, or `R_K` is only reproduced by *importing* a Chern number → Hall is not native edge-channel topological; thesis dead |
| T2 | Josephson "2" = two locked vortices | `K_J = 2e/h = 4.8359×10¹⁴ Hz/V` to <0.1%; the divisor "2" is demonstrably **two W=1 vortices** (CM01 H3), not assumed | if the native phase-count gives `e/h` (a 1, not a 2), or the "2" only appears by *importing* the BCS `2e` → the 2 is not two vortices (→ C, not A) |
| T3 | Exactness = topological robustness | plateau flatness within the relay-quantisation floor as defect density varies over ≥2 orders | if the SDT plateau drifts continuously with disorder (quantisation is not a robust integer count) → exactness is not topological |

## Dependencies

**Upstream:** CM01 (locked pairs → the Josephson 2e), CM02 (native ohm), EMC03 (handedness /
edge confinement), Law VI (topology / winding count). **Downstream:** metrological closure of the SI
ohm and volt within SDT. **Related:** E85 (Josephson volt), E86 (quantum-Hall ohm); the
relay-quantisation floor as the precision limit.

## Implementation notes

Double precision; `R_K`, `K_J` to full CODATA precision; ν and the Josephson divisor as exact integers.
`e` here is the unit-bridge constant, not a charge substance — never write "charge radius"; EM is handed
redirection. The "swirl field" the Hall edge confines is EMC03 handedness, expressed natively, not a
borrowed gauge potential. No gauge fields, no topological-band Chern machinery as mechanism (reproducing
them as targets is fine). Author attribution in all generated files: **J. C. Harvey, Melbourne.**

## Questions This Opens *(generative — log new ones in `CM06_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing it well.

1. **Is the relay-quantisation floor a real precision ceiling?** If plateaus are flat only to a finite
   ℓ_P-scale floor, does SDT predict a fundamental limit on `R_K`/`K_J` reproducibility — below or
   above today's metrological uncertainty?
2. **Are the fractional quantum-Hall states sub-channel vortex fractions?** If ν is normally an integer
   edge-channel count, what native object gives ν = 1/3, 2/5...? Is it a fractional wake circulation,
   and does SDT predict which fractions are stable?
3. **Does "2e = two vortices" survive away from superconductivity?** The same "2" appears in `Φ₀` (CM01)
   and `K_J` (here). Is there any metrological context where a *single*-vortex `e/h` Josephson-like
   relation should appear, and has it been seen?
4. **Can the ohm and volt be closed without ever measuring e separately?** If both constants are integer
   counts of `h/e` combinations, does SDT let the SI ohm and volt be fixed by topology + ℏ alone — and
   does that match the 2019 SI redefinition's logic?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CM06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the R_K / K_J chains (one O(1) channel/geometry factor may be CALIBRATED(1) — list it)
- Engine namespaces actually used: law_VI (topology/winding), law_III (occlusion confinement), EMC03 (handedness), CM01 lock, CM02 ohm
- Phase thresholds (committed before run):
    P1 integer ν edge channels exist · P2 |R_K − h/e²|/R_K < 0.1%, plateaus at integer ν, flat vs disorder
    P3 |K_J − 2e/h|/K_J < 0.1%, divisor = 2 = two vortices · P4 R_K consistent with CM02 ohm
- Forbidden retroactive changes: import a gauge field / Chern number as mechanism then claim A; import the
    BCS 2e as the Josephson "2"; widen tolerances; plug R_K/K_J; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P2 per-channel throughput ≠ e²/h | re-derive the edge-channel confinement from EMC03 + occlusion | **OPEN**: report the actual per-channel value | import a Chern number to force e²/h and grade A |
| P2 plateaus at non-integer ν | recheck the integer-count argument (a count cannot vary continuously) | **OPEN**: report the non-integer behaviour | hand-round ν to integers |
| P3 Josephson divisor ≠ 2 (gives e/h) | re-examine the two-locked-vortex carrier (CM01 H3) | **OPEN**: report the divisor; do NOT import BCS 2e | retro-fit to 2e/h |
| P3 "2" only via imported BCS 2e | down-grade to **C** honestly (the import is the postulate) | — | claim NATIVE while importing 2e |
| Rivals (gauge/TKNN) match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |
| Upstream dependency missing (CM01/CM02 not run) | **DEFER** the affected phase; cite dependency ID | — | fake the plateau |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** edge-confinement routes (EMC03 handedness vs occlusion-boundary), both native.

### Disallowed adjustments

- Importing a gauge field / topological-band Chern number as mechanism and grading A · importing the
  BCS 2e as the Josephson "2" · post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in any
  native chain · "charge substance" language for `e`.

---

*CM06 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
