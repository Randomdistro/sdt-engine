# QM02 — Uncertainty as Relay Bandwidth

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Is the Heisenberg relation **Δx · Δp ≥ ℏ/2** a *bandwidth* property of the convergence wake — the
unavoidable Fourier-type trade between how tightly the wake is localised in the lattice and how
sharply its relay period is defined — rather than an operator-commutator postulate? In SDT a
particle is a hard solid vortex with a definite position and momentum at every tick; "uncertainty"
must then be a property of the **wake's spectral content**, not an ontic indeterminacy of the
vortex. Reproduce ℏ/2, the minimum-uncertainty packet, and the Δt·ΔE form from relay mechanics.

## SDT mechanism & hypotheses

The vortex drags a convergence wake (PPT06/APS04) whose spatial profile is a real lattice pulse. A
pulse confined to N spations has a relay-period spread set by discrete Fourier duality on the
lattice — narrow in `x` ⇒ broad in spatial frequency ⇒ broad in `p` via the relay dispersion
λ = h/p (QM01-H2). The "measurement disturbance" story is replaced by a **structural bandwidth
floor**: you cannot build a wake packet that is both spatially compact and spectrally pure.

- **H1 (Fourier-duality floor):** the wake's `Δx · Δk ≥ ½` is the standard band-limit theorem on the
  relay lattice; multiplying by ℏ (from `κ = h/m`, FD02) gives Δx·Δp ≥ ℏ/2 with **no commutator**.
- **H2 (minimum packet = relay Gaussian):** the equality case is the smoothest lattice pulse (a
  discrete Gaussian), the wake shape of a free vortex — saturating the bound natively.
- **H3 (energy–time):** Δt·ΔE ≥ ℏ/2 is the same theorem on the time axis — finite relay-tick
  duration vs frequency sharpness; linewidth Γ = ℏ/τ follows for QM06 emissions.

## Strategy

**Phase 1 — Relay band-limit theorem.** *Goal:* derive Δx·Δk ≥ ½ for a lattice pulse.
*Method:* discrete Fourier analysis of an N-spation wake packet; variance product. *Success:* the ½
floor recovered analytically and numerically for Gaussian/box/triangle pulses; saturation only by
the Gaussian to <1%.

**Phase 2 — Attach ℏ.** *Goal:* turn Δk into Δp. *Method:* apply λ=h/p with h from `κ=h/m` (FD02,
0.02%). *Success:* Δx·Δp ≥ ℏ/2 with the coefficient ℏ/2 **derived, not inserted**; trace ℏ provenance.

**Phase 3 — Minimum-uncertainty packet.** *Goal:* show the free-vortex wake saturates the bound.
*Method:* evolve a discrete Gaussian wake one tick at a time (FLM05); track variance product.
*Success:* product stays within 1% of ℏ/2 while the packet spreads — spreading is real, indeterminacy is not.

**Phase 4 — Energy–time & linewidth.** *Goal:* Δt·ΔE form. *Method:* finite-duration wake on the
time axis; map to natural linewidth Γτ ≈ ℏ. *Success:* Γ = ℏ/τ reproduced; hooks QM06.

## Success criteria

- **PASS (A):** all four phases native; ℏ/2 derived from the relay band-limit with zero fitted scale.
- **QUALIFIED (C):** bound reproduced but ℏ attaches via one flagged borrow from FD02 (expected landing).
- **PENDING (D):** Fourier floor shown but the Gaussian-saturation or Δt·ΔE step only heuristic.
- **FAIL (F):** cannot get ℏ/2 without importing the canonical commutator `[x,p]=iℏ`. Report honestly.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 — band-limit is the source | Δx·Δk ≥ ½ for every lattice pulse, =½ only for Gaussian | uncertainty not a bandwidth fact |
| T2 — coefficient is ℏ/2 | derived ℏ/2 ±1% with h from κ=h/m | ℏ smuggled, not native |
| T3 — vortex stays definite | per-tick position/momentum sharp; only the wake spreads | ontic indeterminacy crept back in |

## Dependencies

**Upstream:** QM01 (relay-wake kinematics, λ=h/p), FD02 (`κ=h/m` fixes ℏ), FLM05 (tick evolution).
**Downstream:** QM06 (linewidth/Δt·ΔE), QM04 (variance ↔ residence density).
**Related:** [[project_paradox_census]] (§8.2 — no ontic randomness owed), [[project_foundational_ontology_influx_monopole]] (no ψ).
