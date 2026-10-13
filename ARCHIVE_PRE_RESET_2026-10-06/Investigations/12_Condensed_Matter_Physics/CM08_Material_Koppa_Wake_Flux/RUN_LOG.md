# CM08 Run Log

**Author:** James Christopher Tyndall, Melbourne  
**Pre-registration recorded:** 2026-08-15, before instrument creation

## Frozen configuration

- Li density: 534 kg/m³; mass number 7
- U density: 19,100 kg/m³; mass number 238
- Equal-mass comparison: 1.000 kg
- Equal-size comparison: radius 0.050 m
- Wake exponent: −3
- Flux control: one electron-equivalent circular current per atom, common
  angular rate and alignment
- Gates: C0–C6 in `PROMPT.md`

## Run entries

### Run 1 — 2026-08-15

- Direct build: MSVC C++20, `/O2 /utf-8`
- Result: **VALIDATED MATERIAL LEDGER**
- C0–C6: all passed
- Equal mass:
  - far-field ratio U/Li = 1
  - baryon-density ratio U/Li = 35.76779026
  - surface-response ratio U/Li = 10.85578933
- Equal radius:
  - total koppa and far-field ratio U/Li = 35.76779026
- Wake radius-doubling ratio = 8
- Flux count controls:
  - equal mass U/Li = 0.008926688487
  - equal radius U/Li = 1.051993831
- Raw capture: `cm08_results.txt`

### Run 2 — 2026-08-15 verification rerun

- Direct rebuild after the website-data flux controls were wired.
- Result: **VALIDATED MATERIAL LEDGER**
- C0–C6: all passed at the frozen thresholds.
- Numerical results matched Run 1; `cm08_results.txt` is the direct capture.
