# TD09 (the freedom ledger of binding), Round 2: the native-list ledger — assessment (2026-10-14)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–2 are the registration, written before `td09_reset_2.cpp` exists. Follows the rewritten prompt of 2026-10-12 (Round 2: bodies p, e, d with d ⇄ 2p + e releasing 1.442246 MeV; statistical weights from the constituents' own circulation states; neutrality fixes the electron density; output T_flip(native), its difference from Saha's 0.0624 MeV and its input sensitivity; no gate against the BBN band).

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` and the kept original claim (P1 ledger = Saha, P2 cold-universe statement, P3 flip temperature defined as n_d/n_p = 1 at equilibrium with the measured η = 6.13×10⁻¹⁰ and X_n/X_p = 1/7, secondary convention 1; the honesty block: convergent route, shared counting); `laws.hpp` (m_e, m_p, ζ(3) = `bridge::release_acoustics::zeta3`, ħ, c). Not read: `TD09_VERDICT_DIRECT_2026-07-26.md`, `td09_freedom_ledger.cpp`, `td09_rerun_2026-07-26.txt`, the 2026-10-10 assessment's body, `td09_reset_1.cpp` and its results. Exposure: the rewritten prompt itself states the earlier outcome (T_flip = 0.062445 MeV at X_n/X_p = 1/7; 0.065 MeV at X_n/X_p = 1).

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | definition | The flip condition is n_d/n_p = 1 with the baryon number n_B = η n_γ(T) (η measured). With free neutrons (the old list {p, n, d}): n_B = n_p + n_n + 2n_d and a fixed free ratio X_n/X_p; with the native list there is no free neutron and the baryon number is n_B = n_p + 2n_d. |
| D2 | native counting | Bodies p, e, d (d ⇄ 2p + e). Baryon count of d is 2 (two protons inside), one electron inside. Neutrality of the whole system (electrons equal protons in total): n_e,free + n_d = n_p,free + 2n_d, so n_e,free = n_p,free + n_d. At the flip n_d = n_p: n_e = 2n_p, and n_B = 3n_p. |
| D3 | equilibrium relation | Saha for d ⇄ 2p + e in natural units (ħ = c = k_B = 1): n_d/(n_p² n_e) = (g_d/(g_p² g_e)) (m_d/(m_p² m_e))^{3/2} (2π/T)³ e^{B/T}, with m_d = 2m_p + m_e − B (the native mass of the built list), B = 1.442246 MeV (prompt). The photon density n_γ = 2ζ(3)T³/π². |
| D4 | weights | The prompt asks for g_e, g_p from their circulation states (g_e = g_p = 2: two circulation hands) and g_d from the built deuteron's hand count, "to be stated natively". No native hand count of the built deuteron is given in the prompt or in canon; the standard spin multiplicity 3 is an imported label and is not used as the native value. Registered: g_d is an **input scanned over {1, 2, 3, 4, 6, 8}** (8 = 2 × 2 × 2 hands of p, p, e as the unconstrained count; 3 shown as the standard value for comparison), and the result is reported as T_flip(g_d), with its sensitivity d T_flip/d ln g_d. No single value is claimed as native. |
| D5 | validation | The old route (list {p, n, d}, B = 2.224573 MeV, g_d = 3, g_p = g_n = 2, X_n/X_p = 1/7 and 1) is implemented here from the definition and must give the prompt's 0.062445 MeV (1e-3) and 0.065 MeV (rounded) before the native number is read. |
| D6 | labels | No gate against the BBN band (framework-dependent). The result is COMPUTED; convergent with equilibrium counting by construction (the honesty block of the original claim stands). |
No downgrade is made on agreement grounds.

## 2. Registered quantities (fixed before the run)
Units MeV. Constants: m_p, m_e from `sdt::laws::measured` (kg → MeV via c² and the exact joule–MeV relation); m_n = m_p + m_e + 0.782347 MeV (the engine's neutron decay energy relation; the prompt's native "free neutron's own +0.782 MeV"); η = 6.13×10⁻¹⁰; B_old = 2.224573, B_native = 1.442246 (both from the prompt). Validation V1: the old route's T_flip at X_n/X_p = 1/7 and 1. Output: T_flip(native) for each g_d, the difference from the old value, the sensitivity to η (T_flip at η × 2 and η / 2) and to B_native ± 0.001 MeV. Bisection on T in [0.01, 1] MeV to 10⁻¹².
**Expected landing (hand estimate before registering).** Old route: 0.0624 MeV and 0.065 MeV (the prompt). Native: the equation reduces to B/T = ln[...] with ln terms of order 70–80, T_flip ≈ B_native/ (about 22–24) ≈ 0.06 MeV, within 0.005 MeV of the old value for every g_d (ln g_d enters as a few tenths of nats out of ~23): the native list does not move the flip by more than about 5%; discrimination from Saha is therefore weak.

## 3. Attempt 1 and Amendment 1 (registered before any native result was read)
**Attempt 1 (kept: `td09_reset_2_attempt1_V1_baryon_counting.txt`).** Validation V1 **not met**: with the baryon number counted as n_B = n_p + n_n + 2n_d (D1), the old route gave T_flip = 0.060648 MeV at X_n/X_p = 1/7 and 0.063740 MeV at X_n/X_p = 1, against the prompt's 0.062445 and 0.065. The run stopped before any native number was computed (G0).
**Diagnosis.** The two differences (−2.9%, −1.9%) are what a change of the baryon count by a factor (1 + r + 2)/(1 + r) = 22/8 and 4/2 would produce (+1.01 and +0.69 nats in ln n_n, i.e. shifts of +0.0017 and +0.0013 MeV through T²/B per nat): the earlier convention counts the free nucleons only, n_B = n_p + n_n, with the deuterons outside the baryon sum. That is a statement about the earlier convention read off the two known answers (two numbers, one convention change, no free parameter), not a fit.
**Amendment 1.** (i) The old route uses n_B = n_p + n_n (free-nucleon convention); V1 is re-run with the same tolerances (1e-3 at 1/7; 1% at X = 1, the prompt's rounded value). (ii) The native route is evaluated under both conventions, registered now: **C1** free baryons, n_B = n_p (the convention that must reproduce V1, applied by the same rule) and **C2** full count n_B = n_p + 2n_d = 3n_p (the original reading of D2); the native result is reported for both and the difference between them is a stated systematic of the counting convention. Everything else (g_d scan, η and B sensitivities, no gate) is unchanged.

## 4. Results (attempt 2; COMPUTED; `td09_reset_2.cpp`, output `td09_reset_2_results.txt`; V1 met)
**Validation V1 (free-nucleon convention, Amendment 1).** Old list {p, n, d}: T_flip = **0.062445 MeV** at X_n/X_p = 1/7 (prompt 0.062445) and **0.065092 MeV** at X_n/X_p = 1 (prompt 0.065): met.
**Native list {p, e, d}.** Convention C1 (free baryons n_B = n_p, the convention that reproduces V1): T_flip = 0.023817 / 0.024108 / **0.024281** / 0.024406 / 0.024583 / 0.024711 MeV for g_d = 1 / 2 / **3** / 4 / 6 / 8. Convention C2 (full count n_B = 3n_p): 0.022942 / 0.023211 / 0.023371 / 0.023486 / 0.023651 / 0.023769 MeV. **Shift from the old value 0.062445 MeV: −60.4% to −61.9% (C1), −61.9% to −63.3% (C2).** Input sensitivities (g_d = 3, C1): dT_flip/d ln g_d = 4.4×10⁻⁴ MeV per nat (1.8%); η×2 → +2.5%, η/2 → −2.4%; B_native ± 0.001 MeV → ±0.073%. The counting convention (C1 against C2) is a 3.7% systematic.
**Why the shift is large.** The native equation is a three-body equilibrium (2p + e): the phase-space factor carries (2π/T)³ and the density product n_p n_e against (2π/T)^{3/2} and n_n in the two-body route, and B falls from 2.2246 to 1.4422 MeV. The flip condition B/T ≈ ln[...] has about 59 nats in the native route against about 36 in the old: T_flip ≈ 1.44/59 = 0.0244 MeV against 2.22/36 = 0.0624 MeV. The statistical weight, the density and the binding are minor against the change of list.
**Landing against the hand estimate: not held.** I registered a native value near 0.06 MeV within about 5% of the old (an estimate from the size of ln g_d only); the three-body structure (D3) moves it by −61%, a factor 2.6. The sign and size of that move are the result.
**Reading, with limits.** The native-list ledger gives a different T_flip from the Saha route, as the rewritten prompt expected ("potentially discriminating"): −61% is far outside every input sensitivity above. It is not compared with the BBN band [0.035, 0.17] MeV (framework-dependent; the native 0.024 MeV lies below the band's lower edge, which is stated, not tested). Three conditions bound what it means: (i) it holds only if the nucleus list {2p, e} is the framework's and the equilibrium is a three-body (2p + e) Saha; (ii) it needs g_d from a native hand count (scanned, 1.8% effect); (iii) the comparison with an observed assembly requires an SDT-native assembly history without expansion (owed).

## 5. Grades
| Item | Grade |
|---|---|
| V1 (old route reproduces 0.062445 and 0.065) | **met after the baryon-counting amendment** |
| T_flip(native), g_d = 3, C1 | **0.02428 MeV, COMPUTED** (0.0238–0.0247 over g_d; C2 0.0234) |
| Difference from Saha's old-list value | **−61% (convergence with Saha broken by the change of list)** |
| Discrimination | **possible in principle; no observable compares it** (no native assembly history) |
| Gate against the BBN band | **none (registered)** |
| Label | **COMPUTED; convergent with equilibrium counting for a given list** |

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
