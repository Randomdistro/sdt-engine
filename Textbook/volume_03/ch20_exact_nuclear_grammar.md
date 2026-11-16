# Chapter 20 — Exact Nuclear Grammar

*Volume III — Persistent Structures and Nuclear Construction.*
Draft of 9 November 2026. Notation: this chapter uses none of the circulation-boundary symbols of `Textbook/NOTATION_LEDGER.md`. $Z$ is the proton count, $N$ the neutron count, $A=Z+N$; $n_d$ and $n_t$ are the deuteron and triton counts of the grammar. Executable companion: `Textbook/examples/ch20_exact_nuclear_grammar.cpp`; pre-registration and captured output in `Textbook/validation/`. All tests are on exact integers.

## 20.1 The physical question

The nuclear construction rule says that a nucleus of $Z\ge2$ is one alpha core plus $n_d$ deuterons plus $n_t$ tritons (Chapter 19 gave the modules and their slots). This chapter asks what that statement is as arithmetic, how far it extends, and what a count of modules can and cannot be evidence for. The answer has two halves. The grammar is an exact, invertible integer transform, so its algebra can be verified exhaustively. And because it is an invertible relabelling of $(Z,N)$, a rule stated in the module counts is a rule stated in $(Z,N)$: agreement of counts with the chart is a statement about the chart, and the physical content of the module picture lies in what the contact graph, the geometry and the energies (Chapters 21–24) do with the counts, not in the counts.

## 20.2 The affine map

With an alpha base $(Z,A)=(2,4)$, a deuteron adds $(1,2)$ and a triton adds $(1,3)$:

$$(Z,A)=(2,4)+n_d(1,2)+n_t(1,3),\qquad n_d,n_t\in\mathbb Z_{\ge0}. \tag{20.1}$$

The coefficient matrix $\begin{pmatrix}1&1\\2&3\end{pmatrix}$ has determinant $1$, so the map is invertible over the integers, with inverse $\begin{pmatrix}3&-1\\-2&1\end{pmatrix}$:

$$n_d=3Z-A-2,\qquad n_t=A-2Z. \tag{20.2}$$

In neutron terms, $n_t=N-Z$ and $n_d=2Z-2-N$. Nonnegative occupancy confines the map to the wedge

$$2Z\le A\le3Z-2\quad\Longleftrightarrow\quad Z\le N\le2Z-2. \tag{20.3}$$

An integer inverse outside the wedge is mathematically valid but is not an alpha-based construction with nonnegative modules.

**Executed (V1, T1, T2).** An independent Cramer's-rule routine reproduced the hand-derived compositions He-4 $(0,0)$, Li-6 $(1,0)$, Li-7 $(0,1)$, Be-9 $(1,1)$, B-10 $(3,0)$ and C-12 $(4,0)$. The matrix has determinant $1$ and the integer inverse times the matrix is the identity. The engine's `inverse_alpha` followed by `alpha_grammar` returned the original counts for all $40\,401$ pairs $0\le n_d,n_t\le200$, and `alpha_grammar` followed by `inverse_alpha` returned the original $(Z,A)$ for all $7\,140$ valid points of $1\le Z\le120$, $1\le A\le400$: zero mismatches in either direction. On the whole $48\,000$-point grid the engine's validity equalled the wedge (20.3) and the form $Z\le N\le2Z-2$, and its counts equalled $N-Z$ and $2Z-2-N$.

## 20.3 Light species and the helion base

Hydrogen-1, hydrogen-2 and helium-3 lie outside the alpha wedge. A helion base $(Z,A)=(2,3)$ gives the shifted grammar $n_t=A-2Z+1$, $n_d=3Z-A-3$, which is again an affine bijection. Executed (V1, T3): He-3 is $(0,0)$ on the helion base and valid; hydrogen-1 and hydrogen-2 are invalid on both bases. The engine's helion-base validity equalled its two inequalities on the whole grid (T2). The base change gives a representation domain for helium-3 and nothing more: it does not supply a binding energy or a lifetime, and hydrogen-1 and hydrogen-2 have no module representation at all in either grammar.

## 20.4 The embedded table

The engine embeds 287 natural isotopes (CIAAW reconstruction) in `nuclear::natural_basis` and enforces seven aggregate totals by `static_assert`. These were recomputed by the instrument from the raw $(Z,A)$ pairs alone, with the instrument's own formulas (T3):

| quantity | recomputed | stored |
|---|---|---|
| records | 287 | 287 |
| alpha-valid | 284 | 284 |
| alpha-invalid | 3 (H-1, H-2, He-3) | 3 |
| $\sum n_d$ | 7658 | 7658 |
| $\sum n_t$ | 5228 | 5228 |
| $\sum\lfloor n_t/2\rfloor$ | 2560 | 2560 |
| odd-$A$ count ($\sum n_t \bmod 2$) | 108 | 108 |

Table 20.1. Aggregates of the embedded table, recomputed independently (T3). The table is strictly increasing in $(Z,A)$, so it has no duplicate records.

Two further identities hold: $\sum(n_d+n_t)=\sum(Z-2)=12886$ over the valid records, and every valid record satisfies $Z\le N\le2Z-2$. These aggregates are consequences of the list of records and of the transform. They test that the table was transcribed consistently with the transform and say nothing about whether the module picture is physical. The statement that 284 of 287 natural nuclides lie in the wedge is the statement that they satisfy $Z\le N\le2Z-2$, a band of width $Z-1$ in $N$ that contains the whole stability valley for $Z\ge3$ (the neutron-to-proton ratio of $^{238}$U is $146/92=1.59$, inside the limit $(2Z-2)/Z=1.98$ at $Z=92$). The coverage is therefore expected from the shape of the valley and does not count as evidence for the modules. Table membership is also not a stability classification: the table includes radioactive primordial species (residual R20.2).

## 20.5 Binary rearrangement arithmetic

For a binary split $P\to L+H+\nu n$ with $Z_P=Z_L+Z_H$ and $A_P=A_L+A_H+\nu$, adding the daughter ledgers of the linear forms (20.2) gives, exactly,

$$\Delta D=(n_{d,L}+n_{d,H})-n_{d,P}=\nu-2,\qquad \Delta T=(n_{t,L}+n_{t,H})-n_{t,P}=-\nu. \tag{20.4}$$

Take $^{236}$U $\to$ $^{94}$Sr $+\,^{140}$Xe $+\,2n$: the counts are $(38,52)\to(18,18)+(20,32)$, so $\Delta D=0$, $\Delta T=-2$.

**Executed (T4).** The identities (20.4) were checked over every parent in the wedge with $3\le Z_P\le92$, every light daughter with $3\le Z_L\le Z_P-3$, every $\nu\in\{0,\ldots,6\}$ and every heavy daughter that is also in the wedge: $19\,427\,330$ splits (by $\nu=0,\ldots,6$: $2\,786\,146$, $2\,786\,146$, $2\,786\,146$, $2\,782\,318$, $2\,774\,662$, $2\,763\,352$, $2\,748\,560$). The identities held for all, and the engine's snap class (clean for $\nu=2$, mixed for $\nu=3$, adjacent for $\nu=4$, other otherwise) equalled the class implied by $\nu$ alone in every case. The class is a renaming of the neutron multiplicity. The arithmetic selects no split probability and does not give a mechanism of fission.

## 20.6 What the counts can and cannot be evidence for

The map $(Z,N)\mapsto(n_d,n_t)=(2Z-2-N,\,N-Z)$ has determinant $1$ and inverse $(Z,N)=(2+n_d+n_t,\;2+n_d+2n_t)$ (T5). The engine's overlay quantities are therefore restatements in $(Z,N)$: triton load $=N-Z$, deuteron load $=2Z-2-N$, row coordinate $=Z-2$, column coordinate $=n_d-n_t=5Z-2A-2$, the golden boundary $n_d=n_t$ is $2A=5Z-2$, and the odd-valence flag is $(N-Z)\bmod2$. All six agreed with their $(Z,N)$ forms on each of the $7\,139$ wedge points tested.

Consequences: a count of modules in a nucleus is determined by its chart position, so the correlation of a module count with any property that is itself a function of $(Z,N)$ (neutron excess, parity of $N-Z$, the position of a shell closure) is the correlation of that property with $(Z,N)$. Independent evidence for the module picture has to use a label that is not a function of $(Z,N)$ alone: a contact graph that satisfies the slot rule (Chapter 21), a geometry that satisfies exclusion (Chapter 22), a relaxed energy (Chapter 23), a frozen configuration used for several observables (Chapter 24). The grammar fixes what is to be built; whether it can be built is the content of those chapters.

## 20.7 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| the grammar (20.1)–(20.3), helion base | Sections 20.2–20.3 | DERIVED (exact integer algebra), verified exhaustively |
| the 287 $(Z,A)$ pairs of the table | `natural_basis` | OBSERVED (isotope list; CIAAW reconstruction, as stored) |
| the aggregates of Table 20.1 | Section 20.4 | COMPUTED from the table; consistency, not prediction |
| identities (20.4) and the class names | Section 20.5 | DERIVED (exact) |
| coverage of the table by the wedge | Section 20.4 | COMPUTED; expected from the valley, not evidence |

**Residuals.**

* **R20.1 — coordinate versus module.** That the module counts correspond to modules that can be built under the contact rule is not shown by the arithmetic; it is the subject of Chapters 21–24.
* **R20.2 — stability and table membership.** The embedded table lists natural nuclides including radioactive primordial species; membership is not a stability classification.
* **R20.3 — fission.** The identities (20.4) fix the change in module counts for a given $\nu$; they give no split probability and no mechanism.
* **R20.4 — the choice of base.** The alpha base for $Z\ge2$ and the helion base for helium-3 are conventions of the construction; hydrogen-1 and hydrogen-2 are outside both.
* **R20.5 — the range.** The table ends at $Z=92$; the grammar is stated beyond it but not embedded.

## 20.8 Implementation and verification

```
powershell -File Textbook\tools\tb_run.ps1 -Stem ch20_exact_nuclear_grammar
```

Criteria were registered in `Textbook/validation/ch20_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch20_run1_output.txt`) is the run of record and met every criterion.

## 20.9 Exercises and answers

**Exercise 1.** Decompose $^{208}$Pb.

*Answer.* $n_t=208-164=44$, $n_d=3\cdot82-208-2=36$. Check: $Z=2+36+44=82$, $A=4+72+132=208$.

**Exercise 2.** Decompose $^{56}$Fe.

*Answer.* $n_t=56-52=4$, $n_d=78-56-2=20$. Check: $Z=2+20+4=26$, $A=4+40+12=56$.

**Exercise 3.** Show that (20.4) follows from (20.2).

*Answer.* $\Delta D=3(Z_L+Z_H-Z_P)-(A_L+A_H-A_P)-2(2-1)=0+\nu-2$ and $\Delta T=(A_L+A_H-A_P)-2\cdot0=-\nu$.

**Exercise 4.** Derive the wedge (20.3) from $n_t\ge0$ and $n_d\ge0$.

*Answer.* $n_t=A-2Z\ge0$ gives $A\ge2Z$. $n_d=3Z-A-2\ge0$ gives $A\le3Z-2$. With $N=A-Z$ these are $N\ge Z$ and $N\le2Z-2$.

**Exercise 5.** Why does the existence of a unique decomposition of every wedge point not show that nuclei are built from modules?

*Answer.* Uniqueness follows from the determinant being 1: every integer point of a cone has a unique nonnegative integer coordinate in any unimodular basis. It is a property of the lattice, not of nature.

**Exercise 6.** For $^{236}$U $\to$ $^{94}$Sr $+\,^{140}$Xe $+\,2n$, verify $\Delta D=0$.

*Answer.* $^{94}$Sr has $n_d=114-94-2=18$ and $^{140}$Xe has $n_d=162-140-2=20$; $^{236}$U has $n_d=276-236-2=38$. $18+20-38=0=\nu-2$.

## 20.10 Scope

Established in this chapter: the exactness, unimodularity and inversion of the grammar, verified exhaustively on grids of $4\times10^4$ and $4.8\times10^4$ points; the wedge in neutron form; the helion base and the status of the three light species; the recomputation of the seven aggregates of the embedded table; the exact binary-rearrangement identities over $19\,427\,330$ splits; and the statement that the counts are a relabelling of $(Z,N)$.

Not established: that the modules are physical (R20.1), the stability of table members (R20.2), any fission mechanism or probability (R20.3), and the status of the base conventions (R20.4).

*Where it leads.* Chapter 21 derives the contact capacity of a module graph and the embedding constraints that a count cannot see.
