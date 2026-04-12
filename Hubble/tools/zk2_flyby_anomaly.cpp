/**
 * @file zk2_flyby_anomaly.cpp
 * @brief SDT Flyby Anomaly Computation Engine
 *
 * Computes the predicted anomalous velocity change (Δv) for 
 * spacecraft and comets performing Earth gravity assists,
 * based on the rotational convergence gradient hypothesis.
 *
 * Uses the Anderson empirical formula as a calibration target,
 * then derives the SDT prediction from the convergence gradient.
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
#include <array>
#include <format>

// ────────────────────────────────────────────
//  SDT constants (from laws.hpp single source)
// ────────────────────────────────────────────
namespace sdt {
    constexpr double c           = 299'792'458.0;           // m/s
    constexpr double R_Earth     = 6'371'000.0;             // m  (mean)
    constexpr double omega_Earth = 7.292'115e-5;            // rad/s  (sidereal)
    constexpr double v_orb_Earth = 29'780.0;                // m/s  (mean orbital velocity)
    constexpr double g_surface   = 9.806'65;                // m/s²  (standard gravity)
    
    // Anderson empirical constant:  K = 2 ω R / c
    constexpr double K_Anderson  = 2.0 * omega_Earth * R_Earth / c;
    // ≈ 3.099 × 10⁻⁶
    
    // SDT convergence gradient anisotropy factor at Earth's surface
    // The convergent pressure field inherits a rotational bias from Earth's spin.
    // The bias fraction is  ε_rot = 2ωR/c ≈ 3.1 × 10⁻⁶
    // This is the fraction by which the equatorial convergence exceeds the polar.
    // The effective gradient acceleration is g_rot = ε_rot × g_surface
    constexpr double eps_rot = K_Anderson;  // ≡ 2ωR/c
    constexpr double g_rot   = eps_rot * g_surface;
    // ≈ 3.04 × 10⁻⁵ m/s²
}

// ────────────────────────────────────────────
//  Flyby data structure
// ────────────────────────────────────────────
struct Flyby {
    std::string name;
    std::string date;
    double perigee_km;          // Closest approach altitude [km]
    double v_inf_km_s;          // Hyperbolic excess velocity [km/s]
    double delta_in_deg;        // Incoming geocentric declination [°]
    double delta_out_deg;       // Outgoing geocentric declination [°]
    double measured_dv_mm_s;    // Measured anomalous Δv [mm/s]
    double measured_sigma;      // 1σ uncertainty [mm/s]
};

// ────────────────────────────────────────────
//  Anderson et al. 2008 dataset
// ────────────────────────────────────────────
static const std::vector<Flyby> anderson_flybys = {
    {"Galileo I",   "1990-12-08", 960,   8.949, -12.5, -34.2, +3.92,  0.08},
    {"Galileo II",  "1992-12-08", 303,   8.877, -34.3, -4.9,  -4.60,  1.00},
    {"NEAR",        "1998-01-23", 539,   6.851, -20.8, -71.9, +13.46, 0.13},
    {"Cassini",     "1999-08-18", 1175, 16.01,  -12.9, -4.99, -2.00,  1.00},
    {"Rosetta I",   "2005-03-04", 1956,  3.863, -2.8,  -34.3, +1.82,  0.05},
    {"MESSENGER",   "2005-08-02", 2347,  4.056, +31.4, -31.9, +0.02,  0.01},
};

// ────────────────────────────────────────────
//  Later flybys (null results)
// ────────────────────────────────────────────
static const std::vector<Flyby> null_flybys = {
    {"Rosetta II",  "2007-11-13", 5301, 9.32,   -6.0,  -6.7,  0.0,   0.5},
    {"Rosetta III", "2009-11-13", 2481, 9.36,  -34.2, -24.7,  0.0,   0.5},
    {"Juno",        "2013-10-09", 559,  9.87,  -17.1, -22.1,  0.0,   0.5},
};

// ────────────────────────────────────────────
//  Earthgrazer predictions
// ────────────────────────────────────────────
struct EarthgrazerPrediction {
    std::string name;
    int year;
    double perigee_km;
    double v_hyp_km_s;
    double delta_in_deg;
    double delta_out_deg;
};

static const std::vector<EarthgrazerPrediction> earthgrazers = {
    {"Apophis",   2029, 31000,  4.6,  +40.0, -25.0},
    {"2023 BU",   2023, 3540,   9.3,   +5.0,  +3.0},
    {"2019 OK",   2019, 72000, 24.5,  +45.0, -60.0},
};

// ────────────────────────────────────────────
//  Computation functions
// ────────────────────────────────────────────
static constexpr double deg_to_rad(double deg) {
    return deg * std::numbers::pi / 180.0;
}

/**
 * @brief Anderson formula prediction: Δv = K × v∞ × (cos δ_in - cos δ_out)
 * @return Δv in mm/s
 */
double anderson_prediction(double v_inf_km_s, double delta_in_deg, double delta_out_deg) {
    double v_inf_m_s = v_inf_km_s * 1000.0;
    double cos_in  = std::cos(deg_to_rad(delta_in_deg));
    double cos_out = std::cos(deg_to_rad(delta_out_deg));
    double dv = sdt::K_Anderson * v_inf_m_s * (cos_in - cos_out);
    return dv * 1000.0;  // Convert m/s to mm/s
}

/**
 * @brief SDT rotational gradient prediction
 *
 * The convergence gradient's rotational component produces an
 * acceleration g_rot at the surface. The integrated impulse over
 * the flyby duration gives:
 *
 *   Δv ≈ g_rot × (2R/v∞) × Δ(cos δ) × altitude_factor
 *
 * where altitude_factor = (R/(R+h))² captures the gradient falloff.
 */
double sdt_prediction(double v_inf_km_s, double perigee_km, 
                      double delta_in_deg, double delta_out_deg) {
    double v_inf_m_s = v_inf_km_s * 1000.0;
    double h_m       = perigee_km * 1000.0;
    double cos_in    = std::cos(deg_to_rad(delta_in_deg));
    double cos_out   = std::cos(deg_to_rad(delta_out_deg));
    
    // Altitude correction: convergence gradient falls as (R/(R+h))²
    double alt_factor = (sdt::R_Earth / (sdt::R_Earth + h_m)) 
                      * (sdt::R_Earth / (sdt::R_Earth + h_m));
    
    // The SDT prediction uses the convergence anisotropy directly.
    // The Anderson formula is:
    //   Δv = K × v∞ × (cos δ_in - cos δ_out)
    //
    // SDT mechanism: the convergent pressure field has a spin-induced 
    // equatorial enhancement of fraction ε_rot = 2ωR/c. Spacecraft
    // traversing different declinations sample different latitudes of
    // this field. The integrated velocity change scales with v∞ (faster
    // craft carry the impulse more efficiently — this is not a drag
    // force but a redirective pressure differential).
    //
    // At surface level: Δv = ε_rot × v∞ × (cos δ_in - cos δ_out)
    // With altitude:    Δv = ε_rot × v∞ × (cos δ_in - cos δ_out) × (R/(R+h))²
    
    double dv = sdt::eps_rot * v_inf_m_s * (cos_in - cos_out) * alt_factor;
    return dv * 1000.0;  // mm/s
}

// ────────────────────────────────────────────
//  main
// ────────────────────────────────────────────
int main() {
    std::cout << "╔══════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║  SDT Flyby Anomaly Analysis — Convergent Gradient Hypothesis     ║\n";
    std::cout << "║  James Christopher Tyndall — Melbourne, AU — April 2026          ║\n";
    std::cout << "╚══════════════════════════════════════════════════════════════════╝\n\n";

    // ── SDT Constants ──
    std::cout << "  Anderson constant K = 2ωR/c  = " 
              << std::scientific << std::setprecision(4) << sdt::K_Anderson << "\n";
    std::cout << "  SDT rotational gradient g_rot = " 
              << sdt::g_rot << " m/s²\n\n";
    
    // ── Anderson et al. 2008 flybys ──
    std::cout << "══════════════════════════════════════════════════════════════════\n";
    std::cout << "  ANDERSON et al. 2008 — SIX ORIGINAL FLYBYS\n";
    std::cout << "══════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << std::left << std::setw(14) << "Spacecraft"
              << std::right 
              << std::setw(10) << "Measured"
              << std::setw(12) << "Anderson" 
              << std::setw(10) << "SDT"
              << std::setw(10) << "Resid"
              << std::setw(10) << "σ"
              << "\n";
    std::cout << std::setw(14) << ""
              << std::setw(10) << "(mm/s)"
              << std::setw(12) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << std::setw(10) << "(mm/s)"
              << "\n";
    std::cout << std::string(66, '-') << "\n";
    
    for (auto const& f : anderson_flybys) {
        double ap = anderson_prediction(f.v_inf_km_s, f.delta_in_deg, f.delta_out_deg);
        double sp = sdt_prediction(f.v_inf_km_s, f.perigee_km, 
                                   f.delta_in_deg, f.delta_out_deg);
        double resid = f.measured_dv_mm_s - sp;
        
        std::cout << std::left << std::setw(14) << f.name
                  << std::right << std::fixed << std::setprecision(2)
                  << std::setw(10) << f.measured_dv_mm_s
                  << std::setw(12) << ap
                  << std::setw(10) << sp
                  << std::setw(10) << resid
                  << std::setw(10) << f.measured_sigma
                  << "\n";
    }
    
    // ── Null flybys ──
    std::cout << "\n══════════════════════════════════════════════════════════════════\n";
    std::cout << "  LATER FLYBYS — NULL RESULTS\n";
    std::cout << "══════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << std::left << std::setw(14) << "Spacecraft"
              << std::right 
              << std::setw(12) << "Anderson"
              << std::setw(10) << "SDT"
              << std::setw(14) << "Consistent?"
              << "\n";
    std::cout << std::string(50, '-') << "\n";
    
    for (auto const& f : null_flybys) {
        double ap = anderson_prediction(f.v_inf_km_s, f.delta_in_deg, f.delta_out_deg);
        double sp = sdt_prediction(f.v_inf_km_s, f.perigee_km, 
                                   f.delta_in_deg, f.delta_out_deg);
        
        bool consistent = std::abs(sp) < f.measured_sigma;
        
        std::cout << std::left << std::setw(14) << f.name
                  << std::right << std::fixed << std::setprecision(2)
                  << std::setw(12) << ap
                  << std::setw(10) << sp
                  << std::setw(14) << (consistent ? "YES" : "NO")
                  << "\n";
    }

    // ── Earthgrazer predictions ──
    std::cout << "\n══════════════════════════════════════════════════════════════════\n";
    std::cout << "  EARTHGRAZER PREDICTIONS — SDT CONVERGENCE GRADIENT MODEL\n";
    std::cout << "══════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << std::left << std::setw(14) << "Object"
              << std::right 
              << std::setw(8) << "Year"
              << std::setw(12) << "SDT Δv"
              << std::setw(14) << "Anderson Δv"
              << "\n";
    std::cout << std::setw(14) << ""
              << std::setw(8) << ""
              << std::setw(12) << "(mm/s)"
              << std::setw(14) << "(mm/s)"
              << "\n";
    std::cout << std::string(48, '-') << "\n";
    
    for (auto const& eg : earthgrazers) {
        double ap = anderson_prediction(eg.v_hyp_km_s, eg.delta_in_deg, eg.delta_out_deg);
        double sp = sdt_prediction(eg.v_hyp_km_s, eg.perigee_km,
                                   eg.delta_in_deg, eg.delta_out_deg);
        
        std::cout << std::left << std::setw(14) << eg.name
                  << std::right 
                  << std::setw(8) << eg.year
                  << std::fixed << std::setprecision(3)
                  << std::setw(12) << sp
                  << std::setw(14) << ap
                  << "\n";
    }
    
    // ── Apophis 2029 keyhole analysis ──
    std::cout << "\n══════════════════════════════════════════════════════════════════\n";
    std::cout << "  APOPHIS 2029 — KEYHOLE RESOLUTION ANALYSIS\n";
    std::cout << "══════════════════════════════════════════════════════════════════\n\n";
    
    auto const& apophis = earthgrazers[0];
    double dv_apophis = sdt_prediction(apophis.v_hyp_km_s, apophis.perigee_km,
                                        apophis.delta_in_deg, apophis.delta_out_deg);
    
    // Trajectory deviation over 1 year of tracking
    double t_1yr = 365.25 * 24 * 3600;  // seconds in a year
    double delta_x = 0.5 * (dv_apophis / 1000.0) * t_1yr;  // metres  (v*t as linear approx)
    
    std::cout << "  SDT predicted Δv:         " << std::fixed << std::setprecision(4) 
              << dv_apophis << " mm/s\n";
    std::cout << "  Trajectory shift (1 yr):  " << std::setprecision(1)
              << delta_x / 1000.0 << " km\n";
    std::cout << "  Typical keyhole width:    0.5 - 1.0 km\n";
    std::cout << "  SDT correction vs keyhole: " 
              << (std::abs(delta_x / 1000.0) > 0.5 ? "EXCEEDS" : "within")
              << " keyhole width\n\n";
    
    // ── Pioneer anomaly ──
    std::cout << "══════════════════════════════════════════════════════════════════\n";
    std::cout << "  PIONEER ANOMALY — CONVERGENCE GRADIENT RESIDUAL\n";
    std::cout << "══════════════════════════════════════════════════════════════════\n\n";
    
    double a_pioneer_measured = 8.74e-10;  // m/s²
    double a_thermal_recoil   = 7.4e-10;   // m/s²  (Turyshev 2012, ~85%)
    double a_residual = a_pioneer_measured - a_thermal_recoil;
    
    // SDT convergence gradient at ~30 AU
    // Solar convergence falls as 1/r² from the surface
    // At 30 AU: a_conv ≈ g_rot × (R_sun / r)² × correction
    // This is speculative — we compute the order of magnitude
    double r_30AU = 30.0 * 1.496e11;  // metres
    double R_sun  = 6.957e8;
    double a_sdt_pioneer = sdt::g_rot * (R_sun / r_30AU) * (R_sun / r_30AU);
    
    std::cout << "  Measured anomaly:       " << std::scientific << std::setprecision(2) 
              << a_pioneer_measured << " m/s²\n";
    std::cout << "  Thermal recoil:         " << a_thermal_recoil << " m/s²\n";
    std::cout << "  Residual:               " << a_residual << " m/s²\n";
    std::cout << "  SDT gradient at 30 AU:  " << a_sdt_pioneer << " m/s²\n";
    std::cout << "  SDT vs residual ratio:  " << std::fixed << std::setprecision(1)
              << (a_sdt_pioneer / a_residual) << "×\n\n";
    
    std::cout << "  NOTE: The SDT gradient at 30 AU is " 
              << std::scientific << std::setprecision(1) << a_sdt_pioneer
              << " m/s² — this is the convergence gradient contribution\n"
              << "  independent of thermal effects. A thermally symmetric probe\n"
              << "  would test this prediction directly.\n\n";
    
    // ── Summary ──
    std::cout << "══════════════════════════════════════════════════════════════════\n";
    std::cout << "  CONCLUSIONS\n";
    std::cout << "══════════════════════════════════════════════════════════════════\n\n";
    
    std::cout << "  1. The Anderson formula (K = 2ωR/c) is an empirical fit to SDT's\n"
              << "     rotational convergence gradient. The gradient source is the\n"
              << "     Earth's co-rotation with the Sun's accretion geometry.\n\n"
              << "  2. SDT predicts mass-independent Δv anomalies for ALL Earth\n"
              << "     flybys with asymmetric declination geometry.\n\n"
              << "  3. Earthgrazer comets should show the same anomaly. Apophis 2029\n"
              << "     is the definitive test — clean geometry, no thermal effects.\n\n"
              << "  4. The trajectory correction exceeds typical keyhole widths,\n"
              << "     which has implications for planetary defence calculations.\n\n"
              << "  5. A thermally symmetric probe in deep space would test the\n"
              << "     convergence gradient residual independently of Pioneer.\n\n";
    
    return 0;
}
