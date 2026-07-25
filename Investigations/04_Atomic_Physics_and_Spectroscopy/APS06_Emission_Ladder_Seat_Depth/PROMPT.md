# APS06 — The Emission Ladder by Seat Depth: the hydrogen ceiling and the neutron requirement for gamma

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC.
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — The electromagnetic spectrum is taught as an *energy* ladder (microwave → IR → visible → UV → X-ray → gamma), but X-rays and gammas of **the same energy** are indistinguishable as photons and are separated only by **where they were made** (electron-seat vs nucleus-seat). What is the *native* ordering variable that makes this provenance split a derived consequence rather than a teaching convention?
2. **Why does it matter?** — If emission is ordered by **seat depth** (how deep the displaced electron/nucleon sits), then the photon band is a *read-out of structure*, not a free axis. This closes the long-standing conceptual hole "what really separates an X-ray from a gamma," vindicates the alpha grammar (every real nucleus carries neutrons), and feeds the rung below gamma to **PPT10** (the neutrino as straight-light). Stack-blocking for the NP18–NP21 / PPT10–11 emission set.
3. **How will we find out?** — Four gated phases (§④): (P1) define seat depth and pre-commit a *monotonic* seat-depth → emission-energy law from the `atomic` namespace + Rydberg/Lyman; (P2) derive the **hydrogen electronic ceiling = 13.6 eV** as the deepest neutron-free seat and show the next-deeper seats demand added protons (X-ray) or neutrons (gamma); (P3) the decisive empirical test — *every recorded nuclear gamma comes from a neutron-containing nucleus*; (P4) reconcile the X-ray/gamma energy overlap as **provenance, not energy**.
4. **What would prove us wrong?** — §⑧ falsifiers with numeric triggers: a bound neutron-free nucleus past H-1 emitting gamma → **KILL**; seat depth NOT monotonic with energy (a deep seat emitting low-energy light) → ordering **fails**; the 13.6 eV ceiling not recovered from geometry → **PIVOT**.
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). Done = the seat-depth ladder table, the derived 13.6 eV ceiling, and the exceptionless neutron-requirement check all ship with `APS06_VERDICT.md`.

---

## 0 · Reader's contract (non-negotiable, read before §1)

This is a **forensic ordering** investigation. The claim is structural and the test is empirical, so the standards are strict:

1. **No borrowed story.** The measured DATA are anchors — the Lyman limit (13.6 eV / ~91 nm), the observed band sequence microwave→IR→visible→UV→X-ray→gamma, and the empirical fact that the diproton is **unbound**. These enter as *data*. The standard-model narrative that supplies them (binding by the strong force, QED level structure, nuclear shell model) does **not** enter the SDT chain. Anchors in, model out — never the reverse.
2. **No charge-as-substance.** Never write "charge radius." `R_p` is the proton **boundary / displacement radius**. Electromagnetic emission is **handed redirection** of throughput; `e` is a unit-bridge, not a stuff. Seats are geometric depths, not charge wells.
3. **Provenance, not energy, is the electronic/nuclear line.** The corrected teaching (P4) must state plainly: a 100 keV photon from an inner shell and a 100 keV photon from a nucleus are *the same photon*; only the seat that made them differs. Any deliverable that re-imports "X-rays are lower-energy than gammas" as a definition is `VOID`.
4. **Whitelist only.** Permitted inputs `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` + measured observables in measured units. Every constant cites its `laws.hpp` line. No `G`, no `M`, no `GM`. No wavefunctions, fields-as-primitives, quarks/gluons, virtual particles as objects, dark matter/energy, ΛCDM, duality.

If a deliverable cannot satisfy these, it is marked `VOID` and excluded — not estimated, not reconstructed.

---

## 1. Executive Summary (the question, in one breath)

Emission is organised by **seat depth**, not by energy. A displaced constituent sits at a depth `s`; the deeper it sits, the more reorganisation cost is released as a photon when it settles, and the higher the emitted energy. Molecular rotational/vibrational seats are shallow (microwave–IR, meV); atomic outer-shell seats are deeper (visible–near-UV, eV — the "electronic floor"); atomic inner-shell seats are deeper still (soft–hard X-ray, keV, *still electronic*); nuclear seats are deepest (gamma, keV–MeV). **The bands overlap**: an X-ray and a gamma at equal energy are the same photon, labelled only by **origin**. The deepest *neutron-free* seat that exists is hydrogen's Lyman limit, **13.6 eV**: above it, every photon requires either more protons (deeper electronic seats → the X-ray climb) or a real nucleus (neutrons → gamma). Because the **diproton is unbound**, there is no bound all-proton nucleus past H-1 — so **every nuclear gamma ever recorded came from a nucleus containing neutrons**. We will make seat depth the native ordering variable, derive the 13.6 eV ceiling, and verify the neutron requirement is empirically exceptionless.

---

## 2. Physical Context (the ladder, in plain language)

Picture the lattice as a stack of **seats** at increasing depth. A throughput knot that is lifted out of a seat and allowed to settle back releases the lift cost as straight-out light (an emission). The *band* of that light is a read-out of *how deep the seat was*:

- **Shallow seats — molecular geometry.** A molecule re-orients (rotation) or flexes a bond (vibration). Tiny lift cost → microwave to IR (meV). These are *between-knot* seats, the loosest in the stack.
- **The electronic floor — atomic outer shell.** An electron (W=1 loop) sits in the outer wake of a nucleus. Settling releases eV-scale light → visible to near-UV. This is the floor of *atomic* emission: the shallowest *single-particle* seat.
- **Deeper electronic — atomic inner shell.** Knock out a K-shell electron of a high-Z atom; the refill settles from a much deeper wake → keV light, the soft-to-hard **X-ray** band. **Still an electron seat** — the depth grew because there are more protons pulling the wake inward, not because the emitter changed.
- **Deepest — nuclear.** A nucleon rearranges inside the nucleus itself; the lift cost is keV–MeV → **gamma**. The emitter is the *nucleus*, not an electron.

**Key variables (define all; dimensions explicit):**

| Symbol | Meaning | Dimension | Range |
|---|---|---|---|
| `s` | **seat depth** — reorganisation lift cost of the deepest occupied seat (defined in P1) | [J] or [eV] | meV → MeV |
| `E_γ` | emitted photon energy | [eV] | meV → MeV |
| `k = c/v` | kinematic ratio of the active constituent (`v = √(2E/m)`) | [-] | ≥ 1 |
| `Z` | proton count of the emitting structure | [-] | 1 … 118 |
| `n_d, n_t` | deuteron / triton load from the alpha grammar (`nuclear.hpp`) | [-] | ≥ 0 |
| `N = A − Z` | neutron count | [-] | 0 (H-1 only) → … |
| `E_Ly` | hydrogen Lyman limit (the electronic ceiling anchor) | [eV] | 13.6057 |

**Why it connects:** the seat-depth ladder is the spine that unifies APS01/APS02 (atomic emission from the velocity-state chain) with the nuclear alpha grammar (`nuclear::alpha_grammar`) and with NP20 (the neutron = proton + a *seated* electron). The neutron is precisely what lets a seat go **deeper than the 13.6 eV electronic floor** without simply adding protons — it is the rung that opens the gamma band.

---

## 3. Theoretical Framework (axioms, constraints, the ceiling logic)

**Axioms in play (SDT, no borrow):**

- **Law IV** — mass/energy is reorganisation cost of throughput. An emission is the cost of the deepest occupied seat being vacated and re-settled; hence **seat depth `s` ≡ release energy `E_γ`** up to band-specific geometry. This is the load-bearing identification.
- **Law V** — movement budget `v² + v_circ² = c²`; the active constituent's `k = c/v` sets where on the radial ladder it sits (APS01 `zk² = 1` closure).
- **Law VI** — vortex topology: electron W=1 (loop), proton W=3 (trefoil), **neutron = a proton with a seated electron** (NP20; W=3 ⊕ W=1, net like W=0 for the wake). Free neutrons are forbidden in stable nuclei — a "free neutron" is an exposed triton remnant.
- **Alpha grammar (constitutional)** — every nucleus Z ≥ 2 = 1 alpha core + `n_d` deuterons + `n_t` tritons, with `n_t = A − 2Z`, `n_d = 3Z − A − 2`, valid wedge `2Z ≤ A ≤ 3Z − 2` (`nuclear.hpp`). The only `(Z,A)` outside the wedge with `N = 0` is **H-1** (and the light exceptions H-2, He-3 carry `N ≥ 1` or fail the wedge).

**Engine symbols to use (cite the line at use; do NOT redefine):**

- `measured::Ry_eV = 13.605'693…` (laws.hpp:155) — the Lyman-limit anchor.
- `measured::R_inf` (laws.hpp:154) and `atomic::R_inf_derived = m_e c α²/(2h)` (laws.hpp:929) — Rydberg from invariants, the electronic floor's scale.
- `atomic::rydberg_energy_eV(Z,n1,n2)` (laws.hpp:871), `atomic::bohr_radius(Z,n)` (laws.hpp:901), `atomic::bohr_velocity(Z,n)` (laws.hpp:896).
- `atomic::velocity_from_IE1(IE1_J)` (laws.hpp:955) and the drag factor `atomic::drag_factor` (laws.hpp:974) — APS02 lineage for the seat→k map.
- `nuclear::alpha_grammar(Z,A)`, `nuclear::inverse_alpha_grammar`, the valid wedge, and the H-1/H-2/He-3 exceptions (`nuclear.hpp`).
- `measured::eV_to_J`, `MeV_to_J` (laws.hpp:183–184) for band conversions.

**The ceiling logic (to be made rigorous in P2):** for a *one-proton* system the deepest electronic seat is the `n=1` Bohr seat; its release ceiling is exactly the Rydberg energy `Z²·Ry` with `Z=1` ⇒ **13.6 eV**. To go deeper *without* neutrons you must raise `Z` (the X-ray climb, `E ∝ Z²`), but a bound all-proton nucleus with `Z ≥ 2` does not exist — the **diproton is unbound** (`²He` has no bound state). Therefore the only way to seat *anything* deeper than 13.6 eV in a *nucleus* is to admit **neutrons**. The gamma band is gated by neutrons.

**Constraints / prohibitions:** no QED level diagrams, no shell-model magic numbers as inputs, no strong-force coupling, no `G/M/GM`. The diproton's instability is taken as **measured datum** (an OBSERVED anchor), not derived here (its SDT derivation is NP19/NP20 territory — DEFER, cite by ID).

---

## 4. Investigation Strategy (be excessive — four gated phases)

> Native mechanism before any rival. Each phase pre-commits a numeric gate **before** the run; Phase N+1 is forbidden until PASS-GATE or a documented DEFER. Out-of-scope items are stated to prevent creep in both directions.

### Phase 1 — Define seat depth; pre-commit the monotonic seat-depth → energy law (PAPER + tool stub) — ~2–3 h

**Goal:** a quantitative, dimensioned definition of seat depth `s` and a **pre-committed monotonic** map `s ↦ E_γ` across the four seat classes (molecular, outer-shell, inner-shell, nuclear).

**Method:**
1. Define `s` as the reorganisation lift cost (Law IV) of the deepest occupied seat, in J/eV. For atomic seats, anchor `s` to the radial ladder via `k = c/v` and the `zk² = 1` closure (APS01): deeper seat ⇒ larger `k` ⇒ smaller orbit radius `a₀/k²` ⇒ larger release. For molecular seats, `s` is the inter-knot bond/orientation cost (meV scale, taken as OBSERVED anchor band). For nuclear seats, `s` is the alpha-grammar rearrangement cost (keV–MeV anchor band; magnitude via grammar, NOT shell model).
2. **Pre-commit** the ordering inequality (write it into `RUN_LOG.md` before computing any band):
   `s_molecular < s_outer-shell < s_inner-shell(Z) < s_nuclear`, and the monotone map `E_γ = f(s)` with `f` strictly increasing (`df/ds > 0` everywhere).
3. Build the skeleton of `aps06_seat_ladder` (C++ or Python): a table that, for each seat class, emits `[seat class | representative system | s (eV) | predicted band | observed band]`.
4. Tag every number `DERIVED` / `COMPUTED` / `OBSERVED-ANCHOR` / `PENDING` per the parameter ledger.

**Pre-committed success metric:** the four representative seats sort into the *same order* by `s` and by observed band — **monotone, zero inversions** across all four classes. The outer-shell representative (hydrogen `n=1`) must reproduce `Ry_eV` to **< 50 ppm** from `atomic::R_inf_derived` (sanity of the atomic anchor).

**Failure trigger:** any inversion (a deeper seat emitting a lower band) → ordering fails; PIVOT to the §⑩ row (re-define `s` via release cost only, drop any band-dependent weighting) before re-testing. If still inverted → the seat-depth thesis is **OPEN**, not PASS.

**Out of scope (P1):** absolute molecular/nuclear `s` to better than order-of-magnitude (bands are anchors here, not predictions); the 13.6 eV *derivation* (that is P2); any neutron census (P3).

### Phase 2 — Derive the hydrogen electronic ceiling = 13.6 eV; show the next seats need protons or neutrons (CALCULATION) — ~2–3 h

**Goal:** show `13.6 eV` is the deepest *neutron-free* single-particle electronic seat, recovered from geometry (`atomic::R_inf_derived`), and that exceeding it forces either added protons (X-ray, `E ∝ Z²`) or neutrons (a real nucleus, gamma).

**Method:**
1. Compute the hydrogen `n=1` release ceiling natively: `E_ceiling = Z² · R_inf_derived · hc` with `Z=1` ⇒ compare to `measured::Ry_eV`. Use `atomic::rydberg_energy_eV(1, 1, ∞)` / the Lyman limit. This is the **neutron-free electronic ceiling**.
2. **Hydrogen is the only neutron-free nucleus:** run `nuclear::alpha_grammar` (and the H3 grammar) over the `N=0` line; demonstrate that the valid wedge `2Z ≤ A ≤ 3Z−2` admits **no** `(Z≥2, N=0)` nuclide, and that the diproton (`Z=2, A=2`) lies outside it / is the measured-unbound exception. Print the wedge boundary at `A = 2Z` for `Z = 1…10`.
3. The X-ray climb: tabulate the inner-shell (`n=1`) ceiling `Z²·Ry` for `Z = 1, 2, 6, 26, 82` (H, He, C, Fe, Pb) → show eV → keV growth, *all still electronic seats*, all requiring **more protons** (and, past H, therefore neutrons to bind those protons).
4. State the corollary precisely: above 13.6 eV, a photon's seat is either (a) a deeper electronic seat in a higher-`Z` atom — which, past hydrogen, **necessarily** sits on a neutron-containing nucleus — or (b) a nuclear seat (gamma). Either way, **anything past the hydrogen ceiling rides on neutrons.**

**Pre-committed success metric:** `|E_ceiling − Ry_eV| / Ry_eV < 50 ppm` (geometry recovers 13.6 eV); the wedge scan returns **zero** `(Z≥2, N=0)` valid nuclides; the `Z²` X-ray table is monotone in `Z`.

**Failure trigger:** ceiling not recovered to < 50 ppm → **PIVOT** (check `R_inf_derived` vs `R_inf`, units, `hc`); if the geometry genuinely cannot produce 13.6 eV → the ceiling claim is **PIVOT/OPEN**, never retro-passed. If the wedge admits a spurious `(Z≥2,N=0)` nuclide → re-derive the wedge from `nuclear.hpp` (do not hand-edit).

**Out of scope (P2):** deriving *why* the diproton is unbound (DEFER → NP19/NP20); molecular and nuclear absolute energies.

**Gate:** P3 forbidden until the 13.6 eV ceiling PASS-GATE.

### Phase 3 — Consistency check ONLY: the ladder does not contradict the nuclide chart (SURVEY + tool) — ~1 h

> **CORRECTED 2026-07-23 (Harvey, vocal-cords rule).** The original phase called this "the decisive
> empirical test: nuclear gamma requires neutrons" with a pre-registered KILL gate on finding a
> `N=0, Z≥2` gamma emitter. That gate is **vacuous**: no bound `N=0, Z≥2` nucleus exists at all —
> every nucleus after hydrogen has a neutron, as a measured fact upstream of emission, accepted by
> every framework. The counterexample class was empty before any scan ran. "Everyone who yells has
> vocal cords, zero counterexamples." A survey of it, at any sample size, adds zero discriminating
> power and must never be reported as a PASS-GATE or as evidence for the ladder.

**Goal (demoted):** record, as a consistency check, that the seat-depth ladder and the alpha grammar
do not *contradict* the chart — deep (nuclear-seat) emission always sits on neutron-carrying
structure because neutron-carrying structure is the only bound structure there is past H-1.

**Method:** run the grammar over a cited nuclide list (ATOMICUS DB / NNDC / AME2020), record
`N` and `(n_d, n_t)` per gamma emitter, emit `APS06_results.csv`. No gate, no count ceremony.

**What native teeth would actually require (open, deferred):** deriving diproton unboundness from
SDT geometry (NP19/NP20, wedge-free) — i.e. *predicting* that the `N=0, Z≥2` class is empty rather
than observing that it is. Until that derivation lands, the only P3 residue with any content is the
**monotone ordering** of seat depth with emission energy (P1's claim, tested there).

**Gate:** none — P4 proceeds regardless.

### Phase 4 — Reconcile the X-ray/gamma overlap as provenance, not energy (PAPER) — ~1–2 h

**Goal:** state the corrected teaching: the electronic/nuclear line is drawn by **provenance (seat origin)**, not by photon energy, and the energy bands genuinely overlap.

**Method:**
1. Build the overlap table: list a high-energy electronic line (e.g. a high-`Z` Kα X-ray, tens of keV) and a low-energy nuclear gamma (e.g. ⁵⁷Fe 14.4 keV) at **comparable energy**; show that **as photons they are identical** — only the seat (electron vs nucleus) differs.
2. Write the corrected definition explicitly: "X-ray" = electron-seat emission; "gamma" = nucleus-seat emission; the historical energy-band split is a teaching artifact that fails in the overlap region. Seat depth is the native ordering variable; provenance is the native label.
3. Tie back: hydrogen caps the neutron-free electronic ladder at 13.6 eV; everything deeper rides on neutrons; the neutrino (PPT10) is the rung **below** nuclear gamma (straight-light from the deepest seat rearrangement) — flag as downstream, do not derive here.

**Pre-committed success metric:** the overlap table contains ≥ 1 electronic line and ≥ 1 nuclear line within a factor 2 in energy, both with primary citations, with the seat-origin label correctly assigned; the corrected-teaching paragraph contains no "X-rays are lower-energy than gammas" definitional statement.

**Failure trigger:** if no real energy overlap example can be cited → **PIVOT** to the next-closest pair and widen the energy window (documented ADJ); the *claim* (provenance not energy) does not change.

**Out of scope (P4):** quantitative provenance discrimination algorithms; PPT10 neutrino derivation (DEFER).

---

## 5. Success Criteria (dual verdict, canonical labels)

**Dual verdict required in `APS06_VERDICT.md`:** Prompt completion (A–F: did the four phases do what §④ asked?) **and** Physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN).

- ✅ **PASS (Class A: Derived / NATIVE):** seat depth defined and monotone with energy (zero inversions, P1); 13.6 eV ceiling recovered to < 50 ppm from `R_inf_derived` (P2); the overlap reconciled as provenance (P4). No fitted parameters; every constant from `laws.hpp`. **P3 contributes nothing to the verdict either way** (vacuous class — see the P3 correction block); it is recorded as a consistency check only.
- ✅ **QUALIFIED (Class C: Convergence):** P1–P2 pass; molecular/nuclear absolute `s` only order-of-magnitude.
- ⚠️ **QUALIFIED PENDING (Class D: Computed):** ladder ordering holds and the ceiling is recovered, but corpus partial.
- ❌ **FAIL (Class F / KILLED):** the ladder is non-monotone (a deep seat emitting low energy), **or** the 13.6 eV ceiling cannot be recovered from geometry (then the ceiling claim is OPEN, not PASS).

A failed phase is **PIVOT / KILL / OPEN** — never retro-PASS. An OPEN phase must not be summarised as PASS.

---

## 6. Outputs (exact file names — rename ⇒ ADJ entry)

1. **`APS06_DERIVATION.md`** — the seat-depth definition (P1), the 13.6 eV ceiling derivation from `atomic::R_inf_derived` and the alpha-grammar wedge (P2), and the provenance-not-energy corrected teaching (P4). Every number flagged DERIVED / COMPUTED / OBSERVED-ANCHOR / PENDING.
2. **`aps06_seat_ladder.cpp`** (or `.py`) — standalone tool (`#include <sdt/laws.hpp>`): (a) the seat-depth → band table across the four seat classes; (b) the 13.6 eV ceiling check + the `Z²` X-ray climb table; (c) the alpha-grammar wedge scan proving no `(Z≥2, N=0)` nuclide; (d) the neutron-requirement check across the nuclide list. Emits `APS06_results.csv`.
3. **`APS06_results.csv`** — one row per nuclide `[Z, A, N, n_d, n_t, gamma_keV, neutron_present, provenance]` plus the seat-ladder table rows and a summary counting any counterexamples.
4. **`APS06_VERDICT.md`** — dual verdict (prompt A–F + physics class), phase-by-phase result, the §⑧ falsification table updated with actual numbers, circularity / delete-test note.
5. **`RUN_LOG.md`** — mandatory: Pre-Run Commitment Block (copied from §⑩) filled before coding, all ADJ-### entries, phase gates.

---

## 7. Dependencies & References

**Upstream (required):**
- **APS01 / APS02** — the velocity-state emission chain, `zk² = 1` closure, drag factor `D` (the atomic seat ↦ `k` map). `Investigations/04_Atomic_Physics_and_Spectroscopy/APS01_Emissions/`, `APS02_Emission_Prediction/`.
- **`atomic` namespace** — `R_inf_derived`, `rydberg_energy_eV`, `bohr_radius`, `bohr_velocity`, `velocity_from_IE1`, `drag_factor` (laws.hpp:867–975).
- **Nuclear grammar** — `nuclear::alpha_grammar`, `inverse_alpha_grammar`, valid wedge, H-1/H-2/He-3 exceptions (`nuclear.hpp`). Alpha grammar = 1 alpha + `n_d` deuterons + `n_t` tritons.
- **NP20** — neutron = proton + seated electron (the rung that lets a seat go deeper than the 13.6 eV electronic floor). Cite by ID; do not re-derive.

**Downstream (blocked / fed):**
- **PPT10 (straight-light)** — the neutrino as the rung **below** nuclear gamma. APS06 fixes the gamma rung; PPT10 takes the step below it.
- **NP18 (resonator), NP19/NP20 (neutron), NP21 (landscape), PPT11 (oscillation), FLM11 (tape-measure), SAR05 (provenance)** — sibling set; APS06 supplies the emission-ladder ordering they reference.

**Related (informative):** APS03 (drafting crossover — same APS lineage), APS04 (trefoil wake multipole), `ATOMICUS/rules/On the Nature of Atomicus Rules.md` (nuclear constitution), AME2020 / NNDC nuclide data (gamma energies, neutron numbers).

---

## 8. Falsification Tests

| Test | Hypothesis | Predicted outcome | If FAIL |
|---|---|---|---|
| **T1** | Seat depth is monotone with emission energy | Four seat classes sort identically by `s` and by observed band — zero inversions | A deep seat emitting low-energy light ⇒ ordering **fails**; PIVOT to release-cost-only `s`, else OPEN |
| **T2** | 13.6 eV is the neutron-free electronic ceiling, recoverable from geometry | `|E_ceiling − Ry_eV|/Ry_eV < 50 ppm` from `R_inf_derived` | Ceiling not recovered ⇒ **PIVOT** (units / `R_inf` vs derived); if irrecoverable, ceiling claim **OPEN** |
| **T3** | No bound all-proton nucleus past H-1 (diproton unbound) | Alpha-grammar wedge admits **zero** `(Z≥2, N=0)` valid nuclides | A bound `(Z≥2,N=0)` nuclide ⇒ re-derive wedge from `nuclear.hpp`; if real, the ceiling argument breaks → KILL |
| ~~T4~~ | **STRUCK 2026-07-23** — "gamma requires neutrons" has an empty counterexample class (no bound `N=0,Z≥2` nucleus exists, all frameworks). Not a test. | — | — |
| **T5** | X-ray/gamma overlap is provenance, not energy | ≥1 electronic and ≥1 nuclear line within a factor 2 in energy, identical as photons | No real overlap citable ⇒ PIVOT to next-closest pair (claim unchanged) |

**Recovery discipline:** T1/T2/T5 failures invoke the §⑩ pivots; T3 failure is **KILL** (numbers recorded), never rescued by a fit or a widened tolerance. **Rule learned here (apply everywhere): before pre-registering a KILL gate, check the counterexample class is populated — a gate that cannot fire is ceremony, not falsification.**

---

## 9. Implementation Notes

- **Units:** work in eV internally for atomic seats, convert nuclear bands via `MeV_to_J` / `eV_to_J` (laws.hpp:183–184). The ladder spans ~9 orders of magnitude (meV → MeV); use **double precision** and print in scientific notation. Compute *ratios* (e.g. `E_ceiling/Ry_eV`, `Z²` growth) rather than absolute differences where possible.
- **Anchors vs derivations:** molecular and nuclear absolute energies are **OBSERVED-ANCHOR** band magnitudes, not SDT predictions — tag them so the verdict cannot mistake an anchor for a derivation. The only hard *derivation* is the 13.6 eV ceiling (P2) and the monotone ordering (P1).
- **Wedge scan:** drive it from `nuclear::alpha_grammar(Z,A)` directly; never hand-code `n_t = A−2Z`. Print the `A = 2Z` boundary so the `N=0` line is visibly outside the wedge for `Z ≥ 2`.
- **Nuclide data:** prefer a machine-readable table (ATOMICUS isotope DB in-repo, or AME2020/NNDC). Any hand-typed gamma/`(Z,A)` row goes in a separately-labelled, fully-cited array and is excluded from the §13-style verdict unless every value carries a primary citation. Record provenance per row in the CSV.
- **Sanity:** before P2, assert `atomic::R_inf_derived ≈ measured::R_inf` to ~0 ppm (laws.hpp:929 comment) — if not, a units bug exists; STOP and fix before any ceiling claim.
- **Visualisation hint:** a single log-energy axis with the four seat-class bands drawn as overlapping rectangles makes the X-ray/gamma overlap (P4) self-evident; mark 13.6 eV as the hydrogen ceiling line.

---

## ⑩ Adaptive Execution Protocol (MANDATORY)

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS, PLUG, IDENTITY-PASS, or BORROW-SMUGGLE. See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — APS06
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 — none permitted; flag any fit explicitly]
- Engine namespaces: atomic:: (R_inf_derived, rydberg_energy_eV, bohr_radius, velocity_from_IE1, drag_factor),
                     measured:: (Ry_eV, R_inf, eV_to_J, MeV_to_J), nuclear:: (alpha_grammar, wedge)
- Phase thresholds (committed before run):
    P1 monotone ordering: ZERO inversions; H n=1 reproduces Ry_eV < 50 ppm
    P2 ceiling: |E_ceiling − Ry_eV|/Ry_eV < 50 ppm; wedge admits ZERO (Z≥2,N=0) nuclides
    P3: consistency check only — no gate (counterexample class empty; see P3 correction block)
    P4 overlap: ≥1 electronic + ≥1 nuclear line within factor 2 in energy, both cited
- Forbidden retroactive changes: widen any tolerance; relabel an OBSERVED-ANCHOR band as DERIVED;
  hand-edit the alpha-grammar wedge; rescue a T4 counterexample with a fit; local constant namespaces
```

### Pivot table (extend as needed)

| Trigger (numeric) | First response (PIVOT) | If pivot fails | Forbidden |
|---|---|---|---|
| P0 sanity: `R_inf_derived ≠ R_inf` to ~0 ppm | Fix units / `hc` / which Rydberg symbol; re-verify laws.hpp lines | STOP — report blocker | Fit to 13.6 eV |
| P1 T1: any band inversion | Re-define `s` as release cost only (drop band-dependent weighting); re-sort | **OPEN** the seat-depth ordering; do not PASS P1 | RETRO-PASS the ordering |
| P2 T2: ceiling off > 50 ppm | Check `R_inf` vs `R_inf_derived`, `hc`, eV conversion | **OPEN/PIVOT** ceiling; do not retro-pass | PLUG a coefficient to hit 13.6 eV |
| P2 T3: wedge admits `(Z≥2,N=0)` | Re-derive wedge from `nuclear::alpha_grammar` (no hand-edit) | If genuinely bound ⇒ ceiling argument breaks → **KILL** | Hand-edit the wedge |
| P3 T4: an `N=0,Z≥2` gamma emitter | Verify provenance / grammar validity of that nuclide | If real ⇒ **KILL** neutron-requirement; record numbers | Rescue with a fit or exclude silently |
| P4 T5: no energy overlap citable | Next-closest electronic/nuclear pair; widen window (ADJ) | — | Re-import energy-band definition |
| Upstream missing (NP20 neutron mechanism, AME2020 table) | **DEFER** that sub-claim; cite blocker ID | — | Fake PASS |

### Allowed adjustments
- Finer nuclide list, alternative machine-readable table, phase splits (P3a curated / P3b full table), filename fix via ADJ entry.
- Alternative **native** definition of `s` already listed in §④ (release-cost-only route).

### Disallowed adjustments
- Post-hoc tolerance widening · coefficient plugs to hit 13.6 eV · relabelling OBSERVED-ANCHOR bands as DERIVED · hand-editing the alpha-grammar wedge · importing the "X-rays < gammas in energy" definition as a result · `G/M/GM`, wavefunctions, quarks/gluons, virtual particles, ΛCDM in the SDT chain.

### Dual verdict reminder
`APS06_VERDICT.md` must carry **both** axes in its header: Prompt completion (A–F) and Physics class (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN). An OPEN phase is never reported as PASS in the summary line.

---

### Appendix — the one-line statement of the whole investigation

*Is emission ordered by **seat depth** rather than energy — so that hydrogen's 13.6 eV Lyman limit is the deepest neutron-free seat, the X-ray/gamma overlap is a matter of **provenance not energy**, and every nuclear gamma ever recorded (the diproton being unbound) comes from a neutron-containing nucleus — exceptionlessly?*

---

*APS06 · SPEC · execute with `PROMPT_EXECUTION_PROTOCOL.md`. Author: J. C. Harvey, Melbourne.*
