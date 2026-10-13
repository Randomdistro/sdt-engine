# NSEQ17 Repair — Neutron Counter-Circulation and Deformable Wake Mesh

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED repair before revised instrumentation  
**Supersedes:** the fixed-template and target-normalised magnetic implementation

## Reason for repair

The first NSEQ17 instrument made two inadmissible substitutions:

1. it represented a neutron as the Hydrogen wake with handedness reversed and an
   `internalElectron` flag, then scaled that wake from the measured neutron moment;
2. it treated every bound nucleon wake as an undeformed copy of the free-Hydrogen
   four-circuit geometry.

The first operation did not model the neutron's subdued magnetic attribute. The second
confused “operates like Hydrogen” with “is unchanged from Hydrogen”. The previous
`NSEQ17_CALIBRATION_CONSISTENT` assessment is therefore withdrawn as a physical model;
its numerical output remains only a record of the superseded instrument.

## Repaired neutron

The neutron is represented by two signed magnetic circulation ledgers:

- the proton-form circulation;
- a seated-electron counter-circulation.

Both raw contributions and their vector sum must be reported. The free-neutron magnetic
target may fit one explicit counter-circulation coefficient:

`mu_n = mu_proton-form + k_e-seat * mu_e-seat-basis`.

This is `CALIBRATED(1)`, not a prediction. Directly assigning `mu_n` as a segment scale is
forbidden. The suppression ratio

`|mu_n| / (|mu_proton-form| + |mu_e-seat|)`

must be reported so cancellation cannot be hidden.

The displacement wake and magnetic-equivalent wake are separate ledgers. The seated
electron can reorganise the neutron wake and reverse its magnetic projection without
removing the full mechanical circulation needed for nuclear meshing.

## “Operate like Hydrogen”

Hydrogen supplies the operating law, not a frozen template. Every free nucleon begins
from phase-driven circulation with:

- continuous closed flow;
- local one-out/one-in return;
- split and rejoin conservation;
- a field generated as `U = curl(A)`;
- phase lock to the moving nucleon.

When wakes mesh, the solver may alter:

- crown, throat, poloidal, tail, skirt, and return geometry;
- throat/poloidal flow division;
- local strength and axial/radial extent;
- correspondence or merger of circuit sectors.

The revised implementation will first support continuous geometry deformation and
conservative flow repartition. It will report whether the four incoming phase sectors
remain distinct or become paired/shared. Four surviving sectors are an outcome, not a
constraint.

## Repaired calibration parameters

The existing isotope-specific pose and dimensional bridge parameters remain visible.
Each isotope additionally fits:

- wake compliance in `[0, 0.45]`;
- conservative split shift in `[-0.35, 0.35]`.

The split is clamped only by rejecting candidates outside `(0.05, 0.95)`, with
`Q_throat + Q_poloidal = 1` exactly. A common continuous spatial warp is applied to every
point in a circuit so stage seams remain connected.

The free-neutron counter-circulation is calibrated once, frozen, and reused unchanged by
H-2, H-3, and He-3. Composite fitting may not reassign the measured neutron moment to a
unit or alter the frozen internal cancellation.

## Targets

- free neutron: CODATA 2022 magnetic moment;
- H-2: mass defect, magnetic dipole, observed electric quadrupole;
- H-3: mass defect and magnetic dipole;
- He-3: mass defect and magnetic dipole.

Charge radius and spin/parity remain excluded from fitting.

## Rejection tests

The repaired instrument is rejected if:

1. neutron magnetic segments are obtained from `target/selfMoment`;
2. the proton-form and seated-electron contributions are not separately visible;
3. neutron suppression does not result from signed cancellation;
4. composite fitting changes the frozen free-neutron ledger;
5. any transformed circuit opens or acquires a source/sink;
6. split/rejoin residual exceeds `1e-12`;
7. relative numerical divergence exceeds `1%`;
8. wake deformation is absent from all three fitted composites;
9. Release and docs mirrors differ.

## Classification

- free-neutron counter-circulation coefficient: `CALIBRATED(1)`;
- isotope pose, deformation, and dimensional coefficients: `CALIBRATED(n)`;
- closure, conservation, divergence, and circuit-sector accounting: `COMPUTED`;
- spin/parity: `PENDING`.
