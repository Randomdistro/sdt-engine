# NP12 — Nuclear charge radius scaling: reset record (2026-10-10)

**Protocol:** Investigations/RESET_2026-10-06/PROTOCOL.md. Session sdt-engine-e0.

**Read:** PROMPT.md, including its audit finding ("Z·R_p 890.8% off"); laws.hpp 
uclear_boundary_radius, whose comment states RMS 4.96% on 908 radii (exposed).

**Not opened:** NP12_VERDICT.md, RUN_LOG.md, 
p12_results.txt, the old script, the folder's charge_radii_iaea.csv. The dataset used is Datasets/nuclear/IAEA_ground_states_radii.csv.

## Registration (the prompt's phases, carried)
- **Phase B:** RMS relative deviation and R² for R_SDT = Z·R_p (R_p = 0.8414 fm) and for R_std = 1.2·A^(1/3) fm, over every nuclide with a measured radius.
- **Phase C (isotope chains):** for elements with at least 5 measured isotopes, the fractional radius change along the chain, against SDT's "constant" prediction (Z·R_p does not change with N).
- **Added row, labelled exposed:** the engine canon law R = R_p(A/η)^(1/3), η = π/√18. Its 4.96% figure is known from the engine comment, so this row is a re-verification, not a test.
- **Gate (prompt's decisive test):** the model with the smaller RMS on all measured radii. The isotope-chain test separates "constant" from "growing".

## Run and results
(below)
908 measured radii (IAEA). Output in `np12_reset_1_results.txt`. Single pass.

| model | RMS relative deviation | R² |
|---|---|---|
| Z·R_p (prompt's SDT premise) | **890.8%** | −3281.6 |
| 1.2·A^(1/3) (prompt's rival) | 25.6% | −1.46 |
| R_p(A/η)^(1/3) (engine canon; exposed) | 4.96% | 0.961 |

**Phase C (isotope chains).** 60 elements have at least 5 measured isotopes. The radius grows along the chain by **2.36% on average** over ΔN ≈ 15.2, and 48 of 60 chains change by more than 1%. For the same ΔN, A^(1/3) would give 5.10%.

**Outcomes.**
- **The prompt's premise R = Z·R_p is EXCLUDED (G1).** It is off by about 9×. Adding proton radii in one dimension cannot describe a volume-filling object (the prompt's own audit finding, now reproduced).
- **The prompt's "constant along isotope chains" prediction is EXCLUDED (G1).** Radii grow with N, by about half the A^(1/3) rate.
- **Fairness note.** The prompt's rival, 1.2·A^(1/3), is an edge (uniform-sphere) radius, not an RMS radius. A like-for-like RMS form would carry √(3/5). The 25.6% is therefore partly a convention mismatch in the prompt, not a property of the rival.
- **The engine canon law re-verifies at 4.96%.** That figure was known from the engine comment, so this is not a blind result. The canon law has already replaced the prompt's premise.

## Comparison with the archived record
Deferred.
