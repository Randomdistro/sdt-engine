# CH06 — Hydrogen Bonding & van der Waals from Residual Wake

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — whether the hydrogen bond and the van der Waals / London force can be derived as the *residual, fluctuating wake* that leaks outside a molecule's electropause — recovering the ~20 kJ/mol H-bond, the 1/r⁶ London scaling, and water's density-maximum-at-4 °C anomaly — with NO induced-dipole wavefunctions and NO orbital overlap.
2. **Why does it matter?** — the weak bond is the left-over wake the electropause did not fully cancel; it underpins condensed-matter cohesion and all of biochemistry downstream. It consumes CH01 (electropause), CH04 (geometry that sets residual directions), and CH03 (which wakes are near-cancelled).
3. **How will we find out?** — gated phases in §④: derive 1/r⁶ from correlated residual-wake fluctuation, the H-bond energy/geometry from a rim residual, water's turnover from network-vs-packing, and a novel H-bond ordering — native mechanism before any induced-dipole picture or rival.
4. **What would prove us wrong?** — §⑧ numeric triggers: dispersion needing induced dipoles (power ≠ 6), or the H-bond / water anomaly needing an orbital model.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The load-bearing derivation is getting the **1/r⁶ EXPONENT OUT of the correlated residual-wake
fluctuation geometry** — two fluctuating dipolar residuals whose correlation falls as 1/r⁶ — NOT
assuming the London 1/r⁶ form and fitting a coefficient. The same applies to the H-bond: its
energy and ordering must emerge from the rim-residual geometry, not from a tuned amplitude.

> **If 1/r⁶ is assumed rather than derived, or the H-bond energy only matches because the
> residual-wake amplitude was tuned to 20 kJ/mol, that is a fit — caps the grade at C.**

ONE residual-wake amplitude may be **CALIBRATED(1)** — declare it explicitly in `RUN_LOG.md`. But
the **SCALING** (the 1/r⁶ exponent, and the monotonic growth with molecular wake size) and the
H-bond **ORDERING** (Phase 4) must be *predicted*, not fit.

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

| Test | Predicted outcome | If FAIL (numeric kill trigger) |
|------|-------------------|--------------------------------|
| Firewall — 1/r⁶ must be DERIVED | exponent falls out of the correlation geometry, not assumed | 1/r⁶ assumed (form put in by hand) or only the coefficient is fit ⇒ tautology, grade capped at C, **NOT NATIVE** |
| London = residual fluctuation | 1/r⁶ derived, grows monotonically with wake size | derived power ≠ 6 (e.g. comes out 1/r⁴ or 1/r⁸) ⇒ dispersion needs induced dipoles, **KILL** |
| H-bond = rim residual | ~20 kJ/mol, near-linear O–H···O geometry | H-bond energy outside the 10–40 kJ/mol band, or geometry not near-linear ⇒ H-bond has another basis, **KILL** |
| Water anomaly | density max ~4 °C, open tetrahedral ice | no density turnover in 0–8 °C, or turnover off by >5 °C from 4 °C ⇒ anomaly needs an orbital model, **KILL** |

## Dependencies

**Upstream:** CH01 (electropause), CH04 (geometry that leaves residual directions), CH03 (which
wakes are nearly cancelled). **Downstream:** condensed-matter cohesion, biochemistry. **Related:**
EMC03 (residual surplus/deficit), the period-2 cancellation map
([[project_foundational_ontology_influx_monopole]]).
---

## Questions This Opens *(generative — log new ones in `CH06_VERDICT.md`)*

1. Is molecular polarisability *literally* the residual-wake size — does it fall straight out of the
   CH01 electropause extent, rather than being a borrowed parameter?
2. Does the residual-wake picture also give the Lennard-Jones repulsive wall (the 1/r¹²) from
   electropause overlap — one curve yielding both the attractive and repulsive terms?
3. Does H-bond cooperativity in water chains emerge from successive wake re-cancellation along the
   chain (non-additive strengthening)?
4. Does it predict the boiling-point anomalies (HF / H₂O / NH₃ vs their heavier analogues)
   quantitatively from residual-wake size, not just qualitatively?
5. Is the open ice-Ih structure the wake-cancellation tetrahedral fixed point — tying the H-bond
   network geometry directly back to CH04 geometry?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 derive 1/r⁶ exponent (not assumed) + monotonic growth with molecular wake size across noble gases/alkanes · P2 H-bond energy in 10–40 kJ/mol band, near-linear O–H···O, correct O–H···O vs N–H···N ordering · P3 water density turnover within a few °C of 4 °C + open ice qualitatively · P4 novel HF/H₂O/NH₃ H-bond ordering correct
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| Residual fluctuation gives wrong power (not 1/r⁶) | re-derive the correlation geometry of two leaked residuals | **OPEN** the dispersion law | assume 1/r⁶, fit coefficient, claim derived |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · assuming the London 1/r⁶ form then claiming NATIVE · tuning the residual-wake amplitude to hit 20 kJ/mol · invoking induced-dipole wavefunctions in any native chain.

---

*CH06 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
