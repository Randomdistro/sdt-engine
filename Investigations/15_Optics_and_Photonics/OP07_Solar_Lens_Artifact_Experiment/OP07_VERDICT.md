# OP07 — Verdict: Solar Lens-Artifact Experiment (falsifier capstone)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Tool: `op07_solar_fold.cpp` (exit 0; stdout in `results.txt`)

## What the forward model actually says (the deliverable)

Rays traced through n(h,λ) − 1 = μ_neutral(ρ) + μ_plasma(n_e,λ) + 2z_grav (VAL-C-class profile as
MEASURED-INPUT in kind; engine ϟ_Sun = 1477.0 m, no G/M; integrator validated on the engine's own
1.751689″ closed form to 1.3e-07):

| λ (nm) | h_vis (km) | limb elevation (″) | fold band (km) | fold width (″) |
|--------|-----------|--------------------|----------------|----------------|
| 400 | 198 | 9.99 | 198–778 | 7.0 |
| 800 | 171 | 10.86 | 171–771 | 7.9 |
| 1600 | 131 | 12.88 | 131–771 | 9.9 |

(full 11-λ table in `results.txt`). **R(λ) is MONOTONE-increasing** toward the H⁻ opacity minimum
(steps +0.17″ to +0.54″). A fold exists at **every** λ — a limb-generic mapping inversion from the
τ=1 shell up to ~770 km — with width ≈ α(h_vis).

## The kill (reported, not softened)

**H2/H3 as written are KILLED as modelled.** The committed hypothesis was a two-to-one n(h) from the
T(h) turnover, producing a grow→vanish→reappear band at 4400–5000 K whose λ tracks the temp minimum.
The honest medium refuses it: at the temperature minimum μ_neutral/|μ_plasma| = **346:1** (1600 nm,
plasma maximal) — the only T-tracking term is buried; total n(h) is monotone in h; **no dn/dh sign
change exists at the temp minimum.** The computed fold tracks h_vis(λ) (opacity), not the 4400–5000 K
band. Controls: neutral-only 1.157″ vs plasma-only −1.6 mas at 500 km.

**Amplitude caveat (flagged in-run):** the ~10″ elevations depend sensitively on where τ_slant = 1
lands; helioseismic-vs-limb agreement at ~0.5″ argues the true refractive elevation is far smaller —
the transcription likely overestimates transparent-height densities by a factor of several. The
robust content is STRUCTURE (monotone R(λ); limb-generic fold; no temp-min tracking), not amplitude.

## §D seven questions (on the H2/H3 KILL)

1. **Why fail?** Magnitude: the T-tracking (plasma/n_e) refractivity is 2.5–3 orders below the
   neutral-density term at every relevant height and λ; sign: the neutral term is monotone in h.
2. **Recoverable?** Not via the measured medium. Only if matter closure itself tracks T (an SDT-native
   thermal-closure term ≫ standard refractivity), which is exactly OP01's OPEN matter-index problem —
   unbuilt, and any such term is bounded hard by the helioseismic-vs-limb 0.5″ consistency.
3. **What did the target fail to account for?** That n−1 of a gas tracks DENSITY, not temperature;
   T enters only through scale height and ionisation (weak channels).
4. **Errored premise?** "T(h) turnover ⇒ n(h) turnover." False for any medium whose refractivity is
   density-led. This was the priority claim's load-bearing premise.
5. **What freedom corrects it?** None available honestly at this amplitude. A λ-scan fold signature
   survives only in the OPACITY channel (h_vis(λ) structure near strong lines) — a different,
   weaker claim than the dispersive-lens artifact.
6. **Native or knob?** Any rescue term would be a knob today (no native T→closure map exists).
7. **Cascade?** Yes — runs to ground at **OP01-matter-index** (the α²-scale failure): the same root
   that left n(water) 25–99% short leaves no native thermal-closure term here. The dated priority
   claim [[project_solar_lens_artifact_claim]] inherits this verdict: its specific temp-min fold
   version is unsupported by the honest forward model; the falsifiable residue is the corrected
   discriminator below.

**Recovery grade: NO RECOVERY** (for the temp-min fold mechanism as claimed; premise error is
fundamental to density-led refractivity). The EXPERIMENT itself survives in corrected form.

## The corrected, still-falsifiable experiment (what remains on the table)

DKIST-class λ-scan, 400–1600 nm, ≤0.3 nm steps near candidate structure, AO, fixed seeing, with
terrestrial differential refraction modelled out (it is ~0.5″/100 nm at 45° zenith — larger than
most of the signal; P4 partial, DEFER full mimic modelling):
- **Predicted by this model:** R(λ) monotone-increasing toward 1.6 μm; a compressed/bright limb
  pile-up band at every λ; absolute elevation bounded by helioseismic consistency.
- **Kills the artifact claim:** smooth fold-free limb with R(λ) structure fully explained by
  opacity-height physics. **Kills this model too:** a genuine grow→vanish→reappear band at
  4400–5000 K (neither SDT-as-modelled nor the standard medium predicts it).
- **Mechanism class:** DEGENERATE — the computed refraction follows from the measured medium; the
  SDT-specific content (gravitational ϟ term) is achromatic and cannot make λ-folds.

---

**Prompt completion C (P1–P3 delivered, P4 partial) · Physics class DEGENERATE (mechanism) / KILLED (H2/H3 temp-min fold as claimed) · Recovery NO RECOVERY (for the claimed mechanism) · Cascade root: OP01-matter-index (no native T→closure term; shared with OP04-magnitude)**
