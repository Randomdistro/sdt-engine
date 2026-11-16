# Reopen of all investigations — protocol (opened 2026-10-05)

Binding: `GATEWAY_BEHAVIOURAL.md`, `GATEWAY_PROCEDURAL.md`, `CLAUDE.md`. Direct execution only (no delegated agents). Nothing in `Engine/`, `Laws/`, `Release/` is edited. Nothing is deleted. Nothing is committed unless asked. Earlier prompts, tools and outputs stay in place; the reopen adds files beside them.

## Order of work

1. **Graph.** `AUDIT_ALL_INVESTIGATIONS_2026-10-05/declared_dag.csv` (declared edges from each prompt's Upstream/Downstream lines and the stack file) is the starting graph. Reading each prompt adds, corrects or removes edges; edits are recorded in `EDGES_LOG.csv` here, and layers are recomputed after every layer.
2. **Layers.** Layer 0 = investigations with no supplier among the investigations. Within a layer, order by number of investigations below (reach). A cyclic group is run as one unit after its edges are classed `required` or `cross-check`; only `required` edges order the run.
3. **Per investigation, in this order:** read prompt, assessment, tool header and outputs in full; write the R2 record; pre-register (dated, before the tool runs); validate the instrument on known answers; run once over the whole range; record; update the ledger; state the direction for the next layer.
4. **Per layer:** `LAYER_<k>_SYNTHESIS.md` records what the layer's outcomes change for the next layer's premises, before that layer's R2 records are written. Supplier outcome decides the consumer's premise, not the supplier's label: an open supplier makes the consumer open or conditional, never excluded; an excluded supplier excludes only what is computed from it.

## The R2 record (`R2_REOPEN_2026-10-05.md` in each folder)

0. **Header.** Id, recorded status before reopen, audit class and correction status from 2026-10-05, layer.
1. **Prompt analysis.** The premise, the question, the instrument, the registered gates; each defect classed (premise / construction / gating / data / record) with the file and line it was found at. A defect that downgrades a result carries the contaminating-input line required by procedural §3.8, or it is void.
2. **Dependencies.** Suppliers (what quantity is taken, from which file, with the supplier's outcome) and dependents (what quantity is consumed, by whom, at which line). Edges classed `required` or `cross-check`.
3. **Upgraded question.** A measurable gap, the observable, the data with provenance, parameter ledger (what is derived, measured-input, calibrated), controls.
4. **Pre-registration.** Instrument validations on known answers; thresholds; the rejection criteria and the outcome class each one populates; the look-elsewhere count for any selection.
5. **Gradated outputs and triggers.** One ladder per investigation, thresholds numeric:

   | Grade | Meaning | Trigger |
   |---|---|---|
   | G0 | instrument not validated | fix the instrument; the object is not assessed |
   | G1 | excluded (pre-registered rejection criterion met on the pre-registered form) | name the premise that produced it; open the alternative routes below |
   | G2 | open (computed, between the criteria, or conditional on an unbuilt supplier) | name the supplier or datum that decides it |
   | G3 | consistent within tolerance, shared-input (named contaminating input) | derive the input, or find the independent measurement |
   | G4 | consistent within tolerance, independent origin (convergent) | state discrimination separately; look for the observable where the frameworks differ |
   | G5 | discriminating (a measured quantity separates SDT from the comparator) | pre-register the experiment |

   Each record states what lands in each grade and what is started on each trigger.
6. **Alternative outs.** Other routes registered in advance, each with its own rejection criterion, to be used only on a G1 or G2 of the main route.
7. **Run record.** Date, tool, command, output file, validation results, the single-pass comparison.
8. **Outcome and direction.** Grade reached, what it changes for each dependent, what theory the outcome directs next.

## Register

Professional vocabulary (assessment, pre-registered, excluded, ruled out, falsified, withdrawn, open, shared-input, construction). No "honest" as a modifier. No charge-words in SDT prose. No G, GM or M as fundamentals; mass is a baryon count N_b = M/m_p converted at entry. Every number carries one tag: MEASURED-INPUT, DERIVED, COMPUTED, CALIBRATED(n), OBSERVED, PENDING. Every selection among alternatives records its look-elsewhere count.

## Files here

- `PROTOCOL.md` (this file)
- `LEDGER.csv` — one row per investigation: id, layer, prior status, grade, key numbers, supplier-status used, feeds
- `EDGES_LOG.csv` — dependency edges added, changed or removed, with the file and line that justify each
- `LAYER_<k>_SYNTHESIS.md` — per layer
