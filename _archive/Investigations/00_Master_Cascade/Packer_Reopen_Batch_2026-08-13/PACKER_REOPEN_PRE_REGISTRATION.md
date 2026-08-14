# Packer-reopen batch — pre-registration

**Date:** 2026-08-13  
**Canon edits:** none  
**New input:** live NSEQ05 `packNucleus` (`dnn = 1.45` fm, `coulSpread = 0`) as in
`Release/HTML_SDT_Website/js/pack-nucleus.js`. Not the sequencer slider (`1.45×R_p`).
**dnn is frozen.** No retune to binding, RMS, or yields.

This batch pays the missed coupling: NP23 / NP17-heavy / NSEQ13–14 / FLM14-P2 / NP12e / NP36
were not rebuilt against the interleaved seat graph. It also reopens closed items whose
geometry source is now obsolete (NP12e STATED ATOMICUS tables; NP17 α PENDING on imported
trefoil maps; NSEQ14 lengths `{R_p, r_e}` rather than packed contacts).

NSEQ05–07, 09 (locations), 11 seating **not** reopened — they *are* the new data.
NP35 F1 exclusion **not** reopened — no new FY. NP37/NP38 **PENDING_DATA** (Bernas; joint
Y(A,Z,TKE,ν) absent).

## Shared instrument

Python port `Investigations/05_Nuclear_Physics/pack_nucleus.py`, validated against node
`packNucleus` on He-4 / C-12 / Fe-56 before any claim tool runs. Grammar
`n_d = 3Z−A−2`, `n_t = A−2Z`. Z≥2 only.

## Investigations and gates (frozen)

### NP39 — monoisotopy vs pack staircase (new)

Frozen NP23 sets (C1, no decay). No IAEA, no AME, no WHICH-A interpolation.

| Gate | Claim | MATCH | FAIL |
|---|---|---|---|
| G1 | Light soles F-19, Na-23, Al-27, P-31 end at T8 fill = 1 | 4/4 | any miss |
| G2 | Width discriminator: no odd-Z *double* has a stable A with T8 fill = 1 | 0/9 doubles have a T8×1 stable | any T8×1 double |
| G3 | All 25 odd-Z singles end mid-T (0 < fill < cap) | 25/25 | any T-complete or D-only stop |

G2 is the non-identity test. G1/G3 may be CONVERGENCE with even T-caps. No native WHICH-A.

### NP12f — packer proton point-RMS (reopen NP12e)

Same Map as NP12e: `R_{p,RMS}² = (1/Z) Σ |r_i − r̄_p|²`. Centres from `packNucleus`, not
STATED ATOMICUS tables. **IAEA sealed** (file must not be opened). Physical `ρ_q` still
not claimed. Frozen set: ⁴He, ⁹Be, ¹²C, ¹⁶O, ⁵⁶Fe, ⁴⁸Ca.

| Gate | MATCH |
|---|---|
| C1 | instrument: 4 tetra vertices of a regular tetra share one RMS |
| C2 | packed n_p = Z and n = A for the frozen set |
| C3 | R_{p,RMS} published (COMPUTED) |
| C4 | physical charge RMS remains UNDERDETERMINED |
| C5 | IAEA path not read |

Compare NP12e stated-table RMS as a *difference report*, not a gate.

### NP17b — packed geometry binding (reopen NP17 α PENDING)

Energy scale `αℏc = 1.4400` MeV·fm (NP17 record). No B_d/B_α imported into candidates.

| Gate | Claim | MATCH | FAIL |
|---|---|---|---|
| G1 | Li-6 packed deuteron `E = 3 αℏc / D_pn` vs 2.224 MeV | rel < 0.20 | rel ≥ 0.20 |
| G2 | He-4 electrostatic (p–p `αℏc/r_pp` plus NP17 packed pairwise report) vs 28.296 | rel < 0.20 | rel ≥ 0.20 |

G2 expected FAIL (NP17 already under-bound at 2 R_p). Do not retune dnn.

### NSEQ15 — packed contact energy (reopen NSEQ14)

Hold-out: NSEQ09 SEAL medD = **4.242 MeV**. Lengths = packed contact distances on He-4,
C-12, O-16, Fe-56 (mean p–n contact, mean all contacts). Candidates: `αℏc/d`, Law-III
`F(R_p,R_p)×d`. No B_d/B_t.

MATCH: rel < 0.15. Else UNDERDETERMINED (ORDER if rel < 10).

### NP36 — jacket Z from seating

Hold-out: NP35 published obs A_H centroids (eight systems) — **frozen**, not re-fit.
F3 N_H = 82 frozen. ν not predicted.

| Rule | Z_H | A_H |
|---|---|---|
| R_ratio | `round(82 · Z/N)` | NP35 control (not seating) |
| R_T12_actual | protons + neutrons through T12 complete | Z=82, N=112, A=194 (parent-independent) |
| R_T12_label | NSEQ N-label 82 with Z of that prefix | Z=82, N_label=82, A=164 |

MATCH |ΔA_H| < 8; ORDER 8–20; EXCLUDED ≥ 20. Mixed-shell (N from T12, Z from T10) is
F_Z50 already scored — control only, not a new seating rule.

### FLM14-P2 packer seats (geometry precondition only)

P2 Lamb/dwell remains DEFER. This loop only tests whether packed proton seats have
non-uniform closed-tour hop lengths (the missing structured geometry).

| Gate | MATCH |
|---|---|
| V1 | regular 4-gon hop CV = 0 |
| G1 | C-12, O-16, Ca-48, Fe-56 proton nearest-neighbour closed tours have CV > 0.02 (He-4 has Z=2 ⇒ hop CV identically 0; reported, not gated) |
| G2 | Lamb table not opened |

Not EMPIRICALLY SURVIVES. Status `P2_GEOMETRY_PRECONDITION` / still DEFER on dwell.

## Forbidden

- Opening IAEA radii (NP12f)
- Fitting dnn, κ, Z_H, or occupancy to a hold-out
- Binding leaks (B_d, B_t, B_α) as derivation
- Labelling EMPIRICALLY SURVIVES on any item in this batch
- Re-scoring NSEQ09 locations or NP35 F1
