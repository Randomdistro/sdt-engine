# TD06 — Blackbody Thermodynamics from Lattice Modes

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Planck's law, Stefan–Boltzmann, and Wien's displacement law are the pillars of blackbody
thermodynamics, classically obtained by *postulating* quantised oscillators (`E=nhν`). The gap: derive
all three from **lattice mode counting** — because the relay lattice is *already discrete at ℓ_P*, the
quantisation is structural, not an extra axiom. This consolidates the prior SAR02–SAR02 results into one
thermodynamic statement.

## SDT mechanism & hypotheses

A cavity at temperature `T` is a region of disordered convergence throughput. The emission spectrum is
the throughput carried by the lattice's relay modes; mode counting is literal because the lattice has a
finite mode density set by `ℓ_P` and the cavity size. There is **no continuum** to regularise and **no
oscillator to quantise** — the `hν` granularity is the relay tick itself (`ε` per mode, Law I).

- **H1 (Planck from discrete modes):** counting relay modes per frequency band with TD02's occupation
  `exp(−ε/k_BT)` (derived, not postulated) gives `u(ν,T) = (8πν²/c³) · hν/(e^{hν/k_BT}−1)` — the
  Bose-like denominator emerging from indistinguishable relay quanta sharing throughput.
- **H2 (Stefan–Boltzmann):** integrating `u(ν,T)` over the discrete mode set yields `j = σT⁴` with `σ`
  expressed in lattice constants; the `T⁴` is the 3D-mode + linear-dispersion count, derived.
- **H3 (Wien):** the spectral peak `λ_max T = b` is the extremum of the mode-weighted throughput; `b`
  follows from the same counting with no new input. (SAR02–SAR02 already hit these — TD06 unifies them.)

## Strategy

1. **Mode counting → Planck.** *Goal:* reproduce `u(ν,T)`. *Method:* enumerate relay modes per band,
   weight by TD02's emergent occupation. *Success:* Planck curve to <0.1%; Rayleigh–Jeans (low ν) and
   Wien-tail (high ν) limits both recovered; no UV catastrophe (lattice cutoff at `ℓ_P`).
2. **Stefan–Boltzmann.** *Goal:* `σ` from lattice constants. *Method:* integrate the mode-summed
   spectrum. *Success:* `σ = 2π⁵k_B⁴/(15h³c²)` reproduced to <0.1%; `T⁴` exponent exact.
3. **Wien.** *Goal:* `b`. *Method:* extremise the spectral density. *Success:* `b = 2.898×10⁻³ m·K`
   to <0.1%; the transcendental constant `4.965…` derived, not inserted.
4. **Consolidation memo.** *Goal:* one statement subsuming SAR02–SAR02. *Method:* show all three are the
   same mode count read three ways. *Success:* a single derivation chain; cite SAR02–SAR02 numerics as the
   already-passed checks.

## Success criteria

- **PASS (Class A):** Planck, Stefan–Boltzmann, Wien all from lattice mode counting + TD02 occupation,
  only `k_B`, `h`, `c` as unit-bridges; no quantised-oscillator postulate, no continuum regularisation.
- **QUALIFIED (Class C):** all three numerically reproduced; the Bose-denominator step has one flagged
  indistinguishability assumption. *(Likely landing given SAR02–SAR02.)*
- **PENDING (Class D):** spectrum right but `σ`/`b` constants need a borrowed mode-density prefactor.
- **FAIL (Class F):** the spectrum only follows from `E=nhν` as an independent postulate.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | discrete lattice → Planck | `u(ν,T)` to 0.1%, no UV catastrophe | quantisation must be a separate axiom |
| T2 | mode integral → `σT⁴` | `σ=2π⁵k_B⁴/15h³c²`, exponent 4 | `T⁴` not from 3D mode count |
| T3 | extremum → Wien | `b=2.898e-3 m·K`, `4.965…` derived | displacement constant must be inserted |

## Dependencies

**Upstream:** SAR02–SAR02 (lattice mode counting → Planck/SB/Wien — already passed; TD06 consolidates),
[[TD02]] (emergent `exp(−ε/k_BT)` occupation), Law I (`ε` per mode). **Downstream:** stellar
thermodynamics (09), CMB / cyclic-cosmology spectrum ([[project_hubble_tension_resolution]],
[[project_sdt_cyclic_cosmology]]), TD07 (radiative bit-erasure heat bath). **Related:** [[TD01]]
(entropy of radiation `S=4/3 · aT³V`), CR07 (redshift as octaves — same lattice-mode ruler).
