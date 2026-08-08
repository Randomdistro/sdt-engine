# GOM20 GPS Clock Anchor — Source Manifest

**Retrieved:** 2026-08-07  
**Rule:** an artifact's evidentiary class below is binding. None of the files in
this manifest is an uncorrected, time-tagged satellite-clock comparison with a
published uncertainty budget. No file is therefore eligible by itself to set
the GOM20 physical-model verdict.

| local file | bytes | SHA-256 | source | evidentiary class | permitted use |
|---|---:|---|---|---|---|
| `raw/nist_putting_einstein_to_the_test.html` | 92,312 | `1ba074908c7261f2f515edd96505c06f8640836ff47ac5f23902a8cf83220baf` | NIST, “Putting Einstein to the Test” | `EXPLANATORY_SECONDARY` | documents the familiar rounded 7/45/38 microseconds-per-day statement; not a data point or uncertainty budget |
| `raw/is_gps_200n.pdf` | 3,338,120 | `54ec544bfe7e6acd97daaa1de0ca248e5abec6b418f23c1a69991e5c7bcf749a` | U.S. Coast Guard NAVCEN, IS-GPS-200N | `ENGINEERING_CONFIGURATION` | identifies the broadcast/interface frequency offset; never substitute for a measured uncorrected clock rate |
| `raw/nasa_2012_gnss_relativity_introduction.pdf` | 4,082,392 | `402b87a7193e929ec5316e446ada53aa2d7c9daa60877a6717605034318b109b` | NASA NTRS 20120002319 | `EXPLANATORY_ENGINEERING` | checks the configuration interpretation and eccentricity-correction context; not a direct observation table |
| `raw/nasa_1980_navstar4_metadata.json` | 4,182 | `0255b566bca1011144ed8b76afa94489bdf93842f2de0bc78ad0d643697cb467` | NASA NTRS 19800020608 metadata | `MODEL_PROCESSED_OBSERVATION` | establishes that per-pass clock offsets existed but were formed using stated correction paths; metadata only, no series or uncertainty table retrieved |

## Source URLs

- `nist_putting_einstein_to_the_test.html`: <https://www.nist.gov/atomic-clocks/a-powerful-tool-for-science/putting-einstein-test>
- `is_gps_200n.pdf`: <https://www.navcen.uscg.gov/sites/default/files/pdf/gps/IS-GPS-200N.pdf>
- `nasa_2012_gnss_relativity_introduction.pdf`: <https://ntrs.nasa.gov/api/citations/20120002319/downloads/20120002319.pdf>
- `nasa_1980_navstar4_metadata.json`: <https://ntrs.nasa.gov/api/citations/19800020608>

## Retrieval exception

The pre-registered NIST common-view-calibration URL was attempted twice on
2026-08-07: `Invoke-WebRequest` ended with an unexpected closed connection, and
an independent `curl --location --retry 2` returned HTTP 404. No replacement
URL was substituted and no claim relies on that unavailable page.

## Provenance boundary

Browser search and page inspection occurred before the files were frozen, but
no numerical datum, fit, or evidentiary classification from that inspection is
used. The audit uses only the checksummed local copies above. The first three
files are documentation, not observational data. The fourth describes an
observation-derived analysis but explicitly declares its corrections and lacks
the required numerical record; it remains `MODEL_PROCESSED_OBSERVATION`.
