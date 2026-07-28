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

## §1. The rule the traction law forces — 2-colouring and frustration [D]

Every touching pair must counter-rotate. So the nucleons **2-colour** into a (+) set and a (−) set,
and **a contact is a valid bond only if it joins a (+) to a (−).** Therefore:

> **A structure can be fully-traction iff its contact graph is BIPARTITE.**
> An **odd cycle** (e.g. a triangle of three mutually-touching nucleons) **cannot be 2-coloured** —
> at least one contact is forced (+)/(+) or (−)/(−) = a slipping, frustrated contact.

This is the engine we have been missing. **Frustration is not a defect to avoid — it is the selector.**
A configuration where the frustration cancels or closes (every nucleon finds a consistent counter-
rotating seat) is a **closure**; one that cannot is strained. **Conjecture [O]: the magic numbers are
the nucleon counts at which the interleaved-trefoil contact graph admits a globally consistent
traction assignment** — the counts where the gear-train closes. This is the non-circular route to the
magic-number *locations* that NP32 flagged as still-owed. Not proven; it is the thing this log is built
to test as the structures grow.

---

## §2. STEP 1 — Hydrogen (¹H): the seed [D]

One proton. One trefoil torus, R_p, surface 1.830c, the (2,3) torus knot (2 toroidal + 3 poloidal
circuits = the 6π winding, NP30 §2). **No contacts, so no traction constraint** — H is the free
reference rotor. Its handedness defines (+). Nothing to mesh yet.

- boundary R_p = 0.8414 fm · seat 1.830c · period 9.64×10⁻²⁴ s
- one fielded electron outward at a₀ (v=αc); zero stabled electrons (N=0).

## §3. STEP 2 — Deuterium (²H): the first contact [D-traction / C-orientation]

Add a neutron. **A neutron is a proton with one stabled internal electron** at its node R_p/3
(v=3.17c) — the electron economy (N stabled inward). So ²H = proton(+) + neutron, their two tori
brought into contact.

**The single contact:** centres 2R_p = 1.683 fm apart. For traction the neutron must be **(−)** —
counter-rotating to the proton — so the two surfaces roll without slip (relative velocity 0 at the
contact). One (+)/(−) contact, bipartite trivially, **fully-traction. ✓**

- **Orientation [C]:** the two spin axes are parallel and ⊥ to the p–n line of centres (the gear
  configuration that makes the contact roll). This is the model's assignment; what is *forced* is
  the counter-rotation, not the absolute axis direction.
- **The bond = the roll.** The shared/stabled electron seats at the rolling node between them; the
  gap-centre moves at v(D/2)=1.69c; binding (9/7)·αℏc/R_p = **2.200 MeV** vs 2.2246 measured (−1.1%),
  zero-fit [D]. The neutron's own stabled electron sits deeper, at its node (3.17c).
- Grammar: n_t = N−Z = 0, n_d = 0 — ²H is below the α-core threshold (it is the bare first rung).

> **Deuterium closes with one rolling contact. Traction: 1/1 contacts meshing.**

---

## §4. What's next in the iteration (not yet built)

- **STEP 3 — ³H (triton), the n–p–n unit itself:** p(+) sandwiched between two n(−). Two contacts,
  both (+)/(−), a linear chain → still bipartite → should be fully-traction. Verify the two neutrons'
  axes and that they need not touch each other. This *defines the triton as a subunit*.
- **STEP 3′ — ³He (p–n–p):** neutron(−) between two protons(+). Mirror of the triton.
- **STEP 4 — ⁴He (alpha), the first frustration test:** 2p+2n. If the four pack tetrahedrally, every
  nucleon touches the other three → the contact graph contains **triangles (odd cycles)** → it
  **cannot** be 2-coloured → at least one contact is frustrated. **This is the make-or-break:** does
  the alpha relieve the frustration by a geometry that avoids the triangle (e.g. the two interlocked
  deuterons L–R–L–R of NP30, a 4-cycle = bipartite), or does the frustration survive? The answer
  starts telling us whether "closure = traction-consistent" holds.

> **Standing at:** ²H, traction complete. Next on Harvey's word: the triton (n–p–n), then the alpha
> frustration test — the first real probe of the closure conjecture.
