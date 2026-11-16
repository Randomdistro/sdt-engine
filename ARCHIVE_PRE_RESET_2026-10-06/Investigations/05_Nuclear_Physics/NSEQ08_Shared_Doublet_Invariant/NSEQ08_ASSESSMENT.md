# NSEQ08 Assessment — shared doublet-ray invariant

**Date:** 2026-08-09  
**Pre-registration:** `NSEQ08_PRE_REGISTRATION.md`  
**Instrument:** `nseq08_shared_doublets.py`  
**Stdout:** `.audit-tmp/nseq08_run.txt`  
**Canon edited:** no  
**Parents:** NSEQ06-C2 EXCLUDED complementarity; NSEQ07-C4 QQ⊕S provenance

## Status

`SHARED_DOUBLET_QQ_INTERSECT_SURVIVES`

## Gate results

| Gate | Result | Content |
|---|---|---|
| C1/H1 | **PASS** | \|inter\|=4, \|union\|=8, 2 private per branch |
| C2/H2 | **PASS** | \|QQ_triangles ∩ QQ_hexagon\|=4; all 4 shared rays use those QQ edges |
| C3/H3 | **PASS** | Each branch’s 2 private rays use its 2 private QQ edges |
| C4/H4 | **PASS** | Shared rays reuse identical surface edges across branches |

## Corrected relationship

NSEQ06 excluded *empty* complementarity. The positive replacement:

1. The two polar Q−Q selections share **exactly four** edges; those four
   are exactly the Q−Q sides of the four shared doublet rays.
2. Each branch keeps **two private** Q−Q edges → two private doublet rays.
3. On every shared ray the surface partner is the **same** undirected
   T−T (or T−Q) edge under both orientations.

So the orientation fingerprint is not “disjoint doubled sets,” but:

```
shared invariant: 4 QQ edges (= QQ∩) ⊕ 4 fixed surface partners
branch private:   2 QQ edges each
```

Private-ray geometry (diagnostic, not a separate gate): triangles’
private rays are an antipodal pair in the `x–z` plane; hexagon’s are the
`z → −z` images — the two branches partition one four-ray cross into
opposite diagonals.

## What this does *not* claim

Still no emission/transition physics. The invariant is combinatorial /
geometric. A follow-on may ask whether shared vs private chords are the
natural split for a selection rule — without retuning capacities.

## Cascade

| Prior | Update |
|---|---|
| NSEQ06-C2 empty-∩ EXCLUDED | replaced by QQ-intersection invariant |
| NSEQ07 doublet provenance | used; confirmed |
| Capacities | unchanged |
