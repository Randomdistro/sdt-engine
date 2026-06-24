# FLM07 — Verdict

**Question:** Where does the trefoil's superluminal phase couple to the lattice; what does the lattice do (spation rotation, co-drag, contra-rotation); and what packing/void geometry does the contra-rotating shell ride?

**Verdict:** **RESOLVED [exact geometry] for Parts A–C/D; STRONG conjecture for Part E.**

**The chain (one factorisation runs through it: 12 = 3 × 4):**

1. **Glancing transfer (A) — exact.** `v_phase(r) = c/k(r)` is superluminal inside r_e; it relays cleanly only where `cosθ = k(r)`. The c-locus `θ(r) = arccos k(r)` sweeps **86.6° (throat) → 56.9° (R_p) → 0° (r_e)** — a continuum, not a point. It separates the **radiating** wake (super-c side → APS04's Φ₂, Φ₃) from **entrainment** (sub-c side → orbital drag). The (2,3) winding threads it 3-fold → the ℓ=2/ℓ=3 wake **without borrowing Legendre P₂** (closes the APS04 flag). Harvey's `0.335/1.831/2.255c` are just `c/k(r)` sampled across the toroid.

2. **Lattice response (B) — grounded.** The traction wrenches contact spations into rotation (FLM03), which co-drag their neighbours, producing a contra-rotating shell (the dyad). Movement conserved, only transformed.

3. **Frustration (C) — exact.** The densest *even* packing, icosahedral 12-around-1, leaves a **0.103** gap (edge/circumradius = 1.05146 → adjacent outer spations at 2.103 vs 2.000 to touch). The 12 touch the core, not each other — the locally-densest even packing cannot tile.

4. **Crush → voids (D) — exact.** Squeezing out the 0.103 forces close-packing, whose interstices are **tetrahedral (r/R = 0.225, 4-coordinated)** and **octahedral (r/R = 0.414, 6-coordinated)** voids (2 tet + 1 oct per spation).

5. **Void gearing (E) — STRONG conjecture.** The contra-rotating shell threads the **sparsest (tetrahedral, 4-coordinated)** voids → carries the **least spations** → gears **one-for-four**. And **4 = W+1** (R_p = (W+1)ℏ/m_p c), so the PPT06 traction ratio factorises: **T = 3(W+1) = 12 = (trefoil C₃ = 3) × (tet gearing = W+1 = 4)**. The integers align exactly; that the physical shell *is* the tet-void thread is asserted, not proven.

**Honest seam:** A–D are exact geometry / grounded mechanism. E rests on integer coincidences (4 = W+1 = tetrahedral coordination; 12 = 3×4) — strong circumstantial support, not a derivation. Forward work: integrate the glancing locus to recover the wake weights natively, and prove the minimum-drag shell selects the tetrahedral sublattice.

**Artifacts:** `cq52_glancing_void_gearing.cpp`, `cq52_results.txt` (compiles + runs, exit 0), `INVESTIGATION.md`.

*J. C. Harvey, Melbourne, 2026-06-20.*
