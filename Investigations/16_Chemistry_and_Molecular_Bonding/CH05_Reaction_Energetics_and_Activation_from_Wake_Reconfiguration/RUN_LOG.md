# RUN_LOG — CH05 Reaction Energetics & Activation from Wake Reconfiguration

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-05. **Status:** pre-commit written BEFORE coding.

## Grounding

NP17 frame: a bond = a shared-electron well; a reaction = re-seating shared electrons. The prompt's
own firewall is accepted in full: ΔH bond-sum bookkeeping is the near-IDENTITY (CONVERGENCE at
most); the gradeable content is whether a BARRIER emerges from the committed machinery. CH01's
native well is dead (electropause branch); all well parameters below are MEASURED anchors, declared.

## Faith ledger (§G.1)

1. Mean bond enthalpies (kJ/mol, CRC/NIST-class tables) and measured ΔH° — OBSERVED anchors.
2. H₂ pair-well for the saddle model: Morse with measured De=4.747 eV, Re=0.7414 Å, a=1.9426 Å⁻¹
   (OBSERVED anchors — declared; NOT an SDT-derived well; that debt belongs to the NP17 chain).
3. Wake-budget premise: the middle atom's single shared-electron engagement splits b + b' = 1
   between its two partners (Law-V-style budget conservation). Named as faith.

## Models committed (before run)

- **P1 (ΔH bookkeeping):** ΔH = Σ(bonds broken) − Σ(bonds formed), 12 gas-phase reactions.
  Gate: sign correct ≥12/12; magnitude within 15% for ≥9/12 (small-ΔH reactions H₂+I₂ excepted
  from the % gate by |ΔH|<20 kJ/mol rule, committed now). Label: CONVERGENCE/IDENTITY per firewall.
- **P2 (barrier = wake saddle), model M-SADDLE:** collinear H+H₂ exchange. U(r₁,r₂) =
  max over b∈[0,1] of binding b·V(r₁)+(1−b)·V(r₂) (V = the Morse well; U = −max = min(V₁,V₂)),
  plus, in variant M-SADDLE+, the end-end pair term V(r₁+r₂). PREDICTION REGISTERED: report the
  maximum energy along the minimum-energy exchange path vs measured Eₐ(H+H₂) ≈ 40 kJ/mol
  (0.42 eV). Gate: a saddle EMERGES with Eₐ in [10,120] kJ/mol. If no saddle (Eₐ≈0) or wrong sign
  (bound H₃): honest FAIL/OPEN — no cost term may be invented post-hoc to create one.
- **P3 (catalysis):** DEFER if P2 fails (depends on the saddle existing).
- **P4 (novel BEP):** DEFER if P2 fails.

## Pre-Run Commitments — CH05

- Prompt completion target: D (PENDING landing is the honest expectation given CH01 is dead)
- Physics class hoped: CONVERGENCE (P1); OPEN accepted for P2
- CALIBRATED budget: 0 (nothing fitted; the allowed wake-cost scale is NOT used — using it to
  manufacture a barrier would be a FISHED RECOVERY)
- Forbidden: reading Eₐ off measurement; inventing a mis-cancellation cost term with a tuned
  magnitude; retro-widening.

## Run record

- Tool: `ch05_reaction_energetics.py`
- Output: `results.txt` = verbatim stdout.
