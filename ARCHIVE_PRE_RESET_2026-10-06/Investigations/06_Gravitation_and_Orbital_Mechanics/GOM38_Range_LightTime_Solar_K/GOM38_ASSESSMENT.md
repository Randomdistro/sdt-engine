# GOM38 Assessment — Type-37 Range / Light-Time vs Solar K

**Date:** 2026-08-08  
**Class:** SDT claim investigation (+ census)  
**Instrument:** `gom38_range_lighttime.py`  
**Stdout:** `.audit-tmp/gom38_run.txt`  
**Canon edited:** no  
**Solar K:** 1476.35 m (frozen; not fitted)

## Claim ledger

| ID | Status |
|---|---|
| GOM38-C1 | **PASS** — 793× type-37 rows (XMMMV0 157–160) |
| GOM38-C2 | **PASS** — all finite |
| GOM38-C3 | **PASS** — Horizons geometry |
| GOM38-C4 | **PASS** (ledger) — absolute RTLT not recovered from RU/F |
| GOM38-C5 | **PASS** — Δt_K median = 6.58×10⁻⁵ s @ b≈41.7 R_☉ |
| GOM38-C6 | **RANGE_K_UNRESOLVED** — Δt_K/σ ≈ 8.6×10⁻⁶ |
| GOM38-C7 | **PASS** — Doppler–solar-K → `PENDING_DEFINITION` |
| GOM38-C8 | **PASS** — K not fitted |

## Census (COMPUTED)

| Item | Value |
|---|---|
| Type-37 rows | 793 |
| Stations | DSS-25 (435), 65 (206), 45 (89), 54 (63) |
| Uplink band | **2 (X)** on all rows |
| obs RU median | 1.678×10⁷ |
| Geometric RTLT median | 8353.36 s |
| obs/F time median | 0.016 s (≠ absolute RTLT) |

## Classification

**`RANGE_K_UNRESOLVED`.**

1. Type-37 observables under documented RU→time factors do **not** match
   absolute round-trip light time (modulo / residual / reference-frequency
   path still open — no free RU scale fit performed).  
2. Frozen-**K** Shapiro delay (~66 μs) is ~10⁻⁸ of geometric RTLT and
   unresolved against the present residual proxy.  
3. Not EMPIRICALLY SURVIVES. Not EXCLUDED.

## Administrative

ODF **Doppler–solar-K** claim path: **`PENDING_DEFINITION`** (GOM36–37
confounded; DAT scale/Fbias unresolved). Further Doppler corr tests against
**K** are deferred until observable definition closes.

## Next gate (ranked)

1. Parallel non-Doppler claim paths: BF080 absolute δ; GOM25 spectral
   mechanism adjudication; GOM20 clock equation.  
2. DAT-only: published RU modulo / reference-frequency reconstruction (no
   **K** fit).  
3. Benchmark detox propose-and-wait.
