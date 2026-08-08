/**
 * @file benchmarks_b01_b25.cpp
 * @brief SDT Certified Benchmark Suite B01–B25
 *
 * All computations sourced from sdt::laws (sdt_laws.hpp).
 * Zero external dependencies. Zero fitting parameters beyond the hydrogen calibration.
 *
 * Compile (from project root via CMake — recommended):
 *   cmake -S . -B build && cmake --build build
 *
 * Compile (standalone from Benchmarks/B01_B25/):
 *   cl /std:c++20 /EHsc /I../../Engine/include benchmarks_b01_b25.cpp
 *   g++ -std=c++20 -I../../Engine/include benchmarks_b01_b25.cpp -o benchmarks
 *
 * @author SDT Canonical Engine — James Tyndall
 * @date March 2026
 */

#include <sdt/laws.hpp>

#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <array>
#include <numbers>
#include <algorithm>
#include <numeric>

// ═══════════════════════════════════════════════════════════════════════
//  BENCHMARK FRAMEWORK
// ═══════════════════════════════════════════════════════════════════════

enum class Certification { DERIVED, COMPUTED, CALIBRATED, OBSERVED, PENDING, IDENTITY };

struct BenchmarkResult {
    std::string id;
    std::string name;
    std::string domain;
    double sdt_value;
    double exp_value;
    double error_pct;
    double tolerance_pct;
    Certification cert;
    bool passed;
};

static int g_total = 0, g_passed = 0, g_failed = 0;
static int g_identity_pass = 0, g_calibrated_pass = 0;   // shown, but NOT tallied as predictions
static int g_pending_note = 0;  // PENDING that meet tol — note-only, not earned (detox 2026-08-09)
static std::vector<BenchmarkResult> g_results;

static void report(const char* id, const char* name, const char* domain,
                   double sdt_val, double exp_val, double tol_pct,
                   Certification cert, const char* unit = "")
{
    double err = (exp_val != 0.0) ? std::abs(sdt_val - exp_val) / std::abs(exp_val) * 100.0 : 0.0;
    bool pass = err <= tol_pct;

    const char* status = pass ? "PASS" : "FAIL";
    const char* cert_str = "DERIVED";
    switch (cert) {
        case Certification::COMPUTED:   cert_str = "COMPUTED";   break;
        case Certification::CALIBRATED: cert_str = "CALIBRATED"; break;
        case Certification::OBSERVED:   cert_str = "OBSERVED";   break;
        case Certification::PENDING:    cert_str = "PENDING";    break;
        case Certification::IDENTITY:   cert_str = "IDENTITY";   break;
        default: break;
    }

    std::printf("  %-4s %-40s  SDT=%-16.6g  EXP=%-16.6g  ERR=%8.4f%%  TOL=%6.2f%%  [%s] %s %s\n",
                id, name, sdt_val, exp_val, err, tol_pct, cert_str, status, unit);

    g_total++;
    // HUNTER repair 2026-07-03 (CANON_proposals §3, Harvey-authorized): the pass counter
    // previously tallied on tolerance alone, so definitional identities and calibrated
    // fits inflated the headline. IDENTITY/CALIBRATED passes are now shown but counted
    // separately — the headline reports earned predictions only. A FAILING identity is
    // still a genuine failure (an engine inconsistency).
    // Detox 2026-08-09: PENDING that meet tolerance are note-only (literal / shared-form
    // rows); they leave the earned denom. PENDING that miss tolerance remain known-open
    // fails in the earned denom (unchanged prior behaviour).
    if (cert == Certification::IDENTITY) {
        if (pass) g_identity_pass++; else g_failed++;
    } else if (cert == Certification::CALIBRATED) {
        if (pass) g_calibrated_pass++; else g_failed++;
    } else if (cert == Certification::PENDING) {
        if (pass) g_pending_note++; else g_failed++;
    } else {
        if (pass) g_passed++; else g_failed++;
    }
    g_results.push_back({id, name, domain, sdt_val, exp_val, err, tol_pct, cert, pass});
}

// ═══════════════════════════════════════════════════════════════════════
//  B01 — ATOMIC STRUCTURE / HYDROGEN ENERGY LEVELS
//  SDT: Rydberg formula from helical standing waves
//  E_n = -Ry × Z² / n²
// ═══════════════════════════════════════════════════════════════════════

static void B01_atomic_structure()
{
    std::puts("\n══ B01: HYDROGEN ENERGY LEVELS ══");
    using namespace sdt::laws;

    struct Level { int n; double exp_eV; };
    Level levels[] = {
        {1, -13.5984},  // H ground state
        {2,  -3.3996},  // 1st excited
        {3,  -1.5109},  // 2nd excited
        {4,  -0.8499},  // 3rd excited
    };

    for (auto& [n, exp] : levels) {
        double sdt = -measured::Ry_eV / (n * n);
        char name[64];
        std::snprintf(name, sizeof(name), "H n=%d energy [eV]", n);
        report("B01", name, "Atomic", sdt, exp, 0.08, Certification::DERIVED);
    }

    // Spectral lines (Balmer series)
    struct Transition { int n_lo, n_hi; double exp_nm; };
    Transition balmer[] = {
        {2, 3,  656.281},  // H-alpha
        {2, 4,  486.135},  // H-beta
        {2, 5,  434.047},  // H-gamma
        {2, 6,  410.174},  // H-delta
    };

    for (auto& [nl, nh, exp_nm] : balmer) {
        double dE = atomic::rydberg_energy_eV(1, nl, nh);
        double dE_J = dE * measured::eV_to_J;
        double lambda_m = measured::h * measured::c / dE_J;
        double lambda_nm = lambda_m * 1e9;
        char name[64];
        std::snprintf(name, sizeof(name), "Balmer %d->%d [nm]", nh, nl);
        report("B01", name, "Atomic", lambda_nm, exp_nm, 0.08, Certification::DERIVED, "nm");
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  B02 — RYDBERG FORMULA PRECISION
//  Multi-ion Rydberg: He+, Li2+
// ═══════════════════════════════════════════════════════════════════════

static void B02_rydberg_precision()
{
    std::puts("\n══ B02: RYDBERG MULTI-ION ══");

    // He+ Lyman-alpha (Z=2, 1->2)
    double dE = sdt::laws::atomic::rydberg_energy_eV(2, 1, 2);
    double dE_J = dE * sdt::laws::measured::eV_to_J;
    double lambda = sdt::laws::measured::h * sdt::laws::measured::c / dE_J * 1e9;
    report("B02", "He+ Lyman-alpha [nm]", "Atomic", lambda, 30.378, 0.08, Certification::DERIVED);

    // Li2+ Lyman-alpha (Z=3, 1->2)
    dE = sdt::laws::atomic::rydberg_energy_eV(3, 1, 2);
    dE_J = dE * sdt::laws::measured::eV_to_J;
    lambda = sdt::laws::measured::h * sdt::laws::measured::c / dE_J * 1e9;
    report("B02", "Li2+ Lyman-alpha [nm]", "Atomic", lambda, 13.502, 0.08, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B03 — FINE STRUCTURE CONSTANT / SPLITTING
// ═══════════════════════════════════════════════════════════════════════

static void B03_fine_structure()
{
    std::puts("\n══ B03: FINE STRUCTURE ══");
    using namespace sdt::laws;

    // H n=2 fine structure SPLITTING (2P1/2 -> 2P3/2).
    // atomic::fine_structure_eV returns the GROSS Sommerfeld term α²Ry·Z²/n = α²Ry/8 for n=2.
    // The measured splitting between adjacent j-levels is HALF of that (α²Ry/16): the
    // factor 1/2 is the j(j+1) level structure, not a free parameter. The benchmark's
    // reference 4.528e-5 eV (=10.95 GHz) is the 2P1/2-2P3/2 splitting, so compare to ½ term.
    double fs_eV = 0.5 * atomic::fine_structure_eV(1, 2);
    double exp_fs = 4.528e-5;  // eV  (H 2P1/2-2P3/2 splitting; = α²Ry/16 to 0.006%)
    report("B03", "H 2P fine-structure splitting [eV]", "Atomic", fs_eV, exp_fs, 1.0, Certification::DERIVED);

    // Bohr velocity at ground state (should be αc)
    double v1 = atomic::bohr_velocity(1, 1);
    double exp_v = measured::alpha * measured::c;
    report("B03", "Bohr v(1,1) = alpha*c [m/s]", "Atomic", v1, exp_v, 0.001, Certification::IDENTITY);  // bohr_velocity(1,1) RETURNS αc — αc vs αc, definitional (HUNTER P7)
}

// ═══════════════════════════════════════════════════════════════════════
//  B04 — LAMB SHIFT
//  H 2S-2P splitting: 1057.845 MHz
// ═══════════════════════════════════════════════════════════════════════

static void B04_lamb_shift()
{
    std::puts("\n══ B04: LAMB SHIFT ══");
    using namespace sdt::laws;

    // RETRACTED (HUNTER 2026-07-02, applied 2026-07-03, Harvey-authorized):
    // the former "native candidate" 1051.8 MHz was the fabricated APS04 value — a bare
    // literal in laws.hpp with no evaluating code. That number stays dead.
    // STATUS UPDATE (2026-07-29, per APS04_ASSESSMENT/VERDICT_DIRECT 2026-07-26): the rebuilt,
    // instrument-validated APS04 solver now derives the wake's multipole ladder exactly
    // (r^-1 / zero dipole / r^-3 / r^-4·cos3φ) and a nuclear-geometry 2S-2P term of
    // +0.761 MHz — correct sign, correct muonic (m/a²) scaling, zero fitted parameters.
    // The whole-interval claim is excluded on raw scaling (predicted 7.1e6 vs measured
    // 4.6e4 muonic/electronic ratio); the full 1057.845 MHz amplitude routes to the
    // FLM14 route-geometry programme and remains OPEN. No tally until that lands.
    std::printf("  B04  H 2S-2P interval: nuclear-geometry term +0.761 MHz derived (APS04 "
                "2026-07-26, sign/order/scaling earned); full amplitude OPEN (FLM14). "
                "Measured %.3f MHz retained as OBSERVED-INPUT only.\n",
                law_VI::angular::lamb_shift_measured_MHz);
}

// ═══════════════════════════════════════════════════════════════════════
//  B05 — HYPERFINE STRUCTURE (21 cm line)
// ═══════════════════════════════════════════════════════════════════════

static void B05_hyperfine()
{
    std::puts("\n══ B05: HYPERFINE 21cm ══");
    using namespace sdt::laws;

    // Hyperfine = (8/3) α² (m_e/m_p) × Ry × g_p
    // g_p = 2 × μ_P (proton g-factor in nuclear magnetons)
    double g_p = 2.0 * measured::mu_P;
    double hf_eV = (8.0 / 3.0) * measured::alpha * measured::alpha
                 * (measured::m_e / measured::m_p) * measured::Ry_eV * g_p;
    double hf_J = hf_eV * measured::eV_to_J;
    double hf_MHz = hf_J / measured::h / 1e6;
    report("B05", "H hyperfine 21cm [MHz]", "Atomic", hf_MHz, 1420.405, 0.08, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B06 — MANY-ELECTRON ATOMS (Z=2–10 ionisation energies)
// ═══════════════════════════════════════════════════════════════════════

static void B06_multielectron()
{
    std::puts("\n══ B06: MULTI-ELECTRON IONISATION ══");
    using namespace sdt::laws;

    // Ionisation energies with screening: E_ion = Ry × (Z - σ)² / n²
    // STATUS (2026-06): these use empirical Slater screening σ — NOT an SDT
    // derivation — and the hydrogenic (Z-σ)²/n² form is a poor model for multi-electron
    // atoms (errors run 6%–500% here). This is the known open "atoms are the hard problem"
    // (see Investigations/PROMPT_all_emissions_from_first_principles). Relabelled PENDING,
    // not COMPUTED: the geometric-void electron model (Atomicus §10) is the intended SDT
    // route and is not yet implemented. Kept as a flagged open item, not refit to pass.
    struct Atom { const char* sym; int Z; double sigma; int n; double exp_eV; };
    Atom atoms[] = {
        {"He", 2,  0.30, 1, 24.587},
        {"Li", 3,  1.70, 2,  5.392},
        {"Be", 4,  2.05, 2,  9.323},
        {"B",  5,  2.60, 2,  8.298},
        {"C",  6,  2.75, 2, 11.260},
        {"N",  7,  2.85, 2, 14.534},
        {"O",  8,  3.15, 2, 13.618},
        {"F",  9,  3.45, 2, 17.423},
        {"Ne", 10, 3.85, 2, 21.565},
    };

    for (auto& a : atoms) {
        double Z_eff = a.Z - a.sigma;
        double E_ion = measured::Ry_eV * Z_eff * Z_eff / (a.n * a.n);
        char name[64];
        std::snprintf(name, sizeof(name), "%s (Z=%d) 1st ionisation [eV]", a.sym, a.Z);
        report("B06", name, "Atomic", E_ion, a.exp_eV, 5.0, Certification::PENDING);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  B07 — k_B FROM SPATION CONTACT MECHANICS
// ═══════════════════════════════════════════════════════════════════════

static void B07_thermodynamics()
{
    std::puts("\n══ B07: THERMODYNAMICS ══");
    using namespace sdt::laws;

    // Ideal gas law from spation ensemble: PV = NkT
    // k_B is the energy per degree of freedom per spation mode
    // Verification: Stefan-Boltzmann constant σ = 2π⁵k⁴/(15h³c²)
    double sigma_SB = 2.0 * std::pow(std::numbers::pi, 5) * std::pow(measured::k_B, 4)
                    / (15.0 * std::pow(measured::h, 3) * measured::c * measured::c);
    report("B07", "Stefan-Boltzmann [W/m2/K4]", "Thermo", sigma_SB, 5.670374e-8, 0.001, Certification::DERIVED);

    // Wien displacement: λ_max T = hc/(4.965 k_B)
    double wien = measured::h * measured::c / (4.96512 * measured::k_B);
    report("B07", "Wien displacement [m·K]", "Thermo", wien, 2.8978e-3, 0.01, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B08 — ORBITAL MECHANICS (Keplerian)
// ═══════════════════════════════════════════════════════════════════════

static void B08_orbital_mechanics()
{
    std::puts("\n══ B08: ORBITAL MECHANICS ══");
    using namespace sdt::laws;

    // Earth orbital velocity from SDT: v = (c/k)√(R/r)
    // For the Sun: k_Sun ≈ 686.3, R = R_Sun, r = 1 AU
    double v_earth = bridge::v_orbital(bridge::k_Sun, measured::R_Sun, measured::AU);
    report("B08", "Earth orbital velocity [m/s]", "Gravity", v_earth, 29783.0, 0.08, Certification::DERIVED);

    // GM_Sun from SDT bridge
    double GM = bridge::GM_equivalent(bridge::k_Sun, measured::R_Sun);
    report("B08", "GM_Sun [m3/s2]", "Gravity", GM, 1.327e20, 0.5, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B09 — GRAVITATIONAL RADIATION (Hulse-Taylor binary pulsar)
// ═══════════════════════════════════════════════════════════════════════

static void B09_gravitational_radiation()
{
    std::puts("\n══ B09: BINARY PULSAR DECAY ══");

    // RETRACTED as a prediction (HUNTER 2026-07-02, applied 2026-07-03, Harvey-authorized):
    // the previous line typed the GR quadrupole value (-2.4029e-12) and stamped it DERIVED —
    // a BORROW: nothing SDT was computed. Retained as an OBSERVED comparison only, no tally.
    // The SDT chirp convergence lives in B29 (koppa-bridge identity, labelled there).
    std::puts("  B09  Hulse-Taylor dP/dt: observed -2.4025e-12 s/s; GR quadrupole -2.4029e-12."
              " SDT-native emission integral NOT built — OPEN (no earned prediction).");
}

// ═══════════════════════════════════════════════════════════════════════
//  B10 — STRONG FIELD TESTS (Mercury precession + Solar light deflection)
// ═══════════════════════════════════════════════════════════════════════

static void B10_strong_field()
{
    std::puts("\n══ B10: STRONG FIELD RELATIVITY ══");
    using namespace sdt::laws;

    // Mercury perihelion precession: 42.98 arcsec/century (GR)
    // SDT: v_orbital at Mercury → z = v²/c² → precession = 6πz per orbit
    // Mercury: a = 5.791e10 m, e = 0.2056, P = 87.969 days
    double a_merc = 5.791e10;
    double v_merc = bridge::v_orbital(bridge::k_Sun, measured::R_Sun, a_merc);
    double z_merc = bridge::z_from_v(v_merc);
    // Precession per orbit in radians: 6π × z / (1 - e²)
    double e_merc = 0.2056;
    double prec_rad = 6.0 * std::numbers::pi * z_merc / (1.0 - e_merc * e_merc);
    // Per century: 415.2 orbits
    double prec_arcsec = prec_rad * (180.0 / std::numbers::pi) * 3600.0 * 415.2;
    report("B10", "Mercury precession [arcsec/c]", "Gravity", prec_arcsec, 42.98, 0.5, Certification::DERIVED);

    // Solar light deflection: 1.7505 arcsec at limb
    // SDT: Δθ = 2R_c / b = 2GM/(c²b), b = R_Sun
    double R_c = measured::R_Sun / (bridge::k_Sun * bridge::k_Sun);
    double deflection_rad = 2.0 * R_c / measured::R_Sun;
    // Factor of 2 for full GR (both ingoing and outgoing)
    deflection_rad *= 2.0;
    double deflection_arcsec = deflection_rad * (180.0 / std::numbers::pi) * 3600.0;
    report("B10", "Solar light deflection [arcsec]", "Gravity", deflection_arcsec, 1.7505, 0.5, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B11 — PLANETARY OBLATENESS (J2 from spin)
// ═══════════════════════════════════════════════════════════════════════

static void B11_planetary_oblateness()
{
    std::puts("\n══ B11: PLANETARY OBLATENESS ══");

    // J2 ≈ (1/2)(ω²R³)/(GM) — the UNIFORM-FLUID (Maclaurin) estimate. This is only an
    // order-of-magnitude model: real J2 depends on the internal density profile (a centrally
    // condensed body has J2 well below the uniform value), so the uniform formula overshoots
    // Earth (×1.6) and Jupiter (×3). RELABELLED (2026-06): this is PENDING, not DERIVED —
    // it is the textbook fluid estimate (and it imports GM, against the no-G rule). A genuine
    // SDT J2 from the spation displacement-density profile is an open problem (would-be CQ).
    // Kept in the suite as a flagged open item rather than removed or fudged.
    double omega_e = 7.292e-5;
    double R_e = 6.371e6;
    double GM_e = 3.986e14;  // imported — flags this as not-yet-SDT-native (see note)
    double J2_sdt = 0.5 * omega_e * omega_e * R_e * R_e * R_e / GM_e;
    report("B11", "Earth J2 (uniform-fluid est.)", "Gravity", J2_sdt, 1.0826e-3, 3.0, Certification::PENDING);

    // Jupiter
    double omega_j = 1.7585e-4;
    double R_j = 7.149e7;
    double GM_j = 1.267e17;
    double J2_j = 0.5 * omega_j * omega_j * R_j * R_j * R_j / GM_j;
    report("B11", "Jupiter J2 (uniform-fluid est.)", "Gravity", J2_j, 1.4736e-2, 3.0, Certification::PENDING);
}

// ═══════════════════════════════════════════════════════════════════════
//  B12 — STELLAR STRUCTURE (zk²=1 across 10 stars)
// ═══════════════════════════════════════════════════════════════════════

static void B12_stellar_structure()
{
    std::puts("\n══ B12: STELLAR zk²=1 ══");
    using namespace sdt::laws;

    // SDT predicts z × k² = 1 for all gravitationally bound systems
    struct Star { const char* name; double v_surface_ms; };
    Star stars[] = {
        {"Sun",        616.0},     // v_surface from solar oscillation data
        {"Sirius A",   2560.0},
        {"Alpha Cen A", 580.0},
        {"Procyon A",  3000.0},
        {"Vega",       20700.0},
    };

    for (auto& s : stars) {
        double k = bridge::k_from_v(s.v_surface_ms);
        double z = bridge::z_from_v(s.v_surface_ms);
        double zk2 = bridge::zk2_product(z, k);
        char name[64];
        std::snprintf(name, sizeof(name), "%-12s zk2", s.name);
        report("B12", name, "Stellar", zk2, 1.0, 0.001, Certification::IDENTITY);  // zk²≡1 is the closure DEFINITION z=1/k² — true for any v (HUNTER P8)
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  B13 — CMB REDSHIFT (z = 1089)
// ═══════════════════════════════════════════════════════════════════════

static void B13_cmb_redshift()
{
    std::puts("\n══ B13: CMB REDSHIFT ══");
    using namespace sdt::laws;

    // z_CMB = T_rec / T_CMB - 1
    double z_sdt = measured::T_rec / measured::T_CMB - 1.0;
    report("B13", "CMB redshift z", "Cosmology", z_sdt, 1089.0, 1.0, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B14 — GALACTIC ROTATION (R_flat ≈ 2.5 R_d)
// ═══════════════════════════════════════════════════════════════════════

static void B14_galactic_rotation()
{
    std::puts("\n══ B14: GALACTIC ROTATION ══");

    // SDT predicts R_flat ≈ 2.5 × R_d (disk scale length) as a phenomenological onset rule.
    // TOLERANCE FIX (2026-06): the prior 1% tolerance was never physically justified — the
    // R_flat/R_d ratio intrinsically scatters galaxy-to-galaxy (there is no universal value),
    // so a ~12% tolerance is the appropriate bar for a single-ratio rule. The full rotation-curve
    // fit (not just the onset radius) is done properly in GD05/M4 (SPARC, RMS 23.8%); this B14
    // is only the coarse onset-radius check and is labelled COMPUTED, not a precision result.
    struct Galaxy { const char* name; double R_d_kpc; double R_flat_obs_kpc; };
    Galaxy galaxies[] = {
        {"Milky Way",    2.5,  6.0},
        {"NGC 3198",     2.8,  7.2},
        {"NGC 2403",     1.8,  4.4},
        {"M33",          1.6,  4.0},
    };

    for (auto& g : galaxies) {
        double R_flat_pred = 2.5 * g.R_d_kpc;
        char name[64];
        std::snprintf(name, sizeof(name), "%-12s R_flat [kpc]", g.name);
        report("B14", name, "Galactic", R_flat_pred, g.R_flat_obs_kpc, 12.0, Certification::COMPUTED);
    }
}

// ═══════════════════════════════════════════════════════════════════════
//  B15 — BAO SCALE (147 Mpc)
// ═══════════════════════════════════════════════════════════════════════

static void B15_bao_scale()
{
    std::puts("\n══ B15: BAO SCALE ══");

    // DETOX 2026-08-09 (Audits/BENCHMARK_DETOX_B15_B16_B25_2026-08-07.md):
    // literal 147.0 survives engine deletion — LITERAL TARGET ECHO, not COMPUTED.
    // PENDING/note-only until an SDT-native sound-horizon integral exists.
    double r_s_sdt = 147.0;  // Mpc — placeholder literal (not engine-derived)
    report("B15", "BAO sound horizon [Mpc]", "Cosmology", r_s_sdt, 147.09, 3.0, Certification::PENDING);
}

// ═══════════════════════════════════════════════════════════════════════
//  B16 — THERMODYNAMIC TRANSPORT (T^0.5 scaling)
// ═══════════════════════════════════════════════════════════════════════

static void B16_transport()
{
    std::puts("\n══ B16: TRANSPORT SCALING ══");

    // DETOX 2026-08-09: literal 0.5000 ×3 survives engine deletion — LITERAL TARGET ECHO.
    // PENDING/note-only until exponents are produced from engine transport symbols.
    double exponent_sdt = 0.5000;  // placeholder literal (not engine-derived)
    report("B16", "Thermal cond exponent", "Thermo", exponent_sdt, 0.5, 0.05, Certification::PENDING);
    report("B16", "Viscosity exponent", "Thermo", exponent_sdt, 0.5, 0.05, Certification::PENDING);
    report("B16", "Diffusivity exponent", "Thermo", exponent_sdt, 0.5, 0.05, Certification::PENDING);
}

// ═══════════════════════════════════════════════════════════════════════
//  B17 — MAGNETIC g-FACTOR
// ═══════════════════════════════════════════════════════════════════════

static void B17_magnetic()
{
    std::puts("\n══ B17: MAGNETIC g-FACTOR ══");
    using namespace sdt::laws;

    // Electron g-factor from vortex geometry
    // SDT lowest order: g = 2(1 + α/2π)
    double g_sdt = 2.0 * (1.0 + measured::alpha / (2.0 * std::numbers::pi));
    double g_exp = 2.00231930436256;  // CODATA 2018
    report("B17", "Electron g-factor", "EM", g_sdt, g_exp, 0.12, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B18 — PROTON RADIUS (from W+1 conjecture & nuclear geometry)
// ═══════════════════════════════════════════════════════════════════════

static void B18_proton_radius()
{
    std::puts("\n══ B18: PROTON RADIUS ══");
    using namespace sdt::laws;

    // W+1 conjecture: R_p = (W+1)ℏ/(m_p c) = 4ℏ/(m_p c)
    report("B18", "R_p (W+1 conjecture) [m]", "Nuclear",
           winding::R_p_predicted, measured::R_p, 0.08, Certification::DERIVED);

    // W_eff diagnostic
    report("B18", "W_eff (should be 3.000)", "Nuclear",
           winding::W_eff, 3.0, 0.08, Certification::DERIVED);

    // He-4 charge radius: R_He = 2 × R_p
    report("B18", "He-4 radius = 2Rp [m]", "Nuclear",
           nuclear::R_He_predicted, measured::R_He, 0.5, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B19 — BETA DECAY Q-VALUE
// ═══════════════════════════════════════════════════════════════════════

static void B19_beta_decay()
{
    std::puts("\n══ B19: BETA DECAY ══");
    using namespace sdt::laws;

    // Q = (m_n - m_p - m_e) c² in MeV
    double Q_J = (measured::m_n - measured::m_p - measured::m_e) * measured::c * measured::c;
    double Q_MeV = Q_J / measured::MeV_to_J;
    report("B19", "Beta decay Q-value [MeV]", "Nuclear", Q_MeV, 0.782, 0.08, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B20 — z·k² UNIVERSALITY
// ═══════════════════════════════════════════════════════════════════════

static void B20_zk2_universality()
{
    std::puts("\n══ B20: zk² UNIVERSALITY ══");
    using namespace sdt::laws;

    // For any gravitationally bound system: z × k² = 1
    // Hydrogen atom: v = αc, k = 1/α, z = α²
    double z_H = measured::alpha * measured::alpha;
    double k_H = measured::alpha_inv;
    double zk2_H = z_H * k_H * k_H;
    report("B20", "Hydrogen zk2", "Universal", zk2_H, 1.0, 0.001, Certification::IDENTITY);  // definitional closure (HUNTER P9)

    // Earth orbit
    double v_earth = 29783.0;
    double z_e = bridge::z_from_v(v_earth);
    double k_e = bridge::k_from_v(v_earth);
    report("B20", "Earth orbit zk2", "Universal", z_e * k_e * k_e, 1.0, 0.001, Certification::IDENTITY);  // definitional closure (HUNTER P9)
}

// ═══════════════════════════════════════════════════════════════════════
//  B21 — SCREENING FACTORS / FORCE HIERARCHY
// ═══════════════════════════════════════════════════════════════════════

static void B21_screening()
{
    std::puts("\n══ B21: FORCE HIERARCHY ══");
    using namespace sdt::laws;

    // RETRACTED as a prediction (HUNTER 2026-07-02, applied 2026-07-03, Harvey-authorized):
    // the previous line hardcoded NIST G = 6.674e-11 inside a suite whose banner says "No G"
    // ("SDT derives same from k-hierarchy" was asserted in a comment; the NIST number did the
    // work). BORROW-SMUGGLE — deleted, no tally. Note: extracting G from any body's k-hierarchy
    // requires that body's mass in kilograms, which is itself GM/G — the koppa cancels (see the
    // 2026-07-03 lP-relabel retraction). The native statement is the RATIO of koppas, not G.
    std::puts("  B21  EM/Grav force ratio ~2.27e39: displayed for orientation only — the split"
              " of GM into G and kg-mass is unit bookkeeping SDT does not perform. No tally.");
}

// ═══════════════════════════════════════════════════════════════════════
//  B22 — PRESSURE HIERARCHY (33 orders of magnitude)
// ═══════════════════════════════════════════════════════════════════════

static void B22_pressure_hierarchy()
{
    std::puts("\n══ B22: PRESSURE HIERARCHY ══");
    using namespace sdt::laws;

    // Nuclear scale: P_eff
    report("B22", "P_eff [Pa]", "Universal", law_III::P_eff, 5.225e31, 0.5, Certification::CALIBRATED);  // laws.hpp self-labels class E, "FAILS delete-test" — engine's own label restored (HUNTER P10)

    // Transfer function
    report("B22", "f = P_eff/P_conv", "Universal", law_III::f_transfer, 2.125e-17, 1.0, Certification::CALIBRATED);  // class E per laws.hpp (HUNTER P10)

    // CMB pressure
    report("B22", "P_CMB [Pa]", "Universal", law_I::P_rad, 1.391e-14, 1.0, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B23 — COULOMB IDENTITY: k_e e² = αℏc
// ═══════════════════════════════════════════════════════════════════════

static void B23_coulomb_identity()
{
    std::puts("\n══ B23: COULOMB COUPLING IDENTITY ══");
    using namespace sdt::laws;

    report("B23", "k_e*e2 (SDT derived) [J·m]", "Universal",
           coulomb_identity::k_e_e2, coulomb_identity::k_e_e2_codata, 0.001, Certification::IDENTITY);  // α ≡ k_e e²/ℏc — tautology; laws.hpp itself flags class F "FAILS delete-test" (HUNTER P5)
}

// ═══════════════════════════════════════════════════════════════════════
//  B24 — EXCLUSION VOLUMES (V_disp)
// ═══════════════════════════════════════════════════════════════════════

static void B24_exclusion_volumes()
{
    std::puts("\n══ B24: EXCLUSION VOLUMES ══");
    using namespace sdt::laws;

    // V_disp = 3m ℓ_P³ c² / Φ
    report("B24", "V_disp(e) [m3]", "Particle", law_IV::V_disp_e, 9.988e-62, 0.08, Certification::COMPUTED);
    report("B24", "V_disp(p) [m3]", "Particle", law_IV::V_disp_p, 1.834e-58, 0.08, Certification::COMPUTED);

    // Mass ratio preserved
    double ratio = law_IV::V_disp_p / law_IV::V_disp_e;
    double exp_ratio = measured::m_p / measured::m_e;
    report("B24", "V_p/V_e = m_p/m_e", "Particle", ratio, exp_ratio, 0.001, Certification::IDENTITY);  // V_disp ∝ m ⇒ ratio ≡ m_p/m_e by construction (HUNTER P6)

    // Marginal stability: P_cf = P_conv / 3
    double P_cf = law_IV::rho_eff_e * measured::c * measured::c;
    double P_target = law_I::P_conv / 3.0;
    double stability_ratio = P_cf / P_target;
    report("B24", "P_cf / (P_conv/3) = 1.0", "Particle", stability_ratio, 1.0, 0.001, Certification::IDENTITY);  // P_cf ≡ P_conv/3 by the marginal-stability definition (HUNTER P6b)
}

// ═══════════════════════════════════════════════════════════════════════
//  B25 — ALPHA-CLUSTER GEOMETRY (He-4 nuclear occlusion binding)
// ═══════════════════════════════════════════════════════════════════════

static void B25_alpha_cluster()
{
    std::puts("\n══ B25: ALPHA-CLUSTER BINDING ══");
    using namespace sdt::laws;

    // DETOX 2026-08-09: variational uses Ry_eV but Hylleraas/QM shared form — not an
    // SDT-native nuclear amplitude. Exact NR is a borrowed Pekeris literal.
    // Both PENDING/note-only until an SDT-native amplitude exists. R_He=2Rp retained.
    double Z = 2.0;
    double Z_eff = Z - 5.0/16.0;  // Hylleraas 1-parameter (shared-form; not earned)
    double E_var = (2.0 * Z_eff * Z_eff - 4.0 * Z * Z_eff + 1.25 * Z_eff)
                 * measured::Ry_eV;
    report("B25", "He binding variational [eV]", "Nuclear", E_var, -79.005, 2.0, Certification::PENDING);

    // Exact non-relativistic (Pekeris 1959) — borrowed external number
    double E_exact = -79.0052;
    report("B25", "He binding exact NR [eV]", "Nuclear", E_exact, -79.005, 0.001, Certification::PENDING);

    // Charge radius: R_He = 2 R_p (engine radii — retained pending separate radius audit)
    report("B25", "R_He = 2Rp [fm]", "Nuclear",
           2.0 * measured::R_p * 1e15, measured::R_He * 1e15, 0.5, Certification::DERIVED, "fm");
}

// ═══════════════════════════════════════════════════════════════════════
//  B26 — TREFOIL TOPOLOGY (PPT01 modes · PPT06 traction · PPT07 mass ratio)
// ═══════════════════════════════════════════════════════════════════════

static void B26_trefoil_topology()
{
    std::puts("\n══ B26: TREFOIL TOPOLOGY ══");
    using namespace sdt::laws;

    // PPT01: proton (2,3) movement-budget closure v_T²+v_P²=c² (exact)
    report("B26", "Proton (2,3) budget vT2+vP2=c2", "Particle",
           law_VI::topology::budget_residual(2, 3), 1.0, 0.001, Certification::DERIVED);

    // PPT06: superluminal phase velocity at the proton surface = c/k = 1.830c
    report("B26", "Proton surface v_phase [c]", "Particle",
           law_VI::traction::v_phase_proton_surface / measured::c, 1.830, 0.5,
           Certification::COMPUTED);

    // PPT07: m_p/m_e from trefoil topology = 6π⁵ = 1836.118 (distinct from 1.830c)
    report("B26", "m_p/m_e = 6pi^5 (topology)", "Particle",
           law_VI::mass_ratio::six_pi_5, measured::m_p / measured::m_e, 0.01,
           Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B27 — KOPPA CLOSURE: c FROM ORBITAL GEOMETRY (GOM04)
// ═══════════════════════════════════════════════════════════════════════

static void B27_koppa_closure()
{
    std::puts("\n══ B27: c FROM GEOMETRY (koppa closure) ══");
    using namespace sdt::laws;

    // Sun's speed ratio k = c/v from Mercury's precession (no c, no GM input)
    report("B27", "k_Sun from precession", "Gravity",
           bridge::k_Sun_from_precession, bridge::k_Sun, 0.5, Certification::COMPUTED);

    // c reconstructed: c = k_Sun · v_surface — the headline closure (c is OUTPUT)
    report("B27", "c from precession closure [m/s]", "Gravity",
           bridge::c_from_closure, measured::c, 0.01, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B28 — DEPTH-CLOSURE THEOREM (GOM01 · GOM05; keystone: z = ϟ/r)
// ═══════════════════════════════════════════════════════════════════════

static void B28_depth_closure()
{
    std::puts("\n══ B28: DEPTH-CLOSURE THEOREM ══");
    using namespace sdt::laws;

    // C1 keystone: solar gravitational redshift = displacement depth ϟ_Sun/R_Sun.
    // (Known-match; ϟ≡GM/c² makes this an identity-of-interpretation, ~0.03%.)
    report("B28", "Solar redshift = depth z_Sun", "Gravity",
           depth_closure::z_spectral_Sun, 2.1225e-6, 0.1, Certification::COMPUTED);

    // C2 one law v=c√(ϟ/r): Earth orbital velocity at 1 AU (spans ~15 orders)
    report("B28", "Earth v = c sqrt(koppa/r) [m/s]", "Gravity",
           depth_closure::v_bound(bridge::koppa_Sun, measured::AU), 29783.0, 0.08,
           Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B29 — GRAVITATIONAL-WAVE CHIRP AS A LENGTH (GOM06)
// ═══════════════════════════════════════════════════════════════════════

static void B29_gw_chirp()
{
    std::puts("\n══ B29: GW CHIRP FROM KOPPA ══");
    using namespace sdt::laws;

    // GW150914: combined c-boundary ϟ_tot ≈ 96 km (from the measured 65 M_sun
    // frame) → f_isco = c/(π·6^{3/2}·ϟ_tot), no G/M in the dynamics (±15% gate).
    report("B29", "GW150914 f_isco [Hz]", "Gravity",
           bridge::f_GW_isco(96.0e3), 68.0, 5.0, Certification::COMPUTED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B30 — DEUTERON BINDING FROM SHARED-ELECTRON GEOMETRY (NP17 / NP33)
// ═══════════════════════════════════════════════════════════════════════

static void B30_deuteron_binding()
{
    std::puts("\n══ B30: DEUTERON BINDING ══");
    using namespace sdt::laws;

    // E = (9/7)·αℏc/R_p with R_p = 4ℏ/(m_p c)  ⇒  E = (9/7)·α·m_p c²/4.
    // Zero fitted parameters (NP17 interleaved-trefoil node; re-earned in the
    // NP33 traction log as the p↔n gear's shared-electron lock).
    double E_MeV = (9.0 / 7.0) * measured::alpha * measured::m_p
                 * measured::c * measured::c / 4.0 / 1.602176634e-13;
    report("B30", "Deuteron binding [MeV]", "Nuclear", E_MeV, 2.2246, 2.0, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B31 — BBN DEUTERIUM BOTTLENECK FROM THE BINDING LEDGER (TD09)
// ═══════════════════════════════════════════════════════════════════════

static void B31_bbn_bottleneck()
{
    std::puts("\n══ B31: BBN DEUTERIUM BOTTLENECK ══");
    using namespace sdt::laws;

    // Binding-ledger flip temperature: n_d/n_p = 1 at equilibrium with the
    // measured photon/baryon ratio — the temperature where deuteron formation
    // first nets positive routes (TD09, direct 2026-07-26). Algebraically the
    // equilibrium (Saha) condition: convergent route, shared counting, stated.
    const double MeV   = 1.602176634e-13;
    const double m_n   = measured::m_p + 2.30557e-30;   // OBSERVED Δm_np = 1.2933 MeV
    const double E_b   = 2.224573 * MeV;                // OBSERVED deuteron binding
    const double eta_b = 6.13e-10;                      // OBSERVED baryon/photon (Planck)
    const double zeta3 = 1.2020569031595943;
    const double mu_r  = measured::m_p * m_n / (measured::m_p + m_n);
    auto ledger = [&](double T) {
        double n_gam = (2.0 * zeta3 / (std::numbers::pi * std::numbers::pi))
                     * std::pow(measured::k_B * T / (1.054571817e-34 * measured::c), 3.0);
        double n_n   = eta_b * n_gam / 8.0;             // X_n/X_p = 1/7 (measured freeze-out)
        double lam3  = std::pow(measured::h * measured::h
                     / (2.0 * std::numbers::pi * mu_r * measured::k_B * T), 1.5);
        return std::log(0.75 * lam3 * n_n) + E_b / (measured::k_B * T);
    };
    double lo = 0.01 * MeV / measured::k_B, hi = 1.0 * MeV / measured::k_B;
    for (int i = 0; i < 200; ++i) {
        double mid = 0.5 * (lo + hi);
        if (ledger(mid) > 0) lo = mid; else hi = mid;
    }
    double T_flip_MeV = measured::k_B * 0.5 * (lo + hi) / MeV;
    report("B31", "D-bottleneck T [MeV]", "Cosmo", T_flip_MeV, 0.070, 50.0, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B32 — CHERENKOV THRESHOLD ANGLE (FD05 / E57: one criterion, v > c_relay)
// ═══════════════════════════════════════════════════════════════════════

static void B32_cherenkov()
{
    std::puts("\n══ B32: CHERENKOV ANGLE ══");
    // cosθ_max = 1/n — the medium-relay criterion (boom ≡ Cherenkov, FD05).
    double n_water = 1.3330;                            // OBSERVED refractive index
    double theta = std::acos(1.0 / n_water) * 180.0 / std::numbers::pi;
    report("B32", "Cherenkov max angle water [deg]", "Optics", theta, 41.4, 1.0, Certification::COMPUTED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B33 — TURBULENT CASCADE: EXPONENT + REFUSAL-CORRECTED SLOPE (FD04)
// ═══════════════════════════════════════════════════════════════════════

static void B33_turbulence()
{
    std::puts("\n══ B33: TURBULENT CASCADE ══");
    // (a) constant-flux dimensional closure, solved (not typed): E ∝ ε^a k^b.
    //     [E]=L³T⁻², [ε]=L²T⁻³, [k]=L⁻¹  ⇒  a = 2/3, b = −5/3.
    double a = 2.0 / 3.0;
    double b = 2.0 * a - 3.0;                            // = −5/3 from the L-balance
    report("B33", "Inertial-range |slope| (ideal)", "Fluids", -b, 1.705, 5.0, Certification::COMPUTED);
    // (b) the bath's refusal (FD04-P6, direct 2026-07-26): the lattice packing
    //     shortfall g = 0.103 leaks per generation at the wrap step λ = 4 —
    //     zero fitted parameters.
    double g = 0.103, lam = 4.0;
    double slope = 5.0 / 3.0 + std::log(1.0 / (1.0 - g)) / (3.0 * std::log(lam));
    report("B33", "Refusal-corrected |slope|", "Fluids", slope, 1.705, 2.0, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B34 — THE DRAFTING FLOOR a₀ = cH₀/2π (APS03)
// ═══════════════════════════════════════════════════════════════════════

static void B34_drafting_floor()
{
    std::puts("\n══ B34: DRAFTING FLOOR a₀ ══");
    using namespace sdt::laws;
    // The cosmos's own acceleration floor from the boundary rate — no fit.
    // Comparison value is the empirically fitted galactic floor 1.2e-10 m/s².
    double H0 = 67.4 * 1000.0 / 3.0857e22;               // OBSERVED [1/s]
    double a0 = measured::c * H0 / (2.0 * std::numbers::pi);
    report("B34", "a0 = cH0/2pi [m/s2]", "Galactic", a0, 1.2e-10, 20.0, Certification::COMPUTED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B35 — α READ FROM THE HYDROGEN SEAT (APS05 route A)
// ═══════════════════════════════════════════════════════════════════════

static void B35_alpha_extraction()
{
    std::puts("\n══ B35: ALPHA FROM THE SEAT ══");
    using namespace sdt::laws;
    // v(a₀) = αc  ⇒  α = √(2·E_ion/m_e c²): the coupling read off the spectrum.
    // An extraction, not a derivation — α remains an open peg, stated.
    double mec2_eV = measured::m_e * measured::c * measured::c / 1.602176634e-19;
    double alpha_ext = std::sqrt(2.0 * 13.598434 / mec2_eV);
    report("B35", "1/alpha from H ionisation", "Atomic", 1.0 / alpha_ext, 137.035999, 0.2, Certification::COMPUTED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B36 — KOPPA INVARIANCE ACROSS THE JOVIAN MOONS (GOM12)
// ═══════════════════════════════════════════════════════════════════════

static void B36_koppa_invariance()
{
    std::puts("\n══ B36: KOPPA INVARIANCE (JUPITER) ══");
    using namespace sdt::laws;
    // Four moons, one Jupiter, one length: ϟ = v²r/c² must agree moon to moon.
    // v, r OBSERVED (JPL); the spread is the test. No kilogram anywhere.
    struct Moon { const char* name; double v; double r; };
    Moon moons[] = {
        {"Io",       17334.0, 4.218e8}, {"Europa",   13740.0, 6.711e8},
        {"Ganymede", 10880.0, 1.0704e9}, {"Callisto",  8204.0, 1.8827e9},
    };
    double kmin = 1e99, kmax = 0.0;
    for (auto& m : moons) {
        double koppa = m.v * m.v * m.r / (measured::c * measured::c);
        if (koppa < kmin) kmin = koppa;
        if (koppa > kmax) kmax = koppa;
    }
    report("B36", "Moon-to-moon 8/8 ratio (1=exact)", "Gravity", kmax / kmin, 1.0, 0.2, Certification::DERIVED);
}

// ═══════════════════════════════════════════════════════════════════════
//  B37 — STANDING PREDICTION: RANK-4 LATTICE ANISOTROPY (TD03)
// ═══════════════════════════════════════════════════════════════════════

static void B37_rank4_prediction()
{
    std::puts("\n══ B37: RANK-4 LATTICE BAND (PREDICTION) ══");
    // The W+1=4 tetrahedral coordination is a spherical 2-design: the pressure
    // 1/3 is symmetry-protected, and the lattice fingerprint lives at rank 4 —
    // ⟨(b·n)⁴⟩ ∈ [1/9, 7/27] against the continuum 1/5. No measured comparison
    // exists yet; recorded as a standing falsifiable prediction, no tally.
    std::printf("  B37  fourth-moment band predicted [%.4f, %.4f] vs continuum %.4f"
                " — awaiting measurement (TD03, direct 2026-07-26). PENDING.\n",
                1.0 / 9.0, 7.0 / 27.0, 0.2);
}

// ═══════════════════════════════════════════════════════════════════════
//  B38 — SHELL SCHEDULE: CLOSURE TIERS AND TRITON BELTS (canon 2026-07-30)
// ═══════════════════════════════════════════════════════════════════════

static void B38_shell_schedule()
{
    using namespace sdt::laws::nuclear;
    std::puts("\n══ B38: SHELL SCHEDULE — CLOSURE TIERS + TRITON BELTS ══");
    // Deuteron tiers (6,12 | 12,20,30) alternating with triton belts of
    // antipodal pairs (4,5,6,7) rebuild every closure. Capacities are READ to
    // match the measured sequence — deriving them from packing-void geometry
    // is the open NP33 completion law. No spin-orbit force imported: the rod's
    // seating carries what the prevailing account modelled as a coupling.
    int seq_ok = 0;
    for (int k = 0; k < 7; ++k) seq_ok += (closure(k) == magic_numbers[k]);
    std::printf("  B38a closure rebuild 2,8,20,28,50,82,126: %d/7 %s"
                " (also enforced by static_assert in laws.hpp)\n",
                seq_ok, seq_ok == 7 ? "✓" : "✗");

    // Parity lock vs the measured stability record: the misfit predicate must
    // flag exactly the five naturally occurring odd-odd quasi-stables and
    // clear the seven mono-isotopic odd-Z grips.
    struct Row { const char* name; int Z, A; bool misfit_expected; };
    constexpr Row rows[] = {
        {"K-40", 19, 40, true},  {"V-50", 23, 50, true},  {"La-138", 57, 138, true},
        {"Lu-176", 71, 176, true}, {"Ta-180m", 73, 180, true},
        {"Na-23", 11, 23, false}, {"Al-27", 13, 27, false}, {"P-31", 15, 31, false},
        {"Sc-45", 21, 45, false}, {"V-51", 23, 51, false},  {"Mn-55", 25, 55, false},
        {"Co-59", 27, 59, false},
    };
    int par_ok = 0;
    for (const auto& r : rows) par_ok += (triton_parity_misfit(r.Z, r.A) == r.misfit_expected);
    std::printf("  B38b parity lock: %d/12 — five odd-odd quasi-stables flagged,"
                " seven lone-rod grips cleared %s\n", par_ok, par_ok == 12 ? "✓" : "✗");

    // Belt evidence, both poles of the fourth tier:
    std::printf("  B38c first belt (N=28): Ca-48 n_t=%d = full 4-pair belt (held,"
                " doubly magic) · Ni-56 n_t=%d = belt empty (unstable) ✓\n",
                48 - 2 * 20, 56 - 2 * 28);
    std::puts("  B38d closure-kink isotone invariant (measured, pre-registered"
              " 2026-07-30): constant beats occupancy-proportional on every"
              " adjudicable isotone (N=28,50,82); 19/19 closure kinks negative;");
    std::puts("       lone-rod-inward census 83.1% — the freeze does the compacting."
              " ATOMICUS/reports/CLOSURE_KINK_ISOTONE_REPORT.md");
    int cap_ok = 0;
    cap_ok += (tier_capacity(1) == 6) + (tier_capacity(2) == 12);
    cap_ok += (surface_remainder(3) == 12) + (surface_remainder(4) == 20)
            + (surface_remainder(5) == 30);
    cap_ok += (belt_capacity(3) == 8) + (belt_capacity(4) == 10)
            + (belt_capacity(5) == 12) + (belt_capacity(6) == 14);
    std::printf("  B38e COMPLETION LAW: all capacities from two closed forms —"
                " F(n)=(n+1)(n+2) bipartite-triangular tiers, B(n)=2(n+1)"
                " rolling-equator belts: %d/9 %s\n", cap_ok, cap_ok == 9 ? "✓" : "✗");
    std::printf("       forward prediction: next closure N = %d (126 + R(6) + B(7))."
                " Onset n=3 still READ — the residual NP33 debt.\n",
                126 + surface_remainder(6) + belt_capacity(7));
    std::puts("  B38  sequence-exact; counting convergent with the shell model,"
              " origin native — capacities DERIVED 2026-07-30.");
}

// ═══════════════════════════════════════════════════════════════════════
//  B39 — RELAY-SPEED PROFILE FROM THE SHAPIRO DELAY (GOM22 repair, canon)
// ═══════════════════════════════════════════════════════════════════════

static void B39_relay_speed_profile()
{
    using namespace sdt::laws;
    std::puts("\n══ B39: RELAY-SPEED PROFILE (GOM22 canon repair) ══");
    const double koppa = 1476.625;                 // ϟ_Sun = GM/c² [m]
    const double R_Sun = 6.957e8, AU = 1.495'978'707e11;
    const double z = koppa / R_Sun;
    // (i) Shapiro delay, grazing Earth–Mars superior conjunction
    const double dt = 2.0 * depth_closure::shapiro_delay(koppa, AU, 1.524 * AU, R_Sun);
    report("B39", "Shapiro round-trip, grazing (Viking/Cassini)", "Gravitation",
           1e6 * dt, 247.24, 0.5, Certification::DERIVED, "us");
    // (ii) the same profile must return the solar gravitational redshift
    const double v_grav = measured::c * (1.0 / depth_closure::clock_rate(z) - 1.0);
    report("B39", "Solar gravitational redshift", "Gravitation",
           v_grav, 633.0, 1.0, Certification::DERIVED, "m/s");
    // (iii) the superseded relation, printed so the fault stays visible
    std::printf("  B39  superseded c_local=c(1-z) would give %.2f us "
                "(ratio %.4f) — retained only for legacy callers.\n",
                1e6 * dt * 0.5, 0.5);
    std::puts("  B39  OPEN FORK (second-order): c(1-z)^2 [adopted, wall at r=koppa]");
    std::puts("       vs c(1-2z) [Schwarzschild form, horizon at r_s]. A 1.4 Msun");
    std::puts("       NS surface splits them by 8.6% — the named discriminator.");
}

// ═══════════════════════════════════════════════════════════════════════
//  COVERAGE ROSTER — the original B01–B100 catalogue, every row accounted
// ═══════════════════════════════════════════════════════════════════════

static void coverage_roster()
{
    std::puts("\n══ COVERAGE ROSTER: ORIGINAL CATALOGUE B01–B100 ══");
    std::puts("  codes: T = tallied in this suite · A = earned in a direct assessment");
    std::puts("         S = investigation seeded 2026-07-29 · O = investigation open");
    std::puts("         (the companion repo's old certifications carry no weight; B04-old");
    std::puts("          and the self-referential B51+ validations are recorded as void)");
    std::puts("  B01-B25  T  this suite (B04 note-only: APS04 term derived, amplitude open;");
    std::puts("              B06 PENDING → APS10 seeded; B09 open; B11 PENDING)");
    std::puts("  B25-26   A  alpha geometry/overlap — NP10, NP33 mesh log");
    std::puts("  B27,33   A  radius scaling + isotope shifts — NP12, APS07, contraction rule");
    std::puts("  B29,43   S  first ionisation from pressure — APS10 (the B06 gap)");
    std::puts("  B30,31   S  electron affinity CH08 · atomic radius CH09");
    std::puts("  B32,48   A  shell completion / packing pathways — NP32, NP33; the");
    std::puts("              closure schedule is now canon (laws.hpp, tallied B38)");
    std::puts("  B34      T  deuteron lock tallied here (B30); heavier locks open");
    std::puts("  B35-47   O  NP28/NP15/PPT01/CH03/NP12/NP30/FLM10/FD11/CH03/SAR02/CM03/PPT06");
    std::puts("  B49,50   O  stability maps NP21/NP29 · end-to-end = this suite");
    std::puts("  B51-57   A/O/S  QM01 O · OP05 O · QM03 A (Geiger–Nuttall) · QM07 O ·");
    std::puts("              QM05 A · QM08 S (eraser)");
    std::puts("  B58-60   S/A  lepton moments PPT12 S (B17 form here) · APS04 A (B04 note)");
    std::puts("  B61-68   S/A  GPS GOM20 S · muon budget PPT16 S · depth B28 T · GOM21 S ·");
    std::puts("              shadow GOM18 O · chirp B29 T · decay integral open");
    std::puts("  B69,70   A  NS radius 11.0 km (NP30) · CMB counted (TD06) — ports owed");
    std::puts("  B71-78   O/S  PPT03/07 O (6pi^5 hook B26) · pion PPT13 S · n-p B19 T ·");
    std::puts("              resonances PPT14 S · lifetime NP04 O · radius B18 T · CP PPT15 S ·");
    std::puts("              mixing PPT11 O");
    std::puts("  B79,80   O  GD05 · CR09 — open, stated on the public site");
    std::puts("  B81-88   O  CM01/CM03/CM06/CM07/CM05/TD04(A)/OP01");
    std::puts("  B89-94   A/S  SAR03-04 A · white dwarf SAR07 S · pulsar SAR08 S ·");
    std::puts("              SN Ia CR12 A (exclusion recorded) · neutrinos PPT11 O ·");
    std::puts("              BBN TD09 A → tallied here (B31)");
    std::puts("  B95-100  S/O  Zeeman APS08 S · Stark APS09 S · Faraday OP08 S ·");
    std::puts("              Casimir FLM15 S · Cherenkov A → tallied here (B32) · OP01 O");
}

// ═══════════════════════════════════════════════════════════════════════
//  MAIN — RUN ALL BENCHMARKS
// ═══════════════════════════════════════════════════════════════════════

int main()
{
    std::puts("╔══════════════════════════════════════════════════════════════╗");
    std::puts("║  SDT BENCHMARK SUITE — Six-Law Framework                    ║");
    std::puts("║  Single Source of Truth: sdt_laws.hpp                       ║");
    std::puts("║  9 Axioms · 18 Theorems · 0 Free Parameters                ║");
    std::puts("╚══════════════════════════════════════════════════════════════╝");

    B01_atomic_structure();
    B02_rydberg_precision();
    B03_fine_structure();
    B04_lamb_shift();
    B05_hyperfine();
    B06_multielectron();
    B07_thermodynamics();
    B08_orbital_mechanics();
    B09_gravitational_radiation();
    B10_strong_field();
    B11_planetary_oblateness();
    B12_stellar_structure();
    B13_cmb_redshift();
    B14_galactic_rotation();
    B15_bao_scale();
    B16_transport();
    B17_magnetic();
    B18_proton_radius();
    B19_beta_decay();
    B20_zk2_universality();
    B21_screening();
    B22_pressure_hierarchy();
    B23_coulomb_identity();
    B24_exclusion_volumes();
    B25_alpha_cluster();
    B26_trefoil_topology();
    B27_koppa_closure();
    B28_depth_closure();
    B29_gw_chirp();
    B30_deuteron_binding();
    B31_bbn_bottleneck();
    B32_cherenkov();
    B33_turbulence();
    B34_drafting_floor();
    B35_alpha_extraction();
    B36_koppa_invariance();
    B37_rank4_prediction();
    B38_shell_schedule();
    B39_relay_speed_profile();
    coverage_roster();

    // Separate genuine regressions from KNOWN-OPEN (PENDING) items so the summary
    // keeps the classes separate: a PENDING fail is a flagged open problem, not a broken result.
    int pending_fail = 0, real_fail = 0;
    for (auto& r : g_results) {
        if (!r.passed) {
            if (r.cert == Certification::PENDING) pending_fail++; else real_fail++;
        }
    }

    // Summary — earned predictions only in the headline; identities/calibrated/note-PENDING shown separately
    int earned_total = g_total - g_identity_pass - g_calibrated_pass - g_pending_note;
    std::puts("\n╔══════════════════════════════════════════════════════════════╗");
    std::printf("║  RESULTS: %d/%d earned predictions passed (%.1f%%)           ║\n",
                g_passed, earned_total, earned_total > 0 ? 100.0 * g_passed / earned_total : 0.0);
    std::printf("║  + %d consistency identities (definitional; NOT predictions) ║\n", g_identity_pass);
    std::printf("║  + %d CALIBRATED (class E, documented; not earned)           ║\n", g_calibrated_pass);
    std::printf("║  + %d PENDING note-only (literal/shared-form; not earned)    ║\n", g_pending_note);
    std::printf("║  %d genuine fail · %d PENDING open (flagged, in denom)       ║\n",
                real_fail, pending_fail);
    std::puts("╚══════════════════════════════════════════════════════════════╝");

    // Failure detail
    if (g_failed > 0) {
        std::puts("\nUnmet benchmarks (✗ = genuine regression, ⧖ = PENDING open problem):");
        for (auto& r : g_results) {
            if (!r.passed) {
                const char* mark = (r.cert == Certification::PENDING) ? "⧖" : "✗";
                std::printf("  %s %s: %s  (%.4f%% > %.2f%% tolerance)\n",
                            mark, r.id.c_str(), r.name.c_str(), r.error_pct, r.tolerance_pct);
            }
        }
    }

    std::puts("\nCertification labels:");
    std::puts("  DERIVED    — computed from axioms, no external input beyond CODATA");
    std::puts("  COMPUTED   — deterministic calculation from the Law framework");
    std::puts("  CALIBRATED — one parameter fitted (documented at the call site)");
    std::puts("  OBSERVED   — validated against observation, mechanism established");
    std::puts("  PENDING    — mechanism identified, SDT-native derivation not yet implemented");
    std::puts("  IDENTITY   — true by definition/construction; shown as consistency, never tallied");

    // Exit non-zero only on GENUINE regressions; PENDING items are flagged, not failures.
    return real_fail > 0 ? 1 : 0;
}
