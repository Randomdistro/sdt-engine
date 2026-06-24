# OP01 — Refraction and Dispersion as a Spation Gradient-Index Medium

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

---

## 1 · Executive Summary

Light in SDT is an **emission** — a propagating phase-impulse relayed spation-to-spation — and its
local speed is set by the local spation closure: `c_local = c(1−z)`, `z = ϟ/r` (GOM05, the variable-
closure result, [[project_cq43_variable_closure]]). **Can the refractive index, Snell's law, lens
imaging, dispersion, and total internal reflection be reproduced as a gradient-index medium where
`n(r) = c/c_local` is literally the spation-closure ratio — light bending because it takes the
least-resistance (fastest-relay) path through a graded lattice?** This unifies "optical" refraction
(through matter) and "gravitational" lensing (through a mass-graded vacuum) as **one mechanism**, and
sets up the falsifiable solar lens-artifact prediction ([[project_solar_lens_artifact_claim]]).
**We expect:** Snell's `n₁sinθ₁ = n₂sinθ₂` falls out of Fermat least-time on the relay; the lens-maker
and thin-lens equations follow from `n(r)`; dispersion `n(λ)` arises because shorter-wavelength
emissions sample the lattice granularity differently; and the Sun's multi-λ "different surfaces" are
**dispersive lens artifacts of one surface** with a caustic fold at the temperature-minimum shell.

## 2 · Physical Context

Every medium — glass, water, or a mass-graded vacuum near the Sun — is, to light, a region of altered
spation closure. Where closure is tighter (denser matter, or deeper in a convergence well), spations
are "smaller," the relay step is shorter, and the phase-impulse advances slower: `c_local` drops, so
`n = c/c_local` rises. Refraction is then not a mysterious slowing but the emission steering down the
gradient of relay speed — the **same** least-resistance rule that bends starlight past the Sun
(Shapiro/lensing are the n>1 vacuum case of ordinary optics). Dispersion enters because the lattice is
granular at ℓ_P: different emission wavelengths couple to that granularity slightly differently, so
`n` depends on λ — and a graded medium with `n(λ)` produces a **wavelength-dependent focal surface**,
the seed of the solar multi-λ artifact.

Variables: closure depth `z = ϟ/r`; local speed `c_local = c(1−z)`; index `n = c/c_local = 1/(1−z)`;
ray angle θ; focal length f; Abbe number / dispersion `dn/dλ`; lattice granularity scale ℓ_P. Targets:
Snell, thin-lens `1/f = (n−1)(1/R₁−1/R₂)`, prism dispersion, TIR critical angle, Eddington 1.75″ deflection.

## 3 · Theoretical Framework

Build on: GOM05 (`c_local`, `n` as closure ratio), GOM01 (depth engine z(r), Shapiro, bending), CR07
(octave/redshift ruler), Law V (movement budget), depth_closure namespace in `laws.hpp`. **Forbidden:**
photon as a point-quantum with intrinsic frequency-mass, QED vacuum polarisation as the lensing cause,
metric-curvature-as-primitive, "spacetime bends." Snell, lens equations, and the 1.75″ deflection are
targets.

Working hypotheses:
- **H1 (index = closure ratio):** `n(r) = 1/(1−z(r))`; for ordinary matter z is set by the local
  bound-mass convergence, for the solar vacuum by `ϟ_⊙/r`. One formula, two regimes.
- **H2 (Snell = Fermat least-relay-time):** stationary relay-time across a closure interface gives
  `n₁sinθ₁ = n₂sinθ₂`; TIR when no real refracted relay path exists.
- **H3 (lensing ≡ refraction):** integrating the n-gradient along a grazing solar ray gives the
  **1.75″** deflection — i.e. gravitational lensing is gradient-index optics with n−1 = z (factor-2
  vs naive Newton handled by the full closure integral, cross-check GOM01).
- **H4 (dispersion + solar artifact):** `n(λ)` from λ-dependent granularity coupling ⇒ a wavelength-
  dependent solar limb; the false-colour λ-scan shows the disk **grow then partly vanish** at the
  ~4400–5000 K temperature-minimum band (a caustic **fold** where T(height) turns over), then
  reappear — the dated falsifiable claim.

## 4 · Investigation Strategy

**Phase 1 — Index from closure.** Tabulate `n = 1/(1−z)` for glass/water (via their bound-mass z) and
for the solar vacuum (z = ϟ_⊙/r). *Success:* lab `n` (glass ≈1.5, water ≈1.33) recovered to order;
the *mechanism* identical for both.

**Phase 2 — Snell + TIR.** Fermat least-relay-time across an interface. *Success:* Snell exact; TIR
critical angle `θ_c = arcsin(n₂/n₁)` recovered; sign/branch correct.

**Phase 3 — Lens + lensing.** Thin-lens equation from `n(r)` of a curved interface; then the grazing-
solar n-gradient integral. *Success:* `1/f` formula recovered; **1.75″** solar deflection to <1%
(matches GOM01).

**Phase 4 — Dispersion + solar fold.** Add `n(λ)`; ray-trace a false-colour solar limb across λ.
*Success:* prism dispersion sign correct; the predicted disk-grow→fold→reappear at the temp-minimum
shell rendered, with the band location quantified — a concrete falsifier.

## 5 · Success Criteria

- ✅ **PASS (Class A):** Snell, TIR, thin-lens, and 1.75″ all from one `n = 1/(1−z)`, zero fits;
  optics ≡ lensing demonstrated; dispersion sign native.
- ✅ **QUALIFIED (Class C):** the above with lab `n` magnitudes CALIBRATED via measured bound-mass z;
  solar fold predicted qualitatively. (Expected landing.)
- ⚠️ **PENDING (Class D):** refraction/lensing unified but dispersion `n(λ)` only schematic.
- ❌ **FAIL (Class F):** cannot recover Snell/1.75″ from the closure gradient.

## 6 · Outputs

1. `OP01_DERIVATION.md` — n=1/(1−z); Snell/TIR via Fermat; lens + 1.75″; dispersion + solar fold.
2. `op01_gradient_index.cpp` — standalone C++20: interface refraction, solar-ray integral, λ-limb trace.
3. `op01_results.txt` — n table (glass/water/vacuum); Snell checks; deflection vs 1.75″; fold-band λ map.
4. `OP01_VERDICT.md` — A/C/D/F; explicit statement that optical and gravitational refraction are one.

## 7 · Dependencies & References

**Upstream:** GOM05 (variable closure / c_local), GOM01 (depth engine, Shapiro/bending), CR07 (ruler),
depth_closure (laws.hpp). **Downstream:** full gravitational-lensing investigation (GD06, 08_Galactic),
the solar lens-artifact experiment ([[project_solar_lens_artifact_claim]]), fibre/waveguide optics.
**Related:** E72 (c in dense media), E94 (convergence lens), GOM06 (GW speed = c).

## 8 · Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|------|-----------|-------------------|---------|
| T1 | n = 1/(1−z) | glass/water n recovered from bound-mass z | index not a closure ratio |
| T2 | Snell = least relay-time | n₁sinθ₁=n₂sinθ₂ exact; TIR angle right | refraction not Fermat-on-lattice |
| T3 | lensing ≡ refraction | 1.75″ solar deflection <1% (= GOM01) | optics and gravity not unified |
| T4 | dispersive one-surface Sun | λ-limb grows→folds→reappears at temp-min | the "different Suns" are real, not artifacts |

## 9 · Implementation Notes

Double precision; trace rays by integrating `d/ds(n·t̂)=∇n` (the eikonal ray equation, here a relay
least-time path — native, not borrowed wave optics). For the solar fold, use a realistic T(height)
with a minimum near ~500 km and map it to z(height) then n(height,λ); the fold is where dn/dh changes
sign. Plot: (a) bent ray across an interface; (b) deflection vs impact parameter (→1.75″ grazing);
(c) false-colour limb radius vs λ showing the fold. The headline unification — *one n-mechanism for
glass and for the Sun* — is the result; the solar fold is the falsifier that makes it testable.
