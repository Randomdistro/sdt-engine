# OP07 — Solar Lens-Artifact Experiment (Falsifier Capstone)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether the Sun's apparent "different disks at different wavelengths"
   are **separate physical layers** (the standard reading: "the UV Sun," "the Hα Sun" at different
   heights) or **dispersive lens artifacts of one emitting surface** behaving as a gradient-index lens
   (OP01) — distinguished by whether a high-cadence false-colour λ-scan of the limb shows a **caustic
   fold** (grow → vanish → reappear) at the ~4400–5000 K temperature-minimum band, where `T(height)`
   turns over and the `n(height,λ)` mapping goes two-to-one.
2. **Why does it matter?** — This is the **falsifier capstone** of the whole OP suite: the dated,
   on-the-sky prediction that OP01-H4 sets up. A clean fold confirms one dispersive surface (optics ≡
   lensing, [[project_solar_lens_artifact_claim]] priority); a smooth monotonic `R(λ)` kills the
   single-surface claim and vindicates the layered picture. It is where SDT optics meets an instrument.
3. **How will we find out?** — Four gated phases: forward-model `R(λ)` and the caustic from a real
   `T(h)` (mapping `T→z→n(h,λ)` via OP01) **before** asserting the fold; specify an executable
   DKIST-class λ-scan; state a binary discriminator; rule out instrumental/atmospheric mimics. Drawing
   the fold from a schematic `T(h)` and calling it a prediction caps the grade at C (anti-tautology
   gate) — it must survive a measured chromospheric profile.
4. **What would prove us wrong?** — §Falsification, numeric: no `R(λ)` turnover (monotonic to within
   measurement error) across 400–1600 nm; no brightness fold within the 4400–5000 K band; or a fold
   whose λ-position does not track the temp-minimum height; or one that vanishes under PSF/atmosphere
   modelling (instrumental, not solar).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

### Anti-tautology firewall

The fold must be a **forced consequence of the real, non-monotonic `T(h)`** fed through OP01's
`n=1/(1−z)` mapping — not a feature drawn into a hand-built profile. The load-bearing test: when the
*measured* chromospheric `T(h)` (e.g. VAL/FAL model atmospheres) replaces the schematic, does the
caustic survive at the temp-minimum height, and does its λ-position track `dn/dh→0`? **A fold that
only appears for a tuned `T(h)`, or that requires inserting a caustic by hand, is the identity, not
the prediction — it caps the grade at C (row IMPORTED).** `T(h)` enters as MEASURED-INPUT (the medium
descriptor), never as a fit to produce the fold. Light is the OP01 gradient-index relay; no
metric-bending, no photon-particle.

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

## ⑧ Falsification tests (each states the numeric outcome that kills it)

| ID | Test | SDT prediction | The number that kills it |
|----|------|----------------|--------------------------|
| F1 | Caustic fold present | apparent limb grows, then a band drops out and reappears, within the 4400–5000 K temp-minimum band (~500 km height) | **no** brightness/edge fold anywhere in 4400–5000 K across 400–1600 nm (to measurement error) ⇒ not a single dispersive surface — SDT killed, layers vindicated |
| F2 | `R(λ)` non-monotonic | apparent radius `R(λ)` turns over (dR/dλ changes sign) across the temp minimum | `R(λ)` monotonic with no sign change in dR/dλ (within the ≤0.3 nm-resolved scan) ⇒ the multi-λ Suns are genuinely different real layers |
| F3 | Fold λ tracks `dn/dh→0` | the fold's λ-position moves with the height where `dn/dh=0` as the measured `T(h)` dictates | the fold appears but its λ does **not** track the temp-minimum height ⇒ it is not the predicted `n(h)` caustic (coincidental feature) |
| F4 | Solar, not instrumental | fold survives PSF-wing and terrestrial-dispersion modelling as a solar feature | fold disappears (or fully explained) once instrument PSF + atmospheric dispersion are modelled ⇒ artifact of the telescope, not the Sun |
| F5 | Anti-tautology / robustness | the fold persists when a *measured* chromospheric `T(h)` (VAL/FAL) replaces the schematic | fold present only for a schematic/tuned `T(h)` and gone under the measured profile ⇒ Class capped at **C**, row IMPORTED (prediction not robust) |

## Dependencies

**Upstream (required):** OP01 (`n=1/(1−z)`, dispersion `n(λ)`, the solar fold it sets up),
[[project_cq43_variable_closure]] (`c_local`, the depth gradient), GOM01 (solar depth engine, limb
geometry). **Capstone of:** the entire OP suite — it is the on-sky falsifier OP01-H4 promises.
**Lateral:** [[project_solar_lens_artifact_claim]] (the dated priority claim),
[[project_depth_closure_paper]] (solar gravitational redshift = depth). **Framework:**
`Theory/00_Ruleset.md`, `Theory/05` audit spine.

## Questions This Opens *(generative — log new ones in `OP07_VERDICT.md`)*

1. **Does the same caustic appear on other stars?** If the fold is a generic temp-minimum signature,
   should every star with a non-monotonic `T(h)` show a λ-dependent limb fold — a population test
   beyond the one Sun?
2. **Can the fold's λ-width measure the temp-minimum sharpness?** Is the spectral width of the
   drop-out band a direct readout of how sharply `T(h)` turns over — a new chromospheric diagnostic
   independent of line-fitting?
3. **Does the fold shift with solar cycle / active regions?** If `T(h)` varies with activity, the
   fold λ should track it — is that a monitorable SDT prediction over an 11-year cycle?
4. **Is there a second fold higher up (transition region)?** `T(h)` rises steeply into the corona;
   does a second caustic appear at the transition-region gradient, and is it observable in EUV?
5. **Could a total-eclipse limb scan beat DKIST for this?** At totality the photospheric glare is
   gone — does the fold become easier to resolve, making eclipse spectro-imaging the decisive test?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — OP07
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (T(h) is MEASURED-INPUT — the medium descriptor, never tuned to make the fold)
- Engine namespaces used: depth_closure:: (n=1/(1−z), c_local, depth), OP01 dispersion n(λ), GOM01 limb geometry
- T(h) profile committed: [schematic for P1 scaffold → measured VAL/FAL for P4 robustness — name it]
- Phase thresholds (committed before run):
    P1 fold rendered with quantified λ-range + height · P2 λ-scan spec executable (≤0.3 nm, 400–1600 nm,
    AO, stated cadence/seeing) · P3 binary discriminator (fold@4400–5000 K ⇒ SDT; monotonic R(λ) ⇒ killed) ·
    P4 fold survives PSF + atmospheric-dispersion modelling as solar
- Forbidden retroactive changes: tune T(h) to manufacture the fold; insert a caustic by hand;
    widen the temp-min band post hoc; IDENTITY-PASS; local constant namespaces
```

### Pivot table (numeric triggers; solar-optics-specific)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|-------------------|---------------|----------------|-----------|
| P1 no caustic from schematic `T(h)` | check the `T→z→n(h,λ)` mapping and the dispersion sign | **KILL** the single-surface claim, report it | draw the fold in by hand |
| Fold present only for tuned `T(h)` | swap in measured VAL/FAL `T(h)`; if it persists, A | down-grade to **C**, tag row IMPORTED | claim A on a hand-shaped profile |
| P2 required resolution exceeds DKIST-class | relax to the best executable spec; state the gap | **DEFER** the on-sky test (forward model still stands) | claim "executable" without numbers |
| P3 `R(λ)` monotonic in the forward model | recheck dispersion `β` and the temp-min height | **KILL** SDT here (layers vindicated), report it | widen the band until a turnover appears |
| P4 fold removed by PSF/atmosphere | model wings/dispersion explicitly; is residual solar? | **OPEN** the instrumental-mimic question | declare it solar without the null test |
| `z ≥ 1` near the limb | weak-field break (CR10); restrict to the valid shell | **OPEN** that regime | ignore the break |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*OP07 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
