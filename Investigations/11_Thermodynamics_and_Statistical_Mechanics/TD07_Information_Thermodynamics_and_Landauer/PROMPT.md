# TD07 — Information Thermodynamics and Landauer

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

Landauer's principle says erasing one bit dissipates at least `k_BT ln2` of heat, and Maxwell's demon
must obey it. The gap: derive the Landauer bound and close the demon **on the relay lattice** — show
that information is physical because a bit *is* a relay configuration, and erasing it dumps organised
throughput as disordered heat.

## SDT mechanism & hypotheses

A bit is a distinguishable two-state relay configuration — a small set of microstates `W=2`. Erasing
it forces both logical states into one (`W:2→1`), which by [[TD01]]'s `S=k_B ln W` *destroys*
`k_B ln2` of configurational entropy; that throughput cannot vanish (relay conserves throughput) so it
is expelled as disordered heat into the bath at `T`, costing `k_BT ln2`. The demon is not a loophole:
sorting requires measuring (writing a relay record) and resetting that record is itself an erasure.

- **H1 (Landauer = forced microstate merge):** irreversible logic merges relay microstates; the
  minimum heat is `k_BT ln2` per bit erased — derived from TD01 counting + TD02's `k_BT`.
- **H2 (demon pays relay):** the demon's memory is a physical relay register; to sort indefinitely it
  must reset, paying `k_BT ln2` per cleared record — exactly offsetting the work it extracts. No net
  Second-Law violation (closes [[TD01]] H4).
- **H3 (reversible computation is free):** a logically reversible relay operation maps microstates
  one-to-one (`W` unchanged), so `ΔS=0` and it can in principle cost no heat — recovering Bennett.

## Strategy

1. **Bit erasure ledger.** *Goal:* `k_BT ln2` per bit. *Method:* on the TD01 toy lattice prepare a
   `W=2` register, force `W→1`, measure heat dumped to a relay bath. *Success:* dissipated heat
   `= k_BT ln2 ± 1%`; reversible (one-to-one) ops dump `≈0`.
2. **Maxwell's demon.** *Goal:* close the loophole. *Method:* simulate a demon sorting a relay gas
   into hot/cold halves while logging to a finite register; account for the reset cost. *Success:*
   `W_extracted − W_erase_cost ≤ 0`; the apparent gain vanishes exactly when the register reset is paid.
2b. **Szilard engine.** *Goal:* one-molecule cross-check. *Method:* run the Szilard cycle on the
   lattice. *Success:* `k_BT ln2` extracted per cycle equals the measurement+erase cost.
3. **Reversibility boundary.** *Goal:* map cost vs logical reversibility. *Method:* sweep a family of
   gates from fully irreversible to reversible. *Success:* heat cost `∝ ΔS = k_B Δ(ln W)`; zero at the
   reversible end (Bennett recovered).
4. **Audit.** *Goal:* confirm whitelist. *Method:* delete-test `k_B`. *Success:* every bound is
   `k_BT ×` pure number (`ln2`, etc.); no ensemble imported.

## Success criteria

- **PASS (Class A):** `k_BT ln2`/bit derived from TD01 counting, demon closed, reversible-compute free
  — only `k_B` whitelisted, zero fitted parameters.
- **QUALIFIED (Class C):** Landauer + demon native; reversible-limit cost within numerical noise.
  *(Expected.)*
- **PENDING (Class D):** erasure cost right but demon closure stays qualitative.
- **FAIL (Class F):** a relay demon extracts net work — a real Second-Law loophole exists.

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | erase = microstate merge | heat `=k_BT ln2`/bit ±1% | information not physical on lattice |
| T2 | demon pays reset | net extracted work ≤ 0 | a real perpetual-motion loophole exists |
| T3 | reversible logic free | `ΔS=0` ops dump `≈0` heat | reversibility gives no thermodynamic relief |

## Dependencies

**Upstream:** [[TD01]] (`S=k_B ln W`, arrow-of-time, H4 demon note), [[TD02]] (`k_BT` scale).
**Downstream:** computation-energetics / reversible-logic studies, quantum-info correspondence (the
"no wavefunction" route to information). **Related:** [[TD06]] (radiation bath that carries away the
erased heat), [[project_foundational_ontology_influx_monopole]] (throughput conservation forbids the
demon's free lunch — the same eliminative move).
