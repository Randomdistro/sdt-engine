# FLM02 — Granular Pulse Mechanics: The Dynamic Throughput Law

> **Author:** J. C. Harvey, Melbourne. **Status:** WORKED-DERIVATION, UN-VERDICTED · **§K-DEEPENED 2026-07-13** (HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on any canon flag (incl. the "add a law section" criterion).
> **This one is different:** the derivation (GPI → F=ma → SR suite, 8 theorems) is *worked on paper*. §K here is **adversarial verification + reconciliation with FLM12**, then verdict. No auto-agents.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — **Whether F=ma and the SR suite genuinely *derive* from the Granular Pulse Invariant (GPI), or whether a step (GPI-3's δ = a·ℓ_P/c², GPI-8's Newton III) is asserted.** And whether FLM02's mechanism is the *same* as FLM12's (mass = field-resistance to vector change) — one root or two.
2. **Why does it matter?** — If GPI is the root, Laws III/IV/V are *consequences*, not independent posits — a major economy. But it must not double-count FLM12.
3. **How will we find out?** — Verify each theorem's algebra from `laws.hpp` symbols; check GPI-3/GPI-8 for hidden assertions; reconcile with FLM12 (§④ C3).
4. **What would prove us wrong?** — §⑧: if δ = a·ℓ_P/c² is posited (not derived from pulse-timing), or the SR suite quietly imports γ, the "derivation" is a restatement.
5. **How will we know we're done?** — Dual verdict; each theorem graded DERIVED / ASSUMED; FLM02↔FLM12 relationship named (shared root or distinct).

## Question (unchanged — the real target)

Laws III (force = occluded convergence), IV (mass = V_disp cost), V (v_circ²+v²=c²) each describe a different face of dynamics. **What MECHANISM connects them?** How does the granular pulse produce F=ma? Why is constant velocity free, acceleration costly? What is inertia, mechanistically?

## Answer — GPI axioms → theorems (to be graded, not re-assumed)

- **Axiom GPI:** every spation receives one relay pulse per ℓ_P per t_P, per direction, invariant under velocity/acceleration/gravity. Rate = 1/(ℓ_P·t_P). *c, ℏ, Planck units are consequences.*
- **Axiom CS:** after a velocity change ceases, omnidirectional input re-symmetrises at the new velocity (the new v becomes the resting state).
- **Axiom FL:** matter sits at the centre of its own flux; inertia is local to the throughput environment.

**Movement-only reading (FARMER PASS/BECOME/PRESS — already native):**
- constant v → symmetric pulse input → no reorganisation → **PASS** → free (Newton I).
- acceleration → pulse asymmetry δ → reorganisation load on V_disp → **PRESS** ("movement that cannot move" = the cost) → F=ma.
- CS re-symmetrisation → the reaction propagates back through the relay → Newton III.

Theorems GPI-1..8: c=ℓ_P/t_P; Newton I (symmetry); δ=a·ℓ_P/c² (asymmetry); **F = [Φ V_disp/(3ℓ_P³c²)]·a = m·a**; E_kin = ½mv² → (γ−1)mc²; time dilation v_circ=c/γ; Doppler; Newton III.

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| Law I Φ, ε, N | `laws.hpp` law_I | mechanism | ✔ |
| Law IV m = Φ V_disp/(3ℓ_P³c²) | `laws.hpp` law_IV | the mass in F=ma | ✔ |
| Law V v_circ²+v²=c² | `laws.hpp` law_V | the SR budget | ✔ |
| **FLM12 mass = field-resistance to vector change** | Investigations/01 | **same mechanism? (C3 reconcile)** | ⚠ dep |
| FLM08 `lattice_structure.hpp` | Engine | relay geometry | ✔ |
| FARMER §8 PASS/BECOME/PRESS | Investigations | movement modes | ✔ |
| "add law section to laws.hpp" (old criterion 4) | this prompt | **propose-only** — needs Harvey | ⚠ flag |

## ④ Strategy — three checks

**C1 — Verify F=ma.** Derive GPI-4 from GPI + V_disp in code; confirm the /3 quadrature share (Interchange flag #2 warns the banner sometimes drops it). *Metric:* F=ma exact, units close.
**C2 — Audit the SR suite for circular γ.** GPI-5/6/7 must produce γ from the budget (v_circ=c/γ), not assume it. *Kill:* if γ is imported to derive time dilation, it's a restatement (root-3).
**C3 — Reconcile with FLM12.** FLM12: mass = the field's resistance to a change of vector (relay-Doppler imbalance = inertia). GPI-4: pulse asymmetry δ = reorganisation load. **These look like one mechanism.** Determine: shared root (log once in STACK) or genuinely distinct. Do not present both as independent confirmations of inertia.

## ⑧ Falsifiers

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | GPI-4 gives F=ma with /3 share, units close | root-3 (dropped /3) |
| T2 | δ = a·ℓ_P/c² derived from pulse-timing, not posited | root-1 (asserted) |
| T3 | SR suite derives γ, doesn't import it | root-4 (γ contraband) |
| T4 | FLM02 mechanism ≡ FLM12 (one root) | root-2 (double-count if treated independent) |
| T5 | Newton III mechanism (CS re-symmetrisation) is real, not narrated | root-1 |

## ⑨.E Four-root sort
root-1 claim false (a theorem is asserted) · root-2 dependency (FLM12 shared root) · root-3 prompt/algebra (/3 share, units) · root-4 contraband (imported γ). Log per FAIL; FLM02↔FLM12 root once in STACK.

## Brainstorm — overlooked factors
- **FLM02 and FLM12 are almost certainly one mechanism** (inertia = relay asymmetry cost). The §K value here is *merging* them, not stacking two "derivations of F=ma."
- **GPI as the true root** would make Laws III/IV/V consequences — state that ambition, but only claim it if C1–C3 all pass without imports.
- **The /3 quadrature share** (Interchange #2) is a known doc/code slip in Law IV — make sure FLM02's F=ma carries it correctly.
- **"Add a law section to laws.hpp" is propose-only** — FLM02 may *propose* the GPI law block, but it cannot be written to the engine without Harvey.

## ⑤ Success / ⑥ Outputs
Class A: F=ma + SR suite derived from GPI with no imported γ, FLM12 reconciled to one root. Class C: F=ma clean, SR suite partially imports. Outputs: `RUN_LOG.md`, `flm02_*.cpp` (verify), `FLM02_DERIVATION.md`, `FLM02_VERDICT.md`, proposed GPI law block (for Harvey), STACK root entry.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — FLM02 (§K verify-and-reconcile)
- Prompt completion target: [A|B|C]
- Physics class hoped: [NATIVE|CONVERGENCE]
- CALIBRATED budget: 0
- Checks: C1 F=ma(/3 share) · C2 SR-γ audit · C3 FLM12 reconcile
- Forbidden: import γ to derive time dilation; present FLM02 & FLM12 as independent; write laws.hpp
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| SR suite imports γ | derive γ from budget | downgrade CONVERGENCE | claim NATIVE |
| FLM02 = FLM12 | merge, log one root | — | double-count |
| δ asserted | derive from pulse timing | OPEN the asymmetry law | posit and call derived |
| criterion 4 tempts engine edit | write a proposal block | — | edit laws.hpp |

**Disallowed:** post-hoc tolerance widening · imported γ · double-counting FLM12 · editing `laws.hpp`.

---

*FLM02 · §K-deepened 2026-07-13 · worked derivation to be graded; FLM02↔FLM12 is likely one inertia mechanism (reconcile, don't stack); the "add a law" criterion is propose-only.*
