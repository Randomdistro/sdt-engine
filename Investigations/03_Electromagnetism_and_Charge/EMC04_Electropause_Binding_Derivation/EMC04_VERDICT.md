# EMC04 — Verdict

**Question:** What holds the electron at the Bohr radius, and can the binding (hence `P_eff`) be
derived without invoking charge?

**Verdict:** **RESOLVED [STRONG]** — *on the framework's terms.*

The Bohr radius is the **electropause** (pressure-balance boundary). The binding is the **centripetal
requirement**, `F = mₑ(αc)²/a₀ = 8.2387×10⁻⁸ N`, computed from **kinematics with no charge term** and
equal to the Coulomb / occlusion force to ratio **1.0000000000**. Inverting the occlusion law derives
the effective pressure:

```
P_eff = 4 F a₀² / (π R_charge⁴) = 5.2252×10³¹ Pa   (= engine law_III::P_eff, rel 4×10⁻¹²)
      = 4αℏc/(π R_p² r_e²)                          (closed form, no Coulomb input)
      = m_p² mₑ² c⁵ / (4π α ℏ³)                     (whitelist {m_e,m_p,c,α,ℏ}, rel 4×10⁻⁴)
```

The **delete-test passes**: P_eff computes with `k_e` and `e` removed from the inputs.

**Status change:** `P_eff` **E (CALIBRATED) → C (DERIVED)**. Closes the [[EMC01]] coefficient
circularity and completes the [[EMC03]] "two-locks" step.

**Honest residual (the entire caveat):** α is read as the kinematic k-rung ([[PPT02]]), not the Coulomb
coupling — so the closure holds on SDT's own terms; **the model does not derive α**, which remains the
one irreducible input. The whitelist form additionally uses `R_p = 4ℏ/(m_p c)` (W+1 conjecture) at the
2×10⁻⁴ level.

**Artifacts:** `cq49_electropause.cpp`, `cq49_results.txt` (4/4 PASS), `INVESTIGATION.md`.
Folded into `ATOMICUS/ATOMICUS_COMPLETE.md` as **Law 15 (The Electropause)**.

*J. C. Harvey, Melbourne, 2026-06-18.*
