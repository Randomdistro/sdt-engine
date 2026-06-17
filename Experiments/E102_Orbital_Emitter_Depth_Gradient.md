# E102: Orbital Emitter Depth-Gradient Test (the Sundiver Spectrometer)

> **Category**: Convergence Depth / Variable Spation Closure
> **Difficulty**: FEASIBLE NOW (existing trajectories + a calibrated emitter)
> **Status**: Proposed — falsifiable, with a daily-confirmed calibration anchor
> **Source theory**: CQ43 (variable spation closure ℓ_P(r)), CQ15 (depth engine, Shapiro), E101 (lumiopause)
> **Author**: James Christopher Tyndall, Melbourne

---

## 1. Background — what is actually being measured

SDT (CQ43) holds that the spation's Planck-scale closure is **not** a global
constant. Where matter crushes the space it displaces, the local closure
`ℓ_P(r)` tightens, and because light relays one spation per tick, the local
light speed and clock rate track it:

```
z(r) = ϟ/r = 1 − ℓ_P(r)/ℓ_P,∞ = 1 − c_local(r)/c_∞     (one quantity)
dτ/dt = √(1 − z)                                        (Law V clock rate)
```

A **fixed atomic emitter** therefore radiates the *same* intrinsic line, but an
observer at a different depth sees it shifted by the depth difference:

```
Δλ/λ = z(r_emit) − z(r_obs) = ϟ_Sun · (1/r_emit − 1/r_obs)
```

This is the same `z = ϟ/r` field that already reproduces the Shapiro delay
(CQ15, exact) and — crucially — the **GPS gravitational redshift** (below). E102
turns that passive field into an **active, source-controlled experiment** by
flying a calibrated emitter through the solar depth gradient.

The deep point: GR attributes this to spacetime curvature; SDT attributes it to
a real, position-dependent change in the lattice closure (and hence local c).
**At first order the two predict the same shift** — so E102's near-Sun leg is a
consistency test. The *discriminating* signal is in §6 (the galactic depth floor
and the lumiopause), which GR/ΛCDM do not predict.

---

## 2. SDT Prediction (computed — `sundiver.js`)

Emitter at heliocentric radius `r`, reference spectrometer at 1 AU.
`ϟ_Sun = 1477.046 m`. **All values are program output, not estimates.**

| emitter r [AU] | z(r) = ϟ/r | Δλ/λ vs 1 AU | equivalent Δc [m/s] |
|---|---|---|---|
| 1.00 | 9.87×10⁻⁹ | 0 (reference) | 0 |
| 0.70 | 1.41×10⁻⁸ | +4.23×10⁻⁹ | +1.27 |
| 0.50 | 1.97×10⁻⁸ | +9.87×10⁻⁹ | +2.96 |
| 0.30 | 3.29×10⁻⁸ | +2.30×10⁻⁸ | +6.91 |
| 0.20 | 4.94×10⁻⁸ | +3.95×10⁻⁸ | +11.84 |
| 0.10 | 9.87×10⁻⁸ | +8.89×10⁻⁸ | +26.64 |
| **0.046** (~10 R☉, Parker class) | 2.15×10⁻⁷ | **+2.05×10⁻⁷** | **+61.4** |
| 0.020 (~4.3 R☉) | 4.94×10⁻⁷ | +4.84×10⁻⁷ | +145 |

**The line reddens as the emitter descends toward the Sun** (deeper z, slower
local clock). The signal at Parker-perihelion class is **Δλ/λ ≈ 2×10⁻⁷** — five
to six orders of magnitude above the noise floor of modern instruments.

---

## 3. Standard-Model Prediction

GR predicts the identical first-order shift `Δλ/λ = Δ(GM/c²r) = ϟ_Sun·Δ(1/r)`
(since koppa ≡ GM/c²). So on the **near-Sun leg, E102 cannot distinguish SDT
from GR** — it confirms both, and confirms that SDT's pressure-gradient
mechanism reproduces the curvature result. The split appears only in §6.

---

## 4. Calibration Anchor — already confirmed daily

The same `z = ϟ/r` law, applied to Earth, gives the **GPS gravitational
redshift**: surface → 20,200 km altitude, `Δz = 5.29×10⁻¹⁰` (~38 µs/day) — the
correction every GPS satellite applies continuously. **The mechanism is not
speculative; it is operational infrastructure.** E102 extends the *confirmed*
near-field law into the solar gradient with a controlled source.

---

## 5. Apparatus

1. **A calibrated atomic-line emitter** (the key element — James's point): a
   frequency-stabilised reference source (astro-comb / cavity-locked laser or a
   trapped-ion clock line) flown on the descending probe. It defines the
   "same emitted pulse everywhere" boundary condition the theory assumes.
2. **A reference spectrometer at ~1 AU** (Earth orbit / L1) of matching stability.
3. **Trajectory**: any inbound solar pass. **Parker Solar Probe** class
   (perihelion 0.046 AU) already flies the orbit; it lacks the precision emitter.
   The emitter is the missing payload, not the trajectory.
4. **Cross-checks of opportunity**: JWST/NIRSpec IR coverage and the Parker
   "sundiver" trajectory can be corralled for coarse confirmation, but NIRSpec's
   resolving power (R≈2,700) sees the *existence* of the shift class, not the
   10⁻⁷ gradient — the dedicated emitter is required for the quantitative test.

Required fractional precision: 10⁻⁹ resolves the 0.3 AU point; astro-combs reach
10⁻¹¹. **Comfortable margin.**

---

## 6. The discriminating signals (SDT-only, no GR/ΛCDM counterpart)

These are why the payload is worth flying — they are predictions **no curvature
model makes**:

- **Galactic depth floor.** The Sun itself sits in the Milky Way's depth,
  `z_gal = 3.51×10⁻⁷` — a **constant, isotropic c-deficit of ~105 m/s** below the
  absolute lattice ceiling c_∞, present even in "empty" interstellar space. A DC
  offset on every line, independent of solar distance. GR predicts no such floor.
- **Lumiopause handover.** At the surface-area condition `L_sun/(4πr²) = F_CMB`
  → **r = 20,857 AU**, the solar output density crosses the CMB floor; the
  emission/closure regime hands over. A deep-space probe crossing it should see a
  change in the depth-gradient slope. (Oort objects sit *at* this surface in
  lumiostasis — CQ43.)

---

## 7. Feasibility

**FEASIBLE NOW for the near-Sun leg.** The trajectory exists (Parker class), the
required precision is 5–6 orders inside instrument capability, and the mechanism
is pre-confirmed by GPS. The only missing element is the **calibrated emitter
payload**. The deep-space discriminators (§6) require a dedicated outbound probe
and are a longer-horizon goal.

---

## 8. Impact

- **If the near-Sun gradient matches** (Δλ/λ ≈ +2×10⁻⁷ at 0.046 AU): SDT's
  variable-closure mechanism is confirmed to reproduce the GR-class shift from a
  controlled source — and the `z = ϟ/r` depth field is validated as an active,
  not just inferred, quantity.
- **If the galactic floor is detected** (~105 m/s isotropic DC c-deficit):
  a result GR/ΛCDM do not predict — direct evidence the local lattice ceiling is
  below the absolute c_∞. This is the high-payoff target.
- **If no gradient is seen**: the variable-closure mechanism is falsified at the
  10⁻⁷ level — a clean kill, since GPS already guarantees a signal of this form
  exists near Earth.

---

## 9. Predicted curve (reproduce)

`Δλ/λ(r) = ϟ_Sun·(1/r − 1/AU)`, `ϟ_Sun = 1477.046 m`. Tool: `sundiver.js`
(prints the §2 table). Calibration: GPS `Δz = 5.29×10⁻¹⁰`. Discriminators:
`z_gal = M_MW·ϟ_Sun/R₀ = 3.51×10⁻⁷`; lumiopause `r = √(L_sun/4πF_CMB) = 20,857 AU`
(`law_II::pressure_domain`).
