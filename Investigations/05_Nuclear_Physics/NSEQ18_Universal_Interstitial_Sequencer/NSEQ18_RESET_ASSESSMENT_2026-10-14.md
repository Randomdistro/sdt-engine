# NSEQ18 (universal interstitial sequencer), Round 2 — registration and assessment (2026-10-14)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Sections 0–3 are the registration, written **before** `nseq18_reset_2.js` exists. Sections 4 onward are filled in after the run. The engine is read, never edited (Release and docs are the objects under test).

## 0. Inputs read and exposure
Read: the rewritten `PROMPT.md` (state after the reset; the live-sequencer findings; O1–O3; prohibitions) and the kept specification's acceptance list and gates; `NSEQ18_RESET_ASSESSMENT_2026-10-10.md` (deferral); `NP17_.../nseq_cascade_1.js` (template: set construction, AME/NUBASE parsing, ledger access); `NP12f_.../NP12F_ROUND2_RECORD_2026-10-12.md` (the O3 supplier); the engine's `evaluate`, `universalObservableLedger`, `buildNuclide`, `selfTest` and export list.

Exposure, stated plainly: the prompt prints the findings this round re-measures (23 of 173 isotope steps wrong-sign; μ(⁴He) = 1.65 μN; every A ≥ 4 graph is one 4-ring plus a tree; EC isotopes refused). O1 and O2 are therefore **post-seen re-measurements**, registered as such. I did not open `CASCADE_ASSESSMENT_2026-10-11.md`, `nseq18_results.json`, `nseq18_universal_validate.js` or `raw_sequencer_validate.js`.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | set definition | The old specification counts "every public sequencer isotope" (221 nuclides); the cascade set is the NUBASE2020 stable ground states the grammar admits (250) plus ³H. The 173 in "23 of 173 isotope steps" is not defined in the prompt. This round registers its own definition (Section 2) and reports both counts; a difference from 173 is a definition difference to be stated, not a result. |
| D2 | untoleranced gates | The old acceptance item 9 ("wake conservation and route-agreement tolerances pass") carries no number. I commit one now (Section 2) before any value is computed and mark it as my choice. |
| D3 | not runnable here | Acceptance items 10 (no text labels in the 3D model) and 11 (datasheet exposes calculated, measured, residual) are properties of the web page, not of the engine object. They need a browser session and are **not run**. |
| D4 | O3 supplier | O3 (radii) is answered by NP12f round 2 (2026-10-12): median ρ 27.3 % over A ≥ 40 against a 10 % gate, **not met**, and 51 % of 761 chain steps have the opposite sign to the measured change. It is cited, not re-run. |

No downgrade is made on agreement grounds.

## 2. Registered gates and definitions (fixed before the run)
**Set S.** NUBASE2020 ground states flagged stable (`stbl`, isomer index 0) with A ≥ 2 whose `grammar(A,Z)` is valid, plus ³H (the registered seed); sorted by A then Z (the `nseq_cascade_1.js` construction). Spot nuclides built regardless of stability: H-1, H-2, H-3, He-3, He-4, O-16, Ca-48, Fe-56, Pb-208, U-238 (refusals recorded as such).

**Per-nuclide acceptance (from the kept specification, items 1–3 and 7–9).** For each member of S, `buildNuclide(Z, A, {Rp: 0.8414})` (the cascade's R_p) and `evaluate`:
- A1 builds without error, and a second build gives the same node/contact content (deterministic);
- A2 nucleon count = A and proton count = Z;
- A3 the shell allocation reproduces n_t = A − 2Z and n_d = 3Z − A − 2 (where the grammar is the standard one);
- A4 `tractionConsistent`: connected, every unit touched, unlike contacts only, 0 like-like touches, 0 unlisted touches, max contact residual ≤ 1×10⁻¹⁰ and max slip < 1×10⁻¹⁰;
- A5 wake: split, rejoin and paired-flux residuals each ≤ 1×10⁻³ and maximum relative divergence ≤ 1×10⁻² (**my committed tolerance, D2**), reported with the actual values.
Whole-set acceptance = every member passes A1–A5.
- A6 (acceptance item 12): the engine and `nuclear-inputs.js` are byte-identical between `Release/HTML_SDT_Website/js` and `docs/js`.

**O1.** For each Z, take the members of S in increasing A and the calculated zero-fit binding B_calc from `observableLedger.massDefect.calculatedBindingMeV`. Each consecutive pair gives an increment ΔB = B_calc(A′) − B_calc(A). Gate: **every ΔB > 0** (zero non-positive increments). Members whose ledger is the calibrated seed fit (no zero-fit ledger) are excluded from the steps and counted. Two step counts are reported: consecutive-member steps (stable-set chains) and ΔN = 1 steps only.

**O2.** For every even-even member of S (Z and N both even) with a zero-fit ledger: ρ = |μ_calc|/μ_p with μ_p = 2.79284734463 μN. Gate: **ρ ≤ 1×10⁻³ for every one** (measured μ = 0 for all of them; band B1). ⁴He is reported separately (seed, ledger present or not as the engine returns it).

**O3.** Cited from NP12f round 2 (D4): not met.

**Repairs** are proposals only (Section 6), none applied.

**Hand estimates before the run.** A1–A4 expected met for the whole set (the prompt and the cascade built all 250). O1 expected to fail with about 23 non-positive increments among about 173 steps (the prompt's count; mine may differ by D1). O2 expected to fail for ⁴He (1.65 μN, ρ = 0.59) and probably for most even-even members, because the tree-plus-4-ring graphs are not symmetric under the contact-rotation sum. A5 unknown: the wake residuals come from the single-nucleon diagnostic and may be the same for every nuclide.

**Label in advance:** the result is a verification of a construction (COMPUTED, NOT a physics claim); pass or fail of O1/O2 says what the sequencer does, not what nuclei do.

## 3. Prohibitions applied
No census over candidate predictors; grammar counts are not evidence (NP24); no data substitution; the Release engine is read only; the word "charge" is not used.

## 4. Results (`nseq18_reset_2.js`, single pass, about 35 min; output `nseq18_reset_2_results.txt`, per-nuclide rows `nseq18_reset_2_rows.csv`; engine NSEQ18-WEB-1)
Set S has **253** members (not the cascade's 251: the stable-ground-state list also admits ²H and ³He, which are seeds).
- **A1–A4 met for all 253:** deterministic (second build gives the same fingerprint), nucleon and proton counts exact, n_t/n_d reproduce the grammar, `tractionConsistent` true (connected, unlike contacts only, 0 like-like, 0 unlisted touches, residual ≤ 1×10⁻¹⁰, slip < 1×10⁻¹⁰).
- **A5 met, but trivially (see Section 5).** Split, rejoin and paired-flux residuals are exactly 0 and the maximum relative divergence is 3.728×10⁻³ for every member.
- **A6 met:** the engine and `nuclear-inputs.js` are byte-identical in Release and docs.
- **O1 NOT MET:** 171 consecutive-member steps (zero-fit ledgers), **23 non-positive**; ΔA = 1 steps: 102, 10 non-positive. The prompt's "23 of 173" is reproduced in the numerator and differs by 2 in the denominator (D1: its step definition is not given; mine excludes the three calibrated seeds).
  - Non-positive steps run from −0.14 MeV (⁶⁹Ga→⁷¹Ga) to −27.1 MeV (²⁰⁷Pb→²⁰⁸Pb); the largest are at ¹⁶⁴Er→¹⁶⁶Er-class steps in the rare earths (−11 to −18 MeV, Z = 62–70) and at ²⁰²Hg→²⁰⁴Hg (−19.9) and ²⁰⁷Pb→²⁰⁸Pb (−27.1).
- **O2 NOT MET:** 0 of 147 even-even members have ρ = |μ|/μ_p ≤ 10⁻³. Median ρ = 3.22 (3.2 proton moments), minimum 0.078, maximum 7.9; largest |μ|: ⁹⁶Ru 22.1 μN, ¹⁰⁶Cd 21.4, ⁵⁸Ni 21.2, ⁹²Mo 20.3, ⁷⁸Kr 19.9. ⁴He: 1.6506 μN (as in the prompt). The moment of a nucleus whose measured moment is zero is a sum that grows with A instead of cancelling.
- **O3** (cited, NP12f round 2, 2026-10-12): not met (27.3 % median radius error for A ≥ 40; 51 % of chain steps with the wrong sign).
- Spot nuclides all build with `tractionConsistent` true; ²³⁸U builds (contacts = A = 238). Calibrated seeds (²H, ³H, ³He) carry no zero-fit ledger; ⁴He does (B_calc 11.69 MeV, μ 1.6506 μN).

## 5. What the results say, and what they do not
- **Construction geometry is sound; the observable ledger is not.** All 253 builds satisfy every geometric acceptance gate; both ledger gates (O1, O2) and the radius gate (O3) fail by a wide margin. That separates the contact-and-seat construction (A1–A4) from the wake-coupling ledger that sits on it.
- **A5 is not a per-nuclide gate.** In `universalObservableLedger` the wake residuals come from `h1WakeDiagnostics(0)`, a single-nucleon diagnostic called with a fixed argument, so every nuclide returns the same numbers. The registered A5 therefore cannot fail and tests only the H1 nucleon. A per-nuclide wake-conservation measure does not exist in the engine's return value; it is owed (proposal P3).
- **A3 is close to tautological:** the shell allocation uses the same two formulas the gate checks. It confirms the build follows the grammar, not that the grammar is right (NP24: grammar counts are not evidence).
- **O1 pattern:** 10 of the 23 non-positive steps are ΔA = 1 steps and 13 span ΔA ≥ 2 (a skipped isotope sits between the two members). The magnitudes are largest in the heaviest and rare-earth chains. Which structural change causes the drop (a triton-shell closure, a contraction step, a change of the tree attachments) was not isolated here; the prompt and the 2026-10-11 cascade attribute it to contraction multiplying binding while also lowering the wake coupling, and this run neither supports nor contradicts that attribution.
- **O2 pattern:** |μ| scales with A and with the number of contacts (0.078 to 7.9 proton moments), which is the signature of a contact-rotation sum without a pairing cancellation; the engine has no rule that makes paired like units cancel.
- Label: a verification of the construction's behaviour (COMPUTED). It makes no statement about nuclei.

## 6. Repair proposals (not applied; Release and docs not touched)
- **P1 (O1).** Trace the sign of d(B_calc)/dN against the contraction factor along one chain (Z = 82, A = 204…208 is the cleanest: three steps, one of them −27 MeV) by recording `contractionScale`, `fullTritonClosures` and `wakeCoupling` for each end. Then decide whether contraction should divide rather than multiply (NP12f's chain diagnostic points the same way). Owed: NP17 round-2 O1 rule.
- **P2 (O2).** A pairing rule for like units is needed before the magnetic integral can vanish for even-even nuclei; the prompt records no native pairing rule, so none is proposed.
- **P3 (A5).** Return per-nuclide wake residuals from the actual composite mesh rather than from the single-nucleon diagnostic.
- **P4 (gate 10, 11).** Browser session to read the 3D label and datasheet items (D3).

## 7. Grades
| Item | Grade |
|---|---|
| A1–A4 geometric acceptance, 253 builds | **met** |
| A5 wake tolerance | **met trivially** (single-nucleon diagnostic repeated; not a per-nuclide test) |
| A6 mirror identity | **met** |
| O1 positive binding increments | **NOT MET** (23 of 171 steps; 10 of 102 at ΔA = 1) |
| O2 μ(even-even) = 0 | **NOT MET** (0 of 147; median 3.2 μ_p) |
| O3 radii | **NOT MET** (NP12f round 2, cited) |
| Acceptance items 10, 11 | **not run** |
| Release | unchanged |

## 8. Comparison with the archived record
Deferred to the end-of-programme comparison pass.

## 9. Addendum (2026-10-14, after the run): Harvey's slot rule
Rule stated by Harvey: every proton has three neutron slots and every neutron three proton slots (so a deuteron has two free proton slots and two free neutron slots; a triton has one free neutron slot and four free proton slots). The slot rule bounds every unit's contact degree at 3; it does not fix the number of contacts, only the capacity (edges ≤ 3·min(Z, N)).

My Round-2 text called "contacts = A" expected. That was wrong: E = A is the engine's tree-plus-ring result, listed as a defect in the prompt, not a property of nuclei, and gate A4 did not test degree.

Post-seen diagnostic (`scratchpad/slots.js`, same engine, R_p 0.8414), built degree against the 3-slot limit:
| nuclide | contacts built | slot capacity | max degree built | units over 3 slots |
|---|---|---|---|---|
| ²H | 1 | 3 | 1 | 0 |
| ³H | 2 | 3 | 2 | 0 |
| ⁴He | 4 | 6 | 2 | 0 |
| ¹⁶O | 16 | 24 | 5 | 1 (one proton at 5) |
| ⁴⁰Ca | 40 | 60 | 7 | 5 (p: 4, 5; n: 4, 7, 7) |
| ⁴⁸Ca | 48 | 60 | 6 | 3 (p: 6; n: 5, 5) |
| ⁵⁶Fe | 56 | 78 | 7 | 5 |
| ²⁰⁸Pb | 208 | 246 | 7 | 8 (p: four at 4, one at 6; n: one at 4, two at 7) |

Two separate defects follow: (1) the engine builds units with 4 to 7 contacts, which a three-slot unit cannot have; (2) it leaves slots unfilled (¹⁶O uses 16 of 24 possible contacts). Whether more contacts are then filled, and which, is not fixed by the slot rule and is not proposed here. Gate A4 should add "every unit's degree ≤ 3" (new proposal P5); with it, the geometric acceptance for all nuclides with A ≥ 16 is **NOT MET** by this diagnostic for the five nuclides listed (the full set was not re-scanned).

## 10. Engine change and natural-isotope construction check (2026-10-14, registered before `nseq18_natural_1.js` exists)
**Engine change (Harvey's instruction, applied to Release and docs, byte-identical; pre-change copy kept in the session scratchpad, git holds the original):** `traction-gear-engine.js` now enforces the three-slot contact rule: a unit never has more than 3 contacts; a contact is any unlike pair at centre distance 2R_p and every such touch is listed (`kind: 'contact'`); like-type touches and overlaps invalidate a placement; docking anchors must have a free slot; `evaluate` reports `maxDegree`, `unitsOverSlots` and includes `unitsOverSlots === 0` in `tractionConsistent`. Placement still docks one unit per module along the registered seat axes. Validation before applying: all 253 members of S build with A1–A4 met (contacts differ from A by −1 to +9; mean +3.7). Not done: placing a module so that it touches two or three neighbours at once. A first attempt filled every slot in two modules, closed the cluster, and ¹⁶O could not be built beyond seat 3, so it was not applied. How contacts fill in shell order, and how far a module may sit from its seat axis, is Harvey's to rule.

**Harvey's scope ruling (2026-10-14):** "natural isotopes" first, then stable manufactured isotopes, then unstable isotopes one position (±1 in Z or N) from a stable one; "stable" in two stages, (1) construction holds, (2) the engine's own stability call. Caveat stated by Harvey: the mass gap behind "binding energy" is a measurement artefact (a kilogram of water and a kilogram of iron are the same number of baryons; nothing in the arrangement or density earns a bonus or a penalty), so stage 2 may **not** rest on a binding or mass-defect comparison. No native structural stability criterion is on file; stage 2 is therefore not started.

**Stage 1 for the natural set (this section).** Natural set = the NUBASE2020 stable ground states the grammar admits (S without the registered ³H seed) plus the primordial radionuclides: ground states with half-life ≥ 7×10⁸ y (units Gy and longer, and My with value ≥ 700, which brings in ²³⁵U). Gate: every member builds deterministically with A1–A4 as before (count, grammar, `tractionConsistent` including the degree rule). Report contacts, max degree, members refused. No ledger value is read.

**Harvey's half-life tiers (2026-10-14), the target classification for stage 2.** Half-life below 1 000 y: **highly unstable**. From 1 000 y up to 10⁹ y: **unstable**. Longer than 10⁹ y (and every stable ground state): **may persist to the end in some capacity** (tier P). This is a classification of measured half-lives (NUBASE2020), not a model criterion; it says what the engine's stability call must reproduce, not how the engine reaches it, and the how is still open. Consequence for the natural-set run above: its primordial cut was written as 7×10⁸ y (the usual primordial edge), so ²³⁵U (7.04×10⁸ y) enters the run but sits in the unstable tier, not tier P; every row will be labelled with its tier after the run. Tier P is the first target; the one-position neighbours (±1 in Z or N) of tier-P members are the next set, each expected in the highly-unstable or unstable tier.

**Result, natural set stage 1 (`nseq18_natural_1.js`, output `nseq18_natural_1_results.txt`, rows `nseq18_natural_1_rows.csv`).** All **252** stable ground states (A ≥ 2) and all **32** primordial radionuclides build on the live engine with the contact rule met (counts exact, `tractionConsistent`, no unit above 3 contacts, max degree 3 everywhere); none refused. Contacts minus A: −1 to +9 (stable), 0 to +9 (primordial). Tiers: 283 members in tier P (252 stable plus 31 radionuclides above 10⁹ y); ²³⁵U (7.04×10⁸ y) is in the unstable tier. **Scope:** this is stage 1 only (the construction holds). It says nothing about whether the engine calls any of them stable (stage 2, open: no native criterion). Next sets in Harvey's order: stable manufactured isotopes, then the ±1 neighbours.

## 11. O-18 seat tritonisation (Harvey's proposal; registered 2026-10-14 before `o18_enumerate.js` exists)
**Proposal (Harvey, stated as a loose generalisation that may or may not be true).** ¹⁶O and ¹⁸O may both have a deuteron at the oxygen seat; the two extra neutrons of ¹⁸O arrive as two of the lower deuterons being tritons (n_t = A − 2Z = 2, n_d = 3Z − A − 2 = 4), and two ¹⁸O nuclei may differ in which lower seats are tritons. Only contact-allowable constructions. Question: which seats have the potential to be tritonised?

**What the live engine does with ¹⁸O.** `universalShellAllocation(4, 2)` fills the D6 shell with 4 deuterons (two seats vacant) and puts the 2 tritons in the next triton shell (T8), i.e. outside, not at the lower seats. The proposal is a different assignment: all six D6 seats occupied, two of them by tritons.

**Instrument.** A variant of the live engine (`nseq18_variants/traction-gear-engine_seatKinds.js`, derived from the current Release file by `make_patch3.py`; Release not touched) accepts `options.seatKinds`, an array of `'d'`/`'t'` over the six seats of a single full D6 shell in construction order. Everything else is the live engine: the same seat directions, the same sequential placement (docking and touch listing under the three-slot rule), the same `evaluate`. All C(6,2) = 15 triton-seat pairs for ¹⁸O are built; also ¹⁶O (no tritons) and ¹⁷O-free controls are not run (¹⁷O has an odd count the grammar does not admit as d/t only).

**Gates and outputs (fixed now).**
- Per assignment: builds or is refused (and at which seat the refusal occurs); if built, nucleon count 18, protons 8, `tractionConsistent` (only unlike contacts, degree ≤ 3, no overlap, connected), contact count, degree histogram.
- Per seat: it **can be tritonised** if at least one contact-allowable assignment has a triton there. Reported with the symmetry classes the six seat directions form (computed from the seat directions, not assumed).
- Control: the all-deuteron ¹⁶O build reproduces the current engine's ¹⁶O (contacts 16, max degree 3).
- No ledger value (binding, moment, radius) is read or reported; this is a construction answer only.

**Hand estimate before the run.** Placement is sequential, so a triton (three units long) at an early seat may leave later seats with no contact-safe position; some of the 15 assignments will be refused, and which seats are tritonisable will depend on construction order, not only on geometry. I do not expect all 15 to build.

**Result, section 11 (`o18_enumerate.js`, output `o18_enumerate_results.txt`; engine variant `nseq18_variants/traction-gear-engine_seatKinds.js`).**
- The six seats of the full D6 shell are the octahedral directions ±z, ±x, ±y, in construction order (+z, −z, +x, +y, −x, −y). By direction alone they are **one symmetry class**: all six seats are equivalent.
- Control: all-deuteron ¹⁶O through the variant gives contacts 16, max degree 3, `tractionConsistent` true, identical to the live engine.
- **13 of the 15** triton-seat pairs build and satisfy the contact rule (18 nucleons, 8 protons, only unlike contacts, degree ≤ 3). The two refusals are tritons at seats (1,2) [the two poles] and (2,3): "no contact-safe triton placement" at seat 2 and seat 3.
- Each of the six seats can be a triton in at least 3 of its 5 assignments (seats 4, 5, 6 in 5 of 5; seats 1 and 3 in 4 of 5; seat 2 in 3 of 5). **Every seat has the potential to be tritonised.**
- The refusals are order effects, not geometry: the opposite pair (1,2) is refused while the equally opposite pairs (3,5) and (4,6) build, and the adjacent pair (2,3) is refused while the other adjacent pairs build. The cause is the sequential, greedy docking in the engine (earlier modules take the contact positions a triton needs), not a property of the octahedron.
- Contacts per build: 18 or 19 (A or A + 1); most slots stay open, so these are contact-allowable, not slot-saturated. Assignments with a triton at seat 1 gain one extra listed contact.
- Number of seat-assignments with seat 6 (the last placed, the oxygen seat in construction order) a deuteron: 8 of the 13 that build.
- Scope: construction only; no ledger value read; the engine's own answer for ¹⁸O (D6 with 4 deuterons, two seats vacant, tritons in the outer T8 shell) is a different structure and is not what this enumeration tests.

## 12. Correction to sections 9–11: the contact test is not a solid-body test (Harvey, 2026-10-14; audit `solid_audit_1.js`, output `solid_audit_1_results.txt`)
Harvey: the units are solid objects; passing numerically does not mean they fit without jamming or damaging each other. Audit of what the engine's test actually checks:
- **Centre distance only.** A "contact" is two unit centres at 2R_p; "overlap" is centres closer than that. The H1 nucleon is a thin ring: centreline radius 0.9987 R_p, helix radius 0.0504 R_p, strand radius 0.0357 R_p, outer envelope **1.0848 R_p**. Two rings in the same plane at centre distance 2R_p have centreline gap 0.0025 R_p against a strand diameter of 0.0713 R_p, so their strands overlap unless the helices mesh; no test checks that. The envelope (1.085 R_p) exceeds the exclusion radius the placement uses (1.000 R_p).
- **One orientation for every unit.** The ledger poses of every unit in ¹⁶O, ⁴⁰Ca, ⁵⁶Fe and ²⁰⁸Pb carry the same orientation (0, 0, 0, 1): all rings share one axis (z), whatever their contacts.
- **Contacts out of the ring plane.** A rim contact between two rings spinning about z needs the line of centres to lie in the ring plane. Contacts with |n_z| > 0.05 (the line of centres tilted out of the plane): ¹⁶O 4 of 16; ⁴⁰Ca 22 of 40; ⁵⁶Fe 38 of 56; ²⁰⁸Pb 175 of 216; with |n_z| > 0.9 (rings stacked along their common axis, which cannot touch at the rim): 2, 6, 6 and 34.
- **The slip gate cannot fail.** For an unlike pair the two rim velocities are equal for any contact direction (opposite hands cancel the sign of the opposite normal), so slip is 0 whatever the geometry; max slip is exactly 0 in all four nuclei, including the contacts that cannot be rim contacts. Gate G3 and the A4 slip clause are therefore vacuous for orientation.
- **Consequences.** (i) "Contact-allowable" in sections 9–11 means centre-distance-allowable under the 3-slot degree cap, nothing more. (ii) The section 11 answer (13 of 15 ¹⁸O assignments build; every seat can be tritonised) is a point-and-sphere result; it is not evidence that the solid rings fit or turn. (iii) The earlier "slip < 1e-10" results of NSEQ16 G3 and NSEQ18 A4 stand as arithmetic and carry no weight as a kinematic test.
- **What a solid test needs (proposal, not run).** Each unit as its real strand curve with a stated orientation; a rim contact only if the contact normal lies in both rings' planes; a unit with three contacts then needs its three contact normals in its own ring plane (three slots in the plane, e.g. 120° apart is the natural reading, **to be confirmed by Harvey**); minimum strand-to-strand distance ≥ 2 × strand radius for every pair at the build pose; and the same distance checked through a full phase-locked rotation of all units over one period (the jam test). Until then, no build in this section counts as fitting.
