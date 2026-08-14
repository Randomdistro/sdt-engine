# Adversarial Referee Report — Spatial Displacement Theory

**Prepared as if by a hostile but competent PRL/PRD referee, using SDT's own derivation files and machine-readable provenance labels as the primary evidence.** Compiled 2026-07-06 from a full-corpus read (Laws, Theory ruleset, `laws.hpp`, and the FLM/PPT/EMC/APS/NP/GOM/CR/GD/SAR investigation verdicts). Nothing here is imported from outside SDT; every charge is sourced to the framework's own text with `file:line`.

> **How to read this.** A referee's job is not to be fair to the author's hopes; it is to find where the paper would mislead a reader who trusts it. SDT is unusual in that its *investigation files are already brutally honest* (they use IDENTITY / DEGENERATE / KILLED / OPEN correctly and refuse fitted knobs). The problem is a **two-layer inconsistency**: the honest labels live in the verdicts and in `laws.hpp` header comments, while the **headline prose** (the `Laws/LAW_OF_*` papers, several `laws.hpp` provenance stamps, the website, retracted-but-still-displayed PASS narratives) overstates them as DERIVED / zero-parameter. A referee reads both layers and reports the gap. That gap is the report.

---

## Summary judgment

- **The genuine result is a re-parametrisation, not a new dynamics.** SDT's clean content is a set of *identities and change-of-variables* (occlusion geometry → 1/r²; `ϟ ≡ GM/c²`; `v_circ²+v²=c²` ≅ Lorentz γ; shell-cancellation `Φ_shell = ε`) plus a genuinely suggestive *ontology* (push-not-pull, matter-as-vortex, time-as-tick). These are internally coherent and occasionally elegant. They are not, on the present evidence, predictive beyond the Standard Model + GR + Kepler.
- **The EM force scale is parameter-free but inherited from α, not derived from non-EM physics.** The pressure coefficient `P_eff` — which sets every force magnitude — is a pure derivation basis closed form `m_p²m_e²c⁵/(4παℏ³)` derived from the electron's centripetal requirement (it passes the delete-test; it is **not** a fit). What it is *not* is a derivation of electromagnetism from nothing: its magnitude is entirely α, the one EM input SDT does not derive. (Corrected after challenge from an earlier draft that wrongly called it a Coulomb calibration — see Part 1 §2.)
- **No number that was not put in comes out.** Not a single particle mass, not the mass ratio, not α, not a binding energy heavier than the deuteron, not H₀. The two genuinely-derived numbers in the whole corpus (the deuteron binding to 1.1%, and the neutron seat velocity 1.83c to 0.006%) are real and should be foregrounded — but they do not carry a theory.
- **There is an integrity problem**, already self-diagnosed: ~8 fabricated results clustered on famous single constants (Lamb shift, H₀, μ_n, 1.75″ lensing), some still displayed under their retraction banners. These must be quarantined before any external submission, or the first referee to find one discards the whole manuscript.

The strongest, most survivable framing of SDT is **"a neo-Lorentzian, Le-Sage-type re-parametrisation of gravity and EM with a topological particle taxonomy and an unusually honest audit trail."** The weakest and self-defeating framing is the one currently on the website: **"zero-parameter theory of everything, every constant computed."**

---

## Part 1 — Load-bearing failures (what a competent referee kills)

### 1. The convergence-pressure engine cancels out of every quantitative result
The flagship mechanism is convergent boundary pressure `P_conv = Nε ≈ 2.46×10⁴⁸ Pa`. But:
- The symbolic force theorem uses `P_conv` (`SDT_Complete_Laws.md:453`), while **every numerical result and the entire engine use a different pressure `P_eff`** (`laws.hpp:399-403`); `P_conv` appears **nowhere** in any force computation.
- `P_eff` is not `P_conv` reduced by a derived factor, nor is it fitted: it is **independently derived** from the electron's centripetal requirement as a derivation basis closed form `P_eff = m_p²m_e²c⁵/(4παℏ³) = 4αℏc/(π R_p² r_e²)` (`laws.hpp:361`; electropause, EMC04). It equals the atomic Coulomb scale by identity, but no measured Coulomb force is used to set it. (The engine still stamps it `class E / calibrated`; on the electropause algebra that is too harsh — EMC04's class-C claim, delete-test-passing, has the better case. See §2.)
- At hydrogen the occlusion dressing is trivial: substituting `R_charge = √(R_p r_e)` into `(π/4) P_eff R_charge⁴/r²` returns `k_e e²/r²` **identically** (`emc01_scroller.html:519-520`), so the 0.12% match is *consistency at the anchor, not an independent test* (`SDT_Complete_Laws.md:474`). The occlusion cross-section does non-trivial work only away from the EM scale (gravity, nuclear).

**Referee's kill line:** the force law's coefficient is `P_eff` (derived, α-based), **not** the shell pressure `P_conv ≈ 2.46×10⁴⁸ Pa`. `P_conv` enters no force computation; `f = P_eff/P_conv` (`laws.hpp:372`, `class E`) is a diagnostic ratio, not a bridge that does work. So the flagship *convergence pressure* does no quantitative work in the force sector — the force magnitude is carried entirely by `P_eff`, i.e. by α. Law I's mechanism is decorative w.r.t. every force number. (Law IV, by contrast, *does* stay circular: `m = ΦV_disp/3ℓ_P³c²` and `V_disp = 3mℓ_P³c²/Φ` are literal inverses — `laws.hpp:439,450`.)

### 2. P_eff is derived (parameter-free) but α-inherited — corrected after challenge
*An earlier draft called `P_eff` "a fitted scale calibrated to Coulomb." That was wrong; a challenge forced the check, and the check overturns it.* The electropause derivation (EMC04) fixes `P_eff` from a **kinematic** requirement, not a Coulomb fit: the electron sits at `a₀` moving at `v = αc`, so whatever holds it must supply centripetal force `F = m_e(αc)²/a₀ = m_e²α³c³/ℏ`. Invert the occlusion law `F = (π/4)P_eff R_charge⁴/a₀²` (`R_charge = √(R_p r_e)`) and it collapses to the pure derivation basis closed form

`P_eff = m_p²m_e²c⁵/(4παℏ³) = 5.23×10³¹ Pa`,

computed from `{m_p, m_e, c, ℏ, α}` alone. **No measured Coulomb force enters; it passes the delete-test.** So `P_eff` adds **no free parameter** — *"zero free parameters beyond the derivation basis" survives at this joint*, and the engine's `class E / calibrated / FAILS` stamp is too harsh (EMC04's class-C claim has the better algebra).

What honestly remains is narrower:

- **The magnitude is entirely inherited from α**, the one EM input SDT does not derive. Honest claim: *"the EM force scale is fixed by α + kinematics + occlusion geometry, parameter-free."* Overclaim: *"electromagnetism derived."* EMC04's own residual concedes it: *"α is still the one input."*
- **The hydrogen agreement is an identity**: `m_e(αc)²/a₀ ≡ k_e e²/a₀²` (given `a₀ = ℏ/m_e cα`), so the 0.12% match is consistency at the anchor, not an independent test.
- **Two documents disagree by ~π**: the engine's derived `5.23×10³¹ Pa` vs `LAW_OF_RADIATIVE_PRESSURE_ORIGIN.md:137`'s `1.65×10³¹ Pa` from a separate "numerical calibration" (ratio 3.167 ≈ π), self-flagged "cross-canon inconsistency, unresolved." The derived value is the engine's; the Laws-paper value is the outlier — retract or fix.
- The cosmological closure that would also make the *diagnostic* `f = P_eff/P_conv` parameter-free (CR05) is separately **retracted as fabricated** (`CR05_VERDICT.md:3`) — but `f` is not needed for `P_eff` itself.

So the corrected charge is not "P_eff is fitted" (false) but "P_eff is α re-expressed: SDT fixes the EM scale *using* the EM coupling, honestly and parameter-free, but does not *derive* it — and the showcase hydrogen check is an identity."

### 3. Koppa is a change of variables `ϟ ≡ GM/c²`, not a new theory of gravity
The koppa formalism is a clean, precision-honest re-parametrisation `GM ↔ ϟ = v²R/c²` — and the corpus stamps the identity nearly everywhere (`laws.hpp:647,680,837`; `an_argument_for_koppa.md:429-430`). But:
- Every orbital formula is obtained by the textbook substitution `GM → c²R/ϟ²` (`an_argument_for_koppa.md:258,319`); the equations of motion (Kepler `v=√(GM/r)`, the Schwarzschild potential, the Einstein field equations) are **imported and relabelled**, not derived from occlusion/pressure.
- The section meant to prove novelty (Mercury precession, §7) **self-refutes**: *"algebraically identical to the GR result … koppa gives [no] different prediction"* (`an_argument_for_koppa.md:429-430`).
- The 22-orders-of-magnitude orbital "fits" are **Kepler's third law by construction** (fit ϟ to one orbit, predict the rest via `v∝1/√r`) — zero degrees of freedom to falsify SDT vs Newton. Where a genuinely discriminating gate was set it **failed or is open**: GOM10 `μ_ϟ` failed its own 0.122% gate; GOM12 Earth–Moon census failed +0.727% and the E21 quantisation was a clean 0/7 null; GOM14's discriminating prior-free refit is OPEN and the shared-density-prior confound is not killed.
- The only "from-primitives" koppa (`koppa_per_baryon`, `laws.hpp:724-746`) reaches its value **only via `G = ℓ_P²c³/ℏ`** — i.e. G re-enters through ℓ_P (`risk_flag` at `:744`). "No G anywhere" is true only of quantities that are pure relabels of measured `GM`.

### 4. Mass is measured-in, not derived
`V_disp` (the exclusion volume that is the entire physical content of Law IV) is **hardcoded from the measured masses** (`laws.hpp:460,464`); feeding it back returns the mass by construction. No mass, no mass ratio, no lepton spectrum, no binding energy falls out. FLM12 (the "mass mechanism") concedes it computes **no number**: *"a correct ontology with an unpaid quantitative ledger, not a finished theory of mass"* (`FLM12_MASS_MECHANISM.md:286`). Its make-or-break tests came back **UNPAID** (deuteron D1, `FLM12_D1_VERDICT.md:6`) and **OPEN** (iron floor). There is also an unresolved **3× ambiguity** in the mass formula between `Laws/LAW_OF_INERTIAL_MASS...` (no 1/3) and `SDT_Complete_Laws.md:608` / `laws.hpp:450` (with 1/3).

### 5. Special relativity requires a preferred frame the theory admits it cannot see
`v_circ²+v²=c²` is a **posited axiom** (`laws.hpp:530-534`, "posited, not derived") observationally identical to the Lorentz factor — which the engine then **hardcodes** (`gamma(v)=1/√(1−β²)`, `laws.hpp:546`). The `v` in the budget is velocity relative to the lattice/CMB frame — an absolute frame that, by the corpus's own **neo-Lorentzian tension** (`PARADOX_CENSUS.md:344-352`), "must conspire to be locally invisible" to ~10⁻¹⁸ and predicts an absolute ceiling `c_∞ ≈ c+105 m/s` that is "not locally measurable." A referee reads that as *unfalsifiable-adjacent by construction.* And the headline "closure `z·ϟ²=1` verified across 126 ionisation levels" is a **pure identity**: `z·k² = (v/c)²(c/v)² = 1` for any v (`structural_analysis.cpp:200-203`); all 126 rows read `1.000000000` because a tautology cannot do otherwise. Presenting it as validation is the single most misleading claim in the Law V material.

### 6. The topological predictions are one-point fits or postdictions
- **W+1 radius rule** `R_wake=(W+1)ℏ/mc` is a **conjecture** (`laws.hpp:1090,1366`) that predicts exactly one number (R_p to 0.02%) with one integer knob, and **fails for the electron** (g(W=1)=α≠2), which is then handled by a different mechanism and relabelled. It is pre-insulated as a "branch test, not full-SDT kill" (`laws.hpp:1060`).
- **6π⁵ = 1836.118** was OPEN at this audit date. **Superseded
  2026-08-14:** PPT17 resolves its physical assignment as the shared-input
  packing count from the point electron's 720-degree Bohr-closure tube into
  the W=3 torus at `R_p`. This closes the construction, not an independent
  prediction; the historical look-elsewhere warning remains applicable.
- **α is an input** (PPT02 negative result); "α = koppa at H" is a restatement, not a mechanism (`PPT02:87-88`).
- **Only two stable charged particles**: the knot-theory half (Alexander Δ≠1 protects the trefoil) is sound; the energetics half (why W=2/W≥4 decay) rests on **PPT09, a retracted fabricated verdict**. And **muon/tau** are the same W=1 as the electron — the "two knot types = two particles" claim is contradicted inside Law VI by its own lepton family (`LAW_OF_VORTEX...:325`, masses "restated, not predicted").

### 7. Nuclear physics: deterministic bookkeeping + one derived binding energy
The construction grammar `n_t=A−2Z, n_d=3Z−A−2` is **two linear equations in two unknowns** — a deterministic relabel that NP03A itself grades **IDENTITY** ("proves NO geometry"). Binding: **exactly one knob-free result** (deuteron 2.200 vs 2.224 MeV, NP17), while the alpha under-binds electrostatically **6.35×** and everything heavier is PENDING; two of the three proposed binding mechanisms (NP05 volume-price, NP06 gear-frequency) are **KILLED**. Magnetic moments: **zero earned predictions** (best μ_p is flagged numerology; μ_n magnitude is an identity with an assumed sign). A **charge-radius law that was killed at 890% RMS** (NP12) is **still live in the engine** (`laws.hpp:415`, `R_nuc = Z·R_p`) and still showcased on its one surviving He-4 point.

### 8. Cosmology loses to ΛCDM on data, or ties it
- **Pantheon+**: SDT coasting **loses to ΛCDM, ΔAIC ≈ 90** (`CR12_VERDICT.md:13-18`); two other independent fits agree (CR06 ΔAIC=+31; Hubble/17 BIC 107× worse). The one thing earned (EdS/deceleration excluded) is shared with ΛCDM, not evidence for SDT.
- **"No dark matter"**: the *shipped* eclipse-saturation law gives **RMS 66%** on SPARC and structurally cannot supply the missing velocity (`GD05/INVESTIGATION.md:52`); the rescue (M4, RMS 23.8%) **borrows the MOND interpolation function and the Milgrom scale `a₀=cH₀/2π`** (`GD05/INVESTIGATION_twin_regime.md:88`) and is still **worse than MOND** (~10%) on the same data. Every other rotation route is circular (GD03) or falsified behind inflated gates (GD04, GD01 retracted).
- **Degeneracy**: CR10 (z³) and CR11 (Tolman) are self-labelled **DEGENERATE** with ΛCDM — reproduce the same numbers, discriminate nothing.
- **Circular inputs**: `R_CMB`, `H₀`, the BAO scale, and the 48-Gyr age are **hardcoded observed anchors** (`cosmology.hpp:70-124`), several mislabelled "from topology." Depth-closure `z=ϟ/r` is **algebraically GM/(c²R)** — the same weak-field redshift GR predicts (`01_THEOREM.md:56-65`); the 0.03% is the residual between two ways of writing GM/c², not independent corroboration.

**Balance (owed after challenge — "the entirety of ΛCDM is fitted").** True, and it tempers the framing: base ΛCDM is 6 free parameters, ~95% of its budget is an inferred dark sector, and Λ is a ~10⁻¹²² unexplained fine-tune. "SDT loses to ΛCDM" is *not* "loses to a first-principles prediction" — it loses to a fitted curve, and AIC rewards *description*, not *explanation* (it charges 2 per parameter and nothing for a 122-order fine-tune). By an explanation-weighted score a worse fit with no dark sector is the better science — which is the frame SDT is built for. Three residuals keep the loss real: (i) on the SN Hubble diagram specifically the fight is ~1 shape parameter vs ~1 (Ω_m vs SDT's exponent), so the dark-sector flexibility is *not* what beats SDT there — its curve just tracks the points worse; (ii) ΛCDM's genuine edge is **over-determination** — 6 numbers pinned by the CMB then *predict* the BAO scale and SN distances without re-fitting (concordance, itself straining under the 5σ H₀ tension) — and SDT cannot yet pin one law that predicts across probes (the exponent that fits SNe misses the acoustic angle by 2.21×); (iii) parameter-economy is SDT's *stated* advantage but an **unrealized** one until it fits across probes without a dark sector. So the corrected verdict: **SDT fits worse than a heavily-fitted model while not yet cashing the parameter-economy that is its whole reason to exist.**

**The discriminator that beats the χ² fight — amplitude/time, not distance.** An expanding (or any genuinely frequency-*rescaling*) redshift dims and *stretches* the signal in z-dependent ways that are observed and that killed tired-light: SN Ia light-curves time-dilate by (1+z) (a z=1 event fades 2× slower — Goldhaber 2001, Blondin 2008); surface brightness follows the Tolman (1+z)⁴; CMB T∝(1+z) to z≈3. These do **not** uniquely prove metric expansion — they prove redshift is a *uniform rescaling of all timescales*, not an energy drain. So the sharp, decidable SDT test is: **does the κ-squeeze propagation redshift stretch the weeks-long SN light-curve envelope by (1+z), or only lower photon energy?** Uniform-rescale → SDT clears the bar that buried tired-light; energy-loss-only → it dies the same death. Not addressed in the corpus (CR07 tests QSO line *sharpness*, a scattering test, not time-rescaling). This is worth more than any distance-fit and is currently **OPEN**.

---

## Part 2 — The integrity problem (must be fixed before any submission)

The corpus's own HUNTER scour (`Investigations/HUNTER_SCOUR_2026-07-02/MASTER_LEDGER.md`) documents **~8 fabricated results, clustered exactly where a famous single constant sits**:

| Item | Fabrication |
|---|---|
| APS04 Lamb shift "1051.8 MHz, 0.57%, zero-fit" | `.cpp` never compiled; real formula ≈3145 MHz; a knob was fished |
| CR05 "H₀ = 67.4 DERIVED" | Planck H₀ hardcoded; line 371 overwrites the computed value; ΛCDM Ω's relabelled "topology" |
| PPT08A rolling solver "Class A <10⁻¹⁵" | radius increment below float precision → compares a constant to itself |
| PPT09 winding "Class A PASS" | tool prints `PREDICTION FAILED`; verdict asserts the opposite |
| OP01 lensing "Class C PASS" | rebuilt tool fails (0.836″ vs 1.75″); gate retro-loosened, phantom row invented |
| Hubble/17 "no dark energy proof" | its own tool ranks SDT dead last, 107× worse than ΛCDM |
| μ_n "−1.913 μ_N, 0.002%" | feeds the **measured** g_n in (target-in/target-out) |
| `laws.hpp` `lamb_shift_native_MHz = 1051.8` | the fabricated literal **laundered into the canon**, rode into B04 |

Several of these **still display their full PASS narrative below the retraction banner** (CR05, APS04, Hubble/17) — a live contamination risk: a reader who scrolls past line 3 reads a clean win. To the author's credit, the repair (2026-07-03/04) deleted the laundered literal, de-tallied the fake benchmarks, and reclassified the fabrications KILLED while keeping their *hypotheses* OPEN. **But the retracted PASS bodies must be physically removed or clearly struck, not left under a banner**, before any of this goes to a stranger.

---

## Part 3 — What actually survives (a fair referee says this too)

Stripped of overstatement, these are real and worth keeping — several are genuinely interesting:

- **The occlusion geometry → 1/r² with Newton III** is a clean structural result (class C, survives the delete-test): one mechanism giving Coulomb/gravity/nuclear as the *same* inverse-square law is a legitimate unification of *form*.
- **Koppa as bookkeeping**: orbital dynamics genuinely never needed the Cavendish G; expressing results in `(ϟ, R)` avoids importing G's 22-ppm uncertainty. A correct, useful, honestly-labelled observation.
- **Depth-closure single-law collapse**: `v = c√z` spanning ~15 orders (Earth surface → proton, 1.83c) is a striking organising identity, even if each point equals the GR value.
- **GD06 solar-limb lensing 1.7517″ (0.10%)** and **CR12's exclusion of EdS/deceleration** are honest, competitive results.
- **GD05-M4 rotation curves without a dark halo** (RMS 23.8%) is a real near-MOND fit; the asymptotic `a₀=cH₀/2π` is a legitimate SDT-native prediction even though the crossover is borrowed.
- **μ_ν ≡ 0 exactly** from W=0 (no ℓ=2 wake) is a clean, falsifiable, SDT-native prediction (PPT04).
- **The deuteron binding to 1.1% with no fitted energy scale** (NP17) and the **1.83c neutron seat to 0.006%** (NP20) are the two genuinely-derived numbers — foreground these.
- **The topological skeleton** (solid-torus n=3g uniqueness, Alexander-polynomial protection of the trefoil) is internally coherent and SDT-native.
- **FLM08's corner-sharing tetrahedral random network** (27 pass / 0 fail, every invariant reached by ≥2 independent branches) is a real geometric result, honestly held short of "the vacuum IS this."
- **The audit apparatus itself** — two-axis provenance/correspondence classing, the delete-test, IDENTITY/DEGENERATE/KILLED discipline, refusing fitted knobs — is better epistemic hygiene than most published physics. It is the project's single strongest asset and the reason this report could be written from the inside.

---

## Part 4 — The three questions that decide it

A referee would return the manuscript with three demands, any *one* of which, if met, changes the verdict from "re-parametrisation" to "candidate physics":

1. **Derive one number you did not put in.** A lepton mass, the mass ratio 1836.15 from a *mechanism* (not a search), α, or a binding energy heavier than A=2. The corpus's own OPEN list says none of these is done.
2. **Exhibit ONE observable that distinguishes SDT from GR+QM+ΛCDM.** Not a re-derivation of an agreed number (those are identities), and not a degenerate cosmology fit. The neo-Lorentzian `c_∞` is admitted un-measurable; μ_ν≡0 is ~8 orders below testability; the depth-closure P2 (+105 m/s) carries ±20% and is untested. Name one that is measurable this decade.
3. **Publish the dependency graph acyclic.** "Zero free parameters" with a derivation basis containing α and m_p is a contradiction until the graph is shown to derive them without assuming them (`PARADOX_CENSUS.md:354`). Until then, the honest count is **≥2 irreducible seeds** (ℓ_P, and α-or-m_p), not zero.

---

## Verdict

**Reject as "a zero-parameter theory of everything." Reconsider as "a neo-Lorentzian/Le-Sage re-parametrisation with a topological particle taxonomy and an exemplary audit trail,"** provided (a) the fabricated results are excised, not merely bannered; (b) the two-value P_eff and the 3× mass ambiguity are resolved; (c) the headline prose is brought down to the class labels the engine already carries; and (d) at least one of the three questions in Part 4 is answered.

The theory's fatal move is rhetorical, not physical: it *has* honest labels and it *chooses* to headline the overstated ones. A referee cannot be angry at a framework that indicts itself in its own comments — but a referee also cannot pass "every constant computed" when the author's own files say `class E`, `IDENTITY`, `OPEN`, and `FABRICATED`. Bring the marketing down to the ledger, and there is a real, defensible, unusual paper here — a small one, about pushing instead of pulling and counting instead of flowing — not the theory of everything the website promises.

*— Referee (adversarial pass), against SDT's own evidence.*
