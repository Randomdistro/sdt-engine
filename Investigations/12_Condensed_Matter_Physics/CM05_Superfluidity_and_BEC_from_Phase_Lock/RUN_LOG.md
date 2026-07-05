# RUN_LOG — CM05 Superfluidity and BEC from Phase Lock

> **Author:** J. C. Harvey, Melbourne. **Run date:** 2026-07-04.
> Append-only. Pre-commitments written BEFORE any tool code exists.

## Pre-Run Commitments — CM05

- Prompt completion target: **C**
- Physics class hoped: **CONVERGENCE**; T_λ absolute magnitude expected to land OPEN (declared)
- CALIBRATED budget: 0 in the κ chain; **no** T_λ or v_c coefficient will be fitted at all
- Engine namespaces: `measured` (h, hbar, k_B), FD02 κ (Law VI winding forces h/m, no free
  integer), CM01 lock mechanism + FLM14 ADJ-7 constraint channel (zero-dissipation machinery),
  CM04 thermal disorder. **No BEC/Gross–Pitaevskii ψ anywhere** — the condensate is a gear-locked
  wake cluster, mechanically.

### Phase thresholds (committed)

- **P1 (transition existence + scale):** two native crossing criteria, BOTH committed now,
  numbers reported as they fall, NO averaging between them (a geometric mean would be fishing):
  - Route 1 (wake-crossover): lock when wake wavelength λ_w = h/(m v_rms), v_rms = √(3k_BT/m),
    equals the spacing n^{−1/3} → T₁ = h²n^{2/3}/(3 m k_B).
  - Route 2 (lock-energy, CM01 form): k_B T₂ = ℏ²/(2 m d²), d = n^{−1/3}.
  Gate (prompt): within ~2× of T_λ = 2.17 K. Committed expectation: BOTH routes miss the 2× gate
  from opposite sides (bracketing — and **bracketing is not predicting**, HUNTER §C3); the
  existence + kelvin-scale claim is the earnable piece; the magnitude goes OPEN with the missing
  closure named (collective seating statistics of indistinguishable wakes — unbuilt natively).
- **P2 (η → 0):** mechanism = FLM14 rigidity (same as CM01 P3: kick redistributed cluster-wide on
  the constraint channel; dissipation requires lock-breaking). Demonstration: mean-field lock
  fraction f(T) (self-consistent alignment balance, classical) → η(T)/η_n = 1 − f(T) collapses
  sharply below the transition; gate: f(0.5·T_lock) > 0.9 and f(T > T_lock) = 0.
- **P3 (κ, the core gate):** κ = h/m_He4 within 0.1% of measured 9.97e-8 m²/s, divisor exactly 1
  (single wake; no free integer — Law VI). Cross-check (OBSERVED comparison): He-3 superfluid
  circulation is measured at h/(2m₃) — the CM01/CM05 body-count rule (divisor = number of locked
  bodies) must land BOTH divisors (1 for He-4, 2 for He-3) with no adjustment. He-3's *need* to
  pair is narrated (odd constituent count → unpaired half-wake) and labelled ARGUED, not derived.
- **P4 (v_c):** native upper bound v_c ≤ c_s(He) = 238 m/s (compression ceiling); the practical
  roton-set value uses MEASURED-INPUT roton parameters (Δ/k_B = 8.65 K, k₀ = 1.92e10 m⁻¹) →
  v_c = Δ/(ℏk₀) — labelled **OBSERVED-reprocessing, no SDT credit claimed** (the roton spectrum
  is not derived here; CM04 Q1 owns the short-k bend). Gate: the reprocessed number within 2× of
  ~60 m/s, stated as a consistency check only.
- Forbidden: importing ψ as mechanism; averaging the two P1 routes; retro-widening the 2× gate;
  claiming P4 as a prediction; quoting circulation in any borrowed unit.

### §G mirror (pre-run)

- Faith ledger: (a) Law VI winding → κ (earned, FD02); (b) FLM14 constraint channel (canon);
  (c) equipartition v_rms for a liquid (coarse — named risk on Route 1). No rival axiom in gates;
  anchors are measured T_λ, κ, v_c, He-3 circulation.
- Gatekeeper check: the temptation to import Bose occupation statistics (ζ(3/2)) to rescue P1 is
  REFUSED in advance — that is the rival's counting until SDT earns indistinguishable-wake
  seating natively. Its absence is the named OPEN, not a licence to borrow.

## MEASURED-INPUT ledger (frozen)

- He-4: m = 4.002602 u; liquid density at T_λ: 146.2 kg/m³ → n = 2.199e28 m⁻³;
  T_λ = 2.17 K (anchor); κ_meas = 9.97e-8 m²/s (Vinen); c_s(liquid) = 238 m/s.
- He-3: m = 3.016029 u; measured superfluid circulation quantum h/(2m₃) (Avenel–Varoquaux) —
  OBSERVED comparison only.
- Roton: Δ/k_B = 8.65 K, k₀ = 1.92e10 m⁻¹ (neutron data) — MEASURED-INPUT for P4 reprocessing.

## Phase gate record (from real stdout, run 2026-07-04, `cm05_results.txt`)

- P1: Route 1 T₁ = **12.52 K (5.77×) FAIL** · Route 2 T₂ = **0.476 K (0.22×) FAIL** (gate 2×).
  Bracket confirmed exactly as pre-committed; **no averaging performed** (would be fishing).
  Kelvin-scale existence earned; magnitude **OPEN** — missing closure: native seating statistics.
- P2: f(0.5 T_lock) = 0.9575 PASS · f(T > T_lock) = 0.0000 PASS. Sharp collapse demonstrated;
  the unlocked fraction is the only viscous channel (FLM14 rigidity).
- P3: **κ(He-4) = 9.9693e-8 vs 9.97e-8 → 0.007% PASS** (gate 0.1%), divisor 1, no free integer.
  He-3 OBSERVED comparison: measured circulation = h/2m₃ — body-count rule lands divisor 2 with
  zero adjustment. He-3 pairing necessity labelled ARGUED.
- P4: v_c(roton, reprocessed) = 59.0 m/s — consistent; **no SDT credit claimed** (labelled
  OBSERVED-reprocessing as committed); native ceiling 238 m/s stands as bound only.

### ADJ register

(none — P1's committed double-FAIL is a gate outcome, not a pivot; the pivot-table row "no
transition" did not fire because the transition exists at kelvin scale on both routes)
