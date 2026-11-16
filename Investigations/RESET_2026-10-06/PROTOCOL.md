# Blank-slate renewal — protocol (2026-10-06)

Binding: `GATEWAY_BEHAVIOURAL.md`, `GATEWAY_PROCEDURAL.md`, `CLAUDE.md`. Direct execution only. Nothing in `Engine/`, `Laws/`, `Release/` is edited. Nothing is deleted; nothing is moved without item-by-item approval. Nothing is committed unless asked. Supersedes step 3 of `REOPEN_2026-10-05/PROTOCOL.md`.

## Basis
The old investigation records are archived in full (`ARCHIVE_PRE_RESET_2026-10-06/Investigations/`, 4,623 files, copy verified by count). The working folders still hold them; blindness is by procedure: no old finding is read before the pre-registration of the investigation that concerns it.

## Inputs permitted per investigation
`PROMPT.md` of that folder (the specification; claims inside it are hypotheses under test, never evidence) · `Theory/` · `laws.hpp` and the other headers · `derivelist/` · `Datasets/` and the data a prompt names · `REOPEN_2026-10-05/graph_v2*` (structure: which investigation supplies which) · the new records written under this protocol.

## Inputs not permitted before the pre-registration
Old `INVESTIGATION.md`, `*ASSESSMENT*`, `*VERDICT*`, results and output files, old tool output, `R2_REOPEN_2026-10-05.md` drafts, `REOPEN_2026-10-05/STATUS.md`, `LEDGER.csv`, `LAYER_0_FOUNDATIONS_SYNTHESIS.md`. Old tool source is not reused; the instrument is written afresh from the prompt and the engine.

## Order
`graph_v2.json` layers. Layer 0 (145 investigations with no supplier among the investigations) by reach (number of investigations below), then layer 1, and so on; a cyclic group is run as one unit after its edges are classed `required` or `cross-check`. Supplier outcome decides the consumer's premise: an open supplier makes the consumer open or conditional, never excluded.

## Per investigation
1. Read the PROMPT and the canon it names. Write the dependency map (suppliers, dependents) from the graph and from the prompt's Upstream/Downstream lines.
2. Write the hypothesis, the observable, the data with provenance, the parameter ledger (derived, measured-input, calibrated), the controls.
3. Pre-register: instrument validations on known answers, thresholds, rejection criteria with their outcome class populated, look-elsewhere counts for any selection, the gradated outputs G0–G5 (as `REOPEN_2026-10-05/PROTOCOL.md` §5) and what is started on each.
4. Write the instrument; validate on known answers; run once over the whole range; record.
5. A misstep found in the instrument, the premise or the record is noted in place (dated, old text kept), corrected, and the investigation is re-run; every run is kept and numbered.
6. The old record is opened only in an end-of-programme comparison pass (amended 2026-10-06 from "after step 4": a comparison made mid-sequence would carry archived findings into later pre-registrations). Each record's section "Comparison with the archived record" says "deferred" until then; differences are classed (instrument fault in either / premise / data / convention), and a downgrade carries the contaminating-input line (procedural §3.8).

## Files
In each folder: `<ID>_RESET_ASSESSMENT_2026-10-06.md` (record), `<ID>_reset_<n>.cpp` (instrument), `<ID>_reset_<n>_results.txt` (output capture). Here: `PROTOCOL.md`, `STATUS.md` (done list, resume point), `LEDGER.csv`, `EDGES_LOG.csv`.

## Status of the ten earlier drafts
PPT01, FLM01, FLM02, FLM05, FLM06, FLM07, FLM08, FLM15-inf, PPT05, PPT06 were produced by reading the old record first. Their computed numbers come from validated tools on engine constants and are carried as supplier outcomes (with errata where recorded); their pre-registrations were not blind. They are re-run blind in a fresh session.
