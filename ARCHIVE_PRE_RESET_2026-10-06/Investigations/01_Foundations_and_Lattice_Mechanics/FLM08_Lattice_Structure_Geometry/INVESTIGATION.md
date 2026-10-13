# FLM08 — The Lattice Structure

**J. C. Harvey, Melbourne — 2026-06-24.** Domain: `01_Foundations_and_Lattice_Mechanics`.
Class **[GEOMETRY]** (exact, parameter-free). Engine: `sdt::laws::lattice_structure` in its own standalone
header `Engine/include/sdt/lattice_structure.hpp` (depends on nothing but `<cmath>`/`<numbers>`; `laws.hpp` untouched).
Verifier: `cq53_lattice_structure.cpp` → **27 PASS / 0 FAIL**. Model: `cq53_lattice_structure.html`.

---

## Thesis

The CONDENSA result is that the spation substrate is forced — by exact geometry, no physics input — off
both *crystalline* order (tiles, but anisotropic) and *close-packed icosahedral* order (isotropic, but
frustrated) and onto a **corner-sharing tetrahedral random network**. The forcing facts are a small set of
irrational angles. This investigation does two things:

1. **Reaches each invariant by ten different branches of mathematics.** Where they target the same value they
   must agree to machine precision. That agreement is the evidence: a number reached one way could be a
   coincidence of construction; a number reached *ten* ways is a property of the object.
2. **Constructs a SHELL** in this environment and reads off its properties.

**Honesty.** Everything here is class [GEOMETRY] — provable, falsification-proof, no free parameters. The
separate claim that the physical vacuum *is* this network is class [IDENTIFICATION] (interpretive) and is
**not** asserted by this tool. The numbers stand on their own.

---

## The invariants (engine constants)

| symbol | value | meaning |
|---|---|---|
| `dihedral` δ | `arccos(1/3) = 70.528779°` | tetrahedron face–face angle (the frustration source) |
| `bond_angle` | `arccos(−1/3) = 109.471°` | tetrahedral "methane" angle (supplement of δ) |
| `five_edge_deficit` Δ₅ | `2π − 5δ = 7.356103°` | leftover gap ⇒ tetrahedra **cannot tile E³** |
| `bc_twist` θ | `arccos(−2/3) = 131.810315°` | Boerdijk–Coxeter helix twist/cell (irrational ⇒ never closes) |
| `bc_radius` / `bc_rise` | `3√3/10` / `1/√10` | helix radius / axial rise per cell (unit edge) |
| `screw` partition | `1/√10 : 3/√10` → **3:1** (energy 9:1) | channel mode ratio: current ⇒ circulation |
| `icosa_shell_gap` | `8/√(10+2√5) − 2 = 0.102924 r` | residual gap in the 12-around-1 kissing shell |
| `coordination` | `4` (= W+1) | corner-sharing bonded neighbours |
| `void_fraction` | `1 − π√3/16 = 0.659913` | open void (diamond limit) |

---

## The ten methods

Each is a genuinely different branch of mathematics. The right-hand column is the invariant it lands on.

| # | method | branch | converges on |
|---|---|---|---|
| **M1** | edge-perpendicular projection of opposite vertices | vector geometry | δ |
| **M2** | regular *d*-simplex dihedral `= arccos(1/d)`, d=3 | combinatorial geometry | δ |
| **M3** | vertex figure = equilateral 60° spherical triangle; spherical law of cosines; excess = solid angle `arccos(23/27)` | spherical trigonometry | δ, Ω |
| **M4** | **closure** `Σvᵢ = 0` + isotropy ⇒ pairwise dot `−1/3`; Gram eigenvalues `{0, 4/3, 4/3, 4/3}` | linear algebra | bond angle (⇒ δ as supplement) |
| **M5** | build the helix by **reflecting** `vₙ₋₄` across `plane(vₙ₋₃,vₙ₋₂,vₙ₋₁)`; twist from successive local-frame rotation `tr(R)=1+2cosθ` | numerical / orthogonal frames | θ (and unit-tetra check) |
| **M6** | impose `d₁=d₂=d₃=a` on `vₙ=(R cos nθ, R sin nθ, nh)` ⇒ `cosθ=−2/3`, `R²=27/100`, `h²=1/10` | algebra / screw constraints | θ, R, h, screw 3:1 |
| **M7** | discrete (Regge) curvature: in **S³** five tetrahedra *do* close — the `{3,3,5}` 600-cell has dihedral `72°`; `Δ₅ = 5·(72° − δ)` is the curvature flat space cannot supply | discrete differential geometry / polytopes | Δ₅ (curvature reading) |
| **M8** | 12 golden-ratio icosahedron vertices at circumradius 2r; nearest-neighbour edge `> 2r` leaves the gap | variational packing (Tammes) | shell gap |
| **M9** | Maxwell counting: `6N` rigid-unit dof vs `3·(4N/2)` corner constraints ⇒ **isostatic**, floppy RUMs exist | constraint/rigidity theory | coordination 4, the soft mode |
| **M10** | corner-sharing = diamond topology; `r = a√3/8`, 8 atoms/cell ⇒ `φ = π√3/16` | crystallographic density | void fraction |

**Convergence achieved:**
- **δ** independently by **M1, M2, M3, M4** — four unrelated routes, identical to 9 figures.
- **θ** by **M5** (numeric construction) and **M6** (analytic) — identical.
- **Δ₅** by the direct `2π − 5δ` and by **M7**'s curvature form `5·(72° − δ)` — identical (and M7 reveals *why*: the structure wants to live on a 3-sphere).
- **gap** by **M8** coordinates and the closed form.
- **coordination / void** by **M9** (rigidity) and **M10** (density), two different physical handles.

---

## The shell in this environment

There are **two coexisting notions of a shell**, and the distinction is the whole CONDENSA fork:

**(a) The kissing shell — 12 around 1, icosahedral, FRUSTRATED.**
Twelve unit spheres kiss a central unit sphere (3-D kissing number = 12) on the vertices of an icosahedron of
circumradius `2r`. But the icosahedron edge is `2.102924 r > 2r`, so the twelve neighbours **cannot also touch
each other** — a residual `0.102924 r` gap remains. The shell **cannot close**. This is the close-packed
icosahedral branch the substrate **rejects**.

**(b) The bonded shell — 4 around 1, tetrahedral, CORNER-SHARING.**
Each node bonds to four neighbours (coordination 4 = `W+1`, the trefoil/lepton seat). This is the branch that
**can be space**: statistically isotropic *and* space-filling, ~66% open void threading the convergence.

**Breathing modes of the 12-shell.** The twelve radial degrees of freedom decompose under icosahedral symmetry
as `12 = 1 + 3 + 5 + 3`:

| ℓ | count | mode |
|---|---|---|
| 0 | 1 | breathing (uniform radial pulse) |
| 1 | 3 | translation (rigid shift, zero-frequency) |
| 2 | 5 | quadrupole (shape distortion) |
| 3 | 3 | icosahedral (the 3-fold / trefoil-compatible mode) |

---

## Properties of the structure

- **coordination 4**, corner-sharing (shared vertex = hinge; inter-tetrahedral angle free)
- **statistically isotropic** (amorphous form) — no preferred axis
- **space-filling** (the diamond/CRN topology occupies 3D; ~66% void)
- **frustrated kissing shell** (12-around-1 cannot close; gap 0.103 r)
- **aperiodic face-sharing helix** (the BC tetrahelix never closes — irrational twist)
- **isostatic / rigid-unit-mode soft** — compression proceeds by hinge rotation, not bond squeeze
- **screw channels** through the void carry a fixed **3:1 torsion:translation** (axial transport ⇒ circulation)

---

## Run it

```bat
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include ^
   Investigations\01_Foundations_and_Lattice_Mechanics\CQ53_Lattice_Structure_Geometry\cq53_lattice_structure.cpp
cq53_lattice_structure.exe        :: → 27 PASS / 0 FAIL
```

Open `cq53_lattice_structure.html` in a browser for the animated model (9 Three.js scenes:
tetrahedron/dihedral, the 5-around-edge gap, the BC helix, the corner-sharing hinge, the kissing shell with
breathing pulse, the corner-sharing random network, the screw channel, and the S³/600-cell curvature reveal).

---

## Verdict

The frustration geometry is **class [GEOMETRY], exact, and over-determined**: every invariant is reached by at
least two independent methods, and the dihedral by four. This is the strongest evidence-grade a piece of the
framework can carry — not "fits the data" but "is forced by mathematics, multiply." The constants stand in
their own standalone header `sdt/lattice_structure.hpp` (`laws.hpp` left untouched); the substrate
*identification* remains, honestly, an interpretation built on top of them.
