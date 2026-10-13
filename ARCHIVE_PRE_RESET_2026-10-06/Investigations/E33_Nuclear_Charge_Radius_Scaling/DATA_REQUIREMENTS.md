# E33: Nuclear Charge Radius Scaling — Data Requirements

## Measured Charge Radii
| Source | Content | Count |
|--------|---------|-------|
| Angeli & Marinova 2013 compilation | R_ch for ~900 isotopes | All stable + long-lived |
| NIST nuclear charge radius table | Same data, NIST formatting | Cross-check |
| Muonic atom spectroscopy (recent) | R_ch for H, D, He-3, He-4 | High precision |

## SDT Prediction
| Scaling law | Formula | Free parameters |
|-------------|---------|-----------------|
| SDT | R_ch = Z × R_p = Z × 0.8414 fm | 0 (R_p is measured) |
| Standard | R_ch = r₀ × A^(1/3), r₀ ≈ 1.2 fm | 1 (r₀ is fitted) |

## Required Data Table (minimum 80 isotopes)
For each stable isotope with measured R_ch:
- Z, A, N, measured R_ch ± uncertainty
- SDT predicted: Z × R_p
- Standard predicted: r₀ × A^(1/3)
- Residual for each model

## Specific Tests
| Test | Data needed |
|------|------------|
| Light nuclei (Z=1–10) | Precise R_ch from muonic atoms |
| Magic number nuclei | R_ch at Z=2,8,20,28,50,82 |
| Isotope chains (same Z, different A) | R_ch vs A at fixed Z |
| Proton-drip proximity | Very neutron-rich or neutron-poor R_ch |
| Deformed nuclei | R_ch for rare earths (Z=60–70) where deformation is large |
