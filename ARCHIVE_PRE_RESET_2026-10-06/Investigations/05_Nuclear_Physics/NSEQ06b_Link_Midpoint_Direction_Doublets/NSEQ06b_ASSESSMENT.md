# NSEQ06b Assessment — link midpoint direction doublets

**Date:** 2026-08-09  
**Instrument:** `nseq06_midpoint_doublets.py`  
**Stdout:** `.audit-tmp/nseq06_run.txt`  
**Canon edited:** no

## Status

`MIDPOINT_COUNT_SURVIVES__COMPLEMENTARITY_EXCLUDED`

## Results

| Gate | Result | Content |
|---|---|---|
| C1 (both branches) | PASS | E=42, Euclidean midpoints=42, angular dirs=36, doublets=6, singles=30 |
| C2 complementary doublets | **EXCLUDED** | `|inter|=4`, `|union|=8` — not empty intersection / not 12-ray union |

## Corrected relationship

The 14→42 graph **does** force a radial-doublet signature:

- 42 distinct contact midpoints;
- collapse to 36 rays;
- exactly six doubled rays per orientation branch.

But the two polar Q–Q branches do **not** double complementary disjoint ray sets.
They share **four** doublet rays and each owns **two** private ones
(`|union|=8`). Preserve that as an orientation fingerprint for later
emission/transition work — do not advertise empty-complementarity.

## Classification

- C1 counts: DERIVED / COMPUTED from the face graph (NSEQ05).
- Empty-complement hypothesis: EMPIRICALLY EXCLUDED against the graph
  (combinatorial, not lab data — still a failed pre-registered claim).
- Physical meaning of shared vs private doublets: OPEN.
