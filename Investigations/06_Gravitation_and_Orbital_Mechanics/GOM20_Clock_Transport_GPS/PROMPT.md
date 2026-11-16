# GOM20 — Clock transport: the GPS ledger (specification rewritten 2026-10-11)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the next mechanism. The seed specification (2026-07-29) and its audit block are kept unchanged below the line; they are superseded.

**Record of the runs so far:** `../GOM20_Clock_Transport_GPS_Ledger/GOM20_RESET_ASSESSMENT_2026-10-10.md`. That record sits in a sibling folder created on 2026-10-10 by mistake; moving it awaits Harvey's approval. It holds the instrument `gom20_reset_1.cpp`, its output, and the attempt-1 G0 output.

## 1. Question
Does one Ѻ (Earth's, from v_surf and R; no G, no M) carry both GPS clock terms? The terms are the depth differential (z = Ѻ/r) and the Law V budget spend (v² at orbital speed), and the question is whether they reproduce the engineered satellite-clock offset to ±0.1 µs/day.

## 2. What is established (runs of 2026-10-10)
| # | Result | Grade |
|---|---|---|
| R1 | Ѻ_E = 4.434139e-3 m; r_GPS = 26,560.0 km from the half-sidereal period alone (Kepler in Ѻ form); v_GPS = 3873.57 m/s. Depth term +45.7090 µs/day; speed term −7.2122 µs/day; net **+38.4969 µs/day**. | computed |
| R2 | Anchor from the registered frequencies, (10.23 − 10.22999999543)/10.23 = 4.46725e-10 = **38.5971 µs/day**. The prompt's "net +38.7" is a rounded figure and is not the anchor. | MEASURED-INPUT |
| R3 | Round 1 (sphere of radius R, ground clock at rest): net − anchor = −0.1002 µs/day. Missed the ±0.1 gate by 0.0002. | **G1** for the ledger as specified |
| R4 | Round 2 (ground clock also pays the budget for Earth's rotation at the equator, +0.1037 µs/day): +0.0035 µs/day. | **G3, post-seen** (the term's size was printed in round 1) |
| R5 | Provenance: native in form (one Ѻ for depth, orbit and speed). Convergent with the textbook weak-field terms by the same algebra; not discriminating. | label |

## 3. Errors made, and what each teaches
| # | Error | Lesson |
|---|---|---|
| X1 | Attempt 1 computed 1 − √(1 − v²/c²) directly and lost about 1e-6 relative to cancellation (V3 not met, G0). | Use the stable form (v²/c²)/(1 + v_circ/c). Check every validation tolerance against the floating-point floor before registering it. |
| X2 | The anchor was written as 38.575 µs/day: an arithmetic slip in the record. The instrument computed it from the frequencies. | Anchors are computed by the instrument from the primary quantities, never transcribed. |
| X3 | The specified ground term (a clock at rest on a sphere) is incomplete. Rotation and oblateness are each of the order of the gate. | The ground clock lives on the **geoid**: the surface where depth plus rotation spend is constant. The ground term must be the geoid's own measured value, not a sphere. |
| X4 | The engine stores v_Earth to four figures (7909 m/s). Ѻ_E carries about 2e-4 relative from that rounding, worth about 0.009 µs/day on the depth term. | An input-precision floor, below the gate. Recorded as a canon note (propose-and-wait: more figures for `bridge::v_Earth`). |

## 4. Round 3 (registered here; to run)
**Ground term from the geoid, as a measured anchor.** The IAU defining constant L_G = 6.969290134e-10 (IAU 2000 Resolution B1.9) is the geoid clock's total rate offset (depth plus rotation spend) against a clock far from Earth. Native reading: z_geoid ≡ L_G. It is MEASURED-INPUT; it is a defined constant fixed from geodesy.

**Shared-input flag (procedural §3.8).** Contaminating input: W₀, the geoid potential. It is measured via satellite geodesy and altimetry gravity models built on GM, and it enters at L_G = W₀/c². Round 3 is therefore **shared-input** for the ground term. It is useful only as a check of the satellite term against the best ground value, not as a native result.

**Native alternative (owed):** the ground term from Ѻ_E on Earth's measured **geometric** figure (flattening f from geometric geodesy, with rotation). That needs the native depth law on an oblate body, which is not yet in the engine. Registered as GOM20 round 3b, to be specified before any value.

**Satellite term from the one Ѻ:** Ѻ/r + (budget spend at v), i.e. 3Ѻ/(2r) to first order. The stable form is used.

**Net = L_G − (satellite term).** Gate: ±0.1 µs/day against 38.5971.

**Exposure.** While drafting, the author computed this net by hand at about 38.578 µs/day (−0.019). Round 3 is therefore **post-seen**: G3 at most. It replaces the sphere approximation; it does not add evidence.

**Validations:**
- V1: L_G × 86400 × 1e6 = 60.2147 µs/day to 1e-4.
- V2: round 1's satellite terms reproduced to 1e-6.
- V3: the stable form against its first-order expansion at GPS speed, to 1e-9.

## 5. The held-out test (round 4; to register blind before any value is loaded)
**Eccentric-orbit clocks.** Galileo satellites GSAT-0201/0202 (Doresa, Milena) were launched into eccentric orbits (e ≈ 0.16). Their clocks show a periodic rate term from depth and speed varying around the orbit. Its measured amplitude was published (Delva et al. 2018, Phys. Rev. Lett. 121, 231101; Herrmann et al. 2018, same issue) [B: to verify].

The same one-Ѻ ledger predicts the periodic amplitude from the orbit's a and e alone. That amplitude is **not yet computed or looked up**, so this is the first discriminating-strength test GOM20 has.
- Gate: the published fractional uncertainty of the amplitude.
- Data: Delva 2018 tables (to be fetched into `Datasets/gps_clock_2026-08/` with provenance).

## 6. Prohibitions
- No G, GM or M; Earth enters only through v_surf, R and the geoid constant.
- No time-arrow framing: clocks keep rate; nothing "dilates" as a process.
- No borrowed units.
- No edits to Engine/Laws (the v_Earth precision note is propose-and-wait).

---

## Superseded specification (2026-07-29 seed, kept as written)

# GOM20 — Clock Transport: the GPS Ledger

> **Status:** OPEN — specification seed (benchmark-coverage alignment 2026-07-29; catalogue
> row B61). **Author:** J. C. Harvey, Melbourne. Gateways binding.

## Target

GPS satellite clocks run fast by +45.9 μs/day from orbital depth and slow by −7.2 μs/day
from orbital speed: net +38.7 μs/day, corrected by design in every receiver. The prevailing
account needs two separate theories for the two terms. Measured anchor: the engineered
correction itself, documented to fractions of a microsecond.

## SDT footing

One ledger carries both terms natively. The speed term is Law V budget spending (v² at
orbital velocity); the depth term is the seat's depth on the wake, z = ϟ/r read at the
satellite's altitude versus the ground station's (L17; the same depth expression confirmed
at the solar photosphere to 0.03%). Both terms come from one formula pair sharing one
koppa — no separate frameworks, no interface between them. Existing corpus: GOM05 (depth
closure), GOM12 (koppa invariance), the B28 depth-closure tally.

## Pre-registration skeleton (complete before any tool)

- Question: does the single ledger (budget spend + depth differential on Earth's ϟ)
  reproduce +45.9/−7.2/net +38.7 μs/day from Earth's measured v_surface and R alone?
- Rejection criterion (populated): net correction off by more than the documented
  engineering tolerance — the numbers are known to sub-μs precision; there is nowhere to
  hide.
- Anchors: GPS orbital radius/period; the documented corrections.
- Tolerance: ±0.1 μs/day on the net.

## Benchmark linkage

Catalogue row B61 · a clean tally candidate from bridge:: + law_V — one of the easiest
unclimbed rungs in the suite.

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The seed is "PENDING_MECHANISM" with no pre-registration: it names no model for how depth and speed give the +45.9 and −7.2 μs/day terms, and both terms are the standard weak-field results.

**Correction:** Derive both terms from ϟ and the movement budget and register the ±0.1 μs/day gate before running.

**Status:** OWED — model, data or derivation missing; requirement and tolerance recorded, nothing run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
