# FLM07 — Verdict

**Question:** Where does the trefoil's superluminal phase couple to the lattice; what does the lattice do (spation rotation, co-drag, contra-rotation); and what packing/void geometry does the contra-rotating shell ride?

**Verdict:** **A–D geometry DERIVED; tetrahedral thread selected by the
Law-IV minimum-resistance test.**

**The chain (one factorisation runs through it: 12 = 3 × 4):**

1. **Glancing transfer (A) — exact.** `v_phase(r) = c/k(r)` is superluminal inside r_e; it relays cleanly only where `cosθ = k(r)`. The c-locus `θ(r) = arccos k(r)` sweeps **86.6° (throat) → 56.9° (R_p) → 0° (r_e)** — a continuum, not a point. It separates the **radiating** wake (super-c side → APS04's Φ₂, Φ₃) from **entrainment** (sub-c side → orbital drag). The (2,3) winding threads it 3-fold → the ℓ=2/ℓ=3 wake **without borrowing Legendre P₂** (closes the APS04 flag). Harvey's `0.335/1.831/2.255c` are just `c/k(r)` sampled across the toroid.

2. **Lattice response (B) — grounded.** The traction wrenches contact spations into rotation (FLM03), which co-drag their neighbours, producing a contra-rotating shell (the dyad). Movement conserved, only transformed.

3. **Frustration (C) — exact.** The densest *even* packing, icosahedral 12-around-1, leaves a **0.103** gap (edge/circumradius = 1.05146 → adjacent outer spations at 2.103 vs 2.000 to touch). The 12 touch the core, not each other — the locally-densest even packing cannot tile.

4. **Crush → voids (D) — exact.** Squeezing out the 0.103 forces close-packing, whose interstices are **tetrahedral (r/R = 0.225, 4-coordinated)** and **octahedral (r/R = 0.414, 6-coordinated)** voids (2 tet + 1 oct per spation).

5. **Void gearing (E) — derived under Law IV's path premise.** The same
FLM15 engaged-volume kernel prices both close-packed paths. The octahedral
seat is `6.2604×` dearer by seat volume and `9.3906×` dearer when contacts are
counted, so both native routes select the **tetrahedral, 4-coordinate** thread
before a particle radius is loaded. Four action relays give
`R=4ℏ/(m_pc)=0.841236 fm`, `−0.0195%` from the measured boundary; the
octahedral control gives `1.261853 fm`, `+49.97%`.

**Scope:** selection uses the framework's minimum-reorganisation-resistance
premise; the instrument does not independently derive that premise. The W=1
control is the 720-degree closure's two action relays. The remaining work is a
discrete dynamical-lattice test and full glancing-weight integration, not a
choice between tetrahedral and octahedral seats.

**Artifacts:** `flm07_glancing_void_gearing.cpp` (MSVC C++20, exit 0),
`INVESTIGATION.md`, and the FLM15 R4 tests (11/11).

*James Christopher Tyndall, Melbourne, updated 2026-08-14.*
