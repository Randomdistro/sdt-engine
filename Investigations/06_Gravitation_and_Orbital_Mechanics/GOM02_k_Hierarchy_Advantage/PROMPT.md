# GOM02: The k-Hierarchy Advantage — what one formula spans, what that proves, and the identity audit

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes the
> 2026-06-27 bulk-template version; Golden-Rule Q1 was unfilled, the koppa identity was mislabeled a
> "prediction," and the spec said "proton charge radius" — all corrected below).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G.
> **Engine:** `#include <sdt/laws.hpp>` only. **Execution: DIRECT ONLY — no agents.**
> **Run:** §⑩ commitments to `RUN_LOG.md` before code. Prior agent-era verdict deleted 2026-07-24.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Whether the k-hierarchy's claimed *advantage* over G/M is
   (a) **demonstrable as measurement**, not rhetoric: koppa recovered independently from every
   dependent of a host must agree to ephemeris-class precision, beating G's 22 ppm wall — the
   spread IS the thesis, and it has never been gated; and (b) **honestly sorted**: which rows of
   the showcase table are IDENTITIES (algebra), which are COMPUTED (kinematics), and which are
   the two genuinely earned items (the W+1 boundary-radius landing; the cross-scale reach where
   GM is undefined). The prior spec sold the whole table at one price.
2. **Why does it matter?** — The k-hierarchy is the campaign's Front-2 precision argument: SDT
   discards the worst-measured constant in physics and keeps full ephemeris precision. If the
   koppa-invariance gate passes at 1e-8-class spread, that is a *measured* superiority no rival
   bookkeeping shares; if it only passes at percent-class, the "advantage" is bookkeeping
   elegance and must be sold as that. Downstream: GOM14 (the dataset), GOM17 (the ledger),
   GOM19 (chirp-as-ϟ), the website copy.
3. **How will we find out?** — §④: P1 identity audit of every table row (label before compute);
   P2 the koppa-invariance gate on the GOM14 multiplanet dataset (693 dependents, cached);
   P3 the cross-scale bridge with per-rung labels; P4 the G-comparison stated in measurement
   terms only.
4. **What would prove us wrong?** — §⑧: host-wise koppa spread worse than the G-route for clean
   systems (advantage FAILS as measurement); any identity row found load-bearing in a claimed
   prediction (relabel + strike); the W+1 row failing its 0.02% window on recompute.
5. **How will we know we're done?** — Dual verdict; the showcase table republished with a LABEL
   COLUMN (IDENTITY / COMPUTED / DERIVED / OBSERVED-anchor) and the invariance number banked.

---

## §0 Reader's contract

1. **The identity rule (fired-ledger lesson, 2026-07-23).** ϟ_H = r_e is an exact algebraic
   identity: ϟ_H = (αc)²a₀/c² = α²a₀ = αℏ/(m_e c) ≡ r_e by definition of r_e. It is a
   *unification reading* — the same object appearing on two rungs — and it may NEVER be scored
   as a prediction. Same for z·k² = 1. The identity audit (P1) exists precisely to stop this
   class of oversell, in both directions: an identity is not evidence, and it is also not
   nothing — it is the ledger's internal consistency, printed and labeled.
2. **Boundary radius**, never "charge radius" (no charge substance; R_p is the proton
   displacement boundary). The prior spec violated this; corrected throughout.
3. **Rhetoric is not a gate.** "GM_proton is 10³⁹ below ℓ_P, meaningless" is commentary — it may
   appear in prose, never as a scored result. Scored results are numbers with pre-registered
   tolerances.
4. **The stricken claim.** The old capability table asserted "predict stellar rotation
   (v_rot = πv²/c)" with no source anywhere in the repo. STRUCK — do not carry it. If a rotation
   law is wanted, it gets its own investigation with its own derivation.
5. **No G, no M in-chain.** G appears exactly twice, both as OBSERVED rival columns: its 22 ppm
   uncertainty (the thing the thesis beats) and the GM ≡ ϟc² conversion check.
6. **Direct execution only; teed stdout; verdict quotes today's output.**

## §1 Definitions

| Symbol | Form | Label |
|---|---|---|
| k = c/v | velocity ratio | COMPUTED per body |
| z = 1/k² | depth | IDENTITY with k (one quantity, three views) |
| ϟ = v²R/c² = R/k² | koppa | COMPUTED from kinematics (no G/M) |
| ϟ_H = r_e | hydrogen koppa | **IDENTITY** (contract §1) |
| R_p = 4ℏ/(m_p c) | proton **boundary radius**, W+1 rule | DERIVED-conjectural (Law VI; 0.02% vs muonic-H; the campaign's strongest ledger row, delete-test per EMC04) |
| GM = ϟc² | rival bridge | conversion only, labeled |
| G = 6.67430(15)e-11 | rival constant | OBSERVED — 22 ppm, the comparison target |

Anchors: DE440-class GM_host precision ~1e-10 relative (planetary ephemerides); G at 22 ppm;
muonic-H R_p = 0.84087(39) fm; the GOM14 dataset `koppa_multiplanet.csv` (cached in-folder,
112,586 bytes — dependents' (a, T) pairs per host).

## §④ Phases

**P0 — Sanity.** Engine symbols; recompute the five-row hierarchy table (proton, H, Sun, Earth,
Moon) from kinematic inputs; k spans 0.5464 → 1.78×10⁵ printed.

**P1 — The identity audit (label BEFORE compute).** For every row/claim in the prior showcase:
mark IDENTITY / COMPUTED / DERIVED / OBSERVED / STRUCK. Pre-committed outcomes of this audit —
written here so the run can only confirm-or-correct the labels, not invent them:
z·k² = 1 → IDENTITY. ϟ_H = r_e → IDENTITY. ϟ_Sun = r_s/2 correspondence → IDENTITY (given
ϟ≡GM/c²). R_p = 4ℏ/(m_p c) landing at 0.02% → DERIVED-conjectural (the one row with a measured
target it did not consume — cite EMC04's delete-test). Proton k = 0.5464 → COMPUTED (from the
1.83c seat, NP27-supported). GM_proton commentary → prose only. v_rot claim → STRUCK.
**Gate: the published table carries the label column; any relabel found necessary is ADJ-logged.**

**P2 — The koppa-invariance gate (the thesis, finally measured).** Using `koppa_multiplanet.csv`
(GOM14's pull): for every host with ≥2 dependents, compute ϟ_host = 4π²a³/(T²c²) from EACH
dependent independently. Per host: median ϟ, per-dependent residuals, and the host-wise
fractional spread s_host. Pre-registered gates:
- **G2a (clean systems):** for hosts with ≥4 well-tracked dependents (Sun, Jupiter, Saturn,
  Uranus, Neptune, Earth), s_host < 1×10⁻⁴ after excluding flagged irregulars (exclusions listed
  with reasons BEFORE residuals are inspected: ring-moons inside Roche interactions, captured
  irregulars with poor elements — the exclusion rule is orbit-quality class, never residual size).
- **G2b (the advantage number):** best-host spread s_min < 2.2×10⁻⁵ (i.e. **beats G's 22 ppm** —
  the thesis stated as a measurement). Expected from DE440-class inputs: ~1e-8 reachable; gate set
  loose of expectation, tight of the rival.
- **G2c (honesty):** report the WORST host too; a cherry-picked best without the distribution is
  VOID.
**This phase turns the prompt's rhetoric into one number: the measured invariance of ϟ across
independent dependents, side by side with 22 ppm.**

**P3 — The cross-scale bridge (labels attached per rung).** One formula, five rungs:
proton (1.83c seat, NP27) → hydrogen (αc, APS05's measured seat 137.0726) → Sun (686.3) →
Earth → Moon. Print k, z, ϟ per rung with the P1 label on each line. The bridge's honest claim:
*reach* (GM is undefined for four of the five rungs), not *prediction*.

**P4 — The G-comparison, measurement terms only.** Table: [route | what it needs | precision].
ϟ-route: (a,T) or (v,R) only → P2's measured spread. G-route: GM (1e-10) ÷ G (22 ppm) → M at
22 ppm. One sentence of prose permitted: decomposing GM through G *destroys five orders of
precision and buys nothing the dynamics ever uses*. That sentence must cite P2's number.

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | G2a fails on a clean system (spread ≥1e-4, no orbit-quality cause) | koppa invariance FAILS — the advantage thesis is bookkeeping only; record and stop selling it as measurement |
| F2 | G2b fails (no host beats 22 ppm) | the headline is retracted to "matches GM precision, discards G" — weaker, stated honestly |
| F3 | any P1 IDENTITY row found scored as prediction anywhere downstream (grep the repo) | flag the downstream file to CANON_FLAGS (propose-only) |
| F4 | R_p recompute misses 0.02% window | Law VI row broken — escalate to stack (root-2, W+1) |
| F5 | exclusion rule touched after residuals seen | run VOID (anti-cherry-pick) |

## §⑨.E Four-root sort
root-1 thesis false (invariance genuinely fails) · root-2 dependency (ephemeris input quality;
W+1) · root-3 spec (exclusion rule under-specified — fix rule, full re-run) · root-4 gate
contraband (a gate protecting G's role — kill the gate).

## §⑤ Outputs
`RUN_LOG.md` (fresh) · `gom02_k_hierarchy.cpp` re-audited against THIS spec (it predates the
identity audit — patch its print-labels, ADJ-log) + a P2 driver (new: `gom02_koppa_invariance.py`
or extend the .cpp to ingest the CSV) · `gom02_rerun_<date>.txt` · `GOM02_VERDICT_DIRECT_<date>.md`
(dual verdict + labeled table + the invariance number).

## §6 Dependencies
Upstream: laws.hpp bridge:: · NP27 (1.83c) · EMC04 (R_p delete-test) · APS05 (measured H seat).
Data: `../GOM14_Koppa_Density_Multiplanet_Consistency/koppa_multiplanet.csv` (cached; cite by
path; hash at read). Downstream: GOM14 (shares the dataset — GOM02 gates invariance, GOM14 gates
density-consistency), GOM17/GOM19 (ledger users), website copy (the honest version of the
"no G" pitch).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM02 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- Physics class ceiling: the advantage is a MEASUREMENT claim (P2) + a REACH claim (P3);
  identities are labeled and never scored
- CALIBRATED budget: 0
- Gates: G2a <1e-4 clean-host spread · G2b best-host < 2.2e-5 (beat G) · G2c full distribution
  · P1 labels as pre-committed · R_p window 0.02%
- Exclusion rule (frozen now): orbit-quality class only — ring-region moons, captured irregulars
  with GRADE<B elements; NEVER by residual size
- Forbidden: scoring identities; "charge radius"; v_rot claim; touching exclusions post-hoc;
  G/M in-chain; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| CSV schema surprise | inspect header, ADJ-log parse fix | P2 BLOCKED — report | hand-editing data |
| clean host misses G2a | check element quality (root-2) per dependent, documented | F1 fires — record | residual-based pruning |
| best host between 2.2e-5 and 1e-4 | report as-is; F2 retraction applies | — | widening G2b |
| .cpp won't take labels cleanly | new P2 driver script, ADJ-logged | — | skipping the label column |

---

*GOM02 · upgraded 2026-07-24 · the advantage becomes one measured number or it becomes prose;
the identities get named either way. Newton found the projection; prove the source measures better.*
