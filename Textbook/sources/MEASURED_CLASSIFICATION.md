# Classification of the `measured` namespace

Opened 2026-11-09 for Chapter 6. Source: `Engine/include/sdt/laws.hpp`, namespace `measured` (lines 95–239 as read on 2026-11-09), the engine's own provenance comments, and the derivelist record (`derivelist/README.md`, retrieved from git history; the folder is absent from the working tree). Identifiers are quoted as they appear in the engine, including `e_charge`, which this book otherwise writes as the unit bridge $e$. Appearance in the namespace confers no derivational status; the role of each entry is the engine's own statement.

Roles: **UB** unit bridge (SI definition, nothing to derive) · **SEAT** the one mass/action seat · **CLOSURE** a geometric relation with a stored number · **SPEC** spectroscopic derivation · **BOUNDARY** measured mechanical boundary state · **ANCHOR** measured anchor or validation datum · **COMPARISON** comparison datum derivable from other entries · **IN-ENGINE** derived inside the header from other entries · **LEGACY** retained ballpark, not a measurement · **EXTERNAL** external input conditioning a law.

| identifier | engine value | role | label in this book | note |
|---|---|---|---|---|
| `c` | 299 792 458 m/s | UB | MEASURED-INPUT (SI exact) | derivelist item 1: unit bridge, line drawn |
| `hbar` | 1.054 571 817 646 156e-34 J s | SEAT | MEASURED-INPUT (SI exact numerically) | W=1 circulation quantum in role (FLM13); value collapses into the seat |
| `l_P` | 1.616 255e-35 m | CLOSURE | CALIBRATED(1) as a stored number | relation $\ell_P=\sqrt{\mathrm{Om}_b\,\lambda_p}$ (c-boundary per baryon and proton wake; the engine names the first factor koppa) is geometric; the stored number is the CODATA Planck length, whose definition carries $G$ numerically (`laws.hpp:111–119`) |
| `alpha` | 7.297 352 5643e-3 | SPEC | MEASURED-INPUT (CODATA 2022) | hydrogen koppa rung (APS05, PPT02); topology-only origin open |
| `h` | 6.626 070 15e-34 J s | UB | MEASURED-INPUT (SI exact) | $=2\pi\hbar$ |
| `k_B` | 1.380 649e-23 J/K | UB | MEASURED-INPUT (SI exact) | kelvin unit bridge (derivelist item 7) |
| `e_charge` | 1.602 176 634e-19 C | UB | MEASURED-INPUT (SI exact) | unit bridge; irreducible Tier-1 input, not derivable (EMC02) |
| `alpha_inv` | $1/\alpha$ | IN-ENGINE | COMPUTED | exact reciprocal in the engine |
| `a_0` | 5.291 772 105 44e-11 m | ANCHOR | MEASURED-INPUT (CODATA 2022) | the length the seat form rides on (derivelist audit F3) |
| `r_e` | $\alpha^2 a_0$ | IN-ENGINE | CONSTRUCTION | hydrogen c-boundary; equals the classical electron radius |
| `R_p` | 8.414e-16 m | ANCHOR | MEASURED-INPUT (muonic hydrogen, 2019) | FLM07 selects $q=4$ before comparison; $q\hbar/(m_pc)$ agrees to 0.02% |
| `m_e` | 9.109 383 7139e-31 kg | SEAT | MEASURED-INPUT (CODATA 2022) | one mass/action seat with `hbar`, `m_p` |
| `m_p` | 1.672 621 925 95e-27 kg | SEAT | MEASURED-INPUT (CODATA 2022) | $R_p$ and $m_p$ are one fact (shared residual) |
| `m_n` | 1.674 927 500 56e-27 kg | ANCHOR | MEASURED-INPUT (CODATA 2022) | nuclear mass |
| `m_d` | 3.343 583 7768e-27 kg | ANCHOR | MEASURED-INPUT (CODATA 2022) | nuclear mass |
| `m_t` | 5.007 356 7512e-27 kg | ANCHOR | MEASURED-INPUT (CODATA 2022) | nuclear mass |
| `m_He3` | 5.006 412 7862e-27 kg | ANCHOR | MEASURED-INPUT (CODATA 2022) | nuclear mass |
| `R_inf` | 1.097 373 156 8157e7 /m | COMPARISON | MEASURED-INPUT (CODATA 2022) | follows from $\alpha$, $m_e$, $c$, $h$ |
| `Ry_eV` | 13.605 693 122 990 eV | COMPARISON | MEASURED-INPUT (CODATA 2022) | follows from `R_inf`, $h$, $c$, $e$ |
| `lambda_C_e` | $h/(m_ec)$ | IN-ENGINE | COMPUTED | electron Compton wavelength |
| `lambda_C_p` | $h/(m_pc)$ | IN-ENGINE | COMPUTED | proton Compton wavelength |
| `t_P` | $\ell_P/c$ | IN-ENGINE | COMPUTED | relay interval in SI seconds (unit bridge) |
| `l_P3` | $\ell_P^3$ | IN-ENGINE | COMPUTED | cell volume |
| `a_rad` | 7.5657e-16 J m^-3 K^-4 | COMPARISON | MEASURED-INPUT | radiation constant, five digits |
| `T_CMB` | 2.7255 K | BOUNDARY | MEASURED-INPUT (FIRAS) | present convergence boundary state, not a fitted parameter |
| `T_rec` | 3000 K | LEGACY | not cited | round epoch-frame ballpark of the rival account; retained so downstream tools do not change |
| `z_rec` | 1100 | LEGACY | not cited | as `T_rec` |
| `z_release` | 1089 | ANCHOR | OBSERVED (FIRAS frame) | native boundary release; the temperature is computed from it |
| `T_release` | $T_{\rm CMB}(1+z_{\rm release})$ | IN-ENGINE | COMPUTED | 2970.8 K |
| `R_CMB` | 9.527e26 m | EXTERNAL | MEASURED-INPUT (class X) | conditions the Law I chain; fails the delete-test |
| `eV_to_J` | `e_charge` | UB | MEASURED-INPUT (SI exact) | unit conversion |
| `MeV_to_J` | $10^6\times$ `eV_to_J` | UB | MEASURED-INPUT (SI exact) | unit conversion |
| `R_Sun` | 6.957e8 m | ANCHOR | MEASURED-INPUT (IAU 2015) | astrophysical scaling only |
| `AU` | 1.495 978 707e11 m | ANCHOR | MEASURED-INPUT (IAU 2012) | astrophysical scaling only |
| `R_He` | 1.6755e-15 m | ANCHOR | MEASURED-INPUT | He-4 boundary radius |
| `k_e` | 8.987 551 7862e9 N m²/C² | IN-ENGINE | MEASURED-INPUT (CODATA 2022) | $1/(4\pi\epsilon_0)$ from SI |
| `mu_P` | 2.792 847 344 63 | ANCHOR | MEASURED-INPUT (CODATA 2022) | in nuclear magnetons, a borrowed unit; recast to a native ratio before use |
| `mu_N` | -1.913 042 76 | ANCHOR | MEASURED-INPUT (CODATA 2022) | as `mu_P` |
| `mu_D` | 0.857 438 2335 | ANCHOR | MEASURED-INPUT (CODATA 2022) | as `mu_P` |
| `mu_T` | 2.978 962 4650 | ANCHOR | MEASURED-INPUT (CODATA 2022) | as `mu_P` |
| `mu_He3` | -2.127 625 3498 | ANCHOR | MEASURED-INPUT (CODATA 2022) | as `mu_P` |
| `mu_alpha` | 0 | ANCHOR | MEASURED-INPUT | alpha particle, spin 0 |
| `Q_deuteron_fm2` | 0.285 699 fm² | ANCHOR | OBSERVED (Pachucki 2020) | spectroscopy anchor, not a CODATA constant |
| `B_deuteron` | from `m_p`, `m_n`, `m_d` | IN-ENGINE | COMPUTED | MeV, from measured masses |
| `B_triton` | from `m_p`, `m_n`, `m_t` | IN-ENGINE | COMPUTED | MeV, from measured masses |
| `B_helion` | from `m_p`, `m_n`, `m_He3` | IN-ENGINE | COMPUTED | MeV, from measured masses |
| `B_alpha` | 28.296 MeV | ANCHOR | MEASURED-INPUT | typed value |
