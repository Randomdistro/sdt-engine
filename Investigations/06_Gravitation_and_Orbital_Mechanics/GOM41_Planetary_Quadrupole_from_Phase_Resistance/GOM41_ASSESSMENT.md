# GOM41 — Assessment (2026-10-05): reproduction of the 2026-08-15 direct run

**Classification:** `GOM41_B11_PENDING__NUMERICS_PASS_NO_REGISTERED_MODEL_CLEARS_CORPUS_GATE`<br>
**Run class:** direct (MSVC 19.44, `cl /std:c++20 /O2`, constants from `laws.hpp`). Output `gom41_results_2026-10-05.txt` (program's own stdout, exit code 1 on model failure). The results recorded in the PROMPT on 2026-08-15 reproduce exactly; nothing was changed in the code, the model ladder or the gates. **Canon edits:** none. This folder was in the "no result file" triage list only because its results were written inside `PROMPT.md`.

## Reproduced values
| Model | Earth | Mars | Jupiter | Saturn | Uranus | Neptune | within 10% | RMS |
|---|---|---|---|---|---|---|---|---|
| Q0_UNIFORM | +58.35% | +17.12% | +203.40% | +383.66% | +342.78% | +282.18% | 0/6 | 254.75% |
| Q1_CONVERGENCE | +0.91% | +21.82% | −2.11% | −1.75% | +64.78% | −18.04% | 3/6 | 28.89% |
| Q2_BOUNDARIES | +1.16% | −2.78% | +5.14% | +67.61% | −15.41% | −26.99% | 3/6 | 30.47% |

Numeric gates pass: zero-spin |J2| = 0; spherical leakage 0; direct-integral/Radau identity residual max 3.394e-7; doubling the resolution changes J2 by at most 2.443e-4 (relative).

## Gate evaluation (PROMPT §Numeric gates 6)
A model advances B11 only if Earth and Jupiter are each within 3%, at least four of six within 10%, and RMS ≤ 10%. Q1 meets the first (Earth +0.91%, Jupiter −2.11%) and misses the other two (3 of 6; RMS 28.9%). Q2 meets Earth, misses Jupiter's 3% (+5.14%), 3 of 6, RMS 30.5%. No model advances B11; status PENDING.

## Assessment
- The source depth (koppa from one timed satellite orbit per body) and the numerics are resolved; the miss is in the resistance profile, as the PROMPT records: Uranus and Neptune (Q1 +64.8%, −18.0%; Q2 −15.4%, −27.0%) and Saturn under Q2 (+67.6%).
- The boundary-balance model Q1, which has no composition strata, lands five of the six bodies within 25% (Uranus is the exception, +64.8%) and Earth, Jupiter and Saturn within 2.2% with no profile choice; Q2 adds class-level Lane–Emden profiles and worsens Saturn from −1.75% to +67.61%. The profile additions did not improve the corpus RMS (28.9% → 30.5%).
- The missing dependency stated in the PROMPT stands: an independently established giant-planet phase-resistance equation of state and mechanical transition boundaries. It may not be inferred from the J2 column.
