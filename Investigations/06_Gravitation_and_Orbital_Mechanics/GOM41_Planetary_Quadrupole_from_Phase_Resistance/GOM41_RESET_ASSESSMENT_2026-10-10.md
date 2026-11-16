# GOM41 — Planetary quadrupole from phase resistance: reset record, audit (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0. **Read:** PROMPT.md. **Not opened:** GOM41_ASSESSMENT.md, gom41_results_2026-10-05.txt, the old tool.

## Audit
1. **The prompt carries its own executed outcome** (2026-08-15):
   - Q0: RMS 254.75%;
   - Q1: Earth +0.91%, Jupiter −2.11%, 3/6 within 10%, RMS 28.89%;
   - Q2: RMS 30.47%, 3/6 within 10%;
   - every model fails gate 6; numerical controls pass.

   A run now cannot be blind to those numbers.
2. **Q2 imports source models.** It uses PREM mechanical strata (seismological Earth model), Lane–Emden polytropes (n = 1 and n = 3/2), and the Clairaut/Radau response. Under the 2026-10-07 rule these are imported source models, and Q2 is not admissible as a native test in the reset.
3. **Q0 and Q1 are native in form.** Uniform resistance, and the equator/pole convergence-boundary balance from measured boundaries. Rebuilding them needs the six-body corpus: a satellite (r, P) per body, measured polar and equatorial radii, and J2 sealed as comparison-only. No corpus is cached in Datasets/.

## Outcome
**G2 (open): not rerun.** The outcome was exposed in the prompt, the corpus is not cached, and Q2 is not admissible.

**What opens it:**
- cache the six-body corpus with provenance, then rerun Q0/Q1 fresh with J2 sealed;
- a native giant-planet phase-resistance profile (the prompt's own named missing dependency), stated before J2 is loaded.

## Comparison with the archived record
Deferred.
