# PPT11 — Neutrino Flavour Oscillation in SDT

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Tier:** 5 — **THE HARDEST OPEN PROBLEM** in the neutrino account. This is the *price of admission*, not a footnote. Treat with maximum honesty: this is an `[OPEN]` spec written to **attack a known debt**, not a victory lap. The most likely honest outcome is a **sharpened open problem (Class D-or-OPEN)**, not a closure.

---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — If a neutrino is a hard, localised, *straight* electron-stuff vortex (PPT10), we have **no SDT-native account of (a) what the three flavours electron/muon/tau ARE, nor (b) why a straight thread periodically becomes muon-stuff then tau-stuff IN FLIGHT** — without importing a quantum superposition-of-mass-eigenstates wavefunction (prohibited).
2. **Why does it matter?** — This is the single datum **most in tension** with the straight-light-electron picture. Flavour change in flight is *measured* (electron↔muon↔tau conversion is real; the original "massless" assumption is dead). If SDT cannot produce **periodicity from native geometry**, PPT10's straight-thread neutrino has an unfilled hole. NP18 (resonator) tests *conversion*, not *flavour* — **the experiment cannot rescue this; it needs theory.**
3. **How will we find out?** — Four gated phases (§④): P1 define three flavours as three distinct SDT configurations of the straight vortex (state the geometric DoF); P2 propose a native **beat/relay** mechanism for interconversion *without a wavefunction*; P3 derive an oscillation **length** from the engine's three mass minima and compare to measured solar/atmospheric scales, **no fitted knob**; P4 recursive honest failure analysis to root cause.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers. Headline: if **no** native (non-wavefunction) mechanism yields periodicity → record `[OPEN]` (do **not** fabricate); if the derived length is many orders off and no geometric reason recovers it → **KILL** the naive beat model and park.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F: did the tool do §④–§⑥?) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / **OPEN**). Failures **PIVOT / KILL / OPEN** — never retro-PASS.

---

## ① Executive Summary (≈130 words)

**The question:** In SDT a neutrino is a hard, localised, *straight* solid vortex of electron-stuff (W=0, open winding — never closes). Measured fact: such a thread **changes flavour in flight** (νₑ ↔ ν_μ ↔ ν_τ), and oscillation **requires nonzero mass**. **What ARE the three flavours geometrically, and what makes a straight thread cycle between them periodically** — *without* a forbidden quantum superposition wavefunction? **Why it matters:** flavour oscillation is the datum most hostile to the straight-thread picture; resolving it (or honestly failing) **completes or kills** the SDT neutrino account begun in PPT10. **Expected outcome:** an SDT-native **geometric beat** between three near-degenerate straight-vortex configurations, with a beat *length* set by their resistance (mass) difference — **or** a sharpened `[OPEN]`. We expect Class **D-or-OPEN**, not closure.

---

## ② Physical Context (≈320 words)

**The picture (PPT10, upstream).** Light is a straight, transverse relay disturbance in the spation lattice. The neutrino is its *hard, localised* cousin: a solid straight vortex of electron-stuff that **propagates WITH the relay, not against it** (hence near-zero cross-section). Its winding is **open (W=0)** — it never closes into a torus, so there is no toroidal circuit, no handed redirection (no "charge"), no ℓ=2 wake (μ_ν=0, PPT04). The wake radius is macroscopic (`R_wake = ℏ/(mc) ≈ 3–10 μm`) but **non-occluding**: the largest wake-to-body ratio of any particle (`~10¹⁸`), which **IS** the weak interaction, expressed geometrically.

**The debt this spec attacks.** A *straight* thread of one substance has, naively, *nothing to cycle*. Yet measurement is unambiguous: the **flavour** (electron/muon/tau identity) changes periodically along the flight path, and the period requires nonzero mass differences. Standard physics narrates this as a superposition of mass eigenstates beating against each other — **a wavefunction, which SDT prohibits as a primitive import.** SDT must find the *mechanism in the geometry of the straight vortex itself.*

**The candidate foothold (engine).** `neutrino.hpp` already carries **three measured mass eigenstates** (`m_ν1 ≈ 0.02`, `m_ν2 ≈ 0.029`, `m_ν3 ≈ 0.06 eV`) as **three distinct V_disp minima** with **three distinct wake radii** (`R_wake ≈ 9.87 / 6.80 / 3.29 μm`) and exclusion radii. The header narrates oscillation as **"helical pitch precession between three stable pitch angles of the open winding"** — and explicitly notes the open winding *can* precess **precisely because it is not topologically locked** (unlike the W=1 electron or W=3 proton). This is the seed; this spec must turn the narrative into a **derived length** or honestly fail.

**Key variables (define all; carry dimensions):**

| Symbol | Meaning | Dimension |
|--------|---------|-----------|
| `W` | winding number of vortex | dimensionless (`=0` neutrino) |
| `θ_pitch,i` | helical pitch angle of straight vortex, config `i∈{1,2,3}` | rad |
| `m_νi`, `V_disp,i` | resistance (mass) / displacement volume of config `i` | eV·c⁻² / m³ |
| `R_wake,i = ℏ/(m_νi c)` | wake radius of config `i` | m |
| `ΔR_resist` | resistance/length difference between configs (beat driver) | (set in P2) |
| `L_osc` | spatial period of flavour cycle (beat length) | m |
| `E_ν` | neutrino kinetic content (relay speed budget, Law V) | eV |

---

## ③ Theoretical Framework (≈520 words)

**Permitted inputs only:** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in measured units (here: the three `m_νi` minima, the two measured mass-squared splittings `Δm²₂₁, Δm²₃₂`, and the measured solar/atmospheric oscillation lengths as **OBSERVED-TARGET** comparison anchors). **Prohibited, must not enter the SDT chain:** quantum superposition wavefunctions, mass-eigenstate kets, fields-as-primitives, `G_F`, virtual particles as objects, `G/M/GM`, ΛCDM, wave-particle duality. Never write "charge radius" — the neutrino has **no** handed redirection at all.

**Law anchors.**
- **Law VI (topology).** W=0 open winding. The three flavours must be **three configurations of the same W=0 object** — so the distinguishing degree of freedom is **internal**, not a winding change. (If a flavour change required ΔW, it would be a *different particle*, not oscillation. Pin this.)
- **Law V (movement budget).** `v_relay² + v_internal² = c²`. A straight vortex carries the unspent budget in an **internal circulation / pitch**. Different pitch angles `θ_pitch,i` spend the budget differently → different `V_disp,i` → different resistance `m_νi`. This is the bridge from "geometry" to "mass."
- **Law IV (mass as throughput-reorganisation cost).** `V_disp,i = 3 m_νi ℓ_P³ c² / Φ` (engine form). The three minima are three local **resistance** minima of the same straight object.
- **Law I / relay.** The neutrino relays *through* the lattice. As it relays, its internal pitch **precesses** against the lattice cadence — the engine's existing claim. The beat between near-degenerate configs is what must set `L_osc`.

**The native hypothesis to test (state as falsifiable, not assumed).**
> The three flavours are **three nearly-degenerate stable pitch/configuration minima** of one straight W=0 vortex. As it relays, the vortex is not pinned in a single minimum; its internal pitch **precesses/beats** between them. The **beat length** `L_osc` is set by the *difference in resistance (mass)* between configurations: a larger Δ(resistance) → faster phase accumulation → **shorter** beat length. Flavour = which configuration currently dominates the internal pitch.

**The hard reconciliation (must be confronted, not dodged).** If **all three** flavours are W=0, what internal DoF distinguishes them and **cycles**? Candidate answer to develop in P1: the **pitch angle of the open helix** (a continuous internal DoF that does *not* change the integer winding), with three stable values set by the three V_disp minima. Tie this DoF count explicitly to **FLM11's degrees-of-freedom census** of the straight vortex — if FLM11 grants the straight thread ≥1 free internal angular DoF, the beat is geometrically licensed; if it grants **zero**, the beat is **forbidden** and this is an immediate `[OPEN]`/KILL signal (flag in P1 gate).

**What "winning" cannot be.** Reproducing `L_osc = 2.48·E[MeV]/Δm²[eV²]` by *reading* `Δm²` from the engine's `measured::` block is **IDENTITY-PASS**, not a derivation — `Δm²` there is a measured input. The decisive test (P3) must build the beat length from the **independently-listed three mass minima as resistances/lengths** and show the *resulting* splitting lands on the measured scale **without** being handed `Δm²` as a knob.

---

## ④ Investigation Strategy (≈1000 words — be excessive; ≥4 phases, numeric gates)

> **Run order is gated.** No phase begins until the prior phase returns **PASS-GATE** or a documented **DEFER**. Pre-commit every threshold in `RUN_LOG.md` (§⑩ block) *before* coding. Read `neutrino.hpp`, PPT10, PPT04, and FLM11's DoF census first.

### Phase 1 — Define the three flavours as three SDT configurations (the geometry) — **GATE**

- **Goal:** State explicitly the **internal geometric degree of freedom** that distinguishes νₑ, ν_μ, ν_τ while all remain **W=0**, and map each flavour-relevant config to one of the engine's three V_disp / wake-radius minima.
- **Method:**
  1. From `law_VI` confirm W=0 is *unchanged* across flavours (a flavour change is **not** a winding change). Record this as a hard constraint.
  2. Identify the candidate continuous internal DoF: the **helical pitch angle `θ_pitch`** of the open vortex (Law V budget split → Law IV resistance). Cross-check against **FLM11's DoF census**: does the straight W=0 vortex *possess* ≥1 free internal angular DoF?
  3. Tabulate the three engine minima with their geometry:

     | Config | `m_νi` (eV) | `V_disp,i` (m³) | `R_wake,i` (μm) | `θ_pitch,i` (assign) |
     |--------|------------|-----------------|-----------------|----------------------|
     | 1 | 0.02 | `V_disp_nu1` | 9.87 | shallowest |
     | 2 | 0.029 | `V_disp_nu2` | 6.80 | middle |
     | 3 | 0.06 | `V_disp_nu3` | 3.29 | steepest |

  4. State what each *flavour* (e/μ/τ) corresponds to as a **combination/dominance** of these three configs (flavour ≠ single mass minimum — the measured mixing means flavour is a *blend* of configs; describe the blend geometrically, NOT as a wavefunction).
- **Pre-committed success metric:** A *single, named, dimensioned* internal DoF is defined; all three configs map to the three engine minima with no new constants; the e/μ/τ→config relationship is stated geometrically.
- **Failure trigger / PIVOT:** If FLM11 grants the straight vortex **zero** free internal DoF → the beat is geometrically forbidden → **OPEN** immediately (do not invent a DoF). If the only DoF available *requires* ΔW → that is a different particle, not oscillation → **KILL** the naive picture and park.
- **Out of scope (P1):** any numeric beat length; any wavefunction language; any claim that the blend *is* a superposition.

### Phase 2 — Native beat/relay mechanism (no wavefunction) — **GATE**

- **Goal:** Propose, with symbols and dimensions, the **mechanism** by which the internal pitch **periodically cycles** between the three configs as the vortex relays — using only relay cadence + resistance differences, **no superposition ket**.
- **Method:**
  1. Write the relay-cadence picture: the vortex advances one relay step per lattice cell; its internal pitch precesses by an increment set by the **resistance (length) difference** `ΔR_resist,ij` between configs `i,j`.
  2. Define the **phase accumulated per unit length**: `dφ_ij/dx ∝ (resistance/length difference)_ij / (budget term)`. Show dimensionally that this yields an inverse length (a spatial frequency). State the constant of proportionality and its provenance (must trace to whitelist, not be fitted).
  3. Identify the **beat condition**: flavour returns when accumulated phase = 2π; the beat **length** is `L_osc,ij = 2π / (dφ_ij/dx)`.
  4. Explicitly contrast with the prohibited route: a one-paragraph statement of *why this is a geometric beat of one object, not two eigenstates interfering in a wavefunction* (the translation-test: NATIVE vs LINGUISTIC-BORROW).
- **Pre-committed success metric:** `dφ/dx` is dimensionally `[1/length]`; the proportionality constant is sourced from `{ℏ,c,...}` or the engine's V_disp minima — **zero fitted knobs**; the no-wavefunction contrast is explicit.
- **Failure trigger / PIVOT:** If the only way to get a finite `dφ/dx` is to insert a free coefficient → **PIVOT** to an alternative native driver listed in §⑩ (lattice-cadence mismatch length; wake-radius difference `ΔR_wake,ij`); if *all* native drivers need a knob → **OPEN**.
- **Out of scope (P2):** comparison to measured numbers (that is P3); mixing-angle derivation (degenerate stretch goal only).

### Phase 3 — The decisive quantitative test (beat length vs measured scale) — **GATE**

- **Goal:** Derive `L_osc` **from the three mass minima as resistances/lengths** and compare to the **measured** solar (`Δm²₂₁`-scale) and atmospheric (`Δm²₃₂`-scale) oscillation lengths.
- **Method:**
  1. Build the tool `ppt11_oscillation_length.cpp` (or `.py`). Inputs: `neutrino::measured::m_nu1/2/3`, `V_disp_nu*`, `R_wake_nu*` — **the three minima**, tagged `MEASURED-INPUT`. **Do NOT** read `Dm21_sq`/`Dm32_sq` to *construct* `L_osc` (that would be IDENTITY-PASS); they appear **only** in the OBSERVED-TARGET comparison column.
  2. From P2's mechanism, compute the **effective splitting** implied by the three minima and the resulting `L_osc(E_ν)` for a reference `E_ν` (e.g. 1 MeV solar, 1 GeV atmospheric).
  3. Compare to the measured oscillation length `L_meas = 2.48·E[MeV]/Δm²[eV²]` (OBSERVED-TARGET) at the same `E_ν`.
- **Pre-committed success bar (the floor for even a Class D foothold):**
  > **Order-of-magnitude agreement with at least one measured Δ(scale)** — i.e. `|log₁₀(L_osc,SDT / L_meas)| ≤ 1` for **either** the solar **or** the atmospheric splitting — **using the engine's mass minima with no fitted knob.**
- **Failure trigger:**
  - `|log₁₀ ratio| ≤ 1` for ≥1 scale, no knob → **Class D foothold** (PASS-GATE at D level; record honestly, not as closure).
  - `1 < |log₁₀ ratio| ≤ 3` → **PIVOT** to alternative native driver (§⑩); if still off → **OPEN**.
  - `|log₁₀ ratio| > 3` and no geometric reason recovers it → **KILL** the naive beat model and park as `[OPEN]`.
- **Out of scope (P3):** fitting any coefficient to close the gap; widening the ±1-decade bar after seeing the number (forbidden retro-PASS).

### Phase 4 — Recursive honest failure analysis (to root) — **GATE (always runs)**

- **Goal:** Per Harvey's standing recursive-investigation instruction, drive each outcome to a **root cause**, not a one-line verdict.
- **Method (recursion template):**
  - **If FAIL → why?** (e.g. beat length 6 decades short.) → **why is it short?** (resistance difference too small / wrong budget term / wrong cadence). → **why that?** … recurse until the failure bottoms out in a *named geometric/whitelist fact* (e.g. "V_disp minima differ by only ~3×, the measured `Δm²` needs a 30× lever we have not located").
  - **If SUCCEED → find cause^n:** do not stop at "it matched." → **why did it match?** → is the lever a genuine geometric quantity or a coincidence of the chosen `E_ν`? → recurse until the *source* of the agreement is a named SDT mechanism (else label DEGENERATE/coincidence).
- **Pre-committed success metric:** every P3 branch terminates at a root cause expressed in whitelist/geometry terms; no branch ends at "unclear."
- **Out of scope:** rescuing a KILL with a fit; relabelling OPEN as PASS.

---

## ⑤ Success Criteria (dual verdict — canonical labels)

> Two axes, both mandatory in `PPT11_VERDICT.md` (per `PROMPT_EXECUTION_PROTOCOL.md` §4).

**Prompt completion (A–F):** did the tool execute §④ P1–P4 and emit §⑥ files?

**Physics class (the honest read — closure is NOT expected):**

- **Class A (DERIVED) — not expected:** native beat mechanism *and* `L_osc` from the three minima matching **both** measured scales to ≤ ±1 decade, no knob, root cause named.
- **Class C (CONVERGENCE):** native mechanism + order-of-magnitude match to **one** scale, with one clearly-flagged approximation. Publishable as "SDT-native geometric beat reproduces the [solar|atmospheric] oscillation scale to within a decade."
- **Class D (COMPUTED foothold) — the realistic best case:** mechanism is geometrically licensed (FLM11 grants the DoF) and the beat length is **traced** to the three minima, landing within ~1 decade of one scale, physical interpretation incomplete. Ship as a **foothold**, not a closure.
- **OPEN (most likely honest outcome):** no non-wavefunction mechanism produces periodicity, **or** the mechanism exists but the length is many decades off with no geometric recovery → **record the sharpened open problem**; do **NOT** fabricate a mechanism or a number.
- **KILLED:** the naive near-degenerate-beat model is quantitatively excluded (>3 decades off, no recovery) → park it, state precisely what would need to be true instead.

**A failure NEVER becomes a retro-PASS.** `[OPEN]` carried honestly is the success condition for this Tier-5 spec.

---

## ⑥ Outputs (exact filenames — rename ⇒ ADJ entry)

1. **`PPT11_DERIVATION.md`** — symbolic chain: the internal DoF (P1), the beat mechanism with dimensions (P2), the beat-length formula (P3); every line tagged `DERIVED` / `ASSUMED` / `MEASURED-INPUT`.
2. **`ppt11_oscillation_length.cpp`** *(or `.py`)* — standalone tool; `#include <sdt/laws.hpp>` (and `neutrino.hpp`) only, no local constant namespace; derives `L_osc` from the **three mass minima**, prints comparison table vs measured solar/atmospheric `L_meas` with the parameter ledger (§5 tags). The `Dm²` block appears in the **OBSERVED-TARGET column only**, never as construction input.
3. **`ppt11_results.txt`** — stdout capture: `[config | m_νi | V_disp | R_wake | implied Δ | L_osc,SDT | L_meas | log₁₀ ratio | label]`.
4. **`PPT11_VERDICT.md`** — dual verdict header; falsification table updated; **carry the `[OPEN]` honestly** if reached; root-cause tree from P4.
5. **`RUN_LOG.md`** — Pre-Run Commitment Block first; ADJ-### entries for every pivot; phase gates. **Mandatory.**

---

## ⑦ Dependencies & References

**Upstream (read first):**
- **PPT10 — Straight-Light Neutrino:** *grounds this spec* — the straight-thread, propagate-with-relay picture that creates the debt.
- **PPT04 — Neutrino Magnetic Moment (μ_ν=0):** establishes W=0, no ℓ=2 wake, the non-occluding wake structure.
- **`Engine/include/sdt/neutrino.hpp`:** the three mass minima, V_disp, wake radii, and the existing "pitch precession" oscillation narrative + `L_osc` form (treat its `Dm²` as MEASURED-INPUT, not derivation).
- **FLM11 — Tape-Measure / degrees-of-freedom census:** supplies the DoF count that *licenses or forbids* the internal pitch beat (P1 gate hinge).

**Related (parallel set of 9):** NP18 (resonator — tests *conversion*, **cannot** rescue flavour), NP19/NP20 (neutron), NP21 (landscape), APS06 (emission-ladder), SAR05 (provenance).

**Downstream (this unblocks):** completes — **or honestly fails to complete** — the SDT neutrino account. A clean `[OPEN]` here is itself a deliverable: it tells PPT10 exactly which hole remains.

---

## ⑧ Falsification Tests (numeric triggers)

| # | Test | Predicted (SDT) | If FAIL → action |
|---|------|-----------------|------------------|
| T1 | Straight W=0 vortex possesses ≥1 free internal angular DoF (FLM11) | DoF count ≥ 1 | **OPEN** — beat geometrically forbidden; the straight-light picture has an **unfilled hole**. Do **not** invent a DoF. |
| T2 | Flavour change requires **no** ΔW | W stays 0 across e/μ/τ | If oscillation needs ΔW → **KILL** naive picture (that's a different particle, not oscillation). |
| T3 | Native (non-wavefunction) mechanism yields a finite `dφ/dx` `[1/length]` with **no fitted knob** | yes | If only a fitted coefficient gives finite `dφ/dx` → **PIVOT** (alt driver §⑩); if all need a knob → **OPEN**. |
| T4 | Beat length from the **three minima** lands within ±1 decade of ≥1 measured scale, no knob | `\|log₁₀(L_SDT/L_meas)\| ≤ 1` | 1–3 decades → **PIVOT**; >3 decades, no geometric recovery → **KILL** naive beat, park `[OPEN]`. |
| T5 | Agreement (if any) is a genuine geometric lever, not a coincidence of chosen `E_ν` | robust across `E_ν` | If match vanishes when `E_ν` changes → **DEGENERATE/coincidence**, not Class C. |

**Recovery doctrine:** every FAIL routes through §⑩ pivots to either an alternative **native** driver or an honest `[OPEN]`/`KILL`. Fabrication of a mechanism or a number is an instant audit fail.

---

## ⑨ Implementation Notes

- **Double precision throughout.** Lengths span μm wake radii to oscillation lengths of km–10³ km; mass minima differ by only ~3×. Work in **dimensionless ratios** (`L_SDT/L_meas`, `V_disp,i/V_disp,1`) to avoid scale loss.
- **Provenance discipline (the trap):** the engine's `Dm21_sq`, `Dm32_sq` are **MEASURED-INPUT**. Reading them to *build* `L_osc` and then "matching" `L_meas` is **IDENTITY-PASS** and an instant fail. Construct the splitting **only** from the independently-listed `m_nu1/2/3` (and/or `V_disp`, `R_wake`); the measured `Δm²` enters **only** the OBSERVED comparison column.
- **Translation test in code comments:** label the mechanism block NATIVE and write one line distinguishing it from a superposition of eigenstates — if you cannot, the result is **LINGUISTIC-BORROW**, not NATIVE.
- **Plot hints (optional):** (1) `L_osc,SDT` vs `E_ν` overlaid on `L_meas` for solar and atmospheric scales — check the curves are *parallel* (same `E_ν` dependence) before judging the offset; (2) internal pitch `θ_pitch(x)` along flight — should show three-level cyclic beating, not a smooth ramp.
- **Sanity gate before P3 number:** confirm the tool reproduces the engine's wake radii (9.87 / 6.80 / 3.29 μm) and V_disp from `m_nu*` — if those don't round-trip, the inputs are wired wrong.

---

## ⑩ Adaptive Execution Protocol (MANDATORY)

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS, PLUG, IDENTITY-PASS, or BORROW-SMUGGLE. See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PPT11
- Prompt completion target: [A|B|C|D]
- Physics class hoped (HONEST): [most likely OPEN or Class D — closure NOT expected]
- CALIBRATED budget: 0   (this spec permits ZERO fitted knobs; a knob = automatic non-PASS)
- Engine namespaces: sdt::neutrino (m_nu1/2/3, V_disp_nu*, R_wake_nu*, W_neutrino), law_IV, law_V, law_VI
- Decisive bar (P3): |log10(L_osc_SDT / L_meas)| <= 1 for >=1 measured scale, NO fitted knob
- Forbidden construction input: Dm21_sq / Dm32_sq used to BUILD L_osc (OBSERVED column only)
- Phase thresholds: P1 DoF>=1 named; P2 dphi/dx dimensionally [1/length], 0 knobs; P3 bar above; P4 root cause named
- Forbidden retroactive changes: widen the ±1-decade bar; plug a lever coefficient; IDENTITY-PASS on Dm²;
  call a superposition a "geometric beat"; relabel OPEN/KILL as PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden response |
|-------------------|------------------------|----------------|--------------------|
| **P1:** FLM11 grants 0 internal DoF to straight W=0 vortex | Re-examine FLM11 census for a *length/pitch* DoF distinct from winding | **OPEN** — record unfilled hole in straight-light picture | Invent a DoF to keep the model alive |
| **P1:** flavour change seems to need ΔW | Check if it's pitch-level not winding-level | **KILL** naive picture; park (different particle) | Call a ΔW transition "oscillation" |
| **P2:** finite `dφ/dx` only with a fitted coefficient | Switch native driver: lattice-cadence mismatch length → wake-radius difference `ΔR_wake,ij` → V_disp-minima spacing | **OPEN** mechanism; no Class ≥ D | PLUG a coefficient to make `dφ/dx` finite |
| **P3:** `1 < \|log₁₀ ratio\| ≤ 3` | Try alternative native lever from P2's list; document ADJ-### | **OPEN** the lever | Widen the ±1-decade bar post-run (RETRO-PASS) |
| **P3:** `\|log₁₀ ratio\| > 3`, no geometric recovery | — | **KILL** naive beat; park `[OPEN]`, state required lever | Fit to close 3+ decades |
| **P3:** match achieved by reading `Δm²` from engine | Reject — rebuild from `m_nu*`/`V_disp` only | If can't rebuild → **OPEN** | IDENTITY-PASS on a measured input |
| **T5:** match vanishes when `E_ν` changes | Label **DEGENERATE/coincidence** | — | Claim Class C on a coincidence |

### Allowed adjustments
- Finer reference-energy sweep; alternative **native** beat driver (cadence-mismatch length / `ΔR_wake` / `ΔV_disp` spacing) already named above; phase split (3a analytic, 3b numeric); filename fix via ADJ entry.

### Disallowed adjustments
- Post-hoc widening of the ±1-decade bar · any fitted lever coefficient · using `Δm²` as construction input · superposition-wavefunction smuggled in as "beat" · `G/M/GM/G_F/ψ/ΛCDM` in the chain · local constant namespaces · relabelling OPEN/KILL as PASS.

### Dual verdict reminder
`PPT11_VERDICT.md` header must carry **both** axes: **Prompt completion (A–F)** and **Physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN)**. For this Tier-5 spec, a **sharpened, honestly-recorded `[OPEN]`** is a complete and acceptable result — a fabricated closure is not.

---

*PPT11 · the price of admission · the straight thread must earn its three flavours or name the hole it cannot fill.*
