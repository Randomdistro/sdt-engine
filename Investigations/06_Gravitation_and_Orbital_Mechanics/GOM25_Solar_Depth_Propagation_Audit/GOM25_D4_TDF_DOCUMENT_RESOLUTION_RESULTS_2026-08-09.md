# GOM25 D4 TDF Document-Resolution Results - 2026-08-09

**Decision:** `STRUCTURE_PARTIAL / PENDING_RECONSTRUCTION`; observables remain
`UNDECODED`.  
**Evidence class:** technical interface documentation and binary structural
metadata only; no empirical or theory conclusion.

## Frozen sources and coverage finding

| Source | SHA-256 | Result |
|---|---|---|
| `raw/collection_dsn_trk-2-25.xml` | `bf142b66ceeb058a9d074dd8d0cbf9ebea44a9b88cdfda7b39d4ed248cdc839b` | PDS collection declares eight members but does not enumerate their IDs |
| `raw/collection_dsn_trk-2-25.csv` | `ae10d3e8a41896bb2d176e76c8af2a1fbe0452b3f0930971aa7cea522b5f1522` | Lists only 1977, 1986, 1988, 1996, unpack-guide, and example products; no 1998 member |
| `raw/dsn_trk-2-25.1996-07-31.pdf` | `3d47f1372c76a73d1bed60f13403a402f7ded54984cf9bad53855bbfe4946dce` | Candidate grammar file; text extraction is unavailable because this is a scan |
| `raw/dsn_trk-2-25.1996-07-31.xml` | `322d8b1c46518987bce9af63827c48115e09806c1f9701137fd06342139e82d6` | PDS label identifies an 1988 document reissued after reformatting |

The official PDS inventory does not contain the 15 December 1998 TRK-2-25
revision cited by the frozen Cassini SIS. This is precisely
`PDS_COLLECTION_INCOMPLETE_FOR_SIS_1998_CITATION`; it is not proof that JPL
never issued that revision.

## Source consistency audit

The 1996 candidate's PDS label says it documents an initial 1986 release
reissued in 1988 and reissued after reformatting on 1996-07-31. The same label's
modification history instead says the reformatting occurred before a
1996-10-15 release, while its Document section retains 1988-10-15 as the
publication date. The file is therefore a provenance-preserved historical
source but not an unambiguous effective grammar for the 2002 Cassini TDF.

This falsifies the tempting but invalid repair "the 1996 PDS file matches raw
format 8, so it must be the right decoder." No source in the frozen set ties
that document to the 2002 file, explains why the paired label requires `2048`
for its File Identification and Transponder headers, or supplies the missing
data-ID fixture. The 1996 candidate is rejected for grammar selection.

## Unchanged structural re-run

The existing `gom25_d4_tdf_census.py` was compiled and rerun without a source
or grammar change. The exact pre-registered outcome was reproduced:

| Check | Result |
|---|---|
| TDF and label SHA-256 | `PASS` |
| 18,668,160-byte framing and 2,315 physical blocks | `PASS` |
| Nonzero type declarations | `PASS`; types 10, 30, 90, and 91 are declared |
| File-ID creation timestamp | `PASS`; 2002-166T02:25:37 |
| Header format pairs | `FAIL`; type 10 and type 30 are raw `8` where the label expects `2048` |
| Tracking record format | raw `8`, consistent with the paired-label post-1997 rule |
| File-ID data-ID mapping | `UNADJUDICATED` |
| Observable values | `UNDECODED` |
| Classification | `STRUCTURE_PARTIAL` |

The first post-run shell assertion was too strict about output line boundaries:
it expected a standalone `size=PASS`, although the census writes it on a
combined line. This was an audit-harness assertion error, not a source or data
result. The corrected substring assertion passed all ten expected conditions.
No parser or data file was altered.

## Corrected next gate

Before decoding a TDF observable, locate a source that is explicitly applicable
to the 1998 SIS citation or the 2002 ODE-produced Cassini file and that provides
both the header-format transition and a reproducible file-ID data-ID fixture.
Pre-register, checksum, and manifest it before parsing. If the 1998 source
cannot be recovered, preserve `PDS_COLLECTION_INCOMPLETE_FOR_SIS_1998_CITATION`
and redirect physical falsification to an independently decodable observational
channel; do not manufacture a header convention from the desired result.
