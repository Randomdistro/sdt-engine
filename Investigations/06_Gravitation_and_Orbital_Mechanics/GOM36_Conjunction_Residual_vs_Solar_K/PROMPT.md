# GOM36 — Conjunction Residual vs Solar K (hold-out geometric scale)

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Class:** SDT **claim** investigation (not a DAT task).  
> **Upstream:** GOM_DAT7 shape tracking; GOM_DAT8–9 scale unresolved.  
> **Canon edits:** none.  
> **Solar K:** frozen GOM26 IC **K = 1476.35 m** — not fitted.

## 0. Objective

Ask whether, after removing a **single** geometric Doppler scale calibrated on
the first half of P0 only, the hold-out residual correlates with the solar
conjunction geometry predicted from frozen **K** (Shapiro-like delay-rate).

This is the first post-ODF **claim** test on Cassini SCE1 Doppler. A FAIL is
informative. No free solar-**K** adjustment.

## 1. Procedure (single pass)

1. `f_geom(t) = −2 (ṙ_DSS25/c) f_ref` (GOM_DAT7 definition).  
2. Split P0 K252 type-12 DSS-25 samples at midpoint time.  
3. **CALIBRATED(1):** `s = median(obs / f_geom)` on **train** half only.  
4. Hold-out residual: `r = obs − s·f_geom` on **test** half.  
5. Independently COMPUTE solar impact proxy `b(t)` (Sun–ray miss distance)
   and `dΔt/dt` from `Δt = (2K/c) ln(4 r_E r_sc / b²)` with frozen **K**.  
6. Report corr(r, dΔt/dt) and corr(r, 1/b) on the test half.

## 2. Claims

| ID | Claim |
|---|---|
| GOM36-C1 | Train/test split + scale `s` from train only (CALIBRATED(1)). |
| GOM36-C2 | Test residual series published (min/med/max/stdev). |
| GOM36-C3 | Solar geometry `b(t)`, `Δt(t)`, `dΔt/dt` COMPUTED with frozen **K**. |
| GOM36-C4 | \|corr(r, dΔt/dt)\| on test ≥ 0.5 ⇒ `SOLAR_K_RESIDUAL_SIGNAL` (not yet EMPIRICALLY SURVIVES). |
| GOM36-C5 | \|corr\| < 0.2 ⇒ `NO_SOLAR_K_RESIDUAL_SIGNAL` at this fidelity. |
| GOM36-C6 | 0.2 ≤ \|corr\| < 0.5 ⇒ `UNADJUDICATED`. |
| GOM36-C7 | **K** never fitted; γ / Bertotti unused. |

## 3. Scope

A `SOLAR_K_RESIDUAL_SIGNAL` label means only that the hold-out residual tracks
the frozen-**K** delay-rate proxy under this calibration. It is **not**
framework EMPIRICALLY SURVIVES. Media, ramps, and IF definition remain open.
