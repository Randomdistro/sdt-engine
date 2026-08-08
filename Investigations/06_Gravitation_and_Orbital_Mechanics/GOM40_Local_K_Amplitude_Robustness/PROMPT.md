# GOM40 - Local-K Amplitude Robustness Rerun

**Status:** PRE-REGISTERED - 2026-08-09.
**Class:** Cassini observational-data sensitivity audit; no canon edit and no
new retrieval.
**Upstream:** GOM37 multi-day Doppler residual is `UNADJUDICATED` because its
amplitude ratio is `7.07e6` and its delay-rate correlation is time-confounded.
GOM39 subsequently corrected the grammar from a naked frozen solar `K` to
local `k(r)` with `K = R/k^2`.

## Objective

Test whether the GOM39 local-K correction can remove either GOM37 failure
without fitting any quantity. This is a required recalculation after a
definition conflict, not a new confirmation test.

## Fixed hypotheses

The residual construction, ODF rows, train/test split, geometric scale, linear
detrending rule, solar geometry, and finite-difference stencil are identical to
GOM37. The only two permitted fixed values are:

| Case | Solar K (m) | Origin | Role |
|---|---:|---|---|
| `GOM37_FROZEN` | 1476.350 | GOM37 pre-registered investigation constant | Baseline reproduction |
| `GOM39_LOCAL_EARTH_PROXY` | 1455.637 | GOM39 Earth main-sequence median | Sensitivity alternative, not a fit and not a canon replacement |

For the registered delay, `Delta t = (2K/c) ln(4 r_E r_C / b^2)`, the delay
and delay-rate must scale exactly with fixed positive `K`; the ODF residual and
its time correlation must not be recomputed or calibrated differently.

## Frozen inputs

| Input | SHA-256 | Class |
|---|---|---|
| `sce1_157/odf/c32easc2002_157_0000k252v0.odf` | `c2ea51d9b5e795bd3eb9b4f1c5174cc44325080623188dce5e01c0ea914bfaf7` | Primary Cassini tracking bytes |
| `sce1_157/odf/c32easc2002_157_0000k252v0.lbl` | `b27da74ca62187475860e8214c2b76b8b69af760bbe44d27aac93d1c1a5593bf` | Paired product label |
| `sce1_158/odf/c32easc2002_158_0000k252v0.odf` | `9393717f29f5853cb65cd2b1b40b2e411a0d114e326e9d3c3fa1b1b359bc93a4` | Primary Cassini tracking bytes |
| `sce1_158/odf/c32easc2002_158_0000k252v0.lbl` | `3ec4a042de7313524674563723c35526bb9eede27153d4ba060172d2a57d4bf7` | Paired product label |
| `sce1_159/odf/c32easc2002_159_0000k252v0.odf` | `cfcba02622502887d48dea3e4079d8b9d6fd0a4120b069e8ddeccc9be7683288` | Primary Cassini tracking bytes |
| `sce1_159/odf/c32easc2002_159_0000k252v0.lbl` | `446621ccba2c0064b0c5fac4d9d8885eddedd41867b6149ac429220f74a3cba6` | Paired product label |
| `sce1_160/odf/c32easc2002_160_0000k252v0.odf` | `7f447ba5952d6ae85d33ed74f16458a2319e2e88dca38912d5f4d99b6a344ab9` | Primary Cassini tracking bytes |
| `sce1_160/odf/c32easc2002_160_0000k252v0.lbl` | `63c3de17bade5b4a5a8fd6c7dc25d2c1c61c347444f2062d4c81653a0662077b` | Paired product label |
| `jpl_horizons_cassini_dss25_rr_2002_157_160.csv` | `658021f99e35f77679c9227302c2fabe7a5150b2197aed8f42870536df1fa4ac` | Processed geometry/range-rate input |
| `jpl_horizons_cassini_heliocentric_2002_157_160.csv` | `948c46b6c7447c97739134990c034e97aaf69afc5d8d1b94bb55f6e4d49a0e06` | Processed geometry input |
| `jpl_horizons_earth_heliocentric_2002_157_160.csv` | `3950bf02bdcb9f8d471a8a389dae8fd169db2966f281e784073e3be5b65b734c` | Processed geometry input |
| GOM37 instrument | `c805f0bec605c59aa6ba875771493d3efe582991f297b51471dae8322e199da6` | Frozen residual construction |
| GOM39 assessment | `fb7292f298a86c395bacb46c1d7fa1f871bfe6aa3c84f400ff49f27f5d2d76bc` | Frozen source of the local-K value |

## Procedure and decision rule

1. Verify every frozen hash before parsing any numeric field.
2. Reproduce GOM37's type-12, RX-25 extraction, day-157 training scale,
   train-only linear detrend, and days-158-to-160 test residual exactly.
3. Compute the delay-rate proxy for each fixed `K`; do not fit `K`, scale,
   phase, media term, ramp, or intermediate-frequency correction.
4. Report the amplitude ratio `stdev(r_perp) / median(abs(f*dDelta_t/dt))`,
   the residual-delay-rate correlation, and the residual-time delete-test.
5. If either case has amplitude ratio below `100` **and** is not time-confounded,
   record `REOPEN_FOR_DEFINED_OBSERVABLE`. Otherwise record
   `LOCAL_K_REPAIR_DOES_NOT_CLEAR_GOM37_GATES`.

The latter result is not a physical exclusion: the observable-definition and
processed-geometry limitations already identified by GOM37 remain. No
standard-model value, parameter, or rejection rule is used.
