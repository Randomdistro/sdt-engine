# TD07 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `TD07_VERDICT.md`, `RUN_LOG.md`,
> `results.txt`, `td07.exe/.obj` deleted 2026-07-26 (git-recoverable). Tool:
> `td07_landauer_relay.cpp`, g++ 15.2 -O2, exit **0**. Output: `td07_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** Landauer and the demon posed as literal consequences of TD01's counting +
throughput conservation. A category error (partial-erasure quantity is heat Q, not work W) was
caught pre-compile and logged as ADJ-0 with the gate value unchanged — the protocol working.

## What the direct run measured

- **P2 (demon closure):** extraction yields 7.019 ε, erase costs 7.519 ε — net **−0.4995 ε ≤ 0**
  exactly, at all tested speeds. The demon closes.
- **Lattice-flavoured residue (scoped, not oversold):** stepped protocols overpay by the
  integer-step overhead ~ε·[p(0)−p(Emax)] (~6.9% of kT ln2 at kT = 10.5 ε), vanishing as
  ε/kT → 0; a continuous protocol closes at exactly 0. Claim scoped to stepped protocols.
- **P3 (partial erasure):** Q = kT[ln2 − H(p)] to 0.03% across the sweep; reversible end → 0
  exactly (labelled trivial); swap/relabel gates cost 0 (near-definitional Bennett recovery,
  labelled).
- **P4 delete test:** every bound is (kT/ε) × pure number; k_B the only bridge.

## Verdict

- **Prompt completion: A** · **Physics class: CONVERGENCE (Class C), native-count route.**
  Landauer's bound and demon closure re-derived by literal relay counting with no ensemble
  object; the stepped-protocol overpayment is the SDT-flavoured, testable residue (single-bit
  erasure experiments at small kT/ε would see it).
- **Recovery:** n/a · **Cascade root:** none.
