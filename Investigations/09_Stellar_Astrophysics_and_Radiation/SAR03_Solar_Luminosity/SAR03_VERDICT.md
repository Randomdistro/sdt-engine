# SAR03 — Verdict: Solar Luminosity from Convergence Recycling

**Author:** J. C. Harvey, Melbourne. **Date:** 2026-07-03.
**Tool:** `sar03_solar_luminosity.cpp` → `results.txt` (real stdout). Chains pre-registered in `RUN_LOG.md`; gate 20% (prompt's own); no exponent fishing.

## Dual verdict

**Prompt completion: B** (every chain the prompt names was computed and graded; nothing invented).
**Physics class: KILLED** (the prompt's derivation chain) / the framework question stays **OPEN**.

## The numbers

| Chain (pre-registered) | L [W] | vs L_Sun = 3.828e26 W | Grade |
|---|---|---|---|
| C1: z_Sun·4πR²·P_conv·c (prompt "Derivation Chain") | 9.53e69 | ×2.5e43 | **KILLED** |
| C2: C1 × f_transfer | 2.02e53 | ×5.3e26 | **KILLED** |
| C3: πR²·F_CMB (CMB interception) | 4.76e12 | ×1.2e-14 | **KILLED** as source |
| C4: 4πR²σT_eff⁴ | 3.84e26 | 1.004 | **IDENTITY** — excluded |
| C5: r_domain = √(L/4πF_CMB) = 20,857 AU vs Oort ~20,000 AU | — | ratio 1.04 | CONSISTENT, but consumes L |

Also flagged: the PROMPT's data table gives 4.77e7 W for the intercepted-CMB row — arithmetic
error of ~10⁵ (correct: 4.76e12 W).

## What this settles

1. **The prompt's convergence-recycling chain does not produce L_Sun.** Not by 20%, not by an
   order of magnitude — by 43 orders (C1) or 27 orders (C2). The Sun radiates 8×10¹³ times more
   than the CMB flux it intercepts (C3), so "recycling the ambient convergence flux" cannot be
   the luminosity source under any linear reading of Law II.
2. **The only place the budget closes is the Stefan–Boltzmann identity (C4)** — which is a
   definition of T_eff, not a prediction. Diagnostic: the required radiating pressure
   L/(4πR²c) = 0.210 Pa equals u(T_eff)/4 = 0.211 Pa. There is a 47-order gap down from P_conv
   and a 14-order gap up from F_CMB, and no pre-registered SDT quantity spans either gap.
3. **The one earned line: C5.** The pressure-domain radius (where solar flux falls to the CMB
   floor) is 20,857 AU ≈ the Oort-cloud centreline (ratio 1.04). That is a real SDT-native
   *scale* statement — but it takes L as an input; it says nothing about where L comes from.

## §D — Seven questions (on the KILLED chains)

1. **Why fail?** C1 multiplies the full Planck-scale convergence pressure P_conv (2.46e48 Pa)
   by a macroscopic area — but P_conv is a Planck-cell quantity; applying it over 6e18 m² counts
   each shell ~10⁴³ times. C3 fails oppositely: the ambient CMB flux is 14 orders too dilute.
4. **Errored premise?** "The Sun re-radiates what it intercepts, scaled by z or f." Both scalings
   are *pressure ratios*, not power-conversion efficiencies; the prompt chain has no dimensional
   mechanism connecting interception to emission. (Same premise-class as SAR01 Ledger B —
   pressure ratios misused as energy couplings.)
5/6. **What freedom corrects it?** A per-nucleon release rate (Law II cascade applied to the
   Sun's N_baryons ≈ 1.2e57 with the nuclear rearrangement energetics of NP17), i.e. luminosity
   from *held-content release during fusion rearrangement*, not from ambient-flux recycling.
   That is a native route but it is **unbuilt** — nothing in `law_II::` computes a release rate.
7. **Cascade?** YES — runs to ground at the same root as SAR01: **the energy-coupling
   microphysics of the relay (what converts held content to radiated power, and at what rate)
   is not in the engine.** Law II names stars "convergence recyclers" but provides no rate law.

**Recovery: PARTIAL** — premise error named (pressure ratio ≠ power efficiency), native route
named (per-nucleon release rate via nuclear rearrangement), freedom not yet built. The Closure
Principle applies: do not delete Law II's "recycler" language — derive its rate law or retire it
explicitly at canon level (Harvey's call, not this cluster's).

**earned:** clean 43/27/14-order kills; prompt table error caught; C5 Oort-scale consistency restated with honest input-labelling; σ_SB whitelist cross-check (a_rad·c/4, −0.0004%).
**owed:** Law II rate law (release cascade → W per nucleon); C5 upgrade blocked until L is derivable.

> **Prompt completion B · Physics class KILLED (prompt chain; framework question OPEN) · Recovery PARTIAL · Cascade root: Law II release-rate law unbuilt (shared with SAR01 energy-ledger root).**
