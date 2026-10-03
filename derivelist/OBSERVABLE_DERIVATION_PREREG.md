# Observable-ratio derivations — pre-registration (2026-10-03)

> Written before `observable_derivations.cpp` existed. Direct execution, main session.
> Technique under test: **a listed scale is read off as a ratio of two measured quantities of the
> same dimension, with no other listed scale entering the ratio.** The technique is falsifiable if
> (i) each gate below can be missed by a physically possible outcome and (ii) each negative control
> misses its gate.

## Routes and gates (thresholds fixed here, not adjusted after the run)

| id | quantity | ratio of observables | gate | control that must miss the gate |
|---|---|---|---|---|
| A1 | α = k_H⁻¹ | 16·Δν(2P3/2–2P1/2) / (c R∞), both frequencies | \|Δ(1/α)\| ≤ 0.2 % vs measured::alpha | A3 |
| A2 | α, raw hydrogen line | R_H = (4/3)·ν(1S–2S); α² = 16·Δν_fs/R_H | \|Δ(1/α)\| ≤ 0.2 % | A3 |
| A3 | control | A1 with degeneracy factor 8 in place of 16 | must exceed 0.2 % (expected ≈ 41 %) | — |
| L1 | ℓ_P | ℓ_P² = ϟ_b · ƛ_p ; ϟ_b = G m_p / c² (Cavendish coupling per counted baryon, OBSERVED); ƛ_p = R_p/(W+1), W+1 = 4 | within 3σ (σ_rel = 1.15×10⁻³ from u(R_p), u(G)) of measured::l_P | L2: W+1 = 3 and 5 must exceed 3σ |
| H1 | ℏ | ℏ = m_e·(α_B c)·a₀ with a₀ = α_B/(4πR∞), α_B from A1 | ≤ 0.5 % vs measured::hbar | — |
| E1 | e | e = 2/(K_J·R_K), Josephson and von Klitzing electrical measurements | ≤ 1×10⁻⁶ vs measured::e_charge | — |
| C1 | c | λ·ν, Evenson 1972 | within 3σ; tagged IDENTITY-CLASS (metre now defined from c), outside the earned tally | — |
| K1 | k_B | k_B/h = ν_peak / (x·T) from a measured blackbody peak and an independent thermometer | PENDING — no raw peak/thermometer pair in the repo; tabulated Wien b is circular since 2019 | — |
| T1 | T_CMB | measured directly (FIRAS) | OBSERVED boundary state; no derivation expected | — |

Rejection class populated: A1/A2 (a wrong splitting law, e.g. A3, lands 41 % off), L1 (wrong W+1 lands 15 % off),
H1 (a wrong seat form lands ≥ 100 % off), E1 (any non-electrical origin lands off by the unit ratio).

## Forbidden inputs
No G, no M as fundamentals: G enters L1 only as the OBSERVED Cavendish coupling to a counted baryon (ϟ_b);
it is not a seed. No quantum wavefunction, no QED perturbation series. The fine-structure
formula used is the closed form α²/16 of the n=2 splitting over the Rydberg interval; the measured
excess over it is reported as a residual, not corrected.

## Raw observed inputs and provenance (local, not in `measured`)
- Δν(2P3/2–2P1/2) = 10 969.04 ± 0.15 MHz (Hagley & Pipkin 1994)
- ν(1S–2S) = 2 466 061 413 187 035 Hz (Parthey et al. 2011)
- G = 6.674 30(15)×10⁻¹¹ (CODATA 2018)
- K_J-90 = 483 597.9 GHz/V, R_K-90 = 25 812.807 Ω (conventional values)
- c: Evenson et al. 1972, 299 792 456.2 ± 1.1 m/s
- Everything else from `sdt::laws::measured`.
