# SAR09 — Assessment (direct, 2026-07-30)

> Pre-registration: PROMPT.md (committed before instrumentation).
> Instrument: `sar09_gamut.py`, single pass, whole range. Output: `RUN_LOG.txt`.
> Data: `C:\sdt-data\kic8462852\` (DATA_MANIFEST.md). Author: J. C. Harvey, Melbourne.

## Instrument validation — all three gates PASS

- **V1** dip census: D792 recovered at BKJD 792.720, depth 14.25% (published ~16%,
  within the ±15% relative tolerance); D1519 at BKJD 1519.523, depth 20.72%
  (published ~21%). D1568 also recovered (7.70%), unasked.
- **V2** rotation: 0.8782 d vs published 0.88 d.
- **V3** photosphere anchor: W1 +0.1σ, W2 +0.9σ after the stated 0.08-mag
  blackbody-systematic floor (ADJ-1; the bare-blackbody W2 miss is the known
  4.6 μm CO feature of F stars — instrument corrected, not the data).
- Two instrument adjustments, both disclosed: ADJ-1 (model floor), ADJ-2
  (Jy/SI unit conversion in the dust term — caught because the budget table
  printed zeros, impossible for warm dust).

## Q1 — the infrared ledger: STEADY-STATE ABSORPTION EXCLUDED

A steady screen absorbing the measured Kepler-era deficit (f = 0.03 of L*)
must brighten the WISE bands by:

| r [AU] | T_d [K] | ΔW3 [mag] | ΔW4 [mag] |
|---|---|---|---|
| 0.1 | 1294 | +1.57 | +1.73 |
| 0.3 | 747 | +2.71 | +3.11 |
| 1.0 | 409 | +3.66 | +4.56 |
| 3.0 | 236 | +3.68 | +5.50 |
| 10.0 | 129 | +1.93 | +5.59 |

Measured: W3 sits at **+0.14 ± 0.12 mag** from the photosphere (consistent with
zero); W4's upper limit is 4+ mag below the predicted dust brightness at r ≥ 0.3 AU.
The shortfall is a factor of **4 to 160 in flux** across the entire 0.1–10 AU
range — beyond the pre-registered ≥3× margin at every radius. **Steady-state
absorption at the measured optical deficit is EXCLUDED.** The surviving
absorption escape is named: transient dust that never reaches thermal steady
state — which must then stay transient across a fade documented over a century.
Redirection carries this fact at zero cost: nothing absorbs, no ledger exists.
Disclosed: the qualitative "no excess" was prior literature (Marengo 2015,
Meng 2017); the quantified budget and margin are computed here.

## Q2 — chromatic ratios (GTC, in-locker): NON-GREY CONFIRMED; VARIABILITY NOT ESTABLISHED

Fourteen GTC pointings parsed from Deeg+ 2018's own table (their two exclusions
honoured); eight carry significant dimming. Blue/red extinction ratio
A₅₅₆/A₈₆₈ per pointing: 1.68 ± 0.39 → 2.81 ± 0.56.

- **Grey occultation is excluded in-data**: every significant pointing is
  chromatic; jointly the mean ratio ≈ 2.0 sits many σ above grey (= 1.0).
  A grey macro-occulter — the megastructure-sheet class — does not fit this star.
- **Ratio variability: max−min = 1.13 ± 0.68 (1.7σ) — below the pre-registered
  2σ.** Adjudicated as committed: the in-locker data are consistent with one
  fixed wavelength dependence; the geometry-set-ratio claim takes damage and
  is NOT established here. Scope: fourteen pointings are underpowered for this
  test; Bodman+ 2018, with the fuller LCO set, report that "a single wavelength
  dependence does not fit" and the dimming "varies in time" — cited as
  literature, not claimed as our result. The follow-up is the LCO
  machine-readable table (manifest gap #1).

## Q3 — spin-phase coherence: FIELD-LOCKED VARIANT EXCLUDED

Power at P_rot inside the deep-dip windows vs 39 quiet bootstrap windows
(95th percentile 0.0104): D1519 shows excess (0.0232), D792 does not (0.0060).
The pre-registered criterion required both. **The dipping structure does not
know the stellar spin phase: the star's-own-field variant is excluded.** The
structure is exterior — true for orbiting dust AND for exterior redirecting
structure; this gate cuts within SDT's options, not between the accounts.

## Q4 — brightenings (characterisation): two sustained events (+0.1%, >1 d)
recorded in the Kepler record. No verdict attached, per pre-registration.

## Standing after the run

| Account | Status |
|---|---|
| Steady absorbing dust | **EXCLUDED** (Q1: factor 4–160 below its infrared bill) |
| Grey macro-occulter (megastructure sheet) | **EXCLUDED in-data** (Q2: dimming is non-grey at every significant pointing) |
| Transient dust | SURVIVES — at the cost of never reaching steady state across a century-scale fade (named fine-tune) |
| SDT redirection, field-locked | **EXCLUDED** (Q3) |
| SDT redirection, exterior structure | SURVIVES — carries no-IR for free; non-grey natural; ratio-variability unproven in-locker (1.7σ, underpowered) |

## What is owed

1. The LCO 2017 MRT → rerun Q2 with the fuller dataset (the 2σ question is
   answerable; 14 pointings were not enough).
2. An SDT dispersion law n(λ) for displacement-field structure — without it,
   redirection predicts *that* dimming is chromatic but not *how much*; the
   measured ratio ≈ 2.0 over 556→868 nm is the target such a derivation must hit.
   No exponent was fitted here and none is claimed.
3. TESS dip census (sectors cached, unsearched) and the AAVSO series — the
   2019–2022 record extends every test above.
