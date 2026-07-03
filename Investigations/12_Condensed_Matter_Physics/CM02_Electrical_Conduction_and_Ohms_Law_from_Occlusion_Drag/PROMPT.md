# CM02 — Electrical Conduction and Ohm's Law from Occlusion Drag

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → **ACTIVE** on first gated run.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` — `law_III::`, `measured::`, `bridge::`; **no** local `namespace constants`.
> **Prior audit (2026-06-27):** `cm02_ohms_law.cpp` circularly used OBSERVED `τ_Cu` → σ. This prompt supersedes that path.

---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Does metallic conductivity follow from **occlusion drag on drifting W=1
   vortices** — with the scattering time `τ` *derived* from a relay mean free path (`τ = ℓ_mfp/v_drift`,
   `ℓ_mfp` from an occlusion cross-section of lattice defects) — or can σ only ever be "reproduced" by
   the circular Drude path that reads `τ` back out of the *measured* conductivity it is meant to
   predict? Concretely: can `τ_Cu ~ 2.5×10⁻¹⁴ s` be obtained from defect geometry, never from a copper
   table? *(The prior `cm02_ohms_law.cpp` took τ from measured σ — Class F circularity; this prompt
   deprecates that path. See `CM02_VERDICT.md`, now superseded.)*
2. **Why does it matter?** — CM02 is the **normal-state root** of the whole CM stack (README): it is
   the drag that CM01 superconductivity drives to zero, the drift channel CM03 bands gate, and the
   native ohm CM06 metrology closes against. If τ is genuinely geometric, the branch stands on a
   derived ohm; if τ is read from σ, every "PASS" above it inherits the circularity.
3. **How will we find out?** — Phase 0 sanity gate; Phase 1 derives τ from defect cross-section
   **with no OBSERVED τ input**; Phase 2 forms σ = ne²τ/m_e; Phase 3 gets ρ∝T from the FD05 thermal
   amplitude; Phase 4 links the native ohm to `R_K`. Using a measured τ caps the grade at C/F.
4. **What would prove us wrong?** — §⑧: τ from geometry off >2× on Cu; ρ(T) not linear above θ_D;
   σ reproducible *only* with the OBSERVED τ (the circular path). Each has a real failure mode.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class.
   Prompt **B** if σ within 2× on Cu/Ag/Al with **DERIVED** τ; **A** if the ρ(T) slope is native too;
   **F** if the only PASS is the circular τ-from-σ path.

---

## ① Executive Summary

A conduction electron is a **drifting W=1 vortex**. Occlusion events (Law III) randomise organised drift into heat. **Question:** Does `V=IR`, `σ = ne²τ/m_e`, and metallic `ρ ∝ T` emerge when `τ = ℓ_mfp / v_drift` with `ℓ_mfp` from **occlusion cross-section** of thermal + static lattice defects?

**Forbidden:** Band structure, Fermi surface, Boltzmann transport as mechanism inputs. **Allowed:** n, σ, ρ as **OBSERVED-TARGET** comparisons.

---

## ② Physical Context

**Balance:** `F_push = e E` vs time-averaged `F_drag` from occlusion at rate `1/τ`.

**Variables:**

| Symbol | Meaning | Tag |
|--------|---------|-----|
| `τ` | Mean time between occlusions | DERIVED goal |
| `ℓ_mfp` | Mean relay path between occlusions | DERIVED |
| `σ_occl` | Effective occlusion cross-section | DERIVED or CALIBRATED(1) |
| `n` | Carrier density | OBSERVED for Cu |
| `m_e` | Whitelist reorganisation mass | measured::m_e |
| `R_K` | h/e² | OBSERVED metrology |

**Targets:** Cu σ ≈ 5.96×10⁷ S/m; ρ(300K) linear above θ_D ≈ 170 K for Cu.

---

## ③ Theoretical Framework

**H1:** `μ = eτ/m_e`, `σ = n e² τ / m_e` from push/drag balance over one τ.

**H2:** Thermal defect amplitude `δa ∝ √T` (FD05) ⇒ `σ_occl(T) = σ_0 + α√T` ⇒ `ρ ∝ T` above θ_D.

**H3:** Ohm = throughput disorder rate; `R_K = h/e²` closes CM06.

**zk² = 1:** Ground-state identity check once — not part of σ derivation.

---

## ④ Investigation Strategy

### Phase 0 — Sanity (GATE)

Print `R_K`, `m_e`, `e`; verify `h/e²` vs CODATA. **GATE:** rel err < 10⁻⁹.

### Phase 1 — Derive τ from occlusion geometry (GATE — no OBSERVED τ input)

- **Method:** Model drifting vortex radius `R_e`; defect density `n_def`; occluded solid angle increment per event from `law_III::solid_angle_occluded` or documented proxy; `ℓ_mfp = 1/(n_def σ_occl)`; `τ = ℓ_mfp / v_drift` with `v_drift` from Phase 1 balance self-consistency (one iteration OK).
- **Success:** `τ` within **factor 2** of 2.5×10⁻¹⁴ s for Cu using **only** DEFER/ASSUMED material constants (n_def, σ_occl geometry) — or **CALIBRATED(1)** on σ_occl with full ledger.
- **Forbidden:** Input `TAU_CU = 2.5e-14` as given.

### Phase 2 — Drude σ (GATE)

- **Success:** `|σ_calc − σ_Cu|/σ_Cu < 0.5` (50%) with DERIVED τ; **2×** acceptable for Class C.
- **Compare row:** Drude with OBSERVED τ — label **CONVERGENCE check only**.

### Phase 3 — ρ(T) (DEFER if Phase 1 OPEN)

- Linear slope above θ_D; Matthiessen ρ₀ residual.
- **Success:** exponent 1.0 ± 0.2 in log-log band 200–400 K.

### Phase 4 — Native ohm narrative

- Document `P = I²R` as throughput disorder; link `R_K`.

---

## ⑤ Success Criteria — dual verdict

| Prompt | Requirement |
|--------|-------------|
| **A** | τ derived; σ 2×; ρ(T) slope native |
| **B** | τ CALIBRATED(1); σ 2× |
| **C** | σ identity with OBSERVED τ only |
| **F** | Circular τ → σ PASS |

| Physics | Condition |
|---------|-----------|
| **NATIVE** | Phase 1 τ from occlusion |
| **CONVERGENCE** | Drude form only |
| **OPEN** | No τ from geometry |

---

## ⑥ Outputs

1. `CM02_DERIVATION.md`
2. `cm02_ohms_law.cpp` — **must not** hardcode τ_Cu in derivation path
3. `cm02_results.txt`
4. **`RUN_LOG.md`**
5. `CM02_VERDICT.md`

---

## ⑦ Dependencies

**Upstream:** Law III, FD05 thermal displacement, [[project_two_regime_and_occlusion_saturation]].
**Downstream:** CM01, CM06, TD01 heat.

---

## ⑧ Falsification Tests (each has a real failure mode + numeric kill trigger)

| ID | Test | SDT prediction (numeric) | What KILLS it |
|----|------|--------------------------|---------------|
| T1 | τ from occlusion geometry, **no measured-τ input** | `τ_Cu` within factor 2 of 2.5×10⁻¹⁴ s from defect cross-section + density only | if geometry gives τ off by >2× (and the only way to hit it is to read τ from measured σ) → the occlusion-drag model of τ is OPEN/dead |
| T2 | Drude σ with DERIVED τ | rel err of σ vs σ_Cu below 0.5 (50%), with 2× the Class-C floor; Cu 5.96×10⁷ S/m, also Ag/Al | if σ is within tolerance *only* when τ is the OBSERVED value → the cross-section is wrong; PASS is the circular F-path, not a derivation |
| T3 | Metallic ρ ∝ T above θ_D | log-log exponent 1.0 ± 0.2 over 200–400 K (θ_D,Cu ≈ 170 K); ρ increases with T | if the exponent is 0 (flat) or the FD05 thermal amplitude gives the wrong sign → thermal occlusion does not set ρ(T) |

---

## ⑨ Implementation Notes

- Use `measured::e_charge`, `measured::m_e`, `measured::hbar`. `e` is the unit-bridge constant, **not a
  charge substance** — conduction is drifting vortices occluded by lattice defects; never write "charge
  carrier density" as a substance claim or "charge radius". The drift is W=1 vortices; current is
  organised throughput.
- The defect cross-section and τ derivation must use native occlusion geometry, not borrowed transport
  coefficients. Keep n, σ_Cu, ρ(T) as OBSERVED-TARGET comparisons in one labelled block.
- Print ledger column: `[quantity | value | DERIVED / OBSERVED / CALIBRATED]`.
- Author attribution in all generated files: **J. C. Harvey, Melbourne.**

## ⑪ Questions This Opens *(generative — log new ones in `CM02_VERDICT.md`)*

Not required for the verdict; this is the payoff of doing it well.

1. **Is the occlusion cross-section the same object across CM02/CM01/CM03?** The defect cross-section
   that sets τ here is what CM01's locked pair must out-span and what CM03's gap closes. Is it one
   geometric quantity, measurable independently?
2. **Does τ derived from geometry predict the residual-resistance ratio?** If ℓ_mfp splits into thermal
   (FD05 ∝T) and static-defect parts (Matthiessen), does the SDT split predict RRR for pure vs alloyed
   Cu with no extra fit?
3. **Is the Wiedemann–Franz ratio native?** If both charge and heat are organised throughput occluded
   at the same rate 1/τ, does the Lorenz number fall out of SDT geometry rather than being assumed?
4. **Where exactly did the prior tool go circular?** The deprecated `cm02_ohms_law.cpp` read τ from
   measured σ. Documenting that path precisely (and the one geometric input that breaks it) is the
   reusable lesson for the audit spine.

---

## ⑩ Adaptive Execution Protocol

### Pre-Run Commitments

```markdown
- CALIBRATED budget: 1 (σ_occl only, if needed) — never on τ via measured σ
- Engine namespaces actually used: law_III (occlusion), measured (e, m_e, hbar), bridge; FD05 thermal amplitude
- Phase 1: τ within 2× of 2.5e-14 s from geometry OR CALIBRATED(1) documented (NO TAU_CU input)
- Phase 2: σ rel err < 0.5 (2× for Class C)
- Phase 3: ρ(T) log-log exponent 1.0 ± 0.2 over 200–400 K
- Forbidden: TAU_CU as input; RETRO-PASS; relabel the circular τ-from-σ PASS as anything ≥ C
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| τ from geometry off >2× | adjust σ_occl geometry / n_def model | **CALIBRATED(1)** on σ_occl (full ledger) or **OPEN** the drag model | input the measured τ |
| σ within tolerance only with OBSERVED τ | label **CONVERGENCE** (Class C), state the import | — | claim NATIVE; grade ≥ C on the circular path (that is the F-path) |
| ρ(T) exponent ≈ 0 (flat) | recheck the FD05 thermal-amplitude coupling | **DEFER** Phase 3, cite dependency | fake a linear Arrhenius/ρ∝T fit |
| Rivals (Drude) match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

---

*CM02 · 10× upgrade 2026-06-29 · τ must be earned from occlusion, not read from copper tables · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

*CM02 · τ must be earned from occlusion, not read from copper tables.*
