# GOM25 D4 TDF Document-Resolution Amendment 01

**Date:** 2026-08-09  
**Trigger:** the pre-registered PDS collection XML reports eight member products
but does not name their logical identifiers.

## Why the amendment is required

The frozen PDS label for `dsn_trk-2-25.1996-07-31.pdf` identifies an 1988
document reissued after reformatting. It also contains an internal reformat-date
conflict: its citation and document descriptions say 1996-07-31, while a
modification-history entry says 1996-10-15. This candidate cannot by itself
establish whether the SIS-cited 1998 revision is absent from the PDS collection.

An official directory listing was seen during discovery, but its product list
must be frozen as a source artifact before absence from that collection is used
as an audit finding.

## Added candidate source

Retrieve only `collection_dsn_trk-2-25.csv` from the same official PDS
collection directory. Download, SHA-256 checksum, and add it to the manifest
before parsing. The CSV may establish the members of this PDS collection only;
it cannot prove that no 1998 revision exists outside PDS.

## Revised decision boundary

- If the frozen CSV includes a 1998 TRK-2-25 member, retain the candidate and
  pre-register a separate retrieval of its file and label.
- If it does not, report only `PDS_COLLECTION_INCOMPLETE_FOR_SIS_1998_CITATION`.
  Do not convert that absence into proof that JPL never issued the revision.
- In either outcome, do not use the reformatted 1988 source to select a 2002
  grammar without an explicit applicability statement and fixture.

No TDF observable, physical calculation, or theory comparison is authorized by
this amendment.
