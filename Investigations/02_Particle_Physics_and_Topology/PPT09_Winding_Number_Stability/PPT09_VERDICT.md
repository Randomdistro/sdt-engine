# PPT09 — Winding Number Stability

> **Author:** James Christopher Tyndall, Melbourne
> **Status:** knot classification COMPUTED; dynamical stability OPEN
> **Instrument:** `ppt09_occlusion_integral.cpp`

## Direct result

The tested first-order model gives

\[
\frac{E(1,2)}{2E(1,1)}=1.000000.
\]

It therefore supplies no energy preference for W=2 reconnection. It does not compute a barrier, lifetime, decay direction, or a W={1,3}-only stable spectrum.

## Valid result

The knot classification is independent of that failed energy discriminator:

- `(1,1)`: unknot, Alexander polynomial `1`;
- `(1,2)`: unknot, Alexander polynomial `1`;
- `(2,3)`: trefoil, Alexander polynomial `t⁻²−t⁻¹+1−t+t² != 1`.

This establishes a topological distinction between the proton trefoil and the electron unknot. A reconnection is a cut-and-rejoin event, so the invariant alone does not prove a no-decay result.

## Remaining debt

A full wake/boundary occlusion calculation must provide the reconnection energy curve, barrier, dissipation law and lifetimes for W=2, W=3 and higher branches. Until then, W=2 exclusion and the W={1,3}-only claim remain open.
