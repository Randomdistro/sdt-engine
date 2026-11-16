# Chapter 64 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch64_open_derivations_and_research_frontier.py` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). The instrument reads the manuscript chapters as text and writes `Textbook/sources/RESIDUAL_LEDGER.csv` and `Textbook/sources/ENGINE_PROPOSALS.csv`; no physical value is used. Run from Git Bash (`bash Textbook/tools/py_run.sh ch64_open_derivations_and_research_frontier`).

Object. The open derivations of the manuscript as recorded in its own residuals $R_{n.k}$ (each chapter's list of what is not established), their grouping under the closure tasks of the chapter, and the execution order. The closure tasks are: (K) the contact-response operator linking contact deformation to directional impulse, stored energy, relay duration and outgoing redistribution; (P) particle route geometry and reconnection (aspect ratios, barriers, lifetimes); (N) one deformable seating construction for nuclei (closure tightening, binding, isotope moments) with the existing count generator retained; (A) a shared atomic mode-response operator (spectra, line rates, detector coupling); (S) absolute stellar processing and release power from the same mechanism; (Z) Sz: the relative sector response and an independently determining progression rate; (C) cosmology: endpoint spectral response, material reprocessing, distance and acoustic history in one model; (B) compact boundaries: bounded stress and continuation or a derived arrest state. The execution order of the chapter is: K first (directional response on a small construction); the same kernel through normal traction, recurrence timing and a transport ratio; then deuteron/triton and one atomic mode with unchanged local rules; then a nuclear closure response and a stellar processing rate; finally pressure history and strong-depth transport with the same tick-rate conventions. (a) Completeness: each of Chapters 1–63 has residual items with identifiers $R_{n.k}$ and a statement of what is not established. (b) Mapping: each residual is assigned by keyword to one or more closure tasks or to a verification and bookkeeping group (V). (c) Nature: residuals are grouped as derivation gaps (not derived, computed, supplied, owed), data gaps (no measured record loaded or compared), and proposals to the author about the engine (canon untouched); the proposals are extracted into one hand-off file. (d) Order: the task dependency graph implied by the execution order is acyclic and its topological order is K, T, N, C, P where T is the normal-traction/recurrence/transport step that reuses K.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | none (Python) | |
| V1 | the residual extractor on the literal text `* **R5.1 — a title.** the rest of it.` returns id (5,1), title "a title" and text "the rest of it."; the keyword mapper returns {K} for "no contact-response operator is derived" and {V} for "the citations were not checked line by line"; the topological sort of K→T→N→C→P returns that order and rejects a graph with a cycle | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | completeness. At least 61 of the 63 chapters have at least one residual id $R_{n.k}$; at least 250 residuals are extracted in total; for each chapter the ids are unique; the chapters without a residual list or with non-consecutive ids are listed; at least 61 chapters contain the phrase "Not established" or a Scope section | as stated | yes |
| T2 | mapping. At least 70 per cent of the residuals map to at least one of the 8 closure tasks or to group V; each of the 8 closure tasks has at least 5 residuals; the counts per task are reported | as stated | yes |
| T3 | nature. At least 50 per cent of residuals are derivation gaps by keyword; at least 10 residuals are proposals to the author about the engine and are written to `ENGINE_PROPOSALS.csv`; `RESIDUAL_LEDGER.csv` has one line per residual | as stated | yes |
| T4 | order. The graph K→T→N→C→P (with K also required by N, C and P) is acyclic; its topological order is K, T, N, C, P; every task other than K has K as a prerequisite | as stated | yes |

Reported, not criteria: residual counts per chapter and per task; the proposals list.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Record of run 1; one registered statement rejected and one instrument defect (2026-11-10)

Run 1 (`ch64_run1_output.txt`): V1, all of T1 (63 of 63 chapters with residual ids, 330 residuals, consecutive unique ids in every chapter, the phrase "Not established" in every chapter), the per-task counts of T2 (K 33, P 25, N 28, A 22, S 12, Z 8, C 33, B 18, V 78) and the derivation-gap and ledger criteria of T3 (181 of 330 residuals by keyword; $54.8$ per cent), and all of T4 were met. Two criteria failed. (1) **T2, a registered statement rejected.** At least 70 per cent of the residuals were registered to map to a task or to V by keyword: $185$ of $330$ ($56.1$ per cent) did. The unmapped residuals concern the foundations of the medium (the descriptor, dispersion, the void fraction), the ruleset's numbering and similar items that the eight task descriptions do not name. The statement is kept and asserted in run 2; the mapper is not retuned. A post-run exploration (report only, marked as such) lists the unmapped residuals by chapter. (2) **T3, an instrument defect.** The registered criterion counts residuals that are proposals to the author about the engine (at least 10); the instrument searched for the exact phrase "proposal to the author" and found 5. A search of the residual texts for "propos" (excluding "proposition") and "stale comment" with a reference to the engine found 16 items that are proposals under other wording ("Proposed correction, pending", "proposal, not applied", "the proposed half-angle form", a stale comment): the instrument's vocabulary was too narrow for the registered meaning. The detector is repaired to the broader rule (proposal wording or a stale comment, referring to the engine, a header or an identifier; "proposition" excluded) and the criterion (at least 10) is unchanged. Run 2 is the run of record.

## Build line

`bash Textbook/tools/py_run.sh ch64_open_derivations_and_research_frontier`
