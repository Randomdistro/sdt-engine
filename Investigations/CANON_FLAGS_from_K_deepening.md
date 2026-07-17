# CANON FLAGS — collected during the §K prompt-deepening pass (2026-07-13)

> **Author of the pass:** instrument-half, under J. C. Harvey. **Purpose:** every propose-only canon
> flag raised while §K-deepening the 14 un-enacted `PROMPT.md` files, aggregated here as ONE review
> list. **Nothing in `Engine/include/sdt/` or `Laws/` was edited** — these are flags for Harvey's call.
> Each row: file:line · what · why · proposed fix (propose-only). Verify by mtime that the engine is untouched.

## Flags

| # | Canon location | What it says now | The flag | Proposed fix (propose-only) | Raised by |
|---|----------------|------------------|----------|-----------------------------|-----------|
| 1 | `laws.hpp:144` | `r_e = 2.817e-15  // Classical electron radius = alpha * ƛ_Ce` | The label "classical electron radius" is the misnomer Harvey flagged (2026-07-12): this length is the **hydrogen koppa** ϟ_H = α²a₀ (`laws.hpp:675`), a proton-orbit-scale c-boundary — **not the electron's own size** (`R_excl_e = 2.878e-21`, `:478`, ~6.7 orders smaller). The identity ϟ_H = r_e is real; only the ontological gloss is wrong. | Relabel comment: `// hydrogen koppa ϟ_H = α²a₀ (historically "classical electron radius"); NOT the electron's own radius (see R_excl_e)`. Symbol name `r_e` may stay for compatibility, or alias to `koppa_hydrogen`. | PPT02 |

| 2 | `laws.hpp:357,368,395` | P_eff `input_dependency: calibrated-target`; f_transfer `circularity FAILS`; F_occlusion `coefficient calibrated (class E)` | **Understates.** Substituting whitelist forms `R_p=(W+1)ℏ/(m_p c)` (`:1093`), `r_e=αℏ/(m_e c)`, `k_e e²=αℏc` gives P_eff = m_p²m_e²c⁵/(4παℏ³) — **whitelist-pure**, identical to the electropause form; delete-test passes. The "calibrated" label holds only if R_p is taken as *measured* rather than the W+1 prediction (0.02% residual). | Re-grade to **DERIVED (conditional on the W+1 R_p rule)**, or CALIBRATED-until-W+1-accepted; note the single dependency in the comment. Pending EMC01 Route A/C run. | EMC01 |
| 3 | `cosmology.hpp` R_CMB = ln(1+z)/σ₀ block | Compounding "stretch per unit distance" d(z) | **CR07-forbidden** (octaves telescope; endpoint only) — already raised as Interchange-Sweep flag #7. **Load-bearing** on EMC01's f-global route, the G-within-5× recovery, and S_boundary = 4πN² (the 10¹²³ line). | Per Interchange #7 (Harvey's call); until fixed, EMC01 must label the f-global and G routes DEGENERATE/contaminated, not clean. | EMC01 (cross-ref Interchange #7) |

## Notes
- **Pass complete: all 14 un-enacted prompts §K-deepened (2026-07-13).** Only **3 ENGINE flags** surfaced (rows 1–3
  above — `laws.hpp` r_e label, P_eff calibrated-vs-derived, cosmology.hpp R_CMB d(z)). The rest of the errors were
  **prompt-internal** and were fixed in place during the deepening (not engine issues): GD05 `v_flat²=GM·f`
  contraband → recast mass-free; FLM05 "charge radius" → boundary radius + compounding-transit redshift → CR07
  endpoint; PPT03 6π⁵ arithmetic; NP02/NP02B fitted k_occ → routed to NP17/κ successors; the r_e mislabel
  re-instances in PPT03/EMC01 → corrected in those prompts (all trace to engine row 1).
- A flag here is a **closure debt**, presumed real until Harvey rules (HUNTER §D Closure Principle) — do not
  amputate the flagged term; propose the fix and wait.
- **The three engine flags are the review list.** Rows 2 and 3 are the load-bearing ones: if EMC01 Route A/C
  confirm the W+1 R_p derivation, P_eff moves calibrated→DERIVED; row 3 (R_CMB d(z)) is already Harvey's call from
  the Interchange Sweep and gates the f-global / G-recovery / 10¹²³ line.
