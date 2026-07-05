# RUN_LOG — QM02 Uncertainty as Relay Bandwidth

**J. C. Harvey, Melbourne — 2026-07-03.** Executor: HUNTER-disciplined agent run.
Written BEFORE any tool code, per `PROMPT_EXECUTION_PROTOCOL.md`.

## Pre-Run Commitments — QM02

- Prompt completion target: **C** (the prompt's own pre-declared expected landing: bound native,
  ℏ attaches via one flagged borrow).
- Physics class hoped: CONVERGENCE (native ½ floor + one flagged ℏ-attach).
- CALIBRATED budget: 0 fitted. One FLAGGED structural borrow allowed: the k→p bridge (see below).
- Engine anchors: h via FD02 `κ = h/m` (measured circulation, OBSERVED). NO ψ, NO commutator
  `[x,p]=iℏ`, NO operator-variance inequality anywhere in the code.
- **Weighting justification (committed up front, the QM04-adjacent trap):** widths are computed with
  the pulse's **elastic energy density** `w(x) ∝ f(x)²` — the native classical weight for a real
  displacement field (energy ∝ strain²). This is NOT the Born rule: no probability is assigned; f is
  a real displacement amplitude, and Parseval gives the spectral energy density `|F(k)|²`. The ½
  floor to be tested is the classical Gabor band-limit on energy-weighted widths.

## Phase thresholds (committed before run)

Lattice: L = 8192 sites, spacing a = 1 (the ℓ_P analog). Discrete FFT; moments energy-weighted.

- **P1a (continuum regime, pulse width ≥ 3a):** every pulse (Gaussian σ = 3,5,20,100a; box W=64a;
  triangle W=64a; two-sided exponential s=16a) gives Δx·Δk ≥ 0.5 − 0.005. The Gaussian saturates:
  product ≤ 0.505 (<1%). Box/triangle/exponential do NOT saturate: product > 0.55. If any wide pulse
  gives < 0.495 → **KILL** the band-limit thesis (T1 trigger, no redefining variance after the fact).
- **P1b (lattice-scale probe — pre-registered, the honest danger case):** pulses at or below one
  site (single-site delta; Gaussian σ = 0.3a, 0.5a, 1a) computed under BOTH definitions:
  (i) point-lattice (sites are points); (ii) lattice-native finite-extent (each spation is a cell of
  width a; its own second moment a²/12 adds to Δx²). **Pre-commitment:** the point definition is
  expected to let the delta beat ½ trivially (Δx = 0); that alone does NOT kill the thesis — the
  pre-registered pivot (per prompt pivot table row P1, "re-check the discrete variance definition —
  lattice, not continuum") is definition (ii), justified physically: a spation has finite extent ℓ_P
  (matter is substantive; sub-cell structure is not a state of the lattice). **Kill trigger:** if any
  pulse beats 0.49 under definition (ii) as well, the thesis dies — no third definition may be tried.
- **P2 (attach ℏ — provenance analysis, no numeric fit):** Δk→Δp uses p = ℏk. The committed honest
  chain: FD02 measured circulation κ = h/m (OBSERVED, 0.02%) + the substrate identity
  v = (κ/2π)∇φ (superfluid phase-gradient kinematics — [[project_substrate_superfluid_upgrade]],
  Onsager–Feynman) ⇒ k = mv/ℏ ⇒ Δx·Δp ≥ ℏ/2. The identity is a STRUCTURAL BORROW (not derived from
  tick mechanics in this repo) → grade capped at C exactly there. The commutator is never written.
- **P3 (spreading packet):** requires native wake dynamics (the wake dispersion law = ROOT-SIM core,
  unavailable). **Pre-declared OPEN — not run.** Running it with the Schrödinger dispersion would be
  an import; refusing to fake it is the honest outcome.
- **P4 (time axis):** same theorem on (t, ω): Gaussian-in-time saturates ½ within 1%; damped
  exponential e^{−t/2τ}: variance-based Δω DIVERGES (Lorentzian tails — report as found), linewidth
  statement instead: FWHM(|F(ω)|²) = 1/τ within 2% ⇒ Γ = ℏ/τ with ℏ entering at the same single P2
  point. No threshold moved after seeing output.

## Forbidden (restated)

Write `[x,p]=iℏ` or any operator inequality; widen tolerances post-hoc; a third variance definition
if (ii) fails; claim Class A while the k→p bridge is borrowed.

## Run record

- 2026-07-03: commitments frozen. Tool `qm02_relay_bandwidth.py` written after this block.
  → `qm02_results.txt` (real stdout), `QM02_VERDICT.md`.
- **ADJ-1 (2026-07-04, PRE-RUN — scope note added before any number was produced):** per FLM14
  ADJ-7 two-channel doctrine and HUNTER §G: the Δx·Δk floor tested here is a **PULSE-CHANNEL
  statement only** (real wake pulses relaying at c). It asserts NOTHING about the geared
  CONSTRAINT channel (phase constraint through gear-locked clusters, uncapped), which carries no
  free energy and no pulse bandwidth. §G faith-ledger at hunt start: accepted machinery = elastic
  energy ∝ f² (internal consistency, Law I strain energy), discrete Fourier analysis of real
  signals (mathematics, not a rival's formalism); flagged faith = the k→p bridge (named borrow,
  Phase 2). No gate below traces to a rival axiom. Thresholds unchanged.
