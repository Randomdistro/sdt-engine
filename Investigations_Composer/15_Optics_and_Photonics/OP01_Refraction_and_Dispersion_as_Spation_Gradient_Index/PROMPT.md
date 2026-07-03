# OP01 — Refraction and Dispersion as a Spation Gradient-Index Medium

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → **ACTIVE** on first gated run.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` — use `depth_closure::`, `bridge::`, `measured::` only.
> **Prior audit (2026-06-27):** stub `op01_refraction.cpp` failed prompt fidelity (OBSERVED n, no Fermat,
> no 1.75″ integral). This prompt supersedes that execution path.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** Whether optical refraction (glass, water) and gravitational light bending
   (solar 1.75″) are **one** mechanism — local relay speed set by convergence depth
   `c_local = c(1−z)`, `n = c/c_local` — or two unrelated fits.
2. **Why does it matter?** Unifies OP01 with GD06/GOM01; enables the solar lens-artifact falsifier
   (multi-λ limb fold); removes “photon slows in matter” as a separate ontology.
3. **How will we find out?** Four gated phases: derive `n` from `z` (no lab-n inputs) → Fermat/Snell
   from relay time → thin lens + solar eikonal integral → dispersion scaffold + fold band (qualitative
   minimum).
4. **What would prove us wrong?** Snell not from Fermat; 1.75″ off >1% with native integral; water
   `n` not from bound-vortex `z` to 5%; solar fold absent at predicted λ band.
5. **How will we know we're done?** Dual verdict: prompt completion ≥ **B** (Phases 1–3 PASS-GATE);
   physics class **NATIVE** or honest **CONVERGENCE/DEGENERATE** (solar limb may tie GR — say so).

---

## ① Executive Summary

Light in SDT is an **emission** — a phase-impulse relayed spation-to-spation. Local relay speed is
set by convergence depth (Depth–Closure Theorem, `depth_closure` in `laws.hpp`):

$$\boxed{z = \frac{\varkappa}{r} = \frac{1}{k^2} = \left(\frac{v}{c}\right)^2}, \qquad
c_{\text{local}} = c_\infty(1-z), \qquad n = \frac{c_\infty}{c_{\text{local}}} = \frac{1}{1-z}$$

**Question:** Can Snell's law, thin-lens imaging, total internal reflection, the solar limb deflection
(1.750″), and (schematically) dispersion `n(λ)` all follow from this **single** gradient-index medium
— with matter and vacuum differing only in how `z` is sourced?

**Stakes:** If Phase 3 shows 1.75″ from the same `n(r)` that Phase 1 uses for water (different `z`
source, same formula), optics ≡ lensing is earned. If only the solar case works, matter optics stays
**OPEN**.

**Expected landing:** Class **C (CONVERGENCE)** on limb deflection (equivalency with GD06); Class **A**
only if water `n` emerges from bound-vortex `z` without CALIBRATED inputs.

---

## ② Physical Context

**Mechanism.** Every medium — water, glass, or the solar convergence well — is a region of altered
spation closure. Tighter closure ⇒ shorter relay step ⇒ lower `c_local` ⇒ higher `n`. Refraction is
the emission steering along the **least relay-time** path through `n(r)` (Fermat), not “photon mass”
or metric curvature as primitive.

**Variables (define all; use SI unless noted):**

| Symbol | Definition | Source in engine |
|--------|------------|------------------|
| `z` | Convergence depth `ϟ/r` | `depth_closure::depth(koppa, r)` |
| `ϟ` | Koppa length `v²R/c² = R/k²` | `bridge::koppa_*` |
| `k` | Velocity hierarchy rung `c/v` | `bridge::k_*` |
| `c_∞` | Remote relay speed | `measured::c` (local rung; C4 caveat OK) |
| `c_local` | `c_∞(1−z)` | `depth_closure::c_local` |
| `n` | `1/(1−z)` weak-field | derived; **invalid for z≥1** |
| `θ` | Ray angle w.r.t. interface normal | radians internally |
| `b` | Impact parameter (solar ray) | [m] |
| `λ` | Emission wavelength | [m] — spectroscopic OBSERVED when used |
| `ℓ_P` | Planck length | `measured::l_P` |

**Targets (OBSERVED — comparison only, never inputs to SDT chain):**

- Water `n ≈ 1.333` (visible)
- Crown glass `n ≈ 1.52` (typical)
- Solar limb deflection `δ = 1.750″` (VLBI)
- Snell, thin-lens `1/f = (n−1)(1/R₁−1/R₂)`, TIR `θ_c = arcsin(n₂/n₁)`

**Native vs borrowed narration:**
- **Native:** relay time, closure depth, koppa, occlusion pressure gradient
- **Forbidden as mechanism:** photon rest mass, QED vacuum polarisation, metric `g_μν`, “spacetime bends”
- **Allowed as check:** eikonal ray equation (geometric optics limit of relay least-time — not wavefunction)

**zk² = 1 anchor:** Hydrogen ground rung: `z_H · k_H² = 1` with `k_H = 1/α`, `z_H = (v₁/c)²` —
verify once per run as **IDENTITY** check, not as a free parameter.

---

## ③ Theoretical Framework

**Build on (read before coding):**
- `depth_closure` — `c_local`, `depth`, `v_bound`, `z_spectral_Sun`
- `bridge::k_Sun`, `bridge::koppa_Sun`, `measured::R_Sun`
- GOM01/GD06 — deflection `δ ≈ 4ϟ/b` (must be cross-checked in Phase 3, not assumed PASS)
- Law V — movement budget (low-z limit for `c_local`)

**Working hypotheses (test in order):**

- **H1 (index = closure ratio):** `n(r) = 1/(1−z(r))` for `z ≪ 1`; matter `z` from bound vortex
  occlusion depth, vacuum `z = ϟ_⊙/r`.
- **H2 (Snell = Fermat):** Stationary relay-time across a **planar** interface between uniform
  `n₁`, `n₂` ⇒ `n₁ sin θ₁ = n₂ sin θ₂`; TIR when no real refracted path.
- **H3 (lensing ≡ refraction):** Integrating `d/ds(n t̂) = ∇n` for solar `n(r)` gives `δ(b=R_⊙) ≈ 1.75″`
  to **<1%** — same formalism as Phase 2 interface.
- **H4 (dispersion — scaffold):** `n(λ) = n₀ + β(ℓ_P/λ)²` as leading granularity coupling;
  solar fold **qualitative** at T-minimum shell (**Phase 4 minimum**).

**Hard prohibitions:**
- Do **not** set `n_water = 1.333` (or any lab index) as an input to the SDT derivation chain.
- Do **not** use `GM`, `M`, `G` in any calculation path.
- Do **not** call Snell algebra with observed `n` a PASS on H2 — H2 requires Fermat stationarity
  demonstrated on a **computed** interface.

**Weak-field break (CR10 precedent):** If any computed `z ≥ 1`, `(1−z)` form is **KILLED** for that
regime; pivot to piecewise or **OPEN** — document in ADJ.

---

## ④ Investigation Strategy

### Phase 0 — Baseline & ledger (≤30 min) — **GATE: required before Phase 1**

- **Goal:** Reproduce known solar surface quantities from engine; commit thresholds in `RUN_LOG.md`.
- **Method:** Print `z_sun = bridge::koppa_Sun / R_Sun`, `n_sun = 1/(1-z_sun)`, `δ_GD06 = 4ϟ/R_Sun`
  in arcsec; compare `δ_GD06` to 1.750″.
- **Success:** `|δ_GD06 − 1.750|/1.750 < 0.01` (sanity — if this fails, **STOP**, fix engine refs).
- **Out of scope:** Matter indices.

### Phase 1 — Index from closure (matter + vacuum) — **GATE: no lab-n inputs**

- **Goal:** Compute `n` for (a) solar vacuum at `r = R_Sun`, (b) water-like bound matter from SDT `z`.
- **Method (matter — primary route):**
  1. Bound hydrogen electropause: `r ~ atomic::bohr_radius(1,1)`, `k_H = 1/measured::alpha`,
     `ϟ_H = bridge::koppa_hydrogen` or `r_e` scale per EMC04 electropause notes.
  2. `z_matter = depth_closure::depth(koppa_H, r)` **or** electron circulation depth
     `z = depth_closure::depth_from_v(α·c)` — **commit one route in RUN_LOG before run**.
  3. `n_pred = 1/(1-z_matter)`.
- **Method (alternate route — use only on PIVOT):** Effective occlusion compression
  `z = (π/4) P_eff R₁² R₂² / (P_conv r²)` at molecular density scale — label CALIBRATED if `P_eff`
  path used.
- **Success (committed):**
  - `|n_pred − 1.333|/1.333 < 0.05` for water-scale route **OR**
  - Document **OPEN** with computed `n_pred` printed; Phase 1 = **PIVOT**, not retro-PASS.
- **Failure trigger:** Error >5% on primary route → PIVOT to alternate; both >20% → **OPEN** matter-n.
- **Forbidden:** Hardcoding 1.333.

### Phase 2 — Snell & TIR from Fermat (analytic + numeric) — **GATE: H2**

- **Goal:** Derive Snell from relay-time stationarity; verify TIR critical angle.
- **Method:**
  1. **Analytic:** Planar interface `z=0`, `n₁`, `n₂` uniform. Relay time
     `T(θ₂) = n₁ d₁/c + n₂ d₂/c` with geometry linking `θ₁`, `θ₂`. Show `dT/dθ₂ = 0` ⇒ Snell.
  2. **Numeric:** For **computed** `n₁=1`, `n₂=n_pred` from Phase 1 (or 1.333 as **OBSERVED-TARGET
     column only** in a separate “convergence check” row — not as H2 pass):
     scan `θ₂`, find minimum `T(θ₂)`; compare to `asin(n₁ sin θ₁/n₂)`.
  3. **TIR:** For `n₁ > n₂`, find `θ_c` where refracted path vanishes; compare to `arcsin(n₂/n₁)`.
- **Success:**
  - Analytic Snell identity: exact.
  - Numeric Fermat minimum agrees with Snell to **< 10⁻⁶ rad** at `θ₁ = 45°`.
  - TIR: `|θ_c − arcsin(n₂/n₁)| < 10⁻⁶ rad`.
- **Failure trigger:** Numeric Fermat fails → check sign convention / branch; do not PASS H2 with
  `asin(n*sin(asin(sin/n)))` alone (**IDENTITY-PASS forbidden**).

### Phase 3 — Thin lens + solar eikonal integral — **GATE: H3**

- **Goal:** Recover thin-lens formula; integrate solar `n(r)` for limb deflection.
- **Method:**
  1. **Thin lens (symbolic):** Spherical interface, paraxial → `1/f = (n−1)(1/R₁−1/R₂)` from
     `n=1/(1−z)` at interface.
  2. **Solar ray:** Spherically symmetric `n(r) = 1/(1 − ϟ_⊙/r)` for `r ≥ R_Sun`, weak-field.
     Integrate eikonal / small-angle:
     `δ(b) = ∫ (∂n/∂r)(b/r) dr` or equivalent GD06 path `δ = 4ϟ/b` — **both must be computed** and
     agree to **<1%** at `b = R_Sun`.
  3. Compare `δ(R_Sun)` to **1.750″ OBSERVED**.
- **Success:**
  - `|δ − 1.75″|/1.75″ < 0.01`
  - Thin-lens numeric example: `f = R/(2(n−1))` matches formula for committed `n`, `R`.
- **Failure trigger:** >1% on limb → check weak-field, impact parameter, arcsec conversion; if still
  fail → **OPEN** unification (do not claim optics ≡ lensing).

### Phase 4 — Dispersion scaffold + solar fold (minimum) — **may DEFER**

- **Goal:** Leading `n(λ)` and qualitative fold band.
- **Method:**
  1. `n(λ) = n₀ + β (ℓ_P/λ)²` with `β` **DERIVED** from one lattice argument or **CALIBRATED(1)** —
     must be ledgered.
  2. Map solar `T(h)` minimum (~500 km) → `z(h)` → `n(h,λ)`; locate λ where limb radius derivative
     changes sign (fold).
- **Success (minimum):** `dn/dλ` sign matches crown-glass dispersion (blue bends more); fold band
  location stated in nm even if qualitative.
- **DEFER allowed:** Full false-colour ray-trace → OP01b follow-up if Phase 1–3 PASS-GATE.

---

## ⑤ Success Criteria — dual verdict

### Prompt completion (did we run what §④ asked?)

| Grade | Requirement |
|-------|-------------|
| **A** | Phases 1–4 PASS-GATE; water `n` native; no CALIBRATED |
| **B** | Phases 1–3 PASS-GATE; Phase 4 DEFER or partial |
| **C** | Phases 2–3 PASS; Phase 1 OPEN or PIVOT with documented `n_pred` |
| **D** | Only Phase 0 + Snell identity |
| **F** | Snell-only with OBSERVED `n` input; or missing solar integral |

### Physics class (what did SDT earn?)

| Class | Condition |
|-------|-----------|
| **NATIVE** | H1+H2+H3 from closure; matter `n` within 5% native |
| **CONVERGENCE** | Limb + Snell match; matter `n` OPEN or CALIBRATED |
| **DEGENERATE** | 1.75″ matches because ϟ ↔ GM/c² (say so explicitly) |
| **KILLED** | Fermat ≠ Snell; or `n=1/(1−z)` breaks in all regimes |
| **OPEN** | Phase 1 matter index unsolved |

---

## ⑥ Outputs (exact files)

1. **`OP01_DERIVATION.md`** — H1–H3 analytic steps; weak-field validity; zk² identity note.
2. **`op01_gradient_index.cpp`** — **canonical tool name** (rename from `op01_refraction.cpp` via ADJ if needed):
   - Phase 0 table
   - Phase 1 `n_pred` computation (no lab-n input)
   - Phase 2 Fermat scanner + TIR
   - Phase 3 solar integral + thin-lens check
   - Phase 4 optional dispersion stub
3. **`op01_results.txt`** — stdout capture; columns: `[quantity | value | tag | target | err | PASS]`
4. **`RUN_LOG.md`** — pre-commit block + ADJ entries + gate decisions
5. **`OP01_VERDICT.md`** — **dual verdict header** + updated falsification table

---

## ⑦ Dependencies & References

**Upstream (required):** `depth_closure`, GOM01, GD06 (cross-check only), EMC04 (electropause for matter-z),
CR10 (weak-field break at z≥1).

**Downstream:** Solar lens-artifact experiment; fibre optics; GD06 cluster fits.

**Related:** E72 (c in media), E94 (convergence lens), OP01b (full fold ray-trace).

---

## ⑧ Falsification Tests

| ID | Hypothesis | Predicted | If FAIL → |
|----|------------|-----------|-----------|
| T1 | `n = 1/(1−z)` for matter | `n_pred` within 5% of 1.333 | PIVOT route B; then OPEN |
| T2 | Snell from Fermat | numeric min T ↔ Snell < 10⁻⁶ rad | KILL H2; check derivation |
| T3 | TIR angle | `θ_c` match < 10⁻⁶ rad | implementation bug or H2 KILL |
| T4 | Solar limb | `δ` within 1% of 1.75″ | OPEN unification; check integral |
| T5 | Same `n` formalism | Phase 2 interface uses same `n(z)` as Phase 3 | optics ≠ lensing |

---

## ⑨ Implementation Notes

- **Precision:** `double` throughout; angles in rad internally, degrees in print only.
- **Eikonal:** Use small-angle or exact spherical deflection per GOM01/GD06 — commit formula in RUN_LOG
  before comparing to 1.75″.
- **Arcsec:** `206264.806247″/rad`; solar limb `b = R_Sun`.
- **Build:**
  ```bash
  g++ -std=c++20 -IEngine/include op01_gradient_index.cpp -o op01
  cl /std:c++20 /EHsc /O2 /I Engine/include op01_gradient_index.cpp /Fe:op01.exe
  ```
- **Self-audit each commit:** (a) lab `n` not in derivation? (b) Fermat not faked? (c) dual verdict written?

---

## ⑩ Adaptive Execution Protocol

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — OP01
- Prompt completion target: B
- Physics class hoped: CONVERGENCE (limb) + OPEN or NATIVE (matter n)
- CALIBRATED budget: 0 (Phase 4 β only if Phase 4 run — max CALIBRATED(1))
- Matter-z route committed: [koppa_H/a0 | depth_from_v(αc) | — fill before Phase 1]
- Phase thresholds:
  - P0: |δ_GD06−1.75″|/1.75″ < 1%
  - P1: |n_pred−1.333|/1.333 < 5% OR OPEN
  - P2: Fermat vs Snell < 1e-6 rad; TIR < 1e-6 rad
  - P3: |δ−1.75″|/1.75″ < 1%
  - P4: DEFER allowed if P1–P3 PASS-GATE
- Forbidden retroactive changes: n_water input; tolerance widening; IDENTITY-PASS on Snell
```

### Pivot table

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| P0 δ off >1% | Verify `koppa_Sun`, arcsec conversion | STOP — engine bug | Fit ϟ |
| P1 n error >5% | Alternate matter-z route (see §④ Phase 1) | **OPEN** matter index | Input 1.333 |
| P1 z ≥ 1 | Piecewise n; restrict to z<0.1 for (1−z) | **OPEN** or exponential n | Ignore break |
| P2 Fermat fail | Flip normal/sign; increase scan resolution | KILL H2 | Snell reciprocity only |
| P3 δ off >1% | Full eikonal vs 4ϟ/b cross-check | **OPEN** H3 | Claim PASS anyway |
| P4 fold missing | CALIBRATED(1) on β only, documented | DEFER Phase 4 | Fake fold λ |

### Allowed adjustments
- Mesh/step size for Fermat scan
- Alternate **native** matter-z routes listed in Phase 1
- Rename tool to `op01_gradient_index.cpp` (ADJ-001)
- DEFER Phase 4 after B-grade Phases 1–3

### Disallowed adjustments
- RETRO-PASS on 5% / 1% thresholds
- Using OBSERVED `n` in Phases 1–2 derivation path
- Reporting Prompt completion A if Phase 3 integral absent

---

*Spatial Displacement Theory · OP01 · one n( r ), two regimes, adjust the route not the truth.*
