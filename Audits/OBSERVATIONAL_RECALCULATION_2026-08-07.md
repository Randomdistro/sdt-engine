# Observational Recalculation Addendum — 2026-08-07

## Scope correction

This addendum implements the instruction that empirical adjudication use only experimental and observational data. It supersedes the *empirical* status of every finding in Audits/BLUEPRINT_FORMAL_FALSIFICATION_2026-08-07.md.

The engine, the blueprint, and any competing theoretical account are hypotheses only. They are not data sources. Internal contradictions remain engineering and formal-readiness defects, but they are not counted below as empirical falsifications.

## Data register

| ID | Measured or observational input | Value used | Provenance |
|---|---|---:|---|
| D-01 | Bohr radius | 5.291 772 105 44(82) × 10^-11 m | NIST CODATA 2022 |
| D-02 | Proton rms charge radius | 8.4075(64) × 10^-16 m | NIST CODATA 2022 |
| D-03 | Speed of light | 299 792 458 m/s, exact | SI / NIST CODATA 2022 |
| D-04 | Solar disk spectral line shift | 638 ± 6 m/s | HARPS-LFC Moon spectra |
| D-05 | Solar photospheric radius | 695 658 ± 140 km | direct photospheric measurement cited by IAU |
| D-06 | Total solar irradiance | 1361 ± 1 W/m², 2 sigma | calibrated spaceborne radiometry cited by IAU |

Sources:

- [NIST CODATA 2022 values](https://physics.nist.gov/cuu/pdf/JPCRD2022CODATA.pdf)
- [IAU Resolution B3: nominal solar values and observational provenance](https://www.iau.org/common/Uploaded%20files/IAUGA2015-Resolution-B3-recommended-nominal-conversion.pdf)
- [HARPS-LFC solar spectra observation](https://arxiv.org/abs/2009.10558)

The solar line-shift datum remains subject to the paper's stated laboratory-wavelength and photospheric-convection systematics. It is used here as an observation, not as a validation of any theory.

## O-01 — measured radii exclude the blueprint’s 10^39 equality

### Pre-registered calculation

Use only D-01 and D-02 in the blueprint's displayed expression:

~~~text
R_area = (a0/rp)^2.
~~~

No force law, mass model, or framework-specific quantity enters.

### Result

~~~text
R_area = (5.291 772 105 44×10^-11 / 8.4075×10^-16)^2
       = 3.961 580 756×10^9.
~~~

The uncertainty in the proton radius changes this at roughly the 0.15% level, not by thirty orders of magnitude.

### Ruling

The empirical input values exclude the statement that the displayed area ratio is approximately 10^39. The equation produces a measured-radius ratio of order 10^9.

### Origin and recovery

The equation needs approximately 10^29.4 of additional, defined dimensionless factors before it can reach 10^39. The blueprint supplies none. The 10^39 conclusion must therefore be withdrawn from this formula. A replacement must list every experimentally anchored factor before comparison.

**Status:** EXCLUDED by metrology-anchored arithmetic.

## O-02 — optical compactness has no data-producing prediction

### Observable

The HARPS-LFC analysis reports a solar disk line shift of 638 ± 6 m/s. Expressed as a dimensionless shift only:

~~~text
z_obs = (638 ± 6) / 299,792,458
      = (2.1281 ± 0.0200)×10^-6.
~~~

This does not assume an explanation for the shift.

### Blueprint testability check

The blueprint offers:

~~~text
z_model = N a0 alpha² / R_surface.
~~~

It does not define a measured procedure that produces N for a star, nor does it fix N from the listed experimental inputs. Therefore it produces no numerical z_model and cannot be compared to z_obs.

The former engine-derived N counterexample is retained only as a conditional algebra check, not as an observational rejection: its mapping from observed matter to blueprint knot count is not stated in the blueprint.

### Ruling

The solar observation is a valid target. The blueprint has not supplied a prediction for it. It is neither a PASS nor a FAIL.

### Recovery

Pre-register an observational rule that obtains N independently of solar line shifts and without using a target compactness. State uncertainty propagation. Then compute z_model before unblinding D-04.

**Status:** UNADJUDICATED — missing initial condition and measurement map.

## O-03 — thermal-slip claim has no predicted value for observed solar irradiance

### Observable

The IAU documents a cycle-averaged total solar irradiance of 1361 ± 1 W/m² from calibrated radiometry. This is the observational target relevant to a claimed continuous stellar heat output.

### Blueprint testability check

The proposed heat expression contains eta_slip and the aggregate topological area. Neither is derived or assigned by an independent measurement protocol. Consequently its numerical output can be moved across the observed irradiance by selecting undeclared quantities.

### Ruling

No observation can adjudicate the current expression because it does not produce a unique prediction. The existence of a measured solar flux does not pay for an unspecified efficiency or area.

### Recovery

Before looking at any thermal target, specify eta_slip from a separate experiment or declare it CALIBRATED(1), define every A_topo,k, and calculate an absolute flux with units W/m². Hold out D-06, or a second star, for the first comparison.

**Status:** UNADJUDICATED — free quantity and incomplete observable map.

## O-04 — beta-decay and neutrino statements are not yet testable against their data

The blueprint names observable classes: beta-decay energy partitions, spectra, decay rates, and neutrino propagation. It supplies no numerical pressure field, initial condition, boundary condition, coupling tensor, or solver. It therefore emits no energy spectrum, lifetime, angular distribution, or propagation coefficient to compare with experiment.

**Status:** UNADJUDICATED — no output observable is calculated.

**Recovery:** select one observed dataset, state the instrument and its uncertainty, publish all initial conditions, compute a distribution before accessing its target values, and use a whole-range rejection statistic.

## Reclassification of the preceding formal audit

| Prior finding | Data-only standing | Reason |
|---|---|---|
| BF-01 | FORMAL ONLY | independent stored constants are not an observational comparison |
| BF-02 | FORMAL ONLY | unit role of Phi is a definition issue |
| BF-03 | FORMAL ONLY | factor-of-three disagreement was engine-to-blueprint, not data-to-model |
| BF-04 | EXCLUDED | measured radii give 3.9616×10^9, not 10^39 |
| BF-05 | FORMAL ONLY | dimensional mismatch precedes empirical testing |
| BF-06 | FORMAL ONLY | no acceleration-response prediction reaches data |
| BF-07 | UNADJUDICATED | equations lack data-producing initial conditions |
| BF-08 | UNADJUDICATED | no unique thermal prediction reaches observed flux |
| BF-09 | UNADJUDICATED | N has no independent observational measurement map |
| BF-10 | FORMAL ONLY | provenance and terminology are not empirical evidence |

## Data-only rule going forward

A claim enters the empirical ledger only when all five conditions hold:

1. the target is a direct measurement or observation with provenance and uncertainty;
2. every model input is either independently measured before target access or explicitly calibrated;
3. the mechanism outputs the target in the target's units;
4. the prediction and rejection threshold are registered before target comparison; and
5. a parameter cannot be adjusted after the result is known.

No engine constant, summary benchmark, theory-derived decomposition, or competitor-model result may substitute for an observational input.

## Limitations

- CODATA values are recommended metrological adjustments; their provenance and uncertainties are stated in the cited source.
- The solar line-shift result has model-dependent corrections identified by its authors. This addendum uses the reported observation with its uncertainty and does not treat it as a theory-neutral measurement beyond that scope.
- This audit has not downloaded raw telescope or laboratory files; it reports published observational values and their stated uncertainties.

