# RUN_LOG — TD06 Blackbody Thermodynamics from Lattice Modes

**Executor:** J. C. Harvey, Melbourne · 2026-07-03
**Committed BEFORE first compile/run. No threshold below may be widened after a number is seen.**

## Pre-Run Commitments — TD06

- Prompt completion target: **B**
- Physics class hoped: NATIVE; pre-registered suspicion: the chain is Planck 1900 / Bose 1924
  counting; the load-bearing quantum content is the `hν = ε` identity (Law I bridge), which is
  *asserted*, not derived — if nothing else lattice-specific does work, class is **CONVERGENCE**.
- CALIBRATED budget: 0. Whitelist: `measured::k_B`; `c` and `h` used ONLY as the Law-I bridges
  (tick speed; throughput-per-tick granularity ε = hν) and documented as such. If at any point
  `h` must act as an independent oscillator constant, grade F per prompt.
- SAR02 is an external cross-check ONLY (its `a` at 4.4 ppm). TD06's pass/fail is decided by
  TD06's own mode sums. No grade may cite SAR02's pass.
- TD02 inheritance: occupation factor — TD02's firewall did NOT fire (native counting), so the
  occupation is not IMPORTED; TD02's class is CONVERGENCE, so TD06 is capped at CONVERGENCE.

## Phase thresholds (committed)

- **P1a (mode density):** integer standing-wave modes of a cubic cavity, 2 polarisations,
  counted in shells dR=20 for R ∈ [200, 1000]: counted density vs 8πν²/c³ mean |dev| < 0.1%
  (Gauss-sphere fluctuation estimated ~0.03% at this size — committed before run).
- **P1b (occupation from counting, the Bose denominator shown native):**
  (i) hill-climb: distribute U quanta over B=40 bands (g_b ∝ b², large g), energy-conserving
  integer exchange moves accepted iff ΔS = Δln W > 0, from a NON-Bose start; converged
  occupations must satisfy the exact discrete stationarity ln(1 + g_b/q_b) = β ε_b: linear fit
  R² > 0.9999 and RMS occupation deviation from the β-fit Bose form < 1% (occupied bands,
  n̄ > 0.01). (ii) single-mode marginal within a band: p_j ratio constant (geometric) to <1%
  for j with p_j > 1e-4 — the "multiple quanta per mode" series is counted, not lifted.
- **P2 (Planck curve):** counted modes × counted occupation vs continuum Planck: mean |dev|
  < 0.1% over the thermal range; RJ limit (x→0) and Wien tail (x→10) recovered within 1%.
- **P3 (Stefan–Boltzmann):** total mode-sum energy vs π⁴/15 continuum: < 0.1% at θ = kT = 50
  (cavity units, n_max = 1000); fitted T-exponent over θ ∈ {40, 50, 60}: 4.00 ± 0.02;
  σ_SI = 2π⁵k_B⁴/(15h³c²) then compared to measured a_rad = 4σ/c (report ppm; consistency).
- **P4 (Wien):** peak of the counted u_λ extremised numerically; transcendental root must
  emerge as 4.965114 ± 1e-5 from bisection on the derivative (not inserted); b = hc/(x*k_B)
  vs 2.898e-3 m·K < 0.1%.
- **P5 (UV honesty):** state numerically that at T = 300 K the ℓ_P mode cutoff does ZERO work
  (occupation at the cutoff underflows); finiteness at physical T is from ε = hν quantisation —
  i.e. the renamed Planck postulate. This disclosure is a committed deliverable, not optional.

## Decision rules

- Any gate miss → pivot per PROMPT §⑩; never widen; SAR02 may not rescue anything.
- Physics class: which step would break if the substrate were not an SDT lattice?

## Run record

- [x] compile (MSVC /std:c++20 /O2) — clean
- [x] RUN 1: exit 1 — P1a/P2/P3 fired on ONE root: Weyl surface term of the octant (walled)
      count, dev·R ≈ −1.45 const (my error budget had only the Gauss fluctuation). P1b fired:
      paired-shift moves accidentally conserved quantum NUMBER → Bose-with-μ (intercept 0.682).
- [x] ADJ-1: pivot to periodic bulk mode count (allowed alternative native route; octant kept
      as documented contrast). ADJ-2: merge/split moves added (energy-conserving, number-
      changing). **All gates unchanged.**
- [x] RUN 2: exit 0 — all gates pass → results.txt (real stdout)
- [x] Disclosure: RJ sub-check at x=0.05 carries the exact analytic x/2 offset (0.975208);
      RUN_LOG's "1%" was mis-specified vs the estimator; agreement with the 2nd-order RJ
      expansion is 3e-6. Disclosed in VERDICT, not re-gated.
- [x] verdict: TD06_VERDICT.md — Prompt B · Physics CONVERGENCE (capped by TD02; ε=hν bridge
      is the disclosed load-bearing assertion; ℓ_P cutoff does zero work at physical T)
