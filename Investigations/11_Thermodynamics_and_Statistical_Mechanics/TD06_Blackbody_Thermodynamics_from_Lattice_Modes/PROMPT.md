# TD06 — Blackbody Thermodynamics from Lattice Modes

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Can Planck's law, Stefan–Boltzmann, and Wien be obtained from **native
   lattice mode counting** in which (a) the `hν` granularity is the relay tick `ε` (Law I), not a
   postulated oscillator, and (b) the occupation factor is TD02's *natively-derived* `exp(−ε/k_BT)` —
   or do they only reproduce because the Bose denominator `1/(e^{hν/k_BT}−1)` is imported, which would
   make the famous spectrum a CONVERGENCE re-narration rather than a derivation?
2. **Why does it matter?** — This is the suite's most quotable result, so it is the one most at risk of
   an **unfalsifiable victory lap**. SAR02 (Stellar suite) already reproduced these numbers; TD06 must
   NOT grade itself "A because SAR02 passed". The new content TD06 owns is the *consolidation under one
   mode count* and the honest provenance of the occupation factor it inherits from TD02.
3. **How will we find out?** — Four gated phases. Each independently recomputes the curve/constant from
   the discrete mode set so the test **can fail on its own numbers** — SAR02 is a cross-check, not the
   pass criterion.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers and real failure modes,
   including the inherited anti-tautology firewall (F4) on the occupation factor.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

## Question

Planck's law, Stefan–Boltzmann, and Wien's displacement law are the pillars of blackbody
thermodynamics, classically obtained by *postulating* quantised oscillators (`E=nhν`). The gap: derive
all three from **lattice mode counting** — because the relay lattice is *already discrete at ℓ_P*, the
quantisation is structural, not an extra axiom. TD06 **consolidates** the single prior result
**SAR02** (Stellar Astrophysics suite) into one thermodynamic statement — it does not treat SAR02's
pass as its own.

## Dependency-provenance note

The suite records **`k_B` as a thermodynamic unit bridge**. TD06 also uses `h` and `c`
with their previously established roles: `c=ℓ_P/t_P` is the relay tick speed (Law I), and
`h` (equivalently `ε`, the relay energy quantum) is the throughput-per-tick granularity — it is **not** a
new fitted input, and the `hν=ε` identity must be *stated as native*, not assumed. If `h` enters as an
independent quantised-oscillator constant rather than as `ε`, that is the `E=nhν` postulate creeping back
in, and the result drops to F. Document `c` and `h` as derived/bridged, never as free parameters.

## SDT mechanism & hypotheses

A cavity at temperature `T` is a region of disordered convergence throughput. The emission spectrum is
the throughput carried by the lattice's relay modes; mode counting is literal because the lattice has a
finite mode density set by `ℓ_P` and the cavity size. There is **no continuum** to regularise and **no
oscillator to quantise** — the `hν` granularity is the relay tick itself (`ε` per mode, Law I).

- **H1 (Planck from discrete modes):** counting relay modes per frequency band with TD02's occupation
  `exp(−ε/k_BT)` (inherited — class follows TD02's firewall) gives
  `u(ν,T) = (8πν²/c³) · hν/(e^{hν/k_BT}−1)` — the Bose-like denominator emerging from indistinguishable
  relay quanta sharing throughput. **The geometric-series sum that turns `exp(−ε/k_BT)` into the Bose
  denominator must be shown native (multiple quanta per mode), not lifted from QM.**
- **H2 (Stefan–Boltzmann):** integrating `u(ν,T)` over the discrete mode set yields `j = σT⁴` with `σ`
  expressed in lattice constants; the `T⁴` is the 3D-mode + linear-dispersion count, derived.
- **H3 (Wien):** the spectral peak `λ_max T = b` is the extremum of the mode-weighted throughput; `b`
  follows from the same counting with no new input.

## Strategy

1. **Mode counting → Planck.** *Goal:* reproduce `u(ν,T)`. *Method:* enumerate relay modes per band,
   weight by TD02's occupation, sum the per-mode geometric series natively. *Success:* Planck curve to
   <0.1% **from TD06's own mode sum** (not by citing SAR02); Rayleigh–Jeans (low ν) and Wien-tail
   (high ν) limits both recovered; no UV catastrophe (lattice cutoff at `ℓ_P`).
2. **Stefan–Boltzmann.** *Goal:* `σ` from lattice constants. *Method:* integrate the mode-summed
   spectrum. *Success:* `σ = 2π⁵k_B⁴/(15h³c²)` reproduced to <0.1%; `T⁴` exponent exact; the `π⁴/15`
   from the `∫x³/(eˣ−1)dx` mode integral shown, not inserted.
3. **Wien.** *Goal:* `b`. *Method:* extremise the spectral density. *Success:* `b = 2.898×10⁻³ m·K`
   to <0.1%; the transcendental root `4.965114…` of `5(1−e^{−x})=x` derived from the extremum, not
   inserted.
4. **Consolidation memo.** *Goal:* one statement subsuming the three laws. *Method:* show Planck, SB,
   and Wien are the *same* mode count read three ways, and **independently reproduce SAR02's numerics as
   an external cross-check** (agree to <0.1% with SAR02's published values). *Success:* a single
   derivation chain; SAR02 agreement reported as a consistency check, explicitly **not** as the pass.

## Success criteria

- **PASS (Class A):** Planck, Stefan–Boltzmann, Wien each recomputed to <0.1% **from TD06's own lattice
  mode sum**, with the occupation factor inherited from a NATIVE TD02; `k_B` dependency-traced and `c`, `h(=ε)`
  documented as earned bridges; no quantised-oscillator postulate, no continuum regularisation, no Bose
  denominator lifted from QM.
- **QUALIFIED (Class C):** all three numerically reproduced, but the occupation factor rests on a TD02
  graded IMPORTED, **or** the Bose-denominator geometric sum is asserted rather than shown native →
  CONVERGENCE. *(Honest expected landing until TD02 clears its firewall.)*
- **PENDING (Class D):** spectrum right but `σ`/`b` constants need a borrowed mode-density prefactor.
- **FAIL (Class F):** the spectrum only follows from `E=nhν` as an independent postulate (i.e. `h`
  enters as a free oscillator constant, not as the relay quantum `ε`).

## Falsification tests (each has a real failure mode + numeric trigger)

| # | Test | SDT prediction | If it fails (numeric trigger) |
|---|------|----------------|-------------------------------|
| T1 | Discrete lattice → Planck | `u(ν,T)` to <0.1% **from TD06's own mode sum**; no UV catastrophe | if the mode sum diverges at high ν (no `ℓ_P` cutoff) or misses the curve `>0.1%`, quantisation must be a separate axiom → **F** |
| T2 | Mode integral → `σT⁴` | `σ=2π⁵k_B⁴/(15h³c²)` to <0.1%; fitted exponent `= 4.00 ±0.02` | if the best-fit `T`-exponent ≠ 4, the `T⁴` is not from the 3D mode count |
| T3 | Extremum → Wien | `b=2.898e-3 m·K` to <0.1%; root `4.9651…` derived | if `b` only matches by inserting the `4.965` constant, the displacement law is not native |
| T4 | **Anti-tautology firewall (inherited)** | occupation `exp(−ε/k_BT)` and the Bose sum are native (TD02 + geometric series), not imported | if the denominator is lifted from QM **or** TD02's factor is IMPORTED → grade **capped at C** (CONVERGENCE); SAR02 agreement does **not** lift it |

## Dependencies

**Upstream:** **SAR02** (Stellar Astrophysics suite — lattice mode counting → Planck/SB/Wien; TD06
*independently recomputes* and uses SAR02 only as an external cross-check), [[TD02]] (the
`exp(−ε/k_BT)` occupation — **inherited, class follows TD02's firewall**), Law I (`ε` per mode, the
`hν=ε` bridge). **Downstream:** stellar thermodynamics (suite 09), CMB / cyclic-cosmology spectrum
([[project_hubble_tension_resolution]], [[project_sdt_cyclic_cosmology]]), TD07 (radiative bit-erasure
heat bath). **Related:** [[TD01]] (entropy of radiation `S = 4/3 · aT³V`), [[TD03]] (radiation pressure
`P=u/3` is the same isotropy `⟨cos²θ⟩=1/3`), CR07 (redshift as octaves — same lattice-mode ruler).
---

## Questions This Opens *(generative — log new ones in `TD06_VERDICT.md`)*

1. **Does the `ℓ_P` cutoff shift the high-ν tail measurably?** The lattice removes the UV catastrophe by
   a real mode cutoff, not by `e^{−hν/kT}` alone. Is there a tiny native deviation from Planck near the
   spation scale — a Wien-tail correction no continuum theory predicts?
2. **Is the CMB blackbody a boundary-reconnection aftermath (FLM09), and does TD06's mode count predict
   its FIRAS-level deviations?** If the CMB is thermalised relay modes, the <50 ppm FIRAS residual is a
   target TD06 could bound.
3. **Is radiation pressure `P=u/3` the same `1/3` as TD03 and FD05?** The photon-gas EoS should fall out
   of the *same* `⟨cos²θ⟩=1/3` isotropy — can TD06 derive `P=u/3` from its own mode integral and tie the
   three results under one geometric factor?
4. **Why exactly `2` polarizations per mode with no spin postulate?** The factor-2 in `8πν²/c³` is the
   two transverse relay branches (CONDENSA `c_T`). Does the lattice forbid a longitudinal radiative mode
   (cf. FD05's no-longitudinal-vacuum-sound), and is that the *same* statement?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — TD06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (no fitted prefactor; σ and b must come from the mode integral)
- dependency-traced input: k_B only (README). c and h(=ε) are EARNED bridges (Law I), not free params —
    document them as such; if h enters as a free oscillator constant the result is F.
- Engine namespaces actually used: measured::k_B, law_I (ε per mode, hν=ε bridge),
    TD02 occupation exp(−ε/k_BT) (INHERITED — class follows TD02); SAR02 = external cross-check only
- Phase thresholds (committed before run):
    P1 Planck <0.1% from TD06's own mode sum, no UV divergence · P2 σ=2π⁵k_B⁴/(15h³c²) <0.1%, fitted exponent 4.00±0.02
    P3 b=2.898e-3 m·K <0.1%, root 4.9651… derived · P4 SAR02 agreement <0.1% (cross-check, NOT the pass)
- Forbidden retroactive changes: grade A by citing SAR02's pass; lift the Bose denominator from QM;
    let h in as a free oscillator constant; widen tolerances; plug σ/b; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 mode sum diverges at high ν | confirm the `ℓ_P` mode cutoff is in the count, not just the exponential | **F** — UV catastrophe ⇒ quantisation is a separate axiom | regularise with a continuum trick |
| P2 fitted `T`-exponent ≠ 4.00±0.02 | recheck the 3D mode-density × linear dispersion | **OPEN** the `T⁴` origin | force exponent to 4 |
| P3 `b` only matches by inserting `4.965` | re-extremise the spectral density natively | **OPEN** Wien | hard-code the root |
| occupation factor rests on an IMPORTED TD02, or Bose sum lifted from QM | grade TD06 **C** (CONVERGENCE) honestly | — | claim A; lean on SAR02 to lift it |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (TD02 occupation not run) | **DEFER** the occupation-weighted phases; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mode bins, integration grid, root bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes for the mode count (real-space relay enumeration vs k-space mode density).

### Disallowed adjustments

- Grading A by citing SAR02's prior pass (victory lap) · lifting the Bose denominator from QM · admitting
  `h` as a free oscillator constant rather than `ε` · post-hoc tolerance widening · coefficient plugs on
  `σ`/`b` · `atomic::`/GM/G in the native chain.

---

*TD06 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
