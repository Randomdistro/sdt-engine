# PM06 — Cyclotron and Synchrotron from Differential Occlusion

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Does PM01's perpendicular differential-occlusion push, applied to a moving
   vortex, **close into a circular orbit at the cyclotron frequency `ω_c`** with the gyro-radius set by
   the occlusion push balanced against the Law-V movement budget — **using the native handed-swirl gain,
   not a `qB/m` with `q`,`B` in SI and certainly no µ_B** — and does forcing the wake to turn shed
   throughput as synchrotron light (the same E89 emission channel as bremsstrahlung)? The open part is
   whether the gain and the `γ⁴`/`γ³` scalings are *derived* or merely *matched*.
2. **Why does it matter?** — Cyclotron/synchrotron is the test that PM01's Lorentz-occlusion does real
   *dynamics* (a closed orbit), and that PM03's relay-pulse emission carries the radiated power. A native
   pass links magnetism, radiation, and the movement-budget beaming into one mechanism; astrophysical
   synchrotron sources (PM05 populations, AGN jets) then become SDT-native.
3. **How will we find out?** — Four gated phases (§④): integrate the orbit, compute shed throughput per
   turn (E89), Fourier the beamed pulse train (PM03), fold the Law-V budget for beaming. Native gain and
   orbit precede any `qB/m`/textbook-power comparison.
4. **What would prove us wrong?** — §⑧, each falsifier with its killing number (orbit not closing,
   `ω_c` off the form, power not `∝γ⁴`, beaming not `1/γ`).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase.

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

**Anti-tautology firewall.** Writing `ω_c = qB/m` and integrating an orbit with it is the *trivial*
path — it assumes the very Lorentz force PM01 was supposed to derive. The *load-bearing* path is to
integrate the **PM01 occlusion push directly** (the perpendicular differential occlusion across the
swirl gradient, in native units), observe that the orbit closes, and *read off* `ω_c` — then map to the
`qB/m` form last. **Re-importing a primitive `qv×B` to make the orbit close, or expressing the gain in
µ_B/µ_N, caps the grade at C (and the magneton is an outright units FAIL).** The synchrotron `γ⁴` /
`γ³` prefactors are flagged CONVERGENCE until derived from the E89 turned-wake ledger.
**Native-before-borrowed / forbidden:** no primitive `B`/`qv×B` in the orbit chain, no µ_B/µ_N/
magneton anywhere, no G/M-fundamental, no QM wavefunction, no external Lorentz-boost postulate for
beaming (it must come from Law V). The radiated *quanta* are PM03 relay pulses, not photon-field QED.

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

## Falsification tests (each states the number that kills it)

| # | Test | SDT prediction | If it fails (the killing number) |
|---|------|----------------|----------------------------------|
| T1 | Orbit closes at `ω_c` | orbit closes (drift <1% per period); `ω_c` matches `qB/m` *form* to <1% from the native occlusion gain; sense set by EMC03 | orbit does not close, or `ω_c` off >1%, or it closes only after re-importing a primitive `qv×B` → occlusion push not centripetal → C, not A |
| T2 | Radiated power scaling | non-relativistic `P ∝ ω_c²v²`; relativistic `P ∝ γ⁴` from the E89 turned-wake ledger | exponent ≠ 4 (and not derivable) → turning does not shed throughput as synchrotron |
| T3 | Critical frequency | `ω_crit ∝ γ³ ω_c`; spectral shape order-correct | `γ` exponent ≠ 3 → pulse-train Fourier of the turned wake is wrong |
| T4 | Beaming from Law V | emission half-angle `≈ 1/γ`, from the movement-budget fold alone | half-angle ≠ `1/γ`, or needs an external Lorentz boost → beaming not budget-native |
| T5 | Units | every quantity in native circulation units; SI map once at the end | any `ω_c`/power/gain expressed in µ_B/µ_N → automatic units FAIL (no soft downgrade) |

## Questions This Opens *(generative — log in `PM06_VERDICT.md`)*

1. **Is the gyro-radius a koppa-style closure?** If `r = v/ω_c` is the occlusion-push-vs-budget balance,
   is it the same `ϟ = v²R/c²` closure that sets orbits in GOM02 — magnetism and gravity as two readings
   of one closure relation?
2. **Does the synchrotron `γ³` critical frequency share the relativistic origin of the Law-V budget cap?**
   If beaming (`1/γ`) and `ω_crit ∝ γ³` both come from `v_circ²+v²=c²`, the spectrum is a movement-budget
   fingerprint, not an electrodynamic accident.
3. **Is there a maximum synchrotron photon energy set by the spation cutoff?** As the turned wake
   approaches `ℓ_P`-scale curvature, the emission should depart from `γ³` — a falsifiable high-energy cutoff.
4. **Does the cyclotron line in a magnetised plasma tie to PM04's upper-hybrid?** `ω_uh² = ω_p² + ω_c²`
   should reuse the *same* native `ω_c` derived here — a consistency check across PM04/PM06.

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (Lorentz occlusion), E89 (bremsstrahlung/
deceleration radiation), [[PM03_EM_Waves_as_Coupled_Relay_Pulses]] (emission channel), Law V (movement budget).
**Downstream:** [[PM05_Magnetic_Reconnection_and_Solar_Flares_from_Wake_Topology]] (synchrotron from accelerated populations), astrophysical sources.
**Related:** EMC03 (orbit sense / handedness), koppa closure (orbit radius), [[PM04_Plasma_Oscillations_and_Debye_Shielding]] (upper-hybrid reuse of `ω_c`), [[feedback_no_borrowed_units]].
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PM06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces actually used: law_III (occlusion push), law_V (movement budget), bridge (koppa); PM01 field, E89 emission, PM03 pulse
- Phase thresholds (committed before run): P1 orbit drift <1%/period + ω_c <1% (native gain, no qv×B import) · P2 P∝γ⁴ exponent · P3 ω_crit∝γ³ · P4 beaming ≈1/γ
- Forbidden retroactive changes: re-import primitive qv×B to close the orbit then claim A; express ω_c/power/gain in µ_B/µ_N; external Lorentz boost for beaming; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (domain-specialized for PM06)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 orbit won't close from PM01 push | refine integrator timestep; check occlusion-gradient sign | **OPEN** the centripetal claim; report drift | re-import primitive `qv×B` and claim A |
| P1 `ω_c` only via `qB/m` SI | derive the native handed-swirl gain first | down-grade to **C** (gain imported) | quote `q`,`B` in SI as the mechanism |
| Any gain/power expressed in µ_B/µ_N | seek the native circulation expression | **units FAIL** — record, do not soften | quote the magneton, call it native |
| P2/P3 `γ` exponent ≠ 4 / 3 | tie to the E89 turned-wake ledger; recompute | mark prefactor **CONVERGENCE** | plug the exponent, claim native |
| P4 beaming ≠ `1/γ` | re-fold the Law-V budget at high `v` | **OPEN** the beaming; do not boost | insert an external Lorentz transform |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*PM06 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
