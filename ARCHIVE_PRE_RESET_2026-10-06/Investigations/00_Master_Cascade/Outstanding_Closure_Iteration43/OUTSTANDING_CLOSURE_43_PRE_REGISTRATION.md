# Outstanding Closure Batch — Pre-registration (Iteration 43)

**Date:** 2026-08-12  
**Commit:** `3d2de341f711891662133d0e3ecf5ae51a19d48d`  
**Canon edits:** none  
**Upstream:** Iteration 42 ranked debts 1–5

## Scope (all five, single pass)

| ID | Claim under test | Decision labels |
|---|---|---|
| MM04 | Independent Law-III/lattice route to `koppa_per_baryon` beyond MM03 K0–K11 | `INDEPENDENT_SURVIVES` / `PARKED_PERMANENT` |
| OM03 | Shared-om path delay vs Cassini SCE1 admissible residual | `EMPIRICALLY_SURVIVES` / `PARKED_PARTIAL_FETCH` / `DEFINITION_BLOCKED` |
| NU01 | Scalar ν attenuation vs SNO appearance channels | `APPEARANCE_MECH_SURVIVES` / `SCALAR_EXCLUDED__MECH_UNDERDETERMINED` |
| CK01 | Constitutive `n(ω)` + Frank–Tamm yield from SDT without fitted bulk n | `CONSTITUTIVE_SURVIVES` / `ANGLE_COMPUTED__CONSTITUTIVE_OPEN` |
| NSEQ13 | Occupation/emission MeV from Shared∪matching seating | `ENERGY_MAP_SURVIVES` / `UNDERDETERMINED` |

## Global rules

- No post-hoc fitted κ after seeing targets.
- No edits to `Engine/include/sdt` or `Laws/`.
- Direct execution only; first instrument failures preserved then encoding/bug-only repairs.
- EMPIRICALLY SURVIVES requires held-out admissible data + closed observable definition.

## Hold-outs / gates

| ID | Hold-out / gate |
|---|---|
| MM04 | Target = engine `koppa_per_baryon`; candidates must not use `l_P` or `G` |
| OM03 | RSR path at `C:\sdt-data\cassini_sce1` must exist for residual EMPIRICALLY SURVIVES; ODF/TDF inventory alone ≠ survival |
| NU01 | SNO NC/CC appearance is OBSERVED comparison; scalar 1/3 survival is EXCLUDED a priori |
| CK01 | Water `n=1.333` is OBSERVED only for angle COMPUTED; constitutive must derive n without that input |
| NSEQ13 | NSEQ09 SEAL median ~4.2 MeV is OBSERVED hold-out; seating Shared=4 from NSEQ11 is frozen geometry |

## Forbidden

- Revive N·Om_H packing as ε_agg.
- Claim Law-III koppa without independent match.
- Claim Cassini EMPIRICALLY SURVIVES from order-of-magnitude Shapiro log alone.
- Neutrino “disappearance-only” scripts.
- Cherenkov energy independence while A_s remains imported (AS02).
- Promote NSEQ12 EXCLUDED TT/TQ split as energy rule.
