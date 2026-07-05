# The Causal Chain of Reality
### What rests on what, in Spatial Displacement Theory

*A draft synthesis of the dependency and inheritance structure of the SDT engine and its investigations.*
**J. C. Harvey, Melbourne** · DRAFT

---

> Every number in physics is a promise that something earlier was settled first.
> This document traces those promises, in order, for SDT — from the one or two
> things the theory is honest enough to *assume*, up through everything it claims
> to *derive*. It is a map of debts: who owes their existence to whom.

---

## 0. A litre of water

Begin with something everybody trusts: the density of water, about one thousand
kilograms per cubic metre. It feels like a brute fact of the world. It is not. It
is the last link in a chain of decisions, and if you pull on it the whole chain
comes up out of the ground.

To say "kilograms per cubic metre" you must already own a **metre**. The metre was
not handed down; it was *chosen* — originally as one ten-millionth of the distance
from the equator to the North Pole, a line surveyed across France with telescopes
and trigonometry. So before density there was a planet, and a survey, and a
definition.

Then you need a **cubic metre**, which means you need to know that a box ten
centimetres on each side holds exactly one litre, and that one millilitre is one
cubic centimetre — `1 mL = (1 cm)³`, `1 L = (10 cm)³ = 1000 mL`. Volume is the
metre, cubed; it inherits everything the metre assumed and adds the idea of
stacking length in three directions.

Then you need the **kilogram**, and the old kilogram was *defined* as the mass of
one litre of water. But "water" is not enough — water at what temperature? (It is
densest near 4 °C.) So now you need a **temperature scale**, which was itself
pinned to water freezing and boiling, which only happen at fixed points if you
also fix the **pressure**, which means you need an atmosphere, a barometer, a
column of mercury whose own density you had to measure with… a kilogram and a
metre.

The chain bites its own tail. Density rests on mass, which rested on water, which
rested on temperature, which rested on pressure, which rested on density. None of
it is wrong — it is one of the most successful structures humans ever built — but
**not one quantity in it stands alone.** Each is a knot tied to the others, and a
few of the knots are frankly circular, broken only by *deciding* to hold one thing
fixed by hand (these days, a fixed value of the Planck constant) so the rest can
hang from it.

Spatial Displacement Theory is a physics with exactly this shape, and it is
unusually candid about it. This is the map of its knots.

---

## 1. The three pegs

SDT permits itself a short list of measured inputs — its whitelist — and forbids
everything else. The list is:

```
{ ℓ_P,  c,  ℏ,  k_B,  T_CMB,  α,  m_e,  m_p }
```

That is the *stated* rule. But the investigations, read together, tell a sharper
story than the list does. Most of those eight are not independent pegs at all:
`c` is a conversion factor between counting space and counting time; `ℏ`, `k_B`,
`h`, the elementary unit `e` are unit-bridges between SDT's natural bookkeeping
and the SI units a laboratory reports. When you strip away the unit-converters,
**three things remain that the theory genuinely cannot manufacture from anything
deeper.** They are its metre, its kilogram, and its degree:

1. **A length** — the size of a single grain of space, `ℓ_P` (the "spation," taken
   to be the Planck length). This is SDT's metre. Every distance in the theory is,
   underneath, a *count of grains*.

2. **A coupling** — the fine-structure constant `α` (equivalently, the elementary
   unit `e`). This sets how hard electromagnetism pulls, and through that, the
   size of atoms.

3. **A mass** — the electron mass `m_e` (and with it the proton mass `m_p`). This
   fixes how much "stuff" a given amount of displaced space amounts to.

The engine's own source code marks the first of these with unusual frankness. In
`laws.hpp`, beside the Planck length, a comment reads: *"the ONE irreducible
dimensional seed… NOT eliminable… exactly one action/mass/length anchor is
mathematically unavoidable."* That is not an apology. It is a **theorem**.

### Why exactly one anchor is unavoidable (FLM06)

The investigation **FLM06** set out to *derive* the grain size `ℓ_P` from nothing
but SDT's own cosmic quantities — the temperature of the sky, the size of the
visible universe, ratios that carry no smuggled-in metre. It failed, and the
failure is the most useful result in the whole framework. FLM06 proved that **no
combination of dimensionless cosmic ratios can ever build an absolute length.**
Temperature ratios give you numbers around a thousand; you need a number around
`10⁶¹`; the gap cannot be closed by any honest grouping of the permitted
quantities. Somewhere, exactly once, you must reach in from outside and *hand the
theory a single scale*. After that one gift, everything else can in principle be
counted in multiples of it — but the first ruler has to come from somewhere.

This is precisely the moment in the water story where someone fixes the Planck
constant by decree so the kilogram can hang from it. SDT's version is cleaner only
in that it *names* the moment and proves it is forced.

The same wall appears twice more, for the same reason:

- **The elementary unit `e` (EMC02).** The investigation tried to build the elementary unit `e`
  from the whitelist. It cannot be done: the permitted quantities contain no
  electric dimension, so no algebra yields an `[A·s]` quantity. The one route that *seems* to
  work, `e = √(αℏc/k_e)`, is a disguised tautology — because `α` is *defined* as
  `k_e e²/ℏc`, that equation just says `e = e`. Charge is a peg, not a derivation.

- **The mass scale (PPT07).** It is tempting to read the masses as pure geometry — the
  proton weighing 1836 electrons because of a knot. The honest position splits in two.
  The proton/electron *ratio* is genuinely strong: it matches `6π⁵` to 19 ppm, a form
  that is *unique* within 0.1% of 1836 and structurally homed (the `6` is the trefoil's
  `2×3` wrap; the `π⁵` factors into two n-sphere surface areas — see §6). But the
  *absolute* scale that ratio multiplies is not derivable: a ratio is secretly a ratio
  of two lengths, and FLM06 already forbids building an absolute length from cosmic
  arithmetic. So `m_e` is handed in once, for the same reason `ℓ_P` is. The ratio is a
  privileged target still missing its mechanism; the scale is a genuine peg.

So the three pegs are not a stylistic choice. They are three independent places
where the investigations went looking for a derivation and came back with a proof
that none exists. **Everything else in SDT is built on these three, plus the sky.**

---

## 2. From a grain to a universe

Hand the theory its grain `ℓ_P`, and the next layer follows almost for free.

**Time falls out of space and `c`.** A signal crosses one grain in one tick, and
the tick is just the grain divided by the speed of light: `t_P = ℓ_P / c`. In SDT
`c` is not a separate substance to be explained; it is the *exchange rate* between
counting grains and counting ticks. Fix the grain, accept the exchange rate, and
you have both a smallest length and a smallest time.

**Pressure falls out of the sky.** Every grain is "phase-loaded" — it holds a
little deformation content `ε`. How much? That is read off the one temperature SDT
treats as a genuine boundary condition: the cosmic microwave background, `T_CMB =
2.7255 K`. The held energy density of empty space is the blackbody value at that
temperature, and a single grain's share is that density times its tiny volume,
`ε = u_CMB · ℓ_P³`. Here `ℏ` and `k_B` do their job as unit-bridges, turning a
temperature into an energy.

**The lattice gets a size.** Count the grains from here to the edge of the visible
relay — the "Clearing," at distance `R_CMB` — and you get the number of shells,
`N = R_CMB / ℓ_P`, about `6 × 10⁶¹`. Multiply the per-grain content by the count
and you have the total throughput `Φ = Nε`, and dividing by a grain's volume gives
the **convergence pressure** `P_conv` — the steady inward weather that presses on
everything, the reservoir gravity and electromagnetism both draw from.

**But here is the first leak.** `R_CMB` is not derived; it is an *observed* scale,
and it carries the Hubble constant `H₀` inside it. The engine flags this honestly:
`R_CMB` "does not pass the delete-test — the Law I chain is conditioned on this
value." So the cosmological layer of SDT inherits a dependence on `H₀` that the
theory would like to remove and has not yet removed. We will meet this leak again
in §7.

**The budget falls out of motion.** The last piece of the ground floor is a
conservation rule SDT treats as bedrock: a thing's motion through space and its
internal circulation always add, in quadrature, to the speed of light —
`v² + v_circ² = c²`. At rest, all of `c` is spent on internal spin; at light speed,
all of it is spent on travel and none on spin (which is why light has no rest
mass). From this single budget the engine re-derives time dilation, length
contraction, `E = mc²`, and the whole of special relativity — not as postulates but
as bookkeeping. The investigation **FLM02** showed that one axiom — *every grain
gets one relay pulse per tick* — already yields `F = ma` and all three of Newton's
laws to one part in a million.

At the end of §2 we have, built from the three pegs plus the sky: a smallest length
and time, a universal pressure, a lattice with a definite size, and the rules of
motion. No forces yet. No atoms yet. Just the stage.

---

## 3. The bridge that erases G

Now SDT does the thing it is proudest of, and the thing the investigations support
most strongly: **it computes gravity without ever using Newton's `G` or a mass `M`.**

The trick is a single quantity the framework calls **koppa** (`ϟ`). For any body,
take how fast its surface moves and how big it is, and form

```
ϟ = v² R / c²      (equivalently  ϟ = R / k²,  where  k = c / v)
```

Koppa is a *length* — the body's gravitational "depth," the amount by which it
sinks the lattice around it. It is built from two things you can measure directly,
a speed and a size, and from `c`. It never asks what the body weighs, and it never
invokes a gravitational constant. The familiar product `GM` is recovered, after the
fact, as `GM = ϟc²` — so in SDT `GM` is an *output*, a convenient repackaging, not
an input.

From koppa comes the **depth** of any point near the body, `z = ϟ / r`, and from
depth comes essentially all of gravitation as a set of samplings of one function.
The investigation **GOM01** showed that this single `z(r)` reproduces gravitational
redshift, the Shapiro time delay, and the bending of starlight, all at once, with
no curved spacetime and no `G`. **GOM05** sharpened it: the depth is literally a
*slowing of local light and a tightening of the local grain*, `c_local = c(1 − z)`
— one quantity wearing three faces (depth, light-speed deficit, grain deficit).

The most striking single result lives in **GOM04**. Take Mercury's measured
perihelion drift — the famous 43 arc-seconds per century — feed it backwards
through koppa, and out comes the speed of light to within nine parts in a million.
A planet's orbit, read through SDT's bridge, *measures `c`*. That is the opposite of
the usual dependence, where you need `c` and `G` to predict the orbit; here the orbit
hands you `c`.

A word about what this does and doesn't prove — and here the framing matters,
because it is easy to undersell. Several gravitational results (Mercury's precession
as a forward prediction, the Lagrange points, the ocean tides) come out **identical**
to general relativity and Newton. That identity is sometimes read as a weakness. It
is not. Any two theories that both fit the same measurements *must* be algebraically
inter-translatable — this is the **equivalence effect**, and reproducing the textbook
number is the entry ticket every serious theory has to buy, not a prize SDT failed to
win. `GM` reappears here not because koppa is secretly `GM` in disguise — the
dependence runs the other way, as we just saw — but because `GM = ϟc²` is koppa's
*shadow* in the one special case where you insist on weighing the body. The
projection, not the parent.

So the honest comparison is never "does SDT get a *different* number here" — in a
correspondence case it had better not — but **how much machinery each theory spends
to get there.** General relativity reaches Mercury's 43 arc-seconds through the field
equations and a curved metric. SDT reaches the same arc-seconds — *and* the
gravitational redshift, *and* the Shapiro delay, *and* the bending of starlight —
through a single closure, `z·k² = 1`, and one length, koppa: one or two moves in
every case. Most striking of all, the *same* `z·k² = 1` that fixes a planet's orbit
is the relation that reads the hydrogen spectrum — where `α` is just the koppa-rung
of the ground state — so one move spans the solar system and the atom. The economy
*is* the result: not a better number on one observable, but the collapse of many
separate machineries into one.

Where SDT genuinely *parts company* — a different predicted number, not a
re-derivation of the same one — it does so in a few sharp, falsifiable places (the
altitude-dependent Cavendish force, the reflected-light redshift fork), collected as
experiments. The map marks both kinds clearly: the correspondence cases, where the
win is **parsimony**, and the departure cases, where the win would be **decisive**.

---

## 4. The one force and its price

SDT has only one force law. Coulomb's attraction, gravity, and the nuclear binding
are not three forces but three settings of the same machine:

```
F = (π/4) · P_eff · R₁² R₂² / r²
```

In words: two bodies *shadow* each other from the universal inward pressure (this
shadowing is "occlusion"), and the unblocked pressure on their far sides pushes them
together. The `R₁²R₂²/r²` part is pure geometry — the cross-sections of two spheres
and an inverse-square falloff — and the investigations grant it cleanly: that
*shape* is **derived**. The whole question of strength lives in the one coefficient
`P_eff`, the "effective pressure."

And `P_eff` is where the chain first ties a knot it cannot easily cut.

In the first accounting (**EMC01**), `P_eff` was fixed by *requiring* the force law
to reproduce the known electric force in hydrogen. That is calibration, and the
engine says so in as many words — the "fundamental" expression for the coefficient
and the calibrated one "are the same equation written twice." A force law whose one
free number was set by the answer it is meant to predict has not yet earned that
number.

The rescue came from an unexpected direction (**EMC04**, the "electropause"). Ask a
different question: what inward push is needed to hold an electron on its orbit in
hydrogen at all? That is a pure problem in circular motion — a mass, a speed, a
radius — with *no electromagnetic input*: `F = m_e (αc)² / a₀`. Compute it, and it
equals the electric binding force to ten significant figures. Then run the occlusion
law *backwards* from that force and out drops `P_eff`, matching the engine's value,
with the unit `e` and the Coulomb constant `k_e` nowhere in the derivation. This
"delete-test" — remove `e`, see if the answer survives — passes. On the strength
of it, `P_eff` is promoted from *calibrated* to *derived*, and the EMC01 circle is,
on the framework's own terms, closed.

But read the fine print, because the investigation does. The electron's orbit
radius is `a₀ = ℏ / (m_e c α)` — it contains `α`. So the whole rescue works **only
if you are allowed to treat `α` as a kinematic fact (a ratio of speeds) rather than
as the strength of electromagnetism.** A skeptic who insists `α ≡ k_e e²/ℏc` will
say `e` was smuggled back in through the radius. EMC04 did not *destroy* the
circularity; it **moved** it — out of the force coefficient and into `α` itself.
Which brings us to the centre of the whole structure.

---

## 5. The knot you cannot cut

Three quantities in SDT define each other in a ring:

- the coupling **`α`** is defined as `k_e e² / ℏc` — it *is* `e`, squared, in
  disguise;
- the **classical electron radius `r_e`** is defined as `α` times the electron's
  Compton wavelength;
- and every attempt to pin one of them down reaches for the other two.

The investigations hit this ring from three sides — trying to derive `α` from knot
geometry (**PPT02**), trying to derive `e` from the lattice (**EMC02**), trying to
free `P_eff` from `e` (**EMC04**) — and every time the conclusion is the same:
*one* member of the ring must be supplied by hand; the other two then follow. PPT02
put it most plainly: "every attempt to extract `α` reduces to `α = α`."

So SDT makes a philosophical move that is also a bookkeeping move. It declares that
**what convention names *charge* is no substance at all** — only a pattern of motion. What we call positive and
negative are the two *handednesses* with which the one inward through-flow can be
redirected (**EMC03**): a focused surplus pushes out (repulsion), a defocused deficit
pulls in (attraction), and because gravity can only ever *subtract* (it only makes
shadows, never surpluses) it is attraction-only, while the redirection, being handed,
comes in both signs. The elementary unit `e`, in this view, is not a quantity of
stuff but a **unit-conversion factor** — the exchange rate between SDT's natural
description and the Ampère-seconds a laboratory measures, exactly as `ℏ` and `k_B`
are exchange rates for action and temperature.

This is the heart of the dependency map. **The coupling peg of §1 is irreducible not
because SDT is lazy but because the investigations proved the ring `α ↔ e ↔ r_e`
has no entrance.** You hold one of them fixed — SDT chooses `α`, read as a pure
ratio of speeds, the "koppa rung" of hydrogen — and the atom follows.

---

## 6. The weight, the ratio, and what each one costs

The third peg is the mass, and it deserves care, because two very different claims
usually travel together under one heading.

The first is the **absolute scale** — what one electron actually weighs. This is
irreducible, for a familiar reason: FLM06's theorem (§1) forbids conjuring an absolute
mass from dimensionless arithmetic, exactly as it forbids conjuring an absolute length.
A *ratio* can still secretly be a *scale* — the proton/electron ratio is, underneath,
the ratio of two Compton wavelengths, two lengths — so reaching in once to fix `m_e` is
unavoidable. On the scale, the peg stands.

The second is the **ratio** itself, 1836, and here SDT's instinct that *everything is
geometry* is on far firmer ground than a first reading suggests. The proton is the
`(2,3)` trefoil; the electron the `(1,1)` unknot; and the measured ratio sits at `6π⁵`
to **19 parts per million**. The reflex is to call that a coincidence — but it has been
checked, and it survives the check. A look-elsewhere search over every simple form
`a·π^b` (`a ≤ 30`, `b ≤ 6`) finds **exactly one** within 0.1% of 1836: `6π⁵`. Within a
hundred parts per million it is alone — not one lucky draw among many. And both of its
factors have a home: the `6` is the trefoil's total wrap, `2×3` (the electron's is
`1×1`), and the `π⁵` is not loose decoration — it factors exactly into a product of two
real n-sphere surface areas, `6π⁵ = 3·A(S³)·A(S⁵) = 3·(2π²)·(π³)`, the surface volumes
of the 3- and 5-spheres.

So what, precisely, did the blind ROOT-SIM audit kill? The *crude* route — the hope
that 1836 would drop straight out of a naive invariant like winding-squared (which is 9)
or a ropelength ratio (about 2.6). Those land between 1 and 50, two orders short, and no
dressing rescues them; that was worth killing, and the "fittable to any target" caution
belongs to *them*. But the audit did **not** touch — could not touch — the
phase-space-volume route that the `3·A(S³)·A(S⁵)` decomposition points at. That is where
the genuine open question lives, and it is a question of *mechanism*, not of legitimacy:
**why should the proton's wake integrate to that particular product of sphere-surfaces?**
Until that is derived, `6π⁵` is exactly what it honestly is — a uniquely privileged,
structurally-homed target whose generating mechanism is still unbuilt. The *number* is
far better than a coincidence; the *derivation* is what remains owed.

---

## 7. The inheritance

With the three pegs set and the lattice, the bridge, and the one force in place,
the rest of physics in SDT is *inheritance* — each domain spends the capital of the
ones beneath it and, in the honest cases, adds no new pegs of its own.

**Atoms (APS).** The full emission spectrum of hydrogen and beyond comes from the
electron's rotation field and the movement budget — the Rydberg constant emerges
geometrically, with no fitted parameters, and the engine reproduces the spectral
lines of 118 elements. ~~The fine structure and the Lamb shift come from the
*shape of the proton's wake* — its trefoil three-fold symmetry — rather than from
quantum-field corrections, and the Lamb shift lands within 0.6% with nothing tuned
(**APS04**).~~ **[CORRECTION 2026-07-03: the APS04 Lamb claim was FABRICATED and is
retracted (HUNTER scour; the 1051.8 literal was deleted from canon 2026-07-03). The
Lamb amplitude is OPEN — the well-posed native target is
`Investigations/02_…/PPT08_Angular_DOF_from_Trefoil/PPT08_KOPPA_TARGET.md`
(a spacing, not a shift: 1057.8 MHz ≡ 0.703 m/s ≡ 0.272 fm at n=2).]**
Atoms inherit `α`, the budget, and the knot; they invent nothing.

**Nuclei (NP).** Every nucleus is built from one rule — one alpha core plus so many
deuterons and tritons, with the counts fixed by simple arithmetic in the proton and
neutron numbers. This "grammar" is SDT's nuclear constitution, and the engine
verifies that all 287 stable isotopes obey it exactly. But the grammar is itself a
*posited* rule, a fourth thing taken on faith rather than derived from the three
pegs — and the binding *energies* it should predict are still owed: the simplest
hypothesis (binding equals a universal price times a volume) was tested and
**cleanly killed** (**NP05**), and its successor is not yet built. The nuclear domain,
honestly assessed, has strong conservation ledgers and one good falsification, and an
unpaid bill for the energy scale.

**Fluids, heat, materials, optics, chemistry (FD–CH).** These are the leaves of the
tree, and they are almost pure inheritance — across more than sixty investigations in
these domains, *not one new primitive or free parameter is introduced.* The one
genuinely new sub-result hides in fluid dynamics: a native speed limit for sound,
`c_s ≤ c/√3`, falling straight out of the lattice's one-third traction rule
(**FD05**), which downstream domains then reuse for phonons and shock waves. Optics
becomes a single statement — the refractive index is `n = 1/(1 − z)`, so a lens and a
gravitational well are the same phenomenon at different depths. Chemistry becomes the
sharing and trading of "electropauses," the pressure-balance shells of §4. None of it
reaches back to the pegs for anything new.

**Cosmology (CR), and the leak.** Here the chain is most ambitious and most exposed.
SDT reproduces a great deal of modern cosmology *without expansion and without dark
energy*: redshift becomes a ladder of octaves rather than a stretching of space
(**CR07**); the famous `(1+z)⁴` scaling that is usually taken as proof of expansion is
shown to arise identically in a *static* lattice, so that evidence is **degenerate**
(**CR10**); and a one-parameter "aging-glass" distance law fits sixteen hundred real
supernovae with no dark energy at all (**CR12**). But two debts remain unpaid, and the
investigations name them: the chain from the force coefficient up to the size of the
universe still **re-imports `G` through the grain size `ℓ_P`** (Axiom R1, never
derived), and it still leans on the **Hubble constant `H₀`** as an input — `R_CMB`
carries it, and the acceleration floor that fixes galaxy rotation, `a₀ = cH₀/2π`,
is *built from* it. The honest verdict on the cosmology is therefore: a remarkable
amount reproduced, `H₀` matched to a percent — but matched, not yet derived from
scratch. The zero-parameter cosmology is a goal the engine is close to and has not
reached.

**Galaxies (GD), and an honest failure.** Worth recording because the framework
records it: the original galaxy-rotation law, applied to 135 real galaxies, **failed**
— it under-predicts the speeds two- to three-fold (**GD05**). A second formulation, a
convergence "floor," succeeds at the 24% level and recovers the Tully–Fisher relation
— but only by *borrowing* the crossover shape from MOND; the deep limit is SDT's own,
the bridging curve is not yet. This is logged as an open debt, not painted over.

---

## 8. The honest loops

If you draw the whole dependency graph and look for cycles — places where A needs B
needs C needs A — you find a small, well-mapped set of them. They are not bugs hidden
in the theory; they are *flagged in the engine's own comments*, and the framework's
"audit spine" exists precisely to track them. There are four:

1. **`ℓ_P` defines `ℓ_P`.** The prettiest internal route to the grain size,
   `ℓ_P = √(ϟ · ƛ)`, turns out to use a koppa that is itself *defined* using `ℓ_P` —
   so it reduces to `ℓ_P = ℓ_P`. A consistency check, not a derivation. (FLM06 proves
   this is unavoidable: see §1.)

2. **`α ↔ e ↔ r_e`.** The coupling ring of §5. No member is the entrance; one is held
   by hand.

3. **`P_eff` and the force it predicts.** Closed by the electropause argument
   (EMC04) — but only by relocating the dependence onto `α` (§4). The loop is smaller
   now, not gone.

4. **`R_CMB ↔ H₀`.** The size of the universe and the expansion rate define each other
   through the cosmology; the chain currently takes `H₀` as given (§7).

The reason to be loud about these rather than quiet is the same reason the litre of
water in §0 is not a scandal: **a circular definition is only a fraud if you hide
it.** SI does not hide its fixed constants; it announces them. SDT's audit spine does
the same thing — every result carries two labels, one for *where its derivation
started* (did it begin from the pegs, or lean on an outside number?) and one for
*what it matches* (a measured value, a textbook law, or nothing yet). The goal of the
spine is to make the honest graph **acyclic** — to push every loop down onto the
three pegs and the sky, and declare those, and only those, as the things held fixed
by hand.

---

## 9. The shape of the dependence

Strip the framework to its skeleton and this is what holds it up:

```
        HELD FIXED BY HAND (the pegs)
        ┌─────────────┬───────────────┬──────────────┐
        │  a length   │  a coupling   │   a mass     │   + the sky
        │    ℓ_P       │   α  (≡ e)     │    m_e        │    (T_CMB, R_CMB→H₀)
        └─────┬───────┴───────┬───────┴──────┬───────┘
              │               │              │
   time = ℓ_P/c         the atom's        "stuff" per
   pressure = f(sky)    size & coupling   displaced grain
              │               │              │
        ┌─────┴───────────────┴──────────────┴─────┐
        │   the lattice: N, P_conv, the budget      │   (Laws I, V)
        └──────────────────────┬────────────────────┘
                               │
                 ┌─────────────┴─────────────┐
                 │   koppa  ϟ = v²R/c²        │   gravity with no G, no M
                 │   depth  z = ϟ/r           │   (Laws II, III)
                 └─────────────┬─────────────┘
                               │
                 ┌─────────────┴─────────────┐
                 │  one force: occlusion      │   Coulomb = gravity = nuclear
                 │  F = (π/4)P_eff R²R²/r²     │   (Law III, P_eff via EMC04)
                 └─────────────┬─────────────┘
                               │
   ┌───────────┬───────────┬───┴────┬───────────┬───────────┐
  atoms      nuclei      fluids   cosmology   optics     chemistry
 (inherit)  (+grammar)  (+c/√3)  (leaks H₀)  (n=1/(1−z)) (electropause)
```

Everything below the second row is *earned where it is geometry* — the movement
budget, the koppa bridge, the inverse-square shape of the force, the speed of light
read out of Mercury's orbit, the sound limit `c/√3`, the nuclear grammar's
arithmetic, the Rydberg constant ~~, the Lamb shift to a fraction of a percent~~
**[CORRECTION 2026-07-03: the Lamb entry is struck — APS04 was fabricated and
retracted; the Lamb amplitude is OPEN (see PPT08_KOPPA_TARGET.md)]**. These
are the framework's real assets, and they are substantial.

Everything that is still *owed* sits in a few sharp places, and they are exactly the
ones the investigations refused to fudge: the **magnitudes** as opposed to the shapes
(the force coefficient `P_eff`, resting on `α`; the nuclear binding scale, still
unbuilt); the **two-volume** question of how many grains a proton really is; and the
**cosmological leak** of `G` through `ℓ_P` and of `H₀` through `R_CMB`. The audit spine
is the ledger that keeps these debts visible.

So the answer to "what is SDT's reality made of, and in what order?" is this. It is
made of **a single grain of space**, **a single strength for electromagnetism**, and
**a single unit of mass** — three things it proves it cannot derive and therefore
holds fixed by hand, exactly as the metre and the kilogram were once held fixed by a
meridian and a litre of water. To those three it adds **one boundary condition from
the sky**, the temperature and reach of the cosmic background. From that short list,
and from a handful of geometric rules about pressure, shadow, and motion, it builds —
honestly where it can, with the loans clearly marked where it cannot — time, gravity,
the atom, the nucleus, the flow of fluids, the bending of light, and the chemistry of
matter.

Not one quantity in it stands alone. That is not the theory's weakness. As the litre
of water taught us, it is what a physics *is*.

---

### Appendix A — the irreducible inputs, and what they cost

| Peg | Symbol | Plain meaning | Why it can't be derived | Flagged in |
|---|---|---|---|---|
| The metre | `ℓ_P` | size of one grain of space | no dimensionless cosmic ratio reaches `10⁶¹` | FLM06 (theorem) |
| The coupling | `α` (`≡ e`) | strength of electromagnetism / the atom's scale | the `α↔e↔r_e` ring has no entrance | EMC02, PPT02, EMC04 |
| The mass | `m_e`, `m_p` | how much "stuff" a displaced grain is | a mass *ratio* still hides a *scale* | PPT07 (ROOT-SIM) |
| The sky | `T_CMB` | held energy density of empty space | a measured boundary condition | Law I |
| (leak) | `R_CMB`→`H₀` | size of the visible lattice | carries the Hubble constant | CR03–CR05, `laws.hpp` |

The remaining whitelist members — `c`, `ℏ`, `k_B`, `h`, `e` — are best read not as
extra pegs but as **unit-converters** between SDT's natural counting and SI: `c`
between space and time, `ℏ`/`h` for action, `k_B` for temperature, `e` for the electromagnetic unit.

### Appendix B — earned vs. owed, at a glance

**Earned (geometry, derived):** the movement budget and all of special relativity
(FLM02); the koppa bridge and gravity with no `G`/`M` (GOM01, GOM02); `c` from
Mercury's orbit (GOM04); depth-closure unifying redshift/Shapiro/bending (GOM01,
GOM05); the inverse-square *shape* of the one force (EMC01); `P_eff` via the
electropause (EMC04, conditional on `α`); the sound limit `c/√3` (FD05); the nuclear
grammar's arithmetic for all stable isotopes (NP01); the Rydberg constant and spectra
(APS01); ~~the Lamb shift to 0.6% (APS04)~~ **[struck 2026-07-03 — APS04 fabricated,
retracted; Lamb OPEN, target = PPT08_KOPPA_TARGET.md]**; neutrino magnetic moment
exactly zero (PPT04); ~~knot stability selecting the particle spectrum (PPT09)~~
**[struck 2026-07-03 — the PPT09 Class-A closure was fabricated and is retracted
(HUNTER scour); the W∈{1,3}-only conjecture itself remains a legitimate OPEN
target]**.

**Owed (magnitudes, seeds, leaks):** the three pegs themselves (FLM06, EMC02, PPT07);
the nuclear binding-energy scale (NP05 killed the first attempt; successor unbuilt);
the proton's true grain-count (the "two-volume" ambiguity); the galaxy-rotation
crossover shape, currently borrowed from MOND (GD05); and the cosmological re-import
of `G` via `ℓ_P` and of `H₀` via `R_CMB` (CR03–CR05).

---

*Draft. Built from the SDT engine (`Engine/include/sdt/laws.hpp`) and a full pass
over the investigation record (domains 01–16). Every claim of "earned" or "owed"
above is traceable to a named investigation's own verdict; where an investigation
killed a hypothesis or flagged a circularity, this document inherits that verdict
rather than softening it.*
