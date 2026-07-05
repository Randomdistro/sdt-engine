# RUN_LOG — PM06 (Cyclotron and Synchrotron from Differential Occlusion)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Written BEFORE any code.

## Pre-Run Commitments — PM06

- Prompt completion target: **C** (prompt expects C). The ω_c gain is expected to inherit PM01's
  HG-1 wall: the field-proportional turning channel is unsigned; orbit SENSE from handedness is
  expected NOT to close natively. Committed now.
- Physics class hoped: NATIVE-form (orbit closure, ω = |∇×w| with unit gain; γ-scalings from Law-V
  kinematics); CONVERGENCE/BORROW for the rest-frame emission coefficient (E89/PM03 channel —
  PM03 is flagged SUPERSEDED/DO-NOT-TRUST, so the Larmor coefficient is BORROWED, disclosed).
- CALIBRATED budget: 0. Native units c=1 in the orbit integrator (numerics choice). No µ_B/µ_N.
  No external Lorentz boost: all relativistic kinematics via Law V (T10–T17) — aberration and
  time-dilation used AS Law-V theorems (native-within-SDT, DEGENERATE with SR; disclosed).
- Anti-identity-pass guards: (i) P2's γ⁴ is NOT fit to its own formula — the measured objects are
  the orbit arrays (proper vs lab acceleration by finite differences); (ii) P3's pulse cone is NOT
  an inserted 1/γ Gaussian — the angular pattern is the solid-angle Jacobian of Law-V aberration
  from an isotropic rest emitter; (iii) P4's angle is a Monte-Carlo median through the aberration
  map, not the arccos formula.

### Phase thresholds (committed before run)

| Phase | Gate | Threshold |
|---|---|---|
| P1 | orbit closes; ω_c | non-rel: closure drift <0.1% per period; ω_meas = Ω to <0.1%. Relativistic (γ=2,10): ω_rel = Ω/γ to <0.5%; r = γv/Ω to <0.5%. Sense: unsigned channel — HG-1 disclosed; sense-from-EMC03 NOT claimed |
| P2 | proper/lab acceleration | a′/a = γ² measured from RK4 arrays by finite differences to <0.5% (γ=2,10); ⇒ P/P_rest = γ⁴ with the rest-frame coefficient BORROWED (E89/PM03, flagged); ledger exponent = 4.000 ± 0.02 from the measured pieces |
| P3 | ω_crit scaling | pulse train from the orbit + Law-V aberration pattern + arrival-time compression; RMS spectral width ω_rms/ω_rot vs γ over {4,8,16,32}: log-log slope **3.0 ± 0.15** |
| P4 | beaming | Monte-Carlo isotropic rest emitter through Law-V aberration: median lab angle θ_med·γ within **±5% of 1** for γ ≥ 8 |

### Forbidden retroactive changes
Re-import primitive qv×B to close the orbit; fit P2/P3 exponents to their own formulas; insert an
ad-hoc 1/γ cone; widen gates; magnetons anywhere.

## Run record (filled after execution)
- See `pm06_results.txt`, `PM06_VERDICT.md`.
