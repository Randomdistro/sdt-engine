# Chapter 63 — pre-registration of the worked-example instrument

Registered 2026-11-10, before `Textbook/examples/ch63_failed_models_and_supersession.py` was written or run.
Author: James Christopher Tyndall, Melbourne. Drafted by an LLM session; executed directly (no delegated agents). The instrument reads the files of `Textbook/validation/` as text and writes `Textbook/validation/FAILED_RUN_MANIFEST.csv`; no physical value is used. It is run from Git Bash (`bash Textbook/tools/py_run.sh ch63_failed_models_and_supersession`).

Object. The chronology and causes of failed runs recorded in this book. (a) A failure identifies a premise: the first question is why the result occurred; a discrepancy can arise from the physical premise, the numerical instrument, a measurement convention or an inconsistent comparison; the repair follows the cause; changing a tolerance before the cause is identified hides information. (b) Preserve valid substructure: supersession names the withdrawn premise and the surviving consequence; whole-file replacement without a dependency account can destroy valid results. (c) Chronology and evidence: the registration, instrument, execution capture, assessment and dated amendment are stored; a later explanatory paragraph is not a substitute for an execution capture. The instrument enumerates the run outputs of every chapter; a run is a failed run if its output contains "CRITERIA NOT MET" or an exit code other than 0; it checks that every failed run is kept (its file exists and its digest is recorded), that it is accounted for by a dated "Record of run K" section of its chapter's pre-registration, and that the last run of every chapter is the run of record (its output says "ALL CRITERIA MET"). Each record is classified by cause from its own text: launcher failure; instrument defect; registration error; registered statement rejected (a finding on the object or on the manuscript); numerical (cancellation, rounding, stencil); a record may carry several classes.

## Instrument validation (must pass before T-results are read)

| id | known answer | tolerance |
|---|---|---|
| V0 | none (Python) | |
| V1 | the record parser on a literal pre-registration text with the headings `## Record of run 1; two defects (date)` and `## Record of runs 2 and 3; one rejection (date)` returns the run sets $\{1\}$ and $\{2,3\}$; the classifier returns {instrument defect, numerical} for the text "an instrument defect from cancellation" and {registration error, registered statement rejected} for "a registration error; the registered statement ... is rejected"; the SHA-256 of "abc" | exact |

## Tests on the object

| id | statement | pass criterion | rejection class populated? |
|---|---|---|---|
| T1 | preservation. The number of run outputs under `Textbook/validation/` is at least 110 and the number of failed runs at least 40; every failed run is listed in `FAILED_RUN_MANIFEST.csv` with its digest; no two run outputs of one chapter have the same digest (no run overwrote another) | as stated | yes |
| T2 | accounting. Every failed run is named by a "Record of run K" section of its chapter's pre-registration; the chapters with a failed run and no record are listed (criterion: none) | as stated | yes |
| T3 | the run of record. The last run output of at least 98 per cent of the 62 chapters with an instrument says "ALL CRITERIA MET"; the exceptions are listed | as stated | yes |
| T4 | causes. At least 90 per cent of the records carry at least one class; the number of records and the counts per class are reported; the counts of instrument defects and registration errors together exceed the count of records classified only as "registered statement rejected" (most recorded failures were of the method, not of the object) | as stated | yes |

Reported, not criteria: per-class counts; the chapters with the most failed runs; the list of rejected statements.

## Single-pass rule

Every case above is computed in one run with the criteria fixed here. A criterion that needs retuning after the run is itself the finding and is recorded as such. Failed runs are kept with their run number.

## Record of run 1; findings on the corpus, two instrument defects and one registered statement rejected (2026-11-10)

Run 1 (`ch63_run1_output.txt`): V1 and three T1 criteria (at least 110 outputs: 115; at least 40 failed runs: 45; the manifest) were met. Four criteria failed. (1) **T1, no two outputs of a chapter share a digest: rejected as registered.** Chapter 59 run 2 is a repeat of run 1 after a comment-only edit of the instrument and is byte-identical by design (stated in the chapter); the registration did not anticipate a deliberate repeat. The statement is kept and asserted in run 2. (2) **T2, an instrument defect.** The parser read only headings `## Record of run K`; Chapter 8 records its run 2 in an italic paragraph (`*Record of run 2 ...*`) inside the run-1 section, so the run was reported unrecorded although a record exists. The parser is repaired to accept the phrase "Record of run K" (or "runs") anywhere. (3) **T3, an instrument defect and a finding.** Chapters 3, 4 and other early chapters predate `tb_common` and end with "SUMMARY: all pre-registered criteria met" or "SUMMARY: one or more pre-registered criteria were not met"; the detector knew only the later format. Run 1 flagged Chapter 4 (its last run, run 2, ends with the earlier format's success line) and Chapter 63 itself (this run, which was failing). The detector is repaired to accept the earlier format for both success and failure; the earlier-format failures (such as Chapter 4 run 1) were then not counted among the failed runs, and are counted after the repair. (4) **T4, 6 of 47 records unclassified ($87$ per cent against the registered $90$).** The classifier's keywords missed the wording of some early records; the unclassified headings are printed in run 2. The criterion is not changed. Findings of run 1 that stand: 115 run outputs; every failed run listed with its digest; the gap that Chapter 4 run 1 (failed, T5: closed form against direct summation, $2.63\times10^{-12}$, from cancellation in the closed form) has no record in `ch04_PRE_REGISTRATION.md`; a dated amendment adding that record from the captured outputs of runs 1 and 2 is made before run 2, and is marked as an amendment. Run 2 is the run of record.

## Record of run 2; the classifier's vocabulary (2026-11-10)

Run 2 (`ch63_run2_output.txt`): after the repairs of run 1 the preservation and accounting criteria were met (116 outputs, 47 failed runs, none unrecorded after the Chapter 4 amendment and the inline-record parser; the duplicate digest of Chapter 59 asserted as a rejection; the earlier output format accepted). One criterion failed: 7 of 51 records ($13.7$ per cent) were unclassified, against the registered limit of $10$ per cent. Cause: an instrument defect in the classifier, whose keywords were written before the corpus was read and do not include the wording of the early records. The unclassified records (Chapters 3, 5, 6, 8, 14, 19 and 61) describe, in their own words: an instrument limit (Ch. 3, uniform panels too wide), an instrument fault in the output path (Ch. 5, encoding), an instrument-validation fault (Ch. 6, test code against the registered statement), an instrument limit by integer overflow (Ch. 8), a derivation slip in the registered end value (Ch. 14), a misspecified repair (Ch. 19) and an analytic slip in a post-run clause (Ch. 61). The classifier is repaired by adding those phrases ("instrument limit", "instrument fault", "validation fault", "overflow", "misspecif", "derivation slip", "analytic slip", "correction of the"); the registered limit of $10$ per cent is not moved. The last run of the chapter (run 2) is failing, so the chapter-63 exception in T3 is the run itself; run 3 is the run of record.

## Build line

`bash Textbook/tools/py_run.sh ch63_failed_models_and_supersession`
