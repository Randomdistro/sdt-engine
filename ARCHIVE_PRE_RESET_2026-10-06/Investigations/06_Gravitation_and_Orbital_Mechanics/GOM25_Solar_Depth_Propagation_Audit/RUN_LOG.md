# GOM25 RUN_LOG

| Field | Value |
|---|---|
| Date (UTC+10 wall) | 2026-08-07 |
| Commit | `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9` |
| Source | `gom25_solar_depth_audit.cpp` |
| Source SHA-256 | `415c7140f165c20a91bc3efd8777f5fbd04e8d755c906a2e3c94e3612e0fda76` |
| Compiler | MSVC 19.x via VS 2022 Build Tools, `/std:c++20 /O2` |
| OS | Windows 10.0.26300 |
| Exit code | 0 |
| Stdout artifact | `.audit-tmp/gom25_run.txt` |

## Validation

- A PASS · B PASS · C branch PASS · C z>1 unguarded CONFIRMED

## Headline numbers (from stdout)

- D1 rows: 27  
- mean ϟ = 1477.262 m · CV = 1.196e-2  
- v_pred (IAU) = 636.585 ± 7.616 m/s  
- paper comparator = 638 ± 6 m/s → COMPATIBLE  
- D4 = PENDING_DATA  
- exact vs LO relative residue ≈ 1.79e-7
