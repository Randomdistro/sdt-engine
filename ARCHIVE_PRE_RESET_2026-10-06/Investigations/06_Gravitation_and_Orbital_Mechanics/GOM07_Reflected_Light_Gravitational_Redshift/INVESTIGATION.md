# GOM07 — The Reflected-Light Gravitational Redshift Test (Venus vs Jupiter)

> **Domain:** 06 Gravitation & Orbital Mechanics · **Author:** J.C. Harvey, Melbourne · **Framework:** SDT
> Depth-Closure. A falsifiable, today-doable test. **Predictions corrected 2026-06-20 (had been swapped).**

---

## §0 The thesis

- **SDT:** gravitational redshift is **encoded at the point of emission** and is **stable — set without
  movement.** A photon leaves the Sun's surface carrying `z = ϟ_Sun/R_Sun` and keeps it. It does **not**
  keep fighting gravity as it travels (`Depth_Closure_Theorem` C1: solar redshift = `ϟ_Sun/R_Sun` to 0.03%).
- **GR:** light must **"fight gravity all the way until it escapes the gravitational bounds of a body"** —
  the shift is acquired **gradually**, accumulating along the climb out of the well.

For a line **emitted** from a body's own surface the two are **degenerate** — energy conservation makes
GR's full climb equal SDT's emission stamp (`ϟ/R` both ways). To separate them you need light whose path is
**not** a single one-way climb. **Reflected sunlight is exactly that case.**

## §1 Why reflection splits the two theories

A sunbeam reaches a planet, scatters off its cloud-tops, and returns to Earth.

- **SDT:** the redshift was stamped at the **Sun** and is stable. The reflection does **not** re-encode it
  (it is not a new gravitational emission for the redshift — the Sun already set it). The light does **not**
  re-fight the planet's gravity. **The reflector's own well contributes nothing → flat 633 m/s for every
  body.**
- **GR (gradual climb):** the reflected beam leaving the planet must **climb out of the planet's well**,
  losing energy all the way → it **accumulates** the planet's depth `+z_body·c`. **The reflector's well
  DOES contribute → Jupiter ≈ 639 m/s.**

This matches the framing from the outset: *"if GR is correct, Jupiter's reflection will be more redshifted."*

**Honest caveat — the degeneracy:** computed *rigorously*, textbook GR **also** predicts flat, because it
claims the blueshift falling **into** the planet exactly cancels the redshift climbing **out** (the reason
the Moon/asteroid technique reads the *Sun's* 633 with no reflector term). So this test cleanly refutes the
**naive one-way accumulation** picture and **vindicates SDT's emission-stamp**, but it does **not** separate
SDT from *cancellation-GR* — both say the reflector is silent. The genuine SDT-vs-GR split lives in
**observer-position dependence** (§6), not reflection.

## §2 Part A — the SDT side is clean; the load-bearing question is GR's

SDT's prediction needs no extra assumption: redshift is set at the **original** (solar) emission and is
stable, so a passive reflection carries the Sun's stamp unchanged → **flat**. No "re-stamp" is invoked (an
earlier draft wrongly added one, making SDT predict the differential — that was the swap, now removed).

The open theoretical question is on **GR's** side: does the reflected beam's climb-out redshift get
**cancelled** by the fall-in blueshift (→ flat, degenerate with SDT) or **not** (→ Jupiter more redshifted)?
The naive gradual picture says it shows up; the rigorous static-field calculation says it cancels. **The
data adjudicates the naive picture; only the observer-position test (§6) reaches the rigorous one.**

## §3 The predictions (SDT-native — NO G, NO M — `cq51_reflection_redshift.py`)

Inputs are the SDT primitives `v_surf` (surface circulation velocity) and `R` (radius). `koppa = v_surf²·R/c²`
and `g = v_surf²/R` are derived; **GM is never written.** Depth/shift: `z = (v_surf/c)²`, `k = c/v_surf`,
**seat `z·k² = 1`** (verified per body), climb extra `z·c = v_surf²/c`. Solar baseline (Sun → 1 AU) = 633.35.

| body | v_surf (m/s) | z = (v/c)² | z·k² | climb z·c | **SDT (flat)** | GR (climb) |
|------|-------------:|-----------:|-----:|----------:|---------------:|-----------:|
| Moon | 1 680.2 | 3.14×10⁻¹¹ | 1.00000 | 0.009 | **633.35** | 633.36 |
| Mars | 3 554.7 | 1.41×10⁻¹⁰ | 1.00000 | 0.042 | **633.35** | 633.39 |
| Venus | 7 326.7 | 5.97×10⁻¹⁰ | 1.00000 | 0.179 | **633.35** | 633.53 |
| Saturn | 25 522 | 7.25×10⁻⁹ | 1.00000 | 2.173 | **633.35** | 635.52 |
| **Jupiter** | **42 569** | 2.02×10⁻⁸ | 1.00000 | 6.045 | **633.35** | **639.40** |

**Decisive differential:** Jupiter − Moon = **0** (SDT, flat) vs **6.04 m/s** (GR gradual-climb).

> **Provenance note:** for a body we orbit, spacecraft tracking measures the surface acceleration `g`
> directly, and `v_surf = √(g·R)`. The catalogue's "GM" is just the product `g·R²` — a bookkeeping combo
> SDT declines as an *input*. The tabulated `v_surf` are velocities; the tool contains no GM.

## §4 Part B — the data test (predict-before-look)

1. The §3 table is committed to `RUN_LOG.md` **before** any spectrum is read (done).
2. Pull archival reflected-sunlight spectra (HARPS / ESPRESSO / UVES) for **Jupiter, Saturn, Venus**, with
   the **Moon** as the baseline/control. Measure the solar **Fe** absorption-line redshift.
3. Subtract each body's **known** kinematics (orbital + rotational Doppler, JPL Horizons), leaving the
   residual.
4. **GATE:** regress `(measured_residual − 633)` against `z_body·c` across the bodies.
   - **slope ≈ 0** → **SDT** (emission stamp; reflector silent, flat 633). *(and rigorous cancellation-GR)*
   - **slope ≈ 1** → **GR gradual-climb** (reflector's well adds `z_body·c`). Jupiter > Moon by ~6 m/s.

## §4b The within-Jupiter (Galilean) gradient — data exists TODAY

A Galilean moon reflects sunlight while deep in **Jupiter's** well. **GR-climb:** its reflected light
climbing out carries `+ϟ_J/r`, **falling with distance** from Jupiter. **SDT:** flat (the Sun's stamp;
Jupiter irrelevant).

| moon | r from Jupiter | GR-climb extra `ϟ_J/r·c` | SDT |
|------|---------------:|-------------------------:|----:|
| Io | 4.22×10⁸ m | +1.00 m/s | 0 |
| Europa | 6.71×10⁸ m | +0.63 m/s | 0 |
| Ganymede | 1.07×10⁹ m | +0.40 m/s | 0 |
| Callisto | 1.88×10⁹ m | +0.22 m/s | 0 |

GR-climb differentials: Io − Callisto = 0.78 m/s; Europa − Ganymede = 0.24 m/s. **HARPS reflected-sunlight
spectra of Europa and Ganymede already exist** (per-exposure rms 0.83 m/s;
[arXiv:1601.05646](https://arxiv.org/pdf/1601.05646)) — and Lanza et al. went further, putting **Moon +
asteroids + Galilean moons on one common scale with no host-well correction.** That dataset already contains
the test (see `CQ51_VERDICT.md`): **measured slope −1.11 ± 1.28 → 0.9σ from SDT (flat), 1.6σ from GR-climb.**
Consistent with SDT; GR gradual-climb disfavoured; floor-limited (~1.5 m/s body-to-body) so not decisive.

## §5 Literature — has anyone done this?

The reflected-sunlight technique is **mature and m/s-precise**, but always with the reflector treated as a
*passive mirror* (its well assumed silent) — measuring the **Sun's** redshift, never the reflector's:

- Solar gravitational redshift off the **Moon**, HARPS-LFC: **638 ± 6 / 641 ± 18 m/s** vs GR 633.1
  ([A&A 2020](https://www.aanda.org/articles/aa/full_html/2020/11/aa38937-20/aa38937-20.html);
  [arXiv:2009.10558](https://arxiv.org/abs/2009.10558)).
- The Sun's RV off Moon + asteroids + Galilean satellites on one scale, **no host-well correction**
  ([Lanza et al. 2016, arXiv:1601.05646](https://arxiv.org/abs/1601.05646)) — the dataset GOM07 Part B mines.

**The reflector's-own-well differential (Jupiter vs Venus/Moon) has not been isolated as a GR test.**
Jupiter's +6 m/s (GR-climb) exceeds the Moon-study error and is inside ESPRESSO's sub-m/s reach.

## §6 Reuse, the real discriminator, & deliverables

- **Reuse** (`Engine/include/sdt/laws.hpp`): `bridge::koppa(v,R)=v²R/c²`; `depth_closure::depth(ϟ,r)=ϟ/r`;
  `depth_closure::z_spectral`; `z_spectral_Sun` (the 633 baseline). Planetary `v_surf,R` are MEASURED-INPUT.
- **The real SDT-vs-GR discriminator is NOT reflection** (degenerate with cancellation-GR) **but
  observer-position dependence:** read the *same* solar line from very different depths in the Sun's well
  (Parker Solar Probe at ~0.05 AU vs Earth → tens of m/s). GR: redshift = `z_emit − z_obs` (depends on the
  observer's depth). Pure emission-stamp SDT: fixed at emission. **Internal tension to resolve first:** the
  engine's `z_spectral = z_emit − z_obs` carries an observer term — if literal, SDT matches GR there too.
- **Deliverables:** `cq51_reflection_redshift.py` (predictions, SDT-native) · `cq51_partB_lanza2016.py`
  (Part B regression on real data) · `RUN_LOG.md` · `CQ51_VERDICT.md` (consistent-with-SDT; GR-climb
  disfavoured; decisive separation pending the observer-position test).
