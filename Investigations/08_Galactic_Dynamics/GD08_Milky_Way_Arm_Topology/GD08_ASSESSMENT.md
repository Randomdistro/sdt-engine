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
