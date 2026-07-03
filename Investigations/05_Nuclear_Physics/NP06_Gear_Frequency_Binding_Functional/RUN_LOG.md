# RUN_LOG — NP06 (CQ-50): Gear-Frequency Binding Functional

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Written BEFORE any tool code.**
> Engine: `#include <sdt/laws.hpp>` only. Sealed set: `../NP05_Gate_G1_Price_of_Displacement/sealed/answers.json`
> (AME2020; per its own executor_note the seal is procedural — predictions are committed HERE
> before any comparison is printed).

## Pre-Run Commitments — NP06

- Prompt completion target: B (deliverables D1–D6 folded into RUN_LOG + tool + VERDICT;
  logged as ADJ-001, format-only deviation)
- Physics class hoped: NATIVE; honest floor accepted: KILLED with successor named (R4: the
  kill report is a first-class deliverable)
- CALIBRATED budget: **0** for the gate Gω (a κ chosen from data is CALIBRATED(1) and can
  only be used to *demonstrate failure shape*, never to pass)
- Engine namespaces: `measured`, `law_VI::winding` (rim identity), `coulomb_identity`
- Trivial-identity guard (R5, in force): any route where Δω reduces to Δ(mc²)/ℏ is VACUOUS
  and rejected. The tool prints ℏΩ_rim = m_p c² once, flagged FORBIDDEN-IDENTITY, to show
  the trap explicitly.

## D1 — Committed mesh-contact graph (CQ-32 clusters, ring contact s = 2R; blind to energies)

| System | Rotors | Contacts (bonds) | Note |
|--------|--------|------------------|------|
| H₂ | 2 | **0** at kinematic contact (protons at 1.4 a₀ = 0.74 Å ≫ 2R_p: rims do NOT touch) | the anchor's committed prediction under a *contact* mesh is ε = 0 |
| d | 2 | 1 | dimer |
| t / h | 3 | 3 | triangle |
| α | 4 | 6 | tetrahedron (even mesh, fully lockable) |
| ⁶Li | 6 | 9 | α(6) + d(1) + 2 α–d contacts |
| ⁹Be | 9 | 14 | 2α(12) + n bridging 1+1 (α–α not in contact) |

## D2 — Committed derivation rule for κ_geom (the make-or-break step)

κ_geom must come from the no-slip coupled-rotor mesh, parameter-free. Inventory of ALL
dimensionless quantities available in the committed contact geometry (declared now):

1. overlap depth δ/R — **= 0** at ring contact (s = 2R exactly);
2. contact-arc fraction — **= 0** (tangent point);
3. relative axis-angle cosines — **O(1)**, bounded by 1;
4. winding ratio (W+1)/(W'+1) — **= 1** (identical rotors);
5. rim-speed ratio — **= 1**.

**Decision rule (committed):** a rigid no-slip constraint locks phase but stores no energy;
a frequency SPLIT requires a stiffness U(Δφ), and none of the inventory items supplies an
energy scale. If, after honest attempt, every derivable κ is either 0 or O(1) — i.e. nothing
emits the ~10⁻³ (nuclear) and ~10⁻⁹ (H₂) couplings simultaneously — then **κ_geom is NOT
derivable at CALIBRATED(0)** and **Gω is DEAD at the derivation stage**. The remaining
numeric phases then run as *failure-shape demonstrations only*.

## Committed predictions (before any comparison is printed)

- **P-anchor (H₂):** contact-mesh prediction ε(H₂) = 0 (no contact). Target 4.52 eV
  (OBSERVED, stated in the PROMPT itself). Gate: ±15% → 0 vs 4.52 eV = structural FAIL.
- **P-shape (nuclear, demonstration, CALIBRATED(1) declared):** set ε_bond from the deuteron
  (ε = B_d/1 bond), then every other system is bond-count × ε: t,h = 3ε; α = 6ε; ⁶Li = 9ε;
  ⁹Be = 14ε; the 8 Q-values follow by ledger. Gate ±15% each (scored for the record; a pass
  here would STILL not pass Gω, which demands CALIBRATED(0)).
- **P-required (reverse ledger):** κ_req = ε_bond/(m_p c²) per system, labelled
  REQUIRED-NOT-DERIVED; report the spread d→α and d→H₂.

## Kill condition (verbatim from PROMPT §5, in force)
If Gω fails after κ_geom is honestly derived (or shown underivable): log the kill, sort
residuals, name the successor. **Successor named now, before the run:** the NP17
shared-electron Coulomb well — it supplies exactly what the kinematic mesh lacks (an
interaction scale αℏc and a range 1/r) and has already paid the deuteron (−1.06%).

## Forbidden retroactive changes
Inventing a stiffness to rescue κ; promoting the CALIBRATED(1) shape demo to a pass;
widening ±15%; using ℏΩ_rim = mc² anywhere load-bearing.

## Planned outputs
`np06_gear_frequency.cpp` → MSVC → `np06_results.txt` (redirected) → `NP06_VERDICT.md`
(carries D2–D6).
