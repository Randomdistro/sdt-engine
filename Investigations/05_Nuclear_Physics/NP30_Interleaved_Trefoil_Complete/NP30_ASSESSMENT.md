# NP30 triton-contraction root audit — results

**Audit status:** COMPLETE
**Observational status:** radius regularities reconstructed descriptively
**Mechanism status:** UNADJUDICATED — no native predictor of closure locations
**Downstream NP32 anchor:** not independently derived

## Source and method result

The canonical IAEA radius cache and the separate CSV consumed by the historical ATOMICUS tools are byte-identical.  All source gates passed; the full identities are recorded in `NP30_CONTRACTION_ROOT_SOURCE_FREEZE_2026-08-09.md`.

The historical material defines `n_t = N - Z` and `n_d = 2Z - N - 2`, so the alleged triton count is an algebraic re-expression of the observed proton and neutron counts.  NP30 §11 supplies the one-neutron excess equation in prose, but the frozen historical scripts do not implement its claimed 86% calculation or identify the stated 281-member selection.  The historical closure tool does implement a different, later three-point curvature calculation and hard-codes `MAGIC = [8,20,28,50,82,126]`.

## Independent observational reconstruction

The source-gated parser found 908 valid radii and 887 rows satisfying the historical grammar-count non-negativity rule.  With the frozen adjacent-pair definition, it found:

| Statistic | Result |
|---|---:|
| all grammar-valid one-neutron pairs | 530 / 679 negative (`78.06%`) |
| `A_endpoint >= 40` pairs | 502 / 648 negative (`77.47%`) |
| heavy mean excess over the `A^(1/3)` step | `-5.6842 mfm` |
| heavy median excess | `-4.7117 mfm` |
| endpoints at imported neutron-closure labels | 30 / 31 negative; mean `-11.4561 mfm` |
| nonclosure endpoints | 500 / 648 negative; mean `-7.5102 mfm` |

Thus the data contain a negative heavy-isotope step tendency under the stated observational reduction.  The reconstructed heavy mean is close to the historical `-5.9 mfm` description.  However, the historical `86%` value is **not reproducible** from a specified executable method or a recoverable 281-row membership list; the fully specified reconstruction yields `77.47%` for the stated heavy domain.  This is `UNREPRODUCED_HISTORICAL_PERCENTAGE`, not a license to select a subset until 86% appears.

## Closure result and mechanism conflict

The later closure-kink tool independently reproduces all 19 calculable imported-neutron-closure kinks as negative.  For N=28, 50, and 82, its precommitted constant-across-isotone model beats its own triton-occupancy-proportional alternative:

| Imported N label | Members | Constant RMS (mfm) | Proportional RMS (mfm) |
|---|---:|---:|---:|
| 28 | 3 | `4.3653` | `15.4696` |
| 50 | 5 | `1.7306` | `5.6812` |
| 82 | 9 | `1.4354` | `3.1529` |

This is a real reproduced **association** between the imported closure labels and the observed curvature.  It is not a derivation of those labels: they are a hard-coded input to the tool.  It also cannot establish that triton occupancy is the local cause of the closure kink, because the tool's own result favors occupancy independence across each fixed-N isotone.  A separate geometric mechanism could be proposed, but it is not supplied here.

## Correction and downstream impact

- Retain the observational regularities, their source hashes, and the later closure-kink summary.
- Downgrade the NP30 claim “triton-exchange contraction is metric-neutral and real” to `OBSERVATIONAL_REGULARITY_REPRODUCED_MECHANISM_UNADJUDICATED`.
- Mark the N=82/Z=50 lock passed to NP32 as `CLOSURE_LOCATION_EMPIRICALLY_IMPORTED`, not an independent SDT origin.
- Do not call the close-pack floor a physical hard wall from these RMS values; its observable mapping is separately unresolved in the NP12b audit.

No standard-model prediction or fitted coefficient was used as a decision rule, and no canonical file was changed.

## Reopening gate

To turn this into a physical prediction, first derive the closure schedule and a geometry-dependent radius/cost observable from SDT primitives without inserting magic numbers.  Freeze the exact isotope membership, uncertainty rule, triton/deuteron construction, and forward effect size before reading an independently registered holdout set.  The same model must predict both the between-closure trend and the closure event; it may not use a hard-coded closure list to claim their origin.
