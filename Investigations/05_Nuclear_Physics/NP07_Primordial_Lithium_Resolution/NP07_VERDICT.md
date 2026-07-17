# NP07 — Primordial Lithium Resolution · VERDICT

> **Status: OPEN (mechanism map earned; quantitative resolution not claimable in-chain)**
> Run 2026-07-12 by Fable **directly** (no auto-agent). Build/run clean; stdout in
> `np07_results.txt`; phase record appended to `RUN_LOG.md`. Pre-commitments followed
> exactly — zero ADJ, zero fits, zero plugs.

## Earned

- **P0 [NATIVE]** — Grammar selection rule, exact integers: Be-7 is not alpha-constructible
  ((3,−1) underflow); it exists only in the He-3-core grammar (2,0) and is EC-forced to
  Li-7 via the exact (−3,+2) vector. Li-6 = α+d; Li-7 = α+t or Be-7 EC. Cross-checks NP18.
- **P1 [COMPUTED]** — The SDT EC-blocking scale from engine kinematics only:
  stripped Be-7 cannot EC; the EC clock starts when the plasma can hold the ~217.7 eV
  first seat (err 0.004% vs reference; ~16× the hydrogen seat).
- **P2 [RIVAL-COMPARISON]** — If the rival (BBN) production number is taken at face value,
  any resolution requires destroying 66.2% ± 8.2% of mass-7 *during the ionised window*.
  Sign analysis: delayed EC alone conserves mass-7 and cannot help; the EC-block lengthens
  the destruction window — the SDT mechanism has the **right sign**.

## Not earned (and why the verdict is OPEN, not PASS)

Quantitative Li-7/H requires (i) a native SDT primordial thermal/density history — does not
exist (SDT rejects the expansion framework; its cyclic cosmology is uncommitted) — and
(ii) measured σ(p+Be-7→B-8) (NACRE/EXFOR) — legitimate OBSERVED input, not in this repo.
Neither is in-chain. No final number is claimed.

## Data needs (to convert OPEN → decidable)

1. σ(p + Be-7 → B-8) capture data imported as OBSERVED.
2. Any committed SDT thermal history for the pre-Clearing plasma (blocked on the
   cyclic-cosmology canon call).

— Verdict recorded by Fable, 2026-07-12. Sources: PROMPT.md, RUN_LOG.md, np07_results.txt.
