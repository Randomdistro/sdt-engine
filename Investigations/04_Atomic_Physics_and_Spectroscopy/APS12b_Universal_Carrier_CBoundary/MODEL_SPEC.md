# APS12b Model Specification — Universal Carrier and c-Boundary

**Date:** 2026-08-13  
**Author:** James Christopher Tyndall, Melbourne  
**Status:** working model registry  
**Calibration:** allowed, but every fitted parameter is global and scored on
held-out rows.  
**Isolation:** no APS12 or APS12a generated file is an input.

## Questions kept separate

1. **Geometric enclosure:** is the measured nuclear radius smaller than the
   proposed c-boundary?
2. **Universal carrier:** can one source frequency generate atomic line
   frequencies by a depth-dependent transfer law?
3. **Literal opacity:** is direct radiation from inside the boundary absent?
4. **Boundary re-emission:** if strict opacity fails, can one global
   re-emission law predict gamma branching and timing?

Success on question 1 is not evidence for questions 2–4.

## Canonical geometry

For a hydrogenic seat:

```text
koppa_Z = Z r_e
r_n     = a_0 n^2 / Z
z_n     = koppa_Z / r_n = (Z alpha / n)^2
```

For nuclear geometry:

```text
R_cb(q) = q Z r_e
beta(q) = R_nucleus / R_cb(q)
q in {1, 2}
```

`q=1` is the engine c-boundary at `r=koppa`. `q=2` represents the unresolved
Schwarzschild-correspondence horizon at `r=2 koppa`. Neither is fitted in the
primary geometric table.

## Universal-carrier models

Let `nu_0` be one global carrier frequency. Let `z_u` and `z_l` be upper and
lower seat depths.

### Endpoint models

```text
U_upper: nu = nu_0 (1 - z_u)^p
U_lower: nu = nu_0 (1 - z_l)^p
```

Parameters: `log(nu_0)`, `p`.

These models make structural degeneracy predictions. `U_upper` assigns the
same frequency to transitions sharing an upper seat. `U_lower` assigns the
same frequency to transitions sharing a lower seat. No calibration can remove
those equalities.

### Two-endpoint carrier

```text
U_ratio: nu = nu_0 [ (1-z_u) / (1-z_l) ]^p
```

Parameters: `log(nu_0)`, `p`.

This is a multiplicative clock-ratio model. It is not the Rydberg
depth-difference law.

### Empirical carrier benchmark

```text
U_poly: log(nu) = b0 + b1 Delta_z + b2 Delta_z^2
Delta_z = z_l - z_u
```

Parameters: `b0`, `b1`, `b2`. This is explicitly CALIBRATED(3), not a derived
SDT law.

### Comparison models

```text
Rydberg:
nu = c R_inf (mu/m_e) Z^2 (1/n_l^2 - 1/n_u^2)

Ritz:
nu = A (mu/m_e) Z^s (1/n_l^2 - 1/n_u^2)
```

Ritz parameters: `log(A)`, `s`. The Rydberg model has no fitted spectral
parameter after canonical constants and isotope mass are supplied.

## Calibration and scoring

- Objective: ordinary least squares in `log(nu)`; duplicate observations are
  not weighted as independent.
- Primary split: fit hydrogen Lyman and Balmer training rows; test held-out
  hydrogen rows and all He II/Li III rows.
- Cross-element split: fit Z=1–2, test Z=3; separately fit Z=1 and test Z=2–3.
- Metrics: log-RMSE, median absolute fractional error, maximum fractional
  error, AICc, BIC, and parameter stability.
- A carrier model is predictive only if held-out error remains stable and is
  competitive with Ritz/Rydberg.
- Multi-electron lines are a final frozen transfer test. No new element or
  line offset is allowed.

## Opacity models

### Strict opacity

```text
P_direct_gamma(beta < 1) = 0
```

One observed direct nuclear gamma branch from a nucleus with `beta<1`
falsifies this literal model unless a separate boundary-emission process is
specified.

### Boundary re-emission benchmark

Observed gamma fraction:

```text
f_gamma = 1 / [1 + exp(-(a0 + aE log(E_gamma/keV)
                         + aZ log(Z) + aB log(beta)))]
```

Parameters: `a0`, `aE`, `aZ`, `aB`. Where an internal-conversion coefficient
`ICC` is available, `f_gamma = 1/(1+ICC)`. Fit on one isotope subset and test
held-out nuclides. Multipolarity is required as a standard covariate before
claiming an independent beta effect; if the available corpus lacks enough
rows, the model remains OPEN rather than being fitted without controls.

## Parameter ledger

- `U_upper`, `U_lower`, `U_ratio`: CALIBRATED(2)
- `U_poly`: CALIBRATED(3)
- Ritz: CALIBRATED(2)
- Rydberg: COMPUTED from measured constants
- Geometric `q=1`, `q=2`: fixed alternatives
- Strict opacity: zero fitted parameters
- Boundary re-emission: CALIBRATED(4), conditional on adequate gamma data

## Interpretation rules

- A model that algebraically collapses to Rydberg is CONVERGENCE.
- Endpoint degeneracy failure excludes the corresponding literal carrier.
- `beta<1` across nuclei establishes geometric enclosure only.
- Observed nuclear gamma emission excludes strict opacity unless the photon is
  predicted by a separately tested boundary process.
- A boundary re-emission fit without held-out prediction is descriptive only.
