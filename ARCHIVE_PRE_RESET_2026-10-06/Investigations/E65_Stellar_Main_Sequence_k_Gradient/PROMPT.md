# E65: Stellar Main Sequence from k-Gradient — Data/Prompt

## DATA REQUIREMENTS

| Data | Source | Content |
|------|--------|---------|
| GAIA DR3 HR diagram | ESA GAIA | L, T_eff, R for ~10⁶ stars |
| Stellar orbital velocities | Binary surveys / spectroscopic | Surface/orbital v for k computation |
| Main sequence L-M relation | Eker et al. 2018 | L ∝ M^3.5 |
| Stellar radii compilation | Torres et al. 2010 | R vs M for MS stars |
| Solar k value | k_Sun = 686.3 | laws.hpp bridge |
| Solar R, L, T_eff | IAU 2015 nominal | Calibration point |

## INVESTIGATION PROMPT

**Target**: Map the main sequence to a k-gradient equilibrium sequence.

### SDT Prediction

Each star has a k-value: k = c / v_surface (where v_surface is the escape/orbital velocity at the stellar surface). Hot blue stars have low k (strong convergence — compact, massive), cool red stars have high k (weak convergence — diffuse, low-mass).

The main sequence should be a CONTINUOUS k-sequence. Compute k for each spectral class:
- O star (v_esc ~ 1000 km/s): k ≈ 300
- B star: k ≈ 400  
- Sun (G2V): k = 686.3
- M dwarf (v_esc ~ 200 km/s): k ≈ 1500

### Methodology

1. For each star with measured M, R, L: compute k = c / √(2GM/R)
2. Plot k vs L, k vs T_eff, k vs M
3. Is the main sequence a monotonic function of k?
4. Does the mass-luminosity relation L ∝ M^3.5 emerge from the k-gradient?
5. Does the pressure domain radius (r_domain = √(L / 4π F_CMB)) correlate with the star's Roche lobe in binary systems?

### Success Criteria
- [ ] k computed for ≥50 main sequence stars spanning O–M
- [ ] MS is a monotonic k-sequence 
- [ ] L vs k relationship identified (power law? exponential?)
- [ ] Solar k = 686.3 sits correctly on the sequence
