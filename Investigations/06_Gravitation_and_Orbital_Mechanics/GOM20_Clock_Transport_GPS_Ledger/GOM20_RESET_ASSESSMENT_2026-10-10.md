# GOM20 — Clock transport, the GPS ledger: reset record (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0.

**Read:**
- `PROMPT.md`
- `laws.hpp`: `bridge::v_Earth`, `bridge::R_Earth`, `koppa_Earth`
- `graph_v2.json`: layer 0, reach 0

**Not opened:** `GOM20_ASSESSMENT.md`, `gom20_gps_anchor_audit*`, `GOM20_GPS_ANCHOR_PROVENANCE_PRE_REGISTRATION.md` (old record set).

## Registration (fixed before the instrument)

**Native ledger (one Ѻ, two terms; no G, no M).**
- Ѻ_E = v_surf²·R/c², from `bridge::v_Earth` = 7909 m/s and `bridge::R_Earth` = 6.371e6 m.
- GPS orbit radius from the period alone: Kepler in Ѻ form, r³ = Ѻ c² P²/(4π²), with P = half a sidereal day = 43082.045 s (MEASURED-INPUT).
- **Depth term:** clocks keep rate in proportion to (1 − z), with z = Ѻ/r. The satellite gains (Ѻ/R − Ѻ/r) per unit time against a ground clock.
- **Speed term (Law V budget):** the clock's turning is v_circ/c = √(1 − v²/c²), with v² = c²Ѻ/r for the circular orbit. The loss is about v²/(2c²) = Ѻ/(2r).
- **Net fractional rate:** Ѻ(1/R − 3/(2r)).

**Anchors (MEASURED-INPUT).**
- **Primary: the engineered correction itself.** GPS satellite clocks are set to 10.22999999543 MHz for a nominal 10.23 MHz (IS-GPS-200; recalled, tagged [B]). That is Δf/f = −4.4647e-10, or **38.575 µs/day net**.
- **Term anchors** (the prompt's rounded figures): +45.9 and −7.2 µs/day.

**Gate (prompt).** Net within ±0.1 µs/day of the primary anchor.
- **Confirmed (G4)** if met.
- **Rejected** if not; the origin is then assessed.

**Limitation stated before the run.** The ledger as specified uses Earth's v_surf and R alone. It leaves out:
- the ground clock's rotation (v ≈ 465 m/s at the equator, about 0.1 µs/day);
- the geoid's departure from a sphere of radius 6.371e6 m (oblateness).

Both are of the order of the gate. The run uses the ledger exactly as specified.

**Validations:**
- V1: Ѻ_E against `bridge::koppa_Earth` to 1e-12.
- V2: Kepler round trip: the period recomputed from r equals P.
- V3: the exact Law V factor against its first-order form v²/(2c²), compared at GPS speed.

## Run and results

**Errata to the registration text (found in the run; nothing re-scored).** The anchor written above as "Δf/f = −4.4647e-10, 38.575 µs/day" was my arithmetic slip. From the registered frequencies, (10.23 − 10.22999999543)/10.23 = **4.46725e-10 = 38.5971 µs/day**. The instrument computed it from the frequencies.

**Attempt 1: G0.** V3 was not met. Computing 1 − √(1 − v²/c²) directly loses about 1e-6 relative at v²/c² ≈ 1.7e-10, from cancellation. Output kept: `gom20_reset_1_results_attempt1_G0.txt`.

**Attempt 2.** Same ledger, written in the algebraically identical stable form (v²/c²)/(1 + v_circ/c). V1–V3 met.

| quantity | value |
|---|---|
| Ѻ_E | 4.434139e-3 m |
| r_GPS | 26,560.0 km (altitude 20,189 km) |
| v_GPS | 3873.57 m/s |
| depth term | **+45.7090 µs/day** (anchor +45.9) |
| speed term | **−7.2122 µs/day** (anchor −7.2) |
| net | **+38.4969 µs/day** |
| engineered offset | 38.5971 µs/day |
| net − anchor | **−0.1002 µs/day** |

**Gate (±0.1 µs/day): NOT MET**, by 0.0002 µs/day.
- **Round 1 grade: G1**, for the ledger as specified (Earth's v_surf and R alone).
- **Origin:** the limitation registered before the run. A ground clock on the rotating Earth spends part of its own budget on rotation, and the specified ledger leaves that out. At the equator that is v = 464.6 m/s, worth +0.1037 µs/day. The mechanism (one Ѻ, depth plus budget) is not what failed; the specification's ground term is incomplete.

## Round 2 (registered 2026-10-10 AFTER round 1 was seen; flagged)

**Change.** The ground clock also pays the Law V budget for Earth's rotation: v_rot = 2πR/T_sidereal on a sphere of the engine's mean radius. The net becomes net₁ + v_rot²/(2c²) (stable form).

Nothing else changes: the gate, the anchor and the inputs are the same.

**Disclosure.** The size of this term (+0.1037 µs/day) was printed in round 1 as context. Round 2 therefore cannot fail by much and is labelled **post-seen**. It is not counted as an independent confirmation.

**Remaining approximation, stated.** A clock on the equator of a sphere is not a clock on the geoid. Oblateness changes depth and rotation together, and the geoid is defined by their sum being constant.

**Round 2 result** (computed by hand from the round-1 output; no new instrument):
- net₂ = 38.4969 + 0.1037 = **38.6006 µs/day**;
- against 38.5971: **+0.0035 µs/day**, within the gate. **Post-seen; G3 at best.**

## Labels
- **Provenance:** NATIVE in form (one Ѻ for both terms; Kepler and the circular speed from the same Ѻ; no G, no M). CONVERGENT with the weak-field textbook terms, by the same algebra; not discriminating.
- **Discrimination:** none. The prompt's claim that "the prevailing account needs two separate theories" is a narration point, not a numerical difference.

**Downstream:** none.

## Comparison with the archived record
Deferred.
