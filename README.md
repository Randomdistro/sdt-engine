# SDT Engine — Spatial Displacement Theory

**9 Axioms · 17 Theorems · 0 Free Parameters**

One medium. One tick. One budget.

## What Is This?

SDT is a mechanistic theory of physics built on a single postulate: space is a nearest-neighbour relay medium (the spation lattice), and all phenomena emerge from convergent pressure, occlusion, and displacement topology.

This codebase is the **canonical implementation** — the single source of truth for all SDT constants, equations, and derived quantities.

## Quick Start

```bash
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
./build/Release/sdt-benchmarks
```

## Structure

```
sdt-engine/
├── Theory/          # The complete formal framework (read in order 00→11)
├── Engine/          # C++20 header-only library
│   └── include/sdt/
│       ├── laws.hpp          # THE single source of truth
│       ├── state28d.hpp      # 28-dimensional state manifold
│       ├── atomic.hpp        # Rydberg, fine structure, ionisation
│       ├── stellar.hpp       # k-hierarchy, zk²=1, stellar domains
│       ├── galactic.hpp      # Rotation curves (eclipse saturation)
│       ├── nuclear.hpp       # Trefoil geometry, occlusion binding
│       ├── nuclear_occlusion.hpp
│       └── magnetosphere.hpp # Earth + Solar Wind (wake-wake model)
└── Benchmarks/      # B01-B25 validation suite
```

## The Five Laws

| Law | Name | Core Equation |
|-----|------|---------------|
| **I** | Cosmological Relay | Φ = Nε (throughput = shells × content) |
| **II** | Release Cascade | Stars recycle convergence; CMB is the floor |
| **III** | Convergent Boundary | F = (π/4) P_eff R₁²R₂² / r² (all forces) |
| **IV** | Inertial Mass | m = ΦV_disp / (3ℓ_P³c²) |
| **V** | Movement Budget | v_circ² + v² = c² (all of special relativity) |

## Key Results

- **τ = 1/3** — traction fraction is a geometric inevitability of 3D isotropy
- **k_e e² = αℏc** — Coulomb coupling derived, not postulated
- **R_p = 4ℏ/(m_p c)** — proton charge radius from W+1 conjecture (0.02%)
- **Wake tensor** — ℓ=1 is Coulomb, ℓ=2 is magnetic, ℓ≥3 is nuclear form factors
- **Genus-1 torus** — proven minimal persistent topology by elimination

## Prohibitions

This engine does NOT use:
- Quarks, gluons, or Standard Model primitives
- G or M as fundamental constants (derived from k-hierarchy)
- Dark matter or dark energy
- Probabilistic wavefunctions
- Fields as ontological primitives

## Author

**James Tyndall** — Melbourne, Australia  
March 2026

## License

All rights reserved. Contact author for permissions.
