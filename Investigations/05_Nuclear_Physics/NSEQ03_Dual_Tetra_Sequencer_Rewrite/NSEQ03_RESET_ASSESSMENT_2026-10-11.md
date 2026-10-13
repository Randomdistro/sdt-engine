# NSEQ03 (dual-tetra triton seating applied to the sequencer) — blank-slate assessment (2026-10-11)

Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md` with the method of 2026-10-07. Sections 0–2 are the registration, written before `nseq03_reset_1.js` exists.

## 0. Inputs read and exposure
Read: `NSEQ03/PROMPT.md` in full (claims C1–C5 and the 2026-10-05 audit correction); the NSEQ02 and NSEQ05 records of this programme; the live files `Release/HTML_SDT_Website/js/pack-nucleus.js` (261 lines, read in full) and the script and label lines of `nuclear-packing-sequencer.html`. Not read: `NSEQ03_ASSESSMENT.md`, `nseq03_dual_tetra_rewrite.py`, `PROPOSE_LAWS_HPP_BELT_NOMENCLATURE.md`, `traction-gear-engine.js` beyond a word search. Exposure: the `Release` and `docs` copies of the sequencer are byte-identical (MD5 92e9739ac9d9d2eee598354e33393990, 121 500 bytes); the module `pack-nucleus.js` states in its own header that it is the "legacy NSEQ05 geometric comparison control", version `NSEQ05-CONTROL-3`, classification `LEGACY_GEOMETRIC_CONTROL`, "not the Atomicus nucleus"; the live canonical path builds its model in `traction-gear-engine.js` (labelled NSEQ18) and falls back to "legacy shell templates".

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | construction | C1–C5 are code-state checks (the audit correction: unit tests of the sequencer, kept out of the physics tally). They are VERIFICATION rows; none can fail except by a code defect. |
| D2 | record | The module that C1–C4 describe (`pack-nucleus.js`) is the legacy control, no longer the canonical nucleus builder. The claims are tested on that module, as the code the claims name, and the status is recorded as such. C1 ("site and docs sequencers use dual-tetra shells") is tested as: the two copies are identical, both load this module, and its T8 shell is the dual-tetrahedron layout. Whether the canonical (NSEQ18) path seats triton shells the same way is a separate question (not decided here). |
| D3 | gating | "First shell" in C3 is ambiguous for Ca-48: its first shell in schedule order is deuteron (D6). Registered: the first triton shell, T8 (n_t = 8, n_d = 10 so D6 and a partial D12-pre precede it). |
| D4 | gating | C2 is a counting identity (nucleons = A, protons = Z) that the grammar guarantees if the module follows it; tested for He-4, C-12, O-16, Fe-56, U-238 (and Ca-48). |
| D5 | record | C5 (`laws.hpp` not edited) is checked read-only against the repository's working-tree status for that file. |
No downgrade is made on agreement grounds.

## 2. Registered tests (fixed before the run; read-only; node runs the module unmodified)
**T1 (C1).** MD5 equality of `Release/…/nuclear-packing-sequencer.html` and `docs/…`; both reference `js/pack-nucleus.js`; vocabulary scan of the HTML and the three scripts for `BELT_PAIRS`, `beltPlane`, `belt` (expected: none).
**T2 (C2).** `packNucleus(A, Z)` for (4,2), (12,6), (16,8), (40,20)… with Ca-48 = (48,20), (56,26), (238,92): number of nodes = A and number of nodes with type `p` = Z; `grammar` returns n_d, n_t equal to 3Z − A − 2 and A − 2Z.
**T3 (C3).** Ca-48: the T8 shell. Extract its eight seats (the proton node of each triton, by `group`, `sub` and the `subSeq` entry labelled T8): unit directions; test (a) the second-moment tensor of the eight directions has no zero eigenvalue (non-coplanar; expected isotropic, eigenvalues 8/3 each), (b) both poles (0,0,±1) are among the directions, (c) the pair-angle histogram is 12 × 70.5288°, 12 × 109.4712°, 4 × 180° (the NSEQ02 layout), (d) the mean radius of the even (opening) seats exceeds that of the odd (closing) seats and their ratio is 1.05/0.95, (e) the opening seats (even indices) are the north pole and three southern-band seats at z = −1/3, the closing seats the south pole and three northern-band seats at z = +1/3.
**T4 (C4).** `SDT_NUCLEAR_PACKING.shellSequence`: the triton capacities 8, 10, 12, 14, 16, 18 and the deuteron capacities 6, 12, 12, 20, 30, 42, 56 (the NSEQ05 schedule); the cumulative totals 2, 8, 20, 28, 40, 50, 70, 82, 112, 126, 168, 184 recomputed with the α core as 2.
**T5 (C5).** Working-tree status of `Engine/include/sdt/laws.hpp` (no modification relative to the last commit) and the presence of the nomenclature-proposal file (listing only).
**Validations.** V1: the module loads in node without a browser global (it attaches to `globalThis`). V2: for He-4 the module returns the 4-node α core with 2 p and 2 n. V3: the NSEQ02 layout from the module's `dirsPolar` construction reproduces the NSEQ02 histogram (T3c is that test applied to the live module).
**Outcome form.** VERIFICATION rows, each met or not met; no physics grade.
**Expected landing.** All met for the legacy control (the construction was read before registering and agrees with NSEQ02's layout); the HTML vocabulary scan finds no belt terms; the canonical NSEQ18 path is not tested.

## 3. Results (COMPUTED; harness `nseq03_reset_1.js`, output `nseq03_reset_1_results.txt`; single pass, no amendment; exit 0)
**Validations.** V1 met (the module loads under node, attaching `packNucleus` and `SDT_NUCLEAR_PACKING`); V2 met (He-4: 4 nodes, 2 p, 2 n). Module identity as printed: version `NSEQ05-CONTROL-3`, classification `LEGACY_GEOMETRIC_CONTROL`, `contactGeometry` false.
**T1 (C1).** The Release and docs sequencer files are identical (MD5 92e9739ac9d9d2eee598354e33393990); the HTML loads `js/pack-nucleus.js`. Vocabulary scan: `BELT_PAIRS`, `beltPlane`, `belt` occur 0 times in the HTML, `pack-nucleus.js`, `nuclear-inputs.js` and `traction-gear-engine.js`. "stella" occurs 0 times in the HTML, 2 in `pack-nucleus.js`, 1 in `nuclear-inputs.js`, 1 in `traction-gear-engine.js`: the canonical engine files still carry the stella seating vocabulary (which of them seats triton shells with it was not read).
**T2 (C2).** Nodes = A and protons = Z with n_d = 3Z − A − 2, n_t = A − 2Z for He-4 (0, 0), C-12 (4, 0), O-16 (6, 0), Ca-48 (10, 8), Fe-56 (20, 4), U-238 (36, 54): all met.
**T3 (C3), Ca-48.** Shells: α core 1/1 | D6 6/6 | D12-pre 4/12 | **T8 8/8**. The eight T8 seats: second-moment eigenvalues 2.666667 ×3 (non-coplanar, isotropic) [3a]; both poles present [3b]; pair angles 12 × 70.5288°, 12 × 109.4712°, 4 × 180°, none other [3c], the NSEQ02 layout; opening (even) seats' mean radius 8.34308 > closing 7.54850, ratio 1.105263158 = 1.05/0.95 [3d]; opening tetrahedron = north pole + 3 seats at z = −1/3, closing = south pole + 3 seats at z = +1/3 [3e]. Seat distances (fm, at the shell radius): opening–opening 13.6242, closing–closing 12.3266, opening–closing 9.1979 to 15.8916; nearest cross distance / opening edge = 0.6751 (the unit-radius value of NSEQ02, 1.1576/1.7146, rescaled).
**T4 (C4).** Triton capacities 8, 10, 12, 14, 16, 18 and deuteron capacities 6, 12, 12, 20, 30, 42, 56: met. Cumulative totals (α core = 2): 2, 8, 20, 28, 40, 50, 70, 82, 112, 126, 168, 184, then 240, 258 (D56, T18).
**T5 (C5).** `Engine/include/sdt/laws.hpp` has no working-tree modification (clean); the nomenclature proposal file is present.

## 4. Grades
| Item | Grade | Reason |
|---|---|---|
| C1 site and docs use the dual-tetra seating | **VERIFICATION, met for the legacy control** | the two copies are identical and load `pack-nucleus.js`, whose T8 shell is the dual-tetrahedron layout; the vocabulary of the retired belt orientation is absent |
| C2 packing counts | **VERIFICATION, met** | six nuclei, nucleon count = A and protons = Z |
| C3 Ca-48 T8 shell | **VERIFICATION, met** | non-coplanar, poles present, 12/12/4, r_open > r_close at 1.05/0.95, and the layout equals the NSEQ02 construction (V3) |
| C4 capacities | **VERIFICATION, met** | schedule counting unchanged |
| C5 canon untouched | **VERIFICATION, met** | `laws.hpp` clean |
All rows are unit tests of a legacy control (D1, D2) and are outside the physics tally. Status of the tested module: `LEGACY_GEOMETRIC_CONTROL`, "not the Atomicus nucleus" (its own header).

## 5. Direction
1. The claims are true of the module they name; the canonical tool now builds its model in the NSEQ18 traction engine. A test that the canonical path seats triton shells in the same dual-tetrahedron layout (the 12/12/4 histogram on the engine's own T8 seats) is owed and belongs with NSEQ15–18.
2. The seat-radius rule (1.05 and 0.95) is a fixed ratio of the control, not derived (NSEQ02 recorded that the radius rule restates its inputs).
3. The harness is read-only and re-runnable: `node nseq03_reset_1.js`.

## 6. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
