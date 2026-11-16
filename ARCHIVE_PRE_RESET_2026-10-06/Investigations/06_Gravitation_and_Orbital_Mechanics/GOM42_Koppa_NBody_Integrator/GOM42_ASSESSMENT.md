# GOM42 Assessment — Koppa N-Body Integrator

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-15  
**Assessment:** VALIDATED NUMERICAL INSTRUMENT

## Result

The shared three-dimensional kernel

\[
\mathbf a_i=c^2\sum_{j\ne i}\kappa_j
\frac{\mathbf r_j-\mathbf r_i}{|\mathbf r_j-\mathbf r_i|^3}
\]

and velocity-Verlet implementation passed the registered two-body,
stable-Lagrange, figure-eight, timestep-convergence, invariant and collision
gates. Two-dimensional use is the same state with `z=0`.

No \(G\), source mass \(M\), \(GM\), fitted force coefficient or softening
length enters the instrument.

## Direct results

- Two-body, 100 periods: maximum separation drift
  \(4.934790085\times10^{-6}\); relative energy drift
  \(2.445754710\times10^{-11}\).
- Timestep-halving convergence ratio: 3.999798937.
- Stable Lagrange triangle, 20 periods: maximum side drift
  \(1.233700345\times10^{-6}\); barycentre drift
  \(4.981187318\times10^{-15}\).
- Figure-eight, one period: normalized position closure
  \(5.325127963\times10^{-8}\), velocity closure
  \(6.960871570\times10^{-8}\).
- Maximum normalized momentum drift:
  \(1.014332005\times10^{-14}\).
- Maximum normalized angular-momentum drift:
  \(5.509852986\times10^{-14}\).
- The collision fixture stopped outside the supplied contact boundary.

## Run 1 correction

The first run used three equal sources for a 20-period Lagrange test and was
rejected at V3. Equal-source equilateral motion is an exact solution but is
linearly unstable under the Gascheau criterion, so truncation perturbations
grow over that duration. `PROMPT_REPAIR.md` registered a stable source ratio
before the second run. The threshold, duration and timestep were unchanged.
The rejected capture remains in `gom42_results_run1.txt`.

## Scope

This validates a numerical initial-value solver. It computes trajectories for
specified states; it is not a closed-form solution of the unrestricted
three-body problem and does not establish that the SDT source law is uniquely
selected by the validation trajectories.
