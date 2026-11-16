# HUNTER SCOUR — FD (Fluid Dynamics) + TD (Thermodynamics) region

> **Auditor:** HUNTER @ maximum pressure · **Date:** 2026-07-02 · **Assume-fabrication** default.
> **Region:** `Investigations/10_Fluid_Dynamics/FD01–FD11` + `11_Thermodynamics/TD01, TD05, TD07, TD08`.
> **Model to beat:** APS04 (fabricated PASS: tool never compiled, `constexpr std::sqrt` C2131, number reverse-engineered to sit near target).

## Headline

**This region does NOT match the APS04 fabrication pattern.** Every tool I execution-checked (FD01, FD02, FD05, TD01)
**compiled clean under MSVC `/std:c++20 /O2 /utf-8`** (BUILD_EXIT=0) and its **stdout reproduced the committed
`*_results.txt` verbatim** — the opposite of APS04's non-compiling, hand-typed narrative. Verdicts are dominated by
**honestly-labelled Class C convergences** with disclosed CALIBRATED(n) counts, delete-tests, and explicit
"BORROWED / reproduced, not derived" flags on the imported coefficients (2π lift slope, 6π Stokes, Blasius
prefactors, Roshko constants). No fabricated PASS found. The faults below are **INFLATION** and **IDENTITY-PASS**
issues — real, but a full tier below fabrication.

## Execution checks performed (COMPILE+RUN, MSVC BuildTools 2022)

| Tool | BUILD | RUN | stdout == committed results.txt? |
|---|---|---|---|
| `fd01_navier_stokes_relay.cpp` | **0 (clean)** | 0 | **EXACT match** |
| `fd02_viscosity_circulation.cpp` | **0 (clean)** | 0 | **EXACT match** |
| `fd05_sound_shocks.cpp` | **0 (clean)** | 0 | **EXACT match** |
| `td01_microstates.cpp` | **0 (clean)** | 0 | **EXACT match** (results.txt is UTF-16 MSVC redirect) |

All four reproduce. The "machine precision" red flag in the prompt is real but is **honestly narrated as identity /
convergence**, not dressed as a native surprise. No reverse-engineered target found in the compiled set.

---

## Fault table

| ID | Status | Grade | Fault (evidence) |
|---|---|---|---|
| **FD01** Navier–Stokes | Compiles+runs; Class C honest | **IDENTITY-PASS (labelled)** | Tool DOES evolve a real 1-D diffusion (random-walk → Laplacian); it does **NOT** evolve the NS momentum equation. No nonlinear `(v·∇)v`, no pressure–velocity coupling, no actual NS solve. "ν recovered to 3e-10" is recovering the **definitional** `ν=w·dx²/dt` of a symmetric random walk — a textbook heat-equation identity, not NS-specific. Verdict headline "Navier–Stokes reproduced term-for-term" over-reaches vs what the tool shows (diffusion + Ma² + linear advection). BUT the verdict itself says "reproduction of a known PDE, not an independent numerical surprise… Class C," so it is **not** a fabricated PASS. |
| **FD02** Viscosity/Circulation | Compiles+runs; Class C honest | **IDENTITY-PASS (labelled)** | Core gate C4 "κ=h/m_He, rel err 0.020%" is an identity: the measured superfluid circulation quantum *is* `h/m` by construction (Onsager–Feynman–Vinen), and the "two-stream check" `h/m vs 2πℏ/m = 6e-17` is pure algebra (`h≡2πℏ`). The 0.020% is how well Vinen 1961 confirms `h/m`, not an SDT prediction of a number. Verdict **explicitly says "by construction"** and flags 1/(4π) KSS coeff as CALIBRATED(1) and water viscosity ×16.5 off — disclosed, not laundered. |
| **FD03** Reynolds | Compiles claimed; Class C honest | **IDENTITY + CALIBRATED, labelled** | Phase-1 "Re=τ_relay/τ_adv exact to 1e-16" is algebra: `(L²/ν)/(L/U)=UL/ν`. Re_crit value needs CALIBRATED(1) coherence ratio **per geometry** — pipe 2300 does NOT fall out zero-param. Honest "null test": pipe count on flat plate misses 5e5 by ~4 orders, and they SAY it needs a 2nd calibration rather than hide it. Good-faith. |
| **FD04** Kolmogorov −5/3 | Class A(exponent)/C | **CLEAN** | −5/3 is the OUTPUT of a 2×2 dimensional linear solve, not typed in; C_K prefactor held OPEN (not fitted to 1.5); intermittency OPEN. Delete-test clean. This is the strongest-honest FD result. No fault. |
| **FD05** Sound / c/√3 | Compiles+runs; Class A/C | **CONVERGENCE on known result, labelled A** | c/√3 is **genuinely derived** natively: law_I gives P=u/3, ρ_eff c²=u ⇒ c_s²=d(u/3)/du=1/3. Not a bare assertion of the identity c=1/√(μ₀ε₀). It **recovers the textbook relativistic radiation-fluid sound speed** and the boom≡Cherenkov unification; labelled "Class A native." Fair, though "A" for recovering standard physics is generous — the derivation chain is internal and honest. Phase-1 air/water are MEASURED-INPUT convergence (labelled C). |
| **FD06** Boundary layer | Class C honest | **REPRODUCED prefactors, labelled** | No-slip + δ∝√(νx/U) scaling native; Blasius numbers 4.91/0.664/0.332/2.59 are the similarity-ODE eigenvalue, **reproduced by RK4+shooting, flagged "not derived from SDT geometry."** ν CALIBRATED(1). Honest. |
| **FD07** Lift/Magnus | Compiles; Class C honest | **BORROW, labelled** | Lift sign, L=ρUΓ, Kutta-as-relay-continuity native (two-stream 9e-14%). The 2π lift-curve slope is **explicitly flagged BORROWED potential-flow geometry** ("does NOT pass a pure-SDT delete-test") — precisely the disclosure APS04 lacked. |
| **FD08** Bernoulli | Class C honest | **CANON-EDIT log (see boundary note)** | Bernoulli recovered as Law-V budget partition; g=v²/R (no G/M). One input (γ). Honest. **Logs a laws.hpp edit** ("dangling reference at laws.hpp:1162 corrected") — a canon touch; committed change 010b6e3, header currently compiles. Flag, not this-region fault. |
| **FD09** Drag | Compiles claimed; Class C honest | **CORRELATION, labelled + minor overclaim** | 6π Stokes prefactor & C_D(Re) curve & drag crisis are **flagged CORRELATION/MEASURED-INPUT, not derived.** `solid_angle_occluded(R,1m)=πR²` verified real in laws.hpp:424 (not a fudge). Minor: 3mm-drop terminal 8.64 vs 8.0–8.1 is **+6.7%** but called "~7%"/"order-correct" — fine; C5 uses rigid-sphere C_D, disclosed. |
| **FD10** Vortex shedding | Compiles claimed; Class C honest | **CALIBRATED(3), self-caught numerology** | St_∞=0.2063 (+0.61%) from 3 inputs (κ_clock=0.45, D_eff/D=1.20, U_wake/U=0.55): recomputed `1/(1.20·(1/0.55)/0.45)=0.2063` ✓ genuine, not back-solved. **§4 documents that an earlier draft back-solved κ_clock (zero-residual "numerology smell") and REJECTED it** for a fixed literal producing a real +0.61% miss. Exemplary anti-fake discipline. B_eff, k₀ are extra calibrations on separate features. |
| **FD11** Tesla turbine | Class D | **CLEAN (modest)** | Correctly labelled Class D engineering estimate, CALIBRATED(2), "not a sealed SDT prediction." No overclaim. |
| **TD01** Entropy/arrow | Compiles+runs; Class C | **NULL-SDT-CONTENT (labelled), toy** | S=k_B ln W with stars-and-bars C(E+N−1,N−1) — **standard textbook Boltzmann combinatorics; nothing SDT-specific enters** the counting. "Relay lattice" is narration only. Test-3 T_eff=2.27e23 K is physically absurd (dimensionless toy) but not headlined. H-theorem/arrow-of-time (the actual claim in the title) is **PENDING**, honestly. Weak but honest Class C. |
| **TD05** Phase transitions | **NOT STARTED** | **N/A — stub** | Only PROMPT.md exists. No verdict, no .cpp, no results. Nothing to audit; no fabrication. |
| **TD07** Landauer | **NOT STARTED** | **N/A — stub** | Only PROMPT.md exists. Same as TD05. |
| **TD08** Fluctuation-dissipation | **NOT STARTED** | **N/A — stub** | Only PROMPT.md exists. Same as TD05. |

---

## Boundary note (outside FD/TD region — flag for the canon-tracking hunter)

The **uncommitted** working-tree diff of `Engine/include/sdt/laws.hpp` (`git diff`, 14+/10−) is a **comment-only
re-labelling of `ℓ_P`** from *"SDT-posited (Axiom R1) — primitive, NOT derived"* to *"SDT-native — DERIVED from an
observed koppa (G-free)."* The numeric value `1.616255e-35` is unchanged. This flips the framework's foundational
seed from **axiom → "derived,"** which contradicts the standing MEMORY rule ("No edits to the laws canon without
Harvey's explicit OK") and FLM06's own Seed-Theorem stance that one dimensional anchor is unavoidable. **I did NOT
touch it** (off-limits + out of region). Raising it because it is load-bearing (`N=R_CMB/ℓ_P`, `P_conv=Φ/ℓ_P³`) and
a live provenance re-classification, not a numeric change. Separately, FD01/FD08 verdicts log an **older committed**
laws.hpp brace/reference compile-fix (010b6e3) — the header compiles today, so that one is not currently corrupting.

---

## Per-investigation one-line status

- **FD01** — Navier–Stokes: compiles+runs, stdout==results; evolves diffusion not NS; **IDENTITY-PASS labelled C.** OK.
- **FD02** — Viscosity/κ: compiles+runs, stdout==results; κ=h/m is by-construction identity, disclosed; **C, OK.**
- **FD03** — Reynolds: Re=UL/ν re-expressed as timescale ratio (algebra); value CALIBRATED per geometry, disclosed; **C, OK.**
- **FD04** — Kolmogorov: −5/3 from dimensional solve, prefactor OPEN; **cleanest FD, A(exp)/C.**
- **FD05** — Sound/c√3: c/√3 genuinely derived from P=u/3 (native chain), recovers textbook value; **A/C, fair.**
- **FD06** — Boundary layer: no-slip native, Blasius prefactors reproduced+flagged; **C, OK.**
- **FD07** — Lift/Magnus: sign native, 2π flagged BORROWED; **C, exemplary disclosure.**
- **FD08** — Bernoulli: Law-V budget, g=v²/R; **C, OK**; logs older canon compile-fix.
- **FD09** — Drag: occlusion form native, 6π/curve flagged CORRELATION; **C, OK**; minor +6.7% called ~7%.
- **FD10** — Strouhal: St_∞ from 3 calibrations, recomputes clean; **self-caught & rejected numerology; C, exemplary.**
- **FD11** — Tesla turbine: **Class D engineering estimate**, modestly labelled. OK.
- **TD01** — Entropy: textbook S=k_B ln W, no SDT content in the counting; H-theorem PENDING; **weak but honest C.**
- **TD05 / TD07 / TD08** — **STUBS: PROMPT.md only, no result to audit.** No fabrication.

## Verdict line

> **Prompt completion A** (region swept, 4 tools compiled+run, all reproduce) · **Physics class of the region:
> CONVERGENCE, honestly labelled** — dominated by Class C with disclosed calibrations and borrow-flags; **no
> fabricated PASS**, contra the APS04 model. Worst faults are **IDENTITY-PASS dressed slightly hot in FD01's
> "term-for-term" headline** and **null-SDT-content in TD01**, both a tier below fabrication. · **Recovery:** faults
> are wording/inflation, correctable by softening two verdict headlines; the code stands. · **Cascade root:** the FD
> chain's Class-A ceiling is blocked on the shared unbuilt piece — a **parameter-free λ_mfp / coherence-length /
> κ_clock closure from ROOT-SIM** (FD02→FD01/FD03/FD10 all defer to it); log once.

— HUNTER · FD_TD sheet · 2026-07-02
