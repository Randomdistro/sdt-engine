#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>

constexpr double c  = 2.99792458e8;
constexpr double AU = 1.49597871e11;

struct Body {
    std::string name;
    double R;           // radius (m)
    double z;           // surface z
    double rot_period;  // rotation period (s)
};

struct Moon {
    std::string name;
    double a;           // semi-major axis (m)
    double P;           // orbital period (s)
    double R_moon;      // moon radius (m), 0 if unknown
    double z_moon;      // moon surface z, 0 if unknown
};

void analyse_system(const Body& host, const std::vector<Moon>& moons,
                    const std::string& title, double T_sun_surface) {
    double k = 1.0 / std::sqrt(host.z);
    double v_surf = c / k;
    double T_surf = 2.0 * M_PI * host.R / v_surf;
    double kappa = host.R * host.z;

    std::cout << "# " << title << "\n\n";
    std::cout << "## Host: " << host.name << "\n\n";
    std::cout << "```\n";
    std::cout << "R       = " << std::scientific << std::setprecision(4) << host.R << " m\n";
    std::cout << "z       = " << std::scientific << std::setprecision(6) << host.z << "\n";
    std::cout << "k       = " << std::fixed << std::setprecision(2) << k << "\n";
    std::cout << "v_surf  = " << std::fixed << std::setprecision(1) << v_surf << " m/s ("
              << std::setprecision(6) << v_surf/c << " c)\n";
    std::cout << "kappa   = " << std::fixed << std::setprecision(4) << kappa << " m\n";
    std::cout << "T_surf  = " << std::fixed << std::setprecision(2) << T_surf << " s\n";
    std::cout << "sqrt(T) = " << std::fixed << std::setprecision(4) << std::sqrt(T_surf) << "\n";
    std::cout << "T_rot   = " << std::fixed << std::setprecision(2) << host.rot_period << " s ("
              << std::setprecision(4) << host.rot_period/3600.0 << " h)\n";
    std::cout << "T_rot / T_surf = " << std::fixed << std::setprecision(6) << host.rot_period / T_surf << "\n";

    // Light distances
    double d_Tsurf = T_surf * c;
    std::cout << "\nc * T_surf = " << std::scientific << std::setprecision(4) << d_Tsurf << " m = "
              << std::fixed << std::setprecision(4) << d_Tsurf / AU << " AU\n";
    std::cout << "c * T_surf / (2*pi*R) = " << std::fixed << std::setprecision(2)
              << d_Tsurf / (2.0*M_PI*host.R) << " = k\n";
    std::cout << "```\n\n";

    // === MOONS TABLE — RAW ===
    std::cout << "## Satellites — Raw\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(16) << "Moon"
              << std::right
              << std::setw(14) << "a (m)"
              << std::setw(10) << "a/R_host"
              << std::setw(14) << "P (s)"
              << std::setw(12) << "P/T_surf"
              << std::setw(10) << "sqrt(P/T)"
              << std::setw(12) << "v_orb(m/s)"
              << std::setw(12) << "v_pred(m/s)"
              << std::setw(8) << "v_err%"
              << "\n";
    std::cout << std::string(108, '-') << "\n";

    for (auto& m : moons) {
        double a_ratio = m.a / host.R;
        double P_ratio = m.P / T_surf;
        double v_actual = 2.0 * M_PI * m.a / m.P;
        double v_predicted = (c / k) * std::sqrt(host.R / m.a);
        double v_err = (v_actual - v_predicted) / v_predicted * 100.0;

        // Check: P/T_surf should equal (a/R)^(3/2)
        std::cout << std::left << std::setw(16) << m.name
                  << std::right
                  << std::scientific << std::setprecision(3) << std::setw(14) << m.a
                  << std::fixed << std::setprecision(2) << std::setw(10) << a_ratio
                  << std::scientific << std::setprecision(3) << std::setw(14) << m.P
                  << std::fixed << std::setprecision(4) << std::setw(12) << P_ratio
                  << std::fixed << std::setprecision(4) << std::setw(10) << std::sqrt(P_ratio)
                  << std::fixed << std::setprecision(1) << std::setw(12) << v_actual
                  << std::fixed << std::setprecision(1) << std::setw(12) << v_predicted
                  << std::showpos << std::fixed << std::setprecision(2) << std::setw(8) << v_err
                  << std::noshowpos
                  << "\n";
    }
    std::cout << "```\n\n";

    // === MOONS TABLE — NORMALISED ===
    std::cout << "## Satellites — Normalised to T_surf and R_host\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(16) << "Moon"
              << std::right
              << std::setw(10) << "a/R"
              << std::setw(12) << "P/T_surf"
              << std::setw(14) << "(a/R)^(3/2)"
              << std::setw(10) << "match%"
              << std::setw(12) << "v/v_surf"
              << std::setw(14) << "1/sqrt(a/R)"
              << std::setw(10) << "match%"
              << "\n";
    std::cout << std::string(98, '-') << "\n";

    for (auto& m : moons) {
        double a_ratio = m.a / host.R;
        double P_ratio = m.P / T_surf;
        double pred_P = std::pow(a_ratio, 1.5);
        double P_match = pred_P / P_ratio * 100.0;
        double v_actual = 2.0 * M_PI * m.a / m.P;
        double v_ratio = v_actual / v_surf;
        double pred_v = 1.0 / std::sqrt(a_ratio);
        double v_match = pred_v / v_ratio * 100.0;

        std::cout << std::left << std::setw(16) << m.name
                  << std::right
                  << std::fixed << std::setprecision(2) << std::setw(10) << a_ratio
                  << std::fixed << std::setprecision(4) << std::setw(12) << P_ratio
                  << std::fixed << std::setprecision(4) << std::setw(14) << pred_P
                  << std::fixed << std::setprecision(3) << std::setw(10) << P_match
                  << std::fixed << std::setprecision(6) << std::setw(12) << v_ratio
                  << std::fixed << std::setprecision(6) << std::setw(14) << pred_v
                  << std::fixed << std::setprecision(3) << std::setw(10) << v_match
                  << "\n";
    }
    std::cout << "```\n\n";

    // === CROSS-NORMALISATION: Express in Sun's T_surface ===
    std::cout << "## Cross-normalised to Solar T_surface (" << std::fixed << std::setprecision(1)
              << T_sun_surface << " s)\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(16) << "Moon"
              << std::right
              << std::setw(14) << "P/T_sun_surf"
              << std::setw(14) << "P/T_jup_surf"
              << std::setw(14) << "ratio"
              << "\n";
    std::cout << std::string(58, '-') << "\n";

    for (auto& m : moons) {
        double P_sun = m.P / T_sun_surface;
        double P_jup = m.P / T_surf;
        std::cout << std::left << std::setw(16) << m.name
                  << std::right
                  << std::fixed << std::setprecision(4) << std::setw(14) << P_sun
                  << std::fixed << std::setprecision(4) << std::setw(14) << P_jup
                  << std::fixed << std::setprecision(6) << std::setw(14) << P_sun / P_jup
                  << "\n";
    }
    std::cout << "\nT_jup_surf / T_sun_surf = " << std::fixed << std::setprecision(6) << T_surf / T_sun_surface << "\n";
    std::cout << "k_jup / k_sun = " << std::fixed << std::setprecision(4)
              << (1.0/std::sqrt(host.z)) / (1.0/std::sqrt(2.12270e-6)) << "\n";
    std::cout << "```\n\n";

    // === MOON-TO-MOON PERIOD RATIOS ===
    std::cout << "## Moon-to-Moon Period Ratios\n\n";
    std::cout << "```\n";
    for (int i = 0; i < (int)moons.size(); i++) {
        for (int j = i+1; j < (int)moons.size(); j++) {
            double ratio = moons[j].P / moons[i].P;
            double nearest_frac = std::round(ratio * 4.0) / 4.0;
            std::cout << std::left << std::setw(12) << moons[j].name << "/"
                      << std::setw(12) << moons[i].name
                      << "= " << std::fixed << std::setprecision(4) << ratio;
            // Check if close to simple fraction
            for (int n = 1; n <= 20; n++) {
                for (int d = 1; d <= 10; d++) {
                    double frac = (double)n / d;
                    if (std::abs(ratio - frac) / frac < 0.01) {
                        std::cout << "  ~= " << n << "/" << d;
                        goto done;
                    }
                }
            }
            done:
            std::cout << "\n";
        }
    }
    std::cout << "```\n\n";

    // === ROTATION / SURFACE COUPLING ===
    std::cout << "## Rotation Coupling\n\n";
    std::cout << "```\n";
    std::cout << "T_rotation / T_surface = " << std::fixed << std::setprecision(6) << host.rot_period / T_surf << "\n";
    double rot_over_surf = host.rot_period / T_surf;

    // How many surfaces per day?
    std::cout << "Surfaces per rotation = " << std::fixed << std::setprecision(6) << rot_over_surf << "\n";
    std::cout << "  nearest integer: " << std::round(rot_over_surf) << " (off by "
              << std::showpos << std::setprecision(4) << (rot_over_surf - std::round(rot_over_surf)) / std::round(rot_over_surf) * 100
              << "%)" << std::noshowpos << "\n\n";

    // For each moon: how many rotations fit in one orbit?
    for (auto& m : moons) {
        double orbits_per_rot = m.P / host.rot_period;
        std::cout << m.name << ": " << std::fixed << std::setprecision(4) << orbits_per_rot
                  << " rotations/orbit";
        double nearest = std::round(orbits_per_rot * 2) / 2.0;
        std::cout << "  (nearest half: " << nearest << ", off "
                  << std::showpos << std::setprecision(2) << (orbits_per_rot - nearest) / nearest * 100
                  << "%)" << std::noshowpos << "\n";
    }
    std::cout << "```\n\n";

    // === DISTANCE NORMALISATION ===
    std::cout << "## Distance Normalisation\n\n";
    std::cout << "```\n";
    std::cout << std::left << std::setw(16) << "Moon"
              << std::right
              << std::setw(10) << "a/R"
              << std::setw(10) << "a/kappa"
              << std::setw(14) << "a/(c*T_surf)"
              << std::setw(14) << "a*z"
              << "\n";
    std::cout << std::string(64, '-') << "\n";

    for (auto& m : moons) {
        double a_R = m.a / host.R;
        double a_kappa = m.a / kappa;
        double a_cT = m.a / (c * T_surf);
        double a_z = m.a * host.z;
        std::cout << std::left << std::setw(16) << m.name
                  << std::right
                  << std::fixed << std::setprecision(2) << std::setw(10) << a_R
                  << std::scientific << std::setprecision(3) << std::setw(10) << a_kappa
                  << std::scientific << std::setprecision(4) << std::setw(14) << a_cT
                  << std::fixed << std::setprecision(4) << std::setw(14) << a_z
                  << "\n";
    }
    std::cout << "```\n";
}

int main() {
    // === SUN ===
    Body sun = {"Sun", 6.95700e8, 2.12270e-6, 25.38*86400.0};  // sidereal rotation
    double T_sun_surf = 2.0 * M_PI * sun.R / (c / (1.0/std::sqrt(sun.z)));

    // Solar system "moons" = planets
    std::vector<Moon> planets = {
        {"Mercury",  5.791e10,  7.600e6,  2.440e6, 0},
        {"Venus",    1.082e11,  1.941e7,  6.052e6, 0},
        {"Earth",    1.496e11,  3.156e7,  6.371e6, 6.954e-10},
        {"Mars",     2.279e11,  5.936e7,  3.390e6, 0},
        {"Jupiter",  7.785e11,  3.744e8,  7.149e7, 1.4838e-8},
        {"Saturn",   1.434e12,  9.295e8,  5.823e7, 0},
    };

    analyse_system(sun, planets, "Sun — Planetary System", T_sun_surf);
    std::cout << "\n---\n---\n\n";

    // === JUPITER ===
    Body jupiter = {"Jupiter", 7.149e7, 1.9714e-8, 9.925*3600.0};

    std::vector<Moon> jup_moons = {
        {"Metis",     1.280e8,  2.552e4,  2.16e4, 0},
        {"Adrastea",  1.290e8,  2.573e4,  8.2e3,  0},
        {"Amalthea",  1.814e8,  4.318e4,  8.35e4, 0},
        {"Thebe",     2.219e8,  5.832e4,  4.93e4, 0},
        {"Io",        4.218e8,  1.528e5,  1.822e6, 0},
        {"Europa",    6.711e8,  3.068e5,  1.561e6, 0},
        {"Ganymede",  1.070e9,  6.182e5,  2.634e6, 0},
        {"Callisto",  1.883e9,  1.442e6,  2.410e6, 0},
        {"Himalia",   1.146e10, 2.177e7,  8.5e4,  0},
    };

    analyse_system(jupiter, jup_moons, "Jupiter — Satellite System", T_sun_surf);

    return 0;
}
