# RUN_LOG — CH04 Molecular Geometry (VSEPR) from Wake Balance

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-05. **Status:** pre-commit written BEFORE coding.

## Grounding

NP17 frame: a bond direction = a shared-electron seat (partially engaged across the gap); a lone
direction = an unshared seat (fully active). The geometry question is pure machinery: N weighted
unit directions on a sphere, pairwise Law III occlusion energy, minimise. NO hybridisation, NO
target angles as input — the minimiser must produce every angle. Angles are OUTPUT ONLY.

## Faith ledger (§G.1)

1. Kernel: pairwise energy w_i·w_j / |u_i − u_j| (chord form of the 1/r occlusion energy between
   wake signatures on the unit sphere). Named as faith: the radial placement of the wake centroid
   is collapsed to a unit sphere — the angular-window (poloidal-rim) structure is NOT modelled.
2. Multiple bond = integer-fatter wake (double = weight 2 of a single). Grammar, not fitted.
3. One ratio w_lone/w_bond — the CALIBRATED(1) knob the prompt allows. Chosen by scan against
   NH₃ + H₂O jointly; every other number (including all of P1, P3, P4) uses that single value.

## Pre-Run Commitments — CH04

- Prompt completion target: C (expected landing)
- Physics class hoped: CONVERGENCE; honest FAIL/OPEN accepted where the minimiser misses
- CALIBRATED budget: 1 (w_lone/w_bond)
- Phase thresholds (before run):
  - P1 equal wakes: N=2→180°, N=3→120°, N=4→109.47°, N=6→90° all within 1°; N=5 → the {90,120,180} set
  - P2 ONE ratio: NH₃ bond-bond = 107.0±1° AND H₂O bond-bond = 104.5±1°
  - P3 same ratio: SF₄ lone lands equatorial (seesaw), ClF₃ lones equatorial (T-shape), XeF₄ lones
    trans (square planar), CO₂ 180°, H₂CO: HCH < HCO with fat C=O — qualitative, computed
  - P4 novel outliers with the SAME ratio, no refit: H₂S (measured 92.1°), PH₃ (93.5°); committed
    honesty trigger: miss > 5° ⇒ fit-only, cap C (the model carries no central-atom dependence,
    so a miss here is EXPECTED and will be reported, not hidden)
- Forbidden: second knob; per-molecule refit; assuming any target angle; retro-widening.

## Run record

- Tool: `ch04_wake_geometry.py` (projected-gradient minimiser, 60 random restarts per case)
- Output: `results.txt` = verbatim stdout.
