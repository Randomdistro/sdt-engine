# GOM_DAT — Solar-propagation data / reconstruction tasks

> **Class:** data & instrument tasks (not SDT claim investigations).  
> **Series:** `GOM_DAT1` … `GOM_DAT9`  
> **Former numbers:** GOM28–GOM35 → DAT1–DAT8 (renamed 2026-08-08).  
> **Canon edits:** none from this series.

These loops freeze PDS products, decode ODF fields, and close predictor
definition gates so a later **GOM** claim test can use Cassini Doppler/delay
without fitting solar **K**. They do not adjudicate EMPIRICALLY SURVIVES /
EXCLUDED for SDT.

## Index

| ID | Folder | Former | Content |
|---|---|---|---|
| **GOM_DAT1** | `GOM_DAT1_Cassini_ODF_Structural_Census` | GOM28 | PDS3 ODF label/table structural census (STRUCTURE_PASS); TDF noted STRUCTURE_PARTIAL |
| **GOM_DAT2** | `GOM_DAT2_Cassini_ODF_Field_Census` | GOM29 | Orbit-data field census; type-12 2-way Doppler @ DSS-25 bounds |
| **GOM_DAT3** | `GOM_DAT3_Cassini_ODF_Observable_Decode` | GOM30 | Label-scaled `obs_Hz` / `f_ref` decode on frozen P0 K252 |
| **GOM_DAT4** | `GOM_DAT4_Cassini_ODF_Multiday_Decode` | GOM31 | All 8 CORS_0021 ODFs (DOY 157–160); multi-day HAVE |
| **GOM_DAT5** | `GOM_DAT5_ODF_Observable_Unit_Path` | GOM32 | Unit path = engineering Doppler Hz (not µHz ODP residual) |
| **GOM_DAT6** | `GOM_DAT6_Predicted_Doppler_Geometry` | GOM33 | Geocenter geometric Doppler magnitude class check |
| **GOM_DAT7** | `GOM_DAT7_Station_Doppler_Fidelity` | GOM34 | DSS-25 LOS; station ruled out as ~3.4× scale gap source; shape tracks |
| **GOM_DAT8** | `GOM_DAT8_ODF_Doppler_Scale_Convention` | GOM35 | Discrete scale/sign hypotheses → SCALE_CONVENTION_UNRESOLVED |
| **GOM_DAT9** | `GOM_DAT9_ODF_Ramp_Fbias_Reconstruction` | — | TRK-2-18 ramp/`Fbias`; Ka 34.318 GHz; FBIAS_RECON_UNRESOLVED |

## Status snapshot (2026-08-08)

| ID | Headline |
|---|---|
| GOM_DAT1 | STRUCTURE_PASS |
| GOM_DAT2 | FIELD_CENSUS_PASS |
| GOM_DAT3 | OBSERVABLE_DECODE_PASS |
| GOM_DAT4 | MULTIDAY_DECODE_PASS |
| GOM_DAT5 | UNIT_PATH_ENGINEERING_DOPPLER_HZ |
| GOM_DAT6 | GEOM_DOPPLER_MAGNITUDE_PASS |
| GOM_DAT7 | STATION_DOPPLER_FIDELITY_FAIL (informative) |
| GOM_DAT8 | SCALE_CONVENTION_UNRESOLVED |
| GOM_DAT9 | FBIAS_RECON_UNRESOLVED (ramp f0 = 34.318 GHz Ka) |

## Related claim investigations (not DAT)

| ID | Role |
|---|---|
| GOM25 | Solar depth / spectral audit |
| GOM26 | Orbital solar **K** invariant |
| GOM27 | Shared-profile deflection δ(b) |
| GOM36 | Hold-out residual vs solar **K** — gate SIGNAL; delete-test confounded with time |
| GOM37 | Multi-day detrended residual — **UNADJUDICATED** (time + amp_ratio 7e6) |
| GOM38 | Type-37 range/light-time — **RANGE_K_UNRESOLVED**; Doppler–**K** → PENDING_DEFINITION |
| GOM39 | Local **k** / **K = R/k²** definition — **DEFINED**; residual not re-promoted |
| GOM40 | Energy-form **K** — SCE1 arc **ARC_INSUFFICIENT**; year EMB **K=1476.354 m** + local-**k** delay-rate |
| GOM20 | GPS clock — **PENDING_MECHANISM** (author equation) |

## Path status

| Path | Status |
|---|---|
| ODF Doppler vs solar **K** | **DEFINED** (GOM39: local **k**, **K = R/k²**) |
| Energy-form **K** for SCE1 delay | **YEAR_IC** (GOM40 / GOM26); short-arc energy form excluded |
| Empirical Doppler residual vs depth | **UNADJUDICATED** (GOM36–37) |
| ODF type-37 vs solar **K** | **RANGE_K_UNRESOLVED** (GOM38) |

## Next ranked

1. BF080 absolute δ / GOM25 spectral mechanism.  
2. GOM20 author clock equation.  
3. Optional DAT: RU modulo reconstruction (no **K** fit).  

Benchmark detox B15/B16/B25: **applied** (Iteration 21) — earned 50/61.
