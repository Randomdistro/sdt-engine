# QM07 — VERDICT: Spin & Stern–Gerlach from Handedness

**J. C. Harvey, Melbourne — 2026-07-04.**
Tool: `qm07_sg_handedness.py` (seed 23, N=2×10⁵/condition). Real stdout: `qm07_results.txt`.
Pre-commitments: `RUN_LOG.md` (frozen before coding; no threshold moved; the M1 failure below was
pre-declared *before* the run).

## Earned (NATIVE machinery)

1. **Two-valuedness → two spots, no middle.** Binary circulation handedness η = ±1 (EMC03) under
   a swirl-gradient differential-occlusion push gives exactly two equal beams: centre-band
   occupancy 0.14% (gate <1%), peak asymmetry 0.0004, at every gradient. **The rival comparison
   column** (classical continuous dipole, isotropic axis): 50.1% centre-band — a filled
   continuum. The OBSERVED 1922 two-spot data falsifies the continuous-moment rival; binary
   handedness passes. This is the discriminator the prompt asked for, and it is machinery.
2. **Deflection ∝ gradient:** separation linear in G to 0.042% (gate 1%). Magnitudes carry no
   unit claim — no μ_B, no magneton, anywhere (memory rule: SDT-native yardsticks only).
3. **Sequential-SG structure at θ = 0, 90°, 180°:** the undisturbed-vector machinery already
   gets the endpoints and the 50/50 midpoint exactly (1.000 / 0.501 / 0.000) with no tuning.

## The honest miss (pre-declared, fired as committed)

**M1 (undisturbed hidden handedness vector):** transmission = triangle law 1 − θ/π,
RMS vs the OBSERVED cos²(θ/2) = **0.0719 — FAILS the <2% prompt gate.** This is the prompt's T3
firing, reported as found.

**M2 (diagnostic probe — labelled, NOT a derivation):** a re-preparation residence density
∝ cos(angle to the filter axis) on the passed hemisphere reproduces the observed curve to RMS
0.0002. The probe's only role is to name the missing machinery exactly: **what the filter must do
to the surviving vortex's handedness distribution is precisely a cos-weighted residence law.**
Nothing here derives that density; deriving it IS the debt.

## g-factor (Phase 2): OPEN, as the prompt's engine-fact correction requires

Not attempted. The binary moment (two signs, equal magnitude) is structural from Phase 1. The
g number 2.00232 lives in benchmark B17 (`g = 2(1+α/2π)`); the W+1 line is a boundary-radius
coefficient, not a magnetic g — not cited. No μ_B imported.

## HUNTER §D — seven questions (on the M1 sequential-SG failure)

1. **Why (exact mechanism)?** The undisturbed-vector model under-transmits at small θ (0.917 vs
   0.983 at 15°) and over-transmits at large θ (0.249 vs 0.146 at 135°): a uniform hemisphere is
   too broad a survivor population — the filter must *concentrate* residence toward its axis.
2. **Recoverable?** Yes, if the SG filter's occlusion mechanically re-seats the survivor's
   handedness with residence ∝ cos(angle). That is a definite, testable machinery statement.
3. **What did the target fail to account for?** The filter is not passive: passing through the
   swirl gradient is itself a relay interaction that reshapes the handedness distribution
   (measurement-as-mechanics). M1 modelled the filter as a pure gate.
4. **Errored premise?** "The filter only selects; it does not re-prepare." That premise is now
   dead: the observed curve cannot be reached by any pure-selection model of a static vector
   (the triangle law is its ceiling — same structural reason the QM05 local model caps at 2).
5. **What freedom corrects it?** The post-filter residence density over handedness directions.
6. **Native quantity or knob?** Native candidate: the same energy-density residence law owed
   everywhere in this cluster; the cos-weighting was NOT tuned here (M2 is a labelled probe,
   the exact analogue of QM05's cos² probe — it names the target, it is not a pass).
7. **Cascade?** **YES — RESIDENCE-LAW root** (with QM04 Phase-2, QM05 weighting, QM03
   re-seeding). One law closes four debts; owner: FLM14 rule-form-4 (in flight). Note the tight
   link: QM05's joint weighting cos²(a−b) and QM07's sequential cos²(θ/2) are the same functional
   form on one vs two wings — further evidence of a single root.

**Recovery grade: PARTIAL** — errored premise (passive filter) identified and killed; correcting
freedom named and native-candidate; not yet derived. Correction is CLOSE (derive the residence
law), not amputate.

## New questions logged

1. Does the differential-occlusion filter, simulated at the wake level (not gate level), already
   concentrate survivors toward the axis? A tick-level SG filter sim is the direct test of Q4's
   dead premise — first target once FLM14 lands.
2. Re-projection tick cost (prompt Q4): M2-style re-seating is a mechanical event; does it
   predict a measurable dwell time in the filter absent from the operator picture?

---
**Prompt completion B · Physics class NATIVE (two-valuedness, two-spot, gradient-linearity) +
OPEN (sequential cos²(θ/2); g-number OPEN → B17) · Recovery PARTIAL · Cascade root RESIDENCE-LAW**
