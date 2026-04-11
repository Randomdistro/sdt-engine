# Hubble Tension — Collected Data

---

## 1. H₀ Measurements (All Methods)

### 1.1 Early-Universe (CMB-derived)

| Measurement | H₀ (km/s/Mpc) | Uncertainty | Year | Model | Reference |
|-------------|---------------|------------|------|-------|-----------|
| Planck TT,TE,EE+lowE+lensing | 67.4 | ± 0.5 | 2018 | ΛCDM flat | Planck VI, A&A 641 A6 |
| Planck TT,TE,EE+lowE+lensing+BAO | 67.66 | ± 0.42 | 2018 | ΛCDM flat | Planck VI |
| WMAP-9+ACT+SPT | 69.3 | ± 0.7 | 2013 | ΛCDM | Bennett et al. |

### 1.2 Late-Universe (Distance Ladder)

| Measurement | H₀ (km/s/Mpc) | Uncertainty | Year | Calibrator | Reference |
|-------------|---------------|------------|------|-----------|-----------|
| SH0ES | 73.04 | ± 1.04 | 2022 | Cepheids | Riess et al., ApJL 934 |
| SH0ES (earlier) | 73.2 | ± 1.3 | 2021 | Cepheids | Riess et al. |
| SH0ES (JWST confirmed) | 72.6 | ± 2.0 | 2024 | Cepheids (JWST) | Riess et al. |
| CCHP (TRGB+JAGB combined) | 69.96 | ± 1.05(stat) ± 1.12(sys) | 2024 | TRGB+JAGB | Freedman et al., ApJ 985 |
| CCHP (TRGB JWST only) | 68.81 | ± 1.79(stat) ± 1.32(sys) | 2024 | TRGB | Freedman et al. |
| H₀LiCOW/TDCOSMO | 73.3 | +1.7 −1.8 | 2020 | Strong lensing | Wong et al. |
| TDCOSMO (2025) | 71.6 | ± 4.6% | 2025 | Strong lensing (8 systems) | TDCOSMO VII |
| Megamaser (NGC 4258) | 73.9 | ± 3.0 | 2020 | Geometric maser | Pesce et al. |
| Surface brightness fluct. | 73.3 | ± 0.7(stat) ± 2.4(sys) | 2021 | SBF | Blakeslee et al. |

### 1.3 Intermediate / Other

| Measurement | H₀ (km/s/Mpc) | Uncertainty | Method |
|-------------|---------------|------------|--------|
| BAO + BBN (no CMB) | 67.6 | ± 1.1 | BAO inverse ladder |
| DES Y3 + BAO + BBN | 67.4 | +1.1 −1.2 | Inverse ladder |
| Gravitational wave (GW170817) | 70 | +12 −8 | Standard siren |

---

## 2. Planck 2018 Cosmological Parameters

| Parameter | Symbol | Value | Uncertainty |
|-----------|--------|-------|------------|
| Hubble constant | H₀ | 67.4 km/s/Mpc | ± 0.5 |
| Matter density | Ω_m | 0.315 | ± 0.007 |
| Baryon density | Ω_b h² | 0.0224 | ± 0.0001 |
| Dark matter density | Ω_c h² | 0.120 | ± 0.001 |
| Dark energy density | Ω_Λ | 0.685 | ± 0.007 |
| Angular acoustic scale | 100θ_* | 1.0411 | ± 0.0003 |
| Spectral index | n_s | 0.965 | ± 0.004 |
| Optical depth | τ | 0.054 | ± 0.007 |
| Fluctuation amplitude | σ₈ | 0.811 | ± 0.006 |
| Age of universe | t₀ | 13.787 Gyr | ± 0.020 |
| Sound horizon (drag) | r_d | 147.09 Mpc | ± 0.26 |
| Recombination redshift | z_* | 1089.92 | ± 0.25 |
| CMB temperature | T_CMB | 2.7255 K | ± 0.0006 |

---

## 3. Pantheon+ Summary Statistics

| Property | Value |
|----------|-------|
| Total light curves | 1,701 |
| Unique SN Ia | 1,550 |
| Contributing surveys | 18 |
| Redshift range | 0.001 – 2.26 |
| Median redshift | ~0.1 |
| Systematic covariance | Full 1701 × 1701 matrix |
| Source | github.com/PantheonPlusSH0ES |

### Distance Modulus Binned Data (representative)

| z_bin | N_SN | μ_mean (mag) | σ_μ |
|-------|------|-------------|-----|
| 0.01 | ~50 | 33.2 | 0.15 |
| 0.03 | ~100 | 35.4 | 0.12 |
| 0.05 | ~80 | 36.5 | 0.13 |
| 0.1 | ~200 | 38.2 | 0.11 |
| 0.3 | ~250 | 40.8 | 0.10 |
| 0.5 | ~150 | 42.1 | 0.12 |
| 0.7 | ~100 | 43.0 | 0.14 |
| 1.0 | ~50 | 44.0 | 0.18 |

(Note: binned values are approximate; full data uses individual SN)

---

## 4. SH0ES Distance Ladder Structure

### Rung 1: Geometric Anchors

| Anchor | Type | Distance | Uncertainty |
|--------|------|---------|------------|
| Milky Way Cepheids | Gaia EDR3 parallax | various | ~2% per star |
| LMC | Eclipsing binaries | 49.59 kpc | ± 0.09 kpc (0.2%) |
| NGC 4258 | Water masers | 7.576 Mpc | ± 0.082 (1.1%) |

### Rung 2: Cepheid-SN Ia Hosts

| Property | Value |
|----------|-------|
| Host galaxies observed | 37 |
| SN Ia in hosts | 42 |
| Cepheids observed | ~2,200 |
| HST orbits used | ~1,000 |
| Observation span | 20 years |
| Instrument | HST WFC3 (F555W, F814W, F160W) |

### Rung 3: Hubble Flow

| Property | Value |
|----------|-------|
| SN Ia sample | Pantheon+ (1,550 SN) |
| z range for H₀ | 0.023 < z < 0.15 |
| Peculiar velocity correction | Applied (~300 km/s) |

---

## 5. Acceleration Evidence (1998)

### Key Observation

| z range | Expected μ (decelerating) | Observed μ | Difference |
|---------|--------------------------|-----------|-----------|
| 0.3–0.5 | ~42.0 | ~42.2 | +0.2 mag (dimmer) |
| 0.5–0.8 | ~43.0 | ~43.25 | +0.25 mag (dimmer) |
| 0.8–1.0 | ~43.5 | ~43.6 | +0.1 mag (converging) |

SN Ia at z ≈ 0.5 were ~0.25 magnitudes fainter than expected for
a matter-dominated decelerating universe. This implies they are
~12% more distant than the decelerating model predicts.

### Deceleration Parameter

| Model | q₀ | Ω_Λ |
|-------|----|-----|
| Matter only | +0.5 | 0 |
| Observed (1998) | −0.55 ± 0.17 | ~0.7 |
| Planck ΛCDM | −0.527 | 0.685 |

---

## 6. BAO Scale

| Quantity | Value | Uncertainty |
|---------|-------|------------|
| Comoving sound horizon (Planck) | 147.09 Mpc | ± 0.26 Mpc |
| Physical sound horizon | 144.43 Mpc | ± 0.26 Mpc |
| Angular scale on CMB | θ_s = 0.596° | measured |
| BAO peak in galaxy clustering | ~150 Mpc/h | measured |
| Sound speed (pre-Clearing) | c/√3 = 1.73 × 10⁸ m/s | from theory |

---

## 7. KBC Void (Local Underdensity)

| Property | Value | Reference |
|----------|-------|-----------|
| Radius | ~300 Mpc | Keenan, Barger, Cowie 2013 |
| Density contrast δ | −0.15 to −0.46 | KBC, galaxy luminosity density |
| Method | K-band galaxy count | 2MASS, 6dFGRS |
| SDT required δ | −0.077 | From H₀ ratio (Section 9) |

---

## 8. SDT-Specific Quantities

### Compression Coefficient κ

| Region | κ = H₀/c (Mpc⁻¹) | H₀ (km/s/Mpc) | Density class |
|--------|-------------------|---------------|--------------|
| Global mean | 2.247 × 10⁻⁴ | 67.4 | cosmic average |
| TRGB sample | 2.333 × 10⁻⁴ | 70.0 | intermediate |
| Lensing paths | 2.387 × 10⁻⁴ | 71.6 | overdense paths |
| Local (~300 Mpc) | 2.435 × 10⁻⁴ | 73.0 | local underdense |

### Pressure-Temperature Scaling

| z | T (K) | T/T₀ | κ/κ₀ (if T⁴) |
|---|-------|------|-------------|
| 0 | 2.7255 | 1 | 1 |
| 0.5 | 4.088 | 1.5 | 5.06 |
| 1.0 | 5.451 | 2.0 | 16 |
| 2.0 | 8.177 | 3.0 | 81 |
| 10 | 29.98 | 11.0 | 1.46 × 10⁴ |
| 100 | 275.3 | 101 | 1.04 × 10⁸ |
| 1100 | 2,998 | 1100 | 1.46 × 10¹² |

---

## 9. Timeline Comparison

| Framework | Age | Mechanism |
|-----------|-----|-----------|
| ΛCDM | 13.787 ± 0.020 Gyr | Expansion from initial singularity |
| SDT | ~48 Gyr | Lattice traversal time R_CMB/c |
| Ratio | 3.48× | SDT timeline is 3.48× longer |
