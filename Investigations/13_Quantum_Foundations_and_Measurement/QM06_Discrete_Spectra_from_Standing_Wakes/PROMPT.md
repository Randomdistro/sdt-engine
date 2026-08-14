# QM06 — Discrete Spectra from Standing Wakes

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → **ACTIVE** on first gated run (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Domain:** Quantum Foundations & Measurement (relay-resonance quantisation, no ψ, no action postulate).
> **Engine:** `#include <sdt/laws.hpp>` — Phase 2+ may **compare** to `atomic::` only after Phase 1 native survival test.
> **Prior audit (2026-06-27):** `qm06_discrete_spectra.cpp` was IDENTITY-PASS (a wrapper around `atomic::`);
> the stale `QM06_VERDICT.md` signs "PASS, Class C" crediting that wrapper and is **SUPERSEDED** — see its banner.
> **Anti-tautology firewall:** the Rydberg ladder is `atomic::`'s by construction; calling
> `atomic::ionisation_energy_eV` / `atomic::rydberg_energy_eV` *in the derivation chain* is an
> IDENTITY-PASS and caps the grade at **C**. NATIVE requires Phase 1 to show integer-only wrap survival
> **before** any Rydberg formula is touched. This prompt supersedes the prior execution path.

---

## ⓪ The Golden Rule

1. **What don't we know?** Whether hydrogen level quantisation is **native relay resonance** (standing
   wake on a closed orbit) or only Bohr/Rydberg **relabelled** through `atomic::`.
2. **Why does it matter?** Core QM06 claim: no ψ, no action postulate — discreteness from wake survival.
   Blocks QM07 (fine structure), molecular spectra.
3. **How?** Phase 1: tick-by-tick wake on a ring (FLM05-style); Phase 2–3: ladder + lines from closure +
   electropause; Phase 4: quantum defect direction.
4. **Prove us wrong?** Non-integer wrap number survives ≥10⁴ ticks; Rydberg off >0.1% without `atomic::`;
   Hα wrong sign or >0.1%.
5. **Done?** Prompt **B** if Phase 1 PASS-GATE + Phase 2–3 compare within 0.1%; Physics **NATIVE** only
   if Phase 1 shows integer-only survival **before** importing Rydberg formula.

---

## ① Executive Summary

Standard QM: quantised action / ψ boundary conditions. SDT: a bound vortex orbits at electropause; its
**wake** wraps the path. Only circumferences with **integer relay wavelengths** sustain a standing wake;
others destructively cancel over many ticks — **resonance survival**, not an axiom.

**Question:** Does `2πr = nλ` emerge from tick propagation, and does `E_n = −Ry/n²` follow from closure +
PPT01 balance without calling `atomic::ionisation_energy_eV` in the derivation chain?

**Expected landing:** Phase 1 is the discriminator. If only Phase 2–3 run, class is **CONVERGENCE** (max).

---

## ② Physical Context

**Mechanism.** Orbital wake = relay field co-moving with vortex. Closure: `2πr = n · λ_wake` with
`λ_wake = h/p` (QM01 emission wavelength as **measured** relation, not ψ).

**Variables:**

| Symbol | Meaning | Engine |
|--------|---------|--------|
| `r` | Orbit radius | variable [m] |
| `n` | Wrap integer | dimensionless |
| `λ` | Wake wavelength | `h/(m_e v)` derivation basis |
| `Ry` | Rydberg energy | compare to `measured::Ry_eV` |
| `a₀` | Bohr scale | `measured::a_0` |
| `N_ticks` | Survival test length | ≥ 10⁴ committed |

**Targets (OBSERVED-TARGET only):** `E_n = −13.598 eV/n²`, Hα = 656.279 nm, `g_n = n²` (defer exact).

**Forbidden:** ψ, `atomic::` in Phase 1; importing Bohr postulate as input.

---

## ③ Theoretical Framework

**Hypotheses:**
- **H1:** Integer `n` = only surviving wrap numbers after `N_ticks` relay updates.
- **H2:** `r_n ∝ n²` from H1 + electropause balance (PPT01, EMC04).
- **H3:** `ΔE = hν` line from wake mode transition (APS01); Balmer from `E_n − E_m`.

**zk² = 1:** At ground: `z = (v₁/c)²`, `k = c/v₁`, verify `z·k² = 1` once — **IDENTITY**.

---

## ④ Investigation Strategy

### Phase 0 — Ledger (GATE)

Print `Ry`, `a₀`, `α`, Hα target; commit `N_ticks = 10000` in `RUN_LOG.md`.

### Phase 1 — Standing-wake survival (NATIVE — mandatory GATE)

- **Goal:** Show non-integer wrap decays; integer survives.
- **Method:** 1-D ring, `N_cell` sites; inject wake amplitude; each tick advance phase by
  `Δφ = 2π r / (n_wrap · N_cell)` per cell (or FLM05 handoff analogue). Measure total energy /
  coherence vs tick for `n_wrap ∈ {2.0, 2.5, 3.0, 4.0}`.
- **Success:**
  - Integer (2, 3, 4): amplitude ratio `A_final/A_init ≥ 0.9` at `N_ticks`
  - Half-integer (2.5): ratio **< 0.5** (destructive)
- **Failure:** If all persist → **KILL** H1 or PIVOT to 2-D ring (ADJ); do not skip to Phase 2.

### Phase 2 — Hydrogen ladder (DERIVED chain)

- **Goal:** `E_n = −Ry/n²`, `r_n = n² a₀/Z`.
- **Method:** Combine Phase 1 closure `2πr = nλ` with centripetal/occlusion balance (PPT01 electropause
  — document equation). Solve for `r_n`, `E_n` using `m_e`, `c`, `α` only.
- **Success:** `|E_1 + Ry|/Ry < 0.001`; `|r_1 − a₀|/a₀ < 0.001`.
- **Compare row (separate):** `atomic::ionisation_energy_eV` — label CONVERGENCE check, not Phase 2 PASS.

### Phase 3 — Spectral series

- **Goal:** Hα wavelength from `ΔE = E_3 − E_2`.
- **Success:** `|λ − 656.279 nm|/656.279 < 0.001`.
- **Failure >0.1%:** PIVOT emission formula (APS01); do not widen threshold.

### Phase 4 — Quantum defect (DEFER allowed)

Alkali `δ(n)` sign from core occlusion — qualitative OK for **C** grade.

---

## ⑤ Success Criteria — dual verdict

| Prompt completion | Requirement |
|-------------------|-------------|
| **A** | Phase 1 native + Ph 2–3 <0.1% |
| **B** | Phase 1 PASS + Ph 2–3 <0.1% |
| **C** | Phase 2–3 only via `atomic::` |
| **D** | Phase 1 partial |
| **F** | `atomic::` only, no Phase 1 |

| Physics class | Condition |
|---------------|-----------|
| **NATIVE** | Phase 1 PASS-GATE |
| **CONVERGENCE** | Rydberg/Balmer match, Phase 1 skipped or weak |
| **KILLED** | All wrap numbers survive equally |

---

## ⑥ Outputs

1. `QM06_DERIVATION.md`
2. `qm06_standing_wakes.cpp` — Phase 1 simulator + Phase 2–3 derived (no `atomic::` in Phase 1 path)
3. `qm06_results.txt`
4. `RUN_LOG.md`
5. `QM06_VERDICT.md` — dual verdict

---

## ⑦ Dependencies

**Upstream:** FLM05 (pulse propagation), PPT01, APS01, EMC04 electropause.
**Downstream:** QM07 fine structure.
**Blocked if:** Phase 1 KILL — entire native quantisation claim **OPEN**.

---

## ⑧ Falsification Tests (each has a real failure mode + numeric kill trigger)

| ID | Test | SDT prediction | What kills it (numeric) |
|----|------|----------------|-------------------------|
| T1 | wrap-survival is integer-selective (the NATIVE discriminator) | integer n∈{2,3,4}: A_final/A_init ≥ 0.9 at 10⁴ ticks; half-integer 2.5: ratio < 0.5 | if **all** wrap numbers survive ≥0.9 (no selection), or integers also decay <0.9, resonance-survival is not the quantiser → KILL H1 or PIVOT to 2-D ring |
| T2 | ladder is native, not relabelled | `E_1 = −Ry` to 0.1% from closure + electropause balance, using m_e/c/α only | if E_1 matches only when `atomic::ionisation_energy_eV` is called in the chain, it is an IDENTITY-PASS → C, not native; if off >0.1% from the native balance, OPEN the electropause coupling |
| T3 | spectral line is native | Hα from ΔE=E_3−E_2 to 0.1% (656.279 nm) | if Hα is off >0.1% or only via `atomic::`, OPEN the transition mechanism (do not widen 0.1%) |

---

## Questions This Opens *(generative — log new ones in `QM06_VERDICT.md`)*

1. **Does the half-integer decay rate carry a signature?** The *shape* of the destructive cancellation
   for n=2.5 (how fast, with what beat) may encode the relay coherence length — a number, not just a
   pass/fail.
2. **Is `r_n ∝ n²` forced by survival alone, or does it need the electropause?** If H1 (integer wrap)
   gives the ladder *spacing* but the absolute scale needs PPT01, that splits the native claim cleanly
   into "discreteness" (native) vs "scale" (electropause) — which is which?
3. **Does the same survival rule give the l-degeneracy / fine structure (the QM06 ANGULAR-DOF blocker)?**
   The stale verdict marks fine structure OPEN. Is the angular degree of freedom a *second* wrap
   condition on the wake, and does it lift the degeneracy in the right direction (→ QM07)?
4. **Where does `2πr=nλ` break for high Z or high n?** A relay-resonance condition on a curved
   least-resistance path may deviate from the flat Bohr ring — a predicted departure from `−Ry/n²` that
   is SDT-only.

## ⑨ Implementation Notes

- Phase 1 must compile standalone; no `#include` beyond `laws.hpp` for measured constants.
- Use `measured::hbar`, `measured::m_e`, `measured::c` for λ.
- Print survival curves to results file for audit.

---

## ⑩ Adaptive Execution Protocol

### Pre-Run Commitments

```markdown
- N_ticks = 10000
- P1 integer survival: A_ratio ≥ 0.9
- P1 half-integer: A_ratio < 0.5
- P2/P3: 0.1% thresholds (fixed)
- CALIBRATED budget: 0
- Forbidden: atomic:: in Phase 1; retro-PASS
```

### Pivot table

| Trigger | PIVOT | If fail | Forbidden |
|---------|-------|---------|-----------|
| P1 all n survive | 2-D ring; damping model | KILL H1 | Jump to atomic:: |
| P2 Ry off >0.1% | Refine electropause F balance | OPEN | Plug Ry |
| P3 Hα off | Check ΔE units | OPEN | Widen 0.1% |

---

*QM06 · quantisation must survive the ticks, not the namespace.*
