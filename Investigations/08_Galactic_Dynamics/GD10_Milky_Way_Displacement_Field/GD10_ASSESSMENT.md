# GD10 — Assessment (2026-10-16)

Pre-registration: `PROMPT.md` (with Amendment 1). Tool: `gd10_displacement_field.cpp`. Output capture:
`run_output.txt`. Products: `gd10_ridge_profiles.csv` (depth along every arm ridge, every λ, both
conduit sets), `gd10_sightlines.csv` (pair shifts for 180 emitters), `mw_displacement.js` (maps for the
GD08 viewer, Depth → Map). Zero fitted parameters; λ scanned.

## Instrument validation
V1 point baryon −5×10⁻⁵; V2 shell theorem 5.3×10⁻⁴ outside, 9.8×10⁻⁴ inside; V3 uniform disc 4.1×10⁻⁴;
V4 operator identity 0, solver approaches the mean to 6×10⁻⁷ at λ = 10³ kpc, ∫Z ds conserved to 1.2×10⁻¹³;
V5 rotation bridge −1.5×10⁻⁴; V6 composition 1.4×10⁻¹⁶. All consistent. The first run stopped at
validation (V4b conditioning at λ = 10⁶ kpc, V6 coded tolerance); both are recorded in Amendment 1.
Ring finite-difference against the analytic force at R₀: +0.09%. Monte-Carlo noise (two seeds): 0.19% of
Z, 0.29 m/s rms.

## Bulge as recursive shells
| shell | r_edge kpc | N_k | cZ additive m/s | compounding (mult − add)/add |
|---|---|---|---|---|
| 1 | 0.19 | 3.0×10⁶⁵ | 19.0 | 0 (rounding) |
| 2 | 0.38 | 1.3×10⁶⁶ | 51.3 | 2.6×10⁻⁸ |
| 3 | 0.76 | 4.8×10⁶⁶ | 101.7 | 6.7×10⁻⁸ |
| 4 | 1.14 | 5.0×10⁶⁶ | 120.2 | 1.2×10⁻⁷ |
| 5 | 1.53 | 3.7×10⁶⁶ | 119.3 | 1.4×10⁻⁷ |
| 6 | 2.29 | 3.5×10⁶⁶ | 97.8 | 1.3×10⁻⁷ |
| 7 | 3.81 | 1.2×10⁶⁶ | 62.5 | 8.4×10⁻⁸ |

Hand check, shell 1: ϟ₁ = 1.2419×10⁻⁵⁴ m × 2.999×10⁶⁵ = 3.724×10¹¹ m; r = 0.1907 kpc × 3.0857×10¹⁹ m/kpc
= 5.885×10¹⁸ m; Z = 6.33×10⁻⁸; cZ = 2.998×10⁸ × 6.33×10⁻⁸ = 18.97 m/s. Matches the table.
Compounding by multiplicative closure composition is of order Z ≈ 10⁻⁷ relative, 10⁻⁵ m/s absolute. Pressure
compounding P = P_conv(1+Z)⁴ gives ΔP/P = 4Z: 1.7×10⁻⁶ at the Sun, 1.6×10⁻⁶ at the shell maximum,
6.7×10⁻⁶ at the centre (cZ = 498.5 m/s, contrast case).

## C1 — baryon-only rotation bridge at R₀ (single pass)
v_c²/c² = 3.846×10⁻⁷ (v_c = 185.9 km/s) against (Θ₀/c)² = 6.197×10⁻⁷ (Θ₀ = 236 ± 7 km/s, Reid 2019):
ratio 0.621; criterion |ratio − 1| ≤ 0.099. **Inconsistent.** Stellar halo and hot corona are excluded;
a spherical exterior contributes no inward force in the dilute shell theorem. Arm overdensity (K = 1.32)
changes the ratio by +0.03%. The baryon-only value is 79% of Θ₀.

## C2 — the specified mechanism
Ring finite-difference v_c²/c² at R₀ after equalisation (contrast case), ratio to (Θ₀/c)²:
λ = 0.5 → 0.620 · 1 → 0.618 · 2 → 0.620 · 4 → 0.638 · 8 → 0.678 · 16 → 0.713 · ∞ → 0.740.
Every case **inconsistent** with the criterion. The mechanism as encoded (conserving redistribution along
the sheaths plus compounding of order Z) raises the ratio at most to 0.74. The rise above 0.62 comes from
displacement moved between the radii of the two finite-difference rings by arms that cross them; it is an
estimator-dependent quantity (axisymmetric ring means of a non-axisymmetric field).

## C3 — emission-depth gradient at R₀
Baryon-only: c ∂Z/∂R = −14.2 m/s per kpc. With the observed Θ₀ in the same bridge: 22.8 m/s per kpc, which
converges on Loeb (2022, theoretical estimate, standard-physics route) at 0.024 km/s per kpc.

## Emission at depth
- Sun: cZ = 123.4 m/s (no arm contrast), 124.9 m/s (contrast 1.32). Galactic centre: 498.5 m/s.
- Pair shift of an emitter 2–10 kpc from the Sun, depth only, dilute field: −70.6 to +371 m/s. Largest
  toward the centre at 8 kpc (l = 0°: +371 m/s; l = 10°: +239; l = 350°: +231). Most negative: the anticentre at 10 kpc.
- Arm baryon overdensity alone: sheath emitters shift by at most 2.1 m/s (rms 1.1), above the 0.29 m/s noise.
- Equalisation along the sheaths (tiers 0–1, contrast case), shift of cZ for emitters in the sheaths:

| λ kpc | max abs m/s | rms m/s | max up | max down |
|---|---|---|---|---|
| 0.5 | 5.9 | 0.6 | 2.7 | −5.9 |
| 1 | 11.4 | 1.4 | 5.3 | −11.4 |
| 2 | 20.6 | 3.2 | 8.4 | −20.6 |
| 4 | 31.9 | 6.8 | 17.9 | −31.9 |
| 8 | 51.3 | 12.9 | 34.8 | −51.3 |
| 16 | 66.7 | 19.6 | 49.2 | −66.7 |
| ∞ | 75.6 | 26.9 | 57.8 | −75.6 |

  The sign pattern is systematic: segments nearer the bulge lose depth, outer segments gain it. Examples,
  cZ at the inner end → outer end of the measured+extended segment (m/s): Sct-Cen dilute 257 → 124, λ = 8:
  206 → 159, λ = ∞: 182 uniform; Perseus 168 → 69, λ = 8: 146 → 79, λ = ∞: 109; Sgr-Car 167 → 91, λ = 8:
  161 → 117, λ = ∞: 143; Norma 258 → 207, λ = 8: 218 → 215. 3-kpc(N) and Local barely move (short).
- The Sun lies 0.37 kpc from the Local ridge (σ_in 0.32 kpc, taper 0.52), so equalisation also shifts the
  observer's own depth by a few m/s; pair shifts include it.
- Effect of equalisation on the pair shift of the 180 sampled emitters: up to 45 m/s over the λ scan
  (26 m/s at λ = 8: l = 20°, d = 10 kpc, 102.8 → 76.7 m/s).
- Gaia single-star RV zero-point scatter ~300 m/s (HARPS–Gaia wide binaries): per-star detection is out of
  reach; a sample-mean detection needs ~10⁵ stars per bin and removal of arm streaming motions (~10 km/s,
  correlated with arm position), which mimic any along-arm trend.

## Labels
Inputs OBSERVED (Reid 2019; BH&G 2016; Drimmel & Spergel 2001 and Loeb 2022 as cited by secondary
sources; GD09 counts). Z fields, shell tables, pair shifts COMPUTED. H1 (Law II with local depth) and H2
(equalisation operator) are hypotheses, not canon. λ PENDING. DERIVED: none. CALIBRATED: none.

## Scope and limitations
- λ is unconstrained; every equalisation number is a function of λ.
- The sheath taper g = exp(−d²/2σ²) and the nearest-node assignment are modelling choices, not canon.
- The rotation estimator for the equalised field (axisymmetric ring means) is approximate; C2 is
  reported for it as computed.
- Excluded: stellar halo, hot corona, warp, X-shape, bar width. Bulge-region and thin-disc counts may
  double count inner-disc stars (GD09 limitation), which would overstate Z.
- The far-side continued arms (GD08 tier 2) carry no baryon excess; `gd10_ridge_profiles.csv` includes
  them in the conduit-set-B columns only.
- Comparison values entered after the model was fixed. No back-check against the 88-row benchmark ledger
  or CONNECTIONS.md was run in this investigation.
- Not asserted: that arms are channels, that displacement flows along them, or any value of λ.

## What the result excludes and what remains open
Inside the canon's nonlinearity (Depth-closure superposition, multiplicative closure composition,
P ∝ (1+Z)⁴) the Operator's mechanism redistributes displacement by tens of m/s and compounds it by
10⁻⁷ relative. It does not supply the first-order amount (a factor 1/0.621 = 1.61 in v²) that the baryon-only
dilute field lacks at R₀. A first-order amplification has to enter through the coupling law itself: the
GD06 Θ instrument replaces point superposition with the solid-angle integral for extended sources
(thin disc as a band), and the dilute identity z = ϟ/r is the compact-source limit. That is a separate,
pre-registered step (proposed GD11); it is not run here.

## Correction 1 (2026-10-16, Operator ruling)

C1 and C2, the c·Z (m/s) presentation, and H1 are withdrawn (see `PROMPT.md` Correction 1). The
numbers above stay visible as the record of the depth-bridge route; they do not test the Operator's
displacement-cascade mechanism. Successor: GD11.
