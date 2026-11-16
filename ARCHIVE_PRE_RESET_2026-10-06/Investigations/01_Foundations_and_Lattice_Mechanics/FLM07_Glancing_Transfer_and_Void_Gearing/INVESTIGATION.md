# FLM07 — Glancing Transfer, the 0.103 Frustration, and Void Gearing of the Contra-Rotating Shell

> **Author:** James Christopher Tyndall, Melbourne. 2026-06-20.
> **Status:** Parts A–D **DERIVED/COMPUTED**; the tetrahedral thread is selected
> by the 2026-08-14 Law-IV minimum-engaged-resistance test.
> **Tool:** `cq52_glancing_void_gearing.cpp` (consumes `Engine/include/sdt/laws.hpp`; output `cq52_results.txt`).
> **Scope:** the glancing geometry, packing frustration and void ratios are
> exact. Selection of the tetrahedral thread is conditional on Law IV's
> registered minimum-resistance path: both seat-only and contact-weighted
> engaged-volume prices select it before particle-radius comparison.

---

## 0. The question

PPT06 showed the proton trefoil demands a single superluminal phase velocity (1.831c at R_p) and converts the lattice's inability to keep up into the wake. APS04 expanded that wake into multipoles — but **borrowed the Legendre P₂ from QM** and flagged it (CQ38_ANGULAR_QUANTISATION:321). Two things were left open:

1. **Where, exactly, does the superluminal phase couple to the lattice?** It is not one velocity — `v_phase(r) = c/k(r)` varies across the toroid. There must be a locus where the *glancing projection* equals the relay speed c. What is it, and does it derive the wake multipoles natively?
2. **What does the lattice do under that drive — and what shape does it take?** Spation rotation, co-dragging, contra-rotation; and the packing the rotating shell actually rides. Harvey: *"there are a bunch of angles at all different points on that toroid where a glancing blow is c"*, and the contra-rotating shell *"naturally possesses the least amount of spations, with perhaps one gearing for four."*

This investigation answers (1) exactly and (2) as far as geometry allows, flagging the conjectural seam.

---

## 1. Part A — Glancing transfer: where the superluminal phase meets the lattice at c **[exact]**

The proton trefoil's phase velocity is **not** a single number. With the koppa rung `k(r) = (1/α)√(r/a₀)`:

$$v_{\text{phase}}(r) = \frac{c}{k(r)} \qquad\Rightarrow\qquad \text{superluminal wherever } k<1,\ \text{i.e. } r < r_e$$

| point | r | k(r) | v_phase | glancing angle θ |
|---|---|---|---|---|
| throat (r→0) | 0.01 fm | 0.060 | 16.79c | 86.58° |
| **deep** | 0.55 fm | 0.443 | **2.255c** | 63.68° |
| **R_p surface** | 0.84 fm | 0.546 | **1.831c** | 56.88° |
| c-boundary r_e | 2.82 fm | 1.000 | 1.000c | 0.00° |

(These three velocities — `0.335c` far-field sub-c, `1.831c` at R_p, `2.255c` deep — are Harvey's bracket; they are just `c/k(r)` sampled across the toroid.)

A superluminal phase couples to the lattice (which relays at ≤ c) only where the **projected/glancing component equals c**:

$$v_{\text{phase}}(r)\cos\theta = c \;\Rightarrow\; \boxed{\cos\theta = k(r)} \;\Rightarrow\; \theta_{\text{glance}}(r)=\arccos k(r)$$

So **the proton-surface k is literally the cosine of the glancing angle.** The c-locus is a *curve*, not a point — "a bunch of angles at all different points":

$$\theta_{\text{glance}}: \quad \sim\!86.6^\circ\ (\text{throat}) \;\to\; 56.9^\circ\ (R_p) \;\to\; 0^\circ\ (r_e)$$

**The locus is a separatrix.** Inside it (`θ < θ_glance`, projection > c) the lattice cannot keep up and the deficit **radiates** — that is the wake (APS04's Φ₂, Φ₃). Outside it (`θ > θ_glance`, projection < c) the lattice lags but follows — **entrainment** (orbital drag, the ℓ≥3 channel).

**This derives APS04's angular structure natively.** The (2,3) winding makes 3 toroidal passes per circuit, so it threads `θ_glance(r)` in a **three-fold (C₃)** pattern. The angular distribution of *which arcs sit inside vs outside the c-locus* sets the radiated weight — i.e. the ℓ=2 (polar, equator-vs-pole) and ℓ=3 (C₃) wake terms fall out of the glancing geometry, **with no Legendre polynomial imported**. This closes the APS04 honesty flag: P₂(cosθ) was the *answer*; `cosθ = k(r)` is the *mechanism*.

---

## 2. Part B — Spation rotation, co-dragging, contra-rotation **[mechanism, grounded in FLM03/PPT06]**

What the lattice *does* on the radiating side of the locus:

- **Spation rotation.** Each contact spation is wrenched at `ω_demand = 3c/λ_C = 4.27×10²⁴ rad/s` but can only relay at `ω_max = c/R_p = 3.56×10²³ rad/s` (PPT06). The deficit is the traction; the spation *rotates* to shed it (FLM03, Spation Rotation Kinematic Map).
- **Co-dragging.** A rotating spation drags its contact neighbours (the lattice is contact-only). Rotation propagates outward as the organised wake — the lattice is the *transmission*, co-dragging is how torque crosses it cell to cell.
- **Contra-rotation.** The shell that forms around the nucleon counter-rotates against it (Newton-III in the lattice: the reaction to the trefoil's spin). This is the **dyad** — the electron seated in the nucleon's enmeshed, contra-rotating shell rotation; the Lamb shift is the first break of that mesh (see [[project_foundational_ontology_influx_monopole]]).

No movement is destroyed here — only transformed (the master conservation): linear convergence → spation rotation → co-dragged shell rotation → radiated wake. The question is what *shape* the contra-rotating shell takes, which is Parts C–E.

---

## 3. Part C — The 0.103: frustration of the even packing **[exact]**

The densest *even* (locally-isotropic) way to surround a spation is the icosahedral **12-around-1**. But it is **frustrated**: the 12 outer spations each touch the core, yet **cannot all touch each other**.

With unit spations, the 12 outer centres sit at distance 2 from the core. Their angular arrangement is the icosahedron, whose `edge/circumradius = 4/√(10+2√5) = 1.051462`, so adjacent outer centres are at

$$d_{\text{adj}} = 2 \times 1.051462 = 2.102924 \quad(\text{vs } 2.000 \text{ needed to touch})$$

$$\boxed{\text{frustration gap} = 0.102924 \approx 0.103}$$

That **0.103** is the precise statement of why the locally-densest even packing **cannot tile space**: every shell carries a 0.103-per-radius angular surplus it cannot close. (This is the 2-D cousin of this session's `spation_packing_resonance.html` result — the staggered/icosahedral branch is incommensurate and never recombines.) The lattice must either live with the frustration (amorphous/quasicrystalline) **or** crush it out (Part D).

---

## 4. Part D — Crush the gap → tetrahedral and octahedral voids **[exact geometry]**

Squeezing the 0.103 out forces the even packing to collapse into **close-packing (FCC/HCP)**. Close-packing is not void-free — its interstices are exactly two species:

| void | radius ratio r/R | coordination | count per spation |
|---|---|---|---|
| **tetrahedral** | √(3/2) − 1 = **0.2247** | **4** | 2 |
| **octahedral** | √2 − 1 = **0.4142** | 6 | 1 |

So crushing the frustrated icosahedral shell yields a sublattice of **tetrahedral (4-coordinated, small) and octahedral (6-coordinated, large) holes** — the standard close-packing interstitials, now read as the spation lattice's response to its own frustration.

---

## 5. Part E — Minimum-resistance thread and 1:4 gearing **[DERIVED under Law IV]**

The close-packed alternatives are priced by the same FLM15 lock kernel. For a
void radius `r_v`, each engaged contact costs
`(P_conv/3)V_lock(r_v)`, with `V_lock=8πr_v³/7`:

- Tetrahedral: `q=4`, `r/R=√(3/2)-1=0.224745`.
- Octahedral: `q=6`, `r/R=√2-1=0.414214`.

The octahedral/tetrahedral resistance ratio is `6.2604` for the
seat-volume price and `9.3906` when each of the `q` contacts is counted. Both
registered native prices select the tetrahedral path. The choice is invariant
under scale because both prices scale as `R³`; neither path reads a particle
radius or the W+1 target.

- The **tetrahedral void is the sparsest** interstice (4-coordinated, smallest,
  `r/R=0.225`). Law IV therefore selects it as the minimum reorganisation-cost
  path for the contra-rotating shell.
- That makes the gearing **one-for-four**: each tetrahedral void meshes exactly **4** spations, so the shell gears **1:4** against the lattice. This is the "void geometry as gearing" of [[project_two_regime_and_occlusion_saturation]] made concrete.
- **The 4 is W+1.** The proton is the (2,3) trefoil, W=3, and `R_p = (W+1)·ℏ/(m_p c) = 4ℏ/(m_p c)`. So **W+1 = 4 = tetrahedral coordination = the gearing**. And the PPT06 traction ratio factorises cleanly:

$$\mathcal{T} = 3(W+1) = 12 = \underbrace{3}_{\text{trefoil } C_3} \times \underbrace{4}_{\text{tet gearing} = W{+}1}$$

The **12 = 3 × 4** runs through the entire chain: 3 (the trefoil's three-fold lobes, the C₃ of Part A's wake) × 4 (the tetrahedral void coordination = W+1 = the shell's gearing). The trefoil's topology (3) and the lattice's crushed-void coordination (4) are the two factors of the traction the lattice must carry.

**Scope boundary:** the result uses the framework's minimum-resistance-path
premise. The instrument does not derive that variational premise again. Its
W=1 control counts the 720-degree closure as two `2π` action relays; the W=3
selected seat counts four. The alternate octahedral control gives six and
predicts a proton boundary `49.97%` high.

---

## 6. Status ledger

| part | claim | status |
|---|---|---|
| A | `cosθ = k(r)`; c-locus θ(r)=arccos k(r); separatrix radiate/entrain; native ℓ=2,3 | **RESOLVED — exact geometry** |
| A | closes APS04's borrowed-Legendre flag | **strong** (mechanism shown; full multipole weights not yet integrated) |
| B | spation rotation / co-drag / contra-rotation | **grounded** (FLM03, PPT06) — mechanism, not new number |
| C | 0.103 icosahedral frustration of the even packing | **RESOLVED — exact geometry** |
| D | crush → tet (0.225, 4-coord) + oct (0.414, 6-coord) voids | **RESOLVED — exact geometry** |
| E | minimum-resistance path selects tet thread → 1:4 gearing = W+1; 12=3×4 | **DERIVED under Law-IV path premise**; octahedral control is 9.3906× dearer |

---

## 7. Reproduce

```bash
# MSVC
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:flm07.exe ^
   Investigations\01_Foundations_and_Lattice_Mechanics\CQ52_Glancing_Transfer_and_Void_Gearing\cq52_glancing_void_gearing.cpp && flm07.exe
# GCC/Clang
g++ -std=c++20 -IEngine/include cq52_glancing_void_gearing.cpp -o flm07 && ./flm07
```

Output is `cq52_results.txt`.

---

## 8. Cross-references & forward work

- **[[PPT06]]** — the 1.831c traction demand and T=3(W+1)=12 (this refines it into the glancing locus and factorises the 12).
- **[[APS04]]** — the wake multipoles (this gives the native mechanism under its borrowed P₂).
- **[[FLM03]]** — spation rotation kinematic map (Part B's substrate).
- **[[PPT08A]]** — per-spation rolling mechanics (the co-dragging dynamics).
- **[[PPT09]]** — W=1/W=3 winding stability (grounds the W used in Part E).
- **[[FLM06]]** — spation scale closure + `spation_packing_resonance.html` (the incommensurate-packing tool; the 0.103 is its 3-D cousin).
- `Engine/include/sdt/laws.hpp` — `law_VI::winding`, `law_VI::traction`, `bridge::k_proton_surface`, `measured::{alpha,a_0,R_p,r_e}`.

**Forward work:** (1) integrate the glancing-locus angular distribution over
the full `(2,3)` knot to compute the ℓ=2 / ℓ=3 wake weights; (2) test the
minimum-resistance path on a discrete dynamical lattice rather than the
analytic close-packed seats; (3) carry the selected synchrony kernel into
nuclear contact pricing.

## Trefoil action / sublattice-selection freeze (2026-08-14)

Part E is tested rather than assumed. The target-independent call graph is:

```text
glancing locus + FLM15 lock/resistance kernel
  -> tet/octahedral candidate contact graphs
  -> integrated slip and synchrony resistance for each candidate
  -> minimum-resistance sublattice selected
  -> trefoil action per closed circulation
  -> inferred boundary multiplier
  -> compare with W+1 and measured proton boundary
```

Frozen controls and gates:

1. Parts A–D retain their exact geometric values to relative error `<1e-12`.
2. Tetrahedral and octahedral candidates use the same core, boundary, movement
   and quadrature. No candidate-specific coefficient is allowed.
3. A sublattice is selected only if its integrated resistance is lower across
   every registered orientation and by more than `5` numerical standard
   errors. Otherwise Part E remains `OPEN`.
4. W=1, `(2,3)` W=3, and the alternate sublattice are all run before any
   measured particle radius is loaded.
5. The inferred trefoil action/boundary multiplier must be stable within `1%`
   under doubled filament resolution and `0.5%` under doubled volume
   quadrature. Agreement with `W+1=4` is assessed only afterward at `0.08%`.
6. Deleting the measured proton radius and all benchmark comparison values
   must not alter the selected sublattice or inferred multiplier.

Until all six gates pass, `W+1`, 1:4 gearing and the B18 radius remain
structural hypotheses and cannot feed B22.
