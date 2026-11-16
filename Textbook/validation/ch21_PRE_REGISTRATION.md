# Chapter 21 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch21_three_slot_contact_capacity.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The three-slot contact rule of `nuclear` (unlike units only, at most three contacts per unit) as a bipartite-graph problem and as a geometric problem. (a) The exact maximum number of contacts, $\min(3Z,3N,ZN)$, shown by max-flow (so by max-flow/min-cut) on a grid larger than the one of Chapter 19, with the graph extracted from the flow and checked directly; (b) the internal contacts of the grammar's module composition, $E_{\rm int}=4+n_d+2n_t=N+2$, against that capacity, and the slack left for contacts between modules, for every natural nuclide of the embedded table and for named nuclei; (c) a geometric checker on frozen configurations of touching equal spheres (unlike pairs at the contact distance, like pairs never touching, no overlaps), applied to the alpha ring, to the equal-sphere tetrahedron, to the bent triton rod, to a four-neighbour star and to the twelve-around-one icosahedral shell; (d) the engine's `contact_capacity` on the larger grid. Capacity is not realisation: the checker states what a graph with degree at most three cannot yet say about embedding. The slot cap is a stated rule (operator-stated, 2026-10-14) and not a geometric limit; test (c) is registered to show it.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | max-flow capacity on hand-checkable cases: $K_{3,3}$ gives 9; $(Z,N)=(1,5)$ gives 3; $(2,2)$ gives 4; $(4,1)$ gives 3; $(2,7)$ gives 6 | exact |
| V2 | the geometric checker on two touching unit-radius spheres of opposite kind (distance 2): 1 unlike contact, no like contact, no overlap; on two like spheres at distance 2: 1 like contact; at distance 1.5: 1 overlap | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | for every $1\le Z,N\le40$ the max-flow equals $\min(3Z,3N,ZN)$; the graph read back from each flow has all degrees $\le3$, only proton–neutron edges, no repeated edge, and exactly that many edges | exact, 1600 cases | yes — one case above or below rejects the closed form |
| T2 | $E_{\rm int}(Z,N)=4+n_d+2n_t=N+2$ for every wedge point $Z\ge2$; $E_{\rm int}\le\min(3Z,3N,ZN)$ for every wedge point; over the 284 alpha-valid natural nuclides the minimum slack (capacity minus $E_{\rm int}$) is 0 (He-4 only) and the largest is printed; named nuclei He-4, C-12, O-16, Ca-40, Fe-56, Pb-208 printed with capacity, $E_{\rm int}$, slack, free proton slots $3Z-E_{\rm int}$ and free neutron slots $3N-E_{\rm int}$ | exact | yes — a wedge point whose module composition exceeds the capacity rejects the grammar at the contact level |
| T3 | geometry, registered outcomes. Alpha ring (planar square of side 2): 4 unlike contacts, 0 like contacts, 0 overlaps. Equal-sphere tetrahedron of 2 p and 2 n with all edges 2: 4 unlike and 2 like contacts (invalid). Bent triton n–p–n with the proton at the origin and neutrons at distance 2: at 90° 2 unlike, 0 like, valid; at 60° the neutrons touch (1 like contact, invalid); at 50° they overlap (invalid). Four-neighbour star (centre proton, four neutrons at tetrahedral directions at distance 2): 4 unlike contacts, 0 like, 0 overlaps, maximum degree 4, so geometrically placeable and excluded only by the cap. Twelve-around-one icosahedral shell (circumradius 2): 12 unlike contacts on the centre, no overlaps, the shell spacing $2/\sin(2\pi/5)=2.102924$ exceeds the contact distance by 0.102924, maximum degree 12 | exact classification; lengths to $10^{-6}$ | yes |
| T4 | the engine's `contact_capacity` over $1\le Z,N\le40$ equals the exact capacity if and only if $\max(Z,N)\ge3$; `kissing_exceeds_cap(12)` is true and `contact_slots` is 3 | exact | yes |

Reported, not criteria: the slack distribution over the table, the named-nuclei ledger.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch21_three_slot_contact_capacity`
