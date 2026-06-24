# PM06 — Cyclotron and Synchrotron from Differential Occlusion

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **Hard rule (R-units, [[feedback_no_borrowed_units]]):** never express a result in Bohr magnetons,
> magnetons, or any imported magnetic unit. Use native wake-circulation units, koppa, traction `T=3(W+1)`.

## Question

A vortex crossing a swirl field is pushed sideways by differential occlusion (PM01's Lorentz). A
constant sideways push at fixed speed is a **centripetal** push → circular orbit. **Can the cyclotron
frequency `ω_c` be derived as the relay-occlusion orbit, and synchrotron radiation as the throughput
the vortex sheds while its wake is forced to turn (E89 deceleration) — all in native units, no
magneton?** The orbit radius is a koppa-style closure (`ω_c=v/r` with `r` set by occlusion push vs
movement budget); the radiation is the same emission channel as PM03.

## SDT mechanism & hypotheses

The PM01 Lorentz push is always ⊥ to the vortex velocity (differential occlusion across the swirl
gradient), so it does no work — it only turns the vortex, tracing a circle. Forcing the wake to turn
costs throughput it cannot retain at the turn, which is emitted (PM03 pulse) as cyclotron/synchrotron
light; at high speed the movement budget (Law V) beams it forward.

- **H1 (ω_c as occlusion orbit):** centripetal `m v ω_c = ` (PM01 occlusion push) → recover
  `ω_c = qB/m` form, with `qB` as the native handed-swirl gain (no µ_B); radius `r = v/ω_c`.
- **H2 (synchrotron = turned-wake emission):** radiated power = throughput shed per turn (E89
  bremsstrahlung/deceleration); recover `P ∝ γ⁴` scaling and the critical-frequency `∝ γ³ω_c`.
- **H3 (beaming from the budget):** Law-V (`v_circ²+v²=c²`) forward-folds the emission into a
  `1/γ` cone — relativistic beaming without a separate Lorentz-transform postulate.

## Strategy

**Phase 1 — Circular orbit.** Send a test vortex into a uniform PM01 field; integrate the occlusion push.
*Goal:* `ω_c`, `r`. *Method:* trajectory integration. *Success:* `ω_c` matches `qB/m` form to <1%;
orbit closes; sense set by EMC03 handedness.

**Phase 2 — Radiated power.** Compute throughput shed per turn (E89). *Goal:* `P(γ)`. *Method:* turn
ledger + emission. *Success:* non-relativistic `P ∝ ω_c²v²`; relativistic `P ∝ γ⁴` recovered.

**Phase 3 — Spectrum.** Pulse train of the turned wake (PM03). *Goal:* critical frequency, spectrum.
*Method:* Fourier of the beamed pulse. *Success:* `ω_crit ∝ γ³ω_c`; the synchrotron spectral shape order-correct.

**Phase 4 — Beaming.** Apply Law-V budget at high `v`. *Goal:* emission cone. *Method:* movement-budget
fold. *Success:* `1/γ` half-angle recovered.

## Success criteria

- ✅ **PASS (A):** `ω_c` + `P∝γ⁴` + `1/γ` beaming all native, zero fitted params; no µ_B anywhere.
- ✅ **QUALIFIED (C):** `ω_c` & power native; spectral prefactor flagged as a borrowed correlation. *(Expected.)*
- ⚠️ **PENDING (D):** circular orbit & `ω_c` shown but radiation only scaling-correct.
- ❌ **FAIL (F):** orbit needs a primitive `qv×B` re-imported, or radiation needs a magneton.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Orbit | closed circle, `ω_c = qB/m` form, EMC03 sense | occlusion push not centripetal → no cyclotron |
| Radiated power | `P ∝ γ⁴` (E89 turned-wake) | turning doesn't shed throughput → no synchrotron |
| Beaming | `1/γ` cone from Law-V budget | beaming needs an external Lorentz boost |

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (Lorentz occlusion), E89 (bremsstrahlung/
deceleration radiation), [[PM03_EM_Waves_as_Coupled_Relay_Pulses]] (emission channel), Law V (movement budget).
**Downstream:** [[PM05_Magnetic_Reconnection_and_Solar_Flares_from_Wake_Topology]] (synchrotron from accelerated populations), astrophysical sources.
**Related:** EMC03 (orbit sense / handedness), koppa closure (orbit radius), [[feedback_no_borrowed_units]].
