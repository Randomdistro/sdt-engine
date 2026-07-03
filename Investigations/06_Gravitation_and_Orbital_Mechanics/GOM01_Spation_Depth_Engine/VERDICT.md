# VERDICT — GOM01: zk² = 1 Spation Depth Engine

> **Author:** J. C. Harvey, Melbourne. **Executed:** 2026-07-03 (HUNTER discipline).
> **Tool:** `gom01_spation_depth_engine.cpp` — compiled AS-IS (zero edits), MSVC 19.44,
> exit 0, 27/27 proofs. **Evidence:** `results.txt`, `RUN_LOG.md`.

## Dual verdict

- **Prompt completion: B** (all four observables computed for real; the SPEC's §6
  pre-ticked [x] boxes are now backed by an actual run — but see the inflation audit)
- **Physics class: CONVERGENCE (weak-field GR optics with ϟ ≡ GM/c² substituted), with
  the zk² closure rows labelled IDENTITY**
- **Earned vs owed: the single-scalar-field packaging is earned; the "factor of 4
  emerges naturally" claim is NOT earned (killed below)**

## What the run actually shows (real numbers)

One scalar z(r) = ϟ/r reproduces, with ϟ built from (v_surf, R) only:

| Observable | SDT value | Comparison | Err |
|---|---|---|---|
| Pound–Rebka Δν/ν | 2.4689e-15 | gh/c² = 2.46889e-15; measured 2.46e-15 | 0.0004% / 0.36% |
| Solar surface redshift | 2.113e-6 | GM/(c²R) = 2.123e-6 | 0.47% |
| Shapiro (Earth–Mars, b=R_Sun) | 123.66 µs one-way | GR same formula | 0.0000% (identical expression) |
| Light bending at limb | 1.7517″ | 1.75″ (Eddington) | 0.097% |
| Hubble law (small z) | z = (H₀/c)d | linear regime | <1% |

This is a clean, compact demonstration that all classical weak-field tests are functions
of ONE length ϟ per body. **Class: CONVERGENCE** — z(r) = ϟ/r is numerically GM/(c²r),
and every closed form (Δν/ν = ϟΔ(1/r), Δt = (2ϟ/c)ln(4r₁r₂/b²), α = 4ϟ/b) is the
standard GR expression with GM/c² renamed. Agreement with GR is therefore guaranteed by
construction; agreement with MEASUREMENT (Pound–Rebka 0.36%, 1.75″) is inherited from
GR's own success. No SDT-vs-GR discriminator exists anywhere in this tool.

## Inflation audit (what "27/27" really contains)

- ~10 rows are substantive numeric comparisons (listed above plus integral-vs-closed-form
  checks at 1e-4 %).
- ~13 rows are booleans (1.0 vs 1.0), algebraic identities (zk² = 1 — true for all v ≠ 0,
  **IDENTITY**, not physics), definitions (σ₀ = H₀/c, **IDENTITY**), or self-consistency
  by construction (ΔE/E = Δz).
- VIII.1 and VIII.3 are `prove(1.0, 1.0)` — rhetorical rows that test nothing. The
  tired-light rejection is an argument, not a computation.
- **KILLED claim:** "The factor of 4 arises naturally — there is no GR doubling to
  explain." The prefactor 2 in α = 2∫∇⊥z dl is imported from laws.hpp (written to match
  GR); IV.4 merely verifies 2 × 2 = 4. Until that prefactor is derived from lattice
  mechanics (FLM-class work), the doubling is inherited from GR, not explained.
- **Defect:** Section III labels 123.66 µs against "Measured ~200 µs" with a `>100 µs`
  gate — a one-way formula against a round-trip figure (~250 µs). The gate hides a 2×
  category error. Formula-level agreement with GR is unaffected.

## Disposition

GOM01 stands as the repo's cleanest statement that **gravitational optics = one length
per body**, with the closure zk² = 1 as notation. It earns CONVERGENCE and nothing more:
no prediction here differs from GR, and the two claims that gestured at more (natural
factor 4; tired-light "proof") are respectively killed and reclassified as prose.
The §⓪ question "what don't we know?" remains unfilled in the PROMPT; the honest answer
after this run: **where z(r) = ϟ/r comes FROM** (the occlusion→1/r chain is asserted in
comments, not derived) — that is GOM05/FLM territory and stays OWED.

## §D — Seven questions (on the KILLED factor-4 claim)

1. **Why (exact mechanism)?** The claimed "natural" 4 in α = 4ϟ/b decomposes as
   2(prefactor) × 2(integral). The integral's 2/b is genuinely computed; the prefactor 2
   in α = 2∫∇⊥z dl is **imported** from laws.hpp, which was written to reproduce GR.
   Proof row IV.4 verifies only the arithmetic 2 × 2 = 4, not the physics of the 2.
2. **Recoverable?** In principle: derive the relay/wavefront prefactor from lattice
   mechanics (spation contact-relay optics). That is exactly the un-derived link.
3. **What did the target fail to account for?** That an inherited coefficient cannot be
   claimed as "emergent" — the doubling GR attributes to space-curvature+time-dilation
   is present in the SDT chain as an assumption, not a derivation.
4. **Errored premise?** "The laws.hpp form of the deflection integral is itself
   SDT-native." It is GR-matched packaging; the mechanism under it (occlusion → z(r) →
   wavefront response, including the prefactor) is an open closure, not a possession.
5. **Correcting freedom?** The occlusion→optics derivation chain (GOM05/FLM10-class):
   derive z(r) = ϟ/r and the propagation prefactor from lattice mechanics. Per the
   Closure Principle: CLOSE this loop, do not amputate the claim silently.
6. **Native or knob?** The needed freedom is native-in-kind (lattice mechanics) but
   currently unbuilt; nothing here may be tuned to produce the 2.
7. **Cascade?** **Yes.** Same root as GOM13's altitude-law fork and the GD03/GD04
   rotation failures: the mechanistic occlusion law (how occlusion converts to force/
   optics, with which coefficients) is un-derived. Root logged once as
   **OCCLUSION-MECHANISM**.

**Recovery grade: PARTIAL** (premise-error named, closing route identified as GOM05/FLM
work; the derivation itself is owed, not delivered).

---

**Prompt completion B · Physics class CONVERGENCE (zk² rows IDENTITY; factor-4
naturalness claim KILLED) · Recovery PARTIAL · Cascade root OCCLUSION-MECHANISM.**
