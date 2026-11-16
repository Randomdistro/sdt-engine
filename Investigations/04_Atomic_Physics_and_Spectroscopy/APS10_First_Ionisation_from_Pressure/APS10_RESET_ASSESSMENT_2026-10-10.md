# APS10 — First ionisation energies: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0.

**Read:** PROMPT.md, including its 2026-10-03 pre-registration, carried unchanged; laws.hpp tomic::dodecardinal (the solve_state interface).

**Not opened:** APS10_ASSESSMENT.md, ps10_results.txt, ps10_verify_ie1.cpp, RUN_LOG.md, the APS14 assessment.

**Anchor.** Datasets/nuclear/ionisation_energies.json, first entry per Z (NIST/CRC compilation, as the prompt registers).

**Gates (prompt, unchanged):**
- median error ≤ 15%, maximum ≤ 40%;
- all 9 consecutive-pair signs match measurement;
- 5% suite destination reported, not gated.

**Validation (prompt):**
- solve_state(1,1) = −Ry and solve_state(2,1) = −4 Ry, each to 1e-6 relative, with converged = true;
- force residual < 1e-8 for every state used.

**Label ceiling:** COMPUTED (the coefficient forms were isolated against the B06 rows).

## Run and results
(below)
- Instrument: `aps10_reset_1.cpp`; output in `aps10_reset_1_results.txt`. Single pass.
- **Validation met:** −13.605693 and −54.422772 eV against −Ry and −4Ry; both converged; maximum force residual 1.49e-9.

| Z | IE₁ predicted (eV) | IE₁ measured (eV) | error |
|---|---|---|---|
| 2 | 25.5454 | 24.5874 | +3.90% |
| 3 | 5.1304 | 5.3917 | −4.85% |
| 4 | 8.8334 | 9.3227 | −5.25% |
| 5 | 8.2500 | 8.2980 | −0.58% |
| 6 | 11.2791 | 11.2603 | +0.17% |
| 7 | 14.6434 | 14.5341 | +0.75% |
| 8 | 13.5511 | 13.6181 | −0.49% |
| 9 | 17.1657 | 17.4228 | −1.48% |
| 10 | 21.1595 | 21.5646 | −1.88% |

**Opening gate MET:**
- median 1.48% (≤ 15%);
- maximum 5.25% (≤ 40%);
- signs 8/8, including the decreases from Be to B and from N to O.

Note: the prompt says "nine consecutive pairs", but Z = 2–10 has eight. This is a count slip in the prompt; the gate is applied to all eight.

**Suite 5% destination:** the median is within it; the maximum (Be, −5.25%) is just outside.

**Grade:** G3/G4 boundary, labelled COMPUTED. The closure is native geometry (the dodecardinal solver; no wavefunction), but its coefficient forms were isolated against these B06 rows (the prompt's own disclosure), so this is a re-verification, not a blind prediction.

**What remains open:** Z ≥ 11 (the solver's domain ends at 10 electrons), and a blind test on quantities not used in the isolation. The prompt notes APS14's higher sequential ionisations as that test.

## Comparison with the archived record
Deferred.
