# NP42 — ν(A) closure-reset test (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data; the packing sequencer is understood before grammar work. Rounds 1–6 and their correction blocks are kept below the line.

## 1. What is established (round 6, reset run 2026-10-10, `NP42_RESET_ASSESSMENT_2026-10-10.md`)
- **Hockey-stick break.** The ν(N*) break sits at **N\* ≈ 80, not at the N = 82 seal**, consistently in both systems:
  - U-235: 80.50, Δχ² ≤ 4 set 79.00–81.25;
  - U-233: 79.75, set 78.75–80.50.
- **82 is excluded** in both (Δχ²(82) = 13.1 and 27.9); the null at 80 is inside both sets.
- **G6 not met: G1** for "break at the seal".
- **Validations:** a planted break was recovered exactly; complementary-fragment Z balance was 0.18.
- **U-233** has χ²/dof = 24.8: the hockey-stick form does not describe its floor region.

## 2. Origin assessment, and what it points to
1. **Emission timing cannot rescue 82.** Post-emission N lies lower still.
2. **Z assignment bias of about 2 is unlikely** (V2 balance 0.18).
3. **The sequencer's shell schedule (`laws.hpp` shell canon; NSEQ18):**

   … → D20 → **70** → **T12** → **82** → …

   - Between N = 70 and 82, the 12-seat triton belt T12 fills.
   - **N\* ≈ 80 is the point where T12 is one triton pair short of closure.**
   - That is a native reading. It must be **registered before** the next round's data are re-fitted, together with its own prediction for the other belts. If the floor ends one pair short of each belt's closure, the analogous breaks sit at **N\* ≈ 48** (T10 → 50) and **N\* ≈ 124** (T14 → 126).
   - Fission fragments do not populate N ≈ 48 or 124 densely enough to test those ends in U-235/U-233 alone. The data route (other fissioning systems, ²⁵²Cf spontaneous) must be named first.
4. **Context, not evidence.** The live sequencer's own wrong-sign binding steps cluster at N = 64–72 (cascade 2026-10-11): the region where its contraction switches as T12 opens. Same structural region; no mechanism links the two yet.

## 3. Round 7 (to register before any re-fit)
- **H7:** the ν floor ends one triton pair before a belt's closure (N_b = closure − 2).
- **Tests:** U-235 and U-233 as before (now post-seen at 80, so a consistency check only), plus a **held-out system** with fragment yields on disk or fetched with provenance, scanned once.
- **Second form:** for U-233, a shape test of a form other than the hockey stick, registered beforehand (χ²/dof 24.8 says the form is wrong there).

## 4. Prohibitions
- No re-scoring of round 6.
- No sliding the closure to fit.
- Grammar counts are not evidence (NP24).

---

## Rounds 1–6 (kept as written)

# NP42 — ν(A) closure-reset test (pre-registered)

**Author:** J. C. Harvey, Melbourne. **Opened:** 2026-10-03 (direct execution, no agents).
**Placement:** NP42 is proposed (id free; not previously used). Move or rename only on the Operator's word.
**Origin:** the "unseated nucleons" thread (`Audits/atomica_n82_fission_stocktake.md` §4: flay leaves six unseated neutrons); cache in `Datasets/nuclear/neutron_multiplicity/` (its README: "unseated nucleons has no precise definition on file").

## ① What we do not know
Whether prompt-neutron multiplicity ν(A) of a fragment tracks how many neutrons sit above the last closed neutron shell, so that ν resets at a closure.

## ② Definition (pinned here, before any fit)
For a fragment of mass A from a fissioning system (Z_p, A_p), Z_f = A·Z_p/A_p (fragment Z/A equal to the parent Z/A; no Z polarisation), N = A − Z_f.
**Unseated count** u(N) = N − c(N), with c(N) the largest member of `laws::nuclear::magic_numbers` {2,8,20,28,50,82,126} with c ≤ N. Read once from `laws.hpp`; no other input and **no fitted parameter**.
Compound systems: U-235(n,f) Z_p=92, A_p=236; U-233(n,f) 92, 234; Cf-252(sf) 98, 252.

## ③ Hypothesis and gates (all fixed now)
H: ν rises with u inside each shell segment and the sawtooth resets at N = 82.
- **G1 (primary, U-235 TABLE):** Spearman ρ(ν, u) over fragments with N in [82, 126) ≥ +0.8.
- **G2 (reset location, whole range, one pass):** fit continuous two-segment-linear ν(N) with break N_b scanned 70..100 in steps of 1 over N (continuous in N via linear interpolation of A→N). Gate: the best break lies within ±2 of N = 82 **and** N = 82 ranks in the top 3 of the 31 breaks by residual sum of squares. The scan is the look-elsewhere census; the rank is reported whatever it is.
- **G3 (held-out):** G1 and G2 repeated unchanged on U-233 (same mechanism) and Cf-252 (different mechanism; digitized CURVE, lower fidelity, so ρ gate only ≥ +0.7).
- **Null:** the same two gates with u built from a shifted closure set (82→80,84,86; 50→48,52) to show how specific 82 is. Results are reported, not gated.
Passing G1–G3 on all three = ν shape consistent with a closure reset (class COMPUTED, zero parameters, **target-exposed**: the sawtooth minimum near A≈130 is literature knowledge held before the analysis). It does not test a magnitude: a ν scale needs one multiplicative parameter and would be CALIBRATED(1).

## ④ Instrument validation (before use)
V1 u(N) hand-checked on N = 50, 81, 82, 83, 125, 126, 127. V2 break-scan recovers a planted break at N=88 on synthetic data with noise at the measured σ. V3 Spearman against a library-free reimplementation.

## ⑤ Limitations declared in advance
Equal-Z/A ignores Z polarisation (~±0.5 Z, hence ±0.5 N); ν(A) is vs pre-neutron mass; the two segments below and above 82 mix light and heavy fragments since only N matters (a light fragment at N=82 does not occur for these systems). Spearman on a monotone-by-construction u cannot by itself separate "reset" from "smooth rise": G2 is the discriminating gate.

## ⑥ Pivot table
| Outcome | Next step |
|---|---|
| G1 pass, G2 fail (break elsewhere) | assess where the break sits, hypothesise (polarisation, odd-even, triton belts B(n)), new dated round |
| G1 fail | assess sign and range; consider Z-side closure (Z=50) as an alternative u; new round |
| G2 pass but null shifts also pass | resolution too coarse; report as non-discriminating |
| All pass | seal the Phase-2 prediction for a fourth system before access (e.g. Pu-239) |

## Round 2 pre-registration (2026-10-03, written AFTER round 1 results were seen)
Round 1: G1 passed on all three systems, but the same ρ passes for shifted closures (80/84/86), so G1 does not discriminate; G2 failed on all three (best break N_b = 70 / 90 / 88; rank of 82 = 14, 15, 17 of 31). Assessment: a single hinge over the whole pooled N range cannot represent a curve whose light fragments (N below ~66) sit on a separate ν branch; the failure is at least partly the model shape I pinned, not only the hypothesis.
Round 2 (target-exposed: round 1 data seen) restricts to the heavy branch, fragments with N ≥ 70, and asks the V-shape question the sawtooth implies: fit ν(N) = a + b·(N−N_b) for N<N_b and a + c·(N−N_b) for N≥N_b, continuous at N_b with free slopes b, c and break N_b scanned 74..92.
- **G2′:** best N_b within ±2 of 82, 82 in the top 3 of 19, and fitted slopes b ≤ 0 < c. Same null shifts reported. Applied to all three systems unchanged; no gate edits after this block.

## Round 3 pre-registration (2026-10-04, written after rounds 1–2; target-exposed)
Hypothesis: the vertex sits at the Z = 50 proton closure (`magic_numbers` member), not at N = 82. With equal-Z/A, Z_f = 50 occurs at A = 50·A_p/Z_p, i.e. N_pred = 50·(A_p − Z_p)/Z_p: U-235 78.26, U-233 77.22, Cf-252 78.57 (computed from the compound system only; no data enter).
- **G3a:** heavy-branch V-shape fit exactly as round 2 (N ≥ 70, breaks 74..92, 19 values). Best break within ±1.5 of N_pred and rank of the nearest integer break to N_pred ≤ 3, slopes b ≤ 0 < c, on all three systems.
- **Null (reported, not gated):** the same test with Z = 48, 52 (N_pred shifts by about ∓/± 1.5–1.6) and with N = 82; if shifted nulls pass equally the test is non-discriminating at this resolution.
- Limitation: equal-Z/A, pre-neutron A, Z polarisation (~±0.5 Z ↔ ~±0.8 N here) is larger than half the Z 50 vs 48/52 spacing, so a pass is expected to be weak evidence; stated before the run.

## Round 4 pre-registration (2026-10-05, EXPLORATORY: same data as rounds 1–3)
Operator's request to retry after the round 3 near miss (U-235 rank 4, gate ≤ 3). The round 3 gate stays as recorded and stays missed. Rank is a brittle statistic (one RSS step), so round 4 replaces it with a profile set; this is a statistic change after seeing the data, so a pass here is **not confirmatory**.
- Model: round 2 V-shape, same fit range and break scan (N ≥ 70, breaks 74..92). σ² = RSS_min/(n−4). Break set S = {N_b : (RSS(N_b) − RSS_min)/σ² ≤ 1} (about a 68% set).
- **G4:** the nearest integer to N_pred(Z=50) lies in S on all three systems, and slopes b ≤ 0 < c at the best break.
- Reported nulls: Z=48, Z=52, N=82 with the same set.
- Confirmatory step (not run): measured Z(A) for these systems, or a fourth system (Pu-239 n_th,f) sealed before access.

## Round 5 pre-registration (2026-10-05) — measured Z per A (replaces equal-Z/A)
Rounds 2–4 conclusions about N = 82 were withdrawn (see NP42_ASSESSMENT.md correction). Round 5 uses Wahl's evaluated independent fractional yields FI(Z|A) for U-235(n_th,f) (`Datasets/nuclear/fission_z_distribution/`), the only system with Z yields in hand. Exposure: the ν̄ data were seen in rounds 1–4; the Z data are new.
- **Z assignment:** for each ν̄(A*) point (A* pre-neutron), A_post = A* − ν̄; ⟨Z⟩(A) = Σ Z·FI / Σ FI at integer A from Wahl; ⟨Z⟩ linearly interpolated to A_post. Z is unchanged by neutron emission. **N\* = A* − ⟨Z⟩** (pre-emission neutron number). Also reported: mode-Z version.
- **Fit:** V-shape as round 2 (N\* ≥ 70), break N_b scanned 74.00–92.00 in steps of 0.25. Weighted least squares using the file's ERR-S where present (missing errors replaced by the median of present errors; stated). σ² from the fit (χ²/dof scaled).
- **G5 (U-235 only):** (i) best break within ±1.0 of 82; (ii) 82.0 lies inside the Δχ² ≤ 4 set; (iii) slopes b ≤ 0 < c.
- Reported nulls with identical statistic: break targets 80, 84, and N* of Z = 50 at A* = 130 with measured Z.
- A pass is target-exposed on ν̄ (hence not a blind confirmation). A fail is read against the stated limitations: Wahl FI at A ≈ 128–134 mix experiment and model; ν̄ is flat near the floor; single system.

## Round 6 pre-registration (2026-10-05) — the repo's own hypothesis, the repo's own yield data
Source of the hypothesis (already in the repo, not mine): `NP35_Flay_Not_Split` F3 — the outermost sealed triton shell T12 (N = 82) survives as the heavy remnant (A_H_pre 133–135 predicted, matched on 8 fissioners); `NP25_Fission_Geometry_Invariant` — prompt neutrons are stripped tritons, ν × (t → d + n), the jacket beyond the seal. NP35 records "ν is not predicted"; this round supplies the missing ν shape. Id note: NP37 is already queued in `NP35_CHAIN.md` for flay depth; this folder was renamed NP42. Round 5 used a Wahl-table copy; the repo already holds IAEA independent yields, which are used from here on.
- **Model (hockey stick, the "sealed floor then stripped jacket" picture):** ν(N\*) = a + c·max(0, N\* − N_b), a and c free, break N_b scanned 74.00–92.00 step 0.25. Hypothesis: N_b = 82.
- **Z assignment:** ⟨Z⟩(A) from `Datasets/nuclear/IAEA_U235_independent_FY.csv` and `fission_yields/IAEA_233U_independent_FY.csv`, column `independent_thermal_fy`, ground-state rows (`daughter_level_idx` = 0), summed over Z at fixed post-neutron A, FI-weighted mean. A_post = A\* − ν̄, ⟨Z⟩ interpolated; N\* = A\* − ⟨Z⟩. Weighted LSQ with ERR-S (missing → median); errors scaled up if χ²/dof > 1.
- **G6 (both U-235 and U-233, N\* ≥ 70):** best N_b within ±1.0 of 82, 82.0 inside the Δχ² ≤ 4 set, c > 0. Nulls (reported): 80, 84.
- Exposure: ν̄ tables seen in rounds 1–5; the hockey-stick form was chosen after seeing that the V fit has a flat left arm, so the model shape is exploratory; the target N_b = 82 and the physical picture come from NP35/NP25. Cf-252 has no independent-yield file in the repo's list; not run.

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The "unseated nucleons" definition was invented in the folder, assigned neutron numbers by an equal-Z/A assumption that moves N by 1–3 units, and its first gate (G1) is monotone by construction and passes for shifted closures; rounds 2–4 were withdrawn.

**Correction:** Use the repo's NP35/NP25 hypothesis with measured Z yields (as round 6 did) and gate on the break location only.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
