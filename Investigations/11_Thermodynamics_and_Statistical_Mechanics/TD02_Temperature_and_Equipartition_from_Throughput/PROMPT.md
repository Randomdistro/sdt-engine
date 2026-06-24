# TD02 — Temperature and Equipartition from Throughput

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

TD01 made entropy a literal microstate count; what *is* temperature on the lattice, and why does
each quadratic degree of freedom get exactly `½k_BT`? The gap: derive `T` and equipartition from
relay throughput sharing alone, without imposing a Boltzmann distribution or a partition function.

## SDT mechanism & hypotheses

Heat is disordered convergence throughput. A hot region carries more random tick-to-tick throughput
per spation than a cold one. Temperature is therefore not a primitive — it is the **mean disordered
relay throughput per spation degree of freedom**, and `k_B` is the measured unit-bridge that converts
throughput (in SDT energy units) to kelvin, exactly as `e` bridges handed redirection to coulombs.

- **H1 (T = throughput/DoF):** `k_BT ≡ ⟨ε_dis⟩` per spation DoF; the thermodynamic `1/T = ∂S/∂E`
  (TD01's `S=k_B ln W`) returns the *same* `T`, proving the two definitions coincide.
- **H2 (equipartition from even sharing):** because the relay redistributes throughput to contact
  neighbours with no preferred channel, at the spread maximum every quadratic DoF holds `½k_BT` —
  equipartition is the stationary point of TD01's mixing, not a separate postulate.
- **H3 (Maxwell–Boltzmann emerges):** equal-weight microstate counting under a fixed total-throughput
  constraint yields an exponential occupation `∝ exp(−ε/k_BT)` for a single DoF — the MB/Gibbs factor
  *derived*, never assumed.

## Strategy

1. **Two-definition concordance.** *Goal:* show kinetic and entropic `T` agree. *Method:* on the
   TD01 toy lattice compute `T_kin = ⟨ε_dis⟩/(½k_B)` per DoF and `T_ent = (∂S/∂E)⁻¹`. *Success:*
   `|T_kin − T_ent|/T < 10⁻³` across the energy range.
2. **Equipartition.** *Goal:* `½k_BT` per quadratic DoF. *Method:* seed lattice blocks with unequal
   DoF energies, relax per-tick, measure stationary per-DoF energy. *Success:* `⟨E_i⟩ = ½k_BT ± 1%`
   for every DoF independent of initial split.
3. **Gibbs factor.** *Goal:* derive `exp(−ε/k_BT)`. *Method:* enumerate occupation of one tagged DoF
   in contact with a large relay reservoir at fixed total `E`. *Success:* histogram fits MB exponential
   with `T` from Phase 1 to `R² > 0.999`; recover `c_v = 3/2 k_B` for a monatomic relay gas.
4. **Temperature scale audit.** *Goal:* confirm `k_B` is the *only* whitelisted input. *Method:*
   delete-test — recompute with `k_B` symbolic. *Success:* every result is `k_B × (pure number)`.

## Success criteria

- **PASS (Class A):** `T_kin=T_ent`, `½k_BT` per DoF, and MB factor all derived from relay sharing
  with only `k_B` whitelisted; zero fitted parameters.
- **QUALIFIED (Class C):** the above with one flagged ergodicity/coarse-graining step. *(Expected.)*
- **PENDING (Class D):** equipartition holds numerically but the MB-factor derivation stays heuristic.
- **FAIL (Class F):** `T` cannot be defined without importing an ensemble or partition function.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | T = throughput/DoF | `T_kin = T_ent` to 0.1% | temperature has a non-throughput basis |
| T2 | even sharing → equipartition | `½k_BT` per quadratic DoF, init-independent | a DoF is privileged; sharing not even |
| T3 | counting → Gibbs factor | occupation `∝ exp(−ε/k_BT)`, `R²>0.999` | MB must be imposed, not derived |

## Dependencies

**Upstream:** [[TD01]] (`S=k_B ln W`, relay mixing), Law I (`ε`, throughput), FLM02/FLM05 (ticks).
**Downstream:** TD03 (ideal gas needs `T`), TD07 (Landauer needs `k_BT`), TD08 (Einstein `D=µk_BT`).
**Related:** SAR02–SAR02 (mode counting), FD02 (`v_relay`, `λ_mfp` reused in TD04/TD08).
