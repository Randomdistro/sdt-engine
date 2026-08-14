# GD06 — Technical Report (RUN 1, 2026-07-13)
### Occlusion-as-solid-angle ledger, calibrated on the solar census (H6)

> Tool: `gd06_run.py` (standalone Python; no dependency-traced constant enters the *derivation* of Θ — constants used only to convert to OBSERVED SI for comparison). Data: H6 solar census (verified) + standard body parameters. **Triple verdict at foot.**

## 1. Inputs (all OBSERVED or geometric)
Solar: R_⊙=6.957×10⁸ m, N_b=1.189×10⁵⁷, L_⊙=3.828×10²⁶ W. CMB: u=4σT⁴/c at T=2.725 K. ℓ_P=1.616×10⁻³⁵ m. Body ladder parameters standard (neutron star 1.4 M_⊙/12 km, bulge 10¹⁰ M_⊙/1 kpc, cluster 10¹⁵ M_⊙/1 Mpc, etc.).

## 2. H6 census (re-verified)
N_spa=V_⊙/ℓ_P³=**3.341×10¹³¹**; N_surf=A_⊙/ℓ_P²=**2.328×10⁸⁸**; gear=R_⊙/3ℓ_P=**1.435×10⁴³**. ε/spation=u·c·ℓ_P²=3.267×10⁻⁷⁵ W; total=1.091×10⁵⁷ W; **per baryon=0.918 W**; engagement=(L_⊙/N_b)/0.918=**3.507×10⁻³¹**.

## 3. The occlusion ladder — depth redshift z_d = ϟ/r (dilute occlusion limit)
| Body | z_d | cz | regime |
|------|-----|----|--------|
| proton @ R_p | 1.48×10⁻³⁹ | 4.4×10⁻³¹ m/s | dilute |
| Ca nucleus @ a₀ (point) | 9.4×10⁻⁴³ | — | dilute |
| **Sun @ surface** | **2.12×10⁻⁶** | **636 m/s** | dilute (anchor ✓) |
| red giant (1 M_⊙,100 R_⊙) | 2.1×10⁻⁸ | 6.4 m/s | dilute |
| white dwarf | 1.3×10⁻⁴ | 38 km/s | mild |
| **NEUTRON STAR** | **0.172** | 5.2×10⁷ m/s | **DENSE** |
| stellar BH horizon | 0.500 | — | DENSE |
| **galaxy BULGE (10¹⁰,1kpc)** | **4.79×10⁻⁷** | **143 m/s** | **dilute** |
| **galaxy CLUSTER (10¹⁵,1Mpc)** | **4.79×10⁻⁵** | **14.3 km/s** | dilute |

**Occlusion reproduces the weak-field gravitational redshift z_d = ϟ/r exactly** (scaling n R² ∝ M/R confirmed; the bulge/Sun ratio 0.227 is purely geometric). The **dense** branch (z_d ≳ 0.1, where "redshift = motion" and where occlusion can diverge from GR) begins at **neutron-star density**, not before.

## 4. Node verdicts (this run)
- **GD06 core (instrument):** the solid-angle instrument recovers ϟ/r in the dilute limit and saturates (g→2, z_d→O(1)) only at contact/neutron-star density. Instrument **CONFIRMED**; it is the right operation. Class: NATIVE on the recovery, DEGENERATE-with-GR at dilute scales (recovers known physics), **new physics only in the dense branch + the mass-free/geometric provenance.**
- **XSD-A (field shift):** DEFERRED — needs isotope-shift data; the effect is a finite-size penetration term (δ⟨r²⟩), not the point-source z_d above.
- **XSD-B (σ_occ geometrization):** the Sun anchor requires σ_occ=**1.561×10⁻⁵³ m²/baryon** = 7.02×10⁻²⁴ of πR_p². This does **not** match the transfer function f=2.13×10⁻¹⁷ (off by 3×10⁻⁷) nor the engagement 3.5×10⁻³¹ cleanly. **σ_occ geometrization = OPEN → DEFER to EMC01/electropause (XSD-B2).** The make-or-break is unresolved.
- **XSD-C (bulge crux):** **DILUTE.** cz=143 m/s = **0.072% of the 200 km/s rotation.** Depth redshift is a *real, predictable ~143 m/s systematic* (center-systemic and σ channels) but **does NOT corrupt the disk rotation curve.** The dense-bulge hypothesis is **not supported at bulge scale.** (Honest miss vs the "redshift=speed" expectation.)
- **XSD-D (cluster):** cz=14.3 km/s vs measured Wojtak+2011 ~10 km/s — **CONSISTENT**, a genuine cross-check the mechanism passes. But it equals ϟ/r = the GR value → **DEGENERATE with GR** at this order (not yet a discriminating prediction).

## 5. Triple verdict
> **Prompt completion: B** (instrument built + run end-to-end; two children DEFERRED on data). **Physics class: CONVERGENCE/DEGENERATE** at dilute scales (recovers ϟ/r), NATIVE-pending in the dense branch. **Cross-scale: UNDETERMINED** — σ_occ geometrization open, so the 30-order lever is not yet closed. **σ_occ: DEFERRED-to-EMC01.**

## 6. What this run earned, honestly
1. The occlusion instrument is correct and mass-free, and it **recovers the gravitational redshift** across 40 orders of z_d (proton→BH) with one relation.
2. The **bulge is dilute** (143 m/s) — the disk rotation is not a redshift artifact; that hypothesis is quantitatively killed, but the 143 m/s systematic is a real, testable prediction in the clean (σ/systemic) channels.
3. The **cluster prediction (14 km/s) matches the measured value** — consistency, though degenerate with GR.
4. The **σ_occ geometrization is the live make-or-break** and is unresolved; the H6 transparency ledger (3.5×10⁻³¹, 1.6×10⁻¹⁸, f≈2×10⁻¹⁷) is the target to geometrize (XSD-B/EMC01).
5. New physics lives in the **dense branch** (neutron stars) and the **provenance** (geometry not GM), not in the dilute galactic redshift.
