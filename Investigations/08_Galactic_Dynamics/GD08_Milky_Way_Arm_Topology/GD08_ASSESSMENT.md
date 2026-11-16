# GD08 — Assessment (2026-10-14)

Pre-registration: `PROMPT.md`. Tool: `gd08_mw_arm_topology.cpp`. Output capture: `run_output.txt`.
Products: `milky_way_arm_topology.html` (viewer; open in a browser, internet needed for three.js),
`mw_arms_data.js` (viewer data), `mw_arm_topology.obj` (1σ arm surfaces, kpc, true vertical scale).

## Instrument validation
V1–V4 consistent (largest deviation 5.8e-11). Validation completed before the comparison.

## Comparison (single pass)
Q4 tangency longitudes computed from the published pitch angles and kink radii, against Reid 2019
Table 2: 3-kpc(N) +0.06°, Norma +0.17°, Sct-Cen +0.19°, Sgr-Car +0.28° (criterion ±3°).
Rejection criterion met for 0 of 4. The tabulated values come from the fit with a longitude prior;
the model values come from the centre-line parameters alone, so the agreement is between two
routes to the same arm, not a restatement of one number.

## Geometry (COMPUTED from OBSERVED parameters; 0 fitted)
Measured ridge length / extended length (kpc): 3-kpc(N) 0.19/0 · Norma 3.68/8.58 · Sct-Cen 8.26/13.76 ·
Sgr-Car 10.19/23.52 · Local 6.10/0 · Perseus 21.62/30.27 · Outer 18.03/35.43.
In-plane 1σ at R_kink 0.14–0.65 kpc; vertical rms 20 pc inside 7 kpc, 61 pc at 8.15, 200 pc at 12,
344 pc at 16. The disc is about 0.1–0.7 kpc thick across about 30 kpc.
Width-law residuals against 336 + 36(R − 8.15) pc: −63 pc (Norma) to +167 pc (Outer).

## Scope and limitations
- Segments are separate arcs. Reid's Fig. 10 joins them with unpublished adjustments; no join is asserted.
- Extension beyond the measured azimuth range follows each segment's own pitch angle, ±90°, R in
  3–16 kpc. Sgr-Car beyond β = 97° has ψ> = 1.0°, so its extension is nearly circular; that is the
  fitted value outside the data range, not a measurement.
- Warp is not modelled (Reid's heights are warp-removed rms).
- Bar is an axis only (Wegg+2015 half-length 5.0 kpc, 28–33°); in-plane bar width is not given in the
  source abstract and is not drawn.
- The viewer was rendered headless (Edge, SwiftShader) for top, oblique and edge-on views; interactive
  controls (drag, pan, pinch) were not exercised.
- Not read here: `GD02/gd02_spiral_arms.cpp` arm table, labelled Reid+2019, does not match Table 2
  (e.g. Perseus r_ref 9.9 vs R_kink 8.87; a separate "Outer" with r_ref 13.0). Its consumers
  should be re-checked before they are cited.

## Addendum 1 results — context bodies (2026-10-14)

Pre-registered in `PROMPT.md` Addendum 1 before the tool was changed.

Validation: V5 ellipsoid mesh volume −0.18% against 4/3 π a b c; V6 face-on axis ratio 1/2.1 = 0.476
inside the quoted 0.5 ± 0.05; V7 slab volume −0.02% against π R² h. All consistent within the 1% tolerance.

Bodies (OBSERVED ratios from Bland-Hawthorn & Gerhard 2016; ellipsoid axes COMPUTED from them):
- b/p bulge ellipsoid a, b, c = 2.000, 0.952, 0.520 kpc, major axis 27° from the Sun–centre line,
  near end at positive longitude, volume 4.15 kpc³. The X-shape (maximum at 1.5 kpc) is not modelled.
- Thin disc R_t 2.6 kpc, z_t 0.30 kpc; thick disc R_T 2.0 kpc, z_T 0.90 kpc; slabs at ±1 scale
  height drawn to R = 15 kpc. The edge is a drawing limit; the source gives exponential profiles.
- Bar remains an axis (half-length 5.0 kpc, 28–33°). In-plane bar width depends on the parametric
  model form in Wegg+2015 Eq. 9 and Table 1 and was not taken from the text.

Rendered headless (top, oblique, edge-on ×5). OBJ now also contains `bulge_bp`, `thin_disc_1h`, `thick_disc_1h`.

## Addendum 2 results — far-side continuation (2026-10-15)

Pre-registered in `PROMPT.md` Addendum 2 before the tool was changed.

Validation: V8 samples contiguous in azimuth with every step inside the arc bound (worst step
0.74 of the bound); V9 all 2292 continued samples have R in 3.53–15.99 kpc and σ_in > 0
(minimum 0.125 kpc). Consistent. The tangency comparison is unchanged (0 of 4 rejected).

Lengths along the ridge, measured / extended / continued (kpc): Norma 3.7/8.6/13.2 ·
Sct-Cen 8.3/13.8/32.5 · Sgr-Car 10.2/23.5/34.4 · Perseus 21.6/30.3/23.2 · Outer 18.0/35.4/63.8.
3-kpc(N) and Local are not continued.

Scope: the continued tier is the model's own spiral carried past the data, not a measurement. It
does not assert where the arms are on the far side, that segments connect, or that any arm closes.
The far side has no maser parallaxes; Reid's Fig. 10 joins segments with unpublished adjustments
that are not applied here. Segments with ψ near 0 on the continued side (Sgr-Car, Norma) continue
as near-circles because that is their fitted pitch. Continued sections reach R = 16 kpc, past the
15 kpc drawing limit of the disc slabs. The viewer has a separate "Far side" toggle and draws the
tier fainter than the extended tier.
