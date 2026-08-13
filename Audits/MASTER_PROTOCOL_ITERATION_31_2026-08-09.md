# Master Protocol — Iteration 31 (NSEQ02 Triton Shell Orientation)

**Date:** 2026-08-09  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9` (working tree dirty)  
**Canon edits:** none  
**Upstream:** Author — belt orientation is LLM-propagated; shell capacities /
d/t grammar / open–close packing stand

## Result

| Gate | Result |
|---|---|
| Split ledger (capacities kept / belt contested) | PASS |
| Polar dual tetrahedra (8 seats) regular | PASS (`arccos(−1/3)`, equal edges) |
| `r_open > r_close` | PASS |
| Sequencer first belt planar | PASS → **ORIENTATION_STALE** |
| Flat hex-bipyramid as “equator” | ruled out (not regular tetra) |
| Canon / `laws.hpp` edit | none (propose-and-wait) |

**Status:** `BELT_ORIENTATION_STALE`

## Cascade

| Path | Status |
|---|---|
| Shell capacities / magic schedule | retained |
| d/t grammar + open/close packing | retained |
| Sequencer / “belt” orientation | stale — dual-tetra under revision |
| NSEQ01 R5 | amended (capacities frozen; orientation withdrawn) |
| Shadow-union `κ·ΔA` | deferred (do not reuse NSEQ02) |

## Next tests (ranked)

1. Author freeze: dual-tetra seating for all triton shells + nested-radius policy.  
2. Sequencer `packNucleus` orientation rewrite (site + `docs/` mirror).  
3. Propose-and-wait: retire “belt” nomenclature in `laws.hpp` comments / public copy.  
4. Later NSEQ — shadow-union BE with pre-registered κ.
