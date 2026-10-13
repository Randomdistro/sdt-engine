# CH04 — VERDICT: Molecular Geometry (VSEPR) from Wake Balance

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Tool: `ch04_wake_geometry.py` (exit 1 — honest) · Output: `results.txt`

## Results (gates committed in RUN_LOG.md before the run; every angle is minimiser OUTPUT)

| Phase | Result | Call |
|---|---|---|
| P1 equal wakes | 180.000 / 120.000 / 109.471 / TBP{90,120,180} / 90.000 — all exact | **PASS** |
| P2 ladder, ONE ratio | **w_L/w_B = 1.24** (CALIBRATED(1)) → NH₃ **106.79°** (−0.21), H₂O **104.58°** (+0.08); CH₄ 109.47 ratio-free | **PASS ≤1°** |
| P3 same ratio | SF₄ seesaw ✓ (lone equatorial); ClF₃ T-shape ✓ (bonds 85.6/171.2 vs measured 87.5); CO₂ 180.00 ✓; H₂CO opening ORDER ✓ (magnitudes off: HCH 101.6 vs 116.5); **XeF₄ ✗** (lones settle at 94.6°, not trans → not square planar) | partial |
| P4 novel, same ratio | H₂S predicted 104.58 vs **92.1** (+12.5°); PH₃ 106.79 vs **93.5** (+13.3°) | **FAIL — fit-only trigger fires, as pre-registered** |

Earned: the whole symmetric ladder and the 104.5/107/109.5 compression fall out of ONE pairwise 1/|Δu| minimisation with a single declared knob — no hybridisation, no target angles input. The model's honesty edge is equally clear: it carries **no central-atom dependence**, so it cannot tell S from O — and says so by missing H₂S by +12.5°.

## FAILURE RECOVERY (§D seven questions)

**P4 (H₂S +12.5°, PH₃ +13.3°) and P3-XeF₄ — answered together (shared premise).**
1. Why: the model's only inputs are weights and count; H₂S/PH₃ predict identically to H₂O/NH₃ by construction. XeF₄: at 6 seats with w=1.24 the minimiser prefers cis lones (94.6°) over trans; measured structure is trans/square-planar.
2. Recoverable: yes — the missing physics is per-element and per-coordination, not per-molecule tuning.
3. Unaccounted: where on the central form's rim each wake actually engages. Third-row centres bond near 90° (H₂S 92.1, PH₃ 93.5) as if their bond wakes barely repel — i.e. engagement windows, not full-sphere point charges.
4. Errored premise (named): **wakes collapsed to weighted points on a unit sphere.** FARMER frame: contact is a **limited poloidal-rim window — angle is the premium**. A rim-window kernel is element-sized (APS01 k-factor radial scale) and coordination-nonlinear — exactly the two dependencies this run lacks. XeF₄'s cis/trans miss is the same omission at high coordination (window allocation, not chord distance, decides trans).
5. Freedom: the angular-window kernel (window width per element from the poloidal rim geometry; FLM07 glancing-transfer locus).
6. Accounting: native — NP10's angular-window allocation and APS01 k-factors pre-exist this investigation; no knob was added here (the committed single ratio was NOT refit on P4).
7. Cascade: yes — same root FARMER logged for the NP10 coordination lock (×1/×2/×6.35 as angular-window allocation). CH04's misses are that root expressed at Å scale.

**Recovery grade: PARTIAL** — premise and native freedom named; the rim-window kernel is not yet built. Re-open condition: NP10/FLM07 angular-window law lands → re-run P3-XeF₄ and P4 with the derived window widths. Per §G.3 nothing is foreclosed: "one ratio cannot do H₂S" holds only in the point-wake class.

## Cascade root (reported)

**ROOT-RIM (= NP10/FLM07 angular-window root):** CH04-P4 (H₂S, PH₃), CH04-P3 (XeF₄ trans), and the H₂CO magnitude gap. Same root as NP10's coordination lock and FARMER refinement 2.

## Canonical line

**Prompt completion C (P1+P2 earned with CALIBRATED(1); P3 partial; P4 fired the committed fit-only trigger) · Physics class CONVERGENCE (the minimiser survives the delete-test as classical repulsion; SDT supplies the reading, not yet the element dependence) · Recovery PARTIAL · Cascade root ROOT-RIM**
