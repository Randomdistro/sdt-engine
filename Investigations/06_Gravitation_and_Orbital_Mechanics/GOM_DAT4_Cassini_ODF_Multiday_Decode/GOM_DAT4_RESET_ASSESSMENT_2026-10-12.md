# GOM_DAT4 (Cassini ODF multi-day decode) — assessment (2026-10-12)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Class: VERIFICATION (excluded from physics tallies). Sections 0–2 are the registration, written before `gom_dat4_reset_1.cpp` exists. Follows the rewritten prompt of 2026-10-12: confirm all eight CORS_0021 ODFs (K252 and XMMMV0, days 157–160) on disk with a manifest of sizes and hashes; decode each with the validated P0 decoder; per-file format ID, time windows across days, rows per file.

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md`; the eight paired labels (RECORD_BYTES, FILE_RECORDS, the ODF3C_TABLE ROWS, START_TIME, STOP_TIME, DSN_STATION_NUMBER); my GOM_DAT1 and GOM_DAT2 records and the GOM38 census (the XMMMV0 type counts). Not read: archived GOM_DAT4 assessment, `RUN_LOG.md`, tool. Exposure: GOM37 and GOM38 of this programme decoded these files (K252 rows 7447/20 748/17 289/35 942; XMMMV0 rows 84 266/86 389/92 798/106 143), so the expected counts below come from the labels and from that exposure, stated as such.

## 1. Expected values (before decoding)
- Presence: all eight `.odf` with paired `.lbl` under `cassini_sce1/cors_0021/sce1_DDD/odf/` (D = 157…160); size = RECORD_BYTES × FILE_RECORDS for each.
- Rows: the ODF3C_TABLE ROWS of each label equals the number of rows between the key-109 header and the next header.
- Format ID 2 on every row of every file.
- Time: every tag inside the file's label START_TIME…STOP_TIME to within 1 s (the prompt's day-level tolerance is also reported); non-decreasing within each file.
- Windows across days: for each product family the four label windows are in ascending order and non-overlapping; gaps between them are reported (a K252 product is a short pass per day, so contiguity in the strict sense is not expected).
- Data types: K252 all type 12; XMMMV0 types {11, 12, 13, 37} (exposure).
- Stations: non-zero IDs inside each label's DSN_STATION_NUMBER set.

## 2. Registered procedure
Manifest by SHA-256 and byte size of every `.odf` and `.lbl` (the K252 hashes are compared with the table in the GOM40a prompt, which lists them; the XMMMV0 hashes have no prior and are recorded as the manifest). Decoder: the validated P0 field extraction (GOM_DAT2: FORMAT ID bits 1–3, RX 4–10, TX 11–17, TYPE 20–25 of the packed word at byte 17; time = integer seconds + 10-bit milliseconds). Validation: the decoder reproduces the P0 file's GOM_DAT2 histogram exactly (7447 rows, format 2, type 12, (25, 25)) before the other files are read. Group headers are located by scanning the first words for the declared keys (101, 107, 109, 2030, 105, −1) and the data rows are those between the key-109 header and the next header. Decisions as the prompt: format ≠ 2 ⇒ fail; rows ≠ label ROWS ⇒ fail; tag outside the label window by more than 1 s ⇒ reported, by more than 1 day ⇒ fail; station outside the label set ⇒ fail. No residual is computed.
**Expected landing:** eight files present; K252 rows 7447, 20 748, 17 289, 35 942 and XMMMV0 rows 84 266, 86 389, 92 798, 106 143; format 2 everywhere; tags inside the windows within 1 s; windows ascending without overlap.

## 3. Results (VERIFICATION; instrument `gom_dat4_reset_1.cpp`, output `gom_dat4_reset_1_results.txt`; single pass, validation A met)
**Manifest (SHA-256, bytes).** K252 ODF: 157 `c2ea51d9…bfaf7` 274 176; 158 `9393717f…93a4` 749 952; 159 `cfcba026…3288` 628 992; 160 `7f447ba5…ab9` 1 298 304 — all four equal the table of the GOM40a prompt; their labels (54 675, 54 685, 54 686, 54 685 bytes) equal it too. XMMMV0 ODF (no prior): 157 `2eb8d3ff0ba69797db137f7b7d2c7c03fd1c665aa17821f92f81144a7de1e90a` 3 040 128; 158 `fcf9e745be2b31d658488434d39e0193a86484ffcf8de1c93ed2f107be123545` 3 120 768; 159 `d687322e9eafd2c42ae1bcf8e9a25207981a0466d675d3eaef47d61c0ee6c1d7` 3 346 560; 160 `d6cd301e8c7c442b441d5c2d0671a95f1731ae23b770309e94a751dfa2ddf1b9` 3 830 400; labels 63 902, 63 903, 63 902, 63 914 bytes (`ab4204d3…52ef`, `d8789838…3e98`, `071724db…27dc`, `220b2871…cbe4`). All eight files and labels are present.
**Per file.** Size = RECORD_BYTES × FILE_RECORDS in all eight. Orbit rows found between the key-109 header (record 5) and the next header equal the label ROWS in all eight: K252 7447, 20 748, 17 289, 35 942; XMMMV0 84 266, 86 389, 92 798, 106 143. FORMAT ID = 2 on every row. Time tags equal the label START/STOP at both ends of every file (+0.500 s; inside the registered 1 s), non-decreasing (0 non-monotone steps). Data types: K252 {12} only in each file; XMMMV0 157 {11: 9543, 12: 55 558, 13: 18 980, 37: 185}, 158 {11: 1, 12: 63 057, 13: 23 123, 37: 208}, 159 {11: 1, 12: 59 866, 13: 32 763, 37: 168}, 160 {11: 11 047, 12: 69 799, 13: 25 065, 37: 232}.
**Windows across days.** K252: short passes, ascending and non-overlapping, gaps 66 575, 54 692 and 51 024 s between days; spans 7446, 34 241, 31 441, 35 945 s. XMMMV0: ascending and **contiguous** (gaps of 2, 1 and 2 s between days; spans 84 551, 78 410, 90 569, 97 458 s).
**C4 (stations) NOT MET for one file.** The XMMMV0 day-157 label lists DSN_STATION_NUMBER = {25, 45, 54}, but its rows contain a receiving station 65 (one type-37 row, receive 65 / transmit 25, found also by the GOM38 census). By the registered rule (station outside the label set ⇒ fail) that file fails C4; the other seven files' stations are inside their label sets (K252 158–160 and XMMMV0 158–160 list {25, 45, 65}). It is a defect of the day-157 label (an incomplete station list), not of the decode.
The expected landing held for presence, rows, format, time windows, ascending windows, data types and K252 contents; it did not hold for the stations of XMMMV0 day 157.

## 4. Grades
| Item | Grade |
|---|---|
| All eight files present, manifest recorded (K252 hashes equal the prompt's) | **VERIFICATION, met** |
| Rows = label ROWS; format ID 2; tags inside the label windows; monotone | **VERIFICATION, met (8 of 8)** |
| Windows across days | **met** (K252 ascending with gaps; XMMMV0 contiguous to 2 s) |
| Stations inside the label sets | **not met for XMMMV0 day 157 (station 65 absent from its label)**; met for the other seven |
Excluded from physics tallies. The decoded K252 and XMMMV0 products are the data used by GOM37, GOM38, GOM40a, GOM40b and GOM_DAT9 in this programme.

## 5. Direction
The XMMMV0 day-157 label should list 65 among its stations; the rows with station 65 are one type-37 row and no Doppler row in that file, so none of this programme's Doppler selections (receive = transmit = 25) is affected.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
