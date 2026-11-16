# Dependency flow across the investigation structure (2026-10-05)

Scope: how many outputs become inputs, which failures rest on an upstream that failed first, and which of the 2026-10-05 corrections change a downstream outcome. Sources: `dependency_edges.csv/.json` (keyword extraction from PROMPT/VERDICT/ASSESSMENT text, correction blocks stripped), `dependency_flow.csv/.json` (outcome classifier), and the author's own cascade ledger (`INVESTIGATION_STACK.md` §3b). Counts from the extraction are approximate (keyword rule; outcome classifier is also keyword-based and mislabels some nodes, e.g. GD05 reads "passed" although its recorded real-SPARC RMS is 66%). The cascade-ledger reading below is by hand.

## 1. Outputs that become inputs (extraction)

| Quantity | Value |
|---|---|
| Investigation ids | 207 |
| Explicit dependency edges (A's output used by B) | 398 |
| Ids whose output feeds another | 132 |
| Ids that consume another's output | 153 |
| Isolated in the explicit graph | 37 |
| Additional mention-only links | 564 |
| Largest suppliers | FLM10 (35 consumers), PPT06 (15), FD02 (13), APS04 (11), FD05 (11) |
| Edges whose supplier is on the errored list | 237 of 398 |

Consumers of errored suppliers by recorded outcome: passed 96, open 74, failed 50, unrun 17. Failed or open consumers resting on at least one errored supplier: 68; of those, 36 have every stated supplier on the errored list. Passed consumers resting on an errored supplier: 48 (their footing is weaker than their label until the supplier is re-read). Transitive reach is not reported: the extraction is over-inclusive and cyclic, so it would overstate.

## 2. How failures actually chain

The stack does not chain folder to folder. It chains through about 30 named shared roots (§3b), each logged once with member folders: R1 OCCLUSION-MECHANISM, R2 INPUT-PRECISION, TD-ROOT-1/3, FD-ROOT-2, NP17 lock, ROOT-A, ROOT-B, HG-1, WEOS-1, PM03-REBUILD, ROOT-RIM, ROOT-BUDGET, OP-ROOT, OP01-MATTER-INDEX, WAKE-DISPERSION, NP22 exit-channel count, WELL-DEPTH, RESIDENCE-LAW and others. Folder-to-folder failure chains that do exist: OP01 -> OP07 (matter index), PM03 -> PM06 and PM07 (wave solver), HG-1 -> PM01-P3, PM02, PM04, PM05, PM06, PM07, NP32 -> NP35 -> NP36, NP24 -> GOM19, GD03 and GD04 -> R1.

## 3. What the corrections changed downstream

| Correction | Direction | Downstream effect |
|---|---|---|
| GD06 / OP01: solar-limb profile n = (1-z)^-2 (c_far = c(1-z)^2, GOM22 repair) | upgrade | OP01's solar-limb sanity row failed (-49.95%) only because its prompt carried the p = 1 profile; with the repaired profile it passes (+0.10%). GD06's PASS stands. OP01 becomes PARTIAL (matter-index phase OPEN). **The one clean case of a dependency-caused failure that now survives.** OP07 is not rescued by this, but my first reading was wrong: its kill is computed with the measured-medium matter term, and its rescue route is OP01 phase B, which is OPEN. An open upstream cannot close a downstream, so OP07's "NO RECOVERY" is not licensed; restated as excluded-as-modelled (measured-medium term), native version OPEN on OP01 phase B (correction block appended to OP07_VERDICT.md). The same pattern is in GD03 and GD04 (NO RECOVERY, root OCCLUSION-MECHANISM unbuilt): their as-built forms fail their own gates, but the question is open on the root. OP02, OP04, OP05 rest on OP-ROOT, unchanged. |
| PM03: evolved relay pulse replaces closed form | partial | Satisfies "evolving, no plugged closed form" for a 1-D relay (speed/c within 2.3e-4, Courant limit shown). PM03-REBUILD asked for an EM-wave solver: dispersion and transverse/longitudinal separation not run, so PM06's absolute synchrotron coefficient and PM07's dispersion sector stay blocked. Not a survival yet. |
| PM04 ensemble | downgrade | Single-run P2 PASS/FAIL withdrawn as evidence; HG-1 (imported alpha-hbar-c gain) confirmed as the premise. PM05 and PM06 stay failed/open on HG-1 and ROOT-SIM. |
| GD03, GD04 re-run | downgrade | Old PASS banners contradicted the tools' own gates. R1 stays unpaid; GD05 stand-in footing unchanged (real-SPARC RMS 66%). |
| GD01, PPT09, FD11, PPT06 grading withdrawn | downgrade | Consumers keep their numbers but lose a "resolved" supplier label: GD05; EMC02 and PPT10; FD03, FD07, FD09 (verify, outcome label unverified); PPT06's 15 consumers (CH01, NP20, CM01, CM03, FD06, FD07, FD10, PM01, PM02, QM07 and others) now rest on "results on file, not re-graded". |
| NP35 re-score | none | G3/G4 corrected, outcomes unchanged; NP36 fails on its own seating construction. |
| Path / data fixes (APS03 SPARC path, CR08 BOSS table, GOM09 PREM, NP39, NP07, CR05, CH02, NSEQ15) | unblocks a run | Nothing re-scored. APS03's repointed path is the ledger's "APS03-DATA-PATH" standing root: the cross-scale collapse test is runnable again. CR08 and GOM09 runs owed. |

## 4. Answer in numbers

- Corrections that changed an upstream outcome in a direction that could rescue a downstream failure: 2 (GD06/OP01 profile; PM03 evolved pulse).
- Downstream failures that now survive because of them: 1 clean (OP01 solar-limb row), 0 of the roots paid.
- Downstream items now runnable but not yet scored: APS03 collapse test, CR08 with BOSS DR12, GOM09 with PREM.
- Downgrades propagate further than upgrades: eight corrections lowered an upstream label; their consumers (about 25 ids, extraction-approximate) rest on weaker footing than their labels say.

Open: a second read of each edge's text (not keyword) for the 68 failed or open consumers would give exact counts; not done.
