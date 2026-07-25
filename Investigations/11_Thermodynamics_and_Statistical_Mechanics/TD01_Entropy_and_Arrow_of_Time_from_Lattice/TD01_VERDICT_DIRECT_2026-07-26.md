# TD01 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `TD01_VERDICT.md` and `results.txt`
> deleted 2026-07-26 (git-recoverable). Tool: `td01_microstates.cpp`, g++ 15.2 -O2, exit **0**.
> Output: `td01_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** The prompt names its own load-bearing risk: the H-theorem analogue must come from
per-tick neighbour redistribution **without** importing Boltzmann's molecular-chaos assumption.

## What the direct run measured

S = k_B ln W computed by literal microstate counting on the toy relay lattice: monotone and
extensive in E across N = 4/8/12; Stirling cross-check 2.4%; 1/T = ∂S/∂E extracted.

## Verdict

- **Prompt completion: D — Phase 1 only.** The tool never implements Phases 2–3; **the
  H-theorem/arrow-of-time derivation — the falsifiable core the prompt itself identifies — has
  never been run.** TD02's hill-climb (ln W maximisation) partially covers the equilibrium end,
  but the monotone-approach claim from a non-equilibrium start, Stosszahlansatz-free, is
  untested.
- **Physics class: COMPUTED (toy consistency).** S = k_B ln W as a literal relay count is
  demonstrated, nothing more. The arrow of time remains **OPEN and owed** — the TD root's
  hardest and most valuable open item.
- **Recovery:** n/a · **Cascade root:** H-theorem from relay dynamics (feeds TD02–TD08's
  equilibrium assumption).
