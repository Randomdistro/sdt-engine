# QM04 — Born Rule from Residence Density

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Why is probability the **square** of the amplitude? The Born rule `P(x) = |ψ(x)|²` is a *postulate*
in standard QM. SDT must instead **derive** the square. This investigation deepens QM01-H3: the
"amplitude" is the convergence-wake displacement field; its **energy density** goes as displacement²
(every elastic/relay medium stores energy ∝ strain²); and a vortex steered by the wake (least-
resistance, [[project_cq43_variable_closure]]) spends long-run time — its **residence/landing
density** — in proportion to that energy density. So `|amp|²` is the *count* of where vortices land,
and the square is **geometric, not axiomatic**.

## SDT mechanism & hypotheses

The wake is a real pressure/displacement field on the lattice. Two facts conspire: (1) the stored
energy density of a superposed displacement field is `½ K (A_a + A_b)²` — the square is just elastic
energy; (2) a vortex following the wake gradient settles preferentially where the wake delivers most
convergence, so its residence time ∝ energy density. Run many one-at-a-time vortices (QM01) and the
histogram **is** `|amp|²` because that is where they linger and land.

- **H1 (energy ∝ displacement²):** the relay medium stores energy ∝ strain² (Law I/III), so the
  superposed-wake intensity is `|A_a + A_b|²` natively — the cross-term gives interference.
- **H2 (residence ∝ energy density):** least-resistance steering makes long-run vortex residence
  time proportional to local wake energy density (an ergodic/equidistribution argument on the lattice).
- **H3 (no negative probabilities, normalisation):** total landings conserved (one vortex always
  lands somewhere) ⇒ normalisation; energy density ≥ 0 ⇒ P ≥ 0 — both native, not imposed.

## Strategy

**Phase 1 — Energy density of a superposed wake.** *Goal:* show intensity = `|A_a+A_b|²`. *Method:*
elastic energy of a summed displacement field on the lattice (Law I). *Success:* the square + cross
term derived from elastic energy, **not** asserted.

**Phase 2 — Residence ↔ energy density.** *Goal:* prove landing density ∝ energy density. *Method:*
simulate N steered vortices (QM01 engine); measure residence-time histogram vs wake energy density.
*Success:* histogram ∝ energy density to RMS <1% over N≳10⁴; the proportionality is the Born rule.

**Phase 3 — Normalisation & positivity.** *Goal:* recover ∑P=1, P≥0. *Method:* conservation of
vortex count + non-negativity of energy density. *Success:* both fall out with no extra axiom.

**Phase 4 — Cross-checks.** *Goal:* the square shows up elsewhere. *Method:* reuse in QM03 (`−2κd`
amplitude→intensity), QM01 fringe contrast, QM07 SG spot weights. *Success:* one square serves all.

## Success criteria

- **PASS (A):** residence ∝ |amp|² derived from elastic energy + equidistribution; <1%; zero fitted params.
- **QUALIFIED (C):** square shown for the wake energy density; residence∝energy argued but leans on one
  flagged ergodic assumption (expected landing).
- **PENDING (D):** energy² native but the residence-time link only heuristic/numerical.
- **FAIL (F):** the square cannot be obtained without re-importing the Born postulate. Report; debt stands.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 — square is elastic energy | intensity = ½K(A_a+A_b)² with interference cross-term | square is axiomatic, not geometric |
| T2 — residence ∝ energy density | landing histogram ∝ energy density, RMS <1% | Born rule not a residence count |
| T3 — normalisation native | ∑P=1, P≥0 from count-conservation + energy≥0 | needs imposed probability axiom |

## Dependencies

**Upstream:** QM01 (wake + one-at-a-time steering — the engine this deepens), Law I (relay energy).
**Downstream:** QM03 (the `−2`), QM05 (Bell uses the same residence/measurement count), QM07 spot weights.
**Related:** [[project_cq43_variable_closure]] (least-resistance steering), [[project_paradox_census]] (§8.2 #1).
