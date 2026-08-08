# GOM32 — ODF Type-12 Observable Unit-Path Adjudication

> **Status:** PRE-REGISTERED — 2026-08-08.  
> **Upstream:** GOM31 MULTIDAY_DECODE_PASS.  
> **Canon edits:** none.  
> **Notation:** SDT capital **K** = c-boundary radius. In DSN/ODF labels,  
> `K` means **transponder turnaround ratio** — never equate the two.

## 0. Objective

Adjudicate whether Orbit Data Group Items 4–5 (`obs_Hz`) are:

- **(A)** Engineering Doppler observable in hertz (count-rate compressed /
  bias-model form), or  
- **(B)** Navigation ODP residual (observed − predicted), typically µHz-class
  in published Cassini solar-conjunction analyses.

No light-time residual, no solar **K** fit, no γ fit.

## 1. Claims

| ID | Claim |
|---|---|
| GOM32-C1 | Paired PDS3 label states a Doppler **observable** equation from Doppler counts and bias/frequency model terms (not observed−predicted). |
| GOM32-C2 | Label DATA TYPE 12 is titled "Two-way Doppler; Hertz"; FORMAT ID on frozen K252 rows is 2. |
| GOM32-C3 | TRK-2-18 reconstruction identity `Doppler[Hz] = Observable + Fbias` applies to Items 4–5 + 18–19 (documented). |
| GOM32-C4 | Magnitude gate: frozen SCE1 type-12 `|obs|` medians are ≥ 1 kHz and ≤ 10 MHz — consistent with ODF engineering Doppler, inconsistent with µHz-class ODP residuals. |
| GOM32-C5 | External unpack fixture: published MESSENGER ODF example Doppler magnitude is ≥ 1 kHz (same product class). |
| GOM32-C6 | No SDT solar-K fit; no residual formed. |

## 2. Decision rules

1. C1 FAIL if label Item-4 text lacks the count-interval formula or asserts Items 4–5 are ODP residuals.  
2. C2 FAIL if type-12 unit string is not Hertz or FORMAT ID ≠ 2 on P0 K252.  
3. C4 FAIL if any CORS_0021 **K252** type-12 median `|obs|` is outside `[1e3, 1e7]` Hz.  
4. C5 FAIL if documented MESSENGER example `|Doppler| < 1e3` Hz.  
5. Passing C1–C5 ⇒ classify field as **ENGINEERING_DOPPLER_HZ**; residual path remains a separate reconstruction (predicted Doppler or delay), not a unit-path question.

## 3. Admissible inputs

- Local paired labels under CORS_0021.  
- GOM31 stdout / re-decode of local ODFs.  
- PDS Radio Science TRK-2-18 documentation (Rev E appendix A.2; odf_unpack MESSENGER example).  
- Not admissible: Bertotti γ, Fomalont γ, or any fit used as SDT solar **K**.

## 4. Frozen fixture numbers (pre-registered)

MESSENGER one-way Doppler from PDS `odf_unpack` example (bits 65–128):  
`−382738.663803100` Hz.  
Source: https://pds-geosciences.wustl.edu/radiosciencedocs/urn-nasa-pds-radiosci_documentation/DSN_TRK-2-18/odf_unpack.pdf
