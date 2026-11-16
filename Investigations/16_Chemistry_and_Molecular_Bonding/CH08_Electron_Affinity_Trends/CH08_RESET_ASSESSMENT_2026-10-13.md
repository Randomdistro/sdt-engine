# CH08 (electron-affinity trends from void geometry) — blank-slate assessment, one pass (2026-10-13)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Registration and outcome in one record: no instrument was built.

## 0. Inputs read
`CH08/PROMPT.md` in full (a specification seed: target, SDT footing, pre-registration skeleton, benchmark linkage, the 2026-10-05 correction: gate the sign at ≥ 95% against a null and add a magnitude gate). The repository holds no electron-affinity table (`Datasets/nuclear/` has ionisation energies only) and no native rule for "void-completion pricing".

## 1. Analysis
| # | Class | Observation |
|---|---|---|
| D1 | no native model | The footing ("affinity is the mirror of ionisation (APS10): the price a nearly-complete void structure pays or collects") names a quantity but gives no rule that can be evaluated before a measured value is loaded. The standing rule (native mechanism first, fixed before any measured value is loaded) means the instrument cannot be built by choosing a rule against the table. |
| D2 | data | The anchor (a measured EA table for Z = 1–36) is not local; no fetch was made, because a table cannot be used without the rule of D1 fixed first. |
| D3 | gate | The corrected gate (sign ≥ 95% against a random or period-trend null, plus a magnitude gate) is evaluable only with D1 and D2; the null baseline (what a period-trend rule scores) is a property of the table and is not computed here. |
No downgrade is made on agreement grounds.

## 2. Outcome
**PENDING_SPEC** (the model) and **PENDING_DATA** (the table). Nothing was run. What is owed: a native statement of the pricing rule (the quantity, its units, how a seat count enters), registered before the table is fetched; then the table with its source and hash; then the sign test against the period-trend null and the magnitude gate.
