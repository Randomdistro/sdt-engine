# Chapter 2 — Spherical and Dodecardinal Geometry

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 3 November 2026. Notation: $\mathrm{Om}=R/k^2$ and $k=c/v$ as in the production default of `Textbook/NOTATION_LEDGER.md`; they enter Section 2.6 only. Executable companion: `Textbook/examples/ch02_spherical_and_dodecardinal_geometry.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 2.1 The physical question

A statement of SDT locates things: a body, a receiver, a shadow. The location is a fact about the medium. The coordinates that express it are a choice, and a choice can introduce structure the medium does not have: a pole, a seam in the azimuth, a centre where the chart fails. This chapter fixes the geometry in which the later chapters state positions and directions, and separates the quantities that belong to the geometry (separation, solid angle, chord) from those that belong to the chart (the pole, the seam).

The engine states every place as a radius and a direction, a direction as a place of radius 1, and a vector as a place whose radius is its magnitude (`sdt/sphere_frame.hpp`). Nothing in it takes a direction apart into components. The chapter derives the three primitives that carry all of its geometry, tests them where the textbook formulas fail, and defines the symmetric direction sets used in the packing and atomic chapters.

## 2.2 Conventions and premises

* **Locus.** A place is $(r,\theta,\phi)$ with $r>0$, $\theta\in[0,\pi]$ measured from the pole and $\phi\in(0,2\pi]$ about it. A whole turn is $2\pi$ and never $0$. A polar angle past $\pi$ is carried over the pole and the azimuth turned by $\pi$. The radius $r=0$ is refused (test V2: radius $0$, $-1$, NaN and infinity each raise a domain error; $\phi=0$ is stored as $2\pi$; $\theta=\pi+0.3$ becomes $\pi-0.3$ with $\phi$ advanced by $\pi$). The refusal of $r=0$ is a restriction of the data type, not a statement about the medium (Section 2.6).
* **Bearing.** The heading of a great circle at a place: $0$ toward the pole, $+\pi/2$ toward increasing $\phi$.
* **Premise.** Euclidean three-dimensional geometry holds locally across the domain of interest. Chapter 1 showed that for nearest-neighbour relay this is a property of the medium's average structure (residual R1.6); the geometry of this chapter assumes it.

## 2.3 Separation and chord distance

Let $A=(r_1,\theta_1,\phi_1)$ and $B=(r_2,\theta_2,\phi_2)$ and let $\psi$ be the angle between their directions. The law of cosines on the unit sphere gives $\cos\psi=\cos\theta_1\cos\theta_2+\sin\theta_1\sin\theta_2\cos\Delta\phi$. Written with half-angles, using $\cos\psi=1-2\sin^2(\psi/2)$ and $\cos\Delta\theta=1-2\sin^2(\Delta\theta/2)$,

$$\sin^2\frac\psi2=\sin^2\frac{\Delta\theta}{2}+\sin\theta_1\sin\theta_2\,\sin^2\frac{\Delta\phi}{2}. \tag{2.1}$$

The straight distance between the two places follows from the triangle they make with the centre, $d^2=r_1^2+r_2^2-2r_1r_2\cos\psi$. Substituting the half-angle form and collecting the radial difference,

$$d^2=(r_2-r_1)^2+4r_1r_2\sin^2\frac\psi2. \tag{2.2}$$

Both terms are non-negative, so no cancellation occurs between nearly equal large squares of the radii.

**The five-part form.** Place $A$ on the $xz$-plane with unit vectors $\hat a$ (radial), $\hat e_\theta$ (toward increasing $\theta$) and $\hat e_\phi$ at $A$. The unit vector $\hat b$ toward $B$ has the components

$$C=\hat b\cdot\hat a=\cos\theta_1\cos\theta_2+\sin\theta_1\sin\theta_2\cos\Delta\phi,\quad
F=-\hat b\cdot\hat e_\theta=\sin\theta_1\cos\theta_2-\cos\theta_1\sin\theta_2\cos\Delta\phi,\quad
S=\hat b\cdot\hat e_\phi=\sin\theta_2\sin\Delta\phi .$$

Since $\hat b$ is a unit vector, $C^2+F^2+S^2=1$, so $\sin\psi=\sqrt{S^2+F^2}$ and

$$\psi=\operatorname{atan2}\!\big(\sqrt{S^2+F^2},\,C\big). \tag{2.3}$$

The same $S$ and $F$ give the bearing of $B$ from $A$, $\operatorname{atan2}(S,F)$.

**Conditioning.** The three forms (arccos of $C$; the haversine form $2\arcsin\sqrt{h}$ with $h$ the right side of (2.1); the five-part form (2.3)) are the same function in exact arithmetic. In double precision they are not. The instrument built pairs whose true separation follows from the stored inputs without a higher-precision library: pairs on one meridian for small $\psi$ ($\psi=\theta_B-\theta_A$, exact), and pairs on opposite meridian half-planes for $\psi$ near $\pi$ ($\psi=\theta_A+\theta_B$, evaluated by an error-free sum against a two-part $\pi$).

| separation | naive arccos | haversine | engine `angular_distance` |
|---|---|---|---|
| $\delta=10^{-2}$ | $1.4\times10^{-13}$ | exact | exact |
| $10^{-4}$ | $2.6\times10^{-9}$ | exact | exact |
| $10^{-6}$ | $1.8\times10^{-4}$ | exact | exact |
| $10^{-8}$ | $1.0$ (total loss) | exact | exact |
| $10^{-10}$ | $1.0$ | exact | exact |
| $\pi-\varepsilon$, $\varepsilon=10^{-2}$ | $1.1\times10^{-13}$ | $6.7\times10^{-14}$ | $2.2\times10^{-14}$ |
| $10^{-4}$ | $2.6\times10^{-9}$ | $2.9\times10^{-9}$ | $2.2\times10^{-12}$ |
| $10^{-6}$ | $4.4\times10^{-5}$ | $4.4\times10^{-5}$ | $2.2\times10^{-10}$ |
| $10^{-8}$ | $1.0$ | $2.0$ | $2.2\times10^{-8}$ |
| $10^{-10}$ | $1.0$ | $1.0$ | $2.2\times10^{-6}$ |

Table 2.1. Relative error of the separation (small $\delta$ rows) or of $\varepsilon=\pi-\psi$ (near-antipodal rows), executed (tests T1, T2). "Exact" means zero to the last digit.

The pattern is the one rounding predicts. Near $\psi=0$, $\cos\psi=1-\psi^2/2$ and a rounding of size $u\approx10^{-16}$ in the cosine becomes a relative error $u/\psi^2$ in $\psi$: $10^{-4}$ at $10^{-6}$, total loss at $10^{-8}$. The half-angle form works with $\sin(\psi/2)$, which is accurate for small arguments. Near $\psi=\pi$ the haversine form meets the same difficulty from the other side: $h=1-\varepsilon^2/4$ rounds to 1 once $\varepsilon\lesssim10^{-8}$. The five-part form (2.3) has the small sine in the numerator and a cosine near $-1$ in the denominator of the arctangent, so its error is of size $u/\varepsilon$ in the relative error of $\varepsilon$, and the registered budget of $50u/\varepsilon$ was met at every row. The engine uses the haversine value below 1 rad and the five-part value from there up, and the table shows each form being used where it is accurate (`Locus::angular_distance`, `sphere_frame.hpp:59`).

The same care applies to the chord. For two places of radius $6.371\times10^6$ m separated by a nominal $10^{-9}$ rad (the stored polar angles $1$ and $1+10^{-9}$ differ by $1.00000008\times10^{-9}$ rad), (2.2) gives $6.371000527\times10^{-3}$ m, which the engine's `distance_to` reproduces to the last digit; the law-of-cosines form returns $0$ (test T3).

## 2.4 Triangles and solid angle

Three directions bound a spherical triangle. On the unit sphere its area, the solid angle $\Omega$ it subtends, equals its spherical excess:

$$\Omega=A+B+C-\pi. \tag{2.4}$$

Given only the sides $a,b,c$, with $s=(a+b+c)/2$, L'Huilier's formula gives $\tan(\Omega/4)=\sqrt{\tan\tfrac s2\tan\tfrac{s-a}2\tan\tfrac{s-b}2\tan\tfrac{s-c}2}$. Given only the three unit vectors, the Van Oosterom–Strackee form gives $\tan(\Omega/2)=|\hat a\cdot(\hat b\times\hat c)|/(1+\hat a\cdot\hat b+\hat b\cdot\hat c+\hat c\cdot\hat a)$.

The three routes were first validated on triangles with known answers (tests V1, V3). The octant triangle (the pole and two equator points a quarter turn apart) has three sides and three angles equal to $\pi/2$ and area $\pi/2$ sr; the engine's separations and bearings returned each to $1.4\times10^{-16}$ or better. The triangle of the pole and two equator points $2\pi/3$ apart has area $2\pi/3$, equal to the angle at the pole; the bearing route agreed to $2\times10^{-16}$. Applied to 40 pseudo-random triangles (minimum area 0.05 sr, longest side below 3 rad; 42 triples drawn), the excess from the engine's bearings agreed with the Cartesian reference to $1.3\times10^{-15}$ at worst and L'Huilier from the engine's sides to $2.0\times10^{-14}$ (T4). The engine's pair `relative_locus`, `step_locus` recovered the target to $3.1\times10^{-15}$ over 200 random pairs of places (T5).

For a circular cap of half-angle $\eta$,

$$\Omega_{\rm cap}=2\pi(1-\cos\eta). \tag{2.5}$$

A sphere of radius $a$ seen from a centre distance $d>a$ has $\sin\eta=a/d$; the small-angle limit is $\pi a^2/d^2$. The finite-source form precedes any inverse-square approximation (Chapters 9 and 10). Overlapping occulted regions need a union measure, since adding two caps' areas counts the overlap twice.

## 2.5 Dodecardinal sets

**The source definition.** The term is defined in a Helix-side header (`hsml_cpp/core/dodecardinal_frame.hpp`): "the 1+12 cuboctahedral geometry: 12 cardinal direction points equidistant around 1 center point", the Vector Equilibrium. That frame is listed as superseded architecture in the Helix repository. The engine uses the word for a different arrangement, the seat geometry of the multi-electron closure (APS14, `laws.hpp:1565`). This edition takes the source definition and keeps the engine's arrangement under its own description.

**Definition.** The *dodecardinal set* is the set of twelve directions $(\pm1,\pm1,0)/\sqrt2$ and their permutations: the vertices of a cuboctahedron, which are also the nearest-neighbour directions of a face-centred cubic arrangement.

*Proposition 2.1.* Each direction of the dodecardinal set has four others at $60^\circ$, two at $90^\circ$, four at $120^\circ$ and one antipode at $180^\circ$ (cosines $\tfrac12,0,-\tfrac12,-1$). By symmetry each direction owns a cell of $4\pi/12=\pi/3=1.0472$ sr.

**The contact shell as a cover of directions.** Twelve unit spheres touching a central unit sphere have centres at distance 2, so $\sin\eta=1/2$ and each subtends a cap of half-angle $\eta=30^\circ$, $\Omega_{\rm cap}=2\pi(1-\sqrt3/2)=0.84179$ sr (`law_III::solid_angle_cap(1,2)`). For the dodecardinal set the nearest separation is exactly $60^\circ$, so neighbouring caps are tangent: the shell spheres touch, four others each, and the arrangement is rigid. The twelve caps do not overlap and cover

$$\frac{12\,\Omega_{\rm cap}}{4\pi}=6\Big(1-\frac{\sqrt3}{2}\Big)=0.803848 \tag{2.6}$$

of the sphere of directions. The remaining $0.196152$ ($2.465$ sr) lies in fourteen holes: eight triangular holes centred on $(\pm1,\pm1,\pm1)/\sqrt3$, each $\arccos(2/\sqrt6)=35.2644^\circ$ from three vertices ($5.2644^\circ$ beyond the caps), and six square holes centred on the axes, each $45^\circ$ from four vertices ($15^\circ$ beyond the caps). Executed (test T8): every direction showed exactly the multiplicities 4, 2, 4, 1 and no other angle; the worst deviation of any pair angle from $60^\circ$, $90^\circ$ or $120^\circ$ was $4.4\times10^{-16}$ rad; the minimum separation equalled $\pi/3$ to the last digit; the coverage equalled (2.6) to $<10^{-13}$; and the hole counts were 8 and 6 with hole-to-vertex angles within $6.7\times10^{-16}$ rad of the closed forms.

**The icosahedral comparator.** The twelve vertex directions of a regular icosahedron are the other symmetric twelve (Chapter 1, the twelve-around-one shell). Each has five neighbours at $\arccos(1/\sqrt5)=63.4349488^\circ$, five at $116.5650512^\circ$ and one antipode. The nearest separation exceeds $60^\circ$, so the $30^\circ$ caps do not touch and the shell is not rigid; the covered fraction is the same (2.6), now in twenty triangular holes, each centred $\arccos\sqrt{(5+2\sqrt5)/15}=37.3774^\circ$ from its three vertices ($7.3774^\circ$ beyond the caps). Executed (test T6): the multiplicities 5, 5, 1 for every vertex, the neighbour angle to $1.3\times10^{-15}$ rad, the face-centre angle $0.6523581397844$ rad to $3.4\times10^{-16}$ and the coverage to $<10^{-13}$.

Both sets cover the same fraction of directions, because both are non-overlapping arrangements of the same twelve caps. They differ in contact and in symmetry. The cuboctahedral set touches and is the direction set of the face-centred cubic arrangement, whose relay front is anisotropic by $\sqrt2$ (Chapter 1, Table 1.2). The icosahedral set leaves the gap (1.5) of Chapter 1 and is the direction set from which an isotropic, space-occupying network is built (CONDENSA). The project's lattice fork between the two is recorded in Chapter 1; this chapter fixes only the geometry of each.

**The engine's seat arrangement.** For ten electrons `atomic::dodecardinal::make_seats` returns ten seats on eight distinct directions: the two poles, each used by two shells, and a ring of six at $60^\circ$ spacing offset by $\pi/6$. The pairwise angles among the eight distinct directions are $60^\circ$ (6 pairs), $90^\circ$ (12), $120^\circ$ (6) and $180^\circ$ (4: the pole pair and three ring antipodes), and none other (test T7). These are the separations that the resistance table of that header prices (`laws.hpp:1565–1575`); Chapter 29 takes up what they do.

## 2.6 The axis, physical azimuthal motion and the circular branch

The line element is $d\ell^2=dr^2+r^2d\theta^2+r^2\sin^2\theta\,d\phi^2$, so the speed with respect to a declared oscillator count $m$ is

$$v^2=\dot r^2+r^2\dot\theta^2+r^2\sin^2\theta\,\dot\phi^2,\qquad v_\phi=\rho\,\dot\phi,\quad \rho=r\sin\theta. \tag{2.7}$$

The coordinate angle $\phi$ is not a displacement; $\rho\dot\phi$ is. At the pole every azimuth is the same place, and a change of $\phi$ at $\rho=0$ moves nothing. A divergent angular rate does not imply a divergent motion. If $\dot\phi\sim\rho^{-p}$ as $\rho\to0$, then

$$|v_\phi|\sim\rho^{1-p}, \tag{2.8}$$

which tends to zero for $p<1$, to a finite limit for $p=1$ and to infinity for $p>1$. The exponent classifies a geometric limit; no exponent has been assigned to an SDT state.

For the circular branch of the shared law (Chapter 33), with a fixed source $\mathrm{Om}=R/k^2$, the circular speed at reach $r$ is $v_{\rm circ}(r)=c\sqrt{\mathrm{Om}/r}$ and the angular rate along the orbit is

$$\dot\beta=\frac{v_{\rm circ}}{r}=c\sqrt{\mathrm{Om}}\;r^{-3/2}. \tag{2.9}$$

As $r\to0$ the product $r\dot\beta=c\sqrt{\mathrm{Om}/r}$ still diverges, so setting $r=0$ in the circular expression does not turn it into a slowly turning axial path. The requirement $v_{\rm circ}\le c$ confines the branch to

$$r\ge\mathrm{Om}. \tag{2.10}$$

Inside $\mathrm{Om}$ the circular branch does not apply, and a centre-crossing path is a different trajectory class, with a different response law, for which the sources supply only the premise that increasing phase loading arrests movement before a physical infinity develops (Chapter 53). A smooth passage through the centre has finite speed there, even though a centre-based direction is undefined at the instant of crossing: the incoming and outgoing radial directions are antipodal, and a jump in the direction label is not a jump in velocity. A numerical representation of an exact crossing needs a chart centred elsewhere or an event representation, because the engine's `Locus` refuses $r=0$ (V2). That refusal is an implementation restriction.

## 2.7 Shell measures

The volume between radii $r_1<r_2$ is $\tfrac{4\pi}{3}(r_2^3-r_1^3)$. On a sphere of directions, $d\Omega=d\mu\,d\phi$ with $\mu=\cos\theta$, so bands of equal solid angle are bands of equal $\mu$ (Archimedes' hat-box property). The quadratures of Chapter 9 integrate in $\mu$ for this reason. The number of cells at relay distance $d$ from a point is $4\pi d^2$ to leading order (Chapter 4), and on a regular lattice it differs from this by lattice-dependent terms (Chapter 1).

## 2.8 Input ledger and residuals

This chapter's executed values are DERIVED or COMPUTED from geometry alone; no measured input enters. The coverage (2.6) uses `law_III::solid_angle_cap`, a geometric function of the engine.

**Residuals.**

* **R2.1 — the term.** *Dodecardinal* is defined only in a superseded Helix header (the 1+12 cuboctahedral set), and the engine applies the word to a different arrangement (the APS14 polar dyad and six-ring). This edition adopts the source definition and describes the engine's arrangement under its own name. Whether the physical medium's twelve contact directions are the cuboctahedral or the icosahedral set is the lattice fork of Chapter 1 and is open.
* **R2.2 — the centre crossing.** The continuation of a trajectory through $r<\mathrm{Om}$, and the physical content of the arrest premise, are open (Chapter 53).
* **R2.3 — the pole.** All conventions here are chart conventions. Whether a physical axis (a rotation axis) enters a statement is stated where it does; Chapter 58 treats the numerical conditioning at the poles and antipodes.

## 2.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch02_spherical_and_dodecardinal_geometry
```

The criteria of `Textbook/validation/ch02_PRE_REGISTRATION.md` were registered before the instrument existed; the second clause of V3 was corrected before the first run (it had named a degenerate triangle), and the correction is recorded in that file. Run 1 met every criterion (`ch02_run1_output.txt`). After run 1 the source definition of the dodecardinal set (the cuboctahedral 1+12 set) was found, and test T8 for it was registered in a dated addition before it was coded; run 2 (`ch02_run2_output.txt`) repeats V0–V3 and T1–T7 unchanged and adds T8, and met every criterion.

## 2.10 Exercises and answers

**Exercise 1.** Derive (2.2) by the triangle law and by the half-angle identity, and give the limit for equal directions.

*Answer.* The triangle with the centre has sides $r_1$, $r_2$ and angle $\psi$ between them: $d^2=r_1^2+r_2^2-2r_1r_2\cos\psi$. Writing $\cos\psi=1-2\sin^2(\psi/2)$ gives $r_1^2+r_2^2-2r_1r_2+4r_1r_2\sin^2(\psi/2)=(r_2-r_1)^2+4r_1r_2\sin^2(\psi/2)$. For $\psi=0$, $d=|r_2-r_1|$.

**Exercise 2.** Classify the azimuthal speed in (2.8) for $p=\tfrac12,1,\tfrac32$.

*Answer.* $\rho^{1/2}\to0$; $\rho^0=$ constant; $\rho^{-1/2}\to\infty$.

**Exercise 3.** Explain why $r\to0$ in (2.9) differs from a centre-crossing trajectory.

*Answer.* The circular branch imposes a continually turning path set by a source law, with $r\dot\beta\propto r^{-1/2}$. An axial passage is a different path class whose response law must be supplied; the circular expression carries no information about it.

**Exercise 4.** Show $S^2+F^2=\sin^2\psi$.

*Answer.* $\hat a$, $\hat e_\theta$, $\hat e_\phi$ are orthonormal, so the unit vector $\hat b$ has $C^2+F^2+S^2=1$ with $C=\cos\psi$.

**Exercise 5.** Find the solid angle of the cap of a touching sphere in the contact shell, the open fraction of the twelve, and the angle from a square-hole centre to its nearest vertices in the dodecardinal set.

*Answer.* $\sin\eta=1/2$, $\Omega=2\pi(1-\cos30^\circ)=0.84179$ sr; twelve give $10.1015$ sr of $4\pi=12.5664$, a fraction $0.803848$ covered and $0.196152$ open. A square-hole centre is an axis, say $(1,0,0)$; its nearest vertices $(1,\pm1,0)/\sqrt2$ and $(1,0,\pm1)/\sqrt2$ have cosine $1/\sqrt2$, so $45^\circ$, which is $15^\circ$ beyond the $30^\circ$ caps.

**Exercise 6.** Show that the relative error of $\psi$ from $\arccos(C)$ is of order $u/\psi^2$ for small $\psi$.

*Answer.* $C=1-\psi^2/2$, $dC/d\psi=-\sin\psi\approx-\psi$. A rounding error $u$ in $C$ gives $\delta\psi\approx u/\psi$, and $\delta\psi/\psi\approx u/\psi^2$. At $\psi=10^{-8}$ and $u=1.1\times10^{-16}$ this is $1.1$.

## 2.11 Scope

Established in this chapter: the three geometric primitives of the engine (separation, chord, bearing) from their derivations; where each textbook form fails and where the engine's choice is accurate, with executed error tables; the validated equivalence of three routes to a triangle's solid angle; the dodecardinal set of the source (the cuboctahedral 1+12 directions), its pair angles, its tangent contact caps and the open fraction $0.196152$ in fourteen holes, with the icosahedral comparator; and the engine's seat arrangement with its pair angles.

Not established: the physical continuation of a path through $r<\mathrm{Om}$ (R2.2) and the meaning of the sources' term for the seat geometry (R2.1).

*Where it leads.* Chapter 3 gives the relay kinematics that attaches durations to the geometry. Chapter 10 builds the union of occulted regions on the cap of (2.5). Chapter 29 uses the seat directions of Section 2.5. Chapter 58 returns to conditioning, including the poles.
