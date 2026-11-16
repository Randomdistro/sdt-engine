# NP09 — Verdict: Deuteron Binding from Occlusion

**Classification: RESOLVED-NEGATIVE (honest discrepancy documented).**
**Author**: James Christopher Tyndall, Melbourne · Tool: `np09_deuteron_binding.cpp`.

## Results

| Quantity | SDT occlusion | Measured |
|----------|---------------|----------|
| B_d | **0.060 MeV** | **2.224 MeV** |
| Relative error | **−97.3%** | — |

## Reverse engineering

- R_n,eff required to match B_d with atomic P_eff: **5.12 fm** (6.09× R_p).
- W+1 neutron radius 4ℏ/(m_n c) = **0.840 fm** ≈ R_p — physically reasonable scale, not 5 fm.

## Conclusion

The **1/r² occlusion structure** (Law III) is native; the **hydrogen-calibrated P_eff** does not transfer to nuclear binding at the measured 2.14 fm separation. The **NP17 shared-electron Coulomb route** (αℏc geometry, factor 3) hits 2.224 MeV without a fitted energy scale.

## Class

**E/PARTIAL** — magnitude mismatch; structural borrow at atomic P_eff. Nuclear binding requires the shared-electron / gear-frequency route (NP17), not raw F_occlusion with P_eff.

**Sign-off: FAIL on occlusion magnitude; PASS on honest documentation.**
