# OP07 — Solar Lens-Artifact Experiment (Falsifier Capstone)

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

This is the **falsifier capstone** of the optics suite: the dated, falsifiable prediction from
OP01-H4 and [[project_solar_lens_artifact_claim]]. The Sun appears as a slightly different disk at
different wavelengths, conventionally read as imaging *different physical layers* ("the UV Sun," "the
Hα Sun," etc.) at different heights. SDT says there is **one dispersive emitting surface** behaving
as a gradient-index lens (OP01), and the apparent layers are **dispersive lens artifacts of that one
surface**. **Does a high-cadence false-colour λ-scan of the solar limb show the disk GROW then
partly VANISH at the ~4400–5000 K temperature-minimum band — a caustic FOLD where `T(height)` turns
over and the `n(height,λ)` mapping becomes degenerate — then REAPPEAR, exactly as a single-surface
gradient-index lens predicts, and unlike the "different real layers" picture?**

## SDT mechanism & hypotheses

`T(height)` is non-monotonic: it falls from the photosphere to a minimum (~4400–5000 K, ~500 km up)
then rises into the chromosphere. Map height→closure depth `z`→index `n(height,λ)` (OP01). Where
`dn/dh` changes sign (the temperature minimum) the ray mapping folds: a caustic. A caustic in a
dispersive lens images the limb at a λ-dependent radius and, at the fold, **degenerates** — the
apparent edge piles up, brightens, then a band drops out and re-forms on the far side of the fold.

- **H1 (one surface):** every λ images the *same* emitting surface; apparent radius `R(λ)` is the
  lens's λ-dependent focal mapping, not a different physical layer.
- **H2 (the fold):** at the temp-minimum shell the `n(h)` mapping is two-to-one (T(h) turns over), so
  the false-colour limb shows grow → fold/vanish → reappear across that ~4400–5000 K band.
- **H3 (SDT≠standard):** the standard picture predicts a *monotonic* layer sequence with λ and no
  caustic degeneracy at the temp minimum; SDT predicts the specific non-monotonic fold signature.

## Strategy

**Phase 1 — Forward model.** *Goal:* `R(λ)` and the caustic from a realistic `T(h)`. *Method:* map
`T(h)→z(h)→n(h,λ)` (OP01) and ray-trace the limb. *Success:* a rendered false-colour limb showing the
grow→fold→reappear band, with the fold λ-range and height quantified.

**Phase 2 — Observational protocol.** *Goal:* a concrete, runnable experiment. *Method:* specify a
tunable narrowband λ-scan (e.g. 400–1600 nm, ≤0.3 nm steps) of the limb at fixed seeing/cadence, with
adaptive optics; measure `R(λ)` and limb brightness vs λ across the temp-minimum band. *Success:* a
spec a solar telescope (e.g. DKIST-class) could execute, with required resolution and cadence stated.

**Phase 3 — Discriminator.** *Goal:* the falsifying difference. *Method:* compare the measured `R(λ)`
and the presence/absence of the fold against H2 (SDT) vs the monotonic-layer prediction. *Success:* a
clear PASS/FAIL rule: fold present at ~4400–5000 K ⇒ SDT; smooth monotonic `R(λ)` ⇒ SDT killed.

**Phase 4 — Robustness (stretch).** *Goal:* rule out instrumental/atmospheric mimics. *Method:* model
terrestrial dispersion and PSF wings. *Success:* the fold survives as a solar (not instrumental) feature.

## Success criteria

- **PASS (A):** model predicts the fold band, protocol is executable, and the discriminator cleanly separates SDT from the layer picture.
- **QUALIFIED (C):** fold predicted with `T(h)` profile as a MEASURED input; protocol executable (expected).
- **PENDING (D):** forward model done, observational discriminator only schematic.
- **FAIL (F):** no caustic fold arises from the one-surface gradient-index model — the multi-λ Suns are genuinely different layers.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 fold band | limb grows→vanishes→reappears at ~4400–5000 K | no caustic ⇒ not a single dispersive surface |
| T2 `R(λ)` non-monotonic | apparent radius turns over across the temp minimum | monotonic R(λ) ⇒ different real layers |
| T3 solar, not instrumental | fold persists after PSF/atmosphere modelling | feature is an artifact of the instrument, not the Sun |

## Dependencies

**Upstream:** OP01 (n=1/(1−z), dispersion, the solar fold), [[project_cq43_variable_closure]]
(`c_local`, the depth gradient). **Capstone of:** the whole OP suite (it is the falsifier OP01 sets up).
**Related:** [[project_solar_lens_artifact_claim]] (the dated priority claim), GOM01 (solar depth
engine, limb geometry), [[project_depth_closure_paper]] (solar gravitational redshift = depth).
