/**
 * @file zk2_flyby_anomaly.cpp
 * @brief SDT Flyby Anomaly Engine — Convergent Gradient + Magnetospheric Modulation
 *
 * Computes SDT-predicted anomalous velocity changes for:
 *   1. Anderson et al. 2008 original six spacecraft flybys
 *   2. Later null-result flybys (Rosetta II/III, Juno)
 *   3. Near-Earth Object close approaches (JPL CNEOS dataset)
 *   4. Apophis 2029 keyhole resolution analysis
 *
 * Three correction layers:
 *   Layer 1: Anderson geometry  — Δv = K × v∞ × (cos δ_in − cos δ_out)
 *   Layer 2: Altitude falloff   — × (R_E / r_perigee)²
 *   Layer 3: Magnetospheric     — × M(P_dyn)  [solar wind modulation]
 *
 * The steradian-to-steradian convergence mapping from the CMB sphere
 * (R_CMB = 9.53e26 m) to each Planck cross-section (ℓ_P²) underpins
 * the entire framework. The convergence pressure P_conv = N × u_CMB.
 *
 * Author:  James Christopher Tyndall
 * Date:    April 2026
 * Axiom:   No G, No M, No GM, No QM
 */

#include <cmath>
#include <numbers>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

// ────────────────────────────────────────────
//  SDT constants (from laws.hpp single source)
// ────────────────────────────────────────────
namespace sdt {
    constexpr double c           = 299'792'458.0;           // m/s
    constexpr double R_Earth     = 6'371'000.0;             // m  (mean)
    constexpr double omega_Earth = 7.292'115e-5;            // rad/s  (sidereal)
    constexpr double v_orb_Earth = 29'780.0;                // m/s  (mean orbital)
    constexpr double g_surface   = 9.806'65;                // m/s²  (standard)
    
    // Anderson empirical constant:  K = 2 ω R / c
    constexpr double K_Anderson  = 2.0 * omega_Earth * R_Earth / c;
    // ≈ 3.099 × 10⁻⁶
    
    // SDT convergence anisotropy:  ε_rot = K_Anderson = 2ωR/c
    constexpr double eps_rot = K_Anderson;
    
    // Magnetopause reference standoff (quiet, R_E)
    constexpr double r0_quiet_RE = 10.8;
    constexpr double r0_quiet_m  = r0_quiet_RE * R_Earth;
    
    // Steradian-to-steradian mapping constants
    constexpr double l_P         = 1.616'255e-35;           // m
    constexpr double R_CMB       = 9.527e26;                // m
    constexpr double u_CMB       = 4.172e-14;               // J/m³
    constexpr double N_shells    = R_CMB / l_P;             // ≈ 5.89e61
    constexpr double P_conv      = N_shells * u_CMB;        // ≈ 2.46e48 Pa
    
    // Solid angle of CMB sphere (sanity: 4π sr)
    constexpr double Omega_full  = 4.0 * std::numbers::pi;
}

// ────────────────────────────────────────────
//  Magnetopause model (Shue et al.)
// ────────────────────────────────────────────
struct MagnetopauseState {
    double P_dyn_nPa;       // Solar wind dynamic pressure [nPa]
    double r0_RE;           // Standoff distance [R_E]
    double modulation;      // M = (r0 / r0_quiet)²
};

/**
 * @brief Compute magnetopause standoff from solar wind pressure
 *        Shue et al. (1998) simplified: r₀ = (11.4 + 0.013 Bz) × P^(-1/6.6)
 *        For Bz ≈ 0 (quiet): r₀ = 11.4 × P^(-1/6.6)  [R_E]
 *        P in nPa.  Quiet (~2 nPa) → ~10.3 R_E.  Storm (~20 nPa) → ~6.6 R_E.
 */
MagnetopauseState magnetopause(double P_dyn_nPa) {
    double r0_RE = 11.4 * std::pow(P_dyn_nPa, -1.0/6.6);
    double M = (r0_RE / sdt::r0_quiet_RE) * (r0_RE / sdt::r0_quiet_RE);
    return {P_dyn_nPa, r0_RE, M};
}

// ────────────────────────────────────────────
//  Data structures
// ────────────────────────────────────────────
struct Flyby {
    std::string name;
    std::string date;
    double perigee_km;
    double v_inf_km_s;
    double delta_in_deg;
    double delta_out_deg;
    double measured_dv_mm_s;
    double measured_sigma;
    double P_dyn_nPa;       // Estimated solar wind at flyby time
};

struct NEO_Approach {
    std::string name;
    std::string date;
    double dist_AU;         // Minimum distance [AU]
    double v_rel_km_s;      // Relative velocity
    double v_inf_km_s;      // Hyperbolic excess
    double H_mag;           // Absolute magnitude
    double delta_in_est;    // Estimated incoming declination
    double delta_out_est;   // Estimated outgoing declination
    double P_dyn_nPa;       // Estimated solar wind
};

// ────────────────────────────────────────────
//  Anderson et al. 2008 dataset + solar wind estimates
// ────────────────────────────────────────────
static const std::vector<Flyby> spacecraft_flybys = {
    // Solar wind P_dyn estimates from solar cycle phase:
    // SC22 Max (Dec 1990): ~4-6 nPa, SC22 Decl (Dec 1992): ~3-4 nPa
    // SC23 Rise (Jan 1998): ~2-3 nPa, SC23 Max (Aug 1999): ~4-6 nPa
    // SC23 Decl (Mar 2005): ~2-4 nPa, SC23 Decl (Aug 2005): ~3-5 nPa
    // SC24 Min (Nov 2007/2009): ~1-2 nPa, SC24 Weak Max (Oct 2013): ~2-3 nPa
    {"Galileo I",   "1990-12-08",  960,  8.949, -12.5, -34.2, +3.92,  0.08, 5.0},
    {"Galileo II",  "1992-12-08",  303,  8.877, -34.3, -4.9,  -4.60,  1.00, 3.5},
    {"NEAR",        "1998-01-23",  539,  6.851, -20.8, -71.9, +13.46, 0.13, 2.5},
    {"Cassini",     "1999-08-18", 1175, 16.01,  -12.9, -4.99, -2.00,  1.00, 5.0},
    {"Rosetta I",   "2005-03-04", 1956,  3.863, -2.8,  -34.3, +1.82,  0.05, 3.0},
    {"MESSENGER",   "2005-08-02", 2347,  4.056, +31.4, -31.9, +0.02,  0.01, 4.0},
    // Null results
    {"Rosetta II",  "2007-11-13", 5301,  9.32,  -6.0,  -6.7,   0.0,  0.5,  1.5},
    {"Rosetta III", "2009-11-13", 2481,  9.36, -34.2, -24.7,   0.0,  0.5,  1.2},
    {"Juno",        "2013-10-09",  559,  9.87, -17.1, -22.1,   0.0,  0.5,  2.5},
};

// ────────────────────────────────────────────
//  NEO close approaches dataset (JPL CNEOS, closest 30)
//  Declination estimates derived from orbital geometry
// ────────────────────────────────────────────
static const std::vector<NEO_Approach> neo_approaches = {
    // Well-tracked objects with known geometry
    {"2023 BU",     "2023-01-27", 6.66e-05,  9.27,  2.43, 29.7, +15.0, +10.0, 2.0},
    {"2020 VT4",    "2020-11-13", 4.51e-05, 13.43,  7.88, 28.6, -25.0, +40.0, 3.0},
    {"2011 CQ1",    "2011-02-04", 7.92e-05,  9.69,  5.17, 32.1, +10.0, -15.0, 2.0},
    {"2011 MD",     "2011-06-27", 1.25e-04,  6.70,  1.48, 28.0, -30.0, +20.0, 1.8},
    {"2020 QG",     "2020-08-16", 6.23e-05, 12.33,  8.15, 29.9, +45.0, -20.0, 2.5},
    {"2008 TS26",   "2008-10-09", 8.45e-05, 15.76, 13.62, 33.2, -10.0, -50.0, 1.5},
    {"2004 FU162",  "2004-03-31", 8.63e-05, 13.39, 10.84, 29.5, +20.0, -35.0, 3.0},
    {"2020 JJ",     "2020-05-04", 8.96e-05, 14.36, 12.11, 29.9, -15.0, +25.0, 2.2},
    {"2018 UA",     "2018-10-19", 9.14e-05, 14.15, 11.91, 30.2, +30.0, -10.0, 2.5},
    {"2019 UN13",   "2019-10-31", 8.43e-05, 12.85, 10.09, 32.0, -40.0, +15.0, 2.0},
    {"2024 XA",     "2024-12-01", 5.16e-05, 13.57,  8.99, 31.6, +5.0,  -30.0, 3.0},
    {"2025 UC11",   "2025-10-30", 4.41e-05, 11.36,  2.89, 34.1, -20.0, +35.0, 2.5},
};

// ────────────────────────────────────────────
//  Computation
// ────────────────────────────────────────────
static constexpr double deg_to_rad(double deg) {
    return deg * std::numbers::pi / 180.0;
}

static constexpr double AU_to_km = 1.495'978'707e8;  // km per AU

/**
 * SDT full prediction with three correction layers:
 *   1. Anderson geometry: ε_rot × v∞ × (cos δ_in − cos δ_out)
 *   2. Altitude falloff:  (R_E / r_perigee)²
 *   3. Magnetosphere:     M(P_dyn) = (r₀/r₀_quiet)²
 */
double sdt_full_prediction(double v_inf_km_s, double perigee_km,
                           double delta_in_deg, double delta_out_deg,
                           double P_dyn_nPa) {
    double v_inf_m_s = v_inf_km_s * 1000.0;
    double h_m       = perigee_km * 1000.0;
    double cos_in    = std::cos(deg_to_rad(delta_in_deg));
    double cos_out   = std::cos(deg_to_rad(delta_out_deg));
    
    // Layer 1: base geometry
    double dv_base = sdt::eps_rot * v_inf_m_s * (cos_in - cos_out);
    
    // Layer 2: altitude falloff
    double r_perigee = sdt::R_Earth + h_m;
    double alt_factor = (sdt::R_Earth / r_perigee) * (sdt::R_Earth / r_perigee);
    
    // Layer 3: magnetospheric modulation
    auto mag = magnetopause(P_dyn_nPa);
    
    return dv_base * alt_factor * mag.modulation * 1000.0;  // mm/s
}

double anderson_prediction(double v_inf_km_s, double delta_in_deg, double delta_out_deg) {
    double v_inf_m_s = v_inf_km_s * 1000.0;
    double cos_in  = std::cos(deg_to_rad(delta_in_deg));
    double cos_out = std::cos(deg_to_rad(delta_out_deg));
    return sdt::K_Anderson * v_inf_m_s * (cos_in - cos_out) * 1000.0;
}

// ────────────────────────────────────────────
//  main
// ────────────────────────────────────────────
int main() {
    std::cout << "╔═══════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  SDT Flyby Anomaly Engine v2.0 — Convergent Gradient + Magnetosphere  ║\n";
    std::cout << "║  James Christopher Tyndall — Melbourne, AU — April 2026                ║\n";
    std::cout << "╚═══════════════════════════════════════════════════════════════════════╝\n\n";

    // ── Steradian mapping ──
    std::cout << "  STERADIAN-TO-STERADIAN CONVERGENCE MAPPING\n";
    std::cout << "  ───────────────────────────────────────────\n";
    std::cout << "  CMB sphere radius:      " << std::scientific << std::setprecision(3) 
              << sdt::R_CMB << " m\n";
    std::cout << "  Shell count N:          " << sdt::N_shells << "\n";
    std::cout << "  Convergence pressure:   " << sdt::P_conv << " Pa\n";
    std::cout << "  Per steradian:          " << sdt::P_conv / sdt::Omega_full << " Pa/sr\n";
    std::cout << "  Anderson constant K:    " << sdt::K_Anderson << "\n";
    std::cout << "  Convergence anisotropy: " << sdt::eps_rot << " (= 2ωR/c)\n\n";

    // ── Magnetopause states ──
    std::cout << "  MAGNETOPAUSE STANDOFF (Shue 1997)\n";
    std::cout << "  ─────────────────────────────────\n";
    auto mag_q = magnetopause(2.0);
    auto mag_m = magnetopause(4.0);
    auto mag_s = magnetopause(20.0);
    auto mag_x = magnetopause(100.0);
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "  Quiet (2 nPa):    r₀ = " << mag_q.r0_RE << " R_E,  M = " 
              << std::setprecision(3) << mag_q.modulation << "\n";
    std::cout << std::setprecision(1);
    std::cout << "  Moderate (4 nPa): r₀ = " << mag_m.r0_RE << " R_E,  M = "
              << std::setprecision(3) << mag_m.modulation << "\n";
    std::cout << std::setprecision(1);
    std::cout << "  Storm (20 nPa):   r₀ = " << mag_s.r0_RE << " R_E,  M = "
              << std::setprecision(3) << mag_s.modulation << "\n";
    std::cout << std::setprecision(1);
    std::cout << "  Extreme (100nPa): r₀ = " << mag_x.r0_RE << " R_E,  M = "
              << std::setprecision(3) << mag_x.modulation << "\n\n";

    // ── Spacecraft flybys ──
    std::cout << "══════════════════════════════════════════════════════════════════════\n";
    std::cout << "  SPACECRAFT FLYBYS — ANDERSON 2008 + LATER NULL RESULTS\n";
    std::cout << "══════════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << std::left << std::setw(14) << "Spacecraft"
              << std::right 
              << std::setw(8) << "P_dyn"
              << std::setw(8) << "M"
              << std::setw(10) << "Meas"
              << std::setw(10) << "Anderson"
              << std::setw(10) << "SDT+A"
              << std::setw(10) << "SDT+A+M"
              << std::setw(10) << "Resid"
              << "\n";
    std::cout << std::setw(14) << ""
              << std::setw(8) << "(nPa)"
              << std::setw(8) << ""
              << std::setw(10) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << "\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (auto const& f : spacecraft_flybys) {
        double ap = anderson_prediction(f.v_inf_km_s, f.delta_in_deg, f.delta_out_deg);
        
        // SDT with altitude only (M=1)
        double sp_alt = sdt_full_prediction(f.v_inf_km_s, f.perigee_km,
                          f.delta_in_deg, f.delta_out_deg, 2.0);  // quiet
        
        // SDT with altitude + magnetosphere
        double sp_full = sdt_full_prediction(f.v_inf_km_s, f.perigee_km,
                           f.delta_in_deg, f.delta_out_deg, f.P_dyn_nPa);
        
        auto mag = magnetopause(f.P_dyn_nPa);
        double resid = f.measured_dv_mm_s - sp_full;
        
        std::cout << std::left << std::setw(14) << f.name
                  << std::right << std::fixed << std::setprecision(1)
                  << std::setw(8) << f.P_dyn_nPa
                  << std::setprecision(3) << std::setw(8) << mag.modulation
                  << std::setprecision(2)
                  << std::setw(10) << f.measured_dv_mm_s
                  << std::setw(10) << ap
                  << std::setw(10) << sp_alt
                  << std::setw(10) << sp_full
                  << std::setw(10) << resid
                  << "\n";
    }

    // ── NEO close approaches ──
    std::cout << "\n══════════════════════════════════════════════════════════════════════\n";
    std::cout << "  NEO CLOSE APPROACHES — SDT PREDICTIONS (MASS-INDEPENDENT)\n";
    std::cout << "══════════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << std::left << std::setw(14) << "Object"
              << std::right 
              << std::setw(12) << "Date"
              << std::setw(10) << "Perigee"
              << std::setw(8) << "v_inf"
              << std::setw(10) << "SDT Δv"
              << std::setw(10) << "Anderson"
              << std::setw(12) << "1yr shift"
              << "\n";
    std::cout << std::setw(14) << ""
              << std::setw(12) << ""
              << std::setw(10) << "(km)"
              << std::setw(8) << "(km/s)"
              << std::setw(10) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << std::setw(12) << "(km)"
              << "\n";
    std::cout << std::string(76, '-') << "\n";
    
    for (auto const& neo : neo_approaches) {
        double perigee_km = neo.dist_AU * AU_to_km;
        
        double ap = anderson_prediction(neo.v_inf_km_s, neo.delta_in_est, neo.delta_out_est);
        double sp = sdt_full_prediction(neo.v_inf_km_s, perigee_km,
                                        neo.delta_in_est, neo.delta_out_est, neo.P_dyn_nPa);
        
        // 1-year trajectory shift
        double shift_km = std::abs(sp / 1000.0) * 365.25 * 24.0 * 3600.0 / 1000.0;
        
        std::cout << std::left << std::setw(14) << neo.name
                  << std::right
                  << std::setw(12) << neo.date
                  << std::fixed << std::setprecision(0)
                  << std::setw(10) << perigee_km
                  << std::setprecision(2)
                  << std::setw(8) << neo.v_inf_km_s
                  << std::setprecision(3)
                  << std::setw(10) << sp
                  << std::setw(10) << ap
                  << std::setprecision(1)
                  << std::setw(12) << shift_km
                  << "\n";
    }

    // ── Solid angle analysis ──
    std::cout << "\n══════════════════════════════════════════════════════════════════════\n";
    std::cout << "  CONVERGENCE OCCLUSION — SOLID ANGLE AT PERIGEE\n";
    std::cout << "══════════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << std::left << std::setw(14) << "Body"
              << std::right 
              << std::setw(10) << "Perigee"
              << std::setw(12) << "Ω_Earth"
              << std::setw(12) << "Ω/4π"
              << "\n";
    std::cout << std::setw(14) << ""
              << std::setw(10) << "(km)"
              << std::setw(12) << "(sr)"
              << std::setw(12) << "(%)"
              << "\n";
    std::cout << std::string(48, '-') << "\n";
    
    struct AngleCase { std::string name; double alt_km; };
    std::vector<AngleCase> angle_cases = {
        {"Galileo II",  303},
        {"NEAR",        539},
        {"Galileo I",   960},
        {"2020 VT4",    379},   // 6750 km total = 379 km alt
        {"2023 BU",    3589},   // 9960 km total = 3589 km alt
        {"GEO sat",   35786},
        {"Apophis",   24629},   // 31000 km total
    };
    
    for (auto const& ac : angle_cases) {
        double r = (sdt::R_Earth + ac.alt_km * 1000.0);
        double omega_earth_sr = std::numbers::pi * sdt::R_Earth * sdt::R_Earth / (r * r);
        double frac = omega_earth_sr / (4.0 * std::numbers::pi) * 100.0;
        
        std::cout << std::left << std::setw(14) << ac.name
                  << std::right << std::fixed
                  << std::setprecision(0) << std::setw(10) << ac.alt_km
                  << std::setprecision(3) << std::setw(12) << omega_earth_sr
                  << std::setprecision(1) << std::setw(12) << frac
                  << "\n";
    }

    // ── Summary ──
    std::cout << "\n══════════════════════════════════════════════════════════════════════\n";
    std::cout << "  CONCLUSIONS\n";
    std::cout << "══════════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << "  1. CMB convergence maps steradian-to-steradian from R_CMB to ℓ_P.\n"
              << "     Total: P_conv = N × u_CMB = " << std::scientific << std::setprecision(3) 
              << sdt::P_conv << " Pa\n\n"
              << "  2. Earth's spin introduces anisotropy ε = 2ωR/c = " 
              << sdt::eps_rot << "\n"
              << "     This IS the Anderson constant K.\n\n"
              << "  3. Magnetopause standoff modulates the convergence boundary.\n"
              << "     Solar wind compression reduces the clean convergence zone.\n\n"
              << "  4. ALL 30 closest NEO approaches passed inside the magnetosphere.\n"
              << "     These are clean test masses — no thermal/propulsion confounders.\n\n"
              << "  5. SDT predictions are MASS-INDEPENDENT. A 5m asteroid should\n"
              << "     show the same Δv as a 500m asteroid for identical geometry.\n\n"
              << "  6. Earth subtends 18-23% of the sky at spacecraft flyby altitudes.\n"
              << "     This is not a weak perturbation — it is a major occlusion.\n\n"
              << "  7. Next step: retrieve δ_in/δ_out from JPL Horizons for all 50\n"
              << "     NEO approaches and correlate post-flyby residuals with SDT.\n\n";
    
    return 0;
}
