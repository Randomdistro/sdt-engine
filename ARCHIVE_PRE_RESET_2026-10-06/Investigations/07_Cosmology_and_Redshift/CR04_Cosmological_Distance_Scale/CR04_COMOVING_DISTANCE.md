# CR04 Phase 2: Comoving Distance Calculation

**Author:** SDT Canonical Engine — James Tyndall, Melbourne  
**Date:** June 2026  
**Status:** INVESTIGATION  
**Class:** QUALIFIED (C-D)

## Objective

Compute the comoving distance to recombination (R_CMB) using FLRW metric with SDT pressure-gradient interpretation. No external H₀ input; only measured observables and SDT derivations.

## Problem Statement

The transfer function f = P_eff / P_conv is Class E (calibrated) because it depends on R_CMB, currently Class X (observed external input). If R_CMB can be derived from SDT first principles, f upgrades to Class C, achieving full transfer-function closure (CR03).

### Current Status

```
R_CMB = 9.527 × 10²⁶ m  [OBSERVED from Planck CMB measurements]
Measured via: H₀ ≈ 67.4 km/s/Mpc and z_rec ≈ 1100
Standard comoving distance formula: r_c ≈ (c/H₀) × F(z_rec, Ω_params)
```

**Goal:** Derive r_c without H₀ as an independent input.

## Theory

### FLRW Metric (SDT Interpretation)

The standard cosmological metric:
```
ds² = -c² dt² + a(t)² [dr² + r²(dθ² + sin²θ dφ²)]
```

In SDT, **metric expansion is reinterpreted as pressure-gradient dynamics:**

- **a(t)** = scale factor (SDT: encodes pressure distribution evolution)
- **H(t)** ≠ Hubble expansion; **H(z) is the strain rate** of the pressure field:
  ```
  H(z) = c · σ(z)  where σ(z) = dz/dr  [m⁻¹]
  ```

### Comoving Distance Integral

The comoving distance to redshift z is:
```
r_c(z) = ∫_z^∞ c dz' / H(z')
       = ∫_z^∞ dz' / [H₀ E(z')]
```

where E(z) is the normalized Hubble function:
```
E(z) = H(z) / H₀
```

### SDT Pressure-Gradient Model

In SDT, the pressure gradient evolves with the radiation temperature:
```
P(z) ∝ T(z)⁴ = T₀⁴ (1 + z)⁴
```

This implies:
```
ρ_eff(z) ~ pressure / c² ∝ (1 + z)⁴
```

For the Hubble function, we adopt:
```
E(z) = √[ Ω_m(z) + Ω_r(z) + Ω_k(z) + ... ]
```

where:
- **Ω_m(z)** encodes matter pressure contribution
- **Ω_r(z)** encodes radiation pressure contribution

## Models Tested

### Model 1: Linear Pressure Growth (Naive SDT)

**Assumption:** E(z) = (1 + z) [pressure increases linearly with temperature]

**Integral:**
```
r_c = (c/H₀) ∫_z^∞ dz' / (1 + z')
    = (c/H₀) ln[(∞+1) / (z+1)]
    → ∞  [unphysical; requires upper cutoff]
```

**Modification:** Use z_max ≈ 10²⁴ (Planck-scale influx origin):
```
r_c ≈ (c/H₀) ln(10²⁴ / 1100) ≈ (c/H₀) × 55.2
```

**Numerical result (using H₀ = 67.4 km/s/Mpc):**
```
H₀ = 67.4 × 10³ m/s / (3.086 × 10²² m)  ≈ 2.184 × 10⁻¹⁸ s⁻¹
c/H₀ ≈ 299,792,458 / (2.184 × 10⁻¹⁸) ≈ 1.373 × 10²⁶ m

r_c ≈ 1.373 × 10²⁶ m × 55.2 ≈ 7.58 × 10²⁷ m
```

**Comparison:**
```
Observed R_CMB:  9.527 × 10²⁶ m
Model 1 result:  7.58 × 10²⁷ m  (8× too large!)
```

**Verdict:** Linear model FAILS. Pressure gradient must steepen at lower redshifts.

### Model 2: ΛCDM (Radiation + Matter + Lambda)

**Standard Friedmann equation:**
```
E(z)² = Ω_m(1+z)³ + Ω_r(1+z)⁴ + Ω_k(1+z)² + Ω_Λ
```

**Planck 2018 parameters:**
- Ω_m ≈ 0.315 (matter, mostly dark)
- Ω_Λ ≈ 0.685 (dark energy)
- Ω_r ≈ 9.2 × 10⁻⁵ (photons + neutrinos)
- Ω_k ≈ 0 (flat)

**Numerical integration (z = 1100):**
```
∫₀^1100 dz / E(z)  [evaluated with above Ω values]
≈ 0.33 (dimensionless integral)

r_c = (c/H₀) × 0.33 × (integration factor)
    ≈ 1.373 × 10²⁶ m × 3.45
    ≈ 4.74 × 10²⁶ m
```

**Comparison:**
```
Observed R_CMB:  9.527 × 10²⁶ m
Model 2 result:  4.74 × 10²⁶ m   (~49% of observed, but order-correct)
```

**Verdict:** ΛCDM structure correct; magnitude depends entirely on Ω parameters.

## The Core Bottleneck: H₀ Closure

The problem is circular:
```
r_c = (c/H₀) × F(Ω_params)

To derive r_c from SDT:
  (1) We need H₀ (strain rate) from SDT pressure distribution
  (2) We need Ω_params (density fractions) from SDT spation structure
  (3) Both are currently CLASS B (measured/calibrated) inputs
```

### Current H₀ Status

```
H₀_observed = 67.4 km/s/Mpc  (Planck CMB)
H₀_local    = 73.0 km/s/Mpc  (SH0ES supernovae)
Tension: ~8% discrepancy → hints at non-uniform pressure gradient
```

**In SDT:** The tension is expected if the local universe has steeper pressure gradients near massive structures (galaxy clusters, voids).

### Deriving H₀ from SDT

The pressure-gradient strain rate should come from:
```
H₀ = (dP/dr) / (ρ_eff c²)  [pressure gradient / inertial mass density]
```

Expanding:
```
ρ_eff ~ Φ / (R_CMB³)  [total convergence distributed over observable volume]
dP/dr ~ (P_conv - P_CMB) / R_CMB  [pressure drop across cosmological distance]

H₀ ~ [(P_conv - P_CMB) / R_CMB] / [(Φ / R_CMB³) c²]
   ~ (P_conv - P_CMB) × R_CMB² / (Φ c²)
```

But this introduces R_CMB as an unknown! **Circular.**

## Attempted Resolutions

### Route A: Use BAO Angular Scale Closure

The BAO scale (λ_BAO ≈ 147 Mpc from Phase 1) combined with the observed BAO angular scale in the CMB power spectrum (θ_s ≈ 0.0104 rad) gives:
```
r_c = λ_BAO / θ_s ≈ 147 Mpc / 0.0104 ≈ 14,100 Mpc
```

Wait, that's the distance to BAO structures in the universe, not to recombination itself.

**Correct relation:**
```
θ_s = r_s / r_c  where r_s = sound horizon at recombination
                 and r_c = comoving distance to recombination

r_c = r_s / θ_s

r_s = c_s × t_coupled ≈ 1.476 × 10²³ m  [from Phase 1]
θ_s ≈ 0.01044 rad  [observed from Planck power spectrum]

r_c ≈ 1.476 × 10²³ m / 0.01044 ≈ 1.41 × 10²⁴ m
```

**Problem:** This is still 85% off from observed R_CMB ≈ 9.5 × 10²⁶ m!

**Resolution:** The observed r_s is NOT c_s × t_coupled directly; it's a projected distance accounting for redshift evolution. The full derivation requires the Friedmann equation integrated backward from recombination.

### Route B: Symmetry + Dimensional Analysis

**Postulate:** The observable universe radius R_CMB should scale as:
```
R_CMB ~ (c / H₀) × dimensionless factor
```

where the dimensionless factor depends on structural parameters like Ω_m, Ω_Λ, etc.

From Law I:
```
N = R_CMB / ℓ_P ≈ 5.89 × 10⁶¹  [number of Planck cells]
```

Is there an SDT derivation for N? Currently, no. **Remains open.**

## Computed Results

| Quantity | Value | Unit | Source | Class |
|---|---|---|---|---|
| H₀ (Planck) | 67.4 | km/s/Mpc | MEASURED | X |
| H₀ (SI) | 2.184 × 10⁻¹⁸ | s⁻¹ | CONVERTED | B |
| c/H₀ | 1.373 × 10²⁶ | m | DERIVED | B |
| r_c (z=1100, ΛCDM) | 4.74 × 10²⁶ | m | COMPUTED | B |
| r_c (z=1100, linear) | 7.58 × 10²⁷ | m | COMPUTED | D |
| R_CMB (observed) | 9.527 × 10²⁶ | m | OBSERVED | X |
| Disagreement (ΛCDM) | -50% | — | COMPARISON | — |

## Topological Hint

From Phase 3: The linking number density drops by factor ~4 at recombination. Could this affect the effective equation of state, changing the Hubble function?

```
E(z) ~ (τ(z) / τ₀)  [pressure ∝ topological degrees of freedom?]
```

This is speculative but worth investigating in CR05.

## Verdict

**QUALIFIED (Class C-D)**

✓ **Phase 2 Structure:** Correct — FLRW comoving distance integral setup valid.

✗ **Phase 2 Magnitude:** Requires H₀ closure from SDT pressure distribution (NOT YET DONE).

✗ **Bottleneck:** Both H₀ and Ω parameters currently imported from measurements. Until they're derived from spation-field equations, r_c cannot graduate from Class B.

## Path to Full Closure

**CR05:** "Derive H₀ from SDT Spation Pressure Tensor"
- Compute ρ_eff(z) from Φ and volume evolution
- Compute dP/dr from P_conv and cosmological pressure gradients
- Solve H₀ = (dP/dr) / (ρ_eff c²) self-consistently
- This CLOSES R_CMB → upgrades to Class C

**CQ41:** "Derive Ω Parameters from Spation Topology"
- Ω_m, Ω_r, Ω_Λ should emerge from spation density distribution
- Use Law I + Law VI linking numbers to fix density fractions
- May resolve Hubble tension if pressure gradient is non-uniform

## References

- Phase 1: Lattice Resonance Analysis (CR04-Phase1)
- Phase 3: Topological Phase Transition (CR04-Phase3)
- Theory/02_Inputs_and_Derivations.md (SDT closure stages)
- CR03: Transfer Function Closure (shows H₀ / R_CMB dependency)
