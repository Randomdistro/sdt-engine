# FLM11 — Derivation: The Tape-Measure Principle and the Fifth-Ruler Count

> **Author:** J. C. Harvey, Melbourne. **Status:** RUN OUTPUT (2026-07-01).
> **Tool:** `flm11_ruler_count.py` → `flm11_results.txt`. **Engine:** parity with `sdt::laws::law_VI`.
> **Inputs:** derivation basis only `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + `law_VI` integers (W, p, q). No G/M/GM, no ψ, no gauge groups, no charge-substance.
> Each line flagged **DERIVED** (falls out of the form's DoF + a native constraint) or **ASSUMED** (argued, not proven).

---

## 1. Phase 1 — The Tape-Measure Lemma (symbols)

**Setup.** Let **𝒞** be the form's configuration space and let a locus **L ∈ T𝒞** be its tangent (the state's displacement from equilibrium along each DoF). Choose a basis of measurable axes `{a₁, …, a_D}` for the externally accessible tangent subspace, with `⟨aᵢ, aⱼ⟩ = δᵢⱼ`.

**Definition (instrument = committed projection).** An *instrument* pinned to axis `a` is the selection operator

  **Π_a : T𝒞 → ℝ,  Π_a(L) = ⟨L, a⟩.**

The strip is "committed to `a`" because its own internal configuration is frozen onto the direction `a` (it *is* a piece of the medium aligned to `a`).

**Tape-Measure Lemma.** *For a strip committed to axis `a`, the reading of any locus `L` is `⟨L, a⟩`, and this reading is independent of the components `⟨L, a′⟩` for every `a′ ≠ a`.*

  **Proof.** `Π_a(L) = ⟨L, a⟩ = ⟨ Σⱼ cⱼ aⱼ , a ⟩ = cₐ`, by orthonormality. Varying any `c_{a′}` (a′≠a) leaves `cₐ` fixed. ∎ — **DERIVED** (linear-algebraic; the physics is that "commitment" = basis-alignment).

**Corollary (unification is blind from inside).** A cross-axis relation is an off-diagonal quantity `⟨L, a⟩·f(⟨L, a′⟩)`. No single `Π_a` can return it: `Π_a` sees only `cₐ`. To read the *relation* between mass and charge you would need an instrument sensitive to both `a_mass` and `a_charge` at once — but every strip is cut from 𝒞 and thereby pinned to **one** direction. Hence: *you never measure four properties of one object; you measure one object with four committed strips, each handing back its own axis.* — **DERIVED** from the Lemma.

**Two-ledger connection (NP19).** Mass and moment are the same defect read by two committed strips (a time-form `Π_mass` and a boundary-form `Π_moment`). That is the Tape-Measure Lemma applied twice to one `L`. — **ASSUMED** (cross-ref, not re-derived here).

---

## 2. Phase 2 — Enumerate the form's DoF → property count

The form is the (p,q) torus-knot vortex whose measurable structure lives in the 28-D state Levels 5 (Torus `T₁–T₅`) and 6 (Dynamism `Φ₀–Φ₅`). The *externally grippable* axes — those a strip cut from the outside can take purchase on — are enumerated below. A ruler reads by **gripping**: coupling to a resistance, a handedness, a circulation, or an oscillation. Four kinds of purchase ⇒ four grip mechanisms `{RESISTANCE, HANDEDNESS, CIRCULATION, OSCILLATION}`, plus the null class `NONE`.

### 2.1 The independence test (native constraints)

- **Law V movement budget** `v_T² + v_P² = c²` (`law_VI::topology::budget_residual`). Tool output: residual `= 1.000000000000` for electron (1,1) **and** proton (2,3). ⇒ **v_P is a dependent function of v_T**: `v_P = √(c² − v_T²)`. — **DERIVED** (exact, from the budget).
- **Winding W** (`law_VI::winding`): `W=1` electron, `W=3` proton, **`W=0` open line**. W discretely *labels* the form; it is not a continuously read ruler. — **DERIVED**.
- **Traction `T = 3(W+1)`** (`law_VI::traction`): `=12` for the proton. This gives the *three wake output channels* (ℓ=1 Coulomb, ℓ=2 magnetic, ℓ≥3 entrainment). T is a **consequence of W**, confirming the grip mechanisms are *wake channels*, not extra axes. — **DERIVED**.

### 2.2 The axis table (tool-reproduced)

| # | Form axis | Grip | Property | Independent? | Deciding constraint |
|---|---|---|---|---|---|
| A | tube swelling / reorganisation cost (`T₂`, Law IV) | RESISTANCE | **mass** | YES | Law IV cost axis; orthogonal to circulation/handedness/oscillation |
| B | handedness `Φ₃ = ±1` (Level 6) | HANDEDNESS | **charge** (handed redirection; **not** a substance, R2) | YES | discrete ℤ₂ sign; orthogonal to any circulation magnitude |
| C | toroidal circulation `v_T` | CIRCULATION | **magnetic flux** | YES | free continuous rate; the single surviving flux axis |
| D | oscillation `Φ₂` (Level 6) | OSCILLATION | **electromagnetism** | YES | temporal propagating mode ≠ static circulation |
| E | poloidal circulation `v_P` | CIRCULATION | (2nd flux) | **NO** | **Law V budget closes → v_P fixed by v_T** |
| F | through / straight axis (open line) | **NONE** | — (no ruler) | residue | grip=NONE; W=0 open line |
| G | core-ring translation (`T₁` / Level-2 position) | — | — | **excluded** | kinematic position, not an identity property |
| H | surface orientation (Level-4 `ξ_s3`) | — | — | **excluded** | frame choice (direction of already-counted axes) |

**Count (tool):** grippable independent rulers **P = 4** = `{mass, charge, magnetic flux, EM}`; dependent axes = 1 (`v_P`); zero-grip residue = 1 (straight axis). — **DERIVED** (integer, reproduces the pre-committed P before physics' "four" was consulted; see `RUN_LOG.md`).

### 2.3 The fifth-ruler prediction

**NO fifth independent ruler.** The only continuous candidate beyond the four is `v_P`, and Law V removes it (`v_P` is not free once `v_T` is set). Orientation (H) is a frame choice; ring-position (G) is kinematic. — **DERIVED** for `v_P` (exact budget); **ASSUMED** for the grippability exclusions G, H (argued, not proven — the Class-C caveat).

> If a future analysis shows orientation or `v_P` *is* externally grippable as an independent identity, that is a **Class-D novel prediction** of a fifth ruler (F4), not a retro-fit. It did not survive here.

---

## 3. Phase 3 — The straight (zero-grip) projection = the neutrino

Exactly one enumerated axis has grip `NONE`: the **through/straight axis Π_∥** — pure through-flow along the core, no circulation to catch, no handedness to resolve, no resistance to push against, no oscillation to phase-lock. A ruler reads by gripping; Π_∥ is *defined by not gripping*. Therefore **no committed strip in the medium can couple to it** → it has **no native instrument**. — **DERIVED** (from the grip definition).

Π_∥ is **not empty**: it is the open winding **W=0** line, which carries momentum/energy. So the blind spot is **measurability, not existence**. — **DERIVED** (`law_VI::winding` W=0).

**Identification:** the W=0 open winding *is* the SDT neutrino (`laws.hpp` header comment: "W = 0 (open winding) → neutrino"). Hence the neutrino is hard to see **not** because it is rare or weak, but because it is **un-self-measurable by committed cloth** — the one form DoF with no ruler cut from the same medium. — **DERIVED** identification (the W=0 ↔ neutrino mapping is the header's; the *why-unmeasurable* is this investigation's result). Cross-ref PPT10 (straight-light: the straight projection has no ruler) and NP18 (BEC = *uncommitted* cloth, the loophole that reads by coherence rather than grip).

Tool flags (from `flm11_results.txt`): `exactly-one-zero-grip: PASS` · `residue = straight axis: PASS` · `residue maps to W=0: PASS`.

---

## 4. Phase 4 — Consistency vs physics

| Grip mechanism | Ruler cloth (committed strip) | SDT-native axis | Physics name |
|---|---|---|---|
| RESISTANCE | inertial / resistance structures | reorganisation cost (Law IV) | **mass** |
| HANDEDNESS | handed (electronic) structures | `Φ₃ = ±1` | **charge** |
| CIRCULATION | moving-medium structures | `v_T` (with `v_P` slaved by Law V) | **magnetic flux** |
| OSCILLATION | EM (oscillatory) structures | `Φ₂` propagating wake | **electromagnetism** |
| **NONE** | *no committed strip can grip it* | `Π_∥`, W=0 open line | **(neutrino — the residue)** |

**One-to-one map achieved.** The four grippable rulers = physics' four named "fundamental properties"; the straight projection sits *outside* the grippable set as the neutrino residue. Every dependent axis is dependent by a **stated SDT constraint** (Law V), not by hand. — **DERIVED** count and placement; **ASSUMED** (Class-C) that the four 28-D components chosen (T₂, Φ₃, v_T, Φ₂) are the *complete* externally-grippable set.

---

## 5. Provenance summary

```
// provenance_status:     SDT-derived (count + residue); mapping argued (grippability)
// correspondence_status: known-match (4 = physics' four properties) + novel (neutrino = zero-grip residue)
// input_dependency:      primitive-derivation basis + law_VI integers (W, p, q) + Law V budget
// class:                 C  (clean integer DERIVED; DoF→property map rests on 1-2 argued grippability claims)
// circularity_assertion: passes delete-test — physics' "four" is NOT an input; the count is pre-committed
//                        in RUN_LOG before the tool ran, and Law V (not the answer) removes the 5th axis
// risk_flag:             external-grippability of Level-5/6 components is ARGUED, not proven; the
//                        DoF↔property assignment (which component reads which property) is the soft joint
```

**DERIVED vs ASSUMED, one line:** the **integer 4+1 and the zero-grip residue are DERIVED** (Law V is exact, W=0 is in the header, the grip taxonomy is closed); the **assignment of each surviving axis to a specific named property, and the completeness of the grippable set, are ASSUMED** (argued natively but not proven) — which is exactly why this is Class C / CONVERGENCE, not a bare Class A.
