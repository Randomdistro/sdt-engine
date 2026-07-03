# RUN_LOG — TD07 Information Thermodynamics and Landauer

**Executor:** J. C. Harvey, Melbourne · 2026-07-03
**Committed BEFORE first compile/run. No threshold below may be widened after a number is seen.**

## Pre-Run Commitments — TD07

- Prompt completion target: **B**
- Physics class hoped: the prompt itself concedes the k_BT ln2 step is near-definitional given
  TD01+TD02. Pre-registered: Landauer is a theorem of probability + energy bookkeeping; unless a
  lattice-specific step does work, class is **NULL-SDT-CONTENT / CONVERGENCE**. One candidate
  lattice-specific item to watch: the integer relay quantum ε forces stepped protocols — does
  discreteness leave a strictly negative demon net even quasi-statically? (To be tested, not sold
  in advance.)
- CALIBRATED budget: 0. Whitelist: `measured::k_B`. Units: ε = 1, k_B = 1 internally.
- Setup: joint microcanonical system = two-state register (levels E_L = 0, E_R = protocol) +
  TD01 bath (N = 2000 cells, E = 20000 quanta, kT = ε/ln(1+N/E) = 10.49 ε). Dynamics: symmetric
  proposals only (bath-bath one-quantum moves; register flips exchanging ΔE with ONE random
  cell) → uniform joint measure; NO Boltzmann factor input anywhere. Exact ledger from counting:
  p_R(E_R) = W_b(E_tot−E_R)/[W_b(E_tot−E_R)+W_b(E_tot)].

## Phase thresholds (committed)

- **P1 (Landauer ledger):**
  - Exact quasi-static work (trapezoid over integer ramp 0→80): |W_qs/(kT ln2) − 1| < 1%
    (declared systematics: tail p_R(80) ≈ 5e-4 → ~0.07%; finite-bath drift ≤ 0.4%).
  - Sim validation: p_R at E_R ∈ {5,10,20,40} within 3σ of exact counting.
  - Finite-time: W(n_eq=200) > W(n_eq=2000) > W(n_eq=20000) with gaps > 3 combined SE;
    W(slowest) within 3 SE of W_qs. The BOUND (approached from above) is the claim, not an identity.
- **P2 (demon/Szilard closure):**
  - Exact: net = W_extract − W_erase = −ε·[p_R(0) − p_R(80)] ≈ −0.5 ε ≤ 0 (the two ledgers are
    the same trapezoid; endpoints differ). Committed disclosure: whether this strictly negative
    quasi-static net is an ε-discreteness (stepped protocol) effect — report exactly, oversell nothing.
  - Sim: net < 0 at all three speeds (3 SE).
- **P3 (reversibility boundary):** partial erasure to E_t ∈ {2,5,10,20,40}:
  |Q(E_t) − kT[ln2 − H(p_R(E_t))]| < 1.5% of kT ln2, where Q = W − ΔU_register = W − E_t·p(E_t)
  is the HEAT dumped to the bath (H = binary entropy in nats; discretization budget ≈ 0.1%).
  *(ADJ-0, pre-first-compile: the draft compared the WORK W = ΔF to kT[ln2−H]; for partial
  erasure the Landauer-form quantity is the heat Q = W − ΔU — they coincide only at full
  erasure. Category error caught and fixed before any run; gate value unchanged.)*
  Reversible end: E_t = 0 → W = Q = 0 exactly (disclosed as trivial); swap gate (relabel,
  W unchanged) costs 0 — near-definitional, labelled as such.
- **P4 (delete test):** every bound = k_BT × pure number (ln2, H(p)); no ensemble object; the
  only inputs are counting + symmetric dynamics.

## Decision rules

- If the demon nets > 0 anywhere: that is a Second-Law loophole → report as F-class finding
  immediately (do not bury). If sim p_R drifts from counting: trace mixing before touching gates.
- Physics class decided by: does any step break on a non-SDT substrate?

## Run record

- [x] ADJ-0 (pre-compile): P3 quantity corrected from work W=ΔF to heat Q=W−ΔU (category
      error; gate value unchanged). Recorded above.
- [x] compile (MSVC /std:c++20 /O2) — clean
- [x] RUN 1: exit 1 — finite-time gate FIRED: W_fast = 6.81 < kT ln2. Traced: trajectories
      started from an UNMIXED bath (no fluctuations → no rich cells → L→R re-entry blocked,
      R→L always allowed) = a non-equilibrium bath, i.e. a work resource; the bound's premise
      was voided by the tool, not the physics. **ADJ-1: 5e5-tick bath pre-mix per trajectory;
      gates unchanged.**
- [x] RUN 2: exit 0 — all gates pass → results.txt (real stdout). Slow runs center on the
      stepped-protocol left-sum 7.52 ε (= W_qs + ε·Δp/2), consistent with the demon deficit.
- [x] verdict: TD07_VERDICT.md — Prompt B · Physics NULL-SDT-CONTENT/CONVERGENCE · demon
      closed (net = −0.4995 ε exact, ≤ 0 at all speeds); scoped ε-step overhead result
