# GOM27 D5 BF080 Staging Results

**Date:** 2026-08-07  
**Scope:** non-interactive archive-access test only. No raw visibility file was
downloaded, calibrated, or compared with any gravitational prediction.

## Frozen evidence

The product-detail response for the first pre-registered 2005-10-01 execution
block is frozen as
`Datasets/solar_propagation_2026-08/raw/nrao_bf080_file3_product_details.json`,
SHA-256 `2c1908cb9c1ce482f21100a9efde058a2a18bf0da7c35359abf84a5be0ae605b`.
It identifies the raw product as `VLBA_VSN005016_file3.uvfits`, project
`BF080`, with calibration status `Do Not Calibrate` and 56 scan rows. Those
scan rows include all four pre-registered solar-deflection sources.

The catalogue locators resolve the fixed earliest-session subset to six public
UVFITS execution blocks. The first is `VLBA_VSN005016_file3.uvfits`; the
remaining five retain the same fixed-session selection and are not substituted
by data quality or model agreement.

## Access test

| Test | Result |
|---|---|
| BF080 project and first locator checksum gate | PASS |
| First product file identity | PASS: public, raw correlation, UVFITS |
| Four-source scan coverage | PASS |
| Product calibration status | `Do Not Calibrate` |
| Direct delivery URL in frozen product metadata | FAIL: none |
| TAP download capability | unavailable by NRAO's frozen documentation |
| Raw data retrieval in this run | not attempted; would require archive staging |

## Error origin and correction

The first read-only detail request supplied the archive's TAP-style
`uid://vlba/correlation/...` identifier as `sdm_id` and returned HTTP 404. The
archive client uses the UVFITS filename (`VLBA_VSN005016_file3.uvfits`) for this
detail endpoint. Repeating the read-only query with that identifier returned
the documented scan metadata. This corrected a query-identifier assumption; it
does not create a download capability.

## Classification

**`PENDING_ACCESS`**, nested under the prior
**`PENDING_RECONSTRUCTION`** result. The raw observational product is publicly
identified and uncalibrated, but the source provides no direct delivery handle
in the frozen response. NRAO documentation says TAP supports metadata queries,
not downloads; the web archive stages VLBA products and supplies retrieval
information through its delivery flow.

No empirical SDT conclusion follows. The GOM27 deflection prediction remains
`COMPUTED`; its observational status remains `UNADJUDICATED`.

## Required recovery

An operator must use the NRAO Archive Access Tool to request exactly the six
pre-registered 2005-10-01 blocks, receive the archive-issued retrieval link,
and provide the raw files plus associated calibration material. On receipt:

1. checksum and manifest each raw file before inspection;
2. freeze the exact calibration chain and external ancillary inputs;
3. validate the visibility-to-angle pipeline on a non-solar fixture; and
4. pre-register the independent solar geometry and held-out residual test.

No gamma/PPN deflection correction may enter that reconstruction as an input.
