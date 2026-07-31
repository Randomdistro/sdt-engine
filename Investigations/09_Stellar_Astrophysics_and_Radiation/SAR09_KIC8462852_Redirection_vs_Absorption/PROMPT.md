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
