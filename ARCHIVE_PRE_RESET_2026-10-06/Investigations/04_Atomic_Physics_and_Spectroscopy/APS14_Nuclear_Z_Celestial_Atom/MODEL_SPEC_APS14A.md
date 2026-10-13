# APS14a — Angular Occlusion Emission

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-13  
**Status:** calibrated investigation; no canon edit

APS14a preserves APS14 and adds explicit lower/upper configurations, complete
orbital pathway observables, axis/around/diagonal seat templates, phase
minimisation, swept pair occlusion, and companion relaxation.

For each seat:

```text
L = 2 pi r
T = L/v
Omega = v/r
m_e v L = 2 pi hbar n_eff
```

For an active transition:

```text
R_L = L_upper/L_lower
DeltaE_path = B_lower (1 - 1/R_L)
B_lower = 0.5 m_e c^2 z_lower
```

This is exactly the one-electron Rydberg depth difference because
`L~n^2/Z`. Multi-electron states obtain `R_L` from the re-solved pair-occluded
geometry. A4 adds the computed movement-budget change of unchanged companion
seats.

The nested ladder is:

1. `A0_TRANSITION_FIX`: corrected configurations, APS14 endpoint energy.
2. `A1_PATHWAY`: complete-path ratio with APS14 Fibonacci directions.
3. `A2_AXIS_AROUND`: `s` up/down, `p` around, `d` diagonal templates.
4. `A3_ANISOTROPIC_OCCLUSION`: one global orientation coefficient `eta`.
5. `A4_CORE_DEPTH`: companion relaxation and bounded core-shadow coefficient
   `rho`.

No measured line enters a forward state after global coefficients are fixed.
H-like rows are controls only. Neutral-line partitions are by whole element.
