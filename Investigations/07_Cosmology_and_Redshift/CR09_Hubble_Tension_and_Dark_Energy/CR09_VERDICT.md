# CR09 — Verdict: Hubble Tension and Dark Energy

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03.
**Tool:** `cr09_tension_window.cpp` → `results.txt`. Gates W1–W4 pre-committed in `RUN_LOG.md`. H₀ was **not derived** anywhere — 67.4 and 73.04 are OBSERVED anchors (engine `strain::`); the run tests only the geometric consistency of the SDT gradient-steepness story.

## Dual verdict

**Prompt completion: B** (Phases A and C executed; B and D honestly delegated — B = CR12 already fitted Pantheon+ [SDT coasting DEGENERATE, ΔAIC≈90 behind ΛCDM]; D = CR08 just executed [KILLED]).
**Physics class: KILLED** (isotropic radial-gradient dissolution) **/ OPEN** (anisotropic line-of-sight version, out of scope).

## The result

The tension requires **κ_local/κ_global = σ_l/σ_g = 1.0837**, coherent across the entire SH0ES
Hubble-flow window (0.023 < z < 0.15, i.e. 93–574 Mpc deep). A piecewise strain enhancement of
that amplitude was scanned over every transition depth z_t from 0.001 to 1100 (122 log-spaced
values) against four pre-committed gates:

| z_t placement | What happens | Gate broken |
|---|---|---|
| z_t ≤ 0.023 | SH0ES window sits in the *global* zone → recovers 67.4–69.9, not 73 | W1 |
| 0.023 < z_t < 0.15 | window straddles the step → recovered H₀ < 72 AND internal tilt | W1+W2 |
| 0.15 ≤ z_t ≲ 2.3 | Pantheon+ sees a 0.13–0.175 mag step (bound: 0.05) | W2 |
| 0.38 ≤ z_t | BAO bins sit in the enhanced zone → implied ladder H₀ → 73.0 vs 67.4±1.1 | W3 |
| z_t ≳ 2.3 | SNe blind, but W3 still broken; by z_t ≳ 2 the CMB path-average also shifts >1% | W3+W4 |

**Result: 0 of 122 placements pass. The window is empty.** The pincer is exact: W1 forces the
enhancement to reach z ≥ 0.15; W2 forbids any 8.4% strain step anywhere in 0.023 < z < 2.3;
W3 forbids it beyond. These jointly exclude every radius.

## What this settles

1. **The prompt's Phase-C claim ("SDT predicts H₀(local) > H₀(CMB) — exactly what is
   observed") is not available as an isotropic radial mechanism.** Sampling "the steep part
   of the gradient" cannot produce 73 in the SH0ES window without leaving a supernova-visible
   scar — the same SNe that calibrate the 73.
2. **What survives is exactly what CR06 left open**: an *anisotropic* or per-line-of-sight
   κ-variance (the emission-half / host-environment term), or an effect inside the calibrator
   rung (z < 0.023), which is Cepheid territory that no σ(d) profile touches. Those are
   different mechanisms with different signatures, and neither is quantified in SDT today.
3. **Dark energy**: nothing new earned here. CR12 stands: no Λ is *needed* to fit SNe
   (EdS exclusion is the historic argument), but SDT does not *beat* ΛCDM. This folder adds:
   the tension is not SDT's free win either.
4. Engine hygiene note: `cosmology.hpp strain::` carries the comment "Local pressure gradient
   is steeper near massive structures" as if established — this run shows the radial version
   of that sentence is dead; the comment oversells (canon change = Harvey's call, propose-only).

## §D — Seven questions

1. **Why fail?** Amplitude × coherence: 8.37% over ≥574 Mpc is too large to hide — the
   asymptotic μ-step is 5·log₁₀(1.0837) = 0.175 mag against a 0.05 mag bound, and the BAO
   ladder pins σ̄ to 1.6% at five depths.
2. **Recoverable?** Not radially. Smooth profiles only smear the same integral constraint
   (and tuning one to thread the gates would be a FISHED RECOVERY — forbidden in RUN_LOG).
3. **What did the target fail to account for?** That SH0ES's H₀ is measured *through* the very
   region the gradient must occupy; the explanation and the measurement share a footprint.
4. **Errored premise?** "The tension is a radial sampling effect of one scalar σ(r)." The
   tension is a *calibration-chain* discrepancy, not a distance-shell discrepancy.
5. **What freedom corrects it?** Per-source emission term (zk²=1 host-environment shift, the
   CR06 emission half) — acts on calibrators without deforming μ(z); or κ-variance across
   lines of sight (sky-anisotropic, testable against SH0ES sky-quadrant splits).
6. **Native or knob?** Native in form (emission z = ϟ/r is canon), but its magnitude for SN/
   Cepheid hosts is underived — currently a hypothesis, not a number.
7. **Cascade?** Partial: shares the **underived propagation/emission split quantification**
   root with CR06 (which tested only the propagation half). Independent of the CR03/CR08
   t_coupled root.

**Recovery: PARTIAL** — the radial premise is killed cleanly; the named native successor
(emission-half host term) exists in canon but has no derived magnitude; it needs its own
pre-committed run against the SN host-mass step (CR06's stated next step).

**earned:** the empty-window theorem (0/122, three-sided pincer, all gates pre-committed); the tension re-classified from "SDT explains it" to "SDT must route it through the emission half or lose it"; engine comment oversell flagged.
**owed:** emission-half magnitude (host-term) derivation + host-mass-step test; sky-anisotropy split test.

> **Prompt completion B · Physics class KILLED (isotropic radial gradient) / OPEN (emission-half route) · Recovery PARTIAL · Cascade root: emission/propagation split unquantified (shared with CR06).**
