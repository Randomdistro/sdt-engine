# NP24 — Technical Report (RUN 1, 2026-07-18/19)
### Grammar rule extraction: residual law · stability band · ionisation ladder scaled to H

> **Data (all pulled live, all validated):** AME2020 `mass_1.mas20.txt` (3558 mass excesses) · NUBASE2020 `nubase_4.mas20.txt` (253 stable, spins, decay modes) · CRC ionisation ladders (104 elements, 764 stages, 8/8 spot-checks exact).
> **Discipline:** every candidate rule declared in PROMPT §③ *before* fitting; cross-validated even-Z↔odd-Z; every rejection reported.

## P0 — Conservation
All 3213 valid-grammar isotopes (Z≥3, n_d≥0, n_t≥0) satisfy `A = 4+2n_d+3n_t` and `Z = 2+n_d+n_t`. **0 failures.** Domain note: the grammar begins **after** helium — He is the core, not a construction on it. (CLAUDE.md says "Z ≥ 2"; it should read *after helium*.)

## P1 — The residual map
ε = (κ·ΔA − BE)/BE from the shadow-overlap packing model, κ = 10.792 MeV/fm².

| variable | r(ε, x) |
|---|---|
| **f_t = n_t/(n_d+n_t)** | **+0.867** |
| u = n_d − n_t | −0.800 |
| n_d | −0.781 |
| (N−Z)²/A | +0.400 |
| A^(−1/3) | +0.329 |
| n_t | +0.231 |

## P2 — Rule extraction (out-of-sample, even-Z fit → odd-Z test and reverse)

| form | OOS R² |
|---|---|
| R4 pairing alone | −0.000 |
| R5 surface A^(−1/3) | +0.105 |
| R3 asymmetry (N−Z)²/A | +0.159 |
| R1 linear in u | +0.639 |
| **R2 triton fraction f_t** | **+0.751** |
| **R6 = f_t + A^(−1/3) + pairing** | **+0.933** |

**F1 (OOS ≥0.5): PASS. F2 (beats constant by 0.2): PASS.**

**Mechanism, not curve-fit:** a triton casts **3** boundary disks but carries **1** proton; a deuteron casts **2** and carries **1**. The shadow counts *nucleons*; NP17 says binding is the shared-electron well between *protons*. The mismatch between A = 4+2n_d+3n_t and Z = 2+n_d+n_t **is** f_t.

**Direct test:** shadowing protons only collapses the bias (r: 0.867 → **0.205**) — diagnosis confirmed — but degrades everything else (R²(BE) 0.881 → 0.721, error 13.8% → 22.7%). **Binding counts neither nucleons nor protons.**

## P3 — Stability band
- f_t(stable): mean 0.336, sd 0.150. f_t(unstable): mean 0.454.
- Band f_t ∈ [0.000, 0.551] contains **98.8% of stable** — **F3 PASS**.
- **But it also contains 1925 unstable nuclei (65% of all unstable).** The band is **NECESSARY, NOT SUFFICIENT**; it cannot pin a decay-chain endpoint.

## P4 — Ionisation ladder scaled to H (z = IE/13.59844, k = 1/√z)
- **I1 CONFIRMED EXACTLY.** Over all 29 complete ladders: z_last/Z² = **1.00426 ± 0.0034**, max deviation 1.15%, rising monotonically with Z (the relativistic ~(Zα)² correction). **k_last = 1/Z**; H is k = 1, the unit rung. *Degenerate with Moseley — not an SDT result.*
- **Correction to a claim made mid-run:** "every ionisation is a deeper seat than hydrogen" is **false** — Li k₁=1.588, Ba 1.615, Cs 1.869, Fr 1.827 are all **> 1** (shallower than H).
- **Core-breach tally, all 81 elements with ≥2 stages:** biggest tear leaves a noble-gas core in **35/81 = 43%** (He 24, Ne 4, Kr 4, Xe 2, Ar 1). The other **46 tear inside an open d/f shell.** (An earlier sampled view showed only s/p elements and over-generalised.)
- **Z_eff = 1/k correlations:** stage s **+0.872**, electrons present −0.537, **Z only −0.322**. Seat depth is set by *rung position*, not nuclear size.
- **I3 (grammar↔ladder coupling) FAILS; I2 (structure is a function of Z and shell occupancy alone) HOLDS.** **F5 fires: the cross-scale claim is dead. NP24 is nuclear-only on present evidence.**

> ⚠️ **I3 VERDICT WITHDRAWN 2026-07-23 — see `TECHNICAL_REPORT_I3_REVIEW.md`.** The I3 null is a
> **test artifact**: it correlated the ionisation ladder (fixed by Z, isotope-blind to leading order)
> against n_t = N−Z (which ranges across an element's isotopes) — a constant against a variable, null by
> construction. The coupling lives in the **isotope shift** (which I3 discarded), and the King-plot
> nonlinearity already tracks the mass-defect ledger. Corrected verdict: coupling **CONFIRMED**
> (nucleus→valence); valence→nucleus causation **RE-OPENED** (In→I deuteron skip is the candidate).

## Verdict
> Prompt completion **B** · Physics class **MIXED**: R6 residual law **EMPIRICAL-LAW (mechanism named)** · stability band **NECESSARY-NOT-SUFFICIENT** · I1 **DEGENERATE-with-Moseley** · I3 **KILLED**.

## Terminology flag
"Full charge Z" was written into an interim analysis. There is no charge substance — it is a **count of handednesses**, unscreened. Corrected in place.
