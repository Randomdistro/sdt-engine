# APS13 Assessment — Horizon z as wavelength modifier

**Date:** 2026-08-13  
**Direct execution.** **Canon edits:** none.  
**Mode:** exploratory (pre-registration skipped at author direction).  
**Instrument:** `aps13_horizon_z.py`  
**Stdout:** `.audit-tmp/aps13_run.txt` (copy `aps13_results.txt`)  
**Prompt:** `PROMPT.md`  
**Reference:** the atom. Seats, series, and ions of that well. No other body.

## Dual verdict

| Axis | Grade |
|---|---|
| **Prompt completion** | **A** — geometry on each body vs its own ϟ; D0 hydrogen series; D1 H-like family; D2; D3 hold-out |
| **Physics class** | Horizon on this atom **native**. Fractional `(1+z)` and clock **excluded on hydrogen’s own lines**. Stretch `λ ∝ 1/Δz` **MATCH** on H series and H-like 2→1. Law V **MATCH** on Fe XXVI at **0.210%**. Occupancy: CALIBRATED(2) `σ_n` predicts **this table’s** inner/K-shell hold-out; first IE **excluded**. |

## Geometry — each body vs its own koppa

| Seat | z | k | `r/ϟ` | inside |
|---|---:|---:|---:|---|
| H c-boundary | 1 | 1 | 1 | yes |
| H proton | **3.349** | 0.546 | 0.299 | yes |
| H n=1 | 5.325×10⁻⁵ | 137.0 | **18779** | no |
| H n=2 | 1.331×10⁻⁵ | 274.1 | 75115 | no |
| H n=3 | 5.917×10⁻⁶ | 411.1 | 169009 | no |
| He+ n=1 vs He+ ϟ | 2.130×10⁻⁴ | 68.52 | 4695 | no |
| Fe XXVI n=1 vs Fe ϟ | 0.0360 | 5.27 | **27.78** | no |
| Fe-56 vs Fe ϟ | **20.59** | 0.220 | 0.0486 | yes |

Hydrogen: the proton fills **0.299** of *this* koppa; n=1 sits **18779** koppa-radii out. Fe XXVI n=1 sits **27.8** of *that* ion’s koppa-radii out — same law, same family, closer to its own horizon. Electronic light is not born at `z ≥ 1` on this atom.

H n=2 / n=1 radius = 4; `z_1/z_2` = 4. That is this atom’s ladder.

## D0 — hydrogen against itself

Rest = H I Lyα **121.567 nm**. Hydrogen’s own `z_n`.

| Line | obs | A `(1+z)` | D stretch Δz | C `½mc²Δz` |
|---|---:|---:|---:|---:|
| Lyβ 3→1 | 102.5722 nm | 121.57 nm (**18.52%**) | **0.0000%** | 0.053% |
| Hα 3→2 | 656.4614 nm | 121.56 nm (**81.48%**) | **0.0001%** | 0.053% |

Fractional and clock are **excluded on hydrogen**. They cannot turn this atom’s Lyα into this atom’s Hα. Stretch by this atom’s `Δz` can.

## D1 — H-like family, same 2→1

Same well, deeper `ϟ_Z`. Rest still H I Lyα.

| Target | obs | A | D | C |
|---|---:|---:|---:|---:|
| He II | 30.3785 nm | **300%** | **436 ppm** | **97 ppm** |
| Li III | 13.5006 nm | **801%** | **507 ppm** | **26 ppm** |

A is the same miss as D0: `(1+z)` does not move the line. D is `Z²` at fixed excitation. C manufactures the energy from `Δz` with no rest wavelength. Origin of D/C is this family’s koppa depth, not Coulomb.

## D2 — H-like 2→1 through Fe XXVI

| Species | stretch from H | `½mc²Δz` | Law V |
|---|---:|---:|---:|
| H I | 0 (rest) | 0.053% | 0.055% |
| He II | 0.044% | 0.010% | 0.016% |
| Li III | 0.051% | 0.003% | 0.018% |
| Fe XXVI | **0.988%** | **0.934%** | **0.210%** |

Law V on *this ion’s* `z_n`, no extra parameter. Light-Z fitted remainder `a` is unstable and worsens Fe to 2.61%. Excluded.

## D3 — occupancy of this table

Train: Z = 2,4,6,8,10. Hold: Z = 3,5,7,9,11,12,18,20,26.  
`Z_eff = Z − σ_n (N_e − 1)`. CALIBRATED(2): `σ_1 = 0.63177`, `σ_2 = 0.80763`.

| Slice (hold) | σ_n med | σ_n <10% |
|---|---:|---:|
| all 111 | 3.78% | 0.748 |
| first IE k=1 | **90.8%** | 0.111 |
| inner 1<k<Z | **3.78%** | 0.785 |
| last k=Z | 0.15% | 1.000 |
| n=1 | **0.17%** | 1.000 |

Inner and K-shell of the hold-out are predicted from this train. First IE is not. Companions hide *this* nuclear koppa. Valence unpaid.

## Parameter ledger

`c, h, e, α, a_0, r_e, R_p, m_e, Ry` — MEASURED-INPUT / engine DERIVED.  
H I / He II / Li III / Fe XXVI λ — OBSERVED.  
`σ_1, σ_2` — CALIBRATED(2). Law V Fe — DERIVED, CALIBRATED(0).

## Open

`ϟ_felt` for valence. Geometry for `σ_n` that is not inverted from IE. Same-n optical terms.

## Prohibited-move checklist

- [x] No G, M, ψ, QED logs
- [x] No 1051.8; no `dnn` retune
- [x] No hold-out `Z_eff` reused as its own prediction
- [x] No other body as analog
- [x] Canon untouched
