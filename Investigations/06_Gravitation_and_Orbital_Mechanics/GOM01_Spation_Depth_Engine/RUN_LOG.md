# RUN_LOG — GOM01 Spation Depth Engine (zk² = 1)

> **Executor:** Claude (HUNTER-disciplined), on behalf of J. C. Harvey, Melbourne. **Date:** 2026-07-03.

## Pre-Run Commitments — GOM01 (written BEFORE first compile/run)

- Prompt completion target: B
- Physics class hoped: CONVERGENCE (all four observables are the standard weak-field GR
  results with ϟ ≡ GM/c² substituted — z(r) = ϟ/r IS GM/(c²r); the PROMPT's §6 already
  stamps [x] PASS on everything, which is itself a red flag: those boxes were pre-ticked
  in a SPEC. This run re-derives the numbers for real and re-grades.)
- CALIBRATED budget: 0
- Engine namespaces: bridge::, sdt::cosmology::strain, measured::. No G/M in the SDT
  chain (GM_equivalent used only in disclosed "GR BRIDGE (verification only)" rows).
- Phase thresholds (committed before run, from PROMPT §⑩): 0.01% for Pound–Rebka vs
  gh/c², Shapiro closed-vs-GR, bending closed-vs-GR; 0.5% for absolute anchors
  (2.46e-15, 1.75″) as coded.
- Pre-declared audit flags:
  1. zk² = 1 rows (I.2a, I.2b) are algebraic IDENTITIES — they may count as notation
     checks only, never as physics passes. Same for VI.2 (σ = H₀/c is a definition),
     VII.1 (DE/E = Δz is self-consistent by construction), VIII.1/VIII.3 (prove(1,1)
     rhetorical passes — these are NOT tests at all and will be called out).
  2. Every "SDT vs GR" agreement is CONVERGENCE: identical formulae after ϟ = GM/c².
     The bending factor-4 "emerges naturally" claim must be checked: the prefactor 2 in
     α = 2∫∇⊥z dl is put in by hand (matching laws.hpp), so the 4 is 2(assumed)×2(integral)
     — the doubling is inherited, not derived. Grade accordingly.
  3. Exit code must be 0 only if all proofs pass; report N/N honestly.
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS as physics.

## Build log

- 2026-07-03: compiled AS-IS, zero source edits. MSVC 19.44.35223 x64. Exit 0.

## Run log

- 2026-07-03: `gom01_spation_depth_engine.exe` → exit 0, **27/27 proofs passed**,
  full stdout in `results.txt`.
- Substantive numeric rows (all within committed gates):
  - Pound–Rebka: 2.468886e-15 vs gh/c² 2.468895e-15 (0.0004%) and vs measured
    2.46e-15 (0.36%, gate 0.5%) → PASS
  - Solar redshift 2.113e-6 vs GM/(c²R) (0.47%, gate 0.5%) → PASS
  - Shapiro: numerical integral vs closed form 0.0001%; closed form vs GR formula
    0.0000% (same expression — trivial) → PASS
  - Bending: 1.7517″ vs 1.75″ (0.097%, gate 0.5%) → PASS
- Audit flag 1 CONFIRMED: of the 27 "proofs", ~13 are booleans (1.0 vs 1.0), algebraic
  identities (zk²), definitions (σ=H₀/c), or rhetorical prove(1,1) rows (VIII.1, VIII.3
  test literally nothing). The honest substantive count is ~10 numeric comparisons, all
  CONVERGENCE-class.
- Audit flag 2 CONFIRMED (factor of 4): the "2" prefactor in α = 2∫∇⊥z dl is imported
  from laws.hpp, which was written to reproduce GR. IV.4 verifies 2×(2ϟ/b) = 4ϟ/b —
  arithmetic, not a derivation. The claim "no GR doubling to explain" is NOT earned.
- New defect found (not pre-flagged): Section III compares the ONE-WAY Shapiro form
  (2ϟ/c)ln(4r₁r₂/b²) = 123.66 µs against "Measured ~200 µs" (the round-trip radar
  figure ≈ 250 µs) and stamps PASS via a `> 100 µs` gate. The formula agreement with GR
  is exact (same expression); the "measured" row is a category error (one-way vs
  round-trip) hidden by a gate 2× wide. Recorded as a defect in the tool's presentation;
  the physics content (formula identity with GR) is unaffected.
