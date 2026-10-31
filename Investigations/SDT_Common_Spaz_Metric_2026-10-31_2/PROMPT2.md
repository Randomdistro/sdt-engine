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
