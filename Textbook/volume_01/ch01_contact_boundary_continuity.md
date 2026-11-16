# Chapter 1 — Contact-Boundary Continuity

*Volume I — Ontology, Geometry and Admissible States.*
Draft of 3 November 2026. Notation: this chapter uses none of the circulation-boundary symbols ($\mathrm{Om}$, $k$, $z$) of `Textbook/NOTATION_LEDGER.md`. Executable companion: `Textbook/examples/ch01_contact_boundary_continuity.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 1.1 The physical question

Spatial Displacement Theory starts from a medium of contiguous spations and asks three things of it. What can change at a contact? What persists? What can be measured? This chapter fixes the starting statements, separates the ones that are posited from the ones that are derived, states what the network geometry forces, and keeps apart three volumes that the engine's notation can blur.

The representation matters at the first step. A graph represents neighbourhood contact without asserting that space consists of abstract vertices. A pressure function describes a collective response without making a field a primitive. A spherical chart gives a locus without fixing a physical centre. Where this book writes an index $i$ for a spation or a function for a density, the index and the function are bookkeeping; the physical coupling is the contact boundary.

## 1.2 Premises and their status

The constitution (`Theory/00_Ruleset.md`) lists nine axioms. Table 1.1 sets each beside the chapter that derives what follows from it.

| id | statement | status | where used |
|---|---|---|---|
| R1 | Space is a gap-free, contact-only relay medium | posited | all chapters |
| R2 | Transmission is nearest-neighbour only, at $c=\ell_P/t_P$ | posited | Ch 3, 14 |
| R3 | Every spation carries deformation content $\varepsilon$ | posited | Ch 4 |
| R4 | The lattice has $N=R_{\rm CMB}/\ell_P$ radial shells | posited (measured $R_{\rm CMB}$) | Ch 4 |
| R5 | At the Clearing all content was released isotropically | posited | Ch 4, 9 |
| R6 | Convergent arrival from shell $i$ preserves $\Phi=N\varepsilon$ | posited in the Ruleset; **derived** in Ch 4 from premises P1–P6 | Ch 4 |
| M1 | Matter is a persistent displacement of spations | posited | Ch 7, 12, 17 |
| M2 | Displaced spations circulate at $v_{\rm circ}\le c$ | posited | Ch 13 |
| M3 | $v_{\rm circ}^2+v^2=c^2$ | posited in the Ruleset; the budget is examined in Ch 13 | Ch 13 |

Table 1.1. Axioms of the Ruleset.

What follows from these, and is not posited separately, includes the inverse-square form of the interaction (Chapters 9–11), the factor $1/3$ of the isotropic stress (Chapter 9), the Lorentz factor (Law V, Chapter 13) and mass as an output (Law IV, Chapter 12). What is assumed beyond Table 1.1 is stated where it enters. Chapter 4 assumed Euclidean geometry across the causal domain (its premise P5); Section 1.5 shows that this is a property of the medium's average structure and not of nearest-neighbour relay as such.

## 1.3 The contact description

Let the contact network admit the graph representation

$$\mathcal G=(\mathcal V,\mathcal E),\qquad i\sim j\iff (i,j)\in\mathcal E. \tag{1.1}$$

Let $\xi_i$ be a declared local deformation descriptor. A proposed update has the local form

$$\mathcal D\xi_i=\mathcal R_i\big(\xi_i,\{\xi_j: j\sim i\};\mathcal B\big), \tag{1.2}$$

with $\mathcal B$ the boundary conditions and $\mathcal D$ the change over a declared number of relay intervals. Equation (1.2) states locality. It selects no response: the operator $\mathcal R$ comes from a closed dynamical model (Chapters 14 and 16).

*Duration* in this book is an oscillator count. A detector adjacent to arriving material contacts the leading edge at one place and finishes when the material leaves at another; the order of the two contacts is the direction, and the number of cycles of a chosen oscillator between them is the duration. A relay interval is the cycle of the relay oscillator. With this count, nearest-neighbour transmission through a path of graph distance $d_G(i,j)$ gives the causal bound

$$m_{\rm arrive}-m_{\rm depart}\ \ge\ d_G(i,j), \tag{1.3}$$

where $m$ counts relay intervals. The bound assumes no shorter contact path and no pre-existing correlated response counted as a transmitted influence. Correlation and controllable communication need separate operational definitions (Chapter 51).

**Descriptor sufficiency.** A scalar $\xi_i$ cannot distinguish isotropic compression from shear. The stress states $\mathrm{diag}(1,1,1)$ and $\mathrm{diag}(2,1,0)$ have the same trace and different deviators. A descriptor that separates them is a symmetric second-rank array, six independent components, or equivalently the trace, the magnitude of the deviator and its principal axes (residual R1.1).

## 1.4 What the network geometry forces

The contact network of a gap-free medium cannot be a regular tetrahedral stacking. The engine records the facts in `sdt/lattice_structure.hpp` as class GEOMETRY, with no physics input. The instrument of this chapter reproduces each by a second route: explicit vertex coordinates in place of the header's closed forms.

**Tetrahedron.** The dihedral angle of a regular tetrahedron is $\delta=\arccos(1/3)=70.528779^\circ$ and its supplement, the tetrahedral bond angle, is $\arccos(-1/3)=109.471221^\circ$. The routine that computed them from outward face normals was first run on the cube, the octahedron and the icosahedron and returned $90^\circ$, $109.4712206^\circ$ and $138.1896851^\circ$ (test V1). Applied to the tetrahedron it agrees with `lattice_structure::dihedral_rad` and `bond_angle_rad` to $2.2\times10^{-16}$ rad (T1).

**Five about an edge.** Five regular tetrahedra about a common edge subtend $5\delta=352.644^\circ$, short of a full turn by

$$\Delta=2\pi-5\delta=0.128388\ \text{rad}=7.356103^\circ. \tag{1.4}$$

Regular tetrahedra therefore cannot tile Euclidean three-space (T2, within $9\times10^{-16}$ rad of `five_edge_deficit_rad`).

**Face stacking.** Stacking tetrahedra face to face gives the Boerdijk–Coxeter helix, with a twist of $\arccos(-2/3)=131.810315^\circ$ and a rise of $a/\sqrt{10}$ per step at radius $3\sqrt3\,a/10$ from the axis. The instrument built the vertices $P_k=(\rho\cos k\vartheta,\rho\sin k\vartheta,kh)$ and found $|P_k-P_{k+j}|=a$ for $j=1,2,3$ to $4.2\times10^{-15}$ over $k=0\ldots40$, with $|P_k-P_{k+4}|\ge1.63299\,a$ (T4). Because $\cos\vartheta=-2/3$ is rational and not $0,\pm\tfrac12,\pm1$, Niven's theorem gives $\vartheta/\pi$ irrational: the helix never closes. The helix is the channel geometry of the network, not its bulk (CONDENSA §0).

**Twelve about one.** Twelve unit spheres touching a central unit sphere, placed on an icosahedron, have their centres at distance 2 from the centre. The shell neighbours are separated by $2.102924$, which exceeds 2 by

$$g=\frac{8}{\sqrt{10+2\sqrt5}}-2=0.102924\ \text{sphere radii}. \tag{1.5}$$

The twelve spheres therefore do not close into a rigid shell (T3, exhaustive search over the 66 pairs, agreement with `icosa_shell_gap_over_r` to the last printed digit). Equations (1.4) and (1.5) are two expressions of one frustration. The header does not claim that the angular deficit summed radially equals the linear gap, and neither does this chapter.

**Corner sharing.** Corner-sharing tetrahedra join at a vertex, the inter-tetrahedral angle at the hinge is free, and the network can absorb the deficit by flexing while each tetrahedron stays rigid. The statistically isotropic corner-sharing network has coordination 4. In its diamond-limit node model the packing fraction is $\pi\sqrt3/16=0.340087$ and the void fraction $0.659913$ (T5, from eight spheres of radius half the nearest-neighbour distance per cubic cell; V3 confirmed 8 atoms and 4 neighbours).

*Status.* The numbers in this section are DERIVED, exact, and independent of any measured input. The statement that the physical medium is this network is an identification, not a derivation (CONDENSA §7, "interpretive identification — promising, not closed"; residual R1.3). The coordination 4 equals $W+1$ for the trefoil winding $W=3$ of Law VI; the engine records this as a coincidence and no derivation links the two (R1.4). The void fraction of the node model sits beside the axiom R1, that the medium is gap-free, and the two are not reconciled in the sources (R1.5). The face-sharing helix and the close-packed icosahedral arrangement are each excluded as a global tiling of three-space by the numbers above.

## 1.5 Relay reach on regular lattices: isotropy is a property of the medium

Equation (1.3) holds on any network. What it gives for the *shape* of the region reached after $n$ relay intervals depends on the network. On a regular lattice with neighbour vectors $\{v_a\}$ the region reached in at most $n$ hops is the $n$-fold sum of the neighbour set, and the farthest projection along a unit direction $\hat u$ after $n$ hops is

$$n\,h_P(\hat u),\qquad h_P(\hat u)=\max_a\ \frac{v_a\cdot\hat u}{|v_a|}, \tag{1.6}$$

where $h_P$ is the support function of the polytope of neighbour vectors, measured in units of one hop length. The instrument computed the reach by breadth-first search to $n=6$ on three lattices after the search reproduced the coordination sequences $4n^2+2$, $10n^2+2$ and $6n^2+2$ for $n=1\ldots6$ (V2).

| lattice | neighbours | reach per hop along $[100]$ | $[110]$ | $[111]$ | largest / smallest |
|---|---|---|---|---|---|
| simple cubic | 6 | 1.000000 | 0.707107 | 0.577350 | $\sqrt3=1.732051$ |
| face-centred cubic | 12 | 0.707107 | 1.000000 | 0.816497 | $\sqrt2=1.414214$ |
| body-centred cubic | 8 | 0.577350 | 0.816497 | 1.000000 | $\sqrt3=1.732051$ |

Table 1.2. Reach per hop (executed, $n=6$; breadth-first search equals $n\,h_P$ to the last digit; T7).

On the simple cubic lattice the hop distance is $|x|+|y|+|z|$ for every cell within hop radius 6, with no cell missed (T8); the reached region is an octahedron.

*Proposition 1.1.* Under R2 on a regular lattice the relay front is anisotropic by an order-one factor, between $\sqrt2$ and $\sqrt3$ for the three lattices above. The isotropic Euclidean geometry assumed in Chapter 4 (premise P5) and the direction-averaged ray length of its Eq. (4.4) therefore require the medium to be isotropic on average and not a regular lattice. The measured isotropy of the propagation speed is far finer than the order-one anisotropy computed here, so a regular lattice with nearest-neighbour hops as stated is not a candidate for the physical medium. This is the observation that points toward the statistically isotropic network of Section 1.4. The full dispersion relation of that random hinge network, required to show that it supports isotropic propagation, is open in the source (CONDENSA §7; residual R1.6).

## 1.6 Persistent form

A persistent structure is a contact configuration that keeps a recognisable boundary and a recurring pattern. Let $X(\sigma)$ be a family of configurations labelled by a phase $\sigma$. Persistence requires closure after a complete turn, up to an admitted symmetry:

$$X(\sigma+2\pi)=g\,X(\sigma),\qquad g\in\mathcal H. \tag{1.7}$$

Three questions stay separate: whether a recurring configuration exists; whether it is stable under disturbance; and at what rates it forms and decays. A geometric construction answers the first. Equality of two pictures at two phases does not establish stability, and a closed orbit in configuration space can be unstable. Stability needs the response to a perturbation with boundary forcing declared (Chapters 7, 8 and 17). Axioms M1–M3 add that the displaced spations circulate at a speed $v_{\rm circ}\le c$ and that the total speed is $c$.

## 1.7 Three volumes

An envelope, an exclusion volume and an engaged volume are three different quantities. Equal symbols must not hide that.

* The **boundary (envelope) volume** is the volume inside the radius that casts the shadow. For the proton it is $\tfrac{4\pi}{3}R_p^3$ with $R_p=8.414\times10^{-16}$ m. It is occupied by a hard, present, occluding concentration of material.
* The **exclusion volume** $V_{\rm disp}$ is the volume of the Law IV relation

$$mc^2=\frac{P_{\rm conv}\,V_{\rm disp}}{3},\qquad P_{\rm conv}=\frac{\Phi}{\ell_P^3}, \tag{1.8}$$

which is the engine's $m=\Phi V_{\rm disp}/(3\ell_P^3c^2)$ (`law_IV::mass_from_V_disp`, `laws.hpp:619`). Its dimension is checked: $\Phi$ is an energy, $V_{\rm disp}/\ell_P^3$ is a number, and the right-hand side is an energy.
* The **engaged volume** $V_{\rm eng}$ of the resistance law (`resistance_from_engaged_volume`, `laws.hpp:672`) is the part of a structure engaged in a particular response. It is the subject of Chapter 12.

| quantity | value | label | engine reference |
|---|---|---|---|
| cell volume $\ell_P^3$ | $4.222111\times10^{-105}$ m³ | MEASURED-INPUT (stored $\ell_P$) | `measured::l_P3`, 160 |
| proton boundary volume $\tfrac{4\pi}{3}R_p^3$ | $2.495147\times10^{-45}$ m³ $=5.9097\times10^{59}$ cells | COMPUTED | `measured::R_p` |
| proton exclusion volume $V_{\rm disp,p}$ | $1.832653\times10^{-58}$ m³ $=4.3406\times10^{46}$ cells | COMPUTED | `law_IV::V_disp_p`, 834 |
| boundary / exclusion volume (proton) | $1.3615\times10^{13}$ | COMPUTED | |
| electron exclusion volume $V_{\rm disp,e}$ | $9.980942\times10^{-62}$ m³ $=2.3640\times10^{43}$ cells | COMPUTED | `law_IV::V_disp_e`, 830 |
| $R_{\rm excl,p}$, $R_{\rm excl,e}$ | $3.523686\times10^{-20}$ m, $2.877582\times10^{-21}$ m | COMPUTED | 842, 838 |
| $V_{\rm disp,p}/V_{\rm disp,e}$ | $1836.152673=m_p/m_e$ | CONSTRUCTION | |
| radial shells to the Clearing $N=R_{\rm CMB}/\ell_P$ | $5.894491\times10^{61}$ | COMPUTED | `law_I::N`, 264 |

Table 1.3. Executed volumes and cell counts (test T6; line numbers are those of `laws.hpp` as read on 2026-11-03).

The proton's boundary encloses about $5.9\times10^{59}$ cells, a count $10^{-2}$ times the number $N$ of radial shells to the Clearing (a cell count set beside a shell count, for scale only), and its exclusion volume is $10^{13}$ times smaller. Which of the two is the proton's cell count is a question the engine's two proton volumes leave open; the book carries both and names which one each equation uses.

The relation (1.8) is satisfied to $2\times10^{-16}$ when $V_{\rm disp,p}$ is obtained from $m_p$ and substituted back. Both sides share one input, so the check is CONSTRUCTION in the sense of the behavioural gateway: it shows the relation is applied consistently, and it is not an independent resistance prediction. An independent $V_{\rm disp}$ needs the volume from geometry and dynamics without the target mass (residual R1.2). The identity $\rho_{\rm eff,e}c^2=P_{\rm conv}/3$ (`law_IV::P_cf_e`, 851) is the same relation read for the electron, agreeing to $10^{-16}$, and carries the same label.

The engine's `ParticleRadii` pair for each particle the exclusion radius with a boundary radius (the wake radius $r_e$ for the electron, $R_p$ for the proton) and the Compton wavelength. They are three different lengths. The entry $r_e$ needs a caution: $r_e=\alpha^2a_0$ is the c-boundary of *hydrogen*, the length $\mathrm{Om}=v^2r/c^2$ of the proton–electron system obtained by the same expression as the c-boundary of a planetary system (Chapter 33). It is not the electron and not the electron's size (author's statement of 16 November 2026, consistent with the ruling of 2026-10-12 quoted in Chapter 46). Listing it under the electron is the engine's arrangement and is recorded as a proposal item (residual R1.7); Chapter 17 sets out what the sources say about the electron's own extent. For the proton, $R_{\rm excl,p}=3.52\times10^{-20}$ m, $R_p=8.41\times10^{-16}$ m and $\lambda_{C,p}=1.32\times10^{-15}$ m.

## 1.8 Input ledger and residuals

| quantity | role | label |
|---|---|---|
| tetrahedron dihedral, deficit, kissing gap, helix twist and rise, diamond packing | network geometry | DERIVED (exact); reproduced by a second route |
| lattice reach ratios $\sqrt3,\sqrt2,\sqrt3$ | relay front | COMPUTED (exact) |
| $\ell_P$ | cell edge | the relation to the c-boundary per baryon and the proton wake is geometric (FLM06); the stored number is the CODATA Planck length, whose definition carries $G$ numerically: CALIBRATED(1) as a stored number (`laws.hpp:111–119`) |
| $m_p$, $m_e$ | rest masses | MEASURED-INPUT (CODATA) |
| $R_p$ | proton boundary radius | MEASURED-INPUT (muonic hydrogen, 2019) |
| $T_{\rm CMB}$, $R_{\rm CMB}$ | set $\varepsilon$ and $N$ | MEASURED-INPUT (FIRAS; measured Clearing distance) |
| cell counts, $V_{\rm disp}$, $R_{\rm excl}$ | volumes of Table 1.3 | COMPUTED, carrying the measured inputs above |

**Residuals.**

* **R1.1 — the descriptor.** What the minimal deformation descriptor $\xi_i$ is for the medium (a scalar is insufficient; the six-component form is the minimum that separates compression from shear) is not fixed by the sources.
* **R1.2 — independent $V_{\rm disp}$.** A value of the exclusion volume from geometry and dynamics, not from the measured mass.
* **R1.3 — identification.** That the vacuum *is* the corner-sharing network (CONDENSA, interpretive identification).
* **R1.4 — coordination and winding.** Coordination 4 and $W+1=4$ are recorded together; no derivation connects them.
* **R1.5 — void fraction and R1.** The diamond-limit node model has void fraction $0.66$; R1 states a gap-free medium. The sources do not reconcile the two, and Chapter 22 returns to the interstitial voids.
* **R1.6 — isotropy.** The dispersion relation of the random hinge network, needed to show isotropic propagation at the measured level.
* **R1.7 — the electron entry of `ParticleRadii` (proposal to the author, canon untouched).** The engine lists $r_e$, hydrogen's c-boundary, as the electron's boundary radius; the electron's own surface is a different length (Chapter 17, Section 17.3).

## 1.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch01_contact_boundary_continuity
```

The criteria of `Textbook/validation/ch01_PRE_REGISTRATION.md` were registered before the instrument existed. Run 1 met every criterion (`ch01_run1_output.txt`): V0–V3 (helpers, dihedral routine on three known solids, coordination sequences, diamond cell) and T1–T8. T6 shows that the chapter's volume relations and the engine's are the same expressions; its magnitudes carry the measured inputs of Table 1.3.

## 1.10 Exercises and answers

**Exercise 1.** Show that a scalar descriptor cannot separate $\mathrm{diag}(1,1,1)$ from $\mathrm{diag}(2,1,0)$, and give the least additional information that does.

*Answer.* Both have trace 3. Subtracting the isotropic part leaves the zero array and $\mathrm{diag}(1,0,-1)$, whose magnitude is $\sqrt2$. The trace, the magnitude of the deviator and the principal axes (three angles) together determine a symmetric $3\times3$ array: 6 numbers.

**Exercise 2.** Obtain the dihedral angle of the regular tetrahedron from the vertices $(1,1,1),(1,-1,-1),(-1,1,-1),(-1,-1,1)$ and the deficit (1.4).

*Answer.* The face opposite vertex $v$ has outward normal $-v/\sqrt3$. For the faces opposite $(-1,1,-1)$ and $(-1,-1,1)$ the normals' dot product is $(-1,1,-1)\cdot(-1,-1,1)/3=-1/3$, so the normals subtend $\arccos(-1/3)=109.47^\circ$ and the dihedral angle is $\pi-109.47^\circ=\arccos(1/3)=70.53^\circ$. Then $2\pi-5(1.230959)=0.128388$ rad.

**Exercise 3.** Find the electron's cell count from the proton's.

*Answer.* $V_{\rm disp}\propto m$ at fixed $\Phi$, so $N_e=N_p\,m_e/m_p=4.3406\times10^{46}/1836.15=2.364\times10^{43}$, matching Table 1.3.

**Exercise 4.** Show that on the simple cubic lattice the relay front after $n$ hops is an octahedron and find the ratio of its reach along $[100]$ to that along $[111]$.

*Answer.* A walk of unit axis steps reaches $(x,y,z)$ in at least $|x|+|y|+|z|$ steps, with equality for monotone walks. The cells reached in at most $n$ hops satisfy $|x|+|y|+|z|\le n$, an octahedron. Along $[100]$ the reach is $n$; along $[111]$ the face $x+y+z=n$ is met at $x=y=z=n/3$, at distance $n/\sqrt3$. The ratio is $\sqrt3$.

**Exercise 5.** The face-centred cubic neighbour set is the twelve vectors $(\pm1,\pm1,0)$ and permutations. Obtain the ratio of the largest to the smallest reach per hop.

*Answer.* Along $[110]$ the neighbour $(1,1,0)/\sqrt2$ gives 1. Along $[100]$ the best neighbour projection is $1/\sqrt2$. The largest to smallest ratio over the polytope is $\sqrt2$; along $[111]$ the value is $2/\sqrt6=0.8165$, between the two.

## 1.11 Scope

Established in this chapter: the status of each axiom in the constitution and what is derived from it; the exact network geometry forced by gap-free contact (the tetrahedral deficit $7.356^\circ$, the icosahedral gap $0.102924$ radii, the Boerdijk–Coxeter helix and the diamond-limit packing), each reproduced by a second route; the order-one anisotropy of relay reach on regular lattices, which requires a statistically isotropic medium; and the separation of boundary, exclusion and engaged volumes with their executed cell counts.

Not established: that the physical medium is the corner-sharing network (R1.3); an independent exclusion volume (R1.2); the descriptor (R1.1); the reconciliation of the network's void fraction with R1 (R1.5); and the isotropy of the network's propagation (R1.6).

*Where it leads.* Chapter 2 sets the spherical geometry in which loci and directions are stated. Chapter 3 gives the relay kinematics behind (1.3). Chapter 7 takes up persistence and topology, and Chapter 12 the engaged volume.
