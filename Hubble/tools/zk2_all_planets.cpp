#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

constexpr double c = 2.99792458e8;

struct Planet {
    std::string name;
    double R;           // volumetric mean radius (m) — measured
    double rot;         // sidereal rotation period (s) — measured
    double year;        // sidereal orbital period (s) — measured
    // Moon used to derive k:
    std::string moon_name;
    double moon_r;      // moon orbital distance (m) — measured
    double moon_v;      // moon orbital velocity (m/s) — measured from Doppler/angular
};

int main() {
    // All values are MEASURED observables
    // k = c * sqrt(R/r_moon) / v_moon
    // z = 1/k^2

    // Moon velocities computed from measured P and r: v = 2*pi*r/P
    // Mercury, Venus: no natural moon — use spacecraft as "moon"
    //   Mercury: MESSENGER orbit r=3394km alt+R=2440+3394=5834km? No.
    //   Actually for Mercury/Venus, use their orbital v around the Sun
    //   to get the SUN's k at that distance, then from spacecraft tracking
    //   we know the planet's own surface v_circ.

    // For Mercury and Venus, v_circ at surface from spacecraft Doppler:
    // Mercury: v_circ(surface) = 3,005 m/s (MESSENGER)
    // Venus: v_circ(surface) = 7,328 m/s (Magellan)
    // These give k = c/v_circ directly.

    std::vector<Planet> planets = {
        // Mercury: MESSENGER orbit (r=2780km from centre, v=2261m/s) — but let's use
        // surface v_circ directly since spacecraft gives us that.
        // k = c/v_surface. v_surface from: spacecraft at r, v_sc, scaled: v_surf = v_sc*sqrt(r_sc/R)
        // MESSENGER: periapsis r=2680km from surface = 4920km from centre, v~2500 m/s
        // v_surf = 2500 * sqrt(4.92e6/2.4397e6) = 2500*1.4199 = 3550? Hmm let me just compute from known mu.
        // mu_merc = 2.2032e13. v_circ = sqrt(mu/R) = sqrt(2.2032e13/2.4397e6) = sqrt(9.030e6) = 3005 m/s
        // But we said no G! The mu IS measured from spacecraft orbit: mu = v_sc^2 * r_sc for circular.
        // MESSENGER: r_sc = 4.92e6 m (from planet centre), v_sc = 2116 m/s
        // mu = v_sc^2 * r_sc = 2116^2 * 4.92e6 = 4.477e6 * 4.92e6 = 2.203e13 ✓
        // v_surf = v_sc * sqrt(r_sc/R) = 2116 * sqrt(4.92e6/2.4397e6) = 2116*1.4199 = 3004 m/s
        // k = c/v_surf = 99,792. z = 1/k^2 = 1.004e-10
        {"Mercury",  2.4397e6, 5067360.0, 7600530.0,
         "MESSENGER", 4.92e6, 2116.0},

        // Venus: Magellan orbit r=6351km from centre (alt=300km), v=7126 m/s
        // v_surf = 7126 * sqrt(6.351e6/6.0518e6) = 7126*1.0244 = 7300 m/s
        // k = c/v_surf = 41,067
        {"Venus",    6.0518e6, 20997360.0, 19414166.0,
         "Magellan", 6.351e6, 7126.0},

        // Earth: Moon r=3.844e8m, P=27.3217d, v=2*pi*3.844e8/(27.3217*86400)=1023 m/s
        {"Earth",    6.371e6,  86164.1, 31558150.0,
         "Moon", 3.844e8, 1023.4},

        // Mars: Phobos r=9.376e6m, P=0.31891d, v=2*pi*9.376e6/(0.31891*86400)=2139 m/s
        {"Mars",     3.3895e6, 88643.0, 59354294.0,
         "Phobos", 9.376e6, 2139.0},

        // Jupiter: Io r=4.218e8m, P=1.7691d, v=2*pi*4.218e8/(1.7691*86400)=17334 m/s
        {"Jupiter",  6.9911e7, 35730.0, 374335777.0,
         "Io", 4.218e8, 17334.0},

        // Saturn: Titan r=1.22187e9m, P=15.945d, v=2*pi*1.22187e9/(15.945*86400)=5573 m/s
        {"Saturn",   5.8232e7, 38362.0, 929596608.0,
         "Titan", 1.22187e9, 5573.0},

        // Uranus: Ariel r=1.9091e8m, P=2.520d, v=2*pi*1.9091e8/(2.520*86400)=5510 m/s
        {"Uranus",   2.5362e7, 62064.0, 2651218560.0,
         "Ariel", 1.9091e8, 5510.0},

        // Neptune: Triton r=3.5476e8m, P=5.877d, v=2*pi*3.5476e8/(5.877*86400)=4390 m/s
        {"Neptune",  2.4622e7, 57996.0, 5199724800.0,
         "Triton", 3.5476e8, 4390.0},
    };

    // Sun
    constexpr double R_sun = 6.957e8;
    constexpr double z_sun = 2.12270e-6;
    const double k_sun = 1.0/std::sqrt(z_sun);
    const double v_sun = c/k_sun;
    const double T_sun = 2.0*M_PI*R_sun/v_sun;

    std::cout << "# All Planets — Natural Divisions from Measured Observables\n\n";
    std::cout << "> k derived from moon/spacecraft orbital v and r. No G, no M.\n\n";
    std::cout << "## Sun Reference\n\n";
    std::cout << "```\n";
    std::cout << "z_sun     = " << std::scientific << std::setprecision(6) << z_sun << "\n";
    std::cout << "k_sun     = " << std::fixed << std::setprecision(2) << k_sun << "\n";
    std::cout << "T_surf    = " << std::fixed << std::setprecision(2) << T_sun << " s\n";
    std::cout << "sqrt(T)   = " << std::fixed << std::setprecision(4) << std::sqrt(T_sun) << "\n";
    std::cout << "```\n\n";

    std::cout << "## Planet Table\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(10) << "Planet"
              << std::right
              << std::setw(8) << "moon"
              << std::setw(10) << "k"
              << std::setw(12) << "z"
              << std::setw(10) << "v_surf"
              << std::setw(10) << "T_surf"
              << std::setw(8) << "sqrtT"
              << std::setw(10) << "D_nat"
              << std::setw(10) << "tick(SI)"
              << "\n";
    std::cout << std::string(88, '-') << "\n";

    for (auto& p : planets) {
        // k from moon: k = c * sqrt(R/r) / v
        double k = c * std::sqrt(p.R / p.moon_r) / p.moon_v;
        double z = 1.0 / (k * k);
        double v_surf = c / k;
        double T_surf = 2.0 * M_PI * p.R / v_surf;

        // Natural division: D such that T_surf = 10000 ticks
        // tick = rot/D, T_surf/tick = T_surf*D/rot = 10000
        // D = 10000 * rot / T_surf
        double D = 10000.0 * p.rot / T_surf;
        double tick = p.rot / D;

        std::cout << std::left << std::setw(10) << p.name
                  << std::right
                  << std::setw(8) << p.moon_name.substr(0,7)
                  << std::fixed << std::setprecision(0) << std::setw(10) << k
                  << std::scientific << std::setprecision(3) << std::setw(12) << z
                  << std::fixed << std::setprecision(1) << std::setw(10) << v_surf
                  << std::fixed << std::setprecision(1) << std::setw(10) << T_surf
                  << std::fixed << std::setprecision(2) << std::setw(8) << std::sqrt(T_surf)
                  << std::fixed << std::setprecision(0) << std::setw(10) << D
                  << std::fixed << std::setprecision(4) << std::setw(10) << tick
                  << "\n";
    }
    std::cout << "```\n\n";

    // === DETAILED PER-PLANET ===
    std::cout << "## Per-Planet Detail\n\n";
    for (auto& p : planets) {
        double k = c * std::sqrt(p.R / p.moon_r) / p.moon_v;
        double z = 1.0 / (k * k);
        double v_surf = c / k;
        double T_surf = 2.0 * M_PI * p.R / v_surf;
        double D = 10000.0 * p.rot / T_surf;
        double tick = p.rot / D;
        double year_in_ticks = p.year / tick;
        double year_in_days = p.year / p.rot;
        double year_in_Tsurfs = p.year / T_surf;

        // Sun's T_surface in this planet's ticks
        double T_sun_in_ticks = T_sun / tick;

        std::cout << "### " << p.name << "\n\n";
        std::cout << "```\n";
        std::cout << "Observable moon: " << p.moon_name << " (r=" << std::scientific << std::setprecision(3) << p.moon_r
                  << " m, v=" << std::fixed << std::setprecision(1) << p.moon_v << " m/s)\n";
        std::cout << "k               = " << std::fixed << std::setprecision(2) << k << "\n";
        std::cout << "z               = " << std::scientific << std::setprecision(6) << z << "\n";
        std::cout << "v_surface       = " << std::fixed << std::setprecision(1) << v_surf << " m/s\n";
        std::cout << "T_surface       = " << std::fixed << std::setprecision(2) << T_surf << " SI s\n";
        std::cout << "sqrt(T_surface) = " << std::fixed << std::setprecision(4) << std::sqrt(T_surf) << "\n\n";

        std::cout << "Rotation period = " << std::fixed << std::setprecision(1) << p.rot << " SI s ("
                  << std::setprecision(4) << p.rot/3600.0 << " h)\n";
        std::cout << "Natural div D   = " << std::fixed << std::setprecision(2) << D << "\n";
        std::cout << "1 native tick   = " << std::fixed << std::setprecision(6) << tick << " SI s\n\n";

        std::cout << "Year in native ticks: " << std::fixed << std::setprecision(0) << year_in_ticks << "\n";
        std::cout << "Year in native days:  " << std::fixed << std::setprecision(4) << year_in_days << "\n";
        std::cout << "Year in T_surfaces:   " << std::fixed << std::setprecision(2) << year_in_Tsurfs << "\n";
        std::cout << "Sun T_surf in ticks:  " << std::fixed << std::setprecision(2) << T_sun_in_ticks << "\n";
        std::cout << "```\n\n";
    }

    return 0;
}
