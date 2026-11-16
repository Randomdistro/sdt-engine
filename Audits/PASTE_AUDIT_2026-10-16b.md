# Audit of pasted external output: "Single-Medium Pressure and Koppa Hierarchy" (f = 2.12419e-17, B21 = 2.2687e39), 2026-10-16

Source status: output of another model; not citable. Nothing entered the codebase (Engine/ untouched; proposed header `sdt/laws/force_hierarchy_closure.hpp` not created). Recompute: `PASTE_AUDIT_2026-10-16b_recompute.py`.

## Reproduced
- R_p = 4 hbar/(m_p c) = 8.412356e-16 m; r_e = 2.817940e-15 m.
- P_eff = 4 m_e c^2/(pi R_p^2 r_e) = 4 alpha hbar c/(pi R_p^2 r_e^2) = m_p^2 m_e^2 c^5/(4 pi alpha hbar^3) = 5.227252e31 Pa (three forms agree to 1e-15; the electropause closed form is the repo's own).
- V_int = (pi/4) R_p^2 r_e = 1.566235e-45 m^3; m_e c^2 / V_int = P_eff.
- B21 number: R_p r_e/(4 l_P^2) = r_e/(l_P^2/lambda_Cp) = 2.268662e39.
- R_charge-labelled area: pi R_p r_e = 7.447308e-30 m^2; 4 pi l_P^2 = 3.282688e-69 m^2.
- Table P_CMB = P_cf/N reproduces (4 pi N^2 = 4.366e124 also).

## Faults
1. "f is the pure volumetric ratio" is a tautology. B24 defines V_disp = 3 m l_P^3 c^2/Phi = 3 m c^2/P_conv (laws.hpp line 814; suite labels B24 rows COMPUTED/CONSTRUCTION). Then V_disp(e)/(3 V_int) = (m_e c^2/V_int)/P_conv = P_eff/P_conv with no content beyond P_eff = m_e c^2/V_int. Tier: IDENTITY (restated Coulomb identity). The statement "P_eff = electron rest energy / proton-electron interaction volume" is a legitimate native reading; the volumetric f is not a second derivation.
2. f is not G-free or boundary-free. P_conv = Phi/l_P^3 = N u_CMB with N = R_CMB/l_P: f carries l_P and the observed Clearing boundary. Repo tier for f: COMPUTED (suite B22 comment). Paste tier "DERIVED/IDENTITY" for the row is not supported.
3. B21 "G-free area origin" fails on provenance. l_P^2/lambda_Cp = 1.242116e-54 m equals G m_p/c^2 (G = 6.6743e-11, recovered from the stored l_P as l_P^2 c^3/hbar = 6.674300e-11). B21 is the electron-proton Coulomb/gravity ratio alpha hbar c/(G m_e m_p) = 2.2687e39 written with the G-carrying stored l_P. Contaminating input: stored l_P (CODATA G chain; provenance_disclosure in laws.hpp). The suite already marks B21 display-only (unit bookkeeping, no tally).
4. "Exact area ratio of charge cross-section to Planck sphere" is a relabelling: the factor 4 and pi are chosen (sphere radius = l_P rather than l_P/2 or pitch changes the number by 4); R_charge^2 := R_p r_e is a definition.
5. Language: "charge cross-section", "R_charge", "kRCharge_m", "Electromagnetic koppa" with charge wording are prohibited in active SDT prose/code (GATEWAY_BEHAVIOURAL section 1).
6. Tier 3 row circular: P_CMB = P_cf/N with P_cf = N P_CMB.
7. Numeric spread across the paste: P_eff 5.22725 / 5.2273 / 5.2268e31; P_conv 2.46082 / 2.46061e48 (8.6e-5 relative). Rounding-level, but "exact" claims need one value.
8. CODATA 2018 alpha (7.2973525693e-3) and r_e 2.817940326e-15 in header against repo CODATA 2022. Header redefines constants already in laws.hpp (single-source rule) and proposes a file under Engine/ (laws canon: propose-and-wait).

## Disposition
Hold. Worth keeping: P_eff = m_e c^2 / V_int as a wording of the Coulomb identity (IDENTITY, native, G-free).
