# SAR01 — Verdict: Le Sage Thermal Budget

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03.
**Tool:** `sar01_lesage_budget.cpp` → `results.txt` (real stdout). Thresholds pre-committed in `RUN_LOG.md`.

## Dual verdict

**Prompt completion: B** (all three ledgers computed; the recycling mechanism is *located* but not derived).
**Physics class: KILLED (absorption sub-mechanism) / OPEN (relay evasion).**

## The numbers

| Ledger | Power | vs 47 TW geothermal | Result |
|---|---|---|---|
| A — classical absorption floor, P ≥ F_grav·c (Sun→Earth force 3.54e22 N, native koppa chain, no G) | **1.06e31 W** | ×2.3e17 | **KILLED** |
| A′ — same ledger for the Sun (galactic-orbit force) | 1.12e29 W | 293 × L_Sun | KILLED |
| B — the prompt's own heating formula πR_E²·f·P_conv·c | **2.0e54 W** | ×4.3e40 | **REJECTED as a heat term** |
| C — SDT relay ledger | 0 by Law I | — | **OPEN** (axiomatic, see below) |

Cross-check earned in passing: Earth's mass from the koppa bridge
(ϟ_E = v²R/c² = 4.4 mm → N_baryons → m) lands at 5.971e24 kg, **−0.02%** off the reference
value, with no G and no M input anywhere in the chain.

## What this settles

1. **Any absorptive version of SDT occlusion is dead on arrival** — by 17 orders of magnitude
   (Earth) and 2.5 orders even at the most charitable stellar reading (Sun). This is Poincaré's
   classical Le Sage kill, now with SDT-native numbers on it. The prompt's step-1 formula
   (`(πR_E²)·P_conv·c·f`) is itself an absorption formula and overshoots by 40 orders: **f-coupling
   cannot be an energy coupling over the geometric disc.** The prompt's framing "P_heat = f × P_conv
   × ..." must not be reused.
2. **Where the energy goes (the ledger line):** nowhere — it never leaves the relay.
   - Law I (T1 shell cancellation): Φ = Nε preserved at every lattice point; throughput is
     relayed, never terminated (throughpole).
   - Law III occlusion is a **static pressure asymmetry** (boundary condition on relay
     *direction*), and a static pressure does no work: W = F·v, and a freely-falling body has
     F·v = 0 in its own frame. Hydrostatic analogy: a submerged hull under 10⁷ Pa does not heat.
   - Law IV: the cost of holding V_disp open is the **mass itself** — a standing cost, not a
     dissipation rate.
3. **The falsifiable ceiling:** if any fraction η of the force-carrying flux thermalises,
   Earth's heat budget demands **η < 4.4e-18** — i.e. < 21% of even the *coupled* fraction
   f = 2.1e-17. Occlusion must be conservative to 1 part in 10¹⁷ of the raw flux. Any future
   SDT derivation that produces a nonzero dissipation channel at the occlusion boundary
   kills gravity-as-occlusion outright. This is the sharpest internal kill-switch in the
   framework and should be cited by FLM12.

## The honest debt (why C is OPEN, not NATIVE)

The zero-heating result is **axiomatic** (Law I conservation), not derived. And evading the
heating horn of Le Sage by making redirection lossless walks into **Maxwell's other horn**:
purely elastic, isotropically re-emitted flux refills the partner's shadow and cancels the
net force. SDT's answer — *coherent* streamline deflection around V_disp that preserves the
shadow (FLM12 relay-Doppler picture) — is asserted, not derived. **Owed:** a derivation that
coherent redirection yields the (π/4)P_eff R₁²R₂²/r² shadow force with exactly zero
thermalisation. Until then: heating catastrophe **evaded by construction, not explained**.

## §D — Seven questions (HUNTER_PROTOCOL, on the KILLED/OPEN verdicts)

1. **Why fail (exact mechanism)?** Any absorptive coupling must eat energy at ≥ F·c (momentum
   p carried by lightspeed flux costs energy pc): 1.06e31 W vs 4.7e13 W observed — overshoot
   2.3e17. Sign and magnitude are kinematic, not adjustable.
2. **Recoverable?** The absorption ledger: NO — F·c is a floor, and real shadow-asymmetry
   absorption is worse by 1/δ. The relay evasion: possibly, if coherent redirection is derived.
3. **What did the target fail to account for?** That force is a *momentum* ledger and heating
   an *energy* ledger; a viable occlusion mechanism must decouple them exactly.
4. **Errored premise?** The prompt's step 1: "matter *absorbs* convergence flux" and
   "P_heat = f × P_conv × ...". f is a *pressure* ratio (P_eff/P_conv), not an energy-absorption
   efficiency. The premise "coupling = absorption" is the classical Le Sage premise; SDT never
   needed it and dies if it adopts it.
5. **What freedom corrects it?** Lossless redirection: occlusion as a boundary condition on
   relay *direction* (Law I conservation holds through the interaction).
6. **Native or knob?** Native — Law I (T1 shell cancellation) is an axiom of the framework,
   irreducible, not a fitted knob. But the *consequence* (shadow force survives coherent
   redirection) is not yet derived from it.
7. **Cascade?** YES — this failure-of-derivation runs to ground at the same root as EMC01's
   class-E force coefficient and FLM12's relay-Doppler mass mechanism: **the occlusion
   microphysics (coherent engagement/deflection profile at the V_disp boundary) is unbuilt.**

**Recovery: PARTIAL** — the errored premise (absorption) is named and replaced by a native
freedom (Law I conservative redirection), but the freedom's consequence (shadow force ≠ 0
under coherent redirection — the Maxwell horn) is not yet derived. Close the loop, do not
amputate: the η < 4.4e-18 ceiling is the closure debt's kill-switch, keep it live.

---

**earned:** absorption kill quantified (2.3e17×); η < 4.4e-18 ceiling; koppa mass cross-check (−0.02%).
**owed:** coherent-redirection force derivation (Maxwell horn); FLM12 linkage.

> **Prompt completion B · Physics class KILLED (absorption sub-mechanism) / OPEN (relay evasion) · Recovery PARTIAL · Cascade root: FLM12/EMC01 occlusion-boundary engagement profile (unbuilt).**
