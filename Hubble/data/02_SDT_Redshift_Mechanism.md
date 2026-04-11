# SDT Redshift Mechanism: Amplitude-to-Wavelength Conversion

---

## 1. The Mechanism

### 1.1 Metric vs Ratio

**Metric expansion** (ΛCDM): the wavelength increases because
space itself expands. The increase is absolute — every ruler,
every wavelength, every distance grows by the same factor a(t).

This is a tape-measure increase. If you could freeze two spation
positions and measure the distance between them at two different
times, the distance would be larger at the later time.

**Ratio conversion** (SDT): the wavelength increases because
the transverse amplitude is converted to longitudinal extension.
The photon traverses a pressurised medium (the convergent
throughput). The lateral pressure squeezes the oscillation.
Energy conservation forces the amplitude reduction into wavelength
extension.

This is a ratio increase. λ_obs/λ_emit is a dimensionless number
determined by the integrated pressure path.

### 1.2 The Physical Picture

A photon in the SDT lattice is a transverse perturbation
propagating at c through the spation matrix. The convergent
throughput provides omnidirectional compression at every point.

As the photon propagates through a region of compression:

```
          convergent pressure
              ↓     ↓     ↓
    ┌─────────────────────────┐
    │  ~~~~    →    ~~~       │  transverse wave
    │ (high A,    (low A,     │
    │  short λ)    long λ)    │
    └─────────────────────────┘
              ↑     ↑     ↑
          convergent pressure
```

The lateral squeeze reduces the transverse excursion (amplitude).
The energy that was in the transverse mode transfers to the
longitudinal extent (wavelength grows).

### 1.3 Energy Conservation

In ΛCDM, the energy of a cosmologically redshifted photon is
NOT conserved. The photon loses energy by 1/(1+z), and this
energy does not go anywhere. The standard textbook says: "energy
is not conserved in general relativity with a time-dependent
metric." This is the actual explanation.

In SDT, the energy IS conserved:
- Photon energy drops by 1/(1+z)
- The "lost" energy is deposited into the lattice
- This energy sustains the convergent throughput itself

The total energy budget: photon + lattice = constant.

### 1.4 The Compression Coefficient

Define κ(r) as the local compression coefficient at position r
along the photon's path:

```
dλ/dr = κ(r) × λ
```

This is a first-order ODE. Solution:

```
λ(r) = λ₀ × exp(∫₀ʳ κ(r') dr')
```

The redshift:

```
z = λ_obs/λ_emit − 1 = exp(∫₀ᵈ κ(r) dr) − 1
```

At low z:  z ≈ ∫₀ᵈ κ(r) dr ≈ κ̄ × d

This gives the Hubble law: z = (H₀/c) × d, with H₀/c = κ̄.

---

## 2. Why κ Varies With Position

### 2.1 Matter creates occlusion

The convergent throughput arrives from all shells of the CMB.
Matter between the photon's path and the shell boundary blocks
(occludes) some of the throughput. Less throughput → less pressure
→ lower κ.

```
κ(r) = κ₀ × (1 − δ_matter(r))
```

where δ_matter is the fractional matter density relative to the
cosmic mean, and κ₀ is the vacuum compression coefficient.

### 2.2 Implications for H₀

If the local universe (within ~300 Mpc) has δ = −0.077 (7.7%
underdensity):

```
κ_local = κ₀ × (1 − (−0.077)) = κ₀ × 1.077
```

Wait — LESS matter means LESS occlusion, which means MORE
throughput reaches each point, steeper pressure gradient.

Actually: less matter → less occlusion → more convergent pressure
arrives at the photon → steeper gradient → more amplitude squeeze
→ higher κ. So:

```
κ_local = κ_global × (1 + f|δ|)
```

where f is a coupling factor.

For κ_local/κ_global = 73.0/67.4 = 1.083:

f × |δ| = 0.083

If f = 1: |δ| = 0.083 (8.3% underdensity)
If f = 0.5: |δ| = 0.166 (16.6% underdensity)

The KBC void measures |δ| = 0.15–0.46. Both f=1 and f=0.5 are
within the observed range.

---

## 3. Why κ Varies With Epoch (z-dependence)

### 3.1 The throughput was denser

At earlier epochs (higher z), the universe was hotter and denser.
The convergent throughput pressure scales with the radiation
energy density:

```
P_conv(z) ∝ T(z)⁴ = T_CMB⁴ × (1+z)⁴
```

Therefore:
```
κ(z) = κ₀ × (1+z)⁴
```

### 3.2 The distance integral

The physical distance to an object at redshift z, given κ(z):

From dz = κ(z) × (1+z) × dr (accounting for the fact that
at redshift z, a comoving distance element maps to physical):

Actually, let me be more careful. If:

```
d(ln λ)/dr = κ(r)
```

and if κ depends on epoch (which maps to distance):

```
dz/(1+z) = κ(z) dr
```

Then:
```
dr = dz / [κ₀ (1+z)⁵]     (if κ ∝ (1+z)⁴)
```

```
d = ∫₀ᶻ dz' / [κ₀ (1+z')⁵]
  = (1/κ₀) × [1 − 1/(1+z)⁴] / 4
```

At low z: d ≈ z / κ₀  (recovers Hubble law).

At high z: d → 1/(4κ₀) = c/(4H₀). The distance saturates.

This is analogous to the "particle horizon" in standard cosmology
but with a different power law.

### 3.3 The luminosity distance

The flux received from a source at distance d in SDT:

```
F = L / (4π d² × (1+z)²)
```

One (1+z) from energy loss (amplitude squeeze).
One (1+z) from arrival rate reduction (frequency drops).

So:
```
d_L(SDT) = d × (1+z)
```

And:
```
μ(SDT) = 5 log₁₀[d_L(SDT) / 10 pc]
       = 5 log₁₀[d(z) × (1+z) / 10 pc]
```

This can be compared directly to the Pantheon+ μ(z) data.

---

## 4. Comparison of d(z) at Key Redshifts

### ΛCDM (Ω_m = 0.315, Ω_Λ = 0.685, H₀ = 67.4)

| z | D_M (Mpc) | d_L (Mpc) | μ (mag) |
|---|----------|----------|---------|
| 0.01 | 42.3 | 42.7 | 33.15 |
| 0.05 | 210 | 221 | 36.72 |
| 0.1 | 417 | 459 | 38.31 |
| 0.3 | 1,178 | 1,531 | 40.93 |
| 0.5 | 1,849 | 2,774 | 42.22 |
| 1.0 | 3,216 | 6,432 | 44.04 |

### SDT (κ₀ = H₀/c, n=4)

Needs numerical computation. The closed-form expressions
above predict d saturating at c/(4H₀) ≈ 1,114 Mpc. This
is too small — real objects at z=1 are at ~3,000 Mpc.

This indicates n=4 is too steep. The distance saturates at
c/(4H₀) ≈ 1,114 Mpc, but real objects at z=1 are at ~3,000 Mpc.

### The SDT approach: separate the background from the photon

The circularity above arises from conflating the photon's
redshift with the background pressure profile. The resolution:

**The background pressure profile is STATIC and GEOMETRIC.**

The convergent throughput originates from the Clearing shell
(CMB boundary) and spreads inward. The pressure at distance d
from the shell depends on:

```
P(d) = P_shell × f(d/R_shell)
```

where f is a geometric attenuation function determined by:
1. Solid angle subtended by the shell from position d
2. Occlusion by intervening matter

For d ≪ R_shell (which is our regime — we are deep inside):

```
P(d) ≈ P_shell × (1 − d/R_shell)     (first order)
```

The GRADIENT of this static background:

```
dP/dr = −P_shell / R_shell = constant
```

This gives κ = |dP/dr| / P = 1/R_shell = H₀/c.

**A constant κ produces:** z = exp(κd) − 1 ≈ κd for small z.
This is the linear Hubble law. No epoch dependence.

### Why the data shows d_L ≈ cz/H₀ everywhere

The observation (Fix 6 in 06_zk2_Applied_To_SN_Ia.md) is that
d_L(observed) ≈ cz/H₀ to within ~3–7% across the entire
Pantheon+ range. This IS what a constant κ predicts. No
(1+z)⁴ scaling. No dark energy. Just a static pressure
gradient from a fixed geometric shell.

### What about the "acceleration" at z ≈ 0.5?

At z = 0.5, k = √2. The departure from linearity is ~3%.
In ΛCDM this requires Ω_Λ = 0.685. In SDT, three possible
sources of this small departure:

1. **Second-order geometric correction**: P(d) has higher
   terms in d/R_shell that produce weak curvature
2. **Matter occlusion variation**: the line-of-sight matter
   density varies, modulating κ locally
3. **Measurement correction artifacts**: the zHD "correction"
   from heliocentric z to Hubble-flow z introduces model-
   dependent shifts that may mimic curvature

All three are small effects (few percent level), consistent
with the observed ~3% departure.

### Open calculation: d_L in a static lattice

In ΛCDM, the luminosity distance includes two (1+z) factors:
```
d_L = d × (1+z)
F = L / (4π d_L²) = L / (4π d² (1+z)²)
```
One (1+z) for photon energy loss, one for arrival rate reduction.

In SDT with amplitude-to-wavelength conversion:
- **Energy loss**: YES — the photon's energy drops as amplitude
  converts to wavelength. Factor: 1/(1+z). ✓
- **Arrival rate**: NEEDS EXAMINATION. In expansion cosmology,
  photons arrive less frequently because the space between them
  stretches. In a static lattice, the photons are emitted at
  frequency ν_emit but arrive at frequency ν_obs = ν_emit/(1+z)
  because each photon's wavelength (and period) has been stretched
  by the same amplitude squeeze. So the arrival rate DOES drop
  by 1/(1+z). ✓

Therefore d_L(SDT) = d × (1+z), same as standard.

But since d ≈ cz/H₀ (constant κ), this gives:

```
d_L(SDT) ≈ cz(1+z)/H₀
```

At z = 0.5: d_L = 0.75 cz/H₀ × factor.
At z = 1.0: d_L = 2.0 cz/H₀.

But the observed d_L IS ≈ cz/H₀ (ratio ~1.0), NOT cz(1+z)/H₀.
This means either:
1. The (1+z) arrival-rate factor does NOT apply in SDT
   (the lattice preserves photon count even as wavelength changes)
2. The distance formula d ≈ cz/H₀ already INCLUDES the (1+z)
   correction implicitly (because z itself encodes the path)

**This is the key open question.** The data says d_L ≈ cz/H₀.
If the (1+z) factors apply, then d must be smaller than cz/H₀
by 1/(1+z), and the compression must be stronger than constant.
If they don't apply, then d = cz/H₀ and κ is truly constant.

The resolution requires examining whether the spation lattice
preserves photon packet spacing or stretches it. This is
Open Calculation #1.

---

## 5. The zk²=1 Stellar Contribution

### 5.1 Spatial Displacement Redshift at Stellar Surface

Every photon emitted from a stellar surface carries an additional
redshift from the spatial displacement at the star:

```
z = 1/k²
```

For different stellar types:

| Star type | k | z | Δv (km/s) |
|-----------|---|--------|----------|
| Sun | 686 | 2.13 × 10⁻⁶ | 0.64 |
| Red giant | ~200 | 2.5 × 10⁻⁵ | 7.5 |
| White dwarf | 50–100 | 10⁻⁴ to 4×10⁻⁴ | 30–120 |
| Neutron star | ~3 | 0.11 | 33,000 |

### 5.2 SN Ia Ejecta Contribution

Type Ia supernovae eject material at v ≈ 10,000–20,000 km/s.
The spectral lines used to measure redshift come from this
expanding ejecta. The SN Ia "peculiar" redshift:

```
z_ejecta ≈ v²/c² = (10⁴/3×10⁵)² ≈ 10⁻³
```

This is already corrected in standard analyses via the "light
curve shape" correction (the Phillips relation). But the
correction was CALIBRATED assuming expansion cosmology.

### 5.3 Host Galaxy Potential

Stars in elliptical galaxies (deep displacement wells) have higher
z than stars in dwarf galaxies. SN Ia in massive hosts
show a systematic ~0.04 mag offset in the Hubble residual
compared to SN Ia in low-mass hosts.

In SDT: this 0.04 mag corresponds to a z difference of:

```
Δμ = 0.04 mag → Δd_L/d_L ≈ 0.02 → Δz ≈ 0.02 × z
```

At z = 0.05: Δz ≈ 0.001, which corresponds to:

```
z(host) = 1/k²_host ≈ 0.001 → k_host ≈ 32
```

This is the k value of a galaxy with surface escape velocity:

```
v = c/k = 3×10⁵/32 ≈ 9,400 km/s
```

This is reasonable for a massive elliptical galaxy (velocity
dispersion σ ≈ 300 km/s, so v_esc ≈ 3σ ≈ 900 km/s at the
centre, but the luminosity-weighted average potential gives
an effective v_esc of several thousand km/s).

The SDT prediction: the SN Ia host galaxy mass step correlates
with the luminosity-weighted mean displacement field of
the host galaxy, via zk²=1.

---

## 6. Temperature History and the Habitable Window

| z | T (K) | Description | Standard duration | SDT duration |
|---|-------|------------|------------------|-------------|
| 1100 | 3,000 | Clearing (recombination) | t=380,000 yr | t=13.7 My |
| 500 | 1,365 | Deep infrared, warm | ~500,000 yr | ~18 My |
| 107 | 295 | Room temperature (22°C) | ~10 My | ~350 My |
| 100 | 275 | Just above freezing | ~15 My | ~520 My |
| 10 | 30 | Cold, far IR | ~2 Gy | ~7 Gy |
| 0 | 2.73 | Microwave (now) | 13.8 Gy | 48 Gy |

In the standard model, the habitable temperature window
(z ≈ 100–110, T ≈ 273–300 K) lasted approximately 10 million
years. In SDT's longer timeline, it lasted ~350 million years.

---

## 7. Pre-Clearing Pressure Regime

### 7.1 Sound Speed

The acoustic propagation speed in the coupled baryon-photon
plasma before recombination:

```
c_s = c / √3 = 1.732 × 10⁸ m/s
```

This is the speed at which pressure waves (BAO) propagated.
Light could NOT propagate — the mean free path was effectively
zero (Thomson scattering).

### 7.2 Regime Hierarchy

| Regime | Coupling | Speed | Structures |
|--------|---------|-------|-----------|
| Pre-Clearing | Full matter-radiation | c/√3 | QGP, heavy bosons, BAO |
| Post-Clearing | Free relay | c | Photons, electrons, protons |
| Extreme occlusion | Re-coupled? | ??? | SMBH interior |

### 7.3 LHC Particles as Fossils

The heavy particles produced at the LHC (top quark, W/Z bosons,
Higgs) are resonance modes of the pre-Clearing pressure regime.
They decay in femtoseconds because the present-epoch lattice
cannot sustain them — the pressure is too low.

In the pre-Clearing universe, these structures were stable
(or at least long-lived). They are "dinosaur particles" —
creatures of a denser era.
