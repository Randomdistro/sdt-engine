# FLM15 Assessment — Influx-Phase Resistance Ratio

**Author:** James Christopher Tyndall, Melbourne  
**Date:** 2026-08-14  
**Overall result:** `R4_RELAY_LOCK_KERNEL_DERIVED`; the earlier
`SIMPLE_PHASE_STIFFNESS_EXCLUDED_AS_LARGE_WAKE` result is unchanged

## Result

The blind W=3/W=1 linear phase-resistance ratio is:

```text
J_3/J_1 = 2.6471
primary geometry/orientation range = 2.4419–2.8406
reference converged plateau = 2.67–2.68
```

This is an order-unity topology effect. It is not the proton/electron mass
ratio and does not support either large post-run formula.

## Four separate outcomes

### 1. FLM12 resistance ontology — retained, not numerically certified

FLM15 does not falsify the statement that mass is the convergent influx's
resistance to changing a form's vector. It gives that statement a definite
linear-response object. The ontology remains a framework claim because this
particular object does not recover the observed W=3/W=1 magnitude.

### 2. Translation functional — derived and computed

For `phi(x-X(t))`, `d_t phi=-v·grad(phi)` leads to:

```text
K_ab = integral d_a(phi) d_b(phi) dV
J = trace(K)/3.
```

The directional identity
`average[(n·grad(phi))²]=|grad(phi)|²/3` passed at relative error `3.99e-5`.
The common `1/3` therefore cancels from the ratio. `R3_FULL_INFLUX_CYCLE` is
not a new multiplier; under isotropy it is exactly the trace average in R2.

### 3. W=3/W=1 prediction — computed for the specified field model

The regularised filament calculation converges. Segment, sample, core, and box
scans each shift the reference ratio by less than about `0.4%`; trefoil aspect
and orientation span the wider `2.442–2.841` range. The model predicts an
order-unity ratio robustly, but the precise aggregate depends on the allowed
trefoil geometry.

Across the primary scan, ordered tensor eigenvalues span
`(0.300–0.309, 0.303–0.311, 1.059–1.064)` for the circle and
`(0.796–1.561, 0.806–1.601, 1.603–2.743)` for the trefoil. Circle anisotropy
is `1.344–1.371`; trefoil anisotropy is `0.026–1.341`. Because each pair uses
the same integration volume, the response-density ratio is also
`2.442–2.841`. The 2026-08-14 R4 extension now derives the generic relay-lock
fraction and engaged-volume integral, but no topology-specific mechanical
boundary is inferred for this old ratio. A global phase shift leaves `grad(phi)` unchanged,
so the frozen phase scan is analytically constant rather than a selectable
degree of freedom.

This result applies to a regularised Biot–Savart phase-gradient proxy. It is
not proof that every discrete-spation response functional has the same ratio.

### 4. Linear phase stiffness does not generate the mass ratio

After sealing, the computed ratio was compared with the measured ratio,
`6 pi^5`, and the winding self-index construction. It is `99.856%` below all
three. The arithmetic correspondences remain available as conjectures, but
simple phase stiffness and its translation tensor do not generate them.

This negative result is mechanism-specific. PPT17 subsequently resolves the
`6π⁵` assignment as a shared-input tube-volume construction; FLM15 neither
tests nor contradicts that geometric map.

## Model-ladder disposition

- `R0_BARE`: order unity (`length ratio 2.143–2.616`).
- `R1_PHASE_STIFFNESS`: computed; order unity.
- `R2_TRANSLATION_TENSOR`: computed; `J_3/J_1=2.647`.
- `R3_FULL_INFLUX_CYCLE`: collapses analytically to R2 under isotropy.
- `R4_LOCKED_WAKE`: generic kernel DERIVED from FLM07's glancing equality:
  `f_lock=clip(k,0,1)`, `f_wake=1-f_lock`,
  `V_lock=8πr_c³/7`, `V_wake=4πr_c³/21`, and
  `Resistance=(P_conv/3)V_eng`.

The angular and radial controls pass, the partition is exact, and coincident /
non-overlapping synchrony endpoints are analytic. The supplied mechanical
boundary is not fitted. A topology-specific boundary remains an upstream
application requirement and cannot be inferred from a target ratio.

## Repository consequence

The minimal target-free kernel is promoted to `law_IV`; particle constants and
the R0–R3 exclusion are unchanged. No particle mass, radius prediction, or
topology ratio is promoted by the R4 result.

## Next falsifiable debt

Each downstream application must derive its mechanical boundary from its own
lattice dynamics before using the kernel. The next particle-specific debt is
the FLM07 trefoil action/sublattice calculation: it must select the boundary
without particle masses or the target ratio. With locking disabled, the quick
regression gives `J3/J1=2.6375`, within `0.36%` of the sealed `2.6471`.
