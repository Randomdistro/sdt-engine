# CQ18i — Zone-of-Avoidance / Milky-Way Bulge Lensing Residual Test

## Purpose

CQ18i is not a Great Attractor existence test.

It tests whether redshift / peculiar-velocity residuals contain a geometrically organised error field correlated with:

1. Zone-of-Avoidance survey incompleteness and extinction bias.
2. Milky-Way bulge / disk foreground structure.
3. Possible lens-like residual geometry across the Galactic bulge cap.
4. Null-surface behaviour perpendicular to the nominal Great Attractor vector.

The target is not to prove SDT. The target is to find out whether the residual field is random, catalogue-biased, or geometrically structured.

If no stable geometry survives catalogue masks, dust maps, bootstrap uncertainty, and shuffled nulls, the hypothesis is excised.

---

## Core Question

After standard kinematic corrections and H0-rescaling controls, do residuals show a smooth, mirror-testable geometric pattern around the Milky Way disk and bulge rather than a purely GA-directed dipole?

In SDT language, this asks whether the local foreground medium introduces a path-dependent residual consistent with an isotropic throughput mechanism being locally disturbed by high-density Galactic structure.

In orthodox language, this is a foreground/systematics audit for redshift and peculiar-velocity catalogues.

Both descriptions are acceptable. The data decides.

---

## Required Public Datasets

### Primary velocity catalogues

1. **Cosmicflows-4**
   - Use for broad all-sky/grouped peculiar-velocity structure.
   - Required fields: Galactic longitude, Galactic latitude, CMB-frame velocity/redshift, distance, peculiar velocity or distance modulus.

2. **6dFGSv / 6dFGS peculiar velocity catalogue**
   - Use as an independent Southern-hemisphere control.
   - Required fields: RA, Dec, cz, distance-ratio/log-distance, peculiar velocity estimate if provided.

### Foreground/systematic maps

3. **SFD or Planck/Meisner-Finkbeiner dust reddening map**
   - Required field per object: E(B-V) sampled at the source coordinate.
   - Used to test whether any residual geometry is merely dust/extinction selection.

4. **2MASS / 2MRS / ZoA redshift coverage**
   - Used to model catalogue completeness and sky-selection holes near |b| < 10°.

---

## Null Hypotheses

### N0 — Random residual field
Residuals have no stable dependence on Galactic latitude, Galactic longitude, bulge angle, dust column, or GA-perpendicular ring position once survey masks and distance uncertainties are included.

### N1 — Ordinary foreground/systematic bias only
Residuals correlate with E(B-V), source density, or survey completeness but vanish after those controls.

### N2 — Kinematic GA dipole only
Residuals are dominated by the projection onto the GA / bulk-flow vector and vanish on the 90° ring.

### N3 — Structured Galactic foreground lens field
Residuals retain smooth, mirror-testable geometry around the Galactic plane/bulge after N1 and N2 controls.

CQ18i only survives if N3 beats N0, N1, and N2 under bootstrap and shuffled-null testing.

---

## Geometry Features

For each source with Galactic coordinates `(l, b)`:

- `abs_b = |b|`
- `zoa_kernel = exp(-|b| / b0)`
- `ga_cos = dot(unit(l,b), unit(l_GA,b_GA))`
- `ga_ring = |angle_to_GA - 90°|`
- `bulge_north = gaussian angular kernel around (l=0°, b=+b_bulge)`
- `bulge_south = gaussian angular kernel around (l=0°, b=-b_bulge)`
- `bulge_sym = bulge_north + bulge_south`
- `bulge_asym = bulge_north - bulge_south`
- `dust = E(B-V)` if available

The important discriminator is not a single coefficient. It is whether a coherent residual field remains after dust, survey mask, distance, and kinematic projection controls.

---

## Minimum Tests

### T1 — Latitude residual profile
Bin residuals by `|b|`. A ZoA foreground effect should show a monotonic or smoothly decaying dependence on Galactic latitude.

Kill condition: no stable latitude dependence after bootstrap and dust/completeness controls.

### T2 — North/south mirror test
Compare residuals at `+b` and `-b` for matched longitude and distance shells.

Kill condition: asymmetry is dominated by catalogue coverage or dust uncertainty.

### T3 — GA-perpendicular ring null test
At `angle_to_GA = 90° ± Δ`, the first-order GA kinematic projection is zero. Any coherent residual on this ring is not a simple GA dipole.

Kill condition: ring signal disappears under H0 rescaling or shuffled longitudes.

### T4 — Bulge-cap lens kernel
Fit residuals against north/south bulge kernels and compare against dust-only and GA-only models.

Kill condition: bulge terms do not improve AIC/BIC/cross-validation relative to dust + kinematic controls.

### T5 — Distance-shell coherence
Repeat all tests in distance/velocity shells. A local Galactic foreground should weaken or stabilise with distance differently than a true external attractor flow.

Kill condition: signal flips chaotically across shells or only appears in one cherry-picked shell.

---

## Outputs

The executable should produce:

```text
count_total
count_used
bin(|b|): mean residual, sigma, N
ring90: mean residual, quadrupole amplitude, N
regression coefficients:
  intercept
  distance
  ga_cos
  zoa_kernel
  bulge_sym
  bulge_asym
  dust
bootstrap confidence intervals
null-shuffle p-values
kill/survive decision
```

---

## Interpretation Discipline

Passing CQ18i does not prove SDT.

It only says:

> The residual field contains a foreground-linked geometric structure that is not exhausted by ordinary GA dipole, dust, or survey-mask terms.

That would justify deeper modelling.

Failing CQ18i means the ZoA/bulge-lensing pathway is excised from the active SDT investigation tree.
