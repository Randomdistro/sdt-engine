# GOM25 D4 TDF Document-Resolution Pre-Registration

**Date:** 2026-08-09  
**Status before retrieval:** `STRUCTURE_PARTIAL / PENDING_RECONSTRUCTION`;
observable values remain `UNDECODED`.

## Trigger and error origin

The frozen Cassini TDF label says that File Identification and Transponder
record formats must be `2048` after 1997-04-15, but the frozen 2002 raw file
contains `8` in both records. Its Tracking Data records also contain `8`, which
does agree with the label's post-1997 tracking-record rule. The already frozen
TDF unpacking guide supplies a File Identification example using `8`.

The archive SIS cites TRK-2-25 dated 15 December 1998, but the official PDS
TRK-2-25 collection directory exposes a 1996-07-31 document and no listed 1998
document. The revision needed to reconcile the two header rules is therefore
not currently frozen. The data-ID byte field also lacks a source-defined mapping
to the PDS `DATA_SET_ID`.

## Candidate sources, pre-registered before retrieval

Only these official PDS technical-document products may be fetched in this
loop:

1. `collection_dsn_trk-2-25.xml`, solely to freeze the PDS collection inventory;
2. `dsn_trk-2-25.1996-07-31.pdf` and its PDS XML label, solely as a dated
   grammar candidate.

All candidates are in
`https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/dsn_trk-2-25/`.
The directory listing was inspected during source discovery before this
pre-registration. Discovery revealed only filenames, stated revision dates, and
byte counts; it did not open a document body or read any raw TDF observable.

## Fixed sequence and scope

1. Download byte copies only to `Datasets/solar_propagation_2026-08/raw/`.
2. SHA-256 checksum and manifest each file before opening its body.
3. Verify the recorded hash immediately before parsing.
4. Inspect only revision/effective-date statements, File Identification and
   Transponder record-format rules, Tracking Data format rules, record types,
   data-ID encoding, and explicit fixture instructions.
5. Re-run `gom25_d4_tdf_census.py` unchanged only after the source outcome is
   recorded. The script must not decode, export, summarize, or compare a
   Doppler, range, frequency, phase, timing residual, or theory prediction.

## Pre-committed decision rule

`READY_FOR_OBSERVABLE_EXTRACTION` is unavailable unless the frozen source set
unambiguously establishes all of the following for the 2002 sample:

1. the applicable TRK-2-25/SFOC-NAV-2-25 revision, including why the SIS cites
   1998 while the PDS inventory may not contain it;
2. the source-defined File Identification and Transponder format value and its
   compatibility with the observed raw value `8` and the file creation date;
3. the record-type and bit-offset grammar used by the census; and
4. the 14-byte file-ID data-ID encoding plus a reproducible expected value, or
   a provenance-preserved binary fixture that independently validates it.

If any condition is absent or conflicts, retain `STRUCTURE_PARTIAL` and record
the source gap. A 1996 source cannot be treated as a 1998 or 2002 source merely
because it decodes the observed header value. This is a decoder-documentation
audit, not an empirical test; no physical model or reference framework may be
used to choose a grammar.
