# Chapter 64 — Open Derivations and the Research Frontier

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: the eight closure tasks are labelled K (the contact-response operator), P (particle route geometry and reconnection), N (nuclear deformable seating), A (the atomic mode-response operator), S (stellar processing power), Z (Sz: relative sector response and progression rate), C (cosmological joint model) and B (compact boundaries); V labels verification and bookkeeping items; $R_{n.k}$ is residual $k$ of Chapter $n$. Executable companion: `Textbook/examples/ch64_open_derivations_and_research_frontier.py` (Python standard library; reads the manuscript chapters as text and writes `Textbook/sources/RESIDUAL_LEDGER.csv` and `Textbook/sources/ENGINE_PROPOSALS.csv`); pre-registration and captured output in `Textbook/validation/`. No physical value is used. This chapter closes the manuscript sequence and preserves every determining physical task as a stated calculation, not as an invented solved theorem.

## 64.1 Closure tasks with determining outputs

**K — the contact-response operator.** The central remaining operator links contact deformation to the directional impulse, stored energy, relay duration and outgoing redistribution. Completing it would remove freedoms that the book carries as transfer coefficients (Chapters 11, 12, 14), tick-rate-response branches (Chapters 45 and 48) and channel rates (Chapters 10 and 35). A single scalar pressure law is insufficient when orientation and history alter the response (Chapters 9 and 43). Determining output: one operator, evaluated on a small construction, that yields the directional impulse and the relay duration together, with a shared parameter ledger.

**P — particle route geometry.** Stable route geometry and reconnection dynamics, determining aspect ratios, barriers and lifetimes (Chapters 17–19). Determining output: a route geometry that yields the electron, proton and neutron structures and the neutron lifetime from one construction.

**N — nuclear seating.** One deformable seating construction predicting the closure tightening, the binding and the isotope moments while retaining the existing count generator (Chapters 20–24). The closing tightening of the triton shell and the contact capacity beyond the stated rule are open. Determining output: a seating that reproduces the tier counts of Chapter 22 and predicts the tightening of Chapter 23 without a new parameter.

**A — the atomic mode-response operator.** A shared mode-response operator predicting spectra, line rates and detector coupling (Chapters 25–29, 50). Determining output: one operator for a ladder of lines, a linewidth and a detector response, with the registration statistics of Chapter 50 derived and not assigned.

**S — stellar processing power.** The absolute processing and release power from the same mechanism, not the measured solar wattage (Chapter 37). Determining output: a luminosity and a neutrino rate from the mechanism, compared with the measured values after they are printed.

**Z — state, history and strong depth.** The relative sector response and an independently determining progression rate $dS/d\tau$ (Chapters 41–48). Determining output: a measured or derived nonzero relative response, then a predicted crossing route and a duration (Chapter 46), without freezing an unmeasured sector.

**C — the cosmological model.** Endpoint spectral response, material reprocessing, distance and acoustic history in one consistent model (Chapters 44, 47, 48, 54). Determining output: one history that fixes the flux, angular size and timing of the same sources with the same conventions (Chapter 54), and a distance relation that is not borrowed.

**B — compact boundaries.** Bounded stress and either a continuation or a derived arrest state (Chapters 40, 53). Determining output: the contact stress and the interior continuation in the depth branch, and the four checks of Chapter 53 passed together by a derived constitutive law, not a stand-in. None of these tasks is completed by changing a notation or by extending a weak-depth series beyond its domain.

## 64.2 What the manuscript records as open

**Executed (V1, T1).** The extractor and the keyword mapper were checked on literal inputs and the topological sort on a chain and on a cycle. The residuals of Chapters 1–63 were then read: every one of the 63 chapters carries residual identifiers $R_{n.k}$ (unique and consecutive within each chapter) and the phrase "Not established": 330 residuals in all. Mapped by keyword to the closure tasks (T2): K 33, C 33, N 28, P 25, A 22, B 18, S 12, Z 8, with 78 to V (a residual may map to several tasks). The registered statement that at least 70 per cent of the residuals would map to a task or to V was **rejected**: $185$ of $330$ ($56.1$ per cent) did; the unmapped ones concern the foundations of the medium (the minimal deformation descriptor, dispersion, the void fraction), the ruleset's numbering and similar items that the task descriptions do not name; their chapter-by-chapter counts are in the run output and the rows are in `RESIDUAL_LEDGER.csv`. The task counts reflect keyword matches and not weights: the small count for Z does not mean that the task is small (R64.1).

**The nature of the open items (T3).** By keyword, 181 residuals ($54.8$ per cent) are derivation gaps (not derived, not computed, not supplied, owed), 14 are data gaps (no measured record loaded or compared), and 11 are proposals to the author about the engine, extracted into `ENGINE_PROPOSALS.csv`: Chapter 6 (`a_rad` stored to five digits), Chapter 7 (the quoted polynomial of $T(2,5)$), Chapter 8 (`step_locus` near the centre), Chapter 11 (a stale comment), Chapters 19 and 21 (`contact_capacity` for $\max(Z,N)<3$), Chapter 44 (the Wien constant and `a_rad`), Chapter 45 (the comment on `z_spectral`), Chapter 49 (`B_alpha`), Chapter 54 (the stored distance and duration scales) and Chapter 57 (unguarded domains). The first detector, which searched for the exact phrase "proposal to the author", found 5; the broader wording rule found these 11 (recorded in the pre-registration). Items of the same kind with wording that no keyword catches (for instance the missing $Z$ argument of the rotation-field function, Chapter 25, and the scale factor of `fine_structure_eV`, Chapter 27) may be absent from that file; it is a hand-off list, not a complete audit (R64.2). No file in `Engine/include/sdt/` was edited by this book.

## 64.3 Execution order

First derive and test the directional contact response on a small construction (K). Carry the same kernel through the normal traction, the recurrence timing and a transport ratio (the transport kernel of Chapter 56 is an existing instance of the third). Next solve the deuteron and triton and one atomic mode with unchanged local rules (N and A). Then predict a nuclear closure response and a stellar processing rate. Finally integrate the pressure history and the strong-depth transport with the same tick-rate conventions (C, B, Z).

**Executed (T4).** The dependency graph $K\to T$ (traction, recurrence timing, transport ratio), $T\to N$, $N\to C$, $C\to P$, with $K$ a prerequisite of each, is acyclic and its topological order is K, T, N, C, P (a graph with a cycle is rejected by the same routine). The order has two content requirements that a graph does not check: the same local rules must be carried unchanged from step to step, and each step ends in a prediction that is compared after it is printed.

The correspondence with economics supplies a constrained-allocation lens: dual sensitivities show which constraint controls a response and which measurement removes the most freedom (Chapter 43: $\partial F^*/\partial b=-\lambda$, executed). The physical constitutive functions still require contact mechanics. The decisive advance is one derived operator that replaces several independent coefficients, followed by a withheld cross-domain observation.

## 64.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| residual counts, task counts, nature counts | Sections 64.2–64.3 | COMPUTED (text extraction of the manuscript; keyword mapping) |
| `RESIDUAL_LEDGER.csv`, `ENGINE_PROPOSALS.csv` | `Textbook/sources/` | COMPUTED (330 and 11 rows) |
| dependency order | Section 64.3 | COMPUTED (topological sort of the stated graph) |
| closure tasks and determining outputs | Section 64.1 | stated calculations (no solved theorem is claimed) |

**Residuals.**

* **R64.1 — weights of the tasks.** The task counts are keyword matches of residual wording; they do not weigh the difficulty or the importance of a task.
* **R64.2 — completeness of the proposals list.** The 11 engine proposals are those caught by the wording rule; other engine discrepancies noted in the chapters may be missing from the file.
* **R64.3 — the unmapped residuals.** 145 residuals, mostly about the foundations of the medium, belong to no listed task; a task for the minimal deformation descriptor and the dispersion relation of the medium could be added.
* **R64.4 — the order.** The graph encodes the stated order only; no estimate of the effort or of the risk of a step is made.
* **R64.5 — no derivation is completed.** Every task of Section 64.1 remains a stated calculation.

## 64.5 Implementation and verification

```
bash Textbook/tools/py_run.sh ch64_open_derivations_and_research_frontier
```

(from Git Bash). Criteria were registered in `Textbook/validation/ch64_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch64_run1_output.txt`) failed two criteria (a registered coverage statement of the keyword mapper, rejected; a proposal-detection vocabulary that was too narrow, an instrument defect), both recorded. Run 2 (`ch64_run2_output.txt`) is the run of record and met every criterion, with the rejection asserted. Note of 16 November 2026: the review of the finished manuscript afterwards reworded thirteen residuals of Chapters 6, 15, 16, 18, 22, 26, 27, 30, 31, 32, 46 and 57 (the word "owed" replaced by "outstanding" or "remains to be derived"), and additions of the same date entered six new residuals (R1.7, R9.7, R11.7, R11.8, R17.7, R18.7) with the sections they belong to (9.2.1, 11.3.1, 18.7.1 and a passage of 17.3), which bear on tasks K and P. The instrument was not re-run; the counts of Section 64.2 and `RESIDUAL_LEDGER.csv` keep the run-2 wording, in which "owed" is one of the derivation-gap keywords.

## 64.6 Exercises and answers

**Exercise 1.** Which task would a derived hyperfine splitting from the nuclear contact geometry serve?

*Answer.* N and A together, through the shared contact construction (Chapters 24 and 27).

**Exercise 2.** Why is K first in the order?

*Answer.* The later steps carry the same kernel through other observables; without the kernel they would carry separate coefficients.

**Exercise 3.** What does the graph not check?

*Answer.* That the same local rules are unchanged between steps and that each prediction is compared only after it is printed.

**Exercise 4.** What does a derivation-gap residual differ from a data-gap residual in?

*Answer.* A derivation gap needs a calculation from the mechanism; a data gap needs a measured record to compare with.

**Exercise 5.** Why is the proposals file not a complete audit?

*Answer.* It is built from residual wording; discrepancies recorded in other wording or in the chapter text are not caught (R64.2).

**Exercise 6.** How would the completion of K change the ledger of Chapter 62?

*Answer.* Several CALIBRATED or CONSTRUCTION rows (transfer coefficients, channel rates, tick-rate branches) would become DERIVED rows with a shared kernel parameter, and the covariance block of the kernel would replace several independent ones.

## 64.7 Scope

Established: the closure tasks and their determining outputs as stated calculations; the manuscript's own record of what is open (330 residuals in 63 chapters; 181 derivation gaps, 14 data gaps, 11 engine proposals by keyword); the acyclic execution order K, T, N, C, P.

Not established: weights for the tasks (R64.1), the completeness of the proposals list (R64.2), a task for the foundations of the medium (R64.3), effort and risk (R64.4) and any of the derivations themselves (R64.5).

The sequence closes here. Every chapter of the 64 has a pre-registration, an executed instrument with captured output, a chapter text with its input ledger and residuals, and a statement of scope; every failed run is kept and accounted for (Chapter 63).
