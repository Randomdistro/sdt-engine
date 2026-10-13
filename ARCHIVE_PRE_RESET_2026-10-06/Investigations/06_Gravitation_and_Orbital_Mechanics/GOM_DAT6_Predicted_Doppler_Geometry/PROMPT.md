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

---

## Audit correction 2026-10-05 (gating)

**Finding:** Gate C4 passes when the geometric and observed Doppler medians are "within a factor of 10", and it passed at a ratio of 3.365, a scale mismatch that the next two folders could not resolve (GOM_DAT8 "scale convention unresolved").

**Correction:** Gate at ≤ 5% (or the documented turnaround factor exactly) so a 3.4× discrepancy fails at this step.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*

**Id alias (2026-10-05):** claim ids written `GOM33-C*` in this folder and its verdict are the claims of `GOM_DAT6`. The rows are VERIFICATION (data-structure, checksum and field-parse checks), not tests of a physical claim, and are excluded from physics PASS/FAIL tallies; earlier text is not rewritten.
