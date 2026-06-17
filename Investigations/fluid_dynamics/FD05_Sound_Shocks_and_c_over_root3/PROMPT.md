# FD05 — Sound, Shocks, and the c/√3 Ceiling

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

*Inherits the §0 Anti-Creep Protocol and Rules R0–R5 of the SDT fluid-dynamics series in full force throughout.*

---

## 1. Executive Summary

Sound is a **compression relay wave** travelling through the spation lattice: a local densification of displaced lattice volume that the medium relays outward at the speed set by its own compressibility, `c_s = √(dP/dρ)`. This single mechanism is asked to carry three results. First, ordinary-fluid sound (air, ≈343 m/s) must fall out of the medium's **measured** compressibility, re-narrated as relay-wave propagation rather than borrowed acoustics. Second, the relativistic / radiation-fluid limit must recover the **maximal lattice sound speed `c_s = c/√3 ≈ 1.732×10⁸ m/s`** (the pre-Clearing coupled-lattice ceiling of CQ39) natively, as the high-stiffness asymptote of the same `√(dP/dρ)`. Third, a **shock** — the Mach cone and sonic boom — must be shown to be the *same* super-relay-speed disturbance as E57's verified Cherenkov radiation: one mechanism, two relay speeds. Falsify if any of the three fail to follow from compressibility alone.

## 2. Physical Context

A disturbance in a compressible medium propagates as a pressure wave whose speed is fixed by how stiffly the medium resists compression. In SDT the medium is the spation relay lattice (cell closure `ℓ_P`, signal/relay speed `c`), and "compression" means a transient increase in displaced lattice volume per unit region. The continuum fields of fluid dynamics are the coarse-graining of this granular relay (FD01/FD02).

Variables and dimensions:

| Symbol | Meaning | Dimensions / units |
|---|---|---|
| `P` | lattice (or fluid) pressure | Pa = kg m⁻¹ s⁻² |
| `ρ` | mass density (displaced-volume density) | kg m⁻³ |
| `c_s` | sound (compression-relay) speed | m s⁻¹ |
| `c` | relay tick / lattice signal speed | m s⁻¹ |
| `K = ρ dP/dρ` | bulk modulus (adiabatic) | Pa |
| `γ` | heat-capacity ratio (measured, ideal gas) | dimensionless |
| `R_g, T` | specific gas constant, temperature (measured) | J kg⁻¹K⁻¹, K |
| `u` | energy density (radiation: `u = a T⁴`) | J m⁻³ |
| `w = P/(ρc²)` | stiffness / equation-of-state ratio | dimensionless |
| `v` | source (matter) speed through lattice | m s⁻¹ |
| `M = v/c_s` | Mach number | dimensionless |
| `θ` | Mach-cone half-angle (`sinθ = c_s/v`) | rad |
| `δ` | shock thickness | m (∼ few mean free paths λ) |

Regimes span ≈12 orders of magnitude in `c_s`: cold neutral gas (`c_s ≪ c`, `w → 0`) up to the radiation-fluid ceiling (`c_s = c/√3`, `w = 1/3`). The continuum holds while disturbance wavelengths greatly exceed the lattice mean free path; at the shock front it breaks, and the discrete relay rate reasserts itself.

## 3. Theoretical Framework (SDT axioms only)

**Sound speed from compressibility.** A small density perturbation `ρ → ρ + δρ` raises the local lattice pressure by `δP = (dP/dρ) δρ`. Conservation of displaced volume (continuity) and the lattice momentum balance (FD01 Euler limit) combine into the standard linear wave equation `∂²(δρ)/∂t² = (dP/dρ) ∇²(δρ)`, whose characteristic speed is

```
        c_s = √(dP/dρ)            (adiabatic: c_s = √(K/ρ) = √(γ P/ρ))
```

This is asserted here as the lattice's compression-relay speed: the rate at which a densification heals back to equilibrium by relaying into neighbouring cells. For an ideal gas the measured equation of state gives `P = ρ R_g T`, hence `c_s = √(γ R_g T)`; `γ`, `R_g`, `T` are MEASURED-INPUT (the medium's compressibility), the relay narration is SDT-native.

**The c/√3 ceiling.** The lattice cannot relay faster than one cell per tick, so `c_s` is capped at `c`. The *maximal physical* sound speed, however, is set by the stiffest realisable equation of state — the radiation/relativistic fluid, in which the displaced-volume content is pure convergence throughput. Law I fixes the radiation pressure as one third of the energy density (isotropic pressure of an ultrarelativistic relay gas; `P_rad = u/3` at `laws.hpp` `law_I::P_rad = u_CMB/3.0`). For a relativistic fluid the inertia is the energy density, `ρ_eff c² = u`, so

```
        c_s² = dP/d(ρ_eff c²) = d(u/3)/du = 1/3   ⟹   c_s = c/√3 ≈ 1.732×10⁸ m/s
```

This is the same `c/√3` that CQ39 used as the coupled-lattice (pre-Clearing) BAO sound speed; FD05 *derives* it as the high-stiffness asymptote (`w = P/(ρc²) = 1/3`) of the single relation `c_s = √(dP/dρ)`. It is a ceiling, not a floor: ordinary fluids sit far below it because their `w ≪ 1/3`.

**Shock = super-relay disturbance (one mechanism with E57).** When a source moves through the lattice at `v > c_s`, the medium cannot relay the compression away ahead of the source: successive disturbance wavefronts (each expanding at `c_s`) pile up on a conical envelope. The half-angle is the relay-kinematics result

```
        sinθ = c_s / v = 1/M
```

This is structurally identical to E57's Cherenkov criterion (`cosθ_C = c_local / v`, a charge moving faster than the *local* relay/phase speed), differing only in *which* relay speed is exceeded — compression-relay `c_s` (sonic boom, Mach cone) versus phase-relay `c_local` (Cherenkov). The unification claim is: **both are the lattice's response to a disturbance forced past its local smoothing rate.** Across the shock the lattice jumps discontinuously because it cannot smooth across a region thinner than it can relay; the **Rankine–Hugoniot** jump conditions (conservation of mass/momentum/energy across the front) are then just the relay book-keeping of a discontinuity whose thickness `δ ∼ few × λ` (a few mean free paths), the smallest length over which the granular relay can re-equilibrate. No fields, no wavefunctions — only displaced-volume conservation, the relay tick, and the measured compressibility.

## 4. Investigation Strategy

Five phases. Each lists Goal / Method / quantitative Success. Forward-derive and log every number BEFORE comparing to the measured/standard-FD value (R1); standard-FD results are CONVERGENCE targets, never imported coefficients (R5).

### Phase 1 — Ordinary-fluid sound from compressibility
- **Goal:** recover air `c_s ≈ 343 m/s` (and one liquid, e.g. water ≈1481 m/s) as a compression-relay wave.
- **Method:** implement `c_s = √(dP/dρ)`; for air use `c_s = √(γ R_g T)` with `γ=1.4`, `R_g=287 J/kg/K`, `T=293 K` (MEASURED-INPUT); for water use measured bulk modulus `K`/`ρ`. Narrate each as relay healing, tag inputs.
- **Success:** air within ±1% of 343 m/s; water within ±5% of 1481 m/s; both tagged MEASURED-INPUT(γ,T,K) with SDT relay narration.

### Phase 2 — The c/√3 ceiling derived natively
- **Goal:** derive `c_s = c/√3` from `P_rad = u/3` and `ρ_eff c² = u` with no borrowed value.
- **Method:** evaluate `dP/d(ρ_eff c²) = 1/3` symbolically and numerically from `law_I::P_rad`; cross-check against the `c/√3` CQ39 used for BAO. Show the ordinary-fluid `c_s` (Phase 1) sits at `w ≪ 1/3`, on the same `c_s(w) = c√w` curve.
- **Success:** `c_s = 1.732×10⁸ m/s` to 4 sig figs; equals CQ39's coupled-lattice sound speed exactly; `c_s/c = 0.5774`.

### Phase 3 — Sound-speed vs stiffness: one curve from gas to radiation
- **Goal:** show ordinary sound and the radiation ceiling are endpoints of a single `c_s = c√w` relation.
- **Method:** tabulate `c_s(w)` for `w` from 10⁻¹² (cold gas) to 1/3 (radiation); overplot the air, water, and CQ39 points; verify monotonic approach to the ceiling and that nothing exceeds `c/√3` for `w ≤ 1/3`.
- **Success:** all real-fluid points lie on `c_s = c√w` within their input tolerance; the curve saturates at `c/√3`; no point exceeds the ceiling.

### Phase 4 — Mach cone and the shock criterion
- **Goal:** reproduce the Mach-cone angle `sinθ = c_s/v` over `M = 1.2 … 10` and the shock-onset condition `M = 1`.
- **Method:** compute `θ(M)` from relay kinematics; tabulate against textbook Mach-angle values; identify `M=1` as the relay-smoothing threshold; estimate shock thickness `δ ∼ 3–5 λ` from a measured mean free path (air λ ≈ 68 nm at STP).
- **Success:** `θ(M)` matches the textbook relation to <0.5° across the range; shock thickness predicted order-of-magnitude (tens of nm to ∼µm), consistent with measured shock-front widths.

### Phase 5 — Unify Cherenkov (E57) and the sonic boom
- **Goal:** demonstrate one shock mechanism behind both, distinguished only by the relevant relay speed.
- **Method:** place `sinθ = c_s/v` (boom) and `cosθ_C = c_local/v` (E57 Cherenkov) side by side; show both arise from "disturbance forced past local relay/smoothing rate"; state the single criterion `v > c_relay(mode)`. Confirm E57's VERIFIED Cherenkov angle is recovered as the special case `c_relay = c_local`.
- **Success:** a single written criterion reproduces both the Mach cone and E57's Cherenkov angle; no second mechanism, no extra parameter, required.

## 5. Success Criteria (canonical A–F)

- **A — PASS (native):** Phase 2 derives `c_s = c/√3` from `P_rad = u/3` with zero free parameters AND Phases 1,3,4 reproduce air `c_s`, the `c_s = c√w` curve, and the Mach-angle relation within tolerance, AND Phase 5 unifies boom + Cherenkov under one criterion.
- **C — QUALIFIED (convergence):** `c_s = √(dP/dρ)` reproduces measured sound speeds and the c/√3 ceiling, but one link (e.g. the shock-thickness coefficient, or the relativistic `ρ_eff c² = u` identification) is matched-by-convergence / CONVERGENCE-PENDING rather than coefficient-level native.
- **D — PENDING:** mechanism stated and dimensionally closed, but a phase is left numerically unexecuted (e.g. shock thickness only order-of-magnitude, Phase 5 stated not demonstrated).
- **F — FAIL:** `c_s` does not follow from compressibility, OR the `c/√3` limit cannot be recovered from `P=u/3`, OR Cherenkov and the sonic boom demonstrably require *different* mechanisms.

## 6. Outputs

- `fd05_sound_shocks.cpp` — standalone C++20 tool implementing Phases 1–5; consumes `law_I::P_rad`/`u_CMB`; no external dependencies; prints a formatted table + per-phase verdict.
- `fd05_results.txt` — run output: every computed quantity with value, units, input-class label (DERIVED / COMPUTED / MEASURED-INPUT / CONVERGENCE-PENDING), and the A–F verdict per phase.
- `FD05_DERIVATION.md` — the worked derivations: `c_s = √(dP/dρ)`, the `c/√3` ceiling from `P=u/3`, the `c_s = c√w` curve, the Mach-cone kinematics, and the boom↔Cherenkov unification.
- `FD05_VERDICT.md` — final A–F ledger, provenance block, impact on FD09 (form drag at high Mach) and FD08, and any OPEN items (never repaint a fired test).

## 7. Dependencies & References

**Upstream (required):** FD01 (Navier–Stokes / Euler continuum limit of the relay), FD02 (compressibility ↔ relay stiffness), **CQ39** (`c_s = c/√3`, BAO coupled-lattice sound speed), **E57** (Cherenkov radiation as a super-phase-speed lattice shock, VERIFIED).
**Engine hooks (`Engine/include/sdt/laws.hpp`):** `law_I` (`u_CMB`, `P_rad = u_CMB/3.0`, `P_conv`), `law_III` (occlusion force law), `law_V` (movement budget `v_circ² + v² = c²`), `bridge` (koppa, k, z). B16 (transport) for cross-reference.
**Downstream (unblocked):** **FD09** (form drag / wave drag at high Mach uses this shock criterion), **FD08** (compressible Bernoulli, related).
**Framework:** `Theory/00_Ruleset.md` (prohibitions), `Theory/05` audit spine (A–F), `Laws/SDT_Complete_Laws.md`.

## 8. Falsification Tests

| # | Test | SDT prediction | If it fails |
|---|---|---|---|
| F1 | Air sound speed from compressibility | `c_s = √(γR_gT) ≈ 343 m/s`, ±1% | `c_s = √(dP/dρ)` is not the lattice relay-wave speed; thesis dead |
| F2 | Radiation-fluid ceiling | `c_s = c/√3 = 1.732×10⁸ m/s` from `P=u/3`, 4 sig figs | the c/√3 limit is not native to `√(dP/dρ)`; CQ39 link broken |
| F3 | Single stiffness curve | all real fluids on `c_s = c√w`, none exceed `c/√3` for `w≤1/3` | sound and the radiation limit are unrelated; no unified compressibility law |
| F4 | Mach-cone angle | `sinθ = c_s/v = 1/M`, <0.5° vs textbook over `M=1.2–10` | shock geometry not relay-kinematic; "super-relay" picture wrong |
| F5 | Boom ↔ Cherenkov unification | one criterion `v > c_relay(mode)` recovers both, incl. E57's VERIFIED angle | sonic boom and Cherenkov need different mechanisms; unification claim falsified |

## 9. Implementation Notes

- Compile standalone: `cl /std:c++20 /EHsc /I Engine/include Investigations/fluid_dynamics/FD05_Sound_Shocks_and_c_over_root3/fd05_sound_shocks.cpp /Fe:fd05.exe` (MSVC); or `g++ -std=c++20 -I Engine/include …/fd05_sound_shocks.cpp -o fd05`.
- Pull `u_CMB` and `P_rad` from `sdt::laws::law_I`; do **not** redefine constants the header exposes. Tag every value DERIVED / COMPUTED / MEASURED-INPUT / CONVERGENCE-PENDING at first use.
- Keep `γ, R_g, T, K, λ` as clearly-labelled MEASURED-INPUT block at the top; the standard-FD sound speeds are the **convergence target**, never hard-coded as the answer.
- Plots (optional, gnuplot/matplotlib from `fd05_results.txt`): (i) `c_s` vs `w` on log–log with air/water/CQ39 points and the `c/√3` saturation line; (ii) Mach angle `θ` vs `M`; (iii) overlay of the boom envelope and the E57 Cherenkov cone showing the shared geometry.
- Author attribution in all generated files: James Christopher Tyndall, Melbourne.
