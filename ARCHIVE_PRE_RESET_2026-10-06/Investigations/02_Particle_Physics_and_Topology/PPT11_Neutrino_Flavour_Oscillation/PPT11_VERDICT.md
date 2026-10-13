# PPT11 — Neutrino Flavour Oscillation · VERDICT

> **Run:** 2026-07-01 · `ppt11_oscillation_length.py` → `ppt11_results.txt`.
> **Spec:** Tier-5, "THE HARDEST OPEN PROBLEM." Inputs: derivation basis + the three neutrino mass minima
> (MEASURED-INPUT) + measured Δm² (OBSERVED-TARGET only). **Zero fitted knobs.**

---

## DUAL VERDICT (both axes mandatory)

| Axis | Grade | Basis |
|------|-------|-------|
| **Prompt completion** | **A** | Tool executed P1–P4; emitted all §6 files (DERIVATION, tool, results, VERDICT, RUN_LOG); sanity gate + dimensional check + decisive table + robustness + independence audit all ran. |
| **Physics class** | **OPEN** (sharpened) — with a **Class-D numerical foothold** on the length | The oscillation length lands within ±1 decade of **both** measured scales with no knob, but the beat **mechanism** is unpaid (imported phase factor) and the P1 internal-DoF licence is in structural tension with the neutrino's defining zero-grip. |

**Headline (honest):** *The straight thread reproduces the measured oscillation scale as a number, but does not yet earn it as a mechanism.* The length is a Class-D foothold; the "why does a straight W=0 thread cycle in flight without a wavefunction" question returns **[OPEN]** — the outcome the spec called most likely. This holds the same bar as the just-run **FLM12-D1 (UNPAID)**: *accommodate ≠ derive.*

---

## What paid, and what did not

**PAID (numerical foothold — Class D):**
- Wake radii round-trip from the three masses to <1% (sanity gate PASS) — inputs wired correctly.
- `dφ/dx` is dimensionally `[1/length]` (P2 dimensional gate PASS).
- Splitting built **only** from the three minima (`Δm²_ij = m_j² − m_i²`), never from measured Δm² → no hard IDENTITY-PASS on the construction.
- `L_osc,SDT` lands within ±1 decade of **both** scales, zero knobs:
  - atmospheric (ν3−ν2, 1 GeV): **log₁₀ ratio −0.05 (12% off)**
  - solar (ν2−ν1, 1 MeV): **log₁₀ ratio −0.77 (within a decade)**
- Agreement is **E-independent** (T5 clears): not a coincidence of the chosen reference energy.

**UNPAID (the sharpened OPEN):**
- **The phase factor `1/(4ℏE)` is imported, not derived.** It is the standard mass-eigenstate oscillation phase. This run re-narrated it as a "geometric beat" but did **not** produce the factor (nor its `2`/`4`) from SDT relay cadence. Calling it native would be **LINGUISTIC-BORROW**. → `[OPEN]` mechanism.
- **The P1 internal-DoF is not cleanly licensed.** FLM11's census (spec) defines the neutrino's straight axis as the **zero-grip residue with no circulation to grip**. A pitch-precession beat needs an internal circulation to precess. The property that makes the neutrino a neutrino (open W=0, no ℓ=2 circulation, PPT04) removes the very clock a native beat needs. → structural tension, flagged.
- **The mass inputs are partially circular.** m₂=0.029, m₃=0.060 eV are literature best estimates partly informed by the measured Δm² upstream. They do **not** round-trip to the naive back-solve (0.0218/0.0541), so it is **not** a hard identity-pass — but the match is *partly inherited, not fully earned*. Caps the grade below C.

---

## Falsification table (spec §8, filled)

| # | Test | Outcome | Action taken |
|---|------|---------|--------------|
| **T1** | Straight W=0 vortex has ≥1 free internal angular DoF (FLM11) | **AMBIGUOUS → OPEN.** FLM11 grants the straight axis but defines it as zero-grip/zero-circulation; a beat needs a circulation to precess. The pitch DoF is *asserted by the engine* but *not licensed by the census*. | Recorded as the P1 gate hinge; carried as unpaid debt (no invented DoF). |
| **T2** | Flavour change requires no ΔW | **PASS.** All configs are W=0; no ΔW invoked anywhere. | Constraint held. |
| **T3** | Native (non-wavefunction) `dφ/dx` `[1/length]`, no fitted knob | **PARTIAL.** Dimensionally `[1/length]` with no fitted knob (PASS), BUT the kinematic factor `1/(4ℏE)` is **imported** from the mass-eigenstate result, not derived from SDT cadence. | Labelled `[OPEN]` mechanism (translation test FAIL-as-NATIVE). Not fished; stated plainly. |
| **T4** | Beat length within ±1 decade of ≥1 scale, no knob | **PASS (numerically).** Both scales within ±1 decade (atmos. 12%, solar within a decade), zero knobs. | Class-D foothold recorded — **not** relabelled a closure. |
| **T5** | Agreement robust vs E_ν (not a coincidence) | **PASS.** log₁₀ ratio exactly E-independent across 0.1 MeV–1 GeV. | Not a DEGENERATE E-coincidence. |

**Net:** T2, T4, T5 pass; T1 open; T3 partial (imported phase). The falsifier that decides the *physics class* is **T3+T1**, both of which land on the mechanism debt → **OPEN**.

---

## Root-cause tree (P4)

```
NUMBER PASSED (P3 floor met, both scales <1 decade)
├─ why? Δm²_ij(engine) ≈ measured Δm²_ij
│   └─ why? engine masses 0.029/0.060 eV give m₃²−m₂² ≈ 2.76e-3 ~ 2.45e-3
│       └─ ROOT: masses are literature best estimates PARTLY informed by Δm²
│                (not a hard identity-pass — no round-trip — but partial circularity)
└─ is the beat mechanism the reason it matched?  NO
    └─ ROOT: the 1/(4ℏE) phase factor was IMPORTED, not derived

MECHANISM FAILED to be NATIVE
├─ why no native dφ/dx? the kinematic factor was borrowed
│   └─ why couldn't SDT produce it? the pitch DoF is not licensed
│       └─ why not? FLM11 defines the straight axis as zero-grip / zero-circulation
│           └─ ROOT: the same geometry that makes the neutrino non-interacting
│                    (open W=0, no toroidal/poloidal circulation, PPT04 μ_ν≡0)
│                    removes the internal clock a native beat would precess.
│                    STRAIGHT-THREAD ⊥ FLAVOUR-BEAT are in structural tension.
```

**Two named root causes:** (i) partial circularity in the mass inputs; (ii) the beat clock is geometrically absent because the neutrino is defined by zero circulation. Neither branch ends "unclear."

---

## What would need to be true instead (the sharpened problem)

For PPT11 to close as NATIVE (Class A/C), one of these must be supplied — none was fabricated here:
1. **A native derivation of the `1/(4ℏE)` phase factor** from lattice relay cadence + resistance (V_disp) differences, producing the `2`/`4` from geometry, with no mass-eigenstate ket. This is the load-bearing hole.
2. **A licensed internal angular DoF** for the straight W=0 vortex that survives FLM11's zero-grip definition — a residual pitch freedom distinct from the graspable circulation the census zeroes out. (If FLM11's actual run grants **zero** such DoF, the naive beat is **KILLED**, not merely OPEN.)
3. **Independent SDT masses** — the three minima derived from geometry (Law IV / V_disp topology) *without* literature Δm² input, so the splitting match becomes fully earned rather than partly inherited.

Until at least (1)+(2) are paid, PPT11 ships as: **length foothold (Class D), mechanism [OPEN].**

---

## STRESS-TEST SELF-AUDIT

**(1) Independent, or identity/circular?**
*Partially independent, not clean.* The construction is **not** a hard IDENTITY-PASS: the splitting is built **only** from the three mass minima (`m_j²−m_i²`), never from the engine's `Dm21_sq/Dm32_sq` (which appear in the OBSERVED column only), and the engine masses do **not** round-trip to the naive Δm² back-solve (0.0218/0.0541 vs 0.029/0.060). **But** m₂, m₃ are literature best estimates partly informed by Δm² upstream → **partial circularity**, explicitly flagged, caps the grade below C. Separately, the **phase factor** `1/(4ℏE)` is **imported** from the mass-eigenstate result (a borrowed kinematic, not SDT-derived) — this is the deeper non-independence and the reason the physics class is OPEN, not D-clean.

**(2) Fished?**
*No.* Zero fitted knobs; the ±1-decade bar was pre-committed in `RUN_LOG.md` before running; no exponent or coefficient was tuned. The splitting form `m_j²−m_i²` is the only natural one (no exponent search — contrast the FLM12-D1 "squared solid-angle" that was honestly flagged as fished). No result was moved to pass. The atmospheric 12% match is what the rounded engine masses give, not a tuned value.

**(3) Dimensions.**
*Checked, PASS.* `dφ/dx = Δm² c³/(4ℏE)` reduces to `[1/length]` (tool `dimensional_check`). `L_osc` is metres. `Δm²_ij = m_j²−m_i²` is eV² (mass minima in eV). Wake radii round-trip in metres/µm to <1%. All comparisons done in dimensionless log₁₀ ratios (per §9, to avoid scale loss across µm→10³ km).

**(4) Honest class + what is owed.**
**Prompt completion A; Physics class OPEN (sharpened) with a Class-D numerical foothold on the length.** *Owed:* (a) a native derivation of the oscillation phase factor `1/(4ℏE)` from relay cadence — the imported kinematic is the load-bearing debt; (b) resolution of the P1 tension — whether the zero-grip straight vortex retains any internal angular DoF to precess (FLM11's actual run, uncompleted, decides OPEN-vs-KILL); (c) SDT-native masses independent of measured Δm². Until (a)+(b) are paid, this is **not** a closure. The straight thread reproduces the oscillation *scale* but has not yet earned its three flavours — it has **named the hole it cannot fill**, which for this Tier-5 spec is the complete and acceptable deliverable.

---

*PPT11 · length foothold (Class D), mechanism [OPEN] · accommodate ≠ derive · no number fished, no mechanism fabricated.*

---

**REASSESSMENT (2026-07-04, Harvey directive — §G GATE-CONTRABAND check)**

- **The ruling stands: OPEN (Class-D length foothold).** Checked for c-interference: the class was
  capped by the imported `1/(4ℏE)` phase factor and the partial mass circularity — neither clause
  enforced the rival's locality/c-cap axiom. Nothing above is altered.
- **One kill-hinge is scoped, not moved:** T1's OPEN-vs-KILL trigger ("if FLM11's actual run grants
  **zero** such DoF, the naive beat is KILLED") tacitly assumed the only possible internal clock is
  an energy-channel *circulation* (a grip-carrying flow — the thing FLM11's zero-grip definition
  zeroes out). Under the two-channel architecture (FLM14 RUN_LOG ADJ-7; Synchrony Theorem,
  FARMER_PASS 2026-07-03 refinements 5–6), a **gear-locked constraint phase is a locally-readable
  internal variable that carries zero grip** — it survives the zero-grip definition by
  construction. Re-open condition (per §G.3, premise-class named): premise class =
  single-channel/static-spation; if FLM14 rule-form-4 establishes the rotation DoF, an FLM11
  "zero circulation DoF" result downgrades that KILL to **OPEN — beat-clock candidate transfers to
  the constraint-channel gear phase**. The load-bearing debt (native derivation of the phase
  factor) is unchanged either way.
