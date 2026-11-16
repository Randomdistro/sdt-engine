# Chapter 22 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch22_interstitial_seating_and_packing.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The seating schedule of `nuclear` (`laws.hpp:2171–2341`): the tier law $F(n)=(n+1)(n+2)$ as a bipartite double layer of triangular lattices, the split $F=B+R$ into a triton shell $B(n)=2(n+1)$ and a link remainder $R(n)=n(n+1)$, the cumulative closures $2,8,20,28,50,82,126$ and the forward value 184, the synchrony-pricing rule that selects the descent onset $n=q-1=3$ from the lock coordination $q=4$, the Euler-type consistency of the link counts with a polyhedral shell ($E\le3V-6$, flagged by the engine as an open debt at $D_{42}$), and the triton-parity rule. The measured closure list is a stored OBSERVED input (`magic_numbers`); the tests check arithmetic and consistency. What the schedule cannot yet do (reproduce the closing contraction of a triton shell) is recorded by the engine as PENDING and is not tested here; a rigid-sphere instrument cannot represent deformable circulation.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | enumeration of triangular-lattice points $\{(i,j):i,j\ge0,\ i+j\le n\}$ for $n=0\ldots5$ gives $1,3,6,10,15,21$; and the icosahedron ($V=12,E=30,F=20$) and cube ($8,12,6$) satisfy $V-E+F=2$ | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | closed forms for $0\le n\le40$: lattice enumeration of a layer $=(n+1)(n+2)/2$; the double layer $2\times$ that equals `tier_capacity(n)` $=(n+1)(n+2)$; $B(n)+R(n)=F(n)$; `triton_shell_capacity` and `surface_remainder` equal $2(n+1)$ and $n(n+1)$ | exact | yes |
| T2 | the schedule. The species-pure order built independently from the closed forms: $F(0)+F(1)+F(2)=20$, then $+B(3)$, $+R(3)+B(4)$, $+R(4)+B(5)$, $+R(5)+B(6)$, $+R(6)+B(7)$ gives the closures $20,28,50,82,126,184$; the engine's `closure(k)` for $k=0\ldots6$ equals $2,8,20,28,50,82,126$ and the stored `magic_numbers` (OBSERVED) equal them; the sub-shell sums $2,8,20,28,40,50,70,82,112,126,168,184$ of the header's species-pure order reproduce the closures at the expected positions; the forward value is 184 | exact | yes |
| T3 | onset. `triton_delta_resistance_units(n)` for $n=0\ldots8$ is positive for $n\le2$ and negative for $n\ge3$, and `triton_descent_onset` $=q-1=3$ with $q=4$. In the one-parameter family of schedules with onset $n_0\in\{1,\ldots,6\}$ (triton shells $B(n)$ enter from $n=n_0$; deuteron tiers fill the rest), exactly one value, $n_0=3$, reproduces the first four closures $2,8,20,28$ *and* the later closures $50,82,126$. Reported with the flag that the family is scored against the OBSERVED list, which the engine does not use to select the onset | exact | yes |
| T4 | Euler consistency of the shell link counts. With $V=B(n)$, $E=R(n)$, $F=2-V+E$: $E\le3V-6$ holds for $n=3,4,5$ (with $F=6,12,20$) and fails for $n=6,7$ ($E=42>36$ and $56>42$), so a convex polyhedral shell with $R(n)$ edges on $B(n)$ vertices does not exist for $n\ge6$; the first failure is at $n=6$ | exact | yes — a polyhedral realisation at $n=6$ would reject the finding |
| T5 | triton parity. The engine's `triton_parity_misfit(Z,A)` equals (Z odd and N odd and N $\ge$ Z) on the whole grid $1\le Z\le120$, $1\le A\le400$; over the embedded natural table the misfit set is printed and is predicted to be exactly $\{^2$H, $^6$Li, $^{10}$B, $^{14}$N, $^{40}$K, $^{50}$V, $^{138}$La, $^{176}$Lu, $^{180}$Ta$\}$ (the engine's L and H sets) | exact | yes |

Reported, not criteria: the sub-shell sums, the family table of T3.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch22_interstitial_seating_and_packing`
