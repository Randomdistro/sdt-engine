# NSEQ17 — Run Log

**Author:** James Christopher Tyndall, Melbourne  
**Pre-registration time:** 2026-08-16, before the NSEQ17 solver

## Frozen execution order

1. Validate the transformed-filament instrument on rigid-motion invariance, a closed
   circular loop, and a deliberately separated zero-overlap pair.
2. Run H-2, H-3, and He-3 in one process with the frozen bounds and seeds below.
3. Write the complete target, coefficient, contribution, conservation, and residual
   ledger.
4. Repeat the run and compare every fitted parameter for deterministic equality.
5. Apply the registered rejection criteria without changing bounds or weights.

## Frozen seeds

| isotope | separation Rp | opening | tilt | toroidal phase | poloidal phase |
|---|---:|---:|---:|---:|---:|
| H-2 | 2.00 | — | 90° | π | π/2 |
| H-3 | 2.10 | 180° | 90° | 2π/3 | π/2 |
| He-3 | 2.10 | 180° | 90° | 4π/3 | π/2 |

The coordinate-search step is halved after each complete sweep and terminates after
14 halvings. Parameter order is exactly the table order.

## Frozen objective

Targets are normalized by their measured magnitudes. H-2 gives equal weight to
binding, magnetic dipole, and electric quadrupole residuals. H-3 and He-3 give equal
weight to binding and magnetic residuals. Conservation and exclusion penalties are
lexicographically prior: an invalid pose cannot win by matching a target.

No charge-radius term and no spin/parity term may be added during this run.

## Output

The executed output will be written to `nseq17_results.json`; conclusions will be
recorded in `NSEQ17_ASSESSMENT.md` only after all registered checks run.

## Execution — 2026-08-16

`node nseq17_wake_mesh_validate.js`

- instrument validation completed before isotope evaluation;
- H-2: `CALIBRATED(6)`;
- H-3: `CALIBRATED(7)`;
- He-3: `CALIBRATED(7)`;
- deterministic parameter residual: `0`;
- maximum divergence residual: `2.65e-15`;
- maximum magnetic-route disagreement: `3.963%`;
- all registered checks: consistent.

Assessment: `NSEQ17_CALIBRATION_CONSISTENT`.

## Repair execution — 2026-08-16

The preceding execution used a reversed Hydrogen wake scaled from the measured neutron
moment and retained undeformed free-Hydrogen wake templates in every composite. It is
superseded by `PROMPT_REPAIR.md`.

The repaired instrument was run with:

`node nseq17_wake_mesh_validate.js`

Results:

- free neutron: `CALIBRATED(1)`;
  - proton-form contribution: `+2.7928473446 μN`;
  - seated-electron counter-contribution: `−4.7058901046 μN`;
  - net: `−1.9130427600 μN`;
  - net/gross suppression: `25.51%`;
- H-2: `CALIBRATED(8)`;
- H-3: `CALIBRATED(9)`;
- He-3: `CALIBRATED(9)`;
- deterministic parameter residual: `0`;
- maximum relative divergence: `3.01e-15`;
- maximum magnetic-route disagreement: `1.650%`;
- wake compliance is non-zero for every fitted composite;
- throat/poloidal division is `0.80/0.20` (H-2), `0.10/0.90` (H-3), and
  `0.45/0.55` (He-3), each retaining an exact unit sum;
- binding uses the signed `-∫U_i·U_j dV` field cross-term on the frozen
  `5×5×7` integration stencil; the segment-proximity surrogate is absent;
- every repaired rejection check: consistent.

Repaired assessment: `NSEQ17_CALIBRATION_CONSISTENT`.

## Validation environment

- NSEQ17 calibration validator: **PASS**.
- NSEQ16 headless sequencer/browser wiring and Release/docs parity: **PASS**.
- Canonical `laws.hpp` versus Release export, and Release versus docs export:
  **byte-identical**.
- C++ benchmark execution: **not run** — this checkout has no root benchmark
  CMake target, no existing `sdt-benchmarks.exe`, and neither `cl` nor `g++`
  is available in the current environment.
