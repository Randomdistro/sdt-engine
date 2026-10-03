# E42+E49: Hubble Tension and Dark Energy — Data Requirements

## Observational Data
| Dataset | Source | Content |
|---------|--------|---------|
| Pantheon+ SN Ia catalogue | Scolnic et al. 2022 | 1701 SN Ia: z, m_B, x₁, c, host mass |
| CMB distance ladder | Planck 2018 | H₀ = 67.4 ± 0.5 km/s/Mpc |
| Local distance ladder | SH0ES (Riess 2022) | H₀ = 73.04 ± 1.04 km/s/Mpc |
| BAO measurements | SDSS/BOSS/eBOSS | D_A(z), D_H(z) at z = 0.15–2.33 |
| DESI BAO (2024) | DESI Collaboration | Updated BAO at z = 0.3–2.3 |

## SDT Model Parameters
| Quantity | Formula | Source |
|----------|---------|--------|
| Strain rate σ₀ = H₀/c | ~7.3–7.9 × 10⁻²⁷ m⁻¹ | cosmology.hpp |
| Pressure gradient redshift | z = exp(σ₀ d) − 1 | SDT (replaces expansion) |
| Distance-dependent H: H(d) | σ(d) × c | SDT prediction |
| σ_CMB vs σ_local | Convergence gradient steepness | cosmology.hpp strain namespace |

## Key SDT Predictions
1. H₀ is NOT a constant — it's a local measurement of the pressure gradient
2. H₀(near) > H₀(far) because the local gradient is steeper near massive structures
3. There is NO acceleration — apparent acceleration is a misinterpretation of the non-linear pressure gradient
4. The 8.4% Hubble tension is EXPECTED: the CMB and local measurements sample different parts of the gradient
