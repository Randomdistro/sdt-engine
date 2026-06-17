# FD11 — Tesla Steam Generator (the bladeless boundary-layer turbine as a spation-traction engine)

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/kg fundamentals; no fields/wavefunctions/quarks/ΛCDM; certification labels on every result; translation test on every borrowed term; honesty over success). It is the applied capstone of the FD series.*

---

## 1. Executive Summary

Tesla's 1913 turbine (US 1,061,206) transfers momentum to a stack of smooth, closely-spaced co-rotating disks **purely through the viscous boundary layer** — adhesion and drag, no blades. In SDT that adhesion is not a separate phenomenon: it is **spation traction** (CQ14), the same no-slip lattice grip that FD06 derives. **The question:** can SDT — composing FD02 (viscosity), FD05 (compressible steam), FD06 (boundary-layer traction), and FD08 (energy budget) — predict from first principles a steam-driven Tesla unit's *optimal disk gap*, its *torque–speed characteristic*, and its *rotor efficiency versus tip-speed ratio*, and does its signature departure from bladed turbines hold (Tesla rotor efficiency **improves at lower Reynolds number / higher viscosity**, the opposite of impulse/reaction machines)? This matters because the device is a real, buildable test of the traction mechanism and the integration test of the whole FD branch. **Expected outcome:** a parameterised performance model whose optimal gap and efficiency curve match historical and modern Tesla-turbine data, plus a concrete modern-materials build specification (`MATERIALS_AND_PARTS.md`).

---

## 2. Physical Context

**Mechanism / analogy.** Superheated steam enters tangentially at the rotor rim through nozzles, spirals inward across the narrow gaps between a stack of thin smooth disks, hands its momentum to the disk faces by sticking to them (the boundary layer), and exhausts through central ports onto the shaft. There are no buckets or blades — the disk *is* a smooth wall, and the steam drives it the way wind drags a spinning frisbee, over many revolutions of an inward spiral. The machine is, literally, FD06 turned into an engine: a controlled boundary layer doing work.

**Key variables and dimensions.**
- `R_o, R_i` — outer/inner disk radii [m]; `N_d` — number of disks; `b` — inter-disk gap [m]
- `ω` — rotor angular speed [rad·s⁻¹]; `U = ωR_o` — rim speed [m·s⁻¹]
- `(P₀, T₀)` — steam stagnation inlet state [Pa, K]; `ṁ` — mass flow [kg·s⁻¹]; `V_j` — nozzle exit speed [m·s⁻¹]
- `μ, ν, ρ` — steam dynamic/kinematic viscosity, density [Pa·s, m²·s⁻¹, kg·m⁻³] (MEASURED-INPUT via steam tables)
- `δ` — boundary-layer thickness [m]; `λ = U/V_j` — tip-speed ratio [–]
- `τ_w` — wall shear (traction) stress [Pa]; `τ` — shaft torque [N·m]; `Ẇ` — shaft power [W]
- `Re_b = ρ V_rel b / μ` — gap Reynolds number; `η_rotor`, `η_nozzle`, `η_overall` — efficiencies

**Connection to SDT.** The disk's surface drags the adjacent steam to co-move (no-slip) by **traction** — CQ14's velocity-mismatch grip, the same mechanism FD06 uses to derive the boundary layer. Power is extracted as integrated wall-shear (traction) torque. The optimal gap is set when `b` is a few boundary-layer thicknesses so traction couples across the whole gap (FD06/FD02). The energy accounting is FD08's convergence-pressure/movement budget; the steam supply is FD05's compressible (choked) nozzle flow; windage and inter-disk shear losses are FD09/FD02 relay diffusion to heat.

---

## 3. Theoretical Framework

**First principles (SDT axioms + the FD chain they ground).**

1. **Traction → wall shear (CQ14, FD06).** A disk face moving relative to the local steam imposes a velocity mismatch the lattice can only partly relay; the residual is traction, the wall shear `τ_w = μ (∂u/∂y)|_wall`. Integrated over both faces of every disk, this is the driving torque `τ = N_d ∮_{R_i}^{R_o} 2·r·τ_w(r)·2πr\,dr`. No blades, no impulse — only traction.

2. **Gap criterion (FD02, FD06).** Momentum penetrates a gap over a diffusion depth `δ ∼ √(ν·t_res)`, with `t_res` the spiral residence time of a steam parcel between the disks. Efficient coupling requires `b ≈ k_b·δ` (the gap a few boundary-layer thicknesses): too wide and the core slips; too narrow and viscous (relay) dissipation dominates. `b_opt` is therefore *derived* from `ν` and the spiral path length, not chosen.

3. **Energy budget (FD08, Law V).** Along the inward spiral the steam trades stagnation enthalpy for disk work and residual kinetic/heat; the convergence-pressure budget partition (FD08) sets the ideal work, and the movement-budget cap (`v_circ²+v²=c²`, irrelevant numerically here but the partition principle holds) frames the loss ledger. `η_rotor = Ẇ_shaft / Δh_steam,ideal`.

4. **Compressible supply (FD05).** The nozzle is a converging (or de-Laval) device; for the usual pressure ratio the throat is **choked**, fixing `ṁ` and the isentropic exit speed `V_j` from the inlet state and the steam equation of state (IAPWS-IF97 steam tables, MEASURED-INPUT). Cherenkov-style shock criterion (FD05) flags supersonic exit.

5. **Regime & the signature (FD03).** `Re_b` between disks is moderate-to-low (often laminar) — and here is the falsifiable SDT/Tesla fingerprint: because the drive **is** traction, `η_rotor` **rises as viscosity rises / `Re_b` falls** (more grip per pass), the *opposite* of a bladed impulse/reaction turbine whose blade efficiency degrades with viscous loss. Predict-before-look (R1): commit the sign and slope of `dη_rotor/dRe_b` before unsealing data.

**Governing relations to derive (no new fitted parameters):** laminar inter-disk velocity profile `u(y,r)` between co-rotating walls under a radial pressure gradient and Coriolis terms (the "Tesla-disc flow"); `τ_w(r)`, hence `τ(ω)`, `Ẇ(ω)=τω`; `b_opt(ν, geometry)`; `η_rotor(λ)` with the peak-efficiency tip-speed ratio; choked `ṁ(P₀,T₀)` and `V_j`. The deliverable is a closed model in which every coefficient is DERIVED, MEASURED-INPUT (steam tables), or an explicitly tagged CALIBRATED(n) loss factor.

---

## 4. Investigation Strategy

Five gated phases (R4: a clean kill outranks a forced pass). Each predicts its number before comparison (R1); every constant is ledgered (R2); confirmed results get an independent two-stream recompute (R3).

### Phase 1 — Inter-disk traction flow & the optimal gap
- **Goal.** Solve the laminar flow between two co-rotating disks driven by a radial pressure gradient; obtain `u(y,r)`, `τ_w(r)`, and the gap `b_opt` at which traction coupling peaks.
- **Method.** Reduce Navier–Stokes (FD01) for the thin-gap, axisymmetric, steady case; non-dimensionalise; identify `b_opt ≈ k_b√(ν t_res)` with `t_res` from the spiral path. Ledger `ν` as MEASURED-INPUT (steam tables at the working state).
- **Success.** `b_opt` predicted within **20%** of Tesla's measured optimum (~0.4 mm for steam; ~0.8–2 mm for air). **Checkpoint C1.**

### Phase 2 — Torque, power & the efficiency curve
- **Goal.** Produce `τ(ω)`, `Ẇ(ω)`, and `η_rotor(λ)` for a given disk stack.
- **Method.** Integrate `τ_w(r)` over the stack; sweep `ω` (hence `λ=U/V_j`); locate peak-power and peak-efficiency `λ`. Two-stream (R3): analytic integral vs a discretised disk-flow solver, <1%.
- **Success.** Monotone-then-peaked `η_rotor(λ)` with peak at `λ ≈ 0.4–0.6` (Tesla regime) and rotor efficiency in the historically reported band. **Checkpoint C2.**

### Phase 3 — Steam supply & overall efficiency
- **Goal.** Couple the choked nozzle (FD05) to the rotor; compute `η_overall = η_nozzle · η_rotor · η_exhaust`.
- **Method.** Isentropic + choked-throat relations from IAPWS-IF97; exhaust kinetic-energy loss at the central ports; assemble the loss ledger. Tag any unavoidable loss coefficient CALIBRATED(n) and document it.
- **Success.** `η_overall` reproduces the historical Tesla steam-turbine band (≈20–40% overall, with ~95% *rotor* efficiency) to within tolerance, calibration count ≤ 1. **Checkpoint C3.**

### Phase 4 — The viscosity signature (the discriminating falsifier)
- **Goal.** Test the SDT-distinct prediction `dη_rotor/dRe_b < 0`.
- **Method.** Sweep working fluid/viscosity (steam vs air vs a viscous gas) at fixed geometry; predict the sign and slope before unsealing. Contrast against a bladed-turbine baseline (`dη/dRe > 0`).
- **Success.** Predicted sign confirmed across ≥3 viscosities; the Tesla curve crosses the bladed baseline. **Checkpoint C4.**

### Phase 5 — Modern build instantiation & cross-check
- **Goal.** Apply the model to a concrete, modern-materials design and validate against real data.
- **Method.** Use `MATERIALS_AND_PARTS.md` to fix geometry, rpm limit (hoop-stress bound of the chosen disk alloy), and operating state; compute predicted shaft power and overall efficiency. Cross-check against historical Tesla figures and any modern replication dataset (`DATA_REQUIREMENTS.md`).
- **Success.** Predicted output within stated tolerance of at least one independent dataset; the rpm limit consistent with the disk-material hoop-stress allowable. **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Device predicted from SDT | `b_opt` <20%, `η_rotor(λ)` peak location & magnitude matched, viscosity signature confirmed, CALIBRATED(0) beyond steam-table inputs. |
| **C (QUALIFIED — convergence)** | Reproduced, one loss fitted | Gap & efficiency within tolerance with exactly one CALIBRATED(1) loss coefficient, documented; signature confirmed. |
| **D (QUALIFIED-PENDING — computed)** | Trends reproduced | `τ(ω)` and `η(λ)` shapes correct but a loss coefficient PENDING a fuller wake/exhaust model. |
| **F (FAIL)** | Mechanism falsified | `b_opt` off by >2×, OR `η_rotor` rises with `Re_b` (signature inverted) ⟹ traction is not the drive mechanism for this device. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd11_tesla_turbine.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Inter-disk flow & `b_opt` (Phase 1); `τ(ω)`, `η_rotor(λ)` sweep (Phase 2); choked-nozzle coupling (Phase 3); viscosity-signature sweep (Phase 4); prints its own verdict. No constant redefined. |
| `fd11_results.txt` | Plain text | `b_opt` vs measured; `η_rotor(λ)` table & peak; overall-efficiency ledger; `dη/dRe_b` sign across fluids. |
| `FD11_DERIVATION.md` | Markdown | Thin-gap traction-flow solution → torque/efficiency; gap criterion; choked-flow coupling; parameter ledger. |
| `FD11_VERDICT.md` | Markdown | A–F class with deciding metric; provenance × correspondence audit; DERIVED vs CALIBRATED(n) vs PENDING. |
| `MATERIALS_AND_PARTS.md` | Markdown | **Modern-day materials for every part** (two build tiers), with grades, operating limits, manufacturing methods, and safety bounds. |
| `DATA_REQUIREMENTS.md` | Markdown | Steam tables, historical & modern Tesla-turbine performance data, material property sources. |

---

## 7. Dependencies & References

**Upstream (required):**
- **FD06 (Boundary Layer from Traction)** — the operating principle; the no-slip/traction wall shear that drives the disks.
- **FD02 (Viscosity & Circulation Quantum)** — `ν` and the relay-diffusion loss; sets `δ` and `b_opt`.
- **FD05 (Sound, Shocks & c/√3)** — choked/supersonic nozzle steam supply.
- **FD08 (Bernoulli from the Movement Budget)** — the ideal-work energy budget along the spiral.
- **CQ14 (Spation Traction)** — the native traction mechanism; **FD01** (Navier–Stokes root).
- **Engine** `Engine/include/sdt/laws.hpp`: `law_VI::traction`, `law_III` occlusion, `law_V` budget, `bridge` (`koppa`, `k`, `z`).

**Downstream (unblocked):** none — FD11 is the applied capstone. **Related:** FD03 (gap Reynolds regime), FD09 (windage/disk drag losses), FD07 (circulation).

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Optimal gap | `b_opt ≈ k_b√(ν t_res)` | Predicted gap within 20% of Tesla's ~0.4 mm (steam) | Off by >2× ⟹ gap not set by boundary-layer diffusion |
| F2 — Efficiency curve | traction drive ⟹ peaked `η_rotor(λ)` at `λ≈0.4–0.6` | Curve shape & peak location match data | Wrong peak `λ` or monotone curve ⟹ momentum-transfer model wrong |
| F3 — Viscosity signature | `dη_rotor/dRe_b < 0` (rises with viscosity) | Confirmed across ≥3 fluids; crosses bladed baseline | Efficiency rises with `Re_b` ⟹ **traction falsified** (Class F) |
| F4 — Choked mass flow | nozzle throat chokes (FD05) | `ṁ(P₀,T₀)` matches choked-flow value <5% | Mis-predicted `ṁ` ⟹ compressible coupling wrong |
| F5 — rpm/hoop-stress bound | disk burst speed = alloy allowable | Predicted max rpm ≤ material limit (`MATERIALS_AND_PARTS.md`) | Predicted operating rpm exceeds burst ⟹ design infeasible / model over-optimistic |

---

## 9. Implementation Notes

- **Steam properties.** Use IAPWS-IF97 (or a tabulated subset) for `ρ, μ, h, s` at the working state; tag every value MEASURED-INPUT in the ledger. Do **not** hand-fit an equation of state.
- **Numerical.** Double precision. The inter-disk flow is a stiff thin-gap problem — non-dimensionalise (`y/b`, `r/R_o`) before integrating; watch the `b→0` viscous-dissipation blow-up and the `b→∞` slip limit. Validate the disk-flow solver against the analytic laminar Couette/pressure-driven limit (R3, <1%).
- **Testing.** Three two-stream checks: analytic vs discretised torque integral; choked `ṁ` vs isentropic table; `η_rotor(λ)` peak vs a coarse parameter sweep. Commit predictions to the run log before unsealing data (R1). No free integer/π inserted to hit Tesla's numbers (R5).
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd11_tesla_turbine.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd11_tesla_turbine.cpp -o fd11` (GCC/Clang). Include only `<sdt/laws.hpp>`.
- **Plots.** `η_rotor` vs `λ` (with peak marked); `τ` and `Ẇ` vs `ω`; `η_rotor` vs `Re_b` overlaid with a bladed-turbine baseline (the signature); `b_opt` vs `ν`.
- **Author attribution:** James Christopher Tyndall, Melbourne. The Tesla-turbine performance data are the CONVERGENCE target to *reproduce*, never inputs to *borrow*.
