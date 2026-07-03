# PM05 — Magnetic Reconnection and Solar Flares from Wake Topology

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Standard MHD cannot explain *fast* reconnection: Sweet–Parker gives a rate
   `∝ 1/√S` that is orders too slow for observed flares, and the fast-rate plateau (~0.1 `v_A`) is
   inserted by hand (Petschek/anomalous resistivity). **Does treating reconnection as a GOM06 wake
   *topology snap* — where finite relay diffusion (FD02) lets the summed wake jump to a lower-stored
   configuration — produce the fast ~0.1 `v_A` rate *without* an anomalous-resistivity fudge**, and does
   the released energy equal the annihilated anti-parallel swirl with a closed throughput ledger?
2. **Why does it matter?** — If the rate falls out of traction topology rather than resistivity, SDT
   explains the single biggest failure of resistive MHD and powers space-weather (flares/CMEs) from
   wake bundles. PM05 sits downstream of PM01 (swirl bundles) and PM07 (frozen-in flux it breaks); it
   feeds magnetosphere/space-weather coupling.
3. **How will we find out?** — Four gated phases (§④): stored throughput → topology snap + ledger →
   rate from traction → flare/CME budget. The native energy and rate (P1→P3) precede any resistive-MHD
   comparison; standard rates are CONVERGENCE targets, never imported.
4. **What would prove us wrong?** — §⑧, each falsifier with its killing number (ledger not closing,
   rate not recovering `1/√S` + fast plateau, flare energy off by orders).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase.

## Question

Anti-parallel swirl regions (PM01) store throughput in their sheared wakes. When the wake topology
reconfigures, that stored throughput dumps explosively. **Can magnetic reconnection — and the solar
flare / CME it powers — be derived as a change in collective wake topology that releases stored relay
throughput, with the energy budget and reconnection rate falling out of traction, not a resistive-MHD
postulate?** Frozen-in flux (the constraint reconnection breaks) is wake advection (PM07); breaking it
is a GOM06 topology change. No magneton; energies in native circulation units, converted once at the end.

## SDT mechanism & hypotheses

Two opposed swirl bundles are normally **frozen-in** — their wakes advect with the lattice flow and
cannot cross. In a thin current sheet the relay smoothing (finite resistivity ≡ relay diffusion, FD02)
lets the wake topology **snap** to a lower-stored-throughput configuration; the released throughput
heats and accelerates the local vortex population (flare) and launches a wake bundle (CME).

- **H1 (reconnection = topology snap):** model the X-point as a GOM06 topology change of the summed
  wake; show stored throughput drops by the annihilated anti-parallel swirl energy `∝ B²/2µ₀` (native form).
- **H2 (rate from traction):** the inflow/outflow ratio (reconnection rate) follows from PPT06 traction
  at the sheet; recover Sweet–Parker `∝ 1/√S` and the **fast** ~0.1 `v_A` plateau (Petschek-like).
- **H3 (flare/CME budget):** released throughput partitions into heat + bulk acceleration; recover a
  flare energy order (10³¹–10³² erg) and a CME launch speed from the released wake bundle.

**Anti-tautology firewall.** The *trivial* result is to write `U = B²/2µ₀`, "annihilate" the
anti-parallel component, and report the difference — that is energy bookkeeping with the answer assumed.
The *load-bearing* result is: (i) the released energy must equal the annihilated swirl with a **closed
throughput ledger** (nothing created), and (ii) the **fast rate ~0.1 `v_A` must come out of PPT06
traction at the sheet**, not from an inserted anomalous resistivity. **Recovering `1/√S` by importing
the Sweet–Parker formula caps the grade at C**; the rate is only NATIVE if traction produces it.
**Native-before-borrowed / forbidden:** no resistive-MHD Ohm's law as primitive (resistivity ≡ FD02
relay diffusion), no µ_B/µ_N/magneton (energies in native circulation units, SI map once at the end),
no G/M-fundamental, no QM wavefunction. `∇·B=0` (E58) must survive the topology snap.

## Strategy

**Phase 1 — Stored throughput.** Build two opposed PM01 swirl bundles; compute stored relay energy.
*Goal:* `U_stored`. *Method:* integrate swirl energy density. *Success:* matches `B²/2µ₀` form natively.

**Phase 2 — Topology snap.** Allow relay diffusion (FD02) at the sheet; let topology reconfigure.
*Goal:* energy released. *Method:* GOM06 topology transition + ledger. *Success:* `ΔU` = annihilated
anti-parallel component to <5%; ledger closes (no throughput created).

**Phase 3 — Rate.** Measure inflow/outflow from traction. *Goal:* reconnection rate. *Method:* sheet
traction balance. *Success:* Sweet–Parker `1/√S` recovered; fast-rate plateau ~0.1 `v_A` order-correct.

**Phase 4 — Flare/CME.** Drive `magnetosphere.hpp`-style active-region geometry. *Goal:* energy + speed.
*Method:* release partition. *Success:* flare energy 10³¹–10³² erg order; CME speed 10²–10³ km/s order;
inputs (active-region B, scale) flagged MEASURED.

## Success criteria

- ✅ **PASS (A):** topology-snap energy + rate + flare order all native, zero fitted params.
- ✅ **QUALIFIED (C):** energy & rate forms reproduced; one flagged sheet-geometry coefficient. *(Expected.)*
- ⚠️ **PENDING (D):** stored-energy & snap shown but rate only scaling-correct.
- ❌ **FAIL (F):** cannot release energy without importing resistive-MHD Ohm's law as primitive.

## Falsification tests (each states the number that kills it)

| # | Test | SDT prediction | If it fails (the killing number) |
|---|------|----------------|----------------------------------|
| T1 | Energy = annihilated swirl | `ΔU` matches annihilated anti-parallel component to <5%; throughput ledger closes (in − out = stored − released, residual <1%) | residual >5%, or ledger creates throughput → reconnection is not a topology-snap dump |
| T2 | Rate from traction | slow branch recovers `1/√S`; **fast branch ~0.1 `v_A` emerges from PPT06 traction, no anomalous-η insert** | fast rate only reachable by inserting anomalous resistivity → rate not traction-derivable → C, not A |
| T3 | Flare/CME budget | flare energy 10³¹–10³² erg (within an order); CME speed 10²–10³ km/s | predicted energy off by >1 order, or CME speed outside band → wake-bundle release cannot power the events |
| T4 | `∇·B=0` through the snap | divergence stays ≤1e-9 across the topology change | a monopole appears at the X-point during reconnection → E58 violated, ontology breaks |

## Questions This Opens *(generative — log in `PM05_VERDICT.md`)*

1. **Is the fast-rate plateau a topological selection rule, not a transport coefficient?** If ~0.1 `v_A`
   is set by the *allowed* wake-topology transitions (GOM06) rather than resistivity, SDT predicts a
   rate that is nearly geometry-fixed and weakly dependent on `S` — a falsifiable departure from MHD.
2. **Does the topology snap quantise the released energy?** If wake topology jumps by integer winding
   (Law VI), flare energies may cluster at discrete multiples rather than a continuum — testable against
   the flare energy-frequency distribution (the observed power law).
3. **Is "resistivity = FD02 relay diffusion" enough, or is there a genuinely collisionless channel?**
   The fastest events may need wake reconnection with no diffusion at all — is that an OPEN native mode?
4. **Does the CME wake bundle carry the same handedness signature across a solar cycle?** If launch
   handedness is EMC03-locked to the source region, SDT predicts a chirality correlation in CMEs.

## Dependencies

**Upstream:** [[PM01_Magnetism_as_Collective_Vortex_Circulation]] (swirl bundles), GOM06 (wake topology),
FD02 (relay diffusion ≡ resistivity), `Engine/include/sdt/magnetosphere.hpp` (active-region geometry).
**Downstream:** space-weather / magnetosphere coupling, [[PM07_Magnetohydrodynamics_Coupling_to_the_Fluid_Suite]] (frozen-in flux it breaks).
**Related:** [[PM04_Plasma_Oscillations_and_Debye_Shielding]] (heated population), E58 (∇·B=0 preserved through the snap), [[feedback_no_borrowed_units]].
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — PM05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces actually used: law_VI (topology), law_III; PM01 swirl bundles, FD02 relay diffusion, magnetosphere.hpp
- Phase thresholds (committed before run): P1 U_stored vs B²/2µ₀ form · P2 ΔU <5% + ledger residual <1% · P3 rate 1/√S + fast plateau from traction · P4 flare 10³¹⁻³² erg / CME 10²⁻³ km/s
- Forbidden retroactive changes: import Sweet–Parker/anomalous-η to hit the rate then claim A; import resistive-Ohm as primitive; quote energies in µ_B/µ_N; widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (domain-specialized for PM05)

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P2 ledger residual > 1% (throughput created) | hunt the bookkeeping leak in the snap | **KILL** H1; reconnection is not a clean dump | average the leak away |
| P3 fast plateau needs anomalous-η insert | re-derive inflow/outflow from PPT06 traction | down-grade rate to **C** (Sweet–Parker imported) | insert anomalous resistivity, claim native |
| P3 only `1/√S` (no fast branch) | check the topology-snap channel (GOM06) | **OPEN** the fast-reconnection problem honestly | claim fast rate without a native source |
| P4 flare energy off by >1 order | check active-region inputs (flag MEASURED) | **DEFER** P4; report the order gap | retro-tune B/scale to hit 10³¹ erg |
| `∇·B` ≠ 0 during the snap | fix the topology-transition stencil | **KILL** the snap model; E58 violated | hide the monopole |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | claim Class A |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · Snell/reciprocity-only as Fermat PASS.

---

*PM05 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
