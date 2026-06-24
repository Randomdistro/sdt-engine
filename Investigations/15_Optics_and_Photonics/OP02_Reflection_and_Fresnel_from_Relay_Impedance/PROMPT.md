# OP02 — Reflection and Fresnel from Relay Impedance

> **Author:** J.C. Harvey, Melbourne. **Status:** SPEC (seed, unstarted).
> Inherits the §0 anti-creep protocol and rules R0–R5 verbatim.

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

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| T1 normal `r=(n₁−n₂)/(n₁+n₂)` | glass R≈0.04, π flip when n₂>n₁ | reflection not an impedance mismatch |
| T2 Brewster `tanθ_B=n₂/n₁` | p-reflectance → 0 at θ_B | s/p split not the transverse budget |
| T3 `R+T=1` | holds to machine precision all angles | relay count not conserved |

## Dependencies

**Upstream:** OP01 (n=1/(1−z), `c_local`). **Downstream:** OP03 (interference of the reflected
branches), OP06 (cavity mirrors), thin-film/coating optics. **Related:** [[project_cq43_variable_closure]],
Law V movement budget, FD05 (acoustic impedance analogue).
