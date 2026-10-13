# GOM_DAT3 (Cassini ODF observable decode), cumindex freeze list — assessment (2026-10-12)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Class: VERIFICATION (excluded from physics tallies). Sections 0–2 are the registration, written before `gom_dat3_reset_1.py` exists. Scope per the rewritten prompt of 2026-10-12: C1–C3 are met on P0 via the supplier (median |obs| 50 244.3 Hz, f_ref per record); **C4 only**: decode the cumindex for SCE1 days 157–160 and list the frozen records, with the expected list written from the PDS index before comparison.

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` and its kept previous specification (C4: the cumindex enumerates all `*.ODF` products for SCE1_157…160 with start and stop times; priority list P0 K252 day 157, P1 XMMMV0 day 157, P2/P3 K252 and XMMMV0 days 158–160); `Datasets/solar_propagation_2026-08/raw/cassini_sce1_cors0021_cumindex.tab` (first rows only, to see the column layout: volume, label path, product name, product id, start, stop, creation); my GOM_DAT4 record (the eight label windows and creation times). Not read: archived GOM_DAT3/GOM30 results.

## 1. Expected list (written now, from the index layout and the DAT4 labels)
The index rows whose label path contains `/ODF/` and whose directory is SCE1_157…SCE1_160 are the frozen records. Expected: eight products, K252V0 and XMMMV0 for each of the four days, named `C32EASC2002_DDD_0000{K252V0,XMMMV0}.ODF`; their start and stop times equal the label START_TIME and STOP_TIME of the corresponding file (the DAT4 windows: K252 157 20:41:30–22:45:36; XMMMV0 157 05:30:00 (day 157) to 04:59:11 (day 158); the others as decoded in DAT4); creation times equal the labels' PRODUCT_CREATION_TIME (2002-166T02:09:18 for K252 157, 2002-166T02:19:20 for XMMMV0 157). The index may list other ODF products for these days; if so they are listed and reported as not frozen.

## 2. Registered procedure
Parse the index as quoted CSV; select the ODF rows for SCE1_157…160; print the list with start, stop, creation; compare each frozen record with (a) the file present on disk (name) and (b) its label START/STOP/creation (read from the paired `.lbl`). Decisions: C4 met iff every frozen record is present on disk with start/stop equal to its label to the second; extra ODF products in the index for these days are listed (not a failure); a frozen record absent from disk is `PENDING_FETCH` for that product. Hash and byte-size manifest of the eight pairs is the GOM_DAT4 manifest (not repeated). C1–C3 are not re-run (supplier). No residual or delay is computed.
**Expected landing:** eight ODF products listed, all present, start/stop and creation equal to the labels.

## 3. Attempt 1 and Amendment 1 (instrument defect; registered before attempt 2)
**Attempt 1 (kept: `gom_dat3_reset_1_attempt1_compare_length.txt`).** The index lists exactly the eight expected ODF products (K252V0 and XMMMV0 for days 157–160, none extra, none missing) and all eight are present on disk, but every record was reported `MISMATCH` although the printed index and label times are identical. Cause: my comparison cut both strings at 19 characters; the index times carry a tenth-of-second field (`…:30.0`, 19 characters with the point) and the label times do not (`…:30`, 17 characters), so the strings differed by the trailing point. A defect of mine. **Amendment 1:** the comparison is made on the first 17 characters (to the second, as registered). Nothing else changes.
**Attempt 2 (VERIFICATION; `gom_dat3_reset_1.py`, output `gom_dat3_reset_1_results.txt`).** The cumindex has 86 rows (7 columns each); 8 are ODF products of SCE1_157…160, exactly the eight expected names (K252V0 and XMMMV0, days 157–160), none extra and none missing from the index. All eight are present on disk and each record's start, stop and creation time equals its label to the second:
| Product | Start | Stop | Created |
|---|---|---|---|
| 157 K252V0 | 2002-157T20:41:30 | 2002-157T22:45:36 | 2002-166T02:09:18 |
| 157 XMMMV0 | 2002-157T05:30:00 | 2002-158T04:59:11 | 2002-166T02:19:20 |
| 158 K252V0 | 2002-158T17:15:11 | 2002-159T02:45:52 | 2002-168T17:20:50 |
| 158 XMMMV0 | 2002-158T04:59:13 | 2002-159T02:46:03 | 2002-168T16:07:07 |
| 159 K252V0 | 2002-159T17:57:24 | 2002-160T02:41:25 | 2002-175T19:34:26 |
| 159 XMMMV0 | 2002-159T02:46:04 | 2002-160T03:55:33 | 2002-170T19:29:07 |
| 160 K252V0 | 2002-160T16:51:49 | 2002-161T02:50:54 | 2002-176T21:33:22 |
| 160 XMMMV0 | 2002-160T03:55:35 | 2002-161T06:59:53 | 2002-176T17:30:56 |
**C4 met.** The expected landing held. The index shows the priority list of the previous specification (P0–P3) as a complete frozen set: all eight products exist locally, so no `PENDING_FETCH`. Note: the decoded tags of the K252 days 158–160 (DAT4) agree with these windows; the K252 windows of days 158–160 each cross midnight UTC (e.g. 158T17:15 to 159T02:45) while the DAT4 window of the label is the same.

## 4. Grades
| Item | Grade |
|---|---|
| C4 freeze list | **VERIFICATION, met** (8 of 8 products indexed, present, times equal their labels) |
| C1–C3 | **supplier (not re-run here)** |
Excluded from physics tallies.

## 5. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
