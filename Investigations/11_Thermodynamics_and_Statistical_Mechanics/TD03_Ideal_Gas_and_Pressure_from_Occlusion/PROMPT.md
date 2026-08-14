# TD03 — Ideal Gas and Pressure from Occlusion

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (upgrade 2026-06-27).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answered, not stubbed)

1. **What don't we know?** — Is `PV = Nk_BT` a *native* consequence of Law III occlusion — the
   convergence-momentum flux a relay gas deposits on a wall — with the geometric factor `1/3` forced by
   **3-D lattice isotropy** (the genuinely new content), or does it only reproduce because it inherits
   TD02's equipartition `½m⟨v²⟩=(3/2)k_BT`, which is itself the part at risk of importing the Boltzmann
   ensemble? In short: which step here is load-bearing and native, and which is inherited?
2. **Why does it matter?** — TD03 is where the "no imposed ensemble" claim is cashed for matter. But the
   ensemble risk lives upstream in TD02's Boltzmann factor; if TD02 lands IMPORTED, TD03's `PV=Nk_BT`
   is CONVERGENCE, not NATIVE. TD03 must state this dependency openly and credit only the part it owns:
   the `1/3` from isotropy and the occlusion-momentum-flux mechanism. Downstream: TD04, TD05, TD08.
3. **How will we find out?** — Four gated phases. The **single-wall flux** (P1) — where the `1/3` must
   fall out of counting convergence-momentum over the lattice's three axes, with **no inserted geometric
   factor** — is the native core and runs first; the ideal-gas law (P2) only *folds in* TD02 and is
   therefore graded no higher than TD02's own occupation result.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers and real failure modes,
   including the anti-tautology firewall (F4) on the inherited equipartition.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), per phase, no repainting a fired test.

## Question

`PV = Nk_BT` is the canonical ideal-gas law, usually got from a kinetic-theory or partition-function
argument. The gap: derive it from Law III occlusion — the convergence-momentum flux a relay gas
deposits on a wall — with no imposed Boltzmann ensemble and no continuum velocity distribution assumed.

## The honest split (what TD03 owns vs what it inherits)

- **Native and owned by TD03:** pressure = one-sided occlusion momentum-flux (Law III), and the `1/3`
  as a *derived* readout of 3-D lattice isotropy (the same isotropy `⟨cos²θ⟩=1/3` that FD05 derives for
  the sound ceiling `c/√3`). This is the part that can earn A on its own merits.
- **Inherited from TD02 (NOT re-derived here):** the equipartition `½m⟨v²⟩=(3/2)k_BT`. If TD02's
  Boltzmann factor is IMPORTED (its firewall fires), then folding it into `PV=Nk_BT` makes the ideal-gas
  *number* CONVERGENCE, not NATIVE — TD03 must inherit that grade, not launder it. **Asserting `PV=Nk_BT`
  is "ensemble-free" while standing on an imported equipartition is the tautology to avoid (F4).**

## SDT mechanism & hypotheses

A gas particle is a hard solid vortex carrying a wake of disordered throughput. Pressure is not a
fluid abstraction: it is the **rate of convergence-momentum delivered to a boundary** as vortices
strike it and the wall occludes their incoming throughput (Law III, `F_occlusion`,
`solid_angle_occluded`). Temperature `k_BT` (from [[TD02]]) sets the mean disordered throughput per
DoF, hence the mean impact momentum.

- **H1 (pressure = occlusion momentum-flux — the native core):** `P = (1/3) n m ⟨v²⟩` arises because
  each wall element occludes the one-sided convergence-momentum current of the relay gas; the factor
  `1/3` is the three-axis isotropy of the lattice (`⟨cos²θ⟩=1/3`, the same isotropy FD05 derives for the
  `c/√3` sound ceiling), *derived* not assumed. **This `1/3` is the genuinely new content of TD03.**
- **H2 (ideal-gas law — inherits TD02, does not re-derive it):** substituting TD02's
  `½m⟨v²⟩ = (3/2)k_BT` gives `PV = Nk_BT` with `k_B` the only explicit input. **The "no ensemble"
  property of this step is borrowed from TD02, not established here** — if TD02's Boltzmann factor is
  IMPORTED, this number is CONVERGENCE, not NATIVE (see F4 firewall).
- **H3 (Dalton & limits):** partial pressures add because occlusion momentum-fluxes from distinct
  species superpose linearly; departures from ideality appear when vortex wakes overlap (finite-size /
  co-volume), recovering a van-der-Waals-shaped first correction natively (`b` ~ vortex-wake volume,
  order-unity, flagged).

## Strategy

1. **Single-wall flux *(the native core — runs first)*.** *Goal:* `P = ⅓ n m ⟨v²⟩` with the `1/3`
   *derived*. *Method:* count convergence-momentum delivered per tick to a boundary cell from a relay
   gas of tagged vortices; compute `⟨cos²θ⟩` over the lattice axes (and, if `lattice_structure.hpp` is
   available, over the actual CRN bond directions as FD05 does). *Success:* the `1/3` falls out of
   isotropy with **no inserted geometric factor**; report any CRN frustration residual as the lattice
   fingerprint, not as an error to absorb.
2. **Ideal-gas law *(inherits TD02)*.** *Goal:* `PV=Nk_BT`. *Method:* fold in TD02's equipartition
   `½m⟨v²⟩=(3/2)k_BT` — **tagging it as inherited**, not re-derived. *Success:* `PV/(Nk_BT) = 1.000 ±
   10⁻³` across a decade of `N` and `T`; `c_v = (3/2)k_B` recovered. **Grade ceiling = TD02's class:**
   if TD02 landed IMPORTED, this is CONVERGENCE here.
3. **Dalton & equation-of-state.** *Goal:* additivity + first non-ideal term. *Method:* mix two
   species; then crowd the box until wakes overlap. *Success:* `P_total = ΣP_i` to 1%; a positive
   co-volume correction `P(V−Nb)=Nk_BT` emerges with `b` ~ vortex-wake volume (flagged, order-unity).
4. **Input audit.** *Goal:* confirm derivation basis. *Method:* delete-test on `k_B`. *Success:* result is
   `k_B ×` pure number; no ensemble object, no `h`, no partition function `Z` anywhere in the chain.

## Success criteria

- **PASS (Class A):** the `1/3` derived from isotropy with no inserted factor (P1), **and** `PV=Nk_BT`
  closed *given a NATIVE TD02 equipartition*; only `k_B` dependency-traced; zero fitted parameters.
- **QUALIFIED (Class C):** P1 native, but `PV=Nk_BT` rests on a TD02 equipartition graded IMPORTED →
  the ideal-gas number is CONVERGENCE; or the non-ideal `b` coefficient is order-unity / flagged.
  *(Honest expected landing until TD02 clears its firewall.)*
- **PENDING (Class D):** pressure law numerically correct but the `1/3` needs a calibrated isotropy step.
- **FAIL (Class F):** the `1/3` cannot be obtained except by inserting it by hand (P1), **or**
  `PV=Nk_BT` is only reproducible by importing a Maxwell–Boltzmann ensemble directly into TD03.

## Falsification tests (each has a real failure mode + numeric trigger)

| # | Test | SDT prediction | If it fails (numeric trigger) |
|---|------|----------------|-------------------------------|
| T1 | **Native `1/3` from isotropy** | `P=⅓nm⟨v²⟩`; axis-average `⟨cos²θ⟩=1/3` exact | if `1/3` can only be matched by inserting a geometric factor, P1 is empty → **F** |
| T2 | Occlusion + TD02 → ideal gas | `PV/(Nk_BT)=1.000 ±0.1%` over a decade in `N,T` | if `> 0.1%` off after folding TD02, the occlusion-flux link is wrong |
| T3 | Wakes overlap → co-volume | positive `b` ~ wake volume; `P_total=ΣP_i` to 1% | if the first correction is the **wrong sign** (attractive-dominant at low density) or Dalton fails `>1%` |
| T4 | **Anti-tautology firewall (inherited)** | `PV=Nk_BT` graded ≤ TD02's equipartition class | if TD03 asserts "ensemble-free" while TD02's Boltzmann factor is IMPORTED → cap TD03 at **C** (CONVERGENCE), never A |

## Dependencies

**Upstream:** [[TD02]] (equipartition `½m⟨v²⟩=(3/2)k_BT` — **inherited, and its firewall class is
inherited**), Law III occlusion (`F_occlusion`, `solid_angle_occluded`),
`Engine/include/sdt/lattice_structure.hpp` (CRN bond directions for the discrete `⟨cos²θ⟩`, optional).
**Downstream:** TD04 (conduction in a relay gas), TD05 (gas↔condensed EoS), TD08 (Brownian kicks are
the same momentum-flux). **Related:** [[TD01]] (microstate counting), FD05 (the `c/√3` isotropy is the
*same* `⟨cos²θ⟩=1/3` used here), FD09 (drag as occlusion cross-section — same Law III momentum balance).
---

## Questions This Opens *(generative — log new ones in `TD03_VERDICT.md`)*

1. **Is the `1/3` exactly `1/3` in the real lattice?** If the frustrated CRN (FLM08) gives
   `⟨cos²θ⟩=1/3+δ`, then `P=⅓(1+3δ)nm⟨v²⟩` — a tiny native departure from the textbook ideal-gas
   pressure. Could a precision gas-thermometry residual ever bound `δ`?
2. **Does the co-volume `b` predict a real van-der-Waals constant?** If `b` is literally the vortex-wake
   exclusion volume, does feeding a measured molecular size reproduce a tabulated `b` for one gas
   without a fit — turning the first non-ideal term into a native prediction?
3. **Is the wall an occluder or a re-emitter?** A perfectly relaying wall vs a perfectly occluding wall
   give the same pressure but different momentum bookkeeping — does that distinction surface as the
   accommodation coefficient / thermal-creep effects, natively?
4. **Does the same occlusion-flux give radiation pressure `P=u/3`?** TD06's photon gas should give
   `P=u/3` from the *same* isotropy — is the matter `1/3` and the radiation `1/3` one statement, tying
   TD03 to FD05 and TD06 under a single `⟨cos²θ⟩`?

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — TD03
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: 0 in P1 (the b co-volume is order-unity/flagged, not fitted)
- Engine namespaces actually used: measured::k_B, law_III (F_occlusion, solid_angle_occluded),
    lattice_structure.hpp (optional, CRN bond directions), TD02 equipartition (INHERITED — class follows TD02)
- Phase thresholds (committed before run):
    P1 axis-average ⟨cos²θ⟩=1/3 exact, no inserted factor · P2 PV/(Nk_BT)=1.000 ±1e-3 over a decade in N,T
    P3 P_total=ΣP_i within 1%, b > 0 · P4 result = k_B × pure number (no Z, no h, no ensemble)
- Forbidden retroactive changes: insert the 1/3 by hand then claim native; launder an IMPORTED TD02
    equipartition into a "native PV=Nk_BT"; widen tolerances; plug b; IDENTITY-PASS; local constant namespaces
```

### Pivot table

| Trigger (numeric) | PIVOT (first) | If pivot fails | Forbidden |
|---|---|---|---|
| P1 axis-average ≠ 1/3 without an inserted factor | recompute the momentum bookkeeping over axes / CRN bonds | **F** — the `1/3` is not native | hand-insert the geometric factor |
| P1 discrete CRN `⟨cos²θ⟩` off 1/3 by the frustration residual | report it as the **lattice fingerprint** (Q1); keep the continuum 1/3 as the A-core | **OPEN** the frustration shift | average it silently back to 1/3 |
| P2 rests on a TD02 equipartition graded IMPORTED | grade TD03's ideal-gas number **CONVERGENCE** honestly | — | claim "ensemble-free PV=Nk_BT" anyway |
| P3 first non-ideal term has the wrong sign | check the wake-overlap geometry (attractive vs excluded-volume) | **OPEN** the EoS correction | flip the sign to match van der Waals |
| Rivals match but SDT only reproduces | label **DEGENERATE** honestly | — | Claim Class A |
| Upstream missing (TD02 not run) | **DEFER** P2/P3; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (lattice size, tick count, density sweep); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes for the `1/3` (axis-average vs direct momentum-flux integral vs CRN-bond average).

### Disallowed adjustments

- Inserting the `1/3` by hand and grading native · laundering an IMPORTED TD02 equipartition · importing
  a Maxwell–Boltzmann ensemble or partition function directly · post-hoc tolerance widening · coefficient
  plugs on `b` · `atomic::`/GM/G in the native chain.

---

*TD03 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

## B37 rank-4 measurement freeze (2026-08-14)

B37 remains a Class-D standing prediction; no comparison datum currently
exists. The machine-readable prediction must contain, for each sampled
direction `n`,

```text
M2(n) = mean_j[(b_j dot n)^2] = 1/3
M4(n) = mean_j[(b_j dot n)^4]
tetrahedral prediction: min(M4)=1/9, max(M4)=7/27
isotropic continuum: M4=1/5
```

Measurement protocol:

1. Build a four-channel mechanical, acoustic or optical relay analogue whose
   unit channel directions are independently surveyed to form a tetrahedral
   set. Record the measured direction vectors and covariance; do not force
   ideal coordinates in reduction.
2. Rotate a unit-amplitude drive over a spherical grid with at least 1,000
   directions. For each direction record the normalized second- and
   fourth-power channel response before any tetrahedral fit.
3. Validate the apparatus on an isotropic multi-channel control:
   `|M2-1/3|<0.005` and `|M4-1/5|<0.005` after uncertainty propagation.
4. The tetrahedral result supports the standing prediction only if the fitted
   extrema overlap `1/9` and `7/27` at `2 sigma`, the continuum value is
   excluded at both extrema, and the rank-2 response remains within `0.005` of
   `1/3`.
5. Report measured directions, raw channel responses, normalization, moments
   and uncertainties as CSV/JSON. A null result changes B37; absent data does
   not become a synthetic benchmark pass.
