# RUN_LOG — SDT_Loading_EC_Reseating_Neutrino_Coupling

Append-only. Entries are dated; an adjustment is an `ADJ-###` entry.

## 2026-10-03 — execution authorisation and scope

The Operator's message of 2026-10-03 ("run this first, tell me if this is a decent investigative
format") is taken as the separate execution instruction that the specification's header
requires. The specification is frozen verbatim as `PROMPT.md` (hash in `SOURCE_FREEZE.json`).

Scope executed this session: **Phase 0 only**, plus an assessment of the specification's format
(`PHASE0_ASSESSMENT.md`). Phases 1–6 are not started. Reason, recorded before the assessment:
the programme is estimated at three to five weeks, and Phase 0 shows that Phases 2–4 each begin
from a law that does not exist in the corpus (see the ledger rows D44–D48).

## Pre-run commitment block

```text
Investigation:
SDT_Loading_EC_Reseating_Neutrino_Coupling

Primary hypothesis:
A native SDT response law couples loading and electron connectivity
to admissible nuclear conversion, reseating, and carrier emission.

New fitted-parameter budget:
0.

Existing calibration:
NSEQ17 counter-circulation coefficient, CALIBRATED(1)
  (traction-gear-engine.js:894; ledger D41); reused unchanged;
  H-2 CALIBRATED(8), H-3 CALIBRATED(9), He-3 CALIBRATED(9) against binding and magnetic targets.
  Affects: any binding-energy or magnetic-moment prediction (Phases 4 and 6).
APS14 dodecardinal coefficient forms, COMPUTED with post-freeze isolation against the B06
  first-ionisation rows (laws.hpp:1919; ledger D54).
  Affects: Phase 1 atomic comparisons (target-exposed).
P_conv magnitude inherits the observed R_CMB (ledger D16, D20).
  Affects: every Law-IV resistance and every loading magnitude (Phases 1-5).

Canonical-source modifications:
0.

Source-data modifications:
0.

Unclassified load-bearing dependencies:
0.            [Gate not met at Phase 0: three rows untraced, see "Gate evaluation".]

Inventory residual:
Exactly 0.

Contact-slip tolerance:
1e-10, normalised.

Analytic limiting-identity tolerance:
1e-10 relative, with an explicit absolute tolerance near zero.

Closed-domain energy and momentum residual:
1e-6 or smaller, decreasing under refinement.

Stability-growth convergence:
Less than 5% change across three refinement levels.

Measured comparison:
Combined-uncertainty residual, with correlations and systematic errors retained.

Capture-rate gate:
No empirical dimensional rate multiplier.

Blindness:
Declare historical target exposure.
Seal new hold-out predictions before comparison access.

Parent-claim gate:
No full coupling verdict while a necessary mechanism remains OPEN.

Forbidden adjustments:
Target tuning, tolerance widening, inserted rate constants,
measured binding-energy substitution, edge pruning,
silent state redefinition, and retrospective blindness.
```

## Historical target exposure (declared before any Phase 1 work)

The repository already contains, and earlier work in it has compared against: hydrogen and
hydrogenlike spectra and the Rydberg constant (APS01); NIST first-ionisation energies for He–Ne and
higher sequential ionisations (APS14, APS10); binding energies and magnetic moments of H-2, H-3 and
He-3 (NSEQ17, calibrated); N = 82 fission-fragment structure (Audits/atomica_n82_fission_stocktake.md);
the free-neutron lifetime and Q_β (NP11, NP20); and the Be-7 electron-capture rate question (NP18).
None of these can be a blind comparison for this investigation. Phase 6 hold-out data must be chosen
from outside this set and sealed before access.

## Phase 0 execution record

Commands: `git rev-parse HEAD`, `git status --porcelain`, `sha256sum` of every audited file (generator
`phase0_make_freeze.py`), `cl` banner for the toolchain, direct reads of the sources listed in the
specification, and `phase0_candidate_checks.py` (output `phase0_candidate_checks.txt`).

- **P0-1 Baseline.** HEAD 3867c76 on branch `origin-rule-sweep-2026-10-03` (the branch changed during
  the session; an earlier commit 532fdb5 was made on `main`). 32 dirty entries, all of them
  uncommitted records and tools from the 2026-10-03 session plus this directory. No entry in `Engine/`
  or `Release/`. Toolchain MSVC 19.44.35223 x64, which matches the manifest's.
- **P0-2 Qualification currency.** `QUALIFICATION_MANIFEST.json` (generated 2026-08-18) records
  `laws_sha256 = b4212524…`; the current `laws.hpp` is `da72fc92…`. The recorded runtime, parity and
  benchmark gates are not associated with current code. Status STALE (ledger D52).
- **P0-3 The candidate wavelength relation is the Rydberg formula.** With r_n = n²a₀ and v_n = αc/n,
  k_R = (c/v)√(R/r) = 1/α for every n when R = a₀, so Om = R/k_R² = α²a₀ = r_e, and
  λ = 4πk_R r_l r_u/(r_u − r_l) reproduces 1/λ = R∞(1/n_l² − 1/n_u²) with ratio 1.000000000 for
  five hydrogen transitions (1/(4πk_R a₀) = α/(4πa₀) = R∞). For hydrogenlike ions a universal
  R = a₀ gives a wavelength that is too long by exactly √Z (He⁺ 1.41421, Li²⁺ 1.73205); R = a₀/Z, the
  ion's own seat radius, restores exact Z² scaling. The relation is therefore an identity given the
  supplied seats a₀ and α, with the reference length carrying the seat (ledger D31). It is not an
  emission derivation, and by the specification's own exclusion list it cannot count as one.
- **P0-4 Naming.** `Om` is the engine's koppa ϟ = R/k²; `k_R` is the engine's k. Two investigation
  folders carry the id FLM15 (`FLM15_Influx_Phase_Resistance_Ratio`, which the engine's "FLM15
  resistance kernel" and `engaged_volume_fraction = 6/7` refer to, and `FLM15_Casimir_as_Relay_Exclusion`,
  an unrelated seed run earlier today). The specification's "FLM15 relay-lock ratio" is the first.
- **P0-5 Spectroscopic hypothesis.** The specification retains z_R = Δλ/λ. The engine's depth-closure
  statement (laws.hpp, item (4)) is z_spec = z(r_emit) − z(r_obs), a difference of local depths. The
  specification's own pivot row ("fractional-shift interpretation conflicts with spectral baseline")
  applies from the start (ledger D30).
- **P0-6 Undefined symbol.** E_B in the compression-work candidate has no definition and no engine
  source (ledger D32).
- **P0-7 Missing prerequisites in the corpus.** No native definition exists for collective electron
  connectivity or plasma pressure (D48); no capture clock (D45: NP18 DEFER with coherence 7 orders
  short, NP04B kinetics unresolved, NP11 barrier depth back-solved); no derived Q_β (D44: NP20 OPEN);
  no neutrino carrier energy, momentum or transport law (D46, D47); no derivation of the
  inverse-square regime from Laws III–V (D29).
- **P0-8 Sources not named by the specification but relevant.** NP18, NP20, NP11, NP17, PPT10, PPT11,
  Theory_SCT/04, and the solver's dataset files.

## Gate evaluation (Phase 0)

Gate: zero unclassified load-bearing dependencies; zero silently inherited numerical constants.

Result: **not met**. Of 55 ledger rows, 52 are traced and classified. Three are untraced:
D43 (`dnn = 1.45 fm`, a legacy-control parameter, off the load-bearing path unless Phase 3 uses
`pack_nucleus.py`), D49 (occlusion channel weights 1/9 and 4/27) and D51 (the solver's composition
and displacement datasets, not read). Every numerical constant on the executed path that was read is
declared in the ledger; the absence of others cannot be shown by reading, and a mechanical check
(every constant in a built tool appears in the ledger) is proposed for Phase 1.

Class counts: MEASURED_SEAT 10, OBSERVED 6, COMPUTED 11, DERIVED 6, AXIOM 2, CONSTRUCTION 7,
CALIBRATED(1) 1, EXCLUDED 2, OPEN 10.

## Adjustments

None (`ADJ-###` entries: 0).

## Open items for the Operator

1. Whether to split the specification into child investigations (see `PHASE0_ASSESSMENT.md`).
2. Directory placement and numbering: the stack's convention is a domain code (next free NP number
   is NP40), not an unnumbered folder; this directory follows the specification's proposed path and is
   not moved without approval.
3. The FLM15 id collision (rename of `FLM15_Casimir_as_Relay_Exclusion`) — propose-only.
4. Approval to re-qualify the celestial solver against the current `laws.hpp` before Phase 2.


## 2026-10-03 authorised continuation
Operator instruction `ok run it please`; PRECOMMIT.md records conditional scopes. Node freeze replaces inaccessible Python launcher. Existing source and Phase 0 artifacts preserved.

Fresh continuation: cmake configure/build Release; ctest four targets passed; native atomic adapter executed; original NSEQ18 validator executed with result destination redirected. finalize.js generated phase derivations, interfaces, receipts and verdict. Physical closure gates remain OPEN; no extra physical parameters or source edits.

Fresh continuation: cmake configure/build Release; ctest four targets passed; native atomic adapter executed; original NSEQ18 validator executed with result destination redirected. finalize.js generated phase derivations, interfaces, receipts and verdict. Physical closure gates remain OPEN; no extra physical parameters or source edits.

## 2026-10-03 — concurrent continuation recorded; audit; corrections (appended by the Phase 0 session)

A second session ran a continuation inside `run_2026-10-03_continuation/` after Phase 0 (Operator
instruction "ok run it please"). It was not executed by the session that wrote the entries above, so
none of its output is cited here as evidence. The Operator then asked for an audit before the split.
The audit (`AUDIT_continuation_2026-10-03.md`) reproduced the numerical claims directly and found
seven issues (F1–F7), none of them a fabricated number. Corrections to this log's own statements:

- **P0-2 corrected.** The manifest hash was compared with `Engine/include/sdt/laws.hpp`. The solver
  builds from `Release/SDT_Celestial_Three_Body_Solver/include/sdt/laws.hpp` (`f24bdb8c…`), which is
  code-identical to the engine's (1404 code lines, 0 differences; comments differ). The manifest's
  `b4212524…` matches neither, so the manifest is stale; the solver's own self-tests reproduce (3 of 3).
- **Ledger rows** D22, D29, D43, D49, D51, D52 are revised in `DEPENDENCY_LEDGER.csv` v2.
- The `ADJ-001`–`ADJ-004` entries live in the continuation's `PRECOMMIT.md`; they are not copied here
  and the duplicated paragraph above is left as written (append-only).

