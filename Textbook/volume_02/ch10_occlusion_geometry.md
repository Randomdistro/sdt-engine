# Chapter 10 — Occlusion Geometry

*Volume II — Pressure Response, Inertia and Propagation.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch10_occlusion_geometry.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 10.1 The physical question

Chapter 9 gave the force that a removed cap of directions exerts on a target: $\sigma_2 q\,\Omega_{\rm proj}$, with the shadow of body 1 treated as a cap about the axis. The target is not a point. A direction inside the cap blocks only the part of the target's cross-section that the shadow covers, and a direction just outside the cap can still block a sliver. This chapter derives the projected area and the solid-angle deficit with the overlap of a finite shadow and a finite target kept exactly, the union that replaces a sum when two shadows overlap, and the engine's discretisation of the geometry.

## 10.2 Premises

Premises P1–P8 are those of Chapters 4 and 9. One is added.

| id | premise | source |
|---|---|---|
| P9 | A solid form blocks every ray whose line passes through its projected outline; nothing that meets the form passes it. The form is the hard, present, occluding concentration of Chapter 1, and its shadow on a plane perpendicular to the ray is its projected outline. | R9.6; matter is substantive |

The response model of Chapter 9 (an absorbing or specular target) applies unchanged, with the limitation recorded there as R9.6: the coefficients below are properties of the geometry under that model.

## 10.3 Projected area and solid angle of a sphere

A sphere of radius $R$ at distance $r\ge R$ casts, along each direction, a disc of radius $R$ in the plane perpendicular to the ray, and subtends the cap of half-angle $\sin\eta=R/r$ about its centre. The two measures of Chapter 9 are

$$\Omega_{\rm cap}=2\pi\Big(1-\sqrt{1-R^2/r^2}\Big),\qquad \Omega_{\rm proj}=\int_{\rm cap}\mu\,d\Omega=\frac{\pi R^2}{r^2}. \tag{10.1}$$

The first is the solid angle in the ordinary sense and the second is the cosine-weighted measure that enters the axial force. They agree to $x/4$, $x=R^2/r^2$, in the far field and differ by a factor 2 at contact (Chapter 9, Section 9.7).

## 10.4 Overlap of two discs

Two discs of radii $R_1$ and $R_2$ whose centres are a distance $d$ apart overlap in the area

$$A_{\rm ov}(d)=\begin{cases}\pi\min(R_1,R_2)^2,&d\le|R_1-R_2|,\\[1mm]
R_1^2\alpha_1+R_2^2\alpha_2-\tfrac12\sqrt{(-d+R_1+R_2)(d+R_1-R_2)(d-R_1+R_2)(d+R_1+R_2)},&|R_1-R_2|<d<R_1+R_2,\\[1mm] 0,&d\ge R_1+R_2,\end{cases} \tag{10.2}$$

with $\cos\alpha_1=(d^2+R_1^2-R_2^2)/(2dR_1)$ and $\cos\alpha_2=(d^2+R_2^2-R_1^2)/(2dR_2)$. Known answers reproduced by the instrument (V1): two unit circles at $d=1$ give $2\pi/3-\sqrt3/2=1.2283696986$; $d=0$ gives $\pi$; $d\ge2$ gives $0$; a unit circle inside a circle of radius 2 gives $\pi$.

Integrating the overlap over every displacement of one disc relative to the other counts each pair of points once:

$$\int_{\mathbb R^2}A_{\rm ov}(|\vec x|)\,d^2x=A_1A_2=\pi R_1^2\cdot\pi R_2^2, \tag{10.3}$$

the convolution identity of two indicator functions.

## 10.5 The exact occlusion force of two spheres

Let the target be a sphere of radius $R_2$ at the origin and the shadowing body a sphere of radius $R_1$ at distance $r$ along the axis, $r\ge R_1+R_2$. A direction $\hat n$ at angle $\gamma$ to the axis carries the content $q\,d\Omega$ per unit area. Without body 1 the bundle of rays along $\hat n$ that strikes the target has the cross-section $\pi R_2^2$. With body 1 present, the part $A_{\rm ov}(r\sin\gamma)$ of that cross-section is blocked, because the projected centres are $r\sin\gamma$ apart (P9). Each removed element exerts the force $q\,d\Omega\,A_{\rm ov}$ along $-\hat n$ on an absorbing or specular sphere, and its axial component carries the factor $\cos\gamma$. With $d\Omega=2\pi\sin\gamma\,d\gamma$ and $u=r\sin\gamma$, so that $\cos\gamma\,d\gamma=du/r$,

$$F=q\int_0^{\gamma_{\max}}2\pi\sin\gamma\cos\gamma\,A_{\rm ov}(r\sin\gamma)\,d\gamma=\frac{2\pi q}{r^2}\int_0^{\min(R_1+R_2,\;r)}u\,A_{\rm ov}(u)\,du. \tag{10.4}$$

*Proposition 10.1.* For $r\ge R_1+R_2$ the upper limit of (10.4) is $R_1+R_2$, beyond which $A_{\rm ov}=0$, so the integral extends over the whole plane and by (10.3)

$$\boxed{\,F=\frac{q}{r^2}\,\pi R_1^2\cdot\pi R_2^2=\frac{\pi}{4}\,U\,\frac{R_1^2R_2^2}{r^2}\quad\text{for every }r\ge R_1+R_2,\,}\qquad q=\frac U{4\pi}. \tag{10.5}$$

The Law III form carries no finite-body correction down to contact, for spheres of any radii. The cosine weight, the partial coverage of the target's cross-section by directions outside the point-source cap, and the loss of coverage by directions inside it cancel exactly. The result is symmetric in the two bodies, so the force on body 1 from the shadow of body 2 is equal and opposite: Newton's third law holds for finite bodies as it does for points.

*Executed (test T3).* Quadrature of (10.4), split at the breakpoints $|R_1-R_2|$ and $R_1+R_2$, for the pairs $(R_1,R_2)=(1,1),(1,0.2),(3,1),(1,3)$ and $r/(R_1+R_2)=1,\,1.05,\,2,\,10,\,100$ gave $F/(q\pi^2R_1^2R_2^2/r^2)=1$ in all twenty cases, the worst deviation being $2.9\times10^{-13}$ (the quadrature is valid to that level).

| bodies | $r/(R_1+R_2)$ | $F/F_{\rm LawIII}$ |
|---|---|---|
| $(1,1)$ | 1 (contact) | $1.000000000000$ |
| $(1,1)$ | 10 | $1.000000000000$ |
| $(1,0.2)$ | 1 | $1.000000000000$ |
| $(3,1)$ | 1 | $1.000000000000$ |
| $(1,3)$ | 10 | $1.000000000000$ |
| $(1,1)$ | $0.75$ (bodies overlapping, not physical) | $0.904030$ |
| $(1,0.2)$ | $0.75$ | $0.794813$ |
| $(3,1)$ and $(1,3)$ | $0.75$ | $0.858923$ |

Table 10.1. The finite-body force relative to the Law III form, executed.

Below contact the upper limit becomes $r<R_1+R_2$ and the integral is truncated; the ratio falls below 1 in all four pairs. Such separations place the bodies inside one another and are outside the model.

*Relation to Chapter 9.* The argument of Chapter 9 took the shadow as a cap about the axis as seen from the centre of the target and treated every direction inside it as blocking the whole cross-section. That is exact for a target of negligible size at every $r\ge R_1$. For a finite sphere the partial coverage matters direction by direction, and Proposition 10.1 shows that the two errors cancel in the total: (9.10) holds for a finite target for every $r\ge R_1+R_2$.

*Orientation.* The identity (10.3) holds for any two shapes, but the axial reduction that gave (10.5) uses the spherical symmetry of both. For non-spherical forms the force depends on orientation and the vector sum of (10.4) must be taken direction by direction (residual R10.3).

## 10.6 Overlapping shadows

When two bodies shadow one target in nearby directions, their shadows overlap and the removed directions are the union, not the sum. Two caps of half-angles $a$ and $b$ whose axes subtend $\delta$ overlap in the solid angle

$$\Omega_\cap=2\pi-2\cos a\,\arccos\frac{\cos b-\cos a\cos\delta}{\sin a\sin\delta}-2\cos b\,\arccos\frac{\cos a-\cos b\cos\delta}{\sin b\sin\delta}-2\arccos\frac{\cos\delta-\cos a\cos b}{\sin a\sin b} \tag{10.6}$$

for $|a-b|<\delta<a+b$, equal to the smaller cap for $\delta\le|a-b|$ and to zero for $\delta\ge a+b$. The union is $\Omega_\cup=\Omega_1+\Omega_2-\Omega_\cap$.

The closed form was checked on known answers (V2): coincident caps return the cap area, nested caps the smaller cap, tangent caps zero, and two hemispheres whose axes subtend $90^\circ$, $60^\circ$ and $180^\circ$ return $\pi$, $4\pi/3$ and $0$. It was then compared with two independent routes for eight configurations. Integration of the azimuthal width of one cap inside the other over the polar angle agreed to $8.2\times10^{-8}$ in the worst case, and a $3000\times6000$ equal-area grid count agreed to $1.5\times10^{-3}$ for three configurations (test T1).

| axes separated by | $\Omega_\cap$ (sr) | $\Omega_\cup$ (sr) | sum of independent shadows overstates $\Omega_\cup$ by |
|---|---|---|---|
| $0^\circ$ (nested) | $8.6109\times10^{-3}$ | $2.3909\times10^{-2}$ | $36.0\%$ |
| $4^\circ$ | $5.5515\times10^{-3}$ | $2.6969\times10^{-2}$ | $20.6\%$ |
| $7^\circ$ | $7.6756\times10^{-4}$ | $3.1753\times10^{-2}$ | $2.4\%$ |
| $8^\circ$ (tangent) | $0$ | $3.2520\times10^{-2}$ | $0$ |
| $9^\circ$ | $0$ | $3.2520\times10^{-2}$ | $0$ |

Table 10.2. Caps of half-angle $5^\circ$ and $3^\circ$ (test T2). The bounds $\max(\Omega_1,\Omega_2)\le\Omega_\cup\le\Omega_1+\Omega_2$ held in every case with strict inequality on the right exactly for $\delta<8^\circ$.

A third body between two others therefore does not subtract its full shadow twice, and the interaction of a pair is changed by a third body by the overlap of the shadows on the receiver, not by their sum (Chapter 35).

## 10.7 The engine's discretisation

The engine represents each body in the many-body routines by seven circular channels (`sdt/occlusion.hpp`; the spherical form is `occlusion_sphere.hpp`): a central disc and a ring of six, each of radius $R/3$, weighted $1/9$ for the central channel and $4/27$ for each ring channel.

Executed (test T4): the weights sum to $1$; the ring centres lie at $2R/3$ from the centre and adjacent ring centres are $2R/3$ apart, so the seven discs are tangent to one another; the outermost point of the ring discs reaches $R$; and the seven discs cover $7/9=0.7778$ of the projected area $\pi R^2$. The weights are normalised to the whole outline, so the ring channels carry $4/3$ of their own area to represent the gaps. A disc is integrated by a fixed rule of 6 Gauss–Legendre radial and 16 azimuthal nodes; its weights sum to $\pi R^2$ to $8.5\times10^{-16}$. For the apparent solid angle of a face-on disc, `disc_solid_angle` against the exact `axial_disc_solid_angle` $=2\pi(1-d/\sqrt{d^2+R^2})$ gave relative errors

| $d/R$ | 0.5 | 1 | 2 | 5 | 10 | 100 |
|---|---|---|---|---|---|---|
| relative error | $1.2\times10^{-5}$ | $6.3\times10^{-8}$ | $1.2\times10^{-11}$ | $6\times10^{-15}$ | $4\times10^{-15}$ | $7.7\times10^{-13}$ |

Table 10.3. Accuracy of the engine's disc quadrature (all below the registered $10^{-3}$ for $d\ge R$).

How the seven-channel approximation compares with the exact sphere–sphere geometry of Section 10.5 in a force calculation is the subject of Chapter 35.

## 10.8 Input ledger and residuals

All executed values of this chapter are DERIVED (exact geometry) or COMPUTED by quadrature; no measured input enters.

**Residuals.**

* **R10.1 — the response model.** Proposition 10.1 holds for an absorbing or specular target (Chapter 9, R9.6). A diffusely scattering target changes the coefficient (Chapter 9, Proposition 9.3), and an operator-level account of the response is outstanding.
* **R10.2 — many bodies.** The exact pair result does not extend by addition. Overlapping shadows (Section 10.6) and shielding of one pair by a third body need the union measure; the quantitative treatment is Chapter 35.
* **R10.3 — non-spherical forms.** The proton's trefoil and any nucleus are not spheres; the orientation-dependent overlap of (10.4) has not been computed for them.
* **R10.4 — the seven-circle model.** The model covers $7/9$ of a body's outline and assigns weights that sum to 1; the relation between the geometry and the weights is a modelling choice, not a derivation.
* **R10.5 — contact.** The identity (10.5) is exact to contact for hard spheres. For the boundary radii of atomic and nuclear forms ($R_p$, $r_e$) the separations of interest are many orders of magnitude beyond contact, and what happens at contact for forms whose boundaries are equilibria (Chapter 18) is not settled.

## 10.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch10_occlusion_geometry
```

The criteria of `Textbook/validation/ch10_PRE_REGISTRATION.md` were registered before the instrument existed (two draft sentences in V3 and T2 of the registration were cleaned before any run). Run 1 (`ch10_run1_output.txt`) met every criterion.

## 10.10 Exercises and answers

**Exercise 1.** Find the overlap of two unit discs whose centres are one radius apart.

*Answer.* $\alpha_1=\alpha_2=\arccos\tfrac12=\pi/3$. $A=2\cdot\pi/3-\tfrac12\sqrt{1\cdot1\cdot1\cdot3}=2\pi/3-\sqrt3/2=1.22837$.

**Exercise 2.** Prove (10.3).

*Answer.* Write $A_{\rm ov}(\vec x)=\int 1_{D_1}(\vec y)\,1_{D_2}(\vec y-\vec x)\,d^2y$. Integrating over $\vec x$ and exchanging the order, $\int d^2y\,1_{D_1}(\vec y)\int d^2x\,1_{D_2}(\vec y-\vec x)=A_1A_2$.

**Exercise 3.** Use Proposition 10.1 to find $F$ for two equal spheres of radius $R$ at contact, in units of $q\pi^2R^2$.

*Answer.* $r=2R$: $F=q\pi^2R^4/(4R^2)=q\pi^2R^2/4$, one quarter of $q\pi^2R^2$.

**Exercise 4.** For caps of $5^\circ$ and $3^\circ$ whose axes subtend $4^\circ$, by what percentage does the sum of independent shadows overstate the union?

*Answer.* $(3.2520-2.6969)\times10^{-2}/(2.6969\times10^{-2})=20.6\%$ (Table 10.2).

**Exercise 5.** Show that the seven tangent discs of radius $R/3$ cover $7/9$ of the outline.

*Answer.* Seven discs of area $\pi R^2/9$ each total $7\pi R^2/9$, the fraction $7/9=0.7778$ of $\pi R^2$.

**Exercise 6.** Why does the integral of (10.4) for $r<R_1+R_2$ give a ratio below 1?

*Answer.* The upper limit $u=r\sin\gamma\le r$ truncates the plane integral of (10.3) at $u=r<R_1+R_2$, where $A_{\rm ov}$ is still positive, so part of the integrand's support is missing.

## 10.11 Scope

Established in this chapter: the overlap of two discs and the convolution identity; the exact occlusion force of two spheres in the parallel-ray model, equal to the Law III form for every separation from contact outward; the closed form for the overlap and union of two caps of directions, with independent confirmation; and the geometry and accuracy of the engine's seven-circle representation.

Not established: the response model that underlies the force (R10.1), the many-body shielding coefficient (R10.2), the orientation dependence for non-spherical forms (R10.3), and the behaviour at contact of forms whose boundary is an equilibrium (R10.5).

*Where it leads.* Chapter 11 sets (10.5) against the engine's Law III with $P_{\rm eff}$. Chapter 35 uses the union measure and the seven-circle model for many bodies. Chapter 18 returns to the shape of the proton.
