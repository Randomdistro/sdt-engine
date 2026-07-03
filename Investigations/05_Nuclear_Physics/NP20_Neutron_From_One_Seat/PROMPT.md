# NP20: The Neutron from One Seat — 0.782 MeV and −1.913 μ_N from one geometry

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).

---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Does **one** seat geometry (bare proton + one electron driven onto the proton boundary at the framework's already-fixed ~1.83c seat speed) **generate both** neutron numbers — the 0.782 MeV free-decay surplus AND the −1.913 μ_N moment (sign and magnitude) — with **zero free knobs**?
2. **Why does it matter?** — This is the framework's most convincing available closure of the neutron. NP14/NP17 assert "neutron = proton + internal electron"; NP19 reframes the mass surplus as a *resistance difference*, not stored energy. If one declared geometry emits both numbers, the neutron stops being two coincidences and becomes one object. Downstream: NP18 (resonator read-out — flux per seated electron), PPT10/PPT11 (the emitted neutrino), SAR05 (provenance).
3. **How will we find out?** — Four gated phases (§④): **declare one geometry first**, then read the mass off it, then read the moment off it, then prove both came from the *identical* parameters with no per-number fudge.
4. **What would prove us wrong?** — §⑧: a **positive** moment sign → KILL; needing a **different** seat speed for each number → the closure is FALSE (downgrade to two separate COMPUTED results); any fitted parameter → label CALIBRATED and document it.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). Best case: one-geometry-two-numbers (Class A/B). Realistic fallback: Class C/D.

---

## 1. Executive Summary (100–150 words)

The standard textbook says the neutron is a structureless neutral baryon and — folklore — has "no magnetic moment." Both halves are wrong in SDT and wrong in the data: the neutron is a **bare proton plus one seated electron**, and its moment is **−1.913 μ_N** — small, nonzero, **negative**. **The claim under test:** a single seat geometry — the electron driven onto the proton boundary at the framework's already-fixed hyper-relativistic seat speed ~1.83c (the depth-closure / traction value, not a new number) — **generates both** the **0.782 MeV** free-decay surplus (a *form-resistance difference*, per NP19) and the **−1.913 μ_N** moment (sign and magnitude), with **no fitting**. **After this** we will know whether the neutron's two famous numbers are one defect read by two instruments, or two unrelated facts.

---

## 2. Physical Context (250–400 words)

**The picture (plain language).** Take a bare proton — a W=3 trefoil with its handed (ℓ=1) redirection wake. Drive one electron down onto its boundary until it is *seated*: pressed onto the proton surface, circulating at a hyper-relativistic seat speed. That seated composite is the neutron. It is **harder to hold** than the relaxed proton+free-electron pair — the medium grips the seated form more tightly. When the seat lets go (free-neutron decay), the **difference in form-resistance** is released as movement: the 0.782 MeV decay surplus (the energy budget of the emitted electron + the PPT11 neutrino). Per **NP19**, this is *not* stored energy in a well — it is the cost difference between two configurations of the medium.

**One interface, two arrows.** The same seat interface is read two ways:
- **Mass = the medium gripping the form** (resistance to being moved — mass-IN).
- **Magnetic flux = the form moving the medium** (handed redirection radiated out — flux-OUT).
Same interface, opposite arrow. This is *why* magnetic carriers are always the loose, shallow electrons (least-gripped ⇒ least mass-locked ⇒ most free to push flux) — a fact the standard model only stipulates. Cross-ref **CM07/PM01** (ferromagnetism), and note ferromagnetism *living at iron* sits right at the mass/flux crossover.

**Key variables** (all symbols, dimensions, ranges):
| Symbol | Meaning | Dimension | Source |
|---|---|---|---|
| `R_p` | proton boundary (displacement) radius — **never** "charge radius" | m | `measured::R_p` = 8.414e-16 |
| `v_seat` | seat speed of the driven electron | m/s | `traction::v_phase_proton_surface` ≈ 1.831 c |
| `z` | convergence depth at the seat, z = (v/c)² | — | `depth_closure::depth_from_v` |
| `Δ_resist` | form-resistance difference (seated − relaxed) | J → MeV | NP19 reframe |
| `Φ_p` | bare-proton handed flux | μ_N (anchor unit) | from `measured::mu_P` geometry |
| `Φ_seat` | counter-flux of the seated electron | μ_N (anchor unit) | from `v_seat` |
| `μ_n` | composite moment = Φ_p ⊕ Φ_seat | μ_N (anchor unit) | target `measured::mu_N` = −1.913 |

**Unit flag.** μ_N (the nuclear magneton) is a **borrowed yardstick** — it is only the measured anchor's *unit*, not an SDT-native quantity. Express the SDT result in native terms (electron wake / koppa) wherever possible; μ_N appears only to compare against the anchors `measured::mu_P`, `measured::mu_N`. Cross-ref **FLM11** (tape-measure: which instrument reads which arrow).

---

## 3. Theoretical Framework (400–600 words)

**Whitelist inputs only:** {ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p} plus measured observables in their measured units. The measured anchors used here are facts, not standard-model story: neutron moment **−1.913 μ_N** (`measured::mu_N`); proton moment **+2.793 μ_N** (`measured::mu_P`); n–p gap **1.293 MeV** (from `measured::m_n − m_p`); free-neutron decay surplus **0.782 MeV**. We import the **numbers as anchors**; we **do NOT** import the standard-model account (no quarks/gluons, no W-boson exchange, no virtual particles as objects, no wavefunctions, no fields-as-primitives). **No G, no M, no GM** — gravity-style quantities, if they ever appear, come through `ϟ = v²R/c²` and `g = v²/R` only.

**The single geometry (declared, before any number).**
The seat is the electron pressed onto the proton boundary `R_p`, circulating at the seat speed already demanded by the proton trefoil itself:

```
v_seat = c / k_proton_surface = traction::v_phase_proton_surface ≈ 1.831 c
```

This is **not a free parameter**. It is the framework's existing value: the proton trefoil demands `v_phase = 1.831c` at `R_p` (laws.hpp PPT06 / `traction`), and the **depth-closure** bound-motion law `v = c√z` (`depth_closure::v_bound`, laws.hpp §Depth-Closure Theorem) spans Earth→proton and lands on **1.830c** at the proton surface. NP20 takes that one number and asks it to do double duty.

**Number 1 — the MASS (form-resistance).** Per **NP19**, the seated configuration has a *higher form-resistance* than the relaxed proton+free-electron pair. The surplus released on relaxation is the **0.782 MeV** decay surplus (the n–p gap **1.293 MeV** minus the electron rest budget **0.511 MeV** = 0.782 MeV — but NP20 must *generate* 0.782 from the seat geometry's resistance step, not back out the subtraction). The mechanism: the resistance of a form scales with how hard the medium grips it at the seat depth `z(v_seat)`; the seated electron at `v_seat` adds a resistance increment Δ_resist that, on release, becomes free movement.

**Number 2 — the MOMENT (composite flux).** A bare proton carries a handed (ℓ=1) flux Φ_p. Seat onto it a **counter-rotating** electron at `v_seat ≈ 1.83c`. Because the seated electron is hyper-relativistic and *counter*-rotating, its counter-flux **over-rotates the composite negative**: the composite flux Φ_p ⊕ Φ_seat lands at a small **negative** value — **−1.913 μ_N**. On this reading the moment is a **direct read-out of the seat speed**: a second, independent handle on the same 1.83c that the 0.782 MeV constrains. A pure *deepest-seat* (mass-only, flux-zero) would predict **exactly 0**; the data say **almost zero, with a negative leak** — and that leak is the gift that fixes the seat speed.

**CRITICAL FRAMING (obey — Harvey's correction).** Do **NOT** frame this as "make the mass defect and the moment *agree*" or as a cross-check. In the one-ledger view they are the **same defect read by two instruments** (mass spectrometer vs magnetometer — FLM11). They cannot agree or disagree, only be **re-expressed**; the cross-check framing smuggles two separate accounts back in. The legitimate, *narrower* question is a **derivation** task: does one seat geometry **GENERATE** both numbers? Mass = medium gripping form (in); flux = form moving medium (out) — same interface, opposite arrow.

**Constraints.** Both numbers must fall out of the **identical declared parameters** {`R_p`, `v_seat`, counter-rotation sense}. Any per-number adjustment is a FAIL of the *closure* (the numbers may still survive as two separate COMPUTED results).

---

## 4. Investigation Strategy (800–1200 words — be excessive)

> **Run discipline:** PRE-COMMIT → IMPLEMENT → EXECUTE → COMPARE → DECIDE → ADJUST → GATE (per `PROMPT_EXECUTION_PROTOCOL.md` §1). No phase N+1 until N is PASS-GATE or documented DEFER. **One geometry is declared in P1 and frozen** — P2 and P3 may *read* it but may not *re-tune* it.

### Phase 1 — Fix the single seat geometry (declare before any number) — ~1–2 h
- **Goal:** Write down ONE geometry with explicit symbols and dimensions, frozen for the whole investigation.
- **Method:**
  1. Seat **radius** = proton boundary radius `R_p` (`measured::R_p`). Say "boundary/displacement radius" — **never** "charge radius."
  2. Seat **speed** `v_seat = traction::v_phase_proton_surface` (≈ 1.831 c). Independently confirm via `depth_closure::v_bound` at the proton surface that the bound-motion law `v = c√z` lands on ≈ 1.830 c — the two must be the **same number** (this is the depth-closure / traction reconciliation). Reconcile in prose with NP14/NP17 ("neutron = proton + internal electron").
  3. Seat **sense** = electron **counter-rotating** relative to the proton's handed wake (declare the sign convention explicitly; this sign is what makes Number 2 negative).
  4. Convert to depth: `z_seat = depth_closure::depth_from_v(v_seat)`.
- **Pre-committed success metric:** `v_seat` agrees with `depth_closure::v_bound` at `R_p` to **< 1%**; all symbols carry dimensions; geometry table printed and frozen.
- **Failure trigger:** the traction value and the depth-closure value disagree by **> 1%** → the "same 1.83c" premise is unsupported.
- **Gate:** P2 forbidden until the geometry table is printed and frozen in `RUN_LOG.md`.
- **OUT OF SCOPE:** computing either physical number; choosing tolerances for P2/P3 (those are pre-committed below, not now).

### Phase 2 — Read the MASS off that geometry → 0.782 MeV — ~2–3 h
- **Goal:** From the frozen geometry alone, compute the form-resistance step → **0.782 MeV**.
- **Method:**
  1. Compute the resistance increment Δ_resist of the seated electron at depth `z_seat` (NP19 resistance reframe — resistance ∝ how hard the medium grips the form at that depth). Use only whitelist constants + the frozen geometry.
  2. Express the released surplus on relaxation in MeV. **Sanity rail (comparison column only, not the mechanism):** 1.293 MeV (`measured::m_n − m_p`) − 0.511 MeV (electron rest budget) = 0.782 MeV. The mechanism must *generate* 0.782, not subtract to it; the subtraction is an OBSERVED-TARGET column.
- **Pre-committed success metric:** predicted surplus within **±15%** of 0.782 MeV (stretch: ±10%).
- **Failure trigger:** |pred − 0.782|/0.782 **> 15%**.
- **Pivot (from §⑩):** refine the resistance model's geometry factor *within the frozen geometry* (no new seat speed); if still > 15% → **OPEN** the resistance-magnitude mechanism (NP19/NP21 dependency); do **not** PASS by widening tolerance.
- **Gate:** P3 may start in parallel ONLY after the geometry is frozen (P1 PASS); P2 and P3 share the geometry but are scored independently.
- **OUT OF SCOPE:** any moment computation; re-deriving `v_seat`.

### Phase 3 — Read the MOMENT off the SAME geometry → −1.913 μ_N (sign AND magnitude) — ~2–3 h
- **Goal:** From the *identical* frozen geometry, compute the composite flux → **−1.913 μ_N**, sign first.
- **Method:**
  1. Bare-proton flux Φ_p: anchor to the geometry that yields `measured::mu_P` = +2.793 (native expression in electron-wake / koppa terms; μ_N is the borrowed reporting unit only — **flag it**).
  2. Seated-electron counter-flux Φ_seat from `v_seat` (hyper-relativistic, counter-rotating).
  3. Compose: μ_n = Φ_p ⊕ Φ_seat. The counter-rotation + hyper-relativistic over-rotation must drive the composite **negative**.
- **Pre-committed success metric:** **sign negative** (hard gate) AND magnitude within **±15%** of −1.913 μ_N (stretch: ±10%).
- **Failure trigger:** sign **positive** → **KILL** (see §⑧). Magnitude off by **> 15%** with correct sign → PIVOT.
- **Pivot (from §⑩):** refine the flux-composition geometry *within the frozen geometry*; if magnitude still > 15% → **OPEN** with correct-sign partial result. **Do NOT** introduce a different seat speed to fix the magnitude — that would break the closure (see P4).
- **Gate:** P4 forbidden until both P2 and P3 have a DECIDE recorded.
- **OUT OF SCOPE:** the deuteron / composite-nuclei moments (that is NP15); the neutrino spectrum (PPT11).

### Phase 4 — One-geometry consistency (the actual test) — ~1 h
- **Goal:** Prove both numbers came from the **identical declared parameters** with **ZERO free knobs**.
- **Method:**
  1. The tool must compute the **0.782 MeV** path and the **−1.913 μ_N** path from the **same** {`R_p`, `v_seat`, sense} object — a single struct passed to both readers, no second copy, no per-number override.
  2. Emit a **zero-knob check**: enumerate every constant consumed; each must be either a whitelist invariant, a `measured::` anchor used as OBSERVED-TARGET, or the one frozen geometry. **Any per-number fudge parameter = FAIL.**
  3. Print the **dual read-out**: "same defect, two instruments — mass spectrometer reads `Δ_resist`, magnetometer reads `μ_n`."
- **Pre-committed success metric:** the knob count consumed by P2-but-not-P3 (and vice-versa) is **exactly 0** beyond the shared geometry; both numbers reproduced from the single struct.
- **Failure trigger:** any parameter touched by only one number → the closure is **FALSE** → downgrade to **two separate COMPUTED results** (honest Class C/D), and say so.
- **Gate:** investigation complete; write VERDICT.
- **OUT OF SCOPE:** declaring victory if a fitted parameter was needed — that is CALIBRATED and must be documented (§⑧).

**Native-first rule.** No `atomic::`/`bridge::` wrapper may stand in for a Phase-1/2/3 native step; the seat geometry and the two readers are the mechanism. Rivals (standard-model quark moment, weak-decay Q-value) may appear **only** as OBSERVED comparison columns.

---

## 5. Success Criteria (200–300 words)

Use canonical labels. **Dual verdict required** (prompt completion A–F + physics class).

- ✅ **PASS (Class A: Derived / one-geometry closure):** ONE frozen seat geometry generates **both** 0.782 MeV (±10%) and −1.913 μ_N (correct **negative** sign, ±10%) with the **zero-knob check passing**. No fitted parameters beyond whitelist. *Publish:* "The neutron's two numbers are one defect read by two instruments."
- ✅ **QUALIFIED (Class B/C: Convergence):** Both numbers from the shared geometry within **±15%**, sign correct, with 1 documented approximation in the resistance or flux-composition model. *Publish:* honest convergence; name the approximation.
- ⚠️ **QUALIFIED PENDING (Class D: Computed):** The two numbers reproduced but **NOT** from one geometry — each needed its own parameter. This **falsifies the closure**; report as **two separate COMPUTED results**, not a closure. *Next:* NP19/NP21 to find the missing shared handle.
- ❌ **FAIL (Class F / KILLED):** Moment sign comes out **positive** → KILL (the central physical picture is wrong). Or a fitted seat speed is required per number with no whitelist justification.

**Hard gates (non-negotiable):** (1) moment sign must be negative; (2) one geometry, zero per-number knobs; (3) μ_N flagged as borrowed unit; (4) no "charge radius," no G/M/GM, no quarks/wavefunctions in the chain. Failures invoke **PIVOT / KILL / OPEN**, **never** retro-PASS.

---

## 6. Outputs (150–300 words)

1. **`NP20_DERIVATION.md`** — the frozen seat geometry (symbols, dimensions, sign convention), the resistance→0.782 MeV derivation (NP19-grounded), the flux-composition→−1.913 μ_N derivation; every line tagged DERIVED / COMPUTED / CALIBRATED(n) / MEASURED-INPUT / OBSERVED-TARGET / ASSUMED / PENDING. μ_N flagged as borrowed yardstick throughout.
2. **`np20_one_seat.cpp`** (and/or **`np20_one_seat.py`**) — standalone tool (`#include <sdt/laws.hpp>`; compile `cl /std:c++20 /EHsc /O2 /I Engine/include`). Builds ONE seat-geometry struct, passes it to **both** readers, prints **both numbers** (0.782 MeV and −1.913 μ_N with sign) plus the **zero-knob check** (enumerated constant ledger, FAIL if any per-number knob). No local constant namespaces.
3. **`np20_results.txt`** — machine stdout: table [quantity | SDT value | anchor | % error | sign-check | label].
4. **`NP20_VERDICT.md`** — dual verdict header (prompt completion A–F + physics class NATIVE/CONVERGENCE/DEGENERATE/KILLED/OPEN); falsification table updated; closure verdict (one-geometry vs two-results).
5. **`RUN_LOG.md`** — **mandatory**: Pre-Run Commitment Block filled before coding, ADJ-### entries, per-phase gates.

---

## 7. Dependencies & References (150–250 words)

**Upstream (Required):**
- **NP19** — mass-defect-as-resistance: grounds Number 1 (the 0.782 MeV is a *resistance difference*, not stored energy). This is the load-bearing dependency.
- **NP14** — proton–neutron mass difference / "neutron = proton + internal electron"; reconcile the seat picture with it.
- **NP17** — interleaved 6π trefoils, neutron = p + internal e (shared electron = binding).
- **NP15** — nuclear magnetic moments from vortex geometry (proton +2.793, neutron −1.913 read-outs).
- **Depth-Closure Theorem** (`depth_closure` in `laws.hpp`) + **PPT06 `traction`** — the 1.83c seat speed (`v = c√z` Earth→proton = 1.830c; `v_phase_proton_surface` = 1.831c).

**Downstream (Blocked / enabled):**
- **NP18** — resonator read-out: flux per seated electron uses NP20's Φ_seat.
- **PPT10 / PPT11** — straight-light / oscillation: the emitted neutrino of the 0.782 MeV release.
- **SAR05** — provenance audit of this closure.

**Related (Informative / read in parallel):**
- **FLM11** — tape-measure: which instrument (mass spectrometer vs magnetometer) reads which arrow of the same interface.
- **CM07 / PM01** — ferromagnetism: why magnetic carriers are the loose, shallow electrons; ferromagnetism at iron = the mass/flux crossover.
- Sibling set: NP21 (resistance landscape), APS06 (emission ladder).

---

## 8. Falsification Tests (150–250 words)

| Test | Trigger (numeric) | Predicted (closure holds) | If FAIL |
|------|-------------------|----------------------------|---------|
| **T1 — Sign** | composite moment sign | **negative** (−1.913 μ_N) | sign **positive** → **KILL** — the counter-rotating-seat picture is wrong |
| **T2 — Mass magnitude** | \|pred − 0.782\|/0.782 | ≤ 15% (stretch 10%) | > 15% → PIVOT resistance geometry; else **OPEN** (NP19/NP21) |
| **T3 — Moment magnitude** | \|pred − 1.913\|/1.913 | ≤ 15% (stretch 10%), sign neg | > 15% with right sign → PIVOT flux composition; do NOT change seat speed |
| **T4 — One geometry** | per-number knob count beyond shared geometry | **exactly 0** | any per-number knob → **closure FALSE**; downgrade to two separate COMPUTED results |
| **T5 — Same seat speed** | v_seat used by mass vs by moment | **identical** number (the one 1.83c) | different seat speed per number → **not one geometry** → FAIL the closure |
| **T6 — Borrowed-unit honesty** | μ_N treated as native? | flagged borrowed yardstick | treating magnetons as native quantity → audit fail |

**Recovery:** T2/T3 magnitude misses → PIVOT *within* the frozen geometry (refine the resistance / flux-composition geometry factor), never by re-tuning `v_seat` or widening a committed tolerance. T1 positive sign or T4/T5 failure are **terminal for the closure** (not for the two numbers, which may survive as COMPUTED). If a fitted parameter is genuinely required, label it **CALIBRATED(1)** and document it — do not hide it inside the geometry.

---

## 9. Implementation Notes (200–300 words)

- **Double precision** throughout (C++ `double`). Hyper-relativistic `v_seat ≈ 1.83c` means **do NOT** apply a naive `√(1−v²/c²)` Lorentz factor (it goes imaginary). The seat is an SDT depth-closure object (`z = (v/c)² > 1` regime); use the depth formulation `z = depth_from_v(v_seat)` and the framework's bound-motion law, **not** textbook SR. Document the v>c regime explicitly (it is the W+1 / traction superluminal phase velocity, not a moving rest-mass).
- **One struct, two readers.** Enforce the closure structurally: a single `struct SeatGeometry { R_p; v_seat; sense; z_seat; }` constructed once, passed `const&` to `mass_surplus_MeV(seat)` and `composite_moment_muN(seat)`. The zero-knob check then becomes a *compile/runtime* fact, not a claim.
- **Sign convention.** Fix and print the rotation-sense sign at the top; the negative moment must emerge from `sense = counter`, not from an absolute-value flip. Print intermediate Φ_p and Φ_seat with signs.
- **No local constants.** Pull `R_p`, `v_phase_proton_surface`, `mu_P`, `mu_N`, `m_n`, `m_p` from `sdt::laws::measured` / `traction`; redefining any of them locally is an anti-creep violation.
- **Ledger every print.** Each printed number carries exactly one tag (MEASURED-INPUT / DERIVED / COMPUTED / CALIBRATED(n) / OBSERVED-TARGET / IDENTITY / ASSUMED / PENDING).
- **Comparison columns only.** Standard-model quark moment and weak Q-value may print as OBSERVED rivals — never inside the SDT derivation chain.
- **Visual hint:** plot composite μ vs `v_seat/c` around 1.83 — confirm μ crosses zero and goes negative there (the moment as a read-out of the seat speed); and plot Δ_resist vs `z_seat`.

---

## ⑩ Adaptive Execution Protocol (MANDATORY)

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG. See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — NP20
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 — any fitted param must be declared CALIBRATED(n) and documented]
- Engine namespaces: measured (R_p, mu_P, mu_N, m_n, m_p), traction::v_phase_proton_surface,
  depth_closure (depth_from_v, v_bound), bridge::k_proton_surface
- Frozen geometry (P1, declared before numbers): { R_p, v_seat≈1.831c, sense=counter }
- Phase thresholds (committed before run): P1 v_seat agreement <1%; P2 mass ±15% (stretch 10%);
  P3 moment sign NEGATIVE (hard) + magnitude ±15% (stretch 10%); P4 per-number knobs = 0
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant
  namespaces; different seat speed per number; "charge radius"; treat μ_N as native; G/M/GM/quarks/ψ
```

### Pivot table (numeric triggers)

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden |
|-------------------|------------------------|----------------|-----------|
| P0/units sanity fails | Fix engine refs; verify `traction`, `depth_closure`, `measured` symbols | STOP — report blocker | Fit to target |
| P1: v_seat vs `v_bound` disagree > 1% | Recheck `k_proton_surface` / R_p; confirm same regime | **OPEN** the "same 1.83c" premise; do not freeze | Hand-pick a seat speed |
| P2: \|mass − 0.782\|/0.782 > 15% | Refine resistance geometry factor **within frozen geometry** (NP19) | **OPEN** resistance magnitude (cite NP19/NP21) | Widen tolerance; new seat speed |
| P3: moment magnitude > 15% (sign right) | Refine flux composition **within frozen geometry** | **OPEN** with correct-sign partial | Change v_seat to fix magnitude |
| P3: moment sign **positive** | — (no pivot) | **KILL** the closure (T1) | Absolute-value flip to fake sign |
| P4: any per-number knob > 0 | Re-route through shared struct | Downgrade to **two separate COMPUTED** (Class D); say so | Claim one-geometry closure |
| v > c handling breaks (NaN/imag) | Use depth formulation `z=(v/c)²`, not SR γ | **OPEN** the regime | Force-clip v to <c |
| Rival matches but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (NP19 reframe) | **DEFER** P2; cite NP19 | — | Fake PASS |

### Allowed adjustments
- Finer numerics (bracket/mesh); phase splits (2a resistance model, 2b magnitude); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ — **all within the one frozen geometry**.

### Disallowed adjustments
- Post-hoc tolerance widening · coefficient plugs · a different seat speed per number · `atomic::`/GM/G/quarks/ψ in the native chain · "charge radius" · treating μ_N (magnetons) as a native quantity · framing the two numbers as a cross-check that can "agree."

### Dual verdict reminder
Report **prompt completion (A–F)** separately from **physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN)**. Best case: one-geometry-two-numbers (Class A/B). Realistic fallback: Class C/D. A closure that needs two geometries is **two COMPUTED results**, reported honestly — not a retro-PASS.

---

*NP20 · SPEC · the neutron from one seat · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
