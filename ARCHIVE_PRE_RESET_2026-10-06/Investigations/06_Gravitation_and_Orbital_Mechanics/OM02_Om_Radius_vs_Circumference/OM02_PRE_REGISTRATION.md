# OM02 Pre-registration — Om radius vs circumference as solar length

**Date:** 2026-08-11  
**Author relation:** Circumference \(C=2\pi\Omega\) is the correct *length*;
\(\Omega=R/k^2\) is the *distance from centre* where the c-boundary sits.  
**Canon:** not edited

## Freeze

| Symbol | Meaning | Value class |
|---|---|---|
| \(\Omega_\odot\) | radial c-boundary location | \(\approx 1476.6\,\mathrm{m}\) (DE441 / OM01-class) |
| \(C_\odot=2\pi\Omega_\odot\) | circumference length | \(\approx 9.28\,\mathrm{km}\) |

## Test

For each solar formula that presently inserts \(L\sim 1477\,\mathrm{m}\), compute
once with \(L=\Omega\) and once with \(L=C\) (no retune):

| Observable | Formula | Anchor |
|---|---|---|
| Limb deflection | \(4L/R_\odot\) | \(\approx 1.751''\) |
| Surface redshift | \(L/R_\odot\) | \(\approx 2.12\times10^{-6}\) |
| Mercury perihelion | \(6\pi L/(a(1-e^2))\) / century | \(\approx 42.98''/\mathrm{cy}\) |
| Shapiro marker | \((4L/c)\ln(4 r_E^2/R_\odot^2)\) | \(\sim 240\,\mu\mathrm{s}\) order |

## Decision

| Class | Rule |
|---|---|
| MATCH | \(\lvert\log_{10}(\mathrm{pred}/\mathrm{anchor})\rvert < 0.05\) |
| ORDER | \(< 1\) |
| EXCLUDED | else |

- If \(\Omega\) MATCHes and \(C\) fails by \(\sim 2\pi\): circumference is ontology/name only;
  formulas must keep \(\Omega=C/(2\pi)\).
- If \(C\) MATCHes and \(\Omega\) fails: length substitution survives.
- No EMPIRICALLY SURVIVES without raw path data this run.
