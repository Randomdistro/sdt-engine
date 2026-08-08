# GOM25 D4b Cassini ODF Structure Results — 2026-08-08

**Status:** `STRUCTURE_PARTIAL`; `UNDECODED` observables; no propagation or
solar-depth result.

## Scope and inputs

This is a label-defined binary-structure and time-tag audit of the frozen
SCE1 ODF fixture only. The checksum-verified ODF and label are listed in
`Datasets/solar_propagation_2026-08/MANIFEST.md`; the runnable instrument is
`gom25_d4b_odf_structure.py`. It deliberately never reads bytes 9–16, the
numeric observable integer/fractional fields.

The original D4b pre-registration called the fixture non-conjunction. That was
unsupported: the frozen inputs give no independent geometry classification.
Amendment 01 corrected the scope before field processing.

## Structural checks that pass

| check | result |
|---|---|
| ODF framing | `274,176 = 7,616 × 36` bytes; 34 complete 8,064-byte blocks |
| input hashes | ODF and label match the frozen manifest values |
| group headers | all eight label-declared header tuples match at their declared packet positions |
| Orbit Data group | 7,447 rows, exactly as labelled |
| format ID | all 7,447 rows are format `2`, as required by the ODF label |
| tracking category | all rows identify data type `12` (two-way Doppler) |
| station and validity metadata | station 25 transmit/receive; all 7,447 validity flags are `0` |
| Data Summary count | summary reports 7,447 samples |

The data-type label establishes the category and unit convention, but no
numeric Doppler field was extracted, exported, summarized, or compared.

## Unresolved conflicts

1. The ODF file-label date field decodes as `1020615`; the frozen ODF label
   defines that four-byte field as six-digit `YYMMDD`, while its product-creation
   date corresponds to `020615`. No revision-matched source in the frozen set
   authorizes dropping the leading `1` or applying another transformation.
2. The first and last Orbit Data time tags are respectively `500 ms` after the
   label/Data Summary whole-second bounds. The ODF label identifies a Doppler
   time tag as a compression-interval midpoint, but the frozen material does
   not state how that convention relates to the product start/stop fields at
   fractional-second precision. The raw difference is retained rather than
   rounded or silently accepted.

## Audit correction log

The first instrument expectation used `020606`, conflating the observation date
(day 157) with the product-creation date (day 166). The expected calendar date
was corrected to `020615`; the raw `1020615` conflict remains. The instrument
also originally reported `READY_FOR_ODF_FIXTURE_ONLY` unconditionally. It now
derives the classification from all checks and correctly returns
`STRUCTURE_PARTIAL` for this fixture.

## 2026-08-09 source-resolution correction

The official PDS copy closest to the label's claimed 1996 revision is a
Change 1 document reissued 15 August 1996, not 1 August. Its change log says
the 1996 change reformatted the document. The frozen Cassini SIS instead cites
the Change 3 document dated 15 June 2000. The competing source claims therefore
remain unresolved; neither may be silently selected.

Both frozen revisions define the File Label word as `YYMMDD`, define Orbit Data
Format ID 2, and identify Doppler tags as compression-interval midpoints.
Neither provides a source-defined mapping from `1020615` to `020615`, nor an
explicit rule connecting a midpoint tag to Data Summary first/last sample time
at sub-second precision. The document-resolution result is recorded in
`GOM25_D4b_ODF_DOCUMENT_RESOLUTION_RESULTS_2026-08-09.md`.

Accordingly, the earlier wording that an exact 1 August 1996 document was the
sole next gate is superseded. The corrected next gate is a producer-applicable
ODE/ODF source or independently documented binary fixture that resolves both
encodings without transformation by assumption. Status remains
`STRUCTURE_PARTIAL`; no observable field is unlocked.

## Classification and next gate

The ODF label names **TRK-2-18, 1 August 1996** as the applicable Orbit Data
Group specification. That exact revision, with a provenance-preserved binary
fixture or explicit explanation of the date and midpoint encodings, is required
before this ODF may become a decoder fixture. A valid ODF fixture would still
not resolve the TDF document-version conflict or authorize a Cassini solar-delay
residual. The latter additionally requires the pre-registered geometry, clock,
media, station, and multi-day data inputs.
