# NSEQ17 — Light-Nucleus Wake-Mesh Calibration

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED before instrumentation  
**Scope:** H-2, H-3, and He-3 only

## Question

Can independently calibrated, phase-locked assemblies of the canonical four-circuit
nucleon wake reproduce the measured mass defect and magnetic dipole moment of H-2,
H-3, and He-3 while retaining closed flow, low numerical divergence, and the
constitutional no-neutron–neutron-contact rule?

H-2 additionally calibrates its electric quadrupole moment. Charge radius is excluded.
Spin/parity is not a fit input; rotational periodicity and handedness are reported as a
diagnostic with no promotion unless a native mapping is supplied.

## Measured inputs

All masses and magnetic moments come from `sdt::laws::measured`, updated to the
CODATA 2022 adjustment. Binding energies are computed from the constituent and bound
nuclear masses, not entered independently.

The H-2 electric quadrupole target is:

`Q_d = 0.285699 fm²`

Source: Pachucki, *Hyperfine Structure of the First Rotational Level in H2, D2 and HD
Molecules and the Deuteron Quadrupole Moment* (2020), Eq. 24. This is an OBSERVED
spectroscopy input, not a CODATA constant.

## Fixed construction

1. Every nucleon is one complete canonical `(4,3)` four-tour circulation.
2. Every nucleon carries four closed wake circuits:
   `crown → convergence → throat+poloidal split → tail → skirt → exterior → crown`.
3. Composite flow is formed by rigidly transforming complete closed circuits.
4. `U = curl(A)` is retained. No source or sink is added at a mesh interface.
5. H-3 is `n-p-n`; its neutron wakes may not contact one another.
6. He-3 is `p-n-p`.
7. Self-energy is excluded from binding. Only pairwise wake cross-terms enter.

## Calibration parameters and bounds

H-2 uses six fitted quantities:

- centre separation: `[1.40, 2.60] Rp`;
- relative tilt: `[45°, 135°]`;
- toroidal phase: `[0, 2π)`;
- poloidal roll phase: `[0, 2π)`;
- energy bridge: `[0.01, 100] MeV / overlap-unit`;
- magnetic bridge: `[-20, 20] μN / geometric-moment-unit`.

H-3 and He-3 each use seven fitted quantities:

- common centre separation: `[1.40, 2.80] Rp`;
- outer opening angle: `[120°, 180°]`;
- relative tilt: `[45°, 135°]`;
- toroidal phase: `[0, 2π)`;
- poloidal roll phase: `[0, 2π)`;
- the same energy-bridge bounds;
- the same magnetic-bridge bounds.

Each isotope is calibrated independently, as directed. A deterministic bounded
coordinate search with frozen initial seeds and step schedule is used. At each pose,
the two dimensional bridge coefficients are profiled analytically and rejected if
outside their registered bounds.

## Observables

### Binding

On a fixed integration stencil:

`I_mesh = -Σ_(i<j) ∫ U_i · U_j dV`

with self terms omitted. The calibrated binding is:

`B_model = K_E I_mesh`.

### Magnetic dipole

Overlap modifies the signed circuit ledger while preserving split/rejoin closure.
The effective moment is evaluated by:

1. `μ_integral = 1/2 ∫ r × J_eff dV`;
2. an exterior axial/equatorial `1/r³` dipole fit.

The dimensional bridge `K_μ` is visible in the ledger. No final-field normalisation is
permitted after the fit.

### H-2 electric quadrupole

The trace-free axial second moment of the normalized proton circulation is evaluated
directly in `fm²`:

`Q_zz = ∫ ρ_p (3z²-r²) dV / ∫ρ_p dV`.

No charge-radius target enters.

## Registered tolerances and rejection criteria

- split and rejoin residual: `≤ 1e-12`;
- relative numerical divergence: `≤ 1%`;
- magnetic integral/far-field disagreement: `≤ 5%`;
- fitted target relative residual: `≤ 1e-4`;
- deterministic rerun parameter difference: `≤ 1e-12`;
- H-3 neutron–neutron overlap: `< 10%` of its weaker p–n overlap;
- no fitted coefficient may sit within `1e-6` of a registered bound.

The calibration is rejected if any conservation, dimensional, route-agreement,
determinism, coefficient-bound, or neutron–neutron criterion is not met.

## Classification

All target-matched values are `CALIBRATED(n)`, where `n` is the isotope parameter count
above. Wake topology and conservation checks are `COMPUTED`. Measured inputs are
`MEASURED-INPUT` or `OBSERVED` as stated. Spin/parity remains `PENDING`.
