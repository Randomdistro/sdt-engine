# CQ-45 VERDICT — SDT redshift laws vs the real Pantheon Hubble diagram

**Author:** J.C. Harvey, Melbourne. **Data:** binned Pantheon (Scolnic 2018, 40 bins, z=0.014–1.612), real.
**Tool:** `cq45_redshift_fit.cpp` → `cq45_results.txt`. **Run honestly; reported as it fell.**

## The ranking (lower AIC = better)

| model | k | χ² | χ²/dof | ΔAIC vs best | best param |
|---|---|---|---|---|---|
| **ΛCDM** | 2 | 49.7 | **1.31** | **0 (best)** | **Ω_m = 0.284** |
| **SDT n-free** | 2 | 81.0 | 2.13 | +31.3 | **n = 0.656** |
| Milne (empty) | 1 | 169 | 4.34 | +117 | — |
| SDT-exp (n→1) | 1 | 325 | 8.33 | +273 | — |
| Linear (cz/H₀) | 1 | 1060 | 27.2 | +1009 | — |
| EdS (Ω_m=1) | 1 | 1469 | 37.7 | +1417 | — |
| **SDT n=4 (doc §7.2)** | 1 | **16518** | **424** | **+16466** | — |

## The three findings

**1. The doc's `n=4` distance law is decisively FALSIFIED.** `d(z)=(c/H₀)[1−(1+z)⁻³]/3` (the "T⁴ pressure
scaling" of `Hubble/INVESTIGATION_Hubble_Tension.md` §4/§7.2) misses by **+1.7 mag at z=1.6** — χ²/dof = **424**,
worse than *every* other model including the empty universe and even a naive linear law. The saturation
(`d → c/3H₀` as z→∞) makes high-z supernovae far too bright. **This claim must be removed/corrected in the
Hubble investigation.** It is the clean kill of this CQ.

**2. The data's preferred SDT exponent is n ≈ 0.66, NOT 4.** With one free power the SDT propagation law lands
at **n = 0.656** (χ²/dof = 2.13), the **second-best model overall** — it beats Milne, EdS, the linear law, and
the n→1 "amplitude-squeeze" form decisively. At n≈0.66 it **does generate an acceleration-like up-bend without
Λ**: Δμ(obs−Milne) runs +0.05→+0.02 over z=0.4–1.0, and the n=0.66 law tracks it (+0.03→+0.04) where ΛCDM
gives +0.04→+0.01. So a *one-parameter* SDT law reproduces the qualitative "acceleration" the 1998 discovery
attributed to dark energy. The framework is **not** refuted; the specific exponent in the doc was just wrong.

**3. But SDT does NOT beat ΛCDM here.** ΛCDM (Ω_m=0.284, the canonical value, recovered with zero input)
remains best by **ΔAIC = 31** — formally "strong" preference, on a fair 1-shape-parameter-vs-1 comparison. The
n=0.66 law's residuals drift (−0.07 mag at z=0.02, +0.07 at z=0.1, −0.27 at the noisy z=1.6 bin): it has the
right *gross* shape but not ΛCDM's detailed curvature. **"Resolved on the data" is NOT achieved.**

## Classification
- **The doc's n=4 law: Class F (FALSIFIED).**
- **The general SDT one-parameter propagation law: Class C-/PARTIAL** — competitive (2nd of 7), makes the
  acceleration bend without Λ, beats all decelerating nulls; but loses to ΛCDM by ΔAIC=31 and `n` is now a
  *fitted* parameter (n≈0.66), not the derived n=4.

## Honest caveats (what this does and does not establish)
- Tests the **propagation** half only — a *homogeneous* d(z). It does **not** test the **emission** half (the
  per-source pressure-regime λ shift = the host-mass/zk²=1 term) nor the **κ(line-of-sight)** inhomogeneity the
  doc uses for the *local-vs-global* tension. So this neither confirms nor refutes the emission/propagation
  *split* itself, nor the Hubble-**tension** resolution — it refutes one specific *distance law* (n=4) and
  measures the best single-power alternative (n≈0.66).
- **Binned** data, no covariance matrix, tiny per-bin dmb (~0.02–0.07 mag) → all absolute χ²/dof > 1; the
  ranking and Δχ² are robust, the absolute χ² is not a classical goodness-of-fit. A full-sample (1701-SN +
  covariance) fit is the next rigor step.
- The n≈0.66 value has no derivation yet — it is *measured from the data*, the opposite of the doc's
  (failed) *derived* n=4. Deriving n from the pressure/closure evolution is the open theory task.

## What to do with this
1. **Correct the Hubble doc:** strike the n=4 "T⁴ → d(z)" claim; it is falsified at χ²/dof=424.
2. **Re-derive the exponent:** the data wants n≈0.66. Does the SDT closure/pressure evolution predict ~0.66
   (not 4)? If yes, SDT has a *derived* one-parameter law competitive with ΛCDM. If no, n is a fit and the
   honest headline is "competitive phenomenology, not a derivation."
3. **Test the emission half separately:** the SN-Ia host-mass step is the place the emission(atom) term should
   show up; that is the part this CQ did not touch and where the split's real signature lives.

**Bottom line:** the supernovae kill the doc's n=4 outright, leave the SDT framework standing as a competitive
one-parameter phenomenology (n≈0.66, acceleration without Λ), and do **not** let SDT overtake ΛCDM on this
dataset. If it fails, it fails — and here the *specific* law failed while the *framework* survived, demoted
from "derived" to "fitted."
