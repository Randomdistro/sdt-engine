# FLM03 — The Spation Rotation Kinematic Map

> **Author:** J. C. Harvey, Melbourne. **Status:** RESOLVED (tool passes 4/4; recorded `RUN_LOG.md`, 2026-06-26).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/state28d.hpp>` (→ `<sdt/laws.hpp>`). *Retrofit note:* the tool currently declares
> its CODATA constants locally; §9 lists the pull-from-`laws::measured` cleanup. No fitted parameters.

---

## ⓪ Golden Rule — five answers up front

1. **What don't we know?** What is the *rotation profile* `v(r)` of the proton's spation field — how fast does
   the medium circulate as a function of radius, from inside the proton surface out to the hydrogen orbits?
2. **Why does it matter?** Every downstream "seat speed" claim (the neutron's 1.83c counter-rotating seat in
   NP20; the electron-as-driven-orbit; the αc Bohr velocity) assumes a single monotone `v(r)`. If that profile
   is not derivable from proton geometry alone, those claims inherit a free parameter. This pins it down.
3. **How will we find out?** Derive `ϟ_H` from proton geometry, build `v(r) = (c/ϟ_H)·√(R_p/r)`, and check it
   reproduces the three independently-known anchors (1.83c at R_p, c at the c-boundary, αc at a₀) with **zero**
   fitted knobs.
4. **What would prove us wrong?** Any anchor missed beyond tolerance; a non-monotone profile; the c-boundary
   *not* landing on the classical electron radius; `k(a₀) ≠ 1/α`. (See §8.)
5. **How will we know we're done?** Dual verdict — **prompt:** all three anchor proofs + the driven-orbit
   resonance PASS; **physics:** the profile is COMPUTED-from-geometry, no fitted parameter. *(Achieved: 4/4.)*

---

## 1. Executive Summary

The proton is a vortex; the spation medium around it circulates. **Does a single geometric law fix how fast,
at every radius — with no free parameter?** FLM03 derives the koppa `ϟ_H = (1/α)√(R_p/a₀)` from proton geometry
and builds the rotation profile `v(r) = (c/ϟ_H)·√(R_p/r)`. **We expect** this one curve to pass through three
independently-anchored velocities: **1.83c at the proton surface**, **c exactly at the c-boundary** (which
should coincide with the classical electron radius r_e), and **αc at the Bohr radius** — and to make the
electron's orbital velocity *equal the proton's own field velocity* at a₀ (a resonance, not a coincidence).
After: we know the seat-speed ladder the whole framework leans on is forced by geometry, not assumed.

## 2. Physical Context

**Conceptual picture.** A spinning vortex drags the surrounding superfluid; far away the drag is gentle, close
in it is violent. The proton's field rotation `v(r)` falls off from the surface outward. The question is the
*law* of that falloff and whether the radii where physics already has names — the proton surface R_p, the
classical electron radius r_e, the Bohr radius a₀ — sit on it at the velocities we'd independently expect.

**Key variables.**
- `R_p` — proton boundary/displacement radius (≈ 8.414e-16 m). *Never "charge radius."*
- `a₀` — Bohr ground-state radius; `r_e` — classical electron radius (2.818e-15 m).
- `ϟ_H` (koppa_H) — the hydrogen koppa, dimensionless, `= (1/α)√(R_p/a₀) ≈ 0.546`.
- `v(r)` — field rotation velocity [m/s]; `k(r) = c/v(r)` — the local k-rung (dimensionless).
- `ω(r) = v/r`, `T(r) = 2πr/v` — angular velocity and period.

**Why it connects.** The 1.83c surface seat is reused by **NP20** (neutron mass *and* moment from one seat)
and the **Depth-Closure** paper (v = c√z, Earth→proton → 1.830c). FLM03 is the geometric root those share;
it also feeds **FLM04** (the kinematic map) and the atomic-orbit work (the electron as a driven orbit).

## 3. Theoretical Framework

**Axiom / first principle.** Field rotation obeys the koppa law `v_surface = c/ϟ`, with `ϟ = v²R/c²` the SDT
replacement for `GM/c²` (no G, no M). For hydrogen the koppa is fixed by geometry:

```
ϟ_H = (1/α) · √(R_p / a₀)                         # derived from proton geometry + α (derivation basis)
v(r) = (c / ϟ_H) · √(R_p / r)                      # inverse-√r rotation profile
k(r) = c / v(r)                                    # local k-rung
r_c  = R_p / ϟ_H²   (radius where v = c)           # the "c-boundary"
```

**Theorems that must hold (the anchors).**
- **T1** `v(R_p) = c/ϟ_H = 1.831c` — the proton-surface seat is superluminal at exactly 1/ϟ_H.
- **T2** `v(r_c) = c`, and `r_c` coincides with the **classical electron radius r_e** — the c-boundary is r_e.
- **T3** `v(a₀) = αc` — at the Bohr radius the field velocity is the electron orbital velocity, and `k(a₀)=1/α`.
- **T4 (resonance)** the proton's field velocity *at a₀* equals the measured electron orbital velocity αc.

**Constraints.** Inputs limited to the derivation basis `{ℓ_P, c, ℏ, α, m_e, m_p}` + R_p, a₀, r_e as measured anchors.
No G/M/GM; no fitted parameter; no "charge radius"; superluminal `v>c` is physical here (field rotation inside
the c-boundary), **not** a particle signalling speed — flag the regime, do not invoke SR-γ.

## 4. Investigation Strategy

**Phase I — the rotation profile and its three anchors (the spine).**
- *Goal:* build `v(r)` from `ϟ_H` and verify T1–T3.
- *Method:* `state_factory::proton_nuclear()` → `ϟ_H = (1/α)√(R_p/a₀)`; `v(r)=(c/ϟ_H)√(R_p/r)`; evaluate at
  R_p, r_c, a₀; tabulate v/c, k, ω, T across ½R_p → 25a₀.
- *Pre-committed thresholds:* **FLM03-1a** |v(R_p)/c − 1/ϟ_H| < **0.01%**; **FLM03-1b** |v(r_c)/c − 1| < **0.01%**
  *and* r_c ≈ r_e; **FLM03-1c** |v(a₀) − αc|/αc < **0.1%**.
- *Failure trigger:* any anchor over tolerance, or a non-monotone v(r). *Gate:* Part III forbidden until 1a–1c PASS.

**Phase II — state geometry sanity (the ground).**
- *Goal:* confirm the proton/electron `State28D` geometry feeding ϟ_H is the expected one.
- *Method:* print proton/electron `T_2` (radius) and `T_3` (area); compute the occlusion factor `E(a₀)`.
- *Pre-committed:* proton `T_2 = R_p` to machine precision; `E(a₀)` finite and ≪ 1. *Out of scope:* deriving the
  Coulomb/gravity ratio here — that is EMC01/GOM02 (`laws::law_III`); FLM03 only consumes the geometry.

**Phase III — the electron as a driven orbit (the payoff).**
- *Goal:* show the electron orbital velocity is *set by* the proton field, not independent.
- *Method:* evaluate the proton field velocity at a₀; compare to measured αc.
- *Pre-committed:* **FLM03-4a** |v_field(a₀) − αc|/αc < **0.1%**. *Failure trigger:* > 0.1% ⇒ the resonance is
  not exact ⇒ PIVOT to check ϟ_H provenance, do **not** widen the tolerance.

**Out of scope (whole investigation):** time-dependence/spin-down, multi-electron atoms, the nuclear-interior
sub-R_p profile beyond the single ½R_p sample, and any GM-based orbital comparison.

## 5. Success Criteria

- ✅ **PASS (Class A–B, Derived/Computed):** all of FLM03-1a/1b/1c and 4a within their pre-committed tolerances,
  v(r) monotone, r_c = r_e, k(a₀)=1/α, **no fitted parameter.** *Publish:* "the proton field rotation ladder is
  fixed by geometry; 1.83c→c→αc and the electron-orbit resonance follow with no knob."
- ✅ **QUALIFIED (Class C, Convergence):** anchors met but with ≥1 approximation (e.g. r_c=r_e only to ~1%).
- ⚠️ **QUALIFIED PENDING (Class D, Computed):** anchors traced to ϟ_H but one residual > tolerance; interpretation
  incomplete.
- ❌ **FAIL (Class F):** an anchor missed by > order, or v(r) non-monotone, or r_c far from r_e.

**Dual verdict reminder:** prompt-completion (proofs run + recorded) is separate from physics-class (how derived).

**Realized verdict (2026-06-26):** **PASS — 4/4.** 1a/1b at 0.0000%; 1c and 4a at 0.0833%; r_c = 2.823e-15 m ≈
r_e; k(a₀) = 136.92 ≈ 1/α. Physics class **B (Computed-from-geometry, no fitted parameter)** — the single
sub-0.1% residual (αc at 0.083%) keeps it shy of pure-A. See `RUN_LOG.md`.

## 6. Outputs

1. **`flm03_spation_rotation_map.cpp`** — standalone C++20 tool (the implementation; prints Parts I–III + the
   v(r) ladder table and the four proofs).
2. **`RUN_LOG.md`** — the recorded run (build command, 4/4 PASS, anchor table, certification, cross-beam). *Done.*
3. *(optional, on request)* `flm03_ladder.csv` — the radius/v/k/ω/T table for plotting.

## 7. Dependencies & References

**Upstream (required):** `state28d.hpp` (`state_factory::proton_nuclear`); the koppa law `ϟ = v²R/c²`
(`bridge::koppa`); PPT01 (velocity budget, R/a). **Downstream (consumes this):** NP20 (the 1.83c counter-rotating
seat → neutron mass + moment); FLM04 (rotation kinematic map); the atomic-orbit / driven-electron work.
**Related (parallel):** the Depth-Closure paper (v = c√z → 1.830c, independent route to the same seat);
EMC01/GOM02 (the force ratio, which FLM03 deliberately does *not* re-derive).

## 8. Falsification Tests

| Test | Hypothesis | Predicted | If FAIL |
|------|-----------|-----------|---------|
| T1 | v(R_p) = c/ϟ_H | 1.8316c, err < 0.01% | seat speed not geometric → NP20/depth-closure inherit a knob |
| T2 | c-boundary = r_e | v(r_c)=c and r_c≈2.818e-15 m | the c-boundary is not the classical electron radius → coincidence broken |
| T3 | v(a₀) = αc, k(a₀)=1/α | err < 0.1%, k≈137 | the Bohr rung is not the 1/α rung |
| T4 | electron orbit = proton field at a₀ | err < 0.1% (resonance) | electron velocity is independent, not driven |
| T5 | v(r) monotone decreasing | strictly falls R_p→25a₀ | profile not a clean inverse-√r law |

**Recovery:** a missed anchor PIVOTs to re-deriving ϟ_H from geometry (never to inputting the target velocity);
a broken r_c=r_e coincidence is reported as OPEN, not smoothed.

## 9. Implementation Notes

- **Double precision throughout;** radii span ~10 orders (R_p → 25a₀). Use dimensionless ratios (v/c, k) for the
  proofs to avoid scale issues.
- **Superluminal regime is expected** inside r_e; the `regime()` label flags it. Do not "fix" v>c with γ — it is
  field rotation, not a signal.
- **Retrofit cleanup (known deviation):** the tool declares CODATA constants locally (lines ~25–36) instead of
  pulling `laws::measured::{c, alpha, a_0, r_e, R_p, m_e, m_p, hbar}`. Values match CODATA 2018, but per the
  Engine rule this should be refactored to consume `laws.hpp` so there is one source of truth. Low risk, tidy-up.
- **Plot hints:** v/c vs log(r) (monotone falloff through the three anchors); k(r) vs r (should hit 1/α at a₀).

## ⑩ Adaptive Execution Protocol

**Pre-Run Commitment Block** (copied to `RUN_LOG.md`): completion target A; physics class hoped Computed/Derived;
CALIBRATED budget **0**; phase thresholds P1 {1a:0.01%, 1b:0.01%, 1c:0.1%}, P3 {4a:0.1%}; forbidden retroactive
changes: widening any tolerance, inputting a target velocity, adding a fitted scale.

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden |
|---|---|---|---|
| 1a |v(R_p)/c − 1/ϟ_H| > 0.01% | re-derive ϟ_H from proton `T_2`, a₀ | OPEN the koppa provenance | input 1.831 as a target |
| 1b r_c ≠ r_e (>1%) | recompute r_c = R_p/ϟ_H²; check r_e value | report coincidence OPEN | force r_c=r_e by tuning ϟ_H |
| 1c/4a |v(a₀) − αc| > 0.1% | re-check α and a₀ provenance | mark Class D, residual noted | widen to pass |
| T5 non-monotone | re-check `field_velocity` √(R_p/r) | OPEN profile law | hide the non-monotone rows |

**Allowed:** numeric re-derivation, alternative geometric routes to ϟ_H, adding table rows.
**Disallowed:** retro-PASS, inputting any anchor velocity, a fitted scale, treating v>c via γ.
**Dual verdict:** prompt (proofs run + `RUN_LOG.md` written) vs physics class (Computed-from-geometry).

---

**Realized:** PASS · 4/4 · Class B · `RUN_LOG.md` 2026-06-26. The 1.83c → c → αc ladder and the driven-orbit
resonance are fixed by proton geometry with no fitted parameter; the one sub-0.1% residual (αc, 0.083%) is the
only thing between this and pure Class A.
