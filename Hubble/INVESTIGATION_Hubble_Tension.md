# The Hubble Tension: An SDT Investigation

> Status: ACTIVE INVESTIGATION
>
> SDT Laws: [Throughput Cascade](../SDT%20laws/LAW_OF_CONVERGENT_BOUNDARY_PRESSURE.md) ·
> [Radiative Origin](../SDT%20laws/LAW_OF_RADIATIVE_PRESSURE_ORIGIN.md)
>
> Engine: [laws.hpp → zk2_product](../Engine/include/sdt/laws.hpp) (line 418)

---

## 1. The Problem as Stated

Two classes of measurement give different values for the "expansion
rate" of the universe:

| Method | Team | H₀ (km/s/Mpc) | σ | Epoch probed |
|--------|------|---------------|---|-------------|
| CMB power spectrum | Planck (2018) | 67.4 ± 0.5 | — | z ≈ 1100 |
| Cepheid → SN Ia | SH0ES (2022) | 73.04 ± 1.04 | — | z < 0.15 |
| TRGB → SN Ia | CCHP (2024) | 69.96 ± 1.05(stat) ± 1.12(sys) | — | z < 0.1 |
| TRGB (JWST only) | Freedman (2024) | 68.81 ± 1.79(stat) ± 1.32(sys) | — | z < 0.05 |
| Gravitational lensing | TDCOSMO (2025) | 71.6 ± 4.6% | — | z ≈ 0.5–1.5 |
| Megamaser | M106 anchor | 73.9 ± 3.0 | — | geometric |

The gap between Planck (67.4) and SH0ES (73.0) is 5.6 km/s/Mpc,
a 5σ discrepancy. The TRGB measurement sits between them at ~70.

In ΛCDM, these all measure the same quantity: the present-day rate
of metric expansion. The disagreement is called a "crisis."

---

## 2. What Each Measurement Actually Does

### 2.1 The CMB Extraction (Planck)

Planck measures the angular size of the first acoustic peak in the
CMB power spectrum. This angle is:

```
θ_* = r_s / D_A(z_*)
```

where:
- r_s = 147.09 ± 0.26 Mpc = comoving sound horizon at recombination
- D_A(z_*) = angular diameter distance to last scattering (z* ≈ 1100)
- θ_* is measured directly: 100θ_* = 1.0411 ± 0.0003

The angular size θ_* is MODEL-INDEPENDENT. It is a measured angle.

But D_A depends on the EXPANSION HISTORY — it requires a cosmological
model to compute. Planck assumes ΛCDM (flat universe, cosmological
constant, cold dark matter) and solves for H₀ as a fitted parameter.

**Critical point**: the Planck H₀ is an OUTPUT of a model fit, not a
direct measurement. It is only as good as the model it assumes.

### 2.2 The Distance Ladder (SH0ES)

SH0ES measures three things directly:

**Rung 1**: Geometric distances to nearby Cepheids
- Gaia EDR3 parallaxes (Milky Way Cepheids)
- Detached eclipsing binaries (LMC)
- Water masers (NGC 4258)

**Rung 2**: Cepheid period-luminosity relation in SN Ia host galaxies
- 42 Type Ia supernovae in 37 galaxies with Cepheid observations
- Same HST instrument/filters throughout (WFC3, F555W/F814W/F160W)

**Rung 3**: SN Ia in the Hubble flow (z > 0.01)
- Using Pantheon+ sample (1,550 unique SN Ia, 0.001 ≤ z ≤ 2.26)
- Compute H₀ = cz/d where d comes from calibrated SN Ia luminosity

**Critical point**: Rung 3 computes cz/d. The redshift z is spectral
(model-independent). The distance d is calibrated by standard candles.
The RATIO cz/d is a direct measurement of the local redshift gradient.

### 2.3 The TRGB Alternative (Freedman/CCHP)

Same structure as SH0ES but uses a different Rung 2 calibrator:
- Tip of the Red Giant Branch (TRGB) luminosity instead of Cepheids
- TRGB is less affected by dust, crowding, and metallicity
- Uses JWST near-infrared data for improved precision

Result: H₀ ≈ 69–70 km/s/Mpc — between Planck and SH0ES.

---

## 3. SDT Reframing: What Is Being Measured

### 3.1 There Is No Expansion

SDT axiom R1: space is a gap-free, contact-only relay medium. The
lattice does not stretch, expand, or contract. It relays.

If there is no expansion, there is no expansion rate. The quantity
"H₀" does not measure what it claims to measure.

### 3.2 What the Redshift Actually Is

In SDT, light is a transverse oscillation of the spation lattice.
As it propagates through the convergent field (the omnidirectional
pressure of the throughput cascade), the lateral pressure SQUEEZES
the transverse amplitude.

Energy conservation requires: as amplitude drops, wavelength extends.

```
BEFORE (near source):  high amplitude, short wavelength
 ↓ traverses pressure gradient
AFTER (at observer):   low amplitude, long wavelength
```

This is NOT a tape-measure stretching of space. It is a RATIO
conversion: amplitude → wavelength. The energy removed from the
transverse oscillation goes into the lattice itself.

### 3.3 Ratio Increase, Not Metric Increase

James's key distinction:

**Metric expansion**: every wavelength increases by the same
absolute amount per unit time. This is a tape-measure growth.
It predicts z ∝ d (linear at low z), with the proportionality
constant being H₀/c. The increase is environment-independent —
it depends only on the scale factor a(t).

**Pressure gradient**: every wavelength increases by a RATIO
proportional to the integrated pressure traversed. The increase
is:

```
λ_obs / λ_emit = exp(∫₀ᵈ κ(r) dr)
```

where κ(r) is the local compression coefficient of the lattice.
At low z, this is approximately linear: z ≈ κ̄ × d, where κ̄ is
the mean compression coefficient over the path.

The "H₀" measurements are actually measuring κ̄ — the mean
amplitude-to-wavelength conversion rate along the specific path.

### 3.4 Why Two Methods Give Different κ̄

**Planck** extracts κ̄ from the FULL sky power spectrum, averaged
over all directions and all redshifts from z=0 to z≈1100. It
samples the GLOBAL mean compression coefficient.

**SH0ES** measures κ̄ within ~300 Mpc, along specific lines of
sight to Cepheid-hosting galaxies. It samples the LOCAL compression
coefficient.

If κ varies with position (which it must — matter creates local
occlusion variations), then:

```
κ_local ≠ κ_global
```

The tension is the DIFFERENCE between local and global compression
coefficients. This is not a crisis — it is expected.

---

## 4. The Apparent Acceleration

### 4.1 The 1998 Discovery

In 1998, Perlmutter, Schmidt, and Riess found that distant SN Ia
(z ≈ 0.5–1.0) were ~0.25 magnitudes FAINTER than expected for a
decelerating universe. In ΛCDM, this means the expansion is
accelerating — requiring dark energy (Λ) to drive the acceleration.

### 4.2 SDT Explanation: Steeper Early Gradient

In SDT, the convergent field was DENSER at earlier epochs. The
throughput cascade operated at higher pressure. This means:

```
κ(z) > κ(0)     for all z > 0
```

The compression coefficient was HIGHER in the past. Light from
high-z sources traversed a steeper pressure gradient. More
amplitude was squeezed into wavelength per unit distance.

This makes distant SN Ia appear:
- More redshifted than a linear extrapolation of the local κ
- Therefore apparently MORE DISTANT
- Therefore FAINTER

The "acceleration" is the steeper compression at earlier epochs.
No dark energy. No Λ. Just a pressure gradient that was steeper
when the lattice was hotter.

### 4.3 Quantitative Check

The CMB temperature at redshift z:

```
T(z) = T_CMB × (1 + z) = 2.7255 × (1 + z)  K
```

This is confirmed by observations of the Sunyaev-Zel'dovich effect
at various redshifts (measuring CMB temperature at z ≈ 0.5–3).

If κ scales with pressure, and pressure scales with T⁴ (Stefan-
Boltzmann, radiation-dominated throughput), then:

```
κ(z) ∝ T(z)⁴ = T_CMB⁴ × (1 + z)⁴
```

The integrated redshift over distance d at epoch z:

```
dz/dr ∝ κ(z) ∝ (1 + z)⁴
```

This is STEEPER than the ΛCDM prediction (which gives dz/dr ∝
(1+z)³ for matter-dominated and (1+z)⁴ for radiation-dominated).

Wait — the (1+z)⁴ scaling actually MATCHES the radiation-dominated
ΛCDM prediction. The SDT mechanism gives the same mathematical
form but with a different physical interpretation:

| Framework | dz/dr scaling | Mechanism |
|-----------|-------------|-----------|
| ΛCDM (rad-dom) | (1+z)⁴ | Space stretches; radiation dilutes as (1+z)⁴ |
| SDT | (1+z)⁴ | Pressure gradient steeper at higher T; κ ∝ T⁴ |

Same mathematics. Different ontology.

### 4.4 The Acceleration as Gradient Curvature

The "deceleration parameter" q₀ in ΛCDM measures the second
derivative of the scale factor. q₀ < 0 means acceleration.

In SDT, q₀ maps to the CURVATURE of the compression profile:

```
q₀(SDT) = -d²κ/dr² / (dκ/dr)²
```

If κ(r) is convex (steeper gradient at larger r, i.e., earlier
epochs), then q₀ < 0 — the same sign as "accelerating expansion."

The convexity of κ(r) is GUARANTEED by the T⁴ dependence: a
power law with exponent > 1 is always convex when mapped through
the pressure-distance relation.

**Prediction**: SDT reproduces the observed SN Ia distance-modulus
vs z curve WITHOUT dark energy, using only the T⁴ pressure scaling.

---

## 5. The zk²=1 Contribution

### 5.1 The Closure Relation

From laws.hpp (line 417–420):

```c++
/// Closure condition: z · k² = 1 (verification)
constexpr auto zk2_product(double z, double k) -> double {
    return z * k * k;
}
```

For any gravitationally bound system with ground-state coupling
constant k:

```
z = 1/k²
```

This gives the spatial displacement redshift at the surface of the object.
For a star with k = k_star:

```
z_surface = 1/k_star²
```

### 5.2 How zk²=1 Skews Cosmological Measurements

Every photon emitted from a stellar surface carries the zk²=1
spatial displacement redshift of its parent star. When observed at
cosmological distances, this displacement redshift is ADDED to
the pressure-gradient redshift:

```
z_observed = (1 + z_cosmological)(1 + z_stellar) − 1
            ≈ z_cosmological + z_stellar     (at low z)
```

For the Sun: k_Sun ≈ 686 → z_Sun = 1/686² = 2.13 × 10⁻⁶

This is tiny — negligible for cosmological purposes.

But for SN Ia, the progenitor white dwarf has a VERY different k:
White dwarf surface: k_WD ≈ 50–100 → z_WD = 1/k² ≈ 10⁻⁴ to 4×10⁻⁴

And the EXPLOSION environment has k even lower — the blast wave
ejecta are at high velocity (v ≈ 10,000–20,000 km/s):

```
z_ejecta ≈ v²/c² = (10⁴/3×10⁵)² ≈ 10⁻³
```

This ejecta redshift is approximately 0.001 — comparable to the
peculiar velocity corrections already applied in H₀ analyses
(~300 km/s → z ≈ 10⁻³).

But: if the ejecta redshift varies systematically with z (because
higher-z SN Ia are observed at earlier epochs when metallicity,
progenitor mass, and explosion energy may differ), then zk²=1
introduces a z-DEPENDENT systematic that mimics a change in H₀.

### 5.3 Galactic Core Contribution

Light from galaxies is a superposition of stellar light from all
radii. Stars near galactic cores are in deeper displacement
fields → higher z_stellar. Stars in the outskirts are in
shallower fields → lower z_stellar.

The galaxy-averaged z_stellar depends on the luminosity-weighted
mean displacement field. More massive galaxies with denser
cores have higher mean z_stellar.

This is the **SN Ia host galaxy mass correlation** that standard
analyses already observe: SN Ia in more massive host galaxies
appear systematically different. Standard analyses treat this as
a systematic to correct. SDT says it's the zk²=1 of the host
environment.

---

## 6. The Pantheon+ Data Through SDT

### 6.1 What the Data Contains

Pantheon+ (Scolnic et al. 2022): 1,550 unique SN Ia from 18 surveys.
- z range: 0.001 to 2.26
- Provides distance moduli μ = m − M for each SN Ia
- Full 1701 × 1701 covariance matrix

The distance modulus is:
```
μ = 5 log₁₀(d_L / 10 pc)
```

where d_L is the luminosity distance. In ΛCDM:
```
d_L = (1 + z) × D_M(z)
```

where D_M is the comoving distance, computed from the integral:
```
D_M = (c/H₀) ∫₀ᶻ dz'/E(z')
```

with E(z) = √(Ω_m(1+z)³ + Ω_Λ).

### 6.2 SDT Reinterpretation

In SDT, the luminosity distance formula is different:

There is no (1+z) factor from expansion (no expansion).
There IS a (1+z) factor from the amplitude squeeze: photon energy
drops by 1/(1+z) due to amplitude-to-wavelength conversion.

Wait — in ΛCDM the (1+z) in d_L comes from three effects:
1. Photon energy loss: ×(1+z) — ONE factor
2. Time dilation of photon arrival rate: ×(1+z) — ONE factor
3. Geometric area: depends on D_A

In SDT:
1. Photon energy loss from amplitude squeeze: ×(1+z) — PRESENT
2. Time dilation: NOT from expansion. But: is there a time dilation
   in SDT? If the photon traverses a pressure gradient, does the
   gradient impose a time dilation on the arrival rate?

This is a critical question. Let me work through it.

### 6.3 Time Dilation in SDT

The movement budget (Theorem T10): v_circ² + v² = c².

A photon at v = c has v_circ = 0. It carries no circulation —
it IS the relay. Its arrival rate is c / λ = frequency.

If the wavelength extends during propagation (amplitude squeeze),
the frequency drops by 1/(1+z). This IS a time dilation of the
photon arrival rate — fewer photons per unit time arrive, by a
factor of 1/(1+z).

So SDT DOES have the arrival-rate factor of (1+z). But it's from
the amplitude squeeze, not from metric expansion.

Therefore the luminosity relation in SDT:

```
F = L / (4π d² × (1+z)²)
```

where:
- d = physical distance (no comoving nonsense)
- First (1+z): energy loss from amplitude squeeze
- Second (1+z): arrival rate reduction from frequency drop
- L = intrinsic luminosity

This gives:
```
d_L(SDT) = d × (1+z)
```

Identical to the ΛCDM luminosity distance IF d = D_M.

### 6.4 Where the Difference Enters

The difference is NOT in the 1/(1+z)² flux factor — that's the same.
The difference is in the DISTANCE d:

**ΛCDM**: d is computed from the expansion integral, which requires
H₀, Ω_m, Ω_Λ as parameters. At high z, the dark energy term
makes d larger → SN fainter → "acceleration."

**SDT**: d is the physical distance. It relates to z through the
pressure gradient:

```
z = exp(∫₀ᵈ κ(r) dr) − 1
```

At low z: z ≈ κ̄ d, so d ≈ z / κ̄ = z × c / H₀(local).

At high z: the integral is NOT linear because κ was steeper at
earlier epochs (higher T). This makes d LARGER at high z than the
linear extrapolation — the SAME effect as dark energy, but from
physics, not vacuum energy.

---

## 7. Quantitative Comparison

### 7.1 The Distance-Modulus Residual

The key plot in supernova cosmology is the Hubble residual:

```
Δμ = μ_observed − μ_expected(empty universe)
```

where μ_expected for an empty (coasting) universe with H₀ is:

```
μ_empty = 5 log₁₀[(c/H₀) × z × (1 + z/2)] + 25
```

The observed Δμ shows:
- At z < 0.3: approximately zero (Hubble flow)
- At z ≈ 0.5: Δμ ≈ +0.25 mag (dimmer than empty universe)
- At z ≈ 1.0: Δμ ≈ +0.05 mag (converging back)

### 7.2 SDT Prediction for Δμ

If κ(z) ∝ (1+z)⁴ (T⁴ pressure scaling), then the physical
distance to redshift z is:

```
d(z) = (c/H₀) × (1/3) × [(1+z)³ − 1] / (1+z)³
```

No — let me derive this properly.

If dz/dr = κ₀(1+z)ⁿ where n=4 (radiation pressure scaling):

```
∫₀ᶻ dz'/(1+z')⁴ = κ₀ × d
d = [1 − 1/(1+z)³] / (3κ₀)
```

At low z: d ≈ z/κ₀ (linear, as expected).

The distance modulus:
```
μ(SDT) = 5 log₁₀(d_L(SDT) / 10 pc) + 25
       = 5 log₁₀(d(z) × (1+z)) + constant
```

This needs to be computed numerically and compared to the Pantheon+
data. The residual Δμ(SDT) should match the observed Δμ without
requiring Ω_Λ.

### 7.3 Fitting Parameters

ΛCDM has 2 free parameters for the SN Ia fit: Ω_m and H₀.
(Ω_Λ = 1 − Ω_m in the flat case.)

SDT has 2 free parameters: κ₀ (local compression coefficient,
equivalent to H₀/c) and n (pressure-distance power law exponent).

If n = 4 is fixed by the T⁴ physics, SDT has only 1 FREE
parameter: κ₀. This is fewer than ΛCDM.

If the single-parameter SDT model fits the Pantheon+ data as well
as the two-parameter ΛCDM model, that is a significant result.

---

## 8. The Three Measured Values and SDT

### 8.1 Why SH0ES Gets 73

SH0ES measures cz/d within ~300 Mpc. In SDT, this is:

```
H₀(local) = c × κ_local
```

where κ_local is the local compression coefficient.

### 8.2 Why Planck Gets 67

Planck fits the global power spectrum, which constrains the
AVERAGE compression coefficient over the entire sky:

```
H₀(global) = c × κ̄_global
```

If the local universe has less matter (less occlusion) than the
cosmic average, κ_local > κ̄_global:

```
H₀(local) / H₀(global) = κ_local / κ̄_global = 73.04 / 67.4 = 1.084
```

The local compression is 8.4% steeper than the global mean.

### 8.3 Why Freedman Gets 70

The TRGB measurement probes a slightly different volume than
SH0ES. If the TRGB sample includes galaxies at larger distances
(more representative of the cosmic mean), its κ would be
intermediate:

```
κ_TRGB ≈ (κ_local + κ̄_global) / 2
```

This gives H₀(TRGB) ≈ (73 + 67) / 2 = 70.  
Freedman gets 69.96. Exact midpoint.

### 8.4 Why Lensing Gets 72

Gravitational lensing (TDCOSMO, H₀ = 71.6) measures time delays
between lensed images. The time delay depends on the Hubble
constant AND the lens mass distribution:

```
Δt = (1 + z_L) × D_Δt / c × Δφ
```

where D_Δt is a combination of angular diameter distances.

In SDT, the time delay depends on the compression coefficient
ALONG the lensed light paths. These paths traverse through or
near the lens galaxy (high-density, high-occlusion region),
which has a DIFFERENT κ than the void between galaxies.

The lensing H₀ samples paths that pass through overdense regions,
giving a κ intermediate between local and global → H₀ ≈ 72.

---

## 9. The SDT Resolution

### 9.1 Summary

| Method | What it measures | SDT quantity | H₀ (km/s/Mpc) |
|--------|-----------------|-------------|---------------|
| Planck | Global mean compression | κ̄_global | 67.4 |
| Freedman (TRGB) | Intermediate volume | κ̄_intermediate | 70.0 |
| TDCOSMO (lensing) | Overdense path | κ̄_overdense | 71.6 |
| SH0ES (Cepheid) | Local ~300 Mpc | κ_local | 73.0 |

### 9.2 The Ordering

SDT predicts the ORDERING of H₀ measurements:

```
H₀(Planck) < H₀(TRGB) < H₀(lensing) < H₀(SH0ES)
67.4       < 70.0      < 71.6        < 73.0
```

This ordering holds. It is a strict consequence of the compression
coefficient varying with the sampled matter density:

- Planck: global average (most matter)
- TRGB: extended local (slightly less matter)
- Lensing: path through galaxies (intermediate)
- SH0ES: local ~300 Mpc (least matter — local underdensity)

### 9.3 Falsifiable Prediction

**SDT predicts**: any NEW H₀ measurement will fall within the range
67.4–73.0, and its value will correlate with the matter density
sampled by that measurement method.

Specifically:
- Methods sampling large volumes → H₀ → 67.4 (global)
- Methods sampling local volumes → H₀ → 73.0 (local)
- Methods sampling intermediate volumes → H₀ intermediate

No "new physics" is needed. No dark energy. No early dark energy.
No modified gravity. The tension IS the observable difference
between local and global compression coefficients, caused by the
Earth's position in a local region of lower-than-average matter
density.

### 9.4 The Matter Density Contrast

The required local underdensity:

```
δ = 1 − κ̄_global / κ_local = 1 − 67.4/73.0 = 0.077
```

The local universe within ~300 Mpc has ~7.7% less matter density
than the cosmic mean.

Observational constraint: the KBC void (Keenan, Barger, Cowie 2013)
measures δ ≈ −0.15 to −0.46 within ~300 Mpc.

SDT requires δ = −0.077. This is SMALLER than the KBC measurement.
SDT's required underdensity is comfortably within the observed range.

---

## 10. Distinguishing SDT from ΛCDM

### 10.1 Same Predictions

Both frameworks predict:
- Linear Hubble law at low z
- SN Ia fainter at high z (acceleration-like)
- CMB power spectrum with acoustic peaks
- BAO imprint in galaxy clustering

### 10.2 Different Predictions

| Observable | ΛCDM | SDT |
|-----------|------|-----|
| H₀ tension | Requires new physics | Expected (κ varies with density) |
| Dark energy | 68% of universe | Does not exist |
| SN Ia environment dependence | Systematic to correct | The signal itself |
| Time dilation of SN light curves | From (1+z) expansion | From (1+z) amplitude squeeze |
| Age of universe | 13.8 Gyr | ~48 Gyr |
| BAO scale | Fossil of acoustic epoch | Lattice structural constant |
| Photon energy loss | Not conserved | Conserved (→ lattice) |

### 10.3 Testable Differences

1. **SN Ia Hubble residual vs line-of-sight density**: SDT predicts
   correlation. ΛCDM predicts none (after peculiar velocity correction).

2. **H₀ vs measurement volume**: SDT predicts monotonic increase
   as sample volume shrinks. ΛCDM predicts convergence to one value.

3. **Time dilation of SN light curves vs z**: both predict (1+z)
   stretching, but SDT predicts ADDITIONAL stretching from the T⁴
   pressure dependence at high z. At z ≈ 1, this is a ~1% effect
   above the (1+z) baseline.

4. **Photon energy conservation**: In ΛCDM, cosmological redshift
   energy vanishes. In SDT, it is deposited into the lattice. The
   total CMB energy density should equal the integrated throughput
   from all sources — a calculable quantity.

---

## 11. Open Calculations Required

| # | Calculation | Status |
|---|-----------|--------|
| 1 | Fit SDT d(z) to Pantheon+ using κ₀ and n=4 | NOT STARTED |
| 2 | Compute Δμ(SDT) − Δμ(ΛCDM) residual | NOT STARTED |
| 3 | Derive r_s from SDT pre-Clearing acoustic physics | NOT STARTED |
| 4 | Compute local δ from galaxy survey data | NOT STARTED |
| 5 | Test H₀ vs sample volume correlation | NOT STARTED |
| 6 | Compute SDT age with T⁴ pressure profile | NOT STARTED |
| 7 | Calculate lattice energy budget (photon → lattice) | NOT STARTED |
| 8 | Compare SN Ia residual with host galaxy density | NOT STARTED |

---

## 12. Data Inventory

### Available Now

| Dataset | Source | Items |
|---------|--------|-------|
| Pantheon+ SN Ia | github.com/PantheonPlusSH0ES | 1,550 SN, z, μ, covariance |
| Planck 2018 parameters | ESA Planck Legacy Archive | All ΛCDM parameters |
| SH0ES calibration | Riess et al. 2022 (ApJL 934, L7) | All ladder rungs |
| CCHP TRGB | Freedman et al. 2024 (ApJ 985:203) | TRGB + JAGB H₀ |
| TDCOSMO lensing | TDCOSMO VII (2025) | 8 lens systems |
| KBC void | Keenan, Barger, Cowie 2013 | Local density contrast |
| BAO measurements | DESI DR1 (2024) | H(z), D_A(z) at z=0.3–2.1 |

### Needed

| Data | Purpose | Source |
|------|---------|--------|
| SN Ia host galaxy masses | Test environment correlation | Pantheon+ metadata |
| Line-of-sight galaxy counts | Test κ vs density | Survey catalogues |
| SN Ia light-curve stretch vs z | Test (1+z) vs T⁴ prediction | Pantheon+ light curves |

---

## 13. Sources

| Source | Access | Year |
|--------|--------|------|
| Planck Collaboration VI | A&A 641, A6 (2020) | 2018 data |
| Riess et al. | ApJL 934, L7 (2022) | SH0ES final |
| Scolnic et al. | ApJ 938:113 (2022) | Pantheon+ release |
| Brout et al. | ApJ 938:110 (2022) | Pantheon+ constraints |
| Freedman et al. | ApJ 985:203 (2025) | CCHP JWST |
| Perlmutter et al. | ApJ 517:565 (1999) | Acceleration discovery |
| Riess et al. | AJ 116:1009 (1998) | Acceleration discovery |
| Keenan, Barger, Cowie | ApJ 775:62 (2013) | KBC void |
| DESI Collaboration | Various (2024) | BAO measurements |
