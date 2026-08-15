# EMC04 — The Electropause: the electron's binding (and P_eff) derived from kinematics

> **Author:** James Christopher Tyndall, Melbourne. 2026-06-18.
> **Status:** theory investigation, opened from the question *"what actually holds the electron at
> the Bohr radius — and can the binding be derived without ever invoking charge?"* Grounded in
> `emc04_electropause.cpp` (consumes `Engine/include/sdt/laws.hpp`; output in `emc04_rerun_2026-07-23.txt`).
> **Scope:** the *structural* result — the electrostatic binding **is** the centripetal
> requirement **is** the occlusion push, computed from kinematics with **no charge term**, and the
> inversion **derives** `P_eff` reproducing the engine value and the pure-derivation basis closed form
> (delete-test clean) — is **[STRONG]** and numerically verified. The result assigns
> `P_eff` class **C (DERIVED)**: it reads **α**
> as the kinematic k-rung (the chi of [[PPT02]]), not as the Coulomb coupling. **α remains the one
> irreducible input — this does not derive α.** That single caveat is the whole residual.

---

## 0. The question

The occlusion law gives force from geometry: `F = (π/4) P_eff R₁² R₂² / r²`.
EMC01 originally left its magnitude calibrated through the measured Coulomb
number. FLM07 now supplies the target-free proton lock boundary, allowing this
instrument to close the coefficient without measured `R_p`, `k_e`, or `e`.
The transfer ratio `f=P_eff/P_conv` remains conditioned on the observed
Clearing boundary inherited by `P_conv`.

So two questions, one mechanism:

1. **What physically holds the electron at the Bohr radius?** Not gravity-as-attraction (the electron
   is *driven* tangentially by the nuclear gear — Rule 10 of *De Rerum Atomicus*). The radial question
   is separate: what supplies the **centripetal** force?
2. **Can that force — hence P_eff — be obtained without ever writing down a charge?** If yes, the EMC01
   circularity is broken: the orbit side never touches Coulomb.

Tyndall's hypothesis: **the Bohr radius is the *electropause*.**

---

## 1. The electropause **[concept]**

A heliopause is where the Sun's outward output balances the inward CMB convergence. An **electropause**
is the same boundary one rung down: the surface where the electron's outward circulation strength
balances the inward occlusion gradient of the nucleus. The electron does not "sit in a potential well";
it sits at a **pressure-balance radius**, exactly as the Oort cloud sits at lumiostasis ([[GOM05]]) and
the heliopause sits at the CMB stand-off. The Bohr radius `a₀` *is* that radius for hydrogen.

This makes the binding a **radial** statement (where the balance is) that is independent of, and
complementary to, the **tangential** drive (Rule 10: the electron is carried along its Hopf track by
the nuclear rotation). The electropause holds it in; the gear keeps it moving.

---

## 2. The binding is the centripetal requirement — kinematics, no charge **[STRONG, checked]**

To hold a mass `mₑ` on a circle of radius `a₀` at speed `v` requires a centripetal force
`F = mₑ v² / a₀`. The SDT ground-state speed is the k-rung velocity `v = αc` (χ = c/v = 137.036; this
is *not* borrowed from QM — it is the hydrogen rung of the koppa ladder, [[PPT02]]). Then:

```
v             = α c               = 2.187691e6 m/s
F_centripetal = mₑ v² / a₀        = 8.238723e-8 N
```

No charge, no `e`, no `k_e` appears. Compare to the force laws at the same radius:

| force at r = a₀ | value (N) |
|---|---|
| `mₑ (αc)² / a₀`  (centripetal, **kinematics only**) | 8.238723×10⁻⁸ |
| `k_e e² / a₀²`   (textbook Coulomb) | 8.238723×10⁻⁸ |
| `law_III::F_coulomb(a₀)` (SDT occlusion, engine) | 8.238723×10⁻⁸ |

Ratios = **1.0000000000**. The electrostatic binding, the Coulomb force, and the occlusion push are
**one number**, reached from kinematics. This is the mechanical content of *"there is no charge"*
(Law 16 of the ATOMICUS 2026 Enrichment): the atom binds with χ and geometry; `e` is only the SI
unit-bridge.

---

## 3. Inverting the occlusion law derives P_eff — the EMC01 closure **[STRONG, checked]**

The occlusion law at the electropause reads
`F_centripetal = (π/4) P_eff R_charge⁴ / a₀²` with
`R_charge = √(R_p,lock r_e)` and
`R_p,lock=4ℏ/(m_pc)` from FLM07. Solve for the pressure:

```
P_eff = 4 F_centripetal a₀² / (π R_charge⁴) = 5.227252e31 Pa
engine law_III::P_eff                       = 5.227252e31 Pa
```

P_eff is now **output**, not input. The force that set it was computed from kinematics in §2, so the
calibration loop is cut.

---

## 4. The delete-test and the closed forms **[STRONG, checked]**

Reduce symbolically using `r_e=αℏ/(mₑc)` and FLM07's
`R_p,lock=4ℏ/(m_pc)`:

| form of P_eff | Coulomb input? | value (Pa) | rel. err vs engine |
|---|---|---|---|
| `4 F_cen a₀² / (π R_charge⁴)` (the inversion) | none | 5.227252×10³¹ | 6.1×10⁻¹⁰ |
| `4 α ℏ c / (π R_p,lock² r_e²)` (closed) | none | 5.227252×10³¹ | 0 |
| `m_p² mₑ² c⁵ / (4 π α ℏ³)` (mass/action seat) | none | 5.227252×10³¹ | 1.2×10⁻⁹ |

The last form contains only the mass/action seat, `c`, and the spectroscopic
α rung—no `k_e`, `e`, or measured proton boundary. Deleting the Coulomb
comparison and measured `R_p` leaves `P_eff` unchanged. **P_eff: class C.**

---

## 5. Why it is exact **[STRONG, checked]**

The identity `F_centripetal == F_Coulomb` is not a coincidence; it follows from the SDT Bohr radius:

```
a₀ = ℏ / (mₑ c α)   (verified: 5.291772e-11 m, rel 6e-10)
```

Substitute into `mₑ (αc)² / a₀` and you get `α ℏ c / a₀² = k_e e² / a₀²` algebraically. The kinematic
balance and the Coulomb expression are the *same* expression once `a₀` is written in SDT primitives.

---

## 6. What this closes, and what it does not

**Closes:**
- The [[EMC01]] coefficient circularity: P_eff is derived from the electropause balance, not calibrated
  to Coulomb. The delete-test passes.
- The [[EMC03]] **"two-locks"** step: earning the P_eff magnitude from kinematics was the named open
  item; it is done.
- Confirms *"there is no charge"* ([[project_foundational_ontology_influx_monopole]]): the binding
  needs no charge substance — only χ and occlusion geometry.

**Does NOT close (residual):**
- **α is still the one input.** The derivation reads α as the kinematic rung (v/c at the H ground
  state). A reader who *insists* α ≡ k_e e²/ℏc will call `a₀ = ℏ/(mₑcα)` Coulomb-smuggling and the
  argument circular. On SDT's own terms (α = koppa rung, [[PPT02]]) it is not — but the model **does not
  derive α**, and says so.
- The result inherits FLM07's minimum-resistance-path premise. The predicted
  `R_p,lock` differs from the measured boundary by `0.0195%`; measured `R_p`
  is comparison-only.

---

## 7. Reproduce

```bash
# MSVC
cl /std:c++20 /EHsc /O2 /I Engine\include /Fe:emc04.exe \
   Investigations\03_Electromagnetism\EMC04_Electropause_Binding_Derivation\emc04_electropause.cpp && emc04.exe
# GCC/Clang
g++ -std=c++20 -IEngine/include \
   Investigations/03_Electromagnetism/EMC04_Electropause_Binding_Derivation/emc04_electropause.cpp -o emc04 && ./emc04
```

Output is `emc04_rerun_2026-07-23.txt`. All five checks return **PASS**.

---

## Cross-references

- **[[EMC01]]** — the occlusion force law (C) and the P_eff coefficient (was E); this closes the E.
- **[[CR03]]** — the P_eff = 4αℏc/(πR_p²r_e²) closed form, here re-derived from the electropause.
- **[[EMC03]]** — repulsion = inverse of convergence; the P_eff magnitude was its "two-locks" open step.
- **[[PPT02]]** — α as the hydrogen koppa rung (χ = 137), not a magic constant.
- **ATOMICUS_COMPLETE.md** — folded in as **Law 15 (The Electropause)** of the 2026 Enrichment.
- `Engine/include/sdt/laws.hpp` — `lock_geometry`,
  `law_III::{R_p_lock,P_eff,F_coulomb,R_charge}`, and the traced
  hydrogen/mass-action dependencies.
