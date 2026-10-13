# RUN_LOG — PM07 (MHD Coupling to the Fluid Suite)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05 · Written BEFORE any code.

## Pre-Run Commitments — PM07

- Prompt completion target: **C** (prompt expects C: assembly with named orphans).
- Physics class hoped: NATIVE for frozen-in-as-counting (the one place a real theorem is earnable);
  CONVERGENCE for the assembled equation set; the bijection gate is expected to produce **named
  orphan terms**, not a clean bijection — committed now.
- CALIBRATED budget: 0. Native units in the sim. No primitive B (the advected objects are wake
  quanta κ, PM01); no Ohm postulate (slip = FD02 diffusion kicks); no magnetons.
- The deliverable is the explicit **term-by-term coupling map** MHD ↔ {FD01, FD02, PM01, PPT06,
  GOM06} with every un-earned coefficient named — the FD01 house style (its F1 bijection).

### Phase thresholds (committed before run)

| Phase | Gate | Threshold |
|---|---|---|
| P1 | bijection table | every ideal-MHD momentum+induction term mapped to a named FD/PM primitive OR listed as a **named orphan**; zero silent leftovers. (Expected orphans, committed: swirl↔momentum coupling gain = HG-1; ⊥ magnetic-pressure closure; Ohm/η ≡ FD02 as identification.) |
| P2 | frozen-in (counting sim) | 2-D: 10⁴ wake quanta + material loop (512 markers), both advected by one smooth incompressible flow (RK4). η=0: enclosed-count drift ≤ 0.5% over the run (expected exactly 0). η>0 (Gaussian kicks √(2ηdt), carriers only): ensemble-mean leak rate ∝ η — log-log slope **1.0 ± 0.3** over η ∈ {3e-4, 1e-3, 3e-3, 1e-2}, 12 seeds each, window T=1 (quasi-static; Fick regime) |
| P3 | Alfvén assembly | v_A = (swirl tension / lattice inertia)^½ ASSEMBLED (form only, no numeric claim); the **2:1 tension-to-energy-density ratio** shown to match between Maxwell stress and a directed relay stream (dimensionless structural check — flagged as arithmetic, not discovery) |
| P4 | stress projection | ∥ tension ρ_a u² ↔ B²/µ₀ and ⊥ pressure: the ⊥ closure requires wake isotropic pressure = FULL energy density (w=+1), NOT the radiation u/3 of FD05 — this mismatch is REPORTED as an orphan, not smoothed |

### Forbidden retroactive changes
Annotate-and-claim-assembled (the trivial path the prompt names); import the MHD set or quote
v_A = B/√(µ₀ρ) as derived; hide the ⊥-closure mismatch; widen the slope gate; magnetons.

## Run record (filled after execution)
- See `pm07_results.txt`, `PM07_VERDICT.md`.
