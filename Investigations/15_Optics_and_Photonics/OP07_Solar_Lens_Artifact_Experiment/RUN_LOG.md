# OP07 — Run Log

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-04.

## Pre-Run Commitments — OP07 (written BEFORE first compile/run)

- Prompt completion target: **C** (forward model + protocol + discriminator; P4 robustness partial)
- Physics class hoped: honest — the medium descriptor is standard measured gas/plasma refractivity,
  so the MECHANISM class ceiling is **DEGENERATE/CONVERGENCE**; the deliverable is the QUANTITATIVE
  R(λ) curve and the binary falsifier
- CALIBRATED budget: 0 fitted-to-target; the T(h)/n_e(h)/ρ(h) profile is MEASURED-INPUT **in kind**
  (approximate transcription of the published VAL III Model-C figures — flagged; a digitised table
  is owed for publication grade); κ(λ) H⁻-like opacity table is SCHEMATIC MEASURED-INPUT
- Engine solar parameters used: `measured::R_Sun`, `measured::AU`, `measured::r_e`,
  `bridge::koppa_Sun` (gravitational closure — no G, no M)
- **The §A discipline (committed): NO gate requires the fold to exist.** Gating fold-presence would
  be drawing the caustic in by hand (PLUG). If the honest medium produces no visible fold, that is
  the result and H2-as-modelled is reported KILLED/OPEN per the prompt's own pivot table.
- Model structure (committed): n(h,λ) − 1 = μ_neutral(ρ(h), λ) + μ_plasma(n_e(h), λ) + 2·z_grav(h);
  bending α(b) by the tangent-ray integral (u-substitution, singularity-free); visible limb b_vis(λ)
  at slant optical depth τ = 1 with H⁻-like opacity ∝ κ₀(λ)·(n_e·T)/(n_e·T)₀·ρ; apparent mapping
  θ_app(b) = b/D + α(b,λ); fold = non-monotonic θ_app(b) within the visible region.
- Phase gates (committed before run):
  - G1 (integrator validation): with matter terms OFF, α(b) at the limb within 1% of the closed
    form 4ϟ/b (the engine's own depth-closure limb value; validates machinery, no physics claimed)
  - G2 (deliverable): R_app(λ) table over 400–1600 nm produced, with per-λ: h_vis, α(b_vis),
    limb elevation, fold Y/N + height range + angular width; PLUS controls (plasma-term-off;
    neutral-term-off) to isolate what drives any structure
  - G3 (discriminator): binary falsifier printed with numbers (fold band vs smooth monotonic R(λ))
  - NOT gated: fold presence; fold at any particular temperature band
- §G mirror check: the kill condition is the MEASURED λ-scan outcome (smooth R(λ) kills), not any
  rival axiom; conversely no gate presumes the standard layered story either. z ≪ 1 everywhere in
  the modelled shell (checked in-tool).
- Forbidden retroactive changes: tuning T(h)/κ(λ) to manufacture a fold; inserting a caustic by
  hand; widening the temp-min band post hoc; gating fold-presence after seeing the output.

## Gate decisions (to be filled ONLY from real tool stdout after the run)

| Gate | Result | Notes (from `results.txt`, final run 2026-07-04, exit 0) |
|------|--------|-------|
| G1 | **PASS-GATE** | integrator vs engine closed form 4ϟ/b: 1.751689″ vs 1.751689″ (dev 1.25e-07); z ≪ 1 checked |
| G2 | **PASS-GATE (deliverable)** | R_app(λ) table 400–1600 nm; fold present at ALL λ, band [h_vis → ~770 km], width 7.0–9.9″; controls: neutral 1.157″ vs plasma −1.6 mas at 500 km/1600 nm (ratio ~346:1 at temp-min) |
| G3 | **PASS-GATE** | R(λ) monotone (steps +0.17″ to +0.54″, 9.99″→12.88″); corrected falsifier printed |

### Run history

- Run 1: printf format bug mangled the fold-band column; fold_top tracked last-onset not first →
  band width under-reported (770 mas). Fixed to global max→min characterisation. **No thresholds
  involved** — display/bookkeeping only. Run 2 numbers coherent (width ≈ α(h_vis) as cross-checked).
- Run 3 (final): G3 falsifier text corrected to match the model's own finding (the prompt-version
  temp-min discriminator is killed by the model itself; keeping the stale line would have had
  `results.txt` contradict its own H2/H3 driver check).

### The §A discipline held

Fold presence was never gated. The model was free to return "no fold" — it returned a fold, but a
**limb-generic** one (neutral-density driven), NOT the committed hypothesis's temp-min fold. H2/H3
as written are KILLED as modelled; see `OP07_VERDICT.md` for the seven questions and recovery.
