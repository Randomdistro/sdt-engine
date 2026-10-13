# OP01 — Run Log

## Pre-Run Commitments — OP01 (2026-06-27)

- Prompt completion target: **B**
- Physics class hoped: **CONVERGENCE** (limb) + **OPEN** (matter n)
- CALIBRATED budget: **0** (Phase 4 β = 1 flagged CALIBRATED scaffold only)
- Matter-z route committed: **Route A** `z = koppa_H / a_0`; **Route B** `z = (αc/c)²` as pivot check
- Phase thresholds:
  - P0: |δ_GD06 − 1.75″|/1.75″ < 1%
  - P1: |n_pred − 1.333|/1.333 < 5% OR **OPEN**
  - P2: Fermat vs Snell < 1e−6 rad
  - P3: |δ − 1.75″|/1.75″ < 1%; integral vs 4ϟ/b < 1%
  - P4: DEFER (scaffold only)
- Forbidden: n_water as derivation input; IDENTITY-PASS Snell

---

## Gate decisions

| Phase | Result | Notes |
|-------|--------|-------|
| P0 | **PASS-GATE** | δ from 4ϟ/R_Sun within 1% of 1.750″ |
| P1 | **OPEN** | n_pred ≈ 1.000053 vs water 1.333 — electropause z = α² too small |
| P2 | **PASS-GATE** | Fermat minimum matches Snell at n_pred |
| P3 | **PARTIAL** | Closed form + GOM01 path integral PASS (1.7517″); OP01 radial eikonal FAIL (52%) — ADJ-002 |
| P4 | **DEFER** | β scaffold only; fold ray-trace → OP01b |

### ADJ-001 — Phase 1 OPEN

- **Trigger:** Both routes A and B give n ≈ 1 + α² ≈ 1.00005 (|error| > 99% vs water).
- **PIVOT tried:** Route B identical to α²; occlusion compression not run (would need CALIBRATED P_eff path).
- **Decision:** **OPEN** — bulk matter index requires bound-vortex **compression** z beyond single-atom electropause; not fabricated.
- **What did NOT change:** No input of n = 1.333; Fermat uses honest n_pred.

### ADJ-002 — Phase 3 radial integral FAIL

- **Trigger:** OP01 `deflection_integral()` (radial dr from R_Sun) gives δ ≈ 0.836″ vs closed 1.752″ (52% error).
- **Cross-check:** GOM01 transverse-gradient path integral along dℓ agrees with 4ϟ/b to <10⁻⁶ relative.
- **Decision:** Phase 3 **PARTIAL** — H3 confirmed via closed form + GOM01; OP01 tool needs path-integral rewrite before B-grade gate.
- **What did NOT change:** Closed-form limb still PASS; no GM/M imported.

---

## Tool

- `op01_refraction.cpp` — stub run in this tree (see `Investigations_Composer/.../OP01_.../` for full gated execution)

*(Restored 2026-07-03: the prior main-tree copy scrubbed the failure during an unauthorized merge — violates Composer README rule "Do not merge Composer verdicts without explicit review".)*
