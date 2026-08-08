# GOM29 — Cassini SCE1 ODF Orbit-Data Field Census

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Upstream:** GOM28 STRUCTURE_PASS.  
> **Canon edits:** none.

## 0. Objective

Decode **metadata fields only** from the Orbit Data Group of the frozen SCE1
ODF, using the paired PDS3 label as the sole bit-layout source. Report time
coverage, format ID, data-type histogram, and station IDs.

This loop does **not** compare observables to any SDT or competitor delay model.

## 1. Claims

| ID | Claim |
|---|---|
| GOM29-C1 | Orbit data records (after header key 109) parse with FORMAT ID = 2 (post-1997 layout). |
| GOM29-C2 | Time tags are monotonic non-decreasing and lie within label START_TIME…STOP_TIME (±1 day tolerance for UTC/encoding edge). |
| GOM29-C3 | DATA TYPE ID histogram is reported; presence of Doppler (11–13) and/or range (36–37) types is documented. |
| GOM29-C4 | Receiving/transmitting station IDs are reported; must be subset of label `DSN_STATION_NUMBER` when nonzero. |
| GOM29-C5 | No SDT residual is computed in this loop. |

## 2. Layout (from paired label ODF3C)

- Record 5 = orbit data group header (key 109).  
- Records 6 … (next header − 1) = 36-byte data rows.  
- Time integer: bytes 1–4, seconds from 1950-01-01 00:00 UTC.  
- Time frac: bits 1–10 of bytes 5–8, milliseconds.  
- Items 6–19 bitfield starts at byte 17: FORMAT ID bits 1–3; RX station bits 4–10; TX station bits 11–17; DATA TYPE bits 20–25 (6 bits).

## 3. Decision rules

1. Hash gate same as GOM28.  
2. Any FORMAT ID ≠ 2 ⇒ C1 FAIL / UNADJUDICATED for post-1997 layout.  
3. Time outside label window by >1 day ⇒ C2 FAIL.  
4. Printing a μs residual or fitting `ϟ` ⇒ protocol violation.

## 4. Validation

A. Synthetic record with known time/type round-trips.  
B. Header key 109 located at label pointer record 5.
