# CH07 — VERDICT: Molecular Spectra (Vibration & Rotation)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Tool: `ch07_spectra.cpp` (exit 1 — honest) · Output: `results.txt`

## Results (gates and the P1 prediction registered in RUN_LOG.md before the run)

| Phase | Result | Call |
|---|---|---|
| ℏ entry audit | two ASSERTED quantisation rules located and flagged: the rotational ladder step (wake-winding quantiser, PPT06/APS04) and the line-position bridge E=ℏω. ℏ itself is whitelist; the RULES are the owed pieces | flagged |
| P1 native k | shared-seat minimisation: **g\* = −4.19615 at x\* = 0.2887** (H₂⁺ gives exactly −3 at the midpoint — the same machinery as NP17's deuteron factor 3). Well is E = g\*αℏc/R, scale-free → **d²E/dR² = −4.75×10³ N/m at Re: NON-restoring.** No vibrational stiffness exists in this class — registered prediction confirmed | **OPEN** (prompt's 10% gate honestly failed) |
| P2 isotopologues | k back-solved (DECLARED circular for the parent ν — caps at C) then mass-only transfers, zero new inputs: **DCl −0.002%, D₂ −0.070%, ¹³CO +0.001%** (gates <0.5%) | **PASS** — the isotope-transfer premise (k = charge geometry, mass-blind) survives |
| P3 rotation | B(CO) 1.9314 vs 1.93128; B(HCl) 10.5926 vs 10.5934 — **DECLARED IDENTITY** (measured R is spectroscopic in origin; ladder step asserted) | IDENTITY, earns nothing |
| P4 novel | **B(DCl) = 5.4490 vs 5.4488 (+0.004%)**, mass-only, zero new inputs | **PASS** |
| P3-unification | one quantiser for all channels: not demonstrable here | **OPEN** (owner PPT06/APS04; live door FLM14) |

Earned: (a) the honest structural theorem of the run — **the NP17 shared-seat well, which binds, cannot vibrate**: pure 1/R geometry has no interior minimum, so the IR stretch is direct evidence of the short-range wall; (b) the mass-only isotope block (0.001–0.07%), which tests a real native premise (the well is charge geometry, so isotope substitution moves only μ) rather than re-exposing an input.

## FAILURE RECOVERY (§D seven questions — P1)

1. Why: E = g\*αℏc/R gives d²E/dR² = 2g\*αℏc/R³ < 0 for all R (g\* < 0). Sign, not precision: no stiffness anywhere.
2. Recoverable: yes — an interior minimum requires a second, opposing length-scale term; the moment one exists, k follows from the same machinery.
3. Unaccounted: the short-range wall — what stops R shrinking. (Measured k(H₂) = 575 N/m is the size of the missing term's curvature.)
4. Errored premise (named): **point sources valid to contact** — same false premise CH02 met (+9% overshoot, MgO) and NP17 met (alpha under-bind). Occlusion saturates at contact (two-regime law, g→2); saturation both stops the collapse and bends the well.
5. Freedom: the contact-saturation profile (its onset radius and shape).
6. Accounting: native — NP10's saturated solid-angle ledger; measured lock scaling ×1.01/×1.98/×6.35 already brackets its coordination behaviour. Not a knob invented here; nothing was tuned.
7. Cascade: **yes — the sharpest expression of ROOT-CONTACT in the cluster.** One closure owes: NP17-alpha, CH02's overshoot/MgO, CH05's missing three-centre cost (rim sibling), and CH07's k. Pay it once, four debts clear — and the registered cross-check is strong: the derived wall must simultaneously give k(H₂) ≈ 575 N/m AND the NaCl +9.4% correction AND the alpha lock ×6.35.
**Recovery grade: PARTIAL** — premise and native freedom named, magnitude underived. Re-open condition: NP10 saturation law lands → recompute k here directly. Per §G.3: "the well cannot vibrate" holds in the point-source class only; nothing is foreclosed.

## Cascade root (reported)

**ROOT-CONTACT (NP10 saturated occlusion):** CH07-P1 = its cleanest single-number target (k_H₂ = 575 N/m). **OPEN-QUANTISER:** winding rule for ladders (PPT06/APS04, FLM14 door) — separate root, shared with atomic rungs.

## Canonical line

**Prompt completion D (P1 honestly OPEN at its committed gate; P2/P4 mass-only block earned; P3 correctly down-labelled IDENTITY) · Physics class OPEN (native k, quantiser) / CONVERGENCE (isotope block) / IDENTITY (rotation) · Recovery PARTIAL · Cascade root ROOT-CONTACT + OPEN-QUANTISER**
