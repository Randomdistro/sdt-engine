# Renormalising the Sun, round 2: chase the real figure, no target (pre-registration, 2026-10-10)

**Direction (Harvey, 2026-10-10).** "Chase the real figure, no target."
- The 925–975 nm bet is dropped.
- The apparent radius at each wavelength is a prismatic bending by the Sun's spation gradient, and is to be bent back down to the dips.
- The figure sought is the undistorted solar radius, R_true, and where in wavelength it is seen, λ_true.

**Fixed before any fitting.**

The data are the round-1 table `solar_renormalisation/R_lambda_points.csv` (unchanged).

Dips: UV 158 nm; far-IR 150 µm. Their symmetric pivot is λ_d = √(158 nm × 150 µm) = 4.868 µm.

**Seen before this registration.**
- The round-1 fits: my free-pivot quadratic gives 6.87 µm and 957.59″ at its pivot; the published fit gives 6.59 µm and 954.61″.
- A hand check: a dip-pivot parabola through the 160/170 nm pair would give 940″ at 617 nm, against 959.57″ measured. The UV side therefore rises too steeply near the dip for one parabola.

These are disclosed. The forms below are registered with that knowledge.

**No target.** The seismic radius (959.20″), the IAU nominal (959.22″) and Auwers (959.63″) are printed after the fits as context only. No criterion refers to them.

## Data sets
- **S1 (one event, one method).** SDO 2012 Venus transit: AIA 160, AIA 170 and HMI 617.3 nm. Read in the review PDF.
- **S2 (between the dips, 158 nm ≤ λ ≤ 150 µm).** S1 plus the four PICARD SODISM II points (search readings).
- **S3 (all).** S2 plus the three ALMA points. These lie beyond the far-IR dip.

## Forms
- **F1, symmetric prism pivoted on the dips.** R = R_true + κ·ln²(λ/λ_d), with λ_d = 4.868 µm fixed (derived) and 2 parameters fitted. λ_true = λ_d.
- **F2, free pivot.** R = a + b·x + c·x², with x = ln(λ/1 µm) and 3 parameters fitted. λ_true = exp(−b/2c); R_true is the fitted value there.
- **F3, flat floor between steep edges.** R_true = the weighted mean of the points lying at least a factor 2 inside both dips (316 nm ≤ λ ≤ 75 µm). λ_true is the band those points span (no single wavelength).

**Adequacy.** χ²/dof is reported for each form on each data set. A form with χ²/dof > 10 is reported as **inadequate**: its R_true is listed but flagged, not adopted.

For F3, adequacy is the scatter of the floor points about their mean (χ²/dof). F1 and F2 on S1 have 1 and 0 degrees of freedom; F2 on S1 is exactly determined and is reported as such.

**Statement of the outcome.** All F × S results are listed. The real figure is the R_true of the **lowest-χ²/dof adequate form on the largest data set where it is adequate**, with σ (scaled by √(χ²/dof) when that exceeds 1).

If no form is adequate on S2 or S3, the outcome is **"not determined by these data"** (G2), and the instrument-offset problem (HMI against SODISM, about 0.3″) is named as the cause.

## Instrument
`solar_renormalisation/solar_renorm_2.cpp`.

**Validations:**
- V1: F1 recovers a constructed (R_true, κ).
- V2: F3 weighted mean against a hand case.
- V3: the round-1 V2 pivot recovery, repeated.

Single pass.
