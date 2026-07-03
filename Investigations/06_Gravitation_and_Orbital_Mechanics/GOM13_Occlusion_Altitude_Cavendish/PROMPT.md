# The Occlusion-Altitude Cavendish Experiment

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether the overhead-mass occlusion of the convergent influx is separable, at any accessible altitude, from the Newtonian slab attraction it is degenerate with (the Bouguer term).
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

> **⚠️ FARMER correction (2026-07-03, J.C.Harvey directive) — the sin-dip law below is a
> TRANSCRIPTION ERROR against the founding occlusion principle.** `ΔF/F = sin δ` counts the planet
> as a TOTAL occluder of the solid angle it subtends (≈50% of the sky's influx blocked at the
> surface). But Law III occlusion is **transparent-relay and per-baryon**: blocking is proportional
> to the **mass column traversed** (R² cross-sections, EMC01 shadow cones) — "unless blocked, which
> means doing gravitational work." The 2026-07-03 pre-flight run confirmed it: sin-dip is excluded
> **47×** by existing precision-G records (JILA/LANL scatter ~5×10⁻⁴ vs predicted +2%), while the
> mass-column-proportional form lands on the **Bouguer gradient (~4.4×10⁻⁷ at the surface)** — the
> native occlusion signal is already measured in a century of gravimetry, degenerate with the
> Newtonian slab (honest CONVERGENCE). **The kill applies to the sin-dip transcription only; the
> branch survives with the per-baryon law.** Its corrected δ(h) ramp is ~10⁻⁹-class — below any
> current lock-in floor — so this flight as designed does not discriminate; E104's κ-correlation
> channel is the surviving falsifiable core. Every `sin δ` line below is retained as the historical
> record of the killed transcription.

## *A direct, benchtop-to-balloon test that separates SDT from General Relativity*

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (flagship — design-complete, unflown).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.
> **One line:** the Cavendish attraction between two *laboratory* masses should **rise with altitude**
> as `ΔF/F = sin(δ) ≈ √(2h/R)`, where `δ = arccos(R/(R+h))` is the horizon dip — a number GR and
> Newton both predict to be **exactly zero**, with no coordinate in either theory able to produce it.

---

## 1 · Executive Summary

In SDT, gravity is the mutual occlusion of the convergence flux: two masses each shadow the
incoming spation throughput from the other, and the unbalanced push drives them together. The
strength of that push scales with the **ambient flux intensity** at the apparatus. The Earth sits in
the lower sky and **occludes part of that flux** — so the ambient intensity at ground level is
*suppressed*, and it **recovers as you climb and the planet's shadow shrinks**. Therefore the
laboratory Cavendish force is not a constant: it grows with altitude along a fixed geometric law.

**In General Relativity and Newtonian gravity the force between two lab masses is `G m₁m₂/d²` — `G`
is universal and `m₁, m₂, d` are fixed, so the measured force is altitude-independent to all orders.**
The local *Earth* gravity `g` falls as `1/r²` (≈0.03% per km), but that is the Earth-mass term, which
a horizontal Cavendish balance is built to reject; the *lab-mass* term has no altitude dependence in
either classical theory. **SDT predicts it rises; GR/Newton predict a flat line. There is no overlap,
and no free parameter on either side.** A single instrument flown up a continuous altitude profile
decides between them. **We expect:** `ΔF/F ≈ +1.8%` by 1 km, `+5.3%` by Everest, `+11%` by 40 km,
following `√(2h/R)` — and, as an independent lock, the apparatus's orientation tolerance (tilt
budget) growing as `δ`, equal *as a number* to `ΔF/F`.

---

## 2 · The Fork, Stated Without Escape

| quantity | Newton / GR | SDT |
|---|---|---|
| lab-mass Cavendish force `F(h)` | constant (`G m₁m₂/d²`) | `F₀·(1 + sin δ)` , `δ = arccos(R/(R+h))` |
| fractional rise `ΔF/F` to 40 km | `0` (exactly) | `+11.15%` |
| orientation/tilt budget `β(h)` | set by instrument leveling, **altitude-independent** | `= δ = arccos(R/(R+h))` |
| functional form vs `h` | flat | `√(2h/R)` (rising, no ceiling until orbit) |

The two SDT observables — a **force ratio** and an **angle** — are predicted to be the *same number*:
`ΔF/F = sin δ` and `β = δ`, so `ΔF/F / β = sin δ / δ = 1` to <1% up to 50 km (§4). No mundane
systematic raises a force by 11% **and** opens an orientation cone by 0.112 rad in lockstep. The
correlation is the mechanism, and the mechanism is what no other theory possesses.

---

## 3 · Theoretical Framework (SDT)

### 3.1 The occlusion force and the ambient flux
From Law III, the occlusion force between two bodies is `F = (π/4) P R₁²R₂² / d²`, where `P` is the
**local convergence pressure** — the intensity of the spation throughput available to be shadowed.
For a fixed apparatus (`R₁, R₂, d` constant), **`F ∝ P`**. The classical `G` is therefore not
fundamental; it is `G_eff ∝ P`, the local flux intensity wearing Newton's clothes.

### 3.2 Earth's shadow and the altitude law
The convergence flux arrives from `4π` steradians. A body at height `h` above a planet of radius `R`
has the planet subtending a cone of angular radius `α = arcsin(R/(R+h))` about the nadir; the planet
**occludes** that cone. The *un-occluded* solid-angle fraction is

```
f(h) = (4π − 2π(1 − cos α)) / 4π = (1 + cos α)/2 = (1 + sin δ)/2 ,   δ ≡ arccos(R/(R+h))
```

where `δ` is the **horizon dip**. With `P(h) ∝ f(h)` and `F ∝ P`, the fractional Cavendish-force
change relative to the surface (`f(0)=½`) is

```
ΔF/F(h) = f(h)/f(0) − 1 = 2 f(h) − 1 = sin δ = √( h(2R+h) ) / (R+h)
```

and for `h ≪ R` this is the clean square-root law

```
ΔF/F(h) ≈ √(2h/R).
```

**Verified prediction curve** (R = 6 371 km):

| h (km) | dip δ | **ΔF/F** | √(2h/R) | locked ratio `ΔF/F ÷ δ(rad)` |
|---|---|---|---|---|
| 0.5 | 0.718° | **+1.25%** | 1.25% | 1.0000 |
| 1   | 1.015° | **+1.77%** | 1.77% | 1.0000 |
| 5   | 2.269° | **+3.96%** | 3.96% | 0.9997 |
| 8.848 (Everest) | 3.018° | **+5.27%** | 5.27% | 0.9995 |
| 20  | 4.534° | **+7.91%** | 7.92% | 0.9990 |
| 40  | 6.404° | **+11.15%** | 11.21% | 0.9979 |
| 50  | 7.155° | **+12.46%** | 12.53% | 0.9974 |

### 3.3 The independent lock — the tilt budget
A horizontal balance keeps both test masses in the un-occluded sky, where the driving flux is
symmetric. Tilt the measurement axis by an angle and the down-going arm rotates toward the Earth's
occlusion cone; the flux asymmetry it picks up is the contaminating term. The apparatus reads true so
long as the axis stays within the clear cone — i.e. the **tilt budget is the horizon dip**,
`β(h) = δ = arccos(R/(R+h))`. Because `ΔF/F = sin δ` and `β = δ`, the two observables obey

```
ΔF/F  =  sin(β)  ≈  β     (β in radians),
```

a relation with **zero free parameters** that a single flight measures twice over, independently.

### 3.4 The load-bearing assumption (state it; test it)
**H1 (decoupling):** the *macroscopic gravitational* occlusion scales with the ambient,
Earth-shadowed convergence flux (`F_grav ∝ f(h)`), while the *electromagnetic* forces that set the
torsion fibre's restoring constant `κ` are local charge-redirection (EMC03) and do **not** scale with
that ambient flux (`κ ≈ const`). The measured angle is `θ = F_grav/κ`, so the signal survives only if
gravity and EM couple to the ambient flux *differently*. **If instead `κ ∝ f(h)` too, the ratio
cancels and `ΔF/F → 0`** — which would itself be a clean SDT result: gravity and EM share one
coupling. So the experiment is, at root, a test of whether **gravity and electromagnetism see the
ambient convergence flux the same way.** GR + the Standard Model answer "both constant"; SDT answers
"gravity rides the ambient flux, EM rides the local handedness." This is the deep fork the altitude
profile resolves, and H1 must be derived from `laws.hpp` before flight (gate-zero, §10).

---

## 4 · Why GR/Newton *cannot* produce this (the irrefutability argument)

1. **No coordinate.** `arccos(R/(R+h))` is a **line-of-sight-to-the-limb** quantity. It is meaningful
   only if something streams in from the sky and the planet blocks it. GR's gravity is curvature
   between the masses; QED/EM has no sky term either. Neither theory contains a variable that *can*
   equal `sin(arccos(R/(R+h)))` for a lab-force ratio. SDT does not predict a *different number* than
   GR — it predicts a number in a coordinate GR does not possess.
2. **The lab term is altitude-flat in GR.** `F = G m₁m₂/d²`; vary `h`, nothing on the right-hand side
   moves. The `1/r²` weakening of *Earth* gravity (0.03%/km) is a different term and is rejected by
   the horizontal geometry.
3. **The lock is unforgeable.** A force-raising systematic and an orientation-cone-opening systematic
   are physically unrelated; nothing but a single occlusion geometry makes them the same number.

---

## 5 · Confound Kill-List (the discriminator is the *functional form*)

Every mundane altitude-correlated systematic and how it is separated. **SDT ∝ `√(2h/R)` — rising,
geometric, still climbing above the atmosphere. Confounds die exponentially with the air.**

| confound | scaling with `h` | null / discriminator |
|---|---|---|
| air **buoyancy / density** on masses & fibre | `∝ exp(−h/H)`, `H≈7–8 km` | hard-vacuum enclosure (<10⁻³ Pa); residual follows `exp`, **gone by 25 km**; SDT still rising |
| **convection / thermal** gradients | `∝` local `ΔT`, atmospheric | active thermal stage, ±1 mK; monitor; not `√h` |
| **pressure** on enclosure / outgassing | `∝ P_atm ∝ exp(−h/H)` | sealed vacuum cell; getter; `exp` not `√h` |
| **vibration / gondola sway** | broadband, platform-driven | passive+active isolation; lock-in at fibre period; sway is not monotonic in `h` |
| **magnetic / solar-wind** torque at altitude | rises with `h` but tracks geomagnetic/solar, not `√h` | µ-metal + superconducting shield; non-magnetic masses (Si/Cu); correlate-out vs magnetometer |
| **Coriolis / centrifugal** (Earth spin) | known, latitude-fixed | computed and subtracted; constant on a given flight |
| **`g`-gradient** changing the balance set-point | `∝ 1/r²` (0.03%/km), vertical | horizontal signal is orthogonal; monitored by onboard gravimeter |

**The decisive move:** fly *continuously through and above the air*. Below ~15 km, confounds and SDT
both rise and are entangled. Above ~25 km the atmosphere is `<5%` of sea-level density and every
`exp(−h/H)` term has collapsed — **yet SDT predicts the signal is still climbing** (`+7.9%` at 20 km,
`+11%` at 40 km). A monotone `√h` rise persisting into vacuum, *with the tilt budget tracking it in
radians*, is a signature no atmospheric or instrumental effect can mimic.

---

## 6 · Apparatus (the gondola Cavendish)

- **Torsion balance.** Dumbbell of two `m₂` test masses (tungsten or Au, `~50 g` each) on a beam
  `2ℓ ≈ 10 cm`, hung from a fused-silica fibre (`κ ≈ 10⁻⁸ – 10⁻⁹ N·m/rad`), free period `T ≈ 200–600 s`.
- **Attractor.** Two `m₁` source masses (`~1–2 kg` W) on a rotatable carousel, reversed each cycle to
  modulate the signal at a known frequency (kills DC drift; the Cavendish signal lives at the carousel
  reversal frequency only).
- **Readout = the calibration, and it must be MECHANICAL, not gravitational.** Angle by multi-pass
  optical lever or fibre interferometer (`<10 nrad`). **Convert to force via the fibre constant `κ`
  obtained from the free-oscillation period and the known moment of inertia**, `κ = I (2π/T)²`. This
  makes the force an *absolute mechanical* reading independent of the convergence pressure — the single
  most important design choice, because a gravity-referenced calibration would cancel the SDT signal
  (§3.4). Cross-check `κ` with an **electrostatic comb** (a known, EM-sourced reference force);
  agreement of mechanical-`κ` and electrostatic-`κ` is itself a probe of H1.
- **Tiltmeter + 2-axis gimbal.** Bias the measurement axis off-horizontal in controlled steps; map the
  reading vs tilt at each altitude to extract `β(h)` directly. (`β` is read as the tilt at which the
  contaminating term reaches a fixed fraction of signal.)
- **Environment.** Hard-vacuum cell (<10⁻³ Pa, getter-pumped), two-stage thermal control (±1 mK),
  µ-metal + (optionally) superconducting magnetic shield, non-magnetic everything.
- **Onboard truth sensors.** Absolute gravimeter (monitors `g(h)`, the shared `1/r²` row),
  3-axis magnetometer, pressure/temperature, IMU + GNSS altitude to ±5 m. Every confound row in §5
  gets its own witness channel for regression.

---

## 7 · Platform — the cascade balloon (Harvey staged-expansion)

**The idea.** A conventional zero-pressure balloon expands until the latex bursts (~30–40 km). Instead,
seal the primary to a **pinch-valve manifold** feeding a series of initially-deflated balloons. As
ambient pressure falls and the primary reaches its stretch limit, the rising internal pressure (the
"vacuum prising" of the thinning air outside) **cracks the next pinch valve**; helium floods chamber 2,
then 3, then 4 — the *system* volume keeps growing in stages while **no single envelope is ever driven
to burst.** Begin with 4 primaries on the manifold, end with 16 inflated chambers: total expandable
volume rises ~4×, and so does the float ceiling.

**Float-altitude physics.** Neutral buoyancy is `ρ_air(h)·V = m_total`. With `ρ_air ∝ exp(−h/H)` and a
staged total volume `V`, the float altitude is `h_float = H·ln( ρ₀ V / m_total )`. Each cascade stage
multiplies `V` (raising `h_float` by `H·ln(stage-ratio)`), at the cost of the added envelope mass in
`m_total`. **Honest ceiling:** for ultrathin polyethylene the practical limit for any buoyant device
is `~45–53 km` (cf. the JAXA BU60-1 record, 53.0 km) — the envelope mass eventually wins. The cascade
*reaches* that ceiling reliably and *floats* there rather than bursting through it.

**The "terminus."** At `h_float` the system hovers at neutral buoyancy — the natural long-dwell station
for the experiment (hours at fixed altitude = low-noise integration). Above the buoyant ceiling there
is no lift; the romantic picture of a helium platform drifting to the exobase and loitering in the
solar wind is not buoyancy physics (no air to float on, no propulsion), so **treat ~50 km as the
balloon terminus** and hand the higher profile to a sounding rocket / cubesat (§9). What matters: 50 km
is *deep* in the divergence zone — atmosphere `<10⁻³` of sea level, SDT signal `+12.5%` and still rising.

**Flight profile for the physics.** Slow, *continuous* ascent (1–3 m/s) so the `√h` curve is sampled
densely from 0 to ceiling; long float at the terminus for the high-altitude anchor point; carousel
reversals throughout; tilt sweeps at a ladder of fixed altitudes (e.g. 0, 5, 10, 20, 30, 40, terminus).

---

## 8 · Measurement Protocol

1. **Ground truth.** Full sea-level Cavendish run to fix `F₀`, `κ` (mechanical *and* electrostatic),
   and the systematic floor. Repeat at a second ground elevation (a mountain lab) as a static check
   of the low-`h` `√(2h/R)` (`+1.8%` per the 1-km point) before committing helium.
2. **Continuous ascent.** Log `θ(t)`, carousel phase, and all witness channels at high rate; bin by
   altitude to recover `F(h)`. Target precision per altitude bin: `<0.3%` on `F` (well inside the
   `+1.8%`-at-1 km signal).
3. **Tilt sweeps.** At each ladder altitude, gimbal the axis ±a few degrees; extract `β(h)`.
4. **The three tests, scored independently:**
   - **T-Force:** does `F(h)/F₀ − 1` follow `sin(arccos(R/(R+h)))`, *not* a constant and *not*
     `exp(−h/H)`?
   - **T-Tilt:** does `β(h)` follow `arccos(R/(R+h))`?
   - **T-Lock:** does `[F(h)/F₀ − 1] = sin(β(h))` hold to the joint error bar — the unforgeable
     correlation?

---

## 9 · Success / Falsification Criteria

- ✅ **PASS (Class A — SDT, GR excluded):** `F(h)` rises, fits `sin(arccos(R/(R+h)))` with `χ²/dof≈1`,
  is statistically distinct from both `0` and `exp(−h/H)` above 25 km, **and** the lock `ΔF/F = sin β`
  holds. This is a measured departure from GR in a coordinate GR cannot reach.
- ✅ **QUALIFIED (Class C):** a monotone rise consistent with `√h` is seen but the high-altitude anchor
  or the tilt-lock is marginal (single flight, limited ceiling). Compelling, needs the rocket leg.
- ⚠️ **PENDING (Class D):** instrument resolves `<0.3%` but the flight ceiling/duration can't separate
  `√h` from residual `exp` — inconclusive; re-fly higher/longer.
- ❌ **FAIL (Class F):** `F(h)` is **flat** to `<0.3%` through 40 km. Then either H1 is false (gravity
  and EM share the ambient coupling and the ratio cancels) or the occlusion-altitude model is wrong.
  Report it as a clean kill — GR/Newton predicted exactly this, and SDT must concede the macroscopic
  coupling does not ride the ambient flux. **A flat line falsifies the prediction outright.**

---

## 10 · Gate-Zero, Outputs, Dependencies

**Gate-zero (do before any hardware):** from `laws.hpp`, derive (a) that the macroscopic occlusion
force scales as the ambient un-occluded flux `f(h)` — i.e. `G_eff ∝ P_local` — and (b) **H1**: that the
fibre's EM restoring constant does *not* share that scaling (EMC03 handedness is local, not ambient).
Produce the predicted `ΔF/F(h)`, `β(h)`, and the lock to the digit, plus the magnitude check that the
sea-level value reproduces the measured `G`. *If H1 cannot be established, the signal cancels and the
experiment is not worth flying — so this gate is the real keystone.*

**Outputs:** `OCCLUSION_ALT_DERIVATION.md` (gate-zero + the curves); `occlusion_altitude.cpp`
(predicted `F(h)`, `β(h)`, lock, confound-form table, from `laws.hpp`); `INSTRUMENT_SPEC.md`
(balance + cascade-platform engineering); `FLIGHT_ANALYSIS_PLAN.md` (binning, regression against
witness channels, the three tests); `VERDICT.md` (A/C/D/F).

**Dependencies.** *Upstream:* Law III occlusion; EMC03 (charge as local handedness → H1); the
convergence-pressure / receding-CMB ambient-flux picture; the occlusion-saturation thread.
*Downstream:* the Casimir version (`Occlusion_Triad`, adds the plate-shadow `→ 1/d⁴` gate); the
sounding-rocket / cubesat leg that pushes to LEO where `ΔF/F → +34%` and the lock tightens.
*Related:* the flyby anomaly (`K = 2v_rot/c`, the co-rotating-field cousin of this) and the unexplained
lab-to-lab `G` scatter — **re-examine the `G` record now for a correlation with lab elevation;
the first data point of this experiment may already be sitting in the literature.**

---

### The single sentence to hold onto
**Carry one Cavendish balance up a continuous column of air into vacuum; GR says the needle cannot
move; SDT says it climbs as `√(2h/R)` while the orientation cone opens to the same number in radians —
and only one of those is what the needle does.**
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM13
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: bridge::koppa_*, depth_closure::, no G/M
- Phase thresholds (committed before run): 0.03%, 1.8%, 5.3%, 11%, 11.15%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*GOM13 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
