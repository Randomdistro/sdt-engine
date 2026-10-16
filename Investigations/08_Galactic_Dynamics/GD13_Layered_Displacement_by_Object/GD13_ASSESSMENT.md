# GD13 — Assessment (2026-10-16)

Pre-registration: `PROMPT.md` (reading R1–R7, Amendments 1–5). Tool: `gd13_layered_displacement.cpp`. Registered output (Run B):
`run_output.txt`, `gd13_contacts.csv`, `gd13_ridge_owner.csv`, `mw_layers.js`. Run A (20 kpc half-width): `*_domain20.*`.
Viewer: GD08 `milky_way_arm_topology.html`, Depth maps 6/7 (`#top,,,d6`, `#top,,,d7`).

## Validation
Grid 1281² at 0.0625 kpc, half-width 40 kpc. V1 sphere ψ and S 1.3%; V5 shell shift 0.014%; V2 plate ψ 0.056%, S 0.47%; V3a contact layer 0.19%;
V3b equal-pressure point 2.5%; V4 partition sums to the region cell count exactly. All inside the registered tolerances.

## Results (R < 17 kpc, plane; Run B)
- Objects: 10 (Sgr A*, bulge region, long bar, 3-kpc, Norma, Sct-Cen, Sgr-Car, Local, Perseus, Outer); V_i = N_i V_p; 4.81×10⁶⁷ baryons displace.
- K_end (every plane cell inside 17 kpc reached by some object) = 3.249×10⁴⁹ layers.
- Contact order (first 24 of 45 pairs in the CSV): Sgr A*–bulge–bar at the centre (≤ 9.2×10⁴³); bar–Sct-Cen 1.5×10⁴⁶; bar–Norma 2.5×10⁴⁶;
  Norma–Sct-Cen 2.7×10⁴⁷ (first arm–arm); bar–3-kpc 3.1×10⁴⁷; Perseus–Outer 5.6×10⁴⁷; Sgr-Car–Perseus 6.1×10⁴⁷;
  bulge–Sct-Cen 1.4×10⁴⁸ (at 1.6 kpc); bulge–Norma 1.5×10⁴⁸; bulge–3-kpc 2.9×10⁴⁸. The first arm–arm and arm–bar contacts come 5–60× earlier than the first bulge–arm contact (1.4×10⁴⁸), and 15–1000× earlier than the bulge
  front reaches the ridge nodes (median layers above).
- Ownership at K_end (largest pressure by volume among reaching objects): Sct-Cen 92.2% of the owned area, long bar 4.1%, Norma 3.3%, bulge 0.39%,
  3-kpc 0.08%; Sgr-Car, Local, Perseus, Outer, Sgr A* own none.
- Pre-registered classification, "the spiral arms dominate" (arms' share of owned area, 3 < R < 17 kpc): 0.9728 → supported (≥ 50%).
  The share is carried by one arm; see Limitations.
- Engulfment by the bulge: 0 of 2640 ridge nodes are owned by the bulge or Sgr A* at K_end. The bulge's own front (sphere, k = 4πr³/3W) is at 0.66, 1.43,
  3.09 kpc at k = 10⁴⁷, 10⁴⁸, 10⁴⁹, and reaches arm ridge nodes at median layers 1.5×10⁴⁹ (3-kpc) to 8×10⁵⁰ (Outer inner third), i.e. mostly after K_end.
- Free pressure by volume (pitches) at d = 0.5 / 4 / 8 kpc: bulge 7.2×10⁴ / 1.2×10³ / 2.9×10² (falls as 1/d²); Sct-Cen 1.9×10⁴ / 1.1×10⁴ / 9.0×10³;
  Norma 1.7×10⁴ / 1.0×10⁴ / 6.9×10³; Sgr-Car 6.4×10³ / 4.1×10³ / 3.7×10³; Perseus 1.3×10³ / 1.1×10³ / 1.1×10³. A plate's pressure by volume falls slowly
  with distance; a sphere's falls as 1/d². At d = 8 kpc the Sct-Cen plate carries 31× the bulge's.
- Crossover at K_end: every object except Sct-Cen (0.948) has its whole reached cost crossed by another object (fraction 1.0); the 50% shunt is therefore
  ≈ 0.5 of each object's displaced volume at K_end. Earlier checkpoints (O5b): bulge 0.15 / 0.69 / 1.0 at k = 10⁴⁷ / 10⁴⁸ / 10⁴⁹; whole-object arm crossover is 0–0.02 at 10⁴⁷, 0–0.46 at 10⁴⁸
  (Norma 0.46, Sct-Cen 0.19, 3-kpc 0.82) and 0.70–1.0 at 10⁴⁹.
- Superposition: Σ f_i exceeds the owner's f by a factor 2.54 (mean over 3 < R < 17 kpc).

## What the result says and what it does not
- Plates keep their pressure by volume out to large d; spheres lose it as 1/d². That is the Operator's expectation as a property of the layer surface S(d), and it is
  computed, not assumed (V1, V2 validate S for both shapes).
- The ordering of contacts matches the Operator's picture (arms meet each other and the bar first, the bulge later); engulfment of the arms by the bulge does not
  occur inside K_end in this reading, because the bulge's layer volume (W = 3.6×10¹¹ m³ per layer) grows its sphere slowly compared with the plates' surfaces.

## Limitations and residuals
- Reading R1–R7 is mine. Differing readings (layer = 100× the object volume, plate height fixed at the Reid height 2σ_z, bulge and Sgr A* as spheres, owner = largest f,
  unallocated baryons excluded) would change the numbers; no variant was run.
- Sct-Cen owning 92% is a property of its plate: its f = V/(Sℓ_P) is largest because its ±2σ plate is thin and long relative to its volume. Widening the domain
  (Run A → Run B) left every ownership share unchanged to the quoted digits (the grid-clipping hypothesis of Amendment 5 is not supported for ownership). The
  classification therefore rests on Sct-Cen alone; Sgr-Car, Perseus, Outer own nothing because their f is lower than Sct-Cen's everywhere they reach.
- The end-state read at K_end is a comparison of free pressures at one layer; the 50/50 shunt and the engulfment dynamics beyond contact are reported as crossover
  fractions and shunt volumes, not evolved as a time-stepped redistribution (the layer index is analytic, ~10⁴⁹ layers). O5 saturates (fraction 1.0) at K_end.
- Perseus's f rises between d = 4 and 8 kpc (1.07×10³ → 1.13×10³) at 40 kpc half-width: self-overlap of the offset curve of a tightly wound spiral, not clipping.
- 45% of thin-disc and gas baryons and the thick disc belong to no object and do not displace here (GD09b); the 4.81×10⁶⁷ baryons that do displace are the object counts.
- The grid differencing band is ±0.15 kpc, so an object's own pressure is resolved beyond ≈ 0.15 kpc from its centreline; Sgr A* (volume 10⁻⁴ of the total) owns no cell.
- Process fault: the executable ended abnormally (0xC0000409) in 2 of 3 first runs at Run B and once at Run A, at different points; 12 of 12 later runs (with stdout unbuffered
  and an exception handler that caught nothing) were byte-identical. The cause is not identified. Output is reported from completed runs only.
- Not done: no pressure-to-emission map; no vertical structure (plane only, z-integrated cost); the viewer maps show the plane only.
