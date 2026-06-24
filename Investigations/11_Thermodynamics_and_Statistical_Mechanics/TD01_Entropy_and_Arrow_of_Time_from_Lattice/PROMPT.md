# TD01 — Entropy and the Arrow of Time from Lattice Microstates

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

---

## 1 · Executive Summary

The relay lattice is **already discrete at ℓ_P** — so there is no continuum to coarse-grain and no
quantised-oscillator postulate needed (the same reason SDT gets Planck blackbody natively, SAR02–SAR02).
**Can entropy, temperature, the equipartition theorem, and the Second Law be derived as literal
counting of spation microstates, with the arrow of time emerging from the irreversibility of
convergence relay (throughput goes in faster than it spreads out)?** This grounds thermodynamics in
the lattice instead of importing Boltzmann's `S = k_B ln W` as an axiom. **We expect:** `S = k_B ln W`
falls out because the lattice literally *has* W discrete microstates to count; temperature is the
mean relay-throughput per spation degree of freedom; and the Second Law is the statement that
high-throughput (low-entropy) configurations relax toward the overwhelmingly more numerous
spread states — a one-way street set by the relay tick.

## 2 · Physical Context

Heat in SDT is **disordered convergence throughput** — relay activity that is not organised into a
vortex or a coherent wake. A hot body is a region where spations carry more random tick-to-tick
throughput; a cold body, less. Because the lattice is granular and finite-state, a macrostate
(temperature, pressure) corresponds to an astronomically large set `W` of micro-arrangements of
that throughput. The arrow of time is not assumed: each relay tick redistributes throughput toward
contact neighbours, and the number of spread configurations dwarfs the number of concentrated ones,
so the system walks (deterministically, per tick) into the big basin. This is **Boltzmann's H-theorem
made literal** on a real lattice — no Stosszahlansatz hand-wave, the mixing is the relay itself.

Variables: microstate count `W`; entropy `S = k_B ln W`; temperature `T` (mean throughput per DoF);
k_B (whitelisted measured constant); relay tick `t_P`; throughput quantum `ε = u₀ ℓ_P³` (Law I);
heat `Q` (disordered throughput transferred); the equipartition DoF count per spation.

## 3 · Theoretical Framework

Build on: Law I (`ε`, `P_conv`, throughput), Law IV (mass as organised throughput cost), Law V
(movement budget), FLM02/FLM05 (relay tick mechanics), SAR02–SAR02 (lattice mode counting → Planck,
Stefan–Boltzmann, Wien). **Whitelisted input:** `k_B` (it is the entropy↔throughput unit-bridge,
exactly as `e` is the charge unit-bridge — measured, not derived). **Forbidden:** ensembles imposed
as axioms, partition-function-as-postulate, Liouville/phase-space-continuum, Maxwell's demon as a
real loophole, "entropy = disorder" as hand-wave. The ideal-gas law and equipartition are *targets*.

Working hypotheses:
- **H1 (counting is literal):** `W` is a genuine integer count of relay microstates; `S = k_B ln W`
  is therefore a *definition that computes*, not an axiom.
- **H2 (temperature = throughput/DoF):** `k_B T` = mean disordered relay throughput per spation
  degree of freedom; equipartition `½k_B T` per quadratic DoF emerges from even throughput sharing.
- **H3 (Second Law = relay mixing):** per-tick neighbour redistribution monotonically increases `W`
  until the spread maximum; the H-theorem's monotonic functional is the relay entropy.
- **H4 (arrow = tick asymmetry):** convergence influx (the throughpole) injects organised throughput
  that the relay can only *disperse*, never spontaneously re-organise — the cosmological arrow and
  the thermodynamic arrow are the **same** relay asymmetry (ties to the cyclic-cosmology recharge,
  [[project_sdt_cyclic_cosmology]]).

## 4 · Investigation Strategy

**Phase 1 — Microstate counting on a toy lattice.** Enumerate `W(E,N)` for a small relay block at
fixed total throughput. *Success:* `ln W` extensive in N; `S` additive; recover `S = k_B ln W` exactly.

**Phase 2 — Temperature & equipartition.** Define `1/T = ∂S/∂E`; share throughput across DoF.
*Success:* `⟨E⟩ = ½k_B T` per quadratic DoF; ideal-gas `PV = N k_B T` from occlusion-pressure of a
relay gas (P from Law III momentum flux, no Boltzmann ensemble imposed).

**Phase 3 — Second Law / H-theorem.** Start the toy lattice in a low-`W` (concentrated) state; run
the deterministic per-tick redistribution; track `S(t)`. *Success:* `S` monotone non-decreasing to
the spread maximum; relaxation time scales with block size; fluctuations ∝ 1/√N.

**Phase 4 — Arrow-of-time memo.** Connect the tick asymmetry to the cosmological influx; argue the
two arrows are one. *Success:* a clean statement (no perpetual-motion loophole); Maxwell's demon
costs more relay throughput to sort than it saves (Landauer `k_B T ln2` per bit erased, native).

## 5 · Success Criteria

- ✅ **PASS (Class A):** S=k_B ln W, equipartition, PV=Nk_BT, and monotone S(t) all derived from
  relay counting with only `k_B` whitelisted; zero fitted parameters.
- ✅ **QUALIFIED (Class C):** the above with one flagged coarse-graining step; Landauer recovered to
  order unity. (Expected landing.)
- ⚠️ **PENDING (Class D):** counting works but the arrow-of-time link to cosmology stays qualitative.
- ❌ **FAIL (Class F):** entropy cannot be made a literal lattice count without importing an ensemble.

## 6 · Outputs

1. `TD01_DERIVATION.md` — counting → S, T, equipartition, ideal gas, H-theorem, Landauer.
2. `td01_microstates.cpp` — standalone C++20: toy-lattice `W(E,N)`, S(t) relaxation, equipartition check.
3. `td01_results.txt` — S vs ln W; ⟨E⟩/DoF vs ½k_BT; S(t) monotone trace; Landauer bit cost.
4. `TD01_VERDICT.md` — A/C/D/F with the arrow-of-time disposition.

## 7 · Dependencies & References

**Upstream:** FLM02/FLM05 (relay ticks), SAR02–SAR02 (lattice mode counting), Law I/IV. **Downstream:**
stellar thermodynamics (09_Stellar), heat death vs cyclic recharge ([[project_sdt_cyclic_cosmology]]),
condensed-matter phase transitions (12). **Related:** FD-suite (the lattice as a fluid), Landauer/
information-thermodynamics correspondence.

## 8 · Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | W is a literal count | S=k_B ln W exact on toy lattice | entropy not reducible to counting |
| T2 | T = throughput/DoF | equipartition ½k_BT per DoF | temperature has another basis |
| T3 | Second Law = relay mixing | S(t) monotone to spread max | mixing not native / needs Stosszahl |
| T4 | demon obeys Landauer | erase costs ≥ k_BT ln2 | a real perpetual-motion loophole exists |

## 9 · Implementation Notes

Double precision and log-space for `ln W!` (use Stirling for large N; exact enumerate small N to
validate Stirling). Keep blocks small enough to enumerate but large enough that 1/√N fluctuations
are visible. Plot: (a) S vs ln W (slope = k_B); (b) S(t) relaxation for three initial concentrations;
(c) ⟨E⟩/DoF vs T. Do not impose a Boltzmann distribution — it must emerge from equal-weight
microstate counting under the throughput constraint.
