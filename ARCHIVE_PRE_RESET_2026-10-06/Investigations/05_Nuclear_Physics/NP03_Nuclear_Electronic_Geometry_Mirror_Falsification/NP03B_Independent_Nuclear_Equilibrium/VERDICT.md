# NP03B — VERDICT

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (agent executor).
> **Tool:** `np03b_equilibrium.cpp` → `np03b.exe` (MSVC 19.44, build exit 0, run exit 0, 35 s).
> Real stdout: `np03b_results.txt`. Positions: `np03b_positions.txt` (frozen input to NP03C).

## Dual verdict

- **Prompt completion: A** — solver built, presets emerge, determinism proven, null baselines
  recorded, triton assignment deterministic, positions file emitted.
- **Physics class: B-substrate (internal, electron-blind by construction).** The positions are
  not a prediction and are not sold as one; they are the non-circularity guarantee the mirror
  test (NP03E) rests on. The `packing.hpp` presets *emerge* from grammar counts + maximin
  equilibrium with zero electron input — that is the whole deliverable.

## Key numbers

| Gate | Committed | Result |
| --- | --- | --- |
| P0 sanity N=2 / N=3 | < 0.5% | 180.0000° / 120.0000° — 0.000% PASS |
| P1 N=4 tetrahedron | < 2% of 109.4712° | 109.4712° (0.000%) PASS |
| P1 N=6 octahedron | < 2% of 90° | 90.0000° (0.000%) PASS |
| P1 N=8 sq. antiprism | < 2% of 74.8585° | 73.5337° (1.770%) PASS — near-optimal basin, noted |
| P1 N=12 icosahedron | < 2% of 63.4349° | 63.4349° (0.000%) PASS |
| P2 determinism | identical hash | 4/4 IDENTICAL (e.g. `be3519c61e94a831`) |
| P4 vs random null | solved ≥ null | 5/5 demo cases (O-16: 90.0° vs 2.1°) |
| P5 tritons (Fe-56) | max-min subset | 86.42° triton min-angle vs 43.01° block θ_min |

## Honesty notes

- N=8 is the weakest reproduction (1.77%): the fixed-seed relaxation lands in a square-antiprism
  basin slightly short of the Tammes optimum. Inside the pre-committed gate; not retro-tightened,
  not retro-widened, not claimed exact.
- Solver hyper-parameters (seeds 11–97, exponent schedule 2→12, iteration counts) are numerics,
  fixed before the run and logged; the maximin objective itself is parameter-free.
- Kissing radius diverges (inf) at N=2 (antipodal, sin(θ/2)=1) — degenerate case, reported as-is.

## Files

- `np03b_equilibrium.cpp`, `np03b.exe`, `np03b_results.txt`, `np03b_positions.txt`
  (7 demo isotopes: He-4, Li-7, C-12, O-16, Ne-20, Si-28, Fe-56), `RUN_LOG.md`.

---

## SUPERSESSION (same day, on Harvey's direction) — NP17 is the death knell

NP17 (RESOLVED, deuteron to 1.1% with no fitted scale) establishes the actual packing order:
**interleaved 6π trefoils, neutron = proton + internal electron, that electron SHARED between
adjacent protons — the shared-electron well IS the binding.** NP03B's structural model —
blocks as mutually-avoiding spheres at Tammes kissing radii around a central core — is the
**failed branch**. It executed cleanly, and its mathematics (the maximin solver, the emergent
presets, the determinism proof, the random-null baselines) survives as machinery and as
NP03E null-model generators. But as a model of nuclear structure it is **KILLED by NP17**:
nucleons interleave and share electron nodes (deuteron p–p spacing 2R_p + R_p/3); they do not
sit apart on shells. Any NP03E mirror test must generate its nuclear geometry from the NP17
imported geometry (`NUCLEAR_PACKING_STRUCTURE_AND_DATA.md` / `trefoil_mappings.json`), not
from this stage's positions.

**Prompt completion A (as spec'd) · Physics class: solver machinery earned; structural model KILLED (superseded by NP17) · Recovery PARTIAL (route: regenerate positions from NP17 interleaved geometry) · Cascade root NP17-packing-order (shared with NP03C, NP03D)**
