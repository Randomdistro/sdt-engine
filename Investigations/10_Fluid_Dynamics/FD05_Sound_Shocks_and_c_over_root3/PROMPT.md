# FD05 — Sound, Shocks, and the c/√3 Ceiling

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-28).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
> **Domain:** Fluid Dynamics (SDT lattice mechanics).

---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is `c_s = c/√3` a *genuine native consequence of 3-D lattice isotropy*
   (i.e. `c_s = c/√D` with D=3, derivable **without** assuming the radiation equation of state), or is
   it merely the imported relation `P = u/3` differentiated — an identity wearing a derivation's clothes?
   And: is `c/√3` a property of the **vacuum lattice** or only of a **relativistic fluid living on it**?
2. **Why does it matter?** — If the `1/3` is forced by D=3, then `c/√3` is a *measurement of the
   dimensionality of space*, and it supplies the BAO sound speed **independently** of CR04/CR08/CR09
   (which currently obtain it circularly — see §7). If it is only the radiation EoS re-differentiated,
   FD05 adds nothing and must say so. Downstream: FD09 (wave drag), the FLM10 dispersion relation.
3. **How will we find out?** — Seven gated phases (§④). The native isotropy derivation (P2) runs
   **before** any `law_I::P_rad` is touched; touching it earns at most Class C (§⑤ anti-tautology gate).
4. **What would prove us wrong?** — §⑧, seven falsifiers with numeric triggers and **real failure
   modes** — including the LIGO test (F2) that can genuinely come out the wrong way.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

---

## 1. Executive Summary

Sound is a **compression-relay wave** in the spation lattice: a transient densification of displaced
volume that heals outward at `c_s = √(dP/dρ)`. This investigation asks that one mechanism to do four
things, in increasing order of how much it can teach us. **(a)** Ordinary-fluid sound (air ≈343 m/s,
water ≈1481 m/s) must fall out of the medium's *measured* compressibility, re-narrated as relay
healing. **(b)** The ceiling `c_s = c/√3 ≈ 1.7309×10⁸ m/s` must be **derived from 3-D isotropy alone** —
the kinetic identity `P = (1/D)·u` with D=3 — *without* importing the radiation EoS; the prediction
`c_s = c/√D` makes `c/√3` a readout of dimensionality. **(c)** That ceiling must be shown to belong to
a **relativistic fluid on the lattice**, *distinct from the vacuum's own elastic modes* (which travel at
`c`); the discriminator is LIGO's `c_gw = c` to 1 part in 10¹⁵. **(d)** A **shock** (Mach cone, sonic
boom) must be the *same* super-relay disturbance as E57's verified Cherenkov radiation — one mechanism,
two relay speeds. **Falsify** if the `1/3` does not follow from isotropy, if the vacuum modes collapse
onto `c/√3`, if the stiffness curve is not single-valued, or if boom and Cherenkov need separate
mechanisms.

## 2. Physical Context

A disturbance in a compressible medium propagates at a speed fixed by how stiffly the medium resists
compression. In SDT the medium is the corner-sharing tetrahedral relay lattice (cell closure `ℓ_P`,
relay/tick speed `c`; FLM08/CONDENSA), and "compression" is a transient increase in displaced lattice
volume per region. The continuum fields of fluid dynamics are the coarse-graining of this granular relay
(FD01/FD02).

**The distinction this prompt refuses to blur.** There are *two* families of wave here and the original
FD05 conflated them:

- **Vacuum-lattice modes** — the elastic responses of the empty lattice. CONDENSA splits these into a
  **transverse** (shear/twist) branch `c_T` and a **compressive/longitudinal** branch `c_L`. Light/EM is
  `c_T`; gravitational waves are *also* transverse (spin-2, transverse-traceless) and measured at `c`.
  Whether a *propagating* longitudinal vacuum mode exists at all is open (GOM06: "no breathing mode").
- **Fluid sound on the lattice** — the coarse-grained sound speed of *matter* (a gas, a plasma, a
  relativistic relay-gas) sitting on the lattice. This is the `c_s = √(dP/dρ)` family, ceiling `c/√3`.

`c/√3` is a **fluid** result (the relativistic relay-gas / pre-Clearing coupled era), **not** a vacuum
elastic speed. Keeping these apart is half the physics.

| Symbol | Meaning | Dimensions |
|---|---|---|
| `P` | lattice/fluid pressure | Pa |
| `ρ` | mass (displaced-volume) density | kg m⁻³ |
| `u` | energy density (radiation: `u = aT⁴`) | J m⁻³ |
| `c_s` | sound (compression-relay) speed | m s⁻¹ |
| `c` | relay tick speed | m s⁻¹ |
| `w = P/(ρc²)` | stiffness / EoS ratio | – |
| `D` | spatial dimensionality (=3, but kept symbolic in P2) | – |
| `c_T, c_L` | vacuum transverse / longitudinal mode speeds | m s⁻¹ |
| `M = v/c_s`, `θ` | Mach number, cone half-angle (`sinθ = 1/M`) | –, rad |
| `δ` | shock thickness (∼ few mean free paths λ; vacuum: few ℓ_P) | m |
| `ω(k)` | dispersion relation of the lattice | s⁻¹ |

Regimes span ≈12 orders in `c_s`: cold gas (`w→0`) to the radiation ceiling (`w=1/3`).

## 3. Theoretical Framework (SDT axioms only)

**(3.1) Sound speed from compressibility.** A perturbation `ρ→ρ+δρ` raises pressure by
`δP = (dP/dρ)δρ`; continuity + the FD01 Euler momentum balance give the linear wave equation
`∂²ₜ(δρ) = (dP/dρ)∇²(δρ)`, hence `c_s = √(dP/dρ)`. For an ideal gas `P = ρR_gT ⟹ c_s = √(γR_gT)`
(`γ,R_g,T` are MEASURED-INPUT; the relay narration is native).

**(3.2) The native `1/3` — the load-bearing step (DERIVE, do not import).** Consider an isotropic gas
of relay excitations each moving at speed `c` in D spatial dimensions. The momentum flux across any
plane (the pressure) is the energy density times the mean-squared direction cosine onto the plane normal:

```
P = u · ⟨cos²θ⟩_sphere = u / D        (in D=3: ⟨cos²θ⟩ = 1/3  ⟹  P = u/3)
```

`⟨cos²θ⟩ = 1/D` is pure 3-D geometry (the same `1/3` that makes `v_x² = v²/3` for isotropic velocities).
For a relativistic relay-gas the inertia is the energy density, `ρ_eff c² = u`, so

```
c_s² = dP/d(ρ_eff c²) = (1/D) · d(u)/d(u) = 1/D   ⟹   c_s = c/√D    [D=3: c/√3 = 0.57735 c]
```

**This is the test that can fail.** If the lattice's *statistically isotropic but tetrahedrally
frustrated* geometry (the 0.103 r kissing-shell gap, the 7.356° deficit; FLM08) makes `⟨cos²θ⟩` deviate
from exactly `1/3`, then `c_s ≠ c/√3` by that amount — a **fingerprint of the lattice**, or a problem.
Computing `⟨cos²θ⟩` over the actual CRN bond directions (not an assumed continuum sphere) is the native
content. *Consuming `law_I::P_rad = u/3` instead of deriving it is the tautology to avoid (§⑤ gate).*

**(3.3) Vacuum modes vs fluid sound — the LIGO discriminator.** The vacuum's transverse branch carries
light at `c`; gravitational waves are transverse and measured at `c` (GW170817: `|c_gw−c|/c < 10⁻¹⁵`).
If a naïve "spacetime-as-elastic-solid" reading puts the *longitudinal/compressive* vacuum mode at
`c/√3`, that predicts a **scalar gravitational-wave polarization at 0.577 c** — excluded by the GW
speed/polarization bounds. So either (i) there is no propagating longitudinal vacuum mode (the
"compression" SDT calls gravity is the *static* hinge-closure depth gradient, not a sound; GOM05/GOM06),
or (ii) the longitudinal vacuum mode is also `c`. Either way **`c/√3` must NOT be a vacuum mode** — it is
the *fluid* sound of a relativistic relay-gas. P4 tests this explicitly; getting it wrong is an F.

**(3.4) Shock = super-relay disturbance (one mechanism with E57).** For a source at `v > c_s` the medium
cannot relay compression ahead of it; wavefronts pile on a cone of half-angle `sinθ = c_s/v = 1/M`. This
is structurally E57's Cherenkov criterion `cosθ_C = c_local/v` with a different relay speed exceeded —
compression-relay `c_s` (boom) vs phase-relay `c_local` (Cherenkov). Rankine–Hugoniot jumps are the
relay bookkeeping across a front thinner than the medium can smooth: `δ ∼ few·λ` in matter, **`few·ℓ_P`
in vacuum** (ties FLM09: a vacuum shock front is Planck-thick, the opacity→Schwinger regime).

## 4. Investigation Strategy

Seven phases. Forward-derive and **log every number before** comparing to the measured/standard value
(R1); standard-FD results are CONVERGENCE targets, never imported coefficients (R5). Phase N+1 is gated
on N PASS or a documented DEFER.

### Phase 1 — Ordinary-fluid sound from compressibility *(calibration)*
- **Goal:** recover air `c_s ≈ 343 m/s` and water `≈1481 m/s` as relay-healing waves.
- **Method:** `c_s = √(dP/dρ)`; air `√(γR_gT)` (`γ=1.4, R_g=287, T=293`), water from measured `K/ρ`. Tag all MEASURED-INPUT.
- **Success:** air ±1%, water ±5%, inputs labelled; narration native.

### Phase 2 — The native `1/3` from D=3 isotropy *(the core; runs BEFORE law_I::P_rad)*
- **Goal:** derive `P = u/D` and `c_s = c/√D` from isotropy, keeping D symbolic; instantiate D=3.
- **Method:** compute `⟨cos²θ⟩` two ways — (i) the continuum sphere average (must give exactly 1/D),
  (ii) **the discrete average over the CRN bond directions from FLM08/`lattice_structure.hpp`** (must
  give 1/3 ± the frustration residual). Report both. Derive `c_s² = 1/D` symbolically. **Do not import
  `law_I::P_rad`.** Compute `c/√3` to ≥6 sig figs.
- **Success (A-grade):** continuum `⟨cos²θ⟩ = 1/3` exact; discrete CRN average within the committed
  residual (P2 threshold, §⑩); `c_s = 1.73085×10⁸ m/s`, `c_s/c = 0.577350`. **No `law_I::P_rad` call.**

### Phase 3 — One stiffness curve from gas to radiation
- **Goal:** show ordinary sound and the radiation ceiling are endpoints of `c_s = c√w`.
- **Method:** tabulate `c_s(w)` for `w = 10⁻¹² … 1/3`; overplot the air, water, and the P2 ceiling; verify monotonic saturation and that nothing exceeds `c/√3` for `w ≤ 1/3`.
- **Success:** all real points on `c_s = c√w` within input tolerance; curve saturates at `c/√3`; no exceedance.

### Phase 4 — Vacuum modes vs fluid sound *(the LIGO discriminator)*
- **Goal:** establish that `c/√3` is a **fluid** speed, and that the vacuum transverse mode (light, GW) is `c`.
- **Method:** state the vacuum-mode taxonomy (§3.3); compare the *fluid* ceiling `c/√3` against the
  *vacuum* transverse speed `c`; test the hypothesis "longitudinal vacuum mode = `c/√3`" against
  `|c_gw−c|/c < 10⁻¹⁵` (GW170817) and the LIGO scalar-polarization bounds; cross-check GOM06 ("no
  breathing mode").
- **Success:** `c/√3` is shown to be a fluid (matter) mode; the vacuum transverse speed is `c`; the
  "longitudinal-vacuum-mode = c/√3" hypothesis is **rejected** by the GW bound (or, if SDT genuinely
  predicts a 0.577 c scalar GW, that is flagged as a **falsified** sub-claim, not buried).

### Phase 5 — Dispersion relation & the lattice fingerprint *(FLM10 handoff)*
- **Goal:** obtain `c_s` as the long-wavelength slope of the lattice dispersion `ω(k)`, and the short-k deviation.
- **Method:** if FLM10's `ω(k)` is available, extract `c_s = dω/dk|_{k→0}` for the compressive branch and
  compare to the P2 value; characterise the deviation from linearity near `k ∼ 1/ℓ_P` (the cutoff that
  sets shock thickness). If FLM10 is not ready, **DEFER** with a one-line dependency note (do not fake).
- **Success:** `c_s(k→0)` from `ω(k)` matches P2 within 1%; the short-k bend is reported as the predicted
  shock-thickness scale; any anisotropy in `ω(k)` is reported as the lattice fingerprint (ties P2-discrete).

### Phase 6 — Mach cone, shock thickness, Cherenkov unification (E57)
- **Goal:** reproduce `sinθ = c_s/v` over `M = 1.2…10`; predict shock thickness; unify with E57.
- **Method:** compute `θ(M)` vs textbook; estimate `δ ∼ 3–5λ` in air (λ≈68 nm) and `δ ∼ few·ℓ_P` in
  vacuum; place `sinθ = c_s/v` and `cosθ_C = c_local/v` side by side; recover E57's VERIFIED angle as the `c_relay = c_local` case.
- **Success:** `θ(M)` <0.5° vs textbook; shock thickness order-of-magnitude correct; one written criterion `v > c_relay(mode)` reproduces both boom and E57.

### Phase 7 — Break the BAO sound-speed circularity *(cross-domain payoff)*
- **Goal:** supply CR04/CR08/CR09's `c_s = c/√3` **independently**, removing the audited circularity
  (those nodes compute `t_coupled = BAO_scale/c_s` from a hardcoded BAO scale — `cosmology.hpp:71`).
- **Method:** show FD05's P2 value (derived from isotropy, no cosmology input) equals the `c_s` the BAO
  chain *uses*; state explicitly that this makes the BAO sound horizon a *prediction from D=3*, not a
  re-reading of the measured 147 Mpc. Note the baryon-loading correction `c_s = c/√(3(1+R))`.
- **Success:** numerical identity of FD05-`c_s` and BAO-`c_s` (to P2 precision); a written note handed to
  CR04/08/09 marking which step the independence removes. (This *reduces* a cosmology circularity; it does
  not by itself derive the BAO scale — say so.)

## 5. Success Criteria (canonical A–F) + anti-tautology gate

- **A — PASS (NATIVE):** P2 derives `c_s = c/√D` from isotropy with **D symbolic and no `law_I::P_rad`
  call**, instantiates `c/√3` to ≥6 sig figs; P1, P3, P6 reproduce sound/curve/Mach within tolerance;
  P4 correctly classes `c/√3` as a fluid mode and clears the LIGO discriminator; P7 supplies the BAO
  `c_s` independently. CALIBRATED budget = 0 in the native chain.
- **C — QUALIFIED (CONVERGENCE):** the `1/3` is obtained but only via `P = u/3` taken as given (i.e.
  `law_I::P_rad` imported, or the discrete CRN average not computed); or one link (shock coefficient,
  `ρ_eff c² = u` identification) is convergence-matched. **Importing `P=u/3` caps the grade at C** — it
  is the identity, not the derivation.
- **D — PENDING:** mechanism dimensionally closed but a phase unexecuted (e.g. P5 deferred for FLM10, P4 stated not demonstrated).
- **F — FAIL:** `c_s` does not follow from compressibility (P1); the `1/3` does **not** follow from
  isotropy and cannot be obtained except by assuming it (P2); the vacuum modes collapse onto `c/√3`
  against the GW bound (P4); the stiffness curve is multi-valued (P3); or boom and Cherenkov demonstrably
  need different mechanisms (P6).

## 6. Outputs

- `fd05_sound_shocks.cpp` — standalone C++20 (Phases 1–7); D kept symbolic in P2; **no `law_I::P_rad` in
  the P2 native chain** (it may be referenced in P3+ as a cross-check, clearly tagged); prints a table + per-phase A–F verdict.
- `fd05_results.txt` — every quantity with value, units, input-class (DERIVED / COMPUTED / MEASURED-INPUT
  / CONVERGENCE-PENDING / IMPORTED), and the per-phase verdict.
- `FD05_DERIVATION.md` — worked derivations: `√(dP/dρ)`; the `P=u/D ⟹ c_s=c/√D` isotropy derivation
  (continuum **and** discrete-CRN); the `c_s=c√w` curve; the vacuum/fluid taxonomy; Mach kinematics; boom↔Cherenkov.
- `FD05_VERDICT.md` — A–F ledger, provenance block, the BAO-circularity note to CR04/08/09, OPEN items.
- `RUN_LOG.md` — pre-run commitments (mandatory; §⑩).

## 7. Dependencies & References

**Upstream (required):** FD01 (Euler limit of the relay), FD02 (compressibility ↔ relay stiffness),
**FLM08/CONDENSA** (the CRN bond directions for the discrete `⟨cos²θ⟩`; the `c_T/c_L` taxonomy),
**E57** (Cherenkov as super-phase-speed shock, VERIFIED).
**Engine hooks:** `law_I` (`u_CMB`, `P_rad=u_CMB/3.0` — *cross-check only, not P2*), `law_V` (movement
budget), `bridge` (koppa, k, z), `Engine/include/sdt/lattice_structure.hpp` (bond geometry).
**Lateral (the new wires):** **FLM10** (dispersion `ω(k)` → P5; may DEFER), **CR04/CR08/CR09** (consumers
of the BAO `c_s` → P7), **GOM06** (no-breathing-mode, → P4).
**Downstream (unblocked):** **FD09** (wave drag at high Mach), **FD08** (compressible Bernoulli).
**Framework:** `Theory/00_Ruleset.md`, `Theory/05` audit spine, `Laws/`.

## 8. Falsification Tests (each has a real failure mode)

| # | Test | SDT prediction | If it fails |
|---|---|---|---|
| F1 | Air/water sound from compressibility | `√(γR_gT) ≈ 343`, ±1%; water ±5% | `√(dP/dρ)` is not the relay-wave speed; thesis dead |
| F2 | **LIGO discriminator** | vacuum transverse mode = `c`; `c/√3` is a *fluid* mode; no 0.577c scalar GW | if SDT forces a longitudinal vacuum mode at `c/√3`, it predicts a 0.577c scalar GW — **excluded** by `|c_gw−c|/c<10⁻¹⁵` |
| F3 | Native `1/3` from isotropy | continuum `⟨cos²θ⟩ = 1/3` exact; discrete CRN within residual | if the only way to get `1/3` is to assume `P=u/3`, the derivation is empty (→ C, not A) |
| F4 | Single stiffness curve | all fluids on `c_s = c√w`; none exceed `c/√3` for `w≤1/3` | sound and the radiation limit are unrelated |
| F5 | Mach-cone angle | `sinθ = 1/M`, <0.5° vs textbook, `M=1.2–10` | shock geometry not relay-kinematic |
| F6 | Boom ↔ Cherenkov | one criterion `v>c_relay(mode)` recovers both incl. E57's VERIFIED angle | two mechanisms needed; unification falsified |
| F7 | BAO `c_s` independence | FD05's isotropy-`c_s` = the value CR04/08/09 use | the BAO `c_s` is not `c/√3`, or FD05 secretly used a cosmology input (circular again) |

## 9. Implementation Notes

- Double precision throughout (`c_s` spans ~12 orders). Keep `D` a `constexpr int` in P2 so `c/√D` is
  literally parameterised — print `c/√2, c/√3, c/√4` to make the dimensionality claim visible.
- **Guardrail for the central test:** the P2 function must not `#include` or reference `law_I::P_rad`.
  Add a comment marking the firewall; any P3+ cross-check that uses it is tagged `IMPORTED`.
- Pull the CRN bond vectors from `lattice_structure.hpp`; compute the discrete `⟨cos²θ⟩` over them and
  over random isotropic directions as a null — report both and their difference (the fingerprint).
- Keep `γ, R_g, T, K, λ` in one labelled MEASURED-INPUT block; standard-FD speeds are the convergence
  target, never the hard-coded answer.
- Plots (optional): (i) `c_s` vs `w` log–log with air/water/ceiling and the `c/√3` saturation line;
  (ii) `c_s = c/√D` vs D; (iii) `θ(M)`; (iv) boom envelope overlaid on the E57 Cherenkov cone.
- Author attribution in all generated files: **J. C. Harvey, Melbourne.**

## 10. Questions This Opens *(generative — log new ones in `FD05_VERDICT.md`)*

These are *not* required for the verdict; they are the point of doing it well.

1. **Is `1/3` exactly `1/3` in the real lattice?** If the frustrated CRN gives `⟨cos²θ⟩ = 1/3 + δ`, then
   `c_s = c/√3·(1+δ/2)` — a *measurable* deviation of the early-universe / radiation-fluid sound speed
   from the textbook value. Does any cosmological data (BAO width, CMB peak spacing) bound `δ`?
2. **Why is there no longitudinal vacuum sound, when there is a compressive gravity gradient?** If
   gravity is hinge-closure (a *static* depth field, GOM05) and not a propagating longitudinal wave, is
   "no breathing mode" (GOM06) the *same statement* as "no scalar GW polarization"? Can FD05 make that
   identity precise?
3. **Does `c_s = c/√D` make `c/√3` a dimensionality detector?** Any context where space behaves as D≠3
   (near the spation cutoff, inside a knot) should shift the local sound ceiling. Is that observable?
4. **Is the Planck-thick vacuum shock (δ ∼ few ℓ_P) the Schwinger/opacity onset of FLM09?** A source
   forced past `c_local` in vacuum should radiate at a front the lattice can't smooth — is that pair
   production / the Schwinger field, reached as a *shock* rather than a *field strength*?
5. **Does baryon loading `c_s = c/√(3(1+R))` have an SDT meaning** — is `R` the ratio of occluding
   (matter) to relaying (radiation) displaced volume, and does that re-derive the CMB peak heights?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FD05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the P2 native chain (list any elsewhere)
- Engine namespaces actually used: law_I (u_CMB; P_rad CROSS-CHECK ONLY), law_V, bridge, lattice_structure.hpp
- Phase thresholds (committed before run):
    P1 air ±1% / water ±5% · P2 continuum ⟨cos²θ⟩ exact=1/3, discrete CRN within ±1% (residual is data)
    P3 on-curve within input tol · P4 vacuum=c, fluid=c/√3 (binary) · P5 c_s(k→0) within 1% (or DEFER)
    P6 θ(M) <0.5° · P7 |FD05 c_s − BAO c_s|/c_s < 1e-4
- Forbidden retroactive changes: import P=u/3 into P2 then claim A; widen tolerances; plug targets;
    IDENTITY-PASS; local constant namespaces; bury a falsified sub-claim (F2/F4)
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P2 discrete `⟨cos²θ⟩` off 1/3 by > committed residual | report it as the **lattice fingerprint** (Q1); keep continuum result as A-core | **OPEN** the frustration-shift; still A on continuum, note discrete | silently average it back to 1/3 |
| P2 cannot reach 1/3 without `P=u/3` | down-grade to **C** honestly; the import is the identity | — | claim A while importing P_rad |
| P4 SDT forces a longitudinal vacuum mode at c/√3 | re-examine the mode taxonomy (transverse-only?) | mark the 0.577c scalar GW **FALSIFIED**, report it | hide the conflict with `c_gw=c` |
| P5 FLM10 `ω(k)` unavailable | **DEFER** P5 with dependency ID | — | fabricate a dispersion curve |
| P7 FD05 c_s ≠ BAO c_s | check for a smuggled cosmology input; recompute | **OPEN** the BAO-link; do not claim independence | retro-fit c_s to 147 Mpc |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments
- Finer numerics; phase splits (Na/Nb); filename fix via ADJ entry; alternative **native** isotropy routes (e.g. direct momentum-flux integral vs `⟨cos²θ⟩`).

### Disallowed adjustments
- Importing `P=u/3` into the P2 native chain and grading A · post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in any native chain · burying F2/F4/F7 outcomes.

---

*FD05 · 10× upgrade 2026-06-28 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
