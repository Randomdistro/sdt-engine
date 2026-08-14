# FLM11 — The Tape-Measure Principle and the Fifth-Ruler Count

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — How many genuinely independent "fundamental properties" the medium has, and whether that number is the count of the form's measurable degrees of freedom (a geometric fact) rather than a list inherited from experiment.
2. **Why does it matter?** — It explains *why unification looks impossible from inside the medium* (every instrument is cut from the medium and pre-spends the axis it tries to expose), and it predicts the neutrino as a structural blind spot rather than a "weak particle." Upstream of PPT10/PPT11 (straight-light, oscillation) and NP18 (uncommitted-cloth loophole).
3. **How will we find out?** — Formalise "instrument = committed projection of the medium" (P1), enumerate the form's independent DoF from trefoil/vortex geometry + the 28-D state and map each to a property (P2), derive the straight zero-grip projection as the one DoF with no ruler and identify it with the neutrino (P3), check the count against the properties physics actually uses (P4).
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers: a DoF count that disagrees with the independent-ruler count without explanation; a straight projection that is *not* among the form's DoF; or an irreducibly ambiguous count.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). The strong falsifiable core is the **derived integer count** and the **predicted existence/non-existence of a fifth independent ruler**.

---

## §0 Anti-creep protocol (R0–R5)

- **R0 — declared dependencies:** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in their measured units. The `sdt::laws::measured` derivation basis is the only external fact source.
- **R1 — Prohibited:** wavefunctions, fields-as-primitives, quarks/gluons, virtual particles as objects, dark matter/energy, ΛCDM, wave–particle duality. None may enter the chain — not even as "intuition."
- **R2 — No charge-as-substance:** never write "charge radius." `e` is a **unit-bridge**; charge is **handed redirection** of through-flow. A "charge ruler" reads handedness, not a stored substance.
- **R3 — Native yardsticks only:** express results in SDT-native units (electron wake, koppa ϟ = R/k², winding W, traction T = 3(W+1)), never μ_B / magnetons / imported SI-disguised constants.
- **R4 — No G/M/GM in the chain.** The GM_equivalent helper is for OBSERVED comparison columns only.
- **R5 — Count honesty:** the property count is an **integer** to be *derived*, not chosen. If the geometry does not yield a clean integer, the verdict is **OPEN** — do not round, fit, or assert a number to match physics' habit of four.

---

## 1. Executive Summary

Physics names four "fundamental properties" — mass, charge, magnetic flux, electromagnetism — and treats them as separate facts about objects. **They are not facts about objects; they are facts about instruments.** Every instrument is *cut from the medium it measures*, so it can only return its own pre-committed axis: you weigh mass with resistance structures, read charge with handed (electronic) structures, read flux with moving-medium structures, read EM with EM structures. You never measured four things — you measured **one medium** with **four pieces of medium**, each pre-committed to one reading, and each handed that reading back. This investigation (i) formalises "instrument = committed projection of the medium," (ii) **derives the number of independent properties** as a degrees-of-freedom count of the form (trefoil/vortex + 28-D state) and predicts whether a *fifth* independent ruler exists, and (iii) shows that exactly one projection — the **straight** one — has **no native ruler** (a ruler reads by gripping; the straight projection is defined by *not* gripping), and that this blind spot **is the neutrino**. **We expect**: a clean small integer count, the straight projection as the unmeasurable residue, and a definite yes/no on the fifth ruler.

---

## 2. Physical Context (the tape-measure principle)

**Analogy.** A tape-measure is made of the same stuff as the wall it measures; it can only report length because it was *committed to length* before it touched anything. Hand someone a tape-measure and they will find lengths everywhere — never temperatures. The instrument's commitment is prior to the reading. SDT says every physical instrument is exactly this: a strip of the **one medium** (the spation lattice / reconfigurable lightspeed superfluid) that has been **pre-committed to one axis of the form's configuration space**. It reads that axis by **gripping** the medium along it, and hands back precisely the identity it was committed to.

**Why unification looks impossible from inside.** To measure how mass *relates to* charge, you reach for an instrument — but every instrument is a committed strip of the same cloth, so it **pre-selects an axis** and **spends the very identity it was trying to expose**. The "relation" you wanted to see is destroyed by the act of reaching for a committed ruler. Unification is not hard because the properties are far apart; it is hard because the **observer's instruments are all cut from the thing being unified**.

**The four rulers (working map, to be derived in P2):**

| Property (physics) | Instrument cloth (committed strip) | Axis it grips | SDT-native reading |
|---|---|---|---|
| mass | resistance / inertial structures | reorganisation-cost axis | Φ·V_disp / (ℓ_P³c²), Law IV |
| charge | handed (electronic) structures | handedness / through-flow sign | Φ₃ chirality ±1; handed redirection (R2) |
| magnetic flux | moving-medium structures | circulation / motion-of-medium | toroidal circulation v_T, Phi_2 |
| EM | EM (oscillatory field) structures | propagating oscillation axis | bond-switch / wake propagation |

**Key variables.** Form configuration space **𝒞**; an instrument = a selection operator **Π_a : 𝒞 → ℝ** (one axis a). Form DoF set **𝒟** with |𝒟| = D to be derived. Property count **P** = number of *independent* Π_a. Straight projection **Π_∥** = the zero-grip selection. Winding W; traction T = 3(W+1); 28-D state Ξ ∈ ℝ²⁸ (Levels 1–7). Cross-refs: PPT08 (trefoil angular DoF), FLM01 / `state28d.hpp` (the 28 components and their level grouping), `law_VI::winding` (W=0 neutrino / open winding).

---

## 3. Theoretical Framework

**Axiom (instrument = committed projection).** An instrument is a strip of the medium whose internal configuration is *pinned* to one axis a of the form's configuration space 𝒞. Measuring is applying the selection operator Π_a; the reading is the projection of the locus onto a. Because Π_a is *cut from* 𝒞, it returns a only — never the locus's relation to other axes. Formally: a ruler is a choice of **one basis direction** in the form's tangent space, and the reading is the component along it.

**The form's degrees of freedom (the thing to count).** Two converging native sources bound D:

- **Topology / trefoil (Law VI, PPT08/PPT09):** the proton is the (2,3) trefoil (W=3); the electron is the (1,1) unknot (W=1); the neutrino is the **open winding W=0** (`law_VI::winding`). A knot/vortex in 3-space has a fixed set of independent rigid-body + circulation + handedness motions: translation of the core ring (T₁), tube swelling (T₂), surface/orientation, circulation (toroidal v_T and poloidal v_P, Law V budget v_T²+v_P²=c²), handedness Φ₃ = ±1, and the **straight/through axis** (no circulation, no grip).
- **28-D state (FLM01, `state28d.hpp`):** Level 5 (Torus, T₁–T₅) and Level 6 (Dynamism, Φ₀–Φ₅) encode the structural and dynamical DoF. The *measurable property* axes are the subset of these that an external committed strip can grip. Mass↔reorganisation cost, charge↔Φ₃ handedness, flux↔circulation, EM↔oscillation Φ₂.

**Constraint (gripping = reading).** A ruler reads by **gripping**: it couples to a circulation, a handedness, a resistance, or an oscillation — something with a *purchase point* on the medium. The **straight projection Π_∥** is defined by **zero grip**: pure through-flow along the core axis, no circulation to catch, no handedness to resolve, no resistance to push against. It carries energy and momentum (it is the open W=0 line) but offers **no committed cloth anywhere in the medium a purchase**. Therefore Π_∥ has **no native instrument**.

**Do NOT** (per R1–R2): introduce spin operators, Pauli matrices, gauge fields, or "charge density." The handedness axis is Φ₃ (native, `state28d`), the circulation axis is v_T/v_P (Law V), the reorganisation-cost axis is Law IV — all already in `laws.hpp`. The count must come from these, not from a borrowed symmetry group. (If a Lie-group dimension *coincides* with the count, label it CONVERGENCE, not derivation.)

---

## 4. Investigation Strategy (≥4 phases — be excessive)

> Pre-commit every threshold in `RUN_LOG.md` (§⑩ block) **before** writing the tool. Gate each phase.

### Phase 1 — Formalise "instrument = committed projection" (PAPER, ~1–2 h)

- **Goal:** A precise, symbol-level definition of a ruler as a selection of one axis of the form's configuration space, and a theorem stating that any committed strip returns only its own axis.
- **Method:**
  1. Define 𝒞 = the form's configuration space; the measurable tangent space at a locus, with basis axes {a₁ … a_D}.
  2. Define the **selection operator** Π_a (projection onto axis a) and the **commitment** of a strip: its internal pin to a single basis direction (e.g. handedness-pinned, circulation-pinned).
  3. State and argue the **Tape-Measure Lemma:** *for a strip committed to axis a, the reading of any locus L is ⟨L, a⟩ and is independent of L's components on a′ ≠ a* — hence cross-axis relations are unmeasurable by any single committed strip.
  4. Connect to the **two-ledger lemma** (NP19): mass and moment are the *same* defect read by *two* committed strips (time/boundary forms of one principle) — show this is the Tape-Measure Lemma applied twice.
- **Gate / metric:** the Lemma must be stated with symbols (Π_a, ⟨L,a⟩) and must *predict* the impossibility of measuring a cross-axis relation with one instrument. No numeric gate here; this is the definitional spine. **OUT OF SCOPE:** counting D (that is P2); any claim about the neutrino (P3).

### Phase 2 — ENUMERATE the form's independent DoF → property count (CALCULATION + tool, ~2–3 h)

- **Goal:** A **pre-committed integer count** P of independent rulers (measurable property axes) derived from the trefoil/vortex geometry and the 28-D state, plus a **definite prediction** on whether a *fifth* independent ruler exists.
- **Method:**
  1. List the candidate independent motions/axes of the form from two sources and intersect them:
     - **Trefoil/vortex motions:** core-ring translation (T₁), tube swelling (T₂), toroidal circulation v_T, poloidal circulation v_P, handedness Φ₃ = ±1, **through-axis (straight)**, surface orientation.
     - **28-D measurable subset:** which of T₁–T₅ / Φ₀–Φ₅ an *external* committed strip can grip (a strip cannot grip an internal-only DoF; e.g. T₁ central-ring length may be ungrippable from outside — decide explicitly and record).
  2. For each surviving axis, assign exactly one **gripping mechanism** and the matching **property**:
     - reorganisation-cost → **mass** (Law IV)
     - handedness Φ₃ → **charge** (handed redirection; R2)
     - circulation v_T → **magnetic flux** (motion of medium)
     - oscillation Φ₂ → **EM** (propagating wake)
     - and explicitly test whether **poloidal v_P / orientation / something else** constitutes a *fifth independent grippable axis* — or collapses into one already listed (e.g. v_P is fixed by v_T via Law V, hence *not* independent).
  3. **Pre-commit the count** in `RUN_LOG.md` *before* running: state the predicted P (e.g. P = 4 with v_P dependent, or P = 5 if a fifth survives) and the *reason*. The tool then mechanically enumerates and must reproduce the pre-committed integer.
  4. Implement `flm11_ruler_count.cpp` (or `.py`): encode each candidate axis, its grip mechanism, and an *independence test* (is it fixed by a constraint such as v_T²+v_P²=c², or by W, or by T=3(W+1)?). Output the surviving count and the property map.
- **Pre-committed metric:** the tool's enumerated count **equals** the pre-committed integer with **no axis added or removed after seeing physics' "four."** Independence tests must be explicit (Law V budget, winding constraint), not asserted.
- **Failure trigger:** if the enumeration yields a *different* integer than the pre-commit, or the count is **ambiguous** (an axis is neither clearly independent nor clearly dependent) → **do not force 4**; record the ambiguity and route to OPEN per §⑧/§⑩.
- **Gate:** P3 forbidden until P2 yields a committed integer **or** a documented OPEN on the count. **OUT OF SCOPE:** computing magnitudes of the properties (mass values, moments) — this phase counts axes, it does not evaluate them.

### Phase 3 — DERIVE the straight (zero-grip) projection → the neutrino (THEORY + tool flag, ~1–2 h)

- **Goal:** Show that exactly one DoF — the **straight/through axis Π_∥** — has **no associated ruler**, and that it coincides with the SDT neutrino (open winding W=0).
- **Method:**
  1. From P2's axis list, identify the unique axis whose grip mechanism is **null**: pure through-flow, no circulation, no handedness, no resistance to push against. Argue (symbolically) that *no committed strip in the medium can couple to it* — a ruler reads by gripping, and Π_∥ is defined by not gripping.
  2. Show Π_∥ is **not empty**: it carries momentum/energy (the open line is real, W=0 in `law_VI::winding`), so the blind spot is *measurability*, not existence.
  3. **Identify Π_∥ with the neutrino:** the open winding W=0 is the straight projection; therefore the neutrino is hard to see **not** because it is rare or weak but because it is **un-self-measurable by committed cloth**. Cross-ref PPT10 (straight-light: the straight projection has no ruler) and NP18 (BEC = *uncommitted* cloth — the one substrate not pre-pinned to a ruler axis, which reads by **coherence/quietness rather than grip** — the loophole).
  4. Tool: `flm11_ruler_count` flags exactly one enumerated axis as the **zero-grip residue** and asserts it is W=0.
- **Pre-committed metric:** **exactly one** axis flagged zero-grip; it must be the through/straight axis; it must map to W=0. Zero or more-than-one zero-grip axes → fail.
- **Failure trigger:** if the straight projection is **not** among the form's DoF, or if more than one axis is ungrippable → the neutrino-blind-spot claim fails (§⑧ F2). **OUT OF SCOPE:** neutrino mass/oscillation dynamics (PPT11 territory).

### Phase 4 — Consistency: count vs physics, residue placement (AUDIT, ~1 h)

- **Goal:** The derived count must **agree with the number of independent properties physics actually uses** (with the straight one placed as the unmeasurable residue), or the disagreement must be *explained natively*.
- **Method:**
  1. Tabulate the four (or five) grippable properties against the four physics names (mass, charge, flux, EM) and verify a one-to-one map, with Π_∥ explicitly *outside* the grippable set.
  2. If P = 4 grippable + 1 straight, confirm physics' "four fundamental properties" = the four rulers and the neutrino = the residue (clean PASS).
  3. If P predicts a **fifth grippable ruler** physics has not named, state it as a **novel prediction** (what would it grip? does any known instrument secretly already read it?) — Class D novelty, falsifiable.
  4. Independence audit: confirm every "dependent" axis (e.g. v_P) is dependent **by a stated SDT constraint**, not by hand.
- **Metric:** one-to-one map achieved **or** a fifth ruler predicted with a concrete grip mechanism; residue correctly placed as Π_∥. **OUT OF SCOPE:** experimental design for a fifth-ruler search (downstream).

---

## 5. Success Criteria (canonical labels — dual verdict)

- ✅ **PASS (Class A: Derived).** A clean integer property count P emerges from the trefoil/vortex + 28-D DoF with explicit independence tests; the straight projection is the unique zero-grip residue and maps to W=0 (neutrino); the count matches physics' independent rulers (or predicts a fifth with a concrete grip mechanism). **No axis added/removed after seeing "four."**
- ✅ **QUALIFIED (Class C: Convergence).** The count and the residue placement are obtained with 1–2 stated assumptions (e.g. which 28-D components are externally grippable is argued, not proven); map to physics' four holds; fifth-ruler verdict stated with caveat.
- ⚠️ **QUALIFIED PENDING (Class D: Computed).** The framework and the zero-grip residue are derived, but the *integer* rests on an unproven independence claim (e.g. v_P dependence asserted) → ship the count as PENDING with the gap named.
- ❌ **FAIL / OPEN (Class F / OPEN).** No clean count exists (irreducibly ambiguous), **or** the straight projection is not among the DoF, **or** the count disagrees with physics with no native explanation. Do **not** retro-fit to 4.

**Dual verdict (required in `FLM11_VERDICT.md`):** *Prompt completion* (A–F: did P1–P4 execute as written?) **and** *Physics class* (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). Honesty note: this investigation is **partly conceptual**; the *strong, falsifiable* core is the **derived count** and the **fifth-ruler yes/no**.

---

## 6. Outputs

1. **`FLM11_DERIVATION.md`** — the Tape-Measure Lemma (P1) with symbols; the DoF enumeration (P2) with each axis, grip mechanism, property, and independence test; the zero-grip derivation (P3); the physics-consistency table (P4). DERIVED vs ASSUMED flagged per line.
2. **`flm11_ruler_count.cpp`** (or `flm11_ruler_count.py`) — enumerates the form's candidate DoF, applies independence tests (Law V budget, winding W, traction T=3(W+1)), prints the surviving **property count**, the property map, and **flags the single straight/zero-grip residue** (asserts W=0). `#include <sdt/laws.hpp>` only; standalone compile (`cl /std:c++20 /EHsc /O2 /I Engine/include` or `g++ -std=c++20 -IEngine/include`).
3. **`flm11_results.txt`** — machine output: axis table [name | grip mechanism | property | independent? | constraint] + count + residue flag.
4. **`FLM11_VERDICT.md`** — dual verdict + the §⑧ falsification table filled with actual outcomes.
5. **`RUN_LOG.md`** — mandatory: Pre-Run Commitment Block (incl. the **pre-committed integer P** and fifth-ruler prediction), ADJ-### entries, phase gates.

---

## 7. Dependencies & References

**Upstream (required):**
- **PPT08** — angular DoF from the trefoil (the C₃ / circulation axes the count draws on); `law_VI::angular`.
- **FLM01 / `state28d.hpp`** — the 28 components, Levels 5 (Torus T₁–T₅) and 6 (Dynamism Φ₀–Φ₅); which are externally grippable.
- **Law VI / `law_VI::winding`** — W=1 unknot, W=3 trefoil, **W=0 open winding (neutrino)**; Law V budget v_T²+v_P²=c² (the v_P independence test); traction T=3(W+1).

**Downstream (blocked / fed by this):**
- **PPT10 (straight-light)** — the straight projection has no ruler; this supplies the *why*.
- **PPT11 (oscillation)** and the **neutrino-as-blind-spot** program — Π_∥ is the seat.
- **NP18 (resonator / uncommitted cloth)** — the BEC loophole: the one substrate not pre-pinned, reading by coherence/quietness rather than grip.
- **NP19 (mass-defect, two-ledger)** — the same principle in time/boundary form.
- **NP20 (neutron-from-one-seat)** — mass & moment = same defect, two instruments (the Tape-Measure Lemma applied twice).

**Related (parallel set):** NP21 (landscape), APS06 (emission-ladder), SAR05 (provenance).

---

## 8. Falsification Tests

| ID | Hypothesis | Predicted outcome | If FAIL |
|----|-----------|-------------------|---------|
| **F1** | Property count = independent-ruler count (geometric) | DoF enumeration yields the same integer physics uses (4 grippable), each mapped to one ruler | **count ≠ physics' rulers with no native reason → mapping is wrong**; route OPEN, do not retro-fit to 4 |
| **F2** | The straight projection is one of the form's DoF | Exactly one zero-grip axis appears, = through/straight = W=0 | **straight projection NOT among DoF (or >1 zero-grip) → neutrino-blind-spot claim fails**; KILL the identification |
| **F3** | The count is clean (unambiguous integer) | Every candidate axis is decisively independent or dependent by a stated constraint | **count ambiguous → OPEN**; ship framework, withhold the integer |
| **F4** | v_P is *not* an independent ruler | Law V budget v_T²+v_P²=c² fixes v_P given v_T → flux ruler is one, not two | v_P independent → a **fifth** (or different) ruler exists; state as novel prediction (Class D), not a failure of F1 unless physics excludes it |
| **F5** | Committed cloth cannot read Π_∥; only uncommitted cloth (BEC) can | NP18 loophole reads by coherence, not grip | a *committed* instrument reads the straight axis → the "blind spot" thesis is refuted; KILL |

**Recovery:** F1 ambiguous → re-examine which 28-D components are externally grippable (the independence test, not the target). F3 → split the ambiguous axis into a sub-investigation; do not average. Never widen the "clean integer" requirement post-run.

---

## 9. Implementation Notes

- **This is a counting/structure tool, not a numeric-fit tool.** The core output is an **integer** and a **map**, not a value compared to CODATA. Keep `double` only for the independence tests (e.g. checking v_T²+v_P²=c² closes), and prefer exact integer/boolean logic for the count itself.
- **Encode axes as records**, each with: name, grip mechanism (enum: RESISTANCE / HANDEDNESS / CIRCULATION / OSCILLATION / NONE), property string, and an `independent()` predicate that references an SDT constraint (Law V budget, winding W, T=3(W+1)). The count = number of records with grip ≠ NONE and `independent() == true`; the residue = the single record with grip == NONE.
- **Pre-commit before coding** (anti-post-hoc): write the predicted integer P and the fifth-ruler yes/no into `RUN_LOG.md` *first*; the tool must then reproduce it. If it does not, that is a finding, not a bug to silence.
- **No borrowed units / no charge-substance** in any print line (R2/R3): say "handedness ruler," not "charge meter reading μ_B."
- **Symbols, not pictures:** the Lemma in `FLM11_DERIVATION.md` must carry Π_a, ⟨L,a⟩, Π_∥ explicitly so the claim is checkable.
- **Visual aid (optional):** a small table/figure of the configuration-space axes with the zero-grip residue marked — but the verdict rests on the table, not the figure.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FLM11
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 — none permitted; this is a count, not a fit]
- Engine namespaces: law_VI::winding (W=0/1/3), law_VI::angular (C₃), Law V budget, FLM01/state28d (Levels 5–6)
- PRE-COMMITTED COUNT P: [state the integer BEFORE running — e.g. 4 grippable + 1 straight]
- FIFTH-RULER PREDICTION: [YES (with grip mechanism) | NO (v_P dependent via Law V)]
- Independence tests to apply: [Law V v_T²+v_P²=c²; winding W; T=3(W+1); external-grippability of T₁–T₅/Φ₀–Φ₅]
- Phase gates: P1 (Lemma stated, symbols) → P2 (count = pre-commit) → P3 (exactly one zero-grip = W=0) → P4 (map to physics' four)
- Forbidden retroactive changes: add/remove an axis after seeing "four"; round an ambiguous count; widen the "clean integer" rule; call charge a substance; import a Lie-group dimension as the derivation
```

### Pivot table (minimum — extend as needed)

| Trigger (numeric/structural) | First response (PIVOT) | If pivot fails | Forbidden |
|------------------------------|------------------------|----------------|-----------|
| P1 Lemma cannot be stated cleanly (cross-axis leak) | Tighten Π_a definition; restrict to externally grippable axes | **OPEN** the definition; report blocker | Hand-wave the Lemma to proceed |
| P2 enumerated count ≠ pre-committed integer | Re-audit the *independence tests* (is v_P fixed by Law V? is T₁ externally grippable?), document ADJ-### | **OPEN** the count (F3); ship framework, withhold integer | Add/remove an axis to hit 4 (RETRO-PASS) |
| P2 count is ambiguous (axis neither in nor out) | Split the ambiguous axis into a sub-question; mark PENDING | **OPEN**; do not force a number | Average / round to 4 |
| P3 zero zero-grip axes, or >1 | Re-derive grip mechanism per axis; check W=0 line is included | **KILL** the neutrino-blind-spot identification (F2) | Declare PASS with a fuzzy residue |
| P3 straight axis present but not W=0 | Re-check `law_VI::winding` mapping; ADJ-### | **OPEN** the identification | Assert W=0 without the mapping |
| P4 count disagrees with physics' four | Test for a native fifth ruler (F4); state as Class D novelty | **OPEN** (F1) — mapping wrong | Retro-fit to 4 |
| A Lie-group / SU(N) dimension coincides with the count | Label **CONVERGENCE**, not derivation | — | Claim Class A from the coincidence |

### Allowed adjustments
- Refine *which* 28-D components are externally grippable (the test, not the target); split an ambiguous axis (P2a/P2b); fix a filename via ADJ entry; tighten the independence predicate.

### Disallowed adjustments
- Post-hoc change to the pre-committed integer; rounding an ambiguous count; widening the "clean integer" / "exactly one zero-grip" rules; charge-as-substance or borrowed-unit phrasing; importing G/M/GM, ψ, gauge fields, or a symmetry-group dimension into the derivation chain.

### Dual verdict reminder
Report **both** axes in `FLM11_VERDICT.md`: *Prompt completion* (A–F) and *Physics class* (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). A clean derived integer + correct residue placement is NATIVE; a count that merely *ties* a known group dimension is CONVERGENCE; an ambiguous count is OPEN, never a quiet PASS.

---

*FLM11 · SPEC · the strongest general result of the session: the rulers carry the properties, and the straight projection carries none. Execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
