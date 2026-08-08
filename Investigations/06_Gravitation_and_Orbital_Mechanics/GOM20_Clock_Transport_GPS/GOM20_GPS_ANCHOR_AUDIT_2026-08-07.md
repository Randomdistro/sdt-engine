# GOM20 GPS Clock Anchor Audit — 2026-08-07

**Status:** `PENDING_MECHANISM`; anchor `ENGINEERING_ONLY`; physical SDT verdict
`UNADJUDICATED`.

## Boundary

This audit does not use a standard-model calculation as a rejection condition.
It asks only whether GOM20 gives a single, signed, independently testable
satellite-to-ground clock prediction and whether qualifying observations are
available. The frozen evidence classes and checksums are binding in
`Datasets/gps_clock_2026-08/MANIFEST.md`.

No retained artifact is a time-tagged uncorrected satellite-clock comparison
with a published uncertainty budget. There is therefore no empirical residual,
fit, or physical pass/fail result.

## Source correction and recalculation

GOM20 calls the engineered correction its “Measured anchor.” This is incorrect
as written. The GPS interface specification supplies an engineering fractional
frequency offset, not a direct measured clock-rate record. The retained
NAVSTAR-4 metadata describes per-pass estimates made with reference ephemeris,
ionosphere, troposphere, Earth-rotation, and relativistic corrections; it has
no retained series or uncertainty table. It is `MODEL_PROCESSED_OBSERVATION`,
not an uncorrected anchor.

The supported replacement is: a documented GPS frequency-offset configuration
can motivate a pre-registration, but cannot itself be a measured physical
clock-rate datum.

The interface value is `Δf/f = -4.4647e-10`. Configuration arithmetic only:

```text
(-4.4647e-10) × 86,400 s/day × 1,000,000 μs/s = -38.575008 μs/day
```

Its compensation magnitude is `38.575008 μs/day`, not an independently
measured uncorrected rate. It differs from GOM20's `38.7 μs/day` target by
`0.124992 μs/day`, exceeding the seed's `±0.1 μs/day` tolerance. This is a
target-definition failure, not a failure of SDT: the configured value and the
claimed physical observable are not yet defined as the same quantity.

## Supplied mechanism amendment

The model author supplied and the audit recorded the required recovery chain in
`GOM20_GPS_MECHANISM_AMENDMENT_01.md`:

1. use observed polar radius for Earth `koppa` derivation;
2. include baryon-count/volume exclusion;
3. include separate spation-shell exclusion;
4. apply inverse-square radial fall-off; and
5. apply the movement budget.

All five ingredients are present in the deterministic audit output. They do
not yet define a computable prediction. Their units, normalization, signs,
reference radius, ordering/composition, and uncertainty propagation remain
unspecified. In particular, no mean-radius substitution is permitted for a
future `koppa` calculation; the observed polar-radius source and epoch must be
frozen before numerical work begins.

## Mechanism conflict still open

GOM20 does not state the exact signed composition yielding
`dτ_sat/dτ_ground`, a coordinate time and frame, ground-station velocity,
eccentric-orbit treatment, or direct-data uncertainty model.

It also does not select between two canonical depth-rate implementations:

```text
gravitational_time_dilation(z, R, r) = sqrt(1 - z R/r)
depth_closure::clock_rate(z)          = 1 - z
```

With `z_p R_p = koppa`, the associated satellite-to-ground depth factors are,
to first order,

```text
sqrt[(1 - koppa/r_sat) / (1 - koppa/r_ground)]
    = 1 + 1/2 × koppa × (1/r_ground - 1/r_sat) + O(koppa²)

(1 - koppa/r_sat) / (1 - koppa/r_ground)
    = 1 +     koppa × (1/r_ground - 1/r_sat) + O(koppa²)
```

They differ by a factor of two at leading order. The amendment's new exclusion
and shell ingredients may resolve this only after their exact equations and
composition are supplied. No external gravity framework is used to establish
this ambiguity.

## Audit instrument correction log

The first scan falsely marked a coordinate time as present because `eci` occurs
inside “specification” and “precision.” A first repair over-escaped the
word-boundary regex; a second treated the trailing space in `z = ` as a word
boundary before the Greek `koppa` symbol. The final scanner guards a phrase
edge only if that edge is alphanumeric. It now correctly reports the depth
relation as present and the coordinate-time definition as absent.

Run `python gom20_gps_anchor_audit.py` to reproduce the source hashes,
configuration arithmetic, amendment checks, and fail-closed classification in
`gom20_gps_anchor_audit_results.json`.

## Gate for the next calculation

1. Supply a dimensionally complete signed equation that combines polar-radius
   `koppa`, baryon-volume exclusion, spation-shell exclusion, inverse-square
   fall-off, and movement budget into `dτ_sat/dτ_ground`.
2. Freeze observed polar radius, baryon count, volumes, state vectors, ground
   station, time coordinate, and their uncertainties.
3. Pre-register a signed mean-rate and periodic eccentric-orbit prediction
   before retrieving or parsing a direct clock-comparison series.
4. Retrieve raw or separately retained clock phases, propagation/equipment
   corrections, calibration lineage, and uncertainty budget; compare SDT
   directly with those observations and retain negative results.

Until then, neither `±0.1 μs/day` reproduction nor GPS-based falsification is
supported.
