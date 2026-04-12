# INVESTIGATION: Flyby Anomaly, Pioneer Acceleration, and Earthgrazer Trajectory Prediction

> **SDT Domain**: Convergent Boundary Pressure (Law III), Solar Accretion Geometry
> **Status**: Active Investigation
> **Author**: James Christopher Tyndall

---

## 1. Abstract

Six spacecraft performing Earth gravity assists between 1990 and 2005 exhibited anomalous velocity changes (Δv) not predicted by standard Newtonian gravity or General Relativity. The measured anomalies range from +13.46 mm/s (NEAR) to -4.6 mm/s (Galileo II). Anderson et al. (2008) proposed an empirical formula correlating the anomaly with the asymmetry of the flyby geometry — specifically the difference in geocentric declinations of the incoming and outgoing trajectories.

SDT provides a mechanistic explanation: the Earth's convergence gradient is not spherically symmetric. It contains a rotational component inherited from the solar accretion geometry (the solar convergence gradient's equatorial enhancement). Asymmetric flyby trajectories traverse different sectors of this rotational gradient, experiencing differential pressure that produces the observed velocity anomalies.

This investigation extends the analysis to:
1. All known flyby anomaly cases
2. The Pioneer anomalous deceleration
3. Earthgrazer comets as a predictive test case
4. NASA "keyhole" trajectory calculations as a resolution target

---

## 2. The Flyby Anomaly — Complete Dataset

### 2.1 Measured Anomalies (Anderson et al. 2008)

| Spacecraft | Flyby Date | Closest Approach (km) | v∞ (km/s) | δ_in (°) | δ_out (°) | Measured Δv (mm/s) |
|-----------|-----------|----------------------|-----------|----------|----------|-------------------|
| Galileo I | 1990-12-08 | 960 | 8.949 | -12.5 | -34.2 | **+3.92 ± 0.08** |
| Galileo II | 1992-12-08 | 303 | 8.877 | -34.3 | -4.9 | **-4.60 ± 1.0** |
| NEAR | 1998-01-23 | 539 | 6.851 | -20.8 | -71.9 | **+13.46 ± 0.13** |
| Cassini | 1999-08-18 | 1,175 | 16.01 | -12.9 | -4.99 | **-2.0 ± 1.0** |
| Rosetta I | 2005-03-04 | 1,956 | 3.863 | -2.8 | -34.3 | **+1.82 ± 0.05** |
| MESSENGER | 2005-08-02 | 2,347 | 4.056 | 31.4 | -31.9 | **+0.02 ± 0.01** |

### 2.2 Anderson's Empirical Formula

Anderson et al. proposed:

> Δv∞ = K × v∞ × (cos δ_in - cos δ_out)

With K = 2ωR/c ≈ 3.099 × 10⁻⁶, where ω is Earth's angular rotation rate and R is Earth's radius.

This formula fits the first five cases reasonably well. But it is purely empirical — it has no physical mechanism. It correlates the anomaly with the flyby geometry but does not explain WHY the geometry matters.

### 2.3 Later Flybys

| Spacecraft | Flyby Date | Measured Δv (mm/s) | Notes |
|-----------|-----------|-------------------|-------|
| Rosetta II | 2007-11-13 | ≈ 0 | Within measurement error |
| Rosetta III | 2009-11-13 | ≈ 0 | Within measurement error |
| Juno | 2013-10-09 | ≈ 0 | Within measurement error |

The null results from later flybys led the community to dismiss the anomaly as systematic error. However, the null results may themselves be informative — these later flybys had different geometries (declination asymmetries) and closest approach altitudes.

---

## 3. SDT Explanation

### 3.1 The Rotational Convergence Gradient

Earth orbits within the Sun's accretion geometry. The solar convergence gradient has a rotational component — the equatorial enhancement — that produces the ecliptic orbital plane. Earth inherits this geometry: its own convergence gradient contains a rotational component aligned with its orbital motion.

This rotational component is small relative to the spherically symmetric part of the gradient, but it is NOT zero. A spacecraft on a symmetric flyby trajectory (equal declination in and out) traverses equal rotational gradient on both sides — the rotational contribution cancels. A spacecraft on an asymmetric trajectory does NOT traverse equal gradient — the rotational contribution produces a net Δv.

### 3.2 Why the Anderson Formula Works

Anderson's formula Δv = K × v∞ × (cos δ_in - cos δ_out) works because:

1. **v∞ dependence**: Faster spacecraft spend less time in the gradient, so the integrated impulse scales with v∞ (this is unusual — most perturbations scale inversely with v∞).
2. **(cos δ_in - cos δ_out) dependence**: This measures the asymmetry of the trajectory relative to the equatorial plane. Equatorial flybys (δ ≈ 0) encounter the strongest rotational gradient. Polar flybys (δ ≈ ±90°) encounter the weakest. The difference between ingress and egress projections measures the net asymmetry.
3. **K = 2ωR/c**: Earth's surface velocity ωR ≈ 465 m/s. The factor K ≈ 2 × 465 / c ≈ 3.1 × 10⁻⁶. SDT explains this as the ratio of Earth's rotational convergence gradient to the radial gradient — the "tilt" of the convergence field due to Earth's co-rotation with the Sun's accretion geometry.

### 3.3 Why Later Flybys Showed No Anomaly

The null results from Rosetta II, III, and Juno are consistent with SDT if these flybys had:
- More symmetric declination geometry (cos δ_in ≈ cos δ_out)
- Higher closest approach altitudes (gradient falls as 1/r²)
- Equatorial geometry where the gradient is strongest but symmetrically sampled

This must be verified against the actual trajectory data for each flyby.

### 3.4 SDT Prediction for the Anomaly Magnitude

The rotational convergence gradient at Earth's surface is proportional to:

> g_rot = (v_orb / c)² × g_surface

Where v_orb = 29.78 km/s (Earth's orbital velocity) and g_surface = 9.81 m/s².

> g_rot = (29,780 / 299,792,458)² × 9.81 ≈ 9.67 × 10⁻⁸ m/s²

This is the acceleration produced by the rotational convergence gradient at Earth's surface. For a flyby at 1000 km altitude with v∞ = 7 km/s:

> Δv ≈ g_rot × (2R/v∞) × sin(asymmetry angle)

This produces anomalies in the mm/s range — matching the observations.

---

## 4. The Pioneer Anomaly — Reanalysis

### 4.1 The Original Anomaly

Pioneer 10 and 11 exhibited an anomalous sunward acceleration of a_P = (8.74 ± 1.33) × 10⁻¹⁰ m/s² from ~20 AU to ~70 AU.

In 2012, this was attributed to anisotropic thermal radiation from the spacecraft's RTGs. The thermal recoil explanation resolved ~80% of the anomaly. The remaining ~20% was within systematic uncertainties.

### 4.2 SDT Interpretation

SDT does not dispute the thermal recoil contribution. However, SDT predicts that ALL spacecraft crossing into the outer solar system should experience a small additional sunward bias from the convergence pressure gradient:

> a_SDT = d/dr [P_conv(r)] × A_cross / m

Where P_conv(r) is the convergence pressure at distance r from the Sun, A_cross is the spacecraft's cross-sectional area, and m is its mass. The convergence pressure decreases with distance from the Sun (the Sun's convergence domain falls off as 1/r²), producing a net sunward gradient.

### 4.3 Predictive Test

A purpose-built, thermally symmetric probe with:
- Isotropic thermal emission (no RTG thermal bias)
- High m/A ratio (to minimise radiation pressure)
- Large heliocentric distance (30+ AU)
- Sub-nm/s² accelerometry (LISA Pathfinder heritage)

Should show ZERO anomalous acceleration if the Pioneer effect was entirely thermal. SDT predicts a residual sunward acceleration of order 10⁻¹¹ m/s² from the convergence gradient.

---

## 5. Earthgrazer Comets — SDT Predictive Model

### 5.1 The Opportunity

Earthgrazer comets — objects that make close approaches to Earth — should exhibit the SAME asymmetric anomaly as spacecraft, but WITHOUT engines, antennas, or thermal emission to confuse the analysis. They are clean test particles.

### 5.2 SDT Predictions for Earthgrazers

For a comet making a close Earth approach at perigee distance r_p, incoming declination δ_in, and outgoing declination δ_out:

> Δv_predicted = K × v_hyp × (cos δ_in - cos δ_out)

Where K = 2ωR/c ≈ 3.099 × 10⁻⁶ and v_hyp is the hyperbolic excess velocity.

Specific predictions:

1. **Comets with asymmetric ingress/egress declination should show measurable Δv anomalies.**
2. **The anomaly should scale with v_hyp, not inversely.**
3. **Symmetric encounters (δ_in ≈ δ_out) should show Δv ≈ 0.**
4. **The anomaly should be mass-independent** — a 100-kg spacecraft and a 10⁹-kg comet should show the same Δv for the same geometry.

### 5.3 Known Candidates

| Object | Year | Minimum Distance | v_hyp (km/s) | Geometry |
|--------|------|-----------------|-------------|----------|
| 2023 BU | 2023 | 3,540 km | ~9.3 | Near-equatorial |
| Apophis | 2029 | ~31,000 km | ~4.6 | Asymmetric |
| 2024 YR4 | 2032 | TBD | ~7.2 | TBD |
| 2019 OK | 2019 | ~72,000 km | ~24.5 | Highly asymmetric |

Apophis (2029) is the prime target. Its close approach in April 2029 will be tracked by every major telescope and radar facility on Earth. SDT predicts that the post-encounter trajectory will differ from pure-gravitational predictions by:

> Δv_Apophis ≈ 3.1 × 10⁻⁶ × 4600 × (cos δ_in - cos δ_out)

For the predicted geometry (δ_in ≈ +40°, δ_out ≈ -25°):

> Δv ≈ 3.1 × 10⁻⁶ × 4600 × (cos 40° - cos(-25°)) = 3.1 × 10⁻⁶ × 4600 × (0.766 - 0.906) = -2.0 mm/s

This is a small but potentially measurable velocity shift that would accumulate into a trajectory deviation over the following months of tracking.

### 5.4 Resolving the "Keyhole" Problem

NASA currently identifies gravitational "keyholes" — narrow corridors in space through which an asteroid must pass during one close encounter to be on a collision course during a later return. These keyholes are typically a few hundred metres to a few kilometres wide.

The keyhole calculations use pure gravitational trajectories plus Yarkovsky effect corrections. They do NOT include the flyby anomaly.

If the flyby anomaly is real and mass-independent (as SDT predicts), then:
1. **Every keyhole calculation for Earth-approaching asteroids is slightly wrong.**
2. **The error is proportional to the flyby asymmetry.**
3. **For highly asymmetric encounters, the error could exceed the keyhole width.**

SDT predicts that incorporating the rotational convergence gradient into trajectory calculations will:
- Shift some objects INTO keyholes that are currently considered misses
- Shift some objects OUT OF keyholes that are currently considered hits
- The net effect is small but deterministic, and could matter for planetary defence

This is not speculative alarm. It is a call for rigorously computing the rotational gradient correction and incorporating it into trajectory forecasting.

---

## 6. Data Sources

| Source | URL | Content |
|--------|-----|---------|
| Anderson et al. 2008 | PRL 100, 091102 | Original flyby anomaly paper |
| Turyshev et al. 2012 | PRL 108, 241101 | Pioneer anomaly thermal recoil |
| Rosetta navigation | ESA | Rosetta II/III null results |
| Juno flyby | NASA/JPL | 2013 null result |
| Apophis 2029 | NASA/JPL CNEOS | Close approach parameters |
| Anderson formula | PRL 100, 091102 | K = 2ωR/c empirical fit |

---

## 7. Computation Plan

### 7.1 Immediate (calculable now)

- [ ] Verify the Anderson formula against all six original flybys using SDT's rotational gradient interpretation
- [ ] Calculate the expected gradient strength at Earth's surface from the solar accretion geometry
- [ ] Check whether the null results (Rosetta II/III, Juno) are consistent with their specific declination geometries
- [ ] Compute SDT Δv prediction for Apophis 2029 using preliminary trajectory data

### 7.2 Predictive (before 2029)

- [ ] Generate a table of SDT-predicted Δv for all Earth-approaching objects with perigee < 100,000 km in the JPL CNEOS database
- [ ] Contact CNEOS for historical trajectory residuals of past earthgrazers
- [ ] Develop a C++20 tool (zk2_flyby_anomaly.cpp) that takes orbital elements and computes the SDT Δv correction

### 7.3 Validation (during/after Apophis 2029)

- [ ] Compare SDT-predicted post-flyby trajectory to observed trajectory
- [ ] If Δv matches: publish as SDT validation of the flyby anomaly mechanism
- [ ] If Δv does not match: constrain the rotational gradient magnitude

---

## 8. Impact

### If the flyby anomaly is confirmed as a convergence gradient effect:

1. Every gravity assist trajectory in the solar system gets a small correction
2. Keyhole calculations for planetary defence become more accurate
3. The anomaly becomes a TOOL — measuring the rotational convergence gradient of every body in the solar system
4. Jupiter, Saturn, Neptune flybys should show LARGER anomalies (larger bodies, stronger rotational gradients)

### If not confirmed:

1. The convergence gradient's rotational component is undetectable at spacecraft scales
2. Earthgrazer predictions remain as a further test at astronomical scales

---

*Investigation initiated April 2026.*
*James Christopher Tyndall — Melbourne, Australia*
