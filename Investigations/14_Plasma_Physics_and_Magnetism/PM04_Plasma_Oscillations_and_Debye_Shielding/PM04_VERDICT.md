# PM04 — Verdict: Plasma Oscillations and Debye Shielding

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-04
**Tool:** `pm04_plasma.cpp` — 1-D sheet-model N-body, arrays evolve (the PM03 static sin explicitly
avoided) → `pm04_results.txt` (full run history kept: two FAILs recorded, one closure PASS).
**Pre-commitments:** `RUN_LOG.md` (P2b and P2c gates declared before their runs).

---

## 1. Deciding metrics

| Phase | Gate | Result | Class |
|---|---|---|---|
| P1 | ω_p form <1% | cold ring at **ω = √(4πA n/m_e)**, dev **+0.005%**; A = αℏc (engine `coulomb_identity::k_e_e2`) | **NATIVE mechanics / CONVERGENCE gain** (see §2) |
| P2a | Debye λ <15% (collisionless) | **FAIL, recorded**: λ_fit = 1.62× λ_D (+61.8%); heating ruled out (T_meas = 0.954×T_init), selection bias ruled out | honest FAIL |
| P2b | scaling λ ∝ √T, ratio 2.0±15% | **FAIL, recorded**: ratio 1.071; slope window-dependent → not exponential | honest FAIL |
| P2c | thermostated (declared pre-run) | **PASS**: λ_fit = 2.03e-5 vs λ_D = 2.18e-5 (**−6.8%**), exponential R² = 0.943 | **RECOVERED** |
| P3 | Bohm–Gross C ∈ [2,4] | kλ_D=0.188: **C = 2.83** (PASS, ≈3); kλ_D=0.314: C = 4.23 (out of gate; kinetic k⁴-corrected expectation ≈3.6; heavily damped mode, measurement-limited — reported, not excused) | NATIVE-form / analytic C = 3 = (d+2)/d at d=1 |
| P4 | upper hybrid ±0.5% | ω/√(ω_p²+Ω²) = 0.99984 / 0.99714 / 0.99532 for Ω/ω_p = 0.5/1/2 | NATIVE quadrature additivity (turning channel unsigned — HG-1 disclosed) |

## 2. What is earned and what is not

**Earned (native mechanics):** the restoring push assembled from pairwise Law-III 1/r² occlusion
integrated over sheets (2πAσ_s, distance-independent — no E field anywhere in the chain), producing
SHM at exactly √(4πAn/m); the native re-expression **ω_p = √(4πα ℏc n/m_e)** and
**λ_D = √(k_B T/(4πα ℏc n))** — the "e²/ε₀ group" IS 4παℏc, with e and ε₀ appearing only on
[IMPORTED] comparison lines.

**Not earned (disclosed):** the gain itself. A = αℏc is `coulomb_identity` — laws.hpp labels it
class F (α ≡ k_e e²/ℏc definitional). So PM04 answers its Golden-Rule Q1 honestly: we reproduce the
*form* with the gain entering through the permitted α anchor — a re-expression, not a derivation.
The gain derivation is the same HG-1/EMC02 wall as PM01/PM02. §G-3: proven-within = static/linear
coupling class; re-open = HG-1 closure (FLM14 rotation DOF or lattice wake solver).

## 3. The P2 hunt (FIND→TRACE→GROUND→CORRECT→VERIFY, §D)

1. **Why fail?** Collisionless cloud e-folding 1.62×λ_D, and not exponential (window-dependent
   slope; T×4 moved it only 7%).
2. **Recoverable?** Yes — and it was.
3. **What did the test fail to account for?** The Debye formula's premise is the *thermalized
   Boltzmann response*, not bare collisionless dynamics.
4. **Errored premise:** "a 1-D equal-mass sheet plasma relaxes to thermal equilibrium." It provably
   cannot: crossings are exact pass-throughs — there is no velocity-space relaxation channel at all.
   The apparatus tested phase-mixed Vlasov screening, a different object.
5. **Freedom:** a thermalization channel (Langevin bath at the ensemble temperature).
6. **Accounting:** not a knob — it is exactly TD02's "statistical ensemble" input, which the PROMPT
   itself lists as an upstream dependency. γ_L sets only the equilibration rate, not the screening
   length (stated assumption).
7. **Cascade?** None (apparatus-local premise; no shared root with HG-1).

**Verify:** with the bath, exponential (R²=0.94) at λ_D to −6.8%. **Recovery: RECOVERED.**
Generative finding logged: the *collisionless* 1-D screening anomaly (wider, non-exponential,
T-insensitive) is real physics of phase-mixing — connects to prompt Q3 (Landau damping was also
observed qualitatively as heavy mode damping at kλ_D ≳ 0.3): the collisionless channel is where the
relay picture still owes an account. OPEN, named.

## 4. Answers to the prompt's generative questions

- **Q1:** yes at identity level — the same A = αℏc appears in ω_p, the electropause force, and the
  Coulomb law, because all three route through Law III with the α anchor; whether it is ONE derived
  relay property is exactly HG-1.
- **Q4:** the Bohm–Gross 3 is (d+2)/d at d=1 (adiabatic index of the wave's 1-D compression);
  FD05's 1/3 is 1/d at d=3 — two readings of one dimensionality bookkeeping, not the same number.

## 5. Verdict

> **Prompt completion C** · **Physics class** NATIVE (slab mechanics, quadrature additivity,
> dispersion form) / CONVERGENCE (gain via α anchor, class-F identity disclosed) / OPEN
> (collisionless screening channel; HG-1 gain) · **Recovery** RECOVERED (P2 premise traced and
> closed via TD02 bath; verified −6.8%) · **Cascade root** HG-1 (gain only; the P2 fail was
> apparatus-local, no cascade).
