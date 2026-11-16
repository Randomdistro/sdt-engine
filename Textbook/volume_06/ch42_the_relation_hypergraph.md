# Chapter 42 — The Relation Hypergraph

*Volume VI — Sz, Pressure History and Coupled Ratios.*
Draft of 10 November 2026. Notation: $A$ is the exponent matrix of the monomial relations (rows) over the quantity columns; $x_i=\ln(Q_i/Q_{i,0})$; "nullity" is the dimension of the null space of $A$. Executable companion: `Textbook/examples/ch42_the_relation_hypergraph.py` (exact rational arithmetic with Python `fractions`, no linear-algebra library); pre-registration and captured output in `Textbook/validation/`. The data are the frozen inventory `EXACT_CONSTRAINTS2.json` of the Spaz atlas, used as stored. The counts belong to that inventory.

## 42.1 Exact constraints

A monomial relation $\prod_iQ_i^{A_{ji}}=C_j$ gives $A\,x=0$ for matched states with fixed coefficients; a changing $C_j$ belongs in the variable vector. Exact rational row reduction determines the rank, and a null-space basis $B$ gives $x=Bp$. Hyperedges retain multi-quantity relations; pairwise drawings are only projections of that structure.

The frozen inventory has $107$ quantity columns and $63$ monomial relations (and, in the atlas, $28$ nonlinear operators that are not part of this matrix). **Executed (V1, T1, T2).** The elimination routine was first checked on small known matrices: $\begin{pmatrix}1&2&3\\4&5&6\\7&8&9\end{pmatrix}$ has rank $2$ with null space spanned by $(1,-2,1)$; a $3\times5$ matrix of rank $2$ has nullity $3$ and one of rank $3$ nullity $2$; and $\begin{pmatrix}1/2&1/3\\1/4&1/6\end{pmatrix}$ has exact rank $1$ (a floating-point rank routine can fail on such a matrix). On the $63\times107$ matrix the exact rank is $63$ and the nullity $44$; the rank equals the number of rows. The stored null basis ($44\times107$) satisfies $A\,B^T=0$ exactly, has rank $44$, and spans the same space as the instrument's own null space (dimension $44$). The stored rank and null basis are confirmed by an independent exact computation.

Nullity includes unlinked quantities, unit directions and physical response freedom: it is not a count of fundamental dimensions of nature. No connection to the 44-octave reference of Chapter 44 follows from the numerical equality of the two integers.

## 42.2 Every relation carries information

**Executed (T3).** Removing any one of the 63 relations lowers the rank to 62, for each of the 63: none is implied by the others. The inventory therefore has no redundancy. An inventory in which a relation could be removed without lowering the rank would count one piece of information twice.

## 42.3 Pairwise projections lose the structure

**Executed (T4).** Of the 63 relations, $5$ have exactly two non-zero exponents (pure pairwise relations) and $58$ have three or more (the largest has five); none has a single one. The pairwise sub-matrix has rank $5$, so $58$ of the $63$ independent relations are not supplied by any combination of pairwise rows. A pairwise drawing of this inventory would therefore contain under a tenth of its relation content; the hypergraph is not a notational convenience.

## 42.4 Invariants and response routes

A vector $w$ with $w^TB=0$ defines an invariant product across every admissible response of the monomial system; the space of such vectors is the row space of $A$, of dimension $63$ here. A product can also be invariant only along one selected route, which requires $w^Ta(S)=0$ for the route's log-derivatives (Chapter 41). Physical conservation additionally needs a reservoir and a flux law: an algebraic invariant is not automatically conserved energy or momentum. For a nonlinear relation $F_j(Q,S)=0$, differentiation gives $Ja+\partial_SF=0$ with $J_{ji}=\partial F_j/\partial\ln Q_i$; the rank of $J$ can change near a phase boundary, so the operator layer keeps branch events and signed variables rather than replacing every equation by a monomial fit. The $28$ nonlinear operators were not examined here.

## 42.5 Units and independent information

Dimensional rescaling directions lie in the null space of homogeneous relations; the rank of the dimensional matrix is to be subtracted only after those directions have been verified, not guessed from symbol names. New measured input removes physical freedom only when the measurement chain adds independent information.

**Executed (T5).** Appending the sum of two existing relations leaves the rank at $63$ (no information added). Appending the unit relation $x_j=0$, which fixes one quantity, raises the rank to $64$ for **all 107 columns**: no single quantity is determined by the inventory, and every column retains freedom. (A registered statement that some columns would already be determined was rejected; it is recorded in the pre-registration and not retuned.) Appending an integer row $1,2,\ldots,7,1,2,\ldots$ raises the rank to $64$ and lowers the nullity to $43$. A new relation is information exactly when it lies outside the row space; the operational test is the rank change, reported without retuning the existing relations.

## 42.6 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| the matrix, the stored null basis, the stored rank | `EXACT_CONSTRAINTS2.json` | the frozen inventory (the relations are the atlas's; their sources were not re-audited here) |
| rank 63, nullity 44, independence, pairwise counts | Sections 42.1–42.3 | COMPUTED (exact rational arithmetic) |
| addition tests | Section 42.5 | COMPUTED (exact) |

**Residuals.**

* **R42.1 — the nonlinear layer.** The 28 nonlinear operators and their Jacobian rank changes are not examined.
* **R42.2 — provenance of the relations.** Each of the 63 relations rests on a source in the atlas; the matrix was verified as arithmetic, not audited for physical content.
* **R42.3 — meaning of the nullity.** The null space mixes unlinked quantities, unit directions and physical freedom; it is not a count of dimensions.
* **R42.4 — the dimensional matrix.** The rescaling directions were not separated.
* **R42.5 — the integer coincidence.** The value 44 of the nullity and the 44 octaves of Chapter 44 are not related by anything here.

## 42.7 Implementation and verification

```
bash Textbook/tools/py_run.sh ch42_the_relation_hypergraph
```

Criteria were registered in `Textbook/validation/ch42_PRE_REGISTRATION.md` before the instrument existed, after the matrix file had been inspected for its shape only. Run 1 (`ch42_run1_output.txt`) confirmed every exact count and rejected one registered statement (some column already determined). Run 2 (`ch42_run2_output.txt`) is the run of record and met every criterion as recorded, including that rejection.

## 42.8 Exercises and answers

**Exercise 1.** What are the rank and nullity of $\begin{pmatrix}1&1&0\\0&1&1\\1&2&1\end{pmatrix}$?

*Answer.* The third row is the sum of the first two: rank 2, nullity 1 (null vector $(1,-1,1)$).

**Exercise 2.** Why is the nullity of the inventory $44$?

*Answer.* $107-63$: the rank is 63 (the rows are independent) and the matrix has 107 columns.

**Exercise 3.** What does T3 show about the inventory?

*Answer.* Every relation is independent of the other 62; none can be derived from them.

**Exercise 4.** Why can a pairwise drawing not represent the inventory?

*Answer.* Only five relations are pairwise; the pairwise rows span a space of dimension 5, leaving 58 independent relations outside it.

**Exercise 5.** When does a new measurement remove physical freedom?

*Answer.* When the relation it gives lies outside the row space of $A$ (the rank rises) and its measurement chain is independent of the existing relations.

**Exercise 6.** Why is a floating-point rank not used?

*Answer.* Rational entries such as $1/3$ and $1/6$ can produce spurious near-zero pivots; exact arithmetic gives the rank without a tolerance.

## 42.9 Scope

Established: the exact rank $63$ and nullity $44$ of the frozen inventory, the stored null basis, the independence of all 63 relations, the dominance of multi-quantity relations (58 of 63), and that no single quantity is determined by the inventory.

Not established: the nonlinear operators (R42.1), the physical content of each relation (R42.2), the meaning of the null space (R42.3), the dimensional rescalings (R42.4) and any relation of the integer 44 to the octave count (R42.5).

*Where it leads.* Chapter 43 asks what selects a route through the admissible manifold: the constitutive operator.
