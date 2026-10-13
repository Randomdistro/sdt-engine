# PPT07 — Proton/Electron Displacement-Volume Ratio

> **Author:** J. C. Harvey, Melbourne
> **Status:** RESOLVED CONSTRUCTION — shared-input, not an independent prediction
> **Engine:** `sdt::laws::law_VI::mass_ratio`

## Claim

Law IV identifies the mass ratio with the displaced-volume ratio:

\[
\frac{m_p}{m_e}=\frac{V_{\rm disp,p}}{V_{\rm disp,e}}.
\]

The physical construction uses the point electron's finite-width closed path at
the hydrogen Bohr seat as the unit volume. The proton is the same displaced
volume packed into the W=3 torus seated at \(R_p=0.8414\ {\rm fm}\).

## Electron tube

Let \(b_e\) be the physical radius of the point electron and
\(a_0\) the Bohr radial distance. The electron returns to its complete
orientation after 720 degrees, so its closure length and swept volume are

\[
L_e=4\pi a_0,\qquad
V_e=\pi b_e^2L_e=4\pi^2a_0b_e^2.
\]

The point body follows the occlusion profile

\[
\varkappa_H=\alpha^2a_0=r_e,\qquad
v(r)=c\sqrt{\frac{r_e}{r}}.
\]

Consequently

\[
v(a_0)=\alpha c=2.1876913\times10^6\ {\rm m\,s^{-1}},
\]

and at the proton seat

\[
v(R_p)=c\sqrt{\frac{r_e}{R_p}}=1.830057\,c.
\]

## Proton torus

The packing count is

\[
N=6\pi^5=1836.1181087.
\]

Conserving \(N\) electron closure volumes into a ring torus of major radius
\(R_p\) and tube radius \(b_p\) gives

\[
NV_e=2\pi^2R_pb_p^2,
\qquad
\frac{b_p}{b_e}
=\sqrt{\frac{2Na_0}{R_p}}
=15197.2363.
\]

Using the engine's provisional point-body radius
\(b_e=3.0\times10^{-20}\ {\rm m}\) gives

\[
b_p=0.455917\ {\rm fm}<R_p,
\]

so the packed volume forms a valid ring torus. The provisional body width
changes the absolute minor radius but cancels exactly from \(V_p/V_e=N\).

## Scope

- **Resolved:** the geometric meaning of the mass ratio as conserved
  point-electron closure-tube volume packed into the proton torus.
- **Computed correspondence:** \(6\pi^5\) differs from the measured
  \(m_p/m_e\) by \(-18.8245\) ppm.
- **Not claimed:** an independent prediction of the packing count. The count
  is shared input to this construction.
- **Still owed:** the absolute W=1 point-body width. This does not reopen the
  dimensionless volume ratio because the width cancels.

The bare W=1/W=3 centreline and ropelength ratios are order unity and therefore
do not generate 1836. They are not the displacement-volume operator used here.
