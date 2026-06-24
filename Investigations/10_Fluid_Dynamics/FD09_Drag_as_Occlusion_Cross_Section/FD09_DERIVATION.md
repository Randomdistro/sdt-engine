# FD09 — Derivation: Drag as an Occlusion Cross-Section

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Author**: James Christopher Tyndall, Melbourne
**Status**: EXECUTED — Class C (QUALIFIED, convergence)

*Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.*

---

## 0. Thesis in one line

Fluid drag is the **same Law III occlusion mechanism** the engine already uses
for gravity and the Coulomb force: a body moving through the relay medium casts a
**shadow** in the convergent momentum flux, and the **front-minus-wake imbalance
over that shadow cross-section IS the drag force**. Low-Re Stokes drag and
high-Re form drag are the two analytic limits of one occlusion integral.

```
            convergent / streaming momentum flux  →  →  →
                          ┌───────────┐
        q = ½ρv²  →  →  → │  BODY (R) │  · · ·  wake ≈ ambient (own shadow)
            (FD08)        └───────────┘
                       ▲ front bombarded harder than back ▲
            net push  =  F_D = C_D · (½ρv²) · A ,  A = πR² = occluded shadow
```

This is identical in **form** to Le Sage / occlusion gravity (SAR01,
`law_III::F_occlusion`): a body intercepts a directed flux over a shadow
cross-section and the unbalanced part is the force. Drag is that same shadow,
now resolved fore/aft along the velocity instead of radially.

---

## 1. Phase 1 — the occlusion-drag integral (mechanism, Checkpoint C1)

**Statement.** Specialise the Law III occlusion picture to a *directed* momentum
flux. The front face sees the dynamic (stagnation) pressure `q = ½ρv²` (FD08);
the wake sits in the body's own shadow at ≈ambient. The net push integrated over
the shadow cross-section is, *by definition of the drag coefficient*,

```
    F_D = ∮_S (P_front − P_wake)(n̂·v̂) dA  ≡  C_D · (½ρv²) · A ,   A = πR².
```

`C_D` is the **occluded fraction** of the geometric shadow `A = πR²`. The engine's
`law_III::solid_angle_occluded(R, r) = πR²/r²` is the same shadow; at `r = 1 m`
it returns `πR²` — i.e. the frontal area itself. No new constant is introduced.

**Checks (real run):**
- `A = πR² = 3.141593e-04 m²` for `R = 0.01 m`; engine `solid_angle(R, 1m) = 3.141593e-04 sr` — **identical geometry**.
- At `v = 0`, `q = 0 ⟹ F_D = 0` — balanced bombardment, no net push at rest.
- **Free parameters introduced by Phase 1: 0** → **C1 PASS**.

| Quantity | Symbol | Provenance |
|---|---|---|
| Shadow cross-section | `A = πR²` | **DERIVED** (Law III geometry) |
| Dynamic pressure (front flux) | `q = ½ρv²` | **DERIVED** (FD08) |
| Drag coefficient (occluded fraction) | `C_D ≡ F_D/(½ρv²A)` | **DERIVED** (definition) |
| Reynolds number | `Re = ρvD/μ` | **DERIVED** (advection ÷ relay diffusion, Law V/FD01) |

---

## 2. Phase 2 — low-Re Stokes limit, the `6π` (Checkpoint C2)

**SDT-native content (Class C).** In the relay-diffusion limit (`Re ≪ 1`) the
FD01 `ν∇²v` term dominates advection: momentum diffuses *around* the body, the
shadow is "soft", and the drag can only be built from the relay-healing rate `μ`,
a single body length `R`, and the speed `v`. Dimensional closure forces

```
    F  ∝  μ · R · v          ← THIS scaling is the SDT statement.
```

**Borrowed content (CORRELATION, NOT derived).** The dimensionless prefactor is
the full creeping-flow Stokes-sphere solution `6π` (= `4π` skin-friction share +
`2π` pressure/form share). SDT does **not** derive `6π` from first principles in
this investigation; we **adopt** it openly as the correlation and verify the
identity `F = 6πμRv ⇔ C_D = 24/Re`.

**Check (real run, `R=5e-4 m`, `v=1e-3 m/s` in water, `Re=0.9962`):**
- `F(6πμRv) = 9.443628e-09 N`
- `F(C_D=24/Re) = 9.443628e-09 N`
- ratio `= 1.0000000000` — exact identity.
- prefactor used `= 18.8495559215`; `6π = 18.8495559215`; `|dev| = 0.00e+00 %` → **C2 PASS**.

> **R5 honesty.** No integer or `π` was inserted to "force" `6π`. It is the
> published Stokes value, flagged CORRELATION. The genuinely SDT result here is
> the `μRv` scaling, not the coefficient.

---

## 3. Phase 3 — high-Re form-drag plateau (Checkpoint C3)

For `Re ≫ 1` advection (Law IV displacement) outruns relay healing: the medium is
swept aside faster than the relay can fill the gap, a **separated wake** forms,
and the occluded shadow is the **geometric frontal area** `A = πR²`. The occluded
fraction `C_D` is then `O(1)` — set by the laminar-separation wake angle handed
from FD06. SDT predicts **order unity**; the specific sub-critical value
`C_D ≈ 0.47` is **MEASURED-INPUT** (Schlichting sphere tables).

**Check (real run):** `C_D(Re=1e4) = 0.461 ∈ [0.4, 0.5]` → **C3 PASS**.

The composite curve blends Schiller–Naumann (`C_D = 24/Re·(1+0.15 Re^0.687)`,
valid to `Re≈10³`) *onto* the flat plateau via a logistic weight in `log Re`, so
the curve transitions through the intermediate regime to the form plateau without
double-counting.

---

## 4. Phase 4 — the drag crisis (Checkpoint C4)

**Mechanism (SDT-native, qualitative).** The crisis is **not a new mechanism**: it
is the FD06 laminar→turbulent boundary-layer transition. When the boundary layer
trips turbulent it **re-attaches**, separation moves rearward, the wake **narrows**,
the **occluded shadow shrinks**, and `C_D` drops. After transition the (now
turbulent) wake slowly re-widens with `Re`, so `C_D` partially recovers.

**Borrowed numbers (MEASURED-INPUT).** Crisis location `Re_crit ≈ 3×10⁵` and the
post-crisis minimum `C_D ≈ 0.10` are Achenbach (1972) smooth-sphere measurements.
Modelled as a logistic transition between the plateau level (0.47) and the
post-crisis level (0.10). **CALIBRATED(1):** a single wake-shrink scale — the
transition width ≈ 0.12 decade in `log Re` — is the one fitted number; the two
levels and the location are reproduction targets, not free.

**Check (real run):** pre-crisis `C_D(1e5) = 0.469`; minimum `C_D = 0.125` at
`Re = 5.62×10⁵` (within ×2 of `3×10⁵`); post-crisis `C_D ∈ [0.07, 0.15]` → **C4 PASS**.

---

## 5. Phase 5 — full curve + terminal velocity (Checkpoint C5)

**Composite `C_D(Re)` model** (Phases 2–4 stitched):

| Re | C_D(model) | C_D(ref) | regime |
|---|---|---|---|
| 1e-1 | 247.4 | 240 | Stokes |
| 1e0 | 27.6 | 24 | Stokes |
| 1e1 | 4.146 | 4.1 | intermediate |
| 1e2 | 1.07 | 1.07 | intermediate |
| 1e3 | 0.454 | 0.47 | plateau |
| 1e4 | 0.461 | 0.41 | plateau |
| 1e5 | 0.469 | 0.47 | plateau |
| 3e5 | 0.289 | 0.2 | crisis |
| 5e5 | 0.127 | 0.1 | post-crisis |
| 1e6 | 0.140 | 0.18 | post-crisis |

Tracks the Schlichting/Achenbach reference across all 7 decades.

**Terminal velocity — SDT weight `g = v_surf²/R_body` (NO G, NO M).** The weight
enters the balance as `m·g`; `g` is supplied via `g = v²/R` framing (the run
reports that `g = 9.81 m/s²` is reproduced by `v_surf = 7905.7 m/s` on
`R_body = 6.371×10⁶ m` — geometry only, never `G·M`). The balance

```
    F_D(v_t) = C_D(Re(v_t)) · ½ρ_fluid v_t² · πR²  =  m g ,
    m = ρ_body · (4/3)πR³
```

is solved by bisection; the regime is **self-selected** by the resulting `Re`.

| case | D [m] | v_t [m/s] | v_Stokes | Re | C_D | measured ref |
|---|---|---|---|---|---|---|
| steel 1mm / water | 0.001 | 0.425 | 3.73 | 423 | 0.570 | — (Re≫1, not Stokes) |
| glass 3mm / water | 0.003 | 0.473 | 7.35 | 1414 | 0.439 | — |
| steel 5mm / water | 0.005 | 1.067 | 93.2 | 5313 | 0.452 | — |
| water drop 1mm / air | 0.001 | 3.97 | 29.8 | 262 | 0.690 | 4.0–4.5 (Gunn–Kinzer) |
| water drop 3mm / air | 0.003 | 8.64 | 268 | 1710 | 0.437 | 8.0–8.1 (Gunn–Kinzer) |

The closed-form buoyant Stokes `v_Stokes` is shown for cross-check: it only
agrees with `v_t` when `Re ≲ 1`; for these (turbulent-wake) cases `Re ≫ 1`, so the
full `C_D(Re)` form-drag solution is the correct one — and it lands the raindrop
terminal velocities **within ~15%** of Gunn–Kinzer. → **C5 PASS** with **CALIBRATED(1)**.

---

## 6. Parameter ledger

| Quantity | Value / form | Provenance |
|---|---|---|
| Drag form `F = C_D·½ρv²·A` | `A = πR²` | **DERIVED** (Law III shadow) |
| `μRv` Stokes scaling | dimensional | **DERIVED** (FD01/FD02 relay diffusion) |
| `6π` prefactor | 18.8496 | **CORRELATION** (full Stokes-sphere solution) |
| `C_D = 24/Re` | analytic | **MEASURED-INPUT** (Stokes) |
| Schiller–Naumann blend | `24/Re(1+0.15Re^0.687)` | **MEASURED-INPUT** (correlation) |
| Form plateau `C_D ≈ 0.47` | 0.47 | **MEASURED-INPUT** (Schlichting) |
| Crisis location `Re_crit` | 3×10⁵ | **MEASURED-INPUT** (Achenbach 1972) |
| Post-crisis `C_D` | 0.10 | **MEASURED-INPUT** (Achenbach 1972) |
| Crisis transition width | 0.12 decade | **CALIBRATED(1)** (the one fitted scale) |
| Fluid `ρ, μ` (water/air) | NIST/IAPWS | **MEASURED-INPUT** |
| Material densities (steel/glass/water) | tables | **MEASURED-INPUT** |
| Weight `g = v_surf²/R_body` | 9.81 → v_surf=7906 | **DERIVED-framing** (no G/M) |

**CALIBRATED total: 1.** (Target ≤ 1 met.)

---

## 7. Regime map

```
   C_D
   |  \  24/Re (Stokes; μRv scaling NATIVE, 6π borrowed)
   |   \
   |    \___ Schiller–Naumann intermediate
   |        \____ form plateau ~0.47 (wake = frontal shadow, FD06 laminar sep.)
   |              \
   |               | ← DRAG CRISIS (FD06 turbulent re-attach, wake shrinks)
   |               \__ post-crisis ~0.1 → slow recovery
   +----------------------------------------------> log Re
     1e-1   1e0   1e2     1e3      1e5  3e5  1e6
       └ relay-diffusion ┘ └ advection / form-drag ┘
```

---

## 8. What is native vs borrowed (the honest core)

- **NATIVE (Class C, the SDT win):** drag = occlusion shadow; the
  `C_D·½ρv²·A` *form*; the `μRv` Stokes *scaling*; the existence of a
  wake-controlled high-Re regime; the crisis as a wake/shadow *shrink* (FD06);
  the `g = v²/R` weight with no G/M.
- **BORROWED (reproduced, never claimed as derived):** the `6π` prefactor, the
  numerical `C_D(Re)` curve (24/Re, Schiller–Naumann, 0.47), the crisis location
  `3×10⁵`, and the post-crisis `≈0.1`.
- **CALIBRATED(1):** one wake-shrink/crisis-shape scale.

The occlusion framing earns the **shape and the scaling natively**; the
**coefficients are convergence targets**. That is exactly a Class C result.
