# PPT06: Spation Traction from the Trefoil — How the Gears Start

> **Classification**: Theoretical derivation (pure)
> **Target**: Derive the traction, rotation, and orbital entrainment imparted to the spation lattice by the proton's (2,3) trefoil knot

## The Question

The proton is a W=3 trefoil circulating at c. The phase velocity imposed on contact spations at R_p is v_phase = c/k_surface = c/0.5464 = 1.831c — superluminal. The lattice cannot relay faster than c. What happens to the velocity deficit?

## Key Results

1. **Traction ratio** T = ω_demand/ω_max = 3(W+1) = 12 — the trefoil demands 12× the lattice's angular capacity
2. **Three output channels**: traction (ℓ=1 Coulomb), rotation (ℓ=2 magnetic), entrainment (ℓ≥3 orbits)
3. **Gear ratio** nuclear → atomic = ω_p/ω_e ≈ 10⁸ — the lattice carries the rotation from fm to pm scale
4. **Ontic vs kinetic**: CMB convergence is the fuel; trefoil circulation is the engine

## Inputs

- `laws.hpp:450-453`: k_proton_surface = 0.5464
- `CQ11_Trefoil_Confinement`: stable budget angle sin²θ* = 1/3
- `Theory/01_Closure_Derivations.md`: wake tensor ℓ-expansion

### Success Criteria
- [x] v_phase = 1.831c at proton surface derived
- [x] 6π total winding angular demand computed
- [x] Traction ratio T = 12 = 3(W+1) verified
- [x] Three channels identified and connected to wake multipoles
- [x] Gear ratio nuclear→atomic = ~10⁸ computed
- [x] Ontic/kinetic distinction formalised

### Completed: May 2026
See `INVESTIGATION.md` for the full derivation and `cq14_spation_traction.cpp` for computational verification.
