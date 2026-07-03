# CQ-44 — GRAVITATIONAL WAVES: MOVE THE SEA, DON'T MAKE WAVES

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — *(unfilled by the 2026-06-27 bulk template upgrade — write the single measurable gap before the next run)*
2. **Why does it matter?** — Stack position / downstream blockers (see `INVESTIGATION_STACK.md`).
3. **How will we find out?** — Gated phases in §④; native mechanism before `atomic::`/rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## The binary inspiral, chirp, merger, ringdown and **memory** as occlusion-core dynamics in the relay lattice — derived in koppa, never in G or M

**Framework:** Spatial Displacement Theory v6.0+, constitutional ruleset in full force.
**Author:** James Christopher Tyndall, Melbourne.
**Numbering note:** opened as "CQ-42" in the seed session, then **renumbered to CQ-44** — `CQ-42`
(`CQ42_Spation_Scale_Closure`) and `CQ-43` (`CQ43_Variable_Spation_Closure`) were authored in parallel and are
canonical. This GW investigation is **CQ-44**.
**Lineage:** promotes `E48` (GW speed = c, "transverse lattice rigidity", VERIFIED) and `E68` (black-hole
interior = max-compression state, no singularity) from one-line specs into a full mechanism; inherits the
gear/mesh picture of **CQ-41** (the "spation gears" are literal here), the near-incompressible spation lattice
of **CQ-40** (`w₀ ~ 10⁻²–10⁻³`), and — crucially — the **variable spation closure of CQ-43**
(`ℓ_P(r)=ℓ_P,∞(1−z)`, `c_local=c(1−z)`, `z=ϟ/r`) and the **z=1/k=1 self-boundary of CQ-42** (the spation as
the cell whose c-boundary closes on itself — the merger's max-compression endpoint). Rides the koppa bridge of
**CQ-16 / CQ-24** (`GM = c²ϟ`) into the dynamical strong-field regime for the first time.
**Injection target:** fresh agentic session with sdt-engine access, C++20 (`/I Engine/include`), Python optional.

---

## 0. THE SEED (the spec is a poem — read it first)

> *The black hole, she is a big girl, but she don't like to smash head on. She is a big girl, but also a very
> good dancer, she approach gingerly, very nimble, the other black hole, he a bigger boy, but also he no like
> to just ram her, he must woo her, and so they circle, gently, closer and closer, faster and faster, and they
> pulse, make little mirror go chirp chirp, as the spation gears go in and out, in and out, like moving a sea
> as opposed to making waves. And then they kiss, and spin, and now he inside her, and they meld into one, and
> the pulse, she stop, but also, she go, forever.* — J.T.

**The thesis, stated flatly:** A gravitational wave is **not a ripple made *in* a medium** (GR's metric
perturbation `h_{μν}` propagating *through* spacetime). It is the **medium itself being moved** — the orbiting
binary bulk-displaces the convergence (spation) lattice, and because that lattice is **near-incompressible**
(CQ-40), the only thing it can radiate to the far field is **transverse shear**. *Moving a sea, not making
waves.* Two consequences the metaphor insists on and GR treats as afterthoughts become **primary** in SDT and
**falsifiable**: (i) a sea that is incompressible carries shear *cleanly* but leaks only a whisper of
compression — a **scalar "breathing" mode suppressed by ~w₀**; (ii) when you move a sea it **stays moved** —
the **memory effect**, a permanent strain offset ("she go forever").

---

## 1. THE METAPHOR DECODED → THE FOUR CLAIMS

| Poem fragment | SDT-native mechanism (R0 vocabulary) | Gate |
|---|---|---|
| "circle… closer and closer, faster and faster" | Two occlusion/displacement cores (Law III `F=(π/4)P_eff R₁²R₂²/r²`, Law IV) in a koppa-governed decaying orbit; **no G, no M** — only `ϟᵢ = vᵢ²Rᵢ/c²` | G2 |
| "spation gears go in and out, in and out" | Source term: two rotors (CQ-41) whose rims **mesh** as they close; the mass-quadrupole of the displacement field breathes at **2× orbital frequency** | G2 |
| "make little mirror go chirp chirp" | The inspiral chirp `f_GW(t)`, `df/dt ∝ f^{11/3}ϟ_c^{5/3}`; the test masses respond to far-field shear | G2 |
| **"moving a sea as opposed to making waves"** | Bulk displacement of a **near-incompressible** lattice (CQ-40 `w₀≪1`): compression frozen out at the c-cap → radiation is **transverse shear = GR's 2 tensor polarisations**, plus a residual scalar mode `~w₀` | G1, G3 |
| "kiss, spin, now he inside her, meld into one" | Common-core formation: separation falls toward the **z=1, k=1 self-boundary** (CQ-42) = the max-compression state (E68, **no singularity**); two cores coalesce into **one spinning** max-compression vortex (Kerr-like remnant) | (merger) |
| "the pulse, she stop" | Ringdown: damped quasinormal shear modes of the merged core decay to zero | (ringdown) |
| **"but also, she go, forever"** | **Memory:** the net lattice reconfiguration (two separated cores → one merged core) is a *permanent* displacement — a DC strain offset. In SDT this is **primary**, not a nonlinear correction | G4 |

### The honest tension this investigation must resolve
E48 says GWs are **transverse** ("lattice rigidity"). The seed says **"move the sea"** (bulk/longitudinal).
These are reconciled — not contradictory — **only if** the lattice is incompressible: an incompressible medium
*responds* to bulk forcing with volume-preserving flow (it "moves like a sea") yet *radiates* only shear.
**G1 and G3 must demonstrate this, not assume it.** If the mechanism honestly forces an order-unity scalar
mode, SDT is already dead (binary-pulsar decay + GW170817 polarisation match pure-tensor GR to <0.1%).

---

## RULES (carried verbatim from CQ-41 / §0; in force throughout)

- **R0 Vocabulary sovereignty** — reason in SDT primitives (occlusion core, displacement, relay lattice,
  transverse shear, convergence-budget, koppa `ϟ`, c-boundary, rotor, mesh, tick). Conventional GR/QM terms
  (`graviton`, `spin-2`, `h_{μν}`, `chirp mass`, `ISCO`, `quadrupole`) only inside ⟦instrument-output⟧ brackets.
- **R1 Predict-before-look** — derive each quantity and commit it to the run log BEFORE unsealing the measured
  LIGO/Virgo value. Sealed observables (GW150914 / GW170817 / GW190521 frequency tracks, final-mass/spin) live
  in `sealed/`, read only by the harness.
- **R2 Parameter ledger** — every number tagged DERIVED / MEASURED-INPUT / CALIBRATED(n) at first use. Target
  **CALIBRATED(0)**. The koppa bridge `GM = c²ϟ` is a *conversion of a measured observable* (GM, not G·M
  separately — LIGO measures a koppa, never weighs a mass), tagged MEASURED-INPUT, never a fitted parameter.
- **R3 Two-stream verification** — any CONFIRMED result independently recomputed (closed-form koppa relation
  vs numerical orbit integration; agreement <1%).
- **R4 Honesty over success** — a cleanly-logged fired gate outranks a soft pass. If G3 (polarisation) honestly
  yields an order-unity scalar mode, log the kill: SDT's GW mechanism is falsified.
- **R5 Anti-numerology / no borrowed targets** — never import GR's quadrupole coefficient `(96/5)`, `M_c`, or
  `h_{μν}` as a *target*; forward from koppa + the movement budget, check the match **downstream**, and flag
  every borrowed thing. The `96/5` coefficient, until natively derived from lattice shear-radiation reaction,
  is **CONVERGENCE-PENDING**, not DERIVED.

---

## 2. THE GATES

### GATE G1 — Propagation speed & dispersion (CONVERGENCE, must hold)
**Claim:** the transverse shear mode of the relay lattice propagates at exactly `c`, **non-dispersively** in
every accessible band.
**Forward:** the relay advances one `ℓ_P` per `t_P` (GPI, CQ-08) → the lattice's only signal speed is
`ℓ_P/t_P = c`; any mode (shear *or* compression) caps there. Shear speed `c_S = √(μ/ρ_lattice) = c` is to be
shown structurally (not asserted), with the bulk/shear modulus ratio tied to CQ-40's `w(z)`.
**The CQ-43 refinement (honest version):** the relay is one spation per tick = the *local* speed
`c_local = c(1−z)` (CQ-43). So "GW speed = c" is the **far-field, z→0** statement; in the strong-field zone
near merger the wave crosses a region of **compressed closure (high z)** where `ℓ_P(r)` and `c_local` are
reduced — the same gradient that produces the Shapiro delay applies to the GW, and the GW and its EM
counterpart wade through the *identical* `z(r)` (predicting equal lensing/Shapiro delay — a clean co-propagation test).
**Test:** `|c_GW − c|/c` vs **GW170817/GRB170817A** (`<10⁻¹⁵`); dispersion vs **E100** (GRB photon timing) —
SDT predicts onset only at `f ~ c/ℓ_P` (unobservable) → **zero dispersion** in band.
**Risk:** low (this is E48 promoted + a dispersion bound). Watch for circularity — state *why* `μ/ρ = c²` is
not just "we assumed c".

### GATE G2 — The chirp from a LENGTH, no G, no M (CONVERGENCE on form; the executable headline)
**Claim:** the entire inspiral is governed by a **single length**, the combined c-boundary
`ϟ_tot = Σ ϟᵢ = Σ GMᵢ/c²` (and the chirp koppa `ϟ_c = GM_c/c²`), with **G and M absent from every dynamical
relation**. ⟦LIGO is a koppa-meter: it measures the dynamics, i.e. `ϟ`; "mass" is only `c²ϟ/G`.⟧
**Forward (derive, log, then unseal):**
- orbital velocity from koppa (bridge): `v² = c²ϟ/r` ⟹ `ω_orb² = c²ϟ/r³`; `f_GW = 2 f_orb`.
- merger/ISCO scale: horizons touch at `r ≈ 6ϟ_tot` ⟹ **`f_GW,isco = c/(6^{3/2} π ϟ_tot)`** — *only c and a
  length*. For `M_tot ≈ 65 M_⊙` → `ϟ_tot ≈ 96 km` → `f_GW,isco ≈ 68 Hz` (matches GW150914's sweep band).
- inspiral law: `df/dt ∝ f^{11/3} ϟ_c^{5/3}` — same `f^{11/3}` GR gives, with `GM_c → c²ϟ_c`. The **`f^{11/3}`
  structure** is the deliverable; the leading coefficient is **CONVERGENCE-PENDING** until derived from the
  rate the orbiting occlusion sheds convergence-energy into transverse shear.
**Gate:** SDT (koppa form) reproduces the measured `f_GW` scale and frequency track of **GW150914** within
**±15%**, using only `c` and `ϟ`. Cross-check: `c²ϟ_c/G` recovers ⟦LIGO chirp mass ≈ 30 M_⊙⟧ ±15%.
**Status:** the standalone tool `cq44_chirp_from_koppa.cpp` executes this gate (see §6). **DONE this pass.**

### GATE G3 — Polarisation: "move the sea, don't make waves" (DISTINCTIVE — the kill gate) — **EXECUTED**
**Result (see `CQ44_POLARISATION.md`): kill-condition AVOIDED, conditional Class C.** Not via elasticity
(the Depth–Closure Theorem fixes **one** relay speed `c_local`, so the textbook `c_P≫c_S` split does not
apply) but via **conservation + multipole order**:
- the static SDT field is a **scalar** depth `z=ϟ/r` (Depth–Closure Theorem) → a breathing mode is the real
  danger;
- but the breathing channel **is the monopole** = total `ϟ_tot`, and total displacement-load is **conserved**
  (a moving sea conserves its volume) ⟹ **no monopole radiation ⟹ no breathing**; momentum conservation kills
  the dipole; the leading radiated moment is the **quadrupole → the two tensor modes `h₊,h×`** (= GR).
- residual scalar = the merger-epoch **change** in the monopole: `ε_scalar ~ Δϟ_tot/ϟ_tot = E_rad/E_total`
  (GW150914: ~3/65 ≈ **4.6 %**), a *transient* (not a steady inspiral channel → evades the Hulse–Taylor bound),
  and **identical to the memory `Δϟ` of G4** — the breathing whisper and "she go forever" are one quantity.
**Novel falsifiable prediction:** a few-% breathing admixture **confined to the merger epoch and correlated
with the memory offset** — tests: ≥5-detector merger-time polarisation, LISA memory↔breathing correlation, PTA
scalar overlap-reduction function. **Coefficient `κ` in `ε=κΔϟ/ϟ` PENDING the dynamic (radiative) extension of
the Depth–Closure Theorem; the structural result rests only on conservation + multipole order (robust).**

### GATE G4 — Memory: "she stop, but also she go forever" (DISTINCTIVE — cleanest forward falsifier)
**Claim:** after ringdown a **permanent strain offset** `Δh_mem` remains = the net lattice displacement from
the initial two-core configuration to the final single spinning core. In SDT this is **primary** (a moved sea
stays moved), not GR's higher-order "nonlinear/Christodoulou" memory.
**The CQ-43 handle (the native form):** in SDT, memory is a **permanent change in the depth/closure field**
`z(r)`: before merger the detector sits in the superposed `z` of two separated cores; after, in the `z` of one
merged core at a different location/mass-distribution. Since `Δh = Δ(ℓ_P(r)/ℓ_P,∞) = −Δz` (CQ-43), the memory
strain **is** the permanent change in local closure — the sea staying moved is literally `ℓ_P(r)` staying
reconfigured. This replaces GR's nonlinear-memory integral with a difference of two static `z`-fields.
**Forward:** `Δh_mem = −Δz(detector)` from the initial vs final `ϟ/r` configuration (couples to the
radiated-budget that sets the final-core koppa). Predict for a GW150914-class merger; compare to GR's
nonlinear memory (~few % of peak strain).
**Test:** event stacking (LIGO/Virgo, marginal now), **LISA** (per-event memory), PTA burst-with-memory.
**Result (EXECUTED — `CQ44_MEMORY.md`, `cq44_memory.cpp`):** the memory is the **DC part of the trace
(volumetric depth)** — `Δh_mem = η·Δϟ_rad/R`, `Δϟ_rad = ϟ_tot·(ΔM/M)` = a **radiated length** (GW150914:
4.43 km), no G/M. Magnitude **7–35 % of peak** (η=0.2…1) vs GR's ~5–20 % → **order-match, Class C**. The
**distinctive** result: the same `Δϟ_rad` is the G3 breathing transient (AC) and this memory (DC) — **one
quantity**, a correlation GR does not predict. The radiative coefficient comes from the **dynamic Depth–Closure
extension** (`CQ44_DYNAMIC_CLOSURE.md`); native `ΔM/M` (strong-field `z→1`) remains OPEN.

---

## 3. FALSIFICATION TABLE

| # | Test | SDT prediction | If it fails |
|---|---|---|---|
| F1 | GW speed (GW170817) | `=c` to `10⁻¹⁵`, no dispersion | E48 wrong; lattice not the light medium |
| F2 | Chirp scale (GW150914) from `ϟ` only | `f_GW,isco ≈ 68 Hz` from `ϟ_tot≈96 km`, ±15% | koppa bridge fails in radiative regime |
| F3 | Polarisation content | 2 tensor + scalar `~Δϟ/ϟ` (~few %, merger-only, = the memory) | order-unity **or steady-inspiral** scalar ⟹ **model dead** (G3 kill) |
| F4 | Memory amplitude | permanent `Δh_mem`, sea stays moved | no memory ⟹ "make waves" picture, not "move sea" |
| F5 | Ringdown spectrum | shear-mode QNMs of a max-compression core; **echoes** possible (E68) | pure Kerr, no structure ⟹ E68 unsupported |

---

## 4. SUCCESS CRITERIA (canonical A–F)

- ✅ **PASS (A/B):** G1 + G2 reproduce speed and chirp scale from `c` and `ϟ` alone (no G/M), ±15%, and G3
  shows the breathing mode is conservation-forbidden except for the radiated `Δϟ/ϟ` (kill-condition avoided).
- ✅ **QUALIFIED (C — convergence) — CURRENT LANDING:** G2 reproduces the `f^{11/3}` form and merger scale
  (`cq44_chirp_from_koppa.cpp`, −0.5 %); **G3 EXECUTED** (`CQ44_POLARISATION.md`, kill avoided via
  conservation+multipole, grounded on the Depth–Closure Theorem); the `96/5` chirp coefficient, the G3
  coefficient `κ`, and the memory magnitude remain CONVERGENCE-PENDING (need the *dynamic* depth-closure
  extension), matched/structural but not yet coefficient-level native.
- ⚠️ **PENDING (D):** mechanism stated and dimensionally closed, but G3/G4 await the CQ-40 modulus ratio and
  the shear-radiation-reaction integral.
- ❌ **FAIL (F):** G3 forces an order-unity scalar mode, or G2 cannot recover the chirp scale without inserting
  G — either kills the "move the sea" mechanism.

---

## 5. DEPENDENCIES

**Upstream (required):** CQ-16/CQ-24 (koppa bridge `GM=c²ϟ`), CQ-40 (lattice equation of state / `w₀`, the
incompressibility that makes G3 work), **CQ-42** (the z=1/k=1 spation self-boundary = the merger endpoint),
**CQ-43** (variable closure `ℓ_P(r)`, `c_local=c(1−z)` — the local-c form of G1 and the native memory handle
for G4), Law III/IV (occlusion cores), Law V (movement budget), CQ-08 (GPI → speed c), E68 (max-compression
remnant).
**Related (parallel):** CQ-41 (the meshing rotors = the "spation gears"), E48 (speed, now promoted), E100
(dispersion bound).
**Downstream (unblocked by this):** E67 (TOV / neutron-star mergers), ringdown-echo searches, a
"LIGO-as-koppa-meter" reframing of the catalogue's reported masses.

---

## 6. DELIVERABLES

- D1 `PROMPT.md` — this file (metaphor → mechanism → four gates).
- D2 `cq44_chirp_from_koppa.cpp` — standalone C++20 tool: derives the inspiral chirp scale from the koppa
  bridge (no G, no M in the dynamics), applies it to GW150914, cross-checks against the ⟦LIGO chirp mass⟧.
  **(Built and run this pass — see `cq44_chirp_results.txt`.)**
- D3 `cq44_chirp_results.txt` — run output (the G2 verdict).
- D4 `CQ44_POLARISATION.md` — G3 derivation (conservation + multipole, grounded on the Depth–Closure
  Theorem): kill-condition avoided; scalar mode = radiated `Δϟ/ϟ` = the memory. **(DONE this pass.)**
- D5 `CQ44_MEMORY.md` + `cq44_memory.cpp` + `cq44_memory_results.txt` — G4: memory `Δh=η·Δϟ_rad/R`, GW150914
  ≈ 7–35 % of peak (order-match GR); same `Δϟ_rad` as the G3 breathing. **(DONE this pass.)**
- D7 `CQ44_DYNAMIC_CLOSURE.md` — the radiative extension of the Depth–Closure Theorem (trace=depth / shear=GW
  split → tensor polarisation natively; supplies the G2 `96/5` and G3 `κ` coefficients by convergence).
  **(DONE this pass.)**
- D8 `CQ44_RINGDOWN_ECHOES.md` + `cq44_echoes.cpp` — strong-field frontier: ringdown `f_QNM≈275 vs 250 Hz`
  (convergence) + the **distinctive echo prediction** `Δt_echo∝ϟ_f·ln(ϟ_f/ℓ_P)≈58 ms` (no horizon + CQ-42
  closure-floor wall) — the SDT≠GR test (contested observationally). **(DONE this pass.)**
- D6 `CQ44_VERDICT.md` — final A–F ledger: overall **Class C**; native = tensor-by-construction, G3≡G4, echoes;
  open = native radiative coefficients + the nonlinear strong-field sector. **(DONE this pass.)**

## 7. FINAL INSTRUCTION
One question, split four ways: **is a gravitational wave the medium being moved, not a wave made in it?**
Show the chirp is a *length* (G2, done), show the medium's incompressibility forces shear-not-compression and
quantify the scalar whisper (G3), and show the sea stays moved (G4). Forward from `c` and `ϟ`; never insert G;
flag every borrowed coefficient. Open it honestly or report the gate that fires.
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: bridge::koppa_*, depth_closure::, no G/M
- Phase thresholds (committed before run): 0.1%, 1%, 15%, 15%, 4.6 %
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| `z ≥ 1` in closure formula | Weak-field break (CR10); piecewise or exponential | **OPEN** that regime | Ignore break |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*GOM06 · upgraded 2026-06-27 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
