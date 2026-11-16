# Chapter 2 — pre-registration of the worked-example instruments

Registered 2026-11-03, before `Textbook/examples/ch02_spherical_and_dodecardinal_geometry.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object under test: `sdt/sphere_frame.hpp` (`sdt::sphere::Locus`, `angular_distance`, `distance_to`, `bearing`, `offset_direction`, `relative_locus`, `step_locus`) and the seat geometry `sdt::laws::atomic::dodecardinal::make_seats` of `laws.hpp`. References are built so that the true value follows from the stored double-precision inputs without a higher-precision library: pairs on one meridian (separation $|\theta_A-\theta_B|$ or $\theta_A+\theta_B$, evaluated exactly by an error-free sum) and symmetric solids with known angles. The instrument may use Cartesian arrays internally as a reference route; the engine under test uses none.

Let $u=1.11\times10^{-16}$ (half the double-precision unit roundoff, rounding to nearest).

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | octant triangle: poles and equator points $(\theta,\phi)=(0,\cdot),(\pi/2,\,0{+}),(\pi/2,\pi/2)$: all three sides $\pi/2$, all three angles $\pi/2$, area (spherical excess) $\pi/2$ sr | $10^{-14}$ |
| V2 | `Locus` normalisation: $(1,\pi+0.3,0.5)\to\theta=\pi-0.3,\ \phi=0.5+\pi$; $\phi=0\to2\pi$; $\phi=-1\to2\pi-1$; construction with radius $0$, $-1$, NaN or infinity throws `std::domain_error` | exact / $10^{-15}$ |
| V3 | Van Oosterom–Strackee solid angle of the octant triangle $=\pi/2$; of the triangle (pole, equator point at azimuth 0, equator point at azimuth $2\pi/3$) $=2\pi/3$ (its excess equals the angle at the pole), the second also by the engine's bearings | $10^{-14}$ |

*Correction before the first run (2026-11-03):* the second clause of V3 as first written named the triangle (pole, equator $0$, equator $\pi$), which is degenerate (its three points are coplanar with the centre). It was replaced by the triangle above. No run existed when the correction was made.

If V1–V3 fail the instrument is faulty; no T-result is quoted until it is repaired and re-validated.

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | small separations. Pairs on one meridian, $\delta=\theta_B-\theta_A\in\{10^{-2},10^{-4},10^{-6},10^{-8},10^{-10}\}$ (exact in doubles). The engine's `angular_distance` returns $\delta$ | relative error $\le10^{-14}$ for every $\delta$. The naive $\arccos(\cos\theta_A\cos\theta_B+\sin\theta_A\sin\theta_B\cos\Delta\phi)$ must show relative error $>0.1$ at $\delta=10^{-8}$ | yes — a naive form that stays accurate would remove the engine's stated reason for the half-angle form |
| T2 | near-antipodal separations. Pairs with $\Delta\phi=\pi$ (opposite meridian half-planes) and $\theta_A+\theta_B=\pi-\varepsilon$, $\varepsilon\in\{10^{-2},10^{-4},10^{-6},10^{-8},10^{-10}\}$. True $\varepsilon$ from an error-free sum of the stored $\theta$'s and a two-part $\pi$ | engine relative error in $\varepsilon$ at most $50\,u/\varepsilon$ for every case. The pure haversine form $2\arcsin\sqrt{h}$ and the naive arccos form must each show relative error $>0.1$ in $\varepsilon$ at $\varepsilon=10^{-8}$ | yes — the engine's switch to the five-part form is the claim; a haversine that stays accurate near $\pi$ would reject it |
| T3 | chord conditioning. Two loci of equal radius $r=6.371\times10^6$ m, $\delta=10^{-9}$ rad apart in $\theta$. `distance_to` vs $2r\sin(\delta/2)$; naive $\sqrt{r_1^2+r_2^2-2r_1r_2\cos\psi}$ | engine relative error $\le10^{-13}$; naive relative error $>0.1$ | yes |
| T4 | spherical triangle area by three routes (angles from the engine's bearings; L'Huilier from the engine's sides; Van Oosterom–Strackee from Cartesian vectors) for 40 pseudo-random non-degenerate triangles (fixed generator, minimum area 0.05 sr, longest side $<3$ rad) | the three areas agree to $10^{-10}$ in every triangle | yes |
| T5 | `relative_locus` then `step_locus` returns the target: 200 pseudo-random pairs of loci with radii in $[0.5,2]$, separation distance at least $10^{-3}$ | distance from the recovered locus to the target $\le10^{-10}$ in every case | yes |
| T6 | dodecardinal set (this edition's definition: the 12 vertices of a regular icosahedron as directions). Per vertex: 5 neighbours at $\arccos(1/\sqrt5)=63.4349488^\circ$, 5 at $116.5650512^\circ$, 1 antipode at $180^\circ$; the face-centre direction lies $37.3774^\circ$ from each of its three vertices; for the contact shell of Chapter 1 the cap of half-angle $30^\circ$ ($\sin\eta=1/2$) about each vertex does not overlap its neighbours and the twelve cover the fraction $6(1-\sqrt3/2)=0.803848$ of the sphere | multiplicities exact; angles within $10^{-12}$ rad; coverage within $10^{-13}$ | yes — overlap (minimum separation $\le60^\circ$) or a wrong multiplicity rejects |
| T7 | engine seat geometry. For $n=10$ electrons, `atomic::dodecardinal::make_seats` produces 10 seats; the distinct pairwise direction angles among the 8 distinct directions (poles and six ring seats) are $60^\circ$ (6 pairs), $90^\circ$ (12), $120^\circ$ (6), $180^\circ$ (4: the pole pair and the three ring antipodes) | exact multiset | yes |

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch02_spherical_and_dodecardinal_geometry`

## Dated addition: the source definition of the dodecardinal set (2026-11-09)

After run 1 the Helix-side header that defines the term was found (`hsml_cpp/core/dodecardinal_frame.hpp`: "the 1+12 cuboctahedral geometry: 12 cardinal direction points equidistant around 1 center point", the Vector Equilibrium; listed as superseded architecture in the Helix repository). The definition used in the first draft of the chapter, the twelve icosahedron directions, is therefore not the source's. T6 and T7 (run 1) stand as tests of the icosahedral set (the contact-shell comparator of Chapter 1) and of the engine's seat geometry. T8 is added for the source's set, with predictions registered before the test is coded.

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T8 | cuboctahedral set: the twelve directions $(\pm1,\pm1,0)/\sqrt2$ and permutations, built as loci. Per direction: 4 others at $60^\circ$, 2 at $90^\circ$, 4 at $120^\circ$, 1 at $180^\circ$ (cosines $\tfrac12,0,-\tfrac12,-1$), none other. Minimum separation exactly $60^\circ$, so the $30^\circ$ caps of the contact shell are tangent and do not overlap; the covered fraction equals $6(1-\sqrt3/2)=0.803848$ (as for the icosahedral set). The gaps between caps are 14 holes: 8 triangular, centred on $(\pm1,\pm1,\pm1)/\sqrt3$, each $\arccos(2/\sqrt6)=35.2644^\circ$ from three vertices; 6 square, centred on the axes, each $45^\circ$ from four vertices | multiplicities exact; separations within $10^{-12}$ rad; coverage within $10^{-13}$; hole angles within $10^{-12}$ rad; hole counts 8 and 6 | yes — a different multiplicity or a minimum separation below $60^\circ$ rejects |

The run with T8 added is run 2; the criteria of V0–V3 and T1–T7 are unchanged.
