# OP02 — Verdict: Reflection and Fresnel from Relay Impedance

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04 · Tool: `op02_fresnel.cpp` (exit 0; stdout in `results.txt`)

## What was done

Two mechanical continuity conditions at a closure step — (i) tangential transverse displacement
continuous (the lattice does not tear), (ii) tangential relayed impulse-flux continuous (no momentum
accumulates on a massless step), with relay impedance Z = Z₀·n forced by one-lattice/constant-coupling
and variable c_local — were solved as a numeric 2×2 system per angle. No Fresnel closed form, no field
formalism, no amplitude ontology anywhere in the solver; arrival-time offsets kept in two real registers.

## Earned (real stdout, committed gates)

- Normal incidence: r = −0.2000000000 exactly → R = 0.0400 (gate ±0.001); impulse inversion on the
  denser-closure step (the "π flip") and non-inversion on the softer step both emerge from the sign of
  the solved system. Stokes r′ = −r emerged, not imposed.
- Oblique: solved s and p branches match the OBSERVED Fresnel column to 0.000e+00 over 0–89.9°.
  Brewster is a true zero of the solved p-system at 56.309932° = arctan(n₂/n₁), residual 6.7e-17.
- Conservation: max |R+T−1| = 4.4e-16 across all angles, both branches — the impulse-flux ledger closes
  with nothing external smuggled in.
- Thin film: explicit 400-bounce relay-path summation puts the quarter-wave AR null at n_c = 1.2245
  vs √(n₁n₂) = 1.224745 (0.02%) — H5 of the prompt's "questions this opens" answered in passing.

## Owed (the honest caps)

1. **The pairing rule is the missing closure.** WHICH displacement/impulse components the lattice hands
   across the step for the two transverse orientations is asserted, not derived from relay mechanics.
   A full lattice-elastic treatment adds a longitudinal branch and further conditions; its suppression
   is asserted (GOM06 transverse channel), not derived. This caps the class at **CONVERGENCE** — the
   continuity algebra is generic to any relaying medium; SDT's earned content is Z = Z₀·n from
   one-lattice/constant-coupling, plus the π-flip sign falling out mechanically.
2. **P4 (metal/absorbing) DEFER** — a lossy-closure model is owed; importing a conduction model as
   mechanism is forbidden.
3. **TIR/evanescent region logged OPEN, not gated** (§G discipline): beyond the critical angle the
   forward branch becomes a non-relaying penetration — constraint-channel territory per FLM14 ADJ-7.
   No gate here legislates "nothing sub-cycle"; the regime is owed a two-channel treatment.

## §D seven questions (on the OPEN rows — pairing rule and P4)

1. **Why open?** Not a numeric miss — every committed gate passed. Open because the boundary-condition
   *selection* (2 of a possible 4+ continuity rows; longitudinal branch dropped) was chosen, not forced.
2. **Recoverable?** Plausibly: derive the pairing from the relay tick rule on an explicit two-region
   lattice (FLM08/CONDENSA machinery) — if the lattice's transverse channel relays only those two
   components, the pairing is forced and the class lifts toward NATIVE.
3. **What did the target fail to account for?** The longitudinal lattice branch — the historical
   elastic-medium failure point; SDT parks it in the pressure/gravity channel by assertion.
4. **Errored premise?** None proven errored; the unproven premise is "the lattice hands exactly the
   tangential displacement + tangential impulse-flux and nothing else."
5. **What freedom corrects it?** An explicit discrete two-region relay simulation with a closure step —
   measure what actually reflects; no free parameter involved.
6. **Native or knob?** Native (the FLM08 lattice_structure header exists); no knob needed.
7. **Cascade?** Yes — shares its root with OP04 (which transverse components carry) and OP03's
   obliquity question: all three trace to the ONE unbuilt piece: **the explicit transverse relay rule
   on the discrete lattice** (call it the OP-root debt; QM01/FLM08 territory).

**Recovery grade: PARTIAL** (route named and native, not yet executed).

## Generative questions logged

Q1 (one impedance law for optical/acoustic/seismic): supported — the solver is medium-agnostic by
construction. Q2 (π flip = handedness reversal): untested here, OPEN. Q5 (thin-film colour from relay
paths): the 400-bounce sum already produces it; zero new inputs.

---

**Prompt completion B · Physics class CONVERGENCE · Recovery PARTIAL · Cascade root: OP-root (explicit transverse relay rule on the discrete lattice; shared with OP03-obliquity, OP04-pairing)**
