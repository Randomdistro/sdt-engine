# GOM22 — the Shapiro delay measures the relay-speed profile: canon is short by 2

> Direct run 2026-07-30. Instrument: `gom22_shapiro_profile.cpp` (g++ 14, −O2,
> against `sdt/laws.hpp`). Harvey's instruction: formulate the velocity change of
> c from the Shapiro delay and compare to the codebase figures.
> **APPLIED to canon 2026-07-30** on Harvey's instruction ("update all canon you have ready"). laws.hpp relations (2) and (3) repaired; suite row B39 added (both rows PASS); GOM05/GOM06 annotated.

## Method (inversion, not fitting)

A propagation delay through a variable-speed medium is an integral of the inverse
local speed. With `c_local(r) = c(1 − K·z)`, `z ≡ ϟ/r`:

```
Δt = ∫dl/c_local − ∫dl/c ≈ (K·ϟ/c)·∫dl/r = (K·ϟ/c)·ln(4r₁r₂/b²)     [one way]
```

The measured delay therefore **fixes K**. Nothing is free. Verified by explicit
20-million-step line integral along the ray, not just the log approximation.

SDT commits to this reading with no escape: there is no curved spacetime here, so
no part of the delay can be re-attributed to extra path length. The whole delay
is a speed effect. That is our own commitment, not GR's.

## The comparison

| | profile | round-trip delay, grazing Earth–Mars | vs measured |
|---|---|---|---|
| **Measured** | — | **247.24 μs** | Viking ~250 μs (0.1%); Cassini pins the coefficient to 2.1 ± 2.3 ×10⁻⁵ |
| Canon relation (2) | c(1 − z) | 123.62 μs | **0.5000 — exactly half** |
| Canon `shapiro_delay()` | integrand hardcoded 2z | 247.24 μs | matches, but the 2 is inserted |

**The canon's own velocity profile, integrated without the inserted factor, delivers exactly 50% of
the measured Shapiro delay.** Against Cassini's 2.3×10⁻⁵ precision on that
coefficient, a 50% shortfall is not a residual — the relation as written is
falsified by the measurement.

## The same factor sits in the clock relation

| relation | solar gravitational redshift | measured |
|---|---|---|
| canon (3) `dτ/dt = √(1−z)` | 1.061×10⁻⁶ = 318.2 m/s | **ratio 0.500** |
| `√(1−2z)` or equivalently `(1−z)` | 2.123×10⁻⁶ = 636.3 m/s | ratio 1.000 ✓ |

Measured solar gravitational redshift ≈ 633 m/s (z = ϟ/R_Sun = 2.12×10⁻⁶).
Canon relation **(4)** (`z_spec` = depth differential) reproduces it — that is
the C1 result tested to 0.03% — but **(4) does not follow from (3)**: they
disagree by the same factor 2. Three of the five Depth-Closure relations are
mutually inconsistent, and the one the theorem was graded on is the odd one out.

## Root cause (traced, not patched)

`GOM05_Variable_Spation_Closure` derives the profile as

```
c_local(r) = c_∞ · ℓ_P(r)/ℓ_P,∞ = c_∞(1 − z)
```

This scales the **hop length** by the local closure while leaving the **hop
duration** at its far-frame value — a mixed-frame slip. SDT's own relation (3)
says the local tick also closes. Speed is length per time; if the closure
shortens the hop *and* dilates the tick, the far-frame relay speed carries the
factor **twice**:

```
c_far = c · [ℓ_P(r)/ℓ_P,∞] · [t_P,∞/t_P(r)] = c(1 − z)²  ≈ c(1 − 2z)
```

**The missing factor is the clock, and SDT already had it in canon.** This is a
native repair: nothing is imported, one relation is made consistent with another
already on the books. The hardcoded 2 in `shapiro_delay()` becomes *derived*, and
the header line "the local light speed stays c" — which flatly contradicts
relation (2) — can be withdrawn.

## Canon change — APPLIED 2026-07-30

In `depth_closure` and `GOM05`:

```
(2') c_far(r) = c_∞ (1 − z)²        relay speed: closure enters hop AND tick
(3') dτ/dt    = (1 − z)             local clock rate  [≈ √(1−2z), first order]
```

With these, relations (2'), (3') and (4) agree with each other and with all
three measurements: the solar redshift at 636 vs 633 m/s, the Shapiro delay at
0.0000%, and `shapiro_delay()`'s coefficient earned rather than inserted.

## The fork that matters — and it is decidable

Two forms both give K = 2 and both fix the redshift, agreeing to first order:

- **(a) c(1−z)²** — SDT-native: one closure factor applied twice.
- **(b) c(1−2z)** — the Schwarzschild coordinate speed. DISCLOSED: shared form
  with GR, a correspondence, **cannot discriminate** on first-order data.

They part company where it counts. The relay speed vanishes at:

- form (a): z = 1 → **r = ϟ** (half the Schwarzschild radius)
- form (b): z = ½ → **r = 2ϟ = r_s exactly**

So form (b) reproduces GR's horizon, and **GOM06's distinctive echo prediction
dies with it** (that prediction rests on the hard wall sitting inside r_s). Form
(a) keeps the wall at ϟ and keeps the prediction.

**Against my own bias:** that form (a) protects an SDT prediction
is *not evidence for form (a)*. It is a consequence. The evidence must be
second-order measurement, and here is where it lives:

| regime | z | relative (a)−(b) split = z/2 | testable? |
|---|---|---|---|
| solar limb | 2.12×10⁻⁶ | 1.06×10⁻⁶ | ~4% of Cassini's error bar — not yet |
| S2 at Sgr A* periapsis | 3.5×10⁻⁴ | 1.8×10⁻⁴ | below GRAVITY's redshift precision |
| 1.4 M☉ neutron-star surface | 0.172 | **8.6%** | NICER hot-spot / light-bending modelling — the live avenue |

Until one of those separates them, both forms stand and the choice is OPEN. What
is *not* open is that K = 1 is dead.

## Standing

- Canon relation (2) `c_local = c(1−z)`: **FALSIFIED** by the Shapiro delay
  (factor 2, against a coefficient measured to 2×10⁻⁵).
- Canon relation (3) `dτ/dt = √(1−z)`: **FALSIFIED** by the solar gravitational
  redshift (same factor 2), and inconsistent with canon relation (4).
- Canon relation (4) and the C1 result (redshift = depth, 0.03%): **UNTOUCHED** —
  it was graded against measurement and it holds.
- `shapiro_delay()` returns the right number for the wrong reason: its factor 2
  is inserted by hand. After the repair it is derived.
- The repair is native, one line, and fixes both faults at once.
- Form (a) vs (b) — whether SDT has a horizon at r_s — is now a sharp, named,
  second-order question with a candidate observational avenue.

## What is owed

1. Harvey's ruling on the canon change (capstone block — propose-and-wait).
2. Re-run every consumer of `c_local`/`clock_rate` after the change: GOM05
   (its own verdict line quotes the K=1 form), GOM06 (echo spacing integrand
   `1/(1−ϟ/r)` must become the repaired profile), the lumiopause chain.
3. The second-order discriminator: NICER-class strong-field timing is where (a)
   and (b) separate at ~9%.
