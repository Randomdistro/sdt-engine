# GOM42 — Koppa N-body integrator: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0. **Read:** PROMPT.md (gates V0–V6 as registered). **Not opened:** GOM42_ASSESSMENT.md, gom42_results*.txt, gom42_nbody.cpp, PROMPT_REPAIR.md, RUN_LOG.md.

## Registration
Gates V0–V6 are exactly as in the prompt. The instrument is a fresh velocity-Verlet integrator with a = c²Σκ_j(r_j − r_i)/r³, no softening, and a collision stop.
- **Units:** scaled so that c²κ = 1 and L = 1. Scaling is exact; dimensions are checked in V0.
- **V4 initial state:** the published figure-eight (Chenciner–Montgomery):
  - x₁ = −x₂ = (0.97000436, −0.24308753), x₃ = 0;
  - v₃ = (−0.93240737, −0.86473146), v₁ = v₂ = −v₃/2;
  - period T = 6.32591398 (equal sources, unit coupling) [B: recalled published values].
- **V4 scales:** position scale = L (1); velocity scale = |v₃|.

## Run and results
(below)
- **Attempt 1** (output: `gom42_reset_1_results_attempt1.txt`).
  - V6 failed by an instrument fault: on hitting the contact boundary the step stopped without restoring the drifted positions, leaving an overlap of 7.8e-5.
  - V3 failed as described below.
- **Attempt 2.** A rejected step now restores the pre-step state, and a V3 growth diagnostic is printed. No gate changed. Output in `gom42_reset_1_results.txt`.

| gate | result | threshold | outcome |
|---|---|---|---|
| V0 pair symmetry; r⁻² scaling | 0; ×4.000000000000 | 1e-14 | met |
| V1 circular, 100 periods | separation drift 4.93e-6; energy 2.44e-11 | 5e-5; 5e-6 | met |
| V2 second-order convergence | error ratio 4.000 | ≥ 3.5 | met |
| V3 Lagrange equilateral, 20 periods | side drift **4.03** | ≤ 1e-4 | **NOT MET** |
| V4 figure-eight, one period | RMS position 5.33e-8; velocity 5.47e-8 | 2e-5 | met |
| V5 invariants | P drift 1.67e-14; L drift 9.77e-15 | 1e-11; 1e-10 | met |
| V6 collision stop | stopped at separation 0.200346 | ≥ 0.2 | met |

**V3 origin: the registered known answer is physically unstable.**
- The diagnostic shows side drift of 1.23e-6 at 1 and 2 periods, 4.50e-6 at 5, 2.87 at 10 and 4.03 at 20. That is exponential growth from round-off.
- Lagrange's equilateral solution is linearly stable only if one mass dominates (Routh: 27(m₁m₂ + m₂m₃ + m₃m₁) < (m₁ + m₂ + m₃)²). Three equal sources violate it, so no double-precision integrator can hold 1e-4 over 20 periods.
- This is a **registration defect**: the gate's known answer is unstable. It is not an instrument fault. The same instrument holds the stable figure-eight choreography to 5e-8.

**Grade:** VERIFICATION. The instrument is validated on V0–V2 and V4–V6.

**Next round, to be registered before running:** replace V3 with a stable three-body known answer, such as a Lagrange configuration that satisfies Routh (one source ≫ the others), or the equal-mass case run only within its pre-instability window (≤ 2 periods). Also add a numeric physics gate on a measured system (the 2026-10-05 correction).

## Comparison with the archived record
Deferred.
