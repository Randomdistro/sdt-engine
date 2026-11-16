# Chapter 30 — Atomic–Nuclear Correspondence

*Volume IV — Atomic Recurrence, Spectra and Material Organisation.*
Draft of 10 November 2026. Notation: $I_l$ is the rank-$l$ multipole content of Chapter 24 (zero if and only if every rank-$l$ moment vanishes); $s_r$, $s_\nu$ and $R$ are the scale factors and rotation of a proposed correspondence. Executable companion: `Textbook/examples/ch30_atomic_nuclear_correspondence.cpp`; pre-registration and captured output in `Textbook/validation/`. No isotope or line data are loaded and no scale factor is fitted.

## 30.1 The physical question

A nucleus can constrain atomic organisation through source topology, orientation and boundary throughput. The proposed correspondence is a map $A_{\rm atom}=F(X_{\rm nucleus},X_{\rm electronic},S)$, not an assertion that every atomic feature is a scaled drawing of a nuclear one: nuclear and electronic degrees of freedom have different time scales and external boundary responses. For a proposed geometric correspondence one writes $r_{\rm atom}=s_r(X,S)\,r_{\rm nuclear}$, $f_{\rm atom}=s_\nu(X,S)\,f_{\rm nuclear}$ and $\mathrm{orientation}_{\rm atom}=R(X,S)\,\mathrm{orientation}_{\rm nuclear}$. The factors and the rotation have to be predicted or independently fixed. This chapter measures how much a correspondence with free factors can absorb, and then tests one concrete symmetry claim.

## 30.2 What freedom absorbs

**Instrument check (V1).** An exact mirror of a 12-point set (scale $2.7$, a rotation, a translation) is recovered by a best-similarity fit (scale, rotation, translation; Horn's quaternion method) with relative residual $1.5\times10^{-15}$ and scale $2.7$ to $8\times10^{-16}$: when two geometries are one geometry, a single scale and rotation find it.

**Executed (T1).** For 500 pairs of independent random 12-point sets the best single similarity leaves a median relative residual of $0.926$ (minimum $0.707$), and none of the 500 pairs ($0.00\%$) is matched within 5%. For random positive magnitude vectors, a single global factor leaves a median residual of $0.675$ ($N=3$, $0.8\%$ within 5%), $0.825$ ($N=6$, $0\%$) and $0.855$ ($N=12$, $0\%$). A factor per observable leaves a residual of exactly zero for every pair. A correspondence in which each observable has its own scale factor therefore carries no information: it matches unrelated geometries and unrelated magnitudes alike. A match with one global similarity is informative, because it is rare among unrelated sets; the count of free factors must be stated with the result.

## 30.3 Isotope leverage

Isotopes retain the proton number and change the neutron seating. A frozen nuclear grammar (Chapter 20) therefore sets a targeted test: predict isotope shifts, and changes of orientation-dependent moments, without changing the electronic interaction parameters. The part of an isotope shift that follows from the nuclear mass is the reduced-mass response of Chapter 25 ($\lambda_H-\lambda_D=0.17858$ nm for Balmer-$\alpha$, from stored masses only). The part that depends on the nuclear structure (finite-size exposure, orientation coupling; Chapter 27) needs a seated configuration for each isotope and an independently observed label for each; the embedded 287-record basis supplies occupancy coordinates only. A bulk trend along an element chain cannot isolate this coupling, and representation coverage is not a dynamical map.

## 30.4 A symmetry-forced zero as a sharp test

Shared rotational symmetry can constrain a tensor form before any amplitude is known. A symmetry-forced vanishing component is a sharper prediction than a vague scale resemblance; a broken symmetry under a specified seat change should give a calculated non-zero response of definite orientation and sign.

**Executed (T2).** The nuclear shell directions, as unit vectors: T8 (the eight cube vertices), T12 (the twelve icosahedron vertices) and T14 (the face normals of the cuboctahedron: the octahedron's eight and the cube's six). Each has $I_1=I_2=I_3=0$ (to $<10^{-16}$), as their cubic and icosahedral symmetries require; their first non-zero content is at rank 4 for T8 ($I_4=0.259$) and T14 ($1.3\times10^{-3}$), and at rank 6 for the icosahedron ($0.440$). The atomic seat directions of the engine's many-electron construction ($N_e=2\ldots10$: two polar seats at $n=1$, two at $n=2$, then the six-ring) have $I_2>0$ for every $N_e$:

| $N_e$ | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---|---|---|---|---|---|---|---|---|
| $I_2$ | 1.000 | 1.000 | 1.000 | 0.583 | 0.309 | 0.128 | 0.078 | 0.042 | 0.010 |

Table 30.1. Second-moment content of the atomic seat directions, executed (T2). The sets for $N_e=2,3,4$ hold polar seats only and are collinear ($I_2=1$).

The atomic seat sets have a traceless second moment in their own frame, while the three nuclear shells have none, so no atomic seat set has the rank-2 content of any of the nuclear shells and a direct mirroring of the geometries is excluded at rank 2. The content decreases with the filling of the ring ($0.010$ at $N_e=10$), but it does not vanish, and the rank-4 content of the $N_e=10$ set ($0.391$) is not small. Two cautions follow from Chapter 24. The observed moment of a closed-shell atom, which has total impulse zero, is zero for any intrinsic shape (the orientation average of a traceless tensor vanishes), so the observed vanishing of the quadrupole-like moment of neon is not evidence for or against the frozen seat geometry. And a partial correspondence at higher rank (for instance of the rank-4 content of $N_e=10$ with that of T14 or T8) would need its own scale factor and orientation, to be predicted before comparison.

## 30.5 Scale factors that exist

Two lengths of the construction form the natural scale candidates between the two domains: $a_0/R_p\approx6.29\times10^4$ and $r_e/R_p\approx3.349$ (COMPUTED from the stored lengths). They are not used here. A correspondence would need $s_r(X,S)$ derived once, as a function of the species and the state, and then used for every observable of that species.

## 30.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| similarity fit and census | Section 30.2 | COMPUTED (random generator fixed; counts of free factors stated) |
| nuclear shell directions (cube, icosahedron, cuboctahedron normals) | as stated | CONSTRUCTION (exact solids) |
| atomic seat directions | `dodecardinal::make_seats` | the engine's seat geometry |
| $I_l$ values, Table 30.1 | Section 30.4 | COMPUTED |
| $a_0/R_p$, $r_e/R_p$ | Section 30.5 | COMPUTED (not used) |

**Residuals.**

* **R30.1 — the map.** No map $F$ from nuclear to atomic quantities with derived factors exists; none is proposed here.
* **R30.2 — isotope structure.** Nuclear-structure dependent isotope shifts and moment changes are not predicted; seated configurations and sourced labels for a chain are outstanding.
* **R30.3 — higher rank.** Possible correspondences at rank 4 and above are not tested.
* **R30.4 — time scales.** Nuclear and electronic degrees of freedom have different time scales; the correspondence of frequencies $s_\nu$ is not addressed.
* **R30.5 — directions only.** The atomic sets were compared by directions with equal weights; the radii of the shells (Chapter 29) and the weights of a response moment (Chapter 24, R24.2) are not included.

## 30.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch30_atomic_nuclear_correspondence
```

Criteria were registered in `Textbook/validation/ch30_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch30_run1_output.txt`) is the run of record and met every criterion.

## 30.8 Exercises and answers

**Exercise 1.** Why does a per-observable factor match any two sets of magnitudes?

*Answer.* For each observable $a_i,b_i>0$ the factor $b_i/a_i$ reproduces $b_i$ exactly.

**Exercise 2.** Why is a global-similarity match informative?

*Answer.* Among unrelated sets it is rare (none of 500 random pairs within 5%), so it needs a reason.

**Exercise 3.** Which nuclear shell has no rank-4 content?

*Answer.* The icosahedron ($I_4=0$ to $10^{-16}$); its first content is at rank 6.

**Exercise 4.** Why does the vanishing observed quadrupole-like moment of neon not test the seat geometry?

*Answer.* The state has zero total impulse, and the orientation average of a traceless tensor is zero for any intrinsic shape (Chapter 24, T3).

**Exercise 5.** Compute $I_2$ for the collinear set $N_e=2$.

*Answer.* All $P_2(\cos\gamma_{ij})=1$ for collinear directions, so $I_2=1$.

**Exercise 6.** What must an isotope-chain test fix before any label is loaded?

*Answer.* The seated configuration for each isotope, one geometric map with its scale factors, and the observables to be predicted.

## 30.9 Scope

Established in this chapter: the freedom census (one global similarity is rare among unrelated geometries; a factor per observable absorbs everything); the rank-2 content of the atomic seat directions for $N_e=2\ldots10$ and its absence in the three nuclear shells, so that a direct mirroring of the two geometries is excluded at rank 2.

Not established: any correspondence map with derived factors (R30.1), nuclear-structure isotope effects (R30.2), higher-rank correspondence (R30.3), the frequency factors (R30.4) and the comparison with radii and weights (R30.5).

*Where it leads.* Chapter 31 treats bonding between atoms: equilibrium geometry, dissociation and the pathway dependence of reactions.
