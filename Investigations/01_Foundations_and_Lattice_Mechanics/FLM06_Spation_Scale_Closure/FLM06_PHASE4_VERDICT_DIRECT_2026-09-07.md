# FLM06 Phase 4 — the deferred (a') relay-action seed, run direct

> **Run class: DIRECT** (main session, no agents). Pre-registered gate written into
> `flm06_relay_action_seed.cpp` before compiling. Tool: MSVC 19.44 (`cl /std:c++20 /O2`),
> exit 0. `laws.hpp` read-only — nothing added or changed there.

## What this closes

`FLM06_CLEARING_GEOMETRY_FLOOR.md` §5 named a next move and deferred it under the
label "GOM05": re-home ℏ as "the lattice relay-action quantum," then test whether
`l_P = ℏc/(k_B·T_Planck)` closes for some independently-motivated relay-saturation
temperature `T_Planck`. No investigation by that name ever ran it — `GOM05` was later
used for an unrelated closure (`GOM05_Variable_Spation_Closure`). This is that deferred
attempt, executed for the first time.

## Method

Three candidate `T*`, each built only from the one admitted mass/action seat
(`{ℏ ≡ m_e ≡ m_p}`, FLM13) plus unit bridges `c`, `k_B` — no `ℓ_P`, no `G`, nothing that
already encodes a length:

1. Proton rest-mass temperature, `T = m_p c²/k_B`
2. Electron rest-mass temperature, `T = m_e c²/k_B`
3. Electropause matrix-ceiling temperature, from `P_eff` (EMC04) read as a radiation
   pressure: `T = (3·P_eff/a_rad)^(1/4)`, with `P_eff` built from measured `R_p`, `a₀`
   and `α` — no `ℓ_P` anywhere in that chain.

Gate (pre-registered, before running): `l_P_test = ℏc/(k_B·T*)` within 1% of measured
`ℓ_P` = PASS.

## Result

```
candidate T*                                          T* [K]      l_P_test [m]     x l_P   gate
proton rest-mass temperature  T=m_p c^2/k_B        1.0888e+13     2.1031e-16   1.301e+19   FAIL
electron rest-mass temperature T=m_e c^2/k_B       5.9299e+09     3.8616e-13   2.389e+22   FAIL
electropause matrix-ceiling temperature (P_eff)    4.9873e+11     4.5914e-15   2.841e+20   FAIL
```

**0 of 3 passed.** Every candidate misses by 19–22 orders of magnitude — not a
near-thing, the same character of miss as FLM06 Phase 1's clean-but-short candidates.

## Verdict

**NEGATIVE — consistent with, and does not overturn, FLM06's proven Seed Theorem.**
The one admitted seat supplies an action/mass scale; it does not, combined with `c` and
`k_B` alone, supply a length anywhere near `ℓ_P` without also supplying `G` or `ℓ_P`
itself. Re-homing ℏ as "the lattice's own relay-action quantum" is a legitimate
ontological move — it stops ℏ from being narrated as a borrowed QM constant — but it
does not, on this run, produce a new derivation of `ℓ_P`'s absolute value.

`ℓ_P` remains Axiom R1. The deferred (a') thread is now closed as **tried and
negative**, not left open by omission — the deferral was real; the result was not
there to find with these three candidates.

## What would reopen it

A fourth candidate `T*` built from the admitted seat plus a *different* structural
relation than rest-mass energy or radiation pressure — e.g. something tying the
electropause to a relay-throughput rate rather than a static pressure. Not attempted
here; naming it is not claiming it.
