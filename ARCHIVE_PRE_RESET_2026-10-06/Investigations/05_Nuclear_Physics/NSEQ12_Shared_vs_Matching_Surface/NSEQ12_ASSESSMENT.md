# NSEQ12 Assessment — Shared vs matching surface partners

**Date:** 2026-08-11  
**Pre-registration:** `NSEQ12_PRE_REGISTRATION.md` (gates frozen)  
**Instrument:** `nseq12_shared_matching_surface.py`  
**Stdout:** `.audit-tmp/nseq12_run.txt`  
**Canon edited:** no

## Status

`SHARED_VS_MATCHING_SURFACE_EXCLUDED`

## Gate results

| Gate | Result | Content |
|---|---|---|
| C1 | **PASS** | 6 QQ doublets/branch; 4 Shared + 2 matching |
| C2 | **PASS** | Shared partners all **TT** (both branches) |
| C3 | **EXCLUDE** | Matching partners are **TT**, not TQ (`['TT','TT']` both branches) |
| C4 | **PASS** | No C3 in builders |

## What this excludes

The committed claim that Shared and matching QQ contacts are distinguished by
surface-partner **species** (TT vs TQ) is **false**. Under the radial-doublet
map, **all six** QQ edges on each polar branch pair with a T−T surface edge.

## What this does not rescue

No amendment to “all TT SURVIVES” as a substitute headline. That was not the
pre-registered discriminator. A same-species result may inform a *new*
pre-reg (e.g. finer TT geometry), only after fresh commitments.

## Cascade

| Prior | Update |
|---|---|
| NSEQ11 Shared ∪ matching rule | Unchanged (seating rule stands) |
| Surface-species occupation split | **EXCLUDED** |
| Emission / energy along Shared vs matching | Still OPEN; this geometric fork closed negative |
