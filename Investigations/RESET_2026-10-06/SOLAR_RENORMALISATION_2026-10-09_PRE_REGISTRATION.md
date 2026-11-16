# Renormalising the Sun: where is the undistorted Sun? (pre-registration, 2026-10-09)

## Thesis (Harvey, 2026-10-09)

The Sun's apparent size changes with wavelength. That is a lensing artifact of circular or spherical prismatic action of the spation medium.

- The Sun excludes the medium over a gradient. The medium carries the Sun's ring as an electromagnetic oscillation, one spation to the next, at its pressure depth.
- That gradient produces the many-wavelength Sun.
- "Renormalising" means bending the apparent-size differences back down to the dips.

**Harvey's bet, recorded before any radius data: the real Sun is the 925–975 nm Sun.**

**Independent origin of the band.** The engine already carries about 975 nm as the CR13 release-bath edge (laws.hpp:174; cosmology.hpp:199). That number was derived without solar limb data.

**No target values.** The 3.16 m/s question is set aside.

**Known to me before registration (from memory and repo text, not yet sourced). Each is to be confirmed from a source before use:**
- ALMA mm radii are larger by about 0.5–1% (E109 §4).
- The HMI 617 nm radius is about 959.6″.
- The helioseismic radius is a few hundred km below the photospheric one.
- The standard account puts the deepest continuum (the H⁻ opacity minimum) near 1.6 µm. This is E109's node B, 1.6438 µm.

**Look-elsewhere.** Three criteria are tested (Harvey: "test them all"). The assessment reports the hits out of 3. A single hit carries the corresponding chance.

## Data rules (fixed now)

**What counts as an R(λ) point.** A published measurement of the apparent solar radius at a stated wavelength or band, with:
- an uncertainty;
- the limb definition used (inflection point, half-maximum, or another);
- the source.

All points are reduced to arcsec at 1 AU (1″ = 725.27 km at 1 AU).

**Points by definition.**
- Points with different limb definitions are not mixed in a single minimum test unless the source reports them on one definition.
- Every point is tagged with its definition.
- A homogeneous series (one instrument, one definition, several wavelengths) has precedence for C1.

**Search.** Visible, near-IR, UV, EUV, mm and radio. Every qualifying point found is kept; none is dropped after it is seen.

## C1 — smallest disc

The undistorted Sun is the minimum of R(λ).

- **Confirmed** if, in a homogeneous series that brackets 925–975 nm on both sides, the smallest radius lies in the band. The neighbours on both sides must be larger by more than 2σ.
- **Rejected** if a homogeneous series that brackets the band shows a smaller radius outside it, by more than 2σ.
- **Open** if no series brackets the band, or if the series is flat within 2σ.

**Alternative stated beforehand:** the minimum lies near 1.6 µm (the H⁻ window).

## C2 — pivot between the dips

**Fixed now.** A bending symmetric in ln λ, with both dips bent equally, pivots at:
- **λ_p = √(158 nm × 150 µm) = 4.87 µm**;
- **4.92 µm** with E109's SDT-A far-IR position, 153.3 µm.

This is a computed consequence of symmetric bending. If the bet holds, bending is not symmetric in ln λ.

**General form, fitted (CALIBRATED(3)).** R(λ) = a + b·x + c·x², with x = ln(λ/1 µm), fitted to all qualifying R(λ) points by weighted least squares.
- The pivot is λ_p = exp(−b/2c), with its uncertainty from the fit covariance.
- **Confirmed** if λ_p lies in 925–975 nm within 2σ.
- **Rejected** if λ_p lies outside the band by more than 2σ.
- **Open** if the fit is unconstrained (σ(ln λ_p) > 1).

The fit's χ²/dof is reported. A poor fit means the bending is not this simple form, and that is reported as such.

## C3 — equals the true radius

The real Sun is the wavelength whose apparent radius equals a radius obtained with no limb image: the helioseismic f-mode radius. Transit radii are limb measurements at their filter wavelength, so they are R(λ) points, not the reference.

- The crossing wavelength λ_x is where R(λ) passes R_seis. It is found by interpolation in the C2 fit and, separately, between bracketing measured points.
- **Confirmed** if λ_x lies in 925–975 nm within 2σ.
- **Rejected** if R(λ) at every wavelength exceeds R_seis by more than 2σ (no crossing), or if λ_x lies outside the band by more than 2σ.

## Instrument

`solar_renormalisation/solar_renorm_1.cpp`. Data enter as a table in `solar_renormalisation/R_lambda_points.csv`, each row with its source.

**Validations:**
- V1: unit conversion; 959.63″ ↔ 696,000 km at 1 AU.
- V2: the quadratic fit recovers a constructed pivot.
- V3: the crossing finder on a constructed curve.

Single pass.
