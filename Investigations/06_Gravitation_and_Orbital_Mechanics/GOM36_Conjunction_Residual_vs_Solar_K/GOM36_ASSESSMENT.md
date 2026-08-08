# GOM36 Assessment — Conjunction Residual vs Solar K

**Date:** 2026-08-08  
**Class:** SDT claim investigation  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom36_conjunction_residual.py`  
**Stdout:** `.audit-tmp/gom36_run.txt`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM36-C1 | **PASS** — train scale `s = −0.250217` (CALIBRATED(1)) |
| GOM36-C2 | **PASS** — test residual reported |
| GOM36-C3 | **PASS** — `b`, delay, `d(delay)/dt` with frozen **K** |
| GOM36-C4 | **PASS** — \|corr(r, d(delay)/dt)\| = **0.999983** ≥ 0.5 |
| GOM36-C5/C6 | n/a (C4 met) |
| GOM36-C7 | **PASS** — **K** not fitted |

## Numbers (P0 K252, test half)

| Quantity | Value | Tag |
|---|---|---|
| Train / test n | 187 / 186 | — |
| Scale `s` | −0.250217 | CALIBRATED(1) |
| Residual median / stdev | 15298 / 4366 Hz | COMPUTED |
| `b` median | 45.11 R_Sun | COMPUTED |
| Delay median | 6.424×10⁻⁵ s | COMPUTED |
| `f·d(delay)/dt` median | **0.0327 Hz** | COMPUTED |

## Classification

**`SOLAR_K_RESIDUAL_SIGNAL`** under the pre-registered correlation gate.

**Not EMPIRICALLY SURVIVES.** Scope limits:

1. **Amplitude mismatch:** frozen-**K** delay-rate proxy is ~0.03 Hz; hold-out
   residual is ~10⁴ Hz. Correlation without amplitude match can be shared
   slow drift on a ~1 h arc (also `corr(r,1/b)≈0.99998`).  
2. Geometric Doppler definition debt (GOM_DAT8–9) remains; scale is a
   one-parameter calibration, not a closed TRK-2-18 reconstruction.  
3. Conjunction is shallow (`b≈45 R_Sun`); not a limb-grazing discriminator.

## Next gate

1. Add amplitude gate: \|median(r)\| must be within a stated factor of
   \|median(f·d(delay)/dt)\| before SIGNAL can escalate.  
2. Multi-day XMMMV0 arc (stronger `b(t)` variation) with same hold-out rule.  
3. Or close ODF scale definition (DAT) before further claim weight.
