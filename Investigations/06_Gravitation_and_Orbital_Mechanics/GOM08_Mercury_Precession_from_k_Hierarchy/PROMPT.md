# GOM08: Mercury Precession from the k-Hierarchy — the transplant named, and the equivalence-principle fork promoted

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27). The old spec was honest in its discussion ("the result will NECESSARILY match GR")
> but its methodology asserted a native origin for the 1/r³ term it never derived — that gap is
> now the investigation's centre. **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` ·
> `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G. **Engine:** `#include <sdt/laws.hpp>` only.
> **Execution: DIRECT ONLY — no agents.** Prior agent-era DERIVATION/VERDICT/results deleted
> 2026-07-24 (git-recoverable). Campaign status: E24 graduated here as CONVERGENCE — this spec
> keeps it honest and hunts the one place it could become more.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Two things, sharply separated:
   (a) whether SDT possesses a **native derivation** of the 1/r³ effective-potential correction —
   from the depth kernel z(r) = ϟ/r acting on angular momentum (GOM01 P3's second-order terms),
   or from the movement budget — as opposed to what the old spec actually did, which was
   **transplant GR's Schwarzschild potential under the substitution GM → c²R/k²** and call the
   result's origin "the k-gradient." Algebraically identical output; epistemically opposite
   provenance. Until the native route exists, the 42.98″/cy landing is an
   **IDENTITY-demonstration** (bridge algebra), not even convergence-with-mechanism.
   (b) whether SDT predicts **structure-dependence of precession** — the old §3's buried
   question, promoted here to a phase: GR's equivalence principle says a fluffy comet and a
   dense asteroid at the same orbit precess identically; if the k-coupling depends on the
   orbiter's own displacement field, SDT could differ — a genuine fork IF the effect survives
   magnitude estimation.
2. **Why does it matter?** — Mercury's 43″/cy is the historic gate every gravity theory must
   pass; passing it by transplant is worthless as evidence (any theory can relabel GR's
   potential), while passing it natively would upgrade the whole k-hierarchy sector. And the
   structure-dependence question is one of the few places the firing-log targeting rule (kills
   live where the rival predicts exactly zero) could apply inside orbital mechanics: GR predicts
   exactly zero composition-dependence.
3. **How will we find out?** — §④: P1 re-run the identity demonstration under its honest name;
   P2 attempt the native derivation of the 1/r³ coefficient (two routes given); P3 the
   structure-dependence estimate with a pre-committed decision rule; P4 cross-body check
   (Venus 8.6″, Earth 3.8″ — the k-formula must land all three with one substitution).
4. **What would prove us wrong?** — §⑧: P2 failing both routes leaves the sector permanently
   IDENTITY-class (recorded, not spun); P3 magnitude at measurable scale would face immediate
   test against existing ephemerides — a predicted effect already excluded by MESSENGER-class
   data KILLS the k-coupling variant that produced it.
5. **How will we know we're done?** — Dual verdict; the provenance ledger of the 1/r³ term
   (TRANSPLANT / NATIVE-derived) stated in the header; the fork question answered with a
   magnitude, not a vibe.

## §0 Reader's contract

1. **Name the transplant.** V_SDT(r) as written in the old spec IS V_GR(r) with GM → c²R/k²
   (the bridge identity makes them "ALGEBRAICALLY IDENTICAL" — its own words). Any run output
   line reporting the 43″ landing carries the label `[IDENTITY — bridge algebra; native 1/r³
   derivation OWED]` until P2 succeeds. The phrase "arises from the k-gradient" is banned until
   a derivation exists that starts from the k-gradient and reaches the coefficient.
2. **The degeneracy rule** (E107/GOM01): matching GR here can never be a kill or a "beats."
   Ceiling: CONVERGENCE — and only after P2; otherwise IDENTITY.
3. **No G, no M in-chain**; `bridge::GM_equivalent` in rival columns only. The published GR
   value 42.98 ± 0.04″/cy is the OBSERVED anchor (itself extracted through ephemeris fits that
   assume GR — theory-laden; comparison only).
4. **Equivalence-principle data discipline (P3).** Before estimating the structure-dependence
   magnitude, WRITE DOWN the decision rule: effect ≥ current ephemeris sensitivity → the
   variant is already testable and probably already excluded — check before publishing anything;
   effect < sensitivity → record as unfalsifiable-at-present, park honestly. No third option.
5. **Direct execution only; teed stdout; fresh dated verdict.**

## §1 Definitions and anchors

| Quantity | Value | Label |
|---|---|---|
| k_Sun | 686.3 (= c/v_surf-orbit) | COMPUTED |
| R_Sun | 6.957×10⁸ m | OBSERVED-anchor |
| ϟ_Sun = R_Sun/k² | 1477 m | COMPUTED |
| Mercury a, e | 5.7909×10¹⁰ m, 0.2056 | OBSERVED-anchor |
| δφ formula | 6πR_Sun/(k²a(1−e²)) | = 6πϟ/(a(1−e²)) — provenance per contract §1 |
| anchor | 42.98 ± 0.04 ″/cy | OBSERVED-through-ephemeris (rival-fit; comparison only) |
| cross-body anchors | Venus 8.62″ · Earth 3.84″ | same |

## §④ Phases

**P0 — Sanity + source audit.** Engine symbols; audit `gom08_mercury_precession.cpp` for (a) G/M
in-chain, (b) whether it computes δφ from the SDT symbols or hardcodes GR's form — report which,
because that IS the provenance question at code level.

**P1 — The identity demonstration, honestly labeled.** Compute δφ = 6πϟ_Sun/(a(1−e²)) × 415
orbits/cy × 206265. Gate: 42.98 ± 0.1″. Every output line: `[IDENTITY]` label per contract §1.
Also print the explicit two-column algebra (SDT form | GR form | the substitution mapping them)
— the demonstration that they are one expression, which is the honest content of this phase.

**P2 — The native derivation attempt (the phase that could change the class).** Two routes,
pre-committed; trying both and failing both is an acceptable, recordable outcome:
- *Route A — depth-kernel second order (wired to GOM01 P3):* expand the orbit equation in
  z = ϟ/r to second order with the movement budget v² + v_circ² = c² enforcing the closure at
  each radius; the 1/r³ coefficient must EMERGE with its factor (the GR-equivalent 3) from the
  expansion, not be inserted. Deliverable: the coefficient with its derivation chain, each step
  labeled.
- *Route B — angular-momentum re-pricing:* the k-gradient changes the local conversion between
  transverse movement and angular momentum (L is defined against a lattice whose depth varies
  along the orbit); derive the correction to L-conservation and its induced apsidal advance.
- Gate: either route reproduces the full coefficient (not just the 1/r³ shape) with zero
  inserted constants → the P1 label upgrades IDENTITY → CONVERGENCE-with-mechanism, and the
  verdict says which route earned it. Both fail → the sector stays IDENTITY-class; recorded.

**P3 — The structure-dependence fork (promoted from the old §3).** Question: does the apsidal
advance depend on the orbiter's own ϟ_body (its internal displacement field), which GR's
equivalence principle forbids? Method: parameterise the candidate coupling δφ → δφ·(1 + ξ·ϟ_body/ϟ_Sun
or the ratio the P2-winning route naturally produces — the FORM must come from P2's mechanism,
not be invented free); compute the magnitude for the extreme available contrast (Mercury vs a
rubble comet at Mercury-like a). Decision rule per contract §4, written in RUN_LOG before the
number: measurable-and-excluded → that coupling variant KILLED; measurable-and-untested → a
pre-registrable fork (rare, valuable — escalate to campaign); unmeasurably small → parked, with
the number.

**P4 — Cross-body closure.** Same formula, zero refits: Venus and Earth. Gate: both within 2%
of their anchors. A per-body adjustment of anything = FAIL of the one-substitution claim.

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | P1 misses 42.98 ± 0.1″ | arithmetic/inputs bug (the identity cannot miss) — STOP, fix |
| F2 | P2 both routes fail | class locked at IDENTITY; verdict header says so; no "k-gradient" language survives |
| F3 | P3 coupling measurable but excluded by ephemerides | that variant KILLED, logged with the bound |
| F4 | P4 needs per-body adjustment | one-substitution claim FAILS — record |
| F5 | tool found hardcoding GR's form while output claims SDT derivation | provenance violation — patch + ADJ or verdict says TRANSPLANT-at-code-level |

## §⑨.E Four-root sort
root-1 (no native second-order structure exists) · root-2 (ϟ/k input precision; GOM01-P3
dependency) · root-3 (spec: coupling form under-specified — must come from P2) · root-4 (gate
contraband: demanding SDT reproduce GR's coefficient exactly IS legitimate here — the anchor is
measured precession, not GR's formula; keep the distinction).

## §⑤ Outputs
Fresh `RUN_LOG.md` · audited/patched `gom08_mercury_precession.cpp` · `gom08_rerun_<date>.txt` ·
`GOM08_VERDICT_DIRECT_<date>.md` (dual verdict + provenance ledger of the 1/r³ + the P3 number).

## §6 Dependencies
Upstream: bridge:: · GOM01 (P3 second-order kernel — Route A's engine) · Law V. Anchors:
ephemeris precessions (rival-fit, comparison only). Downstream: the campaign ledger row for E24
(stays CONVERGENT unless P2 lands); GOM19 (shares the second-order-kernel question at r ≪ 6ϟ).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM08 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- Physics class ceiling: IDENTITY until P2 lands; then CONVERGENCE. Never higher here.
- CALIBRATED budget: 0
- Gates: P1 42.98±0.1″ [IDENTITY-labeled] · P2 coefficient-with-chain or double-fail recorded ·
  P3 decision rule written BEFORE the magnitude · P4 Venus/Earth 2% zero-refit
- Forbidden: "arises from the k-gradient" without a chain; per-body tweaks; treating P1 as
  evidence; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P2 Route A expansion ambiguous | fix the expansion variable (z, not r) and re-derive | try Route B | inserting the 3 |
| P3 form underdetermined | take the P2-winner's natural ratio; if P2 failed, park P3 (no free forms) | — | inventing a coupling |
| P4 2% miss | check body anchors (root-2) | F4 fires | refitting k |

---

*GOM08 · upgraded 2026-07-24 · the 43″ is free through the bridge and worth nothing there;
the coefficient's derivation chain — or the equivalence-principle fork — is the only cargo.*
