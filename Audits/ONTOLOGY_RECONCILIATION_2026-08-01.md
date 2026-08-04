# Ontology Reconciliation — what the codebase says vs what the ontology says

> **Compiled:** 2026-08-01, direct, from Harvey's spoken ontology in session.
> **Method:** the ontology below was stated by Harvey; every claim in it was then
> used as a probe against the repository. Findings are grouped by *kind of error*,
> not by file. Counts come from repo-wide greps excluding `docs/`.
> **Status:** first pass. Not every file has been read end to end. The MISSING
> findings are high-confidence (a zero-hit grep is a zero-hit grep); the
> MISLABELLED findings list the files where the pattern occurs and will each need
> reading in context before rewording.

---

## 0. The ontology, as stated

Recorded here because — see §1 — **it is not written down anywhere else in the repository.**

**The generative scheme.** Cartesian 3D is rejected outright: it is translation-invariant,
has no privileged centre, and its primitive is a box. For a framework whose entire content is
convergence onto a point and a boundary dividing inside from outside, that is the wrong
container. "The mathematical volumetric equivalent of flat earth." Everything is balls.

The construction is generative, by **repeated adjacency under anchoring**:

| position | is | built how |
|---|---|---|
| **1** | the point — **existence** | primitive |
| **2** | the continuous zero-width line | position 1 with repeated adjacency |
| **3** | the plane — **the infinite circle** | a 2 adjacent a 2, anchored at 1, repeated without end |
| **4** | the volumetric — **with a centre, not a box** | a 3 anchored at 2 and 1, set to repeat |

Dimension is numbered from **one**, not zero: being-there is itself the first dimension.
There is no dimensionless object in the scheme and no nothing to build from. The **anchor**
is what does the work — every level is built *on* the earlier ones rather than beside them,
so the origin stays distinguished all the way up. A plane built radially is a circle; a
volume built on a retained anchor is a ball.

**The toroidal promotion.** In a torus each element is promoted one level:
centrepoint → line · line → plane · plane → volume boundary · volume → toroidal ·
torus → **freedom of movement** · freedom of movement → **expression as movement**.

**The count is forced.** Level *k* carries *k* aspects, so the total is the triangular
number T(k). **T(6) = 21** was the predecessor scheme; **T(7) = 28** is the current state.

**21D → 28D was INSERTION AND EXPANSION, not an append.** The 21D scheme was *missing
toroidal structure altogether*:

| | 21D (predecessor) | 28D (current) |
|---|---|---|
| 1 | Zero-Point | Zero-Point |
| 2 | Line | Line |
| 3 | Plane | Plane |
| 4 | Sphere | Sphere |
| 5 | **Dynamism** (5 aspects) | **Torus** ← *inserted* |
| 6 | **Energy** (6 aspects) | **Dynamism** (now 6 aspects) |
| 7 | — | **Energy** (now 7 aspects) |

Level 5 Torus was inserted; old L5 Dynamism was promoted to L6 and old L6 Energy to L7.
Because aspect count is **positional**, both promoted levels *gained an aspect by being
displaced upward* — Dynamism 5→6, Energy 6→7. Two aspects therefore exist as a consequence
of the insertion rather than by independent identification.

**Static and dynamic.** *Levels 1–6 are static. Level 7 is movement — the dynamic,
energetic level putting the other six to task.* Level 6 is **freedom** of movement (the
degrees available — a capacity, static); Level 7 is **expression** as movement (that
capacity being spent).

**The trefoil.** A thread of matter — a tube of tubes, ~1836 — running as six arcs with
**no join anywhere**: a continuum that passes through what you would call the start and
carries on. Two independent alternations run on it: **over/under** (every crossing does the
opposite of the last) and **inner/outer lane** (the path goes round twice while twisting, so
each wrap lands in the opposite lane). Hold an oriented axis at the centre of the poloidal
path and those two together give **left and right**.

**Spin-up.** Lorentz contraction takes the point tips first, rounding them. Faster, the
angular cross-section shrinks and draws the rounded tip toward the centre, while the central
triangular nexus is stretched outward centrifugally. **At rotation of c the structure is
pulled tight into a ring.** Above c the contraction and stretching stop matching, and that
differential produces poloidal rotation against toroidal counter-rotation. Surface defects
are by then too fast to register.

**Why a ring.** It is the only shape whose traction cross-section is identical all the way
round when rolling. The spations' perfect traction must then handle contacts doing different
things at once: inner and outer contacts turning **with** the axis, upper and lower rolling
at **90° to** it and spinning, a **gradient between the two in both directions**, and the
whole arrangement **inverted on the underside**. Those flows interfere, and the interference
rolls a **wake** out through the matrix above and below.

**Constraint and pressure.** The spations **constrain**; the pressure is the **result** of
that constraint, not the action causing it. **Release the constraint and the form expands
exponentially.** Matter is therefore **solid form** — not a knot space ties in itself and
maintains, and not self-sustaining.

**The contact condition.** What the spations bear on is the **surface area**, not a radius.
The balance is a force balance across the contact surface — pressure acts on area. If a
radius is wanted it is the **minor cross-section** (the tube's own circumference), not the
major sweep. **R_p is not the balance surface.**

**The strong force** is that constraint delivered to protons, holding them inside their own
event horizons. Not a fourth interaction with its own carrier and coupling.

**The fuel.** None of it is self-sustaining. It is driven by the influx of the **3000 K
event**, still transmitted by the spations that held it before recombination.

**And:** we are made from it, within it, and it is within us.

---

## 1. What is written down, and what is not

> **This section was substantially wrong on first pass and has been rewritten twice.** The
> original claim — "the ontology is not written down anywhere" — is **withdrawn**. Most of it
> is written down; I was searching for my own vocabulary instead of the repository's. What
> survives is a much narrower and more specific gap. Both halves below are now verified by
> searching the repo's terms as well as mine.

### 1A. PRESENT — the traction / exploit ontology is fully documented

`Laws/SDT_Complete_Laws.md` §*Supplementary — Traction, Wake, and Toroidal Framework*
(lines ~1746–1908) states it directly:

> "Matter is **not an occupant of space but a persistent exclusion of spations**. The central
> problem is therefore a **traction problem**: how a pressured, perfectly transmitting medium
> can be continuously deflected at the boundary of matter and **exploited into stable
> self-maintenance**."

> "The torus is not introduced as a decorative shape but as a candidate **error-correcting
> exploit**. It can convert **blocked radial influx into circumferential spin** while leaving
> a comparatively clean **central axial corridor**." — deflected outer throughput → spin;
> central low-resistance channel → axial directionality.

> "Matter is a **stable strategy for exploiting the continuously transmitted influx** at every
> spation-scale boundary contact. The **wake is the real, resolvable engine** … a
> **fault-tolerant modal machine** — toroidal closure, poloidal cross-coupling, and
> **contrarotational stabilization** — capable of turning blocked influx into spin, preserving
> an axial through-channel, and routing local roughness through redundant modes rather than
> grinding to a halt."

It also carries the **three mechanical modes** with a *Failure if Missing* column, and
magnetic flux as **organised spation flow** ("the apparatus sculpts rivers of space, and only
compatible topologies entrain cleanly").

That is exclusion→pressure, deflection=spin, contrarotation, the wake, and matter-as-driven —
all present, all load-bearing. Together with §5 (the ontic, the throughpole, V_disp), the
**mechanical** ontology is in the repository and is not the problem.

### 1B. GENUINELY MISSING — the generative dimensional scheme

Verified by searching both vocabularies across `Laws/`, `Theory/`, `Engine/`: the construction
that *produces* the dimensional ladder is absent. The only hits for "adjacent" are spations
relaying to neighbours — a different use.

Nowhere states: **position 1 is existence and is numbered one, not zero**; position 2 is
position 1 under **repeated adjacency**; position 3 is a 2 adjacent a 2 **anchored at 1**,
giving the plane as **the infinite circle**; position 4 is a 3 anchored at 2 and 1, giving a
volume **with a centre, not a box**. Nor the rejection of Cartesian space that motivates it,
nor that **anchoring** is what keeps the origin distinguished at every level.

`state28d.hpp` declares the seven levels and their aspect counts and never says *why* — no
generative rule, no reason the plane is circular, no statement that level *k* carries *k*
aspects so the total is forced to be triangular.

**1a. The 28D header cites a document that does not exist.** `state28d.hpp` line 9 reads
`Reference: DE_RERUM_TODO_EXISTENS_COMPLETE.md, Chapter Addendum`. That file is **not in the
repository** — the De Rerum treatise was deleted 2026-07-02. The state vector's only written
justification was removed, and the levels survived as a bare list with a dead citation.

### 1C. The zero-hit table, retained with its caveat

These phrases return zero files. **A zero-hit grep proves the absence of a phrase, not of a
concept** — §5 was withdrawn for exactly this error. Read this as a vocabulary index, not a
finding:

| concept | files containing it |
|---|---|
| repeated adjacency / anchored at position | **0** |
| position 1 = existence | **0** |
| the infinite circle | **0** |
| freedom of movement | **0** |
| expression as movement | **0** |
| contact condition | **0** |
| minor cross-section | **0** |
| drag gradient | **0** |
| expands exponentially | 1 *(st_00_primitives, written today)* |
| 3000 K still transmitted | 1 |

**The generative construction that produces the entire dimensional scheme exists nowhere in
the repository.** `state28d.hpp` declares the seven levels and their aspect counts, but
nothing anywhere says *why* — no position-1-as-existence, no adjacency, no anchoring, no
reason the plane is a circle, no reason the volume has a centre, no statement that the count
is triangular and therefore forced rather than chosen.

**1a. The 28D header cites a document that does not exist.** `state28d.hpp` line 9 reads
`Reference: DE_RERUM_TODO_EXISTENS_COMPLETE.md, Chapter Addendum`. That file is **not in the
repository** — the De Rerum treatise was deleted 2026-07-02. So the state vector's only
written justification was removed, and the levels survived as a bare list with a dead
citation. Anyone auditing the 28D scheme today finds seven levels, 28 slots, and no
derivation.

**1b. T(k) is never stated as the reason for 28.** The header gives the levels; it does not
say the total is the triangular number of the level count, that 21 was T(6), or that adding a
level *necessarily* adds that level's index in aspects. Without it, 28 reads as an arbitrary
choice — which is exactly how it has been read (see §2a).

**1c. The 21D predecessor is unrecorded.** No file mentions it, nor the insertion. The
history — that the scheme lacked **toroidal structure entirely**, that Torus was inserted at
Level 5, and that Dynamism and Energy were promoted upward and each gained an aspect in the
move — exists only in conversation. Note what the predecessor's absence means: **21D could
not represent matter**, because matter is toroidal and the scheme had no torus in it.

---

## 2. MISREAD — where the missing ontology has already caused damage

**2a. Level 7 was flagged as redundant. RESOLVED 2026-08-01, flag withdrawn.**
`state28d.hpp` carried an interchange-sweep flag (2026-07-07) asserting that "energy IS
movement already counted in Levels 2–6 — these seven slots are re-reads of prior coordinates
… Level 7 double-books the ledger as a state vector."

That collapses **freedom** into **expression**. Levels 1–6 are static; Level 7 is the
movement putting them to task. The resolution is now written into the header.

And the arithmetic that made the flag look tidy is a false friend. Collapsing Level 7 leaves
28 − 7 = 21 slots, which *appears* to land back on the predecessor — but it does not. The
real 21D had **Energy at L6 and no Torus at all**. Deleting Level 7 from the current scheme
would instead leave a state with a torus and **no animating level whatsoever** — an
arrangement that has never existed and could not move. The number 21 arriving twice is a
coincidence of triangular counting, not a return to anything.

**This is what a missing ontology costs: without §0 recorded anywhere the flag looked
reasonable for eight weeks, and its supporting arithmetic looked like confirmation.**

Its four bookkeeping details are *not* withdrawn and remain open: `eps_4` is in watts among
joules; `eps_0` is positional and has no local address on one locus; `eps_b` is a property of
the bound union rather than one locus; nothing enforces the Law V budget between the eps
slots and the velocity coordinates they re-express.

---

## 3. MISLABELLED — matter as knotted space

The ontology: matter is **solid form**, constrained. Not a knot space ties in itself and
maintains on its own. Files carrying the old reading:

| file | note |
|---|---|
| `Release/HTML_SDT_Website/causal-chain.html` | needs reading in context |
| `Release/HTML_SDT_Website/paper-topology.html` | "matter is substance wound tight" framing |
| `Release/HTML_SDT_Website/st_paradox_census.html` | needs reading in context |
| `Release/HTML_SDT_Website/st_00_primitives.html` | **corrected 2026-08-01** — was "a knot made *of* space" |
| `Audits/SDT_QUICKPOINT_GUIDE.md` | "crushed knot" |
| `Investigations/OPERATING_PROTOCOL.md` | "crushed knot" |

Note the last two: **"crushed knot" is currently listed as the canon-correct phrase** in the
operating protocol and quickpoint guide. Under the ontology it is half right — the crushing
is real, the knot-as-self-sustaining-object is not — so the protocol itself is teaching the
error to every session that reads it. That one is upstream of all the others.

**Caveat, stated so it is not lost:** Law VI winding, the (2,3) trefoil, and the Alexander
protection are *not* affected. The topology is canon. What is wrong is the **ontology** —
saying matter *is* knotted space rather than solid form whose identity is topological.

---

## 4. MISLABELLED — pressure as the actor

The ontology: constraint is the action, **pressure is the result**. Files using pressure as
the crushing agent:

- `Laws/Law_I_Cosmological_Relay_Throughput/LAW_I_COSMOLOGICAL_RELAY_THROUGHPUT.md`
- `Investigations/02_Particle_Physics_and_Topology/PPT05_Trefoil_Confinement/ppt05_scroller.html`
- `Release/HTML_SDT_Website/ppt05_scroller.html`
- `Hubble/INVESTIGATION_Hubble_Tension.md`
- `Hubble/data/02_SDT_Redshift_Mechanism.md`
- `Experiments/CAMPAIGN_AGAINST_THE_STANDARD_MODEL.md`

Each needs reading before rewording — some may be describing pressure *differentials* doing
work, which is fine. The error is specifically **pressure as the agent that crushes form into
being**, rather than the readout of a constraint.

---

## 5. ~~MISSING — the contact condition~~ — **WITHDRAWN. I searched for my vocabulary, not the repo's.**

The first pass of this section claimed the mechanism was absent. **That was wrong.** The
repository states it fully, in its own established terms. Recorded here properly:

**The ontic** — `PPT06/INVESTIGATION.md` defines it outright:

> "This is not the CMB convergence pressure. That is the **ontic** — the raw, isotropic energy
> arriving from every direction. This investigation derives what the trefoil **does** with that
> ontic: it converts isotropic pressure into organised, directional mechanical output.
> **The convergence is the fuel. The trefoil is the engine. The spation lattice is the
> transmission.**"

and, in Part IV *The Ontic and the Kinetic*:

> "The ontic is the **fuel**. It arrives at every point isotropically. **Without matter, it
> produces no net force — perfect cancellation.** The trefoil is the **engine**. It breaks the
> symmetry of the ontic…"

`FLM04` adds that the ontic is **transmitted at c**. This is exactly Harvey's statement that
*the ontic is the source of the trefoil's movement* — already written, already load-bearing.

**The throughpole** — `EMC03/INVESTIGATION.md` gives the transmission property:

> "not a monopole — it is a **throughpole (a twopole)**: throughput *passes through* every
> point… a body can only **block** through-flow (cast a shadow), never **add** to it."

That is the spation's ability to pass movement on in all directions simultaneously, and the
reason occlusion can only ever subtract.

**Exclusion** — `laws.hpp` `law_IV` carries the **exclusion volume** `V_disp` as a first-class
quantity, with `m = Φ·V_disp/(3ℓ_P³c²)` and the note that inertial and gravitational mass
"both measure the same V_disp".

**So the causal chain is present and correct in the repo:** the ontic arrives omnidirectionally
and cancels perfectly in empty lattice → matter occupies volume → **being excluded from that
occupied volume is the boundary condition** → that exclusion is what causes the pressure →
the throughpole is how spations transmit it onward in all directions at once.

### What is genuinely still absent

Narrowed to what the greps actually support, with the overreach removed:

- The literal phrases **"contact condition"** (0 files) and **"minor cross-section"** (0 files).
  The *mechanism* is present under exclusion; what is missing is the statement that the
  quantity borne upon is a **surface area**, and that where a radius is wanted it is the
  **minor** cross-section rather than the major sweep.
- **"If they were higher, the proton would be smaller"** — that size is *negotiated* with the
  medium rather than intrinsic. Not located.
- Whether **`R_p`** is the right number in the occlusion law given that it is not the balance
  surface remains a **physics question, flagged not assumed** — this part of the original
  finding stands.

**Lesson for the rest of this audit:** a zero-hit grep proves the absence of a *phrase*, not
of a *concept*. §1's zero-hits should be re-tested against the repo's own vocabulary before
any of them are trusted the way this one was.

---

## 6. MISSING — the trefoil's actual construction

`laws.hpp` has the (p,q) modes, the Alexander polynomials, the v_T/v_P partition. It does not
have the object Harvey describes:

- the **dual alternation** — over/under *and* inner/outer lane, running independently
- **no join** — a continuum through the apparent start, not a closed loop
- left/right arising from those two alternations against an oriented axis
- the **spin-up sequence**: tips round → cross-section shrinks and draws the tip inward →
  nexus spreads centrifugally → **ring at c** → counter-rotation above c
- **the ring as the unique identical-traction-cross-section shape when rolling** — this is
  the reason a nucleon is a ring rather than something else, and it is not written down
- the **contact geometry**: inner/outer with the axis, upper/lower at 90°, gradient between,
  inverted underside → interference → **wake above and below**

**6a. The drag gradient is the load-bearing omission.** Zero files. Yet the magic-numbers
closure schedule rests on radial rods being slip-free *only on the equator* — B(n) = 2(n+1)
exists because of that gradient. The nuclear result depends on a fact about nucleon surfaces
that is documented nowhere.

---

## 7. MISSING — the fuel, and what it implies

One file mentions the 3000 K event still being transmitted. The consequence is not drawn
anywhere: **matter is driven, not self-maintaining.** That is what makes "release the
constraint and the form expands exponentially" a mechanism rather than an assertion, and it
is what forces pressure to be a readout rather than an actor. Every place the framework
describes a particle as *persisting* — topological protection, the trefoil that "cannot be
undone" — is describing a driven system as though it were self-sustaining.

---

## 8. To check — not yet read

Listed so they are not mistaken for cleared:

- **Strong force framing** — the phrase appears in 10+ files (FLM12, PPT05, EMC01, APS06,
  NP16, NP17, GD03, METHOD_B…). Whether any treat it as a separate interaction rather than
  delivered constraint is unread.
- **`Theory/04_Notation.md`** and **`FLM11`** mention Dynamism; whether their reading matches
  §0 is unread.
- **`Compiler/`** carries its own `dimension_engine.hpp` and `types.hpp` referencing the
  scheme — unread, and a second place the ontology could be mis-encoded.
- **`Laws/SDT_Complete_Laws.md`** — the M₀/TeV stratum (53 lines, top quark, Higgs vev)
  remains outstanding from the earlier audit; unrelated to this ontology but still open.
- Whether the triangular T(k) of the dimensional ladder and the triangular T(n+1) of the
  nuclear tier capacity are **one fact or two**. Not asserted either way.

---

## 9. Suggested order

1. **Write §0 into the repository.** Everything else is downstream of the ontology being
   unrecorded. A `Theory/` document stating the generative scheme, the promotion, the
   triangular count, and static-vs-dynamic would have prevented §2a outright.
2. **Fix `OPERATING_PROTOCOL.md` and `SDT_QUICKPOINT_GUIDE.md`** — they teach "crushed knot"
   to every session that starts.
3. **Repair the dead `DE_RERUM` citation** in `state28d.hpp` — point it at whatever §1
   produces.
4. Then §3–§7 file by file, reading each in context.
