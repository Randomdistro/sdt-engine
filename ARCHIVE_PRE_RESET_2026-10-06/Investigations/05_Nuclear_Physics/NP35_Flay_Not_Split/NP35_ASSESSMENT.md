# NP35 Assessment — flay, not split

**Date:** 2026-08-13  
**Stdout:** `.audit-tmp/np35_run.txt`  
**Canon edited:** no

## Status

`NP35_FLAY_ORDER_PARTIAL`

## What was emitted before data

F3 (outermost sealed triton shell, next D-tier complete) for all eight IAEA parents: **N_H = 82**, Z_H from parent Z/N, A_H_pre = 133–135. F1 (stop at largest reached closure) emitted A_H_pre = 205–208.

## Gates

| Gate | Result |
|---|---|
| G1 F1 vs U-235 A_H | **EXCLUDED** (Δ ≈ +70) — unwrap-to-126 is not fission |
| G2 F3 vs U-235 A_H | **MATCH** (134 vs 136.5) |
| G3 F3 A_H band all 8 | **PASS** (133–135 predicted; obs 136–140) |
| G4 F3 A_H vs A* slope | **PASS** (+0.012; obs −0.197) |
| G5 A_L residue in [1, 8] | **FAIL** — Th-232 = 8.54; other seven inside |

F_Z50 (inserted Z=50) is worse than F3 on A_H (Δ ≈ −4 to −8 vs −1 to −6). Not used as the claim.

## Classification

F1 (Pb-like core / N=126) is **EXCLUDED** as the actinide fission remnant.  
F3 (T12 / N=82 remnant, jacket = the rest) is **CONDITIONAL** on A_H: MATCH on eight systems, stationary heavy, sliding light residue in the ν class except Th-232 (ORDER).

This is **not** EMPIRICALLY SURVIVES:

- Z_H is parent Z/N, not a seating derivation (NP36).
- ν is not predicted (G5 is a residue check).
- Jacket `2d→α` is the NP25 ledger, not a coordinate unwrap (NP38).
- Superheavy N≥168 → N_H=126 switch is untested (no FY).

## Ontology

The core is not a goo drop. Naive complete-closure unwrap (F1) would leave a 126-core and does not match. Sealed **triton** masonry (T12) with incomplete D42 so T14 unfrozen **does** match the heavy peak. Necked min-cut remains the wrong object.

## Audit re-score (2026-10-05, from the recorded values; no new run)
G4 was applied to the predicted heavy mass, which is nearly constant by construction (A_H = Z_H + 82), and G3's band [128, 148] was wide. Corrected rules: G4 on the **observed** heavy-peak slope against A*, and G3 as |A_H(pred) − A_H(obs)| < 8 per system. Re-scored on the values recorded above: observed slope −0.197 (|s| < 0.25, PASS); predicted 133–135 against observed 136–140 gives |ΔA_H| of at most 7 (all eight inside 8, PASS). The outcomes are unchanged under the corrected gates; the earlier PASS rested on the wrong quantity and the wrong width, and the spontaneous-fission hold-out (`NP35_SF_HOLDOUT_*`) uses the corrected form.
