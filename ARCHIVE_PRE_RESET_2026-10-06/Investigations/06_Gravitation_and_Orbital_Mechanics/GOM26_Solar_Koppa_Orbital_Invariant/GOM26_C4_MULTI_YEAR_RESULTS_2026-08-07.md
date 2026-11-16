# GOM26 C4 Multi-Year Hold-Out Results — 2026-08-07

**Status:** `COMPATIBLE` with the pre-registered C4 threshold; formal
invariant-construction check only. It does not earn empirical confirmation.

## Inputs and integrity

The source-acceptance boundary and caveat are in
`GOM26_C4_MULTI_YEAR_SOURCE_ACCEPTANCE_2026-08-07.md`. Before parsing, the
2024 file's SHA-256 was checked against
`c194718c09f3ed4d18e4c3397226f2304b1d1a9c9aeb15cc2289e0d3ea5c319f`.
Its header identifies EMB(3) relative to Sun(10), DE441, 2024-01-01 to
2025-01-01, at 14-day cadence. Both calibration and hold-out contained 27
parser-admissible rows.

The state vectors are `MODEL_PROCESSED_OBSERVATION`, not raw observations. The
pre-registration also defines Keplerian two-body energy conservation as a
kinematic premise. Hence this run tests the stability of that construction on a
new interval; it does not test SDT against a competitor framework or establish
an empirical physical prediction.

## Frozen decision rules and result

| gate | registered rule | result | status |
|---|---|---:|---|
| Instrument A | near-circular `mu` relative error `< 1e-8`; reconstructed CV `< 1e-6` | `3.318e-13`; `0` | PASS |
| Instrument B | eccentric `mu` relative error `< 1e-6`; reconstructed CV `< 1e-6` | `6.173e-16`; `4.384e-08` | PASS |
| C1/C2 calibration | pair fraction `>= 0.5`; reconstructed CV `< 1e-3` | `1.0`; `1.059332e-05` | PASS |
| C4 multi-year | `|Δkoppa|/koppa < 1e-3` | `3.508332e-04` | COMPATIBLE |
| C3 spectral | residual within registered 2σ rule | `1.8064 m/s < 12.0001 m/s` | COMPATIBLE / UNADJUDICATED |

The C4 values are `koppa_cal = 1476.354317 m` and
`koppa_hold = 1476.872271 m`. Their nonzero difference is retained; the result
passes only the originally registered `1e-3` threshold. No post-result
tightening or retuning is permitted.

The C3 comparison retains its existing limitation: the HARPS `638 ± 6 m/s`
summary is an observational comparator with laboratory-wavelength and
photospheric-nuisance dependencies, while the model construction is not an
independent measurement. It remains `UNADJUDICATED`.

## Instrument error and repair

The first execution printed `rows used for recon stats = 0 (of 27)` for each
sample. Inspection found a hard-coded zero in the investigation reporting
lambda. The calculation itself already iterated over all parsed rows and the
gate used those vectors; only the printed count was wrong. The display was
repaired to print the passed `nrows` value, then the source was recompiled and
the complete run repeated. The accepted log prints `27 (of 27)` for both
samples and reproduces all numerical gate values above.

The Visual Studio developer batch script also emitted a non-fatal
`vswhere.exe` lookup message after compilation. The compiler and executable
both exited with status zero; the rerun log is retained at
`.audit-tmp/gom26_c4_2024_run.txt`. This environment message did not alter the
source hash, executable exit status, or reported result.

## Cascade and next discriminator

The earlier `INTRA_YEAR` fallback caveat is narrowed: C4 now has a separate
2024 hold-out under the stated provenance limitation. Canonical code and laws
remain unchanged. The actual independent solar-propagation discriminator stays
blocked on absolute deflection or tracking-residual reconstruction:

1. stage and reduce the fixed public BF080 VLBA products for an absolute
   deflection-versus-impact-parameter table; or
2. complete TRK-2-25 decoding, geometry, and clock reconstruction for a
   Cassini residual.

Neither task may substitute a fitted PPN coefficient or a competitor-model
residual as an SDT target.
