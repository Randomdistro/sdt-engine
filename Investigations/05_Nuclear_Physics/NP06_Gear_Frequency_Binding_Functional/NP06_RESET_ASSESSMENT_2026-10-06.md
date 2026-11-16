# NP06 — blank-slate assessment (2026-10-06)

> **ANNOTATION — 2026-10-07, at Harvey's direction (see the NP14 withdrawal).** The census parts of this record (T2, T3: products of fractions and α searched for agreement with the measured deuteron binding energy; T4: αc/r over eight lengths) are the same comparison-seeking method as the withdrawn NP14 run: they start from the measured number and ask which constructions land on it. They are withdrawn as evidence. What stands from this record: the prompt's Δω has no native definition in the repo (G2, open); no mesh-kinematic definition was derived; E_bind/ħ = αc/r is E divided by ħ for a Coulomb-scale well (CONSTRUCTION). The G1 label on "P1 as an α-free statement" rested on the census and is withdrawn; the open requirement is a native definition of Δω from the relay kinematics (FLM07/FLM10), registered and computed before any comparison with the measured binding.


Protocol: `Investigations/RESET_2026-10-06/PROTOCOL.md`. Run 1.

## 0. Inputs read before the pre-registration, and exposure
Read: `NP06/PROMPT.md` (including its 2026-10-05 correction block); `laws.hpp` (`measured`: `B_deuteron`, `R_p`, `r_e`, α, c, ℏ; `bridge::k_proton_surface`); the dependency graph (NP06 is layer 0, reach 107; consumers NP17 and FD10; no supplier among the investigations). Not read: `NP06_ASSESSMENT.md`, `RUN_LOG.md`, `np06_arithmetic.py`, `np06_arithmetic_results.txt`, any NP17 or NP31 file.
Exposure: the prompt states numbers before any run (`E_d/ℏ = 3.38×10²¹ rad/s`, `Ω_rim = 1.83c/R_p = 6.52×10²³ rad/s`, ratio 5.2×10⁻³, "29% off α") and the geometry "two trefoils locked at D = 2R_p + R_p/3, shared electron at the node". The author evaluated, before writing §4, that a product of three factors 1/4 and one factor 1/3 equals 1/192 = 5.208×10⁻³, close to the prompt's ratio. The registered grammar below reports every factor count m = 1…5 and fixes the criterion on m = 3 (three constants are named in the prompt's own geometry: the 2, the 1/3 and W = 3); m = 4 was deliberately not selected as the primary because of that exposure.

## 1. Prompt analysis
| # | Class | Observation |
|---|---|---|
| D1 | premise | Δω ("the change in meshed circulation rate when the structures lock") has no definition in the repo. The prompt's correction block states that P1 cannot be run without inventing the quantity under test. |
| D2 | record | The prompt's "owed pointer" to a result showing the gear frequency to be the movement of the binding does not resolve to a file; none is cited. |
| D3 | construction | For a Coulomb-scale well αℏc/r, E/ℏ = αc/r by division. A Δω built as "αc over a geometric length" reproduces a well of that scale by construction; the prompt's own warning (computing Δω from E) applies to it. The content of P1 is a Δω built from the rim kinematics (Ω_rim) without a Coulomb-scale factor. |
| D4 | gating | Ω_rim = c·√(r_e/R_p)/R_p contains α through r_e = α²a₀ (`laws.hpp:130`, `:963`); "α-free" below means no additional α beyond the one inside Ω_rim. |
| D5 | premise | The dependency direction is stated two ways: the graph lists NP06 → NP17; the prompt says NP17 supplies the energy side and NP06 the movement side. Class: NP06 → NP17 `required` per the graph; NP17 → NP06 `cross-check` (comparator only). |
| D6 | gating | P3 (He-3, α) needs NP31's coordination and NP17's geometry; the prompt names both. |
No downgrade is made on agreement grounds.

## 2. Dependencies
**Suppliers:** none among the investigations (graph); NP17 well (comparator) and NP31 (P3) per the prompt. **Dependents:** NP17, FD10 (graph). Edges as D5.

## 3. Hypothesis, observable, ledger
H: a Δω defined from the locked-mesh geometry and the rim kinematics, with no E and no additional Coulomb-scale factor, satisfies ħΔω(deuteron) = B_d within ±5% (P1); its ratio to Ω_rim is a named native quantity (P2); the same rule holds for A = 3, 4 within ±10% with no per-nucleus adjustment (P3).
Observable: r_t = B_d / (ħ Ω_rim). Data: `measured::B_deuteron` (OBSERVED anchor, from CODATA masses in the engine). Ledger: B_d measured-input (anchor); R_p measured-input; α, a₀, c, ℏ engine constants; no calibrated parameter; the candidate grammar is a registered selection (look-elsewhere count reported).

## 4. Pre-registration (written before `np06_reset_1.cpp` exists)

**Validations (not met ⇒ G0).**
- V1 (units, known answers): ℏc = 197.327 MeV fm to 1e-5; hydrogen: ħ(αc/a₀) = α²m_ec² = 27.211 eV (the Hartree energy) to 1e-6; the prompt's numbers E_d/ℏ = 3.38e21 rad/s, Ω_rim = 6.52e23 rad/s and r_t = 5.2e-3 reproduced to 1.5%.
- V2 (census machinery): on a synthetic grammar with a planted candidate at a stated value, the band count finds it; and for 20000 log-uniform random numbers over 6 decades the sliding-band mean count equals N × (band width in log10)/(span) within 5%.

**Tests.**
- T1 (COMPUTED): r_t and the band [0.95, 1.05] × r_t. The rim rate Ω_rim and the base c/R_p (second base, r_t' = B_d/(ħc/R_p)).
- T2 (COMPUTED, census, P1/P2): α-free grammar: Δω = base × ∏_{i ≤ m} f_i, f_i ∈ F_geo = {1/2, 1/3, 1/4, 1/6, 3/7, 7/3, 2, 3, 4, 1/√2, 1/√3} (the numbers appearing in the prompt's geometry and W, W+1, with the radicals of the budget partition), m = 1…5, distinct values only. Count the candidates inside the band for each m and each base; chance baseline by sliding a band of the same relative width over log-uniform positions within the 5th–95th percentile of the candidate values; report the observed count, the mean count at random positions, and the fraction of positions with count ≥ the observed. Criterion R1 (P1 gate): P1 is rejected as an α-free statement if the m = 3 count with base Ω_rim is 0. Criterion R2: agreement within ±5% is non-discriminating if the m = 3 count is ≥ 3 or the chance fraction exceeds 0.05. Look-elsewhere count = the grammar size at m = 3.
- T3 (COMPUTED, census with a Coulomb-scale factor, report-only): the same grammar multiplied by α, m = 1…3, base Ω_rim; counts and members in band. Shows that a Coulomb-scale factor is needed to reach the band if T2 returns empty, and the members it returns. CONSTRUCTION note D3.
- T4 (COMPUTED, report-only): αc/r for r in the registered set L = {R_p/3, R_p/2, 2R_p/3, R_p, D/3, D/2, D, 2R_p} with D = 7R_p/3: ħαc/r in MeV and the difference from B_d. Look-elsewhere count 8; no selection.
- T5 (P3): DEFERRED (NP31 coordination and NP17 geometry; the prompt names both).

**Whole-range single pass.** Every candidate in each grammar is evaluated once.

## 5. Gradated outputs and triggers
| Grade | Condition | Trigger |
|---|---|---|
| G0 | V1 or V2 not met | repair the instrument |
| G1 | R1 met: no α-free candidate in the m = 3 grammar within ±5% | name the premise: Δω has no α-free definition from the registered geometry; a definition from the lattice relay (FLM07/FLM10) is required before P1 can be run |
| G2 | candidates in band but R2 met (non-discriminating), or P3 deferred | NP17/NP31 outcomes and a derivation of Δω decide |
| G3 | a unique candidate in band with chance fraction ≤ 0.05 | consistent, shared-input if the candidate contains B_d-derived quantities; derive it from the lattice |
| G4, G5 | not available | — |

Expected landing (stated before the run): G2.

## 6. Alternative outs
1. A definition of Δω from the relay kinematics (FLM07 glancing transfer, FLM10 lattice solver): the change of the circulation rate of two locked rims computed on the per-spation lattice.
2. The shared-electron circulation rate at the node computed from W = 1 geometry (not from αc/r), once the node geometry is registered by NP17.
3. A second observable on the same Δω: the A = 3, 4 well depths (P3), registered with the NP31 inventory.

## 7. Run record

- Date 2026-10-06. Instrument `np06_reset_1.cpp` (MSVC 19.44, `/std:c++20 /O2 /utf-8`; constants from `sdt::laws`). Output `np06_reset_1_results.txt`. Single pass, no re-run.
- **Validations met.** V1: ℏc = 197.3270 MeV fm; ℏ(αc/a₀) = 27.211386 eV; E_d/ℏ = 3.3797e21 rad/s; Ω_rim = 6.5205e23 rad/s; ratio 5.18319e-3 (the prompt's 3.38e21, 6.52e23 and 5.2e-3 reproduced within 1.5%). V2: the planted candidate 1/12 is found; the sliding-band mean on 20000 log-uniform numbers is 144.815 against 144.910 expected (0.07%).
- **T1 (COMPUTED).** B_d = 2.22457 MeV (MEASURED-INPUT anchor, engine masses); v_seat/c = 1.83006; ħΩ_rim = 429.189 MeV; ħc/R_p = 234.522 MeV. Target ratios r_t = B_d/(ħΩ_rim) = 5.18319e-3 (band 4.92403e-3 … 5.44234e-3); r_t′ = B_d/(ħc/R_p) = 9.48553e-3.
- **T2 (COMPUTED, census, α-free).** Candidates in the ±5% band (grammar size; chance mean at random positions; fraction of random positions with count ≥ observed): base Ω_rim: m = 1: 0 (12; 0.323); m = 2: 0 (63; 1.137); **m = 3: 0 (209; 2.764; 1.0000)**; m = 4: 3 (519; 5.449; 0.9544); m = 5: 7 (1065; 9.116; 0.8901). Base c/R_p: m = 3: 1 (1/3·1/6·1/6 = 9.259e-3; 209; 2.764; 0.9748); m = 4: 3 (0.9544); m = 5: 10 (9.116; 0.4485). The m = 4 members on base Ω_rim: 1/2·1/4·1/4·1/6 = 5.208e-3 (1/192), 1/3·1/6·1/6·1/√3 = 5.346e-3, 1/6·1/6·3/7·3/7 = 5.102e-3. Rejection criterion R1 met (P1 is rejected as an α-free statement: the m = 3 count with base Ω_rim is 0). The second clause of the registered criterion R2 ("chance fraction > 0.05") is vacuous when the count is 0, because "fraction with count ≥ observed" is 1 for any random position: the printed "MET (non-discriminating)" carries no information at m = 3 and is not used. For m = 4, 5 the counts (3 and 7) are below the chance means (5.4 and 9.1): the 1/192 form and its neighbours are at chance.
- **T3 (COMPUTED, report-only, Coulomb-scale factor).** With one factor α on base Ω_rim: m = 0: 0; m = 1: 1 member (α/√2 = 5.160e-3, −0.45% from r_t; chance mean 0.323, fraction 0.3234); m = 2: 1 (same member; chance mean 1.137); m = 3: 3 (chance mean 2.764, fraction 0.5946). The α-containing members are at chance.
- **T4 (COMPUTED, report-only).** ħαc/r for the eight registered lengths: R_p/3: 5.1342 MeV (+130.79%); R_p/2: 3.4228 (+53.86%); 2R_p/3: 2.5671 (+15.40%); R_p: 1.7114 (−23.07%); D/3 = 7R_p/9: 2.2004 (−1.09%); D/2: 1.4669 (−34.06%); D = 7R_p/3: 0.7335 (−67.03%); 2R_p: 0.8557 (−61.53%). One length of eight is within 5%. By hand, with the eight values spread over about 0.85 decades and a band 0.045 decades wide, the chance that at least one of eight lands in the band is about 0.35. For r = D/3 the ratio to Ω_rim is algebraic: ħαc/(D/3) ÷ ħΩ_rim = (9/7) α k_surface = 5.127e-3 (k_surface = c/v_seat = 0.546431; DERIVED, checked against the printed 2.2004/429.189 = 5.127e-3).
- **T5.** P3 (He-3, α): DEFERRED (NP31 coordination, NP17 geometry).

## 8. Outcome and direction

**Grades.** P1 (an α-free rim-kinematic Δω with ħΔω(deuteron) within ±5% of B_d): **G1**, excluded on the pre-registered form (m = 3 grammar, count 0). Premise that produced it: the factors available in the registered grammar (the numbers of the prompt's geometry, W, W + 1 and the budget radicals) multiply Ω_rim by at most 1/4³ before m = 4, while the required reduction is 5.18e-3; the native quantity of that order in the engine is α (the hydrogen rung), which the registered α-free statement excludes. P2 (is Δω/Ω_rim a named native quantity): **G2**, open: the only α-free forms in band appear at m ≥ 4 and are at chance (count 3 against a chance mean 5.4); with α, one candidate (α/√2, −0.45%) at chance (fraction 0.32); for the Coulomb-scale well at r = D/3 the ratio is (9/7)α k_surface, which carries α twice and a length chosen among eight. P3: **G2**, deferred (NP31, NP17). The correspondence "E_bind = ħΔω with Δω = αc/r" is CONSTRUCTION (E divided by ħ); the registered P1 asks for more than that, and that part is excluded for the grammar above. No downgrade by agreement is made.

**What changes for the dependents.**
- NP17: takes no confirmation of "binding is movement" from NP06. The deuteron well at r = D/3 lands within 1.09% of B_d (T4); that length was one of eight registered lengths (look-elsewhere count 8; chance of at least one hit about 0.35). Why r = D/3 (one third of the contact distance) is not derived here and belongs to NP17's packing geometry.
- FD10: the NP06 premise is open (G2); any consumption of Δω as a derived rim quantity is conditional.
- Edges: NP06 → NP17 `required` (graph); NP17 → NP06 `cross-check`; NP31 → NP06 `required` for P3.

**Direction for the next layer of theory.**
1. A definition of Δω from the lattice relay (FLM07 glancing transfer, FLM10 per-spation solver): the change of the circulation rate of two locked rims. Register the definition and its value before comparing with B_d; the target reduction factor is 5.18e-3 of Ω_rim, which no α-free product of at most three geometric factors supplies.
2. If the Coulomb-scale rate αc/r is the physical content, the open question moves to r: derive r = D/3 (or the length that replaces it) from the node geometry, with the eight-length look-elsewhere count carried.
3. A second observable on the same rule: A = 3, 4 well depths with NP31's coordination, registered before the deuteron value is used.

## 9. Comparison with the archived record
Deferred to the end-of-programme comparison pass.
