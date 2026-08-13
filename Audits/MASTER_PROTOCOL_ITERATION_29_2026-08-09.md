# Master Protocol — Iteration 29 (NP12e Point-Proton RMS Freeze)

**Date:** 2026-08-09  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9` (working tree dirty)  
**Canon edits:** none  
**Upstream:** Iteration 28 O2 branch

## Result

| Gate | Result |
|---|---|
| Frozen set parse (`n_p=Z`) | PASS — He/Be/C/O |
| ⁷Li | WITHDRAWN `TABLE_INCOMPLETE` |
| Point-proton `R_{p,RMS}` | COMPUTED (stated tables) |
| Tammes-4 pair-RMS | value-degenerate |
| Asymmetric subset span | PASS (underdetermined without labels) |
| Physical charge RMS | UNDERDETERMINED |
| IAEA | sealed |

**Status:** `POINT_PROTON_RMS_FROZEN_SET / PHYSICAL_CHARGE_RMS_UNDERDETERMINED`

## Cascade

| Path | Status |
|---|---|
| Boundary-only RMS map | UNDERDETERMINED (I28) |
| Point-proton RMS (stated ATOMICUS) | COMPUTED for 4 nuclides |
| Continuous `ρ_q` | ABSENT |
| Phase B IAEA | sealed |

## Next tests (ranked)

1. Derive proton centres from packing+grammar with proton labels (DERIVED tables).  
2. Intra-proton / `ρ_q` form factor.  
3. Phase B only after DERIVED centres or `ρ_q` freeze.
