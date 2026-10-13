# APS11 Pre-registration — Lamb as pair-breaking occupancy

**Date:** 2026-08-13  
**Author:** J. C. Harvey, Melbourne (ontology: Lamb = cost of breaking a pair).  
**Direct execution.** **Canon edits:** none.  
**Upstream:** PPT08 koppa target (OPEN amplitude); APS04 quadrupole **0.761 MHz** (nuclear-geometry term, not the bulk interval); FLM14-P2 geometry precondition PASS, dwell DEFER.  
**Forbidden:** APS04 1051.8 MHz literal; B04 `k_Lamb=12.7227`; QED α⁵ series as SDT derivation; 137ⁿ fishing; subtracting APS04 from the hold-out to improve a fit.

## ⓪

1. **What don't we know?** Whether the measured nS–nP intervals are the occupancy cost of an incomplete dyad (paired S-form) versus an unpaired plane (P-form), and whether one geometric rule hits the whole seat table.
2. **Why it matters?** PPT08 amplitude is OPEN. Pair-breaking names the two forms. If the rule fails the table, Lamb is still only a koppa re-expression.
3. **How?** Freeze OBSERVED intervals. Re-express via koppa (Phase A). Score a declared candidate matrix (Phase B) in one pass.
4. **Wrong if?** Sign requires 2S *lower* than 2P (complete-dyad binding); or no candidate hits 3/3 of {H n=2, H n=3, He⁺ n=2} at rel<0.10; or the only hit is H n=2 inside the already-logged R_p/3 cluster.
5. **Done when?** Dual verdict: ontology (sign) + table (magnitude). No EMPIRICALLY SURVIVES on H n=2 alone.

## Ontology (frozen)

| Form | Seat | Pair content |
|---|---|---|
| S (dyad) | two-seat pair geometry | In H, one electron ⇒ **incomplete dyad** (vacancy strain) |
| P (plane) | unpaired trigonal/plane | No vacancy |

**S1 (EXCLUDED if 2S lies above 2P):** complete dyad is more bound ⇒ 2S lower.  
**S2:** incomplete-dyad strain ⇒ **2S higher**. Measured 2S₁/₂ > 2P₁/₂ is the sign test.

Lamb is **not** ionization (Be/Mg eV breaking fee). It is the same-*n* occupancy difference.

APS04 +0.761 MHz is a **named nuclear-geometry addend**, not the pair-break quantum. Hold-outs are raw intervals.

## OBSERVED hold-outs (frozen; not inputs to formulae)

| ID | Interval | Value | Provenance |
|---|---|---|---|
| H2 | H, n=2, 2S₁/₂–2P₁/₂ | **1057.8450(29) MHz** | de Beauvoir et al., EPJ D 12, 61 (2000); `laws.hpp` 1057.845 |
| D2 | D, n=2, 2S–2P | **1059.2341(29) MHz** | same |
| H3 | H, n=3, 3S–3P | **314.819(48) MHz** | Fabjan & Pipkin, Phys. Rev. A 6, 556 (1972) |
| He2 | He⁺, n=2, 2S–2P | **14041.13(17) MHz** | van Wijngaarden et al., Can. J. Phys. (2003) |
| H1 | H, 1S Lamb L(1S) | **8172.840(22) MHz** | de Beauvoir et al. (2000) — discriminator, not 1S–1P |
| μH | μp, 2S–2P whole | **202.3706(23) meV** | CREMA; raw whole interval |

H2–He2 are the **PPT08 table**. H1 and μH cannot promote a candidate that failed the table.

## Phase A (not scored as derivation)

Koppa map, hydrogenic seats (reduced mass μ):

```
r_n = a₀ n² / Z · (m_e/μ)
v_n = Z α c / n          (same μ in energy via E_n = Ry (μ/m_e) Z²/n²)
ΔE = h f
Δv = ΔE / (μ v_n)
Δr/r = −2 Δv/v  ⇒ |Δr|
```

Instrument gate: H2 must recover PPT08 **0.2722 fm** and **0.7034 m/s** within 1%.

## Phase B candidates (declared; one pass; no retune)

Node length δ, two pre-registered geometry choices (both reported; not mixed mid-pass):

- δ_A = R_p/3  (trefoil node; `R_p` from `laws.hpp` measured 0.8414 fm)
- δ_B = R_p

| ID | Rule | Notes |
|---|---|---|
| L1 | Δr = δ | constant seat offset |
| L2 | Δr = δ · (n/2) | linear in n |
| E1 | ΔE = \|E_n\| · (δ / r_n) | fractional energy = node/orbit |
| E2 | ΔE = 2 \|E_n\| · (δ / r_n) | koppa ΔE = μ v Δv with Δv/v = δ/r |
| E3 | ΔE = \|E_n\| · (δ / a₀) | node vs Bohr, no 1/r_n |
| HD | f_D = f_H · (μ_D/μ_H) | reduced-mass only; CONVERGENCE cap |
| RIV | α⁵ m c² Z⁴/n³ leading (no logs) | **rival column**; not SDT |

E1/E2/L1/L2/E3 each run at δ_A and δ_B (12 SDT cells + HD + RIV). Look-elsewhere: 12 cells declared here.

## Gates

| Gate | MATCH | FAIL |
|---|---|---|
| V1 instrument | H2 koppa Δr, Δv within 1% of PPT08 | >1% |
| G_sign | S2 (2S higher) | S1 |
| G_line | rel < 0.10 vs that interval | rel ≥ 0.10 |
| G_table | G_line MATCH on **H2 and H3 and He2** for the **same** cell | any of the three miss |
| G_HD | rel < 0.10 on D2 from HD rule | miss (cap CONVERGENCE) |
| G_μ | E1/E2 μH rel < 0.10 vs 202 meV | expected FAIL (APS04: bulk ≠ quadrupole scaling) |

Native amplitude: **G_table PASS** on one cell, no per-line freedom.  
H2-only MATCH inside the R_p/3 cluster: **CONVERGENCE / look-elsewhere**, not native.  
G_sign PASS + G_table FAIL: ontology survives; magnitude still OPEN.

## Non-claims

- Not a replacement for `lamb_shift_measured_MHz` in canon.
- Not ionization pair-break (eV).
- Not NSEQ occupation MeV.
- Not FLM14 dwell exponent.
