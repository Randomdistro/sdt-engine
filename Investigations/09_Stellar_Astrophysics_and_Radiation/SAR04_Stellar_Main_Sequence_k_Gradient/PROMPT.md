# SAR04 — Stellar main sequence and the surface k (specification rewritten 2026-10-12)

**Author:** J. C. Harvey, Melbourne. Rewritten at Harvey's direction: prompts carry new data, and errors inform the mechanism. The 2026-06-27 specification is kept below the line, superseded.

## 1. What is established (reset run 2026-10-10, `SAR04_RESET_ASSESSMENT_2026-10-10.md`)
- **Premise repaired.** The old k = c/√(2GM/R) used G and M (prohibited) and escape speed. The canon is **k = c/v_surface, with v_surface = √(gR)** (spectroscopic g, R from L and T_eff): no G, no M.
- **Data:** 123 FGK stars (DUNES table, `Experiments/E109_Solar_Spectral_Prism/data/dunes_koppa_table.txt`), k = 353–3213.
- **G1, monotonic sequence: EXCLUDED within FGK.**
  - ρ(k, L) = +0.42 and ρ(k, T_eff) = +0.34, both weak.
  - The **sign is opposite** to the old picture: hotter and brighter stars sit at lower k.
- **G2:** log L = −1.49 + 0.49 log k, scatter 0.44 dex. **G3:** the Sun lies inside the band (trivially; it sits mid-sample).
- **O–M span:** not met (the table is FGK only).

## 2. What the errors teach
- Across FGK dwarfs √(gR) varies about ×2 while L varies ×100, so **k is not a luminosity coordinate**.
- **k² = c²/(gR) = 1/z_surface**: k measures the star's **surface depth** (zk² = 1 with z = Ѻ/R = gR/c²).
- The native question is therefore not "does k order the main sequence" but **what the surface depth orders.** Candidates: evolutionary state (dwarf against subgiant, at fixed T_eff) and the surface-depth redshift itself.

## 3. Next round (register before computing)
- **H2:** at fixed T_eff, z_surface = gR/c² separates dwarfs from evolved stars, with no fitted boundary. Test it on a sample with independent evolutionary classification (asteroseismic or luminosity class), with that classification loaded only after the z-ranking is saved.
- **H3 (measured surface redshift):** for the stars with measured gravitational redshift (white dwarfs; the Sun; Gaia/APOGEE dwarfs if available with provenance), z_surface from gR/c² against the measured shift.
  - **Label:** convergent with the GR surface redshift at first order (Ѻ = GM/c²). This tests the mass-free inputs, not a fork.
- **O–M extension:** a mass-free k needs spectroscopic g and radii for O, B and M stars. A dataset with provenance is needed before registering.

## 4. Prohibitions
- No G or M.
- No escape-speed k.
- No sample trimming after the run.

---

## Superseded specification (2026-06-27, kept as written)

# SAR04: Stellar Main Sequence from k-Gradient — Data/Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — **Measurable gap (written 2026-10-05 in the audit correction pass, from this prompt's own content; the 2026-06-27 template left it unfilled):** Does the stellar main sequence follow from a monotone k-gradient (k = c / v_surface), with the luminosity law L(k) derived rather than fitted to the data?
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / SHARED-INPUT / KILLED / OPEN).

## DATA REQUIREMENTS

| Data | Source | Content |
|------|--------|---------|
| GAIA DR3 HR diagram | ESA GAIA | L, T_eff, R for ~10⁶ stars |
| Stellar orbital velocities | Binary surveys / spectroscopic | Surface/orbital v for k computation |
| Main sequence L-M relation | Eker et al. 2018 | L ∝ M^3.5 |
| Stellar radii compilation | Torres et al. 2010 | R vs M for MS stars |
| Solar k value | k_Sun = 686.3 | laws.hpp bridge |
| Solar R, L, T_eff | IAU 2015 nominal | Calibration point |

## INVESTIGATION PROMPT

**Target**: Map the main sequence to a k-gradient equilibrium sequence.

### SDT Prediction

Each star has a k-value: k = c / v_surface (where v_surface is the escape/orbital velocity at the stellar surface). Hot blue stars have low k (strong convergence — compact, massive), cool red stars have high k (weak convergence — diffuse, low-mass).

The main sequence should be a CONTINUOUS k-sequence. Compute k for each spectral class:
- O star (v_esc ~ 1000 km/s): k ≈ 300
- B star: k ≈ 400  
- Sun (G2V): k = 686.3
- M dwarf (v_esc ~ 200 km/s): k ≈ 1500

### Methodology

1. For each star with measured M, R, L: compute k = c / √(2GM/R)
2. Plot k vs L, k vs T_eff, k vs M
3. Is the main sequence a monotonic function of k?
4. Does the mass-luminosity relation L ∝ M^3.5 emerge from the k-gradient?
5. Does the pressure domain radius (r_domain = √(L / 4π F_CMB)) correlate with the star's Roche lobe in binary systems?

### Success Criteria
- [ ] k computed for ≥50 main sequence stars spanning O–M
- [ ] MS is a monotonic k-sequence 
- [ ] L vs k relationship identified (power law? exponential?)
- [ ] Solar k = 686.3 sits correctly on the sequence
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — SAR04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|SHARED-INPUT|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: law_I luminosity, SAR02 mode counting
- Phase thresholds (committed before run): [commit per phase in RUN_LOG]
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

*SAR04 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---

## Audit correction 2026-10-05 (gating)

**Finding:** T2 passes on "L ∝ k^−22.0, R² ≥ 0.90" with the slope "measured, not derived" (a power-law fit passes a fit statistic), T1 passes with 4 inversions in 15 steps, and the question is unfilled.

**Correction:** Gate the exponent against a derived value and score the ordering with a stated inversion limit.

**Status:** RULE RECORDED — corrected gate or definition applies to the next run; the earlier result is not re-scored and nothing was re-run.

*Standing constraints kept in every correction: no G, no GM, no mass as a primitive (mass is a baryon count N_b with its spatial resistance; a catalogue mass is converted at entry, N_b = M/m_p, and labelled a census input); no fields or wavefunctions as primitives; whole-range single pass; nothing re-scored retroactively.*
