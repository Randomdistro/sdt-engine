# APS12a Assessment — Independent nuclear-koppa emission test

**Date:** 2026-08-13  
**Isolation:** No APS12/Grok artifact was read or written.  
**Hold-outs:** 166 rows; SHA256
`4e3c481f2cffc085809f7b7d8c034749a134fcc6d179cdc07c82799481a1761f`  
**Prompt completion:** A  
**CALIBRATED budget used:** 0  
**Canon edits:** none

## Verdict

APS12a does **not** establish a native nuclear-gravitation spectroscopy rule.
It reproduces the expected one-electron Rydberg/Delta-z convergence at low and
moderate Z, but the distinct occupancy and NP12-size rules miss their frozen
gates. The leading high-Z Fe XXVI expression also misses its 0.5% gate.

The result is therefore:

- **CONVERGENCE** for H, He II, Li III, last-electron ionisation, and H-D
  reduced-mass shift;
- **OPEN** for multi-electron occupancy;
- **OPEN / not supported** for NP12 covering fraction as a Ca size-sign rule;
- **EXCLUDED at the frozen gate** for leading-order Fe XXVI Ly-alpha;
- **not NATIVE-distinct** overall.

## Gate table

| Gate | Actual | Decision |
|---|---:|---|
| V0 canonical consistency | max relative `1.946e-12` (bar `1e-10`) | MATCH |
| V0 H I 2->1 | `+11.8915 ppm` (bar 15 ppm) | MATCH |
| two-route | maximum below `1e-15` (bar `1e-9`) | MATCH |
| G_EXC_H | max `12.5009 ppm` | MATCH |
| G_EXC_light | max `263.226 ppm` | MATCH |
| G_EXC_Fe | relative `0.9261%` (bar 0.5%) | EXCLUDED |
| G_ION_last Z<=20 | max `0.5057%` | MATCH |
| G_ION_last Z=21..29 | max `1.0835%` | MATCH |
| G_ION_S S_bare | `3/97 = 3.09%` under 10% error | OPEN |
| G_ION_S S_ion | `14/97 = 14.43%` under 10% error | OPEN |
| G_ISO_mass | relative error on H-D shift `0.0916%` | MATCH |
| G_ISO_size | Ca signs `2/4` | OPEN |
| G_MULTI | four rows, no fitted coefficient | COMPLETE |

## Excitation

The H I Lyman, Balmer, and Paschen rows all remain below 15 ppm. He II and
Li III remain below 1000 ppm; the largest residual is Li III 4->1 at
263.226 ppm. These are the same closed form as Rydberg spectroscopy and count
as CONVERGENCE, not independent mechanism evidence.

Fe XXVI is different at the frozen precision bar. The leading expression gives
6898.02 eV against the 6962.5 eV held-out centroid, a relative miss of 0.926%.
The Law-V value is 6977.12 eV and its correction is 1.1467% of the leading
energy, but it was logged only and was not substituted to rescue the leading
gate.

## Ionisation

The last-electron residual rises smoothly with Z, from 0.0045% at He to 0.506%
at Ca and 1.084% at Cu. It remains within the pre-registered 1%/2% bars.
Z=30 is `NO_DATA` because the canonical JSON lacks IE_30.

Neither frozen companion rule predicts intermediate ionisation:

- S_bare: 3 of 97 rows within 10%;
- S_ion: 14 of 97 rows within 10%;
- required: at least 78 of 97 rows.

The unpaid object is `koppa_felt` in a multi-electron atom. No screening
fraction was introduced.

## Isotopes

Reduced mass predicts the H-D Ly-alpha wavelength separation as
0.0330697 nm against 0.0331000 nm, a 0.0916% relative error on the shift.
This is two-body CONVERGENCE.

NP12 radius is monotonic in A, so its covering fraction increases on all four
Ca steps. The observed charge-radius differences become negative on
44->46 and 46->48. The sign score is 2/4, below the required 4/4. Measured
charge radii were comparison values only, not predictor inputs.

Grammar landmarks were reported without being scored: Ca-40 has `n_t=0`;
Yb-174 has `n_t=n_d=34`.

## Multi-electron lines

- He I: S_bare relative error 0.923; S_ion 0.519.
- Be I and Na D: principal-n-only Delta-z is zero (`SAME_N_NULL`).
- Fe XXV: S_bare relative error 0.0296; S_ion 0.0481. No MATCH is claimed
  because this phase had table-completion only and no line-specific gate.

## Residuals

- The high-Z leading approximation omits a correction of the same order as
  the Fe XXVI residual.
- The two frozen occupancy extremes do not describe intermediate electrons.
- A monotonic `A^(1/3)` boundary cannot reproduce the Ca radius inversion.
- Principal n alone cannot resolve same-n term splittings.

## Prohibited-move checklist

- [x] No APS12/Grok artifact read
- [x] No threshold amended after execution
- [x] No ionisation-derived `Z_eff`
- [x] No third screening rule
- [x] No measured radius used in I_size
- [x] No grammar re-sort claimed as evidence
- [x] No fitted coefficient
- [x] No canon edit

## Conclusion

APS12a supports Delta-z as a representation of the one-electron Rydberg spine,
not as a completed predictive account of nuclear construction in atomic
emission. The distinct payload—companion occupancy and finite-nucleus
structure—remains unpaid by the tested rules.
