# E99: Ocean Tidal Analysis — SDT Pressure vs Newton Potential — Data/Prompt

## DATA REQUIREMENTS
| Data | Source |
|------|--------|
| Global tidal harmonic coefficients (M2, S2, N2, K1, O1) | FES2014 / GOT4.10 |
| Earth-Moon orbital parameters | JPL Horizons |
| Earth-Sun orbital parameters | JPL Horizons |
| Measured tidal amplitudes at ≥20 stations | NOAA/IOC tide gauges |
| Love numbers (h₂, k₂, l₂) | IERS |

## INVESTIGATION PROMPT

**Target**: Compute tidal forcing from SDT convergence gradient and compare to Newtonian tidal potential.

### SDT Tidal Model
Tides arise from the GRADIENT of convergence pressure across Earth's diameter:
- The Moon creates a convergence deficit (occlusion) that is stronger on the near side than the far side
- This differential pressure → tidal bulge
- SDT predicts: F_tidal = d/dr [F_occlusion] × (R_Earth)

$$F_{\text{tidal}} \propto \frac{R_1^2 R_2^2}{r^3} \times R_{\text{Earth}}$$

This has the SAME r⁻³ dependence as the Newtonian tidal force (since Newtonian tidal ∝ GM/r³). The SDT tidal amplitude should match the measured M2 amplitude.

### Methodology
1. Compute the SDT tidal force differential across Earth's body for the Moon
2. Compare M2 amplitude prediction to measured ~0.63 m mean
3. Compute same for the Sun (S2 component)
4. Check the M2/S2 ratio — should be ~2.17 (Moon/Sun tidal ratio)

### Success Criteria
- [ ] M2 tidal amplitude predicted within 10%
- [ ] M2/S2 ratio matches measured value
- [ ] SDT tidal force reduces algebraically to the Newtonian tidal expression
