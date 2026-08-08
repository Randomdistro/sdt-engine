# GOM25 D4b ODF Decoder Pre-Registration

**Date:** 2026-08-08  
**Scope:** binary-structure and documentation-consistency audit of the frozen
non-conjunction Cassini SCE1 ODF sample. This is not a propagation, range,
Doppler, geometry, or theory-residual test.

## Purpose

Use the ODF as a separate decoder fixture while TDF field extraction remains
blocked by its frozen document-version conflict. The audit may establish only
facts that the ODF label and an explicitly revision-matched format source state
unambiguously. It must never transfer a TDF bit layout to ODF merely because
both products are 8,064-byte physical blocks.

## Frozen inputs

1. `Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.odf`
2. `Datasets/solar_propagation_2026-08/raw/cassini_sce1_157_odf.lbl`
3. `Datasets/solar_propagation_2026-08/raw/trk225_tdf_unpack.pdf`, but only
   where it explicitly identifies an ODF-compatible format and revision.

Their full checksums, bytes, and provenance are first verified against the
local dataset manifest/intake record. No other tracking product, ephemeris,
calibration, or physics input is permitted.

## Fixed acceptance checks

1. The ODF byte length equals the label's physical record size times record
   count and frames into declared logical records without remainder.
2. Every non-padding logical-record type and format pair is declared by a
   frozen, ODF-specific source. Undeclared values remain `UNDECODED`.
3. A decoded header/timestamp may be reported only when the label specifies
   its bit offset, width, units, epoch, and expected value independently.
4. Any alleged Doppler, range, frequency, or time field must have a complete
   ODF-specific field definition and a non-conjunction fixture check. Otherwise
   it remains `UNDECODED`.

## Stop conditions

- Missing, contradictory, or TDF-only grammar: `STRUCTURE_PARTIAL`.
- Valid ODF grammar: `READY_FOR_ODF_FIXTURE_ONLY`; this does not unlock TDF
  observable extraction or a solar-delay comparison.
- No fit, residual, solar geometry, `koppa`, profile coefficient, PPN value,
  or standard-model subtraction may be calculated in this loop.
