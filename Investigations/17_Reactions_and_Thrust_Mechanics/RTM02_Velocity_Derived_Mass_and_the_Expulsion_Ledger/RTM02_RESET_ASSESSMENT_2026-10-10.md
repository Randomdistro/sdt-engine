# RTM02 — Velocity-derived mass and the expulsion ledger: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0. **Read:** PROMPT.md, with its 2026-08-03 pre-registration carried. **Not opened:** RTM02_VERDICT.md, tm02_results.txt, the old tool. The supplier RTM01's anchor 10^81.9/day is stated in the prompt; memory exposure "RTM01 3/3" is noted.

## Registration
The phases and gates are as written, with labels fixed by the 2026-10-05 correction:
- **P1 (a, b, c), P2 closed-ledger cancellation, P5 stationarity:** CONSTRUCTION (identities; they cannot fail).
- **P2 open ledger:** reproduce RTM01's 10^81.9/day within 0.1 in the exponent, with g = v_E²/R_E from ridge::v_Earth and ridge::R_Earth (no G). This is a consistency check against the supplier.
- **P3:** the whole-range sweep (computed).
- **P5:** the optimum v_ex/Δv (computed; the known 0.6275 is the reference).
- **Measured propellant-fraction gate** (the correction's request): no dataset is cached, so PENDING_DATA.

## Run and results
(below)
- `rtm02_reset_1.cpp`; output in `rtm02_reset_1_results.txt`. Single pass.
- g = v_E²/R_E = 9.8183 m/s², native.

**Identities (CONSTRUCTION, as the 2026-10-05 correction requires):**
- P1a: worst 9.5e-15.
- P1b: 0 at 1 mm/s.
- P1c: Δm/m = E_k/(mc²) = 0.25 at 0.6c.
- P2 closed ledger: momentum per total expended mass = v_ex exactly (0.5c at 0.5c).
- P5 stationarity.

**Consistency with the supplier:** the open-ledger hover price at 4.5 km/s is **10^81.869 per day**, against RTM01's 10^81.9. That is within 0.1 in the exponent.

**P3 sweep (computed).**
- The closed ledger descends monotonically onto the floor exp(gt/c) = 10^0.001229 per day, reached at v_ex → c (photon rocket).
- The open ledger ignores onboard energy, so it falls **below** the floor at relativistic v_ex: 10^0.00213 at 0.5c, 10^1.7e-6 at c. That is the reason the prompt keeps the ledgers apart; it is not a violation.

**P5:** the energy-optimal v_ex/Δv = **0.6275** (2(1 − e^(−x)) = x, x = 1.593624). It reproduces the known optimum, as a computed result.

**Labels.** Every closed form is shared with special-relativistic rocket mechanics, so this cannot discriminate (the prompt's own scope statement). What is native is the route (the movement budget, with no dilation postulate) and g from Ѻ with no G.

**Grade:** CONSTRUCTION, plus consistency with RTM01. The measured propellant-fraction gate is PENDING_DATA.

## Comparison with the archived record
Deferred.
