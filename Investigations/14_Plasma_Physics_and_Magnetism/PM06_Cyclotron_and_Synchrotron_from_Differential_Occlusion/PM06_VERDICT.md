# PM06 — Verdict: Cyclotron and Synchrotron from Differential Occlusion

**Author:** J. C. Harvey, Melbourne · **Date:** 2026-07-05
**Tool:** `pm06_cyclotron.cpp` (MSVC, real run, exit 0) → `pm06_results.txt`
**Pre-commitments:** `RUN_LOG.md` (incl. three anti-identity-pass guards, all honoured).

---

## 1. Deciding metrics

| Phase | Gate | Result | Class |
|---|---|---|---|
| P1 | orbit closes at ω_c | closure drift 8.6e-15/period; ω = Ω exact; relativistic ω_rel = Ω/γ and r = γv/Ω to 1e-6 (γ = 2, 10) | **NATIVE-form**: ω_c = \|∇×w\| with **unit gain** from the field-proportional entrainment channel |
| P1 sense | orbit sense from EMC03 | **NOT claimed** — the proportional channel is unsigned (PM01: 2/4); the signed channel is field-blind. HG-1 | **OPEN** (inherited) |
| P2 | a′/a = γ² from arrays | 4.0000 / 100.0000 measured by finite differences on the RK4 arrays (dev < 1e-3%); power ledger ⇒ exponent 4.000 | Law-V kinematics NATIVE; **rest-frame coefficient BORROWED** (E89/PM03 — PM03 is DO-NOT-TRUST, so only scalings claimed) |
| P3 | ω_crit ∝ γ³ω_rot | pulse train from orbit + Law-V aberration pattern + arrival-time compression: slope **3.019** over γ = 4–32 (gate 3.0±0.15) | NATIVE-within-SDT (all kinematic), DEGENERATE with SR |
| P4 | beaming 1/γ | Monte-Carlo isotropic rest emitter through Law-V aberration: θ_med·γ = 1.0038 (γ=8), 1.0013 (γ=32) | NATIVE-within-SDT, DEGENERATE with SR |

**Earned:** the entire γ-anatomy of synchrotron radiation (ω_rel = Ω/γ, a′ = γ²a ⇒ P ∝ γ⁴,
ω_crit ∝ γ³ω_rot, cone = 1/γ) is **one Law-V movement-budget statement** unfolded four ways — no
Lorentz transform was imported; the aberration/dilation used are Law-V theorems (T10–T17). Since
Law V ≡ SR kinematics, every one of these is simultaneously DEGENERATE with the SR derivation:
SDT reproduces, and does not yet exceed, the standard anatomy. Stated plainly per §B.

**Not earned:** (i) the orbit's *sense* from carrier handedness and the ω_c = qB/m gain — both are
the HG-1 bilinear wall (PM01); ω_c carries unit gain natively, the SI map is the final line only.
(ii) The absolute radiated power — the rest-frame emission coefficient is borrowed until a real
PM03 relay-pulse solver exists (named missing tool: honest PM03 re-run / lattice wave solver).
(iii) The synchrotron spectral *shape* (only the RMS-width scaling was measured).

## 2. §D seven questions (on the two OPEN items)

1. **Why open?** Sense/gain: unsigned-vs-field-blind channel split, measured in PM01 (2/4 + 2/4).
   Coefficient: no trusted native emission channel (PM03 superseded).
2. **Recoverable?** Sense/gain: iff HG-1 closes. Coefficient: yes — re-run PM03 honestly (evolving
   wave arrays), then E89 ledger fixes C.
3. **Failed to account for:** prompt assumed PM03's channel was usable; it is flagged DO-NOT-TRUST.
4. **Errored premise:** "PM01's Lorentz-occlusion is available as a signed, field-proportional
   push." Only its unsigned half is.
5. **Freedom:** HG-1 coefficient; PM03 solver.
6. **Accounting:** HG-1 native candidates named in PM01 (PPT06 ℓ=2 gearing; FLM14 rotation DOF).
7. **Cascade?** YES — HG-1 (sense/gain); PM03-rebuild (coefficient; also gates PM07's wave sector).

**§G-3:** both OPENs carry premise class (linear one-channel coupling; absent wave solver) and
re-open conditions (HG-1 closure; honest PM03). Neither is "underivable."

## 3. Generative questions logged

- Gyro-radius as koppa-closure (prompt Q1): r = γv/Ω verified; the koppa analogy (ϟ = v²R/c²)
  maps if Ω is read as a local depth gradient — untested, logged.
- PM04 handshake (prompt Q4): PM04's upper-hybrid used this same unit-gain ω_c = Ω — consistent.

## 4. Verdict

> **Prompt completion C** · **Physics class** NATIVE-form (orbit, γ-anatomy — all DEGENERATE with
> SR via Law V, disclosed) / BORROW (rest-frame emission coefficient, flagged) / OPEN (sense + SI
> gain = HG-1; absolute power = PM03 rebuild) · **Recovery** PARTIAL (both routes named, neither
> paid) · **Cascade roots** HG-1; PM03-rebuild.
