# GOM25 D4b ODF Document-Resolution Results - 2026-08-09

**Decision:** `STRUCTURE_PARTIAL`; observables remain `UNDECODED`.  
**Evidence class:** technical format documentation only. No experimental or
observational conclusion is made in this iteration.

## Frozen source set

| Source | SHA-256 | Relevant provenance |
|---|---|---|
| `raw/dsn_trk-2-18.1996-08-15.pdf` | `d9f1ad6b3b2e3a57d77dc45929a06a6f73a2c14131fa0d2e2e66ae2c7fcf5e2c` | Official PDS Change 1 document; cover and PDS label say reissued 15 August 1996 |
| `raw/dsn_trk-2-18.1996-08-15.xml` | `b3f0632343994421aeac1436130544bd1c0e97d3ade16e5f16004cc09a2367d9` | PDS4 label for the 1996 Change 1 document |
| `raw/dsn_trk-2-18.2000-06-15.pdf` | `59c45204b231d5c08e8918038a4c605348d9722487664cf73325050843c77c46` | Official PDS Change 3 document, the date cited by the frozen Cassini SIS |
| `raw/dsn_trk-2-18.2000-06-15.xml` | `56adae070cad6304530a347d3fdc93e9f13d8342188f2e512b4490988bc2f8c5` | PDS4 label for the 2000 Change 3 document |

All four sources were pre-registered, downloaded, SHA-256 verified, and added
to `Datasets/solar_propagation_2026-08/MANIFEST.md` before body text was read.
The official directory listing had been seen during discovery; that ordering
deviation and its strict non-observable scope are retained in the manifest.

## Revision audit

The 1996 PDS label identifies Change 1, issued 1996-08-15. The scanned cover
and change log also say 15 August 1996; the change log describes Change 1 as a
document reformat. The 1996 PDS label says the original issue was 1982-06-15,
whereas the scanned cover says 1983-06-15. This internal provenance conflict is
retained rather than normalized because it demonstrates that a revision date
cannot be inferred from a filename alone.

The frozen Cassini ODF label says "version of 1 August 1996." The frozen
Cassini SIS cites TRK-2-18 dated 15 June 2000 and states that April 1997
introduced significant ODF changes. Both candidate documents define the
observed Orbit Data Format ID as `2`, but the sources do not explicitly state
which one governed this individual 2002 ODE V2.0 file. Criterion 1 of the
pre-registration therefore fails.

## Encoding checks

| Pre-registered criterion | Source evidence | Result |
|---|---|---|
| Identify the applicable revision | 1996 Change 1 date differs from the label by 14 days; the same archive's SIS cites 2000 Change 3 | `FAIL` |
| Explain File Label word `1020615` | Both revisions describe the I32 File Creation Date as `YYMMDD`; neither authorizes a leading `1`, a three-digit year, or an alternate radix | `FAIL` |
| Explain the 500-ms endpoint offsets | Both revisions define a Doppler tag as the midpoint of the interval `ti` to `tj`. Change 3 defines Data Summary fields as first/last sample time, but neither source states whether those fields are interval endpoints, midpoint tags, or a distinct summary convention | `FAIL` |
| Apply the format grammar to the sample | Both revisions list Orbit Data record time as integer seconds plus fractional milliseconds and specify Format ID 2 | `PASS`, but insufficient to remove the block |

The retained raw structural facts are unchanged: File Label date word `1020615`;
Data Summary bounds `2002-06-06T20:41:30Z` and `2002-06-06T22:45:36Z`; first and
last Orbit Data tags respectively 500 ms later. These are metadata/time-tag
facts only. No numeric observable field was read.

## Re-run and validation correction

`python -m py_compile gom25_d4b_odf_structure.py` and the unchanged structure
instrument both passed. The instrument again returned `STRUCTURE_PARTIAL` and
`UNDECODED`, with exactly two failed structure checks:
`data_summary_time_bounds_match` and `time_tags_within_label_bounds`.

The first post-run shell assertion failed because the audit command queried a
nonexistent JSON member named `checks`; the result uses `structure_checks`.
That validator error was identified as an audit-harness error, not a data or
model result. The corrected assertion passed and required exactly the two
pre-registered failed checks. No source code or decoded measurement changed.

## Corrected next gate

Before any ODF observable value is decoded, freeze a source applicable to ODE
V2.0 or a provenance-preserved binary fixture that explicitly maps the creation
date word and states the endpoint-to-midpoint relation. The source must be
pre-registered, checksum-manifested before parsing, and must not be selected
because it happens to make the conflict disappear. A resolved ODF structure
still would not supply a non-conjunction control, a solar geometry solution, or
a Cassini propagation residual.
