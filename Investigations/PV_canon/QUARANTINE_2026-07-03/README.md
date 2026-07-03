# QUARANTINE — 2026-07-03

> **Status: RETRACTED — do not cite anything in this folder.**
> Quarantined by HUNTER (adversarial audit), authorized by J. C. Harvey, 2026-07-03.

## What is quarantined

- `SDT_Complete_Canonical_Compendium.md` (46.5 MB, 772,164 lines)
- `canonical_outline.html` (same lineage)

## Why

The HUNTER scour (2026-07-02) and the follow-up deep scan (2026-07-03) established:

1. **~97% of the compendium is auto-generated filler** — 34,757 stub sections reading
   "This section synthesizes the content implied by `<path>`" (content *implied*, i.e.
   the source was never read). The bulk exists to make the "canon" look exhaustive;
   the bulk is itself the deception.
2. **Every checkable number in the authored ~1.2% is an identity-pass or a
   reverse-engineered fit.** Representative kills:
   - μ_n "SDT Prediction −1.91304272 μ_N … 0.002% ✓" — the CODATA value fed in as
     g_n/2 and quoted back verbatim (target-in / target-out).
   - Deuteron "B_D = 2.2246 MeV … Exact match ✓" — the coefficient k = 4.240962 MeV/sr
     is fitted FROM the measured 2.2246, then the answer is declared predicted.
   - Alpha "18 circulating neutrinos × 1.57 MeV = 28.3 MeV, 0.05% ✓" — 1.57 = 28.3/18,
     reverse-engineered; the live engine holds alpha binding honestly PENDING (NP17).
   - "One equation. All nuclear physics. Zero free parameters." — false (alpha PENDING,
     neutron barrier OPEN).
   - "Axiom 1.4 … three constituent toroidal vortices (quarks)" — a prohibited primitive
     raised to an axiom; a partial Jul-2 patch retracted one instance and **missed the
     one at former line 6382**, demonstrating per-line remediation is unmaintainable.
3. **It is an orphaned build artifact of the external companion repo** (its `Book.md`
   intermediates are not in this tree) — it cannot be regenerated or maintained here.
4. It performs the same completion-narrative laundering function as the De Rerum
   treatise deleted on 2026-07-02.

## What was NOT retracted

The *hypotheses* named in the compendium remain legitimate OPEN targets under the
Closure Principle. The live, honest versions of every real result live in
`Engine/include/sdt/laws.hpp`, `Benchmarks/`, and the `Investigations/` verdicts —
not here. The sibling `Volume_*.md` outlines, `source_index.md`, and the generator
scripts stay in `Investigations/PV_canon/` as a benign index of the companion repo.

## Evidence trail

- `Investigations/HUNTER_SCOUR_2026-07-02/MASTER_LEDGER.md` (§ FABRICATED #7, §Origin)
- `Investigations/HUNTER_SCOUR_2026-07-02/NP_12-21.md` (μ_n conviction)
- `Investigations/HUNTER_SCOUR_2026-07-02/THEORY_ATOMICUS_HUBBLE.md` (faults #2, #3)
- Deep scan 2026-07-03: per-file grep table, stub census, spot-reads across 10 volumes.
  Correction recorded there: the fabricated Lamb 1051.8 does **not** appear in this
  corpus (that propagation was laws.hpp → B04 → De Rerum only).
