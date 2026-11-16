# Chapter 20 — pre-registration of the worked-example instrument

Registered 2026-11-09, before `Textbook/examples/ch20_exact_nuclear_grammar.cpp` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The exact integer grammar of `sdt::nuclear` (`Engine/include/sdt/nuclear.hpp`): the map $(Z,A)\mapsto(n_d,n_t)=(3Z-A-2,\ A-2Z)$ onto an alpha core plus $n_d$ deuterons plus $n_t$ tritons, its inverse $Z=2+n_d+n_t$, $A=4+2n_d+3n_t$, its validity wedge $2Z\le A\le3Z-2$, the shifted helion-base grammar $(n_d,n_t)=(3Z-A-3,\ A-2Z+1)$, the embedded natural-isotope table of 287 records with its seven stored aggregate totals, and the binary-rearrangement identities $\Delta D=\nu-2$, $\Delta T=-\nu$. The chapter's central statement is a limitation: the counts $(n_d,n_t)$ are an integer unimodular relabelling of $(Z,N)$, so a rule stated in counts is a rule stated in $(Z,N)$ and cannot by itself be independent evidence. The tests establish exactness and coverage and say nothing of binding, stability or lifetime. All tests are on exact integers.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | the `tb_common.hpp` helpers | as printed |
| V1 | hand-derived compositions by integer solution of $(Z,A)=(2,4)+n_d(1,2)+n_t(1,3)$ with an independent Cramer's-rule routine: He-4 $(0,0)$, Li-6 $(1,0)$, Li-7 $(0,1)$, Be-9 $(1,1)$, B-10 $(3,0)$, C-12 $(4,0)$; and the helion base: He-3 $(0,0)$ in the shifted grammar | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | unimodular inversion. The coefficient matrix from $(n_d,n_t)$ to $(Z,A)$, $\begin{pmatrix}1&1\\2&3\end{pmatrix}$, has determinant 1 and integer inverse $\begin{pmatrix}3&-1\\-2&1\end{pmatrix}$. For every $0\le n_d,n_t\le200$ the engine's `inverse_alpha` followed by `alpha_grammar` returns $(n_d,n_t)$ and `valid`; for every $1\le Z\le120$, $1\le A\le400$ with `valid`, `alpha_grammar` followed by `inverse_alpha` returns $(Z,A)$ | exact, exhaustive | yes — one mismatch rejects exactness |
| T2 | wedge equivalence. For every $1\le Z\le120$, $1\le A\le400$: `valid` $\iff 2Z\le A\le3Z-2\iff Z\le N\le2Z-2$ with $N=A-Z$; equivalently $n_t=N-Z$ and $n_d=2Z-2-N$. The helion-base grammar is valid exactly when $A-2Z+1\ge0$ and $3Z-A-3\ge0$ | exact, exhaustive | yes |
| T3 | the embedded table, recomputed with the instrument's own formulas from the raw $(Z,A)$ pairs only: 287 records; strictly increasing in $(Z,A)$ (no duplicates); alpha-invalid exactly $\{$H-1, H-2, He-3$\}$; helion-base status: H-1 invalid, H-2 invalid, He-3 valid with $(0,0)$; $\sum n_d=7658$, $\sum n_t=5228$, $\sum\lfloor n_t/2\rfloor=2560$, odd-$A$ count $=108$; $\sum(n_d+n_t)=\sum(Z-2)$ over valid records; all valid records satisfy $Z\le N\le2Z-2$ | exact | yes |
| T4 | binary rearrangement. Over every parent in the wedge with $3\le Z_p\le92$, every light daughter $(Z_l,A_l)$ in the wedge with $3\le Z_l\le Z_p-3$, $\nu\in\{0,\ldots,6\}$, and $(Z_h,A_h)=(Z_p-Z_l,\,A_p-\nu-A_l)$ in the wedge: $\Delta D=\nu-2$ and $\Delta T=-\nu$ exactly, and the engine's `binary_split` class equals the class implied by $\nu$ alone ($\nu=2$ clean, $\nu=3$ mixed, $\nu=4$ adjacent, else other). The number of splits enumerated is printed | exact, exhaustive | yes |
| T5 | relabelling. The map $(Z,N)\mapsto(n_d,n_t)=(2Z-2-N,\ N-Z)$ has determinant $1$ and inverse $(Z,N)=(2+n_d+n_t,\ 2+n_d+2n_t)$. The engine's overlay quantities agree with their $(Z,N)$ forms on the whole wedge grid: `triton_load` $=N-Z$, `deuteron_load` $=2Z-2-N$, `y_coord` $=Z-2$, `x_coord` $=5Z-2A-2=n_d-n_t$, `on_golden_boundary` $\iff2A=5Z-2$, `office_pop` $=(N-Z)\bmod2$ | exact, exhaustive | yes |

Reported, not criteria: the number of wedge points tested, the splits enumerated, the sums.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`powershell -File Textbook\tools\tb_run.ps1 -Stem ch20_exact_nuclear_grammar`
