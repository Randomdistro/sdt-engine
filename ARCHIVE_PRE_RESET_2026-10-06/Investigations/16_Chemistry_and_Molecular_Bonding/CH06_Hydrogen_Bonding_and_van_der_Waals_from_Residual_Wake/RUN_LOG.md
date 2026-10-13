# RUN_LOG — CH06 Hydrogen Bonding & van der Waals from Residual Wake

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-05. **Status:** pre-commit written BEFORE coding.

## Grounding

NP17 machinery throughout: a residual wake = a ± handed pair of point sources (the uncancelled rim
of the electropause), pair energy ±αℏc/r (engine `coulomb_identity`, class F identity, declared).
A bond-rim residual of strength p is represented as a unit-handed ± pair with separation
**d = p/e** (p = measured bond-level electric moment, OBSERVED anchor; e = the unit bridge — no
charge substance implied, handed redirection only). NO induced-dipole machinery, NO assumed 1/r⁶:
every exponent below must come OUT of a numerical fit to the computed sums.

## Faith ledger (§G.1)

1. Residual = ± pair separated by d = p/e: geometric idealisation of the rim residual. Named.
2. The fluctuation source that drives dispersion is substrate influx jitter; its AMPLITUDE is an
   OPEN closure (not derived, not fitted here — only the r-EXPONENT is claimed, jitter-independent).
3. Seat stiffness κ of the residual amplitude: arbitrary in magnitude for the exponent test
   (the exponent is invariant to κ in the weak-coupling regime — demonstrated in-run by using two
   different κ and requiring the same fitted exponent).
4. Donor–acceptor distances: measured heavy-atom separations (OBSERVED): O···O 2.82 Å (water
   dimer/ice), F···F 2.72 Å (HF dimer), N···N 3.26 Å (ammonia dimer).
5. Bond-rim moments (OBSERVED anchors): O–H 1.51 D, H–F 1.826 D, N–H 1.31 D.

## Committed gates (before run)

- **P1a exponent (dipole–dipole):** fitted log-log slope of the exact 4-point sum, aligned axial,
  over r/d ∈ [10, 100] = **−3.00 ± 0.05** (this is the geometric far-field of the ± pair — must
  come out, not be assumed).
- **P1b exponent (correlated fluctuation):** fitted slope of ΔF(r) from the two coupled fluctuating
  residual amplitudes = **−6.00 ± 0.05**, and INVARIANT (±0.05) under a ×10 change of κ and of the
  jitter scale. The London exponent must EMERGE as 2 × (P1a slope).
- **P1c size trend:** structural — from the derived form, ΔF grows monotonically with residual
  amplitude (d) at fixed r. (Full noble-gas ladder needs per-species residual sizes — not available
  natively yet; declared DEFER, not claimed.)
- **P2 H-bond:** exact 4-point sum, aligned: H₂O in the 10–40 kJ/mol band; O–H···O > N–H···N;
  angular scan shows maximum attraction at the linear geometry (linearity DERIVED).
- **P4 novel ordering:** all three pairwise relations of {HF, H₂O, NH₃} vs measured dimer
  energies (20.8, 19.1, 13.2 kJ/mol — OBSERVED). REGISTERED EXPECTATION: NH₃-weakest should hold;
  HF-vs-H₂O is within the anchors' proximity — a miss there is reported as a miss.
- **P3 water 4 °C:** DEFER (network simulation out of scope for this run; named debt).

## Pre-Run Commitments — CH06

- Prompt completion target: C · Physics class hoped: CONVERGENCE (honest) · CALIBRATED budget: 0
  (nothing tuned; amplitudes come from measured moments, distances from measured geometry)
- Forbidden: assuming any exponent; tuning the residual amplitude toward 20 kJ/mol; retro-widening.

## Run record

- Tool: `ch06_residual_wake.cpp` (`#include <sdt/laws.hpp>`) · build.bat (MSVC recipe)
- Output: `results.txt` = verbatim stdout.
