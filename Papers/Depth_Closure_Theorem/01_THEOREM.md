# The Depth–Closure Theorem

> Formal statement, with the minimal hypotheses and the proven corollaries.
> All numerical claims reproduce from `keystone.js`.
> Author: James Christopher Harvey, Melbourne.

---

## Primitives and definitions

Let the spation lattice relay convergence throughput at speed `c` (the relay tick
rate). For any bound configuration define the **speed ratio** `k = c/v` and the
**convergence depth**

```
z ≡ 1/k² = (v/c)² = ϟ/r,        ϟ ≡ v²R/c² = R/k²   (koppa, a velocity-defined length).
```

Let `ℓ_P,∞` be the spation closure in the matter-free limit (zero local
displacement load) and `c_∞` the corresponding relay ceiling.

---

## Theorem (Depth–Closure)

**In the spation lattice, the local closure, the local relay speed, the local
clock rate, and the gravitational spectral shift are a single quantity — the
convergence depth `z = ϟ/r` — and one centripetal law `v = c√z` governs bound
motion at every scale.**

Formally, at any point at depth `z(r) = ϟ/r`:

```
(1)  ℓ_P(r) = ℓ_P,∞ · (1 − z)            local spation closure
(2)  c_local(r) = c_∞ · (1 − z)           local relay speed   ⇒  z = 1 − c_local/c_∞
(3)  dτ/dt = √(1 − z)                      local clock rate (movement budget, Law V)
(4)  z_spectral = z(r_emit) − z(r_obs)     measured "gravitational redshift"
(5)  v(r) = c √(ϟ/r) = c√z                 bound-motion law (displacement pressure = centripetal force)
```

Equations (1)–(3) are three readings of one closure deficit; (4) identifies the
gravitational redshift with the depth differential; (5) is the unique velocity
consistent with `v²/r = g = c²ϟ/r²`.

---

## Hypotheses (minimal)

- **H1.** Space is a relay lattice with finite tick speed `c`; force is occluded
  convergence (SDT Laws I, III), there is no attraction.
- **H2.** Matter displaces lattice volume; local closure tightens with local
  displacement load (FLM06/GOM05).
- **H3.** The movement budget `v_circ² + v² = c²` holds (Law V).

No `G`, no `M` as fundamentals; `koppa = v²R/c²` is the sole gravitational
descriptor and equals `GM/c²` as a *consequence*, not an input.

---

## Proven corollaries (measured, `keystone.js`)

- **C1 (redshift = depth).** `z_spectral(Sun) = ϟ_Sun/R_Sun = 2.123×10⁻⁶`, equal to
  the observed solar gravitational redshift `GM/(c²R)` to **0.03 %**. The shift is
  the displacement depth at the emission point — not a distinct gravitational
  effect.

- **C2 (one law across scales).** `v = c√(ϟ/r)` gives Earth's orbit **29.789 km/s**
  (obs 29.78), a 292-AU orbit 1.742 km/s, and — applied to hydrogen — `v = αc`,
  hence `k_H = 1/α = 137.036`, `koppa_H = α²a₀ = r_e` (exact), and the proton
  surface at `v_phase = 1.830 c` (`k = 0.5464 < 1`, superluminal phase inside the
  c-boundary). One law, ~15 orders of magnitude.

- **C3 (k is a clock / 137 is a countdown).** `dτ/dt = √(1 − 1/k²)`; k decreases
  toward the c-boundary `k = 1` (`v = c`, `dτ/dt = 0`, dissolution, Law V T17).
  Hydrogen sits `1/α = 137` steps from the edge.

- **C4 (c is local).** Measured `c = 299,792,458 m/s` is Earth's rung; the absolute
  ceiling `c_∞ = c/(1−z) ≈ c + 105 m/s` (galactic depth floor `z_gal = 3.5×10⁻⁷`).
  The c-boundary radius is ceiling-relative, scaling as `(1−z)²`.

- **C5 (closure floor, koppa form).** The spation closure is the mass-independent
  fixed point where koppa equals wake: `ℓ_P = √(ϟ·ƛ)`, reproducing the Planck
  length, with the irreducible scale-seed reduced from `{ℏ, G}` to one measured SDT
  length.

- **C6 (lumiopause / lumiostasis).** The solar depth domain ends at the
  surface-area condition `L_sun/(4πr²) = F_CMB`, i.e. `r = √(L_sun/4πF_CMB) =
  20,857 AU`; loosely-bound matter (the Oort cloud) rests at this depth surface.

---

## Falsifiable predictions

- **P1.** A calibrated orbital emitter shows `Δλ/λ = ϟ_Sun(1/r − 1/r_obs)` along a
  solar descent: **+2.05×10⁻⁷ at 0.046 AU** (E102). Pre-anchored by the GPS
  gravitational-redshift correction at Earth.
- **P2.** A constant, isotropic relay-ceiling deficit (**~105 m/s** below `c_∞`)
  exists even in interstellar space — the galactic depth floor — which curved-
  spacetime models do not predict.
- **P3.** Detached/Oort objects cluster at the lumiopause depth surface
  (~20,860 AU) rather than following a purely Keplerian semi-major-axis
  distribution.

---

## Independent corroboration (prior runs, same framework)

- **Galactic rotation (GD05).** The depth/convergence-floor law (with derived
  `a₀ = cH₀/2π = 1.042×10⁻¹⁰ m/s²`) fits 135 SPARC galaxies at RMS 23.8 %,
  unbiased, BTFR slope 3.58.
- **Cross-scale collapse (APS03).** Galactic, atomic, and stellar response collapse
  onto one curve in `ξ = g_self/a₀` at RMS 8.8 %; a deliberately wrong floor
  degrades the collapse 6×, confirming the derived `a₀` is required.

---

## Scope

The theorem's proven content is C1–C2 (the redshift–depth identity and the single
centripetal law) plus the corollaries that follow from them. The absolute closure
`ℓ_P,∞`, the galactic-floor magnitude, and the proton/electron internal radii
carry the caveats listed in the distillation and are stated as future work, not as
theorem content.
