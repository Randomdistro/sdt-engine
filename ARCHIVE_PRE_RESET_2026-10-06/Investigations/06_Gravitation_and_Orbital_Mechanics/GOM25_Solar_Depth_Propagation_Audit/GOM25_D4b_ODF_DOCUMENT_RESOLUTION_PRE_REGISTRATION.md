# GOM25 D4b ODF Document-Resolution Pre-Registration

**Date:** 2026-08-09  
**Status before retrieval:** `STRUCTURE_PARTIAL`; numeric observables remain
`UNDECODED`.

## Trigger and error origin

The frozen Cassini ODF label calls its Orbit Data Group grammar
`TRK-2-18, version of 1 August 1996`. The frozen Cassini archive SIS instead
cites `TRK-2-18`, 15 June 2000, and states that the interface had significant
changes in April 1997. Its ODF record definition also identifies format ID 2,
whereas format ID 1 is the pre-1997 form. These are incompatible revision
claims for a 2002 format-ID-2 file.

Two unrepaired audit conflicts follow:

1. the File Label Group's four-byte creation-date word is `1020615`, while the
   frozen PDS label describes that field as six-digit `YYMMDD` and its
   product-creation timestamp corresponds to `020615`;
2. the first and last Orbit Data time tags are 500 ms later than the
   whole-second label/Data Summary bounds. The label calls a Doppler time tag a
   compression-interval midpoint but does not define the endpoint convention
   at fractional-second precision.

The prior label-only decoder cannot resolve either issue. It must not remove a
digit, round a time tag, or assume that the 1996 and 2000 grammars are
interchangeable.

## Candidate sources, pre-registered before retrieval

Only these official PDS technical-document products may be retrieved in this
loop:

1. `dsn_trk-2-18.1996-08-15.pdf` and its PDS XML label from
   `https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-18/`;
2. `dsn_trk-2-18.2000-06-15.pdf` and its PDS XML label from the same
   directory.

The official directory was discovered in browser navigation before this
pre-registration. No document body, raw ODF observable bytes, observable
value, residual, or physical result was extracted during discovery. That
ordering deviation is retained in the manifest.

## Fixed retrieval and parsing sequence

1. Download byte copies only into
   `Datasets/solar_propagation_2026-08/raw/`.
2. Record URL, filename, byte count, SHA-256, document class, and the discovery
   ordering note in `Datasets/solar_propagation_2026-08/MANIFEST.md` before
   opening either PDF or XML body.
3. Verify each recorded SHA-256 immediately before text extraction.
4. Inspect only the source statements needed for the two conflicts: document
   effective date/revision, format-ID applicability, File Label Group creation
   date encoding, Orbit Data time-tag meaning, and Data Summary/start-stop
   time conventions.
5. Re-run the existing structural instrument only after the source statements
   are recorded. It must continue to avoid bytes 9--16 of Orbit Data records
   and must not export, summarize, or compare Doppler, range, phase,
   frequency, residual, geometry, or theory values.

## Pre-committed acceptance rule

The status may change from `STRUCTURE_PARTIAL` only if the retained sources
jointly establish all of the following without a contradictory clause:

1. which revision applies to this 2002 format-ID-2 Cassini ODF, resolving the
   label's `1 August 1996` claim versus the SIS's `15 June 2000` citation;
2. an unambiguous, source-defined interpretation of the observed File Label
   word `1020615`, including why it corresponds (or does not correspond) to
   the independently labelled creation date;
3. an explicit sub-second relation between a Doppler compression-midpoint time
   tag and the file/Data Summary start and stop timestamps that predicts the
   observed 500-ms endpoint offsets; and
4. a statement applicable to the declared Format ID 2, not a format-ID-1,
   TDF, later-only, or otherwise unlinked example.

If any criterion fails, conflicts, or is absent, the result remains
`STRUCTURE_PARTIAL`; the unknown transformation is recorded and no source is
silently preferred. A structural resolution would only make this file a
format-validation fixture. It cannot establish a propagation measurement or
authorize a Cassini solar-delay residual.

## Prohibited in this loop

No standard-model calculation, SDT calculation, parameter fit, residual,
ephemeris, station/clock/media correction, solar geometry, or empirical claim
is permitted. This loop audits binary documentation only; the retrieved files
are technical documentation, not experimental or observational evidence.
