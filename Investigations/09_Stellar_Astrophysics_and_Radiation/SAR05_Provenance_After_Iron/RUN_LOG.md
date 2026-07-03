# RUN_LOG — SAR05: Provenance After Iron

> Executed per `PROMPT_EXECUTION_PROTOCOL.md`. Append-only during the run.
> Author of run: automated execution of `PROMPT.md` (SPEC by J. C. Harvey, Melbourne).

---

## Pre-Run Commitments — SAR05  (filled BEFORE coding)

- **Prompt completion target:** A (all four phases gated, all §6 outputs written)
- **Physics class hoped:** CONVERGENCE on ledger + seeding arithmetic; after-iron fork
  NATIVE **only if** a real observable separates self-consuming from pressure-fed, else
  **DEGENERATE** (declared, not faked). Honest expectation up front: Class C ceiling.
- **CALIBRATED budget: 0.** No fitted parameters. The numbers `~3e46 J`, `z≈99`, `273 K`,
  `Yₑ=0.4`, `Yₑ≈0.1` are `OBSERVED-TARGET` / `DERIVED` only — never fits.
- **Engine namespaces used:** `sdt::cosmology` (`z_at_T`, `T_at_z`, `wien_peak`,
  `z_freezing`, `z_room_temp`, `z_boiling`), `sdt::laws::measured` (`T_CMB`, `MeV_to_J`, `c`).

### FROZEN DECAY/FORMATION BOUNDARY  (binding contract, written BEFORE P2)

> **RULE (one line):** A claim is *decay-time external* **only if** no local
> formation-time battery can charge the bank; **otherwise it is formation-time local.**
> Equivalently: examined at the instant it is *spent*, does the supply require a live
> wire from beyond the CMB, or was the surplus (wind / seat / ΔR / pressure support)
> already banked when the object *formed*? If a local formation-time battery balances
> the energy and the sign, the claim is **formation-time local** — full stop.

| Row | Side of the cut | Local formation-time battery |
|-----|-----------------|------------------------------|
| **Neutron** | formation-time local | Liberation event (fission / spallation / photodisintegration / r-process / cosmic-ray strike); the **1.83c seat is spun up at liberation** (NP20), carried to decay. |
| **Star-burn** | split-after-iron | Below-Fe: exothermic fusion surplus (banked in the light nuclei). Above-Fe: **directed spation pressure** (gravity as `g=v²/R`) pays the endothermic captures — a *local* pressure battery, not a beyond-CMB wire. |
| **Heavy elements** | local-finite | The **kinetic plunge** of a single GW170817-type merger; the abundance **cliff** (heavies trace, tied to rare violent events) *requires* finite local injection. |
| **Neutronisation** | PRESSURE-runaway (NP19 cut) | **Gravity (directed spation pressure)** pays; electron-degeneracy support evaporating (the "run on the banks"); ~99% vents as neutrinos through the EC valve. Nova recurrence ∝ accretion rate confirms a local battery. |
| **cosmological residue** | THE ONLY SURVIVOR permitted to remain external | Whatever set the initial pressure gradient at **z≈99** (T_CMB·(1+z)=273 K). A *different* question from refuel-at-decay; an early-epoch boundary condition, spent at no decay/burn event. |

### Phase thresholds (committed before run)

- **P1:** 4 rows, each ONE tag, local battery named; boundary frozen above; **0** rows left
  "beyond-CMB at decay" (any un-nameable battery → §8 T1 RE-OPEN, not a pass).
- **P2:** a *signed* `L_ν(Ṁ)` slope (or cliff-vs-supply) difference committed **BEFORE** the
  estimate; else **DEGENERATE** declared.
- **P3:** `|z_at_T(273.15) − 99| < 1` **AND** `|T_at_z(99) − 273.15| < 3 K`, both from
  `cosmology.hpp` symbols (no literal 99/273 as *input*).
- **P4:** `(antineutrinos)/(baryons) = 2/5` EXACT (integer); `Yₑ=0.4` → first peak (A≈80)
  not gold; gold needs `Yₑ≈0.1`; "β⁻ on every rung" overcount withdrawn.

### Forbidden retroactive changes

Widen tolerances/fork-precision post-run; fake a fork separation; tag a row SURRENDERED
when no local battery exists (must RE-OPEN); hardcode 99/273 as *input*; import
G/M/GM / stored gravitational potential / ΛCDM / ψ / quarks / the SM nucleosynthesis
network as truth into the chain; write "charge radius".

---

## P2 PRE-COMMITMENT (signed, BEFORE any estimate)

> Committed direction of the separating observable, written before the number is computed:
>
> **Self-consuming:** the endothermic post-iron captures are paid out of the star's *own
> fixed, finite* internal structure-budget set at formation. Its neutrino output is capped
> by that reservoir → `L_ν` is **independent of accretion rate** `Ṁ` (slope `dL_ν/dṀ ≈ 0`),
> and the heavy-element yield shows a **hard cliff** at a fixed total mass regardless of
> how long fuel is supplied.
>
> **Pressure-fed:** the endothermic captures are paid by *directed spation pressure*
> throughput, which is charged by the local accretion stream → `L_ν` **scales with `Ṁ`**
> (slope `dL_ν/dṀ > 0`, monotone increasing), and the heavy-element yield **tracks supply
> duration** (yield ∝ ∫Ṁ dt), no hard cliff until the supply stops.
>
> **Separating observable (committed):** the sign of `dL_ν/dṀ` across a population of
> events at fixed core mass — flat (self-consuming) vs rising (pressure-fed) — and,
> equivalently, cliff-height-fixed vs yield-tracks-supply.
>
> **Degeneracy guard (committed):** IF both pictures, at the collapse of a single event,
> vent the *same* ~3×10⁴⁶ J on the *same* ~seconds timescale — because the pressure battery
> and the internal budget are the *same gravitational binding energy read through two cuts*
> (NP19) — THEN for a **single event** the two are observationally identical and the fork is
> **DEGENERATE**; it only becomes LIVE if a *population* `L_ν(Ṁ)` slope is measurable. This
> guard is committed *before* the estimate so the DEGENERATE call cannot be dodged.

---

## Execution log

### ADJ-001 — Tool language: C++ → Python  (2026-06-30)

- **Trigger:** MSVC `cl` is not on PATH in this environment (no VS dev shell); `g++`
  absent. Building `sar05_provenance.cpp` with `#include <sdt/laws.hpp>` is not possible
  here. The SPEC §6.2 explicitly permits `sar05_provenance.cpp` **or** `sar05_provenance.py`,
  and the task grant says "python3 fine".
- **Committed response (allowed by §⑩ "filename fix `.cpp`↔`.py` via ADJ entry"):** ship
  `sar05_provenance.py`.
- **Single-source-of-truth discipline preserved:** the tool does **not** invent a literal
  T_CMB or hardcode 99/273 as input. It sources `T_CMB = 2.7255` *verbatim* from
  `Engine/include/sdt/laws.hpp:169` and reproduces `T_at_z`, `z_at_T`, `wien_peak`
  **exactly** as written in `Engine/include/sdt/cosmology.hpp:185–196`. Line references are
  printed in the tool header so drift against the engine is auditable. 99 and 273.15 appear
  ONLY as `OBSERVED-TARGET` comparison columns, never as inputs.
- **What did NOT change:** no fitted numbers; the P3 thresholds unchanged; the 2/5 integer
  assertion unchanged; the after-iron estimate unchanged.

### P3 pre-check (arithmetic, from engine symbols)

- `z_at_T(273.15) = 273.15/2.7255 − 1 = 99.2201…`  →  `|z − 99| = 0.220 < 1`  **PASS**
- `T_at_z(99) = 2.7255·100 = 272.55 K`  →  `|T − 273.15| = 0.600 < 3 K`  **PASS**
- round-trip `z_at_T(T_at_z(99)) = 99.000…`  **clean**
- **Gate P3: PASS-GATE** (numbers reproduced by the tool below).

### Phase gates

- **P1 — PASS-GATE.** Four rows tagged, each with exactly one tag and a named local
  formation-time battery; decay/formation boundary frozen above BEFORE P2. Zero rows left
  "beyond-CMB at decay". See `SAR05_PROVENANCE_LEDGER.md`.
- **P2 — PASS-GATE (fork resolved), physics = SPLIT.** Separating observable committed
  before estimate. Result: for a **single event** the two pictures are DEGENERATE (same
  ~3e46 J / same timescale — NP19 one-energy-two-cuts). Across a **population at fixed core
  mass** the committed `sign(dL_ν/dṀ)` separates them (flat vs rising) → LIVE / NATIVE-eligible
  *at population level*. Both stated honestly; no difference invented for the single-event case.
- **P3 — PASS-GATE.** Thresholds met from engine symbols (above); tool prints the z↔T table
  and the PASS line. Cosmological residue isolated as the sole survivor.
- **P4 — PASS-GATE.** `(ν̄)/(baryons) = 2/5` asserted EXACT (integer); `Yₑ=0.4` → first
  r-process peak (A≈80), NOT gold; gold needs `Yₑ≈0.1`; "β⁻ on every rung" overcount
  withdrawn (climb is silent (n,γ)).

### Result capture

- `sar05_results.txt` — stdout of `sar05_provenance.py` (z↔T table, 2/5 check, after-iron
  estimate). All assertions passed; tool exit 0.
