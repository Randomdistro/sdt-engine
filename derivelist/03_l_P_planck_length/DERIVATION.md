# ℓ_P — exact koppa–wake geometric closure

> Updated 2026-09-08 to distinguish the geometric derivation from numerical-check provenance.
> Primary record: FLM06, `FLM06_CLEARING_GEOMETRY_FLOOR.md` §3b.

## Relation and role

ℓ_P = √(ϟ·ƛ): the lattice floor is the geometric mean of a koppa and a wake.
The relation is exact and mass-independent: koppa scales with mass and the
corresponding wake inversely with mass, so their product is independent of mass.
The spation radius is ℓ_P/2.

In the proton construction, ƛ_p = R_p/(W+1), with W+1 = 4, giving
ℓ_P = √(ϟ_b·R_p/4). FLM06 describes the scale reduction from the borrowed pair
{ℏ, G} to an SDT-native length scale plus the topological integer. The exact
relation must be distinguished from finite-precision measurements: the recorded
proton-radius substitution differs from the stored reference by about 0.0098%.

## Numerical implementation

`closure_floor(koppa, wake)` computes the general geometric mean.
The current convenience check constructs `koppa_per_baryon` as
`stored_l_P²/proton_wake`, where `proton_wake = R_p/(W+1)` and W+1 = 4.
No ℏ, mass, G or speed enters this geometric bridge. Those inputs
return the stored reference by construction. This is a consistency check of
the bridge, not an independent numerical determination of the length.

## Clearing-route scope

FLM06's tested Clearing-subdivision candidates reached approximately 10³,
against the required approximately 10⁶¹. That particular route remains excluded.
Its failure is not a general impossibility theorem for the lattice length and
does not invalidate the koppa–wake geometric derivation.

## Status

**Geometric relation derived; SDT length scale supplied.** The engine retains
1.616255×10⁻³⁵ m as its numerical reference. A new independent numerical input
path must document its koppa and wake provenance separately from this relation.
