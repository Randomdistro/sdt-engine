# TD05 — Phase Transitions and Latent Heat from Reconfiguration

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Is a phase transition a *native* lattice-packing reconfiguration threshold —
   melting/boiling when per-vortex disordered throughput exceeds the wake-binding throughput — with
   latent heat the Law IV reorganisation cost `L=N_bonds·Δε_reorg` paid at constant `T` (so `L=T_mΔS`
   and Clausius–Clapeyron follow), or does a sharp transition only appear once a Landau order-parameter
   field is imported, which SDT forbids?
2. **Why does it matter?** — This is where SDT's "matter is a hard vortex packing held by wakes and
   spation pressure" ontology has to produce a first-order transition with no free-energy functional
   handed in. It feeds the condensed-matter suite (12, esp. CM04 phonons/crystal lattice) and the
   non-ideal EoS term of TD03.
3. **How will we find out?** — Gated phases in §④; the native packing-threshold simulation before any
   imported order-parameter field.
4. **What would prove us wrong?** — §⑧ falsification tests with numeric triggers and real failure modes.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

## Question

Melting and boiling absorb latent heat at a fixed temperature — energy goes in but `T` does not rise.
Classically this is a free-energy crossing. The gap: derive a phase transition as a **lattice-packing
reconfiguration threshold** and latent heat as the **reorganisation cost** (Law IV flavour) of
repacking the vortex assembly into a looser configuration.

## SDT mechanism & hypotheses

Matter is hard solid vortices held in a packing by their mutual wakes and the surrounding spation
pressure. A phase is a packing motif (close-packed solid → mobile-but-bonded liquid → free gas). When
disordered throughput (heat) reaches a threshold, the packing can no longer hold and the assembly
**reconfigures**; the latent heat is the Law IV cost to reorganise the throughput bookkeeping of every
bond broken — paid at constant `T` because it buys configuration, not kinetic throughput.

- **H1 (transition = packing threshold):** melting occurs when per-vortex disordered throughput exceeds
  the wake-binding throughput holding the lattice motif; `T_m` is that threshold, not a fit.
- **H2 (latent heat = reorganisation cost):** `L = N_bonds × Δε_reorg`, the Law IV `V_disp` change
  between motifs; it absorbs heat at constant `T` because the throughput goes into configuration `W`
  (raising entropy `ΔS=L/T`, [[TD01]]), not into `½k_BT` per DoF.
- **H3 (Clausius–Clapeyron from pressure balance):** the coexistence line `dP/dT = L/(TΔV)` is the
  spation-pressure balance between the two packings — derived from occlusion equilibrium (Law III),
  not assumed thermodynamically.

## Strategy

1. **Threshold transition.** *Goal:* a sharp `T_m`. *Method:* heat a 2D/3D toy vortex packing; watch
   order parameter (motif coherence) collapse. *Success:* discontinuous motif loss at a definite
   `T_m`; hysteresis ↔ first-order character.
2. **Latent heat ledger.** *Goal:* `L` from reorganisation. *Method:* count bonds broken × `Δε_reorg`
   (Law IV `V_disp`) across the transition; compare to `T_m ΔS`. *Success:* `L = T_m ΔS` self-consistent;
   heat absorbed at flat `T` on the trace.
3. **Order-of-magnitude check.** *Goal:* real `L`. *Method:* set `Δε_reorg` from a measured bond
   energy proxy for one solid and one liquid→gas. *Success:* `L_melt`, `L_vap` within a factor of ~3
   of tabulated values; `L_vap ≫ L_melt` ordering reproduced (more bonds broken).
4. **Coexistence line.** *Goal:* Clausius–Clapeyron. *Method:* vary spation pressure (occlusion load),
   re-find `T_m`. *Success:* `dP/dT = L/(TΔV)` slope recovered to ~15%.

## Success criteria

- **PASS (Class A):** sharp transition + `L=T_mΔS` + Clausius–Clapeyron all from reconfiguration and
  Law III/IV, zero fitted parameters beyond the one measured bond-energy proxy.
- **QUALIFIED (Class C):** mechanism + `L_vap≫L_melt` ordering + slope native; absolute `L` within ~3×.
  *(Expected.)*
- **PENDING (Class D):** transition sharp but `L` magnitude needs a calibrated bond count.
- **FAIL (Class F):** the transition only appears with an imported Landau free-energy / order-parameter
  field SDT forbids.

## Falsification tests (each has a real failure mode + numeric trigger)

| # | Test | SDT prediction | If it fails (numeric trigger) |
|---|------|----------------|-------------------------------|
| T1 | Transition = packing threshold | discontinuous motif-coherence drop at a definite `T_m`; hysteresis (first-order) | if the order parameter falls **continuously** with no jump (no sharp `T_m`), there is no native first-order transition → **F** |
| T2 | Latent heat = reorg cost | `L=T_mΔS` self-consistent; heat absorbed at flat `T`; `L_vap > L_melt` | if `L ≠ T_mΔS` (mismatch `>` numerical noise) or `L_vap < L_melt`, `L` is not a configuration cost |
| T3 | Coexistence = pressure balance | `dP/dT = L/(TΔV)` recovered to ±15% from re-finding `T_m(P)` | if the slope is off `>15%`, Clausius–Clapeyron is not from native occlusion balance and must be imported |

## Dependencies

**Upstream:** Law IV (`V_disp`, reorganisation cost), Law III (occlusion/spation-pressure balance),
[[TD01]] (`ΔS=L/T`). **Downstream:** condensed-matter suite (12) crystal structure & melting; equation
of state in [[TD03]] (non-ideal/co-volume term is the same wake-overlap physics). **Related:**
**CM04** (Crystal Lattice & Phonons — the packing motifs / structural transitions whose melting this
predicts), **FLM08/CONDENSA** (the lattice packing geometry: corner-sharing CRN vs FCC vs icosahedral
motifs that set which solid phase is stable).
---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — TD05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 1 measured bond-energy proxy (declared); 0 other fitted params
- Engine namespaces actually used: law_IV (V_disp, reorg cost), law_III (occlusion/spation-pressure),
    measured::k_B, TD01 (ΔS=L/T); lattice motifs from FLM08/CONDENSA / CM04
- Phase thresholds (committed before run):
    P1 discontinuous motif collapse at a definite T_m (sharp, with hysteresis) · P2 L=T_mΔS self-consistent, L_vap>L_melt
    P3 L_melt,L_vap within 3× of tabulated · P4 dP/dT=L/(TΔV) slope within 15%
- Forbidden retroactive changes: import a Landau order-parameter field to manufacture the transition;
    plug L or T_m; widen tolerances; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 order parameter falls continuously (no jump) | refine the packing motif / heating rate; check for a metastable branch | **F** — no native first-order transition | inject a Landau double-well to force a jump |
| P2 `L ≠ T_mΔS` beyond numerical noise | recount bonds × `Δε_reorg`; check the entropy ledger (TD01) | **OPEN** the latent-heat ledger | plug `L` to satisfy `T_mΔS` |
| P3 `L` off `> 3×` tabulated | revisit the single bond-energy proxy (is it the right motif?) | grade D on magnitude; keep ordering native | tune the bond count to hit the table |
| P4 `dP/dT` slope off `> 15%` | recheck the two-packing occlusion-pressure balance | **OPEN** Clausius–Clapeyron link | import the thermodynamic relation directly |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (CM04 motifs not ready) | **DEFER** the structural phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (packing size, heating schedule, pressure sweep); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Importing a Landau free-energy / order-parameter field to manufacture the transition · plugging `L`
  or `T_m` · post-hoc tolerance widening · `atomic::`/GM/G in the native chain.

---

## Questions This Opens *(generative — log new ones in `TD05_VERDICT.md`)*

1. **Does the FCC-vs-icosahedral packing fork (FLM08) predict which solids are which?** If the stable
   motif sets the phase, can TD05 + CM04 predict a real crystal structure's melting point ordering
   without a fit?
2. **Is the glass transition a *failed* reconfiguration (FLM09 aging), not a true phase transition?**
   If melting is a packing threshold, a glass is the case where the lattice cannot relax in time — does
   TD05 naturally separate first-order melting from the kinetic glass arrest?
3. **Is latent heat literally the same `V_disp` reorganisation ledger as nuclear binding (Law IV)?**
   Both are "cost to repack a vortex assembly" — is melting a vastly geared-down version of the same
   bookkeeping that sets nuclear binding energies?

---

*TD05 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
