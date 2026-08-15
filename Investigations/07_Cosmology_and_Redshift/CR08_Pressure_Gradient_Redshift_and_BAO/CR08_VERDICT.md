# CR08 — Verdict: Pressure-Gradient Redshift and BAO

**Author:** James Christopher Tyndall, Melbourne. **Date:** 2026-07-03; B15 extension 2026-08-15.
**Tool:** `cr08_bao_consistency.cpp` → `results.txt`. Gates and the fixed (no-freedom) SDT law were pre-registered in `RUN_LOG.md`. Data: consolidated BOSS DR12/eBOSS + Planck θ*, memory-transcribed OBSERVED anchors (±2% risk, flagged; verdicts below rest on ≥5% or factor-2 margins, so they survive the transcription risk). ΛCDM column = rival OBSERVED-comparison only, never in the SDT chain.

## Dual verdict

**Prompt completion: B** (all three original success criteria evaluated; none passed its registered gate).
**Physics class: FALSIFIED** (static exponential-strain law vs BAO) **/ IDENTITY** (the former target-defined duration).

## The numbers (H₀ = 67.4 anchor; 73.04 is uniformly worse — see results.txt)

| Observable | Result | Gate |
|---|---|---|
| G1: 11 survey BAO points (z = 0.15–2.33) | SDT low by 3–12% almost everywhere; **10/11 beyond 3%, 8/11 beyond 5%**; χ²(SDT) = 131.7 vs χ²(ΛCDM, Ω_m=0.31) = 8.2 | **FAIL** |
| G2: 147 Mpc = c_s × t_coupled | t_coupled ≡ BAO_scale/c_s in cosmology.hpp — defined from its own target | **IDENTITY** (cannot pass) |
| G3: CMB acoustic angle | θ_SDT = 4.72 mrad vs θ_obs = 10.41 mrad — **factor 2.21 miss** | **FAIL** |
| G4: no dark energy | true in the SDT chain | earns nothing while G1/G3 fail |

Structure of the failure is informative: the SDT deficit is worst at intermediate z
(−10 to −12% at z = 0.38–1.48) and nearly closes at z = 2.33 (−3.2% D_M, +1.8% D_H — the only
point inside errors), because SDT's effective H(z) = H₀(1+z) crosses ΛCDM's √(Ω_m(1+z)³+Ω_Λ)
near z ≈ 2. Also: d(1100) = 31,153 Mpc reproduces the engine R_CMB (0.9%) — that is CR03's
Route A consistency, restated, not a success here.

## What this settles

1. **The pure exponential strain law 1+z = e^(σ₀d) is falsified against BAO** — independently of
   CR06, which already measured its failure on SNe (χ²/dof = 8.33; data prefer n ≈ 0.66).
   Two independent datasets now falsify the same law-form. It should not be quoted as "the SDT
   distance law" anywhere in the repo without this caveat.
2. **The CMB acoustic angle is a factor-2.2 structural miss, not a percent-level one.** A
   constant 147 Mpc physical ruler at the SDT static distance subtends 4.7 mrad; the sky says
   10.4 mrad. Fixing it requires the ruler at the Clearing to be ×2.2 larger (epoch-dependent
   equilibrium length — possible in the aging-glass picture but currently pure conjecture) or
   a different high-z distance law. Either is new physics that must be derived, not fitted.
3. **The "BAO from lattice sound speed × coupled epoch" story is circular in the engine's own
   header** (same root as CR03 Route B). The derived content of c_s = c/√3 is CR13's
   opacity-conformal-bound link; the 830-Myr t_coupled has no independent derivation.
4. CR12's headline stands unchanged and is the right frame: dark energy is not *required*
   (coasting fits SNe without Λ), but **SDT does not beat ΛCDM** — and on BAO, as coded, it
   loses outright.

## §D — Seven questions

1. **Why fail?** The static ln-law's effective expansion history H_eff(z) = H₀(1+z) is too
   steep at low z (−12% D_H at z=0.38) and its ruler-to-distance ratio at z=1100 is ×2.2 off.
   Magnitude and sign both pinned in results.txt.
2. **Recoverable?** Not by tuning H₀ (both anchors fail; 73.04 is worse everywhere). The
   z-dependence itself is wrong.
3. **What did the target fail to account for?** That BAO measures *both* dθ and dz per ruler —
   a static exponential law cannot satisfy both at once anywhere but one crossing point (z≈2).
4. **Errored premise?** "σ is constant along the path and redshift compounds exponentially."
   CR07 (octave, non-compounding) and CR10 (cubic rung z³) already reject pure compounding —
   this run confirms the compounding form specifically fails hardest.
5. **What freedom corrects it?** The CR10 cubic/octave rung structure (native, already in the
   canon) as the propagation law instead of e^(σd); and/or an epoch-dependent equilibrium
   length Λ_BAO(z). Both are named SDT quantities, not knobs — but neither is derived to the
   point of producing D_M(z).
6. **Native or knob?** CR06's measured n ≈ 0.66 is a knob until derived; CR10's z³ rung is
   native but has no distance-law closure yet.
7. **Cascade?** YES, twofold: (a) G2 shares the **t_coupled circularity root with CR03**;
   (b) G1/G3 share the **"no derived propagation law d(z)" root with CR06/CR12** — the
   exponential was an assumption, and it is now doubly falsified.

**Recovery: PARTIAL** — the failing premise (exponential compounding) is named and already
contradicted inside the canon (CR07/CR10); the native successor (octave/cubic-rung distance
law) exists as structure but not as a computable d(z). No recovery can be claimed until that
law is built and re-run under pre-registration.

**earned:** independent falsification of the exponential distance law on BAO and SNe; the factor-2.21 CMB-angle miss quantified; engine circularity (t_coupled) exposed; crossing-point structure (z≈2) documented for the successor law.
**owed:** derived d(z) from octave/cubic rung; independent `t_coupled` for CR03 Route B; re-run with source-verified BAO table (transcription check).

> **Prompt completion B · Physics class FALSIFIED (exponential strain law vs BAO; old G2 IDENTITY) · Recovery PARTIAL · Cascade roots: target-defined t_coupled (shared CR03) + underived propagation law d(z) (shared CR06/CR12).**

## B15 standing-equilibrium extension — 2026-08-15

CR17b established that the native Clearing is an obstacle-loading depinning
window, not the ionisation/line-of-sight `optical_depth=1` clock assumed by the
first B15 freeze. The three registered optical roots missed the Clearing band,
so no population curve was inserted to force one back. The executed pivot asks
for the spatial standing equilibrium directly.

Forward chain:

```text
FIRAS T_CMB + BBN-deuterium eta
  -> baryon/radiation resistance equality N_eq
  -> Prop-13 local baryon count
  + phase-resistance length per baryon
  -> uniform-sphere escape response
  + baryon-loaded rank-2 relay speed
  -> acoustic round-trip standing radius
  -> Prop-13 present-equivalent scale
```

The sealed values, emitted before reading the BAO comparison, are:

- `N_eq = 902.169740`, with `R = 3/4`;
- `n_b(N_eq) = 1.8397029×10^8 m^-3`;
- `c_s = 1.3084016×10^8 m/s = 0.436436 c`;
- escape response `Γ = 1.3117011×10^-14 s^-1`;
- physical standing radius `0.161631 Mpc`;
- present-equivalent scale **`145.818917 Mpc`**.

The radial finite-volume route agrees with the analytic response to
`7.8×10^-11`; changing 20,000 to 40,000 shells moves it by `2.3×10^-10`.
FLM15 opacity across the physical radius is already greater than unity at the
conservative proton boundary (`τ=2.227`), rises to `27.208` for free
electron-plus-proton boundaries, and remains larger for a bound seat. Thus the
standing region is coupled without selecting a free/bound population curve.

Registered controls remain distinct:

- loading-depinning endpoint `R=1`: `157.502 Mpc`;
- orbital rather than escape response: `206.219 Mpc`;
- travelling rather than standing mode: `291.638 Mpc`.

Only the frozen energy-equality/escape/round-trip route was compared. Against
`147.09 Mpc`, its residual is **0.8642%**, inside the existing 3% gate.
Therefore **B15 advances to COMPUTED**. This does not rehabilitate the
falsified exponential distance law, the G1/G3 BAO-angle failures, or the old
target-defined `t_coupled`; it replaces only B15's literal ruler with an
SDT-native resistance-standing scale. Provenance remains shared with FIRAS and
BBN deuterium, and `koppa_per_baryon` retains its disclosed Planck-seat risk.
