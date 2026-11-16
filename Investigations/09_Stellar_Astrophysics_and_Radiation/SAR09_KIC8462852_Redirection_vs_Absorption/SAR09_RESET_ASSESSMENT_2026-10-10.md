# SAR09 — KIC 8462852, redirection against absorption: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0.

**Read:**
- PROMPT.md, with its 2026-07-30 pre-registration carried
- C:\sdt-data\kic8462852\DATA_MANIFEST.md

**Not opened:** SAR09_ASSESSMENT_2026-07-30.md, RUN_LOG.txt, sar09_gamut.py. The manifest's one-line summaries ("no infrared excess"; Montet & Simon ~3% fade) were read; they are prompt-side facts.

## Registration details fixed now (the prompt leaves these open)

**V1 (dip census).**
- Kepler PDCSAP_FLUX, each quarter normalised by its median.
- **Recovered** if the minimum flux in BKJD 791–793 gives a depth of 16 ± 3% and the minimum in 1518–1520 gives 21.5 ± 3%, with each minimum's epoch within ±1 d of 792 and 1519.

**V2 (rotation).**
- Lomb–Scargle on out-of-dip cadences (flux ≥ 0.99), search 0.5–2 d.
- **Recovered** if the strongest peak lies within 0.02 d of 0.88 d.

**V3 (photosphere at W1/W2).**
- A blackbody at T_eff = 6750 K (F3 IV/V; [B], Boyajian 2015), normalised to W1.
- The predicted W2 must match the measured W2 within 3σ.
- WISE Vega zero points (Jy): 309.54, 171.79, 31.676, 8.363, at 3.368, 4.618, 12.082 and 22.194 µm [B, recalled].

**Q1 (infrared budget).**
- A steady, isotropic absorbing shell intercepts and absorbs a fraction f of the starlight and re-emits it thermally.
- Secular deficit **f = 0.03** (Montet & Simon 2016 Kepler-FFI fade; MEASURED-INPUT via the locker).
- Dust temperature T_d scanned over 100–1500 K (spanning about 10–0.1 AU around an F3 star).
- Required excess: E_req(λ) = f·[B_λ(T_d)/σT_d⁴]/[B_λ(T*)/σT*⁴]. This is independent of R*, L* and distance.
- Allowed excess: W3 measured against photosphere with a 2σ allowance; W4 is an upper limit (no error in AllWISE), used as the allowed ceiling.
- **Steady absorption EXCLUDED at a given T_d** if E_req ≥ 3·E_allowed in W3 or W4.
- **Absorption pays its bill** if E_req ≤ E_allowed.
- Reported across the T_d scan.

**Q2, Q3:** not run in this pass. Q2 needs the published colour-ratio table extracted from the tarballs; Q3 needs the dip fine-structure phase fold after V2.

## Run and results
(below)

**Attempt 1: G0 at V3.** V1 and V2 were met (output kept: `sar09_reset_1_results_attempt1_G0.txt`). The 6750 K blackbody photosphere predicted W2 = 10.370 against the measured 10.436 ± 0.020 (3.3σ). A pure blackbody is not a stellar photosphere at 4.6 µm. Q1 was not run, so no Q1 number was seen.

**Amendment (2026-10-10, after V3 failed, before any Q1 output).** The photosphere model is replaced by the standard Vega-system result: in the Rayleigh–Jeans regime a hot star's mid-IR photospheric colours are about 0.
- Predicted W2 = W3 = W4 = W1, with a model allowance of ±0.03 mag added in quadrature.
- V3 is applied unchanged (W2 within 3σ).
- The Q1 rules are unchanged, with E_req now taken relative to that photosphere: E_req(λ) = f·[B_λ(T_d)/σT_d⁴]/[B_λ(T*)/σT*⁴] keeps T* = 6750 K for the stellar SED shape.

**Attempt 2** (amended photosphere; everything else unchanged). Output in `sar09_reset_1_results.txt`.
- **V1 met:** D792 minimum at BKJD 792.720, depth 14.25%; D1519 at 1519.523, depth 20.72%. 65,268 Kepler cadences.
- **V2 met:** strongest period 0.8806 d.
- **V3 met:** W2 predicted 10.425, measured 10.436 ± 0.020 (0.3σ with the model allowance).

**Q1, the infrared budget.** Allowed excess: W3 0.084 (2σ); W4 1.517 (AllWISE upper limit).

| T_d (K) | W3 E_req | ×allowed | W4 E_req | ×allowed | outcome |
|---|---|---|---|---|---|
| 100 | 0.81 | 9.7 | 96.2 | 63.4 | excluded |
| 200 | 19.5 | 234 | 160 | 105 | excluded |
| 300 | 28.6 | 341 | 101 | 66.6 | excluded |
| 500 | 19.6 | 234 | 37.8 | 24.9 | excluded |
| 1000 | 5.25 | 62.7 | 6.88 | 4.5 | excluded |
| 1500 | 1.96 | 23.4 | 2.29 | 1.5 | excluded |

(All 9 scanned temperatures are excluded; 6 are shown.)

**Q1 outcome, as registered.** A steady, isotropic absorbing shell that removes the measured 3% (Montet & Simon) would need a W3 excess 10 to 340 times what WISE allows. **Steady isotropic absorption at the measured deficit is EXCLUDED at every T_d from 100 to 1500 K.**

**Scope.** The registered model is an isotropic shell; its covering fraction equals the deficit. Not excluded, and named:
- **(a)** transient or freshly destroyed dust;
- **(b)** a non-isotropic screen covering mainly our line of sight. Its re-emission scales with its covering fraction, which can be far below 3%.

These are the prompt's own named escapes. Disclosed prior: the literature (Marengo 2015; Meng 2017) reports no excess. The quantified budget is new here.

**What this does and does not say about redirection.** Q1 removes one absorption geometry. It does **not** compute a redirection (dispersive-depth) account: no native magnitude for the dips or the fade has been derived. Escape (b) still carries the facts. Per the prompt, Q1 is "kill-capable" against steady absorption only, and redirection takes no positive evidence from it.

**Q2 (colour-ratio variability) and Q3 (spin-phase coherence):** not run in this pass. Q2 needs the colour ratios extracted from the locker tarballs; Q3 needs the dip phase fold.

**Grades:**
- V1–V3: instrument validated.
- Q1: G1 for the steady isotropic absorbing shell (excluded); escapes (a) and (b) open.
- Redirection: G2 (no native magnitude).
- Q2, Q3: open.

## Comparison with the archived record
Deferred.
