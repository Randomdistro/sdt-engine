# APS12b Assessment — Universal Carrier and c-Boundary

**Date:** 2026-08-13  
**Author:** James Christopher Tyndall, Melbourne  
**Calibration:** permitted and explicitly counted  
**Canon edits:** none  
**Isolation:** no APS12 or APS12a generated artifact was used

## Executive verdict

The investigation separates a useful geometric observation from two stronger
physical claims.

1. **Nuclear enclosure inside `Z r_e`: SURVIVES as geometry.** All 908 measured
   nuclear radii in the corpus lie inside both `r=koppa` and `r=2 koppa`.
2. **One literal universal wavelength shifted at one electron seat:
   EXCLUDED.** Atomic series contain different frequencies sharing the same
   upper seat and different frequencies sharing the same lower seat.
3. **A multiplicative two-seat redshift of one universal carrier:
   EXCLUDED as a predictive model.** Calibration improves the five training
   rows but fails held-out hydrogen, other elements, and series limits.
4. **Strict nuclear opacity with no boundary re-emission: EXCLUDED.** The
   corpus contains 3,576 evaluated gamma transitions from nuclei geometrically
   inside `Z r_e`.
5. **Calibrated boundary re-emission: OPEN / UNDERDETERMINED.** A beta term
   changes held-out logit error, but beta and Z are almost perfectly
   confounded and only five effective training nuclides carry usable
   conversion data.

The evidence supports saying that the nucleus lies behind the proposed
c-boundary. It does not support calling that boundary a literal black-hole
horizon on the basis of atomic wavelengths or gamma opacity.

## Data

- 52 atomic rows: H series, He II/Li III, 28 hydrogenic series limits, and
  four multi-electron final hold-outs.
- 908 measured nuclear radii.
- 3,576 IAEA/ENSDF adopted gamma transitions across 13 nuclides.
- 639 gamma rows with total internal-conversion coefficients.

Checksums and provenance are in `DATA_MANIFEST.md`.

## Claim 1 — nucleus inside the c-boundary

For `beta=R_nucleus/(q Z r_e)`:

| Fixed boundary | Inside / total | Minimum beta | Median beta | Maximum beta |
|---|---:|---:|---:|---:|
| `q=1`, `r=Z r_e` | 908/908 | 0.02155 | 0.03057 | 0.76017 |
| `q=2`, `r=2 Z r_e` | 908/908 | 0.01077 | 0.01528 | 0.38008 |

This is a robust enclosure inequality over the measured-radius corpus.
Calling it a result about geometry is warranted. Calling it black-hole
behavior is not: the inequality follows from the proposed boundary scale and
does not by itself establish a horizon, opacity, thermal spectrum, or causal
disconnection.

## Claim 2 — literal upper-seat universal carrier

`U_upper` predicts equal frequencies whenever transitions share `n_upper`.
The observed maximum-to-minimum frequency ratios are:

- shared upper `n=3`: 6.400;
- `n=4`: 19.286;
- `n=5`: 13.500;
- `n=6`: 11.667;
- `n=7`: 2.531.

The predicted ratio is exactly 1 for every group. No value of carrier
frequency or redshift exponent can remove this contradiction.

**Decision: EXCLUDED.**

## Claim 3 — literal lower-seat universal carrier

`U_lower` predicts equal frequencies for all lines ending on the same lower
seat. The observed ratios are:

- Lyman lower `n=1`: 1.296;
- Balmer lower `n=2`: 1.653;
- Paschen lower `n=3`: 1.866.

Again, the predicted ratio is exactly 1 and calibration cannot change it.

**Decision: EXCLUDED.**

## Claim 4 — two-endpoint universal carrier

The calibrated model

`nu = nu_0 [(1-z_upper)/(1-z_lower)]^p`

fits five selected H rows with `p=44,440.98`, already showing that the
canonical `p=1` clock shift is far too small to span atomic line energies.
Performance then degrades:

| Evaluation | Calibrated U_ratio log-RMSE | Median fractional error |
|---|---:|---:|
| H training | 0.0933 | 0.0895 |
| H hold-out | 0.445 | 0.167 |
| He II / Li III hold-out | 10.553 | 71,658 |
| Z=2–29 series-limit hold-out | 498.5 | `1.8e261` |

The fixed `p=1` version has 90.9% median fractional error on He/Li and 99.8%
on series limits. A calibrated quadratic in `Delta z` fits training more
closely but also collapses out of sample.

**Decision: EXCLUDED as a predictive universal-carrier model.**

## Comparison with depth-difference spectroscopy

The reduced-mass Rydberg comparator gives:

- H hold-out median fractional error `3.97e-6`;
- He/Li median `4.37e-5`;
- Z=2–29 series-limit median `0.00300`.

The calibrated Ritz comparator returns exponent `s=2.0000346` and is only
marginally different from Rydberg. The spectra therefore select the
inverse-square seat difference:

`nu proportional to Z^2 (1/n_lower^2 - 1/n_upper^2)`.

This does not require every photon to begin with one common wavelength. A
version of the original intuition can survive only in a weaker form: the same
underlying movement law sets every seat, while each transition emits the
difference between two seat depths. Numerically that is Rydberg convergence,
not the literal universal-carrier hypothesis tested here.

## Claim 5 — strict black-hole opacity

All 3,576 adopted gamma transitions in the selected corpus have measured
nuclear radii with `beta<1`. A model stating that no radiation from inside the
boundary can emerge, with no boundary process, predicts zero such gamma
transitions.

**Decision: EXCLUDED for strict opacity without re-emission.**

This does not prove photons traverse the proposed boundary unchanged. It
shows that an opaque model must supply a boundary conversion/re-emission
mechanism that preserves the observed gamma energies, branches, angular
momenta, and lifetimes. Without that mechanism, “black hole” is contradicted
by ordinary nuclear spectroscopy.

## Claim 6 — calibrated boundary re-emission

For 639 transitions with total conversion coefficients, the target gamma
fraction is `1/(1+ICC)`. A regression controlled for gamma energy, Z, and the
available E1/E2/mixed multipolarity classes was compared with a version adding
`log(beta)`.

| Model | Held-out logit RMSE | Held-out fraction MAE |
|---|---:|---:|
| controls only | 2.625 | 0.0910 |
| controls + beta | 2.223 | 0.0949 |

The beta term improves logit RMSE but worsens mean absolute gamma-fraction
error. More importantly:

- only five effective training nuclides have usable ICC rows;
- `corr(log Z, log beta) = -0.999475`;
- design condition number = 1518.84;
- leave-one-nuclide-out beta coefficient ranges from -81.67 to -43.62.

The fit cannot distinguish a boundary-depth effect from Z and isotope
selection. Repeated transitions do not create independent beta information
because beta is constant within each nuclide.

**Decision: OPEN / UNDERDETERMINED, not predictive.**

## Multi-electron hold-out

Neither the universal-carrier models nor bare Rydberg generalise to the four
multi-electron rows. Be I and Na I are same-principal-seat transitions, so a
principal-`n` depth model assigns zero while the observed lines are nonzero.
This remains an occupancy and intra-seat geometry problem; adding per-element
carrier offsets would fit rather than predict it.

## Scope and limitations

- NIST H/He/Li values are repository-cached comparison data; a future refresh
  should add explicit uncertainties and more H-like line measurements.
- The 28 series limits are measured bound-free thresholds, not discrete
  emission lines. They are valid cross-Z energy-scale tests but are labelled
  separately.
- Measured RMS radius is not necessarily the physical outer boundary. The
  enclosure margin is large for most nuclei, but the distinction remains.
- ENSDF gamma existence tests strict opacity. It does not localise a proposed
  SDT re-emission event.
- The re-emission regression is a benchmark, not a mechanism derivation.

## Conclusion

The starting intuition contains one durable statement: under the SDT
definition, measured nuclei are geometrically deep inside `Z r_e`.

The literal spectral statement does not survive. Electron lines are not one
wavelength merely shifted according to either endpoint depth. Their observed
structure requires a two-seat energy difference, and the successful
inverse-square difference is the established Rydberg form.

The black-hole analogy also fails in its strict opaque form because nuclear
gamma emission is observed. A revised theory could propose conversion at the
c-boundary, but it must predict gamma energy, branching, multipolarity, and
lifetime across held-out nuclei. The present calibrated beta benchmark does
not yet do that.
