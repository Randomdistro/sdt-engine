# E110 — Deflection Decomposition by Powered Straight Line

> **Category**: Gravity / Occlusion · Engineering
> **Difficulty**: HIGH (deep-space powered platform)
> **Status**: Specification (RTM01, 2026-08-03)

---

## 1. Background

The light-deflection coefficient 4 decomposes as profile-2 × geometry-2 (GOM01-IV; the same
profile factor that carries the Shapiro delay, GOM22). The two 2s have different origins,
and RTM01 shows they can be read by two different instruments: a slow powered vehicle
holding a star-fixed straight line past a body pays **only the geometric 2**
(Δv⊥ = 2c²ϟ/bv), while light passing the same impact parameter bends by the **full 4**
(θ = 4ϟ/b).

## 2. SDT Prediction

The thrust telemetry of a null-steered straight pass integrates to Δv⊥ = 2c²ϟ/(bv) — the
geometric factor alone, no profile contribution — while simultaneous astrometry of light
grazing the same b shows 4ϟ/b. The ratio θ_slow/θ_light = c²/2v² across the whole speed
range (verified to machine precision in `rtm01_results.txt` for 10–300 km/s).

## 3. Standard Prediction

Identical numbers at first order: PPN gives the slow-body deflection 2GM/bv² and light
(1+γ)·2GM/c²b with γ = 1 — the same 2-vs-4 split. **Shared form; first order cannot
discriminate.** The earned content is operational: one instrument per factor, the
decomposition measured rather than inferred from a single ray.

## 4. Observable

The integrated lateral thrust history (accelerometer + star tracker) of a powered straight
pass at impact parameter b, against optical/radio deflection measured at the same b in the
same epoch. Any departure of the thrust integral from 2c²ϟ/bv at second order — where the
relay-profile fork c(1−z)² vs c(1−2z) begins to bite — is the discriminating tail.

## 5. Apparatus

Drag-referenced, continuously-thrusting deep-space platform (ion-class) with star-fixed
guidance, plus a conjunction-epoch astrometric campaign. Earth-flyby scale: Δv⊥ ≈ 1.25 km/s
at b = 10R_E, v = 10 km/s — within chemical/ion budgets. Solar-grazing scale is heroic
(≈1272 km/s at 10R☉) and is not proposed; the Earth or lunar pass is the practical target.
