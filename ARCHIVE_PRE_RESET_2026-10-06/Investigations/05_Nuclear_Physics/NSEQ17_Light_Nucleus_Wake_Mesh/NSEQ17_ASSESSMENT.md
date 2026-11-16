# NSEQ17 — Light-Nucleus Wake-Mesh Calibration Assessment

**Author:** James Christopher Tyndall, Melbourne  
**Execution:** `nseq17_wake_mesh_validate.js`  
**Output:** `nseq17_results.json`

## Result

`NSEQ17_CALIBRATION_CONSISTENT`

The first fixed-template execution is superseded by `PROMPT_REPAIR.md`. The repaired
deterministic instrument completed the free-neutron counter-circulation and the
deformable H-2, H-3, and He-3 wake meshes in one pass.
The matched values are calibrations, not predictions:

| nucleus | class | binding model / target (MeV) | magnetic model / target (μN) | additional target |
|---|---|---:|---:|---:|
| H-2 | CALIBRATED(8) | 2.224566342 / 2.224566342 | 0.8574382335 / 0.8574382335 | Q = 0.285682357 / 0.285699 fm² |
| H-3 | CALIBRATED(9) | 8.481796625 / 8.481796625 | 2.9789624650 / 2.9789624650 | — |
| He-3 | CALIBRATED(9) | 7.717989650 / 7.717989650 | −2.1276253498 / −2.1276253498 | — |

The fitted dimensional bridges and all pose parameters are exposed in the JSON ledger.
No final-field rescaling follows the fit.

## Instrument checks

- unit circular-filament moment residual: `3.92e-7`;
- rigid translation residual: `4.58e-16`;
- separated-pair overlap: `0`;
- repeated-fit parameter residual: `0`;
- split and rejoin residuals: `0`;
- maximum relative numerical divergence: `3.01e-15`;
- H-3 neutron–neutron contact-channel overlap ratio: `0`;
- magnetic integral/far-field disagreement:
  - H-2: `1.232%`;
  - H-3: `0.379%`;
  - He-3: `1.650%`.

Every registered tolerance is satisfied.

## What the calibration establishes

The neutron is no longer a sign-reversed proton wake. Its frozen magnetic ledger is:

- proton-form circulation: `+2.7928473446 μN`;
- seated-electron counter-circulation: `−4.7058901046 μN`;
- measured net: `−1.9130427600 μN`;
- net/gross suppression: `25.51%`.

The counter-circulation coefficient is `CALIBRATED(1)` and is reused unchanged in every
composite. Nuclear fitting cannot assign the measured neutron moment directly to a wake
segment or modify this frozen internal ledger.

Hydrogen now supplies an operating law rather than an unchanged wake template. The
composite wakes retain closed phase-driven circulation, one-out/one-in return,
split/rejoin conservation, and `U = curl(A)`, while their geometry and flow partition
deform during meshing. Binding is evaluated on the frozen `5×5×7` volume stencil as
the signed field cross-term `-∫U_i·U_j dV`; the superseded segment-proximity surrogate
is removed. The fitted throat/poloidal partitions are approximately `0.80/0.20` for
H-2, `0.10/0.90` for H-3, and `0.45/0.55` for He-3; all split and rejoin residuals
remain zero. H-3 retains two p–n meshes and excludes a neutron–neutron contact mesh.

## Limitations

The neutron counter coefficient and each isotope's mass/magnetic bridges are fixed by
their targets. Those matched numbers therefore carry `CALIBRATED(n)` status and have no
out-of-sample evidential weight. The deformation is continuous and conservative, but the
current solver retains four incoming phase sectors and reports their mesh
correspondences; it has not demonstrated an actual sector merger. The wake-overlap
quadrature is a finite filament discretization on a `5×5×7` midpoint stencil, and
refinement stability beyond the registered resolution has not been established. H-2’s quadrupole is an OBSERVED
spectroscopy target rather than a CODATA constant.

Rotational periodicity and net handedness were not fitted. No native map from those
diagnostics to nuclear spin/parity exists in this instrument, so spin/parity remains
`PENDING`.
