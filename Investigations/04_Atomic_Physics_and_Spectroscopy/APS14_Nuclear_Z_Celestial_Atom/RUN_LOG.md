# APS14 RUN_LOG

**Investigation:** Nuclear-Z celestial atom.  
**Date:** 2026-08-13  
**Direct execution.** **Canon edits:** none.  
**Instrument:** `run_aps14.py`  
**Collector:** `collect_aps14_data.py`  
**Stdout:** `.audit-tmp/aps14_run.txt` (copy `aps14_results.txt`)

## Slice lock

- Calibration elements: all Z=1–30 except hold-outs
- Whole-element hold-outs: `{2, 10, 11, 18, 19, 24, 26, 29}` (He, Ne, Na, Ar, K, Cr, Fe, Cu)
- Fit target: sequential IE log-energy residuals
- Untouched scored lines: APS01 resonance corpus (not in the fit)
- H-like control lines: APS01 NIST comparison columns

## Nested models

M0 zero parameters. M1 one global pair coupling. M2 typed couplings + `delta_s/p/d`. M3 same coupling as M1, relaxed N vs N−1 totals (fit on a thinned calibration slice; scored on the full IE table).
