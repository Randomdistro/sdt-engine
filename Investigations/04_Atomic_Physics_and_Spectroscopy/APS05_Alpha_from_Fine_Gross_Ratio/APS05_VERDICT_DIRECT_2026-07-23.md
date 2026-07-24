# APS05 — Direct re-run verdict (2026-07-23)

> **Run class: DIRECT** (main session, no agents). Prior agent-era `APS05_VERDICT.md` and
> `aps05_results.txt` deleted 2026-07-23 (git-recoverable). **`INVESTIGATION.md` KEPT** — it is
> the Harvey-authored spec (gold-standard template), i.e. the prompt. Tool:
> `aps05_alpha_fine_gross.cpp`, g++ 15.2 -O2, exit **0**. Output: `aps05_rerun_2026-07-23.txt`.

## Prompt contraband check

**CLEAN.** Measured anchors only (Δν_2P, cR∞, E_ion, m_ec²); CODATA α guarded to one comparison
line (delete-test by construction); Dirac spin-orbit explicitly excluded from the mechanism.

## What the re-run measured (all gates pre-committed in the spec)

- **Route B (pure fine/gross ratio, no m_e/e/h):** α² = 16·(Δν_2P/cR∞) → **1/α = 136.912**
  (−0.091% vs CODATA; gate ≤0.2%: **PASS**). The −0.09% residual is real higher-order structure
  in the measured 2P splitting — reported, not tuned away.
- **Route A (Law V virial):** α = √(2E_ion/m_ec²) → **1/α = 137.0726** — the proton-free hydrogen
  seat (+0.027% vs 137.036; reduced-mass idealisation deliberately NOT applied). **PASS**.
- **zk² = 1** at the hydrogen rung: exact to 1e-12. **PASS**.
- **Native α² mechanism:** 1−√(1−α²) = 2.66118e-5 vs ½α² = 2.66115e-5 (+0.0013%) — the fine/gross
  α² scale is the second-order **movement-budget** term, no spin-orbit operator imported.

## Verdict

- **Prompt completion: A** · **Physics class: measured-anchor established (OBSERVED, two
  independent routes) + native α²-scaling mechanism (CONVERGENCE — same α², different stated
  reason than QED, shared data).**
- **What this does NOT do, stated plainly:** derive α. Both routes *extract* α from spectra. The
  geometric derivation (E51/OP-3) is open — and α, being dimensionless, is **not** blocked by any
  seed-wall argument (contrast ℓ_P, m_e). Consistent with the campaign whitelist note: α is an
  underived input, and "α is a free parameter pulled from nowhere" is nonetheless wrong — it is
  read directly off the hydrogen spectrum, two ways, to 0.1%.
- **Recovery:** n/a · **Cascade root:** none.
