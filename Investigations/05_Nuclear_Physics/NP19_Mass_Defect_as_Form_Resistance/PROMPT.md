# NP19: Mass-Defect as Form-Resistance + the Two-Ledger Lemma — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — We have never written down, as a *named framework claim*, that mass is the medium's RESISTANCE to holding a form and that a mass defect is therefore a *resistance difference* (not stored binding energy) — nor have we proven the three nuclear numbers (0.511, 1.293, 0.782 MeV) are one resistance landscape, not three separate energies.
2. **Why does it matter?** — This is the **load-bearing reframe** that grounds NP20 (the neutron's two numbers from one seat) and NP21 (the full resistance landscape). Without it, "mass↔energy interchange" stays a borrowed mystery and the β⁻/EC grammar's determinant −1 looks like a missing energy term. It also lets SDT *dissolve* — not merely restate — E=mc² as one substrate measured two ways.
3. **How will we find out?** — Four gated phases: (P1) formalise mass = form-resistance from Law IV with explicit symbols/dimensions; (P2) prove the **1.293 = 0.511 + 0.782** bookkeeping is resistance-difference accounting and that decay direction is *forced* by least-resistance (sign check); (P3) state and stress-test the **Two-Ledger Lemma** against ≥2 worked cases; (P4) connect to the determinant −1 grammar relabelling. Native reframe first; no fitted number is sought.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric/sign triggers: wrong-sign (bound = lower resistance) → **KILL**; arithmetic `1.293 − 0.511 ≠ 0.782` beyond data error → bookkeeping fails; same boundary yielding both signs → lemma fails.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class. Honest expectation: **Class C (Convergence) / reframe** — conceptual + arithmetic, *not* a new fitted constant. We say so up front.

---

## 1. Executive Summary (100–150 words)

Standard physics tabulates a nuclear "mass defect" as stored binding energy and accepts "mass↔energy interchange" as a brute fact. **SDT claims instead that mass is the medium's resistance to holding a given FORM — Law IV read as resistance — and a mass defect is a RESISTANCE DIFFERENCE.** The neutron is heavier *when bound* (a flipped-sign defect): the bound form is the higher-resistance one, and free-neutron decay is that form relaxing downhill, no trigger, no battery. **We will prove three numbers form one landscape:** electron rest mass 0.511 MeV (the manufacturing TOLL inside the gap), n−p gap 1.293 MeV (the resistance difference), and decay surplus 0.782 MeV (the EXHAUST = 1.293 − 0.511). We then promote the **Two-Ledger Lemma**: the same movement reads endothermic or exothermic depending only on where the system boundary is cut. Expected outcome: a named, audited reframe (Class C) grounding NP20/NP21.

## 2. Physical Context (250–400 words)

**Plain-language picture.** Imagine the substrate as a single reconfigurable medium. Pressing matter into a particular knotted *form* requires the medium to be held in that configuration against its own tendency to relax. The harder the medium resists holding that form — per Planck-length, per tic — the more *mass* the form has. Mass is therefore **not a substance and not a stored reservoir**; it is a *grip*. "Rest energy" is the *same grip* read off the other way: by how much movement is released when the form is allowed to relax. One medium, one resistance, two instruments — a ruler that reads grip (mass) and a ruler that reads relaxation (energy/movement).

**Why two readings give the same number.** Because they measure the same thing. This is why "mass–energy interchange" needs *no separate mechanism*: a resistance and a reservoir read as the same number because they are one medium measured two ways. Interchangeability is the *obvious consequence* of one substrate, not a mystery to be accepted.

**The three numbers (measured anchors, never the SM story).**
- **m_e c² = 0.510 999 MeV** — resistance of the electron form at rest = the **TOLL** that must be paid inside the gap to manufacture an electron form.
- **(m_n − m_p) c² = 1.293 MeV** — the **resistance difference** between the neutron-form and the proton-form.
- **Decay surplus Q_β = 0.782 MeV** — the **EXHAUST** that leaves as movement (electron + antineutrino) *after* the toll is paid: 1.293 − 0.511 = 0.782.

**Key variables / symbols (define once, carry through):**
| Symbol | Meaning | Dimension |
|--------|---------|-----------|
| `ρ_form` | form-resistance density (grip per Planck-volume per tic) | [Pa] = [J·m⁻³] |
| `R(form)` | total form-resistance of a configuration = `∫ρ_form dV` mapped to rest energy | [J] (report in MeV) |
| `ΔR` | resistance difference between two forms = the mass defect | [J] (MeV) |
| `τ` | toll: manufacturing cost of the lighter daughter's new form (here m_e c²) | [J] (MeV) |
| `Q` | exhaust / surplus released as movement = `ΔR − τ` | [J] (MeV) |
| `∂(sys)` | the chosen system boundary (the "cut") | — |

**Connection to the rest of SDT.** Upstream: Law IV (`m = Φ V_disp / (l_P³ c²)`, mass as throughput-reorganisation cost) and NP14 (which already found the bound/heavier neutron is the *larger-V_disp* form). Downstream: NP20 reads the neutron's two numbers from one seat; NP21 maps the whole resistance landscape. Sibling FLM11 supplies the tape-measure principle (the property you read depends on the ruler you pick) — here applied to *boundary/time* form.

## 3. Theoretical Framework (400–600 words)

**Axiom (Law IV, verbatim from `laws.hpp`):** `m = Φ V_disp / (l_P³ c²)` — *mass is throughput reorganisation cost.* Equivalently `V_disp = 3 m l_P³ c² / Φ` (`law_IV::V_disp_from_mass`). NP19 reads this as: the cost of *reorganising* throughput into a held form *is* the medium's resistance to holding it. We therefore **define**

> **R(form) ≡ m(form) · c²** — the form's total rest energy *is* its accumulated form-resistance.

This is not a new equation; it is a *renaming with a claim*: the right-hand side is a resistance, not a reservoir. The claim earns its keep only if it (a) gives the right *sign* of the mass defect and (b) makes the three numbers one landscape.

**Resistance-difference accounting (the mass defect).** For a transformation `A → B + (movement)`,

> **ΔR ≡ R(A) − R(B_forms)** , and the movement carried away `Q = ΔR − τ`,

where `τ` is the manufacturing toll for any *new* form that must be built (the electron, here). A transformation runs **only if `ΔR > 0`** (downhill in form-resistance) — this is the *path of least resistance*, the SDT statement of spontaneity. **No external feed, no battery, no toll-collector at the event:** the surplus was already the difference in grip.

**The flipped-sign neutron (the crux).** In SDT the *bound/heavier* form is the *higher*-resistance form (NP14: neutron has the larger V_disp). So:
- `R(n) > R(p)` ⟹ `ΔR = R(n) − R(p) > 0` ⟹ free neutron is *uphill — a running over-payment (higher maintenance rate)*, relaxes spontaneously. *(word "stored" repaired — interchange sweep 2026-07-07, Harvey-authorized)*
- The toll to make the daughter electron form is `τ = m_e c² = 0.511 MeV`.
- The exhaust is `Q = ΔR − τ = 1.293 − 0.511 = 0.782 MeV` — matches the measured β⁻ endpoint to data error.

Decay runs **because the gap exceeds the manufacturing cost** (`ΔR > τ`). If the gap were *smaller* than the toll, the neutron-form would be stable — exactly the SM threshold condition, *derived here as a least-resistance inequality, not imported.*

**The Two-Ledger Lemma (to be promoted to a named SDT lemma).**

> *The same movement reads endothermic through one accounting boundary and exothermic through another — exactly as the same form reads as mass through one instrument and as flux through another. WHERE the system boundary `∂(sys)` is cut determines the SIGN, just as which ruler is chosen determines the property (FLM11 tape-measure principle, here in time/boundary form).*

Worked seed: `p + e⁻ → n + νₑ` costs **+1.293 MeV** as an *isolated arrow* (endothermic), yet in stellar core collapse the same conversion is the *valve* through which **~3×10⁴⁶ J** vents (massively exothermic at event scale). Sign is an artefact of the cut, not of the medium.

**Grammar consistency (constitutional check, §8.3 of ATOMICUS rules).** The β⁻/EC vector pair is a bijection with **determinant −1** — a pure *relabelling of form* that conserves count and **carries no energy in the grammar**. That is *expected*, because mass defects ARE relabellings of form: the energy is not in the grammar move, it is in the **resistance difference between the two forms the move connects.** The grammar bookkeeps WHICH forms; the resistance landscape (NP21) supplies HOW HARD each is to hold.

**Constraints (whitelist only).** Inputs limited to `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured masses (`measured::m_e`, `m_p`, `m_n`, `MeV_to_J`). **Prohibited:** G/M/GM, wavefunctions, fields-as-primitives, quarks/gluons, virtual particles as objects, dark matter/energy, ΛCDM, duality, and the *standard-model decay story* (W boson, weak coupling G_F). Never write "charge radius" or treat charge as a substance.

## 4. Investigation Strategy (800–1200 words — be excessive)

This investigation is *primarily conceptual + arithmetic*. The "tool" exists to make the bookkeeping and the sign checks **mechanical and falsifiable**, not to fit a number. Four gated phases.

---

### Phase 1 — Formalise mass = form-resistance from Law IV (1–2 h)

**Goal.** Write `R(form) ≡ m c²` as an *audited definition* with explicit symbols, dimensions, and a delete-test: show that calling `m c²` a *resistance* (grip per Planck-volume per tic) introduces **no new constant** beyond Law IV, and changes no numerical value — only the *reading*.

**Method.**
1. Pull `law_IV::V_disp_from_mass(m)` and `mass_from_V_disp(V)` from `laws.hpp`; confirm `m = Φ V_disp / (3 l_P³ c²)` round-trips for `m_e`, `m_p`, `m_n`.
2. Define `ρ_form ≡ R(form) / V_disp` for each particle; print in Pa. Confirm it lands at the marginal-stability scale `P_conv/3` (cross-check `law_IV::P_cf_e`) — i.e. the "resistance density" is the *same* convergence-pressure scale the engine already exposes, *not a new dial*.
3. Write the one-line claim: rest energy *is* accumulated form-resistance; `m_inert = m_grav` follows because both read the same `V_disp`/grip.

**Pre-committed success metric.** Round-trip `|m − mass_from_V_disp(V_disp_from_mass(m))| / m < 1e-9` for all three particles (pure identity check). `ρ_form` for the electron within **1 order of magnitude** of `P_conv/3` (the engine's stability scale). **Zero** new constants introduced (delete-test).

**Failure trigger.** Any new fitted constant required → the "resistance" reading is smuggling; **PIVOT** to a stricter renaming or **OPEN**. Round-trip identity failing → engine-usage bug; fix before proceeding.

**Gate.** No Phase 2 until the renaming is shown constant-free.
**Out of scope.** Deriving Φ or V_disp themselves (PPT01/Law IV own that); any decay arithmetic.

---

### Phase 2 — The 1.293 = 0.511 + 0.782 bookkeeping + forced decay direction (1–2 h)

**Goal.** Show the three numbers are **one resistance landscape**: gap = toll + exhaust, and that decay direction is *forced* by least-resistance with the **correct (flipped) sign**.

**Method.**
1. From `measured`: compute `R(n) = m_n c²`, `R(p) = m_p c²`, `τ = m_e c²` in MeV (via `MeV_to_J`). Print to 4+ sig figs.
2. Compute `ΔR = R(n) − R(p)` → expect **1.293 MeV**. Compute `Q = ΔR − τ` → expect **0.782 MeV**.
3. **Sign check (the crux):** assert `R(n) > R(p)` — the *bound/heavier* neutron-form is the *higher*-resistance form (consistent with NP14 larger-V_disp). Assert `ΔR > τ` (gap exceeds manufacturing cost) ⟹ spontaneous, no trigger.
4. State the spontaneity inequality explicitly: decay runs iff `ΔR > τ`; if `ΔR < τ` the form is stable. Print both sides.
5. Cross-check the exhaust against the measured β⁻ endpoint (0.782 MeV) as an `OBSERVED-TARGET` column — *comparison only*, never a fit.

**Pre-committed success metric.** `|ΔR − 1.293| / 1.293 < 0.1%` (it is a subtraction of measured masses — should be near machine-exact). `|(ΔR − τ) − 0.782| / 0.782 < 0.2%`. Sign assertions both TRUE.

**Failure trigger.** `R(n) ≤ R(p)` (wrong sign) → **KILL** (see §⑧ T1). `1.293 − 0.511 ≠ 0.782` beyond data error → bookkeeping false; **KILL** that claim (§⑧ T2). `ΔR < τ` (would predict a stable free neutron) → contradiction with observation; re-examine which mass is the daughter form.

**Gate.** No Phase 3 until sign + arithmetic both pass.
**Out of scope.** Predicting the 880 s lifetime *value* (that is NP11/NP20); here we only fix the *direction* and the *energy bookkeeping*.

---

### Phase 3 — State & stress-test the Two-Ledger Lemma against ≥2 cases (2–3 h)

**Goal.** Promote the lemma and prove the sign flips **only with the boundary**, never with the physics.

**Method.**
- **Case A — Free neutron decay.** Boundary 1 = {neutron alone}: `n → p + e⁻ + ν̄`, exothermic, `Q = +0.782 MeV` leaves as movement. Boundary 2 = {proton + electron, building a neutron}: `p + e⁻ → n + ν` reads endothermic, `+1.293 MeV` must be supplied. **Same physics, opposite sign — only the cut changed.** Print both ledgers side by side; assert they sum consistently (the +1.293 to build, the −0.782 net to unbuild differ by the 0.511 toll that is *manufactured/consumed*, not destroyed).
- **Case B — Stellar electron capture / core collapse.** Boundary "isolated arrow": `p + e⁻ → n + νₑ` costs **+1.293 MeV** (endothermic). Boundary "event scale": the same conversion is the valve through which **~3×10⁴⁶ J** of gravitational binding vents as neutrinos — *massively exothermic*. Show that the *per-reaction* number is unchanged; only the enclosed system changed (now it includes the collapsing core's released movement). Assert: the *medium's* per-form resistances `R(n), R(p), τ` are identical in both readings.
- **Lemma statement (final wording).** "The same movement reads endothermic through one boundary and exothermic through another; the sign is a property of the cut `∂(sys)`, not of the medium — the boundary-form of the FLM11 tape-measure principle."
- **Stress test.** Attempt to construct a *single fixed boundary* that yields *both* signs for the *same* reaction. Show it cannot (a fixed cut has a fixed `ΔR`). This is the lemma's own falsifier turned inward.

**Pre-committed success metric.** For each case: the two ledgers differ in sign; the per-reaction `|ΔR|` is **identical to ≤1e-6 relative** across boundaries (it must be — same masses). The single-boundary-both-signs construction **fails** (returns one sign).

**Failure trigger.** If any single fixed boundary yields both signs → lemma **KILL** (§⑧ T3). If the per-reaction `|ΔR|` changes with the boundary → we are smuggling energy into the cut; **PIVOT** to find the leak.

**Gate.** No Phase 4 until both cases pass and the both-signs construction provably fails.
**Out of scope.** The numeric `~3×10⁴⁶ J` is an order-of-magnitude *illustration* (supernova binding energy scale), labelled `OBSERVED-TARGET`; not derived here.

---

### Phase 4 — Connect to the determinant −1 grammar relabelling (1 h)

**Goal.** Close the loop with ATOMICUS §8.3: show that "carries no energy in the grammar" is *expected*, not a defect.

**Method.**
1. Restate the β⁻/EC vector pair as a bijection with **determinant −1** (pure relabelling of form, conserves count).
2. Argue: a relabelling-of-form carries **no energy in the grammar move itself**; the energy lives in the **resistance difference** between the two forms the move connects (Phase 2's `ΔR`). The grammar says *which* forms; NP21's landscape says *how hard* each is to hold.
3. Print a one-paragraph reconciliation: grammar (count-conserving, det −1) ⊕ resistance landscape (energy-carrying) = full mass-defect accounting.

**Pre-committed success metric.** A written, internally consistent statement that (a) the grammar move is energy-free by construction and (b) all of `1.293/0.511/0.782` is sourced from `ΔR`, not from the relabelling. No contradiction with NP01 grammar or ATOMICUS rules.

**Failure trigger.** If energy *must* be assigned to the grammar move to balance → the reframe is incomplete; **OPEN** and flag for NP21.

**Gate.** Final verdict only after P1–P4 gated.
**Out of scope.** The full resistance-landscape map (that *is* NP21).

---

**Global pre-commitments.** Best class **C (Convergence) / reframe**. CALIBRATED budget **0**. No new constant in any phase. All numbers traced to `measured::` + `MeV_to_J`. Any phase failure → PIVOT/KILL/OPEN, never RETRO-PASS.

## 5. Success Criteria (200–300 words)

Use canonical labels. **Dual verdict required** (prompt completion A–F × physics class).

✅ **PASS (Class C: Convergence — the realistic ceiling).** All four phases gated. `R(form) ≡ m c²` shown constant-free (P1). Bookkeeping `ΔR = 1.293` within 0.1% and `ΔR − τ = 0.782` within 0.2%, with the **correct flipped sign** `R(n) > R(p)` (P2). Two-Ledger Lemma stated and surviving both worked cases, with the single-boundary-both-signs construction provably failing (P3). Grammar det −1 reconciliation written (P4). **What we publish:** a named SDT lemma + an audited reframe that *dissolves* mass↔energy interchange as one substrate measured two ways. Honestly labelled: conceptual + arithmetic, **not a new fitted number**.

⚠️ **QUALIFIED (Class C, partial).** P1–P3 pass but P4 grammar reconciliation left **OPEN** (energy can't yet be cleanly excluded from the relabelling). Ship the lemma; flag the grammar tie-in for NP21.

⚠️ **QUALIFIED PENDING (Class D: Computed).** Arithmetic and sign check pass (P2) but the lemma's universality (P3) is shown for only one case. Useful as bookkeeping; lemma not yet promoted.

❌ **FAIL / KILL (Class F).** Any of: wrong sign `R(n) ≤ R(p)`; `1.293 − 0.511 ≠ 0.782` beyond data error; a single fixed boundary giving both signs. Record numbers in `NP19_VERDICT.md` and `INVESTIGATION_STACK.md`; do **not** rescue with a fit.

**Forbidden at every level:** RETRO-PASS (widening a committed tolerance after seeing the number), PLUG (a coefficient to force a match), IDENTITY-PASS (calling `m c²` a mechanism without the sign+lemma work), BORROW-SMUGGLE (G, M, ψ, G_F, ΛCDM into the chain).

## 6. Outputs (150–300 words)

All written into `Investigations/05_Nuclear_Physics/NP19_Mass_Defect_as_Form_Resistance/`. **Edit no existing file; never touch `Engine/include/sdt/` or `Laws/`.**

1. **`NP19_DERIVATION.md`** — the analytic spine: Law IV → `R(form) ≡ m c²` (resistance reading, delete-test); the resistance-difference accounting `ΔR = R(A) − R(B) `, `Q = ΔR − τ`; the flipped-sign argument; the **Two-Ledger Lemma** stated formally with both worked cases; the det −1 grammar reconciliation. Each step flagged `DERIVED` / `ASSUMED` / `IDENTITY` / `OBSERVED-TARGET`.
2. **`np19_ledger.cpp`** (or `np19_ledger.py`) — a small standalone tool that `#include <sdt/laws.hpp>` (C++) and prints the **three-number bookkeeping** and **sign checks**: `R(n)`, `R(p)`, `τ = m_e c²`, `ΔR`, `Q = ΔR − τ`, each in MeV with a one-line parameter tag; asserts `R(n) > R(p)` and `ΔR > τ`; prints the two-ledger table for both cases (free n; stellar EC) showing identical `|ΔR|` across boundaries with flipped sign. Build line in a header comment: `cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:np19.exe np19_ledger.cpp` (or `g++ -std=c++20 -IEngine/include …`).
3. **`np19_results.txt`** — captured stdout (the bookkeeping table + PASS/FAIL of each sign assertion).
4. **`NP19_VERDICT.md`** — dual verdict header (prompt completion A–F × physics class), filled falsification table (§⑧), explicit class call (expected C / reframe).
5. **`RUN_LOG.md`** — **mandatory**: Pre-Run Commitment Block (from §⑩) filled before coding, then ADJ-### entries and phase gates per `PROMPT_EXECUTION_PROTOCOL.md`.

## 7. Dependencies & References (150–250 words)

**Upstream (required first):**
- **Law IV** (`laws.hpp` §`law_IV`): `m = Φ V_disp / (l_P³ c²)` — mass as throughput reorganisation cost. The whole reframe is this law *read as resistance*.
- **NP14** (Proton-Neutron Mass Difference): already establishes the bound/heavier neutron is the *larger-V_disp* form — supplies the **sign** NP19 needs.
- `measured::` masses (`m_e`, `m_p`, `m_n`) and `MeV_to_J` — the only external inputs.

**Downstream (blocked until this resolves):**
- **NP20** (the neutron's two numbers from one seat) — needs the resistance-difference framing and the forced decay direction.
- **NP21** (the whole resistance landscape) — NP19 supplies the *unit of account* (form-resistance) the landscape is built from.

**Related (read in parallel):**
- **FLM11** (tape-measure principle) — the property you read depends on the ruler; NP19's Two-Ledger Lemma is its boundary/time form.
- **NP11** (Neutron Lifetime) — the *value* of the 880 s relaxation (NP19 fixes only direction + energy).
- **ATOMICUS `rules/On the Nature of Atomicus Rules.md` §8.3** — the β⁻/EC bijection, determinant −1.
- Sibling set: **NP18, PPT10, PPT11, APS06, SAR05** (same 9-investigation batch).

## 8. Falsification Tests (150–250 words)

| Test | Hypothesis | Predicted Outcome | If FAIL |
|------|-----------|-------------------|---------|
| **T1 (sign — the crux)** | The *bound/heavier* form is the *higher*-resistance form | `R(n) > R(p)` ⟹ `ΔR > 0`, free neutron relaxes downhill | `R(n) ≤ R(p)` → **KILL**: the resistance reading is wrong-signed; mass defect ≠ resistance difference |
| **T2 (bookkeeping)** | The three numbers are one landscape: gap = toll + exhaust | `1.293 − 0.511 = 0.782` within data error | `≠ 0.782` beyond error → **KILL** the one-landscape claim; numbers are independent |
| **T3 (lemma)** | Sign of a reaction is a property of the boundary, not the medium | No single *fixed* boundary yields both signs; `|ΔR|` identical across boundaries | A fixed boundary gives both signs, or `|ΔR|` changes with the cut → **lemma KILL** |
| **T4 (no-feed)** | Decay needs no external trigger/battery; surplus pre-exists as `ΔR` | Spontaneous, `ΔR > τ`; no toll-collector at the event | Decay requires an external energy input to balance → reframe incomplete, **OPEN** |
| **T5 (grammar)** | det −1 relabelling carries no energy *in the grammar* | All energy sourced from `ΔR`, none from the move | Energy must be assigned to the grammar move → **OPEN**, defer to NP21 |

**Recovery:** T1/T2/T3 are hard KILLs — record numbers, no fit. T4/T5 are OPENs — ship partial, flag NP21. Never RETRO-PASS a sign or widen the arithmetic tolerance after seeing the subtraction.

## 9. Implementation Notes (200–300 words)

- **Tool is a checker, not a fitter.** `np19_ledger` exists to make the bookkeeping mechanical and the sign assertions *trip loudly* on failure. Use `assert` (or explicit PASS/FAIL prints) for `R(n) > R(p)` and `ΔR > τ`; do not silently continue past a sign failure.
- **Units.** Compute rest energies in joules (`m * c * c`) then divide by `measured::MeV_to_J` to print MeV. Expect `ΔR ≈ 1.2933 MeV`, `τ = m_e c² ≈ 0.51100 MeV`, `Q ≈ 0.7823 MeV`. The subtraction of two near-equal large masses (`m_n − m_p`) is the one numerical-care point: subtract in **kg first** (double precision is ample — the gap is ~1.4e-30 kg, well above round-off), *then* convert.
- **No local constants.** Read `m_e, m_p, m_n, c, MeV_to_J` from `sdt::laws::measured` only (§0 anti-creep). Do not hardcode 0.511/1.293/0.782 as inputs — they must *emerge* from the masses; the literals appear only as `OBSERVED-TARGET` comparison columns.
- **The `~3×10⁴⁶ J` figure** is an order-of-magnitude illustration of supernova binding energy for the Two-Ledger event-scale ledger; label it `OBSERVED-TARGET`, never derive it.
- **Output discipline.** One parameter tag per printed number (`MEASURED-INPUT` / `DERIVED` / `IDENTITY` / `OBSERVED-TARGET`). Capture stdout verbatim into `np19_results.txt`.
- **Prose discipline.** Never write "charge radius" or treat charge as a substance; the proton is a form, not a charge reservoir. Keep the SM decay *story* (W boson, G_F) out of the chain — anchors are the *numbers*, not the mechanism.
- **Visualisation hint (optional):** a two-row bar — `[1.293]` split into `[0.511 toll | 0.782 exhaust]` — makes the landscape obvious at a glance.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP19
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [CONVERGENCE]  # honest ceiling: reframe, not a new fitted number
- CALIBRATED budget: 0  (no fitted parameters; literals 0.511/1.293/0.782 are OBSERVED-TARGET only)
- Engine namespaces: measured (m_e, m_p, m_n, MeV_to_J, c), law_IV (V_disp round-trip, P_cf)
- Phase thresholds (committed before run):
    P1: round-trip identity < 1e-9; ρ_form_e within 1 order of mag of P_conv/3; 0 new constants
    P2: |ΔR − 1.293|/1.293 < 0.1%; |(ΔR−τ) − 0.782|/0.782 < 0.2%; sign R(n)>R(p) TRUE; ΔR>τ TRUE
    P3: |ΔR| identical across boundaries ≤1e-6 rel; both ledgers opposite sign; both-signs construction FAILS
    P4: written reconciliation, energy sourced 100% from ΔR, none from grammar move
- Forbidden retroactive changes: widen tolerances; plug 0.782; flip a sign assertion post-run;
  IDENTITY-PASS (m c² called a mechanism without P2 sign + P3 lemma); local constant namespaces;
  any G/M/GM/ψ/G_F/ΛCDM in the chain
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric/sign) | PIVOT (first response) | If pivot fails | Forbidden |
|------------------------|------------------------|----------------|-----------|
| P1: "resistance" reading needs a new constant | Tighten to pure renaming of `m c²`; re-run delete-test | **OPEN** — reframe not constant-free | Add the constant and call it derived |
| P1: Law IV round-trip ≠ identity | Fix engine usage / units; verify `laws.hpp` symbols | STOP — report blocker | Fudge V_disp |
| **P2: `R(n) ≤ R(p)` (wrong sign)** | Re-check which form is the daughter; consult NP14 sign | **KILL** (T1) — record numbers | RETRO-flip the assertion |
| P2: `1.293 − 0.511 ≠ 0.782` beyond error | Re-check unit conversions / which mass enters τ | **KILL** (T2) one-landscape claim | Widen the 0.2% tolerance |
| P2: `ΔR < τ` (predicts stable free neutron) | Re-identify daughter forms; check m_e is the toll | **OPEN** — threshold logic | Ignore the contradiction |
| **P3: one fixed boundary gives both signs** | Re-examine boundary definition; is energy leaking in? | **KILL** (T3) the lemma | Claim lemma anyway |
| P3: `|ΔR|` changes with boundary | Find the leak (smuggled energy in the cut) | **PIVOT** or **OPEN** | Average the two values |
| P4: energy must sit in the grammar move | **DEFER** reconciliation; flag NP21 | **OPEN** | Assign energy to det −1 move |
| Rivals (SM) match the numbers but SDT doesn't *beat* | Label **CONVERGENCE / reframe** honestly | — | Claim Class A "derivation" |

### Allowed adjustments

- Finer numerics (subtract masses in kg before MeV conversion); phase splits (3a free-n, 3b stellar) via ADJ entry; filename fix (`.cpp`↔`.py`) via ADJ entry.
- Alternative **native** wordings of the resistance reading already implied in §③ (grip-per-Planck-volume vs reorganisation-cost) — provided constant-free.

### Disallowed adjustments

- Post-hoc tolerance widening · plugging 0.782 or any coefficient · flipping a committed sign assertion after the run · IDENTITY-PASS (`m c²` alone) · importing G/M/GM/ψ/G_F/ΛCDM/wavefunctions/quarks into the chain · treating the SM decay story as input · writing "charge radius".

### Dual verdict reminder

Every `NP19_VERDICT.md` header carries **both** axes: **Prompt completion** (A–F, did §④–§⑥ get done phase by phase?) and **Physics class** (CONVERGENCE / DEGENERATE / OPEN / KILLED). Honest expectation: **CONVERGENCE — a named reframe + arithmetic, not a new number.**

---

*NP19 · SPEC · the load-bearing reframe grounding NP20 & NP21 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
