# CH06 — Hydrogen Bonding & van der Waals from Residual Wake

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Primary bonds (CH01–CH02) merge or transfer whole electropauses. But molecules also stick weakly
without sharing electropauses at all. **Can the hydrogen bond and the van der Waals / London force
be derived as the *residual, fluctuating wake* that leaks outside a molecule's electropause —
recovering the ~20 kJ/mol H-bond, the 1/r⁶ London scaling, and water's density-maximum-at-4 °C
anomaly — with no induced-dipole wavefunctions and no orbital overlap?** The weak bond is the
left-over wake the electropause did not fully cancel.

## SDT mechanism & hypotheses

A closed-shell molecule has nearly all wakes paired and silent (CH03), but cancellation is never
perfect: a small residual wake leaks past the electropause. Two such residuals can transiently
co-align so their leaked wakes partly cancel across the gap — a weak, distance-sensitive
attraction (London). Where a proton sits at the rim of an electropause (O–H, N–H, F–H), the
residual is large and directional: the hydrogen bond, an order of magnitude stronger than London
but far weaker than a shared electropause. Water's anomalies follow from the directional H-bond
network competing with close-packing as wakes try to stay cancelled.

- **H1 (London = residual-wake cancellation):** the fluctuating residual gives an attraction
  scaling as 1/r⁶ and growing with molecular wake size (polarisability analogue), no induced
  dipole invoked.
- **H2 (H-bond = rim residual):** a proton at the electropause rim leaks a strong directional
  wake; predict the ~20 kJ/mol energy and the near-linear O–H···O geometry.
- **H3 (water anomalies):** the directional H-bond network vs close packing yields a density
  maximum near 4 °C and the open ice structure from wake-cancellation geometry.

## Strategy

**Phase 1 — London scaling.** *Goal:* the dispersion law. *Method:* correlated residual-wake
fluctuation between two closed shells. *Success:* derive 1/r⁶ (not assumed) and a monotonic trend
with molecular wake size across the noble gases / alkanes.

**Phase 2 — Hydrogen bond.** *Goal:* energy + geometry. *Method:* rim-residual wake of O–H into a
lone wake of a neighbour. *Success:* H-bond energy 10–40 kJ/mol band; near-linear donor–acceptor;
correct relative O–H···O vs N–H···N strength.

**Phase 3 — Water anomalies.** *Goal:* the 4 °C maximum. *Method:* network vs packing competition.
*Success:* density turnover near 4 °C and open tetrahedral ice from wake-cancellation geometry
(qualitative + the turnover temperature within a few °C).

**Phase 4 — Falsifier.** *Goal:* a novel call. *Method:* predict an un-fit H-bond strength
(HF vs H₂O vs NH₃ ordering) or a boiling-point anomaly from residual-wake size.

## Success criteria

- **PASS (A):** 1/r⁶ derived + H-bond energy/geometry + water turnover, plus a correct novel
  H-bond ordering, no induced-dipole wavefunction.
- **QUALIFIED (C):** 1/r⁶ + H-bond band recovered; one residual-wake amplitude CALIBRATED(1);
  water qualitative. *(Expected landing.)*
- **PENDING (D):** London scaling shown; H-bond only order-of-magnitude.
- **FAIL (F):** weak bonding requires fluctuating-dipole quantum theory.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| London = residual fluctuation | 1/r⁶ derived, grows with wake size | dispersion needs induced dipoles |
| H-bond = rim residual | ~20 kJ/mol, near-linear geometry | H-bond has another basis |
| Water anomaly | density max ~4 °C, open ice | anomaly needs orbital model |

## Dependencies

**Upstream:** CH01 (electropause), CH04 (geometry that leaves residual directions), CH03 (which
wakes are nearly cancelled). **Downstream:** condensed-matter cohesion, biochemistry. **Related:**
EMC03 (residual surplus/deficit), the period-2 cancellation map
([[project_foundational_ontology_influx_monopole]]).
