# CM07 — Ferromagnetism as Aligned Vortex Wakes

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

## Question

A ferromagnet is, in SDT, a region where the **wake circulations of many vortices are co-aligned**:
the same handedness ([[project_cq47_repulsion_inverse]]) repeated across a domain so their
circulations add into a macroscopic net wake. **Can spontaneous magnetisation, the Curie
temperature `T_C`, domains, and the hysteresis loop be reproduced from aligned wake circulation —
the "exchange interaction" being the energy cost of neighbouring wakes co-rotating vs opposing —
with everything quoted in native wake-circulation units and NOT a single Bohr magneton?** The
no-magnetons rule is absolute here ([[feedback_no_borrowed_units]]): magnetisation is a count of
aligned wakes × the electron's own wake circulation, never `μ_B`.

## SDT mechanism & hypotheses

Each W=1 vortex carries a handed wake (EMC03). When neighbours co-rotate, their wakes reinforce
(lower combined occlusion) → an alignment-favouring "exchange" energy `J`. Thermal disorder (CM04)
randomises alignment; above `T_C` it wins. Domains form because a uniformly aligned bulk pays a
long-range wake-field cost — splitting into domains lowers it. Hysteresis is the irreversibility of
unpinning domain walls (occlusion-pinned at defects).

- **H1 (exchange = co-rotation energy):** alignment energy `J` = wake reinforcement of co-rotating
  neighbours; sign of `J` (ferro vs antiferro) = whether co- or contra-rotation lowers occlusion.
- **H2 (Curie point):** `k_B T_C ≈ z J` (z = coordination) — thermal disorder beats wake alignment;
  predict `T_C` ordering for Fe/Co/Ni and `M(T) → 0` at `T_C` (mean-field exponent ½ near T_C).
- **H3 (native magneton):** the moment quantum is the electron's **own wake circulation** (koppa /
  `r_e` scale), and `M` is an integer count of aligned wakes — expressed natively, never in `μ_B`.

## Strategy

**Phase 1 — Exchange energy.** *Goal:* derive `J` from wake co-rotation. *Method:* occlusion of two
neighbouring co- vs contra-rotating wakes (EMC03 handedness). *Success:* `J > 0` (alignment favoured)
for Fe/Co/Ni; sign flip gives antiferro.

**Phase 2 — Curie temperature.** *Goal:* `T_C`. *Method:* alignment energy vs CM04 thermal disorder
(mean field). *Success:* `T_C` ordering Fe/Co/Ni correct; magnitudes within 2×.

**Phase 3 — Spontaneous M(T).** *Goal:* `M(T)`. *Method:* self-consistent alignment fraction.
*Success:* `M(T) → 0` at `T_C`; native-unit magnetisation curve (no magnetons anywhere).

**Phase 4 — Domains + hysteresis.** *Goal:* loop shape. *Method:* domain-wall pinning at occlusion
defects; unpinning threshold = coercive field. *Success:* hysteresis loop with finite coercivity;
remanence; domains as wake-field minimisers.

## Success criteria

- ✅ **PASS (A):** `J`, `T_C` ordering, `M(T)`, and a native-unit hysteresis loop, zero fits, zero magnetons.
- ✅ **QUALIFIED (C):** exchange + `M(T)` derived; `T_C` magnitude CALIBRATED(1). *(Expected.)*
- ⚠️ **PENDING (D):** alignment + Curie point shown; hysteresis only qualitative.
- ❌ **FAIL (F):** cannot get spontaneous M / `T_C` without importing spin operators — **or** any
  result is quotable only in magnetons (automatic FAIL on the units rule).

## Falsification tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | exchange = wake co-rotation | `J>0` for Fe/Co/Ni; antiferro sign flip | alignment not occlusion-set |
| T2 | `k_B T_C ≈ zJ` | Fe/Co/Ni `T_C` ordering; M→0 at T_C | Curie point not disorder threshold |
| T3 | moment = native wake circulation | `M` expressible without any μ_B | the moment is an irreducible magneton |

## Dependencies

**Upstream:** [[CM01]] (wake locking), EMC03 (handedness ± → wake sign), Law VI (wake circulation,
traction), CM04 (thermal disorder vs alignment). **Downstream:** magnetism suite
(14_Plasma_and_Magnetism); domain physics. **Related:** [[feedback_no_borrowed_units]] (absolute:
native wake-circulation units, NO magnetons); APS04 (angular/wake structure).
