# EMC01: Transfer Function f — Mathematical Derivation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC · **§K-DEEPENED 2026-07-13** (300% rule, HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K · §0 anti-creep.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on any canon flag.
> **Run:** Pre-commit in `RUN_LOG.md`; four-root sort (§⑨.E) on every failure before the next phase.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Whether P_eff (hence f = P_eff/P_conv) is fitted-to-Coulomb or derivation basis-derived.** The engine currently labels it `calibrated-target` / class E (`laws.hpp:357,368,395`). This deepening shows the question **collapses to one dependency** (§2.RESOLUTION): *is R_p = (W+1)ℏ/(m_p c) accepted as derived?*
2. **Why does it matter?** — P_eff is the coefficient of the **universal** occlusion force (Coulomb, nuclear share it). If it is calibrated, every force magnitude in the repo inherits one fitted number; if it is derived, the atomic force sector is parameter-free (α only).
3. **How will we find out?** — Three routes (§④): A the derivation basis substitution + delete-test (the likely resolution); B the global shell-ratio (contaminated — see flag); C the electropause centripetal derivation (independent confirmation).
4. **What would prove us wrong?** — §⑧. If P_eff only lands Coulomb when R_p and r_e are taken as *measured* (not derivation basis-derived), it stays CALIBRATED honestly.
5. **How will we know we're done?** — Dual verdict. Class A only if P_eff = m_p²m_e²c⁵/(4παℏ³) is reached with **no measured length input** and survives the delete-test; then flag the engine labels (propose-only).

---

## 1. Definitions

| Symbol | Name | Value | Meaning |
|--------|------|-------|---------|
| P_conv | Convergence pressure | 2.459×10⁴⁸ Pa | isotropic relay pressure from N shells (Law I) |
| P_eff | Effective pressure | 5.225×10³¹ Pa | pressure in one EM interaction — **the number in question** |
| f | Transfer function | 2.123×10⁻¹⁷ | = P_eff/P_conv |
| α | Fine structure | 7.297×10⁻³ | **the ground-state gear v/c** (PPT02), not a "strength" |
| R_p | **Proton boundary radius** | 8.414×10⁻¹⁶ m | `laws.hpp:145` — **NOT "charge radius"** (literature obfuscation; feedback rule) |
| r_e | *(hist. "classical electron radius")* | 2.818×10⁻¹⁵ m | = **hydrogen koppa** αℏ/(m_e c); **not the electron's size** (see CANON_FLAGS #1) |
| R_CMB | Causal depth | 9.527×10²⁶ m | distance to the Clearing — **contaminated dependency** (§3 flag) |
| ℓ_P, ℏ, c, k_e, e | derivation basis / bridges | — | e = unit-bridge, not a charge substance (§ontology) |

> ### ⚠ LABEL FLAGS (in-prompt)
> (i) Prior §1 said *"Proton charge radius"* — **wrong**; `laws.hpp:145` already corrects this to *boundary
> radius*. Never "charge radius" (handed redirection, no charge substance). (ii) r_e is the hydrogen koppa,
> not the electron's radius (CANON_FLAGS #1). (iii) α is the gear v/c (PPT02), not a "coupling strength."

---

## 2. The Question, and its RESOLUTION to one dependency

The universal occlusion force (Law III): `F = (π/4) P_eff R₁² R₂² / r²`. For e–p Coulomb, the engine sets
`R_charge = √(R_p·r_e)` and *defines* P_eff by demanding `k_e e²/r² = (π/4)P_eff R_charge⁴/r²`, giving
`P_eff = 4 k_e e²/(π R_p² r_e²)` (`laws.hpp:354`). **As written, that is circular** (P_eff defined *by* Coulomb) — hence the `calibrated-target` label.

> ### ★ RESOLUTION (the trace-to-root this deepening contributes)
> The circularity **breaks** the moment R_p and r_e are replaced by their derivation basis forms. Substitute
> `k_e e² = αℏc`, `r_e = αℏ/(m_e c)`, and **`R_p = (W+1)ℏ/(m_p c) = 4ℏ/(m_p c)`** (the W+1 rule,
> `laws.hpp:1093`, 0.02% vs muonic-H):
> $$P_\text{eff}=\frac{4\alpha\hbar c}{\pi\,[4\hbar/(m_p c)]^2\,[\alpha\hbar/(m_e c)]^2}=\boxed{\frac{m_p^2 m_e^2 c^5}{4\pi\alpha\hbar^3}}$$
> **This is derivation basis-pure** — no measured length survives — and it is *identically* the electropause form
> (Route C). **So "is P_eff fitted?" = "is R_p = (W+1)ℏ/(m_p c) accepted as derived?"** — one dependency,
> traced to the W+1 conjecture (Law VI / PPT). If yes → **P_eff DERIVED**, and `laws.hpp:357/368/395`
> `calibrated-target`/class-E labels **understate** and should be re-graded (propose-only, CANON_FLAGS).

---

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| P_eff formula | `laws.hpp:354-362` | labeled `calibrated-target` — the thing to re-grade | ⚠ |
| f_transfer | `laws.hpp:365-372` | `circularity FAILS — inherits P_eff` | ⚠ |
| **R_p = (W+1)ℏ/(m_p c)** | `laws.hpp:1093` | **THE ROOT DEPENDENCY** (W+1 rule, 0.02%) | ✔ verify |
| r_e = αℏ/(m_e c) | `laws.hpp:144` | derivation basis (koppa; label flagged) | ✔ |
| k_e e² = αℏc | coulomb_identity | derivation basis identity | ✔ |
| P_conv → N, R_CMB, u_CMB | Law I / `cosmology.hpp` | **R_CMB CONTAMINATED** (Interchange flag #7: CR07-forbidden d(z)) | ⚠ dep |
| electropause centripetal derivation | (companion / memory) — verify on file | Route C confirmation | ⚠ verify |
| R_charge⁴ = (R_p r_e)² force form | `laws.hpp:406-408` | radius-typed handed force (Interchange flag #1) | ⚠ form |

---

## ④ Strategy — three routes

**Route A — derivation basis substitution + delete-test (primary).** Execute §2.RESOLUTION in code: build P_eff from `{α, ℏ, c, m_p, m_e}` via R_p=(W+1)ℏ/(m_pc); compare to `laws.hpp` P_eff. **Delete-test:** remove the Coulomb comparison entirely — does the constructed P_eff still equal 5.225×10³¹ Pa? If yes, it never consumed Coulomb → **DERIVED**. *Metric:* match to <0.1% (the 0.02% R_p residual sets the floor).

**Route B — Global shell-ratio (CONTAMINATED — run only to quantify the contamination).** `f = 4αℏcℓ_P/(π R_p² r_e² R_CMB u_CMB)`. This claims f is a local/global ratio. **But R_CMB = ln(1+z)/σ₀ rests on the compounding d(z) that CR07 forbids** (Interchange flag #7). *Do not* report this as a clean derivation; report it as a DEGENERATE/contaminated route pending the cosmology.hpp fix. Its role is to show f's "global" reading is downstream of an unresolved cosmology debt.

**Route C — Electropause centripetal (independent confirmation).** Derive P_eff from `F = m_e v²/a₀` (centripetal balance at the H ground state) inverted through the occlusion law — no Coulomb input. Verify on file (memory: delete-test passes). If A and C agree, P_eff is doubly independent of Coulomb.

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | P_eff from derivation basis (Route A) = engine P_eff <0.1% | root-2 (R_p W+1 dependency) |
| T2 | delete-test: P_eff stands without Coulomb comparison | root-1 (genuinely circular) → stays CALIBRATED |
| T3 | Route C electropause = Route A form | root-1 if they disagree |
| T4 | f's global reading independent of R_CMB | root-2 (cosmology.hpp d(z), flag #7) — expected FAIL, quantify it |
| T5 | handed force is count×unit-area, not R_charge⁴ | root-3 (form) — for Z=1 harmless, flag the form (Interchange #1) |

## ⑨.E Four-root sort
root-1 claim false (P_eff truly circular → CALIBRATED stands) · root-2 dependency (R_p W+1 rule; R_CMB d(z)) · root-3 prompt/form under-specified (R_charge⁴ vs count×area) · root-4 gate contraband. Log per failure; link R_CMB→cosmology.hpp root once in STACK.

## Brainstorm — overlooked factors
- **The whole EMC01 question may already be answered** — Route A + C likely resolve P_eff to DERIVED. If so, EMC01's deliverable is *re-grading the engine labels*, not new physics. Say so honestly.
- **G (§ old ⑤) leans on the same R_CMB / S_boundary = 4πN²** as the contaminated f-route. The "vacuum catastrophe resolved by shell cancellation" and "G within 5×" both inherit flag #7. Do **not** claim the G-recovery is clean until cosmology.hpp's d(z) is fixed.
- **Handed force form.** R_charge⁴ = (R_p r_e)² is the radius-typed force the Interchange sweep flagged (laws.hpp:412-417, Z² bug at He). For e–p (Z=1) it gives the right answer, but the *form* is contraband — a handed force is count×unit-area. Note it; the bug bites nuclear, not this Z=1 case.
- **α is the gear** (PPT02): P_eff ∝ 1/α means the interaction pressure scales inversely with the ground gear — worth a movement sentence in the verdict.

## ⑤ Success / ⑥ Outputs
Class A: P_eff derivation basis-derived, delete-test passes, Routes A≡C; engine labels flagged for re-grade. Class C: derived modulo the W+1 R_p residual (documented). **Honest floor:** P_eff resolution shown to hinge on the W+1 rule; f's global reading flagged as cosmology-contaminated. Outputs: `RUN_LOG.md`, `emc01_peff_routes.cpp`, `EMC01_DERIVATION.md`, `EMC01_VERDICT.md`, CANON_FLAGS rows.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — EMC01 (§K-deepened)
- Prompt completion target: [A|B|C]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE]
- CALIBRATED budget: 0 (resolving whether P_eff is calibrated, not adding one)
- Routes this session: A (derivation basis+delete-test) · C (electropause) · B (contamination quantify)
- Root dependency to verify on file: R_p = (W+1)ℏ/(m_p c), laws.hpp:1093
- Contamination to flag: R_CMB via cosmology.hpp compounding d(z) (Interchange #7)
- Forbidden: define P_eff by Coulomb then call it derived; report R_CMB-route as clean; edit engine labels
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| Route A needs measured R_p to land | check W+1 R_p residual; if >0.1% flag | CALIBRATED stands (root-1) | call it derived anyway |
| Route B rides R_CMB | label DEGENERATE/contaminated, cite flag #7 | — | report as clean derivation |
| A and C disagree | trace algebra (root-1/3) | OPEN, name the gap | average them |
| delete-test fails | P_eff genuinely circular | **CALIBRATED**, honest | RETRO-PASS the test |

**Disallowed:** define-by-Coulomb-then-call-derived · R_CMB route as clean · post-hoc tolerance widening · editing `laws.hpp` labels (flag only).

---

*EMC01 · §K-deepened 2026-07-13 · the fitted-vs-derived question collapses to the W+1 R_p rule; f's global reading is cosmology-contaminated; label flags routed to CANON_FLAGS.*
