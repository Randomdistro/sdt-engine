# FLM07 — Glancing Transfer, the 0.103 Frustration, and Void Gearing of the Contra-Rotating Shell

> **Author:** James Christopher Harvey, Melbourne. 2026-06-20.
> **Status:** OPEN → Parts A–C **RESOLVED [geometry, exact]**; Parts D–E **[STRONG conjecture, numbers align, not proven]**.
> **Tool:** `cq52_glancing_void_gearing.cpp` (consumes `Engine/include/sdt/laws.hpp`; output `cq52_results.txt`).
> **Honesty contract:** the glancing-transfer geometry (A), the 0.103 even-packing frustration (B/C) and the tetrahedral/octahedral void ratios (D) are **pure geometry — exact, delete-test clean**. The *identification* of the physical contra-rotating shell with the tetrahedral-void sublattice, and the resulting **1:4 gearing**, is a **structural conjecture**: every integer lines up (4 = W+1 = tetrahedral coordination; 12 = 3×4 = the PPT06 traction ratio), but "the shell **is** the tet-void thread" is asserted, not derived. Labelled as such throughout.

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

## 5. Part E — The contra-rotating shell as the tet-void thread: least spations, 1:4 gearing **[STRONG conjecture]**

Here is the seam (clearly conjectural — the numbers align, the identification is asserted):

- The **tetrahedral void is the sparsest** interstice (4-coordinated, smallest, `r/R=0.225`). A shell that wants to rotate against the nucleon with **minimum drag** threads the **fewest spations** — i.e. it rides the tetrahedral-void sublattice. So the **contra-rotating shell naturally possesses the least amount of spations** (Harvey's phrase), by sitting in the 4-coordinated holes rather than the 6-coordinated ones.
- That makes the gearing **one-for-four**: each tetrahedral void meshes exactly **4** spations, so the shell gears **1:4** against the lattice. This is the "void geometry as gearing" of [[project_two_regime_and_occlusion_saturation]] made concrete.
- **The 4 is W+1.** The proton is the (2,3) trefoil, W=3, and `R_p = (W+1)·ℏ/(m_p c) = 4ℏ/(m_p c)`. So **W+1 = 4 = tetrahedral coordination = the gearing**. And the PPT06 traction ratio factorises cleanly:

$$\mathcal{T} = 3(W+1) = 12 = \underbrace{3}_{\text{trefoil } C_3} \times \underbrace{4}_{\text{tet gearing} = W{+}1}$$

The **12 = 3 × 4** runs through the entire chain: 3 (the trefoil's three-fold lobes, the C₃ of Part A's wake) × 4 (the tetrahedral void coordination = W+1 = the shell's gearing). The trefoil's topology (3) and the lattice's crushed-void coordination (4) are the two factors of the traction the lattice must carry.

**What is NOT proven:** that the physical contra-rotating shell *is* the tet-void thread (vs the oct-void, or a mix), and that the gearing is exactly 1:4 rather than, say, the 1:3 of the C₃ or the 1:2 of the tet:oct count. The integer coincidences (4 = W+1 = tet coordination; 12 = 3×4) are strong circumstantial support, not a derivation. Promoting Part E from conjecture to result is the forward work (see §8).

---

## 6. Honest status ledger

| part | claim | status |
|---|---|---|
| A | `cosθ = k(r)`; c-locus θ(r)=arccos k(r); separatrix radiate/entrain; native ℓ=2,3 | **RESOLVED — exact geometry** |
| A | closes APS04's borrowed-Legendre flag | **strong** (mechanism shown; full multipole weights not yet integrated) |
| B | spation rotation / co-drag / contra-rotation | **grounded** (FLM03, PPT06) — mechanism, not new number |
| C | 0.103 icosahedral frustration of the even packing | **RESOLVED — exact geometry** |
| D | crush → tet (0.225, 4-coord) + oct (0.414, 6-coord) voids | **RESOLVED — exact geometry** |
| E | contra-rotating shell = tet-void thread → least spations, 1:4 gearing = W+1; 12=3×4 | **STRONG conjecture** (integers align; identification asserted) |

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

**Forward work (to promote Part E):** (1) integrate the glancing-locus angular distribution over the (2,3) knot and show the ℓ=2 / ℓ=3 wake weights drop out, replacing APS04's P₂; (2) prove (or refute) that the minimum-drag contra-rotating shell selects the tetrahedral-void sublattice specifically, fixing the 1:4 gearing; (3) check whether the `gear_ratio_nuclear_atomic` (laws.hpp) or any measured shell ratio carries the factor 4 = W+1.
