# GOM_DAT1 (Cassini SCE1 ODF structural census) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `gom_dat1_reset_1.cpp` exists. Class: VERIFICATION (data structure); no physical claim and no residual (the prompt's rule 5).

## 0. Inputs read and exposure
Read: `GOM_DAT1/PROMPT.md` in full (including the 2026-10-05 id-alias note: the claim ids written GOM28-C* are those of GOM_DAT1); the paired label `cassini_sce1_157_odf.lbl` (table list with ROWS, the PRIMARY KEY descriptions, the file-label items); the MANIFEST row for the sample. Not read: archived GOM_DAT1/GOM28 results. Exposure: from GOM_DAT8 Phase A of this programme the same file's size (274 176 bytes = 36 × 7616) and the positions of the first and last orbit-data rows were verified; the present loop repeats and extends that to all groups.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | status | Every claim is VERIFICATION (the prompt's alias note). Reported as such and excluded from physics tallies. |
| D2 | C3 | The label declares the primary keys in the header descriptions: 101 (file label), 107 (identifier), 109 (orbit data), 2030 (ramp groups for stations 25, 45, 54), 105 (data summary), −1 (end of file). Secondary keys: 0, except the ramp groups where the secondary key is the station number (a TRK-2-18 statement; the label's "not used" text is for the groups where it is 0). The check is made on the header record at the position the label's ROWS imply, and independently by scanning all records for small-integer first words that are not time tags. |
| D3 | C4 | The label gives no numeric spacecraft ID (its representative list does not include Cassini): the spacecraft-ID comparison is `UNADJUDICATED` by the prompt's own rule 4; the file-creation date and time (YYMMDD, HHMMSS) have a comparable label field (PRODUCT_CREATION_TIME = 2002-166T02:09:18), and the file-reference date (19500101) is compared with the EME50 convention in the label. |
| D4 | C2 | The prompt takes the 8064-byte block as the archive convention; the label's end-of-file data group (ROWS = 156) is the fill to the block end: 7616 records = 34 × 224 records per block. |
| D5 | gate | The manifest hash is checked before any parse. The hash of the same bytes in `cassini_sce1/cors_0021/sce1_157/odf/…k252v0.odf` is also reported (an identity of the two copies, not a new claim). |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
**Validations (before the sample).** A: a synthetic 36-byte record with known big-endian integers round-trips through the decoder. B: a truncated fixture (the sample with its last 7 bytes removed) is rejected by the C1 length rule. C: a one-byte flip in an in-memory copy changes the SHA-256 and the hash gate rejects it. D: the SHA-256 implementation reproduces the known digests of the empty string and of "abc".
**Checks.** C1: file bytes = RECORD_BYTES × FILE_RECORDS (36 × 7616 = 274 176). C2: file bytes / 8064 an integer. C3: the label's table list gives the group sequence and ROWS; the header record at each cumulative position decodes to the declared primary key and the expected secondary key; the sum of ROWS is compared with FILE_RECORDS and any difference is reported; a scan of all records finds every record whose first word is one of the declared keys (as an integer, not a time tag) and reports any other small-integer first word. C4: creation date/time and reference date as in D3.
**Decisions.** The prompt's: SHA mismatch ⇒ INSTRUMENT INVALID; C1 or C2 fail ⇒ STRUCTURE_FAIL; an undeclared key ⇒ C3 fail closed; C4 mismatch ⇒ fail, no comparable field ⇒ UNADJUDICATED; C5 stays PENDING_DATA; nothing in this loop prints a delay or a Doppler residual.
**Expected landing (hand estimate before registering).** C1 and C2 met (274 176 = 36 × 7616 = 34 × 8064). Header keys 101, 107, 109, 2030/25, 2030/45, 2030/54, 105, −1 found where the ROWS place them; the sum of ROWS is 7615 against 7616 records (one record not assigned by my reading of the table list: reported). Creation date 020615 and time 020918 equal the label; spacecraft ID UNADJUDICATED (82 expected from the DSN numbering, not from the label).

## 3. Attempt 1 and Amendment 1 (instrument defect; registered before attempt 2)
**Attempt 1 (kept: `gom_dat1_reset_1_attempt1_label_textmode_hash.txt`).** Validations A–D met; the manifest gate matched the ODF and **rejected the label** (computed 0a12f682… against the manifest b27da74c…), `INSTRUMENT INVALID`, before any parse. Cause: my label reader opened the file in text mode, which on Windows rewrites line endings, so the bytes hashed were not the file's bytes. The gate did its job (fail closed); the defect is mine.
**Amendment 1.** The label is read as bytes (binary mode) for both the hash and the parse. Gates and expectations unchanged.

## 4. Results (attempt 2; VERIFICATION; instrument `gom_dat1_reset_1.cpp`, output `gom_dat1_reset_1_results.txt`)
**Instrument validations.** D (SHA-256 known digests), A (synthetic record round trip), B (truncated fixture rejected), C (one-byte flip rejected): all met.
**Manifest gate.** ODF c2ea51d9… and label b27da74c… match the MANIFEST rows; the copy in `cassini_sce1/cors_0021/sce1_157/odf/…k252v0.odf` is byte-identical.
**C1 met:** 274 176 bytes = 36 × 7616. **C2 met:** 274 176 / 8064 = 34 blocks of 224 records.
**C3 met:** the label's 14 tables give 8 header records; each lies at the position the cumulative ROWS imply and carries a declared primary key and the expected secondary key: 101 (record 1), 107 (3), 109 (5), 2030/25 (7453), 2030/45 (7455), 2030/54 (7456), 105 (7457), −1 (7459); the group start packet numbers equal record − 1 for each (0, 2, 4, 7452, 7454, 7455, 7456, 7458). A scan of all 7616 records for small-integer first words finds only the declared keys (101, 105, 107, 109, −1 once each, 2030 three times) and 154 zero words: no undeclared key. The sum of the label's ROWS is 7615 against 7616 records: the one record not assigned is the last, an all-zero record beyond the label's end-of-file rows (block fill).
**C4 mixed.** The file-label data: spacecraft ID **82**; creation time **020918** (equals the label's 02:09:18); reference date **19500101** (the EME50 convention the label states); creation date **1020615**. The registered literal comparison (YYMMDD = 020615, two least significant digits, as the label's Item 18 text says) **fails**: the field holds 102 for the year (years since 1900), i.e. 1900 + 102 = 2002 and the date 2002-06-15 equals the label's PRODUCT_CREATION_TIME (day 166) under that reading. The label's description of the field differs from the file's convention. By the prompt's rule C4 is not met as written (a description-versus-file difference of the year convention, not an inconsistency of the date). Spacecraft ID: the label supplies no number to compare, UNADJUDICATED (82 is the DSN numbering for Cassini, outside this loop's inputs).
**C5** PENDING_DATA (no residual was computed).
**Post-run inspection (descriptive, not registered).** The end-of-file group data begins with a directory in records 7460–7462: (101000, 0, 0 | 107000, 2, 0 | 109000, 4, 0), (2030025, 7452, 0 | 2030045, 7454, 0 | 2030054, 7455, 0), (105000, 7456, 0 | −1, 7458, 0): group key × 1000 (+ station) and start packet, consistent with the headers found; the rest of the end-of-file rows and the final record are zero. The data-summary record (7458) holds the start and stop tags 1 654 548 090 and 1 654 555 536 s since 1950 (a span of 7446 s, the label's 20:41:30 to 22:45:36) and the 7447 rows.
The expected landing held for C1, C2, the keys, the zero-padding difference of one record, the creation time and the reference date; it did not hold for the creation date, which I had written with a two-digit year.

## 5. Grades
| Item | Grade | Reason |
|---|---|---|
| C1 size | **VERIFICATION, met** | 36 × 7616 |
| C2 block packing | **VERIFICATION, met** | 34 × 8064 |
| C3 keys | **VERIFICATION, met** | 8 of 8 headers declared; scan finds no undeclared key |
| C4 label consistency | **VERIFICATION, not met as written (creation date convention); creation time and reference date met; spacecraft ID UNADJUDICATED** | the file stores the year as 102 (years since 1900); the label text says two digits |
| C5 | **PENDING_DATA** | unchanged |
Excluded from physics tallies (the prompt's alias note).

## 6. Direction
1. The structure is sound enough for the decoded observable work already done (GOM_DAT8, GOM37, GOM38 use the same layout). The label text for the creation-date field should be annotated (year convention), an edit to a dataset label that is outside this repository's scope: recorded here only.
2. The ramp groups for stations 45 and 54 are headers with no data rows in this file; station 25 has one ramp record (record 7454). The ramp content is the subject of GOM_DAT9.

## 7. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
