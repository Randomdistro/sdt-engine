# APS10 run log

## 2026-10-03 — pre-registration (before the instrument existed)

Scope correction recorded in `PROMPT.md`: APS14 already computes He–Ne first ionisation, so
this run re-verifies the engine closure against APS10's gates. Gates, anchor file, validation
checks and rejection criterion are in the "Pre-registration (2026-10-03)" section.
`NIST_ionisation_snapshot.txt` excluded as an error page.

## 2026-10-03 — run

Built with MSVC. Validation passed (H and He⁺ one-electron limits). Single pass over Z = 2–10:
median 1.476%, maximum 5.249%, no period-trend sign disagreements, all states converged.
Rejection criterion not met. Output: `aps10_results.txt`. Conclusions: `APS10_ASSESSMENT.md`.
