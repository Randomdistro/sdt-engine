# GOM42 — Koppa N-Body Integrator

**Author:** James Christopher Tyndall, Melbourne  
**Status:** PRE-REGISTERED · INSTRUMENT NOT YET RUN  
**Date:** 2026-08-15

## Question

Can one shared two- or three-dimensional trajectory engine integrate the SDT
koppa acceleration

\[
\mathbf a_i
=c^2\sum_{j\ne i}\kappa_j
\frac{\mathbf r_j-\mathbf r_i}{|\mathbf r_j-\mathbf r_i|^3}
\]

without importing \(G\), source mass \(M\), \(GM\), force softening, or a
target trajectory?

This is a numerical initial-value solver. Passing the gates below does not
constitute a closed-form solution of the general three-body problem.

## Registered inputs

- `sdt::laws::measured::c`
- `sdt::laws::bridge::koppa_per_baryon`
- Per-body baryon count, or the equivalent source length
  \(\kappa=N_b\kappa_b\)
- Initial position and velocity
- Collision radius, used only as an explicit stop boundary

No weighed source mass is an input. Koppa is the sole source strength and is
also the inertial weighting in the conservation diagnostics.

## Instrument

- Pairwise central acceleration evaluated symmetrically
- Velocity-Verlet stepping
- The same `Vec3` state with `z=0` for two-dimensional runs
- No Plummer softening and no hidden minimum denominator
- A step is rejected if two supplied collision boundaries overlap

## Diagnostics

\[
\mathbf P_\kappa=\sum_i\kappa_i\mathbf v_i,\qquad
\mathbf L_\kappa=\sum_i\kappa_i(\mathbf r_i\times\mathbf v_i)
\]

\[
\mathcal E_\kappa
=\frac12\sum_i\kappa_i|\mathbf v_i|^2
-c^2\sum_{i<j}\frac{\kappa_i\kappa_j}{r_{ij}}.
\]

These are koppa-weighted numerical invariants. They are proportional to the
usual mass-weighted invariants by one common conversion and do not introduce
a mass primitive.

## Validation gates

All thresholds are fixed before the implementation is run.

1. **V0 — pair symmetry and dimensions.** For an isolated pair,
   \(\kappa_1\mathbf a_1+\kappa_2\mathbf a_2=0\) to relative
   \(10^{-14}\). Acceleration must scale as \(r^{-2}\).
2. **V1 — circular two-body limit.** Run 100 periods with
   \(\Delta t=P/2000\). Maximum separation drift must be
   \(\le 5\times10^{-5}\); relative energy drift must be
   \(\le 5\times10^{-6}\).
3. **V2 — second-order convergence.** On the same two-body orbit, halving
   the timestep must reduce the final-state error by a factor of at least
   3.5.
4. **V3 — Lagrange equilateral solution.** Three equal koppa sources run
   for 20 periods at \(\Delta t=P/4000\). Maximum side-length drift must be
   \(\le 10^{-4}\), and barycentre drift must be
   \(\le 10^{-10}\) of the side length.
5. **V4 — figure-eight choreography.** With the published dimensionless
   initial state rescaled only by \(L\) and
   \(T=\sqrt{L^3/(c^2\kappa)}\), one period at
   \(\Delta t=P/50000\) must close with RMS position and velocity errors
   each \(\le 2\times10^{-5}\) of their registered scales.
6. **V5 — invariants.** Across V1, V3 and V4, normalized
   \(\mathbf P_\kappa\) drift must be \(\le10^{-11}\) and normalized
   \(\mathbf L_\kappa\) drift \(\le10^{-10}\).
7. **V6 — collision behavior.** A head-on pair must stop at its supplied
   contact boundary. The instrument must not continue through a zero
   denominator.

## Rejection criteria

The instrument is rejected if any gate fails, if a run requires a
case-specific timestep correction, if softening is introduced to rescue a
trajectory, or if any source strength is reconstructed through \(G\), \(M\),
or \(GM\).

## Whole-range rule

Each validation trajectory is executed once at its registered timestep. The
convergence gate alone uses the declared timestep pair; no mid-run adjustment
or body-specific retuning is permitted.
