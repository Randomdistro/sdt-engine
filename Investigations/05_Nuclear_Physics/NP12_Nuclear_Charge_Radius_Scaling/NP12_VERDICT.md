# NP12 — VERDICT: Nuclear Charge Radius Scaling

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-03.
> Tool: `np12_radius_scaling.py` (exit 0) → `np12_results.txt` (redirected stdout).
> Data: `charge_radii_iaea.csv` — **real download** (IAEA `www-nds.iaea.org/radii/charge_radii.csv`,
> Angeli & Marinova 2013 compilation), N = 908 isotopes after the committed filter.
> ⟦"RMS charge radius"⟧ is the instrument label for the data column; SDT-side lengths are boundary radii.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **A** | Every success criterion met: 908 ≥ 250 isotopes, formal metrics for all models, 3 chain tests, decisive verdict, loss quantified. |
| **Physics class** | **KILLED** (canon Z-linear law) **· CONVERGENCE/DEGENERATE** (native recovery) | R = Z·R_p is dead by 179× against real data; the corrected native form (close-packed A^(1/3)) fits at 5.0% but is indistinguishable from the rival's fair form. |

## Numbers (all models committed in RUN_LOG before metrics were computed)

| Model | RMS rel. | R² | Verdict |
|---|---|---|---|
| M1 Z·R_p (SDT canon, `nuclear::nuclear_charge_radius`) | **890.8%** | −3281.6 | **KILLED** (committed rule: >3× best → killed; actual 179×) |
| M2 1.2·A^(1/3) (PROMPT's rival as written) | 25.6% | −1.46 | FAILS too — pre-declared unit mismatch (sharp-surface vs RMS, ~×1.29) |
| M3 0.9295·A^(1/3) (fair rival) | 5.00% | 0.960 | fits |
| M4a 0.7207·A^(1/3) (SDT close-pack, uniform-charge limit) | 25.1% | −1.12 | FAILS (bracket lower limit) |
| M4b 0.9304·A^(1/3) (SDT close-pack, surface-charge limit) | **4.96%** | 0.961 | fits — **pre-declared DEGENERATE with M3 (0.09% apart)** |
| M5 1.2708·Z^(1/3) (fitted, CALIBRATED(1), diagnostic) | 3.85% | 0.984 | best overall, but 1 fitted param |

**Chains (Phase C, committed gates <2% / >5%):** Ca 1.67% (< 2%: Z-constancy holds — and
A^(1/3) *predicts 8.63%* for the same range: the rival over-predicts chain growth 5×);
Sn 3.20% and Pb 3.28% (intermediate; A^(1/3) predicts 6.92% / 5.55% — again ~2× too much).
**Phase D:** magic-Z residuals (3.10%) = non-magic (3.10%): the A^(1/3) family is blind to
shell structure. **Phase E:** R/Z drifts monotonically 24× (1.593 fm at Z=1 → 0.067 at Z=82)
— R/Z is not remotely constant.

## The finding, honestly stated

1. **The canon law is dead.** `R = Z·R_p` (laws.hpp `nuclear::`) survives only at Z=2–3 and
   fails by an order of magnitude at high Z. **Canon impact — propose-and-wait, NOT edited:**
   `nuclear::nuclear_charge_radius(Z)` and its "R_nuc ≈ Z × R_p" comment need Harvey's
   decision. The He-4 anchor (`R_He_predicted = 2R_p`, +0.44%) is a *different* claim
   (boundary contact of 2 units at A=4) and is NOT killed by this run.
2. **The corrected native premise fits — but degenerately.** Close-packing A spheres of
   radius R_p at η = π/√18 gives R_cl = 0.9304·A^(1/3): 4.96% RMS over 908 isotopes with
   ZERO fitted parameters — numerically identical (0.09%) to the rival's fair form
   0.9295·A^(1/3). Pre-declared: this dataset cannot distinguish them; the SDT content is the
   provenance of the coefficient ({R_p, π/√18}, no fit), not a better curve.
3. **The bracket landed on its shell limit.** Uniform-charge (M4a) fails at 25%; the data sit
   on the surface-charge limit (M4b). Per the committed bracket rule this is
   **bracket-consistency, not a PASS** — the periphery-charge strength is un-derived.
4. **Both extreme scalings lose to the data's actual behaviour.** Chains are ~2–5× flatter
   than A^(1/3) predicts (neutrons move ⟦R_ch⟧ far less than their volume share), yet not
   flat (Sn, Pb > 2%). The fitted Z^(1/3) diagnostic (3.85%) points the same way: charge
   extent is driven by proton count in 3D — directionally SDT-friendly, but its coefficient
   is fitted here, so it proves nothing yet.

## §D Seven questions (HUNTER_PROTOCOL, on the M1 KILL)

1. **Why exactly?** Wrong exponent: linear Z vs cube-root growth; R/Z drifts 24× monotonically. Not a coefficient problem — a dimensionality problem.
2. **Recoverable?** Yes — and the recovery was committed pre-run (M4): radii add in *volume*, not diameter.
3. **What did the target fail to account for?** Nucleons pack in 3D (SDT's OWN NP17 picture: interleaved trefoils, alphas at icosahedral interstices). The linear law contradicts the framework's own packing model.
4. **Which premise erred?** "Each proton contributes R_p to the radius" — 1D additive-diameter stacking.
5. **What freedom corrects it?** R_cl = R_p·(A/η)^(1/3), η = π/√18 — a derived close-packing form, zero fit.
6. **Native or knob?** Native ({R_p, π/√18} both prior); the residual non-native piece is the charge-distribution limit (surface vs uniform) — direction argued (p-p repulsion pushes charge out), magnitude un-derived.
7. **Cascades?** Largely independent of the binding-magnitude root (NP17-lock, NP19/21); the debt it creates is a **canon correction** (`nuclear::` Z-scaling) plus the un-derived periphery-charge profile. Links to NP17's per-isotope geometry import.

**Recovery grade: PARTIAL** (premise error corrected with a zero-fit native form that fits;
degeneracy with the fair rival and the un-derived shell-limit keep it from RECOVERED).

## Stress-test self-audit

1. **Independence:** the data never enter any model; R_p is muonic-H (prior); η is geometry. M5's k is fitted and labelled CALIBRATED(1), used only as a diagnostic.
2. **Fished factors:** all six model forms pre-committed; the M4a/M4b bracket rule enforced (no post-hoc pick); the KILL rule was fixed before metrics existed.
3. **Dimensions:** fm throughout; √(3/5) conversions between sharp and RMS radii applied explicitly and symmetrically to rival and native forms.
4. **Data honesty:** real IAEA download (958 lines), provenance + date logged; no value hand-typed.

---

> **Prompt completion A · Physics class KILLED (canon Z·R_p) / CONVERGENCE-DEGENERATE (native close-pack recovery) · Recovery PARTIAL · Cascade root: canon `nuclear::` Z-linear premise (1D stacking vs 3D packing) — canon fix owed to Harvey, propose-and-wait**

*NP12 · executed 2026-07-03 · the decisive test was run and SDT's stated law lost; the corrected native form ties the fair rival with zero parameters.*
