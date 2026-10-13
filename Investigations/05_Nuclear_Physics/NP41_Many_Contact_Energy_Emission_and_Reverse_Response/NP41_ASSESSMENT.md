# NP41 — Assessment, P0 residual map (2026-10-05)

**Classification:** `NP41_CONSTRUCTION_SHAPE_TRACKS_BINDING__MAGNITUDE_FACTOR_2P7_UNIDENTIFIED`<br>
**Run class:** direct. Tools `np41_residual_map.js` (unchanged engine `docs/js/traction-gear-engine.js`, validator's result write redirected), `np41_analyse.py`; outputs `np41_residual_map.json`, `np41_results.txt`. Pre-registered in `RUN_LOG.md` before the run. **Canon edits:** none. **Fitted parameters in the registered statistics:** 0.
Measured binding is the sequencer table's own column (spot values matched AME2020-based figures in the continuation audit); not re-derived from AME2020 here. In the engine, B_calc = Σ contact coupling × αħc/R_p × contraction scale; the measured value is not an input to it.

## Registered statistics (217 nuclides, none pruned, 0 non-finite)
| Statistic | Value |
|---|---|
| B_calc/B_meas, median (IQR) | 0.366 (0.360–0.381); min 0.346, max 0.594 |
| Spearman(B_calc, B_meas) | 0.9997 |
| Spearman(B_calc/A, B_meas/A) | 0.4709 |
| R² of B_calc/A vs B_meas/A | −163.7 |
| R² of total B_calc vs B_meas | −0.79 |
| corr(ratio, max contact degree) | −0.851; corr(ratio, A) −0.626 |

Median B_calc/B_meas by A: 0.439 (A < 20), 0.390 (20–60), 0.366 (60–120), 0.359 (120–200), 0.364 (200–260).

## Assessment
1. The registered R² values fail badly because B_calc is about 37% of B_meas, so squared residuals are dominated by the scale. They do not describe the shape. Rank agreement is 0.9997, so the construction orders binding across the chart almost perfectly; it does not yet get the magnitude.
2. Diagnostic only (not a registered law, would be CALIBRATED(1)): per-nuclide k = B_meas/B_calc has median 2.729; for A ≥ 60 (n = 157) median 2.756, IQR 2.718–2.788; one global k = 2.757 brings the median absolute residual to 1.6% across all 217 nuclides. Light nuclei depart (Li-7 1.68, Be-9 1.93, B-10 1.87, B-11 2.12, C-13 2.23, N-14 2.17, N-15 2.30, O-17 2.28, F-19 2.30). Nine nuclides lie outside 2.3–2.9, all with A < 20.
3. The residual is therefore nearly one unexplained factor of about 2.7–2.76 with a light-nucleus tail, correlated with the maximum contact degree (−0.85). The factor is not identified; no candidate expression has been tested, and any identification would need a look-elsewhere census registered first (a handful of constants near 2.7 are available).
4. Contacts per nucleon: median 1.000. B_calc per contact: median 3.142 MeV; B_meas per contact 8.467 MeV. Noted, not interpreted.
5. Consistent with the NP24 shared-input rule: the near-perfect rank agreement is expected for any construction whose contact count grows with A; what is informative is the constancy of the ratio at A ≥ 60 (IQR ±1.3%), which a pure count would not give.

## Next (register before running)
P1: a value-law candidate for the factor with its parameter count fixed in advance, fitted (if at all) on the light set and tested once on a sealed heavier subset; P2: degree census and port reading (212 of 217 nuclides exceed three contacts). The light-nucleus tail should be examined as its own class (A < 20 departs from the plateau).

## Instrument check (2026-10-05)
Wake-pair sample count changed 4 → 8 in a scratch copy of the engine: calculated binding unchanged to 1e-4 MeV on five nuclides (He-4 to Fe-56). The factor of about 2.7 between B_meas and B_calc is not a numerical-resolution artefact. Engine copies in `docs/js` and `Release/HTML_SDT_Website/js` are byte-identical.

## Round 2 (2026-10-05) — contact-kind regression, exploratory
Registered in `RUN_LOG.md` before the run. Tools `np41_kinds.js`, `np41_kinds_fit.py`; output `np41_kinds_results.txt`. Parameters: 4 (alpha, dock, internal, interstitial-dock), CALIBRATED(4) and labelled exploratory; not a value law.

| Fit | Result |
|---|---|
| All 217, per-kind energies (MeV) | alpha 5.78, dock 13.72, internal 5.12, interstitial-dock 4.77; median \|residual\| 1.1% |
| Train A < 60, test A ≥ 60 | energies change (alpha 3.69, dock 9.16, internal 9.14, interstitial-dock 9.84); test median 6.8% |
| Train A ≥ 60, test A < 60 | energies change again (alpha 18.8, dock 10.1, internal 6.88, interstitial-dock 3.22); test median 11.7% |
| Interleaved split (even → odd index) | test median 0.98% (neighbouring nuclides are near-duplicates, so this split flatters) |
| One energy per contact, 8.274 MeV | median \|residual\| 3.2% |
| B = k·A baseline, k = 8.274 MeV | median \|residual\| 3.2% (identical) |

## Assessment
1. The contact count equals A in this construction (contacts per nucleon 1.000, and the single-energy fit is identical to B = k·A). Counting contacts adds no information beyond A, so the 3.2% is the saturation of B/A, not a result of the contact graph.
2. The per-kind energies are not stable: they move by factors of 2–6 between the two mass-range splits, and the cross-range test errors (6.8%, 11.7%) are worse than B = k·A. The 1.1% all-fit residual is four parameters used on the data scored. Per-kind energies are therefore not identified by this data; no value law follows from them.
3. What survives from the P0 map: the engine's own B_calc has a stable plateau ratio at A ≥ 60 (IQR ±1.3%) that the contact count alone cannot produce. That plateau is the engine's contact-coupling geometry, so the useful next probe is the per-edge coupling values (`contactWakeLedger`) by kind, not counts.
4. Next (register first): extract per-edge `contactCoupling` by kind from the ledger and test whether the plateau factor comes from one edge class; then a sealed-set test of any proposed expression for the factor. Both are propose-only until registered.

## Round 3 (2026-10-05) — per-edge coupling by contact kind
Registered in `RUN_LOG.md` before the run; tool `np41_edge_coupling.js`, analysis `np41_edge_analyse.py`, output `np41_edge_results.txt`. Statistics only; no refit.

| Kind | edges | mean contactCoupling | CV across edges | share of total coupling |
|---|---|---|---|---|
| alpha | 868 | 1.916 | 0.033 | 4.1% |
| dock | 8595 | 1.769 | 0.079 | 37.5% |
| internal | 12936 | 1.750 | 0.083 | 55.8% |
| interstitial-dock | 581 | 1.838 | 0.072 | 2.6% |

- All four kinds carry nearly the same coupling per edge (1.75–1.92, spread 3–8% within each kind). No single contact class carries the plateau; it is a uniform per-contact quantity: median 1.783 per edge (IQR 1.747–1.845) × αħc/R_p (1.712 MeV) ≈ 3.05 MeV per contact against B_meas/A ≈ 8.3–8.5 MeV per contact.
- Mean coupling per edge by range: 1.867 (A < 20), 1.859 (20–60), 1.762 (A ≥ 60). The light-nucleus tail in B_calc/B_meas follows the larger alpha-contact share (corr +0.78) and the larger coupling per edge in small nuclei.
- Assessment: the shortfall is one per-contact normalisation (about 2.7–2.8 in energy), not a missing contact class. Whether that normalisation is derivable from the construction (the interaction scale or the coupling integral's own definition) is the open question; no candidate has been tested, and any candidate needs a pre-registered look-elsewhere census.
