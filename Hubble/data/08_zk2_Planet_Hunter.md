# zk²=1 as a Planet Hunter — Candidate Systems

> z = measured from spectral lines (the only input)
> k = 1/√z — coupling constant
> κ = R·z — c-orbit anchor (metres)
> v(r) = (c/k)·√(R/r) — orbital velocity at distance r

---

## 1. M31 Status

No confirmed exoplanets in M31. One candidate:

| Object   | Year | Method        | k_host | z_host   | Companion   |
| -------- | ---- | ------------- | ------ | -------- | ----------- |
| PA-99-N2 | 1999 | Microlensing  | ~970   | ~1.1e-6  | ~6.3 M_Jup  |

The microlensing event was one-shot and cannot be repeated.
Individual M31 stars are too faint for RV spectroscopy with
current instruments. But with zk²=1, the approach changes:

**If we measure z for any resolved M31 star from its spectral
lines, we know k. We know the displacement field. Any measured
deviation IS the signal.**

---

## 2. Milky Way Systems with Unresolved Signals

These are real systems where zk²=1 can extract information
from existing data by providing a clean baseline.

### Proxima Centauri (M5.5 V, 4.24 ly)

```
z = 1.89 × 10⁻⁶  (measured: ESPRESSO spectral lines)
k = 727.7
κ = R·z = 1.071e8 × 1.89e-6 = 0.202 m
v_surface = c/k = 412 km/s
```

- **Confirmed**: Proxima b (1.07 M⊕, 11.2 d), Proxima d (0.26 M⊕, 5.1 d)
- **Controversial**: Proxima c (~7 M⊕, ~1900 d period)
  - Signal may be instrumental artifact or stellar activity
  - zk²=1 baseline: z = 1.89e-6. If measured z deviates
    by Δz ~ 10⁻¹⁰ with 1900 d periodicity, it's real.
- **Unknown**: Additional residuals in ESPRESSO data suggest
  possible further companions

### Barnard's Star (M4 V, 5.96 ly)

```
z = 1.91 × 10⁻⁶  (measured: CARMENES spectral lines)
k = 723.6
κ = R·z = 1.364e8 × 1.91e-6 = 0.261 m
v_surface = c/k = 414 km/s
```

- **Confirmed**: Barnard b (0.37 M⊕, 3.15 d)
- **Candidates**: Additional signals from ESPRESSO/MAROON-X
  in the 2–10 d period range, not yet confirmed
- **History**: Decades of spurious claims — zk²=1 would have
  immediately separated stellar surface z from wobble z

### Tau Ceti (G8.5 V, 11.9 ly)

```
z = 2.08 × 10⁻⁶  (measured: HARPS spectral lines)
k = 693.5
κ = R·z = 5.517e8 × 2.08e-6 = 1.148 m
v_surface = c/k = 432 km/s
```

- **Candidates**: 4 planets proposed (e, f, g, h) from RV
- **Problem**: Star is nearly pole-on, very low activity
  - Signals at the noise floor (~0.5–1 m/s)
  - Stellar activity vs planet ambiguity persists
- **zk²=1 approach**: z = 2.08e-6 is the baseline.
  A 2 M⊕ planet at 0.5 AU produces Δz ~ 1.2 × 10⁻¹⁰.
  The stellar activity noise floor is ~ 5 × 10⁻¹⁰.
  Separating these requires the baseline to be EXACT.
  zk²=1 gives that exact baseline.

### Epsilon Eridani (K2 V, 10.5 ly)

```
z = 2.37 × 10⁻⁶  (measured: HARPS spectral lines)
k = 649.8
κ = R·z = 5.113e8 × 2.37e-6 = 1.212 m
v_surface = c/k = 461 km/s
```

- **Confirmed**: Epsilon Eridani b (~0.76 M_Jup, ~7.4 yr)
- **Problem**: Young star, magnetically active, massive
  debris disk. RV data is dominated by stellar noise.
- **Additional companions**: Suspected from RV+astrometry,
  but parameters keep getting revised
- **zk²=1 approach**: Clean the stellar surface contribution
  with z = 2.37e-6, then the residual maps the system

### GJ 876 (M4 V, 15.2 ly)

```
z = 2.26 × 10⁻⁶  (measured: HIRES/Keck spectral lines)
k = 665.0
κ = R·z = 2.616e8 × 2.26e-6 = 0.591 m
v_surface = c/k = 451 km/s
```

- **Confirmed**: 4 planets (b, c, d, e) — one of the most
  complex known systems
- **Residuals**: Even after fitting 4 planets, significant
  RV residuals remain
- **zk²=1 approach**: Use z as baseline. The 4-planet
  model predicts specific Δz patterns. Residuals beyond
  that model are candidate planet 5+.

### HD 10180 (G1 V, 127 ly)

```
z = 2.11 × 10⁻⁶  (measured: HARPS spectral lines)
k = 688.5
κ = R·z = 7.722e8 × 2.11e-6 = 1.629 m
v_surface = c/k = 435 km/s
```

- **Confirmed**: 6 planets (b through g)
- **Candidates**: Planet h and i proposed but unconfirmed
- **Status**: One of the richest planetary systems known,
  but orbital architecture is not fully resolved
- **Residuals suggest additional low-mass companions**

### TRAPPIST-1 (M8 V, 40.7 ly)

```
z = 1.63 × 10⁻⁶  (measured: transit + spectral fitting)
k = 783.4
κ = R·z = 8.418e7 × 1.63e-6 = 0.137 m
v_surface = c/k = 383 km/s
```

- **Confirmed**: 7 planets (b through h)
- **Problem**: TTVs (transit timing variations) constrain
  masses, but densities still debated
- **zk²=1 approach**: The stellar baseline z tells you
  the displacement environment. Each planet's transit
  introduces a Δz from its own spectral signature. The TTV
  residuals should map to specific k-values of each planet.

---

## 3. The Method

For ANY star with spectroscopic observations:

```
1. Measure z from spectral lines (this IS the observation)
2. k = 1/√z
3. κ = R·z   (R measured from luminosity + distance, or interferometry)
4. v_surface = c/k
5. v(r) = (c/k)·√(R/r)  for orbital velocity at any distance r
6. Monitor z over time — the VARIATION is the signal:
   - Periodic Δz = planetary wobble
   - Quasi-periodic Δz = stellar activity
   - Systematic Δz = rotational broadening
7. The PERIODIC component = the planet.
```

The key insight: **z is measured. k follows. κ follows.**
No G. No M. No model. The baseline is the light itself.

Every m/s of wobble = Δz of 3.3 × 10⁻⁹.
A Jupiter at 1 AU = K ≈ 12.5 m/s = Δz ≈ 4.2 × 10⁻⁸.
An Earth at 1 AU = K ≈ 0.09 m/s = Δz ≈ 3.0 × 10⁻¹⁰.

The z baseline is ~10⁻⁶.
The planetary signal is ~10⁻⁸ to 10⁻¹⁰.
The separation is 2–4 orders of magnitude.

**zk²=1 doesn't find the planet. It removes the star.**
What's left is the system.

---

## 4. The PA-99-N2 Reconstruction

For the M31 microlensing candidate, we can attempt a
reconstruction using the limited data:

```
Host: most likely K-dwarf lens star
  z ≈ 1.07 × 10⁻⁶  (estimated from K7V spectral class)
  k ≈ 968
  R ≈ 3.479e+08 m
  κ = R·z = 0.372 m
  v_surface = c/k = 310 km/s

Companion: ~6.3 M_Jup (from microlensing light curve)
  Estimated wobble K ≈ 190 m/s
  Δz_wobble = K/c = 6.3 × 10⁻⁷
  Δz/z_host ≈ 59% — massive signal, easily detectable
  if we could resolve the star spectroscopically
```

The companion's own spatial displacement:

```
R_comp ≈ 7.149e+07 m  (1.0 R_Jup)
z_comp ≈ 1.59 × 10⁻⁷  (estimated from gas giant spectral class)
k_comp ≈ 2510
κ_comp = R·z = 0.011 m

The companion has k ≈ 2510, the host has k ≈ 968.
The k-ratio encodes the relationship between the two
displacement fields in the system.
```

---

## 5. What This Means for Future M31 Work

Current instruments cannot resolve individual M31 stars well
enough for RV planet detection. But:

1. **JWST** can resolve and classify individual bright stars
   (supergiants, Cepheids, bright giants) in M31
2. **ELT/TMT** (expected ~2028) will have the resolving power
   to obtain high-resolution spectra of M31 red giants
3. **With zk²=1**: Once you measure z from the spectral lines,
   you have k. v(r) = (c/k)·√(R/r) gives the orbital velocity
   at any distance. The system architecture follows from z alone
   — even at 2.5 million light-years.

The relation doesn't care about distance. It's z. And z is z.
