# Spatial Displacement Theory — theoretical model (current)

**J. C. Harvey, Melbourne. 2026-08-13.**  
Single-source numbers: `Engine/include/sdt/laws.hpp`. Companion for people: `SDT_FOR_PEOPLE.md`. LLM spine: `SDT_LLM_UPTAKE.md`. Cycle arithmetic: `Theory/07_Cyclic_Reiteration.md`.

This file is the **total model as it stands**: constitution, identities, the Shapiro–Wien chain, the nuclear grammar, and the ledger of open and excluded work. It is not a substitute for gated assessments.

---

## 1. Constitution

**Primitives.** Space = gap-free spation lattice, nearest-neighbour relay, tick `c = ℓ_P / t_P`. Matter = lasting displacement volume (vortex). Movement = circulation + translation, one budget. Now = the tick.

**Force.** Occluded convergence only. No attraction.

```
F = (π/4) P_eff R₁² R₂² / r²
```

Coulomb, gravity, nuclear: same form, domain `P_eff`.

**Scales.** The lattice cell is `ℓ_P` — Axiom R1, the one dimensional seed (FLM06). Time is that cell divided by the relay rate. `c` is the SI definition of that rate; `k_B` converts kelvin to energy; `e` converts charge units. Action, electron mass, and proton mass are one mass/action seat (FLM13). `α` is hydrogen’s ground-state koppa rung `k_H = 1/α` (PPT02, APS05), same ladder as the Sun. `T_CMB` is the FIRAS reading of the bath now — a clock, not a constant of nature. `a_0` is the length that seat form sits on. `sdt::laws::measured` stores CODATA/FIRAS numbers so the engine can compute.

**Prohibited inputs.** G, M as fundamentals; dark matter/energy; ΛCDM; quarks/gluons; ψ as a primitive; fields as stuff; inflaton; a first moment of time.

**Certification.** DERIVED · COMPUTED · CALIBRATED(n) · OBSERVED · PENDING · EXCLUDED · WITHDRAWN. Correspondence (`GM = c²ϟ`) is not provenance.

---

## 2. Six laws

| | Namespace | Load-bearing identity |
|---|---|---|
| I | `law_I` | `Φ = N ε`, `N = R_CMB/ℓ_P`, `P_conv = Φ/ℓ_P³ = N u_CMB`. Inner shells cancel (T1). `R_CMB` class X. |
| II | `law_II` | Release cascade. Stellar domain `r = √(L / 4π F_CMB)`. Sun ≈ 20 800 AU. |
| III | `law_III` | Occlusion law above. `P_eff` atomic: CALIBRATED (hydrogen). `f = P_eff/P_conv` class E until `R_CMB` is derived. |
| IV | `law_IV` | Inertial mass = reorganisation cost of throughput. `m_inert = m_grav` from the same `V_disp`. |
| V | `law_V` | `v_circ² + v² = c²`. SR bookkeeping. Photon: `v = c`. Rest: `v_circ = c`. |
| VI | `law_VI` | W=1 electron (unknot), W=3 proton (trefoil). W=2 not lasting. W+1 conjecture on `R_p`. |

**Planck-face pressure.** Baryons exclude spheres `r = ℓ_P/2`. Throughput on each face: `Φ = R_CMB u_CMB ℓ_P²`. Gravity is that pressure shadowed. EMC01: `F ∝ P_conv V₁ V₂ / (ℓ_P² r²)`. `koppa_per_baryon = ℓ_P² c m_p / ℏ` — C-flagged (CODATA `ℓ_P` still carries conventional G).

---

## 3. Koppa and depth (no G)

```
k = c/v
z = 1/k² = (v/c)² = ϟ/r
ϟ = v² R / c² = R/k²
v = c √(ϟ/r) = c √z
z k² = 1
```

`GM = c²ϟ` is algebra. Inputs are measured `v`, `R`.

Same law: Earth orbit, Mercury, hydrogen `v = αc` ⇒ `k_H = 1/α`, `ϟ_H = α² a₀ = r_e` (exact).

---

## 4. Variable `c` — one `z`

```
ℓ_P(r)  = ℓ_P,∞ (1 − z)
c_far   = c_∞ (1 − z)²          hop and tick  (GOM22)
dτ/dt   = (1 − z)
z_spec  = z_emit − z_obs
Δt      = ∫ dl/c_far − ∫ dl/c_∞
```

`c(1−z)` alone: **falsified** (exactly half Shapiro). Factor 2 is DERIVED, not inserted. Solar C1: `z = ϟ/R = 2.123×10⁻⁶`, 0.03%. Earth’s `c` is a rung: `c_∞ ≈ c + 105 m/s` (galactic floor `z = 3.5×10⁻⁷`). First-order match to Schwarzschild `c(1−2z)` is correspondence. Second-order fork OPEN (wall at `ϟ` vs `r_s`).

---

## 5. Temperature, pressure, and far-frame speed (one ladder)

```
1 + z  = T / T_CMB = (P / P_now)^{1/4} = 1 / (1 − z_depth)
N      = T / T_CMB = λ_now / λ
P      = N⁴ P_now
c_far  = c / N²
```

`T_CMB = 2.7255 K` OBSERVED (FIRAS). `z_release = 1089` OBSERVED; `T_release = 2970.8 K` COMPUTED. Wien `b` DERIVED (B07).

---

## 6. Lifecycle (COMPUTED chain)

Shapiro measures the solar pressure-speed profile of excluded Planck spheres, shell by shell. Reverse-map: photosphere as through-going-speed **0**, Earth orbit as match to **c**. Weak-field SI: `c_far(R_☉) = c − 1273 m/s`, `c_far(1 AU) = c − 6 m/s`. Same identities at cosmological `N` are the ladder.

| Peak | Band | `N` | `c_far` | Role |
|---|---|---|---|---|
| 1.063 mm | microwave | 1 | `c` | now |
| 975 nm | near-IR | 1090 | 252 m/s | FIRAS Clearing; SM last-scattering band |
| 750–380 nm | visible | 1418–2798 | 149–38 m/s | behind the wall |
| 100 nm | UV | 1.06×10⁴ | 2.65 m/s | behind |
| 1.21 pm | gamma | 8.76×10⁸ | 3.9×10⁻¹⁰ m/s | pair threshold |
| 4.30 fm | hard gamma | 2.48×10¹¹ | 4.9×10⁻¹⁵ m/s | `P = P_eff`; stop-death |
| `ℓ_P` | — | 6.58×10³¹ | → 0 | lattice |

Down from now: radio → ELF → `λ = R_CMB` (static; +99.5 octaves). Heat death: `N → 0`, `P → 0`, Law III gravity off, matter expands, structure breaks. Recharge climbs until `c_far → 0`. Clearing = depinning of the IR radiation wall. `c/√3` is the fluid ceiling on the way down (FD05), not the recharge target.

**PENDING:** fire-time / T-floor amplitude. **OPEN:** `R_CMB` from first principles. **EXCLUDED:** CR08 exponential `d(z)`; CR12 pure `z³` SN distances; CR15 ionisation-at-`N=1100` as the CMB.

Elapsed count since this Clearing is a reading (~48 Gyr BAO; 100.7 Gyr on engine `R_CMB/c`).

---

## 7. Relativity as budget

```
v_circ² + v² = c²
γ = 1/√(1 − v²/c²)
E₀ = m c²
E² = (p c)² + (m c²)²
```

Nothing exceeds `c` in translation. Phase speed inside a proton c-boundary may exceed `c` (`v(R_p) ≈ 1.83 c`); that is circulation, not a signal.

---

## 8. Particles, atoms, nuclei

**W=1** electron. **W=3** proton. Neutrino: open W=0, `μ_ν = 0` (PPT04). Neutron = proton + internal electron (structure; magnitude OPEN). `m_p/m_e = 6π⁵` analytic in-engine (−0.0019%); PPT17 closes the tube-volume assignment as a shared-input construction, not an independent prediction.

**Hydrogen** = proton **centre**, not a packed seat. **He-4 / He⁺** = α **centre**. Seats = D/T around the α from Li-6.

Lamb: H 1057.845 MHz, He⁺ 14041.13 MHz — OBSERVED stickers. Not derived from each other. Native 1051.8 **deleted**.

**Grammar** (Z ≥ 2, He-4 core): `n_t = A − 2Z`, `n_d = 3Z − A − 2`. EC isotopes: He-3 core alternate. No free neutrons in stable nuclei. Packer `dnn = 1.45 fm` frozen. Fission is flay, not liquid-drop split (NP35). Contact MeV UNDERDETERMINED.

---

## 9. Cosmology (operating epoch)

No expansion. Redshift = emission depth `z = ϟ/r` ⊕ propagation squeeze, octaves `1+z = 2^Δn` (CMB at 10.10). H₀ “tension” = one number asked to carry two mechanisms. `P(z) = P_conv (1+z)⁴` is shared-input with a radiation-era reading — not independent evidence.

Dark energy: no row. SN `z³` distance: EXCLUDED (CR12). Tired light: EXCLUDED (CR07, sharp QSO lines).

---

## 10. Ledger (do not launder)

| Item | Status |
|---|---|
| Shapiro `c_far = c(1−z)²`; C1 solar redshift | DERIVED / 0.03% |
| Wien reverse-map MW → IR → gamma `c_far→0` | COMPUTED |
| Heat death = Law III at `P→0` | COMPUTED implication |
| Cycle fire-time | PENDING |
| `R_CMB`, H₀ from first principles | OPEN (CR05 H₀ retracted) |
| Lamb frequencies | OBSERVED |
| Lamb native extraction | WITHDRAWN |
| SN `z³` | EXCLUDED |
| GD05 native rotation shape | OPEN (mock success voided) |
| `P_eff` magnitude | CALIBRATED |
| `koppa_per_baryon` Law-III origin without `ℓ_P↔G` | PARKED |
| E51 W=1 torus v_P/v_T as a formula for α | unpaid experiment — not the origin of 137; 137 is k_H |
| FLM14 residence | UNPAID |

---

## 11. Pointers

| Need | Open |
|---|---|
| Numbers | `Engine/include/sdt/laws.hpp` |
| Cycle chain | `Theory/07_Cyclic_Reiteration.md` |
| Rules | `Theory/00_Ruleset.md` |
| Depth | `Papers/Depth_Closure_Theorem/01_THEOREM.md` |
| People | `Papers/SDT_FOR_PEOPLE.md` |
| LLM spine | `Papers/SDT_LLM_UPTAKE.md` |
| Lifecycle (web) | `Release/HTML_SDT_Website/universe-lifecycle.html` |
| Benchmarks | `Benchmarks/B01_B25/benchmarks_suite.cpp` |
