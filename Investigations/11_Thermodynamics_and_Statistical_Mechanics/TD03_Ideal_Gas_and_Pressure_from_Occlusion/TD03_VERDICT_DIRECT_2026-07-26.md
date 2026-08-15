# TD03 — Ideal-Gas Pressure and Rank-4 Lattice Assessment

> **Author:** James Christopher Tyndall, Melbourne. **Executed:** 2026-07-26;
> B37 protocol verification 2026-08-15. **Tool:** `td03_pressure_occlusion.cpp`.

## Prompt contraband check

**CLEAN — model discipline.** The tool pre-discloses its own identity trap (with entropic T,
axis-mean PV/(NkT) ≡ 1 cannot fail → NOT gated) and gates per-axis isotropy instead. The
virial/Mayer link for the co-volume is flagged BORROWED, claims capped at sign + order.

## Executed results

- **P1a:** the 1/3 emerges from bath isotropy by event-counted wall impulses (0.336 vs 1/3 at
  0.7σ) — not inserted.
- **P1b (the native jewel):** the FLM08 tetrahedral bond set (W+1 = 4 coordination) is a
  **spherical 2-design**: ⟨(b·n)²⟩ = 1/3 for ANY wall normal to 3.9e-16 — the pressure 1/3 is
  *protected* by lattice symmetry. **The lattice fingerprint is pushed to rank 4:** ⟨(b·n)⁴⟩
  spans [1/9, 7/27] vs continuum 1/5 — a real, falsifiable SDT-distinct prediction living in
  fourth-moment observables. **Flagged here as an experimental hook.**
- **P2:** per-axis isotropy inside the 4σ gate across N and T; PV = NkT inherited as
  CONVERGENCE from TD02, labelled so.
- **P3:** Dalton additivity exact; co-volume b = 4× particle volume to 0.01%, b > 0 (hard-vortex
  exclusion → repulsive first correction — sign and order claimed, nothing more).

## Verdict

- **Prompt completion: A** · **Physics class: CONVERGENCE (Class C)** for PV = NkT (inherited
  route), **plus one NATIVE protected result** (1/3 from the W+1 = 4 two-design) **and one live
  SDT-distinct prediction** (rank-4 anisotropy band) with a populated failure class.
- **Recovery:** n/a · **Cascade root:** none.

## B37 deterministic protocol verification — 2026-08-15

The rank-4 reducer is now canonical in
`sdt::laws::lock_geometry::rank4`. The exact unit-direction form is

```text
M4(n) = [1 + 4(nx^2 ny^2 + nx^2 nz^2 + ny^2 nz^2)]/9.
```

The direct channel sum and this analytic form agree to `3.89×10^-16`
over a deterministic 100,000-direction Fibonacci sphere. The protected
second moment remains `1/3` to `2.78×10^-16`. Exact endpoint evaluations
give:

- axis `[100]`: `M4=1/9=0.111111111`;
- tetrahedral/body diagonal `[111]`: `M4=7/27=0.259259259`;
- isotropic control: `M2=0.333333333`, `M4=0.200000000`.

The tool emits the machine-readable `B37_PREDICTION_JSON` record with
`measurement:null`. The apparatus protocol requires at least 1,000 surveyed
drive directions, an isotropic control within `0.005`, propagated direction
covariance, and two-sigma overlap with both predicted extrema while excluding
the continuum at those extrema.

**B37 remains PENDING and outside the benchmark tally.** The derivation and
reduction protocol pass; no physical response corpus has yet been measured.
