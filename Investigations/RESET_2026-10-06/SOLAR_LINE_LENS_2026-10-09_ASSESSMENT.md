# Solar line lens: edge reading and twin-dip reading — assessment (2026-10-09)

**Pre-registration.** `SOLAR_LINE_LENS_2026-10-09_PRE_REGISTRATION.md`, with one amendment made before the instrument existed (the SHA check moved to the run command).

**Instrument.** `solar_line_lens/solar_line_lens_1.cpp`.
- **Attempt 1:** G0 at V4. I set the tolerance at 1e-9 m/s, below the floating-point cancellation floor (c·ε ≈ 7e-8 m/s). Output kept as `solar_line_lens_1_results_attempt1_G0.txt`.
- **Attempt 2:** V4 tolerance set to 1e-6 m/s, nothing else changed. All validations met. Output in `solar_line_lens_1_results.txt`.

**Data.** HARPS-LFC table A1, 188 Fe lines, 477.9–582.8 nm, raw core shifts. SHA-256 matches the manifest. No convective or 3D correction is used, per Harvey's direction.

## Route E — edge reading
**E1 (registered).** Spearman ρ(EW, v) = **+0.874**, p ≈ 1e-132.
- The shift rises with line strength across the whole sample: weak lines near 185 m/s, the strongest decile near 583 m/s.
- E-R1 met. The ordering the lens reading requires is present.
- **Discrimination:** none. The convective account predicts the same sign.

**E2 (registered).** The strongest 10% (19 lines, EW ≥ 14.3 pm) give **608.5 ± 13.0 m/s**.

**E3 (registered).** The log-linear fit extrapolated to EW_max gives 811.3 ± 2.8 m/s.
- E-R2 is **not met**: E2 − E3 = −203 ± 13 m/s.
- χ²/dof = 50, so the log-linear form is the wrong shape at the strong end.
- **Edge not determined: G2.**

**E-R3 (registered).** The edge value 608.5 ± 13.0 sits below all four handlings: −2.38σ (subtract), −2.14σ (none), −1.89σ (add), −1.65σ (double).
- Two handlings fall within 2σ, so the data do not choose: **G2**.
- Separating adjacent handlings at 2σ would need σ ≈ 0.8 m/s on the edge value.

**Descriptive, post-run (not a registered test; selection seen after the run).**

Binned in eighths of EW, the shift climbs 185 → 211 → 269 → 329 → 354 → 412 → 464 → 583 m/s and does not level off inside the sample. The ten strongest lines (EW 20–52 pm) lie at 558–705 m/s, mean 641 m/s.

The two strongest (526.95 nm, EW 52.1 pm, 705 ± 15; 492.05 nm, EW 47.9 pm, 698 ± 15) **exceed the full predicted shift by 60–70 m/s**. In Harvey's reading this is the shape of a crossing:
- lines formed below the edge are under-shifted;
- lines formed beyond it are over-shifted;
- the edge is where v(EW) passes the true value (somewhere in EW ≈ 20–40 pm in this sample).

This is recorded as a lead for the next round, not as a finding.

## Route T — twin-dip reading
**T1 (registered).** The handlings differ by 3.17 m/s, which is 1.06e-8 in z. That moves 158 nm by 1.7e-6 nm and 150 µm by 1.6e-3 nm. **The dips cannot choose a handling** (stated before the run).

**T2 (registered).** With one stretch for all lines (c·z₀ = 334.6 m/s), the residual stretch has a wavelength slope of +7.0e-10 ± 0.6e-10 per nm (p ≈ 1e-27). With line strength held, the slope is −9.4e-10 ± 0.6e-10 per nm (p ≈ 3e-47). Criterion met as registered.

Limitation: χ²/dof ≈ 50 means the per-line errors understate the scatter by about 7×. With the errors rescaled, the two slopes stand at about 1.5σ and 2σ. And the sign flips once strength is held, so wavelength and strength are entangled in this sample. **Status: a wavelength-dependent stretch is not established from these lines.** The 105 nm span is too short to carry anything to 158 nm or 150 µm.

**T3 (registered).** T_UV − T_FIR = +60 ± 265 K (+0.23σ): **consistent**, at the resolution of the 1969 far-IR record (±260 K). The two values are as quoted in E109 §2 and have not yet been checked against Samain 1975 and Eddy et al. 1969.

## What this means for Harvey's question
- **Which handling of the 3.16 m/s is correct?** Not decided. The line edge sits 21–31 m/s below all four, and the twin dips have no leverage on it.
- **What the lines do show:** strength-ordered bending of about 520 m/s across the sample (185 → 705 m/s). No convective model was used. The strongest cores overshoot the full shift.
- **Discriminating step, open (no data loaded):** strong chromospheric lines, whose cores form at and beyond the ~4400 K minimum, to see whether the overshoot continues. Candidates: Na D, the Mg b triplet, the Ca II IR triplet, Hα, Ca II H&K. The registered quantities would be:
  - whether v(EW) crosses the predicted shift at one place (the edge);
  - whether lines beyond it are over-shifted by an amount that mirrors the under-shift below it.

  A source with per-line absolute shifts of strong lines is needed (IAG solar FTS atlas, Reiners et al. 2016; not in `Datasets/`).

## Grades
- E1: G4 for the ordering; not discriminating.
- Edge (E-R2): G2.
- Handling (E-R3): G2.
- T1: no power, by construction.
- T2: G2 (not established after the scatter is accounted for).
- T3: consistent at ±265 K, inputs unverified.
