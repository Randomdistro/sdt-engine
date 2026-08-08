# GOM_DAT9 — ODF Ramp / Fbias Reconstruction (TRK-2-18)

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Class:** data / reconstruction task (not an SDT claim investigation).  
> **Upstream:** GOM_DAT8 SCALE_CONVENTION_UNRESOLVED.  
> **Canon edits:** none.  
> **Solar K:** frozen; unused; not fitted.

## 0. Objective

Reconstruct TRK-2-18 Doppler as:

`Doppler[Hz] = Observable + Fbias`

with Case-2 (2-way coherent) `Fbias = ρ · ul_freq`, decode DSS-25 ramp
records, and test whether this closes the ~3.4× scale gap vs DSS-25
geometric range-rate — without fitting solar **K**.

## 1. Claims

| ID | Claim |
|---|---|
| DAT9-C1 | Ramp Group 25 present; ≥1 ramp data row decoded (start freq, rate, times). |
| DAT9-C2 | Case-2 `Fbias = (209/15)·ul_freq` formed; `ul_freq` from Items 18–19 and/or ramp sky frequency. |
| DAT9-C3 | Predictors reported: (P0) `−2(ṙ/c)f_ref`; (P1) `−2(ṙ/c)Fbias`; (P2) sky residual `obs − [Fbias(1−2ṙ/c) − Fbias]`. |
| DAT9-C4 | PASS if some Pi has `rel_resid = med\|obs−f\|/med\|obs\| < 0.15` and `\|ratio−1\| < 0.15`. |
| DAT9-C5 | Else `FBIAS_RECON_UNRESOLVED` — document ramp census; no free scale fit. |
| DAT9-C6 | Solar **K** not fitted. |

## 2. Inputs

- P0 ODF/label (frozen CORS_0021 SCE1_157 K252)  
- Frozen Horizons DSS-25 RR CSV from GOM_DAT7  
- TRK-2-18 Rev E App. A.2 (documented)

## 3. Notation

- SDT capital **K** = c-boundary radius (unused here).  
- ODF/TRK `K` / `ρ` = transponder turnaround ratio.
