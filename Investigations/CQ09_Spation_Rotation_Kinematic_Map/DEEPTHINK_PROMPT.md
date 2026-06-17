# Prompt for Google DeepThink — design the per-spation lattice simulation (SDT hydrogen rotation, CQ09)

> Copy everything below the line into DeepThink. It is self-contained (DeepThink has no access to our repo).

---

## 0. WHAT YOU ARE BEING ASKED TO DO

You are **not** asked for a closed-form answer, and **not** asked to reproduce any known physics result. You
are asked to **design a concrete, runnable computational scheme** — a **simulation specification** — for the
per-element mechanical system described below: the state variables, the governing per-contact equations, the
lattice/packing geometry, the discretisation, the update/iteration rule, the boundary and initial
conditions, the outputs, and the validation tests. Hand back something precise enough that a competent
programmer could implement it directly. Where the mechanics genuinely cannot determine something, **say so
and mark it OPEN — do not fill the gap with imported physics.**

## 1. THE FRAMEWORK AND THE RULES YOU MUST OBEY (non-negotiable)

This is **Spatial Displacement Theory (SDT)** — a purely **mechanical** theory of pressure, displacement,
and rotation in a contact lattice of perfect rigid spheres called **spations**. It is **NOT** quantum
mechanics, **NOT** field theory, **NOT** general relativity, and it must not borrow their **concepts,
vocabulary, units, or machinery.**

**Forbidden (do not use, even as scaffolding):** wavefunction, probability amplitude/density, operator,
Hilbert space, "orbital" as a cloud, spin (as an intrinsic quantum), magnetic moment / magneton, virtual
particles / loop diagrams / exchange bosons, Schrödinger/Dirac/QED machinery, "test particle", "observer",
"measurement", curved spacetime, and any **fitting of a known target value**. If a step seems to need one of
these, **flag it OPEN** rather than importing it. A plausible mechanical-sounding phrase that secretly
stands in for one of these (e.g. "the electron *samples/penetrates* the core" = a probability density in
disguise) is also forbidden.

**Required ontology:**
- A particle is a **hard, localised, solid vortex** — never a cloud, never a probability, never "just
  displacement."
- Use only: the **lattice geometry**, the **rigid spheres**, **contact mechanics** (rolling, traction,
  packing, pressure), and the **relay of disturbance at speed c**.
- Permitted physical constants: `ℓ_P, c, ℏ, α, m_e, m_p`, plus two measured radii `R_p, a₀`. **No G, no M
  (in kg), no GM.**
- In your output, **distinguish what is rigorously forced by the mechanics from every assumption you
  introduce** — flag each assumption explicitly. Do **not** present a definitional restatement (e.g. a
  volume re-expressed as a count of cells) as a derivation.

## 2. THE PHYSICAL SYSTEM TO SIMULATE

- **Central hard body — the proton:** a `(2,3)` trefoil **solid torus** (a hard knot), surface radius
  `R_p = 8.414×10⁻¹⁶ m`. Its surface **rotates** with an equatorial **phase speed** `v₀ = 1.831 c`. Its
  internal circulation splits into toroidal `v_T = c√(2/5) = 0.632c` and poloidal `v_P = c√(3/5) = 0.775c`
  (`v_T² + v_P² = c²`), tracing the trefoil's three equally-spaced crossings.
- **The medium — spations:** perfect rigid spheres of radius `a = ℓ_P/2 = 8.08×10⁻³⁶ m`, in a **close-packed,
  pressurised lattice** under isotropic convergence pressure, filling space around the proton.
- **The contact law — perfect traction:** spations are pressed against the proton and against each other and
  **roll without slipping (perfect traction).** Two **axially-aligned** spheres can **contra-rotate at their
  contact with no slip ⇒ no drag** (they mesh like gears).
- **The relay:** a disturbance (rotation) is handed **outward, shell by shell, at speed c.**
- **Outer reference fact (a boundary condition to REPRODUCE, not to plug in):** at radius
  `a₀ = 5.292×10⁻¹¹ m` the rotation has slowed to `α·c = 2.188×10⁶ m/s` — this is where the electron (a
  separate hard `W=1` vortex) orbits. *Your simulation should output this, not assume it.*

## 3. WHAT IS ALREADY KNOWN — a continuum approximation, and the precise gap

A continuum (smeared) approximation gives the radial profile
```
v(r) = v₀ · √(R_p / r),      v₀ = c·α·√(a₀/R_p) = 1.831 c
```
i.e. `1.831c` at `R_p` → `c` at `2.818×10⁻¹⁵ m` → `αc` at `a₀` (a **250× drop**, `= √(a₀/R_p)`). This is
equivalent to a **per-contact fractional lag of `a/r`** (`d ln v / dr = −1/(2r)`).

What is **rigorous**: the single rolling contact gives **contra-rotation, magnitude preserved per contact,
no drag**, with spin `ω_s = v/a`. What **fails**: *pure* rolling with fixed sphere centres gives **no decay
at all** (`|v| = const`), so the observed 250× decay is **not in the rolling alone**.

**THE OPEN PROBLEM — this is what your simulation must resolve:** *where does the `a/r` lag (the decay)
actually come from, mechanically?* Candidate ingredients (you must determine which matter and with what
coefficient):
- the **finite sphere size** (a rolling sphere of radius `a` at radius `r` has its centre on the `r+a`
  circle);
- the **off-equator latitudes** — *not all contact points roll the great circle*: a sphere's surface speed
  falls as `ω·R·cosθ` with latitude `θ`, so off-equator contacts transmit less;
- the **close-packing interstitial geometry** — tetrahedral / octahedral / and (likely) pentahedral /
  hexahedral holes — which **disallows certain contacts** as the shells rotate;
- the **pressure** packing the spheres;
- the **relay at c** shaping the convergent **anisotropy**.

## 4. WHAT THE SIMULATION MUST CAPTURE (the per-element physics)

For each spation, **addressed individually**, the scheme must represent:
1. its **address** in the close-packed lattice, and how packing fixes which neighbours it contacts and **at
   what latitudes**;
2. its **contact(s)** with the proton surface and/or inner-shell spations, and the **convergence phase** at
   each contact;
3. the **rolling/traction kinematics** at each contact (no-slip; the great-circle-vs-latitude `cosθ` effect;
   axially-aligned **contra-rotation with no drag**);
4. its **own spin**, and how the trefoil's **toroidal + poloidal** rotation drives it;
5. the **shell-by-shell knock-on** — how one shell's rotation sets the next through the interstices,
   including which contacts the rotation geometry **disallows**;
6. the **pressurised** lattice (the convergence pressure packing the spheres);
7. the **disturbance transmitted at c** shaping the convergent **anisotropy**.

## 5. THE DEPENDENCY STACK (inputs your design may assume as given)

```
Laws: convergence pressure P_conv (medium) · movement budget v_circ²+v²=c² (the c-limit) · topology W∈{1,3}
  → close-packing geometry (tetra/octa/penta/hexa interstices)
    → (2,3) trefoil velocities v_T=0.632c, v_P=0.775c   [the proton's internal circulation, given]
      → spation traction / gear hand-off                [the thing you are designing the mechanics of]
        → the rotation field v(r)                       [the output to validate]
```
The trefoil velocities and the packing geometry may be **taken as given inputs**; the **traction/hand-off
mechanics is the unknown you are to formalise**.

## 6. DELIVERABLE — hand back a simulation specification

1. **State variables** per spation (position, orientation, spin axis & rate, contact set).
2. **Governing per-contact equations** (no-slip/traction; the latitude `cosθ` factor; the contra-rotation
   rule; the pressure/packing constraints).
3. **Lattice/packing model** (how to tile the shells; the interstitial geometry; which contacts exist and
   which are disallowed under rotation).
4. **Update/iteration rule** (how rotation propagates shell-to-shell per tick at c; the boundary condition
   at the proton equator `v₀ = 1.831c`).
5. **Discretisation choices** and their trade-offs (you may approximate — state exactly where and how, and
   the expected error).
6. **Outputs to record** (the `v(r)` profile; per-shell rotation senses; per-contact traction; the
   effective decay-per-shell).
7. **Validation tests:** does the scheme **REPRODUCE** `v(r) = v₀√(R_p/r)` and land on `αc` at `a₀`
   **without plugging those in**? Does the `a/r` decay coefficient **emerge** — or a different one? What
   would falsify the scheme?
8. **Flag every assumption** you introduce, and anything that genuinely cannot be done mechanically (mark
   **OPEN**; do not import QM to close it).

## 7. CONSTRAINTS RECAP
Forward/mechanical only · SDT-native · no QM/GR concepts, vocabulary, units, or machinery · no G/M ·
reproduce (don't plug) the `a₀ / αc` boundary · distinguish *derived* from *assumed* · mark genuine gaps
OPEN rather than repainting them.
