# FLM03 — Macro-spation co-rotational formula + dependency stack

> Written 2026-06-08 under the §0 anti-creep protocol (`PROMPT.md`). **Honest scope:** what is rigorous is
> marked rigorous; the one coefficient that is *not* derived is flagged as a **candidate**. Nothing here is
> claimed as a verification of FLM03's field law — only as a mechanical picture *consistent with* it.

---

## PART A — the macro-spation co-rotational formula

### Setup
Spations are **perfect spheres**, radius `a = ℓ_P/2`, **pressed against the proton's hard topology under the
convergence pressure**, with **perfect traction (no slip)**. **Run from the equator**, where the proton
surface phase speed is `v₀`. From measured anchors:
```
v₀ = c/ϟ_H = c·α·√(a₀/R_p) = 1.8301 c     (ϟ_H = (1/α)√(R_p/a₀) = 0.54643)
```

### Step 1 — the single rolling contact  (RIGOROUS)
At the equator a spation's inner face touches the proton moving at `v₀`. No-slip → it spins at
```
ω_s = v₀ / a          (= 6.79×10⁴³ rad/s at R_p)
```
A sphere spinning about a held centre presents its **diametrically-opposite (outer) face moving at −v₀**.
So the next shell out is driven at the **same magnitude, opposite sense**:
> **shells contra-rotate; magnitude is preserved across one contact; there is no drag** — axially-aligned
> spheres mesh like gears (no slip ⇒ no friction loss). This is the lossless contra-rotating hand-off.

### Step 2 — what rolling ALONE gives  (the honest failure)
If the spation centres are fixed (packed lattice) and only the magnitude is passed, then `|v| = const` at
every shell — `1.831c` everywhere — and only the angular rate falls, `ω = v/r ∝ 1/r`.
**Numerically checked: pure rolling produces NO radial decay.** But the measured profile drops **250×**
(`1.831c → αc`). **So the decay is NOT in the rolling** — rolling-alone is wrong by the full 250×.

### Step 3 — the decay needs a per-contact lag  (form RIGOROUS, coefficient CANDIDATE)
The observed profile is `v(r) = v₀√(R_p/r)`. Differentiating (numerically confirmed `= 1.0000` at every
radius):
```
d(ln v)/dr = −1/(2r)
```
This is exactly a **per-contact fractional lag of `a/r`**: the radial step per contact is `ℓ_P = 2a`, so
`(a/r)/(2a) = 1/(2r)`. Integrating gives the macro formula:

> ## v(r) = v₀ · √(R_p / r),   v₀ = c·α·√(a₀/R_p) = 1.831 c
> with **contra-rotating shells**, per-spation spin `ω_s(r) = v(r)/a`, decay set by a per-contact lag `a/r`.

Checks (this session): `v(a₀)/c = 0.007297 = α` to six digits; total drop `R_p→a₀ = 250.8× = √(a₀/R_p)`.

### Step 4 — the gap: the coefficient is NOT derived  (FLAG)
*Where does the `a/r` lag come from?* **Candidate:** a sphere of radius `a` rolling at radius `r` has its
centre on the larger circle `r+a`, so the outer hand-off geometrically lags the inner by ~`a/r` per contact
(finite sphere size relative to `r`). This gives the **right form**. But I have **not** rigorously derived
that the coefficient is exactly `a/r` (vs `2a/r`, or a packing-dependent value). Earning it requires the
**per-point computation**: the off-equator latitudes (*not all contact points roll the great circle* —
surface speed falls as `ω·R·cosθ`), the **tetra/octa/penta/hexa packing interstices**, which contacts the
rotation **disallows**, the **pressurised** lattice, and the **ontic transmitted at c** shaping the
convergent anisotropy.

> **Status:** the 1/√r **form** and the **contra-rotation** are reproduced; the decay **coefficient is a
> candidate, not a derivation.** And note plainly: `v(r)=v₀√(R_p/r)` *is* FLM03's field law — this shows the
> rolling picture is **consistent with** it under one assumption, it does **not independently derive** it.

---

## PART B — the dependency stack (what FLM03 actually rests on)

FLM03's stated prerequisites are *Law V, Law VI, PPT01, PPT05, PPT06*. Bottom-up:

```
┌ FOUNDATION (Laws)
│  Law I   convergence pressure Φ, P_conv ........... the pressurised medium the spations sit in
│  Law V   movement budget v_circ²+v²=c² ............ the c-limit; phase-vs-transport ("no spation > c")
│  Law VI  vortex topology W∈{1,3} .................. proton = (2,3) trefoil, electron = unknot
├ GEOMETRY
│  packing.hpp  Tammes / close-packing ............. the tetra/octa/penta/hexa interstices
│                                                     ← the per-contact rolling NEEDS this
├ VORTEX RESULTS
│  PPT01  vortex equilibrium ........................ the (2,3) trefoil v_T=0.632c, v_P=0.775c, budget closure
│  PPT05  trefoil confinement ....................... why W=3 holds together
│  PPT06  spation traction .......................... the 6π / traction ratio 3(W+1)=12, the gear ratio
│                                                     ← the co-rotation hand-off NEEDS this
├ THIS NODE
│  FLM03  rotation field v(r) ....................... built on ALL the above + measured anchors R_p, a₀, α
└ DOWNSTREAM (consumers)
   APS01 emissions · GOM02 k-hierarchy · bonding · 21-cm · anything using the koppa field at scale
```

**The blunt finding:** the macro formula's missing `a/r` coefficient depends on **PPT06 (traction)** and
**packing (interstices)** — and *those are themselves continuum summaries, not per-spation computations.*
The actual bottom of the stack — the **per-contact, pressure-resolved, packing-aware spation mechanics** —
**has not been computed in any investigation.** It is the foundational open problem the whole stack stands
on, and it is exactly the calculation too large for continuum algebra or for me in chat. *"Running FLM03 for
real"* means building that bottom-of-stack computation and propagating it up — not re-running the field law
and pronouncing.

---

## NEXT
Hand the bottom-of-stack per-spation computation to a heavier reasoning engine (Google DeepThink): give it
the §0 protocol + this formula + this stack + the precise open problem — *derive the per-contact `a/r` lag,
and the full `v(r)`, from per-spation rolling/packing/pressure mechanics, run from the equator, accounting
for off-equator latitudes and the tetra/octa/penta/hexa interstices.* Prompt to be drafted jointly.
