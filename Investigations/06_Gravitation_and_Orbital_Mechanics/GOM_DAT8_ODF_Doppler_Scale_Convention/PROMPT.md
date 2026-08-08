# GOM35 — ODF Doppler Scale/Sign Convention (discrete documented hypotheses)

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Upstream:** GOM34 FAIL — shape tracks (|corr|≈0.9996); scale≈−0.295.  
> **Canon edits:** none.  
> **Solar K:** frozen; not used; not fitted.

## 0. Objective

Identify whether a **pre-registered documented** scale/sign convention brings
DSS-25 geometric Doppler into agreement with P0 `obs_Hz` without fitting
solar **K** or any free coefficient to the ODF series.

## 1. Predictor base

`f0(t) = −2 (ṙ_DSS25(t)/c) f_ref`  
(same as GOM34 B1; ṙ from frozen Horizons DSS-25 CSV).

## 2. Discrete hypotheses (frozen before run)

| ID | Model | Provenance |
|---|---|---|
| H0 | `f = f0` | GOM33/34 baseline |
| H1 | `f = −f0` | bias-polarity / sign convention |
| H2 | `f = −½ f0` | one-way equivalent of two-way formula |
| H3 | `f = −f0/π` | speculative IF factor (documented only as math constant) |
| H4 | `f = −f0 · (221/240)` | S-band T2/T1 from ODF label |
| H5 | `f = −f0 · (240/749)` | X-band T1/T2 fragment from label |
| H6 | `f = −f0 · (2.116e9 / 8.4e9)` | S/`X` carrier ratio using f_ref / 8.4 GHz |
| H7 | `f = −f0 · (8.4e9 / 32.028e9)` | X/Ka nominal ratio |

H3 is included only as a closed mathematical constant; it is **not** an SDT claim.
No least-squares scale is permitted.

## 3. Claims / decision rules

| ID | Claim |
|---|---|
| GOM35-C1 | Reuse frozen DSS-25 RR + P0 ODF; no new free params. |
| GOM35-C2 | For each Hi, report median \|obs−f\| and ratio med\|f\|/med\|obs\|. |
| GOM35-C3 | PASS if some Hi has med\|obs−f\| / med\|obs\| < 0.15 **and** \|med\|f\|/med\|obs\| − 1\| < 0.15. |
| GOM35-C4 | If none pass ⇒ `SCALE_CONVENTION_UNRESOLVED`; ramp/`Fbias` reconstruction required. |
| GOM35-C5 | Solar **K** not fitted. |

## 4. Classification vocabulary

- `SCALE_CONVENTION_PASS (Hi)` if C3 met.  
- `SCALE_CONVENTION_UNRESOLVED` if C4.  
No EMPIRICALLY SURVIVES / EXCLUDED for SDT solar **K** from this loop.
