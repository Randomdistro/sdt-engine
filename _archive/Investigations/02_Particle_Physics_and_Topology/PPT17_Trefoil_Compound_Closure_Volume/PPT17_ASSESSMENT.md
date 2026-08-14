# PPT17 Assessment — Trefoil Compound Closure and 6π⁵

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-08-14.  
> **Disposition:** WITHDRAWN — the phase-lock exponent route is not a volume
> derivation. Superseded by `CORRECTED_VOLUME_ROUTE.md`.

## Withdrawal

The inference `6×1.83≈11`, followed by `11−6=5`, supplies only a nearby integer.
It does not define a displaced-volume operator and does not justify raising
`π` to that integer. The route therefore does not test the stated mechanism
and must not be cited as support for `6π⁵`.

The recurrence enumeration below remains a valid kinematic observation, but
its attempted connection to the mass ratio is withdrawn.

## Result

The `(2,3)` trefoil returns after exactly six distinct compound phase states:

`(0,0) → (2,3) → (4,0) → (0,3) → (2,0) → (4,3) → (0,0)`.

Contrarotational parity also returns at the sixth step. Controls on `(1,1)`,
`(1,2)`, `(3,4)`, and `(4,5)` reproduce the coprime recurrence count
`lcm(p,q)=pq`. The factor six is therefore a native kinematic closure count,
not a number imported from the mass ratio.

## What this pays

The user's compound-circulation statement gives a concrete home to the `6`:
it is the number of distinct `(2,3)` phase seats traversed before the whole
orientation recurs. This is stronger than treating `6` merely as the written
product `2×3`.

It does **not yet** prove that displaced volume is six times a one-seat phase
volume. That further step requires the six swept regions to have equal measure
and to be disjoint, or requires a derived multiplicity rule that handles their
overlap. PPT17 did not assume either result.

## Amendment 01 — the exponent-five route

The author clarified that `n` is an unknown number of rotations executed at
the proton-surface phase speed, approximately `1.83c`. It is a traversal
count, not a count of independent dimensions. The original `d=3+n` reading is
therefore withdrawn.

Using the full-precision engine construction,

`k_surface = α⁻¹√(R_p/a_0) = 0.546431035395`

and hence

`β = v_phase/c = 1/k_surface = 1.830057107348`.

Across six compound seats, the demanded count is

`6β = 10.980342644088 rotations`.

Exact recurrence selects the unique nearby integer lock `N_lock=11`; its
residual is only `−0.019657` turn. The locked speed is `11/6 c =
1.833333c`, differing from the engine value by `−0.178703%`. Relative to the
six rotations the lattice can relay in the same six intervals, the locked
surplus is

`N_surplus = 11 − 6 = 5`.

This gives the exponent five a target-free mechanical candidate:

`six closure seats × five surplus rotations → 6π⁵`.

## Remaining qualification

Speed alone is a rate, not a rotation count. The calculation above uses a
same-path seat clock: one compound-seat interval is the time in which relay at
`c` completes one reference rotation. In general,

`n = v_phase Δt / L_rotation`,

so `Δt` and the rotation-path length must be fixed by the compound geometry.
Until the same-path seat clock is derived rather than chosen as normalization,
the five-surplus result is **conditional**.

It also remains necessary to derive why each surplus rotation contributes one
multiplicative factor `π` to displaced volume, and why the six seat measures
add without double-counting swept overlap. The phase lock supplies a plausible
integer origin for five; it does not yet supply the wake measure.

## Correspondence

- `6π⁵ = 1836.118108711688`
- measured `m_p/m_e = 1836.152673440001`
- signed residual: `−18.824539 ppm`

The numerical correspondence is carried by the corrected tube-volume route,
not by the withdrawn phase-lock route assessed above.

## Ledger disposition

- `m_p/m_e = V_disp,p/V_disp,e`: Law IV identity.
- six-seat `(2,3)` recurrence: **DERIVED**.
- phase-lock exponent route: **WITHDRAWN**.
- corrected point-electron tube → proton torus map: **RESOLVED CONSTRUCTION**.
- `V_disp,p/V_disp,e = 6π⁵`: **COMPUTED, shared-input; not independent prediction**.

## Superseding construction

See `CORRECTED_VOLUME_ROUTE.md`. The active mechanism conserves the
point-electron's finite-width 720-degree Bohr-closure tube volume into the W=3
torus at `R_p`; it does not use the phase-count argument.

