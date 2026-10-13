# NP11 run log

## 2026-10-03 — pre-registration (before the instrument existed)

Premise update (J-PARC beam result), validation V1–V3, Part C (data audit with its predicted
outcomes), Part A1 (clock ambiguity), Part A2 (census grammar, tolerance, null, criterion) and
Part A3 (Law V per-tick candidate) are in `PROMPT.md`, section "Pre-registration (2026-10-03)".
The seed's commitments block (⑩) is answered there: calibrated budget 0, no fitted prefactor,
no thermal barrier import; the sign statement is recorded as a retrodiction.

## 2026-10-03 — run

MSVC build. V1–V3 passed (V3: Monte Carlo null 3.157 against the analytic 3.160 expected hits).
Part C: J-PARC − earlier beams = −10.9 ± 4.6 s (−2.36σ), so the registered criterion (more than
2σ between beam-type results) was met and the 3σ exclusion level was not. Part A1: B_req spans
7.5 nats across the five nuclear-scale clocks. Part A2: 6 hits across the five nuclear-scale
clocks against a null mean of 6.78 (P = 0.64); no per-clock probability below 0.05. Part A3: no
hits (0.22 expected). All registered predictions held.

One report-only addition after the first run: the nearest construction per clock and the
lifetime it implies, because a 1.5% window in B corresponds to a factor 2.5 in τ. Registered
gates unchanged. Output: `np11_results.txt`. Conclusions: `NP11_ASSESSMENT.md`.
