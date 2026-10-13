# TD09 — The Freedom Ledger of Binding (Harvey 2026-07-26)

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC, written BEFORE the tool (gates below are
> pre-commitments). **Run class target: DIRECT** (main session, no agents).
> **Inherits** R0–R5 anti-creep verbatim.

## The claim (Harvey, verbatim core)

Entropy is dead; degrees of freedom is alive. Things move toward greater freedom. Movement
causes time; change causes time. Matter demonstrably climbs into higher, more sophisticated
arrangements — so the "descent into disorder" narration is wrong even where the counting is
right.

## The sharpening that makes it computable

S = k_B ln W already IS a freedom count (TD01). The naive version of the climb-claim — "binding
opens more coordinates than it closes" — is dead on arrival: coordinate count is conserved
(two rigid bodies carry 12 coordinates bound or free). The live version is the **accessible-route
ledger**: binding closes configurational routes for the pair but releases E_bind of movement
into the bath, opening routes there. The claim: **matter binds exactly where the total ledger
nets positive**, and the universe's actual assembly history should sit where the ledger says.

## Phases and PRE-COMMITTED gates

**P1 — Ledger formalism.** Per binding event p + n → d + γ at temperature T:
Δfreedom = E_b/kT (bath routes opened) − ΔlnW_config (pair routes closed: the thermal-wavelength
/ number-density counting, photon bath included via measured η). Show algebraically that
Δfreedom = 0 is the equilibrium (Saha) condition — the ledger and equilibrium counting must be
the SAME equation (two-stream identity, machine precision in the tool).

**P2 — The cold-universe statement.** At T = 300 K, per-deuteron net freedom ≈ E_b/kT ~ 10⁷–10⁸
nats vs a configurational cost of order 30 nats — print the ledger. This is WHY matter climbs:
binding is freedom-positive in a cold bath. (Statement, not gate — it cannot fail at any
plausible number.)

**P3 — THE GATE: the flip temperature.** The ledger flips sign when kT approaches E_b divided by
the configurational cost — which contains ln(1/η): the photon bath's route surplus delays
binding. Compute T_flip (defined: n_d/n_p = 1 at equilibrium with measured η = 6.13×10⁻¹⁰,
X_n/X_p = 1/7 measured freeze-out ratio; secondary convention X_n/X_p = 1 reported for
sensitivity) by bisection from derivation basis constants + measured E_b = 2.224573 MeV. Compare to
the measured BBN deuterium bottleneck (D/H rise at T ≈ 0.06–0.09 MeV).
- **G3-PASS:** T_flip ∈ [0.035, 0.17] MeV (factor ~2.2 band).
- **G3-FAIL:** outside the band → the ledger as posed does not locate the universe's actual
  first assembly step; recorded, no rescue.

**P4 — Honesty block (mandatory in output).** (a) The flip equation is algebraically Saha —
**convergent route, shared counting; cannot discriminate against standard equilibrium
thermodynamics and must not be claimed as a beat.** What the reading adds: the second law
restated as freedom-seeking (no math change), heat death re-read as maximum circulation (Law V:
at max W nothing stops — translation trades into internal spin), and the self-organization
criterion quantified (complexity forms where E_released/kT exceeds the route cost — the same
ledger governs chemistry and stellar assembly; scoping statement only, own pre-commits owed).
(b) Delete test: remove the freedom narration and the number stands; remove the *counting* and
nothing stands. (c) TD01's Phase-3 debt is RE-POSED, not paid: "show W climbs under the relay
rule alone" (the freedom-climb theorem) — same falsifiable deliverable, decay costume gone.

## Outputs
`td09_freedom_ledger.cpp` → `td09_rerun_<date>.txt`, `TD09_VERDICT_DIRECT_<date>.md`.

## Forbidden
Widening the G3 band after the number; hiding the Saha convergence; claiming P2 or the
narration as evidence; importing any cosmology beyond measured η and T (no ΛCDM machinery).
