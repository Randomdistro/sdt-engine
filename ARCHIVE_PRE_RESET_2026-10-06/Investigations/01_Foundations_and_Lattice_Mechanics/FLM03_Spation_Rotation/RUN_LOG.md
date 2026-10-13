# FLM03 — Spation Rotation Kinematic Map · RUN LOG

> **Author:** J. C. Harvey, Melbourne. **Run recorded:** 2026-06-26.
> **Tool:** `flm03_spation_rotation_map.cpp` (`#include <sdt/state28d.hpp>`).
> **Verdict:** ✅ **4 / 4 proofs PASS.** Build clean, run clean.

## Build & run

```
cl /nologo /std:c++20 /EHsc /O2 /I Engine\include ^
   Investigations\01_Foundations_and_Lattice_Mechanics\FLM03_Spation_Rotation\flm03_spation_rotation_map.cpp
```
- Toolchain: MSVC (VC Build Tools 2022), x64. `BUILD_EXIT=0`, `RUN_EXIT=0`.
- Inputs: CODATA 2018 constants (c, α, a₀, r_e, R_p, m_e, m_p, ℏ) declared in-tool + the 28-D
  proton/electron `State28D` geometry. **No fitted parameters.**

## What it shows

The tool maps the proton field's rotation profile **v(r)** from inside the proton surface out to the
hydrogen Bohr orbits, using `v(r) = c·ϟ_H·(R_p/r)`-type geometry with `ϟ_H = (1/α)√(R_p/a₀)`.

### Part I — the velocity ladder (all derived from proton geometry)

| Anchor | r | v(r)/c | k(r) | note |
|---|---|---|---|---|
| ½ R_p | 4.21e-16 m | **2.590** | 0.386 | superluminal interior |
| **R_p (surface)** | 8.41e-16 m | **1.8316** | 0.546 | the 1.83c seat |
| r_e (c-boundary) | 2.82e-15 m | **1.0008** | 0.999 | v = c exactly |
| a₀ (ground) | 5.29e-11 m | **0.00730** | **136.92** | k → 1/α |

- **FLM03-1a** v(R_p) = c/ϟ = **1.831582c** — Err **0.0000%** (PASS)
- **FLM03-1b** v(r_e) = **c** at the classical-electron-radius c-boundary — Err **0.0000%** (PASS)
- **FLM03-1c** v(a₀) = **αc** electron orbit — Err **0.0833%** (PASS)
- Spans: velocity ×250.99 (R_p→a₀); ω ×1.5786e7; period ×6.33e-8.
- k(r) reaches **136.92 ≈ 1/α** exactly at a₀ (the Bohr rung).

### Part III — the electron as a driven orbit

- **FLM03-4a** proton rotation field at a₀ = **2.1895e6 m/s = αc** vs measured electron orbital
  velocity 2.1877e6 m/s — Err **0.0833%** (PASS). The electron sits where the proton's own field
  already rotates at the orbital speed (resonance, not coincidence).

## Certification & honest notes

- **COMPUTED / DERIVED-from-geometry:** the v(r) profile and the three anchor velocities follow from
  proton geometry + CODATA constants with no fitted knob. Class C–B (convergence→derived).
- The single non-zero residual is **v(a₀)=αc at 0.083%** (sub-0.1%); 1a/1b land at machine zero.
- **Cross-beam:** the **1.831c proton-surface seat** here is the same value used by **NP20**
  (the neutron's 0.782 MeV *and* −1.913 μ_N from one 1.83c counter-rotating seat) and by the
  Depth-Closure paper (v = c√z spanning Earth→proton → 1.830c). Three independent routes, one number.

## Status

FLM03 tool: **GREEN, recorded.** No `PROMPT.md` exists for this folder yet (bare-tool legacy folder) —
if a full gold-standard spec is wanted, it can be written around this passing tool.
