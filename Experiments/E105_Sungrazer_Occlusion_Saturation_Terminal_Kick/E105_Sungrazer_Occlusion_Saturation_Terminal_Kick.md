# E105: Sungrazer Occlusion-Saturation Terminal Kick

> **Category**: Orbital Mechanics / Gravity (occlusion saturation)
> **Difficulty**: LOW (archival tracking) → MODERATE (dedicated tracker)
> **Status**: Proposed — falsifiable on existing SOHO/Parker data
> **Source theory**: occlusion-saturation (two-regime ontology), GOM05 (variable closure), EMC03 (occlusion force)
> **Author**: James Christopher Harvey, Melbourne

---

## 1. Background — gravity is only `1/r²` in the far field

Newtonian/GR gravity is `1/r²` everywhere. SDT's occlusion mechanism reproduces
`1/r²` **only in the far field**, where the attracting body subtends a small
solid angle. As a test body approaches contact, the body fills more of the sky;
the occluded solid angle saturates at a **hemisphere**, and the convergent push
that drives infall saturates with it:

```
Ω(r) = 2π(1 − √(1 − (R/r)²))            (occluded solid angle)
g(r) = g_Newton(r) · G(x) ,  G(x) = 2(1 − √(1 − x))/x ,  x = (R/r)²
```

`G(x) → 1` far away (recovers Newton) and `G(x) → 2` at contact. The extra factor
is a **near-surface enhancement** of the infall acceleration that Newton and GR
do **not** contain. A sungrazing comet is the natural probe: it falls almost
radially to within a fraction of a solar radius, sampling the saturation regime
that no planetary orbit reaches.

This is the mechanism behind the observed "fall, fall, then a sudden
unbelievable speed increase" of sundiving comets near perihelion.

---

## 2. SDT Prediction (computed)

For a Sun-grazer, integrating `g(r) = g_N(r)·G(x)` along the radial plunge gives
a terminal-speed **excess over the Keplerian value**:

| perihelion q | `G(x)` at q | terminal-v excess |
|---|---|---|
| 2.0 R☉ | 1.07 | small |
| 1.5 R☉ | 1.20 | rising |
| 1.05 R☉ | 1.53 | strong |
| 1.001 R☉ | 1.91 | near-hemisphere |

- Integrated terminal-speed enhancement at grazing: **≈ +6.8%** over Newton
  (Sun escape-class 617.6 → ~659.9 km/s).
- **Spatial concentration**: ~**80% of the extra kick is delivered inside 1.5 R☉**,
  ~92% inside 2 R☉ — a whip-crack localised at the surface, not a smooth excess.
- Distinctive **shape**: the velocity residual vs `r` follows `G(x)` — flat far
  out, then a sharp rise inside ~2 R☉. This shape (not just the magnitude) is the
  signature; outgassing/fragmentation produce different, stochastic profiles.

---

## 3. Standard-Model Prediction

Newton/GR: the trajectory is a pure Kepler/Schwarzschild plunge, `v(r)` set by
`½v² = GM☉/r` (+ tiny PN terms). **No** near-surface enhancement: `G(x) ≡ 1` at
all `r`. Any apparent terminal excess must be attributed to non-gravitational
forces (outgassing rocket effect, fragmentation), which are stochastic and
comet-specific, not a universal `G(x)` curve.

---

## 4. Observable

Track sungrazers through perihelion and fit the radial velocity residual
`Δv(r) = v_obs(r) − v_Kepler(r)`:

- SDT: `Δv(r)` follows the **universal** `G(x)` curve — same shape for every
  comet, scaling only with `R☉` — peaking as a +6.8% terminal excess concentrated
  inside 1.5 R☉.
- SM: `Δv(r)` is zero in the mean; any scatter is non-gravitational and
  uncorrelated between comets.

The killer test is **universality**: stack many comets after removing
mass/outgassing terms; SDT predicts a common `G(x)` residual, SM predicts none.

---

## 5. Apparatus

- **Archival**: SOHO/LASCO C2/C3 astrometry of Kreutz-group sungrazers (thousands
  catalogued); STEREO; SDO for the deepest divers. Re-reduce positions → fit `v(r)`.
- **In-situ opportunity**: Parker Solar Probe perihelion passes (0.046 AU, ~10 R☉)
  carry exquisite trajectory metrology — a *non-outgassing* spacecraft is the
  clean control (no cometary systematics), directly testing `G(x)` on a known mass.
- **Dedicated**: a small tracker timed to a predicted bright sungrazer with
  ground/space astrometry through perihelion.

---

## 6. Feasibility

**LOW for the archival test** — the data already exist; the work is careful
re-reduction and the stacked `G(x)` fit, separating saturation from
outgassing/fragmentation (the main systematic). Parker provides a comet-free
cross-check at no new cost. The result is a clean SDT≠GR/Newton discriminator on
tracked bodies.

---

## 7. Impact

- **If the universal `G(x)` residual is found** (+6.8% terminal, 80% inside 1.5 R☉,
  common shape across comets and matching Parker): gravity is shown to **saturate**
  near contact — direct evidence it is occlusion of a finite-solid-angle budget,
  not a pure `1/r²` field.
- **If not found** (residuals purely stochastic, consistent with outgassing):
  occlusion saturation is bounded below the detection threshold — the far-field
  `1/r²` regime is all that is accessible, and this SDT prediction is falsified.

---

## 8. Predicted curve (reproduce)

`G(x) = 2(1 − √(1 − x))/x`, `x = (R☉/r)²`; integrate `g(r) = (GM☉/r²)·G(x)` for the
+6.8% terminal excess and the 80%-inside-1.5 R☉ concentration. Tool:
`sundiver.js` (occlusion-saturation calculator). No `G`/`M` as fundamentals —
`GM☉ → v_surf²·R` per the koppa identity.
