# FLM01: State28D Force Ratio Constants — INVESTIGATION RESULTS

> **Status**: RESOLVED (SUPERSEDED)
> **Date**: May 2026
> **Resolved by**: EMC01 (Transfer Function), GOM02 (k-Hierarchy Advantage)

---

## Question
Where do the hardcoded magic numbers `cmb_amplification = 1e30` and `kappa_factor = 1e-9` in state28d.hpp come from? Can they be derived from SDT quantities?

## Answer: SUPERSEDED — The Question is Moot

The force_ratio function with its hardcoded constants has been superseded by the canonical derivation in EMC01 and GOM02.

### How EMC01 Resolves This

The Coulomb-to-gravity hierarchy F_C/F_G ≈ 10³⁹ arises from:

```
F_C = (π/4) P_eff R_charge⁴ / r²     [Coulomb from occlusion]
F_G ≈ P_conv × V₁V₂ / (S_boundary × r²)   [gravity from shell-cancelled convergence]
```

The ratio:
```
F_C/F_G = P_eff × R_charge⁴ × S_boundary / (P_conv × V₁V₂)
        = f × S_boundary × R_charge⁴ / V₁V₂
```

This is entirely geometric — no fitted constants required. The "cmb_amplification = 1e30" was an attempt to capture part of this ratio without the full derivation.

### How GOM02 Resolves This

GOM02 showed that GM is a derived projection of ϟc² — the force hierarchy is a consequence of the cross-scale bridge:
- EM uses R_charge⁴ (atomic cross-section)
- Gravity uses V_disp² / ℓ_P² (macroscopic displacement)
- The 10³⁹ ratio is the geometric scaling between these cross-sections

### Status of state28d.hpp

The `cmb_amplification` and `kappa_factor` constants appear to have been removed or refactored from the current state28d.hpp. The force_ratio function is no longer needed — EMC01's `law_III::F_occlusion()` and the bridge namespace provide the canonical force calculations.

## Verdict

**FLM01 RESOLVED (superseded).** The hardcoded constants were placeholders. The correct derivation is in EMC01 (f = P_eff/P_conv) and GOM02 (k-hierarchy). No code implementation needed — the question is answered by existing investigations.
