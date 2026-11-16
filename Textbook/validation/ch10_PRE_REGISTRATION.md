# Chapter 10 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch10_occlusion_geometry.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. (T1, T2) The overlap of two spherical caps of directions, its closed form and the union that replaces a sum of shadows; (T3) the finite-body occlusion force of two spheres in the parallel-ray response model of Chapter 9 (residual R9.6 applies): for a target sphere of radius $R_2$ and a shadowing sphere of radius $R_1$ at centre distance $r$, a direction $\hat n$ at angle $\gamma$ to the axis removes the part $A_{\rm ov}(r\sin\gamma)$ of the target's cross-section, with $A_{\rm ov}(d)$ the overlap area of two discs of radii $R_1,R_2$ at centre distance $d$, and the axial force removed is
$$F=q\int 2\pi\sin\gamma\cos\gamma\,A_{\rm ov}(r\sin\gamma)\,d\gamma=\frac{2\pi q}{r^{2}}\int_0^{\min(R_1+R_2,\,r)}d\,A_{\rm ov}(d)\,\mathrm dd .$$
The prediction registered here: for $r\ge R_1+R_2$ the integral over the whole plane gives exactly $F=q\pi^2R_1^2R_2^2/r^2$ (the convolution identity $\int A_{\rm ov}\,d^2x=\pi R_1^2\cdot\pi R_2^2$), so the Law III form has no finite-body correction down to contact; (T4) the engine's own occlusion quadrature and its seven-circle geometry (`sdt/occlusion.hpp`).

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | planar lens area $A_{\rm ov}(d)$: unit circles at $d=1$ give $2\pi/3-\sqrt3/2=1.2283696986087568$; $d=0$ gives $\pi$; $d\ge2$ gives $0$; $R_1=2,R_2=1,d=0.5$ gives $\pi$ (nested) | $10^{-13}$ |
| V2 | spherical lens closed form: coincident caps give the cap area $2\pi(1-\cos\eta)$; nested caps give the smaller cap; externally tangent caps give $0$; two hemispheres whose axes subtend $90^\circ$, $60^\circ$, $180^\circ$ give $\pi$, $4\pi/3$, $0$ | $10^{-13}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | the spherical-lens closed form equals an independent integration (azimuthal width of cap 2 inside cap 1, integrated in the polar angle about axis 1 with 4000 panels of 24 nodes) for eight configurations $(\eta_1,\eta_2,\delta)$ covering partial overlaps, and an equal-area grid count ($3000\times6000$ cells, centre-point sampling) for three of them | integration within $10^{-5}$ relative; grid within $3\times10^{-3}$ relative | yes — a wrong term in the closed form rejects |
| T2 | union of two shadows. $\Omega_\cup=\Omega_1+\Omega_2-\Omega_\cap$ satisfies $\max(\Omega_1,\Omega_2)\le\Omega_\cup\le\Omega_1+\Omega_2$. For caps of half-angle $5^\circ$ and $3^\circ$ at separations $0^\circ,4^\circ,7^\circ,8^\circ,9^\circ$: strict inequality $\Omega_\cup<\Omega_1+\Omega_2$ for $0^\circ,4^\circ,7^\circ$ (the caps overlap since $\delta<\eta_1+\eta_2=8^\circ$) and equality for $8^\circ$ and $9^\circ$; $\Omega_\cup=\Omega_1$ at $0^\circ$ (nested) | inequalities as stated in every case; the double-counted amount $\Omega_\cap$ is reported | yes |
| T3 | finite-body occlusion force. For $(R_1,R_2)\in\{(1,1),(1,0.2),(3,1),(1,3)\}$ and $r\in\{R_1+R_2,\ 1.05(R_1+R_2),\ 2(R_1+R_2),\ 10(R_1+R_2),\ 100(R_1+R_2)\}$: $F/(q\pi^2R_1^2R_2^2/r^2)=1$ by quadrature of the integral above, split at the breakpoints $\lvert R_1-R_2\rvert$ and $R_1+R_2$. For the unphysical separation $r=0.75(R_1+R_2)$ the ratio is $<1$ (information about the domain) | within $10^{-9}$ for $r\ge R_1+R_2$; ratio $<1$ for $r<R_1+R_2$ | yes — a ratio differing from 1 at any $r\ge R_1+R_2$ would reject the identity |
| T4 | engine: (a) `disc_solid_angle` (fixed 6 x 16 quadrature) against `axial_disc_solid_angle` $=2\pi(1-d/\sqrt{d^2+R^2})$ at $d/R\in\{0.5,1,2,5,10,100\}$ is reported; the quadrature weights sum to $\pi R^2$ within $10^{-14}$; (b) seven-circle geometry: `central_weight` $+6\times$ `outer_weight` $=1$; the seven discs of radius $R/3$ have centres at distance $2R/3$ from the central one and adjacent ring centres $2R/3$ apart (tangent), and the outermost point reaches $R$; their total area is $7/9$ of $\pi R^2$ | (a) weights within $10^{-14}$; reported errors have no criterion except $\le10^{-3}$ for $d\ge R$; (b) each statement within $10^{-14}$ | yes |

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch10_occlusion_geometry`

*Note (2026-11-09, before the first run):* the T2 row was rewritten from a draft sentence that broke off ("equality on the right at 7° … see instrument") to the statement above. No run existed.
