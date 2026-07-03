# NP10 — VERDICT: Alpha Binding from Tetrahedral Geometry (NP17 premise)

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-03. **Engine:** `sdt/laws.hpp` only.
> Tool: `np10_alpha_binding.cpp` (MSVC exit 0) → `np10_results.txt` (redirected stdout).
> Premise: NP09 occlusion route dead (−97.3%); mechanism = NP17 shared-electron Coulomb well.

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **B** | All committed gates scored, no geometry fished, expected failure confirmed and *quantified* rather than papered over. |
| **Physics class** | **OPEN** (one new structural constraint EARNED; G2 re-verification; G4 DEGENERATE) | Pure shared-electron electrostatics under-binds the alpha 6.35×; the ratio test shows the missing lock term is coordination-dependent, not a common factor. |

## Numbers (all gates committed in RUN_LOG before coding)

| Gate | Result | Label |
|---|---|---|
| G1: B(α) from NP17-exact config (a = 2R_p) | 4.454 MeV vs 28.296 → **−84.3% FAIL → OPEN** | lock remainder R_lock = 23.842 MeV (84.3% of total) |
| G1b: D-spaced variant | 3.817 MeV (−86.5%) | same conclusion |
| G2: R_He = 2R_p = 1.6828 fm vs 1.6755 | **+0.44% PASS (1% blind)** | pre-existing engine result (`nuclear::R_He_predicted`, class C-flagged) — re-verified, NOT sold as new |
| G3: B_α/B_t = 3.336 | predictions 1.041 / 0.892 / 0.980 → **ALL FAIL (−69 to −73%)** | **the informative result** — see below |
| G4: μ_α = 0 | consistent via paired cancellation | DEGENERATE (declared pre-run) |
| G5: edge for 28.296 MeV electrostatically | 0.265 fm < 2R_p | UNPHYSICAL → remainder is real, not a spacing choice (reproduces NP17 inverse) |

## What is earned vs owed

**Earned — a new constraint on the lock term (the actual product of this run):**
The implied boost factors on pure shared-electron electrostatics are
**deuteron ×1.01 → triton ×1.98 → alpha ×6.35** (d: NP17's 2.200 vs 2.224; t: chain
p–e–p–e–p at D; α: NP17-exact tetrahedron). Because ALL committed ratio pairings fail at
~−70%, the missing "tetrahedral lock" is **NOT a common multiplicative factor** on the
electrostatic well — it **grows super-linearly with interleave/coordination number**
(≈1, 2, 6.35 for 1, 2, 3+ interlocked units). Any future lock derivation that produces a
flat per-bond boost is pre-falsified by this run. This sharpens NP17's "PENDING" from
"a remainder exists" to "a remainder with this scaling exists."

**Also earned:** the honest kill of the PROMPT's own Step-2 arithmetic (occlusion bond sums)
— executed under the corrected premise instead, per the 2026-07-03 note; and the G5
unphysical-inversion result showing no spacing choice rescues electrostatics.

**Owed (cascade root):**
- The tetrahedral-lock mechanism and magnitude (NP17-PENDING) — now with a quantitative
  target curve: it must supply 0.02, 4.2, 23.8 MeV for d, t, α respectively (and, via NP08,
  close the 0.379 MeV Hoyle barrier at A=12).
- The prompt's B(He-3) hierarchy row was not scored: it needs the electron-count asymmetry
  (He-3 = 3p + 1e, alternate grammar) whose geometry is part of the same pending import.

## Success criteria scoring (PROMPT §3)

- [ ] Total binding within 20% of 28.296 — **FAIL → OPEN** (−84.3%; remainder quantified)
- [x] R_He within 1% — PASS (+0.44%; pre-existing engine result re-verified)
- [~] μ_α = 0 explained — consistent but DEGENERATE
- [ ] B_α/B_triton ratio reproduced — **FAIL** (and the failure is the finding: lock is
  coordination-dependent)
- [x] Bond-energy consistency with the deuteron — yes at the deuteron (×1.01) and it is
  precisely the *breakdown* of that consistency at t and α that was measured here

## Stress-test self-audit

1. **Identity/circularity:** all energies computed from engine lengths + αℏc; measured
   28.296/8.482 (engine `measured::B_alpha`, `B_triton`) used as OBSERVED targets only.
2. **Fished factors:** zero. Geometries (4 configs) were committed in RUN_LOG before any
   energy was computed; no additional configurations were tried after seeing numbers.
3. **Dimensions:** MeV·fm/fm throughout; charges integer; no borrowed units.
4. **Cascade root:** NP17-PENDING lock magnitude. NP10 does not close it; it fences it in
   (scaling ≈ superlinear in interlock count, unreachable by spacing or common factor).

## §D Seven questions (HUNTER_PROTOCOL, on the G1/G3 FAILs)

1. **Why exactly?** Magnitude: pure shared-electron electrostatics gives 4.454 MeV vs 28.296 (−84.3%); and the α/t ratio fails at ~−70% in all committed pairings — the deficit is not uniform.
2. **Recoverable?** Not by spacing (G5: required edge 0.265 fm < 2R_p, unphysical) and not by a common factor (G3). Recovery requires a qualitatively new term, already named by NP17.
3. **What did the target fail to account for?** Whatever binds interlocked trefoils beyond point-charge electrostatics — the interlock/occlusion ("lock") contribution that grows with coordination.
4. **Which premise erred?** "Alpha binding = sum of pairwise shared-electron Coulomb wells at physical spacing." True for the deuteron (×1.01), increasingly false with interleave count (t ×1.98, α ×6.35).
5. **What freedom corrects it?** The tetrahedral-lock term. This run adds its constraint curve: it must supply ≈0.02 / 4.2 / 23.8 MeV for d / t / α — superlinear in interlock number.
6. **Native or knob?** Must be native (geometry of interleaved trefoils + occlusion); any flat per-bond boost is now pre-falsified by G3. No knob was taken here.
7. **Cascades?** Yes — the same NP17-PENDING root as NP08 (and the heavy-isotope curve). G2 (R_He) and G4 (μ_α) do not cascade; they stand.

**Recovery grade: PARTIAL** (failure fenced with a quantitative target curve; the lock mechanism itself unpaid).

---

> **Prompt completion B · Physics class OPEN (G1 FAIL quantified; G3 constraint EARNED; G2 re-verified; G4 DEGENERATE) · Recovery PARTIAL · Cascade root: NP17-PENDING tetrahedral-lock magnitude (shared with NP08)**

*NP10 · executed 2026-07-03 · honest OPEN · the lock term is now a quantified, falsifiable target.*
