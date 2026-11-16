# Chapter 24 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch24_spin_parity_and_nuclear_moments.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. What a frozen geometric configuration does and does not say about moments, parity and spin. The engine stores for the 287 natural nuclides only $(Z,A)$ and no spin, parity or moment labels; it stores a few moments in nuclear magnetons, a unit this book does not use, and one quadrupole anchor. This chapter therefore executes the structural statements of the plan, not a comparison with labels: (a) for a weighted point set $\{(w_i,\vec r_i)\}$ about its weighted centre, the rotation-invariant multipole content $I_l=\sum_{i,j}w_iw_j\,r_i^lr_j^lP_l(\cos\gamma_{ij})$ (proportional to $\sum_m|q_{lm}|^2$ by the addition theorem; it vanishes if and only if every rank-$l$ moment vanishes) for the module configurations and for symmetric solids; (b) an accidental cancellation: a non-spherical, non-cubic set with $I_2=0$ and $I_4>0$, so that a zero quadrupole-like moment does not prove spherical geometry; (c) the rotational average of the traceless second-moment tensor over all orientations vanishes exactly for any intrinsic shape, so a zero observed value for a spin-zero state carries no shape information; (d) inversion invariance of frozen labelled configurations (kinds preserved), which fixes what a parity assignment from geometry would need. No observable is compared with a measured label.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | traceless second-moment tensor $\sum w(3\vec r\vec r^{\,T}-r^2I)$ of two unit weights at $(0,0,\pm1)$ is $\mathrm{diag}(-2,-2,4)$; and the invariant $I_1$ about the centroid of any two-point set with equal weights is 0; and $P_2$, $P_3$, $P_4$ at $\cos\gamma=1$ are all 1, at $\cos\gamma=0$ are $-1/2,0,3/8$ | $10^{-14}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | multipole pattern of symmetric solids, equal weights, vertex sets about the centroid; "zero" means $I_l\le10^{-12}(\sum_iw_ir_i^l)^2$ and "nonzero" means $\ge10^{-6}(\sum_iw_ir_i^l)^2$. Registered: tetrahedron: $I_1=I_2=0$, $I_3>0$; cube: $I_1=I_2=I_3=0$, $I_4>0$; octahedron: $I_1=I_2=I_3=0$, $I_4>0$; icosahedron: $I_1=\ldots=I_5=0$, $I_6>0$ | as stated | yes — a nonzero $I_2$ on a cubic or icosahedral set rejects the symmetry statement |
| T2 | accidental cancellation. Two points at $(0,0,\pm1.5)$ with weight 1 and four points at $(\pm s,0,0),(0,\pm s,0)$ with weight 0.5, $s^2=4.5$ (so that $w_ah^2=w_rs^2=2.25$): $I_2=0$ (zero in the sense of T1), $I_4>0$, $I_3=0$; the set is not cubic ($h\ne s$). The module configurations are also classified: alpha ring (square, side 2) $I_2>0$, $I_3=0$; two-sphere pair at distance 2 $I_1=0$, $I_2>0$; bent triton (proton at the origin, neutrons at $(2,0,0)$ and $(0,2,0)$, equal weights, about the centroid) $I_2>0$, $I_3>0$ | as stated | yes |
| T3 | orientation average. For the traceless tensors of the alpha ring, the pair and the bent triton, the average over all orientations (Euler quadrature: 8 uniform points in each of $\alpha,\gamma$ and 4-point Gauss–Legendre in $\cos\beta$, exact for the quadratic dependence on the rotation) is the zero tensor | each component $\le10^{-13}$ of the tensor's largest component | yes |
| T4 | inversion. A labelled point set (kinds p/n, equal weights) is inversion-invariant if inversion about its centroid maps the set to itself with kinds preserved. Registered: alpha ring yes; two-sphere pair (p,n) no; bent triton n–p–n at $90^\circ$ no; linear triton n–p–n ($180^\circ$) yes; icosahedral shell of 12 n about a p yes | exact | yes |

Reported, not criteria: the values of $I_l$ for each set.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch24_spin_parity_and_nuclear_moments`
