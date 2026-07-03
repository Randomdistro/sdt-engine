# CR09+CR09: Hubble Tension and Dark Energy — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

---

## 1. The Questions

**CR09**: Can SDT explain the 8.4% Hubble tension (67.4 vs 73.04 km/s/Mpc) as a geometric consequence of sampling different parts of the convergence gradient?

**CR09**: Can SDT fit the SN Ia Hubble diagram (distance modulus vs redshift) WITHOUT dark energy (Λ), using only the pressure-gradient redshift model?

## 2. Methodology

### Phase A: The SDT distance-redshift relation

In SDT, redshift is NOT Doppler. It is the wavelength stretching of photons (lattice deformations) traversing the convergence pressure gradient:

$$1 + z = \frac{T_{\text{emitted}}}{T_{\text{CMB}}} \approx e^{\sigma_0 d}$$

where σ₀ is the strain rate (= H₀/c in conventional units) and d is the physical distance.

For a non-uniform gradient (SDT prediction), σ depends on position:

$$1 + z = \exp\left(\int_0^d \sigma(x) \, dx\right)$$

The distance modulus is then:

$$\mu = 5 \log_{10}(d / 10 \text{pc})$$

### Phase B: Fit the Pantheon+ data

1. Download the Pantheon+ catalog (1701 SN Ia with corrected peak magnitudes and redshifts)
2. Fit two models:
   a. **ΛCDM**: μ(z) with Ω_m, Ω_Λ as free parameters (2 params)
   b. **SDT pressure gradient**: μ(z) with σ(d) = σ₀ × f(d/d₀) where f is a gradient profile function (2 params: σ₀, d₀)
3. Compare χ² for both models
4. Compute the difference in AIC/BIC (information criteria)

### Phase C: Hubble tension dissolution

In SDT, the "tension" is resolved because:
- Local SN Ia (z < 0.1) sample the STEEP part of the local pressure gradient
- CMB (z = 1100) samples the AVERAGE gradient over the full path
- SDT predicts H₀(local) > H₀(CMB) — exactly what is observed

Compute:
1. The expected σ_local / σ_CMB ratio from the density distribution of the local universe
2. Whether the 8.4% tension corresponds to the expected gradient steepness near the Milky Way supercluster

### Phase D: BAO scale test

The BAO scale (147 Mpc) is an independent distance ruler. SDT interprets BAO as a lattice equilibrium length (cosmology.hpp bao namespace), not as a frozen sound wave.

Compare:
- SDT-predicted BAO angular scale at each measured redshift
- vs measured BAO angular scale from BOSS/eBOSS/DESI
- vs ΛCDM prediction

## 3. Success Criteria

- [ ] Pantheon+ data fitted with SDT model
- [ ] χ²(SDT) within 10% of χ²(ΛCDM) → SDT is competitive
- [ ] Hubble tension reproduced as a gradient steepness effect
- [ ] BAO scale at z = 0.15–2.33 reproduced within 3%
- [ ] Zero dark energy used in SDT model
- [ ] If SDT fails at high z: identify where and the magnitude of failure
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CR09
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: cosmology.hpp, z_spectral, CR10 cubic rung
- Phase thresholds (committed before run): 8.4%, 8.4%, 10%, 3%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*CR09 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
