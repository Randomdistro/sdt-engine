# RUN_LOG2 — Common Spaz Metric run 2

| Step | Event |
|---|---|
| 1 | `PROMPT2.md` pre-registration committed (fdb067c) before any tool existed. |
| 2 | `spaz_audit2.cpp` (W1 W2 W4 W7 W8) built and run once. Validations passed: ħc/r_e = 70.025 MeV; projected-solid-angle quadrature matched πR²/d² to 1e−9 at all ten distances; torus Pappus vs Monte Carlo 59.218 / 59.203. |
| 3 | `spaz_precession2.cpp` (W3). First build failed to compile (Vec3 has members, not an index). The perihelion tracker was rewritten (continuous polar angle, linear root of r·v) **before** any validation output was read. Validations then passed: Kepler 2.3e−13, Law V 0.16663, λ = 6 → 1.00141, engine `law_v_response` matched to 12 digits. |
| 4 | `spaz_models2.cpp` (W5 W6 W9), first run. The W5 table's local-c and CMB-β columns used wrong algebra: local c used +ν instead of −ν, and β used the arrival exponent instead of the emission exponent. Both were found by checking the C row against the hand derivation and corrected. The rank, family and pass/fail logic were unchanged by the correction. |
| 5 | W6: the two routes (53 rule N = 1093.0; Saha N = 1380.2) disagree by 26 %. Under the pre-registered 5 % criterion that disagreement is the finding. |
| 6 | **W6b added after inspection (not pre-registered):** release epoch from the fitted rate law by Thomson optical depth. Two transit rules × three H₀ values were reported once, with nothing retuned. Its look-elsewhere burden is stated in the assessment. |
| 7 | Charts drawn from the CSV outputs by a scratchpad script. Palette checked with the dataviz validator (blue / orange / aqua: all checks pass; aqua below 3:1 contrast, so every series is directly labelled). Two label collisions were fixed after viewing (Γ_ep reference labels; z*/z_drag markers). |
| 8 | Not compared: RUN-1 folder (`Projects/sdt-investigations/…_2026-10-22_2/`) is absent from this tree; RUN-1 statements are quoted as cross-checks only. |
