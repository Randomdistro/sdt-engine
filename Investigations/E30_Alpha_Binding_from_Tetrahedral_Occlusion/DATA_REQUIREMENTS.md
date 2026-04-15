# E30: Alpha Binding from Tetrahedral Occlusion — Data Requirements

## Measured Constants
| Quantity | Value | Source |
|----------|-------|--------|
| B_alpha (He-4 binding) | 28.296 MeV | AME2020 |
| B_triton (H-3 binding) | 8.482 MeV | AME2020 |
| B_helion (He-3 binding) | 7.718 MeV | AME2020 |
| B_deuteron (H-2 binding) | 2.224 MeV | AME2020 |
| He-4 charge radius | 1.6755 fm | Angeli & Marinova |
| SDT prediction: R_He = 2×R_p | 1.6828 fm | laws.hpp nuclear |
| He-4 magnetic moment | 0.0 μ_N | Measured (spin-0) |
| He-4 spin/parity | 0⁺ | Measured |

## SDT Grammar
| Quantity | Value | Source |
|----------|-------|--------|
| He-4 grammar | 1 alpha core, 0 d, 0 t | ATOMICUS |
| Internal structure | 2p + 2n in tetrahedral arrangement | SDT conjecture |
| Number of p-n bonds | 4 (each p bonds to 2 n, each n bonds to 2 p) | Tetrahedron edges |
| Number of p-p bonds | 1 | Tetrahedron edge |
| Number of n-n bonds | 1 | Tetrahedron edge |
| Total edges | 6 | Complete graph K₄ |

## Required from E29
| Quantity | Source |
|----------|--------|
| Single p-n occlusion bond energy | E29 result |
| P_eff nuclear correction (if needed) | E29 result |
| Neutron effective radius for occlusion | E29 result |
