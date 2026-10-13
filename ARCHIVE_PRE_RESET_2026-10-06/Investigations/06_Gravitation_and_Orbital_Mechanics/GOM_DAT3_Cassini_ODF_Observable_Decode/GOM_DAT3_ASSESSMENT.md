# GOM30 Assessment — ODF Doppler Observable Decode

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom30_odf_observable_decode.py`  
**Source SHA-256:** `9661FCFD33A6742C58C99A269B2A28A6632F342BF459730F1847BF88B6CB3AF5`  
**Stdout:** `.audit-tmp/gom30_run.txt`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM30-C1 | **PASS** — 7447 finite `obs_Hz` values |
| GOM30-C2 | **PASS** — `f_ref > 0` on all rows; constant `2.116648992×10⁹ Hz` |
| GOM30-C3 | **PASS** — series reported; validity=0 (good) on all rows |
| GOM30-C4 | **PASS** (list); 7/8 were **PENDING_FETCH** at I10 — cleared to HAVE in GOM31 |
| GOM30-C5 | **PENDING_DATA** — no residual |

## Decoded series (P0 file, COMPUTED)

| Quantity | Value |
|---|---|
| Rows | 7447 type-12 two-way Doppler |
| Time | 2002-06-06 20:41:30.5 – 22:45:36.5 UTC |
| `obs_Hz` min / median / max / stdev | 34982.452 / 50244.322 / 65600.179 / 8894.609 |
| `f_ref_Hz` | 2116648992.000 (constant) |
| Band IDs (spot check) | downlink=3 (Ka), uplink=3 (Ka), exciter=1 (S) |
| Stations | RX=TX=25 |

## Interpretation limits

1. Whether Item 4/5 is raw Doppler or a navigation pseudo-residual remains
   **UNADJUDICATED** (label describes both). The ~35–66 kHz magnitude is
   inconsistent with the microhertz-class fractional-frequency residuals in
   published Cassini conjunction papers — treat as an engineering count-rate
   field until a fixture confirms the unit path.
2. `f_ref` sits on an S-band scale while downlink/uplink IDs are Ka. Possible
   that Items 18–19 store the S-band exciter reference. Do not use this number
   as a Ka carrier without an independent check.
3. Multi-day retrieval: the I10 helper used `…/sce1-v1.0/…` (404). The
   authoritative Atmospheres path is `…/co-ss-rss-1-sce1-v10/cors_0021/`.
   All eight products were already local; GOM31 clears PENDING_FETCH.

## Classification

**`OBSERVABLE_DECODE_PASS`** (I10). Multi-day status superseded by GOM31
`MULTIDAY_DECODE_PASS`. Residual path remains **PENDING_RECONSTRUCTION**.

## Next gate

1. Validate observable→Hz against a published non-conjunction engineering
   fixture.  
2. Pre-register independent light-time geometry before any residual vs `ϟ`.  
3. See GOM31 for multi-day coverage.
