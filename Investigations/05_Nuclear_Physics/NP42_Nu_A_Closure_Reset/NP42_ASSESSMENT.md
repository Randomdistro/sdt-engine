# NP42 — Assessment (2026-10-03)

**Classification:** `NP42_INCONCLUSIVE__EQUAL_ZA_INPUT_INVALIDATES_N_ASSIGNMENT` (corrected 2026-10-05; earlier labels superseded, text kept below)<br>
**Run class:** direct, main session. Tool `np37_nu_closure.py` (round 1), `np37_round2.py`; outputs `np37_results_round1.txt`, `np37_results_round2.txt`. Instrument validation V1–V3 passed before use.<br>
**Parameters fitted:** 0 in the hypothesis (u(N) from `laws.hpp` magic numbers); the break scans are the census. **Canon edits:** none.

## Results

| Gate | U-235 | U-233 | Cf-252 |
|---|---|---|---|
| G1 ρ(ν,u), 82≤N<126 | +0.986 PASS | +0.892 PASS | +0.733 PASS |
| G2 single hinge, whole range (best N_b; rank of 82 /31) | 70; 14 FAIL | 90; 15 FAIL | 88; 17 FAIL |
| G2′ heavy-branch V-shape (best N_b; rank of 82 /19; slopes b, c) | 79; 5; −0.067, +0.074 FAIL | 78; 7; −0.226, +0.100 FAIL | 80; 4; −0.263, +0.083 FAIL |
| N at minimum ν in data | 79.3 | 77.1 | 79.7 |

## Assessment

1. **G1 does not discriminate.** u is monotone in N inside a segment, and shifted closures (80, 84, 86) give ρ of the same size (e.g. U-235 +0.991, +0.980, +0.978). The passes carry no evidence for 82.
2. **G2 failed through a model shape I pinned**, not only through the hypothesis: one hinge cannot describe light and heavy branches pooled in N. Recorded as such; round 2 was pre-registered after round 1 was seen (exposure declared in PROMPT.md).
3. **G2′ shows a V-shape on all three systems, with the vertex below 82.** Slopes are negative below and positive above the break on every system; the best break is N = 79, 78, 80 and the data minimum is at N ≈ 79.3, 77.1, 79.7. The pre-registered gate (best within ±2 of 82 and rank ≤ 3) is not met on any system; Cf-252's best break lies within ±2 but 82 ranks 4th. The consistent offset of 2–5 units across three systems is a result to explain, not noise to widen the gate around.
4. **Candidate readings for the offset (not tested here):**
   - Equal-Z/A assignment: at the minimum (A ≈ 130) the equal-Z/A value Z_f ≈ 50.7 against Sn's Z = 50 gives N ≈ 79–80 while the doubly closed fragment has N = 82. A polarisation of about +1 in Z accounts for about 1–2 units of N, not all of the offset in U-233.
   - Pre-neutron mass: A is pre-emission, so the fragment that finishes at the N = 82 closure after emitting ν neutrons starts above it; that moves the pre-emission minimum the other way (above 82), so it does not explain a minimum below 82.
   - The closure that sets the minimum may be a proton-side or paired-shell condition (Z = 50 with N = 82 jointly), which a neutron-only u cannot express.
5. **What is not supported:** a neutron-closure reset at N = 82 as defined. **What is not excluded:** a closure reset with Z-side or paired definition, or with a measured Z distribution. Candidate C-type definitions (joint Z,N) remain available.

## Next round (needs data, not yet registered)
Round 3 should use a measured fragment Z distribution (e.g. most-probable Z(A) for these three systems) instead of equal-Z/A, and a joint (Z,N) closure distance. Source and sealing to be chosen before access. Until then NP42 holds at the classification above.

## Round 3 (2026-10-04) — Z = 50 vertex prediction
Output: `np37_results_round3.txt`. Pre-registered in PROMPT.md after rounds 1–2 (target-exposed).

| System | N_pred (Z=50) | best break | dev | rank of nearest integer /19 | G3a |
|---|---|---|---|---|---|
| U-235 | 78.26 | 79 | 0.74 | 4 | FAIL (rank gate) |
| U-233 | 77.17 | 78 | 0.83 | 3 | PASS |
| Cf-252 | 78.57 | 80 | 1.43 | 3 | PASS |

- **Gate not met on all three** (needs all three): U-235 fails on rank (4, gate ≤ 3). The gate is not widened.
- Deviation from the Z = 50 prediction is 0.7–1.4 on every system, against 3–4 for N = 82. The best break lies above N_pred in all three, the direction and size an equal-Z/A bias would produce at A ≈ 130 (about +1 in Z ↔ about +0.8 N here); not tested.
- **Null:** Z = 48 is clearly disfavoured (ranks 18, 13, 16 of 19; deviations 3.9–4.6). Z = 52 is not separable (ranks 3, 4, 4; deviations 1.7–2.4), so the test discriminates against Z = 48 and N = 82 but cannot yet separate Z = 50 from Z = 52.
- **Assessment:** the vertex is consistent with a proton-side closure near Z = 50 and not with the N = 82 definition as pinned. The pre-registered gate is missed by one rank on one system, and with the Z-polarisation size above the Z = 50/52 spacing, equal-Z/A cannot settle it. A measured Z(A) per system is required; it would also let the Z = 50 versus 52 question be asked.
- Combined with the NP35/NP36 recorded exclusions of Z_H seating, this does not support a neutron-only closure reading of "unseated nucleons"; the joint (Z,N) reading (Z = 50 with N = 82 together, i.e. Sn-132 as the doubly closed fragment) remains the live candidate.

## Next (needs data)
Fetch measured fragment Z(A) (e.g. most-probable Z per A for U-235(n_th,f)) from EXFOR/ENDF before pre-registering round 4; seal the Z = 50 versus 52 gate first.

## Round 4 (2026-10-05) — profile-set statistic, exploratory
Output: `np37_results_round4.txt`. The round 3 gate stands as missed; round 4 changes the statistic after the data were seen, so nothing here is confirmatory.

| System | n | best break | Δχ² ≤ 1 set | Z=50 nearest int in set |
|---|---|---|---|---|
| U-235 | 29 | 79 | 79–80 | no (78) |
| U-233 | 44 | 78 | 78 | no (77) |
| Cf-252 | 65 | 80 | 80 | no (79) |

- G4 fails on all three. The profile set is narrow (one to two integer breaks), and none of Z = 48, 50, 52 or N = 82 falls inside it on any system. The rank statistic had been the lenient one.
- What survives: the vertex is stable across three systems (N = 78–80), lies 0.7–1.4 above the equal-Z/A Z = 50 prediction in every case, and its shape (b < 0 < c) holds. The consistent offset is a property to explain, not a gate to relax. A tool that quotes the offset (≈ +1 N) as a fit would be CALIBRATED(1) and is not registered.
- Resolution caveat: breaks are scanned on an integer grid and compared to a real-valued prediction; a continuous-break scan is a refinement, not a rescue.
- Assessment: neither N = 82 nor an equal-Z/A Z = 50 vertex is supported at this resolution; the data locate the minimum near N ≈ 79 ± 1. Retrying on this data further is exhausted; the next informative step is new data (measured Z(A), or sealed Pu-239 n_th,f ν(A)).

## Correction (2026-10-05) — rounds 1–4 conclusions about N = 82 are withdrawn
Raised by the Operator; checked against the data (`A` and ν̄ near the minimum, printed 2026-10-05).
- The input is ν̄ per **mass number**, not per isotope. N was assigned by equal-Z/A, which gives non-integer N (79.3 at A = 130) and ignores that Z is pinned near 50 for A ≈ 128–134. With Z = 50, A = 130 is N = 80 and A = 132 is N = 82 (Sn-132). The 1–3 unit offset from 82 reported in rounds 2–4 is the same size as this assignment error, so it is not a finding.
- The ν̄ floor is flat: U-235 0.567 at A = 130 against 0.596 at A = 132; U-233 0.555 at A = 127 against 0.652 at A = 132; Cf-252 0.450 at A = 130.4 against 0.646 at A = 132.4. The hinge position on a noisy flat floor is poorly defined, and the round 4 window (Δχ² ≤ 1 on an integer grid) was too tight to carry the weight put on it.
- Statements withdrawn: "N = 82 reset not supported"; "vertex near N ≈ 79 ± 1"; "retrying on this data is exhausted". The G1 non-discrimination and the round 1 pooled-hinge shape errors stand.
- What is open: whether ν resets at N = 82 using real fragment isotopes. Needs a measured Z yield per A (fission-yield library or table), N built from the dominant Z, and the break test repeated with the gate registered first.

## Round 5 (2026-10-05) — measured Z per A (Wahl), U-235(n_th,f) only
Output: `np37_results_round5.txt`; data `Datasets/nuclear/fission_z_distribution/` (Wahl evaluated FI, extraction copy, provenance in its README). Gate registered before the run (PROMPT.md, Round 5). Instrument checks V1–V2 passed (FI sums to 1 per A; Sn-130 FI = 0.66625 reproduced).

| Z assignment | best break N* | Δχ² ≤ 4 set | Δχ² at 82 | slopes b, c | G5 |
|---|---|---|---|---|---|
| mean Z | 79.75 | 78.25–81.25 | 6.45 | −0.038, +0.075 | FAIL |
| mode Z | 80.00 | 77.50–81.50 | 5.87 | −0.023, +0.075 | FAIL |

- Measured Z at the ν̄ floor: A* = 130 is Z ≈ 50.1–50.4, so N* ≈ 79.8–80.0 (Sn-130-like), and ⟨Z⟩ reaches 50 at post-neutron A ≈ 129. The lowest-ν̄ point (A* = 130, ν̄ = 0.567) therefore sits at N* ≈ 80. The point at A* = 132 (ν̄ = 0.596, N* ≈ 81–82) is within error of it.
- With real Z the vertex is at N* ≈ 80, two units below 82, and N* = 82 lies outside the 95% set (Δχ² ≈ 6). A null at 80 is inside the set; 84 is excluded (Δχ² ≈ 10–12). The pre-registered gate (best within ±1 of 82, 82 inside the set) is not met.
- This overturns the round 2–4 caveat in one respect: the offset from 82 does not vanish when real Z replaces equal-Z/A; it stays about 2 units. It does not overturn the limitations: χ²/dof ≈ 1.9–2.3 (the V model is an imperfect shape, errors scaled up), Wahl FI around A ≈ 128–134 mix experimental and model values, the single system, and ν̄ pre-neutron mass mapping via A − ν̄ (a one-parameter-free approximation).
- Classification: `NP42_U235_VERTEX_N80_MEASURED_Z__N82_GATE_NOT_MET` (single system, target-exposed on ν̄). U-233 and Cf-252 are not tested with measured Z (no Wahl table for them in hand); Cf-252 fractional yields are in `UKFY2/UKFY2_6` on the same IAEA server, not fetched.
- Not tested: whether the closure the data show is N = 80-ish for another reason (e.g. pre-emission counting convention: the post-emission neutron number at the floor is N* − ν̄ ≈ 79.2), or whether the "82" enters through the complementary light fragment or the full pair. Those are definitions to register, not rescues.

## Round 6 (2026-10-05) — NP35/NP25 hypothesis on the repo's IAEA independent yields
Output: `np42_results_round6.txt`; registered in PROMPT.md (Round 6) before the run. Folder renamed from NP37 (NP37 is queued for flay depth in `NP35_CHAIN.md`); script file names keep the `np37_` prefix from earlier rounds.

| System | n | χ²/dof | best N_b | floor ν̄ | slope per neutron | Δχ² ≤ 4 set | Δχ² at 82 | G6 |
|---|---|---|---|---|---|---|---|---|
| U-235 | 29 | 1.92 | 80.50 | 0.633 | +0.075 | 79.00–81.25 | 13.1 | FAIL |
| U-233 | 45 | 24.8 | 79.75 | 0.642 | +0.077 | 78.75–80.50 | 27.9 | FAIL |

- Onset of the rising branch is at N\* ≈ 80–80.5 on both systems and is robust to the Z source (Wahl round 5 gave 79.75–80.0; IAEA independent yields give 79.75–80.5). A break at 84 is excluded (Δχ² 85–94).
- The NP35 remnant is Z_H = 52, N = 82, A_H_pre = 134 (parent-composition Z). With measured Z, ⟨Z⟩(A\*=134) = 52.0–52.3, so the repo's remnant sits at N\* ≈ 82 as NP35 says; the ν̄ onset is about 2 neutrons (≈ 3 mass units) below it.
- Slope ≈ +0.075 ν̄ per added neutron, far below one neutron stripped per added jacket triton (a 1:1 strip would give slope 1); a size the NP25 picture would have to explain.
- Limitations: U-233 χ²/dof = 24.8 (its ν̄ errors are small relative to point scatter, so Δχ² is scaled by 24.8 and the set is wide in ν̄ units, not narrow); the hockey-stick form was chosen after seeing a flat floor; IAEA yield sums to 1.8 per fission, not 2.0 (extraction incomplete in the tails; irrelevant at A ≈ 130 where ⟨Z⟩ is taken per mass).
- Classification: `NP42_NU_ONSET_N80_ON_REPO_YIELDS__NP35_N82_ONSET_NOT_MET`. This tests the ν̄ onset only; it does not touch NP35's A_H result (MATCH) or the heavy-remnant claim.
