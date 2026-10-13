# APS10 — First Ionisation Energies from Occlusion Pressure

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> rows B29-original and B43; the standing B06 gap in the engine suite). **Author:** J. C.
> Harvey, Melbourne. Gateways binding.

## Target

First ionisation energies He→Ne (and beyond) from SDT geometry — the suite's oldest open
tally. The current B06 rows run 6%–440% error on empirical Slater screening, flagged PENDING
since the 2026-07 repair; no native derivation exists anywhere in the corpus (verified
2026-07-29). Measured anchors: NIST ionisation tables.

## SDT footing

The intended route is the geometric-void electron model: seats are voids in the shell wake
(L14; octet as void-filling), and the ionisation energy is the cost of lifting a rider out of
its void against the residual occlusion of the core-plus-shell configuration. Existing
corpus: APS01 (emergent shell capacities from the measured terrain — the closest earned
result), APS02 (drag factor, monotone in occupancy), CH03 (valence tally, capped), NP30
(the invariant ladder that must price the exit route). The original tracking sheet's
tolerance ("median ≤ 15%, max ≤ 40%") is adopted as the opening gate — a first native pass
beating Slater's failures would already be progress; the 5% suite gate is the destination.

## Pre-registration skeleton (complete before any tool)

- Question: does void-geometry seat pricing produce IE₁ across He→Ne with median error ≤ 15%
  and no sign inversions in the period trends, forward, zero fitted screening constants?
- Rejection criterion (populated): median > 15%, or period-trend inversions (the B06 rows
  show the hydrogenic form inverts B→C ordering — a populated failure the void model must
  clear).
- Anchors: NIST IE₁, Z = 2–10 minimum.
- Tolerance: opening gate 15% median / 40% max; suite tally at 5%.

## Benchmark linkage

Fills suite rows B06 (nine PENDING tallies) · catalogue rows B29/B43 · the highest-value
open tally in the suite.

## Pre-registration (2026-10-03, before the instrument exists)

**Scope correction.** The seed states that no native derivation exists in the corpus. APS14
(`APS14_ASSESSMENT.md`, 2026-08-15) computes He–Ne first ionisation with the engine's
`sdt::laws::atomic::dodecardinal::first_ionisation_eV`. This run therefore re-verifies that
engine closure against APS10's own gates and records APS10's disposition. It is not a new
derivation and not a blind prediction: the APS14 assessment records that the coefficient
forms were isolated post-freeze against the B06 comparison rows, so the label ceiling is
COMPUTED.

**Instrument.** `first_ionisation_eV(Z)` for Z = 2–10, called as shipped. Z = 11–18 is not
attempted: `solve_state` rejects more than ten electrons, so the closure's domain ends at Ne
(APS14 records the extension as open).

**Anchor.** Measured first ionisation energies, `APS14_Nuclear_Z_Celestial_Atom/data/
ionisation.csv` (step = 1), compiled from NIST/CRC into `Datasets/nuclear/ionisation_energies.json`.
`Datasets/nuclear/NIST_ionisation_snapshot.txt` is not used: it contains a NIST "Invalid
Checkbox Setting" error page, not data.

**Instrument validation (before scoring).** The solver's one-electron limits against closed
forms: `solve_state(1,1)` = −Ry (−13.6057 eV) and `solve_state(2,1)` = −4 Ry (−54.4228 eV),
each to 1e-6 relative with `converged = true`; maximum force residual below 1e-8 for every
state used in the scored range.

**Gates (single pass, Z = 2–10).** Opening gate from the seed: median error ≤ 15%, maximum
≤ 40%. Period trend: the sign of IE₁(Z+1) − IE₁(Z) matches the measured sign for all nine
consecutive pairs, including the Be→B and N→O decreases. Suite destination, reported and not
gated: median and maximum against 5%.

**Rejection criterion (populated).** Met if the median exceeds 15%, the maximum exceeds 40%,
or any consecutive-pair sign disagrees with measurement. The Slater rows in B06 (6%–440%,
B→C inversion) show this class is populated.

**Labels.** COMPUTED (coefficient forms isolated against B06 rows; the 45 higher sequential
ionisations in APS14 were not used in that isolation). Provenance: NATIVE closure geometry.
Discrimination: not applicable to a single-framework fit quality.
