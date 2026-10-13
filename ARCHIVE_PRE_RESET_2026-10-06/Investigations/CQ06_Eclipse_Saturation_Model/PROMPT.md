# CQ06: Eclipse Saturation Model Implementation — Codebase Question

## THE QUESTION
E46 (galaxy rotation curves) references galactic.hpp for the eclipse saturation model, but this file DOES NOT EXIST in the codebase. The Engine only has: laws.hpp, cosmology.hpp, neutrino.hpp, magnetosphere.hpp, state28d.hpp.

The eclipse saturation model is referenced but NEVER implemented. This is a critical gap — the galaxy rotation curve prediction (SDT's answer to dark matter) has no computational implementation.

## INVESTIGATION PROMPT

### Target
Design and derive the eclipse saturation model mathematically, then implement it.

### What Needs to Be Derived
1. **Convergence occlusion by an extended disk**: For an observer at radius r in the galactic plane, what fraction of the 4π sky is occluded by the disk?
   - Ω_disk(r) = f(Σ(r'), h, z₀, r) integrated over the disk
   
2. **Saturation criterion**: At what radius does Ω_disk → 2π (half the sky)?
   - r_sat = function of disk mass, scale length, and thickness
   
3. **Rotation velocity from occlusion**:
   - v(r)² = (c²/k²) × Ω_disk(r) / (4π) × R_gal / r
   - Below saturation: v ∝ √(M(< r)/r) — Keplerian rise
   - At saturation: v → constant — flat curve

4. **The normalization**: What determines v_flat?
   - v_flat² = (c²/k²) × (1/2) × R_gal / r_sat
   - v_flat should depend only on total baryonic mass → BTFR

### Implementation in C++
A new galactic.hpp should provide:
- `eclipse_fraction(r, disk_profile)` — solid angle computation
- `rotation_velocity(r, disk_profile)` — from eclipse model
- `v_flat(total_mass, scale_length)` — flat velocity prediction
- `btfr_prediction(log_mass)` — Baryonic Tully-Fisher prediction

### Success Criteria
- [ ] Mathematical model fully derived 
- [ ] Implemented in galactic.hpp following existing engine patterns
- [ ] Tested against 10 SPARC galaxies
- [ ] BTFR slope = 4 reproduced
