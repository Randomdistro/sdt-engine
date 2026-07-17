# PPT06: Spation Traction from the Trefoil — How the Gears Start

> **Author:** J. C. Harvey, Melbourne. **Status:** RESULTS-ON-FILE, UN-VERDICTED · **§K-DEEPENED 2026-07-13** (HUNTER §K.3).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · `HUNTER_PROTOCOL.md` §K.
> **Engine:** `#include <sdt/laws.hpp>` only. **Propose-only** on any canon flag.
> **This one is different:** the derivation is *done* (INVESTIGATION.md + `cq14_spation_traction.cpp`, May 2026). §K here is **adversarial verification + verdict-filing**, NOT new phases. The job is to run the falsifiers the original never faced, then file `PPT06_VERDICT.md`.
---

## ⓪ The Golden Rule — five questions (answered)

1. **What don't we know?** — Whether the completed results (**v_phase = 1.831c** at R_p, **traction ratio T = 3(W+1) = 12**, three ℓ-channels, ~10⁸ nuclear→atomic gear) are **DERIVED or fitted** — no verdict has ever graded them.
2. **Why does it matter?** — 1.831c is load-bearing across the repo (the 1.83c counter-seat gives μ_n sign+order, Q_β, the neutron ledger). If T = 12 or the ℓ-channel assignment is a fit, several downstream results inherit the debt.
3. **How will we find out?** — Re-derive each headline from `laws.hpp` symbols alone (§④), then apply §⑧ falsifiers. Verify `cq14_spation_traction.cpp` compiles and reproduces the numbers.
4. **What would prove us wrong?** — §⑧: if T = 12 requires choosing W, or the ℓ=1/2/3 → Coulomb/magnetic/orbit map is asserted not derived, downgrade to CONVERGENCE/OPEN.
5. **How will we know we're done?** — `PPT06_VERDICT.md` filed with dual verdict; every [x] criterion re-graded DERIVED / COMPUTED / ASSUMED.

## The Question (unchanged — earned)

Proton = W=3 trefoil circulating at c. Phase velocity on contact spations at R_p is v_phase = c/k_surface = c/0.5464 = **1.831c** — superluminal. The lattice cannot relay faster than c. **What happens to the velocity deficit?** Answer: it splits into three output channels; the surplus demand *is* the force.

## Key Results (to be re-graded, not re-assumed)

1. **Traction ratio** T = ω_demand/ω_max = 3(W+1) = 12 — trefoil demands 12× lattice angular capacity.
2. **Three channels:** traction (ℓ=1, Coulomb) · rotation (ℓ=2, magnetic) · entrainment (ℓ≥3, orbits).
3. **Gear ratio** nuclear→atomic ω_p/ω_e ≈ 10⁸ — lattice carries rotation fm→pm.
4. **Ontic vs kinetic:** CMB convergence = fuel; trefoil circulation = engine.

## Dependency Map (§K.3)

| Item | Where | Enters as | Live? |
|------|-------|-----------|-------|
| k_proton_surface = 0.5464 | `laws.hpp:450-453` | DERIVED input (verify on file) | ✔ |
| v_phase = c/k ≈ 1.831c | `laws.hpp:1268` | the headline | ✔ |
| CQ11 trefoil budget sin²θ* = 1/3 | Investigations | UPSTREAM — verify | ⚠ |
| wake tensor ℓ-expansion | `Theory/01_Closure_Derivations.md` | UPSTREAM (channel map) | ⚠ |
| T = 3(W+1) | this investigation | claim to grade | — |
| 1.831c downstream | NP15 μ_n, NP20 Q_β, neutron ledger | **NEIGHBOURS** (§⑧ neighbour test) | ✔ |

## ④ Re-verification strategy (three checks, not three routes)

**C1 — Reproduce.** Compile `cq14_spation_traction.cpp`; confirm 1.831c, T=12, 10⁸ from `laws.hpp` symbols with no local constants. *Fail → root-2/3.*
**C2 — Is T = 12 predicted or chosen?** Derive 3(W+1) for W=3 from the winding geometry *without* assuming the answer; check it also gives the right T for W=1 (electron) as a control. *Fail → downgrade to CONVERGENCE.*
**C3 — Is the ℓ-channel map derived?** The ℓ=1/2/3 → Coulomb/magnetic/orbit assignment must come from the wake multipole expansion (Theory/01), not be asserted. Movement reading: each ℓ is a distinct *mode of shedding the superluminal surplus* — name the shedding mechanism per ℓ. *Fail → OPEN the channel map.*

## ⑧ Falsifiers (the adversarial pass the original skipped)

| Test | Predicted | If FAIL → root |
|------|-----------|----------------|
| T1 | T = 3(W+1) holds for W=1 control (not just W=3) | root-1 (formula fit to proton) |
| T2 | 1.831c independent of any atomic-scale input (delete-test) | root-2 (hidden α/atomic dep) |
| T3 (neighbour) | re-graded 1.831c preserves NP15 μ_n & NP20 Q_β | root-2 cascade if it shifts |
| T4 | ℓ-channel map derived from wake multipoles, not labelled | root-3 (asserted map) |
| T5 | "superluminal phase velocity" is not a BORROW of QM phase-velocity | root-4 (contraband) — it must be a *lattice relay deficit*, native |

## ⑨.E Four-root sort
root-1 claim false · root-2 dependency (k_surface, CQ11, 1.831c neighbours) · root-3 prompt/derivation under-specified (channel map) · root-4 contraband (QM phase-velocity smuggle). Log per failure; neighbours are witnesses (§H.5).

## Brainstorm — overlooked factors
- **v_phase > c is the mechanism, not a paradox.** The deficit *is* the force — this is the anti-QM move; make sure the verdict states it in movement terms (relay cannot keep up → surplus sheds as ℓ-multipoles), never as "phase velocity can exceed c" (that borrows the QM escape hatch).
- **T = 12 = 3(W+1) and FLM07's T = 3(W+1) = 12** (memory) are the same object — cross-reference; if both derive it independently that's CONVERGENCE, if one feeds the other it's not.
- **The 10⁸ gear** is the fm→pm carry; check it equals a_0/R_p-type ratio and isn't independently fit.
- **1.831c ≈ √(10/3)?** (1.8257) — 0.3% off; flag as a *possible* clean form to test, not to assume (look-elsewhere first).

## ⑤ Success / ⑥ Outputs
Class A: all four headlines re-derived DERIVED, W=1 control passes, neighbours hold. Class C: T=12 correct but ℓ-map asserted. **File `PPT06_VERDICT.md`** (dual verdict + re-graded criteria) · refresh `cq14_spation_traction.cpp` results · `RUN_LOG.md`.

---

## ⑩ Adaptive Execution Protocol

```markdown
## Pre-Run Commitments — PPT06 (§K verify-and-verdict)
- Prompt completion target: [A|B|C]  (results exist; grading them)
- Physics class hoped: [NATIVE|CONVERGENCE]
- CALIBRATED budget: 0
- Checks this session: C1 reproduce · C2 T-control · C3 ℓ-map
- Verify on file: laws.hpp:450-453, :1268; CQ11 budget; Theory/01 ℓ-expansion
- Neighbours to protect: NP15 μ_n, NP20 Q_β (must not shift)
- Forbidden: assume T=12; label ℓ-channels without deriving; QM phase-velocity as the mechanism
```

| Trigger | PIVOT | If fails | Forbidden |
|---------|-------|----------|-----------|
| cq14 tool won't reproduce | fix refs/units (ADJ) | STOP, report blocker | fit to 1.831c |
| T=12 fails W=1 control | re-derive 3(W+1) generally | downgrade CONVERGENCE | claim Class A |
| ℓ-map only labelled | derive from Theory/01 multipoles | OPEN channel map | assert the map |
| 1.831c shifts a neighbour | trace cascade (root-2) | flag downstream debt | hide the shift |

**Disallowed:** post-hoc tolerance widening · QM phase-velocity smuggle · asserting the ℓ-channel map · atomic-scale input in the nuclear derivation.

---

*PPT06 · §K-deepened 2026-07-13 · results-on-file; this pass grades them adversarially and files the missing verdict. 1.831c is a load-bearing neighbour — protect it or trace the cascade.*
