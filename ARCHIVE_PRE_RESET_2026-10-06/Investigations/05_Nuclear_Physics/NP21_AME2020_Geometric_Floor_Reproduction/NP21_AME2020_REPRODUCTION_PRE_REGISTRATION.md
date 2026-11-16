# NP21 AME2020 Geometric-Floor Reproduction - Pre-Registration

**Date:** 2026-08-09
**Objective:** independently reproduce or overturn NP21's narrow claim that the
zero-fit geometric resistance functional places its floor in the Fe/Ni window.

## Trigger and provenance gate

The published NP21 instrument names
`Investigations/04_Atomic_Physics_and_Spectroscopy/APS03_Universal_Drafting_Crossover/mass_1.mas20.txt`,
while the registered AME2020 source is `Datasets/nuclear/AME2020_mass_excess.txt`.
No numerical nuclear value may be parsed until a byte-level duplicate check
passes. The canonical registered source is:

| Source | SHA-256 | Class |
|---|---|---|
| `Datasets/nuclear/AME2020_mass_excess.txt` | `e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307` | AME2020 evaluated experimental mass target; IAEA/AMDC `mass_1.mas20` |

The audit will first hash the legacy duplicate and the frozen NP21 instrument.
If the duplicate is absent or differs from the canonical hash, return
`PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION`; do not select one table or
reconcile values by hand.

## Fixed model calculation

After the duplicate gate passes, evaluate only the published zero-fit Run-G
functional over the frozen `sdt::nuclear::natural_basis` scan domain:

```text
R_tilde/A = 6 A^(-1/3)
          + (1/137.035999084) Z(Z-1) A^(-4/3)
          + (n_t-n_d)^2 A^(-2)
n_d = 3Z - A - 2;  n_t = A - 2Z
```

`a_S = 6`, `a_C = alpha`, and `a_A = 1` are frozen hypothesis inputs copied
from NP21's declared geometric run. There is no fit, coefficient sweep,
exponent change, mass-formula input, or standard-framework rejection criterion.
The AME table supplies an experimental target and a rank-comparison diagnostic;
it does not set the floor calculation.

## Pre-committed decision

| Condition | Classification |
|---|---|
| Source hashes pass; floor A is in `[54, 64]` | `GEOMETRIC_FLOOR_SURVIVES_THIS_REPRODUCTION` |
| Source hashes pass; floor A is outside `[54, 64]` | `GEOMETRIC_FLOOR_KILL_CONFIRMED` |
| Duplicate or frozen-source hash fails | `PROVENANCE_CONFLICT_NO_NUMERIC_REPRODUCTION` |
| Parser/domain failure after hashes pass | `INSTRUMENT_OR_DOMAIN_FAILURE` |

The first two labels adjudicate only this fixed zero-fit functional. They do not
accept or reject SDT as a whole. A fitted coefficient route is explicitly out
of scope and remains `CALIBRATED` regardless of its numerical output.

## Required audit outputs

1. Hashes, source path, byte count, and duplicate-equality result before parse.
2. Parsed AME row count, scan-domain count, alpha-valid row count, and Fe-56 /
   Ni-62 target availability.
3. Zero-fit floor `(Z,A)`, distance from A=56, and whether it lies in the
   pre-committed `[54,64]` window.
4. Spearman diagnostic between `-R_tilde/A` and AME `B/A`, clearly labelled
   diagnostic only.
5. A record of any audit-instrument fault and its repair before final result.

## Frozen implementation sources

The pre-parse duplicate check passed on 2026-08-09. The legacy file is exactly
the canonical registered AME file, so the path split is a source-hygiene defect
but not a numerical-data conflict for this run.

| Source | SHA-256 | Bytes | Role |
|---|---|---:|---|
| Legacy AME duplicate | `e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307` | 472,648 | Equality-gated duplicate only |
| NP21 published instrument | `38aeee91edcca845253a6c039eb270da3bf3d358f913aeda26bf397e75b8827f` | 21,592 | Frozen hypothesis implementation reference |
| `Engine/include/sdt/nuclear.hpp` | `606f2fdf2e86a05500d9b76d79964e652870eb401fc470da033a6c9b4ce04791` | 45,938 | Frozen natural-basis scan domain |

The new audit independently re-parses the canonical AME table and independently
evaluates the fixed formula. It does not call NP21's fit routine or write to
the historical NP21 result files.
