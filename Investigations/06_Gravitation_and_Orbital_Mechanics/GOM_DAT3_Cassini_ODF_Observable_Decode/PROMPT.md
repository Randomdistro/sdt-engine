# GOM30 — ODF Doppler Observable Decode (Hz) + Multi-Day Freeze List

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Upstream:** GOM29 FIELD_CENSUS_PASS.  
> **Canon edits:** none.

## 0. Objective

1. Decode the Orbit Data Group **observable field** of the frozen K252 ODF into
   hertz using only the paired PDS3 label scaling.  
2. Publish a pre-registered multi-day ODF freeze list from `cumindex.tab` for
   SCE1 days 157–160 (CORS_0021).  
3. Do **not** form an SDT or competitor light-time residual in this loop.

## 1. Claims

| ID | Claim |
|---|---|
| GOM30-C1 | `obs_Hz = obs_int + obs_frac/1e9` yields finite values for all 7447 type-12 rows. |
| GOM30-C2 | Reference frequency from Items 18–19 (mHz high/low) reconstructs a positive carrier-scale frequency for every row. |
| GOM30-C3 | Observable time series is reported (min/median/max/stdev); validity flag histogram reported. |
| GOM30-C4 | Cumindex freeze list enumerates all `*.ODF` products for SCE1_157…160 with start/stop times. |
| GOM30-C5 | No SDT delay residual, no γ fit, no `ϟ` fit. |

## 2. Scaling (paired label only)

- Observable integer: bytes 9–12, MSB integer.  
- Observable fractional: bytes 13–16, MSB integer, **scaled by 10⁹**.  
- Ref frequency: Item 18 (22 bits, mHz high) + Item 19 (24 bits, mHz low) →  
  `f_ref_Hz = (high * 2^24 + low) * 1e-3`  
  (bit packing as documented in Items 18–19 of ODF3C).

## 3. Decision rules

1. Hash gate identical to GOM28/29.  
2. Any non-finite `obs_Hz` ⇒ C1 FAIL.  
3. `f_ref_Hz <= 0` on any row ⇒ C2 FAIL.  
4. Printing μs delay or comparing to `shapiro_delay` ⇒ protocol violation.

## 4. Multi-day freeze list (pre-registered targets)

From cumindex, priority order:

| Priority | Product | Span (from index) |
|---|---|---|
| P0 (have) | `C32EASC2002_157_0000K252V0.ODF` | 157 20:41 – 157 22:45 |
| P1 | `C32EASC2002_157_0000XMMMV0.ODF` | 157 05:30 – 158 04:59 |
| P2 | `C32EASC2002_158_0000K252V0.ODF` / `XMMMV0` | day 158 |
| P3 | day 159, 160 K252 + XMMMV0 | days 159–160 |

If P1–P3 cannot be retrieved this cycle → `PENDING_FETCH`; do not block C1–C3 on the frozen P0 file.

## 5. Classification of decoded Hz

Label as **COMPUTED from RAW instrument product**. Whether the ODF stores
raw Doppler or a navigation pseudo-residual is recorded as **UNADJUDICATED**
until a non-conjunction fixture with known engineering value is obtained.
