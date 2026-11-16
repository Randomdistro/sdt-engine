# GOM42 Run Log

**Author:** James Christopher Tyndall, Melbourne  
**Pre-registration recorded:** 2026-08-15, before instrument creation

## Frozen configuration

- Kernel: \(a=c^2\kappa/r^2\), pairwise central
- Integrator: velocity Verlet
- Dimensional implementation: one `Vec3` path; 2D uses `z=0`
- Softening: none
- Collision rule: stop at the sum of supplied body radii
- Gates: V0–V6 in `PROMPT.md`

## Run entries

### Run 1 — 2026-08-15

- Direct build: MSVC C++20, `/O2 /utf-8`
- Result: **REJECTED**
- Passed: V0, V1, V2, V4, V5, V6
- Failed: V3 equal-source equilateral long run
- Measured V3 maximum side drift: 2.111482662
- Cause isolated after the run: the equal-source Lagrange solution violates
  the Gascheau linear-stability condition, so a 20-period truncation-error
  growth test is not a stable known-answer fixture.
- Raw capture: `gom42_results_run1.txt`

### Repair pre-registration

`PROMPT_REPAIR.md` freezes a stable three-source Lagrange fixture before the
repair is implemented. Thresholds, duration and timestep are unchanged.

### Run 2 — 2026-08-15

- Direct build: MSVC C++20, `/O2 /utf-8`
- Result: **VALIDATED**
- V0–V6: all passed
- Stable Lagrange fixture:
  - maximum side drift: 1.233700345e-06
  - barycentre drift: 4.981187318e-15
- Two-body 100-period maximum separation drift: 4.934790085e-06
- Verlet convergence ratio: 3.999798937
- Figure-eight closure:
  - position: 5.325127963e-08
  - velocity: 6.960871570e-08
- Maximum normalized invariant drift:
  - momentum: 1.014332005e-14
  - angular momentum: 5.509852986e-14
- Raw capture: `gom42_results.txt`

### Run 3 — 2026-08-15 verification rerun

- Direct rebuild after the browser walkthrough integration.
- Result: **VALIDATED**
- V0–V6: all passed at the frozen thresholds.
- Numerical results matched Run 2; `gom42_results.txt` is the direct capture.
