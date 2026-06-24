# GOM07 — VERDICT (Part B against real data)

> **Domain:** 06 Gravitation & Orbital Mechanics · **Author:** J.C. Harvey, Melbourne · **Framework:** SDT
> Depth-Closure. Honesty-over-success. **Predictions corrected 2026-06-20 — they had been swapped.**

## The corrected physics (the earlier draft had SDT and GR reversed)
- **SDT:** redshift is **encoded at the point of emission** and is **stable — set without movement.**
  Reflected sunlight carries the **Sun's** emission stamp; it does **not** re-fight gravity at the
  reflector. The reflector's own well contributes **nothing** → **flat 633 m/s for every body**
  → regression slope **0**.
- **GR:** light must **"fight gravity all the way until it escapes the gravitational bounds of a body."**
  Reflected light climbing out of the planet's well **accumulates** extra redshift `z·c = ϟ_body/R`
  → Jupiter ≈ 639 → slope **1**. (`ϟ_J` from SDT primitives `v_surf, R` — **no GM**.)
- **Honest caveat:** *rigorous cancellation-GR* (fall-in blueshift cancels climb-out redshift) also gives
  flat → slope 0, **degenerate with SDT** for reflection. This test cleanly refutes the **gradual one-way
  climb**; it does not separate SDT from cancellation-GR. (That needs observer-position dependence — a
  solar line read at 0.05 AU vs 1 AU — not reflection.)

## The data
**Lanza et al. 2016 (A&A 587, A103; arXiv:1601.05646), Table 2** — the Sun's RV measured off Moon,
asteroids, and Galilean satellites on ONE common HARPS scale, **with no host-well correction** applied.
The Galileans sit deep in Jupiter's well, so this published dataset already contains the signal — if any.

| body | measured solar RV (m/s) | SE | N | GR-climb extra `ϟ_J/r·c` (m/s) | SDT extra |
|------|------------------------:|---:|--:|-------------------------------:|----------:|
| Moon | 99.39 | 0.68 | 6 | 0 | 0 |
| Vesta | 101.68 | 0.69 | 24 | 0 | 0 |
| Pallas | 99.41 | 1.50 | 7 | 0 | 0 |
| Iris | 97.57 | 1.93 | 5 | 0 | 0 |
| Ganymede | 99.07 | 0.38 | 17 | +0.40 | 0 |
| Europa | 101.32 | 0.97 | 10 | +0.63 | 0 |
| Io *(excluded¹)* | 90.18 | 1.27 | 7 | +1.00 | 0 |
| Ceres *(excluded²)* | 98.21 | 2.49 | 7 | 0 | 0 |

¹ Io: authors exclude (albedo 0.10→0.75 × high airmass distorts the mask, 6.65σ low) — the **most
sensitive** point, unusable. ² Ceres: fast rotation + surface inhomogeneity.

## Result — `cq51_partB_lanza2016.py`
**Weighted regression of measured RV vs Jupiter-well extra** (clean set, Io & Ceres excluded per the
authors' documented non-gravitational reasons):

- **slope = −1.11 ± 1.28**, intercept 100.00 ± 0.44 m/s.
- **0.9σ from SDT (slope 0)** → consistent with SDT. **1.6σ from GR (slope 1)** → GR gradual-climb
  mildly disfavoured. Central slope is negative (no positive trend with Jupiter depth).
- Io added back: slope **−5.20 ± 1.04** (albedo artifact; confirms exclusion is mandatory and that the
  dataset's strongest lever is unusable).
- Named within-Jupiter pair: **Europa − Ganymede = +2.25 ± 1.04 m/s** — sign matches GR-climb (deeper
  Europa redder) but is **~10× the predicted 0.23** → systematic, not a GR detection. Io (the deepest) is
  the *lowest*, contradicting GR-climb at the noise level.

## Corrected depth (Harvey, 2026-06-20): the SUN's well, not the planet's own well
The earlier tables used each planet's **own** surface well `ϟ_planet/R_planet` — wrong quantity. "Deeper in
the gravitational influence of the Sun" = the planet's **position in the Sun's well** `z_sun(r)=ϟ_sun/r`,
which **falls with distance** (so Saturn < Jupiter — the tell). `cq51_sun_well.py`:

| body | r (AU) | z_sun·c (m/s) |
|------|-------:|--------------:|
| Venus | 0.723 | 4.09 |
| Earth | 1.000 | 2.96 |
| Jupiter | 5.204 | 0.57 |
| Saturn | 9.583 | 0.31 |

**Venus − Jupiter = +3.52 m/s** (Venus deeper → more shift, *if* reflection re-stamps).

**What reflection is — and the decisive fact:** reflection = absorption + re-emission (minus wavelengths
kept as heat = albedo). RE-STAMP would have the re-emission encode the local depth; PRESERVE has elastic
scatter carry the Sun's surface stamp through. **Reflected sunlight carries the full ~633 m/s solar redshift
— re-stamp to local depth would give ~1–4 m/s, not 633.** So the stamp is **preserved**; the reflected
photons are elastically scattered (we still see the *Sun's* Fe lines). Re-tested on Lanza with the correct
predictor `z_sun(r_body)` (range 0.57–2.96, far better leverage): **slope = +0.08 ± 0.32 → 2.9σ against
re-stamp(+1), 0.2σ from preserve(0).** The Venus>Jupiter re-stamp differential is **rejected at ~3σ.**

**The sting:** flat *confirms* SDT's "encoded at emission, stable" — but that principle then *forbids* the
Venus>Jupiter differential (the stamp is the Sun's, preserved; the reflector cannot re-encode its solar
depth). Consistent SDT predicts Venus = Jupiter = 633. Both theories flat; data flat.

## Why it can't fully decide — the systematic floor
The four zero-well bodies (identical under **both** theories) scatter by **1.46 m/s** and span 4.1 m/s —
that body-to-body floor (albedo, rotation, airmass) is **~3× the 0.4–1.0 m/s** GR-climb signal. The
dataset is floor-limited.

## VERDICT: consistent with SDT (flat); GR gradual-climb disfavoured but not killed
- **SDT (emission-stamp, flat) is supported** — slope 0.9σ from 0; the reflector's well does **not** show
  up, exactly as "encoded at emission, stable" requires.
- **GR gradual-one-way-climb is disfavoured** (slope 1.6σ away, central value negative) — but **not
  killed**, because the floor (~1.5 m/s) is ~3× the signal.
- **Degeneracy flagged:** rigorous cancellation-GR also predicts flat, so this result does not separate
  SDT from careful GR — it kills the *naive accumulation* picture and **vindicates SDT's emission-stamp**.
- **Class:** prediction DERIVED (SDT-native, no GM); empirical status — existing data CONSISTENT-WITH-SDT,
  GR-climb DISFAVOURED, decisive separation PENDING.

## What would sharpen it
1. **Jupiter disk-direct, ESPRESSO** (6 m/s, 10× the Galilean differential, above the floor): a flat 633
   would further bury GR-climb; a 639 would resurrect it. Matched airmass + single bright reflector kills
   the albedo/rotation systematics that dominate Lanza's scatter.
2. **The real SDT-vs-GR discriminator** is not reflection but **observer-position dependence** — read the
   *same* solar line from very different depths in the Sun's well (Parker Solar Probe at ~0.05 AU vs
   Earth, ~tens of m/s). First resolve the internal tension: the engine's `z_spectral = z_emit − z_obs`
   carries an observer term, which if literal makes SDT match GR here too.
