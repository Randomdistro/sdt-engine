# GOM37 — Multi-Day Time-Detrended Residual vs Solar K

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Class:** SDT **claim** investigation.  
> **Upstream:** GOM36 — corr gate fired; delete-test confounded with time.  
> **Canon edits:** none.  
> **Solar K:** frozen **K = 1476.35 m** — not fitted.

## 0. Objective

Re-test the solar-**K** delay-rate proxy against Cassini SCE1 Doppler after
two GOM36 defects are addressed:

1. **Multi-day** DSS-25 type-12 coverage (K252 days 157–160) so `b(t)` is not
   a short monotonic stub.  
2. **Time detrend:** remove a linear trend fitted on the **train** residual
   only, then correlate the test residual with `dΔt/dt`.

## 1. Procedure

1. Load K252 ODFs for SCE1_157…160; keep type-12, RX=25.  
2. `f_geom = −2(ṙ/c)f_ref` with Horizons `CENTER='DSS-25'` range-rate.  
3. **Train** = day 157 only. **Test** = days 158–160.  
4. CALIBRATED(1): `s = median(obs/f_geom)` on train.  
5. `r = obs − s·f_geom`.  
6. Fit `r_train ≈ α + β·t` (least squares). Apply to test:
   `r⊥ = r − (α + β·t)`.  
7. COMPUTE `b(t)`, `Δt(t)`, `dΔt/dt` with frozen **K** (Sun-centered geometry).  
8. Report corr(`r⊥`, `dΔt/dt`) on test, plus amplitude ratio
   `stdev(r⊥) / median|f·dΔt/dt|`.

## 2. Claims / gates

| ID | Claim |
|---|---|
| GOM37-C1 | Multi-day inventory PASS (4× K252 present). |
| GOM37-C2 | Train scale + train-only linear detrend coefficients published. |
| GOM37-C3 | Solar geometry COMPUTED; report b range (min/max R_☉). |
| GOM37-C4 | \|corr(r⊥, dΔt/dt)\| ≥ 0.5 **and** amplitude ratio < 100 → `SOLAR_K_RESIDUAL_SIGNAL`. |
| GOM37-C5 | \|corr\| < 0.2 → `NO_SOLAR_K_RESIDUAL_SIGNAL`. |
| GOM37-C6 | Else, or amplitude ratio ≥ 100 → `UNADJUDICATED`. |
| GOM37-C7 | Delete-test: \|corr(r⊥, time)\| must be reported; if ≥ \|corr(r⊥, dΔt/dt)| − 0.05, mark confounded → force `UNADJUDICATED`. |
| GOM37-C8 | **K** not fitted; no γ. |

## 3. Scope

Still not EMPIRICALLY SURVIVES even if C4 fires. ODF scale definition remains
open (DAT). This loop only asks whether a detrended multi-day residual tracks
frozen-**K** geometry above amplitude/confound gates.
