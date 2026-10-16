# GD09 — Assessment (2026-10-14)

Pre-registration: `PROMPT.md`. Tool: `gd09_baryon_inventory.cpp`. Output capture: `run_output.txt`.
Products: `baryon_inventory.csv` (full table with sources and notes), `mw_baryons.js` (data for the
GD08 viewer's Baryons panel).

## Conversion and validation
N = M/M☉ × N☉, N☉ = `bridge::N_baryons(bridge::koppa_Sun)` = 1.1894×10⁵⁷ (ϟ☉ = 1477.05 m,
ϟ per baryon = 1.2419×10⁻⁵⁴ m). No kilogram value enters a count.
V1 N☉ against M☉,nominal/m_p: +0.048% (reference only). V2 round trip 2×10⁻¹⁶. V3 interval order
holds for all 20 rows. V4 long-bar sum 1.03 × the stated ~10¹⁰. All consistent within the registered tolerances.

## Baryon counts (central; range from the source's stated uncertainty)

| portion | M / M☉ | N | standing |
|---|---|---|---|
| Sgr A* black hole (reference; baryon content not observed) | 4.2×10⁶ | 5.0×10⁶³ | known (dynamical) |
| Nuclear star cluster (nested in bulge region) | 1.8×10⁷ | 2.1×10⁶⁴ | estimated |
| Nuclear stellar disc (nested) | 1.4×10⁹ | 1.7×10⁶⁶ | estimated |
| Bulge region, stellar | 1.4–1.7×10¹⁰ | 1.8×10⁶⁷ (1.7–2.0) | estimated |
| Long bar, thin (nested in the disc) | 6–8×10⁹ | 8.3×10⁶⁶ | estimated |
| Long bar, super-thin (nested in the disc) | 3.3×10⁹ | 3.9×10⁶⁶ | estimated |
| Thin disc, stellar | 3.5±1×10¹⁰ | 4.2×10⁶⁷ (3.0–5.4) | estimated |
| Thick disc, stellar | 6±3×10⁹ | 7.1×10⁶⁶ (3.6–10.7) | estimated |
| Stellar halo (incl. substructure) | 4–7×10⁸ | 6.5×10⁶⁵ (4.8–8.3) | estimated |
| Cold gas incl. helium, disc 2–19 kpc | 8.1±4.5×10⁹ | 9.6×10⁶⁶ (4.3–15) | estimated |
| Cold gas incl. helium, bulge <2 kpc | 1.1±0.8×10⁹ | 1.3×10⁶⁶ | estimated |
| Hot gas corona within r_vir | 2.5±1×10¹⁰ | 3.0×10⁶⁷ (1.8–4.2) | suspected |
| Total stellar (source total) | 5±1×10¹⁰ | 5.9×10⁶⁷ | estimated |
| Stars + cold gas (source total) | 6.3±0.5×10¹⁰ | 7.5×10⁶⁷ | estimated |
| Total baryonic incl. corona (source, text) | 8.8±1.2×10¹⁰ | 1.05×10⁶⁸ | suspected |

## Comparison (single pass)
Additive stellar partition (bulge region + thin disc + thick disc + stellar halo) = 5.7×10¹⁰ M☉,
N = 6.8×10⁶⁷, against the source total 5±1×10¹⁰: difference +7.1×10⁹, σ_combined 1.45×10¹⁰,
|d|/σ = 0.49. Consistent within the registered criterion. This checks the source's own bookkeeping.

## Scope and limitations
- Every mass is an observational inference with a named chain (photometry × IMF, dynamical
  modelling, kinematic gas surveys, X-ray/UV absorption). None is a direct count of baryons.
- The partition may double count inner-disc stars: the bulge-region row includes them and the
  thin-disc row is a whole-disc value. The criterion passes with that possible overlap included.
- The long bar is part of the disc mass (BH&G §6.4.4) and is nested, not added.
- Source disagreement kept visible: the review states the total baryonic mass as 8.8±1.2×10¹⁰ (text)
  and 8.5±1.3×10¹⁰ (sidebar). Both rows are in the table.
- Gas rows come from a secondary compilation (Kubryk et al. 2015, rescaled to R₀ = 8 kpc), not from
  the primary surveys; the HI and H₂ entries cover 2–19 kpc, so HI beyond 19 kpc (the Kalberla &
  Dedes disc extends past 35 kpc) is not counted. HI and H₂ rows are hydrogen only and are nested
  in the helium-inclusive gas row used for the count.
- The corona is suspected: it depends on a spherical β-model, isothermal gas and ionisation
  equilibrium. Miller & Bregman give ~10¹⁰ M☉ within 250 kpc; Tepper-García et al. give
  2.5±1×10¹⁰ within r_vir.
- Masses are at the R₀ each source adopted (8.0–8.3 kpc); none is rescaled here.
- Not counted: dark matter (not a baryon observation), the circumgalactic gas beyond the corona
  estimate, and stellar remnants as a separate row (no separate count in the sources).
- Not done, by design: no comparison with a rotation-curve census (N = ϟ/ϟ_b from v²R/c²), and no
  statement about any residual. That would be a separately pre-registered step, and the dynamical
  total baryonic mass above is itself obtained from fits that use kinematics.

## Addendum 1 results — baryon allotment per object (2026-10-16)

Tool `gd09b_object_allotment.cpp`; captures `run_output_allotment.txt` (measured + near-extended ridge, registered) and
`run_output_allotment_measured.txt` (measured azimuth only); tables `object_allotment.csv`, `object_allotment_measured.csv`.
Rule: every baryon belongs to a named object or is reported unallocated. Validation consistent: surface-density grids
integrate to N (6.5×10⁻⁷, 1.2×10⁻⁴, 4.2×10⁻⁷); thin and gas totals conserved with the overdensity (7×10⁻¹⁴);
per-arm footprints, grid against 10⁶-particle Monte-Carlo, within 1.8% (±2σ) and 2.4% (±1σ).
Galaxy partition total (Sgr A* + bulge region + thick + thin + gas) N = 7.815×10⁶⁷.

| object | N baryons | share | relation |
|---|---|---|---|
| Sgr A* (4.2×10⁶ M☉; 4.28×10⁶ gives 5.09×10⁶³) | 4.995×10⁶³ | 0.0064% | additive, mass-equivalent |
| S stars, eight with measured masses (84.8 M☉) | 1.009×10⁵⁹ | — | nested, NSC region |
| S2 alone (13.6 M☉) | 1.618×10⁵⁸ | — | nested |
| S sample of 40 orbit stars, upper bound 14 M☉ each | 6.34×10⁵⁹ | — | bound; masses of 32 not measured |
| Nuclear star cluster | 2.141×10⁶⁴ | 0.027% | nested in bulge region |
| Nuclear stellar disc | 1.665×10⁶⁶ | 2.13% | nested in bulge region |
| Bulge region (stellar + gas) | 1.974×10⁶⁷ | 25.26% | additive |
| Long bar (thin + super-thin) | 1.225×10⁶⁷ | 15.68% | nested in the thin-disc pool |

S-star masses (Habibi+2017 Table 2, M☉): S1 12.4, S2 13.6, S4 12.2, S6 9.2, S7 8.4, S8 13.2, S9 8.2, S12 7.6. Gillessen+2017:
40 orbit stars, 32 S stars with thermal-eccentricity orbits plus 8 clockwise-disc stars.

Arms (baryons inside the footprint; every thin-disc and gas baryon located there; thick-disc stars excluded):

| arm | ±2σ, registered | ±1σ | excess (K−1) | ±2σ, measured azimuth only | ridge length registered / measured (kpc) |
|---|---|---|---|---|---|
| 3-kpc(N) | 1.68×10⁶⁵ | 5.9×10⁶⁴ | 2.5×10⁶⁴ | 1.73×10⁶⁵ | 0.19 / 0.19 |
| Norma | 1.62×10⁶⁶ | 8.7×10⁶⁵ | 2.7×10⁶⁵ | 5.25×10⁶⁵ | 12.3 / 3.7 |
| Sct-Cen | 3.76×10⁶⁶ | 2.00×10⁶⁶ | 6.3×10⁶⁵ | 1.75×10⁶⁶ | 22.0 / 8.3 |
| Sgr-Car | 3.92×10⁶⁶ | 2.13×10⁶⁶ | 6.6×10⁶⁵ | 1.61×10⁶⁶ | 33.7 / 10.2 |
| Local | 5.51×10⁶⁵ | 2.8×10⁶⁵ | 8.9×10⁶⁴ | 5.68×10⁶⁵ | 6.1 / 6.1 |
| Perseus | 3.07×10⁶⁶ | 1.72×10⁶⁶ | 5.2×10⁶⁵ | 1.66×10⁶⁶ | 51.9 / 21.7 |
| Outer | 3.00×10⁶⁶ | 1.61×10⁶⁶ | 5.0×10⁶⁵ | 1.06×10⁶⁶ | 53.5 / 18.1 |
| all arms | 1.609×10⁶⁷ (20.6%) | 8.67×10⁶⁶ (11.1%) | 2.69×10⁶⁶ (3.4%) | 7.35×10⁶⁶ (9.4%) | |

Measured-azimuth-only totals: ±1σ 3.78×10⁶⁶ (4.8%), excess 1.21×10⁶⁶ (1.5%). The overdensity excess is about 16–17% of each
arm's ±2σ footprint. Unallocated (thin + gas outside every arm footprint, named as such): 3.518×10⁶⁷ (45.0%) outside ±2σ,
4.259×10⁶⁷ (54.5%) outside ±1σ; measured-only 4.391×10⁶⁷ (56.2%) and 4.749×10⁶⁷ (60.8%). Thick disc (not an arm member):
7.136×10⁶⁶ (9.1%).

Independent luminosity route (Drimmel & Spergel 2001, K band): arms are 7% of the disc K luminosity (10% if complete over
3/4 of the Galaxy); on the stellar disc (4.877×10⁶⁷ baryons) with equal M/L that is 3.41×10⁶⁶ to 4.88×10⁶⁶, an upper bound.
The model's stellar (thin-disc) overdensity excess is 2.08×10⁶⁶ (registered) and 9.4×10⁶⁵ (measured only),
0.43–0.61 and 0.19–0.27 of that bound: below it, as required of a lower-mass-to-light object. Nothing was tuned toward it.

Scope and limitations. No observation gives a baryon count per arm; the arm counts follow from the GD08 ridge and σ_in(R), the
GD09 radial profiles and a K-band contrast of 1.32 applied equally to every arm. Stellar tracers indicate unequal arm strength
(Scutum-Centaurus and Perseus strong, Sagittarius and Norma weaker); no per-arm values were retrieved, so none is applied. The
near-extended tier is azimuth beyond Reid's measured range, which is why the two variants differ by a factor of about two.
Arm footprints inside R ≈ 5 kpc (3-kpc, Norma, inner Sct-Cen) overlap the long bar, which is nested in the same thin-disc pool and
has no stated width; the overlap is not separable. Unallocated is the largest single item. Tully–Fisher was not used.
