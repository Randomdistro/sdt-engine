# E101: Complete Convergence Budget of the Solar System — Data/Prompt

## DATA REQUIREMENTS

| Body | v_orbital (km/s) | k = c/v | R (m) | Source |
|------|-------------------|---------|--------|--------|
| Sun | — (source) | 686.3 | 6.957e8 | IAU 2015 |
| Mercury | 47.87 | 6263 | 2.440e6 | JPL |
| Venus | 35.02 | 8563 | 6.052e6 | JPL |
| Earth | 29.78 | 10066 | 6.371e6 | JPL |
| Mars | 24.08 | 12451 | 3.390e6 | JPL |
| Jupiter | 13.07 | 22935 | 6.991e7 | JPL |
| Saturn | 9.68 | 30969 | 5.823e7 | JPL |
| Uranus | 6.80 | 44087 | 2.536e7 | JPL |
| Neptune | 5.43 | 55215 | 2.462e7 | JPL |

| Quantity | Formula | Purpose |
|----------|---------|---------|
| z = 1/k² | Bridge law | Convergence coupling per body |
| ϟ = R/k² | c-boundary | Size of c-boundary |
| GM = c²R/k² | Bridge | Equivalence check |
| Pressure domain | √(L/(4π F_CMB)) | Sun's domain vs Oort cloud |
| v × r = const? | Kepler check | Verify v ∝ 1/√r across system |

## INVESTIGATION PROMPT

**Target**: Compute the complete k-hierarchy and convergence budget for the solar system using SDT's bridge law.

### Methodology

1. For each planet: compute k from orbital velocity, verify z × k² = 1
2. Verify v(r) = (c/k_Sun)√(R_Sun/r) for each planet
3. Compute ϟ (c-boundary) for each body — where does v_orbital = c?
4. Compute the total convergence budget: sum of all z values → total displacement fraction
5. Verify: the Sun's pressure domain (r_domain ≈ 20,800 AU) matches the Oort cloud inner edge
6. Compute convergence contribution of each planet at Earth's orbit → are any significant?
7. Map the k-hierarchy: Sun → planets → moons → asteroids

### Specific predictions
- Jupiter's convergence contribution at Earth ≈ (R_J/r_JE)² × z_J × (solid angle)
- Does the combined planetary convergence explain the ~10⁻⁸ residual in Earth's orbit?
- Does the k² ratio between adjacent planets show integer patterns (E21 from Jovian investigation)?

### Success Criteria
- [ ] z × k² = 1 verified for every planet to machine precision
- [ ] v(r) = (c/k)√(R/r) reproduces all orbital velocities to < 0.1%
- [ ] Solar pressure domain matches Oort cloud to within factor of 2
- [ ] Complete convergence budget tabulated
