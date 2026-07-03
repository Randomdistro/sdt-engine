# NP19 — VERDICT: Mass-Defect as Form-Resistance + the Two-Ledger Lemma

> **Author:** J. C. Harvey, Melbourne. **Run date:** 2026-06-30.
> **Tool:** `np19_ledger.cpp` (MSVC, `#include <sdt/laws.hpp>`), exit code **0** (all assertions pass). Output: `np19_results.txt`.

## Dual verdict header

| Axis | Grade | Basis |
|------|-------|-------|
| **Prompt completion** | **A** | All four gated phases (P1–P4) executed and PASS-GATE; all §6 outputs produced. |
| **Physics class** | **CONVERGENCE (reframe)** | A named, constant-free reframe + an exact arithmetic identity + a proven lemma. **NOT** a new derived number. Exactly the pre-committed ceiling. |

**One-line call:** NP19 does what it set out to do — it *dissolves* "mass↔energy interchange" as one substrate read two ways, pins the flipped sign of the neutron defect, and promotes the Two-Ledger Lemma — **without** deriving any of 0.511/1.293/0.782, which remain measured anchors related by subtraction.

---

## Phase results (committed thresholds vs actual)

| Phase | Committed gate | Actual | Result |
|-------|----------------|--------|--------|
| **P1** | round-trip <1e-9; `ρ_form_e` ~ `P_conv/3`; 0 new constants | rel err ≤4.3e-16; ratio **1.000000**; 0 constants | **PASS-GATE** |
| **P2** | `\|ΔR−1.293\|/1.293 <0.1%`; `\|Q−0.782\|/0.782 <0.2%`; `R(n)>R(p)`; `ΔR>τ` | 0.026%; 0.043%; TRUE; TRUE | **PASS-GATE** |
| **P3** | `\|ΔR\|` inv ≤1e-6; opposite signs; both-signs FAILS | invariant (0); opposite; returns 1 sign | **PASS-GATE** |
| **P4** | written reconciliation; energy 100% from ΔR | written; 1.29333 from ΔR, 0 from move | **PASS-GATE** |

**Key numbers (from `np19_results.txt`):**
`R(n)=939.56542`, `R(p)=938.27209`, `τ=m_e c²=0.51100`, `ΔR=1.29333`, `Q=ΔR−τ=0.78233` MeV.

---

## Falsification table (§8) — filled

| Test | Hypothesis | Predicted | Actual | Outcome |
|------|-----------|-----------|--------|---------|
| **T1 (sign — crux)** | bound/heavier = higher resistance | `R(n) > R(p)`, `ΔR > 0` | `939.565 > 938.272`, `ΔR = +1.293` | **PASS** (not killed) |
| **T2 (bookkeeping)** | three numbers = one landscape | `1.293 − 0.511 = 0.782` within error | `1.29333 − 0.51100 = 0.78233`; `τ+Q=ΔR` exact | **PASS** (identity holds) |
| **T3 (lemma)** | sign = property of the cut | no fixed boundary yields both signs; `\|ΔR\|` invariant | fixed cut → 1 sign; `\|ΔR\|` invariant | **PASS** (lemma survives) |
| **T4 (no-feed)** | decay needs no trigger; surplus pre-exists as `ΔR` | spontaneous, `ΔR > τ` | `1.293 > 0.511` TRUE | **PASS** |
| **T5 (grammar)** | det −1 relabelling carries no energy in the move | all energy from `ΔR` | 100% from `ΔR`, 0 from move | **PASS** |

No KILL triggered. No OPEN required for T4/T5 (both cleanly satisfied). No RETRO-PASS, PLUG, IDENTITY-PASS, or BORROW-SMUGGLE occurred.

---

## STRESS-TEST SELF-AUDIT (mandatory)

### (1) Independent, or identity/circular?

**Mostly identity/reframe — and the document says so in every relevant place.** Breakdown:

- **The arithmetic core `1.293 − 0.511 = 0.782` is a DEFINITIONAL IDENTITY**, not an independent result. It is the subtraction of three measured anchors (`m_n`, `m_p`, `m_e`) that were *always* related this way. Labelled `IDENTITY` throughout. This is the honest heart of the verdict: **NP19 organises three measured numbers; it does not predict any of them.**
- **The Phase-1 `ρ_form_e = P_conv/3` match is ALSO an identity** — it is the pre-existing `P_cf_e` relation (`ρ_eff_e·c² ≡ P_conv/3`, laws.hpp:485), not a fresh derivation. It proves the resistance *reading* is constant-free; it proves nothing new numerically. Labelled `IDENTITY`.
- **The one genuinely directional (non-identity) claim is the SIGN**: `R(n) > R(p)` ⟹ bound = higher resistance ⟹ free neutron relaxes downhill. But even this **sign is imported from NP14** (neutron = larger-V_disp form); NP19 *uses* it, it does not re-derive it. So the "new" content is: (a) the named form-resistance reading, (b) the promoted Two-Ledger Lemma with a working falsifier, (c) the observation that the sign + inequality make decay spontaneous with no trigger. All conceptual/logical, not numerical.
- **Verdict on circularity:** no vicious circularity (nothing is fit to a target then reported as predicting that target). But the work is heavily **identity-based / reframe**, and is labelled as such. Calling it Class A "derivation" would be an IDENTITY-PASS — explicitly avoided; class is **CONVERGENCE**.

### (2) Fished (exponents / coefficients / tolerances tuned to hit a number)?

**No.** There are **zero** free exponents and **zero** fitted coefficients anywhere in the chain. The literals 0.511/1.293/0.782 appear **only** as `OBSERVED-TARGET` comparison columns and are never inputs. Tolerances (0.1%, 0.2%, 1e-9, 1e-6) were committed in `RUN_LOG.md` **before** the run and were **not** touched afterward — the achieved errors (0.026%, 0.043%) sit comfortably inside them, so no widening was even tempting. No coefficient exists that *could* be plugged: `ΔR` and `Q` are pure subtractions of masses read from `sdt::laws::measured`.

### (3) Dimensions

All consistent.

- `R(form) = m c²`: `[kg]·[m²/s²] = [J]` ✓ (reported in MeV via `÷ MeV_to_J [J/MeV]`).
- `ρ_form = R/V_disp`: `[J]/[m³] = [Pa]` ✓ — compared to `P_conv/3` `[Pa]` ✓ (like-for-like).
- `ΔR = R(n) − R(p)`: `[J] − [J] = [J]` ✓; `Q = ΔR − τ`: `[J] − [J] = [J]` ✓.
- Numerical care: `m_n − m_p` subtracted in **kg first** (gap ≈ 2.3×10⁻³⁰ kg, ~10¹³× above double round-off), then × c², then ÷ MeV_to_J — no catastrophic cancellation (round-trip and subtraction both clean to machine epsilon).
- Whitelist obeyed: only `{m_e, m_p, m_n, c, MeV_to_J}` + engine `Phi/P_conv/V_disp`. **No G, no M, no GM, no G_F, no ψ, no ΛCDM, no "charge radius."** The `~3×10⁴⁶ J` is a labelled `OBSERVED-TARGET` illustration, outside the derivation chain.

### (4) Honest class + what is owed

- **Prompt completion: A.** All phases gated, all outputs produced.
- **Physics class: CONVERGENCE / reframe.** A named lemma + a constant-free reading + an organising identity. This is a genuine *conceptual* contribution (it removes the "interchange mystery" and fixes the decay direction from least-resistance) but it is **not a new number** and must never be reported as one.
- **Owed / deferred:**
  1. The flipped **sign** is inherited from **NP14**, not re-derived here — NP19 is only as solid as NP14's larger-V_disp finding.
  2. **What sets the toll `τ = m_e c²`** as *the* manufacturing cost (rather than some other form) is asserted from the β⁻ daughter, not derived — flagged for **NP20/NP21**.
  3. The **resistance-landscape values** themselves (why `R(n)`, `R(p)` are what they are) are **NP21's** job; NP19 supplies only the *unit of account*.
  4. The det −1 grammar tie-in (P4) is a *consistency* statement, not a proof that energy *cannot* live in the move; if NP21 finds otherwise, revisit.

**Bottom line:** an honest, fully-audited **reframe** that passes every committed gate and every falsifier — and is labelled, at every step, as convergence rather than derivation. An honest Class-C beats a faked Class-A.

---

## Stack escalation

- `INVESTIGATION_STACK.md` status: **RESOLVED** (Prompt completion A; physics class honest CONVERGENCE). Grounds NP20/NP21 as intended. *(Note: this verdict records the status; the stack file itself is not edited by this run per the "edit no existing file" constraint — update it in a separate authorised pass.)*

*NP19 · VERDICT · a named reframe, not a new number. The plan bent to the truth.*
