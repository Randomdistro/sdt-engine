# NP08 — VERDICT: Triple-Alpha / Hoyle State from Geometric Packing

> **Author:** J. C. Harvey, Melbourne. **Run:** 2026-07-03. **Engine:** `sdt/laws.hpp` + `sdt/nuclear.hpp`.
> Tool: `np08_triple_alpha.cpp` (MSVC exit 0) → `np08_results.txt` (redirected stdout).

## Dual verdict header

| Axis | Grade | One-line |
|------|-------|----------|
| **Prompt completion** | **C** | Grammar and ledger phases executed exactly; the core Hoyle-energy phase honestly DEFERRED on the named NP17-PENDING dependency instead of being faked. |
| **Physics class** | **OPEN / DEFERRED** (plus one PREMISE-CORRECTION finding) | No knob-free route to 7.654 MeV exists until the tetrahedral-lock magnitude is paid; the prompt's own Be-8 premise contradicted the constitutional grammar and was corrected. |

## Key numbers

| Quantity | Value | Label |
|---|---|---|
| Be-8 grammar (Z=4, A=8) | **α + 2d + 0t** (n_d = 3·4−8−2 = 2) | EXACT — contradicts PROMPT's "2α + 0d" |
| C-12 grammar (Z=6, A=12) | α + 4d + 0t | EXACT (matches PROMPT) |
| Scaffold binding required, Be-8 | 23.755 MeV (11.88/d) | IDENTITY (measured BEs consumed) |
| Scaffold binding required, C-12 | 54.968 MeV (13.74/d) | IDENTITY |
| Q(3α→C-12) | 7.2747 MeV | IDENTITY check (PROMPT's 7.275 ✓) |
| Be-8 vs 2α | −0.0918 MeV (metastable against 2α) | IDENTITY |
| Point-Coulomb repulsion of α+4d closure (committed geometry: r_cv = R_He + D/2 = 2.657 fm) | 6.327 MeV | DERIVED (knob-free, repulsive side only) |
| Hoyle target 7.654 MeV | **DEFERRED** | dependency: NP17-PENDING tetrahedral-lock magnitude |
| The real Hoyle content | barrier = 7.654 − Q = **0.379 MeV** above 3α threshold | OWED |

## What is earned vs owed

**Earned:**
1. **A premise correction with teeth.** The PROMPT's SDT story ("Be-8 = 2α + 0d, unstable
   because no scaffold bonds") violates the constitutional grammar it cites: the formulas give
   Be-8 = α + 2d. The correct SDT reading of Be-8 instability is **packing competition**: the
   α+2d configuration is metastable against reassembly into 2α by 0.092 MeV — not "no bonds."
   The same comparison run at A=12 flips sign (α+4d beats 3α by 7.275 MeV), giving both decay
   directions with no sign choice. (Ledger-consistency: it consumes measured BEs and is
   labelled IDENTITY, but the *direction flip between A=8 and A=12* is a structural point the
   grammar gets right.)
2. **The honest shape of the Hoyle problem.** 7.654 MeV = Q (7.2747, an identity) + 0.379 MeV
   closure barrier. The only SDT-derivable content is the 0.379 MeV barrier; any "derivation
   of 7.654" that leans on Q is mostly re-quoting AME masses. Naming this prevents a future
   fake pass.
3. **The knob-free repulsion ledger** at the committed contact geometry (6.327 MeV) — the
   half of the closure energy that CAN be computed today, on the record for the successor.

**Owed (cascade root):**
- **NP17's tetrahedral-lock/occlusion magnitude** — the attractive shared-electron side for
  d↔α contacts (electron count and placement). Without it no signed closure energy exists,
  so the 20% gate on 7.654 was **not scored** (RUN_LOG decision rule; inventing electron
  placements was forbidden and not done).
- The 0.379 MeV closure barrier once the lock term exists — that is the falsifiable Hoyle
  prediction, and the Be-8 0.092 MeV margin is its sibling test at A=8.

## Success criteria scoring (PROMPT)

- [ ] Hoyle energy within 20% — **NOT SCORED → DEFERRED** (upstream dependency, pivot-table
  path taken; no fake number)
- [~] Be-8 instability explained by grammar — YES, but by **packing competition**, not the
  PROMPT's (grammar-violating) "unbonded 2α" story
- [x] C-12 grammar (α + 4d) confirmed as stable endpoint (downhill from 3α in the ledger)

## Stress-test self-audit

1. **Identity/circularity:** every number that consumes a measured BE is labelled IDENTITY in
   both tool output and this verdict; the only DERIVED number (6.327 MeV) uses engine lengths
   and αℏc only.
2. **Fished factors:** none; no attractive term was invented; the gate was not scored rather
   than widened.
3. **Dimensions:** MeV·fm / fm throughout; αℏc = 1.4400 MeV·fm from `coulomb_identity`.
4. **Cascade root:** NP17-PENDING (tetrahedral-lock magnitude) — the same root blocking the
   alpha's 28.3 MeV. NP08 cannot close before it; it is queued behind, not around, it.

## §D Seven questions (HUNTER_PROTOCOL, on the P2 DEFER)

1. **Why exactly?** No signed closure energy exists: the attractive (shared-electron) side of the α+4d configuration cannot be written knob-free — electron count/placement for d↔α contacts is unbuilt. Only the repulsive ledger (6.327 MeV) is computable.
2. **Recoverable?** Yes, in principle — nothing here is falsified; the phase is blocked, not broken.
3. **What did the target fail to account for?** The PROMPT assumed occlusion bond energies (NP09) that had already failed −97.3%, and mis-stated the Be-8 grammar (2α+0d vs the constitutional α+2d).
4. **Which premise erred?** Two: (i) "binding is scalar occlusion" (dead upstream), and (ii) "Be-8 has no scaffold" (contradicts n_d = 3Z−A−2 = 2). Corrected reading: Be-8 instability is packing *competition* (α+2d metastable against 2α by 0.092 MeV), not bond absence.
5. **What freedom corrects it?** The tetrahedral-lock magnitude + the d↔α shared-electron geometry (NP17's named import). With it, the 0.379 MeV closure barrier becomes computable.
6. **Native or knob?** Native in principle (geometry + αℏc); currently absent. Inventing electron placements to reach 7.654 would have been a knob — refused.
7. **Cascades?** Yes — same root as NP10 and NP17's alpha PENDING: the tetrahedral-lock magnitude. NP08 additionally isolates WHERE the real content is (0.379 MeV barrier; Q = 7.2747 is mass bookkeeping).

**Recovery grade: PARTIAL** (premise errors corrected, dependency named and quantified; the lock itself unpaid).

---

> **Prompt completion C · Physics class OPEN/DEFERRED (premise-correction EARNED; ledger IDENTITY-labelled) · Recovery PARTIAL · Cascade root: NP17-PENDING tetrahedral-lock magnitude (shared with NP10)**

*NP08 · executed 2026-07-03 · OPEN/DEFERRED · premise corrected, Hoyle content isolated (0.379 MeV), no fake pass.*
