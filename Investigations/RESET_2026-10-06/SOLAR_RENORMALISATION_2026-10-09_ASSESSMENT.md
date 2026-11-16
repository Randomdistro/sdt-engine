# Renormalising the Sun: assessment (2026-10-09)

**Pre-registration.** `SOLAR_RENORMALISATION_2026-10-09_PRE_REGISTRATION.md`. Written before any radius value was loaded. The symmetric-dip pivot of 4.87 µm was computed and recorded there before the Rozelot et al. minimum (6.6 ± 1.9 µm) was seen.

**Instrument.** `solar_renormalisation/solar_renorm_1.cpp`, data `R_lambda_points.csv`. Validations V1–V3 met.
- **Run 1:** the C3 report line carried wrong logic, and the crossing uncertainty (a registered quantity) was missing. Output kept as `solar_renorm_1_results_run1_C3fault.txt`.
- **Run 2:** C3 report fixed and crossing σ added. Nothing else changed. Output in `solar_renorm_1_results.txt`.

**Bet (Harvey):** the real Sun is the 925–975 nm Sun. Three criteria, so a single hit carries the chance of 3 tries.

## Data

10 R(λ) points. Read in the review PDF (arXiv:1609.02710):
- AIA 160.0 nm: 963.04 ± 0.03″
- AIA 170.0 nm: 961.76 ± 0.03″
- HMI 617.3 nm: 959.57 ± 0.02″
- the published full-range fit R = 3.120X² − 23.828X + 1000.100, with X = log₁₀(λ/nm)
- the statement that **677 nm – 742 µm is unmeasured**

Search-result readings, primary tables blocked (A&A and HAL returned 403):
- PICARD SODISM II (ground): 535.7, 607.1, 782.2 and 1025 nm (the 1025 nm σ is not found; 0.19″ assumed)
- ALMA: 230, 212 and 100 GHz

Seismic radius: 695.68 ± 0.03 Mm = **959.200 ± 0.041″** (Schou et al. 1997).

Limb definitions are mixed: transit limb, inflection point, radio half-power. HMI (959.57″) and SODISM (959.78–959.88″) disagree by about 0.3″ in the same band. That is a definition or instrument offset, and it dominates the fit χ².

## Results by criterion

**C1, smallest disc: OPEN.**
- No point lies in 925–975 nm.
- The one series that brackets the band (SODISM II, 782.2 and 1025 nm) differs by −0.044 ± 0.214″.
- Across 535.7–1025 nm that series spreads only 0.099″. It is flat within 2σ, so no minimum can be placed.

**C2, pivot of the bending: REJECTED as registered. The fit is poor.**
- My weighted quadratic in ln λ puts the pivot at **6.87 µm** (2σ: 4.5–10.5 µm). The bet sits −9.4σ away.
- χ²/dof = 112. With σ rescaled by √112, σ(ln λ_p) = 2.2, and the registered rule would then read OPEN (unconstrained).
- The published fit, about 40 points from X-EUV to radio, puts the minimum at **6.59 µm** (quoted 6.6 ± 1.9 µm), with R_min = 954.6″. The bet sits −3.0σ from it.
- The minimum lies inside the unmeasured 677 nm – 742 µm gap. It comes from the curvature of the two measured wings, not from a measurement.

**C3, equals the seismic radius: REJECTED as registered.**
- No measured point lies below R_seis. Every UV and visible point exceeds it by more than 2σ; the ALMA points are uninformative.
- Crossings exist only in the fits:
  - mine: **796.5 nm** (σ(ln) = 0.032; the bet is +5.5σ away) and 59.3 µm
  - published: **402.8 nm** and 107.7 µm
- With χ² rescaling, my 796.5 nm crossing would sit within 0.5σ of the band. But the fit passes R_seis at 796 nm only because it compromises between HMI and SODISM. The measured values at 782 and 1025 nm are 959.88″ and 959.83″, about 0.65″ above R_seis.

**Tally against the bet:** 0 of 3 confirmed as registered (C1 open, C2 rejected, C3 rejected). Under χ² rescaling, C2 goes open and C3 is within 2σ, but only through a fit driven by a definition offset.

## The result that stands out (convergent; not the bet)

Bending that treats the two ~4400 K brightness dips (158 nm UV, ~150 µm far-IR) symmetrically pivots at √(158 nm × 150 µm) = **4.87 µm**. This was registered before any radius was seen.

The minimum of the measured solar-radius spectrum lies at:
- **6.6 ± 1.9 µm** (published fit): −0.91σ from 4.87 µm
- **6.87 µm** (my fit): 2σ range 4.5–10.5 µm, which contains 4.87

So the two dips, on their own, predict where the apparent solar size bottoms out. That is Harvey's "bend them back down to the dips". The prismatic bending is symmetric about the dips, and the dips mark its two edges.

**Provenance and discrimination.**
- Origins are independent: dip positions from brightness-temperature spectra; the radius minimum from limb astrometry.
- Discrimination: the layered account has no stated prediction for where the radius minimum falls.
- **Limitations.**
  - The radius minimum is an extrapolation across an unmeasured gap.
  - The far-IR dip position is itself band-limited ("near 150 µm").
  - A 1σ agreement at ±1.9 µm is a weak constraint.

Recorded as C-011.

## What would decide the bet and the pivot
- **Measured radii inside 677 nm – 742 µm**, and especially at 925–975 nm and 3–10 µm. One instrument, one limb definition.

  Candidate instruments: SODISM-class multi-band imaging extended into the IR; DKIST near-IR imaging (1–5 µm); mid-IR solar imaging. On ALMA's shortest bands, the review notes that ALMA observations were scheduled in cycle 4, but those cover mm wavelengths, not the 3–10 µm region.
- **A resolved far-IR dip position** (E109's open measurement). This sets the pivot to better than ±0.05 in ln λ.

## Grades
- C1: G2
- C2: G1 as registered (G2 with scatter rescaling)
- C3: G1 as registered
- Symmetric-dip pivot against the measured radius minimum: G4 convergent, not yet discriminating, weak
