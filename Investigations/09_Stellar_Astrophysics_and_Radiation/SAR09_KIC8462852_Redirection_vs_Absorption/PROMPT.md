# SAR09 — KIC 8462852: redirection against absorption (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the next step. The 2026-07-30 pre-registration is kept below the line; its Q2 and Q3 stand and are now specified.

## 1. What is established (reset run 2026-10-10, `SAR09_RESET_ASSESSMENT_2026-10-10.md`)
- **Instrument validated.**
  - V1: dips recovered at BKJD 792.72 (14.3%) and 1519.52 (20.7%).
  - V2: rotation 0.8806 d.
  - V3: W2 photosphere within 0.3σ, after the amendment below.
- **Q1: steady isotropic absorption at the measured 3% deficit is EXCLUDED** at every dust temperature 100–1500 K. The W3 excess required is 10–340 times what WISE allows.
- **Open, by name:**
  - (a) transient or freshly destroyed dust;
  - (b) a non-isotropic screen covering mainly our line of sight, whose re-emission scales with covering fraction, not with the deficit.
- **Redirection:** G2. No native magnitude for the dips or the fade has been derived. Q1 removes one absorption geometry; it gives redirection no positive evidence.

## 2. Errors, and what they teach
- **X1.** A 6750 K blackbody is not a photosphere at 4.6 µm. Attempt 1 failed V3 at 3.3σ (G0, output kept). The amendment (Vega-system colours of about 0 in Rayleigh–Jeans, ±0.03 mag) was made **before** any Q1 output. **Lesson:** validate the photosphere on the bands themselves before using it as a baseline.
- **X2.** Q1 can only remove absorption geometries. **Redirection needs its own magnitude.** The solar renormalisation and lens work (2026-10-09/10: one dispersive surface; C-011, the radius minimum near 5–7 µm) is the native route to a redirection signature. Its chromatic prediction must be written for an F3 star before any colour data are opened.

## 3. Next round (register before computing)
- **Q2 (colour-ratio variability):**
  - **Data:** extract the published multi-band dip depth ratios from the locker tarballs, with provenance.
  - **Prediction, written first:** absorption by small dust gives a depth ratio rising toward the blue. Redirection by a dispersive surface gives the chromatic form derived from the lens formulation for an F3 photosphere.
  - **Gate:** the measured ratio lies inside one prediction's band and outside the other's.
- **Q3 (spin-phase coherence):** fold the dip fine structure on 0.8806 d. Redirection tied to the star's own surface predicts phase coherence; occulting debris on Keplerian orbits does not.
  - Statistic: Rayleigh test on dip-minimum phases, registered with its p threshold of 0.01 before the fold.
- **Escape (b) quantified:** the largest line-of-sight screen consistent with W3/W4, as a covering fraction. Reported, not graded.

## 4. Prohibitions
- No dust model tuned after seeing colours.
- No redirection claim without its own registered magnitude.

---

## Pre-registration of 2026-07-30 (kept as written)

# SAR09 — KIC 8462852: Redirection vs Absorption

> **Status:** OPEN — pre-registered 2026-07-30 BEFORE instrumentation.
> **Author:** J. C. Harvey, Melbourne. Gateways binding. Direct execution only.
> **Data:** `C:\sdt-data\kic8462852\` (see DATA_MANIFEST.md — provenance + stated gaps).

## The question

KIC 8462852 presents five simultaneous measured facts: aperiodic dips to 22%;
a secular fade on two timescales; CHROMATIC dimming whose colour ratio varies
between events; NO infrared excess; an ordinary F3 star with a bound companion.
The prevailing account is absorbing dust. The SDT candidate is **redirection**:
dimming by dispersive-depth structure in the displacement field along the line
of sight — light redirected, not absorbed. Which account carries the five facts?

## The fork (stated before looking)

- **Absorption (dust):** colour ratio is a MATERIAL property (grain population);
  absorbed optical power must re-appear in the thermal infrared; steady-state
  circumstellar dust at the measured optical deficit implies a computable W3/W4
  excess. Escapes: transient/freshly-destroyed dust; per-event grain populations.
- **Redirection (SDT dispersive depth):** colour ratio is a GEOMETRY property of
  each transit — free to vary event to event; NO infrared ledger exists; total
  flux is conserved over angle (brightenings are permitted for caustic
  alignments but NOT required toward any one observer).

Shared form disclosed: both predict chromatic dimming. Chromaticity alone
CANNOT DISCRIMINATE. The gates below are chosen on where the accounts differ.

## Pre-registered instrument validation (before any new claim)

- **V1 — dip census recovery:** single pass over all 18 Kepler quarters
  (PDCSAP, stitched, normalised). The instrument must recover the PUBLISHED
  Boyajian 2015 dip census — the D792 event at ~16% and D1519 at ~21–22% depth,
  epochs within ±1 d — before any further use. Fail → fix instrument, not data.
- **V2 — rotation recovery:** periodogram must recover the published 0.88-day
  rotation signal.
- **V3 — IR photosphere model:** the W1/W2 bands (photosphere-dominated) must
  match the model within 3σ before W3/W4 are read.

## Pre-registered questions and gates

- **Q1 — the IR budget (kill-capable, two-sided).** From the measured secular
  optical deficit, compute the thermal re-emission a steady absorbing screen at
  0.1–10 AU would add to W3/W4 over the photosphere model. Compare to measured
  WISE W3/W4.
  - If measured excess ≥ the required budget → the absorption account pays its
    bill; redirection loses its unique support. Record as such.
  - If measured excess is ABSENT at ≥3× below the required budget → steady-state
    absorption at the measured deficit is EXCLUDED; only transient-dust escapes
    remain (named, not hidden). Redirection carries the fact for free.
  - Disclosed prior knowledge: the literature (Marengo 2015; Meng 2017) reports
    no excess. The new content is the QUANTIFIED allowed dust budget, computed
    here, not imported.
- **Q2 — chromatic ratio variability (fork-classifier, not a kill).** Extract
  every measured colour-ratio/extinction-exponent in the locker (Deeg GTC
  per-event; Bodman inter-event; Meng secular). Test: do the ratios differ
  between events, and does the secular exponent differ from the dip exponents,
  beyond joint 2σ?
  - YES → consistent with geometry-set ratios (redirection) AND with per-event
    grain populations (absorption escape) — classify, state the degeneracy.
  - NO (one fixed ratio everywhere) → geometry-set ratios take damage; a single
    grain population stands. Two-sided, adjudicated on the numbers.
- **Q3 — spin-phase coherence (fork-classifier).** Phase-fold Kepler dip fine
  structure on the rotation period. Structures of the star's OWN field should
  know the spin phase; external transiting material should not.
  - Coherence across ≥2 independent deep dips → field-structure reading
    supported. Absence → the structure is exterior; the field-locked variant is
    excluded (redirection by exterior structure survives). Not a kill on SDT.
- **Q4 — brightening census (characterisation only, no gate).** Catalogue
  excursions above the rotational envelope (threshold +0.1% sustained > 1 day
  after detrending). Redirection permits caustic brightenings; absence proves
  nothing (redirected flux need not point at us). Recorded to inform the next
  round; no verdict hangs on it.

## Tolerances (committed)

V1 depths ±15% relative, epochs ±1 d; V2 period ±0.02 d; V3 3σ; Q1 factor-3
margin on the budget; Q2 joint 2σ. Whole-range single pass; no per-event
re-tuning; every number printed with its comparison.

## What this is NOT

No claim is made that SDT owns a derived dispersion law n(λ) for the medium —
it does not, and no exponent will be fitted and called a prediction. Q2 reads
exponents from measurement and classifies; deriving the SDT dispersion law is
the follow-up this investigation would open, not a result it asserts.

---

## Audit correction 2026-10-05 (data / provenance)

**Finding:** The data sit in `C:\sdt-data\kic8462852\`, outside the repo, so a reader cannot reproduce the gamut from the repository.

**Correction:** Record the retrieval script and hashes in Datasets and cite them from the prompt.

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
