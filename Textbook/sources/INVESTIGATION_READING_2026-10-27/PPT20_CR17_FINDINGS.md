# Spaz transport and pressure: source recovery and independent checks

2026-10-28. Partial research result. Complete corpus reading and mathematical closure remain unfinished. Canonical sources unchanged.

## Why the earlier Spaz result changed

PPT20 explicitly repairs the earlier distinction between a fixed assignment admitting a unit completion and every allowed response being a unit change. The latter requires both the particular solution and every homogeneous response direction to lie in the dimensional-unit span. The source also replaces the unconditional `or True` duplicate control with independent/redundant controls. These issues already have a registered recovery; reporting the historical defects as unresolved current defects would misrepresent the source history.

PPT20 also separates spectral shape from spectral amplitude. Its S10 completion imposes c proportional to q, mass and action reference proportional to q^-2, fixed relay length, and T proportional to q^-1. The temporal phase completion supplies frequency transfer 1/q. The resulting thermal shape can match the present reference while a conserved dimensional mode action leaves a grey amplitude q^-2. Conservation of action divided by the changing action reference instead removes that grey factor. Neither choice is selected by the phase-speed equation alone.

## Explicit energy and momentum exchange

For the conditional response family

    B x'' + xi B' x' + K x = 0,
    E = (B x'^2 + K x^2)/2, p = B x', omega = sqrt(K/B),

direct differentiation gives

    E' = (1/2-xi) B' x'^2 + (1/2) K' x^2,
    p' = -Kx + (1-xi) B' x'.

For slow evolution, phase averaging gives

    d ln(E/omega) = (1-xi) d ln B.

Thus the same omega history permits different action transfer. With B=q^-2 and q changing from 1/2 to 1, xi=0 gives adiabatic action ratio 1/4; xi=1 gives ratio 1. The difference is explicit exchange with the medium, not an algebraic contradiction. A microscopic contact derivation must select the response and account for the corresponding counter-exchange. Phase kinematics alone cannot select xi.

Independent JavaScript RK4 execution reproduces the historical results. All 15 registered controls pass. At imposed rate 0.002, the action ratios are 0.249882571722016 and 1.000455168575487. The largest relative integrated-energy residual across the four runs is 2.72e-9; step refinement and rate reduction pass. These arbitrary oscillator rates provide no cosmic clock. See `PPT20_CR17_CHECK_RESULTS.json` and the preregistration.

## Why the sound result depends on the speed convention

CR17 computes electromagnetic speed c0/N but uses present reference c0 in c_sound=c0/sqrt(3(1+R)), with R=R0/N. Historical calibration gives R0=676.624331432794. Equal speeds then require

    N^3 - 3N - 3R0 = 0.

The positive crossing is N=12.740607857650467, T=34.72452671602635 K, speed 23530467.411724076 m/s. This is a conditional arithmetic consequence of those two equations, not a new BAO-derived observation.

If the acoustic formula instead uses the same state-dependent electromagnetic speed, the ratio is 1/sqrt(3(1+R)) and remains below unity for positive loading. Neither notation nor agreement with a desired crossing selects the physical expression. The acoustic stiffness/resistance response and operational clocks must select the speed in the numerator. The BAO observable also requires a path/history calculation; a local speed formula alone is insufficient.

Under c=c0/N and T=N T0, no finite positive temperature gives c=0. At 0.01 K the formal branch gives 8.17084344279e10 m/s relative to the fixed present units. That extrapolation is not an independently established future state and does not imply violation of a separately varying local relay limit.

## Preserve the distinct thermal anchors

The complete adjacent CR17 text retains separate conditions: a selected red/near-IR band, a loading-unity clearing state, and the adopted R=0.6 drag reference. The historical arithmetic gives:

| Condition | N | Temperature K | Wavelength under fixed present Wien coefficient |
|---|---:|---:|---:|
| 1 micrometre reference | 1063.2075 | 2897.7720 | 1000 nm |
| Loading unity | 676.6243 | 1844.1396 | 1571.3409 nm |
| Adopted drag loading 0.6 | 1127.7072 | 3073.5660 | 942.8045 nm |

The 974.7 nm historical recombination reference was back-computed from an imported redshift and is explicitly not an independent anchor in CR17. The physical interpretation of clearing remains a separate contact/opacity problem. The source's `received?` labels are assigned by an N threshold; no frequency-dependent optical-depth integral is evaluated by that assignment. A calculated optical-depth or escape-response function is required before an absolute transmission wall follows.

CR17 calls eta a measured BBN input; the script supplies a hard-coded inferred ratio without an abundance-to-eta derivation. Its model dependencies and uncertainties must be recovered before the number is described as raw model-independent measurement. No new online validation of that inference has been performed here.

## Thermal coefficients require state and instrument labels

CR17's historical ladder fixes both the Wien coefficient and radiation-density coefficient while changing c. PPT20's later S10 comparison completion changes the action reference as well. Within the comparison formulas

    a_rad proportional to kB^4/(hbar^3 c^3),
    b_Wien proportional to h c/kB,

S10 gives a_rad proportional to q^3, intrinsic u proportional to q^-1, b_Wien proportional to q^-1, and intrinsic peak wavelength proportional to q^0. The historical fixed-coefficient ladder instead gives u proportional to q^-4 and wavelength proportional to q. These are different declared completions; combining the powers silently would be invalid. Present-instrument temperature labels and received wavelengths require the full emission/transport/detection map. No rejection of the broader pressure-dependent SDT mechanism follows from comparing incompatible completions.

The pressure-regime assessment independently distinguishes convergence pressure, radiation pressure and effective interaction pressure. Its fixed-Phi lattice-pressure branch and fixed-convergence-pressure branch also give different resistance powers. This reinforces the need for a coupled state ledger rather than variation of c in isolation.

## Additional source findings

- Full root `sdt spaz value.txt` read: 7800 lines. Two historical truncation markers remain inside the source. The file does not contain the later red/near-IR, recombination and drag exchange visible in the conversation; missing historical content has not been fabricated.
- Full FLM14 Part C-prime source read. Analyzer settings enter only the final readout of a common trajectory ensemble. The CHSH routine uses a common tie-free subset across all four settings. Consequently the per-trial CHSH expression is bounded by 2 in magnitude; a gate below 2.8334 alone cannot demonstrate a Bell-inequality violation. A locked/unlocked difference can still test transmission within this instrument. The result file is empty, so no production result is certified.
- FLM14's later linear conserved-kick channel supersedes the old residence-exponent Bell transcription. Failure of the old exponent fit must not be used as a failure of the later channel construction.

## Remaining determining calculations

Recover the native acoustic response; emission-to-detector state map; contact-selected kinetic normalization and action exchange; optical-depth/escape response; and the chronology law. Complete all remaining investigations before a theory-wide closure verdict. No empirical calibration, comparison oscillator or threshold label substitutes for these derivations.
