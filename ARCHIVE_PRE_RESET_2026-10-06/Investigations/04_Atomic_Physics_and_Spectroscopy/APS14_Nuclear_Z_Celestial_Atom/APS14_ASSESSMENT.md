# APS14 Assessment — Nuclear-Z celestial atom

**Date:** 2026-08-13; B06/B25 closure added 2026-08-15<br>
**Direct execution.** **Canon edits:** `laws.hpp` dodecardinal state solver;
benchmark B06/B25 consumers.<br>
**Instruments:** `run_aps14.py`, `aps14_b06_b25_closure.py`<br>
**Stdout:** `.audit-tmp/aps14_run.txt` (copy `aps14_results.txt`)<br>
**Spec:** `MODEL_SPEC.md`<br>
**Data:** `DATA_MANIFEST.md`

## Current B06/B25 status

`APS14_POLAR_DYAD_SIX_RING_CLOSURE_COMPUTED`

The fixed polar `2s` dyad plus equatorial `2p` six-ring closes the He–Ne state
functional without empirical screening or an element-specific branch. Pair
resistances come from the FLM15 `6/7 : 1/7` lock/wake partition, coincident
synchrony, glancing arc/chord geometry, and complete counterphase paths.

- B06 first IE: median `1.476%`, maximum `5.249%` — PASS.
- B25 He total binding: `79.9682 eV`, error `1.219%` — PASS.
- 45 higher sequential-ionization checks: median `1.621%`, maximum `8.630%`.
- Maximum normalized force residual: `5.72e-16`.

Classification is `COMPUTED`: exact coefficient forms were isolated during
post-freeze diagnostics against the B06 comparison rows. The 45 higher
ionizations were not part of that isolation and independently corroborate the
mechanism. The calibrated M0–M3 ladder below remains the record of the initial
APS14 run; it is not the active B06/B25 calculation.

## Initial calibrated-run dual verdict

| Axis | Outcome |
|---|---|
| **Prompt completion** | Package, corpora Z≤30, nested fits, hold-out scores, diagnostics, CSVs |
| **Orbital seats (one-electron)** | Exact recovery of `r`, `v`, `z`, `F~Z³`, stiffness `~Z⁴`, `zk²=1` |
| **Sequential IE** | M3 best nested model; hold-out median **36.8%**. Does not beat the CALIBRATED(1) `Z_eff` comparator (**11.5%**) |
| **Excitation `ν/ω/λ`** | H-like control **33 ppm**. Neutral resonance (untouched) **excluded** as a principal-n seat law |
| **Shell closures** | Pair occlusion moves IE in the right direction vs bare `Z`; jumps remain large |
| **Identifiability** | M1 `g=0.643` stable under leave-one-element-out. M2 extra parameters did not earn complexity |
| **Promotion** | **none** — `laws.hpp` untouched |

## One-electron control

M0 on a single 1s seat recovers the engine seats to numerical noise:

`r = a_0/Z`, `v = Z α c`, `z = (Zα)²`, `F ∝ Z³`, stiffness `∝ Z⁴`. Hydrogen n=1 sits 18779 koppa-radii outside *this* atom’s `ϟ`. Fe XXVI n=1 sits 27.8 of *that* ion’s koppa-radii out.

H-like 2→1 / 3→1 / 3→2 (seven APS01 NIST lines): median relative energy **0.0033%** with reduced mass. That is this well’s Δz ladder, not a second scale.

## Nested IE models

Fit on log sequential IE of calibration elements. Hold-outs are whole elements `{He, Ne, Na, Ar, K, Cr, Fe, Cu}` (139 measured stages). Zn missing tail remains `NO_DATA`.

| Model | k | hold median | hold <10% | AICc (cal) | Class |
|---|---:|---:|---:|---:|---|
| M0 bare koppa | 0 | 145% | 0.094 | 328 | control |
| **M1** global `g=0.643` | 1 | 52.2% | 0.194 | **−8.5** | CALIBRATED(1) |
| M2 typed `g`, `δ_s/p/d` | 5 | 51.5% | **0.000** | 370 | did not earn parameters |
| **M3** M1 `g`, relaxed totals | 1 | **36.8%** | 0.223 | 29.6 (thinned train) | best nested SDT |
| Bare Rydberg (comparator) | 0 | 145% | 0.094 | — | shared closed form with M0 |
| Slater screening (comparator) | 0 | 17.8% | 0.388 | — | empirical, not native |
| `Z_eff=Z−σ(N_e−1)`, `σ=0.888` | 1 | **11.5%** | 0.439 | — | CALIBRATED(1) baseline |

M1 pair occlusion from deterministic shell geometry is a real step: hold-out median 145% → 52% with one global `g`. Re-solving the N−1 state (M3) takes it to 37%. Typed offsets (M2) worsen AICc and drive the <10% rate to zero; they are not carried.

The promotion gate was: a global calibrated model must beat the effective-charge baseline on held-out elements. M3 **36.8%** vs `Z_eff` **11.5%**. Gate not met. Origin of `g` is pair occlusion on this atom’s seats; it is not yet a predictor that displaces a one-number `Z_eff`.

## Same-n light

In the initial calibrated model, the untouched APS01 resonance set was not in
the fit. With `δ=0`, promoting `s→p` at the same principal n did not change `r`
or `z`. The closure extension now distinguishes polar and ring seats in
multi-electron pair resistance, but its central nuclear term remains isotropic.
It therefore does not yet compute the absolute one-electron same-`n`
polar-to-ring shelf interval.

H-like control rows (explicit `n_lo`, `n_hi`) remain MATCH.

## Parameter stability

M1 `g` under period-distributed leave-outs: 0.643 on H through Mn; 0.710 when Zn is left out. Bootstrap median 0.705 (range 0.643–0.839). One coupling is identified. It is not element-specific.

## Radii

Cordero covalent radii Z=1–30 are in `data/covalent_radii.csv` as an independent MEASURED table. They were not fit targets and are not the Kepler seat `r_i`. Scoring bonded radii against seat radii would mix objects.

## Delete-test

After `g` is fixed, `solve_state` reads Z, configuration, and engine constants only. Measured IE and wavelengths are not inputs to a forward row.

## Parameter ledger

`c, ħ, h, α, a_0, r_e, m_e, m_p, m_n, Ry` — MEASURED-INPUT from `laws.hpp`.  
`g = 0.64335` — CALIBRATED(1), M1/M3.  
`σ_Zeff = 0.888` — CALIBRATED(1), comparator only.  
M2 `δ_s, δ_p, g_same, g_cross` — fitted, **not used**; complexity not earned.  
CALIBRATED SDT physics budget for a proposed canon function: **not proposed**.

## Open

Extension beyond the second period. Absolute same-`n` polar-to-ring shelf
splitting, including the Lamb magnitude. Grammar (`n_d`, `n_t`) as a
center-dependent seating coefficient is not tested here.

## Prohibited-move checklist

- [x] No `laws.hpp` edit
- [x] No G, M as fundamentals
- [x] No APS12 generated tables as inputs
- [x] No 1051.8
- [x] No `dnn` retune
- [x] No `Z_eff` inverted from a hold-out row and reused as its prediction
- [x] Slater labelled empirical comparator
- [x] Zn missing stages `NO_DATA`


## Angular-occlusion emission extension

**Date:** 2026-08-13  
**Author:** James Christopher Tyndall, Melbourne  
**Canon edits:** none

## Verdict

`ORBITAL_PATHWAY_RELATION_SURVIVES__ABSOLUTE_GLOBAL_PREDICTOR_NOT_YET`

There is a measurable relationship between multi-electron excitation energy
and the relative lower/upper orbital pathway. Across the 19 neutral lines for
which A4 produced a positive energy, `corr(log observed energy, log path
ratio) = 0.832`. The complete geometric predictor remains insufficient:
held-out median error is 60.1% at 75% coverage, versus 35.3% at full coverage
for the calibrated quantum-defect comparator.

## What survived

- The exact one-electron pathway identities survive:
  `L~n^2/Z`, `T~n^3/Z^2`, `Omega~Z^2/n^3`.
- `DeltaE = B_lower(1-L_lower/L_upper)` exactly recovers the H-like Rydberg
  depth difference. Seven held-back H-like lines have median error `0.0033%`.
- Correct transition parsing fixes the earlier false treatment of H
  `1s→2p` as a same-`n` move.
- Axis/around geometry raises neutral prediction coverage from 37.5% (A0) to
  87.5% (A2) on held-out elements.
- One global orientation coefficient gives full coverage in A3. Bootstrap
  `eta` ranges from approximately `-0.382` to `-0.270`; whole-element
  leave-outs remain near this interval.
- Explicit companion relaxation materially improves magnitude: A4 held-out
  median error is 60.1%, compared with 320% for A3.

## What is excluded

- Path length alone is not an absolute multi-electron wavelength predictor:
  A1 worsens the held-out median error to 653%.
- The literal deterministic `s/p/d` templates are not sufficient: A2 held-out
  median error is 257% despite improved coverage.
- The proposed core-shadow depth coefficient is not identified. A4 fits
  `rho = 5.85e-20`, and seven of eight bootstrap fits remain effectively zero.
- Same-`n` splitting is not solved: two of three same-`n` rows are positive,
  with median error about 83%. Cross-`n` positive rows have median error about
  49%.
- APS14a does not beat the calibrated quantum-defect comparator and therefore
  does not qualify for promotion to `laws.hpp`.

## Model ladder

| Model | Hold coverage | Hold median error | Outcome |
|---|---:|---:|---|
| A0 corrected endpoints | 37.5% | 251% | excluded |
| A1 pathway, Fibonacci | 37.5% | 653% | excluded |
| A2 axis/around | 87.5% | 257% | geometry incomplete |
| A3 anisotropic | 100% | 320% | coverage survives, scale excluded |
| A4 companion-relaxed | 75% | 60.1% | partial relationship |
| Quantum-defect comparator | 100% | 35.3% | better comparator |

## Interpretation

The user's pathway variable was absent from APS14 and is load-bearing in
APS14a: it supplies the correct one-electron law and strongly orders the
multi-electron energies. The remaining error is not evidence against an
orbital pathway. It localises the missing mechanism to the construction of
the multi-electron path itself—especially same-`n` lane depth, phase evolution,
and companion reorganisation—not to `lambda = hc/DeltaE`.

## Scope and residuals

- Scored neutral corpus: 21 lines through Z=30, split by whole element.
- Controls: 7 H-like lines, never fitted.
- Raw NIST ASD responses for all neutral Z=1–30 are cached and hashed but were
  not silently added to the scored set.
- Dataset size is small; the `0.832` correlation is a characterisation, not a
  canon-level law.
- Delete-test passes: measured energies and wavelengths do not enter forward
  prediction after global calibration.

## Next constrained move

Do not add another free element parameter. The next test should replace the
single circular lane per seat with contact-resolved swept occlusion: integrate
which companion lane blocks which fraction of the active pathway, then test
whether that computed blocked arc predicts the same-`n` residuals.
