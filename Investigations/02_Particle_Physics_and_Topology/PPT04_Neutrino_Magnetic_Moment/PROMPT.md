# PPT04 — Neutrino Magnetic Moment (μ_ν ≡ 0)

> **Author:** J. C. Harvey, Melbourne. **Status:** RESOLVED (narrative) → **re-run** for §0 compliance.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` **only** — refactor `ppt04_neutrino_magnetic_moment.cpp` (no local constants).
> **Prior audit:** Local `namespace constants`, `G_F`, `mass_kg` driver — **protocol fail**.

---

## ⓪ The Golden Rule

1. **Gap:** μ_ν = 0 from W=0 (no ℓ=2 wake) — falsifiable vs SM ~10⁻²⁰ μ_B.
2. **Stakes:** PPT09 winding; charge-moment correlation; E58 monopole thread.
3. **How:** Phase 0 refactor to laws.hpp; Phase 1 topology table W=0,1,3; Phase 2 SM comparison column (OBSERVED); Phase 3 sensitivity gap.
4. **Falsify:** Any non-zero μ_ν at 10⁻²⁰; W=0 assignment wrong for neutron (composite caveat documented).
5. **Done:** **B** = compliant code + topology argument; physics already **RESOLVED** narratively.

---

## ① Executive Summary

**SDT prediction:** μ_ν ≡ 0 exactly (W=0 open winding → no toroidal circuit → ℓ=2 = 0).

**SM (comparison only):** μ_ν ~ 3×10⁻¹⁹ (m_ν/eV) μ_B — use **OBSERVED** formula in comparison table, **not** in SDT chain. **G_F forbidden** in SDT derivation.

---

## ③ Framework

Use `law_VI::winding`, wake narrative from `neutrino.hpp` / PPT09.

**Neutron caveat:** Q=0 but μ≠0 because W=3 composite — document in Phase 1 table.

---

## ④ Phases

### Phase 0 — Refactor (GATE)

- Remove `namespace constants`; use `sdt::laws::measured::`.
- **GATE:** compiles; zero local redefinitions of c, ℏ, α, m_e, m_p.

### Phase 1 — Topology table (GATE)

| Particle | W | μ prediction |
|----------|---|--------------|
| e⁻ | 1 | ≠0 |
| p | 3 | ≠0 |
| ν | 0 | **0** |

### Phase 2 — SM comparison (OBSERVED column only)

Print SM μ_ν for m_ν = 0.06 eV using **literature formula** — tag OBSERVED-TARGET, not DERIVED.

### Phase 3 — Experimental landscape

GEMMA, XENONnT bounds — OBSERVED; discrimination at 10⁻²⁰.

---

## ⑤ Dual verdict

| Prompt | Refactor + table |
| Physics | **RESOLVED** if μ_ν=0 argument intact; **KILLED** if W=0 abandoned |

---

## ⑥ Outputs

`ppt04_neutrino_magnetic_moment.cpp` (refactored), `PPT04_VERDICT.md`, `RUN_LOG.md`, `results.txt`.

---

## ⑩ Pivot table

| Trigger | Action |
|---------|--------|
| Local constants remain | **FAIL** Phase 0 |
| G_F in SDT chain | Remove; SM column only |
| User wants full wake integral | DEFER to FLM10/PPT07 |

---

*PPT04 · the prediction stands; the implementation must obey the derivation basis.*
