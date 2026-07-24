# GOM14: Mass-Free Koppa-Density Consistency — the demonstration graded honestly, and what it feeds

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **first standalone prompt 2026-07-24.**
> Prior agent-era VERDICT + results deleted 2026-07-24 (git-recoverable; the HUNTER-repair record
> cites ~693 systems at 5.9%-class consistency — an OLD-RUN anchor to reproduce-or-explain).
> **Inherits:** template + protocol + HUNTER §0/§G. **Execution: DIRECT ONLY.**
> Tool: `koppa_consistency.py` · Data: `koppa_multiplanet.csv` (in-folder, NASA Exoplanet
> Archive pull — a/R*, P per planet; cite + hash at read).

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Now that the vocal-cords rule is standing policy, this
   investigation's class must be stated before its numbers: the claim "every planet of one host
   returns the same koppa-density q = ϟ*/R*³ = (4π²/c²)(a/R*)³/P²" is **Kepler's third law per
   host, written mass-free.** Any theory with Kepler (all of them) predicts the consistency —
   so agreement CANNOT discriminate SDT from rivals, and the shuffle control measures **data
   informativeness, not theory truth.** What is genuinely at stake: (a) the METHODOLOGICAL
   claim — full ephemeris/transit-grade bookkeeping with no G, no kilograms, no stellar mass
   anywhere (GOM02's reach thesis on 693 real systems); (b) the MEASURED consistency number
   itself (the 5.9%-class spread = transit-data quality through the mass-free pipeline), which
   feeds GOM02-P2's invariance case; (c) the Sun anchor closure (Earth's orbit alone →
   ϟ☉ = 1476.6 m, and the density gauge landing on ~1408 kg/m³ **with G appearing ONLY in the
   display-conversion line — that line must be labeled rival-column-display in the output**).
2. **Why does it matter?** — It is the widest mass-free dataset in the repo (693 hosts), the
   empirical backbone of the "no G, no M, no precision lost" pitch — provided it is sold at its
   honest grade: CONVERGENCE-demonstration, never discriminator.
3. **How will we find out?** — P1 re-run direct with labels; P2 the distribution report
   (medians, 75th/90th, fraction-within-10%, shuffle control) vs the OLD-RUN anchor; P3 the
   Sun-anchor closure with the display-G line labeled; P4 hand the per-host spreads to
   GOM02-P2 (cross-file citation, no duplication).
4. **What would prove us wrong?** — Real-vs-shuffled separation collapsing (data pipeline
   defect — the CSV or parse broke, since Kepler guarantees separation on good data); the
   Sun anchor missing 1476.6 m by >0.5% (formula/unit bug).
5. **Done =** dual verdict; the class statement in the header; the numbers reproduced-or-
   explained vs the old anchor.

## §0 Reader's contract
1. **The class is CONVERGENCE-demonstration.** The words "test of SDT" may not appear; the
   honest phrase is "mass-free bookkeeping demonstration + data-quality measurement." The
   shuffle control's meaning (informativeness) is stated wherever it is printed.
2. The display-G line (density gauge) prints `[display conversion — rival column]`.
3. CSV provenance printed at read (rows, bytes; NASA Exoplanet Archive citation).
4. Direct only; teed stdout; fresh dated verdict.

## §④ Phases
**P0** — audit script + CSV header; provenance print. **P1** — run direct. Gates: real median
|dev| within ±1 point of the old 5.9%-class anchor (reproduce-or-explain); shuffled median ≫
real (report the ratio); fraction-within-10% reported both. **P2** — distribution table +
per-host spreads exported (`gom14_host_spreads_<date>.csv`) for GOM02-P2. **P3** — Sun anchor:
ϟ☉ = 1476.6 ± 0.5% from (a/R☉ = 215.032, P = 365.2564 d); density-gauge line labeled. **P4** —
one-paragraph hand-off note in the verdict: what GOM02-P2 should gate on from this data.

## §⑧ Falsifiers
F1 real≈shuffled → pipeline defect (Kepler guarantees separation) — fix, never reinterpret.
F2 Sun anchor >0.5% off → unit bug. F3 "test of SDT" language → verdict VOID (class rule).

## §⑤ Outputs
Fresh `RUN_LOG.md` · `gom14_rerun_<date>.txt` · `gom14_host_spreads_<date>.csv` ·
`GOM14_VERDICT_DIRECT_<date>.md`.

## ⑩ Pre-Run Commitments
```markdown
- Target [A|B|C] · class: CONVERGENCE-demonstration (fixed, not hoped)
- CALIBRATED budget: 0 · Gates: P1 anchor ±1pt · P3 ±0.5% · labels on shuffle + display-G
- Forbidden: discriminator language; agents.
```

*GOM14 · first spec 2026-07-24 · Kepler guarantees the pass; the honesty is in saying so — and
the value is 693 hosts of mass-free precision handed to the ledger case.*
