# TD02 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `TD02_VERDICT.md`, `RUN_LOG.md`,
> `results.txt`, `td02.exe/.obj` deleted 2026-07-26 (git-recoverable). Tool:
> `td02_throughput_temperature.cpp`, g++ 15.2 -O2, exit **0**. Output:
> `td02_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** The at-risk import (Boltzmann factor lifted rather than counted) is named in ⓪.1 and
firewalled in the tool: no S(E−ε) expansion, no predefined T, no partition-function object
anywhere; β read off AFTER the counting (firewall printed, T4 NOT FIRED).

## What the direct run measured

- **P1:** β_budget vs β_count converge, worst gap 1.3e-4 (< 1e-3 gate), gap = 1/N discretisation.
- **P2:** equipartition ⟨e_i⟩ = ½k_B T per quadratic DoF, init-independent (concentrated vs
  uniform starts agree; kurtosis → 3.0 Maxwell–Boltzmann). c_v = 3/2 k_B flagged
  near-definitional — not sold as independent.
- **P3 (the core):** the exponential occupation is an **output** of native relay counting three
  ways — exact complement-count marginal (slope gap 0.52%, R² 0.999994), relay-exchange dynamics
  (5e7 ticks), and the Lagrange route — all landing on β = ln(1+N/E) from the P1 budget.
- **P4 delete test:** k_B enters only as the kelvin unit-bridge; no h, no Z, no ensemble object.
- **SDT-flavoured feature (live):** at ⟨j⟩ ~ 1 the kinetic and entropic temperatures separate —
  the discrete-cell freeze-out takes the Einstein form. Predicted, reported, not absorbed.

## Verdict

- **Prompt completion: A** · **Physics class: CONVERGENCE (Class C), native-origin route.** The
  number is Boltzmann's — shared form, cannot discriminate — but the route is SDT's own counting
  with the firewall proving nothing was lifted. The freeze-out separation (T_kin/T_ent < 1 at
  quantised throughput) is the SDT-distinct residue worth a measurement hunt.
- **Recovery:** n/a · **Cascade root:** none. Feeds TD03/TD06 their occupation honestly.
