# CH01 — The Covalent Bond as a Shared Electropause

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → **ACTIVE** on first gated run.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` — Law III occlusion, EMC04 electropause, Law V budget.
> **Prior audit (2026-06-27):** `ch01_covalent_bond.cpp` used `R=2a₀`, `Ry/2` with 35% PASS — prompt
> fidelity **F**. This prompt supersedes that path.

---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether the H₂ bond is a **genuine native consequence of two convergence
   wakes sharing one electropause** — i.e. whether root-finding the axial balance `F_in(R)=F_out(R)`
   from Law III occlusion + Law V budget, with **no orbital and no scaled-Bohr guess**, *lands* the
   measured `R_e = 0.741 Å` and `D_e = 4.478 eV` — or whether the only way to hit those numbers is to
   pre-set the answer (the superseded `R=2a₀`, `D_e=Ry/2` prototype, which missed by 43% / 52%).
2. **Why does it matter?** — This is the **root of the whole CH suite**: CH02 (transfer), CH03
   (valence), CH04 (VSEPR), CH05–CH07 all inherit "the bond = a shared electropause" from here. If the
   covalent bond is native, molecular chemistry follows with no wavefunctions; if it is only a fit,
   every downstream prompt is built on sand. It also closes the EMC04 electropause → molecule step.
3. **How will we find out?** — Five gated phases (§④): reproduce the single-atom electropause at `a₀`
   (P0 gate), **root-find the two-proton axial balance** with no `2a₀` shortcut (P1), integrate the
   well-depth difference for `D_e` (P2), and only then the VSEPR ladder (P3) and a novel angle (P4).
4. **What would prove us wrong?** — §⑧, with numeric kill-triggers: **no** sign change of `F_in−F_out`
   anywhere in 0.4–1.2 Å; a root that lands `R_e` off by >20%; a **negative or zero** `D_e` (anti-bound);
   or VSEPR angles that cannot be reproduced without importing hybridisation. Each can genuinely fire.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with **no repainting a fired test**
   and **no widening the committed 5% / 20% tolerances after the run**.

---

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The mechanism (shared electropause) and the *number* (`0.741 Å`, `4.478 eV`) must be kept apart. The
load-bearing derivation is **finding the crossing** `F_in(R)=F_out(R)` from independently-grounded
occlusion (Law III) and budget (Law V) forces — `R_e` is then *output*, not input. The trivial identity
to avoid is **importing the answer**: hard-coding `R_e=2a₀`, setting `D_e=Ry/2`, or tuning `f_overlap`
post-hoc so the root sits on 0.741 Å. **Importing the answer caps the grade at C** — it is the guess,
not the derivation. The `zk²=1` H-atom ground check (§③) is acknowledged as an **IDENTITY**, never a
PASS. The firewall: the P1 root-finder must not reference `2a₀` or `Ry/2` as the equilibrium; any such
reference is tagged `IMPORTED` and forfeits NATIVE.

---

## ① Executive Summary

EMC04: Bohr radius = **electropause** — inward convergence vs outward movement budget. **Question:** For
H₂, do two proton convergence wakes overlap so one shared electropause encloses the electron pair, with
`R_e` and `D_e` from **occlusion + budget balance** (no LCAO, no exchange integral)?

**Stakes:** If `F_in(R)=F_out(R)` crosses near 0.741 Å without orbital input, covalency is native. If
only `2a₀` scaling works, label **CONVERGENCE** not NATIVE.

---

## ② Physical Context

**Mechanism.** Internuclear region: combined inward occlusion push vs (a) mutual like-pair repulsion
(EMC03 surplus) and (b) electron dyad movement budget outward. Equilibrium `R_e` where net axial force
vanishes. `D_e` = work to separate shared surface back to two atomic electropauses.

**Variables:**

| Symbol | Meaning |
|--------|---------|
| `R` | Internuclear distance [m] |
| `F_in` | Inward convergence + binding occlusion |
| `F_out` | Outward repulsion + budget |
| `D_e` | Dissociation energy [eV] |
| `a₀` | Atomic electropause scale |

**Targets (OBSERVED-TARGET):** `R_e = 0.741 Å`, `D_e = 4.478 eV`; H₂O 104.5°, NH₃ 107°, CH₄ 109.5°.

**Forbidden:** MO/LCAO, hybridisation, ψ, exchange integrals, electron clouds.

---

## ③ Theoretical Framework

**Balance (commit in RUN_LOG before coding):**

```
F_in(R)  = (π/4) P_eff R_p² R_e² / R²   × f_overlap(R)   [Law III, two-proton geometry]
F_out(R) = F_rep(R) + F_budget(R)        [EMC03 surplus + Law V at shared dyad]
```

**Hypotheses:**
- **H1:** ∃ unique root `R_e` in [0.4, 1.2] Å.
- **H2:** `D_e = U_merged(R_e) − 2 U_atomic` from same potentials.
- **H3:** VSEPR angles from wake vector balance (Phase 3; lone/bond weight ratio = max CALIBRATED(1)).

**zk² = 1:** Verify H atom ground once — **IDENTITY**.

---

## ④ Investigation Strategy

### Phase 0 — Atomic electropause baseline (GATE)

- Reproduce single-H electropause at `a₀` from EMC04 relations (document which `P_eff`, radii).
- Success: `|r − a₀|/a₀ < 1%` for balance point.

### Phase 1 — H₂ root find (GATE — no `2a₀` shortcut)

- **Method:** Bracket `F_in − F_out` on [0.4, 1.2] Å; bisection or secant to |F| < 1e−12 N scale.
- **Success:** `|R_e − 0.741 Å|/0.741 Å < 0.05` (**5% committed** — not 35%).
- **Failure >5%:** PIVOT overlap factor `f_overlap`; if >20% → **OPEN**; forbidden: hardcode `2a₀`.

### Phase 2 — Bond energy

- Integrate or evaluate well depth difference.
- **Success:** `|D_e − 4.478|/4.478 < 0.20`, sign bound (D_e > 0).
- **Failure:** **OPEN** or CALIBRATED(1) on overlap only — document.

### Phase 3 — VSEPR wake balance (DEFER if Phase 1 OPEN)

- Unit vectors; lone weight `w_L`, bond `w_B`; minimise torque.
- **Success:** H₂O/NH₃/CH₄ within 3° with one `w_L/w_B` ratio (CALIBRATED(1) if used).

### Phase 4 — Novel falsifier

- Predict one angle/length **not** used in calibration (e.g. H₂S angle) — compare OBSERVED.

---

## ⑤ Success Criteria — dual verdict

| Prompt | Requirement |
|--------|-------------|
| **A** | Ph 1–4; R_e 5%; D_e 20%; VSEPR 3°; novel hit |
| **B** | Ph 1–2 PASS; Ph 3 DEFER |
| **C** | Root found but >5% R_e; honest OPEN |
| **D** | Qualitative only |
| **F** | `2a₀` / `Ry/2` without root find |

| Physics | Condition |
|---------|-----------|
| **NATIVE** | Ph 1–2 from occlusion/budget |
| **CONVERGENCE** | Scaling matches |
| **OPEN** | No root in bracket |

---

## ⑥ Outputs

1. `CH01_DERIVATION.md` — F_in, F_out definitions
2. `ch01_covalent_bond.cpp` — root finder + energy + optional VSEPR
3. `ch01_results.txt` — F vs R table around root
4. `RUN_LOG.md`
5. `CH01_VERDICT.md`

---

## ⑦ Dependencies

**Upstream:** EMC04, EMC03, PPT06/APS04 wakes, APS01 k-factors.
**Downstream:** CH04, ionic/metallic bonding.

---

## ⑧ Falsification Tests *(each states the numeric outcome that kills it)*

| ID | Test | SDT prediction (numeric) | Kill trigger — what FAIL looks like |
|----|------|--------------------------|-------------------------------------|
| T1 | Axial balance has a root | `F_in−F_out` changes sign exactly once in [0.4, 1.2] Å, at `R_e` within **5%** of 0.741 Å | **no** sign change anywhere in the bracket, OR the only root sits >20% off 0.741 Å ⇒ shared-electropause **KILLED/OPEN**, not a balance |
| T2 | Bond is bound, right depth | `D_e = U_merged(R_e) − 2U_atomic > 0`, within **20%** of 4.478 eV | `D_e ≤ 0` (anti-bound) ⇒ **KILL** the bind; `abs(D_e−4.478)/4.478 > 0.20` after f_overlap pivot ⇒ **OPEN** well depth |
| T3 | VSEPR ladder from one ratio | H₂O 104.5° / NH₃ 107° / CH₄ 109.5° to ≤3° with a single `w_L/w_B` (CALIBRATED(1)) | needs a *second* fitted knob, or only reproduces with sp³ hybridisation imported ⇒ **KILL H3**, angles are not wake-torque |
| T4 | Novel angle, not fit | predict an angle never used to set `w_L/w_B` (e.g. H₂S ≈ 92°) within a few ° | the model only reproduces the angles it was tuned on ⇒ fit-only, no predictive content (caps at C) |
| T5 | No imported answer (firewall) | `R_e` is the *output* of the root-find; code contains no `2a₀`/`Ry/2` equilibrium | if the only way to hit 0.741 Å is to seed `2a₀` ⇒ **IDENTITY-PASS**, grade capped at **C** |

---

## ⑨ Implementation Notes

- Plot `F_in − F_out` vs R in results (minimum 20 points).
- Use `law_III::F_occlusion` with documented radii — no G/M.
- Angstrom print, SI internal.
- Author attribution in all generated files: **J. C. Harvey, Melbourne.**

---

## ⑪ Questions This Opens *(generative — log new ones in `CH01_VERDICT.md`)*

Not required for the verdict; they are the payoff of doing it well.

1. **Is `R_e` a fixed fraction of `a₀`, or does it shift per element?** If the native crossing lands
   near `1.4 a₀` (not `2 a₀`) for H₂, is the same crossing-fraction predictive for the homonuclear
   series (Li₂, N₂, F₂), or does each need its own occlusion geometry? A universal fraction would be a
   strong NATIVE signal; a per-element fudge would not.
2. **What sets `f_overlap`?** Is the overlap factor a *derivable* geometric quantity (the fraction of
   each proton's convergence cone the other proton occludes) rather than a knob — and if so does CH01
   have *zero* calibrated parameters in the bond length/energy chain?
3. **Does the shared electropause have a measurable size?** If two protons share one pressure-balance
   surface, that surface has an extent — does it predict the H₂ bond *polarisability* or quadrupole that
   CH06 (van der Waals) and CH07 (spectra) then consume natively?
4. **Where does the singlet/triplet split come from with no spin postulate?** Bound H₂ vs anti-bound
   H₂ (the repulsive state) — is the difference a *handedness* of the two convergence wakes (EMC03
   surplus vs deficit, fore/aft pairing) rather than a Pauli/exchange term?
5. **Does the well curvature at `R_e` predict the CH07 vibration directly?** If `k = d²U/dR²|_{R_e}`
   from this same potential lands the CO/H₂ stretch frequency, then bond length, bond energy, and the
   IR line all fall out of one curve — one mechanism, three observables. CH07 should consume this `k`.

---

## ⑩ Adaptive Execution Protocol

### Pre-Run Commitments

```markdown
- R_e tolerance: 5% (NOT 35%)
- D_e tolerance: 20%
- CALIBRATED budget: 1 (w_L/w_B only, Phase 3)
- Bracket: [0.4, 1.2] Å
- Forbidden: 2a0 as R_e; Ry/2 as D_e without well integral
```

### Pivot table

| Trigger | PIVOT | If fail | Forbidden |
|---------|-------|---------|-----------|
| No sign change in bracket | Revise F_out; add EMC03 repulsion term | OPEN | Widen bracket post-hoc |
| R_e off 5–20% | Adjust f_overlap geometry (geometric, documented) | OPEN | RETRO-PASS at 35%; hardcode 2a₀ |
| D_e wrong sign | Fix integration limits | KILL H2 bind | Negative D_e PASS |
| VSEPR needs a 2nd knob (Phase 3) | re-examine lone vs bond wake weight from EMC03 | KILL H3; CH04 takes it over | sneak hybridisation in as the "ratio" |
| EMC04 overlap relation unavailable | DEFER P1 with dependency ID; finish P0 | — | fabricate f_overlap to hit 0.741 Å |

---

*CH01 · the bond is where the electropauses merge — find the crossing, don't guess 2a₀.*
