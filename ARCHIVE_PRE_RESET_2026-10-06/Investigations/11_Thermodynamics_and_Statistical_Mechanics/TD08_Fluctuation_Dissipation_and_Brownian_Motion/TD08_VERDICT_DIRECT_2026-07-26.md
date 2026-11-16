# TD08 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `TD08_VERDICT.md`, `RUN_LOG.md`,
> `results.txt`, `td08.exe/.obj` deleted 2026-07-26 (git-recoverable). Tool:
> `td08_fdt_brownian.cpp`, g++ 15.2 -O2, exit **0**. Output: `td08_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** The structural claim is the right one: noise and friction as two faces of ONE relay
statistic — and the tool enforces it by construction: **no noise-amplitude parameter exists in
the tool**; kicks and drag come from the same collision stream.

## What the direct run measured

- **P0:** bath equipartition ⟨MV²⟩/k_BT = 0.998/0.999 at T = 1 and 4.
- **P2 (Einstein relation):** D/(μk_BT) = **1.0041** and **1.0009** at the two temperatures —
  as an OUTPUT, with no knob that could have set it.
- **P3 (FDT):** zero-frequency force-noise S_F(0)/2γk_BT = 0.986 within the declared O(m/M)
  budget; white at low frequency, roll-off at the collision rate.
- **P4:** Stokes–Einstein closure vs FD02 **DEFERRED as declared** — the 1D toy has no 6πηR and
  FD02's η carries a documented ×1.44; "producing a closure number here would be fabrication."
  OPEN, correctly.
- The prompt's τ ~ t_P claim is classed OPEN, not asserted (untestable in the toy).

## Verdict

- **Prompt completion: A** · **Physics class: CONVERGENCE (Class C), structurally strong.** The
  Einstein relation and FDT emerge from one collision stream with no noise normalisation
  anywhere in the tool — the "two faces, one bath" claim is enforced by the tool's own
  architecture, which is the cleanest kind of firewall. Open: the 3-D Stokes–Einstein closure
  (blocked on FD02's dense-liquid λ_mfp gap — same root).
- **Recovery:** n/a · **Cascade root:** FD02 λ_mfp closure.
