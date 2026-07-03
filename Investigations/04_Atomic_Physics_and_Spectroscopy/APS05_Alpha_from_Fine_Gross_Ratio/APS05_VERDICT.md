# APS05 — VERDICT

**RESOLVED** — α is a directly **measured spectroscopic anchor** (read two independent
ways) with a **native α²-scaling mechanism**. The geometric derivation of α is
deliberately out of scope and remains **OPEN** (E51 / OP-3).

Tool: `aps05_alpha_fine_gross.cpp` (consumes `sdt/laws.hpp`); built MSVC `cl /std:c++20
/EHsc /O2 /utf-8`, ran exit 0; output `aps05_results.txt`. `α` (CODATA) used on a single
comparison line only — delete-test clean.

## Results

| Route | Inputs used | `1/α` | vs CODATA 137.036 |
|---|---|---|---|
| **B — fine/gross ratio** | `Δν_2P`, `cR∞` only (no `m_e`, `e`, `h`) | **136.912** | −0.091% |
| **A — Law V virial** | `E_ion`, `m_e c²` | **137.073** | +0.027% (proton-free seat) |
| `z·k²` at the H rung | — | `1.000000000000` | exact |
| budget defect `1−√(1−α²)` vs `½α²` | — | match | +0.0013% |

## Classification

- **Class A/B — α as a measured anchor (PASS).** Both routes recover `1/α` to ≤ 0.1%
  from spectra; `α` is never an input. α is a measured number, like `m_p/m_e` off a
  mass spectrometer — **not** a fitted free parameter.
- **Class C — native α²-scaling (PASS, correspondence).** The α² that scales fine
  structure is the second-order movement-budget term (`v_circ² + v² = c²`,
  `1 − √(1−α²) = ½α²`), reproduced to 0.0013% with **no** Dirac spin-orbit imported.
  QED reaches the same α² from the same lines for a different stated reason.
- **Class D — geometric derivation of α (PENDING, out of scope).** Both routes
  *extract* α from data; neither *derives* it from lattice geometry.

## The key distinction (why this is not the seed wall)

`α` is **dimensionless**. The FLM06 seed theorem blocks *dimensional* absolutes — a
length (`ℓ_P`) and a mass (`m_e`) cannot be built from dimensionless cosmic arithmetic.
`α` is not blocked by that argument: it is a **legitimate derivation target**, just an
unpaid one (**E51 / OP-3** — "α from the W=1 torus velocity ratio"). The same is true of
`m_p/m_e` (PPT07: measured, `6π⁵` privileged, wake-integral mechanism open). Both
headline numbers now sit symmetrically:

| Number | Measured from | SDT's structural contribution | Geometric derivation |
|---|---|---|---|
| `1/α = 137.0…` | hydrogen fine/gross ratio | α² scaling = movement budget (this work) | OPEN — E51 / OP-3 |
| `m_p/m_e = 1836.15` | mass spectrometry | `6π⁵ = 3·A(S³)·A(S⁵)`, unique to 0.1% (PPT07) | OPEN — wake integral |

Both are real measured anchors; in both, SDT supplies the **structure** and the unpaid
step routes through the same lattice solver.

## Honest residue

- Route B's −0.09% and Route A's +0.03% are real higher-order (QED/Lamb, reduced-mass)
  structure — **not** tuned away.
- 137.07 is the proton-free seat; 137.036 is the infinite-mass idealisation. The
  reduced-mass μ-correction is **not** applied to chase 137.036.
- This investigation does not weaken the standing claim that the elementary unit `e` (dimensional, `[A·s]`)
  (dimensional) is irreducible (EMC02). It sharpens it: it is `e` (a dimension), not `α`
  (a ratio), that the seed wall blocks.
