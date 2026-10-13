# GOM31 Assessment — Multi-Day CORS_0021 ODF Observable Decode

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom31_odf_multiday_decode.py`  
**Source SHA-256:** `E8696F8608677593F08D8E18F56A99E4562C480EA3DD2C83C8B9360B1FE5F5EC`  
**Stdout:** `.audit-tmp/gom31_run.txt`  
**Volume:** `Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/`  
**Online reference:** https://atmos.nmsu.edu/pdsd/archive/data/co-ss-rss-1-sce1-v10/cors_0021/  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM31-C1 | **PASS** — 8/8 ODF+label pairs present |
| GOM31-C2 | **PASS** — every file `rows == label ROWS`; pointer bounds OK |
| GOM31-C3 | **PASS** — all orbit-data rows finite `obs_Hz`, `f_ref > 0` |
| GOM31-C4 | **PASS** — per-file summaries below |
| GOM31-C5 | **PENDING_DATA** — no residual |

## Per-file summary (COMPUTED)

| Product | Rows | Time (UTC) | obs median (Hz) | f_ref median (Hz) | Types / RX |
|---|---:|---|---:|---:|---|
| 157 K252 | 7447 | 06-06 20:41 – 22:45 | 50244.3 | 2.116649e9 | 12 / DSS-25 |
| 157 XMMMV0 | 84266 | 06-06 05:30 – 06-07 04:59 | 8049.5 | 2.116980e9 | 11/12/13/37 · 25/45/54 |
| 158 K252 | 20748 | 06-07 17:15 – 06-08 02:45 | 20006.3 | 2.116648e9 | 12 / DSS-25 |
| 158 XMMMV0 | 86389 | 06-07 04:59 – 06-08 02:46 | 9622.7 | 2.116985e9 | 11/12/13/37 · 25/45/65 |
| 159 K252 | 17289 | 06-08 17:57 – 06-09 02:41 | 10385.9 | 2.116649e9 | 12 / DSS-25 |
| 159 XMMMV0 | 92798 | 06-08 02:46 – 06-09 03:55 | 292757.1 | 2.117054e9 | 11/12/13/37 · 25/45/65 |
| 160 K252 | 35942 | 06-09 16:51 – 06-10 02:50 | 53099.3 | 2.116658e9 | 12 / DSS-25 |
| 160 XMMMV0 | 106143 | 06-09 03:55 – 06-10 06:59 | 25888.6 | 2.117064e9 | 11/12/13/37 · 25/45/65 |

Total orbit-data rows decoded: **451022**.

## Interpretation limits

1. GOM30 `PENDING_FETCH` for CORS_0021 ODFs is **cleared** — products were
   already local under the `v10` Atmospheres path; the failed helper used
   `v1.0`.
2. K252 files remain single-station type-12 series at tens of kHz (consistent
   with GOM30 P0). XMMMV0 files mix data types 11/12/13/37 and stations, with
   `obs_Hz` spanning ~−3×10⁶ to ~+3×10⁷ Hz — stronger evidence that the field
   is not a microhertz-class published residual series. Unit path stays
   **UNADJUDICATED**.
3. No light-time geometry or SDT residual was formed.

## Classification

**`MULTIDAY_DECODE_PASS / PENDING_RECONSTRUCTION`.**

No SDT empirical adjudication. Multi-day conjunction coverage is now available
for a pre-registered geometry/clock reconstruction gate.

## Next gate

1. Non-conjunction fixture / TRK-2-18 path confirming whether type-12 `obs_Hz`
   is Doppler residual vs engineering count-rate.  
2. Pre-register independent light-time geometry (Horizons/SPK + DSN station)
   before any residual vs `ϟ`. Prefer type-12 DSS-25 subsets first.  
3. Parallel: BF080 NRAO staging; benchmark detox propose-and-wait.
