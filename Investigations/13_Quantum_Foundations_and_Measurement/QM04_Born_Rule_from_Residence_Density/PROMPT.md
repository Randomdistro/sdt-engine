# QM04 — Born Rule from Residence Density

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
> **Domain:** Quantum Foundations & Measurement (deterministic relay mechanics, no ψ).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Why is probability the **square** of the amplitude? Can the Born rule
   `P(x) ∝ |amp(x)|²` be **derived** as a geometric fact — wake energy density ∝ displacement² (every
   elastic medium), and least-resistance vortex residence ∝ energy density — so the landing histogram
   *is* `|amp|²` as a count, with **no Born postulate, no ψ, no measurement axiom** written anywhere?
   The two open sub-questions: (a) is the square genuinely the *elastic energy* of the relay medium,
   or is it inserted; (b) is residence ∝ energy density a *derived* equidistribution result, or an
   ergodic *assumption* in disguise?
2. **Why does it matter?** — The Born rule is the single hardest QM postulate to "explain"; a native
   derivation removes the deepest part of the §8.2 census debt. The same square is reused by QM03
   (the `−2κd`), QM01 (fringe contrast), QM07 (SG spot weights) and QM05 (correlation counts) — all
   inherit whatever QM04 imports.
3. **How will we find out?** — Four gated phases (§④). Phase 1 derives `|A_a+A_b|²` from the relay
   medium's elastic energy **before** any probability language is used; Phase 2 measures the residence
   histogram from the QM01 steering engine — the proportionality must be *measured*, not coded in
   (the §⑤ anti-tautology gate).
4. **What would prove us wrong?** — §⑧, three falsifiers with numeric kill triggers (a square that is
   axiomatic rather than elastic; a histogram that does not track energy density to <1%; normalisation
   or positivity that needs an imposed axiom).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

## Question

Why is probability the **square** of the amplitude? The Born rule `P(x) = |ψ(x)|²` is a *postulate*
in standard QM. SDT must instead **derive** the square. This investigation deepens QM01-H3: the
"amplitude" is the convergence-wake displacement field; its **energy density** goes as displacement²
(every elastic/relay medium stores energy ∝ strain²); and a vortex steered by the wake (least-
resistance, [[project_cq43_variable_closure]]) spends long-run time — its **residence/landing
density** — in proportion to that energy density. So `|amp|²` is the *count* of where vortices land,
and the square is **geometric, not axiomatic**.

## SDT mechanism & hypotheses

The wake is a real pressure/displacement field on the lattice. Two facts conspire: (1) the stored
energy density of a superposed displacement field is `½ K (A_a + A_b)²` — the square is just elastic
energy; (2) a vortex following the wake gradient settles preferentially where the wake delivers most
convergence, so its residence time ∝ energy density. Run many one-at-a-time vortices (QM01) and the
histogram **is** `|amp|²` because that is where they linger and land.

- **H1 (energy ∝ displacement²):** the relay medium stores energy ∝ strain² (Law I/III), so the
  superposed-wake intensity is `|A_a + A_b|²` natively — the cross-term gives interference.
- **H2 (residence ∝ energy density):** least-resistance steering makes long-run vortex residence
  time proportional to local wake energy density (an ergodic/equidistribution argument on the lattice).
- **H3 (no negative probabilities, normalisation):** total landings conserved (one vortex always
  lands somewhere) ⇒ normalisation; energy density ≥ 0 ⇒ P ≥ 0 — both native, not imposed.

## Strategy

**Phase 1 — Energy density of a superposed wake.** *Goal:* show intensity = `|A_a+A_b|²`. *Method:*
elastic energy of a summed displacement field on the lattice (Law I). *Success:* the square + cross
term derived from elastic energy, **not** asserted.

**Phase 2 — Residence ↔ energy density.** *Goal:* prove landing density ∝ energy density. *Method:*
simulate N steered vortices (QM01 engine); measure residence-time histogram vs wake energy density.
*Success:* histogram ∝ energy density to RMS <1% over N≳10⁴; the proportionality is the Born rule.

**Phase 3 — Normalisation & positivity.** *Goal:* recover ∑P=1, P≥0. *Method:* conservation of
vortex count + non-negativity of energy density. *Success:* both fall out with no extra axiom.

**Phase 4 — Cross-checks.** *Goal:* the square shows up elsewhere. *Method:* reuse in QM03 (`−2κd`
amplitude→intensity), QM01 fringe contrast, QM07 SG spot weights. *Success:* one square serves all.

## Success criteria (canonical A–F) + anti-tautology gate

- **PASS (A — NATIVE):** the square `|A_a+A_b|²` is derived from the relay medium's **elastic energy**
  (not asserted); the landing histogram from the QM01 steering engine tracks energy density to RMS
  <1%; normalisation and positivity fall out of count-conservation + energy≥0; zero fitted params.
- **QUALIFIED (C — CONVERGENCE):** square shown for the wake energy density; residence∝energy argued
  but leans on one flagged ergodic/equidistribution assumption. **Anti-tautology gate: if the code
  *assigns* landing probability = energy density (i.e. writes the Born rule in) rather than *measuring*
  the histogram of independently-steered vortices, the square was imported — cap at C.** Expected.
- **PENDING (D):** energy² native but the residence-time link only heuristic/numerical.
- **FAIL (F):** the square cannot be obtained without re-importing the Born postulate / a probability
  axiom. Report; debt stands.

## Falsification tests (each has a real failure mode + numeric kill trigger)

| # | Test | SDT prediction | What kills it (numeric) |
|---|------|----------------|-------------------------|
| T1 | square is **elastic** energy | intensity = ½K(A_a+A_b)² with the interference cross-term, derived from relay strain energy | if the ² only appears by writing `amp²` / Born into the code, the square is axiomatic not geometric → C; if the cross-term sign/magnitude is wrong, the elastic-energy route fails → F |
| T2 | residence ∝ energy density | landing histogram of independently-steered vortices ∝ energy density, RMS <1% over ≥10⁴ | if RMS >1%, or the proportionality holds only because probability was set = energy density, Born is not a measured residence count |
| T3 | normalisation native | ∑P=1 and P≥0 from count-conservation + energy≥0, **no extra axiom** | if either requires an imposed normalisation/positivity postulate, the derivation is incomplete → D/F |

## Dependencies

**Upstream:** QM01 (wake + one-at-a-time steering — the engine this deepens), Law I (relay energy).
**Downstream:** QM03 (the `−2`), QM05 (Bell uses the same residence/measurement count), QM07 spot weights.
**Related:** [[project_cq43_variable_closure]] (least-resistance steering), [[project_paradox_census]] (§8.2 #1).

## Questions This Opens *(generative — log new ones in `QM04_VERDICT.md`)*

1. **Is the equidistribution (residence ∝ energy density) provable, or is it the new postulate?** If it
   reduces to an ergodic theorem on the relay lattice, Born is fully derived; if it must be assumed,
   SDT has *traded* the Born postulate for an ergodic one — is that progress or relabelling? State it.
2. **Does the cross-term predict the *exact* fringe contrast QM01 measures?** If the elastic
   energy-density cross-term and the QM01 steering histogram give the same visibility, the two units
   share one origin; a mismatch flags a borrow in one of them.
3. **Where does the square break?** Strongly non-linear relay regimes (occlusion saturation, g→2 near
   contact) might make stored energy *not* ∝ strain². Is there a measurable departure from Born in a
   high-amplitude wake — an SDT-only prediction?
4. **Does positivity (P≥0) ever fail?** Energy density is ≥0, so P≥0 is automatic — unless interference
   can make a *negative* local residence rate. Can it, and would that be a Wigner-function-style
   negativity with a mechanical meaning?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — QM04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the native chain (flag the one ergodic/equidistribution assumption if leaned on)
- Engine namespaces used: Law I/III (relay strain energy), QM01 steering engine — NO ψ, NO Born/probability axiom written into the steering, NO atomic:: in the native chain
- Phase thresholds (committed before run): P1 cross-term derived (sign+magnitude) · P2 histogram ∝ energy density RMS <1% over ≥10⁴ · P3 ∑P=1, P≥0 with no extra axiom
- Forbidden retroactive changes: assign probability = energy density in the steering then claim it was measured; widen RMS; plug; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P1 cross-term sign/magnitude wrong | re-derive the elastic strain energy of the summed displacement | **OPEN** the elastic-square route; cap at C | write `amp²`/Born to force the square |
| P2 histogram off energy density by >1% | refine the steering integrator / vortex count | **OPEN** the residence∝energy claim; report best RMS | set probability = energy density and call it a measurement |
| P2 proportionality needs an ergodic assumption | name it explicitly; argue it from lattice equidistribution | accept **C** honestly — postulate traded, not removed | hide the ergodic assumption |
| P3 normalisation/positivity needs an axiom | derive from count-conservation + energy≥0 | **OPEN**; state the residual axiom | impose ∑P=1 by hand and claim native |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · the Born rule / a probability axiom inserted into the steering chain ·
  `atomic::`/GM/G in the native chain · hiding a traded ergodic postulate.

---

*QM04 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
