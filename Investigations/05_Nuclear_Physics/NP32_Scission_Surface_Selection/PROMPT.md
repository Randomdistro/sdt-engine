# NP32 — The Scission Surface: where the mesh parts, and whether the input selects it

> **Ontology correction 2026-08-13:** the nucleus is **flayed, not split**. The core is sealed masonry, not a goo drop. A minimum-cut of a liquid-drop contact graph is the wrong object. Empirical yield regularities in this folder stand; the mechanism claim moves to **NP35**. Neck/bipartition language below is historical SPEC text, not current mechanism.
>
> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (opened 2026-07-23, direct).
> **This is the end-goal linchpin.** The nuclear programme's stated purpose is *each nucleus has
> one way to be ⇒ spallation/fission become controllable*. Every other NP investigation feeds this
> one, and until now it had no prompt.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on canon flags.
> **Discipline:** no fitted surface term, no liquid-drop borrowing, no shell-model magic numbers as
> *inputs* (they may only be **outputs**). No "charge radius". No G/M.

---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Which surface a driven nucleus parts on.** We have the packing
   (interleaved trefoils, α core + n_d deuterons + n_t tritons) and, from NP31, the shared-electron
   bonds that hold it. What is unknown is the **cut**: given an input (energy, impact parameter,
   angular momentum), *which* set of shared-electron bonds severs — and therefore which two
   fragments emerge.
2. **Why does it matter?** — This is the whole point. If the parting surface is fixed by geometry
   and the input, then fission products are **predictable**, and the next step — choosing an input
   to obtain a chosen product — becomes an engineering problem rather than a statistical one. It
   would also explain, natively, the fact the standard picture attributes to shell corrections:
   **fission is asymmetric.**
3. **How will we find out?** — Build the mesh contact graph from the grammar, define the cut cost
   as the shared-electron bonds severed (NP31's threaded pairs), find the **minimum-cost cut**, and
   test the predicted mass split against measured yields. Then vary the input and see whether the
   cut moves the way NP27's central-vs-grazing result says it should.
4. **What would prove us wrong?** — §⑧. If the minimum cut is **symmetric** (A/2 + A/2) while the
   measured split is asymmetric, the cost function is wrong. If reproducing asymmetry needs a
   fitted surface/shell term, the claim is CALIBRATED, not derived.
5. **How will we know we're done?** — Dual verdict. A real PASS = the asymmetric split falls out of
   the cut with **zero fitted terms**, and the input→channel map is stated as a testable prediction.

---

## 1. What is already on file (inputs, not to be re-derived)

- **NP25 (fission geometry invariant):** `ν = 100 − A(Zr partner)` — the neutron count *is* the
  light-fragment identity. Te-134 sits fixed on the N=82 anchor while the light Zr partner walks
  102→101→100→99→98 as ν = 0→4. Zr yields trace P(ν) at **r = 0.973**. Iodine is always the larger
  product. Fission reads as a 5f atom (U) parting into 4d (Zr) + 5p (Te/Sn/Xe) fragments.
- **NP27 (beam-peel kinematics, ²³⁸U+p Bernas):** 1.83c surface, β = 0.875, slowdown
  `v_circ = 1/γ = 0.484`, 309° sweep — **zero-fit, confirmed**. And the channel rule:
  **central impact → fission; grazing impact → spallation.** Peel width σ = 17.5 is NOT derived.
- **NP31 (orbital-reach binding):** which proton pairs a given internal electron threads — this
  supplies the **bond inventory** whose severing is the cut cost.
- **NP30 (interleaved trefoil complete):** the packing geometry itself.

## 2. The claim to test

> **The nucleus parts on the surface that severs the fewest threaded shared-electron bonds, and the
> input selects among the near-degenerate cuts.** Asymmetry is then not a shell correction but a
> geometric fact: the α-core + triton scaffold makes symmetric cuts *expensive*.

The measured target this must hit without fitting:

| observable | measured | source |
|---|---|---|
| ²³⁵U(n,f) heavy peak | A ≈ 134–140 | yields |
| light peak | A ≈ 94–100 | yields |
| symmetric valley depth | ~10²–10³ × suppressed | yields |
| Te-134 / N=82 anchor fixed | NP25 | on file |
| ν = 100 − A(Zr) | r = 0.973 | NP25 |

**Magic numbers (50, 82) may appear only as OUTPUTS.** If N=82 must be inserted to get the anchor,
the investigation has borrowed the shell model and must be labelled so.

---

## ④ Strategy — four gated phases

### P1 — the bond inventory (from NP31)
- Build the mesh contact graph for ²³⁵U/²³⁸U: nodes = protons, edges = threaded shared-electron
  bonds (NP31's `k`-coordination), weights = `αℏc/r` per bond.
- **Gate:** total Σ bonds reproduces the parent binding to the accuracy NP31 achieved. If NP31 is
  not yet paid, **DEFER** and say so — do not fabricate the inventory.

### P2 — the minimum cut
- Compute the minimum-cost bipartition of the graph (fewest/cheapest bonds severed).
- **Pre-committed metric:** the minimum cut yields a **mass split within ±4 in A** of the measured
  heavy/light peaks, with **no fitted term**.
- **Failure trigger:** cut comes out symmetric → the cost function is missing the scaffold
  asymmetry → four-root sort before continuing (do NOT add a surface term to rescue it).

### P3 — the input→channel map (the controllability claim)
- Vary impact parameter / deposited energy / angular momentum; track which cut becomes cheapest.
- **Pre-committed:** reproduce NP27's rule as an *output* — central → fission (deep cut), grazing →
  spallation (surface peel) — and predict how the split shifts with input.
- **This is the decidable, forward-looking piece:** state a *falsifiable* prediction of a product
  shift under a named input change, before any comparison.

### P4 — the asymmetry origin
- Determine whether asymmetry comes from the α-core scaffold, the triton distribution, or the
  boundary contraction (triton-contraction rule). Name which, or declare OPEN.
- **Cross-check:** does the same cut logic put the N=82 anchor where NP25 measured it, *without*
  inserting 82?

---

## ⑧ Falsification tests

| ID | Hypothesis | Predicted | If FAIL → root |
|---|---|---|---|
| T1 | minimum cut is asymmetric | heavy 134–140 / light 94–100, ±4 in A | root-1 (cost function wrong) |
| T2 | asymmetry needs no fitted term | zero CALIBRATED | root-4 if a surface term is added |
| T3 | magic numbers emerge, not inserted | N=82 anchor as an output | root-4 contraband (shell model borrowed) |
| T4 | central/grazing channel rule reproduced | NP27's rule as output | root-2 (NP27 dependency) |
| T5 | ν = 100 − A(Zr) recovered | r ≈ 0.97 | root-1 |
| T6 | a forward product-shift prediction exists | stated before comparison | root-3 (prompt under-specified) |

## ⑨.E Four-root sort
root-1 claim false (cut doesn't select the measured split) · root-2 dependency (NP31 bond
inventory / NP30 packing / NP27 kinematics incomplete) · root-3 prompt under-specified (cut cost
ill-defined) · root-4 contraband (liquid-drop surface term, shell magic inserted, fitted asymmetry).

## Brainstorm — overlooked factors
- **Asymmetry may be the α-core's shadow.** A scaffold built on one α core plus tritons has no
  symmetric bipartition that doesn't cut the core — that alone could make symmetric fission
  expensive, with no shell physics at all. Test this first; it is the cheapest possible explanation.
- **The triton-contraction rule is a live input:** tighter regions resist cutting differently. The
  boundary contraction may bias the cut toward the looser (deuteron-rich) side.
- **NP25's Te-134 anchor being *fixed* while the light partner *walks*** is a strong structural
  hint: one side of the cut is rigid, the other absorbs the variation. That asymmetry of roles
  should fall out of the graph, not be imposed.
- **Do not let ν be fitted.** NP25 already has `ν = 100 − A(Zr)` at r=0.973; NP32 must *reproduce*
  it, not re-tune it.
- **Counts trap (NP24-A):** any rule that is a pure function of (Z,N) is not independent evidence.
  The cut must come from the **graph**, not from the counts.

## ⑤ Success / ⑥ Outputs
Class A: asymmetric split derived from the minimum cut, zero fitted terms, magic numbers as
outputs, and a stated forward prediction for input→product. Class C: split reproduced with ≤1
documented approximation. **Honest floor:** the graph and cut cost defined, split qualitatively
asymmetric, magnitude OPEN. Outputs: `RUN_LOG.md`, `np32_scission_cut.py`, `NP32_DERIVATION.md`,
`NP32_VERDICT.md`.

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — NP32
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|OPEN]
- CALIBRATED budget: 0
- Phases this session: [P1|P2|P3|P4]
- Upstream verify-on-file FIRST: NP31 bond inventory, NP30 packing, NP27 kinematics, NP25 invariant
- Forbidden: inserting magic numbers; liquid-drop surface/Coulomb terms; fitting the asymmetry;
  claiming controllability without a stated forward prediction
```

| Trigger | PIVOT | If pivot fails | Forbidden |
|---|---|---|---|
| NP31 unpaid | **DEFER P1**, cite NP31 | ship the graph definition only | fabricate the bond inventory |
| cut comes out symmetric | test the α-core-cannot-be-cut constraint | OPEN (root-1) | add a surface term |
| N=82 won't emerge | check the triton scaffold | OPEN, name it | insert 82 |
| split needs tuning | four-root sort | OPEN | fit and call it derived |

**Disallowed:** post-hoc tolerance widening · fitted asymmetry · shell magic as input · liquid-drop
borrowing · claiming "controllable fission" without a falsifiable input→product prediction.

---

*NP32 · opened 2026-07-23 direct · the programme's purpose has never had its own prompt; this is it.
The nucleus parts where the mesh is cheapest to cut — derive that surface, and fission becomes a
choice rather than a statistic.*
