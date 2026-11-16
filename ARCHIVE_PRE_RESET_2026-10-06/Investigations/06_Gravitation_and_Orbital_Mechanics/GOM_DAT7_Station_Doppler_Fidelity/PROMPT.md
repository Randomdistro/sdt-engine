# GOM34 — DSS-25 Station LOS + Band/Turnaround Doppler Fidelity

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Upstream:** GOM33 GEOM_DOPPLER_MAGNITUDE_PASS (geocenter ratio ≈ 3.37).  
> **Canon edits:** none.  
> **Notation:** SDT capital **K** = c-boundary radius (frozen). ODF `K` = turnaround.

## 0. Objective

1. Replace geocenter LOS with **DSS-25–centered** Cassini range-rate from Horizons.  
2. Apply band IDs / turnaround from the paired ODF (not fitted).  
3. Form a time-series residual `obs_Hz − f_pred` on P0 K252 type-12.  
4. Hold solar **K** fixed; do not fit it; do not claim SDT survival/exclusion.

## 1. Claims

| ID | Claim |
|---|---|
| GOM34-C1 | Horizons delivers Cassini range-rate with `CENTER='DSS-25'` for the P0 window. |
| GOM34-C2 | ODF band IDs decoded; Ka/Ka turnaround `209/15` applied when Item 11/12 = Ka. |
| GOM34-C3 | Two predictors compared (pre-registered): (A) geocenter+f_ref (GOM33 form); (B) DSS-25+band-aware carrier. |
| GOM34-C4 | Fidelity gate: median `\|f_pred_B\| / \|obs\|` is closer to 1 than GOM33’s 3.37 **or** residual median \|obs−f_pred_B\| < residual vs predictor A. |
| GOM34-C5 | Time-series residual summary published (min/median/max/stdev of obs−f_pred_B). |
| GOM34-C6 | Solar **K** unused or separate COMPUTED term only; never fitted. |

## 2. Predictor B (band-aware)

Carrier scale for 2-way coherent Doppler (first pass):

- Read `f_ref` (Items 18–19), downlink/uplink/exciter band IDs.  
- If uplink=Ka and downlink=Ka: turnaround `ρ = 209/15`;  
  `f_down ≈ ρ · f_up` with `f_up` taken as the TRK-2-18 reference frequency when that is the uplink scale, **or** documented Ka uplink nominal if `f_ref` is S-exciter scale.  
- `f_pred = −2 (ṙ/c) f_carrier` with `ṙ` = Horizons DSS-25 range-rate (m/s).

If `f_ref` is S-band scale while bands are Ka, use documented Cassini Ka downlink nominal **32000–34500 MHz class** only as a **sensitivity branch** labelled CALIBRATED(0) documentation constant — not a fit to ODF residuals. Primary branch remains `f_ref`-based; report both.

## 3. Decision rules

1. Horizons DSS-25 fetch failure ⇒ C1 PENDING_DATA / FAIL.  
2. C4 FAIL if neither closeness-to-1 nor residual improvement vs A holds.  
3. Fitting solar **K** or γ ⇒ protocol violation.  
4. No EMPIRICALLY SURVIVES / EXCLUDED label from this loop.

## 4. Frozen solar K

**K** = 1476.35 m (GOM26). Not a free parameter.

---

## Audit correction 2026-10-05 (record / status)

**Finding:** Ids read GOM34-C* against folder GOM_DAT7 and the gate "closer to 1 than 3.37 or smaller residual than predictor A" is relative, not absolute, so it could pass without agreement.

**Correction:** Add an absolute fidelity threshold and align the ids.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*

**Id alias (2026-10-05):** claim ids written `GOM34-C*` in this folder and its verdict are the claims of `GOM_DAT7`. The rows are VERIFICATION (data-structure, checksum and field-parse checks), not tests of a physical claim, and are excluded from physics PASS/FAIL tallies; earlier text is not rewritten.
