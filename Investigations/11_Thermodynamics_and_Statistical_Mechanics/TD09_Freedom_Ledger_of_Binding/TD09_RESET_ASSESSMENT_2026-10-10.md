# TD09 — Freedom ledger of binding: reset record (2026-10-10)

**Protocol:** `Investigations/RESET_2026-10-06/PROTOCOL.md`. Session sdt-engine-e0.

**Read:**
- `PROMPT.md`: its gates were committed before the tool and are carried unchanged.
- `laws.hpp` measured masses and `release_acoustics::zeta3`.
- `graph_v2.json`: layer 0, no suppliers, no dependents.

**Not opened:** `TD09_VERDICT_DIRECT_2026-07-26.md`, `td09_rerun_2026-07-26.txt`, `td09_freedom_ledger.cpp`.

## Registration details fixed before the instrument (the prompt leaves these open)
- **Ratio definition.** n_d/n_p = n_n·S(T), where S(T) = (g_d/(g_p g_n))·(m_d/(m_p m_n))^{3/2}·(2πħ²/kT)^{3/2}·e^{E_b/kT} and g = 3, 2, 2.
  - **Primary:** n_n = X_n·n_b with X_n/X_p = 1/7, taken as the undepleted free-neutron density (the bottleneck estimate).
  - **Sensitivity:** X_n/X_p = 1.

  With depletion included, n_d/n_p = 1 is unreachable at X_n/X_p = 1/7, because the neutrons run out first. That is stated, not used.
- **Densities.** n_b = η·n_γ, n_γ = (2ζ(3)/π²)(kT/ħc)³, η = 6.13e-10 (MEASURED-INPUT, as the prompt specifies).
- **E_b = 2.224573 MeV** (MEASURED-INPUT). Masses from `measured`.
- **Premise note (2026-10-07 rulings).** Counting the neutron as one free body is a counting convention; the native neutron is p + e (NP14). Binding is read as mass defect, and E_b enters as the movement released to the bath. No potential-energy step is used.
- **P1 identity:**
  - **ledger route:** Δfreedom(T) = E_b/kT − Δln W_config, with Δln W_config = ln(n_d/n_p) − ln(n_n·S₀(T)), where S₀ is S without the exponential;
  - **Saha route:** bisection on n_d/n_p = 1.

  The two T_flip values must agree to 1e-12.
- **Gate (prompt):** G3-PASS if T_flip ∈ [0.035, 0.17] MeV.

**Validations:**
- V1: n_γ at 2.7255 K against 4.11e8 m⁻³ (known, 1e-3).
- V2: S(T) dimensional check by unit scaling.
- V3: the bisection on a constructed function with a known root.

## Run and results
- Instrument: `td09_reset_1.cpp`; output in `td09_reset_1_results.txt`.
- The first build failed to compile: `zeta3` sits in `bridge::release_acoustics`. Corrected; no output was produced before the fix.
- Single pass. Validations V1–V3 met.

**P2 (statement).** At 300 K:
- E_b/kT = 8.605e7 nats;
- configurational cost = 57.67 nats (the prompt's rough estimate was about 30).

Binding is freedom-positive by about 10⁷ in a cold bath.

**P1 + P3.**

| X_n/X_p | T_flip, Saha route (MeV) | T_flip, ledger route (MeV) | routes agree | E_b/kT = cost (nats) | ln(1/η) | G3 |
|---|---|---|---|---|---|---|
| 1/7 (primary) | **0.062445** | 0.062445 | 3e-16 | 35.625 | 21.213 | **PASS** |
| 1 (sensitivity) | 0.065092 | 0.065092 | 0 | 34.176 | 21.213 | PASS |

T_flip = 7.25e8 K. This sits inside the registered band [0.035, 0.17] MeV, and inside the measured bottleneck interval of 0.06–0.09 MeV.

**Labels (P4, mandatory).**
- The flip equation is algebraically Saha: **convergent route, shared counting; it cannot discriminate against standard equilibrium thermodynamics.**
- **Delete test:** remove the freedom narration and the number stands; remove the counting and nothing stands.
- The native content is the reading: matter binds where the route ledger nets positive, and ln(1/η) = 21.2 nats of photon-bath route surplus delays the first assembly to 0.062 MeV.
- TD01's debt is re-posed, not paid: show that W climbs under the relay rule alone.

**Grade: G4** (consistent within the registered band; convergent; not discriminating).

**Downstream:** none in the graph.

## Comparison with the archived record
Deferred.
