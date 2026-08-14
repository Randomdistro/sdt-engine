# GOM20 — Clock Transport and GPS

> **Status:** PENDING_MECHANISM  
> **Empirical status:** UNADJUDICATED

## Current canonical basis

The active depth-clock rate is `depth_closure::clock_rate(z) = 1 - z`, as
applied and consumed by GOM22 and the benchmark suite. The public square-root
helper `law_V::gravitational_time_dilation` has no compiled consumer and is a
source-hygiene debt; it is not the GOM20 clock law.

## Result

GOM20 does not yet provide a dimensionally closed equation for
`d tau_sat / d tau_ground`. Existing material names five ingredients—polar
Earth koppa, baryon-volume exclusion, spation-shell exclusion, inverse-square
fall-off, and the Law-V movement budget—but does not define their signs,
normalisations, dimensional composition, reference surface, or coupling to the
active linear clock rate.

The model is therefore `NON_IDENTIFIABLE_BEFORE_PREDICTION`. This is a
mechanism debt, not an empirical exclusion. No SDT parameter was estimated and
no observational residual was adjudicated.

## Required reopening condition

Before any data comparison, supply one signed equation and symbol table fixing:

1. units, signs, normalisations, and reference radius for every term;
2. polar-radius source, epoch, uncertainty, and koppa mapping;
3. baryon-volume and shell-exclusion functions;
4. the exact inverse-square operation and regularisation;
5. movement-budget velocity components;
6. coordinate time, frames, ground and satellite state conventions; and
7. all free constants with a no-retuning rule.

Then freeze primary clock-comparison data and pre-register blind mean-rate and
periodic-orbit tests.
