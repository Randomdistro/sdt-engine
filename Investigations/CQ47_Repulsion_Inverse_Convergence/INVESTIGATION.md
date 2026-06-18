# CQ47 — Is Particle Repulsion the Inverse of the Convergence?

> **Author:** James Christopher Harvey, Melbourne. 2026-06-18.
> **Status:** theory investigation, opened from the question *"is particle repulsion the inverse
> of the convergence?"* Grounding in `repulsion_inverse.js` (Node).
> **Honesty contract:** the *structural* result — repulsion = a throughput **excess** (source),
> attraction = a throughput **deficit** (sink), gravity = the monopole sink-only term — is
> **[STRONG]** and grounded in the existing wake tensor. The *quantitative* derivation that the
> dipole source-lobe carries the exact Coulomb magnitude from vortex handedness is **[OPEN]** and
> shares the P_eff coefficient caveat ([[CQ01]], [[CQ33]]).

---

## 0. The question

Occlusion produces **attraction**: a body casts a convergence shadow, the unoccluded side wins, and
the second body is pushed *toward* the first. That is gravity, and it is opposite-charge attraction,
and it is nuclear binding. But **like charges repel.** Pure occlusion has no obvious way to push two
bodies *apart* — any two displacements shadow the convergence *between* them, which can only pull
them together. So: **where does repulsion come from?**

Harvey's hypothesis: **repulsion is the inverse of the convergence.** Where attraction is a local
*sink* in the convergence throughput (a deficit, a shadow), repulsion is a local *source* (an
excess, an anti-shadow) — the convergence run locally **backwards**.

---

## 1. The force is the sign of the throughput modulation **[STRONG]**

Model the net force on a body as proportional to minus the gradient of relay throughput it sits in:
it is pushed **toward** a deficit and **away from** an excess. (`repulsion_inverse.js`.)

| throughput *between* two bodies | modulation | net force |
|---|---|---|
| **deficit** (shadow / sink) | − | **attraction** (toward) |
| ambient (nothing) | 0 | none |
| **excess** (source / anti-shadow) | + | **repulsion** (apart) |

So attraction and repulsion are **one mechanism read with opposite sign**: attraction rides the
convergence (a sink between the bodies), repulsion inverts it (a source between the bodies). The
magnitude is set by |modulation|; the direction by its sign. This is exactly what "repulsion is the
inverse of the convergence" requires.

## 2. The magnitude test the hypothesis must pass — and does **[STRONG]**

If repulsion is the ± inverse of one and the same throughput modulation, then like-charge repulsion
and opposite-charge attraction must have **equal magnitude** for equal charge. They do — exactly:

$$ |F_{\text{repel}}| = |F_{\text{attract}}| = \frac{k_e e^2}{r^2} \quad(\text{Coulomb, symmetric in sign}). $$

At r = 10⁻¹⁰ m both are 2.307×10⁻⁸ N, equal to the part in the last digit. A mechanism in which
repulsion were a *different* process from attraction would have no reason to match magnitudes; the
**inverse-of-one-modulation** picture forces the match. ✓

## 3. Why gravity is attraction-only and charge is bipolar — the wake tensor **[STRONG]**

The hypothesis immediately explains the deepest asymmetry in physics: **mass only ever attracts,
charge does both.**

> **Ontology correction (Harvey, 2026-06-18): there are no monopoles.** The convergence is **not**
> a monopole — it is a **throughpole (a twopole)**: throughput *passes through* every point (in one
> boundary, out the opposite, transparently through empty spation); it never terminates in a sink or
> springs from a source. **No pole-source and no pole-sink exists.** And **light is an emission** —
> a propagating *phase-impulse* of the through-flow (the "influx impulse of phase as EM") — a
> distinct channel from both the steady through-flow and from charge. So the "ℓ = 0 / ℓ = 1" labels
> below are *multipole moments* (math), **not** pole-objects. Gravity and charge are
> **occlusion/redirection patterns of the one throughpole**, never poles in their own right.
>
> **And there is no "charge" entity at all (Harvey, 2026-06-18).** What is *called* charge **is**
> the handed redirection — there is no charge substance, primitive, or carried property. "+e / −e"
> are the two **handednesses** ((2,3) vs (1,1)), not two amounts of a stuff; **e is an SI
> unit-bridge** (CQ37: e is a *unit*, not a derived charge — you do not derive a unit). Throughout
> this doc "charge" is shorthand for *the handed redirection*, never a thing. This also re-poses the
> open step below: the target is not "derive e/charge" (a category error) but **derive the
> redirection magnitude** (the force coefficient P_eff) from the (1,1)/(2,3) geometry — e²/4πε₀ is
> merely its SI dress.

It then falls straight out of the structure of a vortex's wake (manuscript Part VIII; ℓ = 0 mass,
ℓ = 1 Coulomb, ℓ = 2 magnetism):

- **ℓ = 0, the symmetric wake = MASS.** Gravity is the **symmetric, subtractive occlusion** of the
  throughpole: a body can only *block* through-flow (cast a shadow), never *add* to it. The ℓ=0 term
  is therefore sign-definite — a **deficit only, no surplus possible** — hence only attraction.
  **This is why there is no antigravity:** occlusion can shadow but never anti-shadow. (It is not a
  "sink-pole"; it is a *subtraction* from a two-ended through-flow.)
- **ℓ = 1, the handed wake = CHARGE.** The vortex's handedness **redirects** the through-flow — it
  can *focus* it into a local **surplus** or *defocus* it into a local **deficit**, set by
  directionality (vortex handedness = "occluded influx directionality", the SDT definition of charge
  sign, [[CQ37]]):
  - **same sign →** handedness focuses between them → **surplus → repulsion**;
  - **opposite sign →** handedness defocuses between them → **deficit → attraction** (with gravity).

So *repulsion is the focused-redirection lobe — the inverse of the defocused (deficit) lobe that is
attraction.* Occlusion (mass) can only **subtract** → attraction-only; redirection (charge) can
**focus or defocus** → both signs. The hypothesis is not a new postulate — it is the
**occlusion/redirection structure of the one throughpole**, named correctly. Crucially the surplus
is a *focusing of the through-flow*, **not** a pole-source emission (that would be a forbidden
monopole; emission is reserved for light).

## 4. Why charge dominates gravity **[CONTEXT]**

The dipole (source/sink) channel is ~10³⁹× the monopole deficit (engine B21: EM/gravity ratio
2.27×10³⁹). Every pair of bodies carries the monopole attraction (their mutual gravity); a charged
pair *adds* the dipole term, which for like charges is an excess (repulsion) ~10³⁹× stronger,
burying the tiny mutual gravity. So like charges fly apart, and we never *see* the underlying
universal attraction between them — but it is there, beneath the dominant inverse-convergence push.

## 5. The picture, stated plainly — and the fork resolved **[RESOLVED]**

> **Attraction = a local defocusing of the throughpole (a deficit, a shadow) — through-flow turned
> away from the gap. Repulsion = a local focusing (a surplus) — through-flow turned into the gap.**
> Both are the **same one through-flow, redirected**; charge sign is the handedness of the
> redirection. Gravity is the symmetric subtractive occlusion alone (deficit only) so it has no
> inverse and only ever attracts; charge is the handed redirection, which focuses **or** defocuses —
> so it does both.

Repulsion is not a second force, and it is **not a pole**. It is the **same throughpole, redirected
with the opposite handedness** — the focused twin of the deficit that is attraction.

**The fork (literal outflow vs redirection) is resolved by the corrected ontology — decisively.**
Earlier the open question was: is the "source" lobe a *literal outflow* (spations streaming out of
the proton) or a *redirection* of the inflow? Answer: **redirection — a literal outflow is
impossible, because there are no monopoles.** A point that only emits through-flow would be a
pole-source — a monopole — and none exist; the convergence itself is a **throughpole**, not a
monopole, so a charge cannot be one either. (And **emission is already taken**: light is the
emission — a propagating phase-impulse — which is *not* a steady radial source, hence no monopole.)
Natively, then: the **(2,3) handedness focuses the convergent through-flow** into a directional
surplus, read as positive charge; **(1,1) defocuses** the other way (negative). Surplus and deficit
are one through-flow, handed — a **redirection pattern, not a divergence.**

The discriminator now stands as a *check*, not an open question: literal outflow would make p⁺ an
**emitter** and e⁻ an **absorber** (asymmetric — two kinds of thing); redirection makes both the
**same through-flow, opposite handedness** (symmetric, parsimonious). The net 1/r² of charge is then
a **directional-occlusion pattern — the gravitational shadow, but handed.**

## 6. Falsifiable consequences

1. **No antigravity, ever, from mass alone.** The monopole has no source lobe; a deficit-only term
   cannot become an excess. SDT forbids repulsive gravity at the structural level (a hard
   prediction, consistent with all observation).
2. **The medium state differs between like and unlike pairs.** Between two **like** charges the
   spation throughput is an **excess** (above ambient); between two **unlike** charges it is a
   **deficit** (below ambient). In principle this is a measurable difference in the vacuum/medium
   state (a Casimir-like or vacuum-energy asymmetry) in the gap of a like-pair vs an unlike-pair at
   equal separation — an SDT signature with no standard-model counterpart.
3. **Magnitude symmetry is structural,** not coincidental: any future SDT derivation of Coulomb
   *must* yield |repel| = |attract| automatically, because both are ± one modulation.

## 7. Stars overcome the inverse-convergence by crushing size **[STRONG framing; OPEN barrier]**

(Added at Harvey's prompt: *"the proton's repulsion and the electron's plasma stream — stars
overcome repulsion with their crushing size."*) This is the cleanest place to watch the convergence
fight its own inverse, because **fusion is exactly that fight.** (`fusion_convergence.js`.)

- **The enemy is the inverse-convergence.** Two protons repel by the dipole **excess** of §3 — the
  Coulomb barrier: 1.44 MeV at 1 fm, 0.72 MeV at 2 fm. That excess *is* the convergence run
  backwards between them.
- **Crushing size is accumulated occlusion, scaled up.** A star is ~10⁵⁷ nucleons' worth of
  symmetric throughpole-occlusion (gravity), and that crush sets the core's density and temperature — the
  *confinement*. **But it does not, by itself, bridge the barrier:** Sun-core kT ≈ 1.35 keV is
  ~1000× *below* the 1.44 MeV barrier. Crushing gets the protons dense and fast, not over the wall.
- **The electron plasma stream screens the excess.** Electrons carry the *opposite* directionality
  — a **deficit** — and pack into the gaps between protons (Debye length ≈ 35 pm in the core),
  partially **cancelling the inter-proton excess**. Screening trims the barrier (by percents), it
  does not erase it.
- **The close-approach win is occlusion saturation.** Once protons are crushed toward 1–2 fm, the
  occlusion fraction **saturates** (g: 1→2, the very effect that whips the sungrazer in CQ46), and
  at femtometre scale the occlusion force simply *is* the strong binding (~10³⁸× gravity; alpha-core
  binding ≈ 7.07 MeV/nucleon ≫ the ~1.4 MeV barrier). So at contact the **attractive** occlusion
  overtakes the **repulsive** dipole — the convergence beats its own inverse, and the protons fuse.

**The picture:** crushing (accumulated occlusion) + screening (electron deficit) push the protons
*toward* fm against the dipole excess; at fm, saturating occlusion (attraction → strong binding)
overtakes the excess and they fuse. **The convergence overpowers the inverse-convergence — but only
where size crushes hard enough to reach the saturation crossover.** That is why fusion needs a
*star*: nothing smaller accumulates enough occlusion to get there.

**The honest gap (the real open problem).** keV thermal vs MeV barrier = ~1000×. Standard physics
bridges it with **quantum tunnelling** (the Gamow factor). SDT has no wavefunction, so it owes its
**own** barrier-crossing. Candidates, all **[OPEN]**: (a) the occlusion-saturation crossover
reaching out to pull the last stretch once protons are close enough; (b) the **smaller spations in
the crushed core** (regime 2) changing the effective relay distance a proton must cross; (c) a
count-conserving relay bridging the gap. None is derived. "Crushing size overcomes repulsion" is
the right *confinement* statement and the *crossover* is real, but the SDT analogue of tunnelling —
the last factor of ~1000 — is unfinished, and is named here rather than waved away.

---

## 8. Honest ledger

**[STRONG] (grounded in the existing framework):**
- Attraction = defocused deficit, repulsion = focused surplus — one through-flow redirected with
  opposite handedness; magnitude symmetry forced and observed.
- Gravity attraction-only ⇔ the symmetric (ℓ=0) **subtractive occlusion** (can only shadow, never
  add); charge bipolar ⇔ the handed (ℓ=1) **redirection** (can focus or defocus). This *is* the wake
  structure, named in throughpole terms — no poles invoked.
- Explains the no-antigravity fact at the structural level (occlusion only subtracts) — a genuine
  win, since GR/Newton merely *assume* gravity is attractive.
- **The fork is resolved [§5]:** the surplus is **constructive redirection**, not a literal outflow
  — a literal point-outflow would be a **monopole, and there are none** (the convergence is a
  throughpole; emission is reserved for light). The emitter/absorber-vs-symmetric test
  (consequence 2) remains the empirical check.

**[OPEN] (the real work remaining):**
- The **quantitative** step: deriving that the handed (ℓ=1) surplus has the exact Coulomb magnitude
  (and the right sign per pairing) **from the vortex handedness** — the occluded-influx-directionality
  of the (1,1) electron / (2,3) proton knots. At present the Coulomb *magnitude* still enters through
  the P_eff coefficient, which is imported/flagged ([[CQ01]], [[CQ33]], P_eff provenance).
  **One derivation, two locks:** because P_eff is hydrogen-calibrated *to the Coulomb force*, this
  same handedness derivation would *earn* P_eff and close the **CQ01 class-E circularity** (f and
  P_eff/P_conv being one equation twice). One calculation discharges both CQ47's magnitude and CQ01's
  coefficient — the highest-value open step on the board.
- Connection to magnetism (ℓ = 2): if ℓ = 0 is the symmetric occlusion (gravity) and ℓ = 1 is the
  handed focus/defocus (charge), the ℓ = 2 quadrupole (vortex circulation) should be the *rotational*
  structure (magnetism) — a natural next rung, not addressed here.

**The headline that survives:** repulsion as the inverse of the convergence is not a bolt-on — it is
the **focused-redirection lobe** of the throughpole, the handed twin of the defocused deficit that is
attraction, and it explains in one stroke why gravity only attracts (occlusion subtracts only) while
charge does both (redirection focuses or defocuses). There are **no monopoles**: gravity, charge, and
light are all patterns of — or emissions from — the one throughpole. The quantitative Coulomb
magnitude from handedness, which also earns P_eff, is the open frontier.

---

*Grounding: `repulsion_inverse.js`. Builds on the wake structure (manuscript Part VIII; ℓ=0/1/2),
charge = occluded influx directionality ([[CQ37]]), the **convergence-as-throughpole** ontology
(no monopoles; light = emission), and the two-regime / occlusion thread. The occlusion **magnitude**
caveat — and its closure — is shared with [[CQ01]]/[[CQ33]].*
