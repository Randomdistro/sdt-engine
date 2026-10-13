# NSEQ01 Assessment — Sequencer rules freeze

**Date:** 2026-08-09  
**Source of record:** `Release/HTML_SDT_Website/nuclear-packing-sequencer.html`  
**Instrument:** `nseq01_rules_freeze.py`  
**Stdout:** `.audit-tmp/nseq01_run.txt`  
**Canon edited:** no

## 1. Framing correction (author)

IAEA / literature **charge radius** is a **QED measurement formulation**. Equating
it with the sequencer’s **physical / displacement boundary** was the wrong
comparison object. In the sequencer, neutrons stabilise by **enmeshment**
(internal e⁻ seats, p↔n mesh); the mass defect is **shared shadow occlusion**,
not a charge-radius conversion from `R_boundary`.

NP12c–e remain on file as formal underdetermination of any
`R_boundary → k·R_RMS` map; they are **not** the native nuclear construction
test. Relative to the sequencer: **WRONG_OBSERVABLE**.

## 2. Frozen rules (R1–R8)

| ID | Rule | Status |
|---|---|---|
| R1 | α-grammar `n_t=A−2Z`, `n_d=3Z−A−2` | frozen |
| R2 | `R_p=0.8414 fm`, `A₁=π R_p²` | frozen |
| R3 | α contact-rotation tetrahedron; ring ≡ `R_p`; p↔n | frozen |
| R4 | deuteron tiers 6,12,12,20,30…; n-in / p-out | frozen |
| R5 | **pure shells** D/T alternating (NSEQ05); T₈ stella, D₁₂ cuboct, T₁₄ face-normals; `r_open>r_close` | seating + pack order rewritten; capacities frozen |
| R6 | explicit bipartite `contacts` | frozen |
| R7 | `ΔA=ΣA_i−A_∪`; `E≈κ·ΔA` (κ policy separate) | frozen |
| R8 | enmeshment = defect | frozen |

## 3. Claim ledger

| ID | Status |
|---|---|
| NSEQ01-C1 | **PASS** |
| NSEQ01-C2 | **PASS** — 217/217 grammar identities |
| NSEQ01-C3 | **PASS** |
| NSEQ01-C4 | **PASS** — He/C/O/Fe/U nucleon & proton counts |
| NSEQ01-C5 | **PASS** — NP12 RMS path `WRONG_OBSERVABLE` |
| NSEQ01-C6 | **PASS** |

## 4. Headline

**`SEQUENCER_RULES_FROZEN`**

## 5. Amendment (2026-08-09)

Author correction: R5 “belt” wording was orientation pollution. Capacities /
grammar / open–close packing stand. Orientation track moved to **NSEQ02**
(`BELT_ORIENTATION_STALE`).

## 6. Next

1. Dual-tetra seating freeze + sequencer rewrite (after NSEQ02).  
2. Shadow-union BE (`κ·ΔA`) as a **later** NSEQ id (NSEQ02 already used for
   orientation).
