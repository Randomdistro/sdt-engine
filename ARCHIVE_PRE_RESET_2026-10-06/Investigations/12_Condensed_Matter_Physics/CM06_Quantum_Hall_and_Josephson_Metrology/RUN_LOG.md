# RUN_LOG — CM06 Quantum Hall and Josephson Metrology

> **Author:** J. C. Harvey, Melbourne. **Run date:** 2026-07-04.
> Append-only. Pre-commitments written BEFORE any tool code exists.

## Pre-Run Commitments — CM06

- Prompt completion target: **C/D** (P4 expected DEFER — CM02 upstream is DO-NOT-TRUST)
- Physics class hoped: honest mixed ledger — **IDENTITY** (the constants) + **CONVERGENCE**
  (per-channel count, conditional on the named h-cell premise) + **COMPUTED-toy** (robustness)
- CALIBRATED budget: 0
- Engine namespaces: `measured` (h, e_charge), law_VI (winding/topology), law_III (occlusion
  confinement), EMC03 (handedness), CM01 (the pair count for the Josephson 2)

### The identity firewall (the prompt's own hard rule, restated as commitment)

R_K = h/e², K_J = 2e/h, Φ₀ = h/2e are **DEFINITIONAL once charge quantisation is granted** —
h and e are SI-exact. Printing them "to <0.1%" can NEVER be a pass: they will be printed **once,
tagged IDENTITY, and counted as zero evidence**. The earnable content is structural only:
(a) WHY the per-channel throughput is e²/h; (b) WHY plateaus sit at integers and stay there
under disorder; (c) WHY the Josephson divisor is 2. No Chern number, no gauge field, no
topological-band machinery anywhere.

### Phase thresholds (committed)

- **P1 (edge channels):** narration + count: in a strong handedness field the drifting W=1
  vortex's closed drift orbits occlude in the bulk; only boundary-intercepted orbits relay
  forward (EMC03 handedness fixes one-way sense). Channel number ν = an integer COUNT of
  boundary relay lines. Gate: the toy below produces integer ν only (no fractional occupancy).
- **P2 (per-channel e²/h + robustness toy):** chain (named): a 1-D relay line carries one
  carrier configuration per winding cell (Law VI — the SAME single door as CM04/CM01/CM03);
  cell rate under throughput imbalance Δμ = Δμ/h; current per channel = e·Δμ/h ⇒ G = e²/h.
  Status: **CONVERGENCE conditional on the h-cell premise (ROOT-A)** — NOT native-earned, NOT
  identity-smuggled; grade capped C by the prompt's own rule.
  Robustness toy (COMPUTED-toy, no measured claim): W×L grid, deterministic index-derived
  defects, density p swept over ≥3 orders (1e-4 → 1e-1); edge channel = monotone left-right
  path within w=5 rows of the boundary (re-routing allowed = the topological content: a count
  survives local damage). Gates: ν stays EXACTLY integer and constant over the sweep while the
  bulk drift conductance declines smoothly (>30% decline over the same sweep).
- **P3 (Josephson 2):** V = (h/2e)·f chain: one 2π phase-slip of the weak link transfers ONE
  locked pair (CM01's 2-body cluster) carrying handedness 2e; energy bookkeeping per slip:
  2e·V = h·f. The "2" inherits CM01's body count (earned there as argued; exclusivity OPEN
  there). Printed with the inheritance flagged; K_J value itself IDENTITY.
- **P4 (metrology closure):** requires the native ohm chain (CM02). CM02 is flagged
  DO-NOT-TRUST → **DEFER**, citing CM02 re-run; note CM01-P1's honest normal-state chain as the
  partial repair that a CM02 re-run should build on.
- Forbidden: counting any IDENTITY line as a pass; Chern/gauge import; hand-rounding ν;
  tolerance changes; treating the h-cell premise as earned.

### §G mirror (pre-run)

- Faith ledger: the h-cell premise (ROOT-A, shared cluster-wide, named at every use); EMC03
  handedness as the confinement agent. Nothing else on faith.
- Gatekeeper: the rival's Chern machinery is neither used nor allowed to police the toy — the
  toy's claim is only "a count is disorder-rigid where a magnitude is not," which is checkable
  arithmetic, not borrowed topology.

## Phase gate record (from real stdout, run 2026-07-04, `cm06_results.txt`)

- P1: ν integer-only **PASS** (ν = 2 exactly, both boundaries, at every p).
- P2: ν constant over p ∈ [1e-4, 1e-1] (3 orders) **PASS** while bulk drift magnitude declines
  **96.5%** (gate >30%) **PASS**. G = e²/h chain printed as CONVERGENCE-conditional-on-ROOT-A,
  grade capped C as committed. IDENTITY block printed once, zero weight.
- P3: divisor-2 chain printed with CM01 inheritance flag carried (ARGUED there, exclusivity
  OPEN); single-vortex e/h counterfactual logged as the standing falsifier.
- P4: **DEFER** as committed (CM02 DO-NOT-TRUST; unblock = CM02 re-run on the CM01-P1 template).

### ADJ register

(none — no pivots)
