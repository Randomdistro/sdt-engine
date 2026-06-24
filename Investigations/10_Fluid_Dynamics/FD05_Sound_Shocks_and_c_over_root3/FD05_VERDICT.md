# FD05 — Verdict: Sound, Shocks, and the c/√3 Ceiling

**Classification: CLASS A/C** — the strongest result of the FD series.
**Author**: James Christopher Tyndall, Melbourne · Tool: `fd05_sound_shocks.cpp` (MSVC `/utf-8 /std:c++20`, ran clean; all 5 phases PASS).

## Deciding metrics
| Phase | Result | Class |
|---|---|---|
| 1 — ordinary sound `c_s=√(dP/dρ)` | air 343.31 (+0.031%), water 1477.8 (−0.215%) | C (convergence; EoS slope MEASURED-INPUT, relay narration native) |
| 2 — `c/√3` from `P=u/3` | `1.730853×10⁸` m/s, `w=1/3` exact, = CR04 BAO | **A (native, zero params)** |
| 3 — one curve `c_s=c√w` | nothing exceeds `c/√3`; all on-curve | A/C |
| 4 — Mach cone + thickness | angle 0.00° vs textbook; `δ~(3–5)λ` | A/C |
| 5 — boom ≡ Cherenkov (E57) | `θ_boom+θ_C=90°` exact; recovers ~41° | **A (distinctive native unification)** |

## Why Class A/C (not pure A)
The `c/√3` ceiling and the boom≡Cherenkov unification are **native, zero-parameter** results
(Class A). Ordinary-fluid sound speeds are a **convergence** (`γ, R, K` are MEASURED-INPUT;
SDT supplies the relay-wave *mechanism* and the `c_s=√(dP/dρ)` form, not the material EoS) →
Class C for that phase. Overall the investigation's distinctive content (the relativistic
ceiling + the single shock criterion unifying sonic boom and Cherenkov) is **Class A**.

## Provenance × correspondence
- **provenance**: SDT-derived (c/√3, shock criterion); external/MEASURED-INPUT (γ,R,K for ordinary sound).
- **correspondence**: known-match (343 m/s, Cherenkov ~41°) + **novel** (boom≡Cherenkov one-mechanism claim, falsifiable: any medium where the two cone laws disagree breaks it).

## Falsification (all held)
c_s from compressibility ✓ · c/√3 recovered from P=u/3 ✓ · no medium exceeds c/√3 ✓ · Mach angle 1/M ✓ · Cherenkov angle recovered, θ+θ_C=90° ✓.

## Parameter ledger (R2)
`c, ℓ_P, u_CMB, P_rad=u/3` WHITELIST/DERIVED · `γ_air=1.4006, R=287.05, K_water=2.18e9, ρ_water, λ=68nm, n=1.333` MEASURED-INPUT · zero CALIBRATED. **Sign-off: PASS, Class A/C.**
