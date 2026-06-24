# NP03D — Electron Threading Feasibility *(topological permission, with a real intersection test)*

**Purpose.** Ask whether `Z` electron paths can be **threaded through/around the nuclear topology without intersection** — a genuine non-overlap solve, not "rings parked outside the nucleus."

**Inputs.** NP03C nuclear topology (trefoil tubes at frozen NP03B sites).
**Outputs.** Per electron: a Hopf-fibre path through a proton's poloidal channel; a global **intersection report** (tube/tube, tube/loop, loop/loop) and minimum clearance.

**Method.** For each of the `Z` electrons, generate a Hopf-fibre circle linking an assigned proton's poloidal channel; run a segment–segment minimum-distance test against (a) every nucleon tube and (b) every other electron loop. Feasibility = a placement with **zero intersection** and clearance > 0.

**Fixed metrics.** (i) max electrons placeable with zero intersection; (ii) minimum tube/loop clearance (signed); (iii) whether a *full* Hopf fibration (every fibre pairwise linked, none crossing) is realisable for the shell electron count; (iv) clearance distribution.

**Null / negative control.** Random electron paths (no Hopf constraint) — expected high intersection rate; the Hopf solution must beat it.

**Failure criteria.**
```
feasibility declared WITHOUT an explicit numeric intersection test
Bohr-2n² ring simplification used as proof
"linked-loop styling" substituted for a real fibration solve
```
*(The v4 "trefoil electrons" used exactly those approximations — shell rings + 2n² + styling. That is feasibility **theatre**. NP03D replaces it with the intersection solver.)*

**Reuses.** the Hopf-fibre + poloidal-channel construction; `PPT05` (no free open strand). **Provenance:** class **D** (novel feasibility prediction) if a real solver passes; **F** if only theatre.
