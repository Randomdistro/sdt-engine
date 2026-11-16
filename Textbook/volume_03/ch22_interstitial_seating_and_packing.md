# Chapter 22 — Interstitial Seating and Packing

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 10 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. $D$ denotes a deuteron-seat shell and $T$ a triton shell, with their capacities (the engine's names D6, D12, T8 and so on). Executable companion: `Textbook/examples/ch22_interstitial_seating_and_packing.cpp`; pre-registration and captured output in `Textbook/validation/`.

## 22.1 The physical question

Shapes come before count sequences. The construction proceeds from deuteron and triton rods to alpha rings and then to contact-preserving seating on shells. The engine records a schedule of tiers whose cumulative sums reproduce the stored list of closures. The chapter asks what in that schedule is arithmetic that can be checked, what in it is a premise, and what the schedule does not yet reproduce.

## 22.2 The tier law

Like units never touch (Chapter 21), so every tier is a bipartite double layer, a proton face and a neutron face. If the two-dimensional order of a layer is triangular, a layer of side $n+1$ holds the $(n+1)$-th triangular number $\tfrac12(n+1)(n+2)$ of rod seats, and the tier holds

$$F(n)=(n+1)(n+2)=2,\,6,\,12,\,20,\,30,\,42,\ldots \tag{22.1}$$

($F(0)=2$ is the alpha's own two deuterons). Tritons are radial rods on geometric shells with $B(n)=V=2(n+1)$ vertices ($8,10,12,14,\ldots$ from $n=3$), and the intervening deuteron seats are the links of that shell, $R(n)=E=n(n+1)$ ($12,20,30,42,\ldots$). Then, identically,

$$F(n)=B(n)+R(n). \tag{22.2}$$

**Executed (V1, T1).** Enumeration of the triangular lattice $\{(i,j):i,j\ge0,\,i+j\le n\}$ gave $\tfrac12(n+1)(n+2)$ points for every $0\le n\le40$ (and $1,3,6,10,15,21$ for $n=0\ldots5$); twice that equals the engine's `tier_capacity(n)`; $B+R=F$ for all $n$; and the engine's `triton_shell_capacity` and `surface_remainder` equal $2(n+1)$ and $n(n+1)$. The engine binds its stored arrays to these closed forms by `static_assert`.

## 22.3 The schedule

Closures come from the species-pure order: $2\;\xrightarrow{D6}\;8\;\xrightarrow{D12}\;20\;\xrightarrow{T8}\;28\;\xrightarrow{D12}\;40\;\xrightarrow{T10}\;50\;\xrightarrow{D20}\;70\;\xrightarrow{T12}\;82\;\xrightarrow{D30}\;112\;\xrightarrow{T14}\;126\;\xrightarrow{D42}\;168\;\xrightarrow{T16}\;184$. Up to $n=2$ the deuteron tiers fill ($F(0)+F(1)+F(2)=20$). From $n=3$ the triton shell separates and descends to seal the previous closure, so that

$$28=20+B(3),\quad 50=28+R(3)+B(4),\quad 82=50+R(4)+B(5),\quad 126=82+R(5)+B(6),\quad 184=126+R(6)+B(7). \tag{22.3}$$

**Executed (T2).** An independent build from (22.1)–(22.3) gave the closures $2,8,20,28,50,82,126,184$; the engine's `closure(k)` for $k=0\ldots6$ and the stored list `magic_numbers` (an OBSERVED input) agreed with the first seven; the eleven steps of the species-pure order are $F(1),F(2),B(3),R(3),B(4),R(4),B(5),R(5),B(6),R(6),B(7)$ and the sub-shell sums are $2,8,20,28,40,50,70,82,112,126,168,184$. The value $184$ is a forward value of the formulas, not an observed universal stability claim: proton and neutron shell occupancy, topology and lifetimes need their own state specification.

**Shared counting.** $F(n)$ equals the degeneracy of the three-dimensional oscillator and $B(n)$ the capacity of the intruder orbit of the prevailing shell account. The sequence of closures is therefore convergent with that account at the level of counting, and the counting cannot discriminate between the two. The native content is the bipartite doubling and the vertex/link geometry of the shells.

## 22.4 Selecting the onset

The closures follow the deuteron-only order for $n\le2$ and the descent pattern from $n=3$. The engine selects the onset by synchrony pricing: tier $n$ exposes $n+1$ radial contacts, the lock of Chapter 18 requires $q=4$, a missing contact costs one engaged-resistance unit and a completed graph saves one. The unit change is $q-(n+1)$ while $n+1<q$ and $-(n+1-q+1)$ afterwards, so that the response changes sign at the completed coordination, $n=q-1=3$.

**Executed (T3).** The unit change for $n=0\ldots8$ is $3,\,2,\,1,\,-1,\,-2,\,-3,\,-4,\,-5,\,-6$: positive up to $n=2$ and negative from $n=3$, with `triton_descent_onset` $=q-1=3$ for $q=4$. In the one-parameter family of schedules with onset $n_0=1\ldots6$ (triton shells entering from $n_0$), the closure lists are

| $n_0$ | first seven closures |
|---|---|
| 1 | 2, 6, 14, 28, 50, 82, 126 |
| 2 | 2, 8, 14, 28, 50, 82, 126 |
| 3 | 2, 8, 20, 28, 50, 82, 126 |
| 4 | 2, 8, 20, 40, 50, 82, 126 |
| 5 | 2, 8, 20, 40, 70, 82, 126 |
| 6 | 2, 8, 20, 40, 70, 112, 126 |

Table 22.1. Closure lists of the onset family, executed (T3). Only $n_0=3$ reproduces the observed list.

The reading is limited. The family is scored here against the observed list, and that is exactly what a derivation may not do: a separate contact-dynamical derivation must reproduce the pricing rather than use the closure list to choose the onset. The synchrony pricing selects 3 from $q=4$ without the list, but the pricing rule itself stays open (the engine's open item NP33). A second route, $F(n)>K_3=12\iff n\ge3$, agrees arithmetically but rests on the premise that tier members contact one core, which is not established; it is a candidate and not a confirmation.

## 22.5 Do the link counts fit a polyhedral shell?

If the links of a tier are the edges of a convex polyhedron with the $B(n)$ shell directions as vertices, then Euler's formula $V-E+F=2$ with every face having at least three edges gives $E\le3V-6$. With $V=B(n)$ and $E=R(n)$ this requires $n(n+1)\le6n$, that is $n\le5$.

**Executed (T4).**

| $n$ | $V$ | $E$ | $F=2-V+E$ | $3V-6$ | |
|---|---|---|---|---|---|
| 3 | 8 | 12 | 6 | 18 | fits |
| 4 | 10 | 20 | 12 | 24 | fits |
| 5 | 12 | 30 | 20 | 30 | fits (triangulated) |
| 6 | 14 | 42 | 30 | 36 | exceeds |
| 7 | 16 | 56 | 42 | 42 | exceeds ($56>42$) |
| 8 | 18 | 72 | 56 | 48 | exceeds |

Table 22.2. Euler consistency of the link counts, executed (T4).

For $n=3,4,5$ the counts are those of the cube, a ten-vertex solid with twelve faces and the icosahedron. For $n\ge6$ no convex polyhedron has $R(n)$ edges on $B(n)$ vertices. This is the engine's open item at $D_{42}$ (contact topology against $3V-6$), reproduced as an arithmetic consequence: the link count of the $D_{42}$ tier cannot be the edge set of a convex shell of 14 vertices. The count law and the seating geometry are two statements; the first can stand while the geometric reading of the second fails beyond $n=5$ (residual R22.2).

## 22.6 Triton parity

The engine's parity lock states that stable odd-$Z$ nuclei carry an odd triton count (the lone rod on the inward seat) and that an odd-$Z$ nucleus with an even triton count is a misfit. Since $n_t=N-Z$, an even count with odd $Z$ means odd $N$. **Executed (T5).** The engine's `triton_parity_misfit(Z,A)` equalled "$Z$ odd, $N$ odd, $N\ge Z$" on every point of $1\le Z\le120$, $1\le A\le400$, and over the embedded table the misfit set is the nine species $^2$H, $^6$Li, $^{10}$B, $^{14}$N, $^{40}$K, $^{50}$V, $^{138}$La, $^{176}$Lu, $^{180}$Ta, equal to the engine's light stable odd–odd set together with its long-lived radioactive set. The rule is the odd–odd rule restated in the module counts (Chapter 20, Section 20.6); its native content is the unpaired rod with no partner to seal, and its sign and counting converge with the pairing account. The coincidence of the set with the odd–odd nuclides is not independent evidence for the seat picture.

## 22.7 Rigid instruments and deformable circulation

The engine records a hard-sphere instrument (NSEQ19: three-slot rule, contact-only collapse) that reproduced the *opening* of a triton shell (a rise of the rms radius of $+0.122\,R_p$ for the first shell, $13.6\sigma$, and $+0.047\,R_p$ for the second, $5.6\sigma$) and did not reproduce the *closing* contraction: the radius ratio rose by $3.8$ mfm per triton where the corpus falls by $4$ to $11$ mfm. These are the engine's recorded results; the instrument was not re-run here. A rigid sphere instrument cannot represent route deformation or circulating throughput. The repair is to add the omitted mechanical degrees of freedom while keeping an independent contact checker (Chapter 21); introducing arbitrary tightening terms chosen to force the closure would conceal the missing mechanism. The website mirror's opening and closing scales are unsourced placeholders and are not used.

## 22.8 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| (22.1), (22.2), the lattice count | Section 22.2 | DERIVED (exact), verified |
| the closure list 2, 8, 20, 28, 50, 82, 126 | `magic_numbers` | OBSERVED |
| (22.3) and the forward value 184 | Section 22.3 | COMPUTED; 184 is a forward value (PENDING observation) |
| pricing rule and onset $n=3$ | engine's NP33 | the engine's premise (open); $q=4$ from Chapter 18 |
| Table 22.1 | Section 22.4 | COMPUTED; scored against the observed list |
| Table 22.2 | Section 22.5 | DERIVED (exact) |
| NSEQ19 opening and closing results | engine header | engine-recorded; not re-run here |

**Residuals.**

* **R22.1 — the onset.** The pricing rule that selects $n=3$ is open; a derivation that does not use the closure list is outstanding.
* **R22.2 — polyhedral shells beyond $n=5$.** The link counts for $n\ge6$ exceed the polyhedral edge bound; the contact topology of $D_{42}$ and later is unresolved.
* **R22.3 — closing contraction.** The closing tightening of a triton shell is not reproduced; the missing degrees of freedom are not identified.
* **R22.4 — shared counting.** The sequence of closures cannot discriminate from the prevailing account at the counting level.
* **R22.5 — the forward value.** $N=184$ is a formula extension; no observation is recorded.

## 22.9 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch22_interstitial_seating_and_packing
```

Criteria were registered in `Textbook/validation/ch22_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch22_run1_output.txt`) is the run of record and met every criterion.

## 22.10 Exercises and answers

**Exercise 1.** Verify $F(3)=B(3)+R(3)$.

*Answer.* $F(3)=20$, $B(3)=8$, $R(3)=12$.

**Exercise 2.** Compute the closure after the sixth tier of the schedule, $126$, from (22.3).

*Answer.* $82+R(5)+B(6)=82+30+14=126$.

**Exercise 3.** Which closure does the schedule with $n_0=4$ give instead of 28?

*Answer.* With onset 4 the deuteron tiers fill $F(3)=20$ before any triton shell enters, so the sum goes from 20 to 40; the triton shell $B(4)=10$ then gives 50. The list is $2,8,20,40,50,\ldots$ and 28 is missed (Table 22.1).

**Exercise 4.** Show that $E\le3V-6$ fails first at $n=6$.

*Answer.* $n(n+1)\le6n$ iff $n\le5$.

**Exercise 5.** Why does an odd-$Z$ nucleus with an even $n_t$ have odd $N$?

*Answer.* $n_t=N-Z$ even and $Z$ odd give $N$ odd.

**Exercise 6.** Give one reason the match of the closure list is not by itself evidence for the seat picture.

*Answer.* $F(n)$ and $B(n)$ are the counts of a competing account (shared counting), and the onset is scored against the list it is meant to explain.

## 22.11 Scope

Established in this chapter: the closed forms (22.1)–(22.2) and their lattice origin; the independent build of the schedule and its forward value; the onset family and the uniqueness of $n_0=3$ within it, with the limitation on using the list; the Euler consistency of the link counts and its failure from $n=6$; and the equivalence of the triton-parity rule with the odd–odd rule.

Not established: the onset pricing (R22.1), the shells beyond $n=5$ (R22.2), the closing contraction (R22.3), discrimination from the shell model at the counting level (R22.4) and any observation at $N=184$ (R22.5).

*Where it leads.* Chapter 23 asks for the energy of such configurations: binding, restoring response and decay barriers, from one contact law.
