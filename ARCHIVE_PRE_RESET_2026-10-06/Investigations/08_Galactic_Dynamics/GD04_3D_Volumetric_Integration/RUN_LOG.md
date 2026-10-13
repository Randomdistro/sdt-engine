# RUN_LOG — GD04 3D Volumetric Integration (audit re-run)

> **Executor:** Claude (HUNTER-disciplined), on behalf of J. C. Harvey, Melbourne. **Date:** 2026-07-03.
> **Purpose:** NOT a rescue. The 2026-07-02 repo scour graded this tool INFLATED
> (real RMS ~71% stamped "[SUCCESS]" via a v > 10 m/s gate). This run compiles the tool
> AS-IS, captures the real output, and writes the missing honest VERDICT.md.

## Pre-Run Commitments — GD04

- Prompt completion target: n/a (audit run; the tool is judged, not completed)
- Physics class expected: KILLED (inflated gates), superseded by GD05 twin-regime
- CALIBRATED budget: n/a
- Pre-declared audit points (from source inspection BEFORE run):
  1. Line ~100: `if (ugc_res.predicted_velocity_m_s > 10.0)` — prints "[SUCCESS] LSB
     galaxies ... survived!" if the predicted velocity exceeds **10 m/s** (walking pace;
     the comment itself says "Should be ~64 km/s", i.e. 6,400× the gate). Any nonzero
     model output passes. This is a fake gate.
  2. Line ~106: `if (rms_err < 30.0)` prints a second "[SUCCESS]" — absent when RMS ≥ 30%,
     so a catastrophic RMS produces no FAIL line at all (silence instead of failure).
  3. Sample is 10 hand-picked galaxies with hand-assigned h_z values, not the SPARC set.
  4. Engine function used is `predicted_velocity_3d` — already `[[deprecated]]` in
     galactic.hpp, superseded by GD05's compute paths.
- Committed reporting: the REAL RMS and per-galaxy residuals, verbatim; verdict class
  KILLED regardless of what the stamps print.

## Build log

- 2026-07-03: compiled AS-IS, zero source edits. MSVC 19.44.35223 x64. Exit 0.
  (Uses `predicted_velocity_3d`, which galactic.hpp marks `[[deprecated]]`.)

## Run log

- 2026-07-03: `gd04.exe` → exit 0, full stdout in `results.txt`.
- **Real result: RMS residual 71.39%, max residual 97.70%** across the 10-galaxy sample.
- Per-galaxy: every LSB/dwarf under-predicted by 90–98% (UGC 128: predicted 3.7 km/s vs
  observed 64; DDO 154: 1.1 vs 47; IC 2574: 6.7 vs 67). Best case NGC 7331 still +26.4%.
- Audit point 1 CONFIRMED: tool prints "[SUCCESS] LSB galaxies ... survived!" because
  3.7 km/s > 10 m/s. The gate is 6,400× below the tool's own stated target.
- Audit point 2 CONFIRMED: the RMS<30% success line is absent and NO failure line is
  printed — the run ends on a lone [SUCCESS] over a 71% RMS table.
