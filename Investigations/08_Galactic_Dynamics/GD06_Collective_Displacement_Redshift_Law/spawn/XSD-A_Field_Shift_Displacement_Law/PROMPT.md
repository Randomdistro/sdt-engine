# XSD-A — The Field Shift as δΘ: h′,h″ of the sky-coverage law from the King plot
### (spawned by GD06 · feeds Phase 2 · home 02 · REBUILT on the solid-angle instrument 2026-07-13)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPAWNED-SPEC (rebuilt). **Inherits:** GD06 The Two Rules + §③; `HUNTER_PROTOCOL.md` §A–§K.
> **Engine:** `laws.hpp` for OBSERVED comparison only. **No whitelisted constant in the derivation. No m as input. No "charge radius" → nuclear boundary.**

## ⓪ Five questions
1. **What don't we know?** — The **slope h′(0) and curvature h″(0)** of the dimensionless sky-coverage law z_d=h(Θ) in the **dilute** branch, read from the isotope **field shift** (= the change in the sky-fraction the nucleus subtends at the electron) and its **King nonlinearity**.
2. **Why?** — The nucleus covers a *tiny* sky-fraction at the electron (Θ_nuc≈π R_nuc²/a₀²≈10⁻¹⁰), so the field shift is the cleanest Hz-precision measurement of h near Θ→0 anywhere in physics. GD06's 30-order extrapolation is anchored here.
3. **How?** — Invert δν_FS=F_i·δ⟨r²⟩ into δz_d/δΘ_nuc → h′(0); fit the King second coefficient → h″(0); demand h′ transition-independent (the bridge test).
4. **Wrong if?** — h′ depends on the electronic transition ⟹ the field shift is **not** δΘ ⟹ **GD06 bridge KILLED**; or the King NL is fully a nuclear ⟨r⁴⟩ moment with no h″ residual.
5. **Done when?** — h′(0),h″(0) with covariances for ≥5 isotope chains ×≥2 transitions, transition scatter < FS error, h″ sign pre-committed and matched.

## 1. Framework (solid angle, movement-only)
Θ_nuc(𝐱_e) = sky-fraction the nuclear boundary covers at the electron's position = (1/4π)·(subtended solid angle of the nucleus). For R_nuc≪orbit, Θ_nuc ≈ (1/4)(R_nuc/r_orbit)² ∝ ⟨r²⟩ (a **pure geometric angle**, no mass). A bigger/heavier isotope covers slightly more sky ⟹ the electron's emission climbs out through slightly more coverage ⟹ a frequency shift — the **field shift is δz_d = h′(0)·δΘ_nuc**, a rate-at-a-distance, not an "energy level." Thus
$$\frac{\delta\nu^{A,A'}_i}{\nu_i} = h'(0)\,\delta\Theta_\text{nuc} = h'(0)\cdot\frac{d\Theta}{d\langle r^2\rangle}\,\delta\langle r^2\rangle \;\Rightarrow\; F_i \propto h'(0)\ \text{(same for every transition } i\text{).}$$
That constancy IS the bridge test. **King plot:** transition-2 vs transition-1 mass-scaled shifts, slope F₂/F₁; the **nonlinearity = h″(0)** (curvature of the coverage law near Θ→0), to be separated from a genuine ⟨r⁴⟩ moment.

## 2. Method (gated)
- **P1** Pull isotope-shift data (Ca 40–48 incl. ⁴⁶ couplet, Yb 168–176, Cd, Sr, Ba). Tag OBSERVED.
- **P2** Build the two-transition King plot per chain; extract F_i (→h′(0)) + mass-shift; **metric:** h′(0) transition-scatter < FS error ⟹ bridge holds.
- **P3** Fit King NL; separate SDT h″(0) from ⟨r⁴⟩ using ≥3 transitions (over-determined); pre-commit h″(0)>0 (coverage stiffens).
- **P4** Deliver h(0),h′(0),h″(0) + covariance to GD06 Phase 2 and to XSD-B (which needs h′(0) to fix the form of h).

## Dependency map
| Item | Where | Enters as | Live |
|---|---|---|---|
| δν, F_i, K_i, δ⟨r²⟩, ⟨r⁴⟩ | isotope-shift literature | OBSERVED calibrator | ⚠ pull |
| Θ_nuc(⟨r²⟩) geometry | GD06 §③ (pure angle) | δΘ definition | ✔ |
| King-plot campaign (Ca/Yb/Cd/Sr/Ba) | [[project_kingplot_movement_law]] | method + prior | ✔ |
| r_orbit (electron position) | geometric; NOT a₀=ℏ/(m_e cα) if that launders m_e | dilute lever | ⚠ Rule-2 check |

## ⑧ Falsifiers
| Test | Predicted | FAIL → root |
|---|---|---|
| h′(0) transition-independent | scatter < FS error | root-2: FS≠δΘ → **KILL GD06 bridge** |
| King NL = h″(0) (not just ⟨r⁴⟩) | residual after ⟨r⁴⟩, sign>0 | root-1/3 → spawn **XSD-A2** |
| Rule-2 purity | r_orbit enters as geometry, not via m_e | root-4 if a₀ launders m_e |

## ⑨.E · ⑩
root-1/2/3/4 (root-4 = m_e laundered through a₀). **Pivot:** if h′ scatters, strip the King mass-shift first; if NL is ⟨r⁴⟩-dominated spawn A2, don't force h″. **Forbidden:** fit h″ then claim to predict it; "charge radius"; m as input.

*XSD-A · the Hz anchor at Θ→0. Field shift = δ(covered sky). If it isn't, GD06 dies here — cleanly.*
