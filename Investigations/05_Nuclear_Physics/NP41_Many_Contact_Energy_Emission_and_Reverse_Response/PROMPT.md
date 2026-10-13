# NP41 — Many-contact energy, emission and reverse response (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work. The previous specification is kept below the line.

## 1. State after the reset (2026-10-10)
**Deferred:** P0's residual map needs the NSEQ18 construction outputs. The 2026-10-05 correction forbids count regressions as a value law.

## 2. New data and what it teaches (2026-10-10 to 2026-10-12)
- **The live sequencer was driven by node on 2026-10-10/11** (records: NP17 addendum; `NP17_.../CASCADE_ASSESSMENT_2026-10-11.md`; PPT18 stage 1). Findings:
  - The light seeds ²H, ³H and ³He are **CALIBRATED(8/9)**, fitted exactly to their own B, μ and Q.
  - The zero-fit universal ledger (wake contact coupling × αħc/R_p × contraction) is **B6 on all 250 stable nuclides**: right order, with ratio CV 8.5%, missing a factor that grows with coordination.
  - **Wrong-sign binding** in 23 of 173 isotope steps: contraction multiplies binding and also lowers the wake coupling.
  - Every A ≥ 4 graph is **one α 4-ring plus a tree** (E = A).
  - μ(⁴He) = 1.65 μN against 0.
  - The H1 nucleon envelope reaches **1.085 R_p**, using untraced constants (0.06 fm strand, 5.28 fm helix). Canon-consistent sizes (PPT18 stage 2a): R = 0.444 fm and a = 0.397 fm for (4,5).
  - **No EC grammar:** ⁷Be, ¹¹C and ⁸B are refused.
- **These ARE the NSEQ18 construction outputs P0 needs.** The residual map can now be computed from `CASCADE_ASSESSMENT_2026-10-11.md` / `nseq_cascade_1_results.txt` (250 nuclides; native and {p,n} lists).

## 3. Next round (registered order)
1. P0 residual map from the cascade outputs (computed; no fit).
2. **Before P1:** the sequencer defects (contraction sign; untraced H1 sizes) are either repaired by proposal or carried as named systematics. A value law fitted on a construction with wrong-sign steps would inherit them.
3. P1 with a light calibration set and a **sealed** hold-out, with no count regression.

## Prohibitions
- No census over candidate predictors.
- Grammar counts are not evidence (NP24).
- No data substitution without a label.
- Release is read, never edited (proposals only).
- The word "charge" is not used.

---

## Previous specification (kept as written)

# NP41 — Many-contact energy, emission and reverse response (child C2 of SDT_Loading_EC_Reseating_Neutrino_Coupling)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC, opened 2026-10-05. Id and placement proposed. Gateways binding; direct execution only.
> **Parent:** Phase 4. **Depends on:** NP40 (accessibility definition) and the NSEQ18 construction.

## ⓪ Five questions
1. **What don't we know?** A value law for contact energy that reproduces binding energies without a calibrated coefficient, and how a contact graph with nodes of degree greater than three (212 of 217 nuclides, 1072 nodes) is to be read as a loading path.
2. **Why does it matter?** The continuation's construction gives about 37–41% of stored binding energies (He-4: 11.69 MeV vs 28.296; U-238: 672.6 vs 1801.69). Without a value law there is no energy line-item for an emission or reseating event.
3. **How will we find out?** P0 records the NSEQ18 residual structure as a function of (Z, N, degree); P1 tests candidate value laws on the light calibration set (H-2, H-3, He-3: CALIBRATED(8–9) in NSEQ17) and holds out He-4 and heavier; P2 states the port interpretation or retires it; P3 evaluates energy and momentum closure for an emission only if P1 passes.
4. **What would prove us wrong?** (a) A candidate value law reproduces He-4 binding by more than 5% only after a parameter is fitted to He-4; (b) binding R² over the whole range with the null model of NP24 (R²(BE/A) = −12.2 for shadow overlap) is not improved; (c) energy residual of the closed-domain emission test exceeds 1e-6 or does not decrease under refinement.
5. **How will we know we're done?** Prompt completion A–D; physics class OPEN is acceptable; any fitted parameter is CALIBRATED and listed.

## 1. Executive summary
Question: can the contact graph carry a value law without calibration, and does it support an emission with closed energy and momentum accounting? Closes the Phase 4 gap of the parent. Expected outcome: a residual map and either a candidate law with a hold-out result or a record that none exists yet.

## 2. Physical context
NSEQ16 passes R0–R9 on light nuclei; NSEQ17 meshes H-2, H-3, He-3 with calibrated binding and moments; NSEQ18 builds 221 of 221 isotopes, with four validator failures on canonical tokens and "value law pending". NP17 records the deuteron at 2.200 vs 2.224 MeV and alpha and heavy magnitudes as PENDING. NP33 gives the traction law with derived, constructed and owed items marked.

## 3. Theoretical framework
No inserted binding energies (forbidden adjustment: measured binding-energy substitution). Contact degree is a graph property; the three-port reading is an interpretation to be tested, not assumed. NP24's shared-input rule applies to any count-based rule.

## 4. Investigation strategy
- **P0 residual map:** NSEQ18 binding vs AME2020 per nuclide; residual fraction against degree, A, magic proximity; denominator = all built nuclides.
- **P1 value-law candidates:** each registered with its parameter count before any comparison; fit only on the light set; hold-out He-4 up to a sealed heavier subset (list sealed before access).
- **P2 ports:** compute, per nuclide, the number of nodes above degree three and test whether a three-port rule (merging or sharing contacts) is geometrically admissible; otherwise retire it.
- **P3 emission:** closed-domain energy and momentum accounting for one removal event, with the 23.85 MeV per 2d → α line item and 6.26 MeV per t → d + n from NP25 flagged as literature-memory values to verify.

## 5. Success criteria
Residual map complete; candidate laws registered before use; hold-out evaluated once.

## 6. Outputs
`RUN_LOG.md`, `NP41_ASSESSMENT.md`, residual tables, tool source.

## 7. Dependencies
| Row | Item | Recorded status |
|---|---|---|
| U30 | NSEQ16 | contact construction candidate |
| U31 | NSEQ17 | CALIBRATED(8–9) |
| U32 | NSEQ18 | construction pass; value law pending |
| U22 | NP17 | deuteron resolved; heavy pending |
| U26, U27 | NP30, NP33 | unadjudicated; D/C/O per item |
| U28 | NP35 | flay gates recorded (G1 excluded, G3 pass) |
| D41 | NSEQ17 counter-circulation coefficient | CALIBRATED(1) |

## 8. Falsification tests
Triggers in ⓪.4.

## 9. Implementation notes
The NSEQ18 validator reproduces its own four failures; any run redirects its result writes to a scratch path so source results are not overwritten.

## ⑩ Adaptive execution
**Pre-run commitment:** completion target B; physics class hoped CONVERGENCE; CALIBRATED budget: existing items only; forbidden: refitting NSEQ17, pruning edges, substituting measured binding energies, editing the hold-out after access.
| Trigger | First response | If pivot fails | Forbidden |
|---|---|---|---|
| value law needs a fitted parameter on He-4 | register it as CALIBRATED(1), re-test on a sealed set | OPEN | present as derived |
| ports retire | assess which contact classes violate the reading; alternative interpretation as a new dated round | OPEN | merge contacts to fit three |
| closure residual > 1e-6 | refine twice, check unit consistency | record non-closure | loosen the gate |
Failures get an in-depth assessment and a dated next round.

---

## Audit correction 2026-10-05 (gating)

**Finding:** Round 2 regressed binding on contact-kind counts although the contact count already equals A, so the regression could only reproduce B ∝ A (it did, at 3.2%) and its per-kind energies did not generalise.

**Correction:** Do not use count regressions as a value law and test per-edge coupling values instead (done in round 3).

**Status:** ANNOTATED — label, status or tally corrected in the record; no re-score of earlier runs.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
