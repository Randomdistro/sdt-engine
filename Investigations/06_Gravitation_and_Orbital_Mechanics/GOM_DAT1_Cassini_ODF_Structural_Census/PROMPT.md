# GOM28 — Cassini SCE1 ODF Structural Census (D4 alternate path)

> **Status:** PRE-REGISTERED — 2026-08-07.  
> **Upstream:** GOM25 D4 TDF path `STRUCTURE_PARTIAL` (label vs TRK-2-25 format conflict).  
> **Canon edits:** none.

## 0. Objective

Test whether the frozen Cassini SCE1 **Orbit Data File (ODF)** sample can be
structurally validated against its paired PDS3 label well enough to justify a
later residual reconstruction path — without extracting a delay, Doppler, or
theory residual in this loop.

This is an instrument/data-path audit, not an SDT empirical adjudication.

## 1. Claims under test

| Claim ID | Exact claim |
|---|---|
| GOM28-C1 | Frozen ODF byte length equals `RECORD_BYTES × FILE_RECORDS` from the paired label. |
| GOM28-C2 | Physical block packing is an integer number of 8064-byte blocks (DSN archive convention). |
| GOM28-C3 | Group headers decode to primary/secondary keys declared in the paired label; undeclared group keys are reported and fail closed. |
| GOM28-C4 | Spacecraft ID / creation timestamp fields in the file-label group are consistent with the paired label where the label supplies an expectation. |
| GOM28-C5 | ODF alone yields an admissible one-/two-way propagation residual | **Must remain PENDING_DATA** — this loop never claims a residual. |

## 2. Frozen inputs (checksum-gated)

| File | Expected role |
|---|---|
| `Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.odf` | binary ODF |
| `Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.lbl` | sole field-definition source for this census |
| Manifest SHA-256 | must match before parse |

No Bertotti γ, no PPN fit, no engine `shapiro_delay` enters this instrument.

## 3. Decision rules (before execution)

1. SHA mismatch ⇒ abort; no status beyond INSTRUMENT INVALID.  
2. Size or block packing fail ⇒ C1/C2 FAIL → path `STRUCTURE_FAIL`.  
3. Undeclared primary keys in group headers ⇒ C3 FAIL → fail closed.  
4. Label-expected spacecraft/time mismatch ⇒ C4 FAIL (or UNADJUDICATED if label has no comparable field).  
5. Any path that prints a μs delay or Hz residual in this loop is a protocol violation.

## 4. Instrument validation

A. Synthetic 36-byte record with known big-endian integers round-trips.  
B. Truncated fixture rejected.  
C. Manifest hash gate rejects a flipped byte.

## 5. Parallel side-gate (same iteration)

If Horizons Sun-centered 2024 vectors become available, re-run GOM26 C4
multi-year hold-out with frozen checksum. If unavailable, record
`PENDING_DATA` and do not widen the INTRA_YEAR claim.

## 6. Next gate if C1–C4 PASS

Pre-register ODF observable-field decode (Doppler/range groups) against a
**non-conjunction** fixture before any solar-conjunction residual test.
