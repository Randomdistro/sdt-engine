# Benchmark Detox Assessment — B15 / B16 / B25

**Date:** 2026-08-07  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `Audits/tools/bench_detox_b15_b16_b25.cpp`  
**Stdout:** `.audit-tmp/bench_detox_run.txt`  
**Suite edit:** **applied 2026-08-09** to `Benchmarks/B01_B25/benchmarks_suite.cpp`
(benchmarks are not `laws.hpp` / `Laws/` canon; detox was propose-and-wait only while
formal classification was open). Re-run: `.audit-tmp/bench_detox_suite_run.txt` →
**50/61 earned (82.0%)**, 6 PENDING note-only, 11 PENDING open fails unchanged.

## Delete tests (decisive)

| Row | Printed label | Engine symbols in value | Survives engine deletion? | Detox status |
|---|---|---|---|---|
| B15 BAO 147 Mpc | COMPUTED | none (`147.0` literal) | yes | LITERAL TARGET ECHO |
| B16 κ/η/D exponents ×3 | DERIVED | none (`0.5000` literal) | yes | LITERAL TARGET ECHO |
| B25 exact NR | COMPUTED | none (`-79.0052`; Pekeris) | yes | BORROWED LITERAL |
| B25 variational | COMPUTED | uses `Ry_eV` + Hylleraas form | no (expression) | SHARED-FORM COMPUTED |
| B25 R_He=2Rp | DERIVED | engine radii | — | retain; separate radius audit |

## Recalculated headline

| | Earned pass | Earned denom | Rate |
|---|---:|---:|---:|
| Printed suite | 56 | 67 | 83.6% |
| After detox | **50** | **61** | **82.0%** |

Removed from earned: 5 literal + 1 shared-form = 6 rows.  
Identities (11) and calibrated (2) unchanged (already excluded from earned).  
PENDING fails (11) unchanged.

## Required suite repair — applied 2026-08-09

1. Relabelled B15, B16×3, B25 exact, B25 variational as `PENDING` / note-only.  
2. `report()`: PENDING that meet tolerance → `g_pending_note` (excluded from earned denom); PENDING that miss tol remain known-open fails in denom.  
3. SUMMARY prints note-only count; headline **50/61 (82.0%)** — historical 56/67 retired.

## Classification

Formal detox complete and suite-applied. No empirical exclusion of physical claims — these rows never were independent predictions.
