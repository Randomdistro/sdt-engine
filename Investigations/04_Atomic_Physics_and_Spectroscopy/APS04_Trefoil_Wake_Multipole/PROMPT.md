# APS04 — Trefoil Wake Multipole Expansion and Angular Harmonics

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — [APS04] APS04 — Trefoil Wake Multipole Expansion and Angular Harmonics: *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

**Status:** INVESTIGATION SPEC  
**Date:** June 2026  
**Author:** James Christopher Tyndall, Melbourne, Australia  
**Priority:** FOUNDATIONAL — unblocks PPT08 (angular DOF) and fine structure closure

---

## Problem Statement

**SDT currently has only radial structure.** The orbital velocity law v(r) = (c/k)√(R/r) depends on r only. There is **no native mechanism** that distinguishes s-orbitals (ℓ=0, spherical) from p-orbitals (ℓ=1, three lobes). This angular degree of freedom is currently **borrowed from QM** in the form of spherical harmonics Y_ℓ^m — a conceptual contamination flagged in the CONCEPTUAL_CONTAMINATION_AUDIT.md as M1.

**Without native angular DOF, SDT cannot derive:**
- Fine structure splitting (currently fitted via k_Lamb = 12.7227)
- Lamb shift (2S₁/₂ vs 2P₁/₂: measured 1057.845 MHz)
- Hyperfine structure mechanism
- Spectral selection rules (Δℓ = ±1, Δm = 0, ±1)
- The correct energy ordering E(s) > E(p)

**The root cause:** The electron orbits a **spherically symmetric Coulomb potential** in standard QM. But in SDT, it orbits the **non-spherical wake of the proton's trefoil topology** — and that asymmetry is the source of angular structure.

---

## Hypothesis

**The proton is a trefoil knot (W=3).** Its wake field is NOT spherically symmetric — it has **three-fold rotational symmetry** about the z-axis. The electron, orbiting in this asymmetric wake, experiences different energies depending on whether it orbits:

- **Equatorially** (in the trefoil's plane) — "s-like" — stronger interaction with the quadrupole field
- **Polarly** (perpendicular to the trefoil's axis) — "p-like" — weaker interaction

This energy difference **IS the fine structure splitting** (and Lamb shift).

**Key inversion:** Angular structure comes from the **nuclear wake geometry** (trefoil topology), not from the **electron's wavefunction** (QM borrowed concept).

---

## Methodology: Four Investigation Phases

### Phase 1: Trefoil Wake Geometry (PAPER)

**Objective:** Compute the velocity/pressure field induced by a (2,3) torus knot at large r >> R_p.

**Deliverable:** `CQ38_TREFOIL_WAKE.md`

**Tasks:**
1. Parametrize the (2,3) torus knot in 3D space
2. Compute the wake field using a Biot-Savart-type circulation source
3. Decompose the field into **native multipole components** (C₃ symmetry only, no QM spherical harmonics)
4. Identify power-law radial profiles:
   - Φ₀(r) ~ r⁻¹ (monopole: integrated occlusion)
   - Φ₂(r) ~ r⁻³ (quadrupole: toroidal circulation)
   - Φ₃(r) ~ r⁻⁴ (trefoil harmonic: three-fold phase)
5. Justify each power law from first principles (not fitted)

**Physical reasoning:**
- The Coulomb r⁻¹ falloff comes from the spation lattice's response to occluded convergence
- The r⁻³ quadrupole arises from the trefoil's net angular momentum (second harmonic)
- The r⁻⁴ trefoil harmonic follows from three-fold periodicity (third spatial frequency)

**Success criterion:** Theoretical derivation complete; power laws justified from spation physics.

---

### Phase 2: Multipole Coefficients (CALCULATION)

**Objective:** Extract the radial profiles and fit to power laws.

**Deliverable:** `cq38_wake_field_solver.cpp` (numerical solver); outputs to `cq38_lamb_shift.txt`

**Tasks:**
1. Sample the wake field at multiple radii: r ∈ [1 fm, 1000 fm]
2. At each radius, measure:
   - Equatorial component (θ = π/2): samples all three trefoil lobes
   - Polar component (θ = 0, π): samples near the axis
3. Decompose using azimuthal FFT to extract:
   - Φ₀(r): isotropic (m=0 monopole mode)
   - Φ₂(r): equatorial-vs-polar difference (P₂(cos θ) modulation)
   - Φ₃(r): three-fold azimuthal modulation (cos(3φ) amplitude)
4. Fit each to power law: Φ_ℓ(r) = A_ℓ r^{-α_ℓ}
5. Verify:
   - α₀ = 1.0 ± 0.2 (Coulomb)
   - α₂ = 3.0 ± 0.5 (magnetic)
   - α₃ = 4.0 ± 0.5 (trefoil)
6. Check reconstruction: Φ₀ + Φ₂ + Φ₃ should match raw field to 1% RMS

**Success criterion:** Power-law exponents and amplitudes validated to ±5% accuracy.

---

### Phase 3: Orbital Energy Splitting (CALCULATION)

**Objective:** Place electron at r = a₀ (hydrogen ground state) and compute energy difference.

**Deliverable:** Numerical results in `cq38_lamb_shift.txt`

**Tasks:**
1. Extract Φ₂(a₀) and Φ₃(a₀) from Phase 2
2. Compute the quadrupole contribution to energy:
   $$\Delta E_2 = (3/2) \Phi_2(a_0) [P_2(\cos \pi/2) - P_2(\cos 0)]$$
   $$= (3/2) \Phi_2(a_0) [-1/2 - 1] = (9/4) \Phi_2(a_0)$$
3. Add trefoil harmonic correction:
   $$\Delta E_3 = \Phi_3(a_0) [\langle \cos(3\varphi) \rangle_{eq} - \langle \cos(3\varphi) \rangle_{pol}]$$
4. Convert to frequency (Hz, then MHz):
   $$\nu = \Delta E / h$$
5. Compare to measured Lamb shift: **1057.845 MHz** (NIST)

**Target accuracy:** Prediction within ±5% (i.e., 1005–1110 MHz)

**Success criterion:** Predicted Lamb shift ≥ ±5% of measured value, with correct sign E(s) > E(p).

---

### Phase 4: Angular Quantisation (PAPER)

**Objective:** Show that three-fold symmetry restricts angular states natively.

**Deliverable:** `CQ38_ANGULAR_QUANTISATION.md`

**Tasks:**
1. Derive the periodicity constraint from trefoil C₃ symmetry:
   - Single-valued wavefunction requires ψ(φ + 2π/3) = ψ(φ) up to phase
   - For ψ ∝ e^{imφ}, this forces m = 3k, k ∈ ℤ
2. Classify orbital states:
   - **s-like** (m₃ = 0, isotropic): couples to Φ₀ and ΦF₂ (equatorial)
   - **p-like (polar)** (m₃ = 0, perpendicular): couples to Φ₀ − (1/2)Φ₂
   - **p-like (trefoil)** (m₃ = ±3): couples to Φ₀ ± Φ₃
3. Enumerate states at n = 1 and n = 2:
   - 1s: 1 state (m₃ = 0) × 2 spin = 2 total
   - 2s: 1 state (m₃ = 0) × 2 spin = 2 total
   - 2p: 3 states (m₃ ∈ {−3, 0, 3}) × 2 spin = 6 total (matches QM: 2 + 6 = 8 at n=2)
4. Derive native selection rules:
   - Δm₃ ∈ {0, ±3, ±6, ...} (three-fold constraint)
   - Δℓ ≡ ±1 emerges when mapping to standard notation
5. Check consistency with observed spectral patterns

**Success criterion:** Native selection rules predict observed transitions; angular degeneracies match standard spectroscopy.

---

## Acceptance Criteria (Detailed)

| Phase | Criterion | Target | PASS | PARTIAL | FAIL |
|-------|-----------|--------|------|---------|------|
| 1 | Power-law exponents | 1.0, 3.0, 4.0 | All ±0.2 | One ±0.5 | Any >±0.5 |
| 1 | Theory foundation | First principles | All from spation + geometry | One fitted | >1 fitted |
| 2 | RMS fit error | <5% | <3% RMS | 3–5% RMS | >10% RMS |
| 2 | Reconstruction error | <1% | <1% RMS | 1–2% RMS | >5% RMS |
| 3 | Lamb shift | 1057.845 MHz | ±5% (1006–1110) | ±10% (952–1163) | >±10% |
| 3 | Energy sign | E(s) > E(p) | Correct | Correct | Reversed |
| 4 | Selection rules | m₃ = 3k | All transitions match | 80% match | <70% match |
| 4 | Degeneracies | Match QM | 2, 2, 6 at n=1,2 | Minor differences | Significantly off |

**Overall verdict:**
- **PASS:** All four phases pass; classification → Class C
- **QUALIFIED:** Phases 1–3 pass, Phase 4 partial; classification → Class C (conditional)
- **PARTIAL:** Phases 1–2 pass but Lamb shift > ±10% error; may indicate mechanism issue
- **FAIL:** Fundamental mechanism breaks (e.g., E(p) > E(s), power laws > ±1 error)

---

## Critical Assumptions (For Circularity Check)

1. **Trefoil topology (W=3):** Assumed from Law VI (w+1 conjecture, R_p = 4ℏ/(m_p c), match to muonic H)
   - *Check:* Is this circular? No — R_p is independently measured; W=3 follows from stability analysis.
   - ✓ Permitted input

2. **Three-fold symmetry:** Native from (2,3) knot parametrization
   - *Check:* Is this circular? No — comes from knot theory and topology.
   - ✓ Permitted input

3. **Power-law falloffs:** Derived from spation lattice physics (PPT06) + dimensional analysis
   - *Check:* Is this circular? No — r⁻¹ from occlusion, r⁻³ from circulation, r⁻⁴ from frequency content.
   - ✓ Permitted derivation

4. **Legendre polynomials P₂(cos θ):** Standard mathematical object
   - *Check:* Is this circular? No — arises naturally from the toroidal geometry (equatorial/polar symmetry).
   - ✓ Permitted tool (not borrowed concept, just mathematical language)

5. **Measured values (R_p, a₀, m_p, m_e, α):** From CODATA, muonic H, spectroscopy
   - *Check:* Is this circular? No — these are external inputs.
   - ✓ Permitted inputs

6. **No fitted parameters (no k_Lamb, no amplitude adjustments):**
   - *Check:* Is everything first-principles? Yes — all from geometry + constants.
   - ✓ Anti-circular protection

---

## Risk Assessment

### Low Risk (Expected to Pass)

1. **Power laws from dimensional analysis:** The r⁻¹, r⁻³, r⁻⁴ scaling is robust and doesn't depend on detailed field calculation.
2. **Lamb shift sign:** Physics predicts E(s) > E(p); would be refuted only if fundamental mechanism is wrong.
3. **Three-fold selection rule:** Follows from periodicity; cannot fail unless trefoil assumption is wrong.

### Medium Risk (Possible Refinement)

1. **Numerical coefficients:** Full lattice simulation may shift the predicted 1051.8 MHz by a few percent. Current prediction within ±5% is acceptable for Class C. [RETRACTED baseline — 1051.8 is the fished value; no earned baseline exists]
2. **Multipole power-law exponents:** May need ROOT-SIM to verify ±0.2 accuracy; theoretical justification is solid but numerical confirmation pending.

### High Risk (Would Falsify Mechanism)

1. **Lamb shift prediction fails by > ±5%:** Would indicate trefoil multipole mechanism is incomplete or wrong.
2. **Wrong sign for E(s) − E(p):** Fatal — contradicts the trefoil geometry hypothesis.
3. **Positronium has no fine structure:** Would contradict the claim that angular structure comes from nuclear topology.

---

## Dependency Chain

```
Law VI (W=3 topology)
    ↓
PPT06 (Spation traction: phase velocity, three outputs)
    ↓
APS04 (Phase 1–4: This investigation)
    ├─→ PPT08 (Angular DOF: RESOLVED)
    ├─→ Fine structure closure (now possible)
    └─→ CR04 (Hyperfine structure: neutron W=0 coupling)
         ↓
    ROOT-SIM (Lattice simulation for higher accuracy)
```

---

## Relationship to Standard Physics

| Standard QM Concept | SDT Native Equivalent | Mechanism Difference |
|-------------------|----------------------|----------------------|
| Orbital angular momentum ℓ | Radial node count + m₃ family | Emerges from trefoil wake, not from commuting operator |
| Spherical harmonics Y_ℓ^m | Trefoil multipole eigenbasis | C₃ symmetry instead of SO(3) |
| Fine structure (Sommerfeld) | Quadrupole multipole splitting | Classical field asymmetry instead of QED coupling |
| Lamb shift (QED) | Trefoil + electron wake mixing | Topological wake interaction instead of virtual photons |
| Hyperfine structure (nuclear spin) | Neutron W=0 + electron W=1 coupling | Winding topology interaction instead of nuclear moment |

**Key principle:** Every QM concept has an SDT equivalent that is **more fundamental** (derives from topology and geometry, not postulated).

---

## Investigation Products

### Deliverables

1. **`CQ38_TREFOIL_WAKE.md`** (Part I only)
   - Theory of trefoil wake geometry
   - Multipole decomposition (native, no QM harmonics)
   - Power-law justifications
   - Lamb shift mechanism overview

2. **`cq38_wake_field_solver.cpp`**
   - C++20 tool for computing trefoil wake field
   - Biot-Savart circulation source
   - Multipole decomposition via FFT
   - Power-law fitting
   - Lamb shift prediction
   - Outputs to `cq38_lamb_shift.txt`

3. **`cq38_lamb_shift.txt`**
   - Numerical results: Φ₀, Φ₂, Φ₃ at a₀
   - Predicted Lamb shift vs. measured value
   - Power-law exponents and fit errors
   - Comparison to muonic H and positronium tests

4. **`CQ38_ANGULAR_QUANTISATION.md`**
   - Three-fold symmetry constraint
   - Angular state classification (s, p, d, ...)
   - Wavefunction representation (SDT native vs. QM borrowed)
   - Selection rules derivation
   - n=1, n=2 state enumeration
   - Falsifiable predictions (P1–P3)

5. **`CQ38_VERDICT.md`**
   - Classification decision (Class C target)
   - Phase-by-phase results
   - Circularity check (not circular)
   - Impact on downstream work
   - Unblocked investigations

---

## Success Metrics (Summary)

| Metric | Target | Achieved? |
|--------|--------|-----------|
| Lamb shift prediction | ±5% of 1057.845 MHz | TBD |
| Power-law exponents | 1.0±0.2, 3.0±0.5, 4.0±0.5 | TBD |
| Fitted parameters | 0 (all first-principles) | TBD |
| Angular states at n=2 | 8 total (2s + 6p) | TBD |
| Selection rules match | Δm₃ ∈ {0,±3,...} → Δℓ = ±1 | TBD |
| Circularity check | Passes delete-test | TBD |

---

## Timeline and Milestones

- **Week 1:** Phase 1 (theory paper) + Phase 4 (angular quantisation) — COMPLETE
- **Week 2:** Phase 2 (numerical solver compilation + runs) — PENDING (environment)
- **Week 3:** Phase 3 (Lamb shift prediction from Phase 2 results) — DEPENDS ON WEEK 2
- **Week 4:** Verdict document, integration planning, next investigations

**Status:** APS04 is a **complete investigation spec**. Phases 1 & 4 (theory) are finished. Phases 2 & 3 (numerical) require a working C++20 compiler.

---

## References and Related Work

- **Engine/include/sdt/laws.hpp:812–870** — Law VI (Vortex Topology)
- **CQ14_Spation_Traction_from_Trefoil** — Phase velocity, traction ratio, three outputs
- **CQ09_Spation_Rotation** — Orbital velocity field v(r)
- **CQ34_Angular_DOF_from_Trefoil** — Problem statement (this solves it)
- **CONCEPTUAL_CONTAMINATION_AUDIT.md** — M1 (spherical harmonics contamination)
- **CODATA 2018** — Constants, fine structure constant, Compton wavelengths
- **NIST Hydrogen Spectroscopy** — Lamb shift 1057.845(9) MHz, fine structure data

---

**Status:** INVESTIGATION SPEC — READY FOR EXECUTION

All four phases are specified. Phases 1 & 4 (theory) are COMPLETE. Phases 2 & 3 (numerical) are deferred pending compilation environment.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — APS04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: atomic::, measured::R_inf, electropause / APS01
- Phase thresholds (committed before run): 1%, 5%, 5%, 5%, 5%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*APS04 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
