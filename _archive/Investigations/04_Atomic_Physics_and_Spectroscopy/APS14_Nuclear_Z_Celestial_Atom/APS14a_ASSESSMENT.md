# APS14a Assessment — Angular Occlusion Emission

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
