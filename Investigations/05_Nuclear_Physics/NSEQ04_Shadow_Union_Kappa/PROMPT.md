# NSEQ04 — Shadow-union binding: one-scale κ·ΔA

> **Status:** PRE-REGISTERED — 2026-08-09.  
> **Upstream:** NSEQ01 R7; NSEQ03 dual-tetra seating live.  
> **Class:** CALIBRATED(1) reproduction of the sequencer mass-defect path.  
> **Canon edits:** none.

## 0. Physics under test

Shared occlusion from the packed nucleus:

\[
\Delta A = \sum_i A_i - A_\cup,\qquad E_{\mathrm{bind}} \approx \kappa\,\Delta A
\]

with one scale κ (MeV/fm²). Enmeshment / shadow is the native defect; not an
IAEA charge-radius map.

## 1. κ policy (frozen before run)

| Item | Rule |
|---|---|
| Functional form | `BE ≈ κ·ΔA` through the origin (no intercept) |
| Estimator | least squares: `κ = Σ(BE·ΔA) / Σ(ΔA²)` |
| Sample | full sequencer ISO filter (`nd,nt≥0`, `be>0`) — one pass |
| Packing | live `packNucleus` (dual-tetra tritons); `dnn=1.45 R_p`, `coul=0.30` (sequencer defaults) |
| Light | sequencer `DEFAULT_LIGHT = [-0.4925, 0.80, 0.62]` |
| Shadow | sequencer `measureShadow` (canvas union of boundary disks) |
| Retune | **forbidden** mid-pass; no isotope subset refit |
| Excluded | IAEA RMS; κ(A) or κ(Z) families; volume-price revival |

## 2. Reports (not gates on κ magnitude)

| ID | Report |
|---|---|
| NSEQ04-C1 | Policy ledger published before instrumentation. |
| NSEQ04-C2 | Instrument runs full-table calibrate; κ finite, N≥200. |
| NSEQ04-C3 | Publish κ, R²(BE), R²(BE/A), mean relative \|err\| — label **CALIBRATED(1)**. |
| NSEQ04-C4 | Smoke: He-4, C-12, O-16, Fe-56, U-238 predicted BE vs measured (table). |
| NSEQ04-C5 | No `laws.hpp` edit; no IAEA. |

## 3. Status vocabulary

- **`SHADOW_KAPPA_REPORTED`** — calibrate completed under frozen policy.  
- Does **not** auto-promote to EMPIRICALLY SURVIVES; residuals decide follow-ups.
