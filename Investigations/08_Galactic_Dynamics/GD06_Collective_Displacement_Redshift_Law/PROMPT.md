# GD06 — Occlusion as Subtended Solid Angle: the Depth-Redshift Law from Sky-Coverage (ROOT · cross-scale)
## "From the King Plot to the Bulge" — one dimensionless angular law Θ→z_d, calibrated on the atom, carried to the galaxy and the cluster

> **Author:** J. C. Harvey, Melbourne. **Status:** ROOT-SPEC · **REBUILT ON THE SOLID-ANGLE INSTRUMENT 2026-07-13** (supersedes the volume-𝔇 draft; §K.3, KILL-DEEPEN aware).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §A–§K · `OPERATING_PROTOCOL.md` §0–§4.
> **Engine:** `#include <sdt/laws.hpp>` only, and only for OBSERVED comparison values — **the derivation itself uses no dependency-traced constant** (see The Two Rules). **Propose-only** on canon. **No G, no M(kg), no a₀, no ΛCDM/MOND/ψ, no "charge radius."**
> **Cascade root:** SPAWNS four children (§SPAWN). Build-once-pay-many (FLM10/ROOT-SIM tradition): one angular law pays the atomic field shift, the solar redshift, the sungrazer saturation, the bulge/cluster redshift, and the dissolution of dark matter.

---

## THE TWO RULES (both forced by Harvey, 2026-07-13 — read before anything else)

**RULE 1 — THE INSTRUMENT: occlusion IS the solid angle of sky subtended at a position.** Occlusion is *not* a volume-packing density, an "energy," or a "mass." It is **the fraction of the 4π sky, at a point, that matter covers** — computed by integrating solid-angle patches of blocked sky, saturating direction-by-direction. If a quantity is not the angular integral, it is not occlusion; naming it so is the renaming disease. (The volume-density draft this replaces committed exactly that error.)

**RULE 2 — THE DIRECTION / DISSOLUTION RULE: geometry in, mass and constants out.** The only per-body input is the **geometric angular size of an occluder's boundary**. **Mass is an OUTPUT** (importing m to build the occluder is importing M — circular, since mass *is* the occlusion). And the derivation basis {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} has been **dissolved into the four irreducibles elsewhere in the repo** — those units may **not** re-enter the derivation as primitives. **Θ is a dimensionless angle; the law needs no constant.** This is *why* the calculation is scale-free.

---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **The dimensionless law z_d = h(Θ) mapping the occluded sky-fraction Θ at a position to the depth redshift of light there** — and whether Θ for a bulge/bar/nucleus lands in the **dilute** branch (Θ≪1, h≈h′(0)·Θ, recovers weak-field ϟ/r) or the **saturated** branch (Θ→1, h→h_max, the sungrazer g→2 limit). The prior 0.1% estimate assumed dilute *and* used the wrong (volume/koppa) measure.
2. **Why does it matter?** — Θ is dimensionless and scale-free, so **the atomic field shift (nucleus's Θ at the electron) and the galactic bulge redshift (bulge's Θ at a star) are the SAME law** — a fishbowl-gate prediction across ~30 orders (§0), calibrated where physics is measured to Hz (King plots) and carried to where it is measured in km/s (cluster gravitational redshift). Confirms mass = occlusion = pressure gradient of space (dark matter dissolved; GD05 verdict).
3. **How will we find out?** — Compute Θ by direct solid-angle integration with saturation (κ=1−e^{−τ}) at four anchors (nucleus@electron, Sun-surface, sungrazer, bulge@star); derive the *form* of h from the GOM05 closure; read h′,h″ from the field shift + King nonlinearity; extrapolate h(Θ) with **zero fitted parameters**; validate on the cluster. Five gated phases (§④), four spawned children (§SPAWN).
4. **What would prove us wrong?** — §⑧, each numeric. Chief kills: h that reduces identically to ϟ/r at all Θ (no new physics); a field shift not proportional to δΘ_nuc (bridge dead); a solar anchor that forces a dependency-traced constant back in (Rule 2 violated → the coupling is not geometric); scale-invariance failing nucleus→cluster.
5. **How will we know we're done?** — **Triple verdict:** prompt completion (A–F) × physics class (NATIVE/CONVERGENCE/DEGENERATE/KILLED/OPEN) × cross-scale grade (SCALE-INVARIANT/SCALE-BROKEN/UNDETERMINED). Class-A NATIVE SCALE-INVARIANT = z_d(bulge) and z_d(cluster) predicted from the King-plot h(Θ) within measured error, no fitted parameter, dilute limit = the Sun's 636 m/s, saturation limit = the sungrazer g→2.

---

## ① Executive Summary
Convergence flux arrives at every point isotropically from 4π. Matter **covers part of that sky** — occludes a solid angle. The **isotropic** part of the coverage is a uniform pressure deficit → the **depth redshift** (light climbs out through compressed closure, GOM05: z=1−c_local/c); the **anisotropic** part is the **net force** (gravity, toward the more-covered sky). Both are integrals of one dimensionless field, Θ(𝐱), over the sphere. A high-Z nucleus covers a (tiny) sky-fraction at its electron — measured to Hz as the **field shift**, its nonlinearity the **King NL**. A bulge/bar covers a (possibly large) sky-fraction at an embedded star. **Same Θ, same h — no constant enters, because Θ is an angle.** Calibrate h on the atom, anchor its limits on the Sun (dilute) and the sungrazer (saturated), carry it 30 orders to the bulge and the cluster. The crux — dense or dilute — is **which branch of Θ the bulge occupies**, and it is *computed*, not assumed.

---

## H6 DATA — Solar spation census & convergence ledger (Harvey, folded in 2026-07-13; verified in the run)

The Sun as a worked calibration point for the Θ machinery (all from ℓ_P, CMB u, geometry — no mass in the census):

| Quantity | Value | Meaning |
|----------|-------|---------|
| N_spa = V_⊙/ℓ_P³ | 3.341×10¹³¹ | spations in the solar volume |
| N_surf = A_⊙/ℓ_P² | 2.328×10⁸⁸ | spation patches on the solar surface |
| gear N_spa/N_surf = R_⊙/3ℓ_P | 1.435×10⁴³ | pure geometric volume→surface amplifier |
| ε per spation = u·c·ℓ_P² | 3.267×10⁻⁷⁵ W | convergence power on one patch per tick |
| total volumetric convergence | 1.091×10⁵⁷ W | ε × N_spa |
| **per baryon (÷N_b=1.189×10⁵⁷)** | **0.918 W** | offered budget per baryon (density-signature, = u·c/(ℓ_P·n̄)) |
| engagement fraction (L_⊙/N_b)/0.918 | 3.507×10⁻³¹ | fraction actually engaged — the transparency, per baryon |
| per-crossing transparency (ledger) | 1.6×10⁻¹⁸ | the boundary-crossing face of the same throughput |

**Photobracket (H6):** full unengaged budget at the surface = 1.79×10³⁸ W/m² (T_eq 2.4×10¹¹ K); baryon-skin channel = 787 K; oscillation-cell granule ≈ 2634 K → **the real 5778 K sits between the baryon-skin and the oscillation-cell granule** (engagement granule between R_p and λ_CMB). Five zero-fit constraints logged as **H6** (SAR03 run): offered 0.918 W/baryon → engaged 3.5×10⁻³¹ → granule bracketed 787 K < 5778 K < ~2634 K×2.2 → released through the 10⁴³ volume→surface gear → p_align ≈ 1.3×10⁻²⁵ per thermal encounter. **These transparency numbers (3.5×10⁻³¹, 1.6×10⁻¹⁸, f≈2×10⁻¹⁷) are the coupling ledger XSD-B must geometrize into σ_occ.**

## ② The Instrument & every symbol (all dimensionless or geometric)

| Symbol | Name | Definition | Notes |
|--------|------|-----------|-------|
| n̂ | sky direction | unit vector over 4π | the integration variable |
| σ_occ | **occlusion cross-section of one boundary** | geometric angular blocking area of an occluder | **the ONE per-body input; must be geometric (Rule 2); the σ_occ ↔ old "transfer function f" question is §③ THE OPEN** |
| τ(𝐱,n̂) | occlusion column | ∫ n(𝐱′) σ_occ dℓ along ray n̂ | dimensionless optical depth |
| κ(𝐱,n̂) | covered fraction per direction | **1 − e^{−τ}** | saturates at 1 (a direction cannot be over-blocked — the eclipse limit) |
| **Θ(𝐱)** | **occluded sky-fraction** | **(1/4π)∮ κ(𝐱,n̂) dΩ ∈ [0,1]** | **THE central variable** (replaces 𝔇) |
| **𝐠(𝐱)** | net occlusion force (gravity) | ∝ ∮ κ(𝐱,n̂) n̂ dΩ | the *anisotropy* of coverage |
| c_local/c | local closure | GOM05: = 1 − z_d | compressed where sky is covered |
| **z_d(𝐱)** | **depth redshift** | **z_d = h(Θ(𝐱))**, h(0)=0, h↑ | THE LAW to derive+calibrate |
| Θ_dilute / Θ_sat | branch markers | Θ≪1 (thin) / Θ→1 (opaque) | dilute↔weak gravity; saturated↔sungrazer |
| F_i, δ⟨r²⟩ | field-shift constant, nuclear size change | δν_FS = F_i·δ⟨r²⟩ | atomic calibrator = δ(Θ_nuc@electron) |
| m (any) | mass | **OUTPUT**: m ∝ (occlusion the body sources) | never an input (Rule 2) |

**No length, mass, or action constant appears above.** Θ, τ, κ, h are pure numbers; σ_occ and the geometry are angular. This is the dissolution made operational.

---

## ③ Framework — the chain, the two limits, and the ONE open

**The split.** Expand the coverage field into isotropic + anisotropic parts at 𝐱:
$$\Theta(\mathbf{x})=\frac{1}{4\pi}\oint\!\big(1-e^{-\tau(\mathbf{x},\hat n)}\big)\,d\Omega,\qquad \mathbf{g}(\mathbf{x})\propto\oint\!\big(1-e^{-\tau}\big)\hat n\,d\Omega.$$
- **Isotropic (Θ) → depth redshift.** Uniform coverage compresses the local closure everywhere-inward equally → z_d=h(Θ). No net force, pure depth. This is the piece the volume-draft missed.
- **Anisotropic (𝐠) → gravity.** Net toward the more-covered hemisphere. In the thin limit this **must** reduce to the inverse-square occlusion law and to GD05's streak (disk = great-circle band, Θ_disk→2π/4π at saturation).

**The two limits (both are hard anchors, not fits):**
- **Dilute / thin (τ≪1):** κ≈τ, Θ≈(1/4π)∮τ dΩ ∝ occlusion column ∝ (what is called) enclosed mass ⟹ **weak-field gravity and z_d→ϟ/r**. Anchor: **the Sun's surface redshift 636 m/s** must fall out here.
- **Saturated / opaque (τ≳1):** κ→1, Θ→(geometric covered fraction) ⟹ **occlusion saturation, g→2 near contact** ([[project_two_regime_and_occlusion_saturation]]: sungrazer +6.8%). Anchor: the sungrazer excess must fall out here.

**THE ONE OPEN — what is σ_occ, and is it geometric?** Normal matter is nearly transparent to convergence (gravity is weak ⟹ τ≪1 for a star's line of sight, even though it is geometrically opaque to light). So σ_occ is **not** the atomic geometric area; it is the effective convergence-occlusion cross-section — historically the "transfer function f≈2×10⁻¹⁷" ([[project_electropause_peff_derivation]], EMC01). **Rule 2 demands σ_occ be geometric** (a boundary sky-area, no coupling constant). The cascade's success hinges on **geometrizing f**: showing the effective occlusion cross-section is a pure angular property of the boundary knot (the occluded-spation boundary, 5.9×10⁵⁹ for the proton, as a *fraction of the whole sky at the electron*), not a coupling. This is XSD-B's core and the honest make-or-break. If f cannot be geometrized, GD06 is DEFERRED (not faked) to EMC01/FLM10.

**Closure link (GOM05).** z_d = 1 − c_local/c, and c_local drops as the sky is covered: c_local/c = G(Θ), h(Θ)=1−G(Θ). Derive G from the relay-throughput deficit under coverage (XSD-B). Monotone, G(0)=1.

**Cross-scale (the payoff).** Θ dimensionless ⟹ h(Θ) is one curve. Place four systems on the Θ-axis by pure geometry: Θ_nuc@electron (field shift), Θ_⊙@surface (636 m/s), Θ_sungrazer (saturation), Θ_bulge@star (the prediction), Θ_cluster@galaxy (validation). **No constant converts between them.**

---

## ④ Strategy — five gated phases (each feeds the next)

**Phase 0 — The Θ engine. (spawns XSD-B core)** Build a standalone solid-angle integrator: given a matter distribution n(𝐱′) and a boundary cross-section rule σ_occ, compute Θ(𝐱), 𝐠(𝐱) by direct spherical quadrature with saturation κ=1−e^{−τ}. *Metric:* reproduces GD05's streak (disk band, Θ_disk saturation) and the inverse-square thin limit. **Gate:** no anchor past Phase 2 until Θ reproduces both.

**Phase 1 — Derive h(Θ) and geometrize σ_occ. (spawns XSD-B)** From GOM05 closure derive G(Θ) (hence h); establish whether σ_occ is a pure boundary sky-area (Rule 2) or requires the coupling f (⟹ DEFER to EMC01). *Metric:* dilute limit gives the Sun's 636 m/s AND saturation gives the sungrazer g→2, **with a geometric σ_occ**. **Fail →** DEFER with the f-geometrization named.

**Phase 2 — Calibrate h′,h″ on the King plot. (spawns XSD-A) ★ anchor** Θ_nuc@electron ≈ (angular size of the nucleus at a₀) — small, so the field shift probes the **dilute** slope h′(0); the King NL gives the dilute curvature h″(0). *Metric:* h′ transition-independent (the bridge test); h″ sign pre-committed. **Fail (h′ transition-dependent) →** the field shift is not δΘ ⟹ **KILL the bridge honestly.**

**Phase 3 — Place the bulge on the Θ-axis; the dense/dilute verdict. (spawns XSD-C) ★ crux** Compute Θ_bulge@star by integrating the bulge's covered sky at embedded/nearby stars (M/L-free surface photometry → boundary sky-areas). *Metric:* is Θ_bulge dilute (≪1, z_d≈0.1%, disk speed uncorrupted) or dense (→1, z_d dominates, "redshift=speed" false)? Pre-commit the branch boundary in Θ. Predict Δcz(center−disk), zero free parameters.

**Phase 4 — Cluster validation. (spawns XSD-D)** Θ_cluster@galaxy → z_d(R); compare to the measured cluster gravitational redshift (Wojtak+2011 ~10 km/s), **no cluster fit**. *Metric:* within error ⟹ SCALE-INVARIANT across 30 orders.

**Gate rule:** every galactic/cluster number must be *carried* from the King-plot h(Θ) through the Θ-engine; none may be sized by a koppa or a fitted coupling.

---

## SPAWN — four child investigations (this ROOT generates four PROMPT.md, rebuilt on Θ)

| Child | Title | Home | Feeds | Deliverable |
|-------|-------|------|-------|-------------|
| **XSD-A** | Field Shift as δΘ — h′,h″ from the King plot | 02 | Phase 2 | h′(0),h″(0) of h(Θ), ≥2 transitions ×≥5 chains, bridge test |
| **XSD-B** | The Θ→z_d law + geometrizing σ_occ (transfer function f) | 01 | Phase 0/1 | G(Θ)/h(Θ) form; proof σ_occ is a boundary sky-area or DEFER to EMC01; Sun+sungrazer anchors |
| **XSD-C** | Θ_bulge@star — dense-vs-dilute + the redshift/rotation symmetry | 08 | Phase 3 | Θ_bulge, the branch verdict, common-mode-vs-antisymmetric deconvolution |
| **XSD-D** | Θ_cluster — the 30-order gravitational-redshift validation | 06 | Phase 4 | predicted vs measured cluster z_d; SCALE grade |

**Conditional 2nd-gen (declared now):** XSD-B→**B2** *Geometrize-f* if σ_occ won't reduce to a sky-area (the deep EMC01/electropause link) · XSD-A→**A2** *⟨r⁴⟩ vs h″* if the King NL is higher-moment contaminated · XSD-C→**C2** *inclination deconvolution* if the bulge is dense (how a common-mode z_d separates from antisymmetric rotation) · XSD-D→**D2** *break-scale* if SCALE-BROKEN · 5th-gen *cosmological Θ* (CMB depth z=1099, Hubble split) if Phases 0–4 hold.

---

## Dependency Map (§K.3)
| Item | Where | Enters as | Live |
|------|-------|-----------|------|
| GOM05 variable closure z=1−c_local/c | [[project_cq43_variable_closure]] | the Θ→z_d mechanism | ✔ |
| GD05 streak / eclipse saturation | GD05 (`gd05_sdt_streak.cpp`) | the Θ engine's thin/band test | ✔ |
| Sun z(R_⊙)=636 m/s, sungrazer +6.8% g→2 | Depth-Closure / [[project_two_regime_and_occlusion_saturation]] | dilute + saturated anchors | ✔ |
| transfer function f≈2×10⁻¹⁷, EMC01/electropause | [[project_electropause_peff_derivation]] | the σ_occ-geometrization open | ⚠ B2 |
| boundary occluded-spation count (proton 5.9×10⁵⁹) | boundary calc / FLM10 | σ_occ as a boundary sky-area | ⚠ dep |
| field shift F_i, King NL, ⟨r²⟩ (Ca/Yb/Cd/Sr/Ba) | [[project_kingplot_movement_law]] + isotope data | Phase 2 calibrator = δΘ_nuc | ⚠ pull |
| cluster gravitational redshift (Wojtak 2011) | literature (OBSERVED only) | Phase 4 validation | ⚠ pull |
| mass = occlusion = pressure gradient (no localizable mass) | GD05 verdict | ontological premise | ✔ |
| **PROHIBITED:** G, M(kg), a₀, ΛCDM, MOND, ψ, "charge radius", any dependency-traced constant *in the derivation*, virial-as-derivation | — | kill on sight (§B/§G) | — |

---

## ⑧ Falsifiers → four-root sort
| Test | Predicted | FAIL → root |
|------|-----------|-------------|
| T1 dilute limit | Θ-engine thin limit gives Sun 636 m/s | root-1: closure/instrument wrong |
| T2 saturation | Θ→1 gives sungrazer g→2 | root-1 |
| T3 field shift = δΘ | h′ transition-independent | root-2: bridge dead → KILL |
| T4 King NL = h″(0) | sign & size match derived curvature | root-1/3 → spawn A2 |
| T5 crux | Θ_bulge branch (dense/dilute) computed, not assumed | if dilute: 0.1% stands, disk speed uncorrupted (honest) |
| T6 scale-invariance | cluster z_d within Wojtak error, no fit | root-2: SCALE-BROKEN → spawn D2 |
| T7 Rule-2 purity | no dependency-traced constant in the derivation; σ_occ geometric | root-4: if f won't geometrize → DEFER to EMC01, not fake |
| T8 mass is output | m_e,m_p,6π⁵ fall OUT of the geometry | root-4: any m-input = contraband |

---

## ⑨.E Four-root loop (run on every failure)
root-1 CLAIM (instrument/closure wrong) · root-2 DEPENDENCY (field-shift, boundary sky-area, cluster data, EMC01 f) · root-3 PROMPT (h form / Θ-engine mis-scoped) · root-4 CONTRABAND (a dependency-traced constant or mass smuggled into the derivation; virial; charge radius). The σ_occ-geometrization and any scale-break are **named OPEN closures** (§D), never amputations. Log each; shared roots once in `INVESTIGATION_STACK.md`.

## Brainstorm — leads (§K.3)
- **Geometrizing f is the crown.** If the transfer function 2×10⁻¹⁷ is the boundary knot's sky-fraction at the electron (a pure angle), then EMC01's P_eff, the whole force hierarchy, AND this redshift law are one geometric object — and no coupling constant survives anywhere. This is the biggest prize in the cascade (XSD-B2).
- **Dilute vs dense is the sungrazer vs the Sun.** Both anchors are Θ-branches of one curve; the bulge is somewhere between. Compute where.
- **Common-mode vs anisotropic** is the measurement fork: the isotropic Θ (depth redshift) cancels in the antisymmetric disk-rotation extraction but survives in dispersion — so a dense bulge corrupts σ, not the disk's rotation curve (XSD-C2), unless inclination breaks the symmetry.
- **6π⁵ falls out, not in.** With mass as the sourced occlusion, m_p/m_e is a ratio of boundary sky-areas of the (2,3) trefoil and (1,1) loop — cross-link PPT03; never an input.

## ⑤ Success (triple verdict) · ⑥ Outputs
Class A·NATIVE·SCALE-INVARIANT: h(Θ) derived + King-calibrated + both limits anchored + bulge branch computed + cluster within error, zero fitted parameters, σ_occ geometric. Honest floor (D/OPEN): Θ-engine built, h form + dilute/saturation anchors set, σ_occ-geometrization flagged to EMC01, bulge placed on the Θ-axis. Outputs: `RUN_LOG.md` · `xsd_theta_engine.cpp` (solid-angle integrator, no dependency-traced constant in the physics) · `GD06_DERIVATION.md` · `GD06_VERDICT.md` · the four `spawn/XSD-*/PROMPT.md` (rebuilt) · CANON_FLAGS · STACK cascade-root entry.

---

## ⑩ Adaptive Execution Protocol
```markdown
## Pre-Run Commitments — GD06 (§K ROOT, solid-angle)
- Prompt completion target: [A|B|C|D] · physics class hoped: [NATIVE|OPEN] · cross-scale hoped: [SCALE-INVARIANT|UNDETERMINED]
- CALIBRATED budget: 0 across scales (King plot MEASURES h, does not fit GD06)
- σ_occ rule committed: [geometric boundary sky-area | DEFER to EMC01 if f won't geometrize]
- Branch boundary Θ* (commit before Phase 3): ____   ·   h″(0) sign committed before Phase 2: ____
- Anchors: Sun 636 m/s (dilute) · sungrazer g→2 (saturated) · field shift (Θ_nuc) · Wojtak cluster (OBSERVED only)
- Forbidden: any dependency-traced constant IN THE DERIVATION; m as input; koppa as the general law; virial-as-pressure; "charge radius"; a galactic z_d not carried from the King-plot h(Θ)
```
| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| σ_occ needs the coupling f | try boundary-sky-area geometrization | DEFER to EMC01 (root-4), spawn B2 | keep f as a fitted coupling |
| Θ-engine misses the Sun/sungrazer | fix quadrature/saturation | OPEN the closure (root-1) | tune σ_occ to land it |
| field-shift h′ transition-dependent | strip King mass-shift first | KILL the bridge (T3) | average incompatible h′ |
| bulge lands dilute (T5) | accept 0.1%, report disk speed uncorrupted | honest DEGENERATE on that point | claim corruption anyway |
| cluster overshoot (T6) | spawn D2 break-scale | SCALE-BROKEN, name Θ* | fit a cluster coefficient |
| any constant/mass in the derivation | remove it; re-derive in pure angle | root-4 contraband | smuggle it as "effective" |

**Disallowed:** dependency-traced constants in the derivation · m as input · fitted cross-scale coefficient · virial-as-pressure · koppa-as-general-law · "charge radius" · a galactic z_d not carried from the atom.

---

## Verdict line
> **Prompt completion** [A–F] · **Physics class** [NATIVE/…/OPEN] · **Cross-scale** [SCALE-INVARIANT/BROKEN/UNDETERMINED] · **σ_occ** [GEOMETRIC/DEFERRED-to-EMC01] · **Cascade root** [GD06] · **Children** [XSD-A/B/C/D (+A2/B2/C2/D2)].

*GD06 · rebuilt on the solid-angle instrument 2026-07-13 · occlusion = subtended sky-fraction Θ; depth redshift = h(Θ); one dimensionless angular law, no constants, calibrated on the King plot, anchored on the Sun and the sungrazer, carried 30 orders to the bulge and the cluster; mass and 6π⁵ fall out; the crux and the f-geometrization are DERIVED or honestly DEFERRED, never assumed.*
