# OP03 — Diffraction and Interference from Relay-Huygens Summation

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether double-slit fringes, the grating equation, single-slit `sinc²`
   and the Airy disk *follow* from a discrete relay-Huygens sum (each illuminated spation re-emitting
   its received phase-impulse one tick later, the screen pattern being the relay-time-phased sum) with
   **no continuous wavefield and no photon-particle** — or whether SDT must quietly re-import the
   Huygens–Fresnel integral and call the relay sum its derivation.
2. **Why does it matter?** — Interference is the textbook "proof" of wave-particle duality. If the
   pattern is a *counting statement about relay paths*, single-emission "self-interference" needs no
   collapse and no ψ (ties QM01), and OP06's laser coherence inherits a phased-sum machinery. If the
   relay sum cannot produce fringes without a wavefield, the no-ψ optics programme stalls here.
3. **How will we find out?** — Four gated phases: the discrete tick-rule kernel must reproduce the
   Huygens–Fresnel integral (and its obliquity factor) **in the continuum limit before** any standard
   wave-optics envelope is written; two-slit/grating and single-slit/Airy then fall out as geometry;
   the granularity deviation is the SDT≠wave-optics stretch. Importing the continuum envelope to
   *get* the pattern caps the grade at C (anti-tautology gate).
4. **What would prove us wrong?** — §Falsification, numeric: grating orders off `d sinθ=mλ` by >0.1%;
   single-slit first null off `sinθ=λ/a` by >0.1%; Airy radius off `1.22λ/D` by >0.1%; or fringes
   that only appear once a wavefield/ψ is inserted.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

### Anti-tautology firewall

The load-bearing claim is that **Huygens' principle is *derived* as the discrete relay re-emission
rule**, not assumed as a wave postulate. The obliquity (inclination) factor must *emerge* from the
relay geometry, not be inserted by hand — that is the test that can fail. The continuum
Huygens–Fresnel integral is the CONVERGENCE target: reproducing it in the `ℓ_P→0` limit is the
payoff; *using* it as the kernel to produce fringes is the identity and caps the grade at **C** (row
tagged IMPORTED). Light here is a relayed phase-impulse — never a ψ amplitude, never a single-photon
probability wave, never second quantisation. The wavelength is the relay ruler `λ = N·ℓ_P` (CR07).

## Question

Diffraction and interference are usually read as evidence for a continuous wavefield or for
single-photon "self-interference." SDT has neither: light is a relay emission, and the lattice is
discrete at ℓ_P. **Can double-slit fringes, the grating equation `d sinθ = mλ`, the single-slit
`sinc²` pattern, and the Airy disk all be reproduced by relay-Huygens summation — each illuminated
interface spation re-emitting its received phase-impulse on the next tick, the screen pattern being
the relay-time-phased sum of those re-emissions — with no wavefunction and no photon-particle?**
This makes the double slit a counting statement about relay paths, the same wake-summation
machinery as [[QM01]].

## SDT mechanism & hypotheses

Each spation that receives the emission re-emits it one tick later (a secondary relay source); the
arrival phase at a screen point is set by the *relay-time* along the path (`∫ds/c_local`), so paths
of different length add with a phase difference. This is Huygens' principle **derived** as the
discrete relay rule, not assumed as a wave postulate.

- **H1 (Huygens = relay re-emission):** the field at a screen point is `Σ_j exp(i·2π·L_j/λ)` over
  illuminated spations `j`, with `L_j` the relay path length; constructive when path difference = mλ.
- **H2 (grating/two-slit):** two relay apertures give `d sinθ = mλ`; N apertures sharpen to grating
  resolving power `R = mN` — a pure counting/geometry result, zero fit.
- **H3 (single-slit + Airy):** a finite aperture of re-emitting spations integrates to `sinc²` (slit)
  and the Airy `[2J₁(x)/x]²` (circular); `λ` is the emission's relay wavelength `λ = N·ℓ_P` (CR07).
- **H4 (no self-interference paradox):** because the emission is a real relayed disturbance, "one
  photon" interference is just one emission sampling many relay paths — no collapse, ties [[QM01]].

## Strategy

**Phase 1 — Relay-Huygens kernel.** *Goal:* derive the secondary-source sum from the tick rule.
*Method:* discrete spation re-emission with relay-time phase. *Success:* recovers the Huygens–Fresnel
integral in the continuum limit; obliquity factor emerges, not inserted.

**Phase 2 — Two-slit & grating.** *Goal:* `d sinθ=mλ`. *Method:* sum two/N apertures. *Success:*
fringe spacing and grating angles exact; `R=mN` recovered.

**Phase 3 — Single-slit & Airy.** *Goal:* `sinc²` and Airy disk. *Method:* integrate a finite
aperture. *Success:* first-null positions (`sinθ=λ/a`; `1.22λ/D`) to <0.1%.

**Phase 4 — Granularity correction (stretch).** *Goal:* an ℓ_P-scale deviation. *Method:* keep the
discrete sum un-continuum-limited. *Success:* predicted (tiny) departure from `sinc²` at extreme
angles — a falsifiable SDT≠wave-optics signature, flagged with its size.

## Success criteria

- **PASS (A):** two-slit, grating, single-slit, Airy all from one relay-Huygens sum, zero fits.
- **QUALIFIED (C):** the above with the continuum (wave-optics) limit borrowed for the envelope (expected).
- **PENDING (D):** two-slit/grating recovered, single-slit/Airy only schematic.
- **FAIL (F):** relay summation cannot produce fringes without importing a wavefield.

## ⑧ Falsification tests (each states the numeric outcome that kills it)

| ID | Test | SDT prediction | The number that kills it |
|----|------|----------------|--------------------------|
| F1 | Continuum-limit kernel | the discrete relay sum → Huygens–Fresnel integral as `ℓ_P→0`; obliquity factor emerges | the relay sum does not converge to the H–F integral, or the obliquity factor must be inserted by hand ⇒ Huygens is not the relay rule |
| F2 | Grating equation | orders at `d sinθ=mλ`; resolving power `R=mN` | any order off `d sinθ=mλ` by >0.1%, or `R≠mN` ⇒ relay sum ≠ Huygens summation |
| F3 | Single-slit + Airy nulls | first null `sinθ=λ/a`; Airy radius `1.22λ/D` | first null off `λ/a` by >0.1% or Airy off `1.22λ/D` by >0.1% ⇒ finite aperture not integrable as relay sources |
| F4 | Single-emission build-up | the fringe pattern accumulates from independent one-emission events with **no collapse** | if reproducing the pattern requires a ψ amplitude / collapse / single-photon probability wave ⇒ no-ψ optics fails here |
| F5 | Anti-tautology | the pattern is produced by the relay sum, not by the imported H–F envelope | if fringes appear only when the continuum wave-optics envelope is the kernel ⇒ Class capped at **C**, row IMPORTED |
| F6 | Granularity deviation (stretch) | a tiny computed departure from `sinc²` at extreme angles, size ∼(ℓ_P/λ) | the predicted deviation is identically zero or exceeds current diffraction bounds ⇒ no SDT≠wave-optics signature (or it is already excluded) |

## Dependencies

**Upstream (required):** OP01 (relay speed, `c_local`, the ruler `λ=N·ℓ_P`). **Downstream
(unblocked):** OP06 (coherence/laser linewidth uses the phased sum), holography, interferometry.
**Lateral:** QM01 (deterministic double slit / wake construction — the no-collapse partner), OP02
(reflected branches that then interfere via this sum). **Framework:** CR07 (the relay ruler,
[[project_cq46_redshift_octaves]]), `Theory/00_Ruleset.md`, `Theory/05` audit spine.

## Questions This Opens *(generative — log new ones in `OP03_VERDICT.md`)*

1. **Is the obliquity factor a pure relay-geometry consequence?** Kirchhoff had to bolt
   `(1+cosχ)/2` onto Huygens by hand. If the tick rule *gives* it, is that the cleanest derivation of
   the inclination factor in physics — and does it forbid the backward secondary wave automatically?
2. **Does single-emission build-up match QM01's residence statistics exactly?** If OP03's path-count
   and QM01's wake-residence density are the same histogram, is the Born rule (QM04) already implicit
   in the relay sum?
3. **Is there a measurable ℓ_P-scale floor on fringe contrast?** If the discrete sum departs from
   `sinc²` at size ∼(ℓ_P/λ), what aperture/wavelength/angle makes it largest — is any X-ray or
   electron-diffraction experiment within reach of bounding it?
4. **Does the relay ruler `λ=N·ℓ_P` predict a hard short-λ diffraction limit?** When `N→1` (λ near
   ℓ_P) the sum can no longer phase smoothly — does diffraction itself break down, and is that a
   distinct prediction from continuum optics?
5. **Is grating resolving power `R=mN` a relay-coherence count?** Is `N` literally the number of
   relay sources kept in phase, tying spectral resolution to OP06's coherence-length order parameter?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — OP03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (the relay-Huygens sum takes no fit; λ=N·ℓ_P is the CR07 ruler)
- Engine namespaces used: depth_closure:: (c_local, relay phase), measured:: (l_P, c)
- Phase thresholds (committed before run):
    P1 continuum limit reproduces H–F integral; obliquity emergent ·
    P2 grating orders & R=mN exact (≤0.1%) · P3 single-slit null `λ/a` and Airy `1.22λ/D` ≤0.1% ·
    P4 granularity deviation reported with its size
- Forbidden retroactive changes: import the H–F envelope as the kernel then claim A; insert ψ or
    collapse to "explain" single-emission fringes; widen tolerances; IDENTITY-PASS; local namespaces
```

### Pivot table (numeric triggers; optics-specific)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|-------------------|---------------|----------------|-----------|
| P1 relay sum ≠ H–F integral in `ℓ_P→0` limit | refine the tick-phase kernel / secondary-source weighting | **KILL** "Huygens=relay rule" | hand-insert the obliquity factor and claim it emerged |
| P1 obliquity factor will not emerge | derive it from forward-relay directionality | **OPEN** the inclination factor | bolt on Kirchhoff `(1+cosχ)/2` by fiat |
| Pattern only forms with imported envelope | down-grade to **C**; tag row IMPORTED | — | claim A while the kernel is the wave-optics integral |
| P2/P3 angle off prediction by >0.1% | finer screen/aperture mesh; check `λ=N·ℓ_P` units | **OPEN** that pattern | tune `d`,`a`,`D` to hit textbook angles |
| Single-emission build-up needs ψ/collapse | re-frame as one emission sampling many relay paths (QM01) | **KILL** the no-ψ claim, report it | smuggle a probability amplitude |
| P4 granularity deviation = 0 or already excluded | report the null honestly (no SDT≠wave signature here) | **DEFER**/OPEN the ℓ_P probe | inflate the deviation to look falsifiable |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*OP03 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
