# GOM03: Lunar Orbital Kinematics from Pendulum Acceleration — the self-test named as a self-test, and the real-data road

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC — **full upgrade 2026-07-24** (supersedes
> 2026-06-27; Golden-Rule Q1 was unfilled and the validation design was circular-by-construction
> without saying so — fixed below). **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` ·
> `PROMPT_EXECUTION_PROTOCOL.md` · HUNTER §0/§G. **Engine:** `#include <sdt/laws.hpp>` only.
> **Execution: DIRECT ONLY — no agents.** Prior agent-era VERDICT/RUN_LOG/results deleted
> 2026-07-24 (git-recoverable). §⑩ commitments to `RUN_LOG.md` before code.

---

## ⓪ The Golden Rule — five questions

1. **What don't we know?** — Two things the old spec conflated:
   (a) whether the koppa-only inversion pipeline (a(t) → lunar d, e, i, T with no G/M anywhere)
   is *algorithmically sound* — a code property, testable on synthetic data; and
   (b) whether it works on **measured** acceleration data — the only version that carries physics
   content, and the version that has never been run. The old spec's "validation" synthesized
   a(t) FROM the lunar ephemeris and then recovered the ephemeris — a round trip through our own
   generator. That is the GD05-v1 circularity shape (the mock that validated itself), and it is
   permitted here ONLY under its honest name: **PIPELINE SELF-TEST, zero physics weight.**
2. **Why does it matter?** — The claim "lunar orbital elements recovered from a ground
   accelerometer with no mass-based model" is the k-hierarchy thesis (GOM02) made tabletop: the
   ϟ-ledger runs the whole chain instrument → orbit. It is also the honest gateway to the tidal
   sector (GOM11/E99) where a calibration taint (Q = 2.31) is already on record — this pipeline,
   on real data, is the clean way back into that territory.
3. **How will we find out?** — §④: P1 self-test (labeled), P2 sensitivity budget (what precision
   of real instrument the inversion actually needs), P3 real-data run on public superconducting-
   gravimeter records (IGETS/GGP — fetch row to be added to MUST_FETCH as F11 when P3 opens).
4. **What would prove us wrong?** — §⑧: inversion fails its own synthetic round-trip (code
   broken); sensitivity budget shows real instruments cannot reach the M2/N2 separation
   (pipeline physically impossible as posed — record and close); real-data recovery misses the
   LLR-known elements by more than the instrument budget (the koppa tidal form fails on data —
   that would be a genuine SDT failure since the 1/d³ gradient is shared with Newton, so a miss
   here indicts the pipeline's koppa normalisation ϟ_Moon specifically).
5. **How will we know we're done?** — Dual verdict; the self-test and the real-data claim
   reported in SEPARATE sections that can never be quoted as one number.

## §0 Reader's contract

1. **The circularity rule.** Synthetic-in/synthetic-out proves code, never physics. Every P1
   output line carries `[SELF-TEST — no physics weight]`. The GD05 mock precedent is cited in
   the verdict whenever P1 is mentioned.
2. **Shared-form honesty.** The tidal signature a_tidal = 2ϟ_Moon·R⊕·cosθ_z/d³ has the same
   1/d³ form as Newton's (both are the gradient of a 1/r² field across Earth's extent). On
   synthetic or real data alike, matching the FORM is CONVERGENCE. What is native is the
   NORMALISATION: ϟ_Moon = v²R/c² = 5.46×10⁻⁵ m enters from lunar kinematics with no mass — a
   real-data amplitude match at that normalisation is the earned content.
3. **No G, no M** anywhere in the chain; `bridge::GM_equivalent` only in rival columns.
4. **Tidal-sector hygiene.** No harmonic constant may be CALIBRATED silently (the E99/Q = 2.31
   lesson). If the real-data phase needs an elasticity/loading correction (solid-Earth Love
   numbers), it enters as OBSERVED-ANCHOR with citation, labeled, or the affected component is
   dropped — never absorbed.
5. **Direct execution only; teed stdout; fresh dated verdict.**

## §1 Definitions and anchors

| Quantity | Value | Label |
|---|---|---|
| ϟ_Moon | 5.46×10⁻⁵ m (= v_Moon²R_Moon/c²) | COMPUTED (kinematics) |
| a_tidal peak (M2, equator) | ~1.1×10⁻⁶ m/s² (lunar) | derived in P0, compared to standard tidal value as CONVERGENCE check |
| M2 / O1 / N2 periods | 12.421 h / 25.819 h / 12.658 h | OBSERVED-ANCHOR (astronomical) |
| Lunar elements (comparison ONLY, sealed until P3 recovery is logged) | d̄ = 384,400 km · e = 0.0549 · T_sid = 27.321661 d | OBSERVED-ANCHOR (LLR/ephemeris) |
| Instrument floors | pendulum ~10⁻⁹; superconducting gravimeter ~10⁻¹¹–10⁻¹² m/s²/√Hz | OBSERVED-ANCHOR |

## §④ Phases

**P0 — Sanity.** ϟ_Moon from kinematics; peak tidal amplitude from the koppa form vs the
standard tidal amplitude (must agree — shared form; label CONVERGENCE); engine symbols.

**P1 — Pipeline self-test (code property only).** The existing tool (`gom03_lunar_pendulum.cpp`)
synthesizes a year of a(t) at stated latitude + noise 10⁻⁹ m/s², inverts, recovers elements.
Pre-registered gates (unchanged from the old spec, now honestly labeled):
d̄ within 0.1% · e within 5% · T within 0.01% · zero G/M in the chain (grep the tool — the gate
includes a source audit). **Every line: `[SELF-TEST]`.** Passing means: the inversion algebra is
sound and the noise floor 10⁻⁹ suffices IN SIMULATION.

**P2 — Sensitivity budget (the bridge to reality).** From the P1 machinery: inject the REAL
disturbance inventory at realistic amplitudes — solar tide (~46% of lunar), atmospheric loading,
ocean loading at coastal vs continental sites, instrument drift — and determine: (a) minimum
record length and (b) instrument class needed to separate M2/N2 (the eccentricity channel) and
O1 (the inclination channel) at the P1 gate precisions. Output: a feasibility table
[element | needed floor | needed duration | feasible instrument]. Pre-commit: if the budget says
the pendulum-class floor (10⁻⁹) cannot recover e at 5% in ≤2 years of record, say so — the old
spec's implicit "a pendulum suffices" claim dies there, and the pipeline re-targets
superconducting gravimeters.

**P3 — Real data (the physics phase; opens only after P2 fixes the instrument class).**
Fetch: public superconducting-gravimeter minute-series (IGETS station, ≥1 year, continental
site per P2) — add as MUST_FETCH F11 with provenance protocol (bytes, sha, station, span)
BEFORE download. Pre-commit the pass/fail: recovered d̄, e, T within the P2-budgeted envelopes
of the LLR values, with ϟ_Moon's kinematic normalisation carrying the amplitude (contract §2).
Love-number corrections, if unavoidable, enter labeled (contract §4). Recovery here — real
instrument, no G, no M, koppa normalisation landing the amplitude — is the investigation's
actual result. A FORM match with amplitude off is a partial: form CONVERGENCE, normalisation
FAILED, both stated.

## §⑧ Falsifiers

| # | trigger | consequence |
|---|---|---|
| F1 | P1 round-trip misses its gates | inversion code broken — fix before anything else; no physics statement |
| F2 | P2 budget: no realistic instrument/duration reaches the gates | pipeline infeasible as posed — record, close honestly (this is a finding) |
| F3 | P3 amplitude off beyond budget with form intact | ϟ_Moon normalisation fails on data — genuine SDT miss; escalate root-2 (lunar v,R inputs) then root-1 |
| F4 | any G/M found in the chain by the P1 source audit | run VOID until removed |
| F5 | a harmonic constant absorbed uncited | E99 repeat — run VOID (contract §4) |

## §⑨.E Four-root sort
root-1 claim false (koppa normalisation) · root-2 dependency (lunar kinematic inputs; instrument
metadata) · root-3 spec (site/loading model under-specified) · root-4 gate contraband.

## §⑤ Outputs
Fresh `RUN_LOG.md` · re-audited `gom03_lunar_pendulum.cpp` (+ P2 extension; P3 driver when
opened) · `gom03_rerun_<date>.txt` · `GOM03_VERDICT_DIRECT_<date>.md` (self-test and real-data
sections SEPARATE) · MUST_FETCH F11 row when P3 opens.

## §6 Dependencies
Upstream: laws.hpp bridge:: · GOM02 (the ϟ-ledger thesis this instantiates). Sibling: GOM11/E99
(tidal sector; the calibration-taint precedent), E26 (LLR — comparison anchors). Downstream:
E99 recovery (a clean, labeled tidal pipeline is its prerequisite).

---

## ⑩ Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — GOM03 (2026-07-24 spec)
- Prompt completion target: [A|B|C]
- Physics class: P1 = code self-test (no class); P3 ceiling = CONVERGENCE on form +
  NATIVE-normalisation on amplitude
- CALIBRATED budget: 0 (Love numbers OBSERVED-ANCHOR if unavoidable, labeled)
- Gates: P1 0.1%/5%/0.01% + source audit · P2 feasibility table complete · P3 within P2 envelopes
- Forbidden: quoting P1 as physics; silent harmonic calibration; G/M; agents.
```

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 gate miss | debug inversion (this is code) | STOP — no physics claims | relabeling a miss |
| P2 shows pendulum infeasible | re-target gravimeter class, ADJ-log | F2 close-out | pretending 1e-9 suffices |
| P3 data gaps/spikes | documented gap-fill rule fixed BEFORE inspection | drop the affected component | post-hoc data pruning |

---

*GOM03 · upgraded 2026-07-24 · a round trip through your own generator is a mirror, not a window;
name it, budget the window, then open it.*
