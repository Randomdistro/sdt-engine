# Chapter 24 — Spin, Parity and Nuclear Moments

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 10 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. $\{(w_i,\vec r_i)\}$ is a weighted point set about its weighted centre; $I_l$ is the rank-$l$ multipole content defined in (24.1). Executable companion: `Textbook/examples/ch24_spin_parity_and_nuclear_moments.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 24.1 The physical question

One frozen structure has several observables. A spin label needs total angular impulse, including circulation and any medium contribution. Parity is a statement about transformation under spatial inversion. A moment, such as a quadrupole-like moment, depends on a weighted spatial second moment of the structure. The question of this chapter is what a frozen geometry fixes of these and what it leaves open. The engine supplies none of the observed labels: the embedded table of 287 natural nuclides stores only $(Z,A)$, and the engine's stored moments are in nuclear magnetons, a unit this book does not use, with one quadrupole anchor (the deuteron, an OBSERVED spectroscopy value). No observable is therefore compared with a label here. The chapter executes the structural statements that decide how a later comparison must be set up.

## 24.2 A rotation-invariant measure of multipole content

For a weighted point set about its weighted centre define

$$I_l=\frac{\sum_{i,j}w_iw_j\,r_i^{\,l}r_j^{\,l}\,P_l(\cos\gamma_{ij})}{\big(\sum_iw_ir_i^{\,l}\big)^2}, \tag{24.1}$$

with $\gamma_{ij}$ the angle between $\vec r_i$ and $\vec r_j$. By the addition theorem the numerator is proportional to $\sum_m|q_{lm}|^2$, the squared magnitude of the rank-$l$ moments, so $I_l$ is invariant under rotations and vanishes if and only if every rank-$l$ moment of the set vanishes. $I_1$ is the dipole content and $I_2$ the content of the traceless second moment $\sum w(3\vec r\vec r^{\,T}-r^2\mathbb 1)$ (the quadrupole-like tensor); odd $l$ vanish for any set that is invariant under inversion about its centre.

**Executed (V1).** The traceless tensor of two unit weights at $(0,0,\pm1)$ was $\mathrm{diag}(-2,-2,4)$; $I_1$ of an equal-weight pair about its centroid was zero; and the Legendre values $P_2,P_3,P_4$ were $1$ at $\cos\gamma=1$ and $-\tfrac12,0,\tfrac38$ at $\cos\gamma=0$.

## 24.3 Symmetry removes low ranks, not structure

**Executed (T1).** For vertex sets with equal weights about the centroid, the contents $I_l$ (zero means $\le10^{-12}$):

| set | $I_1$ | $I_2$ | $I_3$ | $I_4$ | $I_5$ | $I_6$ |
|---|---|---|---|---|---|---|
| tetrahedron | 0 | 0 | 0.556 | 0.259 | 0 | 0.395 |
| cube | 0 | 0 | 0 | 0.259 | 0 | 0.395 |
| octahedron | 0 | 0 | 0 | 0.583 | 0 | 0.125 |
| icosahedron | 0 | 0 | 0 | 0 | 0 | 0.440 |

Table 24.1. Rank content of symmetric solids, executed (T1).

The tetrahedral and cubic sets have no traceless second moment but have rank-4 content (and, for the tetrahedron, rank-3 content, since it is not invariant under inversion). The icosahedral set has no content in ranks 1 to 5 and first appears at rank 6. A vanishing quadrupole-like moment is therefore compatible with a structure that is far from spherical: the sets differ from a sphere at higher rank.

## 24.4 An accidental cancellation, and the module configurations

**Executed (T2).** Two points of weight 1 at $(0,0,\pm1.5)$ and four points of weight $\tfrac12$ at $(\pm s,0,0)$, $(0,\pm s,0)$ with $s^2=4.5$ (so that $w_ah^2=w_rs^2=2.25$) form a set that is not cubic ($h=1.5\ne s=2.12$). Its second-moment content vanishes, $I_2=-2\times10^{-17}$, its rank-3 content vanishes (it is centrosymmetric), and its rank-4 content is $I_4=0.600$. A prolate pair and an oblate ring have cancelled in rank 2 without making the set spherical. Zero moment does not prove spherical microscopic geometry, and a generic closed occupancy does not by itself establish a spherical boundary.

The module configurations of Chapters 19 and 21, with equal weights about their centroids:

| configuration | $I_1$ | $I_2$ | $I_3$ | $I_4$ |
|---|---|---|---|---|
| alpha ring (square, side 2) | 0 | 0.250 | 0 | 0.688 |
| two-sphere pair (distance 2) | 0 | 1.000 | 0 | 1.000 |
| bent triton ($90^\circ$) | 0 | 0.4375 | 0.454 | 0.340 |

Table 24.2. Rank content of the module configurations, executed (T2).

Each has a non-zero second-moment tensor in its own frame, and the bent triton, which is not invariant under inversion, also has rank-3 content.

## 24.5 A zero observed moment for a spin-zero state says nothing about shape

The traceless tensor of an intrinsic configuration is a property of the frame fixed to the structure. A moment observed in the laboratory is an average over the orientation distribution of the structure, which a spin-zero state makes uniform. For any intrinsic traceless tensor $Q$, the average of $RQR^T$ over all rotations $R$ is the zero tensor, because the only rotation-invariant traceless symmetric tensor is zero.

**Executed (T3).** For the alpha ring, the pair and the bent triton, the tensor averaged over all orientations (an Euler-angle quadrature that is exact for the quadratic dependence on the rotation) was the zero tensor to a relative $1.3\times10^{-16}$, $6.6\times10^{-17}$ and $3.1\times10^{-17}$ of the largest intrinsic component ($8.0$, $4.0$, $5.33$ in the units of the points). The alpha ring has a non-zero intrinsic tensor and a zero observed one. An observed moment of zero for a spin-zero state therefore carries no information about the intrinsic shape, and a non-zero observed moment requires a state with an anisotropic orientation distribution (a populated total-impulse state), whose weights are not supplied by the geometry. Degenerate configurations need an energy selector or a stated population rule.

## 24.6 Parity is not inferred from a nucleon count

Parity describes the behaviour of the observable under inversion. For a frozen labelled configuration the geometric statement is whether inversion about its centre maps the set to itself with the kinds (proton, neutron) preserved.

**Executed (T4).** The alpha ring is invariant. The two-sphere pair p–n is not (inversion exchanges proton and neutron). The bent triton n–p–n at $90^\circ$ is not. The linear triton n–p–n ($180^\circ$) is invariant, and so is an icosahedral shell of twelve neutrons about a proton. An odd nucleon count does not decide the parity of a configuration: the occupied route symmetry and the observable operator have to be specified. The geometric invariance here is a necessary ingredient, not a parity assignment, because the phase of the circulation under inversion is not in a point set.

## 24.7 The 287-record basis

The embedded natural basis validates module-coordinate coverage (Chapter 20). A prediction of spin, parity and moments across 287 states is a separate task. Each isotope needs an independently sourced observed label, a frozen configuration and a declared prediction rule before any label is loaded. Missing labels stay missing: they are not inferred from the expected pattern and then counted as agreements. The inventory should store the occupied seats, orientations, winding sense, residual open slots and an uncertainty. A lookup that stores observed labels can support navigation; it cannot be the mechanism that predicts them.

The same applies to magnetic moments. The engine's stored values are in nuclear magnetons, a borrowed unit. A native statement needs ratios of moments expressed with native yardsticks, and none is available (residual R24.3).

## 24.8 Atomic correspondence

Nuclear and atomic structures may share directional constraints through connected circulation and wake organisation. The test is an explicit transformation from nuclear geometry to atomic response with species-dependent scale factors derived once. Resemblance supplies no moment magnitude or sign.

## 24.9 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| definition (24.1) and its zeros | Sections 24.2–24.4 | DERIVED (exact) and COMPUTED |
| configurations (module graphs, solids, the accidental set) | as stated | CONSTRUCTION (chosen weights 1, 0.5) |
| Tables 24.1 and 24.2 | executed | COMPUTED |
| orientation average (T3) | Section 24.5 | DERIVED (exact quadrature) |
| inversion invariance (T4) | Section 24.6 | DERIVED (exact) |
| the engine's observed moments and quadrupole anchor | `measured::` | OBSERVED (not used; magnetons not used) |

**Residuals.**

* **R24.1 — labels and rule.** No spin, parity or moment label is stored for the 287 records; a prediction needs sourced labels, a frozen configuration and a rule declared beforehand.
* **R24.2 — weights.** The weights of a response moment (which units source the moment, with what strength) are not given by the geometry; the unit weights used here are a CONSTRUCTION.
* **R24.3 — units.** The stored moments are in nuclear magnetons; a native ratio is not available.
* **R24.4 — population.** The orientation distribution of a populated total-impulse state is not given.
* **R24.5 — circulation phase.** Parity needs the phase of the circulation under inversion, which a point set does not carry.

## 24.10 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch24_spin_parity_and_nuclear_moments
```

Criteria were registered in `Textbook/validation/ch24_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch24_run1_output.txt`) is the run of record and met every criterion.

## 24.11 Exercises and answers

**Exercise 1.** Compute the traceless second-moment tensor of two unit weights at $(0,0,\pm1)$.

*Answer.* $\sum(3z^2-r^2)$ along $z$ is $2\times(3-1)=4$; in $x$ and $y$ each is $2\times(0-1)=-2$. The tensor is $\mathrm{diag}(-2,-2,4)$.

**Exercise 2.** Why does a set with cubic symmetry have $I_2=0$?

*Answer.* A symmetric traceless second-rank tensor invariant under the cubic rotations is proportional to the identity, and being traceless it is zero.

**Exercise 3.** Why is $I_3=0$ for a centrosymmetric set?

*Answer.* Inversion sends $\vec r\to-\vec r$ and multiplies $P_3$ by $-1$; a pair of points related by inversion contributes opposite signs and the sum is zero. The same holds for every odd $l$.

**Exercise 4.** In the accidental set, show the cancellation condition.

*Answer.* The contribution of the two axial points to $\sum w(3z^2-r^2)$ is $2w_a(2h^2)=4w_ah^2$; that of the four ring points is $-4w_rs^2$ (since $z=0$). They cancel when $w_ah^2=w_rs^2$.

**Exercise 5.** What does a zero observed quadrupole moment of a spin-zero state say about the shape?

*Answer.* Nothing: the orientation average of any traceless tensor is zero.

**Exercise 6.** Why is the pair p–n not inversion-invariant as a labelled set?

*Answer.* Inversion about the centroid exchanges the two units, so the proton would land on the neutron's position.

## 24.12 Scope

Established in this chapter: the rotation-invariant rank content (24.1) and its zeros for symmetric solids; the accidental cancellation showing that a zero second moment does not prove a spherical geometry; the exact vanishing of the orientation-averaged tensor for any intrinsic shape; and the inversion invariance of the module configurations as labelled sets.

Not established: any spin, parity or moment of any nucleus, because no sourced label was loaded and no prediction rule was declared (R24.1), the weights of a response moment (R24.2), a native unit for magnetic moments (R24.3), the population of a total-impulse state (R24.4) and the circulation phase for parity (R24.5).

*Where it leads.* Volume IV turns from persistent structures to the atom: hydrogenic structure, spectra, the many-electron closure, and molecular and condensed organisation.
