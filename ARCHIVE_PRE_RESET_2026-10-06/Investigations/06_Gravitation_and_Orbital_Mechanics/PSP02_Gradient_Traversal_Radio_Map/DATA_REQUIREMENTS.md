# PSP02 Data Requirements

## A. Public path (Phase P1 — required)

| Item | Source | Notes |
|---|---|---|
| Heliocentric state | JPL Horizons `Parker Solar Probe` (−96), `CENTER=500@10` | Enc-22 window 2024-12-24 |
| Optional SPICE | https://cdaweb.gsfc.nasa.gov/pub/data/psp/ephemeris/spice/ | Attitude / RTN |
| Earth state | Horizons `Earth`, same times | for Earth–PSP LOS Doppler |

Staging: `Datasets/parker_solar_probe_2026-08/` with manifest (sha256, date).

## B. Primitive radio (Phase P2 — gated)

| Item | Access | Status |
|---|---|---|
| DSN TRK-2-34 TNF / ODF | Restricted (`oscarx.fltops.jpl.nasa.gov` / mission MOC) | **NOT public** |
| Decoder | NASA-PDS PyTrk234 (format only) | usable once files exist |

Without B: investigation stops at `PATH_LEDGER_READY__RADIO_PENDING_DATA`.

## C. Explicitly not substitutes for B

- FIELDS RFS type-III / Langmuir spectra (local plasma emission).  
- Processed “reconstructed trajectory only” without radiometric residuals.  
- Media/scintillation models fitted as if they were \(\Omega/r\).
