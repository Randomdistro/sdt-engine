# GOM20 Canonical Clock-Mechanism Readiness Audit - 2026-08-09

**Status:** `PENDING_MECHANISM`; empirical SDT verdict `UNADJUDICATED`.
**Scope:** canonical-model consistency and prediction readiness only. No
experimental or observational datum is used to accept or reject a theory.

## Fixed source basis

The source hashes and available interfaces are frozen in
`GOM20_CANONICAL_EQUATION_INVENTORY_2026-08-09.md`. The existing GPS audit's
source hashes remain valid and its direct-observation gate remains false. This
audit adds no numerical target and does not alter the canonical sources.

## Clock-law fork

Two canonical functions give different local rates for the same depth variable:

```text
law_V::gravitational_time_dilation(z, R, r) = sqrt(1 - z R / r)
depth_closure::depth(koppa, r)               = koppa / r
depth_closure::clock_rate(z)                 = 1 - z
```

With `koppa = z_p R_p`, the first function becomes `sqrt(1 - koppa/r)`.
For two radii, the candidate satellite-to-ground ratios are therefore:

```text
A = sqrt[(1 - koppa/r_sat) / (1 - koppa/r_ground)]
B =      (1 - koppa/r_sat) / (1 - koppa/r_ground)
```

Their small-depth leading terms differ:

```text
A = 1 + (1/2) koppa (1/r_ground - 1/r_sat) + O(koppa^2)
B = 1 +       koppa (1/r_ground - 1/r_sat) + O(koppa^2)
```

This is an internal model fork, not a comparison to an external framework. The
mechanism amendment does not choose a branch or provide a derivation that makes
the additional exclusion and movement terms select one. A unique GPS prediction
cannot be formed while both remain admissible.

## Units and normalization audit

| Required ingredient | Existing canonical quantity | Missing definition that prevents a clock ratio |
|---|---|---|
| Polar-radius Earth `koppa` | `koppa_Earth = v_Earth^2 R_Earth/c^2`, with `R_Earth = 6.371e6 m` | No polar-radius identifier, source, epoch, uncertainty, or replacement rule; mean-radius constant cannot be substituted silently |
| Baryon count and volume exclusion | `N_baryons(koppa)` is dimensionless; `V_disp_from_mass(m)` returns m^3 | No Earth composition/mass-to-baryon mapping, no Earth volume input, and no dimensionless mapping from their exclusion contribution to clock rate |
| Spation-shell exclusion | `State28D` has shell state fields with m^3 and m^3/s units | No Earth shell geometry, shell state, radial field, sign, normalization, or clock coupling |
| Inverse-square fall-off | No GOM20-specific function | A literal `1/r^2` has inverse-area units; the equation must state the length/area normalization, reference radius, near-surface regularization, and which term it multiplies |
| Movement budget | `v_circ^2 + v_trans^2 = c^2` | No identification of the satellite, ground, shell, or radial-flow velocity component; no conversion from the velocity partition to the chosen clock-rate branch |

The available canonical expressions cannot be added as written: they return a
mixture of length, volume, velocity, and dimensionless rate. No signed,
dimensionally closed expression for `d tau_sat / d tau_ground` exists in the
frozen source set.

## Initial conditions and frame audit

The required mechanism amendment and deterministic audit leave the following
inputs undefined: polar-radius reference surface and epoch; baryon count and
volume provenance; Earth shell geometry/state; ground-station location and
velocity; satellite state vector and eccentric anomaly; coordinate time scale;
signal/clock comparison convention; reference radius; and propagation of input
uncertainties. The current engineering offset is not a replacement for these
initial conditions because it is not a direct clock-comparison series.

## Identifiability result

Even if a direct clock series were supplied today, the model contains at least
these unresolved choices: the clock-law branch; two exclusion functions; shell
field normalization; inverse-square normalization and regularization; signs and
composition order; velocity assignment; reference radius; and frame/time-scale
mapping. They can change both magnitude and sign of a prediction. A single GPS
mean offset cannot identify them, and fitting them after inspection would erase
falsifiability.

The correct result is `NON_IDENTIFIABLE_BEFORE_PREDICTION`, not a physical
failure. No SDT parameter is estimated, no standard-model prediction is used,
and no observational residual is calculated.

## Required author-supplied specification

Before data retrieval, provide one signed equation for
`d tau_sat / d tau_ground` and a symbol table that fixes:

1. every term's units, sign, normalization, and reference radius;
2. the polar-radius source, epoch, uncertainty, and how it enters `koppa`;
3. the baryon/volume and shell-exclusion functions and their coupling to depth;
4. the exact inverse-square operation and its regularization;
5. the movement-budget velocity components and selected canonical clock law;
6. coordinate time scale, frames, ground/satellite state conventions, and
   eccentric-orbit phase rule; and
7. all free constants, their prior values, and a rule prohibiting post-data
   tuning.

Once supplied, freeze the input sources and pre-register a blind mean-rate plus
periodic-orbit prediction against a direct uncertainty-bearing clock series.
Until then, the GPS branch is not empirically testable.

## 2026-08-09 canonical-authority correction

The earlier `Clock-law fork` section correctly reported that both routines are
textually present, but incorrectly treated that coexistence as an unresolved
equal-authority choice. That inference is withdrawn. It did not trace the
repair marker or compiled consumers before classifying the public header.

The frozen authority sources are `Engine/include/sdt/laws.hpp`
(`ae41f3cb12e567cb90b5518795e62da1dc7fa516536739c56a7fcc54d255835b`),
`GOM22_ASSESSMENT_2026-07-30.md`
(`2361629a18296d7bef4009f4118ac3f2e07f9d5b4dc41f96629c264fd0356de5`),
and `Benchmarks/B01_B25/benchmarks_suite.cpp`
(`ec33026c916a051731a2ceabdfe9559c5e3137a1c3717135a7f0d24ed3c981bf`).
GOM22 explicitly records that the linear clock rate was *applied to canon*;
the linear routine has two compiled-source callers, while an exact qualified
call census over `Benchmarks`, `Compiler`, `Experiments`, `Investigations`,
`Papers`, `Theory`, `Laws`, `Engine`, and `Release` finds no caller of
`law_V::gravitational_time_dilation`.

Therefore the corrected source classification is
`REPAIRED_LINEAR_ENGINE_DEFAULT_WITH_GOM20_BINDING_ABSENT`. The square-root
routine remains a stale public source-hygiene risk, not a demonstrated active
GOM20 branch. This correction is a source-authority audit only; it does not
use any observational datum to select a clock law.

The GPS prediction remains non-identifiable. The GOM20 amendment does not bind
its proposed baryon-volume, shell, inverse-square, and movement-budget terms to
the repair-marked linear rate, and it still omits the dimensional composition,
normalizations, state definitions, frames, initial conditions, and a qualified
direct clock series. Thus the required author-supplied equation in the section
above remains the next gate.
