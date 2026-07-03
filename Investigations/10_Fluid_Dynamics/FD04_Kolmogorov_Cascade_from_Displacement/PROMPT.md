# FD04 — The Kolmogorov −5/3 Cascade as the Displacement Cascade

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is the turbulent inertial-range `E(k) ∝ k^{−5/3}` law *postulated* (as in Kolmogorov's 1941 similarity hypotheses) or does the SDT volume-conserved displacement cascade **force** the `−5/3` exponent through the chain volume-conservation → constant flux → `u_ℓ ∝ ℓ^{1/3}` — with nothing fitted but the prefactor `C_K`?
2. **Why does it matter?** — SDT already owns a *verified* shell-by-shell conservation law (`u ∝ 1/r²`, strain `∝ 1/r³`); if turbulence is that same law in the continuum, the most robust empirical fact in fluid mechanics becomes a native consequence, and the dissipation microscale `η = (ν³/ε)^{1/4}` gains a hard `ℓ_P` floor. This is a **genuine native-derivation candidate**, not a borrow — the exponent is the deliverable.
3. **How will we find out?** — Five gated phases (§④): the constant-flux ledger (P1) yields `u_ℓ ∝ ℓ^{1/3}` *before* the spectrum is read; the −5/3 closure (P2) is the core gate; any exponent ≠ −5/3 from the flux argument is a clean kill, **not** a retrofit.
4. **What would prove us wrong?** — §⑧, five falsifiers with real failure modes: non-constant `ε_n`; flux argument yielding any exponent ≠ −5/3; no finite dissipation scale; a derived `η < ℓ_P`; or measured slopes irreconcilable beyond ±0.10.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, with `C_K` and intermittency held honestly OPEN.

**Domain**: Fluid Dynamics (SDT lattice mechanics) · **Status**: SPEC · **Author**: J. C. Harvey, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} + measured observables in their measured units; no G/M/GM fundamentals; no fields/wavefunctions/quarks/gluons/virtual-particles/dark-matter/ΛCDM/magnetons; certification labels DERIVED / COMPUTED / CALIBRATED(n) / OBSERVED / PENDING on every result; audit spine A–F; translation test on every borrowed term; honesty over success — gaps stay OPEN, never repainted or fabricated).*

---

## 1. Executive Summary

Turbulence dissipates energy through a scale-by-scale cascade whose spectrum follows the celebrated `E(k) ∝ k^{−5/3}` law — empirically the most robust fact in fluid mechanics, yet in standard theory it is *postulated* via Kolmogorov's 1941 similarity hypotheses, not derived. **The question:** is the inertial-range cascade nothing other than the SDT *displacement cascade* — a displaced lattice volume passing scale-by-scale into smaller nested displacements with volume (and hence energy flux) conserved? **Why it matters:** SDT already owns a verified shell-by-shell conservation law (`u ∝ 1/r²`, strain `ε ∝ 1/r³`); if turbulence is that same law in the continuum, the −5/3 exponent must fall out of conserved flux on `{ε, k}` rather than being assumed. **Expected outcome:** a native derivation of the `−5/3` exponent and a finite spation Kolmogorov microscale `η = (ν³/ε)^{1/4}` bottoming toward `ℓ_P`, with the Kolmogorov constant `C_K` flagged honestly (COMPUTED or PENDING).

---

## 2. Physical Context

**Mechanism / analogy.** A large eddy is a large displaced volume of the relay lattice. In SDT a displacement does not vanish locally; it *propagates outward shell-by-shell with the displaced volume conserved* (the displacement-cascade result). Picture a stack of nested gears: the outermost (largest eddy) cannot dissipate directly because the lattice only relays to contacting neighbours at one tick, so it hands its displacement to the next-smaller nested displacement, which hands it down again. Energy is not lost in the handoff — only *relocated to a finer scale* — until the shell size reaches the dissipative microscale where relay smoothing (viscosity, FD02) finally converts ordered displacement into thermalised lattice jitter. The inertial range is exactly the band of scales over which the handoff is conservative (no input, no dissipation), and the cascade is therefore a **constant-flux** pipe: the energy-per-mass-per-time `ε` injected at the top equals `ε` dissipated at the bottom equals `ε` passing every intermediate scale.

**Key variables and dimensions.**
- `E(k)` — energy spectrum, energy per unit mass per unit wavenumber [m³·s⁻²]
- `k` — wavenumber, `k = 2π/ℓ` [m⁻¹]; `ℓ` is the eddy/shell size [m]
- `ε` — energy flux per unit mass = dissipation rate [m²·s⁻³]; the cascade invariant
- `u_ℓ` — velocity scale of an eddy of size `ℓ` [m·s⁻¹]
- `ν` — kinematic viscosity [m²·s⁻¹], handed in by FD02 (`ν = (geom)·ℓ_P·c`, scaling `ν ∝ √T`, B16)
- `η = (ν³/ε)^{1/4}` — Kolmogorov dissipation microscale [m]; `u_η = (νε)^{1/4}`, `t_η = (ν/ε)^{1/2}`
- `L` — integral (energy-injection) scale [m]; inertial range is `η ≪ ℓ ≪ L`
- `Re = u_L L/ν` — Reynolds number; inertial-range width scales `L/η ∼ Re^{3/4}`
- `C_K` — Kolmogorov constant, `E(k) = C_K ε^{2/3} k^{−5/3}`, measured `≈ 1.5`

**Connection to SDT.** The injected eddy is a Law-IV displacement load; the handoff between scales is the same nearest-neighbour relay (Law III occlusion, capped at `c`, Law V budget) that carries every SDT force; the conserved cascade invariant `ε` is the rate-form of the volume-conserved displacement cascade (`u ∝ 1/r²`, strain `∝ 1/r³` — the *same* `1/r³` that recurs in galactic line-kernels and tidal gradients). The microscale bottoming toward `ℓ_P` is the lattice telling the cascade where it must stop.

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Displacement cascade with volume conservation (verified SDT result).** A displaced lattice volume `V_disp` propagates outward shell-by-shell with the displaced volume conserved; this fixes amplitude `u(r) ∝ 1/r²` and strain `ε_strain(r) ∝ 1/r³`. This is *distinct* from the koppa depth `z = ϟ/r ∝ 1/r` — the cascade is a steeper, volume-conserving relation. Turbulence's inertial range is the rate-form (per unit time) of this same conservative handoff.

2. **Constant-flux invariant (Law I / Law III relay).** Because the lattice relays only to contacting neighbours at one tick and the inertial range has neither injection nor dissipation, the energy passed per unit mass per unit time `ε` is *scale-independent*: `ε(ℓ) = const` for `η ≪ ℓ ≪ L`. `ε` is the single cascade invariant — the rate at which displaced volume is handed down.

3. **Movement budget (Law V).** `v_circ² + v_trans² = c²` caps every eddy velocity at `c`; the eddy circulation `u_ℓ` is the `v_circ` of a shell of size `ℓ`. This guarantees the cascade is finite and bounded, not runaway.

4. **Relay smoothing = dissipation (FD02, Law III).** At small scales the relay-diffusion term `ν∇²v` (FD01/FD02) finally outcompetes inertial handoff. The crossover defines the microscale.

**The conserved-flux → −5/3 argument (derive natively; do NOT assume the exponent).**

Step A — *Eddy velocity from constant flux.* The displacement handed down per unit time at scale `ℓ` is the eddy's own kinetic content `u_ℓ²` divided by its turnover (relay) time `τ_ℓ = ℓ/u_ℓ`. Constant flux (axiom 2) demands
`ε = u_ℓ² / τ_ℓ = u_ℓ³ / ℓ = const`  ⟹  `u_ℓ = (ε ℓ)^{1/3}` ∝ `ℓ^{1/3}`.
This is the *only* `u_ℓ(ℓ)` law consistent with volume-conserved shell-by-shell handoff at fixed rate.

Step B — *Spectrum by dimensional closure on `{ε, k}`.* The energy held in a logarithmic band of scales is `u_ℓ² ∼ ∫ E(k) dk ∼ k·E(k)` evaluated at `k ∼ 1/ℓ`. Substituting `u_ℓ² = (εℓ)^{2/3} = (ε/k)^{2/3}`:
`k·E(k) ∼ (ε/k)^{2/3}`  ⟹  `E(k) ∼ ε^{2/3} k^{−5/3}`.
The exponent `−5/3` is forced by `u_ℓ ∝ ℓ^{1/3}`, which was forced by constant flux, which was forced by volume conservation — a clean chain, **no fitted exponent**. Write `E(k) = C_K ε^{2/3} k^{−5/3}`; `C_K` is the only undetermined number and must be tagged COMPUTED (if obtained from a lattice/shell count) or PENDING (if not).

Step C — *Dissipation microscale.* Where relay smoothing balances inertial handoff, `Re_ℓ = u_ℓ ℓ / ν ∼ 1`. With `u_ℓ = (εℓ)^{1/3}` this gives the eddy scale `η` at which dissipation closes the cascade: `η = (ν³/ε)^{1/4}`, `u_η = (νε)^{1/4}`, `t_η = (ν/ε)^{1/2}` — all DERIVED, not inserted. In the deep limit (`ν → ν_lattice ∼ ℓ_P·c`, FD02), `η` must approach the spation/Planck scale: the cascade *cannot* bottom below `ℓ_P` because the lattice has no finer shell. Quantify the floor and check `η ≥ ℓ_P`.

**Governing relations to derive (no new fitted parameters):** `u_ℓ = (εℓ)^{1/3}`; `E(k) = C_K ε^{2/3} k^{−5/3}`; `η = (ν³/ε)^{1/4}` with `ν` referenced from FD02. The deliverable is the chain *volume conservation → constant flux → `u_ℓ ∝ ℓ^{1/3}` → −5/3*, with `C_K` and intermittency held OPEN.

---

## 4. Investigation Strategy

Five gated phases. Run in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass). Each phase predicts its number *before* comparing to data (R1).

### Phase 1 — Cascade flux model (the shell-by-shell ledger)
- **Goal.** Cast the SDT displacement cascade as a discrete shell ledger: scales `ℓ_n = L·2^{−n}` (or a log-uniform `k`-grid), each shell holding velocity `u_n` and handing displaced volume to shell `n+1` at rate `ε_n`, in SDT primitives only.
- **Method.** Write the handoff `ε_n = u_n³/ℓ_n` and impose volume conservation between adjacent shells (axiom 1). Tag every constant DERIVED / MEASURED-INPUT / CALIBRATED(n) / PENDING in a parameter ledger (R2). Cite the displacement-cascade result, FD01 (NS root), FD02 (`ν`) as upstream.
- **Success metric.** With no injection/dissipation in the interior, `ε_n` is constant across shells to machine precision, and `u_n ∝ ℓ_n^{1/3}` emerges (fit exponent `1/3 ± 0.02`). **Checkpoint C1:** ledger is conservative; `u_ℓ ∝ ℓ^{1/3}` falls out, not assumed.

### Phase 2 — The −5/3 exponent (the core gate)
- **Goal.** Derive `E(k) ∝ k^{−5/3}` from the Phase-1 ledger via the §3 Step-B closure, with no exponent inserted by hand.
- **Method.** From `u_ℓ = (εℓ)^{1/3}` and `u_ℓ² ∼ kE(k)` read off the spectral slope analytically; independently *measure* the slope from a synthetic constant-flux cascade on the log-`k` grid by a log-log linear fit over the inertial band.
- **Success metric.** Analytic slope = `−5/3` exactly; numerical fitted slope `= −1.667 ± 0.03` over ≥1 decade of `k`. **Checkpoint C2 (core gate):** the displacement-cascade flux argument yields `−5/3`. *If the flux argument yields any exponent ≠ −5/3, that is a clean kill (Class F) — do not retrofit.*

### Phase 3 — Dissipation microscale & the ℓ_P floor
- **Goal.** Derive `η = (ν³/ε)^{1/4}` and show a finite dissipation scale exists, bottoming toward `ℓ_P`.
- **Method.** Impose `Re_ℓ ∼ 1` with FD02's `ν`; compute `η, u_η, t_η`. Sweep `ε` (and `Re`) and verify inertial-range width `L/η ∝ Re^{3/4}`. Take the deep limit `ν → ν_lattice ∼ ℓ_P·c` and check `η ≥ ℓ_P`.
- **Success metric.** `η = (ν³/ε)^{1/4}` reproduces a measured microscale (grid/atmospheric) within stated tolerance; `L/η ∝ Re^{3/4}` exponent `0.75 ± 0.05`; deep-limit `η` does not fall below `ℓ_P`. **Checkpoint C3:** finite, floored microscale. *If no finite dissipation scale emerges, Class F.*

### Phase 4 — Convergence to measured spectra
- **Goal.** Match the derived spectrum to real turbulence-spectrum data (the CONVERGENCE target, never borrowed).
- **Method.** Overlay `E(k) = C_K ε^{2/3} k^{−5/3}` on canonical datasets (tidal-channel, atmospheric boundary-layer, grid/wind-tunnel — see `DATA_REQUIREMENTS.md`). Fit the slope and (if `C_K` is to be extracted) the prefactor. Use `ε` measured from each dataset's integral-scale forcing; do not fit `ε` to the spectrum.
- **Success metric.** Fitted slope across datasets `= −1.667 ± 0.05`; if `C_K` is derived from an SDT shell count, agreement with measured `C_K ≈ 1.5` within 30 % earns COMPUTED, else PENDING. **Checkpoint C4.**

### Phase 5 — Intermittency honesty pass (OPEN)
- **Goal.** Quantify, do not hide, departures from `−5/3` (intermittency / anomalous scaling of higher-order structure functions).
- **Method.** Compute the local spectral slope and any systematic deviation; state plainly whether SDT's volume-conservation cascade predicts a correction or whether intermittency is OPEN. Do NOT fabricate an exponent correction.
- **Success metric.** Deviation magnitude reported with error bars and an explicit OPEN flag if unexplained. **Checkpoint C5:** intermittency catalogued as DERIVED-correction or honestly OPEN.

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | −5/3 cascade derived natively | `u_ℓ ∝ ℓ^{1/3}` and `E(k) ∝ k^{−5/3}` derived from volume-conserved constant flux (no inserted exponent), microscale `η = (ν³/ε)^{1/4}` DERIVED and `η ≥ ℓ_P`, measured-spectrum slope match `−1.667 ± 0.03`, AND `C_K` DERIVED within 30 % of 1.5 (CALIBRATED(0)). |
| **C (QUALIFIED — convergence)** | −5/3 reproduced, prefactor pending | Exponent chain exact and slope match `−1.667 ± 0.05`, microscale DERIVED, but `C_K` COMPUTED/PENDING (not yet derived from lattice geometry); `ν` referenced from FD02. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | Constant-flux argument gives `−5/3` analytically and the microscale form, but numerical slope only `−1.667 ± 0.10` and/or `C_K` and intermittency unresolved; dimensionally closed, not yet fully bijective. |
| **F (FAIL)** | Mechanism falsified | Displacement-cascade flux argument yields an exponent `≠ −5/3` at leading order (and it is not a defensible SDT-distinct prediction), OR no finite dissipation scale emerges, OR derived microscale falls below `ℓ_P`, OR measured slope cannot be reconciled within `±0.10`. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd04_kolmogorov_cascade.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-1 shell-ledger constant-flux cascade; Phase-2 log-log slope fit; Phase-3 microscale + `Re^{3/4}` sweep + `ℓ_P` floor check; Phase-4 overlay/fit against loaded spectra; prints its own A–F verdict. **No new constants redefined.** |
| `fd04_results.txt` | Plain text | Run output: `ε_n`-constancy and `u_ℓ ∝ ℓ^{1/3}` fit (Phase 1); fitted spectral slope vs `−5/3` (Phase 2); `η, u_η, t_η`, `L/η` vs `Re^{3/4}`, `ℓ_P`-floor check (Phase 3); per-dataset slope and `C_K` (Phase 4); intermittency deviation (Phase 5). |
| `FD04_DERIVATION.md` | Markdown | Full chain: volume conservation → constant flux → `u_ℓ = (εℓ)^{1/3}` → `E(k) = C_K ε^{2/3} k^{−5/3}` → `η = (ν³/ε)^{1/4}`; parameter ledger; `C_K` and intermittency status. |
| `FD04_VERDICT.md` | Markdown | A–F classification with the deciding metric; provenance × correspondence audit; what is DERIVED vs COMPUTED vs CALIBRATED(n) vs PENDING/OPEN; downstream handoffs. |

---

## 7. Dependencies & References

**Upstream (required):**
- **The displacement-cascade result** — displaced volume propagates shell-by-shell with volume conserved, `u ∝ 1/r²`, strain `∝ 1/r³`; the rate-form of this is the cascade invariant `ε`. The constitutional input to FD04.
- **FD01 (Navier–Stokes from Spation Relay)** — the FD root; supplies the advection/diffusion terms whose inertial-range balance defines the cascade.
- **FD02 (viscosity / dissipation scale)** — supplies `ν = (geom)·ℓ_P·c` and the `ν ∝ √T` law (B16); FD04 cannot reach Class A without FD02's `ν`.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_I::P_conv`, `law_I` throughput Φ/`u_CMB`; `law_IV` (`V_disp` → displaced volume); `law_V` (`v_circ² + v_trans² = c²` budget); `bridge` (koppa, k, depth z, for the `1/r` vs `1/r³` distinction). **Do not redefine any constant `laws.hpp` exposes.**

**Downstream (unblocked by this):** none yet (FD04 is presently a leaf of the FD branch).

**Related (informative):**
- **FD03 (laminar→turbulent transition)** — supplies the cascade *onset* (where the inertial range begins); read in parallel for the integral-scale `L` and `Re` at onset.
- **B16 (transport exponents)** — `ν ∝ √T`, exponent 0.5.
- Galactic line-kernel `1/r³` and tidal-gradient `1/r³` results — the *same* strain law as the displacement cascade; cross-check that the exponent recurs.

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Flux invariance (Phase 1) | inertial-range handoff is constant-flux | `ε_n` constant across shells; `u_ℓ ∝ ℓ^{1/3}` (exponent `0.333 ± 0.02`) | non-constant `ε_n` or wrong `u_ℓ` exponent ⟹ cascade is not volume-conserved handoff ⟹ revisit axiom 1 |
| F2 — The −5/3 exponent (Phase 2, core) | constant-flux ⟹ `E(k) ∝ k^{−5/3}` | analytic slope `−5/3` exact; numerical fit `−1.667 ± 0.03` | flux argument yields exponent `≠ −5/3` ⟹ **Class F**, clean kill (no retrofit) |
| F3 — Finite microscale (Phase 3) | dissipation closes the cascade at `η = (ν³/ε)^{1/4}` | finite `η`, `L/η ∝ Re^{3/4}` (exponent `0.75 ± 0.05`) | no finite dissipation scale, or wrong `Re` power ⟹ **Class F** |
| F4 — Spation floor (Phase 3) | cascade cannot bottom below `ℓ_P` | deep-limit `η ≥ ℓ_P` | derived `η < ℓ_P` ⟹ lattice ontology violated ⟹ **Class F** |
| F5 — Measured-spectrum match (Phase 4) | real spectra show the derived slope | fitted slope `−1.667 ± 0.05` across grid/atmospheric/tidal data | slopes irreconcilable beyond `±0.10` ⟹ displacement cascade ≠ turbulent cascade ⟹ **Class F** |

---

## 9. Implementation Notes

- **Spectrum fitting.** Work on a **log-uniform `k`-grid** (decades, not linear) so the inertial range spans ≥1 decade; fit the slope by ordinary least squares on `log E(k)` vs `log k` over the inertial band *only* (exclude the energy-injection knee near `k ∼ 1/L` and the dissipation roll-off near `k ∼ 1/η`). Report the fitted slope with its standard error and the fit window. Predict `−5/3` and commit it to the run log *before* fitting (R1).
- **Numerical stability.** Use **double precision**; quantities span many decades (`k` from `1/L` to `1/η ∼ Re^{3/4}/L`). Prefer **dimensionless ratios** (`ℓ/η`, `k·η`, `E(k)/(ε^{2/3} k^{−5/3})`) to avoid overflow; the last ratio should sit flat near `C_K` across the inertial range — a direct visual of −5/3. Guard against division by zero at `k → 0`.
- **Anti-numerology (R5).** The `−5/3` must come from the `u_ℓ ∝ ℓ^{1/3}` chain, never from inserting `5/3` or a tuned integer. `C_K` must be a derived shell count or flagged COMPUTED/PENDING — never fitted silently to force 1.5.
- **Testing strategy (R3 two-stream).** Three independent checks: (i) `ε_n` constancy to machine precision; (ii) analytic slope vs numerically fitted slope agree to `±0.03`; (iii) derived `η` vs a dataset's reported microscale. Each predicted and logged before comparison.
- **Standalone compile.** `cl /std:c++20 /EHsc /I Engine/include fd04_kolmogorov_cascade.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd04_kolmogorov_cascade.cpp -o fd04` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** (1) Compensated spectrum `E(k)·k^{5/3}/ε^{2/3}` vs `k` — a flat plateau at `C_K` is the cleanest −5/3 signature. (2) Raw `log E(k)` vs `log k` with the fitted `−5/3` line and the fit window shaded. (3) `L/η` vs `Re` log-log with the `3/4` reference slope.
- **Author attribution:** J. C. Harvey, Melbourne. The standard-FD result (Kolmogorov K41, the `−5/3` law, `C_K ≈ 1.5`, the microscale) is the CONVERGENCE target to *reproduce*, never an input to *borrow*.

## 10. Questions This Opens *(generative — log new ones in `FD04_VERDICT.md`)*

1. **Does the `1/r³` strain law that recurs in galactic line-kernels and tidal gradients literally equal the turbulent cascade's volume-conservation law?** If one strain exponent underlies both, FD04 ties turbulence to galactic dynamics through a single SDT conservation statement — a cross-domain test of the exponent's universality.
2. **Is the Kolmogorov constant `C_K ≈ 1.5` a derivable shell count** (the number of nested displacements per octave times a geometric factor), or irreducibly empirical? A derived `C_K` would lift FD04 from a clean exponent-derivation to a full prefactor-derivation.
3. **Is intermittency (anomalous higher-order scaling) an SDT-predicted correction** arising from the discreteness of the shell ledger, or genuinely OPEN? Do not fabricate a correction — but the lattice granularity is the natural place to look.
4. **Does the `ℓ_P` floor on the microscale predict a maximum achievable Reynolds number** for any real flow (`Re_max ∼ (L/ℓ_P)^{4/3}`)? That ceiling, though astronomically large, is an SDT-distinct statement absent from continuum K41.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FD04
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in the exponent chain (`C_K` is COMPUTED or PENDING, never silently fitted to 1.5)
- Engine namespaces actually used: law_I (P_conv, Φ/u_CMB), law_IV (V_disp→displaced volume), law_V (v_circ²+v_trans²=c² budget), bridge (koppa/z, the 1/r vs 1/r³ distinction); ν referenced from FD02
- Phase thresholds (committed before run):
    P1 `ε_n` constant to machine precision, `u_ℓ ∝ ℓ^{1/3}` (0.333 ± 0.02) · P2 analytic slope = −5/3 exact, numerical −1.667 ± 0.03 (kill if flux gives ≠ −5/3)
    P3 `L/η ∝ Re^{3/4}` (0.75 ± 0.05), deep-limit `η ≥ ℓ_P` · P4 measured slope −1.667 ± 0.05, `C_K` within 30% (COMPUTED) else PENDING · P5 intermittency OPEN or DERIVED-correction
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces; insert 5/3 or fit `C_K` to 1.5
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P2 flux argument yields exponent ≠ −5/3 | recheck the constant-flux closure on `{ε,k}` | **KILL** (clean — displacement cascade ≠ turbulent cascade) | retrofit the exponent to −5/3 |
| P3 deep-limit `η < ℓ_P` | recheck `ν → ν_lattice` and the `Re∼1` balance | **KILL** (lattice ontology violated) | floor `η` to `ℓ_P` by hand |
| P4 `C_K` not derivable from a shell count | flag `C_K` **PENDING/COMPUTED**, cap at C | **OPEN** the prefactor | silently fit `C_K` to 1.5 |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FD02 `ν`) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in the Phase-1 native chain · inserting the −5/3 exponent rather than deriving it.

---

*FD04 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
