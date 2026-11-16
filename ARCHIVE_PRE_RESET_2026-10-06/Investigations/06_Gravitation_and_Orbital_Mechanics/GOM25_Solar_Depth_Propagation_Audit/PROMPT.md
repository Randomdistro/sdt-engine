# GOM25 — Solar Depth and Non-Local Propagation Audit

> **Status:** PRE-REGISTERED — 2026-08-07.  No GOM25 external dataset was
> downloaded or opened before this record.  This is an adversarial audit, not a
> request to preserve the current mechanism.

## 1. Target mechanism and initial conditions

Test the implemented solar chain, without importing a competitor's field
equations:

```text
koppa_Sun = v_orbit^2 r_orbit / c^2
z(r)      = koppa_Sun / r
z_spec    = z(R_Sun) - z(r_observer)
c_far(r) = c (1 - z(r))^2
```

The orbital state, the solar radius, and the surface spectral shift are three
separate observations.  The measured SI value of `c` is a unit definition, not
a fitted parameter.  `G`, solar mass, a precomputed solar koppa, and a
reference-framework timing formula are prohibited as inputs to the GOM25
prediction path.

## 2. Frozen data requests

### D1 — Solar orbital-depth input

Retrieve a JPL Horizons **vector table** for the Earth–Moon barycenter relative
to the Sun, 2025-01-01T00:00:00 through 2026-01-01T00:00:00, step 14 days,
output in km and km/s, CSV enabled.  The instrument will use every valid row,
not a hand-picked epoch, and calculate
`koppa_i = |v_i|^2 |r_i| / c^2`.

This is a processed observational ephemeris, not raw ranging.  Its dynamical
solution dependency is explicitly retained; it is admissible as a state-vector
observation but cannot establish a mechanism independently of ephemeris
construction.

### D2 — Solar surface radius input

Freeze the IAU 2015 nominal solar radius and, separately, the direct
photospheric-radius estimate `695658 ± 140 km` cited by the IAU resolution.
The nominal value is a conventional scale; the direct estimate controls the
radius uncertainty sensitivity.

### D3 — Solar spectral comparator

Retrieve the machine-readable observational table, if available, underlying
Molaro et al. (2020), *The solar gravitational redshift from HARPS-LFC spectra*
or a higher-provenance equivalent.  The intended summary comparator is the
reported global shift `638 ± 6 m/s`, but individual-line data are preferred.
Convective line shifts, laboratory wavelengths, and any 3D atmospheric model
used by the source must be listed as nuisance dependencies.  This comparator is
therefore initially `UNADJUDICATED`, never confirmation by itself.

### D4 — Non-local timing readiness

Locate a public primary radiometric/range product for a solar-conjunction
experiment with timestamps, station/transponder metadata, and independently
reconstructible geometry.  A publication that reports only a fitted PPN
parameter or a coefficient is insufficient as a timing target.  If no such
product is found in this cycle, report `PENDING_DATA`; do not substitute the
leading-order delay formula for a measurement.

## 3. Predictions and decisions fixed before retrieval

1. **Depth-transfer prediction.**  Compute the full D1 distribution of
   `v_pred,i = c * koppa_i * (1/R_Sun - 1/r_i)`.  Compare its weighted mean to
   D3 only after all rows are processed.  If D3 is an independent observational summary and
   `|mean(v_pred)-v_obs| > 2*sqrt(sigma_pred^2+sigma_obs^2)`, the joint
   `koppa → z_spec` chain is **EXCLUDED** for this input definition.  Otherwise
   it is merely **COMPATIBLE**, not established.
2. **Input-consistency check.**  The coefficient of variation of `koppa_i` must
   be reported.  A non-constant sequence does not refute an elliptic orbit;
   it identifies whether the declared instantaneous form needs a specified
   orbital invariant or a revised initial condition.
3. **Exact propagation check.**  Numerically integrate
   `1/[c(1-koppa/r)^2] - 1/c` along a declared straight path and compare it to
   `depth_closure::shapiro_delay()`.  The latter is labelled **LEADING_ORDER**;
   no agreement with its own approximation is evidence of an observed delay.
4. **Timing criterion.**  D4 can test a Shapiro-like marker only if its
   measured time/range residual is separable from geometry and clock
   calibration.  Fit at most the declared instrumental offsets; do not fit
   koppa, profile exponent, or a delay amplitude after looking at the target.
5. **Domain test.**  Evaluate the adopted profile only for `0 <= z < 1`; all
   `z >= 1` inputs must be rejected rather than interpreted through the
   square-root inverse.

## 4. Error model and falsification conditions

Report source uncertainty, vector-table precision, radius uncertainty,
spectral-systematic uncertainty, numerical quadrature convergence, and the
effect of row exclusions.  A result is excluded if it fails a stated numerical
or observational criterion; lack of open data is `PENDING_DATA`, and an
unmodelled spectral nuisance is `UNADJUDICATED`.

Every failure report must name: the failed equation, where its input entered,
the independently observed target, the residual, a falsifiable repair, and an
out-of-sample test that repair would owe.

## 5. Explicit non-goals

This first loop neither assumes nor rejects any competing gravitational
framework.  It does not infer a cosmological variable-speed law from solar
data.  It records whether the local solar mechanism supplies independently
measurable prerequisites for later lensing and external-frame propagation
tests.

## Amendment 01 — 2026-08-07, before calculation

The original decision rule omitted the `- z(r_observer)` term while the stated
mechanism directly above it included `z_spec = z(R_Sun) - z(r_observer)`.  That
was an internal specification error, not a data result.  The decision rule is
corrected to the full depth differential before any D1 or D3 numerical value is
computed.  Frozen source files, requested date range, source selection, and
the two-standard-deviation exclusion rule are unchanged.
