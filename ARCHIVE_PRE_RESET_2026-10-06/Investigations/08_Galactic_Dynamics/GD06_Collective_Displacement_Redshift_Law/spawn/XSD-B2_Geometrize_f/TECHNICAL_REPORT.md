# XSD-B2 — Geometrize the coupling: TECHNICAL REPORT (RUN 1 + **RUN 2 CORRECTION**, 2026-07-13)
### RUN 2 verdict: the RUN-1 hunt was **categorically mis-typed**. Target re-typed. Root relocated to FLM10.

> **Harvey correction (2026-07-13):** *"you list that the Sun requires a m³ volumetric component to occlude. That is not how occlusion operates. It is merely a phase interrupt — the ontic spation-to-spation transfer is delayed/scattered/reflected. If you have even a single baryon adjacent, that baryon will reduce the influx along those lines occluded by those same lines. Not much — but you get enough superdilution and you have a galaxy like Andromeda barrelling down on the MW."*

## 1. The RUN-1 error (why the hunt failed — a real diagnosis, not an excuse)
RUN 1 expressed the coupling as **σ_occ = 1.561×10⁻⁵³ m² per baryon** — an **area**. That silently imports the **Le Sage corpuscular picture**: a baryon as a disc that *blocks* flux, requiring a physical cross-section/volume to do its work. **Occlusion is not blocking.** It is a **phase interrupt**: the spation→spation relay is *delayed / scattered / reflected* as it passes. Nothing is consumed; no area is required.

**Consequence:** every RUN-1 candidate (πR_p², trefoil-tube projection, ℓ_P², ℓ_P·R_p, α³×area) was an **AREA**. The target is a **dimensionless phase/delay**. The hunt failed because it was **the wrong type of object**, not because the geometry is absent. RUN-1's candidate table is **void** (mis-typed), not merely negative.

## 2. The correctly-typed ledger (RUN 2)
| quantity | value | type |
|---|---|---|
| baryon **crossings** along a solar diameter (n·πR_p²·2R) | 2.609×10⁹ | count of interrupts per relay line |
| **per-crossing phase interrupt ε** (Sun-anchored) | **7.0186×10⁻²⁴** | **dimensionless fractional influx delay per baryon crossed** |
| spation hops across one proton (2R_p/ℓ_P) | 1.041×10²⁰ | relay hops |
| interrupt per hop (ε/hops) | 6.741×10⁻⁴⁴ | dimensionless |

**Reading:** every relay line through the Sun is interrupted ~2.6×10⁹ times; each crossing delays the influx by ~1 part in 1.42×10²³. The Sun is *geometrically* thick in baryons and *phase-wise* almost perfectly transparent — which is exactly why gravity is weak.

> ### ⚠ REJECTED — unit-basis numerology
> interrupt-per-hop = 6.741×10⁻⁴⁴ **looks** like t_P = 5.391×10⁻⁴⁴ s (ratio 1.25). **This is meaningless:** one is dimensionless, the other is seconds; the "match" is an artifact of the SI second and vanishes in any other time base. Same class as the `W_per_spation` "order unity" comment the Interchange Sweep deflated. **Recorded as rejected, not as a lead.**

## 3. Superdilution → Andromeda (Harvey's picture, priced)
| | |
|---|---|
| per-baryon interrupt | 1 part in **1.42×10²³** |
| M31 baryons | **1.784×10⁶⁹** |
| M31 distance | 780 kpc |
| net infall acceleration on the MW | **3.44×10⁻¹³ m/s²** |
| observed approach / time to contact | ~110 km/s / ~6.9 Gyr |

**One baryon is nothing. 10⁶⁹ of them, superdiluted across 780 kpc, steer a galaxy into us.** The mechanism's signature *is* the superdilution: a per-crossing interrupt of 10⁻²⁴ is invisible locally and inexorable at 10⁶⁹.

## 4. ★ ROOT RELOCATED — the coupling is owed by FLM10, not cosmology, not the King plot
RUN 1 concluded "the road runs through the cosmology d(z) fix" (because EMC01's f rides the CR07-forbidden R_CMB). **RUN 2 supersedes that as the primary route.** Re-typed as a phase interrupt, the coupling is a **relay-mechanics quantity**: *what does a baryon-shaped defect do to the spation→spation transfer — how much delay/scatter per crossing?* That is **exactly what FLM10 (the per-spation lattice solver / ROOT-SIM) is built to compute** — per-spation contact mechanics with the c-relay, which FLM02/FLM05 formulate tick-by-tick.

**So ε = 7.02×10⁻²⁴ is an FLM10 deliverable.** This is a cascade *merge*, not a new debt: FLM10 already carries five debts (isotropy/ω(k), PPT07 wake, FLM03/04 v(r), OP-2 winding, OP-1/3 quantisation). **The gravitational coupling becomes the sixth — and it is the one that would make GD06 constant-free.**

*(The cosmology d(z) repair remains owed for EMC01's f, but f was always the EM-pressure channel, a different type again — see RUN 1 §5. It is no longer the blocker for GD06's coupling.)*

## 5. Verdict (RUN 2)
> Prompt completion **B** (mis-typing diagnosed, ledger re-run correctly) · Physics class **NO RECOVERY yet — but the target is now correctly typed** · **root-2 (dependency) → FLM10** (relay-mechanics), superseding the RUN-1 cosmology routing · σ_occ-as-area **VOID**; ε-as-phase-interrupt **the live target**.

**GD06 status unchanged:** still capped at CONVERGENCE (mass-free re-derivation of the gravitational redshift with an unexplained coupling) — but the coupling now has a **named owner with the right instrument** (FLM10) instead of an area-hunt that could never have converged.

## 6. Next actions (dependency order)
1. **FLM10** — compute the per-crossing phase interrupt of a baryon-shaped defect on the c-relay. If it yields ε ≈ 7×10⁻²⁴ from geometry + relay dynamics alone, **the coupling is derived and GD06 becomes constant-free.** This is now FLM10's sixth debt and arguably its most valuable.
2. **XSD-A** (isotope shifts) — independent of ε; still the live cross-scale anchor.
3. Cosmology d(z) repair — still owed, but for EMC01's f (EM channel), no longer GD06's blocker.
