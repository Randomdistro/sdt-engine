# APS04 RUN_LOG — direct execution 2026-07-26

## Pre-Run Commitments — APS04 (final spec 2026-07-26) — WRITTEN BEFORE ANY CODE

- Prompt completion target: **B** (G4c needs the machine-readable NIST line list, not fetched
  this run — taken as an honest completion cost, declared now)
- Physics class hoped: CONVERGENCE-candidate on the ladder; honest expectation for the
  magnitude: **Class D/OPEN with Fork-C standing** (see R1 envelopes below)
- CALIBRATED budget: 0 — any fitted quantity anywhere fails this spec
- Aspect: ρ = 1/4 committed; sensitivity {1/8, 1/2} report-only
- Window: r/R_p ∈ [10, 1e5] FIXED (a₀/R_p = 6.29e4 inside); sub-window check per G2e
- Coupling: ΔE = m_e v₀² (⟨δ⟩_eq − ⟨δ⟩_pol), δ = (Φ − Φ̄)/Φ̄ (normalisation-free), v₀ = αc,
  validity δ < 0.1 — committed in P1 before the solver existed
- Bands: equatorial θ ∈ [80°,100°]; polar θ ∈ [0°,20°]∪[160°,180°]; φ-averaged primary,
  φ-resolved reported
- Gates: G0a–e, G1a–b, G2a–f (+G2-dip: l=1 content < 1e-3 relative — the knot's arclength
  centroid vanishes analytically; a violation is an instrument/parametrisation error),
  G3 valid/sign/order/fork-report/value, G4a–b (G4c DEFERRED-data, declared), G5
- Both forks committed: 1057.845 MHz AND 0.145 MHz (electronic nuclear-size line) — P5
  selects, analyst never does
- Measured anchors for P5 (cited, fixed now): muonic 2S–2P full ≈ 202 meV (CREMA);
  muonic proton-size term ≈ 3.7 meV; electronic nuclear-size Lamb term ≈ 0.145 MHz;
  m_μ/m_e = 206.768; reduced-mass a₀/a_μ = 185.84
- Forbidden retroactive changes: widen bands; move windows; per-order windows; pick a fork
  post-hoc; re-scope fired gates; cite pre-2026-07-23 folder results; land-near-1051.8
  without instrument audit

## R1 predictions (hand-derived BEFORE the solver — see APS04_WAKE_GEOMETRY.md for the work)

1. **Ladder:** α₀ = 1 (line-occlusion monopole); l=1 dipole ≡ 0 (arclength centroid at
   origin, shown analytically); α₂ = 3 (quadrupole of an oblate knot; Q_zz < 0 since the
   knot's z-extent r < its xy-extent R); α₃ = 4 with cos 3φ signature carried by the
   3Rr²cos²3t term of (R + r cos 3t)³ — amplitude ∝ ρ², so EXPONENT aspect-independent,
   AMPLITUDE aspect-dependent (G2f shaped exactly for this).
2. **Magnitude envelope (order only, not a fit):** δ₂(a₀) ~ (knot scale/a₀)² ~ 10⁻¹⁰;
   ΔE ~ m_e(αc)²·δ ~ 27.2 eV × 10⁻¹⁰ ~ 10⁻⁹ eV → **ν ~ 1 MHz-order**. Committed reading:
   G3-order should PASS; G3-value should FAIL both forks at ±10% (envelope sits ~10× above
   Fork-C, ~10³ below Fork-B) → expected honest outcome Class D/OPEN, mechanism live.
3. **P5 scaling (derived from the coupling form):** ΔE_quad ∝ m·v₀²/a² with v₀ = αc mass-blind
   ⇒ muonic/electronic ratio = (m_μ/m_e)·(a₀/a_μ)² = 206.768 × 185.84² = **7.14×10⁶**.
   Fork-C measured ratio ≈ 3.7 meV / 0.145 MHz = **6.2×10⁶** → predicted/measured ≈ 1.16,
   inside the factor-3 gate. Fork-B measured ratio ≈ 202 meV / 1057.845 MHz = **4.6×10⁴** →
   off by ~150× ⇒ **Fork-B should die at P5 on scaling**; Fork-C stands; FLM14 inherits the
   bulk magnitude. This prediction is falsifiable by the run (the actual moments could move
   the powers).
4. **Sign:** genuinely unknown until computed — the oblate quadrupole's band-average
   difference decides it. No prediction committed; the gate is live either way.

## ADJ ledger
- ADJ-0 (declared pre-code): the circulation (Biot–Savart) channel is computed and REPORTED
  (velocity-dipole exponent) but the committed energy chain runs on the occlusion channel's
  relative modulation only — the coupling form was committed that way in P1; mixing channels
  post-hoc is forbidden.
- ADJ-1 (declared pre-code): G4c (selection rules vs full NIST list) DEFERRED-data; principal
  series checked qualitatively; prompt completion capped at B for it.
