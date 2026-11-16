# CM07 — Verdict: Ferromagnetism as Aligned Vortex Wakes

**Author:** J. C. Harvey, Melbourne · **Runs:** 2026-07-04 (run 1 preserved in
`cm07_results_run1.txt`; run 2 after logged numeric ADJs in `cm07_results.txt`).
Tool `cm07_ferromagnetism.cpp` (MSVC `/std:c++20 /O2 /utf-8`).

## Headline

**Three Curie temperatures from one zero-fit formula, in native units, with zero magnetons:**

k_B·T_C = z · n_w · α·ℏ²/(2 m_e d²)

| | z | n_w [wakes/atom] | T_C pred [K] | T_C obs [K] | ratio |
|---|---|---|---|---|---|
| Fe | 8 | 2.22 | **930** | 1043 | 0.89 |
| Co | 12 | 1.72 | **1060** | 1388 | 0.76 |
| Ni | 12 | 0.606 | **378** | 627 | 0.60 |

Ordering Co > Fe > Ni exact; every magnitude inside the committed 2× gate; inputs are measured
crystallography (z, d), the measured aligned-wake count n_w, and derivation basis constants (α, ℏ, m_e).
CALIBRATED parameters: **zero.** The exchange is the cluster's shared confinement door
(ℏ²/2m_e d² — same door as CM01 v_pack and CM03 E_g) geared down by the handed-redirection
coupling α (NP17 precedent). All three predictions run LOW (0.60–0.89) — a signed, systematic
residual, not noise; logged as a generative lead (mean-field z·J is known to overstate the
disorder side, so a low J is partially masked — the honest read is the formula is ~25% soft).

**The units rule held absolutely:** magnetisation is an aligned-wake count per atom; the native
unit is the electron's own wake circulation κ_e = h/m_e. The word "magneton" appears nowhere in
tool or output except in this sentence as a negation. Flagged openly (RUN_LOG): the native
single-wake unit is numerically the same object the rival names its unit after — the rule's
content is the narration and the count, and the count is what the chain uses.

## Other phases

- **P1 sign: OPEN, as committed.** |J| is derived; the ferro-vs-antiferro seating criterion is
  not. Honest finding: naive rim-shear favours *contra*-rotation (that is CM01/NP17's pairing
  channel) — the co-rotation window needs the on-seat/off-seat balance, unbuilt. Cr/MnO enter as
  OBSERVED contrast only.
- **P3:** M(T) → 0 at T_C; effective β = 0.4993 (gate 0.5 ± 0.1). Run 1's β = 0.21 was a solver
  artefact (ADJ-1, bisection; gate untouched).
- **P4:** hysteresis toy — remanence 1.000, coercivity 0.80 (native handedness-field units),
  deterministic index-derived pinning. Run 1's flat loop was a toy-construction error (drive
  weaker than its own pinning; ADJ-2, no measured target involved).
- **Out-of-scope exhibit, declared pre-run:** Gd (4f, indirect exchange) fails at 7.9× — the
  direct-overlap scope boundary is real and shown, not hidden.

## §G mirror (the faith item, named)

The α gear-down is the one faith-item in this run. It was formed by NP17 analogy with rough
arithmetic sighted before commitment (disclosed in RUN_LOG) — so the 3d PASS is **evidence, not
proof**; the look-elsewhere duty stands. Standing falsifiers this formula must now survive
blind: MnBi (ferro, Mn-based), Cr (must NOT fit as ferro), fcc-Fe precipitates (nonmagnetic),
Heusler alloys. Any of these can kill it; none was sighted.

## FAILURE RECOVERY (§D — P1 sign channel OPEN)

1. **Why:** no computed quantity in the chain distinguishes co- from contra-rotation; magnitude
   only. 2. **Recoverable?** Yes — the discriminator must live in the on-site seating cost that
   blocks the pairing (contra) channel when inner-shell wakes already occupy the seat.
3. **Unaccounted:** seat occupancy of the partially-filled shell. 4. **Errored premise:** "the
   pair channel is always available" — Fe/Co/Ni are precisely where it is blocked.
5. **Freedom:** a seat-occupancy criterion (blocked pair-seat → co-rotation wins).
6. **Native?** NP17's seat grammar is the native home; criterion unbuilt — not a knob, a missing
   derivation. Re-open condition: NP17-style seat accounting for the 3d shell. 7. **Cascade:**
   links to CM01's "why exactly 2" exclusivity question (same seat grammar) — local root
   (seat-grammar closure), distinct from ROOT-A/B.

**Recovery grade: PARTIAL.**

---

> **Prompt completion B · Physics class CONVERGENCE (T_C chain zero-fit inside 2×; sign OPEN;
> α-gear = named faith item with standing falsifiers) · Recovery PARTIAL · Cascade root
> seat-grammar closure (shared with CM01 pair-exclusivity; NP17 owes it)**
