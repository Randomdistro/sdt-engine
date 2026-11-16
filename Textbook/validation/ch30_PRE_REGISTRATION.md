# Chapter 30 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch30_atomic_nuclear_correspondence.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. A proposed structural correspondence $A_{\rm atom}=F(X_{\rm nucleus},X_{\rm electronic},S)$ with scale factors and a rotation. The plan's constraint is that the factors must be predicted or independently fixed; allowing a factor per observable makes any two geometries correspond. The chapter executes (a) the freedom census: how often two unrelated geometries are matched by one global similarity (scale + rotation) and the fact that per-observable factors match everything; (b) the rank content (Chapter 24, $I_l$) of the atomic seat directions of the engine's many-electron construction (`dodecardinal::make_seats`, $N_e=2\ldots10$, directions only) against the nuclear shell directions (T8: cube vertices, T12: icosahedron, T14: cuboctahedron face normals, the octahedron's 8 and the cube's 6), with registered predictions about which rank contents vanish. No isotope or line data are loaded; no scale factor is fitted.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | an exact mirror $Q=sRP+t$ of a 12-point random set (scale $s=2.7$, a fixed rotation, a translation) is recovered by the similarity fit (Horn quaternion method, Jacobi eigenproblem): relative residual and the recovered $s$ | $10^{-12}$ |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | freedom census. For 500 pairs of independent random 12-point sets (fixed generator) the best similarity (one global scale, one rotation, a translation) leaves a median relative residual of at least $0.3$ and at most 1% of pairs reach a residual $\le0.05$. For random positive magnitude vectors of length $N=3,6,12$ the best single global factor leaves a median relative residual of at least $0.3$ (500 pairs each) while factors per observable leave residual exactly 0 (all pairs, identically). Printed: the fractions | as stated | yes — a high chance-match rate under one global similarity rejects the use of such a match as evidence |
| T2 | rank content ($I_l$ of Chapter 24, unit directions, equal weights, about the centroid). Registered: T8, T12, T14 each have $I_1=I_2=0$ (cubic or icosahedral symmetry; $I_3=0$ by inversion symmetry); the atomic seat directions for $N_e=2\ldots10$ have $I_2>0$ for every $N_e$ (an accidental zero would be recorded as a finding); hence no atomic seat set has the rank-2 content of any of the three nuclear shells; the ring-free sets $N_e=2$ (collinear) has $I_2=1$ | exact classification, thresholds as Chapter 24 | yes |

Reported, not criteria: all $I_l$ values for $N_e=2\ldots10$ and the three nuclear shells.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch30_atomic_nuclear_correspondence`
