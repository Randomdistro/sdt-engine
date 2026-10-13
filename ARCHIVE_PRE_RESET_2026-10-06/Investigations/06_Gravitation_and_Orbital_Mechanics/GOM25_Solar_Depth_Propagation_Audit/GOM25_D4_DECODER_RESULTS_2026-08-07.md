# GOM25 D4 Cassini Decoder Results

**Date:** 2026-08-07  
**Scope:** frozen binary-grammar test only. No range, Doppler, delay, geometry,
or theory residual is decoded here.

## Inputs and validation rule

The instrument `gom25_d4_tdf_census.py` reads only the frozen TDF and detached
PDS3 label listed in `Datasets/solar_propagation_2026-08/MANIFEST.md`. It first
verifies their manifest SHA-256 values and then treats the label as the only
field-definition source. The public TRK-2-25 unpacking guide is retained in the
same manifest as an audit reference, but this run does not rely on a guessed
observable field from that guide.

The pre-registered decoder criterion requiring all nonzero record types to be
declared is tested directly. The criterion requiring a post-1997 file-ID record
format of 2048 is also tested directly and is not relaxed to match the data.

## Census result

| Item | Result |
|---|---|
| TDF / label SHA-256 | PASS |
| Length (`288 * 64820`) and 8,064-byte blocks | PASS: 18,668,160 B; 2,315 blocks |
| Logical record type census | `10:1`, `30:1`, `90:545`, `91:64271`, `0:2` |
| Undeclared record types | PASS: none |
| File-ID timestamp | PASS: `2002-166T02:25:37` matches label |
| File-ID spacecraft identifier | decoded as `82` |
| File-ID data-ID byte field | `UNADJUDICATED`; raw bytes retained, no verified label-to-field crosswalk |
| Transponder identification | PASS: exactly one type `30`, not type `11` |
| Doppler/range/time residual | `UNDECODED` |

## Falsification finding: format-document contradiction

The raw file-ID and transponder records each decode to record format `8`. Their
paired label says that both fields must be `2048` in files created on or after
1997-04-15; this file's creation timestamp is in 2002. The tracking-data
records decode to `8`, which matches that table's post-1997 rule. These
statements conflict for both header records and the frozen bytes do not satisfy
their file-ID/transponder format rules. Conversely, the frozen public
TRK-2-25 unpacking guide's ATDF example describes file-identification record
format `8`. Thus the guide and paired label disagree; the correct grammar
revision cannot be selected from the frozen sources alone.

This is a documentation-version conflict, not evidence for or against SDT,
relativity, or any propagation model. The raw data do not falsify either
documentation source. The correct action is to preserve the conflict and
prohibit field-level observable extraction until an authoritative
revision-matched grammar resolves it.

## Incomplete pre-registered check

The file-ID timestamp and spacecraft identifier have direct paired-label
expectations and pass. The raw 14-byte data-ID field is logged as
`0000052522f54020004154044460`, but neither frozen document supplies a
validated mapping from that bit sequence to `CO-SS-RSS-1-SCE1-V1.0`. The
original requirement to verify the data-set identifier from that raw field is
therefore `UNADJUDICATED`, rather than inferred from the label header.

## Origin and correction of the prior probe error

`gom25_cassini_tdf_probe.cpp` classified type `11` as the transponder record.
The paired label explicitly defines type `30` for that record. The independent
census finds one type-`30` record and no type-`11` record. The prior inference
is therefore false. It remains unchanged as a reproducible audit artifact;
new work must use type `30` and fail closed on undeclared types.

## 2026-08-09 source-resolution correction

The official PDS TRK-2-25 inventory was frozen and contains no member for the
SIS-cited 15 December 1998 revision. Its later candidate is an 1988 source
reissued after reformatting, with conflicting 1996-07-31 and 1996-10-15
metadata. It cannot resolve the 2002 header contradiction merely by agreeing
with raw format `8`.

`GOM25_D4_TDF_DOCUMENT_RESOLUTION_RESULTS_2026-08-09.md` records the frozen
source hashes, the PDS-collection coverage finding, and the unchanged census
re-run. The correct classification remains `STRUCTURE_PARTIAL`; the next gate
is a source or fixture explicitly applicable to the 1998/2002 grammar, not
another inferred conversion.

## Classification and next gate

**Status: `STRUCTURE_PARTIAL / PENDING_RECONSTRUCTION`.** Physical predictions
remain untested. The valid framing and timestamp checks do not license a delay
claim, because the header-format and data-ID issues leave the binary grammar
only partially validated.

Before a timing-residual test, pre-register and freeze: (1) an authoritative
revision-matched TDF grammar with a fixture; (2) multi-day conjunction TDF/ODF
coverage; (3) station, clock, EOP, ionospheric and tropospheric inputs; (4)
spacecraft and planetary states; (5) a one-/two-/three-way signal convention;
and (6) a blind, held-out impact-parameter test. The decoder must reproduce a
known non-conjunction observable before any solar-depth or Shapiro-like marker
is calculated.
