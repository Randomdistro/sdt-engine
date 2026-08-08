# NP21 AME2020 Geometric-Floor Reproduction - Results

**Date:** 2026-08-09
**Classification:** `GEOMETRIC_FLOOR_KILL_CONFIRMED`.
**Scope:** the published zero-fit NP21 geometric functional only.
**Instrument:** `np21_ame2020_geometric_floor_audit.py`
(`bf47a0d19b390010c09ffc26089b14face32fd4bfdc33043a35aecf50573a70d`).
**Result:** `np21_ame2020_audit_results.json`
(`68dd6c78c71fe73691fbf5df7719e2a9043ca2219995db50ffecd6e7e56198fb`).

## Source and method audit

All four pre-registered hashes pass. The historical NP21 code reads an AME2020
duplicate outside `Datasets/`, but its 472,648 bytes hash exactly to the
canonical manifest-registered AME2020 table. This is a source-path hygiene
defect, not a numeric conflict in this reproduction. The audit therefore parses
only the canonical table and leaves the historical instrument and its outputs
unchanged.

The AME2020 dataset is an evaluated experimental mass compilation rather than
individual raw instrument records. It supplies the empirical Fe/Ni target and
a rank diagnostic; it does not set the zero-fit floor calculation. The scan
uses the frozen `natural_basis` in `Engine/include/sdt/nuclear.hpp` and the
pre-registered coefficients `a_S=6`, `a_C=1/137.035999084`, and `a_A=1`.
No coefficient fitting, exponent adjustment, or semi-empirical mass-formula
term entered the calculation.

## Reproduction result

| Check | Result |
|---|---|
| Canonical/legacy AME duplicate equality | PASS |
| AME binding-per-nucleon rows | 3,554 |
| Frozen natural-basis rows | 287 |
| Alpha-valid observed scan rows | 284 |
| Fe-56 / Ni-62 available | 8.7903563 / 8.7945555 MeV per nucleon |
| Zero-fit floor | U-238 (`Z=92`, `A=238`) |
| Distance from Fe-56 | 182 mass units |
| Pre-registered Fe/Ni window `[54,64]` | FAIL |
| Spearman(`-R_tilde/A`, AME `B/A`) | -0.5739768 |

The independently implemented result exactly matches the historical NP21
zero-fit result (U-238 and approximately -0.574) while avoiding its duplicate
path and its fitted branch.

## Falsification statement

The claim that the fixed geometric coefficients place the resistance floor in
the empirically observed Fe/Ni region is falsified. The fixed functional has
the wrong floor and the wrong rank direction on the registered AME2020 target.
This is a narrow result: it does not reject SDT as a whole, and it does not
license fitting the coefficient ratio until the floor moves to iron.

The source of the model error is specific: the functional provides no native
derivation of the spread-to-surface weight ratio. The observed region can be
reached only by an excluded fitted-ratio path in historical NP21; that route is
calibrated, not a repair of the zero-fit claim.

## Source-hygiene repair

The only identified implementation defect is the legacy AME path outside the
canonical dataset root. It was contained by byte equality for this audit. Do
not silently rewrite the historical instrument, because that would alter its
provenance. A future maintenance patch may point it to
`Datasets/nuclear/AME2020_mass_excess.txt` after preserving the current hash
and verifying a byte-identical rerun.

## Next gate

The geometric-floor claim is closed unless a new coefficient-ratio derivation
is supplied before viewing the AME target. Any proposed derivation must state
units, geometry, free-parameter count, and a no-fit rule, then be tested in a
new pre-registered hold-out protocol. Re-running a fitted coefficient search
would not reopen this result.
