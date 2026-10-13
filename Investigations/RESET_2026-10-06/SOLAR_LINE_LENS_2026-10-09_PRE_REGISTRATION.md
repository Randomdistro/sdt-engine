# Solar line lens: edge reading and twin-dip reading — pre-registration (2026-10-09)

Harvey's direction (2026-10-09), in summary:
- The solar wavelength distortion is to be read as spectroscopic lensing from the inside. We see "the distortion of the distortion".
- Convective-eddy accounts of the line shifts, and of the ~4400 K dips, are excluded.
- "Bend them all down to normal and look at the lines; the closest version between the two dips is the correct one, demarcating the edges."
- Both readings, side by side, by Harvey's choice.

Notation: Ѻ = R/k².

**What was seen before this registration:**
- The first 12 rows of table A1 (shown during the file inspection; shifts 184–595 m/s).
- The CDS column description.
- The E109 text: dip values quoted there, not yet verified.

No statistic was computed on the line data.

## Data
- **Lines.** `Datasets/solar_propagation_2026-08/raw/harps_lfc_tablea1.dat`: 188 lines, SHA-256 `1b662d02…`, CDS J/A+A/643/A146. Used per line:
  - v_core: line-core shift relative to the original laboratory wavelengths (Nave 1994; Nave & Johansson 2013), with its error
  - EW, λ, element, ion, excitation potential, log gf

  Table A2 (the CO5BOLD 3D-convection fit) is excluded by the direction above.
- **Dips (route T only), as quoted in E109 §2 (MEASURED-INPUT, to be verified against the primary sources before the assessment):**
  - UV: 4430 ± 50 K at 158 nm (Samain 1975)
  - far-IR: 4370 ± 260 K at 238–312 µm (Eddy, Léna & MacQueen 1969)

  The model value of about 4200 K (Avrett) is not a measurement and is excluded.

## Predictions fixed before the data (route E)
Observed shift at Earth, c·z_obs, from the engine's Mercury-route Ѻ☉ = 1476.5989 m, R☉ = 6.957×10⁸ m:
- the surface term c·Ѻ☉/R☉ = 636.30 m/s
- the observer terms 2.96 m/s (Sun, at 1 AU) and 0.21 m/s (Earth), so Δ = 3.17 m/s

| handling of Δ | predicted c·z_obs (m/s) |
|---|---|
| subtract | 639.47 |
| none | 636.30 |
| add | 633.13 |
| double | 629.96 |

## Route E — the edge reading
**Premise (stated, not derived).** A line's core forms in a shell whose depth is ordered by line strength: weak lines deep, strong-line cores toward the ~4400 K minimum. In the lens reading, the deeper the shell, the more the line is bent, toward smaller shifts. Bending vanishes at the edge, the temperature-minimum shell. Line strength is EW. The ordering is an empirical proxy, not a radiative-transfer model.

**Quantities.**
- **E1.** Spearman ρ(EW, v_core) over all lines.
- **E2 (edge value).** Mean v_core of the strongest 10% of lines by EW (n = 19 of 188), with σ = sd/√n.
- **E3 (second route, for the same edge).** A weighted linear fit v = a + b·log₁₀EW (weights 1/e_v²), evaluated at the largest EW in the table. σ from the fit covariance.

**Criteria.**
- **E-R1 (direction).** The lens reading requires ρ > 0 with p < 0.01. **Rejected (G1)** if ρ ≤ 0 or p ≥ 0.01.
- **E-R2 (edge reached).** E2 and E3 must agree within their combined 2σ. If not, the edge is not determined (G2).
- **E-R3 (which handling).** Report the handling closest to the E2 value, and every handling within 2σ of it.
  - **Rejected (G1):** the edge value lies more than 2σ from all four predictions.
  - If two or more handlings lie within 2σ, the data do not choose (G2), and the σ needed to choose is reported.

**Not done.** No convective, granulation or 3D-model correction. No per-line weighting other than e_v. No trimming of lines.

## Route T — the twin-dip reading
- **T1 (power, computed before the data).** The z difference between the handlings, carried to the dip wavelengths. This is reported as a statement of discrimination. **Expected:** none.
- **T2 (lines' own stretch, "bend them all down to normal").**
  - One multiplicative stretch for all lines: z₀ = weighted mean of v_core/c.
  - The residual per-line stretch is s_i = v_i/c − z₀.
  - Test for wavelength dependence: weighted fit s = s₀ + s₁·(λ − λ̄); report s₁ and its significance.
  - **Confirmed (dispersion present in the lines)** if s₁ ≠ 0 at p < 0.01.
  - **Otherwise G2:** the lines carry no wavelength-dependent stretch to transport to the dips, and lines in the UV or IR are needed.
  - Report also the partial dependence: the λ slope after the EW ordering of route E is removed, by fitting both terms together. This separates "wavelength" from "strength".
- **T3 (twin identity).** T_UV − T_FIR from the two measured dips.
  - **Consistent** if within 2σ combined.
  - **Rejected** if outside.

  The resolution of the far-IR record (±260 K) is reported as the limit.

## Instrument
`Investigations/RESET_2026-10-06/solar_line_lens/solar_line_lens_1.cpp` (to be written). It reads the raw file and checks its SHA-256 against the manifest prefix before parsing.

**Validations:**
- V1: the parser reads 188 rows, and the row-1 fields match the displayed line.
- V2: the Spearman routine returns +1, −1 and 0 on constructed known cases.
- V3: the weighted fit recovers a constructed line exactly.
- V4: v_core = c(λ_obs − λ_lab)/λ_lab, recomputed for a constructed case.

Single pass. Every run is kept.

**Amendment (2026-10-09, before the instrument was written).** The SHA-256 check is done by the run command (PowerShell `Get-FileHash`) and printed beside the output, not inside the C++ tool. Nothing else changes.
