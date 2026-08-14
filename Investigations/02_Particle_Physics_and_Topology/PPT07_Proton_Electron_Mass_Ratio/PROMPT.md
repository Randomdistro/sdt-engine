# PPT07 — Proton/Electron Displacement-Volume Ratio

> **Author:** J. C. Harvey, Melbourne
> **Status:** COMPLETE
> **Engine:** `#include <sdt/laws.hpp>` only

## Objective

Test whether the proton/electron mass ratio has a valid Law-IV displaced-volume
construction when the electron is treated as a finite-width point body on its
720-degree Bohr-seat closure and the proton volume is packed into a W=3 torus
seated at the measured proton charge radius.

## Inputs and provenance

- \(a_0,\alpha,c,R_p,m_e,m_p\): `sdt::laws::measured`.
- \(N=6\pi^5\): declared geometric packing count.
- \(b_e\): symbolic point-electron body radius. Any numerical value is
  provisional and must not affect the dimensionless volume ratio.

The measured \(m_p/m_e\) is comparison-only. It must not enter either volume
formula or the inferred minor-radius ratio.

## Construction

1. Verify the point-electron occlusion profile
   \(\varkappa_H=\alpha^2a_0\) and
   \(v(r)=c\sqrt{\varkappa_H/r}\).
2. Verify \(v(a_0)=\alpha c\).
3. Use the 720-degree closure length \(L_e=4\pi a_0\).
4. Form the swept electron volume
   \(V_e=\pi b_e^2L_e\).
5. Pack \(N\) copies into
   \(V_p=2\pi^2R_pb_p^2\).
6. Solve
   \(b_p/b_e=\sqrt{2Na_0/R_p}\).
7. Require \(V_p/(NV_e)=1\) to floating-point precision.
8. If a provisional \(b_e\) is evaluated, require \(0<b_p<R_p\) for a
   non-self-intersecting ring-torus envelope.

## Negative-control route

Evaluate the bare W=1 and W=3 centreline/ropelength ratios without introducing
the packing count. If those order-unity invariants do not produce 1836, record
that exclusion only for bare winding and ropelength generators; it does not
test the displaced-volume packing construction.

## Gates

- **Volume conservation:** relative residual below \(10^{-12}\).
- **Width cancellation:** \(V_p/V_e=N\) for at least three positive trial
  values of \(b_e\) spanning six orders of magnitude.
- **Bohr velocity:** \(v(a_0)/c=\alpha\) within machine precision.
- **Provenance:** label the result `COMPUTED`, `construction-resolved`, and
  `shared-input`; never label it an independent prediction.
- **Residual debt:** retain the absolute W=1 point-body width as open unless
  independently derived.

The final result is recorded directly in `INVESTIGATION.md`.
