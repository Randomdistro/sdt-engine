# GOM_DAT5 (ODF observable unit path), C5 — assessment (2026-10-12)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Class: VERIFICATION (excluded from physics tallies). Sections 0–2 are the registration, written before `gom_dat5_reset_1.py` exists. Scope per the rewritten prompt of 2026-10-12: C1, C2, C4 are met on P0 via the supplier (the 2026-10-10 record; median |obs| 50 244.3 Hz); **C5 only**: decode a MESSENGER ODF record with provenance and apply the same magnitude gate, registered first.

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` and the kept previous specification (the C5 fixture: MESSENGER one-way Doppler −382738.663803100 Hz from the PDS `odf_unpack` example, source URL given there); the 2026-10-10 DAT5 record. Fetched for this item (public PDS document, own directory, text extraction only): `odf_unpack.pdf` from the Radio Science documentation bundle (`DSN_TRK-2-18`), SHA-256 `ec3ecc0de7d6e197d6e16972d624a57e448ca4a447a9c52bb0558376828dc156`, 531 084 bytes. Its text was read: the description of the example file (logical identifier `urn:nasa:pds:radiosci_documentation:dsn_trk-2-18:odf07155`, DSN stations 14, 43, 63, 35 hours on 4–5 June 2007, 60 s sampling) and its Table 3, which unpacks record 6 field by field with the hex bytes. Not read: the archived GOM_DAT5/GOM32 assessment, tool and run log. The example **file** (`odf07155.dat`) was not fetched; only the document's unpacked record is available here.

## 1. What can and cannot be done (analysis)
The prompt asks to decode "one MESSENGER ODF with provenance". The file is not in the repository and was not fetched; the document's Table 3 gives the hex bytes of the fields of record 6 and the unpacked values. That allows (a) a **known-answer test of my decoder** on a record not from Cassini (rebuild the 36-byte record from the table's hex fields, decode with the same bit extraction used for Cassini, compare each field with the document's unpacked value) and (b) the C5 magnitude gate on the documented value. It does not allow a decode of the example file's other records, nor of its two-way Doppler (type 12) rows plotted in the document's Figure 3. Registered: C5 is evaluated on the documented record 6; the full-file decode is stated as not done.

## 2. Registered expectations and procedure
Expected values (the document's Table 3, record 6): record time tag 1 812 103 240 s (fraction 0); observable integer part −382 738 (hex `ff fa 28 ee`) and fractional part −663 803 100 × 10⁻⁹ (hex `d8 6f 2b 24`), so −382 738.6638031 Hz; format ID 2; primary receiving station 63; transmitting station 0; network ID 0; data type 11 (one-way Doppler); downlink band 2 (X); uplink band 0; reference-frequency band 2; validity 0; item 15 (receiver channel) 1; item 16 (spacecraft ID) 236; item 17 (receiver/exciter independent flag) 1; reference frequency (I18·2²⁴ + I19) mHz = 137 079 · 2²⁴ + 8 424 936 mHz; compression time item 21 = 6000 (0.01 s) = 60 s; transmitting-station uplink delay item 22 = 0.
Procedure: build the 36-byte record from the table's hex words (time tag, delay word, observable pair) and the bit strings of the packed words as listed (the table's bits 129–288), decode with the Cassini decoder's field positions (time: bytes 1–4 + 10 bits; packed word at byte 17: format 1–3, RX 4–10, TX 11–17, network 18–19, type 20–25, downlink band 26–27, uplink band 28–29, third band 30–31, validity 32; items 15 at bits 33–39, 16 at 40–49, 17 at 50, 18 at 51–72, 19 at 73–96; bytes 29–36: item 20 at 1–20, 21 at 21–42, 22 at 43–64), and compare every field. Validation: a synthetic Cassini-layout record also round-trips (as GOM_DAT2). C5 gate: |observable| ≥ 1 kHz (the old specification's rule: C5 fails if |Doppler| < 10³ Hz).
**Expected landing:** all listed fields reproduce the document's values; |obs| = 382 738.66 Hz ≥ 1 kHz: C5 met on the documented record; the full-file decode PENDING_DATA.

## 3. Results (VERIFICATION; `gom_dat5_reset_1.py`, output `gom_dat5_reset_1_results.txt`; single pass, no amendment)
**Validations.** VA (synthetic Cassini-layout round trip) met. **VK (known answer): the record rebuilt from the document's Table 3 decodes, field by field, to the document's unpacked values** — record time tag 1 812 103 240.0 s; observable −382 738.663803100 Hz (integer part −382 738 and fractional part −663 803 100 × 10⁻⁹); format ID 2; receiving station 63; transmitting station 0; network ID 0; data type 11; downlink band 2; uplink band 0; reference-frequency band 2; validity 0; item 15 = 1; item 16 = 236; item 17 = 1; reference frequency (I18·2²⁴ + I19) = 137 079·2²⁴ + 8 424 936 = 2 299 812 417 000 mHz (2.2998 GHz; the document's text writes the high part as "137097", the table and the arithmetic give 137 079); item 21 = 6000 (compression time 60.00 s); item 22 = 0. Every field matched (19 of 19).
**C5 met on the documented record:** |observable| = 382 738.66 Hz ≥ 1 kHz (the registered gate). The MESSENGER value is a one-way Doppler (type 11) with a reference frequency of 2.2998 GHz and a compression time of 60 s, in the same product class and field layout as the Cassini rows (the field positions that the document lists equal those used for Cassini in GOM37, GOM38, GOM_DAT2 and GOM_DAT4). The example file `odf07155.dat` was **not fetched**: its other records, including the two-way Doppler (type 12) plotted in the document's Figure 3, are PENDING_DATA.
Limits of this test: the record was rebuilt from the document's own field listing and decoded at the field positions I use, so the test confirms that my positions equal the document's (an agreement between two descriptions of the layout), not that the decoder was exercised on bytes written by DSN software. The raw bytes of record 6 are in the document's Figure 2 hex dump, which this record did not use.
The expected landing held (all fields; 382 738.66 Hz).

## 4. Grades
| Item | Grade |
|---|---|
| C5 magnitude gate on the documented MESSENGER record | **VERIFICATION, met** (382 738.66 Hz ≥ 1 kHz) |
| Decoder known-answer (19 fields) | **VERIFICATION, met** (positions equal the document's) |
| Full MESSENGER file decode | **PENDING_DATA** (file not fetched) |
| ENGINEERING_DOPPLER_HZ classification | **supported on P0 (supplier) and now by the published example's magnitude and layout** |
Excluded from physics tallies.

## 5. Direction
1. The document's Table 3 confirms the meaning of Items 15–22 for Doppler rows (receiver channel; spacecraft ID; independent flag; compression time; uplink delay). For range rows the same words carry the range components and coder offsets (TRK-2-18 Table 3-3b); the GOM38 follow-up owed there (decoding Items 15 and 20–22 of the type-37 rows from the documents before any range scale is accepted) can use this layout.
2. To close the full-file decode, the example ODF `odf07155.dat` of the PDS bundle `urn:nasa:pds:radiosci_documentation:dsn_trk-2-18` would be fetched with its hash.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
