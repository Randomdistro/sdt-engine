# Chapter 42 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch42_the_relation_hypergraph.py` was written or run. The matrix file was inspected for its shape only (63 rows, 107 columns, stored null basis 44 rows, stored rank 63) and for the multiset of the most frequent entries; no rank or null-space computation had been run on it.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents).

Object. The frozen exact relation inventory of the Spaz atlas (`Projects/sdt-investigations/Investigations/SDT_Spaz_Cross_Domain_Atlas_2026-10-27_2/EXACT_CONSTRAINTS2.json`: 107 quantity columns, 63 monomial relations as rows of rational exponents, a stored null basis and a stored rank). A monomial relation $\prod Q_i^{A_{ji}}=C_j$ gives $A\,x=0$ for matched states with fixed $C_j$, $x_i=\ln(Q_i/Q_{i,0})$. The chapter recomputes exactly, with the instrument's own rational elimination (Python `fractions`, no library for linear algebra), what the atlas states: the rank, the nullity, the null basis, the independence of every relation, the content of pairwise projections, and the effect of adding information. The counts belong to the frozen inventory: nullity includes unlinked quantities, unit directions and physical response freedom and is not a count of fundamental dimensions; no connection to the 44-octave anchor follows from numerical equality.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | none (no helper in the Python instrument) | — |
| V1 | the elimination routine on small matrices: $\begin{pmatrix}1&2&3\\4&5&6\\7&8&9\end{pmatrix}$ has rank 2 and null space spanned by $(1,-2,1)$; a $3\times5$ matrix of rank 3 has nullity 2; the matrix $\begin{pmatrix}1/2&1/3\\1/4&1/6\end{pmatrix}$ has rank 1 (exact rationals, a floating-point rank routine can fail here) | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | exact rank of the $63\times107$ matrix by the instrument's elimination equals the stored rank 63; the nullity is $107-63=44$; the rank equals the number of rows | exact | yes — a different rank rejects the stored counts |
| T2 | the stored null basis (44 rows over 107 columns): $A\,B^T=0$ exactly; its own rank is 44 (the rows are independent) so it spans the whole null space | exact | yes |
| T3 | independence: removing any single relation lowers the rank to 62, for each of the 63 relations (so no relation is implied by the others) | exact | yes — a relation whose removal leaves rank 63 is redundant and rejects the claim that all 63 carry information |
| T4 | pairwise projections: the number of rows with exactly two non-zero entries (pure pairwise relations), with three or more (hyperedges), and the rank of the pairwise sub-matrix; the number of independent relations that no combination of pairwise rows supplies is $63-\mathrm{rank}_{\rm pair}$ (printed). Registered: at least one relation has three or more non-zero entries, and $63-\mathrm{rank}_{\rm pair}>0$ | as stated | yes — if every relation were pairwise the hypergraph structure would be vacuous |
| T5 | adding information: appending the sum of two existing rows leaves the rank 63; appending the unit relation $x_j=0$ for each column $j$ in turn raises the rank to 64 for at least one $j$ and leaves it at 63 for at least one $j$ (those columns already determined by the inventory); the number of columns for which the rank rises is printed (the number of columns not determined). Appending a fixed integer row with entries $1,2,3,\ldots$ cycling raises the rank to 64 | as stated | yes |

Reported, not criteria: the number of pairwise rows, hyperedges, the number of undetermined columns.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Build line

`bash Textbook/tools/py_run.sh ch42_the_relation_hypergraph`

## Record of run 1 (2026-11-10)

Run 1 (`ch42_run1_output.txt`) confirmed every exact count of the frozen inventory and rejected one registered statement. Met: V1 (five small known cases, including the exact-rational rank of $\begin{pmatrix}1/2&1/3\\1/4&1/6\end{pmatrix}$); T1 (exact rank 63, nullity 44, rank equal to the number of rows); T2 ($AB^T=0$ exactly for the stored null basis, whose own rank is 44, and the instrument's own null space has dimension 44 and the same span); T3 (removing any one of the 63 relations lowers the rank to 62: no relation is implied by the others); T4 (5 pairwise rows with two non-zero entries, 58 with three or more, maximum 5; the pairwise sub-matrix has rank 5, so 58 independent relations are not supplied by pairwise rows); and two clauses of T5 (the sum of two rows leaves the rank at 63; a fixed integer row raises it to 64).

**Rejected, kept.** The registered statement that the unit relation $x_j=0$ raises the rank for at least one column and leaves it unchanged for at least one (columns already determined by the inventory) is **rejected**: appending $x_j=0$ raises the rank to 64 for **all 107** columns, so the inventory determines no single quantity: every column retains freedom. The registered expectation was a guess that some quantities are fixed; the result is a property of the inventory (each relation is a homogeneous monomial relation among two or more quantities and no combination of them reduces to a single unit row). The clause is not retuned: run 2 keeps it and reports its rejection. Run 2 is the run of record.
