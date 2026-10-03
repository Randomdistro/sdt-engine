# Outstanding Investigations — campaign plan and instance prompt

> Drawn up 2026-10-03 from a direct read of the folder tree, `INVESTIGATION_STACK.md`,
> `ADJUDICATION_REGISTER.md`, `REOPENED_FAILURES_2026-07-26.md`, `FAILURE_RECOVERY_2026-07-02.md`,
> `PROMPT_EXECUTION_PROTOCOL.md`, `HUNTER_PROTOCOL.md`, both gateways, and `Theory/03_Open_Problems.md`.
> Repository HEAD at drafting: `90560ee` (2026-09-20, "l_p derived, finally and again").
> Author of record: J. C. Harvey, Melbourne.

---

## Part 1 · How many are outstanding

Method: 264 investigation folders under `Investigations/01_*`–`17_*`, classified by what is on disk
(PROMPT / code / assessment-type file), cross-checked against the aggregate direct-rerun files and the
two registers. `INVESTIGATION_STACK.md` status tags are current only to ~2026-07-04 and cover 47 of 264
folders, so they were not used as the count.

- **Group A — no executed, assessed result: 48**
  - 6 folders with no PROMPT, no code, no assessment: FLM04 (a superseded fork; stack §3 says archive), NP04, NP16, NP29, CR02, CR07
  - 23 with a PROMPT only: FLM15 (Casimir), PPT12, PPT13, PPT14, PPT15, PPT16, APS08, APS09, APS10, NP06, NP07, NP11, NP31, GOM19, GOM21, GOM24, CR09, SAR07, SAR08, QM08, OP08, CH08, CH09
  - 19 with code and/or partial results but no assessment: FLM02, FLM05, FLM08, PPT02, PPT05, PPT06, PPT07, NP01, NP02, NP15, NP26, NP33, GOM41, CR01, GD01, GD02, GD05, GD07, QM01
  - (33 folders had code without an assessment file; GOM01–GOM14, 14 folders, are covered by `DIRECT_RERUN_GOM_2026-07-24.md` and excluded here)
- **Group B — assessed, but the register orders a direct re-adjudication or re-run: 12**
  - NP09, NP10, NP21, NP22 (agent-run, unclassified or genuine partial)
  - CR06, SAR03 (root-relocated, owes the Law-II release-rate law), SAR04, OP07, CH01, GOM09
  - GOM16 (provenance confirmation only), QM05 (verdict file needs the R2 outcome appended)
- **Group C — reopened re-poses and unexecuted winnables with a written diagnosis: 9**
  - R1 FD02 seat-hop viscosity · R2 TD05 re-pricing ledger · R3 TD04 speed-weighted relay flux
  - R4 Wiedemann–Franz with occupancy capped at 1 (unlocks metals) · R5 FD04 compounding-refusal refinement · R6 FD12 coherence-length selector
  - FD05 (D=3 isotropy → c/√3) · FD07 (ℓ=2 lift slope) · FD09 (sphere-geometry 6π)
- **Total: 69 work items.**
- **Not counted, stated so the number is not over-read:**
  - 163 assessed folders contain the words OPEN / DEFER / PENDING / PARTIAL in their assessment text. Most are open sub-questions inside a completed run. They were not read individually and are not in the 69.
  - The root debts below are enabling work; they are not in the 69 and are scheduled separately.
  - `Experiments/E01`–`E102`, `Hubble/`, `ATOMICUS/` and the `Release/` tools are outside `Investigations/` and outside this campaign.
- **Root debts the 69 depend on (Wave 0):**
  - FLM10 — influx/engagement profile ρ_eng(r), its handed/scalar split (~34×), coherence length. Phases 0–1 on disk; no assessment. Under D1, NP20, NP21, NP18.
  - FLM14 — rotating spation, sequential occupancy (rule-form ladder both failed the ≤1.2 isotropy gate). Under RESIDENCE-LAW, PPT08 seats, NP10 lock, FLM03, ε=hν.
  - FLM06 — scale closure. The 2026-09-20 commit changed `laws.hpp` and the l_P closure; every earlier assessment citing l_P or koppa–wake geometry is potentially stale.
  - HG-1 — handedness fixing of the Lenz minus (PM02). PPT09 — winding handedness (NP20 moment sign).
  - FLM11 → PPT11 neutrino residual clock (mass gap).

---

## Part 2 · The constraint that shapes the plan

`GATEWAY_PROCEDURAL.md` §3.5 and `GATEWAY_BEHAVIOURAL.md` §3.5: **delegated-agent output is not citable;
agent-written records carry no evidential weight; all investigation runs in the main session.**
`ADJUDICATION_REGISTER.md` voided 11 agent rulings on this basis.

Consequence for "whichever instances process them":

- An **instance** here means a **separate top-level session**, each running its own batch directly (compile, run, read output, write the assessment itself). Not a subagent spawned from another session.
- Subagents (Agent tool) may be used only for read-only look-ups whose output is re-read by the instance at source before use. Nothing a subagent writes is cited, committed as an assessment, or used as a back-up finding.
- Instances coordinate through files committed to the repo, not through messages whose content gets cited: the **Campaign Ledger** (Part 5).
- One batch per instance. Suggested 4–6 parallel instances, each owning a domain cluster (Part 6). Cross-cluster dependencies go through the ledger.

---

## Part 3 · The extended prompt (paste into each instance)

### 3.1 Role and conduct

- You are executing outstanding investigations in `sdt-engine`, the implementation of Spatial Displacement Theory. You run every tool yourself and read every output yourself.
- Register: **excluded / ruled out / falsified / withdrawn**; **pre-registered**; **shared-input (not independent)**; **assessment**, not verdict (new files `*_ASSESSMENT.md`); **open / outstanding**, not OWED; **prohibited input**, not contraband. PASS/FAIL are allowed in tool output only. Prose says consistent/inconsistent within the stated tolerance.
- Prohibited in prose, code, identifiers: charge / charged / charges / charging (write the mechanics: circulation direction, displacement/exclusion geometry, wake structure, pressure response). "Honest/honestly" as a modifier, "clearly", "obviously", "importantly", "comprehensive", "rigorous" as self-description. "Sample" as a verb.
- Certification label for a relation true by shared construction: **CONSTRUCTION** (not IDENTITY). A relation built from two independent measurement chains is never labelled CONSTRUCTION.
- Every reported number carries exactly one tag: MEASURED-INPUT · DERIVED · COMPUTED · CALIBRATED(n) · OBSERVED · PENDING.
- No validation-leading, no "would you like me to" closings, no ceremony when corrected. Fix the artifact and continue.
- Do not delete files. No `rm` in loops, no `git rm -r`. Move, do not delete; deletion needs item-by-item approval from Harvey.
- Canon (`Engine/include/sdt/`, `Laws/`) is **propose-and-wait**: no edit, including comments. Log a proposal in the ledger and continue.
- Scratch files, binaries, throwaway scripts live in the session scratchpad, never in the repo.

### 3.2 Read-in pack — be current before touching anything

Read in this order, in full, from source, at the HEAD you were given. Record HEAD sha in your first RUN_LOG entry.

- `CLAUDE.md`, `GATEWAY_BEHAVIOURAL.md`, `GATEWAY_PROCEDURAL.md`, `Investigations/TERMINOLOGY.md`
- `Theory/00_Ruleset.md` → `01_Closure_Derivations.md` → `02_Inputs_and_Derivations.md` → `03_Open_Problems.md` → `04_Notation.md` → `05_Provenance_and_Correspondence.md` → `06_Input_Elimination.md` → `07_Cyclic_Reiteration.md`; `Theory/CONDENSA_Spation_Lattice_Unification.md`
- `derivelist/README.md` and `derivelist/AUDIT_2026-07-30.md`: the current seat for each scale (c, ℏ, ℓ_P, α, m_e, m_p, k_B, T_CMB, e)
- `Engine/include/sdt/laws.hpp` in full, including namespaces `measured`, `law_I`–`law_VI`, `bridge`, `atomic`, `nuclear`, `coulomb_identity`. This is the single source; nothing is redefined locally.
- Canon delta check: `git log --since=2026-07-01 -- Engine Laws Theory derivelist Benchmarks` and `git show 90560ee --stat`. Read the diffs of `laws.hpp` and `Audits/KOPPA_WAKE_REPAIR_2026-09-08.md`. Establish what changed in l_P / koppa–wake closure and which assumptions earlier assessments made about it.
- `Investigations/INVESTIGATION_STACK.md` (§0 constraints, §3b cascade ledger) — treat status tags as dated, not current
- `Investigations/ADJUDICATION_REGISTER.md`, `REOPENED_FAILURES_2026-07-26.md`, `FAILURE_RECOVERY_2026-07-02.md`, `DIRECT_RERUN_*.md`, `RECONCILIATION_2026-07-23.md`, `FARMER_PASS_2026-07-03.md`, `KILL_REVIEW_2026-07-08.md`, `REPAIR_LEDGER.md`
- `PERFECT_PROMPT_TEMPLATE.md`, `PROMPT_EXECUTION_PROTOCOL.md` (§8 the seven questions), `HUNTER_PROTOCOL.md` (§0 the drop and the fishbowl, §H.LEASH, §K)
- Then, for each item you own: its `PROMPT.md`, `RUN_LOG.md`, tool source, every results file, and the cascade-ledger entries naming it.
- Prohibitions to hold throughout (`Theory/00_Ruleset.md`): no G, no M as fundamentals (g = v²/R, koppa = v²R/c²); no quantum wavefunctions, no fields as primitives, no dark matter/energy, no ΛCDM, no quarks/gluons, no wave-particle duality; no G_F as an input to an SDT chain. Rivals appear only as OBSERVED comparison columns.
- Nuclear grammar is constitutional: Z ≥ 2 → 1 alpha core + n_d deuterons + n_t tritons with n_t = A − 2Z, n_d = 3Z − A − 2 (electron-capture alternate: He-3 core, n_t = A − 2Z + 1, n_d = 3Z − A − 3). No free neutrons in stable nuclei. No other decomposition.
- Currency re-check: at every wave boundary and before every assessment is written, `git fetch` and diff canon paths against your recorded HEAD. If canon moved, list the items it touches in the ledger and re-run the affected ones.

### 3.3 Failure comprehension — read before the first run, apply on every negative

- Source-reading law: audit the canonical source, never a derivative or summary. Canon = the `.docx` Laws and the `Law_I_…/` subfolder `.md`. Three wrong-source failures (SAR01, Law I, Law II) are why this is a rule.
- The register mislabel to guard against (PM02): a word like "excluded" inside a *rival-branch elimination* is not the investigation's own assessment. Quote each item's own stated physics class, never a paraphrase.
- Known failure classes in this repository, check each negative against them:
  - Dilute-phase ledger applied to dense-phase physics (FD02, TD05, TD04).
  - A premise never carried across from another domain (R4: seat exclusivity not applied to conduction).
  - Localised/kinetic premise contradicting FLM12's ontology (mass = extended engagement, not ½mv²) — D1, NP20.
  - Atomic-scale premise where the spation scale applies (NP18 coherence).
  - Wrong selector: a growth contest where the object is a reach of smoothing (R6).
  - Transcription loss between a prompt and its tool (FARMER-flagged; SAR03, QM05, NP10, GOM13).
  - Prohibited-input gate: an exclusion criterion that enforces a rival's axiom rather than a measured anchor (e.g. "moment quench" presupposes intrinsic spin). Test every criterion for this before accepting a negative.
  - Instrument fault reported as a result. Instruments are validated on known answers first.
  - Fishing: scanning candidate rules until one lands in band (R5 rule (b), R6 candidate A: 12·4 = 48, 2·12·4 = 96). A hit found by scanning establishes nothing until derived forward.
  - Small-integer products near a target are cheap: H3 null found 452 gear-space hits for SAR03.
- On any negative, open, deferred or inconsistent result, answer the seven questions (`PROMPT_EXECUTION_PROTOCOL.md` §8) in the assessment, in this form:
  - Why did it fail (number, structure, or self-consistency — name the axis: INACCURATE / INCONSISTENT / INCONGRUENT)?
  - Is it recoverable?
  - What is unaccounted for?
  - Which premise is in error, and who introduced it (prompt, tool, canon, prior assessment)?
  - What freedom would a retry introduce, and is it justified natively?
  - Where is that justification recorded?
  - What cascade does it feed (name the root)?
- Grade the recovery: RECOVERED / PARTIAL / NO RECOVERY. Do not grade a recovery you reached by scanning.
- Trace to premise before closing, record what assumption produced the result, what would repay it, and where that is recorded (`GATEWAY_PROCEDURAL.md` §5).
- Leash (§H.LEASH): protect-the-refutation and overturn-when-pushed are both home-team biases. The cure is a named mechanism, not a swing. Report the tally (re-opens / recoveries / dead-or-shared-input) in each assessment.

### 3.4 Restructuring for retry

- A retry is a **new pre-registered phase** (`Pn′` with an `ADJ-###` entry), never an edit of the failed one. Both runs are kept in `RUN_LOG.md`.
- Before the retry tool exists, write: the corrected premise, the one freedom it adds and its native justification, the thresholds (numeric, unchanged unless the original threshold was itself shown to be prohibited-input or mis-transcribed — in which case say so and why), the rejection criterion and its populated rejection class, the output filenames.
- Thresholds are never widened after the number is seen (RETRO-PASS). A bracket that moved after a failed run must have its linear-response or validity bound pre-registered numerically (PM02 P4 is the recorded soft spot).
- Allowed pivot routes are those in the prompt's own pivot table. A new route not in the table is added to the PROMPT as a dated amendment before it is run.
- One retry per premise correction. A second failure on the same premise is a finding about the picture, not the pricing: record it as the cascade root and stop that branch.
- Whole-range single-pass comparison for any curve, family, or chart. A rule that needs retuning partway is itself the finding.
- Two-route verification for every load-bearing number (analytic vs numerical, direct vs fitted); the routes agree within stated tolerance before the number is quoted.
- Retries use **forward derivation**. If you find yourself scanning rules or constants for one that lands, stop; that is fishing.

### 3.5 Using one finding to back up another (the dependency rule)

This is where the campaign can go wrong, so it is stated precisely.

- An upstream result is usable as an input to a downstream item only if it is **established in an assessment written by a direct execution** and its label is DERIVED, COMPUTED, or OBSERVED. CALIBRATED(n) carries n into the downstream parameter ledger. OPEN, PENDING, shared-input (not independent) or a result carrying an unresolved cascade flag cannot back anything.
- The dependency is **pre-registered before the downstream tool runs**: name the upstream assessment (path + commit sha), the exact quantity used, its label, and the downstream threshold *as it stood before the upstream result was loaded*. Record it in the downstream RUN_LOG and the Campaign Ledger.
- A downstream result that rests on an upstream one is reported as **conditional on it**, with both parameter ledgers shown. If the upstream is later withdrawn, the downstream is automatically reopened (ledger rule).
- A shared closed form cannot discriminate between frameworks. Two items that both consume the same upstream quantity are **shared-input (not independent)** and must not be counted as separate confirmations.
- A framework's own derived laws are legal inputs to its own chains. A theory-derived decomposition is not data and never adjudicates.
- Alignment with a measured value never counts against a result; origin decides. Independent origin → convergent. Shared input → not independent.
- Do not rescue a failing item by choosing, from several available upstream findings, the one that makes it pass. Pre-register the choice and the reason from the mechanism before comparing. If more than one upstream finding is plausible, run the item once per candidate in one pre-registered pass and report all.

### 3.6 Per-item run protocol

1. Read the item's files (3.2). Check the canon delta for anything touching it.
2. Create or reset `RUN_LOG.md`. Copy the §⑩ Pre-Run Commitment Block from the PROMPT. Fill every `[COMMIT]` field (thresholds, forbidden inputs, output filenames) before any implementation.
3. If the item has no PROMPT: write one to `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ from the stack seed and the failure record, pre-registered, before any tool. If the item is a retired or superseded fork, record that decision for Harvey's approval; do not archive it yourself.
4. Do not read prior assessment or results files for tuning hints until Phase 0 baseline is pre-registered (prevents post-hoc calibration), except where the item is a re-adjudication, which starts by re-running the existing tool.
5. Validate every new instrument on a known answer before using it on the object.
6. Run phases per the loop: pre-register → implement → execute → compare → decide (PASS-GATE / PIVOT / EXCLUDE / OPEN / DEFER) → adjust. DEFER names the exact unblocking item by ID.
7. Standalone tools compile with `g++ -std=c++20 -IEngine/include tool.cpp -o tool`, include `<sdt/laws.hpp>`, read every constant from the engine, print labelled results. Synthetic inputs are labelled demo/toy in the output.
8. Re-adjudication items (Group B): read PROMPT + RUN_LOG + tool source; re-run; diff stdout against logged claims; audit each rejection criterion for prohibited-input; name the mechanism and the failed axis; outcome is REFUTATION-CONFIRMED / OVERTURNED→OPEN / OVERTURNED→ACCURATE.
9. Write `*_ASSESSMENT.md` with the dual assessment (prompt completion vs physics class), the parameter ledger, the seven questions for any non-positive result, the dependency block (3.5), the cascade root named, and the leash tally.
10. Update, in the same session: the category `README.md`, `INVESTIGATION_STACK.md` entry (dated), the Campaign Ledger row, and `Theory/03_Open_Problems.md` by dated entry if an item enters or leaves it. Regenerated reports are regenerated by their tool.
11. Commit per item (or per tightly related pair) with a message stating the result and its label. Push to the instance's designated branch.

### 3.7 Stop and escalate conditions

- Stop and write to the ledger, without proceeding, if: a result requires a canon edit; a prohibited input would be needed to proceed; two instances' results contradict; a threshold appears mis-transcribed or prohibited-input; or a result changes a Theory/Open_Problems statement.
- Report to Harvey in one line each: an unexpected positive (a hit that arrived without scanning), a canon proposal, a decision needing his approval (archive/delete/rename).

---

## Part 4 · The dynamic scheduler

The order is not fixed. It is recomputed from the ledger at each wave boundary.

- **Nodes** = the 69 items + Wave 0 roots. **Edges** = declared upstream dependencies (from the cascade ledger §3b, the item's own PROMPT, and `FAILURE_RECOVERY`). Edges are added to the ledger when an instance finds one; they are never inferred from a number coincidence.
- **Item states:** UNREAD → PRE-REGISTERED → RUNNING → ASSESSED(label) → CONDITIONAL(on X) → BLOCKED(on X) → REOPENED(by X) → ESCALATED.
- **Wave rule:** an item becomes runnable when every upstream it declares is ASSESSED with a usable label (3.5), or when it declares none. BLOCKED items are not run as a stub; they are queued with the unblocker named.
- **Re-prioritisation triggers** (after any assessment lands):
  - A root debt closes → unblock everything under it, rank those by number of dependants.
  - A usable upstream finding appears → scan the BLOCKED and failed items for edges to it; pre-register and retry those that declared the edge, in order of leverage.
  - An upstream is withdrawn or its label downgraded → every CONDITIONAL dependant becomes REOPENED.
  - Canon changes (git diff on canon paths) → re-queue everything whose assessment cites the changed quantity.
  - Two items converge on one root → log the root once, group the debts under it.
- **Leverage ranking** within a wave: (number of declared dependants) × (existing instrument readiness) ÷ (cost). Ties go to the item with a populated rejection class and an on-disk instrument.
- **Retry budget:** one retry per corrected premise; a second failure on the same premise stops the branch and records the root.
- **Cross-instance contradictions** are escalated, not resolved by the later instance overwriting the earlier.

---

## Part 5 · Campaign Ledger (`Investigations/CAMPAIGN_LEDGER.md`, created by the first instance)

One row per item. Columns: ID · cluster · instance · state · label · HEAD sha at run · upstream consumed (assessment path + sha + quantity + label) · downstream dependants · root debt named · retry count · date. Append-only; corrections recorded in place, dated, never silently overwritten.

Also kept in the ledger: the canon-proposal list (for Harvey), the decisions-awaiting-approval list, and a roots table (root → items under it → status).

---

## Part 6 · Waves and clusters

### Wave 0 — roots and instruments (one instance, sequenced first; others may start items with no declared dependency)

- Canon-delta audit of 2026-09-20 `laws.hpp`/l_P/koppa–wake change against every assessment citing it. Output: list of stale items.
- FLM10 phases 0–1 assessed, then the isotropy residual instrument (finite-N CRN → elastic tensor → Zener anisotropy decay) — the one earned root; acceptance test is ρ_eng(r), the ~34× handed/scalar split, the coherence length.
- FLM14 solver state (bond-local gearing + structured seat-tour); both rule forms failed ≤1.2 isotropy gate: assess before anything cites FLM14.
- FLM06 assessment under the current canon; FLM08 assessment (27/27 on disk, no assessment file).
- HG-1 (Lenz handedness) and PPT09 (winding handedness).

### Cluster A — foundations, particle, atomic (Instance 1)
- FLM02, FLM05, FLM15 (Casimir as relay exclusion; PROMPT only), FLM04 (fork decision for Harvey)
- PPT02, PPT05, PPT06, PPT07 · PPT12 (lepton moments), PPT13 (pion), PPT14 (heavy resonances), PPT15 (CP), PPT16 (muon lifetime budget)
- APS08 (Zeeman), APS09 (Stark), APS10 (first ionisation from pressure)

### Cluster B — nuclear (Instance 2; heaviest)
- Execute: NP01, NP02, NP04, NP06, NP07, NP11, NP15, NP16, NP26, NP29, NP31, NP33
- Re-adjudicate: NP09, NP10, NP21, NP22 (NP21 and NP22 both name FLM10/FLM14 roots — hold until Wave 0)
- Carry-over from the register: NP12 canon fix is Harvey's (propose-and-wait); the `R_p·(A/η)^⅓` successor is ready.

### Cluster C — gravitation and cosmology (Instance 3)
- Execute: GOM19, GOM21, GOM24, GOM41 · CR01, CR02, CR07, CR09
- Re-adjudicate: CR06, GOM09; provenance check GOM16
- Open: Cassini raw shared-om integral (OM02, partial fetch); GW radiation coefficient without GR (GW01)

### Cluster D — galactic and stellar (Instance 4)
- Execute: GD01, GD02, GD05 (crossover; Wave 0 root), GD07 · SAR07, SAR08
- Re-adjudicate: SAR03 (owes the Law-II release-rate law fitting the corona lead and p_align together), SAR04

### Cluster E — fluid, thermo, condensed, quantum, plasma, optics, chemistry (Instance 5)
- Execute the written re-poses: R1 FD02, R2 TD05, R3 TD04, R4 Wiedemann–Franz (largest payoff: unlocks metals), R5 FD04 refinement (compounding refusal, own pre-registration), R6 FD12 (mechanism first; look-elsewhere guard on 48 and 96)
- Execute the unexecuted winnables: FD05, FD07, FD09, each with its own pre-registration block
- QM01, QM08 · QM05 file update · OP08 · OP07 re-adjudication · CH01 re-adjudication, CH08, CH09
- Note: the 2026-07-04 order stopped batch 2 (CM/PM/OP/CH + remaining QM) except QM05. Confirm with Harvey that the stop is lifted before running those; the lifting is not recorded in the files read.

### Cross-cluster dependencies already known (seed the ledger with these)
- D1, NP20 (mass), NP21, NP18 → FLM10 influx profile.
- NP21 iron-floor ratio (~32×) ≈ D1 handed/scalar (~34×): testable, unproven; a pre-registered forward derivation, not a match.
- NP20 moment sign → PPT09 winding handedness.
- PPT11 ↔ FLM11 → mass gap as residual clock; number still owed.
- FLM09-A2 isotropy residual, GD05 crossover, R1 occlusion transfer, FLM03 co-rotation → lattice solver.
- NP22 beta spectrum → native 3D exit-channel count N_exit ∝ E² → FLM14 and PPT10/PPT11 budget-speed→E_ν map.
- R4 (metals) → TD04-Cu, Lorenz constancy, degenerate-carrier corners of FD/PM.

---

## Part 7 · What each instance hands back

- Assessments (`*_ASSESSMENT.md`) citing only direct executions and `laws.hpp`.
- Updated RUN_LOG, tool source, captured output, per item.
- Campaign Ledger rows; roots table; canon-proposal list; approvals-needed list.
- A one-paragraph wave summary: what closed, what reopened, which upstream findings were used and which downstream items they changed, which roots remain.
