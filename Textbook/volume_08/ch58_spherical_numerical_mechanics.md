# Chapter 58 — Spherical Numerical Mechanics

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: a locus $(r,\theta,\varphi)$ is a place (positive radius and direction); $\psi$ the angular separation of two loci; $\epsilon$ machine precision ($2.2\times10^{-16}$ in double precision, one ulp at 1); $\mathrm{ulp}(\varphi)$ the spacing of representable azimuths. Executable companion: `Textbook/examples/ch58_spherical_numerical_mechanics.cpp`; pre-registration and captured output in `Textbook/validation/`. The instrument consumes the engine's `sdt::sphere::Locus` (`sphere_frame.hpp`, an untracked header: Chapter 57). No physical value is read; every geometry is a constructed test.

## 58.1 Loci and stable differences

A place is a positive radius and a direction. A vector is a magnitude plus a direction; the zero vector is absence. For two loci with angular separation $\psi$,

$$d^2=(r_2-r_1)^2+4r_1r_2\sin^2(\psi/2). \tag{58.1}$$

The terms are nonnegative, so no cancellation of large squared radii occurs. Small-angle haversine is well conditioned; near-antipodal separation needs a conditioned atan2 expression. A vector difference should use the separation of the original vectors, not an antipode built and then cancelled against nearly opposite directions.

**Executed (V1, T1).** Known answers: two unit loci a quarter turn apart give $\sqrt2$, antipodal loci of radii $2$ and $3$ give $5$, and one direction with radii $2$ and $5$ gives $3$ (all exact). For unit radii and $\varphi_2=\varphi_1+10^{-9}$ the stored separation is $\psi=1.000000083\times10^{-9}$ (the stored angles differ from the intended $10^{-9}$ by $8\times10^{-8}$ relative: Section 58.2). The law of cosines $r_1^2+r_2^2-2r_1r_2\cos\psi$ returns exactly $0$ (the true value is about $10^{-18}$); `distance_to`, which uses (58.1), returns $1.000000083\times10^{-9}$, equal to $2\sin(\psi/2)$ to the arithmetic floor. Radii differing by $10^{-9}$ at one direction give $1.000000083\times10^{-9}$. Near antipodal, with $\psi=\pi-\delta$ and $\delta=1.000000003\times10^{-7}$ (stored), the engine's five-part `atan2` form returns $\pi-\psi=1.000000003\times10^{-7}$ (relative error $0$), while the haversine value is $9.884312\times10^{-8}$ (relative error $1.16\times10^{-2}$): the haversine loses $\sqrt\epsilon$ of accuracy near $\pi$, and the engine keeps it below 1 rad and switches above.

## 58.2 Resolution-aware errors

Double-precision angular storage gives a positional resolution of order $\epsilon r$. A step of size $s$ cannot generally round-trip with a relative accuracy better than order $\epsilon r|\varphi|/s$. Test thresholds must reflect representability. This is a property of the state representation, not a physical minimum distance.

**Executed (T2).** At $r=10^7$ m, $\theta=\pi/2$, $\varphi_1=1.2345$: one ulp is $2.2204\times10^{-16}$ rad and neighbouring representable azimuths are separated by $2.2204\times10^{-9}$ m; a shift of $0.4$ ulp is not representable (the locus is the same, distance $0$). For a step $s=10^{-3}$ m realised as $\Delta\varphi=s/r=10^{-10}$ rad, the round trip returns the step with a relative error of $8.274\times10^{-8}$ at every one of 200 azimuths in $[1,2)$: all share one ulp grid, so the quantisation of $10^{-10}$ to a multiple of $2.2204\times10^{-16}$ (450360 ulps) is the same, $8.3\times10^{-8}$. The worst case over steps is half an ulp over $\Delta\varphi$: $1.1\times10^{-6}$ here. A chart whose threshold is tighter than this fails for a reason of representation, not of physics.

## 58.3 A regular centre-crossing chart

A shifted spherical origin must also avoid the path's polar directions. Let the trajectory line have direction $a$; choose a transverse origin offset $b$ and a polar direction $p$ perpendicular to both $a$ and $b$. Every relative position lies in the plane spanned by $a$ and $b$, so its polar angle is $\pi/2$; its radius is at least $|b|>0$. Across any bounded transit both radial and angular clearance are uniform. The azimuth branch cut still requires overlapping longitude representatives or angle unwrapping: a single conventional spherical chart is not globally regular on the sphere. The engine's locus operations can represent finite directions at poles while the coordinate differential basis stays singular; these are different statements.

**Executed (T3).** For $p(t)=(t,\,1000\ \mathrm{m},\,0)$ with $t\in[-10^5,10^5]$ m in 2001 points the polar angle is $\pi/2$ at every point (worst deviation $0$), the radius is at least $1000$ m, and the azimuth range is $3.121593=\pi-2\arctan(0.01)$ (to $1.4\times10^{-16}$): the path never crosses the origin or a pole. With the origin on the line the radius is $0$ at $t=0$ and the constructor refuses the locus (`domain_error`). Converting a Cartesian point near the pole, $(10^{-9},0,1)$, with $\mathrm{acos}(z/r)$ gives $\theta=0$ (a 100 per cent error), while $\mathrm{atan2}(\sqrt{x^2+y^2},z)$ gives $10^{-9}$: the conversion route is part of the instrument's accuracy. A path whose azimuth crosses the cut ($6.2,6.22,\ldots$ wrapped modulo $2\pi$) has a raw maximum step of $6.2632$ and an unwrapped maximum step of $0.0200$.

The shifted-chart construction is a mathematical specification. It is not a claim that contract 4.0.0 already implements chart switching (Chapter 59).

## 58.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| radii, angles, offsets | Sections 58.1–58.3 | CONSTRUCTION (constructed geometries; no measured input) |
| distances, errors, ranges | Sections 58.1–58.3 | COMPUTED |
| $\epsilon$, ulp | double precision | property of the representation |

**Residuals.**

* **R58.1 — chart switching.** No chart switching is implemented or tested; the regular chart of 58.3 is a specification.
* **R58.2 — other operations.** `offset_direction`, `relative_locus`, `bearing` and the vector operations were not exercised here.
* **R58.3 — the differential basis.** The coordinate differential basis at the poles was not examined.
* **R58.4 — dimension.** Only the three-dimensional spherical frame was treated.
* **R58.5 — the header.** `sphere_frame.hpp` is untracked (R57.1); the results refer to the snapshot hashed in Chapter 57.

## 58.5 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch58_spherical_numerical_mechanics
```

Criteria were registered in `Textbook/validation/ch58_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch58_run1_output.txt`) met every criterion except one lower limit, through an instrument defect (the round trip was measured against the stored step rather than the intended one), recorded. Run 2 (`ch58_run2_output.txt`) is the run of record and met every criterion.

## 58.6 Exercises and answers

**Exercise 1.** Show that (58.1) reduces to the law of cosines.

*Answer.* $4r_1r_2\sin^2(\psi/2)=2r_1r_2(1-\cos\psi)$, so $d^2=r_1^2+r_2^2-2r_1r_2\cos\psi$.

**Exercise 2.** Why does the law of cosines return $0$ at $\psi=10^{-9}$ for unit radii?

*Answer.* $\cos\psi=1-5\times10^{-19}$ rounds to 1 in double precision, and $2-2\cos\psi=0$.

**Exercise 3.** What separation do neighbouring azimuths represent at $r=10^7$ m near $\varphi=1$?

*Answer.* $\mathrm{ulp}\cdot r=2.22\times10^{-16}\times10^7=2.2\times10^{-9}$ m.

**Exercise 4.** Why do the 200 azimuths give the same round-trip error?

*Answer.* They lie in $[1,2)$, which has one ulp ($2.2204\times10^{-16}$); the quantisation of $\Delta\varphi=10^{-10}$ to the ulp grid is the same everywhere.

**Exercise 5.** Why is the polar angle $\pi/2$ along the whole shifted path?

*Answer.* All relative positions lie in the plane of $a$ and $b$, perpendicular to the polar axis.

**Exercise 6.** What does the acos route lose near the pole?

*Answer.* $z/r=1-5\times10^{-19}$ rounds to 1, so $\mathrm{acos}$ returns $0$; $\mathrm{atan2}$ uses $\sqrt{x^2+y^2}=10^{-9}$ directly.

## 58.7 Scope

Established: that (58.1) and the engine's `distance_to` are well conditioned where the law of cosines fails; that the five-part form is accurate near antipodal where haversine is not; the resolution of the double-precision locus and the quantisation of a step; a regular centre-crossing chart as an executed construction; the conversion route and the azimuth cut.

Not established: chart switching (R58.1), the untested operations (R58.2), the pole basis (R58.3) and any dimension other than three (R58.4).

*Where it leads.* Chapter 59 turns to contracts and deterministic sessions: what a version number specifies, and what bitwise replay does and does not guarantee.
