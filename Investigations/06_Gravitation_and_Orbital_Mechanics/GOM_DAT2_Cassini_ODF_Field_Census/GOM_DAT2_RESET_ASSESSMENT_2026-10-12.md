# GOM_DAT2 (Cassini ODF field census), fresh one-file decode — assessment (2026-10-12)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Class: VERIFICATION (excluded from physics tallies). Sections 0–2 are the registration, written before `gom_dat2_reset_1.cpp` exists. Follows the 2026-10-10 record of the other session (format, time and rows met via GOM_DAT8 Phase A; histogram and station IDs open) and the rewritten prompt of 2026-10-12 (restate C3 and C4 with expected values from the PDS label before decoding).

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` (previous specification below its line); the label `cassini_sce1_157_odf.lbl` (START_TIME, STOP_TIME, DSN_STATION_NUMBER, the DATA TYPE ID column text); the 2026-10-10 DAT2 record; my GOM_DAT1 record (file integrity, layout, 7447 orbit rows at records 6–7452). Not read: the archived GOM_DAT2/GOM29 assessment, `RUN_LOG.md`, `gom_dat2_odf_field_census.py`. Exposure: from GOM37 of this programme the same rows selected as type 12, valid, stations 25/25 numbered 7447, i.e. all rows.

## 1. Expected values from the label (before decoding)
- C1 format ID: the label's layout for the orbit group is format ID 2 (Table 3-3b: Format ID = 2).
- C2 time: all tags between START_TIME 2002-157T20:41:30 and STOP_TIME 2002-157T22:45:36 (the prompt's tolerance ±1 day; the tighter expectation, tags inside the window to within 1 s, is registered), non-decreasing.
- C3 data types: members of the label's allowed list (1–6, 11–13, 21–23, 36, 37, 41, 51–58); Doppler types 11–13 present; range types 36/37 not expected in a K252 Doppler product (a hand estimate from exposure, not from the label).
- C4 stations: every non-zero receiving and transmitting ID in {25, 45, 54} (the label's DSN_STATION_NUMBER).
- Validity bit: reported (not part of C1–C4).

## 2. Registered procedure
Validations: A synthetic 36-byte record with known time (integer seconds and milliseconds), station and type round-trips through the field extraction; B record 5 is the key-109 header and the next header (record 7453) is key 2030. Then: histogram of DATA TYPE ID over the 7447 rows, histogram of (receive, transmit) station pairs, FORMAT ID histogram, minimum and maximum time tags against the label window, monotonicity count. Decision as the prompt: format ≠ 2 ⇒ C1 fail; time outside the window by > 1 day ⇒ C2 fail; station outside the label set ⇒ C4 fail. No residual is computed.
**Expected landing:** format 2 for 7447 rows; all type 12; stations (25, 25) for all rows; time from 20:41:30.5 to 22:45:36.5 (the GOM_DAT1 summary record's start and stop tags plus 0.5 s), non-decreasing.

## 3. Results (VERIFICATION; instrument `gom_dat2_reset_1.cpp`, output `gom_dat2_reset_1_results.txt`; single pass, validations met)
Validations: A (synthetic record round trip) and B (record 5 key 109, record 7453 key 2030) met.
**C1 met:** FORMAT ID = 2 on all 7447 rows. **C2 met:** tags 1 654 548 090.500 to 1 654 555 536.500 s, non-decreasing (0 non-monotone steps), +0.500 s inside the label window at both ends (inside the registered ±1 s). **C3:** DATA TYPE ID histogram {12: 7447}; Doppler present (two-way), range types (36, 37) absent; validity {0: 7447}. **C4 met:** one station pair (25, 25) for all rows, inside the label set {25, 45, 54}. **C5:** no residual computed.
The expected landing held in every item (format 2, all type 12, stations (25, 25), time 20:41:30.5 to 22:45:36.5, non-decreasing). Note for the programme: the type-37 range rows exist in the XMMMV0 products (GOM38), not in this K252 product.

## 4. Grades
| Item | Grade |
|---|---|
| C1–C4 on the P0 K252 file | **VERIFICATION, met** (histogram and station IDs now closed) |
| C5 | **no residual, as required** |
Excluded from physics tallies.

## 5. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
