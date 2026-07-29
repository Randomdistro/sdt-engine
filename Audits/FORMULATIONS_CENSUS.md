# SDT Formulation Census — Whole-Codebase Audit

**Scope:** every formula-bearing file in `sdt-engine` — Engine headers, Theory/Laws/Papers/manuscripts, ATOMICUS, Hubble, Experiments (E01–GOM12), Investigations (EMC01–APS03 + E-folders), Benchmarks.
**Method:** 7 parallel extraction agents, one per directory cluster; ~600 raw rows consolidated here into distinct formulations, deduplicated, ordered by **relevance tier** then **canonical appearance**.
**Excluded:** `Theory_SCT/` (a different theory — Structural Coding Theorem), `Compiler/` (a meta-tool that *ingests* these formulas; see `Compiler/output/AUDIT_REPORT.md`), `Release/` (packaged duplicate of Engine/Benchmarks), and pure data files (`.csv/.tsv/.txt/.dat`).

**Relevance legend** — **T0** foundational invariant/axiom · **T1** core law/theorem · **T2** derived domain relation · **T3** applied/numeric/per-object prediction.
**Certification** — DERIVED · COMPUTED · CALIBRATED (≥1 fitted parameter) · OBSERVED/MEASURED (external input) · PENDING · "—" (definitional/unlabelled).

> ⚠️ Coupling note: the SDT *Theory Compiler* mis-parses several of these (e.g. flags the force law `F=(π/4)P_eff R₁²R₂²/r²` as dimensionally invalid). Those are **tool** bugs, not errors in the formulas below — see `Compiler/output/AUDIT_REPORT.md`.

---

## PART I — Foundational invariants & axioms (T0)

| # | Formula | Meaning | Domain | Source (representative) | Cert | Rel |
|---|---|---|---|---|---|---|
| 1 | `c = ℓ_P / t_P` | Relay speed = lattice tick rate | Axiom R2/M1 | laws.hpp:109; Theory/04_Notation.md:9; Laws/SDT_Complete_Laws.md:54 | DERIVED | T0 |
| 2 | inputs `{ℓ_P, c, ℏ, k_B, T_CMB, α, m_e, m_p}` | Permitted external scale set (whitelist) | Ruleset | laws.hpp:107-180; Theory/00_Ruleset.md | MEASURED | T0 |
| 3 | `\|u\| ≤ ℓ_P/t_P = c` | Hard relay-speed bound | Axiom M1 | Theory/00_Ruleset.md:45; Laws/SDT_Complete_Laws.md:726 | — | T0 |
| 4 | `v_circ ⊥ v_trans ; u = v_circ + v_trans` | Orthogonal mode composition | Axiom M2/M3 | Theory/00_Ruleset.md:45; Laws/SDT_Complete_Laws.md:733 | — | T0 |
| 5 | `τ = ε_d/ε = 1/d = 1/3` | Traction fraction = 1/dimensionality (3D) | Operator 3 / T7 | Theory/00_Ruleset.md:12; Theory/01_Closure_Derivations.md:17; laws.hpp:175 | DERIVED | T0 |
| 6 | `v_circ² + v² = c²` | Movement budget (also `v_T²+v_P²+v_C²+v_t²=c²`) | Operator 6 / T10 / Law V | Theory/00_Ruleset.md:27,60; laws.hpp:403 | DERIVED | T0 |
| 7 | `z·k² = 1` (z=(v/c)², k=c/v) | Closure / bridge identity | Bridge | laws.hpp:495; Papers/an_argument_for_koppa.md:333; ATOMICUS structural_analysis.cpp:204 | DERIVED | T0 |
| 8 | `ϟ = v²R/c²` (= GM/c²) | Koppa = c-boundary (gravity without G, M) | Bridge | laws.hpp:546; Papers/an_argument_for_koppa.md:23 | DERIVED | T0 |
| 9 | `⟨cos²θ⟩ = 1/3` (cubic lattice) | Geometric origin of the 1/3 factor | FLM02 closure | Investigations/FLM02.../cq08_measure_closure.cpp:382 | DERIVED | T0 |

## PART II — Law I: Cosmological Relay Throughput (T1)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 10 | `u_CMB = a T_CMB⁴` | CMB energy density | laws.hpp:193 | DERIVED | T1 |
| 11 | `ε = u_CMB · ℓ_P³` | Relay content per spation/shell (Def D3) | laws.hpp:210; Theory/02:25 | DERIVED | T1 |
| 12 | `N = R_CMB / ℓ_P` | Causal depth (shell count); R_CMB=9.527e26 m | laws.hpp:206 | DERIVED | T1 |
| 13 | `Φ_shell(d) = \|S_d\|·ε/(4πd²) = ε` | Shell Cancellation Identity (T1) | Laws/SDT_Complete_Laws.md:99 | DERIVED | T1 |
| 14 | `Φ = N·ε` | Total convergence burden (T2) | laws.hpp:215; Theory/00_Ruleset.md:6 | DERIVED | T1 |
| 15 | `P_conv = Φ/ℓ_P³ = N·u_CMB` | Convergent (Planck-scale) pressure ≈2.46e48 Pa | laws.hpp:219 | DERIVED | T1 |
| 16 | `S = 4πN² ≈ 4.37e124` | Boundary source cells (resolves Λ/10¹²³) | laws.hpp:223; SPATIAL...:300 | COMPUTED | T1 |
| 17 | `φ(n̂) = Φ/(4π)` | Angular convergence uniformity (T3) | Laws/SDT_Complete_Laws.md:416 | DERIVED | T1 |
| 18 | `F = ∮ φ(n̂) n̂ dΩ = 0` | Newton I (net force at rest, C3.1) | Laws/SDT_Complete_Laws.md:427 | DERIVED | T1 |

## PART III — Law II: Release Cascade (T1–T2)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 19 | `F_CMB = c·u_CMB/4` | CMB isotropic energy flux | laws.hpp:247 | DERIVED | T2 |
| 20 | `r_domain = √(L/(4π F_CMB))` | Stellar pressure-domain radius (T9); Sun≈20,800 AU | laws.hpp:257; Laws/SDT_Complete_Laws.md:338 | DERIVED | T2 |
| 21 | `ε(now) = ε₀(1+z_rec)⁻⁴` | Epoch scaling of relay content (T8) | Laws/SDT_Complete_Laws.md:352 | DERIVED | T2 |

## PART IV — Law III: Convergent Boundary Pressure / occlusion force (T1)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 22 | `F = (π/4) P_eff R₁² R₂² / r²` | **Universal occlusion force law** (T4) — Coulomb, gravity, nuclear | laws.hpp:290; Theory/00_Ruleset.md:53; SPATIAL...:86 | DERIVED | T1 |
| 23 | `P_eff = 4 k_e e²/(π R_p² r_e²)` (= m_p²m_e²c⁵/(4παℏ³)) | Effective pressure (hydrogen calibration) ≈5.225e31 Pa | laws.hpp:272; Theory/02:42 | CALIBRATED | T1 |
| 24 | `f = P_eff / P_conv ≈ 2.125e-17` | Transfer function (atomic↔cosmological) | laws.hpp:277; EMC01 cq01_transfer_function.cpp:457 | COMPUTED | T1 |
| 25 | `R_charge = √(R_p · r_e) ≈ 1.540 fm` | Charge interaction radius (T8) | laws.hpp:283; Theory/00_Ruleset.md:58 | DERIVED | T1 |
| 26 | `F_coulomb = (π/4)P_eff R_charge⁴/r² = k_e e²/r²` | Coulomb force from occlusion | laws.hpp:295; Laws/SDT_Complete_Laws.md:1527 | DERIVED | T2 |
| 27 | `Ω = πR²/r²` | Solid angle occluded by a body | laws.hpp:308; Laws/LAW_OF_CONVERGENT...:131 | DERIVED | T2 |
| 28 | `F_l(r) = C_l Q1^(l) Q2^(l)/r^(2l+2)` | Wake multipole overlap force (general l) | Laws/LAW_OF_VORTEX...:721 | DERIVED | T2 |
| 29 | `l=0 mass · l=1 Coulomb 1/r² · l=2 magnetic 1/r³ · l≥3 nuclear 1/r^(l+1)` | Wake-tensor multipole expansion | Theory/01_Closure_Derivations.md:28; SPATIAL...:359 | DERIVED | T1 |

## PART V — Law IV: Inertial Mass (T1)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 30 | `m = Φ V_disp/(3 ℓ_P³ c²)` | Inertial mass = throughput-reorganisation cost (T5) | laws.hpp:333; Laws/SDT_Complete_Laws.md:592 | DERIVED | T1 |
| 31 | `V_disp = 3 m ℓ_P³ c²/Φ` | Exclusion volume from mass | laws.hpp:328; Theory/02:49 | DERIVED | T1 |
| 32 | `m_inert = m_grav` | Equivalence principle (T6) | laws.hpp:173; Theory/00_Ruleset.md:56 | DERIVED | T1 |
| 33 | `P_cf = ρ_eff c² = P_conv/3` | Marginal stability identity (T10) | laws.hpp:363 | DERIVED | T1 |
| 34 | `δΦ(n̂)/Φ = v·n̂/c` | CMB dipole anisotropy (= COBE/Planck, v/c≈1.23e-3) | Laws/LAW_OF_CONVERGENT...:157 | OBSERVED | T2 |
| 35 | `δ = a·t_P/c = a ℓ_P/c²` | Granular Pulse Invariant (acceleration → pulse asymmetry) | FLM02 cq08_granular_pulse_mechanics.cpp:179 | DERIVED | T1 |
| 36 | `F = [Φ V_disp/(3ℓ_P³c²)]·a = m a` | Newton II from relay permeation | FLM02 cq08_local_update_theorem.cpp:399 | DERIVED | T1 |

## PART VI — Law V: Movement Budget / Special Relativity (T1)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 37 | `γ = 1/√(1 − v²/c²)` | Lorentz factor | laws.hpp:413 | DERIVED | T1 |
| 38 | `dτ/dt = √(1 − v²/c²) = 1/γ` | Time dilation (T11) | laws.hpp:419; Theory/00_Ruleset.md:61 | DERIVED | T1 |
| 39 | `L = L₀/γ` | Length contraction (T12) | laws.hpp:425; Theory/00_Ruleset.md:62 | DERIVED | T1 |
| 40 | `E₀ = m₀ c²` | Rest energy (T13) | laws.hpp:430; Theory/00_Ruleset.md:63 | DERIVED | T1 |
| 41 | `E² = (pc)² + (m₀c²)²` ; `E = γm₀c²` | Energy–momentum (T14) | laws.hpp:435; Theory/00_Ruleset.md:64 | DERIVED | T1 |
| 42 | `v_circ=0 ⟹ v=c, m=0, E=pc` | Photon limit (T15) | laws.hpp:444; Theory/00_Ruleset.md:65 | DERIVED | T1 |
| 43 | `m(v) = γ m₀` | Relativistic mass (C7.1) | Laws/SDT_Complete_Laws.md:637 | DERIVED | T2 |

## PART VII — Bridge / koppa / k-hierarchy & GR observables (T1–T2)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 44 | `v(r) = (c/k)√(R/r)` (k=c/v_surface) | Orbital velocity at radius r (Kepler without G) | laws.hpp:474; Papers/an_argument_for_koppa.md:27 | DERIVED | T1 |
| 45 | `g = v²/R = c²ϟ/R²` | Surface gravity (no G, no M) | laws.hpp:552; Papers/an_argument...:39 | DERIVED | T1 |
| 46 | `R_c = R/k² = zR` | c-boundary radius (T17); = ½ Schwarzschild | laws.hpp:457; Papers/an_argument...:43 | DERIVED | T1 |
| 47 | `dτ/dt = √(1 − zR/r)` | Gravitational time dilation (T16) | laws.hpp:449; Theory/00_Ruleset.md:66 | DERIVED | T1 |
| 48 | `GM = v²r = c²R/k²` | Legacy GM equivalence (GM derived, not input) | laws.hpp:519; Papers/an_argument...:31 | COMPUTED | T2 |
| 49 | `ϟ_per_baryon = ℓ_P² c m_p/ℏ` (= G m_p/c²) | Gravitational c-boundary per baryon (G=ℓ_P²c³/ℏ) | laws.hpp:594 | DERIVED | T1 |
| 50 | `N_bar = ϟ_body/ϟ_per_baryon` | SDT baryon census from zk²=1 (no M in kg) | laws.hpp:609; CQ19d cq19d_baryon_count.cpp:53 | DERIVED | T1 |
| 51 | `δφ = 6πR/(ϟ²·a(1−e²))` | Perihelion precession (Mercury=42.98″/cy) | Papers/an_argument...:411; SPATIAL...PAPER:496 | DERIVED | T1 |
| 52 | `\|δφ\| = 4R/(ϟ²b)` ; `n(r)=1/√(1−2R/(ϟ²r))` | Light deflection (refractive, solar=1.75″) | SPATIAL...PAPER:480 | DERIVED | T1 |
| 53 | `Δt = (4R/(ϟ²c)) ln(4r₁r₂/b²)` | Shapiro signal delay | SPATIAL...PAPER:489 | DERIVED | T2 |
| 54 | `Ω_LT = 2RJ/(ϟ²c r³)` | Frame dragging (Lense–Thirring) | SPATIAL...PAPER:503 | DERIVED | T2 |
| 55 | `ds² = −(1−2R/(ϟ²r))c²dt² + (…)⁻¹dr² + r²dΩ²` | Schwarzschild metric (koppa form) | Papers/an_argument_for_koppa.md:440 | DERIVED | T2 |
| 56 | `c = v_*√(6πR/(δφ·a(1−e²)))` | **c derived from Mercury precession geometry alone** | Papers/Deriving_c_From_Mercurial_Precession.md:125; GOM04 cq24_koppa_closure.cpp:137 | COMPUTED | T1 |
| 57 | `g(r) = v_surf² R·f_enc(r)/r²` | Interior gravity from enclosed-mass fraction (GOM09: 1.82% RMS) | laws.hpp:558; GOM09 gom09_seismic.cpp:337 | DERIVED→CONFIRMED | T1 |

## PART VIII — Law VI: Vortex Topology Quantisation (T1)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 58 | `m(p,q) = M₀/(p²q)^(1/4)` | Vortex mass from torus-knot topology (T18) | Laws/SDT_Complete_Laws.md:1026 | DERIVED | T1 |
| 59 | `M₀ = [π²ℏ³P_conv√3/(2c⁵)]^(1/4) ≈ 1 TeV` | Fundamental mass scale | Laws/SDT_Complete_Laws.md:1028 | COMPUTED | T2 |
| 60 | `v_p² + v_t² = c²` ; `gcd(p,q)=1` | Vortex-boundary budget + toroidal closure | Laws/SDT_Complete_Laws.md:996-1001 | DERIVED | T2 |
| 61 | `W ∈ {1, 3}` | Admitted winding set (electron unknot, proton trefoil) | Laws/LAW_OF_VORTEX...:267 | DERIVED | T1 |
| 62 | `m_p/m_e = (q/p)^(q/p)·[2(p+q)]³ − 1 = (3/2)^(3/2)·10³ − 1 = 1836.117` | Mass ratio from (2,3) trefoil (0.002%) | Laws/LAW_OF_VORTEX...:52; PPT07 cq17_mass_ratio_solver.cpp:19 | PENDING | T1 |
| 62b | `m_p/m_e = 6π⁵ = 1836.118` (alt. identity) | Mass ratio numerical identity (PPT03) | PPT03 cq05_mass_ratio.cpp:50 | PENDING | T1 |
| 63 | `sin²θ* = 1/3, cos²θ* = 2/3` ; `v_p/v_t = √2` | Stable budget angle / velocity partition | Laws/SDT_Complete_Laws.md:1042 | DERIVED | T2 |
| 64 | `μ_ν ≡ 0` (W=0 → no l=2 wake) | Neutrino/antineutrino zero magnetic moment | Laws/LAW_OF_VORTEX...:735; PPT04 ppt04...:126 | DERIVED | T1 |

## PART IX — Coulomb identity & Winding / W+1 (T1)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 65 | `k_e e² = α ℏ c` | Coulomb coupling identity (the coupling is the product) | laws.hpp:700; Theory/00_Ruleset.md:59 | DERIVED | T1 |
| 66 | `R_wake = (W+1) ℏ/(m c)` | W+1 wake-radius rule | laws.hpp:716; PPT03 cq05_mass_ratio.cpp:83 | DERIVED | T1 |
| 67 | `R_p = 4ℏ/(m_p c) = 0.84124 fm` (W=3) | Proton charge radius (matches muonic-H, 0.02%) | laws.hpp:737; Theory/01:64; E32 | DERIVED | T1 |
| 68 | `W_eff = R_p m_p c/ℏ − 1 ≈ 3.0008` | Effective winding (falsification form) | laws.hpp:751; Theory/01:68 | COMPUTED | T2 |
| 69 | `g(W) = R_wake/ƛ_C ; g(1)=α, g(3)=4` | Wake-to-quantum ratio | laws.hpp:757; PPT02 cq03_fine_structure.cpp:73 | DERIVED | T2 |

## PART X — Atomic physics (T2)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 70 | `E = Ry Z²(1/n₁² − 1/n₂²)` ; `R∞ = m_e c α²/(2h)` | Rydberg transition energy; R∞ derived | laws.hpp:633; APS01 cq12_forward_derivation.cpp:174 | DERIVED | T2 |
| 71 | `E_ion = Ry Z²/n²` | Ionisation energy | laws.hpp:640 | DERIVED | T2 |
| 72 | `ΔE = E_n α² Z²/n` | Fine-structure splitting (Sommerfeld) | laws.hpp:648 | DERIVED | T2 |
| 73 | `v_n = α c Z/n` ; `r_n = a₀ n²/Z` | Bohr orbital velocity & radius | laws.hpp:653 | DERIVED | T2 |
| 74 | `α = 1/137.036 = v_1/c = 1/ϟ_H` | Fine-structure constant = hydrogen koppa | Papers/an_argument...:504; SPATIAL...:189 | OBSERVED | T1 |
| 75 | `v = √(2 E_ion/m_e) ; k = c/v ; zk²=1` | Atomic kinematics closure (per element) | ATOMICUS structural_analysis.cpp:200; APS01 cq12_forward_derivation.cpp:406 | DERIVED | T1 |
| 76 | `ΔE_HF = (8/3)α⁴ m_e c²(m_e/m_p)μ_P → 21 cm` | Hydrogen hyperfine splitting (1.42 GHz) | FLM03 cq09_spation_rotation_map.cpp:441 | COMPUTED | T2 |

## PART XI — Nuclear construction grammar (ATOMICUS) (T1)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 77 | `n_t = A − 2Z` ; `n_d = 3Z − A − 2` | Alpha-core grammar (1α + n_d deuterons + n_t tritons) | nuclear.hpp:131; ATOMICUS rules; NP01 | DERIVED | T1 |
| 78 | `Z = 2 + n_d + n_t` ; `A = 4 + 2n_d + 3n_t` | Inverse grammar / validity check | nuclear.hpp:147; ATOMICUS generate_isotopes.cpp:531 | DERIVED | T1 |
| 79 | `n_t = A−2Z+1` ; `n_d = 3Z−A−3` (He-3 core) | Electron-capture alternate grammar | nuclear.hpp:139 | DERIVED | T1 |
| 80 | `2Z ≤ A ≤ 3Z − 2` | Valid alpha wedge (n_d,n_t ≥ 0) | nuclear.hpp:130 | DERIVED | T2 |
| 81 | `ΔD = ν − 2 ; ΔT = −ν` | Binary-fission snap identities | nuclear.hpp:670 | DERIVED | T2 |
| 82 | `y = Z−2 = n_d+n_t ; x = n_d−n_t = 5Z−2A−2` | Nuclide-sheet coordinates | nuclear.hpp:713 | DERIVED | T3 |
| 83 | golden boundary `n_d = n_t ⟺ 2A = 5Z−2` (Z=79 last D>T) | Topological-protection threshold | nuclear.hpp:725; ATOMICUS rules:102 | DERIVED | T3 |
| 84 | `R_nuc ≈ Z·R_p` (R_He = 2R_p, 0.43%) | Nuclear charge-radius linear-Z scaling | laws.hpp:671; NP12 | DERIVED | T2 |

## PART XII — Nuclear binding & packing geometry (T2–T3)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 85 | `B = k·Ω, Ω = 2π(1−cosθ), sinθ = R/d` | Occlusion binding ∝ occluded solid angle | ATOMICUS reports/OCCLUSION_GRADIENT...:11 | PENDING | T2 |
| 86 | `B(d) = 2.224 MeV` from `F=(π/4)P_eff R₁²R₂²/r²` | Deuteron binding from occlusion (NP09) | NP09 PROMPT.md:14 | PENDING | T2 |
| 87 | `B(α) = 28.296 MeV` (tetrahedral 2p+2n occlusion) | Alpha binding from packing (NP10) | NP10 PROMPT.md:23 | PENDING | T2 |
| 88 | tetra `r=√6+2`, octa `r=√2+1`, cube `(√3+1)/2`, cuboct `R=2` | Tammes/kissing geometry (He-4, O-16, Ca-40, Fe-56) | packing.hpp:232-421 | DERIVED | T3 |
| 89 | `E_var=(2Z_eff²−4ZZ_eff+1.25Z_eff)Ry, Z_eff=Z−5/16` | Helium variational binding (Hylleraas) | benchmarks_b01_b25.cpp:619; Laws/SDT_Complete_Laws.md:1585 | COMPUTED | T3 |
| 90 | `m_n − m_p = 1.293 MeV` (extra trefoil circulation) | Neutron–proton mass difference (NP14) | NP14 PROMPT.md:20 | PENDING | T2 |

## PART XIII — Cosmology (redshift, BAO, H₀, age, compact objects) (T2)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 91 | `1 + z = exp(κ₀ d), κ₀ = H₀/c` | Pressure-gradient/strain redshift in static lattice | Hubble zk2_lattice_inference.cpp:91; GOM01 gom01...:585 | DERIVED | T1 |
| 92 | `d_L = d·(1+z)` ; `F = L/(4πd²(1+z)²)` | SDT luminosity distance (1 energy-loss + 1 arrival-rate) | Hubble data/02:200; INVESTIGATION_Hubble_Tension.md:405 | DERIVED | T2 |
| 93 | `c_s = c/√3` | Pre-Clearing (BAO) sound speed | cosmology.hpp:66; Hubble data/02:449 | DERIVED | T2 |
| 94 | `BAO scale = c_s·t_coupled ≈ 147 Mpc` | BAO as pre-Clearing lattice standing wave | cosmology.hpp:71; CR08 | DERIVED | T2 |
| 95 | `δ = 1 − H₀_global/H₀_local` (≈0.077) | Local-underdensity contrast (Hubble tension) | Hubble zk2_h0_gradient.cpp:232 | INDICATED | T2 |
| 96 | `R_CMB = r_s/θ_s ≈ 46 Gly ; age = R_CMB/c` | Distance/age to Clearing from BAO angular scale | Hubble data/03:333 | DERIVED | T2 |
| 97 | `T(z) = T_CMB(1+z)` | CMB temperature scaling | cosmology.hpp:185 | OBSERVED | T2 |
| 98 | `σ₀ = H₀/c` (strain rate replaces expansion) | SDT cosmological strain | cosmology.hpp:92 | DERIVED | T2 |
| 99 | `T_H = ℏc/(8π k_B κ), κ=Rz` ; `L_H = ℏc²/(15360π κ²)` | Hawking temp/luminosity from koppa (no G,M) | Hubble zk2_dark_investigation.cpp:308 | COMPUTED | T2 |
| 100 | `a₀ = c H₀/(2π) ≈ 1.04e-10 m/s²` | Derived Milgrom/convergence-floor acceleration | galactic.hpp:76; APS03 | DERIVED | T1 |

## PART XIV — Galactic rotation (occlusion / eclipse saturation) (T1–T2)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 101 | `v²(R) = c² ϟ_eff/R, ϟ_eff = ϟ_int + ϟ_ext + ϟ_lens` | Rotation velocity from effective koppa budget | galactic.hpp:508; CQ20g | DERIVED | T1 |
| 102 | `ϟ_int = ∫₀ᴿ(v/c)²dr ; ϟ_ext = ∫_R^Rmax (v/c)²(R/r)dr` | Bidirectional disk occlusion integrals | galactic.hpp:560-619; CQ20g cq20g...:245 | DERIVED | T2 |
| 103 | `ϟ(R) ∝ R ⟹ v = const` (flat curve) | Flat-rotation proof from linear koppa ramp | CQ20g cq20g_convergence_occlusion.cpp:304 | DERIVED | T2 |
| 104 | `f_enc(R) = 1 − (1+R/h_R)e^(−R/h_R)` | Exponential-disk enclosed fraction | galactic.hpp:636 | DERIVED | T2 |
| 105 | `g_obs = g_bar/(1−e^(−√(g_bar/a₀)))` ; deep `v⁴=GM_bar a₀` (BTFR slope 4) | Convergence-floor transition disk law | GD05 gd05_twin_regime.cpp:102 | DERIVED | T1 |
| 106 | `B = Φ(ξ), ξ = g_self/a₀` | Universal drafting crossover (scale-invariant coupling) | APS03 cq26_drafting_crossover.cpp:54 | COMPUTED | T1 |
| 107 | `τ = κ_area·Λ/m_p ; f_occ = ½(1−e^(−τ)) ; v = v_lim√(2f_occ)` | 3D volumetric eclipse-saturation (1 fitted κ) | galactic.hpp:1426; GD05 gd05_sparc_rotation_curves.cpp | CALIBRATED | T2 |
| 108 | `K_col(l,b) = ∫(v/c)² e^(−\|z\|/h_z) ds ; Δz_gal = K_col/R₀ ∝ cos b` | Galactic self-lensing & photon z-imprint (LCDM-discriminating) | galactic.hpp:136; CQ22 cq22_galactic_skymap.cpp:98 | DERIVED | T2 |

## PART XV — Magnetosphere, Neutrino, State28D (T2–T3)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 109 | `R_mp = R_E(B_eq²/(2μ₀ P_sw))^(1/6)` | Magnetopause standoff (wake-pressure balance) | magnetosphere.hpp:240 | DERIVED | T2 |
| 110 | `v_A = B/√(μ₀ρ) ; ε_Akasofu = (4π/μ₀)v_sw B² l₀² sin⁴(θ/2)` | Alfvén speed; Akasofu coupling (wake overlap) | magnetosphere.hpp:271,313 | DERIVED | T2 |
| 111 | `K_Anderson = 2ωR/c ≈ 3.1e-6` ; `Δv = K v∞(cosδ_in−cosδ_out)·…` | Flyby anomaly (Earth-spin convergence anisotropy) | Hubble zk2_flyby_anomaly.cpp:44 | DERIVED | T2 |
| 112 | `m = Φ V_disp/(3ℓ_P³c²)` for ν; `R_wake = ℏ/(mc)` (W=0) | Neutrino mass/wake (Law IV, zero winding) | neutrino.hpp:69,82 | DERIVED | T2 |
| 113 | `L_osc = 2.48 E[MeV]/Δm²[eV²]` | Neutrino oscillation length (pitch precession) | neutrino.hpp:139 | DERIVED | T2 |
| 114 | `H₀(ν) < H₀(CMB) < H₀(local)` | Three-way Hubble inequality (SDT prediction) | neutrino.hpp:162 | DERIVED | T2 |
| 115 | `Ξ ∈ ℝ²⁸` (7 levels: 1+2+3+4+5+6+7) | 28-D state manifold | state28d.hpp:37 | — | T2 |
| 116 | `E = (Ω_self+Ω_other)/(4π)·(1+tanh(\|T₅\|/1e10))` | 28D occlusion function E∈[0,1] | state28d.hpp:118 | DERIVED | T2 |

## PART XVI — Spation kinematics & internal-structure results (Investigations) (T2–T3)

| # | Formula | Meaning | Source | Cert | Rel |
|---|---|---|---|---|---|
| 117 | `v(r) = cα√(a₀/r) = (c/ϟ_H)√(R_p/r)` ; `k(r)=(1/α)√(r/a₀)` | Single spation-rotation field: 1.831c @ R_p → αc @ a₀ | FLM03 cq09_spation_rotation_map.cpp:113; SPATIAL...PAPER:354 | DERIVED | T1 |
| 118 | `ϟ_H = (1/α)√(R_p/a₀) = 0.5464` | Proton/Coulomb-orbit invariant koppa (superluminal phase 1.831c) | Papers/an_argument...:551; SPATIAL...PAPER:259 | DERIVED | T2 |
| 119 | `koppa_H = α²a₀ = α·ƛ_C = r_e` | Koppa identity: H c-boundary = classical electron radius | GOM02 cq16_k_hierarchy.cpp:192 | DERIVED | T1 |
| 120 | `δ(r)=g₀(R_p/r)² ; g(r)=g₀(1−(R_p/r)²)` | Lattice gap reopening → 1/r² gravity | FLM05 cq10_lattice_pulse.cpp:116 | DERIVED | T1 |
| 121 | `E(L) = σ_string·L` ; `L_c = 2m_π c²/σ` | Trefoil linear confinement & string breaking (QCD-like) | PPT05 cq11_trefoil_confinement.cpp:264; SPATIAL...PAPER:324 | COMPUTED | T1 |
| 122 | `ω_demand/ω_max = 3(W+1) = 12` | Trefoil spation traction ratio (6π winding) | PPT06 cq14_spation_traction.cpp:171; SPATIAL...PAPER:278 | DERIVED | T1 |
| 123 | `ω_p/ω_e = 3(m_p/m_e)(1/α) ≈ 10⁸` | Nuclear→atomic gear ratio | PPT06 cq14_spation_traction.cpp:272; SPATIAL...PAPER:296 | DERIVED | T2 |
| 124 | `z(r)=ϟ/r ; n(r)=1/√(1−2ϟ/r) ; zk²=1` | Spation-depth scalar field → all GR observables | GOM01 cq15_spation_depth_engine.cpp:57 | DERIVED | T1 |
| 125 | `K(P) = K₀ + K'₀ P, K'₀ = d(1+τ) = 3(1+1/3) = 4` | Seismic bulk-modulus pressure derivative from τ=1/3 (GOM09) | GOM09 gom09_seismic.cpp:457 | DERIVED | T2 |
| 126 | `Ω = √(c²(ϟ₁+ϟ₂)/a³) ; F₁₂ = c²ϟ₁ϟ₂/D²` | Two/three-body orbital dynamics & Lagrange points from koppa | GOM10 gom10_lagrange.cpp:151; Papers/an_argument...:301 | DERIVED | T2 |
| 127 | `Ϟ_sun = 4π²r³/(T²c²)` (SDT Kepler) | Koppa from period+radius — self-calibration (8 planets → 1477 m) | CQ18a cq18a_solar_zdecomp.cpp:66 | DERIVED | T2 |
| 128 | `z_total = z_star+z_galgrav+z_rot+z_sun+z_MW+z_cosmo` | Six-layer SNe Ia redshift decomposition (H₀ tension) | CQ18d cq18d_sne_h0_correction.cpp:181 | COMPUTED | T2 |

## PART XVII — Falsifiable predictions, E01–GOM12 (T2–T3, condensed)

Each experiment's headline predictive formula. Most reuse the core laws above; listed for falsifiability coverage. (Full per-experiment rows in the agent appendix.)

| E## | Headline prediction | Cert |
|---|---|---|
| E13–E20 | EC rate vs charge state: bare (q=Z) ⟹ EC halted; `N_EC = ΔZ` (neutron-budget identity) | — |
| E21–E27 | Orbit-drop lateral shift >10 km (mass-indep.); Mercury 43″/cy from k²-gradient; Pioneer `a≈8.7e-10`; solar J₂ convergence term | — |
| NP08–NP15 | Hoyle from α+4d packing; `B(d)=2.224`, `B(α)=28.296 MeV`; `R=Z·R_p`; `m_n−m_p=1.293 MeV`; μ_p,μ_n from trefoil | PENDING |
| E32 | `R_p = 4ℏ/(m_p c) = 0.84124 fm` (validated vs muonic H) | Validated |
| E41–E50 | `T_CMB` from zk²=1; `H₀=v/d` gradient; BAO standing waves; flat v(r) from eclipse saturation; lensing from k-gradient; `v_GW=c` | mixed |
| E48,E56,E57,E70,E77–E81,E84–E86,E89,E90 | GW speed=c; Compton=QED; Cherenkov shock; `z=GM/rc²`; Sagnac; pair/annihilation 511 keV; AB phase; Josephson `f=2eV/h`; QHE `e²/h`; bremsstrahlung; GZK | Validated |
| E51–E53 | `α=1/137.036` from W=1 torus partition; `m_p/m_e=1836` from winding; g−2 from lattice | — |
| SAR03–E69 | `L_Sun` from convergence; main sequence = k-gradient; Chandrasekhar 1.44 M☉; TOV 2.2 M☉; no singularity; Hawking `T=ℏc³/8πk_B GM` | — |
| E76 | `G = c²R/(k²r)` — G derived, may vary with environment | — |
| GOM09 | Earth interior g/P/v_p from koppa+density, **1.82% RMS, no G/M** (CONFIRMED) | CONFIRMED |
| E91,E100 | Muon g−2 from lattice; `c=c(ω)` lattice dispersion (GRB timing) | — |
| GOM12 | Solar-system convergence budget Σ balances CMB influx (Law II) | — |

---

## Coverage ledger

| Cluster | Files read | Distinct formulas surfaced |
|---|---|---|
| Engine + Benchmarks | 13 (incl. galactic.hpp, nuclear.hpp) | ~165 |
| Theory + Laws + Papers + manuscripts | 14 | ~120 |
| ATOMICUS (rules/tools/reports + isotope/element templates) | ~15 read; ~290 isotopes + ~119 elements deduped to templates | ~40 |
| Hubble | 46 | ~60 |
| Experiments E01–GOM12 | 91 | ~95 |
| Investigations EMC01–PPT07 + Atmospheric_Spallation | 36 | ~50 |
| Investigations CR01–APS03 + E-folders + loose | ~60 | ~75 |

**Notes:** `Atmospheric_Spallation`, `CQ18_ZOA_Lensing`, and several `E##` investigation folders are methodology/spec only (no `.cpp`, no closed-form formula). Per-isotope (`isotopes/*.md`) and per-element (`elements/*.md`) files instantiate the templates in Parts XI–XII once each; they are deduped here, not enumerated. `m_p/m_e` has **three** distinct SDT derivations (Law VI trefoil #62, `6π⁵` #62b, and the 28D Pappus form PPT07) — all ≈1836.1. `Theory_SCT/`, `Compiler/`, and `Release/` are out of scope (see header).
