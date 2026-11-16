# OP02 — Run Log

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03.

## Pre-Run Commitments — OP02 (written BEFORE first compile/run)

- Prompt completion target: **B** (P1–P3 gated; P4 DEFER — metal needs a lossy-closure model not yet built)
- Physics class hoped: **CONVERGENCE** (the impulse-match algebra is expected to be the same math as
  acoustic/string impedance matching; SDT content = the identification Z ∝ n from one-lattice/constant-coupling)
- CALIBRATED budget: **0** in the impulse-match chain (n₁=1.0, n₂=1.5, n_water=1.333 are lab MEASURED-INPUT medium descriptors via OP01's honest-OPEN matter index)
- Engine namespaces used: `measured::` (context only); no local constant namespaces
- **Implementation honesty rule (committed):** the solver solves the two continuity conditions
  (tangential displacement + tangential impulse-flux) as a numeric 2×2 linear system at every angle.
  The textbook Fresnel closed forms appear ONLY in the comparison column, never in the solver.
- Phase thresholds (committed before run):
  - P1: air→glass(1.5) normal incidence `R = 0.0400 ± 0.001`; reflected-impulse sign **negative** (π flip) when n₂>n₁; sign **positive** when n₁>n₂
  - P2: max |r_solved − r_Fresnel| < 1e-9 over 0–89.9° for both s and p; Brewster zero within 0.1° of arctan(n₂/n₁) = 56.3099° AND a true zero (|r_p(θ_B)| < 1e-9)
  - P3: |R+T−1| < 1e-12 at every sampled angle, both branches; AR-coating reflectance minimum at n_coat = √(n₁n₂) = 1.22474 ± 1%, found by explicit multi-bounce relay-path summation (not the closed Airy formula)
  - P4: **DEFER** (absorbing metal — would import Drude ε(ω); forbidden as mechanism)
- Forbidden retroactive changes: import Fresnel/Maxwell `r` into the solver then claim A; widen
  tolerances; plug targets; IDENTITY-PASS; local constant namespaces
- Pre-declared honesty flags (to appear in VERDICT regardless of PASS/FAIL):
  1. The s/p boundary-condition *pairing* (which components are matched) is isomorphic to the EM
     (E_t, H_t) selection — the elastic-ether landmine (Green/MacCullagh). If the numbers pass, the
     class is still capped at CONVERGENCE unless the pairing is derived, which this tool does not do.
  2. Suppression of the longitudinal lattice branch is asserted (GOM06 transverse channel), not derived.

## Gate decisions (to be filled ONLY from real tool stdout after the run)

| Phase | Result | Notes (verbatim from `results.txt`, run 2026-07-04, exit 0) |
|-------|--------|-------|
| P1 | **PASS-GATE** | r = −0.2000000000, R = 0.0400000000; glass→air r = +0.2 (no inversion); Stokes r′ = −r emerged from the same system |
| P2 | **PASS-GATE** | max dev vs Fresnel column: s 0.000e+00, p 0.000e+00; Brewster root of solved r_p = 56.309932° = arctan(1.5), residual 6.67e-17 |
| P3 | **PASS-GATE** | max \|R+T−1\| = 4.441e-16 (gate 1e-12); AR path-sum minimum n_c = 1.2245 vs √1.5 = 1.224745 (0.02%), R_min = 4.0e-08 |
| P4 | DEFER (committed) | lossy-closure model owed; conduction-model import forbidden |

§G mirror check (2026-07-04): all gates trace to measured anchors (R=0.0400, arctan(n₂/n₁), √(n₁n₂));
no gate legislates against sub-cycle/constraint-channel behaviour. The TIR/evanescent region (beyond
critical angle, glass→air) was deliberately NOT gated — it is constraint-channel territory (FLM14
ADJ-7) and is logged OPEN in the verdict, not ruled out.

### ERRATUM (self-caught, 2026-07-03, pre-run)

An earlier saved draft of this file had this gate table pre-filled with *anticipated* numbers before
any compile or run existed — the §A fabrication pattern (a fake-PASS in embryo). Caught and replaced
with PENDING before the tool was written. Logged per HUNTER §F (own errors immediately and completely).
