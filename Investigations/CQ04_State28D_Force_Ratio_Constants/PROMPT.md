# CQ04: State28D Force Ratio Hardcoded Amplification — Codebase Question

## THE QUESTION
In state28d.hpp (line 168): `const double cmb_amplification = 1e30;`

This is a HARDCODED magic number in the force_ratio_coulomb_to_gravity function. The comment says "CMB pressure amplification factor for Coulomb (~10³⁰)." But WHERE does 10³⁰ come from? It is not derived from any SDT quantity.

## Context
The function calculates F_Coulomb / F_gravity ≈ 10³⁹ for proton-electron:
- ρ_eff_coulomb ≈ 1 (no screening)
- ρ_eff_gravity ≈ 0.36 × 10⁻⁹ (heavy screening, κ = 10⁻⁹)
- Ratio ≈ (1 / 3.6×10⁻¹⁰) × 10³⁰ ≈ 2.8×10³⁹ ✓

But both the κ_factor (10⁻⁹) and the cmb_amplification (10³⁰) are fitted constants, not derived.

## INVESTIGATION PROMPT

### Target
Either derive these constants from SDT principles or replace them with derivable quantities.

### Key Relationships
1. κ (screening factor) should relate to the occlusion geometry: κ = (V_disp / V_total)^n for some n?
2. The "CMB amplification" should be: P_conv / P_background × (geometric factor)?
3. The overall ratio F_C/F_g = 10³⁹ must be derivable from:
   - R_p / R_excl_p (wake-to-body ratio for proton)
   - R_charge / R_excl_p 
   - Some combination of measured quantities

### What Needs Fixing
The State28D force ratio function has placeholder constants. Replace:
- `cmb_amplification = 1e30` with a derived expression
- `kappa_factor = 1e-9` with a derived expression
- Or demonstrate that these ARE the correct values from first principles

### Success Criteria
- [ ] Both constants derived from existing SDT quantities
- [ ] The 10³⁹ Coulomb/gravity hierarchy reproduced WITHOUT fitted parameters
- [ ] state28d.hpp updated with the derived expressions
