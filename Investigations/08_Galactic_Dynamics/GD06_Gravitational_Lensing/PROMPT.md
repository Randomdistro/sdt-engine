# GD06 — Gravitational Lensing from Convergence Gradient (Refraction)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → **ACTIVE** on first gated run.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `bridge::koppa_Sun`, `depth_closure::`, `measured::R_Sun` — **no G/M**.
> **Prior audit:** Solar 1.75″ only via closed form — prompt requires **eikonal integral** + cluster stub.

---

## ⓪ The Golden Rule

1. **Gap:** Is lensing **gradient-index refraction** with `n=1/(1−z)`, same as OP01, not a separate GR module?
2. **Stakes:** SLACS tests; OP01 unification; zk² closure at solar limb.
3. **How:** Phase 0 small-angle check; Phase 1 numeric eikonal for Sun; Phase 2 compare to `4ϟ/b`; Phase 3 illustrative cluster koppa from v,R.
4. **Falsify:** Integral ≠ 4ϟ/b by >1%; δ off >1% vs 1.750″; OP01 formalism mismatch.
5. **Done:** **B** = integral + closed form agree + limb <1%; **A** = one SLACS-scale lens from measured v,R.

---

## ① Executive Summary

**δ(b) = 4ϟ/b** is the small-angle limit. **Question:** Does integrating `d/ds(n t̂)=∇n` along a grazing solar ray reproduce 1.750″ and match the closed form to <1%?

---

## ② Framework

`n(r) = 1/(1 − ϟ_⊙/r)` for r ≥ R_Sun (weak-field). **Targets:** δ = 1.750″ at b = R_Sun.

**Cross-check OP01:** Same n(r) as OP01 Phase 3.

---

## ④ Phases

### Phase 0 (GATE)

Print `ϟ`, `k_Sun`, `z_surf`; verify `δ = 4ϟ/R_Sun` in arcsec to 1%.

### Phase 1 — Eikonal integral (GATE)

- Integrate deflection (Simpson, ≥1000 steps) for `n(r)=1/(1−ϟ/r)`.
- **Success:** `|δ_int − δ_4k|/δ_4k < 0.01` and `|δ − 1.75″|/1.75″ < 0.01`.

### Phase 2 — OP01 linkage

- Print `n(R_Sun)` from same closure; reference OP01 tool path.

### Phase 3 — Cluster (DEFER or illustrative)

- **If DEFER:** state SLACS needs per-lens `koppa` from `v_circ`, `R` — no `koppa=1e15` without label ASSUMED.

---

## ⑤ Dual verdict

| Prompt | |
|--------|--|
| **B** | Ph 0–2 PASS |
| **D** | Closed form only |
| **F** | Illustrative koppa claimed as result |

---

## ⑥ Outputs

`gd06_gravitational_lensing.cpp`, `gd06_results.txt`, `RUN_LOG.md`, `GD06_VERDICT.md`, `GD06_DERIVATION.md`.

---

## ⑩ Pre-Run Commitments

```markdown
- Limb error < 1%
- Integral vs 4ϟ/b < 1%
- Forbidden: illustrative cluster numbers without ASSUMED tag
```

---

*GD06 · integrate the same n(r) OP01 uses — do not stop at the headline formula.*
