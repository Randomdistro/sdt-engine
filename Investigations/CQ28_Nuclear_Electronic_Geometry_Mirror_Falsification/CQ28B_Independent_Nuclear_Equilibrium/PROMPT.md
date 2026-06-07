# CQ28B — Independent Nuclear Equilibrium *(positions, ELECTRON-BLIND)*

**Purpose.** Produce 3-D nuclear block positions from grammar + packing equilibrium **only** — zero electron input. This is the substrate the whole mirror test rests on; its electron-blindness is the *non-circularity guarantee*.

**Inputs.** `(n_d, n_t)` block count from CQ28A **only**.
**Outputs.** Per isotope: solved 3-D positions of the `n_d+n_t` blocks around the α-core, the achieved `θ_min`, the kissing radius, and a determinism hash.

**Method.** Tammes/Thomson relaxation (max-min angular separation) of `N = n_d+n_t` points on the sphere; kissing radius `r = sin(θ_min/2)/(1−sin(θ_min/2))`. Must reproduce `packing.hpp` presets as **emergent** equilibria: `N=4→109.47° (tetra)`, `6→90° (octa)`, `8→antiprism`, `12→icosa`. Tritons take the maximally-separated sites.

**HARD BAN (the whole point).**
```
NO SUBSHELLS, NO Aufbau order, NO electron-shell radius, NO 2n².
Any electron-ordered placement must be named contaminated_visual_mockup_only()
and is barred from this stage.
```

**Fixed metrics.** (i) convergence to Thomson minimum (energy plateau); (ii) `θ_min` within <2% of `packing.hpp`/known Tammes values; (iii) **determinism** — fixed seed ⇒ identical hash; (iv) zero electron quantities in any dependency.

**Null model (carried to CQ28E).** Random sphere placement with **no** relaxation — the baseline geometry the real mirror score must beat.

**Failure criteria.** Any position depends on an electron quantity; non-deterministic output; divergence from `packing.hpp` presets; tritons not maximally separated.

**Reuses.** `packing.hpp` (Tammes/kissing/min-angular-pair), the verified equilibrium solver. **Provenance:** class **B** (SDT-derived, internal-only, electron-blind by construction).
