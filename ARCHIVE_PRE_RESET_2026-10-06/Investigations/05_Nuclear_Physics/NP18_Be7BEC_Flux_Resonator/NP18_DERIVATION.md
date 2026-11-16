# NP18 — Derivation: resonant inverse-EC σ, the N-vs-N² law, and the λ_ν-span condition

> **Author:** derivation executed per J. C. Harvey NP18 SPEC. **Run date:** 2026-07-01.
> **Engine:** constants mirror `sdt/laws.hpp::measured`; grammar mirrors `sdt/nuclear.hpp`.
> **Discipline:** every step tagged DERIVED / COMPUTED / ASSUMED / MEASURED-INPUT / OBSERVED-TARGET.
> No G / M / GM / **G_F** enters the SDT chain. 478 keV is the Li-7\* de-excitation GAMMA.

---

## 0. The grammar selection rule (Phase 0) — DERIVED, exact

`alpha_grammar(Z,A)`: n_d = 3Z − A − 2, n_t = A − 2Z (nuclear.hpp:131).

| Nuclide | Z | A | n_d | n_t | valid | reading |
|---------|---|---|-----|-----|-------|---------|
| Be-7 | 4 | 7 | 3 | **−1** | False | n_t<0 → **underflow** (below constructable lattice) = EC-cocked |
| Li-7 | 3 | 7 | 0 | 1 | True | on-lattice, clean |

EC grammar vector (Δn_d, Δn_t) = (0−3, 1−(−1)) = **(−3, +2)** — a *single* step Be-7 → Li-7. **DERIVED, integer-exact.**

**Falsifiable selection rule (stated as such):** a good resonant-capture substrate must sit at n_t<0 underflow, reachable to the on-lattice wedge by one EC grammar vector. Zero free parameters. Be-7 satisfies it exactly. **Physics class: NATIVE.**

---

## 1. Resonant inverse-EC cross-section σ_inc (Phase 1)

**Step 1 — the neutrino yardstick (DERIVED).** At the ground-state line E_ν = 0.862 MeV (MEASURED-INPUT / OBSERVED-TARGET, NNDC/Borexino):

  λ̄_ν = ħc / E_ν = 2.289×10⁻¹³ m  →  λ_ν = 2π λ̄_ν = 1.438×10⁻¹² m.

**Step 2 — the resonance ceiling (DERIVED, G_F-free).** On resonance, a cross-section is capped by the wavelength, not by the coupling:

  σ_peak = λ̄² · g_spin · (Γ_in Γ_out)/((Γ/2)²).

For a single dominant channel the branching product → 4. The spin weight g_spin = (2J\*+1)/((2J_Li+1)(2J_ν+1)) = 4/8 = 0.5 from the measured spins (Li-7 3/2⁻, ν 1/2, Be-7 level 3/2⁻). Thus

  σ_peak = λ̄² · 0.5 · 4 = 1.048×10⁻²⁵ m².  **DERIVED.**

*Independence check:* σ_peak contains **no G_F** — only ħ, c, E_ν, and integer spins. G_F would enter only through the *width*, never the on-resonance peak. This is the standard resonance ceiling (Breit–Wigner at peak), used here without importing the weak coupling.

**Step 3 — the EC width from the measured half-life (DERIVED, no G_F).**

  Γ_EC = ħ · (ln2 / t_½),  t_½ = 53.22 d = 4.598×10⁶ s (MEASURED-INPUT)
  Γ_EC = 1.590×10⁻⁴¹ J = 9.92×10⁻²³ eV.  **DERIVED.**

The width is read off the *measured decay rate*, not computed from G_F. This is the honest, borrow-free route.

**Step 4 — resonance-averaged σ (DERIVED, with one ASSUMED bandwidth).** A real drive/target has a finite linewidth dE ≫ Γ_EC, so the *averaged* cross-section is suppressed:

  σ_avg = σ_peak · (π/2) · (Γ_EC / dE),  dE = 1 eV (**ASSUMED** cold-trap linewidth scale)
  σ_avg = 1.633×10⁻⁴⁷ m².

**FLAGGED HONESTLY:** σ_avg scales inversely with the ASSUMED dE. The sanity gate (σ_avg/σ_weak_ref = 0.16, within the loose resonance band) therefore has a soft input. **This dE choice does NOT touch the Phase-3 result** — the span gate depends only on λ_ν and L, both hard. σ_avg is used to set the *scale* of R_inc, not the fork.

**Step 5 — incoherent per-nucleus rate (DERIVED).** R_inc(per Be-7) = σ_avg · Φ_ν = 1.63×10⁻²⁹ s⁻¹ at a reactor-class Φ_ν = 10¹⁸ m⁻²s⁻¹ (**ASSUMED** drive). Units checked: [m²]·[m⁻²s⁻¹] = s⁻¹. ✓

---

## 2. The N-vs-N² enhancement law (Phase 2) — DERIVED, limits exact

**Explicit amplitude sum (the anti-hand-wave form).** For N atoms in one wavefunction with per-atom amplitude a:

  incoherent rate  ∝  Σᵢ |a|²      = N|a|²      (independent atoms, rates add)
  coherent   rate  ∝  |Σᵢ a|² · span(ρ) = N²|a|² · span   (amplitudes add, then squared)

Define the multiplier over the single-atom incoherent rate:

  **K_coh(N, ρ) = N + (N² − N)·span(ρ)**,  span(ρ) = min(ρ_coh, 1),  ρ_coh = λ_ν / L.

**Load-bearing limit checks (asserted in code, all pass EXACTLY):**

| Limit | K_coh | recovers |
|-------|-------|----------|
| N = 1 (any ρ) | 1 | single-atom incoherent |
| ρ → 0 (any N) | N | incoherent N-atom baseline |
| ρ ≥ 1 (full span) | N² | collective coherent (to <1%) |

The crossover is shown in the rate table, not hidden. A model that fails the incoherent limit would be wrong regardless of the headline; both limits are exact here. **DERIVED.**

---

## 3. The λ_ν-span condition (Phase 3) — the decisive geometry

**ρ_coh = λ_ν / L**, with L = (N/n)^{1/3} the BEC linear size.

| | value |
|---|---|
| λ_ν (0.862 MeV) | 1.438×10⁻¹² m |
| smallest tabletop BEC L (N=10⁴, n=10¹⁵ cm⁻³) | 2.15×10⁻⁶ m |
| **best ρ_coh over the whole tabletop grid** | **6.68×10⁻⁷** |

**Result: ρ_coh < 1 by ~6–7 orders of magnitude for every achievable tabletop BEC** (N=10⁴–10⁷, n=10¹³–10¹⁵ cm⁻³). The 0.862 MeV neutrino wavelength (∼pm) is a million times smaller than the condensate (∼µm). **λ_ν cannot span the condensate.**

Consequence: the *whole-condensate* N² enhancement is **geometrically unavailable** at BEC scale. This is exactly the §8 honest boundary: CEνNS proves N² coherence only where q·R ≲ 1 — over nucleons *within one nucleus*. Extending it across a whole BEC needs λ_ν ⊇ BEC, which fails here. **Decision: DEFER (T3).** Not a fit, not a fudge — a hard geometric verdict from measured numbers.

---

## 4. The read-out (Phase 3 signal side) — PENDING / DEFER

The per-capture magnetisation step B_step (the 2s shallow-seat flux quantum) requires the flux-per-atom absolute from **NP19 / NP20**, both still SPEC (BLOCKER-01). Therefore B_sig(N\*)=B_floor **cannot be solved to an absolute N\*** in this run. An illustrative crossing was shown with a single CALIBRATED(1) placeholder B_step=10⁻²⁴ T, labelled illustrative-only; it is not a result. **The absolute N\* is OWED to NP19/NP20.**

---

## 5. Stripped-Be-7 fork (Phase 4) — CONVERGENCE proxy, absolute OWED

Seat-depth proxy (dimensionless, standard hydrogenic/Slater sizes, no fitted SDT coefficient):

  r_2s ≈ (2²/Z_eff,2s)·a₀ = 3.18 a₀ (shallow, flux-active);  r_1s ≈ (1²/Z_eff,1s)·a₀ = 0.27 a₀ (deep K).

Linear ratio **11.75×**, volume ratio **1621×** — both ≥ the pre-committed 3× fork threshold. The deep-K vs shallow-2s signatures are distinguishable by seat depth. Caveat: the absolute B_step and the flux-vs-size exponent are PENDING NP19/NP20. **The fork is callable in shape; the absolute is owed.**

---

## DERIVED vs ASSUMED — line-by-line ledger

| Quantity | Value | Tag |
|----------|-------|-----|
| grammar (3,−1)→(0,1), vector (−3,+2) | exact | **DERIVED** (nuclear.hpp) |
| λ̄_ν, λ_ν | 2.289e−13 / 1.438e−12 m | **DERIVED** (ħ,c,E_ν) |
| g_spin | 0.5 | **DERIVED** (measured spins) |
| σ_peak | 1.048e−25 m² | **DERIVED** (G_F-free ceiling) |
| Γ_EC | 1.590e−41 J | **DERIVED** (measured t_½) |
| dE (bandwidth) | 1 eV | **ASSUMED** (soft; scales σ_avg only) |
| σ_avg | 1.633e−47 m² | **DERIVED** (given dE) |
| Φ_ν | 1e18 m⁻²s⁻¹ | **ASSUMED** (drive) |
| R_inc(per) | 1.63e−29 s⁻¹ | **DERIVED** |
| K_coh(N,ρ) law + limits | exact | **DERIVED** |
| ρ_coh best (tabletop) | 6.68e−7 | **COMPUTED** — decisive |
| B_step absolute | — | **PENDING** (NP19/NP20) |
| seat-size fork ratio | 11.75× / 1621× | **COMPUTED** (Slater proxy) |
| E_ν lines, 478 keV gamma, t_½, BEC N/n/L, SQUID fT, CEνNS N², G_F | — | **MEASURED-INPUT / OBSERVED-TARGET** |

---

*NP18 · derivation · the selection rule is NATIVE and exact; the tabletop cross-condensate N² is geometrically DEFERRED; the absolute read-out is OWED to NP19/NP20.*
