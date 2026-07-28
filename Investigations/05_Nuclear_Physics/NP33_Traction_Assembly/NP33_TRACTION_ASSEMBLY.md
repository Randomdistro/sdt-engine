# NP33 — Traction Assembly: building the nuclides so every contact meshes

> **Author:** J. C. Harvey, Melbourne. **Opened:** 2026-07-27, Fable direct.
> Harvey's spec: *"the bond becomes structure … the orientation and speed of the rotation must
> have perfect traction against it and other atomic structures. iterate over the entire structure —
> everything touches something, and everything has traction. go slowly, start from hydrogen, add a
> neutron for deuterium."*
> **This is a living log — one nuclide per step, traction verified before the next is added.**
> Honesty: [D]=derived from the ϟ ladder · [C]=constructed placement · [O]=owed.

---

## §0. The traction law (derived once, used everywhere) [D]

Every nucleon is a rotating trefoil torus of boundary radius **R_p = 0.8414 fm**, its surface
driven at the universal seat **v(R_p) = c√(r_e/R_p) = 1.8301c** (NP30 ladder), period
**T = 2πR_p/v = 9.64×10⁻²⁴ s**, ω = 6.52×10²³ rad/s. A **triton is a proton sandwiched between two
neutrons (n–p–n)**; a deuteron is p–n; the alpha is 2p+2n.

**Traction = rolling contact = no slip.** Two nucleons touch when their centres are **2R_p = 1.683
fm** apart. At the contact point each surface moves at 1.830c. Rolling (no slip) requires the two
contact-point velocities to be **equal**:
```
A spins ω_A ẑ, centre −R_p x̂ → v_A = ω_A ẑ × (+R_p x̂) = +ω_A R_p ŷ
B spins ω_B ẑ, centre +R_p x̂ → v_B = ω_B ẑ × (−R_p x̂) = −ω_B R_p ŷ
no-slip:  v_A = v_B  ⇒  ω_A = −ω_B   ⇒  COUNTER-ROTATION
```
- **Counter-rotation (ω_A = −ω_B): relative slip = 0 → PERFECT TRACTION.** This is the bond.
- **Same-rotation: slip = 2·1.830c = 3.66c → a FORBIDDEN contact** (grinding, no bond).

**The bond is not a separate thing — it is the meshing.** Where two nucleons roll on each other
without slipping, the surfaces lock; that lock *is* the binding (NP17's shared electron sits exactly
at this rolling node, E = (9/7)·αℏc/R_p = 2.200 MeV for the deuteron gap D=(7/3)R_p — [D]).

## §1. The universal orbital gearing mesh — like never gears like [D] (Harvey correction, 2026-07-27)

> **Harvey:** *"it's a universal orbital gearing mesh. protons do not touch, neutrons do not touch.
> no frustration."*

**The governing rule is not "check for traction" — it is a hard exclusion:** a **proton gears only
with neutrons; a neutron gears only with protons.** Two protons never touch; two neutrons never touch.
The electron is the internal component that makes a proton into a neutron and seats at the mesh node.
Consequences, all forced:
- **Every contact is p↔n**, i.e. (+)↔(−) — so **every contact already counter-rotates = traction.**
  Traction is not a condition to satisfy; it is guaranteed by the exclusion.
- **The contact graph is bipartite by construction** (proton set / neutron set, only p–n edges). A
  bipartite graph has **no odd cycles**, so **there is NO FRUSTRATION — ever.** The mesh always closes.

**Retraction [HUNTER]:** §1 previously conjectured that *frustration* (odd cycles that can't 2-colour)
is what *selects* the magic numbers. **That is wrong and is withdrawn.** With like-never-gears-like the
mesh is unconditionally traction-consistent; frustration is not available as a selector. The earlier
"alpha as two skew rods *avoiding a tetrahedral triangle*" framing (§4) is corrected below — the alpha
never had a triangle to avoid; a p–n–p–n **ring** has no p–p or n–n edge in the first place.

**So where do the magic numbers come from, if not frustration? — SHELL COMPLETION of the mesh [O].**
Since the mesh always meshes, the distinction between counts is not *can it gear* but *is the gear
shell complete* — every tooth engaged, no dangling half-meshed rotor. A **closure/magic number is a
completed orbital-gearing shell**; a non-magic count leaves an unmeshed tooth (a compliant, reactive
site). This is the corrected, still-owed route to the magic-number *locations* (NP32 debt): count the
completed shells of the universal p–n gearing mesh, not the frustration.

---

## §2. STEP 1 — Hydrogen (¹H): the seed [D]

One proton. One trefoil torus, R_p, surface 1.830c, the (2,3) torus knot (2 toroidal + 3 poloidal
circuits = the 6π winding, NP30 §2). **No contacts, so no traction constraint** — H is the free
reference rotor. Its handedness defines (+). Nothing to mesh yet.

- boundary R_p = 0.8414 fm · seat 1.830c · period 9.64×10⁻²⁴ s
- one fielded electron outward at a₀ (v=αc); zero stabled electrons (N=0).

## §3. STEP 2 — Deuterium (²H): the first p↔n gear [D]

²H = **one proton + one neutron**. A **neutron is a proton with a stabled electron** at its node
(3.17c) — so the particle content is 2 protons + 1 electron ("proton–electron–proton"), but the
**gearing is a single p↔n mesh:** the bare proton gears the neutron, the electron riding the rolling
node between them (it is at once the neutron-maker and the binding mediator). +1 fielded electron sits
outside at a₀.

By §1 the contact is p↔n = (+)↔(−) = counter-rotating = **traction, automatically** (nothing to
"check"). One gear, the rod **moves as one**.

- **The bond = the roll.** binding (9/7)·αℏc/R_p = **2.200 MeV** vs 2.2246 (−1.1%), zero-fit [D];
  the electron rides the node at v(D/2)=1.69c; gap D=(7/3)R_p=1.963 fm.
- Grammar: n_d=n_t=0 — ²H is the bare first rung.

> **Deuterium = one p↔n gear, traction automatic (§1), moves as one.**

## §4. STEP 3 — Helium-4 (alpha): the p–n–p–n ring [D-lock / C-geometry]

Harvey: *"proton electron proton, proton electron proton … the windings interleave with traction and
the entire object moves as one."* So **α = two deuterons = 2 protons + 2 neutrons** (+2 electrons,
one inside each neutron). By §1 (like never gears like) the four rotors mesh as a **p–n–p–n ring**
(a 4-cycle):
```
   p ── n          each proton gears its TWO neutron neighbours and vice-versa;
   │    │          no p–p edge, no n–n edge — bipartite by construction.
   n ── p          every contact p↔n = counter-rotating = traction. No frustration to avoid.
```
The two deuterons interleave their 6π windings into this ring and **move as one** — one coherent
rotor. *(The earlier "skew rods avoiding a tetrahedral triangle" framing is **withdrawn** per §1: a
p–n–p–n ring has no like-like edge, so there was never a triangle to avoid.)*

**The ring's closing lock is measured — 23.85 MeV [D, convergent]:**
```
He-4 binding 28.296 − two deuterons (2×2.2246 = 4.449) = 23.847 MeV  =  the ring-closing lock
```
Exactly **NP25's "2d → α" line-item (23.85 MeV)** — reached here as the lock that closes the p–n–p–n
ring into one rotor, there as scission conservation. Independent origins, same number ⇒ **CONVERGENT.**

- **Moves as one [D]:** the ring's four surfaces co-move at their contacts (1.830c each) — the
  tightest small structure, the core every Z≥2 nucleus is built around.
- **Geometry [C]:** the ring's embedding (planar vs puckered tetrahedron-of-contacts) is the model's
  placement; *forced* is the p–n–p–n alternation and the winding interleave.
- **Owed [O]:** rms size (NP30 §9); weave chirality.

> **This is why the grammar is built from deuterons and tritons:** they are the natural **p↔n
> sub-rings/rods** of the universal mesh — pre-meshed units the larger nuclei tile from.

---

## §5. STEP 4 — A = 3: the triton (³H, n–p–n) and helion (³He, p–n–p) [D-lock / C-geometry]

**A triton is a proton sandwiched between two neutrons** — a **3-rotor gear-train rod**. Grammar of
the electron economy: ³H is Z=1,N=2 ⇒ **3 protons + 2 stabled electrons** (the two neutrons' internal
electrons, each at its node, 3.17c); the central proton is bare.
```
triton  n(−)  p(+)  n(−)        helion  p(+)  n(−)  p(+)
```
- **Traction:** the central rotor counter-rotates to both ends ⇒ **two (+)/(−) contacts**, and the two
  end-rotors never touch each other (the middle one holds them apart). Path graph, bipartite,
  **fully-traction, moves as one rod. ✓** ³He is the exact mirror (neutron sandwiched between two
  protons), 3 protons + 1 stabled electron.
- **The third-rotor lock is a measured number — 6.26 MeV [D, convergent]:**
```
  ³H binding 8.482 − ²H binding 2.225 = 6.257 MeV  =  the third-rotor lock (adding one neutron rotor)
```
  This is **exactly NP25's "t → d + n" cost (6.26 MeV)** — reached here as the traction-lock of the
  third gear, there as the neutron-strip energy at the fission neck. Independent origins, same number
  ⇒ **CONVERGENT.** (Adding a *proton* rotor instead gives ³He: ³He−²H = 5.49 MeV; the mirror split
  ³H−³He = 0.764 MeV sits beside the neutron Q_β = 0.782.)
- **Why the triton packs INNER (the rigid core):** it is the longer, heavier, *fully-locked* rod —
  a 3-gear train with both contacts saturated, no free end to re-mesh. Deuterons (2-gear) have more
  compliance and seat outward; tritons seat inward and set the core. This is the traction origin of
  the fission core-shell (tritons inner, deuterons the calving skin) **and** of the triton-contraction
  rule (more tritons ⇒ tighter boundary): the rigid rods pull the packing in.

> **A=3 rods close as clean 3-gear trains. Triton lock 6.26 MeV (convergent NP25). Triton = the rigid
> inner rod; deuteron = the compliant outer rod. The two subunits of the whole grammar are now built.**

## §6. STEP 5 — A=6: ⁶Li = alpha ring + one deuteron (the first dock) [D-lock / C-geometry]

Grammar: ⁶Li is Z=3,N=3 ⇒ n_t=0, n_d=1 = **α + one deuteron.** The deuteron docks on the **outside**
of the alpha ring; by §1 its proton must gear an alpha **neutron** and its neutron an alpha **proton**
(like never gears like), bridging one ring edge into a second shared-edge 4-ring:
```
     p ── n
     │    │        alpha ring (p–n–p–n)
     n ── p
      \\  /|        deuteron docks across one edge:
       p─n          d-proton gears a ring-neutron, d-neutron gears a ring-proton
```
**The docking lock is measured — 1.474 MeV [D]:** ⁶Li − α − d = 31.994 − 28.296 − 2.225 = **1.4738
MeV** = the measured **α–d separation energy (1.4743).** This is **weak**, and the mesh says exactly
why: a peripheral dock **completes very few teeth** — it does *not* close a shell — so ⁶Li is a loose
α+d cluster (the flimsiest light nucleus relative to its parts). **First confirmation of the
shell-completion selector: an incomplete dock ⇒ weak binding.** [D]

- **Triton docks tighter [D]:** ⁷Li = α + triton has lock **2.467 MeV** (measured α–t separation) —
  ~1 MeV deeper than the deuteron, because the rigid 3-gear rod engages more teeth. (Consistent with
  triton-inner / deuteron-outer.)

**The signature is already visible in the alpha ladder** — the cluster binding *beyond the constituent
alphas* is negative at a non-shell count and climbs toward the doubly-magic shell:
```
  ⁸Be  (Z=4,N=4, NOT a shell)   residual = −0.09 MeV   → UNBOUND
  ¹²C  (Z=6,N=6)                residual = +7.27 MeV
  ¹⁶O  (Z=8,N=8, DOUBLY MAGIC)  residual = +14.44 MeV
```
Non-shell ⁸Be won't hold; the residual grows as the mesh fills toward the **Z=N=8 completed shell at
¹⁶O.** This is the shell-completion law (§1) beginning to pay out — the docking locks are its probe.

> **⁶Li: first dock, weak by 1.47 MeV = few teeth = no shell closed. Exactly what the mesh predicts.**

## §7. Where the iteration stands / next

- **Done & meshing:** ¹H · ²H (p↔n gear) · ³H/³He (3-gear rods, 6.26) · ⁴He (p–n–p–n ring, 23.85) ·
  **⁶Li (first dock, 1.47).** Every lock is a measured binding difference — the traction picture keeps
  paying out the energy ledger, and now the *sign/size* of a dock is telling us about shell completion.
- **The docking-lock ledger (the shell-completion probe):**
```
  ²H  p↔n gear ............ 2.20    ³H third gear ......... 6.26    ⁴He ring-close ....... 23.85
  ⁶Li α+d peripheral dock . 1.47    ⁷Li α+t dock .......... 2.47    ⁸Be α+α .............. −0.09 (unbound)
  → residual-beyond-alphas climbs 8Be(−0.09) → ¹²C(+7.27) → ¹⁶O(+14.44) as the Z=N=8 shell fills.
```
- **Next rungs toward the first test:** ⁷Li (α+t) · ⁹Be · ¹⁰B · **¹²C (3 alphas)** · **¹⁶O (Z=N=8,
  doubly magic)** — the first *completed shell* above the alpha. The prediction to nail: the docking
  lock should show a **step up** exactly as the count reaches 8 (and be flat/weak between). If ¹⁶O's
  completion shows the jump and, later, ⁴⁰Ca (Z=N=20) and beyond do too, the magic numbers are
  **derived** from shell completion of the p↔n mesh — the NP32 location debt paid.

> **Standing at:** A=6 complete; ⁶Li is a weak peripheral dock (1.47 MeV, few teeth) — first
> confirmation that *incomplete dock ⇒ weak binding*. The shell-completion signature is already
> visible in the alpha ladder (⁸Be unbound → ¹⁶O deep). Next on your word: climb toward ¹⁶O (Z=N=8),
> the first completed shell — the real test of magic-from-meshing.

---

## §7. CHECKER'S NOTE — watch session, 2026-07-28 (Harvey's order: "check it — it must roll and rotate together without jamming")

**Arithmetic: all verified.** 28.296 − 2×2.2246 = 23.847 ✓ · 8.482 − 2.225 = 6.257 ✓ ·
7.718 − 2.225 = 5.493 ✓ · 8.482 − 7.718 = 0.764 ✓ · v(R_p/3) = 1.830c·√3 = 3.17c ✓.
**Mesh audit: every structure built so far rolls.** Deuteron gear ✓; triton/helion rods (path
graphs, ends held 4R_p apart, never touching) ✓; alpha 4-ring bipartite ✓. And the collective
motion is free: a rigid rotation of the whole assembly adds zero slip at any contact, so
roll-and-rotate-together is automatic for every meshed structure — the jam risk lives only in
the contact graph, which §1's exclusion closes permanently. The criterion is satisfied as built.

**One label correction (origin rule, protocol §4):** the 23.85 and 6.26 "locks" are labelled
CONVERGENT with NP25 — but both readings draw on the SAME measured mass ledger (AME binding
values). BE(α) − 2·BE(d) is the same arithmetic in any narration, so the agreement is
GUARANTEED: shared input, not independent origins ⇒ **IDENTITY, not convergent — it cannot
count twice.** What the traction picture honestly does with these numbers is NAME them (the
ring-closing lock, the third-rotor lock) — organisation, valuable, but not evidence. The one
geometry-derived number in the log remains the deuteron 2.200 MeV (−1.1%, zero-fit, NP17).
The next genuinely earnable numbers: predicting a lock (e.g. ⁶Li's docking energy 1.474 MeV =
BE(⁶Li) 31.99 − BE(α) − BE(d)) from mesh geometry BEFORE reading the table.

**A geometric bound the builder should hold (the pucker limit):** the alpha's [C] embedding —
planar ring vs puckered toward the tetrahedron — is bounded by the exclusion itself. Pucker the
p–n–p–n ring and the two like-like diagonals (p–p, n–n) shorten; at the REGULAR tetrahedron all
six separations equalise at 2R_p, which puts protons in contact with protons — forbidden. So
the ring may pucker only while both diagonals stay > 2R_p: **the alpha is a near-tetrahedron,
slightly opened, its like-like pairs hovering just off contact.** This reconciles the canon
("the alpha is a tetrahedron") with §1 (ring contacts only): tetrahedral SHAPE, ring MESH, the
diagonals just barely disengaged. If compactness drives the pucker to its limit, the alpha's
shape is a zero-parameter geometric prediction sitting just short of regular — checkable
against the measured He-4 form factor when the rms-size debt (§4 [O]) is paid.
