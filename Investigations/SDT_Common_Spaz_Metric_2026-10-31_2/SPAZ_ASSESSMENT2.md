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

## W10 — the Spaz ladder to the halt of light (added 2026-10-31, pre-registered in PROMPT2.md)

10. **Where the locked values land.**
    - **What runs and what doesn't:** under candidate D every local ratio is locked (α, μ, R_p/ƛ_p, E₁/m_ec², a₀/hop, local c). The only thing that runs is the bath against those locks, kT ∝ N. Each locked energy or length therefore lands at a single depth.
    - **Order of landing:**
      - release, N = 734–1090
      - H Saha half-point, 1380
      - visible band, 1519–2798 (the He I half-point, 2489, falls inside it)
      - He II, 5895
      - Lyman-α peak, 8746
      - kT = E₁, 57,930
      - solar-centre temperature, 5.76×10⁶
      - pair threshold, 8.76×10⁸ (Wien photon) to 2.18×10⁹ (kT)
      - deuteron binding, 9.47×10⁹
      - α binding, 1.20×10¹¹
      - **P = P_eff, 2.48×10¹¹**
      - Wien peak = r_e, 3.77×10¹¹
      - Wien peak = R_p, 1.26×10¹²
      - kT = m_pc², 4.0×10¹²
      - P = P_conv, 3.65×10¹⁵
      - Planck temperature, 5.20×10³¹
      - **halt, 6.58×10³¹**
    - **Light speeds:** the far-frame light speed is 252 m/s at release, 9 μm/s at solar-centre temperature, 4.9 fm/s at P_eff, and 6.9×10⁻⁵⁶ m/s at the halt. Locally it is always c.
11. **P_eff lands inside the nuclear-binding band.** It sits between kT = B_α and Wien peak = r_e. The bath peak there is 4.29 fm, which is 1.52 r_e and 5.1 R_p. It is not a lock with any one length (COMPUTED; the closeness to r_e is noted, not claimed).
12. **The desert.** Between kT = m_pc² (N = 4×10¹²) and the Planck temperature (N = 5×10³¹), nineteen decades contain only one engine value, P_conv. The engine has no locked quantity for that range. Whatever the energised spation matrix did there is not yet written down.
13. **The halt is fixed by the hop, not tuned.** "Wien peak = one hop" puts the halt at T = (2π/x_W) T_Planck = 1.79×10³² K, a definitional identity. That is 10²⁵ times any stellar centre in the table, consistent with "hotter than the centre of a dark star". In the far frame the hop there is ℓ_P/N, below Planck by 32 orders: "lower than Planck" holds in far-frame units and nowhere locally.
14. **Time from the halt is not identifiable.** It is 2.9×10⁹/H₀ with a constant transit speed and 1.5×10⁷²/H₀ with a full-Shapiro transit. The transit rule (open item 2) decides it.

## W11 — transit-rule permutations (pre-registered, a84772a)

15. **The release epoch fixes the cosmic transit, and it is not the solar structure.**
    - Across a ∈ {1, 2}, b ∈ {−1…3} and both halts (20 permutations), only b/a ≈ −1 (continuous window −1.29 to −0.77) releases light at 2750–3120 K.
    - In that window the cosmic hop grows with depth and the cosmic transit speed is nearly constant.
    - "Identical structure" (1,1) releases at 2001 K. Every "+1" variant (1,2), (2,1) and (2,2) releases at 1743–2164 K. All of them fail G4.
16. **The 10⁻⁷⁰ m onset is incompatible with that release.**
    - At the hard-gamma halt (P = P_eff), b = 3.09 gives 10⁻⁷⁰ m. The nearest grid member, (1,3), gives 1.07×10⁻⁶⁹ m, just outside the pre-registered decade, and it releases at 1549 K.
    - Every b that reaches 10⁻⁷⁰ is positive. The release window needs b < 0.
    - Within this family, holding both requires a different ingredient: a release mechanism other than Thomson τ = 1 with Saha, an η other than 6.1×10⁻¹⁰, or a cosmic tick that is not a power of N.
17. **The open items are now ranked:**
    1. Derive the cosmic hop law. It must grow with depth (b ≈ −a) if release is to stand.
    2. Decide whether the onset spacing of about 10⁻⁷⁰ m belongs to the same hop, or to a different structure (for example, the spation centre-to-centre spacing rather than the light hop).

## W12 — α against solar depth (pre-registered, 198fdf5)

18. **The Berkeley Cs data carry a 3σ slope against Earth's solar depth.**
    - k = −3.81 ± 1.32 for all 28 datasets, and −4.07 ± 1.36 for the 24 at N = 125. The size matches what the Cs–Rb gap would need, with the sign reversed: α is higher at aphelion.
    - k = +3.5 is excluded at 5.6σ.
    - **What the slope can mean:**
      - Depth and calendar date are collinear (r = −0.986), so this campaign alone cannot separate a solar-depth coupling from a slow drift over Dec 2016 – Jun 2017.
      - The annual swing can supply at most 0.51 ppb of the 1.17 ppb Cs–Rb gap.
      - Clock bounds on an annual α modulation are about 10⁷ tighter. That leaves a depth effect only if it acts on h/m (recoil, mass) and not on clock frequencies, which SDT's "mass as throughput reorganisation" could, in principle, do.
    - **Status:** COMPUTED, indicated, not attributable.
    - **Tests that separate depth from drift:**
      - a campaign whose dates cross perihelion twice, or run Jul → Dec (depth rising over the run);
      - the LKB Rb per-dataset values with dates (Morel and Yao theses);
      - later Berkeley data;
      - the dates of the electron g−2 runs.
19. **Movement budget and dipole (W12b, post-registration).**
    - Heliocentric orbital speed is an exact linear function of depth for a Kepler orbit (v²/c² = 2z − ϟ/a), so "speed plus depth" refits the same 3σ slope: k = −1.26 ± 0.44 on (v²/c² + z).
    - In the CMB frame the campaign swept 399.5 → 341.1 km/s. α tracks that at k_u = −2.24×10⁻³ ± 0.84×10⁻³ (2.7σ), with α higher at lower CMB-frame speed.
    - Depth, orbital speed and dipole speed all peak within about four weeks of each other, so one Dec–Jun campaign cannot separate them, or separate any of them from instrumental drift.
    - **What would separate them:** a campaign with the opposite time order (Jun → Dec), and the Rb per-dataset values.
    - **Clock constraints:** the clock bounds on boost-dependent α (Lorentz-invariance tests) are PENDING sourcing. They decide whether k_u is already excluded.
20. **Above/below and ahead/behind the Sun (W12c, post-registration).**
    - Earth's offset from the Sun along the galactic pole and along the Sun's CMB motion peaks near March. This shape is nearly orthogonal to depth over the campaign (|r| ≤ 0.18), so it is a genuine separating test.
    - **Result:** no effect, |k_g| < 1.2 ppb/AU at 2σ. The depth/speed slope persists (k_z = −3.7 to −4.0) when either is added.
    - **What the data prefer:** a monotonic Dec → Jun trend (depth, orbital speed, dipole speed, or apparatus drift), not a position-on-the-orbit effect peaking in March.
