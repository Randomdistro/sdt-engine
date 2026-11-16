# Chapter 21 — Three-Slot Contact Capacity

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 10 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. $Z$ protons, $N$ neutrons; $E$ is a contact count; spheres have unit radius so the contact distance is 2. Executable companion: `Textbook/examples/ch21_three_slot_contact_capacity.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 21.1 The physical question

The contact rule of the nuclear construction states that a contact joins an unlike pair (proton–neutron) at the contact distance, like pairs never touch, and no unit holds more than three contacts (`nuclear::contact_slots`, `laws.hpp:2137`). The rule fixes a capacity, not a count. Three questions follow. What is the exact capacity of a nucleus with $Z$ protons and $N$ neutrons? Does the module composition of Chapter 20 fit inside it? And what does a graph that satisfies the degree cap still leave undetermined about the spatial embedding of touching solid spheres?

## 21.2 The exact capacity

Let $G=(P\cup N,E)$ be bipartite, with $\lvert P\rvert=Z$, $\lvert N\rvert=N$ and every degree at most 3. Then $E\le3Z$ and $E\le3N$; and since a pair is joined at most once, $E\le ZN$. These are the three bounds, and they are tight:

$$E_{\max}(Z,N)=\min(3Z,\,3N,\,ZN). \tag{21.1}$$

*Proof of tightness.* Model the problem as a flow from a source through the protons (capacity 3 each), across proton–neutron pairs (capacity 1 each), through the neutrons (capacity 3 each) to a sink. Its maximum equals the minimum cut. A cut that keeps $a$ protons on the source side and $b$ neutrons on the sink side severs $3(Z-a)$ source edges, $ab$ pair edges and $3(N-b)$ sink edges, a capacity $3(Z-a)+ab+3(N-b)$. This is linear in $a$ at fixed $b$ and in $b$ at fixed $a$, so its minimum over $0\le a\le Z$, $0\le b\le N$ lies at a corner: $3Z+3N$, $3N$, $3Z$ or $ZN$, of which the first is never the smallest. The minimum cut is therefore the smallest of the three bounds. An integral maximum flow is a graph with the stated edge count.

The closed form $3\min(Z,N)$ is equal to (21.1) if and only if $\max(Z,N)\ge3$: the bound $ZN$ lies below $3\min(Z,N)$ exactly when $ZN<3\min(Z,N)$, i.e. $\max(Z,N)<3$.

**Executed (V1, T1).** The solver reproduced $K_{3,3}=9$, $(1,5)\to3$, $(2,2)\to4$, $(4,1)\to3$, $(2,7)\to6$ (V1). For all $1600$ pairs $1\le Z,N\le40$ the max-flow equalled (21.1), and in every case the graph read back from the flow had all degrees at most 3, only proton–neutron edges, no repeated edge and exactly that many edges: no mismatch. The engine's `contact_capacity(Z,N)=3\min(Z,N)` equalled (21.1) on exactly the pairs with $\max(Z,N)\ge3$ and exceeded it on the four pairs $(1,1),(1,2),(2,1),(2,2)$ (T4; Chapter 19, residual R19.5).

## 21.3 Module composition inside the capacity

An alpha ring has 4 contacts, a deuteron 1 and a triton 2. A nucleus of the wedge of Chapter 20 with $n_d$ deuterons and $n_t$ tritons has internal contacts

$$E_{\rm int}=4+n_d+2n_t=4+(2Z-2-N)+2(N-Z)=N+2. \tag{21.2}$$

Open slots on a module with $Z_m$ protons, $N_m$ neutrons and $E_m$ internal contacts are $3Z_m-E_m$ on its proton units (open for neutron contacts) and $3N_m-E_m$ on its neutron units. The deuteron has $(2,2)$, the triton $(1,4)$ and the alpha ring $(2,2)$. The alpha ring therefore retains external capacity: those open slots can only be used by units of other modules, since inside the four-unit ring every possible contact is already made. Alpha closure cannot be described as exhaustion of every external slot.

**Executed (T2).** At all $7\,140$ wedge points $2\le Z\le120$, $E_{\rm int}=N+2$, and $E_{\rm int}$ did not exceed the exact capacity (21.1) at any of them: the grammar's module composition always fits. The slack $E_{\max}-E_{\rm int}$ (the number of contacts available between modules) over the 284 alpha-valid natural nuclides has minimum 0, which occurs only at $^4$He (zero-slack count 1), maximum 132 at $^{234}$U and mean 74.33. Named nuclei:

| nucleus | $Z$ | $N$ | capacity | $E_{\rm int}$ | slack | free proton slots | free neutron slots |
|---|---|---|---|---|---|---|---|
| $^4$He | 2 | 2 | 4 | 4 | 0 | 2 | 2 |
| $^{12}$C | 6 | 6 | 18 | 8 | 10 | 10 | 10 |
| $^{16}$O | 8 | 8 | 24 | 10 | 14 | 14 | 14 |
| $^{40}$Ca | 20 | 20 | 60 | 22 | 38 | 38 | 38 |
| $^{56}$Fe | 26 | 30 | 78 | 32 | 46 | 46 | 58 |
| $^{208}$Pb | 82 | 126 | 246 | 128 | 118 | 118 | 250 |

Table 21.1. Capacity, module contacts and open slots, executed (T2).

The fit is a statement about capacity. A realised nucleus fills some number of the slack contacts, fixed by geometry (Chapter 22); the table does not say how many.

## 21.4 What a graph with degree at most three leaves undetermined

A valid abstract graph need not admit the spatial embedding: touching unlike vertices must sit at the contact distance while like vertices and non-edges satisfy exclusion. The checker classified frozen configurations of unit spheres (contact distance 2; unlike contact, like contact, overlap; V2 checked it on pairs):

* **Alpha ring**, a planar square of side 2: 4 unlike contacts, no like contact, no overlap; the like pairs sit $2\sqrt2=2.828427$ apart.
* **Equal-sphere tetrahedron** of two protons and two neutrons: 4 unlike and 2 like contacts, so it is not a contact configuration: all six edges touching is forbidden because two of them join like units.
* **Bent triton** n–p–n with the neutrons at distance 2 from the proton: at $90^\circ$ valid (2 unlike, no like); at $60^\circ$ the neutrons touch (a like contact); at $50^\circ$ they overlap. A triton is therefore a rod bent by more than $60^\circ$, not a triangular loop.
* **Four-neighbour star**: a proton with four neutrons at tetrahedral directions at distance 2 has 4 unlike contacts, no like contact, no overlap (neighbour spacing $3.265986$) and maximum degree 4. It is geometrically placeable and excluded only by the cap. The slot cap is therefore a stated rule (operator-stated, 2026-10-14) and not a consequence of packing geometry.
* **Twelve-around-one** icosahedral shell, circumradius 2: 12 unlike contacts on the centre, no overlap, maximum degree 12, four times the cap (`kissing_exceeds_cap(12)` is true). The shell's own spacing is $2/\sin(2\pi/5)=2.102924$, exceeding the contact distance by $0.102924$ sphere radii: it is not a contact shell either, since its members cannot touch each other and the 12 neighbours of the centre leave a gap.

All of the classifications matched the outcomes registered before the run. A degree-four closed graph violates the rule even when a rendered cluster looks compact; conversely a graph passing the cap can still contain loop lengths or orientations that no embedding supplies, which is why the ledger keeps capacity, realised contacts and the embedding check as separate columns.

## 21.5 The separate columns of a nuclear ledger

A nuclear ledger carries four columns that must not be merged: the capacity (21.1); the realised contacts (an embedded graph, checked by an independent geometric checker on the same frozen configuration); the zero modes of the configuration (rigid motions and any free internal motion); and the restoring response (Chapter 23). A closure signature must identify the exhausted accessible seating tier, not the total degree capacity.

## 21.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| the slot rule (unlike only, cap 3) | engine's | the engine's rule (operator-stated 2026-10-14); not derived from geometry |
| (21.1) and the flow proof | Section 21.2 | DERIVED (exact) |
| (21.2) and Table 21.1 | Section 21.3 | DERIVED and COMPUTED |
| geometric classifications | Section 21.4 | COMPUTED (exact geometry) |
| the table of 284 natural nuclides | Chapter 20 | OBSERVED (isotope list) |

**Residuals.**

* **R21.1 — the rule's origin.** The cap of three, and the exclusion of like contacts, are stated rules. The four-neighbour star shows the cap does not follow from equal-sphere packing.
* **R21.2 — realised contacts.** How many of the slack contacts a given nucleus fills is not fixed by capacity.
* **R21.3 — orientation.** The checker tests distances only; orientation compatibility, loop-length constraints and circulation are not tested.
* **R21.4 — the engine's capacity function.** `contact_capacity` equals (21.1) except for $(1,1),(1,2),(2,1),(2,2)$ (R19.5; proposal, not applied).
* **R21.5 — rigidity.** Solid spheres are assumed; deformable boundaries (Chapter 22) change the geometry checks.

## 21.7 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch21_three_slot_contact_capacity
```

Criteria were registered in `Textbook/validation/ch21_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch21_run1_output.txt`) is the run of record and met every criterion.

## 21.8 Exercises and answers

**Exercise 1.** Evaluate (21.1) for $(Z,N)=(1,2)$ and $(3,3)$.

*Answer.* $\min(3,6,2)=2$ and $\min(9,9,9)=9$.

**Exercise 2.** Derive (21.2).

*Answer.* $4+n_d+2n_t$ with $n_d=2Z-2-N$, $n_t=N-Z$: $4+2Z-2-N+2N-2Z=N+2$.

**Exercise 3.** Why does $^4$He have zero slack but still two free proton slots?

*Answer.* Within the four units every proton–neutron pair is already joined ($E=4=ZN$), so no further contact can be made among them. The slots $3Z-E=2$ are open only to units of other modules.

**Exercise 4.** At what angle at the proton do the two neutrons of a triton touch?

*Answer.* Their distance is $4\sin(\theta/2)$ and touching needs it to equal 2, so $\theta=60^\circ$.

**Exercise 5.** Show the icosahedral shell spacing.

*Answer.* The 12 vertices of an icosahedron of circumradius $\rho$ have edge $\rho/\sin(2\pi/5)$. With $\rho=2$ the edge is $2.102924$.

**Exercise 6.** Is the cap of three a packing limit?

*Answer.* No. Twelve equal spheres can touch a central sphere. The cap is a rule of the construction.

## 21.9 Scope

Established in this chapter: the exact capacity (21.1) with a proof and a check on 1600 cases; $E_{\rm int}=N+2$ and the fit of every wedge point and every natural nuclide inside the capacity, with $^4$He the only zero-slack case; and the geometric classification of six frozen configurations, showing that the cap is a rule and that a degree-valid graph is not yet an embedding.

Not established: the origin of the rule (R21.1), the number of realised contacts (R21.2), orientation compatibility (R21.3) and the effect of deformable boundaries (R21.5).

*Where it leads.* Chapter 22 builds the seating and packing sequence from rods to rings and compares rigid instruments with deformable circulation.
