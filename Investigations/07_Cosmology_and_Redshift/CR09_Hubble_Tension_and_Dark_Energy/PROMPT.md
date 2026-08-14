# CR09 — The Hubble Tension and Dark Energy: One Redshift, Two Components, No Λ

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — investigation NOT yet run · **de-preloaded 2026-07-26**.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` and `<sdt/cosmology.hpp>` only — no local constant namespaces.
> **Run:** Direct, no auto-agents. Pre-commit every gate in `RUN_LOG.md` before coding; four-root sort (§⑨.E) on every FAIL.
>
> **This is a spec, not a result.** CR09 does not yet know whether SDT can account for the raw cosmological sky —
> **the raw observables have not been analysed in the SDT frame.** The prompt's job is to state, for each raw
> observable (the supernova magnitudes, the CMB acoustic peak angles, the BAO angles, the line-of-sight
> temperature, the CMB→ℓ_P linkage), the **attempt**: what SDT would have to derive, by what method, and what
> confirms or kills it. The default expectation of every route is **open — it may fail.** No outcome is asserted
> here that the analysis has not produced, and there is no rival model in this prompt: SDT is checked against the
> photons, not against anyone's fit.

---

## §0 Anti-creep protocol (R0–R5)

- **R0 — declared dependencies:** the derivation basis `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + **RAW measured observables
  in their measured units** (§2). Where a quantity in common use is a *model-processed product* (an angle
  reinterpreted as a length via an assumed metric, a magnitude corrected against an assumed cosmology), use the
  **raw observable underneath it**, not the processed number.
- **R1 — Prohibited as inputs:** metric expansion / scale factor a(t); dark energy / vacuum energy / a
  cosmological constant Λ; dark matter; a metric sound horizon; a single global expansion rate assumed a priori.
  None may enter the SDT chain, even "as scaffolding." SDT simply does not contain them — that is the premise
  under test, not a claim of victory.
- **R2 — Redshift is caused by more phenomena than Doppler and is not evidence of expansion.** It is **also** created by (i) **emission depth** in a **displacement field** `z_emit = Ѻ/r` at the source of emission, and is invariant under the path,  
  and (ii) **propagation path straightening** accumulated along the path. State which component every number belong to.
- **R3 — Native yardsticks:** koppa gear `k = c/v at R_surface` (dimensionless, `zk²=1` at a boundary), koppa length
  `Ѻ = v²R/c² = R/k²` (the "Om"; formerly ϟ), octave count `1+z = 2^Δn` (CR07), strain rate `σ₀ = H₀/c`
  (an inverse length carried from the *measured* local velocity–distance slope, **not** an expansion rate). No borrowed metric units.
- **R4 — No G/M/GM.** Depths come from `Ѻ = v²R/c²` (kinematic) and measured redshifts, never from `GM`.
- **R5 — This is an investigation, not a demonstration.** Report what SDT *can* and *cannot yet* derive.
  Compare SDT's derived value to the **raw datum** (a χ² against raw data is fine); do **not** grade SDT against
  another model's fit or its processed products, and do **not** define a "win," a "kill," or an "expected
  outcome" by reference to any rival. Assert no result the analysis has not produced. **Watch the virtue-words**
  — "honest / rigorous / fair / adversarial / like-for-like" are where a hidden scoreboard, or a preloaded
  outcome, tends to re-enter.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — **Whether SDT, from ℓ_P + the sphere with no expansion and no dark energy, can
   account for the raw cosmological sky at all.** None of these have been analysed in the SDT frame: (a) whether
   the two-component redshift (`z_emit = Ѻ/r` + a path-accumulated squeeze) predicts the *direction and size* of
   the local-vs-CMB velocity–distance mismatch from geometry; (b) whether the SDT propagation law reproduces the
   raw supernova magnitudes `mB(z)`; (c) whether a physical shell reproduces the raw BAO angles and the raw CMB
   acoustic peak angles without a metric sound horizon; (d) whether the line-of-sight compression produces the
   observed CMB temperature–density correlation without dark energy; (e) whether the CMB energy density returns
   ℓ_P. **We do not know if any of these succeed.**
2. **Why does it matter?** — If the light carries a two-component redshift, then the **Hubble tension** would be
   the *diagnostic signature* of forcing a single velocity–distance slope onto a two-component quantity, and the
   **late-time acceleration** would be the volumetric (z³, CR10) / octave (CR07) structure of the propagation
   term. If instead the geometry gives the mismatch the wrong sign, or no physical shell can land on the CMB
   peak angles, those claims die here. This is the framework's headline cosmological gamble and the place it is
   most exposed.
3. **How will we find out?** — Eight gated Routes (§④), each an **attempt**: *state the target raw observable →
   derive SDT's value → compare to the raw datum → residual*. Each route carries a **STATUS** (not-yet-analysed
   vs prior-work) and a pre-committed pass/kill. The outcome of each is open going in.
4. **What would prove us wrong?** — §⑧. A mismatch geometry with the *wrong sign*; an SDT `mB(z)` that misses
   the raw magnitudes beyond their errors; raw BAO or raw CMB peak angles no physical shell can reach; a CMB→ℓ_P
   linkage that does not close; a line-of-sight temperature effect that is *absent* in the data or *overshoots*
   the observed CMB uniformity. Each is a direct miss against the raw sky and kills the specific claim.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–H run + `RUN_LOG.md`) × physics
   class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). The hard falsifiable cores are the **sign+size of
   the mismatch (A)** and the **raw CMB peak angles + BAO angles from a physical shell (C, D)** — to be derived,
   not assumed.

---

## 1. The core thesis (what CR09 will TEST — not what it has shown)

> **The hypothesis under investigation:** there is no metric expansion and no dark energy; cosmological redshift
> is one physical quantity with two components — an emission depth `z_emit = Ѻ/r` set where the light is born,
> and a propagation squeeze accumulated as the light crosses the convergence-pressure gradient — and it shows no
> light-or-source warping even as it crosses dense fields and voids, where a genuinely accelerating expansion
> front (racing through voids, dragging through mass) should smear distant sources over billions of light-years.
> **If** the local distance ladder and the CMB sample the two components in different proportions, **then** any
> attempt to read one single velocity–distance slope off the light is forced to two incompatible values — the
> mismatch conventionally called the "Hubble tension" — and the late-time acceleration read from the
> magnitude–redshift curve is the volumetric (z³, CR10) / octave (CR07) structure of the propagation term. **CR09
> exists to find out whether that hypothesis survives contact with the raw observables. It is not yet known to.**

Three sharp, separately-falsifiable claims — each an open question against the raw sky:
- **C1 (does the mismatch have the right sign+size?):** the two-component split *should* make a single-slope
  reading of the *local* ladder (propagation through over-dense regions) return a **larger** slope than the CMB
  end — the ~8.4% direction — from the gradient geometry, **without a fitted mismatch parameter.** Untested.
- **C2 (do the raw magnitudes fit?):** the SDT propagation law should reproduce the raw `mB(z)` at the stated
  parameter count (0 for emission depth; 1 shape `n`). The residual to the raw supernova magnitudes is the test.
- **C3 (do the raw angles fall out of a physical shell?):** the raw CMB peak angular positions and the raw BAO
  angles should come from a **physical shell** (opacity / closest-contact, CR08/CR13) — no metric sound horizon.
  This is the hardest and least-explored claim.

---

## 2. THE INPUT DOSSIER — the RAW measured set (freeze before any derivation)

> Every value below is a **raw measured observable in its measured unit** (R0). Where the community usually
> quotes a *processed* number (a sound horizon, a bias-corrected magnitude, a density budget), the raw
> observable underneath it is given and the processed one is omitted.

### 2.1 The distance-ladder outputs (the mismatch itself — the thing to explain)

| probe | slope [km/s/Mpc] | ± | z-regime | which component it samples | source |
|---|---|---|---|---|---|
| CMB-anchored (Planck) | 67.36 | 0.54 | z≈1100 | emission + propagation (far end) | Planck 2018 VI |
| CMB-anchored (ACT+WMAP) | 67.6 | 1.1 | z≈1100 | far end | ACT DR4 |
| local ladder (Cepheid→SN) | 73.04 | 1.04 | z≲0.15 | propagation (near end) | Riess+ 2022 |
| local (TRGB) | 69.8 | 1.9 | local | propagation | Freedman 2021 |
| local (megamaser) | 73.9 | 3.0 | local | propagation | Pesce+ 2020 |
| local (SBF) | 73.3 | 2.5 | local | propagation | Blakeslee+ 2021 |
| **mismatch** | **8.4%** (73.04 vs 67.36) | **~5σ** | — | **the phenomenon Route A attempts to derive** | — |
| carried in engine | `H0_CMB`, `H0_local`, `σ₀` | | | | `cosmology.hpp` |

### 2.2 CMB — RAW anchors (Planck 2018, FIRAS)

| quantity | value | note |
|---|---|---|
| T_CMB | 2.72548 ± 0.00057 K | FIRAS blackbody; `z_at_T`/`T_at_z` in engine — a **raw** spectrum |
| **acoustic peak angular positions** ℓ₁, ℓ₂, ℓ₃ | ≈ 220, 540, 810 (TT) | **the raw observable** — angles on the sky; Route D attempts these |
| z_* (recombination) | ≈ 1090 | epoch of last scattering |
| SDT octave count to CMB | Δn = log₂(1+z_*) = **10.09** | CR07 (1+z = 2^Δn) |
| SDT CMB backtrack | z≈99 → T = 272.5 K (water freezing) | CR13/SAR05 (a *separate* provenance question) |

*(Deliberately NOT listed: the angular sound horizon θ*, the comoving sound horizon r_*/r_drag, and the
Ω_m/Ω_Λ budget — those are lengths and fractions inferred from the peak angles under an assumed expanding
metric, not raw observables. CR09 attempts the raw peak **angles** directly; it takes no inferred horizon length
or density budget as an input or a target.)*

### 2.3 BAO — RAW angular/redshift peak (the geometric cross-check)

| survey | z_eff | RAW observable | note |
|---|---|---|---|
| 6dFGS | 0.106 | Δθ(z), Δz(z) of the correlation-function peak | low-z anchor |
| SDSS MGS | 0.15 | Δθ, Δz | |
| BOSS DR12 | 0.38, 0.51, 0.61 | Δθ(z), Δz(z) | recover from the published D/H ratios back to raw angles |
| eBOSS (LRG/ELG/QSO/Lyα) | 0.70–2.33 | Δθ(z), Δz(z) | |
| DESI DR1 2024 | 0.30–2.33 | Δθ(z), Δz(z) | Route C attempts these from a physical shell |

### 2.4 Supernovae — RAW magnitudes (the distance-law test)

| set | N | z range | RAW use |
|---|---|---|---|
| Pantheon+SH0ES | 1701 (≈1550 Hubble-flow) | 0.001–2.26 | `Datasets/cosmology/PantheonPlusSH0ES.dat` |
| RAW columns | `mB` (SALT2 apparent mag), `x1`, `c`, `mBERR`, `zHD` | | standardise with **SDT's own** α, β (Tripp) — do **not** use `m_b_corr` (bias-corrected against an assumed cosmology) |
| drop | calibrators (`IS_CALIBRATOR=1`) + z<0.01 | | keep the Hubble-flow set |

### 2.5 The line-of-sight temperature data (Route H)

| observable | value | note |
|---|---|---|
| CMB anisotropy floor | ~30 μK (ΔT/T ~ 1×10⁻⁵) | the uniformity the Route-H effect must not overshoot |
| CMB × large-scale-structure cross-correlation | ~few μK, ~4σ, cooler through mass | the raw signal Route H attempts |

### 2.6 SDT native quantities (the machinery — not results)

| quantity | relation | source |
|---|---|---|
| emission depth | `z_emit = Ѻ/r`, `Ѻ = v²R/c² = R/k²`, `zk²=1` at boundary; invariant under path | koppa / bridge |
| octave ladder | `1+z = 2^Δn`; redshift telescopes (endpoint count, does NOT compound) | CR07 |
| strain rate | `σ₀` (inverse length from the measured local slope; not expansion); `R_CMB = ln(1+z)/σ₀` | cosmology.hpp |
| cubic rung | `z³` from three-dimensionality; `u ∝ (1+z)^4` volumetric | CR10 |
| emission/propagation split | propagation single-power `n≈0.66` fitted (CR06); `n=4` **dead** (missed the raw curve, χ²/dof 424) | CR06 |
| physical shell / BAO+CMB angles | opacity self-jam → real acoustic shells; `c/√3` opaque ceiling | CR08 / opacity note |
| displacement speed | `c_local = c(1 − Ѻ/r)` — the Shapiro compression; slows light in dense fields | GOM05 / Shapiro |
| CMB → ℓ_P | `ε = u_CMB · ℓ_P³` — the linkage FLM06 reports (a prior result, to be re-checked here) | FLM06 |

---

## 3. Theoretical framework — the two-component redshift, explicitly

**The total observed redshift of a source at coordinate distance d, emitting from local depth `Ѻ/r`:**

```text
1 + z_obs = (1 + z_emit) · (1 + z_prop)
z_emit    = Ѻ_source / r_source              # depth where the light is BORN (CR01, koppa); invariant under path
1 + z_prop = 2^{Δn(d)}  = exp( ∫₀ᵈ σ(x) dx ) # octave accumulation along the path (CR07)
σ(x)      = σ₀ · g(x)                          # strain rate, modulated by the local gradient g(x)
```

- **Uniform-gradient limit** (`g≡1`): `1+z_prop = e^{σ₀ d}` → linear velocity–distance law at low z.
- **Non-uniform-gradient hypothesis** (the thing Route A must derive, not assume): if `σ` is steeper near
  massive structure, a single-slope reading anchored in over-dense regions *would* return a larger slope than
  the global-average end. **Whether the geometry actually delivers the observed sign and ~8.4% size is unknown —
  that is the test, not a given.**
- **Distance modulus:** `μ(z) = 5 log₁₀[d_L(z)/10pc]`, `d_L` from the SDT propagation law (one (1+z)
  reciprocity factor; the Tolman exponent from CR11).
- **No a(t), no Λ** — as *inputs* (R1). Whether the μ(z) curvature that a scale-factor reading calls
  "acceleration" is the octave/z³ structure of `z_prop` is Route F's open question.

**Parameter count (state it, then never grow it):** emission depth *fixed* by the source koppa (0 free); the
propagation power `n` is **1 shape parameter** (CR06's ~0.66). That is the entire cosmological freedom of SDT.
Report every residual against the raw data at that count.

---

## Dependency Map (§K.3) — every sibling CR this capstone consumes

| Item | Where | Enters as | Live? |
|---|---|---|---|
| **CR01** redshift decomposition | Investigations/07 | the emission-vs-propagation split | ✔ |
| **CR06** emission/propagation fit | Investigations/07 | `n≈0.66` propagation power; `n=4` killed | ✔ (verified 2026-07-26) |
| **CR07** octave ladder | Investigations/07 | `1+z=2^Δn`, telescoping (endpoint, non-compounding) | ✔ |
| **CR08** pressure-gradient + shell | Investigations/07 | the physical acoustic shell (Routes C, D lean on this) | ⚠ verify |
| **CR10** cubic redshift z³ | Investigations/07 | the volumetric rung; `u∝(1+z)^4` | ✔ |
| **CR11** reciprocity / Tolman | Investigations/07 | the (1+z)^n surface-brightness exponent | ⚠ verify |
| **CR12** Pantheon distance law | Investigations/07 | the raw `mB(z)` fit machinery (Route B) | ✔ (verified 2026-07-26) |
| **CR13** CMB backtrack | Investigations/07 | z≈99→272 K provenance; the shell structure | ✔ (SAR05) |
| **FLM06** CMB → ℓ_P closure | Investigations/01 | `ε = u_CMB·ℓ_P³` (Route G — a prior result to re-check) | ✔ |
| `cosmology.hpp`, `Datasets/cosmology/PantheonPlusSH0ES.dat` | Engine/repo | the raw data + machinery | ✔ |

**Dependency risk:** Routes C/D lean on the CR08/CR13 shell. If the shell cannot reach the raw peak angles, the
honest verdict is **OPEN or KILLED on the angular scale**, cite CR08 — do **not** invent a shell that hits them.

---

## ④ Investigation Strategy — eight gated Routes (each: attempt → raw datum → residual)

> **Every route below is an ATTEMPT.** The STATUS line says whether it has been analysed in the SDT frame. The
> pre-committed gate says what would confirm or kill it. The outcome is open.

### Route A — Can the mismatch sign+size be derived from the split? (strong falsifiable core)
- **STATUS: not analysed in this frame.** The two-component law is written down; the mismatch has never been
  computed from the gradient geometry.
- **Attempt:** the effective `σ₀` a near-end ladder samples (propagation through over-dense regions) vs the
  global average; ratio → predicted mismatch. **No fitted mismatch parameter.**
- **Gate:** correct **sign** (near > far) AND magnitude within ~×2 of the observed 8.4%, from geometry. **Kill:**
  wrong sign → C1 dead → the mismatch is not the two-component signature.

### Route B — Does the SDT law reproduce the raw `mB(z)`?
- **STATUS: partially — CR12 fit the distance law (against a rival); the raw-`mB`, SDT-standardised fit is not
  clean.** Redo it on raw `mB` with SDT's own α, β (Tripp), not `m_b_corr`.
- **Method:** CR12 pipeline on the RAW `mB` (drop calibrators + z<0.01; marginalise the absolute scale).
- **Gate:** report **χ²/dof against the raw magnitudes** and the residual structure. Confirm = the
  zero-cosmological-knob law tracks the raw `mB(z)` within its errors; a systematic residual is a lead, reported
  plainly. (No rival comparison; the datum is the photons.)

### Route C — Can a physical shell reproduce the raw BAO angles? (CR08)
- **STATUS: not analysed in this frame.**
- **Attempt:** derive `Δθ(z), Δz(z)` of the BAO peak from the opacity/acoustic-shell scale (CR08), using the
  *same* gradient that fit `mB(z)` (Route B), no new knob.
- **Gate:** raw angles reached, no new knob → NATIVE candidate; else OPEN, cite CR08.

### Route D — Can a physical shell reproduce the raw CMB peak angles? (decisive geometric test)
- **STATUS: not analysed in this frame — the hardest and least-explored route.**
- **Attempt:** derive the acoustic peak angular positions ℓ₁≈220, ℓ₂, ℓ₃ from the physical shell (CR13
  closest-contact / z≈99–1100 structure) — a real spatial scale, no metric sound horizon. **Derive the shell
  from CR08 physics *before* looking at 220, and let the number fall where it falls.**
- **Gate:** peak angles reached to <few % from the shell → strong NATIVE candidate. Cannot → **OPEN or KILLED on
  the angular scale**, reported plainly. An invented shell that happens to hit 220 is the worst kind of
  fabrication — be adversarial here.

### Route E — Are the sibling CRs mutually consistent?
- **STATUS: to be assembled here.**
- **Attempt:** one ledger showing CR01/06/07/10/11/12/13 hold together under the two-component law (same `n`,
  same σ₀, same octave count). Any internal contradiction is a root to fix, not to paper over.

### Route F — Is the "acceleration" the z³/octave geometry?
- **STATUS: partially — CR10 established the z³ rung; the map onto the μ(z) curvature is not drawn.**
- **Attempt:** show the μ(z) curvature and `u ∝ (1+z)^4` are the z³/octave structure of the propagation term
  (CR10), a fixed geometric law. Address the DESI evolving-w hint as a *forward-consistency*: a fixed geometric
  law read through a cosmological-constant template *must* drift as data sharpen — check whether that is what is
  seen. (Open; the degeneracy may or may not hold quantitatively.)

### Route G — Does the CMB return the fundamental unit?
- **STATUS: prior result (FLM06) — re-check that it closes here.**
- **Attempt:** confirm the CMB energy density hands you ℓ_P — `ε = u_CMB·ℓ_P³` (FLM06) — returning the geometric
  value. **Honest content (FLM06's own finding):** the geometric and CMB routes are "faces of one seed," so the
  claim is that the **linkage exists at all** (CMB ↔ ℓ_P, one closed system), not an independent
  double-derivation. State it that way; do not sell it as two independent confirmations.
- **Gate:** the linkage closes to the geometric ℓ_P → stands as a positive structural feature; if it does not
  close, that is a real problem, reported.

### Route H — Does line-of-sight compression give the observed CMB temperature–density correlation?
- **STATUS: preliminary only — an order-of-magnitude estimate was computed 2026-07-26; not a finished analysis.**
- **Attempt:** from `c_local = c(1 − Ѻ/r)`, dense fields accumulate more compression redshift (COOLER); voids
  less (HOTTER). Per structure `z_comp = v²/c²`; `ΔT/T = −z_comp`. Predict the CMB × large-scale-structure sign
  and amplitude.
- **Preliminary estimate (order-of-magnitude, 2026-07-26 — to be firmed up):** supercluster/void scale
  `z_comp ~ 1×10⁻⁶` → **~few μK**; rich cluster `~1×10⁻⁵` → **~30 μK**; sign mass→cooler. This is a back-of-
  envelope, **not** a validated prediction.
- **Two-sided gate:** the effect must land near the observed ~10⁻⁶ (large-scale) level — at ~10⁻⁴–10⁻³ it would
  **bust the 10⁻⁵ CMB uniformity** (kill by overshoot); if **no** CMB-temperature vs LOS-density correlation
  existed, the compression would be **falsified** (kill by absence). The finished route must check both edges
  against the raw cross-correlation, not stop at the estimate.

---

## ⑧ Falsification tests (numeric triggers — all against the RAW sky)

| ID | Attempt | Confirms if | If FAIL → root |
|---|---|---|---|
| T1 | mismatch sign | near-end slope > far-end slope, from geometry | root-1 (C1 dead) if reversed |
| T2 | mismatch size | within ~×2 of 8.4%, unfitted | root-1/root-3 (needs a mismatch knob) |
| T3 | raw `mB(z)` | zero-cosmological-knob law tracks raw `mB` within errors | root-1 if it misses the raw curve |
| T4 | raw BAO angles | `Δθ(z),Δz(z)` from the SNe gradient, no new knob | root-2 (CR08 dep) |
| T5 | raw CMB peak angles | ℓ₁≈220 (+ℓ₂,ℓ₃) from a physical shell, <few % | root-1 (shell can't → KILL angular scale) |
| T6 | reciprocity | Tolman (1+z)^n exponent matches the raw SB dimming (CR11) | root-2 (CR11 dep) |
| T7 | CMB → ℓ_P | `ε = u_CMB·ℓ_P³` returns ℓ_P (linkage closes) | root-1 if the linkage fails |
| T8 | LOS temperature | ~10⁻⁶ correlation, mass→cooler; present and not overshooting 10⁻⁵ | root-1 (absent → dead; overshoot → dead) |
| T9 | no expansion smuggled | no a(t), no metric sound horizon, no single-rate assumed | root-4 (§G contraband) |

## ⑨.E Four-root sort (run on every FAIL before the next Route)
- **root-1 — CLAIM false:** an SDT attempt misses the raw datum (wrong sign/size, angle unreached, linkage open).
  KILL the specific claim, name it.
- **root-2 — DEPENDENCY:** CR08 (shell) / CR11 (reciprocity) / CR13 (backtrack) incomplete → ROOT-RELOCATE, OPEN.
- **root-3 — PROMPT under-specified:** the split geometry or parameter count mis-scoped → deepen, re-run.
- **root-4 — GATE CONTRABAND:** an expansion primitive (a(t), a metric sound horizon, a single assumed rate, a
  model-processed number used as the datum) smuggled into the SDT chain. Kill the contraband, not the Route.

---

## Brainstorm — overlooked / high-value factors

- **The mismatch SIGN is the cheapest decisive test** — a single number, from geometry, no fit. Attempt it first.
- **The raw peak angles (Route D) are the hardest thing to fake** — derive the shell from CR08 physics *before*
  looking at ℓ₁≈220, and let the number fall where it falls. An invented shell that lands on 220 would be the
  worst fabrication in the set.
- **The two components must not be double-counted.** A source in a deep well has large `z_emit`; the *same* well
  steepens `σ` for light leaving it. Keep the CR01 ledger clean or the split is fictitious.
- **`c/√3` opaque ceiling & opacity self-jam (CR08)** are the candidate native route to the acoustic shell — the
  scale that would set both the BAO angle and the CMB peak angle. Prioritise it in C and D.
- **The routes with no external counterpart are worth most** — the CMB→ℓ_P linkage (G) and the LOS-temperature
  correlation (H). Neither is a distance-curve contest; both ask "does the raw sky show X." Whether X is there,
  at the right size, is the whole content — and for H it is only estimated, not shown.

---

## ⑤ Success Criteria (dual verdict — SDT vs the raw sky, nothing else)

- **Class A (NATIVE):** the mismatch sign+size (A), the raw `mB(z)` (B), the raw BAO angles (C), and the raw CMB
  peak angles (D) are derived from ℓ_P + geometry at the stated parameter count; the CMB→ℓ_P linkage (G) closes;
  the LOS-temperature correlation (H) is confirmed at the observed size. **This is the target, not the
  expectation.**
- **Class C (CONVERGENCE):** the raw `mB(z)`, BAO angles, and mismatch sign are reached at the stated count, but
  the raw CMB peak angles (D) only approximately (shell scale not yet derived cleanly) — a legitimate partial
  result with the peak-angle derivation named as the open front.
- **Class D / OPEN:** the two-component law is internally consistent (E closes) but one of {mismatch sign, peak
  angles, BAO angles} is unmet; named OPEN with its root. **This is a fully acceptable outcome for a first pass.**
- **KILLED:** the mismatch sign is wrong (C1 dead), OR the raw peak angles cannot come from any physical shell
  (C3 dead), OR the raw `mB(z)` needs a fresh fitted knob per dataset.

**Dual verdict reminder:** prompt completion (Routes run + `RUN_LOG.md`) is separate from physics class (how the
numbers were earned). Every result is reported as **attempt → raw datum → residual**. No rival scoreboard, and
no pre-loaded expected outcome, appears anywhere in the verdict.

## ⑥ Outputs
`RUN_LOG.md` (pre-commits + four-root sorts) · `cr09_hubble_darkenergy.py` — Routes A–H, consuming
`cosmology.hpp` + the raw `PantheonPlusSH0ES.dat` columns · `CR09_DERIVATION.md` (the two-component law, each
step tagged DERIVED/CONVERGENCE/OPEN) · `CR09_VERDICT.md` (dual verdict + §⑧ table, attempt-vs-raw-datum
throughout) · consistency ledger (Route E) · `ADJUDICATION_REGISTER.md` entry.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — CR09 (spec; outcome open)
- Prompt completion target: [A|B|C|D]
- Physics class HOPED (not expected): [NATIVE | CONVERGENCE | OPEN]
- CALIBRATED budget: 0 (σ₀ from the measured local slope; n = the ONE propagation shape param; no mismatch knob)
- Routes this session: [A|B|C|D|E|F|G|H]
- Parameter count committed: emission depth 0 free + propagation n (1 shape) — that is the whole cosmology
- RAW data frozen: PantheonPlusSH0ES.dat (RAW mB, x1, c; drop calibrators + z<0.01); CMB peak angles ℓ₁,ℓ₂,ℓ₃;
  BAO Δθ(z),Δz(z); u_CMB, ℓ_P; CMB×LSS cross-correlation
- Every result reported as: attempt → raw datum → residual
- Forbidden: a(t) / metric sound horizon / a single assumed rate / any model-processed number (θ*, r_drag,
  m_b_corr, an information criterion vs another model) as input, datum, kill-gate, or expected outcome;
  double-counting emission+propagation; inventing a shell to hit an angle; a fitted mismatch parameter;
  asserting any route's outcome before it is run
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| mismatch sign wrong (T1) | re-check gradient-steepening direction | **KILL C1**, name it | force the sign by fitting |
| raw `mB(z)` missed (T3) | re-check the SDT standardization on raw mB | report the miss plainly (root-1) | swap in `m_b_corr` to look better |
| peak angles unreached (T5) | derive the shell from CR08 physics | **OPEN/KILL angular scale**, cite CR08 | invent a shell to hit 220 |
| a processed number creeps in as the datum | replace with the raw observable | — | grade against θ*/r_drag/m_b_corr |
| an expansion primitive enters the chain | strike it (root-4) | — | keep a(t) / metric horizon / single assumed rate |

**Disallowed adjustments:** post-hoc tolerance widening · a fitted mismatch parameter · a model-processed number
as datum or gate · an invented shell · metric expansion / a cosmological constant / a metric sound horizon in
the SDT chain · double-counted redshift components · asserting an outcome the analysis has not produced ·
defining any verdict by reference to a rival model.

**Dual verdict reminder:** there is no pre-loaded expected outcome, for SDT or against it. SDT attempts to derive
the raw sky from ℓ_P + geometry; report where each attempt lands against the photons — hit, miss, or open — on
SDT's own terms. Most routes here have never been run in this frame; the honest default is that they may fail.

---

*CR09 · de-preloaded 2026-07-26 · a SPEC, not a result · one redshift, two components (emission depth Ѻ/r +
propagation octaves), no expansion and no dark energy as inputs · every Route is an ATTEMPT to derive a RAW
observable — raw magnitudes, raw peak angles, raw BAO angles, the CMB→ℓ_P linkage, the line-of-sight temperature
— checked against the sky, with no rival model, no processed products, and no asserted outcome anywhere in the
prompt. Execute direct, no agents.*
