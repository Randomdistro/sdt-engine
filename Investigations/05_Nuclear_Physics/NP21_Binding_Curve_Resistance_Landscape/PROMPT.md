# NP21: The Binding Curve as a Resistance Landscape (iron at the floor) — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether the **entire** binding-energy-per-nucleon curve is a single **resistance landscape** in the NP19 sense — and, the decisive sub-question, whether the **location of its floor (the iron peak, A≈56–62, maximum binding / minimum mass-per-nucleon)** falls out of the alpha-grammar + packing **geometry** *without a fitted exponent*, or only by tuning a power law.
2. **Why does it matter?** — NP19 named the unit of account (mass defect = resistance difference `ΔR`). NP21 is the **map**: it asks whether that one statement, applied across the chart of nuclides, reproduces the most famous curve in nuclear physics *and* pins iron as the form the medium resists least. If the floor is **derived**, SDT replaces all of nuclear energy-accounting with one geometric statement (*most-bound = least-resistance = easiest form to hold*). It is the direct upstream of **SAR05** (why fusion stops being exothermic at the floor). Stack position: Tier 4.
3. **How will we find out?** — Four gated phases (§④): (P1) define the **resistance functional** `R̃(Z,A)` from grammar + packing geometry, declaring every input geometric vs fitted **before** running; (P2) reproduce the **qualitative shape** (rise to iron, fall after) as a one-parameter landscape against a pre-committed shape metric; (P3) the decisive test — **derive the floor location** from geometry, pre-commit "floor within ±2 in A of the Fe/Ni region with **no tuned exponent**" for a real PASS; (P4) cross-check Fe-56 vs Ni-62 ordering against NP13.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers: floor lands far from iron → **KILL** the geometric-floor claim; the only way to place the floor at iron is a **fitted exponent** → downgrade to **CALIBRATED / Class C** and *say so*; landscape can't even reproduce rise-then-fall → **OPEN**.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). **Honest bar, stated up front:** the *strong* outcome (iron floor **DERIVED**, no fitted exponent) is the only Class-A/NATIVE result; a fitted-exponent reproduction is **only Class C / CALIBRATED**, and we will label it so without flinching.

---

## 1. Executive Summary (100–150 words)

Standard physics draws the binding-energy-per-nucleon curve, peaks it at iron, and *tabulates* the rest as separate semi-empirical energy terms (volume, surface, Coulomb, asymmetry, pairing). **SDT (via NP19) asserts a single statement instead: every mass defect is a form-resistance difference `ΔR`, so the whole curve is one RESISTANCE LANDSCAPE.** The neutron (heavier-when-bound, flipped-sign defect) and the deuteron (lighter-when-bound) are both `ΔR`; this investigation generalises that across the chart of nuclides. The one geometric statement: **most-bound = least-resistance = easiest form to hold**, and the **iron peak is the FLOOR of the landscape — the deepest relaxation**. We test whether the alpha grammar (`n_t=A−2Z`, `n_d=3Z−A−2`) plus packing geometry (`packing.hpp`: Fe-56 = cuboctahedron + interstitial neutrons) **derives** the floor at A≈56–62 with **no tuned exponent**. Expected ceiling honestly: shape reproducible; floor-from-geometry is the hard bar, and a fitted exponent is only Class C.

## 2. Physical Context (250–400 words)

**Plain-language picture.** Picture the substrate as a single reconfigurable medium and each nuclide as a *knotted form* the medium must hold. NP19 established that the medium's *grip* on a form is its mass, and that a mass defect is a **resistance difference** between two forms — not stored binding-energy in a reservoir. Now lay all the forms out side by side, light to heavy, and read off how hard each is to hold *per nucleon*. That ordering **is** the binding curve, read upside-down: where the curve peaks (maximum binding per nucleon), the medium resists *least*; that point is a **valley floor in resistance**. Empirically the floor sits at iron–nickel (A≈56–62). The question is whether the *geometry of how the grammar pieces pack* puts the floor there on its own.

**Why iron is special, geometrically (the claim to test, not yet derived — say so plainly).** In the alpha grammar every nuclide is `1 alpha-seed + n_d deuterons + n_t tritons`. As `A` grows, the count of pieces that can pack into a **closed, symmetric, low-frustration shell** rises, then the geometry runs out of clean seats and frustration (surface, Coulomb spread, triton excess) grows again. `packing.hpp` already names Fe-56 as a **cuboctahedron (Vector Equilibrium) + interstitial neutron plugs** — a maximally even, zero-strain kissing configuration. The conjecture is that this *geometric* turning point coincides with the resistance floor.

**Key variables / symbols (define once, carry through):**
| Symbol | Meaning | Dimension |
|--------|---------|-----------|
| `B/A(Z,A)` | measured binding energy per nucleon (the curve we must reproduce) | [MeV] (OBSERVED-TARGET) |
| `R̃(Z,A)` | SDT **resistance functional** per nucleon (the landscape value) | [dimensionless or MeV — fixed in P1] |
| `floor` | the `(Z,A)` minimising `R̃` (deepest relaxation = most-bound) | — |
| `n_d, n_t` | grammar deuteron / triton counts (`3Z−A−2`, `A−2Z`) | integer |
| `σ` | grammar symmetry `|n_d−n_t|/(n_d+n_t)` (NP13) | dimensionless |
| `f_geom` | packing fill / coordination metric from `packing.hpp` | dimensionless |
| `p` | **any** exponent in a power law — flagged geometric **or** fitted | — |

**Connection to the rest of SDT.** Upstream: **NP19** (resistance unit of account, the reframe this generalises), **NP13** (Fe-56 vs Ni-62 grammar efficiency), `nuclear.hpp` (`alpha_grammar`), `packing.hpp` (Fe-56 cuboctahedron + plugs). Downstream: **SAR05** consumes the floor to explain why fusion stops being exothermic there. Sibling FLM11 supplies the tape-measure caution: the property you read depends on the ruler — here, *don't let a fitted exponent masquerade as a geometric one.*

## 3. Theoretical Framework (400–600 words)

**Axiom inherited from NP19 (the unit of account).** `R(form) ≡ m(form) c²` — a form's rest energy *is* its accumulated form-resistance (Law IV read as resistance, shown constant-free in NP19 P1). A mass defect is `ΔR = R(constituents) − R(bound)`; the **binding energy per nucleon** is therefore the *per-nucleon resistance relief* of assembling the form:

> `B/A(Z,A) = [ Z·R(p) + (A−Z)·R(n) − R(nuclide) ] / A`  (all `R = m c²`, measured masses).

This is **identity-level** for the *measured* curve — it is just `B/A` rewritten in resistance language. **It is NOT the test.** The test is whether an **SDT-side functional `R̃(Z,A)` built from grammar + packing geometry** *reproduces the shape and locates the floor* without importing the measured `B/A`.

**Building `R̃` from geometry (the part that must be honest).** The grammar gives, for each `(Z,A)`, an exact piece inventory `(1, n_d, n_t)`. Packing geometry gives how those pieces seat:
- a **bulk / volume** relief that grows with the number of seated pieces (more interior bonds shared);
- a **surface / frustration** penalty that grows where the shell is unclosed or strained (`packing.hpp` coordination deficit);
- a **handed-redirection spread** penalty rising with `Z` (the proton forms' mutual redirection over the form — *never* "Coulomb charge substance"; it is the ℓ=1 handed-redirection term of the occlusion law);
- an **asymmetry / triton-excess** penalty rising with grammar asymmetry `σ = |n_d−n_t|/(n_d+n_t)` (NP13).

`R̃(Z,A)` is some combination of these. **CRUCIAL, STANDING CAUTION (from prior grammar work): a FITTED exponent is NOT a derived one.** Any power `p` (surface `∝ A^{2/3}`, spread `∝ Z²/A^{1/3}`, etc.) must be **declared geometric or fitted in P1, before any run.** A `2/3` that comes from "surface area of a packed sphere" is geometric; a `0.71` chosen to land the floor on iron is fitted — and if the floor *only* lands on iron with a fitted exponent, the result is **Class C / CALIBRATED**, full stop. Hold every power law loosely until its exponent comes from geometry.

**The floor as a derived prediction.** The decisive object is `argmin_{(Z,A)} R̃ / A`. If, with **only geometric exponents**, that argmin lands within ±2 in `A` of the Fe/Ni region (A≈56–62), the geometric-floor claim is **DERIVED**. The mechanism narrative: bulk relief saturates as the cuboctahedral shell closes; spread + asymmetry penalties take over beyond it; the crossover **is** iron.

**Constraints (whitelist only).** Inputs limited to `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured masses and the measured `B/A` curve **as an OBSERVED-TARGET anchor only** (AME2020). Use the curve's *data* (Fe-56/Ni-62 near the maximum) as the anchor; **never** import the semi-empirical-mass-formula *story* (its five fitted terms) into the SDT chain — at most it appears as an OBSERVED comparison column. **Prohibited:** G/M/GM, wavefunctions, fields-as-primitives, quarks/gluons, virtual particles as objects, dark matter/energy, ΛCDM, duality, and the liquid-drop/SEMF fitted coefficients as inputs. Never write "charge radius" or treat charge as a substance (use "handed redirection"; `e` = unit-bridge).

## 4. Investigation Strategy (800–1200 words — be excessive)

This investigation is **half geometry, half discipline**. The tool exists to make the landscape and the floor-location *mechanical and falsifiable*, and — above all — to keep the **geometric-vs-fitted ledger of every exponent** loud and explicit. Four gated phases. The pre-commitment that matters most is in **P1**: *every exponent is declared geometric or fitted before P2 runs, and that declaration is frozen.*

---

### Phase 1 — Define the resistance functional `R̃(Z,A)`; freeze the exponent ledger (2–3 h)

**Goal.** Write `R̃(Z,A)` as an explicit function of the grammar inventory `(1, n_d, n_t)` and packing metrics, with **every symbol's dimension stated** and **every exponent tagged `GEOMETRIC` or `FITTED` before any fit or floor-search is run.** This phase produces the *frozen contract* the rest of the investigation is judged against.

**Method.**
1. From `nuclear.hpp::alpha_grammar(Z,A)` pull `(n_d, n_t)` for every alpha-valid nuclide; from `packing.hpp` pull the coordination / fill metric for the relevant shell configs (tetrahedron→He-4, octahedron→O-16, cube→Ca-40, cuboctahedron→Fe-56, cuboct+plugs→Fe-56 full). Define `f_geom(Z,A)` = a coordination/closure score (fraction of pieces in a closed low-frustration shell).
2. Propose the functional form, e.g.
   `R̃/A = − a_V·(bulk relief) + a_S·(surface)·A^{−1/3} + a_C·(handed-redirection spread)·Z(Z−1)/A^{4/3} + a_A·σ`
   — but **the literal terms are placeholders; the binding contract is the EXPONENT TABLE**:

   | Term | Exponent(s) | Source | Tag |
   |------|-------------|--------|-----|
   | bulk relief | `A^{1}` (count of interior bonds) | combinatorial geometry | `GEOMETRIC` (justify) |
   | surface | `A^{2/3}` → per-nucleon `A^{−1/3}` | area of a packed sphere | `GEOMETRIC` (justify) or `FITTED` |
   | handed-redirection spread | `Z(Z−1)/A^{1/3}` | pair count / shell radius | `GEOMETRIC` (justify) or `FITTED` |
   | asymmetry | `σ¹` or `(n_t−n_d)²/A` | grammar (NP13) | `GEOMETRIC` (justify) or `FITTED` |

3. **DECLARE, in `RUN_LOG.md`, before P2:** which exponents are geometric (with a one-line geometric justification each) and which (if any) are fitted. The coefficients `a_V,a_S,a_C,a_A` are *scale weights* — at most **ONE** may be CALIBRATED (the overall units/scale); the rest must be ratios fixed by geometry, **or** the whole result is Class C.

**Pre-committed success metric.** A written functional with **every exponent tagged**, dimensions consistent, grammar + packing pulled from the engine (no local re-derivation of grammar), and a frozen exponent table in `RUN_LOG.md`. **Zero** exponents left untagged.

**Failure trigger.** Any exponent that cannot be given a geometric justification *and* is needed to fit → it is `FITTED`; record it as such (it caps the result at Class C). If **more than one** coefficient must be free to even get a sane scale → **PIVOT** to a stricter form or accept Class C.

**Gate.** No P2 until the exponent ledger is frozen and copied into `RUN_LOG.md`.
**Out of scope.** Locating the floor (P3); reproducing absolute MeV values (only shape matters until P3).

---

### Phase 2 — Reproduce the curve SHAPE as a one-parameter landscape (2–3 h)

**Goal.** Show `R̃/A` reproduces the **qualitative shape** of the measured `B/A` curve: a rise to the iron region then a fall, with the correct curvature sign — using the **frozen P1 form**, with at most the one CALIBRATED scale weight.

**Method.**
1. Evaluate `R̃/A` over all alpha-valid stable nuclides (`Z=2…83`). Plot against `A` (and against `Z`). The landscape is "binding-like" if `−R̃/A` rises then falls.
2. **Pre-commit a shape metric (before plotting):**
   - (a) `−R̃/A` is **monotone increasing** up to `Z≈26` (within a small tolerance of local grammar wiggle — allow ≤3 non-monotone steps from odd/even pairing), then **monotone decreasing** to `Z=83`;
   - (b) the **curvature sign** is correct (concave-down, single broad maximum);
   - (c) Spearman rank correlation between `−R̃/A` and measured `B/A` across all nuclides `> 0.85`.
3. Hold the one scale weight to map `R̃` units onto MeV *only for plotting overlay* — this is a unit map, not a shape fit; the shape must already be right before scaling.

**Pre-committed success metric.** Shape metric (a)+(b) satisfied AND Spearman `> 0.85`. (If Spearman `0.6–0.85`: PARTIAL → P3 may proceed but Class is capped at C/D.)

**Failure trigger.** No rise-then-fall (monotone, or multiple peaks, or wrong curvature) → the landscape can't reproduce the curve → **OPEN** (per §⑧ T3); do **not** start adding fitted exponents to force a shape (that converts an OPEN into a CALIBRATED masquerade).

**Gate.** No P3 until rise-then-fall + Spearman gate met (or PARTIAL explicitly logged).
**Out of scope.** The *exact* peak location (that is P3, the decisive test); absolute MeV accuracy of every point.

---

### Phase 3 — DERIVE the floor location (the decisive test) (3–4 h)

**Goal.** Compute `argmin_{(Z,A)} R̃/A` (equivalently `argmax(−R̃/A)`) and test whether it lands on iron — **using only the geometric exponents frozen in P1, with no exponent tuned to place the floor.**

**Method.**
1. With the P1 functional and frozen exponents, scan all alpha-valid nuclides; record the `(Z,A)` of the deepest relaxation (the floor) and the runner-up.
2. **Pre-committed PASS condition (the bar):** floor `A` is within **±2** of the Fe/Ni region (target window A∈[54,64], centred on Fe-56/Ni-62) **AND no exponent was tuned to achieve it** (verified against the frozen P1 ledger; the floor search must run *after* exponents are locked).
3. **The honesty fork (run this explicitly):** re-run the floor search while *perturbing each FITTED exponent (if any) off its value*. If the floor stays on iron under reasonable geometric exponents → robust, candidate **DERIVED**. If the floor lands on iron *only* for a narrow tuned exponent → it is **fitted**; the result is **CALIBRATED / Class C** and must be labelled so.
4. Print the full `R̃/A` profile near the floor (A=48…70) so the reader sees how sharp/flat the minimum is.

**Pre-committed success metric.**
- **Strong (Class A / NATIVE):** floor within ±2 in A of Fe/Ni, **zero tuned exponents**, robust under exponent perturbation.
- **Class C / CALIBRATED:** floor on iron but **only** with a fitted exponent (documented, one CALIBRATED tag).
- **KILL:** floor more than ±2 in A *and* off the iron region with all-geometric exponents AND cannot be brought to iron except by an exponent so contrived it has no geometric reading.

**Failure trigger.** Floor far from iron with geometric exponents → **KILL** the geometric-floor claim (§⑧ T1). Floor on iron only via fitted exponent → **downgrade to CALIBRATED / Class C**, say so in the verdict (§⑧ T2) — do **not** retro-relabel the fitted exponent as geometric.

**Gate.** Verdict class is set primarily by this phase. No retro-PASS: if it lands as C, it ships as C.
**Out of scope.** Explaining *why fusion stops being exothermic* at the floor — that is **SAR05** downstream.

---

### Phase 4 — Cross-check Fe-56 vs Ni-62 ordering against NP13 (1–2 h)

**Goal.** Confirm the landscape's fine ordering near the floor is consistent with NP13's grammar-efficiency finding (Fe-56 more symmetric, Ni-62 higher measured `B/A`).

**Method.**
1. Evaluate `R̃/A` and `σ` for Fe-56 (`5α+6d+6t`, `σ=0`) and Ni-62 (`5α+6d+9t`, `σ=0.2`).
2. Report which the landscape places lower (deeper relaxation). Note the measured tension: Ni-62 has higher `B/A` (8.795 vs 8.790 MeV/n) yet Fe-56 is more abundant / more grammar-symmetric.
3. State, without fudging, whether `R̃` reproduces the measured `B/A` ordering (Ni-62 deeper) **or** the symmetry ordering (Fe-56 favoured), and reconcile with NP13: abundance follows symmetry, depth-of-binding follows `B/A`; the landscape should not be forced to satisfy both with one knob.

**Pre-committed success metric.** Fe-56 and Ni-62 both within ±2 of the floor in the `R̃/A` profile, and the predicted ordering **stated and compared** to both measured `B/A` and NP13 symmetry — no post-hoc reweighting to match.

**Failure trigger.** If `R̃` can only match the Fe/Ni ordering by re-tuning a coefficient already frozen in P1 → that is a frozen-contract violation; log it as **OPEN**, do not re-tune.

**Gate.** Final verdict after P1–P4 gated.
**Out of scope.** Resolving the Fe-56/Ni-62 abundance physics (NP13 owns it); SAR05's exothermicity argument.

---

**Global pre-commitments.** Strong ceiling **A / NATIVE** *only if* the floor is geometric (no tuned exponent); realistic ceiling **C / CALIBRATED** if a fitted exponent is needed. CALIBRATED budget **≤1** (one overall scale weight; any exponent fit pushes to Class C and is documented). All grammar from `nuclear.hpp`, all geometry from `packing.hpp`, all masses/curve from `measured::` + AME2020 OBSERVED-TARGET. Any phase failure → PIVOT/KILL/OPEN, never RETRO-PASS.

## 5. Success Criteria (200–300 words)

Use canonical labels. **Dual verdict required** (prompt completion A–F × physics class).

✅ **PASS (Class A: Derived — the hard bar).** All four phases gated. `R̃(Z,A)` built from grammar + packing with **every exponent geometric** (P1 ledger). Shape reproduced: rise-then-fall, correct curvature, Spearman `>0.85` (P2). **Floor DERIVED within ±2 in A of Fe/Ni with NO tuned exponent and robust under exponent perturbation** (P3). Fe-56/Ni-62 ordering consistent with NP13 (P4). **What we publish:** the binding curve as one geometric resistance landscape with iron at the floor, derived — replacing nuclear energy-accounting with one statement.

⚠️ **QUALIFIED (Class C: Convergence / CALIBRATED).** Shape reproduced and floor lands on iron, **but only with a fitted exponent** (one CALIBRATED tag, documented). This is the *honest* likely outcome and we **say so**: a fitted-exponent reproduction is NOT a derivation. Ship the landscape; flag the un-derived exponent for future geometric work.

⚠️ **QUALIFIED PENDING (Class D: Computed).** Shape reproduced (P2) but floor is off iron by >±2 with geometric exponents, or P3 robustness untested. Useful as a landscape sketch; floor claim not established.

❌ **FAIL / KILL (Class F).** Floor lands far from iron and cannot be brought there except by a contrived, un-geometric exponent → **KILL** the geometric-floor claim. Or: landscape cannot reproduce rise-then-fall at all → **OPEN** the functional form. Record numbers in `NP21_VERDICT.md` and `INVESTIGATION_STACK.md`; do **not** rescue with a fit.

**Forbidden at every level:** RETRO-PASS (widening the ±2 floor window or the Spearman gate after seeing the result), PLUG (tuning an exponent to place the floor then calling it geometric), IDENTITY-PASS (using the measured `B/A` *as* `R̃` and calling the floor predicted), BORROW-SMUGGLE (SEMF fitted coefficients, G/M/GM, quarks, ψ into the chain).

## 6. Outputs (150–300 words)

All written into `Investigations/05_Nuclear_Physics/NP21_Binding_Curve_Resistance_Landscape/`. **Edit no existing file; never touch `Engine/include/sdt/` or `Laws/`.**

1. **`NP21_DERIVATION.md`** — the analytic spine: NP19 `R(form)≡mc²` → per-nucleon resistance relief = `B/A` (identity); the **geometric functional `R̃(Z,A)`** from grammar + packing with the **frozen exponent ledger** (each exponent `GEOMETRIC`/`FITTED` with one-line justification); the floor-as-argmin argument; the Fe-56 cuboctahedron closure narrative; the Fe-56/Ni-62 ↔ NP13 reconciliation. Each step flagged `DERIVED` / `ASSUMED` / `IDENTITY` / `CALIBRATED(n)` / `OBSERVED-TARGET`.
2. **`np21_landscape.cpp`** (or `np21_landscape.py`) — standalone tool: `#include <sdt/laws.hpp>` (C++), uses `nuclear.hpp::alpha_grammar` and `packing.hpp` metrics. Prints, **per nuclide**: `(Z,A)`, `(n_d,n_t)`, `σ`, `f_geom`, `R̃/A`, and the measured `B/A` (OBSERVED-TARGET column). Prints the **derived floor location** `argmin R̃/A`, the curve-shape check (monotone-up-to-Z≈26 / down-after, Spearman), and the exponent-perturbation robustness result. Build line in a header comment: `cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:np21.exe np21_landscape.cpp` (or `g++ -std=c++20 -IEngine/include …`).
3. **`NP21_results.csv`** — one row per nuclide: `Z,A,n_d,n_t,sigma,f_geom,R_tilde_per_A,BA_measured`, plus a trailer summarising floor `(Z,A)`, Spearman, and exponent tags.
4. **`NP21_VERDICT.md`** — dual verdict header (prompt completion A–F × physics class), filled falsification table (§⑧), explicit class call (A only if floor geometric; else C/CALIBRATED honestly).
5. **`RUN_LOG.md`** — **mandatory**: Pre-Run Commitment Block (§⑩) filled before coding — *including the frozen exponent ledger* — then ADJ-### entries and phase gates per `PROMPT_EXECUTION_PROTOCOL.md`.

## 7. Dependencies & References (150–250 words)

**Upstream (required first):**
- **NP19** (Mass-Defect as Form-Resistance) — supplies the unit of account `ΔR` and the flipped-sign neutron; NP21 *is* NP19 generalised across the chart.
- **NP13** (Fe-56 vs Ni-62 Grammar Efficiency) — supplies the symmetry metric `σ=|n_d−n_t|/(n_d+n_t)` and the abundance-vs-`B/A` tension checked in P4.
- `nuclear.hpp` (`alpha_grammar`: `n_d=3Z−A−2`, `n_t=A−2Z`) — the exact piece inventory; do **not** re-derive locally.
- `packing.hpp` (Fe-56 = cuboctahedron + interstitial neutron plugs; coordination/closure metrics) — the geometry of how pieces seat.
- `measured::` masses + AME2020 `B/A` curve (OBSERVED-TARGET anchor only).

**Downstream (blocked until this resolves):**
- **SAR05** (provenance: why fusion stops being exothermic at the floor) — consumes NP21's derived floor as its starting point.

**Related (read in parallel):**
- **FLM11** (tape-measure principle) — the standing caution against a fitted exponent reading as geometric.
- Sibling set (same 9-investigation batch): **NP18** (Be-7 BEC flux resonator), **NP20** (neutron from one seat), **PPT10** (straight light), **PPT11** (oscillation), **APS06** (emission ladder), **SAR05** (provenance).
- **ATOMICUS `rules/On the Nature of Atomicus Rules.md`** — the grammar constitution (`n_t,n_d`, alternate He-3 grammar).

## 8. Falsification Tests (150–250 words)

| Test | Hypothesis | Predicted Outcome | If FAIL |
|------|-----------|-------------------|---------|
| **T1 (floor location — the crux)** | Geometry alone puts the floor at iron | `argmin R̃/A` within ±2 in A of Fe/Ni with all-geometric exponents | Floor far from iron → **KILL** the geometric-floor claim; record `(Z,A)` and the gap |
| **T2 (no fitted exponent)** | The floor is geometric, not tuned | Floor stays on iron under exponent perturbation; **0** exponents fitted | Floor on iron *only* via a tuned exponent → **downgrade to CALIBRATED / Class C**, label it; do not call it derived |
| **T3 (shape)** | The landscape reproduces rise-then-fall | Monotone-up to `Z≈26`, down after; concave-down; Spearman `>0.85` | No rise-then-fall / wrong curvature / Spearman `<0.6` → **OPEN** the functional form; do not force-fit a shape |
| **T4 (Fe/Ni ordering)** | Fine ordering consistent with NP13 | Both within ±2 of floor; predicted ordering stated vs measured `B/A` & σ | Match only by re-tuning a frozen coefficient → **OPEN** (frozen-contract violation), do not re-tune |
| **T5 (no SEMF smuggle)** | The landscape uses no semi-empirical-mass-formula fitted terms | All exponents geometric or one documented fit; SEMF only as OBSERVED column | A SEMF coefficient enters the SDT chain → **audit fail**; strip it, re-run |

**Recovery:** T1 is a hard KILL of the *geometric-floor* claim (the landscape-as-concept may still be Class C). T2 is the calibration fork — *honesty, not failure*: ship as C and say so. T3 is an OPEN. T4/T5 are OPEN / audit-fail. Never RETRO-PASS the ±2 window, the Spearman gate, or relabel a fitted exponent as geometric after the run.

## 9. Implementation Notes (200–300 words)

- **Tool is a checker, not a fitter.** `np21_landscape` evaluates the **frozen P1 functional** and *reports* the floor; it must not contain an optimiser that tunes exponents to place the floor. If you fit, fit **one** scale weight only, and flag the run CALIBRATED. The exponent-perturbation robustness check (P3) should be a simple loop over ±10–20% on each exponent, printing where the floor moves.
- **Grammar + geometry from the engine.** Pull `(n_d,n_t)` from `nuclear.hpp::alpha_grammar` and coordination/closure from `packing.hpp` — do not hardcode either (§0 anti-creep). Iterate only over alpha-valid nuclides (`2Z ≤ A ≤ 3Z−2`).
- **Shape before scale.** Compute the Spearman rank correlation between `−R̃/A` and measured `B/A` *before* applying any MeV scale weight — rank correlation is scale-invariant, so a good shape is provable with zero calibration.
- **Numerical care.** `R̃/A` near the floor is flat; print the profile A=48…70 to several sig figs so the argmin is unambiguous (and to expose a flat/degenerate minimum honestly rather than reporting a noise-driven `(Z,A)`).
- **Exponent ledger discipline.** Every power in the functional carries a tag in code comments and in `NP21_results.csv` trailer: `GEOMETRIC(justification)` or `FITTED`. This is the single most important output — the whole verdict turns on it.
- **Prose discipline.** Never write "charge radius"; the proton-form spread is **handed redirection** (`e` = unit-bridge), the ℓ=1 term of the occlusion law. Keep the SEMF/liquid-drop *story* out of the chain; the measured `B/A` curve is an anchor (its *data*), not a model to import. Anchor on Fe-56/Ni-62 *data*, never the SM narrative of "iron peak from Coulomb vs surface".
- **Visualisation hint (optional):** overlay `−R̃/A` (scaled) on measured `B/A` vs A; mark the derived floor and the Fe/Ni window — the test passes or fails at a glance.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP21
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE if floor geometric | CONVERGENCE/CALIBRATED if exponent fitted]  # honest fork stated up front
- CALIBRATED budget: ≤1 (one overall scale weight ONLY; any fitted EXPONENT pushes result to Class C and is documented)
- Engine namespaces: measured (m_e,m_p,m_n,c,MeV_to_J), nuclear (alpha_grammar), packing (coordination/closure)
- FROZEN EXPONENT LEDGER (fill BEFORE P2 runs — this is the binding contract):
    bulk relief    : exponent = ____  tag = [GEOMETRIC: __justify__ | FITTED]
    surface        : exponent = ____  tag = [GEOMETRIC: __justify__ | FITTED]
    spread (ℓ=1)   : exponent = ____  tag = [GEOMETRIC: __justify__ | FITTED]
    asymmetry σ    : exponent = ____  tag = [GEOMETRIC: __justify__ | FITTED]
- Phase thresholds (committed before run):
    P1: every exponent tagged; ≤1 free coefficient; grammar+packing from engine; ledger frozen in RUN_LOG
    P2: rise-to-Z≈26 then fall (≤3 non-monotone steps); concave-down single peak; Spearman(−R̃/A, B/A) > 0.85
    P3: floor argmin within ±2 in A of Fe/Ni [54,64]; STRONG only if 0 fitted exponents + robust under ±10–20% perturbation
    P4: Fe-56 & Ni-62 both within ±2 of floor; ordering stated vs measured B/A and σ; no re-tune of frozen coeffs
- Forbidden retroactive changes: widen the ±2 floor window or Spearman gate post-run; relabel a FITTED exponent
  as GEOMETRIC after seeing the floor; tune an exponent to place the floor then call it derived; use measured B/A
  as R̃ (IDENTITY-PASS); import SEMF fitted coefficients / G / M / GM / quarks / ψ into the chain; write "charge radius"
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric) | PIVOT (first response) | If pivot fails | Forbidden |
|-------------------|------------------------|----------------|-----------|
| P1: an exponent has no geometric justification but is needed | Tag it `FITTED`; cap result at Class C; keep going honestly | Two+ exponents fitted → **OPEN** form | Call it geometric to keep Class A |
| P1: grammar/packing not pulled from engine | Fix includes; use `alpha_grammar`/`packing.hpp` | STOP — report blocker | Re-derive grammar locally |
| P2: no rise-then-fall / wrong curvature | Try the next native term ordering listed in §④ (bulk vs surface balance) — *not* a new fitted exponent | **OPEN** the functional (T3) | Add a fitted exponent to force the shape |
| P2: Spearman 0.6–0.85 | Log PARTIAL; proceed to P3 with Class capped at C/D | — | Widen the 0.85 gate post-run |
| **P3: floor far from iron (all-geometric)** | Re-check `f_geom` closure metric / packing config mapping | **KILL** geometric-floor claim (T1); record `(Z,A)` | RETRO-widen the ±2 window |
| **P3: floor on iron only via tuned exponent** | Mark exponent `FITTED`; **downgrade to CALIBRATED / Class C** and say so | — | Relabel the exponent GEOMETRIC |
| P3: minimum is flat/degenerate (noise-driven argmin) | Print profile A=48…70; report flat-minimum honestly | **OPEN** sharpness | Pick the iron point from a flat region |
| P4: Fe/Ni ordering only matches by re-tuning frozen coeff | **OPEN** (frozen-contract violation) | — | Re-tune the frozen coefficient |
| Rivals (SEMF) match the curve but SDT doesn't *beat* derivation-wise | Label **DEGENERATE / CONVERGENCE** honestly | — | Claim Class A "derivation" |

### Allowed adjustments

- Finer numerics (denser nuclide scan, profile resolution near the floor); phase splits (3a floor-search, 3b robustness) via ADJ entry; filename fix (`.cpp`↔`.py`) via ADJ entry.
- Alternative **native** orderings/weightings of the *already-frozen geometric terms* (bulk/surface/spread/asymmetry) — provided **no exponent changes** and no new fitted exponent is introduced.

### Disallowed adjustments

- Post-hoc widening of the ±2 floor window or the Spearman gate · tuning an exponent to land the floor then calling it geometric · relabelling a FITTED exponent as GEOMETRIC after the run · using measured `B/A` as `R̃` (IDENTITY-PASS) · importing SEMF coefficients / G / M / GM / quarks / wavefunctions into the chain · writing "charge radius" or treating charge as a substance.

### Dual verdict reminder

Every `NP21_VERDICT.md` header carries **both** axes: **Prompt completion** (A–F, did §④–§⑥ get done phase by phase?) and **Physics class** (NATIVE / CONVERGENCE / DEGENERATE / OPEN / KILLED). **Honest expectation, stated up front:** the strong outcome (iron floor **DERIVED**, no fitted exponent) is the only NATIVE/Class-A result; a fitted-exponent reproduction is **Class C / CALIBRATED** and will be labelled exactly that — *a fitted exponent is not a derived one.*

---

*NP21 · SPEC · the binding curve as one resistance landscape, iron at the floor · generalises NP19 · feeds SAR05 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
