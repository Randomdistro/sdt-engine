# GD05: Galaxy Rotation Curves from Eclipse Saturation — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
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

---

## 1. The Question

Galaxy rotation curves are flat at large radii: v(r) → constant instead of falling as r^(-1/2). Standard physics invokes dark matter halos. SDT explains this through **eclipse saturation**: beyond a critical radius, the convergence pressure is fully occluded by the visible disk, and further material experiences a saturated (constant) pressure deficit → constant orbital velocity.

Can SDT's eclipse saturation model reproduce the measured rotation curves for 50+ galaxies from the SPARC database using ONLY the visible baryonic mass, with ZERO free parameters?

## 2. Methodology

### Phase A: The eclipse saturation model

1. At any radius r in the galactic plane, the convergence pressure arrives from all 4π steradians
2. The galactic disk OCCLUDES a fraction of this convergence
3. At small r (inside the disk): occlusion grows with r → v(r) rises
4. At large r: the entire disk subtends a solid angle Ω_disk → if Ω_disk ≥ 2π, the convergence deficit from the disk direction is SATURATED
5. Beyond saturation: v(r) = constant = v_flat

The transition radius where Ω_disk ≈ 2π can be computed from the disk scale length h and scale height z₀:

$$r_{\text{sat}} \approx h \times \Sigma_0 / \Sigma_{\text{crit}}$$

where Σ_crit is the surface density at which the disk becomes convergence-opaque.

### Phase B: Compute SDT rotation curves

For each SPARC galaxy:
1. Take the baryonic surface density profile Σ(r) = Σ_disk(r) + Σ_gas(r)
2. At each radius r, compute the solid angle subtended by ALL baryonic material inside r (treated as an extended occlusion screen)
3. The convergence deficit at r determines v(r)²:
   - Below saturation: v(r)² ∝ integrated occlusion ∝ M_bar(< r) / r (Keplerian)
   - At saturation: v² → constant
4. The flat velocity should be: v_flat² = GM_bar,total × f(geometry) where f encodes the saturation

### Phase C: Fit-free comparison

For each galaxy, compute:
- V_SDT(r) from the baryonic mass profile + eclipse saturation model
- Compare to V_obs(r)
- Compute residuals: (V_obs − V_SDT) / V_obs

### Phase D: The BTFR test

The Baryonic Tully-Fisher Relation (BTFR): M_bar ∝ v_flat⁴
- Standard: this requires fine-tuning of dark matter halos
- SDT: this should emerge NATURALLY from eclipse saturation geometry
- Verify: does the SDT model predict BTFR with the correct normalization?

## 3. Required Outputs

1. **Rotation curve fits**: SDT vs observed for ≥50 SPARC galaxies
2. **Residual statistics**: Mean, RMS, and scatter of (V_obs − V_SDT)/V_obs
3. **BTFR plot**: M_bar vs v_flat⁴ from SDT model
4. **Comparison**: SDT model accuracy vs NFW dark matter halo accuracy vs MOND accuracy
5. **Eclipse saturation diagram**: Showing how the solid angle saturates at r_sat

## 4. Success Criteria

- [ ] ≥50 galaxies fitted
- [ ] RMS residual < 20% (comparable to dark matter models)
- [ ] BTFR reproduced with correct slope (≈4) and normalization
- [ ] Zero free parameters (no dark matter halo mass or concentration fitted)
- [ ] If SDT fails for a galaxy class: identify which class and why
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GD05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: galactic.hpp, GD01 eclipse saturation
- Phase thresholds (committed before run): 20%
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

*GD05 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
