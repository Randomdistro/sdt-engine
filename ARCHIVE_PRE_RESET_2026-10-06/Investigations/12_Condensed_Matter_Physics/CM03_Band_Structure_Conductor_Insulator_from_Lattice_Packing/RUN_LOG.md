# RUN_LOG — CM03 Band Structure / Conductor–Insulator from Lattice Packing

> **Author:** J. C. Harvey, Melbourne. **Run date:** 2026-07-04.
> Append-only. Pre-commitments written BEFORE any tool code exists.

## Pre-Run Commitments — CM03

- Prompt completion target: **C** (prompt's expected landing: ordering native, one O(1) factor)
- Physics class hoped: **CONVERGENCE**
- CALIBRATED budget: **1** — one O(1) geometric factor `f` in E_g = f·ℏ²/(m_e d²), the SAME f for
  all solids, chosen ONCE as the minimax factor over the committed C/Si/Ge set (declared here,
  before the tool exists). No Bloch parameter, no k-space dispersion, no per-solid refit.
- Engine namespaces: `measured` (hbar, m_e), law_III narration (occlusion blockade), law_VI /
  PPT06 (traction grip), FD02 wake wavelength λ_w = h/(m_e v) — the confinement chain is the SAME
  wake-packing door as CM01 P1 (named premise, one door for the whole cluster).

### The pre-committed decision tree (P1 — written before the element table is scored)

1. **Grip saturation:** U = z_coord − n_bond (coordination minus directional valence bonds).
   U > 0 → open relay channels → **METAL**.
2. **Network dimensionality:** if U = 0 and the covalent network is 0-D (discrete molecules,
   vdW-relayed) → no bonded relay path at all between units → **INSULATOR** (vdW blockade).
3. **Gap scale:** if U = 0 and the network is 2-D/3-D: a vortex freed into a channel of width d
   must wind at wake wavelength ≤ (2π)d → throughput cost E_g = f·ℏ²/(m_e d²) [FD02 wake
   confinement; same door as CM01 v_pack]. E_g ≤ 2.0 eV → **SEMICONDUCTOR**, else **INSULATOR**
   (the 2.0 eV line is the standard usage convention, declared not derived).

### Phase thresholds (committed)

- **P1:** 9 elements — Cu, Ag, Al (metals); Si, Ge, Sn-grey (semiconductors); C-diamond, S,
  P-black (insulator / insulator / semiconductor). Gate: **0 misclassifications** (kill: ≥2).
  Anchors: observed conduction classes.
- **P2:** ordering E_g(C) > E_g(Si) > E_g(Ge) native (f-independent, pure 1/d²); magnitudes with
  the single minimax f within **2×** of measured 5.47 / 1.12 / 0.66 eV. Committed honesty
  exhibits (outside the gate, printed): Sn-grey and P-black predicted magnitudes vs measured
  (~0.08, 0.33 eV) — expected misses, reported as they fall.
- **P3:** mass-action carrier balance (generation exp(−E_g/k_BT) vs recombination ∝ n²) →
  n ∝ exp(−E_g/2k_BT) [the ½ DERIVED from pair-creation kinetics, not assumed]; simulated slope
  of ln ρ vs 1/T recovers E_g/2k_B within 1% (internal consistency); dρ/dT < 0 for Si/Ge.
- **P4 (stretch):** donor = one substitutional defect = one opened channel → carrier count =
  dopant count (linear σ vs N_d); n/p sign narration (freed wake vs mobile vacancy). Qualitative.
- Forbidden: Bloch/k-space import; per-solid f; tolerance widening; hand-assigned classes.

### §G mirror (pre-run)

- Faith ledger: (a) the wake-confinement door (same named premise as CM01/CM04 — Law VI/FD02);
  (b) the 2.0 eV semiconductor/insulator line is a *convention*, named as such (it can only
  misclassify C vs Si-family, and only if E_g lands near it); (c) bond counts/coordination are
  measured crystallography. No rival axiom in any gate; anchors are measured classes and gaps.

## MEASURED-INPUT ledger (frozen)

| Element | structure | z | n_bond | net-D | d_nn [Å] | class obs | E_g obs [eV] |
|---|---|---|---|---|---|---|---|
| Cu | FCC | 12 | 1 | 3 | 2.556 | metal | — |
| Ag | FCC | 12 | 1 | 3 | 2.889 | metal | — |
| Al | FCC | 12 | 3 | 3 | 2.863 | metal | — |
| Si | diamond | 4 | 4 | 3 | 2.352 | semi | 1.12 |
| Ge | diamond | 4 | 4 | 3 | 2.450 | semi | 0.66 |
| C | diamond | 4 | 4 | 3 | 1.545 | insulator | 5.47 |
| Sn-grey | diamond | 4 | 4 | 3 | 2.810 | semi (zero-gap) | ~0.08 |
| S | S8 molecular | 2 | 2 | 0 | 2.055 | insulator | ~2.6–3.8 |
| P-black | layered | 3 | 3 | 2 | 2.224 | semi | 0.33 |

## Phase gate record (from real stdout, run 2026-07-04, `cm03_results.txt`)

- P1: **0 misclassifications of 9** (gate 0) — PASS-GATE. Tree applied blind, no hand assignment.
- P2: f = 0.9439 CALIBRATED(1), minimax as committed. Si 1.16× · Ge 1.82× · C 1.82× (gate 2×)
  all PASS; ordering C>Si>Ge PASS (f-independent). Exhibits (outside gate, printed honestly):
  Sn-grey **11.4× miss**, P-black **4.4× miss** — the 1/d² scale does NOT hold near the
  zero-gap / layered edge of the family. Seven questions in VERDICT.
- P3: slope recovery 0.00% (internal-consistency of the FORM — labelled COMPUTED-internal, not a
  prediction); dρ/dT < 0 PASS. The earned piece is the DERIVED ½ (pair-creation kinetics).
- P4: qualitative narration only, as committed (no numeric gate).

### ADJ register

(none — no pivots; both P2 exhibits were declared expected misses pre-run)
