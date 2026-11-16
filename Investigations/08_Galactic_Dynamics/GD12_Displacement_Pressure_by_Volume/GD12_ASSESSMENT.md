# GD12 — Assessment (2026-10-16)

Pre-registration: `PROMPT.md` (Amendments 1–3). Tool: `gd12_pressure_by_volume.cpp`. Output capture: `run_output.txt`.
Products: `gd12_ridge_metrics.csv`, `mw_pressure.js` (viewer, Depth → Map states 1 and 2). Nothing was tuned or matched;
no observed value is a target; no velocity, rotation or redshift entered. Labels: inputs OBSERVED (GD08 geometry, GD09
counts); canon quantities from `laws.hpp`; every field COMPUTED; the uniform ambient term uses the BBN baryon ratio η
(shared input, flagged); closure from pressure to emission position PENDING.

## Instrument validation
V1 macro-shell algebra 1.5×10⁻¹³ (k₀ = 10³–10⁵); V2 volume conservation 3×10⁻¹⁶; V3 meeting point exact; V4 mean column
on a uniform ball, softening-corrected −6×10⁻⁴ and +1.9×10⁻³; V5 radial gradient (400-direction mean) −1.1%; V6 column
at the Sun +1.2×10⁻³, at the centre +1.4×10⁻²; V8 ridge f(ray)/f(particle) +3.8×10⁻³; V9 ring-mean derivative +2.2×10⁻³.
All consistent. Three amendments before reporting, all of the instrument: V1/V5 test construction (A1, A2) and the gradient
instrument (A3). Noise: f_local 1.25%; the particle-sum gradient 26% per point (not used for direction tests).

## The measure and the shell table
Pressure by volume f(k) = V/(4π k² ℓ_P³): displaced volume per shell volume, equal to the pitches a shell is shifted;
each shell carries the same V. A 100-shell macro-shell has close side f_c and far side f_f with relative step
200/k₀ + 10⁴/k₀². Exact; the step is below double-precision resolution at every physical depth.

| body | r | k = r/ℓ_P | macro-shells to here | f | relative step |
|---|---|---|---|---|---|
| Earth | 1 m | 6.2×10³⁴ | 6.2×10³² | 3.2×10²⁷ | 3.2×10⁻³³ |
| Earth | R_Earth | 3.9×10⁴¹ | 3.9×10³⁹ | 7.94×10¹³ | 5.1×10⁻⁴⁰ |
| Sun | R_Sun | 4.3×10⁴³ | 4.3×10⁴¹ | 2.22×10¹⁵ | 4.7×10⁻⁴² |
| Sun | 1 AU | 9.3×10⁴⁵ | 9.3×10⁴³ | 4.80×10¹⁰ | 2.2×10⁻⁴⁴ |
| Galaxy | 8.15 kpc | 1.56×10⁵⁵ | 1.56×10⁵³ | 1.11×10³ | 1.3×10⁻⁵³ |
| Galaxy | 15 kpc | 2.86×10⁵⁵ | 2.86×10⁵³ | 329 | 7.0×10⁻⁵⁴ |
| Galaxy | r₁ = 272 kpc | 5.2×10⁵⁶ | 5.2×10⁵⁴ | 1.0 | 3.9×10⁻⁵⁵ |
| Galaxy | R_CMB | 5.9×10⁶¹ | 5.9×10⁵⁹ | 7.8×10⁻¹¹ | 3.4×10⁻⁶⁰ |

Literal enumeration of macro-shells is not possible (1.6×10⁵³ to the Sun from the centre). The closed form is exact for any
grouping of shells, so the macro-shell close side, far side and gradient are exact and no enumeration is needed.
The Galaxy rows treat all baryons as one spherical body at the centre. The field sum f_local at the Sun (2458 below) is larger
than that row (1115 at 8.15 kpc) by design: the unsigned 1/r² kernel does not obey the shell theorem, so matter near the Sun
counts at its own distance and not at the Galactic radius.
Uniform ambient: n_b0 = η n_γ = 0.2505 m⁻³, f_amb = n_b0 V_p N = 2706.5 pitches.

## Earth in the Sun's gradient (computed; nothing compared)
f_Sun at the Earth = 4.80×10¹⁰ pitches, gradient 0.641 per m toward the Sun. f_Earth at its surface = 7.94×10¹³, gradient
2.49×10⁷ per m toward the Earth's centre. f_Earth/f_Sun at the Earth's surface = 1655; |∇f_Sun|/|∇f_Earth| there = 2.6×10⁻⁸.
The meeting surface (f_Earth = f_Sun) on the Sun–Earth line lies 2.59×10⁸ m from the Earth (40.6 R_Earth), shell depth
1.6×10⁴³, pressure there f_Earth + f_Sun = 9.62×10¹⁰. The ambient share at the Earth's surface is 3.4×10⁻¹¹.
Baryon counts: N_Sun from `koppa_Sun`; N_Earth from `koppa_Earth`, which the engine builds from a measured surface speed.

## The Galaxy
Pressure by volume (K = 1.32), pitches:

| | f_local | Sgr A* | bulge | thick | thin | gas | f_total | ambient share |
|---|---|---|---|---|---|---|---|---|
| Sun | 2458 | 0.07 | 301 | 164 | 1490 | 506 | 5165 | 0.52 |
| centre | 78 684 | 5260 | 57 900 | 2110 | 13 100 | 292 | 81 391 | 0.033 |

f_local centre/Sun = 32.0; f_total centre/Sun = 15.8; Sun f_local/f_amb = 0.91. Ring means: f_local = f_amb at R = 7.67 kpc.
The arm overdensity raises f_local at the Sun by 4.7%; the arm excess is 2.9–5.9% of f at the ridge nodes.

**T2, competition.** Sgr A* equals the surrounding matter at r = 8.06 pc (shell depth 1.5×10⁵²). The bulge regime (Sgr A* + bulge)
equals the disc regime (thick + thin + gas) at R = 1.74 kpc in the ring means. At every ridge node of every arm the disc regime
dominates (0% bulge-dominated). In the plane the dominance partition is: bulge inside about 2 kpc, thin disc beyond, gas only
as isolated noise speckles at the grid corners. The meeting surfaces are the equal-f curves between these regimes; the pressure
at a meeting is the sum.

**T1, "pressure is always higher in the direction of the nearest mass"** (696 plane points on a 1 kpc grid, 0.7 < R < 15 kpc,
deterministic gradient): toward the baryon-weighted centroid within 1 kpc, 0.9928 → **holds** (≥ 0.99); toward the Galactic
centre, 1.0000 → **holds**. In-plane |∇f| at the Sun = 430 per kpc, pointing toward the centre.

**T3, "displacement pressure is pushed along the arms"** (measured and near-extended nodes, every third node, deterministic
gradient): ⟨|∇f·t̂|/|∇f|⟩ against the geometric ⟨|r̂·t̂|⟩ of a radial field:

| arm | nodes | gradient | geometric |
|---|---|---|---|
| Norma | 111 | 0.119 | 0.138 |
| Sct-Cen | 164 | 0.223 | 0.225 |
| Sgr-Car | 183 | 0.136 | 0.130 |
| Local | 29 | 0.200 | 0.198 |
| Perseus | 213 | 0.166 | 0.165 |
| Outer | 178 | 0.124 | 0.112 |

All arms 0.157 against 0.155 (difference 0.001) → **not supported**. The pressure gradient meets the arms as a radial field does;
at every sampled ridge node it points toward the Galactic centre (fraction 1.000).
The first pass with the noisy particle-sum gradient (T3 0.538, T1 0.80) is recorded in Amendment 3 and not used.

## Emission at depth: patterns of f_total (closure to spectral position open)
Observer at the Sun, f_total = 5165 pitches. Over the 180 sampled emitters 2–10 kpc from the Sun, f_total(emitter)/f_total(Sun)
spans 0.586 to 14.18 (0.130 to 28.7 without the ambient term). Examples (Δf pitches; ratio): l = 0°, d = 6 kpc +15 379; 3.98 ·
l = 0°, d = 10 kpc +18 863; 4.65 · l = 90°, d = 10 kpc −1642; 0.682 · l = 180°, d = 10 kpc −2133; 0.587 · l = 270°,
d = 10 kpc −1574; 0.695. No amplitude is assigned to a spectral shift: the map from f to the emission position is not supplied.

## Scope and limitations
- The closure from pressure by volume to the spectral position of emission is open; only f and Δf are reported.
- The ambient term uses η from BBN, a shared input; without it the ratios are as stated above.
- The cascade is spherical about each source; the Galaxy field is the superposition of baryon contributions; no force
  direction is asserted from the gradient.
- Halo and corona excluded; bulge and thin-disc counts may double count inner-disc stars (GD09). Gas-dominated grid points
  at the far corners are sampling noise. The viewer's gradient state was removed because the particle-sum gradient is too noisy.
- Not done: any comparison with observation; any equalisation operator beyond the meeting rule f_A = f_B; a time-dependent
  statement (none is made).
