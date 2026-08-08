# GOM37 Assessment — Multi-Day Time-Detrended Residual vs Solar K

**Date:** 2026-08-08  
**Class:** SDT claim investigation  
**Instrument:** `gom37_multiday_detrended.py`  
**Stdout:** `.audit-tmp/gom37_run.txt`  
**Canon edited:** no  
**Solar K:** 1476.35 m (frozen; not fitted)

## Claim ledger

| ID | Status |
|---|---|
| GOM37-C1 | **PASS** — 4× K252 HAVE |
| GOM37-C2 | **PASS** — `s = −0.294774`; α, β from train day 157 |
| GOM37-C3 | **PASS** — b ∈ [35.37, 42.70] R_☉ on test |
| GOM37-C4 | **not met** — amp_ratio ≫ 100 |
| GOM37-C5 | n/a (corr high but invalid under C6/C7) |
| GOM37-C6/C7 | **UNADJUDICATED** — time confound + amplitude gate |
| GOM37-C8 | **PASS** — K not fitted |

## Numbers (test = DOY 158–160)

| Quantity | Value |
|---|---|
| Train / test n | 125 / 1235 |
| b range | 35.37 – 42.70 R_☉ |
| stdev(r⊥) | 2.72×10⁵ Hz |
| median \|f·dΔt/dt\| | 0.0385 Hz |
| amp_ratio | **7.07×10⁶** |
| corr(r⊥, dΔt/dt) | −0.9917 |
| corr(r⊥, time) | −0.9955 |

## Classification

**`UNADJUDICATED`.**

Multi-day + train-only linear detrend does **not** isolate a solar-**K**
delay-rate signal. The residual remains time-aligned and ~10⁶× larger than the
frozen-**K** Doppler proxy. Day-157 scale/detrend does not transfer cleanly to
158–160 (stdev explosion), which is a geometric/definition fidelity finding,
not an SDT exclusion.

Not EMPIRICALLY SURVIVES. Not EXCLUDED.

## Implications

1. Short-window and multi-day corr gates are both confounded without a closed
   ODF observable definition (DAT debt).  
2. Solar-**K** Doppler profile tests on raw `obs_Hz` are **blocked** until
   scale/IF reconstruction closes or a delay/range observable is used.  
3. Highest-leverage claim paths now: (a) type-37 range / light-time product;
   (b) BF080 absolute δ; (c) non-Doppler solar tests already open.

## Next gate (ranked)

1. GOM38 — type-37 range channel census + light-time residual with frozen **K**
   (or declare Doppler path PENDING_DEFINITION).  
2. Parallel: BF080 / benchmark detox.
