# TD04 — Heat Conduction and Diffusion from Relay

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Fourier's law `q = −k∇T` and the diffusion equation describe heat spreading down a gradient, but
classically `k` is a measured material property. The gap: derive conduction as **throughput diffusion**
on the relay lattice and obtain `k` from a relay mean-free-path — the direct thermal analogue of
FD02's kinematic viscosity.

## SDT mechanism & hypotheses

Heat is disordered convergence throughput; a temperature gradient is a throughput-density gradient.
Each relay tick a spation hands a share of its disordered throughput to contact neighbours, so a
gradient relaxes by a random-walk of throughput — the same `λ_mfp v_relay` machinery FD02 used for
momentum, applied now to energy.

- **H1 (Fourier from diffusion):** the per-tick neighbour exchange of disordered throughput gives a
  net current `q = −k∇T` with `k = ⅓ c_v v_relay λ_mfp`; the `1/3` is lattice isotropy (as in TD03).
- **H2 (diffusion equation):** continuity of throughput + H1 yields `∂T/∂t = α∇²T`, `α = k/(ρc_v) =
  ⅓ v_relay λ_mfp` — the thermal diffusivity is a pure relay random-walk coefficient.
- **H3 (temperature scaling & Wiedemann–Franz):** `v_relay ∝ √T` (B16, as in FD02) gives `k ∝ √T` for
  a gas; in a metal the *same* mobile relay channel carries charge and heat, so `k/(σT)` collapses to a
  universal Lorenz number `L` — derived as one transport statistic, not two.

## Strategy

1. **Fourier coefficient.** *Goal:* `k = ⅓ c_v v_relay λ_mfp`. *Method:* impose a fixed `∇T` on a
   relay slab, run per-tick throughput exchange, measure steady current `q`. *Success:* `q = −k∇T`
   linear; fitted `k` matches `⅓ c_v v_relay λ_mfp` to <2%.
2. **Diffusion equation.** *Goal:* `∂T/∂t=α∇²T`. *Method:* release a hot stripe, track the profile.
   *Success:* Gaussian spread, variance grows `∝ t` with `α = ⅓ v_relay λ_mfp` (no free knob).
3. **Material check.** *Goal:* real `k` to order-of-magnitude. *Method:* plug measured `c_v`, sound
   speed (`v_relay` proxy), and a kinetic `λ_mfp` for air and a metal. *Success:* `k_air`, `k_Cu`
   within a factor of ~2; `k ∝ √T` slope confirmed for the gas.
4. **Wiedemann–Franz.** *Goal:* universal Lorenz number. *Method:* let the same relay channel carry
   both heat and charge; compute `k/(σT)`. *Success:* `L` constant across two metals to ~10%
   (prefactor flagged if it needs a calibrated channel-count).

## Success criteria

- **PASS (Class A):** Fourier + diffusion equation derived with `k=⅓c_v v_relay λ_mfp` native, `1/3`
  from isotropy, only `k_B` and measured material inputs used; `k∝√T` exact.
- **QUALIFIED (Class C):** mechanism + scaling native; absolute `k` within ~2× and Lorenz prefactor
  flagged. *(Expected.)*
- **PENDING (Class D):** diffusion works but `λ_mfp` must be borrowed from kinetic theory un-derived.
- **FAIL (Class F):** conduction needs a phonon/field model SDT forbids.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | conduction = throughput diffusion | `q=−k∇T`, `k=⅓c_v v_relay λ_mfp` ±2% | Fourier not a relay random-walk |
| T2 | `v_relay∝√T` (B16) | gas `k∝√T` slope 0.5 | thermal transport has another T-law |
| T3 | one channel carries heat+charge | Lorenz `k/(σT)=L` const ±10% | Wiedemann–Franz needs two mechanisms |

## Dependencies

**Upstream:** [[TD01]] (`T` as throughput, mixing), FD02 (`ν=⅓λ_mfp v_relay`, `ν∝√T` from B16 — same
machinery for energy). **Downstream:** TD05 (latent heat halts conduction at a front), TD06 (radiative
vs conductive transport), TD08 (`D` and `α` are the same random-walk). **Related:** [[TD02]]
(`c_v=3/2 k_B`), [[TD03]] (the `1/3` isotropy factor).
