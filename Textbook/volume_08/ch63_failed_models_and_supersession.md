# Chapter 63 — Failed Models and Supersession

*Volume VIII — Executable Reference, Verification and Research Closure.*
Draft of 10 November 2026. Notation: a *failed run* is a run output whose last line reports that criteria were not met (or whose exit code is not 0); a *record* is a dated section "Record of run K" of a chapter's pre-registration; the *run of record* is the run whose output is quoted. Executable companion: `Textbook/examples/ch63_failed_models_and_supersession.py` (Python standard library; reads `Textbook/validation/` as text and writes `Textbook/validation/FAILED_RUN_MANIFEST.csv`); pre-registration and captured output in `Textbook/validation/`. No physical value is used.

## 63.1 A failure identifies a premise

The first question is why the result occurred. A discrepancy can arise from the physical premise, the numerical instrument, a measurement convention or an inconsistent comparison, and the repair follows the cause. Changing a tolerance before the cause is identified hides information.

The spherical history of Chapters 58 and 59 illustrates two causes. Near-antipodal subtraction produced a real kernel defect (the haversine loses $\sqrt\epsilon$ near $\pi$: Chapter 58, relative error $1.2\times10^{-2}$ against $0$ for the five-part form), while near-pole conversion with $\mathrm{acos}$ introduced an instrument defect (Chapter 58: $\theta=0$ against $10^{-9}$; the registration records $1.2\times10^{-5}$ for polar observers against $1.6\times10^{-12}$ with $\mathrm{atan2}$). Both required numerical repair and neither supported a new physical claim. The registered impulse clause remained unmet ($2.34\times10^{-9}$ against $10^{-9}$) even after the trajectory clauses agreed, and is reported as unmet.

**Executed (V1, T1, T4).** The record parser, the classifier and a digest routine were checked on literal inputs. The run outputs under `Textbook/validation/` were then enumerated: 63 chapters with instruments, 117 run outputs, of which 48 are failed runs; each failed run is listed with its SHA-256 in `FAILED_RUN_MANIFEST.csv`. The 52 records classify by their own wording (a record may carry several classes): instrument defect 23, registration error 26, numerical (cancellation, rounding, stencil, overflow) 25, registered statement rejected 12, launcher failure 1; none is unclassified after the classifier's vocabulary was extended (below), and only 2 records are classified solely as a rejected statement. Records with an instrument defect or a registration error outnumber those classified only as a rejected statement ($49$ against $2$): most recorded failures were failures of the method, not of the object. The failures of the object appear as rejected statements, for instance the ratio of hyperfine to finite-size scales (Chapter 27), the ordering of the Mercury perihelion terms (Chapter 36), the disc-to-scalar ratio $1.345$ (Chapter 38), the rank rise for all 107 columns (Chapter 42), the sound-speed duration (Chapter 48), the NaN claim for `depth_from_c_far` (Chapter 57), the angular floor of the quadrature (Chapter 60) and the correlation of the quadrature coefficient with the drift (Chapter 61). Chapter 19 has three failed runs, Chapters 8, 35, 40, 60, 61 and 63 two each.

## 63.2 Preserve valid substructure

The nuclear rigid instrument's missing closure tightening does not erase the tier-count derivation. The Casimir thermal-occupation route's wrong separation dependence does not erase the independently checked mode-counting coefficient per unit amplitude (Chapter 52: the cutoff-free limit $-\pi^2/360$ to $1.4\times10^{-8}$, while thermal occupation at the present temperature gives a separation-independent pressure). A chemical well's missing stiffness does not automatically erase an isotope-response relation derived under a separately valid limit. Supersession therefore names the withdrawn premise and the surviving consequence; whole-file replacement without a dependency account can destroy valid results along with the failed approximation. In this book a rejected statement is kept in the pre-registration and asserted in the instrument, and the statements that stood in the same run are not withdrawn with it.

## 63.3 Chronology and evidence

Store the registration, instrument, execution capture, assessment and dated amendment. A later explanatory paragraph is not a substitute for an execution capture. An old link pointing to a relocated file receives a path mapping rather than a silent claim that the source vanished.

**Executed (T1–T3).** (T1) Every failed run is kept and listed; two run outputs of one chapter share a digest only in Chapter 59, where run 2 repeats run 1 by design after a comment-only edit (the registered statement that no two outputs would coincide was **rejected**, recorded). (T2) Every failed run is named by a record. The first execution found one run without one: Chapter 4 run 1 (criterion T5, closed form against direct summation, $2.63\times10^{-12}$ against $10^{-12}$, from cancellation in the closed form) had no record. A dated amendment was appended to `ch04_PRE_REGISTRATION.md`, derived from the captured outputs of runs 1 and 2 and marked as added on 2026-11-10; the run outputs themselves were not changed. Chapter 8 records its run 2 in an inline paragraph, which the first parser missed (an instrument defect). (T3) The last run of 62 of the 63 chapters says that all criteria were met; the exception at the time of each scan was this chapter's own run in progress, which is why the run of record is the third. The earlier chapters (3, 4 and others) predate the shared helper and print "SUMMARY: all pre-registered criteria met"; the detector accepts both formats after its repair.

The record of this chapter's own runs is an instance of the rule. Run 1 failed four criteria: a duplicate-digest statement rejected by Chapter 59's design, the inline-record parser, the earlier output format, and 6 unclassified records. Run 2 left one failure: 7 of 51 records ($13.7$ per cent) unclassified, against the registered limit of $10$ per cent, because the classifier's keywords had been written before the corpus was read; the phrases of the early records ("instrument limit", "instrument fault", "validation fault", "overflow", "misspecif", "derivation slip", "analytic slip", "correction of the") were added and the limit was not moved. Run 3 met every criterion.

## 63.4 Input ledger and residuals

| quantity | value | label |
|---|---|---|
| run-output counts, failed-run counts, class counts | Section 63.1 | COMPUTED (text extraction of `Textbook/validation/`) |
| digests | `FAILED_RUN_MANIFEST.csv` | COMPUTED (SHA-256 of the output files) |
| classification of records | Section 63.1 | COMPUTED by keyword; the records' own wording |
| spherical-history numbers | Chapters 58, 59 | quoted from those chapters and the registration |

**Residuals.**

* **R63.1 — keyword classification.** Classes are assigned from the records' wording by keywords; a record may carry several, and a misreading is possible; the counts are a guide to the pattern, not an audit of each failure.
* **R63.2 — premises behind the rejected statements.** The withdrawn premise and the surviving consequence were named in the records, not tabulated here.
* **R63.3 — outputs not covered.** Failed runs of instruments outside `Textbook/validation/` (the earlier investigations of the repository) are not in the manifest.
* **R63.4 — amendments.** The Chapter 4 record is an amendment added after the fact; it carries a dated marker but cannot show when the failure was first understood.
* **R63.5 — reproduction from the original premises.** The first execution of a repaired premise was not re-run from the original premises for every chapter; the captured outputs are the evidence.

## 63.5 Implementation and verification

```
bash Textbook/tools/py_run.sh ch63_failed_models_and_supersession
```

(from Git Bash). Criteria were registered in `Textbook/validation/ch63_PRE_REGISTRATION.md` before the instrument existed. Run 1 (`ch63_run1_output.txt`) failed four criteria and run 2 (`ch63_run2_output.txt`) one; both are recorded. Run 3 (`ch63_run3_output.txt`) is the run of record and met every criterion, with the Chapter 59 duplicate asserted as a rejection. Note of 16 November 2026: the counts of Section 63.1 are those of run 3, made before Chapter 64 had an instrument. The two runs of Chapter 64 (its run 1 failed two criteria and is recorded in its own pre-registration) and run 3 of Chapter 57 (a repeat that met every criterion) were added afterwards; the instrument was not re-run and `FAILED_RUN_MANIFEST.csv` does not list them.

## 63.6 Exercises and answers

**Exercise 1.** A criterion fails by a factor of 3 in a tolerance. What is asked first?

*Answer.* Why: the physical premise, the instrument (cancellation, stencil, window), the registration (arithmetic, domain) or the comparison convention; the tolerance is not changed until that is known.

**Exercise 2.** Why are rejected statements kept and asserted in the instrument?

*Answer.* They preserve the first prediction as it stood and show that the repaired run tested the same object; deleting or loosening them would erase information about the premise.

**Exercise 3.** What does a failed run without a record show?

*Answer.* A gap in the chronology: the output exists, but the cause and the repair are not stated (Chapter 4 run 1).

**Exercise 4.** Why is a repeated run with identical output not an overwrite?

*Answer.* It is a new numbered run whose output is byte-identical to the previous because the change was only a comment; the digest equality is expected and documented.

**Exercise 5.** Which surviving consequence follows from the failed thermal-occupation route of Chapter 52?

*Answer.* The mode-counting coefficient per unit amplitude, $-\pi^2/360$ in units $a\hbar c/d^3$, stands; the thermal-occupation pressure is separation-independent.

**Exercise 6.** What does a rise in instrument and registration errors relative to rejected statements say about the verification?

*Answer.* The method catches its own defects at a high rate before they reach the claims; it does not by itself measure how many claims about the object are true.

## 63.7 Scope

Established: that all 48 failed runs are kept with digests; that every failed run has a record (after one amendment); the classification of the 52 records by their wording; that the failures recorded are mostly failures of the method and that the rejected statements about the object are kept and named.

Not established: an audit of each classification (R63.1), the tabulated dependency of each rejected statement (R63.2), the failed runs outside the validation folder (R63.3), the time of understanding behind amendments (R63.4) and a reproduction from original premises for each chapter (R63.5).

*Where it leads.* Chapter 64 closes the sequence with the open derivations: the closure tasks, their determining outputs and the execution order.
