# RUN_LOG — PM01 (Magnetism as Collective Vortex Circulation)

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-03 · **Executor:** HUNTER-disciplined run.
**Written BEFORE any code, per `PROMPT_EXECUTION_PROTOCOL.md`.**

## Pre-Run Commitments — PM01

- Prompt completion target: **C** (native structure + native sign; the signed-∝B gain is NOT expected
  to close natively — see wall note below, committed before running).
- Physics class hoped: **NATIVE** for (Ampère exponent as conservation law, ∇·B≡0 as identity-of-the-
  identification, Lorentz ± sign via Magnus/FD07 handedness); **OPEN** for the signed gain.
- CALIBRATED budget: **0** in the native chain. SI conversions appear ONLY on final reporting lines,
  tagged `IMPORTED` (µ₀, e, tesla). No µ_B/µ_N anywhere, any phase.
- Engine namespaces actually used: `measured` (c, ℏ, h, m_e), `law_VI::traction` (cited),
  FD02 circulation quantum κ = h/m (cited), `magnetosphere.hpp` earth constants (P4 comparison only).
- Native units in code: lengths in bundle radii, circulation quantum κ = 1, lattice density ρ_a = 1,
  carrier inertia m = 1. Firewall comment in code: `// NO B-in-tesla / NO qv×B / NO µ_B,µ_N here`.

### Phase thresholds (committed before run)

| Phase | Gate | Threshold |
|---|---|---|
| P1 | Γ_v native | Γ_v = h/m_e quoted as circulation [m²/s]; g-factor dimensionless only; **zero magnetons** |
| P2a | aligned-bundle swirl (magnet geometry) | azimuthal `w` exponent −1 ± 2% over ≥1 decade outside bundle; enclosed-circulation count exact to <0.1% |
| P2b | drift-bundle (wire geometry) | B_φ = −∂w_z/∂r exponent −1 ± 2% over ≥1 decade, from a momentum-flux-conserving (1/s) per-carrier wake; the 1/s² (non-conserving) control MUST fail (exponent ≈ −2) — if the control also gives −1, the conservation claim is dead |
| P2c | ∇·B structural | max\|∇·B\| / max\|∇×w\|·(1/h) ≤ 1e-9 on interior nodes of an asymmetric 3-D `w`; **flagged in advance**: div∘curl ≡ 0 is vector calculus — the SDT content is only the identification B ≡ ∇×w. This gate cannot fail honestly; it is a consistency check, not a discovery. |
| P3 | Lorentz sign matrix | 4/4 cells (±handedness × ±field) match the observed qv×B pattern **from the Magnus channel's handedness alone**, no hand flip. Separately: measure gyration frequency vs field strength for BOTH native channels — Magnus (signed) and entrainment/Coriolis (unsigned). Committed expectation: **neither channel alone gives a signed push with ω ∝ B**; if that is what the run shows, record the gain as OPEN (do NOT plug). |
| P4 | magnetosphere | Pivot row 5 fires by inspection: `magnetosphere.hpp` stores B_surface in tesla and µ_earth in A·m² — a native P4 needs the µ₀-free gain that P3 shows is OPEN. **P4 is DEFERRED** (per pivot table). An OBSERVED-inputs Chapman–Ferraro standoff is computed for context only, labelled CONVERGENCE, not claimed native. |

### The wall note (committed before run)

`laws.hpp` (EMC02, lines 131–135) certifies the elementary charge e as an **irreducible Tier-1
input** — not derivable from the derivation basis. The "native handed gain" PM01 needs (a signed coupling
between a W=1 vortex's handedness and ambient swirl, with push ∝ swirl density) is dimensionally
e-shaped. If the run confirms the two-channel split (signed-but-not-∝B vs ∝B-but-unsigned), the
honest verdict is that PM01's gain question and EMC02's charge question are the SAME open problem,
and no amount of simulation in this tool can close it. Committed: that outcome is reported as OPEN,
not softened, not plugged.

### Forbidden retroactive changes

Import qv×B / B-in-tesla into the native chain then claim A; quote any moment in µ_B/µ_N;
hand-flip a Lorentz sign cell; widen tolerances after seeing numbers; plug the gain; IDENTITY-PASS
(the P2c calculus identity is pre-flagged as such and not counted as a discovery); local constant
namespaces.

## Run record (filled after execution — see `pm01_results.txt` for real stdout)

- Build: MSVC `cl /std:c++20 /EHsc /O2 /utf-8 /I Engine\include` — see results header.
- Outcome: see `PM01_VERDICT.md`.
