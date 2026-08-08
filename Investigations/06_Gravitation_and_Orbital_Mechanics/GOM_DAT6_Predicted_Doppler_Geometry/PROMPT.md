# GOM33 — DSS-25 Type-12 Predicted Doppler Geometry (solar K fixed)

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Upstream:** GOM32 UNIT_PATH_ENGINEERING_DOPPLER_HZ.  
> **Canon edits:** none.  
> **Notation:** SDT capital **K** = c-boundary radius (frozen from GOM26).  
> ODF label `K` = turnaround ratio — distinct.

## 0. Objective

Build an independent **predicted** two-way Doppler for frozen SCE1 DSS-25
type-12 samples, so `obs_Hz` can later be compared without refitting solar **K**.

This loop establishes geometry + classical range-rate prediction and reports
order-of-magnitude consistency. It does **not** claim SDT survival or exclusion.

## 1. Claims

| ID | Claim |
|---|---|
| GOM33-C1 | Cassini state vectors at ODF epochs are obtainable from volume SPK and/or Horizons (dependency recorded). |
| GOM33-C2 | DSS-25 Earth-fixed coordinates are taken from a published DSN station table (MEASURED-INPUT). |
| GOM33-C3 | Classical geometric two-way Doppler from line-of-sight range-rate is COMPUTED (no solar **K** in this term). |
| GOM33-C4 | Magnitude gate: median \|f_geom\| on P0 K252 window is within a factor of 10 of median \|obs_Hz\| (same kHz class). |
| GOM33-C5 | Solar-**K** profile correction to Doppler/delay is either omitted or reported separately as COMPUTED with **K** frozen — never fitted to ODF. |
| GOM33-C6 | No γ fit; no Bertotti residual reuse. |

## 2. Decision rules

1. Missing ephemeris coverage for the P0 window ⇒ C1 FAIL / PENDING_DATA.  
2. Station coordinates without provenance ⇒ C2 FAIL.  
3. C4 FAIL if \|f_geom\| median outside `[0.1, 10] × |obs|_median`.  
4. Any least-squares adjust of solar **K** to ODF ⇒ protocol violation.

## 3. Frozen solar K

Investigation IC from GOM26: **K** ≈ 1476.35 m (DERIVED from EMB–Sun vectors).  
Used only if a separate profile term is computed; not a free parameter.

## 4. Scope limit

Full Moyer/Regres formulation (media, troposphere, exact ramp reconstruction)
is **out of scope** for the first pass. First pass = geometric range-rate Doppler
plus documented turnaround scaling. Media/ramp fidelity upgrades are later loops.
