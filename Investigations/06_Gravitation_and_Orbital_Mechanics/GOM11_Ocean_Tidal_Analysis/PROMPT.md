# GOM11: Ocean Tides — the forcing earned, the ratio clean, and the Q=2.31 lesson institutionalised

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27). **The E99 lesson is this investigation's constitution:** the prior "M2 amplitude
> PASS" rode a hardcoded ocean-response factor Q = 2.31 — a CALIBRATED knob dressed as a
> prediction. That failure mode is now structurally excluded below.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G.
> **Engine:** `#include <sdt/laws.hpp>` only. **Execution: DIRECT ONLY — no agents.**
> Prior agent-era VERDICT/results deleted 2026-07-24 (git-recoverable).

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — What, exactly, SDT can claim about ocean tides once the E99 taint
   is removed. Split honestly, the candidate claims are:
   (a) the **forcing** — the tidal acceleration field (amplitude and r⁻³ form) computed from
   ϟ_Moon and ϟ_Sun with no G/M: SDT computes this cleanly, and it is CONVERGENT with Newton
   (shared gradient algebra through the bridge);
   (b) the **equilibrium tide** — the ~0.24 m static bulge that follows from the forcing plus
   Earth's response (Love numbers, OBSERVED-ANCHOR);
   (c) the **observed M2 amplitude** (~0.63 m ocean mean) — which exceeds the equilibrium tide
   because of OCEAN DYNAMICS (basin resonances) that are *nobody's* first-principles number,
   not SDT's to derive and not a legitimate target — this is where Q = 2.31 was smuggled;
   (d) the **M2/S2 ratio** — in which the ocean response largely CANCELS, making it the one
   genuinely clean observable: measured ≈ 2.17–2.18; SDT's forcing ratio (ϟ_Moon/d_M³)/(ϟ_Sun/d_S³)
   must land it with zero knobs. The E99 record already found this leg genuine (2.177).
2. **Why does it matter?** — The tidal sector is where the repo once passed a fit off as a
   prediction; running it clean, with the claim-boundary drawn correctly, converts a graveyard
   item into a small, solid, honest CONVERGENCE + one clean zero-knob ratio — and it is the
   forcing-side prerequisite for GOM03's real-data phase and any E99 recovery.
3. **How will we find out?** — §④: P1 forcing from koppa (amplitude + form, labeled); P2 the
   equilibrium tide with Love numbers labeled as anchors; P3 the M2/S2 ratio (the clean gate);
   P4 (stretch, F8-gated) station-level comparison with the ocean response handled by an
   EXTERNAL tidal model cited as OBSERVED-ANCHOR, never fitted in-house.
4. **What would prove us wrong?** — §⑧: forcing amplitude off from the standard tidal
   acceleration (shared algebra — cannot honestly miss; a miss = inputs bug); M2/S2 ratio off
   by >1% with clean inputs (the ϟ-ledger's lunar/solar strengths are wrong — a real problem
   feeding back to GOM02); any run needing an in-house fitted response factor (the Q-shape
   returns → that leg is CALIBRATED and says so or dies).
5. **How will we know we're done?** — Dual verdict; the four claims (a)–(d) each carrying its
   own label; no aggregate "tides PASS" line permitted.

## §0 Reader's contract

1. **The Q rule (from E99).** No ocean-response factor may be computed, fitted, or tuned in
   this investigation. The ocean's dynamic amplification is an external, cited, labeled anchor
   (from FES/TPXO-class models or gauge data) or it is absent. Any number that needs it carries
   `[× external ocean response — OBSERVED-ANCHOR]` visibly.
2. **Shared-form honesty.** The r⁻³ tidal form and its coefficient are Newton's under the
   bridge — CONVERGENCE ceiling for (a) and (b). The zero-knob content is (d), and only (d).
3. **No G, no M**; Love numbers h₂,k₂,l₂ = IERS OBSERVED-ANCHORS, labeled.
4. **Data:** MUST_FETCH **F8** (harmonic constants) gates P4 only; P1–P3 run on ephemeris
   distances and koppa values already in hand. The old tool's hardcoded constants are audited
   at P0 — any embedded Q-like factor is found, named, and stripped.
5. **Direct only; teed stdout; fresh dated verdict.**

## §1 Definitions and anchors

| Quantity | Value | Label |
|---|---|---|
| ϟ_Moon · ϟ_Sun | 5.46×10⁻⁵ m · 1477 m | COMPUTED (kinematics) |
| d_Moon · d_Sun | 3.844×10⁸ · 1.496×10¹¹ m (means; ephemeris) | OBSERVED-anchor |
| tidal acceleration form | a_t = 2c²ϟ·R_E/d³ | CONVERGENT (bridge algebra) |
| equilibrium tide | ~0.24 m (lunar, before response) | derived in P2 with anchors labeled |
| observed M2 ocean mean | ~0.63 m | OBSERVED — NOT a target (contract §1) |
| M2/S2 forcing ratio | measured ≈ 2.17–2.18 | OBSERVED-anchor — THE clean gate |
| Love numbers h₂=0.61, k₂=0.30 | IERS | OBSERVED-anchor |

## §④ Phases

**P0 — Tool audit (gate).** Read `gom11_ocean_tidal.cpp` in full: locate every embedded
constant; classify (kinematic input / anchor / **response-factor contraband**). Any Q-like
factor found is reported with its value and stripped before P1. G/M sweep included.

**P1 — The forcing, from koppa.** Lunar and solar tidal acceleration amplitudes at Earth's
surface from a_t = 2c²ϟ·R_E/d³; the full angular pattern (cos θ_z dependence). Gates: lunar
a_t = 1.10×10⁻⁶ m/s² ±1%; solar = 5.0×10⁻⁷ ±1% (input-precision-limited; these are the
standard values — shared algebra, labeled CONVERGENT).

**P2 — The equilibrium tide.** Static bulge from P1's forcing + Love numbers (labeled):
lunar ~0.24 m, solar ~0.11 m. Gate: ±5%. Output lines carry the anchor labels. The gap between
0.24 and the observed 0.63 is PRINTED AND NAMED (ocean dynamics — external), so no future
reader mistakes the boundary.

**P3 — The clean gate: M2/S2 with zero knobs.** Ratio = (ϟ_M/d_M³)/(ϟ_S/d_S³) with ephemeris
means (and the eccentricity-averaged refinement stated). Gate: **2.17 ± 1%, zero adjustable
anything.** This is the investigation's one hard claim; a miss here is real news (feeds GOM02's
invariance case since it tests ϟ_Moon/ϟ_Sun directly against an independent observable).

**P4 — STRETCH (F8-gated).** Station-level M2/S2/K1/O1 against ≥20 gauges with the ocean
response supplied by a cited external model, labeled per contract §1. Purpose: consistency
demonstration, ceiling CONVERGENCE — stated before it runs so nobody banks it.

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | P1 misses ±1% | inputs bug (shared algebra cannot miss) — STOP, fix |
| F2 | P3 misses 2.17 ± 1% clean | ϟ_M/ϟ_S ledger defect — escalate to GOM02/root-2, genuinely serious |
| F3 | any leg needs an in-house response factor | that leg CALIBRATED-or-dead, stated; the Q lesson repeats NEVER silently |
| F4 | P0 finds contraband constants | strip + ADJ before any physics phase |

## §⑨.E Four-root sort
root-1 (ϟ ratio genuinely wrong) · root-2 (ephemeris/Love inputs) · root-3 (spec: averaging
convention for d³ — state it, compute both mean-distance and eccentricity-averaged) · root-4
(gate contraband — none expected; all anchors are measured-world).

## §⑤ Outputs
Fresh `RUN_LOG.md` · audited/stripped `gom11_ocean_tidal.cpp` · `gom11_rerun_<date>.txt` ·
`GOM11_VERDICT_DIRECT_<date>.md` (four claims, four labels; the P3 number headline).

## §6 Dependencies
Upstream: bridge · ephemeris distances. Data: F8 (P4 only). Siblings: GOM03 (forcing consumer),
E99 (graveyard item this cleans the path for), GOM02 (P3 feeds the ledger case).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM11 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- Claims and ceilings: (a) forcing CONVERGENT · (b) equilibrium CONVERGENT+anchors ·
  (c) observed amplitude NOT A TARGET · (d) M2/S2 = the one zero-knob gate
- CALIBRATED budget: 0 — the Q rule is absolute
- Gates: P1 ±1% · P2 ±5% · P3 2.17 ± 1% zero-knob
- Forbidden: in-house response factors; aggregate "tides PASS" lines; G/M; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 finds Q-like constant | strip, ADJ, re-run | — | keeping it "temporarily" |
| P3 between 1% and 3% | check eccentricity-averaging convention (root-3) | F2 escalation | widening the gate |
| F8 unavailable for P4 | P4 deferred, stated | — | substituting hand-typed gauges |

---

*GOM11 · upgraded 2026-07-24 · the ocean's amplification is real physics and it is not ours;
the forcing is ours, the ratio is clean, and the boundary between them is the whole verdict.*
