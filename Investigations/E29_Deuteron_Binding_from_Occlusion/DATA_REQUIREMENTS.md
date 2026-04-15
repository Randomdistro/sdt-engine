# E29: Deuteron Binding from Occlusion Geometry — Data Requirements

## Measured Constants (from laws.hpp)
| Quantity | Value | Source |
|----------|-------|--------|
| P_eff | 5.225×10³¹ Pa | laws.hpp law_III |
| R_p (proton charge radius) | 0.8414 fm | CODATA 2018 / muonic H |
| r_e (classical electron radius) | 2.8179 fm | CODATA 2018 |
| Deuteron binding energy B_d | 2.22457 MeV | AME2020 |
| Deuteron charge radius | 2.1421 fm | CODATA 2018 |
| Deuteron magnetic moment | 0.8574 μ_N | CODATA 2018 |
| Proton-neutron separation in deuteron | ~2.14 fm | Measured |
| Neutron charge radius (rms) | 0.0 (overall), −0.1161 fm² (mean square) | PDG |

## SDT Quantities
| Quantity | Formula | Source |
|----------|---------|--------|
| F_occlusion | (π/4) P_eff R₁² R₂² / r² | law_III |
| V_disp (proton) | 1.834×10⁻⁵⁸ m³ | law_IV |
| V_disp (neutron) | ~same as proton (1% heavier) | law_IV |
| R_excl (proton) | 3.525×10⁻²⁰ m | law_IV |
| Neutron wake radius | ℏ/(m_n c) = 0.2100 fm | W+1: W=3 → 4ℏ/(m_n c) ≈ 0.840 fm |

## Required Calculations
1. Compute F_occlusion(R_p, R_n_equiv, r=2.14 fm)
2. Integrate F·dr from r=2.14 fm to ∞ → binding energy
3. Compare to measured 2.224 MeV
4. Assess whether neutron and proton have same R_wake for occlusion purposes
5. Determine if the ℓ≥3 (nuclear) wake contribution needs separate accounting
