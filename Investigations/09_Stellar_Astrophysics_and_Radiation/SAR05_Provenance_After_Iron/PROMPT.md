# SAR05: Provenance After Iron — self-consuming vs pressure-fed — Investigation Prompt

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — For every place the framework *reached* for "fed from beyond the CMB," does the source actually resolve to a **LOCAL, finite, formation-time** battery (fission / spallation / photodisintegration / r-process / cosmic rays / accretion / gravity-as-directed-pressure) — and is there a **single decisive, measurable fork after iron** (self-consuming vs pressure-fed) that the two pictures predict differently, so that beyond-CMB-at-decay is required *nowhere* in the forge or the decay, surviving **only** as a distinct cosmological-provenance question (what set the gradient at z≈99, when T_CMB·(1+z) = 273 K = the freezing point of water)?
2. **Why does it matter?** — This is the **honesty keystone** of the whole nuclear/stellar set. The framework has repeatedly been saved from overreach by re-localising an apparent beyond-CMB supply into a finite local event; SAR05 *formalises that move into a ledger and tests it*. If it holds, "beyond the CMB" stops being a free reservoir invoked on demand and becomes one well-posed cosmological question, cleanly separated from "refuel at the moment of decay." It closes the provenance question for the sibling set (NP18–NP21, PPT10/PPT11, FLM11, APS06). Stack position: Tier 4 (consumes NP21's iron floor; consumes NP19's Two-Ledger Lemma).
3. **How will we find out?** — Four gated phases (§④): (P1) **build and classify** the provenance ledger — every reached-for beyond-CMB claim tagged SURRENDERED-to-formation / split-after-iron / local-finite / cosmological-residue, with the **decay-time vs formation-time boundary pre-committed before any number**; (P2) the **decisive after-iron fork** — quantify a measurable difference between self-consuming and pressure-fed (neutrino luminosity vs accretion-rate scaling, s-/r-process endothermic continuation, nova recurrence vs accretion) and pre-commit the separating observable; (P3) verify the **z≈99 → 273 K** arithmetic from `cosmology.hpp` and isolate the cosmological residue as the *only* surviving beyond-CMB question, distinct from decay-time; (P4) the **2/5 seeding ratio** — confirm 5 baryons → 2 antineutrinos exact, Yₑ=0.4 makes the first r-process peak (not gold), and the climb to gold is mostly silent (n,γ).
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers: a beyond-CMB **at-decay** feed actually **REQUIRED** somewhere (energy/sign won't balance from a local battery) → the surrender was premature, **re-open**; self-consuming and pressure-fed turn out **observationally identical** after iron → the fork is **DEGENERATE** (say so, do not fake a win); the z≈99 arithmetic is **wrong** → fix it (it must come from `cosmology.hpp`, not a literal); the 2/5 ratio is **not** exact, or Yₑ=0.4 is claimed to make gold → withdraw the overcount.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). **Honest expectation, stated up front:** this is mostly an **audited reframe + one falsifiable fork**, so the realistic ceiling is **Class C (Convergence)** on the ledger and the seeding arithmetic, with the after-iron fork landing **NATIVE** only if a real observable separates the two pictures — otherwise **DEGENERATE**, declared.

---

## 1. Executive Summary (100–150 words)

Standard physics tells a clean local story — heavies forged in supernovae and mergers, neutrons liberated by nuclear events — yet SDT prose has at times *reached* for "fed from beyond the CMB" to power a star, a neutron, or the heavy elements. **SAR05 formalises a PROVENANCE LEDGER and tests it: every reached-for beyond-CMB supply is classified and shown to resolve to a LOCAL, FINITE, FORMATION-TIME battery — never a refuel at the moment of decay.** The neutron arrives already wound (NP20's 1.83c seat is spun up at formation); the star's books open only at the iron floor (NP21), where self-consuming and pressure-fed *split* — a measurable fork; GW170817's abundance cliff *requires* finite local injection. Beyond-CMB survives **only** as cosmological provenance — what set the gradient at z≈99, where T_CMB·(1+z)=273 K. Expected: an audited reframe (Class C) plus one falsifiable after-iron fork.

## 2. Physical Context (250–400 words)

**Plain-language picture.** Picture a bank. A "battery" is an account that holds movement put in earlier; "beyond the CMB" would be an *external, bottomless* wire feeding that account live. The framework has occasionally talked as if such a wire is plugged in *at the moment something happens* — a neutron decays, a star burns, gold is made. SAR05 walks each of those moments back to where the account was actually **charged**, and finds it was charged **earlier and locally** — at the *formation* of the object (a fission event, a spallation strike, a merger's kinetic plunge, an accretion stream), not refilled live from outside. The neutron is always a **liberation product**: it was spun up to its seat when it was knocked loose, and it carries that wind to its decay (cross-ref **NP20**: the 1.83c seat is set at formation, not at decay).

**The one place the books genuinely change.** At the **iron floor** (NP21), fusion stops being exothermic. *Below* iron, build-up releases movement; *at and beyond* iron, neutron capture (s-/r-process) is **endothermic** and continues only while a local supply pays. This is the seam where two pictures — **self-consuming** (the star eats its own structure) and **pressure-fed** (directed spation pressure / gravity pays) — make **different, measurable** predictions. That seam is the heart of the investigation.

**Key variables / symbols (define once, carry through):**
| Symbol | Meaning | Dimension |
|--------|---------|-----------|
| `z` | redshift = `T/T_CMB − 1` (`cosmology::z_at_T`) | dimensionless |
| `T(z)` | sky temperature `T_CMB·(1+z)` (`cosmology::T_at_z`) | K (OBSERVED-anchor) |
| `Yₑ` | electron fraction = protons / baryons in the ejecta | dimensionless |
| `ΔR` | form-resistance difference (NP19 unit of account) | J (MeV) |
| `L_ν` | neutrino luminosity of a core-collapse / EC event | W (≈99% channel) |
| `Ṁ` | accretion rate onto a nova / collapsing core | kg s⁻¹ |
| `∂(sys)` | the accounting boundary (NP19 cut: reaction-level vs event-level) | — |

**Connection to the rest of SDT.** Upstream: **NP21** (iron floor — the seam), **NP19** (Two-Ledger Lemma — endothermic-reaction vs exothermic-event is a *boundary cut*), **NP02B/NP07** (grammar growth, r-process seeding), `cosmology.hpp` (`z_at_T`, `T_at_z`, `wien_peak`, `z_freezing`). Downstream: SAR05 **closes the provenance question** for the whole 9-investigation set. Sibling **FLM11** supplies the tape-measure caution: which battery you "see" depends on where you put the meter — do not let a formation-time charge masquerade as a decay-time feed.

## 3. Theoretical Framework (400–600 words)

**derivation basis inputs only.** `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in their measured units. The measured **anchors** (facts, not the SM story) used here: fusion stops being exothermic at the iron peak (NP21); GW170817's kilonova = r-process heavies forged in a **single, local, finite** merger; nova recurrence tracks accretion rate; core-collapse vents ~99% of its budget as neutrinos (~3×10⁴⁶ J, the NP19 event-scale figure, `OBSERVED-TARGET`); the **abundance cliff** — heavies are *trace*, tied to *rare violent events*. **We import the numbers as anchors; we do NOT import the standard-model account** (no nucleosynthesis "network code as truth," no ΛCDM expansion history, no quarks/gluons, no W-boson weak vertex, no virtual particles as objects, no wavefunctions, no fields-as-primitives). **No G, no M, no GM** — gravity is the **PRESSURE of space directed by light influx** (`g = v²/R`, `ϟ = v²R/c²`); there is **NO stored gravitational POTENTIAL reservoir to spend**.

**The provenance axiom (the claim under test).**
> *Every apparent "fed from beyond the CMB" supply, examined at the moment it is spent, resolves to a battery that was charged LOCALLY at the FORMATION of the object — not refuelled live at the moment of decay/burn. The only beyond-CMB supply that survives is the COSMOLOGICAL one: whatever set the initial pressure gradient in the early, hot, dense epoch.*

This is the **path-of-least-resistance** principle (NP19) applied to provenance: a transformation runs because the *form-resistance difference* `ΔR` already existed — the surplus was banked at formation, not wired in at the event.

**The decay-time vs formation-time boundary (pre-commit before any number).** Two distinct questions, kept rigorously separate:
- **Decay-time provenance** — "what pays *at the instant* of decay/burn?" Claim: **nothing external**; the wind/seat/`ΔR` was set at formation. (Neutron: NP20 1.83c seat at liberation.)
- **Cosmological provenance** — "what set the initial gradient?" Claim: a **legitimate, different** question, answered (if at all) in the early epoch — *not* a refuel at decay.
Conflating these two is precisely the overreach SAR05 exists to prevent.

**The Two-Ledger tie (NP19).** Neutronisation `p + e⁻ → n + νₑ` reads **endothermic** as an *isolated arrow* (+1.293 MeV) yet **exothermic** at *event scale* (the EC valve through which ~3×10⁴⁶ J of gravitational binding vents as neutrinos). **Same physics, opposite sign — the sign is a property of the cut `∂(sys)`, not of the medium.** The "neutronisation runaway powered by the gradient" is therefore a **PRESSURE runaway** (electron-degeneracy support evaporating — the "run on the banks"), **not an energy runaway**: directed spation pressure (gravity) pays, venting ~99% as neutrinos through the EC valve. Nova recurrence tracking accretion rate confirms a **local** battery.

**The cosmological residue (the one survivor).** Using only `T(z) = T_CMB·(1+z)`: the epoch where the sky sat at the **freezing point of water (273 K)** is `z = 273.15/T_CMB − 1 ≈ 99` (`cosmology::z_freezing`, already in the engine). That deepest regress — *what set the initial pressure gradient at z≈99* — is **cosmological provenance**: legitimate, but a *different* question from "refuel at the moment of decay." Keeping them separate is what lets the framework stay consistent.

**Constraints / prohibitions.** Inputs limited to the derivation basis + measured anchors. **Prohibited:** G/M/GM as fundamentals or a stored gravitational potential reservoir; wavefunctions; fields-as-primitives; quarks/gluons; virtual particles as objects; dark matter/energy; ΛCDM expansion; wave-particle duality; importing the SM nucleosynthesis *story* (anchors are the *numbers/events*, not the model). Never write "charge radius"; charge is **handed redirection** (`e` = unit-bridge).

## 4. Investigation Strategy (800–1200 words — be excessive)

This investigation is **mostly discipline, with one sharp falsifiable fork**. The tool exists to make the provenance ledger *mechanical*, the after-iron fork *quantitative*, the z↔T arithmetic *engine-sourced*, and the 2/5 seeding ratio *exact* — and, above all, to keep the **decay-time vs formation-time boundary loud and frozen**. Four gated phases. The pre-commitment that matters most is in **P1**: *the boundary between decay-time and formation-time provenance is declared and frozen before P2 runs.*

---

### Phase 1 — Build the provenance ledger; classify each claim; freeze the decay/formation boundary (2–3 h)

**Goal.** Enumerate every place the framework has reached for "fed from beyond the CMB," and **classify** each into exactly one of four tags, *before* any after-iron number is computed. Produce the **frozen contract** the rest of the investigation is judged against: which claims are decay-time (must resolve locally) vs cosmological (legitimately external).

**Method.**
1. Tabulate the four canonical rows, each as `{claim reached-for | where it ACTUALLY resolves | tag}`:
   - **"Neutron fed from beyond the CMB AT DECAY"** → tag **SURRENDERED-to-formation**: the battery is charged at FORMATION (fission, spallation, photodisintegration, r-process, cosmic rays). The neutron is always a **liberation product**, arriving already wound (cross-ref **NP20**: 1.83c seat spun up at formation, not at decay).
   - **"Star burns because crushed from beyond the CMB"** → tag **split-after-iron**: the books are open only at the **iron peak** (NP21 floor). Fusion stops being exothermic at Fe; neutron capture (s-/r-process) is **endothermic** and continues. The two pictures — self-consuming vs pressure-fed — **SPLIT AFTER IRON** (decisive, falsifiable; → P2).
   - **"Heavy elements cooked by a standing gradient"** → tag **local-finite**: GW170817 shows heavies forged in a **SINGLE, LOCAL, FINITE** event; the **kinetic** plunge of the merger is the forge. The abundance **CLIFF** (heavies trace, tied to rare violent events) **REQUIRES** finite local injection, not a smooth standing supply.
   - **"Neutronisation runaway powered by the gradient"** → tag **PRESSURE-runaway (local, NP19 cut)**: the EC cascade ("run on the banks" = electron-degeneracy support evaporating) is a **PRESSURE** runaway, not an energy runaway; **gravity (directed spation pressure) pays**, venting ~99% as neutrinos through the EC valve. Nova recurrence ∝ accretion rate confirms a local battery.
2. **DECLARE, in `RUN_LOG.md`, before P2:** the **decay-time / formation-time boundary** — a one-line rule stating that a claim is *decay-time external* only if no local formation-time battery can supply the bank; otherwise it is *formation-time local*. State for each row which side of the cut it falls on. Pre-commit that the **only** row permitted to remain *external* is the cosmological residue (P3).
3. Tie the two-ledger structure to **NP19's Two-Ledger Lemma**: reaction-level endothermic vs event-level exothermic is a **boundary cut**, not two energies. State the cut explicitly for the neutronisation row.

**Pre-committed success metric.** Four rows, **each carrying exactly one tag**, with a one-line resolution and the local battery named; the decay/formation boundary written and frozen in `RUN_LOG.md`; **zero** rows left as "beyond-CMB at decay" except where P1 explicitly cannot name a local battery (which then becomes a §⑧ T1 re-open trigger, not a pass).

**Failure trigger.** Any row where **no** local formation-time battery can be named *and* a beyond-CMB *at-decay* feed is genuinely required to balance → **the surrender was premature**; flag for §⑧ T1 (re-open), do **not** tag it SURRENDERED to make the ledger look clean.

**Gate.** No P2 until all four rows are tagged and the boundary is frozen in `RUN_LOG.md`.
**Out of scope.** Quantifying the after-iron fork (P2); the z↔T arithmetic (P3); the 2/5 ratio (P4).

---

### Phase 2 — The decisive after-iron FORK: self-consuming vs pressure-fed (3–4 h)

**Goal.** Make the split tagged in P1 **quantitative and falsifiable**: identify and estimate a **measurable** difference between the self-consuming and pressure-fed pictures *after iron*, and **pre-commit the observable that separates them**.

**Method.**
1. State the two pictures as scaling laws with *distinct* observable signatures (pre-commit which observable, and the predicted direction, **before** computing):
   - **(a) Neutrino luminosity vs accretion-rate scaling.** Self-consuming: the energy to drive endothermic captures comes from the star's *own* structure, so `L_ν` tracks the *internal* binding budget (a fixed, finite reservoir set at formation). Pressure-fed: `L_ν` tracks the *directed-pressure* throughput, scaling with the **accretion rate** `Ṁ` (the local battery being charged). Pre-commit: do the two predict different `L_ν(Ṁ)` slopes? State the slope each predicts.
   - **(b) The s-/r-process endothermic continuation.** After iron, captures are endothermic. Self-consuming caps total heavy yield at the internal budget (a **cliff** at a fixed mass); pressure-fed continues while the local supply lasts (yield ∝ supply duration). Pre-commit: which observable abundance feature (cliff height vs supply-tracking) distinguishes them.
   - **(c) Nova recurrence vs accretion.** Recurrence interval ∝ time to accumulate the local battery ⇒ ∝ `1/Ṁ`. This is a **local-battery** signature; pre-commit it as a *consistency check* (it must come out local under both pictures, and it does — confirming the battery is charged locally either way).
2. Estimate the separation: using derivation basis constants and measured anchors, compute order-of-magnitude `L_ν` for a representative core-collapse event (~3×10⁴⁶ J over the collapse timescale, `OBSERVED-TARGET`) and compare the *scaling* the two pictures predict. The number need not be precise; the **separating direction** must be stated and committed.
3. **Pre-commit the verdict map:** if the two pictures predict observably different `L_ν(Ṁ)` (or cliff-vs-supply) at a stated, achievable measurement precision → the fork is **LIVE / NATIVE-eligible**. If they predict the *same* signature within any plausible precision → the fork is **DEGENERATE** — *declare it*, do not invent a difference.

**Pre-committed success metric.** A written, signed scaling difference for at least observable (a) **or** (b), with the predicted direction committed *before* the estimate; the nova-recurrence check (c) confirming a local battery; an explicit DEGENERATE call if no observable separates them.

**Failure trigger.** Self-consuming and pressure-fed give **identical** observable signatures at all plausible precisions → **DEGENERATE** (§⑧ T2); say so plainly, do **not** retro-construct a difference. If the *estimate* needs a beyond-CMB at-decay feed to balance → that is a §⑧ T1 re-open, not a pass.

**Gate.** No P3 until the fork is either committed LIVE (with the separating observable named) or declared DEGENERATE with reasoning.
**Out of scope.** A full nucleosynthesis network (anchors only); deriving the ~3×10⁴⁶ J figure (it is `OBSERVED-TARGET`).

---

### Phase 3 — The z≈99 → 273 K arithmetic; isolate the cosmological residue (1–2 h)

**Goal.** Verify, **from `cosmology.hpp` (not a literal)**, that the sky sat at the freezing point of water (273 K) at z≈99, and establish this **cosmological provenance** as the **ONLY** surviving beyond-CMB question — rigorously distinct from decay-time provenance.

**Method.**
1. Using `cosmology::z_at_T(273.15)` confirm `z ≈ 99` (the engine already exposes `z_freezing = z_at_T(273.15) ≈ 99.2`); using `cosmology::T_at_z(99)` confirm `T ≈ 273 K`. Print both directions; tag `DERIVED` (from `T_CMB` derivation basis input) — **never** hardcode 99 or 273.
2. Print a small z↔T table (z = 0, 10, 99, 107, 136, 1100) with `T_at_z` and `wien_peak`, anchoring the freezing (273 K, z≈99), room-temperature (293 K, z≈107), and boiling (373 K, z≈136) epochs already named in `cosmology.hpp` — as a *sanity ladder*, not a claim about water existing then.
3. State, in one paragraph, that the cosmological residue — *what set the initial pressure gradient at z≈99* — is the **single** beyond-CMB question that survives P1–P2, and that it is **categorically different** from "refuel at the moment of decay." Pre-commit: this residue is **not** spent at any decay/burn event; it is an early-epoch boundary condition.

**Pre-committed success metric.** `|z_at_T(273.15) − 99| < 1` and `|T_at_z(99) − 273.15| < 3 K`, both computed from `cosmology.hpp` symbols (no literal 99/273 as input); a written one-paragraph isolation of the cosmological residue as the sole survivor, distinct from decay-time.

**Failure trigger.** The arithmetic disagrees (`z_at_T(273.15)` not ≈99) → **fix it** (§⑧ T3); re-check `T_CMB` value and the `z_at_T`/`T_at_z` round-trip. If the residue cannot be cleanly separated from decay-time provenance → **OPEN** the separation; do not collapse them.

**Gate.** No P4 until the arithmetic passes from the engine and the residue is isolated.
**Out of scope.** Deriving *what* set the gradient at z≈99 (that is a separate cosmological investigation; SAR05 only *isolates the question*).

---

### Phase 4 — The 2/5 seeding ratio: exact, but only the seed (1–2 h)

**Goal.** Confirm the **2/5 seeding** arithmetic is exact, show `Yₑ=0.4` makes the **first** r-process peak (**not** gold), and establish the climb to gold is mostly **silent (n,γ)** — withdrawing the earlier "β⁻ on every rung" overcount.

**Method.**
1. Seed-making cost from neutron-rich stock: a **deuteron** (2 baryons) costs one `n→p` = **1 antineutrino**; a **triton** (3 baryons) costs one `n→p` = **1 antineutrino** → **5 baryons, 2 antineutrinos**. Assert the ratio **2/5 is EXACT** (integer count, no fit). Tie to the grammar (NP02B): deuteron and triton are the two grammar blocks.
2. Compute `Yₑ` of the seed stock: 2/5 = **0.4**. State that `Yₑ=0.4` is **proton-rich / antineutrino-rich** and makes the **FIRST** r-process peak (A≈80), **NOT** gold. Gold (third peak, A≈197) needs `Yₑ≈0.1` — made by the neutrons you do **NOT** convert.
3. Therefore the **2/5 is the SEEDING cost, not the whole climb.** The climb to gold is mostly **silent strong-force (n,γ) captures** punctuated by occasional β⁻ (the "lazy path"). **Withdraw** the earlier "β⁻ on every rung" as an overcount; state the correction explicitly.
4. Print a small table: {block | baryons | n→p conversions | antineutrinos}, the 2/5 ratio, `Yₑ=0.4`, the peak it makes (first), and the `Yₑ≈0.1` needed for gold.

**Pre-committed success metric.** `(antineutrinos)/(baryons) = 2/5` **exactly** (integer arithmetic, asserted); a written statement that `Yₑ=0.4` → first peak (not gold) and gold needs `Yₑ≈0.1`; the "β⁻ on every rung" overcount explicitly withdrawn.

**Failure trigger.** If the baryon/antineutrino count is **not** 2/5 → re-check the grammar block conversions (§⑧ T4); do not fudge. If anyone claims `Yₑ=0.4` makes gold → **withdraw** the claim (the climb is silent (n,γ), not β⁻-per-rung).

**Gate.** Final verdict after P1–P4 gated.
**Out of scope.** A full r-process abundance fit (anchors only); deriving the peak masses from geometry (NP02B/NP07 own the grammar growth).

---

**Global pre-commitments.** Best class **C (Convergence)** on the ledger + seeding arithmetic; the after-iron fork is **NATIVE-eligible only** if a real observable separates self-consuming from pressure-fed, else **DEGENERATE** (declared). CALIBRATED budget **0** (no fitted parameters; ~3×10⁴⁶ J, 99, 273 K, Yₑ values are `OBSERVED-TARGET`/`DERIVED`, never fits). All z↔T from `cosmology.hpp`; all anchors traced to `measured::` + named events. Any phase failure → PIVOT/KILL/OPEN, never RETRO-PASS.

## 5. Success Criteria (200–300 words)

Use canonical labels. **Dual verdict required** (prompt completion A–F × physics class).

✅ **PASS (Class C: Convergence — the realistic ceiling).** All four phases gated. Provenance ledger built and **every row classified**, each beyond-CMB-at-decay claim SURRENDERED to a named local formation-time battery, with the decay/formation boundary frozen (P1). The after-iron fork either **LIVE** with a named separating observable (`L_ν(Ṁ)` slope or cliff-vs-supply) — *that sub-result is NATIVE* — **or** honestly **DEGENERATE** (P2). The z≈99 → 273 K arithmetic confirmed **from `cosmology.hpp`** and the cosmological residue isolated as the sole survivor, distinct from decay-time (P3). The 2/5 seeding ratio shown **exact**, `Yₑ=0.4`→first-peak-not-gold, climb-is-silent-(n,γ), overcount withdrawn (P4). **What we publish:** a one-table provenance ledger that dissolves beyond-CMB-at-decay everywhere in the forge and the decay, leaving one well-posed cosmological question — the honesty keystone of the set.

✅ **PASS+ (after-iron fork NATIVE).** As above, *and* P2's fork is LIVE with an observable separating self-consuming from pressure-fed at achievable precision. The fork sub-result is **Class A / NATIVE**; the ledger remains Class C.

⚠️ **QUALIFIED (Class C/D).** Ledger built and classified (P1) and arithmetic confirmed (P3, P4), but the after-iron fork is **DEGENERATE** (P2) — no observable separates the pictures. Ship the ledger and the residue; flag the fork as DEGENERATE, not a win.

❌ **FAIL / re-open (Class F / OPEN).** A beyond-CMB **at-decay** feed is genuinely **REQUIRED** somewhere (P1 cannot name a local battery; energy/sign won't balance) → the surrender was premature; **re-open** that row, record it in `INVESTIGATION_STACK.md`. Or the z≈99 arithmetic is wrong → fix it before any verdict.

**Forbidden at every level:** RETRO-PASS (widening a committed tolerance or fork-precision after seeing the number), PLUG (a coefficient to force a separation), IDENTITY-PASS (calling the ledger "done" without P2's fork resolved one way or the other), BORROW-SMUGGLE (G/M/GM, a stored gravitational potential, ΛCDM, ψ, quarks, the SM nucleosynthesis story into the chain).

## 6. Outputs (150–300 words)

All written into `Investigations/09_Stellar_Astrophysics_and_Radiation/SAR05_Provenance_After_Iron/`. **Edit no existing file; never touch `Engine/include/sdt/` or `Laws/`.**

1. **`SAR05_PROVENANCE_LEDGER.md`** — the heart: the four-row ledger `{claim reached-for | where it ACTUALLY resolves | local battery named | tag (SURRENDERED-to-formation / split-after-iron / local-finite / cosmological-residue)}`; the **frozen decay-time vs formation-time boundary**; the NP19 Two-Ledger tie for the neutronisation row; the after-iron fork statement (LIVE or DEGENERATE) with its separating observable; the cosmological-residue isolation. Each row flagged `SURRENDERED` / `LOCAL-FINITE` / `COSMOLOGICAL` / `RE-OPEN`.
2. **`sar05_provenance.cpp`** (or `sar05_provenance.py`) — standalone tool: `#include <sdt/laws.hpp>` (C++), uses `cosmology::z_at_T`, `T_at_z`, `wien_peak`, `z_freezing`. Prints: (i) the **z↔T table** incl. z≈99→273 K computed from the engine (not literals), with a PASS/FAIL on `|z_at_T(273.15)−99|<1`; (ii) the **2/5 baryon/antineutrino check** (integer assertion `2/5` exact, `Yₑ=0.4`, first-peak-not-gold, `Yₑ≈0.1` for gold); (iii) the **after-iron observable-separation estimate** (`L_ν` order-of-magnitude vs `Ṁ` scaling, the committed separating direction). One parameter tag per printed number. Build line in a header comment: `cl /std:c++20 /EHsc /O2 /I Engine/include /Fe:sar05.exe sar05_provenance.cpp` (or `g++ -std=c++20 -IEngine/include …`).
3. **`SAR05_VERDICT.md`** — dual verdict header (prompt completion A–F × physics class), filled falsification table (§⑧), explicit class call (ledger Class C; fork NATIVE or DEGENERATE, stated).
4. **`RUN_LOG.md`** — **mandatory**: Pre-Run Commitment Block (§⑩) filled before coding — *including the frozen decay/formation boundary* — then ADJ-### entries and phase gates per `PROMPT_EXECUTION_PROTOCOL.md`.

## 7. Dependencies & References (150–250 words)

**Upstream (required first):**
- **NP21** (Binding Curve as Resistance Landscape — *iron at the floor*) — supplies the seam where self-consuming and pressure-fed split; SAR05's P2 fork begins at NP21's derived floor.
- **NP19** (Mass-Defect as Form-Resistance + **Two-Ledger Lemma**) — supplies the boundary-cut framing: reaction-level endothermic vs event-level exothermic is one medium read through two cuts.
- **NP02B / NP07** (Grammar Chain Growth / Primordial Lithium) — supply the grammar growth and r-process seeding context (deuteron/triton blocks, EC timing).
- `cosmology.hpp` (`z_at_T`, `T_at_z`, `wien_peak`, `z_freezing`) — the z↔T arithmetic; do **not** re-derive or hardcode.

**Downstream (blocked / closed by this):**
- **Closes the provenance question** for the whole 9-investigation set — once SAR05 lands, no sibling may invoke "beyond-CMB at decay" without re-opening a SAR05 ledger row.

**Related (read in parallel):**
- **NP20** (neutron from one seat) — the 1.83c seat spun up at *formation*, not decay (the neutron's formation-time battery).
- **NP18** (Be-7 BEC flux resonator), **PPT10 / PPT11** (neutrino), **FLM11** (tape-measure principle — which battery you read depends on where you meter), **APS06** (emission ladder) — the sibling batch.
- **ATOMICUS `rules/On the Nature of Atomicus Rules.md`** — grammar constitution (deuteron/triton blocks, EC alternate grammar).

## 8. Falsification Tests (150–250 words)

| Test | Hypothesis | Predicted Outcome | If FAIL |
|------|-----------|-------------------|---------|
| **T1 (no at-decay feed — the crux)** | Every beyond-CMB claim resolves to a LOCAL formation-time battery | Each P1 row names a local battery; energy/sign balances without an external at-decay wire | A beyond-CMB **at-decay** feed is genuinely **REQUIRED** → the surrender was premature; **re-open** that row, record it; do not tag it SURRENDERED |
| **T2 (after-iron fork)** | Self-consuming and pressure-fed differ observably after iron | A signed `L_ν(Ṁ)` slope (or cliff-vs-supply) separates them at achievable precision | Identical signatures at all plausible precisions → **DEGENERATE**; declare it, do **not** fake a difference |
| **T3 (z≈99 arithmetic)** | The sky sat at 273 K at z≈99 (engine-sourced) | `z_at_T(273.15) ≈ 99`, `T_at_z(99) ≈ 273 K` from `cosmology.hpp` | Arithmetic disagrees → **fix it**; re-check `T_CMB` and the `z_at_T`/`T_at_z` round-trip; no verdict until it passes |
| **T4 (2/5 seeding)** | 5 baryons → 2 antineutrinos exact; Yₑ=0.4 → first peak, not gold | Integer `2/5` exact; climb to gold is silent (n,γ), not β⁻-per-rung | 2/5 not exact → re-check grammar conversions; anyone claiming Yₑ=0.4 makes gold → **withdraw** the overcount |
| **T5 (no SM-story smuggle)** | No standard-model nucleosynthesis story / ΛCDM / G in the chain | Anchors are numbers/events only; gravity via `g=v²/R` | An SM network "as truth" or ΛCDM or stored gravitational potential enters the chain → **audit fail**; strip it, re-run |

**Recovery:** T1 is a re-open (the ledger row, not the whole set). T2 is the honesty fork — DEGENERATE is a legitimate, *stated* outcome, not a failure to hide. T3 is a fix-the-arithmetic gate. T4 is a withdrawal of the overcount. T5 is an audit fail. Never RETRO-PASS a tolerance, fake a fork separation, or relabel a re-opened row as SURRENDERED.

## 9. Implementation Notes (200–300 words)

- **Tool is a checker, not a fitter.** `sar05_provenance` *verifies* the z↔T arithmetic, *asserts* the 2/5 integer ratio, and *estimates* (order-of-magnitude) the after-iron scaling separation. It contains **no optimiser** and seeks **no fitted number**. Use `assert` (or loud PASS/FAIL prints) for `|z_at_T(273.15)−99|<1` and the integer `2/5` check; do not silently continue past a failed assertion.
- **z↔T from the engine.** Read `z_at_T`, `T_at_z`, `wien_peak`, `z_freezing` from `sdt::laws`/`cosmology.hpp` only (§0 anti-creep). Do **not** hardcode 99 or 273.15 as inputs — they must *emerge* from `T_CMB`; the literals appear only as `OBSERVED-TARGET` comparison columns. Print the `z_at_T`/`T_at_z` round-trip to expose any drift.
- **Integer arithmetic for the seed.** Baryon and antineutrino counts are **integers** (deuteron: 2 baryons, 1 ν̄; triton: 3 baryons, 1 ν̄ → 5, 2). Compute the ratio as a rational `2/5`, assert exactness, then print `Yₑ = 2/5 = 0.4` as a derived decimal — never the reverse.
- **Order-of-magnitude discipline for P2.** The after-iron `L_ν` estimate is a *scaling argument*, not a precision prediction. Print the ~3×10⁴⁶ J event budget as `OBSERVED-TARGET`, divide by a representative collapse timescale for `L_ν`, and state the *committed direction* of the `L_ν(Ṁ)` slope difference. If the two pictures' slopes coincide, print "DEGENERATE" — do not tune.
- **Prose discipline.** Never write "charge radius"; charge is **handed redirection** (`e` = unit-bridge). Gravity is **directed spation pressure** (`g = v²/R`, `ϟ = v²R/c²`) — **no stored gravitational potential reservoir**, no G/M/GM in the chain. Anchors are the *numbers and events* (iron peak, GW170817 cliff, nova recurrence, ~99% neutrino vent), **not** the standard-model story.
- **Visualisation hint (optional):** a two-column ledger card (claim reached-for → local battery) with a single arrow to one isolated "cosmological residue (z≈99)" box makes the keystone obvious at a glance.

---

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — SAR05
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [CONVERGENCE on ledger + seeding; after-iron fork NATIVE if separable, else DEGENERATE]  # honest fork stated up front
- CALIBRATED budget: 0  (no fitted parameters; ~3e46 J, z≈99, 273 K, Yₑ values are OBSERVED-TARGET/DERIVED only)
- Engine namespaces: cosmology (z_at_T, T_at_z, wien_peak, z_freezing), measured (T_CMB, MeV_to_J, c)
- FROZEN DECAY/FORMATION BOUNDARY (fill BEFORE P2 runs — this is the binding contract):
    rule: a claim is "decay-time external" ONLY if no local formation-time battery can charge the bank; else "formation-time local"
    Neutron row        : side = [formation-time local]  battery = ____  (NP20 1.83c seat at liberation)
    Star-burn row      : side = [split-after-iron]      battery = ____  (below-Fe exothermic / above-Fe pressure-fed)
    Heavy-elements row : side = [local-finite]          battery = ____  (GW170817 kinetic merger; abundance cliff)
    Neutronisation row : side = [PRESSURE-runaway, NP19 cut]  battery = ____  (gravity pays; ~99% ν vent)
    cosmological residue: the ONLY survivor permitted to remain external (z≈99 gradient)
- Phase thresholds (committed before run):
    P1: 4 rows, each ONE tag, local battery named; decay/formation boundary frozen in RUN_LOG; 0 rows left "beyond-CMB at decay"
    P2: a signed L_ν(Ṁ) slope (or cliff-vs-supply) difference committed BEFORE estimate; else DEGENERATE declared
    P3: |z_at_T(273.15) − 99| < 1 AND |T_at_z(99) − 273.15| < 3 K, both from cosmology.hpp (no literal 99/273 input)
    P4: (antineutrinos)/(baryons) = 2/5 EXACT (integer); Yₑ=0.4 → first peak not gold; "β⁻ on every rung" withdrawn
- Forbidden retroactive changes: widen tolerances or fork-precision post-run; fake a fork separation; tag a row
  SURRENDERED when no local battery exists (must re-open); hardcode 99/273; import G/M/GM/stored-potential/ΛCDM/ψ/quarks/SM-network into the chain; write "charge radius"
```

### Pivot table (minimum — extend for this investigation)

| Trigger (numeric/logical) | PIVOT (first response) | If pivot fails | Forbidden |
|---------------------------|------------------------|----------------|-----------|
| P1: a row has no nameable local formation-time battery | Search the formation channels (fission/spallation/photodisintegration/r-process/cosmic-ray/accretion); name one | **RE-OPEN** that row (§⑧ T1); record in stack | Tag it SURRENDERED anyway |
| P1: decay/formation boundary not frozen before P2 | Write the one-line rule; freeze in `RUN_LOG.md` | STOP — report blocker | Start P2 without the cut |
| **P2: self-consuming ≡ pressure-fed (no separating observable)** | Try the next observable in §④ (L_ν(Ṁ) → cliff-vs-supply → recurrence) | **DEGENERATE** (§⑧ T2); declare it | Invent a difference to claim NATIVE |
| P2: estimate needs a beyond-CMB at-decay feed to balance | Re-localise to the formation-time battery (P1) | **RE-OPEN** (§⑧ T1) | Plug an external wire |
| **P3: `z_at_T(273.15)` ≠ 99 (±1)** | Re-check `T_CMB` value and `z_at_T`/`T_at_z` round-trip from engine | STOP — fix arithmetic (§⑧ T3) | Hardcode 99/273 to "pass" |
| P3: cosmological residue can't be separated from decay-time | Re-state the two questions distinctly; show residue is an early-epoch boundary condition | **OPEN** the separation | Collapse them into one |
| **P4: (ν̄)/(baryons) ≠ 2/5** | Re-check grammar block conversions (d=2b/1ν̄, t=3b/1ν̄) | STOP — fix the count (§⑧ T4) | Fudge to 2/5 |
| P4: someone claims Yₑ=0.4 makes gold | State Yₑ=0.4 → first peak (A≈80); gold needs Yₑ≈0.1; climb is silent (n,γ) | — | Keep "β⁻ on every rung" |
| Rivals (SM) match the events but SDT doesn't *beat* | Label **DEGENERATE / CONVERGENCE** honestly | — | Claim Class A "derivation" |

### Allowed adjustments

- Finer numerics (denser z↔T table; representative collapse-timescale refinement for `L_ν`); phase splits (2a `L_ν(Ṁ)` slope, 2b cliff-vs-supply) via ADJ entry; filename fix (`.cpp`↔`.py`) via ADJ entry.
- Alternative **native** separating observables for P2 already listed in §④ (neutrino-luminosity scaling → endothermic-continuation cliff → nova recurrence) — provided no fitted parameter is introduced.

### Disallowed adjustments

- Post-hoc widening of any tolerance or fork precision · faking a fork separation to avoid DEGENERATE · tagging a row SURRENDERED when no local battery exists (must RE-OPEN) · hardcoding 99/273 instead of `cosmology.hpp` · importing G/M/GM / a stored gravitational potential / ΛCDM / ψ / quarks / the SM nucleosynthesis network as truth into the chain · writing "charge radius" or treating charge as a substance.

### Dual verdict reminder

Every `SAR05_VERDICT.md` header carries **both** axes: **Prompt completion** (A–F, did §④–§⑥ get done phase by phase?) and **Physics class** (NATIVE / CONVERGENCE / DEGENERATE / OPEN / KILLED). **Honest expectation, stated up front:** the ledger + seeding arithmetic land **CONVERGENCE (Class C)** — an audited reframe, not a new number; the after-iron fork is **NATIVE only if a real observable separates self-consuming from pressure-fed**, otherwise **DEGENERATE** and labelled exactly that. Beyond-CMB-at-decay is required *nowhere* in the forge or the decay; it survives **only** as the cosmological residue at z≈99 — a legitimate but *different* question, and keeping it separate is the whole point.

---

*SAR05 · SPEC · the provenance ledger — beyond-CMB dissolved into local formation-time batteries, one cosmological residue at z≈99 · consumes NP21's iron floor & NP19's Two-Ledger Lemma · closes the provenance question for the set · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*
