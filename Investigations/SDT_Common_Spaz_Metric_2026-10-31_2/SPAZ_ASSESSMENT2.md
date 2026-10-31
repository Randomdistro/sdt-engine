# SPAZ_ASSESSMENT2 — Common Spaz Metric run 2 (direct execution, 2026-10-31)

Author: James Christopher Tyndall, Melbourne. Tables: `SPAZ_TABLES2.md`. Tools: `spaz_*2.cpp`.

## Findings

1. **Pasted electron/hydrogen derivation (W1): excluded.** One step of six reproduces. Each "result" is a known constant (m_ec², a₀, Ry) inserted after steps that do not reach it. The self-energy integral diverges and has the wrong dimension.

2. **Gemini audit (W2): its arithmetic corrections reproduce, but three of its own claims do not.**
   - **Arithmetic:** every correction to the old markdown files reproduces (Earth, Jupiter, Io).
   - **Io "validation":** it is a calibration. β_J equals Jupiter's orbital GM to 3×10⁻⁷.
   - **Projected solid angle:** the projected form is exact at every distance ≥ R. The scalar cap over-states it by 2.000 at contact and by 0.0036 % at Mercury's distance.
   - **13-sphere contacts:** the 30 tangential contacts do not exist; the outer spheres miss each other by 5.15 % of a diameter.
   - **600-cell:** 20 tetrahedra meet at each vertex, not 12.
   - **Symbol rename:** the proposed k → ϟ rename contradicts the engine (k = c/v, ϟ = R/k²).

3. **Precession (W3), COMPUTED.**
   - The engine's Law V response (T10) supplies exactly 1/6 of the observed perihelion advance (0.16663).
   - The remaining 5/6 needs a static term (1 + λϟ/r) with λ_req = 4.990 (pre-registered expectation 5).
   - Exact projection (pure 1/r²) supplies zero. The 5ϟ/r term is therefore the derivation Law III owes.
   - Fitted to Mercury, λ = 4.998 [CALIBRATED(1)] predicts Venus 8.624, Earth 3.839 and Mars 1.351 "/cy. Their measured comparators are PENDING sourcing.
   - **GOM04:** the 0.0009 % c-closure residual is 53× smaller than the 1σ spread from Mercury's δφ. It is unresolved, so it cannot carry a Shapiro/slowdown reading.

4. **Γ_ep (W4).**
   - Γ_ep = 4α(1+z)·R_p/(4ƛ_p).
   - At z_drag it sits 0.10–0.18 % below π³. That is +0.5σ against R_p = 0.8414(19), but +2.4σ (CODATA-2022) and +3.6σ (muonic 0.84087(39)) against the current values.
   - Four trials were made before selection.
   - **Status:** an unexplained coincidence at the 2–4σ level, not a prediction of R_p. The R_p/ƛ_p ≈ 4 relation (4.0008 / 3.998) is the separable piece.

5. **Varying-c models (W5), exact rank.**
   - **Rank:** 8 observables reduce to rank 3 on {c, ħ, m, k_e e²}, leaving a one-parameter family, every member of which is a **pure unit change**: α, a₀/hop and the local c all stay fixed. Particles are "heavier and smaller" only in far-frame units.
   - **Physical widening:** excluded at first order by the solar redshift, given c = hop/tick.
   - **Candidates excluded:**
     - A (the transcript ladder: α ∝ N, no line redshift, half Shapiro, Law V violated past N = 137).
     - A′ (the same with wavelength kept: blueshift).
     - B (α fixed, m ∝ N²: no line redshift). This corrects an intermediate model given in the 2026-10-22 exchange.
   - **Candidate C** passes every local observable but needs the observer at a centre.
   - **Candidate D** (emission depth, c rising with time; James's rule) passes all eight columns.
   - **RUN-1 cross-check:** RUN-1's "c change with α, k_B and the action seat fixed is a pure unit change" agrees. RUN-1's "only m c² fixed survives" is the a = 1 member of this family. RUN-1's a_ħ < −1 condition uses premises not reproduced here.

6. **Release epoch (W6, W6b).**
   - **Ground state:** 13.6057 eV locally at every epoch, and 13.6057/N eV as seen from here.
   - **Equilibrium Saha:** half-ionisation at N = 1380, not 1091. The 53 rule that gave 1093 is a last-scattering rule of thumb, not equilibrium ionisation.
   - **With the Pantheon+-fitted rate law (W6b, post-inspection):**
     - The full-Shapiro transit (q = 2) puts release at N = 734 (T_local 2000 K).
     - A constant transit speed (q = 0) puts it at N = 1063–1066, within 0.2–0.5 % of z_drag + 1.
   - **Status:** the q = 0 agreement is the most striking number in this run. It is not pre-registered: two transit rules were tried against two comparator epochs. It also contradicts D's own transit speed c₀/N² unless the cosmological transit is not the solar Shapiro profile. That tension is now the sharpest open question.

7. **Torus displacement (W7): excluded as constructed.** The fitted tube is 966× the ring radius (a spindle), so the Pappus volume does not apply. The 0.5 % hit on λ_C/3 rests on three free choices.

8. **Neutrino tick test (W8): prediction recorded.** From a proto-neutron-star depth ϟ/R = 0.10–0.25, neutrino energies arrive at 0.90–0.75 of emitted if neutrinos take the tick, and at 1.00 if they do not.

9. **Depth rate law (W9).**
   - **Fit:** Pantheon+ (diagonal errors) fits s = p + q = 0.720 ± 0.030, with Δχ² = +5.1 against flat ΛCDM at equal parameter count. The rate law is not excluded by this test, and not preferred.
   - **Elapsed time:** non-identifiable from distances. It is 19–25/H₀ (q = 0) or about 3–4.5×10⁶/H₀ (q = 2).

## Missing relations (unchanged from RUN-1, sharpened)

- The static 5ϟ/r force term from Law III.
- Whether the cosmological transit speed is c₀/N² (as for the Sun) or constant. W6b makes this decisive: it moves the release epoch from N = 734 to N = 1064.
- The rate law's origin ("opening of directions of freedom") at p = −1.28 or +0.72.
- Measured comparators for the Venus, Earth and Mars advances.

No paper: the mechanism is not closed.
