# RUN_LOG — GOM03 Lunar Orbital Kinematics

> **Executor:** Claude (HUNTER-disciplined), on behalf of J. C. Harvey, Melbourne. **Date:** 2026-07-03.

## Pre-Run Commitments — GOM03 (written BEFORE first compile/run)

- Prompt completion target: B (the existing tool implements a PARALLAX pipeline, not the
  pendulum-tidal M2/O1/N2 inversion the PROMPT specifies — noted before running; grading
  the tool that exists, honestly, against the PROMPT's numeric criteria)
- Physics class hoped: CONVERGENCE (ϟ = v²d is numerically GM — bridge identity, disclosed)
- CALIBRATED budget: 0
- Engine namespaces: bridge:: only (v_Moon, R_Moon, v_Earth, k_Earth, koppa_Earth, z_from_v,
  k_from_v, zk2_product). No G, no M.
- Phase thresholds (committed before run, from PROMPT §Success Criteria — NOT the looser
  in-code scorecard tolerances):
  - d_mean within **0.1%** of 384,400 km
  - eccentricity within **5%** of 0.0549
  - period within **0.01%** of 27.321661 d
  - no G/M in pipeline (audit of source)
- Pre-declared audit flags (written before run):
  1. `extract_orbit()` has a FALLBACK: if <2 perigees found, P_s is set to the TRUE sidereal
     period (line ~203). If recovered P prints as exactly 27.321661 d / err 0.000%, the
     fallback engaged and the period is HAND-FED, not recovered → that row is void.
  2. The whole run is a SYNTHETIC-RECOVERY loop (ephemeris synthesised from the same known
     parameters it then "recovers"). It can only ever demonstrate pipeline feasibility,
     never an independent measurement. Class ceiling: mock self-consistency.
  3. ϟ = v²d ≡ GM numerically — label CONVERGENCE (sanctioned, disclosed), never NATIVE.
  4. zk² = 1 is an algebraic IDENTITY — must not be counted as a physics pass.
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local
  constant namespaces. Build fixes allowed only if minimal and documented here as ADJ-###.

## Build log

- 2026-07-03: compiled AS-IS, zero source edits. MSVC 19.44.35223 x64,
  `cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include`. Exit 0. No warnings shown.

## Run log

- 2026-07-03: `gom03_lunar_pendulum.exe` → exit 0, full stdout in `results.txt`.
- Against the pre-committed thresholds:
  - d_mean: **+3.61%** vs committed 0.1% → **FAIL**
  - eccentricity: **+66.2%** vs committed 5% → **FAIL**
  - period: **+6.799%** vs committed 0.01% → **FAIL** (recovered 29.179 d ≈ synodic
    29.53 d, not sidereal 27.32 d — the perigee detector aliases against the
    observing-window gaps; fallback did NOT engage, so the number is real)
- Audit flag 1 (hand-fed fallback): did NOT trigger (P ≠ 27.321661 exactly). Good.
- Audit flag 4: the in-code scorecard stamps "✓" at 5%/20%/1% tolerances — those are
  looser than the PROMPT's success criteria and are NOT honoured here. No tolerance
  widening: the committed gates stand, and the run fails them.
- Genuine content that survives: v_surface(Earth) extrapolated from lunar ϟ via
  v²d = const lands −0.74% from 7909 m/s; ϟ = v²d −2.49% from known. Both are the
  Newtonian GM identity in koppa clothes (CONVERGENCE, disclosed). zk² = 1 row is
  an algebraic IDENTITY, not a result.
