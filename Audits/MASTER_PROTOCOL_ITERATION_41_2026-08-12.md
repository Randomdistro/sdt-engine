# Master Protocol — Iteration 41 (TT flip-axis)

**Date:** 2026-08-12  
**Canon edits:** none  
**Upstream:** NSEQ12 all-TT; NSEQ11 frame `{x,z}`

## Result

| Gate | Result |
|---|---|
| Exhaustion | PASS |
| Shared → flip y | **EXCLUDE** (flips x/z) |
| Matching → flip x\|z | **EXCLUDE** (flips y) |

**Status:** `TT_FLIP_AXIS_SPLIT_EXCLUDED`

Observed inversion (Shared→frame, Matching→spectator) recorded as diagnostic
only — **not** a rescued pass.

Evidence: `NSEQ13_TT_Partner_Flip_Axis/` · `.audit-tmp/nseq13_run.txt`

## Next (strict)

1. Optional NSEQ14: pre-register the **inverted** flip rule *before* any rerun.  
2. Else leave occupation geometry; move to ε_agg (MM02) or other debt.  
3. No C3 revival; no silent gate flip.
