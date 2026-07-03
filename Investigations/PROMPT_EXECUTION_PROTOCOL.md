# Prompt Execution Protocol — Adaptive Runs

> **Author:** J. C. Harvey, Melbourne. **Applies to:** every investigation under `Investigations/`.
> **Principle:** *It is a bad plan that cannot be altered.* A prompt is a **committed hypothesis
> with explicit gates**, not a script that must succeed. When data contradict the plan, **adjust the
> method, not the target** — unless the target itself is falsified, in which case **kill or OPEN** it
> honestly.

Every `PROMPT.md` inherits this protocol via `PERFECT_PROMPT_TEMPLATE.md` §⑩. When you **run** a
prompt (human or agent), you follow this document in order.

---

## 0 · Before you write a single line of code

1. **Read** `Engine/include/sdt/laws.hpp` (and any namespace cited in the prompt).
2. **Create or reset** `RUN_LOG.md` in the investigation folder (append-only during the run).
3. **Copy the Pre-Run Commitment Block** from the prompt's §⑩ into `RUN_LOG.md` and fill every
   `[COMMIT]` field — numeric thresholds, forbidden inputs, output filenames — **before** implementation.
4. **Do not** read prior `*_VERDICT.md` or `results.txt` for tuning hints until Phase 0 baseline is
   committed (prevents post-hoc calibration).

---

## 1 · The run loop (repeat per phase)

```
FOR each Phase N in the prompt:
  1. PRE-COMMIT   — state prediction + pass/fail thresholds in RUN_LOG (already in §⑩ block)
  2. IMPLEMENT    — code/prose for Phase N only
  3. EXECUTE      — compile, run, capture stdout → results fragment
  4. COMPARE      — ACTUAL vs COMMITTED; compute relative error
  5. DECIDE       — one of: PASS-GATE | PIVOT | KILL | OPEN | DEFER
  6. ADJUST       — if PIVOT: document ADJ-### entry (see §3); re-run Phase N or fork N'
  7. GATE         — do not start Phase N+1 until PASS-GATE or explicit DEFER with OPEN flag
END FOR
```

**Gate rule:** A phase marked **DEFER** in the verdict must list exactly which later investigation
or dependency unblocks it. A phase marked **OPEN** must not be reported as PASS in the summary line.

---

## 2 · Decision vocabulary (mandatory labels)

| Decision | Meaning | Allowed next step |
|----------|---------|-------------------|
| **PASS-GATE** | All committed thresholds met for this phase | Proceed to Phase N+1 |
| **PIVOT** | Hypothesis mechanism failed; **alternative native route** in prompt's pivot table is engaged | Re-run same phase number or N′ (document ADJ-###) |
| **KILL** | Claim falsified; record in VERDICT and INVESTIGATION_STACK | Stop branch; do not rescue with fits |
| **OPEN** | No honest forward route yet | Ship partial results; no PASS on parent claim |
| **DEFER** | Blocked on upstream dependency (FLM10, EMC04, …) | Ship stub; cite blocker by ID |

**Forbidden decisions (instant audit fail):**
- **RETRO-PASS** — widening a committed tolerance after seeing the number
- **PLUG** — inserting a coefficient so a target matches (except one documented CALIBRATED(n) per prompt)
- **IDENTITY-PASS** — calling `engine_fn()` vs CODATA a mechanism win without Phase-1 native work
- **BORROW-SMUGGLE** — importing G, M, GM, ψ, ΛCDM, G_F into the SDT chain (rivals may appear as OBSERVED comparison columns only)

---

## 3 · Adjustment register (`RUN_LOG.md` format)

Every pivot or scope change gets an entry:

```markdown
### ADJ-003 — Phase 2 PIVOT (2026-06-27)

- **Trigger:** T2 FAIL — weak-field n=1/(1-z) gives n<0 for proton-scale z>1 (CR10 precedent).
- **Committed response (from prompt §⑩ pivot table):** switch to exponential closure n=exp(z) for z>0.5 regions only; keep 1/(1-z) for z<0.1.
- **What changed:** Phase 2 integral uses piecewise closure; solar limb still uses z=ϟ/r weak-field.
- **What did NOT change:** No G/M; no fitted n_water; 1.75″ target unchanged.
- **Re-run result:** [fill after execute]
```

**Allowed adjustments (examples):**
- Bracket / mesh / timestep refinement when numerics fail
- Alternative **native** formula listed in prompt §⑩ pivot table
- Phase split (2a simulation, 2b analytic limit) when compute budget exceeded
- Filename fix if prompt listed stale name (document in ADJ)

**Disallowed adjustments:**
- Any change to committed `% error` thresholds post-run
- Replacing a failed native mechanism with `atomic::` / `bridge::` wrapper only
- Adding CALIBRATED parameters not reserved in the prompt

---

## 4 · Dual verdict (required in every `*_VERDICT.md`)

Separate **whether the prompt was executed** from **what physics class resulted**:

| Axis | Grades | Question |
|------|--------|----------|
| **Prompt completion** | A / B / C / D / F | Did the tool do what §④–§⑥ asked, phase by phase? |
| **Physics class** | NATIVE / CONVERGENCE / DEGENERATE / LINGUISTIC-BORROW / KILLED / OPEN | Did SDT derive, tie, or fail vs rivals? |

Example (OP01 stub run): Prompt completion **F** (Phases 3–4 missing); Physics class **CONVERGENCE** on Snell identity only.

Both axes must appear in the verdict header.

---

## 5 · Parameter ledger (every `.cpp` print block)

Each printed number carries exactly one tag:

`MEASURED-INPUT` · `DERIVED` · `COMPUTED` · `CALIBRATED(n)` · `OBSERVED-TARGET` · `IDENTITY` · `ASSUMED` · `PENDING`

If a constant is read from `sdt::laws::measured` or `bridge`, **do not redefine it locally** (§0 anti-creep).

---

## 6 · Standard files per run

| File | When | Contents |
|------|------|----------|
| `RUN_LOG.md` | Start of run | Pre-commit block, ADJ entries, phase gates |
| `<id>_results.txt` | After each full run | Machine output (stdout capture) |
| `<ID>_DERIVATION.md` | When prompt §⑥ requires | Analytic steps; DERIVED vs ASSUMED flagged |
| `<ID>_VERDICT.md` | End of run | Dual verdict + falsification table updated |

---

## 7 · Escalation to stack

Update `INVESTIGATION_STACK.md` status tag when:
- **RESOLVED** — Prompt completion ≥ B and physics class NATIVE or honest CONVERGENCE
- **ACTIVE** — Partial run with OPEN/DEFER documented
- **KILLED** — KILL decision with numbers
- **DEGENERATE** — Matches rival without beating (CR10, GOM08 pattern)

---

## 8 · Failure Recovery Protocol — the seven questions (MANDATORY on any KILL / OPEN / DEFER / FAIL)

> **Principle (Harvey, 2026-07-02):** *failure is always in the premise, not the outcome.* Finding a fault
> easily does not entitle you to stop — it obliges you to hunt the fix with the same rigour you found the
> fault. A KILL/OPEN/DEFER is **not final** until the seven questions are answered honestly in a
> `## FAILURE RECOVERY` section of the `*_VERDICT.md`.

When a phase or falsifier resolves to **KILL / OPEN / DEFER / FAIL**, answer in order:

1. **If fail, why?** — the exact mechanism of the miss (the number, the sign, the magnitude), not "it didn't work."
2. **Can it be recovered?** — is there any forward route, or is the miss fundamental?
3. **What did the original target fail to account for?** — the omitted quantity or effect.
4. **What premise was errored?** — locate the FALSE ASSUMPTION (failure lives in the premise, not the
   outcome). Name it explicitly.
5. **What freedom corrects it?** — the specific degree of freedom whose adjustment fixes the outcome.
6. **What could account for that freedom?** — is the freedom JUSTIFIED by the framework (another
   investigation, a native quantity), or is it a bare knob?
7. **Does this failure cascade from another overlooked error?** — independent, or downstream of a shared
   unbuilt piece? Name the root; link failures that share it.

**Anti-fake-recovery discipline (mirror of the anti-fake-PASS rules):** a recovery may not be fished any more
than a PASS may. If step 5's freedom only lands the target when tuned and step 6 cannot justify it
independently, the honest verdict is **OPEN, with the premise-error and the missing justification named** —
**not** "recovered." Grade the recovery: `RECOVERED` (freedom justified, target now falls out) /
`PARTIAL` (route + premise-error named, freedom not yet justified) / `NO RECOVERY` (premise error fundamental).

**Cascade ledger:** when step 7 links ≥2 failures to one root, record it ONCE in `INVESTIGATION_STACK.md` — a
shared root means paying it once may clear several debts. (This is where "find the problem easily → find the
solution easily" actually pays off: not per-failure, but at the root they share.)

---

*Spatial Displacement Theory · Investigations · the plan must bend, not break.*
