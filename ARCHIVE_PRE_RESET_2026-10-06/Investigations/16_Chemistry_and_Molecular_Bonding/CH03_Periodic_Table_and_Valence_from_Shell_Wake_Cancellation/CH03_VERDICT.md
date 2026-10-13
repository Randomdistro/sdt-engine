# CH03 — VERDICT: Periodic Table & Valence from Shell Wake-Cancellation

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Tool: `ch03_valence_wakes.py` (exit 1 — honest) · Output: `results.txt`

## Results (gates committed in RUN_LOG.md before the run)

| Phase | Result | Call |
|---|---|---|
| P1/M0 valence tally | `active(n)=min(n,2S−n)` on CALIBRATED capacities {2,8,8}: **18/18** Z=1–18 | matches — but capped: **re-labelling** unless M1 derives the filling |
| P2 octet | He/Ne/Ar = zero-active fixed point | arithmetic of M0 — inherits M0's cap |
| M1 native filling | exact enumeration, 1/d seat kernel: **6/8** — fails at n=2 (min-energy = antipodal pair → Be active 0, needs 2) and n=6 (min-energy = 3 full diagonals → O active 0, needs 2) | **FAIL — the tally is seeded, not derived** (firewall fires exactly as pre-registered) |
| M2 pairing → magnetism | N₂ ✓ diamagnetic; **O₂ ✗ predicted diamagnetic, measured paramagnetic** (χ_mol = +3449×10⁻⁶ cm³/mol — measured anchor, no rival story) | **KILL trigger fired** |
| P4 novel call | NO: residual 1 active → paramagnetic, measured paramagnetic | ✓ (one correct novel call, odd-count class only) |

The honest content: the min(n, 2S−n) arithmetic reproduces every main-group valence, **but the machinery does not yet own it** — static seats with a 1/d kernel pair up at n=2 and n=6 instead of spreading, and the same all-pairing failure is what kills the O₂ call. One premise produces both misses.

## FAILURE RECOVERY (§D seven questions)

**M1 (native filling, 6/8) and M2 (O₂) — answered together; they share the premise.**
1. Why: at n=2 and n=6 the minimum of Σ1/d over static seats is the antipodal (fully-paired) configuration — pairing is distance-maximising on a cube, so the model silences wakes the measured chemistry says are active. O₂: 2+2 actives all pair across the bond → residual 0 → diamagnetic; measured susceptibility says two unpaired signatures.
2. Recoverable: yes in principle — the failure is in the seat model, not in the tally's arithmetic (which matches 18/18).
3. Unaccounted: whatever makes pairing COSTLY when it is geometrically available — the measured table behaves as if wakes spread before they pair (and as if O₂ keeps two unpaired).
4. Errored premise (named): **static, simultaneous seat occupancy.** FARMER refinement 4: electron positions are **sequential** — a gear-stepped tour, not eight tenants. A tour has no "two electrons sit antipodal for free"; pairing on a tour is a timing constraint, not a distance choice. This run was executed inside the static-seat premise class.
5. Freedom: the tour-ordering / dwell-time rule of FLM14 (sequential occupancy; pairing = two tours phase-locked fore/aft).
6. Accounting: native — FLM14 is a committed program with its own kill gates, not a knob invented here. Nothing was tuned in this run to rescue anything.
7. Cascade: **yes — both CH03 failures run to ground at the same root** (static seats), which is the identical premise FARMER already caught escaping QM04/05, PPT08, NP10, FLM03. Not an independent CH03 defect.

**Recovery grade: PARTIAL** — premise located and named, corrective freedom (FLM14 tour) is native and pre-existing, but the tour rule is not yet built, so nothing is promoted. Re-open condition: FLM14 lands its sequential-occupancy rule; CH03 M1/M2 are then re-run inside the rotation class. Per §G.3: "valence cannot be derived from wake seats" is **not** claimed — the negative holds in the static-seat class only.

## Cascade root (reported)

**ROOT-SEAT (= FLM14 sequential-occupancy root):** CH03-M1 (Be/O filling), CH03-M2 (O₂ paramagnetism). Same root FARMER logged for QM04/05, PPT08, NP10-angular-window, FLM03.

## Canonical line

**Prompt completion C (tally + octet + one novel call, capacities CALIBRATED(1), firewall honoured) · Physics class LINGUISTIC (M0/P2: re-labelling of the measured table) / KILLED-in-static-class (M2 pairing map at O₂) · Recovery PARTIAL · Cascade root ROOT-SEAT (FLM14)**

---

## ⟐ RE-OPENED (2026-07-06) — §G.3 premise-class event (Harvey order)

**Trigger:** FARMER refinement 8 (movement triad + rolling/meshing wake firewall). The M2 kill
was recorded KILLED-in-static-class; the mesh class now NAMES the missing mechanism: pairing
is a **cadence/closure constraint, not a distance choice** — a shell closes only when its tours
mesh completely, and **O₂ is a structure that cannot fully close with one identical partner**
(two residual unpaired defects = the measured paramagnetism, stated before any model run).
N₂'s complete triple-mesh closure vs O₂'s incomplete closure is the committed qualitative
fork. **What this does NOT do:** no label changes — M1/M2 stay killed-in-static-class until a
pre-committed mesh-class run lands; the original re-open condition (FLM14 sequential-occupancy
rule) remains the full payer and is still unpaid (run-5 claim REFUSED; run-6 dwell measure is
the named instrument). Quantitative gate for any re-run, committed now: the mesh-closure model
must produce O₂'s TWO unpaired defects and N₂'s zero with the same rule, no per-molecule freedom.
