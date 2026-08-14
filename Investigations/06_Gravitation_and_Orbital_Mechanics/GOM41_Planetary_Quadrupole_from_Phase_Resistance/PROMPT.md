# GOM41 — Planetary Quadrupole from Phase Resistance

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-14  
**Status:** pre-registered B11 closure investigation

## Question

Can a rotating body's normalized resistance quadrupole be predicted from
movement, geometry, independently measured composition/boundaries and the
Law-IV phase-resistance kernel, without a body-source mass parameter or a
profile inferred from the J2 values under test?

## Forward call graph

```text
satellite orbital radius + period
  -> v_satellite=2 pi r/P
  -> koppa_body=v_satellite^2 r/c^2
  -> N_baryons=koppa_body/koppa_per_baryon
  -> Law-IV engaged resistance distribution

body radius + spin period + independent boundary/composition facts
  -> local spin movement / convergence-resistance balance
  -> deformed resistance distribution rho_R(r,theta)
  -> normalized trace-free quadrupole
  -> J2_SDT
  -> measured J2 comparison
```

The source-strength path may use no symbol or alias equivalent to `G`, source
`M`, `GM`, `mu`, or `u=GM`. Published masses and gravitational parameters are
comparison-only. The orbital movement used for koppa must be traced to raw
radius and period.

## Corpus and provenance

The primary one-pass corpus is Earth, Mars, Jupiter, Saturn, Uranus and
Neptune. Each row must record:

- body mean radius and spin period;
- one independently timed satellite orbit `(r,P)` used to obtain koppa;
- independently measured composition or mechanical boundary facts used by a
  resistance profile;
- measured `J2` and uncertainty in a comparison-only structure;
- source, retrieval date, units and uncertainty for every raw datum.

No radial profile may be fitted to, inverted from, or selected by the J2 column.
The frozen model ladder is:

- `Q0_UNIFORM`: constant engaged resistance inside the measured mean radius;
- `Q1_CONVERGENCE`: radial resistance from the Law-I/IV pressure balance, with
  no composition strata;
- `Q2_BOUNDARIES`: Q1 plus independently observed mechanical/composition
  boundaries, frozen before comparison.

## Numeric gates

1. Zero spin produces `J2=0` to absolute error `<1e-12`.
2. Rotating a spherically symmetric numerical grid without deforming it
   produces quadrupole leakage `<1e-8`.
3. Direct volume integration and spherical-harmonic projection of the same
   resistance distribution agree within `0.5%`.
4. Doubling radial and angular resolution changes every predicted J2 by `<1%`.
5. All six bodies run in one pass with the same balance law and no
   body-specific coefficient. Predicted values are sealed before measured J2
   is loaded.
6. A model advances B11 only if Earth and Jupiter are each within `3%`, at
   least four of six bodies are within `10%`, and whole-corpus RMS fractional
   residual is `<=10%`.
7. If Q0 fails, Q1 and then Q2 run in the registered order. If all fail,
   preserve each whole-corpus residual and state the missing resistance-profile
   dependency; do not tune an interior profile to J2.

## Certification

A gate-passing, delete-test-clean result is Class C (`DERIVED` route with known
comparison). A dimensionally closed miss remains `PENDING`. Agreement obtained
by consuming a measured J2 or an equivalent gravity-harmonic profile is void.
