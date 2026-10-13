# RUN_LOG — CH03 Periodic Table & Valence from Shell Wake-Cancellation

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-05. **Status:** pre-commit written BEFORE coding.

## Grounding correction (Harvey directive)

Stands on NP17 bones: shared electrons = the binding; wakes are the residual signatures of
electropause seats. Machinery only. HUNTER §G honoured: the O₂/N₂ gate is a **measured magnetic
susceptibility number**, not any rival's story; no orbital/subshell machinery may enter the chain.
FARMER refinement 4 noted up front: electron seats may be **sequential (a tour), not static** —
this run's static-seat model is therefore explicitly premise-classed (static-seat class), and
every FAIL below carries that re-open condition.

## Faith ledger (§G.1)

1. **Period capacities {2, 8, 8} for Z=1–18 are taken as the one CALIBRATED(1) symmetry** (allowed
   and declared per PROMPT §⓪⁺). They are NOT derived from wake-slot combinatorics here.
2. Seat geometry for the 8-capacity period: 8 static slots at cube corners, antipodal pair =
   fore/aft cancelled (silent), singly-occupied diagonal = active wake. Named as faith (rendering,
   not settled structure — FARMER: "who knows what arrangement the units maintain").
3. Pairwise seat interaction 1/d (Law III occlusion energy form) for the native filling test.

## Models committed (before run)

- **M0 (seeded tally):** active(n) = min(n, 2S−n) per period of capacity 2S. This is arithmetic on
  the calibrated capacities — if it matches the table it is at best a re-labelling (firewall: cap C).
- **M1 (native filling attempt):** exact enumeration of all C(8,n) occupations of the cube-corner
  seats, energy = Σ 1/d over occupied pairs, min-energy config selected; active count = number of
  body diagonals with exactly one occupied end. PREDICTION REGISTERED: if M1's min-energy filling
  does not reproduce the M0 pattern, the tally is seeded, not derived → grade caps at C.
- **M2 (diatomic pairing map):** residual actives after fore/aft pairing across the bond:
  residual = |a_A − a_B| for actives a_A, a_B (all mutually pairable wakes pair). Gate: O₂ measured
  PARAMAGNETIC (χ_mol > 0, two unpaired signatures), N₂ measured diamagnetic.

## Pre-Run Commitments — CH03

- Prompt completion target: C (expected landing per PROMPT)
- Physics class hoped: CONVERGENCE; honest LINGUISTIC/OPEN accepted if M1 fails
- CALIBRATED budget: 1 (period capacities {2,8,8}) — declared above
- Phase thresholds: P1 standard valence correct for ALL Z=1–18 · P2 He/Ne/Ar zero-active ·
  P3 O₂ paramagnetic AND N₂ diamagnetic out of the pairing map · P4 novel para/dia call (NO from
  residual count) correct
- Forbidden: widening tolerances; seeding M1 from the known configuration; subshell machinery.

## Run record

- Tool: `ch03_valence_wakes.py` (pure-geometry enumeration; no physical constants needed)
- Output: `results.txt` = verbatim stdout.
