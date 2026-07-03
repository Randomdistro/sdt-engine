# OP05 — Photoelectric and Compton as Emission↔Vortex Exchange

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Whether the photoelectric line `KE_max = hf − W` and the Compton shift
   `Δλ = λ_C(1−cosθ)` — the textbook "proofs of the photon" — can be *derived* as emission↔vortex
   exchange (a relay impulse absorbed into, or recoiling off, a bound electron-vortex with lattice
   momentum bookkeeping), **with no point quantum of light anywhere in the chain**, or whether SDT
   must reintroduce a localized photon-particle to get the threshold and the recoil.
2. **Why does it matter?** — These two experiments are the historical case for photon-as-particle and
   wave-particle duality. If "quantum of light" becomes "threshold + recoil facts about how a relay
   emission couples to a vortex," the photon-particle drops out of the ontology and OP06's stimulated
   emission becomes the reverse of this same exchange. If it cannot, the relay picture of light fails
   exactly where Einstein and Compton said the wave picture fails.
3. **How will we find out?** — Four gated phases: a native emission energy/momentum ledger (`E=hf` as
   tick-rate energy, `p=E/c`, **not** a photon mass) **before** any photon-collision kinematics; the
   photoelectric line by threshold vortex-coupling; Compton by emission↔vortex elastic recoil; the
   Thomson/inverse limits as the stretch. Recovering Compton by running the standard relativistic
   two-body photon-electron collision and relabelling it caps the grade at C (anti-tautology gate).
4. **What would prove us wrong?** — §Falsification, numeric: Millikan slope off `h` by >0.1%;
   `λ_C` off 2.426 pm by >0.1%; angular shift off `λ_C(1−cosθ)` by >0.1%; absorption time not
   sub-attosecond; or any result requiring a point photon to close.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

### Anti-tautology firewall

`E = hf` here is the **relay-tick energy** of an extended emission — `f` is the tick rate, `h` the
tick→energy conversion — **not** the energy of a localized light-quantum and **not** a second-
quantized field excitation. The load-bearing test: does momentum/energy bookkeeping *between an
extended relay emission and a bound vortex* reproduce `λ_C = h/(m_e c)` from the **vortex geometry**,
rather than from assuming a photon of momentum `h/λ` collides with a free electron? **Running the
standard photon–electron Compton kinematics and relabelling the photon an "emission" is the identity,
not the derivation — it caps the grade at C (row IMPORTED).** No QM wavefunction or field-operator
enters as mechanism; `W` (work functions) and `m_e` are MEASURED-INPUT, not fits.

## Question

The photoelectric threshold and the Compton wavelength shift are the textbook proofs that light is
a particle carrying `E=hf` and `p=h/λ`. SDT has no photon-particle — light is an emission. **Can
E55 (photoelectric: prompt sub-attosecond absorption with a sharp frequency threshold) and E56
(Compton: a measured wavelength shift on scattering off a bound vortex) be reframed as
emission↔vortex exchange — the relay impulse being absorbed into, or recoiling off, an electron
vortex with lattice momentum bookkeeping — reproducing `hf = W + KE_max` and
`Δλ = λ_C(1−cosθ)` without ever invoking a point quantum of light?** The "quantum" facts become
threshold and recoil facts about how a relay emission couples to a vortex.

## SDT mechanism & hypotheses

An electron is a bound vortex (Law VI topology). The emission's energy is `E = h·f` where `f` is its
relay-tick rate; absorption is the vortex swallowing the relay impulse in one coherent gulp (fast =
sub-attosecond, E55), possible only above the binding threshold `W`. Compton is elastic recoil: the
emission hands transverse + forward momentum to the vortex, which the lattice must conserve.

- **H1 (photoelectric threshold = vortex binding):** the emission couples only if its per-tick energy
  exceeds the vortex binding `W`; above threshold `KE_max = hf − W`, slope `h` (the relay tick→energy
  conversion), intercept `W` — Millikan's line, native, with `h` not a photon mass.
- **H2 (prompt absorption):** absorption time is one relay coherence time (sub-attosecond), matching
  attosecond-streaking measurements — no semiclassical build-up delay.
- **H3 (Compton = lattice recoil):** momentum conservation between emission and vortex gives
  `Δλ = (h/m_e c)(1−cosθ) = λ_C(1−cosθ)`; `λ_C` is the electron-vortex relay scale, recoverable from
  the vortex geometry, not from a photon collision postulate.

## Strategy

**Phase 1 — Emission energy/momentum ledger.** *Goal:* native `E=hf`, `p=E/c` for a relay emission.
*Method:* tick-rate × relay quantum from CR07 ruler. *Success:* `E` and `p` of an emission defined
without a photon, consistent with measured photon energies to <0.1%.

**Phase 2 — Photoelectric line.** *Goal:* `KE_max=hf−W`. *Method:* threshold coupling to a vortex of
binding `W`. *Success:* Millikan slope = `h`; thresholds for Na/Cs/W to order; prompt (attosecond) time.

**Phase 3 — Compton shift.** *Goal:* `Δλ=λ_C(1−cosθ)`. *Method:* emission↔vortex elastic recoil with
lattice momentum conservation. *Success:* `λ_C=2.426 pm` and the full angular shift to <0.1%.

**Phase 4 — Inverse/Thomson limits (stretch).** *Goal:* Thomson (`Δλ→0`) and inverse-Compton limits.
*Success:* low-energy and moving-vortex limits correct in sign and scale.

## Success criteria

- **PASS (A):** photoelectric line and Compton shift from emission↔vortex exchange, zero photon-particle, zero fits.
- **QUALIFIED (C):** the above with `W` (work functions) and `m_e` as MEASURED inputs (expected).
- **PENDING (D):** Compton recovered, photoelectric threshold only schematic (or vice versa).
- **FAIL (F):** cannot get the threshold/shift without reintroducing a point photon.

## ⑧ Falsification tests (each states the numeric outcome that kills it)

| ID | Test | SDT prediction | The number that kills it |
|----|------|----------------|--------------------------|
| F1 | Photoelectric line | `KE_max=hf−W`; Millikan slope = `h`; intercept = `W`; sharp threshold | fitted slope off `h` by >0.1%, or a soft (non-sharp) threshold ⇒ absorption is not a vortex-coupling threshold |
| F2 | Compton wavelength | `λ_C = h/(m_e c) = 2.426 pm` from vortex geometry; `Δλ=λ_C(1−cosθ)` | `λ_C` off 2.426 pm by >0.1%, or angular shift off `λ_C(1−cosθ)` by >0.1% ⇒ scattering is not lattice-momentum recoil |
| F3 | Prompt absorption | one relay coherence time, sub-attosecond (no semiclassical build-up delay) | a measured absorption delay above ~1 attosecond (inconsistent with single-relay coupling) ⇒ exchange not instantaneous-relay |
| F4 | No point photon | the whole ledger closes with an extended relay emission + bound vortex | if `λ_C` / the threshold can be obtained **only** by a localized `h/λ` quantum colliding with a free electron ⇒ no-photon-particle claim fails |
| F5 | Anti-tautology | Compton from emission↔vortex bookkeeping, not relabelled photon–electron kinematics | if the shift is reproduced only by the standard relativistic photon-electron collision relabelled ⇒ Class capped at **C**, row IMPORTED |

## Dependencies

**Upstream (required):** OP01 (emission relay, `c_local`, ruler `λ=N·ℓ_P`), **Law VI** (the electron
as a bound vortex — source of `λ_C` from geometry). **Ties (the measured anchors):** E55
(photoelectric, attosecond timing), E56 (Compton shift). **Downstream (unblocked):** OP06 (stimulated
emission = the reverse exchange), pair-production reframes. **Lateral:** E57 (Cherenkov, the inverse
"vortex outruns `c_local`" case). **Framework:** CR07 (relay ruler,
[[project_cq46_redshift_octaves]]), `Theory/00_Ruleset.md`, `Theory/05` audit spine.

## Questions This Opens *(generative — log new ones in `OP05_VERDICT.md`)*

1. **Is `λ_C` a readout of electron-vortex size?** If the Compton wavelength falls out of the Law-VI
   vortex geometry, is `λ_C` literally the vortex's relay circumference — and does that predict the
   muon/proton Compton scales from their topologies with no new input?
2. **Does the photoelectric threshold `W` equal the EMC04 electropause binding?** If "work function"
   = vortex binding depth, is the photoelectric line the same energy ledger as atomic binding (OP/AP),
   tying surface `W` to bound-vortex `z`?
3. **Is the absence of an intensity-threshold a relay statement?** SDT predicts the threshold is in
   `f` not in intensity (single-coupling). Does very-low-intensity attosecond data confirm there is
   never a multi-relay build-up route, even in principle?
4. **Is "wave-particle duality" dissolved here or merely deferred?** With diffraction (OP03) and
   Compton (OP05) both relay phenomena, is there any experiment left that *forces* a particle photon —
   or is duality fully an artifact of two incomplete pictures of one relay emission?
5. **Does inverse-Compton give the same ledger for a moving vortex?** Is astrophysical inverse-Compton
   (CMB up-scatter) the identical exchange with the vortex carrying the energy — a cross-check against
   cosmology (CR) with zero free parameters?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — OP05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (W and m_e are MEASURED-INPUT; h is the tick→energy conversion, not a fit)
- Engine namespaces used: law_VI:: (electron vortex → λ_C), depth_closure:: (emission relay), measured:: (h, m_e, c)
- Phase thresholds (committed before run):
    P1 emission E,p ledger consistent ≤0.1% · P2 Millikan slope=h ≤0.1%, sharp threshold, prompt ·
    P3 λ_C=2.426 pm ≤0.1%, full angular Δλ ≤0.1% · P4 Thomson/inverse limits correct in sign+scale
- Forbidden retroactive changes: relabel photon–electron collision kinematics then claim A;
    introduce a point photon / field operator as mechanism; widen tolerances; IDENTITY-PASS; local namespaces
```

### Pivot table (numeric triggers; optics-specific)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|-------------------|---------------|----------------|-----------|
| P2 Millikan slope off `h` by >0.1% | recheck tick-rate→energy conversion; per-tick coupling | **KILL** H1 (threshold) | tune the slope to `h` |
| P3 `λ_C` off 2.426 pm by >0.1% | derive `λ_C` from Law-VI vortex geometry, not `h/m_ec` by hand | **OPEN** the vortex-scale link | plug `λ_C=2.426 pm` |
| Compton only via relabelled photon collision | down-grade to **C**; tag row IMPORTED | — | claim A while running photon–electron kinematics |
| Any close requires a point photon | re-express as extended-emission↔vortex bookkeeping | **KILL** the no-particle claim, report it | smuggle an `h/λ` quantum / field operator |
| P3 prompt timing shows a real delay | check the relay coherence time; is multi-tick build-up forced? | **OPEN** the timing claim | ignore the measured delay |
| W or m_e needed beyond MEASURED-INPUT | keep as measured anchor (C on magnitude, A on mechanism) | **DEFER** the magnitude | call a fitted `W` derived |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*OP05 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
