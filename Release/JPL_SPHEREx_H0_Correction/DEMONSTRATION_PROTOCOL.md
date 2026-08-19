# Redshift-Correction Bookkeeping Demonstration Protocol

Status: pre-registered before the rebuilt instrument is run.

## Scope

This package demonstrates auditable correction bookkeeping for a low-redshift
catalogue. It does not claim to resolve the Hubble tension and it does not infer
an astrophysical correction from source names, sky position, a hand-assigned
position-angle factor, or a target value of H0.

The former CQ18d/e/f result is withdrawn: its ten selected calibrators were below
a standard Hubble-flow cut, several correction factors were assigned by hand,
observer-frame terms were double-subtracted, and the result depended on
cosmological expansion while claiming to replace it. Those programs are not
built by the rebuilt package.

## Input schema

UTF-8 CSV with one header row:

`id,distance_mpc,z_input,z_host_grav,z_host_rotation,z_observer_motion,z_other,host_grav_already_applied,host_rotation_already_applied,observer_motion_already_applied,other_already_applied`

- Correction terms are signed redshift contributions.
- An `*_already_applied` value of `1` means the catalogue has already removed
  that term, so the instrument must not subtract it again.
- A value of `0` means the term remains in `z_input` and is subtracted once.
- Every correction and flag is supplied explicitly; the instrument derives none.
- The diagnostic `H0_linear = c*z_residual/distance` is emitted only for records
  with `0 < z_residual <= 0.1`; it is not a full cosmological estimator.

## Instrument

1. Parse and validate every row.
2. Construct the correction actually due from each component and its applied flag.
3. Compute `z_residual = z_input - sum(corrections_due)`.
4. Report the naive and residual low-z linear H0 diagnostics.
5. Emit leave-one-component-in sensitivity deltas for every row.
6. Write a row-complete CSV and a JSON summary containing no external target H0.

## Validation gates

- **R0 — parser:** malformed numbers, non-binary flags, non-positive distances,
  duplicate identifiers and non-finite values are rejected.
- **R1 — synthetic known answer:** the bundled synthetic catalogue is generated
  from `H0 = 70 km/s/Mpc`; every eligible row recovers 70 with absolute error
  <= `1e-6 km/s/Mpc`.
- **R2 — no double subtraction:** at least one synthetic row marks each component
  as already applied; its output must show zero subtraction for that component.
- **R3 — sign preservation:** positive and negative supplied corrections survive
  parsing and produce the registered opposite-signed H0 sensitivity shifts.
- **R4 — row completeness:** output contains exactly one row per valid input row.
- **R5 — scope guard:** records above `z=0.1` receive no linear-H0 value and are
  counted as out of diagnostic scope.
- **R6 — provenance:** JSON records the source path, schema version, row counts,
  per-gate status and the explicit statement `scientific_result=false`.

Any failed gate returns a non-zero process status. The bundled catalogue is
synthetic and is labelled as such in both file content and output.

