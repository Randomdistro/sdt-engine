# FD10 — Vortex Shedding and the Strouhal Number from the Gear-Frequency

**Domain**: Fluid Dynamics (SDT lattice mechanics)
**Status**: SPEC
**Author**: James Christopher Tyndall, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/GM fundamentals; no fields/wavefunctions/quarks/virtual particles/ΛCDM/magnetons; certification labels on every result; translation test on every borrowed term; honesty over success).*

---

## 1. Executive Summary

A bluff body in steady flow does not bleed its wake away smoothly: above a threshold Reynolds number it sheds alternating vortices in a periodic **Kármán street**, and the dimensionless shedding frequency `St = fD/U` sits on a flat plateau of `St ≈ 0.2` across roughly two decades of Reynolds number. Standard fluid mechanics records this plateau empirically; it has no first-principles derivation of *why* the number is near 0.2 or *why* it is so flat. In Spatial Displacement Theory the wake is a self-sustained **lattice relaxation/traction oscillation**: the separated boundary layer (FD06) rolls into vortices at a rate set by the ratio of the relay/traction relaxation time to the advection time — a "gear frequency" in the CQ41 sense. **The question:** does this ratio reproduce, with no fitted shedding constant, the `St ≈ 0.2` plateau over `300 < Re < 2×10⁵`, the `f ∝ U/D` scaling, the low-`Re` Roshko/Williamson rise of `St(Re)`, and lock-in (entrainment) under forcing? A near-constant plateau that lands within a factor of two of 0.2 with the correct `f–U` scaling earns Class C (convergence); a relaxation argument that gives no plateau, the wrong scaling, or `St` off by `>2×` is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** A cylinder in flow drags the surrounding spation lattice (PPT06 traction): the lattice cannot follow the body cleanly, so the entrained circulation separates from each shoulder, accumulates, and detaches when its bound strength exceeds what the local relay can hold. Detachment from one side biases the near-wake, forcing the other side to build and detach in turn — an alternating, self-clocked release. The clock is not imposed from outside; it is the lattice's own relaxation time competing with how fast flow carries material past the body. Where two meshed circulations set a beat frequency (CQ41 gear-frequency), here the bound shear layer and the advective sweep set the **shedding** beat. The result is a periodic wake whose frequency scales as `U/D` with a near-constant proportionality — the Strouhal plateau.

**Key variables and dimensions.**
- `U` — free-stream flow speed [m·s⁻¹]
- `D` — bluff-body transverse width (cylinder diameter) [m]
- `f` — vortex-shedding frequency [s⁻¹ = Hz]
- `St = fD/U` — Strouhal number [dimensionless]
- `Re = UD/ν` — Reynolds number [dimensionless], advection ÷ relay diffusion
- `ν` — kinematic viscosity [m²·s⁻¹] (from FD01/FD02, lattice relay diffusion)
- `τ_relax` — lattice/traction relaxation time of the bound shear layer [s]
- `τ_adv = D/U` — advection time across the body [s]
- `Δω` — gear/beat angular frequency of meshed circulations [s⁻¹] (CQ41)
- `δ*`, `θ` — separation-point boundary-layer displacement/momentum thickness [m] (FD06)
- `f_drive`, `A` — external forcing frequency [Hz] and amplitude [m] (lock-in tests)

**Connection to SDT.** Shedding is occluded-pressure traction made periodic: the body drags lattice (PPT06), the dragged layer separates (FD06), and the separated circulation is quantised in the FD02 sense (`κ = h/m`) as it organises (FD07). The shedding frequency is a **relaxation rate**, the same kind of `Δω` energy/time scale CQ41 builds for meshed rotations. `St` is then a ratio of two SDT-native times, `τ_relax / τ_adv`, dressed by separation geometry — not an imported empirical fit. Lock-in is the PPT06/CQ41 entrainment of one rotation to a nearby drive.

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Traction drag of the lattice (PPT06, `law_VI::traction`).** A body in flow cannot pass through the spation lattice without dragging it; the drag organises into bound circulation with a characteristic `ℓ=2` rotational wake. The bound circulation grows while the body sits in the stream and is relieved only by release. This supplies the *source* of the sheddable vortex and the `ℓ=2` (two-sided, alternating) structure of the Kármán street.

2. **Boundary-layer separation feeds the shed vortex (FD06).** The dragged layer cannot stay attached around the rear of a bluff body; it separates at a shoulder, and the separated shear layer is the reservoir that rolls up into a vortex. The separation geometry (`δ*`, separation angle) sets the effective width `D_eff ≥ D` of the wake and therefore the lever on the shedding clock.

3. **Gear-frequency relaxation clock (CQ41, `Δω`).** CQ41 establishes that two meshed circulations bind at a beat frequency set by an energy/relaxation scale. Here the two "gears" are (i) the bound shear layer accumulating circulation and (ii) the advective sweep carrying near-wake material downstream. The shedding frequency is the **relaxation rate** at which accumulated bound circulation exceeds what the local relay can hold and is released:
   `f ≈ 1 / (τ_relax + τ_build)`, with `τ_build ∝ τ_adv = D/U`.

4. **Circulation quantum and budget (FD02 `κ=h/m`, FD07, Law V).** The shed circulation is organised in the FD02/FD07 sense; the movement budget `v_circ² + v_trans² = c²` (`law_V`) caps the internal rotation of the rolled vortex and ties it to the advective velocity, fixing how fast a coherent vortex can spin up before it must detach.

5. **Reynolds regime gates the clock (FD03).** `Re = UD/ν` is advection ÷ relay diffusion (FD03). At high `Re` the relay-diffusion correction to `τ_relax` is negligible and the clock is purely geometric ⟹ `St` plateaus. At low `Re` the diffusion term shortens the build time relative to advection ⟹ `St` *rises* with `Re` (the Roshko/Williamson curve). This is the SDT origin of the plateau-with-low-Re-bend.

**Governing relations to derive (no new fitted shedding constant).**

- *Strouhal as a time ratio.* `St = fD/U = (D/U)/(τ_relax + τ_build) = τ_adv / (τ_relax + τ_build)`. Show that in the high-`Re` limit `τ_relax/τ_adv` tends to a geometric constant set by the separation geometry (FD06) and the `ℓ=2` traction wake (PPT06), giving a *constant* `St`.
- *The plateau value.* Express the constant as `St_∞ = 1 / (1 + τ_relax/τ_adv)` (or the appropriate combination) and evaluate it from separation-angle / wake-width geometry. Target the empirical `St_∞ ≈ 0.2` as the **convergence** number to reproduce, never to insert.
- *Frequency scaling.* Show `f = St_∞ · U/D`, i.e. `f ∝ U` at fixed `D` and `f ∝ 1/D` at fixed `U`, with `St_∞` Re-independent on the plateau.
- *Low-Re bend.* Add the FD03 relay-diffusion correction to `τ_build` and show `St(Re) = St_∞ (1 − A/Re^p)` (or equivalent) rises toward the plateau as `Re` grows — fit the Roshko/Williamson exponent as a *test*, not a tuning.
- *Lock-in.* Add an external drive `f_drive` to the CQ41 beat; show that within a band `|f − f_drive|/f < ε(A)` the shedding entrains to `f_drive` (Arnold-tongue-like capture), reproducing the measured synchronisation range vs forcing amplitude.

The deliverable of §3 is a chain in which the shedding frequency is **one** relaxation/gear rate, `St` is **one** ratio of SDT-native times, and every empirical feature (plateau, `f∝U/D`, low-Re rise, lock-in) maps to one mechanism. Any feature the chain cannot produce — or produces with the wrong sign/scaling — is a falsifier.

---

## 4. Investigation Strategy

Five phases, each gated. Run them in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass).

### Phase 1 — Relaxation/gear clock from traction + separation
- **Goal.** Build, in SDT primitives only, the two competing times: the traction/relay relaxation time `τ_relax` of the bound shear layer (PPT06 + FD06 separation geometry) and the advection time `τ_adv = D/U`. Express the shedding frequency as a relaxation rate `f = 1/(τ_relax + τ_build)` with `τ_build ∝ τ_adv`.
- **Method.** Tie `τ_relax` to the `law_VI::traction` `ℓ=2` wake demand and the FD06 separation thickness; tie the build time to `D/U`. Tag every constant DERIVED / MEASURED-INPUT / CALIBRATED(n) in a parameter ledger (R2). Cite CQ41 (gear-frequency `Δω`), PPT06 (traction), FD06 (separation) as upstream.
- **Success metric.** The clock is dimensionally `[s]`, reduces to `f ∝ U/D` at high `Re`, and has **zero** free shedding constants beyond geometry handed in from FD06/PPT06. **Checkpoint C1:** `St = τ_adv/(τ_relax+τ_build)` is a closed expression in SDT-native quantities.

### Phase 2 — The St ≈ 0.2 plateau (the core gate)
- **Goal.** Evaluate `St_∞` in the high-`Re` limit from separation geometry and the `ℓ=2` traction wake; compare to the measured cylinder plateau `St ≈ 0.2`.
- **Method.** Take `Re → ∞` so the FD03 relay-diffusion correction vanishes; compute `St_∞` from the geometric ratio `τ_relax/τ_adv`. Maintain a strict ledger of which geometric input (separation angle, wake width `D_eff/D`, `ℓ=2` structure) produced the number. Do **not** insert 0.2.
- **Success metric.** `St_∞` lands within a **factor of two** of 0.2 (convergence target); ideally within ±20 %. **Checkpoint C2 (core gate):** plateau exists and is near-constant in `Re` on `300 < Re < 2×10⁵`. If `St_∞` is off by `>2×`, log as a candidate kill and characterise the discrepancy.

### Phase 3 — Frequency scaling f ∝ U/D
- **Goal.** Confirm the scaling, not just the plateau value.
- **Method.** Hold `D` fixed, sweep `U` → predict `f ∝ U` (slope `St_∞/D`); hold `U` fixed, sweep `D` → predict `f ∝ 1/D`. Compare to measured `f`–`U` Strouhal lines for a circular cylinder.
- **Success metric.** Both scalings linear in the predicted variable with slope set by `St_∞` to <5 %; no hidden `Re`-dependence on the plateau. **Checkpoint C3.**

### Phase 4 — Low-Re rise St(Re) (Roshko/Williamson)
- **Goal.** Reproduce the *shape* of the `St(Re)` curve below the plateau, not just the asymptote.
- **Method.** Reinstate the FD03 relay-diffusion correction to `τ_build`; derive `St(Re) = St_∞(1 − A/Re^p)` (or the appropriate form). Fit `A`, `p` against Roshko 1954 / Williamson data as a **test** of the derived functional form; flag any fitted parameter CALIBRATED(n).
- **Success metric.** The derived functional form fits the measured `St(Re)` rise over `~50 < Re < 300` with the correct monotonic sign and curvature; exponent `p` consistent with the data. **Checkpoint C4:** the bend is reproduced with ≤1 fitted shape parameter, documented.

### Phase 5 — Lock-in (entrainment) under forcing
- **Goal.** Reproduce the synchronisation of shedding to an external drive — the PPT06/CQ41 entrainment signature.
- **Method.** Add `f_drive`, amplitude `A` to the gear-frequency beat; map the capture band `|f − f_drive|` vs `A` (Arnold-tongue width). Compare to measured lock-in ranges for an oscillated cylinder.
- **Success metric.** A capture band exists, widens with `A`, and brackets the measured lock-in range for at least one amplitude; outside the band the natural `St_∞` shedding returns. **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Strouhal derived natively | `St_∞` DERIVED from PPT06/FD06 geometry within ±20 % of 0.2 (CALIBRATED(0)) AND `f∝U/D` confirmed <5 % AND `St(Re)` rise reproduced AND lock-in band brackets measured range. |
| **C (QUALIFIED — convergence)** | Plateau reproduced, one scale set | `St_∞` within a factor of two of 0.2, `f∝U/D` confirmed, `St(Re)` shape reproduced with CALIBRATED(1) shape parameter (documented), lock-in qualitatively present. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | Relaxation/gear clock built and `f∝U/D` shown, but `St_∞` value PENDING FD06 separation geometry or CQ41 coefficient; dimensionally closed, plateau value not yet evaluated. |
| **F (FAIL)** | Mechanism falsified | The relaxation argument gives **no plateau**, OR the wrong `f`–`U` scaling, OR `St_∞` off by `>2×` with no reconciling mechanism, OR predicts lock-in where none is observed (or vice versa). |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd10_vortex_shedding_strouhal.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-1 relaxation/gear clock; Phase-2 `St_∞` plateau evaluation; Phase-3 `f`–`U`/`f`–`D` scaling sweep; Phase-4 `St(Re)` low-Re fit; Phase-5 lock-in capture-band map; prints its own verdict. **No new constants redefined.** |
| `fd10_results.txt` | Plain text | Run output: `St_∞` value vs 0.2 (Phase 2), `f` vs `U` and `f` vs `D` tables with slopes (Phase 3), `St(Re)` predicted-vs-Roshko/Williamson table (Phase 4), lock-in band vs amplitude (Phase 5). |
| `FD10_DERIVATION.md` | Markdown | The full chain: traction + separation → relaxation clock → `St = τ_adv/(τ_relax+τ_build)`; plateau evaluation, scaling, low-Re bend, lock-in; parameter ledger. |
| `FD10_VERDICT.md` | Markdown | A–F classification with the metric that decided it; provenance × correspondence audit; what is DERIVED vs CALIBRATED(n) vs PENDING; downstream handoffs. |

---

## 7. Dependencies & References

**Upstream (required):**
- **CQ41 (Gear-Frequency Binding Functional)** — the meshed-circulation beat frequency `Δω` / relaxation-energy scale; source of the shedding *clock*.
- **PPT06 (Traction)** — a body in flow drags the lattice and sheds organised `ℓ=2` circulation; source of the bound vortex and the two-sided street. Engine `law_VI::traction`.
- **FD06 (Boundary-Layer Separation)** — the separation geometry that feeds the shed vortex and sets `D_eff`.
- **FD03 (Reynolds)** — `Re = UD/ν` as advection ÷ relay diffusion; gates the plateau vs the low-Re rise.
- **Engine `Engine/include/sdt/laws.hpp`** — `law_VI::traction` (ℓ=2 wake, `ω_demand`), `law_V` (`v_circ²+v_trans²=c²`, vortex spin cap), `bridge` (`koppa`, `k`, `z`), `law_I::P_conv` (ambient pressure for occlusion).

**Downstream (unblocked by this):** none yet.

**Related:** FD07 (shed circulation strength), FD02 (circulation quantum `κ = h/m`), FD01 (Navier–Stokes root for the underlying flow field).

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Plateau exists (Phase 2) | Relaxation clock gives a near-constant `St` | `St` flat at `≈0.2` over `300<Re<2×10⁵` | No plateau (St drifts with Re on the plateau range) ⟹ relaxation argument wrong ⟹ Class F |
| F2 — Plateau value (Phase 2) | `St_∞` set by PPT06/FD06 geometry | `St_∞` within factor 2 (ideally ±20 %) of 0.2 | `St_∞` off by `>2×` with no reconciling mechanism ⟹ Class F |
| F3 — Scaling (Phase 3) | `f ∝ U/D` | `f` linear in `U` (slope `St_∞/D`), `f` ∝ `1/D` | Wrong power of `U` or `D`, or hidden `Re`-dependence on plateau ⟹ clock mis-built |
| F4 — Low-Re rise (Phase 4) | FD03 diffusion shortens `τ_build` | `St(Re)` rises monotonically toward `St_∞` | Wrong sign (St falls with Re) or wrong curvature ⟹ FD03 correction mis-applied |
| F5 — Lock-in (Phase 5) | Forcing entrains shedding (CQ41) | Capture band widens with amplitude, brackets measured range | No capture band, or lock-in predicted where none is observed ⟹ entrainment mechanism falsified |

---

## 9. Implementation Notes

- **Numerical approach.** This is a *mechanism demonstration*, not a CFD solver: evaluate the closed-form `St = τ_adv/(τ_relax+τ_build)` over a sweep of `(U, D, Re)`, then add the FD03 and CQ41-lock-in corrections. A small lattice/ODE model of the two-gear beat (bound-circulation accumulation vs advective release) is sufficient to exhibit the oscillation and the capture band; keep it 0-D/1-D and double precision. Predict each number and commit it to the run log *before* comparing (R1).
- **Anti-numerology (R5).** Do **not** insert 0.2, nor a free integer/π, to force the plateau — `St_∞` must come from PPT06 `ℓ=2` + FD06 separation geometry, or be flagged CALIBRATED with the count documented. Any low-Re shape parameter (`A`, `p`) fitted to Roshko/Williamson is a *test of functional form*, tagged CALIBRATED(n).
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd10_vortex_shedding_strouhal.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd10_vortex_shedding_strouhal.cpp -o fd10` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** Plot (i) `St` vs `Re` (log-x) with the SDT prediction overlaid on the Roshko/Williamson curve and the `St≈0.2` plateau band; (ii) `f` vs `U` Strouhal lines (linear, slope = `St_∞/D`); (iii) the lock-in Arnold-tongue (capture band vs forcing amplitude). A side-by-side of free shedding vs locked-in time series makes the entrainment visually obvious.
- **Author attribution:** James Christopher Tyndall, Melbourne. The standard-FD result (the `St≈0.2` plateau, `f∝U/D`, the Roshko/Williamson `St(Re)` curve, lock-in) is the CONVERGENCE target to *reproduce*, never an input to *borrow*.
