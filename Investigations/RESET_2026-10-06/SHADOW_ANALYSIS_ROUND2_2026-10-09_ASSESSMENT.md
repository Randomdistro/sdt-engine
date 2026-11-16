# Shadow analysis, round 2 — zk² = 1 from spectra on independent chains (assessment, 2026-10-09)

- **Pre-registration:** `SHADOW_ANALYSIS_ROUND2_2026-10-09_PRE_REGISTRATION.md`.
- **Instrument:** `shadow_analysis/shadow_2.cpp`, output `shadow_2_results.txt`. MSVC, single pass; the validation (the Sun built from its own Ѻ, zk² − 1 = −1×10⁻¹⁶) was met.
- **Notation:** Ѻ = R/k².

## Results

zk² = Ѻ_spec/Ѻ_orbit, where Ѻ_spec = (v_gr/c)·R and Ѻ_orbit = (M_dyn/M☉)·Ѻ☉, with Ѻ☉ = 1476.5989 m. No G enters.

| Star | Redshift source | v_gr (km/s) | zk² | Deviation |
|---|---|---|---|---|
| Sun | González Hernández 2020 (1-AU term removed: one reading examined, not adopted; correction 2026-10-09) | 0.63821 | 1.0030 ± 0.0094 | +0.32σ |
| Sirius B | Greenstein 1971 | 89 ± 16 | 1.103 ± 0.199 | +0.52σ |
| Sirius B | Barstow 2005 | 80.42 ± 4.83 | 0.997 ± 0.062 | −0.05σ |
| Sirius B | Joyce 2018 | 80.65 ± 0.77 | 0.9998 ± 0.0199 | −0.01σ |
| 40 Eri B | Koester & Weidemann 1991 | 26.5 ± 1.5 | 0.951 ± 0.063 | −0.78σ |
| 40 Eri B | Reid 1996 | 25.8 ± 1.4 | 0.926 ± 0.060 | −1.25σ |

All 5 white-dwarf rows are within 2σ: **5 of 5 confirmed**, and with the Sun 6 of 6. Every measurement that satisfied the registered criteria is included; none were selected afterwards.

**Provenance and discrimination.** Two independent chains: a spectral line shift with a flux-and-parallax radius, against a visual-binary orbit in AU and years.
- The relation is **convergent** and could have failed.
- It spans Ѻ from 783 m to 1503 m, and z from 2.1×10⁻⁶ (Sun) to 2.7×10⁻⁴ (Sirius B), a factor of 126 in z.
- It does not discriminate from general relativity: the weak-field relation is the same (the 0.636 km/s form of Joyce et al.'s equation 3).

**Residuals.**
- **40 Eri B:** both measurements sit low, by 5% and 7%. Bond et al. 2017's own radius and mass predict 27.82 ± 0.97 km/s, above both measured values. So the pattern points to the 1991/1996 redshifts, not to the relation, but it is not significant (−0.78σ, −1.25σ).
- **Sirius B:** the HST measurements against laboratory rest wavelengths carry a systematic offset of up to 16 km/s at the E1 position (Joyce et al. 2018 §4.3). Only the 2018 differential measurement is free of it.

**Excluded by the registered criteria.** Procyon B has no measured redshift (no detectable Hα). Stars with astrometric-microlensing masses were not admitted, because the criterion asks for a visual-binary orbit.

**Scope / Limitations.**
- The candidate list came from two searches; a full census of white dwarfs with a dynamical mass and a measured redshift was not made.
- The white-dwarf radii depend on model fluxes at a spectroscopic temperature (atmosphere models), though not on the mass.
- The Sun row depends on the reading of the 3.17 m/s observer term. The data cannot yet choose between subtracted, removed and added (−0.24σ to +0.81σ).

## Sources
- Joyce et al. 2018, MNRAS 479, 1612, arXiv:1809.01240 — read directly; also gives Barstow 2005, Greenstein 1971 and the Bond 2017b mass.
- Bond et al. 2017, arXiv:1709.00478 — via a summarising fetch; gives the 40 Eri B radius, mass, the Koester & Weidemann 1991 and Reid 1996 redshifts, and the prediction.
- Bond et al. 2015, arXiv:1510.00485 — search result; Procyon B.
- González Hernández et al. 2020, A&A 643 A146 — search result.
