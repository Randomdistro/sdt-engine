# 05 — Provenance & Correspondence: The Audit Spine

> **Purpose.** A hostile-but-fair classification for every formula, constant, and
> result in the SDT corpus. It supersedes the single-axis certification labels of
> `00_Ruleset.md` (which are retained as a crosswalk, §4) by separating the **two
> questions that those labels conflated**:
>
> 1. **Provenance** — where did the derivation *start*? (an audit of the path)
> 2. **Correspondence** — what does the result *match*? (an audit of the endpoint)
>
> These are **orthogonal**. The headline class (A–F) is a projection of the 2-D grid
> they span. Keeping them separate is what defeats the predictable attack — see §3.

---

## 1. The two independent label axes

Every formula carries **both** of the following. Neither implies the other.

```text
provenance_status   :  SDT-first | calibrated | external-input | unresolved
correspondence_status:  known-match | novel-prediction | internal-only | pending-test
```

**provenance_status** — answers "what were the inputs to the derivation chain?"
- `SDT-first` — derived from {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} + SDT axioms only. No
  target value entered the derivation. The result is whatever the geometry produced.
- `calibrated` — exactly one parameter was fitted to data (must be named at the call site).
- `external-input` — a functional form, constant, or relation was imported from outside
  SDT (e.g. an interpolation shape borrowed from another framework). Honest, but not SDT.
- `unresolved` — the derivation is incomplete or the inputs are not yet pinned.

**correspondence_status** — answers "what does the finished result line up against?"
- `known-match` — coincides with an independently established empirical/theoretical value.
- `novel-prediction` — predicts something not currently measured, **with a stated test path**.
- `internal-only` — has no external referent yet (a pure internal SDT quantity).
- `pending-test` — a comparison is intended but not yet performed (or failed).

---

## 2. The A–F spine (projection of the grid)

The single-letter class is assigned from the pair. It is a *convenience projection*;
the two labels above remain the ground truth.

| Class | name | provenance | correspondence |
|---|---|---|---|
| **A** | Pure SDT axiom / definition | SDT-first (posited) | internal-only |
| **B** | SDT-first derived internal result | SDT-first (derived) | internal-only |
| **C** | SDT-first result converging on known physics | SDT-first (derived) | known-match |
| **D** | SDT-first novel prediction w/ known test path | SDT-first (derived) | novel-prediction |
| **E** | Calibrated bridge result | calibrated | (any, usually known-match) |
| **F** | Pending / unverified / failed | unresolved | pending-test |

```text
                         correspondence →
provenance     internal-only   known-match    novel-prediction   pending-test
   ↓
SDT-first         A / B             C                 D              (→F)
calibrated          E               E                 E              (→F)
external-input    (flag)          (flag)            (flag)           (→F)
unresolved          F               F                 F               F
```

- **A vs B** split a single grid cell `(SDT-first × internal-only)` by whether the item
  is *posited* (axiom/definition, A) or *derived* (B).
- **An axiom that also matches known physics** (e.g. the movement budget `v_circ²+v²=c²`
  replacing SR) is provenance `SDT-first(axiom)` **and** correspondence `known-match`.
  Its A–F letter is **A** (provenance-of-an-axiom dominates the projection), but the
  *second label carries the correspondence* — this is precisely the case the dual scheme
  exists to represent and the single-axis scheme could not.
- **external-input** items never receive a clean A–D letter. They are flagged explicitly
  (e.g. "C-asymptotes / external-input-shape") so a borrowed component can never be
  laundered into an SDT derivation. (This is the M4 lesson, §5.)

---

## 3. Why C is not derivative — the structural defence

**The key consequence: C is a *convergence* category, not a plagiarism/translation category.**

The predictable attack:

> "You just rewrote existing equations."

The response is not rhetorical — it is forced by the grid:

> "No. The two labels are independent axes. `provenance = SDT-first` is an audit of the
> **derivation path** (which inputs entered, in what order) and is verifiable line-by-line
> in the code. `correspondence = known-match` is an audit of the **endpoint** and is only
> evaluated *after* the SDT computation has already produced the number. A known equation
> appears in a C result solely as an external correspondence check performed downstream of
> the SDT-first computation. To call C 'derivative' is to read the correspondence label as
> if it were the provenance label — a category error the two-axis scheme makes explicit."

Operationally, a result earns **C** only if the **circularity assertion** holds: no field
of the SDT derivation may depend on the known value it later matches. (Same assertion used
in CQ26 §10 and enforced in the harness call-graph.) If the known value entered the
derivation, the result is **E** (calibrated) or `external-input`, never C.

The distinction is testable: delete the correspondence check entirely and a C result is
**unchanged** (the number was already produced); delete it from an E result and the number
**vanishes** (it had no independent source). That asymmetry is the operational definition.

---

## 4. Crosswalk to the legacy 5 labels (`00_Ruleset.md`)

The legacy labels are a lossy single-axis encoding. Mapping:

| Legacy | provenance | correspondence | A–F |
|---|---|---|---|
| DERIVED | SDT-first | internal-only / known-match | A,B (internal) or C (match) |
| COMPUTED | SDT-first | (by correspondence) | B / C / D |
| CALIBRATED | calibrated | usually known-match | E |
| OBSERVED | SDT-first (typically) | known-match | C |
| PENDING | unresolved | pending-test | F |

Legacy `DERIVED`/`COMPUTED`/`OBSERVED` cannot distinguish B from C from D, because they
do not record the correspondence axis. The new scheme is strictly richer; legacy tags
remain valid as a coarse provenance hint.

---

## 5. Worked audit pass — the galaxy/cross-scale work (2026-06)

Applying the spine to the results produced this cycle. Anchors verified against live code.
Every row carries both labels; the A–F letter is the projection.

| Result | formula | provenance | correspondence | A–F | anchor |
|---|---|---|---|---|---|
| Movement budget | `v_circ² + v² = c²` | SDT-first (axiom) | known-match (replaces SR) | **A** | `laws.hpp:401` (T10) |
| Convergence pressure | `Φ = N·ε ; P_conv = Φ/ℓ_P³` | SDT-first (axiom) | internal-only | **A** | `laws.hpp:215,219` |
| Koppa definition | `ϟ = v²R/c²` | SDT-first (definition) | known-match (= GM/c²) | **A** | `laws.hpp:546` |
| Koppa per baryon | `ϟ_b = ℓ_P²·c·m_p/ℏ` | SDT-first (derived) | known-match (= GM/c² via G=ℓ_P²c³/ℏ) | **C** | `laws.hpp:594` |
| Transverse gradient → bending | `∇⊥z = ϟ·b/r³ ; α=4ϟ/b` | SDT-first (derived) | known-match (GR 4GM/c²b, Eddington 1.75″) | **C** | `cq15…cpp:429` |
| Convergence floor scale | `a₀ = c·H₀/2π = 1.042e-10` | SDT-first (derived) | known-match (MOND/RAR a₀≈1.2e-10) | **C** | `galactic.hpp:77` |
| Bulge = spherical | `v² = c²·ϟ_enc/R` | SDT-first (derived) | known-match (exact Newtonian spheroid) | **C** | `galactic.hpp:508` |
| M3 disk (1/r³ line) | `v² = c²·ϟ_disk·f_enc/h_R` | SDT-first (derived) | novel-prediction; underperforms (RMS 34.7%) | **D→F** | `e46_twin_regime.cpp` |
| M4 floor law | `g_obs=g_bar/(1−e^{−√(g_bar/a₀)})` | **mixed**: SDT-first asymptotes / **external-input** crossover shape | known-match (RAR; RMS 23.8%, BTFR 3.58) | **C-asymptotes / external-shape** | `INVESTIGATION_twin_regime.md` §5c |
| CQ26 cross-scale collapse | `B=Φ(ξ), ξ=g_self/a₀` | SDT-first (ξ, a₀) / external Φ-shape | **novel-prediction** (atomic+stellar+galactic on one curve, 8.8% RMS; neg-control 6×) | **D** (shape external) | `cq26…cpp`, `INVESTIGATION.md` |
| Eclipse cross-section | `κ_area = 9.1e-29 m²` | **calibrated** (to 175 M☉/pc²) | known-match (≈1.37 σ_Thomson) | **E** | `galactic.hpp:1375` |
| Single-regime eclipse v | `v ≤ v_Kep/√2` (CQ23) | SDT-first (derived) | failed on real SPARC (RMS 66%) | **F** | `INVESTIGATION.md` |

### Reading the two pivotal rows

- **`a₀ = c·H₀/2π` is C, not E.** It is the strongest result of the cycle: the MOND/RAR
  acceleration scale — historically a *fitted* constant — emerges SDT-first from c and H₀
  with no target value entered. The CQ26 negative control (wrong floor 100·a₀ degrades the
  cross-scale collapse 6×) is the operational proof of §3: the SDT-derived value is *required*
  by the data, so the correspondence is convergence, not calibration.
- **M4 is deliberately split.** Its asymptotes (`Φ→1`, `Φ→√(g_bar·a₀)`) are SDT-first and the
  scale `a₀` is C; but the interpolation *between* them is the borrowed MOND-simple shape —
  `external-input`. It must never be reported as a single clean C. The honest claim is
  "SDT supplies the floor scale (C); the crossover shape is borrowed (external-input);
  deriving that shape from occlusion solid-angle geometry would move it to D."

---

## 6. Authoring rule (applies to all new work)

Every formula committed to the corpus — in `.hpp`, in a benchmark, or in an investigation —
SHALL carry both labels at its definition site, e.g.:

```cpp
// provenance: SDT-first   correspondence: known-match   [class C]
//   derivation: ℓ_P,c,H₀ -> a₀ ; correspondence check vs MOND a₀ is downstream-only
inline constexpr double a_0_SDT = c * H_0_SI / (2.0 * PI);
```

A result may be promoted A→B→C→D as derivation and testing advance, or demoted to F on
failure. A `calibrated` or `external-input` provenance may **never** be relabelled SDT-first
without a new derivation that passes the §3 circularity assertion. The audit is hostile by
construction (it assumes every C is a disguised E until the assertion is shown) and fair by
construction (it grants that a passed assertion makes convergence a *result*, not a rewrite).
