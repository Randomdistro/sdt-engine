# RUN_LOG — PM05 (Magnetic Reconnection and Solar Flares from Wake Topology)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Written BEFORE any code.

## Pre-Run Commitments — PM05

- Prompt completion target: **D** (committed up front: the load-bearing phases P2-snap and P3-fast
  need a 3-D lattice wake-topology solver that DOES NOT EXIST. No sim will be faked; the
  analytically-earnable parts are done and the rest is OPEN with the missing tool named.)
- Physics class hoped: CONVERGENCE for stored energy + slow branch; OPEN (with named native
  candidate) for the fast branch; OBSERVED-inputs order checks for P4.
- CALIBRATED budget: 0. No resistive-Ohm postulate (η = FD02, via PM07's measured slip law);
  no magnetons; energies native (½ρ_a w²), SI map final lines only.
- Two-channel framework (FLM14 RUN_LOG ADJ-7, read before this run): pulse channel at c vs geared
  CONSTRAINT channel (uncapped rigidity in contact-locked structures). Committed use: the
  constraint channel is the NAMED NATIVE CANDIDATE for the fast branch (topology snap = constraint-
  release event, rate geometry-fixed, weakly S-dependent) — CANDIDATE ONLY, not claimed derived.

### Phase thresholds (committed before run)

| Phase | Gate | Threshold |
|---|---|---|
| P1 | stored throughput | U = ½ρ_a∫\|w\|² of two opposed bundles computed on a grid; native form ½ρ_a w² (the B²/2µ₀ conversion is ORPHAN-1/HG-1-adjacent, disclosed); decomposition U = U_self1+U_self2+U_int with U_int < 0 for anti-parallel approach |
| P2 | ledger | pairwise-annihilation bookkeeping: quanta ledger exact by construction (**pre-flagged: this is the trivial arithmetic the prompt's anti-tautology paragraph names — NOT claimed as the result**); released ΔU computed numerically; **the SNAP itself (when/whether topology jumps) = OPEN — missing tool: 3-D lattice wake-topology solver (ROOT-SIM class)** |
| P3 | rates | slow branch: v_in/v_A = S^(−1/2) assembled from continuity + PM07's measured slip ∝ η — **pre-classed LINGUISTIC/CONVERGENCE (textbook chain, renamed nouns — said so)**; numeric table must show the fast-reconnection gap (orders too slow at coronal S) honestly; fast branch: **OPEN**, ADJ-7 constraint channel = named candidate (predicts weakly-S-dependent plateau; falsifiable vs MHD) |
| P4 | flare/CME orders | with OBSERVED inputs flagged (B, L, n): flare U within 10³¹–10³² erg; v_A within 10²–10³ km/s |
| T4 | ∇·B through annihilation | structural: w stays a superposition of curls under quanta removal ⇒ ∇·B ≡ 0 (PM01 P2c identity; pre-flagged, consistency only) |

### Forbidden retroactive changes
Fake any reconnection dynamics; import Sweet–Parker then claim native; insert anomalous η; claim
the ADJ-7 candidate as derived; retro-tune B/L/n to hit 10³¹ erg (values fixed here: B ∈ {0.02,
0.03} T, L ∈ {3e7, 5e7} m, n ∈ {1e15, 1e16} m⁻³, before computing).

## Run record (filled after execution)
- See `pm05_results.txt`, `PM05_VERDICT.md`.

## ADJ-1 (2026-07-05, disclosed): P4 CME classification string corrected (first build printed
"order-correct" for a band that entirely misses the committed 1e2–1e3 km/s gate). Numbers unchanged.
## Run record: build clean, exit 0. P1/P2 as committed; P3 slow branch table + gap stated; P4 flare
energy PASS (4.3e31–4.5e32 erg overlaps), P4 CME speed FAIL (v_A 4.4e3–2.1e4 km/s, above gate).
