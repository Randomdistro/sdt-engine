# E104: Space-Balloon-Gondola Casimir/Cavendish Hybrid

> **Category**: Gravity / Occlusion · Vacuum / Medium (unified occlusion test)
> **Difficulty**: HIGH (stratospheric balloon payload; existing components)
> **Status**: Proposed — falsifiable, single-platform correlation test
> **Source theory**: EMC03 (occlusion = the one force, attraction/repulsion as ± redirection), GOM13 (occlusion-altitude Cavendish), E22 (Casimir vacuum sound), E23 (Cavendish bell), two-regime occlusion-saturation
> **Author**: James Christopher Harvey, Melbourne

---

## 1. Background — why fly *both* on one gondola

In the Standard Model the **Casimir force** (QED vacuum fluctuations between
plates) and the **Cavendish constant** (Newtonian `G` between test masses) are
*unrelated* phenomena governed by different theories. They have no reason to
co-vary as a function of where or when you measure them.

SDT says they are **the same mechanism at two scales** (EMC03): both are
**occlusion of the convergent boundary throughput**. The Casimir plates occlude
each other's relay content over micron gaps; the Cavendish masses occlude each
other's convergent push over centimetre gaps. One law:

```
F = (π/4) · P_eff · R₁² R₂² / r²          (Law III, universal occlusion)
```

If that is true, then **both forces are read off the same local convergent
budget** `P_eff(r)` — and anything that changes that budget changes *both,
together*. A stratospheric balloon gondola (32–40 km, above 99% of the
atmospheric column) is the cleanest accessible platform to vary the overhead
occlusion while holding everything else fixed, and to run the two measurements
**side by side on one thermally-stable, low-vibration bus**.

The hybrid is the point: the discriminating signal is not either force alone —
it is whether the **Casimir and Cavendish readings track each other** as the
overhead matter column and convergent background change with altitude and
pointing. SM predicts independence; SDT predicts correlation.

---

## 2. SDT Prediction

Let the overhead atmospheric column (and Earth-limb geometry) set a small,
altitude-dependent occlusion fraction `δ(h)` of the downward convergent budget.
SDT (GOM13) predicts a fractional change in the *apparent* Cavendish coupling:

```
ΔG_app/G ≈ −δ(h)            (less overhead occlusion → fuller budget)
```

and — because the **same** `P_eff` sets the Casimir pressure — a **correlated**
fractional change in the Casimir force at fixed gap:

```
ΔF_Cas/F_Cas ≈ κ · ΔG_app/G ,   κ = O(1) , same sign
```

with `κ` fixed by the shared `P_eff` (a number the engine can emit, not a fit).
Concretely: as the gondola rises from float-start (≈18 km residual) to ceiling
(≈40 km), or as the payload is rotated so the dense Earth limb sweeps the
plate/mass line-of-sight, **both readings shift in lockstep**. The cross-channel
correlation coefficient `ρ(F_Cas, G_app) → +1` is the SDT signature.

A secondary, stronger-field check rides along: per occlusion **saturation**, the
near-contact Cavendish geometry (masses subtending a large solid angle) departs
from `1/r²` toward the `g→2` hemisphere limit — a deviation that should appear
in the same data set.

---

## 3. Standard-Model Prediction

- **Casimir (QED)**: `F_Cas = π²ħc/(240 d⁴)` per unit area — depends only on the
  gap `d` and temperature, **not** on altitude, pointing, or the gravitational
  environment.
- **Cavendish (Newton/GR)**: `G` is a universal constant; `g(h)` varies with
  altitude *only* through the known `g = GM⊕/(R⊕+h)²` and mass distribution — a
  smooth, computable geometric term with **no** coupling to the Casimir channel.

Therefore the SM predicts the two channels are **statistically independent** once
the trivial `g(h)` term is removed: `ρ(F_Cas, G_app) = 0`.

---

## 4. Observable

The single discriminating number is the **cross-channel correlation** of the two
residuals (after removing the known `g(h)` and `d⁴`, `T` dependences):

| Quantity | SM | SDT |
|---|---|---|
| `ΔF_Cas/F_Cas` vs altitude/pointing | 0 (within noise) | tracks `ΔG_app/G` |
| `ρ(F_Cas residual, G_app residual)` | 0 | +1 (same `P_eff`) |
| Cavendish near-contact `g(r)` shape | `1/r²` | saturating → 2 (occlusion) |

A non-zero, **positive, same-sign** correlation that scales with the overhead
occlusion is impossible in the SM and required by SDT.

---

## 5. Apparatus (one gondola, two heads, shared metrology)

- **Bus**: stratospheric balloon gondola, ceiling 32–40 km, pointing-stabilised,
  passively + actively thermally controlled (the platform E22/E23 always lacked).
  Long float (NASA LDB / super-pressure class) for altitude sweeps and many
  limb-pointing cycles.
- **Casimir head**: gold-coated optical-flat plates, 0.1–10 µm gap on a calibrated
  piezo stage, force read by laser interferometer (sub-pm); cryo-cooled head to
  suppress thermal Casimir background (cf. E22, E60).
- **Cavendish head**: torsion balance with dense (W/Os) test masses, sub-µg
  equivalent sensitivity, autocollimator readout (cf. E23, E76, GOM13).
- **Shared metrology**: one clock, one inertial/attitude reference, one thermal
  and pressure log, so the two residual time-series are co-registered for the
  correlation analysis. **The shared bus is the experiment** — it cancels the
  systematics that would otherwise masquerade as correlation.
- **Pointing programme**: (a) slow altitude ramp float-to-ceiling; (b) repeated
  rotations sweeping the dense Earth limb through the plate/mass axis; (c)
  day/night cycling (Sun in/out of the occlusion cone).

---

## 6. Feasibility

**HIGH but not exotic.** Every component flies today: stratospheric gondolas
(LDB/super-pressure), pointing stabilisation, cryogenic Casimir heads, and
flight torsion balances all exist separately. The novelty is integration and the
**cross-correlation analysis**, not new hardware. A tethered high-altitude or
aircraft prototype can validate the metrology chain before a free flight. Risk is
systematics control (vibration, thermal, electrostatic patch potentials) — which
is exactly why the single-bus design is chosen: shared systematics are common-mode
and differenced out of the correlation.

---

## 7. Impact

- **If the channels correlate** (`ρ → +1`, scaling with overhead occlusion):
  the Casimir force and the Cavendish coupling are shown to read the **same**
  convergent-pressure field — direct evidence for the single occlusion law
  spanning micron to centimetre scales. There is no SM mechanism for this.
- **If only the saturation term appears** (`1/r²` violation near contact, no
  Casimir correlation): partial support — occlusion at the macroscopic scale, but
  the micron-scale unification is not established.
- **If `ρ = 0` to precision**: the unified-occlusion claim is falsified at the
  achieved level — Casimir and Cavendish do not share a field. A clean SDT kill.

---

## 8. Predicted curve (reproduce)

Engine targets to emit before flight: `P_eff` (`law_III::P_eff`) → the shared
coupling `κ`; overhead occlusion δ(h) — **per the FARMER correction (2026-07-03,
GOM13 PROMPT): use the mass-column-proportional per-baryon form (Bouguer-consistent,
~4.4×10⁻⁷ at the surface), NOT the sin-dip cone geometry, which is a transcription
error excluded 47× by existing G records** — → the predicted `ΔG_app/G(h)`;
near-contact saturation `g(r) = 2(1 − √(1 − x))/x , x = (R_mass/r)²`. The single
flight deliverable is the co-registered residual pair and its correlation
coefficient. Pre-flight status (GOM13 run, 2026-07-03): the corrected δ(h) ramp is
~10⁻⁹-class — below any current lock-in floor — so the flight as designed does not
discriminate; the κ-correlation channel is the surviving falsifiable core, pending
an observable with reachable amplitude.
