# FD10 — Vortex Shedding and the Strouhal Number from the Gear-Frequency

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Why does the vortex-shedding Strouhal number sit on a flat plateau `St ≈ 0.2` across ~two decades of Reynolds number — can the SDT relaxation/traction clock (`St = τ_adv/(τ_relax + τ_build)`) reproduce both the plateau *value* and its *flatness* with no fitted shedding constant?
2. **Why does it matter?** — Standard fluid mechanics records the `St ≈ 0.2` plateau empirically with no first-principles account; if it is one ratio of two SDT-native times (relaxation vs advection), the plateau, the `f ∝ U/D` scaling, the low-Re Roshko/Williamson rise, and lock-in all follow from one mechanism. It is the capstone wiring of PPT06 (traction), FD06 (separation), and FD03 (Re regime).
3. **How will we find out?** — Five gated phases (§④). **Honesty up front:** the relaxation/advection ratio carries a dimensionless clock constant (call it `k_clock`); if it must be set to land 0.2 it is **CALIBRATED(1)** and the grade caps at C — the plateau *flatness* and the `f∝U/D` scaling remain the genuinely-predictive content even when the value is calibrated.
4. **What would prove us wrong?** — §⑧, five falsifiers with real failure modes: the clock giving *no* plateau (St drifts with Re on the plateau range); the wrong `f`–`U` power; `St_∞` off by >2× with no reconciling geometry; the low-Re curve bending the wrong way; or lock-in predicted where none is observed.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

**Domain**: Fluid Dynamics (SDT lattice mechanics) · **Status**: SPEC · **Author**: J. C. Harvey, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/GM fundamentals; no fields/wavefunctions/quarks/virtual particles/ΛCDM/magnetons; certification labels on every result; translation test on every borrowed term; honesty over success).*

---

## 1. Executive Summary

A bluff body in steady flow does not bleed its wake away smoothly: above a threshold Reynolds number it sheds alternating vortices in a periodic **Kármán street**, and the dimensionless shedding frequency `St = fD/U` sits on a flat plateau of `St ≈ 0.2` across roughly two decades of Reynolds number. Standard fluid mechanics records this plateau empirically; it has no first-principles derivation of *why* the number is near 0.2 or *why* it is so flat. In Spatial Displacement Theory the wake is a self-sustained **lattice relaxation/traction oscillation**: the separated boundary layer (FD06) rolls into vortices at a rate set by the ratio of the relay/traction relaxation time to the advection time — a "gear frequency" in the NP06 (Gear-Frequency Binding Functional) sense. **The question:** does this ratio reproduce, with no fitted shedding constant, the `St ≈ 0.2` plateau over `300 < Re < 2×10⁵`, the `f ∝ U/D` scaling, the low-`Re` Roshko/Williamson rise of `St(Re)`, and lock-in (entrainment) under forcing? A near-constant plateau that lands within a factor of two of 0.2 with the correct `f–U` scaling earns Class C (convergence); a relaxation argument that gives no plateau, the wrong scaling, or `St` off by `>2×` is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** A cylinder in flow drags the surrounding spation lattice (PPT06 traction): the lattice cannot follow the body cleanly, so the entrained circulation separates from each shoulder, accumulates, and detaches when its bound strength exceeds what the local relay can hold. Detachment from one side biases the near-wake, forcing the other side to build and detach in turn — an alternating, self-clocked release. The clock is not imposed from outside; it is the lattice's own relaxation time competing with how fast flow carries material past the body. Where two meshed circulations set a beat frequency (NP06 gear-frequency binding functional), here the bound shear layer and the advective sweep set the **shedding** beat. The result is a periodic wake whose frequency scales as `U/D` with a near-constant proportionality — the Strouhal plateau.

**Key variables and dimensions.**
- `U` — free-stream flow speed [m·s⁻¹]
- `D` — bluff-body transverse width (cylinder diameter) [m]
- `f` — vortex-shedding frequency [s⁻¹ = Hz]
- `St = fD/U` — Strouhal number [dimensionless]
- `Re = UD/ν` — Reynolds number [dimensionless], advection ÷ relay diffusion
- `ν` — kinematic viscosity [m²·s⁻¹] (from FD01/FD02, lattice relay diffusion)
- `τ_relax` — lattice/traction relaxation time of the bound shear layer [s]
- `τ_adv = D/U` — advection time across the body [s]
- `Δω` — gear/beat angular frequency of meshed circulations [s⁻¹] (NP06)
- `k_clock` — dimensionless relaxation-clock constant in `St = τ_adv/(τ_relax+τ_build)` [–]; DERIVED or CALIBRATED(1)
- `δ*`, `θ` — separation-point boundary-layer displacement/momentum thickness [m] (FD06)
- `f_drive`, `A` — external forcing frequency [Hz] and amplitude [m] (lock-in tests)

**Connection to SDT.** Shedding is occluded-pressure traction made periodic: the body drags lattice (PPT06), the dragged layer separates (FD06), and the separated circulation is quantised in the FD02 sense (`κ = h/m`) as it organises (FD07). The shedding frequency is a **relaxation rate**, the same kind of `Δω` energy/time scale NP06 builds for meshed rotations. `St` is then a ratio of two SDT-native times, `τ_relax / τ_adv`, dressed by separation geometry — not an imported empirical fit. Lock-in is the PPT06/NP06 entrainment of one rotation to a nearby drive.

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Traction drag of the lattice (PPT06, `law_VI::traction`).** A body in flow cannot pass through the spation lattice without dragging it; the drag organises into bound circulation with a characteristic `ℓ=2` rotational wake. The bound circulation grows while the body sits in the stream and is relieved only by release. This supplies the *source* of the sheddable vortex and the `ℓ=2` (two-sided, alternating) structure of the Kármán street.

2. **Boundary-layer separation feeds the shed vortex (FD06).** The dragged layer cannot stay attached around the rear of a bluff body; it separates at a shoulder, and the separated shear layer is the reservoir that rolls up into a vortex. The separation geometry (`δ*`, separation angle) sets the effective width `D_eff ≥ D` of the wake and therefore the lever on the shedding clock.

3. **Gear-frequency relaxation clock (NP06, `Δω`).** NP06 (the Gear-Frequency Binding Functional) establishes that two meshed circulations bind at a beat frequency set by an energy/relaxation scale. Here the two "gears" are (i) the bound shear layer accumulating circulation and (ii) the advective sweep carrying near-wake material downstream. The shedding frequency is the **relaxation rate** at which accumulated bound circulation exceeds what the local relay can hold and is released:
   `f ≈ 1 / (τ_relax + τ_build)`, with `τ_build ∝ τ_adv = D/U`, and a dimensionless clock constant `k_clock` setting the ratio. **`k_clock` is the load-bearing number:** if it must be tuned to land `St ≈ 0.2`, it is CALIBRATED(1) (see §⓪ Q3) and the value-claim caps at C, while the flatness and scaling stay predictive.

4. **Circulation quantum and budget (FD02 `κ=h/m`, FD07, Law V).** The shed circulation is organised in the FD02/FD07 sense; the movement budget `v_circ² + v_trans² = c²` (`law_V`) caps the internal rotation of the rolled vortex and ties it to the advective velocity, fixing how fast a coherent vortex can spin up before it must detach.

5. **Reynolds regime gates the clock (FD03).** `Re = UD/ν` is advection ÷ relay diffusion (FD03). At high `Re` the relay-diffusion correction to `τ_relax` is negligible and the clock is purely geometric ⟹ `St` plateaus. At low `Re` the diffusion term shortens the build time relative to advection ⟹ `St` *rises* with `Re` (the Roshko/Williamson curve). This is the SDT origin of the plateau-with-low-Re-bend.

**Governing relations to derive (no new fitted shedding constant).**

- *Strouhal as a time ratio.* `St = fD/U = (D/U)/(τ_relax + τ_build) = τ_adv / (τ_relax + τ_build)`. Show that in the high-`Re` limit `τ_relax/τ_adv` tends to a geometric constant set by the separation geometry (FD06) and the `ℓ=2` traction wake (PPT06), giving a *constant* `St`.
- *The plateau value.* Express the constant as `St_∞ = 1 / (1 + τ_relax/τ_adv)` (or the appropriate combination) and evaluate it from separation-angle / wake-width geometry. Target the empirical `St_∞ ≈ 0.2` as the **convergence** number to reproduce, never to insert.
- *Frequency scaling.* Show `f = St_∞ · U/D`, i.e. `f ∝ U` at fixed `D` and `f ∝ 1/D` at fixed `U`, with `St_∞` Re-independent on the plateau.
- *Low-Re bend.* Add the FD03 relay-diffusion correction to `τ_build` and show `St(Re) = St_∞ (1 − A/Re^p)` (or equivalent) rises toward the plateau as `Re` grows — fit the Roshko/Williamson exponent as a *test*, not a tuning.
- *Lock-in.* Add an external drive `f_drive` to the NP06 beat; show that within a band `|f − f_drive|/f < ε(A)` the shedding entrains to `f_drive` (Arnold-tongue-like capture), reproducing the measured synchronisation range vs forcing amplitude.

The deliverable of §3 is a chain in which the shedding frequency is **one** relaxation/gear rate, `St` is **one** ratio of SDT-native times, and every empirical feature (plateau, `f∝U/D`, low-Re rise, lock-in) maps to one mechanism. Any feature the chain cannot produce — or produces with the wrong sign/scaling — is a falsifier.

---

## 4. Investigation Strategy

Five phases, each gated. Run them in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass).

### Phase 1 — Relaxation/gear clock from traction + separation
- **Goal.** Build, in SDT primitives only, the two competing times: the traction/relay relaxation time `τ_relax` of the bound shear layer (PPT06 + FD06 separation geometry) and the advection time `τ_adv = D/U`. Express the shedding frequency as a relaxation rate `f = 1/(τ_relax + τ_build)` with `τ_build ∝ τ_adv`.
- **Method.** Tie `τ_relax` to the `law_VI::traction` `ℓ=2` wake demand and the FD06 separation thickness; tie the build time to `D/U`. Tag every constant DERIVED / MEASURED-INPUT / CALIBRATED(n) in a parameter ledger (R2). Cite NP06 (gear-frequency `Δω`), PPT06 (traction), FD06 (separation) as upstream.
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
- **Goal.** Reproduce the synchronisation of shedding to an external drive — the PPT06/NP06 entrainment signature.
- **Method.** Add `f_drive`, amplitude `A` to the gear-frequency beat; map the capture band `|f − f_drive|` vs `A` (Arnold-tongue width). Compare to measured lock-in ranges for an oscillated cylinder.
- **Success metric.** A capture band exists, widens with `A`, and brackets the measured lock-in range for at least one amplitude; outside the band the natural `St_∞` shedding returns. **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Strouhal derived natively | `St_∞` DERIVED from PPT06/FD06 geometry within ±20 % of 0.2 with `k_clock` **DERIVED** (CALIBRATED(0)) AND `f∝U/D` confirmed <5 % AND `St(Re)` rise reproduced AND lock-in band brackets measured range. |
| **C (QUALIFIED — convergence / `k_clock` calibrated)** | Plateau value calibrated, flatness+scaling predicted | `St_∞` within a factor of two of 0.2 with the clock constant `k_clock` set to land the value (**CALIBRATED(1)**, documented) — the predictive content is the plateau *flatness* and `f∝U/D` (confirmed); `St(Re)` shape reproduced (a low-Re shape parameter is a separate CALIBRATED(n)); lock-in qualitatively present. Total calibration count stated explicitly. |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | Relaxation/gear clock built and `f∝U/D` shown, but `St_∞` value PENDING FD06 separation geometry or the NP06 `k_clock` coefficient; dimensionally closed, plateau value not yet evaluated. |
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
- **NP06 (Gear-Frequency Binding Functional)** — the meshed-circulation beat frequency `Δω` / relaxation-energy scale; source of the shedding *clock* and the `k_clock` constant. *(Note: earlier drafts cited "CQ41", which does not exist — the CQ numbering scheme was retired in favour of domain codes; the gear-frequency functional is NP06.)*
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
| F2 — Plateau value (Phase 2) | `St_∞` set by PPT06/FD06 geometry with `k_clock` **derived** | `St_∞` within factor 2 (ideally ±20 %) of 0.2 | If `k_clock` is tuned to land 0.2, F2 is satisfied by construction ⟹ CALIBRATED(1), cap C (the value is not a prediction); if the derived `k_clock` gives `St_∞` off `>2×` with no reconciling geometry ⟹ Class F |
| F3 — Scaling (Phase 3) | `f ∝ U/D` | `f` linear in `U` (slope `St_∞/D`), `f` ∝ `1/D` | Wrong power of `U` or `D`, or hidden `Re`-dependence on plateau ⟹ clock mis-built |
| F4 — Low-Re rise (Phase 4) | FD03 diffusion shortens `τ_build` | `St(Re)` rises monotonically toward `St_∞` | Wrong sign (St falls with Re) or wrong curvature ⟹ FD03 correction mis-applied |
| F5 — Lock-in (Phase 5) | Forcing entrains shedding (NP06 beat) | Capture band widens with amplitude, brackets measured range | No capture band, or lock-in predicted where none is observed ⟹ entrainment mechanism falsified |

---

## 9. Implementation Notes

- **Numerical approach.** This is a *mechanism demonstration*, not a CFD solver: evaluate the closed-form `St = τ_adv/(τ_relax+τ_build)` over a sweep of `(U, D, Re)`, then add the FD03 and NP06-lock-in corrections. A small lattice/ODE model of the two-gear beat (bound-circulation accumulation vs advective release) is sufficient to exhibit the oscillation and the capture band; keep it 0-D/1-D and double precision. Predict each number and commit it to the run log *before* comparing (R1).
- **Anti-numerology (R5).** Do **not** insert 0.2, nor a free integer/π, to force the plateau. `k_clock` (hence `St_∞`) must either come from PPT06 `ℓ=2` + FD06 separation geometry (DERIVED, A-path) or be **flagged CALIBRATED(1)** (C-path) — never silently set to hit 0.2. Any low-Re shape parameter (`A`, `p`) fitted to Roshko/Williamson is a *test of functional form*, tagged CALIBRATED(n). Report the **total** calibration count and do not let it self-contradict between sections.
- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd10_vortex_shedding_strouhal.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd10_vortex_shedding_strouhal.cpp -o fd10` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes.
- **Visualisation hints.** Plot (i) `St` vs `Re` (log-x) with the SDT prediction overlaid on the Roshko/Williamson curve and the `St≈0.2` plateau band; (ii) `f` vs `U` Strouhal lines (linear, slope = `St_∞/D`); (iii) the lock-in Arnold-tongue (capture band vs forcing amplitude). A side-by-side of free shedding vs locked-in time series makes the entrainment visually obvious.
- **Author attribution:** J. C. Harvey, Melbourne. The standard-FD result (the `St≈0.2` plateau, `f∝U/D`, the Roshko/Williamson `St(Re)` curve, lock-in) is the CONVERGENCE target to *reproduce*, never an input to *borrow*.

## 10. Questions This Opens *(generative — log new ones in `FD10_VERDICT.md`)*

1. **Can `k_clock` be derived from the `ℓ=2` wake geometry + FD06 separation angle, or is it irreducibly empirical?** If derivable, the `St ≈ 0.2` *value* becomes a prediction; if not, FD10's honest win is the plateau flatness and `f∝U/D` scaling, with the value CALIBRATED(1).
2. **Is the plateau flatness itself the signature** — i.e. does the relaxation clock predict that `St` is Re-independent precisely where the FD03 relay-diffusion correction to `τ_build` vanishes? The *flatness* may be more diagnostic than the value.
3. **Does the lock-in Arnold tongue share the NP06 entrainment law with nuclear gear-frequency binding?** If one entrainment functional governs both vortex lock-in and meshed-rotation binding, FD10 and NP06 are the same mechanism at two scales — a cross-domain test.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FD10
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 if `k_clock` is DERIVED (A); exactly 1 if `k_clock` is tuned to 0.2 (C) — state the **total** count, no self-contradiction across sections
- Engine namespaces actually used: law_VI::traction (ℓ=2 wake, ω_demand), law_V (v_circ²+v_trans²=c² vortex-spin cap), law_I (P_conv ambient), bridge (koppa, k, z); ν from FD02, separation from FD06, gear functional from NP06
- Phase thresholds (committed before run):
    P1 clock dimensionally `[s]`, `f∝U/D` at high Re, zero free shedding constants beyond geometry · P2 `St_∞` within factor 2 of 0.2 (CALIBRATED(1) if `k_clock` tuned → cap C)
    P3 `f`–`U` and `f`–`D` slopes set by `St_∞` to <5% · P4 `St(Re)` rises monotonically, correct curvature, ≤1 shape param · P5 lock-in band brackets measured range
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces; insert 0.2; **let the CALIBRATED count disagree between §⑤ and §⑩**
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P2 `k_clock` cannot be derived from geometry | set `k_clock` to land 0.2, flag **CALIBRATED(1)**, cap C | **OPEN** the `k_clock` derivation | tune `k_clock` and grade A |
| P2 `St_∞` off `>2×` with derived `k_clock` | recheck the `ℓ=2`-wake/separation-angle inputs | **KILL** (relaxation argument wrong) | widen the factor-2 band post-hoc |
| P1/P3 wrong `f`–`U` power or hidden Re-dependence | re-derive the two competing times | **KILL** (clock mis-built) | hide the Re-drift |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (NP06 `k_clock`, FD06 separation) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in the Phase-1 native chain · grading a tuned `k_clock` as DERIVED · self-contradicting calibration counts.

---

*FD10 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
