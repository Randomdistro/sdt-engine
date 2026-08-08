# GOM26 C4 Multi-Year Source Acceptance — 2026-08-07

**Purpose:** accept a discovered 2024 D1-hold candidate only for the existing
pre-registered GOM26 C4 formal hold-out test.

## Discovery boundary

The original GOM26 pre-registration already specifies D1-hold as 2024
Earth-Moon-barycenter vectors relative to the Sun, with the C4 threshold fixed
at `|Δkoppa|/koppa < 1e-3`. At this audit step, a file with that intended name
was present on disk while the manifest still labelled it absent.

Before this acceptance record, the audit inspected only its container-level
provenance: SHA-256, Horizons header, date span, target, center, frame, units,
and the count of records between `$$SOE` and `$$EOE`. No state-vector component,
derived `mu`, `koppa`, or target result was read.

## Frozen candidate

| field | value |
|---|---|
| file | `Datasets/solar_propagation_2026-08/raw/jpl_horizons_emb_sun_vectors_2024.csv` |
| bytes | 10,537 |
| SHA-256 | `c194718c09f3ed4d18e4c3397226f2304b1d1a9c9aeb15cc2289e0d3ea5c319f` |
| target / center | Earth-Moon Barycenter (3) / Sun (10) |
| source / frame | DE441 / ecliptic J2000 geometric Cartesian states |
| interval / cadence | 2024-01-01 to 2025-01-01 TDB / 20,160 min |
| units / state table | km-s / position and velocity |
| structural count | 27 records between `$$SOE` and `$$EOE` |

## Admissibility and limitation

The header rules out the previously retained wrong-center 2024 file, which has
Earth (399) as center. Its SHA-256 also differs from the 2025 calibration file.
The candidate is admissible for the C4 formal stability check because it
matches the already frozen target, center, interval, cadence, and parser
contract.

Its original transfer actor and full request URL are not retained locally.
Accordingly the file is classified `MODEL_PROCESSED_OBSERVATION`, not raw
observation; C4 can assess the stated invariant construction but cannot earn an
independent empirical confirmation. The subsequent calculation must verify the
checksum before parsing and retain `PENDING_PROVENANCE` if it changes.
