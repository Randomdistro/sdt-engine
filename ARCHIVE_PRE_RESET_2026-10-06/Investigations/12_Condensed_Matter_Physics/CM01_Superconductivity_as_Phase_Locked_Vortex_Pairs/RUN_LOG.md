# RUN_LOG — CM01 Superconductivity as Phase-Locked Vortex Pairs

> **Author:** J. C. Harvey, Melbourne. **Run date:** 2026-07-04.
> Append-only. Pre-commitments written BEFORE any tool code exists.

## Pre-Run Commitments — CM01

- Prompt completion target: **C** (prompt's expected landing)
- Physics class hoped: **CONVERGENCE** (structure), with the pairing-magnitude channel expected OPEN
- CALIBRATED budget: 0 in the P2 native pairing chain. T_c absolute value is expected to remain
  **OPEN** (not even CALIBRATED — no per-material coupling will be fitted).
- Engine namespaces: `measured` (hbar, h, k_B, e_charge, m_e, alpha, c), law_III narration
  (occlusion drag), law_VI (winding / knot exclusion), FD05 c_s narration, FD02 κ, EMC03 expulsion,
  **FLM14 ADJ-7 two-channel** (constraint propagates uncapped inside a gear-locked cluster — the
  native zero-dissipation mechanism, per Harvey's resumption order).
- **CM02 status note:** CM02's verdict is flagged DO-NOT-TRUST (τ hard-coded from measured σ). P1
  here therefore builds the normal state from scratch with τ never touching measured σ — the run
  doubles as the honest re-derivation CM02 owes.

### Phase thresholds (committed before run)

- **P1 (normal-state drag, the anti-CM02 chain):**
  ρ_Cu(300 K) from: ⟨u²⟩ = 3k_BT/(M ω_D²) (ion equipartition) → σ_occ = π⟨u²⟩ → ℓ = 1/(n_ion σ_occ)
  → carrier speed v_pack = ℏ(3π²n_e)^{1/3}/m_e (**wake-packing speed**: two W=1 knots cannot
  co-occupy one winding cell — Law VI knot exclusion, named premise; NOT a Fermi import — flagged
  STRUCTURAL-CONVERGENCE with the rival's v_F) → ρ = m_e v_pack/(n_e e² ℓ).
  Gates: ρ within **10×** of measured 1.68e-8 Ω·m (anchor: measured ρ_Cu); ℓ within **3×** of the
  measured 300 K mean free path 39 nm (anchor: measured MFP); linearity ρ(2T)/ρ(T) = 2.00 ± 0.05.
- **P2 (pairing channel):** compute the lattice-wave (deformation-well) branch honestly:
  F = αℏc/d², k_spring = Mω_D², E_pol = F²/(2k_spring), retardation seat r_seat = v_pack·(2π/ω_D),
  worst-case direct repulsion at seat E_rep = αℏc/r_seat.
  Gates: **E_pol > E_rep(r_seat)** (an attraction window exists) AND **ξ_seat/d > 10** (coherent
  span out-runs the defect scale). Committed expectation (Harvey directive, NP17 death knell): the
  deformation-well branch will NOT close a T_c magnitude — if E_pol comes out ~material-independent
  while measured T_c/θ_D spreads ≥10×, the branch is declared **DEAD as a T_c closure** and the
  binder pivots (ADJ) to the gear-lock channel (FLM14 constraint rigidity, NP17 seat template),
  with the coupling magnitude η = T_c/θ_D held **OPEN** (printed OBSERVED, never fitted).
- **P3 (zero drag + Meissner):**
  Zero drag = FLM14 rigidity: a defect kick is redistributed cluster-wide on the constraint channel
  in the same tick; dissipation requires breaking the lock (cost E_lock) — below T_c no drag channel.
  Quantitative gate: single-carrier drag suppression factor (d/ξ_seat)^{3/2} < 1e-3.
  Meissner/λ_L: zero-drag carriers + Ampère (classical EM, no gauge machinery) →
  λ_L = √(m_e/(μ₀ n_e e²)). Gates: λ_L(Al) within **2×** of 16 nm; λ_L(Nb) within **2×** of 39 nm
  (anchors: measured penetration depths).
- **P4 (flux quantum + isotope):**
  Φ₀ = h/(2e): the divisor is the **body count of the lock** (two W=1 vortices = one phase object of
  carrier mass 2m_e, handedness 2e). The numeric value is **IDENTITY once the carrier is the pair**
  — printed with the IDENTITY tag, NOT claimed as a prediction (anti-tautology firewall). The earned
  content is the divisor argument; exclusivity of 2 (why not 3) = OPEN, logged.
  Isotope: T_c ∝ lock ceiling ℏω_D(M), ω_D = √(k_spring/M)·(geometry fixed) → numeric exponent
  α_iso = −d ln T_c/d ln M. Gate: α_iso = −0.500 ± 0.005 (analytic check) vs measured anchor
  Hg α = 0.50 ± 0.03 (OBSERVED comparison).
- Forbidden retroactive changes: import a BCS gap into P2 then claim A; import Φ₀=h/2e as given;
  widen tolerances; plug T_c; IDENTITY-PASS on Φ₀ (it is *labelled* IDENTITY, never counted as a
  pass); local constant namespaces; any moment in magnetons.

### §G mirror (pre-run)

- Faith ledger: (a) wake-packing speed = Law VI knot exclusion (named; STRUCTURAL-CONVERGENCE with
  rival v_F — the number is derived from n_e, not borrowed); (b) FLM14 constraint channel (canon,
  ADJ-7); (c) lock ceiling = ℏω_D (channel cannot exchange above its cutoff — mechanical claim).
  All three named; none silent.
- Gate audit: every kill number above is a measured anchor (ρ_Cu, MFP, λ_L, Hg exponent). No rival
  axiom polices any gate.

## MEASURED-INPUT ledger (frozen)

| Material | n_e [1/m³] | n_ion [1/m³] | M [amu] | θ_D [K] | d_nn [Å] | anchors |
|---|---|---|---|---|---|---|
| Cu | 8.49e28 (1 e/atom) | 8.49e28 | 63.546 | 343 | 2.556 | ρ=1.68e-8 Ω·m, ℓ=39 nm |
| Al | 1.81e29 (3 e/atom) | 6.03e28 | 26.982 | 428 | 2.863 | λ_L=16 nm, T_c=1.20 K |
| Nb | 5.56e28 (1 e/atom) | 5.56e28 | 92.906 | 275 | 2.858 | λ_L=39 nm, T_c=9.25 K |
| Pb | — | 3.30e28 | 207.2 | 105 | 3.500 | T_c=7.19 K |
| Hg | — | — | 200.59 | 71.9 | — | isotope α=0.50±0.03 |

## Phase gate record (from real stdout, run 2026-07-04, `cm01_results.txt`)

- P1: mfp **64.2 nm** vs 39 nm anchor (1.65×, gate 3×) PASS · ρ_Cu **1.025e-8** vs 1.68e-8
  (1.64×, gate 10×) PASS · linearity 2.0000 PASS. **PASS-GATE. τ never saw measured σ.**
- P2: attraction window OPEN for Cu/Al/Nb/Pb (E_pol 0.12–0.18 eV ≫ E_rep 0.002–0.007 eV at seat);
  ξ_seat/d = 790–2380 (gate >10) PASS. **Death knell confirmed:** E_pol material-blind
  (0.12–0.18 eV) while measured η = T_c/θ_D spreads 24× (0.0028–0.0685) → deformation well
  **DEAD as a T_c closure**. ADJ-1 fired as committed.
- P3: drag suppression 4.47e-5 (gate <1e-3) PASS · λ_L(Al) **12.5 nm** vs 16 (1.28×) PASS ·
  λ_L(Nb) **22.5 nm** vs 39 (1.73×) PASS.
- P4: α_iso = **−0.5000** (gate ±0.005) PASS, anchor Hg 0.50±0.03 · Φ₀ printed **IDENTITY**
  (labelled, not passed); divisor-2 = body count of lock; 3-lock exclusivity OPEN.

### ADJ register

- **ADJ-1 — P2 PIVOT (2026-07-04, committed pre-run in thresholds above).**
  Trigger: E_pol ~material-blind vs 24× spread in measured η — the static deformation well cannot
  set T_c. Committed response (pivot table row 1 + Harvey directive): binder = gear-lock on the
  FLM14 constraint channel, seeded at the retardation seat (the seat and window survive; they are
  where the lock forms, not what sets its depth). What changed: the T_c-magnitude claim moved to
  OPEN (η printed OBSERVED, never fitted). What did NOT change: no gap imported, no tolerance
  moved, no coupling fitted. NP17 is the death knell precedent: SDT binding is seat-sharing geared
  down, not a static well.
