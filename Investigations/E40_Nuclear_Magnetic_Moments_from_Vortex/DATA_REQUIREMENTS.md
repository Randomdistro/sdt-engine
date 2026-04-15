# E40: Nuclear Magnetic Moments from Vortex Geometry — Data Requirements

## Measured Magnetic Moments (CODATA 2018 / PDG)
| Particle | μ (μ_N) | Source |
|----------|---------|--------|
| Proton | +2.792847 | CODATA |
| Neutron | −1.913043 | CODATA |
| Deuteron | +0.857421 | CODATA |
| Triton | +2.979 | CODATA |
| Helion (He-3) | −2.128 | CODATA |
| Alpha (He-4) | 0.0 | Spin-0 |

## Extended Magnetic Moments for Nuclei
| Source | Content |
|--------|---------|
| Stone (2019) compilation | Measured μ for ~800 nuclear ground states |
| NNDC evaluated data | Ground state spins and moments |
| IAEA ENSDF | Full level scheme moments |

## SDT Model Parameters
| Quantity | Formula | Source |
|----------|---------|--------|
| Nuclear magneton μ_N | eℏ/(2m_p) | Definition |
| Proton circulation: v_circ | √(c² − v²) at rest → c | law_V |
| ℓ=2 wake = magnetic dipole | Toroidal + poloidal circulation | Theory/01_Closure |
| W=3 trefoil topology | 3 poloidal loops per toroidal circuit | winding namespace |
| μ = f(W, v_T, v_P, R, a) | To be derived | THIS INVESTIGATION |

## Specific Predictions Needed
1. μ_proton from W=3 trefoil geometry
2. μ_neutron from W=3 trefoil (uncharged variant — no ℓ=1 but HAS ℓ=2)
3. μ_deuteron from p+n geometric addition
4. μ_triton from p+2n geometry
5. μ_helion from 2p+n geometry
6. Predict sign and magnitude for all 5 light nuclei
