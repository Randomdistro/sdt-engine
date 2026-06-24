# CQ-45 — Redshift is two things: emission (atom) + propagation (spation)

**Author:** J.C. Harvey, Melbourne. **Status:** EXECUTED (data fit complete). **Class:** see VERDICT.

## Thesis
Cosmological redshift is **not one quantity**. It is **emission** (the wavelength an atom *emits*, set by its
local spation-pressure regime — high pressure → longer λ; the Depth-Closure result `z=ϟ/r` at the emission
point, verified on the Sun to 0.03 %) **plus propagation** (how the spation lattice works the wavelength along
the path). Standard cosmology assumes the emitted λ is the lab rest value and assigns the *entire* shift to
propagation, which it calls "expansion velocity." Conflating the two is the Hubble tension (see
`Hubble/INVESTIGATION_Hubble_Tension.md`).

## The falsifiable question (this CQ)
Does an SDT **propagation** distance–redshift law fit the SN Ia Hubble diagram **without dark energy** — and in
particular, does the `n=4` (T⁴ pressure) law of the Hubble investigation §7.2 hold? *If it fails, it fails.*

## Data (real, citable)
`data/pantheon_binned_DS17f.txt` — the **binned Pantheon Hubble diagram**, 40 bins, z = 0.014–1.612 (Scolnic et
al. 2018, arXiv:1710.00845; fetched verbatim from `github.com/dscolnic/Pantheon`). Columns used: `zcmb`, `mb`
(SALT2-standardised, bias-corrected peak B mag), `dmb`. (The prior `Hubble/tools/zk2_pantheon.cpp` used *made-up*
high-z points `SN_z*`; this CQ replaces them with the real release.)

## Method (`cq45_redshift_fit.cpp`)
Fit each model's dimensionless luminosity-distance **shape** `D_L(z)` with one nuisance offset
(`a = M − 5log₁₀H₀ + const`, linear in μ → solved analytically by weighted least squares). The shape is what
"needs dark energy", so this is the real test. Models:

| model | `D_L(z)` shape | free params |
|---|---|---|
| ΛCDM(Ω_m) | `(1+z)∫₀ᶻdz'/√(Ω_m(1+z')³+1−Ω_m)` | offset, Ω_m |
| EdS (Ω_m=1) | `(1+z)·2(1−1/√(1+z))` | offset |
| Milne (empty) | `((1+z)²−1)/2` | offset |
| Linear | `z(1+z)` | offset |
| SDT-exp (n→1, amplitude squeeze) | `(1+z)ln(1+z)` | offset |
| SDT n=4 (doc §7.2) | `(1+z)[1−(1+z)⁻³]/3` | offset |
| SDT n-free | `(1+z)[1−(1+z)^−(n−1)]/(n−1)` | offset, n |

Scored by χ², χ²/dof, AIC=χ²+2k, BIC=χ²+k·lnN, ΔAIC vs best. Residual table (where each model breaks) and the
"acceleration signature" Δμ = μ_obs − μ_Milne (does any SDT law make the z≈0.4 up-bend that ΛCDM needs Λ for?).

## Honest success criteria (declared before reading the result)
- **PASS (SDT wins):** a one-parameter SDT law with ΔAIC ≤ 0 vs ΛCDM, reproducing the acceleration bend.
- **QUALIFIED:** a one-parameter SDT law competitive (ΔAIC ≲ 10) and making the bend — "as good as ΛCDM, fewer assumptions."
- **PARTIAL:** SDT power-law beats the decelerating nulls (EdS/linear) and makes a bend, but ΛCDM still wins.
- **FAIL:** SDT laws can't beat the nulls / can't make the bend / the doc's n=4 is ruled out.

## Outputs
`cq45_redshift_fit.cpp`, `cq45_results.txt`, `data/pantheon_binned_DS17f.txt`, `CQ45_VERDICT.md`.

## Scope note (what this does and does NOT test)
This tests the **propagation** half — a *homogeneous* `d(z)`. It does **not** test (a) the **emission** half
(per-source pressure-regime λ shift — the host-mass step / zk²=1 term, a separate per-SN correction), nor
(b) the **inhomogeneous** κ(line-of-sight) that the Hubble doc uses to explain the *local-vs-global* tension.
A clean propagation-law failure here does not by itself refute the emission/propagation split or the
tension resolution — but it does test the doc's specific `n=4` distance law head-on.
