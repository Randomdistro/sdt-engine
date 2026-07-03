# RUN_LOG — GOM12 Solar-System Convergence Budget

> **Executor:** Claude (HUNTER-disciplined), on behalf of J. C. Harvey, Melbourne. **Date:** 2026-07-03.
> **Linked experiment:** E101 (Complete Convergence Budget of the Solar System).

## Pre-Run Commitments — GOM12 (written BEFORE the tool was coded or run)

- Prompt completion target: B
- Physics class hoped: CONVERGENCE (the whole census is kinematics; ϟ ≡ GM/c² is the
  disclosed bridge identity; nothing here can beat Newton — the deliverable is the
  budget bookkeeping, honestly labelled)
- CALIBRATED budget: 0 (inputs are JPL/IAU measured kinematics only: v_orbital, a, R)
- Engine namespaces: `sdt::laws::measured`, `bridge::` (k_Sun, koppa_Sun), `law_II::`
  (r_domain), `depth_closure::lumiopause_m`. No G, no M as inputs. GM/c² appears ONLY
  as the OBSERVED comparison column, labelled CONVERGENCE.
- Committed thresholds (before run):
  1. z·k² = 1 to < 1e-12 for every body — **label IDENTITY** (notation check only; can
     never count as a physics pass).
  2. Kepler check v_pred = v_surf,Sun·√(R_Sun/r) vs JPL orbital velocity: **< 0.1%**
     for all 8 planets (CONVERGENCE with Kepler; the PROMPT's table velocities are
     circular-equivalents √(GM/a) — noted BEFORE run: true time-mean velocities of
     eccentric orbits differ by ~e²/4 and would fail; using the PROMPT's own table).
  3. Parent invariance: ϟ_Sun from 8 planets σ/μ **< 0.1%**; ϟ_Jupiter from the 4
     Galilean moons σ/μ **< 1%**.
  4. ϟ_kinematic vs GM/c² (IAU, OBSERVED column): **< 0.5%** agreement per body
     (CONVERGENCE, disclosed; Mercury/Venus have no moons → their own ϟ is
     UNMEASURABLE by pure orbital kinematics — honest gap, stated, not plugged).
  5. Lumiopause (≈ 20,857 AU from law_II/L_Sun+F_CMB) vs Oort inner edge: literature
     range for the inner edge spans ~2,000–20,000 AU, so the PROMPT's "within factor
     of 2" is under-specified. Committed handling: report the ratio against BOTH ends
     of the range and class the item **OPEN/DEGENERATE** (consistent with the upper
     end only) — no PASS stamp on an under-specified target.
  6. Occlusion census Σ f_i, f_i = R_i²/(4 r_i²): pure geometry, reported, no gate.
  7. Jupiter's convergence contribution at Earth (z_J = ϟ_J/r_JE at opposition) vs the
     ~1e-8 orbital residual: report the raw number; if it is orders below 1e-8, SAY SO.
  8. Adjacent-planet k² ratios (= a ratios): integer "hit" only if |ratio − n| < 0.02;
     expectation stated before run: NO systematic integer pattern exists (a-ratios are
     not integers); a null result is the honest expected outcome for the E21 conjecture.
- Forbidden retroactive changes: widen tolerances; plug targets; sell IDENTITY rows as
  physics; average away a failing body.

## Build log

- 2026-07-03: `gom12_convergence_budget.cpp` written AFTER the commitments above.
  Compiled clean, MSVC 19.44.35223 x64. (`std::strcmp` resolved transitively; noted.)

## Run log

- 2026-07-03: `gom12.exe` → **exit 1** (3 gated FAILs — kept, not widened).
  Full stdout in `results.txt`. Score: 2 PASS, 3 FAIL, 1 IDENTITY (unscored), 2 OPEN.
- Gate outcomes and root causes (diagnosed AFTER, gates unchanged):
  1. zk² identity: max dev 3.3e-16 — IDENTITY, unscored. ✓ as notation.
  2. Kepler v(r): worst err **−0.351% (Saturn)**, Mars +0.220% → **FAIL at 0.1%**.
     Root cause: the PROMPT's JPL velocity table mixes MEAN orbital speeds of
     eccentric orbits with circular equivalents (pre-flagged in commitment #2);
     Mars (e=0.093) and Saturn (e=0.057) are exactly the two failures.
  3. ϟ_Sun invariance from v²a probes: σ/μ = **0.301%** → **FAIL at 0.1%**. Same root
     cause (Mars 1470.6 m, Saturn 1487.5 m pull the spread). Cross-reference: the
     (a,T)-probe version 4π²a³/T²c² run in GD03's tool on the same day gives
     σ/μ = 0.0611% — the invariance holds with clean probes; this probe set is dirty.
     Recorded as FAIL for THIS run per commitment; no retro-substitution.
  4. Satellite census vs GM/c²: **FAIL at 0.5%** — driven by Earth–Moon (+0.727%).
     Diagnosis: v²a of a satellite measures ϟ(parent) + ϟ(satellite) (two-body);
     the Moon is 1.2% of Earth — the parent-only comparison MUST fail at ~1% there.
     Physically informative, not an error of the framework; gate stands as committed.
     Jupiter's 4 Galilean probes: σ/μ = 0.010% → PASS (the clean multi-probe case).
  5. Occlusion census: Σf = 4.19e-9 (Jupiter 2.0e-9 dominant) — the planets shadow
     ~4 parts in 1e9 of the Sun's 4π influx. Budget closes to 1 part in 2.4e8.
  6. Jupiter depth at Earth: z_J = 2.24e-12 = 4,460× BELOW the ~1e-8 residual scale
     → does NOT explain it. Stated plainly.
  7. Lumiopause 20,857 AU vs Oort inner edge 2,000–20,000 AU → OPEN as committed
     (consistent with upper end only; 10.4× vs lower end).
  8. E21 integer k² conjecture: 0/7 hits (closest Uranus/Saturn 2.026, |Δ|=0.026 just
     outside gate) → NOT supported. Null result recorded.
