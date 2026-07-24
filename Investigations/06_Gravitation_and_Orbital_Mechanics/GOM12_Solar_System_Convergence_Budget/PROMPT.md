# GOM12: The Solar-System Convergence Budget — a labeled audit, one gated question, and a numerology fence

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27). **Register/stack status:** PARTIAL on input precision (with GOM10 — clears with
> ephemeris-grade inputs). **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` ·
> `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G. **Engine:** `#include <sdt/laws.hpp>` only.
> **Execution: DIRECT ONLY — no agents.** Prior agent-era VERDICT/RUN_LOG/results deleted
> 2026-07-24 (git-recoverable).

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — The old spec was a grab-bag; sorted, it contains exactly one gated
   physical question and a set of labeled audits:
   **The question (E101/Law II):** does the solar system's total convergence budget BALANCE —
   i.e. does the summed throughput bookkeeping of the Sun's domain close against the Sun's
   output (L☉) as Law II requires? This has never been computed with labels on every term.
   **The audits:** zk² = 1 per body (IDENTITY — consistency print); v(r) = (c/k_☉)√(R_☉/r)
   across nine planets (CONVERGENCE — Kepler in koppa dress; the PARTIAL to clear at 0.1%);
   ϟ per body (COMPUTED); planetary convergence cross-contributions at Earth (bookkeeping —
   are any dynamically significant?); the solar pressure domain r_domain = √(L☉/4πF_CMB) vs
   the Oort inner edge (CONVERGENT-derivation, E106-linked — its DATA test is INCONCLUSIVE
   per the campaign firing log and stays that way here).
   **The fence:** the old "integer patterns in k² ratios between adjacent planets" item is a
   look-elsewhere trap (resonance numerology). It runs ONLY under a pre-registered protocol or
   not at all.
2. **Why does it matter?** — The budget question is Law II's solar-system face: if the ledger
   does not close, Law II's relay bookkeeping has a hole at the scale we know best; if it
   closes, the same bookkeeping that runs the CMB relay runs the heliosphere, and E101
   graduates from spec to computed consistency. The audits feed GOM02's precision case and
   clear this folder's register PARTIAL.
3. **How will we find out?** — §④: P1 the audit table with per-row labels (ephemeris-grade);
   P2 the budget computation with every term's provenance printed; P3 the domain/Oort
   comparison (factor-2 gate, honest E106 status attached); P4 the fenced pattern-scan
   (optional, protocol-gated).
4. **What would prove us wrong?** — §⑧: v(r) failing 0.1% with DE-grade inputs (Kepler-in-koppa
   broken — bridge defect); the budget failing closure by an order of magnitude with all terms
   labeled (Law II's solar-system bookkeeping has a named hole — record it; do NOT plug it);
   planetary cross-terms found significant but contradicting known ephemeris residuals.
5. **How will we know we're done?** — Dual verdict; the budget ledger printed term by term;
   the one gated question answered with a closure ratio and its uncertainty.

## §0 Reader's contract

1. **Label every row.** zk²=1 lines print `[IDENTITY]`. v(r) lines print `[CONVERGENCE —
   Kepler via bridge]`. Budget terms print their provenance (COMPUTED/OBSERVED-anchor/ASSUMED).
   An unlabeled number is a defect.
2. **The numerology fence.** The k-ratio pattern scan may run only with: the hypothesis class
   written first (which ratios, which integer families), the null model stated (how often
   near-integers occur by chance among 36 pairs), and a Bonferroni-style correction applied.
   Otherwise §P4 is skipped and the verdict says "not run (fence)". The measured-anchors
   memory-rule (look-elsewhere BEFORE killing or crowning) applies in both directions.
3. **No G, no M**; GM = c²R/k² appears once as the bridge conversion check, labeled.
4. **E106 honesty:** the 20,857 AU domain radius is a clean derivation whose FIRST DATA TEST
   was negative/ambiguous (osculating-aphelia, campaign firing log 2026-07-23). P3 compares
   derivations and known structure scales; it may NOT claim observational confirmation while
   the original-1/a retest (MUST_FETCH F3) is pending.
5. **Direct only; teed stdout; fresh dated verdict.**

## §1 Definitions and anchors

| Quantity | Form/value | Label |
|---|---|---|
| k per planet | c/v_orb (DE-grade v) | COMPUTED |
| z = 1/k² | — | IDENTITY with k |
| ϟ per body | R/k² (planets: from host-orbit v at surface? NO — from the body's OWN dependents where available; bodies without dependents: v_surf-orbit equivalent, stated) | COMPUTED — the per-body route stated explicitly in-run |
| v(r) profile | (c/k_☉)√(R_☉/r) | CONVERGENCE gate |
| r_domain | √(L☉/(4π F_CMB)) = 20,857 AU | DERIVED (E106-linked; data status per contract §4) |
| L☉ | 3.828×10²⁶ W | OBSERVED-anchor (IAU) |
| F_CMB | c·u_CMB/4 (laws.hpp:247) | DERIVED-from-anchors |
| budget closure ratio | Σ(term)/L☉ | THE gated output (P2) |

## §④ Phases

**P0 — Sanity + input upgrade.** DE-grade v_orb, R per body (cited); engine symbols; the ϟ-route
per body stated (contract table) BEFORE computing.

**P1 — The audit table (clears the PARTIAL).** Nine planets × {v_obs, v_pred, k, z, ϟ, zk²}:
gates — zk² = 1 to machine precision `[IDENTITY]`; v(r) within **0.1%** per planet (DE-grade;
the old run's misses were input-precision — reproduce-or-explain); bridge conversion check
GM = c²R/k² vs published GM per body `[conversion, labeled]`.

**P2 — The budget (the question).** Define the ledger explicitly, then compute:
- influx: the CMB convergence throughput intercepted by the Sun's domain (from F_CMB and the
  domain cross-section — each factor labeled);
- outflux: L☉ (anchor) + solar wind kinetic-energy flux (anchor, ~10⁻⁴ of L☉ — include and
  label) + the planets' interception bookkeeping (computed; expected tiny — print anyway);
- closure ratio C = influx/outflux with propagated input uncertainties.
Pre-registered reading (written before the number): **C within a factor 2 of 1 = Law II
bookkeeping closes at this scale** (E101 graduates to computed-consistency, CONVERGENCE class);
C off by 2–10× = structured discrepancy — localise which term, root-sort, report OPEN;
C off by >10× = Law II's solar face has a named hole — report it plainly, no plugging.
(Note the honest possibility, stated now: the lumiostasis construction r_domain = √(L☉/4πF_CMB)
makes interception ≈ output NEAR-TAUTOLOGICALLY at the domain boundary — P2 must check whether
the closure is an identity of the construction before crediting it as physics. If it is, the
verdict says IDENTITY, not consistency — the vocal-cords rule applied to ourselves.)

**P3 — Domain vs system structure.** r_domain = 20,857 AU printed against: Oort inner-edge
estimates (2,000–20,000 AU literature band — cite), heliopause (~120 AU — a DIFFERENT boundary,
say why: particle-wind pressure balance vs radiative), and the E106 status line (contract §4).
Factor-2 gate against the Oort band's upper region; no confirmation language.

**P4 — OPTIONAL, fenced.** The k-ratio pattern scan under the contract-§2 protocol, or the
explicit line "not run (fence)".

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | zk² ≠ 1 anywhere | algebra bug — STOP |
| F2 | v(r) > 0.1% with DE inputs | bridge/Kepler defect — escalate (cannot honestly fail) |
| F3 | P2 closure fails >10× with labeled terms | Law II solar hole — recorded OPEN, unplugged |
| F4 | P2 closure found tautological | verdict line: IDENTITY-of-construction (not consistency) — the honest downgrade |
| F5 | P4 run without its protocol | that section VOID |

## §⑨.E Four-root sort
root-1 (Law II bookkeeping genuinely fails here) · root-2 (anchors: L☉, u_CMB, DE inputs) ·
root-3 (spec: ledger term-definition ambiguous — fix definition, full re-run) · root-4 (gate
contraband — none expected).

## §⑤ Outputs
Fresh `RUN_LOG.md` · re-audited `gom12_convergence_budget.cpp` · `gom12_rerun_<date>.txt` ·
`GOM12_VERDICT_DIRECT_<date>.md` (audit table + the budget ledger + closure ratio + P3/P4 lines).

## §6 Dependencies
Upstream: bridge · Law I/II (laws.hpp) · GOM05 (lumiostasis construction — the tautology check
targets its form). Anchors: IAU L☉, DE ephemerides, FIRAS u_CMB. Siblings: E101 (this computes
it), E106 (domain data status), GOM02 (audit rows feed the ledger case), GOM10/12 register
PARTIAL (cleared by P1).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM12 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- The one gated question: budget closure ratio C, reading bands 2× / 10× pre-registered,
  WITH the tautology check (F4) run before any consistency credit
- CALIBRATED budget: 0
- Gates: P1 machine-precision identities + 0.1% v(r) · P2 bands + tautology check ·
  P3 factor-2, no confirmation language · P4 fenced
- Forbidden: plugging the budget; confirmation language on E106-linked items; unlabeled rows;
  unfenced pattern-scans; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 0.1% miss | DE-grade input check (root-2) | F2 escalation | widening |
| P2 term ambiguous | fix ledger definition, ADJ, full re-run | root-3 recorded | quiet redefinition mid-run |
| P2 closes suspiciously exactly | run F4 tautology check FIRST | IDENTITY verdict | banking it |
| P3 Oort band unclear | cite the band with sources, gate against upper region | INCONCLUSIVE stated | cherry-picking an edge |

---

*GOM12 · upgraded 2026-07-24 · one real question under the bookkeeping: does the ledger close —
and if it closes by construction, say that instead. The fence stays up either way.*
