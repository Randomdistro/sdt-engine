# FLM15 Pre-registration — Influx-Phase Resistance Ratio

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-14  
**Status:** frozen before instrument construction

## Question

Does the linear response of the surrounding phase field to translation of a
`W=3`, `(2,3)` trefoil predict its resistance relative to a `W=1` unknot,
without consuming either particle mass?

## Frozen ontology

Mass is the coefficient of resistance supplied by the isotropic convergent
influx when a persistent form changes vector. Law IV supplies the common
conversion from engaged phase volume to mass:

```text
m = Phi V_disp / (3 l_P^3 c^2)
```

The common influx, dimensional scale, and isotropic `1/3` cancel from a
W=3/W=1 ratio. `V_disp_e`, `V_disp_p`, exclusion radii obtained from measured
masses, and measured particle masses are forbidden forward inputs.

Law-IV traction `tau=1/3` is not proton gear-slip traction `T=12`.

## Frozen functional

For a translated defect `phi_W(x-X)`:

```text
d_t phi = -v_a d_a phi
K_ab(W) = integral d_a(phi_W) d_b(phi_W) dV
J_W = trace(K_W)/3
ratio = J_3/J_1
```

`K` is the curvature of field reorganisation energy with translation
velocity. Static stiffness, translation resistance, and any phase-locked wake
volume are separate ledgers.

## Geometry

- W=1: unit circular unknot.
- W=3: standard `(2,3)` torus-knot filament.
- Filament phase gradient: regularised Biot-Savart line integral.
- Common circulation quantum in the primary comparison. A separate `W`
  circulation-amplitude control is reported but cannot be selected after the
  run.
- Matched core radius, box, quadrature points, and filament discretisation.

The trefoil aspect ratio is scanned over a frozen range; no point is selected
using a hidden mass target.

## Instrument gates

Before opening the blind ratio:

1. isotropic directional average reproduces `|grad(phi)|^2/3`;
2. circular `K_xx=K_yy` within 3%;
3. tensor eigenvalues are rotation invariant within 3%;
4. doubling circulation gives stiffness ratio 4 within 2%;
5. estimates are finite and positive;
6. quasi-Monte-Carlo repeat spread is below 10%;
7. source scan confirms forbidden names/numbers do not enter the solver.

## Frozen scans

```text
filament segments = {96, 192, 384}
volume samples    = {32768, 65536, 131072}
box half-size     = {3, 5, 8} core radii beyond filament extent
core radius       = {0.08, 0.12, 0.18} in unit major-radius coordinates
trefoil minor/major ratio = {0.35, 0.50, sqrt(2/3), 0.90}
orientations      = identity plus two fixed rotations
```

The primary sealed estimate is the median of converged runs at 192 segments,
65536 samples, core 0.12, box padding 5, across all frozen aspect ratios and
orientations. Full ranges remain visible.

## Outcome rules

- `PHASE_RESISTANCE_RATIO_COMPUTED`: controls pass and a finite ratio is sealed.
- `SIMPLE_PHASE_STIFFNESS_EXCLUDED_AS_LARGE_WAKE`: converged ratios remain
  below 100.
- `WAKE_BOUNDARY_UNDERDETERMINED`: no plateau exists or a lock threshold is
  required.
- `INSTRUMENT_FAIL`: analytic controls fail.

No proximity to any post-run comparison changes the instrument grade.

## R4 benchmark-closure freeze (2026-08-14)

The R4 extension is downstream of the already frozen R0–R3 scan. Its forward
call graph is:

```text
FLM07 glancing relation cos(theta)=k(r)
  -> relay-capacity excess max(0, |cos(theta)|/k(r)-1)
  -> angular lock fraction
  -> V_eng = integral(lock_fraction dV)
  -> Resistance = (P_conv/3) V_eng
  -> delta_Resistance_sync = (P_conv/3)(V_joint-sum(V_parts))
  -> benchmark-facing applications
  -> comparison values
```

Numeric gates, frozen before the R4 implementation:

1. Angular quadrature recovers the analytic lock fraction to absolute error
   `<1e-6`; the existing isotropic `1/3` control remains `<1%`.
2. Radial quadrature of the spherical control agrees with its analytic engaged
   volume to relative error `<1e-5` and scales as the cube of its supplied
   boundary radius to `<1e-10`.
3. Two non-overlapping bodies give
   `|delta_Resistance_sync|/sum(Resistance_parts)<1e-6`; coincident identical
   bodies give the analytically expected union-volume limit to `<1e-5`.
4. With locking disabled, the frozen R0–R3 reference scan must reproduce its
   sealed `J3/J1` median within `0.5%`; R4 may not rewrite that result.
5. The lock boundary is derived only from the glancing equality and the
   supplied mechanical boundary. It must be byte-for-byte unchanged when all
   particle masses, benchmark targets and post-run comparison files are
   absent.

Body-source aliases (`G`, source `M`, `GM`, `mu`, or `u=GM`) are forbidden in
the forward solver. A mechanical boundary radius, geometry, movement,
composition count or timing datum may enter only with item-level provenance.
