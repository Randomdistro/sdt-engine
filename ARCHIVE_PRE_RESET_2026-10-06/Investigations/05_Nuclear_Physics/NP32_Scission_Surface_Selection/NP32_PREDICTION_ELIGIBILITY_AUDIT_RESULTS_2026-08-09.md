# NP32 prediction-eligibility audit — results

**Audit status:** COMPLETE
**Data status:** IAEA independent-yield files identified, hash-verified, and independently reduced
**SDT empirical verdict:** UNADJUDICATED — no executable SDT split predictor was present to test

## Scope and source gate

This audit follows the frozen procedure in `NP32_ELIGIBILITY_AUDIT_PRE_REGISTRATION_2026-08-09.md`.  It separates two questions that the historical result conflated:

1. Are the stated cross-fissioner yield regularities reproducible from the selected observational tables?
2. Did the claimed SDT minimum-cut mechanism produce those quantities before the tables were opened?

All four historical artifacts and all eight independent-yield files passed exact SHA-256 and byte-count checks.  Their complete identities are in `NP32_SOURCE_PROVENANCE_FREEZE_2026-08-09.md`; the IAEA NDS provenance description and manifest checksum prefixes pre-existed in `Datasets/MANIFEST.md`.  The audit instrument hash is `f5555c86e766f322c744c7e7d6539b1ce9e6dd8944680ff253e422b201250c7d`; its deterministic JSON result hash is `cf318d99af453df388bc8e99d56cc67dcfab064b310a4c114fe1865d93c23dc7`.

## Mechanism audit

The stated initial conditions in `PROMPT.md` require a parent mesh contact graph, threaded-bond cost, a minimum-cost bipartition, and an input-to-channel selection rule.  The only historical computation, `np32_predict_check.py`, imports only `csv`, `math`, and `statistics`; its four functions are `massyield`, `hump_centroid`, `slope`, and `report`.

It opens an observed yield table, finds its two mass-yield modes, calculates centroids, slopes, a peak-sum residual, and valley statistics.  It contains no parent contact graph, bond/edge cost, partition/cut routine, model-specific function, or forward split emitted before data loading.  Thus:

- `MINIMUM_CUT_MECHANISM_UNIMPLEMENTED` applies to this claimed computation.
- The N=82/Z=50 lock is explicitly described as “measured this session”; no frozen native calculation of its location is in this branch's declared inputs.  It is therefore `ANCHOR_EMPIRICALLY_IMPORTED`, not an SDT-derived output.
- The script can legitimately summarize selected yield data, but it is not a zero-fit forward SDT predictor.  Its correct classification is `EMPIRICAL_REGULARITY_SUMMARY_NOT_ZERO_FIT_SDT_PREDICTION`.

This is a bounded source-and-mechanism conclusion.  It does not show that no SDT cut model could be implemented elsewhere, and it does not use any standard-model prediction as a rejection rule.

## Observational reconstruction

After the source gate, an independent stdlib implementation reproduced the frozen mass aggregation, fixed half-mass search windows, mode ±8 centroids, slopes, and P4 statistics without parameter fitting or data exclusion.  The full-precision rows are stored in `np32_prediction_eligibility_audit_results.json`.

| Gate | Reconstructed value | Literal result |
|---|---:|---|
| P1 heavy-centroid slope `< 0.25` | `-0.1968945162` | PASS |
| P2 light-centroid slope `[0.7, 1.3]` | `1.2598013156` | PASS |
| P3 every `nu_bc` `[1.5, 4.0]` | `2.3609725121` to `4.3766499781` | **FAIL** |
| P4 Th-232 shallowest fast valley **and** lowest fast P/V | neither condition holds | FAIL |

The stationary-heavy/sliding-light pattern is therefore a reproducible feature of these selected IAEA tables under the frozen summary statistic.  That observation cannot validate the SDT origin claim because the proposed selection mechanism has not emitted a split.

## False statement and correction

The historical results label P3 “PASS (strong)” while reporting a range of `2.4–4.4`; its own precommit requires **every** system to lie in `1.5–4.0`.  The independently reconstructed U-235 value is `4.3766499781`, above the stated upper bound.  The correct record is:

`HISTORICAL_P3_PASS_IS_FALSE_UNDER_ITS_STATED_EVERY_SYSTEM_GATE`.

No gate was broadened to rescue the claim.  The historical P4 `REFUTED` label is consistent with the reconstruction and remains unchanged.

During this audit, the first static detector mistakenly treated the word “weighted” in a centroid comment as evidence of a physical edge/bond cost.  That was a token-matching error, corrected before the final rerun by requiring actual `edge`, `bond`, or `cost` terms.  The corrected detector finds no such capability; neither version altered the absent graph/cut finding or any observational statistic.

## Required reopening test

Do not fit a lock position, a surface penalty, or a cut rule to these eight distributions.  To reopen the physical claim, first freeze a new branch that supplies:

1. a deterministic parent-to-contact-graph construction from defined SDT primitives;
2. a dimensionally specified bond/cut cost, admissible partition set, and tie-breaking rule;
3. a derivation of the lock location without inserting N=82/Z=50 or using the target yield peaks;
4. a forward mass-split distribution and an input-dependent product-shift prediction; and
5. independent, hash-registered holdout yields accessed only after all four model items are frozen.

Until then, the data regularity is retained, P3 is corrected to failure, and the mechanism's empirical status remains `UNADJUDICATED`.
