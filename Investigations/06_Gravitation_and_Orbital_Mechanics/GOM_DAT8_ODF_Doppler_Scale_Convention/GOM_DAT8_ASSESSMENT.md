# GOM35 Assessment — ODF Doppler Scale/Sign Convention

**Date:** 2026-08-08  
**Commit:** `6e091f612cd7b3af85c31dbbc2b83d3770aec1b9`  
**Instrument:** `gom35_doppler_scale.py`  
**Stdout:** `.audit-tmp/gom35_run.txt`  
**Canon edited:** no

## Claim ledger

| ID | Status |
|---|---|
| GOM35-C1 | **PASS** — frozen DSS-25 RR + P0 ODF |
| GOM35-C2 | **PASS** — H0–H7 table reported |
| GOM35-C3 | **FAIL** — no hypothesis met both gates |
| GOM35-C4 | **SCALE_CONVENTION_UNRESOLVED** |
| GOM35-C5 | **PASS** — solar **K** unused |

## Hypothesis table (n=125)

| ID | Model | ratio | rel_resid | Pass |
|---|---|---:|---:|---|
| H0 | f0 | 3.392 | 4.392 | no |
| H1 | −f0 | 3.392 | 2.392 | no |
| H2 | −½ f0 | 1.696 | 0.696 | no |
| H3 | −f0/π | 1.080 | 0.153 | no |
| H4 | −f0·(221/240) | 3.124 | 2.124 | no |
| H5 | −f0·(240/749) | 1.087 | 0.151 | no |
| H6 | −f0·(f_ref/8.4e9) | 0.855 | 0.150 | no |
| H7 | −f0·(8.4/32.028) | 0.890 | 0.150 | no |

Gate: `rel_resid < 0.15` and `|ratio−1| < 0.15`.

## Classification

**`SCALE_CONVENTION_UNRESOLVED`.**

Near-misses (H3/H5/H6/H7 at rel≈0.15) are noted but **not** promoted: no
pre-registered documented factor clears both thresholds without a free fit.
Full TRK-2-18 ramp / `Fbias` reconstruction remains required before any
solar-**K** Doppler profile test.

## Next gate

GOM36 — reconstruct uplink ramps from ODF Group 4 and form
`Doppler = Observable + Fbias` sky-frequency path per TRK-2-18 Rev E App. A.2.
