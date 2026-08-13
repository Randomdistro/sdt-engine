# PSP02 — Pressure-depth gradient traversal ↔ radio observables

> **Status:** PRE-REGISTERED — 2026-08-12.  
> **Class:** SDT claim investigation (depth gradient → oscillation-ratio map).  
> **Upstream:** PSP01 perihelion depth prediction; GOM22 `c_far` / Shapiro spine;  
> GOM_DAT Cassini radio path (method heritage — different mission).  
> **Canon edits:** none.  
> **Ontology:** pressure depth \(z=\Omega/r\); radio = oscillation÷oscillation;  
> no sunward-force claim in this investigation.

## 0. Objective

Map Parker Solar Probe’s **traversal of the solar pressure-depth gradient** to
**predicted radio-signal differences**, then compare:

1. **Predicted** depth / \(c_\mathrm{far}\) / rate-ratio / delay-rate along the
   geometric path (from public ephemeris).
2. **Observed** DSN radiometric series (Doppler / range / carrier), if/when
   obtainable in primitive form.
3. **Onboard path** (SPICE / reconstructed trajectory) vs **apparent path**
   implied by uncorrected radiometrics (where both exist).

## 1. Hard data fact (committed before fetch)

| Product | Public? | Role |
|---|---|---|
| SPICE / CDAWeb ephemeris, Horizons vectors | **Yes** | geometric path \(r(t),\mathbf{v}(t)\) |
| FIELDS / SWEAP science CDF | **Yes** | in situ plasma (separate from DSN carrier) |
| DSN TRK-2-34 TNF / ODF Doppler–range | **Restricted** (authorized DSN/JPL delivery) | primitive radio observables |

**This investigation does not pretend TNF is already in-repo.** Phase A runs on
public path only and freezes predicted ledgers. Phase B is gated
`PENDING_DATA` until TRK-2-34 / equivalent is staged under `Datasets/`.

## 2. Claims

| ID | Claim |
|---|---|
| PSP02-C1 | Enc-22 (or nominated) perihelion arc ephemeris obtainable; \(r_\min\) within 1% of 9.86 \(R_\odot\). |
| PSP02-C2 | Along-track ledger: \(z(t)=\Omega/r(t)\), \(c_\mathrm{far}(t)\), \(\dot z\), one-way Shapiro marker — COMPUTED, \(\Omega\) frozen (no fit). |
| PSP02-C3 | Geometric Earth–PSP range-rate Doppler COMPUTED (classical LOS only). |
| PSP02-C4 | Depth-gradient radio terms (rate ratio \(z_\mathrm{spec}\), delay-rate from \(c_\mathrm{far}\)) published separately from C3 — never fitted to TNF. |
| PSP02-C5 | If TNF present: decode Doppler/range; compare obs − geom to C4 prediction class (pre-registered tolerance). |
| PSP02-C6 | If TNF absent: status `PATH_LEDGER_READY__RADIO_PENDING_DATA` — not EMPIRICALLY SURVIVES. |
| PSP02-C7 | No sunward-accel claim; no γ fit; no plasma scintillation model as SDT depth. |

## 3. Frozen inputs

| Symbol | Value | Class |
|---|---|---|
| \(\Omega_\odot\) | 1476.625 m (B39 / GOM22 working) | DERIVED IC |
| \(c\) | 299792458 m/s | MEASURED-INPUT |
| \(R_\odot\) | 6.957×10⁸ m | MEASURED-INPUT |
| Formulas | `depth_closure::{depth,c_far,clock_rate,z_spectral,shapiro_delay}` | canon |

## 4. Phases

**P0 — Data census.** List URLs / access class for SPICE, Horizons, TNF.  
**P1 — Path ledger.** Build \(r(t)\) for Enc-22 ± window; C1–C4.  
**P2 — Radio ingest.** Only if TNF/ODF staged; else C6.  
**P3 — Apparent vs onboard path.** Residuals only with P2 data.

## 5. Forbidden

- Fitting \(\Omega\) to PSP Doppler.  
- Calling FIELDS plasma bursts a test of \(\Omega/r\).  
- Claiming EMPIRICALLY SURVIVES without primitive radiometrics.  
- Mixing circumference/radius inconsistently (OM02).
