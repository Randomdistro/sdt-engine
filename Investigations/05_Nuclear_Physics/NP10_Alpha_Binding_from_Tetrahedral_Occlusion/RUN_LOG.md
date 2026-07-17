# RUN_LOG — NP10: Alpha Binding from Tetrahedral Geometry (NP17 premise)

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03. **Written BEFORE any tool code.**
> Engine: `#include <sdt/laws.hpp>` only.

## Pre-Run Commitments — NP10

- Prompt completion target: B
- Physics class hoped: NATIVE; honest floor accepted: OPEN (expected: the pure-electrostatic
  number FAILS, per NP17's declared PENDING — the deliverable is then the *measured size and
  scaling* of the missing lock term, not a fake pass)
- CALIBRATED budget: **0**
- Engine namespaces: `measured`, `coulomb_identity`, `nuclear` (R_He_predicted)

## Premise correction (per 2026-07-03 PROMPT note, applied BEFORE running)

NP09's scalar-occlusion E_pn FAILED (−97.3%); FLM12-D1 killed the linear volume price.
The PROMPT's Step-2 bond formula (4·E_pn + E_nn + (E_pp − E_C) with occlusion E's) is
therefore dead as written. Substituted premise: **NP17 shared-electron Coulomb well** —
alpha = 4p + 2e, E = −Σ q_i q_j αℏc/r_ij, no fitted energy scale.

## Committed configurations (geometry fixed BEFORE any energy is computed)

1. **Alpha, NP17-exact (continuity):** 4 protons at regular tetrahedron, **edge a = 2R_p**
   (boundary contact); 2 electrons at midpoints of two OPPOSITE edges (the interlocked-
   deuteron reading). This is byte-for-byte NP17's committed configuration.
2. **Alpha, D-spaced variant:** same shape, edge a = D = 2R_p + R_p/3 (deuteron bond length).
3. **Triton, chain (committed):** p–e–p–e–p collinear, adjacent p–p spacing D, electrons at
   bond midpoints (two NP17 deuteron bonds sharing the middle proton).
4. **Triton, triangle variant:** 3 protons equilateral edge D, electrons at two edge midpoints.

No other configurations will be tried after seeing energies (no geometry fishing).

## Gates (committed now)

- **G1 — headline:** |E(α, config 1) − 28.296|/28.296 ≤ 20% → else FAIL→OPEN with the lock
  remainder R_lock = 28.296 − E quantified. (Expected FAIL ≈ −84% per NP17; committed anyway,
  not softened.)
- **G2 — size:** |2R_p − R_He_meas|/R_He_meas ≤ **1% (blind bar; NOT the known 0.43%)**.
- **G3 — ratio structure:** B_α/B_t predicted vs measured 28.296/8.482 = 3.336, gate ±20%,
  scored for BOTH consistent pairings (config 1 vs 3; config 2 vs 3/4). Purpose: decide
  whether the missing lock term is a COMMON multiplicative factor (ratio would pass) or
  coordination-dependent (ratio fails) — either outcome is information, only one is a pass.
- **G4 — μ_α = 0:** qualitative pairing-cancellation statement; class ceiling DEGENERATE
  (declared now: every model predicts 0 for spin-0).
- **G5 — inversion (record):** edge required for 28.296 MeV electrostatically; if < 2R_p,
  unphysical → confirms the lock remainder is real, not a spacing choice.

## Forbidden retroactive changes
New electron placements after seeing energies; widening 20%/1%; selling G2 (an existing
laws.hpp result, class C-flagged) as a new NP10 discovery; occlusion-route resurrection.

## Planned outputs
`np10_alpha_binding.cpp` → MSVC → `np10_results.txt` (redirected) → `NP10_VERDICT.md`.

---

# RUN 2 — ROOT-CONTACT: the shared-seat contact wall (2026-07-05)

> **Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-05. **Written BEFORE any tool code.**
> Mission: the REGISTERED THREE-FIELD CROSS-CHECK (STACK §3b, ROOT-CONTACT / CH07 §D7):
> one derived wall mechanism must SIMULTANEOUSLY produce
> (a) k(H₂) ≈ 575 N/m, (b) the NaCl +9.4% correction (861→787 kJ/mol), (c) the alpha
> lock ×6.35 (ladder ×1.01/×1.98/×6.35). One function, ONE constant set, no per-target
> tuning. Engine: `#include <sdt/laws.hpp>` only.

## Committed mechanism (declared with native justification BEFORE running)

**THE CONTACT LEDGER — two faces of one scarce resource (rim engagement), zero fitted
parameters, constants = {αℏc, a₀, R_p} from laws.hpp only.**

**Face R (radial, two-body) — the saturated-occlusion ledger (the FARMER-ordered test):**
every unlike-charge (deficit/shadow) pair term is the EXACT solid-angle occlusion of a
finite seat, not the far-field point limit:
- Force: F(r) = (q₁q₂αℏc/r²)·G(x), G(x) = 2(1−√(1−x))/x, x = (R̂/r)² — the canonical
  two-regime form (E105/GOM13), g→2 at the half-sky ceiling.
- Energy (exact integral): E(r) = −(αℏc/R̂)·2A(R̂/r), A(s) = (√(1−s²)−1)/s + arcsin(s),
  for r ≥ R̂; for r < R̂ the force holds at the ceiling 2αℏc/R̂² (linear energy) —
  committed extension, declared.
- Like-charge (surplus/focus) pairs stay point 1/r at ALL r: EMC03 asymmetry — the
  focused surplus has no half-sky ceiling. DECLARED ON FAITH (§G item 1).
- **Cage rule for R̂ (declared):** R̂ = min(a₀, cage half-gap). Molecular/ionic seats
  (H₂, NaCl): no fm-scale cage ⇒ R̂ = a₀. Nuclear shared seat: caged by proton
  boundaries ⇒ R̂ = (D − 2R_p)/2 = R_p/6. §G item 2.

**Face T (combinatorial, many-body) — the angular-window allocation (Harvey's
angle-premium refinement):** contact angle is the scarce resource; a shared seat engages
its Z destinations SEQUENTIALLY (FLM14 rotating-spation sequential occupancy). The lock
multiplicity = number of distinct closed sequential tours of Z destinations =
**(Z−1)!** (circular permutations). B = (Z−1)! × E_electrostatic.
d (Z=2): ×1 · t (Z=3): ×2 · α (Z=4): ×6. Chemistry two-centre bonds (Z=2): ×1 — the
lock face is invisible in H₂/NaCl, natively explaining why pairwise chemistry works.
Energy ∝ tour count is UNDERIVED — §G item 3. The tetrahedron is NOT hard-coded:
Face T sees only the destination count Z; geometry enters only through E_es.

## Gates (committed NOW, before any number is seen; tolerance 25% each)

- **GA — k(H₂):** joint (R,x) minimisation of the Face-R-corrected CH07 shared-seat
  energy (seats at ±xR on the perpendicular bisector; p-p and e-e surplus point terms;
  4 p-e deficit ledger terms, R̂ = a₀). Gate: minimum exists AND |k − 575|/575 ≤ 25%
  at the PREDICTED minimum. Secondary (reported, informal band 25%): R_min vs 0.7414 Å.
- **GB — NaCl correction:** ΔU_wall = Σ over rock-salt shells of (ledger − point), unlike
  pairs only, at r₀ = 2.820 Å (CH02 framework, M = 1.747574 untouched). Required:
  −74.0 kJ/mol (binding reduction 861.0 → 787). Gate: SIGN must be binding-reducing AND
  |ΔU − (−74)|/74 ≤ 25%.
- **GC — alpha lock:** required boost = B_alpha/E_es(α, NP17-exact config) ≈ ×6.35
  (recomputed in-code from run-1's committed configs, byte-identical geometry).
  Gate: |(Z−1)! − required|/required ≤ 25% at Z=4. Support rows (each ±25%):
  B_d = 1×E_es(d), B_t = 2×E_es(t-chain), B_α = 6×E_es(α) vs 2.224 / 8.482 / 28.296 MeV.
- **CONJUNCTION (the registered cross-check):** PASS only if GA ∧ GB ∧ GC.

## Pre-declared expectations (honest, before running)

- The deficit ledger obeys E_exact/E_point = ρ(π−2ρ) ≥ 1 for all ρ = r/R̂ > 0.444:
  exact occlusion ENHANCES attraction everywhere above deep interpenetration. Therefore
  **GB is expected to FAIL IN SIGN** (ledger adds binding; the correction needs binding
  removed) and **GA is expected to FAIL HIGH** (the well deepens; the wall then comes
  only from the surplus 1/R divergence at very short R ⇒ R_min too small, k too stiff).
  Committed anyway, not softened — if Face R fails these, the FARMER premise
  ("saturated occlusion IS the lock/wall") is falsified at chemistry scale and the kill
  is the deliverable.
- **GC expected PASS (−5.5%).** DECLARED LOOK-ELSEWHERE: the ladder ×1.01/×1.98/×6.35
  was already published (run 1); (Z−1)! is a POST-DICTION with a committed native form.
  Simple candidates tried against the ladder before commitment: (Z−1)! ≡ n! (fits, −5.5%
  at α), Catalan (1,2,5: −21%), 2^C(n,2) (1,2,8: +26%), (Z−2)!! (1,1,2: dead). Two of ~5
  fit ⇒ not unique; falsifiable content = Z=5 seat-tour lock ×24 (future run) and the
  simultaneous d/t/α fit with ZERO constants.

## Diagnostics (committed now, NOT gated)

- **D1 — budget-wall rival (flagged):** E_wall = Σ_seats (ℏ²/2m_e)/s², s = p-e seat
  distance — FLM12's confinement cost (ℏ/Δx), Law-IV/V budget reading. FLAGGED: formally
  degenerate with the QM zero-point form; earns at most CONVERGENCE; reported to fence
  the true scale of the chemistry wall (feeds ROOT-BUDGET if Face R dies).
- **D2 — deuteron anchor consistency:** Face R at nuclear scale (R̂ = R_p/6) must leave
  NP17's deuteron within 2% of its point value (−1.1%); if the ledger breaks the
  deuteron, the cage rule is falsified too.
- **D3 —** report the NN enhancement factor at NaCl (quantifies the GB sign failure).

## Forbidden retroactive changes

Widening 25%; re-choosing R̂ / the cage rule / the sub-boundary extension after seeing
numbers; swapping (Z−1)! for another sequence after seeing errors; promoting D1 to a
gated result; selling GC's post-diction as a blind prediction.

## Planned outputs (run 2)

`np10_contact_wall.cpp` → MSVC (build.bat, vcvars64) → `np10_contact_wall_results.txt`
(redirected stdout) → new RUN-2 section appended to `NP10_VERDICT.md`.
