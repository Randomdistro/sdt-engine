# APS04 — P1: Trefoil wake geometry, derived before the solver (2026-07-26)

> **Author:** J. C. Harvey, Melbourne. Direct, main session. Everything here was written
> BEFORE `aps04_wake_field_solver.cpp` (rebuilt) existed, per the spec. The solver's job is to
> confirm or refute these derivations — not to inspire them.

## 1. The knot (committed parametrisation)

(2,3) torus knot, aspect ρ = r/R = 1/4 (the 1:4 gearing, W+1 — same wrap as FD04-P6):

x(t) = (R + r cos 3t)·cos 2t · y(t) = (R + r cos 3t)·sin 2t · z(t) = r sin 3t, t ∈ [0, 2π)

scaled so the outermost extent R + r = R_p = 4ℏ/(m_p c) = 0.8412 fm (Law VI, W+1 rule).
With ρ = 1/4: R = 0.6730 fm, r = 0.1682 fm.

## 2. The wake's two channels (translation notes on record)

- **Occlusion channel (Law III — the force channel):** the knot occludes convergence along
  its length; the wake's convergence-deficit potential is the line integral
  Φ(x) = ∮ σ dl′ / |x − x′| with σ uniform per unit length. The 1/|x−x′| kernel is the
  geometry of an isotropic deficit spreading from each element — mathematics of superposed
  shadows, no field-primitive imported.
- **Circulation channel (PPT06 traction):** the knot's surface runs at 1.83c; the dragged
  medium circulates; the far velocity field is the Biot–Savart integral over the closed curve
  — again mathematics (summed drag geometry). ADJ-0: this channel is REPORTED this run; the
  committed energy chain uses the occlusion channel's relative modulation only.

## 3. The multipole ladder, derived

Expand 1/|x−x′| in solid harmonics about the origin. The moments of the arclength-weighted
knot decide everything:

- **l=0 (monopole):** total occluded length → Φ₀ = M₀/r. **α₀ = 1.** (Extraction-anchored:
  the content is that the INSTRUMENT recovers it; the physics is Law III's baseline.)
- **l=1 (dipole): ZERO analytically.** ⟨x⟩,⟨y⟩ vanish because the speed |x′(t)| contains only
  harmonics of 3t while (R + r cos 3t)·cos 2t contributes frequencies 2 ± 3k ≠ 0; ⟨z⟩
  vanishes by t → −t parity (z odd, speed even). **G2-dip:** any l=1 content in the solver is
  instrument error, gate < 10⁻³ relative.
- **l=2 (quadrupole):** the knot is OBLATE — z-extent r = 0.168 fm against xy-extent
  ~R = 0.673 fm — so Q_zz = ∮(3z′² − r′²) dl < 0, nonzero. Potential term c₂ P₂(cosθ)/r³.
  **α₂ = 3.**
- **l=3, m=3 (the trefoil signature):** the solid harmonic Re(x+iy)³ picks up
  (R + r cos 3t)³ e^{i6t} whose 3Rr² cos²3t term contains e^{−i6t}/4 — the integral over t
  survives: **M₃₃ ∝ Rr² ≠ 0**, amplitude ∝ ρ² (aspect-dependent AMPLITUDE, aspect-independent
  EXPONENT — exactly what G2f checks). A plain circular torus has M₃₃ = 0: this moment IS the
  knot, not the torus. Potential term ~ cos 3φ · sin³θ / r⁴. **α₃ = 4.**

The committed ladder 1/3/4 is therefore not an aspiration — it is the multipole arithmetic of
a compact, centred, oblate, three-lobed line source. If a P0-validated instrument refuses it,
the arithmetic above is wrong and dies.

## 4. The energy coupling (committed; the solver may not improvise)

The electron's seat energy is its movement budget in the local wake (APS01 velocity-seat
chain; v₀ = αc at a₀). The wake's angular structure modulates the drafting field fractionally:

δ(θ, φ; r) = [Φ(r,θ,φ) − Φ̄(r)] / Φ̄(r) — normalisation-free (σ cancels).

**ΔE(route) = m_e v₀² ⟨δ⟩_route**, leading order, valid only if |δ| < 0.1 (else STOP);
s–p split = ΔE(equatorial band) − ΔE(polar band), bands fixed in the RUN_LOG.
Error O(δ²) — at the envelope δ ~ 10⁻¹⁰ this is beyond negligible; the validity gate exists
for honesty, not decoration.

## 5. Hand envelopes (R1, order-of-magnitude only — the run produces the numbers)

δ₂(a₀) ~ (R/a₀)² ~ (0.673 fm / 0.5292 Å)² ~ 1.6×10⁻¹⁰ → ΔE ~ 27.2 eV × 10⁻¹⁰ ~ 4×10⁻⁹ eV →
ν ~ 1 MHz-order. δ₃(a₀) picks up a further (R_p/a₀) ~ 1.6×10⁻⁵ → tens of Hz — negligible in
the split; its cos 3φ signature is the trefoil's fingerprint for the φ-resolved report.

Scaling powers for P5 (from the coupling form, no freedom): ΔE_quad ∝ m · v₀² / a², v₀
mass-blind ⇒ muonic/electronic = (m_μ/m_e)(a₀/a_μ)² = 7.14×10⁶ — the Fork-C-shaped power.
Fork-B's measured whole-shift ratio is 4.6×10⁴; if the run's moments confirm the powers,
Fork-B dies at P5 on scaling alone. All committed in the RUN_LOG before the solver ran.
