# NP19 — Mass-Defect as Form-Resistance + the Two-Ledger Lemma (Derivation)

> **Author:** J. C. Harvey, Melbourne.
> **Status:** RESULT — a **named reframe**, Class C (Convergence).
> **Engine:** all numbers from `sdt::laws::measured` + `law_I` + `law_IV`. No local constants.
> **Step tags:** `DERIVED` · `ASSUMED` · `IDENTITY` · `OBSERVED-TARGET`.

**Up-front honesty (read before anything else).** This document is a *reframe*, not a derivation of a new constant. Its arithmetic core — `1.293 − 0.511 = 0.782 MeV` — is an **exact identity among three measured anchors** (`m_n`, `m_p`, `m_e`), not a prediction. What NP19 *adds* is (i) a named reading of `m c²` as **form-resistance**, shown to be constant-free; (ii) a proven **sign** (bound = higher resistance); and (iii) a promoted **Two-Ledger Lemma** with a working falsifier. Nothing here beats the Standard Model on a number. It *dissolves* the "mass↔energy interchange" mystery by exhibiting one substrate read two ways.

---

## 1. Axiom — Law IV, read as resistance  `[IDENTITY]`

Verbatim from `laws.hpp` (`law_IV`):

```
m = Φ · V_disp / (3 · l_P³ · c²)          (mass_from_V_disp)
V_disp = 3 · m · l_P³ · c² / Φ            (V_disp_from_mass)
```

Mass is the throughput-reorganisation cost of holding a form. NP19 **renames** the rest energy:

> **`R(form) ≡ m(form) · c²`** — the form's total rest energy *is* its accumulated **form-resistance** (grip per Planck-volume per tic). `[ASSUMED reading — a renaming with a claim]`

**Delete-test (Phase 1).** Calling `m c²` a *resistance* introduces **no new constant** and changes **no number**. Proof, from the tool:

- Law IV round-trip `m → V_disp → m` is the identity to machine epsilon for e, p, n (rel err `1.9e-16`, `2.1e-16`, `4.3e-16`). `[IDENTITY]`
- Define `ρ_form ≡ R(form)/V_disp`. For the electron:
  `ρ_form_e = m_e c² / V_disp_e = 8.2027e47 Pa`, and the engine's marginal-stability scale is `P_conv/3 = 8.2027e47 Pa`. **Ratio = 1.000000.** `[IDENTITY]`
  This is *not* a new success — it is exactly the pre-existing `P_cf_e` identity `ρ_eff_e · c² ≡ P_conv/3` (laws.hpp:485). It confirms the resistance reading lands **on the engine's own dial**, not near a new one.

**Conclusion (Phase 1).** The resistance reading is **constant-free**. `m_inert = m_grav` follows trivially because both read the same `V_disp`/grip — no separate mechanism. `[DERIVED — as a consistency statement, not a new number]`

---

## 2. Resistance-difference accounting — the mass defect  `[IDENTITY]`

For a transformation `A → B_forms + (movement)`, define

> **`ΔR ≡ R(A) − R(B_forms)`** ,  and the movement carried away  **`Q = ΔR − τ`** ,

where `τ` is the **manufacturing toll** for any *new* form that must be built. The transformation runs **iff `ΔR > 0`** — the SDT statement of spontaneity (path of least resistance). **No external feed, no battery, no toll-collector at the event:** the surplus is *already* the difference in grip.

**The mass defect is `ΔR` — a resistance difference — not stored binding energy.** This is the whole reframe. `[ASSUMED reading]`

---

## 3. The three numbers as ONE landscape + the flipped sign  `[IDENTITY + sign DERIVED]`

From `measured::` masses (rest energies via `× c² ÷ MeV_to_J`; `m_n − m_p` subtracted in kg first):

| Quantity | Expression | Value (MeV) | Tag |
|---|---|---|---|
| `R(n)` | `m_n c²` | 939.56542 | DERIVED (from measured `m_n`) |
| `R(p)` | `m_p c²` | 938.27209 | DERIVED (from measured `m_p`) |
| `τ` | `m_e c²` (the TOLL) | 0.51100 | DERIVED (from measured `m_e`) |
| `ΔR` | `R(n) − R(p)` | **1.29333** | IDENTITY (subtraction of anchors) |
| `Q` | `ΔR − τ` | **0.78233** | IDENTITY (subtraction of anchors) |

**Comparison to observed anchors (OBSERVED-TARGET — never inputs):**
`ΔR` vs 1.293 MeV → rel err `2.6e-4` (0.026%). `Q` vs 0.782 MeV → rel err `4.3e-4` (0.043%). Landscape check `τ + Q = 1.29333 = ΔR` exactly.

**The flipped-sign neutron (the crux, T1).**

- `R(n) = 939.56542 > R(p) = 938.27209` ⟹ **`ΔR = +1.293 MeV > 0`.** `[DERIVED sign]`
  The *bound/heavier* neutron-form is the **higher-resistance** form (consistent with NP14 larger-V_disp). A free neutron is therefore *uphill — a running over-payment (higher maintenance rate)*; it relaxes spontaneously — no trigger. *(word "stored" repaired — interchange sweep 2026-07-07, Harvey-authorized)*
- Toll to build the daughter electron form: `τ = m_e c² = 0.511 MeV`.
- Exhaust: `Q = ΔR − τ = 0.782 MeV` — the measured β⁻ endpoint.
- **Spontaneity inequality:** decay runs iff `ΔR > τ`. Here `1.293 > 0.511` ⟹ TRUE. If instead `ΔR < τ`, the free neutron-form would be stable — the SM threshold condition, here read as a least-resistance inequality, **not imported**. `[DERIVED as an inequality; the numbers themselves are measured]`

**Brutal honesty.** `1.293 − 0.511 = 0.782` is a **definitional identity** among three measured numbers. It was always true by subtraction. NP19 does **not** predict 0.782; it *organises* the three measured numbers into one ledger (gap = toll + exhaust) and pins the **direction** of the arrow by the sign of `ΔR`. The direction/sign is the only genuinely new content, and it rests on NP14's prior finding that the neutron is the larger-V_disp form.

---

## 4. The Two-Ledger Lemma  `[DERIVED — logical, boundary-invariance is real]`

> **Two-Ledger Lemma.** *The same movement reads endothermic through one accounting boundary and exothermic through another; the SIGN is a property of the cut `∂(sys)`, not of the medium — the boundary/time form of the FLM11 tape-measure principle. The per-form resistances `R(n), R(p), τ` are boundary-invariant; only the enclosed movement changes with the cut.*

**Case A — free-neutron decay.**

- Boundary 1 `{n alone}`: `n → p + e⁻ + ν̄`, **exothermic**, `Q = +0.78233 MeV` leaves as movement.
- Boundary 2 `{p + e⁻, building a neutron}`: `p + e⁻ → n + ν`, **endothermic**, `+1.29333 MeV` must be supplied.
- Same physics, **opposite sign — only the cut changed.** Per-reaction `|ΔR|` identical across the two cuts (same masses; rel diff `0`). The `+1.293` to build and the `−0.782` net to un-build differ by the `m_e c² = 0.511 MeV` toll that is **manufactured/consumed, not destroyed**. `[IDENTITY]`

**Case B — stellar electron capture / core collapse.**

- Boundary "isolated arrow": `p + e⁻ → n + νₑ` costs **+1.29333 MeV** (endothermic).
- Boundary "event scale": the *same* conversion is the valve through which **~3×10⁴⁶ J** of gravitational binding vents as neutrinos — **massively exothermic**. `[OBSERVED-TARGET — supernova binding scale, order of magnitude, NOT derived]`
- The medium's per-form resistances `R(n), R(p), τ` are **identical** in both readings (939.56542 / 938.27209 / 0.51100 MeV). Only the *enclosed system* changed (it now includes the collapsing core's released movement). `[DERIVED — boundary invariance]`

**Falsifier turned inward (T3).** A *single fixed* boundary has a *fixed* `ΔR`, hence exactly **one** sign. The tool's `distinct_signs_on_fixed_boundary(ΔR)` returns **1** — the both-signs construction **fails**, as the lemma requires. To obtain the other sign you must re-cut the boundary, which is by definition a *different* boundary. The lemma survives its own falsifier.

---

## 5. Grammar reconciliation — the determinant −1 relabelling  `[ASSUMED + consistency]`

The β⁻/EC vector pair is a bijection with **determinant −1** (ATOMICUS §8.3): a pure **relabelling of form** that conserves count and **carries no energy in the grammar move itself**.

That energy-freedom is **expected, not a defect**: a mass defect *is* a relabelling of form, and the energy is not in the move — it lives in the **resistance difference `ΔR` between the two forms the move connects** (Phase 2). The grammar bookkeeps **which** forms; the resistance landscape (NP21) supplies **how hard** each is to hold.

- Energy carried in the grammar move: `0 MeV` (by construction — a relabelling). `[ASSUMED]`
- Energy sourced from `ΔR`: `1.29333 MeV` — **100%** of the mass-defect accounting. `[DERIVED-from-measured]`
- No energy must be assigned to the det −1 move to balance the books. No contradiction with NP01 grammar or ATOMICUS rules. `[consistency PASS]`

---

## 6. What this establishes (and what it does not)

**Establishes (honest):**
1. A **named, constant-free reading** of `m c²` as form-resistance (Phase 1, IDENTITY on the engine's own `P_conv/3` scale).
2. The three nuclear numbers form **one ledger**: `ΔR = τ + Q` exactly (Phase 2) — an *organising* identity, not a prediction.
3. The mass defect's **sign is correct and flipped**: bound = higher resistance, `R(n) > R(p)`, free neutron relaxes downhill with no trigger (the one piece of genuinely directional content, inherited from NP14).
4. The **Two-Ledger Lemma** — sign is a property of the cut — proven on two cases with a working falsifier.
5. The det −1 grammar move is **energy-free by construction**; all energy is in `ΔR`.

**Does NOT establish (honest):**
- It does **not** derive 0.511, 1.293, or 0.782 from first principles — those are measured anchors; their relation is a subtraction identity.
- It does **not** predict the neutron lifetime value (that is NP11/NP20).
- The `~3×10⁴⁶ J` figure is an illustration, not a derived number.
- The flipped **sign** is *imported* from NP14; NP19 uses it, it does not re-derive it.

**Physics class: CONVERGENCE (reframe).** The realistic and pre-committed ceiling. A tautology dressed as a derivation would be an audit fail; NP19 is labelled for exactly what it is.

---

*NP19 · derivation · grounds NP20 (neutron's two numbers from one seat) and NP21 (the resistance landscape).*
