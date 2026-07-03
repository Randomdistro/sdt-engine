# FD09 — Drag as an Occlusion Cross-Section

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Are Stokes drag (`F = 6πμRv`, low Re) and form drag (`½ρv²C_D A`, high Re) genuinely *one* SDT occlusion mechanism, and can the `6π` prefactor be **derived** from the sphere relay geometry rather than adopted from the known Stokes solution?
2. **Why does it matter?** — The engine already uses occlusion (Law III) for every force; if drag is the same shadow resolved along the flow, gravity, Coulomb, and drag share one law. The `6π` is the sharp test — and the drag crisis is the integration test that ties FD09 to FD06's boundary-layer transition.
3. **How will we find out?** — Five gated phases (§④). **Two honesty firewalls:** (P2) the `6π` is either DERIVED from the `4πR²` surface + `2πR²` pressure split of a sphere, or it is ADOPTED from the Stokes solution as a CORRELATION (cap C) — the prompt forbids selling an adopted `6π` as derived; (P4) the crisis location/post-crisis `C_D` must be *predicted from the FD06 wake-angle change* and committed before the data are read — a curve hand-built to match Schlichting/Achenbach is circular and scores nothing.
4. **What would prove us wrong?** — §⑧, five falsifiers with real failure modes: sphere geometry yielding a prefactor ≠ `6π` with no reconciliation; form-regime `C_D` the wrong order of magnitude; no crisis emerging from FD06; crisis location off by >2× AND post-crisis `C_D` out of `[0.07,0.15]`; or terminal velocity off >15%.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

**Domain**: Fluid Dynamics (SDT lattice mechanics) · **Status**: SPEC · **Author**: J. C. Harvey, Melbourne

*This investigation inherits the §0 anti-creep protocol and rules R0–R5 verbatim (whitelist inputs only; no G/M/GM fundamentals; no fields/wavefunctions/quarks/virtual particles/ΛCDM/magnetons; certification labels on every result; translation test on every borrowed term; honesty over success).*

---

## 1. Executive Summary

Fluid drag is conventionally split into two unrelated-looking laws: Stokes drag `F = 6πμRv` at low Reynolds number and form drag `F = ½ρv²C_D A` at high Reynolds number, bridged by the empirical `C_D(Re)` curve and its abrupt "drag crisis". **The thesis:** both are one and the same SDT occlusion mechanism the engine already uses for every force (Law III). A body moving through a medium occludes the convergent momentum flux of that medium across its shadow cross-section; the *net unbalanced flux* — front minus wake — **is** the drag force, exactly as occlusion shadowing is the gravitational and Coulomb force. Low Re is relay/viscous-dominated (momentum diffuses around the body → the `6π` prefactor must fall out of sphere relay geometry); high Re is displacement/form-dominated (`A` = occluded frontal area, `C_D` = wake-occlusion efficiency). The drag crisis is the FD06 boundary-layer transition shrinking the separated wake — a smaller occluded shadow. Reproducing `6π`, the full `C_D(Re)` curve including the crisis at `Re≈3×10⁵`, and terminal velocity earns Class C; a wrong Stokes prefactor or a missing crisis is a clean kill.

---

## 2. Physical Context

**Mechanism / analogy.** In SDT the medium is the coarse-grained spation lattice (FD01): a granular relay fluid carrying convergence momentum cell-to-cell at one tick. A body in steady flow sits in a balanced bombardment of incoming momentum flux from all directions — no net force at rest. Set it moving (or stream the medium past it) and the body *occludes* the oncoming flux over its frontal shadow: the upstream face is bombarded harder than the downstream face, which sits inside the body's wake (its own shadow). The unbalanced front-minus-wake flux integrated over the shadow cross-section is the drag. This is identical in form to Law III gravity/Le Sage occlusion (SAR01): a body casts a shadow in convergent flux and the net push is the force. Drag is the *same shadow*, now resolved along the direction of motion.

**Key variables and dimensions.**
- `v` — body speed relative to medium [m·s⁻¹]
- `R`, `D=2R` — sphere radius / diameter [m]; `A = πR²` frontal (occluded) area [m²]
- `ρ` — medium displacement-load density [kg·m⁻³] (Law IV `V_disp`, not kg-as-fundamental)
- `μ = ρν` dynamic viscosity [Pa·s]; `ν` kinematic viscosity [m²·s⁻¹] (FD02)
- `F_D` — drag force [N]; `C_D = F_D / (½ρv²A)` — dimensionless drag coefficient
- `Re = ρvD/μ = vD/ν` — Reynolds number (advection ÷ relay diffusion)
- `δ` — boundary-layer / separated-wake angular extent [sr or rad] (FD06)
- `P_conv ≈ 2.46×10⁴⁸ Pa` — ambient convergence pressure; `q = ½ρv²` dynamic (stagnation) pressure [Pa] (FD08)

**Connection to SDT.** The drag force is `F_D = ∫_shadow Δ(flux·momentum) dA` — the occlusion integral of Law III specialised to a directed flow. At low Re the shadow is "soft": relay diffusion (`ν∇²v`, FD01/FD02) lets momentum stream around the sphere, and the effective occluded cross-section is set by viscous geometry, yielding `F = 6πμRv`. At high Re the shadow is "hard": flow separates, a low-flux wake forms, and `F = ½ρv²C_D A` with `C_D` the fraction of the geometric shadow that actually goes unbalanced. The crisis is FD06 re-attaching the boundary layer, narrowing the wake, shrinking the occluded shadow, dropping `C_D`. Terminal velocity is where this occlusion drag balances the SDT weight `g = v_surf²/R_body` (no G, no M).

---

## 3. Theoretical Framework

**First principles (SDT axioms only).**

1. **Occlusion is the only force (Law III).** The engine's universal law `F = (π/4) P_eff R₁²R₂²/r²` and `solid_angle_occluded = πR²/r²` (engine `law_III::F_occlusion`, `law_III::solid_angle_occluded`) say a force is an *unbalanced flux over a shadow cross-section*. Drag is the same statement with the convergent flux replaced by the directed momentum flux of the streaming medium and the "shadow" resolved fore/aft along `v`. There is no attractive or "sticking" term — only the front-minus-wake flux imbalance.

2. **Le Sage / push budget (SAR01).** The medium delivers momentum by bombardment; a body intercepts and re-emits it. The thermal/relay budget that makes Le Sage gravity finite (SAR01) is the *same* budget that bounds drag: the maximum momentum flux a moving body can occlude is set by `ρ`, `v`, and the relay tick — capping `C_D` at order unity in the form regime and forbidding runaway drag.

3. **Two relay regimes from the movement budget (Law V, FD01).** `Re = vD/ν` is advection ÷ relay diffusion. When `Re ≪ 1` relay diffusion dominates: momentum smooths around the body (FD01 `ν∇²v` term), the occluded shadow is the *viscous* cross-section, and the integral over a sphere's streamlines gives the Stokes form. When `Re ≫ 1` advection dominates: the body's displacement (Law IV `V_disp`) sweeps medium aside faster than relay can heal it, a separated wake forms, and the occluded shadow is the *geometric* frontal area.

4. **Boundary layer sets the wake (FD06).** The separated-wake angular extent `δ` — hence the occluded fraction `C_D` — is governed by the FD06 boundary-layer transition. Laminar separation → wide wake → large shadow → `C_D≈0.5`. Turbulent re-attachment (drag crisis) → narrow wake → small shadow → `C_D≈0.1`. The crisis is not a new mechanism; it is FD06 changing the shadow size.

**Governing relations to derive (no new fitted parameters).**

- *Occlusion drag integral.* Write `F_D = ∮_S (P_front − P_wake) (n̂·v̂) dA`, with the pressure asymmetry sourced by the directed momentum flux of the medium (`q = ½ρv²` ahead, ≈ ambient behind). Reduce to `F_D = ½ρv²·C_D·A` by definition of `C_D` as the *occluded-fraction* of the geometric shadow `A = πR²`.
- *Stokes prefactor `6π` (honesty firewall).* The textbook `F = 6πμRv` splits as a skin-friction `4πμRv` plus a pressure `2πμRv` contribution — a *result of solving creeping flow*, not a free-standing geometric fact. **Two honest routes, graded differently:**
  - **DERIVED (A-path):** actually solve the occlusion integral over the viscous streamlines of a sphere in the relay-diffusion limit and have the `4π`+`2π` split *fall out* of the relay geometry, independent of the known Stokes answer. This is hard and is the only route to "6π DERIVED".
  - **ADOPTED-CORRELATION (C-path):** take the `6π` (or its `4π`/`2π` split) from the known Stokes solution and *show it is consistent* with the occlusion picture. This is a CONVERGENCE/CORRELATION, **labelled IMPORTED**, and caps the grade at C. The prompt forbids reporting an adopted `6π` as "derived from sphere geometry, <1%" — that conflates adoption with derivation. State plainly which route was taken.
- *Form-drag plateau.* In the advection limit show `C_D → O(1)` (sub-critical sphere ≈ 0.44–0.5), set by the laminar-separation wake angle from FD06.
- *Crisis.* Show the FD06 laminar→turbulent transition near `Re≈3×10⁵` shrinks `δ`, dropping `C_D` to ≈0.07–0.1, then recovering.
- *Terminal velocity.* Balance `F_D(v_t) = m·g` with `g = v_surf²/R_body` (Law V/bridge, no G/M); solve for `v_t` in both the Stokes and form regimes and pick by the resulting `Re`.

The §3 deliverable is a single occlusion integral whose two analytic limits *are* Stokes and form drag, with the `6π` prefactor and the crisis emerging from sphere + FD06 geometry — no curve borrowed, only reproduced.

---

## 4. Investigation Strategy

Five phases, each gated. Run in order; a failed checkpoint stops the chain (R4: a clean kill outranks a forced pass). The standard `C_D(Re)` curve is the **convergence target to reproduce**, never an input to the derivation (R5).

### Phase 1 — The occlusion-drag integral (mechanism statement)
- **Goal.** Cast drag as the Law III occlusion integral specialised to a directed momentum flux: `F_D = ∮_S (P_front − P_wake)(n̂·v̂) dA`, the front-minus-wake imbalance over the shadow cross-section.
- **Method.** Start from `law_III::solid_angle_occluded` and the directed dynamic pressure `q = ½ρv²` (FD08). Define `C_D ≡ F_D/(½ρv²A)` as the *occluded fraction* of the geometric shadow `A=πR²`. Build a parameter ledger tagging every quantity DERIVED / MEASURED-INPUT / CALIBRATED(n) (R2). Cite `law_III` (occlusion), SAR01 (Le Sage budget), FD01/FD02 (`ν`), FD08 (stagnation pressure) as upstream.
- **Success metric.** A single closed integral that, by construction, has the right dimensions and reduces to a balanced (zero-drag) state at `v=0`. **Checkpoint C1:** drag expressed purely as an SDT occlusion imbalance with zero free parameters introduced.

### Phase 2 — Low-Re limit: the Stokes `6π` (DERIVED or ADOPTED — declare which)
- **Goal.** Obtain `F = 6πμRv` (equivalently `C_D = 24/Re`) in the relay-diffusion limit, **with the provenance of the `6π` stated honestly** (DERIVED from the sphere relay integral, or ADOPTED from the Stokes solution as a CORRELATION).
- **Method.** Set `Re ≪ 1` so the FD01 `ν∇²v` relay term dominates advection; the occluded shadow is the viscous streamline geometry of a sphere. Attempt the *forward* route: compute the surface (skin) and pressure (form) contributions of the occlusion integral over a sphere and see whether they sum to `6π` *without* using the known answer. If the forward integral does not close, fall back to the ADOPTED route and label it IMPORTED.
- **Success metric.** **A-path:** forward occlusion integral yields `6π` (the `4π`+`2π` split) to <1% with no Stokes-solution input ⟹ DERIVED. **C-path:** `6π` adopted from Stokes and shown consistent ⟹ IMPORTED, cap C. **Checkpoint C2 (core gate):** if the *forward* geometry yields a prefactor that is not `6π` (e.g. `4π` or `8π`) and no SDT mechanism reconciles it, that is a falsifier (Class-F candidate); reporting an adopted `6π` as derived is itself a violation, not a pass.

### Phase 3 — High-Re limit: form drag and the sub-critical plateau
- **Goal.** Recover `F = ½ρv²C_D A` with `C_D ≈ 0.4–0.5` for a sub-critical sphere from the advection-dominated occlusion shadow.
- **Method.** Set `Re ≫ 1`; advection (Law IV displacement) outruns relay healing → separated wake. The occluded fraction is fixed by the laminar-separation angle handed from FD06. Map the wake angle to `C_D` and show it lands at order unity (sphere ≈ 0.47), not 0.01 or 10.
- **Success metric.** `C_D` plateau in `[0.4, 0.5]` over `Re ∈ [10³, 2×10⁵]`. **Checkpoint C3:** correct order of magnitude with the wake-angle → `C_D` map explicit.

### Phase 4 — The drag crisis (FD06 transition) — *not a curve hand-built to the data*
- **Goal.** *Predict* the sudden `C_D` drop (≈0.5 → ≈0.1) near `Re ≈ 3×10⁵` as the FD06 laminar→turbulent transition shrinking the occluded wake — with the wake-angle→`C_D` map fixed **before** the crisis data are loaded.
- **The trap to avoid (stated plainly).** It is trivial — and worthless — to *fit* a sigmoid `C_D(Re)` whose drop location and depth are read off Schlichting/Achenbach. That is circular: the "prediction" is the data. The load-bearing content is: (i) the FD06 transition criterion fixes the crisis `Re_crit` *independently* (from the boundary-layer coherence calc, not from `3×10⁵`); (ii) the separation-angle → occluded-fraction map (Phase 3) converts the pre/post-transition wake angle into pre/post `C_D` *without* using the measured 0.5→0.1 drop. Both numbers are committed to the run log before any crisis dataset is opened (R1).
- **Method.** Take `Re_crit` from FD06; apply the Phase-3 wake-angle→`C_D` map to the laminar-separation angle (pre-crisis) and the turbulent-reattachment angle (post-crisis); read off the two `C_D` values. Only then overlay the data.
- **Success metric.** *Independently-predicted* crisis `Re` within a factor ~2 of `3×10⁵` AND post-crisis `C_D ∈ [0.07, 0.15]`. **Checkpoint C4:** the crisis is located by FD06 and sized by the Phase-3 map, not by fitting a curve to the reference data. A `C_D(Re)` sigmoid whose parameters are read from the data scores nothing.

### Phase 5 — Full curve + terminal velocity (end-to-end check)
- **Goal.** Stitch the three regimes into a single `C_D(Re)` model and predict the terminal velocity of a falling sphere with `g = v_surf²/R_body` (no G/M).
- **Method.** Assemble Phases 2–4 into one `C_D(Re)` function; overlay on the Schlichting/NASA sphere curve (MEASURED-INPUT, comparison only). For terminal velocity, balance `F_D(v_t) = m·g` self-consistently (the regime is chosen by the resulting `Re`); compute for a few standard cases (e.g. steel/water, droplet/air) and compare to measured/standard values. Calibrate at most ONE dimensionless scale (e.g. the wake-angle→`C_D` constant) and tag CALIBRATED(1) explicitly if needed (R2).
- **Success metric.** Model `C_D(Re)` within stated tolerance band of the reference curve across `10⁻¹–10⁶` (including crisis); terminal velocities within ~15% with calibration count ≤ 1. **Checkpoint C5.**

---

## 5. Success Criteria

| Class | Verdict | Quantitative metric |
|---|---|---|
| **A (PASS — derived)** | Drag = occlusion, fully native | Stokes `6π` **DERIVED forward** from the sphere relay integral (no Stokes-solution input, <1%), form plateau `C_D∈[0.4,0.5]`, crisis `Re` **independently predicted** within ×2 and post-crisis `C_D∈[0.07,0.15]` from the wake-angle map (not fitted to data), terminal velocity <15%, ALL with CALIBRATED(0). |
| **C (QUALIFIED — convergence / 6π IMPORTED)** | Same mechanism, prefactor adopted | `6π` **ADOPTED** from the Stokes solution as a CORRELATION (labelled IMPORTED), both regimes + crisis reproduced with the crisis numbers predicted-then-compared, full `C_D(Re)` within tolerance band, terminal velocity <15%, with at most CALIBRATED(1) wake-angle scale (documented). |
| **D (QUALIFIED-PENDING — computed)** | Mechanism stated, gap remains | Occlusion integral + Stokes/form limits reproduced numerically but the crisis criterion is PENDING FD06, or the wake-angle→`C_D` map is unclosed; dimensionally sound, not yet full-curve. |
| **F (FAIL)** | Mechanism falsified | Sphere occlusion geometry gives the wrong Stokes prefactor (not `6π`, no reconciling mechanism), OR no drag crisis emerges from FD06, OR form-regime `C_D` is the wrong order of magnitude. |

---

## 6. Outputs

| File | Format | Contents |
|---|---|---|
| `fd09_drag_occlusion.cpp` | C++20 standalone (`#include <sdt/laws.hpp>`) | Phase-1 occlusion integral; Phase-2 Stokes `6π` derivation/check (`C_D=24/Re`); Phase-3 form plateau; Phase-4 crisis prediction; Phase-5 full `C_D(Re)` + terminal-velocity solver; prints its own verdict. **No new constants redefined.** |
| `fd09_results.txt` | Plain text | Run output: derived Stokes prefactor vs `6π`; `C_D(Re)` table vs reference curve; predicted crisis `Re` and post-crisis `C_D`; terminal-velocity cases vs measured. |
| `FD09_DERIVATION.md` | Markdown | The full chain: occlusion integral → Stokes `6π` from sphere geometry → form drag → crisis from FD06 → terminal velocity; parameter ledger; regime map. |
| `FD09_VERDICT.md` | Markdown | A–F classification with the deciding metric; provenance × correspondence audit; what is DERIVED vs CALIBRATED(n) vs PENDING; downstream handoffs. |

---

## 7. Dependencies & References

**Upstream (required):**
- **Engine `Engine/include/sdt/laws.hpp`** — `law_III::F_occlusion` (`F=(π/4)P_eff R₁²R₂²/r²`) and `law_III::solid_angle_occluded` (`πR²/r²`), the native force-as-shadow mechanism; `law_I::P_conv` (ambient convergence pressure); `law_V` (movement budget, `Re` as advection÷diffusion); `bridge::koppa` / `g = v²/R` for the terminal-velocity weight (no G/M).
- **SAR01 (Le Sage thermal budget)** — the occlusion / pushing mechanism and its finiteness budget; bounds `C_D` at order unity and forbids runaway drag.
- **FD02 (viscosity `ν`)** — supplies the dynamic/kinematic viscosity used in the Stokes regime and in `Re`.
- **FD06 (boundary layer)** — supplies the laminar→turbulent transition criterion and the separated-wake angle that sets `C_D` and the drag crisis.
- **FD01 (Navier–Stokes from relay)** — the `ν∇²v` relay-diffusion term whose dominance defines the low-Re regime.

**Downstream (unblocked by this):** none yet.

**Related:** FD05 (high-Mach / compressible form drag — wave drag onset); FD08 (stagnation / dynamic pressure `q=½ρv²`, the front-face flux). Law IV (`V_disp` displacement → advection sweep); Law V (velocity cap, regime parameter).

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| F1 — Stokes prefactor (Phase 2, provenance) | the *forward* sphere relay integral yields `6π` (no Stokes-solution input) | forward `4π`+`2π` split = `6π`, `C_D=24/Re` (<1%) | If `6π` is adopted from the Stokes solution, F1 is satisfied by construction ⟹ IMPORTED, cap C (not a derivation); if the *forward* integral gives ≠ `6π` with no reconciliation ⟹ occlusion ≠ viscous drag ⟹ Class F |
| F2 — Form plateau (Phase 3) | high-Re shadow = frontal area | sub-critical sphere `C_D∈[0.4,0.5]` | `C_D` wrong order (≪0.1 or ≫1) ⟹ wake-occlusion map wrong |
| F3 — Drag crisis exists (Phase 4) | crisis = FD06 wake shrink | `C_D` drops ≈0.5→≈0.1 near `Re≈3×10⁵` | No crisis emerges from FD06 geometry ⟹ crisis is not boundary-layer occlusion ⟹ Class F |
| F4 — Crisis location/size (Phase 4, anti-circularity) | crisis `Re` and post-crisis `C_D` **predicted from FD06 + the wake-angle map before the data are read** | independently-predicted crisis `Re` within ×2 of `3×10⁵`, post-crisis `C_D∈[0.07,0.15]` | If a `C_D(Re)` sigmoid is fitted to Schlichting/Achenbach, F4 is circular and scores nothing; if the *independent* prediction is wrong in location AND size ⟹ FD06 coupling falsified |
| F5 — Terminal velocity (Phase 5) | drag occlusion balances `g=v²/R` weight | `v_t` within ~15% of measured for standard spheres, CALIBRATED ≤ 1 | >15% miss, or needs >1 fit ⟹ balance mechanism or `C_D(Re)` wrong |

---

## 9. Implementation Notes

- **Standalone compile.** `cl /std:c++20 /EHsc /O2 /I Engine/include fd09_drag_occlusion.cpp` (MSVC) or `g++ -std=c++20 -IEngine/include fd09_drag_occlusion.cpp -o fd09` (GCC/Clang). Include only `<sdt/laws.hpp>`; do not redefine any constant it exposes (use `law_III::solid_angle_occluded`, `law_I::P_conv`, `law_V`, `bridge::koppa`).
- **Numerics.** Use double precision. The occlusion integral over a sphere can be done analytically (preferred, so the `6π` is *seen* to emerge) and/or by quadrature for the cross-check. The terminal-velocity balance is a 1-D root-find on `F_D(v_t)=m·g`; bracket and bisect, then re-check the regime via the resulting `Re`. Anti-numerology (R5): no free integer or π inserted to force the prefactor — it must come from `4πR²` surface + pressure geometry or be flagged CALIBRATED.
- **Predict-then-compare (R1).** Commit the predicted Stokes prefactor, crisis `Re`, post-crisis `C_D`, and terminal velocities to the run log *before* loading the reference curve. The Schlichting/NASA `C_D(Re)` data (DATA_REQUIREMENTS.md) is a comparison target only, never an input to the derivation.
- **Visualisation hints.** Log-log plot of `C_D` vs `Re` over `10⁻¹–10⁶`: overlay (i) derived `24/Re` Stokes line, (ii) form-drag plateau, (iii) the crisis dip, (iv) the digitised reference curve. A second plot: terminal velocity vs sphere diameter for one fluid, predicted vs measured. A schematic of the fore/aft occlusion shadow (wide laminar wake vs narrow turbulent wake) makes the crisis-as-shadow-shrink visually obvious.
- **Author attribution:** J. C. Harvey, Melbourne. The standard-FD results (Stokes `6π`, the `C_D(Re)` curve, the drag crisis, terminal velocity) are the CONVERGENCE target to *reproduce*, never inputs to *borrow*.

## 10. Questions This Opens *(generative — log new ones in `FD09_VERDICT.md`)*

1. **Can the `6π` ever be derived forward from sphere relay geometry, or is creeping flow irreducibly a boundary-value problem the occlusion picture can only *correlate* with?** This is the live open question — if forward derivation fails, FD09's honest result is "drag = occlusion mechanism (Class C), prefactor IMPORTED".
2. **Is the drag crisis `Re_crit` literally the FD06 flat-plate-style transition `Re` mapped onto a curved surface?** If one transition criterion locates both the boundary-layer transition and the crisis, FD06 and FD09 share a single threshold — a strong cross-test.
3. **Does the SAR01 Le Sage thermal budget set a hard upper bound on `C_D`** (the maximum momentum a moving body can occlude per pass), and is that bound visible as the order-unity plateau? If so, "no runaway drag" is an SDT theorem, not an observation.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — FD09
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 if `6π` is forward-DERIVED (A); IMPORTED `6π` (cap C) if adopted from Stokes — declare which; at most 1 wake-angle scale
- Engine namespaces actually used: law_III (F_occlusion, solid_angle_occluded), law_I (P_conv), law_V (Re as advection÷diffusion), bridge (g=v²/R for terminal velocity, no G/M); ν from FD02, wake angle from FD06, q=½ρv² from FD08
- Phase thresholds (committed before run):
    P1 dimensionally closed, zero-drag at v=0 · P2 forward `6π` <1% (IMPORTED if adopted → cap C) · P3 `C_D∈[0.4,0.5]` over `10³–2×10⁵`
    P4 crisis `Re` predicted (not fitted) within ×2 of 3×10⁵, post-crisis `C_D∈[0.07,0.15]` · P5 terminal `v_t` <15%, CALIBRATED ≤1
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces; **fit a `C_D(Re)` sigmoid to the data and call it a prediction**
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| P2 forward sphere integral won't close | adopt `6π` from Stokes, label **IMPORTED**, cap C | **OPEN** the forward `6π` derivation | report the adopted `6π` as DERIVED |
| P4 crisis `Re`/`C_D` need the data to set them | predict from FD06 + the Phase-3 wake-map only; commit before opening data | **OPEN** the crisis coupling | fit a sigmoid to Schlichting/Achenbach |
| P3 form `C_D` wrong order (≪0.1 or ≫1) | recheck the wake-angle → occluded-fraction map | **KILL** (wake-occlusion map wrong) | tune the map to 0.47 |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FD06 transition, FD02 ν) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in any native chain · grading an adopted `6π` as DERIVED · fitting the crisis curve to the data.

---

*FD09 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
