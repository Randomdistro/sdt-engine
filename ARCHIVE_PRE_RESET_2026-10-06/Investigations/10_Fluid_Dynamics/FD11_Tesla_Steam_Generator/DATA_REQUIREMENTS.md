# FD11 — Data Requirements

> All external numbers are **MEASURED-INPUT** (steam properties, device performance, material
> allowables) — legitimate measured-unit inputs/tools, like spectral lines. The Tesla-turbine
> performance figures are the **convergence targets** to reproduce, never coefficients to borrow
> into the derivation. Internal SDT results (FD06 traction, FD02 ν, FD05 nozzle, PPT06) are *not*
> listed here — they come from the engine and upstream investigations.

## External inputs (MEASURED-INPUT)

| Quantity | Use in FD11 | Source |
|----------|-------------|--------|
| Steam properties `ρ, μ, h, s, c_s` vs `(P,T)` | Phase 1 `ν`→`b_opt`; Phase 3 choked `ṁ`, `V_j`, ideal enthalpy drop | **IAPWS-IF97** industrial formulation (or NIST steam tables) |
| Air & viscous-gas properties | Phase 4 viscosity-signature sweep (≥3 fluids) | NIST / standard property tables |
| Tesla's own turbine figures (disk gap ~0.4 mm steam / ~1.6 mm air; rotor efficiency claims; rpm) | Phases 1–3, 5 convergence targets | Tesla US Patent **1,061,206** (1913); Tesla's published test notes |
| Independent Tesla-turbine analyses (efficiency vs tip-speed ratio, torque–speed curves) | Phase 2 curve shape & peak `λ`; Phase 4 baseline | W. Rice, *"An Analytical and Experimental Investigation of Multiple-Disk Turbines"* (J. Eng. Power, 1965); subsequent ASME disk-flow literature |
| Modern replication / CFD datasets (multiple-disk turbine performance) | Phase 5 cross-check | Modern university / maker replication studies and CFD papers (cite specific dataset chosen) |
| Bladed-turbine efficiency-vs-Re baseline | Phase 4 contrast (`dη/dRe > 0`) | Standard turbomachinery texts (e.g. Dixon & Hall) |
| Material allowables: σ_yield/σ_creep, ρ, thermal expansion vs T (Ti-6Al-4V, Inconel 718, maraging C300, 316/347H, SmCo) | Phase 5 max-rpm hoop-stress bound (falsifier F5); gap stability | ASM Handbook / MMPDS / manufacturer datasheets |

## Internal inputs (from the engine / upstream — NOT external data)

- `law_VI::traction` (PPT06), `law_III` occlusion, `law_V` movement budget, `bridge` koppa — from `Engine/include/sdt/laws.hpp`.
- FD06 boundary-layer/no-slip result; FD02 `ν` model (ν∝√T, B16); FD05 choked/de-Laval nozzle; FD08 energy budget; FD01 Navier–Stokes root.

## Acceptance notes

- Record the exact `(P₀,T₀)` working state with every reported performance number (efficiency and `b_opt` depend on it).
- Tag the single permitted loss coefficient (if used) **CALIBRATED(1)** and state which dataset fixed it (R2 ledger).
- Phase 4 is the discriminator: the viscosity-signature sign must be **predicted before** unsealing the multi-fluid data (R1).
