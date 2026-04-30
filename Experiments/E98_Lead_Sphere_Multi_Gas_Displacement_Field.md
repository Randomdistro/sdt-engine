# E98 — Lead Sphere Displacement Field: Directional Gas Tube Array & Vacuum Persistence Test

## Experiment ID: E98
## Status: PROPOSED (laboratory)
## Domain: Gravity / Occlusion / Displacement Field / Molecular Persistence
## Axiom Compliance: ✅ No G, No M, No GM
## Location: ~18 m ASL, inside Earth's convergence well (g = 9.82 m/s²)

---

## 1. Core Questions

1. **Can a 10m lead sphere bend the gas separation planes in sealed gradient tubes?**
2. **At near-vacuum, do gas molecules persist on the lead sphere's surface
   beyond what thermal statistics predict?**
3. **Does the convergence gradient interact differently with diatomic O₂ vs N₂
   at very low pressures — where gas-gas collisions no longer mask
   molecule-field interactions?**

## 2. The Lead Ball

| Property | Value | Derivation |
|----------|-------|-----------|
| Diameter | 10.0 m | |
| Radius (R) | 5.0 m | |
| Material | Lead (Pb, Z=82) | |
| Density (ρ) | 11,340 kg/m³ | |
| ρ × V | 5,934,504 kg | density × (4/3)πR³ |
| g_surface | 1.58 × 10⁻⁵ m/s² | = g_earth × (ρ_Pb/ρ_earth) × (R_ball/R_earth) |
| ϟ (koppa) | 4.40 × 10⁻¹⁹ m | = v²R/c² |

The ball sits at 18 m ASL inside Earth's convergence gradient. Earth's g is
621,000× stronger than the ball's g. The ball is a convergence pebble resting
at the bottom of a convergence ocean.

## 3. Mode A — Directional Gas Tube Array

### 3.1 The Tubes

Small sealed glass tubes (~30 cm long, ~2 cm diameter), pre-filled with a
gas mixture that separates under gravity into distinct visible layers:

| Layer | Gas | Molecular Mass (u) | Colour / Detection |
|:-----:|-----|:-----------------:|-------------------|
| Bottom | SF₆ | 146.1 | Dense, visible via IR absorption |
| Middle-low | Kr | 83.8 | Detectable via fluorescence |
| Middle | Ar | 40.0 | Detectable via spectral lines |
| Middle-high | Ne | 20.2 | Orange glow under discharge |
| Top | He | 4.0 | Lightest, detectable via thermal conductivity |

In Earth's gravity, these gases stratify into clean horizontal separation
planes. The tubes are sealed — no exchange with the chamber atmosphere.

### 3.2 Tube Placement

Tubes are mounted on a rigid frame at **30° from the centre line of the sphere**
(i.e., on a cone 60° wide, 60° apart azimuthally around the sphere). This
places them ~2.5 m from the sphere surface.

For each azimuthal position, **multiple tube orientations**:

| Orientation | Tube axis | What it probes |
|:-----------:|-----------|---------------|
| V | Vertical | Earth's gradient (control) |
| H | Horizontal | Tangential to sphere — should show no sphere effect |
| C | Pointing at sphere centre | Radial to sphere — maximum sphere effect |
| 30° | 30° between V and C | Intermediate |
| 60° | 60° between V and C | Intermediate |

**Total tubes: 6 positions × 5 orientations = 30 tubes**

Each tube also has a rotation mode — axial rotation spinners that test
whether Coriolis/rotation couples to the convergence gradient differently
for different gas layers.

### 3.3 What to Look For

**Control (V, vertical tubes):** Gas separation planes are perfectly horizontal.
Earth's g dominates. No sphere effect visible.

**Radial tubes (C, pointing at centre):** This is the key measurement. The gas
separation planes should be:
- **Standard physics:** Still stratified by Earth's g. The tube is tilted
  relative to Earth's vertical, so the planes are at the same angle as the
  tube's tilt relative to vertical. The sphere's 16 μg field adds ~0.0002%
  to the component along the tube axis. Unmeasurable.
- **SDT (if convergence gradient has near-field enhancement at ~2.5 m from
  a Z=82 nucleus cluster):** The separation planes bend slightly TOWARD
  the sphere. The heavy SF₆ layer shifts toward the sphere-facing end.
  The magnitude depends on whether the convergence gradient at 2.5 m
  distance is purely 1/r² or has a near-field correction from the
  lattice topology around a dense Pb aggregate.

**Intermediate tubes (30°, 60°):** If there IS a bending effect, these tubes
show intermediate deflection. The angular dependence maps the vector field.

**Horizontal tubes (H):** No component along the sphere's radial field.
Any bending here = systematic error or unexpected transverse coupling.

## 4. Mode B — Vacuum Persistence Test (The Real Experiment)

### 4.1 Setup

Fill the chamber (around the lead sphere) with a carefully prepared O₂/N₂
mix — the same composition as atmospheric air (78% N₂, 21% O₂, 1% Ar).

Install molecular density sensors at the sphere surface and at 0.5, 1.0,
2.0, 5.0, and 10.0 m from the surface.

### 4.2 The Pump-Down

Slowly — VERY slowly — pump the chamber down. The key is to reduce the
bulk pressure while monitoring molecular density near the sphere surface.

| Pressure regime | Mean free path | State | Notes |
|:-:|:-:|:-:|:--|
| 101,325 Pa | 68 nm | Continuum | Normal atmosphere. Gas-gas collisions dominate. Sphere's field invisible. |
| 10,000 Pa | 0.7 μm | Continuum | Still bulk gas behaviour |
| 1,000 Pa | 7 μm | Continuum | |
| 100 Pa | 70 μm | Transition | Gas-gas collisions thinning |
| 10 Pa | 0.7 mm | Transition | |
| 1 Pa | 7 mm | Molecular flow | Collisions rare |
| 0.1 Pa | 7 cm | Molecular flow | Mean free path comparable to sensor spacing |
| 0.01 Pa | 0.7 m | Molecular flow | Mean free path comparable to tube array |
| 0.001 Pa | 7 m | Free molecular | **Mean free path > sphere diameter** |
| 0.0001 Pa | 70 m | Free molecular | Individual molecules dominate |
| 0.00001 Pa | 700 m | **Sub-phonon** | **No sound transmission possible** |

### 4.3 The Sub-Phonon Threshold

Sound requires molecular collisions to propagate. When the mean free path
exceeds the measurement baseline, phonon transmission fails. For a
10-metre sphere, this happens at roughly **0.001 Pa** (7 m mean free path).

**This is the critical regime.** Below this pressure:
- No bulk gas behaviour
- Individual molecules interact directly with the sphere's convergence gradient
- Gas-gas collisions no longer mask the molecule-field interaction
- Each molecule is either bound by the sphere or escaping

### 4.4 Success Criterion

**The experiment succeeds when:**

> There is not enough atmosphere for phonon transmission, yet there is an
> appreciable collection of gas molecules still clinging to the lead sphere.

"Appreciable" means: molecular density at the sphere surface is statistically
higher than molecular density at 10 m distance, beyond what the Boltzmann
distribution at 16 μg and 293 K predicts.

The Boltzmann prediction for a 16 μg field at 293 K gives a density
enhancement of ~10⁻¹¹ at the surface relative to 1 m away. This is
effectively zero — standard physics says no molecule clings.

**If molecules are detected persisting near the surface beyond this prediction:**
the convergence gradient has a near-field component that the 1/r² model
doesn't capture. This would be the direct detection of the displacement
field topology around a macroscopic matter aggregate.

### 4.5 O₂ vs N₂ Separation at Low Pressure

As the pump-down proceeds, monitor the O₂/N₂ ratio at the sphere surface
vs far from it:

- **At high pressure:** Both gases behave identically (corrected for mass).
  Ratio stays at 21/78. The effect is LESS obvious here — gas-gas collisions
  homogenise everything.

- **At low pressure (molecular flow regime):** Individual molecules interact
  with the convergence gradient. If O₂ (paramagnetic, double bond, Z=16) 
  interacts differently from N₂ (diamagnetic, triple bond, Z=14), the ratio
  will shift near the surface.

- **O₂ has unpaired electrons.** If the ℓ=2 (spin) wake component couples
  to the convergence gradient of a dense Z=82 Pb aggregate, O₂ should be
  preferentially captured.

- **N₂ has a triple bond.** Tighter node, smaller effective cross-section.
  May interact less with the gradient.

## 5. Mode C — Rotation Tests

The tube array includes axial rotation spinners. For each tube orientation:
- Static (control)
- Slow rotation (1 rpm)
- Medium rotation (10 rpm)
- Fast rotation (100 rpm)

Rotation tests whether the convergence gradient interacts with angular
momentum. In SDT, the ℓ quantum numbers (winding numbers) determine wake
topology. External rotation couples to ℓ — if the convergence gradient
interacts with ℓ, rotated tubes should show different separation patterns.

## 6. Predictions

### Standard Physics
- Gas separation planes are determined by Earth's g alone
- No bending toward the sphere (16 μg << 9.82 m/s², ratio 1:621,000)
- No molecular persistence at sub-phonon pressures
- O₂/N₂ ratio is constant everywhere at all pressures
- Rotation has no effect on gas separation

### SDT (Convergence-Occlusion Model)
- Gas separation planes MAY bend toward the sphere if there is a near-field
  convergence enhancement around dense Z=82 aggregates
- At sub-phonon pressures, molecules MAY persist near the sphere if the
  displacement field has topology that creates local potential wells
- O₂ and N₂ MAY separate differently at low pressures due to different
  wake structures (ℓ=1 vs ℓ=0 orbital topology)
- Rotation MAY modify the interaction by coupling external angular momentum
  to internal winding numbers

### The Experimental Hierarchy (most to least likely to show an effect)
1. **Tube C (pointing at centre) at low pressure** — best alignment, least noise
2. **O₂/N₂ ratio at sphere surface at sub-phonon pressure** — no gas-gas masking
3. **Noble gas tubes at intermediate angles** — moderate alignment
4. **High pressure sweep** — gas-gas collisions wash everything out
5. **Rotation effects** — speculative, but free to test with the apparatus

## 7. What "Less Obvious at High Pressure" Means

At high pressure:
- The mean free path is short (nm to μm)
- Molecules collide constantly
- The thermal energy kT = 4.04 × 10⁻²¹ J at 293 K
- The gravitational potential energy at the sphere surface:
  m × g × R = (4.65e-26 kg) × (1.58e-5) × 5.0 = 3.67e-30 J
- Ratio: kT / (mgR) = 1.1 × 10⁹

Thermal energy is a BILLION times the gravitational potential. Gas-gas
collisions homogenise everything. The sphere's field is invisible.

At low pressure:
- Fewer collisions — individual molecule trajectories become important
- Molecules near the surface spend more time there (lower velocity component
  perpendicular to surface, on average)
- The convergence gradient acts on molecules individually, without the gas
  medium redistributing them
- Any enhanced surface interaction (adsorption, near-field convergence
  topology) acts unmasked

**The signal-to-noise ratio IMPROVES as pressure drops**, even though the
absolute number of molecules decreases. This is counterintuitive but correct:
the noise (thermal randomisation from gas-gas collisions) drops faster than
the signal (molecule-gradient interaction).

## 8. Engineering Notes

- Lead sphere: ~5,930 tonnes, cast or assembled underground
- Chamber: must achieve 0.00001 Pa (10⁻⁵ Pa) — standard UHV technology
- Tube array: 30 sealed glass tubes with noble gas mixtures, on adjustable mounts
- Molecular density sensors: quadrupole mass spectrometer at multiple positions
- Rotation spinners: small motors on tube mounts, vibration-isolated
- O₂/N₂ source: high-purity bottled gas, precision mixing
- Pump system: staged (roughing → turbo → ion pump) for controlled descent
- Temperature: 293 K ± 0.01 K throughout
- Location: underground, seismically isolated, 18 m ASL

---

*No G. No M. No GM. g = v²/R.*
*The gas tells us what the field is doing.*
*At sub-phonon pressure, the molecule talks directly to the lattice.*
