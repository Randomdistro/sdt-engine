# GOM24 — The Cassini Ring-Moon Corpus: the contrarotational seat

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Standing rule (absolute):** no G, no M, no GM anywhere in-chain. Koppa is kinematic:
> Ϟ = 4π²a³/(T²c²) from a dependent's (a, T). Rival values appear only in columns labelled
> `INFORMATIONAL-RIVAL` and are never load-bearing.

---

## ⓪ The Golden Rule — five questions answered up front

1. **What don't we know?** Whether a body seated between two counter-streaming ring flows is
   *rolled* by that shear — and whether the equatorial ridges, the gap-edge waves, and the
   unmeasured spin states of Saturn's eight ring-embedded moons are three faces of one mechanism.
2. **Why does it matter?** Eight bodies occupy the same geometric seat under one primary with one
   dataset. It is the largest controlled sample of the contrarotational position anywhere. If
   occlusion gearing acts at contact, this is where it is visible without a single borrowed mass.
3. **How will we find out?** Kinematic koppa per moon from (a,T); a shear-couple ledger; a
   ridge-prominence census against local shear; and the wave-parity test on the Keeler and Encke
   gap edges — all from Cassini ISS geometry and PDS shape models.
4. **What would prove us wrong?** Five falsifiers with numeric triggers in §8. The decisive one:
   if the two gap edges carry a **common** vertical phase rather than a **mirrored** one, the
   encounter-geometry mechanism is excluded and orbital inclination carries the waves.
5. **How will we know we're done?** Dual verdict — prompt completion (A–D) plus physics class
   (NATIVE / CONVERGENCE / IDENTITY / NULL), with the ridge census and the parity test each
   reported separately, pass or fail.

---

## 1. Executive Summary

Eight small moons — Pan, Daphnis, Atlas, Prometheus, Pandora, Janus, Epimetheus, Aegaeon — sit
embedded in or bounding Saturn's rings. Each occupies the same seat: ring material inside its
orbit overtakes it, material outside falls behind it, so every one is a bearing between two
counter-running walls. **Does that shear roll them?** Three of the eight carry equatorial ridges
found nowhere else in the solar system, and the ridges stop dead at ~138,000 km. **No spin state
has ever been measured for any of the three.** We expect a kinematic ledger that (i) predicts
which bodies carry ridges from shear alone, (ii) predicts the parity of the gap-edge waves, and
(iii) names one measurement — the spin sense of Pan, Daphnis or Atlas — that decides between
shear-driven roll and tidal lock.

---

## 2. Physical Context

**The seat.** A body at semi-major axis *a* in a ring sees material at *a − δ* orbiting faster
and material at *a + δ* orbiting slower. In its own frame the inner wall runs forward and the
outer wall runs backward. That is a bearing between opposed belts. The couple is real and its
sense is fixed: taking the orbit counterclockwise, a force in +ŷ applied at −x̂ and a force in
−ŷ applied at +x̂ both give torque **−ẑ**. Kepler shear therefore drives **retrograde** spin,
while tidal locking drives **prograde** spin at exactly one turn per orbit. The two oppose. Which
wins is unmeasured for every ridge-bearing moon in the set.

**The ridges.** Pan, Daphnis and Atlas carry equatorial skirts. Atlas is more than twice as wide
as it is tall. Nothing else in the solar system is shaped like this. The ridges lie **in the ring
plane** — which is also the plane perpendicular to the shear-couple axis, so orientation alone
cannot separate accretion from rotational bulging.

**The waves.** Daphnis raises structure on both Keeler gap edges with vertical relief measured by
**shadow length** at low solar elevation (a ruler measurement, model-free) and a wavelength
λ = 3π·Δa that follows from Kepler shear alone. The moon's orbital **inclination**, by contrast,
is a fitted quantity — plausibly extracted from the very waves it is invoked to explain. This
investigation must not inherit that circularity.

**Key variables.** *a* [m] semi-major axis; *T* [s] orbital period; *T_spin* [s] rotation period
(UNMEASURED for Pan/Daphnis/Atlas); *R_eq*, *R_pol* [m] shape axes; Δa [m] radial offset from the
moon's orbit to a gap edge; λ [m] edge-wave wavelength; *h* [m] vertical relief from shadows;
Σ [kg m⁻²] local ring surface density (`INFORMATIONAL-RIVAL` only).

---

## 3. Theoretical Framework

**Koppa, kinematic only.** For each moon, Ϟ = 4π²a³/(T²c²). Every moon of Saturn must return the
same Ϟ_Saturn ≈ 0.4221 m; the spread across the eight is the instrument-noise floor of this run
and must be reported before any physics is claimed.

**Depth account.** z_d = Ϟ_Saturn / a. Across the eight this runs 3.16×10⁻⁹ (Pan) to 2.52×10⁻⁹
(Aegaeon) — a **smooth 25% decline with no break**. The ridge boundary is therefore *not* a depth
boundary, and any claim that it is must be refused at Phase 2.

**Rotation account (GOM17).** z_rot = (2πR/T_spin)²/c². For a locked body T_spin ≡ T_orb, so
z_rot = z_d·(R/a)², and the ledger ratio reduces identically to (T_orb/T_spin)². **This is an
identity and is licensed only as a classification column** — it may not be scored as a prediction
anywhere in this run (GOM15/GOM17 precedent; identity flag committed here).

**The shear couple (the new content).** The velocity difference across the body is
Δv = |dv/da|·2R with v(a) = c√(Ϟ/a), giving dv/da = −½·c√Ϟ·a^(−3/2). Define the dimensionless
**seat number**

  𝒮 ≡ (Δv / v) · (a / R) = R · |dv/da| · 2a / (v R) — reduce symbolically before coding.

𝒮 is built from (a, T, R) only. The prediction under test: **ridge prominence R_eq/R_pol is a
monotone function of 𝒮 × (residence proxy)**, and vanishes where the body is not in contact with
dense ring material.

**Wave parity (the discriminant).** Inner-edge particles approach from behind and pass inboard;
outer-edge particles approach from ahead and pass outboard. Both the radial offset and the
relative velocity reverse sign, so the induced vertical circulation sense goes as their cross
product and **reverses between edges**. An inclination-driven wave references the moon's tilted
plane and imprints the **same** vertical phase on both edges. These are opposite, checkable
predictions on the same images.

**Forbidden inputs.** No G, no M, no GM. No ring surface density in-chain. No use of the published
Daphnis inclination as an input to anything (it may appear only as `INFORMATIONAL-RIVAL`).

---

## 4. Strategy — five phases with pre-registered gates

**P1 — Koppa invariance across the eight.** Compute Ϟ from each moon's (a, T) independently.
Report median, per-moon residual, fractional spread s. **Gate G1:** s < 1×10⁻⁴ after excluding
only bodies flagged for orbit quality (Janus/Epimetheus swap their orbits every ~4 years and must
be handled with epoch-matched elements — the exclusion rule is orbit-quality class, declared
before residuals are seen, never residual size). Report the worst body as well as the best.

**P2 — The depth ledger, and the refusal.** Tabulate z_d per moon. Show explicitly that z_d
declines smoothly by ~25% across the set with **no discontinuity at the ridge boundary**.
**Gate G2:** if any candidate depth-based ridge criterion is found to separate the set at
p < 0.05 under a permutation test over the eight, it must be reported — but a smooth z_d is the
expected result and a null here is a *pass*, not a failure. This phase exists to kill a
tempting wrong answer before it is reached for.

**P3 — The ridge census.** For each of the eight, compute 𝒮 from (a, T, R) and tabulate against
measured R_eq/R_pol from PDS shape models (Pan 1.6, Daphnis 1.3, Atlas 2.1, five others ≈ 1).
**Gate G3a:** Spearman ρ(𝒮, R_eq/R_pol) > 0.7 across n = 8. **Gate G3b (the honest one):** the
accretion hypothesis predicts the *same* ordering, so a ρ pass is **CONVERGENCE, not NATIVE**,
unless P4 or P5 breaks the degeneracy. State this in the verdict before computing ρ.

**P4 — Wave parity on the gap edges.** From Cassini ISS frames of the Keeler gap (Daphnis) and
Encke gap (Pan): measure λ against Δa on both edges and confirm λ = 3π·Δa; then extract the
vertical phase on each edge from shadow geometry at known solar elevation. **Gate G4:** the two
edges are **mirrored** (phase opposition, |Δφ − π| < π/4) → encounter geometry; **common**
(|Δφ| < π/4) → inclination. This is the decisive phase and it is the reason the run exists.

**P5 — The naming of the missing measurement.** Compute, for each of Pan, Daphnis and Atlas, the
predicted spin period under (a) tidal lock and (b) shear-driven equilibrium, with the observable
difference stated in hours and in Cassini-equivalent pixel motion. Output a one-page observing
spec. **Gate G5:** the two predictions must differ by more than any plausible measurement error,
or the discriminant is not reachable and must be labelled so.

---

## 5. Success Criteria — dual verdict

**Prompt completion:** A (all five phases run, gates honoured, nulls reported as nulls) ·
B (P1–P3 only) · C (P1–P2 only) · D (incomplete).

**Physics class, reported per phase, never aggregated:**
- P1 → expected IDENTITY/instrument (koppa invariance is a consistency check, not evidence)
- P2 → expected NULL (this is a pass)
- P3 → CONVERGENCE at best, unless P4 breaks the degeneracy
- P4 → NATIVE if mirrored, EXCLUDED if common, OPEN if unresolvable at Cassini resolution
- P5 → SPEC (an observing proposal, not a result)

**A run in which P3 passes and P4 is unresolved may not be reported as support for the roll.**

---

## 6. Outputs

1. `RUN_LOG.md` — mandatory, pre-run commitments copied in before any code.
2. `gom24_ring_moon_ledger.cpp` — C++20, `#include <sdt/laws.hpp>`. P1–P3. Emits the koppa
   invariance table, the z_d table, and the 𝒮 vs ridge census.
3. `gom24_moons.csv` — declared inputs: name, a [km], T [d], R_eq, R_mid, R_pol [km], T_spin
   [d or `UNMEASURED`], source per row, epoch. **No masses.**
4. `gom24_wave_parity.md` — P4: frame list with PDS image IDs, measured λ vs Δa, solar elevation,
   shadow lengths, extracted phase per edge, and the parity verdict.
5. `GOM24_OBSERVING_SPEC.md` — P5: the spin-sense measurement, instrument requirements, and why
   it decides.
6. `GOM24_VERDICT_DIRECT_<date>.md` — dual verdict, per-phase classes, falsifier outcomes.

---

## 7. Dependencies & References

**Upstream (required):** `laws.hpp` `bridge::` (koppa) · GOM17 (z-account definitions; the
identity flag) · GOM15 (Finding 1 precedent: single-body match, look-elsewhere discipline) ·
GOM02 (kinematic-only standing rule).

**Downstream (blocked):** any claim that occlusion gearing acts at contact scale; the
"contrarotational position" entry in the public copy; APS/EMC wake work that would inherit a
contact-gearing result.

**Related (informative):** GOM23 (Koppa on a straight line) · FLM07 (glancing transfer, void
gearing, 1:4) · the two-regime/occlusion-saturation note (g→2 near contact).

**Data:** PDS Rings Node — Cassini ISS calibrated frames of the Keeler and Encke gaps (the
2017-01-16 Daphnis ring-grazing sequence is the primary set); Cassini shape models for the inner
small moons; SPICE kernels for epoch-matched elements. **Cite by file, hash at read.**

---

## 8. Falsification Tests

| # | Trigger (numeric) | Consequence |
|---|---|---|
| F1 | P1 koppa spread s ≥ 1×10⁻⁴ with no orbit-quality cause | The dataset is not clean enough to carry any of this; stop and fix inputs before P3 |
| F2 | P3 Spearman ρ ≤ 0.7 | The shear-seat reading of the ridges FAILS; ridges are not shear-ordered; report and withdraw the mechanism |
| F3 | **P4 edges carry a common vertical phase (\|Δφ\| < π/4)** | Encounter geometry EXCLUDED; inclination carries the waves; the roll mechanism loses its only imaging test |
| F4 | Measured λ departs from 3π·Δa by >20% on either edge | The shear-wake reading is wrong at the outset; P4 is void and must be re-specified |
| F5 | Any published Daphnis inclination is found to have entered the chain as an input | Run VOID (circularity — the fitted quantity explaining the measured one) |
| F6 | P5 predicted spin periods differ by less than plausible measurement error | The discriminant is unreachable; label OPEN-unreachable, do not soften |

---

## 9. Implementation Notes

Use `double` throughout; a spans 1.3×10⁸ to 1.7×10⁸ m while z_d ~ 10⁻⁹ — form dimensionless
ratios before differencing. Compute Ϟ per moon and difference against the **median**, not the
mean, so one bad row cannot drag the centre.

Janus and Epimetheus **exchange orbits every ~4 years**; their (a, T) are epoch-dependent and
must be drawn from the same epoch as each other and flagged. Aegaeon is ~0.5 km and its shape
model is poor — carry its error bar explicitly rather than dropping it silently (a silent drop
is a cap, and caps must be logged per §0).

For P4, solar elevation at the frame epoch sets the shadow-to-height conversion; get it from
SPICE, not from the image caption. Measure λ at three or more Δa values per edge so the 3π slope
is fitted, not asserted from one point.

**Visualisations that would inform:** (1) 𝒮 vs R_eq/R_pol, n = 8, with the ridge boundary marked;
(2) z_d vs a showing the smooth decline against the sharp ridge cutoff — the picture that kills
the depth explanation; (3) the two gap edges stacked with their extracted vertical phases, which
is the whole of P4 in one frame.

---

## ⑩ Adaptive Execution Protocol

**Pre-Run Commitment Block — copy into `RUN_LOG.md` before any code:**

```markdown
## Pre-Run Commitments — GOM24
- Prompt completion target: A
- Physics class hoped: P4 NATIVE; P3 CONVERGENCE; P1 IDENTITY; P2 NULL
- CALIBRATED budget: 0
- Phase thresholds: G1 s<1e-4 · G2 null expected · G3a rho>0.7 · G4 |dphi-pi|<pi/4 · G5 separable
- Exclusion rule (declared before residuals seen): orbit-quality class only —
  Janus/Epimetheus epoch mismatch, Aegaeon shape-model quality. Never residual size.
- Forbidden retroactive changes: the ridge boundary radius; the parity threshold;
  any use of published Daphnis inclination as input; any mass entering the chain.
```

**Pivot table:**

| Trigger | First response (PIVOT) | If pivot fails | Forbidden |
|---|---|---|---|
| G1 fails on Janus/Epimetheus | Re-pull epoch-matched elements, re-run | Exclude the pair *with reason logged*, report n=6 | Excluding by residual size |
| G3a ρ ≤ 0.7 | Test 𝒮 against R_eq/R_mid instead of R_eq/R_pol (declared alternative, one only) | Report F2, withdraw the shear-ridge reading | Adding a third shape metric until one correlates |
| G4 unresolvable at Cassini resolution | Restrict to the 2017-01-16 highest-res subset and re-measure | Report OPEN-unreachable and write P5 anyway | Reporting P3 as support in the absence of P4 |
| λ misfits 3π·Δa | Check Δa is measured to the moon's orbit, not the gap centre | Report F4, void P4 | Fitting a free coefficient in front of 3π |

**Allowed adjustments:** numerical method; image subset selection *by resolution, declared
before phase extraction*; symbolic reduction of 𝒮; splitting P4 into Keeler and Encke sub-runs.

**Disallowed:** retro-PASS; scoring the (T_orb/T_spin)² identity as a prediction; importing ring
surface density in-chain; presenting accretion-degenerate results as NATIVE; any silent cap.

**Dual verdict reminder:** prompt completion and physics class are reported separately, and the
per-phase classes are never aggregated into a single headline.
