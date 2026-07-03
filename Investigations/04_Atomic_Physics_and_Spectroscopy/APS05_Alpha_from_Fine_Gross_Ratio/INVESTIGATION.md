# APS05 — The Fine-Structure Constant as a Measured Spectroscopic Anchor

> **Domain**: 04 — Atomic Physics & Spectroscopy
> **Status**: RESOLVED (measured-anchor + native α²-scaling) · geometric derivation left OPEN (E51/OP-3)
> **Author**: J. C. Harvey, Melbourne
> *(Written to the `Investigations/PERFECT_PROMPT_TEMPLATE.md` gold-standard structure.)*

---

## 1. Executive Summary

A standing criticism of SDT is that `α ≈ 1/137` is "a free parameter pulled from
nowhere." **It is not — it is a directly measured anchor, read straight off the
hydrogen spectrum, exactly as `m_p/m_e` is read off a mass spectrometer.** This
investigation reads `α` two independent ways from real spectroscopic data — once as
the pure *fine-to-gross structure ratio* (`α²`, no `m_e`, `e`, or `h` required), once
as the *ground-state rung velocity* `v = αc` (Law V) — and shows both land on 137 to
~0.1%. It also supplies the part that is genuinely SDT's: **why `α²` is the scale of
fine structure at all.** QED says spin-orbit coupling; SDT says it is the
second-order term of the movement budget `v_circ² + v² = c²`. Same `α²`, same lines,
native mechanism. **What this does NOT do** is derive `α` from lattice geometry — but
because `α` is *dimensionless*, it is not blocked by the FLM06 seed wall the way
`ℓ_P` and `m_e` are; it is a legitimate, still-unpaid derivation target (E51 / OP-3).

## 2. Physical Context

The fine-structure constant got its name for a literal reason: **`α²` is the ratio of
a spectrum's *fine* structure (the small splittings of lines) to its *gross* structure
(the main Rydberg energy levels).** That is not an interpretation; it is what the
quantity *measures*.

The key observables (all measured, no theory imported):

| Symbol | Meaning | Value |
|---|---|---|
| `Δν_2P` | H `2P_3/2 − 2P_1/2` fine-structure splitting | `10 969.13 MHz` |
| `cR∞` | Rydberg frequency (gross-structure scale) | `3.289 842 × 10¹⁵ Hz` |
| `E_ion` | H ionisation energy (Lyman limit) | `13.598 434 eV` |
| `m_e c²` | electron rest energy | `510 998.95 eV` |

The SDT picture (from **PPT02**): the hydrogen electron rides the `k = 137` rung of
the koppa ladder at speed `v = αc`; `α` is simply the `v/c` of that rung, the same
kind of object as the Sun's `k = 686`. Fine structure is then the *second-order*
correction in the movement budget — the `(v/c)² = α²` term. This investigation makes
that concrete and falsifiable: it pins `α` to data and gives the budget reason for the
`α²` scaling, with no Dirac equation and no spin-orbit operator.

Why it matters: it converts a recurring "you fitted `α`" objection into a checkable
statement — `α` is a measured anchor, and the framework's job is the *structure*
(why `α²`), not the *fitting* (there is none).

## 3. Theoretical Framework

**Axioms / first principles used:**
- **Law V (movement budget):** `v_circ² + v² = c²`. At the hydrogen ground state the
  translational mode is `v = αc`, so `k = c/v = 1/α ≈ 137` (PPT02).
- **The fine/gross identity:** for hydrogen `nP`, the fine-structure splitting between
  `j = 3/2` and `j = 1/2` is `Δν = cR∞ · α² / (2n³)`. For `n = 2`, `2n³ = 16`.

**Route B — pure spectroscopic ratio (uses no `m_e`, `e`, or `h`):**
```
α² = 2n³ · (Δν_2P / cR∞) = 16 · (Δν_2P / cR∞)
```
This is two measured frequencies divided, times a known integer level-structure factor.
The `α²` *scale* is the immediate signal; the `16` is pure `n = 2` bookkeeping.

**Route A — SDT-native virial reading (uses the measured ionisation energy):**
```
½ m_e v² = E_ion ,   v = αc   ⇒   α = √(2 E_ion / m_e c²)
```
`α` falls out of the ground-state binding as the rung velocity — the Law V reading of
PPT02, from `{E_ion, m_e c²}` only.

**Why `α²` (the native mechanism — this is the part that is SDT's, not borrowed):**
The electron sits on the rung at `v = αc`. The leading correction to any rung quantity
is the *second-order* budget term: expand `v_circ = √(c² − v²) = c√(1 − α²)`, and the
first correction is `−½α²`. So a `(v/c)² = α²` factor multiplies the fine structure
**by construction of the movement budget** — no spin-orbit operator, no Dirac
equation. QED reaches the identical `α²` through relativistic spin-orbit coupling; SDT
reaches it through `v_circ² + v² = c²`. The two read the *same* `α²` off the *same*
lines for different stated reasons — the data is shared, the mechanism is the lens.

**Constraints (hard):**
- Only measured spectroscopic observables enter. `α` (CODATA) appears on **one**
  comparison line and never as an input — a delete-test.
- No fitted parameters. No QM wavefunction, no Dirac spin-orbit imported as mechanism.
- The proton-free hydrogen seat is `1/α ≈ 137.07` (Route A, real-H ionisation). The
  idealised `137.036` requires treating the proton as infinitely heavy; per the
  project record this μ-correction is **not** applied to "patch toward" 137.036 — the
  seat is what hydrogen actually says.

## 4. Investigation Strategy

**Phase 1 — Route B (pure ratio).** Compute `α² = 16·Δν_2P/cR∞`, then `α`, `1/α`.
*Method:* `cR∞ = R_inf · c` from `laws.hpp::measured`; `Δν_2P` measured (hard-coded,
cited). *Success:* `1/α` within **0.2%** of 137.036, using no `m_e`/`e`/`h`.

**Phase 2 — Route A (virial / movement budget).** Compute `α = √(2 E_ion/m_e c²)`,
then `1/α`. *Method:* `E_ion` measured (real H); `m_e c²` from `laws.hpp`. *Success:*
`1/α` within **0.1%** of the proton-free seat (≈137.07).

**Phase 3 — Cross-check & consistency.** Confirm the two routes agree to ~0.2%, and
that Route B's `α²` equals `(v/c)²` with `v = αc` from Route A. *Success:* agreement
≤ 0.3%; `zk² = 1` consistency at the hydrogen rung (`z = (v/c)²`, `k = c/v`).

**Phase 4 — Native α²-mechanism.** Demonstrate numerically that the fine/gross scale
is the second-order budget term: expand `√(1 − α²)` and show the leading `½α²`
correction reproduces the `α²` factor without any spin-orbit input. *Success:* the
budget expansion yields the `α²` scale to the same order as the measured fine/gross
ratio; a side-by-side "QED spin-orbit vs SDT budget → same α²" line printed.

**Phase 5 — Honesty boundary (deliberate non-derivation).** State explicitly that both
routes *extract* `α` from data and neither *derives* it from geometry. Record the
dimensionless distinction: `α` is **not** seed-wall-blocked (contrast `ℓ_P`, `m_e`),
so it is a legitimate open target — the geometric derivation is **E51 / OP-3** ("α from
the W=1 torus velocity ratio"), routed through the same lattice solver as the
`6π⁵` wake integral (PPT07). *Success:* the verdict cleanly separates "measured anchor +
native α²-scaling" (this investigation, PASS) from "α from first principles" (open).

## 5. Success Criteria

- ✅ **PASS (Class A/B — measured anchor established):** both routes recover `1/α` from
  spectra to ≤ 0.2%; `α` is never used as an input (delete-test clean); the `α²`
  fine/gross identity holds. *Publish:* "α is a directly measured spectroscopic anchor,
  not a free parameter."
- ✅ **PASS (Class C — native mechanism, correspondence):** the `α²` scaling is shown to
  be the second-order movement-budget term, matching QED's spin-orbit `α²` for a
  different stated reason. *Publish:* "SDT supplies the α²-scaling natively (Law V),
  no spin-orbit postulate."
- ⏳ **PENDING (Class D — out of scope):** the *geometric* derivation of `α` from the
  W=1 torus velocity ratio. Explicitly deferred to **E51 / OP-3**.
- ❌ **FAIL (Class F):** if `α` cannot be read from spectra without circular use of `α`,
  or if the `α²` scaling cannot be obtained without importing Dirac spin-orbit.

The headline result is the measured-anchor + native-scaling pair, **not** a
first-principles derivation of `α` (which remains open).

## 6. Outputs

1. **INVESTIGATION.md** — this document.
2. **aps05_alpha_fine_gross.cpp** — standalone C++20 tool (`#include <sdt/laws.hpp>`)
   computing Routes A and B, the cross-check, and the budget-expansion mechanism.
3. **aps05_results.txt** — table: [route | inputs used | 1/α | % vs CODATA].
4. **APS05_VERDICT.md** — classification with reasoning.

## 7. Dependencies & References

**Upstream (required):**
- **PPT02** — α as the koppa-rung of hydrogen (`k = 1/α = 137`); the spectrum-read seat
  137.07.
- **Law V** — movement budget `v_circ² + v² = c²` (the α²-scaling mechanism).
- **APS01** — Rydberg constant `R∞ = m_e c α²/2h` derived geometrically (the gross scale).

**Downstream (enabled / informed):**
- **E51 / OP-3** — "Fine Structure Constant from Lattice Geometry": the geometric
  derivation this investigation deliberately leaves open.
- **APS04** — trefoil-wake fine structure & Lamb shift (consumes the α²-scaling result).

**Related (read in parallel):**
- **EMC02** — the elementary unit `e` is dimensional (`[A·s]`) and seed-wall-blocked; `α` (dimensionless)
  is not — the key asymmetry.
- **EMC04** — α read as the kinematic rung that lets `P_eff` close.
- **PPT07** — the symmetric case: `m_p/m_e` measured, `6π⁵` privileged, mechanism open.

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| T1 | `α²` = fine/gross | `α² = 16·Δν_2P/cR∞` → `1/α` within 0.2% | the name's meaning is wrong; α² ≠ fine/gross |
| T2 | ground-state `v = αc` | `α = √(2E_ion/m_e c²)` → `1/α ≈ 137.07` | Law V virial reading of the rung is wrong |
| T3 | the two routes agree | `|1/α_A − 1/α_B|` ≤ ~0.3 | gross and fine readings are inconsistent |
| T4 | no circular α | remove `measured::alpha` from inputs; result unchanged | α was smuggled in; the claim is circular |
| T5 | α²-scaling is native | budget expansion `√(1−α²)` gives the α² factor | mechanism requires imported Dirac spin-orbit |

If T1–T4 pass and T5 holds, the measured-anchor + native-scaling claim stands; the
geometric derivation (E51/OP-3) is separately open and its absence is **not** a failure
of this investigation.

## 9. Implementation Notes

- **Double precision** throughout. Use `sdt::laws::measured` for `c`, `m_e`, `R_inf`,
  and `eV_to_J`/`MeV_to_J`; **do not** read `measured::alpha` except on the single
  comparison line (that is the whole point — guard it).
- `cR∞ = R_inf · c`. Hard-code `Δν_2P = 10 969.13e6 Hz` and `E_ion = 13.598434 eV`
  with source comments (these are measured spectroscopic inputs, not in `laws.hpp`).
- Expect Route B ≈ `136.91` (−0.09%): the residual is higher-order QED/Lamb structure
  in the real 2P splitting — **do not** tune it away; report it honestly.
- Expect Route A ≈ `137.07` (+0.03% vs 137.036): this is the **proton-free** seat. The
  infinite-mass idealisation would give 137.036 via the reduced-mass factor; do **not**
  apply it to chase 137.036 — record both and state which is which.
- Print a `zk² = 1` line at the hydrogen rung as an independent consistency check.
- Visualisation hint: a two-row bar of `1/α` (Route A, Route B) against the CODATA line
  makes the "two spectra, one constant" point at a glance.
