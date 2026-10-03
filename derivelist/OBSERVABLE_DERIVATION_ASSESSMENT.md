# Observable-ratio derivations — assessment (2026-10-03, direct execution)

Pre-registration: `OBSERVABLE_DERIVATION_PREREG.md` (written before the tool). Tool:
`observable_derivations.cpp` (`g++ -std=c++20 -O2 -I../Engine/include`). Output:
`observable_derivations_results.txt`. Standing check: `check_input_status.py`.

## Result

Earned gates within tolerance 5/5; negative controls that miss as required 3/3.

| scale | derived from | result | label |
|---|---|---|---|
| α = 1/k_H | 16·Δν(2P3/2–2P1/2) / cR∞ (ratio of two frequencies; no m, e, h) | 1/α = 136.913 (−0.090 %) | OBSERVED ratio |
| α, raw line | same, with R_H = (4/3)ν(1S–2S) | 1/α = 136.876 (−0.117 %; reduced mass not applied) | OBSERVED ratio |
| ℓ_P | √(ϟ_b·ƛ_p), ϟ_b = G m_p/c² (Cavendish coupling per counted baryon), ƛ_p = R_p/4 | 1.616413×10⁻³⁵ m, +0.0098 % vs stored (σ_rel 0.11 %) | OBSERVED inputs; convergent with the ℏ-route value |
| ℏ | m_e·(αc)·a₀, a₀ = α/(4πR∞) | +0.18 % | OBSERVED seat; the Rydberg relation rearranged, not independent of it |
| e | 2/(K_J·R_K) | −8.9×10⁻⁸ | OBSERVED ratio |
| c | λν (Evenson 1972) | 1.6σ | IDENTITY-CLASS (metre defined from c); outside tally |
| k_B | k_B/h = ν_peak/(x·T) | no raw peak/thermometer pair in repo | PENDING |
| T_CMB | FIRAS | measured state | OBSERVED, not derived |

Controls: degeneracy 8 for 16 → α off 41 %; W+1 = 3 or 5 → ℓ_P off +15.5 % / −10.6 %. The technique
can fail and does where it should.

## What this establishes
- **α is k for hydrogen**: v₁/c read as a ratio of two counted spectral frequencies. The 0.09 % residual is the measured
  excess over the closed form (not corrected). α is an observed ratio, the same class as k_Sun. Its topology-only origin
  (why 137) stays open and is a separate claim from its status as an input.
- **ℓ_P needs no seed**: three observations (the coupling G m_p/c², m_p, and R_p from muonic spectroscopy) give it to 0.01 %
  with no ℏ in the chain; the W+1 = 4 selection is sensitive (controls). It is independent of the ℏ route by origin.
- Caveats: G enters as the observed coupling to a counted baryon, not as a fundamental. R_p/4 vs ℏ/(m_p c) is the recorded
  0.02 % one-fact (R_p ≡ m_p). The L1 gate (3σ) is loose against the 0.01 % agreement because u(R_p) dominates.

## Why the repo kept reverting (finding)
A derived relation recorded in prose does not bind anything: `measured::l_P` is a stored literal, and live files restate the old
status. `check_input_status.py` fails while any live file still says so. At this commit it reports 6 stale statements (including
`CLAUDE.md` "the ONLY external inputs") — see its output. Canon (`laws.hpp`, `Laws/`) edits are proposed, not made:
(1) replace the stored `measured::l_P` literal with the L1 expression, keeping CODATA ℓ_P as a comparison value;
(2) retire "ONLY external inputs" in `CLAUDE.md`.
