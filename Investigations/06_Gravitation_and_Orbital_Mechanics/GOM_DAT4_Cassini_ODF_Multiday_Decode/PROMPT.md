# GOM_DAT4 — Cassini ODF multi-day decode (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Verification item: its rows are excluded from physics tallies, per the prompt's id alias. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
Open. The supplier decoded P0 only. All eight CORS_0021 ODFs (K252 + XMMMV0, days 157–160) need a fresh multi-file decode; only the day-157 files were confirmed present locally.

## 2. Next round
1. Confirm all eight files on disk (manifest with sizes and hashes).
2. Decode each with the validated P0 decoder.
3. Checks: per-file format ID, time windows contiguous across days, rows per file.

## 3. Note
These decodes feed the Cassini-based gravity tests. No physics result is drawn from a VERIFICATION row.

---

## Previous specification (kept as written)

# GOM31 — Multi-Day CORS_0021 ODF Observable Decode

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Upstream:** GOM30 OBSERVABLE_DECODE_PASS; local CORS_0021 volume confirmed.  
> **Canon edits:** none.

## 0. Objective

1. Decode **all eight** CORS_0021 Orbit Data Files (SCE1 days 157–160,
   K252 + XMMMV0) into label-scaled `obs_Hz` / `f_ref_Hz` series.  
2. Bound each file by its own PDS3 pointers (`^ODF3C_TABLE` … next group).  
3. Clear GOM30-C4 `PENDING_FETCH` to local **HAVE**.  
4. Do **not** form light-time residuals, γ fits, or `ϟ` fits.

## 1. Claims

| ID | Claim |
|---|---|
| GOM31-C1 | All eight ODF binaries exist under the frozen local volume path. |
| GOM31-C2 | For each file, orbit-data row count equals `next_group − ODF3C` and matches label `ROWS` when present. |
| GOM31-C3 | Every orbit-data row yields finite `obs_Hz` and `f_ref_Hz > 0`. |
| GOM31-C4 | Per-file summary published: n, time span, obs min/median/max/stdev, f_ref median, dominant data_type / RX. |
| GOM31-C5 | No residual / no competitor fit / no canon edit. |

## 2. Instrument rules

- Reuse GOM30 bit packing (`obs_Hz`, Items 18–19 → `f_ref_Hz`).  
- Synthetic validation A must PASS before any file decode.  
- Hash gate: report SHA-256 per file; do **not** require the single P0 hash for non-P0 files.  
- Authoritative base:
  `Datasets/solar_propagation_2026-08/raw/cassini_sce1/cors_0021/`  
  Online mirror reference:
  `https://atmos.nmsu.edu/pdsd/archive/data/co-ss-rss-1-sce1-v10/cors_0021/`

## 3. Decision rules

1. Missing any of the eight products ⇒ C1 FAIL.  
2. Row-bound mismatch vs label ⇒ that file FAIL (C2).  
3. Any non-finite obs or non-positive f_ref ⇒ C3 FAIL.  
4. Computing delay residuals ⇒ protocol violation.

## 4. Classification note

Whether `obs_Hz` is raw Doppler or a navigation pseudo-residual remains
**UNADJUDICATED** (carried from GOM30). Multi-day coverage alone does not
adjudicate the unit path.

---

## Audit correction 2026-10-05 (record / status)

**Finding:** Claims are numbered GOM31-C1 … against folder GOM_DAT4, and the PASS rows are file-presence and row-count checks.

**Correction:** Align the ids and label the rows VERIFICATION.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*

**Id alias (2026-10-05):** claim ids written `GOM31-C*` in this folder and its verdict are the claims of `GOM_DAT4`. The rows are VERIFICATION (data-structure, checksum and field-parse checks), not tests of a physical claim, and are excluded from physics PASS/FAIL tallies; earlier text is not rewritten.
