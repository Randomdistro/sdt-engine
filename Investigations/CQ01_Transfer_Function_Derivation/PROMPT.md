# CQ01: Transfer Function f Derivation — Codebase Question

## THE QUESTION
In laws.hpp (line 200): `f_transfer = P_eff / P_conv = 2.125e-17`

This is DERIVED from the hydrogen calibration:
- P_eff = 4 k_e e² / (π R_p² r_e²) = 5.225×10³¹ Pa
- P_conv = N × u_CMB = 2.459×10⁴⁸ Pa
- f = P_eff / P_conv

But IS f truly derivable, or is it a fitted parameter disguised as a derivation?

## The Concern
P_eff is calibrated from the hydrogen atom: the known Coulomb force k_e e²/r² is equated to (π/4) P_eff R_p² r_e² / r². This DEFINES P_eff from the Coulomb identity. Then f = P_eff / P_conv.

So f is NOT independently derived — it's extracted from requiring SDT to reproduce the known Coulomb force. The question is: is f UNIVERSAL? Does the same f that gives the Coulomb force also give:
1. The gravitational force between macroscopic bodies?
2. The nuclear binding force?
3. The correct Casimir force?

## INVESTIGATION PROMPT

### Step 1: What f actually IS
Show explicitly: f = α ℏ c / (π R_p² r_e² P_conv) = 2.125×10⁻¹⁷

### Step 2: Universality test
- Apply f to gravity: F_grav = f × P_conv × (geometric factor involving V_disp). Does this give the correct G?
- Apply f to Casimir: the Casimir force is convergence occlusion at plate scale. Does f give the correct Casimir force at measured plate separations?
- Apply f to nuclear: does the same f give reasonable nuclear binding when applied with the ℓ≥3 wake?

### Step 3: Can f be derived from lattice properties?
f = P_eff / P_conv ≈ 10⁻¹⁷. Is this related to:
- (ℓ_P / R_p)^n for some n?
- (ℓ_P / r_e)^n?
- α^n?
- Some combination of fundamental scales?

### Success Criteria
- [ ] f shown to be universal (works for Coulomb, gravity, Casimir, nuclear) OR shown to be scale-dependent
- [ ] If universal: the universality is THE statement that all forces come from one pressure
- [ ] If scale-dependent: identify the function f(ℓ, r, topology)
