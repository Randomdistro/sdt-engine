# GOM38 — Type-37 Range / Light-Time vs Frozen Solar K

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Class:** SDT **claim** investigation (+ minimal DAT census).  
> **Upstream:** GOM37 Doppler–solar-K path UNADJUDICATED / blocked.  
> **Canon edits:** none.  
> **Solar K:** frozen **K = 1476.35 m** — not fitted.

## 0. Objective

1. Census SRA range (DATA TYPE 37) on CORS_0021 XMMMV0 ODFs.  
2. Compare decoded range observables to Horizons geometric range / light-time.  
3. COMPUTE frozen-**K** Shapiro delay and ask whether it is resolvable against
   the range residual at this product fidelity.  
4. Formally label the Doppler–solar-K path `PENDING_DEFINITION` if range also
   cannot close without a free scale.

## 1. Claims

| ID | Claim |
|---|---|
| GOM38-C1 | Type-37 rows exist on ≥1 XMMMV0 ODF; n, stations, time span reported. |
| GOM38-C2 | Observable decode (int + frac/1e9) finite for all type-37 rows used. |
| GOM38-C3 | Geometric one-way range from Horizons (DSS-25 or geocenter) COMPUTED at sample epochs. |
| GOM38-C4 | Magnitude gate: median\|obs\| and geometric range reported; if a documented RU→metre factor is unavailable, convert only geometric→seconds and compare delay-class quantities as COMPUTED ledger (no fitted RU scale). |
| GOM38-C5 | Shapiro `Δt_K = (2K/c) ln(4 r1 r2 / b²)` COMPUTED; report median Δt_K and ratio Δt_K / (2R/c). |
| GOM38-C6 | If Δt_K / σ_residual_proxy < 0.01 with no RU closure → `RANGE_K_UNRESOLVED` (not exclusion). |
| GOM38-C7 | Doppler–solar-K path status set to `PENDING_DEFINITION` in META (administrative). |
| GOM38-C8 | **K** not fitted; no γ. |

## 2. Decision rules

- Missing type-37 entirely ⇒ C1 FAIL / PENDING_DATA.  
- Fitting RU scale to match Horizons ⇒ protocol violation.  
- Do not claim EMPIRICALLY SURVIVES from C5 alone.

## 3. Scope

First pass is a **resolvability** test: is the frozen-**K** delay large enough
and is the range product clean enough to test it? A NO is `RANGE_K_UNRESOLVED`,
not EXCLUDED.
