# PPT18 stage 1: ProtOm deconstruction record (2026-10-12)

**Registration:** `PROMPT.md`, written before `ppt18_stage1.cpp`.
**Run:** single pass. Output `ppt18_stage1_results.txt`. Validations V1–V3 met.

## Findings

**1. The corpus holds six proton geometries, and they do not agree (K1–K4).**

| check | finding |
|---|---|
| K4, winding pair | Three different pairs for one proton: (2,3) in canon `topology` and NP30; (4,5) in the NSEQ16 braid repair; "4 tours × 3 cross-section turns" in the live engine. |
| K2, aspect R/a | Against the canon mode-locked law √(q/p): NSEQ16 registers 2.818 where canon gives 1.118 for (4,5). The live engine has 19.8, where canon gives 0.866 for (4,3). Neither sized geometry obeys the canon aspect law. |
| K1, envelope | The live engine's nucleon envelope R + a + b = 0.913 fm = **1.085 R_p**: it exceeds the rim it is meant to fill. NSEQ16's closes exactly at R_p. |
| K3, speed | Canon's Law V mode budget keeps every mode ≤ c. The 1.83c figure is hydrogen's ladder at R_p (the PPT06 phase speed). Canon reports both and does not reconcile them. |
| provenance | The live engine's 5.28 fm helix length and 0.06 fm strand diameter were not found in any investigation record. Canon `topology` (G1) gives speeds and an aspect but no absolute size. |

**2. The Ѻ_p matrix (no target exists; reported as a map).**

| geometry | tube a (fm) | v_P | D1: Ѻ_p = a v_P²/c² | D2 control (rigid rotation) |
|---|---|---|---|---|
| G1 (2,3), sized by assuming R + a = R_p | 0.378 | 0.775c | 0.227 fm | 0.488 fm, outside tube |
| G5 (4,5) braid | 0.185 | 0.745c | 0.103 fm | 0.248 fm, outside tube |
| G6 engine, read as (4,3) | 0.042 | 0.655c | 0.018 fm | 0.065 fm, outside tube |
| G6 engine, read as (2,3) speeds | 0.042 | 0.775c | 0.025 fm | 0.055 fm, outside tube |
| D3, action seat ħ/(m_p c) | — | — | 0.210 fm = R_p/4 | — |

- **D1 always lands inside the tube** (because v_P < c).
- **D2 always lands outside**, so the ruling ("well inside") excludes rigid poloidal rotation as the c-boundary mechanism, as the control was designed to show.
- **The candidates span an order of magnitude** (0.018–0.23 fm), purely because the geometry is undetermined.

**3. The one result robust across the whole matrix.** At a nuclear contact (r = 2R_p):
- the proton's own depth is **shallow**: z_p = 0.011–0.135 for every candidate;
- **hydrogen's** depth is deep: z_H = r_e/(2R_p) = **1.675**.

This holds whichever geometry is chosen. It supports Harvey's correction in numbers: at nuclear contact the deep displacement is hydrogen's, not the proton's own. Any "flipped" light/occlusion law past z = 1 therefore belongs to hydrogen's ladder at nuclear scale.

## Stage-2 admissibility (criteria registered in PROMPT §4, applied now)

| pair | (a) inside the circulation | (b) consistent | (c) traced sizes | admissible |
|---|---|---|---|---|
| G1 + D1 | yes | aspect fine; size **assumed** | no (no size in canon) | no |
| G5 + D1 | yes | **K2 conflict** | yes (NSEQ16 registered) | no, pending a ruling on K2 |
| G6 + D1 | yes | **K1 and K2 conflicts** | **no** (0.06 fm untraced) | no |
| D3 | inside the tours; not tied to the poloidal circulation | — | yes | not a poloidal definition; held as reference |

**No pair is admissible.** Per PROMPT §4, the stage-1 result is the geometry conflict itself, which goes to Harvey for a ruling.

## Questions for Harvey (needed before stage 2)
1. **Which winding is the proton:** (2,3) trefoil, (4,5) cyclic quadruple helix, or 4 tours × 3 cross-section turns? "Four tours" in the ruling points away from (2,3), which makes 2 toroidal circuits.
2. **Does the canon aspect law R/a = √(q/p)** (mode-locked, from the Law V budget) govern the nucleon? If so, the registered braid and the engine sizes both violate it.
3. **What fixes the tube (poloidal) radius absolutely?** It might be R_p together with the aspect law, the node R_p/3, or something else.

## Other defects found (propose-only)
- Live engine H1: the envelope exceeds R_p by 8.5%, and the 5.28 / 0.06 fm constants are untraced. Release is not edited.

## Grades
- **Inventory and consistency:** G4, computed.
- **Ѻ_p:** G2, open; geometry undetermined.
- **Contact-depth asymmetry** (z_p ≪ 1 < z_H at contact): G4, computed, robust across all candidates.
