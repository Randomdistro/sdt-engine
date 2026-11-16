# CM01 — Verdict: Superconductivity as Phase-Locked Vortex Pairs

**Author:** J. C. Harvey, Melbourne · **Run:** 2026-07-04 · Tool `cm01_superconductivity.cpp` →
`cm01_results.txt` (MSVC `/std:c++20 /O2 /utf-8`, real stdout; gates pre-committed in `RUN_LOG.md`).

## Headline

Three earned numbers and one clean branch-kill:

1. **ρ_Cu(300 K) = 1.03e-8 Ω·m vs 1.68e-8 measured (1.64×), with τ never touching measured σ.**
   Chain: ion equipartition ⟨u²⟩ → occlusion cross-section π⟨u²⟩ → mfp 64 nm (vs 39 nm measured)
   → wake-packing carrier speed from n_e alone. This is the honest normal state CM02 owed; the
   CM02 circularity (τ from σ, then σ "predicted") is structurally impossible in this chain.
   Linear-in-T resistivity falls out of equipartition (ratio 2.0000 exact).
2. **λ_L(Al) = 12.5 nm vs 16 nm; λ_L(Nb) = 22.5 nm vs 39 nm** (both inside the committed 2× gate)
   from zero-drag carriers + Ampère — classical EM, no gauge machinery.
3. **Isotope exponent −0.5000 exactly** (anchor: Hg 0.50 ± 0.03), from T_c ∝ lock ceiling ℏω_D
   with M entering only through ω_D = √(k_spring/M). Conditional on the ceiling premise (named).
4. **The deformation-well ("polaron") pairing branch is DEAD as a T_c closure** — run to death on
   schedule: the well depth E_pol = F²/2k_spring comes out material-blind (0.12–0.18 eV for
   Cu/Al/Nb/Pb) while measured η = T_c/θ_D spreads 24× (0.0028–0.0685). A material-blind well
   cannot set a material-graded T_c. NP17 is the death-knell precedent: SDT binding is
   seat-sharing geared down, never a static well.

## What survived P2 (the mechanism map)

The **retardation seat** is real and earned: a drifting W=1 vortex deposits compression that
relaxes over 2π/ω_D, so the like-handed partner's seat sits at r_seat = v_pack·2π/ω_D =
**220–830 nm — 790–2380 lattice spacings behind**, where direct handed repulsion has fallen to
~1/30 of the well scale (window OPEN for all four metals). That answers WHY pairs are possible
and WHY they are enormous compared to the lattice (ξ ≫ defect scale — the committed inequality).
WHY exactly two: the seat is a two-body configuration (one wake, one seat); a third like-handed
vortex has no coherent seat in the pair's combined wake — **argued, not proven; exclusivity OPEN.**
The binder itself is the gear-lock on the FLM14 constraint channel (ADJ-1); its depth (η) is the
one number this investigation could not close.

## Zero resistance (the FLM14 mechanism, stated as machinery)

A locked pair-condensate is a gear-locked cluster: constraint propagates uncapped inside it
(FLM14 ADJ-7), so a defect's kick is redistributed cluster-wide within a tick — the defect faces
the whole cluster's reorganisation cost, not one carrier's. Dissipation requires breaking the
lock; below the lock temperature there is no drag channel. Quantified proxy: single-carrier drag
suppression (d/ξ_seat)^{3/2} = 4.5e-5 (gate <1e-3). Meissner = EMC03 swirl expulsion by the
rigid condensate; λ_L numbers above.

## Anti-tautology ledger

- **Φ₀ = h/2e and κ_pair = h/2m are printed IDENTITY** — definitional once the carrier is the
  2-body lock. Not counted as passes. The earned content is the divisor-as-body-count argument.
- η = T_c/θ_D printed OBSERVED, never fitted. CALIBRATED used: 0 of 0.

## FAILURE RECOVERY (§D — the OPEN η magnitude, and the dead P2 branch)

1. **Why:** the only native well computed (deformation) is material-blind; measured coupling
   spreads 24×. No SDT quantity in this run grades materials for lock depth.
2. **Recoverable?** Plausibly — the gear-lock depth needs the FLM14 constraint-channel coupling
   strength per material (how well the local lattice gears the two wakes), which is exactly the
   quantity FLM14 is building.
3. **Unaccounted:** channel-specific gearing (why Pb locks 24× harder than Al relative to θ_D).
4. **Errored premise:** "the compression-wave well depth is the lock energy." The well is where
   the lock *forms* (seat), not what sets its *depth*.
5. **Freedom:** the gear-engagement number of the constraint channel (FLM14's coupling profile).
6. **Accounted natively?** Named native quantity under active construction (FLM14) — not a knob;
   until it lands, η stays OPEN. Re-open condition: FLM14 delivers a per-material engagement
   number; then T_c = η(FLM14)·θ_D is a zero-fit prediction and this verdict upgrades.
7. **Cascade:** YES — shares its root with CM05's T_λ magnitude and SCT's "what sets B":
   **ROOT-B, the lock-depth / engagement-magnitude closure.** Isotope exponent and λ_L do NOT
   depend on it (they survived independently).

**Recovery grade: PARTIAL.**

## Generative questions logged

1. Is η = T_c/θ_D computable as a gear-engagement efficiency of the FLM14 channel (Pb soft-lattice
   high-engagement vs Al stiff-lattice low-engagement — sign already right in the data)?
2. Does the seat distance (220–830 nm) predict the measured ξ ordering Al > Nb (ours: seats near-equal,
   measured ξ 1600 vs 38 nm — the *spread* again points at ROOT-B)?
3. Three-body lock: is the no-coherent-seat argument provable as a Law VI winding obstruction?

---

> **Prompt completion C · Physics class CONVERGENCE (structure earned; magnitude OPEN) ·
> Recovery PARTIAL · Cascade root ROOT-B (lock-depth magnitude — shared with CM05 T_λ, SCT B)**
