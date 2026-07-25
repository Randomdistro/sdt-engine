# FD09 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `FD09_VERDICT.md`,
> `FD09_DERIVATION.md`, `fd09_results.txt` deleted 2026-07-26 (git-recoverable).
> Tool: `fd09_drag_occlusion.cpp`, g++ 15.2 -O2, exit **0**. Output:
> `fd09_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** The sharp test is named up front (⓪.1: can the 6π be DERIVED from sphere relay
geometry rather than adopted?). Weight enters via g = v_surf²/R — no G, no M. R0–R5 inherited.

## What the direct run measured

- Drag *form* C_D·½ρv²·A native (occlusion shadow, front-minus-wake); Stokes *scaling* μRv
  native (relay diffusion); **6π prefactor adopted — labelled CORRELATION, not derived.**
- C_D(Re) composite: plateau 0.461 in [0.4,0.5]; crisis located within 2× of 3e5; post-crisis
  C_D in [0.07,0.15]. Curve is a labelled reproduction target (Schlichting/Achenbach),
  CALIBRATED(1) crisis-shape scale.
- Terminal velocities, regime self-selected: 3 mm water drop 8.64 m/s vs Gunn–Kinzer 8.0–8.1
  (~7%, inside the 15% falsifier); 1 mm drop 3.97 vs 4.0–4.5. PASS.

## Note this verdict adds

**The sharp test was not attempted.** The prompt's F1 — derive the sphere prefactor from relay
geometry and see whether it lands at 6π — is the one place FD09 can win or lose, and the tool
neither derived it nor fired the falsifier. It stays **OPEN**, explicitly. Everything banked
here is form + scaling + honest reproduction.

## Verdict

- **Prompt completion: B** (phases run and labelled; F1's derivation branch unexecuted).
- **Physics class: CONVERGENCE (Class C).** One occlusion law giving the drag *form* in both
  regimes, with the Stokes prefactor and the C_D(Re) curve reproduced-not-derived and said so.
  CALIBRATED(1).
- **Recovery:** n/a · **Cascade root:** sphere relay-geometry prefactor (6π target, populated
  failure class — build the tool).
