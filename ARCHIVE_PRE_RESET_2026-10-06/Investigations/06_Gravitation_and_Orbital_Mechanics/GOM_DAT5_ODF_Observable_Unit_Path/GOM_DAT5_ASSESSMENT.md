# GOM32 Assessment — ODF Observable Unit Path

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom32_odf_unit_path.py`  
**Source SHA-256:** `869D6D42AD02F7861D05073CE1ED4B3B11333002713754FC5B791930CC500F1E`  
**Stdout:** `.audit-tmp/gom32_run.txt`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM32-C1 | **PASS** — Item 4 defines count-interval Doppler observable equation |
| GOM32-C2 | **PASS** — type 12 = Two-way Doppler; Hertz; FORMAT ID 2 on P0 |
| GOM32-C3 | **PASS** — TRK-2-18: `Doppler[Hz] = Observable + Fbias` (documented) |
| GOM32-C4 | **PASS** — K252 `|obs|` medians 10.7–53.1 kHz ∈ [1e3, 1e7] Hz |
| GOM32-C5 | **PASS** — MESSENGER unpack fixture `−382738.66` Hz |
| GOM32-C6 | **PENDING_DATA** — no predicted Doppler / delay residual |

## Classification

**`UNIT_PATH_ENGINEERING_DOPPLER_HZ`.**

Items 4–5 are engineering two-way Doppler observables in hertz (compressed
count-rate form with bias/frequency model terms). They are **not** µHz-class
ODP navigation residuals. The label’s “pseudo-residual” sentence defines a
later analysis product; it does not redefine the stored field.

**Notation caution:** ODF label `K` = transponder turnaround ratio. SDT capital
**K** = c-boundary radius. Do not conflate.

## Implications for SDT solar program

1. GOM30/GOM31 `UNADJUDICATED` unit-path question is **closed** for product class.  
2. A solar-propagation test against this field requires an independent
   **predicted Doppler** (geometry + uplink/turnaround model), or a separate
   delay observable — not a direct comparison of `obs_Hz` to `shapiro_delay`.  
3. Solar **K** remains frozen from GOM26 orbital recovery for any later
   profile test; this loop did not fit **K**.

## Next gate

Pre-register DSS-25 type-12 predicted-Doppler / light-time geometry
(Horizons or volume SPK + station) with solar **K** held fixed — no refit.
