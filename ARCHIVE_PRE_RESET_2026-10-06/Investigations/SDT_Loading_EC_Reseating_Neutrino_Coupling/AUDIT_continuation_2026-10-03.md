# Audit — `run_2026-10-03_continuation/`

**Date:** 2026-10-03<br>
**Audited work:** the specification and the continuation run (authorised by the Operator's "ok run it please"), both produced with ChatGPT. This audit examines the artifacts only; it cannot say which parts a model generated unaided.<br>
**Method:** direct execution in the main session. Every claim below marked *reproduced* was recomputed here by my own script or build, with outputs confined to the session scratchpad. Nothing in the continuation folder was edited.<br>
**Canon edits:** none

## Conclusion

The continuation computes correctly where it computes, and its source-integrity claim holds. No fabricated number was found. It overstates in four ways: its "derived" atomic coupling is the supplied α; five of its prose records are static text written by a script, not results; a headline count ("213 EC inventory pairs") carries no physical selection; and it duplicates engine constants in a script. Its OPEN statuses for Phases 2–5 agree with Phase 0 and are supported by Phase 0's own evidence, not by the continuation.

## Reproduced

| Claim | Check here | Result |
|---|---|---|
| Canonical sources, release code and prior Phase 0 files unchanged | sha256 of all 58 files in my freeze; `git status Engine Release` | no file changed; tree clean |
| Release and canonical `laws.hpp` differ in comments only | comments and blank lines stripped, then compared | 1404 code lines each, 0 differences |
| Native solver tests pass | solver's own CMake built and tested here | 3 of 3 passed (the continuation's fourth test is its own adapter) |
| Atomic numbers: C, μ, R, E_B, Lyman-α | independent Python from engine constants | agree with `atomic_results.json` to full double precision (C = 2.307077550935e-28 J m, R = 5.294654094961e-11 m, λ = 1.215684456174e-7 m) |
| Compression: ΔE = E_B (R/r − 1)² with E_B = C/(2R) | closed form at three ratios | agrees to 1e-16; the algebra of ADJ-003 is correct |
| Compression quadrature residual 4.713e-9 | read from `compression_quadrature.json` | matches (x = 0.1, N = 1024) |
| 221 of 221 isotopes built; 4 validator failures | validator run here with its result write redirected to scratch | same four tokens: `magic_numbers[8]`, `triton_opening_scale`, `triton_closing_scale`, `triton_closure_scale` |
| Maximum contact degree 7 | re-run on the same table | 7 (171 of 217 rows have a node of degree 7) |
| He-4 11.69 MeV and U-238 672.6 MeV against 28.296 and 1801.69 MeV | validator output re-read | match; the construction gives about 37–41% of the stored values across the spot set |

## Findings

**F1 — High. The "derived" atomic coupling is the supplied α.** `F_nuclear_electron(Z, r)` reduces to Z α ħ c / r², because `P_eff` is defined as 4αħc/(π R_p_lock² r_e²) and the effective area is Z R_p_lock² r_e². So C = Zαħc by construction, and with L = ħ the results k = 137.03599908… and z = α² are 1/α and α² to the last digit. The "1,840 force-balance cases passing at 6.8e-16" test a radius that is defined by the same balance: an arithmetic check of rounding, with no physical content. The status "DERIVED conditional" for reference depth overstates what was shown; the classes that fit are CONSTRUCTION (the definitions k_R, z_R, Om) and COMPUTED given α, L = ħ and a central 1/r² law. The fixed-action compression formula is a derivation (DERIVED) from those same premises.

**F2 — High. Five records are static text.** `finalize.js` writes `DERIVATION.md`, `MECHANISM_INTERFACES.md`, `STABILITY_REPORT.md`, `NOVELTY_REPORT.md` and `STATE_AND_UNITS.md` as fixed template strings. The VERDICT's "Phases 2–5 were evaluated through interface and identifiability gates" means a written argument, not a test. The arguments are sound and agree with Phase 0 (an event rate is not identifiable from conservation constraints alone), but they are analysis, not execution evidence. `EVENT_LEDGER.csv` is 213 rows with Q and rate marked OPEN; `CONTACT_AUDIT.csv` has degrees only, with no ports, phases, clearance or slip, so the specification's required contents are unmet (each file says so).

**F3 — High. "Exact EC inventory pairs: 213" has no physical selection.** The count is the number of table rows with at least three deuterons. Of the 213, 198 are flagged stable in the table, and none has a positive Q_EC against AME2020 (0 of 213, with both parent and daughter present). The public table holds stable and long-lived isotopes only (its one beryllium is Be-9). The count describes the grammar, and the VERDICT presents it as a result.

**F4 — Medium. Engine constants duplicated in a script.** `finalize.js` hard-codes c, h, ħ, m_e, m_p, m_d, m_t and m_He3 and computes `spectra_results.json` outside the engine. The values equal the engine's today (checked), so no result is wrong. It breaks the procedural rule that no file redefines a constant the engine exposes, and a future engine change would not propagate. The VERDICT text also embeds typed literals (1,840; 4.713e-9). Both match the data now.

**F5 — Medium. Contact reporting understates the port problem.** Only the maximum degree (7) is reported. 212 of 217 constructed nuclides have nodes above three contacts (1072 nodes in total). The three-port interpretation is violated almost everywhere, not at an extreme.

**F6 — Medium. Bookkeeping.** ADJ-001 to ADJ-004 are in `PRECOMMIT.md` and not in `RUN_LOG.md`, and carry none of the template's fields (trigger, unchanged target, rerun evidence). The run-log paragraph is appended twice. ADJ-003 is a specification change (E_B defined as C/(2R)); it is correct and should be recorded as one. `VERDICT.md` follows the specification's filename; the behavioural gateway asks for `ASSESSMENT.md`.

**F7 — Low. "Fresh native qualification" is the solver's own consistency tests.** They pass and reproduce here. They do not validate physics, browser or WASM parity, or loading models, and the continuation says so.

## What the continuation got right

- The source freeze, the end-of-run integrity comparison, and the decision not to insert constants to satisfy the four validator tokens.
- Declared reduced mass from two-body mechanics rather than an inserted coefficient; the reference length per ion comes out as L²/(μC_Z) = a₀/Z, which answers Phase 0's observation that a universal R fails by √Z. It rests on α, L = ħ and an assumed quantisation n.
- `VALIDATION.csv` states the one prediction as target-aware and not opened.
- Missing laws are reported OPEN without a fabricated rate, connectivity, carrier or instability equation.

## Corrections to the Phase 0 records

1. **P0-2 (qualification currency).** The manifest's `laws_sha256 = b4212524…` was compared with `Engine/include/sdt/laws.hpp` (`da72fc92…`). The solver builds from its own copy, `Release/SDT_Celestial_Three_Body_Solver/include/sdt/laws.hpp` (`f24bdb8c…`). The manifest hash matches neither. The staleness stands, and its basis is corrected: the executable code of the engine and the solver copy is identical, so the numerical gates plausibly carry over, and the manifest still has to be regenerated before it is cited.
2. **D22 and D29 (ledger).** P_eff is constructed so that the electron–nucleus coefficient is exactly Zαħc; the atomic coupling is an α input.
3. **D43, D49, D51 (ledger).** Now traced: D43 a frozen legacy convention (origin undocumented; NP17b records it as frozen), D49 a geometric discretisation frozen in the GOM43 prompt, D51 OBSERVED inputs with a COMPUTED ledger.

## Not audited

Browser and WASM parity; the solver's physical validity; the composition dataset's values against their sources; per-isotope construction outputs beyond counts and spot values; and the continuation's own CMake test target (I rebuilt the solver's tests, not its adapter's CTest wrapper; the adapter's numbers were recomputed in Python instead).

## Addendum 2026-10-05 — F3 scope corrected
F3 stated that none of the 213 rows has a positive Q_EC. That held for the public website table (stable and long-lived nuclides only). Against the full NUBASE2020 table (`Datasets/nuclear/NUBASE2020.txt`) NP40 finds 927 measured EC/B+ parents, all with Q_EC > 0, so a physical accessibility selection can be defined; the finding that the continuation's "213" is a grammar count and not a selection stands. See `05_Nuclear_Physics/NP40_EC_Conversion_Accessibility_and_Capture_Clock/NP40_ASSESSMENT.md`.
