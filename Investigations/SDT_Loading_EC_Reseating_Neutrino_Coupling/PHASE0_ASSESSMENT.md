# Phase 0 Assessment — source freeze, dependency audit, and the specification's format

**Date:** 2026-10-03<br>
**Direct execution.** **Canon edits:** none<br>
**Records:** `PROMPT.md`, `RUN_LOG.md`, `SOURCE_FREEZE.json`, `DEPENDENCY_LEDGER.csv`,
`phase0_make_freeze.py`, `phase0_candidate_checks.py`, `phase0_candidate_checks.txt`

## Status

`PHASE0_COMPLETE__GATE_NOT_MET__PARENT_CLAIM_BOUNDED`

- Phase 0 is executed. Its gate (zero unclassified load-bearing dependencies) is not met: 3 of 55 ledger rows are untraced.
- The parent coupling claim is bounded before Phase 1: four mechanisms it needs have no law in the corpus (ledger D44–D48). Unless Phases 2–4 derive them, the attainable completion is the specification's second outcome, a precise identification of the missing closure.

## What Phase 0 found

| Finding | Evidence | Consequence |
|---|---|---|
| The celestial solver's qualification is stale | manifest `laws_sha256 b4212524…` against current `da72fc92…` *(correction 2026-10-03, see AUDIT: the solver builds from its own copy, `f24bdb8c…`, which is code-identical to the engine's; the manifest hash matches neither, so staleness stands but the code gates plausibly carry over)* | the manifest must be regenerated before its gates are cited; solver self-tests reproduce (3 of 3) |
| The candidate wavelength relation is the Rydberg formula | ratio 1.000000000 on five hydrogen lines; 1/(4πk_R a₀) = α/(4πa₀) = R∞ | it is an identity given the supplied seats a₀ and α, not an emission derivation |
| The reference length carries the seat | universal R = a₀ is off by exactly √Z for He⁺ and Li²⁺; R = a₀/Z restores Z² scaling | Phase 1's real question is whether R follows from a mechanism; the formula itself cannot discriminate |
| `Om` and `k_R` duplicate existing engine quantities | Om = ϟ (laws.hpp:986), k_R = k | adopt the engine names or add the mapping to the symbol table |
| Two investigations carry the id FLM15 | `FLM15_Influx_Phase_Resistance_Ratio` and `FLM15_Casimir_as_Relay_Exclusion` | the specification's "FLM15 relay-lock ratio" is the first; the second needs a new id (propose-only) |
| z_R = Δλ/λ conflicts with the engine's depth statement | laws.hpp item (4): z_spec = z(r_emit) − z(r_obs) | the specification's own pivot row applies from the start |
| E_B is undefined | no engine source | the compression-work candidate cannot be audited as written |
| Four mechanisms have no law | ledger D44–D48: capture clock, Q_β, connectivity and plasma pressure, neutrino carrier and escape | Phases 2–5 each begin by deriving a missing law |

Ledger totals (55 rows): MEASURED_SEAT 10, OBSERVED 6, COMPUTED 11, DERIVED 6, AXIOM 2,
CONSTRUCTION 7, CALIBRATED(1) 1, EXCLUDED 2, OPEN 10. Untraced rows: D43 (`dnn`, legacy control),
D49 (occlusion channel weights), D51 (solver datasets).

## Re-estimate

| Phase | Specification | After Phase 0 |
|---|---|---|
| 1 | 1–3 days | runnable as a standalone investigation; its discriminating content is isotope and per-ion response, not the hydrogen wavelengths |
| 2 | 2–5 days | begins with deriving a definition of connectivity and a plasma pressure closure; no estimate possible |
| 3 | 3–7 days | begins with a capture clock; the corpus records DEFER and UNRESOLVED; no estimate possible |
| 4 | 3–7 days | needs a derived Q and a many-contact domain law; the Q_β seat closure is recorded OPEN |
| 5 | 3–7 days | needs defined dynamics for the state vector; blocked on 2–4 |
| 6 | 2–5 days | hold-out data must be chosen outside a large exposure set (RUN_LOG) |

## Is this a decent investigative format?

**The frame is good; the unit of work is wrong.** It is a programme written as one investigation.

What works:
1. **Endpoints, not rewrites.** Every pivot ends in OPEN or EXCLUDED, adjustments are dated, and forbidden adjustments are listed. This is the repository's own discipline made stricter.
2. **Separate assessment axes.** Ten per-closure assessments and a parent-claim gate stop one passing piece from promoting the whole. The "numerical pass does not promote upstream status" paragraph is the right rule.
3. **Source freeze with a currency check.** It paid for itself: the stale qualification was found in minutes.
4. **The dependency ledger with the repository's own labels.** Writing every quantity down with a class found 3 untraced rows and 10 OPEN mechanisms in one session.
5. **Explicit exclusions and blindness handling.** The importation list and the declared target exposure are specific and checkable.

What does not work, with a fix for each:
1. **Four independent research problems are made gates of one parent** (capture clock, neutrino carrier, connectivity, many-contact domain law). Each is already OPEN or DEFER in the corpus. As written, the parent returns OPEN by construction and the fallback clause does the real work. Split into child investigations with their own prompts: (A) reference depth and emission, (B) connectivity and loading, (C) conversion event and many-contact budget, (D) bulk response, (E) a validation protocol. Keep the parent as a dependency map.
2. **Phase 0 lacks a candidate-relation audit.** Three of this session's findings (the Rydberg identity, the Δλ/λ conflict, the undefined E_B) were closed by minutes of algebra against the engine. Add the step: for every candidate relation, check for identities, undefined symbols and conflicts with existing engine statements, and classify an identity as CONSTRUCTION.
3. **"Zero silently inherited constants" cannot be demonstrated by reading.** Replace it with a mechanical check: every numerical constant in a built tool appears in the ledger.
4. **Gates that are qualitative.** "Must match derived limiting behaviour" (Phase 2) and "independent integrations agree within the declared error budget" (Phase 5) need numeric thresholds, as the template requires of every phase.
5. **Day estimates for Phases 2–5** are not credible where the first task is deriving a law. State "derivation-dependent" and re-estimate at each gate.
6. **Register conflicts.** `VERDICT.md` should be `ASSESSMENT.md` (behavioural gateway §1); "Nuclear charge" in the symbol table should read "proton number" (the gateway prohibits the word); the directory should carry a domain code (next free NP number is NP40), not an unnumbered name.
7. **Upstream sources are incomplete.** Add NP18, NP20, NP11, NP17, PPT10, PPT11, Theory_SCT/04 and the solver's dataset files.
8. **Hold-out data chosen too late.** With this much historical exposure, name and seal the held-out observables at specification time, not in Phase 6.
9. **A pre-listed output set of fifteen files** invites placeholders for phases that may not run. List outputs per phase and produce them when the phase is reached.
10. **Missing pivot.** Add a trigger for "candidate relation reduces to an existing relation": classify CONSTRUCTION, state what it adds, continue.

A quick measure against the repository's template checklist: Executive Summary within the word limit
(yes), key variables with dimensions (partly; E_B and the neutrino carrier symbols are undefined),
falsification tests that could fail (yes), pivot table with numeric triggers (partly), pre-run
commitment block copy-ready (yes), dual assessment (replaced by ten per-closure assessments, an improvement), and
every phase with numeric success metric and failure trigger (no, see item 4).

## Recommended next step

Run Phase 1 as its own investigation (child A), with the candidate audit already done. Its questions
are then sharp: whether R (the reference length) follows from a mechanism shared between atomic and
celestial seats, what the derived response law gives for isotopes without an inserted reduced-mass
coefficient, and which non-hydrogenic data discriminate.
