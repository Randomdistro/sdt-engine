# FD08 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `FD08_VERDICT.md`,
> `FD08_DERIVATION.md`, `fd08_results.txt` deleted 2026-07-26 (git-recoverable).
> Tool: `fd08_bernoulli_budget.cpp`, g++ 15.2 -O2, exit **0**. Output:
> `fd08_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** The ρgz head is required to arrive via g = v_surf²/R (no G/M — R0); tool prints "No
G/M" and no GM appears in the chain. R0–R5 inherited.

## What the direct run measured

- **C1/C2 (core):** Bernoulli as the streamline integral of the FD01 balance — a budget
  partition (directed head vs static push on one ledger, the continuum image of Law V), with the
  trade sign **forced** negative (dP/dv = −ρv). PASS.
- **C3:** Venturi and Pitot recovered exactly; Pitot inversion returns the input airspeed.
- **C4:** compressible corner (1+(γ−1)/2·M²)^(γ/(γ−1)) → incompressible limit ratio → 1.0 to
  1e-8 as M→0; budget bounded at v→c. One measured input (γ). PASS.
- **C5:** struck — see below.

## Correction this verdict applies

**C5 is struck as a test.** The streamtube check *sets* P(s) = B − ½ρv² − ρgz and then verifies
B(s) = B — the invariant is written in and read back out; machine-precision agreement is
guaranteed by construction. What C5 legitimately provides is an exportable pressure field for
FD07/FD09, not evidence.

## Verdict

- **Prompt completion: B** (five phases run; C5 reclassified as construction, not gate).
- **Physics class: CONVERGENCE (Class C).** Bernoulli/Venturi/Pitot/compressible-corner
  reproduced term-for-term as a Law-V budget partition with the sign forced — shared closed form
  with the textbook invariant, so it cannot discriminate; SDT's origin is its own (one movement
  ledger). CALIBRATED(0); γ measured-input for the compressible part only.
- **Recovery:** n/a · **Cascade root:** none.
