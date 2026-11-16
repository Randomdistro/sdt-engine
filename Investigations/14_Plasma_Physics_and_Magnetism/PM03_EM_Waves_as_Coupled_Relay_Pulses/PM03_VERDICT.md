> ⚠️ **SUPERSEDED — contradicts current PROMPT.md** (PASS on a static Courant=1.0 with no wave evolution, which the prompt forbids); DO NOT TRUST; pending honest re-run. — flagged 2026-06-29

# PM03 — Verdict: EM Waves as Coupled Relay Pulses

**Classification: CLASS C (CONVERGENCE on c identity).**
**Author:** James Christopher Tyndall, Melbourne · Tool: `pm03_em_waves.cpp`.

## Hypothesis

c = ℓ_P/t_P is identical to 1/√(μ₀ε₀); EM mode is transverse (c) vs compression (c/√3).

## Key numbers

- |c − c_EM|/c: **<10⁻⁹** — PASS
- Courant stability c·Δt/Δx = **1.0** — PASS

Full PM01⊕PM02 wave equation: **PENDING**.

**Sign-off: PASS, Class C.**

---

## Audit correction (2026-10-05)

The "SUPERSEDED — DO NOT TRUST" banner above stands for the old PASS (a static Courant number of 1.0 and the identity |c − c_EM|/c, which are true by construction and are no longer scored). The test the prompt requires was run: `pm03_evolved_pulse.cpp` evolves a transverse relay displacement on a lattice of spacing l_P with tick C·l_P/c for 1000 steps (no electric or magnetic field as a primitive; speeds reported in SI from l_P and c) and tracks the peak (`pm03_evolved_results_2026-10-05.txt`): C = 1.00 speed/c = 1.000000, C = 0.90 0.999941, C = 0.50 0.999766 (gate < 1%: PASS), and C = 1.05 blows up (the Courant limit as the relay-rate bound). This confirms that a nearest-neighbour relay update propagates a pulse at c with a rate bound; it is a property of the second-order stencil, class CONVERGENCE. Phase 2 (separating transverse from longitudinal speeds) was not run and stays OPEN. The prior hand-reported 2.17e-14 identity row is withdrawn from the tally.
