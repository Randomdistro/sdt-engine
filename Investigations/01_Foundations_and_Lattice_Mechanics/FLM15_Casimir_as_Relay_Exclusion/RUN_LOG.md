# FLM15 run log

## 2026-10-03 — pre-registration (before the instrument existed)

Validation checks V1–V3, Round 1 (literal seed, with its numerical prediction recorded:
d-independent pressure u_CMB/3 ≈ 1.39e-14 Pa, exponent 0) and conditional Round 2 (scale-free
floor) are in `PROMPT.md`, section "Pre-registration (2026-10-03)".

## 2026-10-03 — run 1

MSVC build. V1–V3 passed. Round 1: |P| = 1.3916e-14 Pa at every d from 0.1 to 6 µm, fitted
exponent 0.000000; rejection criterion met. Round 2: extrapolated coefficient −π²/360 to
4.1e-8. The report-only finite-cutoff exponent table was wrong at d ≥ 1 µm (n_eff 3.80 at 3 µm
where λ/d < 1%): the direct sum-minus-integral carries a cancellation of about 1e10 and the
finite differences were rounding noise. Recorded as an instrument fault in a report-only
section; run 1's table is superseded.

## 2026-10-03 — run 2 (after the fault)

Added the Poisson-dual series D = (4d/π²) Σₖ (3λ² − b²)/(λ² + b²)³, b = 2kd, which is
cancellation-free and reduces to −π²/(360 d³) at λ = 0. Validation V4 added: direct sum
against dual series at λ/d = 0.30, 0.10, 0.05 (agree to 1e-8 or better). Report-only table
recomputed on the dual route: n_eff = 3.7675, 3.9749, 3.9977, 3.9997 at d = 0.1, 0.3, 1, 3 µm.
All registered gates unchanged and unaffected. Output: `flm15_results.txt`.
Conclusions: `FLM15_ASSESSMENT.md`.
