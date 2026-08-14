# NP30 triton-contraction root audit — amendment 01

**Date:** 2026-08-09
**Reason:** Static inspection of the registered `ATOMICUS/tools/enrich_boundary_radius.py` identified additional historical inputs and a separate closure-kink computation not named in the original NP30 source inventory.  This amendment freezes them before either data file is parsed or either new artifact is inspected.

| Additional artifact | Role |
|---|---|
| `ATOMICUS/tools/_iaea_ground_states.csv` | actual CSV read by the historical enrichment generator; potential 281-row source |
| `ATOMICUS/tools/closure_kink_isotone.py` | cited closure-kink reduction, if present |
| `ATOMICUS/reports/CLOSURE_KINK_ISOTONE_REPORT.md` | cited historical closure-kink output, if present |

The audit also adds a descriptive historical-kink reconstruction, after all amended source gates pass:

```text
kappa(Z,N) = [R(Z,N) - (R(Z,N-2) + R(Z,N+2))/2] * 1000 milli-fm.
```

This is the exact form in the discovered generator.  It will be reported for calculable triples and for endpoints where `N` or `Z` belongs to the frozen historical list `{2,8,20,28,50,82,126}`.  The list remains an empirical classification input, not a derived conclusion.  The kink is a reconstruction of a historical data summary only; it cannot establish the purported interleave mechanism or closure origin absent a frozen predictive derivation.
