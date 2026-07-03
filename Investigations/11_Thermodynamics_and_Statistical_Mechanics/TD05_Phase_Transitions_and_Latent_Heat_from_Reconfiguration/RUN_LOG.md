# RUN_LOG — TD05 Phase Transitions and Latent Heat from Reconfiguration

**Executor:** J. C. Harvey, Melbourne · 2026-07-03
**Committed BEFORE first compile/run. No threshold below may be widened after a number is seen.**

## Pre-Run Commitments — TD05

- Prompt completion target: **C** (prompt's own expected landing)
- Physics class hoped: the falsifiable core is T1 — does a packing of wake-bound hard vortices
  produce a first-order transition with NO Landau/order-parameter field in the dynamics?
  Pre-registered: the pair-potential MD model is generic condensed matter; "wake binding" is the
  SDT narration of the attractive well → expected class **CONVERGENCE** even on a clean pass.
- CALIBRATED budget: 1 declared measured proxy — the pair potential (LJ form, and for the
  argon mapping the OBSERVED LJ parameters ε/k_B = 119.8 K, σ = 3.405 Å). No other fits.
- Model: 3D MD, N = 108 (3×3×3 FCC), ρ* = 1.0 fixed (PBC), LJ shifted at r_cut = 2.5σ,
  velocity Verlet dt = 0.002, velocity-rescale thermostat during equilibration only
  (2,000 steps), NVE production (3,000 steps) per temperature step. Heating T* = 0.40 → 2.16
  then cooling back, ΔT* = 0.08. **The order parameter S(k₁₁₁) is a diagnostic only — it never
  enters the dynamics** (that is the no-Landau-field discipline).

## Phase thresholds (committed)

- **P1 (sharp transition + hysteresis):**
  - Sharpness: max single-heating-step ΔU_pot > 0.4 ε/particle AND > 4× the median
    off-transition step ΔU; S(k₁₁₁)/N collapses from > 0.3 to < 0.1 across ≤ 2 steps.
  - Hysteresis (first-order character): max_T |U_heat(T) − U_cool(T)| > 5× median step noise;
    cooling branch may recrystallise OR glass-arrest — either is hysteresis; which one occurs
    is reported (prompt Q2 connects glass arrest to FLM09).
- **P2 (latent-heat ledger):**
  - L_sim = ΔU across the jump. Bond ledger: Δ(first-shell pairs, r < 1.35σ)/N × |ū_bond|
    (ū_bond measured in the solid branch). Gate: L_sim within **factor 1.5** of the ledger.
  - DISCLOSED pre-run: "L = T_mΔS self-consistent" (prompt T2) is an identity when ΔS is
    calorimetric (ΔS := L/T_m); an independent ΔS is not measurable in this MD. NOT TESTED —
    declared, not laundered. Flat-T absorption is protocol-set (T is controlled), also disclosed.
- **P3 (argon order-of-magnitude, OBSERVED mapping):**
  - L_melt_pred within factor 3 of argon 1.18 kJ/mol (= 1.185 ε); cohesive-energy ledger
    |U(T*=0.4)|/N within factor 3 of argon L_vap = 6.5 kJ/mol (= 6.55 ε); ordering
    L_vap ≫ L_melt reproduced. T*_jump × 119.8 K reported vs argon T_m = 83.8 K with the
    fixed-density superheating caveat stated (NOT a prediction of T_m; ρ = 1.0 ≠ coexistence).
- **P4 (Clausius–Clapeyron): DEFERRED — declared now.** A slope test needs pressure-controlled
  coexistence (NPT/interface or free-energy route), out of this tool's budget. OPEN with the
  §D questions in the verdict. No number will be produced.

## Decision rules

- No jump found by T* = 2.16 → P1 FAIL honest (pivot: finer ΔT near expected T_m allowed;
  never manufacture a jump). Continuous S(k) fall with no ΔU jump → report as fired T1.
- Ledger off > 1.5× → trace (second-shell share of cohesion) before any classification.
- Physics class: which step would break on a non-SDT substrate?

## Run record

- [x] compile (MSVC /std:c++20 /O2) — clean
- [x] RUN 1: exit 1 — melting found at T* ≈ 1.96 (ΔU = 0.511 ε, hysteresis 1.013 ε, cooling
      branch glass-arrests). Two gates fired: (a) S-collapse — traced to a MIS-IMPLEMENTED
      gate (code checked 1 step; commitment above says ≤ 2 steps; transition straddles two).
      (b) P2 ledger factor 6.03 — genuine fired falsifier.
- [x] ADJ-1: implemented the committed ≤2-step S-collapse window as written (no threshold
      change); added post-fire TRACE decomposition to output (diagnostics only, P2 gate stands).
- [x] RUN 2 (identical seed → identical trajectory): exit 1 — P1 PASS, **P2 FAIL kept** (count
      channel 13% vs re-pricing 87% at fixed density), P3 PASS, P4 DEFERRED.
- [x] verdict: TD05_VERDICT.md — Prompt C · Physics CONVERGENCE (H2 count-ledger KILLED at
      fixed density; recovery route = coexistence/NPT, owed) · new local root TD05-LEDGER
