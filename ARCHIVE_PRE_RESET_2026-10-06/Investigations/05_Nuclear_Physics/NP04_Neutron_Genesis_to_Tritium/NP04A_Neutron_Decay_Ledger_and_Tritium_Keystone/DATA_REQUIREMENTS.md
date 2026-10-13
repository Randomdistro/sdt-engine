# NP04A — Data Requirements *(decay ledger + tritium keystone)*

*(Single copy — no duplication. The `3n→t` genesis inputs `Q(3n)` and the 3n-kinetics unknown live in NP04B, not here.)*

Inputs grouped by `input_dependency` (per `Audits/FORMULATIONS_PROVENANCE_AUDIT.md`). The keystone (`Q_β(³H)`) and the conservation spine consume **only measured masses + binding energies** — no fitted scale — which is why they reach class **C**. Stage A's link energy and Stage F's binding are the only `calibrated-target` consumers.

## 1. `primitive-derivation basis` (CODATA, `sdt::laws::measured`)
| symbol | value | used by |
|---|---|---|
| `c` | 299 792 458 m/s | mass↔energy, circulation freq |
| `ℏ` | 1.054 571 817e-34 J·s | `R_p`, `r_e`, `λ_C`, barrier |
| `α` | 7.297 352 5693e-3 | `a₀ = r_e/α²` (Stage G) |
| `m_e` | 9.109 383 7015e-31 kg | masses |

## 2. `measured-observable` (external; compared/consumed, never fitted)
| quantity | value | stage |
|---|---|---|
| `m_n` | 939.5654 MeV (1.674 927 498e-27 kg) | A/B |
| `m_p` | 938.2720 MeV (1.672 621 924e-27 kg) | A/B/E |
| `m_e` | 0.5110 MeV | A/B |
| `Q_n = m_n−m_p−m_e` | **0.7823 MeV** (meas 782.3 keV) | A/B/H |
| `B(²H)` deuteron | 2.224 MeV (the contact pin) | F |
| `B(³H)` triton | 8.482 MeV | F/H |
| `B(³He)` helion | 7.718 MeV | H |
| `Q_β(³H)` | 18.591 keV; `t½ = 12.32 yr` | H |
| `τ_n` | bottle 877.75 s / beam 887.7 s (Δ≈9.95 s) | C |
| `μ_p, μ_n` | 2.7928, −1.9130 μ_N | A (P3) |
| `λ_C,p` | 1.321 410e-15 m | C |
| `r_e` | 2.8179e-15 m | G |
| `a_0` | 5.2918e-11 m | G |
| `R_excl,p / R_excl,e` | 3.525e-20 / 2.878e-21 (`law_IV` literals) | D |

## 3. `calibrated-target` (class E — fitted scale)
| symbol | value | role |
|---|---|---|
| `k_occ` | `B_deuteron` = 2.224 MeV/contact | triton binding (Stage F) |
| `P_eff` | 5.225e31 Pa | Stage-A link-energy attempt (if computed; stays E) |

## 4. `unresolved` (class F — the honesty targets)
| quantity | status |
|---|---|
| `a_p/a_e = 11.445` | **to be derived** from (2,3)-vs-(1,1) knot equilibrium; numerology `(3/2)^{3/2}·10³−1` stays F until then |
| absolute `τ_n` | barrier inferred from `τ`, not predicted |

> Frozen, must NOT be modified (Stage-E gate verifies): `laws.hpp::winding` (`R_p_predicted`, `W_eff`, `g_proton`) and `nuclear.hpp` (`alpha_grammar`, the triton as alpha-invalid primitive).
