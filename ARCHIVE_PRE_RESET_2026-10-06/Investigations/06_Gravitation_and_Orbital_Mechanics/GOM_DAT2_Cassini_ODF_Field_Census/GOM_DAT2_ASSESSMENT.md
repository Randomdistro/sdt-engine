# GOM29 Assessment — Cassini SCE1 ODF Orbit-Data Field Census

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom29_odf_field_census.py`  
**Source SHA-256:** `9ACDD929BF1A4C7EBA317F1B3E7C2DE9DC407308CE29685C4123B32FFE69C9F5`  
**Stdout:** `.audit-tmp/gom29_run.txt`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM29-C1 | **PASS** — FORMAT ID = 2 on all 7447 rows |
| GOM29-C2 | **PASS** — times 2002-06-06T20:41:30.5 … 22:45:36.5 UTC; monotonic; within label window |
| GOM29-C3 | **PASS** — 7447 × type 12 (two-way Doppler); no range types in this sample |
| GOM29-C4 | **PASS** — RX=TX=DSN 25 for all rows |
| GOM29-C5 | **PENDING_DATA** — no residual computed |

## Classification

**`FIELD_CENSUS_PASS / PENDING_RECONSTRUCTION`.**

This sample is a ~2 h two-way Doppler segment at DSS-25 on 2002-157, not a
full conjunction ranging campaign. It validates label-driven field decode.
It does not adjudicate solar propagation delay.

## Correction retained

First parse over-read past record 7452 into clock-group bytes, producing false
format/time failures. Bound corrected to label pointers (`ODF3C` 7447 rows)
before adjudication.

## Next gate

1. Freeze multi-day SCE1 ODF/TDF coverage spanning solar conjunction.  
2. Pre-register geometry/clock/media reconstruction with held-out impact parameter.  
3. Decode observables to engineering units, then form a residual only after
   independent light-time geometry is frozen — never fit `ϟ`.
