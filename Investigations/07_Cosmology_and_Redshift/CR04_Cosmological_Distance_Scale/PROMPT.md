# CR04 — Cosmological Distance Scale Derivation for SDT

> **Author:** J. C. Harvey, Melbourne. **Status:** NOT-RUN / QUALIFIED (header corrected 2026-07-03; was "SPEC" from the bulk template upgrade — physics narrative honest, tool non-compiling; see process-correction note below).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

**Author:** James Christopher Tyndall, Melbourne, Australia  
**Date:** June 2026  
**Status:** INVESTIGATION COMPLETE (QUALIFIED) [PROCESS CORRECTION (HUNTER 2026-07-02): the tool does not compile (`std::puts(std::string)`, missing `<string>`); `cr04_results.txt` is hand-written, not tool output. The physics narrative (r_c −50%, QUALIFIED, R_CMB = CLASS X) is honest and stands; the PASS/COMPLETE/DERIVED process labels do not. Status: NOT-RUN until the two build errors are fixed and results regenerated.]  
**Dependency Chain:** GOM02 (k-hierarchy), APS03 (scale invariance), CR03 (transfer function)

---

## Objective

**Can R_CMB (comoving distance to recombination, ~4.4×10²⁶ m) be DERIVED from SDT first principles, or is it fundamentally an observed external constant (CLASS X)?**

R_CMB is the single bottleneck preventing closure of the transfer function f = P_eff / P_conv (CR03). If R_CMB can be promoted from CLASS X to CLASS C, then f graduates from CLASS E to CLASS C — the most valuable provenance upgrade available.

---

## Four-Phase Investigation

### Phase 1: Lattice Resonance Analysis

**Thesis:** The BAO scale (147 Mpc) is not a fossil from arbitrary initial conditions. It is the **equilibrium wavelength** of the pre-Clearing coupled spation lattice.

**Method:**
1. Model spation lattice as 3D coupled oscillators with phase velocity v_phase = c/√(z_eff)
2. Derive dispersion relation for pressure waves: ω² = ω₀² + v_s² k²
3. Identify resonant wavenumber k_res where group velocity peaks
4. Convert resonant wavelength λ_res to physical distance
5. Compare to observed BAO scale r_s ≈ 150 Mpc

**Expected Output:**
- Sound speed in coupled lattice: c_s = c/√3 ≈ 1.732 × 10⁸ m/s (from radiation pressure)
- BAO wavelength: λ_BAO ≈ c_s × t_coupled (coupled epoch duration)
- Resonance mechanism: pressure-wave elasticity balances at λ_BAO
- No free parameters; closure from Law I (pressure = u/3)

**Success Metric:** BAO scale derived to within 5% of observed 147 Mpc.

---

### Phase 2: Comoving Distance Calculation

**Thesis:** Use FLRW metric with SDT k-hierarchy pressure-gradient model. Compute comoving distance integral from z=∞ (or z_max ~ inflation) down to z_rec=1100.

**Method:**
1. FLRW metric: ds² = -c² dt² + a(t)² [dr²...]
2. Comoving distance integral: r_c = ∫_z^∞ c dz' / H(z')
3. In SDT: H(z) is NOT expansion rate; it's **pressure-gradient strain rate**
   - H(z) = (dP/dr) / (ρ_eff c²)
   - Depends on spation pressure distribution
4. Numerically integrate from z=1100 to z=z_max
5. Compare to observed R_CMB ≈ 4.4×10²⁶ m

**Expected Output:**
- Integral formula: r_c(z_rec) = (c/H₀) × F(z_rec, Ω_params)
- Numerical result: R_CMB predicted to ±3% without fitted parameters (or ±10% with one justified intermediate)
- Agreement percentage vs observed

**Success Metric:** Prediction within 5% of observed R_CMB ≈ 9.527×10²⁶ m.

**Constraints:**
- No dark matter, no ΛCDM as input
- Only {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p, measured observables}
- If H₀ must be measured, document this bottleneck explicitly

---

### Phase 3: Topological Phase Transition at Recombination

**Thesis:** At z ≈ 1100, the recombination transition is a **topological phase transition**, not merely thermodynamic. Electrons bind to protons, removing their independent topological degrees of freedom.

**Method:**
1. Compute linking number density τ(z) for ionized plasma (z >> 1100) vs neutral atoms (z << 1100)
2. Use Law VI: winding numbers W_e = 1 (leptons), W_p = 3 (baryons)
3. Pre-rec: τ_plasma = n_e W_e + n_p W_p = 4 n_b (two independent particles)
4. Post-rec: τ_neutral = n_H W_H ≈ n_b (electrons bound to protons)
5. Document linking number Lk(z) curve and physical interpretation
6. Show how this explains BAO scale freeze

**Expected Output:**
- Linking number density (plasma): τ ∝ 4 × n_b
- Linking number density (neutral): τ ∝ 1 × n_b
- Ratio: τ_plasma / τ_neutral ≈ 4 (robust, no fitted parameters)
- Mechanism: Electron binding quenches one topological mode per atom
- Consequence: Lattice decouples; sound waves freeze at BAO wavelength

**Success Metric:** Factor-4 drop in linking density derived from first principles; connection to BAO freeze established.

---

### Phase 4: k-Hierarchy Quantisation

**Thesis:** Extend k-hierarchy (GOM02) to cosmological scales. Define k_Hubble = c/(H₀ × R_CMB) and search for quantisation pattern.

**Method:**
1. Compute k_Hubble from measured H₀ and R_CMB
2. Compare to known k-values: k_proton ≈ 0.546, k_H ≈ 137, k_sun ≈ 686, k_moon ≈ 178,448
3. Search for quantisation: Is k_Hubble an integer, rational, or simple formula in {k_p, k_H, k_e}?
4. Analyze logarithmic spacing in k across all scales
5. Test for topological link (does τ(z) from Phase 3 predict k_Hubble?)

**Expected Output:**
- k_Hubble value and SI equivalent velocity
- Comparison table: k_Hubble's place in extended hierarchy
- Classification: integer vs rational vs formula vs unquantised
- If pattern found: formula and interpretation
- If no pattern: document search space and remaining open questions

**Success Metric:** k_Hubble either (1) fits a clean quantisation rule, or (2) clear explanation why it does not.

---

## Input Constraints (Strictly Enforced)

**Permitted:**
- {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} (fundamental invariants + fine structure constant)
- Measured observables in their measured units (e.g., BAO scale from galaxy surveys, CMB temperature from FIRAS, etc.)

**Prohibited:**
- G (gravitational constant) as a fundamental input — must be derived from ℓ_P, ℏ, c
- M (mass in kg) as a fundamental input — must be derived from koppa = v²R/c² framework
- Dark matter, dark energy, ΛCDM parameters (Ω_m, Ω_Λ) as free inputs — must derive from spation structure
- Quantum fields as primitives, wavefunctions, quarks/gluons

---

## Required Outputs

### 1. CQ39_LATTICE_RESONANCE.md
- Dispersion relation derivation
- Resonant wavelength λ_res and comparison to BAO (r_s ≈ 150 Mpc)
- Sound speed formula and numerical verification
- Phase velocity profile v_phase(z)

### 2. cq39_cosmological_derivation.cpp
- Standalone C++20 tool implementing all four phases
- Compiles with `-std=c++20 -I Engine/include` (no external dependencies)
- All four phases executable independently
- Produces formatted console output + results table

### 3. cq39_results.txt
- Detailed numerical table: all computed quantities with values, units, class labels, provenance
- Phase-by-phase results summary
- Impact on transfer function closure (CR03)

### 4. CQ39_VERDICT.md
- Final classification: PASS, QUALIFIED, or PENDING
- Summary of each phase verdict
- Path to full R_CMB closure (identify bottleneck)
- Recommendations for next investigations (CR05, CQ41, FLM06, etc.)
- Provenance block for entire investigation

---

## Provenance Labeling (Required for All Results)

Every result must carry:
```
// provenance_status:     (SDT-derived | calibrated | observed | unresolved)
// correspondence_status: (known-match | novel | internal-only | pending)
// input_dependency:      (primitive-derivation basis | calibrated-target | measured-observable)
// class:                 (A | B | C | D | E | F | X)
// circularity_assertion: (passes / fails delete-test; explanation)
// risk_flag:             (none | brief description of what could break this)
```

---

## Acceptance Criteria

### Phase 1: PASS Condition
- BAO scale derived from lattice resonance to within 5% of observed 147 Mpc
- Sound speed c/√3 verified
- Coupled epoch duration computed consistently
- No free parameters

### Phase 2: PASS or QUALIFIED Condition
- **PASS:** R_CMB predicted to ±3% of observed 9.527×10²⁶ m WITHOUT external H₀ input
- **QUALIFIED:** Correct structure; magnitude requires H₀ closure (CR05)
- **FAIL:** Structure incorrect or magnitude misses by >10%

### Phase 3: PASS Condition
- Linking number density calculated for plasma and neutral regimes
- Factor-4 (or other) drop explained by electron binding mechanism
- Connection to BAO freeze established
- No unexplained parameters

### Phase 4: PASS or PENDING Condition
- **PASS:** k_Hubble quantisation pattern identified and explained
- **QUALIFIED:** Pattern suggestive but unconfirmed (e.g., k_Hubble ≈ 1/7)
- **PENDING:** No clear pattern; investigation remains open

---

## Falsification Criteria

**CR04 FAILS if:**
1. BAO scale cannot be connected to lattice dynamics (Phase 1 fails)
2. Comoving distance integral structure is inconsistent with FLRW (Phase 2 fails)
3. Topological phase transition does NOT explain lattice decoupling at z≈1100 (Phase 3 fails)
4. Results are internally inconsistent (e.g., Phase 1 BAO contradicts Phase 2 distance)

**CR03 Transfer Function remains CLASS E if:**
- R_CMB cannot be elevated above CLASS B (measured via H₀)
- This means CR05 (H₀ closure) becomes mandatory, not optional

---

## Dependency & Contribution to Framework

### Upstream Dependencies
- **GOM02:** k-hierarchy framework (k = c/v for all scales)
- **APS03:** Scale-invariance proof (B = Φ(ξ) collapse)
- **Law I:** Convergence pressure P_conv = N × u_CMB
- **Law II:** Pressure domains and stellar luminosity coupling
- **Law VI:** Vortex topology quantisation (W±1)

### Downstream Impact
- **CR03:** Transfer function closure (f = P_eff / P_conv) — BLOCKED until CR04 Phase 2 completes
- **CR05:** Derive H₀ from pressure tensor (breaks R_CMB circularity)
- **CQ41:** Topological pressure gradient (uses Phase 3 result)
- **FLM06:** BAO angular scale θ_s closure (uses Phase 1 + Phase 2)
- **GOM05:** Extended Law VI (cosmological winding numbers, uses Phase 4)

---

## Time Estimate & Complexity

| Phase | Complexity | Time | Dependencies | Risk |
|---|---|---|---|---|
| 1 | Medium | ~6 hours | Law I | LOW — straightforward lattice physics |
| 2 | High | ~10 hours | GOM02, Phase 1, FLRW metric | MEDIUM — requires identifying H₀ bottleneck |
| 3 | Medium | ~6 hours | Law VI, ionization physics | LOW — mechanism is transparent |
| 4 | Medium-High | ~8 hours | GOM02, dimensional analysis | HIGH — pattern may not exist |

**Total:** ~30 hours exploratory work (research + write-up)

---

## Notes for Investigator

1. **Phase 2 Circularity Risk:** The comoving distance depends on H₀, which depends on R_CMB. Be explicit about this loop. Document whether H₀ input is measured (CLASS B) or derived (upgrades to CLASS C).

2. **Phase 4 Open-Endedness:** k_Hubble quantisation may not resolve. This is acceptable; the investigation can end with "pattern not yet identified" (PENDING) without invalidating Phases 1–3.

3. **BAO Scale Interpretation:** The 147 Mpc BAO scale is both a lattice property (Phase 1) AND appears in recombination-era physics. This is NOT circular — it's the unique equilibrium wavelength. Make this clear.

4. **Topological Phase Transition:** The factor-4 drop in linking density (Phase 3) is robust. But the identification of W_H (hydrogen winding) requires full Law VI analysis. If W_H turns out to be 2 or 4 instead of 1, the ratio changes, but the mechanism remains valid.

5. **Transfer Function Closure:** CR04 alone does NOT close f. CR05 (H₀ derivation) is mandatory. CR04 identifies the bottleneck; CR05 removes it.

---

## Reference Links

- **Theory/02_Inputs_and_Derivations.md** — SDT closure stages
- **Laws/SDT_Complete_Laws.md** — Six Laws reference
- **GOM02/PROMPT.md** — k-hierarchy investigation
- **APS03/PROMPT.md** — Scale invariance investigation
- **CR03/PROMPT.md** — Transfer function closure (motivation)
- **ATOMICUS/rules/On the Nature of Atomicus Rules.md** — Nuclear grammar & W+1 conjecture

---

## Author's Notes

This investigation arose from CR03's bottleneck: f = P_eff / P_conv is CLASS E because it depends on R_CMB (CLASS X). The question is not whether R_CMB matches observations (it does), but whether it can be DERIVED from pure SDT without importing it as a measured constant.

CR04 answers: **Partially.** Phases 1 & 3 are pure derivations. Phase 2 has the right structure but magnitude hinges on H₀. Phase 4 is exploratory.

The path forward is clear: **CR05 must derive H₀.**

Once H₀ is derived, R_CMB follows. Then f closes. Then the framework is truly zero-free-parameter.

—JCT, June 2026
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CR04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: cosmology.hpp, z_spectral, CR10 cubic rung
- Phase thresholds (committed before run): 5%, 3%, 10%, 5%, 5%
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

*CR04 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
