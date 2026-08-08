# GOM25 D4 — Cassini ATDF Readiness Probe

**Date:** 2026-08-07  
**Instrument SHA-256:** `520cdd96a3a57ce103800cba0932223534ce016d658a24af14c40dbf9c0044cd`  
**Stdout:** `.audit-tmp/gom25_cassini_run.txt`  
**Target file:** `Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_tdf.tdf`

## What was tested

Structural integrity of one frozen SCE1 ATDF sample against the PDS label and
TRK-2-25 physical layout (8064-byte blocks × 288-byte logical records).

## Results

| Check | Result |
|---|---|
| Byte length multiple of 8064 | PASS (18,668,160 B = 2315 blocks) |
| Logical record count | 64820 (matches label FILE_RECORDS) |
| Zero-pad records | 2 |
| File-ID record (type 10) creation time | 2002 DOY 166 02:25:37 — **PASS** vs label |
| Spacecraft ID field | 82 (Cassini DSN ID) |
| Doppler/range observable decode | **not performed** |
| Geometry + residual fit | **not performed** |

## Why residual adjudication remains PENDING_DATA

The CORS0021 cumulative index shows the conjunction archive also requires ODF,
RSR, SPK, EOP, ION, TRO, PD1/PD2, and multi-day TDF coverage. A single TDF
sample cannot separate:

- geometric light time,
- clock / media calibrations,
- solar plasma,
- the SDT `c_far` excess delay.

Fetching a decoder alone without those products would still leave the
comparison underdetermined.

## Classification

**PENDING_DATA** (structural sample validated; empirical Shapiro-like marker blocked).

## Next fetch list (pre-register before download)

1. Multi-day TDF/ODF spanning SCE1 closest approach.  
2. SPK + station geodesy + EOP/ION/TRO for the same interval.  
3. Independent path-delay products (PD1/PD2) as MODEL-PROCESSED comparators only.  
4. Validated ATDF→observable tool with fixture tests on a non-conjunction day.  
5. Pre-registered impact-parameter / solar-offset scan and PPN-amplitude hold-out.
