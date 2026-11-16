# NP42 — ν(A) closure-reset test: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0.

**Read:**
- PROMPT.md, rounds 1–6 with their stated round-1 to round-5 outcomes, which the prompt itself carries
- the 2026-10-05 correction (rerun round 6)
- Datasets/nuclear/neutron_multiplicity/README.md

**Not opened:** NP42_ASSESSMENT.md, 
p42_round6.py, 
p42_results_round6.txt, the np37_* files, RUN_LOG.md.

## Registration
Round 6 exactly as written in the prompt (2026-10-05), with a fresh instrument:
- **Model:** ν(N*) = a + c·max(0, N* − N_b), weighted LSQ, N_b scanned 74.00–92.00 in steps of 0.25, fit range N* ≥ 70.
- **Z assignment:** ⟨Z⟩(A_post) from IAEA independent thermal yields (ground-state rows), FI-weighted. A_post = A* − ν̄, with ⟨Z⟩ interpolated linearly. N* = A* − ⟨Z⟩.
- **Errors:** ERR-S; missing values replaced by the median; errors scaled by √(χ²/dof) at the best break if χ²/dof > 1.
- **G6 (U-235 and U-233):** best N_b within ±1.0 of 82, 82.0 inside the Δχ² ≤ 4 set, and c > 0. Nulls (reported): 80, 84.

**Validations:**
- V1: the scan recovers a planted break at N_b = 85.0 on synthetic data (noise at the U-235 median error).
- V2: complementary-fragment Z balance. For U-235, mean |⟨Z⟩(A) + ⟨Z⟩(234 − A) − 92| over A = 85–110 must be < 0.5. Total ν̄ ≈ 2.4, so 236 − 2.4 ≈ 234.

**Exposure:** declared in the prompt (ν̄ seen in rounds 1–5; the hockey-stick shape is exploratory). A pass here is not a blind confirmation.

## Run and results
(below)
Instrument: `np42_reset_1.py`; output in `np42_reset_1_results.txt`. Single pass.
- V1 met (planted break 85.00 recovered at 85.00).
- V2 met (complementary Z balance 0.175).

| system | points (N* ≥ 70) | best N_b | Δχ² ≤ 4 set | a | c | χ²/dof | Δχ²(82) | null 80 in set | null 84 in set | G6 |
|---|---|---|---|---|---|---|---|---|---|---|
| U-235 | 29 | **80.50** | 79.00–81.25 | 0.633 | 0.0749 | 1.92 | 13.07 | yes | no | FAIL |
| U-233 | 45 | **79.75** | 78.75–80.50 | 0.642 | 0.0771 | 24.81 | 27.94 | yes | no | FAIL |

**G6 NOT MET (G1 as registered).** Both systems put the hockey-stick break at N* ≈ 80, two units below the N = 82 seal, and 82 is excluded on both. The shift is the same in both systems, so it is a systematic offset, not noise.

**Origin assessment** (hypotheses for a dated next round; nothing re-scored):
1. **N* is pre-emission.** A post-emission N would sit lower still (N* − ν), moving the break further from 82. So emission timing does not rescue it.
2. **Z assignment by FI-weighted mean ⟨Z⟩**, without polarisation per fragment. A bias of about 2 N units at A ≈ 130 would need ⟨Z⟩ off by about 2, which V2's balance (0.18) makes unlikely.
3. **The picture:** the floor may end where the T12 shell is still one triton pair short (82 − 2), not at the completed seal. That would be a native reading to pre-register (82 − 2 = one t → d + n pair, NP25), not a rescue of this round.
4. **U-233's χ²/dof = 24.8:** the hockey stick does not describe the U-233 shape near the floor. The errors are scaled, and the break set is still tight.

**Grade:** G1 for "break at the N = 82 seal" as registered. A consistent break at N* ≈ 80 in two systems is recorded as a finding for the next round.

## Comparison with the archived record
Deferred.
