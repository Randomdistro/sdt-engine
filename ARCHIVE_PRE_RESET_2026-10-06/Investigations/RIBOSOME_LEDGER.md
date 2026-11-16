
---

## CELL 3 — `Laws/Law_III_Convergent_Boundary_Pressure.docx` · extracted + read in full · CHAIN OF MATHEMATICIANS · PROPOSE-ONLY

- **M1 (Theorem 5, isotropy):** cone at depth d has d²δΩ sources × ε/(4πd²) each = εδΩ/(4π), d-independent; Σ_d → ϕ(n̂) = Φ/(4π). Algebra ✓. **Inherits Law II's 𝒩-crux** (the Σ_d = 𝒩 factor). PASS-as-algebra.
- **M2 (C3.1, Newton I):** F = ∮ϕ(n̂)n̂dΩ = (Φ/4π)∮n̂dΩ = 0 ✓. Isotropy → zero net force. PASS.
- **M3 (C3.2, scalar compression) — FACTOR-3 NAMING INCONSISTENCY.** C3.2 sets P_conv = Φ/(3ℓ_P³) (the u/3 factor), but Law I §6.8 sets P_conv = Φ/ℓ_P³, and Theorem 4 below uses Φ/ℓ_P³ under the same name. One symbol, two quantities. FLAG.
- **M4 (Theorem 4, occlusion force):** δΩ₁ = πR₁²/r² ✓; F = (π/4)(Φ/ℓ_P³)R₁²R₂²/r² ✓; 1/r² clean geometric (mechanism-free). But §4 silently swaps **P_eff** (5.225e31) for P_conv (2.46e48) — the ~17-order f, unstated. FLAG.
- **M5 (§4.1 Coulomb-H "validation") — IDENTITY, not validation.** F_occ(H)=8.23e-8 vs F_C=8.24e-8 (0.12%) ✓ arithmetic — but P_eff ≡ 4k_e e²/(πR_p²R_e²) is constructed EXACTLY so (π/4)P_eff R_p²R_e² = k_e e². So F_occ(H) ≡ k_e e² by algebra; 0.12% = rounding. Consistency-at-anchor, not prediction. FLAG (overclaim).
- **M6 (§4.2 He⁺ Z² scaling) — THE ERROR, and the CANON ROOT of tonight's engine Z² bug.** Law III: "force ∝ Z², F_occ(He⁺)=4×8.23e-8=3.29e-7; F_C(He⁺)=3.30e-7; agreement confirmed." **FALSE.** Real Coulomb on an electron from +Ze nucleus is F=k_e(Ze)(e)/r² = **Z·k_e e²/r²** (LINEAR in Z). At r=a0, F_C(He⁺)=2×8.24e-8=**1.65e-7 N**, not 3.30e-7 — Law III's value is exactly ×Z(=2) too large. The Z² came from radius-typing R_nuc ∝ Z (→R²∝Z²→F∝Z²) — the identical defect fixed in `laws.hpp` F_nuclear_electron tonight (Z·R_p → √Z·R_p; count-typed R²∝Z gives F∝Z, matching Coulomb). **The engine bug was inherited from Law III §4.2; "agreement confirmed" was manufactured by mis-stating the true Coulomb value.** STRONG — two-line-verifiable, canon-level, root of the engine defect. Propose: §4.2 → Z scaling (F(He⁺)=2×); §6 "three regimes" needs count-vs-radius typing for Coulomb at Z>1.

**Cell 3 verdict: Law III STRUCTURE sound** (isotropy→Newton I; occlusion→1/r² geometric; Newton III by symmetry) **but numerical §4 is where the faults live:** H "validation" is an identity (P_eff back-constructed); **He⁺ Z² is WRONG** (Coulomb is Z), mis-stated to claim agreement, and is the canon source of tonight's engine bug. Plus P_conv factor-3 naming (M3) and silent P_conv→P_eff swap (M4). Propose-only; He⁺ correction is the priority.
