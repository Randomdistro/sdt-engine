# De Rerum Todo Existens
### *Of All Things That Exist* — the foundational treatise of Spatial Displacement Theory

> **Author:** James Christopher Harvey, Melbourne. 2026.
> **Status:** canonical treatise, regenerated against the SDT-Engine (`Engine/include/sdt/laws.hpp`).
> This is a ground-up rewrite of the original *De Rerum Todo Existens* (the multi-volume Latin-titled
> treatise core of the prior SDT canon). Every number in every book is emitted by one tool —
> [`de_rerum.cpp`](de_rerum.cpp) — which `#include`s the engine and prints each keystone quantity with
> a PASS/FAIL against measurement. The prose **quotes the tool**; nothing is hand-typed. Re-run the
> tool after any change to `laws.hpp` and the treatise re-syncs mechanically.

---

## What this treatise is

SDT is a **zero-free-parameter** physics framework. It begins by naming what exists and refusing what
does not, and from that geometry it rebuilds the constants and forces of physics without importing the
machinery of the standard models. *De Rerum Todo Existens* is the canonical statement of that
construction: foundations first, then each domain in turn, each grounded in the same engine.

The treatise carries an **honesty contract**. Every result wears a certification class (below). Some
of SDT's most-quoted lines are flagged **F** — they are *true* but not *earned* (an identity, not a
derivation). Those flags are kept in the open. The standard of the document is: **a number can be
right and still not be earned.**

## The four primitives

| # | Primitive | Definition (geometry, not metaphor) |
|---|-----------|-------------------------------------|
| 1 | **Space** (the *matrix*) | An incompressible discrete medium of **spations**; supports pressure propagation at `c`. |
| 2 | **Matter** (a *boundary*) | Displacement geometry that excludes matrix volume — a hole in the medium, not a substance in it. |
| 3 | **Movement** | Structured flow and shunt dynamics; the class of all change. |
| 4 | **Now** | The ordering of change as oscillation count. Time is *counted*, not *contained*. |

Everything else — force, charge, mass, energy, entropy, the constants — is a **structured response of
the matrix** to occlusion (shadowing of the convergence) and circulation (vortex topology).

## The only permitted inputs (the whitelist)

```
{ l_P, c, hbar, k_B, T_CMB, alpha, m_e, m_p }   + measured observables in measured units
```

`alpha` is the single irreducible coupling. In SDT it is read as the **hydrogen koppa-rung**
(χ = c/v = 137.036 at the ground state), not as `k_e e²/ℏc`. The model **does not derive α** and says
so wherever α enters.

## The prohibitions (forbidden inputs)

No **G** and no **M** as fundamentals (gravity is `g = v²/R`, `koppa = v²R/c²`). No quantum
wavefunctions, no fields as primitives, no dark matter/energy, no ΛCDM, no quarks/gluons, no
wave–particle duality, **no charge** as a substance, **no monopoles**. These are not "unsupported" —
they are *prohibited*, and the treatise must reconstruct their observable consequences without them.

## The Six Laws (the spine)

- **Law I** — Cosmological relay throughput: the CMB convergence `Φ = N·ε`, `P_conv`.
- **Law II** — Release cascade: radiative pressure origin, pressure domains.
- **Law III** — Convergent boundary pressure: the **one force law** `F = (π/4) P_eff R₁² R₂² / r²`
  (Coulomb, gravity, nuclear binding are one mechanism at three scales).
- **Law IV** — Inertial mass as throughput-reorganisation cost.
- **Law V** — Movement budget `v_circ² + v² = c²` (special relativity, no postulate).
- **Law VI** — Vortex topology quantisation (W=1 electron, W=3 proton trefoil; T18).

## The books

| Book | Title | Covers |
|------|-------|--------|
| **I** | [Foundations](Book_I_Foundations.md) | The four primitives, the master relay, the movement budget, mass, the eliminations. |
| **II** | [Atomic & Nuclear Architecture](Book_II_Atomic_and_Nuclear.md) | The electropause (P_eff closure), spectra from one rotation field, the trefoil proton, 6π⁵, the Atomicus construction grammar. |
| **III** | [Electromagnetism & Magnetism](Book_III_Electromagnetism_and_Magnetism.md) | There is no charge; Coulomb *is* occlusion; repulsion = inverse convergence; the trefoil multipole; magnetic moments. |
| **IV** | [Gravitation & Stellar Structure](Book_IV_Gravitation_and_Stellar.md) | The koppa ladder, gravity without G/M, Depth-Closure, c from precession, gravitational waves, the lumiopause. |
| **V** | [Cosmology & the Relay](Book_V_Cosmology_and_the_Relay.md) | The relay sets the constants, redshift = octaves (no expansion), the absolute relay ceiling, scale closure. |

## Regenerate every number

```bash
# MSVC
cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include /Fe:de_rerum.exe \
   Papers\De_Rerum_Todo_Existens\de_rerum.cpp && de_rerum.exe
# GCC/Clang
g++ -std=c++20 -IEngine/include \
   Papers/De_Rerum_Todo_Existens/de_rerum.cpp -o de_rerum && ./de_rerum
```

Output is captured in [`de_rerum_results.txt`](de_rerum_results.txt). Current run: **19 numeric
checks PASS / 0 FAIL**, plus one class-**F** identity that matches numerically but is flagged as
un-earned.

## Certification classes (the honesty key)

| Class | Meaning |
|-------|---------|
| **A** | Analytic / exact (topology, identities forced by geometry). |
| **B** | Derived from the whitelist; passes its delete-test. |
| **C** | Derived **on framework terms** (sound given SDT's reading of α as the koppa-rung). |
| **D** | A measured correlation / computed trend (not a closure). |
| **F** | **Fails the delete-test** — true but not earned (an identity, or a calibrated coefficient). Kept in the open. |

---

*Spatial Displacement Theory · De Rerum Todo Existens · J. C. Harvey, Melbourne.*
