# APS09 run log

## 2026-10-03 — pre-registration (before the instrument existed)

Validation V1–V4, Round 1 (linear term, level structure) and Round 2 (degeneracy lifting,
quadratic term) are in `PROMPT.md`, section "Pre-registration (2026-10-03)". One error in the
first draft (level spacing written as "3 e a₀ F n", correct value (3/2) n e a₀ F) was corrected
in place before any code was written.

## 2026-10-03 — run 1

MSVC build. V1–V4 passed (V3: secular dL/dt from the full dynamics within 0.06% of
−(3/2)nF (ẑ × A); V4: so(4) brackets to 1e-10).
- V5 (secular invariants, not pre-registered) failed at its first gate, 1e-10 for L²+A² after
  10⁶ steps (measured 1.9e-10, accumulated rounding). The gate was re-set from the resolution
  needed: 2% of the smallest quadratic shift, about 2e-7, so invariants to 1e-8. The integrator
  had already been changed from RK4 to an exact-rotation splitting for the same reason.
- Rounds 1 and 2 met their registered gates (details in `APS09_ASSESSMENT.md`).

## 2026-10-03 — Round 3 registered after Rounds 1 and 2

Reason and design in `PROMPT.md`, "Round 3". Added validation V6 (adiabatic switching on a
first-order case with a known answer).
- V6 first failed (ratio −6111). The test orbit had ε ∥ z and L ⟂ z (m = 0), which is a
  collision orbit under the field: its eccentricity oscillates up to 1. Test design fault, not a
  fault of the switching method. Replaced by an orbit with L_z ≠ 0; V6 then agrees to 0.47%
  (−1.2788e-4 against −1.2728e-4).
- Round 3 first run: θ = 0° gave −0.500002 F² with exact F² scaling; θ = 60° and 90° were not
  adiabatically continuable (shifts did not scale as F²; the 90° run reached a plunge). The
  registered orientation average could not be formed; the registered rejection criterion was not
  evaluable as designed. Output kept as `aps09_results_run1_round3_superseded.txt`. The printed
  "orientation average" of 2e7 and the line "rejection criterion MET" in that file are artefacts
  of the plunge and are not results.

## 2026-10-03 — Round 3 redesign and final run

Redesign registered in `PROMPT.md` before the rerun: stable family only (circular, L along the
field), n = 1…4, instability diagnostic, predictions −n⁶/2. The diagnostic's first form
(eccentricity and radius thresholds) passed θ = 60° although its shift did not scale as F²;
the registered F² scaling check was added to the continuability test and the tool rerun.
Final output: `aps09_results.txt`. Conclusions: `APS09_ASSESSMENT.md`.
