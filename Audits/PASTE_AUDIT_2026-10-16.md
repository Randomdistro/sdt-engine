# Audit of pasted external output (cosmography / chronology / DSOC package), 2026-10-16

Status of the source: output of another model run under the master prompt. Not citable (GATEWAY_PROCEDURAL: delegated-agent output). Nothing from the paste entered the codebase. Recompute script: `PASTE_AUDIT_2026-10-16_recompute.py` (scipy quad, rtol default).

## Reproduced (arithmetic only; derivations not audited)
- c/676.6 = 4.43087e5 m/s; c/676.6^2 = 654.872 m/s; c/1090^2 = 252.329 m/s.
- N_origin = (P_eff/P0)^(1/4) = 2.47560e11; lambda = 4.2947e-15 m; c/N^2 = 4.8917e-15 m/s; lambda/c_far = 0.87797 s.
- Weak-field 2cz: 1272.62 (R_sun), 5.918 (1 AU), 424.21 (3 R_sun), 104.999 (galactic floor).
- Local elapsed age with H(N)=H_bath*sqrt(Om_rad N^4 + N^3/4 + 3/4): 14.677 Gyr (paste 14.6813, 0.03 %).
- Forward local: to N=1/676.6 108.339 Gyr (paste 108.342); to N=1/N_Gamma 438.647 Gyr (paste 438.654). Far-frame forward 1->0: 16.138 Gyr (paste 16.146).
- DSOC second-order term: 10.948 ps, 3.282 mm, 2117.5 cycles at 1550 nm (paste 10.95 ps, 2118).
- DSOC first-order term: 104.655 us (paste 104.649; ln argument 41101 vs 41089).

## Not reproduced
- Far-frame elapsed age: 49.445 Gyr (int dN/h) against paste 69.752 Gyr (4.8080 T_H vs 3.408 T_H).
- SN integral to z=11.256 of 1/sqrt(0.25(1+z)^3+0.75): 2.4155 against paste 3.2148. D_L = 131,678 Mpc against paste 175,236.
- LCDM D_L at z=14.32 (H0 67.4, Om 0.315): 158,759 Mpc against paste 224,810. L_true/L_naive with recomputed values 0.440 against paste 0.3889. The 61.1 % mass-reduction figure does not stand.
- "residual below 0.038 mag" and "erases Delta AIC ~ 90": no computation shown; none run here.

## Structural faults
1. H(N) written without the square root in the chronology section; the quoted ages need the square root (distance section uses it). Definition inconsistent inside the paste.
2. N_Gamma "fixed by" c0/c_far(Gamma): c_far(Gamma) was computed from N_Gamma (from P_eff). Circular. N_Gamma rests on P_eff (electropause expression, alpha the one input).
3. Luminosity-distance form: (1+z) x integral of 1/sqrt(0.25(1+z)^3+0.75) is the flat-LCDM expression with Omega_m = 0.25, Omega_L = 0.75. The extra "GOM22 tick-closure (1+z)" is the (1+z) already present in the standard flat D_L, so no additional factor. Form is shared; the constant term is cosmological-constant-shaped, so "zero dark energy" is a labelling choice, not a structural difference. Shared form = cannot discriminate by form alone; origin (integer 1/4, 3/4 from the recombination defect count) is the claimed discriminator and is not independent evidence of fit. Pantheon+ flat-LCDM Omega_m is ~0.33 (recalled, verify); 0.25 is expected to fit worse, contradicting the 0.038 mag claim.
4. Forward-timeline framing (Delta t_future, "time symmetry") conflicts with the no-time-arrow rule (Harvey 2026-10-10) and the NOT COMMITTED status of the cyclic cosmology.
5. DSOC: second-order term (10.9 ps) is below ns-scale PPM slots (recalled) and of the size of the standard second-order PPN term; dispersion zeta*l_P/lambda ~ 1e-29 undetectable. Operational problem statement unsupported. First-order term (2 kop/c ln) is the standard one-way coefficient; round-trip B39 uses 4 kop/c (247.2 us checked).
6. JWST scenario: z_emit = 0.250 invented; no source for the emission-depth stamp of high-z cores.
7. Ledger lists l_P as a measured input and CODATA 2018; repo canon: stored l_P carries G (provenance_disclosure in laws.hpp), measured set is CODATA 2022.
8. Package breaches the master prompt: manuscript and deployment package issued without a closed solve; named contacts with unverified titles. Byline "Tyndall"/affiliation unverified against current repo practice.

## Disposition
Hold. Candidate worth a pre-registered check: the c_hop (c/N) versus c_far (c/N^2) split at the 676.6 wall (arithmetic reproduced; wording in the Wall paper not checked here).
