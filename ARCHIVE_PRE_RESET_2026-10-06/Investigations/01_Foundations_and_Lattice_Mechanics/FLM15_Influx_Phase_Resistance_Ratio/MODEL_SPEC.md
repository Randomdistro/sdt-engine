# FLM15 Model Specification

## Linear-response derivation

Let a persistent phase defect have static configuration
`phi(x-X)`, where `X(t)` is its centre. Translation gives

```text
d_t phi = -X_dot · grad(phi).
```

For a relay medium whose quadratic phase cost is common to both topologies,
the translation-dependent reorganisation energy is

```text
E_reorg = C/2 integral (d_t phi)^2 dV
        = C/2 X_dot_a K_ab X_dot_b
K_ab   = integral d_a(phi) d_b(phi) dV.
```

`C` contains the common Law-I influx and Law-IV dimensional conversion.
Consequently the dimensionless inertial resistance is

```text
J = trace(K)/3
m_3/m_1 = J_3/J_1.
```

This derives a ratio only. It does not derive an absolute kilogram without
the repository's one mass/action seat.

## Isotropic cancellation

For unit influx direction `n`,

```text
R(n) = integral (n·grad(phi))^2 dV.
```

Using `average(n_a n_b)=delta_ab/3`,

```text
average_n R(n) = trace(K)/3.
```

Thus isotropic angular averaging supplies the same `1/3` for every form. It
cannot by itself generate a large topology-dependent factor. Such a factor
must come from the W-dependent phase field or a W-dependent locked domain.

## Filament phase field

The numerical phase-gradient proxy is the regularised vortex-filament field

```text
g(x) = Gamma/(4 pi) integral_C dl × (x-X)
       / (|x-X|^2 + a_core^2)^(3/2).
```

The common prefactor cancels. The solver evaluates:

```text
K_ab = integral g_a g_b dV
J = trace(K)/3.
```

The regularisation, integration domain, and sample sequence are identical for
the two topologies. Dependence on them is reported rather than hidden.

## Geometry and provenance

- Circle: analytic unit-radius polygon, `W=1`.
- Trefoil:

```text
x=(R+a cos(3t)) cos(2t)
y=(R+a cos(3t)) sin(2t)
z=a sin(3t)
```

The aspect ratio `a/R` is scanned. The previously asserted equilibrium value
is included as one frozen row, not privileged in aggregation.

## Model ladder

- `R0_BARE`: curve length and enclosed tube proxy.
- `R1_PHASE_STIFFNESS`: `integral |g|^2 dV`.
- `R2_TRANSLATION_TENSOR`: full `K`, eigenvalues, anisotropy, and `J`.
- `R3_FULL_INFLUX_CYCLE`: deterministic directional quadrature; expected to
  equal `J` if the isotropic identity is complete.
- `R4_LOCKED_WAKE`: FLM07 supplies the target-free separatrix. With isotropic
  `mu=|cos(theta)|`, the relay capacity condition is `mu<=k(r)`, hence
  `f_lock(r)=clip(k(r),0,1)` and `f_wake=1-f_lock`. For
  `k(r)=sqrt(r/r_c)` inside the supplied mechanical c-boundary:

```text
V_lock = 4 pi integral_0^r_c r^2 sqrt(r/r_c) dr = 8 pi r_c^3/7
V_wake = 4 pi r_c^3/3 - V_lock = 4 pi r_c^3/21
Resistance = (P_conv/3) V_lock
delta_Resistance_sync = (P_conv/3)(V_joint-sum(V_parts)).
```

`V_joint` is the saturated union of coherent engaged-density domains, so
non-overlapping bodies have zero synchrony change and coincident identical
domains count once. No fitted amplitude threshold enters.

## Scope

R0–R3 test whether simple phase-field stiffness pays the topology-ratio debt;
R4 supplies a reusable engaged-volume and synchrony kernel. R4 does not turn
the already excluded order-unity R0–R3 result into the particle mass ratio.
Applications must provide a separately derived mechanical boundary and may not
infer it from the target being compared.
