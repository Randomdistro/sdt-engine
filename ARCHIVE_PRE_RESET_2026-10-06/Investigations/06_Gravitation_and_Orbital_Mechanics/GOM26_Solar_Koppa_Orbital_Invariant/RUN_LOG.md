# GOM26 RUN_LOG

| Field | Value |
|---|---|
| Date | 2026-08-07 |
| Commit | `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9` |
| Source | `gom26_koppa_invariant.cpp` |
| Source SHA-256 | `D86CBF15D14802D5AB1423AAA4D2BA2583AEB54742EA4E98FC8EC1853494494E` |
| Compiler | MSVC 19.x via VS 2022 Build Tools, `/std:c++20 /O2` |
| OS | Windows 10.0.26300 |
| Command | `.audit-tmp\gom26.exe ...\jpl_horizons_emb_sun_vectors_2025.csv INTRA_YEAR` |
| Exit code | 0 |
| Stdout | `.audit-tmp/gom26_run.txt` |

## Validation

- A PASS · B PASS

## Headline numbers

- C1/C2: CV_recon = 9.94e-6 (inst CV = 1.18e-2) → PASS  
- C4 INTRA_YEAR: \|Δϟ\|/ϟ = 3.56e-5 → PASS  
- C3: v_pred = 636.191 ± 0.050 m/s vs 638 ± 6 → COMPATIBLE / UNADJUDICATED  
- D4: 64820 records · PENDING_DATA  

## Data incidents

- Wrong-center 2024 Horizons retrieval quarantined as non-admissible hold-out.  
- API re-fetch attempts returned VLADD errors; pre-registered INTRA_YEAR fallback used.
