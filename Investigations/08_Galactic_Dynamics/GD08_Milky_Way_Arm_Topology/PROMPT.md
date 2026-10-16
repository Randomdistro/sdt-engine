# GD08 — Milky Way Arm Topology (large-scale structural model)

Pre-registration, 2026-10-14. Written before the tool exists.

## Object

A three-dimensional model of the Milky Way's spiral arms at their measured positions and
measured thicknesses, as a mesh (`.obj`) and a viewer (`.html`). This is the observed-structure
layer. It contains no SDT mechanism and no SDT claim; an SDT overlay (occlusion, depth field)
is a later layer that reads this geometry.

## Inputs (OBSERVED — one source, no fitted values added here)

Reid et al. 2019, ApJ 885, 131 (arXiv:1910.03357), Table 2 and §3, read from the paper text
in this session. Model assumes R0 = 8.15 kpc, Sun at z = +5.5 pc.

- Arm centre line: ln(R/R_kink) = −(β − β_kink) tanψ, ψ = ψ< for β ≤ β_kink, ψ> for β > β_kink.
  β = Galactocentric azimuth, 0 on the Sun–centre line, increasing in the direction of rotation.
  Plan coordinates: x = R sinβ, y = R cosβ; centre (0,0), Sun (0, 8.15).
- In-plane width (Gaussian 1σ, perpendicular to the arm): w(R) = w(R_kink) + 0.042 (R − R_kink) kpc
  (dw/dR = 42 pc/kpc, Reid 2019 §3).
- Vertical width (rms, warp removed): σ_z(R) = 20 + 36 (R − 7.0) pc for R > 7.0 kpc, 20 pc inside.
- Bar (reference only): Wegg, Gerhard & Portail 2015 (abstract): half-length 5.0 ± 0.2 kpc,
  angle to the line of sight 28–33°, thin component ~180 pc thick. In-plane bar width is not
  given in the abstract and is not asserted.

Table 2 rows (R_kink kpc, β_kink°, ψ<°, ψ>°, w_kink kpc, measured β range °):
3-kpc(N) 3.52, 15, −4.2, −4.2, 0.18, 15–18 · Norma 4.46, 18, −1.0, 19.5, 0.14, 5–54 ·
Sct-Cen 4.91, 23, 14.1, 12.1, 0.23, 0–104 · Sgr-Car 6.04, 24, 17.1, 1.0, 0.27, 2–97 ·
Local 8.26, 9, 11.4, 11.4, 0.31, −8–34 · Perseus 8.87, 40, 10.3, 8.7, 0.35, −23–115 ·
Outer 12.24, 18, 3.0, 9.4, 0.65, −16–71.

The repo's earlier arm table (`GD02/gd02_spiral_arms.cpp`, labelled Reid+2019) does not match
Table 2 (e.g. Perseus r_ref 9.9 vs R_kink 8.87; a separate "Outer" with r_ref 13.0). GD08 does
not read it.

## Scope rules

- Measured β range is drawn opaque. Extension beyond it, using the segment's own pitch angle, is
  limited to ±90° and R ∈ [3, 16] kpc, and is drawn distinct and labelled extrapolated.
- 3-kpc(N) and Local are not extended (Reid: bar-associated substructure; isolated segment).
- Segments are not joined to each other. Reid's Fig. 10 applies "small adjustments" to connect
  them; those adjustments are not published as parameters, so no connection is asserted.
- Warp is not modelled (Reid's z values are warp-removed rms).
- Vertical scale is true by default; exaggeration is a display control only.

## Instrument validation (before the model is used)

Run on known answers; a failure here is a validation failure, not a result.

- V1. ψ → 0 gives a circle: R(β) = R_kink to 1e-12.
- V2. Every segment passes through (R_kink, β_kink) exactly.
- V3. Circle case tangency: Q4 longitude extremum of a circle of radius R is 360° − asin(R/R0)
  (R = 3.52 → 334.4°) to 0.01°.
- V4. Pitch continuity: the ridge is continuous at β_kink (no gap) to 1e-12 kpc.

## Comparison (single pass, whole table)

Q4 tangency longitudes computed from the model (Q4 longitude extremum of each segment,
β ∈ [−120°, 0]) against Table 2 column "tangency" for 3-kpc(N), Norma, Sct-Cen, Sgr-Car.
Rejection criterion: any |model − tabulated| > 3° (the tabulated values carry a ±2° prior).
All four are compared in one pass; no mid-range adjustment.

Width-law consistency (information, no threshold): tabulated w(R_kink) against the
global line 336 + 36 (R − 8.15) pc, residual per arm reported.

## Labels

Arm parameters OBSERVED (Reid 2019). Mesh, tangencies, lengths COMPUTED. Zero fitted
parameters in GD08.

---

## Addendum 1 — context components (pre-registered 2026-10-14, before the tool is changed)

The arms are given a body: stellar discs and the central bulge, at sourced sizes. Source:
Bland-Hawthorn & Gerhard 2016, ARA&A 54, 529 (arXiv:1602.07702), §4.2.1, §4.3, §5.1, read from the
paper text in this session; Wegg, Gerhard & Portail 2015 for the long bar.

Inputs (OBSERVED, one source each):
- Thin disc (old stars): radial exponential scale length R_t = 2.6 ± 0.5 kpc; vertical exponential
  scale height z_t ≈ 300 pc (20%). Thick disc: R_T = 2.0 ± 0.2 kpc; z_T = 900 ± 100 pc.
- b/p bulge: major axis at 27 ± 2° from the Sun–centre line, near side at positive longitude;
  face-on axis ratio b/a = 0.5 ± 0.05 (isophotes of 1 : 2.1 reaching ~2 kpc along the major
  axis); edge-on axis ratio c/a = 0.26; central vertical scale height 180 pc; X-shape maximum at
  x_X = 1.5 ± 0.2 kpc.
- Long bar: half-length 5.0 ± 0.2 kpc, angle 28–33°, thin component scale height 180 pc,
  super-thin 45 pc. In-plane width is not stated in the abstract or the review and is not drawn.

Rendering rules:
- Bulge: ellipsoid, semi-major a = 2.0 kpc, b = a/2.1, c = 0.26 a (COMPUTED from the quoted ratios).
  Not the X-shape; the peanut structure is not modelled.
- Discs: translucent slabs at ±1 scale height out to R = 15 kpc. The 15 kpc edge is a drawing limit
  that matches the arm extent; the source gives exponential profiles with no edge, and no
  truncation radius is asserted. Radial scale lengths are marked by rings.
- The bulge and slabs are context bodies; arms remain the object of GD08.

Validation (before use, known answers):
- V5. Ellipsoid mesh volume against 4/3 π a b c, tolerance 1%.
- V6. Face-on axis ratio used (1/2.1 = 0.476) lies inside the quoted 0.5 ± 0.05.
- V7. Slab (cylinder) mesh volume against π R² h, tolerance 1%.

Single pass; no mid-range adjustment. Zero fitted parameters.

---

## Addendum 2 — far-side continuation (pre-registered 2026-10-15, before the tool is changed)

Observation that prompted it: the arms cover only part of the disc. The data are maser parallaxes
seen from the Sun (Reid 2019: parallax distances trace arms over typically < 12 kpc), so the far
side has no measured arm positions.

Rule: each of Norma, Sct-Cen, Sgr-Car, Perseus and Outer is continued along its own fitted
log-spiral (its own ψ< and ψ>, no new parameter) for up to 270° beyond each measured end,
stopping where R leaves [3, 16] kpc. 3-kpc(N) and Local are not continued (as before).
Three tiers, drawn distinctly and toggled separately:
- measured azimuth range (Table 2 column "range");
- extended: up to 90° beyond a measured end (Addendum-0 rule, unchanged);
- continued: beyond 90°, up to 270°. Labelled as unmeasured.

Not asserted: that continued sections are where the arms are; that segments connect to one
another; that any arm closes or wraps. Reid's Fig. 10 joins segments with "small adjustments"
that are not published; none are applied. Segments whose own pitch angle is near zero on the
continued side (Sgr-Car ψ> = 1.0°, Norma ψ< = −1.0°) continue as near-circles; that is the fitted
value, not an observation.

Validation (before use): V8 ridge continuity across tier boundaries (jump < 1e-9 kpc per step
fraction, i.e. no gap); V9 every continued sample has R in [3, 16] kpc and in-plane σ > 0.
Single pass, zero fitted parameters.
