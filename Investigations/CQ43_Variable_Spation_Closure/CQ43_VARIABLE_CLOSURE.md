# CQ43: Variable Spation Closure, the Light-Speed Gradient & Lumiostasis

> **Author:** SDT Canonical Engine — James Christopher Tyndall, Melbourne
> **Date:** June 2026
> **Status:** EXECUTED — 4/4 proofs pass (`cq43_variable_closure.cpp`, MSVC, exit 0)
> **Class:** C (SDT-first mechanism; depth/closure identities exact; lumiopause from law_II)
> **Builds on:** CQ15 (depth engine, Shapiro), CQ42 (spation closure ℓ_P=√(ϟ·ƛ)), E101 (pressure domain)

---

## The thesis (James Tyndall)

The Planck-scale spherical closure of the spation, **ℓ_P, is not a global
constant.** Nucleons — protons and neutrons — are *flat out crushing the space
they displace*, tightening the local closure. Light always relays **one spation
per tick**, so where the closure is smaller, light is locally slower. That is a
**gradient**: light is slow deep in the Sun's domain, faster as you move out,
faster again beyond the lumiopause. The atom emits the **same** kinematic EM
pulse everywhere; the variation is in the medium, not the source.

### Framing constraints (author directives, this investigation)

- **No attraction.** Nothing is gravitationally pulled. The CMB convergence
  pushes everything together; matter follows the **path of least resistance**
  through the depth gradient. **Orbits are real** — a closed least-resistance
  path through a radial gradient *is* an orbit — but the cause is convergence,
  not a gravitational force.
- **koppa is a velocity quantity**, ϟ = R/k² with k = c/v. The *depth* is the
  dimensionless **z = 1/k² = ϟ/r**. Light's local speed is **c_local = c(1−z)**.
  z is what light wades through; koppa = c/k sets the velocity structure.
- **Excluded pending compute:** the conjecture that the Sun deliberately ejects
  mass to herd the field. Logged, not used.

---

## The unification (one quantity, three readings)

```
ℓ_P(r) = ℓ_P,∞ · (1 − z(r))          local spation closure
c_local(r) = c_∞ · ℓ_P(r)/ℓ_P,∞ = c_∞ (1 − z(r))
z(r) = 1 − ℓ_P(r)/ℓ_P,∞ = 1 − c_local/c_∞ = ϟ/r
```

**Measured (CQ43-I.1, I.2 — both 0.0000%):** at the solar surface
`z = 2.123×10⁻⁶`; the closure shrinks by `Δℓ_P = 3.43×10⁻⁴¹ m`; light is
slower by **636.49 m/s**. The depth field, the light-speed deficit, and the
closure deficit are *literally the same number*.

This collapses CQ15 and CQ42 into one statement: the Shapiro "depth" was never
"more shells at fixed ℓ_P" — **the shells themselves are smaller near mass.**

---

## The c-gradient (measured)

| location | r [AU] | z(r)=ϟ/r | ℓ_P(r) [m] | c deficit [m/s] |
|---|---|---|---|---|
| solar surface | 0.00465 | 2.123×10⁻⁶ | 1.616251×10⁻³⁵ | 741.78 |
| Mercury | 0.387 | 2.55×10⁻⁸ | 1.6162544×10⁻³⁵ | 112.93 |
| Earth | 1.0 | 9.87×10⁻⁹ | 1.6162544×10⁻³⁵ | 108.25 |
| Jupiter | 5.2 | 1.90×10⁻⁹ | 1.6162544×10⁻³⁵ | 105.85 |
| heliopause | 120 | 8.23×10⁻¹¹ | 1.6162544×10⁻³⁵ | 105.31 |
| lumiopause | 20857 | 4.73×10⁻¹³ | 1.6162544×10⁻³⁵ | 105.29 |
| deep space | → ∞ | → 0 | → 1.616255×10⁻³⁵ | 105.29 (galactic floor) |

(c deficit is measured against absolute c_∞; the residual ~105 m/s far out is the
**galactic depth floor** — the Sun sits inside the Milky Way's own depth,
`z_gal = 3.51×10⁻⁷`.) Light speeds up monotonically outward as the closure opens.

The Sun's *own* contribution falls as 1/r and is essentially spent by ~Jupiter;
beyond that the gradient is the galactic background. So the Sun's depth gradient
is a near-field effect; the lumiopause is set by a **different** condition (next).

---

## The lumiopause as a surface-area condition (James's correction)

The lumiopause is **not** a force balance. It is where the Sun's output, spread
over the sphere, **maps to the CMB output as a surface-area condition**:

```
L_sun / (4π r²) = F_CMB     ⟹     r_lumio = √(L_sun / 4π F_CMB)
```

**Measured (CQ43-III.1, 0.0000%):** with `L_Sun = 3.828×10²⁶ W` and
`F_CMB = c·u_CMB/4 = 3.129×10⁻⁶ W/m²` (both from `law_II`), the balance holds at
**r_lumio = 3.120×10¹⁵ m = 20,857 AU**. This is `law_II::pressure_domain(L_Sun)`.

**Lumiostasis.** The Oort cloud is suspended **at** this depth surface — held
where the convergence gradient balances, the path of least resistance for matter
pushed inward by the CMB. Not orbiting, not attracted: resting at the depth where
the inward solar-output surface density equals the CMB floor.

---

## Shapiro, re-read (measured, CQ43-IV.1, 0.0000%)

```
Δt = (2ϟ/c) ln(4 r₁ r₂ / b²) = 123.66 µs   (Earth–Mars, b = R_Sun)
```
Identical number to the standard formula — but the **mechanism** is the CQ43
one: light is delayed because the spations near the Sun are **smaller**, so a
fixed coordinate path contains more closure boundaries to relay across. Local
light speed is c at every spation; the relay count per metre rises inward. No
potential, no slowing-in-a-well.

---

## Verdict

One mechanism — `ℓ_P(r) = ℓ_P,∞(1−z)`, `c_local = c(1−z)`, `z = ϟ/r` — and it
ties together: (i) light's outward speed gradient, (ii) the Shapiro delay as an
integrated closure deficit, (iii) the lumiopause as the L/(4πr²)=F_CMB surface,
(iv) the Oort cloud in lumiostasis. All with **no attraction** — convergence
pushing, matter taking the least-resistance path (orbits included).

**Honest scope:**
- The c-gradient identities (z = closure deficit = c deficit) are **exact** and
  parameter-free given ϟ — a genuine unification of CQ15 + CQ42.
- The **absolute** value of ℓ_P,∞ still carries the CQ42 seed caveat (one anchor
  unavoidable); CQ43 fixes the *variation* ℓ_P(r)/ℓ_P,∞ = 1−z, which is fully
  SDT-native (z from ϟ = v²R/c², G-free).
- The **lumiopause = surface-area** reading and **lumiostasis** are the new
  physical claims; the math (r=√(L/4πF_CMB)) is exact, the suspension mechanism
  is a stated, falsifiable prediction (Oort objects should cluster at the depth
  surface, not follow Keplerian orbits).
- The galactic depth floor (~105 m/s residual) is a real prediction: even in
  "deep space" within the Galaxy, c is below absolute c_∞ by the MW's own z.

## Files

- `cq43_variable_closure.cpp` — tool (4/4 proofs).
- `cq43_output.txt` — measured run.
- Inputs: `koppa_Sun`, `l_P`, `L_Sun`, `F_CMB`, `pressure_domain()` from
  `laws.hpp` (`bridge`, `law_II`). No new fitted parameters.

## Open / next

- Map ℓ_P(r) and c_local(r) through a **stellar interior** (nucleon column
  density → local closure) to test "nucleons crush the space they displace"
  quantitatively against helioseismic sound-speed profiles.
- Lumiostasis falsifier: predicted Oort-object depth-surface clustering vs the
  observed semi-major-axis distribution.
- (Parked, needs compute) the Sun-ejects-mass-to-herd-the-field conjecture.
