# PPT18 — ProtOm: the proton's own c-boundary Ѻ_p (deconstruction)

**Author:** J. C. Harvey, Melbourne. Opened 2026-10-12 at Harvey's direction ("begin the ProtOm deconstruction"). Gateways binding; direct execution.

## 1. Question
Where does the proton's own poloidal circulation reach c, i.e. what is **Ѻ_p**? It is not hydrogen's c-boundary.

**Harvey ruling (2026-10-12):**
- The proton sits inside the **hydrogen atom's** c-boundary, r_e = Ѻ_H.
- The proton's own c-boundary is a **poloidally orbiting rotation well inside the proton's four tours**.

**Why it matters.**
- **Contact depth.** Every nuclear contact sits at two depths: hydrogen's (z_H = r_e/r > 1 at contact) and each proton's own (Ѻ_p/r).
- **Shared-cause test.** Harvey's proposal (2026-10-11/12) is that occlusion strength and emission shift share one cause, the displacement, with a possibly flipped law past z = 1. Testing it needs both depths.
- **No value exists.** Ѻ_p has no value anywhere in the corpus.

## 2. Stage 1 — inventory and consistency (this round)
Take apart every proton geometry the corpus and the live engine assign, with provenance. Check each for internal consistency, then tabulate what each would give for Ѻ_p under candidate definitions fixed here.

**There is no measured Ѻ_p.** The tabulation therefore cannot be a fit to a target. The risk is in the later **choice**, and the choice criteria are registered in §4 before stage 2.

**Geometries inventoried:**

| id | source | content |
|---|---|---|
| G1 | `laws.hpp` `topology` | (p, q) = (2, 3) torus knot; v_T = c√(p/(p+q)), v_P = c√(q/(p+q)); aspect R/a = √(q/p); no absolute size |
| G2 | `laws.hpp` `confinement` (PPT05) | R_trefoil = (ħ/m_p c)/√3 |
| G3 | `laws.hpp` `law_III::R_p_lock` (FLM07) | R_p = 4ħ/(m_p c), with 4 = W + 1 (four action relays) |
| G4 | NP30 §2–§3 | (2,3) trefoil filament (tube ≪ R_p); extent R_p; node R_p/3 (stabled electron); surface at 1.83c on **hydrogen's** ladder |
| G5 | NSEQ16 `PROMPT_BRAID_REPAIR.md` | cyclic quadruple helix (P, Q) = (4, 5); R = 0.62 R_p, a = 0.22 R_p, b = 0.16 R_p; R + a + b = R_p |
| G6 | live engine `traction-gear-engine.js` H1 (NSEQ18-WEB-1) | 4 major tours, 3 cross-section turns, 4 apparent strands; helix length 5.28 fm (major radius 5.28/2π); strand diameter 0.06 fm (helix radius 0.06/√2); 1.83c. **The provenance of 5.28 and 0.06 was not found in any investigation record.** |

**Consistency checks (computed, no target):**
- K1: the outer envelope against R_p (where a size is given).
- K2: R/a against the canon aspect √(q/p) for the geometry's own winding pair.
- K3: the canon Law V budget (v_T² + v_P² = c²) against the 1.83c surface figure. These are different quantities: 1.83c is hydrogen's ladder at R_p, i.e. the PPT06 phase speed. The check reports both.
- K4: the winding labels across G1, G4, G5 and G6: (2,3), (4,5), "4 tours × 3 turns".

**Candidate definitions of Ѻ_p** (fixed now; evaluated for every geometry that supplies the inputs):
- **D1 (Om definition on the poloidal circulation):** Ѻ_p = a·(v_P/c)². This is the radius where a ladder v = c√(Ѻ_p/ρ) through the poloidal speed v_P at the tube radius a reaches c. It is the same R/k² construction that gives Ѻ_H = r_e from a₀ and αc.
- **D2 (rigid poloidal rotation, control):** ρ_c = a·c/v_P. This is outside the tube whenever v_P < c, so it contradicts "well inside". It is kept as a control so that the ruling has a case it excludes.
- **D3 (action seat per relay):** ħ/(m_p c) = R_p/4, the radius at which one action unit of the proton circulates at c.

**Validations:**
- V1: the canon v_T and v_P reproduce budget closure 1 to 1e-15 for (2,3) and (4,5).
- V2: 4ħ/(m_p c) = `law_III::R_p_lock` to 1e-15.
- V3: the G5 envelope R + a + b = R_p to 1e-12.

## 3. Outputs
- The inventory table with numbers in fm and c.
- Consistency flags K1–K4.
- The D1–D3 matrix.
- A record `PPT18_STAGE1_RECORD_2026-10-12.md`.

## 4. Choice criteria for stage 2 (registered now, before the matrix is seen)
A geometry and definition pair is admissible only if it meets all of:
- **(a)** Ѻ_p lies inside the four-tour envelope, and inside the tube or poloidal circulation itself (Harvey: "well inside").
- **(b)** It is internally consistent (K1–K4 clean, or the conflict is named and resolved by a ruling).
- **(c)** Every size it uses has traced provenance (no untraced engine constant).

Among admissible pairs, the stage-2 discriminator is a known answer **not used in building any geometry**, to be registered before any value: candidates are the proton magnetic moment and the neutron-node radius R_p/3. If no pair is admissible, that itself is the stage-1 result, and the geometry conflict goes to Harvey for a ruling.

## 5. Prohibitions
- No QM narration.
- No "charge"; e is a unit bridge only.
- No selection of a geometry by its Ѻ_p value.
- Engine, Laws and Release are not edited.

---

## Addendum 2026-10-12: stage 2a (registered before `ppt18_stage2a.cpp` exists)

Stage 1 found no admissible geometry and pairing (record of 2026-10-12). Stage 2a removes the untraced constants and rebuilds each candidate winding from canon rules only. The output is a decision table for Harvey's geometry ruling. **It is not a selection.**

**Construction, for each winding (p, q) ∈ {(2,3), (4,5), (4,3)}:**
- aspect R/a = √(q/p) (`topology::aspect_ratio`, mode-locked by the Law V budget);
- filament envelope R + a = R_p_lock = 4ħ/(m_p c) (NP30 §2: the strand is a filament, b ≪ R_p; FLM07 target-free radius);
- v_P = c√(q/(p+q));
- **Ѻ_p = a v_P²/c²** (D1);
- D3 (ħ/m_p c) kept as reference.

**Checks:**
- **C1, ring:** R > a (a ring torus). If R ≤ a, the canon aspect law cannot host that winding as a ring, and the winding is excluded under this construction.
- **C2, "four tours":** p = 4 (Harvey 2026-10-12). (2,3) has p = 2 and is flagged, not excluded: the reading of "tours" is Harvey's to confirm.
- **C3, depth at contact:** z_p = Ѻ_p/(2R_p) against z_H = 1.675.

**Admissible** = C1 met, with every size traced (true by construction). C2 decides among the admissible windings only with Harvey's confirmation.

**Exposure, disclosed.** While planning stage 2 I evaluated by hand 2μ_p/(e c) = 0.587 fm: the radius at which one circulating unit at c would give the proton moment. It is not used here. If the moment becomes the stage-2b discriminator, that exposure caps it as post-seen. And the engine's H1 geometry was built **targeting** μ_p (`targetMagneticMomentAm2`), so any μ_p comparison using engine geometry is shared-input.

---

## Addendum 2026-10-12 (b): stage 2b, Harvey's construction rule (registered before `ppt18_stage2b.cpp` exists)

**Harvey (2026-10-12, verbatim core):** "the four tours is made with the same volume. the volume doesn't change: point-particle electron cross as electron orbital path tube cross, preserve volume, shrink outer diameter to match 1.68 … femtometers, multiply by 1836, then have that volume stretch out so that it can complete four loops that twine around each other, allowing one poloidal traversal per loop."

**Reading registered (reading A), using canon PPT17's objects:**
1. **V_e** = π b_e² · 4πa₀: the point electron's cross-section swept along its 720° Bohr-seat closure (`mass_ratio::electron_orbit_tube_volume`).
2. **V_p** = 1836 · V_e. The packing count is the measured m_p/m_e (1836.15). Canon's 6π⁵ = 1836.118 is reported alongside; both are shared-input with the mass ratio (PPT17).
3. **Envelope:** outer diameter 2R_p_lock = 1.6825 fm, i.e. outer radius R_p.
4. **Shape:** one strand making **four loops** (toroidal circuits) that twine as a four-pass bundle. In cross-section, four equal circular passes of radius b touch their neighbours around the bundle axis: bundle radius a = √2·b. The bundle runs around major radius R = R_p − a − b. **One poloidal traversal per loop:** each loop winds once around the bundle axis.
   - Strand length L = 4·√((2πR)² + (2πa)²).
5. **Solve** π b² L(b) = V_p for b. If no ring solution exists (R > a > 0), the volume **does not fit** the envelope, and the maximum b_e that fits is reported.
6. **Ѻ_p (D1):** the loop's poloidal and toroidal paths share the Law V budget along the strand: v_P/c = 2πa/√((2πR)² + (2πa)²), and Ѻ_p = a (v_P/c)².

**Input:** b_e = `law_VI::winding::r_electron_body_open` = 3.0e-20 m. This is **OPEN** in canon (from the 1.2 mm/s locked-rotation argument; not derived). The result is reported as a function of b_e over 1e-21 to 1e-19 m, and at canon's value.

**Ambiguity named (for Harvey).** Whether step 2's "shrink outer diameter to 1.68" fixes the cross-section *before* the ×1836 (reading B: the cross-section is kept, and the ×1836 goes into length), or only the final envelope (reading A). Reading B needs a rule for the shape of the shrunk electron torus, which is not given, so it is not computed.

**Validations:**
- V1: V_e reproduces `mass_ratio::electron_orbit_tube_volume(b_e)` to 1e-15.
- V2: the solver recovers a planted b on a synthetic V.
- V3: R + a + b = R_p to 1e-12 at the solution.

**No target exists for Ѻ_p or b.** This is a construction, reported as a decision table.

## Addendum 2026-10-12 (c): stage 2b-r, Harvey ruling on the closure length
**Ruling (Harvey):** "halve it. just because it connects flipped over doesn't mean it does two tours."
- The 720° orientation closure is a **flip connection made within one tour**.
- The electron's tube is therefore **one Bohr orbit long, 2πa₀**: half of canon PPT17's `electron_closure_length` (4πa₀).

Stage 2b is re-run with V_e = π b_e² · 2πa₀. Every other element is unchanged.

**Disclosure.** Before this ruling I showed Harvey the one-orbit numbers: the fit limit b_e = 2.96e-20 m, within 1.5% of canon's 3e-20 m. Any agreement under this reading is **post-seen** and is not counted as confirmation.

**Canon note (propose-and-wait).** PPT17's closure length 4πa₀, and through it `proton_tube_radius_from_packing` and B26's tube radii, would change under this ruling. The 6π⁵ packing count (a declared count) does not. Nothing is edited.

## Addendum 2026-10-12 (d): stage 3, radiation map of the proton's own ladder (registered before `ppt18_stage3.cpp`)
**Harvey:** "what radiation would that .092 create? … all of the above, in a comparison table. be extraordinarily thorough."

**Ladder (stage 2b-r fill limit):** Ѻ_p = 0.15538 fm; z(r) = Ѻ_p/r; v(r) = c√z. Hydrogen's ladder at the same radii, z_H = r_e/r, is shown alongside.

**Stations (radii):**

| station | radius | z_p |
|---|---|---|
| Ѻ_p (proton's own c-boundary) | 0.155 fm | 1 |
| a = R (bundle and tour radius) | 0.311 fm | 0.5 |
| node R_p/3 | 0.280 fm | 0.555 |
| R_p (rim) | 0.841 fm | 0.185 |
| 2R_p (contact) | 1.682 fm | 0.0924 |
| r_e (hydrogen's c-boundary) | 2.818 fm | 0.0551 |
| a₀ | — | 2.9e-6 |
| ∞ | — | 0 |

**Transitions** (a mover settling inward from r_out to r_in): ∞ → 2R_p, ∞ → R_p, 2R_p → R_p, r_e → R_p, R_p → a, a → Ѻ_p, R_p → Ѻ_p, ∞ → Ѻ_p, R_p → R_p/3, a₀ → R_p.

**Movers:**
- electron m_e;
- proton-mass circulation m_p;
- one loop of the four-loop strand, m_p/4 (my reading of "the strand": the volume is shared equally among the four loops).

**Energy forms**, each as the difference between the two stations:
- **F (full):** m c² Δz = Δ(m v²);
- **H (half, the hydrogen rule):** ½ m c² Δz;
- **B (Law V budget spend):** m c² [√(1 − z_out) − √(1 − z_in)], i.e. the change in m c²(1 − v_circ/c) with v_circ = c√(1 − v²/c²). B is defined only for z ≤ 1.

**For each cell:**
- the photon wavelength λ = hc/ΔE and its band;
- the path implied by the movement law λ = 2L(c/v_in), L* = λ v_in/(2c), reported in fm and as L*/(2π r_in), the number of landing-radius circumferences.

**Shift block:** at each station, Δλ/λ from depth on the proton's ladder (z_p), on hydrogen's (z_H), and both, with the light law's speed factor (1 − z)² shown as a speed ratio.

**Validations:**
- V1: the hydrogen rule at a₀ on hydrogen's ladder gives ½ m_e c² α² = 13.6057 eV.
- V2: B → H to first order for small z (ratio → 1 as z → 0, checked at z = 1e-6).
- V3: hc = 1239.84198 MeV·fm.

**No observed radiation is compared in this pass.** The map is a construction. Any comparison must name one mover, one form and one transition before the observed value is loaded.

## Addendum 2026-10-12 (e): stage 3 census (registered before `ppt18_census.py`; Harvey asked "did any … match ANY previously recorded experimental outputs?")
- **This is a census.** It is reported with its look-elsewhere count and a chance baseline. Under the 2026-10-07 rule it is **not evidence**.
- **Cell chosen before matching** (Harvey: "you choose"): proton-mass circulation, H form, ∞ → contact = **43.3245 MeV**.
- **Grid values:** every F, H and B value in `ppt18_stage3_results.txt` (90 proton-ladder cells), plus the 20 hydrogen-ladder values.
- **Reference list** (MEASURED-INPUT; PDG/CODATA/AME values recalled, tagged [B]; fixed here before matching). Values in MeV:

| group | entries |
|---|---|
| leptons | e 0.51099895; μ 105.6583755 |
| mesons | π⁰ 134.9768; π± 139.57039; K± 493.677; K⁰ 497.611; η 547.862; ρ 775.26; ω 782.66; K* 891.67; η′ 957.78 |
| baryons | p 938.27209; n 939.56542 |
| excitations | Δ − N 293.7 (1232 − 938.3) |
| nucleon mass differences | n − p 1.29333; n − p − e 0.78233 |
| bindings, {p,n} list | d 2.22457; t 8.48180; h 7.71804; α 28.2957 |
| bindings, native list | d 1.44225; t 6.91714; h 6.93574; α 26.73102 |
| binding per nucleon | peak ⁶²Ni 8.7945; α 7.0739 |
| anomaly | X17 (ATOMKI) 16.94 |
| annihilation | 1.02200 (2 m_e) |

- **Match bands:** the cascade, B1 ≤ 0.1%, B2 ≤ 1%, B3 ≤ 3%. A cell equal to a reference **by construction** (rest energies at z = 1) is listed separately and not counted.
- **Chance baseline:** multiply every grid value by one random log-uniform factor in [0.5, 2], 20,000 trials. Report the mean number of B2 matches and the fraction of trials with at least the observed count.
