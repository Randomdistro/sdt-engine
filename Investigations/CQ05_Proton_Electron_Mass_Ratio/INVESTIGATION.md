# CQ05: Proton-Electron Mass Ratio — INVESTIGATION RESULTS

> **Status**: OPEN (BLOCKED)
> **Date**: May 2026
> **Dependencies**: 3D lattice perturbation solver for torus knot displacement volumes

---

## Question
Can m_p/m_e = 1836.15 be derived from the W=3 vs W=1 equilibrium?

## Answer: NOT YET — Requires V_disp(p,q)

From Law IV: m_p/m_e = V_disp_p/V_disp_e. CQ02 shows the torus GEOMETRY is fully determined by (p,q), but the displacement volume extends beyond the torus surface via the wake. Solving for V_disp requires the full 3D lattice perturbation around each knot type.

### What IS Known
- The torus volume ratio V_torus_p/V_torus_e ≈ 10⁻¹⁰ (proton is much smaller)
- Therefore V_disp ≠ V_torus — the wake contribution dominates
- 6π⁵ = 1836.12 matches m_p/m_e to 0.002% (numerical coincidence or identity?)
- The g-numbers (CQ03) give g_p/g_e = 4/α ≈ 548 (not directly the mass ratio)

### What IS Blocked
- V_disp as function of (p,q) knot type
- Wake volume integration for trefoil vs unknot
- Self-consistent mass ↔ radius ↔ V_disp coupling

## Verdict

**CQ05 OPEN.** This is the hardest open problem in SDT — connecting topology to mass. Forward dependency: a 3D lattice perturbation solver for torus knot wake volumes.
