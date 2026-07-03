# PPT10 — The Neutrino as Straight Light: pitch = grip and the coupling gap

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).

---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether the neutrino is the **zero-pitch limit of the emission ladder**
   (the electron driven all the way onto the proton surface — *straight light*) and, if so, whether
   its ~20-order-of-magnitude weaker interaction follows from a single law **coupling = f(transverse
   pitch)** as pitch → 0 — **without** importing the weak charged current, `G_F`, a virtual W, or
   wavefunctions. The hinge is Harvey's working hypothesis: **charge-coupling IS the transverse
   pitch**, so straightening far enough genuinely removes the grip.
2. **Why does it matter?** — This is the deepest rung below the nuclear gamma (APS06 ladder) and the
   spine of the whole neutrino set. If it holds, `neutrino.hpp`'s "W=0 open winding, propagates *with*
   the relay" gets a *mechanism* (the geometric wake-dilution narrative becomes a derived coupling
   law), PPT11 inherits a pitch axis to precess along, and NP18 gets a falsifiable grounding
   prediction (νₑ→e⁻ with no mediator). If it fails, the no-mediator weak picture weakens and the
   coupling gap stays an admitted debt.
3. **How will we find out?** — Four gated phases: define **transverse pitch** quantitatively for a
   wake/vortex emission and the straight limit (P1); derive **how cross-section must scale as
   pitch→0** and pre-commit the supporting functional form (P2); confront the **~20-order coupling
   gap** — locate where intermediate-pitch emissions *should* sit and decide **CONTINUOUS vs SNAP**
   by a pre-committed rule (P3); state the **νₑ→e⁻ direct-grounding** SDT prediction NP18 will test,
   distinct from the SM (P4).
4. **What would prove us wrong?** — §⑧, numeric. If straightening **cannot in principle** reduce
   coupling (a straight photon is still a photon, spin-1, grips charge) ⇒ **KILL** straight-light.
   If continuous pitch is **required** but the middle of the gap is **provably empty** AND no
   admissible snap mechanism exists ⇒ pitch=grip is in serious trouble (**OPEN**/park, sharpened fork
   shipped, not a closure).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase. The honest target may be a
   **SHARPENED FORK**, not a PASS; a fired falsifier is never repainted.

### Anti-tautology firewall (read before P2)

The load-bearing claim is that **the weak interaction is geometry, not a coupling constant**:
cross-section falls because the wake is straightened, not because a small number `G_F` is inserted.
Recovering the observed ~20-order suppression by *fitting* a `pitch ↦ σ` exponent to hit the neutrino
point is an **IDENTITY-PASS** and caps the grade at **C** (row IMPORTED). The functional form of
σ(pitch) must be **pre-committed in P2 before** the neutrino value is looked at. `G_F`, a virtual W,
flavour quantum numbers, and wavefunctions are **PROHIBITED inputs to the SDT chain** — they appear
only as an **OBSERVED comparison column**. No "charge radius" / charge-as-substance: charge is
**handed redirection** (EMC03), `e` is a **unit-bridge**, and what straightens is the *transverse
displacement geometry* of the wake, not an amount of charge.

---

## ① Executive Summary

The continuous beta spectrum is the 1930 Pauli puzzle: in a β⁻ event the electron and antineutrino
**share 0.782 MeV smoothly**, a *continuum* not a line. SDT reads this exactly as **violently driven
free charge radiates a continuum** — the split is set by how the movement divides, not by a fixed
ladder rung. **Hypothesis:** the neutrino is the **deepest rung of the emission ladder** (below the
nuclear gamma, APS06) — the electron driven *all the way* onto the proton surface, the straightest,
shortest-pitch emission: **straight light, zero transverse pitch**. The obstacle, stated honestly: a
photon at *any* energy is spin-1 and grips charge (lead stops gamma), yet a neutrino passes a
light-year of lead. Straightening does not *obviously* switch off coupling. This investigation
formalises **transverse pitch**, tests **coupling = f(pitch)** as pitch→0, confronts the **~20-order
gap with apparently nothing in the middle** (CONTINUOUS vs SNAP fork), and states the SDT **νₑ→e⁻
grounding** prediction that NP18 tests against the SM. **Expected outcome:** either a derived
suppression law or — honestly — a **sharpened, falsifiable fork**.

---

## ② Physical Context

Picture the emission ladder as a staircase of pitches. A bound electron jolted between atomic levels
sheds a long-pitch helical wake — a soft photon, lots of sideways throw. Drive the jolt harder
(nuclear transitions, APS06 rungs) and the pitch shortens, the wake tightens toward the line of
travel. Push to the extreme — the electron driven onto the proton surface in β decay — and the wake
goes **straight**: zero transverse throw, all forward. That straight-running thing is the neutrino.

**The key variables:**

| Symbol | Meaning | Dimension / range |
|--------|---------|-------------------|
| `p_T` | **transverse pitch** — the wake's sideways advance per unit forward advance (a geometric tilt, defined in P1) | dimensionless (tan of a wake angle), `p_T ∈ [0, p_T^max]`; **straight light = `p_T → 0`** |
| `θ_w` | wake half-angle of the emission cone | rad; `p_T = tan θ_w` (working definition, P1 fixes it) |
| `R_wake` | wake radius `ℏ/(mc)` (`neutrino.hpp::wake_radius`) | m; ν₁ ≈ 9.87 µm |
| `R_excl` | exclusion (body) radius | m; ν₁ ≈ 9.77e-24 m |
| `σ` | interaction cross-section (the **grip**) | m²; the ~20-order axis |
| `W` | winding number (`law_VI`) | electron W=1, proton W=3, **neutrino W=0 (open winding)** |
| `f(p_T)` | the coupling law to be derived: `σ ∝ f(p_T)` | — |

**Why this matters to SDT:** `neutrino.hpp` already *asserts* "W=0 → no toroidal flow → no charge
(ℓ=1) → no moment (ℓ=2) → propagates *with* the relay → near-zero interaction," and quantifies it via
the wake/body ratio `R_wake/R_excl ≈ 1e18` (the largest of any particle). That is a **geometry
narrative**; PPT10's job is to turn "propagates with the relay" into a **coupling law in pitch** and
to confront the one thing the narrative skips: **why is the gap empty between photon and neutrino?**
This sits directly above PPT04 (μ_ν ≡ 0), feeds PPT11 (oscillation as pitch precession), and arms
NP18 (the grounding experiment).

---

## ③ Theoretical Framework

**Building on (SDT, permitted):**

- **Law V — movement budget** (`law_V`): `v_circ² + v² = c²` (and the transverse/forward partition).
  Pitch lives here: a straight emission spends its whole budget forward; a long-pitch emission spends
  some sideways. P1 must express `p_T` through the Law-V partition, **not** as a free angle.
- **Law VI — winding** (`law_VI`): the discrete `W` spectrum; **W=0 = open winding** that never
  closes — the topological home of "no toroidal circuit" and hence (PPT04) no ℓ=1 charge wake, no
  ℓ=2 moment. Straight light is the **W=0** emission limit.
- **`neutrino.hpp`**: `W_neutrino = 0`; `wake_radius(m)=ℏ/(mc)`; the `R_wake/R_excl ≈ 1e18` dilution;
  oscillation as "three stable pitch angles of the open winding." **Reuse these symbols — do not
  redefine them locally** (§0 anti-creep).
- **OP04 — transverse-wake polarisation**: an emission carries a **transverse displacement vector**;
  its orientation is polarisation. PPT10's `p_T` is the *magnitude/tilt* of that same transverse
  channel; the straight limit is its vanishing. P1 must tie to OP04's transverse vector so pitch and
  polarisation are the **same geometry seen two ways**.
- **APS06 — emission ladder**: the rungs *above* the neutrino (atomic → nuclear gamma). PPT10 is the
  bottom rung. Cross-reference: the ladder's monotone in pitch must reach `p_T→0` at the neutrino.
- **Beta spectrum (measured anchor):** the **0.782 MeV** β⁻ endpoint shared *continuously* — used as
  DATA (continuum ⇒ driven-radiation, not fixed-line), never as the SM neutrino story.

**Constraints (hard):** only `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in measured
units. **PROHIBITED in the SDT chain:** `G_F`, virtual W / charged current, flavour quantum numbers,
wavefunctions, fields-as-primitives, quarks/gluons, virtual particles as objects, dark matter/energy,
ΛCDM, duality. The neutrino is a **HARD, localised, solid STRAIGHT vortex** — never a cloud or a
probability amplitude. No "charge radius"; charge = handed redirection, `e` = unit-bridge.

---

## ④ Investigation Strategy (excessive by design — implement without guessing)

> Gate rule: Phase N+1 forbidden until Phase N is **PASS-GATE** or an explicit **DEFER/OPEN** is
> logged in `RUN_LOG.md`. Every printed number carries one ledger tag (§ protocol 5).

### Phase 1 — Define transverse pitch and the straight (zero-pitch) limit  *(≈2–3 h)*

- **Goal (measurable):** a single, dimensioned definition of **`p_T`** for a wake/vortex emission,
  monotone along the APS06 ladder, with the straight limit `p_T → 0` identified as the **W=0**
  neutrino, and an explicit map to OP04's transverse vector.
- **Method:**
  1. From **Law V**, write the emission's budget split as forward `v_∥` and transverse `v_⊥` with
     `v_∥² + v_⊥² = c²` for the wake impulse; define `p_T ≡ v_⊥ / v_∥ = tan θ_w`. State dimensions
     (dimensionless) and range (`p_T ∈ [0, p_T^max]`).
  2. Tie `v_⊥` to OP04's transverse displacement amplitude (pitch = magnitude of the transverse
     channel; polarisation = its orientation). Confirm the straight limit `v_⊥→0` ⇒ `p_T→0` ⇒
     transverse channel vanishes — **consistent with PPT04's ℓ=2 = 0 and `neutrino.hpp` W=0**.
  3. Anchor the ladder: assign `p_T` (or its proxy) to ≥3 rungs — a soft atomic photon, a nuclear
     gamma (APS06), the neutrino — and show **monotone decrease** to the neutrino.
- **Pre-committed success metric:** definition is dimensionally consistent; `p_T` is **monotone
  non-increasing** down the three named rungs to the neutrino (no rung inversion); the W=0 limit
  reproduces `p_T = 0` and recovers the `neutrino.hpp` wake/body ratio order (`R_wake/R_excl ~ 1e18`)
  to within **±1 order of magnitude** as a sanity tie.
- **Failure trigger:** `p_T` cannot be built from Law V without a free angle (i.e. needs a fitted
  tilt), OR the ladder is non-monotone ⇒ **PIVOT** to defining `p_T` via the geometric wake angle of
  `R_wake/R_excl` directly (still native). If that also fails ⇒ **OPEN** the pitch definition; do not
  proceed to P2 on an unfounded `p_T`.
- **OUT OF SCOPE (P1):** any coupling/cross-section number (that is P2); oscillation precession (PPT11).

### Phase 2 — Coupling = f(pitch): derive the σ(pitch→0) scaling  *(≈3–4 h)*

- **Goal:** derive how interaction cross-section `σ` **must** scale with `p_T` if grip = pitch, and
  **pre-commit** (before viewing the neutrino σ) what functional form counts as *supporting*.
- **Method:**
  1. Native mechanism first: model the grip as the wake's ability to **occlude/redirect** an incoming
     relay — coupling ∝ the transverse footprint of the wake. As `p_T→0` the transverse footprint
     collapses; derive `σ ∝ f(p_T)` from that geometry (candidate native forms: `σ ∝ p_T²` from a
     transverse-area argument, or `σ ∝ p_T^n`; the **exponent must come from geometry, not a fit**).
  2. **Pre-commit the supporting envelope in `RUN_LOG.md` before** reading any neutrino value:
     declare the admissible family (e.g. monotone power-law `σ ∝ p_T^n`, `n` fixed by the
     transverse-area derivation) and the band that counts as a match.
  3. Evaluate at the three ladder rungs. Compare the **predicted** photon→neutrino suppression to the
     **observed** ~20-order ratio (photon σ vs neutrino σ as an **OBSERVED column**).
- **Pre-committed success metric:** the **derived** (un-fitted) exponent reproduces the observed
  photon→neutrino suppression to within **±2 orders of magnitude** (i.e. predicts a ~18–22 order drop
  from the geometry alone). Tighter than ±2 orders with a fitted exponent does **not** count.
- **Failure trigger:** the only way to hit 20 orders is to **fit** `n` to the neutrino point ⇒
  **IDENTITY-PASS**, cap grade at **C** (row IMPORTED); record honestly. If straightening **increases
  or fails to decrease** `σ` ⇒ **KILL** straight-light (a straight photon would still grip) — this is
  the hypothesis's existential test, do not rescue.
- **OUT OF SCOPE (P2):** explaining the *emptiness* of the gap (P3); the grounding prediction (P4).

### Phase 3 — Confront the ~20-order gap: CONTINUOUS vs SNAP  *(≈3–4 h — the real tension)*

- **Goal:** decide, by a **pre-committed rule**, whether grip continuously straightens (predicting
  **intermediate-pitch, half-stoppable emissions** that must exist somewhere) or whether pitch
  **SNAPS** past a threshold (re-introducing a quantisation Harvey is otherwise trying to dissolve).
- **Method:**
  1. From P2's σ(p_T), compute **where** an emission of intermediate pitch should sit on the σ axis —
     i.e. what `p_T` yields σ a few orders below the photon (a *half-gripping*, partly-stoppable
     emission). Tabulate the predicted (p_T, σ) of the "missing middle."
  2. **Seek occupants of the middle** in known DATA before declaring it empty: very soft / strongly
     forward (collinear) radiation; coherent forward scattering; mislabelled or
     hard-to-detect low-σ channels. Ask: are intermediate-pitch emissions **real but mislabelled**,
     or genuinely absent?
  3. **Pre-committed decision rule (write to `RUN_LOG.md` before searching):**
     - **CONTINUOUS** if the predicted middle is **populated** (≥1 credible occupant within the
       predicted (p_T, σ) band) OR P2's law smoothly bridges photon↔neutrino with no forbidden region
       — pitch=grip survives, gap is a detection/labelling artefact.
     - **SNAP** if the middle is **provably empty** AND a **native** threshold mechanism is admissible
       (e.g. W=0 is topologically *discrete* — open vs closed winding is not continuously
       deformable; `law_VI`/PPT09 reconnection forbids a half-open winding). The snap must be
       **derived from topology**, not asserted to save the model.
     - **UNRESOLVED → OPEN** if the middle is provably empty **and no admissible snap mechanism**
       exists ⇒ ship a **sharpened fork**, park pitch=grip; **do not retro-PASS**.
- **Pre-committed success metric:** a decision (CONTINUOUS / SNAP / OPEN) reached **against the
  pre-written rule**, with the (p_T, σ) coordinates of the predicted middle and either a named
  occupant or a topological snap derivation. Honesty is the metric here — a defended OPEN is a valid
  outcome.
- **Failure trigger:** if SNAP is invoked **without** a topological derivation (i.e. a bare threshold
  to save the fit) ⇒ that is a forbidden PLUG ⇒ **OPEN** instead. Do not paper over the gap.
- **OUT OF SCOPE (P3):** the grounding experiment design (P4 / NP18).

### Phase 4 — The νₑ→e⁻ direct-grounding prediction (the NP18 test)  *(≈2 h)*

- **Goal:** state SDT's **falsifiable** prediction for direct neutrino→electron conversion by
  *grounding*, distinct from the SM, as the spec NP18 will execute.
- **Method:**
  1. SDT claim: a neutrino is **straight-running electron-stuff**. Hit a **gapless wall** (no gap to
     thread the straight thread through) and the thread **cannot stay straight** — it **grounds into a
     wiggling electron** (`νₑ → e⁻`), **no mediator**. State the geometric condition for "gapless"
     (lattice with no through-channel at the incoming pitch) and what observable marks a grounding
     event (an electron appearing with the neutrino's forward energy, continuum-distributed).
  2. **SM comparison (OBSERVED column only):** flavour is conserved at the vertex; an electron arises
     only via the **weak charged current through a virtual W** — **direct free νₑ→e⁻ conversion is
     forbidden**. Tag `G_F`/W as OBSERVED-TARGET, never in the SDT chain.
  3. State the **discriminating observable**: SDT predicts a grounding rate set by wall gaplessness
     (geometry), continuum electron energy; SM predicts the standard CC rate (`∝ G_F²`) with no
     direct conversion channel. Hand the numeric design to **NP18**.
- **Pre-committed success metric:** a single sentence each for SDT and SM prediction that **differ in
  an observable** (presence/absence of a direct, mediator-free conversion channel and its energy
  spectrum), plus the gaplessness condition expressed in SDT variables (pitch + lattice channel).
- **Failure trigger:** if SDT and SM predictions are **observationally identical** (degenerate) ⇒
  label **DEGENERATE**; NP18 cannot discriminate, say so. If grounding requires a mediator after all
  ⇒ the "no mediator" claim weakens ⇒ **OPEN** and flag to NP18.
- **OUT OF SCOPE (P4):** building NP18's apparatus model (that is NP18); oscillation (PPT11).

---

## ⑤ Success Criteria (canonical labels + dual verdict)

- ✅ **PASS (Class A — NATIVE):** `p_T` defined from Law V (P1); σ(p_T) exponent **derived, un-fitted**,
  reproducing the ~20-order suppression to ±2 orders (P2); a defended CONTINUOUS **or** topologically
  derived SNAP verdict (P3); a genuinely discriminating νₑ→e⁻ vs SM prediction (P4). **Zero fits.**
- ✅ **QUALIFIED (Class C — CONVERGENCE):** the suppression law reproduces the gap order but only with
  a transverse-area exponent that *coincides with* the observed slope (convergence, delete-test
  defended), or material/rung σ values taken as MEASURED-INPUT. Row IMPORTED where a form is fitted.
- ⚠️ **QUALIFIED PENDING (Class D — COMPUTED):** P1+P2 deliver a pitch axis and a monotone σ(p_T) to
  order, but P3 lands **OPEN** (gap unresolved) — shipped as the **sharpened fork**. *This is an
  acceptable, honest deliverable.*
- ❌ **FAIL (Class F / KILLED):** straightening cannot in principle reduce coupling (P2 KILL), or
  pitch cannot be built natively (P1 OPEN with no route) ⇒ straight-light is not viable as stated.

**Dual verdict (mandatory in `PPT10_VERDICT.md`):**

| Axis | Grades |
|------|--------|
| **Prompt completion** | A / B / C / D / F — did the tool do P1–P4 as written? |
| **Physics class** | NATIVE / CONVERGENCE / DEGENERATE / KILLED / **OPEN (sharpened fork)** |

---

## ⑥ Outputs

| File | Format | Contents |
|------|--------|----------|
| `PPT10_DERIVATION.md` | Markdown | P1 pitch definition (Law V + OP04 tie); P2 σ(p_T) derivation with DERIVED-vs-ASSUMED flags; P3 missing-middle table + CONTINUOUS/SNAP/OPEN reasoning; P4 grounding prediction. Every step tagged. |
| `ppt10_pitch_coupling.cpp` (or `.py`) | C++20 / Python | Computes σ(p_T) curve across the ladder; prints photon, intermediate, neutrino rungs; marks **where the gap sits** and the predicted (p_T, σ) of the missing middle; OBSERVED photon/neutrino σ comparison column. `#include <sdt/laws.hpp>` only; reuse `neutrino.hpp` symbols; ledger tag every printed number. |
| `ppt10_results.txt` | Text | stdout capture: rung table, σ(p_T) values, gap coordinates, CONTINUOUS/SNAP verdict line. |
| `PPT10_VERDICT.md` | Markdown | Dual verdict header; §⑧ falsification table updated with fired/parked; honest statement if deliverable is the sharpened fork. |
| `RUN_LOG.md` | Markdown | Pre-Run Commitment Block (§⑩), the **pre-committed** P2 σ-form and P3 decision rule (timestamped before search), ADJ-### entries, phase gates. |

---

## ⑦ Dependencies & References

**Upstream (required):**
- **PPT04** — μ_ν ≡ 0 (W=0 → no ℓ=2 wake): the topological no-moment result PPT10 extends to no-grip.
- **`neutrino.hpp`** — W=0 open winding, `wake_radius`, `R_wake/R_excl ~ 1e18`, "propagates with the
  relay." Reuse symbols; do not redefine.
- **APS06** — emission ladder: the rungs above the neutrino; supplies the monotone-pitch context.
- **Law V** (`law_V`, movement budget) and **Law VI** (`law_VI`, winding) in `laws.hpp`.
- **OP04** — transverse-wake polarisation: `p_T` is the magnitude of OP04's transverse channel.

**Downstream (blocked until this ships a pitch axis):**
- **PPT11 — oscillation** (the hardest open): pitch precession needs P1's `p_T` axis.
- **NP18 — resonator / grounding experiment**: needs P4's νₑ→e⁻ prediction to design the test.

**Related (informative):** PPT09 (winding stability / reconnection — the topological snap source for
P3); EMC03 (handed redirection — keeps "charge" out of the prose); FLM11 (tape-measure — the straight
projection has no ruler); SAR05 (provenance).

---

## ⑧ Falsification Tests (each states the number/condition that kills it)

| ID | Test | SDT prediction | The number/condition that kills it |
|----|------|----------------|-------------------------------------|
| F1 | **Pitch is native** (P1) | `p_T` built from Law V budget; monotone down the ladder to `p_T=0` at the neutrino | `p_T` needs a fitted free angle, OR the ladder is non-monotone ⇒ pitch is not a Law-V quantity ⇒ **OPEN** P1 |
| F2 | **Straightening reduces grip** (P2) | `σ` monotonically **decreases** as `p_T→0` | `dσ/dp_T ≤ 0` fails (σ flat or rising as pitch→0) ⇒ a straight photon still grips ⇒ **KILL** straight-light |
| F3 | **Suppression from geometry** (P2) | un-fitted exponent gives an 18–22 order photon→neutrino drop | the 20 orders only reachable by **fitting** `n` to the neutrino point ⇒ **IDENTITY-PASS**, grade capped **C** |
| F4 | **The empty middle** (P3) | either the predicted intermediate-pitch band is **populated**, or a **topological** snap (W=0 discrete) forbids it | middle **provably empty** AND **no** topological snap admissible ⇒ pitch=grip in serious trouble ⇒ **OPEN**/park (sharpened fork) |
| F5 | **Snap honesty** (P3) | if SNAP, it is **derived** from `law_VI`/PPT09 (open vs closed winding not continuously deformable) | SNAP asserted as a bare threshold to save the fit ⇒ forbidden PLUG ⇒ relabel **OPEN** |
| F6 | **νₑ→e⁻ discriminates** (P4) | SDT: direct mediator-free grounding at a gapless wall, continuum electron energy; SM: forbidden (CC/virtual-W only) | SDT and SM **observationally identical** ⇒ **DEGENERATE**; NP18 cannot test ⇒ say so |
| F7 | **No smuggling** | the whole chain runs on pitch + winding + wake geometry | any result needs `G_F`, a virtual W, flavour numbers, or a wavefunction as **mechanism** (not OBSERVED column) ⇒ no-mediator claim fails here |

---

## ⑨ Implementation Notes

- **Double precision** throughout; the σ axis spans ~20+ orders — work in **log₁₀(σ)** and in
  **dimensionless ratios** (σ_photon/σ_ν, p_T relative to `p_T^max`) to avoid overflow/underflow.
- **Reuse, don't redefine:** pull `c, ℏ, m_e, m_p, ℓ_P` from `sdt::laws::measured`, wake radii and
  W=0 from `sdt::neutrino`. A locally re-declared constant is a §0 anti-creep fail.
- **Order of operations matters for honesty:** write the P2 σ-form and P3 decision rule into
  `RUN_LOG.md` **before** reading the neutrino σ or searching the middle. The pre-commit timestamp is
  the anti-IDENTITY-PASS evidence.
- **Plots that inform:** (1) `log₁₀σ` vs `p_T` across the ladder — is the photon→neutrino bridge a
  smooth curve (CONTINUOUS) or a step (SNAP)? (2) the **missing-middle marker**: shade the predicted
  intermediate-pitch (p_T, σ) band and overlay any known occupant. (3) `p_T` vs ladder rung (APS06) —
  monotone check for F1.
- **Ledger every print** (`DERIVED` / `COMPUTED` / `CALIBRATED(n)` / `OBSERVED-TARGET` / `MEASURED-INPUT`
  / `ASSUMED` / `PENDING`). The photon and neutrino measured σ are **OBSERVED-TARGET**; the derived
  exponent is **DERIVED**; any fitted slope is **CALIBRATED(1)** and caps the grade.
- **Watch for the trap:** "a straight photon is still a photon" is the strongest objection — make P2
  confront it head-on (F2), not assume it away. The honest win may be the **sharpened fork**, not a PASS.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT10
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN(sharpened fork)]
- CALIBRATED budget: 0 in the σ(p_T) exponent chain (rung σ values = OBSERVED/MEASURED if used)
- Engine namespaces used: law_V (budget), law_VI (winding W=0), sdt::neutrino (wake_radius, R_wake/R_excl)
- P2 σ-form PRE-COMMITTED (write BEFORE viewing neutrino σ): σ ∝ p_T^[n], n from transverse-area geometry; supporting band = ±2 orders on the 20-order suppression
- P3 decision rule PRE-COMMITTED (write BEFORE searching the middle):
    CONTINUOUS if predicted (p_T,σ) middle populated (≥1 credible occupant) or smooth bridge;
    SNAP only if middle provably empty AND topological snap derived from law_VI/PPT09;
    else OPEN (ship sharpened fork)
- Phase thresholds: P1 monotone + dimensional + ±1 order wake-ratio tie · P2 un-fitted ±2 orders, dσ/dp_T<0
    · P3 decision against pre-written rule · P4 SDT≠SM observable stated
- Forbidden retroactive changes: fit n to the neutrino point then claim A; assert a bare snap to save the fit;
    import G_F / virtual-W / flavour / wavefunction into the SDT chain; widen tolerances; IDENTITY-PASS;
    local constant namespaces; say "charge radius"
```

### Pivot table (numeric triggers)

| Trigger (numeric/condition) | PIVOT (first) | If pivot fails | Forbidden |
|------------------------------|---------------|----------------|-----------|
| P1 `p_T` needs a fitted angle | derive `p_T` from the wake angle of `R_wake/R_excl` (still native) | **OPEN** pitch definition; stop at P1 | invent a tilt to fit the ladder |
| P1 ladder non-monotone | recheck rung assignment (APS06); use the geometric wake-angle proxy | **OPEN**; do not build σ(p_T) on it | reorder rungs to force monotone |
| P2 20 orders only via fitted `n` | tag **CALIBRATED(1)**, grade **C**, row IMPORTED | — | call the fitted exponent DERIVED |
| P2 `dσ/dp_T ≥ 0` as `p_T→0` | recheck transverse-footprint geometry | **KILL** straight-light (report) | rescue with a sign flip / extra factor |
| P3 middle provably empty | seek occupants (soft/forward/mislabelled); else derive topological SNAP from `law_VI`/PPT09 | **OPEN** (sharpened fork) | assert a bare threshold (PLUG) |
| P4 SDT≡SM observably | state the result honestly | label **DEGENERATE**; flag NP18 | claim discrimination that isn't there |
| Any step needs `G_F`/W/flavour/ψ | re-express via pitch + winding + wake | **OPEN**/KILL the no-mediator claim, report it | smuggle the weak vertex into the chain |

### Allowed adjustments

- Finer numerics (log-axis, bracket, rung sampling); phase splits (P2a area-geometry / P2b rung
  evaluation; P3a prediction / P3b search); filename fix via ADJ-### entry.
- Alternative **native** routes already listed in §④ (wake-angle proxy for `p_T`; topological snap
  from `law_VI`/PPT09 for the gap).

### Disallowed adjustments

- Post-hoc tolerance widening · fitting the σ(p_T) exponent then claiming NATIVE · bare-threshold snap
  to save the fit · importing `G_F`/virtual-W/flavour/wavefunction into the SDT chain · `atomic::`/GM/G
  wrapper as a "mechanism" · "charge radius" / charge-as-substance · local constant namespaces.

---

*PPT10 · SPEC · 1 of 9 (siblings: NP18, NP19/NP20, NP21, PPT11, FLM11, APS06, SAR05) ·*
*execute with `PROMPT_EXECUTION_PROTOCOL.md`. The coupling gap is a real debt — the deliverable may be a sharpened fork, not a closure.*
