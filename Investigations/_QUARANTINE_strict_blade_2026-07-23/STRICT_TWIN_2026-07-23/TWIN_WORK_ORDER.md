# TWIN WORK ORDER — independent strict re-audit of the kill docket
### For a cold instance. Everything you need is named here; nothing else is assumed.
*Issued 2026-07-23 · dual-front campaign, strict side.*

## 0. Mission

You are the **strict twin**: an independent Method A re-audit of 18 killed/failed SDT claims.
A second front (Method B, recovery) is processing the **same docket** in parallel with a different
methodology. You must not see its outputs (§3). At the end, your verdicts and its verdicts are
compared item-by-item by a reconciliation Adjudicator; **disagreements are the payload** — they
mark exactly where a kill was either solid or a purist artifact.

**Your rulings are ADVISORY.** No label, verdict file, register, or status anywhere in the repo
moves on your say. You write only inside `Investigations/STRICT_TWIN_2026-07-23/` (§5).

**Run everything yourself, directly — no subagent/delegate execution of any audit step.** In this
repo, agent-executed verdicts are a voided class (a 2026-07-12 ruling voided every auto-agent kill
for confabulation risk). A twin verdict produced by delegation would be void on arrival.

## 1. Protocol

Your sole protocol is **`Investigations/METHOD_A_STRICT_FALSIFIER.md`**. Read it first, in full.
Run the complete three-front cycle on every docket item:

- **Front 1** — restate the killed claim's mechanism, prediction, and inputs from its primary sources.
- **Front 2** — audit BOTH the original claim AND the original kill with the §A kill-list, §B
  contamination rule, §C independence test, §G mirror. Where a tool exists in the item's folder,
  **re-run it** and diff its output against the logged claims — do not trust logged numbers.
- **Front 3** — adjudicate the kill yourself (§H six phases): ruling ∈ {KILL CONFIRMED · KILL
  RESCOPED · KILL FALSE, route lives · BOTH FAULTY}, with the named mechanism (§H.LEASH: no ruling
  without one, in either direction).

Because you may not open the register (§3), its four re-adjudication rules are restated here and
bind you: **(1) READ THE SOURCE** — PROMPT.md, RUN_LOG.md, tool source, results files; never
summaries. **(2) RE-RUN** — compile/execute tools directly where present; diff stdout against
logged claims. **(3) GATE AUDIT** — check every kill condition for GATE-CONTRABAND (a gate
enforcing a rival's axiom rather than a measured anchor is itself killed). **(4) MECHANISM** — no
ruling without naming the mechanism in the framework's own terms.

## 2. The docket

**`Investigations/KILL_DOCKET_2026-07-23.md`** — process the 18 active rows in three batches,
in order: **Batch 1** D01–D06 · **Batch 2** D07–D13 · **Batch 3** D14–D18. Sessions may split at
batch boundaries. The docket's one-line summaries are indexing aids only — rule on the primary
sources in each row. §X1 items are permanently excluded (do not audit, recover, or cite); §X2/§X3
are out of scope for you.

## 3. Blinding — read WHITELIST, everything else is closed

You share a repo with the other front, so blinding is by discipline, not by wall. You may read ONLY:

1. This work order and everything in `Investigations/STRICT_TWIN_2026-07-23/`.
2. `Investigations/METHOD_A_STRICT_FALSIFIER.md`.
3. `Investigations/KILL_DOCKET_2026-07-23.md` (all sections).
4. **Each docket item's own investigation/experiment folders** (the primary-sources column) —
   every file inside them.
5. `Datasets/` + `Datasets/MANIFEST.md` — verify a file's sha256(12) against its manifest row
   before using it (OneDrive stale-file hazard is real here).
6. `Engine/include/sdt/` and `Laws/` — READ-ONLY, for mechanism reference. Never edit them.

**Explicitly FORBIDDEN (the other front's material and this campaign's rulings):**
`METHOD_B_RECOVERY_REINVESTIGATION.md` · any `METHOD_B_RUN_*.md` ·
`KILL_READJUDICATION_REGISTER.md` · `RECONCILIATION_2026-07-23.md` ·
`Experiments/CAMPAIGN_AGAINST_THE_STANDARD_MODEL.md` (its firing log rules on D05/D06) ·
`INVESTIGATION_STACK.md` · `KILL_REVIEW_2026-07-08.md` · the `HUNTER_SCOUR_*` / `HUNTER_REPAIR_*`
directories · session distillation / repair-ledger / canon-flag files. If a search or listing
surfaces one of these, do not open it.

**Honest-blinding doctrine.** Item folders have accreted post-kill annotations; you will
occasionally see things you shouldn't. The discipline: **rule on primary evidence only**, and
declare every exposure. Any re-adjudication/recovery/status content you encounter inside
whitelisted files gets a row in `TWIN_CONTAMINATION_LEDGER.md`: *(file · what was seen, one line ·
could it steer your ruling? y/n)* — then proceed on primary evidence. An empty ledger on a shared
repo is a red flag, not a badge; a long honest ledger with clean rulings is the good outcome.

## 4. Per-item verdict file — `TWIN_VERDICT_<ID>.md`

One file per docket ID, this structure:

1. **Sources read** — every primary file opened (path list); any listed source missing → say so.
2. **Re-execution** — what you re-ran (tool, command), and the diff between its output and the
   logged claims. If nothing was re-runnable, state why.
3. **§A audit of the ORIGINAL KILL** — each kill-list mode checked, incl. GATE-CONTRABAND on
   every kill gate.
4. **§H adjudication** — the six phases, brief but explicit; then the four-way ruling **with the
   named mechanism** (of death if the kill stands; of the kill's error if it doesn't).
5. **Method A verdict line** (protocol format).
6. **Contamination** — y/n; if y, the ledger row reference.

## 5. Environment & boundaries

- Windows 11, PowerShell 5.1 primary. C++ tools compile with
  `cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:tool.exe path\to\tool.cpp` (or g++ equivalent).
- **Write ONLY inside `Investigations/STRICT_TWIN_2026-07-23/`**: per-item verdicts,
  `TWIN_CONTAMINATION_LEDGER.md`, and a final `TWIN_SUMMARY.md` (one row per ID: ruling +
  one-line mechanism + batch stats). Everything else in the repo is read-only to you; canon
  (`Engine/include/sdt/`, `Laws/`) is read-only to everyone.
- No commits, no pushes, no file deletion, no re-fetching data the `Datasets/` cache already
  holds (cite the cache; hash-check first).
- If an item is genuinely unauditable (missing sources, tool won't build), file the verdict as
  **UNADJUDICABLE** with the specific blocker — that is a finding, not a failure.

## 6. Done-condition

18 verdict files + summary + ledger, written to your directory, nothing else touched. Hand back
to Harvey. The reconciliation (not you, not the other front) merges the two columns.

*The creed applies: find the fault, trace it to the premise, run it to the root, correct it or
kill it clean, show your work. The number is never the prey — and neither is the overturn.*
