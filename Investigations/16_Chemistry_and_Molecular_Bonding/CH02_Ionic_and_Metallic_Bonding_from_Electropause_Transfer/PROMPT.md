# CH02 — Ionic & Metallic Bonding from Electropause Transfer

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (10× upgrade 2026-06-29).
> **Inherits:** `PERFECT_PROMPT_TEMPLATE.md` §⓪–§⑩ · `PROMPT_EXECUTION_PROTOCOL.md` · §0 anti-creep (R0–R5).
> **Engine:** `#include <sdt/laws.hpp>` only — no local constant namespaces.
> **Run:** Pre-commit thresholds in `RUN_LOG.md` before coding; adjust per pivot table (§⑩).
---

## ⓪ The Golden Rule — five questions (answer before Phase 0)

1. **What don't we know?** — Whether the ionic bond can be derived as an electropause handed off
   *entirely* to the partner and the metallic bond as electropauses *delocalised* into a lattice
   sea — recovering NaCl's lattice energy (~787 kJ/mol) and a metal's bonding radius from
   electropause/occlusion balance, with NO charge substance ("charge" = handed redirection of the
   convergent phase, no orbitals, no band-theory wavefunctions).
2. **Why does it matter?** — CH02 is the second primary-bond branch off CH01 (covalent = shared
   electropause): ionic = full handoff, metallic = delocalised sea. The metallic sea is *literally*
   the conduction substrate of CM02 downstream — one pressure must yield both cohesion and
   conductivity — and the transfer criterion makes the electronegativity ordering fall out as a
   convergence-well-depth ordering.
3. **How will we find out?** — Gated phases in §④: (P1) transfer criterion from APS01 well depths,
   (P2) NaCl lattice energy as a geometric Madelung-analogue occlusion sum, (P3) metallic
   delocalised-pressure balance, (P4) one novel lattice energy — native mechanism established
   BEFORE importing any Coulomb constant as a primitive or touching rivals.
4. **What would prove us wrong?** — §⑧ falsification tests with concrete numeric triggers: wrong
   ionic/covalent split, lattice energy that cannot cohere without importing the Coulomb (or
   literature Madelung) constant as a fitted primitive, wrong sign, or post-hoc tuning of the
   occlusion-pressure scale to hit 787 kJ/mol (IDENTITY-PASS).
5. **How will we know we're done?** — **Dual verdict:** prompt completion (A–F) + physics class
   (NATIVE / CONVERGENCE / DEGENERATE / KILLED / OPEN), logged in `CH02_VERDICT.md`.

## ⓪⁺ Anti-Tautology Firewall *(the load-bearing constraint)*

The load-bearing derivation is the **geometric occlusion sum** over the rock-salt lattice (a
Madelung-analogue computed from lattice *geometry*) together with the **well-depth transfer
criterion** — NOT importing the Coulomb constant or the literature Madelung constant as a fitted
primitive and reading 787 kJ/mol back off it. State plainly: **importing the Coulomb constant (or
the literature Madelung constant) as a primitive caps the grade at C — it is the textbook identity,
not the SDT derivation.** The occlusion-pressure scale MAY be CALIBRATED(1), but it must be declared
in the Pre-Run Commitment Block; matching the measured lattice energy by tuning that scale post-hoc
is forbidden (IDENTITY-PASS).

## Question

CH01 derived the covalent bond as a **shared** electropause. The other two primary bonds are the
same boundary handled differently. **Can the ionic bond be derived as an electropause handed off
*entirely* to the partner, and the metallic bond as electropauses *delocalised* into a shared
lattice sea — recovering NaCl's lattice energy and a metal's bonding radius from electropause
balance, with no charge substance, no orbitals, no band-theory wavefunctions?** "Charge" here is
only the handed redirection of the convergent phase ([[project_cq47_repulsion_inverse]]); the
ion's "+/−" is which way its convergent phase is redirected after the handoff.

## SDT mechanism & hypotheses

When one atom's electropause can sit *more deeply* in a neighbour's convergence well than in its
own, the electropause migrates: the donor is left with a tighter core electropause (the cation),
the acceptor gains an extra outer one (the anion). The bond is then the residual occlusion balance
([[law_III]]) between the two reorganised cores at their equilibrium separation. In a metal the
outermost electropauses cannot settle on any single host — they **delocalise** into a lattice-wide
shared sea, the same merge as CH01 but periodic, which is exactly the conduction substrate of CM02.

- **H1 (transfer):** the electropause migrates iff the partner well is deeper; predicts which
  pairs go ionic vs covalent (electronegativity ordering as well-depth ordering).
- **H2 (lattice energy):** ionic cohesion = summed occlusion balance over the lattice; recover
  NaCl ~787 kJ/mol with the Madelung sum re-read as a geometric occlusion sum, no Coulomb constant
  imported as a primitive.
- **H3 (metallic sea):** delocalised electropauses give a cohesive energy and equilibrium R for
  Na/Cu from a uniform shared-electropause pressure; ties directly to CM02 conduction.

## Strategy

**Phase 1 — Transfer criterion.** *Goal:* predict ionic vs covalent from well depths. *Method:*
compare donor self-well vs acceptor well using APS01 core radii. *Success:* correct ionic/covalent
split for ~15 reference pairs (NaCl, MgO ionic; H₂, CH₄ covalent).

**Phase 2 — NaCl lattice energy.** *Goal:* cohesive energy. *Method:* sum the pairwise occlusion
balance over the rock-salt lattice (geometric Madelung-analogue). *Success:* lattice energy within
~15% of 787 kJ/mol; correct sign.

**Phase 3 — Metallic sea.** *Goal:* cohesive E and R for one metal. *Method:* uniform delocalised
electropause pressure balanced against core occlusion. *Success:* Na bonding radius and cohesive
energy within ~25%; hands the same field to CM02.

**Phase 4 — Falsifier.** *Goal:* one novel number. *Method:* predict an un-calibrated lattice
energy (e.g. KCl or MgO) or a metallic radius down a group from APS01 k-factors.

## Success criteria

- **PASS (A):** transfer criterion + NaCl lattice energy + metallic R from one field, ≤1 flagged
  constant, plus a correct novel lattice energy.
- **QUALIFIED (C):** NaCl and Na recovered with the occlusion-pressure scale CALIBRATED(1).
  *(Expected landing.)*
- **PENDING (D):** transfer criterion shown; lattice energy only order-of-magnitude.
- **FAIL (F):** cannot cohere a lattice without importing the Coulomb constant as a primitive or a
  band wavefunction.

## Falsification tests

| Test | Predicted outcome | If FAIL |
|------|-------------------|---------|
| Transfer = deeper-well migration | ionic/covalent split correct for >=13 of 15 ref pairs (NaCl, MgO ionic; H₂, CH₄ covalent) | split wrong for >2 of 15 pairs ⇒ KILL transfer criterion (electronegativity isn't well depth) |
| Lattice = geometric occlusion sum | NaCl lattice energy 787 kJ/mol within 15%, correct (cohesive) sign | >15% off 787 kJ/mol after pivot ⇒ OPEN; wrong sign ⇒ KILL |
| Metallic = delocalised sea | Na bonding R and cohesion within 25% of measured from one uniform pressure | >25% off after pivot ⇒ OPEN; needs band theory to cohere ⇒ KILL metallic-sea hypothesis |
| No imported Coulomb primitive (firewall) | lattice energy emerges from the geometric occlusion sum alone | cohesion only matches when the Coulomb/Madelung constant is fed in ⇒ IDENTITY-PASS, capped at C |

## Dependencies

**Upstream:** CH01 (shared electropause), EMC04 (electropause/P_eff), EMC03 (handed redirection sign).
**Downstream:** CM02 conduction (the metallic sea is its substrate), CH05 energetics.
**Related:** APS01 k-factor core radii; the Li–Be "loosest dyad" handoff note
([[project_foundational_ontology_influx_monopole]]).
---

## Questions This Opens *(generative — log new ones in `CH02_VERDICT.md`)*

1. Is electronegativity *literally* the convergence-well depth — does the Pauling scale fall out of
   APS01 k-factor well depths as a one-to-one ordering?
2. Is there a continuous covalent-to-ionic spectrum set by the well-depth *difference* (partial
   ionic character = partial handoff), rather than a binary transfer?
3. Does the same delocalised-electropause "sea" that gives metallic cohesion ALSO give CM02's
   conductivity — one pressure, two observables — and can both be read off a single field?
4. What sets the occlusion-pressure scale — is it derivable from Law III geometry alone (zero
   calibrated params), or is the CALIBRATED(1) floor irreducible?
5. Does the lattice-energy occlusion sum predict the Born–Landé repulsion exponent natively, rather
   than taking it as an empirical fit?

## ⑩ Adaptive Execution Protocol

> *It is a bad plan that cannot be altered.* Failures invoke **PIVOT / KILL / OPEN** — never RETRO-PASS or PLUG.
> See `PROMPT_EXECUTION_PROTOCOL.md`.

### Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding)

```markdown
## Pre-Run Commitments — CH02
- Prompt completion target: [A|B|C|D]
- Physics class hoped: [NATIVE|CONVERGENCE|DEGENERATE|OPEN]
- CALIBRATED budget: [0 or list each param — max per §⑤]
- Engine namespaces: EMC04 electropause, CH01 wake balance, no MO/LCAO
- Phase thresholds (committed before run): P1 ionic/covalent split correct for >=15 ref pairs · P2 NaCl lattice energy within 15% of 787 kJ/mol, correct sign · P3 Na radius+cohesion within 25% · P4 novel lattice energy (KCl/MgO) within 20%
- Forbidden retroactive changes: widen tolerances; plug targets; IDENTITY-PASS; local constant namespaces
```

### Pivot table (minimum — extend for this investigation)

| Trigger | PIVOT (first) | If pivot fails | Forbidden |
|---------|---------------|----------------|-----------|
| Phase 0 sanity check fails | Fix units/engine refs; verify `laws.hpp` symbols | STOP — report blocker | Fit to target |
| Native mechanism off > committed % | Alternative route in §④; document ADJ-### | **OPEN** or **KILL** hypothesis | RETRO-PASS |
| Lattice sum won't cohere without Coulomb primitive | re-derive pairwise occlusion balance from Law III geometry | **OPEN** ionic cohesion | import Coulomb constant, call it NATIVE |
| Rivals match but SDT doesn't beat | Label **DEGENERATE** honestly | — | Claim Class A |
| Upstream dependency missing (FLM10, etc.) | **DEFER** phase; cite dependency ID | — | Fake PASS |

### Allowed adjustments

- Finer numerics (mesh, ticks, bracket); phase splits (Na / Nb); filename fix via ADJ entry.
- Alternative **native** routes already listed in §④ Strategy.

### Disallowed adjustments

- Post-hoc tolerance widening · coefficient plugs · `atomic::`/GM/G in Phase-1 native chain · importing the Coulomb/Madelung constant as a primitive then claiming NATIVE · band-theory wavefunctions in any native chain.

---

*CH02 · 10× upgrade 2026-06-29 · execute with `PROMPT_EXECUTION_PROTOCOL.md`.*

---
---

# RUN 2 PROMPT (2026-07-06) — the wall, transmitted: isoelectronic fork + rolling-firewall candidate

> **Author:** J. C. Harvey, Melbourne. **Status:** SPEC (run 2, written 2026-07-06; nothing above this line altered).
> **Inherits:** everything the run-1 prompt inherits, plus `Investigations/HUNTER_PROTOCOL.md` in full (§A–§G) and the
> FARMER refinement-8 record (`Investigations/FARMER_PASS_2026-07-03.md`, "Rules refinements" item 8).
> **Provenance of the re-open (both triggers on record in `CH02_VERDICT.md` ⟐ 2026-07-06):**
> (1) the MgO §D re-open condition fired — NP10 run 2 landed its lock ladder ((Z−1)! Face-T PASS, d −1.06% / t +0.88% / α −5.57%,
> zero constants) AND structurally KILLED the radial saturation wall (enhancement identity ρ(π−2ρ) ≥ 1: exact occlusion can only
> DEEPEN attraction — it cannot be the chemistry wall, at any radius, under any sub-boundary profile);
> (2) refinement 8: **electron repulsion is nuclear repulsion TRANSMITTED** (shell = gearbox; amended in-session: every rotor
> defends with its own wake, the nuclear rotor dominates when present), and the wall mechanism candidate is the **rolling wake
> firewall** — desynchronised rotations ROLL across each other (roll = repulsion, frustration surplus) where cadence-locked
> rotations MESH (mesh = bond = movement saved). Under the movement triad (PASS / BECOME / PRESS), the wall is PRESS:
> **"pressure itself is movement that cannot move."**
> **What run 2 is NOT:** a relabel of run 1. P1/P2/P4 labels stand; the MgO FAIL stands until a **derived** wall is computed,
> not fitted. Run 2 asks one new decidable question and builds one candidate against a registered three-field cross-check.

## §R0 The run-2 question

Run 1's fingerprint was systematic: **+9.4% (NaCl), +7.9% (KCl), +21.6% (MgO)** — overshoot growing with charge product,
exactly where the one underived term (short-range contact repulsion) does its work. NP10 run 2 proved that term is **not**
radial occlusion saturation. Refinement 8 names its successor and hands this file a gift: **Mg²⁺ and O²⁻ are both neon-shell
— MgO is an isoelectronic pair**, so the transmission claim makes a prediction run 1 never asked for. Run 2 asks:

**Is the short-range wall nuclear-sourced (transmitted through the shell-gearbox), and is its mechanism the rolling wake
firewall — one wall that simultaneously pays k(H₂), the 1:1-salt overshoot, and coheres with the NP10 lock split?**

## §R1 Phase 0 — MANDATORY base-data mining (read before building anything)

The base has already paid for every constraint the wall must obey. The executor MUST read the following files and tabulate the
earned numbers into the RUN_LOG **before** writing any code (ADJ-before-code applies to this table too). This list is the
minimum; actively mine for more — anything in the repo that bounds a short-range, contact-scale, repulsive term is in scope.

| File (absolute repo path) | Earned number(s) to extract | What it constrains |
|---|---|---|
| `Investigations/16_Chemistry_and_Molecular_Bonding/CH02_Ionic_and_Metallic_Bonding_from_Electropause_Transfer/RUN_LOG.md` + `CH02_VERDICT.md` + `results.txt` | Evjen geometric **M = 1.747574**; NaCl **861.0** vs 787 (+9.4%); KCl **771.8** vs 715 (+7.9%); MgO **4611.6** vs 3791 (+21.6%); Na sea +460%; anchors r₀ = 2.820 / 3.146 / 2.106 Å | the machinery anchor (§R5.11) and the three lattice targets: the wall must remove ~74.0 kJ/mol at NaCl, ~56.8 at KCl, ~820 at MgO — same wall, no per-target tuning |
| `Investigations/05_Nuclear_Physics/NP10_Alpha_Binding_from_Tetrahedral_Occlusion/NP10_VERDICT.md` (both runs) + `np10_contact_wall_results.txt` | enhancement identity **ρ(π−2ρ) ≥ 1** (the kill); Face-T **(Z−1)!** ladder d −1.06% / t +0.88% / α −5.57%; D1 fence: ℏ²/2m_e budget gives R_min 0.579 Å (−22%), k 2697 N/m (+369%); D2 cage rule: nuclear ledger shifts deuteron only **+0.23%**; run-1 boost curve ×1.01 / ×1.98 / ×6.35 | what the wall must NOT be (any solid-angle-deficit ledger is pre-killed); the wall's scale fence (~ℏ²/2m_e, within ×4.7 of k(H₂) where occlusion missed by ×31); the coherence conditions (§R3.4) |
| `Investigations/16_Chemistry_and_Molecular_Bonding/CH07_Molecular_Spectra_Vibration_and_Rotation/CH07_VERDICT.md` + `results.txt` | **k(H₂) = 575 N/m** (the cleanest single-number target); structural theorem: shared-seat well g\* = −4.19615 at x\* = 0.2887 is NON-restoring (d²E/dR² < 0 everywhere); §G.5: the point well at contact gives −81.5 eV vs 31.95 eV measured — the WELL also fails at contact, not just the wall | the stiffness gate; the theorem that vibration = the bond breathing against the firewall; warning that a wall bolted onto an uncorrected point well inherits the well's contact failure — score it anyway, log the attribution |
| `Investigations/16_Chemistry_and_Molecular_Bonding/CH04_Molecular_Geometry_VSEPR_from_Wake_Balance/CH04_VERDICT.md` | read and extract the earned rim-geometry results (angles, wake-balance geometry) | the rolling interface is a RIM contact (FARMER refinement 2: angle is the premium, contact area is small) — any firewall geometry must be consistent with CH04's earned angular structure |
| `Investigations/16_Chemistry_and_Molecular_Bonding/CH06_Hydrogen_Bonding_and_van_der_Waals_from_Residual_Wake/CH06_VERDICT.md` | read and extract the residual-wake results (index records an emergent **−6.022** power — verify on read; the file is authoritative) | the long-range tail the wall must hand over to at large r: firewall (contact) and residual wake (vdW) must not double-count the same movement |
| `Investigations/12_Condensed_Matter_Physics/CM01_Superconductivity_as_Phase_Locked_Vortex_Pairs/CM01_VERDICT.md` | isotope exponent **−0.5000**; the η = T_c/θ_D **24× spread** | θ_D is lattice stiffness = the wall in bulk; a real wall law should compress or explain the η spread direction; cadence-locking (mesh) is CM01's own mechanism — same firewall vocabulary, opposite sign |
| `Investigations/10_Fluid_Dynamics/FD02_Viscosity_and_Circulation_Quantum/FD02_VERDICT.md` + `FD02_DERIVATION.md` | circulation quantum **κ = h/m** | the rolling interface is a circulation mismatch; h/m is the repo's earned quantum of circulation per unit mass — the natural unit in which a rolling cost should be expressible |
| `Investigations/01_Foundations_and_Lattice_Mechanics/FLM12_The_Mass_Mechanism/FLM12_MASS_MECHANISM.md` + verdicts | mass = resistance to reorganisation; confinement ℏc/Δx forces localisation; mass defect = synchrony saving | the PRESS bookkeeping (Phase C) and the reason the D1 fence lands at ℏ²/2m_e: confinement cost is Law-IV/V native in kind |
| `Investigations/01_Foundations_and_Lattice_Mechanics/FLM14_Rotating_Spation_Sequential_Occupancy/PROMPT.md` + `FLM14_VERDICT.md` + `RUN_LOG.md` | rotation DOF, sequential seat-tours, (Z−1)! tour count; run-1 earned frustration **0.347**; **status: CLAIM REFUSED at runs 4–5** — leads only, nothing from FLM14 is promotable | owner of ROOT-LOCK; the dwell/tour language for Phase C; do NOT import unearned FLM14 claims into a gated chain |
| `Investigations/06_Gravitation_and_Orbital_Mechanics/GOM17_Exchange_Ledger_Gas_Giant_Calibration/GOM17_VERDICT.md` + `RUN_LOG.md` | the exchange-ledger METHOD (two-sided ledger lines, all-kinematic, GM banned in-chain) | the bookkeeping form for Phase C's frustrated-movement budget |
| `Investigations/FARMER_PASS_2026-07-03.md` (refinements 2, 3, 8) | angle-is-the-premium; meshing IS the mass defect (union-not-sum); the movement triad + firewall chain verbatim | the mechanism's own record — quote it, don't paraphrase it into something stronger |
| `Engine/include/sdt/laws.hpp` | αℏc, a₀, R_p, m_e, ℏ (read-only) | the ONLY constant source. **Never edit; never shadow with local namespaces.** |

**Harvey's disqualified-data fallback (mandatory clause, applies from Phase 0 onward):** previously disqualified or
quarantined results — e.g. `Investigations/05_Nuclear_Physics/NP09_Deuteron_Binding_from_Occlusion/` scalar-bond
intermediates (occlusion route dead at −97.3%), static-seat kernels from the pre-FLM14 static-spation class, and any
PV_canon-quarantined material — **may be consulted as LEADS, with their disqualification labels travelling with every
citation.** A disqualified number may suggest a functional form or a scale; it may never sit in a gated chain, and nothing
sourced this way is promoted without a fresh derivation. Log every such consultation in the RUN_LOG with its label.

## §R2 Phase A — THE ISOELECTRONIC FORK (primary decidable; runs FIRST; needs no SDT machinery)

Phase A is a pure measured-data discrimination. It uses no engine symbols, no SDT mechanism, and it decides the fork whatever
state the engine is in. It runs and is scored **before** Phase B is built, so its outcome can steer the wall's functional form
without contaminating the gate.

**A.1 The series (fixed shell, varying nucleus).** Assemble measured short-range repulsion parameters for isoelectronic ions:

- **He-shell (2 e⁻):** H⁻ (Z=1), Li⁺ (Z=3), Be²⁺ (Z=4) — via LiH/NaH hydride data for H⁻; flag its scarcity honestly.
- **Ne-shell (10 e⁻):** O²⁻ (Z=8), F⁻ (Z=9), Na⁺ (Z=11), Mg²⁺ (Z=12), Al³⁺ (Z=13).
- **Ar-shell (18 e⁻):** S²⁻ (Z=16), Cl⁻ (Z=17), K⁺ (Z=19), Ca²⁺ (Z=20).

**A.2 The parameter columns (≥2 independent sources required by the gate).**

1. **Born–Mayer hardness B and range ρ** from the repulsive term B·exp(−r/ρ), per ion pair, from published crystal fits —
   the **Tosi–Fumi (1964) alkali-halide tables** are the canonical set; extend with published fits for the alkaline-earth
   oxides/chalcogenides and hydrides.
2. **Born–Landé exponent n** (the r⁻ⁿ convention) — a DIFFERENT convention, tabulated side-by-side, never averaged with (1).
3. **Bulk-modulus-derived wall stiffness** (independent column): from measured B₀ (elastic data) of each salt, extract the
   implied repulsive curvature at r₀ — this column does not pass through anyone's Born fit and is the strongest independence
   check.
4. (Optional, flagged informational) Shannon/Pauling crystal radii at fixed shell — trivially Z-ordered; used only for the
   degeneracy audit (A.6), never toward the gate.

Because B and ρ are pair parameters (cation×anion), disentangle by holding the counter-ion fixed within a comparison
(e.g. F⁻ salts of Na⁺/Mg²⁺/Al³⁺) and by comparing the repulsive **force and stiffness evaluated at a common contact
criterion** rather than raw B (B and ρ are convention-coupled; a raw-B comparison across different ρ is not a comparison).
Every operationalisation used must be declared in the RUN_LOG **before** tabulation (look-elsewhere).

**A.3 PRE-COMMITTED GATE (verbatim — this text is the gate; it is written here before any data is tabulated and is copied
unchanged into `RUN_LOG.md`):**

> **GATE-A:** if electron repulsion is nuclear repulsion TRANSMITTED, wall hardness rises and range shrinks MONOTONICALLY
> with Z at fixed shell, in ≥2 independent shells, on ≥2 independent parameter sources; the electron-source rival predicts
> flatness at fixed shell. Null: Z-shuffled ordering; look-elsewhere: declare the number of series and parameter conventions
> consulted. FALSIFIER stated plainly: flat hardness at fixed shell kills the transmission claim's chemistry expression.

**A.4 Operationalisation (fixed before tabulation; changing any of it after seeing data = RETRO-PASS).**

- "Monotonically" = strict rank order: Kendall τ = +1 (hardness/stiffness vs Z) and τ = −1 (range vs Z) within a series,
  for every series–source combination with ≥3 ions of usable data.
- **Null model:** the permutation test — recompute the statistic under all Z-shuffles of each series; report the exact
  probability of the observed perfect ordering arising by shuffle (for a 5-ion series, 1/120 per signed ordering; combine
  series as independent).
- **Look-elsewhere declaration (committed now):** 3 series, 4 parameter columns (A.2.1–A.2.4, with A.2.4 informational).
  Any series or convention added later is an ADJ-logged addition and CANNOT count toward the gate — it can only be reported.
- **Data sufficiency floor:** a series–source cell with <3 ions is reported but excluded from the gate arithmetic.

**A.5 Data-provenance clause (binding).** Every number in the Phase-A table carries its source (author/year/table or
database identifier) and its significant figures. Conflicting literature conventions (different Born exponents n, different
fitting ranges, rigid-ion vs shell-model fits) are tabulated **side-by-side, never averaged** — an average across conventions
is a fabricated datum. Where two sources disagree on the same quantity, both rows appear and the gate is scored on each
source separately (that is what "≥2 independent parameter sources" is for).

**A.6 Degeneracy audit (§G MIRROR — do not let the fork flatter the house claim).** The registered rival in GATE-A is the
**electron-count** source (repulsion set by the number of shell electrons — identical at fixed shell ⇒ flat). There is a
third reading the executor must log and address: **cloud contraction** (higher Z contracts the same shell, which also
hardens contact at fixed shell). Distinguish them where the data allows: transmission predicts the hardness trend tracks the
NUCLEAR count Z itself even after controlling for ionic radius (compare at equal contact distance, not equal r₀); pure
contraction predicts the trend is fully absorbed by the radius column (A.2.4). If Phase A's monotone signal survives but
cannot be separated from contraction, the verdict says **MONOTONE-BUT-DEGENERATE** — the fork decided against flatness, the
transmission mechanism not yet uniquely earned. That is an honest outcome; write it if it happens.

**A.7 GATE-CONTRABAND check (pre-run):** GATE-A's kill condition is a measured-data pattern (flatness in published hardness
tables), not a rival's axiom. The rival's PREDICTION (flatness) appears as the alternative hypothesis, not as an enforcement.
Check passes. Re-run this check on any gate added by ADJ.

## §R3 Phase B — the rolling-firewall wall vs the REGISTERED THREE-FIELD CROSS-CHECK

**B.1 The candidate.** The wall = the **rolling wake firewall** (refinement 8): two rotors whose rotations cannot
cadence-lock ROLL across each other, and the rolling interface is a frustration SURPLUS — movement demanded by the ledger,
denied a path, pressing (PRESS mode). Attraction and repulsion are ONE signed frustration ledger (shadow = deficit, rolling
interface = surplus — EMC03 restated). The scale fence is already earned: NP10 run-2's D1 diagnostic puts the ~ℏ²/2m_e
curvature budget within ×4.7 of k(H₂) where radial occlusion missed by ×31 (and it is FLAGGED formally degenerate with the
QM zero-point form — carry that flag; a wall that never separates from the QM form caps at CONVERGENCE). If Phase A lands
transmission, the wall's functional form must carry explicit nuclear dependence at fixed shell (the shell as gearbox:
compliance electronic, force nuclear); if Phase A lands flat, the transmission form is dead here and only an electron-side
rolling cost may be attempted — Phase A steers, it does not tune.

**B.2 Machinery anchor (mandatory clause).** CH02 run-1's Evjen expanding-cubes machinery is reusable **verbatim**. Before
ANY new term is added, the reused code must reproduce run-1's numbers to 1e-6 relative: **M = 1.747574; NaCl 861.0; KCl
771.8; MgO 4611.6 kJ/mol.** Print the anchor block in the results file. If the anchor fails, STOP — fix the reproduction,
never "re-derive past" it.

**B.3 The registered cross-check (gates committed in RUN_LOG before coding; conjunction — one wall pays all or the wall
dies):** one mechanism, one constant set drawn from `laws.hpp` (αℏc, a₀, R_p, m_e, ℏ), **zero per-target tuning**:

- **(a) k(H₂) ≈ 575 N/m** (CH07 anchor) — commit a gate ≤25% (NP10 run-2 precedent). Score at the measured Re = 0.7414 Å;
  also report the candidate's own R_min. Log the CH07 §G.5 caveat: the point well itself fails at contact (−81.5 eV vs
  31.95 eV) — if the wall is right but the well is wrong, say exactly that; do not launder a well failure into a wall pass
  or vice versa.
- **(b) NaCl overshoot corrected:** wall term moves 861.0 → within the original 15% gate of 787 (required removal ≈
  −74.0 kJ/mol, i.e. −8.6%); **KCl same formula, no refit** → within the original 20% gate of 715 (≈ −56.8 kJ/mol);
  **MgO reported and scored** against its original 20% gate of 3791 (the isoelectronic pair — Phase A's fork made flesh).
  Sign discipline: the wall must REMOVE binding; NP10 run-2's Face-R candidate died on this exact sign.
- **(c) coherence with the NP10 α lock ×6.35 story:** ROOT-CONTACT split — the lock (×6.35 at the alpha) is Face-T's
  (Z−1)! tour count, owner FLM14/ROOT-LOCK; the wall is ROOT-WALL. The wall candidate must therefore (i) be negligible at
  nuclear pair scale — evaluated at the deuteron geometry it must not shift NP17's earned 2.200 MeV by more than 1%
  (anchor: NP10 run-2 cage rule, +0.23%); (ii) NOT re-absorb or contradict the (Z−1)! ladder (a wall that claims the ×6.35
  for itself re-merges what NP10 run 2 split — that requires killing Face T first, which is not this run's business);
  (iii) leave the two-centre case lock-free ((2−1)! = 1), which is exactly why pairwise chemistry needs only well + wall.

**B.4 Kill memoranda (pre-falsified forms — attempting them anyway = ignoring the base's own record):**

1. Any wall reducible to a **radial solid-angle-deficit ledger** is pre-killed by the enhancement identity ρ(π−2ρ) ≥ 1
   (NP10 run 2): exact occlusion only deepens attraction. If your candidate, expanded, is occlusion in a costume — it is
   already dead. Write the reduction check explicitly in the tool.
2. Any **flat per-bond boost** is pre-falsified by NP10 run-1 G3 (all flat-factor pairings failed at ~−70%).
3. Any candidate needing a **fitted scale per target** is not a wall, it is three knobs; CALIBRATED budget for Phase B is 0.

**B.5 Constraints to mine (from §R1, actively):** CH04 rim angles (the roll happens at a rim window, not a face); CH06's
residual-wake tail (wall and vdW tail must partition r cleanly, no double-count); CM01's η = T_c/θ_D 24× spread and −0.5000
isotope exponent (bulk stiffness and cadence-locking are this wall's condensed-matter face — report what the candidate
implies for θ_D even ungated); FD02's κ = h/m (express the rolling cost in circulation quanta if the form allows — a wall
whose natural unit is h/m is speaking the base's language). None of these are gates; all of them are cross-checks to report.

## §R4 Phase C — P3 metallic, re-scoped as a PRESS-mode budget (LEADS ONLY — no gate, nothing graded)

Run 1's P3 failed at +460% because the sea was counted as all gain and no cost. Refinement 8 names the cost's mode: the
delocalised sea's confinement is **frustrated movement** — movement demanded by the ledger, denied a path; **pressure =
movement that cannot move.** Phase C produces a MEMO, not a verdict: candidate bookkeeping forms for the confinement cost
of the sea in a 2.08 Å Wigner–Seitz cell, each with what it implies for Na's 1.113 eV/atom — reported, not scored.
Mine for the bookkeeping form: **FLM12** (confinement ℏc/Δx; mass = reorganisation resistance; D1), **FLM14** (seat-tour /
dwell cost language — leads only, CLAIM REFUSED status travels), and **GOM17's exchange-ledger method** (two-sided ledger
lines, all-kinematic: write the sea's budget as paired give/take lines the way GOM17 wrote the Sun–Jupiter line, so that
when a derivation lands it drops into an existing ledger format). No gate; ROOT-BUDGET stays OPEN unless a derivation
actually lands, in which case propose gates for a run 3 — do not gate mid-run.

## §R5 Mandatory clauses (each one binding; violation = prompt-completion cap at D)

1. **Phase 0 base-data mining** (§R1) — the table is filled into RUN_LOG before any code.
2. **Harvey's disqualified-data fallback** (§R1) — disqualified/quarantined results usable as LEADS only, labels travelling;
   nothing promoted without derivation.
3. **ADJ-before-code** — every adjustment (numeric, filename, series addition, convention addition) is ADJ-logged in
   RUN_LOG BEFORE the code that embodies it is written.
4. **Gates never widened** — no committed tolerance moves after any number is seen. Ever.
5. **§D seven questions on any FAIL** — full seven-question recovery in the verdict, per `HUNTER_PROTOCOL.md`.
6. **GATE-CONTRABAND check** — no kill condition may enforce a rival's axiom; every gate must trace to a measured anchor,
   an internal-consistency requirement, or a pre-committed native criterion (§R2 A.7 records the Phase-A check; repeat for
   any ADJ-added gate).
7. **NO G / M / GM in-chain** — kinematic koppa only; any rival-column comparison (e.g. the QM zero-point form the D1 fence
   is degenerate with) is labelled **informational** and sits outside the derivation chain.
8. **Never "charge radius"** — the proton parameter is the **boundary radius** R_p (boundary/surface/displacement radius);
   there is no charge substance, only handed redirection.
9. **No borrowed units** — no μ_B, no magnetons, no imported yardsticks; SDT-native quantities (αℏc, a₀, R_p, κ = h/m,
   koppa) plus SI mechanical units only.
10. **Results file = teed stdout of an exit-0 tool** — `results file` is the verbatim stdout of the tool run; exit code 0
    required for a scored run (an honest structural failure may exit non-zero, as NP10 run 2 did — then the run is scored
    as its verdict says, and the exit code is reported, not hidden).
11. **Machinery anchor** (§R3 B.2) — reused run-1 code reproduces run-1 numbers to 1e-6 relative before new work.
12. **Windows encoding note** — set `PYTHONIOENCODING=utf-8` for any Python tooling (and `/utf-8` for MSVC); the Windows
    console default mangles the symbols this repo uses (ρ, τ, ⟐, ±) and a mangled results file is not a results file.

## §R6 Pre-Run Commitment Block (copy to `RUN_LOG.md` before coding — verbatim, then fill)

```markdown
## Pre-Run Commitments — CH02 RUN 2 (2026-07-06)
- Phase order: 0 → A → B → C. Phase A scored before Phase B is built.
- GATE-A (verbatim from PROMPT §R2 A.3): if electron repulsion is nuclear repulsion TRANSMITTED, wall hardness rises and
  range shrinks MONOTONICALLY with Z at fixed shell, in ≥2 independent shells, on ≥2 independent parameter sources; the
  electron-source rival predicts flatness at fixed shell. Null: Z-shuffled ordering; look-elsewhere: declare the number of
  series and parameter conventions consulted. FALSIFIER stated plainly: flat hardness at fixed shell kills the transmission
  claim's chemistry expression.
- Look-elsewhere declaration: 3 series (He-, Ne-, Ar-shell), 4 parameter columns (Born–Mayer B/ρ; Born–Landé n;
  bulk-modulus stiffness; radii informational-only). Monotone statistic: Kendall τ = ±1; null = exact permutation p.
- Phase B gates (conjunction, one constant set, zero per-target tuning): k(H₂) within [≤25%, commit exact number here] of
  575 N/m · NaCl within 15% of 787 · KCl within 20% of 715 · MgO scored vs 20% of 3791 · deuteron shift < 1% (cage
  coherence) · sign: wall removes binding.
- Machinery anchor: M = 1.747574; NaCl 861.0; KCl 771.8; MgO 4611.6 — reproduced to 1e-6 relative before any wall term.
- CALIBRATED budget: 0. A calibrated wall scale ⇒ Phase B reports OPEN, never PASS.
- Phase C: leads-only memo, no gate.
- Forbidden: widen gates; per-target tuning; radial-occlusion wall in any costume; flat per-bond boost; G/M/GM in-chain;
  borrowed units; "charge radius"; promoting disqualified-data leads without derivation; editing Engine/include/sdt or Laws.
```

## §R7 Deliverables

1. RUN_LOG entries: Phase-0 mining table, faith ledger (§G.1, named before the run), Pre-Run Commitment Block, ADJ log.
2. Tools: Phase-A table/statistics tool (data-assembly; C++ or Python) and Phase-B wall tool (C++20, `#include
   <sdt/laws.hpp>` only) — each producing a teed-stdout results file per §R5.10.
3. `CH02_VERDICT.md` appended with a **RUN 2 VERDICT** in the house dual-verdict format (prompt completion A–F + physics
   class), Phase A and Phase B scored separately (Phase A can PASS while Phase B dies, and vice versa — do not blend them),
   §D seven questions on any FAIL, §G faith ledger and MIRROR paragraph, cascade roots reported (STACK edits left to owner).
4. Nothing in `Engine/include/sdt/` or `Laws/` touched. Labels above the ⟐ notice in the verdict untouched.

---

*CH02 RUN 2 · spec'd 2026-07-06 · J. C. Harvey · Phase A decides the fork, Phase B pays or dies by the cross-check, Phase C
writes the PRESS memo · execute with `PROMPT_EXECUTION_PROTOCOL.md` + `HUNTER_PROTOCOL.md`.*
