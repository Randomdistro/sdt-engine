# APS13 RUN_LOG

**Investigation:** Horizon z as wavelength modifier.  
**Status:** EXPLORATORY (pre-registration skipped at author direction, 2026-08-13).  
**Instrument:** `aps13_horizon_z.py`  
**Stdout:** `.audit-tmp/aps13_run.txt`  
**Canon edits:** none.  
**Calibration:** allowed; count stated in assessment.

## Slice lock (named before the hold-out score)

- Train IE: Z ∈ {2,4,6,8,10}, all stages in `ionisation_energies.json`
- Hold-out IE: Z ∈ {3,5,7,9,11,12,18,20,26}
- Rest wavelength: H I Lyα 121.567 nm OBSERVED. D0 uses H I Lyβ 102.5722 nm and Hα 656.4614 nm on hydrogen itself.
- Fe XXVI 2→1: 0.178074 nm OBSERVED (APS12 sticker)

## Run

2026-08-13, direct. Stdout `.audit-tmp/aps13_run.txt`. Assessment `APS13_ASSESSMENT.md`. Geometry and maps scored on the atom / ion against its own ϟ. No other body.
