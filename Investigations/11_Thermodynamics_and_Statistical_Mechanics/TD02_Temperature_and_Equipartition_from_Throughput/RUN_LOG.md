# RUN_LOG — TD02 Temperature and Equipartition from Throughput

**Executor:** J. C. Harvey, Melbourne · 2026-07-03
**Committed BEFORE first compile/run. No threshold below may be widened after a number is seen.**

## Pre-Run Commitments — TD02

- Prompt completion target: **B** (honest expectation; A only if every phase clears)
- Physics class hoped: NATIVE — but pre-registered suspicion: the counting route is
  Boltzmann's 1877 most-probable-distribution combinatorics; if nothing lattice-specific
  (ℓ_P, occlusion geometry, FLM08 coordination) does work in the chain, the honest class
  is **CONVERGENCE** regardless of numerical passes. This will be judged after the run
  against the pre-registered question: *which step would break if the substrate were not
  an SDT relay lattice?*
- CALIBRATED budget: 0. Only whitelisted input: `measured::k_B`. Energies reported in
  units of the relay quantum ε (symbolic); kelvin only via k_B × pure number.
- Engine namespaces used: `sdt::laws::measured::k_B` only. TD01 counting W(E,N)=C(E+N−1,N−1)
  re-implemented locally (combinatorial function, not a constant).

## Phase thresholds (committed)

- **P1 (two-definition concordance):**
  - β_budget = ln(1+N/E) (Lagrange multiplier from the throughput budget) vs
    β_count = ∂lnW/∂E (central difference of TD01 counting): relative gap < 1e-3
    for N=500, E/N ∈ [10, 2000].
  - T_kin ≡ ⟨ε_dis⟩/k_B per cell vs T_ent = (∂S/∂E)⁻¹: agreement < 1e-3 required only in
    the classical regime ⟨j⟩ = E/N ≥ 1000. The discrete-regime departure is PREDICTED
    (freeze-out of the quantised cell) and will be reported as a curve, not absorbed.
- **P2 (equipartition, M quadratic DoFs, pair-rotation mixing):**
  - k_BT ≡ 2E_tot/M (entropic definition for quadratic DoFs). Success: RMS per-DoF
    deviation of time-averaged ⟨e_i⟩ from ½k_BT < 1%; max per-DoF deviation < 5σ_stat
    (σ_stat estimated from the run and printed); result independent of two grossly
    different initial splits (all-energy-in-10%-of-DoFs vs uniform): the two final
    per-DoF mean vectors agree in distribution (their global means within 0.5%).
  - Velocity marginal: excess kurtosis of v_i within ±0.05 of Gaussian (MB emerges).
- **P3 (Boltzmann factor from NATIVE counting — the firewalled core):**
  - Route (a) analytic Lagrange max of ln[N!/Πn_j!] at fixed E → n_j ∝ e^(−βj), β from budget.
  - Route (b) exact enumeration marginal p_j = W(E−j,N−1)/W(E,N) (whole-lattice uniform
    count, computed EXACTLY — no Taylor expansion of any reservoir entropy).
  - Route (c) dynamics: symmetric one-quantum relay exchange chain, occupancy histogram.
  - Success: ln p_j vs j linear with R² > 0.999 on j ∈ [0, j_max] where p_j > 1e-5;
    |slope + β_budget|/β_budget < 1%; sim histogram matches exact marginal (max abs
    deviation < 3σ_multinomial).
  - **FIREWALL:** no S_res(E−ε) expansion, no pre-defined T, no partition function object.
    Route (b) counts the complement exactly under the uniform microcanonical measure of
    TD01 — it does not presuppose a Boltzmann-weighted bath. If someone judges exact
    complement-counting to be "the reservoir", the fallback class is C; this judgement
    call is flagged openly in the VERDICT.
- **P4 (delete test):** every printed physical result must be k_B × (pure number) or
  ε × (pure number). No h, no Z, no ensemble object in the chain. c_v per 3-DoF particle
  = 3/2 k_B recovered from P2 (flagged: near-definitional given equipartition).

## Decision rules

- Any P1/P3 gate miss → report as fired, apply pivot table (finer lattice first), never widen.
- Physics class decided by the pre-registered question above, not by pass counts.
- Forbidden: reservoir expansion graded A; plugging β; RETRO-PASS; hiding the T_kin/T_ent
  discrete-regime departure.

## Run record

- [x] compile (MSVC /std:c++20 /O2) — clean
- [x] RUN 1: exit 1 — P1 gate FIRED: gap constant 2.00e-3 = 1/N at N=500 (all E/N).
      Traced: central-difference dS/dE finite-size error is exactly 1/N; premise error was
      committing 1e-3 at N=500. **ADJ-1 (allowed: larger lattice, threshold unchanged):**
      added explicit 1/N scaling table (N=250..8000, gap*N=1.000) and gated at N=8000.
- [x] RUN 2: exit 0 — all gates pass → results.txt (real stdout)
- [x] verdict: TD02_VERDICT.md — Prompt A · Physics CONVERGENCE · firewall NOT FIRED
