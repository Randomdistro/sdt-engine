# SDT Common Spaz Metric — run 2 (2026-10-31): full audit of the 2026-10-15…31 session stream

Author: James Christopher Tyndall, Melbourne. Executed directly in the main session (GATEWAY_PROCEDURAL §3.5).

## Scope

Every topic raised in the session stream, tabulated in the Common Spaz Metric form: exact
exponent/rank bookkeeping, unit-change vs physical-change separation, one label per number.
`Hubble/` is superseded by the variable-c investigation and is neither cited nor edited.
Canon (`Engine/include/sdt/`, `Laws/`) is read only. SM/QM/GR forms appear only as
comparators, never as drivers. The first Spaz run (`Projects/sdt-investigations/…/SDT_Common_Spaz_Metric_2026-10-22_2/`)
is not in this working tree; its stated results are cross-checks (marked RUN-1), not inputs.

## Pre-registered criteria (written before any tool exists)

| WS | Item | Instrument validation (known answer) | Criterion / rejection class |
|---|---|---|---|
| W1 | Pasted electron self-energy and Bohr radius | recompute ħc/r_e = 70.02 MeV | each claimed step is REPRODUCED if recomputation agrees to 1e-6 relative, otherwise NOT REPRODUCED |
| W2 | Gemini fault lines (arithmetic, β=GM identity, cap vs projected solid angle, icosahedral contacts, polytope counts) | projected solid angle analytic vs 2-D quadrature agree to 1e-9 | each claim REPRODUCED / NOT REPRODUCED; icosahedral neighbour contact exists only if edge/circumradius ≤ 1 |
| W3 | Apsidal advance | Kepler 1/r²: |advance| < 1e-8 rad/orbit; Law V response: ratio to 6πϟ/(a(1−e²)) = 1/6 ± 0.5 %; static λ=6 term: 1 ± 0.5 % | required static coefficient λ_req (with Law V on) reported; expectation registered: λ_req = 5 ± 0.1. Any other value is the finding |
| W3b | GOM04 c-closure | — | residual is "resolved" only if smaller than 1σ propagated from δφ = 42.98 ± 0.04″/cy; otherwise unresolved |
| W4 | Γ_ep = k_e e² m_p R_p (1+z)/ħ² | reduce to 4α(1+z)·R_p/(4ƛ_p) by two routes, agree to 1e-12 | σ distance from π³ per R_p source; four trial targets/epochs (π³, 32, z*, z_drag) recorded as look-elsewhere count |
| W5 | Varying-c model matrix (A: α∝N; B: α fixed, m∝N², c∝N⁻¹; C: hop-tick, static; D: emission-depth rule) | exponent algebra reproduces known identities (a₀ = ħ/(m c α), E₁ = α²mc²/2) symbolically | PASS/FAIL per observable: solar redshift = ϟ/R (1 %); Shapiro factor 2; SN light-curve stretch exponent 1 ± 0.05; |Δα/α| < 1e-5 at z ≈ 2; CMB T(z) β = 0.004 ± 0.016 (RUN-1 input, within 3σ); Law V k_H ≥ 1 for N ≤ 1100. Pure unit change (all dimensionless ratios fixed) is reported separately from physical change |
| W6 | Ground state per epoch, ionisation | Saha solver reproduces the textbook x_e = 0.5 at T ≈ 3700–3800 K for η = 6.1e-10 | two routes for the release epoch: (i) E₁/kT = 53 rule, (ii) full Saha x_e(N) = 0.5. Agreement within 5 % confirms; disagreement is the finding |
| W7 | Shapiro-displacement torus | Pappus volume vs Monte-Carlo volume of a ring torus (r < R) agree to 1 % | ring torus valid only if r_tube < R_major |
| W8 | Neutrino tick test | — | prediction table only (no data) |
| W9 | Depth rate law D(t): dN/dt = −H₀Nᵖ, transit speed c₀N^(−q), q ∈ {0, 2} | numerical distance integral vs closed form, 1e-8 | Pantheon+ (Datasets/cosmology, zHD > 0.01, diagonal errors only — stated limitation) shape fit: p CALIBRATED(1) + one magnitude offset. Comparator: flat ΛCDM (Ωm + offset) on the same points. Δχ² reported, no verdict beyond Δχ² and BIC. Elapsed time 1090 → 1 across the p family reported as identifiability measure |

Single pass: each table is computed once over its full range from these rules; no mid-range retuning.

## W10 — Spaz ladder: today's ratios traced back to the halt of light (added 2026-10-31, before its tool exists)

Rules, all from candidate D (`SPAZ_ASSESSMENT2.md` §5) and `Papers/SDT_THEORETICAL_MODEL.md` §4–5, with nothing new:
N = T_local/T_CMB; Spaz depth z_S = 1 − 1/N; c_far = c/N²; hop = ℓ_P/N; tick = N t_P;
P = N⁴ P_rad (engine `law_I::P_rad`); Wien peak in local rulers λ = λ_now/N; local physics fixed
(α, μ, R_p/ƛ_p, a₀/hop locked).

Landmarks: each one is defined by a locked local quantity reaching the bath. Each N is computed once over the whole range, from N = 1 to the halt:
FIRAS release (1090) · Saha half-points of H, He I, He II (η = 6.1e-10, Y = 0.245, shared-input) ·
visible band · Lyman-α peak · kT = E₁ · solar-centre temperature (comparator) · Wien photon = 2m_ec² · kT = m_ec² ·
kT = B_d, B_α · P = P_eff · λ = r_e, λ = R_p · kT = m_pc² · Planck temperature ħc/(kℓ_P) · halt λ = ℓ_P.

Validation: the ladder must reproduce the repository's own table (`SDT_THEORETICAL_MODEL.md` §6: N = 1090 → 252 m/s; P = P_eff at N = 2.48×10¹¹; ℓ_P at N = 6.58×10³¹) to 1 %. Saha must reproduce the textbook He II and He I half-points (z ≈ 6000, ≈ 2500 ± 20 %).
Elapsed time is reported for both W9 transit rules and labelled non-identifiable.

## W11 — transit-rule permutations, extended grid (pre-registered 2026-10-31, before `spaz_transit2.cpp` exists)

Each cosmic permutation has a tick exponent a (far-frame emission period ∝ Nᵃ) and a hop exponent b (far-frame hop ∝ N⁻ᵇ), so the transit speed is c_far ∝ N^−(a+b). Locally, a = b = 1 (Sun, W5). Transit conserves the tick spacing; the supernova stretch (W5) requires this.

Grid: a ∈ {1, 2} × b ∈ {−1, 0, 1, 2, 3} × halt ∈ {P = P_eff (T_local 6.747×10¹¹ K), Wien peak = ℓ_P (T_local 1.793×10³² K)}. That is 20 permutations.

Derived per permutation, with nothing tuned: 1+z = Nᵃ; T_local = T₀Nᵃ; the Pantheon+ shape fixes s = 1 − 0.28a (W9), so p = s − (a+b); H = H₀/a; N_halt = (T_halt/T₀)^(1/a).

| Gate | Rule | Pass |
|---|---|---|
| G1/G2 redshift = SN stretch; CMB β = 0 | tick-conserving transit | by construction for all (not evidence) |
| G3 Pantheon+ | identical shape for all (Δχ² = +5.1) | all (not discriminating) |
| G4 release | τ_Thomson = 1, Saha (η = 6.1e-10), local time dt/Nᵃ, H₀ = 70 | T_local within 5 % of 2971 K or 2892 K |
| G5 onset spacing | far-frame hop at the halt, ℓ_P N_halt^(−b) | within one decade of James's stated 10⁻⁷⁰ m |
| G6 elapsed time | (a/H₀)(N_h^(1−p) − 1)/(1−p) | reported for survivors only |

Look-elsewhere: 20 permutations × 2 release comparators × 1 spacing target = 40 trials.
Validation: (1,1) gives release N = 734.1 and (1,−1) gives N = 1064.2 (W6b). The two step sizes in ln N (10⁻³ and 10⁻⁴) must agree to 0.1 %.
Reporting: full detail for permutations passing G4 and G5; fails are listed in one line each.

## W12 — α against Earth's solar depth: Berkeley Cs campaign (pre-registered 2026-10-31, before any fit)

Data: Zhong, PhD thesis (UC Berkeley 2020), Figure 4.4, 28 values of (α − ᾱ)/ᾱ with 1σ bars. They are read from the PDF's vector paths. Dates come from Table 4.1 (13 Dec 2016 – 12 Jun 2017). Depth: z = ϟ_Sun / r(date), with ϟ_Sun from the engine and r from Kepler's equation for Earth's orbit (e = 0.0167086, perihelion 2017-01-04).

Digitisation validation (known answers from the thesis):
- weighted mean of the read values within ±0.05 ppb of 0;
- combined statistical error 0.16 ± 0.01 ppb;
- reduced χ² about the mean 1.2 ± 0.1.

Test: weighted least squares, (α − ᾱ)/ᾱ = c + k·(z − z̄). Report k with 1σ.
- **The depth coupling needed for the Cs–Rb gap, k = 3.5, is excluded** if it lies more than 2σ from the fitted k.
- **A coupling is indicated** if k ≠ 0 at more than 2σ *and* the same sign appears in the N = 125-only subset (removes datasets 2–5, which used N = 150 and 200).

Reported once; no dataset removed except the pre-registered N = 125 subset.

## W13 — Northwestern electron g−2: α against solar depth and frame speeds (T1; pre-registered 2026-11-01, before any fit)

Data: Fan, PhD thesis (Harvard 2022). Sources:
- Table 4.7: 11 field values of raw g/2 with statistical σ, and the cavity correction with its σ.
- Figure 4.37: 11×11 correlation matrix of the cavity-correction uncertainty.
- Table 4.8: common-mode systematics.
- Table 4.1: run dates per field set.

Value per field = raw + correction, in units of 10⁻¹² relative to g/2 = 1.001 159 652 180 59. Conversion to α: Δα/α = Δ(g/2)/a_e, a_e = 1.159 652 18×10⁻³ (leading order; next order changes the slope by 0.15 %). Each field set is dated at the midpoint of its runs.

Covariance V = diag(σ_stat²) + C_ij σ_cav,i σ_cav,j + (common-mode sum)² for every element.

Extraction validation (must reproduce Fan Eq. 4.90 and the stated χ² before any fit is read):
- GLS mean 0.00 ± 0.02 (×10⁻¹²)
- uncertainty 0.13 ± 0.01
- χ² = 13.04 ± 0.5 for 10 dof

Test: GLS fit value = c + k·(x − x̄) for each regressor x ∈ {solar depth z, heliocentric v²/c², CMB-frame v²/c², galactic-frame v²/c²}. Comparison is with Berkeley Cs (W12/W12b/W12d).

| Outcome | Condition |
|---|---|
| **replicates** | k_NW ≠ 0 at > 2σ and \|k_NW − k_Cs\| < 2σ_combined |
| **contradicts** | \|k_NW − k_Cs\| > 2σ_combined |
| **uninformative** | neither of the above |

The magnetic-field/date confound is reported as the correlation of B with z, because the cavity correction depends on the field.
