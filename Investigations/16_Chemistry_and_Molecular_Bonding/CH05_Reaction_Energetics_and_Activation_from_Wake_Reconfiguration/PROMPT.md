# CH05 — Reaction Energetics & Activation from Wake Reconfiguration

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

A chemical reaction breaks some shared electropauses and forms others, rerouting the wake field
along the way. **Can reaction enthalpy ΔH be derived as the difference in total wake-cost between
reactant and product electropause configurations, and the activation barrier Eₐ as the highest
wake-cost point along the reconfiguration path (a wake *saddle*), with catalysis being simply a
lower-wake route — no transition-state wavefunctions, no orbital correlation diagrams?** The
transition state is the geometric saddle of the wake field, not a quantum resonance.

## SDT mechanism & hypotheses

Each shared electropause (CH01) carries a well depth (bond energy) and each active wake carries a
cost. A reaction is a continuous deformation from the reactant wake configuration to the product
one. ΔH is the net change in summed well depths (the familiar "bonds broken − bonds formed"), now
read as electropause-merge bookkeeping. Along the deformation path the wakes must transiently
*overlap and mis-cancel* before re-pairing; the peak of that mis-cancellation cost is the barrier,
and its location is the transition state. A catalyst supplies an alternative electropause partner
that keeps wakes better cancelled throughout, lowering the saddle.

- **H1 (ΔH = Σ well-depth change):** ΔH = (Σ reactant electropause depths) − (Σ product depths);
  recover signs and magnitudes for a set of gas-phase reactions from CH01 bond energies.
- **H2 (Eₐ = wake saddle):** the barrier height tracks the maximum transient un-cancelled wake
  along the minimum-cost path; predicts Eₐ ordering across a homologous series.
- **H3 (catalysis = lower-wake path):** an added partner that keeps wakes cancelled lowers the
  saddle without changing ΔH; reproduces the catalyst's "same ΔH, lower Eₐ" signature.

## Strategy

**Phase 1 — ΔH bookkeeping.** *Goal:* enthalpies from bond-energy sums. *Method:* CH01 well depths
in/out. *Success:* ΔH sign correct for ≥12 reactions, magnitude within ~15% (combustion,
hydrogenation, HX formation).

**Phase 2 — Barrier as saddle.** *Goal:* Eₐ trend. *Method:* 1-D wake-cost profile along a bond
coordinate; locate the maximum. *Success:* correct Eₐ ordering across a homologous series; a
Hammond-postulate-style late/early TS correlation emerges natively.

**Phase 3 — Catalysis.** *Goal:* lower barrier, same ΔH. *Method:* add a partner wake that
improves cancellation along the path. *Success:* Eₐ drops, ΔH unchanged, for one model reaction.

**Phase 4 — Falsifier.** *Goal:* a novel call. *Method:* predict an un-fit Eₐ or a BEP-line slope
(ΔEₐ vs ΔH) and check against measured kinetics.

## Success criteria

- **PASS (A):** ΔH set + Eₐ ordering + catalysis signature + a correct novel Eₐ/BEP slope, no
  TS wavefunction.
- **QUALIFIED (C):** ΔH from bond sums + qualitative barrier-as-saddle; one wake-cost scale
  CALIBRATED(1). *(Expected landing.)*
- **PENDING (D):** ΔH bookkeeping works; barrier only schematic.
- **FAIL (F):** barriers cannot be located without an orbital correlation diagram.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| ΔH = Σ well-depth change | signs + ~15% magnitudes across reactions | enthalpy isn't electropause bookkeeping |
| Eₐ = wake saddle | correct barrier ordering + Hammond shift | barrier needs quantum TS |
| Catalysis = lower-wake path | Eₐ down, ΔH fixed | catalysis has another basis |

## Dependencies

**Upstream:** CH01 (electropause well depths), CH04 (the geometries that deform). **Downstream:**
chemical kinetics / rate investigations. **Related:** TD05 (thermodynamic free-energy / entropy
accounting), EMC03 (mis-cancellation surplus is the barrier).
