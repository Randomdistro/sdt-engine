# PPT11 — RUN LOG (append-only)

> **Run:** 2026-07-01 · Executor: agent (Opus 4.8) executing the SPEC at `PROMPT.md`.
> **Engine read first:** `Engine/include/sdt/laws.hpp` (measured, law_IV, law_V, law_VI), `Engine/include/sdt/neutrino.hpp`.
> **Upstream read:** PPT10 PROMPT, PPT04 VERDICT, FLM11 PROMPT (DoF census spec), FLM12_D1_VERDICT (the just-run UNPAID companion — same honesty bar).

---

## Pre-Run Commitments — PPT11  (written BEFORE coding)

- **Prompt completion target:** A (execute P1–P4 + emit §6 files). Honest physics-class expectation: **OPEN or Class D**, closure NOT expected.
- **Physics class hoped (HONEST):** most likely **OPEN**; best realistic case **Class D foothold** (length traced to the three minima, mechanism geometrically licensed but interpretation incomplete).
- **CALIBRATED budget: 0.** Zero fitted knobs. A knob = automatic non-PASS.
- **Engine namespaces:** `sdt::neutrino` (`measured::m_nu1/2/3_eV`, `V_disp_nu*`, `R_wake_nu*`, `W_neutrino`, `wake_radius`), `sdt::laws::law_IV` (V_disp↔mass), `law_V` (movement budget), `law_VI::winding` (W spectrum).
- **Decisive bar (P3):** `|log10(L_osc_SDT / L_meas)| <= 1` for **>=1** measured scale, **NO fitted knob**.
- **Forbidden construction input:** `Dm21_sq` / `Dm32_sq` used to BUILD `L_osc`. They appear in the **OBSERVED-TARGET column only**. The engine-implied splitting is built ONLY from `m_nu1/2/3` as `Δm²_ij = m_j² − m_i²`.
- **Phase thresholds:**
  - **P1** — a single named dimensioned internal DoF; all 3 configs → 3 engine minima with no new constants; e/μ/τ→config stated geometrically. GATE HINGE: FLM11 must grant the straight W=0 vortex ≥1 free internal angular DoF, else OPEN.
  - **P2** — `dφ/dx` dimensionally `[1/length]`; proportionality constant from `{ℏ,c,...}` or engine V_disp minima; **0 fitted knobs**; explicit no-wavefunction contrast (translation test).
  - **P3** — bar above; sanity gate: tool round-trips wake radii 9.87/6.80/3.29 µm from m_nu*.
  - **P4** — every P3 branch bottoms out at a named geometric/derivation basis root cause; no branch ends "unclear."
- **Forbidden retroactive changes:** widen the ±1-decade bar; plug a lever coefficient; IDENTITY-PASS on Δm²; call a superposition a "geometric beat"; relabel OPEN/KILL as PASS; local constant namespaces.

---

## Pre-commit predictions (written BEFORE running the tool, from analytic recon)

- **PRE-COMMIT-1 (P1 DoF hinge):** I read FLM11's PROMPT (the spec, not a completed run). FLM11 *proposes* the straight/through axis Π_∥ as a DoF of the form but explicitly says it is the **zero-grip residue with NO native ruler**. This is a double-edged licence: it grants that the straight axis EXISTS as a configuration axis, but it is defined by *not gripping* — i.e. it has no internal circulation to precess. **PRE-COMMITTED RISK:** the pitch-precession beat may be geometrically FORBIDDEN because the very thing that makes the neutrino un-measurable (zero grip, no circulation) is also what a beat needs to precess against. Flag this as the P1 gate outcome to test, not assume.
- **PRE-COMMIT-2 (P3 number, hoped band):** I have NOT yet coded, but analytic recon on the three minima gives Δm²_32(engine)=m3²−m2² ≈ 2.76e-3 eV² vs measured 2.453e-3 (log10 ratio +0.05) and Δm²_21(engine)=m2²−m1² ≈ 4.41e-4 vs measured 7.53e-5 (log10 +0.77). **Both are within the ±1-decade bar.** So the *number* will pass the P3 floor. The decisive honesty question moves from "does the length match?" (it does) to "is the mechanism SDT-native or is the phase a smuggled quantum phase, and are the masses independent of Δm²?" — that is where the OPEN likely lives.
- **PRE-COMMIT-3 (independence audit):** the engine masses m2=0.029, m3=0.06 are literature "normal-ordering best estimates" which in the wider literature ARE informed by Δm² measurements. So provenance is **MIXED**: m1=0.02 is the SDT mass-gap (independent), m2/m3 carry rounded literature info partly derived from Δm². This is a **partial-circularity** flag that MUST cap the grade — it is not a clean identity-pass (the masses do not round-trip to the naive back-solve 0.0218/0.0541), but it is not a clean independent derivation either.

---

## Phase gates (filled during run)

### P1 gate — define the 3 flavours as 3 configs (DoF hinge)
- **Outcome:** AMBIGUOUS → **partial-DEFER/OPEN** (not a clean PASS). ΔW=0 across flavours holds (T2 PASS). The pitch-angle DoF is *asserted by the engine* (`neutrino.hpp:5–8,130`) but *not licensed by FLM11's census*: FLM11 defines the neutrino's straight axis as the **zero-grip / zero-circulation residue** — a beat needs an internal circulation to precess, which that definition removes. Recorded as the load-bearing tension.
- **Gate decision:** proceed to P2/P3 to test the *number* while carrying the DoF licence as an unpaid debt (protocol permits: ship partial, no PASS on parent claim). No DoF invented.

### P2 gate — native beat mechanism (no wavefunction)
- **Dimensional metric:** PASS — `dφ/dx = Δm² c³/(4ℏE)` is `[1/length]`, no fitted knob.
- **Translation test:** **FAIL-as-NATIVE.** The `1/(4ℏE)` factor is the standard mass-eigenstate oscillation phase, **imported**, not derived from SDT relay cadence. Re-narrating it as a "geometric beat" is LINGUISTIC-BORROW, so the mechanism is labelled `[OPEN]`/`PENDING`. Not fished; stated plainly.
- **Gate decision:** proceed to P3 with the phase factor flagged as the mechanism hole.

### P3 gate — decisive number (beat length vs measured)
- **Sanity gate:** PASS (wake radii 9.87/6.80/3.29 µm round-trip from masses to <1%).
- **Construction:** splitting built ONLY from `m_j²−m_i²`; measured Δm² in OBSERVED column only. No hard IDENTITY-PASS.
- **Result:** BOTH scales within ±1 decade, **0 knobs** — atmos. log₁₀ −0.05 (12%), solar log₁₀ −0.77. **P3 FLOOR MET.**
- **T5:** log₁₀ ratio exactly E-independent → not an E-coincidence (not DEGENERATE).
- **Independence audit:** engine masses do NOT round-trip to naive Δm² back-solve (0.0218/0.0541) → not a hard identity-pass; BUT m₂,m₃ are literature best estimates partly informed by Δm² → **partial circularity**, caps grade below C.
- **Gate decision:** numerical **Class-D foothold** recorded — NOT relabelled a closure.

### P4 gate — recursive root cause (always runs)
- Two named roots, no branch ends "unclear": **(i)** partial circularity in the mass inputs; **(ii)** the beat clock is geometrically absent because the neutrino is defined by zero circulation (straight-thread ⊥ flavour-beat structural tension). See `PPT11_VERDICT.md` root-cause tree.

## Decision (protocol §2 vocabulary)
- **P1: OPEN** (DoF not cleanly licensed) · **P2: OPEN** (imported phase) · **P3: PASS-GATE at Class-D on the length only** · **P4: complete.**
- **Overall physics class: OPEN (sharpened)** with a Class-D numerical foothold. **Prompt completion: A.**
- No ADJ-### pivots were needed: the plan ran as written; the honest outcome is the pre-committed most-likely one (OPEN). No RETRO-PASS, PLUG, IDENTITY-PASS, or BORROW-SMUGGLE performed. Pre-committed ±1-decade bar unchanged post-run.

## Files emitted (§6)
- `RUN_LOG.md` (this) · `ppt11_oscillation_length.py` · `ppt11_results.txt` · `PPT11_DERIVATION.md` · `PPT11_VERDICT.md`.
