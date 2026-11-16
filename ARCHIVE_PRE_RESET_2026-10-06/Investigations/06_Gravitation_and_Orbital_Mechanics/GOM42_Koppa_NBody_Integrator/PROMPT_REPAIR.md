# GOM42 Repair Pre-Registration — Stable Lagrange Fixture

**Author:** James Christopher Tyndall, Melbourne  
**Recorded:** 2026-08-15, after Run 1 and before repair instrumentation

## Run 1 finding

Run 1 passed V0, V1, V2, V4, V5 and V6. V3 used three equal sources for a
20-period equilateral orbit and failed with maximum side drift 2.11148.

The equal-source equilateral solution is an exact trajectory but is linearly
unstable. It violates the Gascheau stability condition

\[
\frac{\kappa_1\kappa_2+\kappa_2\kappa_3+\kappa_3\kappa_1}
{(\kappa_1+\kappa_2+\kappa_3)^2}<\frac1{27}.
\]

Roundoff and truncation perturbations therefore grow over the registered
20-period run. That makes the fixture unsuitable as a long-run integrator
validation. Run 1 remains rejected; its result is not overwritten.

## Frozen repair

The V3 threshold, duration and timestep remain unchanged. Only the known-answer
fixture is replaced:

- \(\kappa_1=2.5\times10^{-3}\,\mathrm m\)
- \(\kappa_2=2.5\times10^{-6}\,\mathrm m\)
- \(\kappa_3=2.5\times10^{-9}\,\mathrm m\)
- side length \(1.5\times10^9\,\mathrm m\)
- \(\omega=c\sqrt{(\kappa_1+\kappa_2+\kappa_3)/s^3}\)
- vertices translated to the koppa-weighted barycentre before tangential
  velocities are assigned

This source ratio satisfies the stability condition before the trajectory is
run. The registered gates remain:

- 20 periods
- \(\Delta t=P/4000\)
- maximum side-length drift \(\le10^{-4}\)
- barycentre drift \(\le10^{-10}\) of the side length

All other V0–V6 fixtures and thresholds remain exactly as in `PROMPT.md`.
