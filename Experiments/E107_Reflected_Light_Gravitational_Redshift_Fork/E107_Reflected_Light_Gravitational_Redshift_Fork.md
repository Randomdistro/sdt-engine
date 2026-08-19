# E107: Reflected-Light Gravitational-Redshift Fork

> **Category**: Convergence Depth / Variable Closure
> **Difficulty**: MODERATE (existing high-resolution spectroscopy)
> **Status**: Proposed — falsifiable, ontology-discriminating
> **Source theory**: GOM07 (reflected-light gravitational redshift), GOM05 (variable closure), depth-closure z = ϟ/r
> **Author**: James Christopher Harvey, Melbourne

---

## 1. Background — where is the redshift *stamped*?

In SDT a spectral line is stamped with the **depth of its emitter** at the moment
of emission: `z_emit = ϟ/r_emit` (GOM05/depth-closure). This raises a question
the metric picture never has to ask: **when sunlight reflects off a planet, does
the reflection re-stamp the line with the planet's depth, or does the line keep
the Sun's emission stamp?**

SDT's answer (GOM07): reflection is a **passive scattering** event — it does not
re-emit from the atomic depth field, so **a reflector is silent**. Reflected
sunlight carries the **Sun's** emission stamp (and the observer term), *not* the
planet's gravitational well. Only **self-emitted** light (the planet's own
thermal/auroral lines) carries the planet's depth.

GR, by contrast, treats the redshift as accumulated along the photon's worldline
through metric potential — so on a strict cancellation accounting the reflected
beam ends up **flat too**. The two ontologies therefore agree on the *reflected*
channel (degenerate) but **split on the self-emission channel**.

---

## 2. SDT Prediction (computed)

Two channels, two predictions:

- **Reflected channel (degenerate test)**: sunlight reflected from Jupiter or
  Venus shows **no extra planet-well redshift** — the line is emission-stamped by
  the Sun and re-emitted nowhere. SDT and GR both predict ≈ flat here; this leg
  *confirms the ontology* (reflector silence) without beating GR. (Lanza 2016
  Jupiter reflected-light data: slope +0.08 ± 0.32 — consistent with flat;
  re-stamp hypothesis rejected ~3σ.)
- **Self-emission channel (the fork)**: Jupiter's own **H₃⁺ auroral/thermal
  emission at 3.4–4 µm** originates deep in Jupiter's own depth field and is
  stamped with **Jupiter's** `z = ϟ_J/r_J`:

  | source | SDT self-emission shift | GR metric shift |
  |---|---|---|
  | Jupiter H₃⁺ (3.4–4 µm) | **≈ +6.6 m/s** | ≈ +3.7 m/s |

  The **factor ≈ 1.8 difference** is the discriminator. It exists because SDT
  stamps at the emission *depth* (full `ϟ/r` at the emitting layer) while GR
  integrates the metric potential to the observer with the standard cancellations.

---

## 3. Standard-Model Prediction

GR: the gravitational redshift is a worldline integral of the metric potential.
Reflected sunlight, accounted consistently (down the well and back out, plus
relative potentials), yields ≈ no net planet-well term — **flat**, same as SDT.
Self-emitted Jovian lines carry Jupiter's surface-to-observer potential
difference: `z_GR ≈ GM_J/(c²R_J) − …` ≈ **+3.7 m/s** for the H₃⁺ layer. No factor
of ~1.8 enhancement.

---

## 4. Observable

| Channel | SDT | GR | Verdict value |
|---|---|---|---|
| Reflected sunlight (Jupiter, Venus) | flat | flat | confirms reflector silence (shared-input; not independent) |
| **Jupiter H₃⁺ self-emission 3.4–4 µm** | **+6.6 m/s** | **+3.7 m/s** | **the fork — ~1.8× split** |
| Depth scaling Venus vs Jupiter | own-well, not Sun's-well | own-well | sign/scale cross-check |

The single discriminating measurement: the absolute gravitational redshift of
Jupiter's **own** H₃⁺ emission lines, to ≈ ±1 m/s — distinguishing +6.6 (SDT)
from +3.7 (GR).

---

## 5. Apparatus

- **Self-emission**: high-resolution L-band (3–4 µm) spectroscopy of Jovian H₃⁺
  aurorae — VLT/CRIRES+, Keck/NIRSPEC, or JWST/NIRSpec — with an absolute
  wavelength solution good to ≈ 1 m/s (telluric/comb calibration). Compare the
  measured emission redshift against both predictions.
- **Reflected (control)**: existing high-resolution solar-spectrum-off-planet
  data (cf. Lanza 2016 for Jupiter); Venus reflected spectrum as a deeper-vs-shallower
  reflector cross-check.
- **Critical care (a corrected-twice lesson)**: predictions are
  **SDT = flat reflected / +6.6 self-emission**, **not** the other way; and the
  relevant well is the **emitter's own** depth (Jupiter's for H₃⁺), with Saturn <
  Jupiter ordering as the consistency check. Doppler/rotation/wind fields of the
  auroral layer must be modelled out — the main systematic.

---

## 6. Feasibility

**MODERATE.** The reflected control is archival. The self-emission fork needs
absolute 3–4 µm spectroscopy at ≈ 1 m/s on a bright, well-studied target (Jupiter
H₃⁺) — within reach of current IR spectrographs with comb/telluric calibration.
The systematic challenge is the auroral velocity field, not the photon precision.

---

## 7. Impact

- **If Jupiter's self-emission shows ≈ +6.6 m/s**: the redshift is stamped at the
  **emission depth**, not integrated along the worldline — SDT's depth-closure
  ontology beats the metric account by a measured factor ~1.8, while the flat
  reflected channel confirms reflector silence.
- **If it shows ≈ +3.7 m/s**: GR's metric integral is correct and SDT's
  full-`ϟ/r` emission stamp is falsified for self-emission. A clean kill of the
  emission-depth claim. (The reflected channel cannot decide it — that leg is
  degenerate by construction.)

---

## 8. Predicted curve (reproduce)

Self-emission: `z_SDT = ϟ_J/R_J` at the H₃⁺ layer → ≈ +6.6 m/s; `z_GR ≈
GM_J/(c²R_J)` → ≈ +3.7 m/s (`GM_J → v_surf²R`, no `G`/`M` as fundamentals).
Reflected: emission-stamped by the Sun → no planet-well term (flat). The fork is
the self-emission ratio `z_SDT/z_GR ≈ 1.8`.
