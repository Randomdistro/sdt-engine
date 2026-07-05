# RUN_LOG — CH07 Molecular Spectra (Vibration & Rotation)

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-05. **Status:** pre-commit written BEFORE coding.

## Grounding

CH01's electropause well is dead (NP17 is the death knell); the only native molecular well
available is the NP17 shared-seat electrostatic geometry: E(R) = g·αℏc/R with g from pure seat
minimisation. The firewall demand (k from an independent well, not back-solved) is therefore put
to that well directly, and its answer — whatever it is — is the P1 result.

## Faith ledger (§G.1)

1. ℏ is whitelist; but TWO quantisation RULES enter this domain as assertions, and are flagged as
   such up front: (a) the rotational ladder step (wake-winding quantiser, PPT06/APS04 — asserted,
   not derived here); (b) the line-position bridge E = ℏω (emission bridge — same status). Any
   number depending on them is capped IDENTITY/CONVERGENCE, never NATIVE.
2. Shared-seat configuration for H₂ (2 protons ±R/2 on the axis, 2 electron seats on the
   perpendicular bisector at radius xR): a rendering; the seat TOUR (FLM14) is not modelled.
3. Isotope-transfer premise (native, falsifiable): the well is charge-geometry only, so k is
   UNCHANGED under isotope substitution — all isotopologue predictions below have zero new inputs.
4. OBSERVED anchors: ω_e (cm⁻¹) H₂ 4401.21, D₂ 3115.50, HCl 2990.946, DCl 2145.163, CO 2169.813,
   ¹³CO 2121.42; B (cm⁻¹) CO 1.93128, HCl 10.5934, DCl 5.4488; R (Å) CO 1.1283, HCl 1.2746;
   atomic masses (u) standard NIST values; amu = 1.66053906660e-27 kg (unit bridge).

## Committed gates (before run)

- **P1 (native k):** minimise g(x) for the shared-seat well; compute d²E/dR² of E = g*·αℏc/R.
  REGISTERED PREDICTION: the well is scale-free (pure 1/R), so d²E/dR² < 0 everywhere — **no
  restoring stiffness exists in this class**; P1 then resolves OPEN with the missing closure named
  (the contact-saturation wall that would create the interior minimum). If instead a positive k
  emerges, gate: CO/HCl/H₂ stretch within 10%.
- **P2 (back-solved k, declared circular for ν, caps at C):** k_X = μ(2πcω_e)²; then MASS-ONLY
  isotopologue predictions with zero new inputs: DCl from HCl, D₂ from H₂, ¹³CO from CO —
  gate: |error| < 0.5% each.
- **P3 (rotation):** B = ℏ/(4πcI) with measured R — DECLARED IDENTITY (the measured R of these
  molecules is itself spectroscopic in origin; the loop is closed by construction). Reported for
  the record, earns nothing.
- **P4 (novel, mass-only):** B(DCl) predicted from B(HCl)×μ-ratio — gate |error| < 1%.
- **P3-unification:** one winding quantiser for all channels — NOT demonstrable in this run;
  resolves OPEN with owner PPT06/APS04 (+ FLM14 rotation DOF as the live door). Declared now.

## Pre-Run Commitments — CH07

- Prompt completion target: D (native vib chain expected OPEN; mass-scaling predictions earned)
- Physics class hoped: honest mix — OPEN (P1), CONVERGENCE (P2 shifts), IDENTITY (P3)
- CALIBRATED budget: 0 (the allowed stiffness scale is NOT used — a scale plugged to make ν land
  would be the exact circularity the firewall forbids)
- Forbidden: back-solving k and calling ν predicted; retro-widening; per-channel postulates.

## Run record

- Tool: `ch07_spectra.cpp` (`#include <sdt/laws.hpp>`) · build.bat (MSVC recipe)
- Output: `results.txt` = verbatim stdout.
