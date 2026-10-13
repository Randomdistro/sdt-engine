# GOM25 D4 Decoder Pre-Registration

**Date:** 2026-08-07  
**Scope:** structural decoding of the frozen Cassini SCE1 TDF sample only.  This
is not a timing-residual fit and cannot adjudicate a Shapiro-like marker.

## Purpose

Validate the binary record grammar of
`Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_tdf.tdf` against its
paired PDS3 label and the referenced TRK-2-25 specification.  The test begins
because the existing readiness probe uses a provisional `type==11`
transponder classification, whereas the PDS label identifies the transponder
logical record as type 30.  This discrepancy must be resolved before any
observable is decoded.

## declared dependencies

1. Existing frozen TDF, detached label, PDS archive readme, and cumulative
   index under `Datasets/solar_propagation_2026-08/raw/`.
2. The PDS `TRK_2_25.TXT` document and any format document explicitly named by
   the label, retrieved verbatim with checksum and added to the dataset
   manifest before use.

No solar, planetary, or timing value is an input to this decoder.

## Fixed validation criteria

1. File length equals label `RECORD_BYTES * FILE_RECORDS`, and is an integral
   number of 8,064-byte physical blocks.
2. Every nonzero logical record has a record-format/type pair that is declared
   by the label or TRK-2-25.  Undeclared values are reported, never coerced.
3. The file-identification record decodes to its label creation timestamp,
   data-set identifier, and Cassini spacecraft identifier.
4. The transponder logical record is identified using the documented type;
   no value is decoded because a nearby type happened to be present.
5. If a Doppler/range field cannot be independently located, unit-labelled,
   and time-tagged from the format specification, it is emitted as
   `UNDECODED`, not guessed.

## Non-goals and stop conditions

- Do not infer delay, range residual, geometry, profile exponent, or solar
  koppa from this sample.
- Do not fit a baseline or subtract a reference-framework prediction.
- Stop at `READY_FOR_OBSERVABLE_EXTRACTION` if the binary grammar validates;
  full conjunction coverage, station/frequency-ramp data, media corrections,
  and a separately pre-registered geometry model remain required for a timing
  residual.
