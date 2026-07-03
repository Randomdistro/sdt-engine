# SAR05 — VERDICT: Provenance After Iron

> **Author of run:** automated execution of `PROMPT.md` (SPEC by J. C. Harvey, Melbourne).
> **Run artefacts:** `RUN_LOG.md`, `sar05_provenance.py`, `sar05_results.txt`,
> `SAR05_PROVENANCE_LEDGER.md`.

---

## Dual verdict header

| Axis | Grade | One-line justification |
|------|-------|------------------------|
| **Prompt completion** | **A** | All four phases gated and PASSed; all §6 outputs written (ledger, tool, verdict, run-log, results). |
| **Physics class** | **CONVERGENCE (Class C)** on the ledger + seeding arithmetic; the after-iron fork is **DEGENERATE for a single event**, **LIVE / NATIVE-eligible only at the population level** (committed `sign(dL_ν/dṀ)` slope). Declared exactly, not faked. |

**Honest expectation (stated up front, met):** the ledger and the seeding arithmetic land
CONVERGENCE — an audited reframe, not a new number. The fork does **not** yield a clean
single-event NATIVE separation; it becomes NATIVE-eligible only across a population, and that
is reported as such rather than dressed up as a single-event win.

---

## Phase-by-phase result

| Phase | Committed threshold | Actual | Decision |
|-------|---------------------|--------|----------|
| **P1** ledger | 4 rows, 1 tag each, local battery named; boundary frozen; 0 rows beyond-CMB-at-decay | 4 rows tagged (SURRENDERED / split-after-iron / local-finite / PRESSURE-runaway) + isolated cosmological residue; boundary frozen in `RUN_LOG.md` before P2; 0 rows re-opened | **PASS-GATE** |
| **P2** fork | signed `L_ν(Ṁ)` slope committed BEFORE estimate, else DEGENERATE declared | slope committed before estimate; single-event **DEGENERATE** (NP19 one-energy-two-cuts), population-slope **LIVE**; both stated | **PASS-GATE** (fork resolved) |
| **P3** z↔T | `\|z_at_T(273.15)−99\|<1` AND `\|T_at_z(99)−273.15\|<3 K` from engine | 99.22 (\|Δ\|=0.22) and 272.55 K (\|Δ\|=0.60 K); round-trip clean | **PASS-GATE** |
| **P4** 2/5 | `(ν̄)/(baryons)=2/5` exact; Yₑ=0.4→first peak; overcount withdrawn | 2/5 asserted exact (integer); Yₑ=0.4→A≈80 not gold; gold needs Yₑ≈0.1; "β⁻ on every rung" withdrawn | **PASS-GATE** |

---

## Falsification table (§8, filled)

| Test | Hypothesis | Outcome | Result |
|------|-----------|---------|--------|
| **T1** (no at-decay feed) | Every beyond-CMB claim resolves to a LOCAL formation-time battery | Each of 4 rows names a local battery; energy/sign balances with no external at-decay wire | **PASS** (no row re-opened) |
| **T2** (after-iron fork) | Self-consuming vs pressure-fed differ observably after iron | **Single event: DEGENERATE** (same ~3e46 J / same timescale — NP19). **Population at fixed core mass: LIVE** via `sign(dL_ν/dṀ)` | **HONEST SPLIT** — DEGENERATE declared where it is degenerate; LIVE where a real observable exists. No difference invented. |
| **T3** (z≈99 arithmetic) | Sky at 273 K at z≈99, engine-sourced | `z_at_T(273.15)=99.22`, `T_at_z(99)=272.55 K`, both from `cosmology.hpp`/`T_CMB` | **PASS** |
| **T4** (2/5 seeding) | 5 baryons→2 ν̄ exact; Yₑ=0.4→first peak not gold | integer `2/5` exact; Yₑ=0.4→A≈80; gold needs Yₑ≈0.1; overcount withdrawn | **PASS** |
| **T5** (no SM-story smuggle) | No SM nucleosynthesis network / ΛCDM / G / stored potential in the chain | Anchors are numbers/events only (iron peak, GW170817 cliff, nova recurrence ∝ Ṁ, ~99% ν vent, ~3e46 J); gravity via directed spation pressure; no G/M/GM; no "charge radius" | **PASS** |

No RETRO-PASS, PLUG, IDENTITY-PASS, or BORROW-SMUGGLE was used.

---

## Explicit class call

- **Ledger (P1) + seeding arithmetic (P3, P4): Class C — CONVERGENCE.** An audited reframe:
  beyond-CMB-at-decay dissolved into named local formation-time batteries, one cosmological
  residue at z≈99 isolated. The seeding ratio is an exact integer identity (2/5) — a
  structural fact, not a fit.
- **After-iron fork (P2): DEGENERATE at single-event scale; NATIVE-eligible at population
  scale.** The single-event degeneracy is *structural* — it follows directly from NP19
  (pressure battery and internal budget are one gravitational binding energy read through two
  cuts). It is not a measurement-precision accident; it is a genuine identity for a single
  event, and is reported as DEGENERATE. The population-level `L_ν(Ṁ)` slope is the honest
  route to a live separation, committed before the estimate.

**Stack status suggestion:** RESOLVED (Prompt completion A, physics CONVERGENCE on the
keystone; fork honestly DEGENERATE/LIVE-split). The provenance question is closed for the
sibling set with the standing caveat that any sibling invoking "beyond-CMB at decay" must
re-open a SAR05 row.

---

## STRESS-TEST SELF-AUDIT

**(1) Independent, or identity/circular?**
- **z↔T (P3):** an *identity* by construction — `T=T_CMB(1+z)` is a one-line definition, and
  `z≈99↔273 K` is arithmetic on the measured `T_CMB=2.7255`. It is reported as such
  (DERIVED-from-`T_CMB`), **not** as a mechanism win. Not circular: 99 and 273.15 enter only
  as comparison columns; they *emerge* from `T_CMB`, they are not inputs.
- **2/5 (P4):** an *integer identity* from the grammar (deuteron 2b/1ν̄ + triton 3b/1ν̄). It
  is a counting fact, independent of any fit — genuinely non-circular, but also not a
  "prediction" beyond the grammar it restates. Labelled CONVERGENCE, correctly.
- **After-iron fork (P2):** the honest finding is that self-consuming and pressure-fed are
  the **same energy through two NP19 cuts** for a single event → **identity ⇒ DEGENERATE**,
  declared. The only genuinely *independent* discriminator is a population `L_ν(Ṁ)` slope,
  and it is flagged as the (as-yet-unmeasured) live route, not claimed as a result. No fake
  separation.

**(2) Fished?**
No. Zero fitted parameters (CALIBRATED budget 0, honoured). `~3e46 J`, `z≈99`, `273 K`,
`Yₑ=0.4`, `Yₑ≈0.1` are OBSERVED-TARGET / DERIVED, never tuned. The `~3 s` collapse timescale
is an explicit ASSUMED order-of-magnitude used only to sanity-check `L_ν`'s magnitude — it
does not enter any pass/fail gate and no threshold was moved to accommodate it. The tool has
no optimiser.

**(3) Dimensions.**
- `z` dimensionless; `T=T_CMB(1+z)` [K]; `wien_peak` [m] (printed nm). Round-trip clean.
- `2/5` dimensionless (count/count); `Yₑ` dimensionless. Consistent.
- `L_ν = E/t` = [J]/[s] = [W]. `~3e46 J / 3 s = 1e46 W` ✓. `dL_ν/dṀ` has units [W/(kg s⁻¹)];
  only its **sign** is used (flat vs rising), so no unit-mixing enters the discriminator.
- No G/M/GM, no stored gravitational potential, no borrowed magneton/QM units anywhere.

**(4) Honest class + what is owed.**
- **Class:** Prompt completion **A**; physics **CONVERGENCE (C)** on ledger + seeding;
  after-iron fork **DEGENERATE (single event) / LIVE-eligible (population)**.
- **Owed / caveats (declared, not hidden):**
  1. The tool is **Python**, not the C++ engine build (no `cl`/`g++` in this environment;
     ADJ-001). Single-source-of-truth is preserved by sourcing `T_CMB` verbatim from
     `laws.hpp:169` and reproducing `T_at_z`/`z_at_T`/`wien_peak` verbatim from
     `cosmology.hpp:185–196`, with line references printed. It is **owed** a recompile of
     the C++ sibling in a VS dev shell to confirm bit-identical output — but the arithmetic
     is a one-line definition, so drift risk is negligible.
  2. The after-iron fork's NATIVE route is **owed a real population `L_ν(Ṁ)` measurement**;
     until then only the single-event DEGENERATE call stands as settled. The prompt's own
     expectation (Class C ceiling, fork DEGENERATE-unless-separable) is met exactly.
  3. Row 2 (star-burn, above-Fe) leans on "directed spation pressure pays" as the local
     battery. This is consistent with the whitelist (gravity as `g=v²/R`, no stored
     potential), and it balances the sign via the NP19 cut — but the *mechanism* by which
     directed pressure funds a specific endothermic capture rate is asserted at the ledger
     level, not derived here. That derivation is **owed** to NP21/NP19 downstream, not to
     SAR05 (which only classifies).
- **What is NOT owed:** no beyond-CMB **at-decay** feed is required anywhere — T1 passes.
  The cosmological residue at z≈99 is the sole legitimate external question, and it is
  isolated cleanly.
