# OP03 — Run Log

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-04.

## Pre-Run Commitments — OP03 (written BEFORE first compile/run)

- Prompt completion target: **C** (the firewall itself predicts the cap: Huygens summation IS
  interference by construction; the earnable content is λ-scaling + envelopes from geometry)
- Physics class hoped: **CONVERGENCE**, with the obliquity row honestly expected **OPEN**
- CALIBRATED budget: **0** (no fits; all apertures in units of λ)
- Engine namespaces used: `measured::` (ℓ_P for the granularity extrapolation only)
- **Implementation honesty rules (committed):**
  - The screen quantity is the summed arrival-time registers (Σcos, Σsin of 2π·L_j/λ) over
    re-emitting sites — machinery only, no ψ, no probability amplitude, no field.
  - The continuum envelopes (sinc², Airy 1.220λ/D, d·sinθ = mλ) appear ONLY as OBSERVED
    comparison columns, never as kernels.
  - **Located λ entry point (declared up front):** λ enters as the ASSUMED tick periodicity of the
    emission (λ = c_local·T_tick; CR07 ruler λ = N·ℓ_P is a re-parameterisation, not a derivation).
    The relay sum therefore inherits interference by construction; what is earnable is the
    GEOMETRY (angles, envelopes, resolving power), and that only.
- Phase thresholds (committed before run):
  - P1a (continuum limit): max deviation of the discrete sum vs the continuum envelope over the
    first three lobes decreases monotonically with source count M, and < 1e-5 at M = 4096
    (pre-run correction: midpoint-rule error estimate (s²/24)(2π sinθ)² ≈ 9e-7 at M = 4096 makes a
    1e-6 gate marginal-by-construction; 1e-5 committed BEFORE first run — not a retro-gate)
  - P1b (obliquity): committed honest expectation — an isotropic relay re-emission sum does NOT
    produce the obliquity factor (backward/forward intensity ratio = 1). If it emerges, report that
    instead; either way the row is graded on what the run shows.
  - P2: two-source peaks (d = 20λ, m = 1..5) within 0.1% of mλ/d in sinθ; grating N = 10:
    principal maxima within 0.1%, peak-to-first-zero offset within 0.1% of λ/(Nd) ⇒ R = mN
  - P3: single-slit (a = 50λ) first null within 0.1% of λ/a; circular aperture (D = 40λ) first
    dark ring within 0.1% of 1.21967·λ/D (J₁ zero 3.831706/π — OBSERVED column)
  - P4: discretisation-deviation exponent vs spacing s fits 2 ± 0.2 (log-log); extrapolation to
    s = ℓ_P at λ = 500 nm reported with its size (expected ~1e-57 — an honest null if so)
- §G mirror check: no gate legislates against sub-wavelength/near-field behaviour; sub-wavelength
  apertures and evanescent components are constraint-channel territory (FLM14 ADJ-7) — logged OPEN
  in the verdict, not gated. All kill numbers trace to measured diffraction anchors.
- Forbidden retroactive changes: import the continuum envelope as kernel then claim A; insert ψ or
  collapse; hand-insert the obliquity factor and claim emergence; widen tolerances; local namespaces.

## Gate decisions (to be filled ONLY from real tool stdout after the run)

| Phase | Result | Notes (from `results.txt`, final run 2026-07-04, exit 0) |
|-------|--------|-------|
| P1a | **PASS-GATE** | deviation vs sinc² envelope: 1.37e-03 (M=16) → 1.99e-08 (M=4096), monotone |
| P1b | **OPEN (as committed)** | backward/forward = 1.000000 identically — obliquity does NOT emerge from isotropic re-emission; forward-directionality of the relay rule is the unbuilt piece |
| P2 | **PASS-GATE** | two-source maxima m=1..5 rel err 0.0; grating N=10 peak exact, peak-to-zero offset rel err 6.0e-08 ⇒ R = mN = 10 |
| P3 | **PASS-GATE** | slit first null rel err 2.3e-08 vs λ/a; Airy first ring rel err 1.1e-16 vs 1.21967λ/D (chord site-count columns) |
| P4 | **PASS-GATE** | deviation exponent 2.003 (gate 2.0±0.2); extrapolated ℓ_P deviation ~2.4e-62 — honest null, unobservable |

### ADJ-001 — P2-grating first-run FAIL (numeric bracket, not physics)

- **Trigger:** first run found peak-to-zero offset 1.00e-02 = 2/(Nd) (rel err 1.0 vs committed λ/(Nd)).
- **Root:** the zero-search bracket [peak+0.05/(Nd), peak+2/(Nd)] contained BOTH the k=1 and k=2
  array zeros; the scan-grid endpoint landed exactly on the k=2 zero and evaluated deeper.
- **Fix:** bracket [peak+0.5/(Nd), peak+1.5/(Nd)] encloses only the first zero. **Threshold unchanged**
  (allowed adjustment class: "finer numerics/bracket"). Re-run: rel err 6.0e-08 → PASS.
- First-run stdout with the FAIL is preserved in this log entry; final `results.txt` is the re-run.

Note: the tool's printed flag text says "~1e-57-scale" (my pre-run order estimate); the computed
extrapolation is 2.4e-62. The computed number is the citable one; both are unobservably null.
