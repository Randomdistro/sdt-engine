# OP02 — Reflection and Fresnel from Relay Impedance

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether partial reflection, the Fresnel amplitudes, the π phase flip,
   and the Brewster angle are a *derived* consequence of a single closure-impedance mismatch
   `Z = Z₀/n` (the fraction of relay impulse that cannot be handed across an abrupt change in spation
   size), or whether SDT can only *re-label* the standard Fresnel/Maxwell result — importing
   `r=(n₁−n₂)/(n₁+n₂)` and calling it derived.
2. **Why does it matter?** — Reflection is the one optical phenomenon SDT cannot reach with refraction
   alone (OP01 gives `n`, not what bounces back). If `Z=Z₀/n` earns Fresnel natively, every
   downstream node (OP03 reflected-branch interference, OP06 cavity mirrors, thin-film/AR coatings)
   inherits an impedance picture with no Maxwell stress tensor; if it can't, matter reflection stays
   **OPEN** and OP03/OP06 lose their boundary conditions.
3. **How will we find out?** — Four gated phases (§Strategy): the impulse-matching derivation of the
   normal-incidence `r` runs **before** any standard Fresnel form is written; the Law-V transverse
   budget gives oblique s/p and Brewster; relay-count gives `R+T=1`; absorbing metal is the stretch.
   The native impulse-match must be shown; writing `(n₁−n₂)/(n₁+n₂)` from a textbook caps the grade
   at C (§ anti-tautology gate).
4. **What would prove us wrong?** — §Falsification, with numeric kill triggers: glass `R` off 0.040
   by >0.001; wrong π-flip sign; Brewster off `arctan(n₂/n₁)` by >0.1°; `R+T−1` exceeding 1e-12.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

### Anti-tautology firewall

`Z = Z₀/n` is the *load-bearing* step: it must come from matching the relayed impulse and its
tangential flux at a closure step, **not** from asserting the acoustic/EM impedance result. The
test that can fail: does continuity of the relay impulse across a one-tick change in spation size
*force* `r=(Z₂−Z₁)/(Z₂+Z₁)`, including the sign? **Writing the Fresnel coefficient by hand, or
calling `r` from a Maxwell-boundary library and matching it, is the identity, not the derivation —
it caps the grade at C and the row is tagged IMPORTED.** Lab `n` magnitudes entering only as the
*medium descriptor* (via OP01's bound-vortex `z`) are MEASURED-INPUT, not a fit.

## Question

When an emission (the relay phase-impulse) crosses from one closure region into another it
*partly* reflects. In SDT there is no boundary "potential step" and no wave-equation Maxwell
stress tensor to invoke — only a change in the relay step. **Can the Fresnel amplitude
coefficients, R + T = 1, the π phase flip on hard reflection, and the Brewster angle all be
derived from a single closure-impedance mismatch `Z ∝ 1/c_local = n` at the interface — the optical
analogue of an acoustic impedance mismatch in the spation lattice?** If so, partial reflection is
just the fraction of the relay impulse that cannot be handed forward across an abrupt change in
spation size, and the whole of thin-film optics follows.

## SDT mechanism & hypotheses

The lattice relays at `c_local = c(1−z)`; the closure ratio `n = 1/(1−z)` (OP01) plays the role of
a wave impedance because it sets how much momentum-flux a spation can hand to its neighbour per
tick. At a closure discontinuity, continuity of the relayed impulse and of its transverse flux
forces a reflected branch.

- **H1 (impedance = index):** define relay impedance `Z = Z₀/n`; matching the relayed impulse and
  its tangential flux at the interface gives `r = (Z₂−Z₁)/(Z₂+Z₁) = (n₁−n₂)/(n₁+n₂)` at normal
  incidence — the Fresnel amplitude, with the sign giving the π flip when `n₂>n₁` (hard wall).
- **H2 (s/p split = transverse budget):** projecting the relay impulse onto the interface (Law V
  movement budget) yields the angle-dependent `r_s, r_p`; Brewster's angle is where the p-branch
  reflected relay path is degenerate (no transverse component to reflect), `tanθ_B = n₂/n₁`.
- **H3 (energy bookkeeping):** `R = |r|²`, `T = (n₂cosθ_t)/(n₁cosθ_i)|t|²`, and `R+T=1` from
  spation-count (relay) conservation — not an imposed Poynting theorem.

## Strategy

**Phase 1 — Normal-incidence amplitude.** *Goal:* the scalar reflection coefficient. *Method:* match
relayed impulse across a step in `n` from OP01. *Success:* `r=(n₁−n₂)/(n₁+n₂)`, π flip sign correct;
glass `R≈0.04` at n=1.5 reproduced to <1%.

**Phase 2 — Oblique s and p.** *Goal:* full Fresnel `r_s, r_p, t_s, t_p`. *Method:* decompose the
relay impulse via the Law-V transverse budget. *Success:* both curves match Fresnel to <1% across
0–90°; Brewster `tanθ_B=n₂/n₁` recovered exactly.

**Phase 3 — Conservation & thin film.** *Goal:* R+T=1 and a one-layer anti-reflection coating.
*Method:* relay-count bookkeeping + two-interface relay summation. *Success:* `R+T=1` to machine
precision; quarter-wave AR minimum at `n=√(n₁n₂)` predicted.

**Phase 4 — Absorbing/metal case (stretch).** *Goal:* complex `n` reflectance. *Method:* attenuated
relay (closure with loss). *Success:* metal `R→1` trend; phase-on-reflection sign correct.

## Success criteria

- **PASS (A):** all Fresnel `r/t`, R+T=1, π flip, and Brewster from one impedance `Z=Z₀/n`, zero fits.
- **QUALIFIED (C):** the above with lab `n` magnitudes CALIBRATED via measured bound-mass z (expected).
- **PENDING (D):** normal incidence + Brewster recovered, full oblique s/p only schematic.
- **FAIL (F):** cannot get partial reflection or the sign flip from the closure mismatch.

## ⑧ Falsification tests (each states the numeric outcome that kills it)

| ID | Test | SDT prediction | The number that kills it |
|----|------|----------------|--------------------------|
| F1 | Normal-incidence amplitude from impulse-match | `r=(n₁−n₂)/(n₁+n₂)`; air→glass(1.5) `R=0.0400`; π flip when n₂>n₁ | `R` off 0.0400 by >0.001, or reflected-impulse sign **does not** invert when n₂>n₁ ⇒ reflection is not an impedance mismatch (thesis dead) |
| F2 | Brewster from transverse budget | p-reflectance has a true zero at `θ_B=arctan(n₂/n₁)` (=56.31° for 1→1.5) | the p-branch minimum is nonzero, or `θ_B` off `arctan(n₂/n₁)` by >0.1° ⇒ s/p split is not the Law-V transverse projection |
| F3 | Relay-count conservation | `R+T=1` at every angle | `|R+T−1| > 1e-12` (machine eps) at any angle ⇒ relay impulse not conserved; an external Poynting theorem was smuggled in |
| F4 | Quarter-wave AR minimum | reflection nulls at `n_coat=√(n₁n₂)` (=1.225 for air/glass) | AR minimum not at `√(n₁n₂)` within 1% ⇒ two-interface relay summation is wrong |
| F5 | Anti-tautology | the normal-incidence `r` is *derived* from impulse continuity, not written from a textbook | if `r` can only be reproduced by importing the Fresnel/Maxwell form ⇒ Class capped at **C**, row tagged IMPORTED (not an F, but not an A) |

## Dependencies

**Upstream (required):** OP01 (`n=1/(1−z)`, `c_local`, the medium descriptor), **Law V** (movement
budget → the s/p transverse split). **Downstream (unblocked):** OP03 (interference of the reflected
branches), OP06 (cavity mirrors), thin-film/AR-coating optics. **Lateral:** EMC03 (handedness, for
the phase-flip sign), FD05 (the acoustic-impedance-mismatch analogue in the same lattice).
**Framework:** `Theory/00_Ruleset.md`, `Theory/05` audit spine, EMC03 note
[[project_cq47_repulsion_inverse]], variable-closure note [[project_cq43_variable_closure]].

## Questions This Opens *(generative — log new ones in `OP02_VERDICT.md`)*

1. **Is `Z=Z₀/n` exactly the acoustic impedance of the lattice?** If the optical and FD05 acoustic
   mismatches are the *same* `Z`, is reflectance at any interface (optical, acoustic, seismic) one
   relay-impulse-continuity law with different relay speeds?
2. **Does the π flip = EMC03 handedness reversal?** Is "hard-wall phase inversion" literally the
   relay impulse reversing its ± redirection on a denser-closure boundary — and does that fix the
   sign of metal reflection without a complex `n` postulate?
3. **Is the metal `R→1` limit a closure *saturation*?** When the next spation cannot relay forward at
   all (lossy closure), does the impulse reflect wholesale — and is the skin depth the relay
   attenuation length, not a field penetration depth?
4. **Can Brewster's zero be a movement-budget exhaustion?** At `θ_B` the p-branch has no transverse
   budget left to reflect; is that the same `v_circ²+v²=c²` partition as Law V, making Brewster a
   kinematic, not an EM-boundary, statement?
5. **Does thin-film color come out as relay-path interference with OP03?** If OP02's two reflected
   branches feed OP03's phased sum directly, is soap-film/oil-slick color a pure relay-time-difference
   prediction with zero new inputs?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — OP02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the impulse-match chain (lab n via OP01 z = MEASURED-INPUT, not a fit)
- Engine namespaces used: depth_closure:: (n=1/(1-z), c_local), law_V:: (transverse budget), measured::
- Phase thresholds (committed before run):
    P1 glass R=0.0400 ±0.001, π-flip sign correct · P2 Brewster ±0.1°, p-zero true ·
    P3 |R+T−1|<1e-12 all angles · P4 AR null at √(n₁n₂) ±1%
- Forbidden retroactive changes: import Fresnel/Maxwell `r` then claim A; widen tolerances;
    plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (numeric triggers; optics-specific)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|-------------------|---------------|----------------|-----------|
| P1 glass `R` off 0.0400 by >0.001 | re-derive impulse + tangential-flux continuity; check normalisation | **KILL** H1 (reflection≠impedance) | tune `n` to hit 0.04 |
| P1 reflected-impulse sign wrong | tie the flip to EMC03 ± handedness on denser closure | **OPEN** the phase-flip mechanism | assert π by fiat |
| `r` only reproducible by importing Fresnel | down-grade to **C**; tag row IMPORTED | — | claim A while importing the coefficient |
| P2 Brewster off `arctan(n₂/n₁)` >0.1° | recheck Law-V transverse projection of the relay impulse | **OPEN** s/p split | borrow Jones/stress-tensor |
| P3 `|R+T−1|>1e-12` | audit relay-count bookkeeping for a smuggled Poynting term | **KILL** conservation claim | normalise the residual away |
| P4 absorbing metal needs complex-`n` postulate | model as lossy/saturated closure (skin = relay attenuation) | **DEFER** Phase 4 | import Drude `ε(ω)` as mechanism |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*OP02 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
