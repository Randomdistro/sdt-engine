# E106: Oort-Cloud Lumiostasis — Suspension at the Lumiopause

> **Category**: Convergence Depth / Orbital Mechanics
> **Difficulty**: LOW (archival kinematics) → HIGH (deep-space confirmation)
> **Status**: Proposed — falsifiable on distant-object orbital statistics
> **Source theory**: GOM05 (variable closure, lumiopause), E101/GOM12 (convergence budget), depth-closure z = ϟ/r
> **Author**: James Christopher Harvey, Melbourne

---

## 1. Background — the lumiopause is a real surface

SDT (GOM05) defines the **lumiopause**: the heliocentric radius where the Sun's
outgoing luminous flux density falls to the cosmic (CMB) floor:

```
L☉ / (4π r²) = F_CMB        →        r_LP = √(L☉ / 4π F_CMB) ≈ 20,857 AU
```

Inside `r_LP` the Sun dominates the local convergent/luminous budget; outside, the
CMB background does. At the handover the **depth gradient flattens**: a body there
sits in **lumiostasis** — suspended at a depth where the inward convergent push
and the background balance — rather than executing a fast Keplerian orbit. SDT's
claim is not "no dynamics" but that the *least-resistance* configuration at the
lumiopause is **near-stationary suspension at depth**, not a bound ellipse with
Kepler's `v ∝ 1/√a`.

The Oort cloud and the detached/extreme-TNO population (Sedna, 2012 VP113, …) live
in exactly this radial band. They are the natural test set.

---

## 2. SDT Prediction

- **A kinematic floor near `r_LP`**: objects in the outer Oort band have
  characteristic speeds **below** the Keplerian prediction `v_K = √(GM☉/r)` —
  trending toward suspension (low, isotropic residual motion) rather than the
  `1/√r` falloff continued from the planetary region.
- **A clustering of aphelia / semi-major-axis pile-up** near the lumiopause radius
  (~20,000 AU), because it is a depth equilibrium, not an arbitrary turnaround.
- **Isotropy at the floor**: suspended objects show no preferred orbital
  direction (no shared angular momentum), unlike a dynamically-relaxed bound
  swarm — they are held by depth, not orbiting a focus.
- The transition is **smooth and located** at `r_LP` (a derived number), not a
  tunable parameter.

---

## 3. Standard-Model Prediction

Newtonian dynamics + Galactic tide + stellar perturbations: the Oort cloud is a
**bound, isotropic swarm** on long-period Keplerian orbits, `v = √(GM☉(2/r − 1/a))`.
The outer edge (~10⁵ AU) is set by the Galactic tidal truncation and passing
stars — **not** by any solar-flux/CMB handover. There is no special dynamical
radius at 20,857 AU; the distribution is a smooth tidal rollover. Detached objects
(Sedna) require a past perturber/Planet-Nine-class explanation.

---

## 4. Observable

From the orbital catalogue of distant solar-system bodies (semi-major axis,
perihelion, aphelion, velocity vectors):

| Signature | SM | SDT |
|---|---|---|
| `v(r)` near 20,000 AU | continues `v_K ∝ 1/√r` | falls below `v_K`, → suspension |
| feature at `r_LP ≈ 20,857 AU` | none (smooth tidal rollover) | depth-equilibrium pile-up |
| velocity isotropy at the floor | relaxed swarm | held-at-depth, no shared L |

The discriminator is a **located** kinematic floor + aphelion clustering at the
*derived* lumiopause radius, absent in the tidal picture.

---

## 5. Apparatus

- **Archival now**: JPL Horizons / Minor Planet Center orbits of extreme TNOs and
  long-period comets; statistical test for a velocity floor and aphelion pile-up
  at ~`r_LP`. (Small-N and observational bias toward perihelion passages are the
  main caveats — handle with a forward-modelled selection function.)
- **Near future**: LSST/Rubin will multiply the distant-object sample by orders of
  magnitude, sharpening the floor test.
- **Deep-space confirmation**: an outbound probe (Interstellar-Probe class)
  crossing the lumiopause should register the **depth-gradient slope change**
  (companion to E102 §6) — the in-situ version of the same handover.

---

## 6. Feasibility

**LOW for the statistical test** (catalogue analysis, available today, limited by
sample size and selection effects). **HIGH** for the in-situ slope-change
confirmation (decade-class mission). The archival test can already say whether the
outer-object kinematics prefer a located floor at the derived radius over a smooth
tidal rollover.

---

## 7. Impact

- **If a kinematic floor + aphelion pile-up sit at the derived `r_LP`**: strong
  evidence for the lumiopause as a real depth surface, and for orbits as
  least-resistance paths in a depth field rather than Newtonian conics — and the
  detached objects (Sedna) need no extra perturber.
- **If the kinematics are purely tidal/Keplerian with no feature at `r_LP`**: the
  lumiostasis claim is falsified; the outer cloud is a conventional bound swarm.

---

## 8. Predicted curve (reproduce)

`r_LP = √(L☉ / 4π F_CMB) ≈ 20,857 AU` (`law_II::pressure_domain`); depth
`z(r) = ϟ☉/r` flattening to the CMB floor at `r_LP`; compare object `v(r)` against
`v_K = √(GM☉/r)` with `GM☉ → v_surf²R` (no `G`/`M` as fundamentals).
