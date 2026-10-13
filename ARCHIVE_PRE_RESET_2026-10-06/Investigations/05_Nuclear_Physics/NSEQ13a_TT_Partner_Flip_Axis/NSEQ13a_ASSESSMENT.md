# NSEQ13a Assessment — TT partner flip-axis split

**Date:** 2026-08-12  
**Pre-registration:** `NSEQ13_PRE_REGISTRATION.md` (gates frozen)  
**Instrument:** `nseq13_tt_flip_axis.py`  
**Stdout:** `.audit-tmp/nseq13_run.txt`  
**Canon edited:** no

## Status

`TT_FLIP_AXIS_SPLIT_EXCLUDED`

## Gate results

| Gate | Result | Content |
|---|---|---|
| C1 | **PASS** | 6 QQ doublets/branch; 4+2 |
| C2 | **EXCLUDE** | Shared flip-axes = `{z,z,x,x}` — **not** spectator `y` |
| C3 | **EXCLUDE** | Matching flip-axes = `{y,y}` — **not** frame `{x,z}` |
| C4 | **PASS** | No C3 |

## Committed vs observed

| Class | Pre-reg | Observed (both branches) |
|---|---|---|
| Shared | flip `y` | flip `x` or `z` |
| Matching | flip `x` or `z` | flip `y` |

The committed spectator/frame assignment is **wrong**. The data show the
**inverted** assignment. That inversion is **not** accepted as a pass of this
pre-reg (would be post-hoc rescue).

## Strict follow-up (only if re-pre-registered)

A **new** investigation may commit a priori:

- Shared → TT flips axis in NSEQ11 frame `{x,z}`  
- Matching → TT flips spectator `y`  

and run blind. Until that file exists with timestamps/commit before stdout,
the inverted pattern is **diagnostic only**.

## Cascade

| Item | Status |
|---|---|
| NSEQ11 seating | unchanged |
| NSEQ12 TT-vs-TQ | EXCLUDED (stands) |
| NSEQ13a committed flip split | **EXCLUDED** |
| Inverted flip split | NOT PASSED (needs new pre-reg) |
