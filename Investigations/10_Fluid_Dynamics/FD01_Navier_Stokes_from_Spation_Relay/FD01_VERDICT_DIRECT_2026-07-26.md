# FD01 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `FD01_VERDICT.md`,
> `FD01_DERIVATION.md`, `fd01_results.txt` deleted 2026-07-26 (git-recoverable; June de-rerum-era
> provenance). Tool: `fd01_navier_stokes_relay.cpp`, g++ 15.2 -O2, exit **0**.
> Output: `fd01_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** NS/Euler/Stokes named as the CONVERGENCE target to reproduce, never an input (§9 note
is explicit). R0–R5 inherited; derivation basis-only; Chapman–Enskog/Taylor is mathematics, not a rival
axiom. One process gap: the prompt mandates a `RUN_LOG.md` pre-commit block — none exists in the
folder (agent-era run skipped it). The tool prints its R1 predictions before each comparison,
which covers the intent for this re-run.

## What the direct run measured (all match the agent-era recorded numbers)

| gate | committed | today | verdict |
|---|---|---|---|
| P1 conservation | machine precision | drift 0.000e+00; free-streaming 0 | PASS |
| P1/2 ν recovery (0.5·dσ²/dt vs w·dx²/dt) | <0.5% | 2.873e-10 | PASS |
| P3 ‖∇·v‖ ∝ Ma² | exponent 2.0 ± 0.1 | **2.000000** (6-point sweep) | PASS |
| P4a Stokes decay vs exp(−νk²t) | <1% | 0.0196% | PASS |
| P4b Euler limit (ν=0) | peak translates, physical diffusion gone | 100.0 cells = U·n·Δt/Δx | PASS |

Failed numeric checks: 0. Parameter ledger printed: relay fraction w ASSUMED (demo stand-in),
ν = w·dx²/dt an identity of the rule, **CALIBRATED(0)** — no fluid scale fitted.

## Verdict

- **Prompt completion: C-partial** — P1–P4 executed and gated; **P5 (FD01↔FD02 ν coefficient
  handshake) NOT RUN by the tool** — deferred to FD02/ROOT-SIM, so the one cross-investigation
  gate remains open.
- **Physics class: CONVERGENCE (Class C), re-earned direct.** The structure of every
  incompressible-NS term maps to a relay mechanism (Laplacian → ν∇², streaming → advection,
  count conservation → ∇·v=0 at O(Ma²)) and both textbook limits fall out of the same rule.
  Shared form = cannot discriminate; the reproduction banks as coherence of the lattice picture,
  not as a win over the rival. The number that would upgrade this — the ν coefficient from
  lattice geometry, CALIBRATED(0) — is the open prize (FD02/ROOT-SIM).
- **Recovery:** n/a · **Cascade root:** ν coefficient closure (shared with FD02 P1/C5).
