# TD06 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `TD06_VERDICT.md`, `RUN_LOG.md`,
> `results.txt`, `td06.exe/.obj` deleted 2026-07-26 (git-recoverable). Tool:
> `td06_lattice_blackbody.cpp`, g++ 15.2 -O2, exit **0**. Output: `td06_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** ⓪.1 names the at-risk import (Bose denominator lifted); the tool counts it instead
(P1b) and the one genuine assertion is disclosed in P5.

## What the direct run measured

- **P1a:** mode density counted, 0.003% vs 8πν²/c³; the walled-cavity boundary term isolated as
  a clean 1/R correction.
- **P1b:** occupation from ln W hill-climb from a non-Bose start → Bose form to 0.006% RMS; the
  geometric series **counted** (multiple quanta per mode), not lifted.
- **P2–P4:** Planck curve 0.0014%; Stefan–Boltzmann T-exponent 4.0000, σ_SI to **4.4 ppm** of
  measured a_rad; Wien x* = 4.965114, b to 0.008%.
- **P5 (the honest ceiling):** the ℓ_P mode cutoff does ZERO numerical work at physical
  temperatures — finiteness is carried by ε = hν quantisation, **Planck's postulate carried into
  SDT as the Law-I bridge, ASSERTED not derived.** Disclosed in-tool.

## Verdict

- **Prompt completion: A** · **Physics class: CONVERGENCE (Class C, capped).** The whole
  blackbody suite reproduced from counted lattice modes + TD02's natively-counted occupation —
  with the cap honestly placed: the hν granularity itself is asserted via the Law-I bridge.
  Deriving ε = hν from relay mechanics is the open root (it is the same open item as the
  emission-quantum question in the APS ladder).
- **Recovery:** n/a · **Cascade root:** ε = hν from the relay tick (Law-I bridge derivation).
