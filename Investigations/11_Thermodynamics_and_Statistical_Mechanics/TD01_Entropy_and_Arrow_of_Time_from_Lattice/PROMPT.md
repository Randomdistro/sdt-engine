# TD01 — Entropy and the Arrow of Time from Lattice Microstates

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC → **ACTIVE** on first gated run.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `measured::k_B`, `measured::l_P`, `law_I::epsilon` — combinatorics + relay tick narrative.
> **Prior audit:** Stars-and-bars only — no H-theorem, no relay mixing.

---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is `S = k_B ln W` a *literal* count of relay microstates (TD01 is the TD
   root), and — the load-bearing, falsifiable part — does per-tick neighbour redistribution drive `W`
   **monotonically up** from a non-equilibrium start, giving an H-theorem analogue **without** importing
   Boltzmann's Stosszahlansatz (molecular-chaos assumption)?
2. **Why does it matter?** — Everything above it depends on this: TD02 (temperature `1/T=∂S/∂E`), and
   thence TD03/TD04/TD05/TD06/TD07/TD08. The thermodynamic arrow here is the *same* relay asymmetry as
   the cosmological one ([[project_sdt_cyclic_cosmology]]).
3. **How will we find out?** — Phase 1 combinatorics (stars-and-bars, may reuse existing); Phase 2 the
   **native relay-tick mixer** monotonicity test; Phase 3 ideal gas from occlusion (DEFER to TD03 OK);
   Phase 4 the arrow narrative.
4. **What would prove us wrong?** — §④/§⑤ falsifiers with numeric triggers: if `⟨S⟩` has a **net**
   decrease over 10⁴ ticks from a hot start (trend `dS/dt < 0`), or if `ln W` is not extensive in `E`
   (doubling `E,N` does not double `ln W` to ±5%), the lattice-microstate thesis fails.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

---

## ANTI-TAUTOLOGY firewall (the one test that can fail)

The combinatorial `S=k_B ln W` (Phase 1) **cannot fail** — it is a definition plus Stirling, and on its
own earns at most **C** (it is the identity, not the physics). The load-bearing, falsifiable content is
**Phase 2**: the arrow must emerge from the *native relay update* (a deterministic/stochastic per-tick
neighbour exchange, FLM02 GPI), **not** from assuming molecular chaos (Stosszahlansatz) or coarse-graining
by hand. Importing the H-theorem's chaos assumption as machinery caps the grade at C — deriving
monotone `⟨S⟩` from the bare relay update is what earns A on the arrow.

---

## ① Executive Summary

Lattice is discrete at ℓ_P. **Question:** Does entropy emerge from counting relay configurations, and does per-tick neighbour redistribution **monotonically increase** W (H-theorem analogue) without an imported Stosszahlansatz?

---

## ④ Phases

### Phase 1 — Combinatorics (GATE — may reuse existing; identity, not physics)

Stars-and-bars `W(E,N)`; `S = k_B ln W`; monotone in `E`; **extensive** (doubling `E,N` doubles `ln W`
to ±5%). Stirling check at `E=1000, N=50`, err <5%. *(This phase cannot fail — caps at C alone.)*

### Phase 2 — Relay mixer *(GATE — the native, falsifiable core)*

- **Method:** N cells, E quanta; each tick a relay neighbour exchange (FLM02 GPI); track `W` proxy
  (log of accessible-states estimate) or **exact** count for N≤12, E≤20. The update is the bare relay
  rule — **no Stosszahlansatz, no hand coarse-graining** (firewall).
- **Success (A on the arrow):** `⟨S⟩` non-decreasing trend over 10⁴ ticks from a non-equilibrium (hot)
  start; net `ΔS ≥ 0`; **never** RETRO-PASS on a single-tick dip — require the *trend* `dS/dt ≥ 0`.
- **Falsify:** a net `⟨S⟩` decrease (`dS/dt < 0` over the run) kills the lattice-arrow thesis → **F**.

### Phase 3 — Ideal gas (DEFER partial)

`PV = N k_B T` from occlusion pressure — overlaps TD03; OK to **DEFER** to TD03.

### Phase 4 — Arrow narrative

Document how a (micro-reversible) per-tick relay rule yields macro irreversibility — and tie the
thermodynamic arrow to the cosmological one ([[project_sdt_cyclic_cosmology]]).

---

## ⑤ Dual verdict

| Grade | Met when |
|---|---|
| **A** | Phase 1 + Phase 2 native arrow (`dS/dt ≥ 0` from hot start, no Stosszahlansatz) + Phase 3 ideal gas within 20% |
| **B** | Phase 1 + Phase 2 native arrow |
| **C** | Phase 1 only (`S=k_B ln W` identity) — the combinatorics, not the physics |
| **D** | Combinatorics without a working mixer (arrow unexecuted) |
| **F** | `⟨S⟩` trends **down** under the relay update, or `ln W` not extensive in `E` |

---

## ⑥ Outputs

`td01_microstates.cpp` (extend with Phase 2), `TD01_DERIVATION.md`, `RUN_LOG.md`, `TD01_VERDICT.md`.

---

## Questions This Opens *(generative — log new ones in `TD01_VERDICT.md`)*

1. **Is the arrow's direction set by the lattice's initial low-entropy state, the same way the
   cosmological arrow is?** If both arrows are one relay asymmetry, does TD01's hot-start condition map
   onto the cyclic-cosmology recharge ([[project_sdt_cyclic_cosmology]])?
2. **How does a (micro-reversible) tick rule give macro irreversibility without Stosszahlansatz —
   is it the relay's information-erasure (TD07) at coarse-graining?** Is the arrow literally Landauer
   accounting on the relay update?
3. **Is there a maximum-entropy lattice state (heat death) or does reconfiguration (TD05) keep `W`
   growing?** Does the superfluid-substrate picture forbid a true equilibrium?

---

## ⑩ Commitments

```markdown
## Pre-Run Commitments — TD01
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 (k_B is the only whitelisted input)
- Engine namespaces actually used: measured::k_B, measured::l_P, law_I::epsilon, FLM02 GPI relay update
- Phase thresholds (committed before run):
    P1 Stirling err <5% at E=1000,N=50; ln W extensive ±5% · P2 net ΔS ≥ 0, trend dS/dt ≥ 0 over 10⁴ ticks from hot start
    P3 PV=Nk_BT within 20% (or DEFER to TD03)
- Forbidden retroactive changes: import the Stosszahlansatz / molecular-chaos assumption as the arrow
    mechanism; RETRO-PASS on a single-tick dip; grade A on Phase 1 alone; ensemble postulate as axiom
    without a lattice update; widen the 5%/20% gates
```

---

*TD01 · 10× upgrade 2026-06-29 · counting is the identity (C); the native mixer is the arrow (A).*
