# PPT17 Amendment 01 — `n` Is a Rotation Count

> **Date:** 2026-08-14. **Trigger:** author clarification after the first run.  
> **Status:** prospective amendment; the original result remains recorded in
> the assessment history and is not treated as evidence for this route.

The symbol `n` in the supplied circulation statement means an unknown number
of rotations executed at the proton-surface phase speed, approximately
`1.83c`. It does **not** mean `n` independent rotational coordinates.

Consequently, the original dimensional expression `d=1+2+n` is withdrawn.
Repeated traversal of one rotational coordinate does not add dimensions.

## Corrected phase-lock route

Let:

- `s=6` be the independently established compound-seat recurrence;
- `β=v_phase/c=1/k_proton_surface`;
- one seat interval be the time in which the local lattice relay at `c`
  completes one reference rotation on the same path;
- `N_raw=sβ` be the trefoil's demanded rotations per complete six-seat cycle;
- `N_lock` be the integer rotation count required for exact orientation
  recurrence;
- `N_surplus=N_lock-s` be the rotations demanded beyond lattice relay.

The instrument must calculate `β` from `laws.hpp` before opening the mass ratio.
It may accept the nearest integer phase lock only when it is unique within the
pre-registered capture interval `|N_raw-N_lock|<1/4` turn. The quarter-turn
gate is geometric and stricter than mere nearest-integer rounding.

The candidate exponent is `N_surplus`, not a dimension count.

## Gates

1. `N_lock` must be uniquely selected from `sβ` without using `6π⁵` or the
   measured mass ratio.
2. `N_surplus` must equal five.
3. The speed implied by exact lock, `β_lock=N_lock/s`, must agree with the
   engine phase speed to within `0.25%`.
4. Passing gates 1–3 supplies a native integer home for the exponent five.
5. It still does not prove that each surplus rotation multiplies displaced
   volume by `π`, nor that six seat contributions add without overlap. Those
   require a wake-measure map.

