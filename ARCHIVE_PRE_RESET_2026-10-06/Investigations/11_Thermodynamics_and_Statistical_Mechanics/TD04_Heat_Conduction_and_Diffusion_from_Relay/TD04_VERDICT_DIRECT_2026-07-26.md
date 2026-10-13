# TD04 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `TD04_VERDICT.md`, `RUN_LOG.md`,
> `results.txt`, `td04.exe/.obj` deleted 2026-07-26 (git-recoverable). Tool:
> `td04_relay_conduction.cpp`, g++ 15.2 -O2, exit **0** (exit reflects core gates only —
> stated in-output, fails graded here, not laundered). Output: `td04_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** ⓪.1 asks derived-or-borrowed honestly; the copper channel is explicitly refused
rather than borrowed (importing v_F, λ_e would be a borrow — the tool says so and defers).

## What the direct run measured

- **P1–P3 (core, PASS):** relay random walk → D = vλ/3 (1.05%); diffusion equation with
  Gaussian spread (kurtosis 3.0); Fourier slab flux with slip-length correction (0.34%);
  linearity; √T flux scaling in the fixed-λ lattice limit (FD02 caveat restated).
- **P4 (FIRED, standing):** argon k_pred factor **3.30** off measured, air **2.96** — both
  > 2× gate, both recorded as FAIL. Copper DEFERRED/OPEN (no native degenerate-carrier
  statistics — refusing the borrow is correct).
- **P5 (FIRED, standing):** Wiedemann–Franz — classical one-channel relay gives
  L = (3/2)(k_B/e)², ratio 2.19 from the measured Sommerfeld value. The π²/3 needs degenerate
  carrier statistics SDT has not derived. OPEN, grade D on the sub-claim.

## Verdict

- **Prompt completion: B** (all phases run; two falsifiers fired and left standing).
- **Physics class: CONVERGENCE (Class C) for the mechanism; FAIL standing on real-material
  magnitudes.** The relay random-walk structure of conduction is banked; the ~3× magnitude gap
  on real gases and the fired WF gate are the honest debts. The open root is one item: **native
  degenerate carrier statistics** (what an electron gas is in SDT terms) — it gates copper, the
  Lorenz number, and metals generally.
- **Recovery:** n/a · **Cascade root:** degenerate carrier statistics (links the electron
  economy thread in the nuclear phase).
