# CQ-45 — Redshift is two things: emission (atom) + propagation (spation)

> **Author:** J. C. Harvey, Melbourne. **Status:** EXECUTED-honest (header corrected 2026-07-03; was "SPEC" from the bulk template upgrade, contradicting the body's EXECUTED status — CR06 verified by re-run, HUNTER scour 2026-07-02).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — **Measurable gap (written 2026-10-05 in the audit correction pass, from this prompt's own content; the 2026-06-27 template left it unfilled):** How is the measured redshift divided between an emission depth z_emit = koppa/r and a propagation term, and which single-power propagation law reproduces the raw Pantheon distance moduli with the exponent derived rather than fitted?
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. ~~**How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT / KILLED / OPEN).~~ **[WITHDRAWN 2026-10-09 at Harvey's direction: the classification requirement is a gate. Done = the chain is stated, the instrument is validated, the data are fitted once over the whole range, and the results are reported as estimates with uncertainties.]**

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

## ~~Honest success criteria (declared before reading the result)~~ **[WITHDRAWN 2026-10-09 at Harvey's direction — pass/fail classes tied to ΛCDM's ΔAIC are gates; text kept visible as withdrawn]**
- ~~**PASS (SDT wins):** a one-parameter SDT law with ΔAIC ≤ 0 vs ΛCDM, reproducing the acceleration bend.~~
- ~~**QUALIFIED:** a one-parameter SDT law competitive (ΔAIC ≲ 10) and making the bend — "as good as ΛCDM, fewer assumptions."~~
- ~~**PARTIAL:** SDT power-law beats the decelerating nulls (EdS/linear) and makes a bend, but ΛCDM still wins.~~
- ~~**FAIL:** SDT laws can't beat the nulls / can't make the bend / the doc's n=4 is ruled out.~~

## Outputs
`cq45_redshift_fit.cpp`, `cq45_results.txt`, `data/pantheon_binned_DS17f.txt`, `CQ45_VERDICT.md`.

## Scope note (what this does and does NOT test)
This tests the **propagation** half — a *homogeneous* `d(z)`. It does **not** test (a) the **emission** half
(per-source pressure-regime λ shift — the host-mass step / zk²=1 term, a separate per-SN correction), nor
(b) the **inhomogeneous** κ(line-of-sight) that the Hubble doc uses to explain the *local-vs-global* tension.
A clean propagation-law failure here does not by itself refute the emission/propagation split or the
tension resolution — but it does test the doc's specific `n=4` distance law head-on.
---

## ⑩ Adaptive Execution Protocol — **[WITHDRAWN 2026-10-09 at Harvey's direction: the pre-run commitment block with "phase thresholds 0.03 %", the pivot table, and the allowed/disallowed adjustment lists are gates; text kept visible as withdrawn. Instrument validation on known answers, which is a protocol requirement and not a gate on the physics, is kept — see the reframe at the end of this file.]**

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CR06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: cosmology.hpp, z_spectral, CR10 cubic rung
- Phase thresholds (committed before run): 0.03 %
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| A rival lands on the same number | adjudicate by **origin** (gateway procedural §3.8): SDT-origin route ⇒ **CONVERGENCE**; a *named* contaminating input ⇒ **SHARED-INPUT**; state discrimination separately | — | downgrade a convergent result because a rival formula agrees; claim discrimination the numbers do not show *(row corrected 2026-10-03 — the stamped alignment row was excluded 2026-07-26)* |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*CR06 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

## Audit correction 2026-10-05 (opening premise)

**Finding:** The question is unfilled by the bulk template, and the propagation power n ≈ 0.66 is fitted on the data it is scored on (no derivation; CALIBRATED(1)), against a stated 0.03% phase threshold.

**Correction:** State the gap (derive n from the closure evolution) and register a held-out data split for the fit.

**Status:** OWED — needs a new run, derivation or data; the corrected requirement is recorded here.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*

---

## Reframe 2026-10-09 (Harvey direction) — supersedes the gates and the model restriction above

**Withdrawn, in place and visible:** the PASS / QUALIFIED / PARTIAL / FAIL classes and their ΔAIC and bend thresholds; the dual-verdict classification; the §⑩ pre-run commitment block, pivot table and adjustment lists; the 2026-10-05 requirements to "derive n" and to register a held-out split as a gate. **Also withdrawn as restrictions (not gates, but they fixed the answer's form):** that the propagation law must be a single power dz/dr = κ(1+z)ⁿ; that D_L = (1+z)·r is an assumed convention; ΛCDM's ΔAIC as the yardstick. Nothing replaces them with another threshold. Results are estimates with uncertainties and functions with bands. Instrument validation on known answers stays (it checks the tool, not the physics). Run 1 of this reopen (`cr06_reset_1.cpp`, `CR06_RESET_ASSESSMENT_2026-10-09.md`) used the withdrawn gates and the single-power family; its computed numbers stand as computed, its classifications are superseded.

**The chain (the frame).**
1. *Redshift is an endpoint ratio of local lattice states* (CR07 octave counting, zk² = 1 closure, Depth-Closure z = ϟ/r at emission; `cosmology.hpp` guard: nothing happens in transit). There is no differential equation along the path.
2. *Photon energy and event rate scale with the same ruler ratio* (common-mode shrink of light and of every internal ruler and clock; CONDENSA §2). Energy per photon and arrival rate each fall by 1/(1+z), so flux = L/[4π r²(1+z)²] and **D_L = r(1+z)¹**. The prefactor power is a consequence of the premise, not a convention; the data are asked whether p = 1 holds (sensitivity to p reported, nothing selected).
3. *Geometry:* Law III inverse-square in a static lattice: r is a physical distance, no comoving factor.
4. *The unknown is the profile of the lattice state along the line of sight:* 1+z(r), the ratio of the ruler at distance r to the ruler here (variable closure, GOM05). With step 2 the data determine it: r(z) = D_L(z)/(1+z), up to the overall scale c/H_eff carried by the offset. It is represented, with no assumed shape, by the octave-rate function n(x), x = ln(1+z): r̃(x) = ∫₀ˣ e^{(1−n(x′))x′} dx′, n piecewise-linear on K equally spaced knots over the data range (K = 1 reproduces the single power). Every K is reported; none is selected by a threshold.
5. *Emission half:* the luminosity of the source in its own lattice state is degenerate with step 4 in the distance modulus. It is not separated; it is reported as the magnitude residual that a given profile would have to leave to the emission term, per bin, in magnitudes, and as a linear-in-x luminosity drift fitted jointly with a stated profile.
6. *Observer:* one offset a = M − 5log₁₀H_eff + const (analytic).

**Data.** `data/pantheon_binned_DS17f.txt` (40 bins) with the full covariance C = diag(dmb²) + C_sys (`Datasets/cosmology/Pantheon_DS17f_binned_sys_covariance.txt`, manifest row 2026-10-09); and `Datasets/cosmology/PantheonPlusSH0ES.dat` (non-calibrators, zHD ≥ 0.01, diagonal errors only: its covariance is not in the repository) as a second compilation. Both are fitted once over their whole range.

**Reported, not gated:** χ², parameter count, the secant exponent n(z) = ln(dz/dr)/ln(1+z) and the local slope s(z) = d ln(dz/dr)/d ln(1+z) = n + x n′ (two different quantities for a varying exponent; both reported, with ±1σ bands, 2026-10-09 correction), the implied emission-term residuals in magnitudes, the fitted p and drift δ with their correlations with the profile, the same quantities for the comparators (Milne, EdS, de Sitter, flat ΛCDM and its n_eff).
