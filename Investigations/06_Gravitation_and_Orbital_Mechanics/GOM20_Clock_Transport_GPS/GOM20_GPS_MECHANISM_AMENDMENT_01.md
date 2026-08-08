# GOM20 GPS Recovery Mechanism Amendment 01

**Recorded:** 2026-08-07  
**Origin:** model-author clarification during the audit.  
**Status:** required mechanism ingredients; not yet a numerical prediction.

## Required recovery order

For satellite clock-shift recovery, GOM20 must include the following ingredients
in the stated order:

1. Derive Earth `koppa` using the **observed polar radius**, not a mean or
   equatorial radius.
2. Form an exclusion contribution from baryon count and volume.
3. Include exclusion of the spation shell as a distinct contribution.
4. Apply the specified inverse-square radial fall-off.
5. Apply the movement-budget contribution.

## Non-negotiable definitions still required

This amendment supplies ingredients, not a complete equation. Before any GPS
number is calculated, the model must state:

- the source, epoch, uncertainty, and Earth reference surface for the polar
  radius and for every baryon-count and volume input;
- the dimensional definitions, normalization, signs, and reference radius of
  the baryon-volume and spation-shell exclusions;
- whether inverse-square fall-off applies to each contribution separately or
  to their combined field, and how it is regularized at the reference surface;
- the exact signed composition of exclusion, shell, depth, and movement-budget
  terms into `dτ_sat/dτ_ground`;
- the clock time scale and frame, satellite and ground state vectors, and the
  eccentric-orbit treatment.

No numerical value in this amendment is inferred from another theory. The
future comparison remains a direct comparison between this completed SDT
prediction and independently retained clock observations with uncertainty and
correction provenance.
