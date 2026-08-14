# APS14a Run Log

**Date:** 2026-08-13  
**Direct execution:** `python -u run_aps14a.py`  
**Stdout:** `aps14a_results.txt`  
**Outputs:** `outputs_aps14a/`  
**Canon edits:** none

## Frozen split

- Calibration neutral lines: 13
- Whole-element hold-out neutral lines: 8
- H-like controls: 7
- Hold-out Z: `{3, 7, 10, 11, 18, 19, 26, 29}`

The scored ledger is `data/aps14a_lines.csv`. NIST ASD raw responses for
neutral Z=1–30 were cached after adding explicit wavelength bounds to the
query. Hashes are recorded in `DATA_MANIFEST_APS14A.md`.

## Controls

- Ten APS14/APS14a unit controls: pass.
- H-like path ratio maximum relative error: `2.220e-16`.
- Action-closure maximum relative residual: `6.099e-10`.
- Forward delete-test after fitting: pass.

## Fit

```text
A3 eta = -0.57102
A4 eta = -0.330885
A4 rho = 5.85e-20
```

`rho` collapsed to zero. It is not identified. A4's improvement over A3 comes
from explicit companion relaxation and the refitted orientation coefficient,
not a surviving core-depth parameter.

## Execution note

The final run completed with exit code 0. The assessment uses only the final
run's `outputs_aps14a/summary.json` and CSV ledgers.
