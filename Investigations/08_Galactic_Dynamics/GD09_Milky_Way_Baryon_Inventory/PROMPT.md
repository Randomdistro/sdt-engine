# GD09 — Milky Way Baryon Inventory

Pre-registration, 2026-10-14. Written before the tool exists and before any count is computed.

## Object

A record of the baryon count of each general portion of the Milky Way that observations know or
suspect, with the observed mass behind each count, its stated uncertainty, its source, and its
standing (known / estimated / suspected). Companion to GD08 (geometry); the two share component
names. This is a record, not a test of SDT: no SDT claim is made from it.

## Count definition

N_b(component) = (M_component / M_Sun) × N_Sun, with N_Sun = `bridge::N_baryons(bridge::koppa_Sun)`
from `laws.hpp` (the engine's census: ϟ_Sun / ϟ_per_baryon). M_Sun in kilograms is not used in
any count. Masses are carried in solar masses as the sources give them; the conversion factor is
the engine's, and it is the only place SDT enters.

Uncertainty: each row carries (low, central, high) from the source's stated range. Intervals are
carried, not sampled. Where a source gives ±, low/high = central ∓ stated uncertainty. Where a
source gives a range, central = midpoint.

Labels: source masses OBSERVED (with the estimation chain named); counts COMPUTED. Zero fitted
parameters.

## Inputs (read from the papers in this session)

Bland-Hawthorn & Gerhard 2016 (ARA&A 54, 529; arXiv:1602.07702), unless stated.

| row | M / M☉ | stated | standing |
|---|---|---|---|
| Sgr A* black hole | 4.2 ± 0.2 ×10⁶ | stellar orbits | KNOWN dynamical mass; baryon content not observed |
| Nuclear star cluster | 1.8 ± 0.3 ×10⁷ | Sérsic model, M/L₄.₅ | ESTIMATED |
| Nuclear stellar disc | 1.4 ± 0.6 ×10⁹ | Launhardt+2002 | ESTIMATED |
| Bulge region, stellar | 1.4–1.7 ×10¹⁰ | Portail+2015, VVV box ±2.2×±1.4×±1.2 kpc, includes inner-disc stars | ESTIMATED |
| Bulge region, dynamical | 1.84 ± 0.07 ×10¹⁰ | same box; 10–25% dark matter | reference only, not a baryon count |
| Long bar, thin | 6–8 ×10⁹ | Wegg+2015, RCG + Kroupa IMF | ESTIMATED; part of the disc mass (BH&G §6.4.4) |
| Long bar, super-thin | 3.3 ×10⁹ | same | ESTIMATED; part of the disc mass |
| Thin disc, stellar | 3.5 ± 1 ×10¹⁰ | §5.1.3 | ESTIMATED |
| Thick disc, stellar | 6 ± 3 ×10⁹ | §5.2.2 | ESTIMATED |
| Stellar halo | 4–7 ×10⁸ | §6.1.2; substructure 2–3 ×10⁸ within it | ESTIMATED |
| Total stellar | 5 ± 1 ×10¹⁰ | §6.4.4 | ESTIMATED |
| Cold gas HI (2–19 kpc) | 4.9 ± 2.2 ×10⁹ | Kubryk+2015 Table A.1 compilation; range 2.75–7.7 | ESTIMATED (secondary compilation) |
| Cold gas H₂ (2–19 kpc) | 0.9 ± 0.35 ×10⁹ | same; Miville-Deschênes+2017 abstract 1.2 ×10⁹ | ESTIMATED (secondary compilation) |
| Cold gas incl. He, disc >2 kpc | 8.1 ± 4.5 ×10⁹ | Kubryk+2015 Table 1 | ESTIMATED |
| Cold gas, bulge <2 kpc | 1.1 ± 0.8 ×10⁹ | Kubryk+2015 Table 1 | ESTIMATED |
| Hot corona within r_vir | 2.5 ± 1 ×10¹⁰ | Tepper-García+2015; Miller & Bregman ~1 ×10¹⁰ within 250 kpc | SUSPECTED (model-dependent X-ray/UV inference) |
| Stars + cold gas | 6.3 ± 0.5 ×10¹⁰ | BH&G §6.2 (dynamical models) | ESTIMATED |
| Total baryonic incl. corona | 8.8 ± 1.2 ×10¹⁰ (text); 8.5 ± 1.3 ×10¹⁰ (sidebar) | BH&G §6.2 | SUSPECTED; the source states both values |

Excluded, with reason: dark matter (not a baryon observation); dust (carried inside the gas masses
by the sources); stellar remnants (inside the stellar masses to the extent each source includes
them; not separately listed because BH&G does not give a separate count).

## Bookkeeping rules

- Each row is tagged `additive` or `nested`. Nested rows (nuclear rows inside the bulge region;
  long bar inside the disc; stellar halo substructure inside the halo; every total) are listed
  but never summed with their parent.
- The additive stellar partition is: bulge region + thin disc + thick disc + stellar halo.
- Masses are reported at the R0 each source adopted (8.2–8.3 kpc). They are not rescaled.

## Instrument validation (before use)

- V1. N_Sun from the engine census against M_Sun,nominal/m_p with M_Sun,nominal = 1.98841×10³⁰ kg:
  agree within 1% (reference only; both routes printed, neither feeds a count).
- V2. Round trip N → M → N reproduces the input to 1e-12.
- V3. Every row satisfies low ≤ central ≤ high after conversion.
- V4. Long-bar sum (thin + super-thin) lies in BH&G's stated "≈ 10¹⁰" to within a factor 1.2.

## Comparison (single pass, one criterion)

Additive stellar partition against the source's total stellar mass 5 ± 1 ×10¹⁰ M☉: criterion
|Σ − M*| ≤ 1σ_combined, with σ_combined the quadrature sum of the row uncertainties (range
half-widths taken as 1σ) and the total's ±1×10¹⁰. This is an arithmetic consistency check of
the source's own bookkeeping, not independent evidence.

## Scope

A record of what is observed and inferred. No comparison with a rotation-curve count, no
interpretation of any residual, and no statement about dark matter is made here; a rotation-curve
census (N = ϟ/ϟ_b from v²R/c²) would be a separate, separately pre-registered step.

---

## Addendum 1 — baryon allotment per object (pre-registered 2026-10-16, before the tool exists)

Operator ruling: the spiral arms are objects; the disc is not an acceptable catch-all. Rule adopted: every baryon
is assigned to a named object, or reported as **unallocated** with its own count and share. No smooth "disc"
component carries an allotment. Counts that sit inside another object's total are tagged nested and never summed
with it.

Objects and sources (all OBSERVED inputs, read from the papers in this session):
- Sgr A*: 4.2 ± 0.2 ×10⁶ M☉ (BH&G 2016, R₀ = 8.2 kpc, GD09 row) and 4.28 ± 0.10 ± 0.21 ×10⁶ M☉ (Gillessen+2017,
  R₀ = 8.32 kpc). Mass-equivalent baryon count, baryon content not observed.
- S stars: Gillessen+2017 determined orbits for 40 stars (32 with randomly oriented thermal-eccentricity orbits, the
  S stars, plus 8 clockwise-disc stars). Habibi+2017 Table 2 gives evolutionary masses for eight S stars (S1 12.4, S2 13.6,
  S4 12.2, S6 9.2, S7 8.4, S8 13.2, S9 8.2, S12 7.6 M☉; stated range 8–14 M☉). Masses of the other stars are not
  measured and are not assigned; an upper bound at 14 M☉ each is reported separately.
- NSC (1.8 ± 0.3 ×10⁷ M☉), NSD (1.4 ± 0.6 ×10⁹), bulge region stellar (1.4–1.7 ×10¹⁰) with bulge gas
  (1.1 ± 0.8 ×10⁹), long bar thin (6–8 ×10⁹) and super-thin (3.3 ×10⁹): GD09 rows and sources unchanged.
  The bar is part of the disc mass (BH&G §6.4.4): nested in the thin-disc total.
- Arms: GD08 ridges (Reid 2019), measured and near-extended tiers (flags 1 and 0); Gaussian cross-section σ_in(R).
  The far-side continued tier is unmeasured and carries no baryons.

Arm allotment rule. Observation gives no baryon count per arm. The only baryon surface-density information is the
GD09 radial profiles (thin R_t 2.6 kpc, gas scale 5.2 kpc over 2–19 kpc) and the K-band arm/interarm contrast 1.32
(Drimmel & Spergel 2001, via a review), with counts conserved. For each arm the tool reports:
 (a) baryons inside the ±1σ_in footprint and inside the ±2σ_in footprint (every thin-disc and gas baryon located
     there; thick-disc stars are not arm members and are excluded);
 (b) the excess due to the overdensity (the (K−1) part);
 (c) ridge length, baryons per kpc of ridge.
Each grid cell is assigned to one arm (the one with the largest Gaussian weight), so footprints never double count.
Both footprints are reported; neither is chosen. The thin-plus-gas baryons outside every footprint are reported as
**unallocated (not assigned to any observed object)**, with count and share.

Validation (before use): V1 the surface-density grid integrates to N (thin, gas, thick) within 1e-3; V2 with the arm
overdensity and renormalisation the thin and gas totals are conserved within 1e-6; V3 two routes for the per-arm
footprint counts, analytic grid against a 10⁶-particle Monte-Carlo cloud, agree within 3% for every arm with ≥ 10⁻³ of
the total.

No tuning: footprints, contrast and profiles are fixed above; results are reported as computed.

### Addendum 1, amendment (2026-10-16; additions, no rule or input changed)

After the first run two reported items were added, both informational: (i) a variant in which only measured-azimuth
ridge nodes (flag 1) define the arms, run beside the registered measured + near-extended definition and reported
with it, neither chosen; (ii) a row from an independent luminosity route, Drimmel & Spergel (2001), COBE/DIRBE K band:
the spiral-arm component is 7% of the disc K luminosity as modelled and 10% if the arm model is completed over
three quarters of the Galaxy, applied to the stellar disc (thin + thick) baryons with equal mass-to-light. Arms are
younger, so their mass fraction is at most their luminosity fraction: an upper bound. No tuning toward it.
Tully–Fisher was considered and not used (velocity premise; whole-galaxy relation; fitted constants).
