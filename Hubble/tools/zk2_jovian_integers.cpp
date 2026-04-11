#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

constexpr double c = 2.99792458e8;

int main() {
    // ============================================
    // EARTH SYSTEM — for comparison template
    // ============================================
    constexpr double E_day_s      = 86400.0;          // Earth sidereal day in SI seconds
    constexpr double E_sid_day_s  = 86164.1;          // Earth sidereal day (actual)
    constexpr double E_year_s     = 365.25636 * E_day_s; // sidereal year
    constexpr double E_R          = 6.371e6;           // m
    constexpr double R_sun        = 6.957e8;
    constexpr double z_sun        = 2.12270e-6;
    constexpr double Moon_P       = 27.3217 * E_day_s; // sidereal month in SI seconds
    constexpr double Moon_a       = 3.844e8;           // m

    const double k_sun  = 1.0/std::sqrt(z_sun);
    const double v_sun  = c/k_sun;
    const double T_sun  = 2.0*M_PI*R_sun/v_sun;

    // Earth "second" = 1/86400 of Earth rotation
    constexpr double E_sec = E_day_s / 86400.0;  // = 1.0 SI second (by definition)

    // ============================================
    // JUPITER SYSTEM — same ratios
    // ============================================
    constexpr double J_day_s      = 35730.0;           // Jupiter sidereal rotation in SI seconds
    constexpr double J_year_s     = 3.74356e8;         // Jupiter sidereal orbital period in SI seconds
    constexpr double J_R          = 6.9911e7;          // volumetric mean radius (m)
    constexpr double GM_jup       = 1.26687e17;

    const double z_jup = GM_jup / (J_R * c * c);
    const double k_jup = 1.0/std::sqrt(z_jup);
    const double v_jup = c/k_jup;
    const double T_jup = 2.0*M_PI*J_R/v_jup;

    // Jovian "second" = 1/86400 of Jupiter rotation
    const double J_sec = J_day_s / 86400.0;  // in SI seconds

    // Jovian "year" in Jovian "days"
    const double J_year_jd = J_year_s / J_day_s;

    // Moon data (Galilean + inner)
    struct Moon { std::string name; double a; double P_si; double R_m; };
    std::vector<Moon> moons = {
        {"Metis",     1.280e8,  2.5526e4,  2.16e4},
        {"Adrastea",  1.290e8,  2.5730e4,  8.2e3},
        {"Amalthea",  1.814e8,  4.3180e4,  8.35e4},
        {"Thebe",     2.219e8,  5.8320e4,  4.93e4},
        {"Io",        4.218e8,  1.52854e5, 1.822e6},
        {"Europa",    6.711e8,  3.06822e5, 1.561e6},
        {"Ganymede",  1.0704e9, 6.18154e5, 2.634e6},
        {"Callisto",  1.8827e9, 1.44168e6, 2.410e6},
    };

    // ============================================
    // OUTPUT
    // ============================================
    std::cout << "# Jovian Integers — Jupiter in Jupiter's Own Units\n\n";
    std::cout << "> Same RATIO as Earth's units are to Earth\n\n";
    std::cout << "---\n\n";

    // === UNIT DEFINITIONS ===
    std::cout << "## Unit Definitions\n\n";
    std::cout << "```\n";
    std::cout << "                      Earth               Jupiter\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << "1 'second'     = 1/86400 rotation   = 1/86400 rotation\n";
    std::cout << "               = " << std::fixed << std::setprecision(4) << E_sec
              << " SI s          = " << std::setprecision(4) << J_sec << " SI s\n";
    std::cout << "1 'day'        = 1 rotation          = 1 rotation\n";
    std::cout << "               = " << std::fixed << std::setprecision(1) << E_day_s
              << " SI s       = " << std::setprecision(1) << J_day_s << " SI s\n";
    std::cout << "1 'year'       = 1 orbit             = 1 orbit\n";
    std::cout << "               = " << std::fixed << std::setprecision(2) << E_year_s/E_day_s
              << " days        = " << std::setprecision(2) << J_year_jd << " days\n";
    std::cout << "1 'radius'     = " << std::scientific << std::setprecision(3) << E_R
              << " m          = " << J_R << " m\n";
    std::cout << "```\n\n";

    // === T_SURFACE IN NATIVE UNITS ===
    std::cout << "## T_surface in Native Seconds\n\n";
    double T_sun_native  = T_sun / E_sec;   // Sun's T_surf in Earth seconds
    double T_jup_native  = T_jup / J_sec;   // Jup's T_surf in Jovian seconds

    std::cout << "```\n";
    std::cout << "IN EARTH SECONDS:\n";
    std::cout << "  Sun  T_surf = " << std::fixed << std::setprecision(2) << T_sun
              << " Earth secs   sqrt = " << std::setprecision(4) << std::sqrt(T_sun_native) << "\n";
    std::cout << "  Jup  T_surf = " << std::fixed << std::setprecision(2) << T_jup
              << " Earth secs   sqrt = " << std::setprecision(4) << std::sqrt(T_jup / E_sec) << "\n\n";

    double T_sun_in_js = T_sun / J_sec;
    double T_jup_in_js = T_jup / J_sec;
    std::cout << "IN JOVIAN SECONDS:\n";
    std::cout << "  Sun  T_surf = " << std::fixed << std::setprecision(2) << T_sun_in_js
              << " Jovian secs  sqrt = " << std::setprecision(4) << std::sqrt(T_sun_in_js) << "\n";
    std::cout << "  Jup  T_surf = " << std::fixed << std::setprecision(2) << T_jup_in_js
              << " Jovian secs  sqrt = " << std::setprecision(4) << std::sqrt(T_jup_in_js) << "\n\n";

    std::cout << "IN NATIVE SECONDS (each body in its own planet's seconds):\n";
    std::cout << "  Sun  T_surf = " << std::fixed << std::setprecision(2) << T_sun_native
              << " Earth secs   sqrt = " << std::setprecision(4) << std::sqrt(T_sun_native) << "\n";
    std::cout << "  Jup  T_surf = " << std::fixed << std::setprecision(2) << T_jup_native
              << " Jovian secs  sqrt = " << std::setprecision(4) << std::sqrt(T_jup_native) << "\n\n";

    std::cout << "RATIO:\n";
    std::cout << "  T_jup/T_sun (SI) = " << std::fixed << std::setprecision(6) << T_jup/T_sun << "\n";
    std::cout << "  J_sec/E_sec      = " << std::fixed << std::setprecision(6) << J_sec/E_sec << "\n";
    std::cout << "  E_day/J_day      = " << std::fixed << std::setprecision(6) << E_day_s/J_day_s << "\n";
    std::cout << "```\n\n";

    // === SATELLITE PERIODS IN NATIVE DAYS ===
    std::cout << "## Satellite Periods in Native Days\n\n";
    std::cout << "```\n";
    std::cout << "EARTH SYSTEM:\n";
    std::cout << "  Moon sidereal period = " << std::fixed << std::setprecision(4) << Moon_P/E_day_s << " Earth days\n";
    std::cout << "  Moon period / T_surf(Sun) = " << std::setprecision(4) << Moon_P/T_sun << " T_surfs\n";
    std::cout << "  Solar day - Sidereal day = " << std::setprecision(1) << E_day_s - E_sid_day_s << " Earth seconds\n";
    std::cout << "  Moon_sid_period / T_surf = " << std::setprecision(2) << Moon_P/T_sun << "\n\n";

    std::cout << "JUPITER SYSTEM:\n";
    for (auto& m : moons) {
        double P_jd = m.P_si / J_day_s;    // in Jovian days
        double P_js = m.P_si / J_sec;       // in Jovian seconds
        double P_Ts = m.P_si / T_jup;       // in T_surfaces
        std::cout << "  " << std::left << std::setw(12) << m.name
                  << std::right
                  << std::fixed << std::setprecision(4) << std::setw(10) << P_jd << " Jov days"
                  << std::setprecision(2) << std::setw(14) << P_js << " Jov secs"
                  << std::setprecision(4) << std::setw(12) << P_Ts << " T_surfs"
                  << "\n";
    }
    std::cout << "```\n\n";

    // === THE 236 TEST ===
    std::cout << "## The '236' Test\n\n";
    std::cout << "Earth system:\n";
    std::cout << "```\n";
    std::cout << "Moon sidereal / T_surf(Sun) = " << std::fixed << std::setprecision(2) << Moon_P/T_sun << "\n";
    std::cout << "Day - Sidereal day = " << std::fixed << std::setprecision(1) << E_day_s - E_sid_day_s << " Earth seconds\n";
    std::cout << "These are both ~236\n";
    std::cout << "```\n\n";

    std::cout << "Jupiter system (testing each moon):\n";
    std::cout << "```\n";
    // For each moon, compute: Moon_P / T_surf_jup
    // And compare to: Jovian_day_correction
    // Jovian "sidereal day" vs "solar day":
    // Jupiter's sidereal rotation = 35,730 s
    // Jupiter's "solar day" = rotation relative to Sun
    // J_solar_day = 1 / (1/J_sid_day - 1/J_year)
    double J_sid_day = J_day_s;
    double J_solar_day = 1.0 / (1.0/J_sid_day - 1.0/J_year_s);
    double J_day_diff = J_solar_day - J_sid_day;   // in SI seconds
    double J_day_diff_js = J_day_diff / J_sec;      // in Jovian seconds

    std::cout << "Jovian sidereal day   = " << std::fixed << std::setprecision(2) << J_sid_day << " SI s\n";
    std::cout << "Jovian solar day      = " << std::fixed << std::setprecision(2) << J_solar_day << " SI s\n";
    std::cout << "Difference            = " << std::fixed << std::setprecision(2) << J_day_diff << " SI s"
              << " = " << std::setprecision(4) << J_day_diff_js << " Jovian seconds\n\n";

    for (auto& m : moons) {
        double P_Ts = m.P_si / T_jup;
        std::cout << std::left << std::setw(12) << m.name
                  << std::right
                  << "  P/T_surf = " << std::fixed << std::setprecision(4) << P_Ts
                  << "  day_diff(Jov_s) = " << std::setprecision(4) << J_day_diff_js
                  << "  match? " << (std::abs(P_Ts - J_day_diff_js)/P_Ts < 0.05 ? "YES" : "no")
                  << "\n";
    }
    std::cout << "```\n\n";

    // === KEPLER IN NATIVE UNITS ===
    std::cout << "## Kepler in Native Units\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(12) << "Moon"
              << std::right
              << std::setw(10) << "a/R_jup"
              << std::setw(14) << "P(Jov days)"
              << std::setw(12) << "v_orb(m/s)"
              << std::setw(14) << "v/v_surf"
              << std::setw(10) << "err%"
              << "\n";
    std::cout << std::string(72, '-') << "\n";

    for (auto& m : moons) {
        double a_R = m.a / J_R;
        double P_jd = m.P_si / J_day_s;
        double v_act = 2.0*M_PI*m.a/m.P_si;
        double v_pred = v_jup * std::sqrt(J_R / m.a);
        double v_ratio = v_act / v_jup;
        double err = (v_act - v_pred)/v_pred*100.0;

        std::cout << std::left << std::setw(12) << m.name
                  << std::right
                  << std::fixed << std::setprecision(2) << std::setw(10) << a_R
                  << std::fixed << std::setprecision(4) << std::setw(14) << P_jd
                  << std::fixed << std::setprecision(1) << std::setw(12) << v_act
                  << std::fixed << std::setprecision(6) << std::setw(14) << v_ratio
                  << std::showpos << std::setprecision(2) << std::setw(10) << err
                  << std::noshowpos << "\n";
    }
    std::cout << "```\n";

    return 0;
}
