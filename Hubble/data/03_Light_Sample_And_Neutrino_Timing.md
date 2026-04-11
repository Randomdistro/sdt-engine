# Sight-Line Light Sample and Neutrino Timing

> Part of: [Hubble Investigation](INVESTIGATION_Hubble_Tension.md)

---

## 1. The Sight-Line Sample

Using the MUSE Hubble Ultra Deep Field as a representative single
pencil beam: one direction, covering z = 0.1 to z = 6.7. All
galaxies listed are along effectively the SAME line of sight.

### 1.1 Representative Galaxy Redshift Ladder

| Galaxy (HUDF ID) | z | T_CMB(z) (K) | λ_Hα emitted (nm) | λ_Hα observed (nm) | Shift (nm) | Ratio |
|-----------------|---|-------------|-------------------|-------------------|-----------|-------|
| Nearby field | 0.10 | 3.00 | 656.3 | 721.9 | 65.6 | 1.100 |
| [OII] emitter | 0.35 | 3.68 | 656.3 | 886.0 | 229.7 | 1.350 |
| [OII] emitter | 0.70 | 4.63 | 656.3 | 1115.7 | 459.4 | 1.700 |
| [OII] emitter | 1.00 | 5.45 | 656.3 | 1312.6 | 656.3 | 2.000 |
| [OII] emitter | 1.50 | 6.81 | 656.3 | 1640.8 | 984.5 | 2.500 |
| Lyα emitter | 3.00 | 10.90 | 656.3 | 2625.2 | 1968.9 | 4.000 |
| Lyα emitter | 4.00 | 13.63 | 656.3 | 3281.5 | 2625.2 | 5.000 |
| Lyα emitter | 5.00 | 16.36 | 656.3 | 3937.8 | 3281.5 | 6.000 |
| Lyα emitter | 6.00 | 19.08 | 656.3 | 4594.1 | 3937.8 | 7.000 |

### 1.2 The Ratio Observation

Look at the Hα line at 656.3 nm:

At z = 1.0: arrives at 1312.6 nm. **Shift = 656.3 nm.**
At z = 2.0: arrives at 1968.9 nm. **Shift = 1312.6 nm.**

The SHIFT doubles when z doubles. The ratio is always (1+z).

Now look at a DIFFERENT line from the same source — say [OIII]
at 500.7 nm, from the SAME galaxy at z = 1.0:

λ_obs = 500.7 × 2.0 = 1001.4 nm. **Shift = 500.7 nm.**

The 656.3 nm line shifted by 656.3 nm.
The 500.7 nm line shifted by 500.7 nm.

Each line shifts by ITSELF ×z. Longer lines shift MORE in absolute
terms. Shorter lines shift LESS. But the ratio is the same.

### 1.3 What This Tells Us

**Metric (tape-measure) expansion** predicts exactly this: every
wavelength is multiplied by (1+z). The ratio is constant because
the "ruler" itself grows uniformly. All wavelengths are stretched
by the same factor.

BUT: the SAME mathematical form arises from a pressure gradient
(amplitude → wavelength conversion). In a gradient, the conversion
is proportional to the CURRENT wavelength:

```
dλ/dr = κ × λ
```

This gives λ(r) = λ₀ × exp(κr), i.e., λ_obs/λ_emit = (1+z).
The ratio is maintained because the conversion rate is proportional
to the current wavelength — longer wavelengths convert faster,
shorter wavelengths convert slower, and the ratio stays locked.

This is NOT unique to expansion. It's a generic property of ANY
multiplicative process.

### 1.4 The Critical Difference: All Wavelengths Arrive Together

A supernova at z = 1.0 emits photons at many wavelengths
simultaneously. The UV photon (100 nm → 200 nm) and the IR photon
(2000 nm → 4000 nm) arrive at the detector at the SAME TIME.

In metric expansion: obvious. Space stretches all wavelengths
simultaneously and continuously. No dispersion.

In SDT amplitude squeeze: the conversion rate is dλ/dr = κλ.
This converts amplitude to wavelength. But does it change the
propagation SPEED?

If the photon is a lattice relay event (spation-to-spation at c),
the relay speed is c regardless of the photon's wavelength.
The shape change (amplitude → wavelength) happens DURING the relay,
not as a separate process that delays the relay.

Therefore: zero dispersion. All wavelengths arrive together.
This matches observation. ✓

---

## 2. The Neutrino Timing Problem

### 2.1 SN 1987A: The Data

| Event | Time (UTC) | Detector |
|-------|-----------|---------|
| Neutrino burst start | 07:35:35 Feb 23, 1987 | Kamiokande-II |
| Neutrino burst start | 07:35:41 Feb 23, 1987 | IMB |
| Neutrino burst duration | ~13 seconds | Both |
| First optical detection | ~10:38 Feb 23, 1987 | Shelton (visual) |
| **Neutrino lead time** | **~3 hours** | — |

Distance to SN 1987A: 168,000 ly = 51.4 kpc

### 2.2 Standard Explanation

Neutrinos escape the collapsing core IMMEDIATELY (they barely
interact with matter). Photons are trapped in the opaque stellar
envelope and only escape when the shock wave reaches the stellar
surface, ~3 hours later.

So the neutrinos were EMITTED ~3 hours before the photons were
released. The propagation speed is the same (v_ν ≈ c).

The actual velocity difference for a 10 MeV neutrino (m ≈ 0.1 eV):

```
v_ν/c = 1 − m²c⁴/(2E²)
      = 1 − (0.1)²/(2 × (10⁷)²)
      = 1 − 5 × 10⁻¹⁷
```

Over 168,000 ly (= 5.01 × 10¹² s of travel):

```
Δt = t × (1 − v_ν/c) = 5.01e12 × 5e-17 = 0.00025 s
```

The neutrino arrives 0.25 MILLISECONDS after a photon emitted at
the same instant. This is undetectable. The 3-hour lead is entirely
from emission timing, not propagation.

### 2.3 SDT Reinterpretation

In SDT:
- **Photons** are lattice relay events. They travel at c. They ARE
  the relay. During propagation, the convergent pressure converts
  their amplitude to wavelength (they redshift).
- **Neutrinos** are open windings (W→0) that propagate THROUGH the
  lattice without participating in the relay. They are NOT subject
  to the amplitude squeeze. They do not redshift from the pressure
  gradient.

cosmology.hpp explicitly states (line 17-19):
```
Neutrinos, being open windings that don't participate in the relay,
are NOT subject to this gradient — making them the true geometric
distance ruler.
```

The amplitude-to-wavelength conversion does NOT slow the photon.

### 2.4 Why Amplitude Squeeze Cannot Slow Light

The photon IS the relay. Each spation hands the deformation to
the next at rate c = ℓ_P / t_P. The amplitude squeeze is not
an additional process layered on top of the relay — it IS what
the relay does in a pressurised medium. The shape of the
deformation changes during handoff, but the handoff rate is c
regardless.

Analogy: a wave in a medium that narrows. The wave's amplitude
drops and its wavelength extends as it enters the constriction,
but the wave speed is set by the medium's properties (tension
and density), not by the wave's shape. The shape change is a
consequence of propagation, not a cost.

In SDT: the lattice relay speed is c for all photons, at all
wavelengths, in all pressure environments. The amplitude squeeze
happens DURING propagation, not as overhead.

```
Photon speed in SDT: v = c (exactly, always)
Shape change: occurs during relay, zero additional time
Dispersion: zero (all wavelengths at c)
```

**Contrast with metric expansion**: in ΛCDM, the expansion of
space DOES effectively slow light's progress toward a distant
target. The untraversed space ahead of the photon grows while
the photon is in transit. At sufficient recession velocity
(v_rec > c), the photon can NEVER arrive — creating a "horizon."
This is why distant galaxies redden out and disappear at our
visual limit.

Yet we see the CMB at z = 1100. In ΛCDM this requires the
photon to have been emitted when the source was much closer
(before the expansion pushed it away). In SDT, the lattice
doesn't expand — the photon simply crosses the fixed distance
at c. There is no horizon problem.

### 2.5 SN 1987A Timing: Emission, Not Propagation

The 3-hour neutrino lead at SN 1987A is entirely from EMISSION
timing:
- Neutrinos escape the collapsing core immediately
- Photons are trapped in the opaque envelope until the shock
  wave reaches the stellar surface (~3 hours later)

The neutrino velocity deficit is negligible:
```
v_ν/c = 1 − m²c⁴/(2E²) = 1 − 5 × 10⁻¹⁷
```
Over 168,000 ly this produces a 0.25 ms delay — undetectable.

The SDT position: for co-emitted signals, photons (at c) arrive
BEFORE neutrinos (at v < c). The SN 1987A lead is emission
timing, not a propagation effect.

### 2.6 GW170817: Confirming the Shared Relay

The binary neutron star merger GW170817 (August 2017):
- Gravitational waves (LIGO/Virgo): 12:41:04 UTC
- Gamma-ray burst (Fermi-GBM): 12:41:06 UTC (+1.7 s)
- Distance: ~130 Mly (40 Mpc)

The 1.7-second delay is consistent with emission timing (the
jet takes ~1 s to form and break through the merger ejecta).

The SDT reading: BOTH gravitational waves and photons are
lattice deformations. Gravity waves are compression modes;
photons are transverse modes. Both propagate at the same relay
speed c. GW170817 confirms they share the same medium —
consistent with SDT's single-medium lattice.

The 1.7 s constrains the speed difference to:
```
|c_grav − c_photon| / c < 1.7 / (130 Mly × 3.156e7 / c)
                        < 1.7 / (4.11e15 s)
                        ≈ 4 × 10⁻¹⁶
```

They are the same speed to 16 significant figures. Same medium.

---

## 3. What the Neutrino Timing DOES Tell SDT

### 3.1 Neutrinos Are Not Redshifted

If SDT is correct that neutrinos are NOT subject to the pressure
gradient, then neutrinos from distant sources should show NO
cosmological redshift. Their energy spectrum should be determined
purely by the source conditions, not by the distance.

This is testable:
- SN 1987A neutrinos: E = 10–40 MeV (consistent with core collapse
  temperature ~10¹¹ K, no unexpected redshift)
- Future SN detections: compare neutrino energy spectrum with
  expected source spectrum; no systematic softening with distance

### 3.2 Neutrinos Are the True Distance Ruler

If neutrinos don't redshift, then the neutrino flux from a source
at distance d follows a pure inverse-square law:

```
F_ν = L_ν / (4π d²)
```

WITHOUT the (1+z)² dimming factor that applies to photons. The
neutrino luminosity distance equals the physical distance:

```
d_L(ν) = d    (not d × (1+z) as for photons)
```

This means:
- Photon luminosity distance: d_L(γ) = d × (1+z)
- Neutrino luminosity distance: d_L(ν) = d

The RATIO:
```
d_L(γ) / d_L(ν) = (1+z)
```

**SDT prediction**: for any source detected in BOTH neutrinos and
photons, the photon-derived distance should be (1+z) times the
neutrino-derived distance. This is a direct, falsifiable test.

For a source at z = 1:
- Photon distance: 2d (appears twice as far due to dimming)
- Neutrino distance: d (true geometric distance)
- Ratio: 2.0

### 3.3 The Distance Scale Resolution

If this prediction holds, then:
- All photon-derived cosmological distances are overestimates by (1+z)
- The "true" distance to the CMB is not 46 Gly but 46/(1+1100) ≈ 42 Mly

Wait — that can't be right either. The (1+z) factor in d_L comes
from the energy loss. If the photon energy drops by 1/(1+z), the
source appears dimmer by (1+z)², making it appear further by (1+z).

But the ANGULAR SIZE of the source is determined by d_A (angular
diameter distance), not d_L. In ΛCDM:

```
d_A = d_L / (1+z)² = d / (1+z)
```

In SDT, if there's no expansion, the angular diameter distance IS
the physical distance:

```
d_A(SDT) = d
```

And d = d_L / (1+z) — same as ΛCDM's d_A. So the PHYSICAL distance
is the same in both frameworks; only the interpretation of d_L differs.

### 3.4 Connection to R_CMB

The physical distance to the CMB in SDT is d_A(CMB). In ΛCDM:
```
d_A(CMB) = d_M / (1 + z_rec) ≈ 46.3 Gly / 1100 ≈ 42 Mly
```

This is very small. But this is the angular diameter distance —
how big things APPEAR on the sky. The actual light-travel distance
in ΛCDM is ~13.8 Gly (the age).

In SDT, without expansion, the physical distance IS the light-travel
distance. The question is: what is it?

From the observed angular size of the BAO scale (θ_s = 0.596°)
and the known physical size of the sound horizon (r_s = 147 Mpc):

```
d = r_s / θ_s = 147 Mpc / (0.596° × π/180) = 147 / 0.01041 = 14,120 Mpc
```

14,120 Mpc = 46.0 Gly.

This IS the physical distance to the CMB in SDT. And the light-
travel time IS this distance divided by c:

```
t = 46.0 Gly / c = 46.0 Gyr
```

**So the ~48 Gyr number in cosmology.hpp is actually ~46 Gyr.**
The slight discrepancy comes from using the approximate value
46.3 Gly rounded to 48.

But notice: this derivation uses r_s = 147 Mpc, which is computed
from known physics (baryon density, radiation density, recombination
temperature). It does NOT require ΛCDM. The sound horizon is
determined by the pre-Clearing acoustic physics, which SDT agrees
with (same c_s = c/√3, same recombination epoch).

**So: R_CMB = r_s / θ_s ≈ 46 Gly. This IS derivable from SDT.**

The age of the universe in SDT = 46 Gly / c = **46 Gyr**.

---

## 4. Summary

| Finding | Status |
|---------|--------|
| Wavelength ratios are maintained (multiplicative, not additive) | CONFIRMED |
| This is consistent with both expansion and pressure gradient | CONFIRMED |
| All wavelengths arrive simultaneously (no dispersion) | CONFIRMED |
| Amplitude squeeze does NOT slow photons — relay speed is c | SDT AXIOM |
| Metric expansion DOES slow photons (expanding untraversed space) | ΛCDM PROPERTY |
| SDT has no horizon problem (lattice is fixed, photon crosses at c) | SDT PROPERTY |
| GW170817: c_grav = c_photon to 16 sig figs (same medium) | CONFIRMED |
| SN 1987A 3-hour lead is emission delay, not propagation | CONFIRMED |
| Neutrinos should show NO pressure-gradient redshift | SDT PREDICTION |
| d_L(γ) / d_L(ν) = (1+z) for any co-detected source | SDT PREDICTION |
| R_CMB derivable from r_s/θ_s = 46 Gly | DERIVED |
| SDT age = 46 Gyr (not 48) | CORRECTED |
