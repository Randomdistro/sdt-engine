# NP04B — Three-Neutron Genesis Gate *(energetics PASS · kinetics UNRESOLVED)*

> **The missing test NP04A does not perform.** NP04A closes the *decay* ledger (`n→p+e+ν̄`, `³H→³He+e+ν̄`). It never demonstrates *assembly*: `3n → triton + e⁻ + ν̄ₑ`. This sub-investigation isolates that step and is brutally honest about it — **the energy ledger closes; the rate does not.**

## 1. Objective
Test the forward genesis `3 free neutrons → triton (¹H nucleus) + e⁻ + ν̄ₑ` on **two separate gates that must not be conflated**:
- **Energy gate (F0):** is the assembly exothermic? — *answerable now.*
- **Kinetic gate (F0b):** does it actually proceed at a non-negligible rate? — *not yet derivable.*

## 2. The energy gate (F0) — passes
```
Q(3n → t + e⁻ + ν̄ₑ) = Q_n + B(³H)
                     = 0.7823 + 8.482  =  9.264 MeV   (exothermic ⇒ ENERGY GATE: PASS)
```
Derivation (pure conservation): `3m_n = M_nuc(t) + m_e + Q`, with `M_nuc(t) = m_p + 2m_n − B(t)` ⇒ `Q = (m_n−m_p−m_e) + B(t) = Q_n + B(t)`.

**Sequential decomposition** (the physically realisable path, since the di-neutron is unbound):
```
step 1   n → p + e⁻ + ν̄ₑ        +Q_n          = +0.782 MeV   (rate-limiting: τ_n ≈ 880 s)
step 2   p + n → d + γ           +B(²H)        = +2.224 MeV   (radiative capture)
step 3   d + n → t + γ           +[B(t)−B(d)]  = +6.258 MeV   (radiative capture)
                                  ───────────────────────────
                          Σ = Q_n + B(t) = 9.264 MeV  ✓  (= F0, no double-count)
```

## 3. The kinetic gate (F0b) — unresolved
The energy being available says nothing about the rate. F0b requires what SDT has **not** yet derived:
- **3-body simultaneity / density** — three neutrons must coincide; in any dilute regime this is rare.
- **Weak split timing** — step 1 is gated by the slow free-neutron β-decay (`τ_n ≈ 880 s`); neutrons escape/decay-away competing.
- **Proton-keystone requirement** — the di-neutron is unbound (NP04A-F2), so genesis *cannot* proceed by `n+n`; it must route through a proton (step 1 first). The proton is the obligatory keystone.
- **Radiative-capture cross-sections** (steps 2–3) — these live in the BBN / stellar-nucleosynthesis regime and are not yet expressible in occlusion units.

**KINETIC GATE: UNRESOLVED (class F).** Energetics allowed; rate/probability not predicted.

## 4. Verification stages
- **F0** — compute `Q(3n→t) = Q_n + B(t)`; confirm exothermic; print the sequential decomposition and its sum-check. *(tool: `cq29b_genesis_gate.cpp`)*
- **F0b** — enumerate the kinetic suppressors above; declare UNRESOLVED with explicit failure criteria (no fabricated rate). A future stage may attempt step 2–3 cross-sections in occlusion units — that is the open work.

## 5. Data requirements
| quantity | value | gate |
|---|---|---|
| `Q_n = m_n−m_p−m_e` | 0.7823 MeV | F0 |
| `B(²H)` deuteron | 2.224 MeV | F0 step 2 |
| `B(³H)` triton | 8.482 MeV | F0 |
| **`Q(3n→t+e+ν̄) = Q_n + B(³H)`** | **≈ 9.264 MeV** | **F0** |
| 3n capture kinetics (rate/barrier/σ) | **UNRESOLVED** — energy allowed, rate not predicted | **F0b** |

## 6. Provenance (`FORMULATIONS_PROVENANCE_AUDIT.md`)
| # | result | provenance | correspondence | input_dependency | class |
|---|---|---|---|---|---|
| F0 | `Q(3n→t+e+ν̄) = Q_n + B(t) = 9.264 MeV` | conservation-derived | novel-pathway energy gate | measured masses + B(t) | **C-flagged** |
| F0a | sequential `Σ(steps 1–3) = Q_n+B(t)` (no double-count) | conservation-derived | known-match | measured | **C** |
| F0b | actual `3n` capture rate / probability | unresolved | novel-prediction | density + topology + weak timing | **F** |

**Tally (NP04B):** C 1 · C-flagged 1 · F 1.

*Author attribution: James Christopher Tyndall, Melbourne.*
