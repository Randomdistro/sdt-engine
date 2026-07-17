# XSD-B — The Θ→z_d law + geometrizing σ_occ (the transfer function): occlusion done in pure angle
### (spawned by GD06 · feeds Phase 0/1 · home 01 Foundations · REBUILT on the solid-angle instrument 2026-07-13)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPAWNED-SPEC (rebuilt). **Inherits:** GD06 The Two Rules + §③; `HUNTER_PROTOCOL.md` §A–§K.
> **Engine:** `laws.hpp` for OBSERVED anchors only. **No whitelisted constant in the derivation. No m as input. This is the make-or-break of the whole cascade.**

## ⓪ Five questions
1. **What don't we know?** — (a) the **analytic form of h(Θ)** (equivalently G(Θ)=1−h, the closure vs sky-coverage), and (b) **whether the occlusion cross-section σ_occ is a pure geometric boundary sky-area** — i.e. whether the old **transfer function f≈2×10⁻¹⁷ can be GEOMETRIZED** (Rule 2), or must remain a coupling (⟹ DEFER to EMC01).
2. **Why?** — Everything downstream is an angular integral over σ_occ; if σ_occ hides a coupling constant, Rule 2 is violated and GD06 is not yet a pure occlusion law. If it geometrizes, EMC01's P_eff, the force hierarchy, and this redshift law collapse to **one boundary sky-fraction** with no constant anywhere.
3. **How?** — Derive G(Θ) from the relay-throughput deficit under sky-coverage (GOM05); build the Θ-engine; test σ_occ = boundary occluded-spation area as a *fraction of the electron's sky*; anchor on the Sun (dilute) and the sungrazer (saturated).
4. **Wrong if?** — h cannot reduce to ϟ/r in the dilute limit (Sun 636 m/s) with a **geometric** σ_occ; or σ_occ only reproduces gravity with the coupling f left in (then geometrization FAILS → spawn B2/DEFER).
5. **Done when?** — G(Θ)/h(Θ) analytic, dilute=636 m/s and saturation=sungrazer g→2 both hit, and a **verdict on σ_occ** (GEOMETRIC or DEFERRED-to-EMC01).

## 1. Framework
**Coverage → closure.** Convergence relay throughput at 𝐱 is reduced in proportion to the covered sky; GOM05: c_local/c = G(Θ), z_d = 1−G(Θ) = h(Θ). Derive G from the fraction of incoming relay directions removed: candidate forms (declare ≥3) — (i) **G=1−κ₀Θ** (thin/linear, dilute-only); (ii) **G=e^{−Θ}** or **G=(1−Θ)** (opaque saturation, ties the Clearing/opacity [[project_opacity_logjam_cmb_gradient]]); (iii) a stiffening log form. Fix h′(0) from **XSD-A** (field shift) and the two physical anchors below; the correct form must interpolate dilute↔saturated.

**Geometrizing σ_occ (the crux).** τ=∫ n σ_occ dℓ. Normal matter is nearly transparent to convergence (gravity weak ⟹ τ≪1), so σ_occ ≪ the atomic geometric area. **Hypothesis (Rule 2):** σ_occ is the **boundary occluded-spation area of the knot as a fraction of the sky** — the proton's 5.9×10⁵⁹ boundary spations projected, a pure angle, NOT a coupling. Test: does τ built from this geometric σ_occ reproduce weak-field gravity **without** inserting f? If the number that emerges *is* 2×10⁻¹⁷ (EMC01's f) from geometry alone, **f is geometrized** and no constant survives. If not, **DEFER to EMC01/electropause** ([[project_electropause_peff_derivation]]) and spawn **XSD-B2**.

**Two hard anchors (not fits):**
- **Dilute (Sun):** thin-limit Θ_⊙@surface × h′(0) must give **z(R_⊙)=636 m/s**. (Note: at the surface the Sun covers ~½ the sky *geometrically* but τ≪1 optically ⟹ Θ_optical tiny — the reconciliation of geometric-½-sky with 636 m/s IS the σ_occ test.)
- **Saturated (sungrazer):** as τ→large near contact, Θ→geometric fraction and **g→2** (sungrazer +6.8%, [[project_two_regime_and_occlusion_saturation]]).

## 2. Method (gated)
- **P0** Build `xsd_theta_engine.cpp`: spherical quadrature of Θ, 𝐠 with κ=1−e^{−τ}; validate against GD05 streak + inverse-square thin limit.
- **P1** Derive G(Θ); select the form hitting h′(0) (XSD-A) + both anchors.
- **P2** Geometrize σ_occ; **metric:** dilute τ from geometric σ_occ yields 636 m/s AND matches EMC01's f magnitude — or DEFER. Deliver the σ_occ verdict + h(Θ) to GD06.

## Dependency map
| Item | Where | Enters as | Live |
|---|---|---|---|
| GOM05 z=1−c_local/c | [[project_cq43_variable_closure]] | closure→h link | ✔ |
| GD05 streak / eclipse saturation | GD05 tool | Θ-engine validation | ✔ |
| Sun 636 m/s · sungrazer g→2 | Depth-Closure / [[project_two_regime_and_occlusion_saturation]] | the two anchors | ✔ |
| transfer function f, P_eff, EMC01/electropause | [[project_electropause_peff_derivation]] | the geometrization target | ⚠ B2 |
| boundary occluded-spation count (5.9×10⁵⁹) | boundary calc / FLM10 | σ_occ as sky-area | ⚠ verify |
| h′(0) | XSD-A | pins the form | ⚠ dep |

## ⑧ Falsifiers
| Test | Predicted | FAIL → root |
|---|---|---|
| dilute anchor | geometric σ_occ → Sun 636 m/s | root-1: closure/instrument wrong |
| f geometrized | emergent τ magnitude = EMC01 f, no coupling | root-4: σ_occ hides f → DEFER, spawn **B2** |
| saturation anchor | Θ→1 → sungrazer g→2 | root-1 |
| form interpolates | one G(Θ) hits both branches + h′(0) | root-3: split with a NAMED crossover, not fitted |

## ⑨.E · ⑩
root-1/2/3/4 (root-4 = a coupling constant surviving in σ_occ). **Pivot:** if no single G hits both branches, split dilute/saturated with the crossover Θ *named*; if σ_occ won't geometrize, DEFER to EMC01 (do not fake a constant-free law). **Forbidden:** virial-as-derivation; picking a form to land the Sun; leaving f in and calling it geometric.

*XSD-B · the make-or-break. If the transfer function is a boundary sky-fraction, occlusion is pure geometry and no constant survives anywhere in SDT's force sector. If not, GD06 honestly DEFERS to EMC01 — it does not launder f back in.*
