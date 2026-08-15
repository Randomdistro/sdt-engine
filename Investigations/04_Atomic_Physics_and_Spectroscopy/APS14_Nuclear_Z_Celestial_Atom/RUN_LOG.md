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

## B06/B25 closure execution — 2026-08-15

**Instrument:** `aps14_b06_b25_closure.py`<br>
**Kernel:** fixed polar `2s` dyad plus equatorial `2p` six-ring;
`dodecardinal_lock`<br>
**Forward dependencies:** `Ry`, Z, occupancy, FLM15 lock/wake partition,
coincident synchrony, and exact path/chord geometry<br>
**Forbidden dependencies absent:** measured IE in the forward solver,
element-specific screening, Hylleraas/Slater/Pekeris amplitudes

```text
one_electron_max_relative_error=2.220e-16
max_force_residual=5.716e-16
B06_median_relative_error=1.475932%
B06_max_relative_error=5.248820%
B25_He_relative_error=1.218928%
sequential_holdout_rows=45
sequential_holdout_median_relative_error=1.621205%
sequential_holdout_max_relative_error=8.629562%
SEQUENTIAL_HOLDOUT=PASS
B06_GATE=PASS
B25_GATE=PASS
```

The exact coefficient forms were selected during B06 response-surface
diagnostics; classification is `COMPUTED`. Higher sequential ionizations were
not used in that selection and are the independent validation slice.
