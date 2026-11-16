# GOM13: The Occlusion-Altitude Cavendish — after the kill: the corrected law, the reachability audit, and the H1 keystone

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27). **Constitutional history, up front:** the original sin-dip law (ΔF/F = sin δ,
> +1.8% at 1 km) was **killed by Harvey's FARMER correction (2026-07-03)** — it counted the
> planet as a TOTAL occluder, violating Law III's transparent-relay, per-baryon principle, and
> the pre-flight run excluded it **47×** against the existing precision-G record. The Adjudicator
> (KILL_REVIEW 2026-07-08 §H-3) **RESCOPED**: the kill attaches to the radius-typed transcription
> only; the **count-typed (mass-column) form survives** — and lands exactly on the Bouguer
> gradient (~4.4×10⁻⁷ at the surface), i.e. the native occlusion signal is already inside a
> century of gravimetry, **degenerate with the Newtonian slab**. The corrected altitude ramp is
> ~10⁻⁹-class — **below any current lock-in floor — so the balloon flight as designed does not
> discriminate.** This upgraded spec is the honest continuation: derive both forms direct,
> audit every remaining channel for reachability, and either find a live observable or park the
> branch formally with re-entry triggers. The old sin-dip body is preserved in §A (appendix,
> historical record of the killed transcription) — it is NOT part of the runnable spec.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G.
> **Engine:** `#include <sdt/laws.hpp>` only. **Execution: DIRECT ONLY — no agents.**
> Prior agent-era VERDICT/RUN_LOG/results deleted 2026-07-24 (git-recoverable); the direct
> adjudication record lives in `KILL_REVIEW_2026-07-08.md` (untouched).

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Post-kill, three things:
   (a) whether the corrected **count-typed occlusion form** (blocking ∝ mass column traversed,
   per-baryon, R²-cross-sections) is properly derived from Law III and reproduces, from SDT
   quantities, the **Bouguer gradient** it claims to be degenerate with (the convergence must be
   COMPUTED, not asserted);
   (b) whether ANY observable in this branch is **reachable** by real instruments: the δ(h)
   altitude ramp (~10⁻⁹ vs lock-in floors ~10⁻⁶–10⁻⁷?), the lab-elevation correlation in the
   historical G record (predicted gradient vs the actual 5×10⁻⁴ inter-lab scatter — E76's
   territory), and E104's κ-correlation channel (itself recorded sub-threshold) — each gets a
   computed signal-vs-floor ratio, not an adjective;
   (c) **H1, the keystone** (unchanged by the kill): does `laws.hpp` force macroscopic
   occlusion to scale with the ambient flux (`G_eff ∝ P_local`) while the EM restoring constant
   κ does NOT — gravity riding the ambient, EM riding local handedness (EMC03)? If H1 is
   underivable, every channel in this branch cancels in the ratio and the branch is
   structurally, not just practically, closed.
2. **Why does it matter?** — This branch once carried a flagship over-claim; it now carries the
   repo's best example of the system working (a Harvey-corrected kill with a surviving rescope).
   Finishing it honestly — live observable or formal park — closes E104/E23-adjacent campaign
   rows correctly and either revives E76 (G environment-dependence) with a magnitude or retires
   it from this mechanism.
3. **How will we find out?** — §④: P1 both forms derived direct (kill reproduced, convergence
   computed); P2 the reachability audit (three channels, three signal/floor ratios); P3 the H1
   derivation attempt; P4 disposition (live channel escalated, or branch PARKED with triggers).
4. **What would prove us wrong?** — §⑧: the count-typed form failing to reproduce Bouguer from
   SDT quantities (the rescope itself would collapse — the branch dies entirely, not parks);
   H1 derivable with the OPPOSITE sign (κ shares the coupling → ratio cancels → clean
   structural closure, recorded as an SDT self-consistency result: gravity and EM share one
   ambient coupling).
5. **How will we know we're done?** — Dual verdict + the disposition line (LIVE-CHANNEL /
   PARKED-with-triggers / BRANCH-DEAD) + the register's GOM13 entry completed with numbers.

## §0 Reader's contract

1. **The kill is settled.** Sin-dip is dead (FARMER 2026-07-03; 47×). No phase may resurrect it;
   §A is quarantined history. Any output resembling `sin(arccos(R/(R+h)))` at percent scale is a
   bug, not a discovery.
2. **Degeneracy honesty.** The count-typed form's surface signal IS the Bouguer term. That is
   CONVERGENCE (the occlusion reading of known gravimetry), never a discriminator. The only
   possible discriminators are the DIFFERENTIAL channels P2 audits.
3. **Numbers, not adjectives, for reachability.** Every channel verdict is a computed ratio
   (predicted signal / demonstrated instrument floor, with the floor cited). "Below floor" with
   the ratio attached; never "probably too small."
4. **H1 discipline.** The derivation must run in both directions honestly (§G mirror): deriving
   H1 true and deriving H1 false are both wins for the framework's coherence; only failing to
   decide is a loss. No steering toward the flyable answer.
5. **No G, no M in-chain**; the precision-G record (CODATA scatter, JILA/LANL values, lab
   elevations) enters as OBSERVED anchors.
6. **Direct only; teed stdout; fresh dated verdict; register update proposed in-verdict.**

## §1 Definitions and anchors

| Quantity | Value | Label |
|---|---|---|
| killed form | ΔF/F = sin δ, δ = arccos(R/(R+h)) | DEAD (47×; §A history) |
| corrected form | δF/F ∝ overhead mass column (per-baryon relay blocking) | the RESCOPED survivor — to derive in P1 |
| Bouguer gradient (surface) | ~4.4×10⁻⁷ per (standard slab) | OBSERVED-anchor (gravimetry) — the degeneracy partner |
| corrected altitude ramp | ~10⁻⁹-class (prior estimate — recompute in P1) | the P2-channel-1 signal |
| best torsion-balance floors | cite current art (~10⁻⁶–10⁻⁷ relative on F) | OBSERVED-anchor (P2) |
| G-record scatter | ~5×10⁻⁴ relative, inter-lab | OBSERVED-anchor (P2 channel 2 / E76) |
| E104 κ-correlation | recorded sub-threshold (δ ~1e-9 vs lock-in) | prior record — recompute, channel 3 |

## §④ Phases

**P0 — Sanity + tool audit.** `gom13_preflight.cpp` read fully: which form(s) it implements,
where the 2026-07-03 correction is reflected, G/M sweep. The three HTML decks
(BALLOON_EXPANSION, OCCLUSION_EXPERIMENT_DECK, SOFT_SATELLITE_CEILING) are engineering
collateral — kept, out of scope for physics claims.

**P1 — Both forms, derived direct.**
(a) Reproduce the kill: sin-dip's +2%-class prediction vs the precision-G record — the 47×
exclusion recomputed and logged (the register's GOM13 numbers re-earned direct).
(b) Derive the count-typed form from Law III (transparent relay, per-baryon cross-sections,
mass-column integral through the planet along each sky direction) and compute its surface
gradient. **Gate: reproduces the Bouguer gradient ~4.4×10⁻⁷ from SDT quantities with the
chain labeled** — the rescope's claim, finally computed. Failing this gate kills the branch
outright (F1).
(c) The corrected altitude ramp δ(h) recomputed from (b) — the honest replacement of the old
prediction table.

**P2 — The reachability audit (three channels, three ratios).**
- *Channel 1 — the flight:* δ(h) ramp vs the best demonstrated balance floors (cited). Expected
  honest outcome ~10⁻²–10⁻³ of floor → NOT REACHABLE; state the ratio and the floor-improvement
  factor that would change the answer.
- *Channel 2 — the archival scan (E76's cousin):* predicted G_eff dependence on lab overhead
  mass column (elevation, local topography, building mass) vs the actual G-record scatter.
  Compute the predicted spread across real measurement sites (use published lab elevations);
  ratio vs 5×10⁻⁴. If ≥ ~0.1 of scatter: a correlation scan of the record is worth running —
  escalate as the branch's live channel (archival, free). If ≪: recorded unreachable.
- *Channel 3 — E104's κ-correlation:* recompute the shared-P_eff correlation amplitude under
  the corrected form; compare to E104's recorded floor problem. Alive only if the corrected
  form changes its magnitude class.
**Each channel closes with LIVE / UNREACHABLE(ratio) — nothing else.**

**P3 — The H1 keystone derivation.** From laws.hpp: does the macroscopic occlusion coefficient
inherit P_local (ambient flux) while EMC03's handed redirection (the fibre's κ) does not?
Derive, both directions, §G-mirrored. Outcomes: H1-TRUE (branch channels physically real —
reachability per P2 stands), H1-FALSE (ratio cancels — the branch is STRUCTURALLY closed and
this becomes a coherence result: gravity and EM share the ambient coupling; record as a
finding, feed to EMC01/EMC04), H1-UNDECIDED (name the missing derivation — likely the
dynamic/ambient extension of P_eff — and park on it).

**P4 — Disposition.** One of: **LIVE-CHANNEL** (P2 found a reachable observable → escalate to
campaign with its number) · **PARKED** (all channels unreachable; triggers named: balance-floor
factor X, or the E104 redesign, or H1 resolution) · **BRANCH-DEAD** (F1 fired, or H1-FALSE).
The register's GOM13 line and the campaign's E104/E23-adjacent rows updated (proposed
in-verdict; Harvey ratifies).

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | count-typed form fails to reproduce Bouguer from SDT quantities | the rescope collapses — BRANCH-DEAD, register updated |
| F2 | P2 ratios computed with uncited floors | audit VOID — redo with citations |
| F3 | H1 steered (one direction argued, other skipped) | P3 VOID (§G violation) |
| F4 | any sin-dip revival | bug — see contract §1 |

## §⑨.E Four-root sort
root-1 (branch genuinely empty — every channel unreachable and H1 undecidable) · root-2
(P_eff/ambient-flux dependency — EMC04/FLM lattice EoS) · root-3 (spec: mass-column integral
convention — state it, bracket it) · root-4 (gate contraband — the Bouguer gate is
measured-world, legitimate).

## §⑤ Outputs
Fresh `RUN_LOG.md` · audited `gom13_preflight.cpp` (+ P1b/P2 extensions) ·
`gom13_rerun_<date>.txt` · `GOM13_VERDICT_DIRECT_<date>.md` (dual verdict + three channel
ratios + H1 outcome + disposition) · register/campaign updates proposed.

## §6 Dependencies
Upstream: Law III (per-baryon relay) · EMC03 (handedness locality — H1's other half) · EMC04
(P_eff, direct-class) · FARMER correction (2026-07-03, constitutional) · KILL_REVIEW §H-3
(the rescope). Anchors: precision-G record + lab metadata (channel 2), balance floors (channel
1), E104 record (channel 3). Downstream: E76 (lives or retires on channel 2), E104 (channel 3),
E23-class shell tests (mechanism cousin).

## §A — APPENDIX: the killed sin-dip spec (historical record, quarantined)

The original 2026-06 body (executive summary, the sin-dip fork table, the +1.8%/+5.3%/+11%
prediction curve, the cascade-balloon platform §7, and the three-test protocol §8) is preserved
in git history at this file's pre-2026-07-24 revision and summarised here in one line each for
the record: sin-dip law ΔF/F = sinδ [KILLED 47×, FARMER 2026-07-03]; tilt-budget lock β = δ
[dies with it]; cascade balloon staged-expansion platform [engineering, retained in the HTML
decks]; the three-test flight protocol [moot below floor]. Nothing in this appendix is
runnable. The balloon engineering remains available to any future experiment that earns a
reachable signal.

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM13 (2026-07-24 spec; post-kill continuation)
- Prompt completion target: [A|B|C]
- Gates: P1b Bouguer from SDT chain (branch-fatal if missed) · P2 three ratios with cited
  floors · P3 both-directions H1 · P4 one disposition word
- CALIBRATED budget: 0
- Forbidden: sin-dip revival; adjective reachability; steering H1; flying anything on paper
  before P2 says LIVE; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1b integral convention ambiguous | bracket both conventions, report both | root-3 recorded | picking silently |
| channel-2 lab metadata sparse | use the documented subset, state coverage | UNREACHABLE(partial) | inventing elevations |
| P3 stalls at ambient-P_eff | name the missing derivation, PARK on it | H1-UNDECIDED | assuming either way |

---

*GOM13 · upgraded 2026-07-24 · the branch where the system worked: a Harvey kill, a surviving
rescope, and now the duty to finish it with ratios instead of romance. Park it clean or find
the live wire.*
