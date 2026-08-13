# NSEQ09 Pre-registration — Blind δ₂ₙ from pure-shell schedule

**Date:** 2026-08-11  
**Parent debt:** Outstanding “Nuclear packing enumeration / blind δ₂ₙ
(magic not inserted)” · CLM-13 complement to NSEQ05  
**Data:** `Datasets/nuclear/AME2020_mass_excess.txt`  
(SHA-256 `e8599c6d7f724fac91934e59f1b9de8fb8f63e820f4b39456b790665ed2a3307`)

## Blind schedule (no `magic_numbers[]` read)

From closed forms only (`F(n)=(n+1)(n+2)`, `B(n)=2(n+1)`, `R(n)=n(n+1)`):

```
N0 = 2
+ F(1) → 8
+ F(2) → 20
+ B(3) → 28
+ R(3)+B(4) → 50
+ R(4)+B(5) → 82
+ R(5)+B(6) → 126
+ R(6)+B(7) → 184   (forward)
```

Species-pure intermediates (NSEQ05):

```
28 —D12→ 40 —T10→ 50 —D20→ 70 —T12→ 82 —D30→ 112 —T14→ 126 —D42→ 168 —T16→ 184
```

**Classes (pre-labelled, before opening AME numerics beyond neutron ME):**

| Class | N set | Meaning |
|---|---|---|
| SEAL | `{2,8,20,28,50,82,126,184}` | Completed tier / triton-seal or early D closures |
| OPEN_D | `{40,70,112,168}` | Pure-shell deuteron seats *before* next T seal — **not** traditional magic |

If the schedule were just “insert magic,” OPEN_D would be empty or also “magic.”
The discriminator is: SEAL shows δ₂ₙ gaps; OPEN_D does not (or is weaker).

## Observable

For even Z, even N with experimental (non-`#`) AME binding energies:

\[
S_{2n}(Z,N) = B(Z,N) - B(Z,N-2),\quad
B = (B/A)_{\mathrm{AME}}\cdot A
\]

Gap indicator (even N ≥ 4):

\[
D(Z,N) = S_{2n}(Z,N) - S_{2n}(Z,N+2)
\]

Aggregate per neutron number: median over Z of \(D(Z,N)\) when ≥3 chains contribute.

Exclude estimated (`#`) B/A from primary gates. Neutron mass excess used only if
an ME route is added as a cross-check; primary route is B/A.

## Hypotheses

**H1 — Blind schedule.** Computing the cumulative from F/B/R alone yields
exactly `{2,8,20,28,50,82,126,184}` (and OPEN_D `{40,70,112,168}`) with
**zero** reads of any magic table.

**H2 — SEAL gaps.** For SEAL members in `{20,28,50,82,126}` with ≥3 Z-chains,
median \(D(N) > 0\) and the mean of those medians exceeds the mean median-\(D\)
of a control set of even N in `[16,130]` that are neither SEAL nor OPEN_D
(Welch or simple mean comparison; pre-commit: SEAL mean ≥ control mean + 1.0 MeV).

**H3 — OPEN_D weaker.** Mean median-\(D\) over OPEN_D ∩ data `{40,70,112}`
is **less than** mean median-\(D\) over SEAL `{28,50,82}` by ≥ 1.0 MeV
(184 and 168 may be sparse — report, do not require).

**H4 — No magic insert.** Instrument source text contains no literal
`magic_numbers`, `[2, 8, 20, 28, 50, 82, 126]`, or hardcoded SEAL list as
*input* to the schedule builder (SEAL/OPEN_D class labels are allowed as
pre-registered *hypothesis partitions* of the derived cumulatives).

## Decision

| Gate | SURVIVE | EXCLUDE / OPEN |
|---|---|---|
| C1 (H1+H4) | Schedule + no magic-array read | EXCLUDE if schedule wrong or magic list fed in |
| C2 (H2) | SEAL median gaps pass threshold | EXCLUDE if SEAL ≤ control; OPEN if <3 SEAL N adjudicable |
| C3 (H3) | OPEN_D mean < SEAL mean by ≥1 MeV | EXCLUDE if OPEN_D ≥ SEAL; OPEN if <2 OPEN_D adjudicable |

Headline: `BLIND_DELTA2N_SURVIVES` if C1–C3 pass.  
`SCHEDULE_OK_GAPS_FAIL` if C1 pass and C2/C3 fail.  
`DATA_SPARSE_OPEN` if adjudicable counts miss floors.

## Non-goals

No capacity change, no `laws.hpp` edit, no fit to enlarge gaps, no dropping
OPEN_D after seeing data, no shell-model spin–orbit import.
