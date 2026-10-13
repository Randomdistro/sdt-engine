# FD10 — Direct re-run verdict (2026-07-26)

> **Run class: DIRECT** (main session, no agents). Agent-era `FD10_VERDICT.md`,
> `FD10_DERIVATION.md`, `fd10_results.txt` deleted 2026-07-26 (git-recoverable).
> Tool: `fd10_vortex_shedding_strouhal.cpp`, g++ 15.2 -O2, exit **0**. Output:
> `fd10_rerun_2026-07-26.txt`.

## Prompt contraband check

**CLEAN.** ⓪.1 asks for the plateau value "with no fitted shedding constant" — the honest answer
came back NO (one O(1) gear coefficient needed), and the tool says so. R0–R5 inherited.

## What the direct run measured

- **Native:** the two-sided (ℓ=2) periodic wake *exists* in the mechanism; f ∝ U/D scaling;
  low-Re St(Re) *rises* with the derived 1/Re form (right sign and curvature, Roshko RMS 1.5%
  on a calibrated form test); lock-in as CQ41/Adler entrainment — capture band widens with
  amplitude, brackets the measured ±5–15% at A/D ≈ 0.15.
- **Calibrated, labelled:** κ_clock = 0.450 (the one gear coefficient carrying the 0.205
  plateau value), B_eff (low-Re shape), k0 (lock-in stiffness). MEASURED-INPUT: D_eff/D,
  U_wake/U from FD06/Achenbach.

## Note this verdict adds

"11/11 checks passed" counts calibrated-form fits among the 11. The checks with unfitted
content are: the plateau's *existence and flatness*, the f ∝ U/D power, the low-Re *sign and
curvature*, and the lock-in *band structure*. The plateau *value* 0.205 is carried by
κ_clock = 0.45 and banks as nothing until that O(1) coefficient is derived from traction
geometry.

## Verdict

- **Prompt completion: A** (all phases, honest ledger printed).
- **Physics class: CONVERGENCE (Class C, CALIBRATED(1) for the value).** The order, the scaling,
  the low-Re rise, and lock-in are native; the plateau value awaits the gear-coefficient
  derivation (PPT06 traction geometry — populated failure class: it could come out ≠ 0.45).
- **Recovery:** n/a · **Cascade root:** κ_clock from traction geometry.
